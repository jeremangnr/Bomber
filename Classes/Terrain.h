//
//  Terrain.h
//  Bomber
//
//  Created by Jeremias Nunez on 3/18/14.
//
//

#ifndef __Bomber__Terrain__
#define __Bomber__Terrain__

#define MAX_HILL_VERTICES 4000

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
    std::vector<cocos2d::Point> _hillKeyPoints; // for creating the hills
    std::vector<std::tuple<cocos2d::Point, cocos2d::Point>> _hillSegments; // for drawing the hill as a curved line
    
    // for drawing the texture "under" the hill's shape
    cocos2d::Point _hillVertices[MAX_HILL_VERTICES];
    cocos2d::Point _hillTexCoords[MAX_HILL_VERTICES];
    int _nHillVertices;
    
    cocos2d::CustomCommand _customCommand;
    
    Bomber::DynamicTerrainSprite *_terrainTexture;
    
    void generateHills();
    void generateBackground();
};

BOMBER_NS_END

#endif /* defined(__Bomber__Terrain__) */
