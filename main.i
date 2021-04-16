# 1 "main.c"
# 1 "<built-in>"
# 1 "<command line>"
# 1 "main.c"
# 9 "main.c"
int x, y, x2, y2, y3, yb4_jump, dt, v = 0;
int dir = 4;
int timer;
int activated1 = 0;
# 1 "mygbalib.h" 1
# 1 "sprites.h" 1
# 1 "gba.h" 1







typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef signed char s8;
typedef signed short s16;
typedef signed int s32;

typedef unsigned char byte;
typedef unsigned short hword;
typedef unsigned int word;
# 211 "gba.h"
enum
{
    VBLANK_HANDLER,
    HBLANK_HANDLER,
    VCOUNT_HANDLER,
    TIMER0_HANDLER,
    TIMER1_HANDLER,
    TIMER2_HANDLER,
    TIMER3_HANDLER,
    SERIAL_COM_HANDLER,
    DMA0_HANDLER,
    DMA1_HANDLER,
    DMA2_HANDLER,
    DMA3_HANDLER,
    KEYS_HANDLER,
    CART_HANDLER,
    MAX_INTERRUPT_HANDLERS,
};
# 267 "gba.h"
typedef void (*fp)(void);
# 2 "sprites.h" 2




int palette[] = {
((0) + (0<<5) + (0<<10)),
((31) + (31<<5) + (31<<10)),
((0) + (31<<5) + (31<<10)),
((26) + (26<<5) + (26<<10)),
((9) + (9<<5) + (9<<10)),
((31) + (31<<5) + (0<<10)),
((31) + (0<<5) + (0<<10)),
((0) + (0<<5) + (31<<10)),
((11) + (8<<5) + (3<<10)),
((27) + (27<<5) + (27<<10)),
((16) + (16<<5) + (16<<10)),
((31) + (17<<5) + (17<<10)),
((31) + (24<<5) + (24<<10)),
((27) + (0<<5) + (0<<10)),
((0) + (16<<5) + (0<<10)),
((0) + (31<<5) + (0<<10)),
((16) + (31<<5) + (16<<10)),
((23) + (31<<5) + (23<<10))
};




u16 sprites[] = {


0,0,0,0,0,0,1,1,
0,0,0,0,0,1,1,2,
0,0,0,0,0,1,2,2,
0,0,0,3,0,0,1,1,
0,0,3,3,3,1,1,1,
0,0,3,3,3,1,1,1,
0,0,3,3,3,1,1,1,
0,4,3,4,3,1,1,1,

1,0,0,0,0,0,0,0,
2,0,0,0,0,0,0,0,
2,0,0,0,0,0,0,0,
1,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
1,0,0,0,0,0,0,0,
1,1,1,3,0,0,0,0,
0,0,0,0,0,0,0,0,

0,4,3,4,3,1,1,1,
0,0,0,0,0,1,1,1,
0,0,0,0,0,1,1,0,
0,0,0,0,0,1,1,0,
0,0,0,0,0,1,1,0,
0,0,0,0,0,1,1,0,
0,0,0,0,0,1,1,0,
0,0,0,0,0,3,1,1,

0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,



0,0,0,0,0,0,1,1,
0,0,0,0,0,1,1,2,
0,0,0,0,0,1,2,2,
0,0,0,3,0,0,1,1,
0,0,3,3,3,1,1,1,
0,0,3,3,3,1,1,1,
0,0,3,3,3,1,1,1,
0,4,3,4,3,1,1,1,

1,0,0,0,0,0,0,0,
2,0,0,0,0,0,0,0,
2,0,0,0,0,0,0,0,
1,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
1,0,0,0,0,0,0,0,
1,1,1,3,0,0,0,0,
0,0,0,0,0,0,0,0,

0,4,3,4,3,1,1,1,
0,0,5,6,5,1,1,1,
0,0,5,6,5,1,1,0,
0,0,0,5,0,1,1,0,
0,0,0,5,0,1,1,0,
0,0,0,0,0,1,1,0,
0,0,0,0,0,1,1,0,
0,0,0,0,0,3,1,1,

0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,



0,0,0,0,0,0,0,1,
0,0,0,0,0,0,0,2,
0,0,0,0,0,0,0,2,
0,0,0,0,0,0,0,1,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,1,
0,0,0,0,3,1,1,1,
0,0,0,0,0,0,0,0,

1,1,0,0,0,0,0,0,
2,1,1,0,0,0,0,0,
2,2,1,0,0,0,0,0,
1,1,0,0,3,0,0,0,
1,1,1,3,3,3,0,0,
1,1,1,3,3,3,0,0,
1,1,1,3,3,3,0,0,
1,1,1,3,4,3,4,0,

0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,

1,1,1,3,4,3,4,0,
1,1,1,0,0,0,0,0,
0,1,1,0,0,0,0,0,
0,1,1,0,0,0,0,0,
0,1,1,0,0,0,0,0,
0,1,1,0,0,0,0,0,
0,1,1,0,0,0,0,0,
1,1,3,0,0,0,0,0,



0,0,0,0,0,0,0,1,
0,0,0,0,0,0,0,2,
0,0,0,0,0,0,0,2,
0,0,0,0,0,0,0,1,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,1,
0,0,0,0,3,1,1,1,
0,0,0,0,0,0,0,0,

1,1,0,0,0,0,0,0,
2,1,1,0,0,0,0,0,
2,2,1,0,0,0,0,0,
1,1,0,0,3,0,0,0,
1,1,1,3,3,3,0,0,
1,1,1,3,3,3,0,0,
1,1,1,3,3,3,0,0,
1,1,1,3,4,3,4,0,

0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,

1,1,1,3,4,3,4,0,
1,1,1,5,6,5,0,0,
0,1,1,5,6,5,0,0,
0,1,1,0,5,0,0,0,
0,1,1,0,5,0,0,0,
0,1,1,0,0,0,0,0,
0,1,1,0,0,0,0,0,
1,1,3,0,0,0,0,0,



1,1,1,1,1,1,1,1,
1,0,0,0,0,0,0,0,
1,0,0,0,0,0,0,0,
1,0,0,0,0,0,0,0,
1,0,0,0,0,0,0,0,
1,0,0,0,0,0,0,0,
1,0,0,0,0,0,0,0,
1,0,0,0,0,0,0,0,


1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,


1,0,0,0,0,0,0,0,
1,0,0,0,0,0,0,0,
1,0,0,0,0,0,0,0,
1,0,0,0,0,0,0,0,
1,0,0,0,0,0,0,0,
1,0,0,0,0,0,0,0,
1,0,0,0,0,0,0,0,
1,1,1,1,1,1,1,1,


0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
1,1,1,1,1,1,1,1,




1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,


1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,


0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
1,1,1,1,1,1,1,1,


0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
1,1,1,1,1,1,1,1,




1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,


1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,1,
0,0,0,0,0,0,0,1,
0,0,0,0,0,0,0,1,
0,0,0,0,0,0,0,1,
0,0,0,0,0,0,0,1,
0,0,0,0,0,0,0,1,
0,0,0,0,0,0,0,1,


0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
1,1,1,1,1,1,1,1,


0,0,0,0,0,0,0,1,
0,0,0,0,0,0,0,1,
0,0,0,0,0,0,0,1,
0,0,0,0,0,0,0,1,
0,0,0,0,0,0,0,1,
0,0,0,0,0,0,0,1,
0,0,0,0,0,0,0,1,
1,1,1,1,1,1,1,1,



1,1,1,1,1,1,1,1,
1,0,0,0,0,0,0,0,
1,0,0,0,0,0,0,0,
1,0,0,0,0,0,0,0,
1,0,0,0,0,0,0,0,
1,0,0,0,0,0,0,0,
1,0,0,0,0,0,0,0,
1,0,0,0,0,0,0,0,


1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,


1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,


1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,




1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,


1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,1,
0,0,0,0,0,0,0,1,
0,0,0,0,0,0,0,1,
0,0,0,0,0,0,0,1,
0,0,0,0,0,0,0,1,
0,0,0,0,0,0,0,1,
0,0,0,0,0,0,0,1,


1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,


1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,




0,0,0,0,0,0,0,0,
0,0,0,6,6,6,0,0,
0,0,6,12,12,11,6,0,
0,6,12,11,11,6,6,6,
0,6,12,11,6,6,6,6,
0,6,12,11,6,6,6,6,
0,0,6,12,11,6,6,6,
0,0,0,6,12,11,6,6,


0,0,0,0,0,0,0,0,
0,0,6,6,6,0,0,0,
0,6,12,12,11,6,0,0,
6,12,11,6,6,6,6,0,
6,11,11,6,6,6,6,0,
6,6,6,6,6,6,6,0,
6,6,6,6,6,6,0,0,
6,6,6,6,6,0,0,0,


0,0,0,6,12,11,6,6,
0,0,0,0,6,12,6,6,
0,0,0,0,6,12,11,6,
0,0,0,0,0,6,11,6,
0,0,0,0,0,0,6,6,
0,0,0,0,0,0,6,6,
0,0,0,0,0,0,0,6,
0,0,0,0,0,0,0,0,



6,6,6,6,6,0,0,0,
6,6,6,6,0,0,0,0,
6,6,6,0,0,0,0,0,
6,6,6,0,0,0,0,0,
6,6,0,0,0,0,0,0,
6,6,0,0,0,0,0,0,
6,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,





0,0,0,0,0,9,9,0,
0,0,0,0,9,1,9,0,
0,0,0,0,9,1,9,0,
0,0,0,0,9,1,9,0,
0,0,0,0,9,1,9,0,
0,0,0,9,1,1,9,9,
0,9,9,1,1,1,1,10,
0,9,1,1,1,1,13,10,


0,9,9,0,0,0,0,0,
0,9,1,9,0,0,0,0,
0,9,1,9,0,0,0,0,
0,9,1,9,0,0,0,0,
0,9,1,9,0,0,9,0,
9,9,1,1,9,0,9,9,
10,1,1,1,9,9,0,9,
10,13,1,1,1,1,9,0,


0,9,9,1,1,1,1,1,
0,0,9,1,0,0,1,0,
0,0,9,1,1,1,1,1,
0,0,0,9,0,0,1,0,
0,0,0,2,9,9,1,1,
0,0,0,2,2,9,9,9,
0,0,0,0,2,2,2,2,
0,0,0,0,0,0,0,0,


1,1,1,1,1,9,9,0,
0,1,0,0,1,9,0,0,
1,1,1,1,1,9,0,0,
0,1,0,0,9,0,0,0,
1,1,9,9,2,0,0,0,
9,9,9,2,2,0,0,0,
2,2,2,2,0,0,0,0,
0,0,0,0,0,0,0,0,




0,0,0,0,0,0,0,0,
0,0,0,3,3,3,0,0,
0,0,3,4,4,10,3,0,
0,3,4,10,10,3,3,3,
0,3,4,10,3,3,3,3,
0,3,4,10,3,3,3,3,
0,0,3,4,10,3,3,3,
0,0,0,3,4,10,3,3,


0,0,0,0,0,0,0,0,
0,0,3,3,3,0,0,0,
0,3,4,4,10,3,0,0,
3,4,10,3,3,3,3,0,
3,10,10,3,3,3,3,0,
3,3,3,3,3,3,3,0,
3,3,3,3,3,3,0,0,
3,3,3,3,3,0,0,0,


0,0,0,3,4,10,3,3,
0,0,0,0,3,4,3,3,
0,0,0,0,3,4,10,3,
0,0,0,0,0,3,10,3,
0,0,0,0,0,0,3,3,
0,0,0,0,0,0,3,3,
0,0,0,0,0,0,0,3,
0,0,0,0,0,0,0,0,



3,3,3,3,3,0,0,0,
3,3,3,3,0,0,0,0,
3,3,3,0,0,0,0,0,
3,3,3,0,0,0,0,0,
3,3,0,0,0,0,0,0,
3,3,0,0,0,0,0,0,
3,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,




0,0,0,0,0,0,0,0,
0,0,0,14,14,15,0,0,
0,0,14,15,15,17,15,0,
0,14,15,17,15,17,17,15,
0,14,15,15,17,17,17,17,
0,14,15,17,15,17,17,17,
0,14,15,17,17,17,17,17,
0,14,15,15,15,17,17,17,


0,0,0,0,0,0,0,0,
0,0,16,16,16,0,0,0,
0,16,16,17,16,16,0,0,
15,16,17,16,17,16,16,0,
17,17,17,16,17,16,16,0,
17,17,17,17,16,17,16,0,
17,17,17,17,17,16,16,0,
17,17,17,17,16,17,16,0,


0,0,14,15,17,15,17,17,
0,0,0,14,15,15,15,17,
0,0,0,0,14,15,17,15,
0,0,0,0,0,14,15,15,
0,0,0,0,0,0,14,15,
0,0,0,0,0,0,0,14,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,


17,17,17,16,17,16,0,0,
17,17,16,17,16,0,0,0,
17,16,17,16,0,0,0,0,
16,17,16,0,0,0,0,0,
17,16,0,0,0,0,0,0,
16,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,




0,0,0,0,0,6,6,6,
0,0,0,0,0,6,6,6,
0,0,0,0,13,6,6,13,
0,0,0,13,13,13,6,13,
0,0,0,13,13,13,6,13,
0,0,13,13,13,13,6,13,
0,0,13,13,13,13,6,13,
0,6,13,13,13,0,0,13,


6,6,6,0,0,0,0,0,
6,6,6,0,0,0,0,0,
13,6,6,13,0,0,0,0,
13,6,13,13,13,0,0,0,
13,6,13,13,13,0,0,0,
13,6,13,13,13,13,0,0,
13,6,13,13,13,13,0,0,
13,0,0,13,13,13,6,0,


0,6,13,13,0,0,0,13,
0,6,6,13,0,0,0,13,
0,6,6,13,0,0,0,6,
0,6,6,13,0,0,0,6,
6,6,6,6,0,0,6,6,
6,6,6,6,0,0,6,6,
6,6,6,6,0,0,6,6,
0,6,6,0,0,0,0,6,


13,0,0,13,13,13,6,0,
6,0,0,0,13,6,6,0,
6,0,0,0,13,6,6,0,
6,0,0,0,13,6,6,0,
6,6,0,0,6,6,6,6,
6,6,0,0,6,6,6,6,
6,6,0,0,6,6,6,6,
6,0,0,0,0,6,6,0,




0,0,0,1,1,1,6,6,
0,0,0,1,1,1,6,6,
0,0,0,1,1,1,6,6,
0,0,0,1,1,1,6,6,
0,0,0,1,1,1,6,6,
0,0,0,6,6,6,1,1,
0,0,0,6,6,6,1,1,
0,0,0,0,6,6,1,1,


6,1,1,1,6,0,0,0,
6,1,1,1,6,0,0,0,
6,1,1,1,6,0,0,0,
6,1,1,1,6,0,0,0,
6,1,1,1,6,0,0,0,
1,6,6,6,6,0,0,0,
1,6,6,6,6,0,0,0,
1,6,6,6,0,0,0,0,


0,0,0,0,6,6,1,1,
0,0,0,0,6,6,1,1,
0,0,0,0,1,1,6,6,
0,0,0,0,0,1,6,6,
0,0,0,0,0,1,6,6,
0,0,0,0,0,1,6,6,
0,0,0,0,0,1,6,6,
0,0,0,0,0,6,6,6,


1,6,6,6,0,0,0,0,
1,6,6,6,0,0,0,0,
6,1,1,1,0,0,0,0,
6,1,1,0,0,0,0,0,
6,1,1,0,0,0,0,0,
6,1,1,0,0,0,0,0,
6,1,1,0,0,0,0,0,
6,6,6,0,0,0,0,0,




0,0,0,0,0,0,0,6,
0,0,0,0,0,0,6,6,
0,0,0,0,0,0,6,6,
0,0,0,0,0,6,6,6,
0,0,0,0,0,6,6,6,
0,0,0,0,0,6,6,6,
0,0,0,0,0,1,6,6,
0,0,0,0,1,1,6,6,


6,0,0,0,0,0,0,0,
6,6,0,0,0,0,0,0,
6,6,0,0,0,0,0,0,
6,6,6,0,0,0,0,0,
6,6,6,0,0,0,0,0,
6,6,6,0,0,0,0,0,
6,1,1,0,0,0,0,0,
6,1,1,1,0,0,0,0,


0,0,0,0,1,1,6,6,
0,0,0,0,1,1,6,6,
0,0,0,0,1,1,6,6,
0,0,0,0,6,6,1,1,
0,0,0,6,6,6,1,1,
0,0,0,6,6,6,1,1,
0,0,0,6,6,6,1,1,
0,0,0,6,6,6,1,1,


6,1,1,1,0,0,0,0,
6,1,1,1,0,0,0,0,
6,1,1,1,0,0,0,0,
1,6,6,6,0,0,0,0,
1,6,6,6,6,0,0,0,
1,6,6,6,6,0,0,0,
1,6,6,6,6,0,0,0,
1,6,6,6,6,0,0,0,




0,0,1,1,7,7,7,1,
0,0,1,1,7,7,7,1,
0,0,6,1,7,7,7,1,
0,0,6,1,7,7,7,1,
0,0,1,1,7,7,7,1,
0,0,3,1,7,7,7,3,
0,4,1,3,7,7,7,3,
0,4,1,3,7,7,4,1,


1,1,1,7,7,7,0,0,
6,1,1,7,7,7,0,0,
6,6,1,7,7,7,0,0,
6,6,1,7,7,7,0,0,
1,1,1,7,7,7,0,0,
1,1,1,7,7,3,0,0,
3,1,1,7,4,1,3,0,
1,3,1,7,4,1,3,0,


0,4,4,1,3,7,4,1,
1,1,4,1,3,7,4,1,
1,1,1,4,3,7,4,1,
0,4,4,4,0,0,4,4,
0,0,0,8,0,0,0,8,
0,0,8,8,0,0,0,8,
0,8,8,8,8,0,8,8,
0,8,8,8,8,0,8,8,


1,3,1,4,1,4,3,0,
1,3,1,4,1,4,1,3,
1,3,1,4,4,1,1,3,
4,4,0,0,4,4,4,0,
8,0,0,0,8,0,0,0,
8,0,0,0,8,8,0,0,
8,8,0,8,8,8,8,0,
8,8,0,8,8,8,8,0,




0,0,3,3,3,3,3,3,
0,0,1,1,3,1,1,1,
0,0,1,1,3,1,1,1,
0,0,3,3,3,3,3,3,
0,0,1,1,3,1,1,1,
0,0,7,7,7,7,7,7,
0,0,7,7,7,7,7,7,
0,0,1,1,7,7,7,1,


3,3,3,3,3,3,0,0,
1,1,1,1,1,1,0,0,
1,1,1,1,1,1,0,0,
3,3,3,3,3,3,0,0,
1,1,1,1,1,1,0,0,
7,7,7,7,7,7,0,0,
7,7,7,7,7,7,0,0,
1,1,1,7,7,7,0,0,


0,0,1,1,7,7,7,1,
0,0,6,1,7,7,7,1,
0,0,6,1,7,7,7,1,
0,0,6,1,7,7,7,1,
0,0,1,1,7,7,7,1,
0,0,6,1,7,7,7,1,
0,0,6,1,7,7,7,1,
0,0,6,1,7,7,7,1,


1,1,1,7,7,7,0,0,
6,6,1,7,7,7,0,0,
6,6,1,7,7,7,0,0,
6,6,1,7,7,7,0,0,
1,1,1,7,7,7,0,0,
6,6,1,7,7,7,0,0,
6,6,1,7,7,7,0,0,
1,6,1,7,7,7,0,0,




0,0,7,7,7,7,7,7,
0,0,7,7,7,7,7,7,
0,0,1,1,7,7,7,1,
0,0,1,1,7,7,7,1,
0,0,6,1,7,7,7,1,
0,0,6,1,7,7,7,1,
0,0,6,1,7,7,7,1,
0,0,1,1,7,7,7,1,


7,7,7,7,7,7,0,0,
7,7,7,7,7,7,0,0,
1,1,1,7,7,7,0,0,
1,1,1,7,7,7,0,0,
6,6,1,7,7,7,0,0,
6,6,1,7,7,7,0,0,
6,6,1,7,7,7,0,0,
1,1,1,7,7,7,0,0,


0,0,6,1,7,7,7,1,
0,0,6,1,7,7,7,1,
0,0,1,1,3,1,1,1,
0,0,1,1,3,1,1,1,
0,0,3,3,3,3,3,3,
0,0,6,1,3,1,1,7,
0,0,1,1,3,1,1,7,
0,0,6,1,3,1,1,6,


6,6,1,7,7,7,0,0,
6,6,1,7,7,7,0,0,
1,1,1,1,1,1,0,0,
1,1,1,1,1,1,0,0,
3,3,3,3,3,3,0,0,
7,6,6,1,1,1,0,0,
7,1,1,1,1,1,0,0,
6,6,6,1,1,1,0,0,




0,0,1,1,1,1,1,1,
0,0,1,1,1,6,1,1,
0,0,1,1,1,1,1,1,
0,0,1,1,1,1,1,1,
0,0,1,1,1,6,1,1,
0,0,3,3,3,6,3,3,
0,0,1,1,1,1,1,1,
0,0,1,1,1,6,1,1,


1,1,1,1,1,1,0,0,
1,1,1,6,1,1,0,0,
1,1,1,1,1,1,0,0,
1,1,1,1,1,1,0,0,
1,1,1,6,1,1,0,0,
3,3,3,6,3,3,0,0,
1,1,1,1,1,1,0,0,
1,1,1,6,1,1,0,0,


0,0,1,1,1,1,1,1,
0,0,1,1,1,6,1,1,
0,0,1,1,1,6,1,1,
0,0,1,1,1,1,1,1,
0,0,1,1,1,6,1,1,
0,0,3,3,3,3,3,3,
0,0,1,3,1,3,1,3,
0,0,1,3,1,3,1,3,


1,1,1,1,1,1,0,0,
1,1,1,6,1,1,0,0,
1,1,1,6,1,1,0,0,
1,1,1,1,1,1,0,0,
1,1,1,6,1,1,0,0,
3,3,3,3,3,3,0,0,
1,3,1,3,1,3,0,0,
1,3,1,3,1,3,0,0,




0,0,0,0,3,3,3,3,
0,0,0,0,1,1,1,1,
0,0,0,0,1,1,3,1,
0,0,0,0,1,1,1,1,
0,0,0,0,1,1,1,1,
0,0,0,0,1,1,1,1,
0,0,0,0,1,1,1,1,
0,0,0,0,3,1,3,1,


3,3,3,3,0,0,0,0,
1,1,1,1,0,0,0,0,
1,1,3,1,0,0,0,0,
1,1,3,1,0,0,0,0,
1,1,3,1,0,0,0,0,
1,1,3,1,0,0,0,0,
1,1,1,1,0,0,0,0,
3,1,3,1,0,0,0,0,


0,0,0,0,3,3,3,7,
0,0,0,0,1,3,1,7,
0,0,0,0,1,3,1,7,
0,0,0,1,3,1,7,7,
0,0,0,1,3,1,7,7,
0,0,1,3,1,7,7,7,
0,0,1,3,1,7,7,7,
0,0,3,3,3,7,7,7,


7,7,7,7,0,0,0,0,
7,7,7,7,0,0,0,0,
7,7,7,7,0,0,0,0,
7,7,7,1,3,0,0,0,
7,7,7,1,3,0,0,0,
7,7,7,7,1,3,0,0,
7,7,0,7,1,3,0,0,
7,7,7,7,3,3,0,0,




0,0,0,0,0,0,1,1,
0,0,0,0,0,0,1,1,
0,0,0,0,0,0,1,1,
0,0,0,0,0,0,1,1,
0,0,0,0,0,0,1,1,
0,0,0,0,0,1,1,1,
0,0,0,0,0,1,1,1,
0,0,0,0,0,1,1,1,


3,1,0,0,0,0,0,0,
3,1,0,0,0,0,0,0,
3,1,0,0,0,0,0,0,
3,1,0,0,0,0,0,0,
3,1,0,0,0,0,0,0,
1,3,1,0,0,0,0,0,
1,3,1,0,0,0,0,0,
1,3,1,0,0,0,0,0,


0,0,0,0,0,1,1,1,
0,0,0,0,0,1,1,1,
0,0,0,0,0,1,1,1,
0,0,0,0,3,3,3,3,
0,0,0,0,7,7,7,7,
0,0,0,0,7,7,7,7,
0,0,0,0,3,1,3,1,
0,0,0,0,3,1,3,1,


1,3,1,0,0,0,0,0,
1,3,1,0,0,0,0,0,
1,3,1,0,0,0,0,0,
3,3,3,3,0,0,0,0,
7,7,7,7,0,0,0,0,
7,7,7,7,0,0,0,0,
3,1,3,1,0,0,0,0,
3,1,3,1,0,0,0,0,




0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,3,
0,0,0,0,0,0,0,3,
0,0,0,0,0,0,0,3,
0,0,0,0,0,0,0,3,
0,0,0,0,0,0,0,3,
0,0,0,0,0,0,0,1,


0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
3,0,0,0,0,0,0,0,
1,0,0,0,0,0,0,0,


0,0,0,0,0,0,1,4,
0,0,0,0,0,0,1,1,
0,0,0,0,0,0,3,3,
0,0,0,0,0,0,3,4,
0,0,0,0,0,0,3,3,
0,0,0,0,0,0,3,3,
0,0,0,0,0,0,4,3,
0,0,0,0,0,0,1,1,


1,1,0,0,0,0,0,0,
1,1,0,0,0,0,0,0,
4,3,0,0,0,0,0,0,
4,3,0,0,0,0,0,0,
4,3,0,0,0,0,0,0,
4,3,0,0,0,0,0,0,
4,3,0,0,0,0,0,0,
3,1,0,0,0,0,0,0,




0,0,0,0,0,0,0,0,
0,0,0,3,3,9,9,3,
0,4,0,3,3,3,3,3,
4,4,4,3,3,3,3,3,
4,10,3,3,3,3,3,10,
4,4,10,10,3,3,10,10,
4,4,10,3,3,3,4,10,
4,4,10,3,3,3,4,10,


9,9,9,0,0,0,0,0,
3,3,9,9,9,0,0,0,
9,3,3,9,9,9,0,0,
10,9,3,3,3,3,0,0,
10,10,9,3,3,9,0,0,
4,10,10,9,3,9,9,0,
3,4,10,9,9,3,9,0,
10,10,3,3,3,3,9,0,


10,10,3,10,3,3,3,4,
4,10,3,10,3,3,3,3,
4,4,10,3,10,3,3,3,
0,4,10,10,3,3,10,3,
0,4,10,10,10,10,3,10,
0,0,4,4,4,10,10,3,
0,0,0,0,4,4,4,10,
0,0,0,0,0,0,4,4,


10,10,3,3,3,3,9,9,
4,4,3,3,3,3,3,3,
3,3,3,3,3,3,3,3,
3,3,3,10,3,3,9,0,
3,3,10,3,3,9,3,0,
10,3,3,3,3,3,0,0,
3,4,3,3,3,0,0,0,
4,4,0,0,0,0,0,0,




0,0,0,0,0,0,0,0,
0,14,14,0,0,0,0,14,
0,14,15,15,0,0,0,14,
0,0,0,16,16,0,0,0,
0,0,0,16,0,0,9,0,
0,0,0,0,0,10,3,9,
0,14,15,16,0,10,3,3,
0,14,15,16,16,1,1,1,


14,14,0,0,0,0,0,0,
15,15,14,0,0,0,0,0,
17,17,14,0,0,0,0,0,
17,17,0,0,0,16,15,15,
1,0,0,17,16,16,15,14,
1,10,3,9,17,0,14,14,
1,10,3,3,0,0,0,0,
1,0,10,10,0,0,3,0,


0,0,15,0,1,1,9,1,
0,0,17,17,17,10,1,1,
0,0,17,0,10,0,1,0,
0,17,17,0,17,0,1,3,
14,15,17,17,17,0,0,0,
15,15,16,0,0,0,0,3,
14,15,14,0,0,0,10,0,
0,14,0,0,0,0,0,0,


1,1,1,0,0,10,10,0,
3,3,1,10,0,0,0,0,
3,0,1,1,0,0,0,0,
3,3,17,17,0,0,0,0,
0,17,0,17,17,0,0,0,
0,0,0,0,16,16,14,0,
0,0,0,0,16,15,14,0,
0,0,0,0,0,14,14,0,




0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
6,6,6,6,6,6,6,6,


0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
6,6,6,6,6,6,6,6,


6,6,6,6,6,6,6,6,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,


6,6,6,6,6,6,6,6,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0
};
# 2 "mygbalib.h" 2



void buttonA(void)
{
        if(v==0)
    {
        yb4_jump = y;
        dt = 0;
        v = 26;
    }
}
void buttonB(void)
{
        timer = 1;
}
void buttonSel(void)
{
        timer = 0;
}




void buttonR(void)
{
    if (x > 224) {
        x2 = 0;
    } else {
        x2 = 2;
    }
    dir = 0;
}
void buttonL(void)
{
    if (x < 2) {
        x2 = 0;
    } else {
        x2 = -2;
    }
    dir = 2;
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

    u16 buttons = (0x3FF & (~*(volatile u16*)0x4000130));

    if ((buttons & 0x001) == 0x001)
    {
        buttonA();
    }
    if ((buttons & 0x002) == 0x002)
    {
        buttonB();
    }
# 83 "mygbalib.h"
    if ((buttons & 0x010) == 0x010)
    {
        buttonR();
    }
    if ((buttons & 0x020) == 0x020)
    {
        buttonL();
    }
    if ((buttons & 0x040) == 0x040)
    {
        buttonU();
    }
    if ((buttons & 0x080) == 0x080)
    {
        buttonD();
    }
}


void fillPalette(void)
{
    int i;


    for (i = 0; i < 20; i++)
        ((unsigned short *) 0x5000200)[i] = palette[i];
}


void fillSprites(void)
{
    int i;


    for (i = 0; i < 128*16*16; i++)
        ((unsigned short *) 0x6010000)[i] = (sprites[i*2+1] << 8) + sprites[i*2];


    for(i = 0; i < 128; i++)
        drawSprite(0, i, 240,160);
}


void drawSprite(int numb, int N, int x, int y)
{

    *(unsigned short *)(0x7000000 + 8*N) = y | 0x2000;
    *(unsigned short *)(0x7000002 + 8*N) = x | 0x4000;
    *(unsigned short *)(0x7000004 + 8*N) = numb*8;
}
# 14 "main.c" 2
void clearSprites (void)
{

        int j;
        for(j=0;j<128;j++){
                drawSprite(10,j,240,160);
                }
}

void Handler(void)
{
    *(u16*)0x4000208 = 0x00;

    if ((*(u16*)0x4000202 & 0x8) == 0x8)
    {

             dt += 1;
         checkbutton();
         jump();
         x = x + x2;
         y = y + y2;
         x2 = 0;
         y2 = 0;
    }

    *(u16*)0x4000202 = *(u16*)0x4000202;

    *(u16*)0x4000208 = 0x01;
}

void jump(void)
{
    if (v!=0)
    {
        y3 = v*dt - dt*dt;
        y3 = -y3/10;
        y = yb4_jump + y3;
        if (dt > 25)
        {
            dt = 0;
            v = 0;
        }

    }

}

void init_pos(void)
{
        x = 120;
        y = 80;
    drawSprite(0,0,x,y);


}

void move(void){
    clearSprites();

    while (activated1 == 0) {
    drawSprite(dir, 0, x, y);

    }
}







int main(void)
{
        int activated = 0;

    *(unsigned short *) 0x4000000 = 0x40 | 0x2 | 0x1000;

         fillPalette();
         fillSprites();



    (*(unsigned int*)0x3007FFC) = (int)&Handler;
    *(u16*)0x4000200 = 0x8;
    *(u16*)0x4000208 = 0x1;


    *(u16*)0x4000100 = 63350;
    *(u16*)0x4000102 = 0x0002 | 0x0040 | 0x0080;

    activated = 1;
    while (activated == 1) {

    switch (timer)
    {
    case 0:
        init_pos();
        break;
    case 1:

        move();

    }
}

    while(1);

        return 0;
}
