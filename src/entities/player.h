#ifndef PLAYER_H
#define PLAYER_H

#include <stdbool.h>

typedef struct Game Game;

bool player_spawn(Game* game, float x, float y);

#endif // PLAYER_H