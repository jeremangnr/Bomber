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

#define kMaxHillKeyPoints 20

class Terrain : public cocos2d::Node
{
public:
    Terrain();
    virtual ~Terrain();
    
    virtual void draw();
    
private:
    cocos2d::Point _hillKeyPoints[kMaxHillKeyPoints];
    
    void generateHills();
};

#endif /* defined(__Bomber__Terrain__) */
