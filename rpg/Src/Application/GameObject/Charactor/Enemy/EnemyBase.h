#pragma once
#include "../CharaBase.h"
#include "../../../Kanji/KanjiDefine/KanjiDefine.h"

class C_EnemyBase:public C_CharaBase
{
public:
	C_EnemyBase(){}
	virtual ~C_EnemyBase()		override{}

	//敵に刻まれた漢字をセット
	void SetBodyKanji(KanjiID a_kanji) { m_bodyKanji = a_kanji; }

	//敵に刻まれた漢字を取得
	KanjiID GetBodyKanji() const { return m_bodyKanji; }

	//弱点属性をセット
	void SetWeakAttribute(KanjiAttribute a_attr) { m_weakAttribute = a_attr; }

	//弱点属性を取得
	KanjiAttribute GetWeakAttribute() const { return m_weakAttribute; }

	//漢字ドロップ処理
	virtual KanjiID OnDefeated() { return m_bodyKanji; }

private:

	KanjiID			m_bodyKanji		= KanjiID::None;			//敵に刻まれた漢字
	KanjiAttribute	m_weakAttribute = KanjiAttribute::None;		//敵の弱点属性
};