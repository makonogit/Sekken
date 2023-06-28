//======================================================================================
// ���O�FHitCircle.cpp
// �����F�~�̓����蔻��N���X
//======================================================================================

//------------------------------------
//		include
//------------------------------------

#include "HitCircle.h"

//------------------------------------
//		�����o�[�֐�
//------------------------------------


//<><><><><><><><><><><><><><><><><><>
// �֐����F�R���X�g���N�^
// �����F���W�̎Q�ƂƔ��a�̐ݒ������
// �����FXMFLOAT2�@���W�Afloat�@���a
//<><><><><><><><><><><><><><><><><><>
HitCircle::HitCircle(XMFLOAT2 *_Pos) :mPos{ _Pos }, mRadius{ 1.0f }, active{ true }
{
}

//<><><><><><><><><><><><><><><><><><>
// �֐����F�R���X�g���N�^
// �����F���W�̎Q�ƂƔ��a�̐ݒ������
// �����FXMFLOAT2�@���W�Afloat�@���a
//<><><><><><><><><><><><><><><><><><>
HitCircle::HitCircle(XMFLOAT2* _Pos, float _r) :mPos{ _Pos }, mRadius{ _r }, active{ true }
{
	// �i�V
}

//<><><><><><><><><><><><><><><><><><>
// �֐����F�`�F�b�N�q�b�g
// �����F�~�Ɖ~�̂����蔻��
// �����FHitCircle�@�~
// �߂�l�Ftrue �������Ă��� / false �������Ă��Ȃ�
//<><><><><><><><><><><><><><><><><><>
bool HitCircle::CheckHit(HitCircle* _circle)
{
	// �����蔻�肪off�Ȃ�A������false��Ԃ�
	if (active == false || _circle->active == false)
	{
		return false;
	}
	
	//�@
	float VecX = _circle->mPos->x - mPos->x;
	float VecY = _circle->mPos->y - mPos->y;
	//�A
	float ctc = VecX * VecX + VecY * VecY;
	//�B
	float h1_h2 = _circle->mRadius + mRadius;
	//�C
	return  ctc < h1_h2 * h1_h2;;
}

//<><><><><><><><><><><><><><><><><><>
// �֐����F�`�F�b�N�q�b�g
// �����F�~�Ǝl�p�̂����蔻��
// �����FHitSquare�@�l�p
// �߂�l�Ftrue �������Ă��� / false �������Ă��Ȃ�
//<><><><><><><><><><><><><><><><><><>
bool HitCircle::CheckHit(HitSquare * _square)
{
	// �����蔻�肪off�Ȃ�A������false��Ԃ�
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
//���p�`�̒��_ P[n](xp[n], yp[n]) �i���v���ɒ�`�j
//���p�`���\������x�N�g��V[n] = (vx[n], vy[n])
//�~�̒��S�_ C(xc, yc)
//�~�̔��a r
//���p�`�̒��_����~�̒��S�_�֌������x�N�g�� M[n] = (Mx[n], My[n])
//�@ �����̓����H
//V[n]�EM[n]��0�i�s�p�j����V[n]�EM[n + 1]��0�i�݊p�j�� | V[n]�~M[n]|/|V[n] | ��r�Ȃ�ΏՓ˂��N�����Ă���B
//�A �����̊O���̗�O�P�[�X
//�@�ł͂Ȃ����A(xc - xp[n]) ^ 2 + (yc - yp[n]) ^ 2��r ^ 2��������(xc - xp[n + 1]) ^ 2 + (yc - yp[n + 1]) ^ 2��r ^ 2�Ȃ�ΏՓ˂��N�����Ă���B
//�B �@�ƇA�����ׂĂ̕ӂŐ��藧���Ă��Ȃ����ɁAV[n]�~M[n]��0�i�����̉E���ɒ��_������j�����ׂĂ̕ӂɂ��Č�����Ȃ�Փ˂��N�����Ă���B

//======================================================================================
// �S���ҁF		���쒼�o
// ��������F�@ 2022-12-08
// �`�[�����F	����	
//======================================================================================