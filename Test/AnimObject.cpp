//------------------------------------
//		include
//------------------------------------
#include "AnimObject.h"

//<><><><><><><><><><><><><><><><><><>
// �֐����F AnimObject
// �����F�R���X�g���N�^
//<><><><><><><><><><><><><><><><><><>
AnimObject::AnimObject(XMFLOAT3& _Camera)
{
	mAnimObject = new AnimSprite(_Camera);
	mSprite = mAnimObject;					

	// ���̃N���X���p������Ƃ��̃f�t�H���g�T�C�Y
	mSprite->mSize.x = 0.3f;
	mSprite->mSize.y = 0.3f;

	mHit = new HitCircle(&mAnimObject->mCenter,0.1f);
	
}

//<><><><><><><><><><><><><><><><><><>
// �֐����F ~AnimObject
// �����F�f�X�g���N�^
//<><><><><><><><><><><><><><><><><><>
AnimObject::~AnimObject()
{
	delete mAnimObject;
	delete mHit;
}


//======================================================================================
// �S���ҁF		�����S
// ��������F�@ 2022-12-01
// �`�[�����F	����	
//======================================================================================