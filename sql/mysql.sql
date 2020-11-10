/*データベース作成*/
CREATE DATABASE XI_RemakeDB;

/*データベース選択*/
use XI_RemakeDB;

/*ユーザテーブル作成*/
create table User( 
userID VARCHAR(10) UNIQUE KEY,
name  VARCHAR(10) NOT NULL,
id VARCHAR(10) NOT NULL,
pass VARCHAR(10) NOT NULL,
PRIMARY KEY(userID,name)
);

/*scoreテーブル作成*/
create table Score(
scoreID VARCHAR(10),
record INT(10),
onePip INT(3),
twoPip INT(3),
threePip INT(3),
fourPip INT(3),
fivePip INT(3),
sixPip INT(3),
maxChain INT(3),
userID VARCHAR(10) NOT NULL,
userName VARCHAR(10) NOT NULL,
PRIMARY KEY(scoreID),	
FOREIGN KEY(userID,userName) REFERENCES user(userID,name) ON DELETE CASCADE
);	

/*Scoreテーブル用Insert*/
INSERT INTO User Values('U000000','test','test','test');
INSERT INTO score values('S000000',0,0,0,0,0,0,0,0,'U000000','test');

/*Userが作成された時に自動的にスコアを0クリアしてスコアテーブルを作成するトリガ*/
drop trigger insertusertri;
DELIMITER //
CREATE TRIGGER insertusertri AFTER INSERT ON user FOR EACH ROW
BEGIN
/*現在のスコアテーブルの最大Noを取得するための変数*/
DECLARE triMaxScoreId VARCHAR(10);
DECLARE triMaxScoreWork VARCHAR(1);

/*スコアIDを取得するための変数*/
DECLARE triScoreId VARCHAR(8);

/*一番左の文字を取得*/
SELECT SubStr(Max(scoreID), 1, 1) INTO triMaxScoreWork FROM score;

/*その他の数字の部分を抜出し数値に変換後，左を0埋めして保存している文字を左につける*/
SELECT CONCAT(triMaxScoreWork,
LPAD( SUBSTR(MAX(scoreID),2,7) + 1, 6 ,'0' ) )
INTO triMaxScoreId FROM score;

/*スコアテーブルに追加する*/
INSERT INTO score values(triMaxScoreId,0,0,0,0,0,0,0,0,New.userID,New.name);
END;
//

DELIMITER ;

/*テストデータ用*/

INSERT INTO User Values('U000001','test','test','test');
INSERT INTO User Values('U000002','punpuku','1234abcd','abcd1234');


