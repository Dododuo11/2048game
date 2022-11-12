#include "HelloWorldScene.h"
#include "StartGame.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	return HelloWorld::create();
}

bool HelloWorld::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	//±³¾°
	auto bg = Sprite::create("bg4.jpg");
	bg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(bg);

	//²Ëµ¥
	MenuItemFont::setFontName("Times New Roan");
	MenuItemFont::setFontSize(110);
	MenuItemFont *startmenu = MenuItemFont::create("Start", CC_CALLBACK_1(HelloWorld::menuGoCallBack, this));
	startmenu->setColor(Color3B::ORANGE);
	auto menu = Menu::create(startmenu, NULL);
	menu->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(menu);

	return true;
}

void HelloWorld::menuGoCallBack(cocos2d::Ref * pSender)
{
	auto scene = StartGame::create();
	auto tsc = TransitionCrossFade::create(1.0f, scene);
	Director::getInstance()->replaceScene(tsc);
}