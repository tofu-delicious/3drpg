#include "RadicalEnemy.h"
#include "../../../../Asset/AssetManager.h"
#include "../../../../Scene/SceneManager.h"
#include "../../../../Kanji/KanjiDropItem/KanjiDropItem.h"

void C_RadicalEnemy::Init()
{
	m_spModel = C_AssetManager::Instance().GetModel("RadicalEnemy");

	m_spModelWork = std::make_shared<KdModelWork>(m_spModel);
	
	m_mWorld = Math::Matrix::Identity;

	//デバッグスフィア表示
	if (!m_pDebugWire) m_pDebugWire = std::make_unique<KdDebugWireFrame>();

	//プレイヤーと衝突される側の処理
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("RadicalEnemy", m_spModel, KdCollider::Type::TypeDamage);

	//仮：RadicalEnemyの弱点造成を水に設定
	SetWeekAttribute(KanjiAttribute::Water);
}

void C_RadicalEnemy::Update()
{
	ChangeAnimState(CharaAnimState::Idle, "Armature|Idle_Loop");

	UpdateAnimation();

	//行列を更新しないと、初期位置にずっと敵が生成されてしまう
	Math::Matrix _scale = Math::Matrix::CreateScale(17.0f);
	Math::Matrix _trans = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = _scale * _trans;
}

void C_RadicalEnemy::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModelWork, m_mWorld);
	//KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel,m_mWorld);
}

void C_RadicalEnemy::OnHit()
{
	//存在を削除
	m_isExpired = true;

	//漢字を生成
	auto _pKanjiDropItem = std::make_shared<C_KanjiDropItem>();
	//撃破時にドロップする漢字IDをセット
	_pKanjiDropItem->SetKanjiID(OnDefeated());
	//自身が消えた座標を生成するアイテムの座標として指定
	_pKanjiDropItem->SetPos(Math::Vector3{GetPos().x,GetPos().y + _pKanjiDropItem.get()->KANJI_SPAWN_OFFSET_Y,GetPos().z});
	//m_objListに追加
	_pKanjiDropItem->Init();
	SceneManager::Instance().AddObject(_pKanjiDropItem);
}
