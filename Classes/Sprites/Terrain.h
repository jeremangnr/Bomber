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
#define MAX_BORDER_VERTICES 800

#include "cocos2d.h"
#include <Box2D/Box2D.h>
#include "Bomber.h"
#include "GLES-Render.h"

BOMBER_NS_START

class Terrain : public cocos2d::Node
{
public:
    virtual ~Terrain();
    virtual void draw(cocos2d::Renderer *renderer, const kmMat4 &transform, bool transformUpdated) override;
    
    static Terrain* create(b2World *physicsWorld);
    
protected:
    void onDraw(const kmMat4 &transform, bool transformUpdated);
    
private:
    Terrain();
    
    virtual bool init(b2World *physicsWorld);
    
    void setupDebugDrawing();
    void generatePhysicsBody();
    void generateHills();
    void generateBackgroundTexture();
    
    std::vector<cocos2d::Point> _hillKeyPoints; // for creating the hills
    std::vector<std::tuple<cocos2d::Point, cocos2d::Point>> _hillSegments; // for drawing the hill as a curved line
    cocos2d::Point _hillVertices[MAX_HILL_VERTICES]; // for drawing the texture "under" the hill's shape
    cocos2d::Point _hillTexCoords[MAX_HILL_VERTICES];
    cocos2d::Point _borderVertices[MAX_BORDER_VERTICES]; // for drawing the physics body
    int _nHillVertices;
    int _nBorderVertices;
    
    cocos2d::CustomCommand _customCommand;
    cocos2d::RenderTexture *_terrainTexture;
    
    b2World *_physicsWorld;
    b2Body *_physicsBody;
    GLESDebugDraw *_debugDraw;
};

BOMBER_NS_END

#endif /* defined(__Bomber__Terrain__) */
