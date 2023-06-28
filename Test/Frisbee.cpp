//======================================================================================
// 名前：Frisbee.cpp
// 説明：フリスビーのソースファイル
//======================================================================================

#include "Frisbee.h"

extern DWORD gDeltaTime;

//<><><><><><><><><><><><><><><><><><>
// 関数名：Frisbee
// 役割：コンストラクタ
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
// 関数名：~Frisbee
// 役割：デストラクタ
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
// 関数名：SetReserve
// 役割：投げる準備の処理
//<><><><><><><><><><><><><><><><><><>
void Frisbee::SetReserve(XMFLOAT2 _pos , float _ang)
{
	this->mSprite->mCenter = _pos;
	mAngle = _ang;
	mRate = 1.0f;
	//フリスビーの状態を変える
	ChangeState(FRISBEE_FRY);
}

//<><><><><><><><><><><><><><><><><><>
// 関数名：Fry
// 役割：投げられた時の処理
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
	// 進行方向を変える
	float turnRate = 500.0f;
	mAngle -= ( LT / turnRate) * gDeltaTime;
	mAngle += ( RT / turnRate) * gDeltaTime;

	// スピードを落とす
	float normal = 0.0001f;//減速率
	float deceleration = 0.00005f;//ボタンを押した時の減速率
	mRate -= LT * deceleration * gDeltaTime;
	mRate -= RT * deceleration * gDeltaTime;
	mRate -= normal*gDeltaTime;

	// スピードがマイナスにならないよう制限する
	mRate = (mRate <= 0 ? 0 : mRate);

	// 位置の更新
	this->mSprite->mCenter.x += mSpeed * mRate * sinf(mAngle) *gDeltaTime;
	this->mSprite->mCenter.y += mSpeed * mRate * cosf(mAngle) *gDeltaTime;

	//移動制限
	// Xの範囲制限
	if(mSprite->mCenter.x < -2.2f)// -2.27f以下にならないようにする
	{
		mRate -= normal * 2.0f * gDeltaTime;
		mSprite->mCenter.x = -2.2f;
	}
	if(mSprite->mCenter.x > 2.2f)//  2.27f以上にならないようにする
	{
		mRate -= normal * 2.0f * gDeltaTime;
		mSprite->mCenter.x = 2.2f;
	}
	// Yの範囲制限
	if (mSprite->mCenter.y < -1.9f)// -1.9f以下にならないようにする
	{
		mRate -= normal * 2.0f * gDeltaTime;
		mSprite->mCenter.y = -1.9f;
	}
	if (mSprite->mCenter.y > 1.9f)//  1.9f以上にならないようにする
	{
		mRate -= normal * 2.0f * gDeltaTime;
		mSprite->mCenter.y = 1.9f;
	}

	// サイズを変える
	mSprite->mSize.x = mMiniSize + mRate/25;
	mSprite->mSize.y = mMiniSize + mRate/25;

	// 影の位置
	mShadow->mSprite->mCenter.x = this->mSprite->mCenter.x - (mRate/10) * sinf(0.0f);
	mShadow->mSprite->mCenter.y = this->mSprite->mCenter.y - (mRate/10) * cosf(0.0f);

	// DROPに遷移する
	if (mRate <= 0)// スピードが無くなったら
	{
		ChangeState(FRISBEE_DROP);
	}
	
}

//<><><><><><><><><><><><><><><><><><>
// 関数名：Drop
// 役割：落ちた時の処理
//<><><><><><><><><><><><><><><><><><>
void Frisbee::Drop()
{
	/*----- 特にやることない -----*/
	//if(Input_GetButtonTrigger(X))//デバック用
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
// 関数名：Update
// 役割：更新処理
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
	//親クラスで宣言したUpdate関数を実行する
	GameObject::Update();
}

//<><><><><><><><><><><><><><><><><><>
// 関数名：ChangeState
// 役割：状態設定
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
// 関数名：ChangeState
// 役割：状態設定
//<><><><><><><><><><><><><><><><><><>
void Frisbee::Catch(CharHoldFrisbee _catch)
{
	mHold = _catch;
}

//======================================================================================
// 担当者：		中川直登
// チーム名：	黒棺	
//======================================================================================
