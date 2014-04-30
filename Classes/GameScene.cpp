#include "GameScene.h"
#include "Terrain.h"

USING_NS_CC;
using namespace Bomber;

Scene* GameLayer::createScene()
{
    auto scene = Scene::create();
    auto layer = GameLayer::create();

    scene->addChild(layer);

    return scene;
}

bool GameLayer::init()
{
    if (!Layer::init()) return false;

    Terrain *terrain = new Terrain();
    terrain->setPosition(Point::ZERO);
    
    this->addChild(terrain, 0);
    
    return true;
}
