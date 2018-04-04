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
extern int gameState;
extern int selectedOption;
extern SpriteSheet img[];

#define JUMP_STRENGTH 12
#define INGAME 1

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

int acceptGameState(int selectedOption)
{
    switch(selectedOption){
        case 0:
            gameState = INGAME;
            break;
        case 1:
            //open HTML LEADERBOARD
            break;
        case 2:
            return 1;
        default:
            printf("FATAL ERROR IN GAME STATE\n\n");
            exit(1);
    }
    return 0;
}

void checkMouseMainMenu(XEvent *e)
{    
    if (e->type == KeyPress) {

    }
}

int checkKeysMainMenu(int key, XEvent *e)
{
    if (e->type == KeyPress) {
        switch (key){
            case XK_Up:
                selectedOption = ((selectedOption-1)+3)%3;
                break;
            case XK_Down:
                selectedOption = ((selectedOption+1)+3)%3;
                break;
            case XK_Return:
                return acceptGameState(selectedOption);
                break;
            case XK_Right:
                break;
            case XK_Escape:
                return 1;
                break;
        }
    }
    return 0; 
}

void renderMainMenu()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glBindTexture(GL_TEXTURE_2D, g.ramboLogoTexture);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);

    float ssWidth = (float)1.0/img[1].columns;
    float ssHeight = (float)1.0/img[1].rows;

    float textureX = 0;
    float textureY = 0;

    float centerX = g.xres/2;
    float centerY = g.yres*2/3; 

    float width = floor(((float)g.xres/1280)*img[1].width);
    float height = floor(((float)g.yres/720)*img[1].height);

    glBegin(GL_QUADS);
    glTexCoord2f(textureX, textureY+ssHeight);
    glVertex2i(centerX-width, centerY-height);

    glTexCoord2f(textureX, textureY);
    glVertex2i(centerX-width, centerY+height);

    glTexCoord2f(textureX+ssWidth, textureY);
    glVertex2i(centerX+width, centerY+height);

    glTexCoord2f(textureX+ssWidth, textureY+ssHeight);
    glVertex2i(centerX+width, centerY-height);
    glEnd();

    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST);

    Rect r;
    r.bot = g.yres/3;
    r.left = g.xres/2;
    r.center = 1;

    switch (selectedOption) {
        case 0:
            ggprint8b(&r, 16, 0x123fff, "NEW GAME");
            ggprint8b(&r, 16, 0xffffff, "LEADERBOARD");
            ggprint8b(&r, 16, 0xffffff, "EXIT");
            break;
        case 1:
            ggprint8b(&r, 16, 0xffffff, "NEW GAME");
            ggprint8b(&r, 16, 0x123fff, "LEADERBOARD");
            ggprint8b(&r, 16, 0xffffff, "EXIT");
            break;
        case 2:
            ggprint8b(&r, 16, 0xffffff, "NEW GAME");
            ggprint8b(&r, 16, 0xffffff, "LEADERBOARD");
            ggprint8b(&r, 16, 0x123fff, "EXIT");
            break;
        default:
//            printf("FATAL GAME ERROR\n\n");
            break;
    }
}
