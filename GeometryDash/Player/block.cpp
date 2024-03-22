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

void pBlock::loadImage(SDL_Renderer *renderer) {
    mBlock.loadFromFile("icon_30.png", renderer);
    mBall.loadFromFile("ball_23.png", renderer);
    mShip.loadFromFile("ship_86.png", renderer);
    mWave.loadFromFile("wave_13.png", renderer);
    for(int i = 1; i <= 13; i++) {
        std::string s = "robotRun";
        s += std::to_string(i);
        s += ".png";
        mRobot[i-1].loadFromFile(s, renderer);
    }
    mRobot[13].loadFromFile("robotFall.png", renderer);
    mRobot[14].loadFromFile("robotJump.png", renderer);
    for(int i = 0; i <= 13; i++) {
        std::string s = "spiderRun";
        s += std::to_string(i);
        s += ".png";
        mSpider[i].loadFromFile(s, renderer);
    }
    mSpider[14].loadFromFile("spiderFall.png", renderer);
    mSpider[15].loadFromFile("spiderJump.png", renderer);
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

void pBlock::ShowBlock(SDL_Renderer *gRenderer, SDL_Rect *clip) {
    mBlock.setRect(pos_x - map_start_x , pos_y);
    std::cout << pos_x << " " << pos_y << std::endl;
    mBlock.renderEx(gRenderer, NULL, SDL_FLIP_NONE);
    if(!onGround) {
        mBlock.angle += 12 * reverseGravity;
        if(mBlock.angle >= 360) {
            mBlock.angle = 0;
        }
    }
    else mBlock.angle = 0;
}

void pBlock::ShowBall(SDL_Renderer *gRenderer, SDL_Rect *clip) {
    mBall.setRect(pos_x - map_start_x , pos_y);
    mBall.renderEx(gRenderer, NULL, SDL_FLIP_NONE);
    mBall.angle += 12*reverseGravity;
    if(mBall.angle >= 360) mBall.angle = 0;
}

void pBlock::ShowWave(SDL_Renderer *gRenderer, SDL_Rect *clip) {
    mWave.setRect(pos_x - map_start_x , pos_y);
    mWave.renderEx(gRenderer, NULL, SDL_FLIP_NONE);
    if(mouseClick) mWave.angle = -45;
    else if(onGround) mWave.angle = 0;
    else mWave.angle = 45;
}

void pBlock::ShowShip(SDL_Renderer *gRenderer, SDL_Rect *clip) {
    mShip.setRect(pos_x - map_start_x , pos_y);
    mShip.renderEx(gRenderer, NULL, SDL_FLIP_NONE);
    if(mouseClick) mShip.angle -= 2.5;
    else mShip.angle += 2;
    if(onGround) mShip.angle = 0;
    if(mShip.angle*reverseGravity >= 30) {
        mShip.angle = 30*reverseGravity;
    } else if(mShip.angle*reverseGravity <= -30) {
        mShip.angle = -30*reverseGravity;
    }
}


void pBlock::ShowRobot(SDL_Renderer *gRenderer, SDL_Rect *clip) {
    if(onGround) {
        mRobot[cntFrame/2].setRect(pos_x - map_start_x , pos_y);
        if(reverseGravity < 0) {
            mRobot[cntFrame/2].renderEx(gRenderer, NULL, SDL_FLIP_VERTICAL);
        }
        else mRobot[cntFrame/2].renderEx(gRenderer, NULL, SDL_FLIP_NONE);
        cntFrame++;
        if(cntFrame == 26) cntFrame = 0;
    } else if(mouseClick) {
        mRobot[14].setRect(pos_x - map_start_x , pos_y);
        if(reverseGravity < 0) mRobot[14].renderEx(gRenderer, NULL, SDL_FLIP_VERTICAL);
        else mRobot[14].render(gRenderer);
        cntFrame = 0;
    } else {
        mRobot[13].setRect(pos_x - map_start_x , pos_y);
        if(reverseGravity < 0) mRobot[13].renderEx(gRenderer, NULL, SDL_FLIP_VERTICAL);
        else mRobot[13].render(gRenderer);
        cntFrame = 0;
    }
}


void pBlock::ShowSpider(SDL_Renderer *gRenderer, SDL_Rect *clip) {
    if(onGround) {
        mSpider[cntFrame/2].setRect(pos_x - map_start_x , pos_y);
        if(reverseGravity < 0) {
            mSpider[cntFrame/2].renderEx(gRenderer, NULL, SDL_FLIP_VERTICAL);
        }
        else mSpider[cntFrame/2].renderEx(gRenderer, NULL, SDL_FLIP_NONE);
        cntFrame++;
        if(cntFrame == 28) cntFrame = 0;
    } else {
        mSpider[14].setRect(pos_x - map_start_x , pos_y);
        if(reverseGravity < 0) mSpider[14].renderEx(gRenderer, NULL, SDL_FLIP_VERTICAL);
        else mSpider[14].render(gRenderer);
        cntFrame = 0;
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
        val_y = (TILE_SIZE/2) * reverseGravity;
        for(int i = 0; i < 10; i++) {
            pos_y += val_y;
            CheckToMap();
        }
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
        val_y += GRAVITY/2 * reverseGravity;
        if(val_y * reverseGravity >= MAX_FALL_SPEED/2) {
            val_y = MAX_FALL_SPEED/2 * reverseGravity;
        }
    }
    if(mouseClick) {
        val_y -= 3;
        if(val_y <= -MAX_FALL_SPEED/2) {
            val_y = -MAX_FALL_SPEED/2;
        }
    }
    CheckToMap();
    pos_x += val_x;
    pos_y += val_y;
}


void pBlock::DoWave() {
    val_x = RUN_SPEED;
    if(!onGround) {
        val_y = RUN_SPEED;
    }
    if(mouseClick) {
        val_y = -RUN_SPEED;
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
    if(mouseClick) {
        if(val_y*reverseGravity <= 0) val_y = -3.2*2*TILE_SIZE/FPS*reverseGravity;
        if(onGround) mTime.start();
    }
    if(mouseRepeat && mTime.isStarted()) {
//        std::cout << mTime.getTicks() << " ";
        if(mTime.getTicks() > 500) {
            mouseClick = 0;
            mTime.stop();
        }
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
    if((MapType[y1][x2] >= 11 && MapType[y1][x2] <= 20) || (MapType[y2][x2] >= 11 && MapType[y1][x2] <= 20)) {}
        // player chet quay tro lai vi tri ban dau
    else if(MapType[y1][x2] != 0 || MapType[y2][x2] != 0) {
        pos_x = -TILE_SIZE;
        reverseGravity = 1;
        pos_y = SCREEN_HEIGHT-3*TILE_SIZE;
        typePlayer = SPIDER;
        val_y = 0;
    }
    
    //check vertical under
    x1 = pos_x/TILE_SIZE;
    x2 = (pos_x + BLOCK_SIZE - 1)/TILE_SIZE;
    if(reverseGravity > 0) y1 = (pos_y + val_y)/TILE_SIZE;
    else y1 = (pos_y + val_y - 1)/TILE_SIZE;
    y2 = (pos_y + val_y + BLOCK_SIZE)/TILE_SIZE;
    
    if(MapType[y1][x1] == 11 || MapType[y2][x2] == 11 || MapType[y2][x1] == 11 || MapType[y1][x2] == 11
       || MapType[y1-1][x1] == 11 || MapType[y2-1][x2] == 11 || MapType[y2-1][x1] == 11 || MapType[y1-1][x2] == 11) {
        onGround = false;
        reverseGravity = -1;
        val_y = 0;
    }
    else if(MapType[y1][x1] == 12 || MapType[y2][x2] == 12 || MapType[y2][x1] == 12 || MapType[y1][x2] == 12
       || MapType[y1-1][x1] == 12 || MapType[y2-1][x2] == 12 || MapType[y2-1][x1] == 12 || MapType[y1-1][x2] == 12) {
        onGround = false;
        reverseGravity = 1;
        val_y = 0;
    }
    else if(MapType[y1][x1] == 13 || MapType[y2][x2] == 13 || MapType[y2][x1] == 13 || MapType[y1][x2] == 13
       || MapType[y1-1][x1] == 13 || MapType[y2-1][x2] == 13 || MapType[y2-1][x1] == 13 || MapType[y1-1][x2] == 13) {
        onGround = false;
        reverseGravity *= 1;
        val_y = 0;
    }
    else if(MapType[y1][x1] == 14 || MapType[y2][x2] == 14 || MapType[y2][x1] == 14 || MapType[y1][x2] == 14
       || MapType[y1-1][x1] == 14 || MapType[y2-1][x2] == 14 || MapType[y2-1][x1] == 14 || MapType[y1-1][x2] == 14) {
        typePlayer = BALL;
    }
    else if(MapType[y1][x1] == 15 || MapType[y2][x2] == 15 || MapType[y2][x1] == 15 || MapType[y1][x2] == 15
       || MapType[y1-1][x1] == 15 || MapType[y2-1][x2] == 15 || MapType[y2-1][x1] == 15 || MapType[y1-1][x2] == 15) {
        typePlayer = BLOCK;
    }
    else if(MapType[y1][x1] == 16 || MapType[y2][x2] == 16 || MapType[y2][x1] == 16 || MapType[y1][x2] == 16
       || MapType[y1-1][x1] == 16 || MapType[y2-1][x2] == 16 || MapType[y2-1][x1] == 16 || MapType[y1-1][x2] == 16) {
        typePlayer = ROBOT;
    }
    else if(MapType[y1][x1] == 17 || MapType[y2][x2] == 17 || MapType[y2][x1] == 17 || MapType[y1][x2] == 17
       || MapType[y1-1][x1] == 17 || MapType[y2-1][x2] == 17 || MapType[y2-1][x1] == 17 || MapType[y1-1][x2] == 17) {
        typePlayer = SHIP;
        val_angle = 0;
    }
    else if(MapType[y1][x1] == 18 || MapType[y2][x2] == 18 || MapType[y2][x1] == 18 || MapType[y1][x2] == 18
       || MapType[y1-1][x1] == 18 || MapType[y2-1][x2] == 18 || MapType[y2-1][x1] == 18 || MapType[y1-1][x2] == 18) {
        typePlayer = SPIDER;
    }
    else if(MapType[y1][x1] == 19 || MapType[y2][x2] == 19 || MapType[y2][x1] == 19 || MapType[y1][x2] == 19
       || MapType[y1-1][x1] == 19 || MapType[y2-1][x2] == 19 || MapType[y2-1][x1] == 19 || MapType[y1-1][x2] == 19) {
        typePlayer = UFO;
    }
    else if(MapType[y1][x1] == 20 || MapType[y2][x2] == 20 || MapType[y2][x1] == 20 || MapType[y1][x2] == 20
       || MapType[y1-1][x1] == 20 || MapType[y2-1][x2] == 20 || MapType[y2-1][x1] == 20 || MapType[y1-1][x2] == 20) {
        typePlayer = WAVE;
    }
    else if(MapType[y1][x1] != 0 || MapType[y2][x2] != 0 || MapType[y2][x1] != 0 || MapType[y1][x2] != 0) {
        if(reverseGravity > 0) pos_y = y1*TILE_SIZE;
        else pos_y = (y1+1)*TILE_SIZE;
        onGround = true;
        isJumping = false;
        val_y = 0;
    } 
    else {
        onGround = false;
    }
    
    //check vertical top
    y1 = (pos_y + val_y - 1)/TILE_SIZE;
    
    if(MapType[y2][x1] != 0 || MapType[y1][x2] != 0) {
        pos_y = (y1+1)*TILE_SIZE;
        isJumping = false;
        val_y = 0;
    } else {
        onGround = false;
    }
}
