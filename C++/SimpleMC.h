
//  Created by Tunde Taiwo on 17/05/2019.
//  Copyright © 2019 Tunde Taiwo. All rights reserved.
//

#ifndef SimpleMC_h
#define SimpleMC_h

#include "Parameters.h"
#include "Vanilla.h"
#include "MCStatistics.h"
#include "Random.h"

void SimpleMonteCarlo(const VanillaOption& TheOption,
                       double Spot,
                       const Parameters& Vol,
                       const Parameters& r,
                       unsigned long NumberOfPaths,
                       StatisticsMC& gatherer,
                       RandomBase& generator);


#endif /* SimpleMC_hpp */
