#include "UI.h"
#include <msclr\marshal_cppstd.h>

using namespace System;
using namespace System::Windows::Forms;

void HealthTrail::UI::sortItems(System::Windows::Forms::TreeView ^ tv1, System::String^ sortBy1, System::String^ sortBy2, Dictionary<String^, Dictionary< String^, List< HealthEvent^ >^ >^ >^ trail)
{
	tv1->Nodes->Clear();

	cout << "refreshed\n";

	tv1->BeginUpdate();

	Dictionary< String^, List< HealthEvent^ >^ >^ selectedTrail = gcnew Dictionary< String^, List< HealthEvent^ >^ >(0);
	if (!trail->TryGetValue(sortBy1, selectedTrail)) return;	
	
	Dictionary< String^, List< HealthEvent^ >^ >::Enumerator selectedTrailEnum = selectedTrail->GetEnumerator();
	while (selectedTrailEnum.MoveNext())
	{

		TreeNode^ t1Node = gcnew TreeNode(selectedTrailEnum.Current.Key);
		t1Node->Name = selectedTrailEnum.Current.Key;
		tv1->Nodes->Add(t1Node);



		List< HealthEvent^ >^ subNodes = selectedTrailEnum.Current.Value;
		subNodes = MergeSort(subNodes, sortBy2, (sortBy2 == "timeStamp" || sortBy2 == "date")); //inverse alphabetical for dates
		
		List< HealthEvent^ >::Enumerator subNodesEnum = subNodes->GetEnumerator();

		while (subNodesEnum.MoveNext())
		{
			String^ t2text = subNodesEnum.Current->getFirstValue(sortBy2);

			if (t1Node->Nodes->ContainsKey(t2text))
			{
				TreeNode^ t2Node = t1Node->Nodes->Find(t2text, false)[0];
				if (!(t2Node->Nodes->GetEnumerator()->MoveNext())) //No children yet
				{
					auto ienum = t2Node->Parent->Nodes->GetEnumerator();
					while (ienum->MoveNext())
					{
						try
						{
							HealthEvent^ h = (HealthEvent^)((TreeNode^)ienum->Current)->Tag;
							TreeNode^ pushDown = gcnew TreeNode(h->getFirstValue(manageString("id")));
							((TreeNode^)ienum->Current)->Nodes->Add(pushDown);
							((TreeNode^)ienum->Current)->Tag = nullptr;
						}
						catch (...) {}
					}
				}
				TreeNode^ t3Node = gcnew TreeNode(subNodesEnum.Current->getFirstValue("id"));
				t3Node->Name = t3Node->Text;
				t3Node->Tag = subNodesEnum.Current;
				t2Node->Nodes->Add(t3Node);
			}
			else
			{
				TreeNode^ t2Node = gcnew TreeNode(t2text);
				t2Node->Name = t2text;
				t2Node->Tag = subNodesEnum.Current;
				t1Node->Nodes->Add(t2Node);
			}
		}
	}
	tv1->EndUpdate();
}

void HealthTrail::UI::refreshData(System::Windows::Forms::TreeView^ tv1, System::String^ sb1, System::String^ sb2, Dictionary<String^, Dictionary< String^, List< HealthEvent^ >^ >^ >^ trail)
{	
	//Real
	trail = readFromFolder("C:/ProgramData/Sophos/Health/Event Store/Trail", trail);

	//Home
	//trail = ::readFromFolder("C:/Users/Nathan/Desktop/TestJson", trail); 
	
	//Work
	//trail = ::readFromFolder("C:/Users/nathandunne/Desktop/TestJson", trail);

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
