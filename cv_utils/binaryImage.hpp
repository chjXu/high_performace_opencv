#pragma once
#include <iostream>
#include <stdlib.h>

void MyBinaryImage(const unsigned char* src, unsigned char*& dst, int width, int height, int threshold)
{
    if(src == nullptr) return;

    for(int i = 0; i < width * height; ++i)
    {
        if(src[i] < threshold)
        {
            dst[i] = 0;
        }
        else
        {
            dst[i] = 255;
        }
    }
}