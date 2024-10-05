## 사운드 출력

</br>

코코스2d-x에서 **사운드를 출력하려면 심플 오디오 엔진 클래스를 사용**해야 한다.

**심플 오디오 엔진은 cocosDenshion 네임스페이스로 분류**되어 있다.

</br>

사운드의 종류는 크게 배경음과 효과음으로 구분할 수 있다.

**배경음은 동시에 2개 이상을 출력할 수 없고** 오직 한 개만 출력할 수 있다.

하지만, **효과음의 경우는 동시에 여러 개의 효과음을 출력할 수 있다**.

</br>
</br>

### 11.2.1 배경음 출력

</br>

```C++
...
#inlcude "SimpleAudioEngine.h"

using namespace cocosDenshion;

...

bool GameScene::init()
{
    if(!Layer::init())
        return false;

    SimpleAudioEngine::getInstance()->playBackgroundMusic("background.mp3");

    return true;
}
```
</br>

위의 코드와 같이 **배경음은 SimpleAudioEngine의 playBackgroundMusic() 메소드로 간단하게 출력**할 수 있다.

</br>
</br>

### 11.2.2 배경음 관련 메소드

</br>

코코스2d-x에서는 배경음을 출력하는 것뿐만 아니라 다양한 배경음 관련 메소드를 제공한다.

</br>

```C++
SimpleAudioEngine::getInstance()->playBackgroundMusic(const char* pszFilePath, bool bLoop);
```
</br>

|매개변수|설명|
|-------|----|
|pszFilePath|출력할 배경음 파일의 경로|
|bLoop|반복 출력 여부(생략 가능; 생략하면 반복 X)|

</br>
</br>
</br>

```C++
SimpleAudioEngine::getInstance()->pauseBackgroundMusic();       // 배경음의 출력을 일시정지
SimpleAudioEngine::getInstance()->resumeBackgroundMusic();      // 일시정지된 배경음의 출력을 재개
SimpleAudioEngine::getInstance()->stopBackgroundMusic();        // 배경음의 출력을 중지
```
</br>
</br>

### 11.2.3 효과음 출력

효과음을 출력하는 방법은 배경음을 출력하는 방법과 거의 동일하다.

효과음의 경우는 **동시에 여러 개의 효과음을 출력할 수 있으므로**, 출력할 때마다 **출력되는 효과음의 고유 ID값이 반환**된다.

반환된 효과음의 **고유 ID값으로 효과음을 일시정지하거나 중지**할 수 있다.

</br>

```C++
bool GameScene::init()
{
    if(!Layer::init())
        return false;

    int sound_id1 = SimpleAudioEngine::getInstance()->playEffect("effect1.wav");

    return true;
}
```
</br>

위와 같이 **효과음은 출력할 때에 고유의 ID값을 반환받을 수 있다**.

하지만, 이렇게 반환받은 ID값으로 각 효과음을 따로 제어하는 경우보다는 **ID값과 상관없이 현재 출력되고 있는 모든 효과음을 한 번에 모두 제어하는 경우가 더 많다**.

</br>

사운드 파일은 .mp3, .wav, .ogg 등을 지원하지만 **일반적으로 배경음은 .mp3을 많이 사용하며, 효과음은 .wav을 자주 사용**한다.

</br>
</br>

### 11.2.4 효과음 관련 메소드

</br>

코코스2d-x는 배경음과 동일하게 효과음을 구현할 때 필요한 메소드도 제공한다.

특히 효과음은 현재 출력 중인 모든 효과음을 일시정지하거나 중지하는 등 **출력 중인 모든 효과음을 제어할 수 있는 메소드도 제공**한다.

</br>

```C++
SimpleAudioEngine::getInstance()->playEffect(const char* pszFilePath, bool bLoop);
```
</br>

|매개변수|설명|
|-------|----|
|pszFilePath|출력할 효과음 파일의 경로|
|bLoop|반복 출력 여부(생략 가능; 생략하면 반복 X)|

</br>
</br>
</br>

```C++
SimpleAudioEngine::getInstance()->pauseEffect(unsigned int nSoundId);
SimpleAudioEngine::getInstance()->pauseAllEffects();
SimpleAudioEngine::getInstance()->resumeEffect(unsigned int nSoundId);
SimpleAudioEngine::getInstance()->resumeAllEffects();
SimpleAudioEngine::getInstance()->stopEffect(unsigned int nSoundId);
SimpleAudioEngine::getInstance()->stopAllEffects();
```
</br>