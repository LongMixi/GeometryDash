//
//  block.hpp
//  GeometryDash
//
//  Created by Nguyễn Bảo Long on 10/3/24.
//

#ifndef block_hpp
#define block_hpp

#include "BaseFunc.hpp"
#include "BaseObjects.hpp"
#include "Time.hpp"

class pBlock : public ImageLoader{
public:
    pBlock();
    ~pBlock();
    
    void loadImage(SDL_Renderer * renderer);
    
    void ShowBlock(SDL_Renderer *gRenderer, SDL_Rect *clip = NULL);
    void ShowBall(SDL_Renderer *gRenderer, SDL_Rect *clip = NULL);
    void ShowShip(SDL_Renderer *gRenderer, SDL_Rect *clip = NULL);
    void ShowWave(SDL_Renderer *gRenderer, SDL_Rect *clip = NULL);
    void ShowUFO(SDL_Renderer *gRenderer, SDL_Rect *clip = NULL);
    void ShowRobot(SDL_Renderer *gRenderer, SDL_Rect *clip = NULL);
    void ShowSpider(SDL_Renderer *gRenderer, SDL_Rect *clip = NULL);
    
    void HandleEvent(SDL_Event event);
    
    void GetMap(Map_position map) {
        map_start_x = map.start_x;
    }
    
    int Pos_x() {return pos_x;}
    
    int getType() {return typePlayer;};
    
    void DoBlock();
    void DoBall();
    void DoSpider();
    void DoShip();
    void DoWave();
    void DoRobot();
    
    void CheckToMap();
    
private:
    float pos_x;
    float pos_y;
    
    float val_x;
    float val_y;
    
    bool onGround = false;
    bool isJumping = false;
    int reverseGravity = 1;
    bool mouseRepeat = false;
    int typePlayer = SPIDER;
    int val_angle = 0;
    int cntFrame = 0;
    
    int map_start_x;
    
    Timer mTime;
    ImageLoader mBlock, mBall, mShip, mWave;
    ImageLoader mRobot[15], mSpider[16];
};

#endif /* block_hpp */
