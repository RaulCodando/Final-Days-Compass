#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <stdbool.h>

typedef struct Entity Entity;
typedef struct Sprite Sprite;
typedef struct AssetManager AssetManager;
typedef struct Vector Vector;
typedef struct Game Game;
typedef enum ObjectIDs ObjectIDs;
typedef void (*behavior_update)(Entity* self, Game *game_context);

bool init_entities(Vector **game_entities);
bool add_entity(Vector **game_entities, Entity *entity);

#endif // ENTITY_MANAGER_H