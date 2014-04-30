//
//  Terrain.cpp
//  Bomber
//
//  Created by Jeremias Nunez on 3/18/14.
//
//

#include "Terrain.h"

USING_NS_CC;
using namespace std;
using namespace Bomber;

#define MAX_HILL_HORIZONTAL_DISTANCE 200
#define MIN_HILL_HORIZONTAL_DISTANCE 40
#define MIN_HILL_VERTICAL_DISTANCE 80
#define HILL_TOP_OFFSET 200
#define HILL_SEGMENT_WIDTH 5

#pragma mark - Lifecycle
Terrain::Terrain()
{
    generateHills();
    addBackground();
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_1(Terrain::onTouchBegan, this);
    
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

Terrain::~Terrain()
{
}

#pragma mark - Overrides
void Terrain::draw()
{
    _customCommand.init(_globalZOrder);
    _customCommand.func = CC_CALLBACK_0(Terrain::onDraw, this);
    Director::getInstance()->getRenderer()->addCommand(&_customCommand);
}

void Terrain::onDraw()
{
    Point p0 = this->_hillKeyPoints.front();
    
    // draw hill segments
    for (Point p1 : this->_hillKeyPoints) {
//        glLineWidth(1);
//        DrawPrimitives::setDrawColor4B(255, 255, 255, 255);
//        DrawPrimitives::drawLine(p0, p1);
        
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
            
            glLineWidth(3);
            
            DrawPrimitives::setDrawColor4B(255, 0, 0, 255);
            DrawPrimitives::drawLine(pt0, pt1);
            
            pt0 = pt1;
        }
        
        p0 = p1;
    }
    
    // add dark gradient for bg texture
    this->setShaderProgram(ShaderCache::getInstance()->getProgram(GLProgram::SHADER_NAME_POSITION_COLOR));
    
    CC_NODE_DRAW_SETUP();
    
    float gradientAlpha = 0.7f;
    Point vertices[4];
    Color4F colors[4];
    int nVertices = 0;
    
    vertices[nVertices] = Point(0, 0);
    colors[nVertices++] = Color4F(0, 0, 0, 0 );
    vertices[nVertices] = Point(VisibleRect::width(), 0);
    colors[nVertices++] = Color4F(0, 0, 0, 0);
    vertices[nVertices] = Point(0, VisibleRect::height());
    colors[nVertices++] = Color4F(0, 0, 0, gradientAlpha);
    vertices[nVertices] = Point(VisibleRect::width(), VisibleRect::height());
    colors[nVertices++] = Color4F(0, 0, 0, gradientAlpha);
    
    GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION  | GL::VERTEX_ATTRIB_FLAG_COLOR);
    
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_FLOAT, GL_FALSE, 0, colors);
    glBlendFunc(CC_BLEND_SRC, CC_BLEND_DST);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei)nVertices);
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

void Terrain::addBackground()
{
    DynamicTerrainSprite *terrainBg = DynamicTerrainSprite::createWithSizeColor(Size(VisibleRect::width(), VisibleRect::height()), ColorUtils::randomBrightColor());
    terrainBg->setPosition(VisibleRect::center());
    
    // set z = -1 so it goes behind the terrain lines
    this->addChild(terrainBg, -1);
    this->_bgTexture = terrainBg;
}