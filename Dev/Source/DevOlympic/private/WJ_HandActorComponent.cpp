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

	// 플레이어 받아오기
	player = Cast<AWJ_LobbyPlayer>(GetOwner());
	// 플레이어가 존재한다면
	if (player)
	{
		// 왼손 애니메이션 인스턴스 받아오기
		l_handAnim = Cast<UWJ_LobbyHandAnimInstance>(player->leftHand->GetAnimInstance());
		// 오른손 애니메이션 인스턴스 받아오기
		r_handAnim = Cast<UWJ_LobbyHandAnimInstance>(player->rightHand->GetAnimInstance());
	}
}

// 키 조작 바인딩
void UWJ_HandActorComponent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// 왼손 잡기 애니메이션 실행
	PlayerInputComponent->BindAction("GrabLeft", IE_Pressed, this, &UWJ_HandActorComponent::GrabLeftHand);
	// 왼손 펴기 애니메이션 실행
	PlayerInputComponent->BindAction("GrabLeft", IE_Released, this, &UWJ_HandActorComponent::OpenLeftHand);
	// 오른손 잡기 애니메이션 실행
	PlayerInputComponent->BindAction("GrabRight", IE_Pressed, this, &UWJ_HandActorComponent::GrabRIghtHand);
	// 오른손 펴기 애니메이션 실행
	PlayerInputComponent->BindAction("GrabRight", IE_Released, this, &UWJ_HandActorComponent::OpenRIghtHand);


	// 왼손 Grip ->  마우스 좌클릭
	PlayerInputComponent->BindAction("GrabLeft", IE_Pressed, this, &UWJ_HandActorComponent::ButtonClick);
	// Released
	PlayerInputComponent->BindAction("GrabLeft", IE_Released, this, &UWJ_HandActorComponent::ButtonRelease);

	
	// 오른손 Grip버튼 -> 물체 집기
	PlayerInputComponent->BindAction("GrabRight", IE_Pressed, this, &UWJ_HandActorComponent::GrabAction);
	PlayerInputComponent->BindAction("GrabRight", IE_Released, this, &UWJ_HandActorComponent::ReleaseAction);
}

void UWJ_HandActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// 버튼 조작에 따라 밸류 값 조정

	// 왼손 애니메이션 타겟 밸류 값에 따라 움직임 조정
	l_handAnim->gripValue = FMath::Lerp(l_handAnim->gripValue, l_targetGripValue, gripSpeed * DeltaTime);
	// 오른손 애니메이션 타겟 밸류 값에 따라 움직임 조정
	r_handAnim->gripValue = FMath::Lerp(r_handAnim->gripValue, r_targetGripValue, gripSpeed * DeltaTime);

	
	//DrawGrabLine();
}

// 왼손 잡기 애니메이션 실행
void UWJ_HandActorComponent::GrabLeftHand()
{
	l_targetGripValue = 1.0f;
}

// 왼손 펴기 애니메이션 실행
void UWJ_HandActorComponent::OpenLeftHand()
{
	l_targetGripValue = 0.0f;
}

// 오른손 잡기 애니메이션 실행
void UWJ_HandActorComponent::GrabRIghtHand()
{
	r_targetGripValue = 1.0f;
}

// 오른손 펴기 애니메이션 실행
void UWJ_HandActorComponent::OpenRIghtHand()
{
	r_targetGripValue = 0.0f;
}



void UWJ_HandActorComponent::ButtonClick()
{
	// 위젯 인터렉션 포인터의 클릭 포인터 키 값을 마우스 왼쪽 버튼 클릭으로 설정
	// ⇒ 왼쪽 버튼을 누른것과 같은 효과를 준다.
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

		// 물리 객체와 동적 객체에 대해서 충돌 체크
		FCollisionObjectQueryParams objParams;
		objParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		objParams.AddObjectTypesToQuery(ECC_PhysicsBody);

		// 플레이어 액터는 무시
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
		// 잡으면 그상태에서 들어올리기
		avatarObj = Cast<AWJ_AvatarObj>(grabActor);

		if (avatarObj)
		{
			// 나한테 붗었어도 오브젝트 본인의 월드좌표를 잃지 않는다. 자식 오브젝트처럼 행동은 함. 잡는 순간의 위치를 잃지않고 유지됨.
			//FAttachmentTransformRules attachRules = FAttachmentTransformRules::KeepWorldTransform;
			FAttachmentTransformRules attachRules = FAttachmentTransformRules::SnapToTargetNotIncludingScale;

			// 손에 붙이기
			avatarObj->bodyComp->SetSimulatePhysics(false);
			avatarObj->AttachToComponent(player->rightHand, attachRules, TEXT("GrabPoint"));

			// 반드시 붙인다음에 옮겨야 Relative가 의미가있다. 손의 위치로부터 상대좌표
			avatarObj->bodyComp->SetRelativeLocation(avatarObj->grabOffset);

			// 들어올리는 힘 vs 중력으로 떨어지는 힘이 계속 부딪히면서 계쏙 부들부들 떨게됨 -> 중력을 꺼야한다.
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
	//parent 옛날 버전 
	//떼는 순간 원래 위치에서 바로 떨어질지, 등등
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

		// 물리 객체와 동적 객체에 대해서 충돌 체크
		FCollisionObjectQueryParams objParams;
		objParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		objParams.AddObjectTypesToQuery(ECC_PhysicsBody);

		// 플레이어 액터는 무시
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