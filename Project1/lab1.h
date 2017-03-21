#pragma once
#include <memory>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace System::Drawing;
using namespace System;

ref class lab1
{
public:
	
	int widthImg;
	int heightImg;

	/* ������� ����� */
	static const int SVERTKA = 1;

	/* ������������� ������� */
	static const int SEPAR = 2;


	/* ��� ������� �������� */
	static const int TYPE_BORDER_WITHOUT = 1;

	/* ������� ������ �������� */
	static const int TYPE_BORDER_BLACK = 2;

	/* ������������� ����������� */
	static const int TYPE_BORDER_WRAPPING = 3;

	/* �������������� �������� */
	static const int TYPE_BORDER_MIRROR = 4;

	// �����������
	lab1();	

	// �������� ��������� �����������
	int *lab1::loadImage(String^);

	// �������������� ������
	//int *lab1::sobel(int);

	// �������
	int *lab1::svertka(int *imgPoint, int size, double X[], double Y[], int, int);

	Bitmap ^lab1::getImg(int *);

	int lab1::borderWithout(int *, int, int, double[], double[], int, int);

	int lab1::borderBlack(int *, int, int, double[], double[], int, int);

	int lab1::borderWrapping(int *, int, int, double[], double[], int, int);
	
	int lab1::borderMirror(int *, int, int, double[], double[], int, int);
	

};

