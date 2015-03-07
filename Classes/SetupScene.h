#ifndef __SETUP_SCENE_H__
#define __SETUP_SCENE_H__

#include "cocos2d.h"


USING_NS_CC;


class Setup : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void backToMain(Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(Setup);

private:

	MenuItemImage *levelCheckBox1;
	MenuItemImage *levelCheckBox2;
	MenuItemImage *levelCheckBox3;
	void levelButton1(Object * obj);
	void levelButton2(Object * obj);
	void levelButton3(Object * obj);

	MenuItemImage *gradeCheckBox3;
	MenuItemImage *gradeCheckBox4;
	MenuItemImage *gradeCheckBox5;
	MenuItemImage *gradeCheckBox6;
	MenuItemImage *gradeCheckBox7;
	MenuItemImage *gradeCheckBox8;
	MenuItemImage *gradeCheckBox9;
	MenuItemImage *gradeCheckBox10;
	void gradeButton3(Object * obj);
	void gradeButton4(Object * obj);
	void gradeButton5(Object * obj);
	void gradeButton6(Object * obj);
	void gradeButton7(Object * obj);
	void gradeButton8(Object * obj);
	void gradeButton9(Object * obj);
	void gradeButton10(Object * obj);



};

#endif // __SETUP_SCENE_H__
