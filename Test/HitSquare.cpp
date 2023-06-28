//======================================================================================
// 名前：HitSquare.h
// 説明：四角の当たり判定クラス
//======================================================================================

//------------------------------------
//		include
//------------------------------------
#include "HitSquare.h"

//------------------------------------
//		メンバー関数
//------------------------------------


//<><><><><><><><><><><><><><><><><><>
// 関数名：コンストラクタ
// 役割：座標の参照と半径の設定をする
// 引数：XMFLOAT2　座標
//<><><><><><><><><><><><><><><><><><>
HitSquare::HitSquare(XMFLOAT2* _pos):mPos{ _pos } , mAngle{ 0.0f }, active{ true }
{
	XMFLOAT2 size = { 1.0f,1.0f };
	mSize = size;
	XMFLOAT2 gap = { 0.0f,0.0f };
	mGap = gap;
}

//<><><><><><><><><><><><><><><><><><>
// 関数名：コンストラクタ
// 役割：座標の参照と半径の設定をする
// 引数：XMFLOAT2　座標、XMFLOAT2　サイズ、XMFLOAT2　ずらす、float　角度
//<><><><><><><><><><><><><><><><><><>
HitSquare::HitSquare(XMFLOAT2* _pos, XMFLOAT2 _size, XMFLOAT2 _gap, float _angle):mPos{_pos},mGap{_gap},mAngle{_angle},active{true}
{
	/*float X = (x + w / 1.41421356) - x;
	float Y = (y - h / 1.41421356) - y;
	this->R = sqrt(X * X + Y * Y);
	this->ragian3 = acos(X / R);*/
	mSize.x = _size.x / 2;
	mSize.y = _size.y / 2;
	mDiagonal = sqrt(mSize.x *mSize.x + mSize.y * mSize.y);
	mDiagonalAng = acos(mSize.x / mDiagonal);
}

//<><><><><><><><><><><><><><><><><><>
// 関数名：チェックヒット
// 役割：四角と四角のあたり判定
// 引数：HitSquare 四角
// 戻り値：true 当たっている / false 当たっていない
//<><><><><><><><><><><><><><><><><><>
bool HitSquare::CheckHit(HitSquare* _square)
{
	// あたり判定がoffなら、すぐにfalseを返す
	if (active == false || _square->active == false)
	{
		return false;
	}
	float ragian = mAngle * (PI / 180);
	XMFLOAT2 vertexA[4] = 
	{
		{ mPos->x + mGap.x + cosf(ragian - mDiagonalAng + PI) * mDiagonal	,mPos->y + mGap.y + sinf(ragian - mDiagonalAng + PI) * mDiagonal	 },
		{ mPos->x + mGap.x + cosf(ragian + mDiagonalAng + PI) * mDiagonal	,mPos->y + mGap.y + sinf(ragian + mDiagonalAng + PI) * mDiagonal	 },
		{ mPos->x + mGap.x + cosf(ragian - mDiagonalAng) * mDiagonal			,mPos->y + mGap.y + sinf(ragian - mDiagonalAng) * mDiagonal		 },
		{ mPos->x + mGap.x + cosf(ragian + mDiagonalAng) * mDiagonal			,mPos->y + mGap.y + sinf(ragian + mDiagonalAng) * mDiagonal		 },
	};

	ragian = _square->mAngle * (PI / 180);
	XMFLOAT2 vertexB[4] =
	{
		{ _square->mPos->x + _square->mGap.x + cosf(ragian - _square->mDiagonalAng + PI) * _square->mDiagonal	,_square->mPos->y + _square->mGap.y + sinf(ragian - _square->mDiagonalAng + PI) * _square->mDiagonal	 },
		{ _square->mPos->x + _square->mGap.x + cosf(ragian + _square->mDiagonalAng + PI) * _square->mDiagonal	,_square->mPos->y + _square->mGap.y + sinf(ragian + _square->mDiagonalAng + PI) * _square->mDiagonal	 },
		{ _square->mPos->x + _square->mGap.x + cosf(ragian - _square->mDiagonalAng) * _square->mDiagonal			,_square->mPos->y + _square->mGap.y + sinf(ragian - _square->mDiagonalAng) * _square->mDiagonal		 },
		{ _square->mPos->x + _square->mGap.x + cosf(ragian + _square->mDiagonalAng) * _square->mDiagonal			,_square->mPos->y + _square->mGap.y + sinf(ragian + _square->mDiagonalAng) * _square->mDiagonal		 },
	};
	int Hit = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if ((((vertexA[(j + 1) % 4].x - vertexA[j].x)*(vertexB[i].y - vertexA[j].y)) - ((vertexB[i].x - vertexA[j].x)*(vertexA[(j + 1) % 4].y - vertexA[j].y))) >= 0)
			{
				Hit++;
			}
		}
		if (Hit == 4)
		{
			return true;
		}
		Hit = 0;
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if ((((vertexB[(j + 1) % 4].x - vertexB[j].x)*(vertexA[i].y - vertexB[j].y)) - ((vertexA[i].x - vertexB[j].x)*(vertexB[(j + 1) % 4].y - vertexB[j].y))) >= 0)
			{
				Hit++;
			}
		}
		if (Hit == 4)
		{
			return true;
		}
		Hit = 0;
	}
	return false;
}

//======================================================================================
// 担当者：		中川直登
// 制作日時：　 2022-12-08
// チーム名：	黒棺	
//======================================================================================