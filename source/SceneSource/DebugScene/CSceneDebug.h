//----------------------------------------------------
// CSceneDebug 
//	DebugâÊñ ÉVÅ[Éì
//
// @date	2013/12/6
// @author	T.Kawashita
//----------------------------------------------------
#ifndef _C_SCENE_DEBUG_H_
#define _C_SCENE_DEBUG_H_

#include "../../KaiFrameWork/KaiFrameWorkHeader/SceneHeader/CSceneBase.hpp"
#include "../../KaiFrameWork/KaiFrameWorkHeader/SceneHeader/CSceneChange.hpp"

#include "../../KaiFrameWork/KaiFrameWorkHeader/WindowsHeader/CInputKeyboard.hpp"
#include "../../KaiFrameWork/KaiFrameWorkHeader/WindowsHeader/CJoyStick.hpp"
#include "../../KaiFrameWork/KaiFrameWorkHeader/ResourceHeader/CResourceManager.h"

#define FONT_NUM	(6)
#define SELECT_SCENE_COLOR	D3DXCOLOR( 200,0,255,255 )
#define DEFAULT_SCENE_COLOR	D3DXCOLOR( 255,255,255,255 )

class CSceneDebug : public CSceneBase
{
private:
	D3DXCOLOR			m_fontColor[ FONT_NUM ];
	D3DXVECTOR2			m_fontPos[ FONT_NUM ];
	int					m_fontIndex;

public:
	CSceneDebug			 ( void ){}
	CSceneDebug			 ( CSceneChange* change );
	virtual ~CSceneDebug ( void );

public:
	void Initialize	( void ) override;
	void Finalize	( void ) override;
	void Run		( void ) override;
	void Draw		( void ) override;
	bool Load		( void ) override;

};


#endif _C_SCENE_DEBUG_H_