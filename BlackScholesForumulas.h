//
//  BlackScholesForumulas.hpp
//  Project
//
//  Created by Tunde Taiwo on 23/05/2019.
//  Copyright © 2019 Tunde Taiwo. All rights reserved.
//

#ifndef BlackScholesForumulas_h
#define BlackScholesForumulas_h

double BlackScholesCall(double Spot,
                        double Strike,
                        double r,
                        double d,
                        double Vol,
                        double Expiry);
double BlackScholesPut(double Spot,
                       double Strike,
                       double r,
                       double d,
                       double Vol,
                       double Expiry);

double BlackScholesDigitalCall(double Spot,
                               double Strike,
                               double r,
                               double d,
                               double Vol,
                               double Expiry);
double BlackScholesCallVega(double Spot,
                            double Strike,
                            double r,
                            double d,
                            double Vol,
                            double Expiry);
#endif
