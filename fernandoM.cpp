/*
 Author: Fernando Montes De Oca
 Date: February 23, 2018
 */

//includes
#include <X11/keysym.h>
#include <sstream>
#include <GL/glx.h>
#include <iostream>
#include <cmath>
#include "Global.h"
#include "Timers.h"
#include "SpriteSheet.h"
#include "Character.h"
#include "fernandoM.h"
#include "Bullet.h" 
#include "fonts.h"

//extern variables
extern int flipped;
extern float cx;
extern Timers timers;
extern Global g;
extern int keys[];
extern Character rambo;
extern SpriteSheet img[];
extern int nbullets;

using namespace std; 

//constants 
const int MAX_BULLETS = 30;


//function to get input and make right/left movements
void walkInput() {

//      makes Rambo stay still if no keys are being pressed and he's not jumping
    if (keys[XK_Right] == 0 && keys[XK_Left] == 0 && !rambo.jumping) {
        
        rambo.frame = 0;
    }
    
    walkLeft();
    walkRight();
}

//function that makes character walk left
void walkLeft()
{
    if (keys[XK_Left]) {

        rambo.flipped = true;
        rambo.centerX -= rambo.velocityX;
        timers.recordTime(&timers.timeCurrent);
        //record time between frames
        double timeSpan = timers.timeDiff(&timers.walkTime,
                                          &timers.timeCurrent);
        if (timeSpan > g.delay) {
            //advance frame
            ++rambo.frame;
            if (rambo.frame >= 7) {
                rambo.frame -= 6;
            }
            timers.recordTime(&timers.walkTime);
        }
    }
}

//function that makes character walk right
void walkRight()
{
    if (keys[XK_Right]) {
        rambo.flipped = false;
        rambo.centerX += rambo.velocityX;
        timers.recordTime(&timers.timeCurrent);
        //record time between frames
        double timeSpan = timers.timeDiff(&timers.walkTime,
                                          &timers.timeCurrent);
        if (timeSpan > g.delay) {
            //advance frame
            ++rambo.frame;
            if (rambo.frame >= 7) {
                rambo.frame -= 6;
            }
            timers.recordTime(&timers.walkTime);
        }
    }
}

//Bullet Constructor
Bullet::Bullet() {

    //define values
	pos[0] = rambo.getCenterX();
        pos[1] = rambo.getCenterY();
        vel[0] = 10;
        vel[1] = 10;
}

//Bullet Destructor
Bullet::~Bullet() {
        cout << "destructor" << endl;
}

void spaceButton()
{
	if (keys[XK_space]) {
	        if (nbullets < MAX_BULLETS) {
                        //shoot a bullet...

                        Bullet *b = &g.ramboBullets[nbullets];
                        //convert angle to a vector
                        float rad = ((90.0+90.0) / 360.0f) * 3.14 * 2.0;
			//convert angle to a vector
			float xdir = cos(rad);
			float ydir = sin(rad);

                        b->pos[0] = rambo.getCenterX();
                        b->pos[1] = rambo.getCenterY();
                        b->vel[0] += xdir*6.0f + rnd()*0.1;
                        b->vel[1] += ydir*6.0f + rnd()*0.1;  
                        b->color[0] = 1.0f;
                        b->color[1] = 1.0f;
                        b->color[2] = 1.0f; 
                        nbullets++;
                }
        }	

}
void fernandoPhysics()
{
        //Update bullet positions
	int i = 0;
	while (i < nbullets) {

		Bullet *b = &g.ramboBullets[i];

		//if he's looking left, shoot left

                //still need to delete bullets..
                if(rambo.flipped) {
                        b->pos[0] -= 135;
		        b->pos[1] -= 5;
                }
                else { 
                        b->pos[0] += 135;
		        b->pos[1] += 5;
                }
		i++;
	}
}
double printGroupNumber() {
    
    static double td = 0.0; 
    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);

    Rect r;
    r.center = 0;
    r.bot = g.yres - 200;
    r.left = g.xres/4;

    for(int i = 0; i < 100000; i++) {

    r.center = 0;
    }
    ggprint8b(&r, 16, 0xffff47, "Group 2");

    clock_gettime(CLOCK_REALTIME, &end);
    td += timers.timeDiff(&start, &end);

    return td;

}

double printGroupNumberOpt(){

    static double td = 0.0;
    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);

    Rect r;
    r.bot = g.yres << 2;
    r.bot = r.bot >> 2;
    r.left = g.xres >> 2;
    r.center = 0;
    ggprint8b(&r, 16, 0xffff47, "Group 2");

    clock_gettime(CLOCK_REALTIME, &end);
    td += timers.timeDiff(&start, &end);

    return td;
}

void printFernandoM(int size, int color) {

	Rect r;
	r.bot = g.yres - 300;
    	r.left = 30;
    	r.center = 0;
    	ggprint8b(&r, size, color, "Fernando Montes De Oca");
    	ggprint8b(&r, size, color, "GROUP NAME: %lf",printGroupNumber());
    	ggprint8b(&r, size, color, "GROUP NAME OPT: %lf",printGroupNumberOpt());
}
