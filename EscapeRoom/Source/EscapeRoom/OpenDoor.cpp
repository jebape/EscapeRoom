// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/Actor.h"
#include "Containers/Array.h"	// included for TArray data structure
#include "Engine/World.h"		// included for GetWorld()


#define OUT				// it does nothing because is defined to nothing, just marks when a parameter is a return parameter.

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	

}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	this->owner = GetOwner();
	
	
}

void UOpenDoor::OpenDoor()
{
	if(this->owner)
		this->owner->SetActorRotation(FRotator(0.f, this->closedDoorAngle + this->openedDoorAngle, 0.f));

	//FQuat quaternion = FRotator(0.f, this->closedDoorAngle + this->openedDoorAngle, 0.f).Quaternion();
	//this->owner->SetActorRotation(this->owner->GetActorQuat()*quaternion);
}

void UOpenDoor::CloseDoor()
{
	if (this->owner)
		owner->SetActorRotation(FRotator(0.f, this->closedDoorAngle, 0.f));

	//FQuat quaternion = FRotator(0.f, this->closedDoorAngle, 0.f).Quaternion();
	//this->owner->SetActorRotation(this->owner->GetActorQuat()*quaternion);
}

bool UOpenDoor::IsOpen() {
	return this->open;
}



// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// poll the trigger volume
	if (GetTotalMassOnPlatform() > massLimit) {		
		OpenDoor();
		this->lastDoorOpenTime = GetWorld()->GetTimeSeconds();
		this->open = true;
	}
	if (this->IsOpen() && this->lastDoorOpenTime + this->doorCloseDelay < GetWorld()->GetTimeSeconds()) {
		CloseDoor();
		this->open = false;
	}


	
}

float UOpenDoor::GetTotalMassOnPlatform() const
{
	if (!pressurePlatform) {
		UE_LOG(LogTemp, Error, TEXT("Pressure Platform not found in %s"), *GetOwner()->GetName());
		return 0.f;
	}
		

	float totalMass = 0.f;
	TArray<AActor*> overlappingActors;
	// finding all the overlapping actors
	pressurePlatform->GetOverlappingActors(OUT overlappingActors);

	// todo: iterate through them adding their masses
	
	for(const auto* actor : overlappingActors)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *actor->GetName());
		totalMass += actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	
	return totalMass;
}

