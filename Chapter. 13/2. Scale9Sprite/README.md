## Scale9Sprite

</br>

게임에서 사용되는 팝업 이미지는 표시되는 내용에 따라서 크기가 달라지는 경우가 많다.

**표시되는 내용이 가변적일 경우**에는 크기를 고정하는 것이 어렵기 때문에 코코스2d-x에서는 **Scale9Sprite**를 제공한다.

Scale9Sprite를 사용하기 위해서는 **cocos-ext.h를 추가**해야 하며, **USING_NS_CC_EXT와 using namespace ui를 추가**해야 한다.

</br>

Scale9Sprite는 사각형 스프라이트를 생성할 때 지정된 **이미지를 9등분해서 각 조각을 조합해서 화면에 출력**한다.

</br>

```C++
bool GameScene::init()
{
    if(!Layer::init())
        return false;

    auto sprite9 = Scale9Sprite::create("HelloWorld.png");
    sprite9->setContentSize(Size(300, 300));
    sprite9->setPosition(Point(240, 160));
    this->addChild(sprite9);

    return true;
}
```
</br>

![화면 캡처 2024-10-14 185914](https://github.com/user-attachments/assets/dc5d4278-949b-4e36-bf62-a5d5f8793ff0)

</br>

일반적인 **스프라이트의 경우 setContentSize()를 사용해도 동작하지 않는다**. 하지만 **Scale9Sprite의 경우에는 설정한 컨텐츠의 크기만큼 확대**가 된다.

setScale()을 이용하여 확대한 것과는 큰 차이를 가진다. **Scale9Sprite는 setContentSize()로 이미지를 9등분해서 새로운 스프라이트를 만든다**.

</br>

![images](https://github.com/user-attachments/assets/a9729c58-505e-4344-b28a-2ab625a2f4fd)

</br>

Scale9Sprite를 사용해서 새로운 스프라이트를 만들 때는 **모서리가 되는 1, 3, 7, 9번 이미지의 크기는 변하지 않고 모서리에 위치**하게 된다.

**2, 8번 이미지는 높이의 크기는 변하지 않고 너비의 크기만 확대**되고, **4, 6번 이미지는 너비의 크기는 변하지 않고 높이의 크기만 확대**된다.

그리고 가운데 **5번 이미지는 스프라이트 크기에 맞게 너비와 높이가 모두 확대**된다.

또한 Scale9Sprite를 생성할 때는 **가운데 이미지의 영역을 따로 지정**할 수 있으며 이 경우 **나머지 이미지의 영역도 자동으로 지정되므로 더 자연스럽다**.

</br>

```C++
bool GameScene::init()
{
    if(!Layer::init())
        return false;

    auto sprite9 = Scale9Sprite::create("HelloWorld.png", Rect(0, 0, 195, 270), Rect(7, 7, 195 - 7 * 2, 270 - 7 * 2));
    sprite9->setContentSize(Size(300, 300));
    sprite9->setPosition(Point(240, 160));
    this->addChild(sprite9);

    return true;
}
```
</br>

위의 코드는 Scale9Sprite를 생성할 때 가운데 영역의 크기를 지정한다.

</br>
</br>

> auto sprite9 = Scale9Sprite::create("HelloWorld.png", Rect(0, 0, 195, 270), Rect(7, 7, 195 - 7 * 2, 270 - 7 * 2));

|매개변수|설명|
|--------|----|
|HelloWorld.png|이미지 파일의 이름을 입력한다.|
|Rect(0, 0, 195, 270)|원본 이미지에서 Scale9Sprite를 생성할 때 사용되는 이미지 영역을 입력한다.|
|Rect(7, 7, 195 - 7 * 2, 270 - 7 * 2)|5번 조각에 해당되는 이미지의 영역을 입력한다.|

</br>

위의 예제에서는 이미지 파일에서 상하좌우 7픽셀을 제외한 가운데 부분을 5번 조각으로 사용한다.

</br>

![화면 캡처 2024-10-14 193945](https://github.com/user-attachments/assets/8bd7cf40-4d16-4542-a0f5-38c87cdb1686)

</br>

이렇게 **Scale9Sprite를 사용해서 사각형 이미지를 만들면 팝업 테두리에 해당되는 이미지는 깨지지 않고 확대**되는 것을 확인할 수 있다.

</br>
</br>

### 13.2.1 Sprite와 Scale9Sprite의 비교

</br>

```C++
bool GameScene::init()
{
    if(!Layer::init())
        return false;

    auto sprite = Sprite::create("green_edit.png");
    sprite->setScale(3.0);
    sprite->setPosition(Point(100, 160));
    this->addChild(sprite);

    auto sprite9 = Scale9Sprite::create("green_edit.png");
    sprite9->setContentSize(Size(28 * 3, 28 * 3));
    sprite9->setPosition(Point(300, 160));
    this->addChild(sprite9);

    return true;
}
```

</br>

![화면 캡처 2024-10-14 194917](https://github.com/user-attachments/assets/abb1734a-37b1-4203-bef9-6e12d450246b)

</br>

스프라이트로 생성해서 3배 확대하면 외곽선의 이미지가 깨져서 사용하기가 어렵다.

반면에, Scale9Sprite로 3배 확대해서 생성하면 **외각선의 이미지는 깨지지 않고 확대**된다.
