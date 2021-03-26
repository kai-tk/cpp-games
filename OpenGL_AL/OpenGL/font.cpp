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

//������̕`��J�n
void fontBegin() {
	//�s����X�^�b�N�ɕێ�
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	//�ˉe�s��ݒ胂�[�h
	glMatrixMode(GL_PROJECTION);
	//�s��̏�����
	glLoadIdentity();
	//�r���[�|�[�g���擾
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	//�㉺�𔽓]����y������������
	gluOrtho2D(0, viewport[2], viewport[3], 0);

	//���f���s��ݒ胂�[�h
	glMatrixMode(GL_MODELVIEW);
	//�s��̏�����
	glLoadIdentity();
	//�e��ݒ�̖�����
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
}
//������̕`��I��
void fontEnd() {
	//���̍s���Ԃ�
	glPopMatrix();
	glPopAttrib();
}

//�����ʒu�̐ݒ�
void fontSetPosition(float _x, float _y) {
	position = vec2(_x, _y);
}
//�����T�C�Y�̐ݒ�
void fontSetSize(float _size) {
	size = _size;
}
//�����T�C�Y�̎擾
float fontGetSize() {
	return size;
}

//�ݒ�\�ȑ������擾
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
//������ݒ�
void fontSetWeight(float _weight) {
	weight = _weight;
}

//�����F�̐ݒ�
void fontSetColor(unsigned char _red, unsigned char _green, unsigned char _blue) {
	color[0] = _red;
	color[1] = _green;
	color[2] = _blue;
}

//������̕`��
void fontDraw(const char *_format, ...) {
	//���������X�g��
	va_list argList;
	va_start(argList, _format);
	//�t�H�[�}�b�g�ƈ������當�͂𐶐�
	char str[256];
	vsprintf_s(str, _format, argList);
	va_end(argList);

	//�����ƐF�̐ݒ�
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