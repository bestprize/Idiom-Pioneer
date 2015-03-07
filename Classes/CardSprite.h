#ifndef __IDIOMPIONEER_CARDSPRITE
#define __IDIOMPIONEER_CARDSPRITE

#include "cocos2d.h"


USING_NS_CC;

class CardSprite:public Sprite {

public:
	static CardSprite* createCardSprite(int grade,String *myCharacter,int width,int height,float cardSpriteX,float cardSpriteY,int chooseFlag);
	virtual bool init();
	CREATE_FUNC(CardSprite);

	void setCharacter(String *myCharacter);
	String *getCharacter();



private:

	String *character;
	void enemyInit(int grade,String *myCharacter,int width,int height,float cardSpriteX,float cardSpriteY,int chooseFlag);
	LabelTTF *labelTTFCharacter;
	LayerColor *layerBGColorCharacter;
	

};



#endif // __IDIOMPIONEER_CARDSPRITE