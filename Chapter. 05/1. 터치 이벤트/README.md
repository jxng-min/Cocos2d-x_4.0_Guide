## 터치 이벤트

</br>

터치 이벤트는 크게 싱글 터치 이벤트와 멀티 터치 이벤트가 있다.

**싱글 터치**는 **가장 마지막에 터치한 위치 정보**만 사용할 수 있다.

반면 **멀티 터치**는 사용자가 동시에 여러 위치를 터치해도 **터치한 위치 정보를 모두 저장**할 수 있다.

</br>
</br>

### 5.1.1 싱글 터치 이벤트

</br>

#### 설정 순서
</br>

```C++
auto listener = EventListenerTouchOneByOne::create();
```
</br>

먼저 **이벤트 리스너 터치를 생성**한다. 싱글터치로 리스너를 생성하려면 **EventListenerTouchOneByOne으로 생성**하면 된다.

</br>
</br>

```C++
listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
```
</br>

화면을 터치할 때 호출되는 메소드를 리스너에 등록한다.

</br>
</br>

```C++
listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
```
</br>

화면을 터치한 상태로 이동할 때 호출되는 메소드를 등록한다.

</br>
</br>

```C++
listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
```
</br>

화면을 터치한 후, 화면에서 터치를 떼었을 때 호출되는 메소드를 등록한다.

</br>
</br>

```C++
listener->onTouchCancelled = CC_CALLBACK_2(HelloWorld::onTouchCancelled, this);
```
</br>

화면을 터치하고 있을 때 예상치 못한 이유로 터치 이벤트가 취소될 경우 호출되는 메소드를 등록한다.

</br>
</br>

```C++
Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);
```
</br>

마지막으로 생성한 **리스너를 이벤트 디스패처에 추가**한다.

또한 리스너를 추가할 때는 **우선순위를 지정**할 수 있다.

지정한 우선순위는 여러 개의 레이어 클래스가 있는 화면을 터치해서 **동시에 여러 개의 터치 이벤트 메소드가 호출되는 경우**에 우선순위의 **숫자가 작은 순으로 메소드를 호출**해준다.

그리고 터치 이벤트가 발생할 때 호출되는 메소드는 **레이어 클래스의 싱글 터치 이벤트 가상 함수를 재정의해서 사용**할 수 있다.

</br>

#### 싱글 터치 이벤트 가상 함수

싱글 터치 이벤트와 관련된 가상 함수는 4개이며, **화면을 터치하는 상황에 따라 해당 메소드가 호출**된다.

**터치 정보는 touch에 저장**되며 unused_event는 기존의 코코스2d-iPhone과의 **호환성을 위해 만든 변수**로 특별한 값이 전달되진 않는다.

</br>

```C++
virtual bool onTouchBegan(Touch* touch, Event* unused_event);           // 화면을 터치할 때 호출
virtual void onTouchMoved(Touch* touch, Event* unused_event);           // 화면을 터치한 상태에서 손을 이동할 때마다 호출
virtual void onTouchEnded(Touch* touch, Event* unused_event);           // 화면을 터치한 후에 손을 뗄 때 호출
virtual void onTouchCancelled(Touch* touch, Event* unused_event);       // 화면을 터치할 때 예외로 인해 터치 이벤트가 취소될 때 호출
```
</br>

터치 관련 메소드 중에서 싱글 터치 이벤트의 **onTouchBegan()만 리턴 값을 가지고 있다**.

만약 리턴 값을 **false로 설정하면** onTouchBegan() 호출 뒤에 **onTouchMoved(), onTouchEnded(), onTouchCancelled()가 호출되지 않는다**.

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

    virtual bool onTouchBegan(Touch* touch, Event* unused_event);       // 예시로 onTouchBegan()만 선언한다.
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

    auto listener = EventListenerTouchOneByOne::create();                                               // 터치 이벤트 리스너를 생성한 후,
    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);                              // 터치 이벤트 리스너에 터치 시작 함수를 등록하고
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);      // 이벤트 디스패처에 터치 이벤트 리스너에 우선순위 1을 매겨 등록한다.

    return true;
}

bool GameScene::onTouchBegan(Touch* touch, Event* unused_event)
{
    CCLOG("onTouchBegan");

    return true;
}
```
</br>

</br>

터치 이벤트를 구현할 때는 단순히 **터치 여부를 체크**하는 것도 중요하지만, **터치한 영역의 좌표가 필요한 경우도 존재**한다.

</br>

```C++
bool GameScene::onTouchBegan(Touch* touch, Event* unused_event)
{
    Point touch_point = touch->getLocation();                               // getLocation(): 터치한 영역의 Point를 반환
    CCLOG("Touch Position = (%lf, %lf)", touch_point.x, touch_point.y);

    return true;
}
```
</br>

</br>
</br>

### 5.1.2 멀티 터치 이벤트

</br>

멀티 터치 이벤트를 사용하는 방법도 싱글 터치와 크게 다르지 않다.

다만 **멀티 터치 리스너를 생성**하기 위해서는 **EventListenerTouchAllAtOnce로 생성**하면 된다.

터치 이벤트가 발생할 때 호출되는 메소드들도 **레이어 클래스의 멀티 터치 이벤트 관련 가상 함수들을 재정의해서 사용**할 수 있다.

</br>

```C++
virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event* unused_event);           // 화면을 터치할 때 호출
virtual void onTouchesMoved(const std::vector<Touch*>& touches, Event* unused_event);           // 화면을 터치한 상태에서 손을 이동할 때마다 호출
virtual void onTouchesEnded(const std::vector<Touch*>& touches, Event* unused_event);           // 화면을 터치한 후에 손을 뗄 때 호출
virtual void onTouchesCancelled(const std::vector<Touch*>& touches, Event* unused_event);       // 화면을 터치할 때 예외로 인해 터치 이벤트가 취소될 때 호출
```
</br>

위와 같이 멀티 터치 이벤트와 관련된 가상 함수도 4개이며, **화면을 터치하는 상황에 따라 해당 메소드가 호출**된다.

멀티 터치 이벤트는 화면을 터치한 후 다시 화면의 다른 영역을 터치하면 onTouchesBegan()이 호출되며 이 때 **터치에 관련된 정보들이 Vector에 차례로 저장**된다.

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

    virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event* unused_event);       // 예시로 onTouchesBegan()만 선언한다.
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

    auto listener = EventListenerTouchAllAtOnce::create();                                              // 터치 이벤트 리스너를 생성한 후,
    listener->onTouchesBegan = CC_CALLBACK_2(GameScene::onTouchesBegan, this);                          // 터치 이벤트 리스너에 터치 시작 함수를 등록하고
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);      // 이벤트 디스패처에 터치 이벤트 리스너에 우선순위 1을 매겨 등록한다.

    return true;
}

void GameScene::onTouchesBegan(const std::vector<Touch*>& touches, Event* unused_event)
{
    CCLOG("onTouchesBegan");
}
```
</br>

멀티 터치 이벤트를 구현할 때는 단순히 **터치 여부와 위치**를 가져오는 것뿐만 아니라 **동시에 터치한 좌표가 필요한 경우도 존재**한다.

</br>

```C++
void GameScene::onTouchesBegan(const std::vector<Touch*>& touches, Event* unused_event)
{
    auto touch_iter = touches.begin();
    Touch* touch;
    auto touch_pos = std::vector<Point>();

    touch_pos.resize(touches.size());

    for(auto i = 0; i < touches.size(); i++)
    {
        touch = (Touch*)(*touch_iter);
        touch_pos[i] = touch->getLocation();
        touch_iter++;

        CCLOG("Touch Position[%d]: (%lf, %lf)", i, touch_pos[i].x, touch_pos[i].y);
    }
}
```
</br>

</br>
</br>

### 5.1.3 iOS에서의 멀티 터치 설정

</br>

안드로이드의 경우 단말기에서 멀티 터치를 사용하기 위해서 특별한 설정을 할 필요가 없다.

하지만, iOS의 경우 관련 소스 코드를 조금 수정해야만 한다.

</br>

#### AppController.mm

```C++
...

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    
    cocos2d::Application *app = cocos2d::Application::getInstance();
    
    app->initGLContextAttrs();
    cocos2d::GLViewImpl::convertAttrs();

    window = [[UIWindow alloc] initWithFrame: [[UIScreen mainScreen] bounds]];

    // AppController.mm에 setMultipleTouchEnabled 메소드를 추가해야 멀티 터치를 사용할 수 있다.
    [eaglView setMultipleTouchEnabled:YES];

    _viewController = [[RootViewController alloc]init];
    _viewController.wantsFullScreenLayout = YES;
    

    if ( [[UIDevice currentDevice].systemVersion floatValue] < 6.0)
    {
        [window addSubview: _viewController.view];
    }
    else
    {
        [window setRootViewController:_viewController];
    }

    [window makeKeyAndVisible];

    [[UIApplication sharedApplication] setStatusBarHidden:true];
    
    if ( [[UIDevice currentDevice].systemVersion floatValue] >= 13.0f)
    {
        [[NSUserDefaults standardUserDefaults] setBool:NO forKey:@"NSAllowsDefaultLineBreakStrategy"];
    }
    
    cocos2d::GLView *glview = cocos2d::GLViewImpl::createWithEAGLView((__bridge void *)_viewController.view);
    cocos2d::Director::getInstance()->setOpenGLView(glview);
    
    app->run();

    return YES;
}

...
```
</br>