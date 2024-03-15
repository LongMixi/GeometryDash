//
//  block.cpp
//  GeometryDash
//
//  Created by Nguyễn Bảo Long on 10/3/24.
//

#include "block.hpp"

const int MAX_FALL_SPEED = 79;

pBlock::pBlock() {
    pos_x = 0;
    pos_y = 0;
    val_x = 0;
    val_y = 0;
    angle = 0;
    mouseClick = 0;
}

pBlock::~pBlock() {
    pos_x = -BLOCK_SIZE;
    pos_y = 0;
    val_x = 0;
    val_y = 0;
    angle = 0;
    mouseClick = 0;
}

void pBlock::HandleEvent(SDL_Event event) {
    if(event.type == SDL_MOUSEBUTTONDOWN) {
        mouseClick = 1;
    } else if(event.type == SDL_MOUSEBUTTONUP) {
        mouseClick = 0;
    }
}

void pBlock::Show(SDL_Renderer *gRenderer, SDL_Rect *clip) {
    bool res = character.loadFromFile("icon_30.png", gRenderer);
    if(res != false) {
        character.setRect(pos_x - map_start_x , pos_y);
        std::cout << pos_x << " " << pos_y << std::endl;
        character.renderEx(gRenderer, NULL, SDL_FLIP_NONE);
        if(isJumping) {
            character.angle += 12;
            if(character.angle >= 360) {
                character.angle = 0;
            }
        }
        else character.angle = 0;
    }
}

void pBlock::DoBlock() {
    val_x = RUN_SPEED;
    if(!onGround) {
        val_y += GRAVITY;
        if(val_y >= MAX_FALL_SPEED) {
            val_y = MAX_FALL_SPEED;
        }
    }
    if(mouseClick && !isJumping) {
        val_y = -JUMP_SPEED;
        isJumping = true;
        onGround = false;
    }
    CheckToMap();
    pos_x += val_x;
    pos_y += val_y;
}

void pBlock::CheckToMap() {
    int x1, x2;
    int y1, y2;
    
    x1 = (pos_x + val_x)/TILE_SIZE;
    x2 = (pos_x + val_x + BLOCK_SIZE - 1)/TILE_SIZE;
    y1 = (pos_y + 1)/TILE_SIZE;
    y2 = (pos_y + BLOCK_SIZE - 1)/TILE_SIZE;
    
    //check horizontal
    if(MapType[y1][x2] != 0 || MapType[y2][x2] != 0) {
        pos_x = x1*TILE_SIZE;
    }
    
    //check vertical
    x1 = pos_x/TILE_SIZE;
    x2 = (pos_x + BLOCK_SIZE - 1)/TILE_SIZE;
    y1 = (pos_y + val_y + 1)/TILE_SIZE;
    y2 = (pos_y + val_y + BLOCK_SIZE - 1)/TILE_SIZE;
    
    if(MapType[y1][x1] != 0 || MapType[y2][x2] != 0) {
        pos_y = (y1)*TILE_SIZE;
        onGround = true;
        isJumping = false;
        val_y = 0;
    } else {
        onGround = false;
    }
    
}




