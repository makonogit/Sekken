//======================================================================================
// ���O�FPlayer.cpp
// �����F�v���C���[�̃\�[�X�t�@�C��
//======================================================================================

//------------------------------------
//		include
//------------------------------------

#include "Player.h"

// �f���^�^�C���������Ă���iSystem.cpp�j
extern DWORD gDeltaTime;
extern HWND hWnd; // H=Handle=�|�C���^ WND=Window

//------------------------------------
//		�����o�[�֐�
//------------------------------------

//<><><><><><><><><><><><><><><><><><>
// �֐����FPlayer
// �����F�R���X�g���N�^
//<><><><><><><><><><><><><><><><><><>
Player::Player(XMFLOAT3 &_Camera, Frisbee* _Fris):AnimObject(_Camera),mpFrisbee(_Fris)
{
	
	LoadTexture(L"assets/images/Character/Player/Character.png", &mPlayerTex);// �v���C���[�̃e�N�X�`��
	LoadTexture(L"assets/images/Character/Player/Throw_frisbee.png", &mPlayerTexThrow);// �v���C���[�̓�����e�N�X�`��
	LoadTexture(L"assets/Mark_test.png", &mMarkTex); // �ڈ�e�N�X�`��
	mAnimObject->SetTexture(mPlayerTex);// �e�N�X�`���̃Z�b�g
	mAnimObject->mSize.x = 0.2f;// �T�C�YX
	mAnimObject->mSize.y = 0.2f;// �T�C�YY
	mAnimObject->fAnimSpeed = 0.003f;// �A�j���[�V�������x
	mState = PLAYER_MOVE; // �v���C���[�̏��
	mThrowAngle = 0.0f; // ���������

	// �����蔻��
	mCircle = new HitCircle(&mAnimObject->mCenter);
	mCircle->mRadius = 0.05f;// ���a
	//mCircle->mGap.y = -0.05f;

	// ����������̖ڈ�
	mMark = new StaticObject(_Camera);
	Sprite::RGBA color = {0.0f,0.0f,1.0f,1.0f};// �F
	mMark->mSprite->SetColor(color);
	mMark->mSprite->SetTexture(mMarkTex);
	mMark->active = false;// ������Ƃ��ɕ\������
	mMark->mSprite->mSize.x = 0.05f;// �ڈ�̃T�C�YX
	mMark->mSprite->mSize.y = 0.05f;// �ڈ�̃T�C�YY

	// ��R�͂̏�����
	mResistance.x = 0.0f;
	mResistance.y = 0.0f;
	mSpeedSlip.x = 0.0f;
	mSpeedSlip.y = 0.0f; 
	mHitCount = false;
	fWalkSETime = 0.0f;

	Sound_Init(SOUND_LABEL_SE024);

}

//<><><><><><><><><><><><><><><><><><>
// �֐����F~Player
// �����F�f�X�g���N�^
//<><><><><><><><><><><><><><><><><><>
Player::~Player()
{
	Sound_Uninit(SOUND_LABEL_SE024);
	delete mCircle;
	COM_SAFE_RELEASE(mMarkTex);
	COM_SAFE_RELEASE(mPlayerTexThrow);
	COM_SAFE_RELEASE(mPlayerTex);
}

//<><><><><><><><><><><><><><><><><><>
// �֐����FMove
// �����F�ړ�
//<><><><><><><><><><><><><><><><><><>
void Player::Move()
{
	fWalkSETime += gDeltaTime;

	// �X�e�B�b�N�̒l�����Ă����ꏊ(������g���̂ŕϐ��Ƃ��Ď����Ă���)
	float LStick_Y = Input_GetLeftStick_Y();
	float LStick_X = Input_GetLeftStick_X();
	if (LStick_X == 0 && LStick_Y == 0)
	{
		if(Input_GetKeyDown('W'))
		{
			LStick_Y = 1;
		}
		else if(Input_GetKeyDown('S'))
		{
			LStick_Y = -1;
		}
		else
		{
			LStick_Y = 0;
		}
		if (Input_GetKeyDown('D'))
		{
			LStick_X = 1;
		}
		else if (Input_GetKeyDown('A'))
		{
			LStick_X = -1;
		}
		else
		{
			LStick_X = 0;
		}

		if (LStick_X * LStick_X + LStick_Y * LStick_Y >= 2)
		{
			LStick_Y *= 0.707106f;
			LStick_X *= 0.707106f;
		}
	}

	if (LStick_X == 0 && LStick_Y == 0)
	{
		Stop(SOUND_LABEL_SE024);
	}
	else {
		if (fWalkSETime >= 0.65f * 1000) {
			Play(SOUND_LABEL_SE024);
			fWalkSETime = 0.0f;
		}
	}

	float Trans_Factor = 0.0005f ;	//�ړ��W��(�ő�ړ����x

	// �X�s�[�h�ݒ�
	mSpeed.x = LStick_X * Trans_Factor ;
	mSpeed.y = LStick_Y * Trans_Factor ;

	// ���鏈��
	if (mHitCount == true)// ���鏰�ɏ���Ă���Ƃ�
	{
		mSpeedSlip.x += mSpeed.x * 0.005f;
		mSpeedSlip.y += mSpeed.y * 0.005f; 
		// ����ő呬�x
		float MaxSlip = 0.001f;
		mSpeedSlip.x = (mSpeedSlip.x > MaxSlip ? MaxSlip : mSpeedSlip.x);
		mSpeedSlip.x = (mSpeedSlip.x < -MaxSlip ? -MaxSlip : mSpeedSlip.x);
		mSpeedSlip.y = (mSpeedSlip.y > MaxSlip ? MaxSlip : mSpeedSlip.y);
		mSpeedSlip.y = (mSpeedSlip.y < -MaxSlip ? -MaxSlip : mSpeedSlip.y);
	}
	else// ���鏰�ɏ���Ă��Ȃ��Ƃ�
	{
		mSpeedSlip.x = 0.0f;
		mSpeedSlip.y = 0.0f;
	}

	// �v���C���[�̈ʒu�X�V
	mAnimObject->mCenter.x += (mSpeed.x + mResistance.x + mSpeedSlip.x) * gDeltaTime;
	mAnimObject->mCenter.y += (mSpeed.y + mResistance.y + mSpeedSlip.y) * gDeltaTime;
	

	// ��R�͂̏�����
	mResistance.x = 0.0f;
	mResistance.y = 0.0f;
	// mSpeedOld
	
	//���͂ɂ���Č�����ς���
	if (LStick_X * LStick_X > LStick_Y * LStick_Y)//�X�e�B�b�N���傫���|�������Ɍ���
	{
		// �X�e�B�b�N�̂w��0.0f���傫�Ȃ�E�������A����ȊO�͍� �����摜�̈ʒu�Ɨ񋓌^���ႤUP��RIGHT
		mAnimObject->mDirection = (LStick_X > 0.0f ? D_UP : D_LEFT);
	}
	else
	{
		// �X�e�B�b�N��Y��0.0f���傫�Ȃ��������A����ȊO�͉� �����摜�̈ʒu�Ɨ񋓌^���ႤUP��RIGHT
		mAnimObject->mDirection = (LStick_Y > 0.0f ? D_RIGHT : D_DOWN); 
	}
	
	if (LStick_X + LStick_X == 0.0f)//�X�e�B�b�N�������G��Ȃ��Ƃ�
	{
		mAnimObject->fAnimCnt = 1.0f;//�A�j���[�V�������~�߂�i�_�����j
	}

	//�L�����̈ړ�����
	// X�͈̔͐���
	mAnimObject->mCenter.x = (mAnimObject->mCenter.x < -2.22f ? -2.22f : mAnimObject->mCenter.x);	// -2.27f�ȉ��ɂȂ�Ȃ��悤�ɂ���i�O�����Z�q�j
	mAnimObject->mCenter.x = (mAnimObject->mCenter.x >  2.22f ?  2.22f : mAnimObject->mCenter.x);	//  2.27f�ȏ�ɂȂ�Ȃ��悤�ɂ���i�O�����Z�q�j
	// Y�͈̔͐���
	mAnimObject->mCenter.y = (mAnimObject->mCenter.y < -1.9f ? -1.9f : mAnimObject->mCenter.y);	// -1.9f�ȉ��ɂȂ�Ȃ��悤�ɂ���i�O�����Z�q�j
	mAnimObject->mCenter.y = (mAnimObject->mCenter.y >  1.9f ?  1.9f : mAnimObject->mCenter.y);	//  1.9f�ȏ�ɂȂ�Ȃ��悤�ɂ���i�O�����Z�q�j

	// �������Ԃ֕ς���
	if ((Input_GetButtonTrigger(B) || Input_GetKeyTrigger(VK_SPACE)) && mpFrisbee->mHold == HOLD_PLAYER)
	{
		//mState = PLAYER_THROW;// ��ԑJ�ځF������
		//mAnimObject->SetTexture(mPlayerTexThrow);// �e�N�X�`���̕ύX
		//mMark->active = true;// �ڈ�\��
		ChangeState(PLAYER_THROW);
	}
	mHitCount = false;
}

//<><><><><><><><><><><><><><><><><><>
// �֐����FThrow
// �����F������
//<><><><><><><><><><><><><><><><><><>
void Player::Throw()
{
	//enum DIRECTION�̏��� = �摜V�̈ʒu
	//D_DOWN 0, D_LEFT 1, D_RIGHT 2, D_UP 3

	// ���|��{���|�E�{
	float LStick_Y = Input_GetLeftStick_Y();
	float LStick_X = Input_GetLeftStick_X();
	
	//�X�e�B�b�N��G���Ă���Ƃ�
	if (LStick_X + LStick_Y != 0.0f)
	{
		// ������p�x�̌v�Z����
		mThrowAngle = atan2f(LStick_X,LStick_Y);
	}
	else if(LStick_X + LStick_Y == 0.0f)
	{
		float MouseX, MouseY; 
		
		RECT rect;// �E�B���h�E�̒[�̍��W
		GetWindowRect(hWnd,&rect);// �E�B���h�E�̒[�̍��W
		float Width = (rect.right - rect.left)/2.0f;// �����̔���
		float Height = (rect.bottom - rect.top) / 2.0f;// �c���̔���

		// �Q�[�����ł̃}�E�X���W�����߂�
		MouseX = ((float)Input_GetMousePosX() / Width) - 1.0f;// �}�E�X���W��-1.0f�`1.0f�͈̔͂ɂ���
		MouseY = ((float)Input_GetMousePosY() / -Height) + 1.0f;// �}�E�X���W��-1.0f�`1.0f�͈̔͂ɂ���

		float angleX = MouseX - (mAnimObject->mCenter.x - mAnimObject->mCamera.x);// �}�E�X����v���C���[��X���������߂�
		float angleY = MouseY - (mAnimObject->mCenter.y - mAnimObject->mCamera.y);// �}�E�X����v���C���[��Y���������߂�
		// ���K�����邽�߂̂��
		float norm = sqrtf(angleX * angleX + angleY * angleY);

		// ��������������߂�
		mThrowAngle = atan2f(angleX / norm, angleY / norm);
	}

	//���͂ɂ���Č�����ς���
	if (cosf(mThrowAngle) >= 0.0f)//�X�e�B�b�N���ォ�Ȃ��������
	{
		//�X�e�B�b�N�̓��͂ŉE������������
		mAnimObject->mDirection = (sinf(mThrowAngle) > 0.0f ? D_UP : D_LEFT);
	}
	else//�X�e�B�b�N�������Ȃ�O������
	{
		//�X�e�B�b�N�̓��͂ŉE������������
		mAnimObject->mDirection = (sinf(mThrowAngle) > 0.0f ? D_RIGHT : D_DOWN);
	}

	// ����������̖ڈ�̈ʒu�X�V
	mMark->mSprite->mCenter.x = mAnimObject->mCenter.x + sinf(mThrowAngle) * 0.25f;
	mMark->mSprite->mCenter.y = mAnimObject->mCenter.y + cosf(mThrowAngle) * 0.25f;

	// �t���X�r�[�𓊂���܂ł̏���
	if ((Input_GetButtonDown(B)||Input_GetKeyDown(VK_SPACE))&&mMark->active != false)// B�{�^���������Ă����
	{
		mAnimObject->fAnimCnt = 2.0f;//�A�j���[�V�������~�߂�i�t���X�r�[�����j
		mpFrisbee->ChangeState(FRISBEE_HOLD);

	}
	else if(mAnimObject->fAnimCnt <= 1.0f)// B�{�^�����������A������A�j���[�V�������I�������
	{
		mAnimObject->fAnimCnt = 0.0f;//�A�j���[�V�������~�߂�i��������j

		if (mpFrisbee->mState == FRISBEE_HOLD&& mpFrisbee->mHold == HOLD_PLAYER)// �t���X�r�[���������Ă��Ȃ�����\���̎�
		{
			mMark->active = false;
			mpFrisbee->SetReserve(this->mAnimObject->mCenter, mThrowAngle);

		}

		if (mpFrisbee->mState == FRISBEE_DROP )// �t���X�r�[����������
		{
			ChangeState(PLAYER_MOVE);
		}
	}
}

//<><><><><><><><><><><><><><><><><><>
// �֐����FUpdate
// �����F�X�V
//<><><><><><><><><><><><><><><><><><>
void Player::Update()
{
	if (Fade_Bubble::mState == FADE_IN_END || Fade_Bubble::mState == NONE_FADE) {
		switch (mState)
		{
		case PLAYER_MOVE:
			Move();	//�ړ�����
			break;
		case PLAYER_THROW:
			Throw(); //�t���X�r�[�𓊂��鏈��
			break;
		}
		// ����������̖ڈ�̈ʒu�X�V
		mMark->Update();
	}
	GameObject::Update();
}

//<><><><><><><><><><><><><><><><><><>
// �֐����FSlip
// �����F����
//<><><><><><><><><><><><><><><><><><>
void Player::Slip()
{
	mHitCount=true;
}

//<><><><><><><><><><><><><><><><><><>
// �֐����FNoSlip
// �����F����Ȃ�
//<><><><><><><><><><><><><><><><><><>
//void Player::NoSlip()
//{
//	//mSpeedSlip.x = 0.0f;
//	//mSpeedSlip.y = 0.0f;
//	mHitCount = false;
//}

//<><><><><><><><><><><><><><><><><><>
// �֐����FSetResistance
// �����F��R�͂̌v�Z
//<><><><><><><><><><><><><><><><><><>
void Player::SetResistance(XMFLOAT2 _pos)
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

void Player::ChangeState(PlayerStateID _state)
{
	mState = _state;
	switch(_state)
	{
	case PLAYER_MOVE:
		mAnimObject->SetTexture(mPlayerTex);// �ړ��e�N�X�`���ɕς���
		break;
	case PLAYER_THROW:
		mAnimObject->SetTexture(mPlayerTexThrow);// �e�N�X�`���̕ύX
		mMark->active = true;// �ڈ�\��
		break;
	}
}

//======================================================================================
// �S���ҁF		���쒼�o
// �`�[�����F	����	
//======================================================================================
