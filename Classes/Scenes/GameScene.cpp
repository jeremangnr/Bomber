#include "GameScene.h"
#include "Terrain.h"

USING_NS_CC;
using namespace Bomber;

#pragma mark - Init/Lifecycle
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

    setupPhysics();
    setupTerrain(this->_physicsWorld);
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_1(GameLayer::onTouchBegan, this);
    
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    return true;
}

#pragma mark - Overrides
void GameLayer::onEnter()
{
    Layer::onEnter();
    Director::getInstance()->getScheduler()->scheduleUpdate(this, 1, false);
}

void GameLayer::onExit()
{
    Layer::onExit();
    Director::getInstance()->getScheduler()->unscheduleUpdate(this);
}

void GameLayer::update(float dt)
{
    static double UPDATE_INTERVAL = 1.0f/60.0f;
    static double MAX_CYCLES_PER_FRAME = 5;
    static double timeAccumulator = 0;
    
    timeAccumulator += dt;
    
    if (timeAccumulator > (MAX_CYCLES_PER_FRAME * UPDATE_INTERVAL)) {
        timeAccumulator = UPDATE_INTERVAL;
    }
    
    int32 velocityIterations = 3;
    int32 positionIterations = 2;
    
    while (timeAccumulator >= UPDATE_INTERVAL) {
        timeAccumulator -= UPDATE_INTERVAL;
        
        this->_physicsWorld->Step(UPDATE_INTERVAL, velocityIterations, positionIterations);
        this->_physicsWorld->ClearForces();
    }
}

#pragma mark - Physics stuff
void GameLayer::createTestBodyAtPosition(Point position)
{
    b2BodyDef testBodyDef;
    testBodyDef.type = b2_dynamicBody;
    testBodyDef.position.Set(position.x/PTM_RATIO, position.y/PTM_RATIO);
    
    b2CircleShape testBodyShape;
    testBodyShape.m_radius = 25.0/PTM_RATIO;
    
    b2FixtureDef testFixtureDef;
    testFixtureDef.shape = &testBodyShape;
    testFixtureDef.density = 1.0;
    testFixtureDef.friction = 0.2;
    testFixtureDef.restitution = 0.5;
    
    b2Body *testBody = this->_physicsWorld->CreateBody(&testBodyDef);
    testBody->CreateFixture(&testFixtureDef);
}

#pragma mark - Touch handling
bool GameLayer::onTouchBegan(cocos2d::Touch *touch)
{
    Point touchPoint = this->convertTouchToNodeSpace(touch);
    createTestBodyAtPosition(touchPoint);
    
    return true;
}

#pragma mark - Private
void GameLayer::setupTerrain(b2World *world)
{
    Terrain *terrain = Terrain::create(world);
    terrain->setPosition(Point::ZERO);
    
    this->addChild(terrain, 0);
}

void GameLayer::setupPhysics()
{
    b2Vec2 gravity = b2Vec2(0.0f, -9.0); // a little less than earth standard
    
    this->_physicsWorld = new b2World(gravity);
    this->_physicsWorld->SetAllowSleeping(true);
}