//
//  MenuScene.h
//  Bomber
//
//  Created by Jeremias Nuñez on 5/9/14.
//
//

#ifndef __Bomber__MenuScene__
#define __Bomber__MenuScene__

#include "cocos2d.h"
#include "Bomber.h"

BOMBER_NS_START

class MenuLayer : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    CREATE_FUNC(MenuLayer);
    
    void menuCallbackPlay(Ref *sender);
private:
    virtual bool init();
};

BOMBER_NS_END

#endif /* defined(__Bomber__MenuScene__) */
