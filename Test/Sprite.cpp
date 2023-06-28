//======================================================================================
// ���O�FSprite
// �����F�|���S���̕\��
//======================================================================================

//------------------------------------
//		include
//------------------------------------
#include "Sprite.h"


//���_�X�V
void Sprite::Update()
{
	VERTEX2D vx[6];
	
	vx[0] = { (mCenter.x - mSize.x / 2)*mCamera.z -mCamera.x ,  (mCenter.y - mSize.y / 2)* mCamera.z -mCamera.y , mUV.w , mUV.z ,mColor };	//����
	vx[1] = { (mCenter.x - mSize.x / 2)*mCamera.z -mCamera.x ,  (mCenter.y + mSize.y / 2)* mCamera.z -mCamera.y , mUV.w , mUV.y ,mColor };	//����
	vx[2] = { (mCenter.x + mSize.x / 2)*mCamera.z -mCamera.x ,  (mCenter.y - mSize.y / 2)* mCamera.z -mCamera.y , mUV.x , mUV.z ,mColor };	//�E��
	vx[3] = { (mCenter.x + mSize.x / 2)*mCamera.z -mCamera.x ,  (mCenter.y + mSize.y / 2)* mCamera.z -mCamera.y , mUV.x , mUV.y ,mColor };	//�E��
	vx[4] = vx[2];	//�E��
	vx[5] = vx[1];	//����
	
					//�@Direct3D�\���̂ɃA�N�Z�X����
	DIRECT3D* d3d = Direct3D_Get();
	//�@���_�f�[�^��VRAM�ɑ���
	d3d->context->UpdateSubresource(mpVertexBuffer, 0, NULL, vx, 0, 0);
}

// �`�揈��
void Sprite::Draw()
{
	//�@Direct3D�\���̂ɃA�N�Z�X����
	DIRECT3D* d3d = Direct3D_Get();
	//�@�`��ɏ̂��钸�_�o�b�t�@��I������
	UINT stride = sizeof(VERTEX2D);
	UINT offset = 0;

	//�@�s�N�Z���V�F�[�_�[�Ƀe�N�X�`����n��
	d3d->context->PSSetShaderResources(0, 1, &mpTexture);

	//�@�s�N�Z���V�F�[�_�[�ɃT���v���[��n��
	d3d->context->PSSetSamplers(0, 1, &d3d->samplerPoint);


	d3d->context->IASetVertexBuffers(0, 1, &mpVertexBuffer,	//�@�I�����钸�_�o�b�t�@
		&stride, &offset);


	//�@�`�施��
	d3d->context->Draw(6, 0); //�@�������͒��_��
}

void Sprite::SetColor(RGBA color)
{
	mColor = color;
}

void Sprite::SetTexture(ID3D11ShaderResourceView * pTexture)
{
	mpTexture = pTexture;
}


// �R���X�g���N�^
Sprite::Sprite(XMFLOAT3& _Camera):mCamera{_Camera}
{

	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.ByteWidth = sizeof(VERTEX2D) * 6; // VRAM�Ɋm�ۂ���f�[�^�T�C�Y�B�ʏ�͍����瑗�钸�_�f�[�^�̃T�C�Y�B
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER; // ���_�o�b�t�@�쐬�������Ŏw��B
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;
	//�@Direct3D�\���̂ɃA�N�Z�X����
	DIRECT3D* d3d = Direct3D_Get();
	// �o�b�t�@�쐬�֐��i�f�o�C�X�N���X�̃����o�֐��j���Ăяo��
	//												�����̕ϐ��ɕۑ������
	d3d->device->CreateBuffer(&bufferDesc, NULL, &mpVertexBuffer);

	mCenter.x = 0.0f;
	mCenter.y = 0.0f;
	mSize.x = 1.0f;
	mSize.y = 1.0f;
	mUV.w = 0.0f;//��
	mUV.x = 1.0f;//�E
	mUV.y = 0.0f;//��
	mUV.z = 1.0f;//��
	
	mColor = { 1.0f,1.0f,1.0f,1.0f };

}

// �f�X�g���N�^
Sprite::~Sprite()
{
	//�@���_�o�b�t�@�̉��
	COM_SAFE_RELEASE(mpVertexBuffer);

}


//======================================================================================
// �S���ҁF		���쒼�o
// �`�[�����F	����	
//======================================================================================