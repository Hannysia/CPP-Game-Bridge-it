#pragma once
#include "BoardElements.h"

namespace Курсоваробота1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;

	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			pictureBox1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox1_MouseDown);
			pictureBox1->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox1_MouseUp);

			myBoard = gcnew Board(pictureBox1);
			double x, y;
			arrayTDot = gcnew array<Dot^>(20);
			arrayMDot = gcnew array<Dot^>(20);
			Color color1 = Color::Maroon;
			Brush^ brush1 = gcnew SolidBrush(color1);
			Color color2 = Color::FromArgb(12, 125, 106); 
			Brush^ brush2 = gcnew SolidBrush(color2);
			double radius = 15;
			int Id;
			bool connection = false;
			//марунові точки
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 4; j++) {
					y = (i * 150 + 107);
					x = 492.5 + j * 150;
					Id = 4 * i + j + 1;
					arrayMDot[4 * i + j] = gcnew Dot(Id, x, y, brush1, connection, radius);
				}
			}
			//бірюзові точки
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 5; j++) {
					y = 150 * i + 182;
					x = (150 * j + 417.5);
					Id = 5 * i + j + 21; 
					arrayTDot[5 * i + j] = gcnew Dot(Id, x, y, brush2, connection, radius);
				}
			}
			for (int i = 0; i < 20; i++) {
				myBoard->Add(arrayTDot[i]);
				myBoard->Add(arrayMDot[i]);
			}

		}

	protected:
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;

	protected:
	protected:
	private:
System::ComponentModel::Container^ components;
#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(-1, 1);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(1442, 853);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Click += gcnew System::EventHandler(this, &MyForm::pictureBox1_Click_1);
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"NSimSun", 13.875F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic))));
			this->button1->ForeColor = System::Drawing::Color::Maroon;
			this->button1->Location = System::Drawing::Point(421, 764);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(634, 50);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Start to play!";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// button2
			// 
			this->button2->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->button2->Font = (gcnew System::Drawing::Font(L"NSimSun", 13.875F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->button2->ForeColor = System::Drawing::Color::Teal;
			this->button2->Location = System::Drawing::Point(421, 12);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(634, 62);
			this->button2->TabIndex = 2;
			this->button2->Text = L"Who is first\?";
			this->button2->UseVisualStyleBackColor = false;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// MyForm
			// 
			this->ClientSize = System::Drawing::Size(1439, 850);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->pictureBox1);
			this->Name = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load_1);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	Board^ myBoard;
	Bridge^ bridge;
	Graphics^ g;
	array<Dot^>^ arrayTDot;
	array<Dot^>^ arrayMDot;
	Dot^ from;
	Dot^ to;
	int s;
		 void NextUser(int i) {
			Graphics^ g = pictureBox1->CreateGraphics();
			SolidBrush^ brush1 = gcnew SolidBrush(Color::FromArgb(12, 125, 106));
			SolidBrush^ brush2 = gcnew SolidBrush(Color::Maroon);
			if (i == 0) {
				g->DrawString("Turquoise player`s turn!", gcnew Drawing::Font("Arial", 25), brush1, 10, 400);
			}
			else {
				g->DrawString("Maroon player`s turn!", gcnew Drawing::Font("Arial", 25), brush2, 1000, 400);
			}
			Thread::Sleep(1500);
		   }
		   
	System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		for (int i = 0; i < 20; i++) {
			myBoard->Add(arrayTDot[i]);
			myBoard->Add(arrayMDot[i]);
		}
		button1->Visible = false;
		button2->Visible = true;
	}
	System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
			   MouseEventArgs^ mouseEvent = dynamic_cast<MouseEventArgs^>(e);
			   if (mouseEvent != nullptr && mouseEvent->Button == System::Windows::Forms::MouseButtons::Left) {
				   s = ChooseFirst();
				   NextUser(s);
				   button2->Visible = false;
			   }
			   button2->Visible = false;
		   }
	
		System::Void pictureBox1_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
			double x = e->X; 
			double y = e->Y;
				if (s == 0) {
					for (int i = 0; i < 20; i++) {
						if (abs(x - arrayTDot[i]->getX()) <= 50 && abs(y - arrayTDot[i]->getY()) <= 50) {
							from = arrayTDot[i];
							break;
						}
						else if (abs(x - arrayMDot[i]->getX()) <= 50 && abs(y - arrayMDot[i]->getY()) <= 50) {
							from = nullptr;
						}
						else { from = nullptr; }
					}
				}
				else {
					for (int i = 0; i < 20; i++) {
						if (abs(x - arrayMDot[i]->getX()) <= 50 && abs(y - arrayMDot[i]->getY()) <= 50) {
							from = arrayMDot[i];
							break;
						}
						else if(abs(x - arrayTDot[i]->getX()) <= 50 && abs(y - arrayTDot[i]->getY()) <= 50) {
							from = nullptr;
						}
						else { from = nullptr; }
					}
				}
		}
		array<Dot^>^ FindDot(Dot^ f, Dot^ t) {
			Brush^ color = f->getColor();
			Dot^ adjDot1;
			Dot^ adjDot2;
			bool resultM1, resultM2, resultM3, resultM4;
			bool resultT1, resultT2, resultT3, resultT4;
			if (color == arrayTDot[0]->getColor()) {
				for (int i = 0; i < 20; i++) {
					resultM1 = CheckLength(from, arrayMDot[i]);
					resultM2 = CheckLength(to, arrayMDot[i]);
					if (resultM1 && resultM2) {
						adjDot1 = arrayMDot[i];
						break;
					}
				}
				for (int i = 0; i < 20; i++) {
					resultM3 = CheckLength(from, arrayMDot[i]);
					resultM4 = CheckLength(to, arrayMDot[i]);
					if (resultM3 && resultM4 && arrayMDot[i] != adjDot1) {
						adjDot2 = arrayMDot[i];
						break;
					}
				}
			}
			else {
				for (int i = 0; i < 20; i++) {
					resultT1 = CheckLength(from, arrayTDot[i]);
					resultT2 = CheckLength(to, arrayTDot[i]);
					if (resultT1 == true && resultT2 == true) {
						adjDot1 = arrayTDot[i];
						break;
					}
				}
				for (int i = 0; i < 20; i++) {
					resultT3 = CheckLength(from, arrayTDot[i]);
					resultT4 = CheckLength(to, arrayTDot[i]);
					if (resultT3 && resultT4 && arrayTDot[i] != adjDot1) {
						adjDot2 = arrayTDot[i];
						break;
					}
				}
			}
			array<Dot^>^ adjacentdots = gcnew array<Dot^>(2);
			adjacentdots[0] = adjDot1; adjacentdots[1] = adjDot2;
			return adjacentdots;
		}


		System::Void pictureBox1_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
			double x1 = e->X; 
			double y1 = e->Y;
			
			if (s == 0) {
				for (int i = 0; i < 20; i++) {
					if (abs(x1 - arrayTDot[i]->getX()) <= 50 && abs(y1 - arrayTDot[i]->getY()) <= 50) {
						to = arrayTDot[i];
						break;
					}
					else if (abs(x1 - arrayMDot[i]->getX()) <= 50 && abs(y1 - arrayMDot[i]->getY()) <= 50) {
						to = nullptr;
					}
					else { to = nullptr; }
				}
			}
			else if (s == 1) {
				for (int i = 0; i < 20; i++) {
					if (abs(x1 - arrayMDot[i]->getX()) <= 50 && abs(y1 - arrayMDot[i]->getY()) <= 50) {
						to = arrayMDot[i];
						break;
					}
					else { to = nullptr; }
				}
			}
			if (from != to && from != nullptr && to != nullptr && from->getColor()->Equals(to->getColor()) && CalcLength(from, to) == 150) {
				array<Dot^>^ ad = gcnew array<Dot^>(2);
				ad = FindDot(from, to);
				
				if (!myBoard->FindBridge(ad[0], ad[1])) {
					bridge = gcnew Bridge(from, to);
					myBoard->Add(bridge);
					Invalidate();
					if (s == 1) {
						s = 0;
					}
					else { s = 1; }
					NextUser(s);
				}
				else { delete to; delete from; delete ad; }
			}
			else { delete to; delete from; }
		}

	void pictureBox1_Paint(Object^ sender, PaintEventArgs^ e) {
			myBoard->Draw();
		}
	protected:
		virtual void OnPaint(PaintEventArgs^ e) override {
			pictureBox1_Paint(this, e);
		}
	private: Void MyForm_Load(Object^ sender, EventArgs^ e) {
	}
	private: Void pictureBox1_Click(Object^ sender, EventArgs^ e) {
	}
	private: System::Void MyForm_Load_1(System::Object^ sender, System::EventArgs^ e) {
		button2->Visible = false;
	}
	private: System::Void pictureBox1_Click_1(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void textBox2_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {}
};}









