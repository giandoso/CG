#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


FILE *arq;

void init(void);
void display(void);
void keyboard(unsigned char key, int x, int y);
void reshape (int w, int h);
void special(int key, int x, int y);
void idle();
void idle2();

#define AZUL     0.0, 0.0, 1.0
#define VERMELHO 1.0, 0.0, 0.0
#define AMARELO  1.0, 1.0, 0.0
#define VERDE    0.0, 1.0, 0.0
#define CYAN     1.0, 0.0, 1.0
#define LARANJA  0.8, 0.6, 0.1
#define ROSEO    0.7, 0.1, 0.6
#define CINZA    0.6, 0.6, 0.6

static GLfloat *vertices;
float lixo; 

static GLint **indices;
    
static int eixox;
int largura, altura, nvert, nfaces;

char cadeia[50];

int obsy = 0, obsx =0; 

float  eixoy=0.0;

void idle(){
	eixoy = fmod(eixoy - 0.1,360.0);
	glutPostRedisplay();
}
void idle2(){
	eixoy = fmod(eixoy + 0.1,360.0);
	glutPostRedisplay();
}

int main(int argc, char** argv){
  int i;

  if (!(arq = fopen ("bun_zipper_res4.ply", "r"))) {
    printf("Arquivo não foi aberto.\n");
    exit(1);
  }

  printf("\n Arquivo aberto.\n");
  fscanf(arq, "%s", cadeia);
  while (strcmp(cadeia, "end_header")){
    fscanf(arq, "%s", cadeia);
    if (!strcmp(cadeia, "element")){
      fscanf(arq, "%s", cadeia);
      if (!strcmp(cadeia, "vertex")){
        fscanf(arq, "%d", &nvert);
        printf(" Vertices %d\n", nvert);
      }
      if (!strcmp(cadeia, "face")){
        fscanf(arq, "%d", &nfaces);
        printf(" Faces %d\n", nfaces);
      }
    }
  }

  vertices = malloc(3 * nvert * sizeof(GLfloat));
  for (int j = 0; j < nvert; j++){
    for (int i = 0; i < 3; i++){
      fscanf(arq, "%f", &vertices[3*j+i]);
      //printf(" %f ", vertices[3*j+i]);
    }
    fscanf(arq, "%f", &lixo);
    fscanf(arq, "%f", &lixo);
  }

  indices = malloc(nfaces * sizeof(GLint *));
  for (int i = 0; i < nfaces; i++){
    fscanf(arq, "%f", &lixo);
    indices[i] = malloc(3 * sizeof(GLint));
    for (int j = 0; j < 3; j++){
      fscanf(arq, "%d", &indices[i][j]);
      //printf(" %d ", indices[i][j]);
    }
  }
  
  fclose(arq);
  printf(" Fechou o arquivo.\n\n");

  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize (500, 500); 
  glutInitWindowPosition (100, 100); 
  glutCreateWindow (argv[0]);
  init();
  glutDisplayFunc(display); 
	glutSpecialFunc(special);
  glutKeyboardFunc(keyboard);
  glutReshapeFunc(reshape);
  glutMainLoop();
  return 0;
}

void init(void){
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glOrtho (-5, 5, -5, 5, -5, 5);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE); 
}

void reshape (int w, int h){
  glViewport (0, 0, (GLsizei) w, (GLsizei) h);
  largura=w; 
  altura=h;
}

void display(void){
  int i;

  glPushMatrix();
	gluLookAt(obsx,obsy,5,obsx,obsy, 0, 0, 1, 0);

  glRotatef ((GLfloat) eixoy, 0.0, 1.0, 0.0);
  glRotatef ((GLfloat) eixox, 1.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
 
  glScalef(10,10,10);

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, vertices);

  glColor3f (AZUL); 
  for (i = 0; i < nfaces; i++){
    glDrawElements(GL_POLYGON, 3, GL_UNSIGNED_INT, indices[i]);
  }
  
  glDisableClientState (GL_VERTEX_ARRAY);

  glPopMatrix();
  glutSwapBuffers();
}

void special(int key, int x, int y){
	switch(key){
		case GLUT_KEY_UP:
		obsy = obsy -1;
		break;
		case GLUT_KEY_DOWN:
		obsy = obsy +1;
		break;
		case GLUT_KEY_LEFT:
		obsx = obsx + 1;
		break;
		case GLUT_KEY_RIGHT:
		obsx = obsy - 1;
		break;
	}
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y){
  switch (key) {
  case 27:
    exit(0);
    break;
  case 'a':
    glutIdleFunc(idle);
    break;
  case 'A':
    glutIdleFunc(idle2);
    break;
  case 'y':
		eixoy = fmod(eixoy + 5,360.0);
    glutPostRedisplay();
    break;
  case 'Y':
		eixoy = fmod(eixoy - 5,360.0);
    glutPostRedisplay();
    break;
  case 'x':
    eixox = (eixox + 5) % 360;
    glutPostRedisplay();
    break;
  case 'X':
    eixox = (eixox - 5) % 360;
    glutPostRedisplay();
    break;
  case 'p':
    glLoadIdentity();
    gluPerspective(65.0, (GLfloat) largura/(GLfloat) altura, 1.0, 15.0);
    gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);
    glutPostRedisplay();
    break;
  case 'o':
    glLoadIdentity();
    glOrtho (-5, 5, -5, 5, -5, 5);
    glutPostRedisplay();
    break;
  case 's':
    glScalef(1.1,1.1,1.1);
    glutPostRedisplay();
    break;
  case 'S':
    glScalef(0.9, 0.9, 0.9);
    glutPostRedisplay();  	
    break;
  }
	printf("\n%d , %d",x,y);
}
