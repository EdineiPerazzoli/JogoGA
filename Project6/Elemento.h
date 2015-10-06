#include <stdio.h>
#include "Image.h"
#include "LoaderImage.h"

class Elemento {
public:

	Image* movimentaImagem() {
		background->plotImage(background, xMov + (velocidade*0.35), yMov + (velocidade*0.35));
		background->plotImage(foreground, xMov + (velocidade*0.65), yMov + (velocidade*0.65));
		return background;
		
	}

	Image* recortaImagem(Image *imagem) {
		for (int i = 0; i < imagem->getWidth()*imagem->getHeight(); i++) {
			if (i = xFinal) {
				i += i - (imagem->getWidth());
			}
			int x = i % imagem->getWidth();
			int y = i / imagem->getWidth();
			Image* novaRecortada;
			novaRecortada->setPixels(imagem->getPixel(x, y), x , y);
		}
	}

private:
	Image* foreground;
	Image* background;
	int xInicial = 1;
	int xFinal = 480;
	int xMov;
	int yMov;
	int velocidade;
};

