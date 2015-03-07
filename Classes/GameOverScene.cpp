#include "GameOverScene.h"
#include "IdiomPioneerScene.h"
#include "AdsmogoBanner.h"
#include "AdsMogoInterstitial.h"
#include "SetupScene.h"


USING_NS_CC;

Scene* GameOver::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    auto backGroundLayer = LayerColor::create(Color4B(13,64,83,255));
    scene->addChild(backGroundLayer,0,"backGroundLayer");
    
    // 'layer' is an autorelease object
    auto layer = GameOver::create();

    // add layer as a child to scene
    scene->addChild(layer,10,"layer");
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    auto sprite = Sprite::create("back.png");
    sprite->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    
    float x = visibleSize.width/(sprite->getContentSize().width);
    float y = visibleSize.height/(sprite->getContentSize().height);
    auto scaleTo = ScaleTo::create(0.0f, x>=y?x:y);
    sprite->runAction(scaleTo);
    scene->addChild(sprite, 1);
    

    
    UserDefault::sharedUserDefault()->setIntegerForKey("sceneFlag",1);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameOver::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    srand(int(time(0))+ rand());
    auto randShowAd = rand()%3;
    if(randShowAd == 0){
        char mogoid []="4240cd75bd72463ba623ce172c9ce7f9";
        AdsMogoInterstitial::sharedInterstitial()->loadInterstitial(mogoid,AdsMogoInterstitialTypeFullScreen,true);
        AdsMogoInterstitial::sharedInterstitial()->showInterstitial();
    }
    AdsmogoBanner::sharedBanner()->hidenBanner();

    
    Size visibleSize = Director::getInstance()->getVisibleSize();

	string fullPlistPath = FileUtils::sharedFileUtils()->fullPathForFilename("my.plist");
	FileUtils *fu = FileUtils::getInstance();
	ValueMap vm = fu->getValueMapFromFile(fullPlistPath.c_str());
    auto wealth = UserDefault::sharedUserDefault()->getIntegerForKey("wealth",10000);

    
    auto setupItem = MenuItemImage::create(
                                           "setup_48.png",
                                           "setup_96.png",
                                           CC_CALLBACK_1(GameOver::setup, this));
    
    setupItem->setAnchorPoint(Vec2(0,0));
    setupItem->setPosition(Vec2(visibleSize.width-80, visibleSize.height-72));
    auto setupMenu = Menu::create(setupItem, NULL);
    setupMenu->setPosition(Vec2::ZERO);
    this->addChild(setupMenu, 1);
    
	auto labelRight = LabelTTF::create(vm["Right"].asString().c_str(), "Georgia", 48);
    labelRight->setPosition(visibleSize.width/2, visibleSize.height*3/4);
    this->addChild(labelRight, 1);

	auto labelRightAnswerStr = LabelTTF::create(rightAnswerStr, "Georgia", 72,Size(visibleSize.width,200),TextHAlignment::CENTER,TextVAlignment::CENTER);
    labelRightAnswerStr->setPosition(visibleSize.width/2, visibleSize.height*5/8);
    this->addChild(labelRightAnswerStr, 1);

//    auto labelContinue = LabelTTF::create(vm["Continue"].asString().c_str(), "Georgia", 48,Size(visibleSize.width,108),TextHAlignment::CENTER,TextVAlignment::CENTER);
//    labelContinue->setPosition(visibleSize.width/2, visibleSize.height/4);
//    this->addChild(labelContinue, 1);
    
    //    auto touchListener = EventListenerTouchOneByOne::create();
    //    touchListener->onTouchBegan = CC_CALLBACK_2(GameOver::restart,this);
    //    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,this);

	

		MenuItemFont::setFontSize(48);
		MenuItemFont::setFontName("Georgia");
		auto restartMenu = MenuItemFont::create(vm["Continue"].asString().c_str(),this,menu_selector(GameOver::restart));

		restartMenu->setColor(Color3B(255,255,255));
		restartMenu->setPosition(Vec2(visibleSize.width/2 ,visibleSize.height*5/16));

    
		auto restartMenuQ = Menu::create(restartMenu, NULL);
		restartMenuQ->setPosition(Vec2::ZERO);
		this->addChild(restartMenuQ, 1);




    return true;
}


void GameOver::restart(Ref* pSender)
{
    
	log("-------------------------------------------------start--------------------------------------");
    auto *idiomPioneer = IdiomPioneer::createScene();
    //float t = 3.0f;

	//CCDirector::sharedDirector()->replaceScene(TransitionFade ::create(t , aeroStunt));
	Director::sharedDirector()->replaceScene(TransitionPageTurn ::create(1.0f , idiomPioneer,false));
    return;
}

void GameOver::setup(Ref* pSender)
{
    
    auto *setup = Setup::createScene();
    //float t = 3.0f;
    
    Director::sharedDirector()->replaceScene(TransitionPageTurn ::create(1.0f , setup,false));
    //Director::sharedDirector()->replaceScene(setup);
}


