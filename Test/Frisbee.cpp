//======================================================================================
// ���O�FFrisbee.cpp
// �����F�t���X�r�[�̃\�[�X�t�@�C��
//======================================================================================

#include "Frisbee.h"

extern DWORD gDeltaTime;

//<><><><><><><><><><><><><><><><><><>
// �֐����FFrisbee
// �����F�R���X�g���N�^
//<><><><><><><><><><><><><><><><><><>
Frisbee::Frisbee(XMFLOAT3 &_Camera) :StaticObject(_Camera)
{
	//LoadTexture(L"assets/Frisbee_test.png", &mTexture);
	LoadTexture(L"assets/images/Item/Frisbee.png", &mTexture);
	mSprite->SetTexture(mTexture);
	mMiniSize = 0.07f;
	mSprite->mSize.x = mMiniSize;
	mSprite->mSize.y = mMiniSize;
	mRate = 1.0f;
	mSpeed = 0.0005f;
	mAngle = 0.0f;
	mState = FRISBEE_DROP;
	mHold = HOLD_PLAYER;
	active = false;

	mShadow = new StaticObject(_Camera);
	LoadTexture(L"assets/FrisbeeShadow_test.png", &mShadowTexture);
	mShadow->mSprite->SetTexture(mShadowTexture);
	//mShadow->mSprite->mSize.x = mMiniSize;
	//mShadow->mSprite->mSize.y = mMiniSize;
	mShadow->mSprite->mSize.x = mMiniSize + 0.01f;
	mShadow->mSprite->mSize.y = mMiniSize - 0.03f;
	mShadow->active = false;

	mCircle = new HitCircle(&this->mSprite->mCenter);
	mCircle->mRadius = 0.05f;

	Sound_Init(SOUND_LABEL_SE018);

	//SetVolume(SOUND_LABEL_SE018, 1.0f);
}

//<><><><><><><><><><><><><><><><><><>
// �֐����F~Frisbee
// �����F�f�X�g���N�^
//<><><><><><><><><><><><><><><><><><>
Frisbee::~Frisbee()
{
	Sound_Uninit(SOUND_LABEL_SE018);

	delete mCircle;
	COM_SAFE_RELEASE(mShadowTexture);
	delete mShadow;
	COM_SAFE_RELEASE(mTexture);
}


//<><><><><><><><><><><><><><><><><><>
// �֐����FSetReserve
// �����F�����鏀���̏���
//<><><><><><><><><><><><><><><><><><>
void Frisbee::SetReserve(XMFLOAT2 _pos , float _ang)
{
	this->mSprite->mCenter = _pos;
	mAngle = _ang;
	mRate = 1.0f;
	//�t���X�r�[�̏�Ԃ�ς���
	ChangeState(FRISBEE_FRY);
}

//<><><><><><><><><><><><><><><><><><>
// �֐����FFry
// �����F������ꂽ���̏���
//<><><><><><><><><><><><><><><><><><>
void Frisbee::Fry()
{
	if (GetSoundState(SOUND_LABEL_SE018) == FALSE) {
		Play(SOUND_LABEL_SE018);
	}

	float LT = (float)Input_GetLTButton() / 255.0f;
	float RT = (float)Input_GetRTButton() / 255.0f;
	if (LT + RT == 0)
	{
		RT = Input_GetKeyDown(VK_RBUTTON);
		LT = Input_GetKeyDown(VK_LBUTTON);
	}
	// �i�s������ς���
	float turnRate = 500.0f;
	mAngle -= ( LT / turnRate) * gDeltaTime;
	mAngle += ( RT / turnRate) * gDeltaTime;

	// �X�s�[�h�𗎂Ƃ�
	float normal = 0.0001f;//������
	float deceleration = 0.00005f;//�{�^�������������̌�����
	mRate -= LT * deceleration * gDeltaTime;
	mRate -= RT * deceleration * gDeltaTime;
	mRate -= normal*gDeltaTime;

	// �X�s�[�h���}�C�i�X�ɂȂ�Ȃ��悤��������
	mRate = (mRate <= 0 ? 0 : mRate);

	// �ʒu�̍X�V
	this->mSprite->mCenter.x += mSpeed * mRate * sinf(mAngle) *gDeltaTime;
	this->mSprite->mCenter.y += mSpeed * mRate * cosf(mAngle) *gDeltaTime;

	//�ړ�����
	// X�͈̔͐���
	if(mSprite->mCenter.x < -2.2f)// -2.27f�ȉ��ɂȂ�Ȃ��悤�ɂ���
	{
		mRate -= normal * 2.0f * gDeltaTime;
		mSprite->mCenter.x = -2.2f;
	}
	if(mSprite->mCenter.x > 2.2f)//  2.27f�ȏ�ɂȂ�Ȃ��悤�ɂ���
	{
		mRate -= normal * 2.0f * gDeltaTime;
		mSprite->mCenter.x = 2.2f;
	}
	// Y�͈̔͐���
	if (mSprite->mCenter.y < -1.9f)// -1.9f�ȉ��ɂȂ�Ȃ��悤�ɂ���
	{
		mRate -= normal * 2.0f * gDeltaTime;
		mSprite->mCenter.y = -1.9f;
	}
	if (mSprite->mCenter.y > 1.9f)//  1.9f�ȏ�ɂȂ�Ȃ��悤�ɂ���
	{
		mRate -= normal * 2.0f * gDeltaTime;
		mSprite->mCenter.y = 1.9f;
	}

	// �T�C�Y��ς���
	mSprite->mSize.x = mMiniSize + mRate/25;
	mSprite->mSize.y = mMiniSize + mRate/25;

	// �e�̈ʒu
	mShadow->mSprite->mCenter.x = this->mSprite->mCenter.x - (mRate/10) * sinf(0.0f);
	mShadow->mSprite->mCenter.y = this->mSprite->mCenter.y - (mRate/10) * cosf(0.0f);

	// DROP�ɑJ�ڂ���
	if (mRate <= 0)// �X�s�[�h�������Ȃ�����
	{
		ChangeState(FRISBEE_DROP);
	}
	
}

//<><><><><><><><><><><><><><><><><><>
// �֐����FDrop
// �����F���������̏���
//<><><><><><><><><><><><><><><><><><>
void Frisbee::Drop()
{
	/*----- ���ɂ�邱�ƂȂ� -----*/
	//if(Input_GetButtonTrigger(X))//�f�o�b�N�p
	//{
	//	mShadow->active = true;
	//	mSprite->mCenter.x = 0.0f;
	//	mSprite->mCenter.y = 0.0f;
	//	mAngle = 0.0f;
	//	mSpeed = 0.0005f;
	//	mState = FRISBEE_FRY;
	//}
}

//<><><><><><><><><><><><><><><><><><>
// �֐����FUpdate
// �����F�X�V����
//<><><><><><><><><><><><><><><><><><>
void Frisbee::Update()
{
	switch(mState)
	{
	case FRISBEE_DROP:
		Drop();
		break;
	case FRISBEE_FRY:
		Fry();
		break;
	case FRISBEE_HOLD:
		break;
	}
	mShadow->Update();
	//�e�N���X�Ő錾����Update�֐������s����
	GameObject::Update();
}

//<><><><><><><><><><><><><><><><><><>
// �֐����FChangeState
// �����F��Ԑݒ�
//<><><><><><><><><><><><><><><><><><>
void Frisbee::ChangeState(FrisbeeStateID _state)
{
	mState = _state;

	switch (_state)
	{
	case FRISBEE_DROP:
		Stop(SOUND_LABEL_SE018);
		SetVolume(SOUND_LABEL_SE018, 1.0f);
		mSound = false;
		mRate = 0;
		mSprite->mSize.x = mMiniSize + mRate / 25;
		mSprite->mSize.y = mMiniSize + mRate / 25;
		active = true;
		mShadow->active = false;
		Catch(DONT_HOLD);
		break;
	case FRISBEE_FRY:
		if (mSound == false)
		{
			Play(SOUND_LABEL_SE018);
			SetVolume(SOUND_LABEL_SE018, 1.0f);
			mSound = true;
		}
		active = true;
		mShadow->active = true;
		Catch(DONT_HOLD);
		break;
	case FRISBEE_HOLD:
		Stop(SOUND_LABEL_SE018);
		SetVolume(SOUND_LABEL_SE018, 1.0f);
		mSound = false;
		active = false;
		mShadow->active = false;
		break;
	}
}

//<><><><><><><><><><><><><><><><><><>
// �֐����FChangeState
// �����F��Ԑݒ�
//<><><><><><><><><><><><><><><><><><>
void Frisbee::Catch(CharHoldFrisbee _catch)
{
	mHold = _catch;
}

//======================================================================================
// �S���ҁF		���쒼�o
// �`�[�����F	����	
//======================================================================================
