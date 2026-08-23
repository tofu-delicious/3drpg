//多様性コンボ
#pragma once
#include "../KanjiDefine/KanjiDefine.h"

class C_KanjiComboManager
{
public:

	C_KanjiComboManager(){}
	~C_KanjiComboManager(){}

	//直近の漢字と今回の漢字が同じかどうかの判定処理（漢字を使用する際に呼び出す）
	void OnUseKanji(KanjiID a_kanji);
	
	//現在のスコア倍率の取得処理
	float GetScoreMultiplier()const { return m_scoreMultiplier; }

	//現在のコンボ数をUI表示等に使うための取得処理
	int GetComboCount()const { return m_comboCount; }

private:

	KanjiID m_lastUsedKanji   = KanjiID::None;	//直近に使用した漢字を記憶しておくメンバ変数
	int		m_comboCount	  = 0;				//現在何連続で異なる漢字を使えているかを数えるメンバ変数
	float	m_scoreMultiplier = 1.0f;			//現在のスコア倍率を保持するメンバ変数

};