//
//  DynamicTerrainTexture.h
//  Bomber
//
//  Created by Jeremias Nunez on 3/20/14.
//
//

#ifndef __Bomber__DynamicTerrainTexture__
#define __Bomber__DynamicTerrainTexture__

#include "cocos2d.h"

class DynamicTerrainTexture : public cocos2d::Sprite
{
public:
    static DynamicTerrainTexture* create(cocos2d::Size size, cocos2d::Color4F color);
};

#endif /* defined(__Bomber__DynamicTerrainTexture__) */
