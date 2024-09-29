## 화면 생성

</br>

우선 사용해왔던 실습용 프로젝트 기본형을 가지고 새로운 화면을 만들어보자.

기존의 HelloWorld.h와 HelloWorld.cpp의 파일명을 아래와 같이 정리하면 된다.

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
};

#endif
```
</br>

</br>

#### MenuScene.cpp

```C++
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

    return true;
}
```
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
public:
	static Scene* createScene();

	virtual bool init();
	CREATE_FUNC(GameScene);
};

#endif
```
</br>

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
	if (!Layer::init())
		return false;

	return true;
}
```
</br>

</br>

#### AppDelegate.cpp

```C++
#include "MenuScene.h"                          // HelloWorldScene.h에서 MenuScene.h로 수정한다.

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) 
    {
        glview = GLViewImpl::createWithRect("test2", cocos2d::Rect(0, 0, 480, 320));
        director->setOpenGLView(glview);
    }

    director->setDisplayStats(true);
    director->setAnimationInterval(1.0f / 60);

    auto scene = MenuScene::createScene();      // HelloWorld::createScene()에서 MenuScene::createScene()으로 수정한다.

    director->runWithScene(scene);

    return true;
}
```
</br>