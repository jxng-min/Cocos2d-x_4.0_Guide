#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"
#include "GameScene.h"
#include "AboutScene.h"

#define TAG_MENU_START          1
#define TAG_MENU_ABOUT          2
#define TAG_MENU_QUIT           3

USING_NS_CC;

class MenuScene : public Layer
{
private:
    Size m_win_size;

public:
    static Scene* createScene();

    virtual bool init();
    CREATE_FUNC(MenuScene);

    void InitData();
    void InitBackground();
    void InitTitleMenu();
    void MenuCallback(Ref* sender);
};

#endif
