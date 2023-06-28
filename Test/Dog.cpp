//======================================================================================
// ���O�FDog.cpp
// �����F���̃\�|�X�t�@�C��
//======================================================================================

//------------------------------------
//		include
//------------------------------------

#include "Dog.h"

extern DWORD gDeltaTime;

//------------------------------------
//		�����o�[�֐�
//------------------------------------

//<><><><><><><><><><><><><><><><><><>
// �֐����FWalk
// �����F�ʏ��ԏ���
//<><><><><><><><><><><><><><><><><><>
void Dog::Walk(void)
{
	// ���Ԍv�Z
	mTime += gDeltaTime;
	
	// ���x�ݒ�
	float Speed = 0.0001f;
	float SlipSpeed = 0.0f;
	
	// ���鏈��
	if (mSlip == true)
	{
		//mOldAngle = (mAngle+mOldAngle)/2;
		//SlipSpeed = Speed * 0.5f;
		mSpeedSlip.x += Speed * sinf(mAngle) * 0.005f;
		mSpeedSlip.y += Speed * cosf(mAngle) * 0.005f;
		// ����ő呬�x
		float MaxSlip = 0.001f;
		mSpeedSlip.x = (mSpeedSlip.x > MaxSlip ? MaxSlip : mSpeedSlip.x);
		mSpeedSlip.x = (mSpeedSlip.x < -MaxSlip ? -MaxSlip : mSpeedSlip.x);
		mSpeedSlip.y = (mSpeedSlip.y > MaxSlip ? MaxSlip : mSpeedSlip.y);
		mSpeedSlip.y = (mSpeedSlip.y < -MaxSlip ? -MaxSlip : mSpeedSlip.y);
	}
	else
	{
		mSpeedSlip.x = 0.0f;
		mSpeedSlip.y = 0.0f;
	}
	//mAngle = atan2f(mNextPos.x, mNextPos.y);
	// 15�`20�b�Ɉ��,�p�x�̌v�Z����
	if (mTime >= ((float)(rand() % 5) + 15.0f) * 1000.0f)
	{
		mAngle = ((float)(rand() % 2001 - 1000) / 1000.0f) * PI;
		mTime = 0.0f;
	}

	// �ʒu���X�V
	mAnimObject->mCenter.x += (mResistance.x + Speed * sinf(mAngle) + SlipSpeed * sinf(mOldAngle)) * gDeltaTime;
	mAnimObject->mCenter.y += (mResistance.y + Speed * cosf(mAngle) + SlipSpeed * cosf(mOldAngle)) * gDeltaTime;
	// �L�����̌�����ݒ肷��
	float X = sinf(mAngle);
	float Y = cosf(mAngle);

	if (X * X <= Y * Y)//�c
	{
		if (Y <= 0)// ��
		{
			mAnimObject->mDirection = D_DOWN;
		}
		else// ��
		{
			mAnimObject->mDirection = D_RIGHT;// D_UP�ł͂Ȃ�D_RIGHT�������
		}
	}
	else // ��
	{
		if (X <= 0)// ��
		{
			mAnimObject->mDirection = D_LEFT;
		}
		else// �E
		{
			mAnimObject->mDirection = D_UP;// D_RIGHT�ł͂Ȃ�D_UP���E����
		}
	}
		
}

//<><><><><><><><><><><><><><><><><><>
// �֐����FRun
// �����F�t���X�r�[��ǂ��������ԏ���
//<><><><><><><><><><><><><><><><><><>
void Dog::Run(void)
{
	mWaitTime -= gDeltaTime;
	// ���x�ݒ�
	float Speed = 0.0005f;
	//float SlipSpeed = 0.0f;
	// ���鏈��
	if (mSlip == true)
	{
		
		//SlipSpeed = Speed * 0.5f;
		mSpeedSlip.x += Speed * sinf(mAngle) * 0.005f;
		mSpeedSlip.y += Speed * cosf(mAngle) * 0.005f;
		// ����ő呬�x
		float MaxSlip = 0.001f;
		mSpeedSlip.x = (mSpeedSlip.x > MaxSlip ? MaxSlip : mSpeedSlip.x);
		mSpeedSlip.x = (mSpeedSlip.x < -MaxSlip ? -MaxSlip : mSpeedSlip.x);
		mSpeedSlip.y = (mSpeedSlip.y > MaxSlip ? MaxSlip : mSpeedSlip.y);
		mSpeedSlip.y = (mSpeedSlip.y < -MaxSlip ? -MaxSlip : mSpeedSlip.y);
	}
	else
	{
		mSpeedSlip.x = 0.0f;
		mSpeedSlip.y = 0.0f;
	}
	// �p�x�̌v�Z����
	float X = mTarget->x - mAnimObject->mCenter.x ;
	float Y = mTarget->y - mAnimObject->mCenter.y ;
	
	mAngle = atan2f(X, Y);
	
	// �ʒu���X�V
	if (mWaitTime <= 0)
	{
		mAnimObject->mCenter.x += (mResistance.x + Speed * sinf(mAngle) + mSpeedSlip.x) * gDeltaTime;
		mAnimObject->mCenter.y += (mResistance.y + Speed * cosf(mAngle) + mSpeedSlip.y) * gDeltaTime;
	}
	
	
	// �L�����̌�����ݒ肷��
	X = sinf(mAngle);
	Y = cosf(mAngle);
	if (X * X <= Y * Y)//�c
	{
		if (Y <= 0)// ��
		{
			mAnimObject->mDirection = D_DOWN;
		}
		else// ��
		{
			mAnimObject->mDirection = D_RIGHT;// D_UP�ł͂Ȃ�D_RIGHT�������
		}
	}
	else // ��
	{
		if (X <= 0)// ��
		{
			mAnimObject->mDirection = D_LEFT;
		}
		else// �E
		{
			mAnimObject->mDirection = D_UP;// D_RIGHT�ł͂Ȃ�D_UP���E����
		}
	}
	mOldAngle = mAngle;
}


//<><><><><><><><><><><><><><><><><><>
// �֐����FBeCarryed
// �����F�����^�΂�鏈��
//<><><><><><><><><><><><><><><><><><>
void Dog::BeCarryed(void)
{
	mAnimObject->fAnimCnt = 2.0f;//�A�j���[�V�������~�߂�
	// �Y��
	XMFLOAT2 offset;
	offset = {0.0f,0.22f};
	// �ʒu�X�V
	mAnimObject->mCenter.x = mTarget->x + offset.x;
	mAnimObject->mCenter.y = mTarget->y + offset.y;
}


//<><><><><><><><><><><><><><><><><><>
// �֐����FDog
// �����F�R���X�g���N�^
//<><><><><><><><><><><><><><><><><><>
Dog::Dog(XMFLOAT3 & _Camera):AnimObject(_Camera)
{
	LoadTexture(L"assets/images/Character/Dog/Dog.png", &mWalkTexture);
	LoadTexture(L"assets/images/Character/Dog/Run_dog.png", &mRunTexture);
	mAnimObject->SetTexture(mWalkTexture);
	mAnimObject->mSize.x = 0.2f;// �T�C�YX
	mAnimObject->mSize.y = 0.2f;// �T�C�YY
	mAnimObject->fAnimSpeed = 0.002f;// �A�j���[�V�������x
	mAngle = PI;
	mTime = 0.0f;
	mState = DOG_WALK;// ��Ԑݒ�
	mWaitTime = 0.0f;
	mResistance = { 0.0f,0.0f };
	// �����蔻��
	mCircle = new HitCircle(&mAnimObject->mCenter, 0.05f);// �̂̓����蔻��
	mCatchArea = new HitCircle(&mAnimObject->mCenter, 0.09f);// �L���b�`�ł��邠���蔻��
	mMissArea = new HitCircle(&mAnimObject->mCenter, 0.15f);// ���s���邠���蔻��
	mCatchBubbleArea = new HitCircle(&mAnimObject->mCenter, 0.25f);// �L���b�`�������̖A�����蔻��

	Sound_Init(SOUND_LABEL_SE010);
}

//<><><><><><><><><><><><><><><><><><>
// �֐����F~Dog
// �����F�f�X�g���N�^
//<><><><><><><><><><><><><><><><><><>
Dog::~Dog()
{
	Sound_Uninit(SOUND_LABEL_SE010);
	delete mCatchBubbleArea;
	delete mMissArea;
	delete mCatchArea;
	delete mCircle;
	COM_SAFE_RELEASE(mRunTexture);
	COM_SAFE_RELEASE(mWalkTexture);
}

//<><><><><><><><><><><><><><><><><><>
// �֐����FUpdate
// �����F�X�V����
//<><><><><><><><><><><><><><><><><><>
void Dog::Update()
{
	if (Fade_Bubble::mState == FADE_IN_END || Fade_Bubble::mState == NONE_FADE) {
		switch (mState)// ��Ԃ��Ƃ̏���
		{
		case DOG_WALK:
			Walk();
			break;
		case DOG_RUN:
			Run();
			break;
		case DOG_WAIT:
			break;
		case DOG_RETURN:
			Run();
			break;
		case DOG_BE_CARRYED:
			BeCarryed();
			break;
		}
		mSlip = false;// ����t���O�̃��Z�b�g
		//�L�����̈ړ�����
		// X�͈̔͐���
		if (mAnimObject->mCenter.x < -2.2f)
		{
			mAnimObject->mCenter.x = -2.2f;
			mAngle = ((float)(rand() % 1001) / 1000.0f) * PI;
		}
		if (mAnimObject->mCenter.x > 2.2f)
		{
			mAnimObject->mCenter.x = 2.2f;
			mAngle = ((float)(rand() % 1001) / 1000.0f) * -1.0f * PI;
		}
		// Y�͈̔͐���
		if (mAnimObject->mCenter.y < -1.9f)
		{
			mAnimObject->mCenter.y = -1.9f;
			mAngle = (((float)(rand() % 1001) / 1000.0f) - 0.5f) * PI;
		}
		if (mAnimObject->mCenter.y > 1.9f)
		{
			mAnimObject->mCenter.y = 1.9f;
			mAngle = (((float)(rand() % 1001) / 1000.0f) + 0.5f) * -1.0f * PI;
		}
	}

	// ��R�͂̏�����
	mResistance.x = 0.0f;
	mResistance.y = 0.0f;
	// ���N���X�̍X�V����
	GameObject::Update();
}
////
////bool Dog::CatchResult(HitCircle* _circle)
////{
////	if(Input_GetButtonTrigger(B))
////	{
////		if (mCatchArea->CheckHit(_circle))
////		{
////			return true;
////		}
////		else
////		{
////			return false;
////		}
////	}
////	
////	return -1;
////}

//<><><><><><><><><><><><><><><><><><>
// �֐����FSetResistance
// �����F��R�͂̌v�Z
//<><><><><><><><><><><><><><><><><><>
void Dog::SetResistance(XMFLOAT2 _pos)
{
	XMFLOAT2 Distance;// �v���C���[�Ə�Q���̋���
	Distance.x = mAnimObject->mCenter.x - _pos.x;
	Distance.y = mAnimObject->mCenter.y - _pos.y;
	float square_root = sqrt(Distance.x * Distance.x + Distance.y * Distance.y);
	XMFLOAT2 Vector;
	Vector.x = (Distance.x / square_root) * 0.0008f;
	Vector.y = (Distance.y / square_root) * 0.0008f;

	mResistance = Vector;
}

//<><><><><><><><><><><><><><><><><><>
// �֐����FChangeState
// �����F���̏�Ԃ�ς���
//<><><><><><><><><><><><><><><><><><>
void Dog::ChangeState(DogStateID _state)
{
	
	mState = _state;
	switch (_state)
	{
	case DOG_WALK:
		mAnimObject->SetTexture(mWalkTexture);// �e�N�X�`����ύX����
		mAnimObject->fAnimSpeed = 0.002f;// �A�j���[�V�������x
		mWaitTime = 0.0f;// ������
		break;
	case DOG_RUN:
		mAnimObject->SetTexture(mRunTexture);// �e�N�X�`����ύX����
		mAnimObject->fAnimSpeed = 0.006f;// �A�j���[�V�������x
		break;
	case DOG_WAIT:
		mWaitTime = 0.25f*1000.0f;
		break;
	case DOG_RETURN:
		mAnimObject->SetTexture(mRunTexture);// �e�N�X�`����ύX����
		mAnimObject->fAnimSpeed = 0.006f;// �A�j���[�V�������x
		break;
	}
}

//<><><><><><><><><><><><><><><><><><>
// �֐����FSetTarget
// �����F�ǂ������鑊���ݒ肷��
//<><><><><><><><><><><><><><><><><><>
void Dog::SetTarget(XMFLOAT2* _target)
{
	mTarget = _target;// �l�ł͂Ȃ��A�h���X������Ă���
	ChangeState(DOG_RUN);
}

//======================================================================================
// �S���ҁF		���쒼�o
// �`�[�����F	����	
//======================================================================================