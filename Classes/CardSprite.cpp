#include "CardSprite.h"





CardSprite* CardSprite::createCardSprite(int grade,String *myCharacter,int width,int height,float cardSpriteX,float cardSpriteY,int chooseFlag){

	auto enemy = new CardSprite();
	if(enemy && enemy->init()){
		enemy->autorelease();
		enemy->enemyInit(grade,myCharacter,width,height,cardSpriteX,cardSpriteY,chooseFlag);
		return enemy;
	}
	CC_SAFE_DELETE(enemy);
	return NULL;
}




bool CardSprite::init(){

	if(!Sprite::init()){
		return false;
	}

	

	

	


	return true;
}





String *CardSprite::getCharacter(){

	return this->character;

}

void CardSprite::setCharacter(String *myCharacter){

	character = myCharacter;
	labelTTFCharacter->setString(character->getCString());
	
}





void CardSprite::enemyInit(int grade,String *myCharacter,int width,int height,float cardSpriteX,float cardSpriteY,int chooseFlag){

	if(chooseFlag == 0){
		//layerBGColorCharacter = LayerColor::create(Color4B(130,57,53,255),width-4,height-4);
		layerBGColorCharacter = LayerColor::create(Color4B(40,67,122,255),width-4,height-4);
	} else if(chooseFlag == 1){
		//layerBGColorCharacter = LayerColor::create(Color4B(3,22,52,255),width-4,height-4);
        layerBGColorCharacter = LayerColor::create(Color4B(3,22,52,255),width-4,height-4);
	}
	layerBGColorCharacter->setPosition(Vec2(cardSpriteX,cardSpriteY));
	log("%s-width:%d;cardSpriteX:%f;cardSpriteY:%f;x:%f-%f,y:%f-%f",myCharacter->getCString(),width,cardSpriteX,cardSpriteY,cardSpriteX,cardSpriteX+width-4,cardSpriteY,cardSpriteY+width-4);

	labelTTFCharacter = LabelTTF::create(myCharacter->getCString(),"¿¬Ìå",layerBGColorCharacter->getContentSize().width*0.8);
	labelTTFCharacter->setPosition(layerBGColorCharacter->getContentSize().width/2,layerBGColorCharacter->getContentSize().height/2);
    if(chooseFlag == 0){
        labelTTFCharacter->setColor(Color3B(255,255,255));
    } else if(chooseFlag == 1){
        labelTTFCharacter->setColor(Color3B(255,255,255));
    }
	layerBGColorCharacter->addChild(labelTTFCharacter);

	this->addChild(layerBGColorCharacter);

}

