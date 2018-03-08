/*
 Author: Fernando Montes De Oca
 Date: February 23, 2018
 */

//includes
#include <X11/keysym.h>
#include "Global.h"
#include "Timers.h"
#include "SpriteSheet.h"
#include "Character.h"
#include <GL/glx.h>
#include "fernandoM.h"
#include "Bullet.h" 
#include <sstream>
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


//constants 
const int MAX_BULLETS = 11;

//function to get input and make right/left movements
void walkInput() {
    
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

double printGroupNumber() {
    
    static double td = 0.0; 
    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);

    Rect r;
    r.center = 0;
    r.bot = g.yres - 200;
    r.left = g.xres/4;
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

void printFernandoM(int x, int y, int size, int color) {

	Rect r;
	r.bot = g.yres - 300;
    	r.left = 30;
    	r.center = 0;
    	ggprint8b(&r, size, color, "Fernando Montes De Oca");
    	ggprint8b(&r, size, color, "GROUP NAME: %lf",printGroupNumber());
    	ggprint8b(&r, size, color, "GROUP NAME OPT: %lf",printGroupNumberOpt());
}

Bullet::Bullet() {

    //define values
    //
	pos[0] = rambo.getCenterX();
        pos[1] = rambo.getCenterY();
        vel[0] = rambo.getVelocityX();
        vel[1] = rambo.getVelocityY();

}

void Bullet::draw(){

    for (int i=0; i<10; i++)
    {
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_POINTS);
                glVertex2f(pos[0]-1.0f, pos[1]);
                glVertex2f(pos[0]+1.0f, pos[1]);
                glVertex2f(pos[0],      pos[1]-1.0f);
                glVertex2f(pos[0],      pos[1]+1.0f);
                glColor3f(0.8, 0.8, 0.8);
                glVertex2f(pos[0]-1.0f, pos[1]-1.0f);
                glVertex2f(pos[0]-1.0f, pos[1]+1.0f);
                glVertex2f(pos[0]+1.0f, pos[1]-1.0f);
                glVertex2f(pos[0]+1.0f, pos[1]+1.0f);

	glEnd();

	}
}
/*
                if (e->xbutton.button==1) {
                        //Left button is down
                        //a little time between each bullet
                        struct timespec bt;
                        clock_gettime(CLOCK_REALTIME, &bt);
                        double ts = timeDiff(&g.bulletTimer, &bt);
                        if (ts > 0.1) {
                                timeCopy(&g.bulletTimer, &bt);
                                //shoot a bullet...
                                if (g.nbullets < MAX_BULLETS) {
                                        Bullet *b = &g.barr[g.nbullets];
                                        timeCopy(&b->time, &bt);
                                        b->pos[0] = g.ship.pos[0];
                                        b->pos[1] = g.ship.pos[1];
                                        b->vel[0] = g.ship.vel[0];
                                        b->vel[1] = g.ship.vel[1];
                                        //convert ship angle to radians
                                        Flt rad = ((g.ship.angle+90.0) / 360.0f) * PI * 2.0;
                                        //convert angle to a vector
                                        Flt xdir = cos(rad);
                                        Flt ydir = sin(rad);
                                        b->pos[0] += xdir*20.0f;
                                        b->pos[1] += ydir*20.0f;
                                        b->vel[0] += xdir*6.0f + rnd()*0.1;
                                        b->vel[1] += ydir*6.0f + rnd()*0.1;
                                        b->color[0] = 1.0f;
                                        b->color[1] = 1.0f;
                                        b->color[2] = 1.0f;
                                        ++g.nbullets;
                                }
                        }
                }
    }
}
*/

void spaceButton()
{

		if (keys[XK_space]) {
                //a little time between each bullet
        //        struct timespec bt;
	//	timers.recordTime(&timers.timeCurrent);
          //      clock_gettime(CLOCK_REALTIME, &bt);
        //        double ts = timeDiff(&g.bulletTimer, &bt);
        //        if (ts > 0.1) {
        //                timeCopy(&g.bulletTimer, &bt);
         

	              if (nbullets < MAX_BULLETS) {
                                //shoot a bullet...
                                //Bullet *b = new Bullet;
                                //Bullet *b = &g.barr[g.nbullets];
                               // timeCopy(&b->time, &bt);
                                
			//	Bullet *b = new Bullet;
				
                                nbullets++;
                                //convert angle to a vector
                         /*       b->pos[0] += xdir*20.0f;
                                b->pos[1] += ydir*20.0f;
                                b->vel[0] += xdir*6.0f + rnd()*0.1;
                                b->vel[1] += ydir*6.0f + rnd()*0.1;
                                b->color[0] = 1.0f;
                                b->color[1] = 1.0f;
                                b->color[2] = 1.0f; */
                        }
                }	

}

void fernandoPhysics()
{
/*
        //Update bullet positions
        struct timespec bt;
        clock_gettime(CLOCK_REALTIME, &bt);
        int i=0;
        while (i < nbullets) {
                Bullet *b = new Bullet;
                //How long has bullet been alive?
                double ts = timeDiff(&b->time, &bt);
                if (ts > 2.5) {
                        //time to delete the bullet.
                        memcpy(&g.barr[i], &g.barr[g.nbullets-1],
                                sizeof(Bullet));
                        g.nbullets--;
                        //do not increment i.
                        continue;
                }
                //move the bullet
                b->pos[0] += b->vel[0];
                b->pos[1] += b->vel[1];
                //Check for collision with window edges
                if (b->pos[0] < 0.0) {
                        b->pos[0] += (float)gl.xres;
                }
                else if (b->pos[0] > (float)gl.xres) {
                        b->pos[0] -= (float)gl.xres;
                }
                else if (b->pos[1] < 0.0) {
                        b->pos[1] += (float)gl.yres;
                }
                else if (b->pos[1] > (float)gl.yres) {
                        b->pos[1] -= (float)gl.yres;
                }
                i++;
        }
*/
/*		if (gl.keys[XK_space]) {
                //a little time between each bullet
                struct timespec bt;
                clock_gettime(CLOCK_REALTIME, &bt);
                double ts = timeDiff(&g.bulletTimer, &bt);
                if (ts > 0.1) {
                        timeCopy(&g.bulletTimer, &bt);
                        if (g.nbullets < MAX_BULLETS) {
                                //shoot a bullet...
                                //Bullet *b = new Bullet;
                                Bullet *b = &g.barr[g.nbullets];
                                timeCopy(&b->time, &bt);
                                b->pos[0] = g.ship.pos[0];
                                b->pos[1] = g.ship.pos[1];
                                b->vel[0] = g.ship.vel[0];
                                b->vel[1] = g.ship.vel[1];
                                //convert ship angle to radians
                                Flt rad = ((g.ship.angle+90.0) / 360.0f) * PI * 2.0;
                                //convert angle to a vector
                                Flt xdir = cos(rad);
                                Flt ydir = sin(rad);
                                b->pos[0] += xdir*20.0f;
                                b->pos[1] += ydir*20.0f;
                                b->vel[0] += xdir*6.0f + rnd()*0.1;
                                b->vel[1] += ydir*6.0f + rnd()*0.1;
                                b->color[0] = 1.0f;
                                b->color[1] = 1.0f;
                                b->color[2] = 1.0f;
                                g.nbullets++;
                        }
                }
        }

*/
}






