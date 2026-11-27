// Constantes, enumeracoes e estruturas usadas em todo o jogo.

#ifndef DEFINICOES_H
#define DEFINICOES_H

#include "raylib.h"

#define FPS 60
#define LINHA_ESCOLHA 2
#define COLUNA_ESCOLHA 5
#define ALTURA_RETANGULO_MENU 128
#define LARGURA_RETANGULO_MENU 670
#define ESP_RETANGULO_MENU 15
#define X_RETANGULO_MENU 413
#define Y_SAIR 520
#define Y_NOVOJOGO 400
#define ALTURA_TELA 790
#define LARGURA_TELA 1500
#define Y_SLOTS_ESCOLHA 445
#define LARGURA_SLOT 226
#define ALTURA_SLOT 217
// posicao dos slots de selecao, da esquerda para a direita
#define X_SLOT_1 218
#define X_SLOT_2 498
#define X_SLOT_3 775
#define X_SLOT_4 1053
// combate
#define VIDA_MAXIMA 100
#define NUM_JOGADORES 2
#define CHAO 735 // altura dos pes na tela
#define X_INICIAL_P1 400
#define X_INICIAL_P2 1100
#define LARGURA_BARRA 600
#define ALTURA_BARRA 40
#define Y_BARRA 40
#define X_BARRA_P1 50
#define X_BARRA_P2 850
#define NUM_PERSONAGENS 4
#define NUM_ESTADOS 5
#define PES_NO_SPRITE 310 // altura dos pes dentro da imagem
#define VELOCIDADE 7
#define MARGEM_TELA 70
#define LARGURA_CORPO 110 // tamanho da hurtbox
#define ALTURA_CORPO 220
#define DURACAO_ATAQUE 24 // em frames
#define DANO_SOCO_ALTO 8
#define DANO_SOCO_BAIXO 6
#define DANO_CHUTE_ALTO 12
#define DANO_CHUTE_BAIXO 10
#define ALCANCE_SOCO 60
#define ALCANCE_CHUTE 90
#define ALTURA_GOLPE_ALTO 200
#define ALTURA_GOLPE_BAIXO 90
#define ALTURA_HITBOX 50
#define DURACAO_DANO 20
#define INICIO_ATIVO 16 // o golpe acerta enquanto o tempo
#define FIM_ATIVO 8     // esta entre estes dois valores
#define ROUNDS_PARA_VENCER 2
#define DURACAO_FIM_ROUND 180 // 3 segundos

// tipos de golpe, telas e estados do lutador
typedef enum { SOCO_ALTO, SOCO_BAIXO, CHUTE_ALTO, CHUTE_BAIXO } Golpe;
typedef enum { MENU, ESCOLHA, COMBATE } Tela;
typedef enum { PARADO, ANDANDO, ATACANDO, DANO, DERROTADO } Estado;

// dados de um jogador durante a luta
typedef struct {
    int qual;   // qual personagem 0-3
    float x, y; // posição dos pes dos personagens
    int vida;
    Estado estado;
    int direcao; // 1 = olha pra direita, -1 olha pra esquerda
    int tempo;   // frames pro ataque e dano
    Golpe golpe; // golpe em andamento
    int acertou; // 1 se este golpe ja causou dano
} Personagem;

// estado geral do jogo
typedef struct {
    int op_menu;                                     // opcao do menu: 1 novo jogo, 2 sair
    Tela tela_ativa;                                 // tela atual
    Texture2D imagem;                                // fundo do menu
    int quer_sair;                                   // 1 para fechar o jogo
    Texture2D personagens[4];                        // icones da selecao
    int qual_pers;                                   // cursor das setas
    Texture2D imagem_escolha;                        // fundo da selecao
    int qual_persAD;                                 // cursor do A/D
    int escolheuAD;                                  // 1 se o jogador do A/D confirmou
    int escolheu;                                    // 1 se o jogador das setas confirmou
    Texture2D imagem_combate;                        // cenario da luta
    Personagem jogador[NUM_JOGADORES];               // 0 = A/D, 1 = setas
    Texture2D sprites[NUM_PERSONAGENS][NUM_ESTADOS]; // [personagem][estado]
    int vitorias[NUM_JOGADORES];                     // rounds vencidos
    int vencedor;                                    // quem venceu o ultimo round
    int tempo_fim;                                   // maior que 0: round acabou

} EstadoJogo;

#endif