/*------------------------------------------------------/
/ Copyright (c) 2021, Elehobica
/ Released under the BSD-2-Clause
/ refer to https://opensource.org/licenses/BSD-2-Clause
/------------------------------------------------------*/

#ifndef __PLAY_AUDIO_H_INCLUDED__
#define __PLAY_AUDIO_H_INCLUDED__

#include "pico/audio_i2s.h"
#include "fatfs/ff.h"
#include "ReadBuffer.h"
#include "audio_init.h"

//=================================
// Interface of PlayAudio Class
//=================================
class PlayAudio
{
public:
    typedef enum {
        AUDIO_CODEC_NONE = 0,
        AUDIO_CODEC_WAV
    } audio_codec_t;
    static void initialize();
    static void volumeUp();
    static void volumeDown();
    static void setVolume(uint8_t value);
    static uint8_t getVolume();
    PlayAudio();
    virtual ~PlayAudio();
    virtual void play(const char *filename);
    void pause(bool flg = true);
    void stop();
    bool isPlaying();
    bool isPaused();
    uint32_t elapsedMillis();
    virtual uint32_t totalMillis() = 0;
protected:
    static const int RDBUF_SIZE = 2048;
    static const int32_t DAC_ZERO = 1; // to avoid pop noise caused by auto-mute function of DAC
    static audio_buffer_pool_t *ap;
    static ReadBuffer *rdbuf; // Read buffer for Audio codec stream
    static int16_t buf_s16[SAMPLES_PER_BUFFER*2]; // 16bit 2ch data before applying volume
    static uint8_t volume;
    static const uint32_t vol_table[101];
    FIL fil;
    bool playing;
    bool paused;
    uint16_t channels = 2;
    uint16_t sampRateHz = 44100;
    uint16_t bitRateKbps = 44100 * 16 * 2 / 1000;
    uint16_t bitsPerSample = 16;
    uint32_t samplesPlayed = 0;
    uint16_t getU16LE(const char *ptr);
    uint32_t getU32LE(const char *ptr);
    virtual void decode();
};

#endif // __PLAY_AUDIO_H_INCLUDED__