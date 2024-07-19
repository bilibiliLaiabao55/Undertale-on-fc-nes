;
; File generated by cc65 v 2.19 - Git 216bb22
;
	.fopt		compiler,"cc65 v 2.19 - Git 216bb22"
	.setcpu		"6502"
	.smart		on
	.autoimport	on
	.case		on
	.debuginfo	off
	.importzp	sp, sreg, regsave, regbank
	.importzp	tmp1, tmp2, tmp3, tmp4, ptr1, ptr2, ptr3, ptr4
	.macpack	longbranch
	.forceimport	__STARTUP__
	.import		_pal_all
	.import		_ppu_wait_nmi
	.import		_ppu_off
	.import		_ppu_on_all
	.import		_oam_clear
	.import		_oam_meta_spr
	.import		_pad_poll
	.export		_player_x
	.export		_player_y
	.export		_pad1
	.export		_frisk_frame
	.export		_frisk_frame_wait
	.export		_frisk_face
	.export		_palette
	.export		_frisk_down_0_data
	.export		_frisk_down_1_data
	.export		_frisk_down_2_data
	.export		_frisk_down_3_data
	.export		_frisk_down
	.export		_frisk_frame_change
	.export		_main

.segment	"DATA"

_player_x:
	.byte	$00
_player_y:
	.byte	$00
_frisk_frame:
	.byte	$00
_frisk_frame_wait:
	.byte	$00
_frisk_face:
	.byte	$00

.segment	"RODATA"

_palette:
	.byte	$14
	.byte	$30
	.byte	$24
	.byte	$19
	.byte	$14
	.byte	$1C
	.byte	$15
	.byte	$2A
	.byte	$14
	.byte	$06
	.byte	$27
	.byte	$2C
	.byte	$14
	.byte	$06
	.byte	$27
	.byte	$2C
	.byte	$14
	.byte	$06
	.byte	$27
	.byte	$2C
	.byte	$14
	.byte	$06
	.byte	$27
	.byte	$2C
	.byte	$14
	.byte	$06
	.byte	$27
	.byte	$2C
	.byte	$14
	.byte	$06
	.byte	$27
	.byte	$2C
_frisk_down_0_data:
	.byte	$00
	.byte	$00
	.byte	$01
	.byte	$00
	.byte	$08
	.byte	$00
	.byte	$02
	.byte	$00
	.byte	$00
	.byte	$08
	.byte	$03
	.byte	$00
	.byte	$08
	.byte	$08
	.byte	$04
	.byte	$00
	.byte	$00
	.byte	$10
	.byte	$05
	.byte	$00
	.byte	$08
	.byte	$10
	.byte	$06
	.byte	$00
	.byte	$00
	.byte	$18
	.byte	$07
	.byte	$00
	.byte	$08
	.byte	$18
	.byte	$08
	.byte	$00
	.byte	$80
_frisk_down_1_data:
	.byte	$00
	.byte	$00
	.byte	$01
	.byte	$00
	.byte	$08
	.byte	$00
	.byte	$02
	.byte	$00
	.byte	$00
	.byte	$08
	.byte	$03
	.byte	$00
	.byte	$08
	.byte	$08
	.byte	$04
	.byte	$00
	.byte	$00
	.byte	$10
	.byte	$09
	.byte	$00
	.byte	$08
	.byte	$10
	.byte	$06
	.byte	$00
	.byte	$00
	.byte	$18
	.byte	$0A
	.byte	$00
	.byte	$08
	.byte	$18
	.byte	$0B
	.byte	$00
	.byte	$80
_frisk_down_2_data:
	.byte	$00
	.byte	$00
	.byte	$01
	.byte	$00
	.byte	$08
	.byte	$00
	.byte	$02
	.byte	$00
	.byte	$00
	.byte	$08
	.byte	$03
	.byte	$00
	.byte	$08
	.byte	$08
	.byte	$04
	.byte	$00
	.byte	$00
	.byte	$10
	.byte	$05
	.byte	$00
	.byte	$08
	.byte	$10
	.byte	$06
	.byte	$00
	.byte	$00
	.byte	$18
	.byte	$07
	.byte	$00
	.byte	$08
	.byte	$18
	.byte	$08
	.byte	$00
	.byte	$80
_frisk_down_3_data:
	.byte	$00
	.byte	$00
	.byte	$01
	.byte	$00
	.byte	$08
	.byte	$00
	.byte	$02
	.byte	$00
	.byte	$00
	.byte	$08
	.byte	$03
	.byte	$00
	.byte	$08
	.byte	$08
	.byte	$04
	.byte	$00
	.byte	$00
	.byte	$10
	.byte	$05
	.byte	$00
	.byte	$08
	.byte	$10
	.byte	$0C
	.byte	$00
	.byte	$00
	.byte	$18
	.byte	$0D
	.byte	$00
	.byte	$08
	.byte	$18
	.byte	$0E
	.byte	$00
	.byte	$80
_frisk_down:
	.addr	_frisk_down_0_data
	.addr	_frisk_down_1_data
	.addr	_frisk_down_2_data
	.addr	_frisk_down_3_data

.segment	"BSS"

_pad1:
	.res	1,$00

; ---------------------------------------------------------------
; void __near__ frisk_frame_change (void)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_frisk_frame_change: near

.segment	"CODE"

;
; if (frisk_frame_wait == 10){
;
	ldx     #$00
	lda     _frisk_frame_wait
	cmp     #$0A
	jsr     booleq
	jeq     L0002
;
; frisk_frame_wait=0;
;
	ldx     #$00
	lda     #$00
	sta     _frisk_frame_wait
;
; if(frisk_frame<3)
;
	ldx     #$00
	lda     _frisk_frame
	cmp     #$03
	jsr     boolult
	jeq     L0003
;
; frisk_frame = frisk_frame+1;
;
	ldx     #$00
	lda     _frisk_frame
	jsr     incax1
	ldx     #$00
	sta     _frisk_frame
;
; else
;
	jmp     L0004
;
; frisk_frame = 0;
;
L0003:	ldx     #$00
	lda     #$00
	sta     _frisk_frame
;
; else
;
L0004:	jmp     L0005
;
; frisk_frame_wait = frisk_frame_wait + 1;
;
L0002:	ldx     #$00
	lda     _frisk_frame_wait
	jsr     incax1
	ldx     #$00
	sta     _frisk_frame_wait
;
; }
;
L0005:	rts

.endproc

; ---------------------------------------------------------------
; void __near__ main (void)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_main: near

.segment	"CODE"

;
; ppu_off();
;
	jsr     _ppu_off
;
; pal_all(palette);
;
	lda     #<(_palette)
	ldx     #>(_palette)
	jsr     _pal_all
;
; ppu_on_all();
;
	jsr     _ppu_on_all
;
; while(1){
;
	jmp     L0004
;
; ppu_wait_nmi();
;
L0002:	jsr     _ppu_wait_nmi
;
; pad1 = pad_poll(0);
;
	lda     #$00
	jsr     _pad_poll
	sta     _pad1
;
; if(pad1 & PAD_LEFT){
;
	ldx     #$00
	lda     _pad1
	ldx     #$00
	and     #$02
	stx     tmp1
	ora     tmp1
	jeq     L0005
;
; player_x=player_x-1;
;
	ldx     #$00
	lda     _player_x
	jsr     decax1
	ldx     #$00
	sta     _player_x
;
; else if(pad1 & PAD_RIGHT){
;
	jmp     L0007
L0005:	ldx     #$00
	lda     _pad1
	ldx     #$00
	and     #$01
	stx     tmp1
	ora     tmp1
	jeq     L0007
;
; player_x=player_x+1;
;
	ldx     #$00
	lda     _player_x
	jsr     incax1
	ldx     #$00
	sta     _player_x
;
; if(pad1 & PAD_UP){
;
L0007:	ldx     #$00
	lda     _pad1
	ldx     #$00
	and     #$08
	stx     tmp1
	ora     tmp1
	jeq     L0008
;
; player_y=player_y-1;
;
	ldx     #$00
	lda     _player_y
	jsr     decax1
	ldx     #$00
	sta     _player_y
;
; else if(pad1 & PAD_DOWN){
;
	jmp     L000A
L0008:	ldx     #$00
	lda     _pad1
	ldx     #$00
	and     #$04
	stx     tmp1
	ora     tmp1
	jeq     L000A
;
; player_y=player_y+1;
;
	ldx     #$00
	lda     _player_y
	jsr     incax1
	ldx     #$00
	sta     _player_y
;
; if(!(pad1 & PAD_LEFT)&&!(pad1 & PAD_RIGHT)&&!(pad1 & PAD_UP)&&!(pad1 & PAD_DOWN)){
;
L000A:	ldx     #$00
	lda     _pad1
	ldx     #$00
	and     #$02
	jsr     bnegax
	jeq     L000C
	ldx     #$00
	lda     _pad1
	ldx     #$00
	and     #$01
	jsr     bnegax
	jeq     L000C
	ldx     #$00
	lda     _pad1
	ldx     #$00
	and     #$08
	jsr     bnegax
	jeq     L000C
	ldx     #$00
	lda     _pad1
	ldx     #$00
	and     #$04
	jsr     bnegax
	jne     L000D
L000C:	ldx     #$00
	lda     #$00
	jeq     L000E
L000D:	ldx     #$00
	lda     #$01
L000E:	jeq     L000B
;
; frisk_frame=0;
;
	ldx     #$00
	lda     #$00
	sta     _frisk_frame
;
; frisk_frame_wait=0;
;
	ldx     #$00
	lda     #$00
	sta     _frisk_frame_wait
;
; else
;
	jmp     L000F
;
; frisk_frame_change();
;
L000B:	jsr     _frisk_frame_change
;
; oam_clear();
;
L000F:	jsr     _oam_clear
;
; oam_meta_spr(player_x, player_y , frisk_down[frisk_frame]);
;
	lda     _player_x
	jsr     pusha
	lda     _player_y
	jsr     pusha
	ldx     #$00
	lda     _frisk_frame
	jsr     aslax1
	clc
	adc     #<(_frisk_down)
	tay
	txa
	adc     #>(_frisk_down)
	tax
	tya
	ldy     #$01
	jsr     ldaxidx
	jsr     _oam_meta_spr
;
; while(1){
;
L0004:	jmp     L0002
;
; }
;
	rts

.endproc

