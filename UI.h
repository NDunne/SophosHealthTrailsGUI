#pragma once
#include "Header.h"

using namespace std;


namespace HealthTrail {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
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
	protected:
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  helpToolStripMenuItem;
	private: System::Windows::Forms::SplitContainer^  splitContainer1;
	public: System::Windows::Forms::TreeView^  treeView1;
	private:


	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::WebBrowser^  webBrowser1;
	private: System::Windows::Forms::ToolStripMenuItem^  refreshToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  configToolStripMenuItem;














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
			this->helpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->splitContainer1 = (gcnew System::Windows::Forms::SplitContainer());
			this->treeView1 = (gcnew System::Windows::Forms::TreeView());
			this->webBrowser1 = (gcnew System::Windows::Forms::WebBrowser());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->refreshToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->configToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
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
			// treeView1
			// 
			this->treeView1->Dock = System::Windows::Forms::DockStyle::Top;
			this->treeView1->HotTracking = true;
			this->treeView1->Location = System::Drawing::Point(0, 0);
			this->treeView1->Name = L"treeView1";
			this->treeView1->Size = System::Drawing::Size(356, 450);
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
			// textBox1
			// 
			this->textBox1->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->textBox1->Location = System::Drawing::Point(0, 455);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(356, 20);
			this->textBox1->TabIndex = 1;
			// 
			// refreshToolStripMenuItem
			// 
			this->refreshToolStripMenuItem->Name = L"refreshToolStripMenuItem";
			this->refreshToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->refreshToolStripMenuItem->Text = L"Refresh";
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			this->exitToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->exitToolStripMenuItem->Text = L"Exit";
			// 
			// configToolStripMenuItem
			// 
			this->configToolStripMenuItem->Name = L"configToolStripMenuItem";
			this->configToolStripMenuItem->Size = System::Drawing::Size(55, 20);
			this->configToolStripMenuItem->Text = L"Config";
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
};
}
