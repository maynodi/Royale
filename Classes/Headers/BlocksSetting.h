//
//  BlocksSetting.h
//  myTetris
//
//  Created by CD-hj0949 on 2021/03/22.
//

#pragma once

namespace initPos // 시작위치
{
    const int pos[2] = {HALF_WIDTH + 1 , MAP_HEIGHT - 2}; // x, y
    const int nextBlockPos[2] = {HALF_BLOCKLAYER_WIDTH - 1, BLOCKLAYER_HEIGHT - 1};
    const int holdBlockPos[2] = {HALF_BLOCKLAYER_WIDTH + 1, BLOCKLAYER_HEIGHT - 1};
}
namespace location // 기본위치
{
    // Block_J
    const int J[2][BLOCKCNT] =
    {
        {0, 0, 0, -1}, // x
        {1, 0, -1, -1} // y
    };
    
    // Block_I
    const int I[2][BLOCKCNT] =
    {
        {-1, 0, 1, 2},
        {0, 0, 0, 0}
    };

    // Block_S
    const int S[2][BLOCKCNT] =
    {
        {-1, 0, 0, 1},
        {0, 0, 1, 1}
    };

    // Block_T
    const int T[2][BLOCKCNT] =
    {
        {-1, 0, 0, 1},
        {0, 0, -1, 0}
    };

    // Block_O
    const int O[2][BLOCKCNT] =
    {
        {-1, 0, 0, -1},
        {0, 0, 1, 1}
    };
}

namespace posVariance  // 회전할 때 위치 변화량
{
    // Block_J
    const int J[4][8] =
    {
        {-1, -1, 0, 0, 1, 1, 2, 0},
        {1, -1, 0, 0, -1, 1, 0, 2},
        {1, 1, 0, 0, -1, -1, -2, 0},
        {-1, 1, 0, 0, 1, -1, 0, -2}
    };
    
    // Block_I
    const int I[4][8] =
    {
        {1, -1, 0, 0, -1, 1, -2, 2},
        {1, 1, 0, 0, -1, -1, -2, -2},
        {-1, 1, 0, 0, 1, -1, 2, -2},
        {-1, -1, 0, 0, 1, 1, 2, 2}
    };

    // Block_S
    const int S[4][8] =
    {
        {1, -1, 0, 0, -1, -1, -2, 0},
        {1, 1, 0, 0, 1, -1, 0, -2},
        {-1, 1, 0, 0, 1, 1, 2, 0},
        {-1, -1, 0, 0, -1, 1, 0, 2}
    };
    // Block_T
    const int T[4][8] =
    {
        {1, -1, 0, 0, 1, 1, -1, 1},
        {1, 1, 0, 0, -1, 1, -1, -1},
        {-1, 1, 0, 0, -1, -1, 1, -1},
        {-1, -1, 0, 0, 1, -1, 1, 1}
    };

    // Block_O
    const int O[4][8] =
    {
        {1, -1, 0, 0, -1, -1, 0, -2},
        {1, 1, 0, 0, 1, -1, 2, 0},
        {-1, 1, 0, 0, 1, 1, 0, 2},
        {-1, -1, 0, 0, -1, 1, -2, 0}
    };
}
