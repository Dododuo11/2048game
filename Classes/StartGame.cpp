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

	//初始化分数为0
	score = 0;

	auto visibleSize = Director::getInstance()->getVisibleSize();

	//加入游戏背景
	auto bg = Sprite::create("bg7.jpg");
	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 180));
	this->addChild(bg);

	//在上方加入游戏的分数
	auto labTTFCardNumberName = LabelTTF::create("Score", "arial.ttf", 100);
	labTTFCardNumberName->setPosition(Point(visibleSize.width / 5 + 50, visibleSize.height - 230));
	addChild(labTTFCardNumberName);

	labTTFCardNumber = LabelTTF::create("0", "arial.ttf", 100);
	labTTFCardNumber->setPosition(Point(visibleSize.width / 2 + 200, visibleSize.height - 230));
	addChild(labTTFCardNumber);


	//加入游戏的手势识别监听事件，进行绑定
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(StartGame::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(StartGame::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	//调用生成卡片的方法
	createCardSprite(visibleSize);

	//调用生成随机数
	autoCreateCardNumber();
	autoCreateCardNumber();

	return true;
}

//加入手势识别的事件
bool StartGame::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * unused_event)
{
	Point touchP0 = touch->getLocation();

	firstX = touchP0.x;
	firstY = touchP0.y;

	return true;
}

void StartGame::onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * unused_event)
{
	//获取X轴和Y轴的移动范围
	Point touchP0 = touch->getLocation();
	endX = firstX - touchP0.x;
	endY = firstY - touchP0.y;

	//判断X轴和Y轴的移动距离，如果X的绝对值比Y轴的绝对值大的话就是左右，否则是上下滑动
	if (abs(endX) > abs(endY)) {
		//左右
		if (endX + 5 > 0) {
			//左边
			if (doleft()) {
				//调用生成随机数
				autoCreateCardNumber();
				doCheckGameOver();
			}
		}
		else {
			//右边
			if (doright()) {
				//调用生成随机数
				autoCreateCardNumber();
				doCheckGameOver();
			}
		}
	}
	else {
		//上下
		if (endY + 5 > 0) {
			//下边
			if (dodown()) {
				//调用生成随机数
				autoCreateCardNumber();
				doCheckGameOver();
			}
		}
		else {
			//上边
			if (doup()) {
				//调用生成随机数
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

						//设置分数
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

						//设置分数
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

						//设置分数
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

						//设置分数
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

//判断游戏是否还能继续运行下去
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
		//结束游戏
		Director::getInstance()->replaceScene(TransitionFade::create(1, HelloWorld::createScene()));
	}
}

//自动生成卡片
void StartGame::autoCreateCardNumber()
{
	int i = CCRANDOM_0_1() * 4;
	int j = CCRANDOM_0_1() * 4;

	//判断是否是已经存在的位置
	if (cardArr[i][j]->getNumber() > 0) {
		autoCreateCardNumber();
	}
	else {
		cardArr[i][j]->setNumber(CCRANDOM_0_1() * 10 < 1 ? 4 : 2);
	}
}

//创建卡片
void StartGame::createCardSprite(cocos2d::Size size)
{
	//求出单元格的宽度和高度
	int lon = (size.width - 28) / 4;

	//4*4的单元格
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			CardSprite *card = CardSprite::createCardSprite(0, lon, lon, lon*j + 20, lon*i + 20 + size.height / 6);
			addChild(card);

			//添加卡片到数组中
			cardArr[j][i] = card;
		}
	}
}


