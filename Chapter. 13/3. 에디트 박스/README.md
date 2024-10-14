## 에디트 박스

</br>

게임에서는 아이디나 비밀번호 같이 **사용자로부터 입력을 받는 경우가 많이 존재**한다.

코코스2d-x는 사용자로부터 입력을 받을 수 있는 에디트 박스 클래스를 제공한다.

**에디트 박스**는 **사각형 이미지 안에 사용자의 입력을 받은 문자열을 출력**하는 클래스다.

에디트 박스를 사용하기 위해서는 **cocos-ext.h, UI/UIEditBox/UIEditBox.h, USING_NS_CC_EXT, using namespace ui를 추가**해야 한다.

</br>

```C++
bool GameScene::init()
{
    if(!Layer::init())
        return false;

    auto edit_box = EditBox::create(Size(400, 50), Scale9Sprite::create("green_edit.png"));
    edit_box->setPosition(Point(240, 160));
    edit_box->setPlaceHolder("Name: ");
    edit_box->setMaxLength(8);
    this->addChild(edit_box);

    return true;
}
```
</br>

![화면 캡처 2024-10-14 200743](https://github.com/user-attachments/assets/6441880a-ea5e-4a04-bd84-f26e070d65d7)

</br>

위의 예제는 에디트 박스를 사용해서 이름을 입력받는 코드다.

</br>

> auto edit_box = EditBox::create(Size(400, 50), Scale9Sprite::create("green_edit.png"));

|매개변수|설명|
|-------|----|
|Size(400, 50)|에디트 박스의 크기를 입력한다.|
|Scale9Sprite::create("green_edit.png")|에디트 박스가 될 Scale9Sprite를 입력한다.|

<br>

Scale9Sprite에 사용되는 green_edit.png의 크기는 28×28 픽셀이지만 Scale9Sprite이기 때문에 400×50픽셀로 이미지가 생성된다.

</br>

> edit_box->setPlaceHolder("Name: ");

**setPlaceHolder()**는 **사용자의 입력을 받기 전 에디트 박스에 출력되는 문자열을 설정**하는 메소드다.

플레이스 홀더의 기본 색상을 **회색**이다.

</br>

> edit_box->setMaxLength(8);

에디트 박스가 입력받을 수 있는 **문자의 길이를 지정**한다.

</br>
</br>

### 13.3.1 에디트 박스 설정

</br>

에디트 박스는 보여지는 **폰트의 종류와 크기 등을 지정**하는 것 외에도 iOS, Android에서 보여지는 **가상 키보드에 대한 다양한 설정**도 할 수 있다.

</br>

```C++
// 플레이스 홀더의 폰트 종류와 크기를 지정하는 메소드
void setPlaceholderFont(const char* pFontName, intfontSize);

// 플레이스 홀더의 폰트 색상을 지정하는 메소드
void setPlaceholderFontColor(const Color3B& color);

// 폰트의 종류와 크기를 지정하는 메소드
void setFont(const char* pFontName, intfontSize);

// 폰트의 색상을 지정하는 메소드
void setFontColor(const Color3B& color);
```

</br>
</br>

```C++
// 키보드 리턴 키의 종류를 지정하는 메소드
void setReturnType(EditBox::KeyboardReturnType returnType);
```

|종류|표시되는 문자열|
|----|--------------|
|EditBox::KeyboardReturnType::DEFAULT|return|
|EditBox::KeyboardReturnType::DONE|Done|
|EditBox::KeyboardReturnType::SEND|Send|
|EditBox::KeyboardReturnType::SEARCH|Search|
|EditBox::KeyboardReturnType::GO|Go|

</br>
</br>

```C++
// 키보드 입력 모드를 지정하는 메소드
void setInputMode(EditBox::InputMode inputMode);
```

|입력 모드|설명|
|--------|---|
|EditBox::InputMode::ANY|기본 입력 모드|
|EditBox::InputMode::EMAIL_ADDRESS|이메일 주소 입력 모드|
|EditBox::InputMode::NEMERIC|숫자와 특수문자 입력 모드|
|EditBox::InputMode::PHONE_NUMBER|전화번호 입력 모드|
|EditBox::InputMode::URL|URL 입력 모드|
|EditBox::InputMode::DECIMAL|숫자와 부동소수점 입력 모드|

</br>
</br>

```C++
// 키보드 입력 플래그를 지정하는 메소드
void setInputFlag(EditBox::InputFlag inputFlag);
```

|종류|설명|
|----|----|
|EditBox::InputFlag::PASSWORD|비밀번호 입력 플래그(*로 표시)|
|EditBox::InputFlag::SENSITIVE|추천 기능 없음|
|EditBox::InputFlag::INITIAL_CAPS_WORD|단어마다 추천 기능 적용|
|EditBox::InputFlag::INITIAL_CAPS_SENTENCE|문장마다 추천 기능 적용|
|EditBox::InputFlag::INITIAL_CAPS_CHARACTERS|글자마다 추천 기능 적용|

</br>
</br>

```C++
bool GameScene::init()
{
    if (!Layer::init())
        return false;

    auto edit_box = EditBox::create(Size(400, 50), Scale9Sprite::create("green_edit.png"));
    edit_box->setPosition(Point(240, 160));
    edit_box->setPlaceHolder("Name: ");
    edit_box->setMaxLength(8);
    this->addChild(edit_box);

    edit_box->setPlaceholderFont("", 30);
    edit_box->setPlaceholderFontColor(Color3B::BLUE);
    edit_box->setFont("", 20);
    edit_box->setFontColor(Color3B::RED);
    edit_box->setReturnType(EditBox::KeyboardReturnType::SEARCH);
    edit_box->setInputMode(EditBox::InputMode::NUMERIC);
    edit_box->setInputFlag(EditBox::InputFlag::PASSWORD);

    return true;
}
```

</br>

![화면 캡처 2024-10-14 204157](https://github.com/user-attachments/assets/bdb9df43-6835-4887-8a83-6cdedf09ae8e)

</br>
</br>

### 13.3.2 델리게이트

</br>

**델리게이트**는 **특정 객체가 어떤 동작을 할 때 미리 지정한 메소드가 호출되는 것**이다.

에디트 박스의 델리게이트 메소드는 4종류가 있다.

</br>

```C++
// 에디트 박스를 클릭하면 호출되는 메소드
virtual void editBoxEditingDidBegin(EditBox* editBox);

// 에디트 박스의 입력을 리턴 키를 입력하여서 종료할 때 출력되는 메소드
virtual void editBoxEditingDidEnd(EditBox* editBox);

// 에디트 박스를 클릭한 후 글자를 입력할 때마다 호출되는 메소드
virtual void editBoxTextChanged(EditBox* editBox, const std::string& text);

// 리턴 키를 입력할 때 출력되는 메소드
virtual void editBoxReturn(EditBox* editBox);
```
</br>

**일반적으로 리턴 키를 입력하면 editBoxEditingEnd()가 호출되고 바로 editBoxReturn()이 호출**된다.

</br>
</br>

#### GameScene.h

```C++
#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "UI/UIEditBox/UIEditBox.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;

class GameScene : public Layer, public EditBoxDelegate
{
public:
    static Scene* createScene();

    virtual bool init();
    CREATE_FUNC(GameScene);

protected:
    virtual void editBoxEditingDidBegin(EditBox* editBox);
    virtual void editBoxEditingDidEnd(EditBox* editBox);
    virtual void editBoxTextChanged(EditBox* editBox, const std::string& text);
    virtual void editBoxReturn(EditBox* editBox);
};

#endif
```

</br>
</br>

#### GameScene.cpp

```C++
...

void GameScene::editBoxEditingDidBegin(EditBox* editBox)
{
    CCLOG("--- editBoxEditingDidBegin ---");
}

void GameScene::editBoxEditingDidEnd(EditBox* editBox)
{
    CCLOG("--- editBoxEditingDidEnd ---");
}

void GameScene::editBoxTextChanged(EditBox* editBox, const std::string& text)
{
    CCLOG("--- editBoxTextChanged ---");
}

void GameScene::editBoxReturn(EditBox* editBox)
{
    CCLOG("-- - editBoxReturn ---");
}

bool GameScene::init()
{
    if (!Layer::init())
        return false;

    ...

    edit_box->setDelegate(this);

    return true;
}
```
</br>
