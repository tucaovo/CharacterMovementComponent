
// Fill out your copyright notice in the Description page of Project Settings.
// Fill out your copyright notice in the Description page of Project Settings.
// Fill out your copyright notice in the Description p// Fill out your copyright notice in the Description page of Project Settings.


#include "RTS1CharacterMovementComponent.h"
#include "GameFramework/Character.h"

bool URTS1CharacterMovementComponent::FSavedMove_RTS1::CanCombineWith(const FSavedMovePtr& NewMove, ACharacter* InCharacter, float MaxDelta) const{
	FSavedMove_RTS1* NewRTS1Move = static_cast<FSavedMove_RTS1*>(NewMove.Get());
	if (Saved_bWantsToSprint != NewRTS1Move->Saved_bWantsToSprint) {
		return false;
	}
	return FSavedMove_Character::CanCombineWith(NewMove, InCharacter, MaxDelta);
}

void URTS1CharacterMovementComponent::FSavedMove_RTS1::Clear() {
	FSavedMove_Character::Clear();
	Saved_bWantsToSprint = 0;
}

uint8 URTS1CharacterMovementComponent::FSavedMove_RTS1::GetCompressedFlags() const {
	uint8 Result = Super::GetCompressedFlags();
	if (Saved_bWantsToSprint) Result = FLAG_Custom_0;
	return Result;
}

void URTS1CharacterMovementComponent::FSavedMove_RTS1::SetMoveFor(ACharacter* C, float InDeltaTime, FVector const& NewAccel, FNetworkPredictionData_Client_Character& ClientData) {
	FSavedMove_Character::SetMoveFor(C, InDeltaTime, NewAccel, ClientData);
	URTS1CharacterMovementComponent* CharacterMovement = Cast<URTS1CharacterMovementComponent>(C->GetCharacterMovement());
	Saved_bWantsToSprint = CharacterMovement->Safe_bWantsToSprint;
}

void URTS1CharacterMovementComponent::FSavedMove_RTS1::PrepMoveFor(ACharacter* C) {
	Super::PrepMoveFor(C);
	URTS1CharacterMovementComponent* CharacterMovement = Cast<URTS1CharacterMovementComponent>(C->GetCharacterMovement());
	CharacterMovement->Safe_bWantsToSprint = Saved_bWantsToSprint;
}

URTS1CharacterMovementComponent::URTS1CharacterMovementComponent() {

}

FNetworkPredictionData_Client* URTS1CharacterMovementComponent::GetPredictionData_Client() const
{
	check(PawnOwner != nullptr)

	if(ClientPredictionData == nullptr)
	{
		URTS1CharacterMovementComponent* MutableThis = const_cast<URTS1CharacterMovementComponent*>(this);

		MutableThis->ClientPredictionData = new FNetworkPredictionData_Client_RTS1(*this);
		MutableThis->ClientPredictionData->MaxSmoothNetUpdateDist = 92.f;
		MutableThis->ClientPredictionData->NoSmoothNetUpdateDist = 140.f;
	}
	return ClientPredictionData;
}

void URTS1CharacterMovementComponent::UpdateFromCompressedFlags(uint8 Flags)
{
	Super::UpdateFromCompressedFlags(Flags);
	Safe_bWantsToSprint = (Flags & FSavedMove_Character::FLAG_Custom_0) != 0;
}

void URTS1CharacterMovementComponent::OnMovementUpdated(float DeltaSeconds, const FVector& OldLocation, const FVector& OldVelocity)
{
	Super::OnMovementUpdated(DeltaSeconds, OldLocation, OldVelocity);
	if (MovementMode = MOVE_Walking) {
		if (Safe_bWantsToSprint) {
			MaxWalkSpeed = Sprint_MaxWalkSpeed;
		}
		else {
			MaxWalkSpeed = Walk_MaxWalkSpeed;
		}
	}
}

void URTS1CharacterMovementComponent::SprintReleassed()
{
	Safe_bWantsToSprint = true;
}
void URTS1CharacterMovementComponent::SprintPressed()
{
	Safe_bWantsToSprint = false;
}

URTS1CharacterMovementComponent::FNetworkPredictionData_Client_RTS1::FNetworkPredictionData_Client_RTS1(const UCharacterMovementComponent& ClientMovement) : Super(ClientMovement) {

}

FSavedMovePtr URTS1CharacterMovementComponent::FNetworkPredictionData_Client_RTS1::AllocateNewMove()
{
	return FSavedMovePtr(new FSavedMove_RTS1());
}
