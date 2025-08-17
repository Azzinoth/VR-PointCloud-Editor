#include "SubSystems/FocalEngine/FEngine.h"
using namespace FocalEngine;

#include "ThirdParty/ImFileDialog/ImFileDialog.h"

void ShowTransformConfiguration(FEObject* Object, FETransformComponent* Transform, float PositionStep = 0.001f)
{
	// ********************* POSITION *********************
	glm::vec3 Position = Transform->GetPosition();
	ImGui::Text((std::string("Position of ") + Object->GetName() + " :").c_str());
	ImGui::SameLine();
	ImGui::SetNextItemWidth(50);
	ImGui::DragFloat((std::string("##X pos : ") + Object->GetName()).c_str(), &Position[0], PositionStep);

	ImGui::SameLine();
	ImGui::SetNextItemWidth(50);
	ImGui::DragFloat((std::string("##Y pos : ") + Object->GetName()).c_str(), &Position[1], PositionStep);

	ImGui::SameLine();
	ImGui::SetNextItemWidth(50);
	ImGui::DragFloat((std::string("##Z pos : ") + Object->GetName()).c_str(), &Position[2], PositionStep);
	Transform->SetPosition(Position);

	// ********************* ROTATION *********************
	glm::vec3 Rotation = Transform->GetRotation();

	ImGui::Text((std::string("Rotation of ") + Object->GetName() + " :").c_str());
	ImGui::SameLine();
	ImGui::SetNextItemWidth(50);
	ImGui::DragFloat((std::string("##X rot : ") + Object->GetName()).c_str(), &Rotation[0], 0.1f, -360.0f, 360.0f);

	ImGui::SameLine();
	ImGui::SetNextItemWidth(50);
	ImGui::DragFloat((std::string("##Y rot : ") + Object->GetName()).c_str(), &Rotation[1], 0.1f, -360.0f, 360.0f);

	ImGui::SameLine();
	ImGui::SetNextItemWidth(50);
	ImGui::DragFloat((std::string("##Z rot : ") + Object->GetName()).c_str(), &Rotation[2], 0.1f, -360.0f, 360.0f);
	Transform->SetRotation(Rotation);

	// ********************* SCALE *********************
	bool bUniformScaling = Transform->IsUniformScalingSet();
	ImGui::Checkbox("Uniform scaling", &bUniformScaling);
	Transform->SetUniformScaling(bUniformScaling);

	glm::vec3 Scale = Transform->GetScale();
	ImGui::Text((std::string("Scale of ") + Object->GetName() + " :").c_str());
	ImGui::SameLine();
	ImGui::SetNextItemWidth(50);
	ImGui::DragFloat((std::string("##X scale : ") + Object->GetName()).c_str(), &Scale[0], 0.001f, 0.001f, 1000.0f);

	ImGui::SameLine();
	ImGui::SetNextItemWidth(50);
	ImGui::DragFloat((std::string("##Y scale : ") + Object->GetName()).c_str(), &Scale[1], 0.001f, 0.001f, 1000.0f);

	ImGui::SameLine();
	ImGui::SetNextItemWidth(50);
	ImGui::DragFloat((std::string("##Z scale : ") + Object->GetName()).c_str(), &Scale[2], 0.001f, 0.001f, 1000.0f);

	Transform->SetScale(Scale, FE_LOCAL_SPACE);
}

FEScene* MainScene = nullptr;
FEEntity* MainCamera = nullptr;
FEEntity* Sun = nullptr;

FEEntity* VRUIEntity = nullptr;
FEVirtualUI* CurrentVirtualUI = nullptr;
void VRInterfaceRender(FEVirtualUI* CurrentVirtualUI);

FEEntity* SelectionRayEntity = nullptr;

void VRInterfaceRender(FEVirtualUI* CurrentVirtualUI)
{
	static bool bOpenFileDialog = false;
	if (!bOpenFileDialog)
	{
		ifd::FileDialog::Instance().Open("PointCloudOpenDialog", "Open a point cloud", "Point cloud file (*.laz;*.las){.laz,.las},.*");
		bOpenFileDialog = true;
	}

	ImGui::SetNextWindowPos(ImVec2(0, 0));
	if (ifd::FileDialog::Instance().IsDone("PointCloudOpenDialog"))
	{
		if (ifd::FileDialog::Instance().HasResult())
		{
			std::string Result = ifd::FileDialog::Instance().GetResult().u8string();
			printf("OPEN[%s]\n", Result.c_str());
		}

		ifd::FileDialog::Instance().Close();
	}
}

bool TryToAttachEntities(FEEntity* WhatToAttach, FEEntity* WhereToAttach, bool bPreserveWorldTransform)
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

bool AttachVirtualUIToController()
{
	if (OpenXR_MANAGER.GetLeftControllerEntity() == nullptr)
		return false;

	TryToAttachEntities(VRUIEntity, OpenXR_MANAGER.GetLeftControllerEntity(), false);
	TryToAttachEntities(SelectionRayEntity, OpenXR_MANAGER.GetRightControllerEntity(), false);

	return true;
}

void SetupScene()
{
	MainScene = SCENE_MANAGER.CreateScene("Main scene", "", FESceneFlag::Active | FESceneFlag::Renderable | FESceneFlag::GameMode);
	MainCamera = MainScene->CreateEntity("Main camera");

	FEPrefab* FreeCameraPrefab = RESOURCE_MANAGER.GetPrefab("4575527C773848040760656F");
	std::vector<FEEntity*> AddedEntities = SCENE_MANAGER.InstantiatePrefab(FreeCameraPrefab, MainScene, true);
	MainCamera = AddedEntities[0];
	CAMERA_SYSTEM.SetMainCamera(MainCamera);
	CAMERA_SYSTEM.SetCameraViewport(MainCamera, ENGINE.GetDefaultViewport()->GetID());

	CAMERA_SYSTEM.SetCameraRenderingPipeline(MainCamera, FERenderingPipeline::Forward_Simplified);
	FECameraComponent& CameraComponent = MainCamera->GetComponent<FECameraComponent>();
	CameraComponent.SetClearColor(glm::vec4(0.0f));
	CameraComponent.SetNearPlane(0.01f);
	CameraComponent.SetFarPlane(10000.0f);
	//CameraComponent.SetActive(false);

	Sun = MainScene->CreateEntity("Sun");
	Sun->GetComponent<FETransformComponent>().SetRotation(glm::vec3(0.0f, 45.0f, 45.0f));
	Sun->AddComponent<FELightComponent>(FE_DIRECTIONAL_LIGHT);
	FELightComponent& SunLightComponent = Sun->GetComponent<FELightComponent>();
	SunLightComponent.SetCastShadows(false);
	SunLightComponent.SetIntensity(2.0f);

	// Selection Ray
	FEMesh* CylinderMesh = RESOURCE_MANAGER.LoadFEMesh("Resources//Cylinder.model");

	FEShader* SolidColorShader = RESOURCE_MANAGER.GetShader("6917497A5E0C05454876186F"/*"FESolidColorShader"*/);
	// FIX ME: Work of this shader is not correct.
	SolidColorShader->UpdateUniformData("BrightnessFactor", 1.0f);

	FEMaterial* SelectionRayMaterial = RESOURCE_MANAGER.CreateMaterial();
	SelectionRayMaterial->Shader = SolidColorShader;
	SelectionRayMaterial->SetBaseColor(glm::vec3(0.9f, 0.9f, 0.9f));
	FEGameModel* SelectionRayGameModel = RESOURCE_MANAGER.CreateGameModel(CylinderMesh, SelectionRayMaterial);
	SelectionRayGameModel->SetName("White Cylinder Game Model");

	SelectionRayEntity = MainScene->CreateEntity("Selection Ray Entity");
	SelectionRayEntity->AddComponent<FEGameModelComponent>(SelectionRayGameModel);
	FEGameModelComponent& WhiteCylinderGameModelComponent = SelectionRayEntity->GetComponent<FEGameModelComponent>();
	WhiteCylinderGameModelComponent.SetReceivingShadows(false);
	SelectionRayEntity->SetComponentVisible(ComponentVisibilityType::GAME_MODEL, false);
	FETransformComponent& SelectionRayTransform = SelectionRayEntity->GetComponent<FETransformComponent>();
	SelectionRayTransform.SetPosition(glm::vec3(0.0f, 0.0f, -0.052f));
	SelectionRayTransform.SetScale(glm::vec3(0.00045f, 0.03f, 0.00045f));
	SelectionRayTransform.SetRotation(glm::vec3(90.0f, 0.0f, 0.0f));

	// Temporary
	SelectionRayEntity->SetComponentVisible(ComponentVisibilityType::GAME_MODEL, true);
}

std::pair<glm::vec3, glm::vec3> GetControllerInteractionRay(bool bLeftController)
{
	FEEntity* ControllerEntity = bLeftController ? OpenXR_MANAGER.GetLeftControllerEntity() : OpenXR_MANAGER.GetRightControllerEntity();
	if (ControllerEntity == nullptr)
		return std::make_pair(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));

	FETransformComponent& ControllerTransform = ControllerEntity->GetComponent<FETransformComponent>();
	glm::vec3 ControllerPosition = ControllerTransform.GetPosition(FE_WORLD_SPACE);
	glm::quat ControllerOrientation = ControllerTransform.GetQuaternion();
	glm::vec3 InteractionRay = glm::vec3(0.0f, 0.0f, -1.0f);
	InteractionRay = glm::vec3(glm::toMat4(ControllerOrientation) * glm::vec4(InteractionRay, 1.0f));

	return std::make_pair(ControllerPosition, InteractionRay);
}

void OnRightTriggerPress()
{
	CurrentVirtualUI->InvokeMouseButton(ImGuiMouseButton_Left, GLFW_PRESS);
}

void OnRightTriggerRelease()
{
	CurrentVirtualUI->InvokeMouseButton(ImGuiMouseButton_Left, GLFW_RELEASE);
}

void OnLeftTriggerPress()
{
	
}

void OnLeftTriggerRelease()
{
	
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ENGINE.InitWindow(1270, 720, "Cloud Bathymetry");
	ENGINE.SetVsyncEnabled(false);
	THREAD_POOL.SetConcurrentThreadCount(10);

	const int FrameCountTillMeasure = 20;
	double CPUFrameDurations[FrameCountTillMeasure] = { 0.0f };
	double GPUFrameDurations[FrameCountTillMeasure] = { 0.0f };
	int FrameCounter = 0;

	double AverageCpuFrameDuration = 0.0;
	double AverageGpuFrameDuration = 0.0;

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

	SetupScene();
	bool bIsVRActive = ENGINE.EnableVR();

	glm::vec2 FileDialogResolution = glm::vec2(600.0f, 400.0f);

	VRUIEntity = MainScene->CreateEntity("VR Interface");
	FETransformComponent& VRUITransform = VRUIEntity->GetComponent<FETransformComponent>();
	VRUITransform.SetPosition(glm::vec3(0.0f, 0.007f, -0.046f));
	VRUITransform.SetRotation(glm::vec3(0.0f, 90.0f, 90.0f));
	float AspectRatio = FileDialogResolution.x / FileDialogResolution.y;
	float BaseScale = 0.0375f;
	glm::vec3 Scale = glm::vec3(BaseScale / AspectRatio, BaseScale, BaseScale);
	VRUITransform.SetScale(Scale);

	VRUIEntity->AddComponent<FEVirtualUIComponent>();
	FEVirtualUIComponent& VirtualUIComponent = VRUIEntity->GetComponent<FEVirtualUIComponent>();
	VirtualUIComponent.SetCanvasResolution(FileDialogResolution);
	VirtualUIComponent.SetRenderFunction(VRInterfaceRender);
	VirtualUIComponent.SetWindowToListen(APPLICATION.GetMainWindow());
	VirtualUIComponent.SetMouseButtonPassThrough(true);
	VirtualUIComponent.SetMouseMovePassThrough(true);
	VirtualUIComponent.SetCharPassThrough(true);
	VirtualUIComponent.SetKeyPassThrough(true);
	VirtualUIComponent.SetScrollPassThrough(true);
	VirtualUIComponent.SetInputActive(true); // by default should be false
	CurrentVirtualUI = VirtualUIComponent.GetVirtualUI();

	FEOpenXR_INPUT.SetRightTriggerPressCallBack(OnRightTriggerPress);
	FEOpenXR_INPUT.SetRightTriggerReleaseCallBack(OnRightTriggerRelease);

	FEOpenXR_INPUT.SetLeftTriggerPressCallBack(OnLeftTriggerPress);
	FEOpenXR_INPUT.SetLeftTriggerReleaseCallBack(OnLeftTriggerRelease);

	while (ENGINE.IsNotTerminated())
	{
		ENGINE.BeginFrame();
		ENGINE.Render();

		static bool bAttached = false;
		if (OpenXR_MANAGER.GetLeftControllerEntity() != nullptr && !bAttached)
		{
			bAttached = AttachVirtualUIToController();
		}

		if (bAttached)
		{
			FETransformComponent& VRInterfaceTransform = VRUIEntity->GetComponent<FETransformComponent>();
			ShowTransformConfiguration(VRUIEntity, &VRInterfaceTransform);

			/*FETransformComponent& SelectionRayTransform = SelectionRayEntity->GetComponent<FETransformComponent>();
			ShowTransformConfiguration(SelectionRayEntity, &SelectionRayTransform);*/

			std::pair<glm::vec3, glm::vec3> InteractionRayData = GetControllerInteractionRay(false);
			VirtualUIComponent.UpdateInteractionRay(InteractionRayData.first, InteractionRayData.second);
			VirtualUIComponent.UpdateRayIntersection();
		}

		ENGINE.EndFrame();

		// CPU and GPU Time
		CPUFrameDurations[FrameCounter] = ENGINE.GetCpuTime();
		GPUFrameDurations[FrameCounter] = ENGINE.GetGpuTime();
		FrameCounter++;

		if (FrameCounter > FrameCountTillMeasure - 1)
		{
			AverageCpuFrameDuration = 0.0f;
			AverageGpuFrameDuration = 0.0f;
			for (size_t i = 0; i < FrameCountTillMeasure; i++)
			{
				AverageCpuFrameDuration += CPUFrameDurations[i];
				AverageGpuFrameDuration += GPUFrameDurations[i];
			}
			AverageCpuFrameDuration /= FrameCountTillMeasure;
			AverageGpuFrameDuration /= FrameCountTillMeasure;

			FrameCounter = 0;
		}

		std::string CPUMs = std::to_string(AverageCpuFrameDuration);
		CPUMs.erase(CPUMs.begin() + 4, CPUMs.end());

		std::string GPUMs = std::to_string(AverageGpuFrameDuration);
		GPUMs.erase(GPUMs.begin() + 4, GPUMs.end());

		std::string FrameMs = std::to_string(AverageCpuFrameDuration + AverageGpuFrameDuration);
		FrameMs.erase(FrameMs.begin() + 4, FrameMs.end());

		std::string caption = "CPU time : ";
		caption += CPUMs;
		caption += " ms";
		caption += "  GPU time : ";
		caption += GPUMs;
		caption += " ms";
		caption += "  Frame time : ";
		caption += FrameMs;
		caption += " ms";

		ENGINE.SetWindowCaption(caption.c_str());
	}

	return 0;
}