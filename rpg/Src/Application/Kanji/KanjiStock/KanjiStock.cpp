#include "KanjiStock.h"

bool C_KanjiStock::AddKanji(KanjiID a_kanji)
{
	if ((int)m_stockList.size() >= MAX_STOCK_NUM)
	{
		return false;	//満杯なため拾えない
	}

	m_stockList.push_back(a_kanji);
	return true;
}

KanjiID C_KanjiStock::UseKanji(int a_index)
{
	if (a_index < 0 || a_index >= (int)m_stockList.size())
	{
		return KanjiID::None;
	}
	KanjiID _used = m_stockList[a_index];
	m_stockList.erase(m_stockList.begin() + a_index);	//即消費

	return _used;
}
