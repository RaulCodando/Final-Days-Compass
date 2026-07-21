#ifndef HUD_H
#define HUD_H

#include <stdbool.h>
#include <stddef.h>

typedef struct Sprite Sprite;
typedef struct HudElement HudElement;

typedef enum HudElementType {
    HUD_TEXT,
    HUD_ICON,
    HUD_CONTAINER
} HudElementType;

typedef struct HudTextElement {
    int width;
    const char *text;
} HudTextElement;

typedef struct HudIconElement {
    int width;
    int height;
    int state_count;
    int current_state_index;
    Sprite **sprites;
} HudIconElement;

typedef struct HudContainerElement {
    int width;
    int height;
    int state_count;
    int current_state_index;
    Sprite **sprites;
    int childCount;
    HudElement **children;
} HudContainerElement;

typedef union HudElementData {
    HudTextElement *text;
    HudIconElement *icon;
    HudContainerElement *container;
} HudElementData;

typedef struct HudElement {
    int x;
    int y;
    bool center_x;
    bool center_y;
    HudElementType type;
    HudElementData data;
} HudElement;

HudElement *hud_create_text(const char *text, int x, int y, bool center_x, bool center_y);
HudElement *hud_create_icon(const char **sprite_paths, int state_count, int x, int y, bool center_x, bool center_y);
HudElement *hud_create_container(const char **sprite_paths, int state_count, int x, int y, int width, int height, bool center_x, bool center_y);
void hud_container_add_child(HudElement *container, HudElement *child);
void hud_container_set_state(HudElement *container, int state_index);
void hud_icon_set_state(HudElement *icon, int state_index);
void hud_destroy(HudElement *element);

#endif // HUD_H