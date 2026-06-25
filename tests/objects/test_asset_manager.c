#include "test_asset_manager.h"
#include "../../src/objects/asset_manager.h"
#include "../../src/graphics/sprite.h"
#include "../utils/utils.h"
#include <stdlib.h>
#include <stdio.h>

void test_asset_manager_create(){
    AssetManager *asset_manager = asset_manager_create();
    if(asset_manager == NULL){
        printf("test_asset_manager_create: FAILED\n");
        exit(1);
    }
    printf("test_asset_manager_create: PASSED\n");
    asset_manager_destroy(asset_manager);
}

void test_asset_manager_get(){
    AssetManager *asset_manager = asset_manager_create();
    
    Sprite *sprite1 = asset_manager_get(asset_manager, PLAYER, "tests/assets/test_sprite03.txt");
    if(sprite1 == NULL){
        printf("test_asset_manager_get (load): FAILED\n");
        exit(1);
    }
    
    Sprite *sprite2 = asset_manager_get(asset_manager, PLAYER, "tests/assets/test_sprite03.txt");
    if(sprite1 != sprite2) {
        printf("test_asset_manager_get (cache): FAILED (Duplicou o sprite na memoria)\n");
        exit(1);
    }

    print_sprite(sprite1);
    printf("test_asset_manager_get: PASSED\n");
    asset_manager_destroy(asset_manager);
}

void test_asset_manager(){
    test_asset_manager_create();
    test_asset_manager_get();
}