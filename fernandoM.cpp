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


//extern variables
extern int flipped;
extern float cx;
extern Timers timers;
extern Global g;
extern int keys[];
extern Character rambo;
extern SpriteSheet img[];


//function to get input and make right/left movements
void walkInput() {
    
    if (keys[XK_Right] == 0 && keys[XK_Left] == 0 && !rambo.jumping) {
        
        rambo.frame = 0;
    }
    
    walkLeft();
    walkRight();
}

//function that makes characger walk left
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
