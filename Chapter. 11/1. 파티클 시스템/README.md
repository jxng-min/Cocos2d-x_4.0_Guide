## 파티클 시스템

</br>

코코스2d-x에서는 **기본으로 제공하는 파티클**과 **외부 툴에서 제작한 파티클**을 사용할 수 있다.

</br>
</br>

### 11.1.1 기본 파티클

</br>

코코스2d-x에서는 기본적으로 11가지의 기본 파티클을 제공한다.

</br>

|종류|설명|
|----|----|
|ParticleExplosion|폭발 효과|
|ParticleFire|불 모양 효과|
|ParticleFireworks|불꽃 모양 효과|
|ParticleFlower|꽃 모양 효과|
|ParticleGalaxy|은하수 모양 효과|
|ParticleMeteor|유성 모양 효과|
|ParticleRain|비 내리는 효과|
|ParticleSmoke|연기 효과|
|ParticleSnow|눈 내리는 효과|
|ParticleSpiral|나선 모양 효과|
|ParticleSun|태양 모양 효과|

</br>

위의 기본 파티클 중에서 폭발 효과를 사용한 코드를 살펴보자.

</br>

```C++
bool GameScene::init()
{
    if(!Layer::init())
        return false;

    auto particle = ParticleExplosion::create();
    this->addChild(particle);

    return true;
}
```
</br>

</br>

파티클은 **Node를 상속받은 객체**이기 때문에 앞서 사용했던 Node에 적용되는 **일반적인 메소드 역시 파티클에 모두 사용이 가능**하다.

</br>
</br>

### 11.1.2 파티클 효과 생성

</br>

코코스2d-x에서 **파티클 효과는 .plist 형식으로 저장**되어 있다.

물론 .plist의 값을 직접 하나씩 지정하면서 파티클 효과를 만들 수도 있지만 **일반적으로 파티클을 만드는 툴을 사용해서 파티클을 생성**한다.

</br>

#### 파티클 디자이너

* Mac에서 사용하는 파티클 툴이다. Windows에서는 이를 사용할 수 없다.

</br>

#### 파티클2dx

파티클2dx는 툴은 아니지만 **웹에서 쉽게 파티클을 제작할 수 있는 페이지**다.

파티클2dx는 Internet Explorer에서는 실행되지 않으며 **Chrome, Safari, FireFox에서만 실행**된다.

사용법은 다른 파티클 툴과 비슷하며 **실시간으로 .plist 텍스트도 제공하기 때문에 따로 저장해서 사용할 수 있다**.

* 현재로서는 막혀있는 것 같다.