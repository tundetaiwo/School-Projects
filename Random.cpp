
//  Created by Tunde Taiwo on 20/05/2019.
//  Copyright © 2019 Tunde Taiwo. All rights reserved.
//

#include "Random.h"
#include "Normals.h"
#include <cstdlib>
#include "RandomModern.h"
#include <random>

void RandomBase::GetGaussians(MJArray& variates)
{
    GetUniforms(variates);
    for (unsigned long i=0; i < Dimensionality; i++)
    {
        double x=variates[i];
        variates[i] = InverseCumulativeNormal(x);
    }
}
void RandomBase::ResetDimensionality(unsigned long
                                     NewDimensionality)
{
    Dimensionality = NewDimensionality;
}
RandomBase::RandomBase(unsigned long Dimensionality_)
: Dimensionality(Dimensionality_)
{
}
