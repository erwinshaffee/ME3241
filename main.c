// -----------------------------------------------------------------------------
// C-Skeleton to be used with HAM Library from www.ngine.de
// -----------------------------------------------------------------------------
//#include "numbers.h"
//#include "gba.h"
//#include "time.h"


int x, y, x2, y2, y3, y_init, dt, lvl = 0, v = 0, N;
int dir = 4, santa = 0;
int timer, activated1 = 0;
int life_counter = 3;
int map_flag = 0, menu = 0, game = 1, game_win1 = 2, game_win2 = 3, game_win3 = 4, game_lose = 5; 
int flag = 0, win = 6, lose = 7;
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
void check_flags(void)
{
	int dx=16;	 // This local variable is created as it is only called in this function and nowhere else 

	// This checks for the win condition, which is to reach the position x = 192 and y = 10 (chimney sprite)
	if ( (x == 192) & (y == 10)) {
		flag = win;	// When the condition is met, the flag variable will store the value of win, which is 4
	}
	// This flag checks for which button is pressed in the menu page
	if(map_flag == menu) {
		if(lvl==1) // if button A is pressed the map_flag will change to lvlone, which will load the fucntion that codes for level one
		{
			map_flag = game; 	// The map flag will change to lvlone, which will prompt the code load level one map in the main code 
			flag = win;		// When the condition is met, the flag variable will store the value of win, this is need to exit the level loop
		} 
	}
	if(map_flag == game_lose || map_flag == game_win1 || map_flag == game_win2 || map_flag == game_win3) {
		if(lvl==1) // if button A is pressed the map_flag will change to lvlone, which will load the fucntion that codes for level one
		{
			map_flag = menu; 	// The map flag will change to lvlone, which will prompt the code load level one map in the main code 
			flag = win;		// When the condition is met, the flag variable will store the value of win, this is need to exit the level loop
		} 
	}
	// This flag checks if the enemy comes into contact with Santa 
	if ((enemy1_y == y )|(enemy2_y ==y)) {					// This condition is use to check the y co-ordinate of the two viruses and the doctor																	// If the viruses and the doctor is on the same level/y-coordinate, the following if statements will check if the doctor and virus will come into contact
		if( x > enemy_x) {											// This if statement tracks case 1 of the interaction between the virus and the doctor: which is when the doctor is on the right of the virus									
			dx = x - enemy_x;										// in this case the difference between them is then the x-cordinate of the doctor minus the x coordinate of the virus
		}
		if( enemy_x > x) {											// This if statement tracks case 2 of the interaction between the virus and the doctor: which is when the doctor is on the left of the virus
			dx = enemy_x - x;										// in this case the difference between them is then the x-cordinate of the virus minus the x coordinate of the doctor
		}  
		if( dx < 16) { 												// if the difference in x coordinate between the doctor and the virus is less than 16, it means the two sprite have come into contact
			life_counter--;				// this would mean that the doctor have died and hence lost one life/pill, pill_counter tracks the number of live the doctor has left 
			pos_init();						// because the doctor have lost a live, he would have to start from the beginng in the initial position stated in the pos_init function
			if(life_counter == 0) {		// when the pill_counter is down to 0 the charcater has no more lives left and it is game over for the player 
				flag = lose;				// hence the the flag variable will store the value of lose, which is just the integer 6 
			}
		}
	}
}

/*void move(void){ //initial iteration to test movement
    clearSprites();

    while (activated1 == 0) {
    drawSprite(dir, 0, x, y);
   
    }
}*/

void menu_map (void)
{
	// This function draws the map for the menu page 
	N = 7;								    	  	// because N is a gobal variable, it has to be re initialise everytime it is called is a new map function
	clearSprites();						   	// all the sprites that was drawn in previous level will be cleared using this function
	// THIS SECTION DRAWS "THE NIGHT BEFORE XMAS" //	
	y = 22;														//draws the following sprites the y coordinate, y = 32
	x = 100;														//draws the following sprites starting at the x coordinate, x = 50
	drawSprite( LETTER_S,N,x,y);	        				// some random line to get the code working, without this line the next drawSprite will not be drawn
	drawSprite( LETTER_T,N++,x,y);						//draws H at it's respective x and y coordinate
	drawSprite( LETTER_H,N++,x+10,y);						//draws E at it's respective x and y coordinate	
	drawSprite( LETTER_E,N++,x+18,y);					//draws A at it's respective x and y coordinate

	y=36;
	x=92;
	drawSprite( LETTER_N,N++,x,y);					//draws L at it's respective x and y coordinate
	drawSprite( LETTER_I,N++,x+8,y);					//draws T at it's respective x and y coordinate
	drawSprite( LETTER_G,N++,x+15,y);					//draws A at it's respective x and y coordinate
	drawSprite( LETTER_H,N++,x+26,y);					//draws L at it's respective x and y coordinate
	drawSprite( LETTER_T,N++,x+36,y);					//draws T at it's respective x and y coordinate
	
	y = 50;
	x = 86;
	drawSprite( LETTER_B,N++,x,y);					//draws H at it's respective x and y coordinate
	drawSprite( LETTER_E,N++,x+8,y); 					//draws E at it's respective x and y coordinate
	drawSprite( LETTER_F,N++,x+18,y);					//draws W at it's respective x and y coordinate
	drawSprite( LETTER_O,N++,x+28,y);					//draws O at it's respective x and y coordinate
	drawSprite( LETTER_R,N++,x+37,y);					//draws R at it's respective x and y coordinate
	drawSprite( LETTER_E,N++,x+47,y);					//draws L at it's respective x and y coordinate
	
	y=68;
	x=92;
	drawSprite( MR_S_E_R,N++,x-20,y);					//draws T at it's respective x and y coordinate
	drawSprite( LETTER_XR,N++,x,y);					//draws D at it's respective x and y coordinate
	drawSprite( LETTER_M,N++,x+12,y);
	drawSprite( LETTER_AG,N++,x+25,y);
	drawSprite( LETTER_SB,N++,x+36,y);
	drawSprite( PREZ,N++,x+58,y-4);					//draws T at it's respective x and y coordinate
	
	// THIS SECTION ADDS SOME DESIGN//	
	y = 119;
	x = 0;
	drawSprite( PLATFORM_M,N++,x,y);					//draws H at it's respective x and y coordinate
	drawSprite( PLATFORM_M,N++,x+16,y);
	drawSprite( PLATFORM_M,N++,x+32,y);
	drawSprite( PLATFORM_M,N++,x+48,y);
	drawSprite( PLATFORM_M,N++,x+64,y);	        				// some random line to get the code working, without this line the next drawSprite will not be drawn
	drawSprite( PLATFORM_M,N++,x+80,y);
	drawSprite( PLATFORM_M,N++,x+96,y);
	drawSprite( PLATFORM_M,N++,x+112,y);
	drawSprite( PLATFORM_M,N++,x+128,y);
	drawSprite( PLATFORM_M,N++,x+144,y);
	drawSprite( PLATFORM_M,N++,x+160,y);
	drawSprite( PLATFORM_M,N++,x+176,y);
	drawSprite( PLATFORM_M,N++,x+192,y);
	drawSprite( PLATFORM_M,N++,x+208,y);
	drawSprite( PLATFORM_M,N++,x+224,y);

	// THIS SECTION DRAWS "PRESS START" //
	y = 120;														//draws the following sprites the y coordinate, y = 96
	x = 68;														//draws the following sprites starting at the x coordinate, x = 44
	drawSprite( LETTER_P,N++,x,y);					//draws P at it's respective x and y coordinate
	drawSprite( LETTER_R,N++,x+8,y);					//draws R at it's respective x and y coordinate
	drawSprite( LETTER_E,N++,x+17,y);					//draws E at it's respective x and y coordinate
	drawSprite( LETTER_S,N++,x+25,y);					//draws S at it's respective x and y coordinate
	drawSprite( LETTER_S,N++,x+33,y);					//draws S at it's respective x and y coordinate
	drawSprite( LETTER_S,N++,x+53,y);					//draws A at it's respective x and y coordinate
	drawSprite( LETTER_T,N++,x+61,y);					//draws A at it's respective x and y coordinate
	drawSprite( LETTER_A,N++,x+69,y);					//draws A at it's respective x and y coordinate
	drawSprite( LETTER_R,N++,x+77,y);					//draws A at it's respective x and y coordinate
	drawSprite( LETTER_T,N++,x+85,y);					//draws A at it's respective x and y coordinate
}

void game_map(void)
{
	// This function draws the necessary sprites for the game map 
	N=7;													  	// because N is a gobal variable, it has to be re initialise everytime it is called is a new map function
	clearSprites();                      			// clear all the sprites that is drawn previously 
	drawSprite(CHIMNEY,N,2,y);              	 	// some random line to get the code working
	// THIS SECTION DRAWS THE CHIMNEY IN FINAL POSITION //
	x = 16;													//x is set as 16 so that I can draw the sprites by the grid positions instead of actualy pixel number
	y = 10;													//draws the following sprites the y coordinate, y = 16
	drawSprite(CHIMNEY,N++,x*12,y);					//draws vaccine sprite at it's respective x and y coordinate
	// THIS SECTION DRAWS THE PLATFORMS AND GIFTS //
	x = 16;													//x is set as 16 so that I can draw the sprites by the grid positions instead of actualy pixel number
	y = 30;													//draws the following sprites the y coordinate, y = 32
	drawSprite(PLATFORM8_L,N++,x*8,y);				//draws PLATFORM_M with ladder sprite at it's respective x and y coordinate
	drawSprite(PLATFORM8_L,N++,x*9,y);
	drawSprite(PLATFORM8_L,N++,x*10,y);
	drawSprite(PLATFORM8_R,N++,x*11,y);					//draws PLATFORM_M sprite at it's respective x and y coordinate
	drawSprite(PLATFORM8_R,N++,x*12,y);					//draws PLATFORM_M sprite at it's respective x and y coordinate
	x = 16;													//x is set as 16 so that I can draw the sprites by the grid positions instead of actualy pixel number
	y = 28;													//draws the following sprites the y coordinate, y = 48
	drawSprite(PREZ,N++,x*3,y);						//draws ladder sprite at it's respective x and y coordinate
	drawSprite(PREZ,N++,x*6,y);					//draws ladder sprite at it's respective x and y coordinate
	x = 16;													//x is set as 16 so that I can draw the sprites by the grid positions instead of actualy pixel number
	y = 64;													//draws the following sprites the y coordinate, y = 48
	drawSprite(PLATFORM8_L,N++,x*1,y);						//draws ladder sprite at it's respective x and y coordinate
	drawSprite(PLATFORM8_L,N++,x*2,y);
	drawSprite(PLATFORM8_L,N++,x*3,y);
	drawSprite(PLATFORM8_L,N++,x*4,y);
	drawSprite(PLATFORM8_L,N++,x*5,y);		
	drawSprite(PLATFORM8_R,N++,x*6,y);					//draws ladder sprite at it's respective x and y coordinate
	x = 16;													//draws the following sprites starting at the x coordinate, x = 16
	y = 70;													//draws the following sprites the y coordinate, y = 96
	drawSprite(PREZ,N++,x*8,y);					//draws PLATFORM_M sprite at it's respective x and y coordinate
	drawSprite(PREZ,N++,x*11,y);					//draws PLATFORM_M sprite at it's respective x and y coordinate
	x = 16;													//x is set as 16 so that I can draw the sprites by the grid positions instead of actualy pixel number
	y = 110;													//draws the following sprites the y coordinate, y = 96
	drawSprite(PLATFORM8_L,N++,x*8,y);					//draws PLATFORM_M sprite at it's respective x and y coordinate
	drawSprite(PLATFORM8_L,N++,x*9,y);					//draws PLATFORM_M sprite at it's respective x and y coordinate
	drawSprite(PLATFORM8_R,N++,x*10,y);					//draws PLATFORM_M sprite at it's respective x and y coordinate
	drawSprite(PLATFORM8_R,N++,x*11,y);					//draws PLATFORM_M sprite at it's respective x and y coordinate
	drawSprite(PLATFORM8_R,N++,x*12,y);
	x = 16;													//x is set as 16 so that I can draw the sprites by the grid positions instead of actualy pixel number
	y = 120;													//draws the following sprites the y coordinate, y = 128
	drawSprite(PREZ,N++,x*2,y);					//draws PLATFORM_M sprite at it's respective x and y coordinate
	drawSprite(PREZ,N++,x*6,y);					//draws PLATFORM_M sprite at it's respective x and y coordinate

	pos_init();													// reset the initial position of the doctor after the map is drawn 
}

void gamewin_map1(void)
{
	// This function draws the map for the game over page 
	N=7;														// because N is a gobal variable, it has to be re initialise everytime it is called is a new map function
	clearSprites();             				      // clear all the sprites that is drawn previously 
	drawSprite(PREZ,N,2,y); 					   // some random line to get the code working

	// THIS SECTION DRAWS "LEVEL COMPLETE" //	
	y = 22;													//draws the following sprites at the y coordinate, y = 48
	x = 60;													//x is set as 16 so that I can draw the sprites by the grid positions instead of actualy pixel number
	drawSprite( PREZ,N++,x-13,y-4);
	drawSprite( LETTER_L,N++,x,y);					//draws E at it's respective x and y coordinate
	drawSprite( LETTER_E,N++,x+8,y);					//draws E at it's respective x and y coordinate
	drawSprite( LETTER_V,N++,x+16,y);					//draws E at it's respective x and y coordinate
	drawSprite( LETTER_E,N++,x+24,y);				//draws E at it's respective x and y coordinate
	drawSprite( LETTER_L,N++,x+32,y);													//draws the following sprites at the y coordinate, y = 64
													//x is set as 16 so that I can draw the sprites by the grid positions instead of actualy pixel number
	drawSprite( LETTER_C,N++,x+52,y);					//draws E at it's respective x and y coordinate
	drawSprite( LETTER_O,N++,x+60,y);					//draws E at it's respective x and y coordinate
	drawSprite( LETTER_M,N++,x+68,y);					//draws E at it's respective x and y coordinate
	drawSprite( LETTER_P,N++,x+76,y);				//draws E at it's respective x and y coordinate
	drawSprite( LETTER_L,N++,x+84,y);					//draws E at it's respective x and y coordinate
	drawSprite( LETTER_E,N++,x+92,y);					//draws E at it's respective x and y coordinate
	drawSprite( LETTER_T,N++,x+100,y);					//draws E at it's respective x and y coordinate
	drawSprite( LETTER_E,N++,x+108,y);				//draws E at it's respective x and y coordinate
	drawSprite( PREZ,N++,x+128,y-4);
	
	y = 21;
	x = 0;
	drawSprite( PLATFORM_M,N++,x,y);					//draws H at it's respective x and y coordinate
	drawSprite( PLATFORM_M,N++,x+16,y);
	drawSprite( PLATFORM_M,N++,x+32,y);
	drawSprite( PLATFORM_M,N++,x+48,y);
	drawSprite( PLATFORM_M,N++,x+64,y);	        				// some random line to get the code working, without this line the next drawSprite will not be drawn
	drawSprite( PLATFORM_M,N++,x+80,y);
	drawSprite( PLATFORM_M,N++,x+96,y);
	drawSprite( PLATFORM_M,N++,x+112,y);
	drawSprite( PLATFORM_M,N++,x+128,y);
	drawSprite( PLATFORM_M,N++,x+144,y);
	drawSprite( PLATFORM_M,N++,x+160,y);
	drawSprite( PLATFORM_M,N++,x+176,y);
	drawSprite( PLATFORM_M,N++,x+192,y);
	drawSprite( PLATFORM_M,N++,x+208,y);
	drawSprite( PLATFORM_M,N++,x+224,y);

	// THIS SECTION DRAWS "SOMEONE CALL THE POLICE" //	
	y=85;
	x=70;
	drawSprite( DR_RIGHT,N++,x-30,y); //DOOR
	drawSprite( DR_RIGHT,N++,x,y);	//UNDRESSED SANTA
	drawSprite( DR_RIGHT,N++,x+100,y);	//SANTA WIFE

	y = 110;													//draws the following sprites at the y coordinate, y = 96
	x = 120;												   //draws the following sprites the x coordinate,starting from  x = 112
	drawSprite( LETTER_S,N++,x,y);				//draws E at it's respective x and y coordinate
	drawSprite( LETTER_O,N++,x+8,y);				//draws E at it's respective x and y coordinate
	drawSprite( LETTER_M,N++,x+16,y);				//draws E at it's respective x and y coordinate
	drawSprite( LETTER_E,N++,x+24,y);				//draws E at it's respective x and y coordinate
	drawSprite( LETTER_O,N++,x+34,y);					//draws E at it's respective x and y coordinate
	drawSprite( LETTER_N,N++,x+42,y);					//draws E at it's respective x and y coordinate
	drawSprite( LETTER_E,N++,x+50,y);				//draws E at it's respective x and y coordinate
	
	drawSprite( LETTER_C,N++,x+64,y);				//draws E at it's respective x and y coordinate
	drawSprite( LETTER_A,N++,x+72,y);				//draws E at it's respective x and y coordinate
	drawSprite( LETTER_L,N++,x+80,y);				//draws E at it's respective x and y coordinate
	drawSprite( LETTER_L,N++,x+88,y);				//draws E at it's respective x and y coordinate
	
	y = 122;													//draws the following sprites at the y coordinate, y = 96
	x = 130;
	drawSprite( LETTER_T,N++,x-2,y);				//draws E at it's respective x and y coordinate		
	drawSprite( LETTER_H,N++,x+8,y);				//draws E at it's respective x and y coordinate
	drawSprite( LETTER_E,N++,x+16,y);				//draws E at it's respective x and y coordinate
	
	drawSprite( LETTER_P,N++,x+30,y);					//draws E at it's respective x and y coordinate
	drawSprite( LETTER_O,N++,x+38,y);					//draws E at it's respective x and y coordinate
	drawSprite( LETTER_L,N++,x+44,y);				//draws E at it's respective x and y coordinate
	drawSprite( LETTER_I,N++,x+52,y);				//draws E at it's respective x and y coordinate
	drawSprite( LETTER_C,N++,x+60,y);				//draws E at it's respective x and y coordinate
	drawSprite( LETTER_E,N++,x+68,y);				//draws E at it's respective x and y coordinate
}  

void gamewin_map2(void)
{
	// This function draws the map for the game over page 
	N=7;														// because N is a gobal variable, it has to be re initialise everytime it is called is a new map function
	clearSprites();             				      // clear all the sprites that is drawn previously 
	drawSprite(PREZ,N,2,y); 					   // some random line to get the code working
	//THIS SECTION DRAWS THE "LEVEL COMPLETE" //	
	y = 22;													//draws the following sprites at the y coordinate, y = 48
	x = 60;													//x is set as 16 so that I can draw the sprites by the grid positions instead of actualy pixel number
	drawSprite( PREZ,N++,x-13,y-4);
	drawSprite( LETTER_L,N++,x,y);					//draws E at it's respective x and y coordinate
	drawSprite( LETTER_E,N++,x+8,y);					//draws E at it's respective x and y coordinate
	drawSprite( LETTER_V,N++,x+16,y);					//draws E at it's respective x and y coordinate
	drawSprite( LETTER_E,N++,x+24,y);				//draws E at it's respective x and y coordinate
	drawSprite( LETTER_L,N++,x+32,y);													//draws the following sprites at the y coordinate, y = 64
													//x is set as 16 so that I can draw the sprites by the grid positions instead of actualy pixel number
	drawSprite( LETTER_C,N++,x+52,y);					//draws E at it's respective x and y coordinate
	drawSprite( LETTER_O,N++,x+60,y);					//draws E at it's respective x and y coordinate
	drawSprite( LETTER_M,N++,x+68,y);					//draws E at it's respective x and y coordinate
	drawSprite( LETTER_P,N++,x+76,y);				//draws E at it's respective x and y coordinate
	drawSprite( LETTER_L,N++,x+84,y);					//draws E at it's respective x and y coordinate
	drawSprite( LETTER_E,N++,x+92,y);					//draws E at it's respective x and y coordinate
	drawSprite( LETTER_T,N++,x+100,y);					//draws E at it's respective x and y coordinate
	drawSprite( LETTER_E,N++,x+108,y);				//draws E at it's respective x and y coordinate
	drawSprite( PREZ,N++,x+128,y-4);
	
	y = 21;
	x = 0;
	drawSprite( PLATFORM_M,N++,x,y);					//draws H at it's respective x and y coordinate
	drawSprite( PLATFORM_M,N++,x+16,y);
	drawSprite( PLATFORM_M,N++,x+32,y);
	drawSprite( PLATFORM_M,N++,x+48,y);
	drawSprite( PLATFORM_M,N++,x+64,y);	        				// some random line to get the code working, without this line the next drawSprite will not be drawn
	drawSprite( PLATFORM_M,N++,x+80,y);
	drawSprite( PLATFORM_M,N++,x+96,y);
	drawSprite( PLATFORM_M,N++,x+112,y);
	drawSprite( PLATFORM_M,N++,x+128,y);
	drawSprite( PLATFORM_M,N++,x+144,y);
	drawSprite( PLATFORM_M,N++,x+160,y);
	drawSprite( PLATFORM_M,N++,x+176,y);
	drawSprite( PLATFORM_M,N++,x+192,y);
	drawSprite( PLATFORM_M,N++,x+208,y);
	drawSprite( PLATFORM_M,N++,x+224,y);
	// THIS SECTION DRAWS "YOU ARE NOT SANTA" //	
	y=85;
	x=70;
	drawSprite( CHIMNEY,N++,x-30,y); //DOOR
	drawSprite( DR_RIGHT,N++,x,y);	//UNDRESSED SANTA
	drawSprite( DR_RIGHT,N++,x+100,y);	//SANTA WIFE

	y = 110;													//draws the following sprites at the y coordinate, y = 96
	x = 146;												   //draws the following sprites the x coordinate,starting from  x = 112
	drawSprite( LETTER_Y,N++,x,y);				//draws E at it's respective x and y coordinate
	drawSprite( LETTER_O,N++,x+8,y);				//draws E at it's respective x and y coordinate
	drawSprite( LETTER_U,N++,x+16,y);				//draws E at it's respective x and y coordinate
	drawSprite( LETTER_A,N++,x+30,y);				//draws E at it's respective x and y coordinate
	drawSprite( LETTER_R,N++,x+38,y);					//draws E at it's respective x and y coordinate
	drawSprite( LETTER_E,N++,x+46,y);					//draws E at it's respective x and y coordinate
	
	y = 122;													//draws the following sprites at the y coordinate, y = 96
	x = 140;
	drawSprite( LETTER_N,N++,x-2,y);				//draws E at it's respective x and y coordinate		
	drawSprite( LETTER_O,N++,x+8,y);				//draws E at it's respective x and y coordinate
	drawSprite( LETTER_T,N++,x+16,y);				//draws E at it's respective x and y coordinate
	drawSprite( LETTER_S,N++,x+30,y);					//draws E at it's respective x and y coordinate
	drawSprite( LETTER_A,N++,x+38,y);					//draws E at it's respective x and y coordinate
	drawSprite( LETTER_N,N++,x+46,y);				//draws E at it's respective x and y coordinate
	drawSprite( LETTER_T,N++,x+54,y);				//draws E at it's respective x and y coordinate
	drawSprite( LETTER_A,N++,x+62,y);				//draws E at it's respective x and y coordinate
}

void gamewin_map3(void)
{
	// This function draws the map for the game over page 
	N=7;														// because N is a gobal variable, it has to be re initialise everytime it is called is a new map function
	clearSprites();             				      // clear all the sprites that is drawn previously 
	drawSprite(PREZ,N,2,y); 					   // some random line to get the code working
	// THIS SECTION DRAWS "LEVEL COMPLETE" //
	y = 22;													//draws the following sprites at the y coordinate, y = 48
	x = 60;													//x is set as 16 so that I can draw the sprites by the grid positions instead of actualy pixel number
	drawSprite( PREZ,N++,x-13,y-4);
	drawSprite( LETTER_L,N++,x,y);					//draws E at it's respective x and y coordinate
	drawSprite( LETTER_E,N++,x+8,y);					//draws E at it's respective x and y coordinate
	drawSprite( LETTER_V,N++,x+16,y);					//draws E at it's respective x and y coordinate
	drawSprite( LETTER_E,N++,x+24,y);				//draws E at it's respective x and y coordinate
	drawSprite( LETTER_L,N++,x+32,y);												//draws the following sprites at the y coordinate, y = 64
													//x is set as 16 so that I can draw the sprites by the grid positions instead of actualy pixel number
	drawSprite( LETTER_C,N++,x+52,y);					//draws E at it's respective x and y coordinate
	drawSprite( LETTER_O,N++,x+60,y);					//draws E at it's respective x and y coordinate
	drawSprite( LETTER_M,N++,x+68,y);					//draws E at it's respective x and y coordinate
	drawSprite( LETTER_P,N++,x+76,y);				//draws E at it's respective x and y coordinate
	drawSprite( LETTER_L,N++,x+84,y);					//draws E at it's respective x and y coordinate
	drawSprite( LETTER_E,N++,x+92,y);					//draws E at it's respective x and y coordinate
	drawSprite( LETTER_T,N++,x+100,y);					//draws E at it's respective x and y coordinate
	drawSprite( LETTER_E,N++,x+108,y);				//draws E at it's respective x and y coordinate
	drawSprite( PREZ,N++,x+128,y-4);
	
	y = 21;
	x = 0;
	drawSprite( PLATFORM_M,N++,x,y);					//draws H at it's respective x and y coordinate
	drawSprite( PLATFORM_M,N++,x+16,y);
	drawSprite( PLATFORM_M,N++,x+32,y);
	drawSprite( PLATFORM_M,N++,x+48,y);
	drawSprite( PLATFORM_M,N++,x+64,y);	        				// some random line to get the code working, without this line the next drawSprite will not be drawn
	drawSprite( PLATFORM_M,N++,x+80,y);
	drawSprite( PLATFORM_M,N++,x+96,y);
	drawSprite( PLATFORM_M,N++,x+112,y);
	drawSprite( PLATFORM_M,N++,x+128,y);
	drawSprite( PLATFORM_M,N++,x+144,y);
	drawSprite( PLATFORM_M,N++,x+160,y);
	drawSprite( PLATFORM_M,N++,x+176,y);
	drawSprite( PLATFORM_M,N++,x+192,y);
	drawSprite( PLATFORM_M,N++,x+208,y);
	drawSprite( PLATFORM_M,N++,x+224,y);
	// THIS SECTION DRAWS "HO HO HO MERRY XMAS" //	
	y=85;
	x=70;
	drawSprite( DR_RIGHT,N++,x-30,y); //DOOR
	drawSprite( DR_RIGHT,N++,x,y);	//UNDRESSED SANTA
	drawSprite( DR_LEFT,N++,x+20,y);
	drawSprite( DR_RIGHT,N++,x+100,y);	//SANTA WIFE

	y = 110;													//draws the following sprites at the y coordinate, y = 96
	x = 50;												   //draws the following sprites the x coordinate,starting from  x = 112
	
	drawSprite( LETTER_H,N++,x,y);				//draws E at it's respective x and y coordinate
	drawSprite( LETTER_O,N++,x+8,y);				//draws E at it's respective x and y coordinate
	drawSprite( LETTER_H,N++,x+20,y);				//draws E at it's respective x and y coordinate
	drawSprite( LETTER_O,N++,x+28,y);				//draws E at it's respective x and y coordinate
	drawSprite( LETTER_H,N++,x+40,y);					//draws E at it's respective x and y coordinate
	drawSprite( LETTER_O,N++,x+48,y);					//draws E at it's respective x and y coordinate
	
	y = 122;													//draws the following sprites at the y coordinate, y = 96
	x = 50;
	drawSprite( LETTER_MW,N++,x,y);				//draws E at it's respective x and y coordinate
	drawSprite( LETTER_E,N++,x+8,y);				//draws E at it's respective x and y coordinate
	drawSprite( LETTER_R,N++,x+16,y);				//draws E at it's respective x and y coordinate
	drawSprite( LETTER_R,N++,x+24,y);				//draws E at it's respective x and y coordinate
	drawSprite( LETTER_Y,N++,x+32,y);					//draws E at it's respective x and y coordinate
	drawSprite( LETTER_X,N++,x+48,y);					//draws E at it's respective x and y coordinate
	drawSprite( LETTER_M,N++,x+56,y);				//draws E at it's respective x and y coordinate
	drawSprite( LETTER_A,N++,x+66,y);				//draws E at it's respective x and y coordinate
	drawSprite( LETTER_S,N++,x+74,y);				//draws E at it's respective x and y coordinate
}  

void gamelose_map(void)
{
	// This function draws the map for the game over page 
	N=7;														// because N is a gobal variable, it has to be re initialise everytime it is called is a new map function
	clearSprites();             				      // clear all the sprites that is drawn previously 
	drawSprite(PREZ,N,2,y); 					   // some random line to get the code working

	// THIS SECTION DRAWS "GAME OVER" //	
	y = 22;													//draws the following sprites at the y coordinate, y = 48
	x = 81;													//x is set as 16 so that I can draw the sprites by the grid positions instead of actualy pixel number
	drawSprite( PREZ,N++,x-20,y-4);
	drawSprite( LETTER_G,N++,x,y);					//draws E at it's respective x and y coordinate
	drawSprite( LETTER_A,N++,x+8,y);					//draws E at it's respective x and y coordinate
	drawSprite( LETTER_M,N++,x+16,y);					//draws E at it's respective x and y coordinate
	drawSprite( LETTER_E,N++,x+24,y);				//draws E at it's respective x and y coordinate
													
	drawSprite( LETTER_O,N++,x+42,y);					//draws E at it's respective x and y coordinate
	drawSprite( LETTER_V,N++,x+50,y);					//draws E at it's respective x and y coordinate
	drawSprite( LETTER_E,N++,x+58,y);					//draws E at it's respective x and y coordinate
	drawSprite( LETTER_R,N++,x+68,y);				//draws E at it's respective x and y coordinate
	drawSprite( PREZ,N++,x+94,y-4);
	
	y = 21;
	x = 0;
	drawSprite( PLATFORM_M,N++,x,y);					//draws H at it's respective x and y coordinate
	drawSprite( PLATFORM_M,N++,x+16,y);
	drawSprite( PLATFORM_M,N++,x+32,y);
	drawSprite( PLATFORM_M,N++,x+48,y);
	drawSprite( PLATFORM_M,N++,x+64,y);	        				// some random line to get the code working, without this line the next drawSprite will not be drawn
	drawSprite( PLATFORM_M,N++,x+80,y);
	drawSprite( PLATFORM_M,N++,x+96,y);
	drawSprite( PLATFORM_M,N++,x+112,y);
	drawSprite( PLATFORM_M,N++,x+128,y);
	drawSprite( PLATFORM_M,N++,x+144,y);
	drawSprite( PLATFORM_M,N++,x+160,y);
	drawSprite( PLATFORM_M,N++,x+176,y);
	drawSprite( PLATFORM_M,N++,x+192,y);
	drawSprite( PLATFORM_M,N++,x+208,y);
	drawSprite( PLATFORM_M,N++,x+224,y);

	// THIS SECTION DRAWS "SANTA CAN DO BETTER TRY AGAIN"//	
	y=85;
	x=100;
	drawSprite( DR_RIGHT,N++,x-2,y);	//UNDRESSED SANTA
	drawSprite( DR_LEFT,N++,x+20,y);
	drawSprite( DR_RIGHT,N++,x+40,y);	//SANTA WIFE

	y = 110;													//draws the following sprites at the y coordinate, y = 96
	x = 44;												   //draws the following sprites the x coordinate,starting from  x = 112
	drawSprite( LETTER_S,N++,x,y);				//draws E at it's respective x and y coordinate
	drawSprite( LETTER_A,N++,x+8,y);				//draws E at it's respective x and y coordinate
	drawSprite( LETTER_N,N++,x+16,y);				//draws E at it's respective x and y coordinate
	drawSprite( LETTER_T,N++,x+24,y);				//draws E at it's respective x and y coordinate
	drawSprite( LETTER_A,N++,x+32,y);					//draws E at it's respective x and y coordinate
	
	drawSprite( LETTER_C,N++,x+48,y);					//draws E at it's respective x and y coordinate
	drawSprite( LETTER_A,N++,x+56,y);
	drawSprite( LETTER_N,N++,x+64,y);	

	drawSprite( LETTER_D,N++,x+78,y);
	drawSprite( LETTER_O,N++,x+86,y);

	drawSprite( LETTER_B,N++,x+100,y);
	drawSprite( LETTER_E,N++,x+108,y);
	drawSprite( LETTER_T,N++,x+116,y);
	drawSprite( LETTER_T,N++,x+124,y);
	drawSprite( LETTER_E,N++,x+132,y);
	drawSprite( LETTER_R,N++,x+140,y);
	
	y = 124;													//draws the following sprites at the y coordinate, y = 96
	x = 86;
	drawSprite( LETTER_T,N++,x,y);				//draws E at it's respective x and y coordinate
	drawSprite( LETTER_R,N++,x+8,y);				//draws E at it's respective x and y coordinate
	drawSprite( LETTER_Y,N++,x+16,y);				//draws E at it's respective x and y coordinate
	drawSprite( LETTER_A,N++,x+30,y);				//draws E at it's respective x and y coordinate
	drawSprite( LETTER_G,N++,x+38,y);					//draws E at it's respective x and y coordinate
	drawSprite( LETTER_A,N++,x+46,y);					//draws E at it's respective x and y coordinate
	drawSprite( LETTER_I,N++,x+54,y);				//draws E at it's respective x and y coordinate
	drawSprite( LETTER_N,N++,x+62,y);				//draws E at it's respective x and y coordinate
}  

void draw_lives(void)
{

// This fucntion will draw the correct number of lives that the character has left 

	if(life_counter == 3)
	{
		drawSprite(LIFE,1,0,5);     // Pill no. 1 is drawn at the top left hand corner of the screen
		drawSprite(LIFE,2,20,5);	  // Pill no. 2 id drawn on the right of pill no. 1
		drawSprite(LIFE,3,40,5);	  // and pill no. 3 is drawn on the right of pill no. 2
	}
	if(life_counter == 2)
	{
		drawSprite(LIFE,1,0,5);		// Pill no. 1 is drawn at the top left hand corner of the screen
		drawSprite(LIFE,2,20,5);		// Pill no. 2 id drawn on the right of pill no. 1
		drawSprite(LIFE,3,240,160);	// and pill no. 3 is drawn outside of the frame to emulate 2 lives left 
	}
	if(life_counter == 1)
	{
		drawSprite(LIFE,1,0,5);		// Pill no. 1 is drawn at the top left hand corner of the screen
		drawSprite(LIFE,2,240,160);	// Pill no. 2 is drawn outside of the frame 
		drawSprite(LIFE,3,240,160);	// and pill no. 3 is also drawn outside of the frame to emulate 1 lives left
	}
}

void menu(void)
{
	// This function consist of the loop and logic that runs the menu page 
	menu_map();								// The menu map will be drawn when the program first enters this function
	while(flag!=win) {						// The page will be stuck at menu page until the flag has been raised to  win 
		check_flags();						// The programme will be stuck in the loop until the flag has been changed to a win
	}
	lvl = 0;  								// The lvl variable has to be intialised to 0 so that the next time the player enters the menu page, the player can choose which level to play and not stick to what was chosen priviously
	flag = 0;								// After every level/map the flag have to be re-initialsed to zero so that the appropriate actions can take place at different map/level
}

void game(void)
{
	// This function consist of the loop and logic that runs the level one page
	counter = 0;							// This line will ensure that the counter starts counting once the player entire this stage and not when the player loads the entire .gba file
	game_map();						// This will load the level one map
	while(flag==0)							//	This is the start of the level one loop 
	{ 	 										// in this loop the programme will
		draw_lives();						// draw the relevant number of pills based on the pill_counter
		drawSprite(dir,0,x,y);  		// draw the doctor sprite based on it's x and y coordinate that is calculated in the handlr function
		check_flags(); 					// check for the winning or losing flag that will take the programme out of this level one loop
	}
	if(flag==win && santa == 1)
	{
		map_flag = game_win1;	
	}
	if(flag==win && santa == 2)
	{
		map_flag = game_win2;	
	}
	if(flag==win && santa == 3)
	{
		map_flag = game_win3;	
	}
	if(flag==lose)
	{
		map_flag = game_lose;					
	}
	life_counter=3;						// since pill_counter is also a global variable that will store the last state of the number of pills, it have to be initialise to the starting value to prepare for other levels
	flag = 0;						// After every level/map the flag have to be re-initialsed to zero so that the appropriate actions can take place at different map/level
}

void gameover(void)
{
	// This function consist of the loop and logic that runs the game over page
	counter = 0;									// This line will ensure that the counter starts counting once the player entire this stage and not when the player loads the entire .gba file
	gamelose_map();								// This line will load the gameover map
	while(flag!=win) {						// The page will be stuck at menu page until the flag has been raised to  win 
		check_flags();						// The programme will be stuck in the loop until the flag has been changed to a win
	}
	lvl = 0;  								// The lvl variable has to be intialised to 0 so that the next time the player enters the menu page, the player can choose which level to play and not stick to what was chosen priviously
	flag = 0;								// After every level/map the flag have to be re-initialsed to zero so that the appropriate actions can take place at different map/level
}

void gamewin1(void)
{
	// This function consist of the loop and logic that runs the winning page
	counter = 0;									// This line will ensure that the counter starts counting once the player entire this stage and not when the player loads the entire .gba file
	gamewin_map1();									// This line will load the gamewin map
	while(flag!=win) {						// The page will be stuck at menu page until the flag has been raised to  win 
		check_flags();						// The programme will be stuck in the loop until the flag has been changed to a win
	}
	lvl = 0;  								// The lvl variable has to be intialised to 0 so that the next time the player enters the menu page, the player can choose which level to play and not stick to what was chosen priviously
	flag = 0;
}

void gamewin2(void)
{
	// This function consist of the loop and logic that runs the winning page
	counter = 0;									// This line will ensure that the counter starts counting once the player entire this stage and not when the player loads the entire .gba file
	gamewin_map2();									// This line will load the gamewin map
	while(flag!=win) {						// The page will be stuck at menu page until the flag has been raised to  win 
		check_flags();						// The programme will be stuck in the loop until the flag has been changed to a win
	}
	lvl = 0;  								// The lvl variable has to be intialised to 0 so that the next time the player enters the menu page, the player can choose which level to play and not stick to what was chosen priviously
	flag = 0;
}

void gamewin3(void)
{
	// This function consist of the loop and logic that runs the winning page
	counter = 0;									// This line will ensure that the counter starts counting once the player entire this stage and not when the player loads the entire .gba file
	gamewin_map3();									// This line will load the gamewin map
	while(flag!=win) {						// The page will be stuck at menu page until the flag has been raised to  win 
		check_flags();						// The programme will be stuck in the loop until the flag has been changed to a win
	}
	lvl = 0;  								// The lvl variable has to be intialised to 0 so that the next time the player enters the menu page, the player can choose which level to play and not stick to what was chosen priviously
	flag = 0;
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
    REG_IE |= INT_TIMER0;				// TODO: complete this line to choose which timer interrupts to enable
    REG_IME = 0x1;		// Enable interrupt handling

    // Set Timer Mode (fill that section and replace TMX with selected timer number)
    REG_TM0D =	63350;		// TODO: complete this line to set timer initial value
    REG_TM0CNT |=	TIMER_FREQUENCY_256 | TIMER_INTERRUPTS | TIMER_ENABLE;	// TODO: complete this line to set timer frequency and enable timer
    
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
while(map_flag<6)
{
	if(map_flag==start) {
		menu();							// if map_flag == start, the menu loop will be executed
	}
	if(map_flag==game) {
		game();					// if map_flag == lvlone, the level one loop will be executed
	}
	if(map_flag==game_win1) {
		gamewin1();					// if map_flag == gameover, the game over loop will be executed
	}
	if(map_flag==game_win1) {
		gamewin2();					// if map_flag == gameover, the game over loop will be executed
	}
	if(map_flag==game_win1) {
		gamewin3();					// if map_flag == gameover, the game over loop will be executed
	}
	if(map_flag==game_lose) {
		gamelose();						// if map_flag == gamewin, the game win loop will be executed
	}

}

    while(1);

	return 0;
}

