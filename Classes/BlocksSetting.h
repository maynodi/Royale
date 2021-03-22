//
//  BlocksSetting.h
//  myTetris
//
//  Created by CD-hj0949 on 2021/03/22.
//

#pragma once

namespace location //기본위치
{
    int location_J[2][BLOCKCNT] =
    {
        {0, 0, 0, -1}, // x
        {1, 0, -1, -1} // y
    };
}

namespace posVariance  // 회전할 때 위치 변화량
{
    // Block_J
    int posVariance_J[4][8] =
    {
        {-1, -1, 0, 0, 1, 1, 2, 0},
        {1, -1, 0, 0, -1, 1, 0, 2},
        {1, 1, 0, 0, -1, -1, -2, 0},
        {-1, 1, 0, 0, 1, -1, 0, -2}
    };
}
