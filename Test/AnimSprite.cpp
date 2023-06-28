//------------------------------------
//		include
//------------------------------------
#include "AnimSprite.h"

extern DWORD gDeltaTime;

//<><><><><><><><><><><><><><><><><><>
// �֐����F Update
// �����F�X�V����
//<><><><><><><><><><><><><><><><><><>
void AnimSprite::Update()
{
	// �A�j���[�V�����̏���
	fAnimCnt += fAnimSpeed * gDeltaTime;				// �R�}��i�߂�

	// �R�}���Ō�܂ŗ�����ŏ��ɖ߂�
	if (nAnimTable[(int)fAnimCnt] == -1) // -1���Ō�̂��邵
	{
		fAnimCnt = 0.0f;
	}

	float frameYoko = (int)nAnimTable[(int)fAnimCnt]; // �e�[�u�����猻�݂̃R�}���擾
	float frameTate = mDirection;					  // �L�����̌������c�R�}�ԍ��Ƃ���

	float uvWidth = 1.0f / 3.0f;  // �L�����N�^�[�P�R�}��U�̕�
	float uvHeight = 1.0f / 4.0f; // �L�����N�^�[�P�R�}��V�̍���

	float uLeft = frameYoko * uvWidth;
	float uRight = uLeft + uvWidth;
	float vTop = frameTate * uvHeight;
	float vBottom = vTop + uvHeight;

	// mCenterX, mCenterY���L�����N�^�[�̒��S���W
	// ��������X�v���C�g�̂S���_���v�Z����B
	float charWidth = mSize.x;					// �X�v���C�g�̉��̒���
	float charHeight = mSize.y;					// �X�v���C�g�̏c�̒���
	float xLeft = mCenter.x - charWidth / 2.0f;	// �X�v���C�g�̍��[X
	float xRight = xLeft + charWidth;			// �X�v���C�g�̉E�[X
	float yTop = mCenter.y + charHeight / 2.0f;	// �X�v���C�g�̏�[Y
	float yBottom = yTop - charHeight;			// �X�v���C�g�̉��[Y

	VERTEX2D vx[6];
	vx[0] = { xLeft  * mCamera.z - mCamera.x , yBottom * mCamera.z - mCamera.y , uLeft , vBottom ,mColor };	//����
	vx[1] = { xLeft  * mCamera.z - mCamera.x , yTop    * mCamera.z - mCamera.y , uLeft , vTop    ,mColor };	//����
	vx[2] = { xRight * mCamera.z - mCamera.x , yBottom * mCamera.z - mCamera.y , uRight, vBottom ,mColor };	//�E��
	vx[3] = { xRight * mCamera.z - mCamera.x , yTop    * mCamera.z - mCamera.y , uRight, vTop    ,mColor };	//�E��
	vx[4] = vx[2];	//�E��
	vx[5] = vx[1];	//����


	// DIRECT3D�\���̂ɃA�N�Z�X����
	DIRECT3D* d3d = Direct3D_Get();
	// ���_�̃f�[�^��VRAM�ɑ���
	d3d->context->UpdateSubresource(mpVertexBuffer, // �]����̒��_�o�b�t�@
		0, NULL, vx, // �]������z��̖��O�i=�A�h���X�j
		0, 0);

}

//���R���X�g���N�^���Ăяo��
AnimSprite::AnimSprite(XMFLOAT3& _Camera):Sprite(_Camera)
{}

//======================================================================================
// �S���ҁF		�����S
// ��������F�@ 2022-12-01
// �`�[�����F	����	
//======================================================================================