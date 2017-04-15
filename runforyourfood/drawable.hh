#ifndef DRAWABLE_HH
# define DRAWABLE_HH

# include <Gamebuino.h>

namespace RFYF
{
    class Drawable
    {
    public:
        Drawable(Gamebuino& gb, int8_t width, int8_t height, int8_t x, int8_t y)
            : _gb(gb)
            , _width(width)
            , _height(height)
            , _x(x)
            , _y(y)
        {}
        
        virtual ~Drawable() {}

        virtual void draw() {
            _gb.display.drawBitmap(getLeft(), getBottom(), getFrame());
        }

        int8_t getLeft() { return _x; }
        int8_t getRight() { return _x + _width - 1; }
        int8_t getTop() { return LCDHEIGHT - _y; }
        int8_t getBottom() { return LCDHEIGHT - _height - _y; }

        virtual const byte* getFrame() = 0;

    protected:
        Gamebuino& _gb;
        int8_t     _width;
        int8_t     _height;
        int8_t     _x;
        int8_t     _y;

    }; // End of class Drawable

} // End of namespace RFYF

#endif // ! DRAWABLE_HH
