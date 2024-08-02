#include<SDL2/SDL.h>
int main (int argc, char **argv){
SDL_Init(SDL_INIT_VIDEO);
SDL_Window *window = SDL_CreateWindow("Brick Games",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,640,480,0);



SDL_Quit();
return 0;
}
