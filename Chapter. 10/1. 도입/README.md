## 도입

</br>

게임 데이터를 관리하는 방법을 알아보기 위해 예제를 먼저 생성하도록 하겠다.

* 게임 이름: 스마일 게임
* 게임 방법: 화면에 나타난 스마일 이미지를 터치해서 없애기

</br>
</br>

#### GameScene.h

```C++
#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class GameScene : public Layer
{
private:
    Size m_win_size;

public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    CREATE_FUNC(GameScene);

    void InitData();
    void InitSmile();

    virtual bool onTouchBegan(Touch* touch, Event* unused_event);
};

#endif
```
</br>
</br>

#### GameScene.cpp

```C++
#include "GameScene.h"

...

bool GameScene::init()
{
    if (!Layer::init())
        return false;

    InitData();     // 변수 초기화 메소드
    InitSmile();    // 스마일 스프라이트 생성 메소드

    return true;
}

void GameScene::InitData()
{
    m_win_size = Director::getInstance()->getWinSize();

    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);

    // 랜덤 값 생성을 위함
    srand(time(NULL));
}

void GameScene::InitSmile()
{
    auto x = rand() % static_cast<int>(m_win_size.width);
    auto y = rand() % static_cast<int>(m_win_size.height);

    auto smile_sprite = Sprite::create("Pea.png");
    smile_sprite->setPosition(Point(x, y));
    smile_sprite->setTag(1);
    this->addChild(smile_sprite);
}

bool GameScene::onTouchBegan(Touch* touch, Event* unused_event)
{
    auto location = touch->getLocation();

    auto smile_sprite = this->getChildByTag(1);
    auto smile_rect = smile_sprite->getBoundingBox();

    if (smile_rect.containsPoint(location))
    {
        if (smile_sprite->getScale() <= 0.25)
            this->removeChild(smile_sprite);
        else
            smile_sprite->setScale(smile_sprite->getScale() / 2);
    }

    return true;
}
```
</br>