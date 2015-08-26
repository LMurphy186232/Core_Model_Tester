//---------------------------------------------------------------------------
// TestWeibullSnagMort.cpp
//---------------------------------------------------------------------------
#include "TestWeibullSnagMort.h"
#include <gtest/gtest.h>
#include "TreePopulation.h"
#include "SimManager.h"
#include <fstream>
#include <math.h>

/////////////////////////////////////////////////////////////////////////////
// TestExceptionProcessing()
// Tests exception processing. Tests the following error conditions:
// -- Size classes overlap
// -- Behavior assigned to a tree type other than snag
/////////////////////////////////////////////////////////////////////////////
TEST(WeibullSnagMort, TestExceptionProcessing) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  //Load our error files and make sure we get the error we expect
  try
  {
    p_oSimManager->ReadFile(WriteWeibullSnagMortXMLErrorFile1());
    FAIL() << "TestWeibullSnagMort error processing didn't catch error for WriteWeibullSnagMortXMLErrorFile1.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clWeibullSnagMort::ReadParameterFile") != 0)
    {
      FAIL() << "TestWeibullSnagMort error processing caught wrong error for WriteWeibullSnagMortXMLErrorFile1.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteWeibullSnagMortXMLErrorFile2());
    FAIL() << "TestWeibullSnagMort error processing didn't catch error for WriteWeibullSnagMortXMLErrorFile2.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clWeibullSnagMort::ValidateTypes") != 0)
    {
      FAIL() << "TestWeibullSnagMort error processing caught wrong error for WriteWeibullSnagMortXMLErrorFile2.";
    }
    ;
  }
  delete p_oSimManager;
}

/////////////////////////////////////////////////////////////////////////////
// TestNormalProcessing()
// Tests the mortality classes.
// First run: WriteWeibullSnagMortXMLFile1() creates the parameter file. The file has the
// following characteristics:
// -- Timestep length of 1 year.
// -- 4 species: Species 1, Species 2, Species 3, Species 4.
// -- Snag weibull mort behavior, applied to snags of Species 1, 3, 4.
// -- Tree remover, applied to snags of Species 1, 3, 4.
// -- Size classes are 8 and 30.
//
// The function does the following:
// -- 1000 snags are created of each tree species in each of the size classes.
// -- The model is run for 10 timesteps. After each timestep, the remaining
// trees of each tree type and size class are counted.
// -- The counts are compared to expected results, give or take 5%.
/////////////////////////////////////////////////////////////////////////////
TEST(WeibullSnagMort, TestNormalProcessing1) {
  clTreePopulation * p_oPop;
  clTreeSearch *p_oAllTrees;
  clTree *p_oTree;
  float *p_fSizeClass1, *p_fSizeClass2;
  float fDbh, fExpected;
  int **p_iTreeCount;
  int i, j, iNumSpecies = 4, iNumSizeClasses = 3;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    p_fSizeClass1 = new float[iNumSpecies];
    p_fSizeClass2 = new float[iNumSpecies];
    p_fSizeClass1[0] = 12;
    p_fSizeClass2[0] = 30;
    p_fSizeClass1[1] = 8;
    p_fSizeClass2[1] = 21;
    p_fSizeClass1[2] = 31;
    p_fSizeClass2[2] = 39;
    p_fSizeClass1[3] = 12;
    p_fSizeClass2[3] = 30;

    //Create the sim manager and load our file
    p_oSimManager->ReadFile( WriteWeibullSnagMortXMLFile1() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Set up our tree count array
    p_iTreeCount = new int*[iNumSpecies];
    for (i = 0; i < iNumSpecies; i++) {
      p_iTreeCount[i] = new int[iNumSizeClasses];
    }

    //Create 1000 of each species and each size class
    //Species 1, size class 1
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(1, 1, 0, clTreePopulation::snag, 11);
    }

    //Species 1, size class 2
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(10, 10, 0, clTreePopulation::snag, 25);
    }

    //Species 1, size class 3
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(20, 20, 0, clTreePopulation::snag, 37);
    }

    //Species 2, size class 1
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(30, 30, 1, clTreePopulation::snag, 7);
    }

    //Species 2, size class 2
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(40, 40, 1, clTreePopulation::snag, 17);
    }

    //Species 2, size class 3
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(50, 50, 1, clTreePopulation::snag, 22);
    }

    //Species 3, size class 1
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(60, 60, 2, clTreePopulation::snag, 28);
    }

    //Species 3, size class 2
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(70, 70, 2, clTreePopulation::snag, 35);
    }

    //Species 3, size class 3
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(80, 80, 2, clTreePopulation::snag, 44);
    }

    //Species 4, size class 1
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(1, 1, 3, clTreePopulation::snag, 11);
    }

    //Species 4, size class 2
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(10, 10, 3, clTreePopulation::snag, 25);
    }

    //Species 4, size class 3
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(20, 20, 3, clTreePopulation::snag, 37);
    }


    //*****************Timestep 1************************
    p_oSimManager->RunSim(1);
    //Zero out the array and re-count
    for (i = 0; i < iNumSpecies; i++) {
      for (j = 0; j < iNumSizeClasses; j++) {
        p_iTreeCount[i][j] = 0;
      }
    }
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      EXPECT_EQ(p_oTree->GetType(), clTreePopulation::snag);
      p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDbh);

      if (fDbh <= p_fSizeClass1[p_oTree->GetSpecies()])
        p_iTreeCount[p_oTree->GetSpecies()][0]++;
      else if (fDbh <= p_fSizeClass2[p_oTree->GetSpecies()])
        p_iTreeCount[p_oTree->GetSpecies()][1]++;
      else
        p_iTreeCount[p_oTree->GetSpecies()][2]++;

      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(p_iTreeCount[0][0], 1000);
    EXPECT_EQ(p_iTreeCount[0][1], 1000);
    EXPECT_EQ(p_iTreeCount[0][2], 1000);
    EXPECT_EQ(p_iTreeCount[1][0], 1000);
    EXPECT_EQ(p_iTreeCount[1][1], 1000);
    EXPECT_EQ(p_iTreeCount[1][2], 1000);
    EXPECT_EQ(p_iTreeCount[2][0], 1000);
    EXPECT_EQ(p_iTreeCount[2][1], 1000);
    EXPECT_EQ(p_iTreeCount[2][2], 1000);
    EXPECT_EQ(p_iTreeCount[3][0], 1000);
    EXPECT_EQ(p_iTreeCount[3][1], 1000);
    EXPECT_EQ(p_iTreeCount[3][2], 1000);


    //*****************Timestep 2************************
    p_oSimManager->RunSim(1);
    //Zero out the array and re-count
    for (i = 0; i < iNumSpecies; i++) {
      for (j = 0; j < iNumSizeClasses; j++) {
        p_iTreeCount[i][j] = 0;
      }
    }
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      EXPECT_EQ(p_oTree->GetType(), clTreePopulation::snag);
      p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDbh);

      if (fDbh <= p_fSizeClass1[p_oTree->GetSpecies()])
        p_iTreeCount[p_oTree->GetSpecies()][0]++;
      else if (fDbh <= p_fSizeClass2[p_oTree->GetSpecies()])
        p_iTreeCount[p_oTree->GetSpecies()][1]++;
      else
        p_iTreeCount[p_oTree->GetSpecies()][2]++;

      p_oTree = p_oAllTrees->NextTree();
    }
    fExpected = 998.7041503;
    EXPECT_LT(fabs(p_iTreeCount[0][0] - fExpected)/fExpected, 0.05);
    fExpected = 999.9479092;
    EXPECT_LT(fabs(p_iTreeCount[0][1] - fExpected)/fExpected, 0.05);
    fExpected = 995.0006661;
    EXPECT_LT(fabs(p_iTreeCount[0][2] - fExpected)/fExpected, 0.05);
    EXPECT_EQ(p_iTreeCount[1][0], 1000);
    EXPECT_EQ(p_iTreeCount[1][1], 1000);
    EXPECT_EQ(p_iTreeCount[1][2], 1000);
    fExpected = 999.9843751;
    EXPECT_LT(fabs(p_iTreeCount[2][0] - fExpected)/fExpected, 0.05);
    fExpected = 991.9327166;
    EXPECT_LT(fabs(p_iTreeCount[2][1] - fExpected)/fExpected, 0.05);
    fExpected = 999.9405622;
    EXPECT_LT(fabs(p_iTreeCount[2][2] - fExpected)/fExpected, 0.05);
    EXPECT_LT(p_iTreeCount[3][0], 2);
    EXPECT_LT(p_iTreeCount[3][1], 2);
    EXPECT_LT(p_iTreeCount[3][2], 2);


    //*****************Timestep 3************************
    p_oSimManager->RunSim(1);
    //Zero out the array and re-count
    for (i = 0; i < iNumSpecies; i++) {
      for (j = 0; j < iNumSizeClasses; j++) {
        p_iTreeCount[i][j] = 0;
      }
    }
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      EXPECT_EQ(p_oTree->GetType(), clTreePopulation::snag);
      p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDbh);

      if (fDbh <= p_fSizeClass1[p_oTree->GetSpecies()])
        p_iTreeCount[p_oTree->GetSpecies()][0]++;
      else if (fDbh <= p_fSizeClass2[p_oTree->GetSpecies()])
        p_iTreeCount[p_oTree->GetSpecies()][1]++;
      else
        p_iTreeCount[p_oTree->GetSpecies()][2]++;

      p_oTree = p_oAllTrees->NextTree();
    }
    fExpected = 989.325481;
    EXPECT_LT(fabs(p_iTreeCount[0][0] - fExpected)/fExpected, 0.05);
    fExpected = 999.7606758;
    EXPECT_LT(fabs(p_iTreeCount[0][1] - fExpected)/fExpected, 0.05);
    fExpected = 975.6207397;
    EXPECT_LT(fabs(p_iTreeCount[0][2] - fExpected)/fExpected, 0.05);
    EXPECT_EQ(p_iTreeCount[1][0], 1000);
    EXPECT_EQ(p_iTreeCount[1][1], 1000);
    EXPECT_EQ(p_iTreeCount[1][2], 1000);
    fExpected = 999.8750078;
    EXPECT_LT(fabs(p_iTreeCount[2][0] - fExpected)/fExpected, 0.05);
    fExpected = 968.1192569;
    EXPECT_LT(fabs(p_iTreeCount[2][1] - fExpected)/fExpected, 0.05);
    fExpected = 999.6638157;
    EXPECT_LT(fabs(p_iTreeCount[2][2] - fExpected)/fExpected, 0.05);
    EXPECT_LT(p_iTreeCount[3][0], 2);
    EXPECT_LT(p_iTreeCount[3][1], 2);
    EXPECT_LT(p_iTreeCount[3][2], 2);


    //*****************Timestep 4************************
    p_oSimManager->RunSim(1);
    //Zero out the array and re-count
    for (i = 0; i < iNumSpecies; i++) {
      for (j = 0; j < iNumSizeClasses; j++) {
        p_iTreeCount[i][j] = 0;
      }
    }
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      EXPECT_EQ(p_oTree->GetType(), clTreePopulation::snag);
      p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDbh);

      if (fDbh <= p_fSizeClass1[p_oTree->GetSpecies()])
        p_iTreeCount[p_oTree->GetSpecies()][0]++;
      else if (fDbh <= p_fSizeClass2[p_oTree->GetSpecies()])
        p_iTreeCount[p_oTree->GetSpecies()][1]++;
      else
        p_iTreeCount[p_oTree->GetSpecies()][2]++;

      p_oTree = p_oAllTrees->NextTree();
    }
    fExpected = 963.7272362;
    EXPECT_LT(fabs(p_iTreeCount[0][0] - fExpected)/fExpected, 0.05);
    fExpected = 999.4161349;
    EXPECT_LT(fabs(p_iTreeCount[0][1] - fExpected)/fExpected, 0.05);
    fExpected = 939.210099;
    EXPECT_LT(fabs(p_iTreeCount[0][2] - fExpected)/fExpected, 0.05);
    EXPECT_EQ(p_iTreeCount[1][0], 1000);
    EXPECT_EQ(p_iTreeCount[1][1], 1000);
    EXPECT_EQ(p_iTreeCount[1][2], 1000);
    fExpected = 999.578214;
    EXPECT_LT(fabs(p_iTreeCount[2][0] - fExpected)/fExpected, 0.05);
    fExpected = 929.6937948;
    EXPECT_LT(fabs(p_iTreeCount[2][1] - fExpected)/fExpected, 0.05);
    fExpected = 999.0738585;
    EXPECT_LT(fabs(p_iTreeCount[2][2] - fExpected)/fExpected, 0.05);
    EXPECT_LT(p_iTreeCount[3][0], 2);
    EXPECT_LT(p_iTreeCount[3][1], 2);
    EXPECT_LT(p_iTreeCount[3][2], 2);


    //*****************Timestep 5************************
    p_oSimManager->RunSim(1);
    //Zero out the array and re-count
    for (i = 0; i < iNumSpecies; i++) {
      for (j = 0; j < iNumSizeClasses; j++) {
        p_iTreeCount[i][j] = 0;
      }
    }
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      EXPECT_EQ(p_oTree->GetType(), clTreePopulation::snag);
      p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDbh);

      if (fDbh <= p_fSizeClass1[p_oTree->GetSpecies()])
        p_iTreeCount[p_oTree->GetSpecies()][0]++;
      else if (fDbh <= p_fSizeClass2[p_oTree->GetSpecies()])
        p_iTreeCount[p_oTree->GetSpecies()][1]++;
      else
        p_iTreeCount[p_oTree->GetSpecies()][2]++;

      p_oTree = p_oAllTrees->NextTree();
    }
    fExpected = 915.0090781;
    EXPECT_LT(fabs(p_iTreeCount[0][0] - fExpected)/fExpected, 0.05);
    fExpected = 998.9008277;
    EXPECT_LT(fabs(p_iTreeCount[0][1] - fExpected)/fExpected, 0.05);
    fExpected = 885.550984;
    EXPECT_LT(fabs(p_iTreeCount[0][2] - fExpected)/fExpected, 0.05);
    EXPECT_EQ(p_iTreeCount[1][0], 1000);
    EXPECT_EQ(p_iTreeCount[1][1], 1000);
    EXPECT_EQ(p_iTreeCount[1][2], 1000);
    fExpected = 999.0004998;
    EXPECT_LT(fabs(p_iTreeCount[2][0] - fExpected)/fExpected, 0.05);
    fExpected = 878.4467393;
    EXPECT_LT(fabs(p_iTreeCount[2][1] - fExpected)/fExpected, 0.05);
    fExpected = 998.0997426;
    EXPECT_LT(fabs(p_iTreeCount[2][2] - fExpected)/fExpected, 0.05);
    EXPECT_LT(p_iTreeCount[3][0], 2);
    EXPECT_LT(p_iTreeCount[3][1], 2);
    EXPECT_LT(p_iTreeCount[3][2], 2);

    //*****************Timestep 6************************
    p_oSimManager->RunSim(1);
    //Zero out the array and re-count
    for (i = 0; i < iNumSpecies; i++) {
      for (j = 0; j < iNumSizeClasses; j++) {
        p_iTreeCount[i][j] = 0;
      }
    }
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      EXPECT_EQ(p_oTree->GetType(), clTreePopulation::snag);
      p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDbh);

      if (fDbh <= p_fSizeClass1[p_oTree->GetSpecies()])
        p_iTreeCount[p_oTree->GetSpecies()][0]++;
      else if (fDbh <= p_fSizeClass2[p_oTree->GetSpecies()])
        p_iTreeCount[p_oTree->GetSpecies()][1]++;
      else
        p_iTreeCount[p_oTree->GetSpecies()][2]++;

      p_oTree = p_oAllTrees->NextTree();
    }
    fExpected = 839.1327838;
    EXPECT_LT(fabs(p_iTreeCount[0][0] - fExpected)/fExpected, 0.05);
    fExpected = 998.204785;
    EXPECT_LT(fabs(p_iTreeCount[0][1] - fExpected)/fExpected, 0.05);
    fExpected = 816.2267366;
    EXPECT_LT(fabs(p_iTreeCount[0][2] - fExpected)/fExpected, 0.05);
    EXPECT_EQ(p_iTreeCount[1][0], 1000);
    EXPECT_EQ(p_iTreeCount[1][1], 1000);
    EXPECT_EQ(p_iTreeCount[1][2], 1000);
    fExpected = 998.0487811;
    EXPECT_LT(fabs(p_iTreeCount[2][0] - fExpected)/fExpected, 0.05);
    fExpected = 816.6864826;
    EXPECT_LT(fabs(p_iTreeCount[2][1] - fExpected)/fExpected, 0.05);
    fExpected =   996.6827432;
    EXPECT_LT(fabs(p_iTreeCount[2][2] - fExpected)/fExpected, 0.05);
    EXPECT_LT(p_iTreeCount[3][0], 2);
    EXPECT_LT(p_iTreeCount[3][1], 2);
    EXPECT_LT(p_iTreeCount[3][2], 2);

    //*****************Timestep 7************************
    p_oSimManager->RunSim(1);
    //Zero out the array and re-count
    for (i = 0; i < iNumSpecies; i++) {
      for (j = 0; j < iNumSizeClasses; j++) {
        p_iTreeCount[i][j] = 0;
      }
    }
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      EXPECT_EQ(p_oTree->GetType(), clTreePopulation::snag);
      p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDbh);

      if (fDbh <= p_fSizeClass1[p_oTree->GetSpecies()])
        p_iTreeCount[p_oTree->GetSpecies()][0]++;
      else if (fDbh <= p_fSizeClass2[p_oTree->GetSpecies()])
        p_iTreeCount[p_oTree->GetSpecies()][1]++;
      else
        p_iTreeCount[p_oTree->GetSpecies()][2]++;

      p_oTree = p_oAllTrees->NextTree();
    }
    fExpected = 736.5433214;
    EXPECT_LT(fabs(p_iTreeCount[0][0] - fExpected)/fExpected, 0.05);
    fExpected = 997.3200744;
    EXPECT_LT(fabs(p_iTreeCount[0][1] - fExpected)/fExpected, 0.05);
    fExpected = 734.2907643;
    EXPECT_LT(fabs(p_iTreeCount[0][2] - fExpected)/fExpected, 0.05);
    EXPECT_EQ(p_iTreeCount[1][0], 1000);
    EXPECT_EQ(p_iTreeCount[1][1], 1000);
    EXPECT_EQ(p_iTreeCount[1][2], 1000);
    fExpected = 996.6306889;
    EXPECT_LT(fabs(p_iTreeCount[2][0] - fExpected)/fExpected, 0.05);
    fExpected = 747.0673031;
    EXPECT_LT(fabs(p_iTreeCount[2][1] - fExpected)/fExpected, 0.05);
    fExpected = 994.7722373;
    EXPECT_LT(fabs(p_iTreeCount[2][2] - fExpected)/fExpected, 0.05);
    EXPECT_LT(p_iTreeCount[3][0], 2);
    EXPECT_LT(p_iTreeCount[3][1], 2);
    EXPECT_LT(p_iTreeCount[3][2], 2);

    //*****************Timestep 8************************
    p_oSimManager->RunSim(1);
    //Zero out the array and re-count
    for (i = 0; i < iNumSpecies; i++) {
      for (j = 0; j < iNumSizeClasses; j++) {
        p_iTreeCount[i][j] = 0;
      }
    }
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      EXPECT_EQ(p_oTree->GetType(), clTreePopulation::snag);
      p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDbh);

      if (fDbh <= p_fSizeClass1[p_oTree->GetSpecies()])
        p_iTreeCount[p_oTree->GetSpecies()][0]++;
      else if (fDbh <= p_fSizeClass2[p_oTree->GetSpecies()])
        p_iTreeCount[p_oTree->GetSpecies()][1]++;
      else
        p_iTreeCount[p_oTree->GetSpecies()][2]++;

      p_oTree = p_oAllTrees->NextTree();
    }
    fExpected = 613.0796381;
    EXPECT_LT(fabs(p_iTreeCount[0][0] - fExpected)/fExpected, 0.05);
    fExpected = 996.2401498;
    EXPECT_LT(fabs(p_iTreeCount[0][1] - fExpected)/fExpected, 0.05);
    fExpected = 643.8583783;
    EXPECT_LT(fabs(p_iTreeCount[0][2] - fExpected)/fExpected, 0.05);
    EXPECT_EQ(p_iTreeCount[1][0], 1000);
    EXPECT_EQ(p_iTreeCount[1][1], 1000);
    EXPECT_EQ(p_iTreeCount[1][2], 1000);
    fExpected = 994.6549608;
    EXPECT_LT(fabs(p_iTreeCount[2][0] - fExpected)/fExpected, 0.05);
    fExpected = 672.4012624;
    EXPECT_LT(fabs(p_iTreeCount[2][1] - fExpected)/fExpected, 0.05);
    fExpected = 992.3237645;
    EXPECT_LT(fabs(p_iTreeCount[2][2] - fExpected)/fExpected, 0.05);
    EXPECT_LT(p_iTreeCount[3][0], 2);
    EXPECT_LT(p_iTreeCount[3][1], 2);
    EXPECT_LT(p_iTreeCount[3][2], 2);

    //*****************Timestep 9************************
    p_oSimManager->RunSim(1);
    //Zero out the array and re-count
    for (i = 0; i < iNumSpecies; i++) {
      for (j = 0; j < iNumSizeClasses; j++) {
        p_iTreeCount[i][j] = 0;
      }
    }
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      EXPECT_EQ(p_oTree->GetType(), clTreePopulation::snag);
      p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDbh);

      if (fDbh <= p_fSizeClass1[p_oTree->GetSpecies()])
        p_iTreeCount[p_oTree->GetSpecies()][0]++;
      else if (fDbh <= p_fSizeClass2[p_oTree->GetSpecies()])
        p_iTreeCount[p_oTree->GetSpecies()][1]++;
      else
        p_iTreeCount[p_oTree->GetSpecies()][2]++;

      p_oTree = p_oAllTrees->NextTree();
    }
    fExpected = 479.448485;
    EXPECT_LT(fabs(p_iTreeCount[0][0] - fExpected)/fExpected, 0.05);
    fExpected = 994.9594989;
    EXPECT_LT(fabs(p_iTreeCount[0][1] - fExpected)/fExpected, 0.05);
    fExpected = 549.6030401;
    EXPECT_LT(fabs(p_iTreeCount[0][2] - fExpected)/fExpected, 0.05);
    EXPECT_EQ(p_iTreeCount[1][0], 1000);
    EXPECT_EQ(p_iTreeCount[1][1], 1000);
    EXPECT_EQ(p_iTreeCount[1][2], 1000);
    fExpected = 992.0319148;
    EXPECT_LT(fabs(p_iTreeCount[2][0] - fExpected)/fExpected, 0.05);
    fExpected = 595.4725422;
    EXPECT_LT(fabs(p_iTreeCount[2][1] - fExpected)/fExpected, 0.06);
    fExpected = 989.297973;
    EXPECT_LT(fabs(p_iTreeCount[2][2] - fExpected)/fExpected, 0.05);
    EXPECT_LT(p_iTreeCount[3][0], 2);
    EXPECT_LT(p_iTreeCount[3][1], 2);
    EXPECT_LT(p_iTreeCount[3][2], 2);

    //*****************Timestep 10************************
    p_oSimManager->RunSim(1);
    //Zero out the array and re-count
    for (i = 0; i < iNumSpecies; i++) {
      for (j = 0; j < iNumSizeClasses; j++) {
        p_iTreeCount[i][j] = 0;
      }
    }
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      EXPECT_EQ(p_oTree->GetType(), clTreePopulation::snag);
      p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDbh);

      if (fDbh <= p_fSizeClass1[p_oTree->GetSpecies()])
        p_iTreeCount[p_oTree->GetSpecies()][0]++;
      else if (fDbh <= p_fSizeClass2[p_oTree->GetSpecies()])
        p_iTreeCount[p_oTree->GetSpecies()][1]++;
      else
        p_iTreeCount[p_oTree->GetSpecies()][2]++;

      p_oTree = p_oAllTrees->NextTree();
    }
    fExpected = 348.9798423;
    EXPECT_LT(fabs(p_iTreeCount[0][0] - fExpected)/fExpected, 0.05);
    fExpected = 993.47343;
    EXPECT_LT(fabs(p_iTreeCount[0][1] - fExpected)/fExpected, 0.05);
    fExpected = 456.2119428;
    EXPECT_LT(fabs(p_iTreeCount[0][2] - fExpected)/fExpected, 0.05);
    EXPECT_EQ(p_iTreeCount[1][0], 1000);
    EXPECT_EQ(p_iTreeCount[1][1], 1000);
    EXPECT_EQ(p_iTreeCount[1][2], 1000);
    fExpected = 988.6740026;
    EXPECT_LT(fabs(p_iTreeCount[2][0] - fExpected)/fExpected, 0.05);
    fExpected = 518.8709905;
    EXPECT_LT(fabs(p_iTreeCount[2][1] - fExpected)/fExpected, 0.05);
    fExpected = 985.6600039;
    EXPECT_LT(fabs(p_iTreeCount[2][2] - fExpected)/fExpected, 0.05);
    EXPECT_LT(p_iTreeCount[3][0], 2);
    EXPECT_LT(p_iTreeCount[3][1], 2);
    EXPECT_LT(p_iTreeCount[3][2], 2);

    //*****************Timestep 31************************
    p_oSimManager->RunSim(21);
    //Zero out the array and re-count
    for (i = 0; i < iNumSpecies; i++) {
      for (j = 0; j < iNumSizeClasses; j++) {
        p_iTreeCount[i][j] = 0;
      }
    }
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      EXPECT_EQ(p_oTree->GetType(), clTreePopulation::snag);
      p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDbh);

      if (fDbh <= p_fSizeClass1[p_oTree->GetSpecies()])
        p_iTreeCount[p_oTree->GetSpecies()][0]++;
      else if (fDbh <= p_fSizeClass2[p_oTree->GetSpecies()])
        p_iTreeCount[p_oTree->GetSpecies()][1]++;
      else
        p_iTreeCount[p_oTree->GetSpecies()][2]++;

      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(p_iTreeCount[0][0], 0);
    fExpected = 911.591407;
    EXPECT_LT(fabs(p_iTreeCount[0][1] - fExpected)/fExpected, 0.05);
    EXPECT_EQ(p_iTreeCount[0][2], 0);
    EXPECT_EQ(p_iTreeCount[1][0], 1000);
    EXPECT_EQ(p_iTreeCount[1][1], 1000);
    EXPECT_EQ(p_iTreeCount[1][2], 1000);
    fExpected = 655.8160113;
    EXPECT_LT(fabs(p_iTreeCount[2][0] - fExpected)/fExpected, 0.05);
    EXPECT_LT(p_iTreeCount[2][1], 3);
    fExpected = 746.016637;
    EXPECT_LT(fabs(p_iTreeCount[2][2] - fExpected)/fExpected, 0.05);
    EXPECT_LT(p_iTreeCount[3][0], 2);
    EXPECT_LT(p_iTreeCount[3][1], 2);
    EXPECT_LT(p_iTreeCount[3][2], 2);

    //Cleanup
    for (i = 0; i < iNumSpecies; i++) delete[] p_iTreeCount[i];
    delete[] p_iTreeCount;
    delete[] p_fSizeClass1;
    delete[] p_fSizeClass2;
    delete p_oSimManager;
  } catch (modelErr &e) {
    for (i = 0; i < iNumSpecies; i++) delete[] p_iTreeCount[i];
    delete[] p_iTreeCount;
    delete[] p_fSizeClass1;
    delete[] p_fSizeClass2;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestNormalProcessing()
// Tests the mortality classes.
// Second run:
// WriteWeibullSnagMortXMLFile2() creates the parameter file. The file has the following
// characteristics:
// -- Timestep length of 3 years.
// -- 4 species: Species 1, Species 2, Species 3, Species 4.
// -- Snag weibull mort behavior, applied to snags of Species 1, 3, 4.
// -- Tree remover, applied to snags of Species 1, 3, 4.
// -- Size classes are 12 and 30.
//
// The function does the following:
// -- 1000 snags are created of each tree species in each of the size classes.
// -- The model is run for 10 timesteps. After each timestep, the remaining
// trees of each tree type and size class are counted.
// -- The counts are compared to expected results, give or take 5% (greater
// margins are allowed for smaller numbers).
/////////////////////////////////////////////////////////////////////////////
TEST(WeibullSnagMort, TestNormalProcessing2) {
  clTreePopulation * p_oPop;
  clTreeSearch *p_oAllTrees;
  clTree *p_oTree;
  float *p_fSizeClass1, *p_fSizeClass2;
  float fDbh, fExpected;
  int **p_iTreeCount;
  int i, j, iNumSpecies = 4, iNumSizeClasses = 3;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    p_fSizeClass1 = new float[iNumSpecies];
    p_fSizeClass2 = new float[iNumSpecies];
    p_fSizeClass1[0] = 12;
    p_fSizeClass2[0] = 30;
    p_fSizeClass1[1] = 8;
    p_fSizeClass2[1] = 21;
    p_fSizeClass1[2] = 31;
    p_fSizeClass2[2] = 39;
    p_fSizeClass1[3] = 12;
    p_fSizeClass2[3] = 30;

    //Create the sim manager and load our file
    p_oSimManager->ReadFile( WriteWeibullSnagMortXMLFile2() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Set up our tree count array
    p_iTreeCount = new int*[iNumSpecies];
    for (i = 0; i < iNumSpecies; i++) {
      p_iTreeCount[i] = new int[iNumSizeClasses];
    }

    //Create 1000 of each species and each size class
    //Species 1, size class 1
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(1, 1, 0, clTreePopulation::snag, 11);
    }

    //Species 1, size class 2
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(10, 10, 0, clTreePopulation::snag, 25);
    }

    //Species 1, size class 3
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(20, 20, 0, clTreePopulation::snag, 37);
    }

    //Species 2, size class 1
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(30, 30, 1, clTreePopulation::snag, 7);
    }

    //Species 2, size class 2
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(40, 40, 1, clTreePopulation::snag, 17);
    }

    //Species 2, size class 3
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(50, 50, 1, clTreePopulation::snag, 22);
    }

    //Species 3, size class 1
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(60, 60, 2, clTreePopulation::snag, 28);
    }

    //Species 3, size class 2
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(70, 70, 2, clTreePopulation::snag, 35);
    }

    //Species 3, size class 3
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(80, 80, 2, clTreePopulation::snag, 44);
    }

    //Species 4, size class 1
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(1, 1, 3, clTreePopulation::snag, 11);
    }

    //Species 4, size class 2
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(10, 10, 3, clTreePopulation::snag, 25);
    }

    //Species 4, size class 3
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(20, 20, 3, clTreePopulation::snag, 37);
    }

    //*****************Timestep 1************************
    p_oSimManager->RunSim(1);
    //Zero out the array and re-count
    for (i = 0; i < iNumSpecies; i++) {
      for (j = 0; j < iNumSizeClasses; j++) {
        p_iTreeCount[i][j] = 0;
      }
    }
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      EXPECT_EQ(p_oTree->GetType(), clTreePopulation::snag);
      p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDbh);

      if (fDbh <= p_fSizeClass1[p_oTree->GetSpecies()])
        p_iTreeCount[p_oTree->GetSpecies()][0]++;
      else if (fDbh <= p_fSizeClass2[p_oTree->GetSpecies()])
        p_iTreeCount[p_oTree->GetSpecies()][1]++;
      else
        p_iTreeCount[p_oTree->GetSpecies()][2]++;

      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(p_iTreeCount[0][0], 1000);
    EXPECT_EQ(p_iTreeCount[0][1], 1000);
    EXPECT_EQ(p_iTreeCount[0][2], 1000);
    EXPECT_EQ(p_iTreeCount[1][0], 1000);
    EXPECT_EQ(p_iTreeCount[1][1], 1000);
    EXPECT_EQ(p_iTreeCount[1][2], 1000);
    EXPECT_EQ(p_iTreeCount[2][0], 1000);
    EXPECT_EQ(p_iTreeCount[2][1], 1000);
    EXPECT_EQ(p_iTreeCount[2][2], 1000);
    EXPECT_EQ(p_iTreeCount[3][0], 1000);
    EXPECT_EQ(p_iTreeCount[3][1], 1000);
    EXPECT_EQ(p_iTreeCount[3][2], 1000);

    //*****************Timestep 2************************
    p_oSimManager->RunSim(1);
    //Zero out the array and re-count
    for (i = 0; i < iNumSpecies; i++) {
      for (j = 0; j < iNumSizeClasses; j++) {
        p_iTreeCount[i][j] = 0;
      }
    }
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      EXPECT_EQ(p_oTree->GetType(), clTreePopulation::snag);
      p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDbh);

      if (fDbh <= p_fSizeClass1[p_oTree->GetSpecies()])
        p_iTreeCount[p_oTree->GetSpecies()][0]++;
      else if (fDbh <= p_fSizeClass2[p_oTree->GetSpecies()])
        p_iTreeCount[p_oTree->GetSpecies()][1]++;
      else
        p_iTreeCount[p_oTree->GetSpecies()][2]++;

      p_oTree = p_oAllTrees->NextTree();
    }
    fExpected = 963.7272362;
    EXPECT_LT(fabs(p_iTreeCount[0][0] - fExpected)/fExpected, 0.05);
    fExpected = 999.4161349;
    EXPECT_LT(fabs(p_iTreeCount[0][1] - fExpected)/fExpected, 0.05);
    fExpected = 939.210099;
    EXPECT_LT(fabs(p_iTreeCount[0][2] - fExpected)/fExpected, 0.05);
    EXPECT_EQ(p_iTreeCount[1][0], 1000);
    EXPECT_EQ(p_iTreeCount[1][1], 1000);
    EXPECT_EQ(p_iTreeCount[1][2], 1000);
    fExpected = 999.578214;
    EXPECT_LT(fabs(p_iTreeCount[2][0] - fExpected)/fExpected, 0.05);
    fExpected = 929.6937948;
    EXPECT_LT(fabs(p_iTreeCount[2][1] - fExpected)/fExpected, 0.05);
    fExpected = 999.0738585;
    EXPECT_LT(fabs(p_iTreeCount[2][2] - fExpected)/fExpected, 0.05);
    EXPECT_LT(p_iTreeCount[3][0], 2);
    EXPECT_LT(p_iTreeCount[3][1], 2);
    EXPECT_LT(p_iTreeCount[3][2], 2);

    //*****************Timestep 3************************
    p_oSimManager->RunSim(1);
    //Zero out the array and re-count
    for (i = 0; i < iNumSpecies; i++) {
      for (j = 0; j < iNumSizeClasses; j++) {
        p_iTreeCount[i][j] = 0;
      }
    }
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      EXPECT_EQ(p_oTree->GetType(), clTreePopulation::snag);
      p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDbh);

      if (fDbh <= p_fSizeClass1[p_oTree->GetSpecies()])
        p_iTreeCount[p_oTree->GetSpecies()][0]++;
      else if (fDbh <= p_fSizeClass2[p_oTree->GetSpecies()])
        p_iTreeCount[p_oTree->GetSpecies()][1]++;
      else
        p_iTreeCount[p_oTree->GetSpecies()][2]++;

      p_oTree = p_oAllTrees->NextTree();
    }
    fExpected = 736.5433214;
    EXPECT_LT(fabs(p_iTreeCount[0][0] - fExpected)/fExpected, 0.05);
    fExpected = 997.3200744;
    EXPECT_LT(fabs(p_iTreeCount[0][1] - fExpected)/fExpected, 0.05);
    fExpected = 734.2907643;
    EXPECT_LT(fabs(p_iTreeCount[0][2] - fExpected)/fExpected, 0.05);
    EXPECT_EQ(p_iTreeCount[1][0], 1000);
    EXPECT_EQ(p_iTreeCount[1][1], 1000);
    EXPECT_EQ(p_iTreeCount[1][2], 1000);
    fExpected = 996.6306889;
    EXPECT_LT(fabs(p_iTreeCount[2][0] - fExpected)/fExpected, 0.05);
    fExpected = 747.0673031;
    EXPECT_LT(fabs(p_iTreeCount[2][1] - fExpected)/fExpected, 0.05);
    fExpected = 994.7722373;
    EXPECT_LT(fabs(p_iTreeCount[2][2] - fExpected)/fExpected, 0.05);
    EXPECT_LT(p_iTreeCount[3][0], 2);
    EXPECT_LT(p_iTreeCount[3][1], 2);
    EXPECT_LT(p_iTreeCount[3][2], 2);

    //*****************Timestep 4************************
    p_oSimManager->RunSim(1);
    //Zero out the array and re-count
    for (i = 0; i < iNumSpecies; i++) {
      for (j = 0; j < iNumSizeClasses; j++) {
        p_iTreeCount[i][j] = 0;
      }
    }
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      EXPECT_EQ(p_oTree->GetType(), clTreePopulation::snag);
      p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDbh);

      if (fDbh <= p_fSizeClass1[p_oTree->GetSpecies()])
        p_iTreeCount[p_oTree->GetSpecies()][0]++;
      else if (fDbh <= p_fSizeClass2[p_oTree->GetSpecies()])
        p_iTreeCount[p_oTree->GetSpecies()][1]++;
      else
        p_iTreeCount[p_oTree->GetSpecies()][2]++;

      p_oTree = p_oAllTrees->NextTree();
    }
    fExpected = 348.9798423;
    EXPECT_LT(fabs(p_iTreeCount[0][0] - fExpected)/fExpected, 0.07);
    fExpected = 993.47343;
    EXPECT_LT(fabs(p_iTreeCount[0][1] - fExpected)/fExpected, 0.05);
    fExpected = 456.2119428;
    EXPECT_LT(fabs(p_iTreeCount[0][2] - fExpected)/fExpected, 0.07);
    EXPECT_EQ(p_iTreeCount[1][0], 1000);
    EXPECT_EQ(p_iTreeCount[1][1], 1000);
    EXPECT_EQ(p_iTreeCount[1][2], 1000);
    fExpected = 988.6740026;
    EXPECT_LT(fabs(p_iTreeCount[2][0] - fExpected)/fExpected, 0.05);
    fExpected = 518.8709905;
    EXPECT_LT(fabs(p_iTreeCount[2][1] - fExpected)/fExpected, 0.05);
    fExpected = 985.6600039;
    EXPECT_LT(fabs(p_iTreeCount[2][2] - fExpected)/fExpected, 0.05);
    EXPECT_LT(p_iTreeCount[3][0], 2);
    EXPECT_LT(p_iTreeCount[3][1], 2);
    EXPECT_LT(p_iTreeCount[3][2], 2);

    //*****************Timestep 5************************
    p_oSimManager->RunSim(1);
    //Zero out the array and re-count
    for (i = 0; i < iNumSpecies; i++) {
      for (j = 0; j < iNumSizeClasses; j++) {
        p_iTreeCount[i][j] = 0;
      }
    }
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      EXPECT_EQ(p_oTree->GetType(), clTreePopulation::snag);
      p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDbh);

      if (fDbh <= p_fSizeClass1[p_oTree->GetSpecies()])
        p_iTreeCount[p_oTree->GetSpecies()][0]++;
      else if (fDbh <= p_fSizeClass2[p_oTree->GetSpecies()])
        p_iTreeCount[p_oTree->GetSpecies()][1]++;
      else
        p_iTreeCount[p_oTree->GetSpecies()][2]++;

      p_oTree = p_oAllTrees->NextTree();
    }
    fExpected = 79.59440592;
    EXPECT_LT(fabs(p_iTreeCount[0][0] - fExpected)/fExpected, 0.1);
    fExpected = 987.7454719;
    EXPECT_LT(fabs(p_iTreeCount[0][1] - fExpected)/fExpected, 0.05);
    fExpected = 218.5027334;
    EXPECT_LT(fabs(p_iTreeCount[0][2] - fExpected)/fExpected, 0.15);
    EXPECT_EQ(p_iTreeCount[1][0], 1000);
    EXPECT_EQ(p_iTreeCount[1][1], 1000);
    EXPECT_EQ(p_iTreeCount[1][2], 1000);
    fExpected = 973.3612415;
    EXPECT_LT(fabs(p_iTreeCount[2][0] - fExpected)/fExpected, 0.05);
    fExpected = 311.4862758;
    EXPECT_LT(fabs(p_iTreeCount[2][1] - fExpected)/fExpected, 0.07);
    fExpected = 970.7849947;
    EXPECT_LT(fabs(p_iTreeCount[2][2] - fExpected)/fExpected, 0.05);
    EXPECT_LT(p_iTreeCount[3][0], 2);
    EXPECT_LT(p_iTreeCount[3][1], 2);
    EXPECT_LT(p_iTreeCount[3][2], 2);

    //*****************Timestep 6************************
    p_oSimManager->RunSim(1);
    //Zero out the array and re-count
    for (i = 0; i < iNumSpecies; i++) {
      for (j = 0; j < iNumSizeClasses; j++) {
        p_iTreeCount[i][j] = 0;
      }
    }
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      EXPECT_EQ(p_oTree->GetType(), clTreePopulation::snag);
      p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDbh);

      if (fDbh <= p_fSizeClass1[p_oTree->GetSpecies()])
        p_iTreeCount[p_oTree->GetSpecies()][0]++;
      else if (fDbh <= p_fSizeClass2[p_oTree->GetSpecies()])
        p_iTreeCount[p_oTree->GetSpecies()][1]++;
      else
        p_iTreeCount[p_oTree->GetSpecies()][2]++;

      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_LT(p_iTreeCount[0][0], 11);
    fExpected = 980.0562787;
    EXPECT_LT(fabs(p_iTreeCount[0][1] - fExpected)/fExpected, 0.05);
    fExpected = 78.78516157;
    EXPECT_LT(fabs(p_iTreeCount[0][2] - fExpected)/fExpected, 0.15);
    EXPECT_EQ(p_iTreeCount[1][0], 1000);
    EXPECT_EQ(p_iTreeCount[1][1], 1000);
    EXPECT_EQ(p_iTreeCount[1][2], 1000);
    fExpected = 948.6319594;
    EXPECT_LT(fabs(p_iTreeCount[2][0] - fExpected)/fExpected, 0.05);
    fExpected = 161.6211925;
    EXPECT_LT(fabs(p_iTreeCount[2][1] - fExpected)/fExpected, 0.1);
    fExpected = 949.521718;
    EXPECT_LT(fabs(p_iTreeCount[2][2] - fExpected)/fExpected, 0.05);
    EXPECT_LT(p_iTreeCount[3][0], 2);
    EXPECT_LT(p_iTreeCount[3][1], 2);
    EXPECT_LT(p_iTreeCount[3][2], 2);

    //*****************Timestep 7************************
    p_oSimManager->RunSim(1);
    //Zero out the array and re-count
    for (i = 0; i < iNumSpecies; i++) {
      for (j = 0; j < iNumSizeClasses; j++) {
        p_iTreeCount[i][j] = 0;
      }
    }
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      EXPECT_EQ(p_oTree->GetType(), clTreePopulation::snag);
      p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDbh);

      if (fDbh <= p_fSizeClass1[p_oTree->GetSpecies()])
        p_iTreeCount[p_oTree->GetSpecies()][0]++;
      else if (fDbh <= p_fSizeClass2[p_oTree->GetSpecies()])
        p_iTreeCount[p_oTree->GetSpecies()][1]++;
      else
        p_iTreeCount[p_oTree->GetSpecies()][2]++;

      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_LT(p_iTreeCount[0][0], 5);
    fExpected = 970.3615655;
    EXPECT_LT(fabs(p_iTreeCount[0][1] - fExpected)/fExpected, 0.05);
    fExpected = 20.96716446;
    EXPECT_LT(fabs(p_iTreeCount[0][2] - fExpected)/fExpected, 0.2);
    EXPECT_EQ(p_iTreeCount[1][0], 1000);
    EXPECT_EQ(p_iTreeCount[1][1], 1000);
    EXPECT_EQ(p_iTreeCount[1][2], 1000);
    fExpected = 912.9035908;
    EXPECT_LT(fabs(p_iTreeCount[2][0] - fExpected)/fExpected, 0.05);
    fExpected = 72.48323393;
    EXPECT_LT(fabs(p_iTreeCount[2][1] - fExpected)/fExpected, 0.27);
    fExpected = 921.5423789;
    EXPECT_LT(fabs(p_iTreeCount[2][2] - fExpected)/fExpected, 0.05);
    EXPECT_LT(p_iTreeCount[3][0], 2);
    EXPECT_LT(p_iTreeCount[3][1], 2);
    EXPECT_LT(p_iTreeCount[3][2], 2);

    //*****************Timestep 8************************
    p_oSimManager->RunSim(1);
    //Zero out the array and re-count
    for (i = 0; i < iNumSpecies; i++) {
      for (j = 0; j < iNumSizeClasses; j++) {
        p_iTreeCount[i][j] = 0;
      }
    }
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      EXPECT_EQ(p_oTree->GetType(), clTreePopulation::snag);
      p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDbh);

      if (fDbh <= p_fSizeClass1[p_oTree->GetSpecies()])
        p_iTreeCount[p_oTree->GetSpecies()][0]++;
      else if (fDbh <= p_fSizeClass2[p_oTree->GetSpecies()])
        p_iTreeCount[p_oTree->GetSpecies()][1]++;
      else
        p_iTreeCount[p_oTree->GetSpecies()][2]++;

      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(p_iTreeCount[0][0], 0 || p_iTreeCount[0][0] == 1);
    fExpected = 958.6461017;
    EXPECT_LT(fabs(p_iTreeCount[0][1] - fExpected)/fExpected, 0.05);
    EXPECT_LT(p_iTreeCount[0][2], 11);
    EXPECT_EQ(p_iTreeCount[1][0], 1000);
    EXPECT_EQ(p_iTreeCount[1][1], 1000);
    EXPECT_EQ(p_iTreeCount[1][2], 1000);
    fExpected = 865.2791347;
    EXPECT_LT(fabs(p_iTreeCount[2][0] - fExpected)/fExpected, 0.05);
    fExpected = 28.09678843;
    EXPECT_LT(fabs(p_iTreeCount[2][1] - fExpected)/fExpected, 0.22);
    fExpected = 886.811969;
    EXPECT_LT(fabs(p_iTreeCount[2][2] - fExpected)/fExpected, 0.05);
    EXPECT_LT(p_iTreeCount[3][0], 2);
    EXPECT_LT(p_iTreeCount[3][1], 2);
    EXPECT_LT(p_iTreeCount[3][2], 2);

    //*****************Timestep 9************************
    p_oSimManager->RunSim(1);
    //Zero out the array and re-count
    for (i = 0; i < iNumSpecies; i++) {
      for (j = 0; j < iNumSizeClasses; j++) {
        p_iTreeCount[i][j] = 0;
      }
    }
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      EXPECT_EQ(p_oTree->GetType(), clTreePopulation::snag);
      p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDbh);

      if (fDbh <= p_fSizeClass1[p_oTree->GetSpecies()])
        p_iTreeCount[p_oTree->GetSpecies()][0]++;
      else if (fDbh <= p_fSizeClass2[p_oTree->GetSpecies()])
        p_iTreeCount[p_oTree->GetSpecies()][1]++;
      else
        p_iTreeCount[p_oTree->GetSpecies()][2]++;

      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(p_iTreeCount[0][0], 0);
    fExpected = 944.920126;
    EXPECT_LT(fabs(p_iTreeCount[0][1] - fExpected)/fExpected, 0.05);
    EXPECT_LT(p_iTreeCount[0][2], 5);
    EXPECT_EQ(p_iTreeCount[1][0], 1000);
    EXPECT_EQ(p_iTreeCount[1][1], 1000);
    EXPECT_EQ(p_iTreeCount[1][2], 1000);
    fExpected = 805.7353019;
    EXPECT_LT(fabs(p_iTreeCount[2][0] - fExpected)/fExpected, 0.05);
    EXPECT_LT(p_iTreeCount[2][1], 16);
    fExpected = 845.5844702;
    EXPECT_LT(fabs(p_iTreeCount[2][2] - fExpected)/fExpected, 0.05);
    EXPECT_LT(p_iTreeCount[3][0], 2);
    EXPECT_LT(p_iTreeCount[3][1], 2);
    EXPECT_LT(p_iTreeCount[3][2], 2);

    //*****************Timestep 10************************
    p_oSimManager->RunSim(1);
    //Zero out the array and re-count
    for (i = 0; i < iNumSpecies; i++) {
      for (j = 0; j < iNumSizeClasses; j++) {
        p_iTreeCount[i][j] = 0;
      }
    }
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      EXPECT_EQ(p_oTree->GetType(), clTreePopulation::snag);
      p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDbh);

      if (fDbh <= p_fSizeClass1[p_oTree->GetSpecies()])
        p_iTreeCount[p_oTree->GetSpecies()][0]++;
      else if (fDbh <= p_fSizeClass2[p_oTree->GetSpecies()])
        p_iTreeCount[p_oTree->GetSpecies()][1]++;
      else
        p_iTreeCount[p_oTree->GetSpecies()][2]++;

      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(p_iTreeCount[0][0], 0);
    fExpected = 929.2170022;
    EXPECT_LT(fabs(p_iTreeCount[0][1] - fExpected)/fExpected, 0.05);
    EXPECT_EQ(p_iTreeCount[0][2], 0 || p_iTreeCount[0][2] == 1);
    EXPECT_EQ(p_iTreeCount[1][0], 1000);
    EXPECT_EQ(p_iTreeCount[1][1], 1000);
    EXPECT_EQ(p_iTreeCount[1][2], 1000);
    fExpected = 735.248402;
    EXPECT_LT(fabs(p_iTreeCount[2][0] - fExpected)/fExpected, 0.05);
    fExpected = 2.726054373;
    EXPECT_LT(p_iTreeCount[2][1], 11);
    fExpected = 798.3911201;
    EXPECT_LT(fabs(p_iTreeCount[2][2] - fExpected)/fExpected, 0.05);
    EXPECT_LT(p_iTreeCount[3][0], 2);
    EXPECT_LT(p_iTreeCount[3][1], 2);
    EXPECT_LT(p_iTreeCount[3][2], 2);

    //*****************Timestep 31************************
    p_oSimManager->RunSim(21);
    //Zero out the array and re-count
    for (i = 0; i < iNumSpecies; i++) {
      for (j = 0; j < iNumSizeClasses; j++) {
        p_iTreeCount[i][j] = 0;
      }
    }
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      EXPECT_EQ(p_oTree->GetType(), clTreePopulation::snag);
      p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDbh);

      if (fDbh <= p_fSizeClass1[p_oTree->GetSpecies()])
        p_iTreeCount[p_oTree->GetSpecies()][0]++;
      else if (fDbh <= p_fSizeClass2[p_oTree->GetSpecies()])
        p_iTreeCount[p_oTree->GetSpecies()][1]++;
      else
        p_iTreeCount[p_oTree->GetSpecies()][2]++;

      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(p_iTreeCount[0][0], 0);
    fExpected = 354.2395461;
    EXPECT_LT(fabs(p_iTreeCount[0][1] - fExpected)/fExpected, 0.05);
    EXPECT_EQ(p_iTreeCount[0][2], 0);
    EXPECT_EQ(p_iTreeCount[1][0], 1000);
    EXPECT_EQ(p_iTreeCount[1][1], 1000);
    EXPECT_EQ(p_iTreeCount[1][2], 1000);
    EXPECT_EQ(p_iTreeCount[2][0], 0 || p_iTreeCount[2][0] == 1);
    EXPECT_EQ(p_iTreeCount[2][1], 0);
    EXPECT_LT(p_iTreeCount[2][2], 20);
    EXPECT_LT(p_iTreeCount[3][0], 2);
    EXPECT_LT(p_iTreeCount[3][1], 2);
    EXPECT_LT(p_iTreeCount[3][2], 2);

    //Cleanup
    for (i = 0; i < iNumSpecies; i++) delete[] p_iTreeCount[i];
    delete[] p_iTreeCount;
    delete[] p_fSizeClass1;
    delete[] p_fSizeClass2;
    delete p_oSimManager;
  } catch (modelErr &e) {
    for (i = 0; i < iNumSpecies; i++) delete[] p_iTreeCount[i];
    delete[] p_iTreeCount;
    delete[] p_fSizeClass1;
    delete[] p_fSizeClass2;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// WriteWeibullSnagMortXMLFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteWeibullSnagMortXMLFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>50</timesteps>"
       << "<randomSeed>1</randomSeed>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<plot_lenX>200.0</plot_lenX>"
       << "<plot_lenY>200.0</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>0.0</plot_latitude>"
       << "</plot>"
       << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\" />"
       << "<tr_species speciesName=\"Species_2\" />"
       << "<tr_species speciesName=\"Species_3\" />"
       << "<tr_species speciesName=\"Species_4\" />"
       << "</tr_speciesList>"
       << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
       << "<tr_minAdultDBH>"
       << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_2\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_3\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_4\">10.0</tr_madVal>"
       << "</tr_minAdultDBH>"
       << "<tr_maxSeedlingHeight>"
       << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_2\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_3\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_4\">1.35</tr_mshVal>"
       << "</tr_maxSeedlingHeight>"
       << "</trees>"
       << "<allometry>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"Species_1\">40.0</tr_chVal>"
       << "<tr_chVal species=\"Species_2\">40.0</tr_chVal>"
       << "<tr_chVal species=\"Species_3\">40.0</tr_chVal>"
       << "<tr_chVal species=\"Species_4\">40.0</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.7</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_2\">0.7</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_3\">0.7</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_4\">0.7</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_3\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_4\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_stdMaxCrownRad>"
       << "<tr_smcrVal species=\"Species_1\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_2\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_3\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_4\">10</tr_smcrVal>"
       << "</tr_stdMaxCrownRad>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">0.7</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">0.7</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_3\">0.7</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_4\">0.7</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_3\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_4\">0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.7</tr_sachVal>"
       << "<tr_sachVal species=\"Species_2\">0.7</tr_sachVal>"
       << "<tr_sachVal species=\"Species_3\">0.7</tr_sachVal>"
       << "<tr_sachVal species=\"Species_4\">0.7</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_3\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_4\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"Species_1\">0.03</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_2\">0.03</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_3\">0.03</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_4\">0.03</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.7</tr_soahVal>"
       << "<tr_soahVal species=\"Species_2\">0.7</tr_soahVal>"
       << "<tr_soahVal species=\"Species_3\">0.7</tr_soahVal>"
       << "<tr_soahVal species=\"Species_4\">0.7</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
       << "<tr_whatSeedlingHeightDiam>"
       << "<tr_wsehdVal species=\"Species_1\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_2\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_3\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_4\">0</tr_wsehdVal>"
       << "</tr_whatSeedlingHeightDiam>"
       << "<tr_whatSaplingHeightDiam>"
       << "<tr_wsahdVal species=\"Species_1\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_2\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_3\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_4\">0</tr_wsahdVal>"
       << "</tr_whatSaplingHeightDiam>"
       << "<tr_whatAdultHeightDiam>"
       << "<tr_wahdVal species=\"Species_1\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_2\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_3\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_4\">0</tr_wahdVal>"
       << "</tr_whatAdultHeightDiam>"
       << "<tr_whatAdultCrownRadDiam>"
       << "<tr_wacrdVal species=\"Species_1\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_2\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_3\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_4\">0</tr_wacrdVal>"
       << "</tr_whatAdultCrownRadDiam>"
       << "<tr_whatAdultCrownHeightHeight>"
       << "<tr_wachhVal species=\"Species_1\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_2\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_3\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_4\">0</tr_wachhVal>"
       << "</tr_whatAdultCrownHeightHeight>"
       << "<tr_whatSaplingCrownRadDiam>"
       << "<tr_wscrdVal species=\"Species_1\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_2\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_3\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_4\">0</tr_wscrdVal>"
       << "</tr_whatSaplingCrownRadDiam>"
       << "<tr_whatSaplingCrownHeightHeight>"
       << "<tr_wschhVal species=\"Species_1\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_2\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_3\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_4\">0</tr_wschhVal>"
       << "</tr_whatSaplingCrownHeightHeight>"
       << "</allometry>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>WeibullSnagMortality</behaviorName>"
       << "<version>1.1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Snag\" />"
       << "<applyTo species=\"Species_3\" type=\"Snag\" />"
       << "<applyTo species=\"Species_4\" type=\"Snag\" />"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RemoveDead</behaviorName>"
       << "<listPosition>2</listPosition>"
       << "<version>2.0</version>"
       << "<applyTo species=\"Species_1\" type=\"Snag\" />"
       << "<applyTo species=\"Species_3\" type=\"Snag\" />"
       << "<applyTo species=\"Species_4\" type=\"Snag\" />"
       << "</behavior>"
       << "</behaviorList>"
       << "<WeibullSnagMortality1>"
       << "<mo_snagSizeClass1DBH>"
       << "<mo_sc1dVal species=\"Species_3\">31</mo_sc1dVal>"
       << "<mo_sc1dVal species=\"Species_1\">12</mo_sc1dVal>"
       << "<mo_sc1dVal species=\"Species_4\">12</mo_sc1dVal>"
       << "</mo_snagSizeClass1DBH>"
       << "<mo_snagSizeClass2DBH>"
       << "<mo_sc2dVal species=\"Species_3\">39</mo_sc2dVal>"
       << "<mo_sc2dVal species=\"Species_1\">30</mo_sc2dVal>"
       << "<mo_sc2dVal species=\"Species_4\">30</mo_sc2dVal>"
       << "</mo_snagSizeClass2DBH>"
       << "<mo_snag1WeibullA>"
       << "<mo_s1waVal species=\"Species_3\">0.025</mo_s1waVal>"
       << "<mo_s1waVal species=\"Species_1\">0.113</mo_s1waVal>"
       << "<mo_s1waVal species=\"Species_4\">11.51</mo_s1waVal>"
       << "</mo_snag1WeibullA>"
       << "<mo_snag2WeibullA>"
       << "<mo_s2waVal species=\"Species_3\">0.09</mo_s2waVal>"
       << "<mo_s2waVal species=\"Species_1\">0.0113</mo_s2waVal>"
       << "<mo_s2waVal species=\"Species_4\">11.51</mo_s2waVal>"
       << "</mo_snag2WeibullA>"
       << "<mo_snag3WeibullA>"
       << "<mo_s3waVal species=\"Species_3\">0.0204</mo_s3waVal>"
       << "<mo_s3waVal species=\"Species_1\">0.1</mo_s3waVal>"
       << "<mo_s3waVal species=\"Species_4\">11.51</mo_s3waVal>"
       << "</mo_snag3WeibullA>"
       << "<mo_snag1WeibullB>"
       << "<mo_s1wbVal species=\"Species_3\">3</mo_s1wbVal>"
       << "<mo_s1wbVal species=\"Species_1\">3.049</mo_s1wbVal>"
       << "<mo_s1wbVal species=\"Species_4\">1</mo_s1wbVal>"
       << "</mo_snag1WeibullB>"
       << "<mo_snag2WeibullB>"
       << "<mo_s2wbVal species=\"Species_3\">2</mo_s2wbVal>"
       << "<mo_s2wbVal species=\"Species_1\">2.2</mo_s2wbVal>"
       << "<mo_s2wbVal species=\"Species_4\">1</mo_s2wbVal>"
       << "</mo_snag2WeibullB>"
       << "<mo_snag3WeibullB>"
       << "<mo_s3wbVal species=\"Species_3\">2.5</mo_s3wbVal>"
       << "<mo_s3wbVal species=\"Species_1\">2.3</mo_s3wbVal>"
       << "<mo_s3wbVal species=\"Species_4\">1</mo_s3wbVal>"
       << "</mo_snag3WeibullB>"
       << "</WeibullSnagMortality1>"
       << "</paramFile>";
  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteWeibullSnagMortXMLFile2()
/////////////////////////////////////////////////////////////////////////////
const char* WriteWeibullSnagMortXMLFile2() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>35</timesteps>"
       << "<randomSeed>1</randomSeed>"
       << "<yearsPerTimestep>3</yearsPerTimestep>"
       << "<plot_lenX>200.0</plot_lenX>"
       << "<plot_lenY>200.0</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>0.0</plot_latitude>"
       << "</plot>"
       << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\" />"
       << "<tr_species speciesName=\"Species_2\" />"
       << "<tr_species speciesName=\"Species_3\" />"
       << "<tr_species speciesName=\"Species_4\" />"
       << "</tr_speciesList>"
       << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
       << "<tr_minAdultDBH>"
       << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_2\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_3\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_4\">10.0</tr_madVal>"
       << "</tr_minAdultDBH>"
       << "<tr_maxSeedlingHeight>"
       << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_2\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_3\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_4\">1.35</tr_mshVal>"
       << "</tr_maxSeedlingHeight>"
       << "</trees>"
       << "<allometry>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"Species_1\">40.0</tr_chVal>"
       << "<tr_chVal species=\"Species_2\">40.0</tr_chVal>"
       << "<tr_chVal species=\"Species_3\">40.0</tr_chVal>"
       << "<tr_chVal species=\"Species_4\">40.0</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.7</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_2\">0.7</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_3\">0.7</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_4\">0.7</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_3\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_4\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_stdMaxCrownRad>"
       << "<tr_smcrVal species=\"Species_1\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_2\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_3\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_4\">10</tr_smcrVal>"
       << "</tr_stdMaxCrownRad>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">0.7</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">0.7</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_3\">0.7</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_4\">0.7</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_3\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_4\">0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.7</tr_sachVal>"
       << "<tr_sachVal species=\"Species_2\">0.7</tr_sachVal>"
       << "<tr_sachVal species=\"Species_3\">0.7</tr_sachVal>"
       << "<tr_sachVal species=\"Species_4\">0.7</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_3\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_4\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"Species_1\">0.03</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_2\">0.03</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_3\">0.03</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_4\">0.03</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.7</tr_soahVal>"
       << "<tr_soahVal species=\"Species_2\">0.7</tr_soahVal>"
       << "<tr_soahVal species=\"Species_3\">0.7</tr_soahVal>"
       << "<tr_soahVal species=\"Species_4\">0.7</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
       << "<tr_whatSeedlingHeightDiam>"
       << "<tr_wsehdVal species=\"Species_1\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_2\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_3\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_4\">0</tr_wsehdVal>"
       << "</tr_whatSeedlingHeightDiam>"
       << "<tr_whatSaplingHeightDiam>"
       << "<tr_wsahdVal species=\"Species_1\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_2\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_3\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_4\">0</tr_wsahdVal>"
       << "</tr_whatSaplingHeightDiam>"
       << "<tr_whatAdultHeightDiam>"
       << "<tr_wahdVal species=\"Species_1\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_2\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_3\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_4\">0</tr_wahdVal>"
       << "</tr_whatAdultHeightDiam>"
       << "<tr_whatAdultCrownRadDiam>"
       << "<tr_wacrdVal species=\"Species_1\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_2\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_3\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_4\">0</tr_wacrdVal>"
       << "</tr_whatAdultCrownRadDiam>"
       << "<tr_whatAdultCrownHeightHeight>"
       << "<tr_wachhVal species=\"Species_1\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_2\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_3\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_4\">0</tr_wachhVal>"
       << "</tr_whatAdultCrownHeightHeight>"
       << "<tr_whatSaplingCrownRadDiam>"
       << "<tr_wscrdVal species=\"Species_1\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_2\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_3\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_4\">0</tr_wscrdVal>"
       << "</tr_whatSaplingCrownRadDiam>"
       << "<tr_whatSaplingCrownHeightHeight>"
       << "<tr_wschhVal species=\"Species_1\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_2\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_3\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_4\">0</tr_wschhVal>"
       << "</tr_whatSaplingCrownHeightHeight>"
       << "</allometry>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>WeibullSnagMortality</behaviorName>"
       << "<version>1.1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Snag\" />"
       << "<applyTo species=\"Species_3\" type=\"Snag\" />"
       << "<applyTo species=\"Species_4\" type=\"Snag\" />"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RemoveDead</behaviorName>"
       << "<version>2.0</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Snag\" />"
       << "<applyTo species=\"Species_3\" type=\"Snag\" />"
       << "<applyTo species=\"Species_4\" type=\"Snag\" />"
       << "</behavior>"
       << "</behaviorList>"
       << "<WeibullSnagMortality1>"
       << "<mo_snagSizeClass1DBH>"
       << "<mo_sc1dVal species=\"Species_3\">31</mo_sc1dVal>"
       << "<mo_sc1dVal species=\"Species_1\">12</mo_sc1dVal>"
       << "<mo_sc1dVal species=\"Species_4\">12</mo_sc1dVal>"
       << "</mo_snagSizeClass1DBH>"
       << "<mo_snagSizeClass2DBH>"
       << "<mo_sc2dVal species=\"Species_3\">39</mo_sc2dVal>"
       << "<mo_sc2dVal species=\"Species_1\">30</mo_sc2dVal>"
       << "<mo_sc2dVal species=\"Species_4\">30</mo_sc2dVal>"
       << "</mo_snagSizeClass2DBH>"
       << "<mo_snag1WeibullA>"
       << "<mo_s1waVal species=\"Species_3\">0.025</mo_s1waVal>"
       << "<mo_s1waVal species=\"Species_1\">0.113</mo_s1waVal>"
       << "<mo_s1waVal species=\"Species_4\">11.51</mo_s1waVal>"
       << "</mo_snag1WeibullA>"
       << "<mo_snag2WeibullA>"
       << "<mo_s2waVal species=\"Species_3\">0.09</mo_s2waVal>"
       << "<mo_s2waVal species=\"Species_1\">0.0113</mo_s2waVal>"
       << "<mo_s2waVal species=\"Species_4\">11.51</mo_s2waVal>"
       << "</mo_snag2WeibullA>"
       << "<mo_snag3WeibullA>"
       << "<mo_s3waVal species=\"Species_3\">0.0204</mo_s3waVal>"
       << "<mo_s3waVal species=\"Species_1\">0.1</mo_s3waVal>"
       << "<mo_s3waVal species=\"Species_4\">11.51</mo_s3waVal>"
       << "</mo_snag3WeibullA>"
       << "<mo_snag1WeibullB>"
       << "<mo_s1wbVal species=\"Species_3\">3</mo_s1wbVal>"
       << "<mo_s1wbVal species=\"Species_1\">3.049</mo_s1wbVal>"
       << "<mo_s1wbVal species=\"Species_4\">1</mo_s1wbVal>"
       << "</mo_snag1WeibullB>"
       << "<mo_snag2WeibullB>"
       << "<mo_s2wbVal species=\"Species_3\">2</mo_s2wbVal>"
       << "<mo_s2wbVal species=\"Species_1\">2.2</mo_s2wbVal>"
       << "<mo_s2wbVal species=\"Species_4\">1</mo_s2wbVal>"
       << "</mo_snag2WeibullB>"
       << "<mo_snag3WeibullB>"
       << "<mo_s3wbVal species=\"Species_3\">2.5</mo_s3wbVal>"
       << "<mo_s3wbVal species=\"Species_1\">2.3</mo_s3wbVal>"
       << "<mo_s3wbVal species=\"Species_4\">1</mo_s3wbVal>"
       << "</mo_snag3WeibullB>"
       << "</WeibullSnagMortality1>"
       << "</paramFile>";
  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteWeibullSnagMortXMLErrorFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteWeibullSnagMortXMLErrorFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>11</timesteps>"
       << "<randomSeed>1</randomSeed>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<plot_lenX>200.0</plot_lenX>"
       << "<plot_lenY>200.0</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>0.0</plot_latitude>"
       << "</plot>"
       << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\" />"
       << "<tr_species speciesName=\"Species_2\" />"
       << "<tr_species speciesName=\"Species_3\" />"
       << "</tr_speciesList>"
       << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
       << "<tr_minAdultDBH>"
       << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_2\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_3\">10.0</tr_madVal>"
       << "</tr_minAdultDBH>"
       << "<tr_maxSeedlingHeight>"
       << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_2\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_3\">1.35</tr_mshVal>"
       << "</tr_maxSeedlingHeight>"
       << "</trees>"
       << "<allometry>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"Species_1\">40.0</tr_chVal>"
       << "<tr_chVal species=\"Species_2\">40.0</tr_chVal>"
       << "<tr_chVal species=\"Species_3\">40.0</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.7</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_2\">0.7</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_3\">0.7</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_3\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_stdMaxCrownRad>"
       << "<tr_smcrVal species=\"Species_1\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_2\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_3\">10</tr_smcrVal>"
       << "</tr_stdMaxCrownRad>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">0.7</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">0.7</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_3\">0.7</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_3\">0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.7</tr_sachVal>"
       << "<tr_sachVal species=\"Species_2\">0.7</tr_sachVal>"
       << "<tr_sachVal species=\"Species_3\">0.7</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_3\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"Species_1\">0.03</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_2\">0.03</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_3\">0.03</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.7</tr_soahVal>"
       << "<tr_soahVal species=\"Species_2\">0.7</tr_soahVal>"
       << "<tr_soahVal species=\"Species_3\">0.7</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
       << "<tr_whatSeedlingHeightDiam>"
       << "<tr_wsehdVal species=\"Species_1\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_2\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_3\">0</tr_wsehdVal>"
       << "</tr_whatSeedlingHeightDiam>"
       << "<tr_whatSaplingHeightDiam>"
       << "<tr_wsahdVal species=\"Species_1\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_2\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_3\">0</tr_wsahdVal>"
       << "</tr_whatSaplingHeightDiam>"
       << "<tr_whatAdultHeightDiam>"
       << "<tr_wahdVal species=\"Species_1\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_2\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_3\">0</tr_wahdVal>"
       << "</tr_whatAdultHeightDiam>"
       << "<tr_whatAdultCrownRadDiam>"
       << "<tr_wacrdVal species=\"Species_1\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_2\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_3\">0</tr_wacrdVal>"
       << "</tr_whatAdultCrownRadDiam>"
       << "<tr_whatAdultCrownHeightHeight>"
       << "<tr_wachhVal species=\"Species_1\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_2\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_3\">0</tr_wachhVal>"
       << "</tr_whatAdultCrownHeightHeight>"
       << "<tr_whatSaplingCrownRadDiam>"
       << "<tr_wscrdVal species=\"Species_1\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_2\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_3\">0</tr_wscrdVal>"
       << "</tr_whatSaplingCrownRadDiam>"
       << "<tr_whatSaplingCrownHeightHeight>"
       << "<tr_wschhVal species=\"Species_1\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_2\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_3\">0</tr_wschhVal>"
       << "</tr_whatSaplingCrownHeightHeight>"
       << "</allometry>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>WeibullSnagMortality</behaviorName>"
       << "<version>1.1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Snag\" />"
       << "<applyTo species=\"Species_3\" type=\"Snag\" />"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RemoveDead</behaviorName>"
       << "<version>2.0</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Snag\" />"
       << "<applyTo species=\"Species_3\" type=\"Snag\" />"
       << "</behavior>"
       << "</behaviorList>"
       << "<WeibullSnagMortality1>"
       << "<mo_snagSizeClass1DBH>"
       << "<mo_sc1dVal species=\"Species_3\">31</mo_sc1dVal>"
       << "<mo_sc1dVal species=\"Species_1\">40</mo_sc1dVal>"
       << "</mo_snagSizeClass1DBH>"
       << "<mo_snagSizeClass2DBH>"
       << "<mo_sc2dVal species=\"Species_3\">39</mo_sc2dVal>"
       << "<mo_sc2dVal species=\"Species_1\">30</mo_sc2dVal>"
       << "</mo_snagSizeClass2DBH>"
       << "<mo_snag1WeibullA>"
       << "<mo_s1waVal species=\"Species_3\">0.0025</mo_s1waVal>"
       << "<mo_s1waVal species=\"Species_1\">0.0013</mo_s1waVal>"
       << "</mo_snag1WeibullA>"
       << "<mo_snag2WeibullA>"
       << "<mo_s2waVal species=\"Species_3\">0.0009</mo_s2waVal>"
       << "<mo_s2waVal species=\"Species_1\">0.0113</mo_s2waVal>"
       << "</mo_snag2WeibullA>"
       << "<mo_snag3WeibullA>"
       << "<mo_s3waVal species=\"Species_3\">0.0204</mo_s3waVal>"
       << "<mo_s3waVal species=\"Species_1\">0.1</mo_s3waVal>"
       << "</mo_snag3WeibullA>"
       << "<mo_snag1WeibullB>"
       << "<mo_s1wbVal species=\"Species_3\">4</mo_s1wbVal>"
       << "<mo_s1wbVal species=\"Species_1\">2.1</mo_s1wbVal>"
      << "</mo_snag1WeibullB>"
      << "<mo_snag2WeibullB>"
      << "<mo_s2wbVal species=\"Species_3\">1</mo_s2wbVal>"
      << "<mo_s2wbVal species=\"Species_1\">2.2</mo_s2wbVal>"
      << "</mo_snag2WeibullB>"
      << "<mo_snag3WeibullB>"
      << "<mo_s3wbVal species=\"Species_3\">2.5</mo_s3wbVal>"
      << "<mo_s3wbVal species=\"Species_1\">2.3</mo_s3wbVal>"
      << "</mo_snag3WeibullB>"
       << "</WeibullSnagMortality1>"
       << "</paramFile>";
  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteWeibullSnagMortXMLErrorFile2()
/////////////////////////////////////////////////////////////////////////////
const char* WriteWeibullSnagMortXMLErrorFile2() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>11</timesteps>"
       << "<randomSeed>1</randomSeed>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<plot_lenX>200.0</plot_lenX>"
       << "<plot_lenY>200.0</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>0.0</plot_latitude>"
       << "</plot>"
       << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\" />"
       << "<tr_species speciesName=\"Species_2\" />"
       << "<tr_species speciesName=\"Species_3\" />"
       << "</tr_speciesList>"
       << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
       << "<tr_minAdultDBH>"
       << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_2\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_3\">10.0</tr_madVal>"
       << "</tr_minAdultDBH>"
       << "<tr_maxSeedlingHeight>"
       << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_2\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_3\">1.35</tr_mshVal>"
       << "</tr_maxSeedlingHeight>"
       << "</trees>"
       << "<allometry>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"Species_1\">40.0</tr_chVal>"
       << "<tr_chVal species=\"Species_2\">40.0</tr_chVal>"
       << "<tr_chVal species=\"Species_3\">40.0</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.7</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_2\">0.7</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_3\">0.7</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_3\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_stdMaxCrownRad>"
       << "<tr_smcrVal species=\"Species_1\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_2\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_3\">10</tr_smcrVal>"
       << "</tr_stdMaxCrownRad>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">0.7</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">0.7</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_3\">0.7</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_3\">0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.7</tr_sachVal>"
       << "<tr_sachVal species=\"Species_2\">0.7</tr_sachVal>"
       << "<tr_sachVal species=\"Species_3\">0.7</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_3\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"Species_1\">0.03</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_2\">0.03</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_3\">0.03</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.7</tr_soahVal>"
       << "<tr_soahVal species=\"Species_2\">0.7</tr_soahVal>"
       << "<tr_soahVal species=\"Species_3\">0.7</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
       << "<tr_whatSeedlingHeightDiam>"
       << "<tr_wsehdVal species=\"Species_1\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_2\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_3\">0</tr_wsehdVal>"
       << "</tr_whatSeedlingHeightDiam>"
       << "<tr_whatSaplingHeightDiam>"
       << "<tr_wsahdVal species=\"Species_1\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_2\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_3\">0</tr_wsahdVal>"
       << "</tr_whatSaplingHeightDiam>"
       << "<tr_whatAdultHeightDiam>"
       << "<tr_wahdVal species=\"Species_1\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_2\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_3\">0</tr_wahdVal>"
       << "</tr_whatAdultHeightDiam>"
       << "<tr_whatAdultCrownRadDiam>"
       << "<tr_wacrdVal species=\"Species_1\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_2\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_3\">0</tr_wacrdVal>"
       << "</tr_whatAdultCrownRadDiam>"
       << "<tr_whatAdultCrownHeightHeight>"
       << "<tr_wachhVal species=\"Species_1\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_2\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_3\">0</tr_wachhVal>"
       << "</tr_whatAdultCrownHeightHeight>"
       << "<tr_whatSaplingCrownRadDiam>"
       << "<tr_wscrdVal species=\"Species_1\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_2\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_3\">0</tr_wscrdVal>"
       << "</tr_whatSaplingCrownRadDiam>"
       << "<tr_whatSaplingCrownHeightHeight>"
       << "<tr_wschhVal species=\"Species_1\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_2\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_3\">0</tr_wschhVal>"
       << "</tr_whatSaplingCrownHeightHeight>"
       << "</allometry>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>WeibullSnagMortality</behaviorName>"
       << "<version>1.1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Snag\" />"
       << "<applyTo species=\"Species_3\" type=\"Adult\" />"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RemoveDead</behaviorName>"
       << "<version>2.0</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Snag\" />"
       << "<applyTo species=\"Species_3\" type=\"Snag\" />"
       << "</behavior>"
       << "</behaviorList>"
       << "<WeibullSnagMortality1>"
       << "<mo_snagSizeClass1DBH>"
       << "<mo_sc1dVal species=\"Species_3\">31</mo_sc1dVal>"
       << "<mo_sc1dVal species=\"Species_1\">12</mo_sc1dVal>"
       << "</mo_snagSizeClass1DBH>"
       << "<mo_snagSizeClass2DBH>"
       << "<mo_sc2dVal species=\"Species_3\">39</mo_sc2dVal>"
       << "<mo_sc2dVal species=\"Species_1\">30</mo_sc2dVal>"
       << "</mo_snagSizeClass2DBH>"
       << "<mo_snag1WeibullA>"
       << "<mo_s1waVal species=\"Species_3\">0.0025</mo_s1waVal>"
       << "<mo_s1waVal species=\"Species_1\">0.0013</mo_s1waVal>"
       << "</mo_snag1WeibullA>"
       << "<mo_snag2WeibullA>"
       << "<mo_s2waVal species=\"Species_3\">0.0009</mo_s2waVal>"
       << "<mo_s2waVal species=\"Species_1\">0.0113</mo_s2waVal>"
       << "</mo_snag2WeibullA>"
       << "<mo_snag3WeibullA>"
       << "<mo_s3waVal species=\"Species_3\">0.0204</mo_s3waVal>"
       << "<mo_s3waVal species=\"Species_1\">0.1</mo_s3waVal>"
       << "</mo_snag3WeibullA>"
       << "<mo_snag1WeibullB>"
       << "<mo_s1wbVal species=\"Species_3\">4</mo_s1wbVal>"
       << "<mo_s1wbVal species=\"Species_1\">2.1</mo_s1wbVal>"
       << "</mo_snag1WeibullB>"
       << "<mo_snag2WeibullB>"
       << "<mo_s2wbVal species=\"Species_3\">1</mo_s2wbVal>"
       << "<mo_s2wbVal species=\"Species_1\">2.2</mo_s2wbVal>"
       << "</mo_snag2WeibullB>"
       << "<mo_snag3WeibullB>"
       << "<mo_s3wbVal species=\"Species_3\">2.5</mo_s3wbVal>"
       << "<mo_s3wbVal species=\"Species_1\">2.3</mo_s3wbVal>"
       << "</mo_snag3WeibullB>"
       << "</WeibullSnagMortality1>"
       << "</paramFile>";
  oOut.close();

  return cFileString;
}
