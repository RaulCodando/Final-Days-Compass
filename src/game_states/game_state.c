#include "game_state.h"
#include <stdlib.h>

void game_state_destroy(GameState *state) {
    if (!state) return;
    if (state->state_data) {
        free(state->state_data);
    }
    free(state);
}
