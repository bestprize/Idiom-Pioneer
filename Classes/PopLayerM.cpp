#include "PopLayerM.h"
#include "IdiomPioneerScene.h"
#include "CardSprite.h"
#include "SetupScene.h"
#include "PopLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

#include <iostream>
#include <cmath>
#include <string> 
#include <sstream>

using namespace std;


// on "init" you need to initialize your instance
bool PopM::init()
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

	//auto label = LabelTTF::create(vm["NotRight"].asString().c_str(),"Georgia",32);
	//label->setColor(Color3B(255,255,255));
	//label->setPosition(visibleSize.width*3/8,visibleSize.height*2/3+29);
	//addChild(label);
    
 //   auto closeItem = MenuItemImage::create(
 //                                          "yes_48.png",
 //                                          "yes_48.png",
 //                                          CC_CALLBACK_1(PopM::menuCloseCallback, this));
 //   
	//closeItem->setPosition(visibleSize.width/2,visibleSize.height*2/3-29);

 //   // create menu, it's an autorelease object
 //   auto menu = Menu::create(closeItem, NULL);
 //   menu->setPosition(Vec2::ZERO);
 //   addChild(menu, 1);





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



bool PopM::onTouchBegan(cocos2d::Touch *touch,cocos2d::Event *unused_event){

	return true;

}


void PopM::menuCloseCallbackYesTip(Ref* pSender,int wealthDedu)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
    auto ratio = visibleSize.height/visibleSize.width;
    
	int wealth = UserDefault::sharedUserDefault()->getIntegerForKey("wealth",1000) - wealthDedu;
    if(wealth < 0){
        string fullPlistPath = FileUtils::sharedFileUtils()->fullPathForFilename("my.plist");
        FileUtils *fu = FileUtils::getInstance();
        ValueMap vm = fu->getValueMapFromFile(fullPlistPath.c_str());
        
        auto failurePop = Pop::create();
        failurePop->setContentM(vm["CoinsNotEnough"].asString().c_str(),42);
        _parent->addChild(failurePop,100,"failurePop");
        this->removeFromParentAndCleanup(true);
        return;

    }
	UserDefault::sharedUserDefault()->setIntegerForKey("wealth",wealth);
	log("%d",wealth);

	auto labelCoins = LabelTTF::create(String::createWithFormat("%d",wealth)->_string, "Georgia", 36);
	labelCoins->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);//
    labelCoins->setPosition(96, visibleSize.height-48);
	this->_parent->removeChildByName("labelCoins",true);
	this->_parent->addChild(labelCoins, 1,"labelCoins");

	auto tipNumber = UserDefault::sharedUserDefault()->getIntegerForKey("tipNumber",0);
	tipNumber ++;
	Size mySize = Director::getInstance()->getVisibleSize();
	auto grade = UserDefault::sharedUserDefault()->getIntegerForKey("grade",3);
	clearCardSpriteAll(mySize);
	for(int i=0;i<tipNumber;i++){
		String *character = String::createWithFormat("%s",rightAnswer[i].c_str());
        if(ratio > 1.7){
            int lon = (mySize.width-28)/grade;
            CardSprite *cardSprite = CardSprite::createCardSprite(grade,character,lon,lon,lon*rightAnswerPositionOnFinalOrderX[i]+20,lon*rightAnswerPositionOnFinalOrderY[i]+20+mySize.height/4,1);
            this->_parent->addChild(cardSprite);
        }
        if(ratio > 1.4 && ratio < 1.7){
            int lon = (mySize.width-120)/grade;
            CardSprite *cardSprite = CardSprite::createCardSprite(grade,character,lon,lon,lon*rightAnswerPositionOnFinalOrderX[i]+60,lon*rightAnswerPositionOnFinalOrderY[i]+60+mySize.height/4-30,1);
            this->_parent->addChild(cardSprite);
        }
        if(ratio < 1.4){
            int lon = (mySize.width-160)/grade;
            CardSprite *cardSprite = CardSprite::createCardSprite(grade,character,lon,lon,lon*rightAnswerPositionOnFinalOrderX[i]+80,lon*rightAnswerPositionOnFinalOrderY[i]+80+mySize.height/4-90,1);
            this->_parent->addChild(cardSprite);
        }
		characterChoosedArray[i] = rightAnswer[i];
		characterChooseStatus[rightAnswerPositionOnFinalOrderX[i]*grade+rightAnswerPositionOnFinalOrderY[i]] = 1;
		characterChoosedTotal ++;
	}
	if(tipNumber>=rightAnswerLength){tipNumber --;}
	UserDefault::sharedUserDefault()->setIntegerForKey("tipNumber",tipNumber);

	this->removeFromParentAndCleanup(true);
}

void PopM::menuCloseCallbackYesAnswer(Ref* pSender,int wealthDedu)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    auto ratio = visibleSize.height/visibleSize.width;
	int wealth = UserDefault::sharedUserDefault()->getIntegerForKey("wealth",1000) - wealthDedu;
    if(wealth < 0){
        string fullPlistPath = FileUtils::sharedFileUtils()->fullPathForFilename("my.plist");
        FileUtils *fu = FileUtils::getInstance();
        ValueMap vm = fu->getValueMapFromFile(fullPlistPath.c_str());
        
        auto failurePop = Pop::create();
        failurePop->setContentM(vm["CoinsNotEnough"].asString().c_str(),42);
        _parent->addChild(failurePop,100,"failurePop");
        this->removeFromParentAndCleanup(true);
        return;
        
    }
	UserDefault::sharedUserDefault()->setIntegerForKey("wealth",wealth);
	log("%d",wealth);

	auto labelCoins = LabelTTF::create(String::createWithFormat("%d",wealth)->_string, "Georgia", 36);
	labelCoins->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);//
    labelCoins->setPosition(96, visibleSize.height-48);
	this->_parent->removeChildByName("labelCoins",true);
	this->_parent->addChild(labelCoins, 1,"labelCoins");

	Size mySize = Director::getInstance()->getVisibleSize();
	auto grade = UserDefault::sharedUserDefault()->getIntegerForKey("grade",3);
	clearCardSpriteAll(mySize);
	for(int i=0;i<rightAnswerLength;i++){
		String *character = String::createWithFormat("%s",rightAnswer[i].c_str());
        if(ratio > 1.7){
            int lon = (mySize.width-28)/grade;
            CardSprite *cardSprite = CardSprite::createCardSprite(grade,character,lon,lon,lon*rightAnswerPositionOnFinalOrderX[i]+20,lon*rightAnswerPositionOnFinalOrderY[i]+20+mySize.height/4,1);
            this->_parent->addChild(cardSprite);
        }
        if(ratio > 1.4 && ratio < 1.7){
            int lon = (mySize.width-120)/grade;
            CardSprite *cardSprite = CardSprite::createCardSprite(grade,character,lon,lon,lon*rightAnswerPositionOnFinalOrderX[i]+60,lon*rightAnswerPositionOnFinalOrderY[i]+60+mySize.height/4-30,1);
            this->_parent->addChild(cardSprite);
        }
        if(ratio < 1.4){
            int lon = (mySize.width-160)/grade;
            CardSprite *cardSprite = CardSprite::createCardSprite(grade,character,lon,lon,lon*rightAnswerPositionOnFinalOrderX[i]+80,lon*rightAnswerPositionOnFinalOrderY[i]+80+mySize.height/4-90,1);
            this->_parent->addChild(cardSprite);
        }
		characterChoosedArray[i] = rightAnswer[i];
		characterChooseStatus[rightAnswerPositionOnFinalOrderX[i]*grade+rightAnswerPositionOnFinalOrderY[i]] = 1;
		characterChoosedTotal ++;
	}

	this->removeFromParentAndCleanup(true);
}

void PopM::menuCloseCallbackYesSkip(Ref* pSender,int wealthDedu)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
	int wealth = UserDefault::sharedUserDefault()->getIntegerForKey("wealth",1000) - wealthDedu;
    if(wealth < 0){
        string fullPlistPath = FileUtils::sharedFileUtils()->fullPathForFilename("my.plist");
        FileUtils *fu = FileUtils::getInstance();
        ValueMap vm = fu->getValueMapFromFile(fullPlistPath.c_str());
        
        auto failurePop = Pop::create();
        failurePop->setContentM(vm["CoinsNotEnough"].asString().c_str(),42);
        _parent->addChild(failurePop,100,"failurePop");
        this->removeFromParentAndCleanup(true);
        return;
        
    }
	UserDefault::sharedUserDefault()->setIntegerForKey("wealth",wealth);
	log("%d",wealth);

	auto labelCoins = LabelTTF::create(String::createWithFormat("%d",wealth)->_string, "Georgia", 36);
	labelCoins->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);//
    labelCoins->setPosition(96, visibleSize.height-48);
	this->_parent->removeChildByName("labelCoins",true);
	this->_parent->addChild(labelCoins, 1,"labelCoins");

    UserDefault::sharedUserDefault()->setIntegerForKey("firstStartFlag",1);
	auto *idiomPioneer = IdiomPioneer::createScene();
    float t = 1.0f;

	Director::sharedDirector()->replaceScene(TransitionPageTurn ::create(1.0f , idiomPioneer,false));



	this->removeFromParentAndCleanup(true);
}

void PopM::menuCloseCallbackYesSetupSkip(Ref* pSender,int wealthDedu)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    int wealth = UserDefault::sharedUserDefault()->getIntegerForKey("wealth",1000) - wealthDedu;
    if(wealth < 0){
        string fullPlistPath = FileUtils::sharedFileUtils()->fullPathForFilename("my.plist");
        FileUtils *fu = FileUtils::getInstance();
        ValueMap vm = fu->getValueMapFromFile(fullPlistPath.c_str());
        
        auto failurePop = Pop::create();
        failurePop->setContentM(vm["CoinsNotEnough"].asString().c_str(),42);
        _parent->addChild(failurePop,100,"failurePop");
        this->removeFromParentAndCleanup(true);
        return;
        
    }
    UserDefault::sharedUserDefault()->setIntegerForKey("wealth",wealth);
    log("%d",wealth);
    
    auto labelCoins = LabelTTF::create(String::createWithFormat("%d",wealth)->_string, "Georgia", 36);
    labelCoins->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);//
    labelCoins->setPosition(96, visibleSize.height-48);
    this->_parent->removeChildByName("labelCoins",true);
    this->_parent->addChild(labelCoins, 1,"labelCoins");
    
    auto *setup = Setup::createScene();
    float t = 1.0f;
    
    Director::sharedDirector()->replaceScene(TransitionPageTurn ::create(1.0f , setup,false));
    
    
    
    this->removeFromParentAndCleanup(true);
}

void PopM::menuCloseCallbackNo(Ref* pSender)
{
	this->removeFromParentAndCleanup(true);
}

void PopM::setContentM( const char* content, int fontsize ){

	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto label = LabelTTF::create(content,"Georgia",fontsize,Size(visibleSize.width*5/8,400),TextHAlignment::CENTER,TextVAlignment::CENTER);
	label->setColor(Color3B(255,255,255));
	label->setPosition(visibleSize.width/2,visibleSize.height*2/3);
	addChild(label);

//setLabelTitle(ltfTitle);

}

void PopM::setMenuM(int wealthDedu,string func){

	Size visibleSize = Director::getInstance()->getVisibleSize();

	MenuItemImage *closeItemYes;
	if(func.compare("Tip")==0){
		closeItemYes = MenuItemImage::create(
											   "yes_64.png",
											   "yes_128.png",
											   CC_CALLBACK_1(PopM::menuCloseCallbackYesTip, this,wealthDedu));
	} else if(func.compare("Answer")==0){
		closeItemYes = MenuItemImage::create(
											   "yes_64.png",
											   "yes_128.png",
											   CC_CALLBACK_1(PopM::menuCloseCallbackYesAnswer, this,wealthDedu));
	} else if(func.compare("Skip")==0){
		closeItemYes = MenuItemImage::create(
											   "yes_64.png",
											   "yes_128.png",
											   CC_CALLBACK_1(PopM::menuCloseCallbackYesSkip, this,wealthDedu));
    } else if(func.compare("SetupSkip")==0){
        closeItemYes = MenuItemImage::create(
                                             "yes_64.png",
                                             "yes_128.png",
                                             CC_CALLBACK_1(PopM::menuCloseCallbackYesSetupSkip, this,wealthDedu));
    }
    
	closeItemYes->setPosition(visibleSize.width*2/5,visibleSize.height/3);

    // create menu, it's an autorelease object
    auto menuYes = Menu::create(closeItemYes, NULL);
    menuYes->setPosition(Vec2::ZERO);
    addChild(menuYes, 1);

    auto closeItemNo = MenuItemImage::create(
                                           "no_64.png",
                                           "no_128.png",
                                           CC_CALLBACK_1(PopM::menuCloseCallbackNo, this));
    
	closeItemNo->setPosition(visibleSize.width*3/5,visibleSize.height/3);

    // create menu, it's an autorelease object
    auto menuNo = Menu::create(closeItemNo, NULL);
    menuNo->setPosition(Vec2::ZERO);
    addChild(menuNo, 1);




}

void PopM::clearCardSpriteAll(cocos2d::Size mySize){

	auto grade = UserDefault::sharedUserDefault()->getIntegerForKey("grade",3);
    Size visibleSize = Director::getInstance()->getVisibleSize();
    auto ratio = visibleSize.height/visibleSize.width;
    
    if(ratio > 1.7){
        int lon = (mySize.width-28)/grade;

        for(int i=0;i<grade;i++){
            for(int j=0;j<grade;j++){
                if(characterChooseStatus[i*grade+j]==1){
                    String *character = String::createWithFormat("%s",characterArray[i*grade+j].c_str());
                    CardSprite *cardSprite = CardSprite::createCardSprite(grade,character,lon,lon,lon*i+20,lon*j+20+mySize.height/4,0);
                    this->_parent->addChild(cardSprite);
                    characterChooseStatus[i*grade+j]=0;
                    for(int k=0;k<characterChoosedTotal;k++){
                        if(characterChoosedArray[k] == characterArray[i*grade+j]){
                            for(int l=k;l<characterChoosedTotal-1;l++){
                                characterChoosedArray[l] = characterChoosedArray[l+1];
                            }
                            break;
                        }
                    }
                    characterChoosedTotal --;
                }

            }
        }
    }

    if(ratio > 1.4 && ratio < 1.7){
        int lon = (mySize.width-120)/grade;
        
        for(int i=0;i<grade;i++){
            for(int j=0;j<grade;j++){
                if(characterChooseStatus[i*grade+j]==1){
                    String *character = String::createWithFormat("%s",characterArray[i*grade+j].c_str());
                    CardSprite *cardSprite = CardSprite::createCardSprite(grade,character,lon,lon,lon*i+60,lon*j+60+mySize.height/4-30,0);
                    this->_parent->addChild(cardSprite);
                    characterChooseStatus[i*grade+j]=0;
                    for(int k=0;k<characterChoosedTotal;k++){
                        if(characterChoosedArray[k] == characterArray[i*grade+j]){
                            for(int l=k;l<characterChoosedTotal-1;l++){
                                characterChoosedArray[l] = characterChoosedArray[l+1];
                            }
                            break;
                        }
                    }
                    characterChoosedTotal --;
                }
                
            }
        }
    }
    
    if(ratio < 1.4){
        int lon = (mySize.width-160)/grade;
        
        for(int i=0;i<grade;i++){
            for(int j=0;j<grade;j++){
                if(characterChooseStatus[i*grade+j]==1){
                    String *character = String::createWithFormat("%s",characterArray[i*grade+j].c_str());
                    CardSprite *cardSprite = CardSprite::createCardSprite(grade,character,lon,lon,lon*i+80,lon*j+80+mySize.height/4-90,0);
                    this->_parent->addChild(cardSprite);
                    characterChooseStatus[i*grade+j]=0;
                    for(int k=0;k<characterChoosedTotal;k++){
                        if(characterChoosedArray[k] == characterArray[i*grade+j]){
                            for(int l=k;l<characterChoosedTotal-1;l++){
                                characterChoosedArray[l] = characterChoosedArray[l+1];
                            }
                            break;
                        }
                    }
                    characterChoosedTotal --;
                }
                
            }
        }
    }
    
}



