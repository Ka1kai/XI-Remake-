*********************************************
自分用に作ったFramWorkです
*********************************************

CWindowsSystem.cpp,h
ウィンドウの作成やウィンドウのクラスの生成用クラス実装
timeBeginの部分とPeekMessegeの部分更新
デストラクタにてtimeEnd追加。
2013/5/8
　メッセージの受け取り方をGetMessage関数とPeekMessage関数の二つにわけた。

CDirectBase.cpp,h
DirectXのための初期化などを定めたクラス

CDirectGraphics3D.cpp,h
3D描画のためのクラスと処理を定めたクラス

CDirectGraphics2D.cpp,h
2D描画のためのクラスと処理を定めたクラス

CDirectGraphicsSystem.cpp,h
2D,3Dともに描画に必要な処理を定めたクラス

CDirectResource.cpp,h
2D,3D描画に必要なテクスチャの処理を定めたクラス


CDirectInput.cpp,h
入力系機器の情報用クラス実装
ウィンドウハンドルをシングルトンで制御したため必要な部分でGetしている

GameInfo.h
ゲームの定数などをまとめるヘッダー

CConsole.h
コンソールを作成・文字表示を行うためのクラス

CFps.h
FPSを計測・表示・調整するためのクラス

CDirectMeshClone.cpp,h
クローンメッシュ用のクラス