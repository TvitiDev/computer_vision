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

	/* —вертка €дром */
	static const int SVERTKA = 1;

	/* —епарабельна€ свертка */
	static const int SEPAR = 2;


	/* Ѕез крайних пикселей */
	static const int TYPE_BORDER_WITHOUT = 1;

	/* «аливка черным пикселем */
	static const int TYPE_BORDER_BLACK = 2;

	/* «аворачивание изображени€ */
	static const int TYPE_BORDER_WRAPPING = 3;

	/* «еркалирование пикселей */
	static const int TYPE_BORDER_MIRROR = 4;

	// конструктор. загрузка оригинала изображени€
	lab1(String^);

	// конструктор. загрузка оригинала изображени€
	lab1(double *, int, int);
	
	// свертка
	lab1 lab1::svertka(int size, double X[], double Y[], int, int);

	Bitmap ^lab1::getImg();

private :

	double lab1::borderWithout(int, int, double[], double[], int, int);

	double lab1::borderBlack(int, int, double[], double[], int, int);

	double lab1::borderWrapping(int, int, double[], double[], int, int);
	
	double lab1::borderMirror(int, int, double[], double[], int, int);
	

};

