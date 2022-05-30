// Steve Merritt - GameDev.tv Game Jam 2022

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DynamicActor.generated.h"

UCLASS()
class ESCAPEFROMLIMBO_API ADynamicActor : public AActor
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void Activate() { bIsActive = true; }

	UFUNCTION(BlueprintCallable)
	void Deactivate() { bIsActive = false; }

protected:
	UPROPERTY(BlueprintReadOnly)
	bool bIsActive = false;
};
