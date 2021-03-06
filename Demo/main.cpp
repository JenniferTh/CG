#define GLFW_DLL
#include <c:/MinGW/include/GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <iostream>

#include "vec3.hpp"

#include <iostream>
using namespace std;
static double xpos, ypos; //Maus Position
//static double alpha_ = 0;
static double window_width_ = 1024;
static double window_height_ = 768;
double winkelDeckel = 0;
//Rotation
double w1RSpeed = 4;
static double alpha_1 = 0;
static double alpha_2 = 0;
//Translation W�rfel
double w1TX = 0;
double w1TY = 0;
double w1TZ = 0;
double length = 2;
//Translation Kugel
double s1TX = 5;
double s1TY = 0;
double s1TZ = 0;
double radius = .5;
//Skalierung
double w1SX = 1;
double w1SY = 1;
double w1SZ = 1;

// draw a sphere composed of triangles
void DrawSphere(const Vec3& ctr, double r){
  int     i, j,
          n1 = 6, n2 = 12;
  Vec3    normal, v1;
  double  a1, a1d = M_PI / n1,
          a2, a2d = M_PI / n2,
          s1, s2,
          c1, c2;

  glShadeModel(GL_SMOOTH);
  for(i = 0; i < n1; i++){
    a1 = i * a1d;

    glBegin(GL_TRIANGLE_STRIP);
    for(j = 0; j <= n2; j++){
      a2 = (j + .5 * (i % 2)) * 2 * a2d;

      s1 = sin(a1);
      c1 = cos(a1);
      s2 = sin(a2);
      c2 = cos(a2);
      normal = c1 * XVec3 + s1 * (c2 * YVec3 + s2 * ZVec3);
      v1 = ctr + r * normal;
      glNormal3dv(normal.p);
      glVertex3dv(v1.p);

      s1 = sin(a1 + a1d);
      c1 = cos(a1 + a1d);
      s2 = sin(a2 + a2d);
      c2 = cos(a2 + a2d);
      normal = c1 * XVec3 + s1 * (c2 * YVec3 + s2 * ZVec3);
      v1 = ctr + r * normal;
      glNormal3dv(normal.p);
      glVertex3dv(v1.p);
    }
    glEnd();
  }
}

bool kollision(){
	bool kol = false;

	return kol;
}

void SetMaterialColor(int side, double r, double g, double b) {
  float	amb[4], dif[4], spe[4];
  int mat;

  dif[0] = r;
  dif[1] = g;
  dif[2] = b;

  for(int i = 0; i < 3; i++) {
    amb[i] = .1 * dif[i];
    spe[i] = .5;
  }
  amb[3] = dif[3] = spe[3] = 1.0;

  switch(side){
    case 1:	mat = GL_FRONT;
      break;
    case 2:	mat = GL_BACK;
      break;
    default: mat = GL_FRONT_AND_BACK;
  }

  glMaterialfv(mat, GL_AMBIENT, amb);
  glMaterialfv(mat, GL_DIFFUSE, dif);
  glMaterialfv(mat, GL_SPECULAR, spe);
  glMaterialf( mat, GL_SHININESS, 20);
}
// set viewport transformations and draw objects
void InitLighting() {
  GLfloat lp1[4]  = { 10,  5,  10,  0};
  GLfloat lp2[4]  = { -5,  5, -10,  0};
  GLfloat red[4]  = {1.0, .8,  .8,  1};
  GLfloat blue[4] = { .8, .8, 1.0,  1};

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glClearColor(1, 1, 1, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glShadeModel(GL_SMOOTH);
  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);
  glEnable(GL_LIGHTING);

  glLightfv(GL_LIGHT1, GL_POSITION, lp1);
  glLightfv(GL_LIGHT1, GL_DIFFUSE,  red);
  glLightfv(GL_LIGHT1, GL_SPECULAR, red);
  glEnable(GL_LIGHT1);

  glLightfv(GL_LIGHT2, GL_POSITION, lp2);
  glLightfv(GL_LIGHT2, GL_DIFFUSE,  blue);
  glLightfv(GL_LIGHT2, GL_SPECULAR, blue);
  glEnable(GL_LIGHT2);

  glClearColor(1, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // init viewport to canvassize
  glViewport(0, 0, window_width_, window_height_);

  // init coordinate system
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-15, 15, -10, 10, -20, 20);


  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}
// draw the entire scene
void drawSquare( Vec3 seite1, Vec3 seite2, Vec3 seite3, Vec3 seite4){
	glBegin(GL_QUADS);
	//glNormal3d( 0, 0, 1);
	glVertex3dv( seite1.p);
	glVertex3dv( seite2.p);
	glVertex3dv( seite3.p);
	glVertex3dv( seite4.p);
	glEnd();
}
void drawCube(){
	//Festlegen der Position der Kanten
	Vec3 punktA(-length/2, -length/2, -length/2);
	Vec3 punktB(length/2, -length/2, -length/2);
	Vec3 punktC(-length/2, length/2, -length/2);
	Vec3 punktD(-length/2, -length/2, length/2);
	Vec3 punktE(length/2, length/2, -length/2);
	Vec3 punktF(length/2, -length/2, length/2);
	Vec3 punktG(-length/2, length/2, length/2);
	Vec3 punktH(length/2,length/2,length/2);

	/*Vec3 punktA(0, 0, 0);
	Vec3 punktB(length, 0, 0);
	Vec3 punktC(0, length, 0);
	Vec3 punktD(0, 0, length);
	Vec3 punktE(length, length, 0);
	Vec3 punktF(length, 0, length);
	Vec3 punktG(0, length, length);
	Vec3 punktH(length,length,length);*/

	//Alle Fl�chen des W�rfels zeichnen (Ohne Deckel)
		SetMaterialColor(1, 0, 0, 1);
		SetMaterialColor(2, 1, 0, 0);
		drawSquare(punktA, punktD, punktG, punktC);
		SetMaterialColor(2, 1, 0, 0);
		SetMaterialColor(1, 0, 0, 1);
		drawSquare(punktB, punktF, punktD, punktA);
		SetMaterialColor(1, 1, 0, 0);
		SetMaterialColor(2, 0, 0, 1);
		drawSquare(punktA, punktB, punktE, punktC);
		SetMaterialColor(1, 1, 0, 0);
		SetMaterialColor(2, 0, 0, 1);
		drawSquare(punktF, punktH, punktE, punktB);
		SetMaterialColor(2, 0, 0, 1);
		SetMaterialColor(1, 1, 0, 0);
		drawSquare(punktF, punktD, punktG, punktH);

	glPushMatrix();
		glTranslated(0, 1, 1);
		glRotated(winkelDeckel, 1, 0, 0);
		glTranslated(0, -1, -1);
		SetMaterialColor(2, 1, 0, 0);
		SetMaterialColor(1, 0, 0, 1);
		drawSquare(punktC, punktE, punktH, punktG);
	glPopMatrix();
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){

	//Translation sphere
	if (key == GLFW_KEY_J) {
		if(!kollision()){
			s1TX -= 0.1;
		}else{
			printf("Kollision");
		}
	}
	if (key == GLFW_KEY_L) {
		if(!kollision()){
			s1TX += 0.1;
		}else{
			printf("Kollision");
		}
	}
	if (key == GLFW_KEY_I) {
		if(!kollision()){
			s1TX += 0.1;
		}else{
			printf("Kollision");
		}
	}
	if (key == GLFW_KEY_K) {
		if(!kollision()){
			s1TY -= 0.1;
		}else{
			printf("Kollision");
		}
	}

	//Rotation
    if (key == GLFW_KEY_W) alpha_1 -= w1RSpeed;	//Hinten drehen
    if (key == GLFW_KEY_A) alpha_2 -= w1RSpeed;	//Vorne drehen
    if (key == GLFW_KEY_S) alpha_1 += w1RSpeed;	//Links drehen
    if (key == GLFW_KEY_D) alpha_2 += w1RSpeed;	//Rechts drehen

    //Translation
    if ((key == GLFW_KEY_UP && action == GLFW_PRESS)||(key == GLFW_KEY_UP && action == GLFW_REPEAT)) 	w1TY += .1;		//Hoch
    if ((key == GLFW_KEY_DOWN && action == GLFW_PRESS)||(key == GLFW_KEY_DOWN && action == GLFW_REPEAT)) 	w1TY -= .1;		//Runter
    if ((key == GLFW_KEY_LEFT && action == GLFW_PRESS)||(key == GLFW_KEY_LEFT && action == GLFW_REPEAT)) 	w1TX -= .1;		//Links
    if ((key == GLFW_KEY_RIGHT && action == GLFW_PRESS)||(key == GLFW_KEY_RIGHT && action == GLFW_REPEAT)) w1TX += .1;		//Rechts
    if ((key == GLFW_KEY_R && action == GLFW_PRESS)||(key == GLFW_KEY_R && action == GLFW_REPEAT)) w1TZ -= 0.1;		//Weg
    if ((key == GLFW_KEY_F && action == GLFW_PRESS)||(key == GLFW_KEY_F && action == GLFW_REPEAT)) w1TZ += 0.1;		//Nah

    //Skalierung
    if (key == GLFW_KEY_Z) {if(w1SX>=1.1)w1SX -= 0.1;}
	if (key == GLFW_KEY_Z) {if(w1SY>=1.1)w1SY -= 0.1;}
	if (key == GLFW_KEY_Z) {if(w1SZ>=1.1)w1SZ -= 0.1;}	//klein

	if (key == GLFW_KEY_H) {w1SX += 0.1;}
	if (key == GLFW_KEY_H) {w1SY += 0.1;}
	if (key == GLFW_KEY_H) {w1SZ += 0.1;}	//Gro�

	//Deckel

    if (key == GLFW_KEY_O) {
    	 if(winkelDeckel<=100){
    		winkelDeckel +=2;
    	 }
    }
    if (key == GLFW_KEY_C) {
     	 if(winkelDeckel>=2){
     		winkelDeckel -=2;
     	 }
     }

    //test
	if (key == GLFW_KEY_Q) {
		Vec3 pos (w1TX,w1TY,w1TZ);
		pos.Print("Position");
	}
}

void Preview() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();					// Reset The Current Modelview Matrix
	glPushMatrix();
		glTranslated(0, 0, -10.0);      // Move 10 units backwards in z,
										// since camera is at origin
		//Rotation
		glRotated(alpha_1, 1, 0, 0);
		glRotated(alpha_2, 0, 1, 0);

		//Translation
		glTranslated(w1TX, w1TY, w1TZ);
		//Skalierung
		glScaled(w1SX, w1SY, w1SZ);

		//  glRotated(alpha_, 0, 2, 1);
		//  alpha_ += 2;
		drawCube();
	glPopMatrix();
	glPushMatrix();
		glTranslated(-15, 9.5, -10);
		SetMaterialColor(3, 1, 0, 0);
		//DrawSphere(Vec3( (xpos*30/window_width_), (-ypos*20/window_height_), 0), radius);
		DrawSphere(Vec3( s1TX, s1TY, s1TZ), radius);
	glPopMatrix();

  //Test

}
int main() {
  GLFWwindow* window = NULL;

  printf("Here we go!\n");

  if(!glfwInit()){
    return -1;
  }

  window = glfwCreateWindow(window_width_, window_height_,
                            "Ueberragende 3D Animation", NULL, NULL);
  if(!window) {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  while(!glfwWindowShouldClose(window)) {
    // switch on lighting (or you don't see anything)
    InitLighting();

    // set background color
    glClearColor(0.8, 0.8, 0.8, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // draw the scene
    Preview();

    //Listener
    glfwSetKeyCallback(window, key_callback);
    glfwGetCursorPos(window, &xpos, &ypos);

    // make it appear (before this, it's hidden in the rear buffer)
    glfwSwapBuffers(window);

    glfwPollEvents();
  }
  glPopMatrix();

  glfwTerminate();

  //printf("Goodbye!\n");

  return 0;
}
