#include "mcp3008.h"


#ifndef MFADER_H
#define MFADER_H

class MFader {
    private:
        const int index;
        bool touched = 0;

        uint8_t updatePosition();
        void moveUp();
        void moveDown();

    public:
        uint8_t position;

        MFader(int index);

        void moveStop();
        uint8_t getPosition();
        uint8_t moveToPosition(uint8_t newPosition);
        bool getTouched();
        bool setTouched(bool value);
};






#endif // MFADER_H