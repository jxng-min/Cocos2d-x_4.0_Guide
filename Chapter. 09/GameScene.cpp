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

    InitData();
    InitBackground();
    InitGUI();
    InitPlayer();

    this->schedule(CC_SCHEDULE_SELECTOR(GameScene::InitObstacle), 5.0);
    this->scheduleUpdate();

    return true;
}

void GameScene::InitData()
{
    m_win_size = Director::getInstance()->getWinSize();
    m_score = 0.0;
    m_player_is_jump = false;
    m_is_stop = false;

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("man.plist");
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

void GameScene::InitGUI()
{
    auto score_label = Label::createWithTTF("", "StarDust.ttf", 20);
    score_label->setPosition(Point(m_win_size.width - 60, m_win_size.height - 15));
    score_label->setColor(Color3B::BLACK);
    score_label->setTag(TAG_LABEL_SCORE);
    this->addChild(score_label);

    InitScoreGUI();
    InitGameOverGUI();
}

void GameScene::InitScoreGUI()
{
    auto score_label = (Label*)this->getChildByTag(TAG_LABEL_SCORE);
    score_label->setString(StringUtils::format("Score : %03d", static_cast<int>(m_score * 100)));
}

void GameScene::InitGameOverGUI()
{
    auto game_over_layer = Layer::create();
    game_over_layer->setVisible(false);
    game_over_layer->setTag(TAG_LAYER_GAMEOVER);
    this->addChild(game_over_layer, 1);

    auto layer_title_label = Label::createWithTTF("GAME OVER", "StarDust.ttf", 40);
    layer_title_label->setColor(Color3B::BLACK);
    layer_title_label->setPosition(Point(m_win_size.width / 2, m_win_size.height / 2 + 50));
    game_over_layer->addChild(layer_title_label);

    auto retry_label = Label::createWithTTF("RETRY", "StarDust.ttf", 25);
    retry_label->setColor(Color3B::BLACK);

    auto title_label = Label::createWithTTF("TITLE", "StarDust.ttf", 25);
    title_label->setColor(Color3B::BLACK);

    auto retry_item = MenuItemLabel::create(retry_label, CC_CALLBACK_1(GameScene::MenuCallback, this));
    retry_item->setTag(TAG_ITEM_RETRY);

    auto title_item = MenuItemLabel::create(title_label, CC_CALLBACK_1(GameScene::MenuCallback, this));
    title_item->setTag(TAG_ITEM_TITLE);

    auto menu = Menu::create(retry_item, title_item, NULL);
    menu->alignItemsVerticallyWithPadding(20);
    menu->setPosition(Point(m_win_size.width / 2, m_win_size.height / 2 - 50));
    game_over_layer->addChild(menu);
}

void GameScene::InitPlayer()
{
    auto player_sprite = Sprite::createWithSpriteFrameName("man_0.png");
    player_sprite->setAnchorPoint(Point(0.5, 0));
    player_sprite->setPosition(Point(m_win_size.width / 2 - 50, 50));
    player_sprite->setTag(TAG_SPRITE_PLAYER);
    this->addChild(player_sprite);

    InitPlayerAnimation();
}

void GameScene::InitPlayerAnimation()
{
    auto player_sprite = (Sprite*)this->getChildByTag(TAG_SPRITE_PLAYER);

    auto player_animation = Animation::create();
    player_animation->setDelayPerUnit(0.2);

    for (auto i = 0; i < 4; i++)
    {
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("man_%d.png", i));
        player_animation->addSpriteFrame(frame);
    }

    auto player_animate = Animate::create(player_animation);
    auto player_repeat_animate = RepeatForever::create(player_animate);
    player_sprite->runAction(player_repeat_animate);
}

void GameScene::PlayerJump()
{
    if (!m_player_is_jump)
    {
        m_player_is_jump = true;

        auto player_sprite = (Sprite*)this->getChildByTag(TAG_SPRITE_PLAYER);

        auto jump_action = Sequence::create(
                                                JumpBy::create(0.75, Point::ZERO, 110, 1),
                                                CallFunc::create(CC_CALLBACK_0(GameScene::PlayerJumpReset, this)),
                                                NULL);
        
        player_sprite->runAction(jump_action);
    }
}

void GameScene::PlayerJumpReset()
{
    m_player_is_jump = false;
}

void GameScene::InitObstacle(float delta)
{
    auto obstacle_sprite = Sprite::create("block.png");
    obstacle_sprite->setAnchorPoint(Point(0.5, 0));
    obstacle_sprite->setScale(0.7);
    obstacle_sprite->setPosition(Point(m_win_size.width + 50, 50));
    obstacle_sprite->setTag(TAG_SPRITE_OBSTACLE);
    this->addChild(obstacle_sprite);

    InitObstacleAnimation();
}

void GameScene::InitObstacleAnimation()
{
    auto obstacle_sprite = (Sprite*)this->getChildByTag(TAG_SPRITE_OBSTACLE);

    auto move_action = Sequence::create(
                                            MoveBy::create(2.0, Point(-600, 0)),
                                            RemoveSelf::create(),
                                            NULL);

    obstacle_sprite->runAction(move_action);
}

bool GameScene::onTouchBegan(Touch* touch, Event* unused_event)
{
    PlayerJump();

    return true;
}

void GameScene::update(float delta)
{
    m_score += 0.001;
    InitScoreGUI();

    if (this->getChildByTag(TAG_SPRITE_OBSTACLE) != NULL)
    {
        auto player_sprite = (Sprite*)this->getChildByTag(TAG_SPRITE_PLAYER);
        auto player_rect = Rect(player_sprite->getPositionX() - 5, player_sprite->getPositionY(), 10, player_sprite->getContentSize().height);

        auto obstacle_sprite = (Sprite*)this->getChildByTag(TAG_SPRITE_OBSTACLE);
        auto obstacle_rect = obstacle_sprite->getBoundingBox();

        if (player_rect.intersectsRect(obstacle_rect))
        {
            auto game_over_layer = (Layer*)this->getChildByTag(TAG_LAYER_GAMEOVER);
            game_over_layer->setVisible(true);

            Director::getInstance()->pause();
            m_is_stop = true;
        }
    }
}

void GameScene::InitGame()
{
    if (m_is_stop)
    {
        auto obstacle_sprite = (Sprite*)this->getChildByTag(TAG_SPRITE_OBSTACLE);
        this->removeChild(obstacle_sprite);

        Director::getInstance()->resume();
        InitData();

        auto game_over_layer = (Layer*)this->getChildByTag(TAG_LAYER_GAMEOVER);
        game_over_layer->setVisible(false);
    }
}

void GameScene::MenuCallback(Ref* sender)
{
    auto menu_item = (MenuItemLabel*)sender;

    switch (menu_item->getTag())
    {
    case TAG_ITEM_RETRY:
        InitGame();
        break;

    case TAG_ITEM_TITLE:
        InitGame();
        Director::getInstance()->replaceScene(MenuScene::createScene());
        break;
    }
}