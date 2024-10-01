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

    InitBackground();
    InitMenu();

    return true;
}


void MenuScene::InitBackground()
{
    auto menu_background_sprite = Sprite::create("game/game-bg.png");
    menu_background_sprite->setPosition(Point(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2));
    menu_background_sprite->setScale(1.5);
    this->addChild(menu_background_sprite);
}

void MenuScene::InitMenu()
{
    auto play_label = Label::createWithTTF("PLAY", "PFStarDustS.ttf", 15);
    auto help_label = Label::createWithTTF("HELP", "PFStarDustS.ttf", 15);
    auto option_label = Label::createWithTTF("OPTION", "PFStarDustS.ttf", 15);
    auto quit_label = Label::createWithTTF("QUIT", "PFStarDustS.ttf", 15);

    play_label->setColor(Color3B::BLACK);
    help_label->setColor(Color3B::BLACK);
    option_label->setColor(Color3B::BLACK);
    quit_label->setColor(Color3B::BLACK);

    auto play_item = MenuItemLabel::create(play_label, CC_CALLBACK_1(MenuScene::MenuCallback, this));
    auto help_item = MenuItemLabel::create(help_label, CC_CALLBACK_1(MenuScene::MenuCallback, this));
    auto option_item = MenuItemLabel::create(option_label, CC_CALLBACK_1(MenuScene::MenuCallback, this));
    auto quit_item = MenuItemLabel::create(quit_label, CC_CALLBACK_1(MenuScene::MenuCallback, this));

    play_item->setTag(TAG_MENUITEM_PLAY);
    help_item->setTag(TAG_MENUITEM_HELP);
    option_item->setTag(TAG_MENUITEM_OPTION);
    quit_item->setTag(TAG_MENUITEM_QUIT);

    auto title_menu = Menu::create(play_item, help_item, option_item, quit_item, NULL);
    title_menu->alignItemsVerticallyWithPadding(20);
    this->addChild(title_menu);
}

void MenuScene::MenuCallback(Ref* sender)
{
    auto item = (MenuItem*)sender;
    auto game_scene = TransitionFadeTR::create(1.0, GameScene::createScene());

    switch (item->getTag())
    {
    case TAG_MENUITEM_PLAY:
        Director::getInstance()->replaceScene(game_scene);
        break;

    case TAG_MENUITEM_HELP:
        break;

    case TAG_MENUITEM_OPTION:
        break;

    case TAG_MENUITEM_QUIT:
        Director::getInstance()->end();
        break;

    default:
        break;
    }
}