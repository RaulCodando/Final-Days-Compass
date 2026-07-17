#include "game_state.h"
#include <stdlib.h>

void game_state_destroy(GameState *state){
    if(state == NULL) return;
    free(state);
}
