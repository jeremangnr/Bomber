//
//  DynamicTerrainTexture.cpp
//  Bomber
//
//  Created by Jeremias Nunez on 3/20/14.
//
//

#include "DynamicTerrainSprite.h"

#define kGradientColorStart Color4B(0, 0, 0, 0)
#define kGradientColorEnd Color4B(0, 0, 0, 170)

USING_NS_CC;

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
    RenderTexture *noiseTexture = this->noiseTextureWithSizeColor(size, color, true);
    
    if (!Sprite::initWithTexture(noiseTexture->getSprite()->getTexture())) return false;
    
    return true;
}

RenderTexture* DynamicTerrainSprite::noiseTextureWithSizeColor(const cocos2d::Size &size, const cocos2d::Color4F &color, bool gradient)
{
    RenderTexture *rt = RenderTexture::create(size.width, size.height);
    
    rt->beginWithClear(color.r, color.g, color.b, color.a);
    
    // add noise
    Sprite *noise = Sprite::create("noise.png");
    noise->setBlendFunc({GL_DST_COLOR, GL_ZERO});
    noise->setPosition(Point(size.width / 2, size.height / 2));
    noise->visit();
    
    rt->end();
    
    if (gradient == true) {
        LayerGradient *gradient = LayerGradient::create(kGradientColorStart, kGradientColorEnd);
        this->addChild(gradient);
        //gradient->setBlendFunc({GL_SRC_COLOR, GL_DST_COLOR}); // set this for colored gradient
    }
    
    return rt;
}