#pragma once
#include <iostream>
#include <stdlib.h>
#include <queue>

using namespace std;

int dir[8][2] = {0, 1, 1, 0, -1, 0, 0, -1, -1, -1, 1, 1, 1, -1, -1, -1}; // 方向
int bfs(const unsigned char* src, unsigned char*& mask, int row, int col, int width, int height)
{
    queue<pair<int, int>> que;
    que.push({row, col});
    mask[row * width + col] = 255; // 只要加入队列，立刻标记
    int area = 0;
    while(!que.empty()) {
        pair<int ,int> cur = que.front(); 
        que.pop();
        ++area;
        int curx = cur.first;
        int cury = cur.second;
        for (int i = 0; i < 4; i++) {
            int nextx = curx + dir[i][0];
            int nexty = cury + dir[i][1];
            if (nextx < 0 || nextx >= width || nexty < 0 || nexty >= height) continue;  // 越界了，直接跳过
            if (mask[nextx * width + nexty] != 255 && src[nextx * width + nexty] == 255) {
                que.push({nextx, nexty});
                mask[nextx * width + nexty] = 255; // 只要加入队列立刻标记
            }
        }
    }
    return area;
}

void MyconnectedComponents(const unsigned char* src, unsigned char*& mask, int width, int height)
{
    if(src == nullptr || mask == nullptr || width <= 0) return;

    int num = 0;
    int maxArea = 0;
    for(int row = 0; row < height; ++row)
    {
        for(int col = 0; col < width; ++col)
        {
            if(src[row * width + col] == 255 && mask[row * width + col] == 0)
            {
                num++;
                int area = bfs(src, mask, row, col, width, height);
                maxArea = std::max(maxArea, area);
            }
        }
    }

    std::cout << num << std::endl;
    std::cout << maxArea << std::endl;
}