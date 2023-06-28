//======================================================================================
// 名前：Floor.h
// 説明：床のヘッダーファイル
//======================================================================================

//------------------------------------
//		include
//------------------------------------

#include "Floor.h"

//------------------------------------
//		メンバー関数
//------------------------------------

//<><><><><><><><><><><><><><><><><><>
// 関数名：Floor
// 役割：コンストラクタ
//<><><><><><><><><><><><><><><><><><>
Floor::Floor(XMFLOAT3 & _Camera, int Stage[][STAGE_WIDTH])
{
	LoadTexture(L"assets/Slippery.png", &mSlipperyTexture);						// ぴかぴかの床テクスチャ
	LoadTexture(L"assets/images/BackGround/Dirt_b.png", &mDirtTexture);			// 汚れた床テクスチャ
	LoadTexture(L"assets/images/Item/Bubble1.png", &mBabbleTex);					// 泡のテクスチャ

	BubbleNum = 0;

	for (int i = 0; i < STAGE_HIGHT; i++)
	{
		for (int j = 0; j < STAGE_WIDTH; j++)
		{
			// 滑る床の初期化
			mSlippery[i][j] = new SlipperyFloor(_Camera);
			mSlippery[i][j]->mAnimObject->SetTexture(mSlipperyTexture);
			mSlippery[i][j]->SetPosition((-2.32f + mSlippery[i][j]->mSprite->mSize.x / 2) + (mSlippery[i][j]->mSprite->mSize.x * j),
				(1.98f - mSlippery[i][j]->mSprite->mSize.y / 2) - (mSlippery[i][j]->mSprite->mSize.y * i));
			
			// 汚れの初期化
			mDirt[i][j] = new Dirt(_Camera);
			mDirt[i][j]->mSprite->SetTexture(mDirtTexture);
			mDirt[i][j]->SetPosition((-2.32f + mDirt[i][j]->mSprite->mSize.x / 2) + (mDirt[i][j]->mSprite->mSize.x * j),
				(1.98f - mDirt[i][j]->mSprite->mSize.y / 2) - (mDirt[i][j]->mSprite->mSize.y * i));
			
			SetDirtTex(Stage, i, j);	//汚れテクスチャ設定

			if (Stage[i][j] == 1)
			{
				mDirt[i][j]->SetActive(true);
			}
			else
			{
				mDirt[i][j]->SetActive(false);
			}

			// 泡の初期化
			mBubble[i][j] = new Babble(_Camera);
			mBubble[i][j]->mSprite->SetTexture(mBabbleTex);
			mBubble[i][j]->SetActive(false);		//非アクティブにする

		}
	}
}

//<><><><><><><><><><><><><><><><><><>
// 関数名：~Floor
// 役割：デストラクタ
//<><><><><><><><><><><><><><><><><><>
Floor::~Floor()
{

	for (int i = 0; i < STAGE_HIGHT; i++)
	{
		for (int j = 0; j < STAGE_WIDTH; j++)
		{
			delete mSlippery[i][j];
			delete mDirt[i][j];
			delete mBubble[i][j];
			//delete
		}
	}
	COM_SAFE_RELEASE(mSlipperyTexture);
	COM_SAFE_RELEASE(mDirtTexture);
	COM_SAFE_RELEASE(mBabbleTex);
}

//<><><><><><><><><><><><><><><><><><>
// 関数名：Update
// 役割：更新処理
//<><><><><><><><><><><><><><><><><><>
void Floor::Update()
{

	for (int i = 0; i < STAGE_HIGHT; i++)
	{
		for (int j = 0; j < STAGE_WIDTH; j++)
		{
			mSlippery[i][j]->Update();
			mDirt[i][j]->Update();
			mBubble[i][j]->Update();
		}
	}
}

//<><><><><><><><><><><><><><><><><><>
// 関数名：Draw
// 役割：描画処理
//<><><><><><><><><><><><><><><><><><>
void Floor::Draw()
{

	for (int i = 0; i < STAGE_HIGHT; i++)
	{
		for (int j = 0; j < STAGE_WIDTH; j++)
		{
			if (mSlippery[i][j]->active) {
				mSlippery[i][j]->Draw();
			}
			if (mDirt[i][j]->active) {
				mDirt[i][j]->Draw();
			}
		}
	}

	for (int i = 0; i < STAGE_HIGHT; i++)
	{
		for (int j = 0; j < STAGE_WIDTH; j++)
		{
			
			if (mBubble[i][j]->active) {
				mBubble[i][j]->Draw();
			}
		}
	}


}
//<><><><><><><><><><><><><><><><><><>
// 関数名：OnSlipperyFloor
// 役割：ぴかぴかの床に乗っているか
//<><><><><><><><><><><><><><><><><><>
bool Floor::OnSlipperyFloor(HitCircle * _circle)
{
	for (int i = 0; i < STAGE_HIGHT; i++)
	{
		for (int j = 0; j < STAGE_WIDTH; j++)
		{
			if (mSlippery[i][j]->active == true) {
				if (_circle->CheckHit(mSlippery[i][j]->mSquare))
				{
					return true;	
				}

			}
		}
	}
	return false;
}

void Floor::Clean()
{
	for (int i = 0; i < STAGE_HIGHT; i++)
	{
		for (int j = 0; j < STAGE_WIDTH; j++)
		{
			if (mDirt[i][j]->mHitDog == true)
			{
				mSlippery[i][j]->SetLimitTime(10.0f);	//滑る床を設定
				mDirt[i][j]->active = false;			//汚れを非アクティブに
				mDirt[i][j]->mHitDog = false;
			}
		}
	}
}

void Floor::Miss()
{
	for (int i = 0; i < STAGE_HIGHT; i++)
	{
		for (int j = 0; j < STAGE_WIDTH; j++)
		{
			if (mDirt[i][j]->mHitDog == true)
			{
				mDirt[i][j]->mHitDog = false;
			}
		}
	}
}

//<><><><><><><><><><><><><><><><><><>
// 関数名：SetDirtTex
// 役割：汚れの画像設定
//<><><><><><><><><><><><><><><><><><>
void Floor::SetDirtTex(int _mapdata[][STAGE_WIDTH], int hight_num, int width_num)
{
	int DirtUP = _mapdata[hight_num - 1][width_num];	//真上のマップ情報
	int DirtDown = _mapdata[hight_num + 1][width_num];	//真下のマップ情報
	int DirtLeft = _mapdata[hight_num][width_num - 1];	//左のマップ情報
	int DirtRight = _mapdata[hight_num][width_num + 1]; //右のマップ情報

	//マップ端の情報設定
	if (hight_num == 0) {
		DirtUP = 0;	//上
	}
	if (hight_num == STAGE_HIGHT - 1) {
		DirtDown = 0;		//下
	}
	if (width_num == 0) {
		DirtLeft = 0;	//左
	}
	if (width_num == STAGE_WIDTH - 1) {
		DirtRight = 0;	//右
	}

	//UVサイズ
	float DirtTipSize_U = 1.0f / 5.0f;	//8分割
	float DirtTipSize_V = 1.0f / 4.0f;	//6分割

	//周りが全て汚れだったら
	if ((DirtUP == 1 && DirtDown == 1 && DirtLeft == 1 && DirtRight == 1) ||
		(DirtUP == 1 && DirtDown == 1 && DirtLeft == 1 && DirtRight == 1))
	{
		mDirt[hight_num][width_num]->mSprite->mUV.w = DirtTipSize_U * 2.0f;	//左から7番目(0始まり)
		mDirt[hight_num][width_num]->mSprite->mUV.x = mDirt[hight_num][width_num]->mSprite->mUV.w + DirtTipSize_U;	//右
		mDirt[hight_num][width_num]->mSprite->mUV.y = DirtTipSize_V * 1.0f;	//上から2番目(0始まり)
		mDirt[hight_num][width_num]->mSprite->mUV.z = mDirt[hight_num][width_num]->mSprite->mUV.y + DirtTipSize_V;	//下
	}
	else  //周りが全て汚れじゃなかったら
	{
		mDirt[hight_num][width_num]->mSprite->mUV.w = DirtTipSize_U * 4.0f;	//左から4番目(0始まり)
		mDirt[hight_num][width_num]->mSprite->mUV.x = mDirt[hight_num][width_num]->mSprite->mUV.w + DirtTipSize_U;	//右
		mDirt[hight_num][width_num]->mSprite->mUV.y = DirtTipSize_V * 0.0f;	//上から4番目(0始まり)
		mDirt[hight_num][width_num]->mSprite->mUV.z = mDirt[hight_num][width_num]->mSprite->mUV.y + DirtTipSize_V;	//下
	}

	//上だけ汚れだったら
	if (DirtUP == 1 && DirtDown == 0 && DirtLeft == 0 && DirtRight == 0)
	{
		mDirt[hight_num][width_num]->mSprite->mUV.w = DirtTipSize_U * 0.0f;	//左から1番目(0始まり)
		mDirt[hight_num][width_num]->mSprite->mUV.x = mDirt[hight_num][width_num]->mSprite->mUV.w + DirtTipSize_U;	//右
		mDirt[hight_num][width_num]->mSprite->mUV.y = DirtTipSize_V * 2.0f;	//上から3番目(0始まり)
		mDirt[hight_num][width_num]->mSprite->mUV.z = mDirt[hight_num][width_num]->mSprite->mUV.y + DirtTipSize_V;	//下

	}
	//下だけ汚れだったら
	if (DirtUP == 0 && DirtDown == 1 && DirtLeft == 0 && DirtRight == 0)
	{
		mDirt[hight_num][width_num]->mSprite->mUV.w = DirtTipSize_U * 0.0f;	//左から5番目(0始まり)
		mDirt[hight_num][width_num]->mSprite->mUV.x = mDirt[hight_num][width_num]->mSprite->mUV.w + DirtTipSize_U;	//右
		mDirt[hight_num][width_num]->mSprite->mUV.y = DirtTipSize_V * 0.0f;	//上から1番目(0始まり)
		mDirt[hight_num][width_num]->mSprite->mUV.z = mDirt[hight_num][width_num]->mSprite->mUV.y + DirtTipSize_V;	//下
	}
	//上下が汚れだったら
	if (DirtUP == 1 && DirtDown == 1 && DirtLeft == 0 && DirtRight == 0)
	{
		mDirt[hight_num][width_num]->mSprite->mUV.w = DirtTipSize_U * 0.0f;	//左から5番目(0始まり)
		mDirt[hight_num][width_num]->mSprite->mUV.x = mDirt[hight_num][width_num]->mSprite->mUV.w + DirtTipSize_U;	//右
		mDirt[hight_num][width_num]->mSprite->mUV.y = DirtTipSize_V * 1.0f;	//上から2番目(0始まり)
		mDirt[hight_num][width_num]->mSprite->mUV.z = mDirt[hight_num][width_num]->mSprite->mUV.y + DirtTipSize_V;	//下
	}
	//上下左が汚れだったら
	if (DirtUP == 1 && DirtDown == 1 && DirtLeft == 1 && DirtRight == 0)
	{
		mDirt[hight_num][width_num]->mSprite->mUV.w = DirtTipSize_U * 3.0f;	//左から4番目(0始まり)
		mDirt[hight_num][width_num]->mSprite->mUV.x = mDirt[hight_num][width_num]->mSprite->mUV.w + DirtTipSize_U;	//右
		mDirt[hight_num][width_num]->mSprite->mUV.y = DirtTipSize_V * 1.0f;	//上から2番目(0始まり)
		mDirt[hight_num][width_num]->mSprite->mUV.z = mDirt[hight_num][width_num]->mSprite->mUV.y + DirtTipSize_V;	//下
	}
	//上下右が汚れだったら
	if (DirtUP == 1 && DirtDown == 1 && DirtLeft == 0 && DirtRight == 1)
	{
		mDirt[hight_num][width_num]->mSprite->mUV.w = DirtTipSize_U * 1.0f;	//左から2番目(0始まり)
		mDirt[hight_num][width_num]->mSprite->mUV.x = mDirt[hight_num][width_num]->mSprite->mUV.w + DirtTipSize_U;	//右
		mDirt[hight_num][width_num]->mSprite->mUV.y = DirtTipSize_V * 1.0f;	//上から2番目(0始まり)
		mDirt[hight_num][width_num]->mSprite->mUV.z = mDirt[hight_num][width_num]->mSprite->mUV.y + DirtTipSize_V;	//下
	}

	//左だけ汚れだったら
	if (DirtUP == 0 && DirtDown == 0 && DirtLeft == 1 && DirtRight == 0)
	{
		mDirt[hight_num][width_num]->mSprite->mUV.w = DirtTipSize_U * 2.0f;	//左から3番目(0始まり)
		mDirt[hight_num][width_num]->mSprite->mUV.x = mDirt[hight_num][width_num]->mSprite->mUV.w + DirtTipSize_U;	//右
		mDirt[hight_num][width_num]->mSprite->mUV.y = DirtTipSize_V * 3.0f;	//上から4番目(0始まり)
		mDirt[hight_num][width_num]->mSprite->mUV.z = mDirt[hight_num][width_num]->mSprite->mUV.y + DirtTipSize_V;	//下
	}
	//右だけ汚れだったら
	if (DirtUP == 0 && DirtDown == 0 && DirtLeft == 0 && DirtRight == 1)
	{
		mDirt[hight_num][width_num]->mSprite->mUV.w = DirtTipSize_U * 0.0f;	//左から1番目(0始まり)
		mDirt[hight_num][width_num]->mSprite->mUV.x = mDirt[hight_num][width_num]->mSprite->mUV.w + DirtTipSize_U;	//右
		mDirt[hight_num][width_num]->mSprite->mUV.y = DirtTipSize_V * 3.0f;	//上から4番目(0始まり)
		mDirt[hight_num][width_num]->mSprite->mUV.z = mDirt[hight_num][width_num]->mSprite->mUV.y + DirtTipSize_V;	//下
	}
	//左右が汚れだったら
	if (DirtUP == 0 && DirtDown == 0 && DirtLeft == 1 && DirtRight == 1)
	{
		mDirt[hight_num][width_num]->mSprite->mUV.w = DirtTipSize_U * 1.0f;	//左から2番目(0始まり)
		mDirt[hight_num][width_num]->mSprite->mUV.x = mDirt[hight_num][width_num]->mSprite->mUV.w + DirtTipSize_U;	//右
		mDirt[hight_num][width_num]->mSprite->mUV.y = DirtTipSize_V * 3.0f;	//上から4番目(0始まり)
		mDirt[hight_num][width_num]->mSprite->mUV.z = mDirt[hight_num][width_num]->mSprite->mUV.y + DirtTipSize_V;	//下
	}
	
	//左右上が汚れだったら
	if (DirtUP == 1 && DirtDown == 0 && DirtLeft == 1 && DirtRight == 1)
	{
		mDirt[hight_num][width_num]->mSprite->mUV.w = DirtTipSize_U * 2.0f;	//左から3番目(0始まり)
		mDirt[hight_num][width_num]->mSprite->mUV.x = mDirt[hight_num][width_num]->mSprite->mUV.w + DirtTipSize_U;	//右
		mDirt[hight_num][width_num]->mSprite->mUV.y = DirtTipSize_V * 2.0f;	//上から3番目(0始まり)
		mDirt[hight_num][width_num]->mSprite->mUV.z = mDirt[hight_num][width_num]->mSprite->mUV.y + DirtTipSize_V;	//下
	}
	//左右下が汚れだったら
	if (DirtUP == 0 && DirtDown == 1 && DirtLeft == 1 && DirtRight == 1)
	{
		mDirt[hight_num][width_num]->mSprite->mUV.w = DirtTipSize_U * 2.0f;	//左から3番目(0始まり)
		mDirt[hight_num][width_num]->mSprite->mUV.x = mDirt[hight_num][width_num]->mSprite->mUV.w + DirtTipSize_U;	//右
		mDirt[hight_num][width_num]->mSprite->mUV.y = DirtTipSize_V * 0.0f;	//上から1番目(0始まり)
		mDirt[hight_num][width_num]->mSprite->mUV.z = mDirt[hight_num][width_num]->mSprite->mUV.y + DirtTipSize_V;	//下
	}

	//左と上が汚れだったら
	if (DirtUP == 1 && DirtDown == 0 && DirtLeft == 1 && DirtRight == 0)
	{
		mDirt[hight_num][width_num]->mSprite->mUV.w = DirtTipSize_U * 3.0f;	//左から4番目(0始まり)
		mDirt[hight_num][width_num]->mSprite->mUV.x = mDirt[hight_num][width_num]->mSprite->mUV.w + DirtTipSize_U;	//右
		mDirt[hight_num][width_num]->mSprite->mUV.y = DirtTipSize_V * 2.0f;	//上から3番目(0始まり)
		mDirt[hight_num][width_num]->mSprite->mUV.z = mDirt[hight_num][width_num]->mSprite->mUV.y + DirtTipSize_V;	//下
	}
	//左と下が汚れだったら
	if (DirtUP == 0 && DirtDown == 1 && DirtLeft == 1 && DirtRight == 0)
	{
		mDirt[hight_num][width_num]->mSprite->mUV.w = DirtTipSize_U * 3.0f;	//左から4番目(0始まり)
		mDirt[hight_num][width_num]->mSprite->mUV.x = mDirt[hight_num][width_num]->mSprite->mUV.w + DirtTipSize_U;	//右
		mDirt[hight_num][width_num]->mSprite->mUV.y = DirtTipSize_V * 0.0f;	//上から1番目(0始まり)
		mDirt[hight_num][width_num]->mSprite->mUV.z = mDirt[hight_num][width_num]->mSprite->mUV.y + DirtTipSize_V;	//下
	}

	//右と上が汚れだったら
	if (DirtUP == 1 && DirtDown == 0 && DirtLeft == 0 && DirtRight == 1)
	{
		mDirt[hight_num][width_num]->mSprite->mUV.w = DirtTipSize_U * 1.0f;	//左から6番目(0始まり)
		mDirt[hight_num][width_num]->mSprite->mUV.x = mDirt[hight_num][width_num]->mSprite->mUV.w + DirtTipSize_U;	//右
		mDirt[hight_num][width_num]->mSprite->mUV.y = DirtTipSize_V * 2.0f;	//上から3番目(0始まり)
		mDirt[hight_num][width_num]->mSprite->mUV.z = mDirt[hight_num][width_num]->mSprite->mUV.y + DirtTipSize_V;	//下
	}
	//右と下が汚れだったら
	if (DirtUP == 0 && DirtDown == 1 && DirtLeft == 0 && DirtRight == 1)
	{
		mDirt[hight_num][width_num]->mSprite->mUV.w = DirtTipSize_U * 1.0f;	//左から6番目(0始まり)
		mDirt[hight_num][width_num]->mSprite->mUV.x = mDirt[hight_num][width_num]->mSprite->mUV.w + DirtTipSize_U;	//右
		mDirt[hight_num][width_num]->mSprite->mUV.y = DirtTipSize_V * 0.0f;	//上から1番目(0始まり)
		mDirt[hight_num][width_num]->mSprite->mUV.z = mDirt[hight_num][width_num]->mSprite->mUV.y + DirtTipSize_V;	//下
	}

}

//<><><><><><><><><><><><><><><><><><>
// 関数名：OffBubble
// 役割：泡を非アクティブ化
//<><><><><><><><><><><><><><><><><><>
void Floor::OffBubble()
{
	for (int i = 0; i < STAGE_HIGHT; i++)
	{
		for (int j = 0; j < STAGE_WIDTH; j++)
		{
			if (mBubble[i][j]->active)
			{
				mBubble[i][j]->active = false;
			}
		}
	}
}

//======================================================================================
// 担当者：		中川直登
// チーム名：	黒棺	
//======================================================================================