/****************************************************************************
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "CardSprite.h"
#include "StartGame.h"

USING_NS_CC;
using namespace std;

Scene* StartGame::createScene()
{
	auto scene = Scene::create();
	auto layer = HelloWorld::create();
	scene->addChild(layer);
	return scene;
}

bool StartGame::init()
{

	if (!Scene::init())
	{
		return false;
	}

	//��ʼ������Ϊ0
	score = 0;

	auto visibleSize = Director::getInstance()->getVisibleSize();

	//������Ϸ����
	auto bg = Sprite::create("bg7.jpg");
	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 180));
	this->addChild(bg);

	//���Ϸ�������Ϸ�ķ���
	auto labTTFCardNumberName = LabelTTF::create("Score", "arial.ttf", 100);
	labTTFCardNumberName->setPosition(Point(visibleSize.width / 5 + 50, visibleSize.height - 230));
	addChild(labTTFCardNumberName);

	labTTFCardNumber = LabelTTF::create("0", "arial.ttf", 100);
	labTTFCardNumber->setPosition(Point(visibleSize.width / 2 + 200, visibleSize.height - 230));
	addChild(labTTFCardNumber);


	//������Ϸ������ʶ������¼������а�
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(StartGame::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(StartGame::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	//�������ɿ�Ƭ�ķ���
	createCardSprite(visibleSize);

	//�������������
	autoCreateCardNumber();
	autoCreateCardNumber();

	return true;
}

//��������ʶ����¼�
bool StartGame::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * unused_event)
{
	Point touchP0 = touch->getLocation();

	firstX = touchP0.x;
	firstY = touchP0.y;

	return true;
}

void StartGame::onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * unused_event)
{
	//��ȡX���Y����ƶ���Χ
	Point touchP0 = touch->getLocation();
	endX = firstX - touchP0.x;
	endY = firstY - touchP0.y;

	//�ж�X���Y����ƶ����룬���X�ľ���ֵ��Y��ľ���ֵ��Ļ��������ң����������»���
	if (abs(endX) > abs(endY)) {
		//����
		if (endX + 5 > 0) {
			//���
			if (doleft()) {
				//�������������
				autoCreateCardNumber();
				doCheckGameOver();
			}
		}
		else {
			//�ұ�
			if (doright()) {
				//�������������
				autoCreateCardNumber();
				doCheckGameOver();
			}
		}
	}
	else {
		//����
		if (endY + 5 > 0) {
			//�±�
			if (dodown()) {
				//�������������
				autoCreateCardNumber();
				doCheckGameOver();
			}
		}
		else {
			//�ϱ�
			if (doup()) {
				//�������������
				autoCreateCardNumber();
				doCheckGameOver();
			}
		}
	}
}

bool StartGame::doleft()
{
	log("doleft");
	bool isdo = false;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			for (int x1 = x + 1; x1 < 4; x1++)
			{
				if (cardArr[x1][y]->getNumber() > 0)
				{
					if (cardArr[x][y]->getNumber() <= 0)
					{
						cardArr[x][y]->setNumber(cardArr[x1][y]->getNumber());
						cardArr[x1][y]->setNumber(0);
						x--;
						isdo = true;
					}
					else if (cardArr[x][y]->getNumber() == cardArr[x1][y]->getNumber())
					{
						cardArr[x][y]->setNumber(cardArr[x][y]->getNumber() * 2);
						cardArr[x1][y]->setNumber(0);

						//���÷���
						score += cardArr[x][y]->getNumber();
						labTTFCardNumber->setString(__String::createWithFormat("%i", score)->getCString());

						isdo = true;
					}
					break;
				}
			}
		}
	}
	return isdo;
}

bool StartGame::doright()
{
	log("doringht");
	bool isdo = false;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 3; x >= 0; x--)
		{
			for (int x1 = x - 1; x1 >= 0; x1--)
			{
				if (cardArr[x1][y]->getNumber() > 0)
				{
					if (cardArr[x][y]->getNumber() <= 0)
					{
						cardArr[x][y]->setNumber(cardArr[x1][y]->getNumber());
						cardArr[x1][y]->setNumber(0);
						x++;
						isdo = true;
					}
					else if (cardArr[x][y]->getNumber() == cardArr[x1][y]->getNumber())
					{
						cardArr[x][y]->setNumber(cardArr[x][y]->getNumber() * 2);
						cardArr[x1][y]->setNumber(0);

						//���÷���
						score += cardArr[x][y]->getNumber();
						labTTFCardNumber->setString(__String::createWithFormat("%i", score)->getCString());

						isdo = true;
					}
					break;
				}
			}
		}
	}
	return isdo;
}

bool StartGame::doup()
{
	log("doup");
	bool isdo = false;
	for (int x = 0; x < 4; x++)
	{
		for (int y = 3; y >= 0; y--)
		{
			for (int y1 = y - 1; y1 >= 0; y1--)
			{
				if (cardArr[x][y1]->getNumber() > 0)
				{
					if (cardArr[x][y]->getNumber() <= 0)
					{
						cardArr[x][y]->setNumber(cardArr[x][y1]->getNumber());
						cardArr[x][y1]->setNumber(0);
						y++;
						isdo = true;
					}
					else if (cardArr[x][y]->getNumber() == cardArr[x][y1]->getNumber())
					{
						cardArr[x][y]->setNumber(cardArr[x][y]->getNumber() * 2);
						cardArr[x][y1]->setNumber(0);

						//���÷���
						score += cardArr[x][y]->getNumber();
						labTTFCardNumber->setString(__String::createWithFormat("%i", score)->getCString());

						isdo = true;
					}
					break;
				}
			}
		}
	}
	return isdo;
}

bool StartGame::dodown()
{
	log("dodown");
	bool isdo = false;
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			for (int y1 = y + 1; y1 < 4; y1++)
			{
				if (cardArr[x][y1]->getNumber() > 0)
				{
					if (cardArr[x][y]->getNumber() <= 0)
					{
						cardArr[x][y]->setNumber(cardArr[x][y1]->getNumber());
						cardArr[x][y1]->setNumber(0);
						y--;
						isdo = true;
					}
					else if (cardArr[x][y]->getNumber() == cardArr[x][y1]->getNumber())
					{
						cardArr[x][y]->setNumber(cardArr[x][y]->getNumber() * 2);
						cardArr[x][y1]->setNumber(0);

						//���÷���
						score += cardArr[x][y]->getNumber();
						labTTFCardNumber->setString(__String::createWithFormat("%i", score)->getCString());

						isdo = true;
					}
					break;
				}
			}
		}
	}
	return isdo;
}

//�ж���Ϸ�Ƿ��ܼ���������ȥ
void StartGame::doCheckGameOver()
{
	bool isGameOver = true;
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			if (cardArr[x][y]->getNumber() == 0 ||
				(x > 0 && (cardArr[x][y]->getNumber() == cardArr[x - 1][y]->getNumber())) ||
				(x < 3 && (cardArr[x][y]->getNumber() == cardArr[x + 1][y]->getNumber())) ||
				(y > 0 && (cardArr[x][y]->getNumber() == cardArr[x][y - 1]->getNumber())) ||
				(y < 3 && (cardArr[x][y]->getNumber() == cardArr[x][y + 1]->getNumber()))) {
				isGameOver = false;
			}
		}
	}
	if (isGameOver) {
		//������Ϸ
		Director::getInstance()->replaceScene(TransitionFade::create(1, HelloWorld::createScene()));
	}
}

//�Զ����ɿ�Ƭ
void StartGame::autoCreateCardNumber()
{
	int i = CCRANDOM_0_1() * 4;
	int j = CCRANDOM_0_1() * 4;

	//�ж��Ƿ����Ѿ����ڵ�λ��
	if (cardArr[i][j]->getNumber() > 0) {
		autoCreateCardNumber();
	}
	else {
		cardArr[i][j]->setNumber(CCRANDOM_0_1() * 10 < 1 ? 4 : 2);
	}
}

//������Ƭ
void StartGame::createCardSprite(cocos2d::Size size)
{
	//�����Ԫ��Ŀ�Ⱥ͸߶�
	int lon = (size.width - 28) / 4;

	//4*4�ĵ�Ԫ��
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			CardSprite *card = CardSprite::createCardSprite(0, lon, lon, lon*j + 20, lon*i + 20 + size.height / 6);
			addChild(card);

			//��ӿ�Ƭ��������
			cardArr[j][i] = card;
		}
	}
}


