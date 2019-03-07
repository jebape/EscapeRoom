// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"

#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOpenRequest);

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

	// returns total mass over the plate in Kg
	float GetTotalMassOnPlatform() const;

	UPROPERTY(BlueprintAssignable)
		FOnOpenRequest onOpenRequest;

private:
	AActor* owner = nullptr;
	AActor* actorThatOpens = nullptr;
	float lastDoorOpenTime = 0.f;

	// makes the variable editable in the Unreal editor
	UPROPERTY(EditAnywhere)
		float openedDoorAngle = 100.f;
	UPROPERTY(EditAnywhere)
		float closedDoorAngle = 90.f;
	UPROPERTY(EditAnywhere)
		float doorCloseDelay = 5.f;
	UPROPERTY(EditAnywhere)
		float massLimit = 50.f;
	UPROPERTY(EditAnywhere)
		ATriggerVolume* pressurePlatform = nullptr;

	// makes the variable visible in the Unreal editor
	UPROPERTY(VisibleAnywhere)
		bool open = false;

	

};
