#include "lab1.h"
#include <math.h>

/**
* Конструктор
*/
lab1::lab1()
{
}

void lab1::getImg()
{
	imageOut = gcnew Bitmap(image->Width, image->Height);
	Color^ pixelOut;

	int pixel;
	int width = image->Width - 1;
	int height = image->Height - 1;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			pixel = imgPoint[y * width + x];
			pixelOut = Color::FromArgb(pixel, pixel, pixel);
			imageOut->SetPixel(x, y, *pixelOut);
		}
	}

	delete[] imgPoint;
	delete pixelOut;
}

/*
	фильтр гаусса
*/
void lab1::gauss()
{

}

/*
	Преобразование Собеля
*/
void lab1::sobel()
{
	int X[9] = { -1, 0, 1, -2, 0, 2, -1, 0, 1 };
	int Y[9] = { -1, -2, -1, 0, 0, 0, 1, 2, 1 };

	int width = image->Width - 1;
	int height = image->Height - 1;
	int* pixel = new int[9];
	int* imageOut = new int[image->Width * image->Height];

	for (int y = 0; y <= height; y++) {
		for (int x = 0; x <= width; x++) {
			
			switch (borderMode)
			{
			case 1:
				imageOut[y * width + x] = mode1(x, y, width, height, X, Y);
				break;
			case 2:
				imageOut[y * width + x] = mode2(x, y, width, height, X, Y);
				break;
			case 3:
				imageOut[y * width + x] = mode3(x, y, width, height, X, Y);
				break;
			case 4:
				imageOut[y * width + x] = mode4(x, y, width, height, X, Y);
				break;
			default:

				break;
			}			
		}
	}

	delete[] imgPoint;
	imgPoint = imageOut;
}

/**
* Режим обработки краев "зеркалированием"
*/
int lab1::mode4(int x, int y, int width, int height, int X[], int Y[])
{
	bool isBlack = false;
	int Gx = 0;
	int Gy = 0;
	int point;

	for (int i = 0, Xz = -1, Yz = -1; i < 9; i++, Xz++) {
		if ((x + Xz) == -1) {
			point = imgPoint[((y + Yz) < 0 ? 0 : (y + Yz)) * width + 1];
		}
		else if ((y + Yz) == -1) {
			point = imgPoint[width + (x + Xz)];
		}
		else if ((x + Xz) == width + 1) {
			point = imgPoint[(y + Yz) * width + width - 1];
		}
		else if ((y + Yz) == height + 1) {
			point = imgPoint[(height - 1) * x + Xz];
		}
		else
		{
			point = imgPoint[(y + Yz) * width + (x + Xz)];
		}

		Gx += point * X[i];
		Gy += point * Y[i];

		if (Xz == 1) {
			Xz = -2;
			Yz++;
		}
	}

	int G = sqrt(pow(Gx, 2) + pow(Gy, 2));
	return (G > 255) ? 255 : G;
}

/**
* Режим обработки краев "сворачиванием"
*/
int lab1::mode3(int x, int y, int width, int height, int X[], int Y[])
{
	bool isBlack = false;
	int Gx = 0;
	int Gy = 0;
	int point;

	for (int i = 0, Xz = -1, Yz = -1; i < 9; i++, Xz++) {
		if ((x + Xz) == -1) {
			point = imgPoint[(y + Yz) * width + width - 1];
		} 
		else if ((y + Yz) == -1) {
			point = imgPoint[(height - 1) * width + (x + Xz)];
		}
		else if ((x + Xz) == width + 1) {
			point = imgPoint[(y + Yz) * width];
		}
		else if ((y + Yz) == height + 1) {
			point = imgPoint[x + Xz];
		}
		else
		{
			point = imgPoint[(y + Yz) * width + (x + Xz)];
		}

		Gx += point * X[i];
		Gy += point * Y[i];

		if (Xz == 1) {
			Xz = -2;
			Yz++;
		}
	}

	int G = sqrt(pow(Gx, 2) + pow(Gy, 2));
	return (G > 255) ? 255 : G;
}

/**
* Режим обработки краев путем "заливки" на один черный пиксель
*/
int lab1::mode2(int x, int y, int width, int height, int X[], int Y[])
{
	bool isBlack = false;
	int Gx = 0;
	int Gy = 0;
	int point;

	for (int i = 0, Xz = -1, Yz = -1; i < 9; i++, Xz++) {
		point = (y + Yz) * width + (x + Xz);

		if ((x + Xz) == -1 || (y + Yz) == -1 || (x + Xz) == width + 1 || (y + Yz) == height + 1) {
			isBlack = true;
		} else {
			isBlack = false;
		}

		Gx += isBlack ? 0 : imgPoint[point] * X[i];
		Gy += isBlack ? 0 : imgPoint[point] * Y[i];

		if (Xz == 1) {
			Xz = -2;
			Yz++;
		}
	}

	int G = sqrt(pow(Gx, 2) + pow(Gy, 2));
	return (G > 255) ? 255 : G;
}

/**
* Режим обработки краев путем уменьшения изображения на 1 пиксель
*/
int lab1::mode1(int x, int y, int width, int height, int X[], int Y[])
{
	if (x == 0 || y == 0 || x == width || y == height) {
		return 255;
	}

	int Gx = 0;
	int Gy = 0;
	int point;

	for (int i = 0, Xz = -1, Yz = -1; i < 9; i++, Xz++) {
		point = (y + Yz) * width + (x + Xz);
		Gx += imgPoint[point] * X[i];
		Gy += imgPoint[point] * Y[i];

		if (Xz == 1) {
			Xz = -2;
			Yz++;
		}
	}

	int G = sqrt(pow(Gx, 2) + pow(Gy, 2));
	return (G > 255) ? 255 : G;
}

/*
	Преобразование в оттенки серого
*/
void lab1::grey()
{
	int colorMid;
	int width = widthImg - 1;
	int height = heightImg - 1;

	for (int y = 0; y <= height; y++) {
		for (int x = 0; x <= width; x++) {
			Color^ pixel = image->GetPixel(x, y);
			colorMid = pixel->R * 0.299 + pixel->G * 0.587 + pixel->B * 0.114;
		
			imgPoint[y * width + x] = (colorMid > 255) ? 255 : colorMid;
		}
	}
}

/*
	Загрузка оригинала
*/
void lab1::loadImage(String^ name)
{
	Bitmap ^image = gcnew Bitmap(name, true);
	widthImg = image->Width;
	heightImg = image->Height;
	// create array
	imgPoint = new int[widthImg * heightImg];

	int colorMid;
	int width = widthImg - 1;
	int height = heightImg - 1;
	

	for (int y = 0; y <= height; y++) {
		for (int x = 0; x <= width; x++) {
			Color^ pixel = image->GetPixel(x, y);
			colorMid = pixel->R * 0.299 + pixel->G * 0.587 + pixel->B * 0.114;

			imgPoint[y * width + x] = (colorMid > 255) ? 255 : colorMid;
		}
	}
}