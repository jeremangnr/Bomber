//
//  MenuScene.cpp
//  Bomber
//
//  Created by Jeremias Nuñez on 5/9/14.
//
//

#include "MenuScene.h"
#include "GameScene.h"

USING_NS_CC;
using namespace Bomber;

#pragma mark - Init/Lifecycle
Scene* MenuLayer::createScene()
{
    auto scene = Scene::create();
    auto layer = MenuLayer::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool MenuLayer::init()
{
    if (!Layer::init()) return false;
    
    Label *title = Label::createWithTTF("Bomber", "Marker Felt.ttf", 180);
    title->setPosition(VisibleRect::width() / 2, VisibleRect::height() - 120);
    
    this->addChild(title);
    
    MenuItemFont *playItem = MenuItemFont::create("Play", CC_CALLBACK_1(MenuLayer::menuCallbackPlay, this));
    playItem->setFontName("Marker Felt.ttf");
    playItem->setFontSize(30);
    
    Menu *mainMenu = Menu::create(playItem, NULL);
    
    this->addChild(mainMenu);
    
    return true;
}

#pragma mark - Menu callbacks
void MenuLayer::menuCallbackPlay(Ref *sender)
{
    auto gameScene = GameLayer::createScene();
    Director::getInstance()->replaceScene(TransitionZoomFlipAngular::create(2, gameScene));
}
