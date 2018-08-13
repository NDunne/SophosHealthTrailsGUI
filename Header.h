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
	Dictionary< String^, List< String^ >^ >^ values;

	//Creates new List under parameter key if first for that value, or adds to the existing List under the key
	Dictionary< String^, List< String^ >^ >^ createOrAdd(Dictionary< String^, List< String^ >^ >^ map, String^ key, String^ val)
	{
		if (map->ContainsKey(key))
		{
			List< String^ >^ list;
			if (map->TryGetValue(key, list)) list->Add(val);
		}
		else
		{
			List< String^ >^ newList = gcnew List< String^ >(0);
			newList->Add(val);
			map->Add(key, newList);
		}
		return map;
	}

	//Converts string JSON file into Managed Dictionary
	Dictionary<String^, List<String^ >^ >^ explode(const string& s, Dictionary< String^, List< String^ >^ >^ map)
	{
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
					createOrAdd(map, manageString(key), manageString(buff));
					buff = "";
					if (r == DATA)
					{
						key = "";
						r = KEY;
					}

					continue;
				}
				else if (r = KEY)
				{
					buff += n;
				}
			}
			else if (n == '[') r = LIST;	//Start of list
			else if (n == ']') r = DATA;	//End of list
			else if (r == DATA_TIMESTAMP)	//Special case for timestamp, to allow date to be added as well
			{
				if (n == '-') buff += '/' ;	//replace '-' with '/' for prettiness
				else if (n == '.' || n == 'Z') break; //closing Z and fractional seconds ignored
				else if (n == 'T')			//T character seperates date and time 
				{
					createOrAdd(map, manageString("date"), manageString(buff));
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
	HealthEvent(string s)
	{
		setFromString(s);
	}

	String^ getFirstValue(String^ k)
	{
		try { 
			return getValues(k)->ToArray()[0];
		}
		catch (...) { return "unknown"; }
	}

	List< String^ >^ getValues(String^ k)
	{
			List< String^ >^ vList;
			values->TryGetValue(k, vList);
			return vList;
	}

	void setFromString(string s)
	{
		values = gcnew Dictionary< String^, List< String^ >^ >(0);
		values = explode(s, values);
	}

};
Dictionary< String^, Dictionary< String^, List< HealthEvent^ >^ >^ >^ readFromFolder(string folder, Dictionary<String^, Dictionary< String^, List< HealthEvent^ >^ >^ >^ eventList);

Dictionary< String^, Dictionary< String^, List< HealthEvent^ >^ >^ >^ readFile(string path, Dictionary<String^, Dictionary< String^, List< HealthEvent^ >^ >^ >^ eventList);