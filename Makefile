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

#4. Compila o keyboard diretamente para a pasta build/ que já existe
build/keyboard.o: src/input/keyboard.c src/input/keyboard.h
	gcc -c src/input/keyboard.c -o build/keyboard.o -Isrc

# 5. Compila o teste diretamente para a pasta build/
build/test_sprite.o: tests/graphics/test_sprite.c tests/graphics/test_sprite.h
	gcc -c tests/graphics/test_sprite.c -o build/test_sprite.o -Isrc -Itests

# 6. Compila o teste diretamente para a pasta build/
build/test_renderer.o: tests/graphics/test_renderer.c tests/graphics/test_renderer.h
	gcc -c tests/graphics/test_renderer.c -o build/test_renderer.o -Isrc -Itests

# 7. Compila a main do teste diretamente para a pasta build/
build/main_test.o: tests/main_test.c
	gcc -c tests/main_test.c -o build/main_test.o -Isrc -Itests

#8. Compila o teste diretamente para a pasta build/
build/test_game.o: tests/core/test_game.c tests/core/test_game.h
	gcc -c tests/core/test_game.c -o build/test_game.o -Isrc -Itests

#9. Compila o teste diretamente para a pasta build/
build/test_keyboard.o: tests/input/test_keyboard.c tests/input/test_keyboard.h
	gcc -c tests/input/test_keyboard.c -o build/test_keyboard.o -Isrc -Itests

#10. Busca os arquivos .o dentro de build/ e gera o executável lá dentro
test: build/sprite.o build/renderer.o build/test_sprite.o build/test_renderer.o build/main_test.o build/game.o build/test_game.o build/keyboard.o build/test_keyboard.o
	gcc -o tests/run_tests build/main_test.o build/test_sprite.o build/sprite.o build/test_renderer.o build/renderer.o build/game.o build/test_game.o build/keyboard.o build/test_keyboard.o

# Apaga os arquivos de dentro da build e da pasta tests
clean:
	@if exist build\*.o del /q build\*.o
	@if exist build\*.exe del /q build\*.exe
	@if exist tests\run_tests del /q tests\run_tests
	@if exist tests\run_tests.exe del /q tests\run_tests.exe