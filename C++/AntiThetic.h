//
//  AntiThetic.hpp
//  Project
//
//  Created by Tunde Taiwo on 20/05/2019.
//  Copyright © 2019 Tunde Taiwo. All rights reserved.
//

#ifndef AntiThetic_h
#define AntiThetic_h

#include "Random.h"
#include "Wrapper.h"


class AntiThetic : public RandomBase
{public:
    AntiThetic(const Wrapper<RandomBase>& innerGenerator );
    virtual RandomBase* clone() const;
    virtual void GetUniforms(MJArray& variates);
    virtual void Skip(unsigned long numberOfPaths);
    virtual void SetSeed(unsigned long Seed);
    virtual void ResetDimensionality(unsigned long
                                     NewDimensionality);
    virtual void Reset();
private:
    Wrapper<RandomBase> InnerGenerator;
    bool OddEven;
    MJArray NextVariates;
};
#endif

