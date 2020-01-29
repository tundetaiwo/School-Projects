
//  Created by Tunde Taiwo on 17/05/2019.
//  Copyright © 2019 Tunde Taiwo. All rights reserved.
//

#ifndef Random_Modern_h
#define Random_Modern_h

#include "Arrays.h"
#include "Random.h"

class RandomTwist : public RandomBase
{
public:
   
    RandomTwist(unsigned long Dimensionality, unsigned long InitialSeed_ = 1UL);

    virtual RandomBase* clone() const;    
    virtual void GetUniforms(MJArray& variates);
    virtual void Skip(unsigned long numberOfPaths);
    virtual void SetSeed(unsigned long Seed);
    virtual void Reset();

private:
    
    unsigned long InitialSeed;
};

#endif



