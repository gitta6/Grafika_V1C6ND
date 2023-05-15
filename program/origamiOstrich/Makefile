all:
	gcc -Iinclude/ src/app.c src/camera.c src/main.c src/scene.c src/utils.c src/texture.c src/ostrich.c -lobj -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lopengl32 -lm -w -o origamiOstrich.exe -Wall -Wextra -Wpedantic 

linux:
	gcc -Iinclude/ src/app.c src/camera.c src/main.c src/scene.c src/utils.c -lobj -lSDL2 -lSDL2_image -lGL -lm -o origin -Wall -Wextra -Wpedantic
