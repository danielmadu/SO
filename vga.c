#include<system.h>

unsigned short *textmemptr;
int attrib = 0x02; //Atributos para cor de fundo e cor do caractere
int csr_x = 0, csr_y = 0;
/////////////////////////////////////////////////////////////////////////
/* Rola a tela */
void scroll(void)
{
    unsigned blank, temp;

    /* Um vazio � definido com um espa�o... n�s devemos por isto
    *  com a cor de fundo tamb�m */
    blank = 0x20 | (attrib << 8);

    /* Linha 25 � o fim, estes n�s s�o necess�rios para rolar para cima */
    if(csr_y >= 25)
    {
        /* Move o peda�o de texto corrente para cima da tela
        *  para fazer o buffer voltar linha */
        temp = csr_y - 25 + 1;
        memcpy (textmemptr, textmemptr + temp * 80, (25 - temp) * 80 * 2);

        /* Finalmente, n�s atribu�mos o peda�o de mem�ria que ocupa
        *  a ultima linha do texto para nosso caractere 'vazio' */
        memsetw (textmemptr + (25 - temp) * 80, blank, 80);
        csr_y = 25 - 1;
    }
}
////////////////////////////////////////////////////////////////////////
/* Atualiza o cursor do hardware: a pequena linha piscando
*  na tela sobre o ultimo caractere pressionado! */
void move_csr(void)
{
    unsigned temp;

    /* A equa��o para descobrir o �ndice de um peda�o
    *  linear da mem�ria pode ser representada por:
    *  �ndice = [(y * largura) + x] */
    temp = csr_y * 80 + csr_x;

    /* Este manda um comando para os �ndices 14 e 15 no
    *  Registrado de Controle CRT do controle VGA. Esses
    *  s�o os bytes superior e inferior do �ndice que mostra
    *  onde o cursor do hardware est� 'piscando'. Para
    *  aprender mais, voc� deveria procurar alguns documentos espec�ficos
    *  de programa��o para VGA. Um grande come�o para gr�ficos:
    *  http://www.brackeen.com/home/vga */
    outportb(0x3D4, 14);
    outportb(0x3D5, temp >> 8);
    outportb(0x3D4, 15);
    outportb(0x3D5, temp);
}
////////////////////////////////////////////////////////////////////

/* Limpa a tela */
void cls()
{
    unsigned blank;
    int i;

    /* Outra vez, n�s necessitamos o 'short' que vai ser usada para
    *  representar um espa�o com cor */
    blank = 0x20 | (attrib << 8);

    /* Atribui a tela inteira com espa�os para nossa cor
    *  corrente */
    for(i = 0; i < 25; i++)
        memsetw (textmemptr + i * 80, blank, 80);

    /* Atualiza o cursor virtual, e ent�o move o
    *  cursor do hardware */
    csr_x = 0;
    csr_y = 0;
    move_csr();
}
////////////////////////////////////////////////////////////////////
/* Coloca um caractere �nico na tela */
void putch(unsigned char c)
{
    unsigned short *where;
    unsigned att = attrib << 8;

    /* Trata um backspace, recuando o cursor um espa�o */
    if(c == 0x08)
    {
        if(csr_x != 0) csr_x--;
    }
    /* Trata um tab incrementando o cursor x, mas somente
    *  para um ponto que seja divis�vel por 8 */
    else if(c == 0x09)
    {
        csr_x = (csr_x + 8) & ~(8 - 1);
    }
    /* Trata um 'Retorno de Carruagem', que simplesmente traz o
    *  cursor novamente para a margem */
    else if(c == '\r')
    {
        csr_x = 0;
    }
    /* N�s tratamos nossas novas linhas (newlines) do mesmo modo do DOS e BIOS fazem: n�s
    *  trataremos isso como se um 'CR' estivesse l� tamb�m, assim n�s trazemos o
    *  cursor para a margem e n�s incrementamos o valor 'y' */
    else if(c == '\n')
    {
        csr_x = 0;
        csr_y++;
    }
    /* Qualquer caractere maior que e incluindo um espa�o, � um
    *  caractere que pode ser impresso. A equa��o para achar o �ndice
    *  em um peda�o da mem�ria linear pode ser representado por:
    *  �ndice = [(y * largura) + x] */
    else if(c >= ' ')
    {
        where = textmemptr + (csr_y * 80 + csr_x);
        *where = c | att;	/* Caractere E atributos: cor */
        csr_x++;
    }

    /* Se o cursor alcan�ou a margem de largura da tela, n�s
    *  inserimos uma nova linha l� */
    if(csr_x >= 80)
    {
        csr_x = 0;
        csr_y++;
    }

    /* Rola a tela se necess�rio, e finalmente move o cursor */
    scroll();
    move_csr();
}

/////////////////////////////////////////////////////////////////////
/* Usa a rotina acima para escrever uma string... */
void puts(unsigned char *text)
{ /*
    int i;

    for (i = 0; i < strlen(*text); i++)
    {
        putch(text[i]);
    } */
    while (*text)
{
        putch(*text);
        text++;
}
} 


////////////////////////////////////////////////////////////////////
/* Atribui o primeiro plano e o fundo que n�s usaremos */
void settextcolor(unsigned char forecolor, unsigned char backcolor)
{
    /* Top 4 bytes are the background, bottom 4 bytes
    *  are the foreground color */
    attrib = (backcolor << 4) | (forecolor & 0x02);
}
///////////////////////////////////////////////////////////////////
/* Atribui nosso ponteiro de modo-texto VGA, ent�o limpa a tela para n�s */
void init_video(void)
{
    textmemptr = (unsigned short *)0xB8000;
    cls();
}
///////////////////////////////////////////////////////////////////

