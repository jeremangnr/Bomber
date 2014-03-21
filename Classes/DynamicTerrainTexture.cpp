//
//  DynamicTerrainTexture.cpp
//  Bomber
//
//  Created by Jeremias Nunez on 3/20/14.
//
//

#include "DynamicTerrainTexture.h"

USING_NS_CC;

DynamicTerrainTexture* DynamicTerrainTexture::create(Size size, Color4F color)
{
    DynamicTerrainTexture *sprite = new DynamicTerrainTexture();
    if (sprite && sprite->init()) {}
    
    RenderTexture *rt = RenderTexture::create(size.width, size.height);
    
    rt->beginWithClear(color.r, color.g, color.b, color.a);
    
    // draw here
    
    rt->end();
    
    //Sprite *sprite = Sprite::createWithTexture(rt->getSprite()->getTexture());
    
    return static_cast<DynamicTerrainTexture*>(sprite);
}