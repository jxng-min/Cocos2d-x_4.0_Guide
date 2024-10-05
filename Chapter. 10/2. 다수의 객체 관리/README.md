## 여러 개의 데이터 관리

</br>

앞서 Array는 정적인 자료구조라 스마일의 개수가 변할 경우에는 사용하기 어렵다고 했다.

코코스2d-x는 **처음에 생성할 때 개수의 최대값을 지정하지 않고 리스트처럼 추가, 삭제가 가능**한 **Vector**를 제공한다.

</br>
</br>

### 10.2.1 변경점1: schedule 도입

</br>

InitSmile()의 이름을 SetSmile()로 변경하고 스케줄 메소드를 사용해서 스마일 이미지를 반복해서 화면에 출력해보자.

</br>

```C++
bool GameScene::init()
{
    if (!Layer::init())
        return false;

    InitData();
    this->schedule(CC_SCHEDULE_SELECTOR(GameScene::SetSmile), 0.5);

    return true;
}

void GameScene::SetSmile(float delta)
{
    auto x = rand() % static_cast<int>(m_win_size.width);
    auto y = rand() % static_cast<int>(m_win_size.height);

    auto smile_sprite = Sprite::create("Pea.png");
    smile_sprite->setPosition(Point(x, y));
    this->addChild(smile_sprite);
}

```
</br>

InitSmile()의 메소드명을 **SetSmile()로 변경**했고, **태그 값을 설정하는 부분도 삭제**했다.

스케줄 메소드로 사용하려면 float 매개변수도 가지고 있어야 하므로 **SetSmile()에 float 매개변수도 추가**했다.

</br>

![화면 캡처 2024-10-05 122729](https://github.com/user-attachments/assets/c3eda88c-8443-43e1-bda9-7620bd29f859)

</br>
</br>

### 10.2.2 변경점2: Vector 도입

</br>

위의 실행 결과를 보면 **스마일 이미지가 계속해서 생성**되고 있고, 태그 값을 삭제했기 때문에 **스마일 이미지의 스프라이트 값을 가져올 수 없다**.

하지만 코코스2d-x의 **Vector를 사용해서 스마일 이미지의 개수의 제한 및 충돌 체크를 구현**할 수 있다.

</br>

#### GameScene.h

```C++
#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class GameScene : public Layer
{
private:
    Size m_win_size;
    Vector<Sprite*> m_smiles;

public:
    ...
};

#endif
```
</br>
</br>

#### InitData()

```C++
void GameScene::InitData()
{
    ...
    m_smiles.clear();
}
```
</br>

위의 코드는 Vector인 m_smiles의 초기화를 추가한 코드다.

</br>
</br>

#### SetSmile()

```C++
void GameScene::SetSmile(float delta)
{
    if (m_smiles.size() >= 10)
        return;

    ...
    m_smiles.pushBack(smile_sprite);
}
```
</br>

위의 코드는 m_smiles를 사용해서 이미지의 생성되는 개수를 10개로 제한한다.

**Vector는 원소의 개수를 반환하는 size() 메소드를 가지고 있어서** 이를 쉽게 구현할 수 있다.

그리고 마지막에는 생성된 스프라이트를 **pushBack() 메소드를 이용해서 Vector에 추가**한다.

</br>
</br>

#### onTouchBegan()

```C++
bool GameScene::onTouchBegan(Touch* touch, Event* unused_event)
{
    auto location = touch->getLocation();

    auto remove_sprite = Sprite::create();

    for (auto smile : m_smiles)
    {
        auto smile_rect = smile->getBoundingBox();
        if (smile_rect.containsPoint(location))
        {
            if (smile->getScale() <= 0.25)
            {
                remove_sprite = smile;
                this->removeChild(smile);
            }
            else
                smile->setScale(smile->getScale() / 2);
        }
    }

    if(m_smiles.contains(remove_sprite))
        m_smiles.eraseObject(remove_sprite);

    return true;
}
```
</br>

위의 코드는 태그 값에 의해서 스프라이트를 가져오지 않고 **Vector에 저장된 객체들로 스프라이트를 가져오는 것으로 수정**했다.

**반복문을 사용해서 Vector의 모든 원소들과의 충돌 체크**를 시도하며, **삭제할 필요가 있을 시 임시 객체에 저장하여 삭제**한다.

</br>
</br>

### 10.2.3 Vector

Vector는 **게임에서 여러 개의 객체들 간의 충돌 체크 등을 구현할 때 자주 사용**되는 자료구조다. 또한, **동적인 데이터를 관리할 때 효율적**이다.

</br>

#### Vector의 크기 관련 메소드

|메소드|설명|
|-----|----|
|void reserve(ssize_t n);|벡터의 최대 크기를 미리 설정|
|ssize_t capacity() const;|벡터의 최대 크기를 ssize_t로 반환|
|ssize_t size() const;|벡터의 현재 크기를 ssize_t로 반환|
|bool empty() const;|벡터가 비어있는지의 유무를 bool로 반환|

</br>

#### Vector의 객체 반환 관련 메소드

|메소드|설명|
|-----|----|
|iterator find(T object);|입력한 객체가 있는 곳의 반복자를 반환|
|T at(ssize_t index) const;|인덱스 위치의 객체의 사본을 반환|
|T front() const;|벡터의 맨 앞 객체의 사본를 반환|
|T back() const;|벡터의 맨 뒤 객체의 사본을 반환|
|T getRandomObject() const;|벡터에 포함된 무작위 객체의 사본을 반환|
|bool contains(T object) const;|벡터에 특정 객체가 포함되어 있는지의 유무를 bool로 반환|

</br>

#### Vector의 객체 추가 관련 메소드

|메소드|설명|
|-----|----|
|void pushBack(T object);|벡터의 끝에 객체를 추가|
|void pushBack(const Vector<T>& other);|벡터의 끝에 특정 벡터를 추가|

</br>

#### Vector의 객체 삭제 관련 메소드

|메소드|설명|
|-----|----|
|void popBack();|벡터의 끝의 요소를 제거|
|void eraseObject(T object, bool removeAll = false);|벡터에서 특정 객체를 제거|
|void clear();|벡터의 모든 객체를 제거|
