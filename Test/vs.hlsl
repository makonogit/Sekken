
// ���_�V�F�[�_�[�̃��C���֐�
// �����F�e���_�̑΂��čs�������ړ��E��]�E�k���Ȃǂ����s����
// �߂�l�F���̃V�F�[�_�[�̏����̌��ʂ��A���_�̃f�[�^�Ƃ��Ė߂�
// ���� inputPos�FVRAM�ɓ]�����ꂽ���_�f�[�^�i�̂����P�j���n�����
//      C����Őݒ肵�����_���W�Ɠ������W�n

// return�p�̍\����
struct VS_OUTPUT
{
	float4 pos : SV_Position;
	float2 uv  : TEXCOORD;
	float4 col : COLOR;
};

VS_OUTPUT vs_main(float4 inputPos : POSITION, // xy
	float2 uv : TEX, float4 col : COL) // uv
{
	VS_OUTPUT output;

	output.pos = inputPos;  // �n���ꂽxy��uv��ϐ��Ɉڂ�
	output.uv = uv;
	output.col = col;

	// ��ʔ䗦�ŉ����ɂȂ��Ă��܂��̂𒲐�����
	output.pos.x *= 480.0f / 640.0f;

    return output;
}