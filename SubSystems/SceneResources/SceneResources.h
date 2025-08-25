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

	bool TryToAttachEntities(FEEntity* WhatToAttach, FEEntity* WhereToAttach, bool bPreserveWorldTransform);

	void LoadPointCloudFromFile(const std::string& FilePath);
	void DeletePoints(glm::vec3 Center, float Radius);

	void SavePointCloudToFile(const std::string& FilePath);
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
};

#define SCENE_RESOURCES SceneResources::GetInstance()