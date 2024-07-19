#include "lib/neslib.h"
unsigned char player_x=0;
unsigned char player_y=0;
unsigned char pad1;
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
const unsigned char frisk_down_0[]={
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

void main(){
    ppu_off();
    pal_all(palette);
    oam_clear();
    oam_meta_spr(player_x, player_y,0, frisk_down_0);
    ppu_on_all();
    while(1){
        ppu_wait_nmi();

        pad1 = pad_poll(0);

        if(pad1 & PAD_LEFT)
            player_x--;
        if(pad1 & PAD_RIGHT)
            player_x++;
        

        if(pad1 & PAD_UP)
            player_y--;
        if(pad1 & PAD_DOWN)
            player_y++;
        oam_meta_spr(player_x, player_y,0, frisk_down_0);
    }
}