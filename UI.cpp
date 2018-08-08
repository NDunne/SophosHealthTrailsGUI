#include "UI.h"

using namespace System;
using namespace System::Windows::Forms;

string fancyDate(string date)
{

}

String^ convert(string in)
{
	return gcnew String(in.c_str());
}

void HealthTrail::UI::refreshData(System::Windows::Forms::TreeView ^ tv1)
{
	//::Cursor::Current = gcnew System::Windows::Forms::Cursor("MyWait.cur");
	
	vector<HealthEvent*> trail = ::readFromFolder("C:/Users/Nathan/Desktop/TestJson");
	
	cout << "refreshed\n";
	
	tv1->BeginUpdate();
	for (std::vector<HealthEvent*>::iterator it = trail.begin(); it != trail.end(); it++)
	{

		TreeNode^ newNode = gcnew TreeNode(convert((*it)->getFirstValue("timeStamp")) + " - " + convert((*it)->getFirstValue("app")));

		tv1->Nodes->Add(newNode);

		cout << "added\n";
	}
	tv1->EndUpdate();

	cout << "Finished\n";
	/*::Cursor::Current = Cursors::Default;*/
}

[STAThread]
void main()
{
	cout << "Main\n";

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	HealthTrail::UI form;
		
	cout << "Running\n";

	Application::Run(%form);
	
	
}