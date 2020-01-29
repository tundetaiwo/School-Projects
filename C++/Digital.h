
//  Created by Tunde Taiwo on 17/05/2019.
//  Copyright © 2019 Tunde Taiwo. All rights reserved.
//

#ifndef Digital_h
#define Digital_h
#include "PayOff.h"
class PayOffDigitalCall : public PayOff
{
public:
    PayOffDigitalCall(double Strike_);
    virtual double operator()(double Spot) const;
    virtual ~PayOffDigitalCall(){}
    virtual PayOff* clone() const;
    
    
private:
    double Strike;
};

class PayOffDigitalPut : public PayOff
{
public:
    PayOffDigitalPut(double Strike_);
    virtual double operator()(double Spot) const;
    virtual ~PayOffDigitalPut(){}
    virtual PayOff* clone() const;
    
    
private:
    double Strike;
};
#endif
 
 


