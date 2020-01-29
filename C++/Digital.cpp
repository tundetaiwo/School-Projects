//
//  DoubleDigital.cpp
//  Project
//
//  Created by Tunde Taiwo on 17/05/2019.
//  Copyright © 2019 Tunde Taiwo. All rights reserved.
//
#include "Digital.h"


PayOffDigitalCall:: PayOffDigitalCall(double Strike_)
: Strike(Strike_)

{
}
PayOff* PayOffDigitalCall::clone() const
{
    return new PayOffDigitalCall(*this);
}

double PayOffDigitalCall::operator()(double Spot) const

{
    if (Spot <= Strike)
    {return 0;}
    
    else
    {return 1;}
}


PayOffDigitalPut:: PayOffDigitalPut(double Strike_)
: Strike(Strike_)

{
}

PayOff* PayOffDigitalPut::clone() const
{
    return new PayOffDigitalPut(*this);
}


double PayOffDigitalPut::operator()(double Spot) const

{
    if (Spot >= Strike)
        return 0;
    
    else
        return 1;
}
