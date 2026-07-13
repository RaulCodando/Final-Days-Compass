#ifndef PLAYER_BEHAVIOR_H
#define PLAYER_BEHAVIOR_H

typedef struct Entity Entity;
typedef struct Game Game;

void player_update(Entity* self, Game* game);

#endif // PLAYER_BEHAVIOR_H