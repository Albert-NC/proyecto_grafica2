#include <GL/glut.h>
#include <cmath>

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	
	// =================== CIELO DETALLADO ===================
	glBegin(GL_QUADS);
	glColor3f(0.2f, 0.4f, 0.8f); glVertex2f(-1.0f, 1.0f);
	glColor3f(0.3f, 0.5f, 0.9f); glVertex2f(-0.5f, 1.0f);
	glColor3f(0.3f, 0.6f, 1.0f); glVertex2f(-0.5f, 0.7f);
	glColor3f(0.2f, 0.5f, 0.9f); glVertex2f(-1.0f, 0.7f);
	glEnd();
	
	glBegin(GL_QUADS);
	glColor3f(0.25f, 0.45f, 0.85f); glVertex2f(-0.5f, 1.0f);
	glColor3f(0.35f, 0.55f, 0.95f); glVertex2f(0.0f, 1.0f);
	glColor3f(0.35f, 0.65f, 0.95f); glVertex2f(0.0f, 0.7f);
	glColor3f(0.25f, 0.55f, 0.9f);  glVertex2f(-0.5f, 0.7f);
	glEnd();
	
	glBegin(GL_QUADS);
	glColor3f(0.3f, 0.5f, 0.85f); glVertex2f(0.0f, 1.0f);
	glColor3f(0.4f, 0.6f, 0.9f); glVertex2f(0.5f, 1.0f);
	glColor3f(0.45f, 0.7f, 1.0f); glVertex2f(0.5f, 0.7f);
	glColor3f(0.35f, 0.65f, 0.95f); glVertex2f(0.0f, 0.7f);
	glEnd();
	
	glBegin(GL_QUADS);
	glColor3f(0.35f, 0.55f, 0.9f); glVertex2f(0.5f, 1.0f);
	glColor3f(0.4f, 0.6f, 0.95f); glVertex2f(1.0f, 1.0f);
	glColor3f(0.45f, 0.7f, 0.95f); glVertex2f(1.0f, 0.7f);
	glColor3f(0.4f, 0.65f, 0.9f); glVertex2f(0.5f, 0.7f);
	glEnd();
	
	// =================== SOL ===================
	float cx = 0.6f, cy = 0.7f, r = 0.2f;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 0.95f, 0.0f);
	glVertex2f(cx, cy);
	for (int i = 0; i <= 360; i += 10) {
		float rad = i * 3.14159f / 180.0f;
		float rr = r + ((i % 20 == 0) ? 0.05f : 0.0f);
		glColor3f(1.0f, 0.9f - 0.002f*i, 0.0f + 0.002f*i);
		glVertex2f(cx + rr * cos(rad), cy + rr * sin(rad));
	}
	glEnd();
	
	// =================== MONTAÑAS ===================
	glBegin(GL_TRIANGLES);
	glColor3f(0.4f, 0.3f, 0.2f); glVertex2f(-1.0f, 0.2f);
	glColor3f(0.5f, 0.4f, 0.3f); glVertex2f(-0.5f, 0.8f);
	glColor3f(0.3f, 0.2f, 0.1f); glVertex2f(0.0f, 0.2f);
	glEnd();
	
	glBegin(GL_TRIANGLES);
	glColor3f(0.5f, 0.35f, 0.2f); glVertex2f(-0.2f, 0.2f);
	glColor3f(0.6f, 0.4f, 0.25f); glVertex2f(0.3f, 0.9f);
	glColor3f(0.4f, 0.3f, 0.2f); glVertex2f(0.8f, 0.2f);
	glEnd();
	
	// =================== PASTO ===================
	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.6f, 0.2f); glVertex2f(-1.0f, 0.2f);
	glColor3f(0.0f, 0.7f, 0.3f); glVertex2f(1.0f, 0.2f);
	glColor3f(0.0f, 0.5f, 0.2f); glVertex2f(1.0f, -1.0f);
	glColor3f(0.0f, 0.4f, 0.2f); glVertex2f(-1.0f, -1.0f);
	glEnd();
	
	// =================== CASA ===================
	// Pared
	glBegin(GL_QUADS);
	glColor3f(0.9f, 0.6f, 0.4f); glVertex2f(-0.8f, -0.6f);
	glColor3f(0.9f, 0.6f, 0.4f); glVertex2f(-0.5f, -0.6f);
	glColor3f(0.8f, 0.5f, 0.3f); glVertex2f(-0.5f, -0.3f);
	glColor3f(0.8f, 0.5f, 0.3f); glVertex2f(-0.8f, -0.3f);
	glEnd();
	
	// Techo
	glBegin(GL_TRIANGLES);
	glColor3f(0.7f, 0.1f, 0.1f); glVertex2f(-0.85f, -0.3f);
	glColor3f(0.8f, 0.2f, 0.2f); glVertex2f(-0.45f, -0.3f);
	glColor3f(0.6f, 0.1f, 0.1f); glVertex2f(-0.65f, -0.1f);
	glEnd();
	
	// Puerta
	glBegin(GL_QUADS);
	glColor3f(0.3f, 0.2f, 0.1f); glVertex2f(-0.72f, -0.6f);
	glColor3f(0.3f, 0.2f, 0.1f); glVertex2f(-0.6f, -0.6f);
	glColor3f(0.2f, 0.1f, 0.05f); glVertex2f(-0.6f, -0.4f);
	glColor3f(0.2f, 0.1f, 0.05f); glVertex2f(-0.72f, -0.4f);
	glEnd();
	
	// Ventana
	glBegin(GL_QUADS);
	glColor3f(0.6f, 0.8f, 1.0f); glVertex2f(-0.58f, -0.5f);
	glColor3f(0.6f, 0.8f, 1.0f); glVertex2f(-0.52f, -0.5f);
	glColor3f(0.5f, 0.7f, 0.9f); glVertex2f(-0.52f, -0.45f);
	glColor3f(0.5f, 0.7f, 0.9f); glVertex2f(-0.58f, -0.45f);
	glEnd();
	
	// =================== ÁRBOL ===================
	// Tronco
	glBegin(GL_QUADS);
	glColor3f(0.4f, 0.2f, 0.1f); glVertex2f(0.4f, -0.6f);
	glColor3f(0.4f, 0.2f, 0.1f); glVertex2f(0.5f, -0.6f);
	glColor3f(0.3f, 0.15f, 0.05f); glVertex2f(0.5f, -0.3f);
	glColor3f(0.3f, 0.15f, 0.05f); glVertex2f(0.4f, -0.3f);
	glEnd();
	
	// Copa
	glBegin(GL_POLYGON);
	glColor3f(0.0f, 0.5f, 0.0f);
	for (int i = 0; i < 360; i += 20) {
		float rad = i * 3.14159f / 180.0f;
		glVertex2f(0.45f + 0.2f*cos(rad), -0.3f + 0.2f*sin(rad));
	}
	glEnd();
	
	// =================== FLORES ===================
	glPointSize(6.0f);
	glBegin(GL_POINTS);
	glColor3f(1.0f, 0.0f, 0.0f); glVertex2f(-0.2f, -0.8f);
	glColor3f(1.0f, 0.5f, 0.0f); glVertex2f(-0.1f, -0.85f);
	glColor3f(1.0f, 1.0f, 0.0f); glVertex2f(-0.15f, -0.9f);
	glColor3f(0.8f, 0.0f, 0.8f); glVertex2f(-0.25f, -0.85f);
	glEnd();
	
	glFlush();
}

void init() {
	glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1, 1, -1, 1);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Paisaje Vitral OpenGL");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}