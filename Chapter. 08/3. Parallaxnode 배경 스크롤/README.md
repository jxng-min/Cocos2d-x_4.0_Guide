## ParallaxNode 배경 스크롤

</br>

ParallaxNode는 배경 스크롤을 구현할 때 **각 이미지에 액션 기능을 적용하지 않는다**.

대신 **ParallaxNode에 액션 기능을 적용**하고 **스프라이트를 ParallaxNode에 추가하면서 이동 비율 등을 지정**하는 방식이다.

그래서 ParallaxNode의 addChild()는 지금까지의 addChild()와 조금 다르다.

</br>

```C++
void addChild(Node* child, int z, const Point& parallaxRatio, const Point& positionOffset);
```
</br>

|매개변수|설명|
|-------|----|
|child|추가할 Node를 입력한다.|
|z|z-order의 값을 입력한다.|
|parallaxRatio|ParallaxNode의 이동속도를 기준으로 추가되는 스프라이트의 이동비율을 입력한다.|
|positionOffset|ParallaxNode에 추가되는 좌표를 입력한다.|

</br>

parallaxRatio의 입력형은 Point이지만 좌표를 나타내는 것이 아니라 **x축 방향의 이동비율과 y축 방향의 이동비율**을 나타낸다.

또한, positionOffset에서 좌표를 미리 입력하기 때문에 **스프라이트를 생성할 때는 따로 setPosition()을 설정하지 않는다**.

</br>

```C++
void GameScene::InitBackground()
{
    auto node = ParallaxNode::create();
    this->addChild(node);

    auto move_action = MoveBy::create(10.0, Point(-2000, 0));
    auto place_action = Place::create(Point::ZERO);
    auto sequence_action = Sequence::create(move_action, place_action, NULL);
    auto repeat_action = RepeatForever::create(sequence_action);
    node->runAction(repeat_action);

    auto background_sprite1 = Sprite::create("bg1.png");
    background_sprite1->setAnchorPoint(Point::ZERO);
    node->addChild(background_sprite1, 0, Point(1, 0), Point::ZERO);

    auto background_sprite2 = Sprite::create("bg1.png", Rect(0, 0, 480, 320));
    background_sprite2->setAnchorPoint(Point::ZERO);
    node->addChild(background_sprite2, 0, Point(1, 0), Point(2000, 0));

    auto background_sprite3 = Sprite::create("bg2.png");
    background_sprite3->setAnchorPoint(Point::ZERO);
    node->addChild(background_sprite3, 1, Point(2, 0), Point::ZERO);

    auto background_sprite4 = Sprite::create("bg2.png");
    background_sprite4->setAnchorPoint(Point::ZERO);
    node->addChild(background_sprite4, 1, Point(2, 0), Point(2000, 0));

    auto background_sprite5 = Sprite::create("bg2.png", Rect(0, 0, 480, 114));
    background_sprite5->setAnchorPoint(Point::ZERO);
    node->addChild(background_sprite5, 1, Point(2, 0), Point(4000, 0));
}
```
</br>

> auto node = ParallaxNode::create();    
> this->addChild(node);    

ParallaxNode를 이용할 때는 Layer가 아닌 **ParallaxNode를 생성**한다.

ParallaxNode를 사용할 경우에는 **배경 레이어를 따로 생성할 필요가 없다**.

</br>

> node->runAction(repeat_action);

기준이 되는 이미지인 bg1.png의 크기만큼 이동하는 **액션 기능을 ParallaxNode에 적용**한다.

</br>

> node->addChild(background_sprite1, 0, Point(1, 0), Point::ZERO);
> node->addChild(background_sprite2, 0, Point(1, 0), Point(2000, 0));

배경이 되는 이미지를 스프라이트로 만들어서 ParallaxNode에 추가한다.

bg1.png는 z-order의 값은 0으로 하고, **x축의 이동속도는 ParallaxNode의 이동속도와 동일한 1로 설정**한다. y축으로는 이동하지 않기 때문에 0으로 설정한다.

bg1.png로 만든 첫 번째 스프라이트의 오프셋 위치는 Point::ZERO로 설정하였으며, **두 번째 스프라이트는 이미지 크기만큼 뒤로 설정**한다.

</br>

> node->addChild(background_sprite3, 0, Point(2, 0), Point::ZERO);    
> node->addChild(background_sprite4, 0, Point(2, 0), Point(2000, 0));    
> node->addChild(background_sprite5, 0, Point(2, 0), Point(4000, 0));    

bg2.png로 만드는 스프라이트는 bg1.png으로 만든 스프라이트보다 위에 있어야 하기 때문에 **z-order의 값을 1로 설정**하고, **이동속도를 ParallaxNode의 2배로 설정**한다.

</br>

ParallaxNode의 기본 이동거리는 2000픽셀이다. **bg2.png는 2배의 속도로 이동하기 때문에 같은 시간에 2000픽셀의 2배인 4000픽셀을 이동**한다.

그래서 bg2.png는 2배에 해당하는 **2개의 스프라이트를 생성**해야 하며, 화면사이즈인 **480픽셀 크기만큼 이미지도 추가로 만들어서 연결해야 끊김 현상이 보이지 않는다**.

이렇게 다중 레이어 스크롤을 할 때는 기본 액션의 이동거리에 각 이미지들의 이동거리를 계산해서 이동거리에 맞게 이미지를 추가해줘야 한다.

</br>

ParallaxNode는 각 이미지에 액션 기능을 적용해서 스크롤하는 것보다 훨씬 쉽고 간단하게 스크롤을 구현해준다.

하지만, 적용할 때 화면 끊김 현상이 일어나지 않도록 스크롤되는 이미지의 크기와 속도를 계산하는 것이 쉽지는 않지만 이를 계산해야 한다.

또한 **배경의 이미지를 한 개만 스크롤할 때는 오히려 ParallaxNode를 사용하지 않는 것이 효율적**이다.