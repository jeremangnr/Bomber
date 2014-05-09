#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include <Box2D/Box2D.h>

#include "Bomber.h"

BOMBER_NS_START

class GameLayer : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    CREATE_FUNC(GameLayer);
    
    virtual void update(float dt);
    virtual bool onTouchBegan(cocos2d::Touch *touch);
    virtual void onEnter() override;
    virtual void onExit() override;
    
    void createTestBodyAtPosition(cocos2d::Point position);
    
private:
    b2World *_physicsWorld;
    
    virtual bool init();
    
    void setupTerrain(b2World *world);
    void setupPhysics();
};

BOMBER_NS_END

#endif // __GAME_SCENE_H__
