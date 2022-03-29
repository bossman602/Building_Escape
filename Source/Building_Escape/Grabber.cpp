// Copyright Joe Rafferty 2022


#include "DrawDebugHelpers.h"
#include "GameFramework/PlayerController.h"
#include "Grabber.h"


#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.

	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	CheckForPhysicsHandle();

	SetupInputComponent();


}






// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FPlayerViewPoint PlayerViewPoint =	GetPlayerViewPoint();

	DrawDebugLine(
	GetWorld(),
	PlayerViewPoint.Location,
	PlayerViewPoint.ReachEnd,
	FColor(148, 0, 211),
	false,
	0.0f,
	0,
	5.0f
);


	if (PhysicsHandle->GrabbedComponent) {
		PhysicsHandle->SetTargetLocation(PlayerViewPoint.ReachEnd);
	}

//If the physics handle is attached, move the object we are holding.

	
}


void UGrabber::CheckForPhysicsHandle() {

	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (!PhysicsHandle) {
		UE_LOG(LogTemp, Error, TEXT("No PhysicsHandle Component was found. Please verify the PhysicsHandle Component was added to %s"), *GetOwner()->GetName());
	}

	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

}

void UGrabber::SetupInputComponent() {

	if (!InputComponent) {
		UE_LOG(LogTemp, Error, TEXT("No Input Mappings Found."));
	}


	/*template<class UserClass>
	FInputActionBinding& BindAction
	(
		const FName ActionName,
		const EInputEvent KeyEvent,
		UserClass * Object,
		typename FInputActionHandlerSignature::TUObjectMethodDelegate< UserClass >::FMethodPtr Func
	)*/

	else {
		UE_LOG(LogTemp, Warning, TEXT("Input Mappings found"));
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);

	}

}



void UGrabber::Grab() {
	UE_LOG(LogTemp, Warning, TEXT("Grabber Pressed"));

	// Try and Grab any actors with a physics body collision channel

	FHitResult HitResult = GetFirstPhysicsBodyWithinReach();

	FPlayerViewPoint PlayerViewPoint = GetPlayerViewPoint();

	AActor* ActorHit = HitResult.GetActor();

	if (ActorHit) {
		//UE_LOG(LogTemp, Warning, TEXT("Grabbing %s"), *ActorHit->GetActorLocation().ToString());
		UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();

		PhysicsHandle->GrabComponentAtLocationWithRotation(ComponentToGrab, NAME_None, PlayerViewPoint.ReachEnd, ActorHit->GetActorRotation());
		//PhysicsHandle->GrabComponentAtLocation(ComponentToGrab, NAME_None, LineTraceEnd);
		
		if (PhysicsHandle->GetGrabbedComponent()) {
			UE_LOG(LogTemp, Warning, TEXT("Grabbed %s"), *PhysicsHandle->GetGrabbedComponent()->GetOwner()->GetName());

			//PhysicsHandle->SetTargetLocation(HitResult.GetActor()->GetActorLocation());
		}
	}

	

	//if we are hitting something when we grab, then attach the physics handle.

	//
}

void UGrabber::Release() {
	UE_LOG(LogTemp, Warning, TEXT("Grabber Released"));

	if (PhysicsHandle->GetGrabbedComponent()) {
		UE_LOG(LogTemp, Warning, TEXT("Releasing %s"), *PhysicsHandle->GetGrabbedComponent()->GetOwner()->GetName());
		PhysicsHandle->ReleaseComponent();
	}

	// if we have an actor attached to the physics handle, realease it when released.

}




FHitResult UGrabber::GetFirstPhysicsBodyWithinReach() const {

	//Get the player viewpoint
	FHitResult Hit;
	FPlayerViewPoint PlayerViewPoint = GetPlayerViewPoint();

	
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPoint.Location,
		PlayerViewPoint.ReachEnd,
		FCollisionObjectQueryParams(
			ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

	return Hit;

}



FPlayerViewPoint UGrabber::GetPlayerViewPoint() const {

	FPlayerViewPoint PlayerViewPoint;
	
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	PlayerViewPoint.Location = PlayerViewPointLocation;
	PlayerViewPoint.Rotation = PlayerViewPointRotation.Vector();

	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * PlayerReach;

	PlayerViewPoint.ReachEnd = LineTraceEnd;

	return PlayerViewPoint;

}





//UE_LOG(LogTemp, Warning, TEXT("LineTraceDirection: %s"), *LineTraceDirection.ToString());



//DrawDebugLine(
//	GetWorld(),
//	PlayerViewPointLocation,
//	LineTraceEnd,
//	FColor(148, 0, 211),
//	false,
//	0.0f,
//	0,
//	5.0f
//);

	//if (ActorHit) {

		//UE_LOG(LogTemp, Warning, TEXT("%s was hit at %s"), *ActorHit->GetName(), *ActorHit->GetActorLocation().ToString());

	//}