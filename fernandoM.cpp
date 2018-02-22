#include <X11/keysym.h>

//variables declared in main
extern int flipped;
extern float cx;

void rightKeyMovement(){

 if(keys[XK_Right]){
                        flipped = 0;
                        //man is walking...
                        //when time is up, advance the frame.
                        cx += 4;
                        timers.recordTime(&timers.timeCurrent);
                        double timeSpan = timers.timeDiff(&timers.walkTime, &timers.timeCurrent);
                        if (timeSpan > g.delay) {
                                //advance
                                ++g.walkFrame;
                                if (g.walkFrame >= 7)
                                        g.walkFrame -= 6;
                                timers.recordTime(&timers.walkTime);
                        }
                        /*
                        for (int i=0; i<20; i++) {
                                g.box[i][0] -= 2.0 * (0.05 / g.delay);
                                if (g.box[i][0] < -10.0)
                                        g.box[i][0] += g.xres + 10.0;
                        }
                        */
        }

}
