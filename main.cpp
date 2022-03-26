// #include <GL/glew.h>
#include <iostream>
#include <GL/glew.h>
#include "display.h"
#include "shader.h"

int main()
{
    // std::cout << "hi" << std::endl;
    Display display(800, 600, "Hi World");

    Shader shader("./res/basicShader");

    while(!display.IsClosed())
    {
        
        display.Clear(0.2f, 0.15f, 0.3f, 1.0f);
        shader.Bind();
        display.Update();
    }
    return 0;
}