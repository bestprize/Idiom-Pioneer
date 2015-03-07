#ifndef __IDIOMPIONEER_SCENE_H__
#define __IDIOMPIONEER_SCENE_H__

#include "cocos2d.h"
#include "CardSprite.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include <iostream>
#include <cmath>
#include <string> 
#include <sstream>

using namespace std;

extern string idiomArray[25];
extern int idiomArrayPosition;

extern string thisLevel;
extern string rightAnswerStr;

extern int rightAnswerPositionOnFinalOrderX[16];
extern int rightAnswerPositionOnFinalOrderY[16];

extern	string rightAnswer[16];
extern	int rightAnswerLength;

extern	int characterChooseStatus[50];
extern	string characterChoosedArray[50];
extern	int characterChoosedTotal;

extern	string characterArray[50];
extern	int characterArrayPosition;


class IdiomPioneer : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
     // implement the "static create()" method manually
    CREATE_FUNC(IdiomPioneer);

	virtual bool onTouchBegan(cocos2d::Touch *touch,cocos2d::Event *unused_event);
	//virtual void onTouchEnded(cocos2d::Touch *touch,cocos2d::Event *unused_event);
	void confirm(cocos2d::Ref* pSender);
    void coins(Ref* pSender);
	void setup(Ref* pSender);
	void tip(Ref* pSender);
	void remove(Ref* pSender);
	void answer(Ref* pSender);
	void skip(Ref* pSender);
	void createCardSpriteAll(cocos2d::Size mySize);
    void clearCardSpriteAll(cocos2d::Size mySize);
    void sound(Ref *pSender, cocos2d::ui::CheckBoxEventType eventtype);
    
private:

	string level;
	int grade;

	int touchedX,touchedY;



};

int loadRecord(void *para,int n_column,char **column_value,char **column_name);
int loadRecordConfirm(void *para,int n_column,char **column_value,char **column_name);
void bubbleSort(string arr[], int n);

#endif // __IDIOMPIONEER_SCENE_H__
