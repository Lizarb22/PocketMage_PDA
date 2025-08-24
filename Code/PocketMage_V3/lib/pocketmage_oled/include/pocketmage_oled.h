//    .oooooo.   ooooo        oooooooooooo oooooooooo.    //
//   d8P'  `Y8b  `888'        `888'     `8 `888'   `Y8b   //
//  888      888  888          888          888      888  //
//  888      888  888          888oooo8     888      888  //
//  888      888  888          888    "     888      888  //
//  `88b    d88'  888       o  888       o  888     d88'  //
//   `Y8bood8P'  o888ooooood8 o888ooooood8 o888bood8P'    //     
#pragma once
#include <Arduino.h>
#include <U8g2lib.h>
#include <RTClib.h>
#include <vector>
#include <functional>
#include <utility>

// U8G2 FONTS
//U8G2_FOR_ADAFRUIT_GFX u8g2Fonts;
//u8g2_font_4x6_mf
//u8g2_font_5x7_mf
//u8g2_font_spleen5x8_mf
//u8g2_font_boutique_bitmap_9x9_tf
//u8g2_font_courR08_tf.h

class PocketmageOled {
public:
  explicit PocketmageOled(U8G2 &u8) : u8g2_(u8) {}

 // Wire up external buffers/state used to read from globals
  using MeasureTextFn = std::function<uint16_t(const String&)>; // returns text width in e-ink pixels
  using KbStateFn = std::function<int()>;
  using MaxCharsFn = std::function<uint16_t()>;

  PocketmageOled& setAllLines(std::vector<String>* lines)              { lines_ = lines; return *this; }
  PocketmageOled& setDynamicScroll(volatile long* scroll)              { dynamicScroll_ = scroll; return *this; }

  // E-ink measurement
  PocketmageOled& setReferenceWidth(uint16_t w)                        { refWidth_ = w; return *this; }
  PocketmageOled& setMeasureTextWidth(MeasureTextFn fn)                { measure_ = std::move(fn); return *this; }

  // Battery icon/state
  PocketmageOled& setBattery(volatile int* st, const uint8_t* const* icons, int iconCount) {
    battState_ = st;
    battIcons_ = icons;
    battIconCount_ = iconCount;
    return *this;
  }

  // Keyboard state: 0=NORMAL, 1=SHIFT, 2=FUNC
  PocketmageOled& setKeyboardState(int* kbState)                       { kbState_ = kbState; return *this; }
  PocketmageOled& setKeyboardStateGetter(KbStateFn fn) { kbStateFn_ = std::move(fn); return *this; }
  
  // Clock
  PocketmageOled& setClock(RTC_PCF8563* rtc, bool* systemClock, bool* showYear, const char (*days)[12])
  { rtc_ = rtc; systemClock_ = systemClock; showYear_ = showYear; days_ = days; return *this; }

  // Flags
  PocketmageOled& setMSC(bool* mscEnabled)                             { mscEnabled_ = mscEnabled; return *this; }
  PocketmageOled& setSD(volatile bool* sdActive)                       { sdActive_ = sdActive; return *this; }

  // Static assets
  PocketmageOled& setScrollBitmap(const uint8_t* bmp128x32)            { scrollBmp_ = bmp128x32; return *this; }
  
  PocketmageOled& setMaxCharsPerLineEinkGetter(MaxCharsFn fn) { maxCharsFn_ = std::move(fn); return *this;}
  
  // Main methods
  void oledWord(String word, bool allowLarge = false, bool showInfo = true);
  void oledLine(String line, bool doProgressBar = true, String bottomMsg = "");
  void oledScroll();
  void infoBar();

private:
  U8G2                  &u8g2_;
  std::vector<String>*  lines_         = nullptr;
  volatile long*        dynamicScroll_ = nullptr;

  volatile int*         battState_     = nullptr;
  const uint8_t* const* battIcons_     = nullptr;
  int                   battIconCount_ = 0;

  int*                  kbState_       = nullptr;
  KbStateFn             kbStateFn_;
  RTC_PCF8563*          rtc_           = nullptr;
  bool*                 systemClock_   = nullptr;
  bool*                 showYear_      = nullptr;
  const char            (*days_)[12]   = nullptr;

  bool*                 mscEnabled_    = nullptr;
  volatile bool*        sdActive_      = nullptr;

  const uint8_t*        scrollBmp_     = nullptr;

  uint16_t              refWidth_      = 320;   
  MeasureTextFn         measure_;               // measure of display text width in e-ink pixels
  MaxCharsFn            maxCharsFn_;            // measure   
  // helpers
  uint16_t strWidth(const String& s) const;

  int currentKbState() const;
};