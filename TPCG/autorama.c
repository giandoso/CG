#include<GL/glut.h>
#include<math.h>
#include<stdio.h>
#include<time.h>

#define c 3.14/180
#define PI  3.14
#define TWO_PI  2.0 * PI
#define RAD_TO_DEG  180.0 / PI

#define OBSTACULOS 10

void colisao();
void populaPista();
void conelaranja(float a,float b);
void rect(float p[],float q[],float r[],float s[]);
void cylinder(float r,float y);
void circle(float R);
void arbusto (float a,float b);
void estrelaP (float a,float b);
void faixa(float R1, float R2);
void actall(float R1,float R2);
void alloy(float R1,float R2);

//Pontos para modelar o carro
float p1[]={5.5,-2.5,1},q1[]={5.5,-7.5,1},r1[]={10.7,-7.5,1},s1[]={10.7,-2.5,1};
float p2[]={-15,-6.5,1},q2[]={-15,-3.5,1},r2[]={0.5,-2.5,1},s2[]={0.5,-7.5,1};
float p3[]={-13,-6.5,1},q3[]={-13,-6.5,2.5},r3[]={0.5,-7.5,3.5},s3[]={0.5,-7.5,1};
float p4[]={-13,-3.5,1},q4[]={-13,-3.5,2.5},r4[]={0.5,-2.5,3.5},s4[]={0.5,-2.5,1};
float p5[]={0.5,-1,1},q5[]={0.5,-1,3},r5[]={0.5,-2.5,3.5},s5[]={0.5,-2.5,1};
float p6[]={0.5,-7.5,1},q6[]={0.5,-7.5,3.5},r6[]={0.5,-9,3},s6[]={0.5,-9,1};
float p7[]={5.5,-1,1},q7[]={5.5,-1,3},r7[]={5.5,-2.5,3.5},s7[]={5.5,-2.5,1};
float p8[]={5.5,-7.5,1},q8[]={5.5,-7.5,3.5},r8[]={5.5,-9,3},s8[]={5.5,-9,1};
float p9[]={4,-2.5,3.5},q9[]={11,-2.5,3.5},r9[]={11,-7.5,3.5},s9[]={4,-7.5,3.5};

//pontos desecessarios
// float p1[]={10.7,-9,3},s1[]={12.7,-9,3},q1[]={10.7,-1,3},r1[]={12.7,-1,3};
// float p2[]={0.5,-1,1},s2[]={5.5,-1,1},q2[]={0.5,-9,1},r2[]={5.5,-9,1};
// float p6[]={5.5,-2.5,1},q6[]={5.5,-2.5,3.5},r6[]={10.7,-2.5,3.5},s6[]={10.7,-2.5,1};
// float p7[]={5.5,-7.5,1},q7[]={5.5,-7.5,3.5},r7[]={10.7,-7.5,3.5},s7[]={10.7,-7.5,1};
// float p8[]={5.5,-7.5,3.5},q8[]={10.7,-7.5,3.5},r8[]={10.7,-6,3.5},s8[]={5.5,-6,3.5};
// float p9[]={5.5,-2.5,3.5},q9[]={5.5,-4,3.5},r9[]={10.7,-4,3.5},s9[]={10.7,-2.5,3.5};
// float p10[]={5.5,-4,3.5},q10[]={10.7,-4,3.5},r10[]={10.7,-5,4.5},s10[]={5.5,-5,5.5};
// float p11[]={5.5,-6,3.5},q11[]={10.7,-6,3.5},r11[]={10.7,-5,4.5},s11[]={5.5,-5,5.5};
// float p12[]={10.7,-9,2},q12[]={10.7,-9,4},r12[]={12.7,-9,4},s12[]={12.7,-9,2};
// float p13[]={10.7,-1,2},q13[]={10.7,-1,4},r13[]={12.7,-1,4},s13[]={12.7,-1,2};
// float p14[]={0.5,-1,1},q14[]={0.5,-1,3},r14[]={5.5,-1,3},s14[]={5.5,-1,1};
// float p15[]={0.5,-9,1},q15[]={0.5,-9,3},r15[]={5.5,-9,3},s15[]={5.5,-9,1};
// float p20[]={10.7,-7.5,1},q20[]={10.7,-7.5,3.5},r20[]={10.7,-2.5,3.5},
// s20[]={10.7,-2.5,1};

enum
{	//Diferentes views
	HELICOPTER,FRONT,SIDE,BACK
} viewpoint = BACK;


int MID=565; //Distancia do carro na via do centro 
int start=0;
float auxImunidade=0;

char KEY; //Guardar tecla que usuario clicou

float angle;
float speed = 0.0;

float carx=0,cary=570; //Variavel localização do carro

int rot=0; //Rotacao roda

int showScore=0;
char scoreString[50];

int life=3;
int showLife=0;
char lifeString[3];

int imune;
int score=0;

int voltas=0;
int showIntroMessage=1;

int showGameOver = 0;

int disableKeyboard = 0;


//Criar cone
void cone(){
	float i,x,y,r=10;
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0,0,20);
	for(i=0;i<=361;i+=2)
	{
		x= r * cos(i*c);
		y= r * sin(i*c);
		glVertex3f(x,y,0);
	}
	glEnd();
}

void listracone(){
	float j,i,x,y,r=10;
	glColor3f(1,1,1);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0,0,20);
	for(i=100;i<=361;i+=50){
		for(j=0; j<30; j++){	
			x= r * cos(i*c);
			y= r * sin(i*c);
			glVertex3f(x,y,0);
		}
	}
	glEnd();
}

//Cone laranja pra obstaculo
void conelaranja(float a,float b){
	glColor3f(1, 0.35, 0);
	glPushMatrix();
		glTranslatef(a,b,0);
		glScalef(0.6, 0.4, 0.5);
		cone();
		listracone();
	glPopMatrix();
	glPushMatrix();
		listracone();
	glPopMatrix();

}
//Poste para obstaculo
void poste(float a,float b){
	//Corpo do poste
	glColor3f(0.5, 0.5, 1);
	glPushMatrix();
		glTranslatef(a,b,-1);
		glRotatef(90,1,0,0);
		cylinder(1.2, 20);
	glPopMatrix();

	//Cima do poste
	glColor3f(1, 0.9, 0);
	glPushMatrix();
		glTranslatef(a,b,15);
		glRotatef(90,1,0,0);
		cylinder(5, 10);
	glPopMatrix();
}
//Buraco para obstaculo
void buraco(float a, float b){
	glColor3f(0, 0, 0);
	glPushMatrix();
		glTranslatef(a,b,1);
		glRotatef(90,1,0,0);
		circle(6);
	glPopMatrix();
}
//Lata de lixo para obstaculo
void latalixo(float a, float b){
	glColor3f(0, 0, 0);
	glPushMatrix();
		glTranslatef(a,b, -1);
		glRotatef(90,1,0,0);
		cylinder(5, 10);
	glPopMatrix();
	glColor3f(1, 1, 1);
	glPushMatrix();
		glTranslatef(a,b, 9);
		glRotatef(90,1,0,0);
		circle(5);
	glPopMatrix();
}

//Desenhar a pista
void track(float R1,float R2){
	float X,Y,Z;
	int  y;
	glBegin(GL_QUAD_STRIP);
	for( y=0;y<=361;y+=1){
		X=R1*cos(c*y);
		Y=R1*sin(c*y);
		Z=-1;
		glVertex3f(X,Y,Z);

		X=R2*cos(c*y);
		Y=R2*sin(c*y);
		Z=-1;
		glVertex3f(X,Y,Z);
	}
	glEnd();
}
//Faixa de pista
void faixa(float R1,float R2){
	float X,Y,Z;
	int  y;
	glBegin(GL_QUAD_STRIP);
	for( y=0;y<=361;y+=1){
		X=R1*cos(c*y);
		Y=R1*sin(c*y);
		Z=-1;
		glVertex3f(X,Y,Z);

		X=R2*cos(c*y);
		Y=R2*sin(c*y);
		Z=-1;
		glVertex3f(X,Y,Z);
	}
	glEnd();
}
//Estrela no ceu
void estrela(float x, float y, float z){
	glColor3f(1,1,1);
	glPushMatrix();
		glTranslatef(x, y,z- 100);
		glutSolidSphere(5,3,3);
	glPopMatrix();;
}

//Criar um cilindro
void cylinder(float r,float y){
	float x, z; int d;
	glBegin(GL_QUAD_STRIP);
	for( d=0;d<=362;d+=1)
	{
		x=r*cos(c*d);
		z=r*sin(c*d);
		glVertex3f(x,0,z);
		glVertex3f(x,y,z);
	}
	glEnd();
}
//Criar arbusto para paisagem
void arbusto (float a,float b){
	glPushMatrix();		
	glColor3f(0.8, 0.45, 0.35);
	glPushMatrix();
		glTranslatef(a,b,1);
		glScalef(0.6, 0.4, 0.5);
		cone();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(a,b,1);
		glScalef(0.6, 0.4, 0.5);
		glRotatef(90,1,90,0);
		cone();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(a,b,1);
		glScalef(0.6, 0.4, 0.5);
		glRotatef(-90,1,90,0);
		cone();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(a,b,1);
		glScalef(0.6, 0.4, 0.5);
		glRotatef(45,1,90,0);
		cone();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(a,b,1);		
		glScalef(0.6, 0.4, 0.5);
		glRotatef(-45,1,90,0);
		cone();
	glPopMatrix();
	glPopMatrix();
}
//Cria estrela de ganhar ponto ("obstaculo")
void estrelaP (float a,float b){
	glPushMatrix();		
		glColor3f(1, 1, 0);
		glPushMatrix();
			glTranslatef(a,b,10);
			glScalef(0.6, 0.4, 0.5);
			cone();
		glPopMatrix();
		//braço
		glPushMatrix();
			glTranslatef(a,b,10);
			glScalef(0.6, 0.4, 0.5);
			glRotatef(45,1,90,0);
			cone();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(a,b,10);		
			glScalef(0.6, 0.4, 0.5);
			glRotatef(-45,1,90,0);
			cone();
		glPopMatrix();
		//pernas
		glPushMatrix();
			glTranslatef(a,b,10);
			glScalef(0.6, 0.4, 0.5);
			glRotatef(45,1,90,0);
			cone();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(a,b,10);
			glScalef(0.6, 0.4, 0.5);
			glRotatef(-45,1,90,0);
			cone();
		glPopMatrix();
	glPopMatrix();
}

//Cria uma arvore com 3 esferas
void tree2(float a,float b)
{
	//Tronco
	glColor3f(1,0.2,0);
	glPushMatrix();
		glTranslatef(a,b,-1);
		glRotatef(90,1,0,0);
		cylinder(6,25);
	glPopMatrix();

	//Folhas
	glColor3f(0.8, 0.65, 0.55);
	glPushMatrix();
		glTranslatef(a,b,25);
		glutSolidSphere(15,10,10);		
	glPopMatrix();
	glPushMatrix();
		glTranslatef(a,b,35);
		glutSolidSphere(13,10,10);
	glPopMatrix();
		glPushMatrix();
		glTranslatef(a,b,45);
		glutSolidSphere(11,5,5);
	glPopMatrix();
}

//lado pneu
void alloy(float R1,float R2)
{
	float X,Y,Z;int y;
	glColor3f(1,1,1);
	glBegin(GL_QUAD_STRIP);
	for(y=0;y<=361;y+=1)
	{
		X=R1*cos(c*y);
		Z=R1*sin(c*y);
		Y=0;
		glVertex3f(X,Y,Z);

		X=R2*cos(c*y);
		Z=R2*sin(c*y);
		Y=0;
		glVertex3f(X,Y,Z);

	}
	glEnd();
}

//Desenhar as raias do pneu
void actall(float R1,float R2)
{
	float X,Y,Z; int i;
	glBegin(GL_QUADS);
	for(i=0;i<=361;i+=120)
	{
		glColor3f(0,1,1);
		X=R1*cos(c*i);
		Y=0;
		Z=R1*sin(c*i);
		glVertex3f(X,Y,Z);

		X=R1*cos(c*(i+30));
		Y=0;
		Z=R1*sin(c*(i+30));
		glVertex3f(X,Y,Z);

		X=R2*cos(c*(i+30));
		Y=0;
		Z=R2*sin(c*(i+30));
		glVertex3f(X,Y,Z);

		X=R2*cos(c*i);
		Y=0;
		Z=R2*sin(c*i);
		glVertex3f(X,Y,Z);
	}
	glEnd();
}

//Cria um cícurlo
void circle(float R)
{
	float X,Y,Z;int i;

	glBegin(GL_POLYGON);
	for(i=0;i<=360;i++)
	{
		X=R*cos(c*i);
		Z=R*sin(c*i);
		Y=0;
		glVertex3f(X,Y,Z);
	}
	glEnd();
}

//Desenha um retangulo
void rect(float p[],float q[],float r[],float s[])
{
	glBegin(GL_POLYGON);
		glVertex3fv(p);
		glVertex3fv(q);
		glVertex3fv(r);
		glVertex3fv(s);
	glEnd();
  }

//Gerar o motorista
void driver()
{
	glColor3f(0.5,0.2,0.8);
	//ombro - direito
	glPushMatrix();
		glTranslatef(3.5,-3.6,3);
		glutSolidSphere(0.8,5,5);
	glPopMatrix();
	//esquerdo
	glPushMatrix();
		glTranslatef(3.5,-6.4,3);
		glutSolidSphere(0.8,5,5);
	glPopMatrix();
	//maos - direita
	glPushMatrix();
		glTranslatef(3,-3.5,2.5);
		glRotatef(90,0,0,1);
		cylinder(0.4,3);
	glPopMatrix();
	//esquerda
	glPushMatrix();
		glTranslatef(3,-6.5,2.5);
		glRotatef(90,0,0,1);
		cylinder(0.4,3);
	glPopMatrix();

	//Cabeça
	glPushMatrix();
		glTranslatef(3,-5,4);
		glutSolidSphere (1.0, 20, 16);
	glPopMatrix();


	//Corpo
	glPushMatrix();
		glTranslatef(3,-5,1);
		glRotatef(90,1,0,0);
		cylinder(1,2);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(3,-5,3);
		glRotatef(90,1,0,0);
		circle(1);
	glPopMatrix();

	//volante
	glPushMatrix();
		glColor3f(0.1,0.0,0.0);
		glTranslatef(2.3,-5,4);
		glRotatef(90, 180, 90, 0);
		circle(1.2);
	glPopMatrix();
}

//Gerar a cena (rua, ceu, chao, paisagem)
void scenery()
{
	float x,y; int p;
	//ceu
	glColor3f(0.21, 0.18, 0.12);
	glPushMatrix();
		glRotatef(90,1,0,0);
		cylinder(1000,1000);
	glPopMatrix();

	//Ground
	glColor3f(0.41,0.28,0.22);
	glPushMatrix();
		glTranslatef(0,0,-1.1);
		glRotatef(90,1,0,0);
		circle(1100);
	glPopMatrix();

	//Track
	glColor3f(0.25,0.15,0.1);
	track(610,510);

	populaPista();
	colisao();

	glPushMatrix();
		glTranslatef(0,0,1);
		glColor3f(1, 1, 1);
		faixa(519, 521);
		faixa(544, 546);
		faixa(569, 571);
		faixa(594, 596);
	glPopMatrix();


	//ceu
	for(p=0;p<=360;p+=5)
	{
		x=(1000+rand()%50)*cos(c*p);
		y=(1000+rand()%50)*sin(c*p);
		estrela(x,y,rand()%500);
	}

	//arvores lado esquerdo
	for(p=0;p<=360;p+=60)
	{

		x=650*cos(c*p);
		y=650*sin(c*p);
		tree2(x,y);
	}
	for(p=0;p<=360;p+=120)
	{

		x=710*cos(c*p);
		y=710*sin(c*p);
		tree2(x,y);
	}

	// arbusto lado direito
	for(p=0;p<=360;p+=120)
	{
		x=420*cos(c*p);
		y=420*sin(c*p);
		arbusto(x,y);
	}

		for(p=0;p<=360;p+=40)
	{
		x=460*cos(c*p);
		y=460*sin(c*p);
		arbusto(x,y);
	}

}

// //Desenha triangulos, mas não usamos
// void tri(float a[],float b[],float z[])
// {
// 	glBegin(GL_TRIANGLES);
// 		glVertex3fv(a);
// 		glVertex3fv(b);
// 		glVertex3fv(z);
// 	glEnd();
// }

//Junta os pneus, engrenagem, raias
void wheels()
{
	//engrenagem (cilindo que liga as rodas)
	glColor3f(0.5,0.5,0.5);
	cylinder(0.5,9);

	//Pneus <
	glColor3f(0,0,0);
	cylinder(2,2);
	alloy(2,1.4);
	actall(1.4,0.8);
	glColor3f(1,1,1);
	circle(0.8);

	glPushMatrix();
		glTranslatef(0,2,0);
		alloy(2,1.4);
		actall(1.4,0.8);
		glColor3f(0,1,1);
		circle(0.8);
	glPopMatrix();

	//Pneus >
	glPushMatrix();
		glTranslatef(0,8,0);
		glColor3f(0,0,0);
		cylinder(2,2);
		alloy(2,1.4);
		actall(1.4,0.8);
		glColor3f(0,1,1);
		circle(0.8);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0,10,0);
		actall(1.4,0.8);
		alloy(2,1.4);
		glColor3f(0,1,1);
		circle(0.8);
	glPopMatrix();

}

//Gerar o chassis do carro
void chassis()
{

	//nao alterou em nada
	// //Parameters For glMaterialfv() function
	// GLfloat specular[] = { 0.7, 0.7, 0.7, 1.0 };
	// GLfloat ambient[]={1,1,1,1},diffuse[]={0.7,0.7,0.7,1};
	// GLfloat full_shininess[]={100.0};
	// Material Properties
	// glMaterialfv(GL_FRONT,GL_AMBIENT,ambient);
	// glMaterialfv(GL_FRONT,GL_SPECULAR,specular);
	// glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse);
	// glMaterialfv(GL_FRONT,GL_SHININESS, full_shininess);

	glColor3f(0.72,0.1,0);
	//modelando carro
	rect(p1,q1,r1,s1); //baixo atras
	rect(r2,s2,r1,s1);  //retangulo assento
	rect(p2,q2,r2,s2); //retangulo embaixo
	rect(p3,q3,r3,s3); //retangulo <
	rect(p4,q4,r4,s4); //retangulo >
	rect(q4,q3,r3,r4); //retangulo cima
	rect(r5,s2,r4,r2); 	 //painel
	rect(p9,q9,r9,s9); //costa
	rect(p6, q8, q6, p8);//porta esquerda
	rect(s5, r7, r5, s7); //porta direita
}

//Gerar carro
void car()
{
	glPushMatrix();
		glRotatef(180,0,0,1);

		chassis();

		glPushMatrix();
			glTranslatef(8,-10,1);
			glRotatef(rot,0,1,0);
			wheels();
		glPopMatrix();


		glPushMatrix();
			glTranslatef(-12,-10,1);
			glRotatef(rot,0,1,0);
			wheels();
		glPopMatrix();

		driver();

		rot+=90;
		if(rot>360) rot-=360;

	glPopMatrix();
}

/*
Criar estrutura de dados 'obstaculo'
criar função que popula a pista com obstaculos
criar funcao que compara posição atual do carro c obstaculo
caso verdade carro 'bateu'
encerrar jogo
caso falso carro desviou
muda a posição do obstaculo que acabou de ser desviado
*/

typedef struct Obstaculo_{
	float obsX, obsY;
	int modelo;
}Obstaculo;

typedef struct ObstaculoHard_{
	float obsX, obsY;
	int modelo;
}ObstaculoHard;

Obstaculo obs[OBSTACULOS];
ObstaculoHard obsH[OBSTACULOS];


void iniciaObstaculos(){
	int aleatorio;
	srand(time(NULL));
	int i;
	printf("  Id    X    Y    M\n");
	for(i=0;i<10;i++){
		aleatorio = rand() %10;
		if(aleatorio > 4){
			aleatorio = rand()%10;
			if(aleatorio > 4){
				//515
				obs[i].obsX = 515*cos(c*(36*i));
				obs[i].obsY = 515*sin(c*(36*i));
				//randomizar opção de modelo
				obs[i].modelo = rand() %3;
				printf("%4d %4f %4f %4d\n", i, obs[i].obsX, obs[i].obsY, obs[i].modelo );
			}else{
				//540
				obs[i].obsX = 540*cos(c*(36*i));
				obs[i].obsY = 540*sin(c*(36*i));
				//randomizar opção de modelo
				obs[i].modelo = rand() %3;
				printf("%4d %4f %4f %4d\n", i, obs[i].obsX, obs[i].obsY, obs[i].modelo );
			}
		}else{
			aleatorio = rand()%10;
			if(aleatorio > 4){
				//565
				obs[i].obsX = 565*cos(c*(36*i));
				obs[i].obsY = 565*sin(c*(36*i));
				//randomizar opção de modelo
				obs[i].modelo = rand() %3;
				printf("%4d %4f %4f %4d\n", i, obs[i].obsX, obs[i].obsY, obs[i].modelo );
			}else{
				//590
				obs[i].obsX = 590*cos(c*(36*i));
				obs[i].obsY = 590*sin(c*(36*i));
				//randomizar opção de modelo
				obs[i].modelo = rand() %3;
				printf("%4d %4f %4f %4d\n", i, obs[i].obsX, obs[i].obsY, obs[i].modelo );
			}
		}
	}
}

void populaPista(){
	int i;
	float x,y;
	for(i=0;i<10;i++){
			x=obs[i].obsX;
			y=obs[i].obsY;
			printf("obj:%f %f\n", obsH[i].obsX,obsH[i].obsY);

			switch(obs[i].modelo){
				case 0:
					conelaranja(x,y);
				break;
				case 1:
					buraco(x,y);
				break;
				case 2:
					buraco(x,y);
				break;
			}
			if(score>1100){
				float xH,yH;

				xH=obsH[i].obsX;
				yH=obsH[i].obsY;
				switch(obsH[i].modelo){





					case 0:
						conelaranja(xH,yH);
					break;
					case 1:
						poste(xH,yH);
					break;
					case 2:
						latalixo(xH,yH);
					break;
				}
			}
	}
}

//Teclas para jogar
void keys(unsigned char key,int x,int y)
{
	if(disableKeyboard == 0){
		KEY=key;
		if(key=='W' || key=='w')
		{
			if(speed < 0.03){
				speed += 0.005;
				start = 1;
				showIntroMessage = 0;
				showLife = 1;
				showScore = 1;
			}
		}
		if(key=='S' || key=='s')
		{
			if(speed > 0.01){
				speed -= 0.01;
			}else{
				speed = 0.01;
			}
		}
		if(key=='A' || key=='a')
		{
			if(MID<590){
				MID += 25;
			}
		}

		if(key=='D' || key=='d')
		{
			if(MID>515){
				MID -= 25;
			}
		}

		if(key=='E' || key=='e')
		{
			start=0;
		}

		if(key=='G' || key=='g')
		{
			start=1;
		}
		if(key == 27){
			system("pkill ffplay");
			exit(1);
		}
	}
	if(key == 27){
		system("pkill ffplay");
		exit(1);
	}
}

//Função de camera
void view()
{
	float pos[]={1000,1000,2000,1};//Posição da fonte de luz
	// switch(viewpoint)
	// {

	// 		// case HELICOPTER:

	// 		// glLightfv(GL_LIGHT0, GL_POSITION, pos);
	// 		// gluLookAt(200,0,700,0,0,0,0,0,1);
	// 		// scenery();
	// 		// glPushMatrix();
	// 		// 	glTranslatef(carx,cary,0);
	// 		// 	glRotatef(angle*RAD_TO_DEG,0,0,-1);
	// 		// 	car();
	// 		// glPopMatrix();

	// 		// break;


	// 		// case SIDE:
 //      //
	// 		// gluLookAt(-20.0,-20.0,15,0.0,0.0,2.0,0.0, 0.0,1.0);
	// 		// car();
	// 		// glPushMatrix();
	// 		// 	glRotatef(angle*RAD_TO_DEG, 0.0,0.0,1.0);
	// 		// 	glTranslatef(-carx,-cary,0);
	// 		// 	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	// 		// 	();
	// 		// glPopMatrix();
 //      //
	// 		// break;

	// 		// case FRONT:

	// 		// gluLookAt(15.0,5.0,20,0.0,0.0,4.0,0.0,0.0,1.0);
	// 		// car();
	// 		// glPushMatrix();
	// 		// 	glRotatef(angle*RAD_TO_DEG, 0.0,0.0,1.0);
	// 		// 	glTranslatef(-carx,-cary,0);
	// 		// 	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	// 		// 	scenery();
	// 		// glPopMatrix();

	// 		// break;

	// 		case BACK:

			gluLookAt(-12.0,6.0,13,15.0,6.0,2.0,0.0,0.0,1.0);
			car();
			glPushMatrix();
				glRotatef(RAD_TO_DEG * angle, 0.0, 0.0, 1.0);

				glTranslatef(-carx,-cary,0);
				glLightfv(GL_LIGHT0, GL_POSITION, pos);
				scenery();

			glPopMatrix();

	// 		break;

	// }

}

//Idle Callback
void idle()
{

	if(start==1)
	{
		angle+= 0 + speed;
		if(angle==TWO_PI)
		{
			angle-=TWO_PI;
		}

		colisao();
		carx=MID*sin(angle);
		cary=MID*cos(angle);
		viewpoint=BACK;
		// switch(KEY)
		// {
		// case 'H':
		// case 'h':viewpoint=HELICOPTER;break;

		// // case 'S':
		// // case 's':viewpoint=SIDE;break;

		// case 'F':
		// case 'f':viewpoint=FRONT;break;

		// case 'B':
		// case 'b':viewpoint=BACK;break;


		// }
		glutPostRedisplay();
	}
}


void init()
{
	GLfloat amb[]={1,1,1,1},diff[]={1,1,1,1},spec[]={1,1,1,1};

	glLoadIdentity();

	glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
	glLightfv(GL_LIGHT0, GL_SPECULAR, spec);

	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE);

	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

	glClearColor(1,1,1,1);

}

void insereString(void *font, char *string)
{
	// Exibe caractere a caractere
	while(*string)
		glutStrokeCharacter(GLUT_STROKE_ROMAN,*string++);
}


void atualizaScore(){
	score+=10;
	snprintf(scoreString, 50,"Score: %d", score);
}

void atualizaLife(){
	switch(life){
		case 1:
			snprintf(lifeString, 30,"@");
		break;
		case 2:
			snprintf(lifeString, 30,"@@");
		break;
		case 3:
			snprintf(lifeString, 30,"@@@");
		break;
	}
}

void displayScore(){
	if(showScore == 1){
		// Posiciona o texto stroke usando transformações geométricas
		glPushMatrix();
		glColor3f(1.0,0.0,0.0);
		glTranslatef(10.0,25.0,22.0);
		glScalef(0.02, 0.02, 0.015); // diminui o tamanho do fonte
		glRotatef(90.0, 1.0,0.0,0.0); // rotaciona o texto
		// glRotatef(-5.0, 0.0,1.0,0.0); // rotaciona o texto
		glRotatef(-90.0, 0.0,1.0,0.0); // rotaciona o texto

		glLineWidth(2); // define a espessura da linha
		atualizaScore();
		insereString(GLUT_STROKE_ROMAN, scoreString);
		glPopMatrix();
	}
}

void displayLife(){
	if(showLife == 1){
		glPushMatrix();
		glColor3f(1.0,0.0,0.0);
		glTranslatef(10.0,-5.0,22.0);
		glScalef(0.02, 0.03, 0.015); // diminui o tamanho do fonte
		glRotatef(90.0, 1.0,0.0,0.0); // rotaciona o texto
		// glRotatef(-5.0, 0.0,1.0,0.0); // rotaciona o texto
		glRotatef(-90.0, 0.0,1.0,0.0); // rotaciona o texto

		glLineWidth(2); // define a espessura da linha
		atualizaLife();
		insereString(GLUT_STROKE_ROMAN, lifeString);
		glPopMatrix();

	}
}

void displayIntroMessage(){
	if(showIntroMessage == 1){
		glPushMatrix();
		glColor3f(1.0,0.0,0.0);
		glTranslatef(16.0,27.0,20.0);
		glScalef(0.04, 0.04, 0.035); // diminui o tamanho do fonte
		glRotatef(90.0, 1.0,0.0,0.0); // rotaciona o texto
		// glRotatef(-5.0, 0.0,1.0,0.0); // rotaciona o texto
		glRotatef(-90.0, 0.0,1.0,0.0); // rotaciona o texto

		glLineWidth(2); // define a espessura da linha
		atualizaLife();
		insereString(GLUT_STROKE_ROMAN, "Press 'W' to start\n");
		glPopMatrix();

		glPushMatrix();
		glColor3f(1.0,0.0,0.0);
		glTranslatef(16.0,32.0,14.0);
		glScalef(0.035, 0.035, 0.035); // diminui o tamanho do fonte
		glRotatef(90.0, 1.0,0.0,0.0); // rotaciona o texto
		// glRotatef(-5.0, 0.0,1.0,0.0); // rotaciona o texto
		glRotatef(-90.0, 0.0,1.0,0.0); // rotaciona o texto

		glLineWidth(2); // define a espessura da linha
		atualizaLife();
		insereString(GLUT_STROKE_ROMAN, "Use W/A/S/D to move\n");
		glPopMatrix();
	}
}

void displayGameOver(){
	if(showGameOver == 1){
		glPushMatrix();
		glColor3f(1.0,0.0,0.0);
		glTranslatef(16.0,29.0,18.0);
		glScalef(0.06, 0.06, 0.050); // diminui o tamanho do fonte
		glRotatef(90.0, 1.0,0.0,0.0); // rotaciona o texto
		// glRotatef(-5.0, 0.0,1.0,0.0); // rotaciona o texto
		glRotatef(-90.0, 0.0,1.0,0.0); // rotaciona o texto

		glLineWidth(2); // define a espessura da linha
		atualizaLife();
		insereString(GLUT_STROKE_ROMAN, "GAME OVER");
		glPopMatrix();

		glPushMatrix();
		glColor3f(1.0,0.0,0.0);
		glTranslatef(16.0,20.0,13.5);
		glScalef(0.035, 0.035, 0.035); // diminui o tamanho do fonte
		glRotatef(90.0, 1.0,0.0,0.0); // rotaciona o texto
		// glRotatef(-5.0, 0.0,1.0,0.0); // rotaciona o texto
		glRotatef(-90.0, 0.0,1.0,0.0); // rotaciona o texto

		glLineWidth(2); // define a espessura da linha
		atualizaLife();
		insereString(GLUT_STROKE_ROMAN, scoreString);
		glPopMatrix();

		glPushMatrix();
		glColor3f(1.0,0.0,0.0);
		glTranslatef(16.0,20.0,24.0);
		glScalef(0.025, 0.025, 0.025); // diminui o tamanho do fonte
		glRotatef(90.0, 1.0,0.0,0.0); // rotaciona o texto
		// glRotatef(-5.0, 0.0,1.0,0.0); // rotaciona o texto
		glRotatef(-90.0, 0.0,1.0,0.0); // rotaciona o texto

		glLineWidth(2); // define a espessura da linha
		atualizaLife();
		insereString(GLUT_STROKE_ROMAN, "Press 'Esc' to exit.");
		glPopMatrix();

	}
}


void negaImune(){
	if(angle>auxImunidade+0.5){
		imune=0;
	}
}

void colisao(){
	int i;
	for (i = 0; i < 10; i++) {
		if(carx < obs[i].obsX + 5.0 && carx > obs[i].obsX - 5.0 && cary < obs[i].obsY + 5.0 && cary > obs[i].obsY - 5.0){
			printf("carx: %f, cary: %f\n", carx, cary);
			printf("obsX: %f, obsY: %f i: %d\n\n\n ", obs[i].obsX, obs[i].obsY, i);
			if(imune == 0){
				life--;
				imune=1;
				auxImunidade=angle;
				if(life==0){
					showLife = 0;
					showScore = 0;
					showGameOver = 1;
					start=0;
					disableKeyboard = 1;
				}
			}
		}
		if(carx < obsH[i].obsX + 5.0 && carx > obsH[i].obsX - 5.0 && cary < obsH[i].obsY + 5.0 && cary > obsH[i].obsY - 5.0){
			printf("carx: %f, cary: %f\n", carx, cary);
			printf("obsX: %f, obsY: %f i: %d\n\n\n ", obsH[i].obsX, obsH[i].obsY, i);
			if(imune == 0){
				life--;
				imune=1;
				auxImunidade=angle;
				if(life==0){
					showLife = 0;
					showScore = 0;
					showGameOver = 1;
					start=0;
					disableKeyboard = 1;
				}
			}
		}
	}
}

void randomizaPista(){
	if(angle > 6.3 && angle < 6.4){
		angle = 0.0; //volta completa
		voltas++;
		int aleatorio;
		srand(time(NULL));
		int i;
		for(i=5;i<10;i++){
			aleatorio = rand() %10;
			if(aleatorio > 4){
				aleatorio = rand()%10;
				if(aleatorio > 4){
					//515
					obs[i].obsX = 515*cos(c*(36*i));
					obs[i].obsY = 515*sin(c*(36*i));
					//randomizar opção de modelo
					obs[i].modelo = rand() %3;
					if(score>1000){
						aleatorio = rand()%9;
						if(aleatorio<3){
							obsH[i].obsX = 540*cos(c*(36*i));
							obsH[i].obsY = 540*sin(c*(36*i));
							obsH[i].modelo = rand() %3;
						}if(aleatorio<6){
							obsH[i].obsX = 565*cos(c*(36*i));
							obsH[i].obsY = 565*sin(c*(36*i));
							obsH[i].modelo = rand() %3;
						}else{
							obsH[i].obsX = 590*cos(c*(36*i));
							obsH[i].obsY = 590*sin(c*(36*i));
							obsH[i].modelo = rand() %3;
						}
					}
				}else{
					//540
					obs[i].obsX = 540*cos(c*(36*i));
					obs[i].obsY = 540*sin(c*(36*i));
					//randomizar opção de modelo
					obs[i].modelo = rand() %3;
					if(score>1000){
						aleatorio = rand()%9;
						if(aleatorio<3){
							obsH[i].obsX = 515*cos(c*(36*i));
							obsH[i].obsY = 515*sin(c*(36*i));
							//randomizar opção de modelo
							obsH[i].modelo = rand() %3;
						}if(aleatorio<6){
							obsH[i].obsX = 565*cos(c*(36*i));
							obsH[i].obsY = 565*sin(c*(36*i));
							//randomizar opção de modelo
							obsH[i].modelo = rand() %3;
						}else{
							obsH[i].obsX = 590*cos(c*(36*i));
							obsH[i].obsY = 590*sin(c*(36*i));
							//randomizar opção de modelo
							obsH[i].modelo = rand() %3;
						}
					}
				}
			}else{
				aleatorio = rand()%10;
				if(aleatorio > 4){
					//565
					obs[i].obsX = 565*cos(c*(36*i));
					obs[i].obsY = 565*sin(c*(36*i));
					//randomizar opção de modelo
					obs[i].modelo = rand() %3;
					if(score>1000){
						aleatorio = rand()%9;
						if(aleatorio<3){
							obsH[i].obsX = 540*cos(c*(36*i));
							obsH[i].obsY = 540*sin(c*(36*i));
							//randomizar opção de modelo
							obsH[i].modelo = rand() %3;
						}if(aleatorio<6){
							obsH[i].obsX = 515*cos(c*(36*i));
							obsH[i].obsY = 515*sin(c*(36*i));
							//randomizar opção de modelo
							obsH[i].modelo = rand() %3;
						}else{
							obsH[i].obsX = 590*cos(c*(36*i));
							obsH[i].obsY = 590*sin(c*(36*i));
							//randomizar opção de modelo
							obsH[i].modelo = rand() %3;
						}
				}else{
					//590
					obs[i].obsX = 590*cos(c*(36*i));
					obs[i].obsY = 590*sin(c*(36*i));
					//randomizar opção de modelo
					obs[i].modelo = rand() %3;
					if(score>1000){
						aleatorio = rand()%9;
						if(aleatorio<3){
							obsH[i].obsX = 540*cos(c*(36*i));
							obsH[i].obsY = 540*sin(c*(36*i));
							//randomizar opção de modelo
							obsH[i].modelo = rand() %3;
						}if(aleatorio<6){
							obsH[i].obsX = 565*cos(c*(36*i));
							obsH[i].obsY = 565*sin(c*(36*i));
							//randomizar opção de modelo
							obsH[i].modelo = rand() %3;
						}else{
							obsH[i].obsX = 515*cos(c*(36*i));
							obsH[i].obsY = 515*sin(c*(36*i));
							//randomizar opção de modelo
							obsH[i].modelo = rand() %3;
						}
				}
			}
		}
	}
	if(angle > 3.0 && angle < 3.1){
		voltas++;
		int aleatorio;
		srand(time(NULL));
		int i;
		for(i=0;i<5;i++){
			aleatorio = rand() %10;
			if(aleatorio > 4){
				aleatorio = rand()%10;
				if(aleatorio > 4){
					//515
					obs[i].obsX = 515*cos(c*(36*i));
					obs[i].obsY = 515*sin(c*(36*i));
					//randomizar opção de modelo
					obs[i].modelo = rand() %3;
					if(score>1000){
						aleatorio = rand()%9;
						if(aleatorio<3){
							obsH[i].obsX = 540*cos(c*(36*i));
							obsH[i].obsY = 540*sin(c*(36*i));
							obsH[i].modelo = rand() %3;
						}if(aleatorio<6){
							obsH[i].obsX = 565*cos(c*(36*i));
							obsH[i].obsY = 565*sin(c*(36*i));
							obsH[i].modelo = rand() %3;
						}else{
							obsH[i].obsX = 590*cos(c*(36*i));
							obsH[i].obsY = 590*sin(c*(36*i));
							obsH[i].modelo = rand() %3;
						}
					}
				}else{
					//540
					obs[i].obsX = 540*cos(c*(36*i));
					obs[i].obsY = 540*sin(c*(36*i));
					obs[i].modelo = rand() %3;
					if(score>1000){
						aleatorio = rand()%9;
						if(aleatorio<3){
							obsH[i].obsX = 515*cos(c*(36*i));
							obsH[i].obsY = 515*sin(c*(36*i));
							//randomizar opção de modelo
							obsH[i].modelo = rand() %3;
						}else if(aleatorio<6){
							obsH[i].obsX = 565*cos(c*(36*i));
							obsH[i].obsY = 565*sin(c*(36*i));
							//randomizar opção de modelo
							obsH[i].modelo = rand() %3;
						}else{
							obsH[i].obsX = 590*cos(c*(36*i));
							obsH[i].obsY = 590*sin(c*(36*i));
							//randomizar opção de modelo
							obsH[i].modelo = rand() %3;
						}
					}
				}
			}else{
				aleatorio = rand()%10;
				if(aleatorio > 4){
					//565
					obs[i].obsX = 565*cos(c*(36*i));
					obs[i].obsY = 565*sin(c*(36*i));
					obs[i].modelo = rand() %3;
					if(score>1000){
						aleatorio = rand()%9;
						if(aleatorio<3){
							obsH[i].obsX = 540*cos(c*(36*i));
							obsH[i].obsY = 540*sin(c*(36*i));
							obsH[i].modelo = rand() %3;
						}else if(aleatorio<6){
							obsH[i].obsX = 515*cos(c*(36*i));
							obsH[i].obsY = 515*sin(c*(36*i));
							obsH[i].modelo = rand() %3;
						}else{
							obsH[i].obsX = 590*cos(c*(36*i));
							obsH[i].obsY = 590*sin(c*(36*i));
							//randomizar opção de modelo
							obsH[i].modelo = rand() %3;
						}
					}else{
					//590
					obs[i].obsX = 590*cos(c*(36*i));
					obs[i].obsY = 590*sin(c*(36*i));
					obs[i].modelo = rand() %3;
					if(score>1000){
						aleatorio = rand()%9;
						if(aleatorio<3){
							obsH[i].obsX = 540*cos(c*(36*i));
							obsH[i].obsY = 540*sin(c*(36*i));
							obsH[i].modelo = rand() %3;
						}if(aleatorio<6){
							obsH[i].obsX = 565*cos(c*(36*i));
							obsH[i].obsY = 565*sin(c*(36*i));
							obsH[i].modelo = rand() %3;
						}else{
							obsH[i].obsX = 515*cos(c*(36*i));
							obsH[i].obsY = 515*sin(c*(36*i));
							obsH[i].modelo = rand() %3;
						}
					}
				}
				}
			}
		}
	}
	}
}
}

//Display Callback Function
void display(){
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	view();
	colisao();
	randomizaPista();
	displayScore();
	displayLife();
	displayIntroMessage();
	displayGameOver();
	negaImune();
	glutSwapBuffers();
}

//Reshape
void reshape(int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(100, (GLfloat) w/(GLfloat) h, 1, 2000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


//Main
void main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);

	glutInitWindowPosition(500,500);
	glutInitWindowSize(500,500);
	glutCreateWindow("Computer Graphics");
	iniciaObstaculos();
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutKeyboardFunc(keys);
	glutReshapeFunc(reshape);
	system("ffplay -nodisp song.wav &");
	init();
	glutMainLoop();
}
