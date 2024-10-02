## 다중 이미지 배경 스크롤

</br>

다중 이미지 배경 스크롤을 구현하기 위해서 bg1.png와 bg2.png를 프로젝트에 추가한다.

그리고 bg1.png와 동일하게 액션 기능을 적용한다.

</br>

```C++
void GameScene::InitBackground()
{
    auto background_layer1 = Layer::create();
    this->addChild(background_layer1);

    auto background_sprite1 = Sprite::create("bg1.png");
    background_sprite1->setAnchorPoint(Point::ZERO);
    background_sprite1->setPosition(Point::ZERO);
    background_layer1->addChild(background_sprite1);

    auto background_sprite2 = Sprite::create("bg1.png", Rect(0, 0, 480, 320));
    background_sprite2->setAnchorPoint(Point::ZERO);
    background_sprite2->setPosition(Point(2000, 0));
    background_layer1->addChild(background_sprite2);

    auto move_action1 = MoveBy::create(10.0, Point(-2000, 0));
    auto place_action1 = Place::create(Point::ZERO);
    auto sequence_action1 = Sequence::create(move_action1, place_action1, NULL);
    auto repeat_action1 = RepeatForever::create(sequence_action1);
    background_layer1->runAction(repeat_action1);

    auto background_layer2 = Layer::create();
    this->addChild(background_layer2);

    auto background_sprite3 = Sprite::create("bg2.png");
    background_sprite3->setAnchorPoint(Point::ZERO);
    background_sprite3->setPosition(Point::ZERO);
    background_layer2->addChild(background_sprite3);

    auto background_sprite4 = Sprite::create("bg2.png", Rect(0, 0, 480, 114));
    background_sprite4->setAnchorPoint(Point::ZERO);
    background_sprite4->setPosition(Point(2000, 0));
    background_layer2->addChild(background_sprite4);

    auto move_action2 = MoveBy::create(5.0, Point(-2000, 0));
    auto place_action2 = Place::create(Point::ZERO);
    auto sequence_action2 = Sequence::create(move_action2, place_action2, NULL);
    auto repeat_action2 = RepeatForever::create(sequence_action2);
    background_layer2->runAction(repeat_action2);
}
```
</br>

</br>

단일 이미지 배경 스크롤과 유사하게 bg2.png를 가지고 스프라이트 2개를 만들었고, 레이어 하나를 더 추가해서 레이어에 액션 기능을 적용했다.

이 때 주의해야 할 것은 이미지 크기에 맞게 스프라이트를 추가해야 하며, Move 액션 기능을 적용할 때도 이미지의 크기만큼 이동시켜야 한다.

</br>

일반적으로 배경 스크롤을 할 때 화면 뒷부분에 있는 **원경에 해당하는 이미지는 천천히 스크롤**한다.

반대로 화면 앞 부분에 있는 **근경에 해당하는 이미지는 좀 더 빠르게 스크롤**한다.

</br>

배경 스크롤을 구현할 여러 이미지가 생길 때마다 **코드의 양이 매우 많이 추가되는 것을 확인**할 수가 있다.

이는 매우 번거로우며 이런 것을 편하게 구현할 수 있게 해주는 클래스가 바로 **ParallaxNode 클래스**다.