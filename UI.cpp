#include "UI.h"
#include <msclr\marshal_cppstd.h>

using namespace System;
using namespace System::Windows::Forms;

//Reloads TreeView with new grouping
void HealthTrail::UI::sortItems(System::Windows::Forms::TreeView ^ tv1, System::String^ sortBy1, System::String^ sortBy2, Dictionary<String^, Dictionary< String^, List< HealthEvent^ >^ >^ >^ trail)
{
	//remove exisiting nodes
	tv1->Nodes->Clear();

	//Prevent redrawing
	tv1->BeginUpdate();

	//Selected Trail maps Strings : HealthEvent Lists where the key in the selected trail is the attribute SortBy1
	Dictionary< String^, List< HealthEvent^ >^ >^ selectedTrail = gcnew Dictionary< String^, List< HealthEvent^ >^ >(0);
	if (!trail->TryGetValue(sortBy1, selectedTrail)) return;	//If Dictionary using SortBy1 as a key does not exist, return
	
	//Iterate over Dictionary
	Dictionary< String^, List< HealthEvent^ >^ >::Enumerator selectedTrailEnum = selectedTrail->GetEnumerator();
	while (selectedTrailEnum.MoveNext())
	{
		String^ t1text = selectedTrailEnum.Current.Key;

		if (t1text == "-") continue;

		//Key of selected trail represents a top level Node in the TreeView
		TreeNode^ t1Node = gcnew TreeNode(t1text);
		t1Node->Name = selectedTrailEnum.Current.Key; //name is the same as Text, for searching
		tv1->Nodes->Add(t1Node);


		//Child nodes are the elements in the value list
		List< HealthEvent^ >^ subNodes = selectedTrailEnum.Current.Value;
		//subNodes = MergeSort(subNodes, sortBy2, (sortBy2 == "timeStamp" || sortBy2 == "date")); //inverse alphabetical for dates

		//Iterate subnode list
		List< HealthEvent^ >::Enumerator subNodesEnum = subNodes->GetEnumerator();

		while (subNodesEnum.MoveNext())
		{
			String^ t2text = subNodesEnum.Current->getFirstValue(sortBy2);

			if (t2text == "-") continue;

			//If tier2 nodes share a sortBy2 attribute, a third tier is created using ID, so must be unique.
			if (t1Node->Nodes->ContainsKey(t2text))
			{
				TreeNode^ t2Node = t1Node->Nodes->Find(t2text, false)[0];
				if (!(t2Node->Nodes->GetEnumerator()->MoveNext())) //No children yet
				{
					//All tier 2 nodes of the parent are pushed down into a third tier for consistency
					auto ienum = t2Node->Parent->Nodes->GetEnumerator();
					while (ienum->MoveNext())
					{
						try
						{
							//tier 2 node becomes empty parent, with child containing its old value
							HealthEvent^ h = (HealthEvent^)((TreeNode^)ienum->Current)->Tag;
							TreeNode^ pushDown = gcnew TreeNode(h->getFirstValue(manageString("id")));
							pushDown->Tag = ((TreeNode^)ienum->Current)->Tag;
							((TreeNode^)ienum->Current)->Nodes->Add(pushDown);
							((TreeNode^)ienum->Current)->Tag = nullptr;
						}
						catch (...) {}
					}
				}
				//If the tier2 node already has a child, the new one can be added to the TreeNodeCollection
				TreeNode^ t3Node = gcnew TreeNode(subNodesEnum.Current->getFirstValue("id"));
				t3Node->Name = t3Node->Text;
				t3Node->Tag = subNodesEnum.Current;
				t2Node->Nodes->Add(t3Node);
			}
			else //New Tier2 Node
			{
				TreeNode^ t2Node = gcnew TreeNode(t2text);
				t2Node->Name = t2text;
				t2Node->Tag = subNodesEnum.Current;
				t1Node->Nodes->Add(t2Node);
			}
		}
	}
	tv1->EndUpdate();
	//Redraw
}

void HealthTrail::UI::refreshData(System::Windows::Forms::TreeView^ tv1, System::String^ sb1, System::String^ sb2, Dictionary<String^, Dictionary< String^, List< HealthEvent^ >^ >^ >^ trail)
{	
	trail = readFromFolder(UI::path, trail);

	sortItems(tv1, sb1, sb2, trail);
}

[STAThreadAttribute()]
int CALLBACK WinMain(
	_In_ HINSTANCE hInstance,
	_In_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow
)
{
	HealthEvent::initDicts(); //Create Conversion table maps

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);


	String^ cmd = manageString(lpCmdLine);
	String^ path = "C:/ProgramData/Sophos/Health/Event Store/Trail";

	if (cmd != "") path = cmd;

	if (path->EndsWith("sdulog"))
	{
		path += "/ProgramData/Sophos/Health/Event Store/Trail";
	}

	HealthTrail::UI ui(path);

	Application::Run(%ui);
	
	return 0;
}
