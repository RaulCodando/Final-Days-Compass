#ifndef TEST_ENTITY_BEHAVIOR_H
#define TEST_ENTITY_BEHAVIOR_H

typedef struct Entity Entity;
typedef struct Game Game;

void test_entity_behavior_update(Entity *self, Game *game);

#endif // TEST_ENTITY_BEHAVIOR_H