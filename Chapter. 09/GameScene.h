#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "MenuScene.h"

USING_NS_CC;

#define TAG_LABEL_SCORE			1
#define TAG_SPRITE_PLAYER		2
#define TAG_SPRITE_OBSTACLE		3
#define TAG_ITEM_RETRY			4
#define TAG_ITEM_TITLE			5
#define TAG_LAYER_GAMEOVER		6

class GameScene : public Layer
{
private:
	Size m_win_size;
	double m_score;
	bool m_player_is_jump;
	bool m_is_stop;

public:
	static Scene* createScene();

	virtual bool init();
	CREATE_FUNC(GameScene);

	void InitData();

	void InitBackground();

	void InitPlayer();
	void InitPlayerAnimation();

	void PlayerJump();
	void PlayerJumpReset();

	void InitObstacle(float delta);
	void InitObstacleAnimation();

	void InitScoreGUI();
	void InitGameOverGUI();
	void InitGUI();

	void InitGame();

	virtual bool onTouchBegan(Touch* touch, Event* unused_event);

	virtual void update(float delta);

	void MenuCallback(Ref* sender);
};

#endif