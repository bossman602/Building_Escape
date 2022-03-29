// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldPosition.h"
//#include "Actor.h"
#include "Math/TransformNonVectorized.h"

// Sets default values for this component's properties
UWorldPosition::UWorldPosition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWorldPosition::BeginPlay()
{
	Super::BeginPlay();

	FString ActorName = GetOwner()->GetName();
	FString ActorLocation = GetOwner()->GetActorLocation().ToString();
	FString ActorRotation = GetOwner()->GetActorRotation().ToString();
	FString ActorScale3D = GetOwner()->GetActorScale3D().ToString();
	UE_LOG(LogTemp, Warning, TEXT("%s's Location is %s"), *ActorName, *ActorLocation);
	UE_LOG(LogTemp, Warning, TEXT("%s's Rotation is %s"), *ActorName, *ActorRotation);
	UE_LOG(LogTemp, Warning, TEXT("%s's 3D Scaling is %s"), *ActorName, *ActorScale3D);



}


// Called every frame
void UWorldPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

