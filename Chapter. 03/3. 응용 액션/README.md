## 응용 액션

</br>

### 3.3.1 시퀀스 액션

</br>

시퀀스 액션은 **2개 이상의 액션을 순차적으로 실행해주는 액션**이다.

</br>

```C++
bool HelloWorld::init()
{
    if (!Layer::init())
        return false;

    auto sprite = Sprite::create("ball.png");
    sprite->setPosition(Point(100, 100));
    this->addChild(sprite);

    auto move_action_1 = MoveTo::create(1.0, Point(400, 100));
    auto move_action_2 = MoveTo::create(1.0, Point(400, 250));
    auto sequence_action = Sequence::create(move_action_1, move_action_2, NULL);
    sprite->runAction(sequence_action);

    return true;
}
```
</br>

> auto sequence_action = Sequence::create(move_action_1, move_action_2, NULL);

move_action_1과 move_action_2가 순차적으로 실행되는 Sequence 액션을 생성한다.

</br>

시퀀스 액션은 **순차적으로 실행하고자 하는 액션을 생성한 후, create()에서 생성한 액션을 차례대로 입력**한다.

단, 마지막에는 더 이상 입력하는 액션이 없다는 것을 알려주기 위해서 **마지막엔 NULL을 꼭 입력해야 한다**.

시퀀스 액션은 **2개뿐만 아니라 더 많은 개수의 액션**을 create() 입력으로 순차적으로 실행할 수 있다.

</br>
</br>

### 3.3.2 스폰 액션

스폰 액션은 **동시에 2개 이상의 액션을 실행시키는 액션**이다.

</br>

```C++
bool HelloWorld::init()
{
    if (!Layer::init())
        return false;

    auto sprite = Sprite::create("ball.png");
    sprite->setPosition(Point(100, 100));
    this->addChild(sprite);

    auto move_action = MoveTo::create(2.0, Point(400, 100));
    auto fade_out_action = FadeOut::create(2.0);
    auto scale_to_action = ScaleTo::create(2.0, 3.0);
    auto spawn_action = Spawn::create(move_action, fade_out_action, scale_to_action, NULL);
    sprite->runAction(spawn_action);

    return true;
}
```
</br>

> auto spawn_action = Spawn::create(move_action, fade_out_action, scale_to_action, NULL);

move_action, fade_out_action, scale_to_action이 동시에 실행되는 Spawn 액션을 생성한다.

</br>
</br>

### 3.3.3 리버스 액션

</br>

리버스 액션은 **실행했던 액션을 반대로 실행시키는 액션**이다.

</br>

```C++
bool HelloWorld::init()
{
    if (!Layer::init())
        return false;

    auto sprite = Sprite::create("ball.png");
    sprite->setPosition(Point(100, 100));
    this->addChild(sprite);

    auto move_action = MoveBy::create(2.0, Point(400, 100));
    auto reverse_action = move_action->reverse();
    auto sequence_action = Sequence::create(move_action, reverse_action, NULL);
    sprite->runAction(sequence_action);

    return true;
}
```
</br>

> auto reverse_action = move_action->reverse();

move_action의 동작을 반대로 하는 리버스 액션을 생성한다.

</br>

리버스 액션은 **반대로 실행할 수 있는 액션만 가능**하다.

위의 코드에서 move_action에서 MoveBy가 아닌 MoveTo로 했다고 하자.

그렇다면 실행했을 때 **에러는 발생하지 않지만** 첫 번째 액션만 수행하고, 두 번째 리버스 액션을 수행할 때는 이미지에 **변화가 없을 것**이다.

</br>
</br>

### 3.3.4 딜레이타임 액션

</br>

딜레이타임 액션은 **지정된 시간동안 어떤 동작도 하지 않고 기다리는 액션**이다. 일반적으로 2개 이상의 **시퀀스 액션을 수행할 때 많이 사용**된다.

</br>

```C++
bool HelloWorld::init()
{
    if (!Layer::init())
        return false;

    auto sprite = Sprite::create("ball.png");
    sprite->setPosition(Point(100, 100));
    this->addChild(sprite);

    auto move_action_1 = MoveTo::create(2.0, Point(400, 100));              // sprite가 (400, 100)으로 이동하고
    auto delay_time_action = DelayTime::create(3.0);                        // 3초를 대기한 다음
    auto move_action_2 = MoveTo::create(2.0, Point(400, 250));              // sprite가 (400, 250)으로 이동
    auto sequence_action = Sequence::create(move_action_1, delay_time_action, move_action_2, NULL);
    sprite->runAction(sequence_action);

    return true;
}
```
</br>
</br>

### 3.3.5 반복, 무한반복 액션

</br>

**반복 액션**은 **지정된 액션을 지정된 횟수만큼 반복하는 액션**이고, **무한반복 액션**은 반복되는 횟수를 따로 지정하지 않고 **무한으로 반복하는 액션**이다.

**무한반복 액션은 애니메이션을 구현할 때 많이 사용**된다.

</br>

```C++
bool HelloWorld::init()
{
    if (!Layer::init())
        return false;

    auto sprite = Sprite::create("ball.png");
    sprite->setPosition(Point(100, 100));
    this->addChild(sprite);

    auto move_action = MoveBy::create(1.0, Point(200, 100));                        // sprite가 최종적으로 (300, 200)까지 이동하고 
    auto reverse_action = move_action->reverse();                                   // 다시 되돌아 오는 액션을
    auto sequence_action = Sequence::create(move_action, reverse_action, NULL);     // 하나의 시퀀스 액션으로 만들고
    auto repeat_action = Repeat::create(sequence_action, 5);                        // 이 시퀀스 액션을 5번 반복하는 반복 액션을 생성
    sprite->runAction(repeat_action);

    return true;
}
```
</br>

무한 반복 액션의 경우 반복 액션과 **사용 방법이 동일**하며, **반복하는 횟수를 입력받지 않는다**는 것만 다르다.

</br>
</br>

### 3.3.6 이즈 액션

</br>

이즈 액션은 액션을 실행할 때 동일한 속도가 아닌 특정한 가속도를 주어서 실행하게 해주는 액션이다.

</br>

#### In, Out, InOut 액션

이즈 액션은 **언제 해당 액션이 적용되는지에 따라** In, Out, InOut 액션으로 구분한다.

In 액션은 해당되는 이즈 액션이 액션에 **앞부분에 적용**되는 것이고, Out 액션은 **뒷부분에 적용**되며, InOut 액션은 **앞부분과 뒷부분에서 적용**되는 액션이다.

</br>

#### EaseIn, EaseOut, EaseInOut

**액션의 속도를 느리게 해주는 이즈 액션**이다.

EaseIn 액션은 액션의 속도를 **앞부분에서 느리게 했다가** 뒷부분으로 갈수록 빠르게 변화하는 액션이다.

EaseOut 액션은 액션의 속도를 **앞부분에서 빠르게 했다가** 뒷부분으로 갈수록 느리게 변화하는 액션이다.

EaseInOut 액션은 앞부분에서는 느리게 했다가 **실행 시간의 절반 정도가 되었을 때 가장 빠르게 변하며**, 다시 뒷부분을 갈수록 느리게 변화하는 액션이다.

</br>

이즈 액션의 경우는 **가속도의 비율을 직접 입력**할 수도 있다.

**가속도의 비율이 1이면 등속도와 비슷한 속도**로 움직이며, 비율의 값이 **커질수록 느린 부분과 빠른 부분의 차이**가 많이 나게 된다.

</br>

```C++
bool HelloWorld::init()
{
    if (!Layer::init())
        return false;

    auto sprite = Sprite::create("ball.png");
    sprite->setPosition(Point(100, 100));
    this->addChild(sprite);

    auto move_action = MoveTo::create(1.0, Point(400, 100));
    auto ease_action = EaseIn::create(move_action, 3.0);        // MoveTo 액션의 가속 비율을 3.0으로 적용한 EaseIn 액션을 생성
    sprite->runAction(ease_action);

    return true;
}
```
</br>

#### EaseSineIn,EaseSineOut, EaseSineInOut

**EaseSine** 액션은 천천히 **느려지는 부분과 빠르게 변화하는 부분의 차이가 적은** 이즈 액션이다.

Ease 액션에서 가속비율이 1.5일 경우와 결과가 비슷하게 발생한다.

</br>

```C++
bool HelloWorld::init()
{
    if (!Layer::init())
        return false;

    auto sprite = Sprite::create("ball.png");
    sprite->setPosition(Point(100, 100));
    this->addChild(sprite);

    auto move_action = MoveTo::create(1.0, Point(400, 100));
    auto ease_action = EaseSineIn::create(move_action);
    sprite->runAction(ease_action);

    return true;
}
```
</br>

#### EaseExponentialIn, EaseExponentialOut, EaseExponentialInOut

**EaseExponential** 액션은 **천천히 느려지는 부분과 빠르게 변화하는 부분의 차이가 많은** 이즈 액션이다.

Ease 액션에서 가속비율이 6.5일 경우와 결과가 비슷하게 발생한다.

</br>

```C++
bool HelloWorld::init()
{
    if (!Layer::init())
        return false;

    auto sprite = Sprite::create("ball.png");
    sprite->setPosition(Point(100, 100));
    this->addChild(sprite);

    auto move_action = MoveTo::create(1.0, Point(400, 100));
    auto ease_action = EaseExponentialIn::create(move_action);
    sprite->runAction(ease_action);

    return true;
}
```
</br>

#### EaseElasticIn, EaseElasticOut, EaseElasticInOut

EaseElastic 액션은 **고무줄처럼 튕기는 효과**를 주는 이즈 액션이다.

**EaseElasticIn** 액션은 **시작점에서 고무줄을 튕기는 것처럼** 앞뒤로 움직이다가 빠르게 도착점으로 이동한다.

**EaseElasticOut** 액션은 시작점에서 빠르게 이동하고 **도착점에서 고무줄에 튕기는 것처럼** 앞뒤로 움직인다.

</br>

```C++
bool HelloWorld::init()
{
    if (!Layer::init())
        return false;

    auto sprite = Sprite::create("ball.png");
    sprite->setPosition(Point(100, 100));
    this->addChild(sprite);

    auto move_action = MoveTo::create(1.0, Point(400, 100));
    auto ease_action = EaseElasticIn::create(move_action);
    sprite->runAction(ease_action);

    return true;
}
```
</br>

#### EaseBackIn, EaseBackOut, EaseBackInOut

EaseBack 액션은 시작점에서 뒤로 이동했다가 도착점으로 이동하는 이즈 액션이다.

EaseBackIn 액션을 적용해서 실행하면 **시작점에서 뒤로 이동했다가** 도착점으로 이동한다.

EaseBackOut 액션을 적용하면, 바로 도착점으로 이동하는 데 **도착점보다 더 많이 이동한 후에 도착점으로** 돌아온다.

EaseBackInOut 시작점과 도착점에서 **모두 더 많이 이동**한 후에 다시 돌아온다.

</br>

```C++
bool HelloWorld::init()
{
    if (!Layer::init())
        return false;

    auto sprite = Sprite::create("ball.png");
    sprite->setPosition(Point(100, 100));
    this->addChild(sprite);

    auto move_action = MoveTo::create(1.0, Point(400, 100));
    auto ease_action = EaseBackIn::create(move_action);
    sprite->runAction(ease_action);

    return true;
}
```
</br>

#### EaseBounceIn, EaseBounceOut, EaseBounceInOut

EaseBounce 액션은 **공이 튕기는 듯한 느낌을 주는 이즈 액션**이다.

</br>

```C++
bool HelloWorld::init()
{
    if (!Layer::init())
        return false;

    auto sprite = Sprite::create("ball.png");
    sprite->setPosition(Point(200, 300));
    this->addChild(sprite);

    auto move_action = MoveTo::create(2.0, Point(200, 100));
    auto ease_action = EaseBounceOut::create(move_action);
    sprite->runAction(ease_action);

    return true;
}
```
</br>
</br>

### 3.3.7 콜 펑션 액션

</br>

콜 펑션 액션은 **메소드를 호출하는 액션**이다. 이 액션으로 단독으로는 사용하지 않고, **보통 조합 액션에서 사용**된다.

콜 펑션 액션은** 매개변수에 따라 CallFunc, CallFuncN으로 구분**한다. 

CallFunc 액션은 **매개변수가 없는** 콜 펑션이며, CallFuncN 액션은 **매개변수로 액션을 실행한 객체 등을 받는** 콜 펑션이다.

</br>

우선, 콜 펑션 액션을 위해 .h에 메소드 선언을 추가한다.

</br>

```C++
#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class HelloWorld : public Layer
{
public:
    static Scene* createScene();

    virtual bool init();
    void menuCallback(Ref* sender);
    CREATE_FUNC(HelloWorld);

    void setCallFunc_0();
    void setCallFunc_1(Ref* sender);
    void setCallFunc_2(Ref* sender, void* d);
    void setCallFunc_3(Ref* sender, Ref* object);
};

#endif
```
</br>

> void setCallFunc_0();

setCallFunc_0은 **매개변수가 없는 CallFunc 액션에서 호출**할 메소드다.

</br>

> void setCallFunc_1(Ref* sender);

setCallFunc_1은 매개변수로 **액션을 실행한 객체를 받는 CallFuncN 액션에서 호출**할 메소드다.

</br>

> void setCallFunc_2(Ref* sender, void* d);

setCallFunc_2는 매개변수로 액션을 실행한 객체와 특정한 값을 받는 CallFuncN 액션에서 호출할 메소드다.

</br>

> void setCallFunc_3(Ref* sender, Ref* object);

setCallFunc_3는 매개변수로 액션을 실행한 객체와 특정한 객체를 받는 메소드다.

</br>

```C++
void HelloWorld::setCallFunc_0()
{
    CCLOG("HelloWorld::setCallFunc_0()");
}

void HelloWorld::setCallFunc_1(Ref* sender)
{
    CCLOG("HelloWorld::setCallFunc_1()");
}

void HelloWorld::setCallFunc_2(Ref* sender, void* d)
{
    CCLOG("HelloWorld::setCallFunc_2()");
}

void HelloWorld::setCallFunc_3(Ref* sender, Ref* object)
{
    CCLOG("HelloWorld::setCallFunc_3()");
}
```
</br>

#### CallFunc

**매개변수가 없고, 메소드를 호출할 때만 사용**되는 액션이다.

CallFunc 액션은 생성할 때 **CC_CALLBACK_0 콜백형을 매개변수**로 받는다.

CC_CALLBACK_0의 0은 따로 **전달하는 매개변수가 없이 호출되는 메소드와 타겟만 지정**한다. 타깃은 특별한 경우를 제외하고 **거의 this**가 된다.

호출되는 메소드의 이름을 입력할 때는 ()는 빼고 **메소드의 이름만 입력**해야 된다.

</br>

```C++
bool HelloWorld::init()
{
    if (!Layer::init())
        return false;

    auto sprite = Sprite::create("ball.png");
    sprite->setPosition(Point(100, 100));
    this->addChild(sprite);

    auto move_action = MoveTo::create(3.0, Point(400, 100));
    auto delay_action = DelayTime::create(3.0);
    auto call_func_action = CallFunc::create(CC_CALLBACK_0(HelloWorld::setCallFunc_0, this));
    auto sequence_action = Sequence::create(move_action, delay_action, call_func_action, NULL);
    sprite->runAction(sequence_action);

    return true;
}
```
</br>

#### CallFuncN

메소드를 호출할 때 매개변수로 액션을 실행하는 객체 및 다른 특정한 값을 받는다.

</br>

```C++
bool HelloWorld::init()
{
    if (!Layer::init())
        return false;

    auto sprite = Sprite::create("ball.png");
    sprite->setPosition(Point(100, 100));
    this->addChild(sprite);

    auto move_action = MoveTo::create(3.0, Point(400, 100));
    auto delay_action = DelayTime::create(3.0);
    auto call_func_action = CallFuncN::create(CC_CALLBACK_1(HelloWorld::setCallFunc_1, this));      // 액션을 실행한 객체를 setCallFunc_1에 매개변수로 넘긴다.
    auto sequence_action = Sequence::create(move_action, delay_action, call_func_action, NULL);
    sprite->runAction(sequence_action);

    return true;
}

void HelloWorld::setCallFunc_1(Ref* sender)
{
    CCLOG("HelloWorld::setCallFunc_1()");

    auto sprite = (Sprite*)sender;                                                                  // 액션을 실행한 객체를 받아서
    sprite->setScale(2.0);                                                                          // 그 객체의 크기를 2배로 확대한다.
}
```
</br>


</br>

```C++
bool HelloWorld::init()
{
    if (!Layer::init())
        return false;

    auto sprite = Sprite::create("ball.png");
    sprite->setPosition(Point(100, 100));
    this->addChild(sprite);

    auto move_action = MoveTo::create(3.0, Point(400, 100));
    auto delay_action = DelayTime::create(3.0);
    auto call_func_action = CallFuncN::create(CC_CALLBACK_1(HelloWorld::setCallFunc_2, this, (void*)"cocos2d-x"));
    auto sequence_action = Sequence::create(move_action, delay_action, call_func_action, NULL);
    sprite->runAction(sequence_action);

    return true;
}

void HelloWorld::setCallFunc_2(Ref* sender, void* d)
{
    CCLOG("HelloWorld::setCallFunc_2() = %s", (char*)d);

    auto sprite = (Sprite*)sender;
    sprite->setScale(2.0);
}
```
</br>

</br>

```C++
bool HelloWorld::init()
{
    if (!Layer::init())
        return false;

    auto sprite = Sprite::create("ball.png");
    sprite->setPosition(Point(100, 100));
    this->addChild(sprite);

    auto sprite2 = Sprite::create("ball.png");
    sprite2->setPosition(Point(200, 200));
    this->addChild(sprite2);

    auto move_action = MoveTo::create(3.0, Point(400, 100));
    auto delay_action = DelayTime::create(3.0);
    auto call_func_action = CallFuncN::create(CC_CALLBACK_1(HelloWorld::setCallFunc_3, this, sprite2));
    auto sequence_action = Sequence::create(move_action, delay_action, call_func_action, NULL);
    sprite->runAction(sequence_action);

    return true;
}

void HelloWorld::setCallFunc_3(Ref* sender, Ref* object)
{
    CCLOG("HelloWorld::setCallFunc_3()");

    auto sprite = (Sprite*)sender;
    sprite->setScale(2.0);

    auto sprite2 = (Sprite*)object;
    sprite2->setScale(3.0);
}
```
</br>