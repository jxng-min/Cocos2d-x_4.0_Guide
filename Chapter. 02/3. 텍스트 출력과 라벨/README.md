## 2.3 텍스트 출력

</br>

이미지를 출력하는 것과 함께 게임을 만들 때 많이 사용되는 것이 텍스트를 화면에 출력하는 것이다.

코코스2d-x에서 텍스트를 출력하려면 라벨 객체를 생성해야 한다.

라벨은 단순히 텍스트만 가지고 있는 것이 아니라 위치 값, 앵커포인트 등 정보 값을 함께 가지고 있는 객체다.

라벨의 종류는 SystemFont, TTF, BMFont, CharMap이 있다.

</br>

### 2.3.1 SystemFont

</br>

SystemFont는 내장되어 있는 TTF를 사용해서 글자를 화면에 출력하는 것이다. 물론 .ttf를 추가해서 추가한 TTF를 사용할 수도 있다.

</br>

```C++
bool HelloWorld::init()
{
    if(!Layer::init())
        return false;

    auto label = Label::createWithSystemFont("Hello World", "Thonburi", 34);
    label->setPosition(Point(240, 160));
    this->addChild(label);

    return true;
}
```
</br>

> auto label = Label::createWithSystemFont("Hello World", "Thonburi", 34);

Label을 생성하는 가장 기본적인 방법으로 매개변수로 **출력하려는 문자열, 폰트의 이름, 폰트의 크기를 입력**한다.

만약 입력한 폰트의 이름이 잘못되었거나 내장되어 있지 않은 폰트라면 기본 폰트로 출력된다.

</br>

위의 코드처럼 간단하게 라벨을 만드는 방법도 있지만, 라벨을 만들면서 라벨의 영역도 지정하고, 또한 지정된 영역에서 어떻게 정렬할 것인지 지정할 수도 있다.

</br>

```C++
bool HelloWorld::init()
{
    if(!Layer::init())
        return false;

    auto label = Label::createWithSystemFont("Hello World", "Thonburi", 34
                            , Size(150, 150), TextHAligment::LEFT);
    label->setPosition(Point(240, 160));
    this->addChild(label);

    return true;
}
```
</br>