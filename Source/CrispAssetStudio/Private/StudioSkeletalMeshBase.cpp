//Copyright Crisp Clover. Feel free to copy.


#include "StudioSkeletalMeshBase.h"

AStudioSkeletalMeshBase::AStudioSkeletalMeshBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	USkeletalMeshComponent* mc = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	mc->SetCollisionProfileName(UCollisionProfile::BlockAll_ProfileName);
	mc->Mobility = EComponentMobility::Movable;
	mc->SetGenerateOverlapEvents(false);

	RootComponent = MeshComponent = mc;

	USkeletalMeshComponent* wc = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Wireframe"));
	wc->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	wc->Mobility = EComponentMobility::Movable;
	wc->SetGenerateOverlapEvents(false);
	
	WireframeComponent = wc;

	WireframeComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);
}

void AStudioSkeletalMeshBase::OnConstruction(const FTransform& transform)
{
	Super::OnConstruction(transform);

	if (Mesh)
		Cast<USkeletalMeshComponent>(MeshComponent)->SetSkeletalMesh(Mesh);
}

bool AStudioSkeletalMeshBase::ToggleWireframe()
{
	if (!WireframeMaterial)
		return false;

	wireframe = !wireframe;

	if (wireframe && Mesh)
	{
		Cast<USkeletalMeshComponent>(WireframeComponent)->SetSkeletalMesh(Mesh);

		for (int i = 0; i < WireframeComponent->GetNumMaterials(); i++)
			WireframeComponent->SetMaterial(i, WireframeMaterial);
	}
	else
	{
		Cast<USkeletalMeshComponent>(WireframeComponent)->SetSkeletalMesh(nullptr);
	}

	Super::ToggleWireframe();
	return true;
}