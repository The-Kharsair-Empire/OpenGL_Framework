
#pragma once

#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>
#include <SDL2/SDL.h>

class Display
{
public:
    Display(int width, int height, const std::string& title);
    virtual ~Display();

    void Update();
    bool IsClosed();
    void Clear(float r, float g, float b, float a);

private:
    Display(const Display& other) = delete;//{};

    Display& operator=(const Display& other) = delete;// { return *this; };

    SDL_Window* m_ptr_window;
    SDL_GLContext m_glContext;

    bool m_isClosed;
    
};

#endif