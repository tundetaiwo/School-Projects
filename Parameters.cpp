//
//  Parameters.cpp
//  Project
//
//  Created by Tunde Taiwo on 17/05/2019.
//  Copyright © 2019 Tunde Taiwo. All rights reserved.
//

#include "Parameters.h"

Parameters::Parameters(const ParametersInner& innerObject)
{
    InnerObjectPtr = innerObject.clone();
}

Parameters::Parameters(const Parameters& original)
{
    InnerObjectPtr = original.InnerObjectPtr -> clone();
}


Parameters& Parameters::operator = (const Parameters& original)
{
    if (this!= &original)
    {
        delete InnerObjectPtr;
        InnerObjectPtr = original.InnerObjectPtr -> clone();
 }
    return *this;
}
Parameters:: ~Parameters()
{
    delete InnerObjectPtr;
}

double Parameters::Mean(double time1, double time2) const
{
    double total = Integral(time1, time2);
    return total/(time2-time1);
}

double Parameters::RootMeanSquare(double time1, double time2) const
{
    double total = IntegralSquare(time1,time2);
    return total/(time2-time1);
}
ParametersConstant::ParametersConstant(double constant)
{
    Constant = constant;
    ConstantSquare = Constant*Constant;
}

ParametersInner* ParametersConstant::clone() const
{
    return new ParametersConstant(*this);
}
double ParametersConstant::Integral(double time1, double time2) const
{
    return (time2-time1)*Constant;
}

double ParametersConstant::IntegralSquare(double time1, double time2) const
{
    return (time2 - time1)*ConstantSquare;
}

//ParametersPiecewiseConstant

ParametersPiece::ParametersPiece(std::vector< std::vector<double>> constant)
{
    Constant = constant;
    ConstantSquare = constant;
    
    for (unsigned long i = 0; i < Constant[0].size(); i++) {
        ConstantSquare[0][i] = Constant[0][i] * Constant[0][i];
    }
}

ParametersInner* ParametersPiece::clone() const
{
    return new ParametersPiece(*this);
}


double ParametersPiece::Integral(double time1, double time2) const
{
    std::vector<std::vector<double>> param(Constant);
    
    double result = 0.0;
    
    for (unsigned long i = 0; i < param[0].size(); i++) {
        param[1][i] = std::max(param[1][i], time1);
        param[1][i] = std::min(param[1][i], time2);
        param[2][i] = std::max(param[2][i], time1);
        param[2][i] = std::min(param[2][i], time2);
        result += (param[2][i] - param[1][i])*param[0][i];
    }
    return result;
    
    
}

double ParametersPiece::IntegralSquare(double time1, double time2) const
{
    std::vector<std::vector<double>> param(ConstantSquare);
    
    double result = 0.0;
    
    for (unsigned long i = 0; i < param[0].size(); i++) {
        param[1][i] = std::max(param[1][i], time1);
        param[1][i] = std::min(param[1][i], time2);
        param[2][i] = std::max(param[2][i], time1);
        param[2][i] = std::min(param[2][i], time2);
        result += (param[2][i] - param[1][i])*param[0][i];
    }
    
    return result;
}
