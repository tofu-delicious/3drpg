#pragma once
#include "../CharaBase.h"
#include "../../Camera/CameraBase.h"
#include "../../../Kanji/KanjiStock/KanjiStock.h"
#include "../../../Kanji/KanjiUsageHistory/KanjiUsageHistory.h"
#include "../../../Kanji/KanjiComboManager/KanjiComboManager.h"

class C_Player :public C_CharaBase
{

public:

	C_Player(){}
	~C_Player()			override{}

	void Init()			override;
	void Update()		override;
	void PostUpdate()	override;
	void DrawLit()		override;

	//移動処理
	void MovePlayer();

	//行列処理
	void UpdateMatrix();

	//敵ドロップの漢字を拾う処理
	bool PickupKanji(KanjiID a_kanji);

	//手持ちの指定indexの漢字を使用する処理
	void UseKanjiStock(int a_index);

	//現在の漢字使用履歴の取得処理
	const C_KanjiUsageHistory& GetKanjiUsageHistory() const { return m_kanjiUsageHistory; }

	//現在の手持ち漢字ストック一覧をUI表示のために外部公開する取得処理
	const std::vector<KanjiID>& GetKanjiStockList() const { return m_kanjiStock.GetStockList(); }

	//現在のスコア倍率の取得処理
	float GetKanjiScoreMultiplier()const { return m_kanjiComboManager.GetScoreMultiplier(); }

	//地面判定
	void CheckGround();

	//スフィア判定（敵への攻撃判定）
	void CheckSphere();

	//漢字ドロップアイテムの拾得判定を追加
	void CheckKanjiPickup();

	//カメラをセット
	void SetCamera(const std::shared_ptr<CameraBase>& camera)
	{
		m_wpCamera = camera;
	}

private:

	std::weak_ptr<CameraBase> m_wpCamera;

	//手持ち漢字ストック（最大3種類）を保持するメンバ変数
	C_KanjiStock m_kanjiStock;

	//このプレイでの漢字使用履歴（ドロップ抽選の「未使用優先」判定に使う）を保持するメンバ変数
	C_KanjiUsageHistory m_kanjiUsageHistory;

	//多様性コンボとスコア倍率を管理するメンバ変数
	C_KanjiComboManager m_kanjiComboManager;
};