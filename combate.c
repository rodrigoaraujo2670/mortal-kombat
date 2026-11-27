#include "raylib.h"
#include "definicoes.h"
#include "combate.h"

// coloca os dois lutadores na posicao inicial, com a vida cheia
void IniciarRound (EstadoJogo *j){
    for (int i = 0; i < NUM_JOGADORES; i++){
        j->jogador[i].y = CHAO;
        j->jogador[i].vida = VIDA_MAXIMA;
        j->jogador[i].estado = PARADO;
        j->jogador[i].tempo = 0;
    }

    j->jogador[0].x =X_INICIAL_P1;
    j->jogador[0].direcao = 1;
    j->jogador[0].qual = j->qual_persAD;
    j->jogador[1].x =X_INICIAL_P2;
    j->jogador[1].direcao = -1;
    j->jogador[1].qual = j->qual_pers;
}

// hurtbox
static Rectangle Hurtbox (Personagem p){
    Rectangle r = {p.x - LARGURA_CORPO / 2, p.y - ALTURA_CORPO, LARGURA_CORPO, ALTURA_CORPO};
    return r;
}

//impede os lutadores de sair da tela nem atravessar o outro
static void MoverJogador (EstadoJogo *j, int i, int esquerda, int direita){
    Personagem *p = &j->jogador[i];
    int outro = 1 - i;
    float x_antigo = p->x;

    p->estado = PARADO;
    if (esquerda){
        p->x -= VELOCIDADE;
        p->estado = ANDANDO;
    }
    if (direita){
        p->x += VELOCIDADE;
        p->estado = ANDANDO;
    }

    // limites da tela
    if (p->x < MARGEM_TELA) p->x = MARGEM_TELA;
    if (p->x > LARGURA_TELA - MARGEM_TELA) p->x = LARGURA_TELA - MARGEM_TELA;

    // se os corpos se batem desfaz tudo
    if (CheckCollisionRecs(Hurtbox(*p), Hurtbox(j->jogador[outro]))){
        p->x = x_antigo;
    }
}
void AtualizarCombate (EstadoJogo *luta){

    MoverJogador (luta, 0, IsKeyDown(KEY_A),IsKeyDown(KEY_D));
    MoverJogador (luta, 1, IsKeyDown(KEY_LEFT),IsKeyDown(KEY_RIGHT));

    if (luta->jogador[0].x < luta->jogador[1].x){
        luta->jogador[0].direcao = 1;
        luta->jogador[1].direcao = -1;
        
    }
    else {
        luta->jogador[0].direcao = -1;
        luta->jogador[1].direcao = 1;

    }

}
    // desenha um lutador com o sprite do estado atual
    static void DesenharJogador (const EstadoJogo *j, int i){
    Personagem p = j->jogador[i];
    Texture2D img = j->sprites[p.qual][p.estado];

    // largura negativa espelha a imagem
    Rectangle origem = {0, 0, (float)img.width * p.direcao, (float)img.height};
    Rectangle destino = {p.x - img.width / 2, p.y - PES_NO_SPRITE, img.width, img.height};
    DrawTexturePro(img, origem, destino, (Vector2){0, 0}, 0, WHITE);

}

void DesenharCombate (const EstadoJogo *lut){
    int largura0 = LARGURA_BARRA * lut->jogador[0].vida / VIDA_MAXIMA;
    int largura1 = LARGURA_BARRA * lut->jogador[1].vida / VIDA_MAXIMA;
    int xdireita = X_BARRA_P2 + LARGURA_BARRA - largura1;
    DrawTexture (lut -> imagem_combate, 0,0, WHITE);
    DrawRectangle (X_BARRA_P2,Y_BARRA,LARGURA_BARRA,ALTURA_BARRA, DARKGRAY);
    DrawRectangle (X_BARRA_P1,Y_BARRA,LARGURA_BARRA,ALTURA_BARRA, DARKGRAY);
    DrawRectangle (X_BARRA_P1,Y_BARRA,largura0,ALTURA_BARRA, RED);
    DrawRectangle (xdireita,Y_BARRA,largura1,ALTURA_BARRA, RED);
    for (int i = 0; i < NUM_JOGADORES; i++){
    DesenharJogador(lut, i);
}

}