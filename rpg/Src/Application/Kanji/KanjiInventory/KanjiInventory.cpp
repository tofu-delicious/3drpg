#include "KanjiInventory.h"
#include "../KanjiRecipe/KanjiRecipeTable.h"

bool C_KanjiInventory::AddElement(ElementID a_element)
{
	if ((int)m_elementList.size() == MAX_ELEMENT_NUM)
	{
		return false;	//所持上限のため取得拒否
	}

	m_elementList.push_back(a_element);

	TryComposeKanji(a_element);	//取得した瞬間に自動判定

	return true;
}

void C_KanjiInventory::TryComposeKanji(ElementID a_element)
{
	//プレイヤーが所持する部首とつくりを用いた漢字が存在するかどうか
	KanjiID _kanji = FindKanji(m_radical, a_element);

	//漢字が存在しなければ終了
	if (_kanji == KanjiID::None)
	{
		return;
	}

	//漢字が存在すれば漢字リストに格納
	m_kanjiList.push_back(_kanji);

	//漢字が作成できた → その漢字制作に使用したつくりは削除する
	auto _it = std::find(m_elementList.begin(), m_elementList.end(), a_element);
	{
		if (_it != m_elementList.end())
		{
			m_elementList.erase(_it);
		}
	}
}
