#include "Purchase.h"
#include "IOSiAP_Bridge.h"


USING_NS_CC;
USING_NS_CC_EXT;

#include <iostream>
#include <cmath>
#include <string> 
#include <sstream>

using namespace std;


// on "init" you need to initialize your instance
bool PopP::init()
{
    //////////////////////////////
    // 1. super init first
	if ( !LayerColor::initWithColor(Color4B(100,100,100,100)))
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	string fullPlistPath = FileUtils::sharedFileUtils()->fullPathForFilename("my.plist");
	FileUtils *fu = FileUtils::getInstance();
	ValueMap vm = fu->getValueMapFromFile(fullPlistPath.c_str());


	Scale9Sprite* scale9 = Scale9Sprite::create("scale9-.png");
	scale9->setContentSize(Size(visibleSize.width*4/5,visibleSize.height*2/3));
	scale9->setPosition(visibleSize.width/2,visibleSize.height/2);
	addChild(scale9);

    
    auto l1000 = LabelTTF::create("1000", "Georgia", 36);
    l1000->setPosition(visibleSize.width/2,visibleSize.height*2/3+50);
    this->addChild(l1000, 1);
    
    auto label1000 = LabelTTF::create(vm["1000coins"].asString().c_str(), "Georgia", 36, Size(visibleSize.width*7/10,100),TextHAlignment::CENTER,TextVAlignment::CENTER);
    label1000->setPosition(visibleSize.width/2,visibleSize.height*2/3);
    this->addChild(label1000, 1);
    
    auto label1000Price = LabelTTF::create(vm["1000coinsPrice"].asString().c_str(), "Georgia", 36);
    label1000Price->setPosition(visibleSize.width/2-60,visibleSize.height*2/3-50);
    this->addChild(label1000Price, 1);
    
    MenuItemFont::setFontSize(36);
    MenuItemFont::setFontName("Georgia");
    auto coinMenu = MenuItemFont::create(vm["Perchase"].asString().c_str(),CC_CALLBACK_1(PopP::consumble801, this, 1));
    coinMenu->setColor(Color3B(255,196,0));
    coinMenu->setPosition(visibleSize.width/2+90,visibleSize.height*2/3-50);
    auto coinMenuQ = Menu::create(coinMenu,NULL);
    coinMenuQ->setPosition(Vec2::ZERO);
    this->addChild(coinMenuQ, 1);
    
    
    auto l10000 = LabelTTF::create("10000", "Georgia", 36);
    l10000->setPosition(visibleSize.width/2,visibleSize.height/2+50);
    this->addChild(l10000, 1);
    
    auto label10000 = LabelTTF::create(vm["10000coins"].asString().c_str(), "Georgia", 36, Size(visibleSize.width*7/10,100),TextHAlignment::CENTER,TextVAlignment::CENTER);
    label10000->setPosition(visibleSize.width/2,visibleSize.height/2);
    this->addChild(label10000, 1);
    
    auto label10000Price = LabelTTF::create(vm["10000coinsPrice"].asString().c_str(), "Georgia", 36);
    label10000Price->setPosition(visibleSize.width/2-60,visibleSize.height/2-50);
    this->addChild(label10000Price, 1);

    MenuItemFont::setFontSize(36);
    MenuItemFont::setFontName("Georgia");
    auto purchaseMenu = MenuItemFont::create(vm["Perchase"].asString().c_str(),CC_CALLBACK_1(PopP::consumble101, this, 2));
    purchaseMenu->setColor(Color3B(255,196,0));
    purchaseMenu->setPosition(visibleSize.width/2+90,visibleSize.height/2-50);
    auto purchaseMenuQ = Menu::create(purchaseMenu,NULL);
    purchaseMenuQ->setPosition(Vec2::ZERO);
    this->addChild(purchaseMenuQ, 1);
    
//    MenuItemFont::setFontSize(40);
//    MenuItemFont::setFontName("Georgia");
//    auto repurchaseMenu = MenuItemFont::create("repurchase",CC_CALLBACK_1(PopP::consumble801, this, 1));
//    repurchaseMenu->setColor(Color3B(255,255,255));
//    repurchaseMenu->setPosition(visibleSize.width/2,visibleSize.height*2/3-200);
//    auto repurchaseMenuQ = Menu::create(repurchaseMenu,NULL);
//    repurchaseMenuQ->setPosition(Vec2::ZERO);
//    this->addChild(repurchaseMenuQ, 1);
    
   
    
    
    
    
    
    auto returnItem = MenuItemImage::create(
                                            "home_48.png",
                                            "home_96.png",
                                            CC_CALLBACK_1(PopP::cancel, this));
    
    returnItem->setPosition(Vec2(visibleSize.width/2 ,
                                 visibleSize.height/4));
    
    // create menu, it's an autorelease object
    auto returnMenu = Menu::create(returnItem, NULL);
    returnMenu->setPosition(Vec2::ZERO);
    this->addChild(returnMenu, 1);

    auto callback = [](Touch *,Event *){
        return true;
    };
    
    
    
    auto touchListenerPop = EventListenerTouchOneByOne::create();
    //touchListenerPop->onTouchBegan = CC_CALLBACK_2(Pop::onTouchBegan,this);
    touchListenerPop->onTouchBegan = callback;
    touchListenerPop->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListenerPop,this);
    
    return true;
}




void PopP::cancel(Ref* pSender)
{
	this->removeFromParentAndCleanup(true);
    return;
}

void PopP::consumble801(Ref* pSender,int perID)
{
    
    IOSiAP_Bridge* bridge = new IOSiAP_Bridge();
    log("consumble801:%d",perID);
    bridge->requestProducts(perID);
    
    
}

void PopP::consumble101(Ref* pSender,int perID)
{
    
    IOSiAP_Bridge* bridge = new IOSiAP_Bridge();
    bridge->requestProducts(perID);
    
    
}





