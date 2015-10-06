#pragma once
#ifndef _Element_h
#define _Element_h

#include <stdio.h>
#include "Image.h"
#include "LoaderImage.h"

class Element {
public:
	Element(Image *image, int x, int y) {
		this->image = image;
		this->x = x;
		this->y = y;
		
	}
	Element() {}
	void setImage(Image *image) {
		this->image = image;
	}
	Image* getImage() {
		return this->image;
	}
	int getWidth() {
		return this->image->getWidth();
	}
	int getHeight() {
		return this->image->getHeight();
	}
	/*
	Image *updateLayers(Image *realBack,int vel){
		int xB =+ (vel*0.33);
		int yB =+ (vel*0.33);
		int xF =+ (vel*0.66);
		int yF =+ (vel*0.66);

		background->plotImage(realBack,xB, yB);
		foreground->plotImage(background, xF, yF);
		
		return background;
	}
	*/
	
	
	/*void view() {

		int xI = 0;
		int xF = image->getWidth;
		for (int i = 0; i < image->getWidth()*image->getHeight(); i++) {
			if (i = xF) {
				i += i - (image->getWidth());
				xF += (image->getWidth());
			}
			int x = i % image->getWidth();
			int y = i / image->getWidth();
			int test = image->getPixel(x, y);
			image->setPixels(test, x, y);

		}
		 while (xF != image->getWidth())
		 {
		 xI += 2;
		 xF += 2;

		 }
	}*/


private:
	Image *image;
	int z = 0;
	int y = 0;
	int x = 0;

};

#endif