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

	Dictionary< String^, List< HealthEvent^ >^ >::Enumerator selectedTrailEnum = selectedTrail->GetEnumerator();
	while (selectedTrailEnum.MoveNext())
	{
		//T1 Node text for the user
		String^ t1text = selectedTrailEnum.Current.Key;

		//Ignore N/A events
		if (t1text == "-") continue;

		//Key of selected trail represents a top level Node in the TreeView
		TreeNode^ t1Node = gcnew TreeNode(t1text);
		t1Node->Name = selectedTrailEnum.Current.Key; //name is the same as Text, for searching
		
		//No need for further tiers if SortBy1 is ID
		if (sortBy1 == "ID")
		{
			t1Node->Tag = selectedTrailEnum.Current.Value->ToArray()[0];
			tv1->Nodes->Add(t1Node);
			continue;
		}
		tv1->Nodes->Add(t1Node);


		//Child nodes are the elements in the value list
		List< HealthEvent^ >^ subNodes = selectedTrailEnum.Current.Value;

		//For each tier 2 value add a Node, and a tier 3 Node (key: id) with the HealthEvent attached
		List< HealthEvent^ >::Enumerator subNodesEnum = subNodes->GetEnumerator();
		while (subNodesEnum.MoveNext())
		{
			//T2 Node text for the user
			String^ t2text = subNodesEnum.Current->getFirstValue(sortBy2);

			//Ignore N/A Events - NB: this can lead to empty T1 nodes --TODO--
			if (t2text == "-") continue;
			

			TreeNode^ t2Node;
			//If SortBy2 is "id" no need for 3 tiers
			if (sortBy2 != "id" && t1Node->Nodes->ContainsKey(t2text))
			{
				//Get existing T2 Node for this key value
				t2Node = t1Node->Nodes->Find(t2text, false)[0];
			}
			else
			{
				//Create T2 Node for this key value
				t2Node = gcnew TreeNode(t2text);
				t2Node->Name = t2text;
				if (sortBy2 == "id")
				{
					//Attach healthEvent if Node is leaf (Key: id only)
					t2Node->Tag = subNodesEnum.Current;
					t1Node->Nodes->Add(t2Node);
					continue;
				}

				t1Node->Nodes->Add(t2Node);
			}
			
			//Create T3 Node and attach HealthEvent. If key is "id" this is unreachable
			TreeNode^ t3Node = gcnew TreeNode(subNodesEnum.Current->getFirstValue("id"));
			t3Node->Name = t3Node->Text;
			t3Node->Tag = subNodesEnum.Current;
			t2Node->Nodes->Add(t3Node);
		}
	}
	//Sort Tree alphanumeric (case insensitive)
	tv1->Sort();

	//Redraw
	tv1->EndUpdate();
}

void HealthTrail::UI::refreshData(System::Windows::Forms::TreeView^ tv1, System::String^ sb1, System::String^ sb2, Dictionary<String^, Dictionary< String^, List< HealthEvent^ >^ >^ >^ trail)
{	
	//Get Data
	trail = readFromFolder(UI::path, trail);

	//Add to TreeView
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

	if (cmd != "") path = cmd; //Use parameter path if it exists, otherwise default to local machine

	if (path->EndsWith("sdulog"))
	{
		path += "/ProgramData/Sophos/Health/Event Store/Trail"; //Allow path to be sdulog root
	}

	HealthTrail::UI ui(path);

	Application::Run(%ui);
	
	return 0;
}
