#include "GameScene.h"

Scene* GameScene::createScene()
{
	auto scene = Scene::create();

	auto layer = GameScene::create();
	scene->addChild(layer);

	return scene;
}

bool GameScene::init()
{
	if (!Layer::init())
		return false;

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);

	m_is_touch = false;

	InitGameData();
	InitBackground();
	InitTopMenuLabel();
	InitCard();

	InitReady();
	InitStart();

	InitO();
	InitX();

	InitGameClear();
	InitGameOver();

	InitMenu();

	ActionReady();

	return true;
}

void GameScene::InitGameData()
{
	m_win_size = Director::getInstance()->getWinSize();

	m_card_ok = 0;
	m_life = 3;

	srand(time(NULL));

	for (auto i = 0; i < 4; i++)
		m_card[i] = rand() % 6;

	m_count_card = 0;
}

void GameScene::InitBackground()
{
	auto background_sprite = Sprite::create("game/game-bg.png");
	background_sprite->setPosition(Point(m_win_size.width / 2, m_win_size.height / 2));
	background_sprite->setScale(1.5);
	this->addChild(background_sprite);
}

void GameScene::InitTopMenuLabel()
{
	auto card_label = Label::createWithTTF("", "PFStarDustS.ttf", 15);
	card_label->setAnchorPoint(Point(0, 1));
	card_label->setPosition(Point(140, m_win_size.height - 10));
	card_label->setTag(TAG_LABEL_CARD);
	card_label->setColor(Color3B::BLACK);
	this->addChild(card_label);

	auto life_label = Label::createWithTTF("", "PFStarDustS.ttf", 15);
	life_label->setAnchorPoint(Point(1, 1));
	life_label->setPosition(Point(m_win_size.width - 140, m_win_size.height - 10));
	life_label->setTag(TAG_LABEL_LIFE);
	life_label->setColor(Color3B::BLACK);
	this->addChild(life_label);

	SetLabelCard();
	SetLabelLife();
}

void GameScene::InitCard()
{
	for (auto i = 0; i < 6; i++)
	{
		auto card_back_sprite = Sprite::create("game/card-back.png");
		card_back_sprite->setPosition(Point(m_win_size.width / 2 - 45 + 45 * 2 * (i % 2), m_win_size.height / 2 + 90 - 90 * (i / 2)));
		this->addChild(card_back_sprite);

		auto card_front_sprite = Sprite::create(StringUtils::format("game/card_%d.png", (i + 1)));
		card_front_sprite->setPosition(Point(m_win_size.width / 2 - 45 + 45 * 2 * (i % 2), m_win_size.height / 2 + 90 - 90 * (i / 2)));
		card_front_sprite->setVisible(false);
		card_front_sprite->setTag(TAG_SPRITE_CARD + i);
		this->addChild(card_front_sprite);
	}
}

void GameScene::SetLabelCard()
{
	auto label = (Label*)this->getChildByTag(TAG_LABEL_CARD);
	label->setString(StringUtils::format("CARD : %d/4", m_card_ok));
}

void GameScene::SetLabelLife()
{
	auto label = (Label*)this->getChildByTag(TAG_LABEL_LIFE);
	label->setString(StringUtils::format("LIFE : %d", m_life));
}

void GameScene::InitReady()
{
	auto ready_label = Label::createWithTTF("READY", "PFStarDustS.ttf", 45);
	ready_label->setPosition(Point(m_win_size.width / 2, m_win_size.height / 2));
	ready_label->setTag(TAG_LABEL_READY);
	ready_label->setColor(Color3B::BLACK);
	ready_label->setScale(0.0);
	this->addChild(ready_label);
}

void GameScene::InitStart()
{
	auto start_label = Label::createWithTTF("START", "PFStarDustS.ttf", 45);
	start_label->setPosition(Point(m_win_size.width / 2, m_win_size.height / 2));
	start_label->setTag(TAG_LABEL_START);
	start_label->setColor(Color3B::BLACK);
	start_label->setScale(0.0);
	this->addChild(start_label);
}

void GameScene::ActionReady()
{
	auto action = Sequence::create(
									ScaleTo::create(1.0, 1.0),
									DelayTime::create(2.0),
									ScaleTo::create(1.0, 0.0),
									CallFunc::create(CC_CALLBACK_0(GameScene::EndReady, this)),
									NULL);

	auto ready_label = (Label*)this->getChildByTag(TAG_LABEL_READY);
	ready_label->runAction(action);
}

void GameScene::ActionStart()
{
	auto action = Sequence::create(
									ScaleTo::create(1.0, 1.0),
									DelayTime::create(2.0),
									ScaleTo::create(1.0, 0.0),
									CallFunc::create(CC_CALLBACK_0(GameScene::EndStart, this)),
									NULL);

	auto start_label = (Label*)this->getChildByTag(TAG_LABEL_START);
	start_label->runAction(action);
}

void GameScene::EndReady()
{
	ActionStart();
}

void GameScene::EndStart()
{
	ActionCard();
}

void GameScene::ActionCard()
{
	for (auto i = 0; i < 4; i++)
	{
		auto action = Sequence::create(
										DelayTime::create(3.0 * i),
										Show::create(),
										DelayTime::create(2.0),
										Hide::create(),
										NULL);

		auto card_sprite = (Sprite*)this->getChildByTag(TAG_SPRITE_CARD + m_card[i]);
		card_sprite->runAction(action);
	}

	auto action = Sequence::create(
		DelayTime::create(11.0),
		CallFunc::create(CC_CALLBACK_0(GameScene::EndCard, this)),
		NULL);
	this->runAction(action);
}

void GameScene::EndCard()
{
	m_is_touch = true;
}

bool GameScene::onTouchBegan(Touch* touch, Event* unused_event)
{
	if (!m_is_touch)
		return true;

	Point location = touch->getLocation();

	for (auto i = 0; i < 6; i++)
	{
		auto card_sprite = (Sprite*)this->getChildByTag(TAG_SPRITE_CARD + i);
		auto card_sprite_rect = card_sprite->getBoundingBox();

		if (card_sprite_rect.containsPoint(location))
		{
			m_is_touch = false;

			auto action = Sequence::create(
											Show::create(),
											DelayTime::create(0.5),
											Hide::create(),
											NULL);

			card_sprite->runAction(action);

			if (i == m_card[m_count_card])
			{
				m_card_ok++;
				m_count_card++;

				if (m_card_ok == 4)
					ActionGameEnd(true);

				SetLabelCard();
				ActionOX(true);
			}
			else
			{
				m_life--;

				if (m_life == 0)
					ActionGameEnd(false);

				SetLabelLife();
				ActionOX(false);
			}
		}
	}

	return true;
}

void GameScene::InitO()
{
	auto o_sprite = Sprite::create("game/o.png");
	o_sprite->setPosition(Point(m_win_size.width / 2, m_win_size.height / 2));
	o_sprite->setVisible(false);
	o_sprite->setTag(TAG_LABEL_SPRITE_O);
	this->addChild(o_sprite);
}

void GameScene::InitX()
{
	auto x_sprite = Sprite::create("game/x.png");
	x_sprite->setPosition(Point(m_win_size.width / 2, m_win_size.height / 2));
	x_sprite->setVisible(false);
	x_sprite->setTag(TAG_LABEL_SPRITE_O);
	this->addChild(x_sprite);
}

void GameScene::ActionOX(bool is_o)
{
	auto action = Sequence::create(
									Show::create(),
									DelayTime::create(0.5),
									Hide::create(),
									CallFunc::create(CC_CALLBACK_0(GameScene::EndOX, this)),
									NULL);

	Sprite* sprite;

	if (is_o)
		sprite = (Sprite*)this->getChildByTag(TAG_LABEL_SPRITE_O);
	else
		sprite = (Sprite*)this->getChildByTag(TAG_LABEL_SPRITE_X);
	
	sprite->runAction(action);
}

void GameScene::EndOX()
{
	if (!(m_card_ok == 4 || m_life == 0))
		m_is_touch = true;
}

void GameScene::ActionGameEnd(bool is_game_clear)
{
	m_is_touch = false;

	auto action = Sequence::create(
									DelayTime::create(0.5),
									Show::create(),
									EaseBounceOut::create(MoveTo::create(1.0, Point(m_win_size.width / 2, m_win_size.height / 2))),
									DelayTime::create(1.0),
									Hide::create(),
									Place::create(Point(m_win_size.width / 2, m_win_size.height + 50)),
									CallFunc::create(CC_CALLBACK_0(GameScene::EndGameEnd, this)),
									NULL);

	Label* label;

	if (is_game_clear)
		label = (Label*)this->getChildByTag(TAG_LABEL_GAMECLEAR);
	else
		label = (Label*)this->getChildByTag(TAG_LABEL_GAMEOVER);

	label->runAction(action);
}

void GameScene::EndGameEnd()
{
	ActionMenu(true);
}

void GameScene::InitGameClear()
{
	auto clear_label = Label::createWithTTF("GAME CLEAR", "PFStarDustS.ttf", 30);
	clear_label->setPosition(Point(m_win_size.width / 2, m_win_size.height / 2));
	clear_label->setTag(TAG_LABEL_GAMECLEAR);
	clear_label->setColor(Color3B::BLACK);
	clear_label->setVisible(false);
	this->addChild(clear_label);
}

void GameScene::InitGameOver()
{
	auto over_label = Label::createWithTTF("GAME OVER", "PFStarDustS.ttf", 30);
	over_label->setPosition(Point(m_win_size.width / 2, m_win_size.height / 2));
	over_label->setTag(TAG_LABEL_GAMECLEAR);
	over_label->setColor(Color3B::BLACK);
	over_label->setVisible(false);
	this->addChild(over_label);
}

void GameScene::InitMenu()
{
	auto retry_label = Label::createWithTTF("RETRY", "PFStarDustS.ttf", 15);
	auto retry_item = MenuItemLabel::create(retry_label, CC_CALLBACK_1(GameScene::MenuCallback, this));
	retry_item->setTag(0);
	retry_item->setColor(Color3B::BLACK);

	auto title_label = Label::createWithTTF("TITLE", "PFStarDustS.ttf", 15);
	auto title_item = MenuItemLabel::create(title_label, CC_CALLBACK_1(GameScene::MenuCallback, this));
	title_item->setTag(1);
	title_item->setColor(Color3B::BLACK);

	auto menu = Menu::create(retry_item, title_item, NULL);
	menu->alignItemsHorizontallyWithPadding(100);
	menu->setPosition(Point(m_win_size.width / 2, 15));
	menu->setTag(TAG_MENU);
	menu->setVisible(false);
	this->addChild(menu);
}

void GameScene::ActionMenu(bool is_show)
{
	auto menu = (Menu*)this->getChildByTag(TAG_MENU);
	menu->setVisible(is_show);
}

void GameScene::MenuCallback(Ref* sender)
{
	auto item = (MenuItemLabel*)sender;

	if (item->getTag() == 0)
	{
		InitGameData();

		SetLabelCard();
		SetLabelLife();

		ActionMenu(false);
		ActionReady();
	}
	else
		Director::getInstance()->replaceScene(MenuScene::createScene());
}