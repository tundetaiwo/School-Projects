
//  Created by Tunde Taiwo on 17/05/2019.
//  Copyright © 2019 Tunde Taiwo. All rights reserved.
//

#ifndef Vanilla_h
#define Vanilla_h

#include "PayOffBridge.h"


class VanillaOption
{
public:
    
    VanillaOption(const PayOffBridge& ThePayOff_, double Expiry);
    
    double OptionPayOff(double Spot) const;
    double GetExpiry() const;
    
private:
    
    double Expiry;
    PayOffBridge ThePayOff;
};



#endif /* Vanilla1_hpp */
