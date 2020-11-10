/*�f�[�^�x�[�X�쐬*/
CREATE DATABASE XI_RemakeDB;

/*�f�[�^�x�[�X�I��*/
use XI_RemakeDB;

/*���[�U�e�[�u���쐬*/
create table User( 
userID VARCHAR(10) UNIQUE KEY,
name  VARCHAR(10) NOT NULL,
id VARCHAR(10) NOT NULL,
pass VARCHAR(10) NOT NULL,
PRIMARY KEY(userID,name)
);

/*score�e�[�u���쐬*/
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

/*Score�e�[�u���pInsert*/
INSERT INTO User Values('U000000','test','test','test');
INSERT INTO score values('S000000',0,0,0,0,0,0,0,0,'U000000','test');

/*User���쐬���ꂽ���Ɏ����I�ɃX�R�A��0�N���A���ăX�R�A�e�[�u�����쐬����g���K*/
drop trigger insertusertri;
DELIMITER //
CREATE TRIGGER insertusertri AFTER INSERT ON user FOR EACH ROW
BEGIN
/*���݂̃X�R�A�e�[�u���̍ő�No���擾���邽�߂̕ϐ�*/
DECLARE triMaxScoreId VARCHAR(10);
DECLARE triMaxScoreWork VARCHAR(1);

/*�X�R�AID���擾���邽�߂̕ϐ�*/
DECLARE triScoreId VARCHAR(8);

/*��ԍ��̕������擾*/
SELECT SubStr(Max(scoreID), 1, 1) INTO triMaxScoreWork FROM score;

/*���̑��̐����̕����𔲏o�����l�ɕϊ���C����0���߂��ĕۑ����Ă��镶�������ɂ���*/
SELECT CONCAT(triMaxScoreWork,
LPAD( SUBSTR(MAX(scoreID),2,7) + 1, 6 ,'0' ) )
INTO triMaxScoreId FROM score;

/*�X�R�A�e�[�u���ɒǉ�����*/
INSERT INTO score values(triMaxScoreId,0,0,0,0,0,0,0,0,New.userID,New.name);
END;
//

DELIMITER ;

/*�e�X�g�f�[�^�p*/

INSERT INTO User Values('U000001','test','test','test');
INSERT INTO User Values('U000002','punpuku','1234abcd','abcd1234');


