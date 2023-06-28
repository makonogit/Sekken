//======================================================================================
// 名前：Duck.h
// 説明：アヒルのヘッダーファイル
//======================================================================================

//------------------------------------
//		include
//------------------------------------

#include "Duck.h"

extern DWORD gDeltaTime;

//------------------------------------
//		メンバー関数
//------------------------------------

//<><><><><><><><><><><><><><><><><><>
// 関数名：Move
// 役割：DUCK_MOVE状態の処理
//<><><><><><><><><><><><><><><><><><>
void Duck::Move(void)// 処理は犬とほぼ同じ
{
	// 時間計算
	mTime += gDeltaTime;
	// 速度設定
	float Speed = 0.0004f;
	// 15～20秒に一回,角度の計算する
	if (mTime >= ((float)(rand() % 5) + 15.0f) * 1000.0f)
	{
		mAngle = ((float)(rand() % 2001 - 1000) / 1000.0f) * PI;
		mTime = 0.0f;
	}

	// 位置を更新
	mAnimObject->mCenter.x += (mResistance.x + Speed * sinf(mAngle))* gDeltaTime;
	mAnimObject->mCenter.y += (mResistance.y + Speed * cosf(mAngle))* gDeltaTime;
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
// 関数名：Confusion
// 役割：DUCK_CONFUSIONの処理
//<><><><><><><><><><><><><><><><><><>
void Duck::Confusion(void)
{
	// 時間計算
	mTime += gDeltaTime;
	// 5～10秒経過すると戻る
	if (mTime >= ((float)(rand() % 5) + 5.0f) * 1000.0f)
	{
		ChangeState(DUCK_MOVE);
		mTime = 0.0f;
	}
}

//<><><><><><><><><><><><><><><><><><>
// 関数名：Duck
// 役割：コンストラクタ
//<><><><><><><><><><><><><><><><><><>
Duck::Duck(XMFLOAT3 & _Camera) :AnimObject(_Camera)
{

	LoadTexture(L"assets/images/Character/Duck/ChickRobot.png", &mDuckTex);
	mAnimObject->SetTexture(mDuckTex);
	mAnimObject->mCenter.x = 0.5f;// 位置X
	mAnimObject->mCenter.y = 0.5f;// 位置Y
	mAnimObject->mSize.x = 0.5f;// サイズX
	mAnimObject->mSize.y = 0.5f;// サイズY
	mAnimObject->fAnimSpeed = 0.002f;// アニメーション速度
	mAngle = PI*-1.0f;
	mTime = 0.0f;
	mState = DUCK_MOVE;// 状態設定
	
	mResistance = { 0.0f,0.0f };
	// あたり判定
	mCircle = new HitCircle(&mAnimObject->mCenter, 0.15f);// 体の当たり判定

	Sound_Init(SOUND_LABEL_SE013);
	Play(SOUND_LABEL_SE013);
	SetVolume(SOUND_LABEL_SE013, 5.5f);
	
}

//<><><><><><><><><><><><><><><><><><>
// 関数名：~Duck
// 役割：デストラクタ
//<><><><><><><><><><><><><><><><><><>
Duck::~Duck()
{
	Sound_Uninit(SOUND_LABEL_SE013);
	delete mCircle;
	COM_SAFE_RELEASE(mDuckTex);
}

//<><><><><><><><><><><><><><><><><><>
// 関数名：Update
// 役割：更新処理
//<><><><><><><><><><><><><><><><><><>
void Duck::Update()
{
	if (GetSoundState(SOUND_LABEL_SE013) == FALSE) {
		Play(SOUND_LABEL_SE013);
		SetVolume(SOUND_LABEL_SE013, 5.5f);
	}

	switch(mState)
	{
	case DUCK_CARRY:// MOVEと同じ処理で状態だけ違う
	case DUCK_MOVE:
		Move();
		break;
	case DUCK_CONFUSION:
		Confusion();
		break;
	}
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

	// 抵抗力の初期化
	mResistance.x = 0.0f;
	mResistance.y = 0.0f;
	GameObject::Update();
}

//<><><><><><><><><><><><><><><><><><>
// 関数名：SetResistance
// 役割：抵抗力の計算
//<><><><><><><><><><><><><><><><><><>
void Duck::SetResistance(XMFLOAT2 _pos)
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
// 役割：状態変更
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
