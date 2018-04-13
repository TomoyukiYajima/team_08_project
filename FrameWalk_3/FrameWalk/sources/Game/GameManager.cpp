#include "GameManager.h"
#include "../Scene/ScenesImport.h"

#include "../Utility/Input/InputManager.h"
#include "../Utility/Resource/Mesh/SkeletalMesh.h"
#include "../Utility/Resource/Graphic/Graphics2D/Graphics2D.h"
#include "../Utility/Resource/Graphic/Graphics3D/Graphics3D.h"
#include "../Utility/Resource/Sound/Sound.h"

GameManager::GameManager() : 
	Game("Game", 1024, 768, 1.0f, TRUE)
{
}

void GameManager::start()
{
	// ƒJƒƒ‰‚Ì•`‰æãŒÀ‚Æ‰ºŒÀ‚Ìİ’è
	SetCameraNearFar(0.1f, 1000.0f);

	sceneManager_.add(Scene::Loading, std::make_shared<LoadingScene>());
	sceneManager_.add(Scene::Title, std::make_shared<TitleScene>());
	sceneManager_.add(Scene::GamePlay, std::make_shared<GamePlayScene>());
	sceneManager_.change(Scene::Loading);
}

void GameManager::update()
{
	InputManager::GetInstance().GetHitKeyFrameAll();

	sceneManager_.update(1.0f);
}

void GameManager::draw()
{
	sceneManager_.draw();
}

void GameManager::end()
{
	sceneManager_.end();
	SkeletalMesh::finalize();
	Graphics2D::finalize();
	Graphics3D::finalize();
	Sound::finalize();
}
