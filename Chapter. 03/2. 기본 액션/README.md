## 기본 액션

</br>

코코스2d-x에서 제공하는 기본 액션은 아래의 표와 같다.

|분류|종류|
|----|----|
|위치|MoveBy, MoveTo, JumpBy, JumpTo, BezierBy, BezierTo|
|크기|ScaleBy, ScaleTo|
|회전|RotateBy, RotateTo|
|화면 출력|Show, Hide, Blink, ToggleVisibility|
|투명도|FadeIn, FadeOut, FadeTo|
|색상|TintBy, TintTo|

</br>

**액션은 Node를 상속받은 객체(Layer, Sprite, Label 등)에 실행**시킬 수 있다.

</br>
</br>

### 3.2.1 위치

</br>

#### MoveBy, MoveTo

**지정한 시간 동안 지정한 위치로 객체의 위치를 변경**해주는 액션이다.

</br>

#### JumpBy, JumpTo

**지정한 시간 동안 지정한 위치로 객체의 위치를 변경**해주면서 **지정한 높이로 지정한 횟수만큼 점프**를 하는 액션이다.

**JumpBy** 액션의 경우 **도착 위치가 현재 위치를 기준으로 상대적인 위치**가 되며, **JumpTo** 액션은 **현재 위치와 상관없이 지정한 위치**로 이동한다.

</br>

```C++
bool HelloWorld::init()
{
    if (!Layer::init())
        return false;

    auto sprite = Sprite::create("ball.png");
    sprite->setPosition(Point(100, 100));
    this->addChild(sprite);

    auto move_action = JumpBy::create(5.0, Point(300, 0), 150, 5);
    sprite->runAction(move_action);

    return true;
}
```
</br>

JumpBy를 사용했기 때문에 5초 동안 현재 위치인 (100, 100)보다 (300, 0)을 이동한 **(400, 100)으로 이동**한다. 

그리고 **이동하면서 150픽셀의 높이만큼 5번 점프**한다.

</br>

#### BezierBy, BezierTo

ccBezierConfig에 의해서 만들어진 **베지어 곡선대로 지정된 시간 동안 움직이는 액션**이다.

코코스2d-x에서는 **시작점과 도착점, 그리고 2개의 제어점을 가지는 3차 베지어 곡선을 사용**하고 있다.

베지어 곡선의 **설정은 ccBezierConfig 객체를 생성해서 설정**할 수 있다. 설정하는 방법은 아래와 같다.

</br>

```C++
bool HelloWorld::init()
{
    if (!Layer::init())
        return false;

    auto sprite = Sprite::create("ball.png");
    sprite->setPosition(Point(50, 50));                 // 시작점
    this->addChild(sprite);

    ccBezierConfig bezier_config;
    bezier_config.controlPoint_1 = Point(200, 250);     // 제어점1
    bezier_config.controlPoint_1 = Point(400, 150);     // 제어점2
    bezier_config.endPosition = Point(450, 50);         // 도착점

    auto bezier_action = BezierTo::create(3.0, bezier_config);
    sprite->runAction(bezier_action);

    return true;
}
```
</br>

위 코드에서는 ccBezierConfig를 선언한 후, 첫 번째 제어점을 (200, 250)으로 설정했고, 두 번째 제어점을 (400, 150)으로 설정했다.

그리고 도착점을 (450, 50)으로 설정했다.

</br>

> auto bezier_action = BezierTo::create(3.0, bezier_config);

이렇게 생성한 bezier_config를 가지고 이동 시간을 3초로 한 Bezier 액션을 생성할 수 있다.

</br>

Bezier 액션에서 By와 To의 차이점은 By는 제어점 또는 도착점으로 이동할 때 이전의 값을 기준으로 상대적인 위치 값으로 이동한다.

반대로 To는 이전의 값과 상관없이 지정된 위치로 값을 이동한다. 이는 여러 번 실습을 하게 되면 대략적인 이동 경로를 예측할 수 있다.

</br>

#### Place

**객체의 위치를 지정된 위치로 변경**하는 액션이다. Place 액션은 **setPosition()과 동일한 기능**을 하는 액션이다.

Place 액션의 경우 단독으로 사용하기보다는 나중에 배울 **조합액션에서 많이 사용**된다. 즉, **단순히 위치를 변경하고 싶을 경우에는 setPosition()을 사용**하면 된다.

하지만 어떤한 **액션들을 순차적으로 조합하는 과정에서 중간에 위치를 변경하고 싶을 때는 Place 액션을 사용**하면 된다.

</br>

```C++
bool HelloWorld::init()
{
    if (!Layer::init())
        return false;

    auto sprite = Sprite::create("ball.png");
    sprite->setPosition(Point(50, 50));
    this->addChild(sprite);

    auto place_action = Place::create(Point(100, 100));
    sprite->runAction(place_action);

    return true;
}
```
</br>
</br>

### 3.2.2 크기

</br>

#### ScaleBy, ScaleTo 

**지정한 시간 동안 지정한 크기로 객체의 크기를 변경**해주는 액션이다. Scale 액션은 객체의 크기를 원하는 크기로 **확대 또는 축소할 수 있는 액션**이다.

ScaleBy 액션은 **현재의 크기를 기준으로 크기를 변경**하며, 크기의 **값이 1.0보다 작으면 객체는 축소되며, 1.0보다 크면 객체는 확대**된다.

ScaleTo 액션은 현재의 크기와 상관없이 **지정한 크기로 변경하는 액션**이다. 그래서 **현재의 크기 값보다 변경할 크기의 값이 작으면 축소, 크면 확대**된다.

</br>

```C++
bool HelloWorld::init()
{
    if (!Layer::init())
        return false;

    auto sprite = Sprite::create("ball.png");
    sprite->setPosition(Point(50, 50));
    sprite->setScale(1.0);
    this->addChild(sprite);

    auto scale_action = ScaleTo::create(2.0, 3.0); // 2초 동안 크기를 3배 확대하는 ScaleTo 액션을 생성
    sprite->runAction(scale_action);

    return true;
}
```
</br>
</br>

### 3.2.3 회전

</br>

#### RotateBy, RotateTo

지정한 시간 동안 지정한 각도로 객체를 회전시키는 액션이다. Rotate 액션에서 회전하는 방향은 상황에 따라서 조금씩 다르다.

</br>

RotateTo의 경우, 기본적으로 입력한 각도가 **+일 경우에는 시계 방향으로 회전**을 하며, **-일 경우에는 반시계 방향으로 회전**한다.

하지만 회전하는 **각도의 크기가 180을 넘을 경우에는 더 적게 회전하는 방향으로 회전**을 하게 된다.

즉, RotateTo는 입력한 각도의 값으로 방향이 결정되지 않고 **입력한 각도로 가장 빠르게 이동할 수 있는 방향으로 회전**한다.

</br>

RotateBy의 경우, RotateTo와 다르게 **입력된 값만큼 회전**한다. 예를 들어 450을 입력하면 한 바퀴 회전을 한 후에 90도만큼 더 회전한다.

또 270을 입력하면 시계방향으로 270도 회전하며 마찬가지로, -270을 입력하면 반시계 방향으로 270도 회전한다.

</br>

각도를 지정하는 **매개변수를 1개만 입력하면 z축을 기준으로 회전**한다.

각도를 지정하는 **매개변수를 2개 입력하면 x축, y축을 기준으로 회전하는 것도 설정할 수 있다**.

x축, y축의 경우는 처음에는 쉽게 예상할 수 없으므로 **각 값 중에서 하나는 0의 값으로 설정한 후 회전을 살펴보면 더 이해하기 쉽다**.

</br>

```C++
bool HelloWorld::init()
{
    if (!Layer::init())
        return false;

    auto sprite = Sprite::create("HelloWorld.png");
    sprite->setPosition(Point(200, 200));
    this->addChild(sprite);

    auto rotate_action = RotateBy::create(2.0, 450);    // 2초 동안 450도만큼 시계 방향으로 회전
    sprite->runAction(rotate_action);

    return true;
}
```
</br>
</br>

### 3.2.4 화면 출력

</br>

#### Show

Show **액션은 객체를 보여주는 액션**이다. 즉, **setVisible()의 값을 true로 변경해주는 액션**이다.

이미 객체의 setVisible()의 값이 true인 경우에는 아무런 변화가 없으며, false일 경우에는 화면에 보여준다.

Show 액션도 단일 액션으로는 잘 사용되지 않으며, Place 액션과 비슷하게 **조합 액션을 만들 때 자주 사용**된다.

</br>

```C++
bool HelloWorld::init()
{
    if (!Layer::init())
        return false;

    auto sprite = Sprite::create("HelloWorld.png");
    sprite->setPosition(Point(200, 200));
    sprite->setVisible(false);              // sprite의 setVisible()을 false로 설정하고,
    this->addChild(sprite);

    auto show_action = Show::create();
    sprite->runAction(show_action);         // Show 액션을 통해 sprite의 setVisible()을 true로 설정

    return true;
}
```
</br>

#### Hide

Hide 액션은 **객체를 화면에서 안보이게 하는 액션**이다. 즉, Show 액션과 반대로 **setVisible()의 값을 false로 변경해주는 액션**이다.

</br>

```C++
bool HelloWorld::init()
{
    if (!Layer::init())
        return false;

    auto sprite = Sprite::create("HelloWorld.png");
    sprite->setPosition(Point(200, 200));
    this->addChild(sprite);

    auto hide_action = Hide::create();
    sprite->runAction(hide_action);         // Hide 액션을 통해 sprite의 setVisible()을 false로 설정

    return true;
}
```
</br>

#### Blink

Blink는 **지정된 시간 동안 지정한 횟수만큼 객체를 깜박이게 하는 액션**이다.

</br>

```C++
bool HelloWorld::init()
{
    if (!Layer::init())
        return false;

    auto sprite = Sprite::create("HelloWorld.png");
    sprite->setPosition(Point(200, 200));
    sprite->setVisible(false);
    this->addChild(sprite);

    auto blink_action = Blink::create(3.0, 10);     // sprite 객체가 3초동안 10번 깜박이도록 설정
    sprite->runAction(blink_action);

    return true;
}
```
</br>

#### ToggleVisibility

ToggleVisibility 액션은 **실행할 때마다 setVisible()의 값을 반대로 바꿔주는 액션**이다.

즉, 객체가 화면에 보일 때 ToggleVisibility 액션을 실행하면 객체가 안보이게 되며, 안보일 때 실행하면 보이게 된다.

</br>

```C++
bool HelloWorld::init()
{
    if (!Layer::init())
        return false;

    auto sprite = Sprite::create("HelloWorld.png");
    sprite->setPosition(Point(200, 200));
    sprite->setVisible(true);                                       // setVisible()의 값을 명시적으로 true로 설정하고,
    this->addChild(sprite);

    auto toggle_visibility_action = ToggleVisibility::create();     // ToggleVisibility 액션을 통해 setVisible()의 값을 false로 설정
    sprite->runAction(toggle_visibility_action);

    return true;
}

```
</br>
</br>

### 3.2.5 투명도

</br>

#### FadeIn

**지정된 시간 동안 객체의 투명도를 0에서 255로 변하게 하는 액션**이다.

FadeIn 액션은 **객체가 보이지 않다가 자연스럽게 화면에 출력하려고 할 때 사용되는 액션**이다.

객체의 setOpacity()의 **값이 이미 255라면 FadeIn 액션은 실행되지 않는다**.

</br>

```C++
bool HelloWorld::init()
{
    if (!Layer::init())
        return false;

    auto sprite = Sprite::create("HelloWorld.png");
    sprite->setPosition(Point(200, 200));
    sprite->setOpacity(0);
    this->addChild(sprite);

    auto fade_in_action = FadeIn::create(3.0);
    sprite->runAction(fade_in_action);

    return true;
}
```
</br>

#### FadeOut

**지정된 시간 동안 객체의 투명도를 255에서 0으로 변하게 하는 액션**이다.

FadeOut 액션은 FadeIn 액션과 반대로 투명도를 255에서 0으로 변하게 한다.

역시 마찬가지로 객체의 setOpacity()의 **값이 이미 0이라면 FadeOut 액션은 실행되지 않는다**.

</br>

```C++
bool HelloWorld::init()
{
    if (!Layer::init())
        return false;

    auto sprite = Sprite::create("HelloWorld.png");
    sprite->setPosition(Point(200, 200));
    sprite->setOpacity(255);
    this->addChild(sprite);

    auto fade_out_action = FadeOut::create(3.0);
    sprite->runAction(fade_out_action);

    return true;
}
```
</br>

#### FadeTo

FadeTo 액션은 **지정된 시간 동안 지정한 투명도로 변경해주는 액션**이다.

</br>

```C++
bool HelloWorld::init()
{
    if (!Layer::init())
        return false;

    auto sprite = Sprite::create("HelloWorld.png");
    sprite->setPosition(Point(200, 200));
    sprite->setOpacity(255);
    this->addChild(sprite);

    auto fade_to_action = FadeTo::create(3.0, 128);
    sprite->runAction(fade_to_action);

    return true;
}
```
</br>
</br>

### 3.2.6 색상

</br>

#### TintBy, TintTo

**지정한 시간 동안 지정한 RGB의 값으로 색상을 변경하는 액션**이다. Tint 액션은 지정한 RGB의 값으로 객체를 변경하는 액션이다.

객체의 모든 색상을 지정한 값으로 변경하는 것은 아니다. 쉽게 설명하면 **어떤 객체에 색상을 더한다**고 생각하면 된다.

</br>

```C++
bool HelloWorld::init()
{
    if (!Layer::init())
        return false;

    auto sprite = Sprite::create("HelloWorld.png");
    sprite->setPosition(Point(200, 200));
    sprite->setOpacity(255);
    this->addChild(sprite);

    auto tint_to_action = TintTo::create(3.0, Color3B::RED);
    sprite->runAction(tint_to_action);

    return true;
}
```
</br>