#include "IdiomPioneerScene.h"
#include "CardSprite.h"
#include "sqlite3.h"
#include "GameOverScene.h"
#include "SetupScene.h"
#include "PopLayer.h"
#include "PopLayerM.h"
#include "Purchase.h"
#include "AdsmogoBanner.h"
#include "AdsMogoInterstitial.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"



#include <iostream>
#include <cmath>
#include <string> 
#include <sstream>


string idiomArray[25];
int idiomArrayPosition;

string thisLevel;
string rightAnswerStr;

string idiomArrayConfirm[1];
int idiomArrayPositionConfirm;

int rightAnswerPositionOnFinalOrderX[16];
int rightAnswerPositionOnFinalOrderY[16];

string rightAnswer[16];
int rightAnswerLength;

int characterChooseStatus[50];
string characterChoosedArray[50];
int characterChoosedTotal;

string characterArray[50];
int characterArrayPosition;


USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;

Scene* IdiomPioneer::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layerIdiomPioneer = IdiomPioneer::create();

    // add layer as a child to scene
    scene->addChild(layerIdiomPioneer,10,"layerIdiomPioneer");

	//auto backGroundLayer = LayerColor::create(Color4B(81,125,105,255));
    auto backGroundLayer = LayerColor::create(Color4B(80,137,167,255));
	scene->addChild(backGroundLayer,0,"backGroundLayer");
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    auto sprite = Sprite::create("back.png");
    sprite->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    
    float x = visibleSize.width/(sprite->getContentSize().width);
    float y = visibleSize.height/(sprite->getContentSize().height);
    auto scaleTo = ScaleTo::create(0.0f, x>=y?x:y);
    sprite->runAction(scaleTo);
    scene->addChild(sprite, 1);
    
    
    
    UserDefault::sharedUserDefault()->setIntegerForKey("sceneFlag",0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool IdiomPioneer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    auto ratio = visibleSize.height/visibleSize.width;
    int adjustHeightTop = 0;
    int adjustHeightBot = 0;
    if(ratio > 1.7){
        
    }
    if(ratio > 1.4 && ratio < 1.7){
        adjustHeightTop = -90;
        adjustHeightBot = 0;
    }
    if(ratio < 1.4){
        adjustHeightTop = -170;
        adjustHeightBot = -30;
    }
    
    char mogoid []="4240cd75bd72463ba623ce172c9ce7f9";
    AdsmogoBanner::sharedBanner()->createBanner(mogoid,AdsmogoBannerTypeNormalBanner,AdMoGoPointTypeDown_middle,true);
    AdsmogoBanner::sharedBanner()->showBanner();
    
    struct timeval nowTimeval;
    gettimeofday(&nowTimeval, NULL);
    struct tm * tm;
    time_t time_sec ;
    time_sec = nowTimeval.tv_sec;
    tm = localtime(&time_sec);
    auto nowDay = tm->tm_mday;
    int day = UserDefault::sharedUserDefault()->getIntegerForKey("day",1);
    if(nowDay != day){
        UserDefault::sharedUserDefault()->setIntegerForKey("day",nowDay);
        UserDefault::sharedUserDefault()->setIntegerForKey("wealth",UserDefault::sharedUserDefault()->getIntegerForKey("wealth",1000)+1000);
    }
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("click.mp3");
    
	//level = "1";
	level = UserDefault::sharedUserDefault()->getStringForKey("level","1");
	//grade = 3;
	grade = UserDefault::sharedUserDefault()->getIntegerForKey("grade",3);
	//wealth = 1000;
	auto wealth = UserDefault::sharedUserDefault()->getIntegerForKey("wealth",1000);
    UserDefault::sharedUserDefault()->setIntegerForKey("wealth",wealth);

	UserDefault::sharedUserDefault()->setIntegerForKey("tipNumber",0);

    

	string fullPlistPath = FileUtils::sharedFileUtils()->fullPathForFilename("my.plist");
	FileUtils *fu = FileUtils::getInstance();
	ValueMap vm = fu->getValueMapFromFile(fullPlistPath.c_str());

//    auto spriteCoins = Sprite::create("coins_64.png");
//    spriteCoins->setAnchorPoint(Vec2(0,0));
//    spriteCoins->setPosition(32, visibleSize.height-96);
//    this->addChild(spriteCoins, 1);

    auto coinsItem = MenuItemImage::create(
                                           "coins_48.png",
                                           "coins_96.png",
                                           CC_CALLBACK_1(IdiomPioneer::coins, this));
    
    coinsItem->setAnchorPoint(Vec2(0,0));
    coinsItem->setPosition(Vec2(32, visibleSize.height-72));
    auto coinsMenu = Menu::create(coinsItem, NULL);
    coinsMenu->setPosition(Vec2::ZERO);
    this->addChild(coinsMenu, 1);
    
    auto labelCoins = LabelTTF::create(String::createWithFormat("%d",wealth)->_string, "Georgia", 36);
	labelCoins->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);//
    labelCoins->setPosition(96, visibleSize.height-48);
    this->addChild(labelCoins, 1,"labelCoins");

    auto setupItem = MenuItemImage::create(
                                           "setup_48.png",
                                           "setup_96.png",
                                           CC_CALLBACK_1(IdiomPioneer::setup, this));
    
	setupItem->setAnchorPoint(Vec2(0,0));
	setupItem->setPosition(Vec2(visibleSize.width-80, visibleSize.height-72));
    auto setupMenu = Menu::create(setupItem, NULL);
    setupMenu->setPosition(Vec2::ZERO);
    this->addChild(setupMenu, 1);

    auto tipItem = MenuItemImage::create(
                                           "tip_48.png",
                                           "tip_96.png",
                                           CC_CALLBACK_1(IdiomPioneer::tip, this));
    
	tipItem->setPosition(Vec2(90, visibleSize.height/4+visibleSize.width-8 + 47 + adjustHeightTop));
    auto tipMenu = Menu::create(tipItem, NULL);
    tipMenu->setPosition(Vec2::ZERO);
    this->addChild(tipMenu, 1);

    auto removeItem = MenuItemImage::create(
                                           "refresh_48.png",
                                           "refresh_96.png",
                                           CC_CALLBACK_1(IdiomPioneer::remove, this));
    
	removeItem->setPosition(Vec2(90+(visibleSize.width-28)/4,visibleSize.height/4+visibleSize.width-8 + 47 + adjustHeightTop));
    auto removeMenu = Menu::create(removeItem, NULL);
    removeMenu->setPosition(Vec2::ZERO);
    this->addChild(removeMenu, 1);

    auto answerItem = MenuItemImage::create(
                                           "answer_48.png",
                                           "answer_96.png",
                                           CC_CALLBACK_1(IdiomPioneer::answer, this));
    
	answerItem->setPosition(Vec2(90+(visibleSize.width-28)*2/4,visibleSize.height/4+visibleSize.width-8 + 47 + adjustHeightTop));
    auto answerMenu = Menu::create(answerItem, NULL);
    answerMenu->setPosition(Vec2::ZERO);
    this->addChild(answerMenu, 1);

    auto skipItem = MenuItemImage::create(
                                           "skip_48.png",
                                           "skip_96.png",
                                           CC_CALLBACK_1(IdiomPioneer::skip, this));
    
	skipItem->setPosition(Vec2(90+(visibleSize.width-28)*3/4,visibleSize.height/4+visibleSize.width-8 + 47 + adjustHeightTop));
    auto skipMenu = Menu::create(skipItem, NULL);
    skipMenu->setPosition(Vec2::ZERO);
    this->addChild(skipMenu, 1);

    int firstStartFlag = UserDefault::sharedUserDefault()->getIntegerForKey("firstStartFlag",0);
    int sceneFlag = UserDefault::sharedUserDefault()->getIntegerForKey("sceneFlag",0);
    log("firstStartFlag--------%d",firstStartFlag);
    log("sceneFlag--------%d",sceneFlag);
    
    if(firstStartFlag==0 && sceneFlag==0){
        
        string characterArrayStrExisted = UserDefault::sharedUserDefault()->getStringForKey("characterArrayStr","");
        string rightAnswerStrStoredExisted = UserDefault::sharedUserDefault()->getStringForKey("rightAnswerStrStored","");
        string rightAnswerStrExisted = UserDefault::sharedUserDefault()->getStringForKey("rightAnswerStr","");
        log("%s",rightAnswerStrStoredExisted.c_str());
        log("%s",rightAnswerStrExisted.c_str());
        
        if(strlen(characterArrayStrExisted.c_str())/3 == grade*grade){
            for(int i=0;i<grade*grade;i++){
                characterArray[i] = characterArrayStrExisted.substr(i*3,3);
            }
            
            
            for(int i=0;i<strlen(rightAnswerStrStoredExisted.c_str())/3;i++){
                rightAnswer[i] = rightAnswerStrStoredExisted.substr(i*3,3);
            }
            
            rightAnswerStr = rightAnswerStrExisted;
            rightAnswerLength = strlen(rightAnswerStrStoredExisted.c_str())/3;
        } else {
            log("%s","data error!");
            UserDefault::sharedUserDefault()->setIntegerForKey("firstStartFlag",1);
            auto *newIdiomPioneerScene = IdiomPioneer::createScene();
            Director::sharedDirector()->replaceScene(newIdiomPioneerScene);
        }
        
        
    } else {
        
	//////init data
	sqlite3 *pDB = NULL;
	char *errMsg = NULL;
	std::string sqlstr;
	int result;
	char **dbResult;
	int nRow;
	int nColumn;

	string fullDBPath = FileUtils::sharedFileUtils()->fullPathForFilename("idiom");
	//log("%s",fullDBPath.c_str());
	result = sqlite3_open(fullDBPath.c_str(),&pDB);
	if(result != SQLITE_OK){
		CCLOG("open DB error!");
	}

	int totalCount;
	sqlstr = "select * from idiom";
	sqlite3_get_table(pDB,sqlstr.c_str(),&dbResult,&nRow,&nColumn,&errMsg);
	totalCount = nRow;
	//log("-------------%d",totalCount);

	int idiomNumber;
	idiomArrayPosition = 0;
	//the answer
	srand(int(time(0))+ rand());
	bool isThisLevel = false;
	while(!isThisLevel){
		sqlstr = "select * from idiom where id = " + String::createWithFormat("%d",1+rand()%totalCount)->_string;
		//sqlstr = "select * from idiom where id = 15862" ;
		//log("%s",sqlstr.c_str());
		sqlite3_exec(pDB,sqlstr.c_str(),loadRecord,NULL,&errMsg);
		//log("thislevel:%s",thisLevel.c_str());
		if(thisLevel.compare(level) == 0){isThisLevel = true;}
		if(grade==3 && strlen(idiomArray[idiomArrayPosition].c_str())/3>9){isThisLevel = false;}
	}
	//log("%s",idiomArray[idiomArrayPosition].c_str());
	//log("%d",strlen(idiomArray[idiomArrayPosition].c_str()));
	idiomNumber = (grade*grade - strlen(idiomArray[idiomArrayPosition].c_str())/3)/2 + 1;
	//log("%d",idiomNumber);
	idiomArrayPosition ++;
	for(int i=0;i<idiomNumber;i++){
		srand(int(time(0))+ rand());
		sqlstr = "select * from idiom where id = " + String::createWithFormat("%d",1+rand()%(totalCount))->_string;
		sqlite3_exec(pDB,sqlstr.c_str(),loadRecord,NULL,&errMsg);
		//log("%s",idiomArray[idiomArrayPosition].c_str());
		//log("%d",strlen(idiomArray[idiomArrayPosition].c_str()));
		idiomArrayPosition ++;
	}
	sqlite3_close(pDB);

	//right answer
	characterArrayPosition = 0;
	rightAnswerLength = 0;
	for(int i=0;i<strlen(idiomArray[0].c_str())/3;i++){
		characterArray[i] = idiomArray[0].substr(i*3,3);
		rightAnswer[i] = characterArray[i];
		//log("++++++++++%s",characterArray[i].c_str());
		characterArrayPosition ++;
		rightAnswerLength ++;
	}
	rightAnswerStr = idiomArray[0];
	bubbleSort(rightAnswer,rightAnswerLength);
	for(int i=0;i<rightAnswerLength;i++){
		log("rightAnswer::::::%s",rightAnswer[i].c_str());
	}

//////////////////////////////////////////////////////////////
	//log("%s",fullDBPath.c_str());
	//result = sqlite3_open(fullDBPath.c_str(),&pDB);
	//if(result != SQLITE_OK){
	//	CCLOG("open DB error!");
	//}

	////idiomArrayPositionConfirm = 0;
	//for(int i=totalCount;i<totalCount;i++){
	//	sqlstr = "select * from idiom where id = " + String::createWithFormat("%d",i+1)->_string;
	//	sqlite3_exec(pDB,sqlstr.c_str(),loadRecordConfirm,NULL,&errMsg);

	//	string rightAnswerConfirm[50];
	//	int rightAnswerLengthConfirm = 0;
	//	for(int j=0;j<strlen(idiomArrayConfirm[0].c_str())/3;j++){
	//		rightAnswerConfirm[j] = idiomArrayConfirm[0].substr(j*3,3);
	//		log("++++++++++%s",rightAnswerConfirm[j].c_str());
	//		rightAnswerLengthConfirm ++;
	//	}

	//	bubbleSort(rightAnswerConfirm,rightAnswerLengthConfirm);

	//	string md5Str = "";
	//	for(int j=0;j<rightAnswerLengthConfirm;j++){
	//		md5Str = md5Str + rightAnswerConfirm[j];
	//	}
	//	log("%s",md5Str.c_str());
	//	sqlstr = "update idiom set md5='"+md5Str+"' where id = " + String::createWithFormat("%d",i+1)->_string;
	//	log("%s",sqlstr.c_str());
	//	result=sqlite3_exec(pDB,sqlstr.c_str(),NULL,NULL,&errMsg);
	//	if(result!=SQLITE_OK){CCLOG("update error");}
	//	//sqlite3_close(pDB);

	//}

	//sqlite3_close(pDB);
//////////////////////////////////////////////////////////////

	for(int i=1;i<idiomNumber+1;i++){
		int firstCharacterPosition = rand()%((strlen(idiomArray[i].c_str())/3));
		characterArray[characterArrayPosition] = idiomArray[i].substr(firstCharacterPosition*3,3);
		//log("%d",characterArrayPosition);
		//log("++++++++++%s",characterArray[characterArrayPosition].c_str());
		characterArrayPosition++;
		if(characterArrayPosition == grade*grade){
			break;
		}
		int leftOrRight = rand()%2;
		if(firstCharacterPosition==0){leftOrRight = 1;}
		if(firstCharacterPosition==strlen(idiomArray[i].c_str())/3-1){leftOrRight = 0;}
		if(leftOrRight == 0){
			characterArray[characterArrayPosition] = idiomArray[i].substr((rand()%(firstCharacterPosition))*3,3);
		}
		if(leftOrRight == 1){
			characterArray[characterArrayPosition] = idiomArray[i].substr((firstCharacterPosition+1+rand()%(strlen(idiomArray[i].c_str())/3-firstCharacterPosition-1))*3,3);
		}
		//characterArray[characterArrayPosition] = idiomArray[i].substr(rand()%((strlen(idiomArray[i].c_str())/3))*3,3);
		//log("%d",characterArrayPosition);
		//log("++++++++++%s",characterArray[characterArrayPosition].c_str());
		characterArrayPosition++;
		if(characterArrayPosition == grade*grade){
			break;
		}

	}

	int tempRandIt;
	string randResult[50];
	for(int i=0;i<grade*grade;i++){
		srand(int(time(0))+ rand());
		if(i!=grade*grade-1){
			tempRandIt = rand()%(grade*grade-i);
		}else{
			tempRandIt = 0;
		}
		randResult[i] = characterArray[tempRandIt];
		for(int j=tempRandIt;j<grade*grade-1-i;j++){
			characterArray[j] = characterArray[j+1];
		}
	}
	

	for(int i=0;i<grade*grade;i++){
		characterArray[i] = randResult[i];
		log("^^^^^^^^^^^^^^^%s",characterArray[i].c_str());
	}

        
        string characterArrayStr = "";
        for(int i=0;i<grade*grade;i++){
            characterArrayStr = characterArrayStr + characterArray[i];
        }
        
        string rightAnswerStrStored = "";
        for(int i=0;i<rightAnswerLength;i++){
            rightAnswerStrStored = rightAnswerStrStored + rightAnswer[i];
        }
        
        UserDefault::sharedUserDefault()->setStringForKey("characterArrayStr",characterArrayStr);
        UserDefault::sharedUserDefault()->setStringForKey("rightAnswerStrStored",rightAnswerStrStored);
        UserDefault::sharedUserDefault()->setStringForKey("rightAnswerStr",rightAnswerStr);
        
    }
    
    
	//////search the right position
	int rightAnswerPositionOnFinalOrder[16];
	for(int i=0;i<rightAnswerLength;i++){
		for(int j=0;j<grade*grade;j++){
			if(rightAnswer[i].compare(characterArray[j])==0){
				rightAnswerPositionOnFinalOrder[i] = j;
				log("%s:%d",rightAnswer[i].c_str(),j);
				bool isRepeat = false;
				for(int k=0;k<i;k++){
					if(rightAnswerPositionOnFinalOrder[i]==rightAnswerPositionOnFinalOrder[k]){
						isRepeat = true;
						break;
					}
				}
				if(!isRepeat){break;}
			}
		}
	}

	for(int i=0;i<rightAnswerLength;i++){
		rightAnswerPositionOnFinalOrderX[i] = rightAnswerPositionOnFinalOrder[i]/grade;
		rightAnswerPositionOnFinalOrderY[i] = rightAnswerPositionOnFinalOrder[i]%grade;
	}



	for(int i=0;i<grade*grade;i++){
		characterChooseStatus[i] = 0;
	}

	characterChoosedTotal = 0;

	createCardSpriteAll(visibleSize);
    
    
    CheckBox *sound = CheckBox::create("soundoff_48.png",
                                       "",
                                       "sound_48.png",
                                       "",
                                       "");
    sound->setPosition(Vec2(90,visibleSize.height/4 - 27 + adjustHeightBot));
    sound->addEventListenerCheckBox(this,checkboxselectedeventselector(IdiomPioneer::sound));
    if(UserDefault::sharedUserDefault()->getIntegerForKey("sound",1) == 1){
        sound->setSelectedState(true);
    } else {
        sound->setSelectedState(false);
    }
    addChild(sound);

    auto confirmItem = MenuItemImage::create(
                                           "confirm.png",
                                           "confirm_256.png",
                                           CC_CALLBACK_1(IdiomPioneer::confirm, this));
    
	confirmItem->setPosition(Vec2(visibleSize.width*2/3,visibleSize.height/4-47 + adjustHeightBot));
    auto confirmMenu = Menu::create(confirmItem, NULL);
    confirmMenu->setPosition(Vec2::ZERO);
    this->addChild(confirmMenu, 1);



	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(IdiomPioneer::onTouchBegan,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,this);

    UserDefault::sharedUserDefault()->setIntegerForKey("firstStartFlag",1);
    UserDefault::sharedUserDefault()->setIntegerForKey("sceneFlag",1);
    
    return true;
}




void IdiomPioneer::createCardSpriteAll(cocos2d::Size mySize){
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    auto ratio = visibleSize.height/visibleSize.width;
    if(ratio > 1.7){
        int lon = (mySize.width-28)/grade;

        //String *example = String::create("X");
        //String *example = String::createWithFormat("%s",characterArray[0].c_str());
        for(int i=0;i<grade;i++){
            for(int j=0;j<grade;j++){
                String *character = String::createWithFormat("%s",characterArray[i*grade+j].c_str());
                CardSprite *cardSprite = CardSprite::createCardSprite(grade,character,lon,lon,lon*i+20,lon*j+20+mySize.height/4,characterChooseStatus[i*grade+j]);
                addChild(cardSprite);

            }
        }
    }

    if(ratio > 1.4 && ratio < 1.7){
        int lon = (mySize.width-120)/grade;
        
        //String *example = String::create("X");
        //String *example = String::createWithFormat("%s",characterArray[0].c_str());
        for(int i=0;i<grade;i++){
            for(int j=0;j<grade;j++){
                String *character = String::createWithFormat("%s",characterArray[i*grade+j].c_str());
                CardSprite *cardSprite = CardSprite::createCardSprite(grade,character,lon,lon,lon*i+60,lon*j+60+mySize.height/4 - 30,characterChooseStatus[i*grade+j]);
                addChild(cardSprite);
                
            }
        }
    }
    
    if(ratio < 1.4){
        int lon = (mySize.width-160)/grade;
        
        //String *example = String::create("X");
        //String *example = String::createWithFormat("%s",characterArray[0].c_str());
        for(int i=0;i<grade;i++){
            for(int j=0;j<grade;j++){
                String *character = String::createWithFormat("%s",characterArray[i*grade+j].c_str());
                CardSprite *cardSprite = CardSprite::createCardSprite(grade,character,lon,lon,lon*i+80,lon*j+80+mySize.height/4 - 90,characterChooseStatus[i*grade+j]);
                addChild(cardSprite);
                
            }
        }
    }
    
}


bool IdiomPioneer::onTouchBegan(cocos2d::Touch *touch,cocos2d::Event *unused_event){

    
	Point touchPO = touch->getLocation();
	Size visibleSize = Director::getInstance()->getVisibleSize();
    auto ratio = visibleSize.height/visibleSize.width;

    if(ratio > 1.7){
        int lon = (visibleSize.width-28)/grade;
        for(int i=0;i<grade;i++){
            for(int j=0;j<grade;j++){
                if((touchPO.x>lon*i+20) && (touchPO.x<lon*(i+1)+20) && (touchPO.y>lon*j+20+visibleSize.height/4) && (touchPO.y<lon*(j+1)+20+visibleSize.height/4)){
                    
                    if(UserDefault::sharedUserDefault()->getIntegerForKey("sound",1) == 1){
                        auto m_nSoundId = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("click.mp3");
                    }
                    
                    String *character = String::createWithFormat("%s",characterArray[i*grade+j].c_str());
                    if(characterChooseStatus[i*grade+j] == 0){
                        characterChooseStatus[i*grade+j] = 1;
                        characterChoosedArray[characterChoosedTotal] = characterArray[i*grade+j];
                        characterChoosedTotal ++;
                    } else if(characterChooseStatus[i*grade+j] == 1){
                        characterChooseStatus[i*grade+j] = 0;
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
                    CardSprite *cardSprite = CardSprite::createCardSprite(grade,character,lon,lon,lon*i+20,lon*j+20+visibleSize.height/4,characterChooseStatus[i*grade+j]);
                    addChild(cardSprite);
                    break;
                }
            }
        }
    }

    if(ratio > 1.4 && ratio < 1.7){
        int lon = (visibleSize.width-120)/grade;
        for(int i=0;i<grade;i++){
            for(int j=0;j<grade;j++){
                if((touchPO.x>lon*i+60) && (touchPO.x<lon*(i+1)+60) && (touchPO.y>lon*j+60+visibleSize.height/4-30) && (touchPO.y<lon*(j+1)+60+visibleSize.height/4-30)){
                    
                    if(UserDefault::sharedUserDefault()->getIntegerForKey("sound",1) == 1){
                        auto m_nSoundId = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("click.mp3");
                    }
                    
                    String *character = String::createWithFormat("%s",characterArray[i*grade+j].c_str());
                    if(characterChooseStatus[i*grade+j] == 0){
                        characterChooseStatus[i*grade+j] = 1;
                        characterChoosedArray[characterChoosedTotal] = characterArray[i*grade+j];
                        characterChoosedTotal ++;
                    } else if(characterChooseStatus[i*grade+j] == 1){
                        characterChooseStatus[i*grade+j] = 0;
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
                    CardSprite *cardSprite = CardSprite::createCardSprite(grade,character,lon,lon,lon*i+60,lon*j+60+visibleSize.height/4-30,characterChooseStatus[i*grade+j]);
                    addChild(cardSprite);
                    break;
                }
            }
        }
    }
    
    if(ratio < 1.4){
        int lon = (visibleSize.width-160)/grade;
        for(int i=0;i<grade;i++){
            for(int j=0;j<grade;j++){
                if((touchPO.x>lon*i+80) && (touchPO.x<lon*(i+1)+80) && (touchPO.y>lon*j+80+visibleSize.height/4-90) && (touchPO.y<lon*(j+1)+80+visibleSize.height/4-90)){
                    
                    if(UserDefault::sharedUserDefault()->getIntegerForKey("sound",1) == 1){
                        auto m_nSoundId = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("click.mp3");
                    }
                    
                    String *character = String::createWithFormat("%s",characterArray[i*grade+j].c_str());
                    if(characterChooseStatus[i*grade+j] == 0){
                        characterChooseStatus[i*grade+j] = 1;
                        characterChoosedArray[characterChoosedTotal] = characterArray[i*grade+j];
                        characterChoosedTotal ++;
                    } else if(characterChooseStatus[i*grade+j] == 1){
                        characterChooseStatus[i*grade+j] = 0;
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
                    CardSprite *cardSprite = CardSprite::createCardSprite(grade,character,lon,lon,lon*i+80,lon*j+80+visibleSize.height/4-90,characterChooseStatus[i*grade+j]);
                    addChild(cardSprite);
                    break;
                }
            }
        }
    }
    
	/*log("%d",characterChoosedTotal);
	for(int i=0;i<characterChoosedTotal;i++){
		log("--------------------%s",characterChoosedArray[i].c_str());
	}*/

	



	//CardSprite *cardSprite = getCardSprite(visibleSize,touchPO);
	

		return true;

}

void IdiomPioneer::confirm(Ref* pSender){

	bool successFlag = false;
    bubbleSort(characterChoosedArray,characterChoosedTotal);
	if(characterChoosedTotal != rightAnswerLength){
		successFlag = false;
	} else{
		for(int i=0;i<characterChoosedTotal;i++){
			if(characterChoosedArray[i] != rightAnswer[i]){
				successFlag = false;
				break;
			}
			successFlag = true;
		}
	}

	if(!successFlag){

		sqlite3 *pDB = NULL;
		char *errMsg = NULL;
		std::string sqlstr;
		int result;
		char **dbResult;
		int nRow;
		int nColumn;

        string fullDBPath = FileUtils::sharedFileUtils()->fullPathForFilename("idiom");
        //log("%s",fullDBPath.c_str());
        result = sqlite3_open(fullDBPath.c_str(),&pDB);
		if(result != SQLITE_OK){
			CCLOG("open DB error!");
		}

		string md5Str = "";
		for(int j=0;j<characterChoosedTotal;j++){
			md5Str = md5Str + characterChoosedArray[j];
		}
		log("%s",md5Str.c_str());

		int matchCount;
		sqlstr = "select idiomcontent from idiom where md5='"+md5Str+"'";
		sqlite3_get_table(pDB,sqlstr.c_str(),&dbResult,&nRow,&nColumn,&errMsg);
		matchCount = nRow;
		log("matchCount:%d",matchCount);
		if(matchCount>0){
            successFlag=true;
            rightAnswerStr = dbResult[1];
        }else{
            successFlag=false;
        }


		sqlite3_close(pDB);	
	}

	


	int successFlagInt;
	if(successFlag){successFlagInt=1;}else{successFlagInt=0;}
	log("%d",successFlagInt);

	//if(successFlag){MessageBox("’˝»∑","Ω·π˚");}else{MessageBox("≤ª’˝»∑","Ω·π˚");}
	if(successFlag){
        if(UserDefault::sharedUserDefault()->getIntegerForKey("sound",1) == 1){
            auto m_nSoundId = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("success.mp3");
        }

        Size visibleSize = Director::getInstance()->getVisibleSize();
        int wealth = UserDefault::sharedUserDefault()->getIntegerForKey("wealth",1000) + grade;
        UserDefault::sharedUserDefault()->setIntegerForKey("wealth",wealth);
        log("%d",wealth);
        
        auto labelCoins = LabelTTF::create(String::createWithFormat("%d",wealth)->_string, "Georgia", 36);
        labelCoins->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);//
        labelCoins->setPosition(96, visibleSize.height-48);
        removeChildByName("labelCoins",true);
        addChild(labelCoins, 1,"labelCoins");

		auto *gameOver = GameOver::createScene();
		Director::sharedDirector()->replaceScene(TransitionPageTurn ::create(1.0f , gameOver,false));
	
	}else{
        if(UserDefault::sharedUserDefault()->getIntegerForKey("sound",1) == 1){
            auto m_nSoundId = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("failure.mp3");
        }

        string fullPlistPath = FileUtils::sharedFileUtils()->fullPathForFilename("my.plist");
        FileUtils *fu = FileUtils::getInstance();
        ValueMap vm = fu->getValueMapFromFile(fullPlistPath.c_str());
        
		auto failurePop = Pop::create();
        failurePop->setContentM(vm["NotRight"].asString().c_str(),48);
		addChild(failurePop,10,"failurePop");
			
	}
	
	
}

void IdiomPioneer::coins(Ref* pSender)
{
    
    auto purchasePop = PopP::create();
    addChild(purchasePop,10,"purchasePop");
}

void IdiomPioneer::setup(Ref* pSender)
{
    
    //auto *setup = Setup::createScene();
	//Director::sharedDirector()->replaceScene(TransitionPageTurn ::create(1.0f , setup,false));
    
    string fullPlistPath = FileUtils::sharedFileUtils()->fullPathForFilename("my.plist");
    FileUtils *fu = FileUtils::getInstance();
    ValueMap vm = fu->getValueMapFromFile(fullPlistPath.c_str());
    
    int wealthDedu;
    if(level.compare("1")==0){wealthDedu = grade*10;}
    if(level.compare("2")==0){wealthDedu = grade*20;}
    if(level.compare("3")==0){wealthDedu = grade*30;}
    auto pop = PopM::create();
    pop->setContentM((vm["SetupSkip"].asString()+String::createWithFormat("%d",wealthDedu)->_string).c_str(),42);
    pop->setMenuM(wealthDedu,"SetupSkip");
    addChild(pop,10,"pop");
    

}

void IdiomPioneer::tip(Ref* pSender)
{
    string fullPlistPath = FileUtils::sharedFileUtils()->fullPathForFilename("my.plist");
	FileUtils *fu = FileUtils::getInstance();
	ValueMap vm = fu->getValueMapFromFile(fullPlistPath.c_str());

	int wealthDedu;
	if(level.compare("1")==0){wealthDedu = grade*10;}
	if(level.compare("2")==0){wealthDedu = grade*20;}
	if(level.compare("3")==0){wealthDedu = grade*30;}
    auto pop = PopM::create();
	pop->setContentM((vm["Tip"].asString()+String::createWithFormat("%d",wealthDedu)->_string).c_str(),42);
	pop->setMenuM(wealthDedu,"Tip");
	addChild(pop,10,"pop");




}

void IdiomPioneer::remove(Ref* pSender)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    clearCardSpriteAll(visibleSize);

}

void IdiomPioneer::answer(Ref* pSender)
{
    string fullPlistPath = FileUtils::sharedFileUtils()->fullPathForFilename("my.plist");
	FileUtils *fu = FileUtils::getInstance();
	ValueMap vm = fu->getValueMapFromFile(fullPlistPath.c_str());

	int wealthDedu;
	if(level.compare("1")==0){wealthDedu = 4*grade*10;}
	if(level.compare("2")==0){wealthDedu = 4*grade*20;}
	if(level.compare("3")==0){wealthDedu = 4*grade*30;}
    auto pop = PopM::create();
	pop->setContentM((vm["Answer"].asString()+String::createWithFormat("%d",wealthDedu)->_string).c_str(),42);
	pop->setMenuM(wealthDedu,"Answer");
	addChild(pop,10,"pop");


}

void IdiomPioneer::skip(Ref* pSender)
{
    string fullPlistPath = FileUtils::sharedFileUtils()->fullPathForFilename("my.plist");
	FileUtils *fu = FileUtils::getInstance();
	ValueMap vm = fu->getValueMapFromFile(fullPlistPath.c_str());

	int wealthDedu;
	if(level.compare("1")==0){wealthDedu = grade*10;}
	if(level.compare("2")==0){wealthDedu = grade*20;}
	if(level.compare("3")==0){wealthDedu = grade*30;}
    auto pop = PopM::create();
	pop->setContentM((vm["Skip"].asString()+String::createWithFormat("%d",wealthDedu)->_string).c_str(),42);
	pop->setMenuM(wealthDedu,"Skip");
	addChild(pop,10,"pop");


}

void IdiomPioneer::sound(Ref *pSender, CheckBoxEventType eventtype)
{
    switch (eventtype)
    {
            
        case CheckBoxEventType::CHECKBOX_STATE_EVENT_SELECTED:
            UserDefault::sharedUserDefault()->setIntegerForKey("sound",1);
            break;
        case CheckBoxEventType::CHECKBOX_STATE_EVENT_UNSELECTED:
            UserDefault::sharedUserDefault()->setIntegerForKey("sound",0);
            break;
        default:
            break;
    }
    
}

void IdiomPioneer::clearCardSpriteAll(cocos2d::Size mySize){
    
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
                    addChild(cardSprite);
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
                    addChild(cardSprite);
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
                    addChild(cardSprite);
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




int loadRecord(void *para,int n_column,char **column_value,char **column_name){

	CCLOG("ID=%s,IDIOM=%s",column_value[0],column_value[1]);
	idiomArray[idiomArrayPosition] = column_value[1];
	thisLevel = (string)column_value[3];
	return 0;
}

int loadRecordConfirm(void *para,int n_column,char **column_value,char **column_name){
    
    CCLOG("ID=%s,IDIOM=%s",column_value[0],column_value[1]);
    idiomArrayConfirm[0] = column_value[1];
    return 0;
}



void bubbleSort(string arr[], int n){
	for(int i = 0;i < n;i++){  
		for(int j = 0;j < n-i-1;j++){  
            //if(strcmp(arr[j].c_str(),arr[j+1].c_str())>0){  
			if(arr[j].compare(arr[j+1])>0){  
                string t = arr[j];  
                arr[j] = arr[j+1];  
                arr[j+1] = t;  
            }  
        }  
    }       
}
