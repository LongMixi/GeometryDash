#ifndef BaseObjects_hpp
#define BaseObjects_hpp

#include "BaseFunc.hpp"

class ImageLoader {
public:
    ImageLoader();
    ~ImageLoader();
    
    double angle;
    
    bool loadFromFile(std::string path, SDL_Renderer* renderer);
    
    void free();
    
    SDL_Rect getRect() const {return rect;}
    
    void setRect(const int &a, const int &b) {
        rect.x = a;
        rect.y = b;
    }
    
    void render(SDL_Renderer* renderer, SDL_Rect* clip = NULL);
    
    void renderEx(SDL_Renderer* renderer, SDL_Rect* clip, SDL_RendererFlip flip);

protected:
    SDL_Texture* mTexture;
    SDL_Rect rect;
};

#endif
