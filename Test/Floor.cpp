//======================================================================================
// ���O�FFloor.h
// �����F���̃w�b�_�[�t�@�C��
//======================================================================================

//------------------------------------
//		include
//------------------------------------

#include "Floor.h"

//------------------------------------
//		�����o�[�֐�
//------------------------------------

//<><><><><><><><><><><><><><><><><><>
// �֐����FFloor
// �����F�R���X�g���N�^
//<><><><><><><><><><><><><><><><><><>
Floor::Floor(XMFLOAT3 & _Camera, int Stage[][STAGE_WIDTH])
{
	LoadTexture(L"assets/Slippery.png", &mSlipperyTexture);						// �҂��҂��̏��e�N�X�`��
	LoadTexture(L"assets/images/BackGround/Dirt_b.png", &mDirtTexture);			// ���ꂽ���e�N�X�`��
	LoadTexture(L"assets/images/Item/Bubble1.png", &mBabbleTex);					// �A�̃e�N�X�`��

	BubbleNum = 0;

	for (int i = 0; i < STAGE_HIGHT; i++)
	{
		for (int j = 0; j < STAGE_WIDTH; j++)
		{
			// ���鏰�̏�����
			mSlippery[i][j] = new SlipperyFloor(_Camera);
			mSlippery[i][j]->mAnimObject->SetTexture(mSlipperyTexture);
			mSlippery[i][j]->SetPosition((-2.32f + mSlippery[i][j]->mSprite->mSize.x / 2) + (mSlippery[i][j]->mSprite->mSize.x * j),
				(1.98f - mSlippery[i][j]->mSprite->mSize.y / 2) - (mSlippery[i][j]->mSprite->mSize.y * i));
			
			// ����̏�����
			mDirt[i][j] = new Dirt(_Camera);
			mDirt[i][j]->mSprite->SetTexture(mDirtTexture);
			mDirt[i][j]->SetPosition((-2.32f + mDirt[i][j]->mSprite->mSize.x / 2) + (mDirt[i][j]->mSprite->mSize.x * j),
				(1.98f - mDirt[i][j]->mSprite->mSize.y / 2) - (mDirt[i][j]->mSprite->mSize.y * i));
			
			SetDirtTex(Stage, i, j);	//����e�N�X�`���ݒ�

			if (Stage[i][j] == 1)
			{
				mDirt[i][j]->SetActive(true);
			}
			else
			{
				mDirt[i][j]->SetActive(false);
			}

			// �A�̏�����
			mBubble[i][j] = new Babble(_Camera);
			mBubble[i][j]->mSprite->SetTexture(mBabbleTex);
			mBubble[i][j]->SetActive(false);		//��A�N�e�B�u�ɂ���

		}
	}
}

//<><><><><><><><><><><><><><><><><><>
// �֐����F~Floor
// �����F�f�X�g���N�^
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
// �֐����FUpdate
// �����F�X�V����
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
// �֐����FDraw
// �����F�`�揈��
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
// �֐����FOnSlipperyFloor
// �����F�҂��҂��̏��ɏ���Ă��邩
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
				mSlippery[i][j]->SetLimitTime(10.0f);	//���鏰��ݒ�
				mDirt[i][j]->active = false;			//������A�N�e�B�u��
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
// �֐����FSetDirtTex
// �����F����̉摜�ݒ�
//<><><><><><><><><><><><><><><><><><>
void Floor::SetDirtTex(int _mapdata[][STAGE_WIDTH], int hight_num, int width_num)
{
	int DirtUP = _mapdata[hight_num - 1][width_num];	//�^��̃}�b�v���
	int DirtDown = _mapdata[hight_num + 1][width_num];	//�^���̃}�b�v���
	int DirtLeft = _mapdata[hight_num][width_num - 1];	//���̃}�b�v���
	int DirtRight = _mapdata[hight_num][width_num + 1]; //�E�̃}�b�v���

	//�}�b�v�[�̏��ݒ�
	if (hight_num == 0) {
		DirtUP = 0;	//��
	}
	if (hight_num == STAGE_HIGHT - 1) {
		DirtDown = 0;		//��
	}
	if (width_num == 0) {
		DirtLeft = 0;	//��
	}
	if (width_num == STAGE_WIDTH - 1) {
		DirtRight = 0;	//�E
	}

	//UV�T�C�Y
	float DirtTipSize_U = 1.0f / 5.0f;	//8����
	float DirtTipSize_V = 1.0f / 4.0f;	//6����

	//���肪�S�ĉ��ꂾ������
	if ((DirtUP == 1 && DirtDown == 1 && DirtLeft == 1 && DirtRight == 1) ||
		(DirtUP == 1 && DirtDown == 1 && DirtLeft == 1 && DirtRight == 1))
	{
		mDirt[hight_num][width_num]->mSprite->mUV.w = DirtTipSize_U * 2.0f;	//������7�Ԗ�(0�n�܂�)
		mDirt[hight_num][width_num]->mSprite->mUV.x = mDirt[hight_num][width_num]->mSprite->mUV.w + DirtTipSize_U;	//�E
		mDirt[hight_num][width_num]->mSprite->mUV.y = DirtTipSize_V * 1.0f;	//�ォ��2�Ԗ�(0�n�܂�)
		mDirt[hight_num][width_num]->mSprite->mUV.z = mDirt[hight_num][width_num]->mSprite->mUV.y + DirtTipSize_V;	//��
	}
	else  //���肪�S�ĉ��ꂶ��Ȃ�������
	{
		mDirt[hight_num][width_num]->mSprite->mUV.w = DirtTipSize_U * 4.0f;	//������4�Ԗ�(0�n�܂�)
		mDirt[hight_num][width_num]->mSprite->mUV.x = mDirt[hight_num][width_num]->mSprite->mUV.w + DirtTipSize_U;	//�E
		mDirt[hight_num][width_num]->mSprite->mUV.y = DirtTipSize_V * 0.0f;	//�ォ��4�Ԗ�(0�n�܂�)
		mDirt[hight_num][width_num]->mSprite->mUV.z = mDirt[hight_num][width_num]->mSprite->mUV.y + DirtTipSize_V;	//��
	}

	//�ゾ�����ꂾ������
	if (DirtUP == 1 && DirtDown == 0 && DirtLeft == 0 && DirtRight == 0)
	{
		mDirt[hight_num][width_num]->mSprite->mUV.w = DirtTipSize_U * 0.0f;	//������1�Ԗ�(0�n�܂�)
		mDirt[hight_num][width_num]->mSprite->mUV.x = mDirt[hight_num][width_num]->mSprite->mUV.w + DirtTipSize_U;	//�E
		mDirt[hight_num][width_num]->mSprite->mUV.y = DirtTipSize_V * 2.0f;	//�ォ��3�Ԗ�(0�n�܂�)
		mDirt[hight_num][width_num]->mSprite->mUV.z = mDirt[hight_num][width_num]->mSprite->mUV.y + DirtTipSize_V;	//��

	}
	//���������ꂾ������
	if (DirtUP == 0 && DirtDown == 1 && DirtLeft == 0 && DirtRight == 0)
	{
		mDirt[hight_num][width_num]->mSprite->mUV.w = DirtTipSize_U * 0.0f;	//������5�Ԗ�(0�n�܂�)
		mDirt[hight_num][width_num]->mSprite->mUV.x = mDirt[hight_num][width_num]->mSprite->mUV.w + DirtTipSize_U;	//�E
		mDirt[hight_num][width_num]->mSprite->mUV.y = DirtTipSize_V * 0.0f;	//�ォ��1�Ԗ�(0�n�܂�)
		mDirt[hight_num][width_num]->mSprite->mUV.z = mDirt[hight_num][width_num]->mSprite->mUV.y + DirtTipSize_V;	//��
	}
	//�㉺�����ꂾ������
	if (DirtUP == 1 && DirtDown == 1 && DirtLeft == 0 && DirtRight == 0)
	{
		mDirt[hight_num][width_num]->mSprite->mUV.w = DirtTipSize_U * 0.0f;	//������5�Ԗ�(0�n�܂�)
		mDirt[hight_num][width_num]->mSprite->mUV.x = mDirt[hight_num][width_num]->mSprite->mUV.w + DirtTipSize_U;	//�E
		mDirt[hight_num][width_num]->mSprite->mUV.y = DirtTipSize_V * 1.0f;	//�ォ��2�Ԗ�(0�n�܂�)
		mDirt[hight_num][width_num]->mSprite->mUV.z = mDirt[hight_num][width_num]->mSprite->mUV.y + DirtTipSize_V;	//��
	}
	//�㉺�������ꂾ������
	if (DirtUP == 1 && DirtDown == 1 && DirtLeft == 1 && DirtRight == 0)
	{
		mDirt[hight_num][width_num]->mSprite->mUV.w = DirtTipSize_U * 3.0f;	//������4�Ԗ�(0�n�܂�)
		mDirt[hight_num][width_num]->mSprite->mUV.x = mDirt[hight_num][width_num]->mSprite->mUV.w + DirtTipSize_U;	//�E
		mDirt[hight_num][width_num]->mSprite->mUV.y = DirtTipSize_V * 1.0f;	//�ォ��2�Ԗ�(0�n�܂�)
		mDirt[hight_num][width_num]->mSprite->mUV.z = mDirt[hight_num][width_num]->mSprite->mUV.y + DirtTipSize_V;	//��
	}
	//�㉺�E�����ꂾ������
	if (DirtUP == 1 && DirtDown == 1 && DirtLeft == 0 && DirtRight == 1)
	{
		mDirt[hight_num][width_num]->mSprite->mUV.w = DirtTipSize_U * 1.0f;	//������2�Ԗ�(0�n�܂�)
		mDirt[hight_num][width_num]->mSprite->mUV.x = mDirt[hight_num][width_num]->mSprite->mUV.w + DirtTipSize_U;	//�E
		mDirt[hight_num][width_num]->mSprite->mUV.y = DirtTipSize_V * 1.0f;	//�ォ��2�Ԗ�(0�n�܂�)
		mDirt[hight_num][width_num]->mSprite->mUV.z = mDirt[hight_num][width_num]->mSprite->mUV.y + DirtTipSize_V;	//��
	}

	//���������ꂾ������
	if (DirtUP == 0 && DirtDown == 0 && DirtLeft == 1 && DirtRight == 0)
	{
		mDirt[hight_num][width_num]->mSprite->mUV.w = DirtTipSize_U * 2.0f;	//������3�Ԗ�(0�n�܂�)
		mDirt[hight_num][width_num]->mSprite->mUV.x = mDirt[hight_num][width_num]->mSprite->mUV.w + DirtTipSize_U;	//�E
		mDirt[hight_num][width_num]->mSprite->mUV.y = DirtTipSize_V * 3.0f;	//�ォ��4�Ԗ�(0�n�܂�)
		mDirt[hight_num][width_num]->mSprite->mUV.z = mDirt[hight_num][width_num]->mSprite->mUV.y + DirtTipSize_V;	//��
	}
	//�E�������ꂾ������
	if (DirtUP == 0 && DirtDown == 0 && DirtLeft == 0 && DirtRight == 1)
	{
		mDirt[hight_num][width_num]->mSprite->mUV.w = DirtTipSize_U * 0.0f;	//������1�Ԗ�(0�n�܂�)
		mDirt[hight_num][width_num]->mSprite->mUV.x = mDirt[hight_num][width_num]->mSprite->mUV.w + DirtTipSize_U;	//�E
		mDirt[hight_num][width_num]->mSprite->mUV.y = DirtTipSize_V * 3.0f;	//�ォ��4�Ԗ�(0�n�܂�)
		mDirt[hight_num][width_num]->mSprite->mUV.z = mDirt[hight_num][width_num]->mSprite->mUV.y + DirtTipSize_V;	//��
	}
	//���E�����ꂾ������
	if (DirtUP == 0 && DirtDown == 0 && DirtLeft == 1 && DirtRight == 1)
	{
		mDirt[hight_num][width_num]->mSprite->mUV.w = DirtTipSize_U * 1.0f;	//������2�Ԗ�(0�n�܂�)
		mDirt[hight_num][width_num]->mSprite->mUV.x = mDirt[hight_num][width_num]->mSprite->mUV.w + DirtTipSize_U;	//�E
		mDirt[hight_num][width_num]->mSprite->mUV.y = DirtTipSize_V * 3.0f;	//�ォ��4�Ԗ�(0�n�܂�)
		mDirt[hight_num][width_num]->mSprite->mUV.z = mDirt[hight_num][width_num]->mSprite->mUV.y + DirtTipSize_V;	//��
	}
	
	//���E�オ���ꂾ������
	if (DirtUP == 1 && DirtDown == 0 && DirtLeft == 1 && DirtRight == 1)
	{
		mDirt[hight_num][width_num]->mSprite->mUV.w = DirtTipSize_U * 2.0f;	//������3�Ԗ�(0�n�܂�)
		mDirt[hight_num][width_num]->mSprite->mUV.x = mDirt[hight_num][width_num]->mSprite->mUV.w + DirtTipSize_U;	//�E
		mDirt[hight_num][width_num]->mSprite->mUV.y = DirtTipSize_V * 2.0f;	//�ォ��3�Ԗ�(0�n�܂�)
		mDirt[hight_num][width_num]->mSprite->mUV.z = mDirt[hight_num][width_num]->mSprite->mUV.y + DirtTipSize_V;	//��
	}
	//���E�������ꂾ������
	if (DirtUP == 0 && DirtDown == 1 && DirtLeft == 1 && DirtRight == 1)
	{
		mDirt[hight_num][width_num]->mSprite->mUV.w = DirtTipSize_U * 2.0f;	//������3�Ԗ�(0�n�܂�)
		mDirt[hight_num][width_num]->mSprite->mUV.x = mDirt[hight_num][width_num]->mSprite->mUV.w + DirtTipSize_U;	//�E
		mDirt[hight_num][width_num]->mSprite->mUV.y = DirtTipSize_V * 0.0f;	//�ォ��1�Ԗ�(0�n�܂�)
		mDirt[hight_num][width_num]->mSprite->mUV.z = mDirt[hight_num][width_num]->mSprite->mUV.y + DirtTipSize_V;	//��
	}

	//���Əオ���ꂾ������
	if (DirtUP == 1 && DirtDown == 0 && DirtLeft == 1 && DirtRight == 0)
	{
		mDirt[hight_num][width_num]->mSprite->mUV.w = DirtTipSize_U * 3.0f;	//������4�Ԗ�(0�n�܂�)
		mDirt[hight_num][width_num]->mSprite->mUV.x = mDirt[hight_num][width_num]->mSprite->mUV.w + DirtTipSize_U;	//�E
		mDirt[hight_num][width_num]->mSprite->mUV.y = DirtTipSize_V * 2.0f;	//�ォ��3�Ԗ�(0�n�܂�)
		mDirt[hight_num][width_num]->mSprite->mUV.z = mDirt[hight_num][width_num]->mSprite->mUV.y + DirtTipSize_V;	//��
	}
	//���Ɖ������ꂾ������
	if (DirtUP == 0 && DirtDown == 1 && DirtLeft == 1 && DirtRight == 0)
	{
		mDirt[hight_num][width_num]->mSprite->mUV.w = DirtTipSize_U * 3.0f;	//������4�Ԗ�(0�n�܂�)
		mDirt[hight_num][width_num]->mSprite->mUV.x = mDirt[hight_num][width_num]->mSprite->mUV.w + DirtTipSize_U;	//�E
		mDirt[hight_num][width_num]->mSprite->mUV.y = DirtTipSize_V * 0.0f;	//�ォ��1�Ԗ�(0�n�܂�)
		mDirt[hight_num][width_num]->mSprite->mUV.z = mDirt[hight_num][width_num]->mSprite->mUV.y + DirtTipSize_V;	//��
	}

	//�E�Əオ���ꂾ������
	if (DirtUP == 1 && DirtDown == 0 && DirtLeft == 0 && DirtRight == 1)
	{
		mDirt[hight_num][width_num]->mSprite->mUV.w = DirtTipSize_U * 1.0f;	//������6�Ԗ�(0�n�܂�)
		mDirt[hight_num][width_num]->mSprite->mUV.x = mDirt[hight_num][width_num]->mSprite->mUV.w + DirtTipSize_U;	//�E
		mDirt[hight_num][width_num]->mSprite->mUV.y = DirtTipSize_V * 2.0f;	//�ォ��3�Ԗ�(0�n�܂�)
		mDirt[hight_num][width_num]->mSprite->mUV.z = mDirt[hight_num][width_num]->mSprite->mUV.y + DirtTipSize_V;	//��
	}
	//�E�Ɖ������ꂾ������
	if (DirtUP == 0 && DirtDown == 1 && DirtLeft == 0 && DirtRight == 1)
	{
		mDirt[hight_num][width_num]->mSprite->mUV.w = DirtTipSize_U * 1.0f;	//������6�Ԗ�(0�n�܂�)
		mDirt[hight_num][width_num]->mSprite->mUV.x = mDirt[hight_num][width_num]->mSprite->mUV.w + DirtTipSize_U;	//�E
		mDirt[hight_num][width_num]->mSprite->mUV.y = DirtTipSize_V * 0.0f;	//�ォ��1�Ԗ�(0�n�܂�)
		mDirt[hight_num][width_num]->mSprite->mUV.z = mDirt[hight_num][width_num]->mSprite->mUV.y + DirtTipSize_V;	//��
	}

}

//<><><><><><><><><><><><><><><><><><>
// �֐����FOffBubble
// �����F�A���A�N�e�B�u��
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
// �S���ҁF		���쒼�o
// �`�[�����F	����	
//======================================================================================