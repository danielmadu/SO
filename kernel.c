#define BRANCO_TXT 0x07

void k_cls();
unsigned int k_printf(char *message,unsigned int linha);
void update_cursor(int linha, int coluna);

k_main()
{
k_cls();
k_printf("Kernel executado com sucesso!!!\nExito na exececucao.",0);
};

void k_cls()
{
char *vidmem = (char *) 0x8000;
unsigned int i=0;
while(i < (80*25*2)){
vidmem[i] = ' ';
i++;
vidmem[i] = BRANCO_TXT;
i++;
};
};

unsigned int k_printf(char *message, unsigned int linha) // a mensagem e então a linha #

{

char *vidmem = (char *) 0xb8000;

unsigned int i=0;

 

i=(linha*80*2);

 

while(*message!=0)

{

if(*message=='\n') // checa para nova linha

{

linha++;

i=(linha*80*2);

*message++;

} else {

vidmem[i]=*message;

*message++;

i++;

vidmem[i]=BRANCO_TXT;

i++;

};

};

 

return(1);

};