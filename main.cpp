#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <stdbool.h>


float velocidadRocas = 20;

float capi_posicionX = 0;
const float sueloY = 0;
float capi_posicionY = sueloY;

float capi_ancho = 20;
float capi_alto  = 20;
float capi_offsetX = -60;
float capi_offsetY = -35;

float roca_ancho = 10;
float roca_alto  = 10;

float r1_posicionX = 46;
float r1_posicionY = -40;
float r2_posicionX = 100;
float r2_posicionY = -45;

bool capi_saltando = false;
float capi_velocidadY = 0;
float capi_velocidadX = 0;
float gravedad = -0.5;

bool detectarColisionBox(float x1, float y1, float ancho1, float alto1,
						 float x2, float y2, float ancho2, float alto2) {
return (fabs(x1 - x2) * 2 < (ancho1 + ancho2)) &&
	(fabs(y1 - y2) * 2 < (alto1  + alto2));
} 
 
void verificarColisiones() {
	if (detectarColisionBox(capi_posicionX + capi_offsetX,
							capi_posicionY + capi_offsetY,
							capi_ancho, capi_alto,
							r1_posicionX, r1_posicionY, roca_ancho, roca_alto)) {
		printf("Colision con roca 1\n");
		exit(0);
	}
	if (detectarColisionBox(capi_posicionX + capi_offsetX,
							capi_posicionY + capi_offsetY,
							capi_ancho, capi_alto,
							r2_posicionX, r2_posicionY, roca_ancho, roca_alto)) {
		printf("Colision con roca 2\n");
		exit(0);
	}
}
 
void inicializar() {
	glClearColor(226.0/255.0, 244.0/255.0, 253.0/255.0, 0);
}
 
void redimensionar(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-76, 76, -50, 50, -1, 1);
}
 
void circulo(float cx, float cy, float r, int segmentos,
			float rR, float gR, float bR) {
	glColor3f(rR, gR, bR);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(cx, cy);
	for (int i = 0; i <= segmentos; i++) {
		float ang = 2 * M_PI * i / segmentos;
		float x = cx + r * cos(ang);
		float y = cy + r * sin(ang);
		glVertex2f(x, y);
	}
	glEnd();
}

void nubes(float x, float y) { 
	float r = 0.95, g = 0.98, b = 0.99;
	float br = 0.6, bg = 0.6, bb = 0.6;
	circulo(x,     y,     6, 30, r, g, b);
	circulo(x + 5, y + 2, 6.5, 30, r, g, b);
	circulo(x + 10,y,     6, 30, r, g, b);
	circulo(x + 5, y - 2, 5.5, 30, r, g, b);
}

void sol() {
	//sol
	glBegin(GL_TRIANGLES);
	glColor3ub(255,216,23);
	glVertex2f(72, 50);
	glVertex2f(76, 50);
	glVertex2f(76, 48);
	glEnd();
	
	glBegin(GL_TRIANGLES);
	glColor3ub(255,158,2);
	glVertex2f(72, 50);
	glVertex2f(76, 48);
	glVertex2f(74, 46);
	glEnd();
	
	glBegin(GL_TRIANGLES);
	glColor3ub(255,172,26);
	glVertex2f(72, 50);
	glVertex2f(74, 46);
	glVertex2f(70, 46);
	glEnd();
	
	glBegin(GL_TRIANGLES);
	glColor3ub(255,117,0);
	glVertex2f(76, 48);
	glVertex2f(76, 41.5);
	glVertex2f(74, 46);
	glEnd();
	
	glBegin(GL_TRIANGLES);
	glColor3ub(255,127,0);
	glVertex2f(74, 46);
	glVertex2f(70, 46);
	glVertex2f(72, 42);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3ub(255,92,1);
	glVertex2f(69, 50);
	glVertex2f(72, 50);
	glVertex2f(70, 46);
	glVertex2f(69, 49);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3ub(255,92,1);
	glVertex2f(72, 42);
	glVertex2f(74, 46);
	glVertex2f(76, 41.5);
	glVertex2f(75, 41);
	glEnd();
	
	//rayos
	glBegin(GL_TRIANGLES);
	glColor3ub(255,158,2);
	glVertex2f(64, 50);
	glVertex2f(66, 50);
	glVertex2f(67, 48);
	glEnd();
	
	glBegin(GL_TRIANGLES);
	glColor3ub(253,195,26);
	glVertex2f(67, 48);
	glVertex2f(68, 50);
	glVertex2f(64, 50);
	glEnd();
	
	glBegin(GL_TRIANGLES);
	glColor3ub(255,117,2);
	glVertex2f(64, 42);
	glVertex2f(65.5, 44);
	glVertex2f(68, 42);
	glEnd();
	
	glBegin(GL_TRIANGLES);
	glColor3ub(254,168,2);
	glVertex2f(65.5, 44);
	glVertex2f(68, 42);
	glVertex2f(68, 44);
	glEnd();
	
	glBegin(GL_TRIANGLES);
	glColor3ub(253,195,26);
	glVertex2f(65.5, 44);
	glVertex2f(68, 47);
	glVertex2f(68, 44);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3ub(255,195,26);
	glVertex2f(68, 47);
	glVertex2f(70, 42);
	glVertex2f(68, 42);
	glVertex2f(68, 44);
	glEnd();
	
	glBegin(GL_TRIANGLES);
	glColor3ub(229,151,7);
	glVertex2f(72, 40.5);
	glVertex2f(74, 38);
	glVertex2f(76, 39.5);
	glEnd();
	
	glBegin(GL_TRIANGLES);
	glColor3ub(254,174,26);
	glVertex2f(72, 40.5);
	glVertex2f(72.5, 37);
	glVertex2f(74, 38);
	glEnd();
	
	glBegin(GL_TRIANGLES);
	glColor3ub(255,127,2);
	glVertex2f(72.5, 37);
	glVertex2f(74, 38);
	glVertex2f(73.5, 35);
	glEnd();
	
	glBegin(GL_TRIANGLES);
	glColor3ub(255,158,1);
	glVertex2f(74, 38);
	glVertex2f(73.5, 35);
	glVertex2f(76, 39.5);
	glEnd();
}

void montanas() {
	//1
	glColor3f(0.70, 0.60, 0.82);
	glBegin(GL_POLYGON);
	glVertex2f(-76, 14.9);
	glVertex2f(-73.5, 16.9);
	glVertex2f(-70.5, 14.9);
	glVertex2f(-76, 11.9);
	glEnd();
	
	glColor3f(0.55, 0.45, 0.70);
	glBegin(GL_POLYGON);
	glVertex2f(-76, 5.9);
	glVertex2f(-70.5, 14.9);
	glVertex2f(-76, 11.9);
	glEnd();
	
	glColor3f(0.70, 0.60, 0.82);
	glBegin(GL_POLYGON);
	glVertex2f(-76, 5.9);
	glVertex2f(-70.5, 14.9);
	glVertex2f(-76, -10.1);
	glEnd();
	
	glColor3f(0.55, 0.45, 0.70);
	glBegin(GL_POLYGON);
	glVertex2f(-76, -10.1);
	glVertex2f(-70.5, 14.9);
	glVertex2f(-67.5, -10.1);
	glVertex2f(-71.5, -11.1);
	glEnd();
	
	glColor3f(0.70, 0.60, 0.82);
	glBegin(GL_POLYGON);
	glVertex2f(-67.5, -10.1);
	glVertex2f(-68.3, -4.1);
	glVertex2f(-63.5, 7.9);
	glVertex2f(-61.5, -5.1);
	glVertex2f(-63.5, -8.1);
	glEnd();
	
	glColor3f(0.55, 0.45, 0.70);
	glBegin(GL_POLYGON);
	glVertex2f(-68.3, -4.1);
	glVertex2f(-70.5, 14.9);
	glVertex2f(-63.5, 7.9);
	glEnd();
	
	glColor3f(0.70, 0.60, 0.82);
	glBegin(GL_POLYGON);
	glVertex2f(-70.5, 14.9);
	glVertex2f(-56.5, 27.9);
	glVertex2f(-63.5, 7.9);
	glEnd();
	
	glColor3f(0.55, 0.45, 0.70);
	glBegin(GL_POLYGON);
	glVertex2f(-61.5, -5.1);
	glVertex2f(-63.5, 7.9);
	glVertex2f(-52.5, 14.9);
	glEnd();
	
	glColor3f(0.70, 0.60, 0.82);
	glBegin(GL_POLYGON);
	glVertex2f(-63.5, 7.9);
	glVertex2f(-56.5, 27.9);
	glVertex2f(-52.5, 14.9);
	glEnd();
	
	glColor3f(0.55, 0.45, 0.70);
	glBegin(GL_POLYGON);
	glVertex2f(-63.5, -8.1);
	glVertex2f(-61.5, -5.1);
	glVertex2f(-58.5, -8.1);
	glEnd();
	
	glColor3f(0.70, 0.60, 0.82);
	glBegin(GL_POLYGON);
	glVertex2f(-61.5, -5.1);
	glVertex2f(-63.5, 7.9);
	glVertex2f(-52.5, 14.9);
	glEnd();
	
	glColor3f(0.55, 0.45, 0.70);
	glBegin(GL_POLYGON);
	glVertex2f(-61.5, -5.1);
	glVertex2f(-52.5, 14.9);
	glVertex2f(-53.5, -7.1);
	glVertex2f(-58.5, -8.1);
	glEnd();
	
	glColor3f(0.70, 0.60, 0.82);
	glBegin(GL_POLYGON);
	glVertex2f(-53.5, -7.1);
	glVertex2f(-52.5, 14.9);
	glVertex2f(-46.5, -2.1);
	glEnd();
	
	glColor3f(0.55, 0.45, 0.70);
	glBegin(GL_POLYGON);
	glVertex2f(-46.5, -2.1);
	glVertex2f(-52.5, 14.9);
	glVertex2f(-33.5, 0);
	glVertex2f(-38.5, 2.9);
	glEnd();
	
	glColor3f(0.70, 0.60, 0.82);
	glBegin(GL_POLYGON);
	glVertex2f(-33.5, 0);
	glVertex2f(-52.5, 14.9);
	glVertex2f(-47.5, 16.9);
	glEnd();
	
	glColor3f(0.55, 0.45, 0.70);
	glBegin(GL_POLYGON);
	glVertex2f(-33.5, 0);
	glVertex2f(-56.5, 27.9);
	glVertex2f(-52.5, 14.9);
	glEnd();
	
	glColor3f(0.70, 0.60, 0.82);
	glBegin(GL_POLYGON);
	glVertex2f(-33.5, 0);
	glVertex2f(-47.5, 16.9);
	glVertex2f(-34.5, 8.9);
	glEnd();
	
	glColor3f(0.55, 0.45, 0.70);
	glBegin(GL_POLYGON);
	glVertex2f(-34.5, 8.9);
	glVertex2f(-47.5, 16.9);
	glVertex2f(-43.5, 21.9);
	glEnd();
	
	glColor3f(0.70, 0.60, 0.82);
	glBegin(GL_POLYGON);
	glVertex2f(-33.5, 0);
	glVertex2f(-34.5, 8.9);
	glVertex2f(-19.5, 2.9);
	glEnd();
	
	glColor3f(0.55, 0.45, 0.70);
	glBegin(GL_POLYGON);
	glVertex2f(-33.5, 0);
	glVertex2f(-34.5, 8.9);
	glVertex2f(-23.5, -5.1);
	glEnd();
	
	glColor3f(0.70, 0.60, 0.82);
	glBegin(GL_POLYGON);
	glVertex2f(-34.5, 8.9);
	glVertex2f(-23.5, 20.9);
	glVertex2f(-19.5, 2.9);
	glEnd();
	
	glColor3f(0.55, 0.45, 0.70);
	glBegin(GL_POLYGON);
	glVertex2f(-33.5, 0);
	glVertex2f(-19.5, 2.9);
	glVertex2f(-23.5, -5.1);
	glEnd();
	
	glColor3f(0.70, 0.60, 0.82);
	glBegin(GL_POLYGON);
	glVertex2f(-23.5, -5.1);
	glVertex2f(-19.5, 2.9);
	glVertex2f(-10, 4.9);
	glEnd();
	
	glColor3f(0.55, 0.45, 0.70);
	glBegin(GL_POLYGON);
	glVertex2f(-23.5, -5.1);
	glVertex2f(-10, 4.9);
	glVertex2f(-19.5, -6.9);
	glEnd();
	
	glColor3f(0.70, 0.60, 0.82);
	glBegin(GL_POLYGON);
	glVertex2f(-10, 4.9);
	glVertex2f(-9.5, 18.9);
	glVertex2f(-2.5, 2.5);
	glVertex2f(-6.5, -0.1);
	glEnd();
	
	glColor3f(0.55, 0.45, 0.70);
	glBegin(GL_POLYGON);
	glVertex2f(-18.5, 13.9);
	glVertex2f(-9.5, 18.9);
	glVertex2f(-10, 4.9);
	glEnd();
	
	glColor3f(0.70, 0.60, 0.82);
	glBegin(GL_POLYGON);
	glVertex2f(-19.5, 2.9);
	glVertex2f(-18.5, 13.9);
	glVertex2f(-10, 4.9);
	glEnd();
	
	glColor3f(0.55, 0.45, 0.70);
	glBegin(GL_POLYGON);
	glVertex2f(-19.5, 2.9);
	glVertex2f(-23.5, 20.9);
	glVertex2f(-18.5, 13.9);
	glEnd();
	
	glColor3f(0.70, 0.60, 0.82);
	glBegin(GL_POLYGON);
	glVertex2f(-18.5, 13.9);
	glVertex2f(-23.5, 20.9);
	glVertex2f(-14.5, 27.9);
	glEnd();
	
	glColor3f(0.55, 0.45, 0.70);
	glBegin(GL_POLYGON);
	glVertex2f(-18.5, 13.9);
	glVertex2f(-14.5, 27.9);
	glVertex2f(-9.5, 18.9);
	glEnd();
	
	glColor3f(0.70, 0.60, 0.82);
	glBegin(GL_POLYGON);
	glVertex2f(-2.5, 2.5);
	glVertex2f(-9.5, 18.9);
	glVertex2f(-6.5, 20.9);
	glEnd();
	
	glColor3f(0.55, 0.45, 0.70);
	glBegin(GL_POLYGON);
	glVertex2f(-2.5, 2.5);
	glVertex2f(2, 4.9);
	glVertex2f(3.5, 7.9);
	glVertex2f(-6.5, 20.9);
	glEnd();
	
	//2
	glColor3f(0.55, 0.78, 0.94);
	glBegin(GL_POLYGON);
	glVertex2f(-19.5, -6.9);
	glVertex2f(-17.5, -7.9);
	glVertex2f(-6.5, -0.1);
	glVertex2f(-10, 4.9);
	glEnd();
	
	glColor3f(0.40, 0.70, 0.90);
	glBegin(GL_POLYGON);
	glVertex2f(-17.5, -7.9);
	glVertex2f(-6.5, -0.1);
	glVertex2f(-11.5, -11.1);
	glEnd();
	
	glColor3f(0.55, 0.78, 0.94);
	glBegin(GL_POLYGON);
	glVertex2f(-6.5, -0.1);
	glVertex2f(-11.5, -11.1);
	glVertex2f(-6.5, -14.1);
	glEnd();
	
	glColor3f(0.40, 0.70, 0.90);
	glBegin(GL_POLYGON);
	glVertex2f(-6.5, -0.1);
	glVertex2f(-6.5, -14.1);
	glVertex2f(-1.5, -16.1);
	glEnd();
	
	glColor3f(0.55, 0.78, 0.94);
	glBegin(GL_POLYGON);
	glVertex2f(-6.5, -0.1);
	glVertex2f(2.5, 5.9);
	glVertex2f(1.1, -17.1);
	glVertex2f(-1.5, -16.1);
	glEnd();
	
	glColor3f(0.40, 0.70, 0.90);
	glBegin(GL_POLYGON);
	glVertex2f(2.5, 5.9);
	glVertex2f(12.5, 0);
	glVertex2f(4.5, -16.1);
	glVertex2f(1.1, -17.1);
	glEnd();
	
	glColor3f(0.55, 0.78, 0.94);
	glBegin(GL_POLYGON);
	glVertex2f(12.5, 0);
	glVertex2f(18.5, 10.9);
	glVertex2f(11.5, -14.1);
	glVertex2f(4.5, -16.1);
	glEnd();
	
	glColor3f(0.40, 0.70, 0.90);
	glBegin(GL_POLYGON);
	glVertex2f(18.5, 10.9);
	glVertex2f(30.5, 0);
	glVertex2f(23.5, -9.1);
	glVertex2f(11.5, -14.1);
	glEnd();
	
	glColor3f(0.55, 0.78, 0.94);
	glBegin(GL_POLYGON);
	glVertex2f(30.5, 0);
	glVertex2f(38.5, -16.1);
	glVertex2f(33.5, -16.1);
	glVertex2f(23.3, -9.3);
	glEnd();
	
	glColor3f(0.40, 0.70, 0.90);
	glBegin(GL_POLYGON);
	glVertex2f(18.5, 10.9);
	glVertex2f(30.5, 0);
	glVertex2f(23.3, -9.3);
	glVertex2f(11.5, -14.1);
	glEnd();
	
	glColor3f(0.55, 0.78, 0.94);
	glBegin(GL_POLYGON);
	glVertex2f(30.5, 0);
	glVertex2f(36.5, 0);
	glVertex2f(40.5, -16.1);
	glVertex2f(23.3, -9.3);
	glEnd();
	
	glColor3f(0.40, 0.70, 0.90);
	glBegin(GL_POLYGON);
	glVertex2f(36.5, 0);
	glVertex2f(44.5, -9.1);
	glVertex2f(43.5, -17.1);
	glVertex2f(40.5, -16.1);
	glEnd();
	
	glColor3f(0.55, 0.78, 0.94);
	glBegin(GL_POLYGON);
	glVertex2f(44.5, -9.1);
	glVertex2f(50.5, -20.1);
	glVertex2f(43.5, -17.1);
	glEnd();
	
	glColor3f(0.40, 0.70, 0.90);
	glBegin(GL_POLYGON);
	glVertex2f(44.5, -9.1);
	glVertex2f(55.5, 5.99);
	glVertex2f(53.5, -21.1);
	glVertex2f(50.5, -20.1);
	glEnd();
	
	glColor3f(0.55, 0.78, 0.94);
	glBegin(GL_POLYGON);
	glVertex2f(55.5, 5.99);
	glVertex2f(66.5, -7.1);
	glVertex2f(67.5, -25.1);
	glVertex2f(66, -25.1);
	glVertex2f(53.5, -21.1);
	glEnd();
	
	glColor3f(0.40, 0.70, 0.90);
	glBegin(GL_POLYGON);
	glVertex2f(66.5, -7.1);
	glVertex2f(76, -21.1);
	glVertex2f(76, -28.1);
	glVertex2f(67.5, -25.1);
	glEnd();
	
	glColor3f(0.55, 0.78, 0.94);
	glBegin(GL_POLYGON);
	glVertex2f(2.5, 5.9);
	glVertex2f(14.5, 29.9);
	glVertex2f(12.5, 0);
	glEnd();
	
	glColor3f(0.40, 0.70, 0.90);
	glBegin(GL_POLYGON);
	glVertex2f(14.5, 29.9);
	glVertex2f(18.5, 10.9);
	glVertex2f(12.5, 0);
	glEnd();
	
	glColor3f(0.55, 0.78, 0.94);
	glBegin(GL_POLYGON);
	glVertex2f(14.5, 29.9);
	glVertex2f(26.5, 26.9);
	glVertex2f(18.5, 10.9);
	glEnd();
	
	glColor3f(0.40, 0.70, 0.90);
	glBegin(GL_POLYGON);
	glVertex2f(26.5, 26.9);	
	glVertex2f(30.5, 0);
	glVertex2f(18.5, 10.9);
	glEnd();
	
	glColor3f(0.55, 0.78, 0.94);
	glBegin(GL_POLYGON);
	glVertex2f(26.5, 26.9);	
	glVertex2f(36.5, 0);
	glVertex2f(30.5, 0);
	glEnd();
	
	glColor3f(0.40, 0.70, 0.90);
	glBegin(GL_POLYGON);
	glVertex2f(26.5, 26.9);	
	glVertex2f(32.5, 22.9);
	glVertex2f(36.5, 0);
	glEnd();
	
	glColor3f(0.55, 0.78, 0.94);
	glBegin(GL_POLYGON);
	glVertex2f(26.5, 26.9);	
	glVertex2f(39.5, 32.9);
	glVertex2f(32.5, 22.9);
	glEnd();
	
	glColor3f(0.40, 0.70, 0.90);
	glBegin(GL_POLYGON);
	glVertex2f(26.5, 26.9);	
	glVertex2f(40.5, 46.9);
	glVertex2f(39.5, 32.9);
	glEnd();
	
	glColor3f(0.55, 0.78, 0.94);
	glBegin(GL_POLYGON);
	glVertex2f(32.5, 22.9);
	glVertex2f(39.5, 32.9);
	glVertex2f(39.5, 14.9);
	glEnd();
	
	glColor3f(0.40, 0.70, 0.90);
	glBegin(GL_POLYGON);
	glVertex2f(32.5, 22.9);
	glVertex2f(39.5, 14.9);
	glVertex2f(36.5, 0);
	glEnd();
	
	glColor3f(0.55, 0.78, 0.94);
	glBegin(GL_POLYGON);
	glVertex2f(36.5, 0);
	glVertex2f(39.5, 14.9);
	glVertex2f(44.5, -9.1);
	glEnd();
	
	glColor3f(0.40, 0.70, 0.90);
	glBegin(GL_POLYGON);
	glVertex2f(39.5, 14.9);
	glVertex2f(55.5, 5.9);
	glVertex2f(44.5, -9.1);
	glEnd();
	
	glColor3f(0.55, 0.78, 0.94);
	glBegin(GL_POLYGON);
	glVertex2f(39.5, 14.9);
	glVertex2f(39.5, 32.9);
	glVertex2f(62.5, 2.9);
	glVertex2f(55.5, 5.9);
	glEnd();
	
	glColor3f(0.40, 0.70, 0.90);
	glBegin(GL_POLYGON);
	glVertex2f(39.5, 32.9);
	glVertex2f(40.5, 46.9);
	glVertex2f(62.5, 2.9);
	glEnd();
	
	glColor3f(0.55, 0.78, 0.94);
	glBegin(GL_POLYGON);
	glVertex2f(55.5, 5.9);
	glVertex2f(62.5, 2.9);
	glVertex2f(66.5, -8.1);
	glEnd();
	
	glColor3f(0.40, 0.70, 0.90);
	glBegin(GL_POLYGON);
	glVertex2f(62.5, 2.9);
	glVertex2f(69.5, -1.1);
	glVertex2f(66.5, -8.1);
	glEnd();
	
	glColor3f(0.55, 0.78, 0.94);
	glBegin(GL_POLYGON);
	glVertex2f(55.5, 5.9);
	glVertex2f(62.5, 2.9);
	glVertex2f(66.5, -8.1);
	glEnd();
	
	glColor3f(0.40, 0.70, 0.90);
	glBegin(GL_POLYGON);
	glVertex2f(66.5, -8.1);
	glVertex2f(69.5, -1.1);
	glVertex2f(76, -15.1);
	glVertex2f(76, -21.1);
	glEnd();
	
	glColor3f(0.55, 0.78, 0.94);
	glBegin(GL_POLYGON);
	glVertex2f(69.5, -1.1);
	glVertex2f(76, -1.1);
	glVertex2f(76, -15.1);
	glEnd();
	
	glColor3f(0.40, 0.70, 0.90);
	glBegin(GL_POLYGON);
	glVertex2f(69.5, -1.1);
	glVertex2f(72.5, 5.9);
	glVertex2f(76, 3.9);
	glVertex2f(76, -1.1);
	glEnd();
}

void pradera() {
	glColor3f(0.65, 0.85, 0.50);
	glBegin(GL_POLYGON);
	glVertex2f(-76, -10.1);
	glVertex2f(-70.5, -16.1);
	glVertex2f(-76,-19.1);
	glEnd();
	
	glColor3f(0.55, 0.75, 0.40);
	glBegin(GL_POLYGON);
	glVertex2f(-76, -10.1);
	glVertex2f(-71.5, -11.1);
	glVertex2f(-70.5, -16.1);
	glEnd();
	
	glColor3f(0.40, 0.55, 0.25);
	glBegin(GL_POLYGON);
	glVertex2f(-76,-19.1);
	glVertex2f(-70.5, -16.1);
	glVertex2f(-68, -20.1);
	glEnd();
	
	glColor3f(0.65, 0.85, 0.50);
	glBegin(GL_POLYGON);
	glVertex2f(-76,-19.1);
	glVertex2f(-68, -20.1);
	glVertex2f(-76, -22.1);
	glEnd();
	
	glColor3f(0.55, 0.75, 0.40);
	glBegin(GL_POLYGON);
	glVertex2f(-76, -22.1);
	glVertex2f(-68, -20.1);
	glVertex2f(-76, -26.1);
	glEnd();
	
	glColor3f(0.40, 0.55, 0.25);
	glBegin(GL_POLYGON);
	glVertex2f(-76, -26.1);
	glVertex2f(-68, -20.1);
	glVertex2f(-69, -27.1);
	glEnd();
	
	glColor3f(0.65, 0.85, 0.50);
	glBegin(GL_POLYGON);
	glVertex2f(-69, -27.1);
	glVertex2f(-68, -20.1);
	glVertex2f(-62, -26.1);
	glEnd();
	
	glColor3f(0.55, 0.75, 0.40);
	glBegin(GL_POLYGON);
	glVertex2f(-68, -20.1);
	glVertex2f(-59, -25.8);
	glVertex2f(-62, -26.1);
	glEnd();
	
	glColor3f(0.40, 0.55, 0.25);
	glBegin(GL_POLYGON);
	glVertex2f(-68, -20.1);
	glVertex2f(-60.5, -23.1);
	glVertex2f(-59, -25.8);
	glEnd();
	
	glColor3f(0.65, 0.85, 0.50);
	glBegin(GL_POLYGON);
	glVertex2f(-68, -20.1);
	glVertex2f(-66, -14.1);
	glVertex2f(-60.5, -23.1);
	glEnd();
	
	glColor3f(0.55, 0.75, 0.40);
	glBegin(GL_POLYGON);
	glVertex2f(-70.5, -16.1);
	glVertex2f(-66, -14.1);
	glVertex2f(-68, -20.1);
	glEnd();
	
	glColor3f(0.40, 0.55, 0.25);
	glBegin(GL_POLYGON);
	glVertex2f(-70.5, -16.1);
	glVertex2f(-71.5, -11.1);
	glVertex2f(-66, -14.1);
	glEnd();
	
	glColor3f(0.65, 0.85, 0.50);
	glBegin(GL_POLYGON);
	glVertex2f(-71.5, -11.1);
	glVertex2f(-63.5, -8);
	glVertex2f(-66, -14.1);
	glEnd();
	
	glColor3f(0.55, 0.75, 0.40);
	glBegin(GL_POLYGON);
	glVertex2f(-66, -14.1);
	glVertex2f(-63.5, -8);
	glVertex2f(-56, -7.5);
	glEnd();
	
	glColor3f(0.40, 0.55, 0.25);
	glBegin(GL_POLYGON);
	glVertex2f(-66, -14.1);
	glVertex2f(-47.5, -1.8);
	glVertex2f(-48.5, -7.8);
	glEnd();
	
	glColor3f(0.65, 0.85, 0.50);
	glBegin(GL_POLYGON);
	glVertex2f(-47.5, -1.8);
	glVertex2f(-48.5, -7.8);
	glVertex2f(-33.5, 0.1);
	glEnd();
	
	glColor3f(0.55, 0.75, 0.40);
	glBegin(GL_POLYGON);
	glVertex2f(-66, -14.1);
	glVertex2f(-48.5, -7.8);
	glVertex2f(-52, -18.1);
	glEnd();
	
	glColor3f(0.40, 0.55, 0.25);
	glBegin(GL_POLYGON);
	glVertex2f(-66, -14.1);
	glVertex2f(-52, -18.1);
	glVertex2f(-59, -25.8);
	glEnd();
	
	glColor3f(0.65, 0.85, 0.50);
	glBegin(GL_POLYGON);
	glVertex2f(-48.5, -7.8);
	glVertex2f(-33.5, 0.1);
	glVertex2f(-36, -10.1);
	glEnd();
	
	glColor3f(0.55, 0.75, 0.40);
	glBegin(GL_POLYGON);
	glVertex2f(-48.5, -7.8);
	glVertex2f(-36, -10.1);
	glVertex2f(-52, -18.1);
	glEnd();
	
	glColor3f(0.40, 0.55, 0.25);
	glBegin(GL_POLYGON);
	glVertex2f(-52, -18.1);
	glVertex2f(-36, -10.1);
	glVertex2f(-38, -17.1);
	glEnd();
	
	glColor3f(0.65, 0.85, 0.50);
	glBegin(GL_POLYGON);
	glVertex2f(-38, -17.1);
	glVertex2f(-52, -18.1);
	glVertex2f(-59, -25.8);
	glEnd();
	
	glColor3f(0.55, 0.75, 0.40);
	glBegin(GL_POLYGON);
	glVertex2f(-33.5, 0.1);
	glVertex2f(-23.3, -5.1);
	glVertex2f(-36, -10.1);
	glEnd();
	
	glColor3f(0.40, 0.55, 0.25);
	glBegin(GL_POLYGON);
	glVertex2f(-36, -10.1);
	glVertex2f(-23.3, -5.1);
	glVertex2f(-24, -11.1);
	glEnd();
	
	glColor3f(0.65, 0.85, 0.50);
	glBegin(GL_POLYGON);
	glVertex2f(-24, -11.1);
	glVertex2f(-23.3, -5.1);
	glVertex2f(-10.1, -11.5);
	glEnd();
	
	glColor3f(0.40, 0.55, 0.25);
	glBegin(GL_POLYGON);
	glVertex2f(-24, -11.1);
	glVertex2f(-10.1, -11.5);
	glVertex2f(-5, -14.5);
	glEnd();
	
	glColor3f(0.65, 0.85, 0.50);
	glBegin(GL_POLYGON);
	glVertex2f(-24, -11.1);
	glVertex2f(-22, -18.1);
	glVertex2f(-5, -14.5);
	glEnd();
	
	glColor3f(0.40, 0.55, 0.25);
	glBegin(GL_POLYGON);
	glVertex2f(-36, -10.1);
	glVertex2f(-24, -11.1);
	glVertex2f(-22, -18.1);
	glEnd();
	
	glColor3f(0.65, 0.85, 0.50);
	glBegin(GL_POLYGON);
	glVertex2f(-22, -18.1);
	glVertex2f(-5, -14.5);
	glVertex2f(1.1, -17);
	glEnd();
	
	glColor3f(0.40, 0.55, 0.25);
	glBegin(GL_POLYGON);
	glVertex2f(-36, -10.1);
	glVertex2f(-22, -18.1);
	glVertex2f(-38, -17.1);
	glEnd();
	
	glColor3f(0.65, 0.85, 0.50);
	glBegin(GL_POLYGON);
	glVertex2f(-59, -25.8);
	glVertex2f(-38, -17.1);
	glVertex2f(-22, -18.1);
	glEnd();
	
	glColor3f(0.40, 0.55, 0.25);
	glBegin(GL_POLYGON);
	glVertex2f(-22,-18);
	glVertex2f(-10, -17.5);
	glVertex2f(-13,-21);
	glEnd();
	
	glColor3f(0.65, 0.85, 0.50);
	glBegin(GL_POLYGON);
	glVertex2f(-10, -17.5);
	glVertex2f(-1, -19.5);
	glVertex2f(-13,-21);
	glEnd();
	
	glColor3f(0.40, 0.55, 0.25);
	glBegin(GL_POLYGON);
	glVertex2f(-10, -17.5);
	glVertex2f(1.1, -17);
	glVertex2f(-1, -19.5);
	glEnd();
	
	glColor3f(0.65, 0.85, 0.50);
	glBegin(GL_POLYGON);
	glVertex2f(-1, -19.5);
	glVertex2f(1.1, -17);
	glVertex2f(12, -13.9);
	glVertex2f(6, -20);
	glEnd();
	
	glColor3f(0.40, 0.55, 0.25);
	glBegin(GL_POLYGON);
	glVertex2f(-13,-21);
	glVertex2f(-1, -19.5);
	glVertex2f(-5, -23);
	glEnd();
	
	glColor3f(0.65, 0.85, 0.50);
	glBegin(GL_POLYGON);
	glVertex2f(-5, -23);
	glVertex2f(-1, -19.5);
	glVertex2f(6, -20);
	glVertex2f(9, -24);
	glEnd();
	
	glColor3f(0.40, 0.55, 0.25);
	glBegin(GL_POLYGON);
	glVertex2f(9, -24);
	glVertex2f(6, -20);
	glVertex2f(15, -17);
	glEnd();
	
	glColor3f(0.65, 0.85, 0.50);
	glBegin(GL_POLYGON);
	glVertex2f(6, -20);
	glVertex2f(15, -17);
	glVertex2f(12, -13.9);
	glEnd();
	
	glColor3f(0.40, 0.55, 0.25);
	glBegin(GL_POLYGON);
	glVertex2f(15, -17);
	glVertex2f(12, -13.9);
	glVertex2f(20, -10.5);
	glEnd();
	
	glColor3f(0.65, 0.85, 0.50);
	glBegin(GL_POLYGON);
	glVertex2f(15, -17);
	glVertex2f(20, -10.5);
	glVertex2f(28, -12);
	glVertex2f(24, -17);
	glEnd();
	
	glColor3f(0.40, 0.55, 0.25);
	glBegin(GL_POLYGON);
	glVertex2f(20, -10.5);
	glVertex2f(23.5, -9);
	glVertex2f(28, -12);
	glEnd();
	
	glColor3f(0.65, 0.85, 0.50);
	glBegin(GL_POLYGON);
	glVertex2f(26, -21);
	glVertex2f(24, -17);
	glVertex2f(28, -12);
	glVertex2f(35, -18);
	glEnd();
	
	glColor3f(0.40, 0.55, 0.25);
	glBegin(GL_POLYGON);
	glVertex2f(35, -18);
	glVertex2f(39, -15.5);
	glVertex2f(28, -12);
	glEnd();
	
	glColor3f(0.65, 0.85, 0.50);
	glBegin(GL_POLYGON);
	glVertex2f(9, -24);
	glVertex2f(15, -17);
	glVertex2f(24, -17);
	glVertex2f(26, -21);
	glEnd();
	
	glColor3f(0.40, 0.55, 0.25);
	glBegin(GL_POLYGON);
	glVertex2f(26, -21);
	glVertex2f(43, -22);
	glVertex2f(35, -18);
	glEnd();
	
	glColor3f(0.65, 0.85, 0.50);
	glBegin(GL_POLYGON);
	glVertex2f(35, -18);
	glVertex2f(39, -15.5);
	glVertex2f(43.6, -17.1);
	glVertex2f(43, -22);
	glEnd();
	
	glColor3f(0.40, 0.55, 0.25);
	glBegin(GL_POLYGON);
	glVertex2f(43, -22);
	glVertex2f(43.6, -17.1);
	glVertex2f(52, -20.5);
	glEnd();
	
	glColor3f(0.65, 0.85, 0.50);
	glBegin(GL_POLYGON);
	glVertex2f(9, -24);
	glVertex2f(26, -21);
	glVertex2f(24, -23);
	glEnd();
	
	glColor3f(0.40, 0.55, 0.25);
	glBegin(GL_POLYGON);
	glVertex2f(24, -23);
	glVertex2f(26, -21);
	glVertex2f(35, -23);
	glEnd();
	
	glColor3f(0.65, 0.85, 0.50);
	glBegin(GL_POLYGON);
	glVertex2f(35, -23);
	glVertex2f(26, -21);
	glVertex2f(43, -22);
	glEnd();
	
	glColor3f(0.40, 0.55, 0.25);
	glBegin(GL_POLYGON);
	glVertex2f(35, -23);
	glVertex2f(52, -20.5);
	glVertex2f(63, -24);
	glEnd();
}

void orilla() {
	glBegin(GL_POLYGON);
	glColor3f(165.0/255.0, 63.0/255.0, 48.0/255.0);
	glVertex2f(-76,-26);
	glVertex2f(-65.5,-32);
	glVertex2f(-76,-32);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(201.0/255.0, 87.0/255.0, 71.0/255.0);
	glVertex2f(-76,-26);
	glVertex2f(-69,-27);
	glVertex2f(-65.5,-32);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(165.0/255.0, 63.0/255.0, 48.0/255.0);
	glVertex2f(-69,-27);
	glVertex2f(-64,-26.3);
	glVertex2f(-65.5,-32);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(201.0/255.0, 87.0/255.0, 71.0/255.0);
	glVertex2f(-65.5,-32);
	glVertex2f(-64,-26.3);
	glVertex2f(-60,-32);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(165.0/255.0, 63.0/255.0, 48.0/255.0);
	glVertex2f(-60,-32);
	glVertex2f(-64,-26.3);
	glVertex2f(-56,-25);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(201.0/255.0, 87.0/255.0, 71.0/255.0);
	glVertex2f(-60,-32);
	glVertex2f(-57.8,-28);
	glVertex2f(-52,-32);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(165.0/255.0, 63.0/255.0, 48.0/255.0);
	glVertex2f(-57.8,-28);
	glVertex2f(-56,-25);
	glVertex2f(-50,-24);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(201.0/255.0, 87.0/255.0, 71.0/255.0);
	glVertex2f(-57.8,-28);
	glVertex2f(-50,-24);
	glVertex2f(-52,-28.5);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(165.0/255.0, 63.0/255.0, 48.0/255.0);
	glVertex2f(-52,-32);
	glVertex2f(-57.8,-28);
	glVertex2f(-50,-24);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(165.0/255.0, 63.0/255.0, 48.0/255.0);
	glVertex2f(-52,-32);
	glVertex2f(-50,-24);
	glVertex2f(-46,-32);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(201.0/255.0, 87.0/255.0, 71.0/255.0);
	glVertex2f(-46,-32);
	glVertex2f(-50,-24);
	glVertex2f(-46,-23);
	glVertex2f(-42,-32);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(165.0/255.0, 63.0/255.0, 48.0/255.0);
	glVertex2f(-46,-23);
	glVertex2f(-37,-21.2);
	glVertex2f(-44.3,-27);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(201.0/255.0, 87.0/255.0, 71.0/255.0);
	glVertex2f(-44.3,-27);
	glVertex2f(-37,-21.2);
	glVertex2f(-34,-29);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(165.0/255.0, 63.0/255.0, 48.0/255.0);
	glVertex2f(-42,-32);
	glVertex2f(-44.3,-27);
	glVertex2f(-34,-29);
	glVertex2f(-36,-32);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(201.0/255.0, 87.0/255.0, 71.0/255.0);
	glVertex2f(-36,-32);
	glVertex2f(-34,-29);
	glVertex2f(-30,-32);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(165.0/255.0, 63.0/255.0, 48.0/255.0);
	glVertex2f(-30,-32);
	glVertex2f(-34,-29);
	glVertex2f(-29,-26);
	glVertex2f(-27,-32);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(201.0/255.0, 87.0/255.0, 71.0/255.0);
	glVertex2f(-34,-29);
	glVertex2f(-37,-21.2);
	glVertex2f(-29,-26);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(165.0/255.0, 63.0/255.0, 48.0/255.0);
	glVertex2f(-37,-21.2);
	glVertex2f(-22,-18);
	glVertex2f(-29,-26);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(201.0/255.0, 87.0/255.0, 71.0/255.0);
	glVertex2f(-29,-26);
	glVertex2f(-22,-18);
	glVertex2f(-15,-22);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(165.0/255.0, 63.0/255.0, 48.0/255.0);
	glVertex2f(-22,-18);
	glVertex2f(-13,-21);
	glVertex2f(-15,-22);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(201.0/255.0, 87.0/255.0, 71.0/255.0);
	glVertex2f(-27,-32);
	glVertex2f(-29,-26);
	glVertex2f(-20,-32);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(165.0/255.0, 63.0/255.0, 48.0/255.0);
	glVertex2f(-20,-32);
	glVertex2f(-29,-26);
	glVertex2f(-15,-22);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(201.0/255.0, 87.0/255.0, 71.0/255.0);
	glVertex2f(-20,-32);
	glVertex2f(-15,-22);
	glVertex2f(-13,-21);
	glVertex2f(-10,-25);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(165.0/255.0, 63.0/255.0, 48.0/255.0);
	glVertex2f(-20,-32);
	glVertex2f(-10,-25);
	glVertex2f(-6,-32);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(201.0/255.0, 87.0/255.0, 71.0/255.0);
	glVertex2f(-13,-21);
	glVertex2f(-10,-25);
	glVertex2f(-5,-23);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(165.0/255.0, 63.0/255.0, 48.0/255.0);
	glVertex2f(-10,-25);
	glVertex2f(-5,-23);
	glVertex2f(9.9,-24);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(201.0/255.0, 87.0/255.0, 71.0/255.0);
	glVertex2f(-10,-25);
	glVertex2f(9.9,-24);
	glVertex2f(0,-29);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(165.0/255.0, 63.0/255.0, 48.0/255.0);
	glVertex2f(-6,-32);
	glVertex2f(-10,-25);
	glVertex2f(0,-29);
	glVertex2f(3,-32);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(201.0/255.0, 87.0/255.0, 71.0/255.0);
	glVertex2f(3,-32);
	glVertex2f(0,-29);
	glVertex2f(10,-30);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(165.0/255.0, 63.0/255.0, 48.0/255.0);
	glVertex2f(0,-29);
	glVertex2f(9.9,-24);
	glVertex2f(10,-30);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(201.0/255.0, 87.0/255.0, 71.0/255.0);
	glVertex2f(3,-32);
	glVertex2f(10,-30);
	glVertex2f(18,-32);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(165.0/255.0, 63.0/255.0, 48.0/255.0);
	glVertex2f(18,-32);
	glVertex2f(10,-30);
	glVertex2f(9.9,-24);
	glVertex2f(15,-25);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(201.0/255.0, 87.0/255.0, 71.0/255.0);
	glVertex2f(9.9,-24);
	glVertex2f(15,-25);
	glVertex2f(20,-23.2);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(165.0/255.0, 63.0/255.0, 48.0/255.0);
	glVertex2f(19,-30);
	glVertex2f(15,-25);
	glVertex2f(20,-23.2);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(201.0/255.0, 87.0/255.0, 71.0/255.0);
	glVertex2f(18,-32);
	glVertex2f(15,-25);
	glVertex2f(21,-32);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(165.0/255.0, 63.0/255.0, 48.0/255.0);
	glVertex2f(19,-30);
	glVertex2f(20,-23.2);
	glVertex2f(21,-32);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(201.0/255.0, 87.0/255.0, 71.0/255.0);
	glVertex2f(21,-32);
	glVertex2f(20,-23.2);
	glVertex2f(28,-28);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(165.0/255.0, 63.0/255.0, 48.0/255.0);
	glVertex2f(21,-32);
	glVertex2f(28,-28);
	glVertex2f(26,-32);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(201.0/255.0, 87.0/255.0, 71.0/255.0);
	glVertex2f(26,-32);
	glVertex2f(28,-28);
	glVertex2f(32,-32);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(165.0/255.0, 63.0/255.0, 48.0/255.0);
	glVertex2f(20,-23.2);
	glVertex2f(28,-28);
	glVertex2f(30,-23);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(201.0/255.0, 87.0/255.0, 71.0/255.0);
	glVertex2f(32,-32);
	glVertex2f(28,-28);
	glVertex2f(30,-23);
	glVertex2f(38,-32);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(165.0/255.0, 63.0/255.0, 48.0/255.0);
	glVertex2f(38,-32);
	glVertex2f(30,-23);
	glVertex2f(40,-28);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(201.0/255.0, 87.0/255.0, 71.0/255.0);
	glVertex2f(40,-28);
	glVertex2f(30,-23);
	glVertex2f(38,-23);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(165.0/255.0, 63.0/255.0, 48.0/255.0);
	glVertex2f(38,-23);
	glVertex2f(40,-28);
	glVertex2f(48,-23.3);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(201.0/255.0, 87.0/255.0, 71.0/255.0);
	glVertex2f(38,-32);
	glVertex2f(38,-23);
	glVertex2f(48,-23.3);
	glVertex2f(50,-32);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(165.0/255.0, 63.0/255.0, 48.0/255.0);
	glVertex2f(50,-32);
	glVertex2f(48,-23.3);
	glVertex2f(55,-32);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(201.0/255.0, 87.0/255.0, 71.0/255.0);
	glVertex2f(55,-32);
	glVertex2f(48,-23.3);
	glVertex2f(60,-32);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(165.0/255.0, 63.0/255.0, 48.0/255.0);
	glVertex2f(48,-23.3);
	glVertex2f(56,-23.8);
	glVertex2f(60,-32);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(201.0/255.0, 87.0/255.0, 71.0/255.0);
	glVertex2f(60,-32);
	glVertex2f(55.8,-23.7);
	glVertex2f(63,-23.8);
	glVertex2f(65,-32);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(165.0/255.0, 63.0/255.0, 48.0/255.0);
	glVertex2f(65,-32);
	glVertex2f(63,-23.8);
	glVertex2f(72,-32);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(201.0/255.0, 87.0/255.0, 71.0/255.0);
	glVertex2f(72,-32);
	glVertex2f(63,-23.8);
	glVertex2f(76,-27);
	glVertex2f(76,-32);
	glEnd();
}

void arboles() {
	//1
	glBegin(GL_POLYGON);
	glColor3f(155 / 255, 113 / 255, 102 / 255);
	glVertex2f(-27.6, -14.8);
	glVertex2f(-27, -6.87);
	glVertex2f(-27.2, 0.87);
	glVertex2f(-25.2, 1.3);
	glVertex2f(-25.6, -7.87); 
	glVertex2f(-26, -15);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(73 / 255, 42 / 255, 40 / 255);
	glVertex2f(-25.3, 1.3);
	glVertex2f(-26, -15);
	glVertex2f(-24.8, -13.53);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(233 / 255, 255 / 255, 150 / 255);
	glVertex2f(-27.2, 0.87);
	glVertex2f(-28, 3);
	glVertex2f(-24.5, 3.5);
	glVertex2f(-25.2, 1.3);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(220 / 255, 255 / 255, 140/ 255);
	glVertex2f(-30, -2);
	glVertex2f(-28, 3);
	glVertex2f(-27.2, 0.87);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(220 / 255, 255 / 255, 130 / 255);
	glVertex2f(-30, -2);
	glVertex2f(-27.2, 0.87);
	glVertex2f(-27.3, -5);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(210 / 255, 255 / 255, 120 / 255);
	glVertex2f(-29, -8);
	glVertex2f(-30, -2);
	glVertex2f(-27.3, -5);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(200 / 255, 255 / 255, 110 / 255);
	glVertex2f(-29, -8);
	glVertex2f(-27.8, -10);
	glVertex2f(-26.2, -3);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(190 / 255, 255 / 255, 100 / 255);
	glVertex2f(-27.3, -5);
	glVertex2f(-30, -2);
	glVertex2f(-29.3, -7.9);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(210 / 255, 255 / 255, 120 / 255);
	glVertex2f(-25.2, 1.3);
	glVertex2f(-24.5, 3.5);
	glVertex2f(-23.3, -2);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(210 / 255, 255 / 255, 110 / 255);
	glVertex2f(-25.2, 1.3);
	glVertex2f(-23.3, -2);
	glVertex2f(-24.3, -5);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(200 / 255, 255 / 255, 100 / 255);
	glVertex2f(-24.3, -5);
	glVertex2f(-23.3, -2);
	glVertex2f(-24, -7);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(190 / 255, 255 / 255, 90 / 255);
	glVertex2f(-27.2, 0.87);
	glVertex2f(-24, -7);
	glVertex2f(-25.2, 1.3);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(180 / 255, 255 / 255, 80 / 255);
	glVertex2f(-27.2, 0.87);
	glVertex2f(-24, -7);
	glVertex2f(-26, -10);
	glEnd();
	
	//2
	glBegin(GL_POLYGON);
	glColor3f(155 / 255, 113 / 255, 102 / 255);
	glVertex2f(21.36, -1.87);
	glVertex2f(17.42, -14.8);
	glVertex2f(20.08, -15.44);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(73 / 255, 42 / 255, 40 / 255);
	glVertex2f(20.36, -4.87); 
	glVertex2f(20.08, -15.44);
	glVertex2f(23.91, -13.53);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(239 / 255, 225 / 255, 165 / 255);
	glVertex2f(16.7, 2.26);
	glVertex2f(18.31, -0.5); 
	glVertex2f(20.87, 3.69); 
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(233 / 255, 255 / 255, 150 / 255);
	glVertex2f(18.31, -0.5); 
	glVertex2f(20.87, 3.69); 
	glVertex2f(22.79, 3.69); 
	glVertex2f(23.27, -0.66); 
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(153 / 255, 173 / 255, 66 / 255);
	glVertex2f(22.79, 3.69); 
	glVertex2f(23.27, -0.66); 
	glVertex2f(26.46, 1.78); 
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(228 / 255, 248 / 255, 139 / 255);
	glVertex2f(16.7, 2.26);
	glVertex2f(18.31, -0.5); 
	glVertex2f(18.47, -7.65);
	glVertex2f(15.5, -4.2); 
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(115 / 255, 139 / 255, 47 / 255);
	glVertex2f(18.31, -0.5); 
	glVertex2f(18.47, -7.65);
	glVertex2f(23.59, -7.97); 
	glVertex2f(23.27, -0.66);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(80 / 255, 93 / 255, 26 / 255);
	glVertex2f(23.27, -0.66);
	glVertex2f(23.59, -7.97); 
	glVertex2f(27.1, -6.92);
	glVertex2f(26.46, 1.78); 
	glEnd();
	
	//3
	glBegin(GL_POLYGON);
	glColor3ub(73,42,40);
	glVertex2f(48.31, -13.28);
	glVertex2f(52, -13.28);
	glVertex2f(49.31, -21.15);
	glVertex2f(54.37, -28.32);
	glVertex2f(50.28, -29.51);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3ub(155,113,102);
	glVertex2f(48.31, -13.28);
	glVertex2f(50.28, -29.51);
	glVertex2f(47.47, -28.32);
	glVertex2f(49.08, -21.32);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3ub(173,194,89);
	glVertex2f(50, 3); 
	glVertex2f(54.87, 1.57); 
	glVertex2f(49.67, -1.96);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3ub(194,215,101);
	glVertex2f(54.87, 1.57); 
	glVertex2f(49.67, -1.96);
	glVertex2f(52.95, -5.47); 
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3ub(209,230,125);
	glVertex2f(50, 3); 
	glVertex2f(49.67, -1.96);
	glVertex2f(44.29, 1.41);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3ub(233,255,150);
	glVertex2f(54.87, 1.57); 
	glVertex2f(49.67, -1.96);
	glVertex2f(49.83, -5.15); 
	glVertex2f(52.95, -5.47); 
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3ub(121,138,46);
	glVertex2f(54.87, 1.57); 
	glVertex2f(52.95, -5.47); 
	glVertex2f(58.21, -6.9); 
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3ub(228,248,139);
	glVertex2f(52.95, -5.47); 
	glVertex2f(58.21, -6.9);  
	glVertex2f(52.95, -9.29);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3ub(115,139,47);
	glVertex2f(49.83, -5.15); 
	glVertex2f(52.95, -5.47); 
	glVertex2f(49.51, -10.09); 
	glVertex2f(52.95, -9.29);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3ub(80,93,26);
	glVertex2f(52.95, -5.47);
	glVertex2f(58.21, -6.9); 
	glVertex2f(52.95, -9.29);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3ub(80,93,26);
	glVertex2f(58.21, -6.9); 
	glVertex2f(52.95, -9.29);
	glVertex2f(52, -13.28);
	glVertex2f(57.42, -11.21); 
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3ub(80,93,26);
	glVertex2f(52.95, -9.29);
	glVertex2f(52, -13.28);
	glVertex2f(48.31, -13.28); 
	glVertex2f(49.51, -10.09); 
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3ub(80,93,26);
	glVertex2f(48.31, -13.28); 
	glVertex2f(49.51, -10.09); 
	glVertex2f(43.25, -8.97); 
	glVertex2f(44.13, -12); 
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3ub(115,139,47);
	glVertex2f(41.42, -4.67); 
	glVertex2f(43.2, -9.2); 
	glVertex2f(44.22, 1.3); 
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3ub(108,123,44);
	glVertex2f(52.95, -5.47); 
	glVertex2f(58.21, -6.9); 
	glVertex2f(52.95, -9.29); 
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3ub(241,255,182);
	glVertex2f(43.25, -8.97); 
	glVertex2f(49.51, -10.09); 
	glVertex2f(49.83, -5.15); 
	glVertex2f(49.67, -1.96); 
	glVertex2f(44.29, 1.41); 
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3ub(149,171,66);
	glVertex2f(52.95, -5.47); 
	glVertex2f(49.51, -10.09); 
	glVertex2f(52.95, -9.29); 
	glEnd();
	
	//4
	glBegin(GL_POLYGON);
	glColor3ub(73,42,40);
	glVertex2f(-61.86, -15.79);
	glVertex2f(-59.36, -16.69); 
	glVertex2f(-61.97, -1.34);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3ub(155,113,102);
	glVertex2f(-61.86, -15.79);
	glVertex2f(-61.97, -1.34);
	glVertex2f(-64.34, -16.69); 
	glVertex2f(-63.19, -13.89); 
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3ub(211,233,116);
	glVertex2f(-62.18, 5.62); 
	glVertex2f(-67.68, -11.3); 
	glVertex2f(-61.86, -13.79);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3ub(84,101,30);
	glVertex2f(-62.18, 5.62); 
	glVertex2f(-61.86, -13.79);
	glVertex2f(-56.16, -11.4); 
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3ub(211,233,136);
	glVertex2f(-62.18, 5.62); 
	glVertex2f(-66.85, -6.84); 
	glVertex2f(-61.97, -8.6);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3ub(84,101,50);
	glVertex2f(-62.18, 5.62); 
	glVertex2f(-61.97, -8.6);
	glVertex2f(-57.51, -7.04); 
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3ub(211,233,156);
	glVertex2f(-62.18, 5.62); 
	glVertex2f(-66.12, -3.31); 
	glVertex2f(-61.86, -4.66);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3ub(84,101,70);
	glVertex2f(-62.18, 5.62); 
	glVertex2f(-61.86, -4.66);
	glVertex2f(-58.13, -3.2); 
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3ub(211,233,176);
	glVertex2f(-62.18, 5.62); 
	glVertex2f(-65.39, 0.01); 
	glVertex2f(-61.97, -1.34);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3ub(84,101,90);
	glVertex2f(-62.18, 5.62); 
	glVertex2f(-61.97, -1.34);
	glVertex2f(-58.86, 0.12);
	glEnd();
}

void rio() {
	glBegin(GL_POLYGON);
	glColor3f(0.56, 0.79, 0.96);
	glVertex2f(-76,-32);
	glVertex2f(-54.5,-32);
	glVertex2f(-63.5,-36);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.61, 0.70, 0.96);
	glVertex2f(-76,-32);
	glVertex2f(-63.5,-36);
	glVertex2f(-71,-38);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.56, 0.79, 0.96);
	glVertex2f(-76,-32);
	glVertex2f(-71,-38);
	glVertex2f(-73,-40);
	glVertex2f(-76,-39);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.61, 0.70, 0.96);
	glVertex2f(-73,-40);
	glVertex2f(-71,-38);
	glVertex2f(-64,-36);
	glVertex2f(-65,-40);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.56, 0.79, 0.96);
	glVertex2f(-65,-40);
	glVertex2f(-64,-36);
	glVertex2f(-57,-41);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.61, 0.70, 0.96);
	glVertex2f(-64,-36);
	glVertex2f(-49,-38);
	glVertex2f(-57,-41);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.56, 0.79, 0.96);
	glVertex2f(-64,-36);
	glVertex2f(-54.5,-32);
	glVertex2f(-49,-38);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.61, 0.70, 0.96);
	glVertex2f(-54.5,-32);
	glVertex2f(-36,-35);
	glVertex2f(-49,-38);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.56, 0.79, 0.96);
	glVertex2f(-57,-41);
	glVertex2f(-49,-38);
	glVertex2f(-48,-42);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.61, 0.70, 0.96);
	glVertex2f(-48,-42);
	glVertex2f(-49,-38);
	glVertex2f(-36,-35);
	glVertex2f(-43,-42);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.56, 0.79, 0.96);
	glVertex2f(-43,-42);
	glVertex2f(-36,-35);
	glVertex2f(-30,-42);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.61, 0.70, 0.96);
	glVertex2f(-30,-42);
	glVertex2f(-36,-35);
	glVertex2f(-24,-32);
	glVertex2f(-17,-41);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.56, 0.79, 0.96);
	glVertex2f(-54.5,-32);
	glVertex2f(-24,-32);
	glVertex2f(-36,-35);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.61, 0.70, 0.96);
	glVertex2f(-24,-32);
	glVertex2f(-4,-37);
	glVertex2f(-17,-41);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.56, 0.79, 0.96);
	glVertex2f(-30,-42);
	glVertex2f(-17,-41);
	glVertex2f(-20,-46);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.61, 0.70, 0.96);
	glVertex2f(-20,-46);
	glVertex2f(-17,-41);
	glVertex2f(-7,-46);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.56, 0.79, 0.96);
	glVertex2f(-17,-41);
	glVertex2f(-4,-37);
	glVertex2f(-7,-46);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.61, 0.70, 0.96);
	glVertex2f(-24,-32);
	glVertex2f(10,-32);
	glVertex2f(-4,-37);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.56, 0.79, 0.96);
	glVertex2f(-7,-46);
	glVertex2f(-4,-37);
	glVertex2f(3,-45);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.61, 0.70, 0.96);
	glVertex2f(3,-45);
	glVertex2f(-4,-37);
	glVertex2f(8,-43);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.56, 0.79, 0.96);
	glVertex2f(-7,-46);
	glVertex2f(-4,-37);
	glVertex2f(3,-45);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.61, 0.70, 0.96);
	glVertex2f(3,-45);
	glVertex2f(-4,-37);
	glVertex2f(8,-43);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.56, 0.79, 0.96);
	glVertex2f(8,-43);
	glVertex2f(10,-32);
	glVertex2f(21,-36);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.61, 0.70, 0.96);
	glVertex2f(-4,-37);
	glVertex2f(10,-32);
	glVertex2f(8,-43);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.56, 0.79, 0.96);
	glVertex2f(8,-43);
	glVertex2f(21,-36);
	glVertex2f(25,-38);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.61, 0.70, 0.96);
	glVertex2f(10,-32);
	glVertex2f(28,-32);
	glVertex2f(21,-36);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.56, 0.79, 0.96);
	glVertex2f(21,-36);
	glVertex2f(28,-32);
	glVertex2f(29,-37);
	glVertex2f(25,-38);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.61, 0.70, 0.96);
	glVertex2f(29,-37);
	glVertex2f(28,-32);
	glVertex2f(35,-35);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.56, 0.79, 0.96);
	glVertex2f(28,-32);
	glVertex2f(42,-32);
	glVertex2f(35,-35);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.61, 0.70, 0.96);
	glVertex2f(35,-35);
	glVertex2f(42,-32);
	glVertex2f(47,-35);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.56, 0.79, 0.96);
	glVertex2f(47,-35);
	glVertex2f(42,-32);
	glVertex2f(63,-32);
	glVertex2f(60,-34);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.61, 0.70, 0.96);
	glVertex2f(63,-32);
	glVertex2f(76,-32);
	glVertex2f(76,-34);
	glVertex2f(60,-34);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.56, 0.79, 0.96);
	glVertex2f(-76,-45);
	glVertex2f(-70,-50);
	glVertex2f(-73,-40);
	glVertex2f(-76,-39);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.61, 0.70, 0.96);
	glVertex2f(-76,-50);
	glVertex2f(-76,-45);
	glVertex2f(-70,-50);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.56, 0.79, 0.96);
	glVertex2f(-73,-40);
	glVertex2f(-65,-45);
	glVertex2f(-70,-50);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.61, 0.70, 0.96);
	glVertex2f(-70,-50);
	glVertex2f(-65,-45);
	glVertex2f(-48,-42);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.56, 0.79, 0.96);
	glVertex2f(-73,-40);
	glVertex2f(-65,-45);
	glVertex2f(-65,-40);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.61, 0.70, 0.96);
	glVertex2f(-65,-40);
	glVertex2f(-57,-41);
	glVertex2f(-65,-45);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.56, 0.79, 0.96);
	glVertex2f(-57,-41);
	glVertex2f(-48,-42);
	glVertex2f(-65,-45);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.61, 0.70, 0.96);
	glVertex2f(-70,-50);
	glVertex2f(-48,-42);
	glVertex2f(-55,-50);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.56, 0.79, 0.96);
	glVertex2f(-55,-50);
	glVertex2f(-50.5,-45);
	glVertex2f(-46,-50);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.61, 0.70, 0.96);
	glVertex2f(-50.5,-45);
	glVertex2f(-48,-42);
	glVertex2f(-46,-50);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.56, 0.79, 0.96);
	glVertex2f(-48,-42);
	glVertex2f(-46,-50);
	glVertex2f(-36,-50);
	glVertex2f(-43,-42);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.61, 0.70, 0.96);
	glVertex2f(-43,-42);
	glVertex2f(-36,-50);
	glVertex2f(-30,-42);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.56, 0.79, 0.96);
	glVertex2f(-36,-50);
	glVertex2f(-30,-42);
	glVertex2f(-20,-46);
	glVertex2f(-17,-50);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.61, 0.70, 0.96);
	glVertex2f(-20,-46);
	glVertex2f(-17,-50);
	glVertex2f(-7,-46);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.56, 0.79, 0.96);
	glVertex2f(-17,-50);
	glVertex2f(-4,-50);
	glVertex2f(-7,-46);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.61, 0.70, 0.96);
	glVertex2f(-7,-46);
	glVertex2f(-4,-50);
	glVertex2f(3,-45);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.56, 0.79, 0.96);
	glVertex2f(3,-45);
	glVertex2f(-4,-50);
	glVertex2f(8,-50);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.61, 0.70, 0.96);
	glVertex2f(3,-45);
	glVertex2f(8,-43);
	glVertex2f(8,-50);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.56, 0.79, 0.96);
	glVertex2f(8,-50);
	glVertex2f(8,-43);
	glVertex2f(18,-50);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.61, 0.70, 0.96);
	glVertex2f(18,-50);
	glVertex2f(8,-43);
	glVertex2f(25,-38);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.56, 0.79, 0.96);
	glVertex2f(18,-50);
	glVertex2f(25,-38);
	glVertex2f(29,-37);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.61, 0.70, 0.96);
	glVertex2f(18,-50);
	glVertex2f(24,-43);
	glVertex2f(29,-50);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.56, 0.79, 0.96);
	glVertex2f(29,-50);
	glVertex2f(24,-43);
	glVertex2f(35,-39);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.61, 0.70, 0.96);
	glVertex2f(24,-43);
	glVertex2f(29,-37);
	glVertex2f(35,-39);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.56, 0.79, 0.96);
	glVertex2f(29,-50);
	glVertex2f(35,-39);
	glVertex2f(38,-50);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.61, 0.70, 0.96);
	glVertex2f(35,-39);
	glVertex2f(29,-37);
	glVertex2f(35,-35);
	glVertex2f(41,-38);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.56, 0.79, 0.96);
	glVertex2f(35,-39);
	glVertex2f(41,-38);
	glVertex2f(38,-50);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.61, 0.70, 0.96);
	glVertex2f(41,-38);
	glVertex2f(35,-35);
	glVertex2f(47,-35);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.56, 0.79, 0.96);
	glVertex2f(41,-38);
	glVertex2f(47,-35);
	glVertex2f(50,-40);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.61, 0.70, 0.96);
	glVertex2f(38,-50);
	glVertex2f(40,-42);
	glVertex2f(50,-40);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.56, 0.79, 0.96);
	glVertex2f(40,-42);
	glVertex2f(41,-38);
	glVertex2f(50,-40);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.61, 0.70, 0.96);
	glVertex2f(50,-40);
	glVertex2f(47,-35);
	glVertex2f(60,-34);
	glVertex2f(62,-38);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.56, 0.79, 0.96);
	glVertex2f(62,-38);
	glVertex2f(60,-34);
	glVertex2f(76,-34);
	glVertex2f(76,-40);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.61, 0.70, 0.96);
	glVertex2f(38,-50);
	glVertex2f(50,-40);
	glVertex2f(56,-50);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.56, 0.79, 0.96);
	glVertex2f(56,-50);
	glVertex2f(62,-38);
	glVertex2f(50,-40);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.61, 0.70, 0.96);
	glVertex2f(56,-50);
	glVertex2f(60,-42);
	glVertex2f(76,-50);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.56, 0.79, 0.96);
	glVertex2f(60,-42);
	glVertex2f(62,-38);
	glVertex2f(76,-40);
	glVertex2f(76,-50);
	glEnd();
}

void roca1() {
	glBegin(GL_TRIANGLES);
	glColor3f(0.5, 0.5, 0.5);
	glVertex2f(-2, 2);
	glVertex2f(0, 4);
	glVertex2f(0, -1);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.4, 0.4, 0.4);
	glVertex2f(-2, 2);
	glVertex2f(0, -1);
	glVertex2f(1, -3);
	glVertex2f(-4, -3);
	glEnd();
	
	glBegin(GL_TRIANGLES);
	glColor3f(0.45, 0.45, 0.45);
	glVertex2f(0, -1);
	glVertex2f(2, -3);
	glVertex2f(1, -3);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.4, 0.4, 0.4);
	glVertex2f(0, -1);
	glVertex2f(0, 4);
	glVertex2f(3, -3);
	glVertex2f(2, -3);
	glEnd();
}

void roca2() {
	glBegin(GL_TRIANGLES);
	glColor3f(0.5f, 0.5f, 0.5f);
	glVertex2f(-4, -1);
	glVertex2f(-2, 2);
	glVertex2f(0, -1);
	glEnd();
	
	glBegin(GL_TRIANGLES);
	glColor3f(0.4f, 0.4f, 0.4f);
	glVertex2f(-2, 2);
	glVertex2f(2, 2);
	glVertex2f(4, -1);
	glEnd();
	
	glBegin(GL_TRIANGLES);
	glColor3f(0.45f, 0.45f, 0.45f);
	glVertex2f(-2, 2);
	glVertex2f(4, -1);
	glVertex2f(0, -1);
	glEnd();
}

void moverRocas(float deltaTime) {
	float desplazamiento = velocidadRocas * deltaTime;
	
	r1_posicionX -= desplazamiento;
	r2_posicionX -= desplazamiento;
	
	if (r1_posicionX < -76) {
		r1_posicionX = 76;
		r1_posicionY = -50 + rand() % 19;
	}
	
	if (r2_posicionX < -76) {
		r2_posicionX = 76;
		r2_posicionY = -50 + rand() % 19;
	}
}

void capibara() {
	glBegin(GL_POLYGON);
	glColor3f(213.0/255.0, 112.0/255.0, 25.0/255.0);
	glVertex2f(-62.45,-27.91);
	glVertex2f(-65.04,-28.25);
	glVertex2f(-68.13,-30.25);
	glVertex2f(-64.70,-29.59);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(203.0/255.0, 94.0/255.0, 22.0/255.0);
	glVertex2f(-62.45,-27.91);
	glVertex2f(-64.70,-29.59);
	glVertex2f(-63.11,-30.00);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(208.0/255.0, 105.0/255.0, 22.0/255.0);
	glVertex2f(-64.70,-29.59);
	glVertex2f(-63.11,-30.00);
	glVertex2f(-67.54,-32.51);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(203.0/255.0, 100.0/255.0, 22.0/255.0);
	glVertex2f(-68.13,-30.25);
	glVertex2f(-64.70,-29.59);
	glVertex2f(-67.54,-32.51);
	glVertex2f(-69.38,-33.09);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(187.0/255.0, 91.0/255.0, 27.0/255.0);
	glVertex2f(-68.13,-30.25);
	glVertex2f(-69.38,-33.09);
	glVertex2f(-70.88,-33.68);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(175.0/255.0, 80.0/255.0, 26.0/255.0);
	glVertex2f(-69.38,-33.09);
	glVertex2f(-70.88,-33.68);
	glVertex2f(-69.46,-36.44);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(188.0/255.0, 91.0/255.0, 26.0/255.0);
	glVertex2f(-71.97,-37.44);
	glVertex2f(-70.88,-33.68);
	glVertex2f(-69.46,-36.44);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(189.0/255.0, 90.0/255.0, 27.0/255.0);
	glVertex2f(-69.38,-33.09);
	glVertex2f(-69.46,-36.44);
	glVertex2f(-67.54,-32.51);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(214.0/255.0, 113.0/255.0, 35.0/255.0);
	glVertex2f(-69.46,-36.44);
	glVertex2f(-67.54,-32.51);
	glVertex2f(-65.37,-34.51);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(199.0/255.0, 94.0/255.0, 21.0/255.0);
	glVertex2f(-63.11,-30.00);
	glVertex2f(-67.54,-32.51);
	glVertex2f(-65.37,-34.51);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(215.0/255.0, 122.0/255.0, 37.0/255.0);
	glVertex2f(-71.97,-37.44);
	glVertex2f(-70.47,-39.19);
	glVertex2f(-69.46,-36.44);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(171.0/255.0, 75.0/255.0, 17.0/255.0);
	glVertex2f(-71.97,-37.44);
	glVertex2f(-70.47,-39.19);
	glVertex2f(-72.05,-41.87);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(140.0/255.0, 58.0/255.0, 21.0/255.0);
	glVertex2f(-70.13,-43.45);
	glVertex2f(-70.47,-39.19);
	glVertex2f(-72.05,-41.87);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(155.0/255.0, 67.0/255.0, 16.0/255.0);
	glVertex2f(-70.13,-43.45);
	glVertex2f(-70.47,-39.19);
	glVertex2f(-68.38,-42.28);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(179.0/255.0, 83.0/255.0, 25.0/255.0);
	glVertex2f(-70.47,-39.19);
	glVertex2f(-67.38,-38.94);
	glVertex2f(-68.38,-42.28);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(215.0/255.0, 117.0/255.0, 32.0/255.0);
	glVertex2f(-70.47,-39.19);
	glVertex2f(-69.46,-36.44);
	glVertex2f(-67.38,-38.94);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(193.0/255.0, 93.0/255.0, 24.0/255.0);
	glVertex2f(-65.37,-34.51);
	glVertex2f(-69.46,-36.44);
	glVertex2f(-67.38,-38.94);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(185.0/255.0, 81.0/255.0, 19.0/255.0);
	glVertex2f(-63.62,-36.44);
	glVertex2f(-65.37,-34.51);
	glVertex2f(-67.38,-38.94);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(178.0/255.0, 74.0/255.0, 17.0/255.0);
	glVertex2f(-63.62,-36.44);
	glVertex2f(-65.37,-34.51);
	glVertex2f(-62.53,-32.43);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(188.0/255.0, 79.0/255.0, 15.0/255.0);
	glVertex2f(-63.11,-30.00);
	glVertex2f(-65.37,-34.51);
	glVertex2f(-62.53,-32.43);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(205.0/255.0, 102.0/255.0, 23.0/255.0);
	glVertex2f(-63.11,-30.00);
	glVertex2f(-62.53,-32.43);
	glVertex2f(-60.69,-29.59);
	glVertex2f(-59.36,-25.99);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(222.0/255.0, 121.0/255.0, 38.0/255.0);
	glVertex2f(-63.11,-30.00);
	glVertex2f(-62.45,-27.91);
	glVertex2f(-59.94,-24.66);
	glVertex2f(-59.94,-25.07);
	glVertex2f(-59.36,-25.99);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(177.0/255.0, 80.0/255.0, 23.0/255.0);
	glVertex2f(-59.36,-25.99);
	glVertex2f(-59.94,-25.07);
	glVertex2f(-59.94,-24.66);
	glVertex2f(-59.52,-24.41);
	glVertex2f(-59.02,-24.91);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(73.0/255.0, 31.0/255.0, 14.0/255.0);
	glVertex2f(-59.94,-24.66);
	glVertex2f(-60.52,-23.07);
	glVertex2f(-58.35,-23.40);
	glVertex2f(-59.52,-24.41);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(99.0/255.0, 43.0/255.0, 18.0/255.0);
	glVertex2f(-60.52,-23.07);
	glVertex2f(-60.02,-21.90);
	glVertex2f(-58.35,-23.40);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(82.0/255.0, 24.0/255.0, 0.0/255.0);
	glVertex2f(-60.02,-21.90);
	glVertex2f(-59.10,-21.65);	
	glVertex2f(-58.35,-23.40);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(62.0/255.0, 22.0/255.0, 6.0/255.0);
	glVertex2f(-58.35,-23.40);
	glVertex2f(-59.02,-24.91);
	glVertex2f(-59.52,-24.41);	
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(174.0/255.0, 104.0/255.0, 48.0/255.0);
	glVertex2f(-59.10,-21.65);	
	glVertex2f(-58.35,-23.40);
	glVertex2f(-57.94,-22.40);	
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(193.0/255.0, 89.0/255.0, 20.0/255.0);
	glVertex2f(-58.35,-23.40);
	glVertex2f(-57.94,-22.40);	
	glVertex2f(-58.02,-23.82);	
	glVertex2f(-57.35,-24.57);	
	glVertex2f(-59.36,-25.99);
	glVertex2f(-59.02,-24.91);	
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(241.0/255.0, 151.0/255.0, 49.0/255.0);
	glVertex2f(-58.02,-23.82);	
	glVertex2f(-57.94,-22.40);	
	glVertex2f(-55.68,-22.23);
	glVertex2f(-56.93,-23.32);	
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(214.0/255.0, 109.0/255.0, 26.0/255.0);
	glVertex2f(-57.35,-24.57);		
	glVertex2f(-58.02,-23.82);	
	glVertex2f(-56.93,-23.32);	
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(246.0/255.0, 171.0/255.0, 66.0/255.0);
	glVertex2f(-55.68,-22.23);
	glVertex2f(-56.93,-23.32);	
	glVertex2f(-54.01,-23.99);	
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(220.0/255.0, 120.0/255.0, 31.0/255.0);
	glVertex2f(-57.35,-24.57);		
	glVertex2f(-56.93,-23.32);	
	glVertex2f(-54.01,-23.99);
	glVertex2f(-55.60,-24.24);	
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(233.0/255.0, 131.0/255.0, 46.0/255.0);
	glVertex2f(-55.68,-22.23);		
	glVertex2f(-54.01,-22.57);	
	glVertex2f(-53.42,-22.65);
	glVertex2f(-52.76,-23.07);	
	glVertex2f(-50.92,-24.07);	
	glVertex2f(-51.50,-24.07);	
	glVertex2f(-54.01,-23.99);	
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(84.0/255.0, 42.0/255.0, 23.0/255.0);
	glVertex2f(-54.01,-22.57);	
	glVertex2f(-53.42,-22.65);
	glVertex2f(-52.76,-23.07);	
	glVertex2f(-53.01,-21.40);		
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(195.0/255.0, 109.0/255.0, 40.0/255.0);
	glVertex2f(-51.50,-24.07);	
	glVertex2f(-54.01,-23.99);	
	glVertex2f(-51.92,-25.32);		
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(213.0/255.0, 111.0/255.0, 27.0/255.0);
	glVertex2f(-57.35,-24.57);	
	glVertex2f(-59.36,-25.99);
	glVertex2f(-58.69,-27.00);		
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(193.0/255.0, 85.0/255.0, 17.0/255.0);
	glVertex2f(-60.69,-29.59);	
	glVertex2f(-59.36,-25.99);
	glVertex2f(-58.69,-27.00);		
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(151.0/255.0, 102.0/255.0, 59.0/255.0);
	glVertex2f(-51.50,-24.07);	
	glVertex2f(-50.92,-24.07);	
	glVertex2f(-50.58,-24.99);		
	glVertex2f(-49.58,-25.83);	
	glVertex2f(-48.16,-27.83);
	glVertex2f(-49.33,-27.41);	
	glVertex2f(-50.50,-26.24);	
	glVertex2f(-51.92,-25.31);	
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(220.0/255.0, 124.0/255.0, 39.0/255.0);
	glVertex2f(-54.01,-23.99);	
	glVertex2f(-53.09,-25.99);
	glVertex2f(-51.92,-25.32);		
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(189.0/255.0, 107.0/255.0, 42.0/255.0);
	glVertex2f(-51.59,-27.75);	
	glVertex2f(-53.09,-25.99);
	glVertex2f(-51.92,-25.32);		
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(152.0/255.0, 90.0/255.0, 44.0/255.0);
	glVertex2f(-51.59,-27.75);
	glVertex2f(-51.92,-25.32);	
	glVertex2f(-50.50,-26.24);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(168.0/255.0, 107.0/255.0, 54.0/255.0);
	glVertex2f(-51.59,-27.75);
	glVertex2f(-49.33,-27.41);	
	glVertex2f(-50.50,-26.24);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(204.0/255.0, 98.0/255.0, 18.0/255.0);
	glVertex2f(-55.60,-24.24);	
	glVertex2f(-54.01,-23.99);	
	glVertex2f(-53.09,-25.99);		
	glVertex2f(-54.26,-25.74);	
	glVertex2f(-55.09,-25.07);
	glEnd();	
	
	glBegin(GL_POLYGON);
	glColor3f(206.0/255.0, 104.0/255.0, 29.0/255.0);
	glVertex2f(-55.09,-25.07);
	glVertex2f(-54.26,-25.74);	
	glVertex2f(-53.67,-27.00);		
	glVertex2f(-55.09,-26.16);
	glEnd();	
	
	glBegin(GL_POLYGON);
	glColor3f(180.0/255.0, 91.0/255.0, 24.0/255.0);
	glVertex2f(-54.26,-25.74);
	glVertex2f(-53.09,-25.99);	
	glVertex2f(-51.59,-27.75);		
	glVertex2f(-53.67,-27.00);
	glEnd();	
	
	glBegin(GL_POLYGON);
	glColor3f(204.0/255.0, 98.0/255.0, 18.0/255.0);
	glVertex2f(-57.35,-24.57);	
	glVertex2f(-55.60,-24.24);	
	glVertex2f(-55.09,-25.07);		
	glVertex2f(-55.09,-26.16);	
	glVertex2f(-55.43,-25.66);
	glVertex2f(-56.18,-24.74);
	glEnd();	
	
	glBegin(GL_POLYGON);
	glColor3f(216.0/255.0, 114.0/255.0, 29.0/255.0);
	glVertex2f(-58.69,-27.00);	
	glVertex2f(-57.35,-24.57);	
	glVertex2f(-57.02,-27.41);
	glEnd();	
	
	glBegin(GL_POLYGON);
	glColor3f(226.0/255.0, 133.0/255.0, 40.0/255.0);
	glVertex2f(-57.35,-24.57);	
	glVertex2f(-56.77,-25.91);
	glVertex2f(-56.18,-25.91);
	glVertex2f(-55.09,-26.16);
	glVertex2f(-57.02,-27.41);	
	glEnd();	
	
	glBegin(GL_POLYGON);
	glColor3f(39.0/255.0, 5.0/255.0, 1.0/255.0);
	glVertex2f(-57.35,-24.57);	
	glVertex2f(-56.18,-24.74);	
	glVertex2f(-55.43,-25.66);		
	glVertex2f(-56.18,-25.91);	
	glVertex2f(-56.77,-25.91);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(77.0/255.0, 23.0/255.0, 6.0/255.0);
	glVertex2f(-57.35,-24.57);	
	glVertex2f(-56.60,-25.07);
	glVertex2f(-56.93,-25.24);
	glEnd();	
	/*
	glBegin(GL_POLYGON);
	glColor3f(140.0/255.0, 113.0/255.0, 82.0/255.0);
	glVertex2f(-57.35,-24.57);	
	glVertex2f(-56.60,-25.07);
	glVertex2f(-56.93,-25.24);
	glEnd();	
	*/
	glBegin(GL_POLYGON);
	glColor3f(102.0/255.0, 42.0/255.0, 12.0/255.0);
	glVertex2f(-55.09,-26.16);	
	glVertex2f(-55.43,-25.66);
	glVertex2f(-56.18,-25.91);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(220.0/255.0, 118.0/255.0, 33.0/255.0);
	glVertex2f(-55.09,-26.16);
	glVertex2f(-57.02,-27.41);	
	glVertex2f(-54.51,-28.33);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(230.0/255.0, 136.0/255.0, 47.0/255.0);
	glVertex2f(-55.09,-26.16);
	glVertex2f(-53.67,-27.00);	
	glVertex2f(-54.51,-28.33);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(220.0/255.0, 120.0/255.0, 34.0/255.0);
	glVertex2f(-52.42,-28.75);
	glVertex2f(-53.67,-27.00);	
	glVertex2f(-54.51,-28.33);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(224.0/255.0, 132.0/255.0, 46.0/255.0);
	glVertex2f(-52.42,-28.75);
	glVertex2f(-53.67,-27.00);	
	glVertex2f(-51.59,-27.75);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(90.0/255.0, 54.0/255.0, 29.0/255.0);
	glVertex2f(-51.59,-27.75);	
	glVertex2f(-49.33,-27.41);	
	glVertex2f(-48.24,-27.83);		
	glVertex2f(-48.33,-29.17);	
	glVertex2f(-49.33,-29.34);
	glVertex2f(-51.42,-29.42);
	glEnd();	
	
	glBegin(GL_POLYGON);
	glColor3f(166.0/255.0, 89.0/255.0, 34.0/255.0);
	glVertex2f(-52.42,-28.75);
	glVertex2f(-51.42,-29.42);	
	glVertex2f(-51.59,-27.75);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(205.0/255.0, 98.0/255.0, 22.0/255.0);
	glVertex2f(-60.69,-29.59);
	glVertex2f(-58.69,-27.00);	
	glVertex2f(-58.19,-29.84);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(211.0/255.0, 108.0/255.0, 29.0/255.0);
	glVertex2f(-58.69,-27.00);	
	glVertex2f(-58.19,-29.84);
	glVertex2f(-57.02,-27.41);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(192.0/255.0, 90.0/255.0, 23.0/255.0);
	glVertex2f(-54.51,-28.33);
	glVertex2f(-57.02,-27.41);	
	glVertex2f(-58.19,-29.84);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(216.0/255.0, 113.0/255.0, 34.0/255.0);
	glVertex2f(-54.51,-28.33);
	glVertex2f(-55.35,-30.92);	
	glVertex2f(-58.19,-29.84);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(204.0/255.0, 103.0/255.0, 26.0/255.0);
	glVertex2f(-54.51,-28.33);
	glVertex2f(-55.35,-30.92);	
	glVertex2f(-53.51,-30.00);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(206.0/255.0, 106.0/255.0, 28.0/255.0);
	glVertex2f(-54.51,-28.33);
	glVertex2f(-52.42,-28.75);	
	glVertex2f(-53.51,-30.00);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(168.0/255.0, 88.0/255.0, 34.0/255.0);
	glVertex2f(-51.42,-29.42);
	glVertex2f(-52.42,-28.75);	
	glVertex2f(-53.51,-30.00);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(222.0/255.0, 127.0/255.0, 37.0/255.0);
	glVertex2f(-60.69,-29.59);
	glVertex2f(-62.53,-32.43);	
	glVertex2f(-61.03,-34.10);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(189.0/255.0, 88.0/255.0, 18.0/255.0);
	glVertex2f(-63.62,-36.44);
	glVertex2f(-62.53,-32.43);	
	glVertex2f(-61.03,-34.10);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(206.0/255.0, 103.0/255.0, 24.0/255.0);
	glVertex2f(-60.69,-29.59);
	glVertex2f(-59.36,-32.01);	
	glVertex2f(-61.03,-34.10);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(182.0/255.0, 82.0/255.0, 18.0/255.0);
	glVertex2f(-60.69,-29.59);
	glVertex2f(-59.36,-32.01);	
	glVertex2f(-58.19,-29.84);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(160.0/255.0, 67.0/255.0, 15.0/255.0);
	glVertex2f(-57.18,-32.18);
	glVertex2f(-59.36,-32.01);	
	glVertex2f(-58.19,-29.84);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(184.0/255.0, 86.0/255.0, 23.0/255.0);
	glVertex2f(-57.18,-32.18);
	glVertex2f(-55.35,-30.92);	
	glVertex2f(-58.19,-29.84);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(139.0/255.0, 55.0/255.0, 12.0/255.0);
	glVertex2f(-57.18,-32.18);
	glVertex2f(-59.36,-32.01);	
	glVertex2f(-56.35,-33.93);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(112.0/255.0, 40.0/255.0, 6.0/255.0);
	glVertex2f(-57.18,-32.18);
	glVertex2f(-54.93,-32.93);	
	glVertex2f(-56.35,-33.93);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(148.0/255.0, 64.0/255.0, 13.0/255.0);
	glVertex2f(-57.18,-32.18);
	glVertex2f(-54.93,-32.93);	
	glVertex2f(-55.35,-30.92);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(214.0/255.0, 117.0/255.0, 32.0/255.0);
	glVertex2f(-58.35,-35.68);
	glVertex2f(-61.03,-34.10);	
	glVertex2f(-59.36,-32.01);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(181.0/255.0, 80.0/255.0, 20.0/255.0);
	glVertex2f(-58.35,-35.68);
	glVertex2f(-56.35,-33.93);	
	glVertex2f(-59.36,-32.01);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(189.0/255.0, 91.0/255.0, 22.0/255.0);
	glVertex2f(-58.35,-35.68);
	glVertex2f(-61.03,-34.10);	
	glVertex2f(-61.03,-38.02);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(177.0/255.0, 79.0/255.0, 18.0/255.0);
	glVertex2f(-63.62,-36.44);
	glVertex2f(-61.03,-34.10);	
	glVertex2f(-61.03,-38.02);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(161.0/255.0, 69.0/255.0, 19.0/255.0);
	glVertex2f(-63.62,-36.44);
	glVertex2f(-63.53,-40.28);	
	glVertex2f(-61.03,-38.02);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(141.0/255.0, 56.0/255.0, 13.0/255.0);
	glVertex2f(-63.62,-36.44);
	glVertex2f(-63.53,-40.28);	
	glVertex2f(-65.29,-40.61);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(168.0/255.0, 70.0/255.0, 16.0/255.0);
	glVertex2f(-63.62,-36.44);
	glVertex2f(-67.38,-38.94);	
	glVertex2f(-65.29,-40.61);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(141.0/255.0, 52.0/255.0, 10.0/255.0);
	glVertex2f(-66.04,-43.12);
	glVertex2f(-67.38,-38.94);	
	glVertex2f(-65.29,-40.61);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(157.0/255.0, 67.0/255.0, 16.0/255.0);
	glVertex2f(-66.04,-43.12);
	glVertex2f(-67.38,-38.94);	
	glVertex2f(-68.38,-42.28);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(90.0/255.0, 32.0/255.0, 8.0/255.0);
	glVertex2f(-66.04,-43.12);
	glVertex2f(-67.63,-45.63);	
	glVertex2f(-68.38,-42.28);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(118.0/255.0, 48.0/255.0, 17.0/255.0);
	glVertex2f(-70.13,-43.45);
	glVertex2f(-67.63,-45.63);	
	glVertex2f(-68.38,-42.28);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(98.0/255.0, 39.0/255.0, 14.0/255.0);
	glVertex2f(-70.13,-43.45);
	glVertex2f(-67.63,-45.63);	
	glVertex2f(-69.46,-45.79);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(112.0/255.0, 49.0/255.0, 21.0/255.0);
	glVertex2f(-70.13,-43.45);
	glVertex2f(-69.46,-45.79);	
	glVertex2f(-70.13,-45.79);
	glVertex2f(-72.05,-41.87);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(79.0/255.0, 26.0/255.0, 9.0/255.0);
	glVertex2f(-66.04,-43.12);
	glVertex2f(-67.63,-45.63);
	glVertex2f(-65.62,-45.63);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(62.0/255.0, 16.0/255.0, 7.0/255.0);
	glVertex2f(-66.04,-43.12);
	glVertex2f(-64.54,-45.63);
	glVertex2f(-65.62,-45.63);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(93.0/255.0, 32.0/255.0, 10.0/255.0);
	glVertex2f(-66.04,-43.12);
	glVertex2f(-64.54,-45.63);
	glVertex2f(-63.28,-42.87);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(77.0/255.0, 25.0/255.0, 10.0/255.0);
	glVertex2f(-61.86,-44.96);
	glVertex2f(-64.54,-45.63);
	glVertex2f(-63.28,-42.87);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(92.0/255.0, 33.0/255.0, 10.0/255.0);
	glVertex2f(-61.86,-44.96);
	glVertex2f(-63.28,-42.87);
	glVertex2f(-63.53,-40.28);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(123.0/255.0, 45.0/255.0, 11.0/255.0);
	glVertex2f(-65.29,-40.61);
	glVertex2f(-63.28,-42.87);
	glVertex2f(-63.53,-40.28);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(110.0/255.0, 39.0/255.0, 8.0/255.0);
	glVertex2f(-65.29,-40.61);
	glVertex2f(-63.28,-42.87);
	glVertex2f(-66.04,-43.12);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(136.0/255.0, 55.0/255.0, 12.0/255.0);
	glVertex2f(-61.11,-41.45);
	glVertex2f(-63.53,-40.28);	
	glVertex2f(-61.03,-38.02);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(129.0/255.0, 51.0/255.0, 13.0/255.0);
	glVertex2f(-61.11,-41.45);
	glVertex2f(-63.53,-40.28);	
	glVertex2f(-62.50,-43.20);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(110.0/255.0, 47.0/255.0, 17.0/255.0);
	glVertex2f(-61.11,-41.45);
	glVertex2f(-60.52,-44.37);	
	glVertex2f(-62.50,-43.20);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(93.0/255.0, 45.0/255.0, 21.0/255.0);
	glVertex2f(-62.50,-43.20);
	glVertex2f(-60.52,-44.37);	
	glVertex2f(-61.19,-46.55);
	glVertex2f(-61.86,-44.96);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(123.0/255.0, 51.0/255.0, 17.0/255.0);
	glVertex2f(-61.11,-41.45);
	glVertex2f(-60.52,-44.37);	
	glVertex2f(-59.19,-42.37);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(107.0/255.0, 44.0/255.0, 20.0/255.0);
	glVertex2f(-58.85,-45.79);
	glVertex2f(-60.52,-44.37);	
	glVertex2f(-59.19,-42.37);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(154.0/255.0, 65.0/255.0, 19.0/255.0);
	glVertex2f(-61.11,-41.45);
	glVertex2f(-59.27,-39.44);	
	glVertex2f(-61.03,-38.02);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(122.0/255.0, 50.0/255.0, 18.0/255.0);
	glVertex2f(-61.11,-41.45);
	glVertex2f(-59.27,-39.44);	
	glVertex2f(-59.19,-42.37);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(169.0/255.0, 73.0/255.0, 17.0/255.0);
	glVertex2f(-58.35,-35.68);
	glVertex2f(-59.27,-39.44);	
	glVertex2f(-61.03,-38.02);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(156.0/255.0, 64.0/255.0, 15.0/255.0);
	glVertex2f(-55.35,-30.92);
	glVertex2f(-53.59,-32.01);
	glVertex2f(-52.17,-32.76);	
	glVertex2f(-52.92,-32.93);
	glVertex2f(-54.93,-32.93);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(215.0/255.0, 113.0/255.0, 30.0/255.0);
	glVertex2f(-53.51,-30.00);
	glVertex2f(-53.59,-32.01);
	glVertex2f(-55.35,-30.92);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(217.0/255.0, 134.0/255.0, 57.0/255.0);
	glVertex2f(-53.51,-30.00);
	glVertex2f(-53.59,-32.01);
	glVertex2f(-52.34,-30.76);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(205.0/255.0, 123.0/255.0, 51.0/255.0);
	glVertex2f(-53.51,-30.00);
	glVertex2f(-51.42,-29.42);
	glVertex2f(-52.34,-30.76);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(199.0/255.0, 115.0/255.0, 42.0/255.0);
	glVertex2f(-53.59,-32.01);
	glVertex2f(-52.34,-30.76);
	glVertex2f(-51.50,-31.51);	
	glVertex2f(-52.17,-32.76);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(180.0/255.0, 100.0/255.0, 38.0/255.0);
	glVertex2f(-51.42,-29.42);
	glVertex2f(-51.50,-31.51);	
	glVertex2f(-52.34,-30.76);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(107.0/255.0, 57.0/255.0, 31.0/255.0);
	glVertex2f(-51.42,-29.42);
	glVertex2f(-50.08,-29.50);	
	glVertex2f(-50.42,-31.09);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(149.0/255.0, 78.0/255.0, 31.0/255.0);
	glVertex2f(-51.42,-29.42);
	glVertex2f(-51.50,-31.51);	
	glVertex2f(-50.42,-31.09);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(153.0/255.0, 79.0/255.0, 35.0/255.0);
	glVertex2f(-50.08,-32.00);
	glVertex2f(-51.50,-31.51);	
	glVertex2f(-50.42,-31.09);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(168.0/255.0, 79.0/255.0, 28.0/255.0);
	glVertex2f(-52.17,-32.76);
	glVertex2f(-51.50,-31.51);	
	glVertex2f(-50.08,-32.00);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(199.0/255.0, 115.0/255.0, 42.0/255.0);
	glVertex2f(-50.08,-29.50);	
	glVertex2f(-49.33,-29.34);
	glVertex2f(-49.50,-32.51);
	glVertex2f(-50.08,-32.00);
	glVertex2f(-50.42,-31.09);	
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(154.0/255.0, 76.0/255.0, 29.0/255.0);
	glVertex2f(-49.33,-29.34);
	glVertex2f(-48.33,-29.17);	
	glVertex2f(-48.66,-31.17);
	glVertex2f(-49.50,-32.51);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(86.0/255.0, 36.0/255.0, 17.0/255.0);
	glVertex2f(-49.50,-32.51);
	glVertex2f(-50.58,-32.68);
	glVertex2f(-52.17,-32.76);	
	glVertex2f(-50.08,-32.00);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(124.0/255.0, 61.0/255.0, 20.0/255.0);
	glVertex2f(-50.58,-32.68);
	glVertex2f(-50.58,-33.26);	
	glVertex2f(-49.50,-32.51);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(118.0/255.0, 39.0/255.0, 10.0/255.0);
	glVertex2f(-54.93,-32.93);
	glVertex2f(-52.92,-32.93);
	glVertex2f(-52.17,-32.76);	
	glVertex2f(-50.58,-32.68);
	glVertex2f(-50.58,-33.26);
	glVertex2f(-51.75,-33.43);
	glVertex2f(-52.09,-33.51);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(101.0/255.0, 36.0/255.0, 10.0/255.0);
	glVertex2f(-54.18,-34.01);
	glVertex2f(-54.93,-32.93);	
	glVertex2f(-56.35,-33.93);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(84.0/255.0, 32.0/255.0, 10.0/255.0);
	glVertex2f(-54.18,-34.01);
	glVertex2f(-54.93,-32.93);	
	glVertex2f(-52.09,-33.51);	
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(84.0/255.0, 32.0/255.0, 10.0/255.0);
	glVertex2f(-54.18,-34.01);
	glVertex2f(-54.93,-32.93);	
	glVertex2f(-52.09,-33.51);	
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(148.0/255.0, 64.0/255.0, 19.0/255.0);
	glVertex2f(-51.75,-33.43);
	glVertex2f(-52.09,-33.51);	
	glVertex2f(-52.50,-35.52);	
	glVertex2f(-53.17,-36.85);
	glVertex2f(-51.50,-35.60);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(112.0/255.0, 44.0/255.0, 16.0/255.0);
	glVertex2f(-54.18,-34.01);
	glVertex2f(-52.50,-35.52);	
	glVertex2f(-52.09,-33.51);	
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(133.0/255.0, 54.0/255.0, 17.0/255.0);
	glVertex2f(-54.18,-34.01);
	glVertex2f(-52.50,-35.52);	
	glVertex2f(-53.17,-36.85);	
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(150.0/255.0, 62.0/255.0, 18.0/255.0);
	glVertex2f(-54.18,-34.01);
	glVertex2f(-55.51,-36.85);	
	glVertex2f(-53.17,-36.85);	
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(134.0/255.0, 54.0/255.0, 15.0/255.0);
	glVertex2f(-54.18,-34.01);
	glVertex2f(-55.51,-36.85);	
	glVertex2f(-56.35,-33.93);	
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(159.0/255.0, 67.0/255.0, 15.0/255.0);
	glVertex2f(-58.35,-35.68);
	glVertex2f(-55.51,-36.85);	
	glVertex2f(-56.35,-33.93);	
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(185.0/255.0, 89.0/255.0, 24.0/255.0);
	glVertex2f(-58.35,-35.68);
	glVertex2f(-55.51,-36.85);	
	glVertex2f(-57.60,-39.36);	
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(152.0/255.0, 62.0/255.0, 14.0/255.0);
	glVertex2f(-58.35,-35.68);
	glVertex2f(-59.27,-39.44);	
	glVertex2f(-57.60,-39.36);	
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(167.0/255.0, 72.0/255.0, 19.0/255.0);
	glVertex2f(-54.51,-39.78);
	glVertex2f(-55.51,-36.85);	
	glVertex2f(-53.17,-36.85);	
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(146.0/255.0, 62.0/255.0, 14.0/255.0);
	glVertex2f(-54.51,-39.78);
	glVertex2f(-52.42,-39.36);	
	glVertex2f(-53.17,-36.85);	
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(177.0/255.0, 82.0/255.0, 21.0/255.0);
	glVertex2f(-51.50,-35.60);
	glVertex2f(-52.42,-39.36);	
	glVertex2f(-53.17,-36.85);	
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(142.0/255.0, 55.0/255.0, 12.0/255.0);
	glVertex2f(-54.51,-39.78);
	glVertex2f(-55.51,-36.85);	
	glVertex2f(-56.60,-41.28);	
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(153.0/255.0, 65.0/255.0, 17.0/255.0);
	glVertex2f(-57.60,-39.36);
	glVertex2f(-55.51,-36.85);	
	glVertex2f(-56.60,-41.28);	
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(133.0/255.0,50.0/255.0, 13.0/255.0);
	glVertex2f(-57.60,-39.36);
	glVertex2f(-59.27,-39.44);	
	glVertex2f(-57.94,-40.95);	
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(116.0/255.0,44.0/255.0, 13.0/255.0);
	glVertex2f(-59.19,-42.37);
	glVertex2f(-59.27,-39.44);	
	glVertex2f(-57.94,-40.95);	
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(120.0/255.0,45.0/255.0, 12.0/255.0);
	glVertex2f(-57.60,-39.36);
	glVertex2f(-56.60,-41.28);	
	glVertex2f(-57.94,-40.95);	
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(78.0/255.0,24.0/255.0, 6.0/255.0);
	glVertex2f(-59.19,-42.37);
	glVertex2f(-59.10,-43.96);	
	glVertex2f(-58.69,-43.87);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(88.0/255.0,32.0/255.0, 13.0/255.0);
	glVertex2f(-59.19,-42.37);
	glVertex2f(-57.94,-40.95);	
	glVertex2f(-58.69,-43.87);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(104.0/255.0,37.0/255.0, 11.0/255.0);
	glVertex2f(-56.60,-41.28);
	glVertex2f(-57.94,-40.95);	
	glVertex2f(-58.69,-43.87);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(130.0/255.0,51.0/255.0, 14.0/255.0);
	glVertex2f(-54.51,-39.78);
	glVertex2f(-52.42,-39.36);	
	glVertex2f(-54.43,-42.20);	
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(106.0/255.0, 39.0/255.0, 12.0/255.0);
	glVertex2f(-58.69,-43.87);
	glVertex2f(-57.10,-43.04);	
	glVertex2f(-55.76,-41.78);	
	glVertex2f(-54.51,-39.78);	
	glVertex2f(-56.60,-41.28);	
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(88.0/255.0, 34.0/255.0, 13.0/255.0);
	glVertex2f(-54.51,-39.78);
	glVertex2f(-54.43,-42.20);	
	glVertex2f(-56.18,-44.62);	
	glVertex2f(-55.76,-41.78);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(63.0/255.0, 26.0/255.0, 14.0/255.0);
	glVertex2f(-57.10,-43.04);
	glVertex2f(-55.76,-41.78);	
	glVertex2f(-56.18,-44.62);	
	glVertex2f(-56.52,-44.87);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(107.0/255.0, 45.0/255.0, 20.0/255.0);
	glVertex2f(-52.42,-39.36);
	glVertex2f(-54.43,-42.20);	
	glVertex2f(-54.26,-44.62);	
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(87.0/255.0, 40.0/255.0, 18.0/255.0);
	glVertex2f(-55.43,-45.38);
	glVertex2f(-54.43,-42.20);	
	glVertex2f(-54.26,-44.62);	
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(70.0/255.0, 32.0/255.0, 16.0/255.0);
	glVertex2f(-55.43,-45.38);
	glVertex2f(-54.43,-42.20);	
	glVertex2f(-56.18,-44.62);	
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(54.0/255.0, 27.0/255.0, 14.0/255.0);
	glVertex2f(-55.43,-45.38);
	glVertex2f(-56.18,-44.62);	
	glVertex2f(-56.51,-44.87);	
	glVertex2f(-56.35,-45.54);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(61.0/255.0, 31.0/255.0, 17.0/255.0);
	glVertex2f(-56.35,-45.54);
	glVertex2f(-55.43,-45.38);
	glVertex2f(-55.68,-47.88);	
	glVertex2f(-56.10,-47.71);	
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(76.0/255.0, 39.0/255.0, 20.0/255.0);
	glVertex2f(-54.43,-48.63);
	glVertex2f(-55.43,-45.38);
	glVertex2f(-55.68,-47.88);	
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(63.0/255.0, 30.0/255.0, 17.0/255.0);
	glVertex2f(-55.43,-45.38);
	glVertex2f(-54.43,-48.63);
	glVertex2f(-54.18,-48.05);	
	glVertex2f(-53.67,-48.47);
	glVertex2f(-52.17,-48.55);
	glVertex2f(-54.26,-47.46);
	glVertex2f(-53.92,-46.38);
	glVertex2f(-54.26,-44.62);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(77.0/255.0, 38.0/255.0, 21.0/255.0);
	glVertex2f(-54.26,-47.46);
	glVertex2f(-53.92,-46.38);
	glVertex2f(-52.17,-48.55);	
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(80.0/255.0, 43.0/255.0, 20.0/255.0);
	glVertex2f(-53.92,-46.38);
	glVertex2f(-52.00,-47.88);
	glVertex2f(-52.92,-47.71);	
	glVertex2f(-52.17,-48.55);	
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(68.0/255.0, 32.0/255.0, 18.0/255.0);
	glVertex2f(-60.52,-44.37);
	glVertex2f(-61.19,-46.55);
	glVertex2f(-58.85,-45.79);	
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(81.0/255.0, 40.0/255.0, 24.0/255.0);
	glVertex2f(-61.19,-46.55);
	glVertex2f(-58.85,-45.79);	
	glVertex2f(-59.36,-47.55);
	glVertex2f(-60.27,-48.72);
	glVertex2f(-61.28,-49.39);
	glVertex2f(-61.61,-48.55);	
	glVertex2f(-61.19,-47.80);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(82.0/255.0, 44.0/255.0, 27.0/255.0);
	glVertex2f(-59.36,-47.55);
	glVertex2f(-60.27,-48.72);
	glVertex2f(-59.61,-49.30);
	glVertex2f(-58.52,-49.55);	
	glVertex2f(-58.35,-48.88);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(67.0/255.0, 34.0/255.0, 19.0/255.0);
	glVertex2f(-58.85,-45.79);	
	glVertex2f(-59.36,-47.55);
	glVertex2f(-58.52,-49.55);
	glVertex2f(-58.35,-48.88);
	glVertex2f(-57.35,-49.30);
	glVertex2f(-56.60,-49.22);	
	glVertex2f(-58.27,-48.38);
	glVertex2f(-58.27,-47.63);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(83.0/255.0, 47.0/255.0, 29.0/255.0);
	glVertex2f(-58.27,-48.38);
	glVertex2f(-58.27,-47.63);
	glVertex2f(-56.60,-49.22);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(83.0/255.0, 47.0/255.0, 29.0/255.0);
	glVertex2f(-58.27,-48.38);
	glVertex2f(-58.27,-47.63);
	glVertex2f(-56.60,-49.22);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(60.0/255.0, 26.0/255.0, 12.0/255.0);
	glVertex2f(-70.13,-45.79);
	glVertex2f(-67.63,-45.63);
	glVertex2f(-69.38,-47.05);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(66.0/255.0, 35.0/255.0, 16.0/255.0);
	glVertex2f(-67.88,-47.21);
	glVertex2f(-67.63,-45.63);
	glVertex2f(-69.38,-47.05);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(97.0/255.0, 54.0/255.0, 29.0/255.0);
	glVertex2f(-67.88,-47.21);
	glVertex2f(-66.54,-48.38);
	glVertex2f(-69.38,-47.05);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(79.0/255.0, 42.0/255.0, 20.0/255.0);
	glVertex2f(-67.63,-45.63);
	glVertex2f(-67.88,-47.21);
	glVertex2f(-66.54,-48.38);
	glVertex2f(-66.21,-47.38);
	glVertex2f(-66.79,-46.88);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(61.0/255.0, 34.0/255.0, 20.0/255.0);
	glVertex2f(-67.63,-45.63);
	glVertex2f(-66.54,-48.38);
	glVertex2f(-66.29,-47.88);
	glVertex2f(-65.70,-48.13);
	glVertex2f(-64.54,-48.22);
	glVertex2f(-66.21,-47.38);
	glVertex2f(-66.46,-46.29);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(81.0/255.0, 44.0/255.0, 23.0/255.0);
	glVertex2f(-67.63,-45.63);
	glVertex2f(-65.79,-46.21);
	glVertex2f(-65.12,-46.96);
	glVertex2f(-64.54,-48.22);
	glVertex2f(-66.21,-47.38);
	glVertex2f(-66.46,-46.29);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(64.0/255.0, 37.0/255.0, 21.0/255.0);
	glVertex2f(-65.79,-46.21);
	glVertex2f(-65.04,-46.38);
	glVertex2f(-64.20,-47.13);
	glVertex2f(-63.95,-47.71);
	glVertex2f(-65.12,-46.96);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(46.0/255.0, 17.0/255.0, 4.0/255.0);
	glVertex2f(-65.12,-46.96);
	glVertex2f(-64.54,-48.22);
	glVertex2f(-64.54,-47.71);
	glVertex2f(-63.95,-47.71);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(43.0/255.0, 13.0/255.0, 4.0/255.0);
	glVertex2f(-67.63,-45.63);
	glVertex2f(-64.62,-45.63);
	glVertex2f(-63.87,-46.63);
	glVertex2f(-65.04,-46.38);
	glVertex2f(-65.79,-46.21);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(47.0/255.0, 14.0/255.0, 4.0/255.0);
	glVertex2f(-64.62,-45.63);
	glVertex2f(-61.86,-44.96);
	glVertex2f(-63.87,-46.63);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(58.0/255.0, 22.0/255.0, 11.0/255.0);
	glVertex2f(-63.87,-46.63);
	glVertex2f(-61.86,-44.96);
	glVertex2f(-61.19,-46.55);
	glVertex2f(-61.19,-46.88);
	glEnd();
}

void actualizarCapi() {
	if (capi_saltando) {
		capi_posicionX += capi_velocidadX;
		capi_posicionY += capi_velocidadY;
		capi_velocidadY += gravedad;
		
		if (capi_posicionY <= sueloY) {
			capi_posicionY = sueloY;
			capi_saltando = false;
			capi_velocidadY = 0;
			capi_velocidadX = 0;
		}
	}
	verificarColisiones();
}

void timer(int value) {
	float deltaTime = 0.016f; // 16 ms ˜ 1/60 segundos
	actualizarCapi();
	moverRocas(deltaTime);
	glutPostRedisplay();
	glutTimerFunc(16, timer, 0);
}

void dibujarBox(float x, float y, float ancho, float alto) {
	glColor3f(1, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(x - ancho/2, y - alto/2);
	glVertex2f(x + ancho/2, y - alto/2);
	glVertex2f(x + ancho/2, y + alto/2);
	glVertex2f(x - ancho/2, y + alto/2);
	glEnd();
}

void graficar() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	nubes(-55, 35);
	nubes(-20, 40);
	nubes(20, 45);
	montanas();
	pradera();
	orilla();
	rio();
	sol();
	arboles();
	
	glPushMatrix();
	glTranslatef(r1_posicionX, r1_posicionY, 0);
	roca1();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(r2_posicionX, r2_posicionY, 0);
	roca2();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(capi_posicionX, capi_posicionY, 0);
	capibara();
	glPopMatrix();

	dibujarBox(r1_posicionX, r1_posicionY, roca_ancho, roca_alto);
	dibujarBox(r2_posicionX, r2_posicionY, roca_ancho, roca_alto);
	
	dibujarBox(capi_posicionX + capi_offsetX,
	capi_posicionY + capi_offsetY,
	capi_ancho, capi_alto);
	
	glFlush();
}

void manejarTeclado(unsigned char key, int x, int y) {
	switch (key) {
	case 'w':
	case 'W':
		if (!capi_saltando) capi_posicionY += 5;
		break;
		
	case 's':
	case 'S':
		if (!capi_saltando) capi_posicionY -= 5;
		break;
		
	case 'a':
	case 'A':
		if (!capi_saltando) capi_posicionX -= 5;
		break;
		
	case 'd':
	case 'D':
		if (!capi_saltando) capi_posicionX += 5;
		break;
		
	case 'x':
	case 'X':
		if (!capi_saltando) {
			capi_saltando = true;
			capi_velocidadY = 5;
			capi_velocidadX = 2;
		}
		break;
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1280, 700);
	glutInitWindowPosition(300, 200);
	glutCreateWindow("Capibara Aventura");
	inicializar();
	
	glutDisplayFunc(graficar);
	glutReshapeFunc(redimensionar);
	glutKeyboardFunc(manejarTeclado);
	glutTimerFunc(100, timer, 0);
	
	glutMainLoop();
	return 0;
}