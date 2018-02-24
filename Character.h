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
	    float health;
        int spriteSheetIndex;
        float velocityX;
        float velocityY;

	    Character(int);

	    //Accessors
	    float getCenterX() const;
	    float getCenterY() const;
	    float getHeight() const;
	    float getWidth() const;
	    int getFrame() const;
	    bool isFlipped() const;
	    float getHealth() const;

	    //Mutators
	    void setCenterX(float x);
	    void setCenterY(float y);
	    void setHeight(float h);
	    void setWidth(float w);
	    void setFrame(int f);
	    void setFlipped(bool f);
	    void setHealth(float h);

        //Other
        void draw();
};

#endif
