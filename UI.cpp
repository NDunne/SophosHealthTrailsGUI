#include "UI.h"
#include <msclr\marshal_cppstd.h>

using namespace System;
using namespace System::Windows::Forms;

String^ manageString(std::string in)
{
	return gcnew String(in.c_str());
}

void HealthTrail::UI::sortItems(System::Windows::Forms::TreeView ^ tv1, System::String^ sb1, System::String^ sb2, map<string, map<string, vector<HealthEvent*> > > trail)
{
	tv1->Nodes->Clear();

	cout << "refreshed\n";

	tv1->BeginUpdate();

	std::string sortBy1 = msclr::interop::marshal_as< std::string >(sb1);
	std::string sortBy2 = msclr::interop::marshal_as< std::string >(sb2); //Managed String to std::string

	map<string, vector<HealthEvent*> > selectedTrail = trail[sortBy1];


	for (map< string, vector<HealthEvent*> >::iterator mapIt = selectedTrail.begin(); mapIt != selectedTrail.end(); mapIt++)
	{

		TreeNode^ newNode = gcnew TreeNode(manageString(mapIt->first));
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

void HealthTrail::UI::refreshData(System::Windows::Forms::TreeView^ tv1, System::String^ sb1, System::String^ sb2)
{	
	//Real
	map<string, map<string, vector<HealthEvent*> > > trail = ::readFromFolder("C:/ProgramData/Sophos/Health/Event Store/Trail");

	//Home
	//map<string, map<string, vector<HealthEvent*> > > = ::readFromFolder("C:/Users/Nathan/Desktop/TestJson"); 
	
	//Work
	//map<string, map<string, vector<HealthEvent*> > > trail = ::readFromFolder("C:/Users/nathandunne/Desktop/TestJson");

	sortItems(tv1, sb1, sb2, trail);
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
