//---------------------------------------------------------------------------
// TestDensDepInfestation.cpp
//---------------------------------------------------------------------------
#include "TestDensDepInfestation.h"
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
TEST(DensDepInfestation, TestErrorProcessing)
{
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try
  {
    p_oSimManager->ReadFile( WriteDensDepInfestationXMLErrorFile1() );
    FAIL()  << "TestDensDepInfestation error processing didn't catch error for WriteDensDepInfestationXMLErrorFile1.";
  }
  catch ( modelErr& err )
  {
    if ( err.sFunction.compare("clDensDepInfestation::ReadParFile" ) != 0 )
    {
      FAIL()  << "TestDensDepInfestation error processing caught wrong error for WriteDensDepInfestationXMLErrorFile1.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile( WriteDensDepInfestationXMLErrorFile2() );
    FAIL()  << "TestDensDepInfestation error processing didn't catch error for WriteDensDepInfestationXMLErrorFile2.";
  }
  catch ( modelErr& err )
  {
    if ( err.sFunction.compare("clDensDepInfestation::RegisterTreeDataMembers" ) != 0 )
    {
      FAIL()  << "TestDensDepInfestation error processing caught wrong error for WriteDensDepInfestationXMLErrorFile2.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile( WriteDensDepInfestationXMLErrorFile3() );
    FAIL()  << "TestDensDepInfestation error processing didn't catch error for WriteDensDepInfestationXMLErrorFile3.";
  }
  catch ( modelErr& err )
  {
    if ( err.sFunction.compare("clDensDepInfestation::ReadParFile" ) != 0 )
    {
      FAIL()  << "TestDensDepInfestation error processing caught wrong error for WriteDensDepInfestationXMLErrorFile3.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile( WriteDensDepInfestationXMLErrorFile4() );
    FAIL()  << "TestDensDepInfestation error processing didn't catch error for WriteDensDepInfestationXMLErrorFile4.";
  }
  catch ( modelErr& err )
  {
    if ( err.sFunction.compare("clDensDepInfestation::ReadParFile" ) != 0 )
    {
      FAIL()  << "TestDensDepInfestation error processing caught wrong error for WriteDensDepInfestationXMLErrorFile4.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile( WriteDensDepInfestationXMLErrorFile5() );
    FAIL()  << "TestDensDepInfestation error processing didn't catch error for WriteDensDepInfestationXMLErrorFile5.";
  }
  catch ( modelErr& err )
  {
    if ( err.sFunction.compare("clDensDepInfestation::ReadParFile" ) != 0 )
    {
      FAIL()  << "TestDensDepInfestation error processing caught wrong error for WriteDensDepInfestationXMLErrorFile5.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile( WriteDensDepInfestationXMLErrorFile6() );
    FAIL()  << "TestDensDepInfestation error processing didn't catch error for WriteDensDepInfestationXMLErrorFile6.";
  }
  catch ( modelErr& err )
  {
    if ( err.sFunction.compare("clDensDepInfestation::ReadParFile" ) != 0 )
    {
      FAIL()  << "TestDensDepInfestation error processing caught wrong error for WriteDensDepInfestationXMLErrorFile6.";
    }
    ;
  }
  delete p_oSimManager;
}

/////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun1()
/////////////////////////////////////////////////////////////////////////////
TEST(DensDepInfestation, TestNormalProcessingRun1)
{
  clTreePopulation * p_oPop;
  long iInfested;
  long *p_iResistant = new long[3], *p_iCondSusc = new long[3], *p_iResistant2 = new long[3], *p_iCondSusc2 = new long[3];
  float fDbh, fX, fY;
  int i, iInf;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    //Feed our file to the sim manager
    p_oSimManager->ReadFile( WriteDensDepInfestationXMLFile1());

    //Get the tree population
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //---------------------------------------------------------------------
    //Add 1000 trees of each species, to start.
    // Trees below minimum infestibility
    /*fDbh = 4;
    for ( i = 0; i < 1000; i++ ) {
      fX = clModelMath::GetRand() * 99;
      fY = clModelMath::GetRand() * 99;
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::sapling, fDbh );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::sapling, fDbh );
      p_oPop->CreateTree( fX, fY, 2, clTreePopulation::sapling, fDbh );
    }*/

    // Bigger trees
    fDbh = 7.6;
    for ( i = 0; i < 1000; i++ ) {
      fX = clModelMath::GetRand() * 99;
      fY = clModelMath::GetRand() * 99;
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::sapling, fDbh );
    }

    fDbh = 6;
    for ( i = 0; i < 1000; i++ ) {
      fX = clModelMath::GetRand() * 99;
      fY = clModelMath::GetRand() * 99;
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::sapling, fDbh );
    }

    fDbh = 4;
    for ( i = 0; i < 1000; i++ ) {
      fX = clModelMath::GetRand() * 99;
      fY = clModelMath::GetRand() * 99;
      p_oPop->CreateTree( fX, fY, 2, clTreePopulation::sapling, fDbh );
    }

    //---------------------------------------------------------------------
    // Timestep 1
    // Infestation not yet started.
    p_oSimManager->RunSim( 1 );
    clTreeSearch *p_oAllTrees = p_oPop->Find( "all" );
    clTree *p_oTree = p_oAllTrees->NextTree();

    while (p_oTree) {
      if (0 != p_oTree->GetSpecies()) {
        p_oTree->GetValue(p_oPop->GetIntDataCode("YearsInfested", p_oTree->GetSpecies(), p_oTree->GetType()), &iInf);
        EXPECT_EQ(0, iInf);
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    //---------------------------------------------------------------------
    // Timestep 2
    // Infestation not yet started.
    p_oSimManager->RunSim( 1 );
    p_oAllTrees = p_oPop->Find( "all" );
    p_oTree = p_oAllTrees->NextTree();

    while (p_oTree) {
      if (0 != p_oTree->GetSpecies()) {
        p_oTree->GetValue(p_oPop->GetIntDataCode("YearsInfested", p_oTree->GetSpecies(), p_oTree->GetType()), &iInf);
        EXPECT_EQ(0, iInf);
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    //---------------------------------------------------------------------
    // Timestep 3
    // First year of infestation
    p_oSimManager->RunSim( 1 );
    p_oAllTrees = p_oPop->Find( "all" );
    p_oTree = p_oAllTrees->NextTree();
    iInfested = 0;
    for (i = 0; i < 3; i++) {p_iResistant[i] = 0; p_iCondSusc[i] = 0;}

    //Check resistance status
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDbh);
      if (0 != p_oTree->GetSpecies()) {
        p_oTree->GetValue(p_oPop->GetIntDataCode("DensDepResistanceStatus", p_oTree->GetSpecies(), p_oTree->GetType()), &iInf);
        if (iInf == resistant) p_iResistant[p_oTree->GetSpecies()]++;
        else if (iInf == cond_susceptible) p_iCondSusc[p_oTree->GetSpecies()]++;
      }
      p_oTree = p_oAllTrees->NextTree();
    }
    //Species 2 resistant - 1% of 1000 trees = around 10
    ASSERT_TRUE(p_iResistant[1] < 30);
    //Species 3 resistant - 5% of 2000 trees = around 50
    ASSERT_TRUE(p_iResistant[2] > 38 && p_iResistant[2] < 62);
    //Species 2 conditionally susceptible - 20% of 1000 trees = around 200
    ASSERT_TRUE(p_iCondSusc[1] > 180 && p_iCondSusc[1] < 220);
    //Species 3 conditionally susceptible - 30% of 1000 trees = around 300
    ASSERT_TRUE(p_iCondSusc[2] > 270 && p_iCondSusc[2] < 430);

    //Check infestation
    p_oAllTrees->StartOver();
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDbh);
      if (0 != p_oTree->GetSpecies()) {
        p_oTree->GetValue(p_oPop->GetIntDataCode("YearsInfested", p_oTree->GetSpecies(), p_oTree->GetType()), &iInf);
        if (fDbh < 5) {
          EXPECT_EQ(0, iInf);
        } else {
          if (iInf > 0) {
            iInfested++;
            EXPECT_EQ(1, iInf);
          }
        }
      }
      p_oTree = p_oAllTrees->NextTree();
    }
    //Should be about 589 infested
    ASSERT_TRUE(fabs(iInfested - 589.0)/ iInfested < 0.1 );



    //---------------------------------------------------------------------
    // Timestep 4
    // Second year of infestation
    p_oSimManager->RunSim( 1 );
    p_oAllTrees = p_oPop->Find( "all" );
    p_oTree = p_oAllTrees->NextTree();
    iInfested = 0;
    for (i = 0; i < 3; i++) {p_iResistant2[i] = 0; p_iCondSusc2[i] = 0;}

    //Check resistance status is the same
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDbh);
      if (0 != p_oTree->GetSpecies()) {
        p_oTree->GetValue(p_oPop->GetIntDataCode("DensDepResistanceStatus", p_oTree->GetSpecies(), p_oTree->GetType()), &iInf);
        if (iInf == resistant) p_iResistant2[p_oTree->GetSpecies()]++;
        else if (iInf == cond_susceptible) p_iCondSusc2[p_oTree->GetSpecies()]++;
      }
      p_oTree = p_oAllTrees->NextTree();
    }
    for (i = 0; i < 3; i++) {
    EXPECT_EQ(p_iResistant[i], p_iResistant2[i]);
    EXPECT_EQ(p_iCondSusc[i], p_iCondSusc2[i]);
    }
    delete[] p_iCondSusc2; delete[] p_iResistant2;

    //Check infestation
    p_oAllTrees->StartOver();
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDbh);
      if (0 != p_oTree->GetSpecies()) {
        p_oTree->GetValue(p_oPop->GetIntDataCode("YearsInfested", p_oTree->GetSpecies(), p_oTree->GetType()), &iInf);
        if (fDbh < 5) {
          EXPECT_EQ(0, iInf);
        } else {
          if (iInf > 0) {
            iInfested++;
          }
        }
      }
      p_oTree = p_oAllTrees->NextTree();
    }
    //Should be about 1225 infested
    ASSERT_TRUE(fabs(iInfested - 1225.0)/ iInfested < 0.1 );

    //---------------------------------------------------------------------
    // Timestep 5
    // Third year of infestation
    p_oSimManager->RunSim( 1 );
    p_oAllTrees = p_oPop->Find( "all" );
    p_oTree = p_oAllTrees->NextTree();
    iInfested = 0;

    //Check infestation
    p_oAllTrees->StartOver();
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDbh);
      if (0 != p_oTree->GetSpecies()) {
        p_oTree->GetValue(p_oPop->GetIntDataCode("YearsInfested", p_oTree->GetSpecies(), p_oTree->GetType()), &iInf);
        if (fDbh < 5) {
          EXPECT_EQ(0, iInf);
        } else {
          if (iInf > 0) {
            iInfested++;
          }
        }
      }
      p_oTree = p_oAllTrees->NextTree();
    }
    //Should be about 1663 infested
    ASSERT_TRUE(fabs(iInfested - 1663.0)/ iInfested < 0.1 );

    //---------------------------------------------------------------------
    // Timestep 6
    // Fourth year of infestation
    p_oSimManager->RunSim( 1 );
    p_oAllTrees = p_oPop->Find( "all" );
    p_oTree = p_oAllTrees->NextTree();
    iInfested = 0;

    //Check infestation
    p_oAllTrees->StartOver();
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDbh);
      if (0 != p_oTree->GetSpecies()) {
        p_oTree->GetValue(p_oPop->GetIntDataCode("YearsInfested", p_oTree->GetSpecies(), p_oTree->GetType()), &iInf);
        if (fDbh < 5) {
          EXPECT_EQ(0, iInf);
        } else {
          if (iInf > 0) {
            iInfested++;
          }
        }
      }
      p_oTree = p_oAllTrees->NextTree();
    }
    //Should be about 1871 infested
    ASSERT_TRUE(fabs(iInfested - 1871.0)/ iInfested < 0.1 );

    //---------------------------------------------------------------------
    // Timestep 7
    // Fifth year of infestation
    // At this point, only resistant trees should be left
    p_oSimManager->RunSim( 1 );
    p_oAllTrees = p_oPop->Find( "all" );
    p_oTree = p_oAllTrees->NextTree();
    iInfested = 0;

    //Check infestation
    p_oAllTrees->StartOver();
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDbh);
      if (0 != p_oTree->GetSpecies()) {
        p_oTree->GetValue(p_oPop->GetIntDataCode("YearsInfested", p_oTree->GetSpecies(), p_oTree->GetType()), &iInf);
        if (fDbh < 5) {
          EXPECT_EQ(0, iInf);
        } else {
          if (iInf > 0) {
            iInfested++;
          } else {
            p_oTree->GetValue(p_oPop->GetIntDataCode("DensDepResistanceStatus", p_oTree->GetSpecies(), p_oTree->GetType()), &iInf);
            EXPECT_EQ(iInf, resistant);
          }
        }
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    EXPECT_EQ(iInfested, 2000 - (p_iResistant[1] + p_iResistant[2]));

    delete[] p_iResistant;
    delete[] p_iCondSusc;
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete[] p_iResistant;
    delete[] p_iCondSusc;
    delete p_oSimManager;
    FAIL()  << "Testing failed in function: "  << e.sFunction  << " with message: "  << e.sMoreInfo;
  }
}


/////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun2()
/////////////////////////////////////////////////////////////////////////////
TEST(DensDepInfestation, TestNormalProcessingRun2)
{
  clTreePopulation * p_oPop;
  long iInfested;
  float fDbh, fX, fY;
  int i, iInf;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    //Feed our file to the sim manager
    p_oSimManager->ReadFile( WriteDensDepInfestationXMLFile2());

    //Get the tree population
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //---------------------------------------------------------------------
    //Add 1000 trees of each species, to start.
    // Trees below minimum infestibility
    fDbh = 4;
    for ( i = 0; i < 1000; i++ ) {
      fX = clModelMath::GetRand() * 99;
      fY = clModelMath::GetRand() * 99;
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::sapling, fDbh );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::sapling, fDbh );
      p_oPop->CreateTree( fX, fY, 2, clTreePopulation::sapling, fDbh );
    }

    // Bigger trees
    fDbh = 13;
    for ( i = 0; i < 1000; i++ ) {
      fX = clModelMath::GetRand() * 99;
      fY = clModelMath::GetRand() * 99;
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::sapling, fDbh );
    }

    fDbh = 6;
    for ( i = 0; i < 1000; i++ ) {
      fX = clModelMath::GetRand() * 99;
      fY = clModelMath::GetRand() * 99;
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::sapling, fDbh );
    }

    fDbh = 12;
    for ( i = 0; i < 1000; i++ ) {
      fX = clModelMath::GetRand() * 99;
      fY = clModelMath::GetRand() * 99;
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::sapling, fDbh );
    }

    fDbh = 8;
    for ( i = 0; i < 1000; i++ ) {
      fX = clModelMath::GetRand() * 99;
      fY = clModelMath::GetRand() * 99;
      p_oPop->CreateTree( fX, fY, 2, clTreePopulation::sapling, fDbh );
    }

    fDbh = 17;
    for ( i = 0; i < 1000; i++ ) {
      fX = clModelMath::GetRand() * 99;
      fY = clModelMath::GetRand() * 99;
      p_oPop->CreateTree( fX, fY, 2, clTreePopulation::sapling, fDbh );
    }

    //---------------------------------------------------------------------
    // Timestep 1
    // First year of infestation
    p_oSimManager->RunSim( 1 );
    clTreeSearch *p_oAllTrees = p_oPop->Find( "all" );
    clTree *p_oTree = p_oAllTrees->NextTree();
    iInfested = 0;

    //Check infestation
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDbh);
      if (0 != p_oTree->GetSpecies()) {
        p_oTree->GetValue(p_oPop->GetIntDataCode("YearsInfested", p_oTree->GetSpecies(), p_oTree->GetType()), &iInf);
        if ((p_oTree->GetSpecies() == 1 && fDbh < 10) ||
            (p_oTree->GetSpecies() == 2 && fDbh < 15)) {
          EXPECT_EQ(0, iInf);
        } else {
          if (iInf > 0) {
            iInfested++;
            EXPECT_EQ(1, iInf);
          }
        }
      }
      p_oTree = p_oAllTrees->NextTree();
    }
    //Should be about 1179 infested
    ASSERT_TRUE(fabs(iInfested - 1179.0)/ iInfested < 0.1 );



    //---------------------------------------------------------------------
    // Timestep 2
    // Second year of infestation
    p_oSimManager->RunSim( 1 );
    p_oAllTrees = p_oPop->Find( "all" );
    p_oTree = p_oAllTrees->NextTree();
    iInfested = 0;

    //Check infestation
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDbh);
      if (0 != p_oTree->GetSpecies()) {
        p_oTree->GetValue(p_oPop->GetIntDataCode("YearsInfested", p_oTree->GetSpecies(), p_oTree->GetType()), &iInf);
        if (fDbh < 5) {
          ASSERT_EQ(0, iInf);
        } else if ((p_oTree->GetSpecies() == 1 && fDbh > 10) ||
                   (p_oTree->GetSpecies() == 2 && fDbh > 15)) {
          ASSERT_GT(iInf, 0);
          iInfested++;
        } else {
          if (iInf > 0) {
            iInfested++;
          }
        }
      }
      p_oTree = p_oAllTrees->NextTree();
    }
    //Should be about 2499 infested
    ASSERT_TRUE(fabs(iInfested - 2499.0)/ iInfested < 0.1 );

    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL()  << "Testing failed in function: "  << e.sFunction  << " with message: "  << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun3()
/////////////////////////////////////////////////////////////////////////////
TEST(DensDepInfestation, TestNormalProcessingRun3)
{
  clTreePopulation * p_oPop;
  long *p_iYrInfested = new long[6]; //Number assigned each year of infestation
  long iInfested;
  float fDbh;
  int i, iInf;

  for (i = 0; i < 6; i++) p_iYrInfested[i] = 0;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    //Feed our file to the sim manager
    p_oSimManager->ReadFile( WriteDensDepInfestationXMLFile3());

    //Get the tree population
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //---------------------------------------------------------------------
    // Timestep 1
    // Sixth year of infestation
    p_oSimManager->RunSim( 1 );
    clTreeSearch *p_oAllTrees = p_oPop->Find( "all" );
    clTree *p_oTree = p_oAllTrees->NextTree();
    iInfested = 0;

    //Check infestation
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDbh);
      if (0 == p_oTree->GetSpecies()) {
        p_oTree->GetValue(p_oPop->GetIntDataCode("YearsInfested", p_oTree->GetSpecies(), p_oTree->GetType()), &iInf);
        EXPECT_LT(iInf, 7);
        if (iInf > 0) {
          iInfested++;
          p_iYrInfested[(iInf-1)]++;
        }
      }
      p_oTree = p_oAllTrees->NextTree();
    }
    //Should be about 841 infested
    ASSERT_TRUE(fabs(iInfested - 841.0)/ iInfested < 0.1 );

    //Infested for 1 year: about 66
    ASSERT_TRUE(fabs(p_iYrInfested[0] - 66.0)/ p_iYrInfested[0] < 0.15 );

    //Infested for 2 years: about 89
    ASSERT_TRUE(fabs(p_iYrInfested[1] - 89.0)/ p_iYrInfested[2] < 0.1 );

    //Infested for 3 years: about 113
    ASSERT_TRUE(fabs(p_iYrInfested[2] - 113.0)/ p_iYrInfested[2] < 0.1 );

    //Infested for 4 years: about 134
    ASSERT_TRUE(fabs(p_iYrInfested[3] - 134.0)/ p_iYrInfested[3] < 0.1 );

    //Infested for 5 years: about 143
    ASSERT_TRUE(fabs(p_iYrInfested[4] - 143.0)/ p_iYrInfested[4] < 0.1 );

    //Infested for 6 years: about 294
    ASSERT_TRUE(fabs(p_iYrInfested[5] - 294.0)/ p_iYrInfested[5] < 0.1 );


    delete[] p_iYrInfested;
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete[] p_iYrInfested;
    delete p_oSimManager;
    FAIL()  << "Testing failed in function: "  << e.sFunction  << " with message: "  << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun4()
// Tests end date to infestation
/////////////////////////////////////////////////////////////////////////////
TEST(DensDepInfestation, TestNormalProcessingRun4)
{
  clTreePopulation * p_oPop;
  long iInfested;
  float fDbh;
  int i, iInf;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    //Feed our file to the sim manager
    p_oSimManager->ReadFile( WriteDensDepInfestationXMLFile4());

    //Get the tree population
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //---------------------------------------------------------------------
    // Timestep 1
    p_oSimManager->RunSim( 1 );
    clTreeSearch *p_oAllTrees = p_oPop->Find( "all" );
    clTree *p_oTree = p_oAllTrees->NextTree();
    iInfested = 0;

    //Check infestation
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDbh);
      if (0 == p_oTree->GetSpecies()) {
        p_oTree->GetValue(p_oPop->GetIntDataCode("YearsInfested", p_oTree->GetSpecies(), p_oTree->GetType()), &iInf);
        if (iInf > 0) {
          iInfested++;
        }
      }
      p_oTree = p_oAllTrees->NextTree();
    }
    //Should be about 294 infested
    ASSERT_TRUE(fabs(iInfested - 294.0)/ iInfested < 0.1 );

    //---------------------------------------------------------------------
    // Timestep 2
    p_oSimManager->RunSim( 1 );
    p_oAllTrees = p_oPop->Find( "all" );
    p_oTree = p_oAllTrees->NextTree();
    iInfested = 0;

    //Check infestation
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDbh);
      if (0 == p_oTree->GetSpecies()) {
        p_oTree->GetValue(p_oPop->GetIntDataCode("YearsInfested", p_oTree->GetSpecies(), p_oTree->GetType()), &iInf);
        if (iInf > 0) {
          iInfested++;
        }
      }
      p_oTree = p_oAllTrees->NextTree();
    }
    //Should be about 438 infested
    ASSERT_TRUE(fabs(iInfested - 438.0)/ iInfested < 0.1 );

    //---------------------------------------------------------------------
    // Timestep 3
    p_oSimManager->RunSim( 1 );
    p_oAllTrees = p_oPop->Find( "all" );
    p_oTree = p_oAllTrees->NextTree();
    iInfested = 0;

    //Check infestation
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDbh);
      if (0 == p_oTree->GetSpecies()) {
        p_oTree->GetValue(p_oPop->GetIntDataCode("YearsInfested", p_oTree->GetSpecies(), p_oTree->GetType()), &iInf);
        if (iInf > 0) {
          iInfested++;
        }
      }
      p_oTree = p_oAllTrees->NextTree();
    }
    //Should be about 572 infested
    ASSERT_TRUE(fabs(iInfested - 572.0)/ iInfested < 0.1 );

    //---------------------------------------------------------------------
    // Timestep 4 - infestation ends
    for (i = 0; i < 10; i++) {
      p_oSimManager->RunSim( 1 );
      p_oAllTrees = p_oPop->Find( "all" );
      p_oTree = p_oAllTrees->NextTree();
      iInfested = 0;

      //Check infestation
      while (p_oTree) {
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDbh);
        if (0 == p_oTree->GetSpecies()) {
          p_oTree->GetValue(p_oPop->GetIntDataCode("YearsInfested", p_oTree->GetSpecies(), p_oTree->GetType()), &iInf);
          ASSERT_EQ(0, iInf);
        }
        p_oTree = p_oAllTrees->NextTree();
      }
    }


    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL()  << "Testing failed in function: "  << e.sFunction  << " with message: "  << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// WriteDensDepInfestationXMLFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteDensDepInfestationXMLFile1()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  WriteDensDepNormalProcessingCommonStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>DensDepInfestation</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>ConstRadialGrowth</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
       << "</behavior>"
       << "</behaviorList>";

  oOut << "<DensDepInfestation1>"
       << "<di_densDepInfMaxInfestation>1</di_densDepInfMaxInfestation>"
       << "<di_densDepInfA>0.2</di_densDepInfA>"
       << "<di_densDepInfBx>1</di_densDepInfBx>"
       << "<di_densDepInfBy>0.2</di_densDepInfBy>"
       << "<di_densDepInfMinDBH>"
       << "<di_ddimdVal species=\"Species_2\">5</di_ddimdVal>"
       << "<di_ddimdVal species=\"Species_3\">5</di_ddimdVal>"
       << "</di_densDepInfMinDBH>"
       << "<di_densDepInfCohortDBH>"
       << "<di_ddicdVal species=\"Species_2\">0</di_ddicdVal>"
       << "<di_ddicdVal species=\"Species_3\">0</di_ddicdVal>"
       << "</di_densDepInfCohortDBH>"
       << "<di_densDepInfPropResistant>"
       << "<di_ddiprVal species=\"Species_2\">0.01</di_ddiprVal>"
       << "<di_ddiprVal species=\"Species_3\">0.05</di_ddiprVal>"
       << "</di_densDepInfPropResistant>"
       << "<di_densDepInfPropCondSusceptible>"
       << "<di_ddipcsVal species=\"Species_2\">0.2</di_ddipcsVal>"
       << "<di_ddipcsVal species=\"Species_3\">0.3</di_ddipcsVal>"
       << "</di_densDepInfPropCondSusceptible>"
       << "<di_densDepInfStartYear>3</di_densDepInfStartYear>"
       << "</DensDepInfestation1>";

  oOut << "<ConstRadialGrowth2>"
       << "<gr_adultConstRadialInc>"
       << "<gr_acriVal species=\"Species_1\">6</gr_acriVal>"
       << "<gr_acriVal species=\"Species_2\">10</gr_acriVal>"
       << "<gr_acriVal species=\"Species_3\">15</gr_acriVal>"
       << "</gr_adultConstRadialInc>"
       << "</ConstRadialGrowth2>";

  oOut << "</paramFile>";

  oOut.close();

  return cFileString;

}

/////////////////////////////////////////////////////////////////////////////
// WriteDensDepInfestationXMLFile2()
/////////////////////////////////////////////////////////////////////////////
const char* WriteDensDepInfestationXMLFile2()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  WriteDensDepNormalProcessingCommonStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>DensDepInfestation</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StochasticMortality</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RemoveDead</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
       << "</behavior>"
       << "</behaviorList>";

  oOut << "<DensDepInfestation1>"
       << "<di_densDepInfMaxInfestation>1</di_densDepInfMaxInfestation>"
       << "<di_densDepInfA>0.2</di_densDepInfA>"
       << "<di_densDepInfBx>0.8</di_densDepInfBx>"
       << "<di_densDepInfBy>0.2</di_densDepInfBy>"
       << "<di_densDepInfMinDBH>"
       << "<di_ddimdVal species=\"Species_2\">5</di_ddimdVal>"
       << "<di_ddimdVal species=\"Species_3\">5</di_ddimdVal>"
       << "</di_densDepInfMinDBH>"
       << "<di_densDepInfCohortDBH>"
       << "<di_ddicdVal species=\"Species_2\">10</di_ddicdVal>"
       << "<di_ddicdVal species=\"Species_3\">15</di_ddicdVal>"
       << "</di_densDepInfCohortDBH>"
       << "<di_densDepInfPropResistant>"
       << "<di_ddiprVal species=\"Species_2\">0</di_ddiprVal>"
       << "<di_ddiprVal species=\"Species_3\">0</di_ddiprVal>"
       << "</di_densDepInfPropResistant>"
       << "<di_densDepInfPropCondSusceptible>"
       << "<di_ddipcsVal species=\"Species_2\">0.2</di_ddipcsVal>"
       << "<di_ddipcsVal species=\"Species_3\">0.3</di_ddipcsVal>"
       << "</di_densDepInfPropCondSusceptible>"
       << "<di_densDepInfStartYear>1</di_densDepInfStartYear>"
       << "</DensDepInfestation1>";

  oOut << "<StochasticMortality2>"
       << "<mo_stochasticMortRate>"
       << "<mo_smrVal species=\"Species_1\">1.0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_2\">0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_3\">0</mo_smrVal >"
       << "</mo_stochasticMortRate>"
       << "</StochasticMortality2>";

  oOut << "</paramFile>";

  oOut.close();

  return cFileString;

}

/////////////////////////////////////////////////////////////////////////////
// WriteDensDepInfestationXMLFile3()
/////////////////////////////////////////////////////////////////////////////
const char* WriteDensDepInfestationXMLFile3()
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
       << "<yearsPerTimestep>1</yearsPerTimestep>";

  oOut << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>100</plot_lenX>"
       << "<plot_lenY>100</plot_lenY>"
       << "<plot_precip_mm_yr>1150.64</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88</plot_temp_C>"
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
       << "<tr_treemap>"
       << "<tm_treeSettings sp=\"Species_1\" tp=\"3\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_2\" tp=\"3\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>";
  for (int i = 0; i < 1000; i++) {
    oOut << "<tree sp=\"0\" tp=\"3\">"
         << "<fl c=\"0\">" << clModelMath::GetRand() * 99 << "</fl>" //X
         << "<fl c=\"1\">" << clModelMath::GetRand() * 99 << "</fl>" //Y
         << "<fl c=\"2\">20</fl>" //DBH
         << "</tree>";
  }
  for (int i = 0; i < 1000; i++) {
    oOut << "<tree sp=\"1\" tp=\"3\">"
         << "<fl c=\"0\">" << clModelMath::GetRand() * 99 << "</fl>" //X
         << "<fl c=\"1\">" << clModelMath::GetRand() * 99 << "</fl>" //Y
         << "<fl c=\"2\">15</fl>" //DBH
         << "</tree>";
  }
  oOut << "</tr_treemap>"
       << "</trees>"
       << "<allometry>"
       << "<tr_adultLinearSlope>"
       << "<tr_alsVal species=\"Species_1\">1</tr_alsVal>"
       << "<tr_alsVal species=\"Species_2\">1</tr_alsVal>"
       << "</tr_adultLinearSlope>"
       << "<tr_adultLinearIntercept>"
       << "<tr_aliVal species=\"Species_1\">0</tr_aliVal>"
       << "<tr_aliVal species=\"Species_2\">0</tr_aliVal>"
       << "</tr_adultLinearIntercept>"
       << "<tr_saplingLinearSlope>"
       << "<tr_salsVal species=\"Species_1\">1</tr_salsVal>"
       << "<tr_salsVal species=\"Species_2\">1</tr_salsVal>"
       << "</tr_saplingLinearSlope>"
       << "<tr_saplingLinearIntercept>"
       << "<tr_saliVal species=\"Species_1\">0</tr_saliVal>"
       << "<tr_saliVal species=\"Species_2\">0</tr_saliVal>"
       << "</tr_saplingLinearIntercept>"
       << "<tr_seedlingLinearSlope>"
       << "<tr_selsVal species=\"Species_1\">1</tr_selsVal>"
       << "<tr_selsVal species=\"Species_2\">1</tr_selsVal>"
       << "</tr_seedlingLinearSlope>"
       << "<tr_seedlingLinearIntercept>"
       << "<tr_seliVal species=\"Species_1\">0</tr_seliVal>"
       << "<tr_seliVal species=\"Species_2\">0</tr_seliVal>"
       << "</tr_seedlingLinearIntercept>"
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
       << "<tr_stdMaxCrownRad>"
      << "<tr_smcrVal species=\"Species_1\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Species_2\">10</tr_smcrVal>"
      << "</tr_stdMaxCrownRad>"
      << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_2\">0.03418</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "<tr_whatSeedlingHeightDiam>"
       << "<tr_wsehdVal species=\"Species_1\">1</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_2\">1</tr_wsehdVal>"
       << "</tr_whatSeedlingHeightDiam>"
       << "<tr_whatSaplingHeightDiam>"
       << "<tr_wsahdVal species=\"Species_1\">1</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_2\">1</tr_wsahdVal>"
       << "</tr_whatSaplingHeightDiam>"
       << "<tr_whatAdultHeightDiam>"
       << "<tr_wahdVal species=\"Species_1\">1</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_2\">1</tr_wahdVal>"
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
       << "<behaviorName>DensDepInfestation</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>";

  oOut << "<DensDepInfestation1>"
       << "<di_densDepInfMaxInfestation>1</di_densDepInfMaxInfestation>"
       << "<di_densDepInfA>0.2</di_densDepInfA>"
       << "<di_densDepInfBx>0.3</di_densDepInfBx>"
       << "<di_densDepInfBy>0.2</di_densDepInfBy>"
       << "<di_densDepInfMinDBH>"
       << "<di_ddimdVal species=\"Species_1\">0</di_ddimdVal>"
       << "</di_densDepInfMinDBH>"
       << "<di_densDepInfCohortDBH>"
       << "<di_ddicdVal species=\"Species_1\">0</di_ddicdVal>"
       << "</di_densDepInfCohortDBH>"
       << "<di_densDepInfPropResistant>"
       << "<di_ddiprVal species=\"Species_1\">0</di_ddiprVal>"
       << "</di_densDepInfPropResistant>"
       << "<di_densDepInfPropCondSusceptible>"
       << "<di_ddipcsVal species=\"Species_1\">0.2</di_ddipcsVal>"
       << "</di_densDepInfPropCondSusceptible>"
       << "<di_densDepInfStartYear>-5</di_densDepInfStartYear>"
       << "<di_densDepInfEndYear>-1</di_densDepInfEndYear>"
       << "</DensDepInfestation1>";

  oOut << "</paramFile>";

  oOut.close();

  return cFileString;

}

/////////////////////////////////////////////////////////////////////////////
// WriteDensDepInfestationXMLFile4()
/////////////////////////////////////////////////////////////////////////////
const char* WriteDensDepInfestationXMLFile4()
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
       << "<yearsPerTimestep>1</yearsPerTimestep>";

  oOut << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>100</plot_lenX>"
       << "<plot_lenY>100</plot_lenY>"
       << "<plot_precip_mm_yr>1150.64</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88</plot_temp_C>"
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
       << "<tr_treemap>"
       << "<tm_treeSettings sp=\"Species_1\" tp=\"3\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_2\" tp=\"3\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>";
  for (int i = 0; i < 1000; i++) {
    oOut << "<tree sp=\"0\" tp=\"3\">"
         << "<fl c=\"0\">" << clModelMath::GetRand() * 99 << "</fl>" //X
         << "<fl c=\"1\">" << clModelMath::GetRand() * 99 << "</fl>" //Y
         << "<fl c=\"2\">20</fl>" //DBH
         << "</tree>";
  }
  for (int i = 0; i < 1000; i++) {
    oOut << "<tree sp=\"1\" tp=\"3\">"
         << "<fl c=\"0\">" << clModelMath::GetRand() * 99 << "</fl>" //X
         << "<fl c=\"1\">" << clModelMath::GetRand() * 99 << "</fl>" //Y
         << "<fl c=\"2\">15</fl>" //DBH
         << "</tree>";
  }
  oOut << "</tr_treemap>"
       << "</trees>"
       << "<allometry>"
       << "<tr_adultLinearSlope>"
       << "<tr_alsVal species=\"Species_1\">1</tr_alsVal>"
       << "<tr_alsVal species=\"Species_2\">1</tr_alsVal>"
       << "</tr_adultLinearSlope>"
       << "<tr_adultLinearIntercept>"
       << "<tr_aliVal species=\"Species_1\">0</tr_aliVal>"
       << "<tr_aliVal species=\"Species_2\">0</tr_aliVal>"
       << "</tr_adultLinearIntercept>"
       << "<tr_saplingLinearSlope>"
       << "<tr_salsVal species=\"Species_1\">1</tr_salsVal>"
       << "<tr_salsVal species=\"Species_2\">1</tr_salsVal>"
       << "</tr_saplingLinearSlope>"
       << "<tr_saplingLinearIntercept>"
       << "<tr_saliVal species=\"Species_1\">0</tr_saliVal>"
       << "<tr_saliVal species=\"Species_2\">0</tr_saliVal>"
       << "</tr_saplingLinearIntercept>"
       << "<tr_seedlingLinearSlope>"
       << "<tr_selsVal species=\"Species_1\">1</tr_selsVal>"
       << "<tr_selsVal species=\"Species_2\">1</tr_selsVal>"
       << "</tr_seedlingLinearSlope>"
       << "<tr_seedlingLinearIntercept>"
       << "<tr_seliVal species=\"Species_1\">0</tr_seliVal>"
       << "<tr_seliVal species=\"Species_2\">0</tr_seliVal>"
       << "</tr_seedlingLinearIntercept>"
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
       << "<tr_stdMaxCrownRad>"
      << "<tr_smcrVal species=\"Species_1\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Species_2\">10</tr_smcrVal>"
      << "</tr_stdMaxCrownRad>"
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
       << "<tr_wsehdVal species=\"Species_1\">1</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_2\">1</tr_wsehdVal>"
       << "</tr_whatSeedlingHeightDiam>"
       << "<tr_whatSaplingHeightDiam>"
       << "<tr_wsahdVal species=\"Species_1\">1</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_2\">1</tr_wsahdVal>"
       << "</tr_whatSaplingHeightDiam>"
       << "<tr_whatAdultHeightDiam>"
       << "<tr_wahdVal species=\"Species_1\">1</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_2\">1</tr_wahdVal>"
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
       << "<behaviorName>DensDepInfestation</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>";

  oOut << "<DensDepInfestation1>"
       << "<di_densDepInfMaxInfestation>1</di_densDepInfMaxInfestation>"
       << "<di_densDepInfA>0.2</di_densDepInfA>"
       << "<di_densDepInfBx>0.3</di_densDepInfBx>"
       << "<di_densDepInfBy>0.2</di_densDepInfBy>"
       << "<di_densDepInfMinDBH>"
       << "<di_ddimdVal species=\"Species_1\">0</di_ddimdVal>"
       << "</di_densDepInfMinDBH>"
       << "<di_densDepInfCohortDBH>"
       << "<di_ddicdVal species=\"Species_1\">0</di_ddicdVal>"
       << "</di_densDepInfCohortDBH>"
       << "<di_densDepInfPropResistant>"
       << "<di_ddiprVal species=\"Species_1\">0</di_ddiprVal>"
       << "</di_densDepInfPropResistant>"
       << "<di_densDepInfPropCondSusceptible>"
       << "<di_ddipcsVal species=\"Species_1\">0.2</di_ddipcsVal>"
       << "</di_densDepInfPropCondSusceptible>"
       << "<di_densDepInfStartYear>1</di_densDepInfStartYear>"
       << "<di_densDepInfEndYear>4</di_densDepInfEndYear>"
       << "</DensDepInfestation1>";

  oOut << "</paramFile>";

  oOut.close();

  return cFileString;

}

/////////////////////////////////////////////////////////////////////////////
// WriteDensDepInfestationXMLErrorFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteDensDepInfestationXMLErrorFile1()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  WriteDensDepInfestationErrorCommonStuff(oOut);

  oOut << "<DensDepInfestation1>"
       << "<di_densDepInfMaxInfestation>1</di_densDepInfMaxInfestation>"
       << "<di_densDepInfA>0.2</di_densDepInfA>"
       << "<di_densDepInfBx>1</di_densDepInfBx>"
       << "<di_densDepInfBy>0.2</di_densDepInfBy>"
       << "<di_densDepInfMinDBH>"
       << "<di_ddimdVal species=\"Species_1\">-5</di_ddimdVal>"
       << "<di_ddimdVal species=\"Species_2\">5</di_ddimdVal>"
       << "</di_densDepInfMinDBH>"
       << "<di_densDepInfCohortDBH>"
       << "<di_ddicdVal species=\"Species_1\">0</di_ddicdVal>"
       << "<di_ddicdVal species=\"Species_2\">0</di_ddicdVal>"
       << "</di_densDepInfCohortDBH>"
       << "<di_densDepInfPropResistant>"
       << "<di_ddiprVal species=\"Species_1\">0.01</di_ddiprVal>"
       << "<di_ddiprVal species=\"Species_2\">0.05</di_ddiprVal>"
       << "</di_densDepInfPropResistant>"
       << "<di_densDepInfPropCondSusceptible>"
       << "<di_ddipcsVal species=\"Species_1\">0.2</di_ddipcsVal>"
       << "<di_ddipcsVal species=\"Species_2\">0.3</di_ddipcsVal>"
       << "</di_densDepInfPropCondSusceptible>"
       << "<di_densDepInfStartYear>3</di_densDepInfStartYear>"
       << "</DensDepInfestation1>";

  oOut << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteDensDepInfestationXMLErrorFile2()
/////////////////////////////////////////////////////////////////////////////
const char* WriteDensDepInfestationXMLErrorFile2()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut  << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>25</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>";

  oOut  << "<randomSeed>1</randomSeed>"
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
       << "<tr_stdMaxCrownRad>"
       << "<tr_smcrVal species=\"Species_1\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_2\">10</tr_smcrVal>"
       << "</tr_stdMaxCrownRad>"
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
       << "<behaviorName>DensDepInfestation</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>";

  oOut << "<DensDepInfestation1>"
       << "<di_densDepInfMaxInfestation>1</di_densDepInfMaxInfestation>"
       << "<di_densDepInfA>0.2</di_densDepInfA>"
       << "<di_densDepInfBx>1</di_densDepInfBx>"
       << "<di_densDepInfBy>0.2</di_densDepInfBy>"
       << "<di_densDepInfMinDBH>"
       << "<di_ddimdVal species=\"Species_1\">5</di_ddimdVal>"
       << "<di_ddimdVal species=\"Species_2\">5</di_ddimdVal>"
       << "</di_densDepInfMinDBH>"
       << "<di_densDepInfCohortDBH>"
       << "<di_ddicdVal species=\"Species_1\">0</di_ddicdVal>"
       << "<di_ddicdVal species=\"Species_2\">0</di_ddicdVal>"
       << "</di_densDepInfCohortDBH>"
       << "<di_densDepInfPropResistant>"
       << "<di_ddiprVal species=\"Species_1\">0.01</di_ddiprVal>"
       << "<di_ddiprVal species=\"Species_2\">0.05</di_ddiprVal>"
       << "</di_densDepInfPropResistant>"
       << "<di_densDepInfPropCondSusceptible>"
       << "<di_ddipcsVal species=\"Species_1\">0.2</di_ddipcsVal>"
       << "<di_ddipcsVal species=\"Species_2\">0.3</di_ddipcsVal>"
       << "</di_densDepInfPropCondSusceptible>"
       << "<di_densDepInfStartYear>3</di_densDepInfStartYear>"
       << "</DensDepInfestation1>";

  oOut << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteDensDepInfestationXMLErrorFile3()
/////////////////////////////////////////////////////////////////////////////
const char* WriteDensDepInfestationXMLErrorFile3()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  WriteDensDepInfestationErrorCommonStuff(oOut);

  oOut << "<DensDepInfestation1>"
       << "<di_densDepInfMaxInfestation>1</di_densDepInfMaxInfestation>"
       << "<di_densDepInfA>0.2</di_densDepInfA>"
       << "<di_densDepInfBx>1</di_densDepInfBx>"
       << "<di_densDepInfBy>0.2</di_densDepInfBy>"
       << "<di_densDepInfMinDBH>"
       << "<di_ddimdVal species=\"Species_1\">5</di_ddimdVal>"
       << "<di_ddimdVal species=\"Species_2\">5</di_ddimdVal>"
       << "</di_densDepInfMinDBH>"
       << "<di_densDepInfCohortDBH>"
       << "<di_ddicdVal species=\"Species_1\">0</di_ddicdVal>"
       << "<di_ddicdVal species=\"Species_2\">0</di_ddicdVal>"
       << "</di_densDepInfCohortDBH>"
       << "<di_densDepInfPropResistant>"
       << "<di_ddiprVal species=\"Species_1\">0.01</di_ddiprVal>"
       << "<di_ddiprVal species=\"Species_2\">0.05</di_ddiprVal>"
       << "</di_densDepInfPropResistant>"
       << "<di_densDepInfPropCondSusceptible>"
       << "<di_ddipcsVal species=\"Species_1\">-0.2</di_ddipcsVal>"
       << "<di_ddipcsVal species=\"Species_2\">0.3</di_ddipcsVal>"
       << "</di_densDepInfPropCondSusceptible>"
       << "<di_densDepInfStartYear>3</di_densDepInfStartYear>"
       << "</DensDepInfestation1>";

  oOut << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteDensDepInfestationXMLErrorFile4()
/////////////////////////////////////////////////////////////////////////////
const char* WriteDensDepInfestationXMLErrorFile4()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  WriteDensDepInfestationErrorCommonStuff(oOut);

  oOut << "<DensDepInfestation1>"
       << "<di_densDepInfMaxInfestation>1</di_densDepInfMaxInfestation>"
       << "<di_densDepInfA>0.2</di_densDepInfA>"
       << "<di_densDepInfBx>1</di_densDepInfBx>"
       << "<di_densDepInfBy>0.2</di_densDepInfBy>"
       << "<di_densDepInfMinDBH>"
       << "<di_ddimdVal species=\"Species_1\">5</di_ddimdVal>"
       << "<di_ddimdVal species=\"Species_2\">5</di_ddimdVal>"
       << "</di_densDepInfMinDBH>"
       << "<di_densDepInfCohortDBH>"
       << "<di_ddicdVal species=\"Species_1\">-5</di_ddicdVal>"
       << "<di_ddicdVal species=\"Species_2\">0</di_ddicdVal>"
       << "</di_densDepInfCohortDBH>"
       << "<di_densDepInfPropResistant>"
       << "<di_ddiprVal species=\"Species_1\">0.01</di_ddiprVal>"
       << "<di_ddiprVal species=\"Species_2\">0.05</di_ddiprVal>"
       << "</di_densDepInfPropResistant>"
       << "<di_densDepInfPropCondSusceptible>"
       << "<di_ddipcsVal species=\"Species_1\">0.2</di_ddipcsVal>"
       << "<di_ddipcsVal species=\"Species_2\">0.3</di_ddipcsVal>"
       << "</di_densDepInfPropCondSusceptible>"
       << "<di_densDepInfStartYear>3</di_densDepInfStartYear>"
       << "</DensDepInfestation1>";

  oOut << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteDensDepInfestationXMLErrorFile5()
/////////////////////////////////////////////////////////////////////////////
const char* WriteDensDepInfestationXMLErrorFile5()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  WriteDensDepInfestationErrorCommonStuff(oOut);

  oOut << "<DensDepInfestation1>"
       << "<di_densDepInfMaxInfestation>1.5</di_densDepInfMaxInfestation>"
       << "<di_densDepInfA>0.2</di_densDepInfA>"
       << "<di_densDepInfBx>1</di_densDepInfBx>"
       << "<di_densDepInfBy>0.2</di_densDepInfBy>"
       << "<di_densDepInfMinDBH>"
       << "<di_ddimdVal species=\"Species_1\">5</di_ddimdVal>"
       << "<di_ddimdVal species=\"Species_2\">5</di_ddimdVal>"
       << "</di_densDepInfMinDBH>"
       << "<di_densDepInfCohortDBH>"
       << "<di_ddicdVal species=\"Species_1\">0</di_ddicdVal>"
       << "<di_ddicdVal species=\"Species_2\">0</di_ddicdVal>"
       << "</di_densDepInfCohortDBH>"
       << "<di_densDepInfPropResistant>"
       << "<di_ddiprVal species=\"Species_1\">0.01</di_ddiprVal>"
       << "<di_ddiprVal species=\"Species_2\">0.05</di_ddiprVal>"
       << "</di_densDepInfPropResistant>"
       << "<di_densDepInfPropCondSusceptible>"
       << "<di_ddipcsVal species=\"Species_1\">0.2</di_ddipcsVal>"
       << "<di_ddipcsVal species=\"Species_2\">0.3</di_ddipcsVal>"
       << "</di_densDepInfPropCondSusceptible>"
       << "<di_densDepInfStartYear>3</di_densDepInfStartYear>"
       << "</DensDepInfestation1>";

  oOut << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteDensDepInfestationXMLErrorFile6()
/////////////////////////////////////////////////////////////////////////////
const char* WriteDensDepInfestationXMLErrorFile6()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  WriteDensDepInfestationErrorCommonStuff(oOut);

  oOut << "<DensDepInfestation1>"
       << "<di_densDepInfMaxInfestation>1</di_densDepInfMaxInfestation>"
       << "<di_densDepInfA>0.2</di_densDepInfA>"
       << "<di_densDepInfBx>1</di_densDepInfBx>"
       << "<di_densDepInfBy>0.2</di_densDepInfBy>"
       << "<di_densDepInfMinDBH>"
       << "<di_ddimdVal species=\"Species_1\">5</di_ddimdVal>"
       << "<di_ddimdVal species=\"Species_2\">5</di_ddimdVal>"
       << "</di_densDepInfMinDBH>"
       << "<di_densDepInfCohortDBH>"
       << "<di_ddicdVal species=\"Species_1\">0</di_ddicdVal>"
       << "<di_ddicdVal species=\"Species_2\">0</di_ddicdVal>"
       << "</di_densDepInfCohortDBH>"
       << "<di_densDepInfPropResistant>"
       << "<di_ddiprVal species=\"Species_1\">-0.01</di_ddiprVal>"
       << "<di_ddiprVal species=\"Species_2\">0.05</di_ddiprVal>"
       << "</di_densDepInfPropResistant>"
       << "<di_densDepInfPropCondSusceptible>"
       << "<di_ddipcsVal species=\"Species_1\">0.2</di_ddipcsVal>"
       << "<di_ddipcsVal species=\"Species_2\">0.3</di_ddipcsVal>"
       << "</di_densDepInfPropCondSusceptible>"
       << "<di_densDepInfStartYear>3</di_densDepInfStartYear>"
       << "</DensDepInfestation1>";

  oOut << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteDensDepInfestationErrorCommonStuff()
/////////////////////////////////////////////////////////////////////////////
void WriteDensDepInfestationErrorCommonStuff(std::fstream &oOut)
{
  using namespace std;
  oOut  << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>25</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>";

  oOut  << "<randomSeed>1</randomSeed>"
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
       << "<tr_stdMaxCrownRad>"
       << "<tr_smcrVal species=\"Species_1\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_2\">10</tr_smcrVal>"
       << "</tr_stdMaxCrownRad>"
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
       << "<behaviorName>DensDepInfestation</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>";
}


/////////////////////////////////////////////////////////////////////////////
// WriteNormalProcessingCommonStuff()
/////////////////////////////////////////////////////////////////////////////
void WriteDensDepNormalProcessingCommonStuff(std::fstream &oOut) {

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>30</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>";

  oOut << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>100</plot_lenX>"
       << "<plot_lenY>100</plot_lenY>"
       << "<plot_precip_mm_yr>1150.64</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>"
       << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\"/>"
       << "<tr_species speciesName=\"Species_2\"/>"
       << "<tr_species speciesName=\"Species_3\"/>"
       << "</tr_speciesList>"
       << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
       << "<tr_minAdultDBH>"
       << "<tr_madVal species=\"Species_1\">10</tr_madVal>"
       << "<tr_madVal species=\"Species_2\">10</tr_madVal>"
       << "<tr_madVal species=\"Species_3\">10</tr_madVal>"
       << "</tr_minAdultDBH>"
       << "<tr_maxSeedlingHeight>"
       << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_2\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_3\">1.35</tr_mshVal>"
       << "</tr_maxSeedlingHeight>"
       << "</trees>"
       << "<allometry>"
       << "<tr_adultLinearSlope>"
       << "<tr_alsVal species=\"Species_1\">1</tr_alsVal>"
       << "<tr_alsVal species=\"Species_2\">1</tr_alsVal>"
       << "<tr_alsVal species=\"Species_3\">1</tr_alsVal>"
       << "</tr_adultLinearSlope>"
       << "<tr_adultLinearIntercept>"
       << "<tr_aliVal species=\"Species_1\">0</tr_aliVal>"
       << "<tr_aliVal species=\"Species_2\">0</tr_aliVal>"
       << "<tr_aliVal species=\"Species_3\">0</tr_aliVal>"
       << "</tr_adultLinearIntercept>"
       << "<tr_saplingLinearSlope>"
       << "<tr_salsVal species=\"Species_1\">1</tr_salsVal>"
       << "<tr_salsVal species=\"Species_2\">1</tr_salsVal>"
       << "<tr_salsVal species=\"Species_3\">1</tr_salsVal>"
       << "</tr_saplingLinearSlope>"
       << "<tr_saplingLinearIntercept>"
       << "<tr_saliVal species=\"Species_1\">0</tr_saliVal>"
       << "<tr_saliVal species=\"Species_2\">0</tr_saliVal>"
       << "<tr_saliVal species=\"Species_3\">0</tr_saliVal>"
       << "</tr_saplingLinearIntercept>"
       << "<tr_seedlingLinearSlope>"
       << "<tr_selsVal species=\"Species_1\">1</tr_selsVal>"
       << "<tr_selsVal species=\"Species_2\">1</tr_selsVal>"
       << "<tr_selsVal species=\"Species_3\">1</tr_selsVal>"
       << "</tr_seedlingLinearSlope>"
       << "<tr_seedlingLinearIntercept>"
       << "<tr_seliVal species=\"Species_1\">0</tr_seliVal>"
       << "<tr_seliVal species=\"Species_2\">0</tr_seliVal>"
       << "<tr_seliVal species=\"Species_3\">0</tr_seliVal>"
       << "</tr_seedlingLinearIntercept>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_2\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_3\">39.48</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_2\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_3\">0.0549</tr_sacrVal>"
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
       << "<tr_cdtdVal species=\"Species_1\">1</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">1</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_3\">1</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_3\">0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_3\">0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_2\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_3\">0.389</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_3\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_2\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_3\">0.03418</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "<tr_whatSeedlingHeightDiam>"
       << "<tr_wsehdVal species=\"Species_1\">1</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_2\">1</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_3\">1</tr_wsehdVal>"
       << "</tr_whatSeedlingHeightDiam>"
       << "<tr_whatSaplingHeightDiam>"
       << "<tr_wsahdVal species=\"Species_1\">1</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_2\">1</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_3\">1</tr_wsahdVal>"
       << "</tr_whatSaplingHeightDiam>"
       << "<tr_whatAdultHeightDiam>"
       << "<tr_wahdVal species=\"Species_1\">1</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_2\">1</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_3\">1</tr_wahdVal>"
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
       << "</allometry>";
}
