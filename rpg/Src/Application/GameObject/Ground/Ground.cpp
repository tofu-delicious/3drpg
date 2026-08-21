#include "Ground.h"
#include "../../Asset/AssetManager.h"

void C_Ground::Init()
{
	m_spModel = C_AssetManager::Instance().GetModel("Ground");
}

void C_Ground::Update()
{
}

void C_Ground::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel);
}
