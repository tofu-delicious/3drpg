#include "KanjiDropItem.h"
#include ".././../Asset/AssetManager.h"

void C_KanjiDropItem::Init()
{
	m_spModel = C_AssetManager::Instance().GetModel("Hi");

	m_mWorld = Math::Matrix::CreateTranslation(m_pos);
}

void C_KanjiDropItem::Update()
{
	//回転角度を毎フレーム加算
	m_rotateAngle += 0.02f;

	//1周超えたら0に戻す
	if (m_rotateAngle >= DirectX::XM_2PI) m_rotateAngle -= DirectX::XM_2PI;

	//浮遊演出用の経過時間を毎フレーム加算
	m_floatTimer += 0.05f;

	//経過時間をsin波に通し、-0.2 ～ +0.2の範囲で上下に往復するオフセットを計算
	float _floatOffsetY = sinf(m_floatTimer) * 0.2f;

	//Y軸周りに回転させる行列を生成
	Math::Matrix _rotY = Math::Matrix::CreateRotationY(m_rotateAngle);
	Math::Matrix _trans = Math::Matrix::CreateTranslation(m_pos + Math::Vector3{ 0.0f,_floatOffsetY,0.0f });
	m_mWorld = _rotY * _trans;

}

void C_KanjiDropItem::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}

