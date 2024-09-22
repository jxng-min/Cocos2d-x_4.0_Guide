## 2.2 이미지 출력

</br>

이미지를 화면에 출력하려면 **스프라이트**(Sprite) 이미지 객체를 만들어야 한다.          

스프라이트는 단순히 이미지일 뿐만 아니라 **이미지의 정보(위치, 색상, 투명도 등)도 포함**하는 객체다.

</br>

### 2.2.1 스프라이트 사용

</br>

```C++
bool HelloWorld::init()
{
    if(!Layer::init())
        return false;

    auto sprite = Sprite::create("HelloWorld.png");
    sprite->setAnchorPoint(Point(0.5, 0.5));
    sprite->setPosition(Point(200, 200));
    this->addChild(sprite); 

    return true;
}
```
</br>

> auto sprite = Sprite::create("HelloWorld.png");

코코스2d-x에서 객체를 생성할 때는 C++의 new가 아닌 **create()라는 코코스2d-x의 메소드를 사용해서 생성**한다.

create()를 사용해서 객체를 생성할 경우에는 **메모리 관리를 코코스2d-x 내부에서** 해준다.

 일반적으로 **클래스가 소멸될 때 자동으로 해당 클래스에서 create()로 생성했던 모든 객체를 소멸**시켜준다.

 </br>

 > sprite->setAnchorPoint(Point(0.5, 0.5));

 setAnchorPoint()는 **앵커포인트를 설정해주는 메소드**다.

 스프라이트 **앵커포인트의 기본값은 (0.5, 0.5)**이기 때문에 따로 설정하지 않으면 앵커포인트가 (0.5, 0.5)로 설정된다.

 Point() 뒤에서 자세히 설명하도록 하겠다.

 </br>

> sprite->setPosition(Point(100, 100));

setPosition()은 객체의 위치를 설정해주는 메소드다.

스프라이트 위치의 기본값은 (0, 0)이기 때문에 따로 설정하지 않으면 위치 값은 (0, 0)의 좌표로 설정된다.

</br>

> this->addChild(sprite);

코코스2d-x에서는 객체를 화면에 그리는 메소드를 따로 제공하지 않는다.

대신 객체를 생성한 후 addChild()를 호출하면 그 순간부터 해당 객체가 화면에 보이기 시작한다.

addChild()는 뒤에서 자세히 설명하도록 하겠다.

</br>
</br>

```C++
bool HelloWorld::init()
{
    if(!Layer::init())
        return false;

    auto sprite = Sprite::create("HelloWorld.png", Rect(0, 0, 100, 100));
    sprite->setPosition(Point(200, 200));
    this->addChild(sprite); 

    return true;
}
```
</br>

> auto sprite = Sprite::create("HelloWorld.png", Rect(0, 0, 100, 100));

스프라이트를 생성할 때 매개변수로 영역을 설정하는 Rect()를 추가로 입력할 수도 있다.

위의 코드는 이미지의 (0, 0) 좌표에서 100×100픽셀 크기만큼을 영역으로 설정하는 코드다.

</br>

💡 Rect()를 이용할 때는 **코코스2d-x 좌표계가 아닌 일반적인 좌표계**를 따른다.

</br>

위의 코드에서 스프라이트 객체인 **sprite는 addChild()를 호출한 객체인 this에 종속**된다.

이러한 것을 **부모-자식 관계**라고 말한다. 위의 코드에서는 this인 Layer가 부모가 되며, sprite는 자식이 된다.

</br>

```C++
bool HelloWorld::init()
{
    if(!Layer::init())
        return false;

    auto sprite = Sprite::create("HelloWorld.png");
    sprite->setAnchorPoint(Point(0.5, 0.5));
    sprite->setPosition(Point(200, 200));
    this->addChild(sprite);

    this->setPosition(Point(100, 100));

    return true;
}
```
</br>

위의 코드에서는 부모인 this의 좌표가 (0, 0)에서 (100, 100)만큼 이동했다. 

따라서 this의 자식으로 추가되었던 sprite 객체의 위치를 (200, 200)으로 설정해도 (300, 300)만큼 이동한 것처럼 보인다.

이렇게 **부모-자식 관계에서 부모의 위치뿐만 아니라 부모를 확대/축소해도 자식도 똑같은 비율로 확대/축소**된다.

</br>

|종류|매개변수|
|----|-------|
|addChild(Node* child)|[child] 자식이 되는 객체|
|addChild(Node* child, int localZOrder)|[child] 자식이 되는 객체, [localZOrder] z축 값|
|addChild(Node* child, int localZOrder, int tag)|[child] 자식이 되는 객체, [localZOrder] z축 값, [tag] 태그 값|

</br>

> addChild(Node* child)

우리가 일반적으로 사용하는 방법으로 **자식의 객체만을 지정하는 방법**이다.

</br>

> addChild(Node* child, int localZOrder)

위의 방법에다가 추가적으로 localZOrder인 z축 값을 지정할 수 있다.

z축이 같다면 addChild()를 나중에 한 객체가 화면상에서 위에 출력되는데, **z축의 값이 큰 것이 화면 위에 나중에 보이게 된다**.

만약, **z축의 값만 따로 설정**하고 싶을 때는 **setZOrder()**를 사용할 수 있다.

</br>

### 2.2.2 코코스2d-x의 기본 자료형

#### Point

Point는 x 좌표 값인 X와 y 좌표 값인 y를 가지며 **위치의 값을 지정할 때 사용되는 자료형**이다.

앞선 예제에서 위치를 설정할 때 Point()로 설정하는 것을 볼 수 있었다.

추가적으로 아래 코드처럼 **Point()의 x, y값을 사용하는 것도 가능**하다.

</br>

```C++
bool HelloWorld::init()
{
    if(!Layer::init())
        return false;

    Point point = Point(240, 160);
    CCLOG("%f: %f", point.x, point.y);      // CCLOG는 코코스2d-x에서 로그를 출력하는 메소드다.
}
```
</br>

#### Size

Size는 너비인 width와 높이인 height를 가지며, **크기를 지정할 때 사용되는 자료형**이다.

역시 Size 요소들의 값들도 사용할 수 있다.

</br>

```C++
bool HelloWorld::init()
{
    if(!Layer::init())
        return false;

    Size size = Size(100, 100);
    CCLOG("%f %f", size.width, size.height);

    return true;
}
```
</br>

#### Rect

Rect는 **x와 y 좌표의 값을 가지는 origin**과 너비와 높이를 가지는 **size로 구성**되며, **영역을 지정할 때 사용되는 자료형**이다.

앞선 예제를 보면 이미지의 영역을 설정할 때 Rect(0, 0, 100, 100)으로 입력한 것을 확인할 수 있었다.

이는 (0, 0) 좌표를 기준에다가 일반적인 좌표계 기준으로 100×100 픽셀만큼의 이미지를 영역으로 설정한 것이다.

</br>

```C++
bool HelloWorld::init()
{
    if(!Layer::init())
        return false;

    Rect rect = Rect(240, 160, 100, 100);
    CCLOG("%f: %f: %f: %f", rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);

    return true;
}
```
</br>

### 2.2.3 코코스2d-x의 기본 메소드

코코스2d-x에서는 스프라이트나 텍스트에 해당하는 라벨 등에 **공통적으로 적용되는 기본 메소드들이 존재**한다.

예를 들어 이미지의 크기를 확대/축소한다거나 90도로 회전한다거나, 이미지 객체를 반투명으로 만드는 때 사용하는 기능들이다.

</br>

#### setScale(), setScaleX(), setScaleY()

setScale()은 객체를 확대/축소할 때 사용되는 메소드다.

float형으로 크기의 비율을 매개변수로 받으며 1보다 클 경우에는 확대되며, 1보다 작을 경우에는 축소된다.

</br>

```C++
bool HelloWorld::init()
{
    if(!Layer::init())
        return false;

    auto test_spr = Sprite::create("Test.png");
    test_spr->setScale(2.0);        // 객체를 2배 확대한다.
    test_spr->setScale(0.5);        // 객체를 0.5배로 축소한다.
    test_spr->setScaleX(2.0);       // 객체의 너비를 2배 확대한다.
    test_spr->setScaleY(1.5);       // 객체의 높이를 1.5배 확대한다.

    return true;
}
```
</br>

#### setRotation(), setRotationSkewX(), setRotationSkewY()

setRotation()은 객체를 회전시키는 메소드다.

회전시킬 각도를 매개변수로 받으며, **입력한 값이 +면 시계방향으로 회전하며, -일 경우에는 반시계방향으로 회전**한다.

만약 **360도를 초과할 경우에는 360을 제외한 만큼 회전**한다.

**setRotation()은 z축을 기준으로 회전**하며, 일반적으로 화면에 있는 객체를 회전할 때 사용하는 메소드다.

setRotationSkewX(), setRotationSkewY()는 x축과 y축을 기준으로 회전하는 메소드다.

또한 **회전할 때는 앵커포인트를 기준으로 회전한다**. 그래서 앵커포인트에 따라서 회전하는 궤적이 달라진다.

</br>

```C++
bool HelloWorld::init()
{
    if(!Layer::init())
        return false;

    auto test_spr = Sprite::create("Test.png");
    test_spr->setRotation(30);          // Z축 기준, 시계방향으로 30도 회전한다.
    test_spr->setRotation(-45);         // Z축 기준, 반시계방향으로 45도 회전한다.
    test_spr->setRotationSkewX(70);     // X축 기준, 시계방향으로 70도 회전한다.
    test_spr->setRotationSkewY(60);     // Y축 기준, 시계방향으로 60도 회전한다.

    return true;
}
```
</br>

#### setFlippedX(), setFlippedY()

setFlippedX()는 객체의 **좌우 반전을 설정**하는 메소드이며, setFlippedY()는 객체의 **상하 반전을 설정**하는 메소드다.

또한 **반전을 할 때는 앵커포인트의 영향을 받지 않는다**. 즉, 반전을 하면 **반전하기 전에 객체가 있는 영역에서 객체만 반전 되어서 출력**된다.

</br>

```C++
bool HelloWorld::init()
{
    if(!Layer::init())
        return false;

    auto test_spr = Sprite::create("Test.png");
    test_spr->setFlippedX(true);        // 좌우 반전을 한다.
    test_spr->setFlippedY(true);        // 상하 반전을 한다.

    return true;
}
```
</br>

#### setOpacity()

setOpacity()는 **객체의 투명도를 설정**하는 메소드다. **투명도의 값은 0부터 255**까지다.

**0일 경우에는 투명 상태**로 화면에 보이지 않게 되고, **255일 경우에는 불투명 상태**로 일반적으로 화면에 객체가 출력되는 상태다. 128은 반투명 상태다.

</br>

```C++
bool HelloWorld::init()
{
    if(!Layer::init())
        return false;

    auto test_spr = Sprite::create("Test.png");
    test_spr->setOpacity(255);      // 객체를 불투명 상태로 만든다.
    test_spr->setOpacity(0);        // 객체를 투명 상태로 만든다.
    test_spr->setOpacity(128);      // 객체를 반투명 상태로 만든다.

    return true;
}
```
</br>

#### setVisible()

setVisible()은 **객체의 화면 출력 여부를 설정**하는 메소드다.

받는 매개변수의 값이 **true면 화면에 객체가 출력되고, false일 경우에는 화면에 객체가 출력되지 않는다**.

</br>

```C++
bool HelloWorld::init()
{
    if(!Layer::init())
        return false;

    auto test_spr = Sprite::create("Test.png");
    test_spr->setVisible(true);     // 화면에 객체가 출력되게 한다.
    test_spr->setVisible(false);    // 화면에 객체가 출력되지 않도록 한다.

    return true;
}
```
</br>

### 2.2.4 스프라이트를 이용한 화면 구성

지금까지 공부한 내용들로 스프라이트를 생성해서 화면을 구성해보자.

스프라이트의 위치는 수치를 입력하는 것이 아닌 화면 크기 값을 가져와서 사용할 것이다.

화면의 크기를 가져오기 위해서는 다음의 메소드를 사용하면 된다.

</br>

```C++
Size win_size = Director::getInstance()->getWinSize();
```
</br>

또한 화면에 배경을 검은색이 아닌 흰색으로 출력하기 위해서 Layer가 아닌 LayerColor를 상속받을 것이다.

</br>

```C++
#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class HelloWorld : public LayerColor
{
public:
    static Scene* createScene();

    virtual bool init();
    CREATE_FUNC(HelloWorld);
};

#endif
```
</br>

</br>

```C++
bool HelloWorld::init()
{
    if ( !LayerColor::initWithColor(Color4B(255, 255, 255, 255)) )
    {
        return false;
    }

    Size win_size = Director::getInstance()->getWinSize();

    auto sprite1 = Sprite::create("HelloWorld.png");
    sprite1->setAnchorPoint(Point::ZERO);
    sprite1->setScale(0.5);
    this->addChild(sprite1);

    auto sprite2 = Sprite::create("HelloWorld.png");
    sprite2->setAnchorPoint(Point(0.5, 0));
    sprite2->setScale(0.5);
    sprite2->setPosition(Point(win_size.width / 2, 0));
    this->addChild(sprite2, 1);

    auto sprite3 = Sprite::create("HelloWorld.png");
    sprite3->setAnchorPoint(Point(1, 0));
    sprite3->setPosition(Point(win_size.width, 0));
    this->addChild(sprite3);

    auto sprite4 = Sprite::create("HelloWorld.png");
    sprite4->setPosition(Point(win_size.width / 2, 0));
    sprite4->setScale(0.5);
    this->addChild(sprite4);

    auto sprite5 = Sprite::create("HelloWorld.png");
    sprite5->setAnchorPoint(Point(0.5, 1));
    sprite5->setPosition(Point(win_size.width / 2, win_size.height));
    sprite5->setScale(0.5);
    sprite5->setFlippedY(true);
    this->addChild(sprite5);

    return true;
}
```
</br>