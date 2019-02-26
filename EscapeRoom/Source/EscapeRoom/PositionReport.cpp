// Fill out your copyright notice in the Description page of Project Settings.

#include "PositionReport.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UPositionReport::UPositionReport()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	
}


// Called when the game starts
void UPositionReport::BeginPlay()
{
	Super::BeginPlay();

	FString itemName = GetOwner()->GetName();
	FString itemPosition = GetOwner()->GetActorLocation().ToString();
	UE_LOG(LogTemp, Error, TEXT("%s is at %s"), *itemName, *itemPosition);  // note: The * is not referig to a pointer. It is a operator overflow.
	//UE_LOG(LogTemp, Warning, TEXT("Position report on $s"), *itemName);
	//UE_LOG(LogTemp, Log, TEXT("Position report on %s"), *itemName);
}


// Called every frame
void UPositionReport::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

