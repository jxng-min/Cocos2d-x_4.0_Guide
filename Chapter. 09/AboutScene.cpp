#include "AboutScene.h"

Scene* AboutScene::createScene()
{
	auto scene = Scene::create();

	auto layer = AboutScene::create();
	scene->addChild(layer);

	return scene;
}

bool AboutScene::init()
{
	if (!Layer::init())
		return false;

    InitData();
    InitBackground();
    InitAboutMenu();

	return true;
}

void AboutScene::InitData()
{
    m_win_size = Director::getInstance()->getWinSize();
}

void AboutScene::InitBackground()
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

void AboutScene::InitAboutMenu()
{
    auto menu_layer = Layer::create();
    this->addChild(menu_layer);

    auto about_title_label = Label::createWithTTF("ABOUT", "StarDust.ttf", 50);
    about_title_label->setColor(Color3B::BLACK);
    about_title_label->setPosition(Point(m_win_size.width / 2, m_win_size.height - 30));
    menu_layer->addChild(about_title_label);

    auto back_label = Label::createWithTTF("BACK", "StarDust.ttf", 25);
    back_label->setColor(Color3B::BLACK);
    
    auto back_item = MenuItemLabel::create(back_label, CC_CALLBACK_1(AboutScene::MenuCallback, this));
    back_item->setTag(TAG_ITEM_BACK);

    auto about_menu = Menu::create(back_item, NULL);
    about_menu->setPosition(Point(m_win_size.width - 50, m_win_size.height - 30));
    about_menu->alignItemsVertically();
    menu_layer->addChild(about_menu);

    auto about_main_label = Label::createWithTTF("This game is for Cocos2d-x practice.", "StarDust.ttf", 25);
    about_main_label->setColor(Color3B::BLACK);
    about_main_label->setAnchorPoint(Point::ZERO);
    about_main_label->setPosition(Point(20, m_win_size.height / 2 + 30));
    menu_layer->addChild(about_main_label);

    auto about_github_label = Label::createWithTTF("Github: jxng-min", "StarDust.ttf", 20);
    about_github_label->setColor(Color3B::BLACK);
    about_github_label->setAnchorPoint(Point::ZERO);
    about_github_label->setPosition(Point(m_win_size.width - 160, 10));
    menu_layer->addChild(about_github_label);
}

void AboutScene::MenuCallback(Ref* sender)
{
    auto item = (MenuItemLabel*)sender;

    switch (item->getTag())
    {
    case TAG_ITEM_BACK:
        Director::getInstance()->popScene();
        break;
    }
}