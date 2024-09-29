## 화면 전환

</br>

이전에 생성한 2개의 화면 클래스를 가지고 화면 전환에 대해서 알아보자.

화면을 전환하는 방법은 replaceScene()을 사용하는 방법과 pushScene(), popScene()을 사용하는 방법이 존재한다.

</br>

### 4.2.1 replaceScene()

replaceScene()은 화면을 전환할 때 **새로운 화면을 생성해서 화면을 전환**하고 **이전의 화면은 메모리에서 해제**된다.

즉, A 화면에서 B 화면으로 전환할 때 B 화면 클래스로 화면 전환이 완료되면 A 화면 클래스는 메모리에서 해제된다.

또한 다시 A 화면 클래스로 화면 전환을 하면, A 화면 클래스를 다시 메모리에 생성하며, 생성이 완료되면 B 화면 클래스는 메모리에서 해제된다.

</br>

이와 같이 사용하지 않는 화면 클래스는 메모리에서 해제되기 때문에 **메모리 효율성은 좋다**.

하지만 이전의 화면 클래스를 매번 해제하기 때문에 **직전의 화면 상태가 유지되지 않고 새롭게 생성된 화면 상태**로 보여진다.

</br>

> Director::getInstance()->replaceScene(scene);

replaceScene()을 사용하려면 위 코드와 같이 **전환하려고 하는 scene을 매개변수로 입력**해주면 된다.

일반적으로 **Scene은 우리가 만든 화면 클래스에서 createScene() 메소드로 얻을 수 있다**.

</br>

#### MenuScene.h

```C++
#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class MenuScene : public Layer
{
public:
    static Scene* createScene();

    virtual bool init();
    CREATE_FUNC(MenuScene);

    void changeScene(Ref* sender);
};

#endif
```

</br>

#### MenuScene.cpp

```C++
#include "MenuScene.h"
#include "GameScene.h"

...

bool MenuScene::init()
{
    if (!Layer::init())
        return false;

    auto label = Label::createWithTTF("GAME START", "PFStarDustS.ttf", 34);

    auto item = MenuItemLabel::create(label, CC_CALLBACK_1(MenuScene::changeScene, this));
    
auto menu = Menu::create(item, NULL);
    menu->alignItemsVertically();
    this->addChild(menu);

    return true;
}

void MenuScene::changeScene(Ref* sender)
{
    Director::getInstance()->replaceScene(GameScene::createScene());
}
```
</br>

#### GameScene.h

</br>

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

	void changeScene(Ref* sender);
};

#endif
```
</br>

#### GameScene.cpp

</br>

```C++
#include "GameScene.h"
#include "MenuScene.h"

...

bool GameScene::init()
{
	if (!Layer::init())
		return false;

	auto label = Label::createWithTTF("Back to Title", "PFStarDustS.ttf", 34);

	auto item = MenuItemLabel::create(label, CC_CALLBACK_1(GameScene::changeScene, this));

	auto menu = Menu::create(item, NULL);
	menu->alignItemsVertically();
	this->addChild(menu);

	return true;
}

void GameScene::changeScene(Ref* sender)
{
	Director::getInstance()->replaceScene(MenuScene::createScene());
}
```
</br>

</br>
</br>

### 4.2.2 pushScene(), popScene()

pushScene()과 popScene()은 이름에서 알 수 있듯이 **스택 구조로 화면을 전환하는 방식**이다.

</br>

pushScene()은 매개변수로 새로운 화면 클래스를 받으며, **pushScene()을 실행하면 매개변수로 받은 화면으로 전환**된다.

하지만 이 때 이전에 있었던 화면 클래스는 **화면에서만 보이지 않을 뿐 메모리에서는 해제되지 않는다**.

</br>

popScene()은 따로 매개변수를 받지 않고, 지금 **화면에 보이는 화면의 클래스를 메모리에서 해제**한다.

그러면 직전에 보였었던 화면 클래스가 자동으로 화면에 보여진다.

이렇게 화면에 보여질 때는 **직전의 화면 상태가 그대로 유지된 채로 다시 화면에 보여진다**.

</br>

</br>

```C++
void MenuScene::changeScene(Ref* sender)
{
    Director::getInstance()->pushScene(GameScene::createScene());
}

void GameScene::changeScene(Ref* sender)
{
    Director::getInstance()->popScene();
}
```
</br>