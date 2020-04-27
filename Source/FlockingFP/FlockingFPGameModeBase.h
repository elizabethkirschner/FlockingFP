// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FlockingFPGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class FLOCKINGFP_API AFlockingFPGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	AFlockingFPGameModeBase();

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent * AgentMesh;

	class UFlockingManager *Manager;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
  
public:  
  void OnAgentHit();

  UPROPERTY(EditAnywhere)
  int32 PointsToWin;

};
