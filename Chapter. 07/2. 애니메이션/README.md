## 애니메이션

</br>

애니메이션을 구현하려면 Animation 객체를 만들고, **Animation 객체를 가지고 Animate 객체를 생성**해야 한다.

그리고 이렇게 만들어진 **Animate 객체를 기준이 되는 스프라이트의 액션으로 적용**해주면 된다.

**Animation 객체를 생성**할 때는 **애니메이션에 사용할 프레임을 추가**해야 하며, **프레임의 시간 간격도 반드시 지정**해야 한다.

</br>
</br>

### 7.2.1 이미지 파일을 사용한 애니메이션 구현

</br>

애니메이션을 구현하기 전에 애니메이션에 사용할 grossini_dance로 시작하는 14개의 이미지 파일을 프로젝트에 추가한다.

그리고 setAnimation()을 GameScene.h에 추가하고 init()에서 setAnimation()을 호출하고 GameScene.cpp에서 이를 구현한다.

</br>

```C++
void GameScene::setAnimation()
{
    auto sprite = Sprite::create("grossini_dance_01.png");          // 기준이 되는 스프라이트를 생성한다.
    sprite->setPosition(Point(150, 150));
    this->addChild(sprite);

    auto animation = Animation::create();                           // Animation 객체를 만들고,
    animation->setDelayPerUnit(0.3);                                // 프레임의 간격 시간을 0.3초로 지정한다.

    animation->addSpriteFrameWithFile("grossini_dance_01.png");     // 14개의 파일 이름을 모두 지정해서 프레임을 추가한다.
    animation->addSpriteFrameWithFile("grossini_dance_02.png");
    animation->addSpriteFrameWithFile("grossini_dance_03.png");
    animation->addSpriteFrameWithFile("grossini_dance_04.png");
    animation->addSpriteFrameWithFile("grossini_dance_05.png");
    animation->addSpriteFrameWithFile("grossini_dance_06.png");
    animation->addSpriteFrameWithFile("grossini_dance_07.png");
    animation->addSpriteFrameWithFile("grossini_dance_08.png");
    animation->addSpriteFrameWithFile("grossini_dance_09.png");
    animation->addSpriteFrameWithFile("grossini_dance_10.png");
    animation->addSpriteFrameWithFile("grossini_dance_11.png");
    animation->addSpriteFrameWithFile("grossini_dance_12.png");
    animation->addSpriteFrameWithFile("grossini_dance_13.png");
    animation->addSpriteFrameWithFile("grossini_dance_14.png");

    auto animate = Animate::create(animation);                      // Animation 객체를 이용하여 Animate 객체를 생성한다.
    sprite->runAction(animate);                                     // sprite에서 이를 실행한다.
}
```
</br>



</br>

하지만 위의 코드는 애니메이션이 단 한 번만 실행되고 어느 순간에 멈추게 된다.

이를 해결하기 위해서는 RepeatForever 액션을 사용하면 된다.

</br>

```C++
void GameScene::setAnimation()
{
    auto sprite = Sprite::create("grossini_dance_01.png");          // 기준이 되는 스프라이트를 생성한다.
    sprite->setPosition(Point(150, 150));
    this->addChild(sprite);

    auto animation = Animation::create();                           // Animation 객체를 만들고,
    animation->setDelayPerUnit(0.3);                                // 프레임의 간격 시간을 0.3초로 지정한다.

    animation->addSpriteFrameWithFile("grossini_dance_01.png");     // 14개의 파일 이름을 모두 지정해서 프레임을 추가한다.
    animation->addSpriteFrameWithFile("grossini_dance_02.png");
    animation->addSpriteFrameWithFile("grossini_dance_03.png");
    animation->addSpriteFrameWithFile("grossini_dance_04.png");
    animation->addSpriteFrameWithFile("grossini_dance_05.png");
    animation->addSpriteFrameWithFile("grossini_dance_06.png");
    animation->addSpriteFrameWithFile("grossini_dance_07.png");
    animation->addSpriteFrameWithFile("grossini_dance_08.png");
    animation->addSpriteFrameWithFile("grossini_dance_09.png");
    animation->addSpriteFrameWithFile("grossini_dance_10.png");
    animation->addSpriteFrameWithFile("grossini_dance_11.png");
    animation->addSpriteFrameWithFile("grossini_dance_12.png");
    animation->addSpriteFrameWithFile("grossini_dance_13.png");
    animation->addSpriteFrameWithFile("grossini_dance_14.png");

    auto animate = Animate::create(animation);                      // Animation 객체를 이용하여 Animate 객체를 생성한다.
    auto action = RepeatForever::create(animate);                   // Animate 액션을 무한반복하는 액션을 만든다.
    sprite->runAction(action);                                      // sprite에서 이를 실행한다.
}
```
</br>

또한 프레임을 추가할 때 **파일의 수가 많아지면 소스 코드의 양이 많아져**서 불편하므로 이를 수정할 필요가 있다.

</br>

```C++
void GameScene::setAnimation()
{
    auto sprite = Sprite::create("grossini_dance_01.png");
    sprite->setPosition(Point(150, 150));
    this->addChild(sprite);

    auto animation = Animation::create();
    animation->setDelayPerUnit(0.3);

    // for문과 StringUtils를 이용하여 만든 문자열로 프레임을 추가
    for(auto i = 0; i < 14; i++)
        animation->addSpriteFrameWithFile(StringUtils::format("grossini_dance_%02d.png", i + 1));

    auto animate = Animate::create(animation);
    auto action = RepeatForever::create(animate);
    sprite->runAction(action);
}
```

</br>
</br>

### 7.2.2 스프라이트 프레임을 사용한 애니메이션 구현

</br>

스프라이트 프레임을 사용해서 애니메이션을 구현하려면 아틀라스 이미지의 .png와 .plist를 프로젝트에 추가한다.

</br>

```C++
void GameScene::setAnimation()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("grossini.plist");

    auto sprite = Sprite::createWithSpriteFrameName("grossini_dance_01.png");
    sprite->setPosition(Point(150, 150));
    this->addChild(sprite);

    auto animation = Animation::create();
    animation->setDelayPerUnit(0.3);

    for (auto i = 0; i < 14; i++)
    {
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("grossini_dance_%02d.png", i + 1));
        animation->addSpriteFrame(frame);
    }

    auto animate = Animate::create(animation);
    sprite->runAction(RepeatForever::create(animate));
}
```
</br>

> SpriteFrameCache::getInstance()->addSpriteFramesWithFile("grossini.plist");

스프라이트 프레임을 이용할 때는 제일 먼저 스프라이트 프레임캐시에 .plist를 추가해야 한다.

</br>

> auto sprite = Sprite::createWithSpriteFrameName("grossini_dance_01.png");

스프라이트를 생성할 때도 파일 이름이 아닌 스프라이트 프레임 이름으로 생성한다.

</br>

> auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("grossini_dance_%02d.png", i + 1));

애니메이션에 프레임을 추가할 때도 스프라이트 프레임캐시에서 프레임을 가져와서 추가한다.