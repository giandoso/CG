#include <GL/glut.h>
#include <stdlib.h>

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

  //glColor3f(1.0, 1.0, 1.0);

	//Triangulo Base Cima
	glPushMatrix();
	glTranslatef(-1.0, 0.0, 0.0);
	glScalef(2.0, 1.0, 1.0);
			//transformação

	DrawTriangle();
	glPopMatrix(); //Interrompe as alterações aos blocos seguintes
		
	//Triangulo Base Baixo
	glPushMatrix();
	glRotatef(180.0, 0.0, 0.0, 1.0);
	glTranslatef(-1.0, 0.0, 0.0);
	glScalef(2.0, 1.0, 1.0);
	DrawTriangle();
	glPopMatrix();

	int i;
	float contRotate = 0.0;
	//float r=0.25,g=0.25,b=0.25;
	//Color change
	glColor3f(1.0, 0.0 , 0.0);	
	for (i=0 , contRotate = 0.0 ; i < 4; i++ , contRotate += 90.0){ 
	
		glPushMatrix();
		glRotatef(contRotate, 0.0, 0.0, 1.0);
		glTranslatef(-0.5, 1.0, 0.0);
		glScalef(1.0, 0.5, 0.5);
		DrawTriangle();

		

		//r+=0.33;
		//g+=0.25;		
		//b+=0.25;

		glPopMatrix();
	}
/*
	Triangulo 5
	glPushMatrix();
	glRotatef(0.0, 0.0, 0.0, 1.0);
	glTranslatef(-0.5, 1.0, 0.0);
	DrawTriangle();
	glPopMatrix();

	Triangulo 3
	glPushMatrix();
	glRotatef(90.0, 0.0, 0.0, 1.0);
	glTranslatef(-0.5, 1.0, 0.0);
	DrawTriangle();
	glPopMatrix();

	Triangulo 5
	glPushMatrix();
	glRotatef(180.0, 0.0, 0.0, 1.0);
	glTranslatef(-0.5, 1.0, 0.0);
	DrawTriangle();
	glPopMatrix();

	Triangulo 4
	glPushMatrix();
	glRotatef(270.0, 0.0, 0.0, 1.0);
	glTranslatef(-0.5, 1.0, 0.0);
	DrawTriangle();
	glPopMatrix();




*/

  glutSwapBuffers();
}
