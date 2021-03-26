#pragma comment(lib,"OpenAL32.lib")

#include <stdio.h>
#include <alc.h>
#include <al.h>
#include "audio.h"

ALCdevice* device;
ALCcontext* context;
ALuint bid;
ALuint sid;

//初期化
int audioInit() {
	//デバイスを開く
	device = alcOpenDevice(NULL);
	if (device == NULL) return 1;

	//コンテキストの作成
	context = alcCreateContext(device, NULL);
	if (context == NULL) return 1;
	//コンテキストの設定
	alcMakeContextCurrent(context);

	//バッファの作成
	alGenBuffers(1, &bid);

	//矩形波
	unsigned char data[] = { 0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
	
	//バッファに波形をセット
	alBufferData(bid, AL_FORMAT_MONO8, data, sizeof(data), sizeof(data) * 440);
	
	//ソースの作成
	alGenSources(1, &sid);

	//ソースにバッファをセット
	alSourcei(sid, AL_BUFFER, bid);
	//ループを有効化
	alSourcei(sid, AL_LOOPING, AL_TRUE);
	//音量を下げる
	alSourcef(sid, AL_GAIN, 0.1f);

	return 0;
}
//再生
void audioPlay() {
	alSourcePlay(sid);
}
//停止
void audioStop() {
	alSourceStop(sid);
}