//
//  Terrain.cpp
//  Bomber
//
//  Created by Jeremias Nunez on 3/18/14.
//
//

#include "Terrain.h"
#include "MathUtils.h"
#include "VisibleRect.h"

USING_NS_CC;
using namespace std;

#define MAX_HILL_HORIZONTAL_DISTANCE 200
#define MIN_HILL_HORIZONTAL_DISTANCE 40
#define MIN_HILL_VERTICAL_DISTANCE 80
#define HILL_TOP_OFFSET 200
#define HILL_SEGMENT_WIDTH 5

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
    Point p0 = this->_hillKeyPoints.front();
    
    for (Point p1 : this->_hillKeyPoints) {
        glLineWidth(1);
        DrawPrimitives::setDrawColor4B(255, 255, 255, 255);
        DrawPrimitives::drawLine(p0, p1);
        
        int hSegments = floorf((p1.x - p0.x) / HILL_SEGMENT_WIDTH);
        
        float dx = (p1.x - p0.x) / hSegments;
        float da = M_PI / hSegments;
        float yMid = (p0.y + p1.y) / 2;
        float ampl = (p0.y - p1.y) / 2;
        
        Point pt0, pt1;
        pt0 = p0;
        
        for (int i = 0; i < hSegments + 1; ++i) {
            pt1.x = p0.x + (i * dx);
            pt1.y = yMid + ampl * cosf(da * i);
            
            glLineWidth(4);
            DrawPrimitives::setDrawColor4B(255, 0, 0, 255);
            DrawPrimitives::drawLine(pt0, pt1);
            
            pt0 = pt1;
        }
        
        p0 = p1;
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
    float currentX = 0;
    float currentY = MathUtils::randIntInRange(MIN_HILL_VERTICAL_DISTANCE, VisibleRect::height() - HILL_TOP_OFFSET);
    
    bool outOfScreen = false;
    
    while (!outOfScreen) {
        Point hillPoint = Point(currentX, currentY);
        this->_hillKeyPoints.push_back(hillPoint);
        
        currentX += MathUtils::randIntInRange(MIN_HILL_HORIZONTAL_DISTANCE, MAX_HILL_HORIZONTAL_DISTANCE);
        currentY = MathUtils::randIntInRange(MIN_HILL_VERTICAL_DISTANCE, VisibleRect::height() - HILL_TOP_OFFSET);
        
        if (currentX > VisibleRect::width()) {
            outOfScreen = true;
            
            Point finalPoint = Point(VisibleRect::width(), currentY);
            this->_hillKeyPoints.push_back(finalPoint);
        }
    }
}