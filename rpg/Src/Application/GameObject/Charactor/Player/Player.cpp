#include "Player.h"
#include "../../../Asset/AssetManager.h"

void C_Player::Init()
{
	m_spModel = C_AssetManager::Instance().GetModel("Player");

	m_mWorld = Math::Matrix::CreateScale(10.0f);
}

void C_Player::Update()
{

}

void C_Player::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}