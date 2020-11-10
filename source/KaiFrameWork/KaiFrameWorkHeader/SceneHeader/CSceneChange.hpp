//----------------------------------------------------
// CSceneChangeClass 
//	Sceneを変更するためのクラス
//
// @date	2013/6/13
// @author  T.Kawashita
//----------------------------------------------------
#ifndef _C_SCENE_CHANGE_H_
#define _C_SCENE_CHANGE_H_

typedef enum 
{
	eSceneTitle,
    eSceneModeSelect,	// モードセレクト画面
	eSceneHighScore,	// スコア表示画面 
    eSceneGame,			// ゲーム画面
    eSceneResult,		// リザルト
	eSceneConfig,		// 設定画面
	eSceneModelView,	// モデルビューワー
	eSceneDebug,		// デバッグ画面

    eScene_None,	    // 無し
}eSceneState;

class CSceneChange
{
public:
	CSceneChange(){};
	virtual ~CSceneChange(){}

public:
    virtual void ChangeScene( eSceneState NextScene ) = 0;//指定シーンに変更する
};

#endif _C_SCENE_CHANGE_H_