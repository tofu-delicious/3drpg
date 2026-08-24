#include "KanjiStockUI.h"
#include "../../../Asset/AssetManager.h"
#include "../../../Kanji/KanjiMasterTable/KanjiMasterTable.h"

void C_KanjiStockUI::Init()
{
	m_spFrameTex = C_AssetManager::Instance().GetTex("KanjiFrame");
}

void C_KanjiStockUI::DrawSprite()
{
	//プレイヤーが存在しているかどうか判定
	auto _spPlayer = m_wpPlayer.lock();
	if (!_spPlayer) { return; }

	//プレイヤーが所持している漢字ストック一覧を取得
	const std::vector<KanjiID>& _stockList = _spPlayer->GetKanjiStockList();

	//最大ストック数分だけ、左から順にスロットを並べて描画する
	for (int i = 0; i < C_KanjiStock::MAX_STOCK_NUM; ++i)
	{
		int _x = -SCREEN_WIDTH_REF / 2 + SCREEN_MARGIN_X + (SLOT_SIZE + SLOT_MARGIN) * i;
		int _y = -SCREEN_HEIGHT_REF / 2 + SCREEN_MARGIN_Y;

		//スロットの枠描画
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_spFrameTex.get(), _x, _y, SLOT_SIZE, SLOT_SIZE, nullptr, &kWhiteColor, { 0.0f,0.0f });

		//スロット番号に該当する漢字がストックに存在するかどうかを判定
		if (i >= (int)_stockList.size()) { continue; }

		//ストックに入っているKanjiIDから、マスタデータを検索
		const KanjiMasterData* _pMaster = FindKanjiMaster(_stockList[i]);

		//マスタに存在しないKanjiIDなら描画をスキップする
		if (!_pMaster) { continue; }

		//マスタデータのアイコンキーワードから、AssetManagerに登録済みのテクスチャを取得
		auto _spIconTex = C_AssetManager::Instance().GetTex(_pMaster->iconTexKeyword);

		//アイコンをスロットの中央に重ねて描画
		KdShaderManager::Instance().m_spriteShader.DrawTex(_spIconTex.get(), _x + SLOT_SIZE / 2, _y + SLOT_SIZE / 2, SLOT_SIZE, SLOT_SIZE);
	}
}
