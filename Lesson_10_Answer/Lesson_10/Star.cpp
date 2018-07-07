#include "stdafx.h"
#include "Star.h"
#include "Player.h"

Star::Star(Player& player, CVector3 pos) :
	m_player(player)
{
	m_model.Init(L"Assets/modelData/star.cmo");
	m_model.UpdateWorldMatrix(pos, CQuaternion::Identity(), CVector3::One());
	m_position = pos;
}

Star::~Star()
{
}

void Star::Update()
{
	//Hands-On 2 �v���C���[�ƃR�C���̋������v�Z���āA�擾�o���Ă����玀�S�t���O��true�ɂ���B
	auto vDiff = m_player.GetPosition() - m_position;
	auto len = vDiff.Length();
	if (len < 30.0f) {
		//���S�t���O�𗧂Ă�B
		m_isDead = true;
	}
}
void Star::Draw()
{
	m_model.Draw(g_camera3D.GetViewMatrix(), g_camera3D.GetProjectionMatrix());
}