#include "PlayerAnimator.h"

#include "../Managers/InputManager.h"
#include "../Managers/ResourceManager.h"
#include "../Managers/Factory.h"

#include "Physics.h"

#include "../Enums.h"
#include "../Actors/APlayerBullet.h"

class Component;

PlayerAnimator::PlayerAnimator(AActor* InOwner)
	: Animator(InOwner)
{
	AddAnimation(
		static_cast<int>(EPlayerState::Idle),
		new FAnimation(
			ResourceManager::GetInstance().GetImage(EPlayerState::Idle),
			10, 15.0f, true
		)
	);

	AddAnimation(
		static_cast<int>(EPlayerState::Move),
		new FAnimation(
			ResourceManager::GetInstance().GetImage(EPlayerState::Move),
			10, 20.0f, true
		)
	);

	AddAnimation(
		static_cast<int>(EPlayerState::Jump),
		new FAnimation(
			ResourceManager::GetInstance().GetImage(EPlayerState::Jump),
			3, 10.0f, true
		)
	);

	AddAnimation(
		static_cast<int>(EPlayerState::Fall),
		new FAnimation(
			ResourceManager::GetInstance().GetImage(EPlayerState::Fall),
			3, 10.0f, true
		)
	);

	AddAnimation(
		static_cast<int>(EPlayerState::Crouch),
		new FAnimation(
			ResourceManager::GetInstance().GetImage(EPlayerState::Crouch),
			1, 100.0f, true
		)
	);

	AddAnimation(
		static_cast<int>(EPlayerState::Dash),
		new FAnimation(
			ResourceManager::GetInstance().GetImage(EPlayerState::Dash),
			12, 40.0f, false
		)
	);

	AddAnimation(
		static_cast<int>(EPlayerState::Attack1),
		new FAnimation(
			ResourceManager::GetInstance().GetImage(EPlayerState::Attack1),
			4, 20.0f, false
		)
	);

	AddAnimation(
		static_cast<int>(EPlayerState::Attack2),
		new FAnimation(
			ResourceManager::GetInstance().GetImage(EPlayerState::Attack2),
			6, 20.0f, false
		)
	);

	AddAnimation(
		static_cast<int>(EPlayerState::Shoot),
		new FAnimation(
			ResourceManager::GetInstance().GetImage(EPlayerState::Shoot),
			6, 100.0f, false
		)
	);

	AddAnimation(
		static_cast<int>(EPlayerState::Hit),
		new FAnimation(
			ResourceManager::GetInstance().GetImage(EPlayerState::Hit),
			1, 1.0f, false
		)
	);

	AddAnimation(
		static_cast<int>(EPlayerState::Death),
		new FAnimation(
			ResourceManager::GetInstance().GetImage(EPlayerState::Death),
			10, 30.0f, false
		)
	);

	PlayAnimation(static_cast<int>(EPlayerState::Idle));
}

PlayerAnimator::~PlayerAnimator()
{
	for(auto const& [key, val] : Animations)
	{
		delete val;
	}
}

void PlayerAnimator::OnTick(float DeltaTime)
{
	Animator::OnTick(DeltaTime);
	UpdateAnimation();
}

void PlayerAnimator::UpdateAnimation()
{
	APlayer* Player = static_cast<APlayer*>(Owner);
	if (!Player) return;

	Physics* MyPhysics = Player->GetComponent<Physics>();
	if (!MyPhysics) return;

	Gdiplus::PointF& Velocity = MyPhysics->GetVelocity();
	Gdiplus::PointF& Acceleration = MyPhysics->GetAcceleration();

	InputManager& IM = InputManager::GetInstance();

	if(State == EPlayerState::Death)
		return;

	if (State != EPlayerState::Hit && Player->WasJustHit())
	{
		SetState(EPlayerState::Hit);
		return;
	}
	if(State == EPlayerState::Hit)
	{
		if (bIsFinished)
		{
			if (Player->GetHealth() <= 0)
			{
				SetState(EPlayerState::Death);
			}
			else
			{
				SetState(EPlayerState::Idle);
				Player->SetState(EPlayerState::Idle);
			}
		}
		return;
	}

	if (IM.IsKeyPressed(EKey::EK_SHOOT) && !IsDashState() && !IsAttackState() && !IsShootState())
	{
		SetState(EPlayerState::Shoot);
		return;
	}
	if(State == EPlayerState::Shoot)
	{
		if (bIsFinished)
		{
			SetState(EPlayerState::Idle);
			Player->bCanShoot = true;
		}
		return;
	}

	Gdiplus::PointF AttackRangeOffset = { 30.0f, 40.0f };
	if(Player->GetLook() == ELook::Left)
		AttackRangeOffset.X *= -1;

	if (IM.IsKeyPressed(EKey::EK_ATTACK) && !IsDashState() && !IsShootState() && !IsAttackState())
	{
		SetState(EPlayerState::Attack1);
		APlayerBullet* AttackRange1 = Factory::GetInstance().SpawnActor<APlayerBullet>(EResourceID::None, ERenderLayer::Bullet);
		AttackRange1->SetPosition(Player->GetPosition().X + AttackRangeOffset.X, Player->GetPosition().Y + AttackRangeOffset.Y);
		AttackRange1->SetDirection({ 0, 0 });
		AttackRange1->GetComponent<CircleCollider>()->SetRadius(60.0f);
		AttackRange1->GetComponent<CircleCollider>()->SetLayer(EPhysicsLayer::PlayerBullet);
		AttackRange1->SetLifeTime(0.4f);
		return;
	}
	if(State == EPlayerState::Attack1)
	{
		if (bIsFinished)
		{
			if (IM.IsKeyPressed(EKey::EK_ATTACK))
			{
				SetState(EPlayerState::Attack2);
				APlayerBullet* AttackRange2 = Factory::GetInstance().SpawnActor<APlayerBullet>(EResourceID::None, ERenderLayer::Bullet);
				AttackRange2->SetPosition(Player->GetPosition().X + AttackRangeOffset.X, Player->GetPosition().Y + AttackRangeOffset.Y);
				AttackRange2->SetDirection({ 0, 0 });
				AttackRange2->GetComponent<CircleCollider>()->SetRadius(60.0f);
				AttackRange2->GetComponent<CircleCollider>()->SetLayer(EPhysicsLayer::PlayerBullet);
				AttackRange2->SetLifeTime(0.6f);
			}
			else
				SetState(EPlayerState::Idle);
		}
		return;
	}
	if (State == EPlayerState::Attack2)
	{
		if (bIsFinished)
		{
			if (IM.IsKeyPressed(EKey::EK_ATTACK))
				SetState(EPlayerState::Attack1);
			else
				SetState(EPlayerState::Idle);
		}
		return;
	}

	if(!Player->IsOnGround())
	{
		if (Velocity.Y > 0)
		{
			SetState(EPlayerState::Fall);
			return;
		}
		else if (Velocity.Y < 0)
		{
			SetState(EPlayerState::Jump);
			return;
		}
	}

	if (IM.IsKeyPressed(EKey::EK_DASH) && !IsDashState() && !IsShootState() && !IsAttackState())
	{
		SetState(EPlayerState::Dash);
		return;
	}
	if(State == EPlayerState::Dash)
	{
		if (bIsFinished)
		{
			SetState(EPlayerState::Idle);
			Player->bCanDash = true;
			Player->bIsDashing = false;
		}
		return;
	}
	else
	{
		Player->bCanDash = true;
		Player->bIsDashing = false;
	}

	if (IM.IsKeyPressed(EKey::EK_DOWN) &&
		(State == EPlayerState::Idle || State == EPlayerState::Move))
	{
		SetState(EPlayerState::Crouch);
	}
	if (State == EPlayerState::Crouch)
	{
		if (!IM.IsKeyPressed(EKey::EK_DOWN))
		{
			SetState(EPlayerState::Idle);
		}
		return;
	}

	if ((IM.IsKeyPressed(EKey::EK_LEFT) || IM.IsKeyPressed(EKey::EK_RIGHT)))
	{
		SetState(EPlayerState::Move);
		return;
	}

	SetState(EPlayerState::Idle);
}

void PlayerAnimator::SetState(EPlayerState InState)
{
	if(State == InState) return;
	State = InState;
	bIsFinished = false;
	CurrentAnimation = Animations[static_cast<int>(State)];
	CurrentFrameIndex = 0;
}