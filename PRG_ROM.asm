
PPU_CTRL = $2000
PPU_MASK = $2001
PPU_STATUS = $2002

PPU_ADDR = $2006
PPU_DATA = $2007

OAM_ADDR = $2003
OAM_DATA = $2004
OAM_DMA = $4014


.segment "HEADER"
    .byte "NES",$1A ;文件头 NES<EOF>
    .byte $02   ;2个16kb的代码 $开始表示16进制数字 默认看做地址
    .byte $01   ;1个8kb的chr
; Code
.segment "CODE"
RESET:
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

PALDATA:
    .incbin "FriskPalette.dat"

LOOP:
    JMP LOOP

.segment "VECTORS"  
    .word 0,RESET,0   ;3个中断地址 NMI,RESET,IQR
; Chr
.segment "CHARS"
    .incbin "CHR_ROM.chr"