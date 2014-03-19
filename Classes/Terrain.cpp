//
//  Terrain.cpp
//  Bomber
//
//  Created by Jeremias Nunez on 3/18/14.
//
//

#include "Terrain.h"

USING_NS_CC;

#pragma mark - Lifecycle
Terrain::Terrain()
{
    generateHills();
}

Terrain::~Terrain()
{
}

#pragma mark - Override
void Terrain::draw()
{
    for (int i = 1; i < kMaxHillKeyPoints; ++i) {
        DrawPrimitives::drawLine(this->_hillKeyPoints[i-1], this->_hillKeyPoints[i]);
    }
}

#pragma mark - Private
void Terrain::generateHills()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    float x = 0;
    float y = visibleSize.height / 2;
    
    for (int i = 0; i < kMaxHillKeyPoints; ++i) {
        this->_hillKeyPoints[i] = Point(x, y);
        
        x += (random() % (int)visibleSize.width);
        y = (random() % (int)visibleSize.height);
    }
}