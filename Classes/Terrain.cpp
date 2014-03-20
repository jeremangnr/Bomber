//
//  Terrain.cpp
//  Bomber
//
//  Created by Jeremias Nunez on 3/18/14.
//
//

#include "Terrain.h"
#include "MathUtils.h"

#define MAX_HILL_HORIZONTAL_DISTANCE 200
#define MIN_HILL_HORIZONTAL_DISTANCE 40
#define MIN_HILL_VERTICAL_DISTANCE 80
#define HILL_TOP_OFFSET 200

USING_NS_CC;
using namespace std;

#pragma mark - Lifecycle
Terrain::Terrain()
{
    generateHills();
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_1(Terrain::onTouchBegan, this);
    
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

Terrain::~Terrain()
{
}

#pragma mark - Node Override
void Terrain::draw()
{
    vector<Point> points = this->_hillKeyPoints;
    Point prev = this->_hillKeyPoints.front();
    
    for (auto it = points.begin(); it != points.end(); ++it) {
        DrawPrimitives::drawLine(prev, *it);
        prev = *it;
    }
}

#pragma mark - Touch handling
bool Terrain::onTouchBegan(Touch *touch)
{
    this->_hillKeyPoints.clear();
    generateHills();
    
    return true;
}

#pragma mark - Private
void Terrain::generateHills()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    float currentX = 0;
    float currentY = MathUtils::randIntInRange(MIN_HILL_VERTICAL_DISTANCE, visibleSize.height - HILL_TOP_OFFSET);
    
    bool outOfScreen = false;
    
    while (!outOfScreen) {
        Point hillPoint = Point(currentX, currentY);
        this->_hillKeyPoints.push_back(hillPoint);
        
        currentX += MathUtils::randIntInRange(MIN_HILL_HORIZONTAL_DISTANCE, MAX_HILL_HORIZONTAL_DISTANCE);
        currentY = MathUtils::randIntInRange(MIN_HILL_VERTICAL_DISTANCE, visibleSize.height - HILL_TOP_OFFSET);
        
        if (currentX > visibleSize.width) {
            outOfScreen = true;
            
            Point finalPoint = Point(visibleSize.width, currentY);
            this->_hillKeyPoints.push_back(finalPoint);
        }
    }
}