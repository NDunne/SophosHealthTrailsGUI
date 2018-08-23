//TODO
// - Parent nodes display table
// - Child nodes prettier
// - Same number of levels for all nodes

#include "Header.h"

using std::vector;
using std::string;

//Helper function for frequently required conversion
String^ manageString(std::string in)
{
	return gcnew String(in.c_str());
}

//Add a given health event to its key in the Dictionary if the key exists. If not, create the key
Dictionary< String^, List< HealthEvent^ >^ >^ addHealthEvent(Dictionary< String^, List< HealthEvent^ >^ >^ eventSingle, String^ key, HealthEvent^ h)
{
	//Key here is the value of the attribute this Dictionary is mapped on
	//Value is a list of Health Events with the same value for this attribute

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

//Add a health event to the right Dictionary of String : HealthEvent List based on which attribute it is stored by. Add if doesn't exist already
Dictionary<String^, Dictionary< String^, List< HealthEvent^ >^ >^ >^ createAndAdd(Dictionary<String^, Dictionary< String^, List< HealthEvent^ >^ >^ >^ eventList, String^ userKey, String^ fileKey, HealthEvent^ h)
{
	//Key here is the User Formated attribute name that the value is indexing by
	//Value is a dictionary mapping attriubute values for the attribute in the key to a List of HealthEvents sharing that value

	Dictionary< String^, List< HealthEvent^ >^ >^ eventSingle = gcnew Dictionary< String^, List< HealthEvent^ >^ >(0);
	if (eventList->TryGetValue(userKey, eventSingle)) addHealthEvent(eventSingle, h->getFirstValue(fileKey), h);
	else
	{
		Dictionary< String^, List< HealthEvent^ >^ >^ eventSingle = gcnew Dictionary< String^, List< HealthEvent^ >^ >(0);
		addHealthEvent(eventSingle, h->getFirstValue(fileKey), h);
		eventList->Add(userKey, eventSingle);
	}
	return eventList;
}

//Read in a JSON file and update the master Dictionary
Dictionary<String^, Dictionary< String^, List< HealthEvent^ >^ >^ >^ readFile(string path, Dictionary<String^, Dictionary< String^, List< HealthEvent^ >^ >^ >^ eventList)
{
	//ignore non json files
	if (path.substr(path.length() - 5) == ".json")
	{
		std::ifstream f;
		f.open(path, std::ifstream::in);

		if (f.fail())
		{
			std::cout << (f.bad() ? "R/W error" : "Logical error");
		}
		else
		{
			std::string s((std::istreambuf_iterator<char>(f.rdbuf())), std::istreambuf_iterator<char>());

			HealthEvent^ h;
			h = gcnew HealthEvent(s);

			f.close();

			//Same HealthEvent pointer is stored multiple times to allow quicker re-sorting

			List < String^ >::Enumerator keys = HealthEvent::sortableAttributes()->GetEnumerator();
			while (keys.MoveNext())
			{
				String^ k = keys.Current;
				createAndAdd(eventList, k, HealthEvent::getFileString(k), h);
			}
		}

		if (f.is_open()) f.close();
	}

	return eventList;
}

//find all filenames in given filepath
Dictionary<String^, Dictionary< String^, List< HealthEvent^ >^ >^ >^  readFromFolder(String^ folder, Dictionary<String^, Dictionary< String^, List< HealthEvent^ >^ >^ >^ eventList)
{
	WIN32_FIND_DATA fd;
	String^ search_path = folder + "/*.*";
	HANDLE hFind = ::FindFirstFile(msclr::interop::marshal_as<std::string>(search_path).c_str(), &fd);

	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			// read all (real) files in current folder
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				char* filename = fd.cFileName;
				string path = msclr::interop::marshal_as<std::string>(folder) + "/" + filename; //full path passed to Object creator
				eventList = readFile(path, eventList); //JSON data from file added to eventList Dictionary
			}
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}

	return eventList;
}