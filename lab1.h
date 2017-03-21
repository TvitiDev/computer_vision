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
		Режим обработки краев
		1 - обрезаем по 1 пикселю
		2 - черный пиксель по краям
		3 -
		4 -
	*/
	const int borderMode = 4;

	int *imgPoint;

	// конструктор
	lab1();

	// преобразование в оттенки серого
	void grey();

	// загрузка оригинала изображения
	void lab1::loadImage(String^);

	// преобразование собеля
	void lab1::sobel();

	void lab1::getImg();

	void lab1::gauss();

	int lab1::mode1(int, int, int, int, int[], int[]);

	int lab1::mode2(int, int, int, int, int[], int[]);

	int lab1::mode3(int, int, int, int, int[], int[]);

	int lab1::mode4(int, int, int, int, int[], int[]);


};

