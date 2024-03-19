//
//  Time.hpp
//  GeometryDash
//
//  Created by Nguyễn Bảo Long on 17/3/24.
//

#ifndef Time_hpp
#define Time_hpp

#include "BaseFunc.hpp"

class Timer {

public:
    Timer();
    ~Timer();
    void start();
    void stop();
    void pause();
    void unpause();
    Uint32 getTicks();
    bool isStarted();
    bool isPaused();
    
private:
    Uint32 startTime;
    Uint32 pausedTime;
    bool paused;
    bool started;
};

#endif /* Time_hpp */
