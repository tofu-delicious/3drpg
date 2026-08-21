#include "Player.h"
#include "../../../Asset/AssetManager.h"

void C_Player::Init()
{
	m_spModel = C_AssetManager::Instance().GetModel("Player");

	m_mWorld = Math::Matrix::CreateScale(5.0f);
}

void C_Player::Update()
{
	MovePlayer();		//移動処理

	UpdateMatrix();		//行列処理
}

void C_Player::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}

void C_Player::MovePlayer()
{
	// 移動処理
	float		_moveSpd = 0.05f;
	Math::Vector3	_nowPos = GetPos();

	Math::Vector3	_moveVec = Math::Vector3::Zero;
	if (GetAsyncKeyState('D')) { _moveVec.x = 1.0f; }
	if (GetAsyncKeyState('A')) { _moveVec.x = -1.0f; }
	if (GetAsyncKeyState('W')) { _moveVec.z = 1.0f; }
	if (GetAsyncKeyState('S')) { _moveVec.z = -1.0f; }

	_moveVec.Normalize();
	_moveVec *= _moveSpd;
	m_pos += _moveVec;
}

void C_Player::UpdateMatrix()
{
	Math::Matrix _scale = Math::Matrix::CreateScale(5.0f);
	Math::Matrix _trans = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = _scale * _trans;
}


