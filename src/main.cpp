#include <iostream>

#define SDL_MAIN_HANDLED 

#include "SDL2/SDL.h"

int main(int argc , char **argv) {
    //启动SDL
    SDL_Init( SDL_INIT_EVERYTHING );
    
    //退出SDL 
    SDL_Quit();

    std::cout << "Hello World !!! " << std::endl;
    return 0;
}


