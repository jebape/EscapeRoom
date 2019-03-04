// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"				// included for GetWorld()
#include "GameFramework/Actor.h"		// inclided for GetOwner()
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
		// bind input action
		inputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		inputComponent->BindAction("Grab", IE_Released,	this, &UGrabber::Release);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("UInputComponent not found in %s"), *GetOwner()->GetName());
	}
}

// look for attached physics handle
void UGrabber::FindPhysicsComponent()
{
	physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (physicsHandle == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("UPhysicshandleComponent not found in %s"), *GetOwner()->GetName());
	}
}

// called when Grab key is pressed
void UGrabber::Grab() 
{
	// result from reaching an actor with physics collision channel
	FHitResult hitResult = this->GetPhysicsBodyInReach();
	// if we hit, then attach physics handle
	AActor* actorHit = hitResult.GetActor();
	if (actorHit != nullptr) {
		UE_LOG(LogTemp, Log, TEXT("Grabbing %s"), *actorHit->GetName());
		UPrimitiveComponent* componentToGrab = hitResult.GetComponent();
		physicsHandle->GrabComponent(
			componentToGrab,
			NAME_None,	// bone name (we do not have a bone)
			componentToGrab->GetOwner()->GetActorLocation(),	// location where we grab
			true	// allows rotation
		);
	}

}

// called when Grab key is released
void UGrabber::Release()
{
	// release atached physics handle
	physicsHandle->ReleaseComponent();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// if physics handle is attached, then move object we are holding
	if (physicsHandle->GrabbedComponent) {
		physicsHandle->SetTargetLocation(this->GetLineTraceEnd());
	}
}

FVector UGrabber::GetLineTraceStart() const
{
	// gets player view point location & rotation
	FVector playerViewPointLocation;
	FRotator playerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT playerViewPointLocation,
		OUT playerViewPointRotation
	);

	// Addition of two vectors: playerViewPointLocation + (lineTraceDirection * reach)
	return playerViewPointLocation;
}

FVector UGrabber::GetLineTraceEnd() const
{
	// gets player view point location & rotation
	FVector playerViewPointLocation;
	FRotator playerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT playerViewPointLocation,
		OUT playerViewPointRotation
	);

	// Addition of two vectors: playerViewPointLocation + (lineTraceDirection * reach)
	 return playerViewPointLocation + playerViewPointRotation.Vector() * this->reach;
}

FHitResult UGrabber::GetPhysicsBodyInReach() const
{
	// result of what we are hitting
	FHitResult hitResult;
	GetWorld()->LineTraceSingleByObjectType(
		OUT hitResult,
		this->GetLineTraceStart(),
		this->GetLineTraceEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		FCollisionQueryParams(FName(TEXT("")), false, GetOwner())	/// false because we want the simple colliders & we ignore ourselves
	);
	return hitResult;
}

