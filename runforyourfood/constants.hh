#ifndef CONSTANTS_HH
# define CONSTANTS_HH

# include <Gamebuino.h>

namespace RFYF
{
    namespace constants
    {
        const int8_t GROUND_HEIGHT = 5;

        namespace player
        {
            const int8_t HSPEED = 2;
            const int8_t VSPEED = 3;
            const int8_t HEIGHT = 9;
            const int8_t WIDTH = 5;
        } // End of namespace player

        const int8_t BIRD_HSPEED = 2;
        const int8_t BIRD_VSPEED = 1;

    } // End of namespace constants

} // End of namespace RFYF

#endif // ! CONSTANTS_HH
