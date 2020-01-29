
//  Created by Tunde Taiwo on 17/05/2019.
//  Copyright © 2019 Tunde Taiwo. All rights reserved.
//

#include "RandomModern.h"
#include <random>
#include "time.h"
#include <vector>


// the basic math functions should be in namespace std but aren't in VCPP6
#if !defined(_MSC_VER)
using namespace std;
#endif

RandomTwist::RandomTwist(unsigned long Dimensionality, unsigned long InitialSeed_)
: RandomBase(Dimensionality), InitialSeed(InitialSeed_)
{
    SetSeed(InitialSeed);
}

RandomBase* RandomTwist::clone() const
{
    return new RandomTwist(*this);
}

void RandomTwist::GetUniforms(MJArray& variates)
{
    
    random_device source;
    seed_seq seq{source(),source(),source()};
    mt19937 engine(seq);

        for (unsigned long i=0; i < GetDimensionality(); i++)
        {
            uniform_real_distribution<double> unidist(0.0,1.0);
            variates[i] = unidist(engine);
        }
     
}

void RandomTwist::Skip(unsigned long numberOfPaths)
{
    MJArray tmp(GetDimensionality());
    for (unsigned long j=0; j < numberOfPaths; j++)
        for (unsigned long i=0; i < GetDimensionality(); i++)
            GetUniforms(tmp);
}

void RandomTwist::SetSeed(unsigned long Seed)
{

    //srand(static_cast<unsigned int>(Seed));

}

void RandomTwist::Reset()
{
    SetSeed(InitialSeed);
}

