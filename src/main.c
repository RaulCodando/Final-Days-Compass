#include "core/game.h"
#include "entity_behaviors/player_behavior.h"
#include "entity_behaviors/test_entity_behavior.h"
#include "entities/player.h"
#include "entities/dummy_entity.h"
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

    static char tile_ids[1] = {(char) 5};

    if (manage_window_init(game, 0.0f, 0.0f, 0.25f) == false) {
        fprintf(stderr, "Erro ao inicializar Window.\n");
        game_destroy(game);
        return EXIT_FAILURE;
    }

    if (manage_entities_init(game) == false) {
        fprintf(stderr, "Erro ao inicializar Entities.\n");
        game_destroy(game);
        return EXIT_FAILURE;
    }

    if (player_spawn(game, 0.0f, 0.0f) == false) {
        fprintf(stderr, "Erro ao criar Player.\n");
        game_destroy(game);
        return EXIT_FAILURE;
    }

    if (test_entity_spawn(game, 0.0f, 112.0f) == false) {
        fprintf(stderr, "Erro ao criar Test Entity.\n");
        game_destroy(game);
        return EXIT_FAILURE;
    }

    if (manage_world_init(game, "tests/assets/test_tile_map03.txt", 32, tile_ids, 1, (SDL_Color){0, 0, 0, 255}) == false) {
        fprintf(stderr, "Erro ao inicializar World.\n");
        game_destroy(game);
        return EXIT_FAILURE;
    }

    if (manage_world_colliders_init(game) == false) {
        fprintf(stderr, "Erro ao inicializar Colliders.\n");
        game_destroy(game);
        return EXIT_FAILURE;
    }

    game_run(game);
    game_destroy(game);
    SDL_Quit();

    return 0;
}