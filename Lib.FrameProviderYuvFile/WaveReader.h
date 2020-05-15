#pragma once
#ifdef _MSC_VER
#include <Windows.h>
#else
#endif _MSC_VER
#include <memory>
#include "WaveHeader.h"

class AudioFrame;

class CWaveReader
{
	wav_t m_wavInfo;
	BYTE* m_pRawWave;
	wchar_t m_szLogFile[MAX_PATH];
	void  initLog(wchar_t* szLogFile);
	int   openFile(const char* file_name);
	int   checkFileHeader();
	int   getMarker(char(&_marker)[4], int& size);
	bool  isMarkerFMT(const char* _marker);
	bool  isMarkerDATA(const char * _marker);
	int   readFMT(const char* _marker, int size);
	int   readDATA(const char* _marker, int size, int & _offset);
	int   fillBufferFromDisk(int _sampleCount);

public:
	CWaveReader();
	~CWaveReader();
	bool open(const char *file_name, wchar_t*szLogFile);
	void close();
	bool getAudioFrame(std::shared_ptr<AudioFrame>& _aFrame);
};
