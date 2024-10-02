## 스케쥴

</br>

코코스2d-x에서는 **타이머**를 스케쥴이라고 한다.

스케쥴을 구현하는 방법은 입력하는 매개변수에 따라 달라질 수 있다.

코코스2d-x로 게임을 만들 때는 **C++에서 제공하는 기본적인 타이머를 사용하는 것보다 스케줄을 사용하는 것을 권장**한다.

</br>
</br>

### 7.3.1 schedule

</br>

```C++
bool GameScene::init()
{
    if (!Layer::init())
        return false;

    this->schedule(CC_SCHEDULE_SELECTOR(GameScene::ScheduleCallback), 1.0);

    return true;
}

void ScheduleCallback(float delta)
{
    CCLOG("ScheduleCallback: %f", delta);
}
```
</br>

> this->schedule(CC_SCHEDULE_SELECTOR(GameScene::ScheduleCallback), 1.0);

schedule()의 **첫 번째 매개변수**는 **호출하는 메소드**의 이름이다. 하지만, 이름을 바로 입력하지 않고 **셀렉터를 통해서 메소드를 호출**하고 있다.

설렉터에 메소드를 입력할 때는 매개변수를 입력하지 않고 클래스명과 메소드명만 입력한다.

schedule()의 **두 번째 매개변수**는 **메소드를 호출하는 시간 간격**이다.

</br>

```C++
void ScheduleCallback(float delta)
{
    CCLOG("ScheduleCallback: %f", delta);
}
```
</br>

호출되는 ScheduleCallback()에서는 ScheduleCallback 문자열과 매개변수로 입력받은 delta 값을 결과창에 출력하고 있다.

**delta** 값은 따로 입력하는 것이 아니라 스케쥴에 의해서 호출되는 메소드인 경우에는 **직전에 메소드가 호출된 시간과 현재 메소드가 호출된 시간에 차이 값이 자동으로 입력**된다.

그래서 **결과창에 출력된 값을 보면 1.0보다 조금 큰 수가 출력**되고 있는 것을 확인할 수 있다.

</br>

스케쥴 메소드에서는 간격을 1.0초보다 조금 큰 값으로 한 이유는 **스케쥴 메소드가 호출되는 시간이 AppDelegate.cpp에서 설정한 setAnimationInterval()의 시간에 종속되기 때문**이다.

게임이 실행되는 메인 애니메이션의 시간 간격을 1.0 / 10인 0.1초로 지정했을 경우, 아무리 스케쥴에 시간 간격을 0.05초로 설정해도 스케쥴은 메인 애니메이션의 시간 간격인 0.1초마다 호출된다.

그래서 메인 애니메이션의 시간 간격이 1.0 / 60인 약 0.0016초이기 때문에 정확하게 1.0초마다 스케쥴 함수가 호출되는 것이 아니라 **0.016초마다 호출되는 메인 애니메이션 타이머에서 1.0초가 지난 직후에 호출**된다.

그래서 콘솔 창에 1.0초보다 조금 큰 값이 출력되는 것이다.

</br>

```C++
bool GameScene::init()
{
    if(!Layer::init())
        return false;

    this->schedule(CC_SCHEDULE_SELECTOR(GameScene::ScheduleCallback), 1.0, 5, 5.0);    // 처음에 5초 동안 대기하고 한 번 호출되고 그 뒤로 1초 간격으로 5번 호출

    return true;
}
```
</br>

> this->schedule(CC_SCHEDULE_SELECTOR(GameScene::ScheduleCallback), 1.0, 5, 5.0);

첫 번째와 두 번째 매개변수는 위의 코드와 동일하다. **세 번째 매개변수는 반복 횟수를 지정**하는 것이다.

따라서 무한으로 메소드를 호출하는 것이 아니라 **반복 횟수만큼 메소드를 호출**하게 된다.

**네 번째 매개변수는 처음에 기다리는 대기시간을 설정**한다.

</br>

```C++
bool GameScene::init()
{
    if(!Layer::init())
        return false;

    this->schedule(CC_SCHEDULE_SELECTOR(GameScene::ScheduleCallback));

    return true;
}
```
</br>

> this->schedule(CC_SCHEDULE_COLLECTOR(GameScene::ScheduleCallback));

위의 코드는 매개변수가 호출하는 메소드의 이름을 입력하는 것 밖에는 없다.

호출하는 메소드만 매개변수로 입력할 경우에는 **호출되는 간격이 AppDelegate.cpp에서 지정한 메인 애니메이션 시간 간격으로 호출**된다.

</br>
</br>

### 7.3.2 scheduleUpdate()

</br>

```C++
bool GameScene::init()
{
    if(!Layer::init())
        return false;

    this->scheduleUpdate();

    return true;
}
```
</br>

> this->scheduleUpdate();

scheduleUpdate()는 메소드의 이름을 지정하지 않고 **무조건 update()를 호출**하게 된다.

그래서 **scheduleUpdate()를 사용할 때는 반드시 update()를 구현**해야만 한다.

그리고 시간 간격도 따로 지정하지 않기 때문에 **메인 애니메이션 시간 간격으로 호출**된다.

</br>
</br>

### 7.3.3 scheduleOnce()

</br>

```C++
bool GameScene::init()
{
    if(!Layer::init())
        return false;

    this->scheduleOnce(CC_SCHEDULE_SELECTOR(GameScene::ScheduleCallback), 5.0);

    return true;
}
```
</br>

> this->scheduleOnce(CC_SCHEDULE_SELECTOR(GameScene::ScheduleCallback), 5.0);

scheduleOnce()는 **오직 한 번만 호출**되며, **두 번째 매개변수로 입력한 시간만큼 대기한 후에 첫 번째 매개변수로 입력한 메소드가 호출**된다.

</br>
</br>

### 7.3.4 그 외의 스케쥴 메소드

위에서 정리한 5가지 스케쥴 메소드 외에도 여러가지 스케쥴 메소드가 존재한다.

여러 개의 레이어가 있는 화면에서 여러 개의 scheduleUpdate()를 호출했을 때 실행되는 우선순위를 부여하는 scheduleUpdateWithPriority()도 있다.

</br>

호출한 스케쥴이 더 이상 사용되지 않아서 중지하고 싶을 때에는 다음과 같이 중지할 수 있다.

</br>

* unschedule(CC_SCHEDULE_SELECTOR(호출할 메소드명)): 한 개의 스케쥴만 중지할 때 사용
* unscheduleAllSelectors(): 호출한 모든 스케쥴을 중지할 때 사용
* unscheduleUpdate(): update() 스케쥴만 중지할 때 사용 