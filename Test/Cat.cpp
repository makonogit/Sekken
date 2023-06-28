#include "Cat.h"
#include "System.h"
#include <stdlib.h>

extern DWORD gDeltaTime;

//<><><><><><><><><><><><><><><><><><>
// 関数名：Cat
// 役割：コンストラクタ
//<><><><><><><><><><><><><><><><><><>
Cat::Cat(XMFLOAT3 & _Camera):AnimObject(_Camera)
{
	//テクスチャ読み込み
	LoadTexture(L"assets/images/Character/Cat/Cat_Walk.png", &mCatTex);
	LoadTexture(L"assets/images/Character/Cat/Dirty_Cat.png", &mDirtCatTex);
	LoadTexture(L"assets/images/Character/Cat/LieDown.png", &mCatLieDownTex);
	LoadTexture(L"assets/images/Character/Cat/Cat_Jump.png", &mCatJampTex);

	//アニメーションしない状態のオブジェクト(寝転ぶ・ジャンプ)
	mStaticObj = new StaticObject(_Camera);
	mStaticObj->mSprite->SetTexture(mCatLieDownTex);
	mStaticObj->SetSize(0.14f, 0.14f);
	mStaticObj->SetPosition(-1.0f, -1.0f);
	
	//寝転んだ時の当たり判定
	mLieDownHit = new HitCircle(&mStaticObj->mSprite->mCenter, 0.1f);
	//mLieDownHit->active = false;

	//追いかけるあたり
	mBlockAreaHit = new HitCircle(&mStaticObj->mSprite->mCenter, 0.05f);

	//アニメーションするオブジェクトの設定(歩く・走る)
	mAnimObject->SetTexture(mCatTex);
	mAnimObject->mSize.x = 0.14f;
	mAnimObject->mSize.y = 0.14f;
	mAnimObject->mCenter.x = -2.2f;
	mAnimObject->mCenter.y = 1.9f;

	fCatDownTime = 0.0f;
	fTarget = NULL;				//追いかける対象を空にする
	nState = CatState::WALK;	//歩く
	nDirtState = CatDirtState::CLEARN;	//きれいな状態
	fAngle = PI;
	mHit->mRadius = 0.05f;
	Appearance = false;

	Sound_Init(SOUND_LABEL_SE011);
}

//<><><><><><><><><><><><><><><><><><>
// 関数名：~Cat
// 役割：デストラクタ
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
// 関数名：Update
// 役割：更新
//<><><><><><><><><><><><><><><><><><>
void Cat::Update()
{
	if (Fade_Bubble::mState == FADE_IN_END || Fade_Bubble::mState == NONE_FADE) {
		
		fTime += gDeltaTime;		//時間の計算
		fCatDownTime += gDeltaTime;	//寝転ぶ時間

		//mAnimObject->Update();
		mStaticObj->Update();

		//歩くor走ってる場合は移動し続ける
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

		//15秒から20秒に1回寝転ぶ(走ってるときは寝転ばない)
		if (fCatDownTime >= ((float)(rand() % 5) + 15.0f)* 1000.0f && nState != CatState::RUN && nState != CatState::WAIT) {

			nState = CatState::LIEDOWN;
			fCatDownTime = 0.0f;
		}

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
// 関数名：Draw
// 役割：更新
//<><><><><><><><><><><><><><><><><><>
void Cat::Draw()
{
	//アニメーションするかしないか
	if (nState == CatState::WALK || nState == CatState::RUN || nState == CatState::CNONE) {
		mAnimObject->Draw();
	}
	if(nState == CatState::LIEDOWN || nState == CatState::JUMP || nState == CatState::WAIT) {
		mStaticObj->Draw();
	}
}

//<><><><><><><><><><><><><><><><><><>
// 関数名：Move
// 役割：移動
//<><><><><><><><><><><><><><><><><><>
void Cat::Move()
{
	if (nState == WALK) {
		fMoveSpeed = 0.0001f;	//移動スピード
		mAnimObject->fAnimSpeed = 0.002f;
	}
	if (nState == RUN) {
		fMoveSpeed = 0.0004f;	//移動スピード
		mAnimObject->fAnimSpeed = 0.006f;
	}
	

	//追いかける対象があれば
	if (fTarget != NULL) {
		
		// 角度の計算する
		float X = fTarget->x - mAnimObject->mCenter.x;
		float Y = fTarget->y - mAnimObject->mCenter.y;

		fAngle = atan2f(X, Y);
	}
	else {
		//10秒置きに向きを決める
		if (fTime >= 10.0f * 1000.0f && nState != JUMP) {

			fAngle = ((float)(rand() % 2001 - 1000) / 1000.0f) * PI;
			fTime = 0.0f;
		}
	}

	//位置指定
	mAnimObject->mCenter.x += (fMoveSpeed * sinf(fAngle)) * gDeltaTime;
	mAnimObject->mCenter.y += (fMoveSpeed * cosf(fAngle)) * gDeltaTime;

	// キャラの向きを設定する
	float X = sinf(fAngle);
	float Y = cosf(fAngle);

	if (X * X <= Y * Y)//縦
	{
		if (Y <= 0)// 下
		{
			mAnimObject->mDirection = D_DOWN;
		}
		else// 上
		{
			mAnimObject->mDirection = D_UP;
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
			mAnimObject->mDirection = D_RIGHT;
		}
	}
}

//<><><><><><><><><><><><><><><><><><>
// 関数名：寝転ぶ
// 役割：
//<><><><><><><><><><><><><><><><><><>
void Cat::LieDown()
{	
	nState = LIEDOWN;

	mLieDownHit->active = true;
	mStaticObj->mSprite->SetTexture(mCatLieDownTex);//テクスチャを指定

	fCatDownTime += gDeltaTime;
	
	//時間経過で歩行に戻る(2秒)
	if (fCatDownTime >= 2.0f * 1000.0f) 
	{
		Stop(SOUND_LABEL_SE007);
		mLieDownHit->active = false;
		fCatDownTime = 0.0f;
		nState = WALK;
	}
}

//<><><><><><><><><><><><><><><><><><>
// 関数名：走る
// 役割：走る
//<><><><><><><><><><><><><><><><><><>
void Cat::Run()
{
	//画像変えたいカモ

}

//<><><><><><><><><><><><><><><><><><>
// 関数名：Jump
// 役割：ジャンプ
//<><><><><><><><><><><><><><><><><><>
void Cat::Jump()
{
	mStaticObj->mSprite->SetTexture(mCatJampTex);	//テクスチャの変更
	fMoveSpeed = 0.0005f;

	if (GetSoundState(SOUND_LABEL_SE011) == FALSE)
	{
		Play(SOUND_LABEL_SE011);
	}

	//画像を変える
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
// 関数名：Wait
// 役割：威嚇
//<><><><><><><><><><><><><><><><><><>
void Cat::Wait()
{
	//テクスチャの張替
	mStaticObj->mSprite->SetTexture(mCatLieDownTex);

	////nState = CatState::WAIT;
	//
	////めっちゃゆっくり後ずさりする
	//fMoveSpeed = 0.00002f;

	//*mAnimObject->mCenter.x += (fMoveSpeed * fabsf(sinf(fAngle)) * gDeltaTime);
	//mAnimObject->mCenter.y += (fMoveSpeed * fabsf(cosf(fAngle)) * gDeltaTime);

	//Move();
}

//<><><><><><><><><><><><><><><><><><>
// 関数名：SetTarget
// 役割：追いかける対象を指定
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
// 関数名：状態遷移
// 役割：状態遷移
//<><><><><><><><><><><><><><><><><><>
void Cat::ChangeState(CatState _state)
{
	nState = _state;
}

//<><><><><><><><><><><><><><><><><><>
// 関数名：GetState
// 役割：現在の状態を渡す
//<><><><><><><><><><><><><><><><><><>
CatState Cat::GetState(void)
{
	return nState;
}

//<><><><><><><><><><><><><><><><><><>
// 関数名：汚れ状態のセット
// 役割：状態遷移
//<><><><><><><><><><><><><><><><><><>
void Cat::SetDirtState(CatDirtState _state)
{
	nDirtState = _state;

	//テクスチャの変更
	if (nDirtState == CatDirtState::CLEARN) {
		mAnimObject->SetTexture(mCatTex);
	}
	if (nDirtState == CatDirtState::DIRT) {
		mAnimObject->SetTexture(mDirtCatTex);
	}

}

//<><><><><><><><><><><><><><><><><><>
// 関数名：SetAppearance
// 役割：出現状態のセット
//<><><><><><><><><><><><><><><><><><>
void Cat::SetAppearance(bool _appearance)
{
	Appearance = _appearance;

	if (_appearance == true) {
		int AppearanceDirection = rand() % 4;	//出てくる方向を決める

		switch (AppearanceDirection)
		{
		case D_RIGHT:	//右
			mAnimObject->mCenter.x = 2.2f;
			mAnimObject->mCenter.y = -1.9f + (float)(rand() % 381) / 100.0f;
			break;
		case D_LEFT:	//左
			mAnimObject->mCenter.x = -2.2f;
			mAnimObject->mCenter.y = -1.9f + (float)(rand() % 381) / 100.0f;
			break;
		case D_UP:		//上
			mAnimObject->mCenter.x = -2.2f + (float)(rand() % 441) / 100.0f;
			mAnimObject->mCenter.y = -1.9f;
			break;
		case D_DOWN:	//下
			mAnimObject->mCenter.x = -2.2f + (float)(rand() % 441) / 100.0f;
			mAnimObject->mCenter.y = 1.9f;
			break;
		default:
			break;
		}
	}
}

//<><><><><><><><><><><><><><><><><><>
// 関数名：OutSideRun
// 役割：出現状態のセット
//<><><><><><><><><><><><><><><><><><>
void Cat::OutSideRun(XMFLOAT2 * _Pos)
{
}
