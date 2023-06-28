#pragma once
//======================================================================================
// ���O�FMiniMap
// �����F�~�j�}�b�v
//======================================================================================
#include"StaticObject.h"
#include"Dirt.h"

#define MAP_SIZE 1.2f	//�~�j�}�b�v�k����
#define STAGE_HIGHT 30
#define STAGE_WIDTH 40

class MiniMap
{
private:
	
	ID3D11ShaderResourceView* mPlayerPosTex;		//�v���C���[�e�N�X�`��
	ID3D11ShaderResourceView* mDogPosTex;			//���e�N�X�`��
	ID3D11ShaderResourceView* mCatPosTex;			//�L�e�N�X�`��
	ID3D11ShaderResourceView* mDirtPosTex;			//����e�N�X�`��
	ID3D11ShaderResourceView* mBlockPosTex;			//��Q���e�N�X�`��
	ID3D11ShaderResourceView* mMiniMapTex;			//�~�j�}�b�v�e�N�X�`��
	ID3D11ShaderResourceView* mCamera_RangeTex;		//�J�����͈̓e�N�X�`��


	XMFLOAT3 camera = { 0.0f,0.0f,1.0f };			//���̃N���X�̃J����
	Sprite::RGBA color = { 1.0f,1.0f,1.0f,1.0f };	//�w�i�F
	Sprite::RGBA Red   = { 1.0f,0.0f,0.0f,0.5f };	//��
	Sprite::RGBA Green = { 0.0f,1.0f,0.0f,0.5f };	//��
	Sprite::RGBA Blue  = { 0.0f,0.0f,1.0f,0.5f };	//��

public:

	//GameMain�ŋ��L����
	StaticObject* mPlayerPos;		//�v���C���[
	StaticObject* mDogPos;			//��
	StaticObject* mCatPos;			//�L
	StaticObject* mDirtPos[STAGE_HIGHT][STAGE_WIDTH];		//����
	StaticObject* mBlockPos[3];		//��Q��	
	StaticObject* mCamera_Range;	//�J�����͈̔�
	StaticObject* mMiniMap;			//�~�j�}�b�v
	StaticObject* mBack;			//�w�i


	bool active;	//�A�N�e�B�u���
	MiniMap(Dirt * _Dirt[][STAGE_WIDTH],StaticObject *_Block[]);					//�R���X�g���N�^
	~MiniMap();						//�f�X�g���N�^
	void SetActive(bool _active);	//�\�����邩
	void Update();					//�`��
	void Draw();					//�X�V

};

