//
//  DynamicTerrainTexture.cpp
//  Bomber
//
//  Created by Jeremias Nunez on 3/20/14.
//
//

#include "DynamicTerrainSprite.h"

USING_NS_CC;
using namespace Bomber;

DynamicTerrainSprite* DynamicTerrainSprite::createWithSizeColor(const cocos2d::Size &size, const cocos2d::Color4F &color)
{
    DynamicTerrainSprite *sprite = new DynamicTerrainSprite();
    if (sprite && sprite->initWithSizeColor(size, color))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

bool DynamicTerrainSprite::initWithSizeColor(const Size &size, const Color4F &color)
{
    RenderTexture *noiseTexture = this->noiseTextureWithSizeColor(size, color);
    
    if (!Sprite::initWithTexture(noiseTexture->getSprite()->getTexture())) return false;
    
    return true;
}

RenderTexture* DynamicTerrainSprite::noiseTextureWithSizeColor(const cocos2d::Size &size, const cocos2d::Color4F &color)
{
    RenderTexture *rt = RenderTexture::create(size.width, size.height);
    
    rt->beginWithClear(color.r, color.g, color.b, color.a);
    
    // add noise
    Sprite *noise = Sprite::create("noise.png");
    noise->setBlendFunc({GL_DST_COLOR, GL_ZERO});
    noise->setPosition(Point(size.width / 2, size.height / 2));
    noise->visit();
    
    rt->end();
    
    return rt;
}