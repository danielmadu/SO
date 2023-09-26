#include<system.h>
////////////////////////////////////////////////////////
unsigned char *memcpy(unsigned char *dest, const unsigned char *src, int count)
{
    const char *sp = (const char *)src;
    char *dp = (char *)dest;
    for(; count != 0; count--) *dp++ = *sp++;
    return dest;
}
///////////////////////////////////////////////////////
unsigned char *memset(unsigned char *dest, unsigned char val, int count)
{
    char *temp = (char *)dest;
    for( ; count != 0; count--) *temp++ = val;
    return dest;
}
///////////////////////////////////////////////////////
unsigned short *memsetw(unsigned short *dest, unsigned short val, int count)
{
    unsigned short *temp = (unsigned short *)dest;
    for( ; count != 0; count--) *temp++ = val;
    return dest;
}
//////////////////////////////////////////////////////
int strlen(const char *str)
{
        unsigned i=0;
        char *__s = (char *)str;

        while (*__s)
        {
            i++;
            __s++;
        }

        return i;
}
///////////////////////////////////////////////////////
unsigned char inportb (unsigned short _port)
{
    unsigned char rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}
////////////////////////////////////////////////////////
void outportb (unsigned short _port, unsigned char _data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}

////////////////////////////////////////////////////////
int main(){
init_video();
char nome[30] =  "Madux SO Kernel ver 0.0.1-a";
puts(&nome);

for(;;);

}

