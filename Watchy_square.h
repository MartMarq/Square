#ifndef WATCHY_square_H
#define WATCHY_square_H

#ifdef WATCHY_SIM
    #include "..\..\Watchy.h"
#else // WATCHY_SIM
    #include <Watchy.h>
#endif // WATCHY_SIM
#include "MONOFONT20pt7b.h"


class Watchysquare : public Watchy{
    using Watchy::Watchy;
    public:
        void drawWatchFace();
        void drawTime();
        void drawDate();
        void drawBattery();
};

#endif