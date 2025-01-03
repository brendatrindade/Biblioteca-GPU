/*
Casos de Teste para mostrar o funcionamento da biblioteca criada.

Obs. para testar cada caso de teste na função main é necessário deixar somente 1 função sem comentar.
Obs. falta testar todos casos de testes e seu funcionamento
Obs. lembrar de modificar o makefile para testar os casos de teste
*/

#include "proc_grafico.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern void inicializa_fpga();
extern void fecha_dev_mem();
extern void desenha_poligono(uint16_t cor, uint16_t tamanho, uint16_t forma, uint16_t endereco);
extern void altera_cor_bg(uint16_t cor, uint8_t registrador);

extern void exibe_sprite(uint8_t sp, uint16_t x, uint16_t offset, uint8_t registrador);
extern void altera_pixel_sprite(uint16_t cor, uint16_t endereco);

//extern void escreve_bloco(uint16_t posicao, uint16_t cor);
//extern void apaga_bloco(uint16_t posicao);
//extern void startGame();

#define largura_sprite 20
#define altura_sprite 20

//Dados da imagem para formar um sprite (20x20) em formato RRRGGGBB - 1 byte por pixel
uint8_t dados_da_imagem[altura_sprite][largura_sprite] = {
{0x7b,0x7b,0x7b,0x61,0x61,0x61,0x61,0x61,0x61,0x61,0x61,0x61,0x61,0x61,0x61,0x61,0x61,0x7b,0x61,0x7b}, //0
{0x7b,0x61,0x61,0x61,0x61,0x61,0x61,0x00,0x00,0x00,0x00,0x00,0x00,0x61,0x61,0x61,0x61,0x7b,0x61,0x7b}, //1
{0x7b,0x61,0x61,0x61,0x61,0x61,0x00,0xb6,0xb6,0x00,0x00,0xb6,0xb6,0x00,0x61,0x61,0x61,0x7b,0x7b,0x7b}, //2
{0x7b,0x61,0x61,0x61,0x61,0x61,0x00,0xff,0x00,0xff,0xff,0x00,0xff,0x00,0x61,0x61,0x61,0x61,0x61,0x61}, //3
{0x7b,0x7b,0x7b,0x61,0x7b,0x61,0x00,0xff,0xff,0x49,0x49,0xff,0xff,0x00,0x61,0x61,0x61,0x7b,0x7b,0x7b}, //4
{0x61,0x61,0x61,0x61,0x61,0x61,0x00,0xff,0x49,0xf4,0xf4,0x49,0xff,0x00,0x61,0x61,0x61,0x7b,0x61,0x61}, //5
{0x7b,0x61,0x61,0x61,0x61,0x61,0x00,0xff,0xff,0x00,0x00,0xff,0xff,0x00,0x61,0x61,0x61,0x7b,0x61,0x61}, //6
{0x7b,0x61,0x61,0x61,0x61,0x61,0x00,0x49,0xff,0xff,0xff,0xff,0x49,0x00,0x61,0x61,0x61,0x7b,0x61,0x61}, //7
{0x7b,0x7b,0x7b,0x61,0x61,0x00,0x00,0x49,0x49,0xff,0xff,0x49,0x49,0x00,0x00,0x61,0x61,0x7b,0x7b,0x7b}, //8
{0x7b,0x61,0x7b,0x61,0x61,0x00,0x00,0x49,0xff,0xff,0xff,0xff,0x49,0x00,0x00,0x61,0x61,0x61,0x61,0x61}, //9
{0x7b,0x7b,0x7b,0x61,0x00,0x00,0x00,0xb6,0xb6,0xff,0xff,0xb6,0xb6,0x00,0x00,0x00,0x61,0x7b,0x61,0x7b}, //10
{0x61,0x61,0x61,0x61,0x00,0x00,0x00,0xb6,0xff,0xff,0xff,0xff,0xb6,0x00,0x00,0x00,0x61,0x7b,0x7b,0x61}, //11
{0x7b,0x61,0x61,0x00,0x00,0x00,0xb6,0xff,0xb6,0xff,0xff,0xb6,0xff,0xb6,0x00,0x00,0x00,0x7b,0x61,0x7b}, //12
{0x7b,0x61,0x61,0x00,0x00,0x00,0xb6,0xb6,0xff,0xff,0xff,0xff,0xb6,0xb6,0x00,0x00,0x00,0x7b,0x61,0x7b}, //13
{0x7b,0x61,0x61,0x00,0x00,0x00,0xb6,0xff,0xb6,0xff,0xff,0xb6,0xff,0xb6,0x00,0x00,0x00,0x61,0x61,0x61}, //14
{0x7b,0x61,0x61,0x00,0x61,0x00,0x49,0xb6,0xff,0xff,0xff,0xff,0xb6,0x49,0x00,0x61,0x00,0x61,0x51,0x51}, //15
{0x7b,0x7b,0x7b,0x61,0x61,0x00,0x49,0x49,0xb6,0xff,0xff,0xb6,0x49,0x49,0x00,0x61,0x61,0x61,0x51,0x51}, //16
{0x61,0x61,0x61,0x61,0x61,0x61,0x00,0x49,0x00,0x00,0x00,0x00,0x49,0x00,0x61,0x61,0x61,0x61,0x61,0x61}, //17
{0x7b,0x7b,0x7b,0x61,0x61,0xf4,0xf4,0xf4,0x61,0x61,0x61,0x61,0xf4,0xf4,0xf4,0x61,0x61,0xe0,0xe0,0x61}, //18
{0x7b,0x61,0x7b,0x61,0x61,0x61,0x61,0x61,0x61,0x61,0x61,0x61,0x61,0x61,0x61,0x61,0x61,0xe0,0xe0,0x61}  //19
};

//Converte os dados da imagem de RGB para BGR 9 bits - formato da instrucao wsm
uint16_t converte_em_bgr(uint8_t rgb) {
    uint8_t r, g, b;
    uint16_t bgr;

    //Extrai cada tom (R, G e B) do formato RGB
    r = (rgb >> 5) & 0b111; // 3 bits msb do vermelho
    g = (rgb >> 2) & 0b111; // 3 bits do meio do verde
    b = rgb & 0b11; // 2 bits lsb do azul
    //ajusta o azul de 2 para 3 bits
    b = b << 1;

    //Coloca no formato BBB GGG RRR de 9 bits
    bgr = ( (b << 6) | (g << 3) | r );

    return bgr;
}

//Cria e armazena um sprite na memoria de sprites
void cria_sprite(uint16_t end_base, uint16_t dados_do_sprite[altura_sprite][largura_sprite]) {
    uint16_t cor[400]; //20x20 -> 400 pixels por sprite
    int y, x;
    int z = 0;
    for ( y = 0; y < altura_sprite; y++) {
        for ( x = 0; x < largura_sprite; x++) {
            cor[z] = dados_do_sprite[y][x]; //Extrai a cor de cada pixel em 9 bits BGR
            z++;
        }
    }
    //Escreve cada pixel da matriz 20x20 na memoria de sprites
    int i = 0;
    while (i < 400){
        altera_pixel_sprite(cor[i], end_base + i);
        i++;
        usleep(10000);
    }
}

//Exibe e move um sprite armazenado na memoria de sprites pela tela
void move_sprite() {
    #define mascara_10bits 0b1111111111
    uint16_t pos_x = 350;
    uint16_t pos_y = 240;

    pos_x &= mascara_10bits;
    pos_y &= mascara_10bits;
    
    uint32_t pos_xy_20b;
    pos_xy_20b = (pos_x << 10 | pos_y);
    uint32_t pos_xy_20b_ant = (pos_xy_20b); //inicia com posicao anterior igual a posicao atual

    int direcao_sprite = 1; //1 descendo e -1 subindo
    int i = 0;

    while (i < 1000) {
        //apaga o sprite exibido na posicao anterior
        exibe_sprite(0, pos_xy_20b_ant, 5, 1);//sp = 0 - desabilita sprite
        pos_xy_20b_ant = pos_xy_20b;
    
        //exibe o sprite na posicao atual
        exibe_sprite(1, pos_xy_20b, 5, 1);//sp = 1 - habilita sprite

        //verifica os limites da tela para ajustar a direcao
        //tela 640 x 480
        if (direcao_sprite == 1 && (pos_xy_20b < 358850) ){
            pos_xy_20b+= 10;//posicao atual + 10
            if(pos_xy_20b == 358850){
                //101011110 0111000010 -> x = 0101011110 = 350, y = 0111000010 = 450
                direcao_sprite = -1;
            }
        }

        else if (direcao_sprite == -1 && (pos_xy_20b > 358410) ){
            pos_xy_20b-=10;//posicao atual - 10
            if(pos_xy_20b == 358410){
                //0101011110 0000001010 -> x = 0101011110 = 350, y = 0000001010 = 10
                direcao_sprite = 1;
            }
        }
        usleep(10000);
        i++;
    }
}

//Instrução DP
void caso_teste_1(){
    inicializa_fpga();

    //definindo mascara de bits para a posição
    #define mascara_09bits 0b111111111

    //para tamanho 1 menor x,y = 10,10
    uint16_t pos_x = 10;
    uint16_t pos_y = 10;

    pos_x &= mascara_09bits;
    pos_y &= mascara_09bits;
    uint32_t pos_xy_18b;
    pos_xy_18b = (pos_x << 9 | pos_y);

    //OBS: para apagar o poligono passa tamanho 0
    desenha_poligono(ROXO, 1, 1, pos_xy_18b); //cor, tamanho, forma, xy
    fecha_dev_mem();
}

//Instrução WBR para backgraund
void caso_teste_2(){
    inicializa_fpga();

    //OBS: para apagar o BG passa a cor como 000
    altera_cor_bg(PRETO, 0); //cor, registrador
    fecha_dev_mem();
}

//Instrução WBR para sprite
void caso_teste_3(){
    inicializa_fpga();
    move_sprite();
    fecha_dev_mem();
}

//Instrução WSM para sprite
void caso_teste_4(){
    inicializa_fpga();

    #define mascara_10bits 0b1111111111
    uint16_t pos_x = 350;
    uint16_t pos_y = 320;

    pos_x &= mascara_10bits;
    pos_y &= mascara_10bits;
    
    uint32_t pos_xy_20b;
    pos_xy_20b = (pos_x << 10 | pos_y);

    //Dados para formar um sprite 20x20 em formato RRR GGG BBB - 9 bits
    uint16_t dados_do_sprite[altura_sprite][largura_sprite];

    int y, x;
    for ( y = 0; y < altura_sprite; y++) {
        for ( x = 0; x < largura_sprite; x++) {
            dados_do_sprite[y][x] = converte_em_bgr(dados_da_imagem[y][x]);//Converte pixel por pixel do formato RGB para o BGR
        }
    }

    //Escreve os dados de cada pixel na memoria de sprites. [end_base = offset * 400]
    cria_sprite(1600, dados_do_sprite);

    //Exibe o sprite criado identificado por offset na posicao xy
    exibe_sprite(1, pos_xy_20b, 4, 1);
    fecha_dev_mem();
}

int main() {

    /* 
    Caso de Teste 1: Instrução DP
    Esse primeiro caso de teste tem por objetivo desenhar um poligono na tela, seja triangulo ou quadrado.
    Utilizamos a instrução desenha_poligono da nossa blibioteca.
    triangulo > 1 e quadrado > 0
    */
    caso_teste_1(); //OK E TESTADA NO LEDS


    /* 
    Caso de Teste 2: Instrução WBR para alterar o backgraund
    Esse segundo caso de teste tem por objetivo mudar a cor do backgraund usando o WBR.
    */
    //caso_teste_2(); //OK E TESTADO NO LEDS


    /* 
    Caso de Teste 3: Instrução WBR para exibir sprite
    Esse segundo caso de teste tem por objetivo exibir na tela um sprite usando o WBR.
    */
    //caso_teste_3(); //OK E TESTADO NO LEDS


    /* 
    Caso de Teste 4: Instrução WSM para armazena ou modifica o conteúdo presente na Memória de Sprite
    Esse segundo caso de teste tem por objetivo modificar o conteúdo na memória do sprite usando a intrução WSM 
    e após isso exibir o sprite modificado.
    */
    //caso_teste_4(); //OK E TESTADO NO LEDS

    return 0;
}
