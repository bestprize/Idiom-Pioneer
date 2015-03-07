#include "LogoScene.h"
#include "IdiomPioneerScene.h"

USING_NS_CC;

Scene* Logo::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto logo = Logo::create();

    // add layer as a child to scene
    scene->addChild(logo,1,"logo");

	auto backGroundLayer = LayerColor::create(Color4B(255,255,255,255));
	scene->addChild(backGroundLayer,0,"backGroundLayer");

    UserDefault::sharedUserDefault()->setIntegerForKey("firstStartFlag",0);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Logo::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();


    // add "logo" splash screen"
    auto logo = Sprite::create("baibu_256.png");

    // position the sprite on the center of the screen
    logo->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));

    // add the sprite as a child to this layer

    this->addChild(logo, 0, "logo");

	this->scheduleOnce(schedule_selector(Logo::logoIntoIdiomPioneer), 1.0f);  


    return true;
}



void Logo::logoIntoIdiomPioneer(float dt)  
{
    this->unschedule(schedule_selector(Logo::logoIntoIdiomPioneer)); 

    auto *idiomPioneer = IdiomPioneer::createScene();
    float t = 2.0f;

	Director::sharedDirector()->replaceScene(TransitionPageTurn ::create(t , idiomPioneer,false));
	//Director::sharedDirector()->replaceScene(aeroStunt);
}

