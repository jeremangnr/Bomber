//
//  Tank.cpp
//  Bomber
//
//  Created by Jeremias Nuñez on 5/15/14.
//
//

#include "Tank.h"

USING_NS_CC;
using namespace Bomber;


#pragma mark - Lifecycle
Tank::Tank()
{
    this->_cannon = nullptr;
}

Tank::~Tank()
{
    if (this->_cannon != nullptr) CC_SAFE_RELEASE_NULL(this->_cannon);
}

Tank* Tank::create(Point origin)
{
    Tank *pRet = new Tank();
    if (pRet && pRet->init(origin)) {
        pRet->autorelease();
        return pRet;
    } else {
        CC_SAFE_DELETE(pRet);
        return nullptr;
    }
}

bool Tank::init(Point origin)
{
    if (!this->initWithFile("tank.png")) return false;
    
    this->setPosition(origin);
    
    Sprite *cannon = Sprite::create("cannon.png");
    cannon->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2 + cannon->getContentSize().height / 2);
    
    this->addChild(cannon);
    
    return true;
}