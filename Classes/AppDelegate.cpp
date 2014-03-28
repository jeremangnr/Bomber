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
        CCLOG("%s", "Device is iPhone 4 inch\n");
        
        searchPaths.push_back("iphone_4_retina");
        director->setContentScaleFactor(1136/640);
    } else if (screenSize.width == 960) {
        CCLOG("%s", "Device is iPhone 3.5 inch Retina\n");
        
        searchPaths.push_back("iphone_4_retina");
        director->setContentScaleFactor(640/640);
    }
    
    CCLOG("%s %.2f x %.2f", "Screen size is", screenSize.width, screenSize.height);
    CCLOG("%s %.2f x %.2f", "Design resolution size is", eglView->getDesignResolutionSize().width, eglView->getDesignResolutionSize().height);
    CCLOG("%s: %.2f", "Content scale factor is", director->getContentScaleFactor());
    
    CCLOG("%s", "Loading assets from: ");
    
    FileUtils::getInstance()->setSearchPaths(searchPaths);

    for (std::string p : searchPaths) {
        std::cout << "\t\t\t-> " + p << std::endl;
    }
    
    auto scene = HelloWorld::createScene();

    director->setAnimationInterval(1.0 / 60); // 60fps
    director->runWithScene(scene);

    return true;
}

void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
}

void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
}
