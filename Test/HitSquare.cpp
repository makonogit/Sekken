//======================================================================================
// ���O�FHitSquare.h
// �����F�l�p�̓����蔻��N���X
//======================================================================================

//------------------------------------
//		include
//------------------------------------
#include "HitSquare.h"

//------------------------------------
//		�����o�[�֐�
//------------------------------------


//<><><><><><><><><><><><><><><><><><>
// �֐����F�R���X�g���N�^
// �����F���W�̎Q�ƂƔ��a�̐ݒ������
// �����FXMFLOAT2�@���W
//<><><><><><><><><><><><><><><><><><>
HitSquare::HitSquare(XMFLOAT2* _pos):mPos{ _pos } , mAngle{ 0.0f }, active{ true }
{
	XMFLOAT2 size = { 1.0f,1.0f };
	mSize = size;
	XMFLOAT2 gap = { 0.0f,0.0f };
	mGap = gap;
}

//<><><><><><><><><><><><><><><><><><>
// �֐����F�R���X�g���N�^
// �����F���W�̎Q�ƂƔ��a�̐ݒ������
// �����FXMFLOAT2�@���W�AXMFLOAT2�@�T�C�Y�AXMFLOAT2�@���炷�Afloat�@�p�x
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
// �֐����F�`�F�b�N�q�b�g
// �����F�l�p�Ǝl�p�̂����蔻��
// �����FHitSquare �l�p
// �߂�l�Ftrue �������Ă��� / false �������Ă��Ȃ�
//<><><><><><><><><><><><><><><><><><>
bool HitSquare::CheckHit(HitSquare* _square)
{
	// �����蔻�肪off�Ȃ�A������false��Ԃ�
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
// �S���ҁF		���쒼�o
// ��������F�@ 2022-12-08
// �`�[�����F	����	
//======================================================================================