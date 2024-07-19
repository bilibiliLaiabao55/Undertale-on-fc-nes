

cc65 -t nes CODE.c -o elsefiles/NOT_IMPORTANT/PRG_ROM.s --add-source 

@REM 编译 .s -> .o
ca65 lib\crt0.s
ca65 elsefiles/NOT_IMPORTANT/PRG_ROM.s -l elsefiles/NOT_IMPORTANT/OUT.txt -o elsefiles/NOT_IMPORTANT/UNDERTALE.o

@REM 链接器 .o -> .nes 使用内置的nes.cfg
ld65 -C elsefiles/NOT_IMPORTANT/nes.cfg lib\crt0.o elsefiles/NOT_IMPORTANT/UNDERTALE.o nes.lib -o EXPORT/UNDERTALE.nes

@REM del ch3.o

@REM 运行
CD EXPORT
UNDERTALE.NES

pause