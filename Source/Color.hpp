#ifndef _SPLITCELL_DATGUI_COLOR_HPP_
#define _SPLITCELL_DATGUI_COLOR_HPP_

namespace splitcell
{
	namespace datgui
	{
		class Color
		{
			private:
				float m_Values[4];

			public:
				Color() : m_Values{1.0f, 1.0f, 1.0f, 1.0f}
				{

				}

				Color(float r, float g, float b) : m_Values{r,g,b,1.0f}
				{

				}

				Color(float r, float g, float b, float a) : m_Values{r,g,b,a}
				{

				}

				Color(int r, int g, int b, int a) : m_Values{r/255.0f,g/255.0f,b/255.0f,a/255.0f}
				{

				}

				Color(int r, int g, int b) : m_Values{r/255.0f,g/255.0f,b/255.0f,1.0f}
				{

				}

				Color(float rgba) : m_Values{rgba,rgba,rgba,rgba}
				{

				}
				
				inline const float* values() const
				{
					return m_Values;
				}

				void set(float r, float g, float b, float a)
				{
					m_Values[0] = r;
					m_Values[1] = g;
					m_Values[2] = b;
					m_Values[3] = a;
				}

				void lerp(const Color& second, float amount)
				{
					float iamount = 1.0f-amount;
					for(int i = 0; i < 4; i++)
					{
						m_Values[i] = second.m_Values[i]*amount + m_Values[i]*iamount;
					}
				}

				void mul(const Color& second)
				{
					for(int i = 0; i < 4; i++)
					{
						m_Values[i] *= second.m_Values[i];
					}
				}

				void red(float r) { m_Values[0] = r; }
				void green(float r) { m_Values[1] = r; }
				void blue(float r) { m_Values[2] = r; }
				void alpha(float r) { m_Values[3] = r; }

				float red() const { return m_Values[0]; }
				float green() const { return m_Values[1]; }
				float blue() const { return m_Values[2]; }
				float alpha() const { return m_Values[3]; }

				float r() const { return m_Values[0]; }
				float g() const { return m_Values[1]; }
				float b() const { return m_Values[2]; }
				float a() const { return m_Values[3]; }
		};
	}
}
#endif