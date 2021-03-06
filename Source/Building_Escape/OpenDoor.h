// Copyright Joe Rafferty 2022

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"




#include "OpenDoor.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDING_ESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);

private:



	float InitialYaw;
	float CurrentYaw;

	float DoorLastOpened = 0.0f;
	
	
	UPROPERTY(EditAnywhere)
	float DoorCloseSpeed = 8;


	UPROPERTY(EditAnywhere)
	float DoorOpenSpeed = 3;

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = .5f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* DoorTrigger;

	UPROPERTY(EditAnywhere)
	float TargetYaw;

	UPROPERTY(EditAnywhere)
	AActor* ActorThatOpens;
		
};
