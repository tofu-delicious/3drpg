//手持ちストック
#pragma once
#include "../KanjiDefine/KanjiDefine.h"

class C_KanjiStock
{
public:

	static const int MAX_STOCK_NUM = 3;		//漢字の最大ストック数

	C_KanjiStock(){}
	~C_KanjiStock(){}

	//true：漢字を拾えた　false：漢字を拾えない
	bool AddKanji(KanjiID a_kanji);

	//指定した並び順（index）の漢字を使用し、手持ちから取り除く処理
	KanjiID UseKanji(int a_index);

	//現在の手持ちリスト情報を取得する
	const std::vector<KanjiID>& GetStockList() const { return m_stockList; }

private:

	//手持ちの漢字を並び順つきで保持する可変長配列
	std::vector<KanjiID> m_stockList;

};