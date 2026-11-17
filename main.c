#include "raylib.h"
#include "definicoes.h"
#include "jogo.h"


int main(void){

 
EstadoJogo men = {1, MENU};


InitWindow(LARGURA_TELA, ALTURA_TELA, "ufrgs_kombat");
men.imagem = LoadTexture("menu.png");
men.imagem_escolha = LoadTexture("escolha.png");
SetTargetFPS(FPS);

while(!WindowShouldClose() && !(men.quer_sair == 1)){

  BeginDrawing();
  ClearBackground(RAYWHITE);
        switch (men.tela_ativa){

        case MENU:
        AtualizarMenu(&men);
        DesenharMenu(&men);
        break;
        case ESCOLHA:
        AtualizarEscolha(&men);
        DesenharEscolha(&men);
        break;
        case COMBATE:
        break;

    }

  EndDrawing();

}
UnloadTexture (men.imagem);
UnloadTexture (men.imagem_escolha);
CloseWindow();

return 0;

}
