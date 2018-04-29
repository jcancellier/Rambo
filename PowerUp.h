#ifndef POWERUP_H
#define POWERUP_H

class PowerUp{
    public:
	    float centerX;
	    float centerY;
	    float height;
	    float width;
        int spriteSheetIndex;
        int frame;
        bool done;
        float velocityX;
        float velocityY;
        // struct timespec animationTime;
		// float animationSpeedFactor;
    
        PowerUp(float, float, float, float);
        void draw();
};

#endif