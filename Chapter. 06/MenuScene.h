#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"
#include "GameScene.h"

USING_NS_CC;

#define TAG_MENUITEM_PLAY           0
#define TAG_MENUITEM_HELP           1
#define TAG_MENUITEM_OPTION         2
#define TAG_MENUITEM_QUIT           3

class MenuScene : public Layer
{
public:
    static Scene* createScene();

    virtual bool init();    
    CREATE_FUNC(MenuScene);

    void InitBackground();
    void InitMenu();

    void MenuCallback(Ref* sender);
};

#endif
