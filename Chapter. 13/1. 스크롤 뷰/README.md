## 스크롤 뷰

</br>

게임에서 **도움말이나 상점**을 구현할 때처럼 **많은 정보를 한 화면에 보여줄 때 스크롤 뷰를 자주 사용**한다.

스크롤 뷰는 **화면에 보이는 영역보다 보여줘야 하는 정보의 크기가 커서** 터치 이벤트로 스크롤을 구현할 때 사용되는 클래스다.

스크롤 뷰를 구현할 때는 스크롤 뷰 말고도 **스크롤 뷰의 컨테이너가 되는 레이어가 필요**하다.

</br>
</br>

### 13.1.1 스크롤 뷰 구현

</br>

#### GameScene.h

```C++
#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#inlcude "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class GameScene : public Layer
{
public:
static Scene* createScene();

virtual bool init();
CREATE_FUNC(GameScene);
};

#endif
```

</br>

스크롤 뷰는 코코스2d-x 기본 클래스가 아닌 **확장형 클래스기 때문에 cocos-ext.h를 추가**해야 한다.

또한 **이름공간을 생략하려면 USING_NS_CC_EXT을 선언**해야 한다.

</br>

위와 같이 하면 모두 완료되지만 윈도우의 경우 관련 파일을 찾지 못한다는 에러가 발생한다.

따라서 해당 경로를 프로젝트 속성에서 추가해야 한다.

</br>

> 구성 속성 → C/C++ → 일반 → 추가 포함 디렉터리

</br>

![화면 캡처 2024-10-14 165930](https://github.com/user-attachments/assets/489609f9-bdd8-4d52-8bb4-642107fc1a84)

</br>

```C++
bool GameScene::init()
{
    if(!Layer::init())
        return false;

    auto layer = LayerColor::create(Color4B::WHITE);
    layer->setContentSize(Size(100, 600));
    this->addChild(layer);

    return true;
}
```

</br>

init()에서 setContentSize()를 이용해서 너비 100픽셀, 높이 600픽셀인 흰색 컬러레이어를 생성한다.

하지만 화면의 높이가 320픽셀이기 때문에 320픽셀만 보이고 윗부분은 화면에 보이지 않는다.

이렇게 화면의 크기보다 더 많은 정보를 보여주고 싶을 때 스크롤 뷰를 사용하면 된다.

</br>

![화면 캡처 2024-10-14 170408](https://github.com/user-attachments/assets/87958150-5e08-4046-8b26-582d5dd62351)

</br>

```C++
bool GameScene::init()
{
    if(!Layer::init())
        return false;

    auto layer = LayerColor::create(Color4B::WHITE);
    layer->setContentSize(Size(100, 600));
    this->addChild(layer);

    auto scroll = ScrollView::create(Size(100, 320), layer);
    scroll->setDirection(ScrollView::Direction::VERTICAL);
    scroll->setBounceable(false);
    this->addChild(scroll);

    return true;
}
```

</br>
</br>

> auto scroll = ScrollView::create(Size(100, 320), layer);

|매개변수|설명|
|-------|----|
|Size(100, 320)|스크롤 뷰의 크기를 입력한다.|
|layer|스크롤 뷰 내에서 스크롤되는 객체를 입력한다.|

</br>
</br>

> scroll->setDirection(ScrollView::Direction::VERTICAL);

스크롤 뷰의 스크롤 방향을 설정한다. **기본적으로 상하좌우 방향으로 스크롤**된다.

|방향|설명|
|----|----|
|ScrollView::Direction::Both|상하좌우 방향으로 스크롤|
|ScrollView::Direction::Horizontal|좌우 방향으로 스크롤|
|ScrollView::Direction::VERTICAL|상하 방향으로 스크롤|

</br>
</br>

> scroll->setBounceable(false);

스크롤 뷰의 바운스 효과를 설정한다.

설정 값을 **true**로 설정하면 **스크롤이 모두 끝난 부분에서도 화면을 스크롤한 만큼 이동한 다음에 원래 자리로 이동**한다.

설정 값을 **false**로 설정하면 스크롤이 끝난 후 **화면을 이동해도 스크롤 뷰는 더 이상 스크롤되지 않는다**.

setBounceable()의 기본 값이 true이기 때문에 **따로 설정하지 않으면 바운스 효과가 적용**된다.

</br>

더 확실하게 스크롤 뷰를 확인하기 위해 스프라이트를 컬러레이어에 포함시키겠다.

</br>

```C++
bool GameScene::init()
{
    if (!Layer::init())
        return false;

    auto layer = LayerColor::create(Color4B::WHITE);
    layer->setContentSize(Size(100, 600));
    this->addChild(layer);

    auto scroll = ScrollView::create(Size(100, 320), layer);
    scroll->setDirection(ScrollView::Direction::VERTICAL);
    scroll->setBounceable(false);
    this->addChild(scroll);

    auto sprite = Sprite::create("HelloWorld.png");
    sprite->setScale(0.5);
    sprite->setPosition(Point(50, 450));
    layer->addChild(sprite);

    return true;
}
```

</br>

![화면 캡처 2024-10-14 184354](https://github.com/user-attachments/assets/0a6605d7-7392-4724-aab8-3889180be9c9)

</br>
</br>

### 13.1.2 스크롤 뷰 설정

</br>

스크롤 뷰에 관련된 메소드는 생성 메소드 외에도 중요한 메소드가 몇 개 존재한다.

</br>

#### setContentOffset()

**스크롤 뷰에 포함되어 있는 레이어의 위치를 변경**하는 메소드다.

</br>

```C++
bool GameScene::init()
{
    if (!Layer::init())
        return false;

    auto layer = LayerColor::create(Color4B::WHITE);
    layer->setContentSize(Size(100, 600));
    this->addChild(layer);

    auto scroll = ScrollView::create(Size(100, 320), layer);
    scroll->setDirection(ScrollView::Direction::VERTICAL);
    scroll->setBounceable(false);
    this->addChild(scroll);

    auto sprite = Sprite::create("HelloWorld.png");
    sprite->setScale(0.5);
    sprite->setPosition(Point(50, 450));
    layer->addChild(sprite);

    scroll->setContentOffset(Point(0, -280));

    return true;
}
```
</br>

(50, 450)의 위치에 있던 sprite가 레이어 자체가 y축으로 -280만큼 이동하여 (50, 170)에 위치하는 것을 확인할 수 있다.

</br>

![화면 캡처 2024-10-14 184118](https://github.com/user-attachments/assets/7582a980-53d1-4e1a-b547-cddd186fb688)

</br>

```C++
bool GameScene::init()
{
    if (!Layer::init())
        return false;

    auto layer = LayerColor::create(Color4B::WHITE);
    layer->setContentSize(Size(100, 600));
    this->addChild(layer);

    auto scroll = ScrollView::create(Size(100, 320), layer);
    scroll->setDirection(ScrollView::Direction::VERTICAL);
    scroll->setBounceable(false);
    this->addChild(scroll);

    auto sprite = Sprite::create("HelloWorld.png");
    sprite->setScale(0.5);
    sprite->setPosition(Point(50, 450));
    layer->addChild(sprite);

    scroll->setContentOffsetDuration(Point(0, -280), 0.5);

    return true;
}
```

</br>

**setContentOffsetInDuration()**을 사용하면 **지정한 시간동안 스크롤 뷰 레이어의 위치가 변경**된다.
