//フィールド上に落ちている漢字アイテムを表すクラス
#pragma once
#include "../../GameObject/ObjectBase.h"
#include "../../Kanji/KanjiDefine/KanjiDefine.h"

class C_KanjiDropItem :public C_ObjectBase
{
public:

	C_KanjiDropItem() {}
	~C_KanjiDropItem()	override {}

	void Init()		override;	//モデルロード処理
	void Update()	override;	//更新処理
	void DrawLit()	override;	//描画処理

	//このアイテムが何の漢字かを外部からセットする処理
	void SetKanjiID(KanjiID a_kanji) { m_kanjiID = a_kanji; }

	//このアイテムが何の漢字かを取得する処理
	KanjiID GetKanjiID()const { return m_kanjiID; }

	//生成する際のY軸方向を少し上に補正するための定数
	static constexpr float KANJI_SPAWN_OFFSET_Y = 0.5f;

private:

	KanjiID m_kanjiID = KanjiID::None;	//このドロップアイテムが表す漢字

	float m_rotateAngle = 0.0f;			//回転演出用に枚フレーム加算していく角度
	float m_floatTimer = 0.0f;			//浮遊演出用に枚フレーム加算していく経過時間
};