// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"

#include "OpenDoor.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEROOM_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	bool IsOpen();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void OpenDoor();
	void CloseDoor();
	

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// makes the variable openAngle visible in the Unreal editor
	UPROPERTY(VisibleAnywhere)
	float openAngle = 90.f;

	// makes the variable openAngle editable in the Unreal editor
	UPROPERTY(EditAnywhere)
	ATriggerVolume* pressurePlatform;
	
	UPROPERTY(EditAnywhere)
	float doorCloseDelay = 5.f;

	float lastDoorOpenTime;

	UPROPERTY(VisibleAnywhere)
	bool open = false;

	AActor* owner;
	AActor* actorThatOpens;

};
