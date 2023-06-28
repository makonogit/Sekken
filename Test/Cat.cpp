#include "Cat.h"
#include "System.h"
#include <stdlib.h>

extern DWORD gDeltaTime;

//<><><><><><><><><><><><><><><><><><>
// �֐����FCat
// �����F�R���X�g���N�^
//<><><><><><><><><><><><><><><><><><>
Cat::Cat(XMFLOAT3 & _Camera):AnimObject(_Camera)
{
	//�e�N�X�`���ǂݍ���
	LoadTexture(L"assets/images/Character/Cat/Cat_Walk.png", &mCatTex);
	LoadTexture(L"assets/images/Character/Cat/Dirty_Cat.png", &mDirtCatTex);
	LoadTexture(L"assets/images/Character/Cat/LieDown.png", &mCatLieDownTex);
	LoadTexture(L"assets/images/Character/Cat/Cat_Jump.png", &mCatJampTex);

	//�A�j���[�V�������Ȃ���Ԃ̃I�u�W�F�N�g(�Q�]�ԁE�W�����v)
	mStaticObj = new StaticObject(_Camera);
	mStaticObj->mSprite->SetTexture(mCatLieDownTex);
	mStaticObj->SetSize(0.14f, 0.14f);
	mStaticObj->SetPosition(-1.0f, -1.0f);
	
	//�Q�]�񂾎��̓����蔻��
	mLieDownHit = new HitCircle(&mStaticObj->mSprite->mCenter, 0.1f);
	//mLieDownHit->active = false;

	//�ǂ������邠����
	mBlockAreaHit = new HitCircle(&mStaticObj->mSprite->mCenter, 0.05f);

	//�A�j���[�V��������I�u�W�F�N�g�̐ݒ�(�����E����)
	mAnimObject->SetTexture(mCatTex);
	mAnimObject->mSize.x = 0.14f;
	mAnimObject->mSize.y = 0.14f;
	mAnimObject->mCenter.x = -2.2f;
	mAnimObject->mCenter.y = 1.9f;

	fCatDownTime = 0.0f;
	fTarget = NULL;				//�ǂ�������Ώۂ���ɂ���
	nState = CatState::WALK;	//����
	nDirtState = CatDirtState::CLEARN;	//���ꂢ�ȏ��
	fAngle = PI;
	mHit->mRadius = 0.05f;
	Appearance = false;

	Sound_Init(SOUND_LABEL_SE011);
}

//<><><><><><><><><><><><><><><><><><>
// �֐����F~Cat
// �����F�f�X�g���N�^
//<><><><><><><><><><><><><><><><><><>
Cat::~Cat()
{
	Sound_Uninit(SOUND_LABEL_SE011);
	delete mLieDownHit;
	delete mBlockAreaHit;
	delete mStaticObj;

	COM_SAFE_RELEASE(mCatTex);
	COM_SAFE_RELEASE(mDirtCatTex);
	COM_SAFE_RELEASE(mCatLieDownTex);
	COM_SAFE_RELEASE(mCatJampTex);
}

//<><><><><><><><><><><><><><><><><><>
// �֐����FUpdate
// �����F�X�V
//<><><><><><><><><><><><><><><><><><>
void Cat::Update()
{
	if (Fade_Bubble::mState == FADE_IN_END || Fade_Bubble::mState == NONE_FADE) {
		
		fTime += gDeltaTime;		//���Ԃ̌v�Z
		fCatDownTime += gDeltaTime;	//�Q�]�Ԏ���

		//mAnimObject->Update();
		mStaticObj->Update();

		//����or�����Ă�ꍇ�͈ړ���������
		switch (nState) {
		case WALK:
			Move();
			break;
		case RUN:
			Move();
			break;
		case JUMP:
			Jump();
			break;
		case WAIT:
			Wait();
			break;
		case LIEDOWN:
			LieDown();
			break;
		default:
			break;
		}

		//15�b����20�b��1��Q�]��(�����Ă�Ƃ��͐Q�]�΂Ȃ�)
		if (fCatDownTime >= ((float)(rand() % 5) + 15.0f)* 1000.0f && nState != CatState::RUN && nState != CatState::WAIT) {

			nState = CatState::LIEDOWN;
			fCatDownTime = 0.0f;
		}

		//----------�ړ�����-------------

		if (mAnimObject->mCenter.x < -2.2f)
		{
			mAnimObject->mCenter.x = -2.2f;
			fAngle = ((float)(rand() % 1001) / 1000.0f) * PI;
		}
		if (mAnimObject->mCenter.x > 2.2f)
		{
			mAnimObject->mCenter.x = 2.2f;
			fAngle = ((float)(rand() % 1001) / 1000.0f) * -1.0f * PI;
		}

		if (mAnimObject->mCenter.y < -1.9f)
		{
			mAnimObject->mCenter.y = -1.9f;
			fAngle = (((float)(rand() % 1001) / 1000.0f) - 0.5f) * PI;
		}
		if (mAnimObject->mCenter.y > 1.9f)
		{
			mAnimObject->mCenter.y = 1.9f;
			fAngle = (((float)(rand() % 1001) / 1000.0f) + 0.5f) * -1.0f * PI;
		}

		mStaticObj->SetPosition(mAnimObject->mCenter.x, mAnimObject->mCenter.y);

	}

	GameObject::Update();
}

//<><><><><><><><><><><><><><><><><><>
// �֐����FDraw
// �����F�X�V
//<><><><><><><><><><><><><><><><><><>
void Cat::Draw()
{
	//�A�j���[�V�������邩���Ȃ���
	if (nState == CatState::WALK || nState == CatState::RUN || nState == CatState::CNONE) {
		mAnimObject->Draw();
	}
	if(nState == CatState::LIEDOWN || nState == CatState::JUMP || nState == CatState::WAIT) {
		mStaticObj->Draw();
	}
}

//<><><><><><><><><><><><><><><><><><>
// �֐����FMove
// �����F�ړ�
//<><><><><><><><><><><><><><><><><><>
void Cat::Move()
{
	if (nState == WALK) {
		fMoveSpeed = 0.0001f;	//�ړ��X�s�[�h
		mAnimObject->fAnimSpeed = 0.002f;
	}
	if (nState == RUN) {
		fMoveSpeed = 0.0004f;	//�ړ��X�s�[�h
		mAnimObject->fAnimSpeed = 0.006f;
	}
	

	//�ǂ�������Ώۂ������
	if (fTarget != NULL) {
		
		// �p�x�̌v�Z����
		float X = fTarget->x - mAnimObject->mCenter.x;
		float Y = fTarget->y - mAnimObject->mCenter.y;

		fAngle = atan2f(X, Y);
	}
	else {
		//10�b�u���Ɍ��������߂�
		if (fTime >= 10.0f * 1000.0f && nState != JUMP) {

			fAngle = ((float)(rand() % 2001 - 1000) / 1000.0f) * PI;
			fTime = 0.0f;
		}
	}

	//�ʒu�w��
	mAnimObject->mCenter.x += (fMoveSpeed * sinf(fAngle)) * gDeltaTime;
	mAnimObject->mCenter.y += (fMoveSpeed * cosf(fAngle)) * gDeltaTime;

	// �L�����̌�����ݒ肷��
	float X = sinf(fAngle);
	float Y = cosf(fAngle);

	if (X * X <= Y * Y)//�c
	{
		if (Y <= 0)// ��
		{
			mAnimObject->mDirection = D_DOWN;
		}
		else// ��
		{
			mAnimObject->mDirection = D_UP;
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
			mAnimObject->mDirection = D_RIGHT;
		}
	}
}

//<><><><><><><><><><><><><><><><><><>
// �֐����F�Q�]��
// �����F
//<><><><><><><><><><><><><><><><><><>
void Cat::LieDown()
{	
	nState = LIEDOWN;

	mLieDownHit->active = true;
	mStaticObj->mSprite->SetTexture(mCatLieDownTex);//�e�N�X�`�����w��

	fCatDownTime += gDeltaTime;
	
	//���Ԍo�߂ŕ��s�ɖ߂�(2�b)
	if (fCatDownTime >= 2.0f * 1000.0f) 
	{
		Stop(SOUND_LABEL_SE007);
		mLieDownHit->active = false;
		fCatDownTime = 0.0f;
		nState = WALK;
	}
}

//<><><><><><><><><><><><><><><><><><>
// �֐����F����
// �����F����
//<><><><><><><><><><><><><><><><><><>
void Cat::Run()
{
	//�摜�ς������J��

}

//<><><><><><><><><><><><><><><><><><>
// �֐����FJump
// �����F�W�����v
//<><><><><><><><><><><><><><><><><><>
void Cat::Jump()
{
	mStaticObj->mSprite->SetTexture(mCatJampTex);	//�e�N�X�`���̕ύX
	fMoveSpeed = 0.0005f;

	if (GetSoundState(SOUND_LABEL_SE011) == FALSE)
	{
		Play(SOUND_LABEL_SE011);
	}

	//�摜��ς���
	switch (mAnimObject->mDirection)
	{
	case D_LEFT:
		break;
	case D_RIGHT:
		break;
	case D_UP:
		break;
	case D_DOWN:
		break;
	default:
		break;
	}

	Move();

}

//<><><><><><><><><><><><><><><><><><>
// �֐����FWait
// �����F�Њd
//<><><><><><><><><><><><><><><><><><>
void Cat::Wait()
{
	//�e�N�X�`���̒���
	mStaticObj->mSprite->SetTexture(mCatLieDownTex);

	////nState = CatState::WAIT;
	//
	////�߂�����������ジ���肷��
	//fMoveSpeed = 0.00002f;

	//*mAnimObject->mCenter.x += (fMoveSpeed * fabsf(sinf(fAngle)) * gDeltaTime);
	//mAnimObject->mCenter.y += (fMoveSpeed * fabsf(cosf(fAngle)) * gDeltaTime);

	//Move();
}

//<><><><><><><><><><><><><><><><><><>
// �֐����FSetTarget
// �����F�ǂ�������Ώۂ��w��
//<><><><><><><><><><><><><><><><><><>
void Cat::SetTarget(XMFLOAT2 * target)
{
	fTarget = target;
	
	if (target == NULL) {
		ChangeState(CatState::WALK);
	}
	else {
		ChangeState(CatState::RUN);
	}
}

//<><><><><><><><><><><><><><><><><><>
// �֐����F��ԑJ��
// �����F��ԑJ��
//<><><><><><><><><><><><><><><><><><>
void Cat::ChangeState(CatState _state)
{
	nState = _state;
}

//<><><><><><><><><><><><><><><><><><>
// �֐����FGetState
// �����F���݂̏�Ԃ�n��
//<><><><><><><><><><><><><><><><><><>
CatState Cat::GetState(void)
{
	return nState;
}

//<><><><><><><><><><><><><><><><><><>
// �֐����F�����Ԃ̃Z�b�g
// �����F��ԑJ��
//<><><><><><><><><><><><><><><><><><>
void Cat::SetDirtState(CatDirtState _state)
{
	nDirtState = _state;

	//�e�N�X�`���̕ύX
	if (nDirtState == CatDirtState::CLEARN) {
		mAnimObject->SetTexture(mCatTex);
	}
	if (nDirtState == CatDirtState::DIRT) {
		mAnimObject->SetTexture(mDirtCatTex);
	}

}

//<><><><><><><><><><><><><><><><><><>
// �֐����FSetAppearance
// �����F�o����Ԃ̃Z�b�g
//<><><><><><><><><><><><><><><><><><>
void Cat::SetAppearance(bool _appearance)
{
	Appearance = _appearance;

	if (_appearance == true) {
		int AppearanceDirection = rand() % 4;	//�o�Ă�����������߂�

		switch (AppearanceDirection)
		{
		case D_RIGHT:	//�E
			mAnimObject->mCenter.x = 2.2f;
			mAnimObject->mCenter.y = -1.9f + (float)(rand() % 381) / 100.0f;
			break;
		case D_LEFT:	//��
			mAnimObject->mCenter.x = -2.2f;
			mAnimObject->mCenter.y = -1.9f + (float)(rand() % 381) / 100.0f;
			break;
		case D_UP:		//��
			mAnimObject->mCenter.x = -2.2f + (float)(rand() % 441) / 100.0f;
			mAnimObject->mCenter.y = -1.9f;
			break;
		case D_DOWN:	//��
			mAnimObject->mCenter.x = -2.2f + (float)(rand() % 441) / 100.0f;
			mAnimObject->mCenter.y = 1.9f;
			break;
		default:
			break;
		}
	}
}

//<><><><><><><><><><><><><><><><><><>
// �֐����FOutSideRun
// �����F�o����Ԃ̃Z�b�g
//<><><><><><><><><><><><><><><><><><>
void Cat::OutSideRun(XMFLOAT2 * _Pos)
{
}
