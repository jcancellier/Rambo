#include<X11/keysym.h>
#include "Global.h"
#include "Timers.h"
#include "SpriteSheet.h"
#include "Character.h"

extern int flipped;
extern float cx;
extern Timers timers;
extern Global g;
extern int keys[];
extern Character rambo;
extern const float gravity;

#define JUMP_STRENGTH 5

void kuljitS_physics() 
{
	//check for a jump
	if(keys[XK_a]){
		rambo.setCenterY(rambo.getCenterY()+JUMP_STRENGTH);
		//Uncomment below when rambo get a velocity
		//rambo.setVelocityY(JUMP_STRENGTH);
	}

	if(rambo.getCenterY() > 200){
		rambo.setCenterY(rambo.getCenterY() + -2.0f);
	}
	//apply gravity
	/*uncomment when rambo gets a velocity
	if(rambo.getCenterY() > 200){
		rambo.setVelocityY(rambo.getVelocityY() + gravity;
	}
*/
	


	

		
}

