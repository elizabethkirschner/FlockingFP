// Fill out your copyright notice in the Description page of Project Settings.

#include "FlockingManager.h"
#include "Agent.h"
#include "Kismet/KismetMathLibrary.h"

#define AGENT_COUNT 10

void UFlockingManager::Init( UWorld *world, UStaticMeshComponent *mesh ) {
  UE_LOG(LogTemp, Warning, TEXT("Manager initialized"));
    
  World = world;
  float incr = (PI * 2.f) / AGENT_COUNT;
  for( int i = 0; i < AGENT_COUNT; i++ ) {
    if( World != nullptr ) {
      FRotator rotation = FRotator();

      FVector location = FVector();
      location.X = -100.f;
      location.Y = FMath::Sin( incr * i ) * 150.f;
      location.Z = FMath::Cos( incr * i ) * 150.f + 500;
            
      AAgent * agent = World->SpawnActor<AAgent>( location, rotation );
      agent->Init( mesh, i );
      Agents.Add( agent );
    }
  }
  initialized = true;
}

void UFlockingManager::Flock() {
  //UE_LOG(LogTemp,Warning,TEXT("OH THEY FLOCKING"));
  FVector v1, v2,v3;

  for (int i = 0; i < Agents.Num(); i++) {
    
    v1 = FVector(0,0,0);
    v2 = FVector(0,0,0);
    v3 = FVector(0,0,0);

    AAgent * currentAgent = Agents[i];
    v1 = V1(currentAgent);
    v2 = V2(currentAgent);
    v3 = V3(currentAgent);
    FVector agentVelocity = v1 + v2 +v3;

    agentVelocity = agentVelocity + BoundPosition(currentAgent);      

    // velocity limit
    int vlim = 8;
    if (agentVelocity.Size() > vlim) {
      agentVelocity = (agentVelocity / agentVelocity.Size()) * vlim;
    }     

    currentAgent->Velocity = currentAgent->Velocity + agentVelocity;
  }
}

FVector UFlockingManager::V1(AAgent * b) {
  FVector v1 = FVector(0,0,0);

  for (int i = 0; i < Agents.Num(); i++) {
    if (!(Agents[i] == b)) {
      FVector otherAgentLoc = Agents[i]->GetActorLocation();
      v1 = v1 + otherAgentLoc;
    }
  }
  v1 = v1 / (Agents.Num() - 1);
  v1 = (v1 - b->GetActorLocation()) / 400;
  
  return v1;
}

FVector UFlockingManager::V2(AAgent * b) {
  FVector v2 = FVector(0,0,0);

  for (int i = 0; i < Agents.Num(); i++) {
    if (!(Agents[i] == b)) {
      FVector dif = (Agents[i]->GetActorLocation() - b->GetActorLocation());

      if (dif.Size() < 100) {
        v2 = v2 - dif;
      }
    }
  }

  return v2;
}

FVector UFlockingManager::V3(AAgent * b) {
  FVector v3 = FVector(0,0,0);

  for (int i = 0; i < Agents.Num(); i++) {
    if (!(Agents[i] == b)) {
      v3 = v3 + Agents[i]->Velocity;
    }
  }

  v3 = v3 / (Agents.Num() - 1);
  v3 = ( v3 - b->Velocity) / 32;

  return v3;
}

FVector UFlockingManager::BoundPosition(class AAgent * b) {
	int Xmin = -300, Xmax = 300, Ymin = -300, Ymax = 300, Zmin = 0, Zmax = 1000;
  FVector V = FVector(0,0,0);

  FVector BLoc = b->GetActorLocation();

  if(BLoc.X < Xmin) {
    V.X = 10;
  }
  else if (BLoc.X > Xmax) {
    V.X = -10;
  }
  else if (BLoc.Y < Ymin) {
    V.Y = 10;
  }
  else if (BLoc.Y > Ymax) {
    V.Y = -10;
  }
  else if (BLoc.Z < Zmin) {
    V.Z = 10;
  }
  else if (BLoc.Z > Zmax) {
    V.Z = -10;
  }
  return V;
}