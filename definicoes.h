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



typedef enum {MENU,ESCOLHA,COMBATE} Tela;

typedef struct {
    int op_menu;
    Tela tela_ativa;
    Texture2D imagem;
    int quer_sair;
    Texture2D personagens[4];
    int qual_pers;
    Texture2D imagem_escolha;

}EstadoJogo;

#endif