#include "SceneResources.h"
#include "../VRManager/VRManager.h"

SceneResources::SceneResources()
{
	
}

void SceneResources::Initialize()
{
	SetupScene();
	InitResourses();
}

FEScene* SceneResources::GetMainScene()
{
	return MainScene;
}

FEEntity* SceneResources::GetMainCamera()
{ 
	return MainCamera;
}

void SceneResources::SetupScene()
{
	MainScene = SCENE_MANAGER.CreateScene("Main scene", "", FESceneFlag::Active | FESceneFlag::Renderable | FESceneFlag::GameMode);
	MainCamera = SCENE_RESOURCES.GetMainScene()->CreateEntity("Main camera");

	FEPrefab* FreeCameraPrefab = RESOURCE_MANAGER.GetPrefab("4575527C773848040760656F");
	std::vector<FEEntity*> AddedEntities = SCENE_MANAGER.InstantiatePrefab(FreeCameraPrefab, SCENE_RESOURCES.GetMainScene(), true);
	MainCamera = AddedEntities[0];
	CAMERA_SYSTEM.SetMainCamera(MainCamera);
	CAMERA_SYSTEM.SetCameraViewport(MainCamera, ENGINE.GetDefaultViewport()->GetID());

	CAMERA_SYSTEM.SetCameraRenderingPipeline(MainCamera, FERenderingPipeline::Forward_Simplified);
	FECameraComponent& CameraComponent = MainCamera->GetComponent<FECameraComponent>();
	CameraComponent.SetClearColor(glm::vec4(0.0f));
	CameraComponent.SetNearPlane(0.01f);
	CameraComponent.SetFarPlane(10000.0f);
	CameraComponent.SetActive(false);

	Sun = SCENE_RESOURCES.GetMainScene()->CreateEntity("Sun");
	Sun->GetComponent<FETransformComponent>().SetRotation(glm::vec3(0.0f, 45.0f, 45.0f));
	Sun->AddComponent<FELightComponent>(FE_DIRECTIONAL_LIGHT);
	FELightComponent& SunLightComponent = Sun->GetComponent<FELightComponent>();
	SunLightComponent.SetCastShadows(false);
	SunLightComponent.SetIntensity(2.0f);

	ifd::FileDialog::Instance().CreateTexture = [](uint8_t* Data, int Width, int Height, char TextureFormat) -> void* {
		GLuint TextureID;

		glGenTextures(1, &TextureID);
		glBindTexture(GL_TEXTURE_2D, TextureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Width, Height, 0, (TextureFormat == 0) ? GL_BGRA : GL_RGBA, GL_UNSIGNED_BYTE, Data);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);

		return (void*)TextureID;
	};

	ifd::FileDialog::Instance().DeleteTexture = [](void* TexturePointer) {
		GLuint texID = (GLuint)((uintptr_t)TexturePointer);
		glDeleteTextures(1, &texID);
	};
}

void SceneResources::InitResourses()
{
	FEMesh* ValveIndexRightControllerMesh = RESOURCE_MANAGER.LoadFEMesh("Resources//ValveIndexRightController.model");
	FEMesh* ValveIndexLeftControllerMesh = RESOURCE_MANAGER.LoadFEMesh("Resources//ValveIndexLeftController.model");

	FEMaterial* NewMaterial = RESOURCE_MANAGER.CreateMaterial();
	NewMaterial->Shader = RESOURCE_MANAGER.GetShader("0800253C242B05321A332D09"/*"FEPBRShader"*/);
	NewMaterial->SetAlbedoMap(RESOURCE_MANAGER.LoadFETexture("Resources//ValveIndexControllerAlbedo.texture"));

	// Cylinders
	FEMesh* CylinderMesh = RESOURCE_MANAGER.LoadFEMesh("Resources//Cylinder.model");

	FEShader* SolidColorShader = RESOURCE_MANAGER.GetShader("6917497A5E0C05454876186F"/*"FESolidColorShader"*/);
	// FIX ME: Work of this shader is not correct.
	SolidColorShader->UpdateUniformData("BrightnessFactor", 1.0f);

	FEMaterial* GreenMaterial = RESOURCE_MANAGER.CreateMaterial();
	GreenMaterial->Shader = SolidColorShader;
	GreenMaterial->SetBaseColor(glm::vec3(0.0f, 1.0f, 0.0f));
	FEGameModel* GreenCylinderGameModel = RESOURCE_MANAGER.CreateGameModel(CylinderMesh, GreenMaterial);

	FEMaterial* RedMaterial = RESOURCE_MANAGER.CreateMaterial();
	RedMaterial->Shader = SolidColorShader;
	RedMaterial->SetBaseColor(glm::vec3(1.0f, 0.0f, 0.0f));
	FEGameModel* RedCylinderGameModel = RESOURCE_MANAGER.CreateGameModel(CylinderMesh, RedMaterial);

	FEMaterial* BlueMaterial = RESOURCE_MANAGER.CreateMaterial();
	BlueMaterial->Shader = SolidColorShader;
	BlueMaterial->SetBaseColor(glm::vec3(0.0f, 0.0f, 1.0f));
	FEGameModel* BlueCylinderGameModel = RESOURCE_MANAGER.CreateGameModel(CylinderMesh, BlueMaterial);

	FEMaterial* WhiteMaterial = RESOURCE_MANAGER.CreateMaterial();
	WhiteMaterial->Shader = SolidColorShader;
	WhiteMaterial->SetBaseColor(glm::vec3(0.9f, 0.9f, 0.9f));
	FEGameModel* WhiteCylinderGameModel = RESOURCE_MANAGER.CreateGameModel(CylinderMesh, WhiteMaterial);
	WhiteCylinderGameModel->SetName("White Cylinder Game Model");

	GreenCylinderEntity = SCENE_RESOURCES.GetMainScene()->CreateEntity("Green Cylinder");
	GreenCylinderEntity->AddComponent<FEGameModelComponent>(GreenCylinderGameModel);
	FEGameModelComponent& GreenCylinderGameModelComponent = GreenCylinderEntity->GetComponent<FEGameModelComponent>();
	GreenCylinderGameModelComponent.SetReceivingShadows(false);
	GreenCylinderEntity->SetComponentVisible(ComponentVisibilityType::GAME_MODEL, false);
	FETransformComponent& GreenCylinderTransform = GreenCylinderEntity->GetComponent<FETransformComponent>();
	GreenCylinderTransform.SetScale(glm::vec3(0.001f, 0.01f, 0.001f));

	RedCylinderEntity = SCENE_RESOURCES.GetMainScene()->CreateEntity("Red Cylinder");
	RedCylinderEntity->AddComponent<FEGameModelComponent>(RedCylinderGameModel);
	FEGameModelComponent& RedCylinderGameModelComponent = RedCylinderEntity->GetComponent<FEGameModelComponent>();
	RedCylinderGameModelComponent.SetReceivingShadows(false);
	RedCylinderEntity->SetComponentVisible(ComponentVisibilityType::GAME_MODEL, false);
	FETransformComponent& RedCylinderTransform = RedCylinderEntity->GetComponent<FETransformComponent>();
	RedCylinderTransform.SetScale(glm::vec3(0.001f, 0.01f, 0.001f));
	RedCylinderTransform.SetRotation(glm::vec3(90.0f, 0.0f, 0.0f));

	BlueCylinderEntity = SCENE_RESOURCES.GetMainScene()->CreateEntity("Blue Cylinder");
	BlueCylinderEntity->AddComponent<FEGameModelComponent>(BlueCylinderGameModel);
	FEGameModelComponent& BlueCylinderGameModelComponent = BlueCylinderEntity->GetComponent<FEGameModelComponent>();
	BlueCylinderGameModelComponent.SetReceivingShadows(false);
	BlueCylinderEntity->SetComponentVisible(ComponentVisibilityType::GAME_MODEL, false);
	FETransformComponent& BlueCylinderTransform = BlueCylinderEntity->GetComponent<FETransformComponent>();
	BlueCylinderTransform.SetScale(glm::vec3(0.001f, 0.01f, 0.001f));
	BlueCylinderTransform.SetRotation(glm::vec3(0.0f, 0.0f, 90.0f));

	WhiteCylinderEntity = SCENE_RESOURCES.GetMainScene()->CreateEntity("White Cylinder");
	WhiteCylinderEntity->AddComponent<FEGameModelComponent>(WhiteCylinderGameModel);
	FEGameModelComponent& WhiteCylinderGameModelComponent = WhiteCylinderEntity->GetComponent<FEGameModelComponent>();
	WhiteCylinderGameModelComponent.SetReceivingShadows(false);
	WhiteCylinderEntity->SetComponentVisible(ComponentVisibilityType::GAME_MODEL, false);
	FETransformComponent& WhiteCylinderTransform = WhiteCylinderEntity->GetComponent<FETransformComponent>();
	WhiteCylinderTransform.SetScale(glm::vec3(0.00075f, 0.1f, 0.00075f));
	WhiteCylinderTransform.SetRotation(glm::vec3(0.0f, 0.0f, 90.0f));

	InteractionRayEntity = SCENE_RESOURCES.GetMainScene()->CreateEntity("Interaction Ray Cylinder");
	InteractionRayEntity->AddComponent<FEGameModelComponent>(WhiteCylinderGameModel);
	FEGameModelComponent& MouseRayCylinderGameModelComponent = InteractionRayEntity->GetComponent<FEGameModelComponent>();
	MouseRayCylinderGameModelComponent.SetReceivingShadows(false);
	InteractionRayEntity->SetComponentVisible(ComponentVisibilityType::GAME_MODEL, false);
	FETransformComponent& InteractionRayTransform = InteractionRayEntity->GetComponent<FETransformComponent>();
	InteractionRayTransform.SetPosition(glm::vec3(0.0f, 0.0f, -0.052f));
	InteractionRayTransform.SetScale(glm::vec3(0.00045f, 0.03f, 0.00045f));
	InteractionRayTransform.SetRotation(glm::vec3(90.0f, 0.0f, 0.0f));
}

bool SceneResources::TryToAttachEntities(FEEntity* WhatToAttach, FEEntity* WhereToAttach, bool bPreserveWorldTransform)
{
	if (WhereToAttach == nullptr || WhatToAttach == nullptr)
		return false;

	if (WhereToAttach->GetParentScene() != WhatToAttach->GetParentScene())
		return false;

	FEScene* SceneToUse = WhereToAttach->GetParentScene();

	FENaiveSceneGraphNode* WhereToAttachNode = SceneToUse->SceneGraph.GetNodeByEntityID(WhereToAttach->GetObjectID());
	FENaiveSceneGraphNode* WhatToAttachNode = SceneToUse->SceneGraph.GetNodeByEntityID(WhatToAttach->GetObjectID());

	if (WhereToAttachNode == nullptr || WhatToAttachNode == nullptr)
		return false;

	return SceneToUse->SceneGraph.MoveNode(WhatToAttachNode->GetObjectID(), WhereToAttachNode->GetObjectID(), bPreserveWorldTransform);
}

//void SceneResources::FlagPoints(glm::vec3 Center, float Radius)
//{
//	if (AllSoundingsEntity == nullptr)
//		return;
//
//	PointCloudComputeShader->Start();
//	PointCloudComputeShader->UpdateUniformData("FEWorldMatrix", AllSoundingsEntity->GetComponent<FETransformComponent>().GetWorldMatrix());
//	PointCloudComputeShader->UpdateUniformData("Center", Center);
//	PointCloudComputeShader->UpdateUniformData("Radius", Radius);
//	PointCloudComputeShader->LoadUniformsDataToGPU();
//
//	FEPointCloud* PointCloud = AllSoundingsEntity->GetComponent<FEPointCloudComponent>().GetPointCloud();
//	GLuint ComputeShaderBuffer;
//	if (PointCloud->GetComputeShaderBuffer(ComputeShaderBuffer))
//	{
//		FE_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, ComputeShaderBuffer));
//		FE_GL_ERROR(glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, ComputeShaderBuffer));
//
//		PointCloudComputeShader->Dispatch(static_cast<GLuint>((PointCloud->GetPointCount() / 1024) + 1), 1, 1);
//		FE_GL_ERROR(glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT));
//	}
//}

void SceneResources::LoadPointCloudFromFile(const std::string& FilePath)
{
	FEPointCloud* LoadedPointCloud = RESOURCE_MANAGER.ImportPointCloud(FilePath);
	if (LoadedPointCloud != nullptr)
	{
		LoadedPointCloud->SetAdvancedRenderingEnabled(true);
		if (PointCloudEntity == nullptr)
			PointCloudEntity = MainScene->CreateEntity("Point Cloud Entity");

		if (PointCloudEntity->HasComponent<FEPointCloudComponent>())
		{
			PointCloudEntity->GetComponent<FEPointCloudComponent>().SetPointCloud(LoadedPointCloud);
		}
		else
		{
			PointCloudEntity->AddComponent<FEPointCloudComponent>(LoadedPointCloud);
		}
	}
}