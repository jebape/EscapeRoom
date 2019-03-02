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
	FRotator rotation = FRotator(0.f, 180.f, 0.f);
	this->owner->SetActorRotation(rotation);
	//FRotator ownersRotation = this->owner->GetActorRotation();

	//FQuat quaternion = rotation.Quaternion();
	//actor->SetActorRotation(actor->GetActorQuat()*quaternion);
}

void UOpenDoor::CloseDoor()
{
	FRotator rotation = FRotator(0.f, 90.f, 0.f);
	this->owner->SetActorRotation(rotation);

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
	if (this->lastDoorOpenTime + this->doorCloseDelay < GetWorld()->GetTimeSeconds() && this->IsOpen()) {
		CloseDoor();
		this->open = false;
	}


	
}

