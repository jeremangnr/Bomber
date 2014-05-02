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
    generateBackground();
    
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
    // draw hill segments
    for(tuple<Point, Point> segment : this->_hillSegments) {
        glLineWidth(3);
        
        Point p0 = get<0>(segment);
        Point p1 = get<1>(segment);
        
        DrawPrimitives::setDrawColor4B(255, 0, 0, 255);
        DrawPrimitives::drawLine(p0, p1);
    }
    
    // draw texture inside terrain shape
    this->setShaderProgram(ShaderCache::getInstance()->getProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE));
    CC_NODE_DRAW_SETUP();
    
    CCLOG("binding texture: %u", this->_terrainTexture->getTexture()->getName());
    GL::bindTexture2D(this->_terrainTexture->getTexture()->getName());
    GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_TEX_COORDS);
    
    DrawPrimitives::setDrawColor4F(1.0f, 1.0f, 1.0f, 1.0f);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, this->_hillVertices);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORDS, 2, GL_FLOAT, GL_FALSE, 0, this->_hillTexCoords);
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei)this->_nHillVertices);
    
    // add dark gradient for bg texture
    this->setShaderProgram(ShaderCache::getInstance()->getProgram(GLProgram::SHADER_NAME_POSITION_COLOR));
    CC_NODE_DRAW_SETUP();
    
    float gradientAlpha = 0.7f;
    Point vertices[4];
    Color4F colors[4];
    int nVertices = 0;
    
    vertices[nVertices] = Point(VisibleRect::width(), VisibleRect::height());
    colors[nVertices++] = Color4F(0, 0, 0, 0 );
    
    vertices[nVertices] = Point(0, VisibleRect::height());
    colors[nVertices++] = Color4F(0, 0, 0, 0);
    
    vertices[nVertices] = Point(VisibleRect::width(), 0);
    colors[nVertices++] = Color4F(0, 0, 0, gradientAlpha);
    
    vertices[nVertices] = Point(0, 0);
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
    this->_hillSegments.clear();
    
    generateHills();
    generateBackground();
    
    this->visit();
    
    return true;
}

#pragma mark - Private
void Terrain::generateHills()
{
    float currentX = 0;
    float currentY = MathUtils::randIntInRange(MIN_HILL_VERTICAL_DISTANCE, VisibleRect::height() - HILL_TOP_OFFSET);
    
    bool outOfScreen = false;
    
    // generate key points first
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
    
    // generate points for the curved line
    Point p0 = this->_hillKeyPoints.front();
    
    for (Point p1 : this->_hillKeyPoints) {
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
            
            // store segments as tuple<Point, Point> so we can use them when drawing
            auto hillSegment = make_tuple(pt0, pt1);
            this->_hillSegments.push_back(hillSegment);
            
            pt0 = pt1;
        }
        
        p0 = p1;
    }
    
    // clean this up sometime
    float minY = 0;
    int hillPointsCount = this->_hillKeyPoints.size();
    this->_nHillVertices = 0;
    int nBorderVertices = 0;
    Point borderVertices[800];
    Point p1, pt0, pt1;
    
    p0 = this->_hillKeyPoints.front();
    
    for (int i = 0; i < hillPointsCount; i++) {
        p1 = this->_hillKeyPoints[i];
        
        // triangle strip between p0 and p1
        int hSegments = floorf((p1.x-p0.x) / HILL_SEGMENT_WIDTH);
        float dx = (p1.x - p0.x) / hSegments;
        float da = M_PI / hSegments;
        float ymid = (p0.y + p1.y) / 2;
        float ampl = (p0.y - p1.y) / 2;
        pt0 = p0;
        borderVertices[nBorderVertices++] = pt0;
        for (int j=1; j<hSegments+1; j++) {
            pt1.x = p0.x + j*dx;
            pt1.y = ymid + ampl * cosf(da*j);
            borderVertices[nBorderVertices++] = pt1;
            
            this->_hillVertices[this->_nHillVertices] = Point(pt0.x, 0 + minY);
            this->_hillTexCoords[this->_nHillVertices++] = Point(pt0.x/512, 1.0f);
            this->_hillVertices[this->_nHillVertices] = Point(pt1.x, 0 + minY);
            this->_hillTexCoords[this->_nHillVertices++] = Point(pt1.x/512, 1.0f);
            
            this->_hillVertices[this->_nHillVertices] = Point(pt0.x, pt0.y);
            this->_hillTexCoords[this->_nHillVertices++] = Point(pt0.x/512, 0);
            this->_hillVertices[this->_nHillVertices] = Point(pt1.x, pt1.y);
            this->_hillTexCoords[this->_nHillVertices++] = Point(pt1.x/512, 0);
            
            pt0 = pt1;
        }
        
        p0 = p1;
    }
}

void Terrain::generateBackground()
{
    if (this->_terrainTexture != nullptr) {
        CC_SAFE_RELEASE_NULL(this->_terrainTexture);
    }
    
    DynamicTerrainSprite *terrainBg = DynamicTerrainSprite::createWithSizeColor(Size(VisibleRect::width(), VisibleRect::height()), ColorUtils::randomBrightColor());
    terrainBg->retain();
    
    this->_terrainTexture = terrainBg;
}