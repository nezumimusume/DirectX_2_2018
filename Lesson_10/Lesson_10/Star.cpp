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
	//Hands-On 2 プレイヤーとコインの距離を計算して、取得出来ていたら死亡フラグをtrueにする。

}
void Star::Draw()
{
	m_model.Draw(g_camera3D.GetViewMatrix(), g_camera3D.GetProjectionMatrix());
}
