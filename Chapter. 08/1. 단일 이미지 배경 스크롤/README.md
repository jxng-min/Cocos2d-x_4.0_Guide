## 단일 이미지 배경 스크롤

</br>

단일 이미지 배경을 스크롤하는 방법은 **액션 기능을 사용해서 쉽게 구현**할 수 있다.

</br>
</br>

### 8.1.1 단일 이미지 배경 스크롤 구현 방법

</br>

1. 배경으로 사용할 이미지를 Sprite로 만든다.
2. Move 액션 기능을 사용해서 스크롤하고 싶은 방향으로 이미지를 이동한다.
3. 이동이 끝나면 Place 액션 기능을 사용해서 배경 이미지를 초기 위치로 변경한다.
4. Move와 Place 액션 기능을 Sequence 액션 기능을 사용해서 하나의 액션으로 만든다.
5. RepeatForever 액션 기능을 사용해서 Sequence 액션으로 만든 액션을 무한 반복한다.

</br>

```C++
void GameScene::InitBackground()
{
    auto background_sprite = Sprite::create("bg1.png");
    background_sprite->setAnchorPoint(Point::ZERO);
    this->addChild(background_sprite);

    auto move_action = MoveBy::create(10.0, Point(-2000, 0));
    auto place_action = Place::create(Point::ZERO);
    auto sequence_action = Sequence::create(move_action, place_action, NULL);
    auto repeat_action = RepeatForever::create(sequence_action);
    background_sprite->runAction(repeat_action);
}
```
</br>

> background_sprite->setAnchorPoint(Point::ZERO);

배경으로 사용되는 스프라이트의 **앵커포인트와 위치 값을 (0, 0)으로 설정하는 것이 스크롤을 구현할 때 위치 계산을 하기가 더 수월**하다.

</br>

> auto move_action = MoveTo::create(10.0, Point(-2000, 0));    
> auto place_action = Place::create(Point::ZERO);    
> auto sequence_action = Sequence::create(move_action, place_action, NULL);    
> auto repeat_action = Sequence::create(sequence_action);    

bg1.png의 **가로 크기가 2000픽셀이기 때문에 왼쪽 방향으로 2000픽셀 이동하는 MoveBy 액션을 생성**하는 코드다.

그리고 이동한 후에 다시 **원래 위치로 이동하는 Place 액션도 생성**했다.

이렇게 만든 2개의 액션을 Sequence 액션으로 묶은 후에 RepeatForever 액션으로 무한 반복했다.

</br>

![화면 캡처 2024-10-02 161041](https://github.com/user-attachments/assets/6da4ec71-2170-4c18-97e7-d4d8ed2077e4)

</br>

하지만, 이미지의 크기만큼 이동하기 때문에 **이미지의 오른쪽 끝부분이 화면의 왼쪽 끝까지 올 때까지 화면에는 아무런 이미지도 출력되지 않는다**.

</br>

#### 화면 끊김 현상 해결 방법

1. 화면 크기만큼 이미지의 앞부분을 이미지 뒤에 추가해서 이미지 파일을 만든다.
    * bg1.png의 이미지 크기는 2000×320이지만 새로 만든 이미지의 크기는 (2000+480)×320이 된다.

</br>

2. 배경 이미지로 사용된 이미지로 또 하나의 스프라이트를 만들어서 첫 번째 스프라이트 뒤에 추가한다.
    * 뒤에 추가하는 스프라이트를 만들 때는 해당 화면의 크기만큼만 스프라이트로 생성한다.

</br>

2번 방법을 사용하는 편이 더 효율적이고 복잡하지 않으므로 2번 방법을 사용한다.

</br>

```C++
void GameScene::InitBackground()
{
    auto background_layer = Layer::create();
    this->addChild(background_layer);

    auto background_sprite1 = Sprite::create("bg1.png");
    background_sprite1->setAnchorPoint(Point::ZERO);
    background_sprite1->setPosition(Point::ZERO);
    background_layer->addChild(background_sprite1);

    auto background_sprite2 = Sprite::create("bg1.png", Rect(0, 0, 480, 320));
    background_sprite2->setAnchorPoint(Point::ZERO);
    background_sprite2->setPosition(Point(2000, 0));
    background_layer->addChild(background_sprite2);

    auto move_action = MoveBy::create(10.0, Point(-2000, 0));
    auto place_action = Place::create(Point::ZERO);
    auto sequence_action = Sequence::create(move_action, place_action, NULL);
    auto repeat_action = RepeatForever::create(sequence_action);
    background_layer->runAction(repeat_action);
}
```
</br>

![화면 캡처 2024-10-02 162206](https://github.com/user-attachments/assets/82438ae5-4d37-417e-8862-a9e5525b2a3c)

</br>

> auto background_layer = Layer::create();    
> this->addChild(background_layer);    

스프라이트 2개를 추가할 배경 레이어를 만들어서 화면에 추가한다.

</br>

> auto background_sprite2 = Sprite::create("bg1.png", Rect(0, 0, 480, 320));    
> background_sprite2->setAnchorPoint(Point::ZERO);    
> background_sprite2->setPosition(Point(2000, 0));    
> background_layer->addChild(background_sprite2);    

화면 끊김을 없애기 위해 bg1.png 이미지로 화면의 영역만큼만 스프라이트를 만들어서 첫 번째 스프라이트 뒤에 추가한다.

</br>

> background_layer->addChild(background_sprite1);    
> background_layer->addChild(background_sprite2);    

2개의 스프라이트는 this의 자식으로 두는 것이 아닌 배경 레이어의 자식으로 둔다.

</br>

> background_layer->runAction(repeat_action);

스프라이트가 아닌 배경 레이어에 액션 기능을 적용한다.

</br>

이렇게 배경을 구현할 때는 배경 이미지에 직접 액션 기능을 적용하는 것보다 레이어를 새로 만드는 것이 좋다.

**레이어에 배경 이미지의 스프라이트를 추가하고 레이어에 액션 기능을 적용하는 것이 좀 더 효율적**이다.
