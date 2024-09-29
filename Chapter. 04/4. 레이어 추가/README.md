## 레이어 추가

</br>

화면 클래스가 아닌 새로운 레이어 클래스를 만들고 화면 클래스에 추가해보자.

</br>

#### MenuLayer.h

```C++
#ifndef __MENU_LAYER_H__
#define __MENU_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class MenuLayer : public Layer
{
public:
    virtual bool init();
    CREATE_FUNC(MenuLayer);
};

#endif
```
</br>

#### MenuLayer.cpp

```C++
#include "MenuLayer.h"

bool MenuLayer::init()
{
    if(!Layer::init())
        return false;

    return true;
}
```
</br>

그리고 이렇게 만든 MenuLayer 클래스를 HelloWorld 클래스에 추가해보자.

</br>

#### HelloWorld.cpp

```C++
#include "HelloWorldScene.h"
#include "MenuLayer.h"

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();

    auto layer = HelloWorld::createScene();
    scene->addChild(layer);

    return scene;
}

bool HelloWorld::init()
{
    if(!Layer::init())
        return false;

    CCLOG("HelloWorld::init()");

    auto layer = MenuLayer::create();
    this->addChild(layer);

    return true;
}
```
</br>

새로 만든 레이어 클래스는 일반적인 객체를 추가하는 것과 같이 **create()로 생성해서 addChild()로 추가**하면 된다.