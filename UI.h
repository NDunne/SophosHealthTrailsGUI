#pragma once
#include "Header.h"
#include "Sorter.h"
#include "resource.h"

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

		void refreshData(System::Windows::Forms::TreeView^ tv1);

		UI(void)
		{
			InitializeComponent();

			refreshData(this->treeView1);
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
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::WebBrowser^  webBrowser1;

	private: System::Windows::Forms::Button^  Submit;
	private: System::Windows::Forms::ComboBox^  comboBox3;
	private: System::Windows::Forms::ComboBox^  comboBox2;
	private: System::Windows::Forms::ComboBox^  comboBox1;

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->refreshToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->configToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->helpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->splitContainer1 = (gcnew System::Windows::Forms::SplitContainer());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->treeView1 = (gcnew System::Windows::Forms::TreeView());
			this->webBrowser1 = (gcnew System::Windows::Forms::WebBrowser());
			this->comboBox3 = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox2 = (gcnew System::Windows::Forms::ComboBox());
			this->Submit = (gcnew System::Windows::Forms::Button());
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
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1070, 24);
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
			this->fileToolStripMenuItem->Size = System::Drawing::Size(37, 20);
			this->fileToolStripMenuItem->Text = L"File";
			//
			// refreshToolStripMenuItem
			//
			this->refreshToolStripMenuItem->Name = L"refreshToolStripMenuItem";
			this->refreshToolStripMenuItem->Size = System::Drawing::Size(113, 22);
			this->refreshToolStripMenuItem->Text = L"Refresh";
			this->refreshToolStripMenuItem->Click += gcnew System::EventHandler(this, &UI::refreshMenuItem_Click);
			//
			// exitToolStripMenuItem
			//
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			this->exitToolStripMenuItem->Size = System::Drawing::Size(113, 22);
			this->exitToolStripMenuItem->Text = L"Exit";
			//
			// configToolStripMenuItem
			//
			this->configToolStripMenuItem->Name = L"configToolStripMenuItem";
			this->configToolStripMenuItem->Size = System::Drawing::Size(55, 20);
			this->configToolStripMenuItem->Text = L"Config";
			//
			// helpToolStripMenuItem
			//
			this->helpToolStripMenuItem->Name = L"helpToolStripMenuItem";
			this->helpToolStripMenuItem->Size = System::Drawing::Size(44, 20);
			this->helpToolStripMenuItem->Text = L"Help";
			//
			// splitContainer1
			//
			this->splitContainer1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer1->Location = System::Drawing::Point(0, 24);
			this->splitContainer1->Name = L"splitContainer1";
			//
			// splitContainer1.Panel1
			//
			this->splitContainer1->Panel1->Controls->Add(this->Submit);
			this->splitContainer1->Panel1->Controls->Add(this->comboBox2);
			this->splitContainer1->Panel1->Controls->Add(this->comboBox1);
			this->splitContainer1->Panel1->Controls->Add(this->comboBox3);
			this->splitContainer1->Panel1->Controls->Add(this->textBox1);
			this->splitContainer1->Panel1->Controls->Add(this->treeView1);
			//
			// splitContainer1.Panel2
			//
			this->splitContainer1->Panel2->Controls->Add(this->webBrowser1);
			this->splitContainer1->Size = System::Drawing::Size(1070, 475);
			this->splitContainer1->SplitterDistance = 356;
			this->splitContainer1->TabIndex = 1;
			//
			// textBox1
			//
			this->textBox1->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->textBox1->Location = System::Drawing::Point(0, 455);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(356, 20);
			this->textBox1->TabIndex = 1;
			//
			// treeView1
			//
			this->treeView1->Font = (gcnew System::Drawing::Font(L"Consolas", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->treeView1->HotTracking = true;
			this->treeView1->Location = System::Drawing::Point(0, 26);
			this->treeView1->Name = L"treeView1";
			this->treeView1->Size = System::Drawing::Size(356, 424);
			this->treeView1->Click += gcnew System::EventHandler(this, &UI::treeView1_Click);
			this->treeView1->TabIndex = 0;
			//
			// webBrowser1
			//
			this->webBrowser1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->webBrowser1->Location = System::Drawing::Point(0, 0);
			this->webBrowser1->MinimumSize = System::Drawing::Size(20, 20);
			this->webBrowser1->Name = L"webBrowser1";
			this->webBrowser1->Size = System::Drawing::Size(710, 475);
			this->webBrowser1->TabIndex = 0;
			//
			// comboBox1
			//
			this->comboBox1->Font = (gcnew System::Drawing::Font(L"Consolas", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Location = System::Drawing::Point(101, 0);
			this->comboBox1->Margin = System::Windows::Forms::Padding(0, 3, 0, 3);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(101, 23);
			this->comboBox1->TabIndex = 5;
			//
			// comboBox2
			//
			this->comboBox2->Font = (gcnew System::Drawing::Font(L"Consolas", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->comboBox2->FormattingEnabled = true;
			this->comboBox2->Location = System::Drawing::Point(202, 0);
			this->comboBox2->Margin = System::Windows::Forms::Padding(0, 3, 0, 3);
			this->comboBox2->Name = L"comboBox2";
			this->comboBox2->Size = System::Drawing::Size(101, 23);
			this->comboBox2->TabIndex = 6;
			//
			// comboBox3
			//
			this->comboBox3->Font = (gcnew System::Drawing::Font(L"Consolas", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->comboBox3->FormattingEnabled = true;
			this->comboBox3->Location = System::Drawing::Point(0, 0);
			this->comboBox3->Margin = System::Windows::Forms::Padding(3, 3, 0, 3);
			this->comboBox3->Name = L"comboBox3";
			this->comboBox3->Size = System::Drawing::Size(101, 23);
			this->comboBox3->TabIndex = 4;
			//
			// Submit
			//
			this->Submit->Location = System::Drawing::Point(303, 0);
			this->Submit->Margin = System::Windows::Forms::Padding(0);
			this->Submit->Name = L"Submit";
			this->Submit->Size = System::Drawing::Size(54, 23);
			this->Submit->TabIndex = 7;
			this->Submit->Text = L"Filter";
			this->Submit->UseVisualStyleBackColor = true;
			this->Submit->Click += gcnew System::EventHandler(this, &UI::FilterButtonClick);
			//
			// UI
			//
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1070, 499);
			this->Controls->Add(this->splitContainer1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"UI";
			this->Text = L"SophosHealth Trails";
			this->Load += gcnew System::EventHandler(this, &UI::UI_Load);
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

		private: void FilterButtonClick(Object^ sender, EventArgs^ e) {
			MessageBox::Show("CLICKED");
		}

		private: void treeView1_Click(Object^ sender, EventArgs^ e) {
			MessageBox::Show("CLICKED " + sender->ToString());
		}

		private: void refreshMenuItem_Click(Object^ sender, EventArgs^ e) {
			MessageBox::Show("REFRESH " + sender->ToString());

			refreshData(this->treeView1);
		}

		private: System::Void splitter1_SplitterMoved(System::Object^  sender, System::Windows::Forms::SplitterEventArgs^  e) {
		}

		private: System::Void treeView1_AfterSelect(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e) {
		}

		private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		}
		private: System::Void textBox1_TextChanged_1(System::Object^  sender, System::EventArgs^  e) {
		}
		private: System::Void tabPage1_Click(System::Object^  sender, System::EventArgs^  e) {
		}
		private: System::Void UI_Load(System::Object^  sender, System::EventArgs^  e) {
		}
		private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
		}
		private: System::Void comboBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
		}
	};
}
