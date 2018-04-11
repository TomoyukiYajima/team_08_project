#ifndef _SCENE_MGR_H_
#define _SCENE_MGR_H_

#include <unordered_map>
#include "Scene.h"
#include "IScenePtr.h"
//#include"SceneDataKeeper.h"
//#include"../MainMenu/SceneChange.h"

class SceneManager {
public:
	SceneManager(); //(SceneDataKeeper* keeper);
	void init();
	void update(float deltaTime);
	void draw() const;
	void end();
	void add(Scene name, const IScenePtr& scene);
	void change(Scene name);
	void sceneChanger();

private:
	// ÉRÉsÅ[ã÷é~
	SceneManager(const SceneManager& other) = delete;
	SceneManager& operator = (const SceneManager& other) = delete;

private:
	std::unordered_map<Scene, IScenePtr>scenes_;
	IScenePtr currentScene_;
	/*SceneDataKeeper* keeper_;
	SceneChange changer_;*/

	//int absnum;

	/*bool isFirst_;
	bool isMove_;*/

};

#endif