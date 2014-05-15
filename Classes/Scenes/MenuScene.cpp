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
    
    MenuItemFont::setFontName("Marker Felt.ttf");
    MenuItemFont::setFontSize(80);
    
    MenuItemFont *playItem = MenuItemFont::create("Play", CC_CALLBACK_1(MenuLayer::menuCallbackPlay, this));
    MenuItemFont *configItem = MenuItemFont::create("Config", CC_CALLBACK_1(MenuLayer::menuCallbackConfig, this));
    
    Menu *mainMenu = Menu::create(playItem, configItem, NULL);
    mainMenu->alignItemsVerticallyWithPadding(25);
    
    Point newPosition = Point(mainMenu->getPosition().x, mainMenu->getPosition().y - 50);
    mainMenu->setPosition(newPosition);
    
    this->addChild(mainMenu);
    
    return true;
}

#pragma mark - Menu callbacks
void MenuLayer::menuCallbackPlay(Ref *sender)
{
    auto gameScene = GameLayer::createScene();
    Director::getInstance()->replaceScene(TransitionZoomFlipAngular::create(2, gameScene));
}

void MenuLayer::menuCallbackConfig(Ref *sender)
{
    MessageBox("Config will be here", "Hey");
}
