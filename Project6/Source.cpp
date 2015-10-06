#include<Windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>
#include <cstdio>
#include <stdio.h>
#include <math.h>
#include "Image.h"
#include "Element.h"
#include "LoaderImage.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int winWidth = 600, winHeight = 480;
Image *image = new Image(winWidth, winHeight);

Image *frame_1 = NULL;
Image *frame_2 = NULL;
Image *frame_3 = NULL;
Image *frame_4 = NULL;

Image *layer = NULL;
Image *teste = NULL;

Image *train = NULL;
Image *sprite[5];

Image *sol = NULL;

int xB = winWidth; //definir para ver aonde estaremos pegando a imagem primeiramemte
int yB = winHeight; //definir para ver aonde estaremos pegando a imagem primeiramemte
int xF = winWidth; //definir para ver aonde estaremos pegando a imagem primeiramemte
int yF = winHeight; //definir para ver aonde estaremos pegando a imagem primeiramemte

int vel = 1;
int posSprite = 2;
int posCactos = 800;
int posCactos2 = 400;
int posMont = 1000;
float posSol = 850;
int posAguia = 100;
int posSnake = 200;
int posChao = 800;
int gravity = 0;
int contador = -1;
int pontos = 0;
bool inicia = false;
int maiorPont = 0;

Image *background; //primeiro layer sendo o background
Image *cacto;
Image *cactos;
Image *foreground; //segundo layer
Image *montanha;
Image *chao;
Image *gameOver;
Image *start;
Image *aguia[4];
Image *snake[3];
void escreve(int width, int height, int x, int y, void *font, string texto) {
	float xxx = (float)x / width;
	float yyy = (float)y / height;
	glColor3f(0, 0, 0);
	glRasterPos2f(xxx, yyy);
	for (int i = 0; i<texto.length(); i++)
		glutBitmapCharacter(font, texto.at(i));
}

void setInicial() {
	vel = 1;
	posSprite = 2;
	posCactos = 800;
	posCactos2 = 400;
	posMont = 1000;
	posSol = 850;
	posAguia = 100;
	posSnake = 200;
	posChao = 800;
	gravity = 0;
	contador = -1;
	pontos = 0;
	inicia = false;
}

void drawImage(Image *image) {
	glDrawPixels(image->getWidth(), image->getHeight(), GL_BGRA_EXT, GL_UNSIGNED_BYTE, image->getPixels());
	glFlush();
}
int i = 0;
void movimentaSprite(Image *imagem, int numeroImagens, int gravity) {
	i = (i + 1) % numeroImagens;
	image->plotImage(sprite[i], posSprite,8 + gravity);
	if (posSprite > 150)
		posSprite--;
	pontos++;
	if (maiorPont < pontos) {
		maiorPont = pontos;
	}
}
int si = 0;
void movimentaSnake(Image *imagem, int numeroImagens) {
	si = (si + 1) % numeroImagens;
	image->plotImage(snake[si], posSnake, 8);
	posSnake -= (2 * vel); 
	if (posSnake <0)
		posSnake = 800;
}
int ai = 0;
void movimentaAguia(Image *imagem, int numeroImagens) {
	ai = (ai + 1) % numeroImagens;
	image->plotImage(aguia[ai], posAguia, 80);
	posAguia++;
	if (posAguia == 800)
		posAguia = 0;
}
void movimentaCacto(Image *cacto) {
	image->plotImage(cacto, posCactos, 8);
	posCactos -= 2 * vel;
	posCactos--;
	if (posCactos < 0) {
		posCactos = 800;
		vel += 1;
	}
}
void movimentaCactos(Image *cacto) {
	image->plotImage(cacto, posCactos2, 8);
	posCactos2 -= 2 * vel;
	posCactos2--;
	if (posCactos2 < 0) {
		posCactos2 = 600;
	}
}
void movimentaMontanha(Image *montanha) {
	image->plotImage(montanha, posMont, 10);
	posMont -= 0.1;
	if (posMont < 0) {
		posMont = 1000;
	}
}
void movimentaSol(Image *sol) {
	image->plotImage(sol, posSol, 100);
	posSol -= 0.001;
	if (posSol == 0) {
		posSol = 600;
	}
}
void movimentaChao(Image *chao) {
	image->plotImage(chao, posChao,0);
	posChao -= 1*vel;
	if (posChao < 0) {
		posChao = 800;
	}
}
void timer(int v) {
	glutPostRedisplay();
	glutTimerFunc(10, timer, 1);
}
void perdeu() {
	if (posSprite == posCactos && gravity < 50 || posSprite > posCactos - 5 && posSprite < posCactos + 5 && gravity < 40) {
		image->plotImage(gameOver, 10, 10);
		inicia = false;
		pontos = 0;
		setInicial();
	}
	else if (posSprite == posSnake && gravity < 40 || posSprite > posSnake - 5 && posSprite < posSnake + 5 && gravity < 40) {
		image->plotImage(gameOver, 10, 10);
		inicia = false;
		pontos = 0;
		setInicial();
	}
	else if (posSprite > posAguia - 3 && posSprite < posAguia + 3 && gravity > 40) {
		image->plotImage(gameOver, 10, 10);
		inicia = false;
		pontos = 0;
		setInicial();
	}else if (posSprite == posCactos2 && gravity < 50 || posSprite > posCactos2 - 5 && posSprite < posCactos2 + 5 && gravity < 40) {
		image->plotImage(gameOver, 10, 10);
		inicia = false;
		pontos = 0;
		setInicial();
	}
}
int desce = 0;
void jump() {
	if (gravity > 20) {
		cout << "Trapaceando!";
	}
	else {
		gravity += 20;
		posSprite += 5;
		gravity += 20;
		posSprite += 5;
		gravity += 20;
		posSprite += 5;
		gravity += 20;
		posSprite += 5;
		contador = 10;
	}
	desce = (gravity / contador)+0.9;
}
void ChangeSize(int w, int h) {
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	winWidth = w;
	winHeight = h;

	glViewport(0, 0, w, h);

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set the clipping volume
	gluOrtho2D(0.0f, (GLfloat)w, 0.0, (GLfloat)h);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void init(void) {
	// Black background.
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// Targa's are 1 byte aligned
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	layer = LoaderImage::loadImage("fundo.ptm");
	train = LoaderImage::loadImage("train2.ptm");
	image = LoaderImage::loadImage("fundo.ptm");
	cacto = LoaderImage::loadImage("Cactus.ptm");
	cactos = LoaderImage::loadImage("Cactus2.ptm");
	montanha = LoaderImage::loadImage("rochas.ptm");
	sol = LoaderImage::loadImage("novoSol.ptm");
	chao = LoaderImage::loadImage("deserto.ptm");
	gameOver = LoaderImage::loadImage("gameOver.ptm");
	start = LoaderImage::loadImage("start.ptm");
	//aguia
	aguia[0] = LoaderImage::loadImage("aguia\\aguia_1.ptm");
	aguia[1] = LoaderImage::loadImage("aguia\\aguia_2.ptm");
	aguia[2] = LoaderImage::loadImage("aguia\\aguia_3.ptm");
	aguia[3] = LoaderImage::loadImage("aguia\\aguia_4.ptm");
	//snake
	snake[0] = LoaderImage::loadImage("snake\\snake_1.ptm");
	snake[1] = LoaderImage::loadImage("snake\\snake_2.ptm");
	snake[2] = LoaderImage::loadImage("snake\\snake_3.ptm");
	//dragon
	sprite[0] = LoaderImage::loadImage("sprites3\\frames_1.ptm");
	sprite[1] = LoaderImage::loadImage("sprites3\\frames_2.ptm");
	sprite[2] = LoaderImage::loadImage("sprites3\\frames_3.ptm");
	sprite[3] = LoaderImage::loadImage("sprites3\\frames_4.ptm");
	sprite[4] = LoaderImage::loadImage("sprites3\\frames_5.ptm");
	//sprite[5] = LoaderImage::loadImage("sprites3\\sprite_7.ptm");

}
void finish(void) {
	if (image != NULL) {
		delete(image);
		delete(montanha);
		delete(sol);
		delete(*sprite);
		delete(*aguia);
		delete(*snake);
	}
}
int t = winWidth;
int s = 0;
void limpaCena(int teste) {
	int i = teste;
	for (i; i < (layer->getWidth() * (layer->getHeight())); i++)
	{
		if (i == t) {
			i += (layer->getWidth() - i);
			t += layer->getWidth();
			s++;
		}
		int x = i % layer->getWidth();
		int y = i / layer->getWidth();
		int test = layer->getPixel(x, y);
		image->setPixels(test, x, y);
	}
}
void RenderScene(void) {
	if (inicia == true) {
		// Clear the window with current clearing color
		glClear(GL_COLOR_BUFFER_BIT);
		// Use Window coordinates to set raster position

		glRasterPos2i(0, 0);

		limpaCena(1);
		movimentaSol(sol);
		movimentaMontanha(montanha);
		movimentaCacto(cacto);
		movimentaCactos(cactos);
		movimentaSprite(*sprite, 5, gravity);
		movimentaAguia(*aguia, 4);
		movimentaSnake(*snake, 3);
		movimentaChao(chao);
		perdeu();
		if (contador > 0) {
			gravity -= desce;
			contador--;
		}		
		string pontuacao;
		stringstream ss;
		ss << "Pontuacao: " << pontos << "    Maior Pontuacao: " << maiorPont;
		pontuacao = ss.str();
		drawImage(image);
		escreve(600, 480, 50, 30, GLUT_BITMAP_HELVETICA_18, pontuacao);
		glFlush();
		glutSwapBuffers();

	}
	timer(0);
}
void keyboard(unsigned char key, int x, int y) {
	if (key == 's') {
		inicia = true;
	}
	if (key == 'j') {
		jump();
	}
	else if (key == 'q') {
		finish();
		exit(0);
	}
	else if (key == 't') {
		cout << " Aguia ";
		cout << posAguia;
		cout << " sprite ";
		cout << posSprite;
		cout << " cacto ";
		cout << posCactos;
		cout << " Cactos ";
		cout << posCactos2;
		cout << " Cobra ";
		cout << posCactos;
		cout << " Chao ";
		cout << posChao;

	}
	glutSwapBuffers();
}
int main(int argc, char* argv[]) {
	// inicialização da glut
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GL_DOUBLE);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Jogo");

	// especifica qual a função que trata da alteração da janela
	glutReshapeFunc(ChangeSize);

	// especifica qual é a função de renderização da tela
	glutDisplayFunc(RenderScene);

	// especifica qual é a função de tratamento de eventos de teclado
	glutKeyboardFunc(keyboard);
	//glutTimerFunc(30, timer, 1);
	// carrega imagem para a memória
	// iniciliza parâmetros
	init();


	// inicia looping do OpenGL
	glutMainLoop();

	// limpa memória ao final do looping
	finish();

	return 0;
}
