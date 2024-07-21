#include "lib/LIB/neslib.h"
#include "lib/LIB/nesdoug.h"
#include "lib/MMC3/mmc3_code.h"
#include "FRISK.C"
#include "FLOWEY.C"
unsigned char player_x=120;
unsigned char player_y=0xC0;
unsigned char pad1;
unsigned char frisk_frame=0;
unsigned char frisk_frame_wait=0;
unsigned char frisk_face=1;//0=down,1=up,2=left,3=right
unsigned char map_frisk_collison=0x00;
unsigned char state;
unsigned char tempL;
unsigned char tempR;
unsigned char tempT;
unsigned char tempD;
unsigned char pal_had_fade_not=0;
struct Box2D frisk_map_box;

const char LEFT_COLLISON = 0x01;
const char RIGHT_COLLISON = 0x02;
const char UP_COLLISON = 0x04;
const char DOWN_COLLISON = 0x08;
const char palette[]={
    0x14,0x10,0x0F,0x30,
    0x14,0x10,0x0F,0x27,
    0x14,0x06,0x27,0x2C,
    0x14,0x06,0x27,0x2C,

    0x14,0x06,0x27,0x2C,
    0x14,0x27,0x0F,0x2A,
    0x14,0x10,0x0F,0x27,
    0x14,0x06,0x27,0x2C
};
struct Box2D {
    unsigned char x;
    unsigned char y;
    unsigned char width;
    unsigned char height;
};

void frisk_frame_change(){
    if (frisk_frame_wait == 10){
        frisk_frame_wait=0;
        if(frisk_frame<3)
            frisk_frame = frisk_frame+1;
        else
            frisk_frame = 0;
        }
    else
        frisk_frame_wait = frisk_frame_wait + 1;
}

void main(){
    //0=menu,1=flowey,2=toriel,3=ruins,4=battle,5=gameover,6=home
    music_play(0);
    ppu_off();
    pal_all(palette);
    ppu_on_all();
    pal_fade_to(0,4);
	frisk_map_box.width=16;
	frisk_map_box.height=8;
    while(1){
        ppu_wait_nmi();
        
        pad1 = pad_poll(0);
        if(state == 0){
            if(pad1 & PAD_START){
                music_stop();
                music_play(1);
                pal_fade_to(4,0);
                state = 1;
            }
        }
        if(state == 1){
            if(pal_had_fade_not == 0){
                pal_fade_to(0,4);
                pal_had_fade_not = 1;
            }
            if((pad1 & PAD_LEFT)&&(player_x>=0x02)){
                frisk_face = 2;
                player_x=player_x-1;
            }
            else if((pad1 & PAD_RIGHT)&&(player_x<=0xF0)){
                frisk_face = 3;
                player_x=player_x+1;
            }

            if((pad1 & PAD_UP)&&(player_y>=0x02)){
                frisk_face = 1;
                player_y=player_y-1;
            }
            else if((pad1 & PAD_DOWN)&&(player_y<=0xC5)){
                
                frisk_face = 0;
                player_y=player_y+1;

            }
            if(!(pad1 & PAD_LEFT)&&!(pad1 & PAD_RIGHT)&&!(pad1 & PAD_UP)&&!(pad1 & PAD_DOWN)){
                frisk_frame = 0;
                frisk_frame_wait = 0;
            }
            else
                frisk_frame_change();

            map_frisk_collison=0;
            frisk_map_box.x = player_x;
            frisk_map_box.y = player_y+24;
            oam_clear();
            oam_meta_spr(player_x, player_y , frisk[frisk_face][frisk_frame]);
            oam_meta_spr(120, 100 , flowey_talk[0]);
        }
    }
}