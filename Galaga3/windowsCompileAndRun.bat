gcc -c Representation.c
gcc -c Galaga.c
gcc *.o -o Galaga  -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
Galaga.exe
