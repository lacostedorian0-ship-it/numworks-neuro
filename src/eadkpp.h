#ifndef EADKPP_H
#define EADKPP_H
extern "C" {
#include <eadk.h>
}
namespace EADK {
class Color { public: constexpr Color(uint32_t rgb):v(((rgb&0xF80000)>>8)|((rgb&0x00FC00)>>5)|((rgb&0x0000F8)>>3)){} constexpr operator eadk_color_t()const{return (eadk_color_t)v;} private:uint16_t v;};
class Point {public: constexpr Point(int x,int y):x_(x),y_(y){} constexpr operator eadk_point_t()const{return *reinterpret_cast<const eadk_point_t*>(this);}private:uint16_t x_,y_;};
class Rect {public: constexpr Rect(int x,int y,int w,int h):x_(x),y_(y),w_(w),h_(h){} constexpr operator eadk_rect_t()const{return *reinterpret_cast<const eadk_rect_t*>(this);}private:uint16_t x_,y_,w_,h_;};
namespace Screen {constexpr uint16_t Width=EADK_SCREEN_WIDTH;constexpr uint16_t Height=EADK_SCREEN_HEIGHT;}
namespace Display {static inline void pushRectUniform(Rect r,Color c){eadk_display_push_rect_uniform(r,c);}static inline void drawString(const char*s,Point p,bool l,Color f,Color b){eadk_display_draw_string(s,p,l,f,b);}}
namespace Keyboard {enum class Key:uint8_t{Left=0,Up=1,Down=2,Right=3,OK=4,Back=5,Home=6,Pi=27,Zero=48};class State{public:constexpr State(uint64_t s=0):bits(s){}inline bool keyDown(Key k)const{return eadk_keyboard_key_down(*this,(eadk_key_t)k);}constexpr operator eadk_keyboard_state_t()const{return *reinterpret_cast<const eadk_keyboard_state_t*>(this);}private:uint64_t bits;};static inline State scan(){return State(eadk_keyboard_scan());}}
namespace Timing {static inline void msleep(uint32_t ms){eadk_timing_msleep(ms);}}
static inline uint32_t random(){return eadk_random();}
}
#endif