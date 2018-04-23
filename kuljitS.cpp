// 3350 Project Rambo - kuljitS.cpp
// author: Kuljit Singh
// last modified: Feb 28, 2018

#include<X11/keysym.h>
#include "Global.h"
#include "Timers.h"
#include "SpriteSheet.h"
#include "Character.h"
#include "Enemy1.h"
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
extern int MAX_ENEMIES;
extern int nEnemies;
extern Enemy1* enemies;
extern int nbullets;
extern void deleteBullet(int);
extern int done;

double menuSelectionDelay = 0.15;
double enemySpawnDelay = 1.0;
double ramboCollisionDelay = 1.0;
#define JUMP_STRENGTH 12
#define INGAME 1
#define MAINMENU 0

void kuljitS_physics() 
{
    //check for bullet collision with enemy
    for (int i=0; i<nbullets; i++) {
        for (int j=0; j<nEnemies; j++) {
            if (g.ramboBullets[i].pos[0] > enemies[j].hitBox->getLeft() &&
                    g.ramboBullets[i].pos[0] < enemies[j].hitBox->getRight() &&
                    g.ramboBullets[i].pos[1] > enemies[j].hitBox->getBottom() &&
                    g.ramboBullets[i].pos[1] < enemies[j].hitBox->getTop()) {
                deleteBullet(i);
                enemies[j].centerY = enemies[nEnemies-1].centerY;
                enemies[j].centerX = enemies[nEnemies-1].centerX;
                enemies[j].velocityY = enemies[nEnemies-1].velocityY;
                enemies[j].velocityX = enemies[nEnemies-1].velocityX;
                enemies[j].flipped = enemies[nEnemies-1].flipped;
                enemies[j].health = enemies[nEnemies-1].health;
                g.score+=50;
                nEnemies--;
            }
        }
    }
 
    //create new enemies if not at max enemies
    if (nEnemies < MAX_ENEMIES) {
        timers.recordTime(&timers.timeCurrent);
        double timeSpan = timers.timeDiff(&timers.enemySpawnTime,
                                            &timers.timeCurrent);
        if (timeSpan > enemySpawnDelay) {
            enemies[nEnemies].centerY = 100;  
            if (rnd() < .5) {
                enemies[nEnemies].centerX = 0 - rnd()*50; 
                enemies[nEnemies].velocityX = rnd()*2 + 2;  
                enemies[nEnemies].flipped=true;
            } else {
                enemies[nEnemies].centerX = g.xres + rnd()*50;  
                enemies[nEnemies].velocityX = -1*(rnd()*2 + 2);
                enemies[nEnemies].flipped=false;  
            }
            timers.recordTime(&timers.enemySpawnTime); 
            nEnemies++; 
        }  
    }    

    //check for enemy collisions
    for (int i=0; i<nEnemies; i++) {
        if (enemies[i].hitBox->getLeft() <= rambo.hitBox->getRight() &&
                    enemies[i].hitBox->getRight() >= rambo.hitBox->getLeft() &&
                    enemies[i].hitBox->getTop() >= rambo.hitBox->getBottom() &&
                    enemies[i].hitBox->getBottom() <= rambo.hitBox->getTop()) {
            timers.recordTime(&timers.timeCurrent);
            double timeSpan = timers.timeDiff(&timers.ramboCollisionTime,
                                                &timers.timeCurrent);
            if (timeSpan > ramboCollisionDelay) {
                printf("Enemy Collision\n");
                rambo.health--;
                if (rambo.health<=0) {
                    printf("RAMBO DEAD\n");
                    //temporary until death menu exists
                    gameState=MAINMENU; 
                }
                timers.recordTime(&timers.ramboCollisionTime);
            }

        }
    } 

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
    rambo.centerX +=rambo.velocityX;

    //update enemy positions
    for (int i=0; i<nEnemies; i++) {
        if (enemies[i].centerX < 0 && enemies[i].velocityX<0) {
            enemies[i].velocityX *= -1;
            enemies[i].flipped=true;
        }

        if (enemies[i].centerX > g.xres && enemies[i].velocityX>0) {
            enemies[i].velocityX *= -1;
            enemies[i].flipped=false;
        }
        enemies[i].centerX += enemies[i].velocityX;
        enemies[i].centerY += enemies[i].velocityY;
    }

    //velocity == 0 if standing on a platform
    if (rambo.centerY <= 100) {
        rambo.centerY = 100;
        rambo.velocityY = 0;
    }

}

void kuljitS_render(){
    Rect r;
    
    //draw enemies + enemy ID's
    for (int i=0; i<nEnemies; i++) {
        enemies[i].draw();
        r.left = enemies[i].centerX;
        r.bot = enemies[i].centerY + 100;
        ggprint8b(&r, 16, 0xffffff, "%i", i);
    }

    //print score
    r.bot = g.yres-20;
    r.left = g.xres/2;
    r.center = 1;
    ggprint13(&r, 16, 0xffffff, "Score: %i", g.score);
    
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
    //update game state to selected option in main menu
    switch (selectedOption) {
        case 0:
            gameState = INGAME;
            break;
        case 1:
            //open HTML LEADERBOARD
            system("firefox cs.csubak.edu");
            //ShellExecute(NULL, "open", "cs.csubak.edu", NULL, NULL, SW_SHOWNORMAL);
            break;
        case 2:
            done=1;
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

void checkKeysMainMenu()
{
        if (keys[XK_Up]) {
            timers.recordTime(&timers.timeCurrent);
            double timeSpan = timers.timeDiff(&timers.menuSelectionTime,
                                                &timers.timeCurrent);
            if (timeSpan > menuSelectionDelay) {
                selectedOption = ((selectedOption-1)+3)%3;
                timers.recordTime(&timers.menuSelectionTime);
            }
        }
        
        if (keys[XK_Down]) {
            timers.recordTime(&timers.timeCurrent);
            double timeSpan = timers.timeDiff(&timers.menuSelectionTime,
                                                &timers.timeCurrent);
            if (timeSpan > menuSelectionDelay) {
                selectedOption = ((selectedOption+1)+3)%3;
                timers.recordTime(&timers.menuSelectionTime);
            }
        }
        
        if (keys[XK_Return]) {
            timers.recordTime(&timers.timeCurrent);
            double timeSpan = timers.timeDiff(&timers.menuSelectionTime,
                                                &timers.timeCurrent);
            if (timeSpan > menuSelectionDelay) {
                acceptGameState(selectedOption);
                timers.recordTime(&timers.menuSelectionTime);
            }
        }

/*        case XK_Down:
        case XK_Escape:
            done = 1;
            break;*/
}

void renderMainMenu()
{
    //set background to black
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    //draw rambo logo //////////////////////////////////////
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

    ////////////////////////////////////////////

    //display meny options
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
