// Steve Merritt - GameDev.tv Game Jam 2022


#include "DynamicPlatform.h"

// Sets default values
ADynamicPlatform::ADynamicPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADynamicPlatform::BeginPlay()
{
	Super::BeginPlay();
	
	StartLocation = GetActorLocation();
	ActorForward = GetActorRotation().Vector().GetSafeNormal();

	TargetLocation = GetActorTransform().TransformPositionNoScale(TargetPoint);
	TargetDirection = (TargetLocation - StartLocation).GetSafeNormal();
	CurrentTarget = TargetLocation;
	
	MeshPosition_WS = StartLocation + (ActorForward * MeshLocalPosition.Size());

	//DrawDebugLine(GetWorld(), StartLocation, StartLocation + ActorForward * 100.f, FColor::Red, true, -1.f, 0, 10.f);
	//DrawDebugLine(GetWorld(), StartLocation, StartLocation + TargetDirection * 100.f, FColor::Cyan, true, -1.f, 0, 10.f);
	//DrawDebugSphere(GetWorld(), TargetLocation, 25.f, 32, FColor::Cyan, true, -1.f, 0, 1.f);
}

// Called every frame
void ADynamicPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Only move if we're activated
	if (!bIsActive)
	{
		return;
	}

	if (bRotateInPlaceHorizontal || bRotateInPlaceVertical)
	{
		FRotator Rotation = GetActorRotation();

		if (bRotateInPlaceHorizontal)
		{
			// Rotate around our forward axis
			Rotation.Roll += Speed * DeltaTime;
		}
		else
		{
			// Rotate around our up axis
			Rotation.Yaw += Speed * DeltaTime;
		}

		SetActorRotation(Rotation);
	}
	else if (bRotateTowardsTarget)
	{
		// Lerp between our original direction and the direction to our target
		UnitRotation = FMath::Clamp(UnitRotation + Speed * DeltaTime, 0.f, 1.f);
		FVector NewForward = FMath::Lerp(ActorForward, TargetDirection, UnitRotation);
		SetActorRotation(NewForward.ToOrientationRotator());
	}
	else
	{
		// Move towards our new location
		FVector Location = GetActorLocation();
		FVector NewLocation = Location + TargetDirection * Speed * DeltaTime;

		// Check if we need to clamp to our target location and only change direction if we're in loop mode
		if (CurrentTarget == TargetLocation && FVector::DotProduct(TargetDirection, TargetLocation - NewLocation) < 0)
		{
			if (bLoopMovement)
			{
				NewLocation = TargetLocation;
				TargetDirection = -TargetDirection;
				CurrentTarget = StartLocation;
			}
			else
			{
				bIsActive = false;
			}
		}
		else if (CurrentTarget == StartLocation && FVector::DotProduct(TargetDirection, StartLocation - NewLocation) < 0)
		{
			NewLocation = StartLocation;
			TargetDirection = -TargetDirection;
			CurrentTarget = TargetLocation;
		}

		SetActorLocation(NewLocation);
	}
}

