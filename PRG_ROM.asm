
PPU_CTRL = $2000
PPU_MASK = $2001
PPU_STATUS = $2002

PPU_ADDR = $2006
PPU_DATA = $2007

OAM_ADDR = $2003
OAM_DATA = $2004
OAM_DMA = $4014


.segment "HEADER"
    .BYTE "NES",$1A ;文件头 NES<EOF>
    .BYTE $02   ;2个16kb的代码 $开始表示16进制数字 默认看做地址
    .BYTE $01   ;1个8kb的chr
; Code
.segment "CODE"
RESET:
    LDA #$0F
    STA PLAYER_X
    STA PLAYER_Y
    SEI
    CLD

VBLANKWAIT1:
    LDA PPU_STATUS
    BPL VBLANKWAIT1

VBLANKWAIT2:
    LDA PPU_STATUS
    BPL VBLANKWAIT2

LOAD_PAL:
    LDA PPU_STATUS
    LDA #$3F
    STA PPU_ADDR
    LDA #$00
    STA PPU_ADDR
    LDX #$00
:   LDA PALDATA,X
    STA PPU_DATA
    INX 
    CPX #$20
    BNE :- 




LOAD_SPRITE:
    lda FRISK_DOWN
    sta ANI_ADDR
    lda FRISK_DOWN + 1
    sta ANI_ADDR + 1
    lda #$00
    sta SPR_ADDR
    lda #$02
    sta SPR_ADDR+1
    lda #$00
    sta OAM_USED

:   ldy #$00 
    lda (ANI_ADDR),y
    adc PLAYER_X
    ldy #$03
    sta (SPR_ADDR),y

    ldy #$01 
    lda (ANI_ADDR),y
    adc PLAYER_Y
    ldy #$00
    sta (SPR_ADDR),y

    ldy #$02 
    lda (ANI_ADDR),y
    ldy #$01
    sta (SPR_ADDR),y
    ldy #$03 
    lda (ANI_ADDR),y
    ldy #$02
    sta (SPR_ADDR),y
    lda ANI_ADDR
    clc
    adc #$04
    sta ANI_ADDR

    lda ANI_ADDR + 1
    adc #$00
    sta ANI_ADDR + 1

    lda SPR_ADDR
    clc 
    adc #$04
    sta SPR_ADDR 

    inc OAM_USED
    lda OAM_USED
    cmp #$08
    bne :-

    
ENABLE_PPU:
    LDA #%10000000
    STA PPU_CTRL
    LDA #%00010000
    STA PPU_MASK

LOOP:
    JMP LOOP

NMI:
    LDA #$00
    STA OAM_ADDR
    LDA #$02
    STA OAM_DMA
    lda #$01    ;0000 00001
    sta $4016 
    sta buttons ;buttons = 0000 0001

    lsr A       ;0000 0000 > C = 1;A = 0
    sta $4016 ;

:   lda $4016 ;A = 0000 000 Button_A
    lsr A       ; C = Button_A;A=0000 0000
    rol buttons ; buttons = 0000 001 buttons[0] = C 
                ; C = 0 -->[A B SEL STATR UP DOWN LEFT RIGHT] ; C = 1
    bcc :-    ;

    READ_UP:
    lda buttons
    and #BUTTON_UP  ;A = UP键按键信息
    beq READ_DOWN   ;Z = 0
    jsr MoveSpriteUP
    RTS

PALDATA:
    .INCBIN "Palette.dat"

FRISK_DOWN_0:
	.byte   0,  0,$00,0
	.byte   8,  0,$01,0
	.byte   0,  8,$02,0
	.byte   8,  8,$03,0
	.byte   0, 16,$04,0
	.byte   8, 16,$05,0
	.byte   0, 23,$06,0
	.byte   8, 23,$07,0
	
FRISK_DOWN_1:
	.byte   0,  0,$00,0
	.byte   8,  0,$01,0
	.byte   0,  8,$02,0
	.byte   8,  8,$03,0
	.byte   0, 16,$08,0
	.byte   8, 16,$05,0
	.byte   0, 23,$09,0
	.byte   8, 23,$0a,0
	
FRISK_DOWN_2:
	.byte   0,  0,$00,0
	.byte   8,  0,$01,0
	.byte   0,  8,$02,0
	.byte   8,  8,$03,0
	.byte   0, 16,$04,0
	.byte   8, 16,$05,0
	.byte   0, 23,$06,0
	.byte   8, 23,$07,0
	
FRISK_DOWN_3:
	.byte   0,  0,$00,0
	.byte   8,  0,$01,0
	.byte   0,  8,$02,0
	.byte   8,  8,$03,0
	.byte   0, 16,$04,0
	.byte   8, 16,$0b,0
	.byte   0, 23,$0c,0
	.byte   8, 23,$0d,0
	
FRISK_DOWN:
	.word FRISK_DOWN_0
	.word FRISK_DOWN_1
	.word FRISK_DOWN_2
	.word FRISK_DOWN_3

.segment "ZEROPAGE"
    PLAYER_X: .res 1
    PLAYER_Y: .res 1
    ANI_ADDR: .res 2
    SPR_ADDR: .res 2
    OAM_USED: .res 1
    buttons: .res 1

.segment "VECTORS"  
    .WORD NMI,RESET,0   ;3个中断地址 NMI,RESET,IQR
; Chr
.segment "CHARS"
    .INCBIN "CHR_ROM.chr"