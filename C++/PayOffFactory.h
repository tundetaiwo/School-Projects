
//  Created by Tunde Taiwo on 21/05/2019.
//  Copyright © 2019 Tunde Taiwo. All rights reserved.
//

#ifndef PayOffFactory_h
#define PayOffFactory_h

#include "PayOff.h"

#include <map>
#include <string>

class PayOffFactory
{
public:
    
    typedef PayOff* (*CreatePayOffFunction)(double );
    
    static PayOffFactory& Instance();
    void RegisterPayOff(std::string, CreatePayOffFunction);
    PayOff* CreatePayOff(std::string PayOffId,double Strike);
    ~PayOffFactory(){};
    
private:
    std::map<std::string, CreatePayOffFunction> TheCreatorFunctions;
    PayOffFactory(){}
    PayOffFactory(const PayOffFactory&){}
    PayOffFactory& operator=(const PayOffFactory&){ return *this;}
    
};

#endif /* PayOffFactory_hpp */
