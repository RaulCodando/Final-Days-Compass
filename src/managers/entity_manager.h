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

bool init_entities(Vector **game_entities, AssetManager **asset_manager, ObjectIDs *object_ids, const char **sprite_paths, int sprite_count);
bool add_entity(Vector **game_entities, AssetManager **asset_manager, int *game_entity_count, ObjectIDs id, int health, int standard_attack, float speed, float x_pos, float y_pos, const char *sprite_path);
bool add_entity_behavior(Vector **game_entities, ObjectIDs id, behavior_update behavior);
bool init_entity_collider(Vector **game_entities, ObjectIDs id, float collider_width, float collider_height, float offset_x, float offset_y);

#endif // ENTITY_MANAGER_H