#include "Player.h"
#include "../../../Asset/AssetManager.h"
#include "../../../Scene/SceneManager.h"
#include "../../../Kanji/KanjiDropItem/KanjiDropItem.h"

void C_Player::Init()
{
	//モデルデータ取得
	m_spModel = C_AssetManager::Instance().GetModel("Player");

	//アニメーション再生用のモデルワークを生成
	m_spModelWork = std::make_shared<KdModelWork>(m_spModel);

	//初期状態として待機アニメーションを再生
	//ChangeAnimState(CharaAnimState::Idle, "Idle_Loop");
	ChangeAnimState(CharaAnimState::Idle, "Armature|Armature|Idle_Loop");

	//デバッグスフィア表示
	if (!m_pDebugWire) m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}

void C_Player::Update()
{
	MovePlayer();		//移動処理

	UpdateAnimation();	//アニメーションを1フレーム進める処理

	UpdateMatrix();		//行列処理
}

void C_Player::PostUpdate()
{
	CheckGround();		//地面判定

	CheckSphere();		//スフィア判定
	
	CheckKanjiPickup();	//漢字ドロップアイテムの拾得判定
}

void C_Player::DrawLit()
{
	//アニメーション反映後のモデルワークを描画
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModelWork, m_mWorld);

	//静的モデルは描画しない
	//KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}

void C_Player::MovePlayer()
{
	// 移動処理
	float		_moveSpd = 0.1f;
	Math::Vector3	_nowPos = GetPos();

	Math::Vector3	_moveVec = Math::Vector3::Zero;
	if (GetAsyncKeyState('D') & 0x8000) { _moveVec.x = 1.0f; }
	if (GetAsyncKeyState('A') & 0x8000) { _moveVec.x = -1.0f; }
	if (GetAsyncKeyState('W') & 0x8000) { _moveVec.z = 1.0f; }
	if (GetAsyncKeyState('S') & 0x8000) { _moveVec.z = -1.0f; }

	//移動入力の有無でアニメーションを切り替える
	if (_moveVec == Math::Vector3::Zero)
	{
		//ChangeAnimState(CharaAnimState::Idle, "Idle_Loop");	//Player
		ChangeAnimState(CharaAnimState::Idle, "Armature|Armature|Idle_Loop");	//Player
	}
	else
	{
		ChangeAnimState(CharaAnimState::Run, "Armature|Armature|Sprint_Loop");		//Player
	}

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
	Math::Matrix _scale = Math::Matrix::CreateScale(1.0f);
	Math::Matrix _rot   = Math::Matrix::Identity;

	//モデルが正面を向くのを補正する
	//Math::Matrix _modelFix = Math::Matrix::CreateRotationY(DirectX::XM_PI);

	//カメラの回転を反映するとき（拡縮 + カメラ回転）
	const auto _spCamera = m_wpCamera.lock();
	if (_spCamera)
	{
		_rot = _spCamera->GetRotationYMatrix();
	}

	Math::Matrix _trans = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = _scale /** _modelFix*/ * _rot * _trans;
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

void C_Player::CheckGround()
{
	//地面判定用のレイ情報を宣言している
	KdCollider::RayInfo _rayInfo;

	//レイの発射位置：現在のプレイヤー座標より少し上（地面にめり込んだ状態から判定を始めないため）
	_rayInfo.m_pos = m_pos + Math::Vector3(0, 1.0f, 0);

	//レイの発射方向：真下に向けて飛ばしている
	_rayInfo.m_dir = Math::Vector3::Down;

	//レイが届く距離を設定している（地面まで十分届く長さを確保）
	_rayInfo.m_range = 1000.0f;

	//当たり判定をしたいタイプを「地形」に設定している
	_rayInfo.m_type = KdCollider::TypeGround;

	//レイに当たったオブジェクトの詳細結果を格納するリストを宣言している
	std::list<KdCollider::CollisionResult> _retRayList;

	//シーン上の全オブジェクトに対してレイ判定を実行している
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		obj->Intersects(_rayInfo, &_retRayList);
	}

	//一番近い地面のヒット情報を探すための変数を宣言している
	float _maxOverlap = 0.0f;
	Math::Vector3 _hitPos = {};
	bool _isHit = false;

	//ヒットリストの中から、プレイヤーに一番近い地面の座標を検索している
	for (auto& ret : _retRayList)
	{
		//overlapDistanceが大きいほどレイの発射位置に近いヒットを意味する
		if (_maxOverlap < ret.m_overlapDistance)
		{
			_maxOverlap = ret.m_overlapDistance;
			_hitPos = ret.m_hitPos;
			_isHit = true;
		}
	}

	//地面にヒットしていれば、プレイヤーのY座標を地面の高さに固定している
	if (_isHit)
	{
		m_pos.y = _hitPos.y;
	}
}

void C_Player::CheckSphere()
{
	//スフィア判定用の変数を宣言
	KdCollider::SphereInfo sphere;
	sphere.m_sphere.Center = m_pos + Math::Vector3(0, 2.3f, 0); //原点が足元なので↑に0.5上げる
	sphere.m_sphere.Radius = 0.3f;
	sphere.m_type = KdCollider::TypeDamage;

	//デバッグ
	//m_pDebugWire->AddDebugSphere(sphere.m_sphere.Center, sphere.m_sphere.Radius);

	//➀球に当たったオブジェクト情報を格納するリスト
	std::list<KdCollider::CollisionResult> retSphereList;

	//➁全オブジェクトと当たり判定をする
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		//Intersects（当たり判定を行う関数）：実際に当たっていればtrueが返る
		bool _isHit = obj->Intersects(sphere, &retSphereList);

		if (_isHit)
		{
			obj->OnHit();
		}
	}
}

void C_Player::CheckKanjiPickup()
{
	//拾得判定用の変数を宣言
	KdCollider::SphereInfo sphere;
	sphere.m_sphere.Center = m_pos + Math::Vector3{ 0,0.5f,0 };
	sphere.m_sphere.Radius = 0.3f;
	sphere.m_type = KdCollider::TypeDamage;

	//球に当たったオブジェクト情報を格納するリスト
	std::list<KdCollider::CollisionResult> _retSphereList;

	//全オブジェクトと当たり判定
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		bool _isHit = obj->Intersects(sphere, &_retSphereList);

		//当たっていなければ次のオブジェクトへ
		if (!_isHit) { continue; }

		//当たったオブジェクトが漢字ドロップアイテムかどうかをダウンキャストして判定
		auto _pDropItem = std::dynamic_pointer_cast<C_KanjiDropItem>(obj);

		//漢字ドロップアイテム以外は拾得対象外なのでスキップ
		if (!_pDropItem) { continue; }

		//手持ちストックに空きがある場合のみ、漢字を拾いアイテム側を消滅させる
		if (PickupKanji(_pDropItem->GetKanjiID()))
		{
			_pDropItem->OnHit();
		}

		//ストックが満杯で拾えなかった場合はアイテムを消さずそのまま残す
	}
}
