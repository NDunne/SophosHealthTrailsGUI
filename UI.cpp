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
{
	//::Cursor::Current = gcnew System::Windows::Forms::Cursor("MyWait.cur");

	//Real
	vector<HealthEvent*> trail = ::readFromFolder("C:/ProgramData/Sophos/Health/Event Store/Trail");

	//Home
	/*vector<HealthEvent*> trail = ::readFromFolder("C:/Users/Nathan/Desktop/TestJson");*/ 
	
	//Work
	//vector<HealthEvent*> trail = ::readFromFolder("C:/Users/nathandunne/Desktop/TestJson");

	cout << "refreshed\n";

	tv1->BeginUpdate();

	trail = MergeSort(trail, "timeStamp");

	for (std::vector<HealthEvent*>::iterator it = trail.begin(); it != trail.end(); it++)
	{

		TreeNode^ newNode = gcnew TreeNode(manageString(fancyDate((*it)->getFirstValue("timeStamp"))));

		tv1->Nodes->Add(newNode);

	}
	tv1->EndUpdate();
	/*::Cursor::Current = Cursors::Default;*/
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
