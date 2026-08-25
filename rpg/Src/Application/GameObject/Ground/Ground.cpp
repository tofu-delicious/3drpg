#include "Ground.h"
#include "../../Asset/AssetManager.h"

void C_Ground::Init()
{
	m_spModel = C_AssetManager::Instance().GetModel("Ground");

	//当たり判定
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("Ground", m_spModel, KdCollider::TypeGround);
}

void C_Ground::Update()
{
}

void C_Ground::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel);
}
