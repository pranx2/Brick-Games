#include<SDL2/SDL.h>
bool  quit = false ;
SDL_Event event;
int ballx = 10;
int bally = 10;
int ballvelx = 1;
int ballvely = 1;

int bkw = 800;
int bkh = 600;
int bkwmin = 0;
int bkhmin = 0; 
int batx = bkw/2;
int baty = bkh - 30;
void EventHandler(){
  SDL_PollEvent(&event);
  if(event.type == SDL_QUIT){
    quit = true;
  }
}
void moveBall(){
  ballx = ballx + ballvelx;
  bally = bally + ballvely;
}
void ball_collision(){
  if(ballx < bkwmin || ballx > bkw-30){
    ballvelx =- ballvelx;
  }
  if(bally < bkhmin || bally > bkh-30){
    ballvely =- ballvely;
  }
}
int main (int argc, char **argv){
SDL_Init(SDL_INIT_VIDEO);
SDL_Window *window = SDL_CreateWindow("Brick Games",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,800,600,0);
SDL_Renderer *renderer = SDL_CreateRenderer(window,-1,0);

SDL_Rect bkrect = {0,0,800,600};
SDL_Rect batrect = {batx,baty,60,30};
SDL_Surface *ball = SDL_LoadBMP("Textures/ball.bmp");
SDL_Surface *bk = SDL_LoadBMP("Textures/BG.bmp");
SDL_Surface *bat = SDL_LoadBMP("Textures/bat.bmp");
SDL_Texture *balltexture = SDL_CreateTextureFromSurface(renderer,ball);
SDL_Texture *bktexture = SDL_CreateTextureFromSurface(renderer,bk);
SDL_Texture *battexture = SDL_CreateTextureFromSurface(renderer,bat);


SDL_RenderCopy(renderer,bktexture,NULL,&bkrect);



while(!quit){
  EventHandler();
  SDL_Rect ballrect = {ballx,bally,20,30};
  moveBall();
  ball_collision();
  SDL_RenderCopy(renderer,bktexture,NULL,&bkrect);
  SDL_RenderCopy(renderer,balltexture,NULL,&ballrect);
  SDL_RenderCopy(renderer,battexture,NULL,&batrect);
  SDL_RenderPresent(renderer);
  SDL_RenderClear(renderer);
}
SDL_Quit();
return 0;
}
