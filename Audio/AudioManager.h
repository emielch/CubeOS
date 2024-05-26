#ifdef USB_MIDI_AUDIO_SERIAL
#include <Arduino.h>

class AudioManager {
 public:
  void init();
  void update();
  int16_t* getBuffer(void);
  void playBuffer();

  float levels[16];
  float peaks[16];
  bool newData = false;

 private:
  void fftUpdate();
  elapsedMillis sincePlayBuffer = 0;
  elapsedMillis sinceBuffSend = 0;
};

extern AudioManager audioManager;
#endif