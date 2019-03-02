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
	AActor* owner;
	AActor* actorThatOpens;
	float lastDoorOpenTime;

	// makes the variable editable in the Unreal editor
	UPROPERTY(EditAnywhere)
		float openedDoorAngle = 100.f;
	UPROPERTY(EditAnywhere)
		float closedDoorAngle = 90.f;
	UPROPERTY(EditAnywhere)
		float doorCloseDelay = 5.f;
	UPROPERTY(EditAnywhere)
		ATriggerVolume* pressurePlatform;

	// makes the variable visible in the Unreal editor
	UPROPERTY(VisibleAnywhere)
		bool open = false;



};
