#include "Header.h"

using std::vector;
using std::string;

HealthEvent* createFromString(std::string s)
{	
		return (new HealthEvent(s));
}

vector<HealthEvent*> readFile(std::string path, vector<HealthEvent*> eventList)
{
	std::ifstream f;
	f.open(path, std::ifstream::in);
	//std::cout << path << "\n";

	if (f.fail())
	{
		std::cout << (f.bad() ? "R/W error" : "Logical error");
	}

	std::string s((istreambuf_iterator<char>(f.rdbuf())),istreambuf_iterator<char>());
	if (path.substr(path.length() - 5) == ".json")
		eventList.push_back(createFromString(s));

	f.close();

	return eventList;
}

//find all filenames in given filepath
vector<HealthEvent*> readFromFolder(string folder)
{
	WIN32_FIND_DATA fd;
	std::string search_path = folder + "/*.*";
	HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);

	vector<HealthEvent*> eventList;
	
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