#pragma once
#include "../ObjectBase.h"

//アニメーション状態を表す構造体
enum class CharaAnimState
{
	None,	//未初期化
	Idle,	//待機
	Walk,	//歩行
	Run,	//走行
	Attack,	//攻撃
	Dying,	//死亡
};

class C_CharaBase :public C_ObjectBase
{
public:

	C_CharaBase(){}
	virtual ~C_CharaBase()	override{}

	//アニメーション状態を変更する処理
	void ChangeAnimState(CharaAnimState a_newState, std::string_view a_clipName, bool a_isLoop = true);

	//アニメーションをiフレーム分進める処理
	void UpdateAnimation();

protected:

	//現在のアニメーション状態を保持するメンバ変数
	CharaAnimState m_animState = CharaAnimState::None;

	//アニメーション再生の進行を管理するメンバ変数
	KdAnimator m_animator;
};