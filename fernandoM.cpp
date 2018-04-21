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
extern int MAX_ENEMIES;
extern int nEnemies;
extern Character* enemies;

using namespace std; 

//constants 
const int MAX_BULLETS = 30;

//Bullet Constructor
Bullet::Bullet() {

    velocityValue = 10;
    //define starter values
	pos[0] = rambo.getCenterX();
    pos[1] = rambo.getCenterY();
    vel[0] = 0;
    vel[1] = 0;
    height = 5.0;
    width = height;

}

//Bullet Destructor
Bullet::~Bullet() {

}

void Bullet::draw() {
     glColor3f(1.0, 1.0, 1.0);
                        glBegin(GL_QUADS);
                        glVertex2i(pos[0] - (width / 2), pos[1] + (height/2));
                        glVertex2i(pos[0] + (width / 2), pos[1] + (height/2));
                        glVertex2i(pos[0] + (width / 2), pos[1] - (height/2));
                        glVertex2i(pos[0] - (width / 2), pos[1] - (height/2));
                        glEnd();
}

void spaceButton() {
	if (keys[XK_space]) {

		struct timespec newBT;
		clock_gettime(CLOCK_REALTIME, &newBT);
		double seconds = timers.timeDiff(&g.bulletTimer, &newBT);

        if (seconds > 0.35) {
			timers.timeCopy(&g.bulletTimer, &newBT);

	        if (nbullets < MAX_BULLETS) {
                        
                //shoot a bullet...
                Bullet *b = &g.ramboBullets[nbullets];

                b->pos[0] = rambo.getCenterX();
                b->pos[1] = rambo.getCenterY();

                    if(rambo.angleUp){ 
	                    b->vel[0] = b->velocityValue;
	                    b->vel[1] = b->velocityValue;
                    }
                    else if (rambo.angleDown) { 
                        b->vel[0] = b->velocityValue;
	                    b->vel[1] = -b->velocityValue;

                    }
                    else if (rambo.shootingStraight) {
                        b->vel[0] = b->velocityValue;
                        b->vel[1] = 0;
                    }
                    else if (rambo.aimUp) {
                        b->vel[0] = 0;
                        b->vel[1] = b->velocityValue;
                    }
                    else if (rambo.jumping) {
                        	if(keys[XK_Left]){
		                        if(keys[XK_Up]){
			                        b->vel[0] = b->velocityValue;
			                        b->vel[1] = b->velocityValue;
                                }
		                        else if (keys[XK_Down]){ 
			                        b->vel[0] = b->velocityValue;
			                        b->vel[1] = -b->velocityValue;
                                }
		                        else {//shoot straight
			                        b->vel[0] = b->velocityValue;
			                        b->vel[1] = 0;
                                }
                            }
                            else if(keys[XK_Right]){
		                        if (keys[XK_Up]) { 
			                        b->vel[0] = b->velocityValue;
			                        b->vel[1] = b->velocityValue;
                                }
		                        else if(keys[XK_Down]) {
			                        b->vel[0] = b->velocityValue;
			                        b->vel[1] = -b->velocityValue;
                                }
		                        else { 
                                    //shoot straight
			                        b->vel[0] = b->velocityValue;
			                        b->vel[1] = 0;
                                }
                            }
                            else if(keys[XK_Up]) {
		                        b->vel[0] = 0;
		                        b->vel[1] = b->velocityValue;
                            }
                            else if(keys[XK_Down]){ 
		                        b->vel[0] = 0;
		                        b->vel[1] = -b->velocityValue;
                            }
                            else {
                                b->vel[0] = b->velocityValue;
		                        b->vel[1] = 0;
                            }
                    }
                            else { 
	                            b->vel[0] = b->velocityValue;
	                            b->vel[1] = 0;
                            }
                    
                    if (rambo.flipped) {

                    if(!(b->vel[0] < 0.0)) {
                                
                        b->vel[0] *= -1;

                    }            
                }
                else {
                    
                    if ((b->vel[0] < 0.0)) {
                        b->vel[0] *= -1;
                    }
                }        
                b->color[0] = 1.0f;
                b->color[1] = 1.0f;
                b->color[2] = 1.0f; 
                nbullets++;
            }
        }
    }	
}


void fernandoPhysics() {

	int i = 0;
    //Update bullet positions
	while (i < nbullets) {

		Bullet *b = &g.ramboBullets[i];

        b->pos[0] += b->vel[0];
        b->pos[1] += b->vel[1];
            
        //Check for collision with window edges and deleting if so
        if (b->pos[0] < 0.0) {
			memcpy(&g.ramboBullets[i], &g.ramboBullets[nbullets-1], sizeof(Bullet));
			nbullets--;
		}
		else if (b->pos[0] > (float)g.xres) {
			memcpy(&g.ramboBullets[i], &g.ramboBullets[nbullets-1], sizeof(Bullet));
			nbullets--;
		}
		else if (b->pos[1] < 0.0) {
			memcpy(&g.ramboBullets[i], &g.ramboBullets[nbullets-1], sizeof(Bullet));
			nbullets--;
		}
		else if (b->pos[1] > (float)g.yres) {
			memcpy(&g.ramboBullets[i], &g.ramboBullets[nbullets-1], sizeof(Bullet));
			nbullets--;
		}
		
        i++;
	}      
}

void deleteBullet(int n) {
    
    memcpy(&g.ramboBullets[n], &g.ramboBullets[nbullets-1], sizeof(Bullet));
    nbullets--;
                
}

double printGroupNumber() {
    

 static double td = 0.0; 
    #ifdef PROFILING
   //////////////////////////////////////////////
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
  //////////////////////////////////////////////////
    #endif
    return td;

 
}

double printGroupNumberOpt(){
 
    static double td = 0.0;
     #ifdef PROFILING
   //////////////////////////////////////////////
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
     //////////////////////////////////////////////////
   #endif
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