#include "SubSystems/VRManager/VRManager.h"
using namespace FocalEngine;

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

	APPLICATION.GetMainWindow()->AddOnMouseButtonCallback(MouseButtonCallback);
	SCENE_RESOURCES.Initialize();

	bool bIsVRActive = ENGINE.EnableVR(FERenderingPipeline::Forward_Simplified);
	VR_MANAGER.Initialize();

	while (ENGINE.IsNotTerminated())
	{
		ENGINE.BeginFrame();
		ENGINE.Render();

		VR_MANAGER.Update();

		FEEntity* SelectionRayEntity = SCENE_RESOURCES.GetInteractionRayEntity();
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