#include "lab1.h";
#include <iostream>


namespace Project1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: 
		System::Windows::Forms::Button^  button1;
		System::Windows::Forms::PictureBox^  pictureBox1;
		Bitmap^ image1;
		Bitmap^ image2;
		Bitmap^ image3;
		Bitmap^ image4;
		Image^ image;


	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::Button^  button5;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(746, 12);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(122, 21);
			this->button1->TabIndex = 0;
			this->button1->Text = L"��������";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(12, 12);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(728, 473);
			this->pictureBox1->TabIndex = 1;
			this->pictureBox1->TabStop = false;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(747, 40);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(35, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"label1";
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(746, 72);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(122, 23);
			this->button2->TabIndex = 3;
			this->button2->Text = L"�������� ������";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(746, 115);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(122, 23);
			this->button3->TabIndex = 4;
			this->button3->Text = L"������";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(746, 154);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(122, 25);
			this->button4->TabIndex = 5;
			this->button4->Text = L"�����";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
			// 
			// button5
			// 
			this->button5->Location = System::Drawing::Point(746, 199);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(122, 26);
			this->button5->TabIndex = 6;
			this->button5->Text = L"button5";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &MyForm::button5_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(880, 501);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->button1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		image1 = gcnew Bitmap("e46_2.jpg", true);
				
		pictureBox1->Image = image1;
	}
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
		image2 = gcnew Bitmap(image1->Width, image1->Height);
		
		for (int x = 0; x < image1->Width; x++) {
			for (int y = 0; y < image1->Height; y++) {
				Color^ pixel = image1->GetPixel(x, y);
				int ColorMid = (int) (pixel->R * 0.299 + pixel->G * 0.587 + pixel->B * 0.114);
				if (ColorMid > 255) {
					ColorMid = 255;
				}

				Color^ pixel2 = Color::FromArgb(ColorMid, ColorMid, ColorMid);

				image2->SetPixel(x, y, *pixel2);
			}
		}

		pictureBox1->Image = image2;
	}

	private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
		image4 = gcnew Bitmap(image2->Width, image2->Height);

		int X[9] = { -1, 0, 1, -2, 0, 2, -1, 0, 1 };
		int Y[9] = { -1, -2, -1, 0, 0, 0, 1, 2, 1 };
		Color* pixel[9];
		int Ex = 0;
		Color^ pixel2;

		int Gx = 0,
			Gy = 0,
			G;

		for (int x = 1; x < image2->Width - 1; x++) {
			for (int y = 1; y < image2->Height - 1; y++) {

				pixel[0] = &image2->GetPixel(x-1, y-1);
				pixel[1] = &image2->GetPixel(x, y-1);
				pixel[2] = &image2->GetPixel(x+1, y-1);
				pixel[3] = &image2->GetPixel(x-1, y);
				pixel[4] = &image2->GetPixel(x, y);
				pixel[5] = &image2->GetPixel(x+1, y);
				pixel[6] = &image2->GetPixel(x-1, y+1);
				pixel[7] = &image2->GetPixel(x, y+1);
				pixel[8] = &image2->GetPixel(x+1, y+1);
				
				Gx = Gy = 0;

				for (int i = 0; i < 9; i++) {
					Gx += pixel[i]->R * X[i];
					Gy += pixel[i]->R * Y[i];
				}

				G = (int) Math::Sqrt(Math::Pow(Gx, 2) + Math::Pow(Gy, 2));

				if (G > 255) {
					G = 255;
					Ex += 1;
				}

				pixel2 = Color::FromArgb(G, G, G);
				image4->SetPixel(x, y, *pixel2);
				delete pixel2;
			}
		}

		label1->Text = Convert::ToString(Ex);
		pictureBox1->Image = image4;
	}
	private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
		image3 = gcnew Bitmap(image2->Width, image2->Height);

		int X[9] = { 1, 2, 1, 2, 4, 2, 1, 2, 1 };
		Color* pixel[9];
		int Ex = 0;

		for (int x = 1; x < image2->Width - 1; x++) {
			for (int y = 1; y < image2->Height - 1; y++) {

				pixel[0] = &image2->GetPixel(x - 1, y - 1);
				pixel[1] = &image2->GetPixel(x, y - 1);
				pixel[2] = &image2->GetPixel(x + 1, y - 1);
				pixel[3] = &image2->GetPixel(x - 1, y);
				pixel[4] = &image2->GetPixel(x, y);
				pixel[5] = &image2->GetPixel(x + 1, y);
				pixel[6] = &image2->GetPixel(x - 1, y + 1);
				pixel[7] = &image2->GetPixel(x, y + 1);
				pixel[8] = &image2->GetPixel(x + 1, y + 1);

				int Gx = 0,
					G;

				for (int i = 0; i < 9; i++) {
					Gx += pixel[i]->R * X[i];
				}

				G = Gx;
				
				if (G > 255) {
					G = 255;
					Ex += 1;
				}

				Color^ pixel = Color::FromArgb(G, G, G);
				image3->SetPixel(x, y, *pixel);
			}
		}

		label1->Text = Convert::ToString(Ex);
		pictureBox1->Image = image3;

	}

	private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e) {
		
		lab1^ Img = gcnew lab1();
		int *imgPoint = Img->loadImage("e46_2.jpg");
		double static const a = 1;
		int static const N = a * 6 + 1;
		int N2 = (int) N / 2;
		double *Gauss = new double[N];
		
		double r = 0;

		for (double i = 0, j = -1 * N2; i < N; j++, i++) {
			r += Gauss[(int) i] = (pow(M_E, ((-1 * j * j) / (2 * a * a))) / (sqrt(2 * M_PI) * a));
		}
		
		label1->Text = System::Convert::ToString(r);

		// �����
		int *imgPoint2 = Img->svertka(imgPoint, N, Gauss, Gauss, lab1::TYPE_BORDER_WITHOUT, lab1::SEPAR);

		double X[9] = { -1, 0, 1, -2, 0, 2, -1, 0, 1 };
		double Y[9] = { -1, -2, -1, 0, 0, 0, 1, 2, 1 };

		// �������������� ������
		int *imgPoint3 = Img->svertka(imgPoint2, 3, X, Y, lab1::TYPE_BORDER_WRAPPING, lab1::SVERTKA);

		pictureBox1->Image = Img->getImg(imgPoint3);
	}
};
}
