#include "HelloWorldScene.h"
#include "Terrain.h"

#include "DynamicTerrainSprite.h"
#include "VisibleRect.h"
#include "ColorUtils.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();

    scene->addChild(layer);

    return scene;
}

bool HelloWorld::init()
{
    if (!Layer::init()) return false;

    auto terrain = new Terrain();
    terrain->setPosition(Point::ZERO);
    
    auto bg = DynamicTerrainSprite::createWithSizeColor(Size(VisibleRect::width(), VisibleRect::height()), ColorUtils::randomBrightColor());
    bg->setPosition(VisibleRect::center());
    
    this->addChild(bg, 0);
    this->addChild(terrain, 1);
    
    return true;
}
