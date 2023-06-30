#include "Game.pch.h"
#include "Project.h"
//end Shaidors

#include "Components\ComponentHandler.h"
#include "Components\Physics\Collisions\CollisionManager.h"
#include "Assets\AssetLoader.h"
#include "ComponentTools\SceneManager.h"
#include "Components\ComponentDemo.h"

//Not too fond of settings not loading correctly
#include "ProjectSettings.h"


std::shared_ptr<NetMessageHandler> Project::netMessageHandler;
std::shared_ptr<NetworkGameManager> Project::netGameManger;
double Project::myUpdateFrameTime;

void Project::Setup()
{

#pragma region Components setup

	ComponentHandler::RegisterComponent<ComponentDemo>();

#pragma endregion


	ProjectSettings::LoadProjectSettings();

	
	if (!EDITORMODE)
	{	
		AssetLoader::LoadAsset("Assets/Scenes/SplashScreen.scene");
		AssetLoader::LoadAsset("Assets/UI/MainMenu/StartupImage.dds");
		AssetLoader::ThreadedLoading();

		auto& worldInstancing = AssetRegistry::GetInstance()->GetAsset<Scene>("SplashScreen");
		Engine::GetInstance()->GetSceneManager()->LoadScene(worldInstancing);
	}
}


void Project::Update()
{
	if (PLAYMODE)
	{
		PerformanceManager::BeginTimer("Project", "Whole Frame");
	
		PerformanceManager::StopTimer("Project");
	}
}

void Project::Start()
{
}

double Project::RenderProjectFrameTime(float aTotalFrameTime)
{
	std::string data = std::to_string((myUpdateFrameTime) * 1000.0f) + " ms";
	bool open = ImGui::TreeNodeEx("Project Frame: ", ImGuiTreeNodeFlags_FramePadding | ImGuiTreeNodeFlags_Leaf);
	ImGui::SameLine();
	ImGui::Text(&data[0]);
	data = std::to_string((myUpdateFrameTime / aTotalFrameTime) * 100.0f) + " %%";
	ImGui::SameLine();
	ImGui::Text(&data[0]);
	if (open) 
	{
		ImGui::TreePop();
	}
	return myUpdateFrameTime;
}
