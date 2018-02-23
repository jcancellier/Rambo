#include<X11/keysym.h>
#include "Global.h"
#include "Timers.h"
#include "SpriteSheet.h"
#include "Character.h"

extern int flipped;
extern float cx;
extern Timers timers;
extern Global g;
extern int keys[];
extern Character rambo;

Character::Character(){
    centerX = 100;
    centerY = 200;
    height = 50;
    width = height * 0.7;
    frame = 0;
    flipped = false;
    health = 4;
}

//Accessors
float Character::getCenterX() const{ return centerX; }
float Character::getCenterY() const{ return centerY; }
float Character::getHeight() const{ return height; }
float Character::getWidth() const{ return width; }
int Character::getFrame() const{ return frame; }
bool Character::isFlipped() const{ return flipped; }
float Character::getHealth() const{ return health; }

//Mutators
void Character::setCenterX(float x){ centerX = x; }
void Character::setCenterY(float y){ centerY = y; }
void Character::setHeight(float h){ height = h; }
void Character::setWidth(float w){ width = w; }
void Character::setFrame(int f){ frame = f; }
void Character::setFlipped(bool f){ flipped = f; }
void Character::setHealth(float h){health = h; }

void walkLeft()
{
    if(keys[XK_Left]){
	flipped = 1;
	//man is walking...
	//when time is up, advance the frame.
	cx -= 4;
	timers.recordTime(&timers.timeCurrent);
	double timeSpan = timers.timeDiff(&timers.walkTime, &timers.timeCurrent);
	if (timeSpan > g.delay) {
	    //advance
	    ++rambo.frame;
	    if (rambo.frame >= 7)
		rambo.frame -= 6;
	    timers.recordTime(&timers.walkTime);
	}
    }
}
