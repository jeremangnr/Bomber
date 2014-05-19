//
//  MathUtils.h
//  Bomber
//
//  Created by Jeremias Nunez on 3/20/14.
//
//

#ifndef __Bomber__MathUtils__
#define __Bomber__MathUtils__

#include "cocos2d.h"

class MathUtils {
    
public:
    static int randIntInRange(int min, int max);
    static float angleFromVector(cocos2d::Point p0, cocos2d::Point p1);
};

#endif /* defined(__Bomber__MathUtils__) */
