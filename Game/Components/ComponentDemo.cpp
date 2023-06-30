#include "Game.pch.h"
#include "ComponentDemo.h"
#include "Components\3D\ModelInstance.h"
#include "Assets\Model.h"

void ComponentDemo::Awake()
{
	auto model = AssetRegistry::GetInstance()->GetAsset<Model>("Sven");
	myGameObject->GetComponent<ModelInstance>()->SetModel(model);
}

void ComponentDemo::Update()
{
	float moveX = 0;
	float moveZ = 0;

	moveX += Input::GetKeyHeld(KeyCode::D);
	moveX -= Input::GetKeyHeld(KeyCode::A);
	moveZ += Input::GetKeyHeld(KeyCode::W);
	moveZ -= Input::GetKeyHeld(KeyCode::S);

	myTransform->Translate(moveX * 3 * deltaTime, 0, moveZ * 3 * deltaTime);
}
