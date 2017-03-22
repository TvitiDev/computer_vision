#pragma once
#include <memory>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace System::Drawing;
using namespace System;

class lab1
{
public:
	
	int widthImg;
	int heightImg;

	double *imagePoint;

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

	// �����������. �������� ��������� �����������
	lab1(String^);

	// �����������. �������� ��������� �����������
	lab1(double *, int, int);
	
	// �������
	lab1 lab1::svertka(int size, double X[], double Y[], int, int);

	Bitmap ^lab1::getImg();

private :

	double lab1::borderWithout(int, int, double[], double[], int, int);

	double lab1::borderBlack(int, int, double[], double[], int, int);

	double lab1::borderWrapping(int, int, double[], double[], int, int);
	
	double lab1::borderMirror(int, int, double[], double[], int, int);
	

};

