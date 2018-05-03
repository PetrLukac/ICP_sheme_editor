#ifndef SAVER_H
#define SAVER_H

#include <fstream>

#include "block.h"

class Saver
{
public:
    Saver();



    template<class T>
    static void printVectorToOut(std::ostream &file, const std::vector<T> vector)
    {
        for(const T &it: vector)
        {
            file << it << '\n';
        }
    }

};

#endif // SAVER_H
