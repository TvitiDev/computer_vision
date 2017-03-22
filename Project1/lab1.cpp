#include "lab1.h"


/*
	Получить объект изображения
*/
Bitmap ^lab1::getImg()
{
	Bitmap ^imageOut = gcnew Bitmap(widthImg, heightImg);
	Color^ pixelOut;

	double pixel;
	int width = widthImg - 1;
	int height = heightImg - 1;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			pixel = imagePoint[y * width + x];
			pixel = pixel > 255 ? 255 : pixel;
			pixelOut = Color::FromArgb(pixel, pixel, pixel);
			imageOut->SetPixel(x, y, *pixelOut);
		}
	}

	return imageOut;
}

lab1::lab1(double *imgPoint, int width, int height) 
{
	widthImg = width;
	heightImg = height;
	imagePoint = imgPoint;
}


/*
	Свертка по ядру размером size*size или сепарабельная
*/
lab1 lab1::svertka(int size, double X[], double Y[], int mode, int type)
{
	int width = widthImg - 1;
	int height = heightImg - 1;
	double* imageOut = new double[widthImg * heightImg];
	
	for (int y = 0; y <= height; y++) {
		for (int x = 0; x <= width; x++) {

			switch (mode)
			{
			case lab1::TYPE_BORDER_WITHOUT:
				imageOut[y * width + x] = borderWithout(x, y, X, Y, size, type);
				break;
			case lab1::TYPE_BORDER_BLACK:
				imageOut[y * width + x] = borderBlack(x, y, X, Y, size, type);
				break;
			case lab1::TYPE_BORDER_WRAPPING:
				imageOut[y * width + x] = borderWrapping(x, y, X, Y, size, type);
				break;
			case lab1::TYPE_BORDER_MIRROR:
				imageOut[y * width + x] = borderMirror(x, y, X, Y, size, type);
				break;
			default:

				break;
			}
		}
	}

	return *(new lab1(imageOut, widthImg, heightImg));
}

/**
* Режим обработки краев "зеркалированием"
*/
double lab1::borderMirror(int x, int y, double X[], double Y[], int size, int type)
{
	int aura = size / 2;
	int width = widthImg - 1;
	int height = heightImg - 1;
	double Gx = 0;
	double Gy = 0;
	double G = 0;
	double point;
	int pointX;
	int pointY;
	double *SV = new double[size];
	SV[0] = 0;

	for (int n = 0, m = 0, i = 0, Xz = -1 * aura, Yz = -1 * aura; i < pow(size, 2); i++, Xz++, m++) {
		
		pointX = x + Xz;
		pointY = y + Yz;

		if ((x + Xz) < 0) {
			pointX = x - Xz;
		}
		
		if ((y + Yz) < 0) {
			pointY = y - Yz;
		}
		
		if ((x + Xz) > width - 1) {
			pointX = x - Xz;	
		}
		
		if ((y + Yz) > height - 1) {
			pointY = y - Yz;
		}		

		point = imagePoint[pointY * width + pointX];

		if (type == lab1::SVERTKA) {
			Gx += point * X[i];
			Gy += point * Y[i];
		}
		else if (type == lab1::SEPAR) {
			SV[n] += point * X[m];
		}

		if (Xz == aura) {
			Xz = -1 * aura - 1;
			Yz++;
			n++;
			m = 0;
			SV[n] = 0;
		}
	}

	if (type == lab1::SVERTKA) {
		G = sqrt(Gx * Gx + Gy * Gy);
	}
	else if (type == lab1::SEPAR) {
		for (int n = 0; n < size; n++) {
			G += SV[n] * X[n];
		}
	}

	return (G > 255) ? 255 : G;
}

/**
* Режим обработки краев "сворачиванием"
*/
double lab1::borderWrapping(int x, int y, double X[], double Y[], int size, int type)
{
	int aura = size / 2;
	int width = widthImg - 1;
	int height = heightImg - 1;
	double Gx = 0;
	double Gy = 0;
	double G = 0;
	double point;
	int pointX;
	int pointY;
	double *SV = new double[size];
	SV[0] = 0;

	for (int n = 0, m = 0, i = 0, Xz = -1 * aura, Yz = -1 * aura; i < pow(size, 2); i++, Xz++, m++) {

		pointX = x + Xz;
		pointY = y + Yz;

		if ((x + Xz) < 0) {
			pointX = width + Xz;
		}

		if ((y + Yz) < 0) {
			pointY = height + Yz;
		}

		if ((x + Xz) > width - 1) {
			pointX = Xz;
		}

		if ((y + Yz) > height - 1) {
			pointY = Yz;
		}

		point = imagePoint[pointY * width + pointX];

		if (type == lab1::SVERTKA) {
			Gx += point * X[i];
			Gy += point * Y[i];
		}
		else if (type == lab1::SEPAR) {
			SV[n] += point * X[m];
		}	

		if (Xz == aura) {
			Xz = -1 * aura - 1;
			Yz++;
			n++;
			m = 0;
			SV[n] = 0;
		}
	}

	if (type == lab1::SVERTKA) {
		G = sqrt(Gx * Gx + Gy * Gy);
	}
	else if (type == lab1::SEPAR) {
		for (int n = 0; n < size; n++) {
			G += SV[n] * X[n];
		}
	}

	return (G > 255) ? 255 : G;
}

/**
* Режим обработки краев путем "заливки" на один черный пиксель
*/
double lab1::borderBlack(int x, int y, double X[], double Y[], int size, int type)
{
	int aura = size / 2;
	int width = widthImg - 1;
	int height = heightImg - 1;
	bool isBlack = false;
	double Gx = 0;
	double Gy = 0;
	double G = 0;
	double point; 
	double *SV = new double[size];
	SV[0] = 0;

	for (int n = 0, m = 0, i = 0, Xz = -1 * aura, Yz = -1 * aura; i < pow(size, 2); i++, Xz++, m++) {
		point = imagePoint[(y + Yz) * width + (x + Xz)];

		if ((x + Xz) < aura || (y + Yz) < aura || (x + Xz) > width - aura || (y + Yz) > height - aura) {
			isBlack = true;
		} else {
			isBlack = false;
		}		

		if (type == lab1::SVERTKA) {
			Gx += isBlack ? 0 : point * X[i];
			Gy += isBlack ? 0 : point * Y[i];
		}
		else if (type == lab1::SEPAR) {
			SV[n] += isBlack ? 0 : point * X[m];
		}

		if (Xz == aura) {
			Xz = -1 * aura - 1;
			Yz++;
			n++;
			m = 0;
			SV[n] = 0;
		}
	}	

	if (type == lab1::SVERTKA) {
		G = sqrt(Gx * Gx + Gy * Gy);
	}
	else if (type == lab1::SEPAR) {
		for (int n = 0; n < size; n++) {
			G += SV[n] * X[n];
		}
	}

	return (G > 255) ? 255 : G;
}

/**
* Режим обработки краев путем уменьшения изображения на 1 пиксель
*/
double lab1::borderWithout(int x, int y, double X[], double Y[], int size, int type)
{
	int aura = size / 2;
	int width = widthImg - 1;
	int height = heightImg - 1;

	if (x < aura || y < aura || x > width - aura || y > height - aura) {
		return 255;
	}

	double Gx = 0;
	double Gy = 0;
	double G = 0;
	double point;

	double *SV = new double[size];
	SV[0] = 0;

	for (int n = 0, m = 0, i = 0, Xz = -1 * aura, Yz = -1 * aura; i < pow(size, 2); i++, Xz++, m++) {
		point = imagePoint[(y + Yz) * width + (x + Xz)];

		if (type == lab1::SVERTKA) {
			Gx += point * X[i];
			Gy += point * Y[i];
		}
		else if (type == lab1::SEPAR) {
			SV[n] += point * X[m];
		}
		
		if (Xz == aura) {
			Xz = -1 * aura - 1;
			Yz++;
			n++;
			m = 0;
			SV[n] = 0;
		}
	}

	if (type == lab1::SVERTKA) {
		int G = sqrt(Gx * Gx + Gy * Gy);
	}
	else if (type == lab1::SEPAR) {
		for (int n = 0; n < size; n++) {
			G += SV[n] * X[n];
		}
	}

	return (G > 255) ? 255 : G;
}

/**
*	Загрузка оригинала
*/
lab1::lab1(String^ name)
{
	Bitmap ^image = gcnew Bitmap(name, true);
	widthImg = image->Width;
	heightImg = image->Height;

	// create array
	imagePoint = new double[widthImg * heightImg];

	int colorMid;
	int width = widthImg - 1;
	int height = heightImg - 1;	

	for (int y = 0; y <= height; y++) {
		for (int x = 0; x <= width; x++) {
			Color^ pixel = image->GetPixel(x, y);
			colorMid = pixel->R * 0.299 + pixel->G * 0.587 + pixel->B * 0.114;

			imagePoint[y * width + x] = (colorMid > 255) ? 255 : colorMid;
		}
	}
}