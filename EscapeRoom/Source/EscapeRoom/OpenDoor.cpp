// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"		// included for GetWorld()

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
	this->actorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	
}

void UOpenDoor::OpenDoor()
{
	this->owner->SetActorRotation(FRotator(0.f, this->closedDoorAngle + this->openedDoorAngle, 0.f));

	//FQuat quaternion = rotation.Quaternion();
	//actor->SetActorRotation(actor->GetActorQuat()*quaternion);
}

void UOpenDoor::CloseDoor()
{
	owner->SetActorRotation(FRotator(0.f, this->closedDoorAngle, 0.f));

	//FQuat quaternion = rotation.Quaternion();
	//actor->SetActorRotation(actor->GetActorQuat()*quaternion);
}

bool UOpenDoor::IsOpen() {
	return this->open;
}



// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// todo: poll the trigger volume
	if (this->pressurePlatform->IsOverlappingActor(this->actorThatOpens)) {
	// if the actorThatOpens is in the volume
		OpenDoor();
		this->lastDoorOpenTime = GetWorld()->GetTimeSeconds();
		this->open = true;
	}
	if (this->IsOpen() && this->lastDoorOpenTime + this->doorCloseDelay < GetWorld()->GetTimeSeconds()) {
		CloseDoor();
		this->open = false;
	}


	
}

