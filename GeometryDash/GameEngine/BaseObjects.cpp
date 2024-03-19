#include "BaseObjects.hpp"
#include <iostream>

ImageLoader::ImageLoader() {
    mTexture = NULL;
    rect.x = 0;
    rect.y = 0;
    rect.w = 0;
    rect.h = 0;
    angle = 0;
}

ImageLoader::~ImageLoader() {
    free();
}

bool ImageLoader::loadFromFile(std::string s, SDL_Renderer* renderer) {
    free();

    SDL_Surface* loadedSurface = IMG_Load(s.c_str());
    if (loadedSurface == NULL) {
        std::cout << "Unable to load image " << s << "! SDL_image Error: " << IMG_GetError() << std::endl;
        return false;
    }

    mTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if (mTexture == NULL) {
        std::cout << "Unable to create texture from " << s << "! SDL Error: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(loadedSurface);
        return false;
    }

    rect.w = loadedSurface->w;
    rect.h = loadedSurface->h;
    SDL_FreeSurface(loadedSurface);
    return true;
}

void ImageLoader::free() {
    if (mTexture != NULL) {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        rect.x = 0;
        rect.y = 0;
        rect.w = 0;
        rect.h = 0;
//        angle = 0;
    }
}

void ImageLoader::render(SDL_Renderer* renderer, SDL_Rect* clip) {
    
    SDL_Rect renderQuad = {rect.x, rect.y, rect.w, rect.h};

    SDL_RenderCopy(renderer, mTexture, clip, &renderQuad);
}


void ImageLoader::renderEx(SDL_Renderer* renderer, SDL_Rect* clip , SDL_RendererFlip flip)
{
    SDL_Rect renderQuad = {rect.x, rect.y, rect.w, rect.h};

    //Render to screen with angle
    SDL_RenderCopyEx( renderer, mTexture, clip, &renderQuad, angle, NULL, flip );
}
