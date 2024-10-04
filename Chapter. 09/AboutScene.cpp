#include "AboutScene.h"

Scene* AboutScene::createScene()
{
	auto scene = Scene::create();

	auto layer = AboutScene::create();
	scene->addChild(layer);

	return scene;
}

bool AboutScene::init()
{
	if (!Layer::init())
		return false;

	return true;
}