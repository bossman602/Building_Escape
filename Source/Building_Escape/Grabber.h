// Copyright Joe Rafferty 2022

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"






#include "Grabber.generated.h"

struct FPlayerViewPoint {
	FVector Location;
	FVector Rotation;
	FVector ReachEnd;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDING_ESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	FPlayerViewPoint GetPlayerViewPoint() const;

private:
	UPROPERTY(EditAnywhere)
	float PlayerReach = 100.0f;

	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* InputComponent = nullptr;

	void Grab();
	void Release();

	void CheckForPhysicsHandle();
	void SetupInputComponent();

	FHitResult GetFirstPhysicsBodyWithinReach() const;
};
