
//  PayOffConstructible.cpp
//  Project
//
//  Created by Tunde Taiwo on 22/05/2019.
//  Copyright © 2019 Tunde Taiwo. All rights reserved.
//

#include "PayOffConstructible.h"
#include "Digital.h"
namespace
{
    PayOffHelper<PayOffCall> RegisterVC("VC");
    PayOffHelper<PayOffPut> RegisterVP("VP");
    PayOffHelper<PayOffCall> RegisterAC("AC");
    PayOffHelper<PayOffPut> RegisterAP("AP");
    PayOffHelper<PayOffDigitalCall> RegisterDC("DC");
    PayOffHelper<PayOffDigitalPut> RegisterDP("DP");                                    
}
