#include "raylib.h"
#include "definicoes.h"
#include "jogo.h"
#include "combate.h"


int main(void){

 
EstadoJogo men = {1, MENU};


InitWindow(LARGURA_TELA, ALTURA_TELA, "ufrgs_kombat");
men.imagem_combate = LoadTexture ("imagens/combate.png");
men.imagem = LoadTexture("imagens/menu.png");
men.imagem_escolha = LoadTexture("imagens/escolha.png");
men.personagens[0] = LoadTexture("icons/spider-icon.png");
men.personagens[1] = LoadTexture("icons/mario-icon.png");
men.personagens[2] = LoadTexture("icons/bob-icon.png");
men.personagens[3] = LoadTexture("icons/link-icon.png");
// os nomes seguem a ordem dos icones e do enum Estado, tudo conforme o nome dos sprites no aquivo la
const char *nomes[NUM_PERSONAGENS] = {"spider", "mario", "bob", "link"};
const char *poses[NUM_ESTADOS] = {"parado", "andando", "atacando", "dano", "derrotado"};

for (int p = 0; p < NUM_PERSONAGENS; p++){
    for (int e = 0; e < NUM_ESTADOS; e++){
        men.sprites[p][e] = LoadTexture(TextFormat("sprites/%s%s.png", nomes[p], poses[e]));
    }
}
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
        AtualizarCombate(&men);
        DesenharCombate(&men);
        break;

    }

  EndDrawing();

}
UnloadTexture (men.imagem);
UnloadTexture (men.imagem_escolha);
UnloadTexture (men.imagem_combate);
UnloadTexture (men.personagens[0]);
UnloadTexture (men.personagens[1]);
UnloadTexture (men.personagens[2]);
UnloadTexture (men.personagens[3]);
for (int p = 0; p < NUM_PERSONAGENS; p++){
    for (int e = 0; e < NUM_ESTADOS; e++){
       UnloadTexture(men.sprites[p][e]);
    }
}
CloseWindow();

return 0;

}
