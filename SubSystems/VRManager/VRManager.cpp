#include "VRManager.h"

VRManager::VRManager()
{
	EntitiesToManipulate.push_back(nullptr);
}

void VRManager::Initialize()
{
	FEOpenXR_INPUT.SetRightTriggerPressCallBack(&VRManager::OnRightTriggerPress);
	FEOpenXR_INPUT.SetRightTriggerReleaseCallBack(&VRManager::OnRightTriggerRelease);

	FEOpenXR_INPUT.SetLeftTriggerPressCallBack(&VRManager::OnLeftTriggerPress);
	FEOpenXR_INPUT.SetLeftTriggerReleaseCallBack(&VRManager::OnLeftTriggerRelease);

	// "A" Button
	FEOpenXR_INPUT.SetLeftAButtonPressCallBack(&VRManager::OnLeftAButtonPress);
	FEOpenXR_INPUT.SetLeftAButtonReleaseCallBack(&VRManager::OnLeftAButtonRelease);

	FEOpenXR_INPUT.SetRightAButtonPressCallBack(&VRManager::OnRightAButtonPress);
	FEOpenXR_INPUT.SetRightAButtonReleaseCallBack(&VRManager::OnRightAButtonRelease);

	FEOpenXR_INPUT.SetLeftAButtonTouchActivateCallBack(&VRManager::OnLeftAButtonTouchActivate);
	FEOpenXR_INPUT.SetLeftAButtonTouchDeactivateCallBack(&VRManager::OnLeftAButtonTouchDeactivate);
	FEOpenXR_INPUT.SetRightAButtonTouchActivateCallBack(&VRManager::OnRightAButtonTouchActivate);
	FEOpenXR_INPUT.SetRightAButtonTouchDeactivateCallBack(&VRManager::OnRightAButtonTouchDeactivate);

	// "B" Button
	//FEOpenXR_INPUT.SetLeftBButtonPressCallBack(&VRManager::OnLeftBButtonPress);
	FEOpenXR_INPUT.SetLeftBButtonReleaseCallBack(&VRManager::OnLeftBButtonRelease);

	//FEOpenXR_INPUT.SetRightBButtonPressCallBack(&VRManager::OnRightBButtonPress);
	FEOpenXR_INPUT.SetRightBButtonReleaseCallBack(&VRManager::OnRightBButtonRelease);

	// Vive alternative
	FEOpenXR_INPUT.SetLeftViveSqueezePressCallBack(&VRManager::OnLeftAButtonPress);
	FEOpenXR_INPUT.SetLeftViveSqueezeReleaseCallBack(&VRManager::OnLeftAButtonRelease);

	FEOpenXR_INPUT.SetRightViveSqueezePressCallBack(&VRManager::OnRightAButtonPress);
	FEOpenXR_INPUT.SetRightViveSqueezeReleaseCallBack(&VRManager::OnRightAButtonRelease);

	InitializeSphereCursor();
}

void VRManager::InitializeSphereCursor()
{
	SphereCursorMeshes.resize(3);
	SphereCursorMeshes[0] = RESOURCE_MANAGER.LoadFEMesh("Resources/SphereCursor/TorusInnerMesh.model", "TorusInnerMesh");
	SphereCursorMeshes[1] = RESOURCE_MANAGER.LoadFEMesh("Resources/SphereCursor/TorusMiddleMesh.model", "TorusMiddleMesh");
	SphereCursorMeshes[2] = RESOURCE_MANAGER.LoadFEMesh("Resources/SphereCursor/TorusOuterMesh.model", "TorusOuterMesh");

	FEShader* SolidColorShader = RESOURCE_MANAGER.GetShader("6917497A5E0C05454876186F"/*"FESolidColorShader"*/);
	SphereCursorMaterial = RESOURCE_MANAGER.CreateMaterial();
	SphereCursorMaterial->Shader = SolidColorShader;
	SphereCursorMaterial->SetBaseColor(glm::vec3(0.9f, 0.9f, 0.9f));

	SphereCursorGameModels.resize(3);
	SphereCursorGameModels[0] = RESOURCE_MANAGER.CreateGameModel(SphereCursorMeshes[0], SphereCursorMaterial, "Sphere Cursor Inner Game Model");
	SphereCursorGameModels[1] = RESOURCE_MANAGER.CreateGameModel(SphereCursorMeshes[1], SphereCursorMaterial, "Sphere Cursor Middle Game Model");
	SphereCursorGameModels[2] = RESOURCE_MANAGER.CreateGameModel(SphereCursorMeshes[2], SphereCursorMaterial, "Sphere Cursor Outer Game Model");

	FEScene* MainScene = SCENE_RESOURCES.GetMainScene();
	SphereCursorEntities.resize(3);
	SphereCursorEntities[0] = MainScene->CreateEntity("Sphere Cursor Inner Entity");
	SphereCursorEntities[0]->AddComponent<FEGameModelComponent>(SphereCursorGameModels[0]);
	SphereCursorEntities[1] = MainScene->CreateEntity("Sphere Cursor Middle Entity");
	SphereCursorEntities[1]->AddComponent<FEGameModelComponent>(SphereCursorGameModels[1]);
	SphereCursorEntities[2] = MainScene->CreateEntity("Sphere Cursor Outer Entity");
	SphereCursorEntities[2]->AddComponent<FEGameModelComponent>(SphereCursorGameModels[2]);

	glm::vec3 SphereCursorPosition = glm::vec3(-0.010f, -0.020f, -0.150f);
	float SphereCursorScale = 0.06f;
	for (size_t i = 0; i < SphereCursorEntities.size(); i++)
	{
		FETransformComponent& SphereCursorTransform = SphereCursorEntities[i]->GetComponent<FETransformComponent>();
		SphereCursorTransform.SetPosition(SphereCursorPosition);
		SphereCursorTransform.SetScale(glm::vec3(SphereCursorScale));
	}

	for (size_t i = 0; i < SphereCursorEntities.size(); i++)
		SphereCursorEntities[i]->SetComponentVisible(ComponentVisibilityType::GAME_MODEL, false);
}

float VRManager::ControllerDistance()
{
	return glm::length(FEOpenXR_INPUT.GetLeftControllerPosition() - FEOpenXR_INPUT.GetRightControllerPosition());
}

void VRManager::CheckShouldScaleWorldActivate()
{
	if (bLeftControllerScalingJustGotActive && bRightControllerScalingJustGotActive)
	{
		SetScalingWithControllers(true);

		bLeftControllerScalingJustGotActive = false;
		bRightControllerScalingJustGotActive = false;

		if (VR_MANAGER.CurrentEntityToManipulate != nullptr)
		{
			InitialControllerDistanceForScale = ControllerDistance();
			FETransformComponent& EntityToManipulateTransform = VR_MANAGER.CurrentEntityToManipulate->GetComponent<FETransformComponent>();
			InitialEntityScale = EntityToManipulateTransform.GetScale();
			OriginalEntityPosition = EntityToManipulateTransform.GetPosition();

			FEEntity* LeftControllerEntity = OpenXR_MANAGER.GetLeftControllerEntity();
			FETransformComponent& LeftControllerTransform = LeftControllerEntity->GetComponent<FETransformComponent>();

			FEEntity* RightControllerEntity = OpenXR_MANAGER.GetRightControllerEntity();
			FETransformComponent& RightControllerTransform = RightControllerEntity->GetComponent<FETransformComponent>();

			OriginalPivotPosition = 0.5f * (LeftControllerTransform.GetPosition(FE_WORLD_SPACE) + RightControllerTransform.GetPosition(FE_WORLD_SPACE)) * TranslateScale;
		}
	}

	if (bLeftControllerScalingJustGotInActive || bRightControllerScalingJustGotInActive)
	{
		bLeftControllerScalingJustGotInActive = false;
		bRightControllerScalingJustGotInActive = false;

		SetScalingWithControllers(false);
	}
}

void VRManager::UpdateWhiteCylinder()
{
	FETransformComponent& WhiteCylinderTransform = SCENE_RESOURCES.GetWhiteCylinderEntity()->GetComponent<FETransformComponent>();

	if (bScalingWithControllersActive)
	{
		WhiteCylinderTransform.SetPosition(CurrentPivotPosition);
		float OriginalLength = 2.0f;

		WhiteCylinderTransform.SetScale(glm::vec3(0.00075f, ControllerDistance() / OriginalLength, 0.00075f) * VRRigScale);

		// Assumes cylinder is oriented along y-axis
		glm::vec3 DefaultCylinderDirection = glm::vec3(0, 1, 0);
		glm::vec3 Direction = glm::normalize(FEOpenXR_INPUT.GetLeftControllerPosition() - FEOpenXR_INPUT.GetRightControllerPosition());
		glm::quat Rotation = glm::rotation(DefaultCylinderDirection, Direction);
		WhiteCylinderTransform.SetQuaternion(Rotation);
	}
	else
	{
		//FETransformComponent& InteractionRayTransform = SCENE_RESOURCES.GetInteractionRayCylinderEntity()->GetComponent<FETransformComponent>();
		//InteractionRayTransform.SetScale(glm::vec3(0.00075f, 1000.1f, 0.00075f)/*, FE_WORLD_SPACE*/);
	}
}

void VRManager::ScaleWorldUpdate()
{
	CheckShouldScaleWorldActivate();
	UpdateWhiteCylinder();

	bool bShouldBeVisible = ((bLeftAButtonTouched && bRightAButtonTouched) || bScalingWithControllersActive) && (GetCurrentEntityToManipulate() != nullptr);
	SCENE_RESOURCES.GetRedCylinderEntity()->SetComponentVisible(ComponentVisibilityType::GAME_MODEL, bShouldBeVisible);
	SCENE_RESOURCES.GetGreenCylinderEntity()->SetComponentVisible(ComponentVisibilityType::GAME_MODEL, bShouldBeVisible);
	SCENE_RESOURCES.GetBlueCylinderEntity()->SetComponentVisible(ComponentVisibilityType::GAME_MODEL, bShouldBeVisible);

	bool bShouldInteractionRayBeVisible = bScalingWithControllersActive && (GetCurrentEntityToManipulate() != nullptr);
	SCENE_RESOURCES.GetWhiteCylinderEntity()->SetComponentVisible(ComponentVisibilityType::GAME_MODEL, bShouldInteractionRayBeVisible);

	if (bShouldBeVisible)
	{
		if (VR_MANAGER.CurrentEntityToManipulate != nullptr)
		{
			FEEntity* LeftControllerEntity = OpenXR_MANAGER.GetLeftControllerEntity();
			FETransformComponent& LeftControllerTransform = LeftControllerEntity->GetComponent<FETransformComponent>();

			FEEntity* RightControllerEntity = OpenXR_MANAGER.GetRightControllerEntity();
			FETransformComponent& RightControllerTransform = RightControllerEntity->GetComponent<FETransformComponent>();

			CurrentPivotPosition = 0.5f * (LeftControllerTransform.GetPosition(FE_WORLD_SPACE) + RightControllerTransform.GetPosition(FE_WORLD_SPACE)) * TranslateScale;

			SCENE_RESOURCES.GetRedCylinderEntity()->GetComponent<FETransformComponent>().SetPosition(CurrentPivotPosition);
			SCENE_RESOURCES.GetGreenCylinderEntity()->GetComponent<FETransformComponent>().SetPosition(CurrentPivotPosition);
			SCENE_RESOURCES.GetBlueCylinderEntity()->GetComponent<FETransformComponent>().SetPosition(CurrentPivotPosition);

			if (bScalingWithControllersActive)
			{
				float Delta = ControllerDistance() - InitialControllerDistanceForScale;

				if (!isnan(exp(Delta * 10.f) * InitialEntityScale.x) &&
					!isnan(exp(Delta * 10.f) * InitialEntityScale.y) &&
					!isnan(exp(Delta * 10.f) * InitialEntityScale.z))
				{
					// Each frame if scaling is active
					glm::vec3 NewScale = glm::vec3(exp(Delta * 10.0f) * InitialEntityScale);
					// The pivot position in the original scaled space
					glm::vec3 OriginalPivotRelativePosition = (OriginalPivotPosition - OriginalEntityPosition) / InitialEntityScale;
					// The position of the pivot point in the new scaled space
					glm::vec3 ScaledPivotPosition = OriginalPivotRelativePosition * NewScale;

					FETransformComponent& EntityToManipulateTransform = CurrentEntityToManipulate->GetComponent<FETransformComponent>();
					EntityToManipulateTransform.SetScale(NewScale);

					// Adjust the PointCloudPosition to ensure the pivot point remains at the same position in the scaled space
					glm::vec3 NewPosition = OriginalPivotPosition - ScaledPivotPosition;

					// Make sure that we can move data while scaling
					NewPosition -= OriginalPivotPosition - CurrentPivotPosition;
					EntityToManipulateTransform.SetPosition(NewPosition, FE_COORDINATE_SPACE_TYPE::FE_WORLD_SPACE);
				}
			}
		}
	}
}

void VRManager::OnRightTriggerPress()
{
	if (VR_MANAGER.bShowInterface)
		VR_MANAGER.CurrentVirtualUI->InvokeMouseButton(ImGuiMouseButton_Left, GLFW_PRESS);
	
	VR_MANAGER.bSphereCursorIsActive = true;
	VR_MANAGER.bRightControllerTriggerIsPressed = true;
}

void VRManager::OnRightTriggerRelease()
{
	if (VR_MANAGER.bShowInterface)
	{
		VR_MANAGER.CurrentVirtualUI->InvokeMouseButton(ImGuiMouseButton_Left, GLFW_RELEASE);
		FEVirtualUIComponent& VirtualUIComponent = VR_MANAGER.VRUIEntity->GetComponent<FEVirtualUIComponent>();
		if (!VirtualUIComponent.IsLastProvidedRayIntersectingCanvas())
		{
			
		}
	}

	VR_MANAGER.bSphereCursorIsActive = false;
	VR_MANAGER.bRightControllerTriggerIsPressed = false;
}

void VRManager::OnLeftTriggerPress()
{
	if (!VR_MANAGER.VR_MANAGER.bShowInterface)
		SCENE_RESOURCES.TryToAttachEntities(VR_MANAGER.CurrentEntityToManipulate, OpenXR_MANAGER.GetLeftControllerEntity(), true);
	
	VR_MANAGER.bSphereCursorIsActive = true;
	VR_MANAGER.bLeftControllerTriggerIsPressed = true;
}

void VRManager::OnLeftTriggerRelease()
{
	VR_MANAGER.bLeftControllerTriggerIsPressed = false;

	VR_MANAGER.ReleaseEntity();
}

void VRManager::OnLeftAButtonPress()
{
	VR_MANAGER.bLeftControllerScalingJustGotActive = true;
}

void VRManager::OnRightAButtonPress()
{
	VR_MANAGER.bRightControllerScalingJustGotActive = true;
}

void VRManager::OnLeftAButtonRelease()
{
	VR_MANAGER.bLeftControllerScalingJustGotInActive = true;

	if (VR_MANAGER.bScalingWithControllersActive)
		return;

	// Or check if the left B button was pressed

	uint64_t CurrentTimeStamp = TIME.GetTimeStamp();
	uint64_t TimeSinceLeftBButtonRelease = CurrentTimeStamp - VR_MANAGER.RightAButtonReleaseTimeStamp;
	if (TimeSinceLeftBButtonRelease > 100)
	{
		FEEntity* InteractionRayEntity = SCENE_RESOURCES.GetInteractionRayEntity();
		FEGameModelComponent& InteractionRayModelComponent = InteractionRayEntity->GetComponent<FEGameModelComponent>();
		FEVirtualUIComponent& VirtualUIComponent = VR_MANAGER.VRUIEntity->GetComponent<FEVirtualUIComponent>();

		VR_MANAGER.bShowInterface = !VR_MANAGER.bShowInterface;
		VR_MANAGER.VRUIEntity->SetComponentVisible(ComponentVisibilityType::VIRTUAL_UI, VR_MANAGER.bShowInterface);
		VirtualUIComponent.SetInputActive(VR_MANAGER.bShowInterface);
		InteractionRayEntity->SetComponentVisible(ComponentVisibilityType::GAME_MODEL, VR_MANAGER.bShowInterface);
	}
}

void VRManager::OnRightAButtonRelease()
{
	VR_MANAGER.bRightControllerScalingJustGotInActive = true;

	VR_MANAGER.RightAButtonReleaseTimeStamp = TIME.GetTimeStamp();
}

void VRManager::OnLeftAButtonTouchActivate()
{
	VR_MANAGER.bLeftAButtonTouched = true;
}

void VRManager::OnLeftAButtonTouchDeactivate()
{
	VR_MANAGER.bLeftAButtonTouched = false;
}

void VRManager::OnRightAButtonTouchActivate()
{
	VR_MANAGER.bRightAButtonTouched = true;
}

void VRManager::OnRightAButtonTouchDeactivate()
{
	VR_MANAGER.bRightAButtonTouched = false;
}

void VRManager::OnLeftBButtonRelease()
{
	//VR_MANAGER.LeftBButtonReleaseTimeStamp = TIME.GetTimeStamp();
}

void VRManager::OnRightBButtonRelease()
{
	//VR_MANAGER.RightBButtonReleaseTimeStamp = TIME.GetTimeStamp();
}

void VRManager::Update()
{
	static bool bAttached = false;
	if (OpenXR_MANAGER.GetLeftControllerEntity() != nullptr && !bAttached)
	{
		AttachVirtualUIToController();
		bAttached = true;
	}

	// Ensure that VR camera have a black background
	FEEntity* VRCamera = OpenXR_MANAGER.GetVRHeadsetEntity();
	if (VRCamera != nullptr)
	{
		FECameraComponent& CameraComponent = VRCamera->GetComponent<FECameraComponent>();
		if (CameraComponent.GetClearColor()[0] != 0.0f)
			CameraComponent.SetClearColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	}

	//bool bLeftControllerWasActiveCurrentFrame = false;
	//bool bRightControllerWasActiveCurrentFrame = false;

	//if (IsControllerSelectionModeActive() && MODE_MANAGER.GetCurrentMode() != INTERACTION_MODE::SUPER_GRID)
	//{
	//	bShowInterface = false;
	//	SetControllerSelectionModeActive(false);

	//	FEEntity* InteractionRayCylinderEntity = SCENE_RESOURCES.GetInteractionRayCylinderEntity();
	//	FEGameModelComponent& InteractionRayModelComponent = InteractionRayCylinderEntity->GetComponent<FEGameModelComponent>();
	//	InteractionRayCylinderEntity->SetVisible(ComponentVisibilityType::GAME_MODEL, false);
	//}

	//if (FEOpenXR_INPUT.IsLeftControllerConnectedAndTracked() && OpenXR_MANAGER.GetLeftControllerEntity() != nullptr)
	//{
	//	bLeftControllerWasActiveCurrentFrame = true;
	//}
	//else
	//{
	//	OnControllerDisconnected();
	//	/*if (VRUIEntity != nullptr)
	//	{
	//		FEVirtualUIComponent& VirtualUIComponent = VRUIEntity->GetComponent<FEVirtualUIComponent>();

	//		VirtualUIComponent.SetVisibility(false);
	//		VirtualUIComponent.SetInputActive(false);
	//	}*/
	//	
	//	//VR_MANAGER.bShowInterface = false;
	//}

	//if (FEOpenXR_INPUT.IsRightControllerConnectedAndTracked() && OpenXR_MANAGER.GetRightControllerEntity() != nullptr)
	//{
	//	bRightControllerWasActiveCurrentFrame = true;
	//	static bool bFistTimeRightControllerActive = true;
	//	if (bFistTimeRightControllerActive)
	//	{
	//		bFistTimeRightControllerActive = false;
	//		for (size_t i = 0; i < SphereCursorEntities.size(); i++)
	//		{
	//			if (SphereCursorEntities[0] != nullptr)
	//			{
	//				SCENE_RESOURCES.TryToAttachEntities(SphereCursorEntities[i], OpenXR_MANAGER.GetRightControllerEntity(), false);
	//			}
	//		}
	//	}

	//	for (size_t i = 0; i < SphereCursorEntities.size(); i++)
	//	{
	//		if (SphereCursorEntities[0] != nullptr)
	//		{
	//			FEGameModelComponent& SphereCursorModelComponent = SphereCursorEntities[i]->GetComponent<FEGameModelComponent>();
	//			SphereCursorEntities[i]->SetVisible(ComponentVisibilityType::GAME_MODEL, false);
	//		}
	//	}
	//}
	//else if (!FEOpenXR_INPUT.IsRightControllerConnectedAndTracked() || OpenXR_MANAGER.GetRightControllerEntity() != nullptr)
	//{
	//	OnControllerDisconnected(false);
	//}

	//if (!bLeftControllerWasActiveLastFrame && bLeftControllerWasActiveCurrentFrame)
	//{
	//	OnControllerReConnected();
	//	/*if (VR_MANAGER.bShowInterface && MODE_MANAGER.IsInDeveloperMode())
	//	{
	//		FEVirtualUIComponent& VirtualUIComponent = VR_MANAGER.VRUIEntity->GetComponent<FEVirtualUIComponent>();

	//		VirtualUIComponent.SetVisibility(true);
	//		VirtualUIComponent.SetInputActive(true);

	//		AttachVirtualUIToController();
	//	}*/
	//}

	//if (!bRightControllerWasActiveLastFrame && bRightControllerWasActiveCurrentFrame)
	//{
	//	OnControllerReConnected(false);
	//	//if (bShowInterface)
	//	//{
	//	//	// Ensure that interaction ray is reattached to the right controller
	//	//	AttachInteractionRayToController();
	//	//	SCENE_RESOURCES.GetInteractionRayCylinderEntity()->GetComponent<FEGameModelComponent>().SetVisibility(true);
	//	//}
	//}

	//if (VR_MANAGER.IsControllerSelectionModeActive())
	//{
	//	std::pair<glm::vec3, glm::vec3> InteractionRayData = GetControllerInteractionRay(false);
	//	glm::vec3 SelectionRayOrigin = InteractionRayData.first;
	//	glm::dvec3 SelectionRayDirection = InteractionRayData.second;

	//	SUPERCELL_MANAGER.UpdateHighlightedCellsBasedOnRay(SelectionRayDirection, SelectionRayOrigin, 70.0f);
	//}

	//if (SCENE_RESOURCES.GetAllResourcesRootEntity() != nullptr)
	//{
	//	bool bFound = false;
	//	for (size_t i = 0; i < EntitiesToManipulate.size(); i++)
	//	{
	//		if (EntitiesToManipulate[i] == SCENE_RESOURCES.GetAllResourcesRootEntity())
	//		{
	//			bFound = true;
	//			break;
	//		}
	//	}

	//	if (!bFound)
	//	{
	//		EntitiesToManipulate.push_back(SCENE_RESOURCES.GetAllResourcesRootEntity());
	//		VR_MANAGER.SetCurrentEntityToManipulate(SCENE_RESOURCES.GetAllResourcesRootEntity());
	//	}
	//}
	
	ScaleWorldUpdate();
	InitializeVirtualUI();

	if (UIAdded)
	{
		FEVirtualUIComponent& VirtualUIComponent = VRUIEntity->GetComponent<FEVirtualUIComponent>();

		if (bShowInterface)
		{
			std::pair<glm::vec3, glm::vec3> InteractionRayData = GetControllerInteractionRay(false);
			VirtualUIComponent.UpdateInteractionRay(InteractionRayData.first, InteractionRayData.second);
			VirtualUIComponent.UpdateRayIntersection();
		}
	}

	if (bRightControllerTriggerIsPressed)
	{

	}

	AnimateSphereCursor();
}

void VRManager::AnimateSphereCursor()
{
	if (SphereCursorEntities.size() == 3 && SphereCursorEntities[0] != nullptr && SphereCursorEntities[1] != nullptr && SphereCursorEntities[2] != nullptr)
	{
		double TimeEscaped = ENGINE.GetGpuTime() + ENGINE.GetCpuTime();
		double RotationAmount = 0.35 * TimeEscaped;

		FETransformComponent& SphereCursorInnerTransform = SphereCursorEntities[0]->GetComponent<FETransformComponent>();
		SphereCursorInnerTransform.RotateAroundAxis(glm::vec3(1.0f, 0.0f, 0.0f), RotationAmount, FE_COORDINATE_SPACE_TYPE::FE_LOCAL_SPACE);

		FETransformComponent& SphereCursorMiddleTransform = SphereCursorEntities[1]->GetComponent<FETransformComponent>();
		SphereCursorMiddleTransform.RotateAroundAxis(glm::vec3(0.0f, .0f, 1.0f), RotationAmount, FE_COORDINATE_SPACE_TYPE::FE_LOCAL_SPACE);

		FETransformComponent& SphereCursorOuterTransform = SphereCursorEntities[2]->GetComponent<FETransformComponent>();
		SphereCursorOuterTransform.RotateAroundAxis(glm::vec3(1.0f, 0.0f, 0.0f), RotationAmount, FE_COORDINATE_SPACE_TYPE::FE_LOCAL_SPACE);
		SphereCursorOuterTransform.RotateAroundAxis(glm::vec3(0.0f, 0.0f, 1.0f), RotationAmount, FE_COORDINATE_SPACE_TYPE::FE_LOCAL_SPACE);
	}

	glm::vec3 SphereCursorColor = glm::vec3(0.9f, 0.9f, 0.9f);
	if (bSphereCursorIsActive)
		SphereCursorColor = glm::vec3(0.9f, 0.0f, 0.0f);
	
	SphereCursorMaterial->SetBaseColor(SphereCursorColor);
}

void VRManager::InitializeVirtualUI()
{
	if (!UIAdded)
	{
		FEScene* MainScene = SCENE_RESOURCES.GetMainScene();
		if (MainScene == nullptr)
			return;
		
		if (OpenXR_MANAGER.GetLeftControllerEntity() == nullptr || OpenXR_MANAGER.GetRightControllerEntity() == nullptr)
			return;

		glm::vec2 FileDialogResolution = glm::vec2(600.0f, 400.0f);

		VRUIEntity = SCENE_RESOURCES.GetMainScene()->CreateEntity("VR Interface");
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
		VirtualUIComponent.SetInputActive(false);
		CurrentVirtualUI = VirtualUIComponent.GetVirtualUI();
		VRUIEntity->SetComponentVisible(ComponentVisibilityType::VIRTUAL_UI, false);

		AttachVirtualUIToController();
		AttachInteractionRayToController();
		UIAdded = true;
	}
}

void VRManager::AttachVirtualUIToController()
{
	FEScene* MainScene = SCENE_RESOURCES.GetMainScene();
	if (MainScene == nullptr)
		return;

	if (OpenXR_MANAGER.GetLeftControllerEntity() == nullptr)
		return;

	SCENE_RESOURCES.TryToAttachEntities(VRUIEntity, OpenXR_MANAGER.GetLeftControllerEntity(), false);
	SCENE_RESOURCES.TryToAttachEntities(SCENE_RESOURCES.GetInteractionRayEntity(), OpenXR_MANAGER.GetRightControllerEntity(), false);
}

void VRManager::AttachInteractionRayToController()
{
	FEScene* MainScene = SCENE_RESOURCES.GetMainScene();
	if (MainScene == nullptr)
		return;

	if (OpenXR_MANAGER.GetRightControllerEntity() == nullptr)
		return;

	FEEntity* InteractionRayEntity = SCENE_RESOURCES.GetInteractionRayEntity();
	SCENE_RESOURCES.TryToAttachEntities(InteractionRayEntity, OpenXR_MANAGER.GetRightControllerEntity(), false);
}

void VRManager::VRInterfaceRender(FEVirtualUI* CurrentVirtualUI)
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
			if (FILE_SYSTEM.DoesFileExist(Result))
			{
				SCENE_RESOURCES.LoadPointCloudFromFile(Result);
				VR_MANAGER.SetCurrentEntityToManipulate(SCENE_RESOURCES.GetPointCloudEntity());
			}
		}

		ifd::FileDialog::Instance().Close();
	}
}

std::pair<glm::vec3, glm::vec3> VRManager::GetControllerInteractionRay(bool bLeftController) const
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

bool VRManager::IsControllerSelectionModeActive() const
{
	return bControllerSelectionMode;
}

void VRManager::SetControllerSelectionModeActive(bool bActive)
{
	bControllerSelectionMode = bActive;
}

FEEntity* VRManager::GetCurrentEntityToManipulate() const
{
	return CurrentEntityToManipulate;
}

void VRManager::SetCurrentEntityToManipulate(FEEntity* NewEntity)
{
	if (CurrentEntityToManipulate != nullptr)
		ReleaseEntity();
	
	CurrentEntityToManipulate = NewEntity;
}

void VRManager::ReleaseEntity()
{
	if (CurrentEntityToManipulate == nullptr)
		return;

	FENaiveSceneGraphNode* NodeToManipulate = SCENE_RESOURCES.GetMainScene()->SceneGraph.GetNodeByEntityID(CurrentEntityToManipulate->GetObjectID());
	FENaiveSceneGraphNode* ControllerNode = SCENE_RESOURCES.GetMainScene()->SceneGraph.GetNodeByEntityID(OpenXR_MANAGER.GetLeftControllerEntity()->GetObjectID());

	if (NodeToManipulate == nullptr || ControllerNode == nullptr)
		return;

	// If the controller node is not a parent of the node to manipulate, we cannot release it
	if (ControllerNode->GetChild(NodeToManipulate->GetObjectID()) == nullptr)
		return;

	SCENE_RESOURCES.GetMainScene()->SceneGraph.MoveNode(NodeToManipulate->GetObjectID(), SCENE_RESOURCES.GetMainScene()->SceneGraph.GetRoot()->GetObjectID(), true);
}

void VRManager::SetScalingWithControllers(bool bNewValue)
{
	if (bScalingWithControllersActive && !bNewValue)
		LastTimeControllerScalingWasActive = TIME.GetTimeStamp();
	
	bScalingWithControllersActive = bNewValue;
}

void VRManager::OnControllerDisconnected(bool bLeftController)
{
	if (bLeftController)
	{
		if (VRUIEntity != nullptr)
		{
			FEVirtualUIComponent& VirtualUIComponent = VRUIEntity->GetComponent<FEVirtualUIComponent>();

			VRUIEntity->SetComponentVisible(ComponentVisibilityType::VIRTUAL_UI, false);
			VirtualUIComponent.SetInputActive(false);
		}
	}
	else
	{
		SCENE_RESOURCES.GetInteractionRayEntity()->SetComponentVisible(ComponentVisibilityType::GAME_MODEL, false);

		for (size_t i = 0; i < SphereCursorEntities.size(); i++)
		{
			if (SphereCursorEntities[0] != nullptr)
			{
				FEGameModelComponent& SphereCursorModelComponent = SphereCursorEntities[i]->GetComponent<FEGameModelComponent>();
				SphereCursorEntities[i]->SetComponentVisible(ComponentVisibilityType::GAME_MODEL, false);
			}
		}
	}
}

void VRManager::OnControllerReConnected(bool bLeftController)
{
	if (bLeftController)
	{
		if (VR_MANAGER.bShowInterface)
		{
			FEVirtualUIComponent& VirtualUIComponent = VR_MANAGER.VRUIEntity->GetComponent<FEVirtualUIComponent>();

			VR_MANAGER.VRUIEntity->SetComponentVisible(ComponentVisibilityType::VIRTUAL_UI, true);
			VirtualUIComponent.SetInputActive(true);

			AttachVirtualUIToController();
		}
	}
	else
	{
		if (bShowInterface)
		{
			// Ensure that interaction ray is reattached to the right controller
			AttachInteractionRayToController();
			SCENE_RESOURCES.GetInteractionRayEntity()->SetComponentVisible(ComponentVisibilityType::GAME_MODEL, true);
		}
	}
}

// First time the controller is connected, we need to set the callbacks
void VRManager::OnControllerConnected(bool bLeftController)
{

}