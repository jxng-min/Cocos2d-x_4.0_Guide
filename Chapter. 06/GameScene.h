#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "MenuScene.h"

USING_NS_CC;

#define TAG_LABEL_CARD			0
#define TAG_LABEL_LIFE			1
#define TAG_LABEL_READY			2
#define TAG_LABEL_START			3
#define TAG_LABEL_SPRITE_O		4
#define TAG_LABEL_SPRITE_X		5
#define TAG_LABEL_GAMEOVER		6
#define TAG_LABEL_GAMECLEAR		7
#define TAG_MENU				8

#define TAG_SPRITE_CARD			10

class GameScene : public Layer
{
private:
	Size m_win_size;

	int m_card_ok;					// 올바르게 선택한 카드의 개수를 저장
	int m_life;						// 목숨의 개수를 저장하는 변수
	std::array<int, 4> m_card;		// 앞면을 보여줘야 하는 카드의 번호를 저장하는 배열
	int m_count_card;				// 맞춰야 할 카드의 순서를 저장

	bool m_is_touch;

public:
	static Scene* createScene();

	virtual bool init();
	CREATE_FUNC(GameScene);

	void InitGameData();
	void InitBackground();
	void InitTopMenuLabel();

	void SetLabelCard();
	void SetLabelLife();

	void InitReady();
	void ActionReady();
	void EndReady();

	void InitStart();
	void ActionStart();
	void EndStart();

	void InitCard();
	void ActionCard();
	void EndCard();

	void InitO();
	void InitX();
	void ActionOX(bool isO);
	void EndOX();

	void ActionGameEnd(bool is_game_clear);
	void EndGameEnd();

	void InitGameClear();
	void InitGameOver();

	void InitMenu();
	void ActionMenu(bool is_show);
	void MenuCallback(Ref* sender);

	virtual bool onTouchBegan(Touch* touch, Event* unused_event);
};
#endif