#pragma once
#include "../CharaBase.h"
#include "../../../Kanji/KanjiDefine/KanjiDefine.h"
#include "../../../Kanji/KanjiUsageHistory/KanjiUsageHistory.h"

class C_EnemyBase:public C_CharaBase
{
public:
	C_EnemyBase(){}
	virtual ~C_EnemyBase()		override{}

	//各敵がドロップする漢字をプレイヤーの使用履歴を参照して出現時に決定する
	void DecideBodyKanji(const C_KanjiUsageHistory& a_history);

	//各敵がドロップする漢字の内容を取得
	KanjiID GetBodyKanji() const { return m_bodyKanji; }

	//弱点属性セット
	void SetWeekAttribute(KanjiAttribute a_attr) { m_weakAttribute = a_attr; }

	//弱点属性情報の取得
	KanjiAttribute GetWeakAttribute() const { return m_weakAttribute; }

	//敵撃破時、ドロップする漢字を返す
	virtual KanjiID OnDefeated() { return m_bodyKanji; }

private:

	KanjiID			m_bodyKanji		= KanjiID::None;			//敵に刻まれた漢字
	KanjiAttribute	m_weakAttribute = KanjiAttribute::None;		//敵の弱点属性
};