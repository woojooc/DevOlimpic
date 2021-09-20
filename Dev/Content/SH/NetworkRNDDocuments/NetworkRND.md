# 언리얼 네트워킹 RND

<br>
네트워크는 크게 변수 동기화(Property updates)와 RPC 통신(Remote Procedure Calls)으로 동작한다. 서버와 각 클라이언트가 가진 특정 변수값이 일치하도록 하는것이 변수 동기화, 서버와 클라이언트가 서로 선언된 함수를 호출하여 함수 실행의 결과를 동기화하는 것이 RPC 통신이다.
<br>
<br>

## 컴포넌트 동기화<br><br>
![ex_screenshot](./images/Replicate1.png)<br>
![ex_screenshot](./images/Replicate2.png)<br>
<br>
Pawn 컴포넌트에서는 Replication 세팅의 Replicate를, Collision 컴포넌트에서는 Physics의 Replicate Physics to Autonomous Proxy를 체크 하여 Replicate한다.
<br>
<br>
## 변수 동기화<br><br>
### 변수 값 전달, 동기화(Replicated)   
```C++
// Header
UPROPERTY(Replicated) // UPROPERTY로 동기화 설정
bool bIsDoorOpen;

void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const; // 변수동기화 설정을 위한 함수

```
```C++
// CPP
#include "Net/UnrealNetwork.h" // DOREPLIFETIME 변수 동기화를 위한 헤더 추가

...

// 변수 동기화를 위한 함수 선언
void ADoor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ADoor, bIsDoorOpen);
}
```
<br>

### 변수 값 할당에 따른 함수 호출(ReplicatedUsing)<br><br>

```C++
// Header
UPROPERTY(ReplicatedUsing = OnRep_ToggleDoor) // ReplicatedUsing 뒤에 bIsDoorOpen 변수가 변경될때마다 호출될 함수를 지정
bool bIsDoorOpen;

UFUNCTION()
void OnRep_ToggleDoor();

void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const; // 변수동기화 설정을 위한 함수
```
```C++
// CPP
#include "Net/UnrealNetwork.h" // DOREPLIFETIME 변수 동기화를 위한 헤더 추가

...

// 변수 동기화를 위한 함수 선언
void ADoor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ADoor, bIsDoorOpen); // 동기화할 변수 값을 가진 클래스와 동기화할 변수 값을 지정
}

// 변수가 새롭게 할당(Set) 될때마다 호출되는 함수 설정
void ADoor::OnRep_ToggleDoor()
{
	UE_LOG(LogTemp, Warning, TEXT("Door is open : %d"), bIsDoorOpen);

	if (!bIsDoorOpen && closeAnimation) // 문을 닫는다
	{
		doorMesh->PlayAnimation(closeAnimation, false);
	}
	else if (bIsDoorOpen && openAnimation) // 문을 연다
	{
		doorMesh->PlayAnimation(openAnimation, false);
	}
}
```
<br>

### OnRep함수를 실행하기 위한 조건 달기<br>
DOREPLIFETIME_CONDITION을 사용하여 서버 혹은 클라이언트, 오너에 대한 조건에 따라 어떤 유저가 함수를 호출할지 지정할 수 있다
<br>

```C++
// CPP
// 변수 동기화를 위한 함수 선언
void AMultiplayerRNDCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);	 

	// 액터의 오너를 제외하고 함수를 실행, 미리 실행되는 스폰 함수와 함께 두번 호출되는것을 막는다
	DOREPLIFETIME_CONDITION(AMultiplayerRNDCharacter, ShotsFired, COND_SkipOwner);
}

```
<br>

## RPC 통신<br><br>

참조 : [RPC 사용하기 공식 문서](https://docs.unrealengine.com/4.27/ko/InteractiveExperiences/Networking/Actors/RPCs/)


함수를 RPC 로 선언하려면 UFUNCTION 선언에 Server, Client, NetMulticast 키워드를 붙여주기만 하면 된다. 예를 들어 함수를 서버에서 호출되지만 클라이언트에서 실행되는 RPC 로 선언하려면, 다음과 같이 선언.
```C++
UFUNCTION( Client ) // 서버에서 호출하여 클라이언트에서 실행
void ClientRPCFunction();
```


함수를 클라이언트에서 호출되지만 서버에서 실행되는 RPC 로 선언하는 것은 Server 키워드를 사용한다는 것 빼고는 매우 유사하다:
```C++
UFUNCTION( Server ) // 클라이언트에서 호출하여 서버에서 실행
void ServerRPCFunction();
```


Multicast RPC 는 서버에서 호출된 다음 서버는 물론 현재 연결된 모든 클라이언트에서도 실행되도록 고안. 멀티캐스트 함수를 선언하려면 NetMulticast 키워드를 사용한다(멀티캐스트 RPC 는 클라이언트에서도 호출 가능하지만, 이 경우 로컬에서만 실행됩니다).
```C++
UFUNCTION( NetMulticast ) // 서버와 연결된 모든 클라이언트에서 실행
void MulticastRPCFunction();
```





### RPC Server
```C++
// Header
	/** Fires a projectile. */
	void OnFire();

	// 클라이언트에서 서버로 함수를 호출하기 위한 선언
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_OnFire(FVector Location, FRotator Rotation);
	// Server_OnFire를 클라이언트에서 호출할 경우 다음 두 함수가 호출
	bool Server_OnFire_Validate(FVector Location, FRotator Rotation); // true를 반환할 경우 서버의 implementaion함수를 호출한다, false를 반환할 경우 클라이언트와의 접속을 끊는다(유저를 추방하는 용도로 사용가능)
	// 서버에서 불러질 함수 구현부, Server_OnFire를 호출하면 아래 함수가 실행된다
	void Server_OnFire_Implementation(FVector Location, FRotator Rotation);
```

```C++
// CPP

// 마우스 왼쪽을 클릭했을때 실행되는 총알 생성 함수
void AMultiplayerRNDCharacter::OnFire()
{
	//UE_LOG(LogTemp, Warning, TEXT("Firing"));
	// try and fire a projectile
	if (ProjectileClass != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			if (bUsingMotionControllers)
			{
				const FRotator SpawnRotation = VR_MuzzleLocation->GetComponentRotation();
				const FVector SpawnLocation = VR_MuzzleLocation->GetComponentLocation();
				World->SpawnActor<AMultiplayerRNDProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);
			}
			else
			{
				const FRotator SpawnRotation = GetControlRotation();
				// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
				const FVector SpawnLocation = ((FP_MuzzleLocation != nullptr) ? FP_MuzzleLocation->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);

				// 스폰 콜리젼 핸들링 변수 선언 및 할당
				FActorSpawnParameters ActorSpawnParams;

				// 생성한 총알의 오너를 총알을 생성한 플레이어로 설정
				ActorSpawnParams.Owner = this;

				ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
				// 프로젝타일 오브젝트 스폰
				World->SpawnActor<AMultiplayerRNDProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);

				// 서버가 아니라 클라이언트일 경우에 RPC 함수를 호출한다
                // 함수를 호출할 객체(자신)가 서버가 아니라면
				if (!HasAuthority()) 
                //if (!GetWorld()->IsServer()) 다음과 같이도 선언 가능
				//if (GetLocalRole() < ROLE_Authority) 다음과 같이도 선언 가능
				{
					// 클라이언트에서 실행(총알을 쏜 유저가 클라이언트라면)
					// 서버에서 MUlticast함수를 호출하도록 한다
					Server_OnFire(SpawnLocation, SpawnRotation);
				}
				else
				{
					// 서버에서 실행(총알을 쏜 유저가 서버라면)
                    // 멀티캐스트로 서버에 연결된 모든 클라이언트 유저들에게도 서버 유저가 총알을 쏘도록 함수 호출
					Multi_OnFire(SpawnLocation, SpawnRotation);
				}
			}
		}
	}

	// try and play the sound if specified
	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	// try and play a firing animation if specified
	if (FireAnimation != nullptr)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
		if (AnimInstance != nullptr)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}
}



// 서버 통신을 확인하기 위한 함수
bool AMultiplayerRNDCharacter::Server_OnFire_Validate(FVector Location, FRotator Rotation)
{
	return true;
}

// 서버에서 불러와질 함수
void AMultiplayerRNDCharacter::Server_OnFire_Implementation(FVector Location, FRotator Rotation)
{
	// 클라이언트에서 호출하는 함수 (클라이언트 -> 서버로 전달)
	Multi_OnFire(Location, Rotation); // 서버에서 Multicast를 실행하여 서버에 연결된 모든 클라이언트에서도 해당 유정가 총알을 발사하도록 한다
}
```


### RPC Multicast   
```C++
// Header
// 클라이언트 유저가 총을 발사했을때 다른 모든 클라이언트에서 해당 함수가 실행될 수 있도록 서버에서 호출될 멀티캐스트 함수
UFUNCTION(NetMulticast, Reliable, WithValidation)
void Multi_OnFire(FVector Location, FRotator Rotation);
bool Multi_OnFire_Validate(FVector Location, FRotator Rotation);
void Multi_OnFire_Implementation(FVector Location, FRotator Rotation);
```

```C++
/// CPP
// 서버 통신을 확인하기 위한 함수
bool AMultiplayerRNDCharacter::Multi_OnFire_Validate(FVector Location, FRotator Rotation)
{
	return true;
}

// 서버에서 모든 클라이언트 유저에게 호출하는 함수
void AMultiplayerRNDCharacter::Multi_OnFire_Implementation(FVector Location, FRotator Rotation)
{
	// 서버에서 보내진 신호를 받으면(네트워크로에서 호출된 신호라면) 아래 코드를 실행한다
    // 자신이 호출한 함수라면 이미 총알을 생성했으므로 실행하지 않는다
	if (!IsLocallyControlled())
	{
		// 스폰 콜리젼 핸들링 변수 선언 및 할당
		FActorSpawnParameters ActorSpawnParams;
		// 클라이언트에서 총알을 생성할때 생성한 플레이어를 Owner로 설정한다
		if (HasAuthority())
		{
			ActorSpawnParams.Owner = this;
		}

		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

		// 프로젝타일 오브젝트 스폰
		GetWorld()->SpawnActor<AMultiplayerRNDProjectile>(ProjectileClass, Location, Rotation, ActorSpawnParams);

		// try and play the sound if specified
		// 서버와 모든 클라이언트가 총성을 발생
		if (FireSound != nullptr)
		{
			UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
		}

		// 서버와 모든 클라이언트에서 애니메이션 실행
		if (FireAnimation != nullptr)
		{
			// Get the animation object for the arms mesh
			UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
			if (AnimInstance != nullptr)
			{
				AnimInstance->Montage_Play(FireAnimation, 1.f);
			}
		}
	}	
}
```


<br>

