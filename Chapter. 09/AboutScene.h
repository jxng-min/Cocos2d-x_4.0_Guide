#ifndef __ABOUT_SCENE_H__
#define __ABOUT_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

#define TAG_ITEM_BACK			1

class AboutScene : public Layer
{
private:
	Size m_win_size;

public:
	static Scene* createScene();

	virtual bool init();
	CREATE_FUNC(AboutScene);

	void InitData();
	void InitBackground();
	void InitAboutMenu();
	void MenuCallback(Ref* sender);
};

#endif