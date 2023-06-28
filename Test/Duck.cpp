//======================================================================================
// ���O�FDuck.h
// �����F�A�q���̃w�b�_�[�t�@�C��
//======================================================================================

//------------------------------------
//		include
//------------------------------------

#include "Duck.h"

extern DWORD gDeltaTime;

//------------------------------------
//		�����o�[�֐�
//------------------------------------

//<><><><><><><><><><><><><><><><><><>
// �֐����FMove
// �����FDUCK_MOVE��Ԃ̏���
//<><><><><><><><><><><><><><><><><><>
void Duck::Move(void)// �����͌��Ƃقړ���
{
	// ���Ԍv�Z
	mTime += gDeltaTime;
	// ���x�ݒ�
	float Speed = 0.0004f;
	// 15�`20�b�Ɉ��,�p�x�̌v�Z����
	if (mTime >= ((float)(rand() % 5) + 15.0f) * 1000.0f)
	{
		mAngle = ((float)(rand() % 2001 - 1000) / 1000.0f) * PI;
		mTime = 0.0f;
	}

	// �ʒu���X�V
	mAnimObject->mCenter.x += (mResistance.x + Speed * sinf(mAngle))* gDeltaTime;
	mAnimObject->mCenter.y += (mResistance.y + Speed * cosf(mAngle))* gDeltaTime;
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
// �֐����FConfusion
// �����FDUCK_CONFUSION�̏���
//<><><><><><><><><><><><><><><><><><>
void Duck::Confusion(void)
{
	// ���Ԍv�Z
	mTime += gDeltaTime;
	// 5�`10�b�o�߂���Ɩ߂�
	if (mTime >= ((float)(rand() % 5) + 5.0f) * 1000.0f)
	{
		ChangeState(DUCK_MOVE);
		mTime = 0.0f;
	}
}

//<><><><><><><><><><><><><><><><><><>
// �֐����FDuck
// �����F�R���X�g���N�^
//<><><><><><><><><><><><><><><><><><>
Duck::Duck(XMFLOAT3 & _Camera) :AnimObject(_Camera)
{

	LoadTexture(L"assets/images/Character/Duck/ChickRobot.png", &mDuckTex);
	mAnimObject->SetTexture(mDuckTex);
	mAnimObject->mCenter.x = 0.5f;// �ʒuX
	mAnimObject->mCenter.y = 0.5f;// �ʒuY
	mAnimObject->mSize.x = 0.5f;// �T�C�YX
	mAnimObject->mSize.y = 0.5f;// �T�C�YY
	mAnimObject->fAnimSpeed = 0.002f;// �A�j���[�V�������x
	mAngle = PI*-1.0f;
	mTime = 0.0f;
	mState = DUCK_MOVE;// ��Ԑݒ�
	
	mResistance = { 0.0f,0.0f };
	// �����蔻��
	mCircle = new HitCircle(&mAnimObject->mCenter, 0.15f);// �̂̓����蔻��

	Sound_Init(SOUND_LABEL_SE013);
	Play(SOUND_LABEL_SE013);
	SetVolume(SOUND_LABEL_SE013, 5.5f);
	
}

//<><><><><><><><><><><><><><><><><><>
// �֐����F~Duck
// �����F�f�X�g���N�^
//<><><><><><><><><><><><><><><><><><>
Duck::~Duck()
{
	Sound_Uninit(SOUND_LABEL_SE013);
	delete mCircle;
	COM_SAFE_RELEASE(mDuckTex);
}

//<><><><><><><><><><><><><><><><><><>
// �֐����FUpdate
// �����F�X�V����
//<><><><><><><><><><><><><><><><><><>
void Duck::Update()
{
	if (GetSoundState(SOUND_LABEL_SE013) == FALSE) {
		Play(SOUND_LABEL_SE013);
		SetVolume(SOUND_LABEL_SE013, 5.5f);
	}

	switch(mState)
	{
	case DUCK_CARRY:// MOVE�Ɠ��������ŏ�Ԃ����Ⴄ
	case DUCK_MOVE:
		Move();
		break;
	case DUCK_CONFUSION:
		Confusion();
		break;
	}
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

	// ��R�͂̏�����
	mResistance.x = 0.0f;
	mResistance.y = 0.0f;
	GameObject::Update();
}

//<><><><><><><><><><><><><><><><><><>
// �֐����FSetResistance
// �����F��R�͂̌v�Z
//<><><><><><><><><><><><><><><><><><>
void Duck::SetResistance(XMFLOAT2 _pos)
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
// �����F��ԕύX
//<><><><><><><><><><><><><><><><><><>
void Duck::ChangeState(DuckStateID _state)
{
	mState = _state;
	switch (mState)
	{
	case DUCK_CARRY:
		mTime = 0.0f;
		break;
	case DUCK_MOVE:
		mTime = 0.0f;
		break;
	case DUCK_CONFUSION:
		mTime = 0.0f;
		break;
	}
}
