#include "MenuScene.h"

Scene* MenuScene::createScene()
{
    auto scene = Scene::create();

    auto layer = MenuScene::create();
    scene->addChild(layer);

    return scene;
}

bool MenuScene::init()
{
    if (!Layer::init())
        return false;

    InitData();
    InitBackground();
    InitTitleMenu();

    return true;
}

void MenuScene::InitData()
{
    m_win_size = Director::getInstance()->getWinSize();
}

void MenuScene::InitBackground()
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

void MenuScene::InitTitleMenu()
{
    auto menu_layer = Layer::create();
    this->addChild(menu_layer);

    auto title_label = Label::createWithTTF("COCOS JUMP GAME", "StarDust.ttf", 40);
    title_label->setColor(Color3B::BLACK);
    title_label->setPosition(Point(m_win_size.width / 2, m_win_size.height / 2 + 50));
    menu_layer->addChild(title_label);

    auto start_label = Label::createWithTTF("START", "StarDust.ttf", 25);
    start_label->setColor(Color3B::BLACK);

    auto about_label = Label::createWithTTF("ABOUT", "StarDust.ttf", 25);
    about_label->setColor(Color3B::BLACK);

    auto quit_label = Label::createWithTTF("QUIT", "StarDust.ttf", 25);
    quit_label->setColor(Color3B::BLACK);

    auto start_item = MenuItemLabel::create(start_label, CC_CALLBACK_1(MenuScene::MenuCallback, this));
    start_item->setTag(TAG_MENU_START);

    auto about_item = MenuItemLabel::create(about_label, CC_CALLBACK_1(MenuScene::MenuCallback, this));
    about_item->setTag(TAG_MENU_ABOUT);

    auto quit_item = MenuItemLabel::create(quit_label, CC_CALLBACK_1(MenuScene::MenuCallback, this));
    quit_item->setTag(TAG_MENU_QUIT);

    auto title_menu = Menu::create(start_item, about_item, quit_item, NULL);
    title_menu->alignItemsVerticallyWithPadding(20);
    title_menu->setPosition(Point(m_win_size.width / 2, m_win_size.height / 2 - 70));
    menu_layer->addChild(title_menu);
}

void MenuScene::MenuCallback(Ref* sender)
{
    auto menu_item = (MenuItemLabel*)sender;

    switch (menu_item->getTag())
    {
    case TAG_MENU_START:
        Director::getInstance()->replaceScene(GameScene::createScene());
        break;

    case TAG_MENU_ABOUT:
        Director::getInstance()->pushScene(AboutScene::createScene());
        break;

    case TAG_MENU_QUIT:
        exit(1);
    }
}