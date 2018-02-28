/* Author: Joshua Cancellier
 *
 * Start Date: February 24, 2018
 *
 * Purpose: handle character input, movement, and animations
 *
 */

#include <X11/keysym.h>
#include "Global.h"
#include "Timers.h"
#include "SpriteSheet.h"
#include "Character.h"
#include <GL/glx.h>
#include "joshuaC.h"

extern int flipped;
extern float cx;
extern Timers timers;
extern Global g;
extern int keys[];
extern Character rambo;
extern SpriteSheet img[];

//Constructors
Character::Character(int ssIdx)
{
    centerX = 100;
    centerY = 800;
    height = 50;
    width = height * 0.7;
    frame = 0;
    flipped = false;
    jumping = false;
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

//Character Member functions
void Character::draw()
{
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glBindTexture(GL_TEXTURE_2D, g.walkTexture);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    
    float ssWidth = (float)1.0/img[spriteSheetIndex].columns;
    float ssHeight = (float)1.0/img[spriteSheetIndex].rows;
    
    int ix = rambo.frame % img[spriteSheetIndex].columns;
    int iy = 0;
    
    //move to next row of spriteSheet (if available)
    if(frame >= img[spriteSheetIndex].columns) {
        iy = 1;
    }
    
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

//Handle Input and animations
void joshuaCInput()
{
    if (keys[XK_Right] == 0 && keys[XK_Left] == 0 && !rambo.jumping) {
        rambo.frame = 0;
    }
    
    jumpAnimation();
}

void jumpAnimation()
{
    if (rambo.centerY > 200) {
        rambo.jumping = true;
    }
    else {
        rambo.jumping = false;
    }
    
    if (keys[XK_a] || rambo.jumping) {
        
        //check if in walk state
        if (rambo.frame >= 0 && rambo.frame <= 6) {
            rambo.frame = 7;
        }
        //rambo.flipped = (keys[XK_Left] ? true : false);
        
        timers.recordTime(&timers.timeCurrent);
        //record time between frames
        double timeSpan = timers.timeDiff(&timers.walkTime,
                                          &timers.timeCurrent);
        if (timeSpan > g.delay) {
            //advance frame
            ++rambo.frame;
            if (rambo.frame >= 11) {
                rambo.frame = 7;
            }
            timers.recordTime(&timers.walkTime);
        }
    }
}
