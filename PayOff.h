
//  Created by Tunde Taiwo on 17/05/2019.
//  Copyright © 2019 Tunde Taiwo. All rights reserved.
//


#ifndef PayOff3_h
#define PayOff3_h

class PayOff
{
public:
    
    PayOff(){};
    
    virtual double operator()(double Spot) const=0;
    virtual ~PayOff(){}
    virtual PayOff* clone() const=0;
    
private:
    
};

class PayOffCall : public PayOff
{
public:
    
    PayOffCall(double Strike_);
    
    virtual double operator()(double Spot) const;
    virtual ~PayOffCall(){}
    virtual PayOff* clone() const;
    
private:
    
    double Strike;
    
};


class PayOffPut : public PayOff
{
public:
    
    PayOffPut(double Strike_);
    
    virtual double operator()(double Spot) const;
    virtual ~PayOffPut(){}
    virtual PayOff* clone() const;
    
private:
    
    double Strike;
    
};


#endif
