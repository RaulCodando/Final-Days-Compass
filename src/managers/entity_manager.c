#include "entity_manager.h"
#include "../objects/entity.h"
#include "../graphics/sprite.h"
#include "../objects/asset_manager.h"
#include "../utils/vector.h"
#include "../core/game.h"
#include <stdio.h>
#include <stdlib.h>

bool init_entities(Vector **game_entities){
    *game_entities = vector_create();
    if(!*game_entities) return false;

    return true;
}

bool add_entity(Vector **game_entities, Entity *entity){
    if(!game_entities || !(*game_entities) || !entity) return false;
    
    if(!vector_push(*game_entities, entity)){
        entity_destroy(entity);
        return false;
    }

    return true;
}