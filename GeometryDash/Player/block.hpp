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

enum Player_Tyle {
    Block, Ship, Ball, Spider, Wave
};

class pBlock : public ImageLoader{
public:
    pBlock();
    ~pBlock();
    
    void Show(SDL_Renderer *gRenderer, SDL_Rect *clip = NULL);
    
    void HandleEvent(SDL_Event event);
    
    void Jump();
    
    void GetMap(Map_position map) {
        map_start_x = map.start_x;
    }
    
    int Pos_x() {return pos_x;}
    
    void DoBlock();
    
    void CheckToMap();
    
private:
    float pos_x;
    float pos_y;
    
    float val_x;
    float val_y;
    
    bool onGround = false;
    bool isJumping = false;
    int reverseGravity = 1;
    
    int map_start_x;
    
    ImageLoader character;
};

#endif /* block_hpp */
