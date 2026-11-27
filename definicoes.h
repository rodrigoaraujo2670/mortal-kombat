#ifndef DEFINICOES_H
#define DEFINICOES_H

#include "raylib.h"

#define FPS 60
#define LINHA_ESCOLHA 2
#define COLUNA_ESCOLHA 5
#define ALTURA_RETANGULO_MENU 128
#define LARGURA_RETANGULO_MENU 670
#define ESP_RETANGULO_MENU 15
#define X_RETANGULO_MENU  413
#define Y_SAIR 520
#define Y_NOVOJOGO 400
#define ALTURA_TELA 790
#define LARGURA_TELA 1500
#define Y_SLOTS_ESCOLHA 445
#define LARGURA_SLOT 226
#define ALTURA_SLOT 217
//esquerda pra direita
#define X_SLOT_1 218
#define X_SLOT_2 498
#define X_SLOT_3 775
#define X_SLOT_4 1053
//
#define VIDA_MAXIMA 100
#define NUM_JOGADORES 2
#define CHAO 735            // altura dos pes na tela
#define X_INICIAL_P1 400
#define X_INICIAL_P2 1100
#define LARGURA_BARRA 600
#define ALTURA_BARRA 40
#define Y_BARRA 40
#define X_BARRA_P1 50
#define X_BARRA_P2 850
#define NUM_PERSONAGENS 4
#define NUM_ESTADOS 5
#define PES_NO_SPRITE 310    // altura dos pes dentro da imagem
#define VELOCIDADE 7
#define MARGEM_TELA 70
#define LARGURA_CORPO 110     // tamanho da hurtbox
#define ALTURA_CORPO 220
#define DURACAO_ATAQUE 24     // em frames


typedef enum {SOCO_ALTO, SOCO_BAIXO, CHUTE_ALTO, CHUTE_BAIXO} Golpe;
typedef enum {MENU,ESCOLHA,COMBATE} Tela;
typedef enum {PARADO, ANDANDO, ATACANDO, DANO, DERROTADO} Estado;

typedef struct {
    int qual;     //qual personagem 0-3   
    float x, y;  //posição dos pes dos personagens     
    int vida;
    Estado estado;
    int direcao;     // 1 = olha pra direita, -1 olha pra esquerda
    int tempo;       // frames pro ataque e dano 
    Golpe golpe;     // golpe em andamento
    int acertou;     // 1 se este golpe ja causou dano
} Personagem;

typedef struct {
    int op_menu;
    Tela tela_ativa;
    Texture2D imagem;
    int quer_sair;
    Texture2D personagens[4];
    int qual_pers;
    Texture2D imagem_escolha;
    int qual_persAD;
    int escolheuAD;
    int escolheu;
    Texture2D imagem_combate;
    Personagem jogador [NUM_JOGADORES];
    Texture2D sprites[NUM_PERSONAGENS][NUM_ESTADOS];

}EstadoJogo;

#endif