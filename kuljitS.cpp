// 3350 Project Rambo - kuljitS.cpp
// author: Kuljit Singh
// last modified: Feb 28, 2018

#include<X11/keysym.h>
#include "Global.h"
#include "Timers.h"
#include "SpriteSheet.h"
#include "Character.h"
#include "fonts.h"
#include <sstream>

extern int flipped;
extern float cx;
extern Timers timers;
extern Global g;
extern int keys[];
extern Character rambo;
extern float gravity;

#define JUMP_STRENGTH 12

void kuljitS_physics() 
{
    //check for a jump
    if (keys[XK_a] && !rambo.jumping) {
        rambo.jumping = true;
        rambo.velocityY=JUMP_STRENGTH;
    }

    //apply gravity
    if (rambo.jumping) {
        rambo.velocityY += gravity;
    }

    //update rambo position
    rambo.centerY +=rambo.velocityY;

    //velocity == 0 if standing on a platform
    if(rambo.centerY <= 200){
        rambo.velocityY = 0;
    }

}

double printRamboCenter(){
    
    static double td = 0.0;
    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);

    Rect r;
    r.bot = g.yres*2/4;
    r.left = g.xres/2;
    r.center = 1;
    ggprint8b(&r, 16, 0xffffff, "RAMBO");

    clock_gettime(CLOCK_REALTIME, &end);
    td += timers.timeDiff(&start, &end);

    return td;
}


double printRamboCenterOpt(){
    
    static double td = 0.0;
    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);

    Rect r;
    r.bot = g.yres << 1;
    r.bot = r.bot >> 2;
    r.left = g.xres >> 1;
    r.center = 1;
    ggprint8b(&r, 16, 0xffffff, "RAMBO");

    clock_gettime(CLOCK_REALTIME, &end);
    td += timers.timeDiff(&start, &end);

    return td;
}
void printKuljitS(int x, int y, int size, int color){
    Rect r;
    r.bot = y;
    r.left = x;
    r.center = 0;
    ggprint8b(&r, size, color, "Kuljit Singh");
    ggprint8b(&r, size, color, "RAMBO: %lf",printRamboCenter());
    ggprint8b(&r, size, color, "R_OPT: %lf",printRamboCenterOpt());
}
