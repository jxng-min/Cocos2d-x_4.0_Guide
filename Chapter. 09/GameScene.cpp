#include "GameScene.h"

Scene* GameScene::createScene()
{
	auto scene = Scene::create();

	auto layer = Layer::create();
	scene->addChild(layer);

	return scene;
}

bool GameScene::init()
{
	if (!Layer::init())
		return false;

    InitData();
    InitBackground();
    InitScoreGUI();

	return true;
}

void GameScene::InitData()
{
	m_win_size = Director::getInstance()->getWinSize();
	m_score = 0.0f;
}

void GameScene::InitBackground()
{
    auto background_node = ParallaxNode::create();
    this->addChild(background_node);

    auto move_action = MoveBy::create(20.0, Point(-2000, 0));
    auto place_action = Place::create(Point::ZERO);
    auto sequence_action = Sequence::create(move_action, place_action, NULL);
    auto repeat_action = RepeatForever::create(sequence_action);
    background_node->runAction(repeat_action);

    auto background_sprite1 = Sprite::create("bg1.png");
    background_sprite1->setAnchorPoint(Point::ZERO);
    background_node->addChild(background_sprite1, 0, Point(1, 0), Point::ZERO);

    auto background_sprite2 = Sprite::create("bg1.png", Rect(0, 0, 480, 320));
    background_sprite2->setAnchorPoint(Point::ZERO);
    background_node->addChild(background_sprite2, 0, Point(1, 0), Point(2000, 0));

    auto background_sprite3 = Sprite::create("bg2.png");
    background_sprite3->setAnchorPoint(Point::ZERO);
    background_node->addChild(background_sprite3, 1, Point(2, 0), Point::ZERO);

    auto background_sprite4 = Sprite::create("bg2.png");
    background_sprite4->setAnchorPoint(Point::ZERO);
    background_node->addChild(background_sprite4, 1, Point(2, 0), Point(2000, 0));

    auto background_sprite5 = Sprite::create("bg2.png", Rect(0, 0, 480, 114));
    background_sprite5->setAnchorPoint(Point::ZERO);
    background_node->addChild(background_sprite5, 1, Point(2, 0), Point(4000, 0));
}

void GameScene::InitScoreGUI()
{
    auto score_label = Label::createWithTTF("", "StarDust.ttf", 35);
    score_label->setPosition(Point(m_win_size.width - 30, m_win_size.height - 15));
    this->addChild(score_label);
}