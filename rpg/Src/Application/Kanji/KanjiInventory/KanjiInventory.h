//#pragma once
//#include "../KanjiDefine/KanjiDefine.h"
//#include <vector>
//
//class C_KanjiInventory
//{
//public:
//
//	static const int MAX_ELEMENT_NUM = 3;	//つくりの所持上限（構成は変えず維持）
//
//	//部首情報をセット
//	void SetRadical(RadicalID a_radical) { m_radical = a_radical; }
//
//	//部首情報を取得
//	RadicalID GetRadical() const { return m_radical; }
//
//	//敵からドロップした「つくり」を入手できたかどうか
//	bool AddElement(ElementID a_element);
//
//	const std::vector<ElementID>& GetElementList() const { return m_elementList; }
//
//	const std::vector<KanjiID>& GetKanjiList()	const { return m_kanjiList; }
//
//private:
//
//	void TryComposeKanji(ElementID a_element);
//
//	RadicalID m_radical = RadicalID::None;		//部首情報管理
//
//	std::vector<ElementID> m_elementList;		//つくり可変長配列
//
//	std::vector<KanjiID> m_kanjiList;			//漢字可変長配列
//};