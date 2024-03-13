#ifndef BaseObjects_hpp
#define BaseObjects_hpp

#include "BaseFunc.hpp"

class ImageLoader {
public:
    ImageLoader();
    ~ImageLoader();
    bool loadFromFile(std::string path, SDL_Renderer* renderer);
    void free();
    void render(int x, int y, SDL_Renderer* renderer, SDL_Rect* clip = nullptr);

private:
    SDL_Texture* mTexture;
    int mWidth;
    int mHeight;
};

#endif
