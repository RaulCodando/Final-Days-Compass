#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <stdbool.h>

typedef struct Entity Entity;
typedef struct Sprite Sprite;
typedef struct AssetManager AssetManager;
typedef struct Vector Vector;
typedef enum ObjectIDs ObjectIDs;

bool init_entities(Vector **game_entities, AssetManager **asset_manager, ObjectIDs *object_ids, const char **sprite_paths, int sprite_count);
bool add_entity(Vector **game_entities, AssetManager **asset_manager, int *game_entity_count, ObjectIDs id, int health, int standard_attack, float speed, float x_pos, float y_pos, const char *sprite_path);
bool init_entity_collider(Vector **game_entities, ObjectIDs id, float collider_width, float collider_height, float offset_x, float offset_y);

#endif // ENTITY_MANAGER_H