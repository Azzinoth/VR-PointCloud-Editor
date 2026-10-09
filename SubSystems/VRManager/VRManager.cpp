#include "VRManager.h"

void VRManager::SetImGuiStyleForVR()
{
	ImVec4* Colors = ImGui::GetStyle().Colors;
	Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	Colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.06f, 0.94f);
	Colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	Colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
	Colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
	Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	Colors[ImGuiCol_FrameBg] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
	Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.60f, 0.26f, 0.98f, 0.40f);
	Colors[ImGuiCol_FrameBgActive] = ImVec4(0.60f, 0.26f, 0.98f, 0.67f);
	Colors[ImGuiCol_TitleBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
	Colors[ImGuiCol_TitleBgActive] = ImVec4(0.31f, 0.16f, 0.48f, 1.00f);
	Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
	Colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
	Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
	Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
	Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
	Colors[ImGuiCol_CheckMark] = ImVec4(0.60f, 0.26f, 0.98f, 1.00f);
	Colors[ImGuiCol_SliderGrab] = ImVec4(0.54f, 0.24f, 0.88f, 1.00f);
	Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.60f, 0.26f, 0.98f, 1.00f);
	Colors[ImGuiCol_Button] = ImVec4(0.60f, 0.26f, 0.98f, 0.40f);
	Colors[ImGuiCol_ButtonHovered] = ImVec4(0.60f, 0.26f, 0.98f, 1.00f);
	Colors[ImGuiCol_ButtonActive] = ImVec4(0.49f, 0.06f, 0.98f, 1.00f);
	Colors[ImGuiCol_Header] = ImVec4(0.60f, 0.26f, 0.98f, 0.31f);
	Colors[ImGuiCol_HeaderHovered] = ImVec4(0.60f, 0.26f, 0.98f, 0.80f);
	Colors[ImGuiCol_HeaderActive] = ImVec4(0.60f, 0.26f, 0.98f, 1.00f);
	Colors[ImGuiCol_Separator] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
	Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.41f, 0.10f, 0.75f, 0.78f);
	Colors[ImGuiCol_SeparatorActive] = ImVec4(0.41f, 0.10f, 0.75f, 1.00f);
	Colors[ImGuiCol_ResizeGrip] = ImVec4(0.60f, 0.26f, 0.98f, 0.20f);
	Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.60f, 0.26f, 0.98f, 0.67f);
	Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.60f, 0.26f, 0.98f, 0.95f);
	Colors[ImGuiCol_TabHovered] = ImVec4(0.60f, 0.26f, 0.98f, 0.80f);
	Colors[ImGuiCol_Tab] = ImVec4(0.37f, 0.18f, 0.58f, 0.86f);
	Colors[ImGuiCol_TabSelected] = ImVec4(0.42f, 0.20f, 0.68f, 1.00f);
	Colors[ImGuiCol_TabSelectedOverline] = ImVec4(0.60f, 0.26f, 0.98f, 1.00f);
	Colors[ImGuiCol_TabDimmed] = ImVec4(0.11f, 0.07f, 0.15f, 0.97f);
	Colors[ImGuiCol_TabDimmedSelected] = ImVec4(0.27f, 0.14f, 0.42f, 1.00f);
	Colors[ImGuiCol_TabDimmedSelectedOverline] = ImVec4(0.50f, 0.50f, 0.50f, 0.00f);
	Colors[ImGuiCol_DockingPreview] = ImVec4(0.60f, 0.26f, 0.98f, 0.70f);
	Colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	Colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
	Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);
	Colors[ImGuiCol_TableBorderLight] = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);
	Colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	Colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
	Colors[ImGuiCol_TextLink] = ImVec4(0.60f, 0.26f, 0.98f, 1.00f);
	Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.53f, 0.53f, 0.53f, 0.45f);
	Colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
	Colors[ImGuiCol_NavCursor] = ImVec4(0.60f, 0.26f, 0.98f, 1.00f);
	Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
	Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
	Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
}

VRManager::VRManager()
{
	EntitiesToManipulate.push_back(nullptr);
}

void VRManager::Initialize()
{
	if (!ENGINE.IsVREnabled())
		return;
	
	FEOpenXR_INPUT.AddControllerStateChangeCallback(&VRManager::OnControllerConnectionStatusChangeCallBack);

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

	FEOpenXR_INPUT.SetLeftViveMenuClickCallBack(&VRManager::OnLeftViveMenuClick);

	InitializeSphereCursor();
	InitializeVirtualUI();
}

void VRManager::InitializeSphereCursor()
{
	SphereCursorMeshes.resize(3);
	// In the beginning, different meshes were used for inner, middle and outer parts of the cursor.
	SphereCursorMeshes[0] = RESOURCE_MANAGER.LoadFEMesh("Resources/SphereCursor/TorusMiddleMesh.model", "TorusMiddleMesh");
	SphereCursorMeshes[1] = SphereCursorMeshes[0];
	SphereCursorMeshes[2] = SphereCursorMeshes[1];

	FEShader* SolidColorShader = RESOURCE_MANAGER.GetShader(FEEngineResourceIDs::SolidColorShader);
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

	for (size_t i = 0; i < SphereCursorEntities.size(); i++)
	{
		FETransformComponent& SphereCursorTransform = SphereCursorEntities[i]->GetComponent<FETransformComponent>();
		SphereCursorTransform.SetPosition(SphereCursorPosition);
		SphereCursorTransform.SetScale(glm::vec3(SphereCursorScale));
	}

	for (size_t i = 0; i < SphereCursorEntities.size(); i++)
		SphereCursorEntities[i]->SetComponentVisible(ComponentVisibilityType::GAME_MODEL, false);

	glGenBuffers(1, &DeletionFlagBuffer);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, DeletionFlagBuffer);
	glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(uint32_t), nullptr, GL_DYNAMIC_READ);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, DeletionFlagBuffer);
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

		WhiteCylinderTransform.SetScale(glm::vec3(SelectionRayWideness, ControllerDistance() / OriginalLength, SelectionRayWideness) * VRRigScale);

		// Assumes cylinder is oriented along y-axis
		glm::vec3 DefaultCylinderDirection = glm::vec3(0, 1, 0);
		glm::vec3 Direction = glm::normalize(FEOpenXR_INPUT.GetLeftControllerPosition() - FEOpenXR_INPUT.GetRightControllerPosition());
		glm::quat Rotation = glm::rotation(DefaultCylinderDirection, Direction);
		WhiteCylinderTransform.SetQuaternion(Rotation);
	}
	else if (bShowInterface)
	{
		FEGameModelComponent& InteractionRayGameModelComponent = SCENE_RESOURCES.GetInteractionRayEntity()->GetComponent<FEGameModelComponent>();
		FEMaterial* InteractionRayMaterial = InteractionRayGameModelComponent.GetGameModel()->GetMaterial();
		InteractionRayMaterial->SetBaseColor(glm::vec4(1.0f));

		float RayLength = 100.0f;
		FEVirtualUIComponent& VirtualUIComponent = VR_MANAGER.VRUIEntity->GetComponent<FEVirtualUIComponent>();
		FEVirtualUIComponent& VirtualKeyboardUIComponent = VR_MANAGER.VRVirtualKeyboardEntity->GetComponent<FEVirtualUIComponent>();
		double DistanceToInterface = 0.0;
		if (VirtualUIComponent.IsLastProvidedRayIntersectingCanvas() && VR_MANAGER.VRUIEntity->IsComponentVisible(ComponentVisibilityType::VIRTUAL_UI))
			DistanceToInterface = VirtualUIComponent.GetLastRayIntersectionDistance();

		if (VirtualKeyboardUIComponent.IsLastProvidedRayIntersectingCanvas() && VR_MANAGER.VRVirtualKeyboardEntity->IsComponentVisible(ComponentVisibilityType::VIRTUAL_UI))
			DistanceToInterface = VirtualKeyboardUIComponent.GetLastRayIntersectionDistance();

		if ((VirtualUIComponent.IsLastProvidedRayIntersectingCanvas() && VR_MANAGER.VRUIEntity->IsComponentVisible(ComponentVisibilityType::VIRTUAL_UI)) ||
			(VirtualKeyboardUIComponent.IsLastProvidedRayIntersectingCanvas() && VR_MANAGER.VRVirtualKeyboardEntity->IsComponentVisible(ComponentVisibilityType::VIRTUAL_UI)))
		{
			RayLength = static_cast<float>(DistanceToInterface);
			InteractionRayMaterial->SetBaseColor(glm::vec4(0.0f, 0.95f, 0.0f, 1.0f));
		}

		// FIX ME: Ugly temporary workaround for incorrect ray thickness and position 
		// before the ray first intersects with a UI element.
		//
		// Root cause:
		//   - SetPosition() only updates the transform if the new value differs
		//     from the current one.
		//   - On the very first frame, the local transform is different, but the
		//     parent transform has not yet been updated, resulting in a wrong 
		//     final position.
		//   - On the next frame, the parent transform is updated correctly, but
		//     since the local transform hasn’t changed, SetPosition() does not
		//     trigger an update. This leaves the final position incorrect.
		//
		// Hack explanation:
		//   - Slightle oscillation of RayLength (+/- 0.001f every frame depending 
		//     on frame index parity) forces SetPosition() to register a 
		//     change and reapply the transform, ensuring the correct final 
		//     position is used once the parent transform is valid.
		auto FrameIndex = ENGINE.GetCurrentFrameIndex();
		if (FrameIndex % 2 == 0)
			RayLength = RayLength + 0.001f;
		else
			RayLength = RayLength - 0.001f;

		FETransformComponent& InteractionRayTransform = SCENE_RESOURCES.GetInteractionRayEntity()->GetComponent<FETransformComponent>();
		InteractionRayTransform.SetScale(glm::vec3(SelectionRayWideness, RayLength / 2.0f, SelectionRayWideness), FE_WORLD_SPACE);
		InteractionRayTransform.SetPosition(glm::vec3(0.0f, 0.0f, -RayLength * 0.1f), FE_LOCAL_SPACE);
		InteractionRayTransform.SetDirtyFlag(true);
	}
	else if (!bShowInterface)
	{
		FEGameModelComponent& InteractionRayGameModelComponent = SCENE_RESOURCES.GetInteractionRayEntity()->GetComponent<FEGameModelComponent>();
		FEMaterial* InteractionRayMaterial = InteractionRayGameModelComponent.GetGameModel()->GetMaterial();
		InteractionRayMaterial->SetBaseColor(glm::vec4(1.0f));

		float RayLength = 100.0f;
		FETransformComponent& InteractionRayTransform = SCENE_RESOURCES.GetInteractionRayEntity()->GetComponent<FETransformComponent>();
		InteractionRayTransform.SetScale(glm::vec3(SelectionRayWideness, RayLength / 2.0f, SelectionRayWideness), FE_WORLD_SPACE);
		InteractionRayTransform.SetPosition(glm::vec3(0.0f, 0.0f, -RayLength * 0.1f), FE_LOCAL_SPACE);
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
	{
		FEVirtualUIComponent& VirtualKeyboardUIComponent = VR_MANAGER.VRVirtualKeyboardEntity->GetComponent<FEVirtualUIComponent>();
		// If user is interacting with the keyboard we do not want to interact with the main UI,
		// to not break focus on the input text field.
		if (!VirtualKeyboardUIComponent.IsLastProvidedRayIntersectingCanvas())
			VR_MANAGER.CurrentVirtualUI->InvokeMouseButton(ImGuiMouseButton_Left, GLFW_PRESS);

		VR_MANAGER.CurrentVirtuaKeyboardlUI->InvokeMouseButton(ImGuiMouseButton_Left, GLFW_PRESS);
		FEVirtualUIComponent& VirtualUIComponent = VR_MANAGER.VRUIEntity->GetComponent<FEVirtualUIComponent>();

		if (!VirtualUIComponent.IsLastProvidedRayIntersectingCanvas() && !VirtualKeyboardUIComponent.IsLastProvidedRayIntersectingCanvas())
			VR_MANAGER.HideVirtualKeyboard();
	}
	
	VR_MANAGER.bSphereCursorIsActive = true;
	VR_MANAGER.bRightControllerTriggerIsPressed = true;
}

void VRManager::OnRightTriggerRelease()
{
	if (VR_MANAGER.bShowInterface)
	{
		VR_MANAGER.CurrentVirtualUI->InvokeMouseButton(ImGuiMouseButton_Left, GLFW_RELEASE);
		VR_MANAGER.CurrentVirtuaKeyboardlUI->InvokeMouseButton(ImGuiMouseButton_Left, GLFW_RELEASE);
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
		OpenXR_MANAGER.GetLeftControllerEntity()->AttachChild(VR_MANAGER.CurrentEntityToManipulate);
	
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
	VR_MANAGER.MenuClick();
}

void VRManager::OnLeftViveMenuClick()
{
	VR_MANAGER.MenuClick();
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
	
}

void VRManager::OnRightBButtonRelease()
{
	VR_MANAGER.bVirtualKeyboardIsActive = !VR_MANAGER.bVirtualKeyboardIsActive;
}

void VRManager::Update()
{
	if (OpenXR_MANAGER.GetVRRigEntity() == nullptr)
		return;

	// Ensure that VR camera have a black background
	FEEntity* VRCamera = OpenXR_MANAGER.GetVRHeadsetEntity();
	if (VRCamera != nullptr)
	{
		FECameraComponent& CameraComponent = VRCamera->GetComponent<FECameraComponent>();
		if (CameraComponent.GetClearColor()[0] != 0.0f)
			CameraComponent.SetClearColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	}
	
	ScaleWorldUpdate();

	if (VRUIEntity != nullptr)
	{
		FEVirtualUIComponent& VirtualUIComponent = VRUIEntity->GetComponent<FEVirtualUIComponent>();

		if (bShowInterface)
		{
			std::pair<glm::vec3, glm::vec3> InteractionRayData = GetControllerInteractionRay(false);
			VirtualUIComponent.UpdateInteractionRay(InteractionRayData.first, InteractionRayData.second);
			VirtualUIComponent.UpdateRayIntersection();
		}
	}

	if (VRVirtualKeyboardEntity != nullptr)
	{
		FEVirtualUIComponent& VirtualUIComponent = VRVirtualKeyboardEntity->GetComponent<FEVirtualUIComponent>();

		if (bShowInterface)
		{
			std::pair<glm::vec3, glm::vec3> InteractionRayData = GetControllerInteractionRay(false);
			VirtualUIComponent.UpdateInteractionRay(InteractionRayData.first, InteractionRayData.second);
			VirtualUIComponent.UpdateRayIntersection();
		}
	}

	if (bRightControllerTriggerIsPressed)
	{
		FEScene* MainScene = SCENE_RESOURCES.GetMainScene();
		FEAABB SphereCursorAABB = MainScene->GetEntityAABB(SphereCursorEntities[0]);

		SCENE_RESOURCES.DeletePoints(SphereCursorAABB.GetCenter(), SphereCursorAABB.GetLongestAxisLength() * SphereCursorActionScale);
	}

	if (!IsSphereCursorVisible() && bHaveActivePointCloud && !IsMainMenuVisible())
		ShowSphereCursor();

	AnimateSphereCursor();
}

void VRManager::RotateTowardCamera(FEEntity* Entity, FEEntity* CameraEntity)
{
	if (Entity == nullptr || CameraEntity == nullptr)
		return;

	FETransformComponent& CameraTransform = CameraEntity->GetComponent<FETransformComponent>();
	glm::vec3 CameraPosition = CameraTransform.GetPosition(FE_WORLD_SPACE);

	FETransformComponent& EntityTransform = Entity->GetComponent<FETransformComponent>();
	glm::vec3 EntityPosition = EntityTransform.GetPosition(FE_WORLD_SPACE);

	if (glm::all(glm::epsilonEqual(CameraPosition, EntityPosition, glm::vec3(1e-6f))))
		return;

	glm::vec3 DirectionToCamera = glm::normalize(CameraPosition - EntityPosition);

	if (glm::all(glm::isnan(DirectionToCamera)))
		return;

	FEAABB SelectedOriginalAABB = Entity->GetParentScene()->GetEntityAABB(Entity, true);
	glm::vec3 OriginalAABBNormal = glm::normalize(SelectedOriginalAABB.GetApproximateForwardDirection());
	glm::quat RotationQuaternion = glm::rotation(OriginalAABBNormal, DirectionToCamera);
	EntityTransform.SetQuaternion(RotationQuaternion, FE_WORLD_SPACE);
}

void VRManager::PlaceInFrontOfCamera(FEEntity* Entity, FEEntity* CameraEntity)
{
	if (Entity == nullptr || CameraEntity == nullptr)
		return;

	FETransformComponent& CameraTransform = CameraEntity->GetComponent<FETransformComponent>();
	glm::vec3 CameraPosition = CameraTransform.GetPosition(FE_WORLD_SPACE);
	glm::vec3 CameraForward = CameraEntity->GetComponent<FECameraComponent>().GetForward();

	FETransformComponent& EntityTransform = Entity->GetComponent<FETransformComponent>();
	glm::vec3 EntityPosition = EntityTransform.GetPosition(FE_WORLD_SPACE);
	EntityTransform.SetPosition(CameraPosition + CameraForward * 1.0f, FE_WORLD_SPACE);

	RotateTowardCamera(Entity, CameraEntity);

	//FEAABB NewSelectedAABB = Entity->GetParentScene()->GetEntityAABB(Entity);
	//float LongestAxis = NewSelectedAABB.GetLongestAxisLength();
	//// Given near and far plane and fov of the camera, calculate how far the object should be to fit the screen
	//float FOV = CameraEntity->GetComponent<FECameraComponent>().GetFOV();
	//float DistanceToFit = (LongestAxis / 2.0f) / tan(glm::radians(FOV / 2.0f));
	//EntityTransform.SetPosition(CameraPosition + CameraForward * DistanceToFit);
}

void VRManager::AnimateSphereCursor()
{
	if (SphereCursorEntities.size() == 3 && SphereCursorEntities[0] != nullptr && SphereCursorEntities[1] != nullptr && SphereCursorEntities[2] != nullptr)
	{
		double TimeEscaped = ENGINE.GetGpuTime() + ENGINE.GetCpuTime();
		double RotationAmount = 0.35 * TimeEscaped;

		FETransformComponent& SphereCursorInnerTransform = SphereCursorEntities[0]->GetComponent<FETransformComponent>();
		SphereCursorInnerTransform.RotateAroundAxis(glm::vec3(1.0f, 0.0f, 0.0f), float(RotationAmount), FE_COORDINATE_SPACE_TYPE::FE_LOCAL_SPACE);

		FETransformComponent& SphereCursorMiddleTransform = SphereCursorEntities[1]->GetComponent<FETransformComponent>();
		SphereCursorMiddleTransform.RotateAroundAxis(glm::vec3(0.0f, .0f, 1.0f), float(RotationAmount), FE_COORDINATE_SPACE_TYPE::FE_LOCAL_SPACE);

		RotateTowardCamera(SphereCursorEntities[2], OpenXR_MANAGER.GetVRHeadsetEntity());
	}

	glm::vec3 SphereCursorColor = glm::vec3(0.9f, 0.9f, 0.9f);
	if (bSphereCursorIsActive)
		SphereCursorColor = glm::vec3(0.9f, 0.0f, 0.0f);
	
	SphereCursorMaterial->SetBaseColor(SphereCursorColor);
}

void VRManager::InitializeVirtualUI()
{
	FEScene* MainScene = SCENE_RESOURCES.GetMainScene();
	if (MainScene == nullptr)
		return;
		
	VRUIEntity = SCENE_RESOURCES.GetMainScene()->CreateEntity("VR Interface");
	FETransformComponent& VRUITransform = VRUIEntity->GetComponent<FETransformComponent>();
	VRUITransform.SetPosition(glm::vec3(0.0f, 0.0f, -0.056f));
	VRUITransform.SetRotation(glm::vec3(0.0f, 90.0f, 90.0f));
	float AspectRatio = InterfaceResolution.x / InterfaceResolution.y;
	float BaseScale = 0.0475f;
	glm::vec3 Scale = glm::vec3(BaseScale / AspectRatio, BaseScale, BaseScale);
	VRUITransform.SetScale(Scale);

	VRUIEntity->AddComponent<FEVirtualUIComponent>();
	FEVirtualUIComponent& VirtualUIComponent = VRUIEntity->GetComponent<FEVirtualUIComponent>();
	VirtualUIComponent.SetCanvasResolution(InterfaceResolution);
	VirtualUIComponent.SetRenderFunction(VRMainMenuRender);
	VirtualUIComponent.SetWindowToListen(APPLICATION.GetMainWindow());
	VirtualUIComponent.SetMouseButtonPassThrough(true);
	VirtualUIComponent.SetMouseMovePassThrough(true);
	VirtualUIComponent.SetCharPassThrough(true);
	VirtualUIComponent.SetKeyPassThrough(true);
	VirtualUIComponent.SetScrollPassThrough(true);
	VirtualUIComponent.SetInputActive(false);
	VirtualUIComponent.SetKeyboardInputRequiresRayCollision(false);
	CurrentVirtualUI = VirtualUIComponent.GetVirtualUI();
	VRUIEntity->SetComponentVisible(ComponentVisibilityType::VIRTUAL_UI, false);

	// Virtual Keyboard Entity
	VirtualKeyboard.Initialize(64.0f, 64.0f, 8.0f);
	VirtualKeyboard.AddOnCharacterInputCallback(&VRManager::OnVirtualKeyboardCharacterInput);
	VirtualKeyboard.AddOnSpecialKeyCallback(&VRManager::OnVirtualKeyboardSpecialKey);

	glm::vec2 VirtualKeyboardResolution = glm::vec2(1140.0f, 408.0f);
	VRVirtualKeyboardEntity = MainScene->CreateEntity("VR Virtual Keyboard");
	FETransformComponent& VRVirtualKeyboardTransform = VRVirtualKeyboardEntity->GetComponent<FETransformComponent>();
	VRVirtualKeyboardTransform.SetPosition(glm::vec3(0.095f, 0.020f, -0.05f));
	VRVirtualKeyboardTransform.SetRotation(glm::vec3(0.0f, 90.0f, 112.2f));
	AspectRatio = VirtualKeyboardResolution.x / VirtualKeyboardResolution.y;
	Scale = glm::vec3(BaseScale / AspectRatio, BaseScale, BaseScale);
	VRVirtualKeyboardTransform.SetScale(Scale);

	VRVirtualKeyboardEntity->AddComponent<FEVirtualUIComponent>();
	FEVirtualUIComponent& VirtualKeyboardUIComponent = VRVirtualKeyboardEntity->GetComponent<FEVirtualUIComponent>();
	VirtualKeyboardUIComponent.SetCanvasResolution(VirtualKeyboardResolution);
	VirtualKeyboardUIComponent.SetRenderFunction(VRVirtualKeyboardRender);
	VirtualKeyboardUIComponent.SetWindowToListen(APPLICATION.GetMainWindow());
	VirtualKeyboardUIComponent.SetMouseButtonPassThrough(true);
	VirtualKeyboardUIComponent.SetMouseMovePassThrough(true);
	VirtualKeyboardUIComponent.SetCharPassThrough(true);
	VirtualKeyboardUIComponent.SetKeyPassThrough(true);
	VirtualKeyboardUIComponent.SetScrollPassThrough(true);
	VirtualKeyboardUIComponent.SetInputActive(true);
	CurrentVirtuaKeyboardlUI = VirtualKeyboardUIComponent.GetVirtualUI();
	VRVirtualKeyboardEntity->SetComponentVisible(ComponentVisibilityType::VIRTUAL_UI, false);

	ifd::FileDialog::Instance().AddOnFileNameTextboxFocusChangedCallback(&VRManager::OnFileDialogTextboxFocusChangedCallback);
	ifd::FileDialog::Instance().SetZoom(ifd::FileDialog::Instance().GetZoom() * 3.0f);
}

void VRManager::AttachVirtualUIToController()
{
	FEScene* MainScene = SCENE_RESOURCES.GetMainScene();
	if (MainScene == nullptr)
		return;

	if (OpenXR_MANAGER.GetLeftControllerEntity() == nullptr)
		return;

	if (VRUIEntity == nullptr)
		return;

	FETransformComponent& VRUITransform = VRUIEntity->GetComponent<FETransformComponent>();
	VRUITransform.SetPosition(glm::vec3(0.0f, 0.0f, -0.056f));
	VRUITransform.SetRotation(glm::vec3(0.0f, 90.0f, 90.0f));
	float AspectRatio = InterfaceResolution.x / InterfaceResolution.y;
	float BaseScale = 0.0475f;
	glm::vec3 Scale = glm::vec3(BaseScale / AspectRatio, BaseScale, BaseScale);
	VRUITransform.SetScale(Scale);

	OpenXR_MANAGER.GetLeftControllerEntity()->AttachChild(VRUIEntity, false);

	glm::vec2 VirtualKeyboardResolution = glm::vec2(1140.0f, 408.0f);
	FETransformComponent& VRVirtualKeyboardTransform = VRVirtualKeyboardEntity->GetComponent<FETransformComponent>();
	VRVirtualKeyboardTransform.SetPosition(glm::vec3(0.095f, 0.020f, -0.05f));
	VRVirtualKeyboardTransform.SetRotation(glm::vec3(0.0f, 90.0f, 112.2f));
	AspectRatio = VirtualKeyboardResolution.x / VirtualKeyboardResolution.y;
	Scale = glm::vec3(BaseScale / AspectRatio, BaseScale, BaseScale);
	VRVirtualKeyboardTransform.SetScale(Scale);

	OpenXR_MANAGER.GetLeftControllerEntity()->AttachChild(VRVirtualKeyboardEntity, false);
}

void VRManager::AttachInteractionRayToController()
{
	FEScene* MainScene = SCENE_RESOURCES.GetMainScene();
	if (MainScene == nullptr)
		return;

	if (OpenXR_MANAGER.GetRightControllerEntity() == nullptr)
		return;

	FEEntity* InteractionRayEntity = SCENE_RESOURCES.GetInteractionRayEntity();
	if (InteractionRayEntity == nullptr)
		return;

	FETransformComponent& InteractionRayTransform = InteractionRayEntity->GetComponent<FETransformComponent>();
	InteractionRayTransform.SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	InteractionRayTransform.SetScale(glm::vec3(SelectionRayWideness, 0.03f, SelectionRayWideness));
	InteractionRayTransform.SetRotation(glm::vec3(90.0f, 0.0f, 0.0f));
	OpenXR_MANAGER.GetRightControllerEntity()->AttachChild(InteractionRayEntity, false);
}

void VRManager::VRMainMenuRender(FEVirtualUI* CurrentVirtualUI)
{
	// Making sure that ImGui is configured for VR interaction.
	ImGui::GetIO().MouseDoubleClickTime = 0.9f; // default is 0.30f 
	ImGui::GetIO().MouseDoubleClickMaxDist = 15.0f; // default is 6.0f
	ImGui::GetIO().MouseDragThreshold = 12.0f;

	VR_MANAGER.SetImGuiStyleForVR();

	if (VR_MANAGER.bOpenFileDialogActive)
	{
		if (VR_MANAGER.bNeedToOpenLoadFileDialog)
		{
			ifd::FileDialog::Instance().Open("PointCloudOpenDialog", "Open a point cloud", "Point cloud file (*.laz;*.las){.laz,.las},.*");
			VR_MANAGER.bNeedToOpenLoadFileDialog = false;
		}

		ImGui::SetNextWindowPos(ImVec2(0, 0));
		if (ifd::FileDialog::Instance().IsDone("PointCloudOpenDialog"))
		{
			if (ifd::FileDialog::Instance().HasResult())
			{
				std::string Result = ifd::FileDialog::Instance().GetResult().u8string();
				if (FILE_SYSTEM.DoesFileExist(Result))
				{
					VR_MANAGER.bLoadingInProgress = true;
					VR_MANAGER.bOpenFileDialogActive = false;
					VR_MANAGER.HideVirtualKeyboard();
					SCENE_RESOURCES.LoadPointCloudFromFile(Result);
				}
			}
			else
			{
				VR_MANAGER.bOpenFileDialogActive = false;
				VR_MANAGER.HideVirtualKeyboard();
			}

			ifd::FileDialog::Instance().Close();
		}
	}
	else if (VR_MANAGER.bLoadingInProgress)
	{
		if (ImGui::Begin("Loading", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar))
		{
			ImGui::SetWindowFontScale(3.0f);
			ImGui::SetWindowSize(ImVec2(VR_MANAGER.InterfaceResolution.x, VR_MANAGER.InterfaceResolution.y));
			ImGui::SetWindowPos(ImVec2(0.0f, 0.0f));
			
			static int DotsCount = 0;
			float AnimationProgress = (TIME.GetTimeStamp() % 2000) / 2000.0f;
			float SineWave = (sin(AnimationProgress * 2 * glm::pi<float>()) + 1.0f) / 2.0f;
			DotsCount = static_cast<int>(SineWave * 3.99f); // 0-3 range.

			std::string LoadingText = "Loading";
			for (int i = 0; i < DotsCount; i++)
				LoadingText += ".";

			ImGui::SetCursorPos(ImVec2((VR_MANAGER.InterfaceResolution.x - ImGui::CalcTextSize(LoadingText.c_str()).x) * 0.5f, (VR_MANAGER.InterfaceResolution.y - ImGui::GetFontSize()) * 0.5f));
			ImGui::Text("%s", LoadingText.c_str());
		}

		ImGui::End();
	}
	else if (VR_MANAGER.bSavingInProgress)
	{
		if (ImGui::Begin("Saving", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar))
		{
			ImGui::SetWindowFontScale(3.0f);
			ImGui::SetWindowSize(ImVec2(VR_MANAGER.InterfaceResolution.x, VR_MANAGER.InterfaceResolution.y));
			ImGui::SetWindowPos(ImVec2(0.0f, 0.0f));

			static int DotsCount = 0;
			float AnimationProgress = (TIME.GetTimeStamp() % 2000) / 2000.0f;
			float SineWave = (sin(AnimationProgress * 2 * glm::pi<float>()) + 1.0f) / 2.0f;
			DotsCount = static_cast<int>(SineWave * 3.99f); // 0-3 range.

			std::string SavingText = "Saving";
			for (int i = 0; i < DotsCount; i++)
				SavingText += ".";

			ImGui::SetCursorPos(ImVec2((VR_MANAGER.InterfaceResolution.x - ImGui::CalcTextSize(SavingText.c_str()).x) * 0.5f, (VR_MANAGER.InterfaceResolution.y - ImGui::GetFontSize()) * 0.5f));
			ImGui::Text("%s", SavingText.c_str());
		}

		ImGui::End();
	}
	else if (VR_MANAGER.bHaveActivePointCloud && !VR_MANAGER.bSaveFileDialogActive)
	{
		if (ImGui::Begin("bHaveActivePointCloud", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar))
		{
			ImGui::SetWindowFontScale(3.0f);
			ImGui::SetWindowSize(ImVec2(VR_MANAGER.InterfaceResolution.x, VR_MANAGER.InterfaceResolution.y));
			ImGui::SetWindowPos(ImVec2(0.0f, 0.0f));

			int ButtonCount = 3;
			ImVec2 ButtonSize = ImVec2(400.0f, 70.0f);
			if (VR_MANAGER.IsInDemoMode())
			{
				ButtonCount = 4;
			}
			float CenterX = VR_MANAGER.InterfaceResolution.x * 0.5f;
			float FirstButtonCenterY = VR_MANAGER.InterfaceResolution.y / float(ButtonCount + 1);
			float HalfOfButtonWidth = ButtonSize.x * 0.5f;
			float HalfOfButtonHeight = ButtonSize.y * 0.5f;

			ImGui::SetCursorPos(ImVec2(CenterX - HalfOfButtonWidth, FirstButtonCenterY - HalfOfButtonHeight));
			if (ImGui::Button("Save Along Original", ButtonSize))
			{
				std::string FilePathToSave = "";
				std::string FilePath = SCENE_RESOURCES.GetLastLoadedPointCloudFilePath();
				if (FilePath == "")
				{
					FilePathToSave = "NewPointCloud.laz";
				}
				else
				{
					std::string FileName = FILE_SYSTEM.GetFileName(FilePath, false);
					std::string DirectoryPath = FILE_SYSTEM.GetDirectoryPath(FilePath);

					FilePathToSave = DirectoryPath + FileName + "_Edited.laz";
				}
				
				SCENE_RESOURCES.SavePointCloudToFile(FilePathToSave);
				VR_MANAGER.bSavingInProgress = true;
			}

			ImGui::SetCursorPos(ImVec2(CenterX - HalfOfButtonWidth, FirstButtonCenterY * 2.0f - HalfOfButtonHeight));
			if (ImGui::Button("Save As...", ButtonSize))
			{
				VR_MANAGER.bSaveFileDialogActive = true;
				VR_MANAGER.bNeedToOpenSaveFileDialog = true;
			}

			ImGui::SetCursorPos(ImVec2(CenterX - HalfOfButtonWidth, FirstButtonCenterY * 3.0f - HalfOfButtonHeight));
			if (ImGui::Button("Close Current", ButtonSize))
			{
				SCENE_RESOURCES.ClearPointCloud();
			}

			if (VR_MANAGER.IsInDemoMode())
			{
				ImGui::SetCursorPos(ImVec2(CenterX - HalfOfButtonWidth, FirstButtonCenterY * 4.0f - HalfOfButtonHeight));
				if (ImGui::Button("Reload", ButtonSize))
				{
					SCENE_RESOURCES.ReloadCurrentPointCloud();
				}
			}
		}

		ImGui::End();
	}
	else if (VR_MANAGER.bSaveFileDialogActive)
	{
		if (VR_MANAGER.bNeedToOpenSaveFileDialog)
		{
			ifd::FileDialog::Instance().Save("PointCloudSaveDialog", "Save a point cloud", "Point cloud file (*.laz;*.las){.laz,.las},.*");
			VR_MANAGER.bNeedToOpenSaveFileDialog = false;
		}

		ImGui::SetNextWindowPos(ImVec2(0, 0));
		if (ifd::FileDialog::Instance().IsDone("PointCloudSaveDialog"))
		{
			if (ifd::FileDialog::Instance().HasResult())
			{
				std::string Result = ifd::FileDialog::Instance().GetResult().u8string();
				SCENE_RESOURCES.SavePointCloudToFile(Result);
				VR_MANAGER.bSaveFileDialogActive = false;
				VR_MANAGER.HideVirtualKeyboard();
				VR_MANAGER.bSavingInProgress = true;
			}
			else
			{
				VR_MANAGER.bSaveFileDialogActive = false;
				VR_MANAGER.HideVirtualKeyboard();
			}

			ifd::FileDialog::Instance().Close();
		}
	}
	else
	{
		if (ImGui::Begin("Start Menu", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar))
		{
			ImGui::SetWindowFontScale(3.0f);
			ImGui::SetWindowSize(ImVec2(VR_MANAGER.InterfaceResolution.x, VR_MANAGER.InterfaceResolution.y));
			ImGui::SetWindowPos(ImVec2(0.0f, 0.0f));

			ImVec2 ButtonSize = ImVec2(400.0f, 150.0f);
			ImGui::SetCursorPos(ImVec2((VR_MANAGER.InterfaceResolution.x - ButtonSize.x) * 0.5f, (VR_MANAGER.InterfaceResolution.y - ButtonSize.y) * 0.5f));
			if (ImGui::Button("Open...", ButtonSize))
			{
				VR_MANAGER.bOpenFileDialogActive = true;
				VR_MANAGER.bNeedToOpenLoadFileDialog = true;
			}
		}

		ImGui::End();
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

	FENaiveSceneGraphNode* NodeToManipulate = SCENE_RESOURCES.GetMainScene()->SceneGraph.GetNodeByEntityID(CurrentEntityToManipulate->GetID());
	FENaiveSceneGraphNode* ControllerNode = SCENE_RESOURCES.GetMainScene()->SceneGraph.GetNodeByEntityID(OpenXR_MANAGER.GetLeftControllerEntity()->GetID());

	if (NodeToManipulate == nullptr || ControllerNode == nullptr)
		return;

	// If the controller node is not a parent of the node to manipulate, we cannot release it
	if (ControllerNode->GetChild(NodeToManipulate->GetID()) == nullptr)
		return;

	SCENE_RESOURCES.GetMainScene()->SceneGraph.MoveNode(NodeToManipulate->GetID(), SCENE_RESOURCES.GetMainScene()->SceneGraph.GetRoot()->GetID(), true);
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
			if (SphereCursorEntities[i] != nullptr)
				SphereCursorEntities[i]->SetComponentVisible(ComponentVisibilityType::GAME_MODEL, false);
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
		}

		AttachVirtualUIToController();
	}
	else
	{
		if (bShowInterface)
			SCENE_RESOURCES.GetInteractionRayEntity()->SetComponentVisible(ComponentVisibilityType::GAME_MODEL, true);
		
		AttachInteractionRayToController();
		AttachSphereCursorToController();
	}
}

void VRManager::OnControllerConnected(bool bLeftController)
{
	if (bLeftController)
		AttachVirtualUIToController();

	if (!bLeftController)
		AttachInteractionRayToController();

	if (!bLeftController)
		AttachSphereCursorToController();

	if (FEOpenXR_INPUT.IsLeftControllerConnectedAndTracked() && FEOpenXR_INPUT.IsRightControllerConnectedAndTracked())
	{
		bShowInterface = true;
		ActivateMenuMode();
	}
}

void VRManager::MenuClick()
{
	if (VR_MANAGER.bScalingWithControllersActive)
		return;

	uint64_t CurrentTimeStamp = TIME.GetTimeStamp();
	uint64_t TimeSinceLeftBButtonRelease = CurrentTimeStamp - VR_MANAGER.RightAButtonReleaseTimeStamp;
	if (TimeSinceLeftBButtonRelease > 100)
	{
		VR_MANAGER.bShowInterface = !VR_MANAGER.bShowInterface;
		VR_MANAGER.bShowInterface ? ActivateMenuMode() : CloseMainMenu();
	}
}

void VRManager::ActivateMenuMode()
{
	FEEntity* InteractionRayEntity = SCENE_RESOURCES.GetInteractionRayEntity();
	FEGameModelComponent& InteractionRayModelComponent = InteractionRayEntity->GetComponent<FEGameModelComponent>();
	FEVirtualUIComponent& VirtualUIComponent = VR_MANAGER.VRUIEntity->GetComponent<FEVirtualUIComponent>();

	VR_MANAGER.bShowInterface = true;
	VR_MANAGER.VRUIEntity->SetComponentVisible(ComponentVisibilityType::VIRTUAL_UI, VR_MANAGER.bShowInterface);
	VirtualUIComponent.SetInputActive(VR_MANAGER.bShowInterface);
	InteractionRayEntity->SetComponentVisible(ComponentVisibilityType::GAME_MODEL, VR_MANAGER.bShowInterface);

	for (size_t i = 0; i < SphereCursorEntities.size(); i++)
		SphereCursorEntities[i]->SetComponentVisible(ComponentVisibilityType::GAME_MODEL, false);
}

bool VRManager::IsMainMenuVisible() const
{ 
	return bShowInterface;
}

void VRManager::CloseMainMenu()
{
	FEEntity* InteractionRayEntity = SCENE_RESOURCES.GetInteractionRayEntity();
	FEGameModelComponent& InteractionRayModelComponent = InteractionRayEntity->GetComponent<FEGameModelComponent>();
	FEVirtualUIComponent& VirtualUIComponent = VR_MANAGER.VRUIEntity->GetComponent<FEVirtualUIComponent>();

	VR_MANAGER.bShowInterface = false;
	VR_MANAGER.VRUIEntity->SetComponentVisible(ComponentVisibilityType::VIRTUAL_UI, VR_MANAGER.bShowInterface);
	VirtualUIComponent.SetInputActive(VR_MANAGER.bShowInterface);
	InteractionRayEntity->SetComponentVisible(ComponentVisibilityType::GAME_MODEL, VR_MANAGER.bShowInterface);
}

bool VRManager::IsLoadingInProgress() const
{ 
	return bLoadingInProgress;
}

void VRManager::SetLoadingInProgress(bool NewValue)
{ 
	bLoadingInProgress = NewValue;
}

void VRManager::SetHaveActivePointCloud(bool NewValue, FEEntity* PointCloudEntity)
{
	VR_MANAGER.bHaveActivePointCloud = NewValue;
	SetCurrentEntityToManipulate(PointCloudEntity);
}

bool VRManager::HasActivePointCloud() const
{
	return VR_MANAGER.bHaveActivePointCloud;
}

FEEntity* VRManager::GetVRInterfaceEntity() const
{
	return VRUIEntity;
}

void VRManager::OnControllerConnectionStatusChangeCallBack(bool bLeft, FE_VR_CONTROLLER_STATE_CHANGE Change)
{
	if (Change == FE_VR_CONTROLLER_STATE_CHANGE::CONNECTED)
	{
		VR_MANAGER.OnControllerConnected(bLeft);
	}
	else if (Change == FE_VR_CONTROLLER_STATE_CHANGE::DISCONNECTED)
	{
		VR_MANAGER.OnControllerDisconnected(bLeft);
	}
	else if (Change == FE_VR_CONTROLLER_STATE_CHANGE::RECONNECTED)
	{
		VR_MANAGER.OnControllerReConnected(bLeft);
	}
}

void VRManager::VRVirtualKeyboardRender(FEVirtualUI* CurrentVirtualUI)
{
	if (!VR_MANAGER.VirtualKeyboard.ShouldBeRendered())
		VR_MANAGER.HideVirtualKeyboard();

	VR_MANAGER.SetImGuiStyleForVR();
	VR_MANAGER.VirtualKeyboard.DrawVirtualKeyboard();
}

FEEntity* VRManager::GetVirtualKeyboardEntity() const
{
	return VRVirtualKeyboardEntity;
}

void VRManager::OnVirtualKeyboardCharacterInput(char NewCharacter)
{
	VR_MANAGER.CurrentVirtualUI->InvokeCharInput(NewCharacter);
}

void VRManager::OnVirtualKeyboardSpecialKey(ImGuiVirtualKeyboard::VirtualKeyboardSpecialKey Key)
{
	switch (Key)
	{
		case ImGuiVirtualKeyboard::VirtualKeyboardSpecialKey::BACKAPACE:
		{
			VR_MANAGER.CurrentVirtualUI->InvokeKeyInput(GLFW_KEY_BACKSPACE, 0, GLFW_PRESS, 0);
			VR_MANAGER.CurrentVirtualUI->InvokeKeyInput(GLFW_KEY_BACKSPACE, 0, GLFW_RELEASE, 0);
			break;
		}
		case ImGuiVirtualKeyboard::VirtualKeyboardSpecialKey::ENTER:
		{
			VR_MANAGER.CurrentVirtualUI->InvokeKeyInput(GLFW_KEY_ENTER, 0, GLFW_PRESS, 0);
			VR_MANAGER.CurrentVirtualUI->InvokeKeyInput(GLFW_KEY_ENTER, 0, GLFW_RELEASE, 0);
			break;
		}
	}
}

void VRManager::OnFileDialogTextboxFocusChangedCallback(bool bIsFocused)
{
	VR_MANAGER.VRVirtualKeyboardEntity->SetComponentVisible(ComponentVisibilityType::VIRTUAL_UI, bIsFocused);
	VR_MANAGER.bVirtualKeyboardIsActive = bIsFocused;
	VR_MANAGER.VirtualKeyboard.SetShouldBeRendered(bIsFocused);
}

void VRManager::ShowVirtualKeyboard()
{
	VR_MANAGER.VRVirtualKeyboardEntity->SetComponentVisible(ComponentVisibilityType::VIRTUAL_UI, true);
	VR_MANAGER.bVirtualKeyboardIsActive = true;
	VirtualKeyboard.SetShouldBeRendered(true);
}

void VRManager::HideVirtualKeyboard()
{
	VR_MANAGER.VRVirtualKeyboardEntity->SetComponentVisible(ComponentVisibilityType::VIRTUAL_UI, false);
	VR_MANAGER.bVirtualKeyboardIsActive = false;
}

bool VRManager::IsSphereCursorActive() const
{
	return bSphereCursorIsActive;
}

bool VRManager::IsSphereCursorVisible() const
{
	int VisibleCount = 0;
	for (size_t i = 0; i < SphereCursorEntities.size(); i++)
	{
		if (SphereCursorEntities[i] != nullptr)
		{
			if (SphereCursorEntities[i]->IsComponentVisible(ComponentVisibilityType::GAME_MODEL))
				VisibleCount++;
		}
	}

	return VisibleCount == 3;
}

void VRManager::ShowSphereCursor()
{
	for (size_t i = 0; i < SphereCursorEntities.size(); i++)
	{
		if (SphereCursorEntities[i] != nullptr)
			SphereCursorEntities[i]->SetComponentVisible(ComponentVisibilityType::GAME_MODEL, true);
	}
}

void VRManager::HideSphereCursor()
{
	for (size_t i = 0; i < SphereCursorEntities.size(); i++)
	{
		if (SphereCursorEntities[i] != nullptr)
			SphereCursorEntities[i]->SetComponentVisible(ComponentVisibilityType::GAME_MODEL, false);
	}
}

void VRManager::AttachSphereCursorToController()
{
	for (size_t i = 0; i < SphereCursorEntities.size(); i++)
	{
		if (SphereCursorEntities[i] != nullptr)
			OpenXR_MANAGER.GetRightControllerEntity()->AttachChild(SphereCursorEntities[i], false);
	}
}

bool VRManager::IsInDemoMode() const
{
	return bDemoMode;
}

void VRManager::SetDemoMode(bool bNewValue)
{
	bDemoMode = bNewValue;
}