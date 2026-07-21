#include "hud.h"
#include "../graphics/sprite.h"
#include "../core/settings.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

HudElement *hud_create_text(const char *text, int x, int y, bool center_x, bool center_y){
    HudElement *element = (HudElement *)malloc(sizeof(HudElement));
    if (!element) {
        perror("Failed to allocate HudElement");
        exit(EXIT_FAILURE);
    }

    element->type = HUD_TEXT;
    element->data.text = (HudTextElement *)malloc(sizeof(HudTextElement));
    if (!element->data.text) {
        perror("Failed to allocate HudTextElement");
        free(element);
        exit(EXIT_FAILURE);
    }

    element->data.text->text = text;
    element->data.text->width = strlen(text);
    element->x = center_x ? (SCREEN_WIDTH - element->data.text->width) / 2 : x;
    element->y = center_y ? (SCREEN_HEIGHT - 1) / 2 : y;
    element->center_x = center_x;
    element->center_y = center_y;

    return element;
}

HudElement *hud_create_icon(const char **sprite_paths, int state_count, int x, int y, bool center_x, bool center_y){
    HudElement *element = (HudElement *)malloc(sizeof(HudElement));
    if (!element) {
        perror("Failed to allocate HudElement");
        exit(EXIT_FAILURE);
    }

    element->type = HUD_ICON;
    element->data.icon = (HudIconElement *)malloc(sizeof(HudIconElement));
    if (!element->data.icon) {
        perror("Failed to allocate HudIconElement");
        free(element);
        exit(EXIT_FAILURE);
    }

    element->data.icon->sprites = (Sprite **)malloc(state_count * sizeof(Sprite *));
    if (!element->data.icon->sprites) {
        perror("Failed to allocate sprites array");
        free(element->data.icon);
        free(element);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < state_count; i++) {
        element->data.icon->sprites[i] = sprite_create(sprite_paths[i]);
    }

    if (!element->data.icon->sprites[0]) {
        fprintf(stderr, "Error: Failed to load base sprite for HudIcon at path: %s\n", sprite_paths[0]);
        for (int i = 0; i < state_count; i++) {
            if (element->data.icon->sprites[i]) {
                sprite_destroy(element->data.icon->sprites[i]);
            }
        }
        free(element->data.icon->sprites);
        free(element->data.icon);
        free(element);
        exit(EXIT_FAILURE);
    }

    element->data.icon->state_count = state_count;
    element->data.icon->width = element->data.icon->sprites[0]->width;
    element->data.icon->height = element->data.icon->sprites[0]->height;
    element->data.icon->current_state_index = 0;
    element->x = center_x ? (SCREEN_WIDTH - element->data.icon->width) / 2 : x;
    element->y = center_y ? (SCREEN_HEIGHT - element->data.icon->height) / 2 : y;
    element->center_x = center_x;
    element->center_y = center_y;

    return element;
}

HudElement *hud_create_container(const char **sprite_paths, int state_count, int x, int y, int width, int height, bool center_x, bool center_y) {
    HudElement *element = (HudElement *)malloc(sizeof(HudElement));
    if (!element) {
        perror("Failed to allocate HudElement");
        exit(EXIT_FAILURE);
    }

    element->type = HUD_CONTAINER;
    element->data.container = (HudContainerElement *)malloc(sizeof(HudContainerElement));
    if (!element->data.container) {
        perror("Failed to allocate HudContainerElement");
        free(element);
        exit(EXIT_FAILURE);
    }

    element->data.container->sprites = NULL;
    element->data.container->state_count = state_count;
    element->data.container->width = width; 
    element->data.container->height = height;
    element->data.container->childCount = 0;
    element->data.container->children = NULL;
    element->data.container->current_state_index = 0;

    if (sprite_paths && state_count > 0) {
        element->data.container->sprites = (Sprite **)malloc(state_count * sizeof(Sprite *));
        if (!element->data.container->sprites) {
            perror("Failed to allocate sprites array");
            free(element->data.container);
            free(element);
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < state_count; i++) {
            Sprite *sprite = sprite_create(sprite_paths[i]);
            element->data.container->sprites[i] = sprite;
        }

        if(element->data.container->sprites[0] != NULL){
            element->data.container->width = element->data.container->sprites[0]->width;
            element->data.container->height = element->data.container->sprites[0]->height;
        }
    }

    element->x = center_x ? (SCREEN_WIDTH - element->data.container->width) / 2 : x;
    element->y = center_y ? (SCREEN_HEIGHT - element->data.container->height) / 2 : y;
    element->center_x = center_x;
    element->center_y = center_y;

    return element;
}

void hud_container_add_child(HudElement *container, HudElement *child){
    if (!container || container->type != HUD_CONTAINER || !child) {
        perror("Container element is not a container or NULL element provided");
        exit(EXIT_FAILURE);
    }

    container->data.container->childCount++;
    container->data.container->children = (HudElement **)realloc(
        container->data.container->children, 
        container->data.container->childCount * sizeof(HudElement *)
    );
    if (!container->data.container->children) {
        perror("Failed to reallocate container children");
        exit(EXIT_FAILURE);
    }
    container->data.container->children[container->data.container->childCount - 1] = child;

    int parent_x = container->x;
    int parent_y = container->y;
    int parent_w = container->data.container->width;
    int parent_h = container->data.container->height;

    switch(child->type){
        case HUD_TEXT:
            child->x = child->center_x 
                ? parent_x + (parent_w - child->data.text->width) / 2 
                : parent_x + child->x;

            child->y = child->center_y 
                ? parent_y + (parent_h - 1) / 2 
                : parent_y + child->y;
            break;

        case HUD_ICON:
            child->x = child->center_x 
                ? parent_x + (parent_w - child->data.icon->width) / 2 
                : parent_x + child->x;

            child->y = child->center_y 
                ? parent_y + (parent_h - child->data.icon->height) / 2 
                : parent_y + child->y;
            break;

        case HUD_CONTAINER:
            child->x = child->center_x 
                ? parent_x + (parent_w - child->data.container->width) / 2 
                : parent_x + child->x;

            child->y = child->center_y 
                ? parent_y + (parent_h - child->data.container->height) / 2 
                : parent_y + child->y;
            break;
    }
}

void hud_container_set_state(HudElement *container, int state_index) {
    if (!container || container->type != HUD_CONTAINER) return;

    HudContainerElement *elem = container->data.container;
    if (!elem) return;
    if (state_index < 0 || state_index >= elem->state_count) return;

    elem->current_state_index = state_index;

    if (elem->sprites && elem->sprites[state_index]) {
        elem->width = elem->sprites[state_index]->width;
        elem->height = elem->sprites[state_index]->height;
    }
}

void hud_icon_set_state(HudElement *icon, int state_index) {
    if (!icon || icon->type != HUD_ICON) return;

    HudIconElement *elem = icon->data.icon;
    if (!elem) return;
    if (state_index < 0 || state_index >= elem->state_count) return;

    elem->current_state_index = state_index;

    if (elem->sprites && elem->sprites[state_index]) {
        elem->width = elem->sprites[state_index]->width;
        elem->height = elem->sprites[state_index]->height;
    }
}

void hud_destroy(HudElement *element){
    if (!element) return;

    switch (element->type) {
        case HUD_TEXT:
            free(element->data.text);
            break;
            
        case HUD_ICON:
            if (element->data.icon->sprites) {
                for (int i = 0; i < element->data.icon->state_count; i++) {
                    sprite_destroy(element->data.icon->sprites[i]);
                }
                free(element->data.icon->sprites);
            }
            free(element->data.icon);
            break;
            
        case HUD_CONTAINER:
            if (element->data.container->sprites) {
                for (int i = 0; i < element->data.container->state_count; i++) {
                    sprite_destroy(element->data.container->sprites[i]);
                }
                free(element->data.container->sprites);
            }
            if (element->data.container->children) {
                for (int i = 0; i < element->data.container->childCount; i++) {
                    hud_destroy(element->data.container->children[i]);
                }
                free(element->data.container->children);
            }
            free(element->data.container);
            break;
    }

    free(element);
}