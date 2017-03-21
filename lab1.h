#pragma once
#include <memory>

using namespace System::Drawing;
using namespace System;

ref class lab1
{
public:

	// Bitmap^ image;
	Bitmap^ imageOut;

	int widthImg;
	int heightImg;

	/*
		����� ��������� �����
		1 - �������� �� 1 �������
		2 - ������ ������� �� �����
		3 -
		4 -
	*/
	const int borderMode = 4;

	int *imgPoint;

	// �����������
	lab1();

	// �������������� � ������� ������
	void grey();

	// �������� ��������� �����������
	void lab1::loadImage(String^);

	// �������������� ������
	void lab1::sobel();

	void lab1::getImg();

	void lab1::gauss();

	int lab1::mode1(int, int, int, int, int[], int[]);

	int lab1::mode2(int, int, int, int, int[], int[]);

	int lab1::mode3(int, int, int, int, int[], int[]);

	int lab1::mode4(int, int, int, int, int[], int[]);


};

