/*typedef double Vec[3];

class Bullet {
public:
	Vec pos;
	Vec vel;
	float color[3];
	struct timespec time;
public:
	Bullet() { }
};

void kuljitS_physics(){

    /////////////////////////////////////////////////////////
    //update bullets
    /////////////////////////////////////////////////////////
    struct timespec bt;
    clock_gettime(CLOCK_REALTIME, &bt);
    int i=0;
    while (i < g.nbullets) {
	Bullet *b = &g.barr[i];
	//How long has bullet been alive?
	double ts = timers.timeDiff(&b->time, &bt);
	if (ts > 2.5) {
	    //time to delete the bullet.
	    memcpy(&g.barr[i], &g.barr[g.nbullets-1],
		    sizeof(Bullet));
	    g.nbullets--;
	    //do not increment i.
	    continue;
	}
	//move the bullet
	b->pos[0] += b->vel[0];
	b->pos[1] += b->vel[1];
	//Check for collision with window edges
	if (b->pos[0] < 0.0 ||
		b->pos[0] > (float)gl.xres ||
		b->pos[1] < 0.0 ||
		b->pos[1] > (float)gl.yres){
	    memcpy(&g.barr[i], &g.barr[g.nbullets-1], sizeof(Bullet));
	    g.nbullets--;	
	} 
	i++;
    }


    //////////////////////////////////////////////////////////
    //check keys for space press to create bullet
    //////////////////////////////////////////////////////////




}

*/
