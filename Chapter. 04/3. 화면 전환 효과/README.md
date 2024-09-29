## 화면 전환 효과

</br>

코코스2d-x에서는 화면을 전활할 때 다양한 화면 전환 효과를 제공한다.

r**eplaceScene()과 pushScene()에서는 이러한 화면 전환 효과를 사용**할 수 있다.

하지만 popScene()은 매개변수로 Scene을 사용하지 않기 때문에 사용할 수 없다.

</br>
</br>

### 4.3.1 화면 전환 효과의 종류

</br>

#### Fade

|메소드|효과|
|-----|----|
|TransitionFade|전환되는 2개의 화면이 순차적으로 페이드 효과로 전환|
|TransitionCrossFade|전환되는 2개의 화면이 동시에 페이드 효과로 전환|
|TransitionFadeUp|하단에서 상단으로 두꺼운 선 모양의 페이드 효과로 전환|
|TransitionFadeDown|상단에서 하단으로 두꺼운 선 모양의 페이드 효과로 전환|
|TransitionFadeBL|우측 상단에서 좌측 하단으로 블록 모양 페이드 효과로 전환|
|TransitionFadeTR|좌측 하단에서 우측 상단으로 블록 모양 페이드 효과로 전환|

</br>

#### Flip

|메소드|효과|
|-----|----|
|TransitionFlipAngular|화면 가운데에서 비스듬하게 회전하면서 전환|
|TransitionFlipFlipX|화면 가운데에서 X축을 기준으로 회전하면서 전환|
|TransitionFlipFlipY|화면 가운데에서 Y축을 기준으로 회전하면서 전환|

</br>

#### Zoom

|메소드|효과|
|-----|----|
|TransitionJumpZoom|현재 화면이 축소되면서 왼쪽으로 점프로 이동하고 오른쪽에서 새로운 화면이 점프로 나타난 후에 확대되면서 전환|
|TransitionRotoZoom|현재 화면이 화면 가운데로 축소되면서 회전하며 사라지고, 새로운 화면이 확대되면서 회전하며 나타나는 효과로 전환|

</br>

#### ZoomFlip
|메소드|효과|
|-----|----|
|TransitionZoomFlipAngular|확대되면서 화면 가운데에서 비스듬하게 회전하면서 전환|
|TransitionZoomFlipX|확대되면서 화면 가운데에서 X축을 기준으로 회전하면서 전환|
|TransitionZoomFlipY|확대되면서 화면 가운데에서 Y축을 기준으로 회전하면서 전환|

<br>

#### MoveIn
|메소드|효과|
|-----|----|
|TransitionMoveInB|새로운 화면이 아래에서 위로 겹쳐지면서 전환|
|TransitionMoveInT|새로운 화면이 위에서 아래로 겹쳐지면서 전환|
|TransitionMoveInL|새로운 화면이 왼쪽에서 오른쪽으로 겹쳐지면서 전환|
|TransitionMoveInR|새로운 화면이 오른쪽에서 왼쪽으로 겹쳐지면서 전환|

</br>

#### SlideIn
|메소드|효과|
|-----|----|
|TransitionSlideInB|새로운 화면이 현재 화면을 아래에서 위로 밀어내면서 전환|
|TransitionSlideInT|새로운 화면이 현재 화면을 위에서 아래로 밀어내면서 전환|
|TransitionSlideInL|새로운 화면이 현재 화면을 왼쪽에서 오른쪽으로 밀어내면서 전환|
|TransitionSlideInR|새로운 화면이 현재 화면을 오른쪽에서 왼쪽으로 밀어내면서 전환|

</br>

#### Progress
|메소드|효과|
|-----|----|
|TransitionProgressHorizontal|새로운 화면이 좌측에서 우측으로 지나가는 효과로 전환|
|TransitionProgressVertical|새로운 화면이 상단에서 하단으로 지나가는 효과로 전환|
|TransitionProgressRadicalCW|새로운 화면이 시계방향으로 회전하면서 나타나는 효과로 전환|
|TransitionProgressRadicalCCW|새로운 화면이 반시계방향으로 회전하면서 나타나는 효과로 전환|
|TransitionProgressInOut|새로운 화면이 화면 가운데에서 확대되면서 나타나는 효과로 전환|
|TransitionProgressOutIn|현재 화면이 화면 가운데로 축소되면서 나타나는 효과로 전환|

</br>

#### Split
|메소드|효과|
|-----|----|
|TransitionSplitCols|전환되는 2개의 화면이 상하로 나눠지면서 전환|
|TransitionSplitRows|전환되는 2개의 화면이 좌우로 나눠지면서 전환|

</br>

#### 기타
|메소드|효과|
|-----|----|
|TransitionPageTurn|페이지 넘기는 효과로 전환|
|TransitionTrunOffTiles|타일 조각 효과로 전환|
|TransitionShrinkGrow|전환되는 2개의 화면이 확대, 축소로 교차되면서 전환|

</br>
</br>

### 4.3.2 화면 전환 효과 적용

</br>

replaceScene()을 사용해서 화면 전환 효과를 적용시켜보자.

</br>

```C++
Director::getInstance()->replaceScene(GameScene::createScene());
```
</br>

화면 전환 효과를 적용하지 않는 경우에는 위와 같이 매개변수에 바로 Scene을 입력할 수 있다.

하지만 **화면 전환 효과를 적용할 때는** 바로 입력하는 것보다는 **Scene으로 생성한 후 적용하는 것이 보기 좋다**.

</br>

```C++
auto target_scene = GameScene::createScene();
Director::getInstance()->replaceScene(target_scene);
```
</br>

그러면 이제 화면 전환 효과를 적용해보자.

</br>

```C++
void MenuScene::changeScene(Ref* sender)
{
    auto target_scene = TransitionCrossFade::create(3.0, GameScene::createScene());
    Director::getInstance()->replaceScene(target_scene);
}
```
</br>

![화면 캡처 2024-09-29 155333](https://github.com/user-attachments/assets/62c49fa7-0d00-4b44-b077-1e718ddb4221)
