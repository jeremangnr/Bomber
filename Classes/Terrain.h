//
//  Terrain.h
//  Bomber
//
//  Created by Jeremias Nunez on 3/18/14.
//
//

#ifndef __Bomber__Terrain__
#define __Bomber__Terrain__

#include "cocos2d.h"
#include "Bomber.h"

#include "DynamicTerrainSprite.h"

BOMBER_NS_START

class Terrain : public cocos2d::Node
{
public:
    Terrain();
    virtual ~Terrain();
    
    virtual void draw() override;
    virtual void onDraw();
    
    virtual bool onTouchBegan(cocos2d::Touch *touch);
private:
    std::vector<cocos2d::Point> _hillKeyPoints;
    cocos2d::CustomCommand _customCommand;
    
    Bomber::DynamicTerrainSprite *_bgTexture;
    
    void generateHills();
    void addBackground();
};

BOMBER_NS_END

#endif /* defined(__Bomber__Terrain__) */
