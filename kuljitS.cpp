// 3350 Project Rambo - kuljitS.cpp
// author: Kuljit Singh
// last modified: Feb 28, 2018

#include<X11/keysym.h>
#include "Global.h"
#include "Timers.h"
#include "SpriteSheet.h"
#include "Character.h"
#include "fonts.h"

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
		//rambo.setCenterY(rambo.getCenterY()+JUMP_STRENGTH);
		//Uncomment below when rambo get a velocity
		rambo.velocityY=JUMP_STRENGTH;
	}

	//apply gravity
	if (rambo.jumping) {
		//rambo.setCenterY(rambo.getCenterY() + -2.0f);
		rambo.velocityY += gravity;
	}
	/*uncomment when rambo gets a velocity
	  if(rambo.getCenterY() > 200){
	  rambo.setVelocityY(rambo.getVelocityY() + gravity;
	  }
	 */

	//update rambo position
	rambo.centerY +=rambo.velocityY;

	//velocity == 0 if standing on a platform
	if(rambo.centerY <= 200){
		rambo.velocityY = 0;
	}

}

void printKuljitS(int x, int y, int size, int color){
	Rect r;
	r.bot = y;
	r.left = x;
	r.center = 0;
	ggprint8b(&r, size, color, "Kuljit Singh");
}

