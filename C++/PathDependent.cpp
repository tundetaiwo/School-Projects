//
//  PathDependent.cpp
//  Project
//
//  Created by Tunde Taiwo on 21/05/2019.
//  Copyright © 2019 Tunde Taiwo. All rights reserved.
//

#include "PathDependent.h"

PathDependent::PathDependent(const MJArray& LookAtTimes_)
: LookAtTimes(LookAtTimes_)
{}
const MJArray& PathDependent::GetLookAtTimes() const
{
    return LookAtTimes;
}
