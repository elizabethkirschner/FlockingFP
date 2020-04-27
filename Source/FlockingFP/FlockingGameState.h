// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "FlockingGameState.generated.h"

/**
 * 
 */
UCLASS()
class FLOCKINGFP_API AFlockingGameState : public AGameStateBase
{
	GENERATED_BODY()

 public: 

  AFlockingGameState();
  int32 Points;
	
};
