// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Camera/CameraComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"



// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UPhysicsHandleComponent* PhysicalHandle = GetPhysicsHandle();
	if (PhysicalHandle == nullptr)return;
	if (PhysicalHandle->GetGrabbedComponent() != nullptr) {
		FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
		PhysicalHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
	}

}

void UGrabber::Release()
{
	UPhysicsHandleComponent* PhysicalHandle = GetPhysicsHandle();
	if (PhysicalHandle && PhysicalHandle->GetGrabbedComponent() == nullptr)return;
	PhysicalHandle->GetGrabbedComponent()->GetOwner()->Tags.Remove("Grabbed");
	PhysicalHandle->ReleaseComponent();

}

void UGrabber::Grab()
{
	UPhysicsHandleComponent* PhysicalHandle = GetPhysicsHandle();
	if (PhysicalHandle == nullptr)return;

	FHitResult HitResult;
	bool bHasHit = GetGrabbableInreach(HitResult);
	if (bHasHit) {
		UPrimitiveComponent* HitComponent = HitResult.GetComponent(); 
		HitComponent->WakeAllRigidBodies();
		HitResult.GetActor()->Tags.Add("Grabbed");
		HitResult.GetComponent()->SetSimulatePhysics(true);
		HitResult.GetActor()->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

		PhysicalHandle->GrabComponentAtLocationWithRotation(
			HitComponent,
			NAME_None,
			HitResult.ImpactPoint,
			GetComponentRotation()
		);
	}
}

UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const
{
	UPhysicsHandleComponent* PhysicalHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicalHandle == nullptr) { 
		UE_LOG(LogTemp, Error, TEXT("No Handle"));
	}
	return PhysicalHandle;
	
}

bool UGrabber::GetGrabbableInreach(FHitResult& OutHitResult) const
{
	FVector Start = GetComponentLocation();
	FVector End = GetComponentLocation() + GetForwardVector() * GrabDistance;
	DrawDebugLine(GetWorld(), Start, End, FColor::Cyan, false, -1.0f, 0U, 1.0f);
	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);
	return GetWorld()->SweepSingleByChannel(OutHitResult, Start, End, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, Sphere);
}

