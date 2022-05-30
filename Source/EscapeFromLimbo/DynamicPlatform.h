// Steve Merritt - GameDev.tv Game Jam 2022

#pragma once

#include "DynamicActor.h"
#include "DynamicPlatform.generated.h"

UCLASS()
class ESCAPEFROMLIMBO_API ADynamicPlatform : public ADynamicActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADynamicPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, Meta = (MakeEditWidget = true))
	FVector TargetPoint;

	UPROPERTY(EditAnywhere)
	float Speed = 0.f;

	UPROPERTY(EditInstanceOnly, Meta = (Tooltip = "Allows this platform to cycle between start and target locations."))
	bool bLoopMovement = false;

	UPROPERTY(EditInstanceOnly, Meta = (Tooltip = "Enable this flag to have the platform rotate towards the target point instead of move."))
	bool bRotateTowardsTarget = false;

	UPROPERTY(EditInstanceOnly, Meta = (Tooltip = "Enable this flag to have the platform rotate in place around its forward axis."))
	bool bRotateInPlaceHorizontal = false;

	UPROPERTY(EditInstanceOnly, Meta = (Tooltip = "Enable this flag to have the platform rotate in place around its up axis."))
	bool bRotateInPlaceVertical = false;

	UPROPERTY(BlueprintReadWrite)
	FVector MeshLocalPosition;

private:
	FVector StartLocation;
	FVector TargetLocation;
	FVector TargetDir;
	FVector TargetDirection;
	FVector CurrentTarget;

	FVector MeshPosition_WS;
	float UnitRotation = 0.f;
	FVector ActorForward;
};
