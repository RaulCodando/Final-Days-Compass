#include "core/game.h"
#include "entities/player.h"
#include "entities/dummy_entity.h"
#include "scenery_elements/tree.h"
#include "SDL3/SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main() {
    Game *game = game_create();
    if (!game) {
        fprintf(stderr, "Erro ao criar estrutura do Game.\n");
        return EXIT_FAILURE;
    }

    static char tile_ids[1] = {(char) 2};

    if (manage_window_init(game, 0.0f, 0.0f, 0.25f) == false) {
        fprintf(stderr, "Erro ao inicializar Window.\n");
        game_destroy(game);
        return EXIT_FAILURE;
    }

    if (player_spawn(game, 640.0f, 360.0f) == false) {
        fprintf(stderr, "Erro ao criar Player.\n");
        game_destroy(game);
        return EXIT_FAILURE;
    }

    if (manage_world_init(game, "assets/tile_maps/tile_map.txt", 16, tile_ids, 1, (SDL_Color){0, 0, 0, 255}) == false) {
        fprintf(stderr, "Erro ao inicializar World.\n");
        game_destroy(game);
        return EXIT_FAILURE;
    }

    if(build_tree(game, 640, 256, 0, 16) == false){
        fprintf(stderr, "Erro ao criar tree.\n");
        game_destroy(game);
        return EXIT_FAILURE;
    }

    game_run(game);
    game_destroy(game);
    SDL_Quit();

    return 0;
}