#pragma once


#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED



class Image {
public:
	Image(int w, int h) {
		width = w;
		height = h;
		pixels = new int[w*h];
	}
	~Image() {
		delete pixels;
	}
	void setPixels(int rgb, int x, int y) {
		pixels[(y * width) + x] = rgb;
	}
	int getPixel(int x, int y) {
		return pixels[(y * width) + x];
	}
	int getWidth() {
		return width;
	}
	int getHeight() {

		return height;
	}
	int *getPixels() {
		return pixels;
	}
	void setARGB(int argb, int x, int y) {
		pixels[x + y*width] = argb;
	}
	int getARGB(int x, int y) {
		return pixels[x + y*width];
	}
	void dropPixels() {//da uma zerada nos pixels
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				setPixels(0, i, j);
			}
		}
	}
	void plotImage(Image *foreground, int xi, int yi) { //verificar com o professor

		for (int i = 0; i < foreground->getWidth() * foreground->getHeight(); i++) {
			int x = i % foreground->getWidth();
			int y = i / foreground->getWidth();
			int argb = foreground->getPixel(x, y);
			x += xi;
			y += yi;
			int a = (argb >> 24) & 0xff;
			if (a == 0) {
				continue;
			}
			else if (a == 255) {
				this->setPixels(argb, x, y);
			}
			else {
				int r = ((foreground->getPixel(x, y)) >> 16) & 0xff;
				int g = ((foreground->getPixel(x, y)) >> 8) & 0xff;
				int b = (foreground->getPixel(x, y)) & 0xff;

				int aThis = ((this->getPixel(x, y)) >> 24) & 0xff;
				int rThis = ((this->getPixel(x, y)) >> 16) & 0xff;
				int gThis = ((this->getPixel(x, y)) >> 8) & 0xff;
				int bThis = (this->getPixel(x, y)) & 0xff;

				int calcr = (rThis*(1 - a) + r*a);
				int calcg = (gThis*(1 - a) + r*a);
				int calcb = (bThis*(1 - a) + r*a);
				int argb = (255 << 24) | (calcr << 16) | (calcg << 8) | (calcb);
				this->setPixels(argb, x, y);
			}
		}
	}
	void plotInt(Image *foreground, int xi, int yi, int largura, int altura) {
		for (int i = 0; i < largura * altura; i++) {
			int x = i % largura;
			int y = i / largura;
			x = +xi;
			y = +yi;
			int argb = foreground->getPixel(x, y);
			int a = (argb >> 24) & 0xff;
			if (a == 0) {
				continue;

			}
			else if (a = 255) {
				setARGB(a, x, y);

			}
			else {
				int r = ((foreground->getPixel(x, y)) >> 16) & 0xff;
				int g = ((foreground->getPixel(x, y)) >> 8) & 0xff;
				int b = (foreground->getPixel(x, y)) & 0xff;

				int aThis = ((this->getPixel(x, y)) >> 24) & 0xff;
				int rThis = ((this->getPixel(x, y)) >> 16) & 0xff;
				int gThis = ((this->getPixel(x, y)) >> 8) & 0xff;
				int bThis = (this->getPixel(x, y)) & 0xff;

				int calcr = (rThis*(1 - a) + r*a);
				int calcg = (gThis*(1 - a) + r*a);
				int calcb = (bThis*(1 - a) + r*a);
				int argb = (255 << 24) | (calcr << 16) | (calcg << 8) | (calcb);
				this->setPixels(argb, x, y);
			}
		}
	}

	Image *original(Image *layer, Image *two, int xF) {
		for (int i = 0; i < (layer->getWidth() * (two->getHeight())); i++)
		{
			if (i == xF) {
				i += (layer->getWidth() - i);
			}
			int x = i % layer->getWidth();
			int y = i / layer->getWidth();
			int test = layer->getPixel(x, y);
			this->setARGB(test, x, y);
		}
		return this;
	}

	
	Image *cutImage(Image *foreground, int xi, int xf) {
		for (int i = 0; i < (foreground->getWidth() * (foreground->getHeight())); i++)
		{
			if (i == xf) {
				i += (foreground->getWidth() - i);
				xf += foreground->getWidth();
			}
			int x = i % foreground->getWidth();
			int y = i / foreground->getWidth();
			int test = foreground->getPixel(x, y);
			this->setARGB(test, x, y);
		}
		return this;
	}

	


private:
	int *pixels;
	int width, height;
	int matriz[1000][250];
};

#endif