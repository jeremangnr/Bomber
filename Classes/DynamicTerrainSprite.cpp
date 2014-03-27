//
//  DynamicTerrainTexture.cpp
//  Bomber
//
//  Created by Jeremias Nunez on 3/20/14.
//
//

#include "DynamicTerrainSprite.h"

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
    
    if (gradient == true) {
        float gradientAlpha = 0.7;
        Vertex2F vertices[4];
        Color4F colors[4];
        int nVertices = 0;
        
        vertices[nVertices] = Vertex2F(0, 0);
        colors[nVertices++] = Color4F(0, 0, 0, 0 );
        vertices[nVertices] = Vertex2F(size.width, 0);
        colors[nVertices++] = Color4F(0, 0, 0, 0);
        vertices[nVertices] = Vertex2F(0, size.height);
        colors[nVertices++] = Color4F(0, 0, 0, gradientAlpha);
        vertices[nVertices] = Vertex2F(size.width, size.height);
        colors[nVertices++] = Color4F(0, 0, 0, gradientAlpha);
        
        this->setShaderProgram(ShaderCache::getInstance()->getProgram(GLProgram::SHADER_NAME_POSITION_COLOR));
        CC_NODE_DRAW_SETUP();
        
        GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_COLOR);
        
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, vertices);
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_FLOAT, GL_FALSE, 0, colors);
        
        GL::blendFunc( _blendFunc.src, _blendFunc.dst );
        glDrawArrays(GL_TRIANGLE_STRIP, 0, nVertices);
    }
    
    // add noise
    Sprite *noise = Sprite::create("noise.png");
    noise->setBlendFunc({GL_DST_COLOR, GL_ZERO});
    noise->setPosition(Point(size.width / 2, size.height / 2));
    noise->visit();
    
    rt->end();
    
    //rt->autorelease();
    return rt;
}