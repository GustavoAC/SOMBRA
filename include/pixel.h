#pragma once

using color_t = unsigned char;

class Pixel {
   private:
    color_t m_colors[3];

   public:
    Pixel(color_t _r = 0, color_t _g = 0, color_t _b = 0) {
        m_colors[0] = _r;
        m_colors[1] = _g;
        m_colors[2] = _b;
    }

    inline color_t getR() const { return m_colors[0]; }

    inline color_t getG() const { return m_colors[1]; }

    inline color_t getB() const { return m_colors[2]; }

    inline bool operator==(const Pixel& rhs) {
        return (getR() == rhs.getR() && getG() == rhs.getG() && getB() == rhs.getB());
    }

    inline bool operator!=(const Pixel& rhs) { return !(*this == rhs); }
};

static const Pixel COLOR_BLACK = Pixel(0,0,0);
static const Pixel COLOR_RED = Pixel(255,0,0);
static const Pixel COLOR_GREEN = Pixel(0,255,0);
static const Pixel COLOR_BLUE = Pixel(0,0,255);
static const Pixel COLOR_WHITE = Pixel(255,255,255);

Pixel GET_COLOR(const std::string &colorName) {
    if (colorName == "black") return COLOR_BLACK;
    if (colorName == "red") return COLOR_RED;
    if (colorName == "green") return COLOR_GREEN;
    if (colorName == "blue") return COLOR_BLUE;
    
    return COLOR_WHITE;
}