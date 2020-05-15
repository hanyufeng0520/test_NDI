#pragma once
#include <cstdint>
#include <memory>
#include "IBaseFrame.h"

class AudioFrame :public IBaseFrame
{
	uint8_t*           m_raw = nullptr;
	uint32_t		   m_totalSize = 0;
	uint32_t           m_monoCnt = 16;
	uint32_t           m_sampleCnt = 0;
	double			   m_ptsFrame = 0;
	uint64_t		   m_timeID = 0;
	Timecode		   m_tc;
	uint32_t		   m_nbBitPerSample = 32;

public:
	struct header
	{
		uint32_t	rawSize = 0;
	};

	explicit AudioFrame(int _monoCnt = 16);
	~AudioFrame();

	int				init(uint32_t _nbMonoCnl = 16, uint32_t _nbBitPerSample = 32, uint32_t _nbSample = 2000);

	unsigned char *	getRaw() const override;
	int				getTotalSize() const override;
	int				setBufferSize(unsigned long _rawSize) override;
	unsigned long	getDataSize() const override;
	unsigned char*	getRawWithHeader() const;
	unsigned long	getRawWithHeaderSize() const;

	uint32_t		getNbBitPerSample() const { return m_nbBitPerSample; }
	void			setToMute(uint32_t _size = 0) const;
	void			SetMonoCnt(uint32_t cnt);
	void			SetSampleCnt(uint32_t  sampleCnt);
	uint32_t		GetMonoCnt() const { return m_monoCnt; }
	unsigned long	getBufferTotalSize() const;
	unsigned long	getSampleCount() const { return m_sampleCnt; }
	bool			isMute() const;
	void			setPts(double pts);
	double			getPts()const;
	void			setTC(const Timecode& _tc) override;
	Timecode		getTC() const override;
};

using pAframe = std::shared_ptr<AudioFrame>;
