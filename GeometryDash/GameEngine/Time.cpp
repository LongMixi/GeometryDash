//
//  Time.cpp
//  GeometryDash
//
//  Created by Nguyễn Bảo Long on 17/3/24.
//
//This code is referenced from https://lazyfoo.net/tutorials/SDL/23_advanced_timers/index.php

#include "Time.hpp"

Timer::Timer() {
    startTime = 0;
    pausedTime = 0;
    paused = false;
    started = false;
}

Timer::~Timer(){;}

void Timer::start() {
    started = true;
    paused = false;
    startTime = SDL_GetTicks();
    pausedTime = 0;
}

void Timer::stop() {
    started = false;
    paused = false;
    startTime = 0;
    pausedTime = 0;
}

void Timer::pause() {
    if (started && !paused) {
        paused = true;
        pausedTime = SDL_GetTicks() - startTime;
    }
}

void Timer::unpause() {
    if (started && paused) {
        paused = false;
        startTime = SDL_GetTicks() - pausedTime;
        pausedTime = 0;
    }
}

Uint32 Timer::getTicks() {
    Uint32 time = 0;
    if (started) {
        if (paused) {
            time = pausedTime;
        } else {
            time = SDL_GetTicks() - startTime;
        }
    }
    return time;
}

bool Timer::isStarted() {
    return started;
}

bool Timer::isPaused() {
    return paused && started;
}
