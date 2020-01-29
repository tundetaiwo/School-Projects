
//  Created by Tunde Taiwo on 17/05/2019.
//  Copyright © 2019 Tunde Taiwo. All rights reserved.
//

#include "SimpleMC.h"
#include "Random.h"
#include <cmath>
#

// the basic math functions should be in namespace std but aren't in VCPP6
#if !defined(_MSC_VER)
using namespace std;
#endif

void SimpleMonteCarlo(const VanillaOption& TheOption,
                       double Spot,
                       const Parameters& Vol,
                       const Parameters& r,
                       unsigned long NumberOfPaths,
                       StatisticsMC& gatherer,
                       RandomBase& generator)
{
    generator.ResetDimensionality(1);
    double Expiry = TheOption.GetExpiry();
    double variance = Vol.IntegralSquare(0,Expiry);
    double rootVariance = sqrt(variance);
    double itoCorrection = -0.5*variance;
    double movedSpot = Spot*exp(r.Integral(0,Expiry)
                                + itoCorrection);
    double thisSpot;
    double discounting = exp(-r.Integral(0,Expiry));
    MJArray VariateArray(1);
    for (unsigned long i=0; i < NumberOfPaths; i++)
    {
        generator.GetGaussians(VariateArray);
        thisSpot = movedSpot*exp(rootVariance*VariateArray[0]);
        double thisPayOff = TheOption.OptionPayOff(thisSpot);
        gatherer.DumpOneResult(thisPayOff*discounting);
    }
    return;
}
