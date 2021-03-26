#include "font.h"
#include <stdio.h>
#include <stdarg.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
using namespace glm;

static vec2 position;
static float size = FONT_DEFAULT_SIZE;
static unsigned char color[3];
static float weight = 1;

//文字列の描画開始
void fontBegin() {
	//行列をスタックに保持
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	//射影行列設定モード
	glMatrixMode(GL_PROJECTION);
	//行列の初期化
	glLoadIdentity();
	//ビューポートを取得
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	//上下を反転してy軸を下向きに
	gluOrtho2D(0, viewport[2], viewport[3], 0);

	//モデル行列設定モード
	glMatrixMode(GL_MODELVIEW);
	//行列の初期化
	glLoadIdentity();
	//各種設定の無効化
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
}
//文字列の描画終了
void fontEnd() {
	//元の行列を返す
	glPopMatrix();
	glPopAttrib();
}

//文字位置の設定
void fontSetPosition(float _x, float _y) {
	position = vec2(_x, _y);
}
//文字サイズの設定
void fontSetSize(float _size) {
	size = _size;
}
//文字サイズの取得
float fontGetSize() {
	return size;
}

//設定可能な太さを取得
float fontGetWeightMin() {
	GLfloat weight[2];
	glGetFloatv(GL_LINE_WIDTH_RANGE,weight);
	return weight[0];
}
float fontGetWeightMax() {
	GLfloat weight[2];
	glGetFloatv(GL_LINE_WIDTH_RANGE, weight);
	return weight[1];
}
//太さを設定
void fontSetWeight(float _weight) {
	weight = _weight;
}

//文字色の設定
void fontSetColor(unsigned char _red, unsigned char _green, unsigned char _blue) {
	color[0] = _red;
	color[1] = _green;
	color[2] = _blue;
}

//文字列の描画
void fontDraw(const char *_format, ...) {
	//引数をリスト化
	va_list argList;
	va_start(argList, _format);
	//フォーマットと引数から文章を生成
	char str[256];
	vsprintf_s(str, _format, argList);
	va_end(argList);

	//太さと色の設定
	glLineWidth(weight);
	glColor3ub(color[0], color[1], color[2]);

	glPushMatrix();
	{
		glTranslatef(position.x, position.y+size, 0);
		float s = size / FONT_DEFAULT_SIZE;
		glScalef(s,-s,s);
		for (char* p = str; *p != '\0'; p++) {
			glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);
		}
	}
	glPopMatrix();
	//printf("%s\n", str);
}