;hello-os
;TAB=4

	ORG	0x7c00	; Where this program is loaded

	JMP	entry
	DB	0x90
	DB	"HELLOIPL"	; ブートセクタの名前
	DW	512		; 1セクタの大きさ
	DB	1		; クラスタの大きさ
	DW	1		; FATの開始位置
	DB	2		; FATの個数
	DW	224		; ルートディレクトリ領域の大きさ
	DW	2880		; このドライブの大きさ
	DB	0xf0		; メディアのタイプ
	DW	9		; FAT領域の長さ
	DW	18		; セクタ数/1トラック
	DW	2		; ヘッドの数
	DD	0		; パーティションがあると変わる
	DD	2880		; このドライブの大きさ
	DB	0, 0, 0x29	; 作者もよくわからないらしい？
	DD	0xffffffff	; ボリュームシリアル番号
	DB	"HELLO-OS   "	; ディスクの名前
	DB	"FAT12   "	; フォーマットの名前
	RESB	18		; 18バイトあけておく

; body
entry:
	MOV	AX, 0		; レジスタ初期化
	MOV	SS, AX
	MOV	SP, 0x7c00
	MOV	DS, AX
	MOV	ES, AX

	MOV	SI, msg

putloop:
	MOV	AL, [SI]
	ADD	SI, 1		; SIをインクリメント
	CMP	AL, 0
	JE	fin
	MOV	AH, 0x0e	; 1文字表示関数の番号
	MOV	BX, 15		; カラーコード
	INT	0x10		; システムコール
	JMP	putloop
fin:
	HLT
	JMP	fin

msg:
	DB	0x0a, 0x0a	; 改行をふたつ
	DB	"hello, world"
	DB	0x0a
	DB	0

	RESB	0x7dfe - $	; 0x7dfeまで0でうめる

	DB	0x55, 0xaa

	DB	0xf0, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00
	RESB	4600
	DB	0xf0, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00
	RESB	1469432
