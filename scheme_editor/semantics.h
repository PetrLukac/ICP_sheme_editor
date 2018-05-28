/*****
 * file: semantics.h
 * author: Peter Lukac xlukac11
 * */

#ifndef SEMANTICS_H
#define SEMANTICS_H
#include <vector>
#include <string>


/***********
 * Semantics provides computation of data presend in the blocks
 * class is implemented as singleton
 * */
class Semantics
{
public:

    /*************
     * computeData computes given data based on implemented instructions
     * @param value array of values
     * @param type array of types
     * @param opcode oparation
     * */
    double computeData( const std::vector<double> &value,
                     const std::vector<std::string> &type,
                     const std::string &opcode);

    /***************
     * getInstance returns instance of singleton
     * */
    static Semantics& getInstance(){
        static Semantics instance;

        return instance;
    }
private:
    Semantics() {}
    Semantics(Semantics const &);
    void operator =(Semantics const&);
};

#endif // SEMANTICS_H
