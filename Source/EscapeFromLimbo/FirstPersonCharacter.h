// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FirstPersonCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UAnimMontage;
class USoundBase;

// Declaration of the delegate that will be called when the Primary Action is triggered
// It is declared as dynamic so it can be accessed also in Blueprints
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPrimaryAction);

UCLASS(config=Game)
class AFirstPersonCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** Delegate to whom anyone can subscribe to receive this event */
	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnPrimaryAction PrimaryAction;

public:
	/** Default Constructor **/
	AFirstPersonCharacter();

	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	virtual void FellOutOfWorld(const class UDamageType& dmgType) override;

protected:
	//~ AActor Interface Begin
	virtual void BeginPlay() override;
	//~ AActor Interface End

	//~ APawn Interface Begin
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	//~ APawn Interface End

	/** Fires a projectile. */
	void OnPrimaryActionInput();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles strafing movement, left and right */
	void MoveRight(float Val);
};

