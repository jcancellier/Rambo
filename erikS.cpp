// Platform boxes class
// Father: CS God
// Author: Erik Soto
//
#include <GL/glx.h>

class Platform{

    class point{
	public: 
	    float x,y;


    };
  
    class color{
	public:	
	    float r,g,b;
    };



    private:
    point one,two,three,four;
    color set;

    public:
	int top;
	int left;
	int right;


    Platform(float xpos ,float ypos,float xpos2 ,float ypos2,float xpos3 ,float ypos3,float xpos4 ,float ypos4)
    {
	// set the ranges for physics
	top = greatest(ypos,ypos2,ypos3,ypos4);

	one.x = xpos;
	one.y = ypos;

	two.x = xpos2;
	two.y = ypos2;

	three.x = xpos3;
	three.y = ypos3;

	four.x = xpos4;
	four.y = ypos4;
    }

    void drawPlatform()
    {
	glBegin(GL_QUADS);
	glColor3f(set.r,set.g,set.b);
	glVertex2i(one.x,	one.y);
	glVertex2i(two.x,	two.y);
	glColor3f(set.r,set.g,set.b);
	glVertex2i(three.x,	three.y);
	glVertex2i(four.x,	four.y);

	glEnd();
    }
    void setColor(float r, float g, float b)
    {
	set.r =r;
	set.g =g;
	set.b = b;


    }
    float greatest(float one,float two,float three,float four)
    {
	float g= greatest( one,two);
	float b= greatest(three,four);
	return greatest(g,b);

    }
    float greatest(float one,float two)
    {
	if(one < two)
	{
	    return two;
	}
	else return one;

    }






};

