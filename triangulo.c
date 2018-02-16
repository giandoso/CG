#include <GL/glut.h>
#include <stdlib.h>
#define AZUL     0.0, 0.0, 1.0
#define VERMELHO 1.0, 0.0, 0.0
#define AMARELO  1.0, 1.0, 0.0
#define VERDE    0.0, 1.0, 0.0
#define CYAN     1.0, 0.0, 1.0
#define LARANJA  0.8, 0.6, 0.1
#define ROSEO    0.7, 0.1, 0.6
#define CINZA    0.6, 0.6, 0.6


void init(void);
void display(void);
void reshape (int w, int h);
void keyboard(unsigned char key, int x, int y);

int main(int argc, char** argv){
  int i;
  char a;
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize (400, 400);
  glutInitWindowPosition (100, 100);
  glutCreateWindow (argv[0]);
  init();
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutReshapeFunc(reshape);
  glutMainLoop();
  return 0;
}

void init(void){
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glLoadIdentity();
  glOrtho (-5, 5, -5, 5, -5 , 5);
}

void reshape (int w, int h){
}

void DrawTriangle(void){
  glPushMatrix();
  glBegin(GL_LINE_LOOP);
  glVertex2f(0.0, 0.0);
  glVertex2f(1.0, 0.0);
  glVertex2f(0.5, 1.0);
  glEnd();
  glPopMatrix();
}

void keyboard(unsigned char key, int x, int y){
  switch (key){
    case 27:
      exit (0);
      break;
  }
}

void display(){

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  // Desenha o sistema de coordenadas.
  glBegin(GL_LINES);
  // Eixo x.
  glColor3f(1.0, 0.0, 0.0);
  glVertex2f(-5.0, 0.0);
  glVertex2f(5.0, 0.0);
  // Eixo y.
  glColor3f(0.0, 0.0, 1.0);
  glVertex2f(0.0, 5.0);
  glVertex2f(0.0, -5.0);
  glEnd();


  glPushMatrix();
  glTranslatef(2.0, -1.0, 0.0);
  glScalef(2.0, 0.5, 1.0);
  glRotatef(90.0, 0.0, 0.0, 1.0);
  DrawTriangle();
  glPopMatrix();

  glPushMatrix();
  glColor3f(VERMELHO);
  glRotatef(90.0, 0.0, 0.0, 1.0);
  glScalef(2.0, 1.0, 1.0);
  glTranslatef(0.0, -2.0, 0.0);
  DrawTriangle();
  glPopMatrix();

  glPushMatrix();
  glColor3f(AMARELO);
  glTranslatef(-1.0,0.0,0.0);
  glRotatef(135.0,0.0,0.0,1.0);
  glTranslatef(-1.0,0.0,0.0);
  DrawTriangle();
  glPopMatrix();

  glPushMatrix();
  glColor3f(VERDE);
  glRotatef(180.0, 0.0, 0.0, 1.0);
  glTranslatef(-0.5,-2.0,0.0);
  glScalef(1.0,2.0,1.0);
  DrawTriangle();
  glPopMatrix();

  glPushMatrix();
  glColor3f(LARANJA);
  glTranslatef(-1.0,0.0,0.0);
  glRotatef(-45.0,0.0,0.0,1.0);
  glScalef(0.5,1.0,1.0);
  glTranslatef(-1.0,0.0,0.0);
  DrawTriangle();
  glPopMatrix();

  glPushMatrix();
  glColor3f(AMARELO);
  glRotatef(270.0, 0.0, 0.0, 1.0);
  glTranslatef(-3.0,-2.0,0.0);

  DrawTriangle();
  glPopMatrix();

  // glPushMatrix();
  // glColor3f(VERDE);
  // glScalef(0.5,1.0,1.0);
  // glTranslatef(-3.0,0.0,0.0);
  // glRotatef(-45.0, 0.0, 0.0, 1.0);
  // DrawTriangle();
  // glPopMatrix();

  // glPushMatrix();
  // glColor3f(VERDE);
  // glRotatef(0.0, 0.0, 0.0, 1.0);
  // glTranslatef(-3.0, 1.0, 0.0);
  // glScalef(2.0, 1.0, 1.0);
  // DrawTriangle();
  // glPopMatrix();


  // glPushMatrix();
  // glColor3f(AZUL);
  // glTranslatef(2.0, 2.5, 0.0);
  // glRotatef(90.0, 0.0, 0.0, 1.0);
  // glScalef(1.0, 2.0, 1.0);
  // DrawTriangle();
  // glPopMatrix();
  //
  // glPushMatrix();
  // glColor3f(VERMELHO);
  // glTranslatef(-1.0, 0.0, 0.0);
  // glRotatef(-180.0, 0.0, 0.0, 1.0);
  // glScalef(1.0, 0.5, 1.0);
  // DrawTriangle();
  // glPopMatrix();
  //
  // glPushMatrix();
  // glColor3f(AMARELO);
	// glScalef(1.0, -1.0, 1.0);
  // glRotatef(45.0, 0.0, 0.0, 1.0);
  // glTranslatef(2.0, 0.0, 0.0);
  // DrawTriangle();
  // glPopMatrix();
  //
	// glPushMatrix();
  // glColor3f(VERDE);
	// glRotatef(0.0, 0.0, 0.0, 1.0);
	// glTranslatef(-3.0, 1.0, 0.0);
  // glScalef(2.0, 1.0, 1.0);
	// DrawTriangle();
	// glPopMatrix();
  //
	// glPushMatrix();
  // glColor3f(CYAN);
	// glTranslatef(0.0, 2.0, 0.0);
	// glRotatef(270.0, 0.0, 0.0, 1.0);
  // glScalef(2.0, 1.0, 1.0);
	// DrawTriangle();
	// glPopMatrix();
  // //
	// glPushMatrix();
  // glColor3f(LARANJA);
	// glRotatef(90.0, 0.0, 0.0, 1.0);
	// glTranslatef(-2.0, 1.0, 0.0);
  // glScalef(1.0, 2.0, 1.0);
	// DrawTriangle();
	// glPopMatrix();


/*
	glPushMatrix();
	glRotatef(180.0, 0.0, 0.0, 1.0);
	glTranslatef(-1.0, 0.0, 0.0);
	glScalef(2.0, 1.0, 1.0);
	DrawTriangle();
	glPopMatrix();


	glPushMatrix();
	glRotatef(90.0, 0.0, 0.0, 1.0);
	glTranslatef(-0.5, 1.0, 0.0);
	DrawTriangle();
	glPopMatrix();


	glPushMatrix();
	glRotatef(270.0, 0.0, 0.0, 1.0);
	glTranslatef(-0.5, 1.0, 0.0);
	DrawTriangle();
	glPopMatrix();


	glPushMatrix();
	glRotatef(0.0, 0.0, 0.0, 1.0);
	glTranslatef(-0.5, 1.0, 0.0);
	DrawTriangle();
	glPopMatrix();


	glPushMatrix();
	glRotatef(180.0, 0.0, 0.0, 1.0);
	glTranslatef(-0.5, 1.0, 0.0);
	DrawTriangle();
	glPopMatrix();



  // Triangulo 1
  glPushMatrix();
  glRotatef(135.0, 0.0, 0.0, 1.0);
  glTranslatef(2.0, 0.0, 0.0);
  DrawTriangle();
  glPopMatrix();

  // Triangulo 2
  glPushMatrix();
  glTranslatef(-1.0, 2.0, 0.0);
  glScalef(2.0, -0.5, 1.0);
  DrawTriangle();
  glPopMatrix();

  // Triangulo 3
  glPushMatrix();
  glTranslatef(1.0, 1.0, 0.0);
  glScalef(0.5, -1.0, 1.0);
  DrawTriangle();
  glPopMatrix();

  // Triangulo 4
  glPushMatrix();
  glTranslatef(2.0, -1.0, 0.0);
  glRotatef(90.0, 0.0, 0.0, 1.0);
  glScalef(1.0, 2.0, 1.0);
  DrawTriangle();
  glPopMatrix();

  // Triangulo 5
  glPushMatrix();
  glTranslatef(-2.0, 0.0, 0.0);
  glRotatef(-90.0, 0.0, 0.0, 1.0);
  glScalef(1.0, 0.5, 1.0);
  DrawTriangle();
  glPopMatrix();

  // Triangulo Teste
  glPushMatrix();
  glColor3f(1.0, 0.0, 0.0);
  glTranslatef(-0.5, 0.0, 0.0);
//  glRotatef(-90.0, 0.0, 0.0, 1.0);
  glScalef(2.0, -0.5, 1.0);
  glTranslatef(0.0, 2.0, 0.0);
  DrawTriangle();
  glPopMatrix();
*/
  glutSwapBuffers();
}
