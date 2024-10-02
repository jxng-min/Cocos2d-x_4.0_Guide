## 타일 배경 스크롤

</br>

배경을 구성할 때는 큰 이미지를 가지고 구성할 때도 있지만 작은 타일 이미지를 가지고 구성할 때도 많다.

</br>

```C++
void GameScene::InitBackground()
{
    for(auto i = 0; i < 15; i++)
        for(auto j = 0; j < 7; j++)
        {
            auto sprite = Sprite::create("tile.png");
            sprite->setAnchorPoint(Point::ZERO);
            sprite->setPosition(Point(i * 33, j * 49));
            this->addChild(sprite);
        }
}
```
</br>

![화면 캡처 2024-10-02 174534](https://github.com/user-attachments/assets/bd1440eb-1ec5-4dfe-9418-38957a002679)

</br>

tile.png의 크기가 33×49이기 때문에 480×320의 화면을 타일 이미지로 채우기 위해서 반복문으로 tile.png를 15×7개의 바둑판 모양으로 스프라이트를 생성한 후 출력한다.

**타일 이미지로 구성한 배경을 스크롤 할 때는 배경 레이어를 생성한 후 배경 레이어에 액션 기능을 추가**한다.

</br>

```C++
void GameScene::InitBackground()
{
    auto background_layer = Layer::create();
    this->addChild(background_layer);

    for(auto i = 0; i < 15; i++)
        for(auto j = 0; j < 8; j++)
        {
            auto sprite = Sprite::create("tile.png");
            sprite->setAnchorPoint(Point::ZERO);
            sprite->setPosition(Point(i * 33, j * 49));
            background_layer->addChild(sprite);
        }

    auto move_action = MoveBy::create(2.0, Point(0, -49));
    auto place_action = Place::create(Point::ZERO);
    auto sequence_action = Sequence::create(move_action, place_action, NULL);
    auto repeat_action = RepeatForever::create(sequence_action);
    background_layer->runAction(repeat_action);
}
```
</br>

타일의 경우는 **이동하는 방향의 뒷부분에 타일 한 개 만큼의 이미지를 추가**하고, **이동하는 크기도 타일의 크기만큼만 이동**하면 된다.
