#include "SubSystems/VRManager/VRManager.h"
using namespace FocalEngine;

#include "VersionInfo/VR_PointCloud_Editor_Version.h"
#include "VersionInfo/FEVersionInfo.h"
FE_DEFINE_VERSION_INFO(VR_PointCloud_Editor_)
std::string GetVREditorVersion()
{
	return GetVR_PointCloud_Editor_VersionInfo().GetVersion();
}

int GetVREditorBuildNumber()
{
	return GetVR_PointCloud_Editor_VersionInfo().BuildNumber;
}

std::string GetVREditorBuildTimestamp()
{
	return GetVR_PointCloud_Editor_VersionInfo().BuildTimestamp;
}

std::string GetVREditorBuildInfo()
{
	return GetVR_PointCloud_Editor_VersionInfo().GetBuildInfo();
}

std::string GetVREditorFullVersion()
{
	return "VR PointCloud Editor " + GetVREditorVersion() + " " + GetVREditorBuildInfo();
}

bool bShouldOpenAboutWindow = false;
void ShowAboutDialog()
{
	bShouldOpenAboutWindow = true;
}

void RenderAboutWindow()
{
	if (bShouldOpenAboutWindow)
	{
		ImGui::OpenPopup("About");
		bShouldOpenAboutWindow = false;
	}

	float PopupW = 450.0f;
	float PopupH = 135.0f;
	ImGui::SetNextWindowSize(ImVec2(PopupW, PopupH));
	if (ImGui::BeginPopupModal("About", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove))
	{
		int WindowW = 0;
		int WindowH = 0;
		APPLICATION.GetMainWindow()->GetSize(&WindowW, &WindowH);

		ImGui::SetWindowPos(ImVec2(WindowW / 2.0f - ImGui::GetWindowWidth() / 2.0f, WindowH / 2.0f - ImGui::GetWindowHeight() / 2.0f));

		std::string Text = GetVREditorFullVersion();
		ImVec2 TextSize = ImGui::CalcTextSize(Text.c_str());
		ImGui::SetCursorPosX(PopupW / 2.0f - TextSize.x / 2.0f);
		ImGui::Text(Text.c_str());

		ImGui::Separator();

		Text = "To submit a bug report or provide feedback, ";
		TextSize = ImGui::CalcTextSize(Text.c_str());
		ImGui::SetCursorPosX(PopupW / 2.0f - TextSize.x / 2.0f);
		ImGui::Text(Text.c_str());

		Text = "please email me at kberegovyi@ccom.unh.edu.";
		TextSize = ImGui::CalcTextSize(Text.c_str());
		ImGui::SetCursorPosX(PopupW / 2.0f - TextSize.x / 2.0f);
		ImGui::Text(Text.c_str());

		ImGui::Separator();

		Text = "UNH CCOM";
		TextSize = ImGui::CalcTextSize(Text.c_str());
		ImGui::SetCursorPosX(PopupW / 2.0f - TextSize.x / 2.0f);
		ImGui::Text(Text.c_str());

		ImGui::SetCursorPosX(PopupW / 2.0f - 210.0f / 2.0f);
		ImGui::SetNextItemWidth(210);
		if (ImGui::Button("Close", ImVec2(210.0f, 20.0f)))
			ImGui::CloseCurrentPopup();

		ImGui::EndPopup();
	}
}

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

void MouseButtonCallback(int button, int action, int mods)
{
	FEEntity* MainCamera = SCENE_RESOURCES.GetMainCamera();

	if (ImGui::GetIO().WantCaptureMouse)
	{
		MainCamera->GetComponent<FECameraComponent>().SetActive(false);
		return;
	}

	if (button == GLFW_MOUSE_BUTTON_2 && action == GLFW_PRESS)
	{
		MainCamera->GetComponent<FECameraComponent>().SetActive(true);
	}
	else if (button == GLFW_MOUSE_BUTTON_2 && action == GLFW_RELEASE)
	{
		MainCamera->GetComponent<FECameraComponent>().SetActive(false);
	}
}

void KeyButtonCallback(const int Key, const int Scancode, const int Action, const int Mods)
{
	if (Key == GLFW_KEY_ESCAPE && Action == GLFW_RELEASE)
		ENGINE.Terminate();
	
	if (Key == GLFW_KEY_R && Action == GLFW_PRESS && VR_MANAGER.IsInDemoMode())
		SCENE_RESOURCES.ReloadCurrentPointCloud();
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	std::vector<CommandLineAction> ParsedCommandActions;
	ParsedCommandActions = APPLICATION.ParseCommandLine(lpCmdLine);

	ENGINE.InitWindow(1270, 720, "VR-PointCloud-Editor");
	ENGINE.SetVsyncEnabled(false);
	THREAD_POOL.SetConcurrentThreadCount(10);

	const int FrameCountTillMeasure = 20;
	double CPUFrameDurations[FrameCountTillMeasure] = { 0.0f };
	double GPUFrameDurations[FrameCountTillMeasure] = { 0.0f };
	int FrameCounter = 0;

	double AverageCpuFrameDuration = 0.0;
	double AverageGpuFrameDuration = 0.0;

	APPLICATION.GetMainWindow()->AddOnMouseButtonCallback(MouseButtonCallback);
	APPLICATION.GetMainWindow()->AddOnKeyCallback(KeyButtonCallback);
	SCENE_RESOURCES.Initialize();

	bool bIsVRActive = ENGINE.EnableVR(FERenderingPipeline::Forward_Simplified);
	VR_MANAGER.Initialize();

	if (!ParsedCommandActions.empty())
	{
		for (size_t i = 0; i < ParsedCommandActions.size(); i++)
		{
			CommandLineAction& CurrentCommand = ParsedCommandActions[i];
			std::transform(CurrentCommand.Action.begin(), CurrentCommand.Action.end(), CurrentCommand.Action.begin(), [](unsigned char Character) {
				return std::tolower(Character);
			});

			if (CurrentCommand.Action == "demo_mode")
			{
				VR_MANAGER.SetDemoMode(true);
			}

			if (CurrentCommand.Action == "file_load")
			{
				auto SettingsIterator = CurrentCommand.Settings.find("filepath");
				if (SettingsIterator != CurrentCommand.Settings.end())
				{
					std::string FilePath = SettingsIterator->second;
					SCENE_RESOURCES.LoadPointCloudFromFile(FilePath);
				}
			}
		}
	}

	while (ENGINE.IsNotTerminated())
	{
		ENGINE.BeginFrame();
		ENGINE.Render();

		VR_MANAGER.Update();

		/*FEEntity* SelectionRayEntity = SCENE_RESOURCES.GetInteractionRayEntity();
		if (SelectionRayEntity != nullptr)
		{
			FETransformComponent& SelectionRayTransform = SelectionRayEntity->GetComponent<FETransformComponent>();
			ShowTransformConfiguration(SelectionRayEntity, &SelectionRayTransform);
		}

		FEEntity* VRInterfaceEntity = VR_MANAGER.GetVRInterfaceEntity();
		if (VRInterfaceEntity != nullptr)
		{
			FETransformComponent& VRInterfaceTransform = VRInterfaceEntity->GetComponent<FETransformComponent>();
			ShowTransformConfiguration(VRInterfaceEntity, &VRInterfaceTransform, 0.01f);
		}

		FEEntity* VRKeyboardEntity = VR_MANAGER.GetVirtualKeyboardEntity();
		if (VRKeyboardEntity != nullptr)
		{
			FETransformComponent& VRKeyboardTransform = VRKeyboardEntity->GetComponent<FETransformComponent>();
			ShowTransformConfiguration(VRKeyboardEntity, &VRKeyboardTransform, 0.01f);
		}

		FEEntity* PointCloudEntity = SCENE_RESOURCES.GetPointCloudEntity();
		if (PointCloudEntity != nullptr)
		{
			FETransformComponent& PointCloudTransform = PointCloudEntity->GetComponent<FETransformComponent>();
			ShowTransformConfiguration(PointCloudEntity, &PointCloudTransform, 0.01f);
		}*/

		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("Info"))
			{
				if (ImGui::MenuItem("About..."))
					ShowAboutDialog();

				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}

		RenderAboutWindow();

		static int MainWindowRenderingMode = 0;
		if (ImGui::RadioButton("Mirror VR View", MainWindowRenderingMode == 0))
		{
			MainWindowRenderingMode = 0;
			FEEntity* Camera = SCENE_RESOURCES.GetMainCamera();
			FECameraComponent& CameraComponent = Camera->GetComponent<FECameraComponent>();
			CameraComponent.SetRenderingEnabled(false);
		}

		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::TextUnformatted("Display what the VR headset sees in the main window");
			ImGui::EndTooltip();
		}
		
		if (ImGui::RadioButton("Free Camera View", MainWindowRenderingMode == 1))
		{
			MainWindowRenderingMode = 1;
			FEEntity* Camera = SCENE_RESOURCES.GetMainCamera();
			FECameraComponent& CameraComponent = Camera->GetComponent<FECameraComponent>();
			CameraComponent.SetRenderingEnabled(true);
		}
		
		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::TextUnformatted("Show independent camera view that can be manipulated\n"
								   "to view scene from alternative perspective.\n"
								   "This will cause lower performance.");
			ImGui::EndTooltip();
		}

		if (ImGui::RadioButton("Disabled", MainWindowRenderingMode == 2))
		{
			MainWindowRenderingMode = 2;
			FEEntity* Camera = SCENE_RESOURCES.GetMainCamera();
			FECameraComponent& CameraComponent = Camera->GetComponent<FECameraComponent>();
			CameraComponent.SetRenderingEnabled(false);
		}

		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::TextUnformatted("Disable main window rendering to save performance");
			ImGui::EndTooltip();
		}

		if (VR_MANAGER.IsInDemoMode())
		{
			bool bReloadButtonEnabled = !SCENE_RESOURCES.GetLastLoadedPointCloudFilePath().empty();
			if (!bReloadButtonEnabled)
				ImGui::BeginDisabled();

			if (ImGui::Button("Reload current point cloud"))
				SCENE_RESOURCES.ReloadCurrentPointCloud();

			if (!bReloadButtonEnabled)
				ImGui::EndDisabled();
		}

		FEEntity* VRHeadsetEntity = OpenXR_MANAGER.GetVRHeadsetEntity();
		if (VRHeadsetEntity != nullptr && MainWindowRenderingMode == 0)
		{
			FETexture* FinalSceneTexture = RENDERER.GetCameraResult(VRHeadsetEntity);
			if (FinalSceneTexture != nullptr)
			{
				glViewport(0, 0, APPLICATION.GetMainWindow()->GetWidth(), APPLICATION.GetMainWindow()->GetHeight());
				FE_GL_ERROR(glBindFramebuffer(GL_FRAMEBUFFER, 0));

				FEMesh* ScreenQuad = RESOURCE_MANAGER.GetMesh("1Y251E6E6T78013635793156"/*"plane"*/);
				FEShader* ScreenQuadShader = RESOURCE_MANAGER.GetShader("7933272551311F3A1A5B2363");

				FinalSceneTexture->Bind(0);
				ScreenQuadShader->Start();
				ScreenQuadShader->LoadUniformsDataToGPU();

				FE_GL_ERROR(glBindVertexArray(ScreenQuad->GetVaoID()));
				FE_GL_ERROR(glEnableVertexAttribArray(0));
				FE_GL_ERROR(glDrawElements(GL_TRIANGLES, ScreenQuad->GetVertexCount(), GL_UNSIGNED_INT, nullptr));
				FE_GL_ERROR(glDisableVertexAttribArray(0));
				FE_GL_ERROR(glBindVertexArray(0));

				FinalSceneTexture->UnBind();
				ScreenQuadShader->Stop();
			}
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