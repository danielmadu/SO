nasm -f aout inicio.asm -o inicio.o
gcc -Wall -nostdlib -nostdinc -fno-exceptions -fno-builtin -I./include/ -c nucleo.c -o nucleo.o
gcc -Wall -nostdlib -nostdinc -fno-exceptions -fno-builtin -I./include/ -c vga.c -o vga.o
ld -T link.ld -o kernel.bin inicio.o nucleo.o vga.o