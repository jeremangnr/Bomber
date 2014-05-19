#include "GameScene.h"
#include "Tank.h"
#include "MathUtils.h"

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
    //setupTanks();
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_1(GameLayer::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
    
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    return true;
}

#pragma mark - Overrides
void GameLayer::onEnter()
{
    Layer::onEnter();
    Director::getInstance()->getScheduler()->scheduleUpdate(this, 1, false);
}

void GameLayer::onEnterTransitionDidFinish()
{
    Layer::onEnterTransitionDidFinish();
    setupTanks();
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
    
    while (timeAccumulator >= UPDATE_INTERVAL) {
        timeAccumulator -= UPDATE_INTERVAL;
        
        this->_physicsWorld->Step(UPDATE_INTERVAL, 3, 2); // interval, velocity iterations, position iterations
        this->_physicsWorld->ClearForces(); // i think this is not really necessary
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
bool GameLayer::onTouchBegan(Touch *touch)
{
    return true;
}

void GameLayer::onTouchMoved(Touch *touch, Event *event)
{
    float rotation = MathUtils::angleFromVector(this->_tank->getPosition(), touch->getLocation());
    
    this->_tank->rotateCannon(rotation);
}

#pragma mark - Private
void GameLayer::setupTerrain(b2World *world)
{
    Terrain *terrain = Terrain::create(world);
    terrain->setPosition(Point::ZERO);
    
    this->addChild(terrain, 0);
    
    this->_terrain = terrain;
}

void GameLayer::setupPhysics()
{
    b2Vec2 gravity = b2Vec2(0.0f, -9.0); // a little less than earth standard
    
    this->_physicsWorld = new b2World(gravity);
    this->_physicsWorld->SetAllowSleeping(true);
}

void GameLayer::setupTanks()
{
    Point tankOrigin = this->_terrain->getRandomTerrainPoint();
    
    // place offscreen first
    Tank *tank = Tank::create(Point(tankOrigin.x, VisibleRect::height()));
    this->addChild(tank);
    
    this->_tank = tank;
    // drop, bounce, and rotate to terrain angle
    auto drop = EaseIn::create(MoveTo::create(0.3f, tankOrigin), 1);
    auto bounce = EaseElasticOut::create(MoveBy::create(1.0f, Point(0, 10)));
    auto rotate = RotateTo::create(0.1f, this->_terrain->getRotationAngleForHillPoint(tankOrigin));
    
    this->_tank->runAction(Sequence::create(drop, rotate, bounce, NULL));
}