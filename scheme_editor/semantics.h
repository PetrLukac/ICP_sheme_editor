#ifndef SEMANTICS_H
#define SEMANTICS_H
#include <vector>
#include <string>


class Semantics
{
public:

    int computeData( const std::vector<double> &value,
                     const std::vector<std::string> &type,
                     const std::string &opcode);
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
