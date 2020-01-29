
//  Created by Tunde Taiwo on 17/05/2019.
//  Copyright © 2019 Tunde Taiwo. All rights reserved.
//

#include "Vanilla.h"

VanillaOption::VanillaOption(const PayOffBridge& ThePayOff_, double Expiry_)
:  ThePayOff(ThePayOff_), Expiry(Expiry_)
{
}

double VanillaOption::GetExpiry() const
{
    return Expiry;
}

double VanillaOption::OptionPayOff(double Spot) const
{
    return  ThePayOff(Spot);
}
