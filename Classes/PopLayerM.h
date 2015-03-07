#ifndef __POPLAYERM_H__
#define __POPLAYERM_H__

#include "cocos2d.h"
#include "cocos-ext.h"

class PopM : public cocos2d::LayerColor
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
   

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
	
	bool onTouchBegan(cocos2d::Touch *touch,cocos2d::Event *unused_event);
    // implement the "static create()" method manually
    CREATE_FUNC(PopM);
	void menuCloseCallbackYes(Ref* pSender,int wealthDedu);
	void menuCloseCallbackYesTip(Ref* pSender,int wealthDedu);
	void menuCloseCallbackYesRemove(Ref* pSender,int wealthDedu);
	void menuCloseCallbackYesAnswer(Ref* pSender,int wealthDedu);
	void menuCloseCallbackYesSkip(Ref* pSender,int wealthDedu);
    void menuCloseCallbackYesSetupSkip(Ref* pSender,int wealthDedu);
	void menuCloseCallbackNo(Ref* pSender);
	void setContentM( const char* content, int fontsize );
	void setMenuM(int wealthDedu,std::string func);
	void clearCardSpriteAll(cocos2d::Size mySize);

};

#endif // __POPLAYERM_H__
