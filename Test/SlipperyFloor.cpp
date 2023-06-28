//======================================================================================
// 名前：SlipperyFloor.cpp
// 説明：ぴかぴかの床のソースファイル
//======================================================================================

//------------------------------------
//		include
//------------------------------------
#include "SlipperyFloor.h"

extern DWORD gDeltaTime;

//------------------------------------
//		メンバー関数
//------------------------------------

//<><><><><><><><><><><><><><><><><><>
// 関数名：SliperyFloor
// 役割：コンストラクタ
//<><><><><><><><><><><><><><><><><><>
SlipperyFloor::SlipperyFloor(XMFLOAT3 &_Camera) :AnimObject(_Camera)
{
	//LoadTexture(L"assets/Slippery.png", &mTexture);
	//mSprite->SetTexture(mTexture);
	Sprite::RGBA color = { 1.0f,1.0f,0.9f,1.0f };// 色
	mSprite->SetColor(color);// 色の設定
	this->active = false;// 非アクティブ化
	mlimitTime = 0.0f;// 制限時間の初期化
	mTime = 0.0f;// 経過時間の初期化
	
	//mAnimObject->mSize.x = 0.116f;	//サイズ設定
	//mAnimObject->mSize.y = 0.132f;
	//mSprite->mSize.x = mAnimObject->mSize.x;
	//mSprite->mSize.y = mAnimObject->mSize.y;
	this->SetSize(0.116f, 0.132f);// ポリゴンサイズ

	mAnimObject->mDirection = D_LEFT;// テクスチャの位置
	mAnimObject->fAnimSpeed *= 5;// アニメーションの速度

	mSquare = new HitSquare(&mSprite->mCenter, { mSprite->mSize.x,mSprite->mSize.y }, {0.0f,0.0f}, 0.0f);// あたり判定
	/*mSquare->mGap = { 0.0f,0.0f };
	mSquare->mSize = { mSprite->mSize.x,mSprite->mSize.y};*/
	//mSquare->Setting();
}

//<><><><><><><><><><><><><><><><><><>
// 関数名：~SlipperyFloor
// 役割：デストラクタ
//<><><><><><><><><><><><><><><><><><>
SlipperyFloor::~SlipperyFloor()
{
	delete mSquare;
	//COM_SAFE_RELEASE(mTexture);
}

//<><><><><><><><><><><><><><><><><><>
// 関数名：Update
// 役割：更新処理
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
// 関数名：SetLimitTime
// 役割：制限時間設定兼アクティブ化
//<><><><><><><><><><><><><><><><><><>
void SlipperyFloor::SetLimitTime(float _limit)
{
	this->active = true;
	mlimitTime = _limit* 1000.0f;// 制限時間 * 1秒
	mTime = 0.0f;
}

//======================================================================================
// 担当者：		中川直登
// チーム名：	黒棺	
//======================================================================================