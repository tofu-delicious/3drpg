#include "Player.h"
#include "../../../Asset/AssetManager.h"

void C_Player::Init()
{
	m_spModel = C_AssetManager::Instance().GetModel("Player");
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
	float		_moveSpd = 0.1f;
	Math::Vector3	_nowPos = GetPos();

	Math::Vector3	_moveVec = Math::Vector3::Zero;
	if (GetAsyncKeyState('D')) { _moveVec.x = 1.0f; }
	if (GetAsyncKeyState('A')) { _moveVec.x = -1.0f; }
	if (GetAsyncKeyState('W')) { _moveVec.z = 1.0f; }
	if (GetAsyncKeyState('S')) { _moveVec.z = -1.0f; }

	_moveVec.Normalize();

	// カメラのY軸回転を取得して移動ベクトルをカメラ方向に変換
	const auto _spCamera = m_wpCamera.lock();
	if (_spCamera)
	{
		_moveVec = Math::Vector3::TransformNormal(_moveVec, _spCamera->GetRotationYMatrix());
	}

	_moveVec *= _moveSpd;
	m_pos += _moveVec;
}

void C_Player::UpdateMatrix()
{
	//カメラの回転を反映しないとき（拡縮 + 初期回転）
	Math::Matrix _scale = Math::Matrix::CreateScale(17.0f);
	Math::Matrix _rot   = Math::Matrix::Identity;

	//カメラの回転を反映するとき（拡縮 + カメラ回転）
	const auto _spCamera = m_wpCamera.lock();
	if (_spCamera)
	{
		_rot = _spCamera->GetRotationYMatrix();
	}

	Math::Matrix _trans = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = _scale * _rot * _trans;
}