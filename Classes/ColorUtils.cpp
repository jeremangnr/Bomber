//
//  ColorUtils.cpp
//  Bomber
//
//  Created by Jeremias Nuñez on 3/26/14.
//
//

#include "ColorUtils.h"

#define kRequiredBrightness 192

USING_NS_CC;

cocos2d::Color4F ColorUtils::randomBrightColor()
{
    while (true) {
        Color4B color = Color4B::Color4B(arc4random() % 255, arc4random() % 255, arc4random() % 255, 255);
        
        if (color.r > kRequiredBrightness || color.g > kRequiredBrightness || color.b > kRequiredBrightness) {
            return Color4F::Color4F(color);
        }
    }
}