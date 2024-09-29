## 충돌 체크

</br>

충돌 체크란 2개 이상의 객체가 화면상에서 서로 겹쳐졌는지를 확인하는 것이다.

충돌 체크는 일반적으로 객체들 간의 충돌뿐만 아니라 화면의 터치를 확인하는 모든 경우에도 사용된다.

</br>

### 5.2.1 containsPoint

충돌 체크를 하기 위해서는 일단 주체가 되는 영역이 필요하다.

그리고 그 영역에 어떤 포인트가 교차되었는지를 확인 하는 메소드가 containsPoint()이다.

containsPoint()는 게임에서 **화면의 특정 영역을 올바르게 터치했는지를 확인**한다.

</br>

```C++
auto rect = Rect(0, 0, 100, 100);
auto point = Point(50, 50);

if(rect.containsPoint(point))
{
    // 지정된 영역에 포인트가 포함되어 있는 경우
}
```
</br>

containsPoint()를 사용하려면 **Rect와 point의 값이 필요**하다.

**Rect의 영역에 Point의 값이 포함되면 containsPoint()는 true를 반환**하며, 포함하지 않으면 false를 반환한다.

</br>
</br>

### 5.2.2 intersectsRect

**두 영역의 충돌 체크**를 할 때는 intersectsRect()를 사용한다. **가장 일반적으로 영역의 충돌 여부를 체크할 때 사용**하는 메소드다.

</br>

```C++
auto rect_1 = Rect(0, 0, 100, 100);
auto rect_2 = Rect(50, 50, 200, 200);

if(rect_1.intersectsRect(rect_2))
{
    // 두 영역이 겹쳐져 있는 경우
}
```
</br>

intersectsRect()를 사용하려면 **Rect의 값이 2개 필요**하다.

**한 Rect의 영역이 다른 Rect의 영역에 겹쳐지면 intersectsRect()는 true를 반환**하며, 겹쳐지지 않으면 false를 반환한다.

</br>
</br>

### 5.2.3 터치 이벤트와 충돌 체크

</br>

화면에 아이콘 이미지를 출력하고 아이콘 이미지를 클릭하면 아이콘의 크기를 확대하도록 해보자.

</br>

#### GameScene.h

```C++
#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class GameScene : public Layer
{
public:
    static Scene* createScene();

    virtual bool init();
    CREATE_FUNC(GameScene);

    virtual bool onTouchBegan(Touch* touch, Event* unused_event);
};

#endif
```
</br>

#### GameScene.cpp

```C++
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
    if(!Layer::init())
        return false;

    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);

    auto sprite = Sprite::create("HelloWorld.png");
    sprite->setPosition(Point(100, 100));
    sprite->setTag(1);
    this->addChild(sprite);

    return true;
}

bool GameScene::onTouchBegan(Touch* touch, Event* unused_event)
{
    Point touch_point = touch->getLocation();

    auto sprite = (Sprite*)this->getChildByTag(1);
    auto rect = sprite->getBoundingBox();           // 객체가 화면에 보이는 영역을 반환

    if(rect.containsPoint(touch_point))
        sprite->setScale(2.0);
    else
        sprite->setScale(1.0);

    return true;
}
```
</br>

![화면 캡처 2024-09-29 191448](https://github.com/user-attachments/assets/495ec74f-589a-4316-915f-d3ff0697f945)
