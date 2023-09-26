[BITS 16]  ; C�digo de 16 bits
[ORG 0x7C00]  ; Origem do c�digo em 7C00
 
principal:  ; Marcador do in�cio do programa
 
    ; Limpar a tela
mov ah,0x07  ; Indica a rotina de rolagem de tela da BIOS
mov al,0x00  ; Rolar TODAS as linhas
mov bh,0x07  ; Texto branco em fundo preto
mov ch,0x00  ; Linha do canto superior esquerdo
mov cl,0x00  ; Coluna do canto superior esquerdo
mov dh,800  ; Linha do canto inferior direito (maior que a tela)
mov dl,1200  ; Coluna do canto inferior direito (maior que a tela)
int 0x10  ; Chamar a INT 10
 
    ; Posicionar o cursor
mov ah,0x02  ; Indica a rotina de posicionamento do cursor
mov bh,0x00  ; N�mero da p�gina de v�deo
mov dx,0x0000  ; Linha e coluna da nova posi��o do cursor (0,0)
int 0x10    ; Chamar a INT 10
 
mov ax,0x0000  ; Como n�o � poss�vel carregar diretamente DS
mov ds,ax  ; passamos o valor de ax para ds
mov si,StringSO  ; Ponteiro para o deslocamento da string
call PoeString  ; Chamar a rotina de impress�o
 
pendura:
  jmp pendura  ; Loop infinito
 
; Procedimentos
PoeString:  ; Marcador do in�cio da sub-rotina
  mov ah,0x0E  ; Indica a rotina de teletipo da BIOS
  mov bh,0x00  ; N�mero da p�gina de v�deo
  mov bl,0x07  ; Texto branco em fundo preto
 
  .proxCar  ; Marcador interno para in�cio do loop
    lodsb    ; Copia o byte em DS:SI para AL e incrementa SI
    or al,al  ; Verifica se al = 0
    jz .volta  ; Se al=0, string terminou e salta para .volta
    int 0x10  ; Se n�o, chama INT 10 para por caracter na tela
    jmp .proxCar  ; Vai para o in�cio do loop
 
  .volta
    ret    ; Retorna � rotina principal
 
; Dados
StringSO db 'Sistema Operacional MaduxSO Desenvolvido por Daniel Madureira Batista',13,10,0
 
; Para terminar
times 510-($-$$) db 0  ; Preenche o resto do setor com zeros
db 0x55,0xAA    ; P�e a assinatura do boot loader no final