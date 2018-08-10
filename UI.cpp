#include "UI.h"

using namespace System;
using namespace System::Windows::Forms;

string fancyDate(string date)
{
	int dotCount = 0;
	string buff{ "" };
	for (auto n : date)
	{
		if (n == 'Z') continue;
		else if (n == '-') buff += '/';
		else if (n == 'T') buff += "   ";
		else
		{
			if (n == '.') break;
			buff += n;
		}
	}
	return buff;
}

String^ manageString(std::string in)
{
	return gcnew String(in.c_str());
}

void HealthTrail::UI::refreshData(System::Windows::Forms::TreeView ^ tv1)
{	//Real
	map<string, map<string, vector<HealthEvent*> > > trail = ::readFromFolder("C:/ProgramData/Sophos/Health/Event Store/Trail");

	//Home
	//map<string, map<string, vector<HealthEvent*> > > = ::readFromFolder("C:/Users/Nathan/Desktop/TestJson"); 
	
	//Work
	//map<string, map<string, vector<HealthEvent*> > > trail = ::readFromFolder("C:/Users/nathandunne/Desktop/TestJson");

	tv1->Nodes->Clear();

	cout << "refreshed\n";

	tv1->BeginUpdate();
	
	string sortBy1 = "app";
	string sortBy2 = "timeStamp";

	map<string, vector<HealthEvent*> > selectedTrail = trail[sortBy1];


	for (map< string, vector<HealthEvent*> >::iterator mapIt = selectedTrail.begin(); mapIt != selectedTrail.end(); mapIt++)
	{

		TreeNode^ newNode = gcnew TreeNode(manageString(fancyDate(mapIt->first)));
		tv1->Nodes->Add(newNode);

		vector<HealthEvent*> subNodes = selectedTrail[mapIt->first];

		OutputDebugString(to_string(tv1->Nodes->IndexOf(newNode)).c_str());

		for (vector<HealthEvent*>::iterator vecIt = subNodes.begin(); vecIt != subNodes.end(); vecIt++)
		{
			//tv1->Nodes->Item[tv1->Nodes->IndexOf(newNode)]->Nodes->Add(gcnew TreeNode(manageString((*vecIt)->getFirstValue(sortBy2))));
			newNode->Nodes->Add(gcnew TreeNode(manageString((*vecIt)->getFirstValue(sortBy2))));
		}
	}
	tv1->EndUpdate();
}

[STAThreadAttribute]
int main()
{

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	HealthTrail::UI ui;

	Application::Run(%ui);

	return 0;
}
