#pragma once
#include "Header.h"
#include "Sorter.h"

using namespace std;


namespace HealthTrail {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	
	/// <summary>
	/// Main Body UI form
	/// </summary>
	public ref class UI : public System::Windows::Forms::Form
	{
	public:
		//Load Data from file into 'trail' Dictionary
		void refreshData(System::Windows::Forms::TreeView^ tv1, System::String^ sb1, System::String^ sb2, Dictionary<String^, Dictionary< String^, List< HealthEvent^ >^ >^ >^ trail);

		//Applys new groupings from drop down menus, re-allocates treeview Nodes. Does not re-read from file
		void sortItems(System::Windows::Forms::TreeView ^ tv1, System::String^ sb1, System::String^ sb2, Dictionary<String^, Dictionary< String^, List< HealthEvent^ >^ >^ >^ trail);

		UI(void)
		{
			InitializeComponent();

			Dictionary<String^, Dictionary< String^, List< HealthEvent^ >^ >^ >^ trail();

			//Initial data read
			refreshData(this->treeView1, "App", "id", this->trail);
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~UI()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  refreshToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem;

	private: System::Windows::Forms::ToolStripMenuItem^  configToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  helpToolStripMenuItem;

	private: System::Windows::Forms::SplitContainer^  splitContainer1;
	public: System::Windows::Forms::TreeView^  treeView1;
	//private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::WebBrowser^  webBrowser1;

	private: System::Windows::Forms::Button^  Submit;
	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: System::Windows::Forms::ComboBox^  comboBox2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;

	protected:

	private:
		Dictionary<String^, Dictionary< String^, List< HealthEvent^ >^ >^ >^ trail;

		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			trail = gcnew Dictionary<String^, Dictionary< String^, List< HealthEvent^ >^ >^ >(0);

			Int32 scrHeight = GetSystemMetrics(SM_CYSCREEN);

			Int32 treeWidth = 7 * scrHeight / 24;
			Int32 browserWidth = scrHeight / 3;

			Int32 winWidth = treeWidth + browserWidth;
			Int32 winHeight = scrHeight / 2;

			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->refreshToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->configToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->helpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->splitContainer1 = (gcnew System::Windows::Forms::SplitContainer());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->Submit = (gcnew System::Windows::Forms::Button());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox2 = (gcnew System::Windows::Forms::ComboBox());
			//this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->treeView1 = (gcnew System::Windows::Forms::TreeView());
			this->webBrowser1 = (gcnew System::Windows::Forms::WebBrowser());
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->BeginInit();
			this->splitContainer1->Panel1->SuspendLayout();
			this->splitContainer1->Panel2->SuspendLayout();
			this->splitContainer1->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->fileToolStripMenuItem,
					this->configToolStripMenuItem, this->helpToolStripMenuItem
			});

			Int32 menuHeight = winHeight / 25;

			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(winWidth, menuHeight);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->refreshToolStripMenuItem,
				this->exitToolStripMenuItem
			});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(40, menuHeight);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// refreshToolStripMenuItem
			// 
			this->refreshToolStripMenuItem->Name = L"refreshToolStripMenuItem";
			this->refreshToolStripMenuItem->Size = System::Drawing::Size(100, menuHeight);
			this->refreshToolStripMenuItem->Text = L"Refresh";
			this->refreshToolStripMenuItem->Click += gcnew System::EventHandler(this, &UI::refreshMenuItem_Click);
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			this->exitToolStripMenuItem->Size = System::Drawing::Size(100, menuHeight);
			this->exitToolStripMenuItem->Text = L"Exit";
			// 
			// configToolStripMenuItem
			// 
			this->configToolStripMenuItem->Name = L"configToolStripMenuItem";
			this->configToolStripMenuItem->Size = System::Drawing::Size(40, menuHeight);
			this->configToolStripMenuItem->Text = L"Config";
			// 
			// helpToolStripMenuItem
			// 
			this->helpToolStripMenuItem->Name = L"helpToolStripMenuItem";
			this->helpToolStripMenuItem->Size = System::Drawing::Size(40, menuHeight);
			this->helpToolStripMenuItem->Text = L"Help";
			// 
			// splitContainer1
			// 
			this->splitContainer1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer1->Location = System::Drawing::Point(0, menuHeight);
			this->splitContainer1->Name = L"splitContainer1";
			// 
			// splitContainer1.Panel1
			// 
			this->splitContainer1->Panel1->Controls->Add(this->comboBox1);
			this->splitContainer1->Panel1->Controls->Add(this->comboBox2);
			this->splitContainer1->Panel1->Controls->Add(this->label1);
			this->splitContainer1->Panel1->Controls->Add(this->label2);
			this->splitContainer1->Panel1->Controls->Add(this->Submit);
			//this->splitContainer1->Panel1->Controls->Add(this->textBox1);
			this->splitContainer1->Panel1->Controls->Add(this->treeView1);
			// 
			// splitContainer1.Panel2
			// 
			this->splitContainer1->Panel2->Controls->Add(this->webBrowser1);
			this->splitContainer1->Size = System::Drawing::Size(winWidth, winHeight);
			this->splitContainer1->SplitterDistance = treeWidth;
			this->splitContainer1->TabIndex = 1;
			// 
			// label1
			// 

			Int32 font120 = scrHeight / 120;
			this->label1->Font = (gcnew System::Drawing::Font(L"Consolas", font120));
			this->label1->Location = System::Drawing::Point(0, 0);
			this->label1->Margin = System::Windows::Forms::Padding(0);
			this->label1->Name = L"label1";
			this->label1->AutoSize = false;
			this->label1->Size = System::Drawing::Size(treeWidth/4, menuHeight);
			this->label1->TabIndex = 8;
			this->label1->Text = L"Group By:";
			this->label1->TextAlign = ContentAlignment::MiddleRight;
			// 
			// label2
			// 
			this->label2->Font = (gcnew System::Drawing::Font(L"Consolas", font120));
			this->label2->Location = System::Drawing::Point(treeWidth/2, 0);
			this->label2->Margin = System::Windows::Forms::Padding(0);
			this->label2->Name = L"label2";
			this->label2->AutoSize = false;
			this->label2->Size = System::Drawing::Size(treeWidth/8, menuHeight);
			this->label2->TabIndex = 9;
			this->label2->Text = L"Then:";
			this->label2->TextAlign = ContentAlignment::MiddleRight;
			// 
			// Submit
			// 
			this->Submit->Location = System::Drawing::Point(7*treeWidth/8, 0);
			this->Submit->Margin = System::Windows::Forms::Padding(0);
			this->Submit->Name = L"Submit";
			this->Submit->Size = System::Drawing::Size(treeWidth/8, menuHeight);
			this->Submit->TabIndex = 7;
			this->Submit->UseVisualStyleBackColor = true;
			this->Submit->Text = "Go";
			this->Submit->Click += gcnew System::EventHandler(this, &UI::GroupButtonClick);
			// 
			// comboBox1
			// 
			this->comboBox1->Font = (gcnew System::Drawing::Font(L"Consolas", font120));
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(10) {
				L"ID", L"Family ID", L"App", L"Date", L"Location",
					L"Severity", L"Service Name", L"Resource ID", L"Threat Name", L"Time Stamp"
			});
			this->comboBox1->Location = System::Drawing::Point(treeWidth/4, 0);
			this->comboBox1->Margin = System::Windows::Forms::Padding(0);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(treeWidth / 4, menuHeight);
			this->comboBox1->TabIndex = 5;
			this->comboBox1->SelectedIndex = 2; //App
			// 
			// comboBox2
			// 
			this->comboBox2->Font = (gcnew System::Drawing::Font(L"Consolas", font120));
			this->comboBox2->FormattingEnabled = true;
			this->comboBox2->Items->AddRange(gcnew cli::array< System::Object^  >(10) {
				L"ID", L"Family ID", L"App", L"Date", L"Location",
					L"Severity",L"Service Name",L"Resource ID",L"Threat Name",L"Time Stamp"
			});
			this->comboBox2->Location = System::Drawing::Point(5*treeWidth/8, 0);
			this->comboBox2->Margin = System::Windows::Forms::Padding(0);
			this->comboBox2->Name = L"comboBox2";
			this->comboBox2->Size = System::Drawing::Size(treeWidth / 4, menuHeight);
			this->comboBox2->TabIndex = 6;
			this->comboBox2->SelectedIndex = 0; //ID
			// 
			// textBox1
			// 
			/*this->textBox1->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->textBox1->Location = System::Drawing::Point(0, 455);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(450, 20);
			this->textBox1->TabIndex = 1;*/
			// 
			// treeView1
			// 
			Int32 font100 = scrHeight / 100;
			this->treeView1->Font = (gcnew System::Drawing::Font(L"Consolas", font100, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->treeView1->HotTracking = true;
			//this->treeView1->Dock = System::Windows::Forms::DockStyle::Right;
			this->treeView1->Location = System::Drawing::Point(0, menuHeight);
			this->treeView1->Margin = System::Windows::Forms::Padding(0);
			this->treeView1->Name = L"treeView1";
			this->treeView1->Size = System::Drawing::Size(treeWidth, winHeight-menuHeight);
			this->treeView1->TabIndex = 0;
			this->treeView1->AfterSelect += gcnew TreeViewEventHandler(this, &UI::treeView1_AfterSelect);
			// 
			// webBrowser1
			// 
			this->webBrowser1->Dock = System::Windows::Forms::DockStyle::Left;
			this->webBrowser1->Location = System::Drawing::Point(0, menuHeight);
			this->webBrowser1->MinimumSize = System::Drawing::Size(20, 20);
			this->webBrowser1->Name = L"webBrowser1";
			this->webBrowser1->Size = System::Drawing::Size(browserWidth, winHeight);
			this->webBrowser1->TabIndex = 0;
			// 
			// UI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(5, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(winWidth, winHeight);
			this->Controls->Add(this->splitContainer1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"UI";
			this->Text = L"SophosHealth Trails" + scrHeight;
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->splitContainer1->Panel1->ResumeLayout(false);
			this->splitContainer1->Panel1->PerformLayout();
			this->splitContainer1->Panel2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->EndInit();
			this->splitContainer1->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
		#pragma endregion

		//Event Handler for Grouping button - resorts Nodes without re-reading files
		private: System::Void GroupButtonClick(Object^ sender, EventArgs^ e) {
			sortItems(this->treeView1, this->comboBox1->SelectedItem->ToString(), HealthEvent::getFileString(this->comboBox2->SelectedItem->ToString()), this->trail);
		}

		//Re-reads files to add any new events
		private: System::Void refreshMenuItem_Click(Object^ sender, EventArgs^ e) {
			refreshData(this->treeView1, this->comboBox1->SelectedItem->ToString(), HealthEvent::getFileString(this->comboBox2->SelectedItem->ToString()), this->trail);
		}

		//TreeNode Event Handler
		private: System::Void treeView1_AfterSelect(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e) {
			try
			{
				HealthEvent^ attached = (HealthEvent^)((TreeView^)sender)->SelectedNode->Tag;
				this->webBrowser1->DocumentText = attached->toHTML();
			}
			catch (...) {}
		}
};
}
