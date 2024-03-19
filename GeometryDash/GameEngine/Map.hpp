//
//  Map.hpp
//  GeometryDash
//
//  Created by Nguyễn Bảo Long on 11/3/24.
//

#ifndef Map_hpp
#define Map_hpp

#include "BaseFunc.hpp"
#include "BaseObjects.hpp"

class Map : public ImageLoader{
public:
    Map() {;};
    ~Map() {;};
    void LoadMap(std::string s);
    void LoadTileMap(SDL_Renderer *gRenderer);
    void DrawMap(SDL_Renderer *gRenderer);
    Map_position getMap() {return game_map;}
    void getPos_x(const int &a) {
        pos_x = a;
    }
private:
    ImageLoader TileMap[MAX_TILE];
    Map_position game_map;
    int pos_x;
};

#endif /* Map_hpp */
