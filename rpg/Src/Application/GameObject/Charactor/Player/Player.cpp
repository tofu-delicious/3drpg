#include "Player.h"
#include "../../../Asset/AssetManager.h"
#include "../../../Scene/SceneManager.h"

void C_Player::Init()
{
	m_spModel = C_AssetManager::Instance().GetModel("Player");

	//デバッグスフィア表示
	if (!m_pDebugWire) m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}

void C_Player::Update()
{
	MovePlayer();		//移動処理

	UpdateMatrix();		//行列処理
}

void C_Player::PostUpdate()
{
	CheckSphere();		//スフィア判定
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

bool C_Player::PickupKanji(KanjiID a_kanji)
{
	//手持ちストックへの追加を試みる
	return m_kanjiStock.AddKanji(a_kanji);
}

void C_Player::UseKanjiStock(int a_index)
{
	//手持ちストックから該当漢字を取り出す（同時に配列からは削除）
	KanjiID _used = m_kanjiStock.UseKanji(a_index);

	//取り出しに失敗（範囲外指定等）した場合は何もせず終了
	if (_used == KanjiID::None)
	{
		return;
	}

	//使用した漢字を「使用済み」として履歴に記録
	m_kanjiUsageHistory.MarkUsed(_used);

	//使用した漢字をコンボ管理へ渡し、コンボ数とスコア倍率を更新
	m_kanjiComboManager.OnUseKanji(_used);

	//ここにコンボ更新・属性ダメージ・レベル効果発動を呼び出す
}

void C_Player::CheckSphere()
{
	//スフィア判定用の変数を宣言
	KdCollider::SphereInfo sphere;
	sphere.m_sphere.Center = m_pos + Math::Vector3(0, 2.3f, 0); //原点が足元なので↑に0.5上げる
	sphere.m_sphere.Radius = 0.3f;
	sphere.m_type = KdCollider::TypeDamage;

	//デバッグ
	m_pDebugWire->AddDebugSphere(sphere.m_sphere.Center, sphere.m_sphere.Radius);

	//➀球に当たったオブジェクト情報を格納するリスト
	std::list<KdCollider::CollisionResult> retSphereList;

	//➁全オブジェクトと当たり判定をする
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		//Intersects（当たり判定を行う関数）
		obj->Intersects(sphere, &retSphereList);
	}

	//球に当たったリストから一番近いオブジェクトを探す
	float maxOverLap = 0.0f;
	bool isHit = false;
	Math::Vector3 hitDir;	//当たった方向を格納する変数
	for (auto& ret : retSphereList)
	{
		//球にめり込んだ長さが一番長いものを探す
		if (maxOverLap < ret.m_overlapDistance)
		{
			//更新
			maxOverLap = ret.m_overlapDistance;
			hitDir = ret.m_hitDir;
			isHit = true;
		}
	}
	if (isHit == true)
	{
		//Z方向への押し出し無効
		hitDir.y = 0.0f;

		//方向ベクトルは長さ1
		hitDir.Normalize();

		m_pos += hitDir * maxOverLap;
	}
}
