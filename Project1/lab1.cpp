#include "lab1.h"



/**
* Конструктор
*/
lab1::lab1()
{
}

/*
	Получить объект изображения
*/
Bitmap ^lab1::getImg(int *imgPoint)
{
	Bitmap ^imageOut = gcnew Bitmap(widthImg, heightImg);
	Color^ pixelOut;

	int pixel;
	int width = widthImg - 1;
	int height = heightImg - 1;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			pixel = imgPoint[y * width + x] > 255 ? 255 : imgPoint[y * width + x];
			pixelOut = Color::FromArgb(pixel, pixel, pixel);
			imageOut->SetPixel(x, y, *pixelOut);
		}
	}

	return imageOut;
}


/*
	Свертка по ядру размером size*size или сепарабельная
*/
int *lab1::svertka(int *imgPoint, int size, double X[], double Y[], int mode, int type)
{
	int width = widthImg - 1;
	int height = heightImg - 1;
	int* pixel = new int[pow(size, 2)];
	int* imageOut = new int[widthImg * heightImg];
	
	for (int y = 0; y <= height; y++) {
		for (int x = 0; x <= width; x++) {

			switch (mode)
			{
			case lab1::TYPE_BORDER_WITHOUT:
				imageOut[y * width + x] = borderWithout(imgPoint, x, y, X, Y, size, type);
				break;
			case lab1::TYPE_BORDER_BLACK:
				imageOut[y * width + x] = borderBlack(imgPoint, x, y, X, Y, size, type);
				break;
			case lab1::TYPE_BORDER_WRAPPING:
				imageOut[y * width + x] = borderWrapping(imgPoint, x, y, X, Y, size, type);
				break;
			case lab1::TYPE_BORDER_MIRROR:
				imageOut[y * width + x] = borderMirror(imgPoint, x, y, X, Y, size, type);
				break;
			default:

				break;
			}
		}
	}

	return imageOut;
}

/**
* Режим обработки краев "зеркалированием"
*/
int lab1::borderMirror(int *imgPoint, int x, int y, double X[], double Y[], int size, int type)
{
	int aura = size / 2;
	int width = widthImg - 1;
	int height = heightImg - 1;
	int Gx = 0;
	int Gy = 0;
	int G;
	int point;
	int pointX;
	int pointY;
	int *SV = new int[size];
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

		point = imgPoint[pointY * width + pointX];

		if (type == lab1::SVERTKA) {
			Gx += point * X[i];
			Gy += point * Y[i];
		}
		else if (type == lab1::SEPAR) {
			SV[n] += imgPoint[point] * X[m];
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
int lab1::borderWrapping(int *imgPoint, int x, int y, double X[], double Y[], int size, int type)
{
	int aura = size / 2;
	int width = widthImg - 1;
	int height = heightImg - 1;
	int Gx = 0;
	int Gy = 0;
	int G;
	int point;
	int pointX;
	int pointY;
	int *SV = new int[size];
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

		point = imgPoint[pointY * width + pointX];

		if (type == lab1::SVERTKA) {
			Gx += point * X[i];
			Gy += point * Y[i];
		}
		else if (type == lab1::SEPAR) {
			SV[n] += imgPoint[point] * X[m];
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
int lab1::borderBlack(int *imgPoint, int x, int y, double X[], double Y[], int size, int type)
{
	int aura = size / 2;
	int width = widthImg - 1;
	int height = heightImg - 1;
	bool isBlack = false;
	int Gx = 0;
	int Gy = 0;
	int G;
	int point; 
	int *SV = new int[size];
	SV[0] = 0;

	for (int n = 0, m = 0, i = 0, Xz = -1 * aura, Yz = -1 * aura; i < pow(size, 2); i++, Xz++, m++) {
		point = (y + Yz) * width + (x + Xz);

		if ((x + Xz) < aura || (y + Yz) < aura || (x + Xz) > width - aura || (y + Yz) > height - aura) {
			isBlack = true;
		} else {
			isBlack = false;
		}		

		if (type == lab1::SVERTKA) {
			Gx += isBlack ? 0 : imgPoint[point] * X[i];
			Gy += isBlack ? 0 : imgPoint[point] * Y[i];
		}
		else if (type == lab1::SEPAR) {
			SV[n] += isBlack ? 0 : imgPoint[point] * X[m];
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
int lab1::borderWithout(int *imgPoint, int x, int y, double X[], double Y[], int size, int type)
{
	int aura = size / 2;
	int width = widthImg - 1;
	int height = heightImg - 1;

	if (x < aura || y < aura || x > width - aura || y > height - aura) {
		return 255;
	}

	int Gx = 0;
	int Gy = 0;
	int G = 0;
	int point;

	int *SV = new int[size];
	SV[0] = 0;

	for (int n = 0, m = 0, i = 0, Xz = -1 * aura, Yz = -1 * aura; i < pow(size, 2); i++, Xz++, m++) {
		point = (y + Yz) * width + (x + Xz);

		if (type == lab1::SVERTKA) {
			Gx += imgPoint[point] * X[i];
			Gy += imgPoint[point] * Y[i];
		}
		else if (type == lab1::SEPAR) {
			SV[n] += imgPoint[point] * X[m];
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
int *lab1::loadImage(String^ name)
{
	Bitmap ^image = gcnew Bitmap(name, true);
	widthImg = image->Width;
	heightImg = image->Height;

	// create array
	int *imgPoint = new int[widthImg * heightImg];

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

	return imgPoint;
}