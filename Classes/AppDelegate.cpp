#include "AppDelegate.h"
#include "HelloWorldScene.h"

USING_NS_CC;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    auto director = Director::getInstance();
    auto eglView = EGLView::getInstance();

    director->setOpenGLView(eglView);
    
    eglView->setDesignResolutionSize(1136, 640, ResolutionPolicy::FIXED_WIDTH);
    
    Size screenSize = eglView->getFrameSize();
    std::vector<std::string> searchPaths;
    
    if (screenSize.width == 1136) {
        CCLOG("%s", "device is iPhone 5");
        
        searchPaths.push_back("iphone5");
        director->setContentScaleFactor(1136/640);
    } else if (screenSize.width == 960) {
        CCLOG("%s", "device is iPhone Retina");
        
        searchPaths.push_back("retina");
        director->setContentScaleFactor(640/640);
    } else if (screenSize.width == 320) {
        CCLOG("%s", "device is iPhone (non-retina)");
        
        searchPaths.push_back("regular");
        director->setContentScaleFactor(320/640);
    }
    
    FileUtils::getInstance()->setSearchPaths(searchPaths);
    
    director->setAnimationInterval(1.0 / 60); // 60fps

    auto scene = HelloWorld::createScene();

    director->runWithScene(scene);

    return true;
}

void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
}

void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
}
