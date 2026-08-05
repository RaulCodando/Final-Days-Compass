#include "playing_state.h"
#include "menu_state.h"
#include "../core/game.h"
#include "../input/commands.h"
#include "../objects/entity.h"
#include "../objects/scenery_element.h"
#include "../core/state_manager.h"
#include <stdlib.h>
#include <math.h>

int compare_renderables(const void *a, const void *b) {
    const RenderableObject *itemA = *(const RenderableObject **)a;
    const RenderableObject *itemB = *(const RenderableObject **)b;

    if (itemA->y_anchor < itemB->y_anchor) return -1;
    if (itemA->y_anchor > itemB->y_anchor) return 1;
    return 0;
}

static void playing_state_enter(Game *game, void *state_data){
    
}

static void playing_state_exit(Game *game, void *state_data){
    
}

static void playing_state_update(Game *game, void *state_data){
    if(!game || !game->entities) return;

    if (game->commands.quit_game.triggered) {
        game->commands.quit_game.triggered = false;

        state_manager_push(game->state_manager, menu_state_create(), game);
        return;
    }

    Entity *player = NULL;
    int map_width_px = game->map->width * game->map->tile_size;
    int map_height_px = game->map->height * game->map->tile_size;

    for (size_t i = 0; i < game->entities->size; i++) {
        Entity *entity = (Entity *)vector_get(game->entities, i);
        if(entity == NULL) continue;
        entity->vel_x = 0.0f;
        entity->vel_y = 0.0f;
        if(entity->base.id == PLAYER) player = entity;
    }

    if(player == NULL) return;

    for (size_t i = 0; i < game->entities->size; i++) {
        Entity *entity = (Entity *)vector_get(game->entities, i);
        if(entity == NULL || entity->update_behavior == NULL) continue;
        
        entity->update_behavior(entity, game);
        if(entity->vel_x != 0.0f || entity->vel_y != 0.0f) wrap_around_map(entity, map_width_px, map_height_px);
    }

    camera_update(game->camera, player->x_pos, player->y_pos, player->base.sprite->width, player->base.sprite->height, map_width_px, map_height_px);
}

static void playing_state_render(Game *game, void *state_data){
    if(!game || !game->entities) return;

    if (game->map != NULL) {
        renderer_draw_map(game->renderer, game->camera, game->map, 0);
    }

    size_t max_renderables = game->entities->size + game->scenery_elements->size;
    if (max_renderables == 0) return;

    RenderableObject *renderables[max_renderables];
    size_t current_renderable = 0;

    for(size_t i = 0; i < game->entities->size; i++){
        Entity *entity = (Entity*)vector_get(game->entities, i);
        if (!entity) continue;

        float y_anchor = entity_get_y_anchor(entity);
        renderables[current_renderable] = renderable_object_create(RENDERABLE_ENTITY, entity, y_anchor);
        current_renderable++;
    }

    for(size_t i = 0; i < game->scenery_elements->size; i++){
        SceneryElement *scenery_element = (SceneryElement*)vector_get(game->scenery_elements, i);
        if (!scenery_element) continue;

        float y_anchor = scenery_element_get_y_anchor(scenery_element);
        renderables[current_renderable] = renderable_object_create(RENDERABLE_SCENERY_ELEMENT, scenery_element, y_anchor);
        current_renderable++;
    }

    qsort(renderables, current_renderable, sizeof(RenderableObject*), compare_renderables);

    for(size_t i = 0; i < current_renderable; i++){
        Sprite *sprite = NULL;
        float x = 0;
        float y = 0;

        if(renderables[i]->type == RENDERABLE_ENTITY) {
            Entity *entity = (Entity*)renderables[i]->object;
            sprite = entity->base.sprite;
            x = entity->x_pos;
            y = entity->y_pos;
        }
        else if(renderables[i]->type == RENDERABLE_SCENERY_ELEMENT) {
            SceneryElement *scenery_element = (SceneryElement*)renderables[i]->object;
            sprite = scenery_element->base.sprite;
            x = scenery_element->x_pos;
            y = scenery_element->y_pos;
        }

        int renderable_screen_x = (int) floorf(x - game->camera->x);
        int renderable_screen_y = (int) floorf(y - game->camera->y);

        if(sprite != NULL) {
            renderer_draw(game->renderer, renderable_screen_x, renderable_screen_y, sprite);
        }

        renderable_object_destroy(renderables[i]);
    }

    renderer_draw_map(game->renderer, game->camera, game->map, 1);
}

GameState *playing_state_create(){
    GameState *state = calloc(1, sizeof(GameState));
    if(state == NULL) return NULL;
    state->type = STATE_PLAYING;
    state->update_lower_state = false;
    state->render_lower_state = false;
    state->enter = playing_state_enter;
    state->exit = playing_state_exit;
    state->update = playing_state_update;
    state->render = playing_state_render;
    return state;
}