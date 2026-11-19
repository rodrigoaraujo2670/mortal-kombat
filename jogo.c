#include "raylib.h"
#include "definicoes.h"
#include "jogo.h"


void AtualizarMenu (EstadoJogo *op){


if (IsKeyPressed (KEY_UP)){
    op -> op_menu = 1;

}
if (IsKeyPressed (KEY_DOWN)){
    op -> op_menu = 2;
}

if (IsKeyPressed (KEY_ENTER)){

    if (op-> op_menu==1){
        op -> tela_ativa = ESCOLHA;
    }
    else {
        op -> quer_sair = 1;
    }
}

}

void DesenharMenu (const EstadoJogo *vis ){


Rectangle borda_sair = {X_RETANGULO_MENU,Y_SAIR,LARGURA_RETANGULO_MENU, ALTURA_RETANGULO_MENU};
Rectangle borda_novojogo = {X_RETANGULO_MENU,Y_NOVOJOGO,LARGURA_RETANGULO_MENU, ALTURA_RETANGULO_MENU};
Rectangle origem = {0, 0, (float)vis->imagem.width, (float)vis->imagem.height};
Rectangle destino = {0, 0, LARGURA_TELA, ALTURA_TELA};
DrawTexturePro (vis -> imagem, origem, destino, (Vector2){0, 0}, 0, WHITE);
if (vis -> op_menu == 1){
DrawRectangleLinesEx(borda_novojogo, ESP_RETANGULO_MENU, RED);
}
if (vis -> op_menu == 2){
DrawRectangleLinesEx(borda_sair, ESP_RETANGULO_MENU, RED);  
}

}

void AtualizarEscolha (EstadoJogo *per){

    


}

void DesenharEscolha (const EstadoJogo *pers){
    Rectangle origem = {0, 0, (float)pers->personagens[0].width,(float)pers->personagens[0].height};
    Rectangle destino = {X_SLOT_1, Y_SLOTS_ESCOLHA, LARGURA_SLOT, ALTURA_SLOT};
    DrawTexture (pers -> imagem_escolha, 0,0, WHITE);
    DrawTexturePro (pers -> personagens[0],origem, destino, (Vector2){0, 0},0 ,WHITE);
    origem.width = pers->personagens[1].width;
    origem.height = pers->personagens[1].height;
    destino.x = X_SLOT_2;
    DrawTexturePro (pers -> personagens[1],origem, destino, (Vector2){0, 0},0 ,WHITE);
    origem.width = pers->personagens[2].width;
    origem.height = pers->personagens[2].height;
    destino.x = X_SLOT_3;
    DrawTexturePro (pers -> personagens[2],origem, destino, (Vector2){0, 0},0 ,WHITE);
    origem.width = pers->personagens[3].width;
    origem.height = pers->personagens[3].height;
    destino.x = X_SLOT_4;
    DrawTexturePro (pers -> personagens[3],origem, destino, (Vector2){0, 0},0 ,WHITE);
}