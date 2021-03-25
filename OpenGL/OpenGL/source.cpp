#include "font.h"
#include <stdio.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
using namespace glm;

ivec2 windowSize = { 800,600 };
bool keys[256];

void display(void) {
	//�`����e���N���A
	glClear(GL_COLOR_BUFFER_BIT);
	//�ˉe�s��ݒ胂�[�h
	glMatrixMode(GL_PROJECTION);
	//�s��̏�����
	glLoadIdentity();
	//�㉺�𔽓]����y������������
	gluOrtho2D(0,windowSize.x,windowSize.y,0);

	//���f���s��ݒ胂�[�h
	glMatrixMode(GL_MODELVIEW);
	//�s��̏�����
	glLoadIdentity();

	//�\�����e
	glTranslatef(windowSize.x / 2, windowSize.y / 2, 0);
	static float angle;
	if (keys['d']) angle += 1;
	if (keys['a']) angle -= 1;
	glRotatef(angle, 0, 0, 1);
	glScalef(256, 256, 1);
	glutWireTeapot(1);

	//������̕\��
	fontBegin();
	fontSetColor(0, 0xff, 0);
	fontSetPosition(0, windowSize.y - fontGetSize() * 1.4);
	fontSetSize(FONT_DEFAULT_SIZE / 2);
	fontDraw("angle:%f", angle);
	fontEnd();

	//�_�u���o�b�t�@�̓��e��\��
	glutSwapBuffers();
}

void idle(void) {
	//�ĕ`��
	glutPostRedisplay();
}

void reshape(int width, int height) {
	printf("reshape: width:%d height:%d\n", width, height);
	//�r���[�|�[�g�̐ݒ�
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
	//������,�p�l���ݒ�
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowPosition(640, 0);
	glutInitWindowSize(windowSize.x, windowSize.y);
	glutCreateWindow("title");

	//�\����
	glutDisplayFunc(display);
	//�A�C�h����Ԏ�
	glutIdleFunc(idle);
	//�ό`��
	glutReshapeFunc(reshape);
	//�L�[�{�[�h���͎�
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	//�L�[�̘A�����͂𖳌���
	glutIgnoreKeyRepeat(true);
	

	glutMainLoop();
}

