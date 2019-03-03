// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Engine/World.h"				// included for GetWorld()
#include "DrawDebugHelpers.h"			// included for DrawDebugLine()
#include "CollisionQueryParams.h"		// included for FCollisionObjectQueryparams


#define OUT				// it does nothing because is defined to nothing, just marks when a parameter is a return parameter.

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	
	FindPhysicsComponent();
	FindInputComponent();

}

// look for attached input component
void UGrabber::FindInputComponent()
{
	inputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (inputComponent) {
		UE_LOG(LogTemp, Log, TEXT("UInputComponent found in %s"), *GetOwner()->GetName());
		// bind input action
		inputComponent->BindAction(
			"Grab",
			IE_Pressed,
			this,
			&UGrabber::Grab
		);
		inputComponent->BindAction(
			"Grab",
			IE_Released,
			this,
			&UGrabber::Release
		);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("UInputComponent not found in %s"), *GetOwner()->GetName());
	}
}

// look for attached physics handle
void UGrabber::FindPhysicsComponent()
{
	physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!physicsHandle) {
		UE_LOG(LogTemp, Error, TEXT("UPhysicshandleComponent not found in %s"), *GetOwner()->GetName());
	}
}

// called when Grab key is pressed
void UGrabber::Grab() 
{
	UE_LOG(LogTemp, Warning, TEXT("Grab action key pressed"));

	// todo: try to reach any actor with physics collision channel
	FHitResult res = this->GetPhysicsBodyInReach();
	// todo: if we hit, then attach physics handle

}

// called when Grab key is released
void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab action key released"));

	// todo: release atached physics handle
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// todo: if physics handle is attached, then move object we are holding

	
	// see what we hit
	
	
}

FHitResult UGrabber::GetPhysicsBodyInReach() const
{
	// gets player view point location & rotation
	FVector playerViewPointLocation;
	FRotator playerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT playerViewPointLocation,
		OUT playerViewPointRotation
	);

	// Addition of two vectors: playerViewPointLocation + (lineTraceDirection * reach)
	FVector lineTraceEnd = playerViewPointLocation + playerViewPointRotation.Vector() * this->reach;
	//DrawDebugLine(GetWorld(), playerViewPointLocation, lineTraceEnd, FColor(255, 0, 0));	// Drawa visible line trace for debugging

	// result of what we are hitting
	FHitResult hitResult;
	GetWorld()->LineTraceSingleByObjectType(
		OUT hitResult,
		playerViewPointLocation,
		lineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		FCollisionQueryParams(FName(TEXT("")), false, GetOwner())	/// false because we want the simple colliders & we ignore ourselves
	);

	AActor* actorHit = hitResult.GetActor();
	if (actorHit) {
		UE_LOG(LogTemp, Log, TEXT("Line trace hitting: %s"), *actorHit->GetName());
	}


	return hitResult;
}

