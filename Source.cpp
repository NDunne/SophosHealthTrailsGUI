#include "Header.h"

using std::vector;
using std::string;

String^ manageString(std::string in)
{
	return gcnew String(in.c_str());
}

Dictionary< String^, List< HealthEvent^ >^ >^ addHealthEvent(Dictionary< String^, List< HealthEvent^ >^ >^ eventSingle, String^ key, HealthEvent^ h)
{
	List< HealthEvent^ >^ addTo = gcnew List< HealthEvent^ >(0);
	if (eventSingle->TryGetValue(key, addTo)) addTo->Add(h);
	else
	{
		List< HealthEvent^ >^ addTo = gcnew List< HealthEvent^ >(0);
		addTo->Add(h);
		eventSingle->Add(key,addTo);
	}
	return eventSingle;
}

Dictionary<String^, Dictionary< String^, List< HealthEvent^ >^ >^ >^ createAndAdd(Dictionary<String^, Dictionary< String^, List< HealthEvent^ >^ >^ >^ eventList, string userKey, string fileKey, HealthEvent^ h)
{
	Dictionary< String^, List< HealthEvent^ >^ >^ eventSingle = gcnew Dictionary< String^, List< HealthEvent^ >^ >(0);
	if (eventList->TryGetValue(manageString(userKey), eventSingle)) addHealthEvent(eventSingle, h->getFirstValue(manageString(fileKey)), h);
	else
	{
		Dictionary< String^, List< HealthEvent^ >^ >^ eventSingle = gcnew Dictionary< String^, List< HealthEvent^ >^ >(0);
		addHealthEvent(eventSingle, h->getFirstValue(manageString(fileKey)), h);
		eventList->Add(manageString(userKey), eventSingle);
	}
	return eventList;
}

Dictionary<String^, Dictionary< String^, List< HealthEvent^ >^ >^ >^ readFile(string path, Dictionary<String^, Dictionary< String^, List< HealthEvent^ >^ >^ >^ eventList)
{
	if (path.substr(path.length() - 5) == ".json")
	{
		std::ifstream f;
		f.open(path, std::ifstream::in);
		//std::cout << path << "\n";

		if (f.fail())
		{
			std::cout << (f.bad() ? "R/W error" : "Logical error");
		}
	
		std::string s((istreambuf_iterator<char>(f.rdbuf())),istreambuf_iterator<char>());
	
		HealthEvent^ h;
		h = gcnew HealthEvent(s);

		f.close();

		//Could generate these in a more data driven way, fine for now
		createAndAdd(eventList, "ID", "id", h);
		createAndAdd(eventList, "Family ID", "familyId", h);
		createAndAdd(eventList, "Time Stamp", "timeStamp", h);
		createAndAdd(eventList, "App", "app", h);
		createAndAdd(eventList, "Severity", "severity", h);
		createAndAdd(eventList, "Threat Name", "threatName", h);
		createAndAdd(eventList, "Location", "location", h);
		createAndAdd(eventList, "Date", "date", h);
		createAndAdd(eventList, "Service Name", "serviceName", h);
		createAndAdd(eventList, "Resource ID", "resourceId", h);
	
		if (f.is_open()) f.close();
	}

	return eventList;
}

//find all filenames in given filepath
Dictionary<String^, Dictionary< String^, List< HealthEvent^ >^ >^ >^  readFromFolder(string folder, Dictionary<String^, Dictionary< String^, List< HealthEvent^ >^ >^ >^ eventList)
{
	WIN32_FIND_DATA fd;
	std::string search_path = folder + "/*.*";
	HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);

	//Key: data field that value dictionary is indexed by

	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			// read all (real) files in current folder
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				char* filename = fd.cFileName;
				std::string path = folder + "/" + filename; //full path passed to Object creator
				eventList = readFile(path, eventList);
			}
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}

	return eventList;
}

String^ userString(String^ in)
{
	if (in == "id") return "ID";
	else if (in == "familyId") return "Family ID";
	else if (in == "timeStamp") return "Time Stamp";
	else if (in == "app") return "App";
	else if (in == "severity") return "Severity";
	else if (in == "threatName") return "Threat Name";
	else if (in == "location") return "Location";
	else if (in == "date") return "Date";
	else if (in == "serviceName") return "Service Name";
	else if (in == "resourceId") return "Resource ID";
	else return in;
}

String^ fileString(String^ in)
{
	if (in == "ID") return "id";
	else if (in == "Family ID") return "familyId";
	else if (in == "Time Stamp") return "timeStamp";
	else if (in == "App") return "app";
	else if (in == "Severity") return "severity";
	else if (in == "Threat Name") return "threatName";
	else if (in == "Location") return "Location";
	else if (in == "Date") return "date";
	else if (in == "Service Name") return "serviceName";
	else if (in == "Resource ID") return "resourceId";
	else return in;
}
