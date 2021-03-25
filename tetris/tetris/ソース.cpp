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

//�~�m�f�[�^
int minoType = 0, minoAngle = 0;
int minoX = 5, minoY = 0;

//�`��֐�
void display() {
	//�t�B�[���h���o�b�t�@�ɏ�������
	memcpy(displayBuffer, field, sizeof(field));
	//�~�m���o�b�t�@�ɏ�������
	for (int i = 0; i < MINO_HEIGHT; i++) {
		for (int j = 0; j < MINO_WIDTH; j++) {
			displayBuffer[minoY + i][minoX + j] |= minoShapes[minoType][minoAngle][i][j];
		}
	}
	//�`����e���N���A
	system("cls");
	//�o�b�t�@��\��
	for (int i = 0; i < FIELD_HEIGHT; i++) {
		for (int j = 0; j < FIELD_WIDTH; j++) {
			printf(displayBuffer[i][j] ? "��" : "�@");
		}
		printf("\n");
	}
}

//�~�m�ƃt�B�[���h�̐ڐG����֐�
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

//�~�m�̏������֐�
void resetMino() {
	minoX = 5;
	minoY = 0;
	minoType = rand() % MINO_TYPE_MAX;
	minoAngle = rand() % MINO_ANGLE_MAX;
}

void main() {
	//�Ֆʏ�����
	memset(field, 0, sizeof(field));
	//�Ǎ쐬
	for (int i = 0; i < FIELD_HEIGHT; i++) {
		field[i][0] = 1;
		field[i][FIELD_WIDTH - 1] = 1;
	}
	//���쐬
	for (int i = 0; i < FIELD_WIDTH; i++) {
		field[FIELD_HEIGHT-1][i] = 1;
	}
	//�~�m��������
	resetMino();

	//�J�n����
	time_t t = time(NULL);

	//�Q�[������
	while (1) {
		//���͂��������Ƃ�
		if (_kbhit()) {
			switch (_getch()) {
			case 's': //���ړ�
				if (!isHit(minoX, minoY + 1, minoType, minoAngle)) {
					minoY++;
				}
				break;
			case 'a': //���ړ�
				if (!isHit(minoX - 1, minoY, minoType, minoAngle)) {
					minoX--;
				}
				break;
			case 'd': //�E�ړ�
				if (!isHit(minoX + 1, minoY, minoType, minoAngle)) {
					minoX++;
				}
				break;
			case 0x20: //��]
				if (!isHit(minoX, minoY, minoType, (minoAngle + 1) % MINO_ANGLE_MAX)) {
					minoAngle = (minoAngle + 1) % MINO_ANGLE_MAX;
				}
			}
			display();
		}
		//1�b�o�߂����Ƃ�
		if (t != time(NULL)) {
			t = time(NULL);
			if (isHit(minoX, minoY + 1, minoType, minoAngle)) {
				//�ڐG���Ă���΃~�m���t�B�[���h�ɒǉ�
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
				//���̃~�m�𐶐�
				resetMino();
			}else{
				//�ڐG���Ă��Ȃ���΃~�m�����ɉ�����
				minoY++;
			}
			display();
		}
	}
}