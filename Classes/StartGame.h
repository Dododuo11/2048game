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

	//��������ʶ����¼�
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);

	//�������ҵķ���
	bool doleft();
	bool doright();
	bool doup();
	bool dodown();
	//�Զ����ɿ�Ƭ
	void autoCreateCardNumber();
	//��Ϸ�Ƿ��ܼ���������ȥ
	void doCheckGameOver();

private:
	//�����Ԫ��
	int firstX, firstY, endX, endY;
	//����һ����ά����
	CardSprite *cardArr[4][4];
	//������Ƭ
	void createCardSprite(cocos2d::Size size);

	//�������
	int score;
	//������ʾ���ݵĿؼ�
	cocos2d::LabelTTF *labTTFCardNumber;
};

#endif // __STARTGAME_H__
