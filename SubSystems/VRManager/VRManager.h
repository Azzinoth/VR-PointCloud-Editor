#pragma once
#include "../ImGuiVirtualKeyboard.h"
using namespace FocalEngine;

class VRManager
{
	SINGLETON_PRIVATE_PART(VRManager)

	friend class SceneResources;

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

	glm::vec2 InterfaceResolution = glm::vec2(600.0f, 400.0f);

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

	static void OnLeftViveMenuClick();
	void MenuClick();

	bool bShowInterface = false;
	FEEntity* VRUIEntity = nullptr;
	bool bControllerSelectionMode = false;

	float LineWidth = 0.1f;

	std::vector<FEEntity*> EntitiesToManipulate;
	int EntitiesToManipulateIndex = 0;
	FEEntity* CurrentEntityToManipulate = nullptr;
	void ReleaseEntity();

	void ActivateMenuMode();
	
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

	bool bNeedToOpenLoadFileDialog = false;
	bool bOpenFileDialogActive = false;

	bool bNeedToOpenSaveFileDialog = false;
	bool bSaveFileDialogActive = false;

	bool bLoadingInProgress = false;
	bool bHaveActivePointCloud = false;

	void SetLoadingInProgress(bool NewValue);
	void SetHaveActivePointCloud(bool NewValue, FEEntity* PointCloudEntity);

	GLuint DeletionFlagBuffer;
	float SphereCursorActionScale = 1.0f / 2.55f;
	float SelectionRayWideness = 0.00065f;

	static void OnControllerConnectionStatusChangeCallBack(bool bLeft, FE_VR_CONTROLLER_STATE_CHANGE Change);

	static void OnFileDialogTextboxFocusChangedCallback(bool bIsFocused);

	ImGuiVirtualKeyboard VirtualKeyboard;
	bool bVirtualKeyboardIsActive = false;
	FEEntity* VRVirtualKeyboardEntity = nullptr;
	FEVirtualUI* CurrentVirtuaKeyboardlUI = nullptr;
	static void VRVirtualKeyboardRender(FEVirtualUI* CurrentVirtualUI);
	static void OnVirtualKeyboardCharacterInput(char NewCharacter);
	static void OnVirtualKeyboardSpecialKey(ImGuiVirtualKeyboard::VirtualKeyboardSpecialKey Key);

	void ShowVirtualKeyboard();
	void HideVirtualKeyboard();
public:
	SINGLETON_PUBLIC_PART(VRManager)

	void Initialize();
	void Update();
	void InitializeVirtualUI();

	FEEntity* GetVRInterfaceEntity() const;
	FEVirtualUI* CurrentVirtualUI = nullptr;
	static void VRMainMenuRender(FEVirtualUI* CurrentVirtualUI);
	FEEntity* GetVirtualKeyboardEntity() const;

	std::pair<glm::vec3, glm::vec3> GetControllerInteractionRay(bool bLeftController = true) const;

	bool IsControllerSelectionModeActive() const;
	void SetControllerSelectionModeActive(bool bActive);

	FEEntity* GetCurrentEntityToManipulate() const;
	void SetCurrentEntityToManipulate(FEEntity* NewEntity);

	bool IsLoadingInProgress() const;
	bool HasActivePointCloud() const;

	bool IsMainMenuVisible() const;
	void CloseMainMenu();

	bool IsSphereCursorActive() const;
	bool IsSphereCursorVisible() const;
	void ShowSphereCursor();
	void HideSphereCursor();

	void RotateTowardCamera(FEEntity* Entity, FEEntity* CameraEntity);
	void PlaceInFrontOfCamera(FEEntity* Entity, FEEntity* CameraEntity);
};

#define VR_MANAGER VRManager::GetInstance()