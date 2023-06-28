//======================================================================================
// ���O�FSlipperyFloor.cpp
// �����F�҂��҂��̏��̃\�[�X�t�@�C��
//======================================================================================

//------------------------------------
//		include
//------------------------------------
#include "SlipperyFloor.h"

extern DWORD gDeltaTime;

//------------------------------------
//		�����o�[�֐�
//------------------------------------

//<><><><><><><><><><><><><><><><><><>
// �֐����FSliperyFloor
// �����F�R���X�g���N�^
//<><><><><><><><><><><><><><><><><><>
SlipperyFloor::SlipperyFloor(XMFLOAT3 &_Camera) :AnimObject(_Camera)
{
	//LoadTexture(L"assets/Slippery.png", &mTexture);
	//mSprite->SetTexture(mTexture);
	Sprite::RGBA color = { 1.0f,1.0f,0.9f,1.0f };// �F
	mSprite->SetColor(color);// �F�̐ݒ�
	this->active = false;// ��A�N�e�B�u��
	mlimitTime = 0.0f;// �������Ԃ̏�����
	mTime = 0.0f;// �o�ߎ��Ԃ̏�����
	
	//mAnimObject->mSize.x = 0.116f;	//�T�C�Y�ݒ�
	//mAnimObject->mSize.y = 0.132f;
	//mSprite->mSize.x = mAnimObject->mSize.x;
	//mSprite->mSize.y = mAnimObject->mSize.y;
	this->SetSize(0.116f, 0.132f);// �|���S���T�C�Y

	mAnimObject->mDirection = D_LEFT;// �e�N�X�`���̈ʒu
	mAnimObject->fAnimSpeed *= 5;// �A�j���[�V�����̑��x

	mSquare = new HitSquare(&mSprite->mCenter, { mSprite->mSize.x,mSprite->mSize.y }, {0.0f,0.0f}, 0.0f);// �����蔻��
	/*mSquare->mGap = { 0.0f,0.0f };
	mSquare->mSize = { mSprite->mSize.x,mSprite->mSize.y};*/
	//mSquare->Setting();
}

//<><><><><><><><><><><><><><><><><><>
// �֐����F~SlipperyFloor
// �����F�f�X�g���N�^
//<><><><><><><><><><><><><><><><><><>
SlipperyFloor::~SlipperyFloor()
{
	delete mSquare;
	//COM_SAFE_RELEASE(mTexture);
}

//<><><><><><><><><><><><><><><><><><>
// �֐����FUpdate
// �����F�X�V����
//<><><><><><><><><><><><><><><><><><>
void SlipperyFloor::Update()
{
	if(mTime >= mlimitTime)
	{
		this->active = false;
		mTime = 0.0f;
	}
	mTime += active * gDeltaTime;// false = 0 ,true = 1
	if (mAnimObject->fAnimCnt >= 3)
	{
		mAnimObject->fAnimCnt = 0.0f;
	}

	GameObject::Update();
}

//<><><><><><><><><><><><><><><><><><>
// �֐����FSetLimitTime
// �����F�������Ԑݒ茓�A�N�e�B�u��
//<><><><><><><><><><><><><><><><><><>
void SlipperyFloor::SetLimitTime(float _limit)
{
	this->active = true;
	mlimitTime = _limit* 1000.0f;// �������� * 1�b
	mTime = 0.0f;
}

//======================================================================================
// �S���ҁF		���쒼�o
// �`�[�����F	����	
//======================================================================================