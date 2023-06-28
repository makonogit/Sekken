//------------------------------------
//		include
//------------------------------------
#include "AnimSprite.h"

extern DWORD gDeltaTime;

//<><><><><><><><><><><><><><><><><><>
// 関数名： Update
// 役割：更新処理
//<><><><><><><><><><><><><><><><><><>
void AnimSprite::Update()
{
	// アニメーションの処理
	fAnimCnt += fAnimSpeed * gDeltaTime;				// コマを進める

	// コマが最後まで来たら最初に戻す
	if (nAnimTable[(int)fAnimCnt] == -1) // -1が最後のしるし
	{
		fAnimCnt = 0.0f;
	}

	float frameYoko = (int)nAnimTable[(int)fAnimCnt]; // テーブルから現在のコマを取得
	float frameTate = mDirection;					  // キャラの向きを縦コマ番号とする

	float uvWidth = 1.0f / 3.0f;  // キャラクター１コマのUの幅
	float uvHeight = 1.0f / 4.0f; // キャラクター１コマのVの高さ

	float uLeft = frameYoko * uvWidth;
	float uRight = uLeft + uvWidth;
	float vTop = frameTate * uvHeight;
	float vBottom = vTop + uvHeight;

	// mCenterX, mCenterYがキャラクターの中心座標
	// そこからスプライトの４頂点を計算する。
	float charWidth = mSize.x;					// スプライトの横の長さ
	float charHeight = mSize.y;					// スプライトの縦の長さ
	float xLeft = mCenter.x - charWidth / 2.0f;	// スプライトの左端X
	float xRight = xLeft + charWidth;			// スプライトの右端X
	float yTop = mCenter.y + charHeight / 2.0f;	// スプライトの上端Y
	float yBottom = yTop - charHeight;			// スプライトの下端Y

	VERTEX2D vx[6];
	vx[0] = { xLeft  * mCamera.z - mCamera.x , yBottom * mCamera.z - mCamera.y , uLeft , vBottom ,mColor };	//左下
	vx[1] = { xLeft  * mCamera.z - mCamera.x , yTop    * mCamera.z - mCamera.y , uLeft , vTop    ,mColor };	//左上
	vx[2] = { xRight * mCamera.z - mCamera.x , yBottom * mCamera.z - mCamera.y , uRight, vBottom ,mColor };	//右下
	vx[3] = { xRight * mCamera.z - mCamera.x , yTop    * mCamera.z - mCamera.y , uRight, vTop    ,mColor };	//右上
	vx[4] = vx[2];	//右下
	vx[5] = vx[1];	//左上


	// DIRECT3D構造体にアクセスする
	DIRECT3D* d3d = Direct3D_Get();
	// 頂点のデータをVRAMに送る
	d3d->context->UpdateSubresource(mpVertexBuffer, // 転送先の頂点バッファ
		0, NULL, vx, // 転送する配列の名前（=アドレス）
		0, 0);

}

//基底コンストラクタを呼び出す
AnimSprite::AnimSprite(XMFLOAT3& _Camera):Sprite(_Camera)
{}

//======================================================================================
// 担当者：		菅眞心
// 制作日時：　 2022-12-01
// チーム名：	黒棺	
//======================================================================================