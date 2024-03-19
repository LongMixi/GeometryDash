//
//  block.cpp
//  GeometryDash
//
//  Created by Nguyễn Bảo Long on 10/3/24.
//

#include "block.hpp"

pBlock::pBlock() {
    pos_x = -BLOCK_SIZE;
    pos_y = SCREEN_HEIGHT-3*TILE_SIZE;
    val_x = 0;
    val_y = 0;
    angle = 0;
    mouseClick = 0;
    mouseRepeat = false;
}

pBlock::~pBlock() {
    pos_x = 0;
    pos_y = 0;
    val_x = 0;
    val_y = 0;
    angle = 0;
    mouseClick = 0;
    mouseRepeat = false;
}

void pBlock::HandleEvent(SDL_Event event) {
    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT && !mouseRepeat) {
        mouseClick = 1;
        mouseRepeat = true;
    } else if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT) {
        mouseClick = 0;
        mouseRepeat = false;
    }
}

void pBlock::Show(SDL_Renderer *gRenderer, SDL_Rect *clip) {
    bool res = character.loadFromFile("icon_30.png", gRenderer);
    if(res != false) {
        character.setRect(pos_x - map_start_x , pos_y);
        std::cout << pos_x << " " << pos_y << std::endl;
        character.renderEx(gRenderer, NULL, SDL_FLIP_NONE);
        if(!onGround) {
            character.angle += 12 * reverseGravity;
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
        val_y += GRAVITY * reverseGravity;
        if(val_y * reverseGravity >= MAX_FALL_SPEED) {
            val_y = MAX_FALL_SPEED * reverseGravity;
        }
    }
    if(mouseClick && !isJumping) {
        val_y = -JUMP_SPEED * reverseGravity;
        isJumping = true;
        onGround = false;
    }
    CheckToMap();
    pos_x += val_x;
    pos_y += val_y;
}

void pBlock::DoBall() {
    val_x = RUN_SPEED;
    if(!onGround) {
        val_y += GRAVITY * reverseGravity;
        if(val_y * reverseGravity >= MAX_FALL_SPEED) {
            val_y = MAX_FALL_SPEED * reverseGravity;
        }
    }
    CheckToMap();
    if(onGround && mouseClick) {
        reverseGravity *= -1;
        onGround = false;
    }
    if(mouseRepeat == true) {
        mouseClick = 0;
    }
    pos_x += val_x;
    pos_y += val_y;
}


void pBlock::DoSpider() {
    val_x = RUN_SPEED;
    if(!onGround && !isJumping) {
        val_y += GRAVITY * reverseGravity;
        if(val_y * reverseGravity >= MAX_FALL_SPEED) {
            val_y = MAX_FALL_SPEED * reverseGravity;
        }
    }
    if(onGround && mouseClick) {
        reverseGravity *= -1;
        val_y = 159 * reverseGravity;
        onGround = false;
    }
    
    //khi lap phim thi doi lai trang thai chuot
    if(mouseRepeat == true) {
        mouseClick = 0;
    }
    
    CheckToMap();
    pos_x += val_x;
    pos_y += val_y;
}


void pBlock::DoShip() {
    val_x = RUN_SPEED;
    if(!onGround) {
        val_y += GRAVITY * reverseGravity;
        if(val_y * reverseGravity >= MAX_FALL_SPEED) {
            val_y = MAX_FALL_SPEED * reverseGravity;
        }
    }
    if(mouseClick) {
        val_y -= 4;
        if(val_y <= -MAX_FALL_SPEED) {
            val_y = -MAX_FALL_SPEED;
        }
    }
    CheckToMap();
    pos_x += val_x;
    pos_y += val_y;
}


void pBlock::DoWave() {
    val_x = RUN_SPEED;
    if(!onGround) {
        val_y += GRAVITY * reverseGravity;
        if(val_y * reverseGravity >= MAX_FALL_SPEED) {
            val_y = MAX_FALL_SPEED * reverseGravity;
        }
    }
    if(mouseClick) {
        val_y = -RUN_SPEED;
    } else {
        val_y = RUN_SPEED;
    }
    CheckToMap();
    pos_x += val_x;
    pos_y += val_y;
}


void pBlock::DoRobot() {
    val_x = RUN_SPEED;
    if(!onGround && !isJumping) {
        val_y += GRAVITY * reverseGravity;
        if(val_y * reverseGravity >= MAX_FALL_SPEED) {
            val_y = MAX_FALL_SPEED * reverseGravity;
        }
    }
    if(onGround && mouseClick) {
        reverseGravity *= -1;
        val_y = 159 * reverseGravity;
        onGround = false;
    }
    
    //khi lap phim thi doi lai trang thai chuot
    if(mouseRepeat == true) {
        mouseClick = 0; 
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
    y1 = pos_y/TILE_SIZE;
    y2 = (pos_y + BLOCK_SIZE - 1)/TILE_SIZE;
    
    //check horizontal
    if(MapType[y1][x2] == 11 || MapType[y2][x2] == 11) {}
    else if(MapType[y1][x2] == 12 || MapType[y2][x2] == 12) {}
    else if(MapType[y1][x2] != 0 || MapType[y2][x2] != 0) {
        pos_x = -TILE_SIZE;
        reverseGravity = 1;
        pos_y = SCREEN_HEIGHT-3*TILE_SIZE;
    }
    
    //check vertical
    x1 = pos_x/TILE_SIZE;
    x2 = (pos_x + BLOCK_SIZE - 1)/TILE_SIZE;
    if(reverseGravity > 0) y1 = (pos_y + val_y)/TILE_SIZE;
    else y1 = (pos_y + val_y - 1)/TILE_SIZE;
    y2 = (pos_y + val_y + BLOCK_SIZE)/TILE_SIZE;
    
    if(MapType[y1][x1] == 11 || MapType[y2][x2] == 11 || MapType[y2][x1] == 11 || MapType[y1][x2] == 11
       || MapType[y1-1][x1] == 11 || MapType[y2-1][x2] == 11 || MapType[y2-1][x1] == 11 || MapType[y1-1][x2] == 11) {
        onGround = false;
        reverseGravity = -1;
    }
    else if(MapType[y1][x1] == 12 || MapType[y2][x2] == 12 || MapType[y2][x1] == 12 || MapType[y1][x2] == 12
       || MapType[y1-1][x1] == 12 || MapType[y2-1][x2] == 12 || MapType[y2-1][x1] == 12 || MapType[y1-1][x2] == 12) {
        onGround = false;
        reverseGravity = 1;
    }
    else if(MapType[y1][x1] != 0 || MapType[y2][x2] != 0 || MapType[y2][x1] != 0 || MapType[y1][x2] != 0) {
        if(reverseGravity > 0) pos_y = y1*TILE_SIZE;
        else pos_y = (y1+1)*TILE_SIZE;
        onGround = true;
        isJumping = false;
        val_y = 0;
    } else {
        onGround = false;
    }
    
    y1 = (pos_y + val_y - 1)/TILE_SIZE;
    
    if(MapType[y2][x1] != 0 || MapType[y1][x2] != 0) {
        pos_y = (y1+1)*TILE_SIZE;
        isJumping = false;
        val_y = 0;
    } else {
        onGround = false;
    }
}
