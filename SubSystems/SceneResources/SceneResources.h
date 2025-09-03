#pragma once
#include "../FocalEngine/FEngine.h"
using namespace FocalEngine;
#include "../../../ThirdParty/ImFileDialog/ImFileDialog.h"

class SceneResources
{
public:
	SINGLETON_PUBLIC_PART(SceneResources)

	void Initialize();

	FEScene* GetMainScene();
	FEEntity* GetMainCamera();
	FEEntity* GetSun() { return Sun; }
	FEEntity* GetGreenCylinderEntity() { return GreenCylinderEntity; }
	FEEntity* GetRedCylinderEntity() { return RedCylinderEntity; }
	FEEntity* GetBlueCylinderEntity() { return BlueCylinderEntity; }
	FEEntity* GetWhiteCylinderEntity() { return WhiteCylinderEntity; }
	FEEntity* GetInteractionRayEntity() { return InteractionRayEntity; }
	FEEntity* GetPointCloudEntity() { return PointCloudEntity; }

	void LoadPointCloudFromFile(const std::string& FilePath);
	void SavePointCloudToFile(const std::string& FilePath);
	void ClearPointCloud();

	void DeletePoints(glm::vec3 Center, float Radius);

	glm::dvec3 GetPositionShift() const { return PositionShift; }
private:
	SINGLETON_PRIVATE_PART(SceneResources)

	FEScene* MainScene = nullptr;
	FEEntity* MainCamera = nullptr;
	FEEntity* Sun = nullptr;

	FEEntity* GreenCylinderEntity = nullptr;
	FEEntity* RedCylinderEntity = nullptr;
	FEEntity* BlueCylinderEntity = nullptr;
	FEEntity* WhiteCylinderEntity = nullptr;

	FEShader* DeletePointsComputeShader = nullptr;

	FEEntity* InteractionRayEntity = nullptr;

	FEEntity* PointCloudEntity = nullptr;

	void SetupScene();
	void InitResourses();

	static void CallBackWhenPointCloudIsLoaded(FEPointCloud* LoadedPointCloud);

	glm::dvec3 OriginalMin = glm::dvec3(DBL_MAX);
	glm::dvec3 OriginalMax = glm::dvec3(-DBL_MAX);
	glm::dvec3 ReCenteredMin = glm::dvec3(DBL_MAX);
	glm::dvec3 ReCenteredMax = glm::dvec3(-DBL_MAX);
	glm::dvec3 PositionShift = glm::dvec3(0.0);
	double MaxExtent = 0.0;
};

#define SCENE_RESOURCES SceneResources::GetInstance()