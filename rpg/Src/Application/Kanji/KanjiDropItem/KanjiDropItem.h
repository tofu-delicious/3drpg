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

private:

	KanjiID m_kanjiID = KanjiID::None;	//このドロップアイテムが表す漢字
};