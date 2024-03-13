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
        std::string s = "MapGD/map";
        s += std::to_string(i);
        s += ".png";
        TileMap[i].loadFromFile(s, gRenderer);
    }
}

void Map::DrawMap(SDL_Renderer *gRenderer) {
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 15; j++) {
            int temp = MapType[i][j];
            if(temp > 0) TileMap[temp].render(j*TILE_SIZE, i*TILE_SIZE, gRenderer);
        }
    }
}
