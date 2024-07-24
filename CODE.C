#include "lib/LIB/neslib.h"
#include "lib/LIB/nesdoug.h"
#include "lib/MMC3/mmc3_code.h"
#include "lib/MMC3/mmc3_code.c"
#include <stdlib.h>

#pragma bss-name(push, "ZEROPAGE")
unsigned char player_x=120;
unsigned char player_y=0xC0;
unsigned char pad1;
unsigned char frisk_frame=0;
unsigned char frisk_frame_wait=0;
unsigned char frisk_face=1;//0=down,1=up,2=left,3=right
unsigned char map_frisk_collison=0x00;
unsigned char state;
unsigned char steps;
unsigned char timer0=0;
unsigned char timer1=0;
unsigned char timer2=0;
unsigned char scroll_x=0;
unsigned char scroll_y=0;
unsigned char pal_had_fade_not=0;
unsigned char temp0=0;
unsigned char temp1=0;
unsigned char battle_choosen=0;
unsigned char keys_pressed=0;
//00000000
//++++++++
//||||||||
//|||||||a
//||||||b
//|||||l
//||||r
//|||u
//||d
//|l
//r
//a=a b=b l=select r=start u=up d=down l=left r=rights
#pragma bss-name(pop)

#pragma bss-name(push, "XRAM")
unsigned char wram_array[0x2000];

#pragma bss-name(pop)


struct Box2D frisk_map_box;

const char LEFT_COLLISON = 0x01;
const char RIGHT_COLLISON = 0x02;
const char UP_COLLISON = 0x04;
const char DOWN_COLLISON = 0x08;
const char palette[]={
    0x0F,0x1A,0x30,0x30,
    0x0F,0x10,0x0F,0x27,
    0x0F,0x06,0x27,0x2C,
    0x0F,0x06,0x27,0x2C,

    0x0F,0x06,0x27,0x2C,
    0x0F,0x15,0x27,0x2A,
    0x0F,0x10,0x0F,0x27,
    0x0F,0x06,0x27,0x2C
};
struct Box2D {
    unsigned char x;
    unsigned char y;
    unsigned char width;
    unsigned char height;
};
void save(){
    wram_array[0]=0;
    wram_array[1]=0;
    wram_array[2]=0;
    wram_array[3]=0;
    wram_array[4]=0;
    wram_array[5]=0;
    wram_array[6]=0;
    wram_array[7]=0;
    wram_array[8]=0;
}

#pragma rodata-name ("BANK0")
#pragma code-name ("BANK0")
#include "FRISK.C"
#include "FLOWEY.C"
#include "toriel.C"
//sprite bank
void set_frisk(){
    oam_meta_spr(player_x, player_y , frisk[frisk_face][frisk_frame]);
}
void set_die_soul(){
    oam_spr(player_x, player_y+8 ,0x26,1);
    oam_spr(player_x+8, player_y+8 ,0x27,1);
}
void set_soul(){
    oam_spr(player_x,player_y,0x25, 1);
}
#pragma rodata-name ("BANK1")
#pragma code-name ("BANK1")
#include "bgs/title.h"
//bg bank
void clear_background(){
    ppu_off();
    vram_adr(NAMETABLE_A);
    vram_fill(0x00,960);
    ppu_on_all();
}
void set_fight_bg(){
    ppu_off();
    vram_adr(NAMETABLE_A);
    for(temp1=0;temp1<9;temp1++){
        for(temp0=0;temp0<16;temp0++){
            vram_put(0x5E);
            vram_put(0x67);
        }
        for(temp0=0;temp0<16;temp0++){
            vram_put(0x68);
            vram_put(0x69);
        }
    }
    vram_put(0x5F);
    vram_fill(0x60, 30);
    vram_put(0x61);
    for(temp0=0;temp0<6;temp0++){
        vram_put(0x66);
        vram_fill(0x00, 30);
        vram_put(0x62);
    }
    vram_put(0x64);
    vram_fill(0x65, 30);
    vram_put(0x63);

    vram_fill(0x00, 35);

    vram_put(0x6A);
    vram_put(0x6B);
    vram_put(0x6C);
    vram_put(0x6D);
    vram_put(0x6E);
    vram_fill(0x00, 2);
    vram_put(0x74);
    vram_put(0x75);
    vram_put(0x76);
    vram_put(0x77);
    vram_put(0x78);
    vram_fill(0x00, 2);
    vram_put(0x7E);
    vram_put(0x7F);
    vram_put(0x80);
    vram_put(0x81);
    vram_put(0x82);
    vram_fill(0x00, 2);
    vram_put(0x88);
    vram_put(0x89);
    vram_put(0x8A);
    vram_put(0x8B);
    vram_put(0x8C);
    vram_fill(0x00, 6);

    vram_put(0x6F);
    vram_put(0x70);
    vram_put(0x71);
    vram_put(0x72);
    vram_put(0x73);
    vram_fill(0x00, 2);
    vram_put(0x79);
    vram_put(0x7A);
    vram_put(0x7B);
    vram_put(0x7C);
    vram_put(0x7D);
    vram_fill(0x00, 2);
    vram_put(0x83);
    vram_put(0x84);
    vram_put(0x85);
    vram_put(0x86);
    vram_put(0x87);
    vram_fill(0x00, 2);
    vram_put(0x8D);
    vram_put(0x8E);
    vram_put(0x8F);
    vram_put(0x90);
    vram_put(0x91);
    vram_fill(0x00, 38);
    ppu_on_all();
}
void set_title(){
    ppu_off();
    vram_unrle(title);
    ppu_on_all();
}
#pragma rodata-name ("BANK2")
#pragma code-name ("BANK2")
//fight bank
void check_set_soul(){
    sfx_play(11, 0);
    if(battle_choosen==0){
        player_x=25;
    }
    if(battle_choosen==1){
        player_x=81;
    }
    if(battle_choosen==2){
        player_x=137;
    }
    if(battle_choosen==3){
        player_x=193;
    }
}
void init_fight(){
    state=2;
    player_y=220;
    banked_call(2,check_set_soul);
    music_stop();
    music_play(4);
    banked_call(1,clear_background);
    oam_clear();
    banked_call(1,set_fight_bg);
}
void frames_funcion(){
    if(pad1 & PAD_LEFT){
        
        if(!(keys_pressed & 1<<6)){
            banked_call(2,check_set_soul);
            if(battle_choosen==0)
                battle_choosen=4;
            battle_choosen--;
        }
        keys_pressed|= (1 << 6);
    }
    else
        keys_pressed&= ~(1 << 6);
    if(pad1 & PAD_RIGHT){
        
        if(!(keys_pressed & 1<<7)){
            banked_call(2,check_set_soul);
            battle_choosen++;
            if(battle_choosen==4)
            battle_choosen=0;
        }
        keys_pressed|= (1 << 7);
    }
    else
        keys_pressed&= ~(1 << 7);

    
    oam_clear();
    banked_call(0,set_soul);
}


#pragma rodata-name ("BANK3")
#pragma code-name ("BANK3")
//event bank
#pragma rodata-name ("CODE")
#pragma code-name ("CODE")	

void frisk_frame_change(){
    if (frisk_frame_wait == 10){
        steps++;
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
    //music_play(0);
    sfx_play(1, 0);
    ppu_off();
    set_vram_buffer();
    
    banked_call(1, set_title);
    disable_irq();
    pal_all(palette);
    ppu_on_all();
    pal_fade_to(0,4);
	frisk_map_box.width=16;
	frisk_map_box.height=8;
    
    while(1){
        
        ppu_wait_nmi();
        if(timer0>0){
            timer0 -= 1;
        }
        if(timer1>0){
            timer1 -= 1;
            }
        if(timer2>0){
            timer2 -= 1;
        }
        pad1 = pad_poll(0);
        if(state == 0){
            if(pad1 & PAD_START){
                //music_stop();
                music_play(1);
                pal_fade_to(4,8);
                state = 1;
                ppu_off();
                vram_adr(NAMETABLE_A);
                vram_fill(0x01,960);
                ppu_on_all();
            }
        }
        if(state == 1){
            map_frisk_collison=0;
            frisk_map_box.x = player_x;
            frisk_map_box.y = player_y+24;
            set_scroll_x(scroll_x);
            set_scroll_y(scroll_y);
            oam_clear();
            banked_call(0, set_frisk);
            if(pal_had_fade_not == 0){
                pal_fade_to(8,4);
                pal_had_fade_not = 1;
            }
            if((pad1 & PAD_LEFT)&&(player_x>=0x02)){
                //set_mirroring(MIRROR_HORIZONTAL);
                //scroll_x = scroll_x - 1;
                frisk_face = 2;
                player_x=player_x-1;
            }
            else if((pad1 & PAD_RIGHT)&&(player_x<=0xF0)){
                //set_mirroring(MIRROR_HORIZONTAL);
                //scroll_x = scroll_x + 1;
                frisk_face = 3;
                player_x=player_x+1;
            }

            if((pad1 & PAD_UP)&&(player_y>=0x02)){
                //set_mirroring(MIRROR_VERTICAL);
                //scroll_y = sub_scroll_y(1,scroll_y);
                frisk_face = 1;
                player_y=player_y-1;
            }
            else if((pad1 & PAD_DOWN)&&(player_y<=0xC5)){
                //set_mirroring(MIRROR_VERTICAL);
                //scroll_y = add_scroll_y(1,scroll_y);
                frisk_face = 0;
                player_y=player_y+1;

            }
            if(pad1 & PAD_SELECT){
                state = 3;
                timer0 = 60;
                oam_clear();
                music_stop();
            }
            if(pad1 & PAD_START){
                banked_call(2,init_fight);
            }
            if(!(pad1 & PAD_LEFT)&&!(pad1 & PAD_RIGHT)&&!(pad1 & PAD_UP)&&!(pad1 & PAD_DOWN)){
                frisk_frame = 0;
                frisk_frame_wait = 0;
            }
            else
                frisk_frame_change();

        }
        if(state == 2){
            banked_call(2,frames_funcion);
        }
        if(state == 3){
            if(timer0==60){
                banked_call(1, clear_background);
                banked_call(0,set_die_soul);
                sfx_play(2, 0);
            }
            if(timer0==1){
                oam_clear();
                sfx_play(3, 0);
            }
            if(timer0==0){
                if(pad1 & PAD_START){
                    state=1;
                    ppu_off();
                    vram_adr(NAMETABLE_A);
                    vram_fill(0x01,960);
                    ppu_on_all();
                }
            }
        }
    }
}