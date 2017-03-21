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

	/* Свертка ядром */
	static const int SVERTKA = 1;

	/* Сепарабельная свертка */
	static const int SEPAR = 2;


	/* Без крайних пикселей */
	static const int TYPE_BORDER_WITHOUT = 1;

	/* Заливка черным пикселем */
	static const int TYPE_BORDER_BLACK = 2;

	/* Заворачивание изображения */
	static const int TYPE_BORDER_WRAPPING = 3;

	/* Зеркалирование пикселей */
	static const int TYPE_BORDER_MIRROR = 4;

	// конструктор
	lab1();	

	// загрузка оригинала изображения
	int *lab1::loadImage(String^);

	// преобразование собеля
	//int *lab1::sobel(int);

	// свертка
	int *lab1::svertka(int *imgPoint, int size, double X[], double Y[], int, int);

	Bitmap ^lab1::getImg(int *);

	int lab1::borderWithout(int *, int, int, double[], double[], int, int);

	int lab1::borderBlack(int *, int, int, double[], double[], int, int);

	int lab1::borderWrapping(int *, int, int, double[], double[], int, int);
	
	int lab1::borderMirror(int *, int, int, double[], double[], int, int);
	

};

