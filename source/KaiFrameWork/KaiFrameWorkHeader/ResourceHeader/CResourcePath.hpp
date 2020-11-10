//----------------------------------------------------
// CResourcePath
//	リソースのファイルパスのみを定義したもの
//
// @date	2014/1/14 
// @author	T.Kawashita
//----------------------------------------------------
#ifndef _C_RESOURCE_PATH_H_
#define _C_RESOURCE_PATH_H_

// オブジェクト用ファイルパス
CONST LPSTR PLAYER_PNGPATH  = "resource/2D/player/player.png";	// プレイヤーのファイルパス
CONST LPSTR DICE_XFILEPATH = "resource/xFile/dice.x";			// サイコロのファイルパス
CONST LPSTR PARTICLE_PNGPATH = "resource/2D/particle.png";		// 雪

// タイトル用ファイルパス
CONST LPSTR TITLE_BACK_PNGPATH = "resource/2D/title/titleBack.png";
CONST LPSTR TITLELOG_PNGPATH = "resource/2D/title/title.png";
CONST LPSTR TITLE_REMAKE_PNGPATH = "resource/2D/title/remake.png";
CONST LPSTR PUSHSTART_PNGPATH = "resource/2D/title/pushStartPlay.png";
CONST LPSTR VIEWMODE_PNGPATH = "resource/2D/title/modelViewMode.png";
CONST LPSTR EXIT_PNGPATH = "resource/2D/title/exit.png";
CONST LPSTR TITLEEFFECT_PNGPATH = "resource/2D/title/titleEffect.png";

// モードセレクト用ファイルパス
CONST LPSTR MODE_STAGE_XFILEPATH = "resource/xFile/modeSelectStage.x";
CONST LPSTR MODE_MENU_PNGPATH = "resource/2D/modeselect/menu.png";
CONST LPSTR MODE_TITLEMESSAGE_PNGPATH = "resource/2D/modeselect/title.png";
CONST LPSTR MODE_EXITMESSAGE_PNGPATH = "resource/2D/modeselect/exit.png";
CONST LPSTR MODE_GAMEPLAYMESSAGE_PNGPATH = "resource/2D/modeselect/gameplay.png";
CONST LPSTR MODE_RANKINGMESSAGE_PNGPATH = "resource/2D/modeselect/ranking.png";
CONST LPSTR MODE_RECORDMESSAGE_PNGPATH = "resource/2D/modeselect/record.png";
CONST LPSTR MODE_OPTIONMESSAGE_PNGPATH = "resource/2D/modeselect/option.png";

// ゲーム用ファイルパス
CONST LPSTR GAME_STAGE_XFILEPATH = "resource/xFile/stage.x";
CONST LPSTR GAME_DICEINFO_PNGPATH = "resource/2D/game/info.png";
CONST LPSTR GAME_SCOREVALUE_PNGPATH = "resource/2D/game/score.png";
CONST LPSTR GAME_SCOREDIGIT_PNGPATH = "resource/2D/game/scoreDigit.png";

// タイム用ファイルパス
CONST LPSTR TIME_PNGPATH = "resource/2D/game/time.png";
CONST LPSTR TIMEDIGIT_PNGPATH = "resource/2D/game/timeDigit.png";
CONST LPSTR TIMEUP_PNGPATH = "resource/2D/game/timeup.png";
CONST LPSTR TIMEUP_PUSHENTER_PNGPATH = "resource/2D/game/pushEnter.png";

// ポーズ用ファイルパス
CONST LPSTR PAUSE_BACK_PNGPATH = "resource/2D/pause/back.png";
CONST LPSTR PAUSE_PNGPATH = "resource/2D/pause/pause.png";
CONST LPSTR RETRY_PNGPATH = "resource/2D/pause/retry.png";
CONST LPSTR RESUME_PNGPATH = "resource/2D/pause/resume.png";
CONST LPSTR BACKTITLE_PNGPATH = "resource/2D/pause/backTitle.png";
CONST LPSTR CURSOL_PNGPATH = "resource/2D/pause/cursol.png";
CONST LPSTR PAUSEEFFECT_PNGPATH = "resource/2D/pause/pauseEffect.png";

// デバッグ用ファイルパス
CONST LPSTR DEBUGMODE_PNGPATH = "resource/2D/debug/debugBack.png";

// リザルト用ファイルパス
CONST LPSTR RESULT_RESULTVALUE_PNGPATH = "resource/2D/result/resultValue.png";
CONST LPSTR RESULT_SCOREDIGIT_PNGPATH = "resource/2D/result/scoreDigit.png";
CONST LPSTR RESULT_SCOREVALUE_PNGPATH = "resource/2D/result/scoreValue.png";
CONST LPSTR RESULT_MAXCHAIN_PNGPATH = "resource/2D/result/maxChain.png";
CONST LPSTR RESULT_ONE_PNGPATH = "resource/2D/result/one.png";
CONST LPSTR RESULT_TWO_PNGPATH = "resource/2D/result/two.png";
CONST LPSTR RESULT_THREE_PNGPATH = "resource/2D/result/three.png";
CONST LPSTR RESULT_FOUR_PNGPATH = "resource/2D/result/four.png";
CONST LPSTR RESULT_FIVE_PNGPATH = "resource/2D/result/five.png";
CONST LPSTR RESULT_SIX_PNGPATH = "resource/2D/result/six.png";
CONST LPSTR RESULT_PUSHENTER_PNGPATH = "resource/2D/result/pushEnter.png";

// ハイスコア用ファイルパス
CONST LPSTR SCORE_HIGHSCORE_VALUE_PNGPATH = "resource/2D/highScore/highScore.png"; 

// モデルビュー用ファイルパス
CONST LPSTR modelViewPath = "resource/ModelView/goldskybill.x";

#endif _C_RESOURCE_PATH_H_