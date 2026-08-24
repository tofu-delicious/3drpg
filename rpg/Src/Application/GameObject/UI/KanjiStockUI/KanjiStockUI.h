//プレイヤーの手持ち漢字ストックを画面端にスロット風に表示するUIクラス
#pragma once
#include "../../ObjectBase.h"
#include "../../Charactor/Player/Player.h"

class C_KanjiStockUI : public C_ObjectBase
{
public:

	C_KanjiStockUI(){}
	~C_KanjiStockUI()		override{}

	void Init()				override;		//枠テクスチャのロード処理
	void DrawSprite()		override;		//スロットUIの描画処理

	//表示対象のプレイヤーを外部からセットする処理
	void SetPlayer(const std::shared_ptr<C_Player>& a_spPlayer)
	{
		m_wpPlayer = a_spPlayer;
	};

private:

	std::weak_ptr<C_Player> m_wpPlayer;		//手持ちストックを取得するためのプレイヤー弱参照

	std::shared_ptr<KdTexture> m_spFrameTex = nullptr;	//スロットの枠テクスチャ

	static constexpr int SLOT_SIZE = 64;				//1スロットの表示サイズ
	static constexpr int SLOT_MARGIN = 16;				//スロット同士の間隔
	static constexpr int SCREEN_MARGIN_X = 24;			//画面左端からのXオフセット
	static constexpr int SCREEN_MARGIN_Y = 24;			//画面下端からのYオフセット
	static constexpr int SCREEN_WIDTH_REF = 1280;		//画面幅
	static constexpr int SCREEN_HEIGHT_REF = 720;		//画面の高さ
};