#include "GameEngine/BaseFunc.hpp"
#include "GameEngine/BaseObjects.hpp"
#include "GameEngine/Map.hpp"
#include "Player/block.hpp"
#include "GameEngine/Time.hpp"

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Scene textures
ImageLoader gBlockTexture;
ImageLoader gBackgroundTexture;

Map gMap;

pBlock player;

Timer gTime;

int main( int argc, char* args[] )
{
    if( !init() )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
        if( !loadMedia() )
        {
            printf( "Failed to load media!\n" );
        }
        else
        {
            bool quit = false;
            
            SDL_Event e;
//            gMap.LoadMap("djsk");
            gMap.LoadTileMap(gRenderer);
            player.loadImage(gRenderer);

            while( !quit )
            {
                gTime.start();
                while( SDL_PollEvent( &e ) != 0 )
                {
                    if( e.type == SDL_QUIT )
                    {
                        quit = true;
                    }
                    player.HandleEvent(e);
                }

                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear(gRenderer);

                gBackgroundTexture.render(gRenderer);
                
                gMap.getPos_x(player.Pos_x());
                
                gMap.DrawMap(gRenderer);
                
                player.GetMap(gMap.getMap());
                
                switch (player.getType()) {
                    case BLOCK:
                        player.DoBlock();
                        player.ShowBlock(gRenderer);
                        break;
                    case BALL:
                        player.DoBall();
                        player.ShowBall(gRenderer);
                        break;
                    case SHIP:
                        player.DoShip();
                        player.ShowShip(gRenderer);
                        break;
                    case UFO:
                        player.DoUFO();
                        player.ShowUFO(gRenderer);
                        break;
                    case SPIDER:
                        player.DoSpider();
                        player.ShowSpider(gRenderer);
                        break;
                    case ROBOT:
                        player.DoRobot();
                        player.ShowRobot(gRenderer);
                        break;
                    case WAVE:
                        player.DoWave();
                        player.ShowWave(gRenderer);
                        break;
                }

                SDL_RenderPresent(gRenderer);
                
                int real_time = gTime.getTicks();
                if(real_time < TIME_1_FPS) {
                    SDL_Delay(TIME_1_FPS-real_time);
                }
            }
        }
    }

    //Free resources and close SDL
    close();

    return 0;
}

bool init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Set texture filtering to linear
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            printf( "Warning: Linear texture filtering not enabled!" );
        }

        //Create window
        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Create renderer for window
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
            if( gRenderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }
            }
        }
    }

    return success;
}

bool loadMedia()
{
    //Loading success flag
    bool success = true;
    
    if( !gBlockTexture.loadFromFile( "icon_30.png", gRenderer ) )
    {
        printf( "Failed to load background texture image!\n" );
        success = false;
    }

    //Load background texture
    if( !gBackgroundTexture.loadFromFile( "hinh.png", gRenderer ) )
    {
        printf( "Failed to load background texture image!\n" );
        success = false;
    }

    return success;
}

void close()
{
    //Free loaded images
    gBlockTexture.free();
    gBackgroundTexture.free();
    
    //Destroy window
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;
    
    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}
