//
//  ConvergenceTable.hpp
//  Project
//
//  Created by Tunde Taiwo on 20/05/2019.
//  Copyright © 2019 Tunde Taiwo. All rights reserved.
//

#ifndef ConvergenceTable_h
#define ConvergenceTable_h

#include "MCStatistics.h"
#include "Wrapper.h"

class ConvergenceTable: public StatisticsMC
{
public:
    ConvergenceTable (const Wrapper<StatisticsMC>& Inner_);
    virtual StatisticsMC* clone() const;
    virtual void DumpOneResult(double result);
    virtual std::vector<std::vector<double>> GetResultsSoFar() const;
    virtual std::vector<std::vector<double>> wholestory() const;

private:
    Wrapper<StatisticsMC> Inner;
    std::vector<std::vector<double> > ResultsSoFar;
    unsigned long StoppingPoint;
    unsigned long PathsDone;
};
#endif /* ConvergenceTable_hpp */
