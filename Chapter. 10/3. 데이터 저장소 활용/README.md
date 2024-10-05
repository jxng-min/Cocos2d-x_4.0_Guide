## 데이터 저장소 활용

</br>

코코스2d-x에서는 **UserDefault**라는 **기본적인 데이터 저장소를 제공**한다. UserDefault는 **XML 형식으로 저장**되는 데이터 저장소다.

UserDefault는 **키와 값**의 포맷으로 어떤 값을 저장할 때 그 값에 해당되는 키 값을 입력해서 저장하고, 저장소에서 값을 가져올 때도 함께 저장한 키 값으로 값을 가져온다.

</br>
</br>

### 10.3.1 저장소에 데이터 저장

</br>

저장소에는 **Boolean, Double, Float, Integer, String을 저장**할 수 있으며, **매개변수로 키 값과 저장하려는 값을 입력**하면 된다.

|메소드|설명|
|------|----|
|UserDefault::getInstance()->setBoolForKey(const char* pKey, bool value)|키 값을 지정하고 Boolean형 값을 저장한다.|
|UserDefault::getInstance()->setDoubleForKey(const char* pKey, double value)|키 값을 지정하고 Double형 값을 저장한다.|
|UserDefault::getInstance()->setFloatForKey(const char* pKey, float value)|키 값을 지정하고 Float형 값을 저장한다.|
|UserDefault::getInstance()->setIntegerForKey(const char* pKey, int value)|키 값을 지정하고 Integer형 값을 저장한다.|
|UserDefault::getInstance()->setStringForKey(const char* pKey, const std::string& value)|키 값을 지정하고 String형 값을 저장한다.|

</br>
</br>

### 10.3.2 저장소에서 데이터 불러오기

</br>

저장소에서 **저장한 값을 불러올 때는** 매개변수로 함께 **저장한 키 값만 입력**하면 된다.

</br>

|메소드|설명|
|------|----|
|UserDefault::getInstance()->getBoolForKey(const char* pKey)|키 값에 해당되는 Boolean형 값을 불러온다.|
|UserDefault::getInstance()->getDoubleForKey(const char* pKey)|키 값에 해당되는 Double형 값을 불러온다.|
|UserDefault::getInstance()->getFloatForKey(const char* pKey)|키 값에 해당되는 Float형 값을 불러온다.|
|UserDefault::getInstance()->getIntegerForKey(const char* pKey)|키 값에 해당되는 Integer형 값을 불러온다.|
|UserDefault::getInstance()->getStringForKey(const char* pKey)|키 값에 해당되는 String형 값을 불러온다.|
|UserDefault::getInstance()->getTForKey(const char* pKey, T defaultValue)|키 값에 해당되는 T형 값을 볼러온다. 만약 해당되는 값이 없다면 defaultValue를 가져온다.|