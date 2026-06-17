all: test

# 1. Compila o sprite diretamente para a pasta build/ que já existe
build/sprite.o: src/graphics/sprite.c src/graphics/sprite.h
	gcc -c src/graphics/sprite.c -o build/sprite.o -Isrc

# 2. Compila o teste diretamente para a pasta build/
build/test_sprite.o: tests/graphics/test_sprite.c tests/graphics/test_sprite.h
	gcc -c tests/graphics/test_sprite.c -o build/test_sprite.o -Isrc -Itests

# 3. Compila a main do teste diretamente para a pasta build/
build/main_test.o: tests/main_test.c
	gcc -c tests/main_test.c -o build/main_test.o -Isrc -Itests

# 4. Busca os arquivos .o dentro de build/ e gera o executável lá dentro
test: build/sprite.o build/test_sprite.o build/main_test.o
	gcc -o tests/run_tests build/main_test.o build/test_sprite.o build/sprite.o

# Apaga os arquivos de dentro da build e da pasta tests
clean:
	@if exist build\*.o del /q build\*.o
	@if exist build\*.exe del /q build\*.exe
	@if exist tests\run_tests del /q tests\run_tests
	@if exist tests\run_tests.exe del /q tests\run_tests.exe