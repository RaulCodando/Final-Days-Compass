all: test

# 1. Compila o sprite diretamente para a pasta build/ que já existe
build/sprite.o: src/graphics/sprite.c src/graphics/sprite.h
	gcc -c src/graphics/sprite.c -o build/sprite.o -Isrc

# 2. Compila o renderer diretamente para a pasta build/ que já existe
build/renderer.o: src/graphics/renderer.c src/graphics/renderer.h
	gcc -c src/graphics/renderer.c -o build/renderer.o -Isrc

# 3. Compila o game diretamente para a pasta build/ que já existe
build/game.o: src/core/game.c src/core/game.h
	gcc -c src/core/game.c -o build/game.o -Isrc

# 4. Compila o keyboard diretamente para a pasta build/ que já existe
build/keyboard.o: src/input/keyboard.c src/input/keyboard.h
	gcc -c src/input/keyboard.c -o build/keyboard.o -Isrc

# 5. Compila o commands diretamente para a pasta build/ que já existe
build/commands.o: src/input/commands.c src/input/commands.h
	gcc -c src/input/commands.c -o build/commands.o -Isrc

# 6. Compila o map diretamente para a pasta build/ que já existe
build/map.o: src/world/map.c src/world/map.h
	gcc -c src/world/map.c -o build/map.o -Isrc

# 7. Compila o tiles diretamente para a pasta build/ que já existe
build/tiles.o: src/world/tiles.c src/world/tiles.h
	gcc -c src/world/tiles.c -o build/tiles.o -Isrc

# 8. Compila o game_object diretamente para a pasta build/
build/game_object.o: src/objects/game_object.c src/objects/game_object.h
	gcc -c src/objects/game_object.c -o build/game_object.o -Isrc

# 9. Compila o entity diretamente para a pasta build/
build/entity.o: src/objects/entity.c src/objects/entity.h
	gcc -c src/objects/entity.c -o build/entity.o -Isrc

# 10. Compila o asset_manager diretamente para a pasta build/
build/asset_manager.o: src/objects/asset_manager.c src/objects/asset_manager.h
	gcc -c src/objects/asset_manager.c -o build/asset_manager.o -Isrc

# 11. Compila a camera diretamente para a pasta build/
build/camera.o: src/graphics/camera.c src/graphics/camera.h
	gcc -c src/graphics/camera.c -o build/camera.o -Isrc

# 12. Compila o utils diretamente para a pasta build/
build/utils.o: tests/utils/utils.c tests/utils/utils.h
	gcc -c tests/utils/utils.c -o build/utils.o -Isrc -Itests

# 13. Compila o teste diretamente para a pasta build/
build/test_sprite.o: tests/graphics/test_sprite.c tests/graphics/test_sprite.h
	gcc -c tests/graphics/test_sprite.c -o build/test_sprite.o -Isrc -Itests

# 14. Compila o teste diretamente para a pasta build/
build/test_renderer.o: tests/graphics/test_renderer.c tests/graphics/test_renderer.h
	gcc -c tests/graphics/test_renderer.c -o build/test_renderer.o -Isrc -Itests

# 15. Compila o teste diretamente para a pasta build/
build/test_camera.o: tests/graphics/test_camera.c tests/graphics/test_camera.h
	gcc -c tests/graphics/test_camera.c -o build/test_camera.o -Isrc -Itests

# 16. Compila a main do teste diretamente para a pasta build/
build/main_test.o: tests/main_test.c
	gcc -c tests/main_test.c -o build/main_test.o -Isrc -Itests

# 17. Compila o teste diretamente para a pasta build/
build/test_game.o: tests/core/test_game.c tests/core/test_game.h
	gcc -c tests/core/test_game.c -o build/test_game.o -Isrc -Itests

# 18. Compila o teste diretamente para a pasta build/
build/test_keyboard.o: tests/input/test_keyboard.c tests/input/test_keyboard.h
	gcc -c tests/input/test_keyboard.c -o build/test_keyboard.o -Isrc -Itests

# 19. Compila o teste diretamente para a pasta build/
build/test_commands.o: tests/input/test_commands.c tests/input/test_commands.h
	gcc -c tests/input/test_commands.c -o build/test_commands.o -Isrc -Itests

# 20. Compila o teste diretamente para a pasta build/
build/test_map.o: tests/world/test_map.c tests/world/test_map.h
	gcc -c tests/world/test_map.c -o build/test_map.o -Isrc -Itests

# 21. Compila o teste diretamente para a pasta build/
build/test_tiles.o: tests/world/test_tiles.c tests/world/test_tiles.h
	gcc -c tests/world/test_tiles.c -o build/test_tiles.o -Isrc -Itests

# 22. Compila o teste diretamente para a pasta build/
build/test_game_object.o: tests/objects/test_game_object.c tests/objects/test_game_object.h
	gcc -c tests/objects/test_game_object.c -o build/test_game_object.o -Isrc -Itests

# 23. Compila o teste diretamente para a pasta build/
build/test_entity.o: tests/objects/test_entity.c tests/objects/test_entity.h
	gcc -c tests/objects/test_entity.c -o build/test_entity.o -Isrc -Itests

# 24. Compila o teste diretamente para a pasta build/
build/test_asset_manager.o: tests/objects/test_asset_manager.c tests/objects/test_asset_manager.h
	gcc -c tests/objects/test_asset_manager.c -o build/test_asset_manager.o -Isrc -Itests

# 25. Busca os arquivos .o dentro de build/ e gera o executável lá dentro
test: build/sprite.o build/renderer.o build/test_sprite.o build/test_renderer.o build/main_test.o build/game.o build/test_game.o build/keyboard.o build/test_keyboard.o build/commands.o build/test_commands.o build/map.o build/test_map.o build/tiles.o build/test_tiles.o build/game_object.o build/entity.o build/asset_manager.o build/test_game_object.o build/test_entity.o build/test_asset_manager.o build/utils.o build/camera.o build/test_camera.o
	gcc -o tests/run_tests build/main_test.o build/test_sprite.o build/sprite.o build/test_renderer.o build/renderer.o build/game.o build/test_game.o build/keyboard.o build/test_keyboard.o build/commands.o build/test_commands.o build/map.o build/test_map.o build/tiles.o build/test_tiles.o build/game_object.o build/entity.o build/asset_manager.o build/test_game_object.o build/test_entity.o build/test_asset_manager.o build/utils.o build/camera.o build/test_camera.o

# Apaga os arquivos de dentro da build e da pasta tests
clean:
	@if exist build\*.o del /q build\*.o
	@if exist build\*.exe del /q build\*.exe
	@if exist tests\run_tests del /q tests\run_tests
	@if exist tests\run_tests.exe del /q tests\run_tests.exe