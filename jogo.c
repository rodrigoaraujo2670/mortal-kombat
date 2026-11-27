// Telas de abertura e de selecao de personagens.

#include "raylib.h"
#include "definicoes.h"
#include "jogo.h"
#include "combate.h"

// le as setas e o ENTER na tela de abertura
void AtualizarMenu(EstadoJogo *op) {

    if (IsKeyPressed(KEY_UP)) {
        op->op_menu = 1;
    }
    if (IsKeyPressed(KEY_DOWN)) {
        op->op_menu = 2;
    }

    if (IsKeyPressed(KEY_ENTER)) {

        if (op->op_menu == 1) {
            op->tela_ativa = ESCOLHA;
        } else {
            op->quer_sair = 1;
        }
    }
}

// desenha a abertura e a borda na opcao selecionada
void DesenharMenu(const EstadoJogo *vis) {

    Rectangle borda_sair = {X_RETANGULO_MENU, Y_SAIR, LARGURA_RETANGULO_MENU,
                            ALTURA_RETANGULO_MENU};
    Rectangle borda_novojogo = {X_RETANGULO_MENU, Y_NOVOJOGO, LARGURA_RETANGULO_MENU,
                                ALTURA_RETANGULO_MENU};
    Rectangle origem = {0, 0, (float)vis->imagem.width, (float)vis->imagem.height};
    Rectangle destino = {0, 0, LARGURA_TELA, ALTURA_TELA};
    DrawTexturePro(vis->imagem, origem, destino, (Vector2){0, 0}, 0, WHITE);
    if (vis->op_menu == 1) {
        DrawRectangleLinesEx(borda_novojogo, ESP_RETANGULO_MENU, RED);
    }
    if (vis->op_menu == 2) {
        DrawRectangleLinesEx(borda_sair, ESP_RETANGULO_MENU, RED);
    }
}

// move os cursores, trata as confirmacoes e inicia a luta
void AtualizarEscolha(EstadoJogo *per) {

    // cada cursor so se move enquanto o jogador nao confirmou
    if (per->escolheuAD == 0) {
        if (IsKeyPressed(KEY_A)) {
            per->qual_persAD--;
        }
        if (IsKeyPressed(KEY_D)) {
            per->qual_persAD++;
        }
    }
    if (per->escolheu == 0) {
        if (IsKeyPressed(KEY_LEFT)) {
            per->qual_pers--;
        }
        if (IsKeyPressed(KEY_RIGHT)) {
            per->qual_pers++;
        }
    }
    // confirma, desde que o outro nao tenha escolhido o mesmo personagem
    if (IsKeyPressed(KEY_SPACE) && (per->escolheu == 0 || per->qual_persAD != per->qual_pers)) {
        per->escolheuAD = 1;
    }
    if (IsKeyPressed(KEY_ENTER) && (per->escolheuAD == 0 || per->qual_pers != per->qual_persAD)) {
        per->escolheu = 1;
    }

    // mantem os cursores entre o primeiro e o ultimo personagem
    if (per->qual_persAD < 0) {
        per->qual_persAD = 0;
    }
    if (per->qual_persAD > 3) {
        per->qual_persAD = 3;
    }
    if (per->qual_pers < 0) {
        per->qual_pers = 0;
    }
    if (per->qual_pers > 3) {
        per->qual_pers = 3;
    }

    // com os dois confirmados, zera o placar e comeca a luta
    if (per->escolheu == 1 && per->escolheuAD == 1) {
        per->tela_ativa = COMBATE;
        per->vitorias[0] = 0;
        per->vitorias[1] = 0;
        IniciarRound(per);
    }
}

// desenha os personagens e as bordas de cada jogador
void DesenharEscolha(const EstadoJogo *pers) {

    int xs[4] = {X_SLOT_1, X_SLOT_2, X_SLOT_3, X_SLOT_4};
    Rectangle borda2 = {xs[pers->qual_persAD], Y_SLOTS_ESCOLHA, LARGURA_SLOT, ALTURA_SLOT};
    Rectangle borda = {xs[pers->qual_pers], Y_SLOTS_ESCOLHA, LARGURA_SLOT, ALTURA_SLOT};
    Rectangle origem = {0, 0, (float)pers->personagens[0].width,
                        (float)pers->personagens[0].height};
    Rectangle destino = {X_SLOT_1, Y_SLOTS_ESCOLHA, LARGURA_SLOT, ALTURA_SLOT};
    DrawTexture(pers->imagem_escolha, 0, 0, WHITE);
    // o personagem confirmado fica escurecido
    Color cor = WHITE;
    Color cor1 = WHITE;
    Color cor2 = WHITE;
    Color cor3 = WHITE;
    if (pers->escolheu == 1 && pers->qual_pers == 0) {
        cor = DARKGRAY;
    }
    if (pers->escolheu == 1 && pers->qual_pers == 1) {
        cor1 = DARKGRAY;
    }
    if (pers->escolheu == 1 && pers->qual_pers == 2) {
        cor2 = DARKGRAY;
    }
    if (pers->escolheu == 1 && pers->qual_pers == 3) {
        cor3 = DARKGRAY;
    }
    if (pers->escolheuAD == 1 && pers->qual_persAD == 0) {
        cor = DARKGRAY;
    }
    if (pers->escolheuAD == 1 && pers->qual_persAD == 1) {
        cor1 = DARKGRAY;
    }
    if (pers->escolheuAD == 1 && pers->qual_persAD == 2) {
        cor2 = DARKGRAY;
    }
    if (pers->escolheuAD == 1 && pers->qual_persAD == 3) {
        cor3 = DARKGRAY;
    }
    DrawTexturePro(pers->personagens[0], origem, destino, (Vector2){0, 0}, 0, cor);
    origem.width = pers->personagens[1].width;
    origem.height = pers->personagens[1].height;
    destino.x = X_SLOT_2;
    DrawTexturePro(pers->personagens[1], origem, destino, (Vector2){0, 0}, 0, cor1);
    origem.width = pers->personagens[2].width;
    origem.height = pers->personagens[2].height;
    destino.x = X_SLOT_3;
    DrawTexturePro(pers->personagens[2], origem, destino, (Vector2){0, 0}, 0, cor2);
    origem.width = pers->personagens[3].width;
    origem.height = pers->personagens[3].height;
    destino.x = X_SLOT_4;
    DrawTexturePro(pers->personagens[3], origem, destino, (Vector2){0, 0}, 0, cor3);
    DrawRectangleLinesEx(borda, 8, BLUE);
    DrawRectangleLinesEx(borda2, 8, GREEN);
}
