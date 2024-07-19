#include "assets/LIB/neslib.h"
#include "assets/LIB/nesdoug.h"
unsigned char player_x=0;
unsigned char player_y=0;
unsigned char pad1;
unsigned char frisk_frame=0;
unsigned char frisk_frame_wait=0;
unsigned char frisk_face=0;//0=down,1=up,2=left,3=right
const char palette[]={
    0x14,0x30,0x24,0x19,
    0x14,0x1C,0x15,0x2A,
    0x14,0x06,0x27,0x2C,
    0x14,0x06,0x27,0x2C,
    0x14,0x06,0x27,0x2C,
    0x14,0x06,0x27,0x2C,
    0x14,0x06,0x27,0x2C,
    0x14,0x06,0x27,0x2C
};
const unsigned char frisk_down_0_data[]={

	  0,  0,0x01,0,
	  8,  0,0x02,0,
	  0,  8,0x03,0,
	  8,  8,0x04,0,
	  0, 16,0x05,0,
	  8, 16,0x06,0,
	  0, 24,0x07,0,
	  8, 24,0x08,0,
	128

};

const unsigned char frisk_down_1_data[]={

	  0,  0,0x01,0,
	  8,  0,0x02,0,
	  0,  8,0x03,0,
	  8,  8,0x04,0,
	  0, 16,0x09,0,
	  8, 16,0x06,0,
	  0, 24,0x0a,0,
	  8, 24,0x0b,0,
	128

};

const unsigned char frisk_down_2_data[]={

	  0,  0,0x01,0,
	  8,  0,0x02,0,
	  0,  8,0x03,0,
	  8,  8,0x04,0,
	  0, 16,0x05,0,
	  8, 16,0x06,0,
	  0, 24,0x07,0,
	  8, 24,0x08,0,
	128

};

const unsigned char frisk_down_3_data[]={

	  0,  0,0x01,0,
	  8,  0,0x02,0,
	  0,  8,0x03,0,
	  8,  8,0x04,0,
	  0, 16,0x05,0,
	  8, 16,0x0c,0,
	  0, 24,0x0d,0,
	  8, 24,0x0e,0,
	128

};

const unsigned char* const frisk_down[]={

	frisk_down_0_data,
	frisk_down_1_data,
	frisk_down_2_data,
	frisk_down_3_data

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
    ppu_off();
    pal_all(palette);
    ppu_on_all();
    while(1){
        ppu_wait_nmi();

        pad1 = pad_poll(0);

        if(pad1 & PAD_LEFT){
            
            player_x=player_x-1;
        }
        else if(pad1 & PAD_RIGHT){
            player_x=player_x+1;
        }

        if(pad1 & PAD_UP){
            player_y=player_y-1;
        }
        else if(pad1 & PAD_DOWN){
            player_y=player_y+1;

        }
        if(!(pad1 & PAD_LEFT)&&!(pad1 & PAD_RIGHT)&&!(pad1 & PAD_UP)&&!(pad1 & PAD_DOWN)){
            frisk_frame=0;
            frisk_frame_wait=0;
        }
        else
            frisk_frame_change();
        oam_clear();
        oam_meta_spr(player_x, player_y , frisk_down[frisk_frame]);
    }
}