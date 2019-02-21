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

	inline color_t getR() const {
		return m_colors[0];
	}

	inline color_t getG() const {
		return m_colors[1];
	}

	inline color_t getB() const {
		return m_colors[2];
	}
};