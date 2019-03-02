// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Engine/World.h"			// included for GetWorld()
#include "DrawDebugHelpers.h"		// included for DrawDebugLine()


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

	UE_LOG(LogTemp, Log, TEXT("This is the grabber class"));
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector playerViewPointLocation;
	FRotator playerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(playerViewPointLocation, playerViewPointRotation);
	//UE_LOG(LogTemp, Log, TEXT("%s : %s"), *playerViewPointLocation.ToString(), *playerViewPointRotation.ToString());

	// Adding two vectors: playerViewPointLocation + (lineTraceDirection * reach)
	FVector lineTraceEnd = playerViewPointLocation + playerViewPointRotation.Vector() * this->reach;
	DrawDebugLine(GetWorld(), playerViewPointLocation, lineTraceEnd, FColor(255, 0, 0));
	// todo: Ray-castout to reach distance

	// todo: see what we hit
	
}

