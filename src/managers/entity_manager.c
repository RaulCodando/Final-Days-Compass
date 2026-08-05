#include "entity_manager.h"
#include "../objects/entity.h"
#include "../graphics/sprite.h"
#include "../asset_manager/asset_manager.h"
#include "../utils/vector.h"
#include "../core/game.h"
#include <stdio.h>
#include <stdlib.h>

bool add_entity(Vector **game_entities, Entity *entity){
    if(!game_entities || !(*game_entities) || !entity) return false;
    
    if(!vector_push(*game_entities, entity)){
        entity_destroy(entity);
        return false;
    }

    return true;
}