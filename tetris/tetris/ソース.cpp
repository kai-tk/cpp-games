#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define FIELD_WIDTH 12
#define FIELD_HEIGHT 22
#define MINO_WIDTH 4
#define MINO_HEIGHT 4

char field[FIELD_HEIGHT][FIELD_WIDTH];
char displayBuffer[FIELD_HEIGHT][FIELD_WIDTH];

enum{
	MINO_TYPE_I,
	MINO_TYPE_O,
	MINO_TYPE_S,
	MINO_TYPE_Z,
	MINO_TYPE_J,
	MINO_TYPE_L,
	MINO_TYPE_T,
	MINO_TYPE_MAX
};

enum {
	MINO_ANGLE_0,
	MINO_ANGLE_90,
	MINO_ANGLE_180,
	MINO_ANGLE_270,
	MINO_ANGLE_MAX
};

char minoShapes[MINO_TYPE_MAX][MINO_ANGLE_MAX][MINO_HEIGHT][MINO_WIDTH] = {
	//MINO_TYPE_I
	{
		//MINO_ANGLE_0
		{
			0,1,0,0,
			0,1,0,0,
			0,1,0,0,
			0,1,0,0,
		},
		//MINO_ANGLE_90
		{
			0,0,0,0,
			0,0,0,0,
			1,1,1,1,
			0,0,0,0,
		},
		//MINO_ANGLE_180
		{
			0,0,1,0,
			0,0,1,0,
			0,0,1,0,
			0,0,1,0,
		},
		//MINO_ANGLE_270
		{
			0,0,0,0,
			1,1,1,1,
			0,0,0,0,
			0,0,0,0,
		},
	},
	//MINO_TYPE_O
	{
		//MINO_ANGLE_0
		{
			0,0,0,0,
			0,1,1,0,
			0,1,1,0,
			0,0,0,0,
		},
		//MINO_ANGLE_90
		{
			0,0,0,0,
			0,1,1,0,
			0,1,1,0,
			0,0,0,0,
		},
		//MINO_ANGLE_180
		{
			0,0,0,0,
			0,1,1,0,
			0,1,1,0,
			0,0,0,0,
		},
		//MINO_ANGLE_270
		{
			0,0,0,0,
			0,1,1,0,
			0,1,1,0,
			0,0,0,0,
		},
	},
	//MINO_TYPE_S
	{
		//MINO_ANGLE_0
		{
			0,1,1,0,
			1,1,0,0,
			0,0,0,0,
			0,0,0,0,
		},
		//MINO_ANGLE_90
		{
			0,1,0,0,
			0,1,1,0,
			0,0,1,0,
			0,0,0,0,
		},
		//MINO_ANGLE_180
		{
			0,0,0,0,
			0,1,1,0,
			1,1,0,0,
			0,0,0,0,
		},
		//MINO_ANGLE_270
		{
			1,0,0,0,
			1,1,0,0,
			0,1,0,0,
			0,0,0,0,
		},
	},
	//MINO_TYPE_Z
	{
		//MINO_ANGLE_0
		{
			1,1,0,0,
			0,1,1,0,
			0,0,0,0,
			0,0,0,0,
		},
		//MINO_ANGLE_90
		{
			0,0,1,0,
			0,1,1,0,
			0,1,0,0,
			0,0,0,0,
		},
		//MINO_ANGLE_180
		{
			0,0,0,0,
			1,1,0,0,
			0,1,1,0,
			0,0,0,0,
		},
		//MINO_ANGLE_270
		{
			0,1,0,0,
			1,1,0,0,
			1,0,0,0,
			0,0,0,0,
		},
	},
	//MINO_TYPE_J
	{
		//MINO_ANGLE_0
		{
			0,0,1,0,
			1,1,1,0,
			0,0,0,0,
			0,0,0,0,
		},
		//MINO_ANGLE_90
		{
			0,1,0,0,
			0,1,0,0,
			0,1,1,0,
			0,0,0,0,
		},
		//MINO_ANGLE_180
		{
			0,0,0,0,
			1,1,1,0,
			1,0,0,0,
			0,0,0,0,
		},
		//MINO_ANGLE_270
		{
			1,1,0,0,
			0,1,0,0,
			0,1,0,0,
			0,0,0,0,
		},
	},
	//MINO_TYPE_L
	{
		//MINO_ANGLE_0
		{
			1,0,0,0,
			1,1,1,0,
			0,0,0,0,
			0,0,0,0,
		},
		//MINO_ANGLE_90
		{
			0,1,1,0,
			0,1,0,0,
			0,1,0,0,
			0,0,0,0,
		},
		//MINO_ANGLE_180
		{
			0,0,0,0,
			1,1,1,0,
			0,0,1,0,
			0,0,0,0,
		},
		//MINO_ANGLE_270
		{
			0,1,0,0,
			0,1,0,0,
			1,1,0,0,
			0,0,0,0,
		},
	},
	//MINO_TYPE_T
	{
		//MINO_ANGLE_0
		{
			0,1,0,0,
			1,1,1,0,
			0,0,0,0,
			0,0,0,0,
		},
		//MINO_ANGLE_90
		{
			0,1,0,0,
			0,1,1,0,
			0,1,0,0,
			0,0,0,0,
		},
		//MINO_ANGLE_180
		{
			0,0,0,0,
			1,1,1,0,
			0,1,0,0,
			0,0,0,0,
		},
		//MINO_ANGLE_270
		{
			0,1,0,0,
			1,1,0,0,
			0,1,0,0,
			0,0,0,0,
		},
	},
};

//ミノデータ
int minoType = 0, minoAngle = 0;
int minoX = 5, minoY = 0;

//描画関数
void display() {
	//フィールドをバッファに書き込み
	memcpy(displayBuffer, field, sizeof(field));
	//ミノをバッファに書き込む
	for (int i = 0; i < MINO_HEIGHT; i++) {
		for (int j = 0; j < MINO_WIDTH; j++) {
			displayBuffer[minoY + i][minoX + j] |= minoShapes[minoType][minoAngle][i][j];
		}
	}
	//描画内容をクリア
	system("cls");
	//バッファを表示
	for (int i = 0; i < FIELD_HEIGHT; i++) {
		for (int j = 0; j < FIELD_WIDTH; j++) {
			printf(displayBuffer[i][j] ? "■" : "　");
		}
		printf("\n");
	}
}

//ミノとフィールドの接触判定関数
bool isHit(int _minoX, int _minoY, int _minoType, int _minoAngle) {
	for (int i = 0; i < MINO_HEIGHT; i++) {
		for (int j = 0; j < MINO_WIDTH; j++) {
			if (minoShapes[_minoType][_minoAngle][i][j] && field[_minoY + i][_minoX + j]) {
				return true;
			}
		}
	}
	return false;
}

//ミノの初期化関数
void resetMino() {
	minoX = 5;
	minoY = 0;
	minoType = rand() % MINO_TYPE_MAX;
	minoAngle = rand() % MINO_ANGLE_MAX;
}

void main() {
	//盤面初期化
	memset(field, 0, sizeof(field));
	//壁作成
	for (int i = 0; i < FIELD_HEIGHT; i++) {
		field[i][0] = 1;
		field[i][FIELD_WIDTH - 1] = 1;
	}
	//床作成
	for (int i = 0; i < FIELD_WIDTH; i++) {
		field[FIELD_HEIGHT-1][i] = 1;
	}
	//ミノを初期化
	resetMino();

	//開始時間
	time_t t = time(NULL);

	//ゲーム処理
	while (1) {
		//入力があったとき
		if (_kbhit()) {
			switch (_getch()) {
			case 's': //下移動
				if (!isHit(minoX, minoY + 1, minoType, minoAngle)) {
					minoY++;
				}
				break;
			case 'a': //左移動
				if (!isHit(minoX - 1, minoY, minoType, minoAngle)) {
					minoX--;
				}
				break;
			case 'd': //右移動
				if (!isHit(minoX + 1, minoY, minoType, minoAngle)) {
					minoX++;
				}
				break;
			case 0x20: //回転
				if (!isHit(minoX, minoY, minoType, (minoAngle + 1) % MINO_ANGLE_MAX)) {
					minoAngle = (minoAngle + 1) % MINO_ANGLE_MAX;
				}
			}
			display();
		}
		//1秒経過したとき
		if (t != time(NULL)) {
			t = time(NULL);
			if (isHit(minoX, minoY + 1, minoType, minoAngle)) {
				//接触していればミノをフィールドに追加
				for (int i = 0; i < MINO_HEIGHT; i++) {
					for (int j = 0; j < MINO_WIDTH; j++) {
						field[minoY + i][minoX + j] |= minoShapes[minoType][minoAngle][i][j];
					}
				}

				{
					for (int i = 0; i < FIELD_HEIGHT - 1; i++) {
						bool lineFill = true;
						for (int j = 1; j < FIELD_WIDTH - 1; j++) {
							if (!field[i][j]) {
								lineFill = false;
							}
						}
						if (lineFill) {
							for(int k=i;k>0;k--){
								for (int j = 1; j < FIELD_WIDTH - 1; j++) {
									field[k][j] = field[k - 1][j];
								}
							}
							for (int j = 1; j < FIELD_WIDTH - 1; j++) {
								field[0][j] = 0;
							}
						}
					}
				}
				//次のミノを生成
				resetMino();
			}else{
				//接触していなければミノを下に下げる
				minoY++;
			}
			display();
		}
	}
}