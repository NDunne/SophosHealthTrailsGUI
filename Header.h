#pragma once
#include <Windows.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <map>
#include <algorithm>


using namespace std;
using namespace System;
using namespace System::Collections::Generic;

String^ manageString(std::string in);

ref class HealthEvent
{
private:
	//JSON decomposition in to key:value pairs. Most values are a unary List
	Dictionary< String^, List< String^ >^ >^ values;

	//Static conversion tables from camelCase to pretty UserStrings
	static Dictionary< String^, String^ >^ userString;
	static Dictionary< String^, String^ >^ fileString;

	//Creates new List under parameter key if first for that value, or adds to the existing List under the key
	Dictionary< String^, List< String^ >^ >^ createOrAdd(Dictionary< String^, List< String^ >^ >^ map, String^ key, String^ val)
	{
		if (map->ContainsKey(key))
		{
			//Add under exisiting Key
			List< String^ >^ list;
			if (map->TryGetValue(key, list)) list->Add(val);
		}
		else
		{
			//Create new Key to add under
			List< String^ >^ newList = gcnew List< String^ >(0);
			newList->Add(val);
			map->Add(key, newList);
		}
		return map;
	}

	//Converts string JSON file into Managed Dictionary
	Dictionary<String^, List<String^ >^ >^ explode(const string& s, Dictionary< String^, List< String^ >^ >^ map)
	{
		//read buffers
		string buff{ "" };
		string key{ "" };

		//track what data is being read
		enum readingState { KEY, DATA, DATA_TIMESTAMP, LIST };
		
		readingState r = KEY; //First data will be a key

		//Iterate characters in input string
		for (auto n : s)
		{
			if (n == '{' || n == '}' || n == '"') continue; //Ignore

			if (n == ':' && r == KEY) //Keys do not contain ':' so the end of the key has been reached
			{
					r = DATA;
					key = buff;
					if (key == "timeStamp") r = DATA_TIMESTAMP;
					buff = "";
					continue;
			}
			else if (n == ',' ) //List seperator. If a key did contain a comma this is accounted for
			{
				if (r == DATA || r == DATA_TIMESTAMP || r == LIST)
				{
					//End of data string so push value under key, or create if necessary
					createOrAdd(map, manageString(key), manageString(buff));
					buff = "";
					if (r == DATA || r == DATA_TIMESTAMP)
					{
						key = "";	//Clear key if not reading a list of values
						r = KEY;
					}

					continue;
				}
				else if (r = KEY)
				{
					//Just in case a key has a comma in it, but unlikely
					buff += n;
				}
			}
			else if (n == '[') r = LIST;	//Start of list
			else if (n == ']') r = DATA;	//End of list
			else if (r == DATA_TIMESTAMP)	//Special case for timestamp, to allow date to be added as well
			{
				if (n == '-') buff += '/' ;	//replace '-' with '/' for prettiness
				else if (n == 'Z') continue; //closing Z ignored
				else if (n == 'T')			//T character seperates date and time 
				{
					createOrAdd(map, manageString("date"), manageString(buff));
					buff += "  ";
					//buffer is not clearered so date is still in timeStamp
				}
				else buff += n;
			}
			else
			{
				buff += n;	//default is add character to buffer
			}
		}
		if (buff != "") createOrAdd(map, manageString(key), manageString(buff)); //add last K/V pair if exists
		return map;
	}

public:

	static void initDicts()
	{
		userString = gcnew Dictionary< String^, String^ >(19);

		//This could be done more data Driven: Capitalise 1st letter, push extra space upon reading a capital letter
		//However Initiliasations like ID and SID would be harder to format so I did it like this and kept adding

		userString->Add("id","ID");
		userString->Add("familyId","Family ID");
		userString->Add("timeStamp","Time Stamp");
		userString->Add("app","App");
		userString->Add("severity","Severity");
		userString->Add("threatName","Threat Name");
		userString->Add("location","Location");
		userString->Add("date","Date");
		userString->Add("serviceName","Service Name");
		userString->Add("resourceId","Resource ID");
		userString->Add("sequence", "Sequence");
		userString->Add("showNotification", "Notification?");
		userString->Add("updateSummary", "Update Summary?");
		userString->Add("userName", "Username");
		userString->Add("userSid", "User SID");
		userString->Add("path", "Path");
		userString->Add("reboot", "Reboot?");
		userString->Add("origin", "Origin");
		userString->Add("threatType", "Threat Type");
		userString->Add("counterName", "Counter Name");


		fileString = gcnew Dictionary< String^, String^ >(19);
		Dictionary< String^, String^ >::Enumerator mirror = userString->GetEnumerator();

		while (mirror.MoveNext())
		{
			fileString->Add(mirror.Current.Value, mirror.Current.Key);
		}
		
	}

	//Apply conversion table from file to user format, or return input string if not found
	static String^ getUserString(String^ in)
	{
		String^ result;
		if (userString->TryGetValue(in, result)) return result;
		return in;
	}

	//Apply conversion table from user to file format, or return input string if not found
	static String^ getFileString(String^ in)
	{
		String^ result;
		if (fileString->TryGetValue(in, result)) return result;
		return in;
	}

	static List < String^ >^ sortableAttributes()
	{
		List < String^ >^ attr = gcnew List< String^ >(15);
		attr->Add("ID");
		attr->Add("Family ID");
		attr->Add("Time Stamp");
		attr->Add("App");
		attr->Add("Severity");
		attr->Add("Threat Name");
		attr->Add("Location");
		attr->Add("Date");
		attr->Add("Service Name");
		attr->Add("Resource ID");
		attr->Add("Sequence");
		attr->Add("Username");
		attr->Add("User SID");
		attr->Add("Path");
		attr->Add("Threat Type");

		return attr;
	}

	//Constructor takes string from JSON and builds map from the string
	HealthEvent(string s)
	{
		values = gcnew Dictionary< String^, List< String^ >^ >(0);
		values = explode(s, values);
	}

	//Return only first value under key String. Some attributes like ID, app will always be able to use this
	String^ getFirstValue(String^ k)
	{
		try { 
			return getValues(k)->ToArray()[0];
		}
		catch (...) { return "-"; }
	}

	// return all values below parameter key String
	List< String^ >^ getValues(String^ k)
	{
			List< String^ >^ vList;
			values->TryGetValue(k, vList);
			return vList;
	}

	//Return slightly prettier string than input. Mostly for debugging purposes
	String^ toString()
	{
		String^ buff = "";
		Dictionary< String^, List< String^ >^ >::Enumerator valEnum = values->GetEnumerator();
		while (valEnum.MoveNext())
		{
			buff += valEnum.Current.Key;
			buff += ": ";
			List< String^ >::Enumerator subEnum = valEnum.Current.Value->GetEnumerator();
			while (subEnum.MoveNext())
			{
				buff += subEnum.Current;
				buff += ", ";
			}
			buff += "| ";
		}

		return buff;
	}

	//Return HTML for Output browser display
	String^ toHTML()
	{
		//ID, APP, SEVERITY are constant, so will always bea t the top

		String^ buff = "<html><body><h1>Event Data</h1><h2>ID</h2><ul><li>";
		buff += getFirstValue("id");
		buff += "</li></ul>";
		
		buff += "<h2>App</h2><ul><li>";
		buff += getFirstValue("app");
		buff += "</li></ul>";

		buff += "<h2>Severity</h2><ul><li>";
		buff += getFirstValue("severity");
		buff += "</li></ul>";


		//Then read rest of values from map in order
		Dictionary< String^, List< String^ >^ >::Enumerator valEnum = values->GetEnumerator();
		while (valEnum.MoveNext())
		{
			String^ k = valEnum.Current.Key;
			if (k == "id" || k == "app" || k == "severity") continue;

			buff += "<h2>";
			buff += getUserString(k);
			buff += "</h2><ul>";
			List< String^ >::Enumerator subEnum = valEnum.Current.Value->GetEnumerator();
			while (subEnum.MoveNext())
			{
				buff += "<li>";
				buff += subEnum.Current;
				buff += "</li>";
			}
			buff += "</ul>" ;
		}

		buff += "</body></html>";

		return buff;
	}
};

Dictionary< String^, Dictionary< String^, List< HealthEvent^ >^ >^ >^ readFromFolder(string folder, Dictionary<String^, Dictionary< String^, List< HealthEvent^ >^ >^ >^ eventList);

Dictionary< String^, Dictionary< String^, List< HealthEvent^ >^ >^ >^ readFile(string path, Dictionary<String^, Dictionary< String^, List< HealthEvent^ >^ >^ >^ eventList);