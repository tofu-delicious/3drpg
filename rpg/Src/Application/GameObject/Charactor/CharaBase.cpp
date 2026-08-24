#include "CharaBase.h"

void C_CharaBase::ChangeAnimState(CharaAnimState a_newState, std::string_view a_clipName, bool a_isLoop)
{
	//指定された状態が現在の状態と同じなら終了
	if (m_animState == a_newState) { return; }

	//現在の状態を新しい状態で上書きする
	m_animState = a_newState;

	//モデルワークが未生成なら修正
	if (!m_spModelWork) { return; }

	//モデルワークから指定名のアニメーションクリップを検索して取得
	auto _spClip = m_spModelWork->GetAnimation(a_clipName);

	//取得したクリップをアニメーターにセットし、再生時間をリセットする
	m_animator.SetAnimation(_spClip, a_isLoop);
}

void C_CharaBase::UpdateAnimation()
{
	//モデルワークが未生成なら何もせず終了
	if (!m_spModelWork) { return; }

	//アニメーターの時間を1フレーム進め、各ボーンのローカル行列を更新
	m_animator.AdvanceTime(m_spModelWork->WorkNodes());
}
