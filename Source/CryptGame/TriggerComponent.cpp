// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (Mover != nullptr) {
		AActor* AcceptableActor = GetAcceptableActor();
		//UE_LOG(LogTemp, Warning, TEXT("%s"), (AcceptableActor != nullptr) ? TEXT("Unlocking") : TEXT("RElocking"));
		//(AcceptableActor != nullptr) ? Mover->SetShouldMove(true) : Mover->SetShouldMove(false);
		if (AcceptableActor != nullptr)
		{
			UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(AcceptableActor->GetRootComponent());
			if (Component != nullptr) {
				Component->SetSimulatePhysics(false);
			}
			AcceptableActor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
			Mover->SetShouldMove(true);
		}
		else
		{
			Mover->SetShouldMove(false);
		}
	}


 }

void UTriggerComponent::SetMover(UMover* NewMover)
{
	Mover = NewMover; 
}

AActor* UTriggerComponent::GetAcceptableActor() const
{
	TArray<AActor*> ActorsArray;
	GetOverlappingActors(ActorsArray);

	for (AActor* Actor : ActorsArray) {
		if (Actor->ActorHasTag(TagName) && !Actor->ActorHasTag("Grabbed")) {
			return Actor;
		}
	}
	return nullptr;
}