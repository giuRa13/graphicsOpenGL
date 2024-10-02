#pragma once

#include "../include/glad/glad.h"
#include "Buffer.hpp"

class Quad
{

public:
    Quad();
    ~Quad();

    void Render();


private:
    Buffer m_buffer;

};
