//---------------------------------------------------------------------------
// TestNCIDoubleLocalDiffClimateGrowth.cpp
//---------------------------------------------------------------------------
#include "TestNCIDoubleLocalDiffClimateGrowth.h"
#include <gtest/gtest.h>
#include <fstream>
#include <math.h>
#include "TreePopulation.h"
#include "SimManager.h"
#include "BehaviorBase.h"
#include "DataTypes.h"
#include "NCIEffectsList.h"
#include "NCI/PrecipitationEffectBase.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////
// TestRun1()
////////////////////////////////////////////////////////////////////////////
TEST(NCIDoubleLocalDiffClimateGrowth, TestRun1) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTree **p_oTargetTree = new clTree*[10];
    float *p_fExpected = new float[10];
    float fDiam;
    int iSpecies, i;


    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile(WriteNCIDoubleLocalDiffClimateGrowthXMLFile1());
    p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject(
        "treepopulation");

    //Create our trees
    i = 0;
    fDiam = 11;
    iSpecies = 1;
    p_oTargetTree[i] = p_oPop->CreateTree(10, 10, iSpecies,
        clTreePopulation::adult, fDiam);

    i++;
    fDiam = 15;
    iSpecies = 2;
    p_oTargetTree[i] = p_oPop->CreateTree(53, 52, iSpecies,
        clTreePopulation::adult, fDiam);

    i++;
    fDiam = 25;
    iSpecies = 3;
    p_oTargetTree[i] = p_oPop->CreateTree(59, 50, iSpecies,
        clTreePopulation::adult, fDiam);

    i++;
    fDiam = 4;
    iSpecies = 1;
    p_oTargetTree[i] = p_oPop->CreateTree(52, 52, iSpecies,
        clTreePopulation::sapling, fDiam);

    i++;
    fDiam = 4;
    iSpecies = 2;
    p_oTargetTree[i] = p_oPop->CreateTree(53, 53, iSpecies,
        clTreePopulation::sapling, fDiam);

    i++;
    fDiam = 11;
    iSpecies = 4;
    p_oTargetTree[i] = p_oPop->CreateTree(10, 10, iSpecies,
        clTreePopulation::adult, fDiam);

    i++;
    fDiam = 15;
    iSpecies = 5;
    p_oTargetTree[i] = p_oPop->CreateTree(53, 52, iSpecies,
        clTreePopulation::adult, fDiam);

    i++;
    fDiam = 25;
    iSpecies = 6;
    p_oTargetTree[i] = p_oPop->CreateTree(59, 50, iSpecies,
        clTreePopulation::adult, fDiam);

    i++;
    fDiam = 4;
    iSpecies = 4;
    p_oTargetTree[i] = p_oPop->CreateTree(52, 52, iSpecies,
        clTreePopulation::sapling, fDiam);

    i++;
    fDiam = 4;
    iSpecies = 5;
    p_oTargetTree[i] = p_oPop->CreateTree(53, 53, iSpecies,
        clTreePopulation::sapling, fDiam);

    //-----------------------------------------------------------------------//
    // Timestep 1
    //-----------------------------------------------------------------------//
    p_oSimManager->RunSim(1);

    //----- Check diameter --------------------------------------------------//
    p_fExpected[0] = 11.72260405;
    p_fExpected[1] = 15.12936966;
    p_fExpected[2] = 25.71402819;
    p_fExpected[3] = 4.722604045;
    p_fExpected[4] = 4.129369664;
    p_fExpected[5] = 11.3201567;
    p_fExpected[6] = 15.05278892;
    p_fExpected[7] = 25.85700571;
    p_fExpected[8] = 4.320156696;
    p_fExpected[9] = 4.052788917;

    for (i = 0; i < 10; i++) {
      p_oTargetTree[i]->GetValue(p_oPop->GetDbhCode(p_oTargetTree[i]->GetSpecies(),
          p_oTargetTree[i]->GetType()), &fDiam);
      EXPECT_LT(fabs(fDiam - p_fExpected[i])/fDiam, 0.001);
    }

    //-----------------------------------------------------------------------//
    // Timestep 2
    //-----------------------------------------------------------------------//
    p_oSimManager->RunSim(1);

    //----- Check diameter --------------------------------------------------//
    p_fExpected[0] = 12.44377368;
    p_fExpected[1] = 15.26303351;
    p_fExpected[2] = 26.4190465;
    p_fExpected[3] = 5.443773677;
    p_fExpected[4] = 4.263033512;
    p_fExpected[5] = 11.64056361;
    p_fExpected[6] = 15.10576033;
    p_fExpected[7] = 26.53350983;
    p_fExpected[8] = 4.640563606;
    p_fExpected[9] = 4.10576033;

    for (i = 0; i < 10; i++) {
      p_oTargetTree[i]->GetValue(p_oPop->GetDbhCode(p_oTargetTree[i]->GetSpecies(),
          p_oTargetTree[i]->GetType()), &fDiam);
      EXPECT_LT(fabs(fDiam - p_fExpected[i])/fDiam, 0.001);
    }

    //-----------------------------------------------------------------------//
    // Timestep 3
    //-----------------------------------------------------------------------//
    p_oSimManager->RunSim(1);

    //----- Check diameter --------------------------------------------------//
    p_fExpected[0] = 13.13976855;
    p_fExpected[1] = 15.3919;
    p_fExpected[2] = 27.15280655;
    p_fExpected[3] = 6.139768547;
    p_fExpected[4] = 4.391900002;
    p_fExpected[5] = 11.96448199;
    p_fExpected[6] = 15.15521516;
    p_fExpected[7] = 27.21475353;
    p_fExpected[8] = 4.964481992;
    p_fExpected[9] = 4.15521516;

    for (i = 0; i < 10; i++) {
      p_oTargetTree[i]->GetValue(p_oPop->GetDbhCode(p_oTargetTree[i]->GetSpecies(),
          p_oTargetTree[i]->GetType()), &fDiam);
      EXPECT_LT(fabs(fDiam - p_fExpected[i])/fDiam, 0.001);
    }

    //-----------------------------------------------------------------------//
    // Timestep 4
    //-----------------------------------------------------------------------//
    p_oSimManager->RunSim(1);

    //----- Check diameter --------------------------------------------------//
    p_fExpected[0] = 13.8424923;
    p_fExpected[1] = 15.53307851;
    p_fExpected[2] = 27.85332475;
    p_fExpected[3] = 6.842492301;
    p_fExpected[4] = 4.533078512;
    p_fExpected[5] = 12.29356797;
    p_fExpected[6] = 15.210619;
    p_fExpected[7] = 27.93234663;
    p_fExpected[8] = 5.293567967;
    p_fExpected[9] = 4.210618995;

    for (i = 0; i < 10; i++) {
      p_oTargetTree[i]->GetValue(p_oPop->GetDbhCode(p_oTargetTree[i]->GetSpecies(),
          p_oTargetTree[i]->GetType()), &fDiam);
      EXPECT_LT(fabs(fDiam - p_fExpected[i])/fDiam, 0.001);
    }

    delete[] p_oTargetTree;
    delete[] p_fExpected;
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestRun2()
////////////////////////////////////////////////////////////////////////////
TEST(NCIDoubleLocalDiffClimateGrowth, TestRun2) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTreeSearch *p_oAllTrees;
    clTree *p_oTree;
    float *p_fExpected = new float[10];
    float fDiam, fX, fY,
        fTarget1X = 10, fTarget1Y = 10, //coords of target 1 trees
        fTarget2X = 20, fTarget2Y = 20, //coords of target 2 trees
        fTarget3X = 30, fTarget3Y = 30, //coords of target 3 trees
        fTarget4X = 50, fTarget4Y = 50, //coords of target 4 trees
        fTarget5X = 53, fTarget5Y = 52, //coords of target 5 trees
        fTarget6X = 59, fTarget6Y = 50, //coords of target 6 trees
        fTarget7X = 50, fTarget7Y = 59, //coords of target 7 trees
        fTarget8X = 55, fTarget8Y = 55, //coords of target 8 trees
        fTarget9X = 60, fTarget9Y = 60, //coords of target 9 trees
        fTarget10X = 65, fTarget10Y = 65; //coords of target 10 trees
    int iSpecies, i, iNumTargets = 10;
    int *p_iCount = new int[iNumTargets];


    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile(WriteNCIDoubleLocalDiffClimateGrowthXMLFile2());
    p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject("treepopulation");

    //Create our trees
    i = 0;
    fDiam = 11;
    iSpecies = 1;
    for (i = 0; i < 1000; i++) {
      p_oPop->CreateTree(fTarget1X, fTarget1Y, iSpecies,
          clTreePopulation::adult, fDiam);
    }

    i++;
    fDiam = 15;
    iSpecies = 2;
    for (i = 0; i < 1000; i++) {
      p_oPop->CreateTree(fTarget2X, fTarget2Y, iSpecies,
        clTreePopulation::adult, fDiam);
    }

    i++;
    fDiam = 25;
    iSpecies = 3;
    for (i = 0; i < 1000; i++) {
      p_oPop->CreateTree(fTarget3X, fTarget3Y, iSpecies,
        clTreePopulation::adult, fDiam);
    }

    i++;
    fDiam = 4;
    iSpecies = 1;
    for (i = 0; i < 1000; i++) {
      p_oPop->CreateTree(fTarget4X, fTarget4Y, iSpecies,
        clTreePopulation::sapling, fDiam);
    }

    i++;
    fDiam = 4;
    iSpecies = 2;
    for (i = 0; i < 1000; i++) {
      p_oPop->CreateTree(fTarget5X, fTarget5Y, iSpecies,
        clTreePopulation::sapling, fDiam);
    }

    i++;
    fDiam = 11;
    iSpecies = 4;
    for (i = 0; i < 1000; i++) {
      p_oPop->CreateTree(fTarget6X, fTarget6Y, iSpecies,
        clTreePopulation::adult, fDiam);
    }

    i++;
    fDiam = 15;
    iSpecies = 5;
    for (i = 0; i < 1000; i++) {
      p_oPop->CreateTree(fTarget7X, fTarget7Y, iSpecies,
        clTreePopulation::adult, fDiam);
    }

    i++;
    fDiam = 25;
    iSpecies = 6;
    for (i = 0; i < 1000; i++) {
      p_oPop->CreateTree(fTarget8X, fTarget8Y, iSpecies,
        clTreePopulation::adult, fDiam);
    }

    i++;
    fDiam = 4;
    iSpecies = 4;
    for (i = 0; i < 1000; i++) {
      p_oPop->CreateTree(fTarget9X, fTarget9Y, iSpecies,
        clTreePopulation::sapling, fDiam);
    }

    i++;
    fDiam = 4;
    iSpecies = 5;
    for (i = 0; i < 1000; i++) {
      p_oPop->CreateTree(fTarget10X, fTarget10Y, iSpecies,
        clTreePopulation::sapling, fDiam);
    }

    //-----------------------------------------------------------------------//
    // Timestep 1
    //-----------------------------------------------------------------------//
    p_oSimManager->RunSim(1);

    //Count the target trees that are left
    for (i = 0; i < iNumTargets; i++) {
      p_iCount[i] = 0;
    }

    p_oAllTrees = p_oPop->Find("all");

    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      //Get the X and Y
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
      p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);

      //Find out if it's a target tree
      if (fabs(fX - fTarget1X) < 0.001 && fabs(fY - fTarget1Y) < 0.001) {
        p_iCount[0]++;
      } else if (fabs(fX - fTarget2X) < 0.001 && fabs(fY - fTarget2Y) < 0.001) {
        p_iCount[1]++;
      } else if (fabs(fX - fTarget3X) < 0.001 && fabs(fY - fTarget3Y) < 0.001) {
        p_iCount[2]++;
      } else if (fabs(fX - fTarget4X) < 0.001 && fabs(fY - fTarget4Y) < 0.001) {
        p_iCount[3]++;
      } else if (fabs(fX - fTarget5X) < 0.001 && fabs(fY - fTarget5Y) < 0.001) {
        p_iCount[4]++;
      } else if (fabs(fX - fTarget6X) < 0.001 && fabs(fY - fTarget6Y) < 0.001) {
        p_iCount[5]++;
      } else if (fabs(fX - fTarget7X) < 0.001 && fabs(fY - fTarget7Y) < 0.001) {
        p_iCount[6]++;
      } else if (fabs(fX - fTarget8X) < 0.001 && fabs(fY - fTarget8Y) < 0.001) {
        p_iCount[7]++;
      } else if (fabs(fX - fTarget9X) < 0.001 && fabs(fY - fTarget9Y) < 0.001) {
        p_iCount[8]++;
      } else if (fabs(fX - fTarget10X) < 0.001 && fabs(fY - fTarget10Y) < 0.001) {
        p_iCount[9]++;
      }

      p_oTree = p_oAllTrees->NextTree();
    }

    //----- Check counts ----------------------------------------------------//
    p_fExpected[0] = 708.7307967;
    p_fExpected[1] = 319.6337509;
    p_fExpected[2] = 184.6398717;
    p_fExpected[3] = 708.7307967;
    p_fExpected[4] = 319.6337509;
    p_fExpected[5] = 320.3777611;
    p_fExpected[6] = 890.3825862;
    p_fExpected[7] = 774.4416772;
    p_fExpected[8] = 320.3777611;
    p_fExpected[9] = 890.3825862;

    for (i = 0; i < iNumTargets; i++) {
      EXPECT_LT(fabs(p_iCount[i] - p_fExpected[i])/p_iCount[i], 0.1);
    }


    //-----------------------------------------------------------------------//
    // Timestep 2
    //-----------------------------------------------------------------------//
    p_oSimManager->RunSim(1);

    //----- Check diameter --------------------------------------------------//
    p_fExpected[0] = 12.44377368;
    p_fExpected[1] = 15.26303351;
    p_fExpected[2] = 26.4190465;
    p_fExpected[3] = 5.443773677;
    p_fExpected[4] = 4.263033512;
    p_fExpected[5] = 11.64056361;
    p_fExpected[6] = 15.10576033;
    p_fExpected[7] = 26.53350983;
    p_fExpected[8] = 4.640563606;
    p_fExpected[9] = 4.10576033;



    delete[] p_iCount;
    delete[] p_fExpected;
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIDoubleLocalDiffClimateGrowthXMLFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIDoubleLocalDiffClimateGrowthXMLFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteNCIDoubleLocalCommon(oOut);
  int i;

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>ClimateImporter</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "</behavior>"

      // First NCI growth behavior: precip only
      << "<behavior>"
      << "<behaviorName>NCIMasterGrowth</behaviorName>"
      << "<version>3</version>"
      << "<listPosition>2</listPosition>";
  for (i = 2; i < 5; i++) {
    oOut  << "<applyTo species=\"Species_" << i << "\" type=\"Sapling\"/>";
    oOut  << "<applyTo species=\"Species_" << i << "\" type=\"Adult\"/>";
  }
  oOut  << "</behavior>"
      // Second NCI growth behavior: temp only
      << "<behavior>"
      << "<behaviorName>NCIMasterGrowth</behaviorName>"
      << "<version>3</version>"
      << "<listPosition>3</listPosition>";
  for (i = 5; i < 8; i++) {
    oOut  << "<applyTo species=\"Species_" << i << "\" type=\"Sapling\"/>";
    oOut  << "<applyTo species=\"Species_" << i << "\" type=\"Adult\"/>";
  }
  oOut  << "</behavior>"
      << "</behaviorList>"
      << "<ClimateImporter1>"
      << "<sc_ciAWS>60.9</sc_ciAWS>"
      << "<sc_ciCalendarMean>0</sc_ciCalendarMean>"
      << "<sc_ciLTM>5</sc_ciLTM>"

      << "<sc_ciMonthlyTempJan>"
      << "<sc_cimtjanVal ts=\"-5\">-3.86</sc_cimtjanVal>"
      << "<sc_cimtjanVal ts=\"-4\">0.56</sc_cimtjanVal>"
      << "<sc_cimtjanVal ts=\"-3\">-1.51</sc_cimtjanVal>"
      << "<sc_cimtjanVal ts=\"-2\">5.03</sc_cimtjanVal>"
      << "<sc_cimtjanVal ts=\"-1\">-5.5</sc_cimtjanVal>"
      << "<sc_cimtjanVal ts=\"1\">-2.57</sc_cimtjanVal>"
      << "<sc_cimtjanVal ts=\"2\">-3.46</sc_cimtjanVal>"
      << "<sc_cimtjanVal ts=\"3\">-6.93</sc_cimtjanVal>"
      << "<sc_cimtjanVal ts=\"4\">-7.76</sc_cimtjanVal>"
      << "<sc_cimtjanVal ts=\"5\">-0.72</sc_cimtjanVal>"
      << "<sc_cimtjanVal ts=\"6\">1.3</sc_cimtjanVal>"
      << "</sc_ciMonthlyTempJan>"

      << "<sc_ciMonthlyTempFeb>"
      << "<sc_cimtfebVal ts=\"-5\">-1.56</sc_cimtfebVal>"
      << "<sc_cimtfebVal ts=\"-4\">-0.03</sc_cimtfebVal>"
      << "<sc_cimtfebVal ts=\"-3\">2.16</sc_cimtfebVal>"
      << "<sc_cimtfebVal ts=\"-2\">4.5</sc_cimtfebVal>"
      << "<sc_cimtfebVal ts=\"-1\">-0.6</sc_cimtfebVal>"
      << "<sc_cimtfebVal ts=\"1\">2.75</sc_cimtfebVal>"
      << "<sc_cimtfebVal ts=\"2\">-8.57</sc_cimtfebVal>"
      << "<sc_cimtfebVal ts=\"3\">1.98</sc_cimtfebVal>"
      << "<sc_cimtfebVal ts=\"4\">-7.5</sc_cimtfebVal>"
      << "<sc_cimtfebVal ts=\"5\">-2.44</sc_cimtfebVal>"
      << "<sc_cimtfebVal ts=\"6\">-9.36</sc_cimtfebVal>"
      << "</sc_ciMonthlyTempFeb>"

      << "<sc_ciMonthlyTempMar>"
      << "<sc_cimtmarVal ts=\"-5\">1.93</sc_cimtmarVal>"
      << "<sc_cimtmarVal ts=\"-4\">1.57</sc_cimtmarVal>"
      << "<sc_cimtmarVal ts=\"-3\">7.49</sc_cimtmarVal>"
      << "<sc_cimtmarVal ts=\"-2\">6.95</sc_cimtmarVal>"
      << "<sc_cimtmarVal ts=\"-1\">1.54</sc_cimtmarVal>"
      << "<sc_cimtmarVal ts=\"1\">2.94</sc_cimtmarVal>"
      << "<sc_cimtmarVal ts=\"2\">0.28</sc_cimtmarVal>"
      << "<sc_cimtmarVal ts=\"3\">0.3</sc_cimtmarVal>"
      << "<sc_cimtmarVal ts=\"4\">-0.78</sc_cimtmarVal>"
      << "<sc_cimtmarVal ts=\"5\">4.85</sc_cimtmarVal>"
      << "<sc_cimtmarVal ts=\"6\">3.78</sc_cimtmarVal>"
      << "</sc_ciMonthlyTempMar>"

      << "<sc_ciMonthlyTempApr>"
      << "<sc_cimtaprVal ts=\"-5\">5.53</sc_cimtaprVal>"
      << "<sc_cimtaprVal ts=\"-4\">11.17</sc_cimtaprVal>"
      << "<sc_cimtaprVal ts=\"-3\">6.21</sc_cimtaprVal>"
      << "<sc_cimtaprVal ts=\"-2\">11.68</sc_cimtaprVal>"
      << "<sc_cimtaprVal ts=\"-1\">8.66</sc_cimtaprVal>"
      << "<sc_cimtaprVal ts=\"1\">2.17</sc_cimtaprVal>"
      << "<sc_cimtaprVal ts=\"2\">5.9</sc_cimtaprVal>"
      << "<sc_cimtaprVal ts=\"3\">7.17</sc_cimtaprVal>"
      << "<sc_cimtaprVal ts=\"4\">8.67</sc_cimtaprVal>"
      << "<sc_cimtaprVal ts=\"5\">5.61</sc_cimtaprVal>"
      << "<sc_cimtaprVal ts=\"6\">4.56</sc_cimtaprVal>"
      << "</sc_ciMonthlyTempApr>"

      << "<sc_ciMonthlyTempMay>"
      << "<sc_cimtmayVal ts=\"-5\">10.59</sc_cimtmayVal>"
      << "<sc_cimtmayVal ts=\"-4\">7.49</sc_cimtmayVal>"
      << "<sc_cimtmayVal ts=\"-3\">7.66</sc_cimtmayVal>"
      << "<sc_cimtmayVal ts=\"-2\">12.52</sc_cimtmayVal>"
      << "<sc_cimtmayVal ts=\"-1\">10.68</sc_cimtmayVal>"
      << "<sc_cimtmayVal ts=\"1\">7.25</sc_cimtmayVal>"
      << "<sc_cimtmayVal ts=\"2\">7.6</sc_cimtmayVal>"
      << "<sc_cimtmayVal ts=\"3\">9.46</sc_cimtmayVal>"
      << "<sc_cimtmayVal ts=\"4\">11.26</sc_cimtmayVal>"
      << "<sc_cimtmayVal ts=\"5\">7.6</sc_cimtmayVal>"
      << "<sc_cimtmayVal ts=\"6\">6.9</sc_cimtmayVal>"
      << "</sc_ciMonthlyTempMay>"

      << "<sc_ciMonthlyTempJun>"
      << "<sc_cimtjunVal ts=\"-5\">14.99</sc_cimtjunVal>"
      << "<sc_cimtjunVal ts=\"-4\">7.67</sc_cimtjunVal>"
      << "<sc_cimtjunVal ts=\"-3\">10.1</sc_cimtjunVal>"
      << "<sc_cimtjunVal ts=\"-2\">14.33</sc_cimtjunVal>"
      << "<sc_cimtjunVal ts=\"-1\">16.65</sc_cimtjunVal>"
      << "<sc_cimtjunVal ts=\"1\">11.05</sc_cimtjunVal>"
      << "<sc_cimtjunVal ts=\"2\">17.16</sc_cimtjunVal>"
      << "<sc_cimtjunVal ts=\"3\">11.06</sc_cimtjunVal>"
      << "<sc_cimtjunVal ts=\"4\">17.72</sc_cimtjunVal>"
      << "<sc_cimtjunVal ts=\"5\">14.05</sc_cimtjunVal>"
      << "<sc_cimtjunVal ts=\"6\">13.52</sc_cimtjunVal>"
      << "</sc_ciMonthlyTempJun>"

      << "<sc_ciMonthlyTempJul>"
      << "<sc_cimtjulVal ts=\"-5\">13.42</sc_cimtjulVal>"
      << "<sc_cimtjulVal ts=\"-4\">15.48</sc_cimtjulVal>"
      << "<sc_cimtjulVal ts=\"-3\">15.24</sc_cimtjulVal>"
      << "<sc_cimtjulVal ts=\"-2\">17.87</sc_cimtjulVal>"
      << "<sc_cimtjulVal ts=\"-1\">14.13</sc_cimtjulVal>"
      << "<sc_cimtjulVal ts=\"1\">16.82</sc_cimtjulVal>"
      << "<sc_cimtjulVal ts=\"2\">22</sc_cimtjulVal>"
      << "<sc_cimtjulVal ts=\"3\">18.34</sc_cimtjulVal>"
      << "<sc_cimtjulVal ts=\"4\">20.99</sc_cimtjulVal>"
      << "<sc_cimtjulVal ts=\"5\">15.46</sc_cimtjulVal>"
      << "<sc_cimtjulVal ts=\"6\">15.74</sc_cimtjulVal>"
      << "</sc_ciMonthlyTempJul>"

      << "<sc_ciMonthlyTempAug>"
      << "<sc_cimtaugVal ts=\"-5\">7.55</sc_cimtaugVal>"
      << "<sc_cimtaugVal ts=\"-4\">12.01</sc_cimtaugVal>"
      << "<sc_cimtaugVal ts=\"-3\">15.55</sc_cimtaugVal>"
      << "<sc_cimtaugVal ts=\"-2\">16.23</sc_cimtaugVal>"
      << "<sc_cimtaugVal ts=\"-1\">19.9</sc_cimtaugVal>"
      << "<sc_cimtaugVal ts=\"1\">18.32</sc_cimtaugVal>"
      << "<sc_cimtaugVal ts=\"2\">15.97</sc_cimtaugVal>"
      << "<sc_cimtaugVal ts=\"3\">17.54</sc_cimtaugVal>"
      << "<sc_cimtaugVal ts=\"4\">17.46</sc_cimtaugVal>"
      << "<sc_cimtaugVal ts=\"5\">16.69</sc_cimtaugVal>"
      << "<sc_cimtaugVal ts=\"6\">17.48</sc_cimtaugVal>"
      << "</sc_ciMonthlyTempAug>"

      << "<sc_ciMonthlyTempSep>"
      << "<sc_cimtsepVal ts=\"-5\">13.72</sc_cimtsepVal>"
      << "<sc_cimtsepVal ts=\"-4\">17.95</sc_cimtsepVal>"
      << "<sc_cimtsepVal ts=\"-3\">11.19</sc_cimtsepVal>"
      << "<sc_cimtsepVal ts=\"-2\">16.39</sc_cimtsepVal>"
      << "<sc_cimtsepVal ts=\"-1\">5.87</sc_cimtsepVal>"
      << "<sc_cimtsepVal ts=\"1\">22.73</sc_cimtsepVal>"
      << "<sc_cimtsepVal ts=\"2\">20.94</sc_cimtsepVal>"
      << "<sc_cimtsepVal ts=\"3\">15.94</sc_cimtsepVal>"
      << "<sc_cimtsepVal ts=\"4\">18.87</sc_cimtsepVal>"
      << "<sc_cimtsepVal ts=\"5\">22.85</sc_cimtsepVal>"
      << "<sc_cimtsepVal ts=\"6\">19.53</sc_cimtsepVal>"
      << "</sc_ciMonthlyTempSep>"

      << "<sc_ciMonthlyTempOct>"
      << "<sc_cimtoctVal ts=\"-5\">2.83</sc_cimtoctVal>"
      << "<sc_cimtoctVal ts=\"-4\">7.09</sc_cimtoctVal>"
      << "<sc_cimtoctVal ts=\"-3\">10.7</sc_cimtoctVal>"
      << "<sc_cimtoctVal ts=\"-2\">2.84</sc_cimtoctVal>"
      << "<sc_cimtoctVal ts=\"-1\">4.3</sc_cimtoctVal>"
      << "<sc_cimtoctVal ts=\"1\">7.92</sc_cimtoctVal>"
      << "<sc_cimtoctVal ts=\"2\">8.18</sc_cimtoctVal>"
      << "<sc_cimtoctVal ts=\"3\">8.43</sc_cimtoctVal>"
      << "<sc_cimtoctVal ts=\"4\">8.68</sc_cimtoctVal>"
      << "<sc_cimtoctVal ts=\"5\">8.94</sc_cimtoctVal>"
      << "<sc_cimtoctVal ts=\"6\">9.19</sc_cimtoctVal>"
      << "</sc_ciMonthlyTempOct>"

      << "<sc_ciMonthlyTempNov>"
      << "<sc_cimtnovVal ts=\"-5\">-0.58</sc_cimtnovVal>"
      << "<sc_cimtnovVal ts=\"-4\">8.71</sc_cimtnovVal>"
      << "<sc_cimtnovVal ts=\"-3\">7.51</sc_cimtnovVal>"
      << "<sc_cimtnovVal ts=\"-2\">-0.57</sc_cimtnovVal>"
      << "<sc_cimtnovVal ts=\"-1\">1.98</sc_cimtnovVal>"
      << "<sc_cimtnovVal ts=\"1\">2.48</sc_cimtnovVal>"
      << "<sc_cimtnovVal ts=\"2\">2.56</sc_cimtnovVal>"
      << "<sc_cimtnovVal ts=\"3\">2.64</sc_cimtnovVal>"
      << "<sc_cimtnovVal ts=\"4\">2.72</sc_cimtnovVal>"
      << "<sc_cimtnovVal ts=\"5\">2.8</sc_cimtnovVal>"
      << "<sc_cimtnovVal ts=\"6\">2.88</sc_cimtnovVal>"
      << "</sc_ciMonthlyTempNov>"

      << "<sc_ciMonthlyTempDec>"
      << "<sc_cimtdecVal ts=\"-5\">2.34</sc_cimtdecVal>"
      << "<sc_cimtdecVal ts=\"-4\">-3.33</sc_cimtdecVal>"
      << "<sc_cimtdecVal ts=\"-3\">-0.66</sc_cimtdecVal>"
      << "<sc_cimtdecVal ts=\"-2\">3.22</sc_cimtdecVal>"
      << "<sc_cimtdecVal ts=\"-1\">0.6</sc_cimtdecVal>"
      << "<sc_cimtdecVal ts=\"1\">-9.6</sc_cimtdecVal>"
      << "<sc_cimtdecVal ts=\"2\">-6.94</sc_cimtdecVal>"
      << "<sc_cimtdecVal ts=\"3\">-6.51</sc_cimtdecVal>"
      << "<sc_cimtdecVal ts=\"4\">-1.59</sc_cimtdecVal>"
      << "<sc_cimtdecVal ts=\"5\">0.19</sc_cimtdecVal>"
      << "<sc_cimtdecVal ts=\"6\">2.49</sc_cimtdecVal>"
      << "</sc_ciMonthlyTempDec>"

      << "<sc_ciMonthlyPptJan>"
      << "<sc_cimpjanVal ts=\"-5\">156.75</sc_cimpjanVal>"
      << "<sc_cimpjanVal ts=\"-4\">200.8</sc_cimpjanVal>"
      << "<sc_cimpjanVal ts=\"-3\">76.15</sc_cimpjanVal>"
      << "<sc_cimpjanVal ts=\"-2\">144.61</sc_cimpjanVal>"
      << "<sc_cimpjanVal ts=\"-1\">81.05</sc_cimpjanVal>"
      << "<sc_cimpjanVal ts=\"1\">161.48</sc_cimpjanVal>"
      << "<sc_cimpjanVal ts=\"2\">152.09</sc_cimpjanVal>"
      << "<sc_cimpjanVal ts=\"3\">152.5</sc_cimpjanVal>"
      << "<sc_cimpjanVal ts=\"4\">152.71</sc_cimpjanVal>"
      << "<sc_cimpjanVal ts=\"5\">78.44</sc_cimpjanVal>"
      << "<sc_cimpjanVal ts=\"6\">123.19</sc_cimpjanVal>"
      << "</sc_ciMonthlyPptJan>"

      << "<sc_ciMonthlyPptFeb>"
      << "<sc_cimpfebVal ts=\"-5\">187.85</sc_cimpfebVal>"
      << "<sc_cimpfebVal ts=\"-4\">124.88</sc_cimpfebVal>"
      << "<sc_cimpfebVal ts=\"-3\">63.49</sc_cimpfebVal>"
      << "<sc_cimpfebVal ts=\"-2\">192.17</sc_cimpfebVal>"
      << "<sc_cimpfebVal ts=\"-1\">182.35</sc_cimpfebVal>"
      << "<sc_cimpfebVal ts=\"1\">199.32</sc_cimpfebVal>"
      << "<sc_cimpfebVal ts=\"2\">192.94</sc_cimpfebVal>"
      << "<sc_cimpfebVal ts=\"3\">188.1</sc_cimpfebVal>"
      << "<sc_cimpfebVal ts=\"4\">153.95</sc_cimpfebVal>"
      << "<sc_cimpfebVal ts=\"5\">89.79</sc_cimpfebVal>"
      << "<sc_cimpfebVal ts=\"6\">189.67</sc_cimpfebVal>"
      << "</sc_ciMonthlyPptFeb>"

      << "<sc_ciMonthlyPptMar>"
      << "<sc_cimpmarVal ts=\"-5\">208.64</sc_cimpmarVal>"
      << "<sc_cimpmarVal ts=\"-4\">233.06</sc_cimpmarVal>"
      << "<sc_cimpmarVal ts=\"-3\">246.05</sc_cimpmarVal>"
      << "<sc_cimpmarVal ts=\"-2\">183.98</sc_cimpmarVal>"
      << "<sc_cimpmarVal ts=\"-1\">144.42</sc_cimpmarVal>"
      << "<sc_cimpmarVal ts=\"1\">169.99</sc_cimpmarVal>"
      << "<sc_cimpmarVal ts=\"2\">105.49</sc_cimpmarVal>"
      << "<sc_cimpmarVal ts=\"3\">141.34</sc_cimpmarVal>"
      << "<sc_cimpmarVal ts=\"4\">84.71</sc_cimpmarVal>"
      << "<sc_cimpmarVal ts=\"5\">188.92</sc_cimpmarVal>"
      << "<sc_cimpmarVal ts=\"6\">93.47</sc_cimpmarVal>"
      << "</sc_ciMonthlyPptMar>"

      << "<sc_ciMonthlyPptApr>"
      << "<sc_cimpaprVal ts=\"-5\">61.72</sc_cimpaprVal>"
      << "<sc_cimpaprVal ts=\"-4\">197.01</sc_cimpaprVal>"
      << "<sc_cimpaprVal ts=\"-3\">146.71</sc_cimpaprVal>"
      << "<sc_cimpaprVal ts=\"-2\">173.62</sc_cimpaprVal>"
      << "<sc_cimpaprVal ts=\"-1\">50.19</sc_cimpaprVal>"
      << "<sc_cimpaprVal ts=\"1\">82.02</sc_cimpaprVal>"
      << "<sc_cimpaprVal ts=\"2\">77.49</sc_cimpaprVal>"
      << "<sc_cimpaprVal ts=\"3\">186.32</sc_cimpaprVal>"
      << "<sc_cimpaprVal ts=\"4\">174.4</sc_cimpaprVal>"
      << "<sc_cimpaprVal ts=\"5\">161.25</sc_cimpaprVal>"
      << "<sc_cimpaprVal ts=\"6\">99.76</sc_cimpaprVal>"
      << "</sc_ciMonthlyPptApr>"

      << "<sc_ciMonthlyPptMay>"
      << "<sc_cimpmayVal ts=\"-5\">98.88</sc_cimpmayVal>"
      << "<sc_cimpmayVal ts=\"-4\">221.62</sc_cimpmayVal>"
      << "<sc_cimpmayVal ts=\"-3\">245.51</sc_cimpmayVal>"
      << "<sc_cimpmayVal ts=\"-2\">227.17</sc_cimpmayVal>"
      << "<sc_cimpmayVal ts=\"-1\">157.19</sc_cimpmayVal>"
      << "<sc_cimpmayVal ts=\"1\">132.54</sc_cimpmayVal>"
      << "<sc_cimpmayVal ts=\"2\">121.74</sc_cimpmayVal>"
      << "<sc_cimpmayVal ts=\"3\">178.18</sc_cimpmayVal>"
      << "<sc_cimpmayVal ts=\"4\">102.86</sc_cimpmayVal>"
      << "<sc_cimpmayVal ts=\"5\">102.84</sc_cimpmayVal>"
      << "<sc_cimpmayVal ts=\"6\">172.41</sc_cimpmayVal>"
      << "</sc_ciMonthlyPptMay>"

      << "<sc_ciMonthlyPptJun>"
      << "<sc_cimpjunVal ts=\"-5\">144.55</sc_cimpjunVal>"
      << "<sc_cimpjunVal ts=\"-4\">142.87</sc_cimpjunVal>"
      << "<sc_cimpjunVal ts=\"-3\">184.78</sc_cimpjunVal>"
      << "<sc_cimpjunVal ts=\"-2\">249.3</sc_cimpjunVal>"
      << "<sc_cimpjunVal ts=\"-1\">201.05</sc_cimpjunVal>"
      << "<sc_cimpjunVal ts=\"1\">157.67</sc_cimpjunVal>"
      << "<sc_cimpjunVal ts=\"2\">133.89</sc_cimpjunVal>"
      << "<sc_cimpjunVal ts=\"3\">147.29</sc_cimpjunVal>"
      << "<sc_cimpjunVal ts=\"4\">123.74</sc_cimpjunVal>"
      << "<sc_cimpjunVal ts=\"5\">126.66</sc_cimpjunVal>"
      << "<sc_cimpjunVal ts=\"6\">134.35</sc_cimpjunVal>"
      << "</sc_ciMonthlyPptJun>"

      << "<sc_ciMonthlyPptJul>"
      << "<sc_cimpjulVal ts=\"-5\">96.74</sc_cimpjulVal>"
      << "<sc_cimpjulVal ts=\"-4\">198.29</sc_cimpjulVal>"
      << "<sc_cimpjulVal ts=\"-3\">56.77</sc_cimpjulVal>"
      << "<sc_cimpjulVal ts=\"-2\">55.16</sc_cimpjulVal>"
      << "<sc_cimpjulVal ts=\"-1\">174.6</sc_cimpjulVal>"
      << "<sc_cimpjulVal ts=\"1\">97.63</sc_cimpjulVal>"
      << "<sc_cimpjulVal ts=\"2\">141.94</sc_cimpjulVal>"
      << "<sc_cimpjulVal ts=\"3\">173.88</sc_cimpjulVal>"
      << "<sc_cimpjulVal ts=\"4\">166.53</sc_cimpjulVal>"
      << "<sc_cimpjulVal ts=\"5\">140.41</sc_cimpjulVal>"
      << "<sc_cimpjulVal ts=\"6\">128.89</sc_cimpjulVal>"
      << "</sc_ciMonthlyPptJul>"

      << "<sc_ciMonthlyPptAug>"
      << "<sc_cimpaugVal ts=\"-5\">250.84</sc_cimpaugVal>"
      << "<sc_cimpaugVal ts=\"-4\">145.97</sc_cimpaugVal>"
      << "<sc_cimpaugVal ts=\"-3\">104.14</sc_cimpaugVal>"
      << "<sc_cimpaugVal ts=\"-2\">99.69</sc_cimpaugVal>"
      << "<sc_cimpaugVal ts=\"-1\">59.28</sc_cimpaugVal>"
      << "<sc_cimpaugVal ts=\"1\">145.57</sc_cimpaugVal>"
      << "<sc_cimpaugVal ts=\"2\">156.69</sc_cimpaugVal>"
      << "<sc_cimpaugVal ts=\"3\">146.55</sc_cimpaugVal>"
      << "<sc_cimpaugVal ts=\"4\">167.73</sc_cimpaugVal>"
      << "<sc_cimpaugVal ts=\"5\">147.67</sc_cimpaugVal>"
      << "<sc_cimpaugVal ts=\"6\">119.52</sc_cimpaugVal>"
      << "</sc_ciMonthlyPptAug>"

      << "<sc_ciMonthlyPptSep>"
      << "<sc_cimpsepVal ts=\"-5\">154.02</sc_cimpsepVal>"
      << "<sc_cimpsepVal ts=\"-4\">124.84</sc_cimpsepVal>"
      << "<sc_cimpsepVal ts=\"-3\">142.08</sc_cimpsepVal>"
      << "<sc_cimpsepVal ts=\"-2\">207.51</sc_cimpsepVal>"
      << "<sc_cimpsepVal ts=\"-1\">87.88</sc_cimpsepVal>"
      << "<sc_cimpsepVal ts=\"1\">134.38</sc_cimpsepVal>"
      << "<sc_cimpsepVal ts=\"2\">89.78</sc_cimpsepVal>"
      << "<sc_cimpsepVal ts=\"3\">173.37</sc_cimpsepVal>"
      << "<sc_cimpsepVal ts=\"4\">146.16</sc_cimpsepVal>"
      << "<sc_cimpsepVal ts=\"5\">108.71</sc_cimpsepVal>"
      << "<sc_cimpsepVal ts=\"6\">90.68</sc_cimpsepVal>"
      << "</sc_ciMonthlyPptSep>"

      << "<sc_ciMonthlyPptOct>"
      << "<sc_cimpoctVal ts=\"-5\">129.54</sc_cimpoctVal>"
      << "<sc_cimpoctVal ts=\"-4\">72.4</sc_cimpoctVal>"
      << "<sc_cimpoctVal ts=\"-3\">162.74</sc_cimpoctVal>"
      << "<sc_cimpoctVal ts=\"-2\">51.89</sc_cimpoctVal>"
      << "<sc_cimpoctVal ts=\"-1\">98.17</sc_cimpoctVal>"
      << "<sc_cimpoctVal ts=\"1\">100.17</sc_cimpoctVal>"
      << "<sc_cimpoctVal ts=\"2\">178.11</sc_cimpoctVal>"
      << "<sc_cimpoctVal ts=\"3\">120.16</sc_cimpoctVal>"
      << "<sc_cimpoctVal ts=\"4\">198.43</sc_cimpoctVal>"
      << "<sc_cimpoctVal ts=\"5\">75.22</sc_cimpoctVal>"
      << "<sc_cimpoctVal ts=\"6\">198.3</sc_cimpoctVal>"
      << "</sc_ciMonthlyPptOct>"

      << "<sc_ciMonthlyPptNov>"
      << "<sc_cimpnovVal ts=\"-5\">186.31</sc_cimpnovVal>"
      << "<sc_cimpnovVal ts=\"-4\">74.2</sc_cimpnovVal>"
      << "<sc_cimpnovVal ts=\"-3\">68.19</sc_cimpnovVal>"
      << "<sc_cimpnovVal ts=\"-2\">197.74</sc_cimpnovVal>"
      << "<sc_cimpnovVal ts=\"-1\">222.2</sc_cimpnovVal>"
      << "<sc_cimpnovVal ts=\"1\">112.34</sc_cimpnovVal>"
      << "<sc_cimpnovVal ts=\"2\">191.22</sc_cimpnovVal>"
      << "<sc_cimpnovVal ts=\"3\">125.47</sc_cimpnovVal>"
      << "<sc_cimpnovVal ts=\"4\">79.8</sc_cimpnovVal>"
      << "<sc_cimpnovVal ts=\"5\">116.29</sc_cimpnovVal>"
      << "<sc_cimpnovVal ts=\"6\">146.75</sc_cimpnovVal>"
      << "</sc_ciMonthlyPptNov>"

      << "<sc_ciMonthlyPptDec>"
      << "<sc_cimpdecVal ts=\"-5\">168.86</sc_cimpdecVal>"
      << "<sc_cimpdecVal ts=\"-4\">153.39</sc_cimpdecVal>"
      << "<sc_cimpdecVal ts=\"-3\">80.31</sc_cimpdecVal>"
      << "<sc_cimpdecVal ts=\"-2\">203.43</sc_cimpdecVal>"
      << "<sc_cimpdecVal ts=\"-1\">50.59</sc_cimpdecVal>"
      << "<sc_cimpdecVal ts=\"1\">137.22</sc_cimpdecVal>"
      << "<sc_cimpdecVal ts=\"2\">101.29</sc_cimpdecVal>"
      << "<sc_cimpdecVal ts=\"3\">159.21</sc_cimpdecVal>"
      << "<sc_cimpdecVal ts=\"4\">171.75</sc_cimpdecVal>"
      << "<sc_cimpdecVal ts=\"5\">191.54</sc_cimpdecVal>"
      << "<sc_cimpdecVal ts=\"6\">131.83</sc_cimpdecVal>"
      << "</sc_ciMonthlyPptDec>"

      << "<sc_ciJanRad>7468.475</sc_ciJanRad>"
      << "<sc_ciFebRad>10353.32</sc_ciFebRad>"
      << "<sc_ciMarRad>17453.07</sc_ciMarRad>"
      << "<sc_ciAprRad>22721.85</sc_ciAprRad>"
      << "<sc_ciMayRad>27901.37</sc_ciMayRad>"
      << "<sc_ciJunRad>28677.54</sc_ciJunRad>"
      << "<sc_ciJulRad>28764.65</sc_ciJulRad>"
      << "<sc_ciAugRad>25075.4</sc_ciAugRad>"
      << "<sc_ciSepRad>19259.27</sc_ciSepRad>"
      << "<sc_ciOctRad>12609.6</sc_ciOctRad>"
      << "<sc_ciNovRad>7988.013</sc_ciNovRad>"
      << "<sc_ciDecRad>6307.151</sc_ciDecRad>"
      << "</ClimateImporter1>"

      << "<NCIMasterGrowth2>"
      << "<nciWhichShadingEffect>" << no_shading << "</nciWhichShadingEffect>"
      << "<nciWhichCrowdingEffect>" << no_crowding_effect << "</nciWhichCrowdingEffect>"
      << "<nciWhichNCITerm>" << no_nci_term << "</nciWhichNCITerm>"
      << "<nciWhichSizeEffect>" << no_size_effect << "</nciWhichSizeEffect>"
      << "<nciWhichDamageEffect>" << no_damage_effect << "</nciWhichDamageEffect>"
      << "<nciWhichPrecipitationEffect>" << double_local_diff_precip_effect << "</nciWhichPrecipitationEffect>"
      << "<nciWhichTemperatureEffect>" << no_temp_effect << "</nciWhichTemperatureEffect>"
      << "<nciWhichNitrogenEffect>" << no_nitrogen_effect << "</nciWhichNitrogenEffect>"
      << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
      << "<gr_stochGrowthMethod>" << deterministic_pdf << "</gr_stochGrowthMethod>"
      << "<gr_nciMaxPotentialGrowth>"
      << "<gr_nmpgVal species=\"Species_2\">1</gr_nmpgVal>"
      << "<gr_nmpgVal species=\"Species_3\">1</gr_nmpgVal>"
      << "<gr_nmpgVal species=\"Species_4\">1</gr_nmpgVal>"
      << "</gr_nciMaxPotentialGrowth>"
      << "<nciDoubLocPrecipEffCurrAA>"
      << "<ndlpecaaVal species=\"Species_2\">0.93</ndlpecaaVal>"
      << "<ndlpecaaVal species=\"Species_3\">1.8393E-05</ndlpecaaVal>"
      << "<ndlpecaaVal species=\"Species_4\">0.9788117</ndlpecaaVal>"
      << "</nciDoubLocPrecipEffCurrAA>"
      << "<nciDoubLocPrecipEffCurrABLo>"
      << "<ndlpecablVal species=\"Species_2\">0.9979457</ndlpecablVal>"
      << "<ndlpecablVal species=\"Species_3\">0.9739622</ndlpecablVal>"
      << "<ndlpecablVal species=\"Species_4\">0.9112952</ndlpecablVal>"
      << "</nciDoubLocPrecipEffCurrABLo>"
      << "<nciDoubLocPrecipEffCurrABHi>"
      << "<ndlpecabhVal species=\"Species_2\">0.9967062</ndlpecabhVal>"
      << "<ndlpecabhVal species=\"Species_3\">0.9278246</ndlpecabhVal>"
      << "<ndlpecabhVal species=\"Species_4\">0.943658</ndlpecabhVal>"
      << "</nciDoubLocPrecipEffCurrABHi>"
      << "<nciDoubLocPrecipEffCurrAC>"
      << "<ndlpecacVal species=\"Species_2\">1.11607</ndlpecacVal>"
      << "<ndlpecacVal species=\"Species_3\">-0.109959</ndlpecacVal>"
      << "<ndlpecacVal species=\"Species_4\">3</ndlpecacVal>"
      << "</nciDoubLocPrecipEffCurrAC>"
      << "<nciDoubLocPrecipEffCurrBLo>"
      << "<ndlpecblVal species=\"Species_2\">0.9057236</ndlpecblVal>"
      << "<ndlpecblVal species=\"Species_3\">0.9948863</ndlpecblVal>"
      << "<ndlpecblVal species=\"Species_4\">0.9001916</ndlpecblVal>"
      << "</nciDoubLocPrecipEffCurrBLo>"
      << "<nciDoubLocPrecipEffCurrBHi>"
      << "<ndlpecbhVal species=\"Species_2\">0.9136399</ndlpecbhVal>"
      << "<ndlpecbhVal species=\"Species_3\">0.9475929</ndlpecbhVal>"
      << "<ndlpecbhVal species=\"Species_4\">0.9843666</ndlpecbhVal>"
      << "</nciDoubLocPrecipEffCurrBHi>"
      << "<nciDoubLocPrecipEffCurrC>"
      << "<ndlpeccVal species=\"Species_2\">-1.892206</ndlpeccVal>"
      << "<ndlpeccVal species=\"Species_3\">0.5525589</ndlpeccVal>"
      << "<ndlpeccVal species=\"Species_4\">2.999962</ndlpeccVal>"
      << "</nciDoubLocPrecipEffCurrC>"
      << "<nciDoubLocPrecipEffPrevAA>"
      << "<ndlpepaaVal species=\"Species_2\">0.1245304</ndlpepaaVal>"
      << "<ndlpepaaVal species=\"Species_3\">0.5547286</ndlpepaaVal>"
      << "<ndlpepaaVal species=\"Species_4\">0.7225592</ndlpepaaVal>"
      << "</nciDoubLocPrecipEffPrevAA>"
      << "<nciDoubLocPrecipEffPrevABLo>"
      << "<ndlpepablVal species=\"Species_2\">0.9733152</ndlpepablVal>"
      << "<ndlpepablVal species=\"Species_3\">0.9752083</ndlpepablVal>"
      << "<ndlpepablVal species=\"Species_4\">0.9294581</ndlpepablVal>"
      << "</nciDoubLocPrecipEffPrevABLo>"
      << "<nciDoubLocPrecipEffPrevABHi>"
      << "<ndlpepabhVal species=\"Species_2\">0.9</ndlpepabhVal>"
      << "<ndlpepabhVal species=\"Species_3\">0.90253</ndlpepabhVal>"
      << "<ndlpepabhVal species=\"Species_4\">1</ndlpepabhVal>"
      << "</nciDoubLocPrecipEffPrevABHi>"
      << "<nciDoubLocPrecipEffPrevAC>"
      << "<ndlpepacVal species=\"Species_2\">-2</ndlpepacVal>"
      << "<ndlpepacVal species=\"Species_3\">-1.247639</ndlpepacVal>"
      << "<ndlpepacVal species=\"Species_4\">1.727392</ndlpepacVal>"
      << "</nciDoubLocPrecipEffPrevAC>"
      << "<nciDoubLocPrecipEffPrevBLo>"
      << "<ndlpepblVal species=\"Species_2\">0.9956259</ndlpepblVal>"
      << "<ndlpepblVal species=\"Species_3\">0.9</ndlpepblVal>"
      << "<ndlpepblVal species=\"Species_4\">0.9004499</ndlpepblVal>"
      << "</nciDoubLocPrecipEffPrevBLo>"
      << "<nciDoubLocPrecipEffPrevBHi>"
      << "<ndlpepbhVal species=\"Species_2\">0.9436914</ndlpepbhVal>"
      << "<ndlpepbhVal species=\"Species_3\">0.9082155</ndlpepbhVal>"
      << "<ndlpepbhVal species=\"Species_4\">0.9</ndlpepbhVal>"
      << "</nciDoubLocPrecipEffPrevBHi>"
      << "<nciDoubLocPrecipEffPrevC>"
      << "<ndlpepcVal species=\"Species_2\">-2</ndlpepcVal>"
      << "<ndlpepcVal species=\"Species_3\">3</ndlpepcVal>"
      << "<ndlpepcVal species=\"Species_4\">-1.966302</ndlpepcVal>"
      << "</nciDoubLocPrecipEffPrevC>"
      << "<nciDoubLocPrecipType>" << clPrecipitationEffectBase::seasonal_precip << "</nciDoubLocPrecipType>"
      << "</NCIMasterGrowth2>"

      << "<NCIMasterGrowth3>"
      << "<nciWhichShadingEffect>" << no_shading << "</nciWhichShadingEffect>"
      << "<nciWhichCrowdingEffect>" << no_crowding_effect << "</nciWhichCrowdingEffect>"
      << "<nciWhichNCITerm>" << no_nci_term << "</nciWhichNCITerm>"
      << "<nciWhichSizeEffect>" << no_size_effect << "</nciWhichSizeEffect>"
      << "<nciWhichDamageEffect>" << no_damage_effect << "</nciWhichDamageEffect>"
      << "<nciWhichPrecipitationEffect>" << no_precip_effect << "</nciWhichPrecipitationEffect>"
      << "<nciWhichTemperatureEffect>" << double_local_diff_temp_effect << "</nciWhichTemperatureEffect>"
      << "<nciWhichNitrogenEffect>" << no_nitrogen_effect << "</nciWhichNitrogenEffect>"
      << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
      << "<gr_stochGrowthMethod>" << deterministic_pdf << "</gr_stochGrowthMethod>"
      << "<gr_nciMaxPotentialGrowth>"
      << "<gr_nmpgVal species=\"Species_5\">1</gr_nmpgVal>"
      << "<gr_nmpgVal species=\"Species_6\">1</gr_nmpgVal>"
      << "<gr_nmpgVal species=\"Species_7\">1</gr_nmpgVal>"
      << "</gr_nciMaxPotentialGrowth>"
      << "<nciDoubLocTempEffCurrAA>"
      << "<ndltecaaVal species=\"Species_5\">0.350302</ndltecaaVal>"
      << "<ndltecaaVal species=\"Species_6\">0.03393611</ndltecaaVal>"
      << "<ndltecaaVal species=\"Species_7\">1</ndltecaaVal>"
      << "</nciDoubLocTempEffCurrAA>"
      << "<nciDoubLocTempEffCurrABLo>"
      << "<ndltecablVal species=\"Species_5\">0.9694824</ndltecablVal>"
      << "<ndltecablVal species=\"Species_6\">0.9851785</ndltecablVal>"
      << "<ndltecablVal species=\"Species_7\">0.9123379</ndltecablVal>"
      << "</nciDoubLocTempEffCurrABLo>"
      << "<nciDoubLocTempEffCurrABHi>"
      << "<ndltecabhVal species=\"Species_5\">0.9928637</ndltecabhVal>"
      << "<ndltecabhVal species=\"Species_6\">0.9223768</ndltecabhVal>"
      << "<ndltecabhVal species=\"Species_7\">1</ndltecabhVal>"
      << "</nciDoubLocTempEffCurrABHi>"
      << "<nciDoubLocTempEffCurrAC>"
      << "<ndltecacVal species=\"Species_5\">4.112366</ndltecacVal>"
      << "<ndltecacVal species=\"Species_6\">4.127323</ndltecacVal>"
      << "<ndltecacVal species=\"Species_7\">8.614621</ndltecacVal>"
      << "</nciDoubLocTempEffCurrAC>"
      << "<nciDoubLocTempEffCurrBLo>"
      << "<ndltecblVal species=\"Species_5\">0.9004149</ndltecblVal>"
      << "<ndltecblVal species=\"Species_6\">0.986613</ndltecblVal>"
      << "<ndltecblVal species=\"Species_7\">0.9050776</ndltecblVal>"
      << "</nciDoubLocTempEffCurrBLo>"
      << "<nciDoubLocTempEffCurrBHi>"
      << "<ndltecbhVal species=\"Species_5\">0.9840264</ndltecbhVal>"
      << "<ndltecbhVal species=\"Species_6\">0.9657315</ndltecbhVal>"
      << "<ndltecbhVal species=\"Species_7\">0.9205827</ndltecbhVal>"
      << "</nciDoubLocTempEffCurrBHi>"
      << "<nciDoubLocTempEffCurrC>"
      << "<ndlteccVal species=\"Species_5\">-0.7583497</ndlteccVal>"
      << "<ndlteccVal species=\"Species_6\">9.963309</ndlteccVal>"
      << "<ndlteccVal species=\"Species_7\">1.043878</ndlteccVal>"
      << "</nciDoubLocTempEffCurrC>"
      << "<nciDoubLocTempEffPrevAA>"
      << "<ndltepaaVal species=\"Species_5\">1</ndltepaaVal>"
      << "<ndltepaaVal species=\"Species_6\">0.05439883</ndltepaaVal>"
      << "<ndltepaaVal species=\"Species_7\">0.9999728</ndltepaaVal>"
      << "</nciDoubLocTempEffPrevAA>"
      << "<nciDoubLocTempEffPrevABLo>"
      << "<ndltepablVal species=\"Species_5\">0.9013303</ndltepablVal>"
      << "<ndltepablVal species=\"Species_6\">0.9000145</ndltepablVal>"
      << "<ndltepablVal species=\"Species_7\">0.9182816</ndltepablVal>"
      << "</nciDoubLocTempEffPrevABLo>"
      << "<nciDoubLocTempEffPrevABHi>"
      << "<ndltepabhVal species=\"Species_5\">0.9096494</ndltepabhVal>"
      << "<ndltepabhVal species=\"Species_6\">0.9994287</ndltepabhVal>"
      << "<ndltepabhVal species=\"Species_7\">1</ndltepabhVal>"
      << "</nciDoubLocTempEffPrevABHi>"
      << "<nciDoubLocTempEffPrevAC>"
      << "<ndltepacVal species=\"Species_5\">1.355715</ndltepacVal>"
      << "<ndltepacVal species=\"Species_6\">2.930429</ndltepacVal>"
      << "<ndltepacVal species=\"Species_7\">12.96049</ndltepacVal>"
      << "</nciDoubLocTempEffPrevAC>"
      << "<nciDoubLocTempEffPrevBLo>"
      << "<ndltepblVal species=\"Species_5\">0.9001837</ndltepblVal>"
      << "<ndltepblVal species=\"Species_6\">0.9745306</ndltepblVal>"
      << "<ndltepblVal species=\"Species_7\">0.9134678</ndltepblVal>"
      << "</nciDoubLocTempEffPrevBLo>"
      << "<nciDoubLocTempEffPrevBHi>"
      << "<ndltepbhVal species=\"Species_5\">0.9914288</ndltepbhVal>"
      << "<ndltepbhVal species=\"Species_6\">0.9304641</ndltepbhVal>"
      << "<ndltepbhVal species=\"Species_7\">0.9416269</ndltepbhVal>"
      << "</nciDoubLocTempEffPrevBHi>"
      << "<nciDoubLocTempEffPrevC>"
      << "<ndltepcVal species=\"Species_5\">-22.6664</ndltepcVal>"
      << "<ndltepcVal species=\"Species_6\">1.490487</ndltepcVal>"
      << "<ndltepcVal species=\"Species_7\">-0.3788826</ndltepcVal>"
      << "</nciDoubLocTempEffPrevC>"
      << "</NCIMasterGrowth3>"
      << "</paramFile>";
  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIDoubleLocalDiffClimateGrowthXMLFile2()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIDoubleLocalDiffClimateGrowthXMLFile2() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteNCIDoubleLocalCommon(oOut);
  int i;

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>ClimateImporter</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "</behavior>"

      // First NCI growth behavior: precip only
      << "<behavior>"
      << "<behaviorName>NCIMasterMortality</behaviorName>"
      << "<version>3</version>"
      << "<listPosition>2</listPosition>";
  for (i = 2; i < 5; i++) {
    oOut  << "<applyTo species=\"Species_" << i << "\" type=\"Sapling\"/>";
    oOut  << "<applyTo species=\"Species_" << i << "\" type=\"Adult\"/>";
  }
  oOut  << "</behavior>"
      // Second NCI growth behavior: temp only
      << "<behavior>"
      << "<behaviorName>NCIMasterMortality</behaviorName>"
      << "<version>3</version>"
      << "<listPosition>3</listPosition>";
  for (i = 5; i < 8; i++) {
    oOut  << "<applyTo species=\"Species_" << i << "\" type=\"Sapling\"/>";
    oOut  << "<applyTo species=\"Species_" << i << "\" type=\"Adult\"/>";
  }
  oOut  << "</behavior>"
      << "<behavior>"
      << "<behaviorName>RemoveDead</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>4</listPosition>";
  for (i = 2; i < 8; i++) {
      oOut  << "<applyTo species=\"Species_" << i << "\" type=\"Sapling\"/>";
      oOut  << "<applyTo species=\"Species_" << i << "\" type=\"Adult\"/>";
    }
    oOut << "</behavior>"
      << "</behaviorList>"
      << "<ClimateImporter1>"
      << "<sc_ciAWS>60.9</sc_ciAWS>"
      << "<sc_ciCalendarMean>0</sc_ciCalendarMean>"
      << "<sc_ciLTM>5</sc_ciLTM>"

      << "<sc_ciMonthlyTempJan>"
      << "<sc_cimtjanVal ts=\"-5\">-3.86</sc_cimtjanVal>"
      << "<sc_cimtjanVal ts=\"-4\">0.56</sc_cimtjanVal>"
      << "<sc_cimtjanVal ts=\"-3\">-1.51</sc_cimtjanVal>"
      << "<sc_cimtjanVal ts=\"-2\">5.03</sc_cimtjanVal>"
      << "<sc_cimtjanVal ts=\"-1\">-5.5</sc_cimtjanVal>"
      << "<sc_cimtjanVal ts=\"1\">-2.57</sc_cimtjanVal>"
      << "<sc_cimtjanVal ts=\"2\">-3.46</sc_cimtjanVal>"
      << "<sc_cimtjanVal ts=\"3\">-6.93</sc_cimtjanVal>"
      << "<sc_cimtjanVal ts=\"4\">-7.76</sc_cimtjanVal>"
      << "<sc_cimtjanVal ts=\"5\">-0.72</sc_cimtjanVal>"
      << "<sc_cimtjanVal ts=\"6\">1.3</sc_cimtjanVal>"
      << "</sc_ciMonthlyTempJan>"

      << "<sc_ciMonthlyTempFeb>"
      << "<sc_cimtfebVal ts=\"-5\">-1.56</sc_cimtfebVal>"
      << "<sc_cimtfebVal ts=\"-4\">-0.03</sc_cimtfebVal>"
      << "<sc_cimtfebVal ts=\"-3\">2.16</sc_cimtfebVal>"
      << "<sc_cimtfebVal ts=\"-2\">4.5</sc_cimtfebVal>"
      << "<sc_cimtfebVal ts=\"-1\">-0.6</sc_cimtfebVal>"
      << "<sc_cimtfebVal ts=\"1\">2.75</sc_cimtfebVal>"
      << "<sc_cimtfebVal ts=\"2\">-8.57</sc_cimtfebVal>"
      << "<sc_cimtfebVal ts=\"3\">1.98</sc_cimtfebVal>"
      << "<sc_cimtfebVal ts=\"4\">-7.5</sc_cimtfebVal>"
      << "<sc_cimtfebVal ts=\"5\">-2.44</sc_cimtfebVal>"
      << "<sc_cimtfebVal ts=\"6\">-9.36</sc_cimtfebVal>"
      << "</sc_ciMonthlyTempFeb>"

      << "<sc_ciMonthlyTempMar>"
      << "<sc_cimtmarVal ts=\"-5\">1.93</sc_cimtmarVal>"
      << "<sc_cimtmarVal ts=\"-4\">1.57</sc_cimtmarVal>"
      << "<sc_cimtmarVal ts=\"-3\">7.49</sc_cimtmarVal>"
      << "<sc_cimtmarVal ts=\"-2\">6.95</sc_cimtmarVal>"
      << "<sc_cimtmarVal ts=\"-1\">1.54</sc_cimtmarVal>"
      << "<sc_cimtmarVal ts=\"1\">2.94</sc_cimtmarVal>"
      << "<sc_cimtmarVal ts=\"2\">0.28</sc_cimtmarVal>"
      << "<sc_cimtmarVal ts=\"3\">0.3</sc_cimtmarVal>"
      << "<sc_cimtmarVal ts=\"4\">-0.78</sc_cimtmarVal>"
      << "<sc_cimtmarVal ts=\"5\">4.85</sc_cimtmarVal>"
      << "<sc_cimtmarVal ts=\"6\">3.78</sc_cimtmarVal>"
      << "</sc_ciMonthlyTempMar>"

      << "<sc_ciMonthlyTempApr>"
      << "<sc_cimtaprVal ts=\"-5\">5.53</sc_cimtaprVal>"
      << "<sc_cimtaprVal ts=\"-4\">11.17</sc_cimtaprVal>"
      << "<sc_cimtaprVal ts=\"-3\">6.21</sc_cimtaprVal>"
      << "<sc_cimtaprVal ts=\"-2\">11.68</sc_cimtaprVal>"
      << "<sc_cimtaprVal ts=\"-1\">8.66</sc_cimtaprVal>"
      << "<sc_cimtaprVal ts=\"1\">2.17</sc_cimtaprVal>"
      << "<sc_cimtaprVal ts=\"2\">5.9</sc_cimtaprVal>"
      << "<sc_cimtaprVal ts=\"3\">7.17</sc_cimtaprVal>"
      << "<sc_cimtaprVal ts=\"4\">8.67</sc_cimtaprVal>"
      << "<sc_cimtaprVal ts=\"5\">5.61</sc_cimtaprVal>"
      << "<sc_cimtaprVal ts=\"6\">4.56</sc_cimtaprVal>"
      << "</sc_ciMonthlyTempApr>"

      << "<sc_ciMonthlyTempMay>"
      << "<sc_cimtmayVal ts=\"-5\">10.59</sc_cimtmayVal>"
      << "<sc_cimtmayVal ts=\"-4\">7.49</sc_cimtmayVal>"
      << "<sc_cimtmayVal ts=\"-3\">7.66</sc_cimtmayVal>"
      << "<sc_cimtmayVal ts=\"-2\">12.52</sc_cimtmayVal>"
      << "<sc_cimtmayVal ts=\"-1\">10.68</sc_cimtmayVal>"
      << "<sc_cimtmayVal ts=\"1\">7.25</sc_cimtmayVal>"
      << "<sc_cimtmayVal ts=\"2\">7.6</sc_cimtmayVal>"
      << "<sc_cimtmayVal ts=\"3\">9.46</sc_cimtmayVal>"
      << "<sc_cimtmayVal ts=\"4\">11.26</sc_cimtmayVal>"
      << "<sc_cimtmayVal ts=\"5\">7.6</sc_cimtmayVal>"
      << "<sc_cimtmayVal ts=\"6\">6.9</sc_cimtmayVal>"
      << "</sc_ciMonthlyTempMay>"

      << "<sc_ciMonthlyTempJun>"
      << "<sc_cimtjunVal ts=\"-5\">14.99</sc_cimtjunVal>"
      << "<sc_cimtjunVal ts=\"-4\">7.67</sc_cimtjunVal>"
      << "<sc_cimtjunVal ts=\"-3\">10.1</sc_cimtjunVal>"
      << "<sc_cimtjunVal ts=\"-2\">14.33</sc_cimtjunVal>"
      << "<sc_cimtjunVal ts=\"-1\">16.65</sc_cimtjunVal>"
      << "<sc_cimtjunVal ts=\"1\">11.05</sc_cimtjunVal>"
      << "<sc_cimtjunVal ts=\"2\">17.16</sc_cimtjunVal>"
      << "<sc_cimtjunVal ts=\"3\">11.06</sc_cimtjunVal>"
      << "<sc_cimtjunVal ts=\"4\">17.72</sc_cimtjunVal>"
      << "<sc_cimtjunVal ts=\"5\">14.05</sc_cimtjunVal>"
      << "<sc_cimtjunVal ts=\"6\">13.52</sc_cimtjunVal>"
      << "</sc_ciMonthlyTempJun>"

      << "<sc_ciMonthlyTempJul>"
      << "<sc_cimtjulVal ts=\"-5\">13.42</sc_cimtjulVal>"
      << "<sc_cimtjulVal ts=\"-4\">15.48</sc_cimtjulVal>"
      << "<sc_cimtjulVal ts=\"-3\">15.24</sc_cimtjulVal>"
      << "<sc_cimtjulVal ts=\"-2\">17.87</sc_cimtjulVal>"
      << "<sc_cimtjulVal ts=\"-1\">14.13</sc_cimtjulVal>"
      << "<sc_cimtjulVal ts=\"1\">16.82</sc_cimtjulVal>"
      << "<sc_cimtjulVal ts=\"2\">22</sc_cimtjulVal>"
      << "<sc_cimtjulVal ts=\"3\">18.34</sc_cimtjulVal>"
      << "<sc_cimtjulVal ts=\"4\">20.99</sc_cimtjulVal>"
      << "<sc_cimtjulVal ts=\"5\">15.46</sc_cimtjulVal>"
      << "<sc_cimtjulVal ts=\"6\">15.74</sc_cimtjulVal>"
      << "</sc_ciMonthlyTempJul>"

      << "<sc_ciMonthlyTempAug>"
      << "<sc_cimtaugVal ts=\"-5\">7.55</sc_cimtaugVal>"
      << "<sc_cimtaugVal ts=\"-4\">12.01</sc_cimtaugVal>"
      << "<sc_cimtaugVal ts=\"-3\">15.55</sc_cimtaugVal>"
      << "<sc_cimtaugVal ts=\"-2\">16.23</sc_cimtaugVal>"
      << "<sc_cimtaugVal ts=\"-1\">19.9</sc_cimtaugVal>"
      << "<sc_cimtaugVal ts=\"1\">18.32</sc_cimtaugVal>"
      << "<sc_cimtaugVal ts=\"2\">15.97</sc_cimtaugVal>"
      << "<sc_cimtaugVal ts=\"3\">17.54</sc_cimtaugVal>"
      << "<sc_cimtaugVal ts=\"4\">17.46</sc_cimtaugVal>"
      << "<sc_cimtaugVal ts=\"5\">16.69</sc_cimtaugVal>"
      << "<sc_cimtaugVal ts=\"6\">17.48</sc_cimtaugVal>"
      << "</sc_ciMonthlyTempAug>"

      << "<sc_ciMonthlyTempSep>"
      << "<sc_cimtsepVal ts=\"-5\">13.72</sc_cimtsepVal>"
      << "<sc_cimtsepVal ts=\"-4\">17.95</sc_cimtsepVal>"
      << "<sc_cimtsepVal ts=\"-3\">11.19</sc_cimtsepVal>"
      << "<sc_cimtsepVal ts=\"-2\">16.39</sc_cimtsepVal>"
      << "<sc_cimtsepVal ts=\"-1\">5.87</sc_cimtsepVal>"
      << "<sc_cimtsepVal ts=\"1\">22.73</sc_cimtsepVal>"
      << "<sc_cimtsepVal ts=\"2\">20.94</sc_cimtsepVal>"
      << "<sc_cimtsepVal ts=\"3\">15.94</sc_cimtsepVal>"
      << "<sc_cimtsepVal ts=\"4\">18.87</sc_cimtsepVal>"
      << "<sc_cimtsepVal ts=\"5\">22.85</sc_cimtsepVal>"
      << "<sc_cimtsepVal ts=\"6\">19.53</sc_cimtsepVal>"
      << "</sc_ciMonthlyTempSep>"

      << "<sc_ciMonthlyTempOct>"
      << "<sc_cimtoctVal ts=\"-5\">2.83</sc_cimtoctVal>"
      << "<sc_cimtoctVal ts=\"-4\">7.09</sc_cimtoctVal>"
      << "<sc_cimtoctVal ts=\"-3\">10.7</sc_cimtoctVal>"
      << "<sc_cimtoctVal ts=\"-2\">2.84</sc_cimtoctVal>"
      << "<sc_cimtoctVal ts=\"-1\">4.3</sc_cimtoctVal>"
      << "<sc_cimtoctVal ts=\"1\">7.92</sc_cimtoctVal>"
      << "<sc_cimtoctVal ts=\"2\">8.18</sc_cimtoctVal>"
      << "<sc_cimtoctVal ts=\"3\">8.43</sc_cimtoctVal>"
      << "<sc_cimtoctVal ts=\"4\">8.68</sc_cimtoctVal>"
      << "<sc_cimtoctVal ts=\"5\">8.94</sc_cimtoctVal>"
      << "<sc_cimtoctVal ts=\"6\">9.19</sc_cimtoctVal>"
      << "</sc_ciMonthlyTempOct>"

      << "<sc_ciMonthlyTempNov>"
      << "<sc_cimtnovVal ts=\"-5\">-0.58</sc_cimtnovVal>"
      << "<sc_cimtnovVal ts=\"-4\">8.71</sc_cimtnovVal>"
      << "<sc_cimtnovVal ts=\"-3\">7.51</sc_cimtnovVal>"
      << "<sc_cimtnovVal ts=\"-2\">-0.57</sc_cimtnovVal>"
      << "<sc_cimtnovVal ts=\"-1\">1.98</sc_cimtnovVal>"
      << "<sc_cimtnovVal ts=\"1\">2.48</sc_cimtnovVal>"
      << "<sc_cimtnovVal ts=\"2\">2.56</sc_cimtnovVal>"
      << "<sc_cimtnovVal ts=\"3\">2.64</sc_cimtnovVal>"
      << "<sc_cimtnovVal ts=\"4\">2.72</sc_cimtnovVal>"
      << "<sc_cimtnovVal ts=\"5\">2.8</sc_cimtnovVal>"
      << "<sc_cimtnovVal ts=\"6\">2.88</sc_cimtnovVal>"
      << "</sc_ciMonthlyTempNov>"

      << "<sc_ciMonthlyTempDec>"
      << "<sc_cimtdecVal ts=\"-5\">2.34</sc_cimtdecVal>"
      << "<sc_cimtdecVal ts=\"-4\">-3.33</sc_cimtdecVal>"
      << "<sc_cimtdecVal ts=\"-3\">-0.66</sc_cimtdecVal>"
      << "<sc_cimtdecVal ts=\"-2\">3.22</sc_cimtdecVal>"
      << "<sc_cimtdecVal ts=\"-1\">0.6</sc_cimtdecVal>"
      << "<sc_cimtdecVal ts=\"1\">-9.6</sc_cimtdecVal>"
      << "<sc_cimtdecVal ts=\"2\">-6.94</sc_cimtdecVal>"
      << "<sc_cimtdecVal ts=\"3\">-6.51</sc_cimtdecVal>"
      << "<sc_cimtdecVal ts=\"4\">-1.59</sc_cimtdecVal>"
      << "<sc_cimtdecVal ts=\"5\">0.19</sc_cimtdecVal>"
      << "<sc_cimtdecVal ts=\"6\">2.49</sc_cimtdecVal>"
      << "</sc_ciMonthlyTempDec>"

      << "<sc_ciMonthlyPptJan>"
      << "<sc_cimpjanVal ts=\"-5\">156.75</sc_cimpjanVal>"
      << "<sc_cimpjanVal ts=\"-4\">200.8</sc_cimpjanVal>"
      << "<sc_cimpjanVal ts=\"-3\">76.15</sc_cimpjanVal>"
      << "<sc_cimpjanVal ts=\"-2\">144.61</sc_cimpjanVal>"
      << "<sc_cimpjanVal ts=\"-1\">81.05</sc_cimpjanVal>"
      << "<sc_cimpjanVal ts=\"1\">161.48</sc_cimpjanVal>"
      << "<sc_cimpjanVal ts=\"2\">152.09</sc_cimpjanVal>"
      << "<sc_cimpjanVal ts=\"3\">152.5</sc_cimpjanVal>"
      << "<sc_cimpjanVal ts=\"4\">152.71</sc_cimpjanVal>"
      << "<sc_cimpjanVal ts=\"5\">78.44</sc_cimpjanVal>"
      << "<sc_cimpjanVal ts=\"6\">123.19</sc_cimpjanVal>"
      << "</sc_ciMonthlyPptJan>"

      << "<sc_ciMonthlyPptFeb>"
      << "<sc_cimpfebVal ts=\"-5\">187.85</sc_cimpfebVal>"
      << "<sc_cimpfebVal ts=\"-4\">124.88</sc_cimpfebVal>"
      << "<sc_cimpfebVal ts=\"-3\">63.49</sc_cimpfebVal>"
      << "<sc_cimpfebVal ts=\"-2\">192.17</sc_cimpfebVal>"
      << "<sc_cimpfebVal ts=\"-1\">182.35</sc_cimpfebVal>"
      << "<sc_cimpfebVal ts=\"1\">199.32</sc_cimpfebVal>"
      << "<sc_cimpfebVal ts=\"2\">192.94</sc_cimpfebVal>"
      << "<sc_cimpfebVal ts=\"3\">188.1</sc_cimpfebVal>"
      << "<sc_cimpfebVal ts=\"4\">153.95</sc_cimpfebVal>"
      << "<sc_cimpfebVal ts=\"5\">89.79</sc_cimpfebVal>"
      << "<sc_cimpfebVal ts=\"6\">189.67</sc_cimpfebVal>"
      << "</sc_ciMonthlyPptFeb>"

      << "<sc_ciMonthlyPptMar>"
      << "<sc_cimpmarVal ts=\"-5\">208.64</sc_cimpmarVal>"
      << "<sc_cimpmarVal ts=\"-4\">233.06</sc_cimpmarVal>"
      << "<sc_cimpmarVal ts=\"-3\">246.05</sc_cimpmarVal>"
      << "<sc_cimpmarVal ts=\"-2\">183.98</sc_cimpmarVal>"
      << "<sc_cimpmarVal ts=\"-1\">144.42</sc_cimpmarVal>"
      << "<sc_cimpmarVal ts=\"1\">169.99</sc_cimpmarVal>"
      << "<sc_cimpmarVal ts=\"2\">105.49</sc_cimpmarVal>"
      << "<sc_cimpmarVal ts=\"3\">141.34</sc_cimpmarVal>"
      << "<sc_cimpmarVal ts=\"4\">84.71</sc_cimpmarVal>"
      << "<sc_cimpmarVal ts=\"5\">188.92</sc_cimpmarVal>"
      << "<sc_cimpmarVal ts=\"6\">93.47</sc_cimpmarVal>"
      << "</sc_ciMonthlyPptMar>"

      << "<sc_ciMonthlyPptApr>"
      << "<sc_cimpaprVal ts=\"-5\">61.72</sc_cimpaprVal>"
      << "<sc_cimpaprVal ts=\"-4\">197.01</sc_cimpaprVal>"
      << "<sc_cimpaprVal ts=\"-3\">146.71</sc_cimpaprVal>"
      << "<sc_cimpaprVal ts=\"-2\">173.62</sc_cimpaprVal>"
      << "<sc_cimpaprVal ts=\"-1\">50.19</sc_cimpaprVal>"
      << "<sc_cimpaprVal ts=\"1\">82.02</sc_cimpaprVal>"
      << "<sc_cimpaprVal ts=\"2\">77.49</sc_cimpaprVal>"
      << "<sc_cimpaprVal ts=\"3\">186.32</sc_cimpaprVal>"
      << "<sc_cimpaprVal ts=\"4\">174.4</sc_cimpaprVal>"
      << "<sc_cimpaprVal ts=\"5\">161.25</sc_cimpaprVal>"
      << "<sc_cimpaprVal ts=\"6\">99.76</sc_cimpaprVal>"
      << "</sc_ciMonthlyPptApr>"

      << "<sc_ciMonthlyPptMay>"
      << "<sc_cimpmayVal ts=\"-5\">98.88</sc_cimpmayVal>"
      << "<sc_cimpmayVal ts=\"-4\">221.62</sc_cimpmayVal>"
      << "<sc_cimpmayVal ts=\"-3\">245.51</sc_cimpmayVal>"
      << "<sc_cimpmayVal ts=\"-2\">227.17</sc_cimpmayVal>"
      << "<sc_cimpmayVal ts=\"-1\">157.19</sc_cimpmayVal>"
      << "<sc_cimpmayVal ts=\"1\">132.54</sc_cimpmayVal>"
      << "<sc_cimpmayVal ts=\"2\">121.74</sc_cimpmayVal>"
      << "<sc_cimpmayVal ts=\"3\">178.18</sc_cimpmayVal>"
      << "<sc_cimpmayVal ts=\"4\">102.86</sc_cimpmayVal>"
      << "<sc_cimpmayVal ts=\"5\">102.84</sc_cimpmayVal>"
      << "<sc_cimpmayVal ts=\"6\">172.41</sc_cimpmayVal>"
      << "</sc_ciMonthlyPptMay>"

      << "<sc_ciMonthlyPptJun>"
      << "<sc_cimpjunVal ts=\"-5\">144.55</sc_cimpjunVal>"
      << "<sc_cimpjunVal ts=\"-4\">142.87</sc_cimpjunVal>"
      << "<sc_cimpjunVal ts=\"-3\">184.78</sc_cimpjunVal>"
      << "<sc_cimpjunVal ts=\"-2\">249.3</sc_cimpjunVal>"
      << "<sc_cimpjunVal ts=\"-1\">201.05</sc_cimpjunVal>"
      << "<sc_cimpjunVal ts=\"1\">157.67</sc_cimpjunVal>"
      << "<sc_cimpjunVal ts=\"2\">133.89</sc_cimpjunVal>"
      << "<sc_cimpjunVal ts=\"3\">147.29</sc_cimpjunVal>"
      << "<sc_cimpjunVal ts=\"4\">123.74</sc_cimpjunVal>"
      << "<sc_cimpjunVal ts=\"5\">126.66</sc_cimpjunVal>"
      << "<sc_cimpjunVal ts=\"6\">134.35</sc_cimpjunVal>"
      << "</sc_ciMonthlyPptJun>"

      << "<sc_ciMonthlyPptJul>"
      << "<sc_cimpjulVal ts=\"-5\">96.74</sc_cimpjulVal>"
      << "<sc_cimpjulVal ts=\"-4\">198.29</sc_cimpjulVal>"
      << "<sc_cimpjulVal ts=\"-3\">56.77</sc_cimpjulVal>"
      << "<sc_cimpjulVal ts=\"-2\">55.16</sc_cimpjulVal>"
      << "<sc_cimpjulVal ts=\"-1\">174.6</sc_cimpjulVal>"
      << "<sc_cimpjulVal ts=\"1\">97.63</sc_cimpjulVal>"
      << "<sc_cimpjulVal ts=\"2\">141.94</sc_cimpjulVal>"
      << "<sc_cimpjulVal ts=\"3\">173.88</sc_cimpjulVal>"
      << "<sc_cimpjulVal ts=\"4\">166.53</sc_cimpjulVal>"
      << "<sc_cimpjulVal ts=\"5\">140.41</sc_cimpjulVal>"
      << "<sc_cimpjulVal ts=\"6\">128.89</sc_cimpjulVal>"
      << "</sc_ciMonthlyPptJul>"

      << "<sc_ciMonthlyPptAug>"
      << "<sc_cimpaugVal ts=\"-5\">250.84</sc_cimpaugVal>"
      << "<sc_cimpaugVal ts=\"-4\">145.97</sc_cimpaugVal>"
      << "<sc_cimpaugVal ts=\"-3\">104.14</sc_cimpaugVal>"
      << "<sc_cimpaugVal ts=\"-2\">99.69</sc_cimpaugVal>"
      << "<sc_cimpaugVal ts=\"-1\">59.28</sc_cimpaugVal>"
      << "<sc_cimpaugVal ts=\"1\">145.57</sc_cimpaugVal>"
      << "<sc_cimpaugVal ts=\"2\">156.69</sc_cimpaugVal>"
      << "<sc_cimpaugVal ts=\"3\">146.55</sc_cimpaugVal>"
      << "<sc_cimpaugVal ts=\"4\">167.73</sc_cimpaugVal>"
      << "<sc_cimpaugVal ts=\"5\">147.67</sc_cimpaugVal>"
      << "<sc_cimpaugVal ts=\"6\">119.52</sc_cimpaugVal>"
      << "</sc_ciMonthlyPptAug>"

      << "<sc_ciMonthlyPptSep>"
      << "<sc_cimpsepVal ts=\"-5\">154.02</sc_cimpsepVal>"
      << "<sc_cimpsepVal ts=\"-4\">124.84</sc_cimpsepVal>"
      << "<sc_cimpsepVal ts=\"-3\">142.08</sc_cimpsepVal>"
      << "<sc_cimpsepVal ts=\"-2\">207.51</sc_cimpsepVal>"
      << "<sc_cimpsepVal ts=\"-1\">87.88</sc_cimpsepVal>"
      << "<sc_cimpsepVal ts=\"1\">134.38</sc_cimpsepVal>"
      << "<sc_cimpsepVal ts=\"2\">89.78</sc_cimpsepVal>"
      << "<sc_cimpsepVal ts=\"3\">173.37</sc_cimpsepVal>"
      << "<sc_cimpsepVal ts=\"4\">146.16</sc_cimpsepVal>"
      << "<sc_cimpsepVal ts=\"5\">108.71</sc_cimpsepVal>"
      << "<sc_cimpsepVal ts=\"6\">90.68</sc_cimpsepVal>"
      << "</sc_ciMonthlyPptSep>"

      << "<sc_ciMonthlyPptOct>"
      << "<sc_cimpoctVal ts=\"-5\">129.54</sc_cimpoctVal>"
      << "<sc_cimpoctVal ts=\"-4\">72.4</sc_cimpoctVal>"
      << "<sc_cimpoctVal ts=\"-3\">162.74</sc_cimpoctVal>"
      << "<sc_cimpoctVal ts=\"-2\">51.89</sc_cimpoctVal>"
      << "<sc_cimpoctVal ts=\"-1\">98.17</sc_cimpoctVal>"
      << "<sc_cimpoctVal ts=\"1\">100.17</sc_cimpoctVal>"
      << "<sc_cimpoctVal ts=\"2\">178.11</sc_cimpoctVal>"
      << "<sc_cimpoctVal ts=\"3\">120.16</sc_cimpoctVal>"
      << "<sc_cimpoctVal ts=\"4\">198.43</sc_cimpoctVal>"
      << "<sc_cimpoctVal ts=\"5\">75.22</sc_cimpoctVal>"
      << "<sc_cimpoctVal ts=\"6\">198.3</sc_cimpoctVal>"
      << "</sc_ciMonthlyPptOct>"

      << "<sc_ciMonthlyPptNov>"
      << "<sc_cimpnovVal ts=\"-5\">186.31</sc_cimpnovVal>"
      << "<sc_cimpnovVal ts=\"-4\">74.2</sc_cimpnovVal>"
      << "<sc_cimpnovVal ts=\"-3\">68.19</sc_cimpnovVal>"
      << "<sc_cimpnovVal ts=\"-2\">197.74</sc_cimpnovVal>"
      << "<sc_cimpnovVal ts=\"-1\">222.2</sc_cimpnovVal>"
      << "<sc_cimpnovVal ts=\"1\">112.34</sc_cimpnovVal>"
      << "<sc_cimpnovVal ts=\"2\">191.22</sc_cimpnovVal>"
      << "<sc_cimpnovVal ts=\"3\">125.47</sc_cimpnovVal>"
      << "<sc_cimpnovVal ts=\"4\">79.8</sc_cimpnovVal>"
      << "<sc_cimpnovVal ts=\"5\">116.29</sc_cimpnovVal>"
      << "<sc_cimpnovVal ts=\"6\">146.75</sc_cimpnovVal>"
      << "</sc_ciMonthlyPptNov>"

      << "<sc_ciMonthlyPptDec>"
      << "<sc_cimpdecVal ts=\"-5\">168.86</sc_cimpdecVal>"
      << "<sc_cimpdecVal ts=\"-4\">153.39</sc_cimpdecVal>"
      << "<sc_cimpdecVal ts=\"-3\">80.31</sc_cimpdecVal>"
      << "<sc_cimpdecVal ts=\"-2\">203.43</sc_cimpdecVal>"
      << "<sc_cimpdecVal ts=\"-1\">50.59</sc_cimpdecVal>"
      << "<sc_cimpdecVal ts=\"1\">137.22</sc_cimpdecVal>"
      << "<sc_cimpdecVal ts=\"2\">101.29</sc_cimpdecVal>"
      << "<sc_cimpdecVal ts=\"3\">159.21</sc_cimpdecVal>"
      << "<sc_cimpdecVal ts=\"4\">171.75</sc_cimpdecVal>"
      << "<sc_cimpdecVal ts=\"5\">191.54</sc_cimpdecVal>"
      << "<sc_cimpdecVal ts=\"6\">131.83</sc_cimpdecVal>"
      << "</sc_ciMonthlyPptDec>"

      << "<sc_ciJanRad>7468.475</sc_ciJanRad>"
      << "<sc_ciFebRad>10353.32</sc_ciFebRad>"
      << "<sc_ciMarRad>17453.07</sc_ciMarRad>"
      << "<sc_ciAprRad>22721.85</sc_ciAprRad>"
      << "<sc_ciMayRad>27901.37</sc_ciMayRad>"
      << "<sc_ciJunRad>28677.54</sc_ciJunRad>"
      << "<sc_ciJulRad>28764.65</sc_ciJulRad>"
      << "<sc_ciAugRad>25075.4</sc_ciAugRad>"
      << "<sc_ciSepRad>19259.27</sc_ciSepRad>"
      << "<sc_ciOctRad>12609.6</sc_ciOctRad>"
      << "<sc_ciNovRad>7988.013</sc_ciNovRad>"
      << "<sc_ciDecRad>6307.151</sc_ciDecRad>"
      << "</ClimateImporter1>"

      << "<NCIMasterMortality2>"
      << "<nciWhichShadingEffect>" << no_shading << "</nciWhichShadingEffect>"
      << "<nciWhichCrowdingEffect>" << no_crowding_effect << "</nciWhichCrowdingEffect>"
      << "<nciWhichNCITerm>" << no_nci_term << "</nciWhichNCITerm>"
      << "<nciWhichSizeEffect>" << no_size_effect << "</nciWhichSizeEffect>"
      << "<nciWhichDamageEffect>" << no_damage_effect << "</nciWhichDamageEffect>"
      << "<nciWhichPrecipitationEffect>" << double_local_diff_precip_effect << "</nciWhichPrecipitationEffect>"
      << "<nciWhichTemperatureEffect>" << no_temp_effect << "</nciWhichTemperatureEffect>"
      << "<nciWhichNitrogenEffect>" << no_nitrogen_effect << "</nciWhichNitrogenEffect>"
      << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
      << "<gr_stochGrowthMethod>" << deterministic_pdf << "</gr_stochGrowthMethod>"
      << "<mo_nciMaxPotentialSurvival>"
      << "<mo_nmpsVal species=\"Species_2\">1</mo_nmpsVal>"
      << "<mo_nmpsVal species=\"Species_3\">1</mo_nmpsVal>"
      << "<mo_nmpsVal species=\"Species_4\">1</mo_nmpsVal>"
      << "</mo_nciMaxPotentialSurvival>"
      << "<mo_nciMortSurvPeriod>1</mo_nciMortSurvPeriod>"
      << "<nciDoubLocPrecipEffCurrAA>"
      << "<ndlpecaaVal species=\"Species_2\">0.93</ndlpecaaVal>"
      << "<ndlpecaaVal species=\"Species_3\">1.8393E-05</ndlpecaaVal>"
      << "<ndlpecaaVal species=\"Species_4\">0.9788117</ndlpecaaVal>"
      << "</nciDoubLocPrecipEffCurrAA>"
      << "<nciDoubLocPrecipEffCurrABLo>"
      << "<ndlpecablVal species=\"Species_2\">0.9979457</ndlpecablVal>"
      << "<ndlpecablVal species=\"Species_3\">0.9739622</ndlpecablVal>"
      << "<ndlpecablVal species=\"Species_4\">0.9112952</ndlpecablVal>"
      << "</nciDoubLocPrecipEffCurrABLo>"
      << "<nciDoubLocPrecipEffCurrABHi>"
      << "<ndlpecabhVal species=\"Species_2\">0.9967062</ndlpecabhVal>"
      << "<ndlpecabhVal species=\"Species_3\">0.9278246</ndlpecabhVal>"
      << "<ndlpecabhVal species=\"Species_4\">0.943658</ndlpecabhVal>"
      << "</nciDoubLocPrecipEffCurrABHi>"
      << "<nciDoubLocPrecipEffCurrAC>"
      << "<ndlpecacVal species=\"Species_2\">1.11607</ndlpecacVal>"
      << "<ndlpecacVal species=\"Species_3\">-0.109959</ndlpecacVal>"
      << "<ndlpecacVal species=\"Species_4\">3</ndlpecacVal>"
      << "</nciDoubLocPrecipEffCurrAC>"
      << "<nciDoubLocPrecipEffCurrBLo>"
      << "<ndlpecblVal species=\"Species_2\">0.9057236</ndlpecblVal>"
      << "<ndlpecblVal species=\"Species_3\">0.9948863</ndlpecblVal>"
      << "<ndlpecblVal species=\"Species_4\">0.9001916</ndlpecblVal>"
      << "</nciDoubLocPrecipEffCurrBLo>"
      << "<nciDoubLocPrecipEffCurrBHi>"
      << "<ndlpecbhVal species=\"Species_2\">0.9136399</ndlpecbhVal>"
      << "<ndlpecbhVal species=\"Species_3\">0.9475929</ndlpecbhVal>"
      << "<ndlpecbhVal species=\"Species_4\">0.9843666</ndlpecbhVal>"
      << "</nciDoubLocPrecipEffCurrBHi>"
      << "<nciDoubLocPrecipEffCurrC>"
      << "<ndlpeccVal species=\"Species_2\">-1.892206</ndlpeccVal>"
      << "<ndlpeccVal species=\"Species_3\">0.5525589</ndlpeccVal>"
      << "<ndlpeccVal species=\"Species_4\">2.999962</ndlpeccVal>"
      << "</nciDoubLocPrecipEffCurrC>"
      << "<nciDoubLocPrecipEffPrevAA>"
      << "<ndlpepaaVal species=\"Species_2\">0.07</ndlpepaaVal>"
      << "<ndlpepaaVal species=\"Species_3\">0.999981607</ndlpepaaVal>"
      << "<ndlpepaaVal species=\"Species_4\">0.0211883</ndlpepaaVal>"
      << "</nciDoubLocPrecipEffPrevAA>"
      << "<nciDoubLocPrecipEffPrevABLo>"
      << "<ndlpepablVal species=\"Species_2\">0.9733152</ndlpepablVal>"
      << "<ndlpepablVal species=\"Species_3\">0.9752083</ndlpepablVal>"
      << "<ndlpepablVal species=\"Species_4\">0.9294581</ndlpepablVal>"
      << "</nciDoubLocPrecipEffPrevABLo>"
      << "<nciDoubLocPrecipEffPrevABHi>"
      << "<ndlpepabhVal species=\"Species_2\">0.9</ndlpepabhVal>"
      << "<ndlpepabhVal species=\"Species_3\">0.90253</ndlpepabhVal>"
      << "<ndlpepabhVal species=\"Species_4\">1</ndlpepabhVal>"
      << "</nciDoubLocPrecipEffPrevABHi>"
      << "<nciDoubLocPrecipEffPrevAC>"
      << "<ndlpepacVal species=\"Species_2\">-2</ndlpepacVal>"
      << "<ndlpepacVal species=\"Species_3\">-1.247639</ndlpepacVal>"
      << "<ndlpepacVal species=\"Species_4\">1.727392</ndlpepacVal>"
      << "</nciDoubLocPrecipEffPrevAC>"
      << "<nciDoubLocPrecipEffPrevBLo>"
      << "<ndlpepblVal species=\"Species_2\">0.9956259</ndlpepblVal>"
      << "<ndlpepblVal species=\"Species_3\">0.9</ndlpepblVal>"
      << "<ndlpepblVal species=\"Species_4\">0.9004499</ndlpepblVal>"
      << "</nciDoubLocPrecipEffPrevBLo>"
      << "<nciDoubLocPrecipEffPrevBHi>"
      << "<ndlpepbhVal species=\"Species_2\">0.9436914</ndlpepbhVal>"
      << "<ndlpepbhVal species=\"Species_3\">0.9082155</ndlpepbhVal>"
      << "<ndlpepbhVal species=\"Species_4\">0.9</ndlpepbhVal>"
      << "</nciDoubLocPrecipEffPrevBHi>"
      << "<nciDoubLocPrecipEffPrevC>"
      << "<ndlpepcVal species=\"Species_2\">-2</ndlpepcVal>"
      << "<ndlpepcVal species=\"Species_3\">3</ndlpepcVal>"
      << "<ndlpepcVal species=\"Species_4\">-1.966302</ndlpepcVal>"
      << "</nciDoubLocPrecipEffPrevC>"
      << "<nciDoubLocPrecipType>" << clPrecipitationEffectBase::water_deficit << "</nciDoubLocPrecipType>"
      << "</NCIMasterMortality2>"

      << "<NCIMasterMortality3>"
      << "<nciWhichShadingEffect>" << no_shading << "</nciWhichShadingEffect>"
      << "<nciWhichCrowdingEffect>" << no_crowding_effect << "</nciWhichCrowdingEffect>"
      << "<nciWhichNCITerm>" << no_nci_term << "</nciWhichNCITerm>"
      << "<nciWhichSizeEffect>" << no_size_effect << "</nciWhichSizeEffect>"
      << "<nciWhichDamageEffect>" << no_damage_effect << "</nciWhichDamageEffect>"
      << "<nciWhichPrecipitationEffect>" << no_precip_effect << "</nciWhichPrecipitationEffect>"
      << "<nciWhichTemperatureEffect>" << double_local_diff_temp_effect << "</nciWhichTemperatureEffect>"
      << "<nciWhichNitrogenEffect>" << no_nitrogen_effect << "</nciWhichNitrogenEffect>"
      << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
      << "<gr_stochGrowthMethod>" << deterministic_pdf << "</gr_stochGrowthMethod>"
      << "<mo_nciMaxPotentialSurvival>"
      << "<mo_nmpsVal species=\"Species_5\">1</mo_nmpsVal>"
      << "<mo_nmpsVal species=\"Species_6\">1</mo_nmpsVal>"
      << "<mo_nmpsVal species=\"Species_7\">1</mo_nmpsVal>"
      << "</mo_nciMaxPotentialSurvival>"
      << "<mo_nciMortSurvPeriod>1</mo_nciMortSurvPeriod>"
      << "<nciDoubLocTempEffCurrAA>"
      << "<ndltecaaVal species=\"Species_5\">0.350302</ndltecaaVal>"
      << "<ndltecaaVal species=\"Species_6\">0.03393611</ndltecaaVal>"
      << "<ndltecaaVal species=\"Species_7\">1</ndltecaaVal>"
      << "</nciDoubLocTempEffCurrAA>"
      << "<nciDoubLocTempEffCurrABLo>"
      << "<ndltecablVal species=\"Species_5\">0.9694824</ndltecablVal>"
      << "<ndltecablVal species=\"Species_6\">0.9851785</ndltecablVal>"
      << "<ndltecablVal species=\"Species_7\">0.9123379</ndltecablVal>"
      << "</nciDoubLocTempEffCurrABLo>"
      << "<nciDoubLocTempEffCurrABHi>"
      << "<ndltecabhVal species=\"Species_5\">0.9928637</ndltecabhVal>"
      << "<ndltecabhVal species=\"Species_6\">0.9223768</ndltecabhVal>"
      << "<ndltecabhVal species=\"Species_7\">1</ndltecabhVal>"
      << "</nciDoubLocTempEffCurrABHi>"
      << "<nciDoubLocTempEffCurrAC>"
      << "<ndltecacVal species=\"Species_5\">4.112366</ndltecacVal>"
      << "<ndltecacVal species=\"Species_6\">4.127323</ndltecacVal>"
      << "<ndltecacVal species=\"Species_7\">8.614621</ndltecacVal>"
      << "</nciDoubLocTempEffCurrAC>"
      << "<nciDoubLocTempEffCurrBLo>"
      << "<ndltecblVal species=\"Species_5\">0.9004149</ndltecblVal>"
      << "<ndltecblVal species=\"Species_6\">0.986613</ndltecblVal>"
      << "<ndltecblVal species=\"Species_7\">0.9050776</ndltecblVal>"
      << "</nciDoubLocTempEffCurrBLo>"
      << "<nciDoubLocTempEffCurrBHi>"
      << "<ndltecbhVal species=\"Species_5\">0.9840264</ndltecbhVal>"
      << "<ndltecbhVal species=\"Species_6\">0.9657315</ndltecbhVal>"
      << "<ndltecbhVal species=\"Species_7\">0.9205827</ndltecbhVal>"
      << "</nciDoubLocTempEffCurrBHi>"
      << "<nciDoubLocTempEffCurrC>"
      << "<ndlteccVal species=\"Species_5\">-0.7583497</ndlteccVal>"
      << "<ndlteccVal species=\"Species_6\">9.963309</ndlteccVal>"
      << "<ndlteccVal species=\"Species_7\">1.043878</ndlteccVal>"
      << "</nciDoubLocTempEffCurrC>"
      << "<nciDoubLocTempEffPrevAA>"
      << "<ndltepaaVal species=\"Species_5\">0.649698</ndltepaaVal>"
      << "<ndltepaaVal species=\"Species_6\">0.96606389</ndltepaaVal>"
      << "<ndltepaaVal species=\"Species_7\">0</ndltepaaVal>"
      << "</nciDoubLocTempEffPrevAA>"
      << "<nciDoubLocTempEffPrevABLo>"
      << "<ndltepablVal species=\"Species_5\">0.9013303</ndltepablVal>"
      << "<ndltepablVal species=\"Species_6\">0.9000145</ndltepablVal>"
      << "<ndltepablVal species=\"Species_7\">0.9182816</ndltepablVal>"
      << "</nciDoubLocTempEffPrevABLo>"
      << "<nciDoubLocTempEffPrevABHi>"
      << "<ndltepabhVal species=\"Species_5\">0.9096494</ndltepabhVal>"
      << "<ndltepabhVal species=\"Species_6\">0.9994287</ndltepabhVal>"
      << "<ndltepabhVal species=\"Species_7\">1</ndltepabhVal>"
      << "</nciDoubLocTempEffPrevABHi>"
      << "<nciDoubLocTempEffPrevAC>"
      << "<ndltepacVal species=\"Species_5\">1.355715</ndltepacVal>"
      << "<ndltepacVal species=\"Species_6\">2.930429</ndltepacVal>"
      << "<ndltepacVal species=\"Species_7\">12.96049</ndltepacVal>"
      << "</nciDoubLocTempEffPrevAC>"
      << "<nciDoubLocTempEffPrevBLo>"
      << "<ndltepblVal species=\"Species_5\">0.9001837</ndltepblVal>"
      << "<ndltepblVal species=\"Species_6\">0.9745306</ndltepblVal>"
      << "<ndltepblVal species=\"Species_7\">0.9134678</ndltepblVal>"
      << "</nciDoubLocTempEffPrevBLo>"
      << "<nciDoubLocTempEffPrevBHi>"
      << "<ndltepbhVal species=\"Species_5\">0.9914288</ndltepbhVal>"
      << "<ndltepbhVal species=\"Species_6\">0.9304641</ndltepbhVal>"
      << "<ndltepbhVal species=\"Species_7\">0.9416269</ndltepbhVal>"
      << "</nciDoubLocTempEffPrevBHi>"
      << "<nciDoubLocTempEffPrevC>"
      << "<ndltepcVal species=\"Species_5\">-22.6664</ndltepcVal>"
      << "<ndltepcVal species=\"Species_6\">1.490487</ndltepcVal>"
      << "<ndltepcVal species=\"Species_7\">-0.3788826</ndltepcVal>"
      << "</nciDoubLocTempEffPrevC>"
      << "</NCIMasterMortality3>"
      << "</paramFile>";
  oOut.close();

  return cFileString;
}



////////////////////////////////////////////////////////////////////////////
// WriteNCIDoubleLocalCommon
////////////////////////////////////////////////////////////////////////////
void WriteNCIDoubleLocalCommon(std::fstream &oOut) {
  using namespace std;

  int i;

   oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">"
      << "<plot>"
      << "<timesteps>6</timesteps>"
      << "<yearsPerTimestep>1</yearsPerTimestep>"
      << "<randomSeed>1</randomSeed>"
      << "<plot_lenX>200.0</plot_lenX>"
      << "<plot_lenY>200.0</plot_lenY>"
      << "<plot_latitude>55.37</plot_latitude>"
      << "<plot_precip_mm_yr>115</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88</plot_temp_C>"
      << "<plot_n_dep>4.76</plot_n_dep>"
      << "<plot_seasonal_precipitation>1150.65</plot_seasonal_precipitation>"
      << "<plot_water_deficit>456.2</plot_water_deficit>"
      << "</plot>";

  oOut << "<trees>"
      << "<tr_speciesList>";
  for (i = 1; i < 9; i++) {
    oOut << "<tr_species speciesName=\"Species_" << i << "\" />";
  }
  oOut << "</tr_speciesList>"
      << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
      << "<tr_minAdultDBH>";
  for (i = 1; i < 9; i++) {
    oOut << "<tr_madVal species=\"Species_" << i << "\">10.0</tr_madVal>";
  }
  oOut << "</tr_minAdultDBH>"
      << "<tr_maxSeedlingHeight>";
  for (i = 1; i < 9; i++) {
    oOut << "<tr_mshVal species=\"Species_" << i << "\">1.35</tr_mshVal>";
  }
  oOut << "</tr_maxSeedlingHeight>"
      << "</trees>"
      << "<allometry>"
      << "<tr_canopyHeight>";
  for (i = 1; i < 9; i++) {
    oOut << "<tr_chVal species=\"Species_" << i << "\">39.48</tr_chVal>";
  }
  oOut << "</tr_canopyHeight>"
      << "<tr_stdAsympCrownRad>";
  for (i = 1; i < 9; i++) {
    oOut << "<tr_sacrVal species=\"Species_" << i << "\">0.0549</tr_sacrVal>";
  }
  oOut << "</tr_stdAsympCrownRad>"
      << "<tr_stdCrownRadExp>";
  for (i = 1; i < 9; i++) {
    oOut << "<tr_screVal species=\"Species_" << i << "\">1.0</tr_screVal>";
  }
  oOut << "</tr_stdCrownRadExp>"
      << "<tr_stdMaxCrownRad>";
  for (i = 1; i < 9; i++) {
    oOut << "<tr_smcrVal species=\"Species_" << i << "\">10</tr_smcrVal>";
  }
  oOut  << "</tr_stdMaxCrownRad>"
      << "<tr_conversionDiam10ToDBH>";
  for (i = 1; i < 9; i++) {
    oOut << "<tr_cdtdVal species=\"Species_" << i << "\">1</tr_cdtdVal>";
  }
  oOut << "</tr_conversionDiam10ToDBH>"
      << "<tr_interceptDiam10ToDBH>";
  for (i = 1; i < 9; i++) {
    oOut << "<tr_idtdVal species=\"Species_" << i << "\">0</tr_idtdVal>";
  }
  oOut << "</tr_interceptDiam10ToDBH>"
      << "<tr_stdAsympCrownHt>";
  for (i = 1; i < 9; i++) {
    oOut << "<tr_sachVal species=\"Species_" << i << "\">0.389</tr_sachVal>";
  }
  oOut << "</tr_stdAsympCrownHt>"
      << "<tr_stdCrownHtExp>";
  for (i = 1; i < 9; i++) {
    oOut << "<tr_scheVal species=\"Species_" << i << "\">1.0</tr_scheVal>";
  }
  oOut << "</tr_stdCrownHtExp>"
      << "<tr_slopeOfHeight-Diam10>";
  for (i = 1; i < 9; i++) {
    oOut << "<tr_sohdVal species=\"Species_" << i << "\">0.03418</tr_sohdVal>";
  }
  oOut << "</tr_slopeOfHeight-Diam10>"
      << "<tr_slopeOfAsymHeight>";
  for (i = 1; i < 9; i++) {
    oOut << "<tr_soahVal species=\"Species_" << i << "\">0.0299</tr_soahVal>";
  }
  oOut << "</tr_slopeOfAsymHeight>"
      << "<tr_whatSeedlingHeightDiam>";
  for (i = 1; i < 9; i++) {
    oOut << "<tr_wsehdVal species=\"Species_" << i << "\">0</tr_wsehdVal>";
  }
  oOut << "</tr_whatSeedlingHeightDiam>"
      << "<tr_whatSaplingHeightDiam>";
  for (i = 1; i < 9; i++) {
    oOut << "<tr_wsahdVal species=\"Species_" << i << "\">0</tr_wsahdVal>";
  }
  oOut << "</tr_whatSaplingHeightDiam>"
      << "<tr_whatAdultHeightDiam>";
  for (i = 1; i < 9; i++) {
    oOut << "<tr_wahdVal species=\"Species_" << i << "\">0</tr_wahdVal>";
  }
  oOut << "</tr_whatAdultHeightDiam>"
      << "<tr_whatAdultCrownRadDiam>";
  for (i = 1; i < 9; i++) {
    oOut << "<tr_wacrdVal species=\"Species_" << i << "\">0</tr_wacrdVal>";
  }
  oOut << "</tr_whatAdultCrownRadDiam>"
      << "<tr_whatAdultCrownHeightHeight>";
  for (i = 1; i < 9; i++) {
    oOut << "<tr_wachhVal species=\"Species_" << i << "\">0</tr_wachhVal>";
  }
  oOut << "</tr_whatAdultCrownHeightHeight>"
      << "<tr_whatSaplingCrownRadDiam>";
  for (i = 1; i < 9; i++) {
    oOut << "<tr_wscrdVal species=\"Species_" << i << "\">0</tr_wscrdVal>";
  }
  oOut << "</tr_whatSaplingCrownRadDiam>"
      << "<tr_whatSaplingCrownHeightHeight>";
  for (i = 1; i < 9; i++) {
    oOut << "<tr_wschhVal species=\"Species_" << i << "\">0</tr_wschhVal>";
  }
  oOut << "</tr_whatSaplingCrownHeightHeight>"
      << "</allometry>";
}
