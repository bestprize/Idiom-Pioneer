#ifndef __GAMEOVER_SCENE_H__
#define __GAMEOVER_SCENE_H__

#include "cocos2d.h"

class GameOver : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void restart(Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameOver);
    void coins(Ref* pSender);
    void setup(Ref* pSender);
};

#endif // __GAMEOVER_SCENE_H__
