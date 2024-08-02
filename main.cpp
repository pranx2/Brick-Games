#include<SDL2/SDL.h>

//Window Screen
#define width 720  
#define height 480

//Background Image to Windows width distance;
#define winposx 0  
#define winposy 0


//Ball Size
#define ball_width 30
#define ball_height 20

//Ball position from window screen;
#define ballposx 10
#define ballposy 10
int ballx = ballposx;
int bally = ballposy;
int ballvelx = 1;//ball Velocity X position;
int ballvely = 1;//ball Velocity Y position;

//Checking the user Interaction;
bool quit = false;
SDL_Event event;
void EventHandler(){
SDL_PollEvent(&event);
 if(event.type == SDL_QUIT){
  quit = true;
 }
}

//Changing Ball position by user Interaction;
void moveBall(){
  ballx = ballx + ballvelx;
  bally = bally + ballvely;
}
//Ball bouncing;
void Ball_Collision(){
 if(ballx < winposx || ballx > width-ball_width){
  ballvelx =-ballvelx;
 }
 if(bally < winposy || bally > height - ball_width){
  ballvely =-ballvely; 
 }
}

int main( int argc, char **argv){
//Creating Window;
SDL_Init(SDL_INIT_VIDEO);
SDL_Window *window = SDL_CreateWindow("Brick Games",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_UNDEFINED,width,height,0);
//Surface Renderer;
SDL_Renderer *renderer = SDL_CreateRenderer(window,-1,0);

SDL_Rect BGRect ={winposx,winposy,width,height};//BackGround Dimension;
SDL_Surface *BG = SDL_LoadBMP("Textures/BG.bmp"); //BG surface add;
SDL_Surface *ball =SDL_LoadBMP("Textures/ball.bmp");//Ball surface add;
SDL_Texture *ballTexture = SDL_CreateTextureFromSurface(renderer,ball);
SDL_Texture *BGTexture = SDL_CreateTextureFromSurface(renderer,BG);
SDL_RenderCopy(renderer,BGTexture,NULL,&BGRect);

 
//Windows running time/s;
//Game loop
while (!quit){
 EventHandler();
 SDL_Rect ballRect = {ballx,bally,ball_width,ball_height};//Ball Dimension; windows winposX,winposY,Image posX,posY;
 moveBall();
 Ball_Collision();
SDL_RenderCopy(renderer,BGTexture,NULL,&BGRect);
SDL_RenderCopy(renderer,ballTexture,NULL,&ballRect);
SDL_RenderPresent(renderer);
SDL_RenderClear(renderer);
}
//Closing Window;
//SDL_Delay(6000);//Test 0x1;
SDL_Quit();
return 0;
}