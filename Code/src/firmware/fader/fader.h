
#ifndef MFADER_H
#define MFADER_H

class MFader {
    private:
        const int index;
        bool touched = 0;

        int updatePosition();
        void moveUp();
        void moveDown();

    public:
        int position;

        MFader(int index);

        void moveStop();
        int getPosition();
        int moveToPosition(int newPosition);
        bool getTouched();
        bool setTouched(bool value);
};






void spi_init_mcp3008();
#endif // MFADER_H