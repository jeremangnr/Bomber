//
//  MathUtils.cpp
//  Bomber
//
//  Created by Jeremias Nunez on 3/20/14.
//
//

#include "MathUtils.h"
#include <random>

int MathUtils::randIntInRange(int min, int max)
{
    return min + (arc4random() % (int)(max - min + 1));
}