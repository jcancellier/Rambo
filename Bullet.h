#ifndef BULLET_H
#define BULLET_H

class Bullet {

    public: 

	float pos[3];
	float vel[3]; 
	float color[3];
	struct timespec time;
	
	~Bullet();
	Bullet(); 
};

#endif
	
	
