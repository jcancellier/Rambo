// Platform boxes class
// Father: CS God
// Author: Erik Soto


#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <GL/glu.h>
#include <GL/glx.h>
#include "ppm.h"
#include "fonts.h"
#include "erikS.h"
#include "Global.h"
#include "Character.h"
extern Global g;
extern Level lev;
extern Character rambo;
using namespace std;

//macros
#define rnd() (((double)rand())/(double)RAND_MAX)
#define random(a) (rand()%a)
#define VecCopy(a,b) (b)[0]=(a)[0];(b)[1]=(a)[1];(b)[2]=(a)[2]
#define VecDot(a,b)	((a)[0]*(b)[0]+(a)[1]*(b)[1]+(a)[2]*(b)[2])
#define VecSub(a,b,c) (c)[0]=(a)[0]-(b)[0]; \
			     (c)[1]=(a)[1]-(b)[1]; \
    (c)[2]=(a)[2]-(b)[2]
void teleportCheck()
{
    if(rambo.centerX < 0)
    {   
	rambo.centerX = g.xres;
    }
    if(rambo.centerX > g.xres)
    {
	rambo.centerX = 0;
    } 
}
void renderBackground(float s , float sh, float w, float h)
{
    //background image
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glBindTexture(GL_TEXTURE_2D, g.RamboTexture);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);

    float ssWidth = s;
    float ssHeight =sh;

    float textureX = 0;
    float textureY = 0;

    float centerX = g.xres / 2;
    float centerY = (g.yres / 2) + g.yres*0.20833;

    float width = w;
    float height = h;

    glBegin(GL_QUADS);
    glTexCoord2f(textureX, textureY + ssHeight);
    glVertex2i(centerX - width, centerY - height);

    glTexCoord2f(textureX, textureY);
    glVertex2i(centerX - width, centerY + height);

    glTexCoord2f(textureX + ssWidth, textureY);
    glVertex2i(centerX + width, centerY + height);

    glTexCoord2f(textureX + ssWidth, textureY + ssHeight);
    glVertex2i(centerX + width, centerY - height);
    glEnd();

    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST);
    //render background end
}

void pauseScreen()
{
    //Renders Pause Screen
    Rect r; 
    float h = 100.0;
    float w = 200.0;
    glPushMatrix();
    glEnable(GL_BLEND);
    glColor4f(0.58,0.58,0.72,0.8);
    glTranslated(g.xres/2, g.yres/2, 0);
    glBegin(GL_QUADS);
    glVertex2i(-w, -h);
    glVertex2i(-w,  h);
    glVertex2i(w,   h);
    glVertex2i(w,  -h);
    glEnd();
    glDisable(GL_BLEND);
    glPopMatrix();
    r.bot = g.yres/2 + 80;
    r.left = g.xres/2;
    r.center = 1; 
    ggprint8b(&r, 16, 0, "PAUSE SCREEN");
    r.center = 0;
    r.left = g.xres/2 - 100;
    // start game timer and clear screen with double buffer for pretty transition
    ggprint8b(&r, 16, 0, "Press P - Play");
    // implent with the keys function 
    ggprint8b(&r, 16, 0, "Press E - Exit to Menu");
    ggprint8b(&r, 16, 0, "Press Esc - Exit Game");
}

Platform::Platform(
	float xpos ,float ypos,
	float xpos2 ,float ypos2,
	float xpos3 ,float ypos3,
	float xpos4 ,float ypos4)
{
    // set the ranges for physics
    top = greatest(ypos,ypos2,ypos3,ypos4);

    one.x = xpos;
    one.y = ypos;

    two.x = xpos2;
    two.y = ypos2;

    three.x = xpos3;
    three.y = ypos3;

    four.x = xpos4;
    four.y = ypos4;
}

void Platform::drawPlatform()
{
    glColor3f(0.8, 0.8, 0.6);
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, g.walkTexture);
    /*	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0); glVertex2i( 0,  0);
	glTexCoord2f(0.0, 0.0); glVertex2i( 0, ty);
	glTexCoord2f(1.0, 0.0); glVertex2i(tx, ty);
	glTexCoord2f(1.0, 1.0); glVertex2i(tx,  0);
	glEnd();
	*/
    glBegin(GL_QUADS);
    glVertex2i(one.x,	one.y);
    glVertex2i(two.x,	two.y);
    glColor3f(set.r,set.g,set.b);
    glVertex2i(three.x,	three.y);
    glVertex2i(four.x,	four.y);

    glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Platform::setColor(float r, float g, float b)
{
    set.r =r;
    set.g =g;
    set.b = b;


}

float Platform::greatest(float one,float two,float three,float four)
{
    float g= greatest( one,two);
    float b= greatest(three,four);
    return greatest(g,b);

}

float Platform::greatest(float one,float two)
{
    if(one < two)
    {
	return two;
    }
    else return one;

}

class levelGlo {
    public:
	Vec box[20];
	//camera is centered at (0,0) lower-left of screen. 
	Flt camera[2];
	~levelGlo() {

	}
	levelGlo() {

	    camera[0] = camera[1] = 40.0;
	    for (int i=0; i<20; i++) {
		box[i][0] = rnd() * g.xres;
		box[i][1] = rnd() * (g.yres-220) + 220.0;
		box[i][2] = 0.0;
	    }
	    //memset(keys, 0, 65536);
	}
};

Level::Level() {
    for (int i=0; i < 180; i++) {

	dynamicHeight[i] = -1;

    }

    tilesize[0] = 32;

    tilesize[1] = 32;

    ftsz[0] = (Flt)tilesize[0];

    ftsz[1] = (Flt)tilesize[1];

    tile_base = (g.yres/g.yres);

    //read level
    FILE *fpi = fopen("level.txt","r");

    if (fpi) {

	nrows=0;

	char line[700];

	while (fgets(line, 700, fpi) != NULL) {

	    removeCrLf(line);

	    int slen = strlen(line);

	    ncols = slen;
	    for (int j=0; j<slen; j++) {

		arr[nrows][j] = line[j];

	    }

	    ++nrows;

	}

	fclose(fpi);

    }



}

void Level::removeCrLf(char *str) {
    char *p = str;

    while (*p) {

	if (*p == 10 || *p == 13) {

	    *p = '\0';

	    break;

	}

	++p;

    }

}

// need to design the level with text file
void renderlevel(){
    //========================
    //Render the tile system
    //========================
    int tx = lev.tilesize[0];
    int ty = lev.tilesize[1];
    Flt dd = lev.ftsz[0];
    Flt offy = lev.tile_base;
    int ncols_to_render = g.xres / lev.tilesize[0] + 2;
    int col = (int)(g.camera[0] / dd);
    col = col % lev.ncols;

    Flt cdd = g.camera[0] / dd;
    //flo: just the integer portion
    Flt flo = floor(cdd);
    //dec: just the decimal portion
    Flt dec = (cdd - flo);
    //offx: the offset to the left of the screen to start drawing tiles
    Flt offx = -dec * dd;

    for (int j=0; j<ncols_to_render; j++) {
	int row = lev.nrows-1;
	for (int i=0; i<lev.nrows; i++) {
	    if (lev.arr[row][col] == 'w') {
		glColor3f(0.8, 0.8, 0.6);
		glPushMatrix();
		//put tile in its place
		glTranslated((Flt)j*dd+offx, (Flt)i*lev.ftsz[1]+offy, 0);
		glBegin(GL_QUADS);
		glVertex2i( 0,  0);
		glVertex2i( 0, ty);
		glVertex2i(tx, ty);
		glVertex2i(tx,  0);
		glEnd();
		glPopMatrix();
	    }
	    if (lev.arr[row][col] == 'b') {
		glColor3f(0.9, 0.2, 0.2);
		glPushMatrix();
		glTranslated((Flt)j*dd+offx, (Flt)i*lev.ftsz[1]+offy, 0);
		glBegin(GL_QUADS);
		glVertex2i( 0,  0);
		glVertex2i( 0, ty);
		glVertex2i(tx, ty);
		glVertex2i(tx,  0);
		glEnd();
		glPopMatrix();
	    }
	    --row;
	}
	col = (col+1) % lev.ncols;
    }
}

void Live(int xres, int yres)
{
    //generate a healthbar on top left of the screen
    //dynamic based on the amount of lives left
    Rect r;
    unsigned int c = 0x002d88d8;
    r.bot = yres-30;
    r.left = (xres/xres)+70 ;
    r.center = 0;
    ggprint8b(&r, 16, c, "Lives");

    for (int i = 0; i < 3; i++) {
	glPushMatrix();
	glColor3ub(255, 0, 255);
	glTranslatef(g.xres/2, g.yres/2, 0);
	float w = g.xres/100;
	float h = g.yres/100;
	glBegin(GL_QUADS);
	// have to texture map rambos head to each quad;
	glVertex2i(-w, -h);
	glVertex2i(-w, h);
	glVertex2i(w, h);
	glVertex2i(w, -h);
	glEnd();
	glPopMatrix();
    }
}
void erikRender()
{
    Platform a(0,200,0,210,150,210,150,200);
    Platform c(g.xres,200,g.xres,210,g.xres-150,210,g.xres-150,200);
    Platform d((g.xres/3)+25,200,(g.xres/3)+25,210,(g.xres/3)-170+25,210,(g.xres/3)-170+25,200);
    Platform e((g.xres/1.3)+25,200,(g.xres/1.3)+25,210,(g.xres/1.3)-170+25,210,(g.xres/1.3)-170+25,200);
    a.drawPlatform();   
    c.drawPlatform();   
    d.drawPlatform();   
    e.drawPlatform();  
}


