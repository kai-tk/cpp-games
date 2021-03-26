#include <stdio.h>
#include <time.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include "font.h"
#include "Rect.h"
#include "Ball.h"
#include "Paddle.h"
#include "audio.h"
using namespace glm;

#define BALL_MAX 128

ivec2 windowSize = { 800,600 };

bool keys[256];

Rect rect1 = Rect(vec2(100, 100), vec2(100, 200));
Rect rect2 = Rect(vec2(windowSize.x / 2, windowSize.y / 2), vec2(200, 100));

Ball balls[BALL_MAX];
Paddle paddle;

//vec2 point = vec2(windowSize.x / 2, windowSize.y / 2);

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
	
	glTranslatef(windowSize.x / 2.f, windowSize.y / 2.f, 0);
	static float angle;
	if (keys['d']) angle += 1;
	if (keys['a']) angle -= 1;
	glRotatef(angle, 0, 0, 1);
	glScalef(256, -256, 1);
	glutWireTeapot(1);

	/*
	//��`�̐F
	if (rect1.intersect(rect2)) {
		glColor3ub(0xff, 0x00, 0x00);
	}
	else {
		glColor3ub(0x00, 0x00, 0xff);
	}
	//��`�̕\��
	rect1.draw();

	glColor3ub(0x00, 0xff, 0x00);
	rect2.draw();

	//�_�̕\��
	glColor3ub(0xff, 0xff, 0xff);
	glPointSize(8);
	glBegin(GL_POINTS);
	{
		glVertex2f(point.x, point.y);
	}
	glEnd();

	//������̕\��
	fontBegin();
	fontSetColor(0, 0xff, 0);
	fontSetSize(FONT_DEFAULT_SIZE);
	float lineHeight = fontGetSize() * 1.5;
	float y = windowSize.y - lineHeight * 2;
	fontSetPosition(0, y);
	fontSetWeight(fontGetWeightMin());
	fontDraw("min:%f", fontGetWeightMin());
	fontSetPosition(0, y += lineHeight);
	fontSetWeight(fontGetWeightMax());
	fontDraw("max:%f", fontGetWeightMax());
	fontEnd();

	//�p�h���̕\��
	glColor3ub(0xff, 0xff, 0xff);
	paddle.draw();

	//�J���[�p���b�g
	unsigned char colors[6][3] = {
		{0xff,0x00,0x00},
		{0x00,0xff,0x00},
		{0x00,0x00,0xff},
		{0xff,0xff,0x00},
		{0x00,0xff,0xff},
		{0xff,0x00,0xff},
	};
	//�{�[���̕\��
	for (int i = 0; i < BALL_MAX; i++) {
		glColor3ub(colors[i % 6][0], colors[i % 6][1], colors[i % 6][2]);
		balls[i].draw();
	}
	*/

	//�_�u���o�b�t�@�̓��e��\��
	glutSwapBuffers();
}

void idle(void) {
	/*
	float f = 3;
	if (keys['w']) rect1.m_position.y -= f;
	if (keys['a']) rect1.m_position.x -= f;
	if (keys['s']) rect1.m_position.y += f;
	if (keys['d']) rect1.m_position.x += f;

	for (int i = 0; i < BALL_MAX; i++) {
		balls[i].update();

		if (balls[i].m_position.y < 0 || balls[i].m_position.y > windowSize.y) {
			balls[i].m_position.y = balls[i].m_position.y < 0 ? 0 : windowSize.y;
			balls[i].m_speed.y *= -1;
		}
		if (balls[i].m_position.x < 0 || balls[i].m_position.x > windowSize.x) {
			balls[i].m_position.x = balls[i].m_position.x < 0 ? 0 : windowSize.x;
			balls[i].m_speed.x *= -1;
		}
		if (paddle.intersectBall(balls[i])) {
			balls[i].m_position = balls[i].m_lastPosition;
			balls[i].m_speed.x *= -1;
		}
	}
	*/

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
	/*if (key == 0x1b) {
		exit(0);
	}
	printf("keyboard: \'%c\' (%#x)\n", key, key);
	keys[key] = true;
	*/
	switch (key) {
	case 0x1b:
		exit(0);
		break;
	case 'p':
		audioPlay();
		break;
	case 's':
		audioStop();
		break;
	}
}

void keyboardUp(unsigned char key, int x, int y) {
	if (key == 0x1b) {
		exit(0);
	}
	printf("keyboardUp: \'%c\' (%#x)\n", key, key);
	keys[key] = false;
}

void motion(int x, int y) {
	paddle.m_position = vec2(x, y - paddle.m_height / 2);
}

int main(int argc, char *argv[]) {
	
	if (audioInit() != 0) {
		return 1;
	}

	/*
	srand(time(NULL));
	for (int i = 0; i < BALL_MAX; i++) {
		balls[i].m_position = vec2(rand() % windowSize.x, rand() % windowSize.y);
		balls[i].m_speed = normalize(vec2(float(rand()) / RAND_MAX - 0.5, float(rand()) / RAND_MAX - 0.5)) * 2.f;
	}

	paddle.m_height = 300;
	*/

	//������,�p�l���ݒ�
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowPosition(640, 0);
	glutInitWindowSize(windowSize.x, windowSize.y);
	glutCreateWindow("title");

	//�\��
	glutDisplayFunc(display);
	//�A�C�h�����
	glutIdleFunc(idle);
	//�E�B���h�E���ό`����
	glutReshapeFunc(reshape);
	//�L�[������
	glutKeyboardFunc(keyboard);
	//�L�[�𗣂�
	glutKeyboardUpFunc(keyboardUp);
	//�L�[�̘A�����͂𖳌���
	glutIgnoreKeyRepeat(true);
	//�}�E�X�̈ʒu
	glutPassiveMotionFunc(motion);
	

	glutMainLoop();
}

