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

class DynamicTerrainSprite : public cocos2d::Sprite
{
public:
    static DynamicTerrainSprite* createWithSizeColor(const cocos2d::Size &size, const cocos2d::Color4F &color);
private:
    bool initWithSizeColor(const cocos2d::Size &size, const cocos2d::Color4F &color);
    cocos2d::RenderTexture* noiseTextureWithSizeColor(const cocos2d::Size &size, const cocos2d::Color4F &color, bool gradient);
};

#endif /* defined(__Bomber__DynamicTerrainTexture__) */