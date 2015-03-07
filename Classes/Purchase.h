#ifndef __PURCHASE_H__
#define __PURCHASE_H__

#include "cocos2d.h"
#include "cocos-ext.h"

class PopP : public cocos2d::LayerColor
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
   

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
	
    // implement the "static create()" method manually
    CREATE_FUNC(PopP);
	void cancel(Ref* pSender);
    void consumble801(Ref* pSender,int perID);
    void consumble101(Ref* pSender,int perID);

};

#endif // __PURCHASE_H__
