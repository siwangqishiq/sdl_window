#include <iostream>

#define SDL_MAIN_HANDLED    //这行必须加上 否则运行不了

#include "SDL2/SDL.h"
#include "SDL2/SDL_mutex.h"

int hello_sdl(){
    //启动SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1){
        std::cout << SDL_GetError() << std::endl;
        return 1;
    }
    
    SDL_Window *win = nullptr;
    win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
    if (win == nullptr){
        std::cout << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Renderer *ren = nullptr;
    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr){
        std::cout << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Surface *bmp = nullptr;
    bmp = SDL_LoadBMP("assets/songxia.bmp");
    if (bmp == nullptr){
        std::cout << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Texture *tex = nullptr;
    tex = SDL_CreateTextureFromSurface(ren, bmp);
    SDL_FreeSurface(bmp);

    SDL_RenderClear(ren);
    SDL_RenderCopy(ren, tex, nullptr, nullptr);
    SDL_RenderPresent(ren);

    SDL_Delay(2000);

    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);

    SDL_Quit();

    return 0;
}

SDL_Thread *thread = nullptr;
SDL_cond *cond = nullptr;
SDL_mutex *lock = nullptr;


int thread_func(void *data){
    for(int i = 0 ; i < 4 ; i++){
        std::cout << SDL_GetThreadName(thread) << " index = " << i << std::endl;
        SDL_Delay(1000);
    }

    std::cout << "thread end" << std::endl;

    SDL_CondSignal(cond);

    return 0;
}

int cond_signal_demo(){
    //启动SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1){
        std::cout << SDL_GetError() << std::endl;
        return 1;
    }

    cond = SDL_CreateCond();
    lock = SDL_CreateMutex();

    thread = SDL_CreateThread(thread_func , "thread1" , nullptr);

    std::cout << "main thread start wait..." <<std::endl;

    SDL_CondWait(cond , lock);

    std::cout << "main thread wait end" << std::endl;

    // for(int i = 0 ; i < 10 ; i++){
    //     std::cout << "main thread " << i << std::endl;
    //     SDL_Delay(1000);
    // }

    SDL_Quit();

    std::cout << "main thread end" << std::endl;

    return 0;
}

int main(int argc , char **argv) {
    //cond_signal_demo();
    
    return 0;
}


