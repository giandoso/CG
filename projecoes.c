#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

void init(void);
void display(void);
void keyboard(unsigned char key, int x, int y);
void reshape (int w, int h);

#define AZUL     0.0, 0.0, 1.0
#define VERMELHO 1.0, 0.0, 0.0
#define AMARELO  1.0, 1.0, 0.0
#define VERDE    0.0, 1.0, 0.0
#define CYAN     1.0, 0.0, 1.0
#define LARANJA  0.8, 0.6, 0.1
#define ROSEO    0.7, 0.1, 0.6
#define CINZA    0.6, 0.6, 0.6

static GLfloat vertices[30]={
  0.0,  0.0, 0.0, /* 0 */
  30.0, 0.0, 0.0, /* 1 */
  0.0, 0.0, 30.0, /* 2 */
  30.0,  0.0, 30.0, /* 3 */
  0.0,   30.0, 0.0, /* 4 */
  30.0,  30.0,  0.0, /* 5 */
  0.0, 30.0,  30.0, /* 6 */
  30.0,  30.0,  30.0, /* 7 */
  15.0,   40.0,  30.0, /* 8 */
  15.0, 40.0, 0.0  /* 9 */
}; 

static GLubyte baseIndices[]    = {0,1,3,2};
static GLubyte dirIndices[]      = {5,7,3,1};
static GLubyte esqIndices[]  = {0,2,6,4};
static GLubyte fundoIndices[]   = {4,5,1,0};
static GLubyte frenteIndices[]      = {2,3,7,6};
static GLubyte telDirIndices[]     = {8,7,5,9};
static GLubyte telEsqIndices[] = {6,8,9,4};
static GLubyte telFrenteIndices[] = {6,7,8};
static GLubyte telTrasIndices[] = {5,4,9};
    
static int eixoy, eixox;
int largura, altura;

int main(int argc, char** argv){
  int i;
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize (256, 256); 
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
  glOrtho (-50, 50, -50, 50, -50 , 50);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE); 
}

void reshape (int w, int h){
  glViewport (0, 0, (GLsizei) w, (GLsizei) h);
  largura=w; 
  altura=h;
}

void display(void){
  glPushMatrix();
  glRotatef ((GLfloat) eixoy, 0.0, 1.0, 0.0);
  glRotatef ((GLfloat) eixox, 1.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, vertices);

  glColor3f (CYAN); /* Base */
  glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, baseIndices);

  glColor3f (LARANJA); /* Dir */
  glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, dirIndices);

  glColor3f (LARANJA); /* Esq */
  glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, esqIndices);

  glColor3f (LARANJA); /* Fundo */
  glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, fundoIndices);

  glColor3f (LARANJA); /* Frente */
  glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, frenteIndices);

  glColor3f (AZUL); /* telDir */
  glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, telDirIndices);

  glColor3f (AZUL); /* telEsq */
  glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, telEsqIndices);

  glColor3f (CYAN); /* telFrente */
  glDrawElements(GL_POLYGON, 3, GL_UNSIGNED_BYTE, telFrenteIndices);

  glColor3f (CYAN); /* telTras */
  glDrawElements(GL_POLYGON, 3, GL_UNSIGNED_BYTE, telTrasIndices);

  glDisableClientState (GL_VERTEX_ARRAY);

  glPopMatrix();
  glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y){
  switch (key) {
  case 27:
    exit(0);
    break;
  case 'a':
    printf("%d, %d\n",x,y);
    break;
  case 'y':
    eixoy = (eixoy + 5) % 360;
    glutPostRedisplay();
    break;
  case 'Y':
    eixoy = (eixoy - 5) % 360;
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
    gluPerspective(65.0, (GLfloat) largura/(GLfloat) altura, 20.0, 120.0);
    gluLookAt(0, 0, 90, 0, 0, 0, 0, 1, 0);
    glutPostRedisplay();
    break;
  case 'o':
    glLoadIdentity();
    glOrtho (-50, 50, -50, 50, -50 , 50);
    glutPostRedisplay();
    break;
  }
}
