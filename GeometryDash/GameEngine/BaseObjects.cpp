#include "BaseObjects.hpp"
#include <iostream>

ImageLoader::ImageLoader() : mTexture(nullptr), mWidth(0), mHeight(0) {}

ImageLoader::~ImageLoader() {
    free();
}

bool ImageLoader::loadFromFile(std::string path, SDL_Renderer* renderer) {
    free();

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        std::cerr << "Unable to load image " << path << "! SDL_image Error: " << IMG_GetError() << std::endl;
        return false;
    }

    mTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if (mTexture == nullptr) {
        std::cerr << "Unable to create texture from " << path << "! SDL Error: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(loadedSurface);
        return false;
    }

    mWidth = loadedSurface->w;
    mHeight = loadedSurface->h;
    SDL_FreeSurface(loadedSurface);
    return true;
}

void ImageLoader::free() {
    if (mTexture != nullptr) {
        SDL_DestroyTexture(mTexture);
        mTexture = nullptr;
        mWidth = 0;
        mHeight = 0;
    }
}

void ImageLoader::render(int x, int y, SDL_Renderer* renderer, SDL_Rect* clip) {
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};

    if (clip != nullptr) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopy(renderer, mTexture, clip, &renderQuad);
}
