MBOOT_PAGE_ALIGN EQU 1<<0  
MBOOT_MEMORY_INFO EQU 1<<1  
MBOOT_AOUT_KLUDGE EQU 1<<16  
MBOOT_HEADER_MAGIC EQU 0x1BADB002  
MBOOT_HEADER_FLAGS EQU MBOOT_PAGE_ALIGN | MBOOT_MEMORY_INFO | MBOOT_AOUT_KLUDGE  
MBOOT_CHECKSUM EQU -(MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)  
  
ALIGN 4  
mboot:  
dd MBOOT_HEADER_MAGIC  
dd MBOOT_HEADER_FLAGS  
dd MBOOT_CHECKSUM  
dd mboot    
dd _d_code    
dd _d_bss     
dd _end       
dd ncl_inicio  

[BITS 32]
[global start]
[extern _k_main]


start:
call _k_main

cli
hlt