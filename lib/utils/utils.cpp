#include<cmath>

#include"utils.h"

float SoundSpeedInAir(float CelsiusTemp)
{
    return 331.3f * sqrtf( 1.0f + CelsiusTemp/273.15f);
}
