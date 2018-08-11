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

class HealthEvent
{
private:
	map<string, vector<string> > values;

	map<string, vector<string> > explode(const string& s)
	{
		string buff{ "" };
		string key{ "" };

		enum readingState { KEY, DATA, DATA_TIMESTAMP, LIST };
		readingState r = KEY;
		map<string, vector<string> > m;

		for (auto n : s)
		{
			if (n == '{' || n == '}' || n == '"') continue;

			if (n == ':' && r == KEY)
			{
					r = DATA;
					key = buff;
					if (key == "timeStamp") r = DATA_TIMESTAMP;
					buff = "";
					continue;
			}
			else if (n == ',' )
			{
				if (r == DATA || r == DATA_TIMESTAMP || r == LIST)
				{
					m[key].push_back(buff);
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
			else if (n == '[') r = LIST;
			else if (n == ']') r = DATA;
			else if (r == DATA_TIMESTAMP)
			{
				if (n == '-') buff += '/' ;
				else if (n == '.' || n == 'Z') break;
				else if (n == 'T')
				{
					m["date"].push_back(buff);
				}
				else buff += n;
			}
			else
			{
				buff += n;
			}
		}
		if (buff != "") m[key].push_back(buff);
		return m;
	}

public:
	HealthEvent(string s)
	{
		setFromString(s);
	}

	string getFirstValue(string k) const
	{
		try { return values.at(k)[0]; }
		catch (...) { return "Unknown"; }
	}

	vector<string> getValues(string k)
	{
		return values[k];
	}

	void setFromString(string s)
	{
		values = explode(s);

		for (map<string, vector<string> >::iterator mapIt = values.begin(); mapIt != values.end(); mapIt++)
		{
			string k = mapIt->first;
			vector<string> v = mapIt->second;
			/*cout << "\n" << k << ": ";
			for (vector<string>::iterator vecIt = v.begin(); vecIt != v.end(); vecIt++)
			{
				cout << "   " << *vecIt << "\n";
			}*/
		}
		//cout << "\n";
	}

};
map<string, map<string, vector<HealthEvent*> > > readFromFolder(string folder);

map<string, map<string, vector<HealthEvent*> > > readFile(std::string path, map<string, map<string, vector<HealthEvent*> > > eventList);