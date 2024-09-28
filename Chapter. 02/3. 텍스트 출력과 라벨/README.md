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

위의 코드처럼 간단하게 라벨을 만드는 방법도 있지만, 라벨을 만들면서 **라벨의 영역도 지정하고, 또한 지정된 영역에서 어떻게 정렬할 것인지 지정할 수도 있다**.

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

위의 코드와 같이 입력하면 아래 그림과 같이 지정한 너비의 크기만큼 라벨이 출력되며, **지정한 크기를 초과할 경우에는 자동으로 줄 바꿈을 하게 된다**.

</br>

> auto label = Label::createWithSystemFont("Hello World", "Thonburi", 34, Size(150, 150), TextHAligment::LEFT);

위의 코드는 라벨을 생성할 때 문자열과 폰트 종류, 폰트 크기 다음으로 **라벨의 크기를 설정**한다.

또한 **글자의 가로 정렬을 지정할 수 있으며** 예제에서는 왼쪽으로 지정을 했다.

</br>

|종류|설명|
|----|----|
|TextHAlignment::CENTER|가운데 정렬|
|TextHAlignment::LEFT|왼쪽 정렬|
|TextHAlignment::RIGHT|오른쪽 정렬|

</br>

또한 **강제적으로 줄 바꿈을 하고 싶을 때는 입력하는 텍스트에 \n을 삽입**하면 된다.

위의 코드에서는 좌우 정렬은 왼쪽으로 지정했지만 **상하 정렬은 지정**하지 않았기 때문에 **기본값인 위쪽으로 설정**되어서 지정한 영역에서 왼쪽 상단에 라벨이 출력되는 것을 볼 수 있다.

</br>

```C++
bool HelloWorld::init()
{
    if(!Layer::init())
        return false;

    auto label = Label::createWithSystemFont("Hello World", "Thonburi", 34
                            , Size(150, 150), TextHAligment::CENTER, TextVAligment::CENTER);
    label->setPosition(Point(240, 160));
    this->addChild(label);

    return true;
}
```
</br>

> auto label = Label::createWithSystemFont("Hello World", "Thonburi", 34, Size(150, 150), TextHAligment::CENTER, TextVAligment::CENTER);

위의 코드에서 라벨을 생성할 때 매개변수의 마지막에 글자의 세로 정렬 값을 추가로 설정했다.

</br>

|종류|설명|
|----|----|
|TextVAlignment::CENTER|가운데 정렬|
|TextVAlignment::TOP|상단 정렬|
|TextVAlignment::BOTTOM|하단 정렬|

</br>

### 2.3.2 TTF

</br>

내장되어 있는 .ttf가 아닌 **외부에 있는 .ttf를 사용하고 싶을 때**는 해당 ttf 파일을 **Resources 폴더에 추가한 후 사용**하면 된다.

win32와 안드로이드의 경우, 아래와 같이 createWithTTF()에 출력할 텍스트와 폰트 이름에 파일 확장자까지 포함해서 입력하고 폰트에 크기를 입력한 후 사용하면 된다.

</br>

```C++
bool HelloWorld::init()
{
    if(!Layer::init())
        return false;

    auto label = Label::createWithTTF("Hello World", "PFStarDustS.ttf", 34);

    return true;
}
```
</br>

### 2.3.3 BMFont

</br>

BMFont는 비트맵 이미지로 만든 .png 파일과 폰트의 정보를 저장한 .fnt 파일을 가지고 글자를 출력하는 것이다.

BMFont를 사용하려면 먼저 앞서 말한 **.png, .fnt가 필요**하다. 따라서 이들을 **Resources 폴더에 추가한 후 사용**하면 된다.

</br>

```C++
bool HelloWorld::init()
{
    if ( !Layer::init() )
        return false;

    auto label = Label::createWithBMFont("bitmapFontChinese.fnt", "Hello World");
    label->setPosition(Point(240, 160));
    this->addChild(label);

    return true;
    
}
```
</br>

BMFont를 가장 일반적으로 사용하는 방법은 **createWithBMFont()에 .fnt 파일명과 출력할 텍스트를 입력**하는 것이다.

또한 사용하려는 **.fnt의 파일명과 .png의 파일명이 반드시 일치**해야만 한다.

그리고 폰트의 이미지가 비트맵 이미지로 지정되어 있기 때문에 따로 **폰트의 사이즈를 지정할 수 없다**.

</br>

위의 코드처럼 만든 라벨의 단점은 **한 줄로 밖에 표시를 할 수 없다**. 줄바꿈이 필요한 경우에는 아래의 코드처럼 **너비를 지정해서 줄 바꿈**을 할 수 있다.

그렇지만, 줄 바꿈은 띄어쓰기가 있는 경우에만 가능하며 **띄어쓰기가 없다면 너비를 초과해도 줄 바꿈이 발생하지 않는다**.

</br>

```C++
bool HelloWorld::init()
{
    if ( !Layer::init() )
        return false;

    auto label = Label::createWithBMFont("bitmapFontChinese.fnt", "Hello World", TextHAlignment::CENTER, 120);
    label->setPosition(Point(240, 160));
    this->addChild(label);

    return true;
}
```
</br>

> auto label = Label::createWithBMFont("bitmapFontChinese.fnt", "Hello World", TextHAlignment::CENTER, 120);

위의 코드에서 라벨을 만들면서 가로 정렬과 라벨의 너비의 크기를 매개변수로 설정했다.

</br>

### 2.3.4 CharMap

</br>

CharMap은 BMFont와 비슷하지만 **.fnt을 사용하지 않고 사용자가 파일의 정보를 직접 지정**할 수 있다.

따라서 사용자는 **이미지 파일을 제작할 때 글자의 순서를 아스키코드의 순서대로 제작**해야 하며, 각 **글자의 너비와 높이도 일치**해야 한다.

일반적으로 **CharMap은 숫자를 라벨로 출력할 때 많이 사용**한다. 게임에서는 숫자를 많이 사용하기 때문에 이미지로 사용하는 것이 더 효율적이기 때문이다.

</br>

```C++
bool HelloWorld::init()
{
    if(!Layer::init())
        return false;

    auto label = Label::createWithCharMap("labelatlas.png", 16, 32, '.');
    label->setString("012345");
    label->setAnchorPoint(Point(0.5, 0.5));
    label->setPosition(Point(240, 160));
    this->addChild(label);

    return true;
}
```
</br>

> auto label = Label::createWithCharMap("labelatlas.png", 16, 32, '.');

CharMap을 생성할 때는 **폰트의 내용이 있는 이미지 파일의 이름을 매개변수로 입력**하며, **각 글자의 너비와 높이를 차례대로 입력**한다.

그리고 **이미지에서 시작하는 아스키코드의 값을 매개변수로 입력**한다.

</br>

> label->setString("012345");

출력하고자 하는 내용은 setString() 메소드로 입력한다.

</br>

> label->setAnchorPoint(Point(0.5, 0.5));

**SystemFont, TTF와 BMFont의 기본 앵커포인트의 값은 (0.5, 0.5)**이지만, **CharMap의 기본 앵커포인트의 값은 (0, 0)**이다.

그래서 가운데에 출력하려고 하면 따로 앵커포인트를 지정해야 한다.

</br>

### 2.3.5 기타 메소드

</br>

스프라이트에 사용되는 기본적인 메소드 외에 라벨에서 많이 사용되는 메소드에는 setString()과 getString(), setColor() 등이 있다.

</br>

#### setString(), getString()

**setString()은 라벨의 내용을 변경**하는 메소드다.

setString()으로 새로운 텍스트를 입력하면 이전의 텍스트는 자동으로 지워지고, **라벨의 텍스트가 입력한 새로운 텍스트로 자동으로 변경**된다.

또한 **getString()를 호출하면 해당 라벨의 텍스트의 내용이 리턴**한다.

</br>

#### setColor()

setColor()는 **색상을 지정**하는 메소드다. 이 메소드는 다른 곳보다 **라벨에서 자주 사용**된다.

setColor()의 매개변수는 코코스2d-x에서 색상을 나타내는 자료형인 **Color3B**다.

</br>

#### enableShadow()

enableShadow()는 **그림자를 생성**하는 메소드다. 입력할 수 있는 매개변수는 2개다.

참고로 매개변수를 입력하지 않으면 검은색의 간격이 (2, -2)만큼 떨어진 그림자가 기본적으로 생성된다.

</br>

> enableShadow(const Color4B& shadowColor, const Size& offset)

|매개변수|설명|
|-------|----|
|shadowColor|그림자의 색상을 지정한다.|
|offset|라벨과 그림자의 간격을 지정한다.|

</br>

#### enableOutline()

enableOutline()는 외곽선을 생성하는 메소드다. 입력할 수 있는 매개변수는 2개다.

참고로 외곽선 두께를 지정하지 않으면 두께가 1인 외곽선이 생성된다. 그리고 외곽선 효과는 TTF에만 적용된다.

> enableOutline(const Color4B& outlineColor, int outlineSize)

|매개변수|설명|
|-------|----|
|outlineColor|외곽선 색상을 지정한다.|
|outlineSize|외곽선 두께를 지정한다.|

</br>
</br>

```C++
bool HelloWorld::init()
{
    if(!Layer::init())
        return false;

    auto label_0 = Label::createWithSystemFont("Hello World", "Thonburi", 50);
    label_0->setPosition(Point(240, 220));
    label_0->setColor(Color3B(255, 0, 0));
    this->addChild(label_0);

    auto label_1 = Label::createWithSystemFont("Shadow", "Thonburi", 50);
    label_1->setPosition(Point(240, 160));
    label_1->enableShadow(Color4B::BLUE, Size(2, -2));
    this->addChild(label_1);

    auto label_2 = Label::createWithTTF("Outline", "arial.ttf", 50);
    label_2->setPosition(Point(240, 100));
    label_2->enableOutline(Color4B::RED, 2);
    this->addChild(label_2);

    return true;
}
```
</br>

위의 코드를 보면 라벨에 색상들을 지정할 수 있다. 색상은 Color3B와 Color4B로 지정한다.

Color3B는 R, G, B 값으로 구성된 색상 자료형이다. 색상값은 다음과 같이 지정되어 있다.

</br>

|종류|삽입|
|----|----|
|Color3B::WHITE|흰색|
|Color3B::YELLOW|노란색|
|Color3B::BLUE|파란색|
|Color3B::GREEN|녹색|
|Color3B::RED|빨간색|
|Color3B::MAGENTA|자홍색|
|Color3B::BLACK|검은색|
|Color3B::ORANGE|오렌지색|
|Color3B::GRAY|회색|

</br>