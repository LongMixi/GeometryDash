#include<iostream>
#include<SDL2/SDL.h>
//#include<SDL2_image/SDL_image.h>

using namespace std;

const int SCREEN_WIGHT = 960;
const int SCREEN_HEIGHT = 540;

SDL_Window * window = NULL;
SDL_Surface * background = NULL;
SDL_Surface * image = NULL;
SDL_Surface * character = NULL;

bool init() {
    bool success = true;
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << SDL_GetError();
        success = false;
    } else {
        window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIGHT, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(window == NULL) {
            cout << SDL_GetError();
            success = false;
        }
    }
    background = SDL_GetWindowSurface(window);
    return success;
}

bool loadBMP() {
//    image = SDL_LoadBMP("02_getting_an_image_on_the_screen/geometry_dash.bmp");
//    if(image == NULL) {
//        cout << SDL_GetError();
//        return false;
//    }
    return true;
}

void close() {
    SDL_FreeSurface(image);
    image = NULL;
    
    SDL_DestroyWindow(window);
    window = NULL;
    
    SDL_Quit();
}

int main(int argc, char *args[]) {
    if(!init()) {
        cout << "Faild init";
    } else {
        if(!loadBMP()) cout << "Faild loadBMP";
        else {
            SDL_BlitSurface(image, NULL, background, NULL);
            SDL_UpdateWindowSurface(window);
            
            //open window until press any key or quit
            SDL_Event e;
            bool quit = false;
            while( quit == false ) {
                while( SDL_PollEvent( &e ) ){
                    if( e.type == SDL_QUIT || e.type == SDL_KEYDOWN)
                        quit = true;
                }
            }
            
        }
    }
    close();
}

