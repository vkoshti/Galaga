gcc -c Representation.c -lSDL2 -lmingw32 -lSDL2_main -lSDL2_image
gcc -c Galaga.c -lSDL2 -lmingw32 -lSDL2_main -lSDL2_image
gcc *.o -o Galaga  -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
Galaga.exe