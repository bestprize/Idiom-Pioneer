#include "SetupScene.h"
#include "IdiomPioneerScene.h"




Scene* Setup::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Setup::create();

    // add layer as a child to scene
    scene->addChild(layer,10,"layer");

	auto backGroundLayer = LayerColor::create(Color4B(13,64,83,255));
	scene->addChild(backGroundLayer,0,"backGroundLayer");
    
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    auto sprite = Sprite::create("back.png");
    sprite->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    
    float x = visibleSize.width/(sprite->getContentSize().width);
    float y = visibleSize.height/(sprite->getContentSize().height);
    auto scaleTo = ScaleTo::create(0.0f, x>=y?x:y);
    sprite->runAction(scaleTo);
    scene->addChild(sprite, 1);
    


    UserDefault::sharedUserDefault()->setIntegerForKey("sceneFlag",2);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Setup::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();

	string fullPlistPath = FileUtils::sharedFileUtils()->fullPathForFilename("my.plist");
	FileUtils *fu = FileUtils::getInstance();
	ValueMap vm = fu->getValueMapFromFile(fullPlistPath.c_str());
	string Continue = vm["Continue"].asString().c_str();
	
	auto levelLabel = LabelTTF::create(vm["Level"].asString().c_str(), "Georgia", 48);
    levelLabel->setPosition(visibleSize.width/2, visibleSize.height-150);
    this->addChild(levelLabel, 1);

	auto levelLabel1 = LabelTTF::create(vm["Level1"].asString().c_str(), "Georgia", 32);
    levelLabel1->setPosition(visibleSize.width*2/6, visibleSize.height-224);
    this->addChild(levelLabel1, 1);

	auto levelLabel2 = LabelTTF::create(vm["Level2"].asString().c_str(), "Georgia", 32);
    levelLabel2->setPosition(visibleSize.width*3/6, visibleSize.height-224);
    this->addChild(levelLabel2, 1);

	auto levelLabel3 = LabelTTF::create(vm["Level3"].asString().c_str(), "Georgia", 32);
    levelLabel3->setPosition(visibleSize.width*4/6, visibleSize.height-224);
    this->addChild(levelLabel3, 1);

	levelCheckBox1 = MenuItemImage::create("off_48.png","on_48.png",this,menu_selector(Setup::levelButton1));
	levelCheckBox2 = MenuItemImage::create("off_48.png","on_48.png",this,menu_selector(Setup::levelButton2));
	levelCheckBox3 = MenuItemImage::create("off_48.png","on_48.png",this,menu_selector(Setup::levelButton3));
	Menu * levelMenu = Menu::create(levelCheckBox1,levelCheckBox2,levelCheckBox3,NULL);
	levelMenu->alignItemsHorizontallyWithPadding(58);
	levelMenu->setPosition(ccp(visibleSize.width/2,visibleSize.height-269));
	string level = UserDefault::sharedUserDefault()->getStringForKey("level","1");
	if(level.compare("1")==0){levelCheckBox1->selected();}
	if(level.compare("2")==0){levelCheckBox2->selected();}
	if(level.compare("3")==0){levelCheckBox3->selected();}
	this->addChild(levelMenu);

	auto gradeLabel = LabelTTF::create(vm["Grade"].asString().c_str(), "Georgia", 48);
    gradeLabel->setPosition(visibleSize.width/2, visibleSize.height-410);
    this->addChild(gradeLabel, 1);

	auto gradeLabel3 = LabelTTF::create(vm["Grade3"].asString().c_str(), "Georgia", 32);
    gradeLabel3->setPosition(visibleSize.width/6, visibleSize.height-484);
    this->addChild(gradeLabel3, 1);

	auto gradeLabel4 = LabelTTF::create(vm["Grade4"].asString().c_str(), "Georgia", 32);
    gradeLabel4->setPosition(visibleSize.width*2/6, visibleSize.height-484);
    this->addChild(gradeLabel4, 1);

	auto gradeLabel5 = LabelTTF::create(vm["Grade5"].asString().c_str(), "Georgia", 32);
    gradeLabel5->setPosition(visibleSize.width*3/6, visibleSize.height-484);
    this->addChild(gradeLabel5, 1);

	auto gradeLabel6 = LabelTTF::create(vm["Grade6"].asString().c_str(), "Georgia", 32);
    gradeLabel6->setPosition(visibleSize.width*4/6, visibleSize.height-484);
    this->addChild(gradeLabel6, 1);

	auto gradeLabel7 = LabelTTF::create(vm["Grade7"].asString().c_str(), "Georgia", 32);
    gradeLabel7->setPosition(visibleSize.width*5/6, visibleSize.height-484);
    this->addChild(gradeLabel7, 1);

	gradeCheckBox3 = MenuItemImage::create("off_48.png","on_48.png",this,menu_selector(Setup::gradeButton3));
    gradeCheckBox4 = MenuItemImage::create("off_48.png","on_48.png",this,menu_selector(Setup::gradeButton3));
    gradeCheckBox4 = MenuItemImage::create("off_48.png","on_48.png",this,menu_selector(Setup::gradeButton4));
	gradeCheckBox5 = MenuItemImage::create("off_48.png","on_48.png",this,menu_selector(Setup::gradeButton5));
	gradeCheckBox6 = MenuItemImage::create("off_48.png","on_48.png",this,menu_selector(Setup::gradeButton6));
	gradeCheckBox7 = MenuItemImage::create("off_48.png","on_48.png",this,menu_selector(Setup::gradeButton7));
	Menu * gradeMenu = Menu::create(gradeCheckBox3,gradeCheckBox4,gradeCheckBox5,gradeCheckBox6,gradeCheckBox7,gradeCheckBox8,gradeCheckBox9,gradeCheckBox10,NULL);
	gradeMenu->alignItemsHorizontallyWithPadding(58);
	gradeMenu->setPosition(ccp(visibleSize.width/2,visibleSize.height-529));
	int grade = UserDefault::sharedUserDefault()->getIntegerForKey("grade",3);
	if(grade==3){gradeCheckBox3->selected();}
	if(grade==4){gradeCheckBox4->selected();}
	if(grade==5){gradeCheckBox5->selected();}
	if(grade==6){gradeCheckBox6->selected();}
	if(grade==7){gradeCheckBox7->selected();}
	this->addChild(gradeMenu);

    auto returnItem = MenuItemImage::create(
                                           "home_48.png",
                                           "home_96.png",
                                           CC_CALLBACK_1(Setup::backToMain, this));
    
    returnItem->setPosition(Vec2(visibleSize.width/2 ,
                                 visibleSize.height/4));
    
    // create menu, it's an autorelease object
    auto returnMenu = Menu::create(returnItem, NULL);
    returnMenu->setPosition(Vec2::ZERO);
    this->addChild(returnMenu, 1);







    return true;
}



void Setup::levelButton1(Object * obj)
{
	levelCheckBox1->selected();
	levelCheckBox2->unselected();
	levelCheckBox3->unselected();
	UserDefault::sharedUserDefault()->setStringForKey("level","1");
}

void Setup::levelButton2(Object * obj)
{
	levelCheckBox2->selected();
	levelCheckBox1->unselected();
	levelCheckBox3->unselected();
	UserDefault::sharedUserDefault()->setStringForKey("level","2");
}
void Setup::levelButton3(Object * obj)
{
	levelCheckBox3->selected();
	levelCheckBox1->unselected();
	levelCheckBox2->unselected();
	UserDefault::sharedUserDefault()->setStringForKey("level","3");
}

void Setup::gradeButton3(Object * obj)
{
	gradeCheckBox3->selected();
	gradeCheckBox4->unselected();
	gradeCheckBox5->unselected();
	gradeCheckBox6->unselected();
	gradeCheckBox7->unselected();
	UserDefault::sharedUserDefault()->setIntegerForKey("grade",3);
}

void Setup::gradeButton4(Object * obj)
{
	gradeCheckBox4->selected();
	gradeCheckBox3->unselected();
	gradeCheckBox5->unselected();
	gradeCheckBox6->unselected();
	gradeCheckBox7->unselected();
	UserDefault::sharedUserDefault()->setIntegerForKey("grade",4);
}

void Setup::gradeButton5(Object * obj)
{
	gradeCheckBox5->selected();
	gradeCheckBox4->unselected();
	gradeCheckBox3->unselected();
	gradeCheckBox6->unselected();
	gradeCheckBox7->unselected();
	UserDefault::sharedUserDefault()->setIntegerForKey("grade",5);
}

void Setup::gradeButton6(Object * obj)
{
	gradeCheckBox6->selected();
	gradeCheckBox4->unselected();
	gradeCheckBox5->unselected();
	gradeCheckBox3->unselected();
	gradeCheckBox7->unselected();
	UserDefault::sharedUserDefault()->setIntegerForKey("grade",6);
}

void Setup::gradeButton7(Object * obj)
{
	gradeCheckBox7->selected();
	gradeCheckBox4->unselected();
	gradeCheckBox5->unselected();
	gradeCheckBox6->unselected();
	gradeCheckBox3->unselected();
	UserDefault::sharedUserDefault()->setIntegerForKey("grade",7);
}

void Setup::backToMain(Ref* pSender)
{
    
	log("-------------------------------------------------start--------------------------------------");
    auto *idiomPioneer = IdiomPioneer::createScene();
    //float t = 3.0f;

	Director::sharedDirector()->replaceScene(TransitionPageTurn ::create(1.0f , idiomPioneer,false));
	//Director::sharedDirector()->replaceScene(idiomPioneer);
}

