//======================================================================================
// 名前：Player.cpp
// 説明：プレイヤーのソースファイル
//======================================================================================

//------------------------------------
//		include
//------------------------------------

#include "Player.h"

// デルタタイムを持ってくる（System.cpp）
extern DWORD gDeltaTime;
extern HWND hWnd; // H=Handle=ポインタ WND=Window

//------------------------------------
//		メンバー関数
//------------------------------------

//<><><><><><><><><><><><><><><><><><>
// 関数名：Player
// 役割：コンストラクタ
//<><><><><><><><><><><><><><><><><><>
Player::Player(XMFLOAT3 &_Camera, Frisbee* _Fris):AnimObject(_Camera),mpFrisbee(_Fris)
{
	
	LoadTexture(L"assets/images/Character/Player/Character.png", &mPlayerTex);// プレイヤーのテクスチャ
	LoadTexture(L"assets/images/Character/Player/Throw_frisbee.png", &mPlayerTexThrow);// プレイヤーの投げるテクスチャ
	LoadTexture(L"assets/Mark_test.png", &mMarkTex); // 目印テクスチャ
	mAnimObject->SetTexture(mPlayerTex);// テクスチャのセット
	mAnimObject->mSize.x = 0.2f;// サイズX
	mAnimObject->mSize.y = 0.2f;// サイズY
	mAnimObject->fAnimSpeed = 0.003f;// アニメーション速度
	mState = PLAYER_MOVE; // プレイヤーの状態
	mThrowAngle = 0.0f; // 投げる方向

	// あたり判定
	mCircle = new HitCircle(&mAnimObject->mCenter);
	mCircle->mRadius = 0.05f;// 半径
	//mCircle->mGap.y = -0.05f;

	// 投げる方向の目印
	mMark = new StaticObject(_Camera);
	Sprite::RGBA color = {0.0f,0.0f,1.0f,1.0f};// 色
	mMark->mSprite->SetColor(color);
	mMark->mSprite->SetTexture(mMarkTex);
	mMark->active = false;// 投げるときに表示する
	mMark->mSprite->mSize.x = 0.05f;// 目印のサイズX
	mMark->mSprite->mSize.y = 0.05f;// 目印のサイズY

	// 抵抗力の初期化
	mResistance.x = 0.0f;
	mResistance.y = 0.0f;
	mSpeedSlip.x = 0.0f;
	mSpeedSlip.y = 0.0f; 
	mHitCount = false;
	fWalkSETime = 0.0f;

	Sound_Init(SOUND_LABEL_SE024);

}

//<><><><><><><><><><><><><><><><><><>
// 関数名：~Player
// 役割：デストラクタ
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
// 関数名：Move
// 役割：移動
//<><><><><><><><><><><><><><><><><><>
void Player::Move()
{
	fWalkSETime += gDeltaTime;

	// スティックの値を入れておく場所(何回も使うので変数として持っておく)
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

	float Trans_Factor = 0.0005f ;	//移動係数(最大移動速度

	// スピード設定
	mSpeed.x = LStick_X * Trans_Factor ;
	mSpeed.y = LStick_Y * Trans_Factor ;

	// 滑る処理
	if (mHitCount == true)// 滑る床に乗っているとき
	{
		mSpeedSlip.x += mSpeed.x * 0.005f;
		mSpeedSlip.y += mSpeed.y * 0.005f; 
		// 滑る最大速度
		float MaxSlip = 0.001f;
		mSpeedSlip.x = (mSpeedSlip.x > MaxSlip ? MaxSlip : mSpeedSlip.x);
		mSpeedSlip.x = (mSpeedSlip.x < -MaxSlip ? -MaxSlip : mSpeedSlip.x);
		mSpeedSlip.y = (mSpeedSlip.y > MaxSlip ? MaxSlip : mSpeedSlip.y);
		mSpeedSlip.y = (mSpeedSlip.y < -MaxSlip ? -MaxSlip : mSpeedSlip.y);
	}
	else// 滑る床に乗っていないとき
	{
		mSpeedSlip.x = 0.0f;
		mSpeedSlip.y = 0.0f;
	}

	// プレイヤーの位置更新
	mAnimObject->mCenter.x += (mSpeed.x + mResistance.x + mSpeedSlip.x) * gDeltaTime;
	mAnimObject->mCenter.y += (mSpeed.y + mResistance.y + mSpeedSlip.y) * gDeltaTime;
	

	// 抵抗力の初期化
	mResistance.x = 0.0f;
	mResistance.y = 0.0f;
	// mSpeedOld
	
	//入力によって向きを変える
	if (LStick_X * LStick_X > LStick_Y * LStick_Y)//スティックが大きく倒した方に向く
	{
		// スティックのＸが0.0fより大きなら右を向く、それ以外は左 ※元画像の位置と列挙型が違うUP⇔RIGHT
		mAnimObject->mDirection = (LStick_X > 0.0f ? D_UP : D_LEFT);
	}
	else
	{
		// スティックのYが0.0fより大きなら上を向く、それ以外は下 ※元画像の位置と列挙型が違うUP⇔RIGHT
		mAnimObject->mDirection = (LStick_Y > 0.0f ? D_RIGHT : D_DOWN); 
	}
	
	if (LStick_X + LStick_X == 0.0f)//スティックを何も触らないとき
	{
		mAnimObject->fAnimCnt = 1.0f;//アニメーションを止める（棒立ち）
	}

	//キャラの移動制限
	// Xの範囲制限
	mAnimObject->mCenter.x = (mAnimObject->mCenter.x < -2.22f ? -2.22f : mAnimObject->mCenter.x);	// -2.27f以下にならないようにする（三項演算子）
	mAnimObject->mCenter.x = (mAnimObject->mCenter.x >  2.22f ?  2.22f : mAnimObject->mCenter.x);	//  2.27f以上にならないようにする（三項演算子）
	// Yの範囲制限
	mAnimObject->mCenter.y = (mAnimObject->mCenter.y < -1.9f ? -1.9f : mAnimObject->mCenter.y);	// -1.9f以下にならないようにする（三項演算子）
	mAnimObject->mCenter.y = (mAnimObject->mCenter.y >  1.9f ?  1.9f : mAnimObject->mCenter.y);	//  1.9f以上にならないようにする（三項演算子）

	// 投げる状態へ変える
	if ((Input_GetButtonTrigger(B) || Input_GetKeyTrigger(VK_SPACE)) && mpFrisbee->mHold == HOLD_PLAYER)
	{
		//mState = PLAYER_THROW;// 状態遷移：投げる
		//mAnimObject->SetTexture(mPlayerTexThrow);// テクスチャの変更
		//mMark->active = true;// 目印表示
		ChangeState(PLAYER_THROW);
	}
	mHitCount = false;
}

//<><><><><><><><><><><><><><><><><><>
// 関数名：Throw
// 役割：投げる
//<><><><><><><><><><><><><><><><><><>
void Player::Throw()
{
	//enum DIRECTIONの順番 = 画像Vの位置
	//D_DOWN 0, D_LEFT 1, D_RIGHT 2, D_UP 3

	// 下－上＋左－右＋
	float LStick_Y = Input_GetLeftStick_Y();
	float LStick_X = Input_GetLeftStick_X();
	
	//スティックを触っているとき
	if (LStick_X + LStick_Y != 0.0f)
	{
		// 投げる角度の計算する
		mThrowAngle = atan2f(LStick_X,LStick_Y);
	}
	else if(LStick_X + LStick_Y == 0.0f)
	{
		float MouseX, MouseY; 
		
		RECT rect;// ウィンドウの端の座標
		GetWindowRect(hWnd,&rect);// ウィンドウの端の座標
		float Width = (rect.right - rect.left)/2.0f;// 横幅の半分
		float Height = (rect.bottom - rect.top) / 2.0f;// 縦幅の半分

		// ゲーム内でのマウス座標を求める
		MouseX = ((float)Input_GetMousePosX() / Width) - 1.0f;// マウス座標を-1.0f～1.0fの範囲にする
		MouseY = ((float)Input_GetMousePosY() / -Height) + 1.0f;// マウス座標を-1.0f～1.0fの範囲にする

		float angleX = MouseX - (mAnimObject->mCenter.x - mAnimObject->mCamera.x);// マウスからプレイヤーのX距離を求める
		float angleY = MouseY - (mAnimObject->mCenter.y - mAnimObject->mCamera.y);// マウスからプレイヤーのY距離を求める
		// 正規化するためのやつ
		float norm = sqrtf(angleX * angleX + angleY * angleY);

		// 投げる方向を求める
		mThrowAngle = atan2f(angleX / norm, angleY / norm);
	}

	//入力によって向きを変える
	if (cosf(mThrowAngle) >= 0.0f)//スティックが上かなら後ろを向く
	{
		//スティックの入力で右か左かを向く
		mAnimObject->mDirection = (sinf(mThrowAngle) > 0.0f ? D_UP : D_LEFT);
	}
	else//スティックが下かなら前を向く
	{
		//スティックの入力で右か左かを向く
		mAnimObject->mDirection = (sinf(mThrowAngle) > 0.0f ? D_RIGHT : D_DOWN);
	}

	// 投げる方向の目印の位置更新
	mMark->mSprite->mCenter.x = mAnimObject->mCenter.x + sinf(mThrowAngle) * 0.25f;
	mMark->mSprite->mCenter.y = mAnimObject->mCenter.y + cosf(mThrowAngle) * 0.25f;

	// フリスビーを投げるまでの処理
	if ((Input_GetButtonDown(B)||Input_GetKeyDown(VK_SPACE))&&mMark->active != false)// Bボタンを押している間
	{
		mAnimObject->fAnimCnt = 2.0f;//アニメーションを止める（フリスビーを持つ）
		mpFrisbee->ChangeState(FRISBEE_HOLD);

	}
	else if(mAnimObject->fAnimCnt <= 1.0f)// Bボタンを放した後、投げるアニメーションが終わったか
	{
		mAnimObject->fAnimCnt = 0.0f;//アニメーションを止める（投げた後）

		if (mpFrisbee->mState == FRISBEE_HOLD&& mpFrisbee->mHold == HOLD_PLAYER)// フリスビーが投げられていない且つ非表示の時
		{
			mMark->active = false;
			mpFrisbee->SetReserve(this->mAnimObject->mCenter, mThrowAngle);

		}

		if (mpFrisbee->mState == FRISBEE_DROP )// フリスビーが落ちた時
		{
			ChangeState(PLAYER_MOVE);
		}
	}
}

//<><><><><><><><><><><><><><><><><><>
// 関数名：Update
// 役割：更新
//<><><><><><><><><><><><><><><><><><>
void Player::Update()
{
	if (Fade_Bubble::mState == FADE_IN_END || Fade_Bubble::mState == NONE_FADE) {
		switch (mState)
		{
		case PLAYER_MOVE:
			Move();	//移動処理
			break;
		case PLAYER_THROW:
			Throw(); //フリスビーを投げる処理
			break;
		}
		// 投げる方向の目印の位置更新
		mMark->Update();
	}
	GameObject::Update();
}

//<><><><><><><><><><><><><><><><><><>
// 関数名：Slip
// 役割：滑る
//<><><><><><><><><><><><><><><><><><>
void Player::Slip()
{
	mHitCount=true;
}

//<><><><><><><><><><><><><><><><><><>
// 関数名：NoSlip
// 役割：滑らない
//<><><><><><><><><><><><><><><><><><>
//void Player::NoSlip()
//{
//	//mSpeedSlip.x = 0.0f;
//	//mSpeedSlip.y = 0.0f;
//	mHitCount = false;
//}

//<><><><><><><><><><><><><><><><><><>
// 関数名：SetResistance
// 役割：抵抗力の計算
//<><><><><><><><><><><><><><><><><><>
void Player::SetResistance(XMFLOAT2 _pos)
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

void Player::ChangeState(PlayerStateID _state)
{
	mState = _state;
	switch(_state)
	{
	case PLAYER_MOVE:
		mAnimObject->SetTexture(mPlayerTex);// 移動テクスチャに変える
		break;
	case PLAYER_THROW:
		mAnimObject->SetTexture(mPlayerTexThrow);// テクスチャの変更
		mMark->active = true;// 目印表示
		break;
	}
}

//======================================================================================
// 担当者：		中川直登
// チーム名：	黒棺	
//======================================================================================
