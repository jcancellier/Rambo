#include "HitBox.h"

#ifndef CHARACTER_H
#define CHARACTER_H
//cx and cy in walk.cpp
class Character{
    public:
	    float centerX;
	    float centerY;
	    float height;
	    float width;
	    int frame;
	    bool flipped;
        bool jumping;
	    float health;
        int spriteSheetIndex;
        float velocityX;
        float velocityY;
		HitBox *hitBox;
      
	    Character(int);

	    //Accessors
	    float getCenterX() const;
	    float getCenterY() const;
	    float getHeight() const;
	    float getWidth() const;
	    int getFrame() const;
	    bool isFlipped() const;
		bool isJumping() const;
	    float getHealth() const;
		int getSpriteSheetIndex() const;
		float getVelocityX() const;
		float getVelocityY() const;

	    //Mutators
	    void setCenterX(float x);
	    void setCenterY(float y);
	    void setHeight(float h);
	    void setWidth(float w);
	    void setFrame(int f);
	    void setFlipped(bool f);
		void setJumping(bool j);
	    void setHealth(float h);
		void setSpriteSheetIndex(int ssIdx);
		void setVelocityX(float vx);
		void setVelocityY(float vy);
        
		//Other
        void draw();
		void drawOptimized();
		void update();
		~Character(){
			delete hitBox;
		}
};

#endif
