// Copyright Joe Rafferty 2022


#include "OpenDoor.h"
//#include "Math/TransformNonVectorized.h"
#include "GameFramework/PlayerController.h"



// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	TargetYaw += InitialYaw;


	if (!DoorTrigger) {

		UE_LOG(LogTemp, Error, TEXT("%s has the OpenDoor component but does not have a DoorTrigger set!"), *GetOwner()->GetName());

	}

	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();

}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	



	if (DoorTrigger && DoorTrigger->IsOverlappingActor(ActorThatOpens)) {

		OpenDoor(DeltaTime);
		DoorLastOpened = GetWorld()->GetTimeSeconds();
		
	}
	else {
		if (GetWorld()->GetTimeSeconds() - DoorLastOpened > DoorCloseDelay) {
			CloseDoor(DeltaTime);
		}
	}
	

}

void UOpenDoor::OpenDoor(float DeltaTime) {

	/*if (DoorTrigger->IsOverlappingActor() == )*/
//UE_LOG(LogTemp, Warning, TEXT("Current Rotation: %s"), *CurrentRotation.ToString());
//UE_LOG(LogTemp, Warning, TEXT("Current Yaw: %f"), CurrentRotation.Yaw);
	CurrentYaw = FMath::FInterpTo(CurrentYaw, TargetYaw, DeltaTime, DoorOpenSpeed);
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	//UE_LOG(LogTemp, Warning, TEXT("Current Rotation: %s"), *DoorRotation.ToString());
	DoorRotation.Yaw = CurrentYaw;

	GetOwner()->SetActorRotation(DoorRotation);

}

void UOpenDoor::CloseDoor(float DeltaTime) {

	/*if (DoorTrigger->IsOverlappingActor() == )*/
//UE_LOG(LogTemp, Warning, TEXT("Current Rotation: %s"), *CurrentRotation.ToString());
//UE_LOG(LogTemp, Warning, TEXT("Current Yaw: %f"), CurrentRotation.Yaw);
	CurrentYaw = FMath::FInterpTo(CurrentYaw, InitialYaw, DeltaTime, DoorCloseSpeed);
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	//UE_LOG(LogTemp, Warning, TEXT("Current Rotation: %s"), *DoorRotation.ToString());
	DoorRotation.Yaw = CurrentYaw;

	GetOwner()->SetActorRotation(DoorRotation);

}