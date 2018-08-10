#include "Header.h"

using std::vector;
using std::string;

map<string, map<string, vector<HealthEvent*> > > readFile(std::string path, map<string, map<string, vector<HealthEvent*> > > eventList)
{
	std::ifstream f;
	f.open(path, std::ifstream::in);
	//std::cout << path << "\n";

	if (f.fail())
	{
		std::cout << (f.bad() ? "R/W error" : "Logical error");
	}

	std::string s((istreambuf_iterator<char>(f.rdbuf())),istreambuf_iterator<char>());
	
	HealthEvent* h;

	if (path.substr(path.length() - 5) == ".json")
	{
		h = new HealthEvent(s);

		f.close();

		eventList["id"][h->getFirstValue("id")].push_back(h);
		eventList["familyId"][h->getFirstValue("familyId")].push_back(h);
		eventList["timeStamp"][h->getFirstValue("timeStamp")].push_back(h);
		eventList["app"][h->getFirstValue("app")].push_back(h);
		eventList["severity"][h->getFirstValue("severity")].push_back(h);
		eventList["threatName"][h->getFirstValue("threatName")].push_back(h);
		eventList["location"][h->getFirstValue("location")].push_back(h);
	}

	if (f.is_open()) f.close();

	return eventList;
}

//find all filenames in given filepath
map<string, map<string, vector<HealthEvent*> > > readFromFolder(string folder)
{
	WIN32_FIND_DATA fd;
	std::string search_path = folder + "/*.*";
	HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);

	map<string, map<string, vector<HealthEvent*> > > eventList;
	//event list is a map key hashField as a string, value a map of that value to HealthEvent objects.
	//Each HealthEvent is stored multiple times by each field a user might want to order by.

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
