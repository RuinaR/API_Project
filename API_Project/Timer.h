#pragma once
#include <Windows.h>

class Timer 
{
public:
    Timer()
    {
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&lastTime);
    }

    void tick() 
    {
        LARGE_INTEGER currentTime;
        QueryPerformanceCounter(&currentTime);
        LONGLONG elapsedTime = currentTime.QuadPart - lastTime.QuadPart;
        deltaTime = double(elapsedTime) / frequency.QuadPart;
        lastTime = currentTime;
        totalElapsedTime += deltaTime;
    }

    double getDeltaTime() const 
    {
        return deltaTime;
    }

    bool hasSecondPassed() 
    {
        return totalElapsedTime >= 1.0;
    }

    void resetElapsedTime() 
    {
        totalElapsedTime = 0.0;
    }

private:
    LARGE_INTEGER frequency;
    LARGE_INTEGER lastTime;
    double deltaTime = 0.0;
    double totalElapsedTime = 0.0;
};