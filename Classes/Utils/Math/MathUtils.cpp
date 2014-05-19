//
//  MathUtils.cpp
//  Bomber
//
//  Created by Jeremias Nunez on 3/20/14.
//
//

#include "MathUtils.h"
#include "cocos2d.h"

USING_NS_CC;

int MathUtils::randIntInRange(int min, int max)
{
    return min + (arc4random() % (int)(max - min + 1));
}

float MathUtils::angleFromVector(cocos2d::Point p0, cocos2d::Point p1)
{
    cocos2d::Point direction = p1 - p0;
    float rad = CC_RADIANS_TO_DEGREES(-direction.getAngle());
    
    return fmod(rad, 360.0f); // keep angle in the 360 range
}