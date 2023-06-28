//======================================================================================
// 名前：Dog.cpp
// 説明：犬のソ－スファイル
//======================================================================================

//------------------------------------
//		include
//------------------------------------

#include "Dog.h"

extern DWORD gDeltaTime;

//------------------------------------
//		メンバー関数
//------------------------------------

//<><><><><><><><><><><><><><><><><><>
// 関数名：Walk
// 役割：通常状態処理
//<><><><><><><><><><><><><><><><><><>
void Dog::Walk(void)
{
	// 時間計算
	mTime += gDeltaTime;
	
	// 速度設定
	float Speed = 0.0001f;
	float SlipSpeed = 0.0f;
	
	// 滑る処理
	if (mSlip == true)
	{
		//mOldAngle = (mAngle+mOldAngle)/2;
		//SlipSpeed = Speed * 0.5f;
		mSpeedSlip.x += Speed * sinf(mAngle) * 0.005f;
		mSpeedSlip.y += Speed * cosf(mAngle) * 0.005f;
		// 滑る最大速度
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
	// 15～20秒に一回,角度の計算する
	if (mTime >= ((float)(rand() % 5) + 15.0f) * 1000.0f)
	{
		mAngle = ((float)(rand() % 2001 - 1000) / 1000.0f) * PI;
		mTime = 0.0f;
	}

	// 位置を更新
	mAnimObject->mCenter.x += (mResistance.x + Speed * sinf(mAngle) + SlipSpeed * sinf(mOldAngle)) * gDeltaTime;
	mAnimObject->mCenter.y += (mResistance.y + Speed * cosf(mAngle) + SlipSpeed * cosf(mOldAngle)) * gDeltaTime;
	// キャラの向きを設定する
	float X = sinf(mAngle);
	float Y = cosf(mAngle);

	if (X * X <= Y * Y)//縦
	{
		if (Y <= 0)// 下
		{
			mAnimObject->mDirection = D_DOWN;
		}
		else// 上
		{
			mAnimObject->mDirection = D_RIGHT;// D_UPではなくD_RIGHTが上向き
		}
	}
	else // 横
	{
		if (X <= 0)// 左
		{
			mAnimObject->mDirection = D_LEFT;
		}
		else// 右
		{
			mAnimObject->mDirection = D_UP;// D_RIGHTではなくD_UPが右向き
		}
	}
		
}

//<><><><><><><><><><><><><><><><><><>
// 関数名：Run
// 役割：フリスビーを追っかける状態処理
//<><><><><><><><><><><><><><><><><><>
void Dog::Run(void)
{
	mWaitTime -= gDeltaTime;
	// 速度設定
	float Speed = 0.0005f;
	//float SlipSpeed = 0.0f;
	// 滑る処理
	if (mSlip == true)
	{
		
		//SlipSpeed = Speed * 0.5f;
		mSpeedSlip.x += Speed * sinf(mAngle) * 0.005f;
		mSpeedSlip.y += Speed * cosf(mAngle) * 0.005f;
		// 滑る最大速度
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
	// 角度の計算する
	float X = mTarget->x - mAnimObject->mCenter.x ;
	float Y = mTarget->y - mAnimObject->mCenter.y ;
	
	mAngle = atan2f(X, Y);
	
	// 位置を更新
	if (mWaitTime <= 0)
	{
		mAnimObject->mCenter.x += (mResistance.x + Speed * sinf(mAngle) + mSpeedSlip.x) * gDeltaTime;
		mAnimObject->mCenter.y += (mResistance.y + Speed * cosf(mAngle) + mSpeedSlip.y) * gDeltaTime;
	}
	
	
	// キャラの向きを設定する
	X = sinf(mAngle);
	Y = cosf(mAngle);
	if (X * X <= Y * Y)//縦
	{
		if (Y <= 0)// 下
		{
			mAnimObject->mDirection = D_DOWN;
		}
		else// 上
		{
			mAnimObject->mDirection = D_RIGHT;// D_UPではなくD_RIGHTが上向き
		}
	}
	else // 横
	{
		if (X <= 0)// 左
		{
			mAnimObject->mDirection = D_LEFT;
		}
		else// 右
		{
			mAnimObject->mDirection = D_UP;// D_RIGHTではなくD_UPが右向き
		}
	}
	mOldAngle = mAngle;
}


//<><><><><><><><><><><><><><><><><><>
// 関数名：BeCarryed
// 役割：犬が運ばれる処理
//<><><><><><><><><><><><><><><><><><>
void Dog::BeCarryed(void)
{
	mAnimObject->fAnimCnt = 2.0f;//アニメーションを止める
	// ズレ
	XMFLOAT2 offset;
	offset = {0.0f,0.22f};
	// 位置更新
	mAnimObject->mCenter.x = mTarget->x + offset.x;
	mAnimObject->mCenter.y = mTarget->y + offset.y;
}


//<><><><><><><><><><><><><><><><><><>
// 関数名：Dog
// 役割：コンストラクタ
//<><><><><><><><><><><><><><><><><><>
Dog::Dog(XMFLOAT3 & _Camera):AnimObject(_Camera)
{
	LoadTexture(L"assets/images/Character/Dog/Dog.png", &mWalkTexture);
	LoadTexture(L"assets/images/Character/Dog/Run_dog.png", &mRunTexture);
	mAnimObject->SetTexture(mWalkTexture);
	mAnimObject->mSize.x = 0.2f;// サイズX
	mAnimObject->mSize.y = 0.2f;// サイズY
	mAnimObject->fAnimSpeed = 0.002f;// アニメーション速度
	mAngle = PI;
	mTime = 0.0f;
	mState = DOG_WALK;// 状態設定
	mWaitTime = 0.0f;
	mResistance = { 0.0f,0.0f };
	// あたり判定
	mCircle = new HitCircle(&mAnimObject->mCenter, 0.05f);// 体の当たり判定
	mCatchArea = new HitCircle(&mAnimObject->mCenter, 0.09f);// キャッチできるあたり判定
	mMissArea = new HitCircle(&mAnimObject->mCenter, 0.15f);// 失敗するあたり判定
	mCatchBubbleArea = new HitCircle(&mAnimObject->mCenter, 0.25f);// キャッチした時の泡あたり判定

	Sound_Init(SOUND_LABEL_SE010);
}

//<><><><><><><><><><><><><><><><><><>
// 関数名：~Dog
// 役割：デストラクタ
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
// 関数名：Update
// 役割：更新処理
//<><><><><><><><><><><><><><><><><><>
void Dog::Update()
{
	if (Fade_Bubble::mState == FADE_IN_END || Fade_Bubble::mState == NONE_FADE) {
		switch (mState)// 状態ごとの処理
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
		mSlip = false;// 滑るフラグのリセット
		//キャラの移動制限
		// Xの範囲制限
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
		// Yの範囲制限
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

	// 抵抗力の初期化
	mResistance.x = 0.0f;
	mResistance.y = 0.0f;
	// 基底クラスの更新処理
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
// 関数名：SetResistance
// 役割：抵抗力の計算
//<><><><><><><><><><><><><><><><><><>
void Dog::SetResistance(XMFLOAT2 _pos)
{
	XMFLOAT2 Distance;// プレイヤーと障害物の距離
	Distance.x = mAnimObject->mCenter.x - _pos.x;
	Distance.y = mAnimObject->mCenter.y - _pos.y;
	float square_root = sqrt(Distance.x * Distance.x + Distance.y * Distance.y);
	XMFLOAT2 Vector;
	Vector.x = (Distance.x / square_root) * 0.0008f;
	Vector.y = (Distance.y / square_root) * 0.0008f;

	mResistance = Vector;
}

//<><><><><><><><><><><><><><><><><><>
// 関数名：ChangeState
// 役割：犬の状態を変える
//<><><><><><><><><><><><><><><><><><>
void Dog::ChangeState(DogStateID _state)
{
	
	mState = _state;
	switch (_state)
	{
	case DOG_WALK:
		mAnimObject->SetTexture(mWalkTexture);// テクスチャを変更する
		mAnimObject->fAnimSpeed = 0.002f;// アニメーション速度
		mWaitTime = 0.0f;// 初期化
		break;
	case DOG_RUN:
		mAnimObject->SetTexture(mRunTexture);// テクスチャを変更する
		mAnimObject->fAnimSpeed = 0.006f;// アニメーション速度
		break;
	case DOG_WAIT:
		mWaitTime = 0.25f*1000.0f;
		break;
	case DOG_RETURN:
		mAnimObject->SetTexture(mRunTexture);// テクスチャを変更する
		mAnimObject->fAnimSpeed = 0.006f;// アニメーション速度
		break;
	}
}

//<><><><><><><><><><><><><><><><><><>
// 関数名：SetTarget
// 役割：追いかける相手を設定する
//<><><><><><><><><><><><><><><><><><>
void Dog::SetTarget(XMFLOAT2* _target)
{
	mTarget = _target;// 値ではなくアドレスを取ってくる
	ChangeState(DOG_RUN);
}

//======================================================================================
// 担当者：		中川直登
// チーム名：	黒棺	
//======================================================================================