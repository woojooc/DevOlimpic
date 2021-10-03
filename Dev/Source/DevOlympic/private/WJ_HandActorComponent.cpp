#include "WJ_HandActorComponent.h"
#include "WJ_LobbyPlayer.h"
#include "WJ_LobbyHandAnimInstance.h"
#include <Components/WidgetInteractionComponent.h>
#include "WJ_AvatarObj.h"
#include "DrawDebugHelpers.h"
#include "Components/TextRenderComponent.h"
#include <Engine/SkeletalMeshSocket.h>


UWJ_HandActorComponent::UWJ_HandActorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}


void UWJ_HandActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// �÷��̾� �޾ƿ���
	player = Cast<AWJ_LobbyPlayer>(GetOwner());
	// �÷��̾ �����Ѵٸ�
	if (player)
	{
		// �޼� �ִϸ��̼� �ν��Ͻ� �޾ƿ���
		l_handAnim = Cast<UWJ_LobbyHandAnimInstance>(player->leftHand->GetAnimInstance());
		// ������ �ִϸ��̼� �ν��Ͻ� �޾ƿ���
		r_handAnim = Cast<UWJ_LobbyHandAnimInstance>(player->rightHand->GetAnimInstance());
	}
}

// Ű ���� ���ε�
void UWJ_HandActorComponent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// �޼� ��� �ִϸ��̼� ����
	PlayerInputComponent->BindAction("GrabLeft", IE_Pressed, this, &UWJ_HandActorComponent::GrabLeftHand);
	// �޼� ��� �ִϸ��̼� ����
	PlayerInputComponent->BindAction("GrabLeft", IE_Released, this, &UWJ_HandActorComponent::OpenLeftHand);
	// ������ ��� �ִϸ��̼� ����
	PlayerInputComponent->BindAction("GrabRight", IE_Pressed, this, &UWJ_HandActorComponent::GrabRIghtHand);
	// ������ ��� �ִϸ��̼� ����
	PlayerInputComponent->BindAction("GrabRight", IE_Released, this, &UWJ_HandActorComponent::OpenRIghtHand);


	// �޼� Grip ->  ���콺 ��Ŭ��
	PlayerInputComponent->BindAction("GrabLeft", IE_Pressed, this, &UWJ_HandActorComponent::ButtonClick);
	// Released
	PlayerInputComponent->BindAction("GrabLeft", IE_Released, this, &UWJ_HandActorComponent::ButtonRelease);

	
	// ������ Grip��ư -> ��ü ����
	PlayerInputComponent->BindAction("GrabRight", IE_Pressed, this, &UWJ_HandActorComponent::GrabAction);
	PlayerInputComponent->BindAction("GrabRight", IE_Released, this, &UWJ_HandActorComponent::ReleaseAction);
}

void UWJ_HandActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ��ư ���ۿ� ���� ��� �� ����

	// �޼� �ִϸ��̼� Ÿ�� ��� ���� ���� ������ ����
	l_handAnim->gripValue = FMath::Lerp(l_handAnim->gripValue, l_targetGripValue, gripSpeed * DeltaTime);
	// ������ �ִϸ��̼� Ÿ�� ��� ���� ���� ������ ����
	r_handAnim->gripValue = FMath::Lerp(r_handAnim->gripValue, r_targetGripValue, gripSpeed * DeltaTime);

	
	//DrawGrabLine();
}

// �޼� ��� �ִϸ��̼� ����
void UWJ_HandActorComponent::GrabLeftHand()
{
	l_targetGripValue = 1.0f;
}

// �޼� ��� �ִϸ��̼� ����
void UWJ_HandActorComponent::OpenLeftHand()
{
	l_targetGripValue = 0.0f;
}

// ������ ��� �ִϸ��̼� ����
void UWJ_HandActorComponent::GrabRIghtHand()
{
	r_targetGripValue = 1.0f;
}

// ������ ��� �ִϸ��̼� ����
void UWJ_HandActorComponent::OpenRIghtHand()
{
	r_targetGripValue = 0.0f;
}



void UWJ_HandActorComponent::ButtonClick()
{
	// ���� ���ͷ��� �������� Ŭ�� ������ Ű ���� ���콺 ���� ��ư Ŭ������ ����
	// �� ���� ��ư�� �����Ͱ� ���� ȿ���� �ش�.
	player->widgetPointer->PressPointerKey(EKeys::LeftMouseButton);
}

void UWJ_HandActorComponent::ButtonRelease()
{
	player->widgetPointer->ReleasePointerKey(EKeys::LeftMouseButton);
}

void UWJ_HandActorComponent::GrabAction()
{
	AActor* grabActor = grabObject.GetActor();

	if (grabActor == nullptr)
	{
		FHitResult hitInfo;
		//auto grabSokect = player->rightHand->GetSocketByName(TEXT("GrabPoint"));;
		FVector startPos = player->rightHand->GetSocketLocation(TEXT("GrabPoint"));

		// ���� ��ü�� ���� ��ü�� ���ؼ� �浹 üũ
		FCollisionObjectQueryParams objParams;
		objParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		objParams.AddObjectTypesToQuery(ECC_PhysicsBody);

		// �÷��̾� ���ʹ� ����
		FCollisionQueryParams queryParams;
		queryParams.AddIgnoredActor(player);

		if (GetWorld()->SweepSingleByObjectType(hitInfo, startPos, startPos, FQuat::Identity, objParams, FCollisionShape::MakeSphere(15.f), queryParams))
		{
			grabObject = hitInfo;
			player->rightLog->SetText(FText::FromString(hitInfo.GetActor()->GetName()));
		}
		else
		{
			grabObject = FHitResult();
			player->rightLog->SetText(FText::FromString(TEXT("Null")));
		}

		DrawDebugSphere(GetWorld(), startPos, 15.f, 30, FColor::Green, false, -1, 0, 1);

		return;
	}

	if (avatarObj == nullptr)
	{
		// ������ �׻��¿��� ���ø���
		avatarObj = Cast<AWJ_AvatarObj>(grabActor);

		if (avatarObj)
		{
			// ������ �ʾ�� ������Ʈ ������ ������ǥ�� ���� �ʴ´�. �ڽ� ������Ʈó�� �ൿ�� ��. ��� ������ ��ġ�� �����ʰ� ������.
			//FAttachmentTransformRules attachRules = FAttachmentTransformRules::KeepWorldTransform;
			FAttachmentTransformRules attachRules = FAttachmentTransformRules::SnapToTargetNotIncludingScale;

			// �տ� ���̱�
			avatarObj->bodyComp->SetSimulatePhysics(false);
			avatarObj->AttachToComponent(player->rightHand, attachRules, TEXT("GrabPoint"));

			// �ݵ�� ���δ����� �Űܾ� Relative�� �ǹ̰��ִ�. ���� ��ġ�κ��� �����ǥ
			avatarObj->bodyComp->SetRelativeLocation(avatarObj->grabOffset);

			// ���ø��� �� vs �߷����� �������� ���� ��� �ε����鼭 ��� �ε�ε� ���Ե� -> �߷��� �����Ѵ�.
			avatarObj->bodyComp->SetEnableGravity(false);
		}
	}
}

void UWJ_HandActorComponent::ReleaseAction()
{
	if (!avatarObj)
	{
		return;
	}

	avatarObj->bodyComp->SetEnableGravity(true);
	//parent ���� ���� 
	//���� ���� ���� ��ġ���� �ٷ� ��������, ���
	avatarObj->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	avatarObj->bodyComp->SetSimulatePhysics(true);

	avatarObj = nullptr;
	grabObject = FHitResult();

}

void UWJ_HandActorComponent::DrawGrabLine()
{
	if (avatarObj == nullptr)
	{
		FHitResult hitInfo;
		FVector startPos = player->rightHand->GetComponentLocation();

		// ���� ��ü�� ���� ��ü�� ���ؼ� �浹 üũ
		FCollisionObjectQueryParams objParams;
		objParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		objParams.AddObjectTypesToQuery(ECC_PhysicsBody);

		// �÷��̾� ���ʹ� ����
		FCollisionQueryParams queryParams;
		queryParams.AddIgnoredActor(player);

		if (GetWorld()->SweepSingleByObjectType(hitInfo, startPos, startPos, FQuat::Identity, objParams, FCollisionShape::MakeSphere(15.f), queryParams))
		{
			grabObject = hitInfo;
		}
		else
		{
			grabObject = FHitResult();
		}

		DrawDebugSphere(GetWorld(), startPos, 15.f, 30, FColor::Green, false, -1, 0, 1);
	
	}
}