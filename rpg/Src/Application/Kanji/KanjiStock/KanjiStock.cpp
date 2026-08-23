#include "KanjiStock.h"

bool C_KanjiStock::AddKanji(KanjiID a_kanji)
{
	//現在の所持数が上限（3）以上かどうかを判定
	if ((int)m_stockList.size() >= MAX_STOCK_NUM)
	{
		return false;	//満杯なため拾えない
	}

	//配列の末尾に新たな漢字を追加
	m_stockList.push_back(a_kanji);
	return true;
}

KanjiID C_KanjiStock::UseKanji(int a_index)
{
	//指定indexが配列の範囲外かどうかを判定
	if (a_index < 0 || a_index >= (int)m_stockList.size())
	{
		return KanjiID::None;
	}

	//削除する前に、使用する漢字の値を一時変数にコピーして保持
	KanjiID _used = m_stockList[a_index];

	//指定インデックスの要素を配列から削除（即消費）
	m_stockList.erase(m_stockList.begin() + a_index);	//即消費

	//使用した漢字の値を呼び出し元へ返す
	return _used;
}
