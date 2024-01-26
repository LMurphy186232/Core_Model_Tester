//---------------------------------------------------------------------------
// TestNCIDoubleNoLocalDiffClimateGrowth.cpp
//---------------------------------------------------------------------------
#include "TestNCIDoubleNoLocalDiffClimateGrowth.h"
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
TEST(NCIDoubleNoLocalDiffClimateGrowth, TestRun1) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTree **p_oTargetTree = new clTree*[18];
    float *p_fExpected = new float[18];
    float fDiam;
    int iSpecies, i;


    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile(WriteNCIDoubleNoLocalDiffClimateGrowthXMLFile1());
    p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject(
        "treepopulation");

    //Create our trees
    i = 0;
    fDiam = 11;
    iSpecies = 1;
    p_oTargetTree[i] = p_oPop->CreateTree(10, 10, iSpecies,
        clTreePopulation::adult, fDiam);

    i++;
    fDiam = 10.5;
    iSpecies = 1;
    p_oTargetTree[i] = p_oPop->CreateTree(50, 50, iSpecies,
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
    fDiam = 30;
    iSpecies = 1;
    p_oTargetTree[i] = p_oPop->CreateTree(50, 59, iSpecies,
        clTreePopulation::adult, fDiam);

    i++;
    fDiam = 45;
    iSpecies = 2;
    p_oTargetTree[i] = p_oPop->CreateTree(55, 55, iSpecies,
        clTreePopulation::adult, fDiam);

    i++;
    fDiam = 15;
    iSpecies = 3;
    p_oTargetTree[i] = p_oPop->CreateTree(60, 61, iSpecies,
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
    fDiam = 10.5;
    iSpecies = 4;
    p_oTargetTree[i] = p_oPop->CreateTree(50, 50, iSpecies,
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
    fDiam = 30;
    iSpecies = 4;
    p_oTargetTree[i] = p_oPop->CreateTree(50, 59, iSpecies,
        clTreePopulation::adult, fDiam);

    i++;
    fDiam = 45;
    iSpecies = 5;
    p_oTargetTree[i] = p_oPop->CreateTree(55, 55, iSpecies,
        clTreePopulation::adult, fDiam);

    i++;
    fDiam = 15;
    iSpecies = 6;
    p_oTargetTree[i] = p_oPop->CreateTree(60, 61, iSpecies,
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
    p_fExpected[0] = 11.85166594;
    p_fExpected[1] = 11.35166594;
    p_fExpected[2] = 16;
    p_fExpected[3] = 26;
    p_fExpected[4] = 30.85166594;
    p_fExpected[5] = 46;
    p_fExpected[6] = 16;
    p_fExpected[7] = 4.851665937;
    p_fExpected[8] = 5;
    p_fExpected[9] = 11.74951551;
    p_fExpected[10] = 11.24951551;
    p_fExpected[11] = 15.01020588;
    p_fExpected[12] = 25.06971657;
    p_fExpected[13] = 30.74951551;
    p_fExpected[14] = 45.01020588;
    p_fExpected[15] = 15.06971657;
    p_fExpected[16] = 4.749515513;
    p_fExpected[17] = 4.010205876;


    for (i = 0; i < 18; i++) {
      p_oTargetTree[i]->GetValue(p_oPop->GetDbhCode(p_oTargetTree[i]->GetSpecies(),
          p_oTargetTree[i]->GetType()), &fDiam);
      EXPECT_LT(fabs(fDiam - p_fExpected[i])/fDiam, 0.001);
    }

    //-----------------------------------------------------------------------//
    // Timestep 2
    //-----------------------------------------------------------------------//
    p_oSimManager->RunSim(1);

    //----- Check diameter --------------------------------------------------//
    p_fExpected[0] = 12.70333187;
    p_fExpected[1] = 12.20333187;
    p_fExpected[2] = 17;
    p_fExpected[3] = 27;
    p_fExpected[4] = 31.70333187;
    p_fExpected[5] = 47;
    p_fExpected[6] = 17;
    p_fExpected[7] = 5.703331871;
    p_fExpected[8] = 6;
    p_fExpected[9] = 12.4977377;
    p_fExpected[10] = 11.9977377;
    p_fExpected[11] = 15.0203543;
    p_fExpected[12] = 25.13943315;
    p_fExpected[13] = 31.4977377;
    p_fExpected[14] = 45.0203543;
    p_fExpected[15] = 15.13943315;
    p_fExpected[16] = 5.497737701;
    p_fExpected[17] = 4.020354304;

    for (i = 0; i < 18; i++) {
      p_oTargetTree[i]->GetValue(p_oPop->GetDbhCode(p_oTargetTree[i]->GetSpecies(),
          p_oTargetTree[i]->GetType()), &fDiam);
      EXPECT_LT(fabs(fDiam - p_fExpected[i])/fDiam, 0.001);
    }

    //-----------------------------------------------------------------------//
    // Timestep 3
    //-----------------------------------------------------------------------//
    p_oSimManager->RunSim(1);

    //----- Check diameter --------------------------------------------------//
    p_fExpected[0] = 13.55574034;
    p_fExpected[1] = 13.05574034;
    p_fExpected[2] = 18;
    p_fExpected[3] = 28;
    p_fExpected[4] = 32.55574034;
    p_fExpected[5] = 48;
    p_fExpected[6] = 18;
    p_fExpected[7] = 6.555740342;
    p_fExpected[8] = 7;
    p_fExpected[9] = 13.25123498;
    p_fExpected[10] = 12.75123498;
    p_fExpected[11] = 15.0304865;
    p_fExpected[12] = 25.20926962;
    p_fExpected[13] = 32.25123498;
    p_fExpected[14] = 45.0304865;
    p_fExpected[15] = 15.20926962;
    p_fExpected[16] = 6.251234981;
    p_fExpected[17] = 4.030486504;

    for (i = 0; i < 18; i++) {
      p_oTargetTree[i]->GetValue(p_oPop->GetDbhCode(p_oTargetTree[i]->GetSpecies(),
          p_oTargetTree[i]->GetType()), &fDiam);
      EXPECT_LT(fabs(fDiam - p_fExpected[i])/fDiam, 0.001);
    }

    //-----------------------------------------------------------------------//
    // Timestep 4
    //-----------------------------------------------------------------------//
    p_oSimManager->RunSim(1);

    //----- Check diameter --------------------------------------------------//
    p_fExpected[0] = 14.4033669;
    p_fExpected[1] = 13.9033669;
    p_fExpected[2] = 19;
    p_fExpected[3] = 29;
    p_fExpected[4] = 33.4033669;
    p_fExpected[5] = 49;
    p_fExpected[6] = 19;
    p_fExpected[7] = 7.403366901;
    p_fExpected[8] = 8;
    p_fExpected[9] = 14.05598424;
    p_fExpected[10] = 13.55598424;
    p_fExpected[11] = 15.0421547;
    p_fExpected[12] = 25.27953663;
    p_fExpected[13] = 33.05598424;
    p_fExpected[14] = 45.0421547;
    p_fExpected[15] = 15.27953663;
    p_fExpected[16] = 7.055984241;
    p_fExpected[17] = 4.0421547;

    for (i = 0; i < 18; i++) {
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
TEST(NCIDoubleNoLocalDiffClimateGrowth, TestRun2) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTree **p_oTargetTree = new clTree*[9];
    float *p_fExpected = new float[9];
    float fDiam;
    int iSpecies, i;


    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile(WriteNCIDoubleNoLocalDiffClimateGrowthXMLFile2());
    p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject(
        "treepopulation");

    //Create our trees
    i = 0;
    fDiam = 11;
    iSpecies = 1;
    p_oTargetTree[i] = p_oPop->CreateTree(10, 10, iSpecies,
        clTreePopulation::adult, fDiam);

    i++;
    fDiam = 10.5;
    iSpecies = 1;
    p_oTargetTree[i] = p_oPop->CreateTree(50, 50, iSpecies,
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
    fDiam = 30;
    iSpecies = 1;
    p_oTargetTree[i] = p_oPop->CreateTree(50, 59, iSpecies,
        clTreePopulation::adult, fDiam);

    i++;
    fDiam = 45;
    iSpecies = 2;
    p_oTargetTree[i] = p_oPop->CreateTree(55, 55, iSpecies,
        clTreePopulation::adult, fDiam);

    i++;
    fDiam = 15;
    iSpecies = 3;
    p_oTargetTree[i] = p_oPop->CreateTree(60, 61, iSpecies,
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



    //-----------------------------------------------------------------------//
    // Timestep 1
    //-----------------------------------------------------------------------//
    p_oSimManager->RunSim(1);

    //----- Check diameter --------------------------------------------------//
    p_fExpected[0] = 11.27639764;
    p_fExpected[1] = 10.77639764;
    p_fExpected[2] = 15.00390323;
    p_fExpected[3] = 25.64042174;
    p_fExpected[4] = 30.27639764;
    p_fExpected[5] = 45.00390323;
    p_fExpected[6] = 15.64042174;
    p_fExpected[7] = 4.607242925;
    p_fExpected[8] = 4.010205876;

    for (i = 0; i < 9; i++) {
      p_oTargetTree[i]->GetValue(p_oPop->GetDbhCode(p_oTargetTree[i]->GetSpecies(),
          p_oTargetTree[i]->GetType()), &fDiam);
      EXPECT_LT(fabs(fDiam - p_fExpected[i])/fDiam, 0.001);
    }

    //-----------------------------------------------------------------------//
    // Timestep 2
    //-----------------------------------------------------------------------//
    p_oSimManager->RunSim(1);

    //----- Check diameter --------------------------------------------------//
    p_fExpected[0] = 11.55220783;
    p_fExpected[1] = 11.05220783;
    p_fExpected[2] = 15.00781748;
    p_fExpected[3] = 26.2807223;
    p_fExpected[4] = 30.55220783;
    p_fExpected[5] = 45.00781748;
    p_fExpected[6] = 16.2807223;
    p_fExpected[7] = 5.21343581;
    p_fExpected[8] = 4.020354304;

    for (i = 0; i < 9; i++) {
      p_oTargetTree[i]->GetValue(p_oPop->GetDbhCode(p_oTargetTree[i]->GetSpecies(),
          p_oTargetTree[i]->GetType()), &fDiam);
      EXPECT_LT(fabs(fDiam - p_fExpected[i])/fDiam, 0.001);
    }

    //-----------------------------------------------------------------------//
    // Timestep 3
    //-----------------------------------------------------------------------//
    p_oSimManager->RunSim(1);

    //----- Check diameter --------------------------------------------------//
    p_fExpected[0] = 11.82836768;
    p_fExpected[1] = 11.32836768;
    p_fExpected[2] = 15.01178254;
    p_fExpected[3] = 26.93050075;
    p_fExpected[4] = 30.82836768;
    p_fExpected[5] = 45.01178254;
    p_fExpected[6] = 16.93050075;
    p_fExpected[7] = 5.823150159;
    p_fExpected[8] = 4.030486504;

    for (i = 0; i < 9; i++) {
      p_oTargetTree[i]->GetValue(p_oPop->GetDbhCode(p_oTargetTree[i]->GetSpecies(),
          p_oTargetTree[i]->GetType()), &fDiam);
      EXPECT_LT(fabs(fDiam - p_fExpected[i])/fDiam, 0.001);
    }

    //-----------------------------------------------------------------------//
    // Timestep 4
    //-----------------------------------------------------------------------//
    p_oSimManager->RunSim(1);

    //----- Check diameter --------------------------------------------------//
    p_fExpected[0] = 12.09948714;
    p_fExpected[1] = 11.59948714;
    p_fExpected[2] = 15.01583689;
    p_fExpected[3] = 27.61420263;
    p_fExpected[4] = 31.09948714;
    p_fExpected[5] = 45.01583689;
    p_fExpected[6] = 17.61420263;
    p_fExpected[7] = 6.457969645;
    p_fExpected[8] = 4.0421547;

    for (i = 0; i < 9; i++) {
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
// TestRun3()
////////////////////////////////////////////////////////////////////////////
TEST(NCIDoubleNoLocalDiffClimateGrowth, TestRun3) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTreeSearch *p_oTrees;
    clTree *p_oTree;
    float *p_fMean = new float[15], *p_fSD = new float[15];
    float fDiam, fGrowth;
    int *p_iCount = new int[15];
    int iSpecies, i;


    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile(WriteNCIDoubleNoLocalDiffClimateGrowthXMLFile3());
    p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject(
        "treepopulation");

    //Create our trees: 1000 of each species. Size doesn't matter, there's no
    //size effect
    fDiam = 11;
    for (iSpecies = 0; iSpecies < 15; iSpecies++) {
      for (i = 0; i < 1000; i++) {
        p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
      }
    }

    // Timestep 1
    p_oSimManager->RunSim(1);

    //-----------------------------------------------------------------------//
    // Calculate mean
    //-----------------------------------------------------------------------//
    for (i = 0; i < 16; i++) {
      p_fMean[i] = 0;
      p_fSD[i] = 0;
      p_iCount[i] = 0;
    }

    p_oTrees = p_oPop->Find("all");
    p_oTree = p_oTrees->NextTree();
    while (p_oTree) {

      //----- Get the value for growth, in mm -------------------------------//
      p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(),
                                           p_oTree->GetType()), &fGrowth);

      //----- To cm, and add it up ------------------------------------------//
      p_fMean[p_oTree->GetSpecies()] += (fGrowth - fDiam);
      p_iCount[p_oTree->GetSpecies()]++;

      p_oTree = p_oTrees->NextTree();
    }

    for (i = 0; i < 15; i++) {
      ASSERT_EQ(1000, p_iCount[i]);
    }

    //----- Calculate mean --------------------------------------------------//
    for (i = 0; i < 16; i++) {
      p_fMean[i] /= p_iCount[i];
    }

    //-----------------------------------------------------------------------//
    // Calculate sd
    //-----------------------------------------------------------------------//
    p_oTrees = p_oPop->Find("all");
    p_oTree = p_oTrees->NextTree();
    while (p_oTree) {

      //----- Get the value for growth --------------------------------------//
      p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(),
                                                 p_oTree->GetType()), &fGrowth);
      fGrowth -= fDiam;

      //----- The sd calc ---------------------------------------------------//
      fGrowth -= p_fMean[p_oTree->GetSpecies()];
      fGrowth = fabs(fGrowth);
      p_fSD[p_oTree->GetSpecies()] += fGrowth*fGrowth;

      p_oTree = p_oTrees->NextTree();
    }

    for (i = 0; i < 15; i++) {
      p_fSD[i] /= p_iCount[i];
      p_fSD[i] = sqrt(p_fSD[i]);
    }

    //-----------------------------------------------------------------------//
    // Check results
    //-----------------------------------------------------------------------//
    EXPECT_LT(fabs(p_fMean[0]  - 10.33)/p_fMean[0] , 0.1);
    EXPECT_LT(fabs(p_fMean[1]  - 2.61 )/p_fMean[1] , 0.1);
    EXPECT_LT(fabs(p_fMean[2]  - 2.32 )/p_fMean[2] , 0.1);
    EXPECT_LT(fabs(p_fMean[3]  - 2.17 )/p_fMean[3] , 0.1);
    EXPECT_LT(fabs(p_fMean[4]  - 10.2 )/p_fMean[4] , 0.1);
    EXPECT_LT(fabs(p_fMean[5]  - 8.57 )/p_fMean[5] , 0.1);
    EXPECT_LT(fabs(p_fMean[6]  - 3.73 )/p_fMean[6] , 0.1);
    EXPECT_LT(fabs(p_fMean[7]  - 10.53)/p_fMean[7] , 0.1);
    EXPECT_LT(fabs(p_fMean[8]  - 5.15 )/p_fMean[8] , 0.1);
    EXPECT_LT(fabs(p_fMean[9]  - 1.24 )/p_fMean[9] , 0.1);
    EXPECT_LT(fabs(p_fMean[10] - 7.61 )/p_fMean[10], 0.1);
    EXPECT_LT(fabs(p_fMean[11] - 5.33 )/p_fMean[11], 0.1);
    EXPECT_LT(fabs(p_fMean[12] - 10.15)/p_fMean[12], 0.1);
    EXPECT_LT(fabs(p_fMean[13] - 2.54 )/p_fMean[13], 0.1);
    EXPECT_LT(fabs(p_fMean[14] - 3.84 )/p_fMean[14], 0.1);

    EXPECT_LT(fabs(p_fSD[0]  - 3.121232954)/p_fSD[0] , 0.16);
    EXPECT_LT(fabs(p_fSD[1]  - 1.735385387)/p_fSD[1] , 0.16);
    EXPECT_LT(fabs(p_fSD[2]  - 1.41801069 )/p_fSD[2] , 0.16);
    EXPECT_LT(fabs(p_fSD[3]  - 1.227998749)/p_fSD[3] , 0.16);
    EXPECT_LT(fabs(p_fSD[4]  - 5.139264775)/p_fSD[4] , 0.16);
    EXPECT_LT(fabs(p_fSD[5]  - 2.988367301)/p_fSD[5] , 0.16);
    EXPECT_LT(fabs(p_fSD[6]  - 1.926222992)/p_fSD[6] , 0.16);
    EXPECT_LT(fabs(p_fSD[7]  - 7.261731735)/p_fSD[7] , 0.16);
    EXPECT_LT(fabs(p_fSD[8]  - 2.313112789)/p_fSD[8] , 0.16);
    EXPECT_LT(fabs(p_fSD[9]  - 0.820153422)/p_fSD[9] , 0.16);
    EXPECT_LT(fabs(p_fSD[10] - 6.865953308)/p_fSD[10], 0.16);
    EXPECT_LT(fabs(p_fSD[11] - 2.352311954)/p_fSD[11], 0.16);
    EXPECT_LT(fabs(p_fSD[12] - 4.417110283)/p_fSD[12], 0.16);
    EXPECT_LT(fabs(p_fSD[13] - 1.458415671)/p_fSD[13], 0.16);
    EXPECT_LT(fabs(p_fSD[14] - 2.602503471)/p_fSD[14], 0.16);



    delete[] p_fMean;
    delete[] p_fSD;
    delete[] p_iCount;
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIDoubleNoLocalDiffClimateGrowthXMLFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIDoubleNoLocalDiffClimateGrowthXMLFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  int i;

  //Write file
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
      << "</allometry>"
      << "<behaviorList>"
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

      << "<sc_ciMonthlyTempJan>"
      << "<sc_cimtjanVal ts=\"1\">-2.57</sc_cimtjanVal>"
      << "<sc_cimtjanVal ts=\"2\">-3.46</sc_cimtjanVal>"
      << "<sc_cimtjanVal ts=\"3\">-6.93</sc_cimtjanVal>"
      << "<sc_cimtjanVal ts=\"4\">-7.76</sc_cimtjanVal>"
      << "<sc_cimtjanVal ts=\"5\">-0.72</sc_cimtjanVal>"
      << "<sc_cimtjanVal ts=\"6\">1.3</sc_cimtjanVal>"
      << "</sc_ciMonthlyTempJan>"

      << "<sc_ciMonthlyTempFeb>"
      << "<sc_cimtfebVal ts=\"1\">2.75</sc_cimtfebVal>"
      << "<sc_cimtfebVal ts=\"2\">-8.57</sc_cimtfebVal>"
      << "<sc_cimtfebVal ts=\"3\">1.98</sc_cimtfebVal>"
      << "<sc_cimtfebVal ts=\"4\">-7.5</sc_cimtfebVal>"
      << "<sc_cimtfebVal ts=\"5\">-2.44</sc_cimtfebVal>"
      << "<sc_cimtfebVal ts=\"6\">-9.36</sc_cimtfebVal>"
      << "</sc_ciMonthlyTempFeb>"

      << "<sc_ciMonthlyTempMar>"
      << "<sc_cimtmarVal ts=\"1\">2.94</sc_cimtmarVal>"
      << "<sc_cimtmarVal ts=\"2\">0.28</sc_cimtmarVal>"
      << "<sc_cimtmarVal ts=\"3\">0.3</sc_cimtmarVal>"
      << "<sc_cimtmarVal ts=\"4\">-0.78</sc_cimtmarVal>"
      << "<sc_cimtmarVal ts=\"5\">4.85</sc_cimtmarVal>"
      << "<sc_cimtmarVal ts=\"6\">3.78</sc_cimtmarVal>"
      << "</sc_ciMonthlyTempMar>"

      << "<sc_ciMonthlyTempApr>"
      << "<sc_cimtaprVal ts=\"1\">2.17</sc_cimtaprVal>"
      << "<sc_cimtaprVal ts=\"2\">5.9</sc_cimtaprVal>"
      << "<sc_cimtaprVal ts=\"3\">7.17</sc_cimtaprVal>"
      << "<sc_cimtaprVal ts=\"4\">8.67</sc_cimtaprVal>"
      << "<sc_cimtaprVal ts=\"5\">5.61</sc_cimtaprVal>"
      << "<sc_cimtaprVal ts=\"6\">4.56</sc_cimtaprVal>"
      << "</sc_ciMonthlyTempApr>"

      << "<sc_ciMonthlyTempMay>"
      << "<sc_cimtmayVal ts=\"1\">7.25</sc_cimtmayVal>"
      << "<sc_cimtmayVal ts=\"2\">7.6</sc_cimtmayVal>"
      << "<sc_cimtmayVal ts=\"3\">9.46</sc_cimtmayVal>"
      << "<sc_cimtmayVal ts=\"4\">11.26</sc_cimtmayVal>"
      << "<sc_cimtmayVal ts=\"5\">7.6</sc_cimtmayVal>"
      << "<sc_cimtmayVal ts=\"6\">6.9</sc_cimtmayVal>"
      << "</sc_ciMonthlyTempMay>"

      << "<sc_ciMonthlyTempJun>"
      << "<sc_cimtjunVal ts=\"1\">11.05</sc_cimtjunVal>"
      << "<sc_cimtjunVal ts=\"2\">17.16</sc_cimtjunVal>"
      << "<sc_cimtjunVal ts=\"3\">11.06</sc_cimtjunVal>"
      << "<sc_cimtjunVal ts=\"4\">17.72</sc_cimtjunVal>"
      << "<sc_cimtjunVal ts=\"5\">14.05</sc_cimtjunVal>"
      << "<sc_cimtjunVal ts=\"6\">13.52</sc_cimtjunVal>"
      << "</sc_ciMonthlyTempJun>"

      << "<sc_ciMonthlyTempJul>"
      << "<sc_cimtjulVal ts=\"1\">16.82</sc_cimtjulVal>"
      << "<sc_cimtjulVal ts=\"2\">22</sc_cimtjulVal>"
      << "<sc_cimtjulVal ts=\"3\">18.34</sc_cimtjulVal>"
      << "<sc_cimtjulVal ts=\"4\">20.99</sc_cimtjulVal>"
      << "<sc_cimtjulVal ts=\"5\">15.46</sc_cimtjulVal>"
      << "<sc_cimtjulVal ts=\"6\">15.74</sc_cimtjulVal>"
      << "</sc_ciMonthlyTempJul>"

      << "<sc_ciMonthlyTempAug>"
      << "<sc_cimtaugVal ts=\"1\">18.32</sc_cimtaugVal>"
      << "<sc_cimtaugVal ts=\"2\">15.97</sc_cimtaugVal>"
      << "<sc_cimtaugVal ts=\"3\">17.54</sc_cimtaugVal>"
      << "<sc_cimtaugVal ts=\"4\">17.46</sc_cimtaugVal>"
      << "<sc_cimtaugVal ts=\"5\">16.69</sc_cimtaugVal>"
      << "<sc_cimtaugVal ts=\"6\">17.48</sc_cimtaugVal>"
      << "</sc_ciMonthlyTempAug>"

      << "<sc_ciMonthlyTempSep>"
      << "<sc_cimtsepVal ts=\"1\">22.73</sc_cimtsepVal>"
      << "<sc_cimtsepVal ts=\"2\">20.94</sc_cimtsepVal>"
      << "<sc_cimtsepVal ts=\"3\">15.94</sc_cimtsepVal>"
      << "<sc_cimtsepVal ts=\"4\">18.87</sc_cimtsepVal>"
      << "<sc_cimtsepVal ts=\"5\">22.85</sc_cimtsepVal>"
      << "<sc_cimtsepVal ts=\"6\">19.53</sc_cimtsepVal>"
      << "</sc_ciMonthlyTempSep>"

      << "<sc_ciMonthlyTempOct>"
      << "<sc_cimtoctVal ts=\"1\">7.92</sc_cimtoctVal>"
      << "<sc_cimtoctVal ts=\"2\">8.18</sc_cimtoctVal>"
      << "<sc_cimtoctVal ts=\"3\">8.43</sc_cimtoctVal>"
      << "<sc_cimtoctVal ts=\"4\">8.68</sc_cimtoctVal>"
      << "<sc_cimtoctVal ts=\"5\">8.94</sc_cimtoctVal>"
      << "<sc_cimtoctVal ts=\"6\">9.19</sc_cimtoctVal>"
      << "</sc_ciMonthlyTempOct>"

      << "<sc_ciMonthlyTempNov>"
      << "<sc_cimtnovVal ts=\"1\">2.48</sc_cimtnovVal>"
      << "<sc_cimtnovVal ts=\"2\">2.56</sc_cimtnovVal>"
      << "<sc_cimtnovVal ts=\"3\">2.64</sc_cimtnovVal>"
      << "<sc_cimtnovVal ts=\"4\">2.72</sc_cimtnovVal>"
      << "<sc_cimtnovVal ts=\"5\">2.8</sc_cimtnovVal>"
      << "<sc_cimtnovVal ts=\"6\">2.88</sc_cimtnovVal>"
      << "</sc_ciMonthlyTempNov>"

      << "<sc_ciMonthlyTempDec>"
      << "<sc_cimtdecVal ts=\"1\">-9.6</sc_cimtdecVal>"
      << "<sc_cimtdecVal ts=\"2\">-6.94</sc_cimtdecVal>"
      << "<sc_cimtdecVal ts=\"3\">-6.51</sc_cimtdecVal>"
      << "<sc_cimtdecVal ts=\"4\">-1.59</sc_cimtdecVal>"
      << "<sc_cimtdecVal ts=\"5\">0.19</sc_cimtdecVal>"
      << "<sc_cimtdecVal ts=\"6\">2.49</sc_cimtdecVal>"
      << "</sc_ciMonthlyTempDec>"

      << "<sc_ciMonthlyPptJan>"
      << "<sc_cimpjanVal ts=\"1\">161.48</sc_cimpjanVal>"
      << "<sc_cimpjanVal ts=\"2\">152.09</sc_cimpjanVal>"
      << "<sc_cimpjanVal ts=\"3\">152.5</sc_cimpjanVal>"
      << "<sc_cimpjanVal ts=\"4\">152.71</sc_cimpjanVal>"
      << "<sc_cimpjanVal ts=\"5\">78.44</sc_cimpjanVal>"
      << "<sc_cimpjanVal ts=\"6\">123.19</sc_cimpjanVal>"
      << "</sc_ciMonthlyPptJan>"

      << "<sc_ciMonthlyPptFeb>"
      << "<sc_cimpfebVal ts=\"1\">199.32</sc_cimpfebVal>"
      << "<sc_cimpfebVal ts=\"2\">192.94</sc_cimpfebVal>"
      << "<sc_cimpfebVal ts=\"3\">188.1</sc_cimpfebVal>"
      << "<sc_cimpfebVal ts=\"4\">153.95</sc_cimpfebVal>"
      << "<sc_cimpfebVal ts=\"5\">89.79</sc_cimpfebVal>"
      << "<sc_cimpfebVal ts=\"6\">189.67</sc_cimpfebVal>"
      << "</sc_ciMonthlyPptFeb>"

      << "<sc_ciMonthlyPptMar>"
      << "<sc_cimpmarVal ts=\"1\">169.99</sc_cimpmarVal>"
      << "<sc_cimpmarVal ts=\"2\">105.49</sc_cimpmarVal>"
      << "<sc_cimpmarVal ts=\"3\">141.34</sc_cimpmarVal>"
      << "<sc_cimpmarVal ts=\"4\">84.71</sc_cimpmarVal>"
      << "<sc_cimpmarVal ts=\"5\">188.92</sc_cimpmarVal>"
      << "<sc_cimpmarVal ts=\"6\">93.47</sc_cimpmarVal>"
      << "</sc_ciMonthlyPptMar>"

      << "<sc_ciMonthlyPptApr>"
      << "<sc_cimpaprVal ts=\"1\">82.02</sc_cimpaprVal>"
      << "<sc_cimpaprVal ts=\"2\">77.49</sc_cimpaprVal>"
      << "<sc_cimpaprVal ts=\"3\">186.32</sc_cimpaprVal>"
      << "<sc_cimpaprVal ts=\"4\">174.4</sc_cimpaprVal>"
      << "<sc_cimpaprVal ts=\"5\">161.25</sc_cimpaprVal>"
      << "<sc_cimpaprVal ts=\"6\">99.76</sc_cimpaprVal>"
      << "</sc_ciMonthlyPptApr>"

      << "<sc_ciMonthlyPptMay>"
      << "<sc_cimpmayVal ts=\"1\">132.54</sc_cimpmayVal>"
      << "<sc_cimpmayVal ts=\"2\">121.74</sc_cimpmayVal>"
      << "<sc_cimpmayVal ts=\"3\">178.18</sc_cimpmayVal>"
      << "<sc_cimpmayVal ts=\"4\">102.86</sc_cimpmayVal>"
      << "<sc_cimpmayVal ts=\"5\">102.84</sc_cimpmayVal>"
      << "<sc_cimpmayVal ts=\"6\">172.41</sc_cimpmayVal>"
      << "</sc_ciMonthlyPptMay>"

      << "<sc_ciMonthlyPptJun>"
      << "<sc_cimpjunVal ts=\"1\">157.67</sc_cimpjunVal>"
      << "<sc_cimpjunVal ts=\"2\">133.89</sc_cimpjunVal>"
      << "<sc_cimpjunVal ts=\"3\">147.29</sc_cimpjunVal>"
      << "<sc_cimpjunVal ts=\"4\">123.74</sc_cimpjunVal>"
      << "<sc_cimpjunVal ts=\"5\">126.66</sc_cimpjunVal>"
      << "<sc_cimpjunVal ts=\"6\">134.35</sc_cimpjunVal>"
      << "</sc_ciMonthlyPptJun>"

      << "<sc_ciMonthlyPptJul>"
      << "<sc_cimpjulVal ts=\"1\">97.63</sc_cimpjulVal>"
      << "<sc_cimpjulVal ts=\"2\">141.94</sc_cimpjulVal>"
      << "<sc_cimpjulVal ts=\"3\">173.88</sc_cimpjulVal>"
      << "<sc_cimpjulVal ts=\"4\">166.53</sc_cimpjulVal>"
      << "<sc_cimpjulVal ts=\"5\">140.41</sc_cimpjulVal>"
      << "<sc_cimpjulVal ts=\"6\">128.89</sc_cimpjulVal>"
      << "</sc_ciMonthlyPptJul>"

      << "<sc_ciMonthlyPptAug>"
      << "<sc_cimpaugVal ts=\"1\">145.57</sc_cimpaugVal>"
      << "<sc_cimpaugVal ts=\"2\">156.69</sc_cimpaugVal>"
      << "<sc_cimpaugVal ts=\"3\">146.55</sc_cimpaugVal>"
      << "<sc_cimpaugVal ts=\"4\">167.73</sc_cimpaugVal>"
      << "<sc_cimpaugVal ts=\"5\">147.67</sc_cimpaugVal>"
      << "<sc_cimpaugVal ts=\"6\">119.52</sc_cimpaugVal>"
      << "</sc_ciMonthlyPptAug>"

      << "<sc_ciMonthlyPptSep>"
      << "<sc_cimpsepVal ts=\"1\">134.38</sc_cimpsepVal>"
      << "<sc_cimpsepVal ts=\"2\">89.78</sc_cimpsepVal>"
      << "<sc_cimpsepVal ts=\"3\">173.37</sc_cimpsepVal>"
      << "<sc_cimpsepVal ts=\"4\">146.16</sc_cimpsepVal>"
      << "<sc_cimpsepVal ts=\"5\">108.71</sc_cimpsepVal>"
      << "<sc_cimpsepVal ts=\"6\">90.68</sc_cimpsepVal>"
      << "</sc_ciMonthlyPptSep>"

      << "<sc_ciMonthlyPptOct>"
      << "<sc_cimpoctVal ts=\"1\">100.17</sc_cimpoctVal>"
      << "<sc_cimpoctVal ts=\"2\">178.11</sc_cimpoctVal>"
      << "<sc_cimpoctVal ts=\"3\">120.16</sc_cimpoctVal>"
      << "<sc_cimpoctVal ts=\"4\">198.43</sc_cimpoctVal>"
      << "<sc_cimpoctVal ts=\"5\">75.22</sc_cimpoctVal>"
      << "<sc_cimpoctVal ts=\"6\">198.3</sc_cimpoctVal>"
      << "</sc_ciMonthlyPptOct>"

      << "<sc_ciMonthlyPptNov>"
      << "<sc_cimpnovVal ts=\"1\">112.34</sc_cimpnovVal>"
      << "<sc_cimpnovVal ts=\"2\">191.22</sc_cimpnovVal>"
      << "<sc_cimpnovVal ts=\"3\">125.47</sc_cimpnovVal>"
      << "<sc_cimpnovVal ts=\"4\">79.8</sc_cimpnovVal>"
      << "<sc_cimpnovVal ts=\"5\">116.29</sc_cimpnovVal>"
      << "<sc_cimpnovVal ts=\"6\">146.75</sc_cimpnovVal>"
      << "</sc_ciMonthlyPptNov>"

      << "<sc_ciMonthlyPptDec>"
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
      << "<nciWhichPrecipitationEffect>" << double_no_local_diff_precip_effect << "</nciWhichPrecipitationEffect>"
      << "<nciWhichTemperatureEffect>" << no_temp_effect << "</nciWhichTemperatureEffect>"
      << "<nciWhichNitrogenEffect>" << no_nitrogen_effect << "</nciWhichNitrogenEffect>"
      << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
      << "<gr_stochGrowthMethod>" << deterministic_pdf << "</gr_stochGrowthMethod>"
      << "<gr_nciMaxPotentialGrowth>"
      << "<gr_nmpgVal species=\"Species_2\">1</gr_nmpgVal>"
      << "<gr_nmpgVal species=\"Species_3\">1</gr_nmpgVal>"
      << "<gr_nmpgVal species=\"Species_4\">1</gr_nmpgVal>"
      << "</gr_nciMaxPotentialGrowth>"
      << "<nciDoubNoLocPrecipEffCurrA>"
      << "<ndnlpecaVal species=\"Species_2\">0.001765319</ndnlpecaVal>"
      << "<ndnlpecaVal species=\"Species_3\">1</ndnlpecaVal>"
      << "<ndnlpecaVal species=\"Species_4\">0.9597078</ndnlpecaVal>"
      << "</nciDoubNoLocPrecipEffCurrA>"
      << "<nciDoubNoLocPrecipEffCurrBLo>"
      << "<ndnlpecblVal species=\"Species_2\">0.9139451</ndnlpecblVal>"
      << "<ndnlpecblVal species=\"Species_3\">0.9000193</ndnlpecblVal>"
      << "<ndnlpecblVal species=\"Species_4\">0.9352008</ndnlpecblVal>"
      << "</nciDoubNoLocPrecipEffCurrBLo>"
      << "<nciDoubNoLocPrecipEffCurrBHi>"
      << "<ndnlpecbhVal species=\"Species_2\">0.910562</ndnlpecbhVal>"
      << "<ndnlpecbhVal species=\"Species_3\">0.9656258</ndnlpecbhVal>"
      << "<ndnlpecbhVal species=\"Species_4\">0.9316474</ndnlpecbhVal>"
      << "</nciDoubNoLocPrecipEffCurrBHi>"
      << "<nciDoubNoLocPrecipEffCurrC>"
      << "<ndnlpeccVal species=\"Species_2\">0.8712764</ndnlpeccVal>"
      << "<ndnlpeccVal species=\"Species_3\">0.3</ndnlpeccVal>"
      << "<ndnlpeccVal species=\"Species_4\">0.9407407</ndnlpeccVal>"
      << "</nciDoubNoLocPrecipEffCurrC>"
      << "<nciDoubNoLocPrecipEffPrevA>"
      << "<ndnlpepaVal species=\"Species_2\">0.86</ndnlpepaVal>"
      << "<ndnlpepaVal species=\"Species_3\">0.34</ndnlpepaVal>"
      << "<ndnlpepaVal species=\"Species_4\">0.66</ndnlpepaVal>"
      << "</nciDoubNoLocPrecipEffPrevA>"
      << "<nciDoubNoLocPrecipEffPrevBLo>"
      << "<ndnlpepblVal species=\"Species_2\">0.9</ndnlpepblVal>"
      << "<ndnlpepblVal species=\"Species_3\">0.9761828</ndnlpepblVal>"
      << "<ndnlpepblVal species=\"Species_4\">0.9981236</ndnlpepblVal>"
      << "</nciDoubNoLocPrecipEffPrevBLo>"
      << "<nciDoubNoLocPrecipEffPrevBHi>"
      << "<ndnlpepbhVal species=\"Species_2\">0.9657148</ndnlpepbhVal>"
      << "<ndnlpepbhVal species=\"Species_3\">0.9456557</ndnlpepbhVal>"
      << "<ndnlpepbhVal species=\"Species_4\">0.9541563</ndnlpepbhVal>"
      << "</nciDoubNoLocPrecipEffPrevBHi>"
      << "<nciDoubNoLocPrecipEffPrevC>"
      << "<ndnlpepcVal species=\"Species_2\">0.3</ndnlpepcVal>"
      << "<ndnlpepcVal species=\"Species_3\">0.84678993</ndnlpepcVal>"
      << "<ndnlpepcVal species=\"Species_4\">0.89953342</ndnlpepcVal>"
      << "</nciDoubNoLocPrecipEffPrevC>"
      << "<nciDoubNoLocPrecipType>" << clPrecipitationEffectBase::seasonal_precip << "</nciDoubNoLocPrecipType>"
      << "</NCIMasterGrowth2>"

      << "<NCIMasterGrowth3>"
      << "<nciWhichShadingEffect>" << no_shading << "</nciWhichShadingEffect>"
      << "<nciWhichCrowdingEffect>" << no_crowding_effect << "</nciWhichCrowdingEffect>"
      << "<nciWhichNCITerm>" << no_nci_term << "</nciWhichNCITerm>"
      << "<nciWhichSizeEffect>" << no_size_effect << "</nciWhichSizeEffect>"
      << "<nciWhichDamageEffect>" << no_damage_effect << "</nciWhichDamageEffect>"
      << "<nciWhichPrecipitationEffect>" << no_precip_effect << "</nciWhichPrecipitationEffect>"
      << "<nciWhichTemperatureEffect>" << double_no_local_diff_temp_effect << "</nciWhichTemperatureEffect>"
      << "<nciWhichNitrogenEffect>" << no_nitrogen_effect << "</nciWhichNitrogenEffect>"
      << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
      << "<gr_stochGrowthMethod>" << deterministic_pdf << "</gr_stochGrowthMethod>"
      << "<gr_nciMaxPotentialGrowth>"
      << "<gr_nmpgVal species=\"Species_5\">1</gr_nmpgVal>"
      << "<gr_nmpgVal species=\"Species_6\">1</gr_nmpgVal>"
      << "<gr_nmpgVal species=\"Species_7\">1</gr_nmpgVal>"
      << "</gr_nciMaxPotentialGrowth>"
      << "<nciDoubNoLocTempEffCurrA>"
      << "<ndnltecaVal species=\"Species_5\">0.7789208</ndnltecaVal>"
      << "<ndnltecaVal species=\"Species_6\">0.008861627</ndnltecaVal>"
      << "<ndnltecaVal species=\"Species_7\">0.06436607</ndnltecaVal>"
      << "</nciDoubNoLocTempEffCurrA>"
      << "<nciDoubNoLocTempEffCurrBLo>"
      << "<ndnltecblVal species=\"Species_5\">0.9738308</ndnltecblVal>"
      << "<ndnltecblVal species=\"Species_6\">0.9</ndnltecblVal>"
      << "<ndnltecblVal species=\"Species_7\">0.9</ndnltecblVal>"
      << "</nciDoubNoLocTempEffCurrBLo>"
      << "<nciDoubNoLocTempEffCurrBHi>"
      << "<ndnltecbhVal species=\"Species_5\">0.9736826</ndnltecbhVal>"
      << "<ndnltecbhVal species=\"Species_6\">1</ndnltecbhVal>"
      << "<ndnltecbhVal species=\"Species_7\">1</ndnltecbhVal>"
      << "</nciDoubNoLocTempEffCurrBHi>"
      << "<nciDoubNoLocTempEffCurrC>"
      << "<ndnlteccVal species=\"Species_5\">17.24231</ndnlteccVal>"
      << "<ndnlteccVal species=\"Species_6\">11.21695</ndnlteccVal>"
      << "<ndnlteccVal species=\"Species_7\">6.21471</ndnlteccVal>"
      << "</nciDoubNoLocTempEffCurrC>"
      << "<nciDoubNoLocTempEffPrevA>"
      << "<ndnltepaVal species=\"Species_5\">0.85</ndnltepaVal>"
      << "<ndnltepaVal species=\"Species_6\">0.77</ndnltepaVal>"
      << "<ndnltepaVal species=\"Species_7\">0.45</ndnltepaVal>"
      << "</nciDoubNoLocTempEffPrevA>"
      << "<nciDoubNoLocTempEffPrevBLo>"
      << "<ndnltepblVal species=\"Species_5\">1</ndnltepblVal>"
      << "<ndnltepblVal species=\"Species_6\">0.9188785</ndnltepblVal>"
      << "<ndnltepblVal species=\"Species_7\">0.9006845</ndnltepblVal>"
      << "</nciDoubNoLocTempEffPrevBLo>"
      << "<nciDoubNoLocTempEffPrevBHi>"
      << "<ndnltepbhVal species=\"Species_5\">0.9166126</ndnltepbhVal>"
      << "<ndnltepbhVal species=\"Species_6\">0.9934763</ndnltepbhVal>"
      << "<ndnltepbhVal species=\"Species_7\">0.990283</ndnltepbhVal>"
      << "</nciDoubNoLocTempEffPrevBHi>"
      << "<nciDoubNoLocTempEffPrevC>"
      << "<ndnltepcVal species=\"Species_5\">5.389124</ndnltepcVal>"
      << "<ndnltepcVal species=\"Species_6\">-19.21351</ndnltepcVal>"
      << "<ndnltepcVal species=\"Species_7\">-14.44979</ndnltepcVal>"
      << "</nciDoubNoLocTempEffPrevC>"
      << "</NCIMasterGrowth3>"
      << "</paramFile>";
  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIDoubleNoLocalDiffClimateGrowthXMLFile2()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIDoubleNoLocalDiffClimateGrowthXMLFile2() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  int i;

  //Write file
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
  for (i = 1; i < 5; i++) {
    oOut << "<tr_species speciesName=\"Species_" << i << "\" />";
  }
  oOut << "</tr_speciesList>"
      << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
      << "<tr_minAdultDBH>";
  for (i = 1; i < 5; i++) {
    oOut << "<tr_madVal species=\"Species_" << i << "\">10.0</tr_madVal>";
  }
  oOut << "</tr_minAdultDBH>"
      << "<tr_maxSeedlingHeight>";
  for (i = 1; i < 5; i++) {
    oOut << "<tr_mshVal species=\"Species_" << i << "\">1.35</tr_mshVal>";
  }
  oOut << "</tr_maxSeedlingHeight>"
      << "</trees>"
      << "<allometry>"
      << "<tr_canopyHeight>";
  for (i = 1; i < 5; i++) {
    oOut << "<tr_chVal species=\"Species_" << i << "\">39.48</tr_chVal>";
  }
  oOut << "</tr_canopyHeight>"
      << "<tr_stdAsympCrownRad>";
  for (i = 1; i < 5; i++) {
    oOut << "<tr_sacrVal species=\"Species_" << i << "\">0.0549</tr_sacrVal>";
  }
  oOut << "</tr_stdAsympCrownRad>"
      << "<tr_stdCrownRadExp>";
  for (i = 1; i < 5; i++) {
    oOut << "<tr_screVal species=\"Species_" << i << "\">1.0</tr_screVal>";
  }
  oOut << "</tr_stdCrownRadExp>"
      << "<tr_stdMaxCrownRad>";
  for (i = 1; i < 5; i++) {
    oOut << "<tr_smcrVal species=\"Species_" << i << "\">10</tr_smcrVal>";
  }
  oOut  << "</tr_stdMaxCrownRad>"
      << "<tr_conversionDiam10ToDBH>";
  for (i = 1; i < 5; i++) {
    oOut << "<tr_cdtdVal species=\"Species_" << i << "\">1</tr_cdtdVal>";
  }
  oOut << "</tr_conversionDiam10ToDBH>"
      << "<tr_interceptDiam10ToDBH>";
  for (i = 1; i < 5; i++) {
    oOut << "<tr_idtdVal species=\"Species_" << i << "\">0</tr_idtdVal>";
  }
  oOut << "</tr_interceptDiam10ToDBH>"
      << "<tr_stdAsympCrownHt>";
  for (i = 1; i < 5; i++) {
    oOut << "<tr_sachVal species=\"Species_" << i << "\">0.389</tr_sachVal>";
  }
  oOut << "</tr_stdAsympCrownHt>"
      << "<tr_stdCrownHtExp>";
  for (i = 1; i < 5; i++) {
    oOut << "<tr_scheVal species=\"Species_" << i << "\">1.0</tr_scheVal>";
  }
  oOut << "</tr_stdCrownHtExp>"
      << "<tr_slopeOfHeight-Diam10>";
  for (i = 1; i < 5; i++) {
    oOut << "<tr_sohdVal species=\"Species_" << i << "\">0.03418</tr_sohdVal>";
  }
  oOut << "</tr_slopeOfHeight-Diam10>"
      << "<tr_slopeOfAsymHeight>";
  for (i = 1; i < 5; i++) {
    oOut << "<tr_soahVal species=\"Species_" << i << "\">0.0299</tr_soahVal>";
  }
  oOut << "</tr_slopeOfAsymHeight>"
      << "<tr_whatSeedlingHeightDiam>";
  for (i = 1; i < 5; i++) {
    oOut << "<tr_wsehdVal species=\"Species_" << i << "\">0</tr_wsehdVal>";
  }
  oOut << "</tr_whatSeedlingHeightDiam>"
      << "<tr_whatSaplingHeightDiam>";
  for (i = 1; i < 5; i++) {
    oOut << "<tr_wsahdVal species=\"Species_" << i << "\">0</tr_wsahdVal>";
  }
  oOut << "</tr_whatSaplingHeightDiam>"
      << "<tr_whatAdultHeightDiam>";
  for (i = 1; i < 5; i++) {
    oOut << "<tr_wahdVal species=\"Species_" << i << "\">0</tr_wahdVal>";
  }
  oOut << "</tr_whatAdultHeightDiam>"
      << "<tr_whatAdultCrownRadDiam>";
  for (i = 1; i < 5; i++) {
    oOut << "<tr_wacrdVal species=\"Species_" << i << "\">0</tr_wacrdVal>";
  }
  oOut << "</tr_whatAdultCrownRadDiam>"
      << "<tr_whatAdultCrownHeightHeight>";
  for (i = 1; i < 5; i++) {
    oOut << "<tr_wachhVal species=\"Species_" << i << "\">0</tr_wachhVal>";
  }
  oOut << "</tr_whatAdultCrownHeightHeight>"
      << "<tr_whatSaplingCrownRadDiam>";
  for (i = 1; i < 5; i++) {
    oOut << "<tr_wscrdVal species=\"Species_" << i << "\">0</tr_wscrdVal>";
  }
  oOut << "</tr_whatSaplingCrownRadDiam>"
      << "<tr_whatSaplingCrownHeightHeight>";
  for (i = 1; i < 5; i++) {
    oOut << "<tr_wschhVal species=\"Species_" << i << "\">0</tr_wschhVal>";
  }
  oOut << "</tr_whatSaplingCrownHeightHeight>"
      << "</allometry>"
      << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>ClimateImporter</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "</behavior>"

      // First NCI growth behavior: saplings only
      << "<behavior>"
      << "<behaviorName>NCIMasterGrowth</behaviorName>"
      << "<version>3</version>"
      << "<listPosition>2</listPosition>";
  for (i = 2; i < 5; i++) {
    oOut  << "<applyTo species=\"Species_" << i << "\" type=\"Sapling\"/>";
  }
  oOut  << "</behavior>"
      // Second NCI growth behavior: adults only
      << "<behavior>"
      << "<behaviorName>NCIMasterGrowth</behaviorName>"
      << "<version>3</version>"
      << "<listPosition>3</listPosition>";
  for (i = 2; i < 5; i++) {
    oOut  << "<applyTo species=\"Species_" << i << "\" type=\"Adult\"/>";
  }
  oOut  << "</behavior>"
      << "</behaviorList>"
      << "<ClimateImporter1>"
      << "<sc_ciAWS>60.9</sc_ciAWS>"

      << "<sc_ciMonthlyTempJan>"
      << "<sc_cimtjanVal ts=\"1\">-2.57</sc_cimtjanVal>"
      << "<sc_cimtjanVal ts=\"2\">-3.46</sc_cimtjanVal>"
      << "<sc_cimtjanVal ts=\"3\">-6.93</sc_cimtjanVal>"
      << "<sc_cimtjanVal ts=\"4\">-7.76</sc_cimtjanVal>"
      << "<sc_cimtjanVal ts=\"5\">-0.72</sc_cimtjanVal>"
      << "<sc_cimtjanVal ts=\"6\">1.3</sc_cimtjanVal>"
      << "</sc_ciMonthlyTempJan>"

      << "<sc_ciMonthlyTempFeb>"
      << "<sc_cimtfebVal ts=\"1\">2.75</sc_cimtfebVal>"
      << "<sc_cimtfebVal ts=\"2\">-8.57</sc_cimtfebVal>"
      << "<sc_cimtfebVal ts=\"3\">1.98</sc_cimtfebVal>"
      << "<sc_cimtfebVal ts=\"4\">-7.5</sc_cimtfebVal>"
      << "<sc_cimtfebVal ts=\"5\">-2.44</sc_cimtfebVal>"
      << "<sc_cimtfebVal ts=\"6\">-9.36</sc_cimtfebVal>"
      << "</sc_ciMonthlyTempFeb>"

      << "<sc_ciMonthlyTempMar>"
      << "<sc_cimtmarVal ts=\"1\">2.94</sc_cimtmarVal>"
      << "<sc_cimtmarVal ts=\"2\">0.28</sc_cimtmarVal>"
      << "<sc_cimtmarVal ts=\"3\">0.3</sc_cimtmarVal>"
      << "<sc_cimtmarVal ts=\"4\">-0.78</sc_cimtmarVal>"
      << "<sc_cimtmarVal ts=\"5\">4.85</sc_cimtmarVal>"
      << "<sc_cimtmarVal ts=\"6\">3.78</sc_cimtmarVal>"
      << "</sc_ciMonthlyTempMar>"

      << "<sc_ciMonthlyTempApr>"
      << "<sc_cimtaprVal ts=\"1\">2.17</sc_cimtaprVal>"
      << "<sc_cimtaprVal ts=\"2\">5.9</sc_cimtaprVal>"
      << "<sc_cimtaprVal ts=\"3\">7.17</sc_cimtaprVal>"
      << "<sc_cimtaprVal ts=\"4\">8.67</sc_cimtaprVal>"
      << "<sc_cimtaprVal ts=\"5\">5.61</sc_cimtaprVal>"
      << "<sc_cimtaprVal ts=\"6\">4.56</sc_cimtaprVal>"
      << "</sc_ciMonthlyTempApr>"

      << "<sc_ciMonthlyTempMay>"
      << "<sc_cimtmayVal ts=\"1\">7.25</sc_cimtmayVal>"
      << "<sc_cimtmayVal ts=\"2\">7.6</sc_cimtmayVal>"
      << "<sc_cimtmayVal ts=\"3\">9.46</sc_cimtmayVal>"
      << "<sc_cimtmayVal ts=\"4\">11.26</sc_cimtmayVal>"
      << "<sc_cimtmayVal ts=\"5\">7.6</sc_cimtmayVal>"
      << "<sc_cimtmayVal ts=\"6\">6.9</sc_cimtmayVal>"
      << "</sc_ciMonthlyTempMay>"

      << "<sc_ciMonthlyTempJun>"
      << "<sc_cimtjunVal ts=\"1\">11.05</sc_cimtjunVal>"
      << "<sc_cimtjunVal ts=\"2\">17.16</sc_cimtjunVal>"
      << "<sc_cimtjunVal ts=\"3\">11.06</sc_cimtjunVal>"
      << "<sc_cimtjunVal ts=\"4\">17.72</sc_cimtjunVal>"
      << "<sc_cimtjunVal ts=\"5\">14.05</sc_cimtjunVal>"
      << "<sc_cimtjunVal ts=\"6\">13.52</sc_cimtjunVal>"
      << "</sc_ciMonthlyTempJun>"

      << "<sc_ciMonthlyTempJul>"
      << "<sc_cimtjulVal ts=\"1\">16.82</sc_cimtjulVal>"
      << "<sc_cimtjulVal ts=\"2\">22</sc_cimtjulVal>"
      << "<sc_cimtjulVal ts=\"3\">18.34</sc_cimtjulVal>"
      << "<sc_cimtjulVal ts=\"4\">20.99</sc_cimtjulVal>"
      << "<sc_cimtjulVal ts=\"5\">15.46</sc_cimtjulVal>"
      << "<sc_cimtjulVal ts=\"6\">15.74</sc_cimtjulVal>"
      << "</sc_ciMonthlyTempJul>"

      << "<sc_ciMonthlyTempAug>"
      << "<sc_cimtaugVal ts=\"1\">18.32</sc_cimtaugVal>"
      << "<sc_cimtaugVal ts=\"2\">15.97</sc_cimtaugVal>"
      << "<sc_cimtaugVal ts=\"3\">17.54</sc_cimtaugVal>"
      << "<sc_cimtaugVal ts=\"4\">17.46</sc_cimtaugVal>"
      << "<sc_cimtaugVal ts=\"5\">16.69</sc_cimtaugVal>"
      << "<sc_cimtaugVal ts=\"6\">17.48</sc_cimtaugVal>"
      << "</sc_ciMonthlyTempAug>"

      << "<sc_ciMonthlyTempSep>"
      << "<sc_cimtsepVal ts=\"1\">22.73</sc_cimtsepVal>"
      << "<sc_cimtsepVal ts=\"2\">20.94</sc_cimtsepVal>"
      << "<sc_cimtsepVal ts=\"3\">15.94</sc_cimtsepVal>"
      << "<sc_cimtsepVal ts=\"4\">18.87</sc_cimtsepVal>"
      << "<sc_cimtsepVal ts=\"5\">22.85</sc_cimtsepVal>"
      << "<sc_cimtsepVal ts=\"6\">19.53</sc_cimtsepVal>"
      << "</sc_ciMonthlyTempSep>"

      << "<sc_ciMonthlyTempOct>"
      << "<sc_cimtoctVal ts=\"1\">7.92</sc_cimtoctVal>"
      << "<sc_cimtoctVal ts=\"2\">8.18</sc_cimtoctVal>"
      << "<sc_cimtoctVal ts=\"3\">8.43</sc_cimtoctVal>"
      << "<sc_cimtoctVal ts=\"4\">8.68</sc_cimtoctVal>"
      << "<sc_cimtoctVal ts=\"5\">8.94</sc_cimtoctVal>"
      << "<sc_cimtoctVal ts=\"6\">9.19</sc_cimtoctVal>"
      << "</sc_ciMonthlyTempOct>"

      << "<sc_ciMonthlyTempNov>"
      << "<sc_cimtnovVal ts=\"1\">2.48</sc_cimtnovVal>"
      << "<sc_cimtnovVal ts=\"2\">2.56</sc_cimtnovVal>"
      << "<sc_cimtnovVal ts=\"3\">2.64</sc_cimtnovVal>"
      << "<sc_cimtnovVal ts=\"4\">2.72</sc_cimtnovVal>"
      << "<sc_cimtnovVal ts=\"5\">2.8</sc_cimtnovVal>"
      << "<sc_cimtnovVal ts=\"6\">2.88</sc_cimtnovVal>"
      << "</sc_ciMonthlyTempNov>"

      << "<sc_ciMonthlyTempDec>"
      << "<sc_cimtdecVal ts=\"1\">-9.6</sc_cimtdecVal>"
      << "<sc_cimtdecVal ts=\"2\">-6.94</sc_cimtdecVal>"
      << "<sc_cimtdecVal ts=\"3\">-6.51</sc_cimtdecVal>"
      << "<sc_cimtdecVal ts=\"4\">-1.59</sc_cimtdecVal>"
      << "<sc_cimtdecVal ts=\"5\">0.19</sc_cimtdecVal>"
      << "<sc_cimtdecVal ts=\"6\">2.49</sc_cimtdecVal>"
      << "</sc_ciMonthlyTempDec>"

      << "<sc_ciMonthlyPptJan>"
      << "<sc_cimpjanVal ts=\"1\">161.48</sc_cimpjanVal>"
      << "<sc_cimpjanVal ts=\"2\">152.09</sc_cimpjanVal>"
      << "<sc_cimpjanVal ts=\"3\">152.5</sc_cimpjanVal>"
      << "<sc_cimpjanVal ts=\"4\">152.71</sc_cimpjanVal>"
      << "<sc_cimpjanVal ts=\"5\">78.44</sc_cimpjanVal>"
      << "<sc_cimpjanVal ts=\"6\">123.19</sc_cimpjanVal>"
      << "</sc_ciMonthlyPptJan>"

      << "<sc_ciMonthlyPptFeb>"
      << "<sc_cimpfebVal ts=\"1\">199.32</sc_cimpfebVal>"
      << "<sc_cimpfebVal ts=\"2\">192.94</sc_cimpfebVal>"
      << "<sc_cimpfebVal ts=\"3\">188.1</sc_cimpfebVal>"
      << "<sc_cimpfebVal ts=\"4\">153.95</sc_cimpfebVal>"
      << "<sc_cimpfebVal ts=\"5\">89.79</sc_cimpfebVal>"
      << "<sc_cimpfebVal ts=\"6\">189.67</sc_cimpfebVal>"
      << "</sc_ciMonthlyPptFeb>"

      << "<sc_ciMonthlyPptMar>"
      << "<sc_cimpmarVal ts=\"1\">169.99</sc_cimpmarVal>"
      << "<sc_cimpmarVal ts=\"2\">105.49</sc_cimpmarVal>"
      << "<sc_cimpmarVal ts=\"3\">141.34</sc_cimpmarVal>"
      << "<sc_cimpmarVal ts=\"4\">84.71</sc_cimpmarVal>"
      << "<sc_cimpmarVal ts=\"5\">188.92</sc_cimpmarVal>"
      << "<sc_cimpmarVal ts=\"6\">93.47</sc_cimpmarVal>"
      << "</sc_ciMonthlyPptMar>"

      << "<sc_ciMonthlyPptApr>"
      << "<sc_cimpaprVal ts=\"1\">82.02</sc_cimpaprVal>"
      << "<sc_cimpaprVal ts=\"2\">77.49</sc_cimpaprVal>"
      << "<sc_cimpaprVal ts=\"3\">186.32</sc_cimpaprVal>"
      << "<sc_cimpaprVal ts=\"4\">174.4</sc_cimpaprVal>"
      << "<sc_cimpaprVal ts=\"5\">161.25</sc_cimpaprVal>"
      << "<sc_cimpaprVal ts=\"6\">99.76</sc_cimpaprVal>"
      << "</sc_ciMonthlyPptApr>"

      << "<sc_ciMonthlyPptMay>"
      << "<sc_cimpmayVal ts=\"1\">132.54</sc_cimpmayVal>"
      << "<sc_cimpmayVal ts=\"2\">121.74</sc_cimpmayVal>"
      << "<sc_cimpmayVal ts=\"3\">178.18</sc_cimpmayVal>"
      << "<sc_cimpmayVal ts=\"4\">102.86</sc_cimpmayVal>"
      << "<sc_cimpmayVal ts=\"5\">102.84</sc_cimpmayVal>"
      << "<sc_cimpmayVal ts=\"6\">172.41</sc_cimpmayVal>"
      << "</sc_ciMonthlyPptMay>"

      << "<sc_ciMonthlyPptJun>"
      << "<sc_cimpjunVal ts=\"1\">157.67</sc_cimpjunVal>"
      << "<sc_cimpjunVal ts=\"2\">133.89</sc_cimpjunVal>"
      << "<sc_cimpjunVal ts=\"3\">147.29</sc_cimpjunVal>"
      << "<sc_cimpjunVal ts=\"4\">123.74</sc_cimpjunVal>"
      << "<sc_cimpjunVal ts=\"5\">126.66</sc_cimpjunVal>"
      << "<sc_cimpjunVal ts=\"6\">134.35</sc_cimpjunVal>"
      << "</sc_ciMonthlyPptJun>"

      << "<sc_ciMonthlyPptJul>"
      << "<sc_cimpjulVal ts=\"1\">97.63</sc_cimpjulVal>"
      << "<sc_cimpjulVal ts=\"2\">141.94</sc_cimpjulVal>"
      << "<sc_cimpjulVal ts=\"3\">173.88</sc_cimpjulVal>"
      << "<sc_cimpjulVal ts=\"4\">166.53</sc_cimpjulVal>"
      << "<sc_cimpjulVal ts=\"5\">140.41</sc_cimpjulVal>"
      << "<sc_cimpjulVal ts=\"6\">128.89</sc_cimpjulVal>"
      << "</sc_ciMonthlyPptJul>"

      << "<sc_ciMonthlyPptAug>"
      << "<sc_cimpaugVal ts=\"1\">145.57</sc_cimpaugVal>"
      << "<sc_cimpaugVal ts=\"2\">156.69</sc_cimpaugVal>"
      << "<sc_cimpaugVal ts=\"3\">146.55</sc_cimpaugVal>"
      << "<sc_cimpaugVal ts=\"4\">167.73</sc_cimpaugVal>"
      << "<sc_cimpaugVal ts=\"5\">147.67</sc_cimpaugVal>"
      << "<sc_cimpaugVal ts=\"6\">119.52</sc_cimpaugVal>"
      << "</sc_ciMonthlyPptAug>"

      << "<sc_ciMonthlyPptSep>"
      << "<sc_cimpsepVal ts=\"1\">134.38</sc_cimpsepVal>"
      << "<sc_cimpsepVal ts=\"2\">89.78</sc_cimpsepVal>"
      << "<sc_cimpsepVal ts=\"3\">173.37</sc_cimpsepVal>"
      << "<sc_cimpsepVal ts=\"4\">146.16</sc_cimpsepVal>"
      << "<sc_cimpsepVal ts=\"5\">108.71</sc_cimpsepVal>"
      << "<sc_cimpsepVal ts=\"6\">90.68</sc_cimpsepVal>"
      << "</sc_ciMonthlyPptSep>"

      << "<sc_ciMonthlyPptOct>"
      << "<sc_cimpoctVal ts=\"1\">100.17</sc_cimpoctVal>"
      << "<sc_cimpoctVal ts=\"2\">178.11</sc_cimpoctVal>"
      << "<sc_cimpoctVal ts=\"3\">120.16</sc_cimpoctVal>"
      << "<sc_cimpoctVal ts=\"4\">198.43</sc_cimpoctVal>"
      << "<sc_cimpoctVal ts=\"5\">75.22</sc_cimpoctVal>"
      << "<sc_cimpoctVal ts=\"6\">198.3</sc_cimpoctVal>"
      << "</sc_ciMonthlyPptOct>"

      << "<sc_ciMonthlyPptNov>"
      << "<sc_cimpnovVal ts=\"1\">112.34</sc_cimpnovVal>"
      << "<sc_cimpnovVal ts=\"2\">191.22</sc_cimpnovVal>"
      << "<sc_cimpnovVal ts=\"3\">125.47</sc_cimpnovVal>"
      << "<sc_cimpnovVal ts=\"4\">79.8</sc_cimpnovVal>"
      << "<sc_cimpnovVal ts=\"5\">116.29</sc_cimpnovVal>"
      << "<sc_cimpnovVal ts=\"6\">146.75</sc_cimpnovVal>"
      << "</sc_ciMonthlyPptNov>"

      << "<sc_ciMonthlyPptDec>"
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
      << "<nciWhichPrecipitationEffect>" << double_no_local_diff_precip_effect << "</nciWhichPrecipitationEffect>"
      << "<nciWhichTemperatureEffect>" << double_no_local_diff_temp_effect << "</nciWhichTemperatureEffect>"
      << "<nciWhichNitrogenEffect>" << no_nitrogen_effect << "</nciWhichNitrogenEffect>"
      << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
      << "<gr_stochGrowthMethod>" << deterministic_pdf << "</gr_stochGrowthMethod>"
      << "<gr_nciMaxPotentialGrowth>"
      << "<gr_nmpgVal species=\"Species_2\">1</gr_nmpgVal>"
      << "<gr_nmpgVal species=\"Species_3\">1</gr_nmpgVal>"
      << "<gr_nmpgVal species=\"Species_4\">1</gr_nmpgVal>"
      << "</gr_nciMaxPotentialGrowth>"
      << "<nciDoubNoLocPrecipEffCurrA>"
      << "<ndnlpecaVal species=\"Species_2\">0.001765319</ndnlpecaVal>"
      << "<ndnlpecaVal species=\"Species_3\">1</ndnlpecaVal>"
      << "<ndnlpecaVal species=\"Species_4\">0.9597078</ndnlpecaVal>"
      << "</nciDoubNoLocPrecipEffCurrA>"
      << "<nciDoubNoLocPrecipEffCurrBLo>"
      << "<ndnlpecblVal species=\"Species_2\">0.9139451</ndnlpecblVal>"
      << "<ndnlpecblVal species=\"Species_3\">0.9000193</ndnlpecblVal>"
      << "<ndnlpecblVal species=\"Species_4\">0.9352008</ndnlpecblVal>"
      << "</nciDoubNoLocPrecipEffCurrBLo>"
      << "<nciDoubNoLocPrecipEffCurrBHi>"
      << "<ndnlpecbhVal species=\"Species_2\">0.910562</ndnlpecbhVal>"
      << "<ndnlpecbhVal species=\"Species_3\">0.9656258</ndnlpecbhVal>"
      << "<ndnlpecbhVal species=\"Species_4\">0.9316474</ndnlpecbhVal>"
      << "</nciDoubNoLocPrecipEffCurrBHi>"
      << "<nciDoubNoLocPrecipEffCurrC>"
      << "<ndnlpeccVal species=\"Species_2\">0.8712764</ndnlpeccVal>"
      << "<ndnlpeccVal species=\"Species_3\">0.3</ndnlpeccVal>"
      << "<ndnlpeccVal species=\"Species_4\">0.9407407</ndnlpeccVal>"
      << "</nciDoubNoLocPrecipEffCurrC>"
      << "<nciDoubNoLocPrecipEffPrevA>"
      << "<ndnlpepaVal species=\"Species_2\">0.86</ndnlpepaVal>"
      << "<ndnlpepaVal species=\"Species_3\">0.34</ndnlpepaVal>"
      << "<ndnlpepaVal species=\"Species_4\">0.66</ndnlpepaVal>"
      << "</nciDoubNoLocPrecipEffPrevA>"
      << "<nciDoubNoLocPrecipEffPrevBLo>"
      << "<ndnlpepblVal species=\"Species_2\">0.9</ndnlpepblVal>"
      << "<ndnlpepblVal species=\"Species_3\">0.9761828</ndnlpepblVal>"
      << "<ndnlpepblVal species=\"Species_4\">0.9981236</ndnlpepblVal>"
      << "</nciDoubNoLocPrecipEffPrevBLo>"
      << "<nciDoubNoLocPrecipEffPrevBHi>"
      << "<ndnlpepbhVal species=\"Species_2\">0.9657148</ndnlpepbhVal>"
      << "<ndnlpepbhVal species=\"Species_3\">0.9456557</ndnlpepbhVal>"
      << "<ndnlpepbhVal species=\"Species_4\">0.9541563</ndnlpepbhVal>"
      << "</nciDoubNoLocPrecipEffPrevBHi>"
      << "<nciDoubNoLocPrecipEffPrevC>"
      << "<ndnlpepcVal species=\"Species_2\">0.3</ndnlpepcVal>"
      << "<ndnlpepcVal species=\"Species_3\">0.84678993</ndnlpepcVal>"
      << "<ndnlpepcVal species=\"Species_4\">0.89953342</ndnlpepcVal>"
      << "</nciDoubNoLocPrecipEffPrevC>"
      << "<nciDoubNoLocPrecipType>" << clPrecipitationEffectBase::mean_precip << "</nciDoubNoLocPrecipType>"
      << "<nciDoubNoLocTempEffCurrA>"
      << "<ndnltecaVal species=\"Species_2\">0.7789208</ndnltecaVal>"
      << "<ndnltecaVal species=\"Species_3\">0.008861627</ndnltecaVal>"
      << "<ndnltecaVal species=\"Species_4\">0.06436607</ndnltecaVal>"
      << "</nciDoubNoLocTempEffCurrA>"
      << "<nciDoubNoLocTempEffCurrBLo>"
      << "<ndnltecblVal species=\"Species_2\">0.9738308</ndnltecblVal>"
      << "<ndnltecblVal species=\"Species_3\">0.9</ndnltecblVal>"
      << "<ndnltecblVal species=\"Species_4\">0.9</ndnltecblVal>"
      << "</nciDoubNoLocTempEffCurrBLo>"
      << "<nciDoubNoLocTempEffCurrBHi>"
      << "<ndnltecbhVal species=\"Species_2\">0.9736826</ndnltecbhVal>"
      << "<ndnltecbhVal species=\"Species_3\">1</ndnltecbhVal>"
      << "<ndnltecbhVal species=\"Species_4\">1</ndnltecbhVal>"
      << "</nciDoubNoLocTempEffCurrBHi>"
      << "<nciDoubNoLocTempEffCurrC>"
      << "<ndnlteccVal species=\"Species_2\">17.24231</ndnlteccVal>"
      << "<ndnlteccVal species=\"Species_3\">11.21695</ndnlteccVal>"
      << "<ndnlteccVal species=\"Species_4\">6.21471</ndnlteccVal>"
      << "</nciDoubNoLocTempEffCurrC>"
      << "<nciDoubNoLocTempEffPrevA>"
      << "<ndnltepaVal species=\"Species_2\">0.85</ndnltepaVal>"
      << "<ndnltepaVal species=\"Species_3\">0.77</ndnltepaVal>"
      << "<ndnltepaVal species=\"Species_4\">0.45</ndnltepaVal>"
      << "</nciDoubNoLocTempEffPrevA>"
      << "<nciDoubNoLocTempEffPrevBLo>"
      << "<ndnltepblVal species=\"Species_2\">1</ndnltepblVal>"
      << "<ndnltepblVal species=\"Species_3\">0.9188785</ndnltepblVal>"
      << "<ndnltepblVal species=\"Species_4\">0.9006845</ndnltepblVal>"
      << "</nciDoubNoLocTempEffPrevBLo>"
      << "<nciDoubNoLocTempEffPrevBHi>"
      << "<ndnltepbhVal species=\"Species_2\">0.9166126</ndnltepbhVal>"
      << "<ndnltepbhVal species=\"Species_3\">0.9934763</ndnltepbhVal>"
      << "<ndnltepbhVal species=\"Species_4\">0.990283</ndnltepbhVal>"
      << "</nciDoubNoLocTempEffPrevBHi>"
      << "<nciDoubNoLocTempEffPrevC>"
      << "<ndnltepcVal species=\"Species_2\">5.389124</ndnltepcVal>"
      << "<ndnltepcVal species=\"Species_3\">-19.21351</ndnltepcVal>"
      << "<ndnltepcVal species=\"Species_4\">-14.44979</ndnltepcVal>"
      << "</nciDoubNoLocTempEffPrevC>"
      << "</NCIMasterGrowth2>"

      << "<NCIMasterGrowth3>"
      << "<nciWhichShadingEffect>" << no_shading << "</nciWhichShadingEffect>"
      << "<nciWhichCrowdingEffect>" << no_crowding_effect << "</nciWhichCrowdingEffect>"
      << "<nciWhichNCITerm>" << no_nci_term << "</nciWhichNCITerm>"
      << "<nciWhichSizeEffect>" << no_size_effect << "</nciWhichSizeEffect>"
      << "<nciWhichDamageEffect>" << no_damage_effect << "</nciWhichDamageEffect>"
      << "<nciWhichPrecipitationEffect>" << double_no_local_diff_precip_effect << "</nciWhichPrecipitationEffect>"
      << "<nciWhichTemperatureEffect>" << double_no_local_diff_temp_effect << "</nciWhichTemperatureEffect>"
      << "<nciWhichNitrogenEffect>" << no_nitrogen_effect << "</nciWhichNitrogenEffect>"
      << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
      << "<gr_stochGrowthMethod>" << deterministic_pdf << "</gr_stochGrowthMethod>"
      << "<gr_nciMaxPotentialGrowth>"
      << "<gr_nmpgVal species=\"Species_2\">1</gr_nmpgVal>"
      << "<gr_nmpgVal species=\"Species_3\">1</gr_nmpgVal>"
      << "<gr_nmpgVal species=\"Species_4\">1</gr_nmpgVal>"
      << "</gr_nciMaxPotentialGrowth>"
      << "<nciDoubNoLocPrecipEffCurrA>"
      << "<ndnlpecaVal species=\"Species_2\">0.002</ndnlpecaVal>"
      << "<ndnlpecaVal species=\"Species_3\">1.79137E-06</ndnlpecaVal>"
      << "<ndnlpecaVal species=\"Species_4\">0.9725126</ndnlpecaVal>"
      << "</nciDoubNoLocPrecipEffCurrA>"
      << "<nciDoubNoLocPrecipEffCurrBLo>"
      << "<ndnlpecblVal species=\"Species_2\">1</ndnlpecblVal>"
      << "<ndnlpecblVal species=\"Species_3\">0.9008502</ndnlpecblVal>"
      << "<ndnlpecblVal species=\"Species_4\">0.9044741</ndnlpecblVal>"
      << "</nciDoubNoLocPrecipEffCurrBLo>"
      << "<nciDoubNoLocPrecipEffCurrBHi>"
      << "<ndnlpecbhVal species=\"Species_2\">0.9367533</ndnlpecbhVal>"
      << "<ndnlpecbhVal species=\"Species_3\">0.9794937</ndnlpecbhVal>"
      << "<ndnlpecbhVal species=\"Species_4\">0.90842</ndnlpecbhVal>"
      << "</nciDoubNoLocPrecipEffCurrBHi>"
      << "<nciDoubNoLocPrecipEffCurrC>"
      << "<ndnlpeccVal species=\"Species_2\">1.815486</ndnlpeccVal>"
      << "<ndnlpeccVal species=\"Species_3\">-0.9896434</ndnlpeccVal>"
      << "<ndnlpeccVal species=\"Species_4\">0.04242577</ndnlpeccVal>"
      << "</nciDoubNoLocPrecipEffCurrC>"
      << "<nciDoubNoLocPrecipEffPrevA>"
      << "<ndnlpepaVal species=\"Species_2\">0.85</ndnlpepaVal>"
      << "<ndnlpepaVal species=\"Species_3\">0.65</ndnlpepaVal>"
      << "<ndnlpepaVal species=\"Species_4\">0.89</ndnlpepaVal>"
      << "</nciDoubNoLocPrecipEffPrevA>"
      << "<nciDoubNoLocPrecipEffPrevBLo>"
      << "<ndnlpepblVal species=\"Species_2\">0.963682</ndnlpepblVal>"
      << "<ndnlpepblVal species=\"Species_3\">0.9</ndnlpepblVal>"
      << "<ndnlpepblVal species=\"Species_4\">0.9208368</ndnlpepblVal>"
      << "</nciDoubNoLocPrecipEffPrevBLo>"
      << "<nciDoubNoLocPrecipEffPrevBHi>"
      << "<ndnlpepbhVal species=\"Species_2\">0.9532435</ndnlpepbhVal>"
      << "<ndnlpepbhVal species=\"Species_3\">0.9010854</ndnlpepbhVal>"
      << "<ndnlpepbhVal species=\"Species_4\">0.9999121</ndnlpepbhVal>"
      << "</nciDoubNoLocPrecipEffPrevBHi>"
      << "<nciDoubNoLocPrecipEffPrevC>"
      << "<ndnlpepcVal species=\"Species_2\">-2</ndnlpepcVal>"
      << "<ndnlpepcVal species=\"Species_3\">3</ndnlpepcVal>"
      << "<ndnlpepcVal species=\"Species_4\">0.7098731</ndnlpepcVal>"
      << "</nciDoubNoLocPrecipEffPrevC>"
      << "<nciDoubNoLocPrecipType>" << clPrecipitationEffectBase::mean_precip << "</nciDoubNoLocPrecipType>"
      << "<nciDoubNoLocTempEffCurrA>"
      << "<ndnltecaVal species=\"Species_2\">0.7789208</ndnltecaVal>"
      << "<ndnltecaVal species=\"Species_3\">0.008988428</ndnltecaVal>"
      << "<ndnltecaVal species=\"Species_4\">0.977192</ndnltecaVal>"
      << "</nciDoubNoLocTempEffCurrA>"
      << "<nciDoubNoLocTempEffCurrBLo>"
      << "<ndnltecblVal species=\"Species_2\">0.9738308</ndnltecblVal>"
      << "<ndnltecblVal species=\"Species_3\">0.9143604</ndnltecblVal>"
      << "<ndnltecblVal species=\"Species_4\">0.9936756</ndnltecblVal>"
      << "</nciDoubNoLocTempEffCurrBLo>"
      << "<nciDoubNoLocTempEffCurrBHi>"
      << "<ndnltecbhVal species=\"Species_2\">0.9736826</ndnltecbhVal>"
      << "<ndnltecbhVal species=\"Species_3\">0.996639</ndnltecbhVal>"
      << "<ndnltecbhVal species=\"Species_4\">0.9105076</ndnltecbhVal>"
      << "</nciDoubNoLocTempEffCurrBHi>"
      << "<nciDoubNoLocTempEffCurrC>"
      << "<ndnlteccVal species=\"Species_2\">17.24231</ndnlteccVal>"
      << "<ndnlteccVal species=\"Species_3\">-1.057076</ndnlteccVal>"
      << "<ndnlteccVal species=\"Species_4\">35</ndnlteccVal>"
      << "</nciDoubNoLocTempEffCurrC>"
      << "<nciDoubNoLocTempEffPrevA>"
      << "<ndnltepaVal species=\"Species_2\">0.68</ndnltepaVal>"
      << "<ndnltepaVal species=\"Species_3\">0.867</ndnltepaVal>"
      << "<ndnltepaVal species=\"Species_4\">0.78</ndnltepaVal>"
      << "</nciDoubNoLocTempEffPrevA>"
      << "<nciDoubNoLocTempEffPrevBLo>"
      << "<ndnltepblVal species=\"Species_2\">1</ndnltepblVal>"
      << "<ndnltepblVal species=\"Species_3\">0.9873755</ndnltepblVal>"
      << "<ndnltepblVal species=\"Species_4\">1</ndnltepblVal>"
      << "</nciDoubNoLocTempEffPrevBLo>"
      << "<nciDoubNoLocTempEffPrevBHi>"
      << "<ndnltepbhVal species=\"Species_2\">0.9166126</ndnltepbhVal>"
      << "<ndnltepbhVal species=\"Species_3\">0.9348672</ndnltepbhVal>"
      << "<ndnltepbhVal species=\"Species_4\">0.9000048</ndnltepbhVal>"
      << "</nciDoubNoLocTempEffPrevBHi>"
      << "<nciDoubNoLocTempEffPrevC>"
      << "<ndnltepcVal species=\"Species_2\">5.389124</ndnltepcVal>"
      << "<ndnltepcVal species=\"Species_3\">34.99974</ndnltepcVal>"
      << "<ndnltepcVal species=\"Species_4\">5.452489</ndnltepcVal>"
      << "</nciDoubNoLocTempEffPrevC>"
      << "</NCIMasterGrowth3>"
      << "</paramFile>";
  oOut.close();

  return cFileString;
}



const char* WriteNCIDoubleNoLocalDiffClimateGrowthXMLFile3() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  int i;

  //Write file
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
  for (i = 1; i < 16; i++) {
    oOut << "<tr_species speciesName=\"Species_" << i << "\" />";
  }
  oOut << "</tr_speciesList>"
      << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
      << "<tr_minAdultDBH>";
  for (i = 1; i < 16; i++) {
    oOut << "<tr_madVal species=\"Species_" << i << "\">10.0</tr_madVal>";
  }
  oOut << "</tr_minAdultDBH>"
      << "<tr_maxSeedlingHeight>";
  for (i = 1; i < 16; i++) {
    oOut << "<tr_mshVal species=\"Species_" << i << "\">1.35</tr_mshVal>";
  }
  oOut << "</tr_maxSeedlingHeight>"
      << "</trees>"
      << "<allometry>"
      << "<tr_canopyHeight>";
  for (i = 1; i < 16; i++) {
    oOut << "<tr_chVal species=\"Species_" << i << "\">39.48</tr_chVal>";
  }
  oOut << "</tr_canopyHeight>"
      << "<tr_stdAsympCrownRad>";
  for (i = 1; i < 16; i++) {
    oOut << "<tr_sacrVal species=\"Species_" << i << "\">0.0549</tr_sacrVal>";
  }
  oOut << "</tr_stdAsympCrownRad>"
      << "<tr_stdCrownRadExp>";
  for (i = 1; i < 16; i++) {
    oOut << "<tr_screVal species=\"Species_" << i << "\">1.0</tr_screVal>";
  }
  oOut << "</tr_stdCrownRadExp>"
      << "<tr_stdMaxCrownRad>";
  for (i = 1; i < 16; i++) {
    oOut << "<tr_smcrVal species=\"Species_" << i << "\">10</tr_smcrVal>";
  }
  oOut  << "</tr_stdMaxCrownRad>"
      << "<tr_conversionDiam10ToDBH>";
  for (i = 1; i < 16; i++) {
    oOut << "<tr_cdtdVal species=\"Species_" << i << "\">1</tr_cdtdVal>";
  }
  oOut << "</tr_conversionDiam10ToDBH>"
      << "<tr_interceptDiam10ToDBH>";
  for (i = 1; i < 16; i++) {
    oOut << "<tr_idtdVal species=\"Species_" << i << "\">0</tr_idtdVal>";
  }
  oOut << "</tr_interceptDiam10ToDBH>"
      << "<tr_stdAsympCrownHt>";
  for (i = 1; i < 16; i++) {
    oOut << "<tr_sachVal species=\"Species_" << i << "\">0.389</tr_sachVal>";
  }
  oOut << "</tr_stdAsympCrownHt>"
      << "<tr_stdCrownHtExp>";
  for (i = 1; i < 16; i++) {
    oOut << "<tr_scheVal species=\"Species_" << i << "\">1.0</tr_scheVal>";
  }
  oOut << "</tr_stdCrownHtExp>"
      << "<tr_slopeOfHeight-Diam10>";
  for (i = 1; i < 16; i++) {
    oOut << "<tr_sohdVal species=\"Species_" << i << "\">0.03418</tr_sohdVal>";
  }
  oOut << "</tr_slopeOfHeight-Diam10>"
      << "<tr_slopeOfAsymHeight>";
  for (i = 1; i < 16; i++) {
    oOut << "<tr_soahVal species=\"Species_" << i << "\">0.0299</tr_soahVal>";
  }
  oOut << "</tr_slopeOfAsymHeight>"
      << "<tr_whatSeedlingHeightDiam>";
  for (i = 1; i < 16; i++) {
    oOut << "<tr_wsehdVal species=\"Species_" << i << "\">0</tr_wsehdVal>";
  }
  oOut << "</tr_whatSeedlingHeightDiam>"
      << "<tr_whatSaplingHeightDiam>";
  for (i = 1; i < 16; i++) {
    oOut << "<tr_wsahdVal species=\"Species_" << i << "\">0</tr_wsahdVal>";
  }
  oOut << "</tr_whatSaplingHeightDiam>"
      << "<tr_whatAdultHeightDiam>";
  for (i = 1; i < 16; i++) {
    oOut << "<tr_wahdVal species=\"Species_" << i << "\">0</tr_wahdVal>";
  }
  oOut << "</tr_whatAdultHeightDiam>"
      << "<tr_whatAdultCrownRadDiam>";
  for (i = 1; i < 16; i++) {
    oOut << "<tr_wacrdVal species=\"Species_" << i << "\">0</tr_wacrdVal>";
  }
  oOut << "</tr_whatAdultCrownRadDiam>"
      << "<tr_whatAdultCrownHeightHeight>";
  for (i = 1; i < 16; i++) {
    oOut << "<tr_wachhVal species=\"Species_" << i << "\">0</tr_wachhVal>";
  }
  oOut << "</tr_whatAdultCrownHeightHeight>"
      << "<tr_whatSaplingCrownRadDiam>";
  for (i = 1; i < 16; i++) {
    oOut << "<tr_wscrdVal species=\"Species_" << i << "\">0</tr_wscrdVal>";
  }
  oOut << "</tr_whatSaplingCrownRadDiam>"
      << "<tr_whatSaplingCrownHeightHeight>";
  for (i = 1; i < 16; i++) {
    oOut << "<tr_wschhVal species=\"Species_" << i << "\">0</tr_wschhVal>";
  }
  oOut << "</tr_whatSaplingCrownHeightHeight>"
      << "</allometry>"
      << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>NCIMasterGrowth</behaviorName>"
      << "<version>3</version>"
      << "<listPosition>1</listPosition>";
  for (i = 1; i < 16; i++) {
    oOut  << "<applyTo species=\"Species_" << i << "\" type=\"Adult\"/>";
  }
  oOut  << "</behavior>"
      << "</behaviorList>"

      << "<NCIMasterGrowth1>"
      << "<nciWhichShadingEffect>" << no_shading << "</nciWhichShadingEffect>"
      << "<nciWhichCrowdingEffect>" << no_crowding_effect << "</nciWhichCrowdingEffect>"
      << "<nciWhichNCITerm>" << no_nci_term << "</nciWhichNCITerm>"
      << "<nciWhichSizeEffect>" << no_size_effect << "</nciWhichSizeEffect>"
      << "<nciWhichDamageEffect>" << no_damage_effect << "</nciWhichDamageEffect>"
      << "<nciWhichPrecipitationEffect>" << no_precip_effect << "</nciWhichPrecipitationEffect>"
      << "<nciWhichTemperatureEffect>" << no_temp_effect << "</nciWhichTemperatureEffect>"
      << "<nciWhichNitrogenEffect>" << no_nitrogen_effect << "</nciWhichNitrogenEffect>"
      << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
      << "<gr_stochGrowthMethod>" << heteroscedastic_normal_pdf << "</gr_stochGrowthMethod>"
      << "<gr_nciMaxPotentialGrowth>"
      << "<gr_nmpgVal species=\"Species_1\">10.33</gr_nmpgVal>"
      << "<gr_nmpgVal species=\"Species_2\">2.61</gr_nmpgVal>"
      << "<gr_nmpgVal species=\"Species_3\">2.32</gr_nmpgVal>"
      << "<gr_nmpgVal species=\"Species_4\">2.17</gr_nmpgVal>"
      << "<gr_nmpgVal species=\"Species_5\">10.2</gr_nmpgVal>"
      << "<gr_nmpgVal species=\"Species_6\">8.57</gr_nmpgVal>"
      << "<gr_nmpgVal species=\"Species_7\">3.73</gr_nmpgVal>"
      << "<gr_nmpgVal species=\"Species_8\">10.53</gr_nmpgVal>"
      << "<gr_nmpgVal species=\"Species_9\">5.15</gr_nmpgVal>"
      << "<gr_nmpgVal species=\"Species_10\">1.24</gr_nmpgVal>"
      << "<gr_nmpgVal species=\"Species_11\">7.61</gr_nmpgVal>"
      << "<gr_nmpgVal species=\"Species_12\">5.33</gr_nmpgVal>"
      << "<gr_nmpgVal species=\"Species_13\">10.15</gr_nmpgVal>"
      << "<gr_nmpgVal species=\"Species_14\">2.54</gr_nmpgVal>"
      << "<gr_nmpgVal species=\"Species_15\">3.84</gr_nmpgVal>"
      << "</gr_nciMaxPotentialGrowth>"
      << "<gr_hetNormInt>"
      << "<gr_hniVal species=\"Species_1\">1.8825675</gr_hniVal>"
      << "<gr_hniVal species=\"Species_2\">1.7211176</gr_hniVal>"
      << "<gr_hniVal species=\"Species_3\">1.8288683</gr_hniVal>"
      << "<gr_hniVal species=\"Species_4\">2.9281439</gr_hniVal>"
      << "<gr_hniVal species=\"Species_5\">0.7299959</gr_hniVal>"
      << "<gr_hniVal species=\"Species_6\">2.1709456</gr_hniVal>"
      << "<gr_hniVal species=\"Species_7\">1.4508971</gr_hniVal>"
      << "<gr_hniVal species=\"Species_8\">1.1418387</gr_hniVal>"
      << "<gr_hniVal species=\"Species_9\">1.9373051</gr_hniVal>"
      << "<gr_hniVal species=\"Species_10\">1.9448008</gr_hniVal>"
      << "<gr_hniVal species=\"Species_11\">0.6998483</gr_hniVal>"
      << "<gr_hniVal species=\"Species_12\">1.8916099</gr_hniVal>"
      << "<gr_hniVal species=\"Species_13\">2.106962</gr_hniVal>"
      << "<gr_hniVal species=\"Species_14\">0.4571966</gr_hniVal>"
      << "<gr_hniVal species=\"Species_15\">1.2892418</gr_hniVal>"
      << "</gr_hetNormInt>"
      << "<gr_hetNormSigma>"
      << "<gr_hnsVal species=\"Species_1\">0.7285181</gr_hnsVal>"
      << "<gr_hnsVal species=\"Species_2\">0.8428638</gr_hnsVal>"
      << "<gr_hnsVal species=\"Species_3\">0.7995021</gr_hnsVal>"
      << "<gr_hnsVal species=\"Species_4\">0.7264695</gr_hnsVal>"
      << "<gr_hnsVal species=\"Species_5\">0.8486945</gr_hnsVal>"
      << "<gr_hnsVal species=\"Species_6\">0.7463495</gr_hnsVal>"
      << "<gr_hnsVal species=\"Species_7\">0.7957558</gr_hnsVal>"
      << "<gr_hnsVal species=\"Species_8\">0.9167974</gr_hnsVal>"
      << "<gr_hnsVal species=\"Species_9\">0.7747422</gr_hnsVal>"
      << "<gr_hnsVal species=\"Species_10\">0.7283079</gr_hnsVal>"
      << "<gr_hnsVal species=\"Species_11\">0.9738845</gr_hnsVal>"
      << "<gr_hnsVal species=\"Species_12\">0.7731892</gr_hnsVal>"
      << "<gr_hnsVal species=\"Species_13\">0.8093394</gr_hnsVal>"
      << "<gr_hnsVal species=\"Species_14\">0.8186369</gr_hnsVal>"
      << "<gr_hnsVal species=\"Species_15\">0.879441</gr_hnsVal>"
      << "</gr_hetNormSigma>"
      << "</NCIMasterGrowth1>"


      << "</paramFile>";
  oOut.close();

  return cFileString;
}

