#include "SceneManager.h"
#include "NullScene.h"

SceneManager::SceneManager() : 
	currentScene_(std::make_shared<NullScene>())
{
}

void SceneManager::init()
{
	scenes_.clear();
}

void SceneManager::update(float deltaTime)
{
	currentScene_->update(deltaTime);
	// そのシーンが終了したら、自動で移動
	if (currentScene_->isEnd()) {
		currentScene_->end();
		change(currentScene_->next());
	}
}

void SceneManager::draw() const
{
	currentScene_->draw();
}

void SceneManager::end()
{
	currentScene_->end();
	currentScene_ = std::make_shared<NullScene>();
}

void SceneManager::add(Scene name, const IScenePtr & scene)
{
	scenes_[name] = scene;
}

void SceneManager::change(Scene name)
{
	end();
	currentScene_ = scenes_[name];
	currentScene_->start();
}

void SceneManager::sceneChanger()
{
}
