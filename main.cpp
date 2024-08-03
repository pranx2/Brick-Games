#include<SDL2/SDL.h>
bool  quit = false ;
SDL_Event event;
int ballx = 10;
int bally = 10;
int ballvelx = 1;
int ballvely = 1;

int bkw = 800;
int bkh = 600;
int brickw = 80;
int brickh = 60;
SDL_Surface *bricks;
SDL_Texture *bricktexture;

SDL_Rect brickrect[3][7];
SDL_Rect ballrect = {ballx,bally,20,30};

void InitializeBrick(){
  brickrect[0][0] = {50, 50,brickw,brickh};
  brickrect[0][1] = {150,50,brickw,brickh};
  brickrect[0][2] = {250,50,brickw,brickh};
  brickrect[0][3] = {350,50,brickw,brickh};
  brickrect[0][4] = {450,50,brickw,brickh};
  brickrect[0][5] = {550,50,brickw,brickh};
  brickrect[0][6] = {650,50,brickw,brickh};
  brickrect[1][1] = {150,100,brickw,brickh};
  brickrect[1][0] = {50, 100,brickw,brickh};
  brickrect[1][2] = {250,100,brickw,brickh};
  brickrect[1][3] = {350,100,brickw,brickh};
  brickrect[1][4] = {450,100,brickw,brickh};
  brickrect[1][5] = {550,100,brickw,brickh};
  brickrect[1][6] = {650,100,brickw,brickh};
  brickrect[2][0] = {50, 150,brickw,brickh};
  brickrect[2][1] = {150,150,brickw,brickh};
  brickrect[2][2] = {250,150,brickw,brickh};
  brickrect[2][3] = {350,150,brickw,brickh};
  brickrect[2][4] = {450,150,brickw,brickh};
  brickrect[2][5] = {550,150,brickw,brickh};
  brickrect[2][6] = {650,150,brickw,brickh};
}


int bkwmin = 0;
int bkhmin = 0; 
int batx = bkw/2;
int baty = bkh - 30;
void EventHandler(){
  SDL_PollEvent(&event);
  if(event.type == SDL_QUIT){
    quit = true;
  }
  else if(event.type == SDL_KEYDOWN){
    if(event.key.keysym.sym == SDLK_LEFT && batx > 0){
      batx = batx-2;
    }
    if(event.key.keysym.sym == SDLK_RIGHT && batx < bkw -60){
      batx = batx+2;
    }
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
  int ballscaling = 20;
  if(bally+ballscaling >= baty && bally+ballscaling<=baty+30 && ballx+ballscaling >= batx && ballx+ballscaling<=batx+60){
    ballvely =-ballvely;
  }
}
bool ballbreakcollisiondetect(SDL_Rect rect1, SDL_Rect rect2){
  if(rect1.x>rect2.x+rect2.w){
    return false;
  }
  if(rect1.x+rect1.w < rect2.x){
    return false;
  }
  if(rect1.y>rect2.y+rect2.h){
    return false;
  }
  if(rect1.y+rect1.h < rect2.y){
    return false;
  }
  return true;
}
void ballbreakcollision (){
  bool a;
  for(int i = 0; i<4; i++){
    for(int j= 0; j<7; j++){
    a = ballbreakcollisiondetect(brickrect[i][j],ballrect);
    if(a == true){
      brickrect[i][j].x = 3000;
      ballvely = ballvely;
      }
    }
  }
}
int main (int argc, char **argv){
SDL_Init(SDL_INIT_VIDEO);
SDL_Window *window = SDL_CreateWindow("Brick Games",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,800,600,0);
SDL_Renderer *renderer = SDL_CreateRenderer(window,-1,0);

SDL_Rect bkrect = {0,0,800,600};
InitializeBrick();
SDL_Surface *ball = SDL_LoadBMP("Textures/ball.bmp");
SDL_Surface *bk = SDL_LoadBMP("Textures/BG.bmp");
SDL_Surface *bat = SDL_LoadBMP("Textures/bat.bmp");
bricks = SDL_LoadBMP("Textures/brick.bmp");
SDL_Texture *balltexture = SDL_CreateTextureFromSurface(renderer,ball);
SDL_Texture *bktexture = SDL_CreateTextureFromSurface(renderer,bk);
SDL_Texture *battexture = SDL_CreateTextureFromSurface(renderer,bat);
bricktexture = SDL_CreateTextureFromSurface(renderer,bricks);

SDL_RenderCopy(renderer,bktexture,NULL,&bkrect);



while(!quit){
  EventHandler();

  SDL_Rect batrect = {batx,baty,60,30};
  moveBall();
  ball_collision();
  ballbreakcollision();

  SDL_RenderCopy(renderer,bktexture,NULL,&bkrect);
  SDL_RenderCopy(renderer,balltexture,NULL,&ballrect);
  SDL_RenderCopy(renderer,battexture,NULL,&batrect);
  SDL_RenderCopy(renderer,bricktexture,NULL,&brickrect[0][0]);
SDL_RenderCopy(renderer,bricktexture,NULL,&brickrect[0][1]);
SDL_RenderCopy(renderer,bricktexture,NULL,&brickrect[0][2]);
SDL_RenderCopy(renderer,bricktexture,NULL,&brickrect[0][3]);
SDL_RenderCopy(renderer,bricktexture,NULL,&brickrect[0][4]);
SDL_RenderCopy(renderer,bricktexture,NULL,&brickrect[0][5]);
SDL_RenderCopy(renderer,bricktexture,NULL,&brickrect[0][6]);
SDL_RenderCopy(renderer,bricktexture,NULL,&brickrect[1][0]);
SDL_RenderCopy(renderer,bricktexture,NULL,&brickrect[1][1]);
SDL_RenderCopy(renderer,bricktexture,NULL,&brickrect[1][2]);
SDL_RenderCopy(renderer,bricktexture,NULL,&brickrect[1][3]);
SDL_RenderCopy(renderer,bricktexture,NULL,&brickrect[1][4]);
SDL_RenderCopy(renderer,bricktexture,NULL,&brickrect[1][5]);
SDL_RenderCopy(renderer,bricktexture,NULL,&brickrect[1][6]);
SDL_RenderCopy(renderer,bricktexture,NULL,&brickrect[2][0]);
SDL_RenderCopy(renderer,bricktexture,NULL,&brickrect[2][1]);
SDL_RenderCopy(renderer,bricktexture,NULL,&brickrect[2][2]);
SDL_RenderCopy(renderer,bricktexture,NULL,&brickrect[2][3]);
SDL_RenderCopy(renderer,bricktexture,NULL,&brickrect[2][4]);
SDL_RenderCopy(renderer,bricktexture,NULL,&brickrect[2][5]);
SDL_RenderCopy(renderer,bricktexture,NULL,&brickrect[2][6]);
  SDL_RenderPresent(renderer);
  SDL_RenderClear(renderer);
}
SDL_Quit();
return 0;
}
