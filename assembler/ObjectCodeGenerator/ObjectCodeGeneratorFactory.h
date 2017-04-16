#ifndef OCGF_INCLUDED
#define OCGF_INCLUDED

#include <map>
#include "ObjectCodeGenerator.h"
using namespace std;

class ObjectCodeGeneratorFactory {
    private :
    ObjectCodeGeneratorFactory();
    static ObjectCodeGeneratorFactory* objectCodeGeneratorFactoryInstance;

    public :

    ObjectCodeGeneratorFactory* getInstance();

    ObjectCodeGenerator* getObjectCodeGenerator(string type);
};

#endif // OCGF_INCLUDED
