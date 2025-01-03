#include <string>
#include "../public/iaudioplayer.h"
#include <globals.h>

// not using
// /*
//  * @param slot - player slot to set
//  * @param factor - voice level to set, usually negative
//  */
// void SetPlayerVolume(int slot, float factor);
// void SetAllPlayerVolume(float factor);
// float GetPlayerVolume(int slot);

/*
 * @param slot - player slot to set
 * @param hearing - whether player can hear
 */
void SetPlayerHearing(int slot, bool hearing);
void SetAllPlayerHearing(bool hearing);
bool IsHearing(int slot);

/*
 * @param slot - player slot to set
 * @param voiceData - buffer string, contains pcm data, pass null means stop playing
 * either buffer or path
 */
void SetPlayerAudioBufferString(int slot, std::string audioBuffer, std::string audioPath);
void SetAllAudioBufferString(std::string audioBuffer, std::string audioPath);
bool IsPlaying(int slot);
bool IsAllPlaying();

class CAudioPlayerInterface : IAudioPlayer
{

public:
  virtual void SetPlayerHearing(int slot, bool hearing) override;
  virtual void SetAllPlayerHearing(bool hearing) override;
  virtual bool IsHearing(int slot) override;

  virtual void SetPlayerAudioBuffer(int slot, const char *audioBuffer, int audioBufferSize) override;
  virtual void SetPlayerAudioFile(int slot, const char *audioFile, int audioFileSize) override;
  virtual void SetAllAudioBuffer(const char *audioBuffer, int audioBufferSize) override;
  virtual void SetAllAudioFile(const char *audioFile, int audioFileSize) override;
  virtual bool IsPlaying(int slot) override;
  virtual bool IsAllPlaying() override;

  virtual int RegisterPlayStartListener(PLAY_START_CALLBACK callback);
  virtual void UnregisterPlayStartListener(int id);
  virtual int RegisterPlayEndListener(PLAY_END_CALLBACK callback);
  virtual void UnregisterPlayEndListener(int id);
};

#ifdef PLATFORM_LINUX
#define PINVOKE_EXPORT __attribute__((visibility("default")))
#else
#define PINVOKE_EXPORT __declspec(dllexport)
#endif

extern "C"
{
  PINVOKE_EXPORT void NativeSetPlayerHearing(int slot, bool hearing);
  PINVOKE_EXPORT void NativeSetAllPlayerHearing(bool hearing);
  PINVOKE_EXPORT bool NativeIsHearing(int slot);

  PINVOKE_EXPORT void NativeSetPlayerAudioBufferString(int slot, const char *audioBuffer, int audioBufferSize, const char *audioPath, int audioPathSize);
  PINVOKE_EXPORT void NativeSetAllAudioBufferString(const char *audioBuffer, int audioBufferSize, const char *audioPath, int audioPathSize);
  PINVOKE_EXPORT bool NativeIsPlaying(int slot);
  PINVOKE_EXPORT bool NativeIsAllPlaying();

  PINVOKE_EXPORT int NativeRegisterPlayStartListener(PLAY_START_CALLBACK callback);
  PINVOKE_EXPORT void NativeUnregisterPlayStartListener(int id);
  PINVOKE_EXPORT int NativeRegisterPlayEndListener(PLAY_END_CALLBACK callback);
  PINVOKE_EXPORT void NativeUnregisterPlayEndListener(int id);
}