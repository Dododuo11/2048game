#ifndef __STARTGAME_H__
#define __STARTGAME_H__

#include "cocos2d.h"
#include "CardSprite.h"

class StartGame : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(StartGame);

	//加入手势识别的事件
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);

	//上下左右的方法
	bool doleft();
	bool doright();
	bool doup();
	bool dodown();
	//自动生成卡片
	void autoCreateCardNumber();
	//游戏是否还能继续运行下去
	void doCheckGameOver();

private:
	//点击的元素
	int firstX, firstY, endX, endY;
	//定义一个二维数组
	CardSprite *cardArr[4][4];
	//创建卡片
	void createCardSprite(cocos2d::Size size);

	//整体分数
	int score;
	//定义显示数据的控件
	cocos2d::LabelTTF *labTTFCardNumber;
};

#endif // __STARTGAME_H__
