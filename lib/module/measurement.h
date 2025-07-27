#ifndef __MEASUREMENT_H__
#define __MEASUREMENT_H__

#include"Pin.h"


namespace Uls // _Ul_tra _s_ound
{
    void init();

    float getDistance(int delta_time=10);

}
#endif

