#pragma once
class Mob;
class Options;

#include <FACT.h>
#include <FACT3D.h>

#include "../../../../Minecraft.World/Util/SoundTypes.h"

extern FAudio* g_pXAudio2;       // pointer to XAudio2 instance used by QNet and XACT
extern FAudioMasteringVoice* g_pXAudio2MasteringVoice;  // pointer to XAudio2 mastering voice

class SoundEngine : public ConsoleSoundEngine
{
	//static const unsigned char *ucSoundNames[eSoundType_MAX][32];
	static const int MAX_POLYPHONY = 30;		// 4J added
	static const int MAX_SAME_SOUNDS_PLAYING = 8; // 4J added
	static FACTAudioEngine				*m_pXACT3Engine;
	static F3DAUDIO_HANDLE			m_xact3dInstance;
	static F3DAUDIO_DSP_SETTINGS	m_DSPSettings;
	static F3DAUDIO_EMITTER			m_emitter;
	static F3DAUDIO_LISTENER		m_listeners[4];
	static int						m_validListenerCount;

	static F3DAUDIO_DISTANCE_CURVE	m_VolumeCurve;
	static F3DAUDIO_DISTANCE_CURVE_POINT m_VolumeCurvePoints[2];

	static F3DAUDIO_DISTANCE_CURVE	m_DragonVolumeCurve;
	static F3DAUDIO_DISTANCE_CURVE_POINT m_DragonVolumeCurvePoints[2];

	static F3DAUDIO_DISTANCE_CURVE	m_VolumeCurveNoDecay;
	static F3DAUDIO_DISTANCE_CURVE_POINT m_VolumeCurvePointsNoDecay[2];

	static FACTWaveBank	    *m_pWaveBank;
	static FACTWaveBank	    *m_pWaveBank2;
	static FACTWaveBank	    *m_pStreamedWaveBank;
	static FACTWaveBank	    *m_pStreamedWaveBankAdditional;
	static FACTSoundBank	*m_pSoundBank;
	static FACTSoundBank	*m_pSoundBank2;

	static CRITICAL_SECTION		m_CS;

	struct soundInfo
	{
		// 4J-PB - adding the cue index so we can limit the number of the same sounds playing (rain)
		uint16_t	idx;
		int			iSoundBank;
		eSOUND_TYPE	eSoundID;
		float		x, y, z;
		float		volume;
		float		pitch;
		FACTCue     *pCue;
		bool		updatePos;
	};

	void update3DPosition( soundInfo *pInfo, bool bPlaceEmitterAtListener = false, bool bIsCDMusic = false);
	static std::vector<soundInfo *>currentSounds;

	int noMusicDelay;
	Random *random;

	// 4J Added

	char * m_chMusicName;
	soundInfo m_MusicInfo;

	uint16_t m_musicIDX;
	bool m_bStreamingMusicReady;
	bool m_bStreamingWaveBank1Ready;
	bool m_bStreamingWaveBank2Ready;

	// to handle volume changes
	uint16_t m_xactSFX;
	uint16_t m_xactMusic;
public:
	SoundEngine();
	virtual void destroy();
	virtual void play(int iSound, float x, float y, float z, float volume, float pitch);
	virtual void playStreaming(const std::wstring& name, float x, float y , float z, float volume, float pitch, bool bMusicDelay=true);
	virtual void playUI(int iSound, float volume, float pitch);
	virtual void playMusicTick();
	virtual void updateMusicVolume(float fVal);
	virtual void updateSystemMusicPlaying(bool isPlaying);
	virtual void updateSoundEffectVolume(float fVal);
	virtual void init(Options *);
	virtual void tick(std::shared_ptr<Mob> *players, float a);	// 4J - updated to take array of local players rather than single one
	virtual void add(const std::wstring& name, File *file);
	virtual void addMusic(const std::wstring& name, File *file);
	virtual void addStreaming(const std::wstring& name, File *file);
	static void setXACTEngine( FACTAudioEngine *pXACT3Engine);
	void CreateStreamingWavebank(const char *pchName, FACTWaveBank **ppStreamedWaveBank);
	void CreateSoundbank(const char *pchName, FACTSoundBank **ppSoundBank);
	virtual char *ConvertSoundPathToName(const std::wstring& name, bool bConvertSpaces=false);
	bool isStreamingWavebankReady();		// 4J Added
	bool isStreamingWavebankReady(FACTWaveBank *pWaveBank);
	int initAudioHardware(int iMinSpeakers)	{ return iMinSpeakers;}

private:
	static void XACTNotificationCallback( const FACTNotification* pNotification );
}; 