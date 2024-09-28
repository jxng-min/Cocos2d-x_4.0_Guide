## 2.4 메뉴 버튼 생성

</br>

메뉴는 게임에서 **메뉴 버튼을 만들 때 사용되는 객체**다.

</br>

```C++
bool HelloWorld::init()
{
    if(!Layer::init())
        return false;

    auto item_1 = MenuItemImage::create("btn-play-normal.png", "btn-play-selected.png", CC_CALLBACK_1(HelloWorld::menuCallback, this));
    auto item_2 = MenuItemImage::create("btn-highscores-normal.png", "btn-highscores-selected.png", CC_CALLBACK_1(HelloWorld::menuCallback, this));
    auto item_3 = MenuItemImage::create("btn-about-normal.png", "btn-about-selected.png", CC_CALLBACK_1(HelloWorld::menuCallback, this));

    auto menu = Menu::create(item_1, item_2, item_3, NULL);
    menu->alignItemsVertically();
    this->addChild(menu);
    
    return true;
}
```

void HelloWorld::menuCallback(Ref* sender)
{
    CCLOG("menuCallback");
}
</br>

**메뉴는 메뉴 아이템으로 구성**되며, 위에서는 Play, High Score, About 메뉴 아이템으로 구성되어 있다.

메뉴 아이템을 **클릭하면 선택되었을 때 보여지는 이미지로 변경**되며, **선택한 후 메소드를 호출하는 기능**도 가지고 있다.

</br>

### 2.4.1 메뉴 아이템

</br>

#### MenuItemFont

</br>

```C++
bool HelloWorld::init()
{
    if (!Layer::init())
        return false;

    auto item_1 = MenuItemFont::create("Play", CC_CALLBACK_1(HelloWorld::menuCallback, this));
    auto item_2 = MenuItemFont::create("High Scores", CC_CALLBACK_1(HelloWorld::menuCallback, this));
    auto item_3 = MenuItemFont::create("About", CC_CALLBACK_1(HelloWorld::menuCallback, this));

    auto menu = Menu::create(item_1, item_2, item_3, NULL);
    menu->alignItemsVertically();
    this->addChild(menu);

    return true;
}
```
</br>

> auto item_1 = MenuItemFont::create("Play", CC_CALLBACK_1(HelloWorld::menuCallback, this));

MenuItemFont는 가장 간단하게 사용할 수 있는 메뉴 아이템으로 **메뉴로 사용할 텍스트를 직접 입력해서 간단하게 메뉴 아이템을 만들 수 있다**.

MenuItemFont는 지정한 텍스트로 메뉴 아이템이 만들어지며, **클릭하면 글자가 조금 커지면서 선택**되었다는 것을 알 수 있다.

메뉴 아이템의 텍스트를 입력한 후 선택되었을 때 **호출될 메소드와 타겟을 지정**하면 된다.

</br>

호출되는 메소드는 메소드 이름을 입력하는 것이 아니라 **CC_CALLBACK_1()으로 정의된 콜백 메소드를 이용하여 호출**해야 한다.

또한 호출한 메소드 이름을 지정할 때는 **매개변수 부분은 생략하고 오직 메소드 이름만 입력**하면 된다.

즉, menuCloseCallback(Ref* sender)의 경우에는 ()부분을 제외하고 menuCloseCallback이라고 입력하면 된다.

또한 **콜백 메소드의 숫자는 전달되는 매개변수의 개수**를 말한다.

</br>

> sender       
> 코코스2d-x 소스를 보면 매개변수가 sender인 것을 많이 관찰할 수 있다.       
> 대부분의 경우 sender는 직접 어떠한 매개변수를 입력하는 것보다 **해당 메소드를 호출하는 주체인 경우가 많다**.       
> menuCallback(Ref* sender) 경우에도 **해당 메소드를 CC_CALLBACK_1()를 통해서 호출**하게 되면, 호출될 때 **해당 메뉴 아이템의 포인터가 sender에 자동으로 전달**되게 된다.

</br>

```C++
void HelloWorld::menuCallback(Ref* sender)
{
    CCLOG("menuCallback");

    auto item = (MenuItemFont*)sender;
}
```
</br>

#### MenuItemLabel

</br>

MenuItemFont는 메뉴 아이템의 내용을 바로 입력하는 반면 MenuItemLabel은 텍스트를 Label로 만들어서 메뉴 아이템을 만든다.

그렇기 때문에 **MenuItemFont의 경우는 폰트의 크기나 색상 등을 직접 지정할 수 없다**.

하지만 **MenuItemLabel의 경우는 Label을 만들어서 메뉴 아이템을 만들기 때문에 좀 더 다양하게 활용**할 수 있다.

</br>

```C++
bool HelloWorld::init()
{
    if(!Layer::init())
        return false;

    auto label_1 = Label::createWithSystemFont("Play", "Thonburi", 50);
    auto label_2 = Label::createWithSystemFont("High Scores", "Thonburi", 50);
    auto label_3 = Label::createWithSystemFont("About", "Thonburi", 50);

    auto item_1 = MenuItemLabel::create(label_1, CC_CALLBACK_1(HelloWorld::menuCallback, this));
    auto item_2 = MenuItemLabel::create(label_2, CC_CALLBACK_2(HelloWorld::menuCallback, this));
    auto item_3 = MenuItemLabel::create(label_3, CC_CALLBACK_3(HelloWorld::menuCallback, this));

    auto menu = Menu::create(item_1, item_2, item_3, NULL);
    menu->alignItemsVertically();
    this->addChild(menu);

    return true;
}
```
</br>

사용법은 MenuItemFont와 동일하지만 메뉴 문구를 직접 입력하지 않고, 해당 문구로 라벨을 만든 후 라벨을 사용한다는 점에서 다르다.

</br>

#### MenuItemImage

</br>

MenuItemImage는 .png로 메뉴를 만드는 것으로 **입력 상태에서 보여지는 이미지와 선택되었을 때 보여지는 이미지를 다르게 지정**할 수 있다.

또한 **비활성화 상태일 때 보여지는 이미지도 지정**할 수 있다.

</br>

```C++
bool HelloWorld::init()
{
    if(!Layer::init())
        return false;

    auto item_1 = MenuItemImage::create("btn-play-normal.png", "btn-play-selected.png", "btn-play-selected.png", CC_CALLBACK_1(HelloWorld::menuCallback, this));
    auto item_2 = MenuItemImage::create("btn-highscores-normal.png", "btn-highscores-selected.png", CC_CALLBACK_1(HelloWorld::menuCallback, this));
    auto item_3 = MenuItemImage::create("btn-about-normal.png", "btn-about-selected.png", CC_CALLBACK_1(HelloWorld::menuCallback, this));

    auto menu = Menu::create(item_1, item_2, item_3, NULL);
    menu->alignItemsVertically();
    this->addChild(menu);

    item_1->setEnabled(false);

    return true;
}
```
</br>

메뉴가 비활성화 상태인 경우 메뉴 아이템을 클릭해도 아무런 반응을 하지 않는다.

</br>

> auto item_1 = MenuItemImage::create("btn-play-normal.png", "btn-play-selected.png", "btn-play-selected.png", CC_CALLBACK_1(HelloWorld::menuCallback, this));

item_1의 경우 일반 이미지와 선택 이미지를 입력하고 **비활성화일 때 보이는 이미지를 3번째 항목으로 입력**했다.

이렇게 3번째 매개변수로 비활성화 이미지를 입력하면 **메뉴 아이템이 비활성화될 경우 비활성화 이미지가 보인다**.

</br>

> item_1->setEnabled(false);

setEnabled()는 **객체의 활성화 여부를 설정**하는 메소드다.

기본값은 활성화 상태로 되어 있으며 매**개변수로 false로 입력하면 객체가 비활성화** 된다.

비활성화 상태에서는 선택도 되지 않고, 메소드도 호출할 수 없다.

</br>

#### MenuItemSprite

MenuItemSprite는 MenuItemImage와 거의 동일하지만 이미지가 아닌 스프라이트로 만든다는 것이 다르다.

MenuItemImage로 메뉴 아이템을 만들 경우에는 이미지의 변경이 불가능하지만 **MenuItemSprite로 만들 경우에는 스프라이트의 메소드를 사용해서 크기, 알파값 등의 변경이 가능**하다.

</br>

```C++
bool HelloWorld::init()
{
    if (!Layer::init())
        return false;

    auto spr_1_n = Sprite::create("btn-play-normal.png");
    auto spr_1_s = Sprite::create("btn-play-selected.png");
    auto spr_2_n = Sprite::create("btn-highscores-normal.png");
    auto spr_2_s = Sprite::create("btn-highscores-selected.png");
    auto spr_3_n = Sprite::create("btn-about-normal.png");
    auto spr_3_s = Sprite::create("btn-about-selected.png");

    spr_3_n->setScaleY(0.5);

    auto item_1 = MenuItemSprite::create(spr_1_n, spr_1_s, CC_CALLBACK_1(HelloWorld::menuCallback, this));
    auto item_2 = MenuItemSprite::create(spr_2_n, spr_2_s, CC_CALLBACK_1(HelloWorld::menuCallback, this));
    auto item_3 = MenuItemSprite::create(spr_3_n, spr_3_s, CC_CALLBACK_1(HelloWorld::menuCallback, this));

    auto menu = Menu::create(item_1, item_2, item_3, NULL);
    menu->alignItemsVertically();
    this->addChild(menu);

    return true;
}
```
</br>

위의 예제에서는 spr_3_s의 세로 크기를 0.5로 축소했기 때문에 축소된 이미지로 보인다.

</br>

#### MenuItemToggle

</br>

MenuItemToggle은 이미 생성했던 메뉴 아이템을 가지고 Toggle 아이템을 생성한다.

</br>

```C++
bool HelloWorld::init()
{
    if(!Layer::init())
        return false;

    auto item_1_1 = MenuItemImage::create("btn-play-normal.png", "btn-play-selected.png");
    auto item_1_2 = MenuItemImage::create("btn-highscores-normal.png", "btn-highscores-selected.png");

    auto item_1 = MenuItemToggle::createWithCallback(CC_CALLBACK_1(HelloWorld::menuCallback, this), item_1_1, item_1_2, NULL);
    auto item_2 = MenuItemImage::create("btn-about-normal.png", "btn-about-selected.png", CC_CALLBACK_1(HelloWorld::menuCallback, this));

    auto menu = Menu::create(item_1, item_2, NULL);
    menu->alignItemsVertically();
    this->addChild(menu);

    return true;
}
```
</br>

> auto item_1_1 = MenuItemImage::create("btn-play-normal.png", "btn-play-selected.png");
> auto item_1_2 = MenuItemImage::create("btn-highscores-normal.png", "btn-highscores-selected.png");

먼저 토글 아이템에서 사용될 메뉴 아이템을 생성한다. **토글 아이템은 각 메뉴 아이템의 콜백 메소드가 호출되지 않고 토글 아이템의 콜백 메소드가 호출**된다.

따라서 **토글 아이템에 사용될 메뉴 아이템을 만들 때는 일반적으로 콜백 메소드를 지정하지 않는다**.

</br>

> auto item_1 = MenuItemToggle::createWithCallback(CC_CALLBACK_1(HelloWorld::menuCallback, this), item_1_1, item_1_2, NULL);

생성한 메뉴 아이템을 가지고 createWithCallback() 메소드로 토글 아이템을 생성한다.

토글 아이템을 만드는 메소드는 콜백 메소드를 먼저 입력한 후 토글 아이템에 사용될 메뉴 아이템의 이름을 차례대로 입력한다. 그리고 마지막엔 반드시 NULL을 입력해야 한다.

</br>

### 2.4.2 메뉴 위치 설정

</br>

메뉴는 **메뉴 아이템의 자동 정렬을 제공**하는 것 외에는 특별한 기능을 가지고 있지 않다.

여러 개의 메뉴 아이템으로 메뉴를 생성해서 특별한 설정을 하지 않고 **바로 addChild()를 하면 화면에 여러 개가 아닌 마지막에 입력한 아이템만 보이게 된다**.

이유는 메뉴 아이템의 Position 값을 따로 지정하지 않았고, 또한 메뉴에서 제공하는 자동 정렬 기능을 사용하지도 않았기 때문에 **같은 위치에 메뉴 아이템이 여러 개 생성**된다.

</br>

메뉴의 위치를 설정하는 방법은 2가지 방법이 있다.

* 각 메뉴 아이템에 원하는 위치를 지정하는 방법
* 메뉴에서 제공하는 자동 정렬 기능을 사용하는 방법

</br>

#### alignItems

</br>

alignItems의 종류는 세로로 정렬해주는 **alignItemsVertically()**와 가로로 정렬해주는 **alignItemsHorizontally()**가 있다.

이 두 개의 메소드를 사용하면 **자동으로 세로 또는 가로로 메뉴 아이템을 정렬**하며, **메뉴 아이템의 간격은 코코스2d-x에서 지정된 값**으로 된다.

**메뉴 아이템의 간격을 따로 지정**하고 싶으면 **alignItemsVerticallyWithPadding()과 alignItemsHorizontallyWithPadding()에서 매개변수로 원하는 간격을 입력**하면 된다.

</br>

#### setPosition()을 통한 위치 지정

</br>

setPosition() 메소드를 이용해 각 위치를 지정하기 위해서는 메뉴 아이템, 메뉴의 기본 앵커포인트와 기본 위치 값을 알아야 한다.

</br>

|    |MenuItem|Menu|
|----|--------|----|
|AnchorPoint|(0.5, 0.5)|(0, 0)|
|Position|(0, 0)|(winSize.width/2, winSize.height/2)|

위의 표와 같이 MenuItem과 Menu의 기본 앵커포인트 및 기본 위치 값이 다르다.

사용자가 **다른 설정을 하지 않을 경우에는 메뉴 아이템의 위치가 부모에 위치 기준 값인 화면 가운데에 그려진다**.

</br>

메뉴 아이템의 위치를 화면에 출력하고 싶은 **위치로 지정할 때는 잊지 말고 메뉴에 앵커포인트와 위치를 (0, 0)으로 변경**해야 한다.

이렇게 변경해야 비로소 각 메뉴 아이템이 제대로 된 위치에 출력되는 것을 볼 수 있다.