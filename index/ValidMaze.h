#ifndef VALIDMAZE_H
#define VALIDMAZE_H


class Valid{
    public:
        //constructor
        Valid();
        Valid(unsigned int xLen, unsigned zLen);
        Valid(char** structure,unsigned int xLen, unsigned zLen);
        // function declarations
        bool isolatedCells1(char** structure1);
        void isolatedCells2(char** structure2, unsigned int x, unsigned int y);

        int  numGate(char** structure3);

        bool loopDetection1(char** structure4);
        bool loopDetection2( char** structure5,unsigned int x,unsigned int y,unsigned int x0,unsigned int y0);

        void mazeTrans(unsigned int x, unsigned z);
        char** getArr();

    private:
        unsigned int xlen;
        unsigned int zlen;
        char** structure;
};


#endif