#pragma once
#include "../SceneResources/SceneResources.h"
using namespace FocalEngine;

class VRManager
{
public:
	SINGLETON_PUBLIC_PART(VRManager)

	void Initialize();

	void Update();

	void InitializeVirtualUI();
private:
	SINGLETON_PRIVATE_PART(VRManager)

	float TranslateScale = 1.0f;

	// Scaling part
	bool bLeftControllerScalingJustGotActive = false;
	bool bRightControllerScalingJustGotActive = false;

	bool bLeftControllerScalingJustGotInActive = false;
	bool bRightControllerScalingJustGotInActive = false;
	bool bScalingWithControllersActive = false;
	uint64_t LastTimeControllerScalingWasActive = 0;
	void SetScalingWithControllers(bool bNewValue);

	float InitialControllerDistanceForScale = 0.0f;
	glm::vec3 InitialEntityScale;
	glm::vec3 OriginalEntityPosition;

	glm::vec3 OriginalPivotPosition;
	glm::vec3 CurrentPivotPosition;
	glm::vec3 PivotDirection;

	bool bLeftAButtonTouched = false;
	bool bRightAButtonTouched = false;

	float ControllerDistance();
	void CheckShouldScaleWorldActivate();
	void UpdateWhiteCylinder();
	void ScaleWorldUpdate();

	static void OnRightTriggerPress();
	static void OnRightTriggerRelease();

	static void OnLeftTriggerPress();
	static void OnLeftTriggerRelease();
	
	static void OnLeftAButtonPress();
	static void OnRightAButtonPress();

	static void OnLeftAButtonRelease();
	static void OnRightAButtonRelease();

	static void OnLeftAButtonTouchActivate();
	static void OnLeftAButtonTouchDeactivate();

	static void OnRightAButtonTouchActivate();
	static void OnRightAButtonTouchDeactivate();

	//static void OnLeftBButtonPress();
	//static void OnRightBButtonPress();

	static void OnLeftBButtonRelease();
	static void OnRightBButtonRelease();

	bool bShowInterface = false;
	bool bControllerSelectionMode = false;

	float LineWidth = 0.1f;

	std::vector<FEEntity*> EntitiesToManipulate;
	int EntitiesToManipulateIndex = 0;
	FEEntity* CurrentEntityToManipulate = nullptr;
	void ReleaseEntity();

	bool bLeftControllerWasActiveLastFrame = false;
	bool bRightControllerWasActiveLastFrame = false;

	void AttachVirtualUIToController();
	void AttachInteractionRayToController();

	bool bNextFrameUpdateAABBs = false;
	size_t FrameOfRecordingAABBs = 0;
	float VRRigScale = 1.0f; // was 50.0f

	bool bLeftControllerTriggerIsPressed = false;
	bool bRightControllerTriggerIsPressed = false;

	std::vector<FEMesh*> SphereCursorMeshes;
	FEMaterial* SphereCursorMaterial = nullptr;
	std::vector<FEGameModel*> SphereCursorGameModels;
	std::vector<FEEntity*> SphereCursorEntities;
	glm::vec3 SphereCursorPosition = glm::vec3(-0.010f, -0.020f, -0.150f);
	float SphereCursorScale = 0.06f;
	bool bSphereCursorIsActive = false;

	void InitializeSphereCursor();
	void AnimateSphereCursor();

	void OnControllerConnected(bool bLeftController = true);
	void OnControllerDisconnected(bool bLeftController = true);
	void OnControllerReConnected(bool bLeftController = true);

	//uint64_t LastTimeControllerScalingWasActive = 0;
	uint64_t RightAButtonReleaseTimeStamp = 0;
	bool bRightAButtonIsPressed = false;
public:
	FEEntity* VRUIEntity = nullptr;
	FEVirtualUI* CurrentVirtualUI = nullptr;
	bool bFontLoaded = false;
	bool bFontIsReady = false;
	bool UIAdded = false;

	static void VRInterfaceRender(FEVirtualUI* CurrentVirtualUI);

	std::pair<glm::vec3, glm::vec3> GetControllerInteractionRay(bool bLeftController = true) const;

	bool IsControllerSelectionModeActive() const;
	void SetControllerSelectionModeActive(bool bActive);

	FEEntity* GetCurrentEntityToManipulate() const;
	void SetCurrentEntityToManipulate(FEEntity* NewEntity);
};

#define VR_MANAGER VRManager::GetInstance()