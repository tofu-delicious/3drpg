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

	//漢字使用処理
	KanjiID UseKanji(int a_index);

	//漢字ストックリストを取得
	const std::vector<KanjiID>& GetStockList() const { return m_stockList; }

private:

	std::vector<KanjiID> m_stockList;

};