#ifndef BULLET_H
#define BULLET_H

class Bullet {

    public: 

	Vec pos;
	Vec vel; 
	float color[3];
	struct timespec time;
	
	void draw();
	~Bullet();
	Bullet(); 
};

#endif
	
	
