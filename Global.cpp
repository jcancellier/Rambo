#include "Global.h"

Global::Global() {
    done=0;
    xres=1280;
    yres=720;
    walk=0;
    walkFrame=0;
    delay = 0.1;
    for (int i=0; i<20; i++) {
	box[i][0] = rnd() * xres;
	box[i][1] = rnd() * (yres-220) + 220.0;
	box[i][2] = 0.0;
    }
}

