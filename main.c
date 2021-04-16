// -----------------------------------------------------------------------------
// C-Skeleton to be used with HAM Library from www.ngine.de
// -----------------------------------------------------------------------------
//#include "numbers.h"
//#include "gba.h"
//#include "time.h"


int x, y, x2, y2, y3, y_init, dt, lvl = 0, v = 0, N;
int dir = 4;
int timer, activated1 = 0;
int map_flag = 0, s_level = 1; 
int flag = 0;
#include "mygbalib.h"

void clearSprites (void)
{
// The purpose of this fucntion is to clear all the sprites that is drawn previously, so that new sprites/ new level map can be drawn
	int j; 						         // This function is only does not rely on any other function that has been defines so a local variable is used instead
	for(j=0;j<128;j++){		         // This for loop cycle through sprite of N value 0-128 ( cause that's the maximum number of sprites to be drawn  in the screen)
		drawSprite(10,j,240,160);      // This for loop will make sure that all the available sprites will be drawn outside of the gba screen             
		}
} 

void Handler(void)
{
    REG_IME = 0x00; // Stop all other interrupt handling, while we handle this current one
    
    if ((REG_IF & INT_TIMER0) == INT_TIMER0) // TODO: replace XXX with the specific interrupt you are handling
    {
        // TODO: Handle timer interrupt here
	     dt += 1;
         checkbutton();
         jump();
         check_flags(); //Placeholder here as there needs to be an initial flag check
         x = x + x2;
         y = y + y2;
         x2 = 0; 
         y2 = 0;
    }
    
    REG_IF = REG_IF; // Update interrupt table, to confirm we have handled this interrupt
    
    REG_IME = 0x01;  // Re-enable interrupt handling
}

void jump(void) 
{
    if (v!=0)
    {
        y3 = v*dt - dt*dt;
        y3 = -y3/10;
        y = y_init + y3;
        if (dt > 25) 
        {
            dt = 0;
            v = 0;
        }

    }

}
void init_pos(void) //To set the initial position of the sprite
{
	clearSprites();
    x = 0;
	y = 144; //to input starting location
    dir = A_R_NF; //Start with Santa facing right
}

void check_flags()
{
    if(lvl == 1)
    {
        map_flag = s_level;
    } 

}
/*void move(void){ //initial iteration to test movement
    clearSprites();

    while (activated1 == 0) {
    drawSprite(dir, 0, x, y);
   
    }
}*/

void sample_map()
{
    N = 7;
    clearSprites();
    drawSprite(MIL_FAL,10,2,y);
    x = 16;
    y = 32;
    drawSprite(7,11,x*4,y);
    drawSprite(8,12,x*5,y);
    //drawSprite(6,N++,x*6,y);

    init_pos();
}

void sample_level() 
{
    sample_map();
    while (flag==0)
    {
        drawSprite(dir,0,x,y);
        check_flags();
    }
}




// -----------------------------------------------------------------------------
// Project Entry Point
// -----------------------------------------------------------------------------
int main(void)
{
	int activated = 0;
    // Set Mode 2
    *(unsigned short *) 0x4000000 = 0x40 | 0x2 | 0x1000;
	
	 fillPalette(); //stores all the rgb colours from sprite.h
	 fillSprites(); //stores all the sprites from sprite.h (This replaces the lines from CA2, see session 1)
  

    // Set Handler Function for interrupts and enable selected interrupts
    REG_INT = (int)&Handler;
    REG_IE = INT_TIMER0;				// TODO: complete this line to choose which timer interrupts to enable
    REG_IME = 0x1;		// Enable interrupt handling

    // Set Timer Mode (fill that section and replace TMX with selected timer number)
    REG_TM0D =	63350;		// TODO: complete this line to set timer initial value
    REG_TM0CNT =	TIMER_FREQUENCY_256 | TIMER_INTERRUPTS | TIMER_ENABLE;	// TODO: complete this line to set timer frequency and enable timer
    
    activated = 1;
    /*while (activated == 1) { //as long as activated, look for the timer values and do accordingly

    switch (timer)
    {
    case 0:
        init_pos();
        break;
    case 1:
        move();
    } 
}*/ 
while(map_flag<5)
{
    if (map_flag == s_level) 
    {
        sample_level();
    }

}

    while(1);

	return 0;
}

