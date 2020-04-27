// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FlockingManager.generated.h"

UCLASS()
class FLOCKINGFP_API UFlockingManager : public UObject
{

public:
	GENERATED_BODY()

	void Init( UWorld *world, UStaticMeshComponent *mesh );
	void Flock();
  FVector V1(class AAgent * b);
  FVector V2(class AAgent * b);
  FVector V3(class AAgent * b);
  FVector BoundPosition(class AAgent* b);

private:
	UWorld *World;	
	bool initialized;
	TArray<class AAgent *> Agents;
};