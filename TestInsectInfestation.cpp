//---------------------------------------------------------------------------
// TestInsectInfestation.cpp
//---------------------------------------------------------------------------
#include "TestInsectInfestation.h"
#include <gtest/gtest.h>
#include "SimManager.h"
#include "Grid.h"
#include "TreePopulation.h"
#include "Storm.h"
#include <fstream>
#include <sstream>
#include <math.h>

////////////////////////////////////////////////////////////////////////////
// TestErrorProcessing()
////////////////////////////////////////////////////////////////////////////
TEST(InsectInfestation, TestErrorProcessing)
{
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try
  {
    p_oSimManager->ReadFile( WriteInsectInfestationXMLErrorFile1() );
    FAIL() << "TestInsectInfestation error processing didn't catch error for WriteInsectInfestationXMLErrorFile1.";
  }
  catch ( modelErr& err )
  {
    if ( err.sFunction.compare("clInsectInfestation::ReadParFile" ) != 0 )
    {
      FAIL() << "TestInsectInfestation error processing caught wrong error for WriteInsectInfestationXMLErrorFile1.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile( WriteInsectInfestationXMLErrorFile2() );
    FAIL() << "TestInsectInfestation error processing didn't catch error for WriteInsectInfestationXMLErrorFile2.";
  }
  catch ( modelErr& err )
  {
    if ( err.sFunction.compare("clInsectInfestation::RegisterTreeDataMembers" ) != 0 )
    {
      FAIL() << "TestInsectInfestation error processing caught wrong error for WriteInsectInfestationXMLErrorFile2.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile( WriteInsectInfestationXMLErrorFile3() );
    FAIL() << "TestInsectInfestation error processing didn't catch error for WriteInsectInfestationXMLErrorFile3.";
  }
  catch ( modelErr& err )
  {
    if ( err.sFunction.compare("clInsectInfestation::ReadParFile" ) != 0 )
    {
      FAIL() << "TestInsectInfestation error processing caught wrong error for WriteInsectInfestationXMLErrorFile3.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile( WriteInsectInfestationXMLErrorFile4() );
    FAIL() << "TestInsectInfestation error processing didn't catch error for WriteInsectInfestationXMLErrorFile4.";
  }
  catch ( modelErr& err )
  {
    if ( err.sFunction.compare("clInsectInfestation::ReadParFile" ) != 0 )
    {
      FAIL() << "TestInsectInfestation error processing caught wrong error for WriteInsectInfestationXMLErrorFile4.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile( WriteInsectInfestationXMLErrorFile5() );
    FAIL() << "TestInsectInfestation error processing didn't catch error for WriteInsectInfestationXMLErrorFile5.";
  }
  catch ( modelErr& err )
  {
    if ( err.sFunction.compare("clInsectInfestation::ReadParFile" ) != 0 )
    {
      FAIL() << "TestInsectInfestation error processing caught wrong error for WriteInsectInfestationXMLErrorFile5.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile( WriteInsectInfestationXMLErrorFile6() );
    FAIL() << "TestInsectInfestation error processing didn't catch error for WriteInsectInfestationXMLErrorFile6.";
  }
  catch ( modelErr& err )
  {
    if ( err.sFunction.compare("clInsectInfestation::ReadParFile" ) != 0 )
    {
      FAIL() << "TestInsectInfestation error processing caught wrong error for WriteInsectInfestationXMLErrorFile6.";
    }
    ;
  }
  delete p_oSimManager;
}

/////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun1()
/////////////////////////////////////////////////////////////////////////////
TEST(InsectInfestation, TestNormalProcessingRun1)
{
  clTreePopulation * p_oPop;
  long *p_iTotal = new long[5], *p_iInfested = new long[5];
  float fDiam, fX, fY, fExpected;
  int i, iNumSp = 5, iInf;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    //Feed our file to the sim manager
    p_oSimManager->ReadFile( WriteInsectInfestationXMLNormalFile(1, 3));

    //Get the tree population
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Add 1000 trees of each species, to start.
    fDiam = 20;
    for ( i = 0; i < 1000; i++ )
    {
      fX = clModelMath::GetRand() * 100;
      fY = clModelMath::GetRand() * 100;
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, fDiam );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::adult, fDiam );
      p_oPop->CreateTree( fX, fY, 2, clTreePopulation::adult, fDiam );
      p_oPop->CreateTree( fX, fY, 3, clTreePopulation::adult, fDiam );
      p_oPop->CreateTree( fX, fY, 4, clTreePopulation::adult, fDiam );

    }

    //******************************************************
    // Timestep 1
    // Infestation not yet started.
    p_oSimManager->RunSim( 1 );
    GetTreeCount1Yr(p_oPop, p_iTotal, p_iInfested, false);
    fExpected = 900;
    for (i = 0; i < iNumSp; i++) {
      EXPECT_EQ(0, p_iInfested[i]);
      EXPECT_LT(fabs(fExpected - p_iTotal[i])/fExpected, 0.1);
    }

    //******************************************************
    // Timestep 2
    // Infestation not yet started.
    p_oSimManager->RunSim( 1 );
    GetTreeCount1Yr(p_oPop, p_iTotal, p_iInfested, false);
    fExpected = 810;
    for (i = 0; i < iNumSp; i++) {
      EXPECT_EQ(0, p_iInfested[i]);
      EXPECT_LT(fabs(fExpected - p_iTotal[i])/fExpected, 0.1);
    }

    //******************************************************
    // Timestep 3
    p_oSimManager->RunSim( 1 );
    GetTreeCount1Yr(p_oPop, p_iTotal, p_iInfested, false);
    fExpected = 729;
    for (i = 0; i < iNumSp; i++) {
      EXPECT_LT(fabs(fExpected - p_iTotal[i])/fExpected, 0.1);
    }
    fExpected = 0.01;
    ASSERT_TRUE(p_iInfested[0] > 0 && fabs(fExpected -
        ((float)p_iInfested[0]/(float)p_iTotal[0])) < 0.01);
    fExpected = 0.01;
    ASSERT_TRUE(p_iInfested[1] > 0 && fabs(fExpected -
        ((float)p_iInfested[1]/(float)p_iTotal[1])) < 0.01);
    EXPECT_EQ(0, p_iInfested[2]);
    EXPECT_EQ(p_iInfested[3], p_iTotal[3]);
    fExpected = 0.01;
    ASSERT_TRUE(p_iInfested[4] > 0 && fabs(fExpected -
        ((float)p_iInfested[4]/(float)p_iTotal[4])) < 0.01);

    //******************************************************
    // Timestep 4
    p_oSimManager->RunSim( 1 );
    GetTreeCount1Yr(p_oPop, p_iTotal, p_iInfested, false);
    fExpected = 2456.1;
    for (i = 0; i < iNumSp; i++) {
      EXPECT_LT(fabs(fExpected - p_iTotal[i])/fExpected, 0.1);
    }
    fExpected = 0.01158147;
    ASSERT_TRUE(p_iInfested[0] > 0 && fabs(fExpected -
        ((float)p_iInfested[0]/(float)p_iTotal[0])) < 0.01);
    fExpected = 0.01000186;
    ASSERT_TRUE(p_iInfested[1] > 0 && fabs(fExpected -
        ((float)p_iInfested[1]/(float)p_iTotal[1])) < 0.01);
    EXPECT_EQ(0, p_iInfested[2]);
    EXPECT_EQ(p_iInfested[3], p_iTotal[3]);
    fExpected = 0.01;
    ASSERT_TRUE(p_iInfested[4] > 0 && fabs(fExpected -
        ((float)p_iInfested[4]/(float)p_iTotal[4])) < 0.01);

    //******************************************************
    // Timestep 5
    p_oSimManager->RunSim( 1 );
    GetTreeCount1Yr(p_oPop, p_iTotal, p_iInfested, false);
    fExpected = 0.034711388;
    ASSERT_TRUE(fabs(fExpected -
        ((float)p_iInfested[0]/(float)p_iTotal[0])) < 0.01);
    fExpected = 0.010119209;
    ASSERT_TRUE(p_iInfested[1] > 0 && fabs(fExpected -
        ((float)p_iInfested[1]/(float)p_iTotal[1])) < 0.01);
    EXPECT_EQ(0, p_iInfested[2]);
    EXPECT_EQ(p_iInfested[3], p_iTotal[3]);
    fExpected = 0.010000563;
    ASSERT_TRUE(p_iInfested[4] > 0 && fabs(fExpected -
        ((float)p_iInfested[4]/(float)p_iTotal[4])) < 0.01);

    //******************************************************
    // Timestep 6
    p_oSimManager->RunSim( 1 );
    GetTreeCount1Yr(p_oPop, p_iTotal, p_iInfested, false);
    fExpected = 0.123583569;
    ASSERT_TRUE(fabs(fExpected -
        ((float)p_iInfested[0]/(float)p_iTotal[0])) < 0.01);
    fExpected = 0.011356164;
    ASSERT_TRUE(p_iInfested[1] > 0 && fabs(fExpected -
        ((float)p_iInfested[1]/(float)p_iTotal[1])) < 0.01);
    EXPECT_EQ(0, p_iInfested[2]);
    EXPECT_EQ(p_iInfested[3], p_iTotal[3]);
    fExpected = 0.010032444;
    ASSERT_TRUE(p_iInfested[4] > 0 && fabs(fExpected -
        ((float)p_iInfested[4]/(float)p_iTotal[4])) < 0.01);

    //******************************************************
    // Timestep 7
    p_oSimManager->RunSim( 1 );
    GetTreeCount1Yr(p_oPop, p_iTotal, p_iInfested, false);
    fExpected = 0.297673099;
    ASSERT_TRUE(fabs(fExpected -
        ((float)p_iInfested[0]/(float)p_iTotal[0])) < 0.01);
    fExpected = 0.017571914;
    ASSERT_TRUE(fabs(fExpected -
        ((float)p_iInfested[1]/(float)p_iTotal[1])) < 0.01);
    EXPECT_EQ(0, p_iInfested[2]);
    EXPECT_EQ(p_iInfested[3], p_iTotal[3]);
    fExpected = 0.01057561;
    ASSERT_TRUE(p_iInfested[4] > 0 && fabs(fExpected -
        ((float)p_iInfested[4]/(float)p_iTotal[4])) < 0.01);

    //******************************************************
    // Timestep 8
    p_oSimManager->RunSim( 1 );
    GetTreeCount1Yr(p_oPop, p_iTotal, p_iInfested, false);
    fExpected = 0.505;
    ASSERT_TRUE(fabs(fExpected -
        ((float)p_iInfested[0]/(float)p_iTotal[0])) < 0.01);
    fExpected = 0.038275839;
    ASSERT_TRUE(fabs(fExpected -
        ((float)p_iInfested[1]/(float)p_iTotal[1])) < 0.01);
    EXPECT_EQ(0, p_iInfested[2]);
    EXPECT_EQ(p_iInfested[3], p_iTotal[3]);
    fExpected = 0.015317655;
    ASSERT_TRUE(fabs(fExpected -
        ((float)p_iInfested[4]/(float)p_iTotal[4])) < 0.01);

    //******************************************************
    // Timestep 9
    p_oSimManager->RunSim( 1 );
    GetTreeCount1Yr(p_oPop, p_iTotal, p_iInfested, false);
    fExpected = 0.677902134;
    ASSERT_TRUE(fabs(fExpected -
        ((float)p_iInfested[0]/(float)p_iTotal[0])) < 0.01);
    fExpected = 0.089899117;
    ASSERT_TRUE(fabs(fExpected -
        ((float)p_iInfested[1]/(float)p_iTotal[1])) < 0.01);
    EXPECT_EQ(0, p_iInfested[2]);
    EXPECT_EQ(p_iInfested[3], p_iTotal[3]);
    fExpected = 0.041453705;
    ASSERT_TRUE(fabs(fExpected -
        ((float)p_iInfested[4]/(float)p_iTotal[4])) < 0.01);

    //******************************************************
    // Timestep 10
    p_oSimManager->RunSim( 1 );
    GetTreeCount1Yr(p_oPop, p_iTotal, p_iInfested, false);
    fExpected = 0.795522141;
    ASSERT_TRUE(fabs(fExpected -
        ((float)p_iInfested[0]/(float)p_iTotal[0])) < 0.01);
    fExpected = 0.189439692;
    ASSERT_TRUE(fabs(fExpected -
        ((float)p_iInfested[1]/(float)p_iTotal[1])) < 0.01);
    EXPECT_EQ(0, p_iInfested[2]);
    EXPECT_EQ(p_iInfested[3], p_iTotal[3]);
    fExpected = 0.132886225;
    ASSERT_TRUE(fabs(fExpected -
        ((float)p_iInfested[4]/(float)p_iTotal[4])) < 0.01);

    //******************************************************
    // Timestep 11
    p_oSimManager->RunSim( 1 );
    GetTreeCount1Yr(p_oPop, p_iTotal, p_iInfested, false);
    fExpected = 0.868936666;
    ASSERT_TRUE(fabs(fExpected -
        ((float)p_iInfested[0]/(float)p_iTotal[0])) < 0.01);
    fExpected = 0.337025536;
    ASSERT_TRUE(fabs(fExpected -
        ((float)p_iInfested[1]/(float)p_iTotal[1])) < 0.01);
    EXPECT_EQ(0, p_iInfested[2]);
    EXPECT_EQ(p_iInfested[3], p_iTotal[3]);
    fExpected = 0.305;
    ASSERT_TRUE(fabs(fExpected -
        ((float)p_iInfested[4]/(float)p_iTotal[4])) < 0.01);

    //******************************************************
    // Timestep 12
    p_oSimManager->RunSim( 1 );
    GetTreeCount1Yr(p_oPop, p_iTotal, p_iInfested, false);
    fExpected = 0.913895074;
    ASSERT_TRUE(fabs(fExpected -
        ((float)p_iInfested[0]/(float)p_iTotal[0])) < 0.01);
    fExpected = 0.505;
    ASSERT_TRUE(fabs(fExpected -
        ((float)p_iInfested[1]/(float)p_iTotal[1])) < 0.01);
    EXPECT_EQ(0, p_iInfested[2]);
    EXPECT_EQ(p_iInfested[3], p_iTotal[3]);
    fExpected = 0.461088908;
    ASSERT_TRUE(fabs(fExpected -
        ((float)p_iInfested[4]/(float)p_iTotal[4])) < 0.01);

    //******************************************************
    // Timestep 13
    p_oSimManager->RunSim( 1 );
    GetTreeCount1Yr(p_oPop, p_iTotal, p_iInfested, false);
    fExpected = 0.941764706;
    ASSERT_TRUE(fabs(fExpected -
        ((float)p_iInfested[0]/(float)p_iTotal[0])) < 0.01);
    fExpected = 0.656449978;
    ASSERT_TRUE(fabs(fExpected -
        ((float)p_iInfested[1]/(float)p_iTotal[1])) < 0.01);
    EXPECT_EQ(0, p_iInfested[2]);
    EXPECT_EQ(p_iInfested[3], p_iTotal[3]);
    fExpected = 0.542791905;
    ASSERT_TRUE(fabs(fExpected -
        ((float)p_iInfested[4]/(float)p_iTotal[4])) < 0.01);

    //******************************************************
    // Timestep 14
    p_oSimManager->RunSim( 1 );
    GetTreeCount1Yr(p_oPop, p_iTotal, p_iInfested, false);
    fExpected = 0.959468754;
    ASSERT_TRUE(fabs(fExpected -
        ((float)p_iInfested[0]/(float)p_iTotal[0])) < 0.01);
    fExpected = 0.771547489;
    ASSERT_TRUE(fabs(fExpected -
        ((float)p_iInfested[1]/(float)p_iTotal[1])) < 0.01);
    EXPECT_EQ(0, p_iInfested[2]);
    EXPECT_EQ(p_iInfested[3], p_iTotal[3]);
    fExpected = 0.576546452;
    ASSERT_TRUE(fabs(fExpected -
        ((float)p_iInfested[4]/(float)p_iTotal[4])) < 0.01);

    //************************************
    // Kill all non-infested trees of Species 2
    //************************************
    clTreeSearch *p_oTrees = p_oPop->Find("all");
    clTree *p_oTree = p_oTrees->NextTree();
    while (p_oTree) {
      if (1 == p_oTree->GetSpecies()) {
        if (clTreePopulation::seedling == p_oTree->GetType())
          p_oPop->KillTree(p_oTree, remove_tree);
        else {
          p_oTree->GetValue(p_oPop->GetIntDataCode("YearsInfested", p_oTree->GetSpecies(), p_oTree->GetType()), &iInf);
          if (iInf == 0)
            p_oPop->KillTree(p_oTree, remove_tree);
        }
      }
      p_oTree = p_oTrees->NextTree();
    }

    //******************************************************
    // Timestep 15
    p_oSimManager->RunSim( 1 );
    GetTreeCount1Yr(p_oPop, p_iTotal, p_iInfested, false);
    fExpected = 0.971033659;
    ASSERT_TRUE(fabs(fExpected -
        ((float)p_iInfested[0]/(float)p_iTotal[0])) < 0.01);
    fExpected = 1;
    EXPECT_EQ(p_iInfested[1], p_iTotal[1]);
    EXPECT_EQ(0, p_iInfested[2]);
    EXPECT_EQ(p_iInfested[3], p_iTotal[3]);
    fExpected = 0.589942903;
    ASSERT_TRUE(fabs(fExpected -
        ((float)p_iInfested[4]/(float)p_iTotal[4])) < 0.01);



    //******************************************************
    // Timestep 23
    p_oSimManager->RunSim( 8 );
    GetTreeCount1Yr(p_oPop, p_iTotal, p_iInfested, false);
    fExpected = 0.99614786;
    ASSERT_TRUE(fabs(fExpected -
        ((float)p_iInfested[0]/(float)p_iTotal[0])) < 0.01);
    fExpected = 0.991846973;
    ASSERT_TRUE(fabs(fExpected -
        ((float)p_iInfested[1]/(float)p_iTotal[1])) < 0.01);
    EXPECT_EQ(0, p_iInfested[2]);
    EXPECT_EQ(p_iInfested[3], p_iTotal[3]);
    fExpected = 0.599938141;
    ASSERT_TRUE(fabs(fExpected -
        ((float)p_iInfested[4]/(float)p_iTotal[4])) < 0.01);

    //*****************************************************
    // Kill all trees
    //*****************************************************
    p_oTrees = p_oPop->Find("all");
    p_oTree = p_oTrees->NextTree();
    while (p_oTree) {
      p_oPop->KillTree(p_oTree, remove_tree);
      p_oTree = p_oTrees->NextTree();
    }

    //******************************************************
    // Timestep 25
    p_oSimManager->RunSim( 4 );
    GetTreeCount1Yr(p_oPop, p_iTotal, p_iInfested, true);
    fExpected = 1600;
    for (i = 0; i < iNumSp; i++) {
      EXPECT_EQ(0, p_iInfested[i]);
      EXPECT_LT(fabs(fExpected - p_iTotal[i])/fExpected, 0.1);
    }

    delete[] p_iInfested;
    delete[] p_iTotal;
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete[] p_iInfested;
    delete[] p_iTotal;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun2()
/////////////////////////////////////////////////////////////////////////////
TEST(InsectInfestation, TestNormalProcessingRun2)
{
  clTreePopulation * p_oPop;
  long *p_iTotal = new long[5], *p_iInfested = new long[5];
  float fDiam, fX, fY, fExpected;
  int i, iNumSp = 5;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {

    //Feed our file to the sim manager
    p_oSimManager->ReadFile( WriteInsectInfestationXMLNormalFile(3, 1));

    //Get the tree population
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Add 1000 trees of each species, to start.
    fDiam = 20;
    for ( i = 0; i < 1000; i++ )
    {
      fX = clModelMath::GetRand() * 100;
      fY = clModelMath::GetRand() * 100;
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, fDiam );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::adult, fDiam );
      p_oPop->CreateTree( fX, fY, 2, clTreePopulation::adult, fDiam );
      p_oPop->CreateTree( fX, fY, 3, clTreePopulation::adult, fDiam );
      p_oPop->CreateTree( fX, fY, 4, clTreePopulation::adult, fDiam );

    }

    //******************************************************
    // Timestep 1
    p_oSimManager->RunSim( 1 );
    GetTreeCount3Yrs(p_oPop, p_iTotal, p_iInfested, false);
    fExpected = 729;
    for (i = 0; i < iNumSp; i++) {
      EXPECT_LT(fabs(fExpected - p_iTotal[i])/fExpected, 0.1);
    }
    fExpected = 0.01;
    ASSERT_TRUE(p_iInfested[0] > 0 && fabs(fExpected -
        ((float)p_iInfested[0]/(float)p_iTotal[0])) < 0.02);
    fExpected = 0.01;
    ASSERT_TRUE(p_iInfested[1] > 0 && fabs(fExpected -
        ((float)p_iInfested[1]/(float)p_iTotal[1])) < 0.02);
    EXPECT_EQ(0, p_iInfested[2]);
    EXPECT_EQ(p_iInfested[3], p_iTotal[3]);
    fExpected = 0.01;
    ASSERT_TRUE(p_iInfested[4] > 0 && fabs(fExpected -
        ((float)p_iInfested[4]/(float)p_iTotal[4])) < 0.02);

    //******************************************************
    // Timestep 2
    p_oSimManager->RunSim( 1 );
    GetTreeCount3Yrs(p_oPop, p_iTotal, p_iInfested, false);
    fExpected = 0.123583569;
    ASSERT_TRUE(fabs(fExpected -
        ((float)p_iInfested[0]/(float)p_iTotal[0])) < 0.02);
    fExpected = 0.011356164;
    ASSERT_TRUE(p_iInfested[1] > 0 && fabs(fExpected -
        ((float)p_iInfested[1]/(float)p_iTotal[1])) < 0.02);
    EXPECT_EQ(0, p_iInfested[2]);
    EXPECT_EQ(p_iInfested[3], p_iTotal[3]);
    fExpected = 0.010032444;
    ASSERT_TRUE(p_iInfested[4] > 0 && fabs(fExpected -
        ((float)p_iInfested[4]/(float)p_iTotal[4])) < 0.02);

    //******************************************************
    // Timestep 3
    p_oSimManager->RunSim( 1 );
    GetTreeCount3Yrs(p_oPop, p_iTotal, p_iInfested, false);
    fExpected = 0.677902134;
    ASSERT_TRUE(fabs(fExpected -
        ((float)p_iInfested[0]/(float)p_iTotal[0])) < 0.02);
    fExpected = 0.089899117;
    ASSERT_TRUE(fabs(fExpected -
        ((float)p_iInfested[1]/(float)p_iTotal[1])) < 0.02);
    EXPECT_EQ(0, p_iInfested[2]);
    EXPECT_EQ(p_iInfested[3], p_iTotal[3]);
    fExpected = 0.041453705;
    ASSERT_TRUE(fabs(fExpected -
        ((float)p_iInfested[4]/(float)p_iTotal[4])) < 0.02);

    //******************************************************
    // Timestep 4
    p_oSimManager->RunSim( 1 );
    GetTreeCount3Yrs(p_oPop, p_iTotal, p_iInfested, false);
    fExpected = 0.913895074;
    ASSERT_TRUE(fabs(fExpected -
        ((float)p_iInfested[0]/(float)p_iTotal[0])) < 0.02);
    fExpected = 0.505;
    ASSERT_TRUE(fabs(fExpected -
        ((float)p_iInfested[1]/(float)p_iTotal[1])) < 0.02);
    EXPECT_EQ(0, p_iInfested[2]);
    EXPECT_EQ(p_iInfested[3], p_iTotal[3]);
    fExpected = 0.461088908;
    ASSERT_TRUE(fabs(fExpected -
        ((float)p_iInfested[4]/(float)p_iTotal[4])) < 0.02);

    delete[] p_iInfested;
    delete[] p_iTotal;
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete[] p_iInfested;
    delete[] p_iTotal;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// WriteInsectInfestationXMLNormalFile()
/////////////////////////////////////////////////////////////////////////////
const char* WriteInsectInfestationXMLNormalFile(int iNumYrsTimestep, int iTSStart)
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">"
      << "<plot>"
      << "<timesteps>30</timesteps>"
      << "<yearsPerTimestep>" << iNumYrsTimestep << "</yearsPerTimestep>";

  oOut << "<randomSeed>1</randomSeed>"
      << "<plot_lenX>100</plot_lenX>"
      << "<plot_lenY>100</plot_lenY>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88171785</plot_temp_C>"
      << "<plot_latitude>55.37</plot_latitude>"
      << "</plot>"
      << "<trees>"
      << "<tr_speciesList>"
      << "<tr_species speciesName=\"Species_1\"/>"
      << "<tr_species speciesName=\"Species_2\"/>"
      << "<tr_species speciesName=\"Species_3\"/>"
      << "<tr_species speciesName=\"Species_4\"/>"
      << "<tr_species speciesName=\"Species_5\"/>"
      << "</tr_speciesList>"
      << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
      << "<tr_minAdultDBH>"
      << "<tr_madVal species=\"Species_1\">10</tr_madVal>"
      << "<tr_madVal species=\"Species_2\">10</tr_madVal>"
      << "<tr_madVal species=\"Species_3\">10</tr_madVal>"
      << "<tr_madVal species=\"Species_4\">10</tr_madVal>"
      << "<tr_madVal species=\"Species_5\">10</tr_madVal>"
      << "</tr_minAdultDBH>"
      << "<tr_maxSeedlingHeight>"
      << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Species_2\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Species_3\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Species_4\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Species_5\">1.35</tr_mshVal>"
      << "</tr_maxSeedlingHeight>"
      << "</trees>"
      << "<allometry>"
      << "<tr_adultLinearSlope>"
      << "<tr_alsVal species=\"Species_1\">1</tr_alsVal>"
      << "<tr_alsVal species=\"Species_2\">1</tr_alsVal>"
      << "<tr_alsVal species=\"Species_3\">1</tr_alsVal>"
      << "<tr_alsVal species=\"Species_4\">1</tr_alsVal>"
      << "<tr_alsVal species=\"Species_5\">1</tr_alsVal>"
      << "</tr_adultLinearSlope>"
      << "<tr_adultLinearIntercept>"
      << "<tr_aliVal species=\"Species_1\">0</tr_aliVal>"
      << "<tr_aliVal species=\"Species_2\">0</tr_aliVal>"
      << "<tr_aliVal species=\"Species_3\">0</tr_aliVal>"
      << "<tr_aliVal species=\"Species_4\">0</tr_aliVal>"
      << "<tr_aliVal species=\"Species_5\">0</tr_aliVal>"
      << "</tr_adultLinearIntercept>"
      << "<tr_saplingLinearSlope>"
      << "<tr_salsVal species=\"Species_1\">1</tr_salsVal>"
      << "<tr_salsVal species=\"Species_2\">1</tr_salsVal>"
      << "<tr_salsVal species=\"Species_3\">1</tr_salsVal>"
      << "<tr_salsVal species=\"Species_4\">1</tr_salsVal>"
      << "<tr_salsVal species=\"Species_5\">1</tr_salsVal>"
      << "</tr_saplingLinearSlope>"
      << "<tr_saplingLinearIntercept>"
      << "<tr_saliVal species=\"Species_1\">0</tr_saliVal>"
      << "<tr_saliVal species=\"Species_2\">0</tr_saliVal>"
      << "<tr_saliVal species=\"Species_3\">0</tr_saliVal>"
      << "<tr_saliVal species=\"Species_4\">0</tr_saliVal>"
      << "<tr_saliVal species=\"Species_5\">0</tr_saliVal>"
      << "</tr_saplingLinearIntercept>"
      << "<tr_seedlingLinearSlope>"
      << "<tr_selsVal species=\"Species_1\">1</tr_selsVal>"
      << "<tr_selsVal species=\"Species_2\">1</tr_selsVal>"
      << "<tr_selsVal species=\"Species_3\">1</tr_selsVal>"
      << "<tr_selsVal species=\"Species_4\">1</tr_selsVal>"
      << "<tr_selsVal species=\"Species_5\">1</tr_selsVal>"
      << "</tr_seedlingLinearSlope>"
      << "<tr_seedlingLinearIntercept>"
      << "<tr_seliVal species=\"Species_1\">0</tr_seliVal>"
      << "<tr_seliVal species=\"Species_2\">0</tr_seliVal>"
      << "<tr_seliVal species=\"Species_3\">0</tr_seliVal>"
      << "<tr_seliVal species=\"Species_4\">0</tr_seliVal>"
      << "<tr_seliVal species=\"Species_5\">0</tr_seliVal>"
      << "</tr_seedlingLinearIntercept>"
      << "<tr_canopyHeight>"
      << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
      << "<tr_chVal species=\"Species_2\">39.48</tr_chVal>"
      << "<tr_chVal species=\"Species_3\">39.48</tr_chVal>"
      << "<tr_chVal species=\"Species_4\">39.48</tr_chVal>"
      << "<tr_chVal species=\"Species_5\">39.48</tr_chVal>"
      << "</tr_canopyHeight>"
      << "<tr_stdAsympCrownRad>"
      << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_2\">0.0549</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_3\">0.0549</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_4\">0.0549</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_5\">0.0549</tr_sacrVal>"
      << "</tr_stdAsympCrownRad>"
      << "<tr_stdCrownRadExp>"
      << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_3\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_4\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_5\">1.0</tr_screVal>"
      << "</tr_stdCrownRadExp>"
      << "<tr_conversionDiam10ToDBH>"
      << "<tr_cdtdVal species=\"Species_1\">1</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_2\">1</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_3\">1</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_4\">1</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_5\">1</tr_cdtdVal>"
      << "</tr_conversionDiam10ToDBH>"
      << "<tr_interceptDiam10ToDBH>"
      << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_3\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_4\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_5\">0</tr_idtdVal>"
      << "</tr_interceptDiam10ToDBH>"
      << "<tr_interceptDiam10ToDBH>"
      << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_3\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_4\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_5\">0</tr_idtdVal>"
      << "</tr_interceptDiam10ToDBH>"
      << "<tr_stdAsympCrownHt>"
      << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
      << "<tr_sachVal species=\"Species_2\">0.389</tr_sachVal>"
      << "<tr_sachVal species=\"Species_3\">0.389</tr_sachVal>"
      << "<tr_sachVal species=\"Species_4\">0.389</tr_sachVal>"
      << "<tr_sachVal species=\"Species_5\">0.389</tr_sachVal>"
      << "</tr_stdAsympCrownHt>"
      << "<tr_stdCrownHtExp>"
      << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_3\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_4\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_5\">1.0</tr_scheVal>"
      << "</tr_stdCrownHtExp>"
      << "<tr_slopeOfHeight-Diam10>"
      << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_2\">0.03418</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_3\">0.03418</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_4\">0.03418</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_5\">0.03418</tr_sohdVal>"
      << "</tr_slopeOfHeight-Diam10>"
      << "<tr_whatSeedlingHeightDiam>"
      << "<tr_wsehdVal species=\"Species_1\">1</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_2\">1</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_3\">1</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_4\">1</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_5\">1</tr_wsehdVal>"
      << "</tr_whatSeedlingHeightDiam>"
      << "<tr_whatSaplingHeightDiam>"
      << "<tr_wsahdVal species=\"Species_1\">1</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_2\">1</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_3\">1</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_4\">1</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_5\">1</tr_wsahdVal>"
      << "</tr_whatSaplingHeightDiam>"
      << "<tr_whatAdultHeightDiam>"
      << "<tr_wahdVal species=\"Species_1\">1</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_2\">1</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_3\">1</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_4\">1</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_5\">1</tr_wahdVal>"
      << "</tr_whatAdultHeightDiam>"
      << "<tr_whatAdultCrownRadDiam>"
      << "<tr_wacrdVal species=\"Species_1\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Species_2\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Species_3\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Species_4\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Species_5\">0</tr_wacrdVal>"
      << "</tr_whatAdultCrownRadDiam>"
      << "<tr_whatAdultCrownHeightHeight>"
      << "<tr_wachhVal species=\"Species_1\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Species_2\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Species_3\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Species_4\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Species_5\">0</tr_wachhVal>"
      << "</tr_whatAdultCrownHeightHeight>"
      << "<tr_whatSaplingCrownRadDiam>"
      << "<tr_wscrdVal species=\"Species_1\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Species_2\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Species_3\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Species_4\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Species_5\">0</tr_wscrdVal>"
      << "</tr_whatSaplingCrownRadDiam>"
      << "<tr_whatSaplingCrownHeightHeight>"
      << "<tr_wschhVal species=\"Species_1\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Species_2\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Species_3\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Species_4\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Species_5\">0</tr_wschhVal>"
      << "</tr_whatSaplingCrownHeightHeight>"
      << "</allometry>";

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>ConstRadialGrowth</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_5\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_5\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_4\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_5\" type=\"Seedling\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>StochasticMortality</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_5\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_5\" type=\"Sapling\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>RemoveDead</behaviorName>"
      << "<version>3</version>"
      << "<listPosition>3</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_5\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_5\" type=\"Sapling\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>NonSpatialDisperse</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>4</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_5\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_5\" type=\"Sapling\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>Establishment</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>5</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
      << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
      << "<applyTo species=\"Species_3\" type=\"Seed\"/>"
      << "<applyTo species=\"Species_4\" type=\"Seed\"/>"
      << "<applyTo species=\"Species_5\" type=\"Seed\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>InsectInfestation</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>6</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_5\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_5\" type=\"Sapling\"/>"
      << "</behavior>"
      << "</behaviorList>";

  oOut << "<InsectInfestation6>"
      << "<di_insectIntercept>"
      << "<di_iiVal species=\"Species_1\">0.01</di_iiVal>"
      << "<di_iiVal species=\"Species_2\">0.01</di_iiVal>"
      << "<di_iiVal species=\"Species_4\">1</di_iiVal>"
      << "<di_iiVal species=\"Species_5\">0.01</di_iiVal>"
      << "</di_insectIntercept>"
      << "<di_insectMaxInfestation>"
      << "<di_imiVal species=\"Species_1\">1</di_imiVal>"
      << "<di_imiVal species=\"Species_2\">1</di_imiVal>"
      << "<di_imiVal species=\"Species_4\">1</di_imiVal>"
      << "<di_imiVal species=\"Species_5\">0.6</di_imiVal>"
      << "</di_insectMaxInfestation>"
      << "<di_insectX0>"
      << "<di_ix0Val species=\"Species_1\">5</di_ix0Val>"
      << "<di_ix0Val species=\"Species_2\">9</di_ix0Val>"
      << "<di_ix0Val species=\"Species_4\">11</di_ix0Val>"
      << "<di_ix0Val species=\"Species_5\">8</di_ix0Val>"
      << "</di_insectX0>"
      << "<di_insectXb>"
      << "<di_ixbVal species=\"Species_1\">-4</di_ixbVal>"
      << "<di_ixbVal species=\"Species_2\">-6</di_ixbVal>"
      << "<di_ixbVal species=\"Species_4\">-8</di_ixbVal>"
      << "<di_ixbVal species=\"Species_5\">-10</di_ixbVal>"
      << "</di_insectXb>"
      << "<di_insectMinDBH>"
      << "<di_imdVal species=\"Species_1\">2.2</di_imdVal>"
      << "<di_imdVal species=\"Species_2\">2.2</di_imdVal>"
      << "<di_imdVal species=\"Species_4\">2.2</di_imdVal>"
      << "<di_imdVal species=\"Species_5\">2.2</di_imdVal>"
      << "</di_insectMinDBH>"
      << "<di_insectStartTimestep>" << iTSStart << "</di_insectStartTimestep>"
      << "</InsectInfestation6>";

  oOut << "<ConstRadialGrowth1>"
      << "<gr_adultConstRadialInc>"
      << "<gr_acriVal species=\"Species_1\">4.3</gr_acriVal>"
      << "<gr_acriVal species=\"Species_2\">4.3</gr_acriVal>"
      << "<gr_acriVal species=\"Species_3\">4.3</gr_acriVal>"
      << "<gr_acriVal species=\"Species_4\">4.3</gr_acriVal>"
      << "<gr_acriVal species=\"Species_5\">4.3</gr_acriVal>"
      << "</gr_adultConstRadialInc>"
      << "</ConstRadialGrowth1>"
      << "<StochasticMortality2>"
      << "<mo_stochasticMortRate>"
      << "<mo_smrVal species=\"Species_1\">0.1</mo_smrVal>"
      << "<mo_smrVal species=\"Species_2\">0.1</mo_smrVal>"
      << "<mo_smrVal species=\"Species_3\">0.1</mo_smrVal>"
      << "<mo_smrVal species=\"Species_4\">0.1</mo_smrVal>"
      << "<mo_smrVal species=\"Species_5\">0.1</mo_smrVal>"
      << "</mo_stochasticMortRate>"
      << "</StochasticMortality2>"
      << "<NonSpatialDisperse4>"
      << "<di_minDbhForReproduction>"
      << "<di_mdfrVal species=\"Species_1\">15.0</di_mdfrVal>"
      << "<di_mdfrVal species=\"Species_2\">15.0</di_mdfrVal>"
      << "<di_mdfrVal species=\"Species_3\">15.0</di_mdfrVal>"
      << "<di_mdfrVal species=\"Species_4\">15.0</di_mdfrVal>"
      << "<di_mdfrVal species=\"Species_5\">15.0</di_mdfrVal>"
      << "</di_minDbhForReproduction>"
      << "<di_nonSpatialSlopeOfLambda>"
      << "<di_nssolVal species=\"Species_1\">0</di_nssolVal>"
      << "<di_nssolVal species=\"Species_2\">0</di_nssolVal>"
      << "<di_nssolVal species=\"Species_3\">0</di_nssolVal>"
      << "<di_nssolVal species=\"Species_4\">0</di_nssolVal>"
      << "<di_nssolVal species=\"Species_5\">0</di_nssolVal>"
      << "</di_nonSpatialSlopeOfLambda>"
      << "<di_nonSpatialInterceptOfLambda>"
      << "<di_nsiolVal species=\"Species_1\">0.2</di_nsiolVal>"
      << "<di_nsiolVal species=\"Species_2\">0.2</di_nsiolVal>"
      << "<di_nsiolVal species=\"Species_3\">0.2</di_nsiolVal>"
      << "<di_nsiolVal species=\"Species_4\">0.2</di_nsiolVal>"
      << "<di_nsiolVal species=\"Species_5\">0.2</di_nsiolVal>"
      << "</di_nonSpatialInterceptOfLambda>"
      << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
      << "</NonSpatialDisperse4>";


  oOut << "</paramFile>";

  oOut.close();

  return cFileString;

}


/////////////////////////////////////////////////////////////////////////////
// WriteInsectInfestationXMLErrorFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteInsectInfestationXMLErrorFile1()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  WriteInsectInfestationErrorCommonStuff(oOut);

  oOut << "<InsectInfestation1>"
      << "<di_insectIntercept>"
      << "<di_iiVal species=\"Species_1\">0.01</di_iiVal>"
      << "<di_iiVal species=\"Species_2\">0.01</di_iiVal>"
      << "</di_insectIntercept>"
      << "<di_insectMaxInfestation>"
      << "<di_imiVal species=\"Species_1\">1</di_imiVal>"
      << "<di_imiVal species=\"Species_2\">1</di_imiVal>"
      << "</di_insectMaxInfestation>"
      << "<di_insectX0>"
      << "<di_ix0Val species=\"Species_1\">5</di_ix0Val>"
      << "<di_ix0Val species=\"Species_2\">9</di_ix0Val>"
      << "</di_insectX0>"
      << "<di_insectXb>"
      << "<di_ixbVal species=\"Species_1\">-4</di_ixbVal>"
      << "<di_ixbVal species=\"Species_2\">-6</di_ixbVal>"
      << "</di_insectXb>"
      << "<di_insectMinDBH>"
      << "<di_imdVal species=\"Species_1\">-2.2</di_imdVal>"
      << "<di_imdVal species=\"Species_2\">2.2</di_imdVal>"
      << "</di_insectMinDBH>"
      << "<di_insectStartTimestep>3</di_insectStartTimestep>"
      << "</InsectInfestation1>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteInsectInfestationXMLErrorFile2()
/////////////////////////////////////////////////////////////////////////////
const char* WriteInsectInfestationXMLErrorFile2()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  using namespace std;
  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">"
      << "<plot>"
      << "<timesteps>25</timesteps>"
      << "<yearsPerTimestep>1</yearsPerTimestep>";

  oOut << "<randomSeed>1</randomSeed>"
      << "<plot_lenX>100</plot_lenX>"
      << "<plot_lenY>100</plot_lenY>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88171785</plot_temp_C>"
      << "<plot_latitude>55.37</plot_latitude>"
      << "</plot>"
      << "<trees>"
      << "<tr_speciesList>"
      << "<tr_species speciesName=\"Species_1\"/>"
      << "<tr_species speciesName=\"Species_2\"/>"
      << "</tr_speciesList>"
      << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
      << "<tr_minAdultDBH>"
      << "<tr_madVal species=\"Species_1\">10</tr_madVal>"
      << "<tr_madVal species=\"Species_2\">10</tr_madVal>"
      << "</tr_minAdultDBH>"
      << "<tr_maxSeedlingHeight>"
      << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Species_2\">1.35</tr_mshVal>"
      << "</tr_maxSeedlingHeight>"
      << "</trees>"
      << "<allometry>"
      << "<tr_slopeOfAsymHeight>"
      << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
      << "<tr_soahVal species=\"Species_2\">0.0299</tr_soahVal>"
      << "</tr_slopeOfAsymHeight>"
      << "<tr_canopyHeight>"
      << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
      << "<tr_chVal species=\"Species_2\">39.48</tr_chVal>"
      << "</tr_canopyHeight>"
      << "<tr_stdAsympCrownRad>"
      << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_2\">0.0549</tr_sacrVal>"
      << "</tr_stdAsympCrownRad>"
      << "<tr_stdCrownRadExp>"
      << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
      << "</tr_stdCrownRadExp>"
      << "<tr_conversionDiam10ToDBH>"
      << "<tr_cdtdVal species=\"Species_1\">1</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_2\">1</tr_cdtdVal>"
      << "</tr_conversionDiam10ToDBH>"
      << "<tr_interceptDiam10ToDBH>"
      << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
      << "</tr_interceptDiam10ToDBH>"
      << "<tr_interceptDiam10ToDBH>"
      << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
      << "</tr_interceptDiam10ToDBH>"
      << "<tr_stdAsympCrownHt>"
      << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
      << "<tr_sachVal species=\"Species_2\">0.389</tr_sachVal>"
      << "</tr_stdAsympCrownHt>"
      << "<tr_stdCrownHtExp>"
      << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
      << "</tr_stdCrownHtExp>"
      << "<tr_slopeOfHeight-Diam10>"
      << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_2\">0.03418</tr_sohdVal>"
      << "</tr_slopeOfHeight-Diam10>"
      << "<tr_whatSeedlingHeightDiam>"
      << "<tr_wsehdVal species=\"Species_1\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_2\">0</tr_wsehdVal>"
      << "</tr_whatSeedlingHeightDiam>"
      << "<tr_whatSaplingHeightDiam>"
      << "<tr_wsahdVal species=\"Species_1\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_2\">0</tr_wsahdVal>"
      << "</tr_whatSaplingHeightDiam>"
      << "<tr_whatAdultHeightDiam>"
      << "<tr_wahdVal species=\"Species_1\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_2\">0</tr_wahdVal>"
      << "</tr_whatAdultHeightDiam>"
      << "<tr_whatAdultCrownRadDiam>"
      << "<tr_wacrdVal species=\"Species_1\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Species_2\">0</tr_wacrdVal>"
      << "</tr_whatAdultCrownRadDiam>"
      << "<tr_whatAdultCrownHeightHeight>"
      << "<tr_wachhVal species=\"Species_1\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Species_2\">0</tr_wachhVal>"
      << "</tr_whatAdultCrownHeightHeight>"
      << "<tr_whatSaplingCrownRadDiam>"
      << "<tr_wscrdVal species=\"Species_1\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Species_2\">0</tr_wscrdVal>"
      << "</tr_whatSaplingCrownRadDiam>"
      << "<tr_whatSaplingCrownHeightHeight>"
      << "<tr_wschhVal species=\"Species_1\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Species_2\">0</tr_wschhVal>"
      << "</tr_whatSaplingCrownHeightHeight>"
      << "</allometry>";

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>InsectInfestation</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "</behaviorList>";

  oOut << "<InsectInfestation1>"
      << "<di_insectIntercept>"
      << "<di_iiVal species=\"Species_1\">0.01</di_iiVal>"
      << "<di_iiVal species=\"Species_2\">0.01</di_iiVal>"
      << "</di_insectIntercept>"
      << "<di_insectMaxInfestation>"
      << "<di_imiVal species=\"Species_1\">1</di_imiVal>"
      << "<di_imiVal species=\"Species_2\">1</di_imiVal>"
      << "</di_insectMaxInfestation>"
      << "<di_insectX0>"
      << "<di_ix0Val species=\"Species_1\">5</di_ix0Val>"
      << "<di_ix0Val species=\"Species_2\">9</di_ix0Val>"
      << "</di_insectX0>"
      << "<di_insectXb>"
      << "<di_ixbVal species=\"Species_1\">-4</di_ixbVal>"
      << "<di_ixbVal species=\"Species_2\">-6</di_ixbVal>"
      << "</di_insectXb>"
      << "<di_insectMinDBH>"
      << "<di_imdVal species=\"Species_1\">2.2</di_imdVal>"
      << "<di_imdVal species=\"Species_2\">2.2</di_imdVal>"
      << "</di_insectMinDBH>"
      << "<di_insectStartTimestep>3</di_insectStartTimestep>"
      << "</InsectInfestation1>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteInsectInfestationXMLErrorFile3()
/////////////////////////////////////////////////////////////////////////////
const char* WriteInsectInfestationXMLErrorFile3()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  WriteInsectInfestationErrorCommonStuff(oOut);

  oOut << "<InsectInfestation1>"
      << "<di_insectIntercept>"
      << "<di_iiVal species=\"Species_1\">0.01</di_iiVal>"
      << "<di_iiVal species=\"Species_2\">0.01</di_iiVal>"
      << "</di_insectIntercept>"
      << "<di_insectMaxInfestation>"
      << "<di_imiVal species=\"Species_1\">1</di_imiVal>"
      << "<di_imiVal species=\"Species_2\">1</di_imiVal>"
      << "</di_insectMaxInfestation>"
      << "<di_insectX0>"
      << "<di_ix0Val species=\"Species_1\">5</di_ix0Val>"
      << "<di_ix0Val species=\"Species_2\">9</di_ix0Val>"
      << "</di_insectX0>"
      << "<di_insectXb>"
      << "<di_ixbVal species=\"Species_1\">-4</di_ixbVal>"
      << "<di_ixbVal species=\"Species_2\">-6</di_ixbVal>"
      << "</di_insectXb>"
      << "<di_insectMinDBH>"
      << "<di_imdVal species=\"Species_1\">2.2</di_imdVal>"
      << "<di_imdVal species=\"Species_2\">2.2</di_imdVal>"
      << "</di_insectMinDBH>"
      << "<di_insectStartTimestep>-3</di_insectStartTimestep>"
      << "</InsectInfestation1>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteInsectInfestationXMLErrorFile4()
/////////////////////////////////////////////////////////////////////////////
const char* WriteInsectInfestationXMLErrorFile4()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  WriteInsectInfestationErrorCommonStuff(oOut);

  oOut << "<InsectInfestation1>"
      << "<di_insectIntercept>"
      << "<di_iiVal species=\"Species_1\">1.01</di_iiVal>"
      << "<di_iiVal species=\"Species_2\">0.01</di_iiVal>"
      << "</di_insectIntercept>"
      << "<di_insectMaxInfestation>"
      << "<di_imiVal species=\"Species_1\">1</di_imiVal>"
      << "<di_imiVal species=\"Species_2\">1</di_imiVal>"
      << "</di_insectMaxInfestation>"
      << "<di_insectX0>"
      << "<di_ix0Val species=\"Species_1\">5</di_ix0Val>"
      << "<di_ix0Val species=\"Species_2\">9</di_ix0Val>"
      << "</di_insectX0>"
      << "<di_insectXb>"
      << "<di_ixbVal species=\"Species_1\">-4</di_ixbVal>"
      << "<di_ixbVal species=\"Species_2\">-6</di_ixbVal>"
      << "</di_insectXb>"
      << "<di_insectMinDBH>"
      << "<di_imdVal species=\"Species_1\">2.2</di_imdVal>"
      << "<di_imdVal species=\"Species_2\">2.2</di_imdVal>"
      << "</di_insectMinDBH>"
      << "<di_insectStartTimestep>3</di_insectStartTimestep>"
      << "</InsectInfestation1>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteInsectInfestationXMLErrorFile5()
/////////////////////////////////////////////////////////////////////////////
const char* WriteInsectInfestationXMLErrorFile5()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  WriteInsectInfestationErrorCommonStuff(oOut);

  oOut << "<InsectInfestation1>"
      << "<di_insectIntercept>"
      << "<di_iiVal species=\"Species_1\">0.01</di_iiVal>"
      << "<di_iiVal species=\"Species_2\">0.01</di_iiVal>"
      << "</di_insectIntercept>"
      << "<di_insectMaxInfestation>"
      << "<di_imiVal species=\"Species_1\">1</di_imiVal>"
      << "<di_imiVal species=\"Species_2\">-1</di_imiVal>"
      << "</di_insectMaxInfestation>"
      << "<di_insectX0>"
      << "<di_ix0Val species=\"Species_1\">5</di_ix0Val>"
      << "<di_ix0Val species=\"Species_2\">9</di_ix0Val>"
      << "</di_insectX0>"
      << "<di_insectXb>"
      << "<di_ixbVal species=\"Species_1\">-4</di_ixbVal>"
      << "<di_ixbVal species=\"Species_2\">-6</di_ixbVal>"
      << "</di_insectXb>"
      << "<di_insectMinDBH>"
      << "<di_imdVal species=\"Species_1\">2.2</di_imdVal>"
      << "<di_imdVal species=\"Species_2\">2.2</di_imdVal>"
      << "</di_insectMinDBH>"
      << "<di_insectStartTimestep>3</di_insectStartTimestep>"
      << "</InsectInfestation1>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteInsectInfestationXMLErrorFile6()
/////////////////////////////////////////////////////////////////////////////
const char* WriteInsectInfestationXMLErrorFile6()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  WriteInsectInfestationErrorCommonStuff(oOut);

  oOut << "<InsectInfestation1>"
      << "<di_insectIntercept>"
      << "<di_iiVal species=\"Species_1\">0.01</di_iiVal>"
      << "<di_iiVal species=\"Species_2\">0.01</di_iiVal>"
      << "</di_insectIntercept>"
      << "<di_insectMaxInfestation>"
      << "<di_imiVal species=\"Species_1\">1</di_imiVal>"
      << "<di_imiVal species=\"Species_2\">1</di_imiVal>"
      << "</di_insectMaxInfestation>"
      << "<di_insectX0>"
      << "<di_ix0Val species=\"Species_1\">0</di_ix0Val>"
      << "<di_ix0Val species=\"Species_2\">9</di_ix0Val>"
      << "</di_insectX0>"
      << "<di_insectXb>"
      << "<di_ixbVal species=\"Species_1\">0</di_ixbVal>"
      << "<di_ixbVal species=\"Species_2\">-6</di_ixbVal>"
      << "</di_insectXb>"
      << "<di_insectMinDBH>"
      << "<di_imdVal species=\"Species_1\">2.2</di_imdVal>"
      << "<di_imdVal species=\"Species_2\">2.2</di_imdVal>"
      << "</di_insectMinDBH>"
      << "<di_insectStartTimestep>3</di_insectStartTimestep>"
      << "</InsectInfestation1>"
      << "</paramFile>";

  oOut.close();

  return cFileString;

}

/////////////////////////////////////////////////////////////////////////////
// WriteInsectInfestationErrorCommonStuff()
/////////////////////////////////////////////////////////////////////////////
void WriteInsectInfestationErrorCommonStuff(std::fstream &oOut)
{
  using namespace std;
  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">"
      << "<plot>"
      << "<timesteps>25</timesteps>"
      << "<yearsPerTimestep>1</yearsPerTimestep>";

  oOut << "<randomSeed>1</randomSeed>"
      << "<plot_lenX>100</plot_lenX>"
      << "<plot_lenY>100</plot_lenY>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88171785</plot_temp_C>"
      << "<plot_latitude>55.37</plot_latitude>"
      << "</plot>"
      << "<trees>"
      << "<tr_speciesList>"
      << "<tr_species speciesName=\"Species_1\"/>"
      << "<tr_species speciesName=\"Species_2\"/>"
      << "</tr_speciesList>"
      << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
      << "<tr_minAdultDBH>"
      << "<tr_madVal species=\"Species_1\">10</tr_madVal>"
      << "<tr_madVal species=\"Species_2\">10</tr_madVal>"
      << "</tr_minAdultDBH>"
      << "<tr_maxSeedlingHeight>"
      << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Species_2\">1.35</tr_mshVal>"
      << "</tr_maxSeedlingHeight>"
      << "</trees>"
      << "<allometry>"
      << "<tr_slopeOfAsymHeight>"
      << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
      << "<tr_soahVal species=\"Species_2\">0.0299</tr_soahVal>"
      << "</tr_slopeOfAsymHeight>"
      << "<tr_canopyHeight>"
      << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
      << "<tr_chVal species=\"Species_2\">39.48</tr_chVal>"
      << "</tr_canopyHeight>"
      << "<tr_stdAsympCrownRad>"
      << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_2\">0.0549</tr_sacrVal>"
      << "</tr_stdAsympCrownRad>"
      << "<tr_stdCrownRadExp>"
      << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
      << "</tr_stdCrownRadExp>"
      << "<tr_conversionDiam10ToDBH>"
      << "<tr_cdtdVal species=\"Species_1\">1</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_2\">1</tr_cdtdVal>"
      << "</tr_conversionDiam10ToDBH>"
      << "<tr_interceptDiam10ToDBH>"
      << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
      << "</tr_interceptDiam10ToDBH>"
      << "<tr_interceptDiam10ToDBH>"
      << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
      << "</tr_interceptDiam10ToDBH>"
      << "<tr_stdAsympCrownHt>"
      << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
      << "<tr_sachVal species=\"Species_2\">0.389</tr_sachVal>"
      << "</tr_stdAsympCrownHt>"
      << "<tr_stdCrownHtExp>"
      << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
      << "</tr_stdCrownHtExp>"
      << "<tr_slopeOfHeight-Diam10>"
      << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_2\">0.03418</tr_sohdVal>"
      << "</tr_slopeOfHeight-Diam10>"
      << "<tr_whatSeedlingHeightDiam>"
      << "<tr_wsehdVal species=\"Species_1\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_2\">0</tr_wsehdVal>"
      << "</tr_whatSeedlingHeightDiam>"
      << "<tr_whatSaplingHeightDiam>"
      << "<tr_wsahdVal species=\"Species_1\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_2\">0</tr_wsahdVal>"
      << "</tr_whatSaplingHeightDiam>"
      << "<tr_whatAdultHeightDiam>"
      << "<tr_wahdVal species=\"Species_1\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_2\">0</tr_wahdVal>"
      << "</tr_whatAdultHeightDiam>"
      << "<tr_whatAdultCrownRadDiam>"
      << "<tr_wacrdVal species=\"Species_1\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Species_2\">0</tr_wacrdVal>"
      << "</tr_whatAdultCrownRadDiam>"
      << "<tr_whatAdultCrownHeightHeight>"
      << "<tr_wachhVal species=\"Species_1\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Species_2\">0</tr_wachhVal>"
      << "</tr_whatAdultCrownHeightHeight>"
      << "<tr_whatSaplingCrownRadDiam>"
      << "<tr_wscrdVal species=\"Species_1\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Species_2\">0</tr_wscrdVal>"
      << "</tr_whatSaplingCrownRadDiam>"
      << "<tr_whatSaplingCrownHeightHeight>"
      << "<tr_wschhVal species=\"Species_1\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Species_2\">0</tr_wschhVal>"
      << "</tr_whatSaplingCrownHeightHeight>"
      << "</allometry>";

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>InsectInfestation</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "</behaviorList>";
}

/////////////////////////////////////////////////////////////////////////
// GetTreeCount1Yr
/////////////////////////////////////////////////////////////////////////
void GetTreeCount1Yr(clTreePopulation *p_oPop,
    long *p_iTotal, long *p_iInfested, bool bNoInfestation) {
  clTreeSearch *p_oAllTrees = p_oPop->Find( "all" );
  clTree *p_oTree = p_oAllTrees->NextTree();
  float fDbh;
  int iInf, i, iNumSp = 5;

  for (i = 0; i < iNumSp; i++) {
    p_iTotal[i] = 0;
    p_iInfested[i] = 0;
  }

  while (p_oTree) {
    if (clTreePopulation::seedling != p_oTree->GetType()) {
      p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDbh);
      if (fDbh > 2.2) {
        p_iTotal[p_oTree->GetSpecies()]++;
      }
      if (2 != p_oTree->GetSpecies()) {
        p_oTree->GetValue(p_oPop->GetIntDataCode("YearsInfested", p_oTree->GetSpecies(), p_oTree->GetType()), &iInf);
        if (fDbh < 2.2) {
          EXPECT_EQ(0, iInf);
        } else {
          if (iInf > 0) p_iInfested[p_oTree->GetSpecies()]++;
        }
        if (3 == p_oTree->GetSpecies() && !bNoInfestation) {
          if (fabs(fDbh - 2.68) < 0.1) {
            EXPECT_EQ(1, iInf);
          } else if (fabs(fDbh - 3.54) < 0.1) {
            EXPECT_EQ(2, iInf);
          } else if (fabs(fDbh - 4.4) < 0.1) {
            EXPECT_EQ(3, iInf);
          } else if (fabs(fDbh - 5.26) < 0.1) {
            EXPECT_EQ(4, iInf);
          } else if (fabs(fDbh - 6.12) < 0.1) {
            EXPECT_EQ(5, iInf);
          }

        }
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }
}

/////////////////////////////////////////////////////////////////////////
// GetTreeCount3Yrs
/////////////////////////////////////////////////////////////////////////
void GetTreeCount3Yrs(clTreePopulation *p_oPop,
    long *p_iTotal, long *p_iInfested, bool bNoInfestation) {
  clTreeSearch *p_oAllTrees = p_oPop->Find( "all" );
  clTree *p_oTree = p_oAllTrees->NextTree();
  float fDbh;
  int iInf, i, iNumSp = 5;

  for (i = 0; i < iNumSp; i++) {
    p_iTotal[i] = 0;
    p_iInfested[i] = 0;
  }

  while (p_oTree) {
    if (clTreePopulation::seedling != p_oTree->GetType()) {
      p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDbh);
      if (fDbh > 2.2) {
        p_iTotal[p_oTree->GetSpecies()]++;
      }
      if (2 != p_oTree->GetSpecies()) {
        p_oTree->GetValue(p_oPop->GetIntDataCode("YearsInfested", p_oTree->GetSpecies(), p_oTree->GetType()), &iInf);
        if (fDbh < 2.2) {
          EXPECT_EQ(0, iInf);
        } else {
          if (iInf > 0) p_iInfested[p_oTree->GetSpecies()]++;
        }
        if (3 == p_oTree->GetSpecies() && !bNoInfestation) {
          if (fabs(fDbh - 2.68) < 0.1) {
            EXPECT_EQ(3, iInf);
          } else if (fabs(fDbh - 5.26) < 0.1) {
            EXPECT_EQ(6, iInf);
          }
        }
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }
}

