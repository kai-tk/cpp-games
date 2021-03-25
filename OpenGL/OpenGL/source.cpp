#include "font.h"
#include <stdio.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
using namespace glm;

ivec2 windowSize = { 800,600 };
bool keys[256];

void display(void) {
	//描画内容をクリア
	glClear(GL_COLOR_BUFFER_BIT);
	//射影行列設定モード
	glMatrixMode(GL_PROJECTION);
	//行列の初期化
	glLoadIdentity();
	//上下を反転してy軸を下向きに
	gluOrtho2D(0,windowSize.x,windowSize.y,0);

	//モデル行列設定モード
	glMatrixMode(GL_MODELVIEW);
	//行列の初期化
	glLoadIdentity();

	//表示内容
	glTranslatef(windowSize.x / 2, windowSize.y / 2, 0);
	static float angle;
	if (keys['d']) angle += 1;
	if (keys['a']) angle -= 1;
	glRotatef(angle, 0, 0, 1);
	glScalef(256, 256, 1);
	glutWireTeapot(1);

	//文字列の表示
	fontBegin();
	fontSetColor(0, 0xff, 0);
	fontSetPosition(0, windowSize.y - fontGetSize() * 1.4);
	fontSetSize(FONT_DEFAULT_SIZE / 2);
	fontDraw("angle:%f", angle);
	fontEnd();

	//ダブルバッファの内容を表示
	glutSwapBuffers();
}

void idle(void) {
	//再描画
	glutPostRedisplay();
}

void reshape(int width, int height) {
	printf("reshape: width:%d height:%d\n", width, height);
	//ビューポートの設定
	glViewport(0,0,width,height);
	windowSize = ivec2(width, height);
}

void keyboard(unsigned char key,int x,int y) {
	if (key == 0x1b) {
		exit(0);
	}
	printf("keyboard: \'%c\' (%#x)\n", key, key);
	keys[key] = true;
}

void keyboardUp(unsigned char key, int x, int y) {
	if (key == 0x1b) {
		exit(0);
	}
	printf("keyboardUp: \'%c\' (%#x)\n", key, key);
	keys[key] = false;
}

int main(int argc, char *argv[]) {
	//初期化,パネル設定
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowPosition(640, 0);
	glutInitWindowSize(windowSize.x, windowSize.y);
	glutCreateWindow("title");

	//表示時
	glutDisplayFunc(display);
	//アイドル状態時
	glutIdleFunc(idle);
	//変形時
	glutReshapeFunc(reshape);
	//キーボード入力時
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	//キーの連続入力を無効化
	glutIgnoreKeyRepeat(true);
	

	glutMainLoop();
}

