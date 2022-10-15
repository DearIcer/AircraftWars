// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShip.h"
#include<particles/ParticleSystemComponent.h>
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include"Bullet.h"
#include "ammo.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include<Sound/SoundCue.h>
// Sets default values
ASpaceShip::ASpaceShip()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	IsUpMove = true;
	IsRightMove = true;
	IsDead = false;

	Speed = 2000.0f;
	//开火间隔
	Time_BetweenShot = 0.2f;
	//实例化碰撞
	CollisionCom = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	RootComponent = CollisionCom;

	//飞机模型实例化
	ShipSM = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	ShipSM->SetupAttachment(CollisionCom);

	//实例化弹簧臂
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 1500.0f;
	SpringArmComp->bInheritPitch = false;
	SpringArmComp->bInheritRoll = false;
	SpringArmComp->bInheritYaw = false;
	//SpringArmComp->bUsePawnControlRotation = true;
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);
	CameraComp->SetProjectionMode(ECameraProjectionMode::Orthographic);
	CameraComp->SetOrthoWidth(4500.0f);

	//实例化子弹槽位
	SpawnPiont = CreateDefaultSubobject<USceneComponent>(TEXT("BulletRoot"));
	SpawnPiont->SetupAttachment(ShipSM);

	SpawnPiont2 = CreateDefaultSubobject<USceneComponent>(TEXT("BulletRoot2"));
	SpawnPiont2->SetupAttachment(ShipSM);

	//实例化粒子系统
	ParticleSystem= CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem"));
	ParticleSystem->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASpaceShip::BeginPlay()
{
	Super::BeginPlay();
	//获取到玩家
	PC = Cast<APlayerController>(GetController());
	//显示鼠标
	PC->bShowMouseCursor = true;
}

void ASpaceShip::LookAtCursor()
{
	FVector MouseLocation, MouseDirection;
	//将鼠标位置转换到世界坐标（参数鼠标的位置和方向）
	PC->DeprojectMousePositionToWorld(MouseLocation, MouseDirection);
	//转换成鼠标的目标位置（位置，方向，深度为0）
	FVector TargetLocation = FVector(MouseLocation.X, MouseLocation.Y, GetActorLocation().Z);
	//获取角色旋转的角度(起始位置，目标位置)Find a rotation for an object at Start location to point at Target location.
	//在"开始"位置处查找对象的旋转以指向目标位置。
	FRotator Rotator = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetLocation);
	//设置角色旋转
	SetActorRotation(Rotator);
}

void ASpaceShip::MoveUp(float Value)
{
	if (Value != 0)
	{
		IsUpMove = true;
	}
	else
	{
		IsUpMove = false;
	}
	AddMovementInput(FVector::ForwardVector, Value);
}

void ASpaceShip::MoveRight(float Value)
{
	if (Value != 0)
	{
		IsRightMove = true;
	}
	else
	{
		IsRightMove = false;
	}
	AddMovementInput(FVector::RightVector, Value);
}

void ASpaceShip::Move()
{
	//添加角色移动(移动位置，获取当前角色输入向量乘以速度再乘以帧时间得到移动的方向和速度，最后开启碰撞)
	AddActorWorldOffset(ConsumeMovementInputVector() * Speed * FApp::GetDeltaTime(), true);
}

void ASpaceShip::Fire()
{
	//判断对象是否存在，执行开火
	if (Bullet != nullptr)
	{
		FActorSpawnParameters SpawnParameters;
		GetWorld()->SpawnActor<ABullet>(Bullet, SpawnPiont->GetComponentLocation(), SpawnPiont->GetComponentRotation(), SpawnParameters);
		GetWorld()->SpawnActor<ABullet>(Bullet, SpawnPiont2->GetComponentLocation(), SpawnPiont2->GetComponentRotation(), SpawnParameters);
		//播放声音
		//UGameplayStatics::PlaySoundAtLocation(this, ShootCue, GetActorLocation());
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Fire"));
		if (FireSound != nullptr)
		{
			UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
		}
	}
}

void ASpaceShip::StarFire()
{
	//设置定时器调用开火
	GetWorldTimerManager().SetTimer(TimerHandle_BetweenShot, this, &ASpaceShip::Fire, Time_BetweenShot, true, 0.0f);

}

void ASpaceShip::EndFire()
{
	//清除定时器
	GetWorldTimerManager().ClearTimer(TimerHandle_BetweenShot);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("EndFire"));
}

// Called every frame
void ASpaceShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(!IsDead)
	{
		//如果角色没有移动 禁用粒子组件
		if (IsUpMove || IsRightMove)
		{
			//禁用粒子组件
			ParticleSystem->Activate();
		}
		else
		{
			//启用粒子组件
			ParticleSystem->Deactivate();
		}
		Move();
		LookAtCursor();
	}
	else
	{
		//禁用粒子组件
		ParticleSystem->Activate();
	}
}

// Called to bind functionality to input
void ASpaceShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//绑定输入,轴映射
	PlayerInputComponent->BindAxis("MoveUp", this, &ASpaceShip::MoveUp);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASpaceShip::MoveRight);
	//开火绑定
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ASpaceShip::StarFire);//按下持续开火
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &ASpaceShip::EndFire);//松开结束开火
}

