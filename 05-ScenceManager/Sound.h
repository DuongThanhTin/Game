#pragma once

#include "dsound.h"
#include "windows.h"
#include "Game.h"
#include "Utils.h"
#include <map>
#include <string>
#include <iostream>
#include <mmsystem.h>
#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")
using namespace std;

class CSound
{
public:
	static CSound* getInstance();

	struct WaveHeaderStruct
	{
		char chunkId[4];
		unsigned long chunkSize;
		char format[4];
		char subChunkId[4];
		unsigned long subChunkSize;
		unsigned short audioFormat;
		unsigned short numChannels;
		unsigned long sampleRate;
		unsigned long bytesPerSecond;
		unsigned short blockAlign;
		unsigned short bitsPerSample;
		char dataChunkId[4];
		unsigned long dataSize;
	};

	float volume;
	void static create(HWND hWnd);
	void setVolume(float percentage, string name = "");
	void loadSound(char* fileName, string name);
	void play(string name, bool infiniteLoop, int times);
	void stop(string name = "");
	bool isPlaying(string name);


	float getVolume();
	void mute();
	void unMute();


	~CSound();

private:
	CSound(HWND hWnd);
	static CSound * instance;
	IDirectSound8* pDevice;
	IDirectSoundBuffer* primaryBuffer;
	map<string, IDirectSoundBuffer8*> soundBufferMap;
	bool isMute;
};