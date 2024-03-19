//
//  Map.cpp
//  GeometryDash
//
//  Created by Nguyễn Bảo Long on 11/3/24.
//

#include "Map.hpp"
#include <fstream>

void Map::LoadMap(std::string s) {
    std::ifstream file(s);
    if(!file.is_open()) std::cout << "Can't open " << s << std::endl;
    for(int i = 0; i < MAX_MAP_Y; i++) {
        for(int j = 0; j < MAX_MAP_X; j++) {
            file >> MapType[i][j];
        }
    }
    file.close();
}

void Map::LoadTileMap(SDL_Renderer *gRenderer) {
    for(int i = 1; i <= MAX_TILE; i++) {
        std::string s;
        if(i < 10) {
            s += "MapGD/map";
        } else {
            s += "MapGD/gate";
        }
        s += std::to_string(i%10);
        s += ".png";
        TileMap[i].loadFromFile(s, gRenderer);
    }
    game_map.start_x = 0;
    game_map.start_y = 0;
    game_map.max_x = MAX_MAP_X * TILE_SIZE;
    game_map.max_y = MAX_MAP_Y * TILE_SIZE;
}

void Map::DrawMap(SDL_Renderer *gRenderer) {
    int x1 = (game_map.start_x % TILE_SIZE) * -1;
    int x2 = x1 + SCREEN_WIDTH + TILE_SIZE;
    
    int y1 = (game_map.start_y % TILE_SIZE) * -1;
    int y2 = y1 + SCREEN_HEIGHT + TILE_SIZE;
    
    int tile_x = game_map.start_x / TILE_SIZE;
    int tile_y = game_map.start_y / TILE_SIZE;
    
    for(int i = y1; i < y2; i+=TILE_SIZE) {
        tile_x = game_map.start_x / TILE_SIZE;
        for(int j = x1; j < x2; j+=TILE_SIZE) {
            int temp = MapType[tile_y][tile_x];
            if(temp > 0) {
                TileMap[temp].setRect(j, i);
                TileMap[temp].render(gRenderer);
            }
            tile_x++;
        }
        tile_y++;
    }
    game_map.start_x = pos_x-3*TILE_SIZE;
    if(pos_x <= 3*TILE_SIZE) {
        game_map.start_x = 0;
    } else if(pos_x >= game_map.max_x - SCREEN_WIDTH + 3*TILE_SIZE) {
        game_map.start_x = game_map.max_x - SCREEN_WIDTH;
    }
}
