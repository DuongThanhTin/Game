#include "Sound.h"



CSound* CSound::instance = NULL;

CSound* CSound::getInstance()
{
	if (instance == nullptr)
		instance = new CSound(CGame::GetInstance()->getHWND());

	return instance;
}

CSound::CSound(HWND hWnd)
{
	primaryBuffer = 0;
	HRESULT result;

	DSBUFFERDESC bufferDesc;

	result = DirectSoundCreate8(NULL, &pDevice, NULL);


	result = pDevice->SetCooperativeLevel(hWnd, DSSCL_PRIORITY);

	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRLVOLUME;
	bufferDesc.dwBufferBytes = 0;
	bufferDesc.dwReserved = 0;
	bufferDesc.lpwfxFormat = NULL;
	bufferDesc.guid3DAlgorithm = GUID_NULL;

	result = pDevice->CreateSoundBuffer(&bufferDesc, &primaryBuffer, NULL);

	volume = 90.0f;
	int volume_80 = 80.0f;
	int volume_90 = 90.0f;
	int volume_120 = 120;
	isMute = false;


	//Load Sound
	loadSound("Sound/usingwhip.wav", "usingwhip");
	setVolume(volume_80, "usingwhip");

	loadSound("Sound/collectitem.wav", "collectitem");
	setVolume(volume_80, "collectitem");

	loadSound("Sound/dagger.wav", "dagger");
	setVolume(volume_90, "dagger");

	loadSound("Sound/watereffect.wav", "watereffect");
	setVolume(volume_90, "watereffect");

	loadSound("Sound/holywater.wav", "holywater");
	setVolume(volume_80, "holywater");

	loadSound("Sound/holycross.wav", "holycross");
	setVolume(volume_90, "holycross");

	loadSound("Sound/stopwatch.wav", "stopwatch");
	setVolume(volume_120, "stopwatch");

	loadSound("Sound/simondie.wav", "simondie");
	setVolume(volume_120, "simondie");


	loadSound("Sound/axe.wav", "axe");
	setVolume(volume_90, "axe");

	loadSound("Sound/Stage_01.wav", "Stage_01");
	setVolume(volume_90, "Stage_01");

	loadSound("Sound/hit.wav", "hit");
	setVolume(volume_80, "hit");

	loadSound("Sound/boomerang.wav", "boomerang");
	setVolume(volume_90, "boomerang");

	loadSound("Sound/hidebrick.wav", "hidebrick");
	setVolume(volume_90, "hidebrick");

	DebugOut(L"Size %d\n", soundBufferMap.size());
}

CSound::~CSound()
{
	for (auto it = soundBufferMap.begin(); it != soundBufferMap.end(); it++)
	{

		if (it->second)
		{
			it->second->Release();
			it->second = NULL;
		}

	}
	if (primaryBuffer)
		primaryBuffer->Release();
	if (pDevice)
		pDevice->Release();
	pDevice = NULL;

	primaryBuffer = NULL;


}

void CSound::create(HWND hWnd)
{
	if (instance == nullptr)
	{
		instance = new CSound(hWnd);
	}

}

float CSound::getVolume()
{
	return volume;
}

void CSound::loadSound(char* fileName, string name)
{
	if (soundBufferMap.find(name) != soundBufferMap.end())
		return;


	FILE* filePtr;
	WaveHeaderStruct waveHeaderStruct;
	IDirectSoundBuffer* tempBuffer;
	DSBUFFERDESC bufferDesc;
	WAVEFORMATEX waveFormat;
	unsigned char* wavData;
	unsigned char* bufferPtr;
	unsigned long bufferSize;

#pragma region read file

	int error = fopen_s(&filePtr, fileName, "rb");


	fread(&waveHeaderStruct, sizeof(WaveHeaderStruct), 1, filePtr);

	waveFormat.wFormatTag = WAVE_FORMAT_PCM;
	waveFormat.nSamplesPerSec = waveHeaderStruct.sampleRate;
	waveFormat.wBitsPerSample = waveHeaderStruct.bitsPerSample;
	waveFormat.nChannels = waveHeaderStruct.numChannels;
	waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
	waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
	waveFormat.cbSize = 0;

	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_GLOBALFOCUS;
	bufferDesc.dwBufferBytes = waveHeaderStruct.dataSize;
	bufferDesc.dwReserved = 0;
	bufferDesc.lpwfxFormat = &waveFormat;
	bufferDesc.guid3DAlgorithm = GUID_NULL;

	IDirectSoundBuffer8* secondaryBuffer = 0;
	IDirectSoundBuffer8** pSecondaryBuffer = &secondaryBuffer;


	pDevice->CreateSoundBuffer(&bufferDesc, &tempBuffer, NULL);

	long result = tempBuffer->QueryInterface(IID_IDirectSoundBuffer8, (void**)&(*pSecondaryBuffer));

	tempBuffer->Release();
	tempBuffer = 0;


	fseek(filePtr, sizeof(WaveHeaderStruct), SEEK_SET);


	wavData = new unsigned char[waveHeaderStruct.dataSize];



	fread(wavData, waveHeaderStruct.dataSize, 1, filePtr);

	error = fclose(filePtr);
#pragma endregion 

	result = (*pSecondaryBuffer)->Lock(0, waveHeaderStruct.dataSize, (void**)&bufferPtr, (DWORD*)&bufferSize, NULL, 0, 0);

	if (FAILED(result))
	{
		return;
	}

	memcpy(bufferPtr, wavData, waveHeaderStruct.dataSize);

	(*pSecondaryBuffer)->Unlock((void*)bufferPtr, bufferSize, NULL, 0);

	if (wavData != NULL)
		delete wavData;
	wavData = 0;
	long tempVolume = (volume) / 100 * (-DSBVOLUME_MIN) + DSBVOLUME_MIN;
	(*pSecondaryBuffer)->SetVolume(tempVolume);
	vector<string> tokens = split(name);
	wstring path = ToWSTR(tokens[0]);
	DebugOut(L"NAME %s\n", path.c_str());

	soundBufferMap[name] = secondaryBuffer;

}

void CSound::play(string name, bool infiniteLoop, int times)
{
	if (isMute || isPlaying(name) == true)
	{
		return;
	}
	map< std::string, IDirectSoundBuffer8*> ::iterator it;
	it = soundBufferMap.find(name);

	if (it == soundBufferMap.end())
		return;
	if (infiniteLoop)
	{
		it->second->Play(0, 0, DSBPLAY_LOOPING);
	}
	else
	{
		it->second->Stop();
		it->second->SetCurrentPosition(0);
		it->second->Play(0, 0, times - 1);
	}

}

void CSound::stop(string name)
{
	if (name == "")
	{
		for (std::map< std::string, IDirectSoundBuffer8*> ::iterator it = soundBufferMap.begin(); it != soundBufferMap.end(); it++)
		{
			it->second->Stop();
			it->second->SetCurrentPosition(0);
		}
	}
	else
	{
		std::map< std::string, IDirectSoundBuffer8*> ::iterator it;
		it = soundBufferMap.find(name);
		if (it == soundBufferMap.end())
			return;
		else it->second->Stop();
	}
}

bool CSound::isPlaying(string name)
{
	std::map< std::string, IDirectSoundBuffer8*> ::iterator it;
	it = soundBufferMap.find(name);
	if (it == soundBufferMap.end())
		return false;
	else
	{
		DWORD result;
		it->second->GetStatus(&result);
		if (result == DSBSTATUS_PLAYING)
			return true;
		else return false;
	}

}

void CSound::setVolume(float percentage, string name)
{
	volume = percentage;
	if (name == "")
	{
		long volumne = (percentage) / 100 * (-DSBVOLUME_MIN) + DSBVOLUME_MIN;
		for (std::map< std::string, IDirectSoundBuffer8*> ::iterator it = soundBufferMap.begin(); it != soundBufferMap.end(); it++)
		{
			it->second->SetVolume(volumne);
		}
	}
	else
	{
		std::map< std::string, IDirectSoundBuffer8*> ::iterator it;
		it = soundBufferMap.find(name);
		if (it == soundBufferMap.end())
			return;
		long volumne = (percentage) / 100 * (-DSBVOLUME_MIN) + DSBVOLUME_MIN;
		it->second->SetVolume(volumne);
	}
}

void CSound::mute()
{
	isMute = true;
	CSound::getInstance()->stop();
}

void CSound::unMute()
{
	isMute = false;
}