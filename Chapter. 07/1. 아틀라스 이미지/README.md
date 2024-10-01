## 아틀라스 이미지

</br>

**아틀라스 이미지**는 **여러 개의 이미지를 하나의 큰 이미지로 만드는 것**이다.

게임에서 사용되는 이미지는 수십 개에서 많게는 수백 개까지 될 수 있다.

이렇게 많은 이미지를 각 파일로 사용하면 **리소스 관리도 힘들고 효율도 좋지 않다**.

</br>
</br>

### 7.1.1 아틀라스 이미지 생성

</br>

아틀라스 이미지를 만드는 툴은 대부분 유료 툴이지만, 무료 버전에서도 기본적인 기능을 제공하는 것들이 있다.

</br>

|도구 이름|링크|
|--------|----|
|Texture Packer|https://www.codeandweb.com/texturepacker|
|Zwoptex|https://zwoptex.apponic.com/mac/|
|Sprite Helper|https://pixelbyte.itch.io/paint-net-sprite-plugin|

</br>

일반적으로 아틀라스 이미지를 만드는 **툴의 사용법은 거의 비슷**하다. 이 중 Windows와 Mac을 모두 지원하는 Texture Packer(텍스처 팩커)로 이틀라스 이미지를 만들겠다.

</br>

</br>

아틀라스 이미지를 만들려면 먼저 왼쪽 상단에 있는 **Open Project 버튼을 클릭해서 합치려는 이미지를 선택**하거나, 합치려는 **이미지를 모두 선택한 후 Sprites 박스 안으로 드래그**한다.

</br>

</br>

오른쪽 Output 항목 중에서 **Framework를 클릭**하면 다양한 데이터 포맷을 볼 수 있으며, 그 중에서 **cocos2d 또는 cocos2d-x를 선택**하면 된다.

그리고 상단 메뉴에서 가운데에 있는 **Publish sprite sheet 버튼을 클릭**한 후 결과물의 이름을 입력하고 폴더를 지정한 후 **Save 버튼**을 누르면 파일이 저장된다.

저장한 후 지정한 경로로 가면 **.png와 .plist가 생성**된 것을 확인할 수 있다.

</br>
</br>

### 7.1.2 아틀라스 이미지 사용

</br>

우선 위에서 생성한 아틀라스 이미지의 .png와 .plist를 프로젝트에 추가한다.

</br>

```C++
bool GameScene::init()
{
    if (!Layer::init())
        return false;

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("grossini.plist");

    auto sprite = Sprite::createWithSpriteFrameName("grossini_dance_01.png");
    sprite->setPosition(Point(150, 150));
    this->addChild(sprite);

    return true;
}
```
</br>

> SpriteFrameCache::getInstance()->addSpriteFramesWithFile("grossini.plist");

아틀라스 이미지를 사용하기 위해서는 **.plist를 먼저 스프라이트 프레임캐시에 등록**해야 한다.

</br>

> auto sprite = Sprite::createWithSpriteFrameName("grossini_dance_01.png");

등록된 **.plist에 포함되어 있는 이미지는 createWithSpriteFrameName()을 사용해서 스프라이트를 생성**할 수 있다.

여기서 사용되는 **프레임 이름**은 아틀라스 **이미지를 만들때 사용한 각 파일들의 이름을 사용**하면 된다.

그리고 **.plist는 xml로 작성된 파일**이기 때문에 .plist에 포함되어 있는 **프레임의 이름은 frames 항목에 모두 저장**되어 있다.

</br>

</br>

**스프라이트 프레임캐시에 등록된 파일은 스프라이트를 만들 수 있을 뿐만 아니라 스프라이트 프레임도 만들 수 있다**.