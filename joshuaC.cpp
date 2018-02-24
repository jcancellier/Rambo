#include<X11/keysym.h>
#include "Global.h"
#include "Timers.h"
#include "SpriteSheet.h"
#include "Character.h"
#include <GL/glx.h>

extern int flipped;
extern float cx;
extern Timers timers;
extern Global g;
extern int keys[];
extern Character rambo;
extern SpriteSheet img[];

Character::Character(int ssIdx){
	centerX = 100;
	centerY = 200;
	height = 50;
	width = height * 0.7;
	frame = 0;
	flipped = false;
	health = 4;
    spriteSheetIndex = ssIdx;
    velocityX = 4;
    velocityY = 4;
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

//Others
void Character::draw()
{
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glBindTexture(GL_TEXTURE_2D, g.walkTexture);
	//
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);
	glColor4ub(255,255,255,255);

    float ssWidth = (float)1.0/img[spriteSheetIndex].columns;
    float ssHeight = (float)1.0/img[spriteSheetIndex].rows;

	int ix = rambo.frame % img[spriteSheetIndex].columns;
	int iy = 0;

    //move to next row of spriteSheet (if available)
	if(rambo.frame >= 7)
        	iy = 1;

	float textureX = (float)ix / img[spriteSheetIndex].columns;
	float textureY = (float)iy / img[spriteSheetIndex].rows;
	glBegin(GL_QUADS);
	    glTexCoord2f(textureX, textureY+ssHeight); 
        glVertex2i(flipped ? centerX+width : centerX-width, centerY-height);

	    glTexCoord2f(textureX, textureY);    
        glVertex2i(flipped ? centerX+width : centerX-width, centerY+height);

	    glTexCoord2f(textureX+ssWidth, textureY);    
        glVertex2i(flipped ? centerX-width : centerX+width, centerY+height);

	    glTexCoord2f(textureX+ssWidth, textureY+ssHeight); 
        glVertex2i(flipped ? centerX-width : centerX+width, centerY-height);
	glEnd();
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_ALPHA_TEST); 
}

void walkLeft()
{
	if(keys[XK_Left]){
		rambo.flipped = true;
		rambo.centerX -= rambo.velocityX;
		timers.recordTime(&timers.timeCurrent);
		//record time between frames
		double timeSpan = timers.timeDiff(&timers.walkTime, &timers.timeCurrent);
		if (timeSpan > g.delay) {
			//advance frame
			++rambo.frame;
			if (rambo.frame >= 7)
				rambo.frame -= 6;
			timers.recordTime(&timers.walkTime);
		}
	}
}
