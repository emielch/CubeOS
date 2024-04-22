#include "AudioManager.h"

#include "ok_play_queue.h"

// clang-format off
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputUSB            usb1;           //xy=589.2000122070312,431.00001525878906
AudioAmplifier           amp2;           //xy=770.2000122070312,452.00001525878906
AudioAmplifier           amp1;           //xy=772.2000122070312,410.00001525878906
OKAudioPlayQueue         queue1;         //xy=780.2000122070312,610.0000152587891
AudioMixer4              mixer1;         //xy=1061.2000122070312,404.00001525878906
AudioMixer4              mixer2;         //xy=1063.2000122070312,561.0000152587891
#if ESP_AUDIO
AudioInputI2Sslave       i2s_in;         //xy=771.2000122070312,514.0000152587891
AudioOutputI2Sslave      i2s1;           //xy=1432.2000122070312,516.0000152587891
AudioConnection          patchCord4(i2s_in, 0, mixer1, 1);
AudioConnection          patchCord5(i2s_in, 1, mixer2, 1);
#else
AudioOutputI2S           i2s1;           //xy=1432.2000122070312,516.0000152587891
#endif
AudioFilterBiquad        biquad_L;       //xy=1268.2000122070312,472.00001525878906
AudioFilterBiquad        biquad_R;       //xy=1271.2000122070312,525.0000152587891
AudioMixer4              mixer_fft;      //xy=1290.2000122070312,613.0000152587891
AudioAnalyzeFFT1024      fft1024;        //xy=1450.2000122070312,624.0000152587891
AudioConnection          patchCord1(usb1, 0, amp1, 0);
AudioConnection          patchCord2(usb1, 1, amp2, 0);
AudioConnection          patchCord3(amp2, 0, mixer2, 0);
AudioConnection          patchCord6(amp1, 0, mixer1, 0);
AudioConnection          patchCord7(queue1, 0, mixer1, 2);
AudioConnection          patchCord8(queue1, 0, mixer2, 2);
AudioConnection          patchCord9(mixer1, biquad_L);
AudioConnection          patchCord10(mixer1, 0, mixer_fft, 0);
AudioConnection          patchCord11(mixer2, biquad_R);
AudioConnection          patchCord12(mixer2, 0, mixer_fft, 1);
AudioConnection          patchCord13(biquad_L, 0, i2s1, 0);
AudioConnection          patchCord14(biquad_R, 0, i2s1, 1);
AudioConnection          patchCord15(mixer_fft, fft1024);
// GUItool: end automatically generated code
// clang-format on

const int bins[] = {0, 1, 3, 5, 8, 13, 20, 30, 50, 80, 120, 190, 220, 270, 300, 330, 390};

void AudioManager::init() {
#if defined(__IMXRT1062__)
  AudioMemory(200);
  queue1.setMaxBuffers(50);
#else
  AudioMemory(100);
  queue1.setMaxBuffers(40);
#endif

  queue1.setBehaviour(OKAudioPlayQueue::NON_STALLING);

  biquad_L.setLowShelf(0, 350, 20, 1);
  biquad_R.setLowShelf(0, 350, 20, 1);
  mixer_fft.gain(0, 0.5);
  mixer_fft.gain(1, 0.5);
}

void AudioManager::update() {
  float vol = usb1.volume();
  vol = pow(vol, 2.5);
  amp1.gain(vol);
  amp2.gain(vol);

  fftUpdate();

  if (sincePlayBuffer < 500 && sinceBuffSend > 100) {
    Serial.printf("AQ,%2f\r\n", queue1.getQueueFillAvg());
    sinceBuffSend = 0;
  }
}

int16_t* AudioManager::getBuffer(void) {
  return queue1.getBuffer();
}

void AudioManager::playBuffer() {
  queue1.playBuffer();
  sincePlayBuffer = 0;
}

void AudioManager::fftUpdate() {
  if (fft1024.available()) {
    for (int i = 0; i < 16; i++) {
      float n = fft1024.read(bins[i], bins[i + 1]);

      if (n > peaks[i]) {
        peaks[i] = n;
      }
      float tempVal = map(n, 0, 1, 0, peaks[i]);

      if (tempVal < levels[i] * 0.95) {
        levels[i] *= 0.95;
      } else {
        levels[i] = tempVal;
      }

      // Serial.print(String(peaks[i] * 100, 2) + "  ");

      peaks[i] *= 0.96;
    }

    // Serial.println();
    newData = true;
  }
}

AudioManager audioManager;