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
	CameraComponent.SetRenderingEnabled(false);

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

	DeletePointsComputeShader = RESOURCE_MANAGER.CreateShader("DeletePointsComputeShader",
															  nullptr, nullptr,
															  nullptr, nullptr,
															  nullptr, RESOURCE_MANAGER.LoadGLSL("Resources//PointCloudShaders//PointCloud_DeletePoints_CS.glsl").c_str());
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
	WhiteCylinderTransform.SetScale(glm::vec3(VR_MANAGER.SelectionRayWideness, 0.1f, VR_MANAGER.SelectionRayWideness));
	WhiteCylinderTransform.SetRotation(glm::vec3(0.0f, 0.0f, 90.0f));

	InteractionRayEntity = SCENE_RESOURCES.GetMainScene()->CreateEntity("Interaction Ray Cylinder");
	InteractionRayEntity->AddComponent<FEGameModelComponent>(WhiteCylinderGameModel);
	FEGameModelComponent& MouseRayCylinderGameModelComponent = InteractionRayEntity->GetComponent<FEGameModelComponent>();
	MouseRayCylinderGameModelComponent.SetReceivingShadows(false);
	InteractionRayEntity->SetComponentVisible(ComponentVisibilityType::GAME_MODEL, false);
	FETransformComponent& InteractionRayTransform = InteractionRayEntity->GetComponent<FETransformComponent>();
	InteractionRayTransform.SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	InteractionRayTransform.SetScale(glm::vec3(VR_MANAGER.SelectionRayWideness, 0.03f, VR_MANAGER.SelectionRayWideness));
	InteractionRayTransform.SetRotation(glm::vec3(90.0f, 0.0f, 0.0f));
}

void SceneResources::DeletePoints(glm::vec3 Center, float Radius)
{
	if (PointCloudEntity == nullptr)
		return;

	for (size_t i = 0; i < VR_MANAGER.SphereCursorEntities.size(); i++)
	{
		if (VR_MANAGER.SphereCursorEntities[i] == nullptr)
			return;

		if (!VR_MANAGER.SphereCursorEntities[i]->IsComponentVisible(ComponentVisibilityType::GAME_MODEL))
			return;
	}

	DeletePointsComputeShader->Start();

	uint32_t Zero = 0;
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, VR_MANAGER.DeletionFlagBuffer);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, VR_MANAGER.DeletionFlagBuffer);
	glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, sizeof(uint32_t), &Zero);
	glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

	DeletePointsComputeShader->UpdateUniformData("FEWorldMatrix", PointCloudEntity->GetComponent<FETransformComponent>().GetWorldMatrix());
	DeletePointsComputeShader->UpdateUniformData("Center", Center);
	DeletePointsComputeShader->UpdateUniformData("Radius", Radius);
	DeletePointsComputeShader->LoadUniformsDataToGPU();

	FEPointCloud* PointCloud = PointCloudEntity->GetComponent<FEPointCloudComponent>().GetPointCloud();
	static const size_t MaxBytesPerBuffer = UINT32_MAX - 1;
	static const size_t MaxPointsPerBuffer = MaxBytesPerBuffer / sizeof(FEPointCloudVertex);
	
	if (PointCloud->GetPointCount() > MaxPointsPerBuffer)
	{
		std::vector<GLuint> ComputeShaderBuffers;
		PointCloud->GetComputeShaderBuffers(ComputeShaderBuffers);

		size_t BufferIndex = 0;
		for (size_t i = 0; i < PointCloud->GetPointCount(); i += MaxPointsPerBuffer)
		{
			if (BufferIndex < ComputeShaderBuffers.size())
			{
				FE_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, ComputeShaderBuffers[BufferIndex]));
				FE_GL_ERROR(glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, ComputeShaderBuffers[BufferIndex]));
				BufferIndex++;

				// Calculate the number of points for the current buffer
				size_t NumberOfPoints = std::min(MaxPointsPerBuffer, PointCloud->GetPointCount() - i);
				DeletePointsComputeShader->Dispatch(static_cast<GLuint>((NumberOfPoints / 1024) + 1), 1, 1);
				FE_GL_ERROR(glMemoryBarrier(GL_ALL_BARRIER_BITS));
			}
		}
	}
	else
	{
		GLuint ComputeShaderBuffer;
		if (PointCloud->GetComputeShaderBuffer(ComputeShaderBuffer))
		{
			FE_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, ComputeShaderBuffer));
			FE_GL_ERROR(glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, ComputeShaderBuffer));

			DeletePointsComputeShader->Dispatch(static_cast<GLuint>((PointCloud->GetPointCount() / 1024) + 1), 1, 1);
			FE_GL_ERROR(glMemoryBarrier(GL_ALL_BARRIER_BITS));
		}
	}

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, VR_MANAGER.DeletionFlagBuffer);
	uint32_t* DeletionFlagValue = (uint32_t*)glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_READ_ONLY);
	bool bWasAnyPointDeleted = (*DeletionFlagValue > 0);
	glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

	if (bWasAnyPointDeleted)
		FEOpenXR_INPUT.TriggerHapticFeedback(0.1f, 0.1f, 0.2f, false);
}

#include "../VRManager/VRManager.h"
void SceneResources::CallBackWhenPointCloudIsLoaded(FEPointCloud* LoadedPointCloud)
{
	if (LoadedPointCloud != nullptr)
	{
		LoadedPointCloud->SetAdvancedRenderingEnabled(true);
		if (SCENE_RESOURCES.PointCloudEntity == nullptr)
			SCENE_RESOURCES.PointCloudEntity = SCENE_RESOURCES.MainScene->CreateEntity("Point Cloud Entity");

		if (SCENE_RESOURCES.PointCloudEntity->HasComponent<FEPointCloudComponent>())
		{
			SCENE_RESOURCES.PointCloudEntity->GetComponent<FEPointCloudComponent>().SetPointCloud(LoadedPointCloud);
		}
		else
		{
			SCENE_RESOURCES.PointCloudEntity->AddComponent<FEPointCloudComponent>(LoadedPointCloud);
		}

		VR_MANAGER.SetHaveActivePointCloud(true, SCENE_RESOURCES.PointCloudEntity);
	}
	else
	{
		VR_MANAGER.SetHaveActivePointCloud(false, nullptr);
	}

	VR_MANAGER.PlaceInFrontOfCamera(SCENE_RESOURCES.PointCloudEntity, OpenXR_MANAGER.GetVRHeadsetEntity());

	VR_MANAGER.SetLoadingInProgress(false);
	VR_MANAGER.CloseMainMenu();
}

void SceneResources::LoadPointCloudFromFile(const std::string& FilePath)
{
	auto ProcessRawData = [&](std::vector<FEPointCloudVertexDouble>& RawData) {
		for (size_t i = 0; i < RawData.size(); i++)
		{
			if (RawData[i].X < OriginalMin.x)
				OriginalMin.x = RawData[i].X;

			if (RawData[i].X > OriginalMax.x)
				OriginalMax.x = RawData[i].X;

			if (RawData[i].Y < OriginalMin.y)
				OriginalMin.y = RawData[i].Y;

			if (RawData[i].Y > OriginalMax.y)
				OriginalMax.y = RawData[i].Y;

			if (RawData[i].Z < OriginalMin.z)
				OriginalMin.z = RawData[i].Z;

			if (RawData[i].Z > OriginalMax.z)
				OriginalMax.z = RawData[i].Z;

			if (RawData[i].R == 0 && RawData[i].G == 0 && RawData[i].B == 0)
			{
				RawData[i].R = 255;
				RawData[i].G = 255;
				RawData[i].B = 255;
			}
		}

		glm::dvec3 Extent = abs(OriginalMax - OriginalMin);
		glm::dvec3 Center = OriginalMin + Extent / 2.0;

		for (size_t i = 0; i < RawData.size(); i++)
		{
			RawData[i].X = RawData[i].X - Center.x;
			RawData[i].Y = RawData[i].Y - Center.y;
			RawData[i].Z = RawData[i].Z - Center.z;
		}

		ReCenteredMin = OriginalMin - Center;
		ReCenteredMax = OriginalMax - Center;
		MaxExtent = std::max({ Extent.x, Extent.y, Extent.z });

		// Normalize to fit into a cube 1x1x1
		for (size_t i = 0; i < RawData.size(); i++)
		{
			glm::dvec3 NewPosition = glm::dvec3(RawData[i].X, RawData[i].Y, RawData[i].Z);
			NewPosition = (NewPosition - ReCenteredMin) / MaxExtent;

			RawData[i].X = NewPosition.x;
			RawData[i].Y = NewPosition.y;
			RawData[i].Z = NewPosition.z;
		}

		PositionShift = Center;
	};

	RESOURCE_MANAGER.ImportLasOrLazPointCloudAsync(FilePath, CallBackWhenPointCloudIsLoaded, false, ProcessRawData);
}

void SceneResources::SavePointCloudToFile(const std::string& FilePath)
{
	if (PointCloudEntity == nullptr)
		return;

	if (!PointCloudEntity->HasComponent<FEPointCloudComponent>())
		return;

	FEPointCloud* PointCloud = PointCloudEntity->GetComponent<FEPointCloudComponent>().GetPointCloud();
	if (PointCloud == nullptr)
		return;

	std::vector<FEPointCloudVertex> RawData = PointCloud->GetRawData();
	std::vector<FEPointCloudVertex> NonDeletedPoints;
	for (size_t i = 0; i < RawData.size(); i++)
	{
		if (!(RawData[i].A == 0))
		{
			glm::dvec3 ConvertedPosition = glm::dvec3(RawData[i].X, RawData[i].Y, RawData[i].Z);
			ConvertedPosition = (ConvertedPosition) * MaxExtent + ReCenteredMin + PositionShift;

			RawData[i].X = float(ConvertedPosition.x);
			RawData[i].Y = float(ConvertedPosition.y);
			RawData[i].Z = float(ConvertedPosition.z);

			NonDeletedPoints.push_back(RawData[i]);
		}
	}

	RESOURCE_MANAGER.SaveRawDataToLASOrLAZ(NonDeletedPoints, FilePath, true, 0.0001);
}

void SceneResources::ClearPointCloud()
{
	if (PointCloudEntity == nullptr)
		return;

	VR_MANAGER.SetHaveActivePointCloud(false, nullptr);

	MainScene->DeleteEntity(PointCloudEntity);
	PointCloudEntity = nullptr;

	OriginalMin = glm::dvec3(DBL_MAX);
	OriginalMax = glm::dvec3(-DBL_MAX);
	ReCenteredMin = glm::dvec3(DBL_MAX);
	ReCenteredMax = glm::dvec3(-DBL_MAX);
	PositionShift = glm::dvec3(0.0);
	MaxExtent = 0.0;
}