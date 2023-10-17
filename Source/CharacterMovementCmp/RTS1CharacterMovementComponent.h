// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "RTS1CharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class CHARACTERMOVEMENTCMP_API URTS1CharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
	class FSavedMove_RTS1: public FSavedMove_Character {
		typedef FSavedMove_Character Super;
		uint8 Saved_bWantsToSprint : 1;
		virtual bool CanCombineWith(const FSavedMovePtr& NewMove, ACharacter* InCharacter, float MaxDelta) const override;
		virtual void Clear() override;
		virtual uint8 GetCompressedFlags() const override;
		virtual void SetMoveFor(ACharacter* C, float InDeltaTime, FVector const& NewAccel, FNetworkPredictionData_Client_Character& ClientData) override;
		virtual void PrepMoveFor(ACharacter* C) override;
	};

	class FNetworkPredictionData_Client_RTS1 : public FNetworkPredictionData_Client_Character {
	public:
		FNetworkPredictionData_Client_RTS1(const UCharacterMovementComponent& ClientMovement);

		typedef FNetworkPredictionData_Client_Character Super;

		virtual FSavedMovePtr AllocateNewMove() override;
	};
	UPROPERTY(EditDefaultsOnly) float Sprint_MaxWalkSpeed;
	UPROPERTY(EditDefaultsOnly) float Walk_MaxWalkSpeed;
public:
	bool Safe_bWantsToSprint;

public:
	URTS1CharacterMovementComponent();
	virtual FNetworkPredictionData_Client* GetPredictionData_Client() const override;
protected:
	virtual void UpdateFromCompressedFlags(uint8 Flags) override;
	virtual void OnMovementUpdated(float DeltaSeconds, const FVector& OldLocation, const FVector& OldVelocity) override;
public:
	UFUNCTION(BlueprintCallable) void SprintPressed();
	UFUNCTION(BlueprintCallable) void SprintReleassed();
	
};
