// Fill out your copyright notice in the Description page of Project Settings.

#include "FlockingFPGameModeBase.h"
#include "FlockingManager.h"
#include "FlockingFPHUD.h"
#include "FlockingFPCharacter.h"
#include "FlockingGameState.h"

AFlockingFPGameModeBase::AFlockingFPGameModeBase() {
    AgentMesh = CreateDefaultSubobject<UStaticMeshComponent>("AgentMesh");
    PrimaryActorTick.bCanEverTick = true;

  // set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFlockingFPHUD::StaticClass();

  PointsToWin = 10;
}  

void AFlockingFPGameModeBase::BeginPlay() {
    Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("GAMEMODE BEGINPLAY()"));
    Manager = NewObject<UFlockingManager>();
    Manager->Init( GetWorld(), AgentMesh );
}

void AFlockingFPGameModeBase::Tick( float DeltaTime ) {
    Super::Tick( DeltaTime );
    Manager->Flock();
} 

void AFlockingFPGameModeBase::OnAgentHit() {
  if (AFlockingGameState* GS = Cast<AFlockingGameState>(GameState)) {
    GS->Points++;

    if (GS->Points >= PointsToWin) {
      UE_LOG(LogTemp,Warning,TEXT("YOU WON THE GAME"));
    }
    else {
      UE_LOG(LogTemp,Warning,TEXT("YOU SCORED"));      
    }
  }
}
