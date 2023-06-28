#include "Robot.h"

extern DWORD gDeltaTime;

Robot::Robot(XMFLOAT3 & _Camera):AnimObject(_Camera)
{
	LoadTexture(L"assets/images/Character/Robot/Robot.png", &mRobotTexture);

	//アニメーションするオブジェクトの設定
	mAnimObject->SetTexture(mRobotTexture);
	mAnimObject->mSize.x = 0.6f;
	mAnimObject->mSize.y = 0.6f;
	mAnimObject->mCenter.x = -0.2f;
	mAnimObject->mCenter.y = 1.8;
	
	fAngle = PI;
	mState = false;
	mHit->active = false;

	Sound_Init(SOUND_LABEL_SE019);

	Play(SOUND_LABEL_SE019);
	SetVolume(SOUND_LABEL_SE019, 0.15f);

}

Robot::~Robot()
{
	Sound_Uninit(SOUND_LABEL_SE019);
	COM_SAFE_RELEASE(mRobotTexture);
}

void Robot::Move()
{
	if (GetSoundState(SOUND_LABEL_SE019) == FALSE) {
		Play(SOUND_LABEL_SE019);
		SetVolume(SOUND_LABEL_SE019, 0.15f);
	}

	fMoveSpeed = 0.001f * 0.5f;	//移動スピード
	mAnimObject->fAnimSpeed = 0.02f;

	// ロボットの向きを設定する
	if (mState)
	{			
		mAnimObject->mDirection = D_LEFT;
	}
	else
	{
		mAnimObject->mDirection = D_DOWN;
	}
	

}

void Robot::Update()
{

	Move();

	mAnimObject->mCenter.x += (fMoveSpeed * sinf(fAngle)) * gDeltaTime;
	mAnimObject->mCenter.y += (fMoveSpeed * cosf(fAngle)) * gDeltaTime;


	//----------移動制限-------------

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

	if (mAnimObject->mCenter.y < -1.7f)
	{
		mAnimObject->mCenter.y = -1.7f;
		fAngle = (((float)(rand() % 1001) / 1000.0f) - 0.5f) * PI;
		mState = true;
	}

	if (mAnimObject->mCenter.y > 1.8f)
	{
		mAnimObject->mCenter.y = 1.8f;
		fAngle = (((float)(rand() % 1001) / 1000.0f) + 0.5f) * -1.0f * PI;
		mState = false;
	}

	if (mHit->active == true)
	{
		mHit->active = false;
		fAngle = ((float)(rand() % 1001) / 1000.0f) * PI;
	}

	AnimObject::Update();
}
