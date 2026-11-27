// Regras e desenho do combate: movimento, golpes, rounds e informacoes na tela.

#include "raylib.h"
#include "definicoes.h"
#include "combate.h"

// coloca os dois lutadores na posicao inicial, com a vida cheia
void IniciarRound(EstadoJogo *j) {
    for (int i = 0; i < NUM_JOGADORES; i++) {
        j->jogador[i].y = CHAO;
        j->jogador[i].vida = VIDA_MAXIMA;
        j->jogador[i].estado = PARADO;
        j->jogador[i].tempo = 0;
    }

    j->jogador[0].x = X_INICIAL_P1;
    j->jogador[0].direcao = 1;
    j->jogador[0].qual = j->qual_persAD;
    j->jogador[1].x = X_INICIAL_P2;
    j->jogador[1].direcao = -1;
    j->jogador[1].qual = j->qual_pers;
    j->tempo_fim = 0;
}

// hurtbox: retangulo do corpo, onde o lutador pode ser atingido
static Rectangle Hurtbox(Personagem p) {
    Rectangle r = {p.x - LARGURA_CORPO / 2, p.y - ALTURA_CORPO, LARGURA_CORPO, ALTURA_CORPO};
    return r;
}

// move o jogador i, sem deixar sair da tela nem atravessar o outro
static void MoverJogador(EstadoJogo *j, int i, int esquerda, int direita) {
    Personagem *p = &j->jogador[i];
    int outro = 1 - i;
    float x_antigo = p->x;

    // quem esta atacando ou levando dano nao pode andar
    if (p->estado == ATACANDO || p->estado == DANO) {
        p->tempo--;                            // conta os frames da acao
        if (p->tempo <= 0) p->estado = PARADO; // acao terminou
        return;
    }

    p->estado = PARADO;
    if (esquerda) {
        p->x -= VELOCIDADE;
        p->estado = ANDANDO;
    }
    if (direita) {
        p->x += VELOCIDADE;
        p->estado = ANDANDO;
    }

    // limites da tela
    if (p->x < MARGEM_TELA) p->x = MARGEM_TELA;
    if (p->x > LARGURA_TELA - MARGEM_TELA) p->x = LARGURA_TELA - MARGEM_TELA;

    // se os corpos se batem desfaz tudo
    if (CheckCollisionRecs(Hurtbox(*p), Hurtbox(j->jogador[outro]))) {
        p->x = x_antigo;
    }
}

// inicia um golpe, se o lutador estiver livre
static void Atacar(Personagem *p, Golpe g) {
    if (p->estado == PARADO || p->estado == ANDANDO) {
        p->estado = ATACANDO;
        p->golpe = g;
        p->tempo = DURACAO_ATAQUE;
        p->acertou = 0;
    }
}
// hitbox: retangulo do golpe, na frente do corpo
static Rectangle Hitbox(Personagem p) {
    float largura = ALCANCE_SOCO;
    float altura = ALTURA_GOLPE_ALTO;

    if (p.golpe == CHUTE_ALTO || p.golpe == CHUTE_BAIXO) largura = ALCANCE_CHUTE;
    if (p.golpe == SOCO_BAIXO || p.golpe == CHUTE_BAIXO) altura = ALTURA_GOLPE_BAIXO;

    float x = p.x + LARGURA_CORPO / 2;
    if (p.direcao == -1) x = p.x - LARGURA_CORPO / 2 - largura;

    Rectangle r = {x, p.y - altura, largura, ALTURA_HITBOX};
    return r;
}

// devolve o dano de cada golpe
static int DanoDoGolpe(Golpe g) {
    switch (g) {
    case SOCO_ALTO: return DANO_SOCO_ALTO;
    case SOCO_BAIXO: return DANO_SOCO_BAIXO;
    case CHUTE_ALTO: return DANO_CHUTE_ALTO;
    case CHUTE_BAIXO: return DANO_CHUTE_BAIXO;
    }
    return 0;
}

// aplica o dano se o golpe do jogador i atingir o adversario
static void VerificarGolpe(EstadoJogo *j, int i) {
    Personagem *atacante = &j->jogador[i];
    Personagem *alvo = &j->jogador[1 - i];

    if (atacante->estado != ATACANDO || atacante->acertou) return;
    if (atacante->tempo > INICIO_ATIVO || atacante->tempo < FIM_ATIVO) return;

    if (CheckCollisionRecs(Hitbox(*atacante), Hurtbox(*alvo))) {
        atacante->acertou = 1; // cada golpe tira vida uma vez so
        alvo->vida -= DanoDoGolpe(atacante->golpe);
        if (alvo->vida < 0) alvo->vida = 0;
        alvo->estado = DANO;
        alvo->tempo = DURACAO_DANO;
    }
}
// se alguem ficou sem vida, encerra o round
static void VerificarFimRound(EstadoJogo *j) {
    if (j->jogador[0].vida > 0 && j->jogador[1].vida > 0) return;

    j->vencedor = 0;
    if (j->jogador[0].vida == 0) j->vencedor = 1;

    j->vitorias[j->vencedor]++;
    j->jogador[j->vencedor].estado = PARADO;
    j->jogador[1 - j->vencedor].estado = DERROTADO;
    j->tempo_fim = DURACAO_FIM_ROUND;
}

// espera o fim do round e decide o que vem depois
static void EsperarFimRound(EstadoJogo *j) {
    j->tempo_fim--;
    if (j->tempo_fim > 0) return;

    if (j->vitorias[j->vencedor] == ROUNDS_PARA_VENCER) {
        j->tela_ativa = MENU; // acabou a luta
        j->escolheu = 0;      // libera a escolha de novo
        j->escolheuAD = 0;
    } else {
        IniciarRound(j); // proximo round
    }
}

// executa um frame da luta: le o teclado e aplica as regras
void AtualizarCombate(EstadoJogo *luta) {

    if (luta->tempo_fim > 0) { // luta parada entre rounds
        EsperarFimRound(luta);
        return;
    }

    // movimentacao
    MoverJogador(luta, 0, IsKeyDown(KEY_A), IsKeyDown(KEY_D));
    MoverJogador(luta, 1, IsKeyDown(KEY_LEFT), IsKeyDown(KEY_RIGHT));

    // os lutadores ficam sempre de frente um para o outro
    if (luta->jogador[0].x < luta->jogador[1].x) {
        luta->jogador[0].direcao = 1;
        luta->jogador[1].direcao = -1;

    } else {
        luta->jogador[0].direcao = -1;
        luta->jogador[1].direcao = 1;
    }
    // golpes de cada jogador
    if (IsKeyPressed(KEY_U)) Atacar(&luta->jogador[0], SOCO_ALTO);
    if (IsKeyPressed(KEY_J)) Atacar(&luta->jogador[0], SOCO_BAIXO);
    if (IsKeyPressed(KEY_I)) Atacar(&luta->jogador[0], CHUTE_ALTO);
    if (IsKeyPressed(KEY_K)) Atacar(&luta->jogador[0], CHUTE_BAIXO);
    if (IsKeyPressed(KEY_KP_7)) Atacar(&luta->jogador[1], SOCO_ALTO);
    if (IsKeyPressed(KEY_KP_4)) Atacar(&luta->jogador[1], SOCO_BAIXO);
    if (IsKeyPressed(KEY_KP_8)) Atacar(&luta->jogador[1], CHUTE_ALTO);
    if (IsKeyPressed(KEY_KP_5)) Atacar(&luta->jogador[1], CHUTE_BAIXO);
    // colisoes e fim do round
    VerificarGolpe(luta, 0);
    VerificarGolpe(luta, 1);
    VerificarFimRound(luta);
}

// desenha um lutador com o sprite do estado atual
static void DesenharJogador(const EstadoJogo *j, int i) {
    Personagem p = j->jogador[i];
    Texture2D img = j->sprites[p.qual][p.estado];

    // largura negativa espelha a imagem
    Rectangle origem = {0, 0, (float)img.width * p.direcao, (float)img.height};
    Rectangle destino = {p.x - img.width / 2, p.y - PES_NO_SPRITE, img.width, img.height};
    DrawTexturePro(img, origem, destino, (Vector2){0, 0}, 0, WHITE);
}

// nomes, placar de rounds e mensagem de vitoria
static void DesenharHUD(const EstadoJogo *j) {
    const char *nomes[NUM_PERSONAGENS] = {"HOMEM-ARANHA", "MARIO", "BOB ESPONJA", "LINK"};
    int y = Y_BARRA + ALTURA_BARRA + 10;

    DrawText(TextFormat("P1 %s  ROUNDS: %d", nomes[j->jogador[0].qual], j->vitorias[0]), X_BARRA_P1,
             y, 30, WHITE);
    DrawText(TextFormat("P2 %s  ROUNDS: %d", nomes[j->jogador[1].qual], j->vitorias[1]), X_BARRA_P2,
             y, 30, WHITE);

    if (j->tempo_fim > 0) {
        if (j->vitorias[j->vencedor] == ROUNDS_PARA_VENCER) {
            DrawText(TextFormat("JOGADOR %d VENCEU A LUTA!", j->vencedor + 1), 320, 250, 60, GOLD);
        } else {
            DrawText(TextFormat("JOGADOR %d VENCEU O ROUND", j->vencedor + 1), 320, 250, 60, GOLD);
        }
    }
}

// desenha o cenario, as barras de vida, os lutadores e o placar
void DesenharCombate(const EstadoJogo *lut) {
    int largura0 = LARGURA_BARRA * lut->jogador[0].vida / VIDA_MAXIMA;
    int largura1 = LARGURA_BARRA * lut->jogador[1].vida / VIDA_MAXIMA;
    int xdireita = X_BARRA_P2 + LARGURA_BARRA - largura1;
    DrawTexture(lut->imagem_combate, 0, 0, WHITE);
    DrawRectangle(X_BARRA_P2, Y_BARRA, LARGURA_BARRA, ALTURA_BARRA, DARKGRAY);
    DrawRectangle(X_BARRA_P1, Y_BARRA, LARGURA_BARRA, ALTURA_BARRA, DARKGRAY);
    DrawRectangle(X_BARRA_P1, Y_BARRA, largura0, ALTURA_BARRA, RED);
    DrawRectangle(xdireita, Y_BARRA, largura1, ALTURA_BARRA, RED);
    for (int i = 0; i < NUM_JOGADORES; i++) {
        DesenharJogador(lut, i);
    }
    DesenharHUD(lut);
}