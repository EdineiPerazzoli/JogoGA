#pragma once

#ifndef _LoaderImage_
#define _LoaderImage_

#include <fstream>
#include <math.h>
#include "Image.h"

using namespace std;

class LoaderImage {
public:
	static Image* loadImage(char const *path) {
		char *IMAGES_PATH = "jogo\\";
		char str[300];
		strcpy_s(str, IMAGES_PATH);
		strcat_s(str, path);
		ifstream arq(str);
		char BUFFER[256];
			
		int w, h, max;
		arq >> BUFFER;

		arq >> w >> h;
		arq >> max;

		Image *image = new Image(w, h);
		for (int i = 0; i < w * h; i++) {
			int a, r, g, b;
			arq >> a >> r >> g >> b;
			int x = i % w;
			int y = i / w;
			y = h - y - 1;
			int pixel = (a << 24) | (r << 16) | (g << 8) | b;
			image->setPixels(pixel, x, y);
		}
		return image;
	}

};

#endif /* defined(_LoaderImage_) */
