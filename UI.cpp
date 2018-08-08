#include "UI.h"

using namespace System;
using namespace System::Windows::Forms;


void HealthTrail::UI::refreshData(System::Windows::Forms::TreeView ^ tv1)
{
	//::Cursor::Current = gcnew System::Windows::Forms::Cursor("MyWait.cur");
	
	vector<HealthEvent*> trail = ::readFromFolder("C:/Users/nathandunne/Desktop/TestJson");
	
	cout << "refreshed";

	for (std::vector<HealthEvent*>::iterator it = trail.begin(); it != trail.end(); it++)
	{
		TreeNode^ newNode = gcnew TreeNode(gcnew String((*it)->getFirstValue("timeStamp").c_str()));

		tv1->BeginUpdate();
		tv1->Nodes->Add(newNode);
		tv1->EndUpdate();
		cout << "added";
	}
	/*::Cursor::Current = Cursors::Default;*/
}

void main()
{
	std::cout << "HELLO W.";

	std::string test = "";

	//cout << "Main";

	//Application::EnableVisualStyles();
	//Application::SetCompatibleTextRenderingDefault(false);

	//HealthTrail::UI form;
	//	
	//cout << "Running";

	//Application::Run(%form);
	//
	//
}