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

    // 랜덤 값 생성을 위한 기준 값을 현재 시간으로 초기화
    srand(time(NULL));
}

void GameScene::InitSmile()
{
    // 화면 내부에서 랜덤하게 생성되도록, rand() 사용
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
        // 스마일의 크기가 0.25보다 작다면 메모리를 해제하고, 그렇지 않다면 2배 축소
        if (smile_sprite->getScale() <= 0.25)
            this->removeChild(smile_sprite);
        else
            smile_sprite->setScale(smile_sprite->getScale() / 2);
    }

    return true;
}
```
</br>

![화면 캡처 2024-10-05 121830](https://github.com/user-attachments/assets/8e5461d0-7235-45cf-8bd8-0e3bb6892157)

</br>

위의 코드에서는 출력된 이미지가 1개라서 태그 값으로 간단하게 이미지의 영역을 가져와서 충돌 체크를 했다.

하지만, **이미지의 개수가 여러 개라면 태그 값으로 이미지의 영역을 가져오는 것이 조금 복잡**해진다.

그리고 태그 값이 아닌 **스프라이트 배열을 사용**해서 구현할 경우에도 스프라이트의 개수가 정적이면 상관없지만, **동적이면 배열을 사용하는 것도 불편**하다.
