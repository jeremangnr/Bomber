//
//  Tank.h
//  Bomber
//
//  Created by Jeremias Nuñez on 5/15/14.
//
//

#ifndef __Bomber__Tank__
#define __Bomber__Tank__

#include "cocos2d.h"
#include <Box2D/Box2D.h>
#include "Bomber.h"

BOMBER_NS_START

class Tank : public cocos2d::Sprite
{
public:
    virtual ~Tank();
    
    static Tank* create(cocos2d::Point origin);
    
private:
    Tank();
    
    virtual bool init(cocos2d::Point origin);
    
    cocos2d::Sprite *_cannon;
};

BOMBER_NS_END

#endif /* defined(__Bomber__Tank__) */
