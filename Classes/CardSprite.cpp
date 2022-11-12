#include "CardSprite.h"

USING_NS_CC;

//初始化游戏卡片的方法
CardSprite * CardSprite::createCardSprite(int numbers, int wight, int height, float CardSpriteX, float CardSpriteY)
{
	CardSprite *enemy = new CardSprite();
	if (enemy && enemy->init())
	{
		enemy->autorelease();
		enemy->enemyInit(numbers, wight, height, CardSpriteX, CardSpriteY);

		return enemy;
	}
	CC_SAFE_DELETE(enemy);
	return NULL;
}

bool CardSprite::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	return true;
}

//设置数字
void CardSprite::setNumber(int num)
{
	number = num;

	//根据数字的大小来调整字体的大小
	if (number >= 0)
	{
		labTTFCardNumber->setFontSize(100);
	}
	if (number >= 16)
	{
		labTTFCardNumber->setFontSize(90);
	}
	if (number >= 128)
	{
		labTTFCardNumber->setFontSize(60);
	}
	if (number >= 1024)
	{
		labTTFCardNumber->setFontSize(40);
	}

	//根据数字的大小来调整颜色
	if (number == 0){
		layerColorBg->setColor(cocos2d::Color3B(200, 190, 180));
	}
	if (number == 2) {
		layerColorBg->setColor(cocos2d::Color3B(240, 230, 220));
	}
	if (number == 4) {
		layerColorBg->setColor(cocos2d::Color3B(240, 220, 200));
	}
	if (number == 8) {
		layerColorBg->setColor(cocos2d::Color3B(240, 180, 120));
	}
	if (number == 16) {
		layerColorBg->setColor(cocos2d::Color3B(240, 140, 90));
	}
	if (number == 32) {
		layerColorBg->setColor(cocos2d::Color3B(240, 120, 90));
	}
	if (number == 64) {
		layerColorBg->setColor(cocos2d::Color3B(240, 90, 60));
	}
	if (number == 128) {
		layerColorBg->setColor(cocos2d::Color3B(240, 90, 60));
	}
	if (number == 256) {
		layerColorBg->setColor(cocos2d::Color3B(240, 200, 70));
	}
	if (number == 512) {
		layerColorBg->setColor(cocos2d::Color3B(240, 200, 70));
	}
	if (number == 1024) {
		layerColorBg->setColor(cocos2d::Color3B(0, 130, 0));
	}
	if (number == 2048) {
		layerColorBg->setColor(cocos2d::Color3B(0, 130, 0));
	}

	//更新显示的数字
	if (number > 0)
	{
		labTTFCardNumber->setString(__String::createWithFormat("%i", number)->getCString());
	}
	else
	{
		labTTFCardNumber->setString("");
	}
}

//获取数字
int CardSprite::getNumber()
{
	return number;
}

void CardSprite::enemyInit(int numbers, int wight, int height, float CardSpriteX, float CardSpriteY)
{
	//初始化数字
	number = numbers;
	//加入游戏卡片的背景颜色
	layerColorBg = cocos2d::LayerColor::create(cocos2d::Color4B(255, 228, 196, 200), wight - 15, height - 15);
	layerColorBg->setPosition(Point(CardSpriteX, CardSpriteY));

	//判断如果不等于0就显示，否则为空
	if (number > 0)
	{//加入中间字体
		labTTFCardNumber = cocos2d::LabelTTF::create(__String::createWithFormat("%i", number)->getCString(), "HirakakuProN-W6", 100);
		labTTFCardNumber->setPosition(Point(layerColorBg->getContentSize().width / 2, layerColorBg->getContentSize().height / 2));
		layerColorBg->addChild(labTTFCardNumber);
	}
	else
	{//加入中间字体
		labTTFCardNumber = cocos2d::LabelTTF::create("", "HirakakuProN-W6", 100);
		labTTFCardNumber->setPosition(Point(layerColorBg->getContentSize().width / 2, layerColorBg->getContentSize().height / 2));
		layerColorBg->addChild(labTTFCardNumber);
	}
	this->addChild(layerColorBg);
}
