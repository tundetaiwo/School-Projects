
//  Created by Tunde Taiwo on 23/05/2019.
//  Copyright © 2019 Tunde Taiwo. All rights reserved.
//


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>
#include "Date.h"
#include "PayOffFactory.h"
#include "PayOffConstructible.h"
#include <iostream>
#include "PayOff.h"
#include <string>
#include "Vanilla.h"
#include "Parameters.h"
#include "Arrays.h"
#include "Digital.h"
#include <numeric>
#include "MCStatistics.h"
#include "ConvergenceTable.h"
#include "AntiThetic.h"
#include "PathDependentAsian.h"
#include "ExoticBSEngine.h"
#include "RandomModern.h"
#include "SimpleMC.h"
using namespace std;



int main()
{
    //Timing the program run duration
    auto alpha = chrono::steady_clock::now();
    
    //Declaring variables
    int DealNumber;
    string DealType;
    string Index;
    double Strike;
    string Expiry1;
    string Expiry2;
    string Expiry3;
    double Mat1;
    double Mat2 = 0.0;
    double Mat3 = 0.0;
    double Spot = 0.0;
    double d = 0; // dividends functionality is included but we set it to zero.
    unsigned long NumberOfRuns = 100;
    unsigned long NumberOfPaths = 10000;
    unsigned NumberOfDates = 3;
    string ConvergenceTab;
    string ConInt;
    string Scenario;
    double r = 0.0;
    double Vol = 0.0;
    vector<vector<double>> Rr(3);
    vector<vector<double>> Vv(3);
    vector<double> Volv(5,0);
    vector<double> Rv(5,0);
    vector<double> times1(5,0);
    vector<double> times2(5,0);
    vector<double> Percentiles(NumberOfRuns,1);
    
    //Extracting  Inputs
    ifstream ifs("/Users/danieltaiwo/Documents/MSFM/CPP/Project-Real/Final-Project-Inputs.txt");
    if (!ifs.is_open())
    {
        cout << "Error opening file." << endl;
        return -1;
    }
    
    //Convergence Tables On or Off
    cout << "Convergence Tables On/Off?" << endl;
    cout << "Warning: Confidence Intervals and Convergence Tables Cannot Both Run At Once." << endl;
    cin >> ConvergenceTab;
    if(ConvergenceTab != "On" && ConvergenceTab != "Off")
    {
        cout << "Error: Invalid input, please type 'On' or 'Off' " << endl;
        return 0;
    }
   
    //Confidence Intervals On or Off
    cout << "Confidence Intervals On/Off?" << endl;;
    cin >> ConInt;
    
    if(ConInt != "On" && ConInt != "Off")
    {
        cout << "Error: Invalid input, please type 'On' or 'Off'" << endl;
        return 0;
    }
    
    //ensuring that both CI and C Tables are both not switched on - code takes too long to run.
    if(ConvergenceTab == "On" && ConInt== "On")
    {
        cout << "Error: Convergence Tables and Confidence Intervals cannot both be on." << endl;
    }
    //only run pricing functions once for C tables on or CI off.
    if (ConvergenceTab == "On" || ConInt == "Off")
    {
        NumberOfRuns = 1;
    }
    // Scenario Selection
    cout << "Enter Scenario" << endl;
    cin >> Scenario;
    
    
    while (!ifs.eof())
    {
        //obtains lines from input to analyse
        string line;
        while (getline(ifs, line))
        {
            istringstream ss(line);
            ss >> DealNumber >> DealType >> Index >> Strike >> Expiry1;
            
            //file extract for asian option
            if (ss >> Expiry2 >> Expiry3)
            {
                ss >> DealNumber >> DealType >> Index >> Strike >> Expiry1 >> Expiry2 >> Expiry3;
                cout << "\n"<< DealNumber << " | " << DealType << " | " << Index
                << " | " << Strike << " | " << Expiry1 << " | " << Expiry2 << " | " << Expiry3 << endl;
                
                string Sexp1 = Expiry1;
                Sexp1.erase(remove(Sexp1.begin(), Sexp1.end(), '-'), Sexp1.end());
                long Nexp1 = atol(Sexp1.c_str());
                
                string Sexp2 = Expiry2;
                Sexp2.erase(remove(Sexp2.begin(), Sexp2.end(), '-'), Sexp2.end());
                long Nexp2 = atol(Sexp2.c_str());
                
                string Sexp3 = Expiry3;
                Sexp3.erase(remove(Sexp3.begin(), Sexp3.end(), '-'), Sexp3.end());
                long Nexp3 = atol(Sexp3.c_str());
                
                int year1, month1, day1, year2, month2, day2, year3, month3, day3;
                
                //obtaining the year, month and day from the expiry date
                year1 = Nexp1/10000.0;
                Nexp1 %= 10000;
                month1 = Nexp1 / 100.0;
                day1 = Nexp1 % 100;
                Date Maturity1(year1, month1, day1);
                
                year2 = Nexp2/10000.0;
                Nexp2 %= 10000;
                month2 = Nexp2/100.0;
                day2 = Nexp2 % 100;
                Date Maturity2(year2, month2, day2);
                
                year3 = Nexp3 / 10000.0;
                Nexp3 %= 10000;
                month3 = Nexp3 / 100.0;
                day3 = Nexp3 % 100;
                Date Maturity3(year3, month3, day3);
                
                Mat1 = max(Date::today().daysDifference(Maturity1),0) / 365.0;
                Mat2 = max(Date::today().daysDifference(Maturity2),0) / 365.0;
                Mat3 = max(Date::today().daysDifference(Maturity3),0) / 365.0;

            }
            else
            {
                ss >> DealNumber >> DealType >> Index >> Strike >> Expiry1;
                cout << "\n" << DealNumber << " | " << DealType << " | " << Index << " | " << Strike << " | " << Expiry1 << endl;
                
                string Sexp1 = Expiry1;
                Sexp1.erase(remove(Sexp1.begin(), Sexp1.end(), '-'), Sexp1.end());
                long Nexp1 = atol(Sexp1.c_str());
                
                int year, month, day;
                
                year = Nexp1 / 10000.0;
                Nexp1 %= 10000;
                month = Nexp1 / 100.0;
                day = Nexp1 % 100;
                Date Maturity(year, month, day);
                Mat1 = max(Date::today().daysDifference(Maturity),0) / 365.0;
                
            }
          ;
            
            times1[0] = max(Date::today().daysDifference(Date(2019,3,1)),0) / 365.0;
            times1[1] = max(Date::today().daysDifference(Date(2019,4,1)),0) / 365.0;
            times1[2] = max(Date::today().daysDifference(Date(2019,5,1)),0) / 365.0;
            times1[3] = max(Date::today().daysDifference(Date(2019,6,1)),0) / 365.0;
            times1[4] = max(Date::today().daysDifference(Date(2019,7,1)),0) / 365.0;
            
            times2[0] = max(Date::today().daysDifference(Date(2019,4,1)),0) / 365.0;
            times2[1] = max(Date::today().daysDifference(Date(2019,5,1)),0) / 365.0;
            times2[2] = max(Date::today().daysDifference(Date(2019,6,1)),0) / 365.0;
            times2[3] = max(Date::today().daysDifference(Date(2019,7,1)),0) / 365.0;
            
            if(DealType == "AC" ||DealType ==  "AP")
            {
                times2[4] = Mat3;
            }
            else
            {
                times2[4] = Mat1;
            }
            
            Vv[1] = times1;
            Vv[2] = times2;
            
            Rr[1] = times1;
            Rr[2] = times2;
            
          
            if (Scenario == "1")
            {
                r = 0.025;
                if (Index == "S")
                {
                    Vol = 0.17;
                    Spot = 2700;
                }
                else if (Index == "E")
                {
                 Vol = 0.15;
                 Spot = 3080;
                }
                else
                {
                    cout << "Please Enter Inputs with a Correct Index. " << endl;
                    return 0;
                }
                // pointer to payoff depending on what the option type is.
                ParametersConstant VolParam(Vol);
                ParametersConstant rParam(r);
                ParametersConstant dParam(d);
                PayOff* PayOffPtr = PayOffFactory::Instance().CreatePayOff(DealType,Strike);

                
                if (DealType == "VC" ||DealType == "VP" ||DealType == "DP" ||DealType == "DC")
                {
                    vector<vector<double>> results;
                    for (int i=0 ; i < NumberOfRuns; i++)
                    {
                        StatisticsMean gatherer;
                        ConvergenceTable gathererTwo(gatherer);
                        RandomTwist generator(1);
                        AntiThetic GenTwo(generator);
                        PayOffCall thePayOff(Strike);
                        VanillaOption theOption(*PayOffPtr, Mat1);
                        SimpleMonteCarlo(theOption,
                                      Spot,
                                      VolParam,
                                      rParam,
                                      NumberOfPaths,
                                      gathererTwo,
                                      GenTwo);
                    
                        results = gathererTwo.GetResultsSoFar();
                        Percentiles[i] =  results[results.size()-1][0];
                        if (ConvergenceTab == "On")
                        {
                            for (unsigned long i=0; i < results.size(); i++)
                            {
                                for (unsigned long j=0; j < results[i].size(); j++)
                                    cout << results[i][j] << " ";
                                
                                cout << "\n";
                           
                            }
                        }
                        else {}
                    }
                    if (ConInt == "On")
                    {
                        sort(Percentiles.begin(), Percentiles.end());
                        float average = accumulate(Percentiles.begin(), Percentiles.end(), 0.0)/Percentiles.size();
                        cout <<"\nFor the " <<  DealType << " Option The Price is: " << average << endl;;
                        cout << "The 50th Percentile is: "<< Percentiles[49] << endl;
                        cout << "The 10th Percentile is: "<< Percentiles[9] << endl;
                        cout << "The 90th Percentile is: "<< Percentiles[89] << endl;
                    }
                    else if (ConInt == "Off")
                    {
                          cout <<"\nFor the " <<  DealType <<" Option Using " << NumberOfPaths<< " Number of Paths the Price is: " << results[results.size()-1][0] << endl;
                    }
                    
                }
                    
         
                else if(DealType == "AC" ||DealType == "AP")
                {
                    vector<vector<double>> results;
                    for (int i=0 ; i < NumberOfRuns; i++)
                    {
                
                    StatisticsMean gatherer;
                    ConvergenceTable gathererTwo(gatherer);
                    RandomTwist generator(1);
                    AntiThetic GenTwo(generator);
                    MJArray times(NumberOfDates);
                    times[0] = Mat1;
                    times[1] = Mat2;
                    times[2] = Mat3;
                    PathDependentAsian theOption(times, Mat3, *PayOffPtr);
                    ExoticBSEngine theEngine(theOption, rParam, dParam,
                                             VolParam, GenTwo, Spot);
                    theEngine.DoSimulation(gathererTwo, NumberOfPaths);
                    results = gathererTwo.GetResultsSoFar();
                        
                        if (ConvergenceTab == "On")
                        {
                            for (unsigned long i=0; i < results.size(); i++)
                            {
                                for (unsigned long j=0; j < results[i].size(); j++)
                                    cout << results[i][j] << " ";
                                
                                cout << "\n";
                            }

                        }
                        else {}
                        Percentiles[i] =  results[results.size()-1][0];

                    }
   
                    if (ConInt == "On")
                    {
                        sort(Percentiles.begin(), Percentiles.end());
                        float average = accumulate(Percentiles.begin(), Percentiles.end(), 0.0)/Percentiles.size();
                        cout <<"\nFor the " <<  DealType << " Option The Price is: " << average << endl;;
                        cout << "The 50th Percentile is: "<< Percentiles[49] << endl;
                        cout << "The 10th Percentile is: "<< Percentiles[9] << endl;
                        cout << "The 90th Percentile is: "<< Percentiles[89] << endl;
                    }
                    else if (ConInt == "Off")
                    {
                           cout <<"\nFor the " <<  DealType <<" Option Using " << NumberOfPaths<< " Number of Paths the Price is: " << results[results.size()-1][0] << endl;
                    }
               }
                
            }

           //Setting non-constant parameters for each index.
            else if  (Scenario == "2")
            {
                Rv[0] = 0.025;
                Rv[1] = 0.02;
                Rv[2] = 0.01;
                Rv[3] = 0.01;
                Rv[4] = 0.005;
                Rr[0] = Rv;
                if (Index == "S")
                {
                    Volv[0] = 0.2;
                    Volv[1] = 0.2;
                    Volv[2] = 0.19;
                    Volv[3] = 0.18;
                    Volv[4] = 0.17;
                
                    Vv[0] = Volv;
                    
                    Spot = 2700;
                }
                else if (Index == "E")
                {
                    Volv[0] = 0.25;
                    Volv[1] = 0.2;
                    Volv[2] = 0.18;
                    Volv[3] = 0.16;
                    Volv[4] = 0.15;
                    Vv[0] = Volv;
                    Spot =  3080;
                }
                else
                {
                    cout << "Please Enter Inputs with a Correct Index. " << endl;
                    return 0;
                }
                //Uses factory to point to the correct pay off type.
                PayOff* PayOffPtr = PayOffFactory::Instance().CreatePayOff(DealType,Strike);
                ParametersConstant dParam(d);
                ParametersPiece RrParam(Rr);
                ParametersPiece VvParam(Vv);
                
                if (DealType == "VC" ||DealType == "VP" ||DealType == "DP" ||DealType == "DC")
                {
                    vector<vector<double>> results;

                    for (int i=0 ; i < NumberOfRuns; i++)
                    {
                        StatisticsMean gatherer;
                        ConvergenceTable gathererTwo(gatherer);
                        RandomTwist generator(1);
                        AntiThetic GenTwo(generator);
                        PayOffCall thePayOff(Strike);
                        VanillaOption theOption(*PayOffPtr, Mat1);
                        SimpleMonteCarlo(theOption,
                                          Spot,
                                          VvParam,
                                          RrParam,
                                          NumberOfPaths,
                                          gathererTwo,
                                          GenTwo);
                        
                        results = gathererTwo.GetResultsSoFar();
                        if (ConvergenceTab == "On")
                        {
                            for (unsigned long i=0; i < results.size(); i++)
                            {
                                for (unsigned long j=0; j < results[i].size(); j++)
                                    cout << results[i][j] << " ";
                                
                                cout << "\n";
                                
                            }
                        }
                        else {}
                        Percentiles[i] =  results[results.size()-1][0];
                    }
                    if (ConInt == "On")
                    {
                        sort(Percentiles.begin(), Percentiles.end());
                        float average = accumulate(Percentiles.begin(), Percentiles.end(), 0.0)/Percentiles.size();
                        cout <<"\nFor the " <<  DealType << " Option The Price is: " << average << endl;;
                        cout << "The 50th Percentile is: "<< Percentiles[49] << endl;
                        cout << "The 10th Percentile is: "<< Percentiles[9] << endl;
                        cout << "The 90th Percentile is: "<< Percentiles[89] << endl;
                    }
                    else if (ConInt == "Off")
                    {
                          cout <<"\nFor the " <<  DealType <<" Option Using " << NumberOfPaths<< " Number of Paths the Price is: " << results[results.size()-1][0] << endl;
                    }
                    
                }
                
                else if(DealType == "AC" ||DealType == "AP")
                {
                    vector<vector<double>> results;
                    for (int i=0 ; i < NumberOfRuns; i++)
                    {
                        StatisticsMean gatherer;
                        ConvergenceTable gathererTwo(gatherer);
                        RandomTwist generator(1);
                        AntiThetic GenTwo(generator);
                        MJArray times(NumberOfDates);
                        times[0] = Mat1;
                        times[1] = Mat2;
                        times[2] = Mat3;
                        PathDependentAsian theOption(times, Mat3, *PayOffPtr);
                        ExoticBSEngine theEngine(theOption, RrParam, dParam,
                                                 VvParam, GenTwo, Spot);
                        theEngine.DoSimulation(gathererTwo, NumberOfPaths);
                        results = gathererTwo.GetResultsSoFar();
                        if (ConvergenceTab == "On")
                        {
                            for (unsigned long i=0; i < results.size(); i++)
                            {
                                for (unsigned long j=0; j < results[i].size(); j++)
                                    cout << results[i][j] << " ";
                                
                                cout << "\n";
                                
                            }
                        }
                        else {}
                        Percentiles[i] =  results[results.size()-1][0];
                    }
                    
                    if (ConInt == "On")
                    {
                        sort(Percentiles.begin(), Percentiles.end());
                        float average = accumulate(Percentiles.begin(), Percentiles.end(), 0.0)/Percentiles.size();
                        cout <<"\nFor the " <<  DealType << " Option The Price is: " << average << endl;;
                        cout << "The 50th Percentile is: "<< Percentiles[49] << endl;
                        cout << "The 10th Percentile is: "<< Percentiles[9] << endl;
                        cout << "The 90th Percentile is: "<< Percentiles[89] << endl;
                    }
                    else if (ConInt == "Off")
                    {
                         cout <<"\nFor the " <<  DealType <<" Option Using " << NumberOfPaths<< " Number of Paths the Price is: " << results[results.size()-1][0] << endl;
                    }
                }
               
            }
            else //Error message in the event invalid scenario entered.
            {
                cout << "Please Enter a Valid Scenario." << endl;
                return 0;
            }
            
        }
    }
    
    //outputting the time it took to run program.
    auto omega = chrono::steady_clock::now();
    auto delta = omega - alpha;
    cout <<"\nExecution Time: "<< endl;
    typedef std::chrono::duration<float> float_seconds;
    cout << chrono::duration_cast <float_seconds> (delta).count()<< " seconds" << endl;
    cout << "which is the same as " << endl;
    cout << chrono::duration_cast <float_seconds> (delta).count()/60 << " minutes" << endl;

    return 0;

}

    


