//----------------------------------------------------
// CSceneBase Class
//	Sceneの基底クラス
//	 各種シーンに派生させる
//
// @date	2013/6/10
// @auter	T.Kawashita
//----------------------------------------------------
#ifndef _C_SCENE_BASE_H_
#define _C_SCENE_BASE_H_

#include "CSceneChange.hpp"

#include "../DirectX9Header/CDirectX9DrawSystem.h"
#include "../DirectX9Header/CDirectX9Camera.h"

class CSceneBase
{
protected:
    CSceneChange* mSceneChanger;    // クラス所有元にシーン切り替えを伝えるインターフェイス

public:
	// コンストラクタ
    CSceneBase( CSceneChange* changer )
	{
		mSceneChanger = changer;
	}
	CSceneBase(){}
    virtual ~CSceneBase(){}

public:
    virtual void Initialize(){}			// 初期化処理
	virtual void Finalize(){}			// 終了処理
    virtual void Run() {}				// 更新処理
	virtual void Draw(){}				// 描画処理
	virtual bool Load(){return true;}	// ロード処理
};

#endif _C_SCENE_BASE_H_