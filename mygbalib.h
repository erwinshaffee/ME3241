#include "sprites.h"
#define INPUT                      (KEY_MASK & (~REG_KEYS))


void buttonA(void) //Z
{
	if(v==0)
    {
        yb4_jump = y; //locks initial y position before the jump
        dt = 0; //reinitialize timer to ensure start from zero
        v = 37; //inputs initial starting velocity
    }//jump function here;
}
void buttonB(void) //X
{
	lvl = 1;
}
void buttonSel(void) //Backspace
{
	y = y;
}
/*void buttonS(void)
{
	x = x;
}*/
void buttonR(void)
{
    if (x > 224) {
        x2 = 0;
    } else 
    {
	    x2 = 2;
    }

    if (santa == 0)
    {
        dir = MR_S_N_R;
    }
    if (santa == 1)
    {
        dir = MR_S_T_R;
	} 
    if (santa == 2)
    {
        dir = MR_S_E_R;
    }
    
}
void buttonL(void)
{
    if (x < 2) {
        x2 = 0;
    } else 
    {
	    x2 = -2;
    }

    if (santa == 0)
    {
        dir = MR_S_N_L;
    }
    if (santa == 1)
    {
        dir = MR_S_T_L;
    } 
    if (santa == 2)
    {
        dir =  MR_S_E_L;
    }
}
void buttonU(void)
{
	if (y < 2) {
        y2 = 0;
    } else {
        y2 = -2;
    }
}
void buttonD(void)
{
	if (y > 140) {
        y2 = 0;
    } else {
        y2 = 2;
    }
}


void checkbutton(void)
{
	// Gift function to show you how a function that can be called upon button interrupt to detect which button was pressed and run a specific function for each button could look like. You would have to define each buttonA/buttonB/... function yourself.
    u16 buttons = INPUT;

    if ((buttons & KEY_A) == KEY_A)
    {
        buttonA();
    }
    if ((buttons & KEY_B) == KEY_B)
    {
        buttonB();
    }
    /*if ((buttons & KEY_SELECT) == KEY_SELECT)
    {
        buttonSel();
    }
    if ((buttons & KEY_START) == KEY_START)
    {
        buttonS();
    }*/
    if ((buttons & KEY_RIGHT) == KEY_RIGHT)
    {
        buttonR();
    }
    if ((buttons & KEY_LEFT) == KEY_LEFT)
    {
        buttonL();
    }
    if ((buttons & KEY_UP) == KEY_UP)
    {
        buttonU();
    }
    if ((buttons & KEY_DOWN) == KEY_DOWN)
    {
        buttonD();
    }
}


void fillPalette(void)
{
    int     i;

	// Fill the palette in GBA memory
    for (i = 0; i < NCOLS; i++)
        spritePal[i] = palette[i];
}


void fillSprites(void)
{
    int     i;

	// Load all sprites in GBA memory
    for (i = 0; i < 128*16*16; i++)
        spriteData[i] = (sprites[i*2+1] << 8) + sprites[i*2];

	// draw all sprites on screen, but all of them outside of the screen (starting at position (240,160) the bottom right corner of the GBA screen)
    for(i = 0; i < 128; i++)
        drawSprite(0, i, 240,160);
}


void drawSprite(int numb, int N, int x, int y)
{
	// Same as CA2, make specific sprite (based on its name/numb) appear on screen, as slide number N (each sprite needs a different, arbitrary, N >= 0)
    *(unsigned short *)(0x7000000 + 8*N) = y | 0x2000;
    *(unsigned short *)(0x7000002 + 8*N) = x | 0x4000;
    *(unsigned short *)(0x7000004 + 8*N) = numb*8;
}


/*void drawLaser(void) //for fun/future, delete when necessary
//Need to define NPLATS, NROCK, NMET, LaserX and LASERY
{
	// Gift function showing you how to draw an example sprite defined in sprite.h on screen, using drawSprite()
	// Note that this code uses largeer sprites with a palette, so the main code needs to be initialized in graphical mode 2, using:
    //		*(unsigned short *) 0x4000000 = 0x40 | 0x2 | 0x1000;
	// at the beginning of main() in main.c
    switch(lPlat) {
        case 16:
        {
            drawSprite(LASER, NPLATS*3 + 5 + NROCK + NMET, LaserX, LaserY);
            break;
        }
        case 9:
        {
            drawSprite(LASER, NPLATS*2 + 5 + NROCK + NMET, LaserX, LaserY);
            break;
        }
        default:
            break;
    }
}*/ 