
//  Created by Tunde Taiwo on 21/05/2019.
//  Copyright © 2019 Tunde Taiwo. All rights reserved.
//

#ifndef PathDependentAsian_h
#define PathDependentAsian_h

#include "PathDependent.h"
#include "PayOffBridge.h"

class PathDependentAsian: public  PathDependent
{
public: PathDependentAsian(const MJArray& LookAtTimes_, double DelieryTime_, const PayOffBridge& ThePayOff_);
    
    virtual unsigned long MaxNumberOfCashFlows() const;
    virtual MJArray PossibleCashFlowTimes() const;
    virtual unsigned long CashFlows(const MJArray& SpotValues,
                                    std::vector<CashFlow>& GeneratedFlows) const;
    virtual ~PathDependentAsian(){}
    virtual PathDependent* clone() const;
private:
    double DeliveryTime;
    PayOffBridge ThePayOff;
    unsigned long NumberOfTimes;
};


#endif /* PathDependentAsian_hpp */
