#pragma comment(lib,"OpenAL32.lib")

#include <stdio.h>
#include <alc.h>
#include <al.h>
#include "audio.h"

ALCdevice* device;
ALCcontext* context;
ALuint bid;
ALuint sid;

//������
int audioInit() {
	//�f�o�C�X���J��
	device = alcOpenDevice(NULL);
	if (device == NULL) return 1;

	//�R���e�L�X�g�̍쐬
	context = alcCreateContext(device, NULL);
	if (context == NULL) return 1;
	//�R���e�L�X�g�̐ݒ�
	alcMakeContextCurrent(context);

	//�o�b�t�@�̍쐬
	alGenBuffers(1, &bid);

	//��`�g
	unsigned char data[] = { 0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
	
	//�o�b�t�@�ɔg�`���Z�b�g
	alBufferData(bid, AL_FORMAT_MONO8, data, sizeof(data), sizeof(data) * 440);
	
	//�\�[�X�̍쐬
	alGenSources(1, &sid);

	//�\�[�X�Ƀo�b�t�@���Z�b�g
	alSourcei(sid, AL_BUFFER, bid);
	//���[�v��L����
	alSourcei(sid, AL_LOOPING, AL_TRUE);
	//���ʂ�������
	alSourcef(sid, AL_GAIN, 0.1f);

	return 0;
}
//�Đ�
void audioPlay() {
	alSourcePlay(sid);
}
//��~
void audioStop() {
	alSourceStop(sid);
}