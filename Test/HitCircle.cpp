//======================================================================================
// 名前：HitCircle.cpp
// 説明：円の当たり判定クラス
//======================================================================================

//------------------------------------
//		include
//------------------------------------

#include "HitCircle.h"

//------------------------------------
//		メンバー関数
//------------------------------------


//<><><><><><><><><><><><><><><><><><>
// 関数名：コンストラクタ
// 役割：座標の参照と半径の設定をする
// 引数：XMFLOAT2　座標、float　半径
//<><><><><><><><><><><><><><><><><><>
HitCircle::HitCircle(XMFLOAT2 *_Pos) :mPos{ _Pos }, mRadius{ 1.0f }, active{ true }
{
}

//<><><><><><><><><><><><><><><><><><>
// 関数名：コンストラクタ
// 役割：座標の参照と半径の設定をする
// 引数：XMFLOAT2　座標、float　半径
//<><><><><><><><><><><><><><><><><><>
HitCircle::HitCircle(XMFLOAT2* _Pos, float _r) :mPos{ _Pos }, mRadius{ _r }, active{ true }
{
	// ナシ
}

//<><><><><><><><><><><><><><><><><><>
// 関数名：チェックヒット
// 役割：円と円のあたり判定
// 引数：HitCircle　円
// 戻り値：true 当たっている / false 当たっていない
//<><><><><><><><><><><><><><><><><><>
bool HitCircle::CheckHit(HitCircle* _circle)
{
	// あたり判定がoffなら、すぐにfalseを返す
	if (active == false || _circle->active == false)
	{
		return false;
	}
	
	//①
	float VecX = _circle->mPos->x - mPos->x;
	float VecY = _circle->mPos->y - mPos->y;
	//②
	float ctc = VecX * VecX + VecY * VecY;
	//③
	float h1_h2 = _circle->mRadius + mRadius;
	//④
	return  ctc < h1_h2 * h1_h2;;
}

//<><><><><><><><><><><><><><><><><><>
// 関数名：チェックヒット
// 役割：円と四角のあたり判定
// 引数：HitSquare　四角
// 戻り値：true 当たっている / false 当たっていない
//<><><><><><><><><><><><><><><><><><>
bool HitCircle::CheckHit(HitSquare * _square)
{
	// あたり判定がoffなら、すぐにfalseを返す
	if (active == false || _square->active == false)
	{
		return false;
	}
	float ragian = _square->mAngle * (PI / 180);
	XMFLOAT2 vertex[4] =
	{
		{ _square->mPos->x + _square->mGap.x + cosf(ragian - _square->mDiagonalAng + PI) * _square->mDiagonal	,_square->mPos->y + _square->mGap.y + sinf(ragian - _square->mDiagonalAng + PI) * _square->mDiagonal	 },
		{ _square->mPos->x + _square->mGap.x + cosf(ragian + _square->mDiagonalAng + PI) * _square->mDiagonal	,_square->mPos->y + _square->mGap.y + sinf(ragian + _square->mDiagonalAng + PI) * _square->mDiagonal	 },
		{ _square->mPos->x + _square->mGap.x + cosf(ragian - _square->mDiagonalAng) * _square->mDiagonal			,_square->mPos->y + _square->mGap.y + sinf(ragian - _square->mDiagonalAng) * _square->mDiagonal		 },
		{ _square->mPos->x + _square->mGap.x + cosf(ragian + _square->mDiagonalAng) * _square->mDiagonal			,_square->mPos->y + _square->mGap.y + sinf(ragian + _square->mDiagonalAng) * _square->mDiagonal		 },
	};
	XMFLOAT2 vectorS[4];
	for (int i = 0; i < 4; i++)
	{
		vectorS[i] = { vertex[(i + 1) % 4].x - vertex[i].x, vertex[(i + 1) % 4].y - vertex[i].y };
	}
	XMFLOAT2 vectorM[4];
	for (int i = 0; i < 4; i++)
	{
		vectorM[i] = { mPos->x - vertex[i].x, mPos->y - vertex[i].y };
	}

	for (int i = 0; i < 4; i++)
	{
		bool condition01 = vectorS[i].x * vectorM[i].x + vectorS[i].y * vectorM[i].y >= 0;//Dot(vectorS[i],vectorM[i])>=0
		bool condition02 = vectorS[i].x * vectorM[(i + 1) % 4].x + vectorS[i].y * vectorM[(i + 1) % 4].y <= 0;//Dot(vectorS[i],vectorM[(i+1)%4])<=0
		bool condition03 = fabs(vectorS[i].x * vectorM[i].y - vectorS[i].y * vectorM[i].x) / fabs(vectorS[i].x * vectorS[i].x + vectorS[i].y * vectorS[i].y) <= mRadius;//fabs(Cross(vectorS[i],vectorM[i]))/
		if (condition01 && condition02 && condition03)
		{
			return true;
		}
	}
	for (int i = 0; i < 4; i++)
	{
		float X = mPos->x - vertex[i].x;
		float Y = mPos->y - vertex[i].y;
		
		if (X * X + Y * Y <= mRadius * mRadius )
		{
			return true;
		}
	}
	int hit = 0;
	for (int i = 0; i < 4; i++)
	{
		if(vectorS[i].x * vectorM[i].y - vectorS[i].y * vectorM[i].x >= 0)
		{
			hit+=1;
		}
	}
	if (hit >= 4)
	{
		return true;
	}
	return false;

}
//多角形の頂点 P[n](xp[n], yp[n]) （時計回りに定義）
//多角形を構成するベクトルV[n] = (vx[n], vy[n])
//円の中心点 C(xc, yc)
//円の半径 r
//多角形の頂点から円の中心点へ向かうベクトル M[n] = (Mx[n], My[n])
//① 線分の内側？
//V[n]・M[n]≧0（鋭角）且つV[n]・M[n + 1]≦0（鈍角）で | V[n]×M[n]|/|V[n] | ≦rならば衝突を起こしている。
//② 線分の外側の例外ケース
//①ではない時、(xc - xp[n]) ^ 2 + (yc - yp[n]) ^ 2≦r ^ 2もしくは(xc - xp[n + 1]) ^ 2 + (yc - yp[n + 1]) ^ 2≦r ^ 2ならば衝突を起こしている。
//③ ①と②がすべての辺で成り立っていない時に、V[n]×M[n]≦0（線分の右側に頂点がある）がすべての辺について言えるなら衝突を起こしている。

//======================================================================================
// 担当者：		中川直登
// 制作日時：　 2022-12-08
// チーム名：	黒棺	
//======================================================================================