
ca65 PRG_ROM.asm -l not_important/out.txt -o not_important/UNDERTALE.o
@REM 链接器 .o -> .nes
@REM ld65 --target nes demo.o -o ch4.nes 使用cc65自带的
ld65 --config not_important/nes.cfg not_important/UNDERTALE.o -o export/UNDERTALE.nes

fceux export/UNDERTALE.nes
pause