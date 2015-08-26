//---------------------------------------------------------------------------
// TestStormKiller.cpp
//---------------------------------------------------------------------------
#include "TestStormKiller.h"
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
TEST(StormKiller, TestErrorProcessing)
{
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try
  {
    p_oSimManager->ReadFile( WriteStormKillerXMLErrorFile1() );
    FAIL() << "TestStormKiller error processing didn't catch error for WriteStormKillerXMLErrorFile1.";
  }
  catch ( modelErr& err )
  {
    if ( err.sFunction.compare("clStormKiller::GetStmDmgCodes" ) != 0 )
    {
      FAIL() << "TestStormKiller error processing caught wrong error for WriteStormKillerXMLErrorFile1.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile( WriteStormKillerXMLErrorFile2() );
    FAIL() << "TestStormKiller error processing didn't catch error for WriteStormKillerXMLErrorFile2.";
  }
  catch ( modelErr& err )
  {
    if ( err.sFunction.compare("clStormKiller::GetStmDmgCodes" ) != 0 )
    {
      FAIL() << "TestStormKiller error processing caught wrong error for WriteStormKillerXMLErrorFile2.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile( WriteStormKillerXMLErrorFile3() );
    FAIL() << "TestStormKiller error processing didn't catch error for WriteStormKillerXMLErrorFile3.";
  }
  catch ( modelErr& err )
  {
    if ( err.sFunction.compare("clStormKiller::GetStmDmgCodes" ) != 0 )
    {
      FAIL() << "TestStormKiller error processing caught wrong error for WriteStormKillerXMLErrorFile3.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile( WriteStormKillerXMLErrorFile4() );
    FAIL() << "TestStormKiller error processing didn't catch error for WriteStormKillerXMLErrorFile4.";
  }
  catch ( modelErr& err )
  {
    if ( err.sFunction.compare("clStormKiller::GetParameterFileData" ) != 0 )
    {
      FAIL() << "TestStormKiller error processing caught wrong error for WriteStormKillerXMLErrorFile4.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile( WriteStormKillerXMLErrorFile5() );
    FAIL() << "TestStormKiller error processing didn't catch error for WriteStormKillerXMLErrorFile5.";
  }
  catch ( modelErr& err )
  {
    if ( err.sFunction.compare("clStormKiller::GetParameterFileData" ) != 0 )
    {
      FAIL() << "TestStormKiller error processing caught wrong error for WriteStormKillerXMLErrorFile5.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile( WriteStormKillerXMLErrorFile6() );
    p_oSimManager->RunSim(1);
    FAIL() << "TestStormKiller error processing didn't catch error for WriteStormKillerXMLErrorFile6.";
  }
  catch ( modelErr& err )
  {
    if ( err.sFunction.compare("clStormKiller::GetDeadCodes" ) != 0 )
    {
      FAIL() << "TestStormKiller error processing caught wrong error for WriteStormKillerXMLErrorFile6.";
    }
    ;
  }
  delete p_oSimManager;
}

/////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun1()
// Tests normal processing. WriteStormKillerXMLFile1() writes the parameter file.
// Aspects of the run:
//
// -- Grid resolution of "Storm Damage" is default.
// -- Run is 5 timesteps.
// -- 1 year per timestep.
// -- Snags are present in the run.
// -- The following trees will be added:
//   -- Grid (0,0): 1000 trees of Species 1 and 2, DBH 30.  Damage counter is
//      0.
//   -- Grid (0,1): 1000 trees of Species 1 and 2, DBH 30.  Damage counter is
//      1000.
//   -- Grid (0,2): 1000 trees of Species 1 and 2, DBH 30.  Damage counter is
//      2000.
//   -- Grid (1,0): 1000 trees of Species 1 and 2, DBH 8.  Damage counter is
//      0.
//   -- Grid (1,1): 1000 trees of Species 1 and 2, DBH 8.  Damage counter is
//      1000.
//   -- Grid (1,2): 1000 trees of Species 1 and 2, DBH 8.  Damage counter is
//      2000.
//   -- All grids get 100 trees of DBH 4, Species 1, and DBH 5, Species 2,
//      which are never damaged or killed.
//   -- All grids get 100 trees of DBH 20, Species 1, Snag, which are never
//      removed.
//
// The run proceeds for 5 timesteps and the number of trees with each damage
// counter is checked through time.
/////////////////////////////////////////////////////////////////////////////
TEST(StormKiller, TestNormalProcessingRun1) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    //Feed our file to the sim manager
    p_oSimManager->ReadFile( WriteStormKillerXMLFile1() );

    //Get the tree population
    clTreePopulation * p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
    clTree * p_oTree;
    float fX, fY, fDiam;
    int i, iDmgCounter;

    //Grid (0,0): 1000 trees of Species 1 and 2, DBH 30.  Damage counter is 0.
    //100 trees of DBH 4, Species 1, and DBH 5, Species 2, and
    //100 trees of DBH 20, Species 1, Snag
    fX = 1;
    fY = 1;
    fDiam = 30;
    for ( i = 0; i < 1000; i++ )
    {
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, fDiam );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::adult, fDiam );
    }
    for ( i = 0; i < 100; i++ )
    {
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::sapling, 4.0 );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::sapling, 5.0 );
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::snag, 20.0 );
    }

    //Grid (0,1): 1000 trees of Species 1 and 2, DBH 30.  Damage counter is 1000.
    //100 trees of DBH 4, Species 1, and DBH 5, Species 2, and
    //100 trees of DBH 20, Species 1, Snag
    iDmgCounter = 1000;
    fX = 1;
    fY = 9;
    fDiam = 30;
    for ( i = 0; i < 1000; i++ )
    {
      p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, fDiam );
      p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType()), iDmgCounter);
      p_oTree = p_oPop->CreateTree( fX, fY, 1, clTreePopulation::adult, fDiam );
      p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType()), iDmgCounter);
    }
    for ( i = 0; i < 100; i++ )
    {
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::sapling, 4.0 );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::sapling, 5.0 );
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::snag, 20.0 );
    }

    //Grid (0,2): 1000 trees of Species 1 and 2, DBH 30. Damage counter is 2000.
    //100 trees of DBH 4, Species 1, and DBH 5, Species 2, and
    //100 trees of DBH 20, Species 1, Snag
    iDmgCounter = 2000;
    fX = 1;
    fY = 17;
    fDiam = 30;
    for ( i = 0; i < 1000; i++ )
    {
      p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, fDiam );
      p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType()), iDmgCounter);
      p_oTree = p_oPop->CreateTree( fX, fY, 1, clTreePopulation::adult, fDiam );
      p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType()), iDmgCounter);
    }
    for ( i = 0; i < 100; i++ )
    {
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::sapling, 4.0 );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::sapling, 5.0 );
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::snag, 20.0 );
    }

    //Grid (1,0): 1000 trees of Species 1 and 2, DBH 8.  Damage counter is 0.
    //100 trees of DBH 4, Species 1, and DBH 5, Species 2, and
    //100 trees of DBH 20, Species 1, Snag
    fX = 9;
    fY = 1;
    fDiam = 8;
    for ( i = 0; i < 1000; i++ )
    {
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, fDiam );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::adult, fDiam );
    }
    for ( i = 0; i < 100; i++ )
    {
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::sapling, 4.0 );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::sapling, 5.0 );
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::snag, 20.0 );
    }

    //Grid (1,1): 1000 trees of Species 1 and 2, DBH 8. Damage counter is 1000.
    //100 trees of DBH 4, Species 1, and DBH 5, Species 2, and
    //100 trees of DBH 20, Species 1, Snag
    iDmgCounter = 1000;
    fX = 9;
    fY = 9;
    fDiam = 8;
    for ( i = 0; i < 1000; i++ )
    {
      p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, fDiam );
      p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType()), iDmgCounter);
      p_oTree = p_oPop->CreateTree( fX, fY, 1, clTreePopulation::adult, fDiam );
      p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType()), iDmgCounter);
    }
    for ( i = 0; i < 100; i++ )
    {
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::sapling, 4.0 );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::sapling, 5.0 );
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::snag, 20.0 );
    }

    //Grid (1,2): 1000 trees of Species 1 and 2, DBH 8.  Damage counter is 2000.
    //100 trees of DBH 4, Species 1, and DBH 5, Species 2, and
    //100 trees of DBH 20, Species 1, Snag
    iDmgCounter = 2000;
    fX = 9;
    fY = 17;
    fDiam = 8;
    for ( i = 0; i < 1000; i++ )
    {
      p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, fDiam );
      p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType()), iDmgCounter);
      p_oTree = p_oPop->CreateTree( fX, fY, 1, clTreePopulation::adult, fDiam );
      p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType()), iDmgCounter);
    }
    for ( i = 0; i < 100; i++ )
    {
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::sapling, 4.0 );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::sapling, 5.0 );
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::snag, 20.0 );
    }

    //For the first timestep, only do storm killing at first so we can check
    //dead snags before they are cleaned away
    p_oSimManager->GetBehaviorObject(2)->Action();
    TestStormKillerRun1Timestep1( p_oPop );
    //Now finish
    for (i = 3; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
      p_oSimManager->GetBehaviorObject(i)->Action();
    }
    for (i = 0; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
      p_oSimManager->GetBehaviorObject(i)->TimestepCleanup();
    }

    p_oSimManager->RunSim(1);
    TestStormKillerRun1Timestep2( p_oPop );
    p_oSimManager->RunSim(1);
    TestStormKillerRun1Timestep3( p_oPop );
    p_oSimManager->RunSim(1);
    TestStormKillerRun1Timestep4( p_oPop );
    p_oSimManager->RunSim(1);
    TestStormKillerRun1Timestep5( p_oPop );
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun2()
// Tests normal processing. WriteStormKillerXMLFile2() writes the parameter file.
// Aspects of the run:
// -- Grid resolution of "Storm Damage" is default.
// -- Run is 3 timesteps.
// -- 3 year per timestep.
// -- Snags are present in the run.
// -- The following trees will be added:
//   -- Grid (0,0): 1000 trees of Species 1 and 2, DBH 30.  Damage counter is
//      0.
//   -- Grid (0,1): 1000 trees of Species 1 and 2, DBH 30.  Damage counter is
//      1000.
//   -- Grid (0,2): 1000 trees of Species 1 and 2, DBH 30.  Damage counter is
//      2000.
//   -- Grid (1,0): 1000 trees of Species 1 and 2, DBH 8.  Damage counter is
//      0.
//   -- Grid (1,1): 1000 trees of Species 1 and 2, DBH 8.  Damage counter is
//      1000.
//   -- Grid (1,2): 1000 trees of Species 1 and 2, DBH 8.  Damage counter is
//      2000.
//   -- All grids get 100 trees of DBH 4, Species 1, and DBH 5, Species 2,
//      which are never damaged or killed.
//   -- All grids get 100 trees of DBH 20, Species 1, Snag, which are never
//      removed.
//
// The run proceeds for 3 timesteps and the number of trees with each damage
// counter is checked through time.
/////////////////////////////////////////////////////////////////////////////
TEST(StormKiller, TestNormalProcessingRun2) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    //Feed our file to the sim manager
    p_oSimManager->ReadFile( WriteStormKillerXMLFile2() );

    //Get the tree population
    clTreePopulation * p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
    clTree * p_oTree;
    float fX, fY, fDiam;
    int i, iDmgCounter;

    //Grid (0,0): 1000 trees of Species 1 and 2, DBH 30.  Damage counter is 0.
    //100 trees of DBH 4, Species 1, and DBH 5, Species 2, and
    //100 trees of DBH 20, Species 1, Snag
    fX = 1;
    fY = 1;
    fDiam = 30;
    for ( i = 0; i < 1000; i++ )
    {
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, fDiam );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::adult, fDiam );
    }
    for ( i = 0; i < 100; i++ )
    {
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::sapling, 4.0 );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::sapling, 5.0 );
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::snag, 20.0 );
    }

    //Grid (0,1): 1000 trees of Species 1 and 2, DBH 30.  Damage counter is 1000.
    //100 trees of DBH 4, Species 1, and DBH 5, Species 2, and
    //100 trees of DBH 20, Species 1, Snag
    iDmgCounter = 1000;
    fX = 1;
    fY = 9;
    fDiam = 30;
    for ( i = 0; i < 1000; i++ )
    {
      p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, fDiam );
      p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType()), iDmgCounter);
      p_oTree = p_oPop->CreateTree( fX, fY, 1, clTreePopulation::adult, fDiam );
      p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType()), iDmgCounter);
    }
    for ( i = 0; i < 100; i++ )
    {
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::sapling, 4.0 );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::sapling, 5.0 );
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::snag, 20.0 );
    }

    //Grid (0,2): 1000 trees of Species 1 and 2, DBH 30. Damage counter is 2000.
    //100 trees of DBH 4, Species 1, and DBH 5, Species 2, and
    //100 trees of DBH 20, Species 1, Snag
    iDmgCounter = 2000;
    fX = 1;
    fY = 17;
    fDiam = 30;
    for ( i = 0; i < 1000; i++ )
    {
      p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, fDiam );
      p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType()), iDmgCounter);
      p_oTree = p_oPop->CreateTree( fX, fY, 1, clTreePopulation::adult, fDiam );
      p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType()), iDmgCounter);
    }
    for ( i = 0; i < 100; i++ )
    {
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::sapling, 4.0 );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::sapling, 5.0 );
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::snag, 20.0 );
    }

    //Grid (1,0): 1000 trees of Species 1 and 2, DBH 8.  Damage counter is 0.
    //100 trees of DBH 4, Species 1, and DBH 5, Species 2, and
    //100 trees of DBH 20, Species 1, Snag
    fX = 9;
    fY = 1;
    fDiam = 8;
    for ( i = 0; i < 1000; i++ )
    {
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, fDiam );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::adult, fDiam );
    }
    for ( i = 0; i < 100; i++ )
    {
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::sapling, 4.0 );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::sapling, 5.0 );
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::snag, 20.0 );
    }

    //Grid (1,1): 1000 trees of Species 1 and 2, DBH 8. Damage counter is 1000.
    //100 trees of DBH 4, Species 1, and DBH 5, Species 2, and
    //100 trees of DBH 20, Species 1, Snag
    iDmgCounter = 1000;
    fX = 9;
    fY = 9;
    fDiam = 8;
    for ( i = 0; i < 1000; i++ )
    {
      p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, fDiam );
      p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType()), iDmgCounter);
      p_oTree = p_oPop->CreateTree( fX, fY, 1, clTreePopulation::adult, fDiam );
      p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType()), iDmgCounter);
    }
    for ( i = 0; i < 100; i++ )
    {
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::sapling, 4.0 );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::sapling, 5.0 );
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::snag, 20.0 );
    }

    //Grid (1,2): 1000 trees of Species 1 and 2, DBH 8.  Damage counter is 2000.
    //100 trees of DBH 4, Species 1, and DBH 5, Species 2, and
    //100 trees of DBH 20, Species 1, Snag
    iDmgCounter = 2000;
    fX = 9;
    fY = 17;
    fDiam = 8;
    for ( i = 0; i < 1000; i++ )
    {
      p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, fDiam );
      p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType()), iDmgCounter);
      p_oTree = p_oPop->CreateTree( fX, fY, 1, clTreePopulation::adult, fDiam );
      p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType()), iDmgCounter);
    }
    for ( i = 0; i < 100; i++ )
    {
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::sapling, 4.0 );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::sapling, 5.0 );
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::snag, 20.0 );
    }

    //For the first timestep, only do storm killing at first so we can check
    //dead snags before they are cleaned away
    p_oSimManager->GetBehaviorObject(2)->Action();
    TestStormKillerRun1Timestep1( p_oPop );
    //Now finish
    for (i = 3; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
      p_oSimManager->GetBehaviorObject(i)->Action();
    }
    for (i = 0; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
      p_oSimManager->GetBehaviorObject(i)->TimestepCleanup();
    }

    p_oSimManager->RunSim( 1 );
    TestStormKillerRun1Timestep4( p_oPop );
    p_oSimManager->RunSim( 1 );
    TestStormKillerRun1Timestep5( p_oPop );
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun3()
// Tests normal processing. WriteStormKillerXMLFile3() writes the parameter file.
// Aspects of the run:
//
// -- Grid resolution of "Storm Damage" is default.
// -- Run is 3 timesteps.
// -- 3 year per timestep.
// -- No snags in the run.
// -- The following trees will be added:
//   -- Grid (0,0): 1000 trees of Species 1 and 2, DBH 30. Damage counter is 0.
//   -- Grid (0,1): 1000 trees of Species 1 and 2, DBH 30. Damage counter is 1000.
//   -- Grid (0,2): 1000 trees of Species 1 and 2, DBH 30. Damage counter is 2000.
//   -- Grid (1,0): 1000 trees of Species 1 and 2, DBH 8. Damage counter is 0.
//   -- Grid (1,1): 1000 trees of Species 1 and 2, DBH 8. Damage counter is 1000.
//   -- Grid (1,2): 1000 trees of Species 1 and 2, DBH 8. Damage counter is 2000.
//   -- All grids get 100 trees of DBH 4, Species 1, and DBH 5, Species 2,
//      which are never damaged or killed.
//   -- All grids get 100 trees of DBH 20, Species 1, Snag, which are never
//      removed.
//
// The run proceeds for 5 timesteps and the number of trees with each damage
// counter is checked through time.
/////////////////////////////////////////////////////////////////////////////
TEST(StormKiller, TestNormalProcessingRun3)
{
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    //Feed our file to the sim manager
    p_oSimManager->ReadFile( WriteStormKillerXMLFile3() );

    //Get the tree population
    clTreePopulation * p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
    clTree * p_oTree;
    float fX, fY, fDiam;
    int i, iDmgCounter;

    //Grid (0,0): 1000 trees of Species 1 and 2, DBH 30.  Damage index is 0.
    //100 trees of DBH 4, Species 1, and DBH 5, Species 2
    fX = 1;
    fY = 1;
    fDiam = 30;
    for ( i = 0; i < 1000; i++ )
    {
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, fDiam );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::adult, fDiam );
    }
    for ( i = 0; i < 100; i++ )
    {
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::sapling, 4.0 );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::sapling, 5.0 );
    }

    //Grid (0,1): 1000 trees of Species 1 and 2, DBH 30.  Damage counter is 1000.
    //100 trees of DBH 4, Species 1, and DBH 5, Species 2
    iDmgCounter = 1000;
    fX = 1;
    fY = 9;
    fDiam = 30;
    for ( i = 0; i < 1000; i++ )
    {
      p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, fDiam );
      p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType()), iDmgCounter);
      p_oTree = p_oPop->CreateTree( fX, fY, 1, clTreePopulation::adult, fDiam );
      p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType()), iDmgCounter);
    }
    for ( i = 0; i < 100; i++ )
    {
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::sapling, 4.0 );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::sapling, 5.0 );
    }

    //Grid (0,2): 1000 trees of Species 1 and 2, DBH 30. Damage counter is 2000.
    //100 trees of DBH 4, Species 1, and DBH 5, Species 2
    iDmgCounter = 2000;
    fX = 1;
    fY = 17;
    fDiam = 30;
    for ( i = 0; i < 1000; i++ )
    {
      p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, fDiam );
      p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType()), iDmgCounter);
      p_oTree = p_oPop->CreateTree( fX, fY, 1, clTreePopulation::adult, fDiam );
      p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType()), iDmgCounter);
    }
    for ( i = 0; i < 100; i++ )
    {
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::sapling, 4.0 );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::sapling, 5.0 );
    }

    //Grid (1,0): 1000 trees of Species 1 and 2, DBH 8.  Damage counter is 0.
    //100 trees of DBH 4, Species 1, and DBH 5, Species 2
    fX = 9;
    fY = 1;
    fDiam = 8;
    for ( i = 0; i < 1000; i++ )
    {
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, fDiam );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::adult, fDiam );
    }
    for ( i = 0; i < 100; i++ )
    {
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::sapling, 4.0 );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::sapling, 5.0 );
    }

    //Grid (1,1): 1000 trees of Species 1 and 2, DBH 8. Damage counter is 1000.
    //100 trees of DBH 4, Species 1, and DBH 5, Species 2
    iDmgCounter = 1000;
    fX = 9;
    fY = 9;
    fDiam = 8;
    for ( i = 0; i < 1000; i++ )
    {
      p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, fDiam );
      p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType()), iDmgCounter);
      p_oTree = p_oPop->CreateTree( fX, fY, 1, clTreePopulation::adult, fDiam );
      p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType()), iDmgCounter);
    }
    for ( i = 0; i < 100; i++ )
    {
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::sapling, 4.0 );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::sapling, 5.0 );
    }

    //Grid (1,2): 1000 trees of Species 1 and 2, DBH 8.  Damage counter is 2000.
    //100 trees of DBH 4, Species 1, and DBH 5, Species 2
    iDmgCounter = 2000;
    fX = 9;
    fY = 17;
    fDiam = 8;
    for ( i = 0; i < 1000; i++ )
    {
      p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, fDiam );
      p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType()), iDmgCounter);
      p_oTree = p_oPop->CreateTree( fX, fY, 1, clTreePopulation::adult, fDiam );
      p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType()), iDmgCounter);
    }
    for ( i = 0; i < 100; i++ )
    {
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::sapling, 4.0 );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::sapling, 5.0 );
    }

    //For the first timestep, only do storm killing at first so damage counters
    //are not unexpectedly incremented
    p_oSimManager->GetBehaviorObject(2)->Action();
    //Now finish
    for (i = 3; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
      p_oSimManager->GetBehaviorObject(i)->Action();
    }
    for (i = 0; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
      p_oSimManager->GetBehaviorObject(i)->TimestepCleanup();
    }
    TestStormKillerRun3Timestep1( p_oPop );

    p_oSimManager->RunSim( 1 );
    TestStormKillerRun3Timestep2( p_oPop );
    p_oSimManager->RunSim( 1 );
    TestStormKillerRun3Timestep3( p_oPop );
    p_oSimManager->RunSim( 1 );
    TestStormKillerRun3Timestep4( p_oPop );
    p_oSimManager->RunSim( 1 );
    TestStormKillerRun3Timestep5( p_oPop );
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestStormKillerRun1Timestep1()
/////////////////////////////////////////////////////////////////////////////
void TestStormKillerRun1Timestep1( clTreePopulation * p_oPop )
{
  using namespace std;
  clTreeSearch * p_oAllTrees;
  clTree * p_oTree;
  stringstream sMessage;
  float fX, fY, fDiam, fExpected;
  int iSp1Group1, iSp2Group1,
  iSp1Group2, iSp2Group2,
  iSp1Group3, iSp2Group3,
  iSp1SnagsGroup1, iSp2SnagsGroup1,
  iSp1SnagsGroup2, iSp2SnagsGroup2,
  iSp1DeadSnags, iSp2DeadSnags,
  iNoStormSnags,
  iSp, iStmDmgValue,
  iIsDead;

  //Get all trees
  p_oAllTrees = p_oPop->Find( "all" );

  //>>>>>>>>>>>>Separate out and only do cell 0,0<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0.  Group 2: storm damage = 1000.  Group 3:
  //storm damage = 2000.
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  iSp1SnagsGroup1 = 0; iSp2SnagsGroup1 = 0;
  iSp1SnagsGroup2 = 0; iSp2SnagsGroup2 = 0;
  iSp1DeadSnags = 0; iSp2DeadSnags = 0; iNoStormSnags = 0;


  int iTest = 0;

  p_oTree = p_oAllTrees->NextTree();
  while ( p_oTree )
  {
    if (p_oTree->GetType() != clTreePopulation::snag)
      iTest++;

    iSp = p_oTree->GetSpecies();

    //Get X and Y
    p_oTree->GetValue( p_oPop->GetXCode( iSp, p_oTree->GetType() ), & fX );
    p_oTree->GetValue( p_oPop->GetYCode( iSp, p_oTree->GetType() ), & fY );

    //Get storm damage counter
    p_oTree->GetValue( p_oPop->GetIntDataCode( "stm_dmg", iSp, p_oTree->GetType() ), & iStmDmgValue );

    if ( fX < 8 && fY < 8 )
    {

      //Get DBH
      p_oTree->GetValue( p_oPop->GetDbhCode( iSp, p_oTree->GetType() ), & fDiam );

      //Test "deadness"
      p_oTree->GetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), &iIsDead);
      if (p_oTree->GetType() == clTreePopulation::snag) {
        if (iIsDead > notdead) {
          if (iSp == 0) iSp1DeadSnags++;
          else iSp2DeadSnags++;
        }
      }
      else {
        if (p_oTree->GetType() == clTreePopulation::adult)
          EXPECT_EQ(notdead, iIsDead);
      }

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if (notdead == iIsDead) {
        if ( fDiam < 6 ) {
          EXPECT_EQ( 0, iStmDmgValue );
        }
        else if ( 0 == iSp && 0 == iStmDmgValue ) {
          if (clTreePopulation::snag == p_oTree->GetType()) iNoStormSnags++;
          else iSp1Group1++;
        }
        else if ( 1 == iSp && 0 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iNoStormSnags++;
          else iSp2Group1++;
        }
        else if ( 0 == iSp && 1000 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp1SnagsGroup1++;
          else iSp1Group2++;
        }
        else if ( 1 == iSp && 1000 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp2SnagsGroup1++;
          else iSp2Group2++;
        }
        else if ( 0 == iSp && 2000 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp1SnagsGroup2++;
          else iSp1Group3++;
        }
        else if ( 1 == iSp && 2000 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp2SnagsGroup2++;
          else iSp2Group3++;
        }
        else
        {
          //Error
          sMessage << "TestNormalProcessingRun1, timestep 1, found an unexpected " << "tree storm damage value.  X: " << fX
              << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
          FAIL() << sMessage.str();
        }
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  //Validate the counts
  EXPECT_EQ( 1000, iSp1Group1 );
  EXPECT_EQ( 1000, iSp2Group1 );
  EXPECT_EQ( 0, iSp1Group2 );
  EXPECT_EQ( 0, iSp2Group2 );
  EXPECT_EQ( 0, iSp1Group3 );
  EXPECT_EQ( 0, iSp2Group3 );
  EXPECT_EQ( 0, iSp1SnagsGroup1 );
  EXPECT_EQ( 0, iSp2SnagsGroup1 );
  EXPECT_EQ( 0, iSp1SnagsGroup2 );
  EXPECT_EQ( 0, iSp2SnagsGroup2 );
  EXPECT_EQ( 0, iSp1DeadSnags );
  EXPECT_EQ( 0, iSp2DeadSnags );
  EXPECT_EQ( 100, iNoStormSnags );


  //>>>>>>>>>>>>Separate out and only do cell 0, 1<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0.  Group 2: storm damage = 1000.  Group 3:
  //storm damage = 2000.
  p_oAllTrees->StartOver();
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  iSp1SnagsGroup1 = 0; iSp2SnagsGroup1 = 0;
  iSp1SnagsGroup2 = 0; iSp2SnagsGroup2 = 0;
  iSp1DeadSnags = 0; iSp2DeadSnags = 0; iNoStormSnags = 0;

  p_oTree = p_oAllTrees->NextTree();
  while ( p_oTree )
  {

    iSp = p_oTree->GetSpecies();

    //Get X and Y
    p_oTree->GetValue( p_oPop->GetXCode( iSp, p_oTree->GetType() ), & fX );
    p_oTree->GetValue( p_oPop->GetYCode( iSp, p_oTree->GetType() ), & fY );

    //Get storm damage counter
    p_oTree->GetValue( p_oPop->GetIntDataCode( "stm_dmg", iSp, p_oTree->GetType() ), & iStmDmgValue );

    if ( fX < 8 && fY > 8 && fY < 16 )
    {
      //Get DBH
      p_oTree->GetValue( p_oPop->GetDbhCode( iSp, p_oTree->GetType() ), & fDiam );

      //Test "deadness"
      p_oTree->GetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), &iIsDead);
      if (p_oTree->GetType() == clTreePopulation::snag) {
        if (iIsDead > notdead) {
          if (iSp == 0) iSp1DeadSnags++;
          else iSp2DeadSnags++;
        }
      }
      else {
        if (p_oTree->GetType() == clTreePopulation::adult)
          EXPECT_EQ(notdead, iIsDead);
      }

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if (notdead == iIsDead) {
        if ( fDiam < 6 ) {
          EXPECT_EQ( 0, iStmDmgValue );
        }
        else if ( 0 == iSp && 0 == iStmDmgValue ) {
          if (clTreePopulation::snag == p_oTree->GetType()) iNoStormSnags++;
          else iSp1Group1++;
        }
        else if ( 1 == iSp && 0 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iNoStormSnags++;
          else iSp2Group1++;
        }
        else if ( 0 == iSp && 1000 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp1SnagsGroup1++;
          else iSp1Group2++;
        }
        else if ( 1 == iSp && 1000 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp2SnagsGroup1++;
          else iSp2Group2++;
        }
        else if ( 0 == iSp && 2000 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp1SnagsGroup2++;
          else iSp1Group3++;
        }
        else if ( 1 == iSp && 2000 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp2SnagsGroup2++;
          else iSp2Group3++;
        }
        else
        {
          //Error
          sMessage << "TestNormalProcessingRun1, timestep 1, found an unexpected " << "tree storm damage value.  X: " << fX
              << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
          FAIL() << sMessage.str();
        }
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  //Validate the counts
  EXPECT_EQ( 0, iSp1Group1);
  EXPECT_EQ( 0, iSp2Group1);
  fExpected = 574.4;
  EXPECT_LT( fabs( fExpected - iSp1Group2 ) / fExpected, 0.1 );
  fExpected = 850.6;
  EXPECT_LT( fabs( fExpected - iSp2Group2 ) / fExpected, 0.1 );
  EXPECT_EQ( 0, iSp1Group3);
  EXPECT_EQ( 0, iSp2Group3);
  fExpected = 425.5;
  EXPECT_LT( fabs( fExpected - iSp1SnagsGroup1 ) / fExpected, 0.1 );
  fExpected = 149.3;
  EXPECT_LT( fabs( fExpected - iSp2SnagsGroup1 ) / fExpected, 0.10 );
  EXPECT_EQ( 0, iSp1SnagsGroup2);
  EXPECT_EQ( 0, iSp2SnagsGroup2);
  EXPECT_EQ( 0, iSp1DeadSnags);
  EXPECT_EQ( 0, iSp2DeadSnags);
  EXPECT_EQ( 100, iNoStormSnags );




  //>>>>>>>>>>>>Separate out and only do cell 0, 2<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0.  Group 2: storm damage = 1000.  Group 3:
  //storm damage = 2000.
  p_oAllTrees->StartOver();
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  iSp1SnagsGroup1 = 0; iSp2SnagsGroup1 = 0;
  iSp1SnagsGroup2 = 0; iSp2SnagsGroup2 = 0;
  iSp1DeadSnags = 0; iSp2DeadSnags = 0; iNoStormSnags = 0;

  p_oTree = p_oAllTrees->NextTree();
  while ( p_oTree )
  {

    iSp = p_oTree->GetSpecies();

    //Get X and Y
    p_oTree->GetValue( p_oPop->GetXCode( iSp, p_oTree->GetType() ), & fX );
    p_oTree->GetValue( p_oPop->GetYCode( iSp, p_oTree->GetType() ), & fY );

    //Get storm damage counter
    p_oTree->GetValue( p_oPop->GetIntDataCode( "stm_dmg", iSp, p_oTree->GetType() ), & iStmDmgValue );

    if ( fX < 8 && fY > 16 && fY < 24 )
    {
      //Get DBH
      p_oTree->GetValue( p_oPop->GetDbhCode( iSp, p_oTree->GetType() ), & fDiam );

      //Test "deadness"
      p_oTree->GetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), &iIsDead);
      if (p_oTree->GetType() == clTreePopulation::snag) {
        if (iIsDead > notdead) {
          if (iSp == 0) iSp1DeadSnags++;
          else iSp2DeadSnags++;
        }
      }
      else {
        if (p_oTree->GetType() == clTreePopulation::adult)
          EXPECT_EQ(notdead, iIsDead);
      }

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if (notdead == iIsDead) {
        if ( fDiam < 6 ) {
          EXPECT_EQ( 0, iStmDmgValue );
        }
        else if ( 0 == iSp && 0 == iStmDmgValue ) {
          if (clTreePopulation::snag == p_oTree->GetType()) iNoStormSnags++;
          else iSp1Group1++;
        }
        else if ( 1 == iSp && 0 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iNoStormSnags++;
          else iSp2Group1++;
        }
        else if ( 0 == iSp && 1000 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp1SnagsGroup1++;
          else iSp1Group2++;
        }
        else if ( 1 == iSp && 1000 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp2SnagsGroup1++;
          else iSp2Group2++;
        }
        else if ( 0 == iSp && 2000 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp1SnagsGroup2++;
          else iSp1Group3++;
        }
        else if ( 1 == iSp && 2000 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp2SnagsGroup2++;
          else iSp2Group3++;
        }
        else
        {
          //Error
          sMessage << "TestNormalProcessingRun1, timestep 1, found an unexpected " << "tree storm damage value.  X: " << fX
              << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
          FAIL() << sMessage.str();
        }
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  //Validate the counts
  EXPECT_EQ( 0, iSp1Group1 );
  EXPECT_EQ( 0, iSp2Group1 );
  EXPECT_EQ( 0, iSp1Group2 );
  EXPECT_EQ( 0, iSp2Group2 );
  fExpected = 809.9;
  EXPECT_LT( fabs( fExpected - iSp1Group3 ) / fExpected, 0.1 );
  fExpected = 472.5;
  EXPECT_LT( fabs( fExpected - iSp2Group3 ) / fExpected, 0.1 );
  EXPECT_EQ( 0, iSp1SnagsGroup1 );
  EXPECT_EQ( 0, iSp2SnagsGroup1 );
  fExpected = 133.0;
  EXPECT_LT( fabs( fExpected - iSp1SnagsGroup2 ) / fExpected, 0.2 );
  fExpected = 105.4;
  EXPECT_LT( fabs( fExpected - iSp2SnagsGroup2 ) / fExpected, 0.2 );
  fExpected = 57.0;
  EXPECT_LT( fabs( fExpected - iSp1DeadSnags ) / fExpected, 0.25 );
  fExpected = 421.9;
  EXPECT_LT( fabs( fExpected - iSp2DeadSnags ) / fExpected, 0.1 );
  EXPECT_EQ( 100, iNoStormSnags );





  //>>>>>>>>>>>>Separate out and only do cell 1, 0<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0.  Group 2: storm damage = 1000.  Group 3:
  //storm damage = 2000.
  p_oAllTrees->StartOver();
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  iSp1SnagsGroup1 = 0; iSp2SnagsGroup1 = 0;
  iSp1SnagsGroup2 = 0; iSp2SnagsGroup2 = 0;
  iSp1DeadSnags = 0; iSp2DeadSnags = 0; iNoStormSnags = 0;

  p_oTree = p_oAllTrees->NextTree();
  while ( p_oTree )
  {

    iSp = p_oTree->GetSpecies();

    //Get X and Y
    p_oTree->GetValue( p_oPop->GetXCode( iSp, p_oTree->GetType() ), & fX );
    p_oTree->GetValue( p_oPop->GetYCode( iSp, p_oTree->GetType() ), & fY );

    //Get storm damage counter
    p_oTree->GetValue( p_oPop->GetIntDataCode( "stm_dmg", iSp, p_oTree->GetType() ), & iStmDmgValue );

    if ( fX > 8 && fX < 16 && fY < 8 )
    {
      //Get DBH
      p_oTree->GetValue( p_oPop->GetDbhCode( iSp, p_oTree->GetType() ), & fDiam );

      //Test "deadness"
      p_oTree->GetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), &iIsDead);
      if (p_oTree->GetType() == clTreePopulation::snag) {
        if (iIsDead > notdead) {
          if (iSp == 0) iSp1DeadSnags++;
          else iSp2DeadSnags++;
        }
      }
      else {
        if (p_oTree->GetType() == clTreePopulation::adult)
          EXPECT_EQ(notdead, iIsDead);
      }

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if (notdead == iIsDead) {
        if ( fDiam < 6 ) {
          EXPECT_EQ( 0, iStmDmgValue );
        }
        else if ( 0 == iSp && 0 == iStmDmgValue ) {
          if (clTreePopulation::snag == p_oTree->GetType()) iNoStormSnags++;
          else iSp1Group1++;
        }
        else if ( 1 == iSp && 0 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iNoStormSnags++;
          else iSp2Group1++;
        }
        else if ( 0 == iSp && 1000 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp1SnagsGroup1++;
          else iSp1Group2++;
        }
        else if ( 1 == iSp && 1000 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp2SnagsGroup1++;
          else iSp2Group2++;
        }
        else if ( 0 == iSp && 2000 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp1SnagsGroup2++;
          else iSp1Group3++;
        }
        else if ( 1 == iSp && 2000 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp2SnagsGroup2++;
          else iSp2Group3++;
        }
        else
        {
          //Error
          sMessage << "TestNormalProcessingRun1, timestep 1, found an unexpected " << "tree storm damage value.  X: " << fX
              << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
          FAIL() << sMessage.str();
        }
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  //Validate the counts
  EXPECT_EQ( 1000, iSp1Group1 );
  EXPECT_EQ( 1000, iSp2Group1 );
  EXPECT_EQ( 0, iSp1Group2 );
  EXPECT_EQ( 0, iSp2Group2 );
  EXPECT_EQ( 0, iSp1Group3 );
  EXPECT_EQ( 0, iSp2Group3 );
  EXPECT_EQ( 0, iSp1SnagsGroup1 );
  EXPECT_EQ( 0, iSp2SnagsGroup1 );
  EXPECT_EQ( 0, iSp1SnagsGroup2 );
  EXPECT_EQ( 0, iSp2SnagsGroup2 );
  EXPECT_EQ( 0, iSp1DeadSnags );
  EXPECT_EQ( 0, iSp2DeadSnags );
  EXPECT_EQ( 100, iNoStormSnags );




  //>>>>>>>>>>>>Separate out and only do cell 1, 1<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0.  Group 2: storm damage = 1000.  Group 3:
  //storm damage = 2000.
  p_oAllTrees->StartOver();
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  iSp1SnagsGroup1 = 0; iSp2SnagsGroup1 = 0;
  iSp1SnagsGroup2 = 0; iSp2SnagsGroup2 = 0;
  iSp1DeadSnags = 0; iSp2DeadSnags = 0; iNoStormSnags = 0;

  p_oTree = p_oAllTrees->NextTree();
  while ( p_oTree )
  {

    iSp = p_oTree->GetSpecies();

    //Get X and Y
    p_oTree->GetValue( p_oPop->GetXCode( iSp, p_oTree->GetType() ), & fX );
    p_oTree->GetValue( p_oPop->GetYCode( iSp, p_oTree->GetType() ), & fY );

    //Get storm damage counter
    p_oTree->GetValue( p_oPop->GetIntDataCode( "stm_dmg", iSp, p_oTree->GetType() ), & iStmDmgValue );

    if ( fX > 8 && fX < 16 && fY > 8 && fY < 16 )
    {
      //Get DBH
      p_oTree->GetValue( p_oPop->GetDbhCode( iSp, p_oTree->GetType() ), & fDiam );

      //Test "deadness"
      p_oTree->GetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), &iIsDead);
      if (p_oTree->GetType() == clTreePopulation::snag) {
        if (iIsDead > notdead) {
          if (iSp == 0) iSp1DeadSnags++;
          else iSp2DeadSnags++;
        }
      }
      else {
        if (p_oTree->GetType() == clTreePopulation::adult)
          EXPECT_EQ(notdead, iIsDead);
      }

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if (notdead == iIsDead) {
        if ( fDiam < 6 ) {
          EXPECT_EQ( 0, iStmDmgValue );
        }
        else if ( 0 == iSp && 0 == iStmDmgValue ) {
          if (clTreePopulation::snag == p_oTree->GetType()) iNoStormSnags++;
          else iSp1Group1++;
        }
        else if ( 1 == iSp && 0 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iNoStormSnags++;
          else iSp2Group1++;
        }
        else if ( 0 == iSp && 1000 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp1SnagsGroup1++;
          else iSp1Group2++;
        }
        else if ( 1 == iSp && 1000 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp2SnagsGroup1++;
          else iSp2Group2++;
        }
        else if ( 0 == iSp && 2000 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp1SnagsGroup2++;
          else iSp1Group3++;
        }
        else if ( 1 == iSp && 2000 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp2SnagsGroup2++;
          else iSp2Group3++;
        }
        else
        {
          //Error
          sMessage << "TestNormalProcessingRun1, timestep 1, found an unexpected " << "tree storm damage value.  X: " << fX
              << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
          FAIL() << sMessage.str();
        }
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  //Validate the counts
  EXPECT_EQ( 0, iSp1Group1);
  EXPECT_EQ( 0, iSp2Group1);
  fExpected = 627.1;
  EXPECT_LT( fabs( fExpected - iSp1Group2 ) / fExpected, 0.1 );
  fExpected = 898.4;
  EXPECT_LT( fabs( fExpected - iSp2Group2 ) / fExpected, 0.1 );
  EXPECT_EQ( 0, iSp1Group3);
  EXPECT_EQ( 0, iSp2Group3);
  EXPECT_EQ( 0, iSp1SnagsGroup1);
  EXPECT_EQ( 0, iSp1SnagsGroup2);
  EXPECT_EQ( 0, iSp2SnagsGroup1);
  EXPECT_EQ( 0, iSp2SnagsGroup2);
  EXPECT_EQ( 0, iSp1DeadSnags);
  EXPECT_EQ( 0, iSp2DeadSnags);
  EXPECT_EQ( 100, iNoStormSnags );






  //>>>>>>>>>>>>Separate out and only do cell 1, 2<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0.  Group 2: storm damage = 1000.  Group 3:
  //storm damage = 2000.
  p_oAllTrees->StartOver();
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  iSp1SnagsGroup1 = 0; iSp2SnagsGroup1 = 0;
  iSp1SnagsGroup2 = 0; iSp2SnagsGroup2 = 0;
  iSp1DeadSnags = 0; iSp2DeadSnags = 0; iNoStormSnags = 0;

  p_oTree = p_oAllTrees->NextTree();
  while ( p_oTree )
  {

    iSp = p_oTree->GetSpecies();

    //Get X and Y
    p_oTree->GetValue( p_oPop->GetXCode( iSp, p_oTree->GetType() ), & fX );
    p_oTree->GetValue( p_oPop->GetYCode( iSp, p_oTree->GetType() ), & fY );

    //Get storm damage counter
    p_oTree->GetValue( p_oPop->GetIntDataCode( "stm_dmg", iSp, p_oTree->GetType() ), & iStmDmgValue );

    if ( fX > 8 && fX < 16 && fY > 16 && fY < 24 )
    {
      //Get DBH
      p_oTree->GetValue( p_oPop->GetDbhCode( iSp, p_oTree->GetType() ), & fDiam );

      //Test "deadness"
      p_oTree->GetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), &iIsDead);
      if (p_oTree->GetType() == clTreePopulation::snag) {
        if (iIsDead > notdead) {
          if (iSp == 0) iSp1DeadSnags++;
          else iSp2DeadSnags++;
        }
      }
      else {
        if (p_oTree->GetType() == clTreePopulation::adult)
          EXPECT_EQ(notdead, iIsDead);
      }

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if (notdead == iIsDead) {
        if ( fDiam < 6 ) {
          EXPECT_EQ( 0, iStmDmgValue );
        }
        else if ( 0 == iSp && 0 == iStmDmgValue ) {
          if (clTreePopulation::snag == p_oTree->GetType()) iNoStormSnags++;
          else iSp1Group1++;
        }
        else if ( 1 == iSp && 0 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iNoStormSnags++;
          else iSp2Group1++;
        }
        else if ( 0 == iSp && 1000 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp1SnagsGroup1++;
          else iSp1Group2++;
        }
        else if ( 1 == iSp && 1000 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp2SnagsGroup1++;
          else iSp2Group2++;
        }
        else if ( 0 == iSp && 2000 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp1SnagsGroup2++;
          else iSp1Group3++;
        }
        else if ( 1 == iSp && 2000 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp2SnagsGroup2++;
          else iSp2Group3++;
        }
        else
        {
          //Error
          sMessage << "TestNormalProcessingRun1, timestep 1, found an unexpected " << "tree storm damage value.  X: " << fX
              << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
          FAIL() << sMessage.str();
        }
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  //Validate the counts
  EXPECT_EQ( 0, iSp1Group1 );
  EXPECT_EQ( 0, iSp2Group1 );
  EXPECT_EQ( 0, iSp1Group2 );
  EXPECT_EQ( 0, iSp2Group2 );
  fExpected = 960.3;
  EXPECT_LT( fabs( fExpected - iSp1Group3 ) / fExpected, 0.1 );
  fExpected = 729.0;
  EXPECT_LT( fabs( fExpected - iSp2Group3 ) / fExpected, 0.1 );
  EXPECT_EQ( 0, iSp1SnagsGroup1 );
  EXPECT_EQ( 0, iSp2SnagsGroup1 );
  EXPECT_EQ( 0, iSp1SnagsGroup2 );
  EXPECT_EQ( 0, iSp2SnagsGroup2 );
  EXPECT_EQ( 0, iSp1DeadSnags );
  EXPECT_EQ( 0, iSp2DeadSnags );
  EXPECT_EQ( 100, iNoStormSnags );
}

/////////////////////////////////////////////////////////////////////////////
// TestStormKillerRun1Timestep2()
/////////////////////////////////////////////////////////////////////////////
void TestStormKillerRun1Timestep2( clTreePopulation * p_oPop )
{
  using namespace std;
  clTreeSearch * p_oAllTrees;
  clTree * p_oTree;
  stringstream sMessage;
  float fX, fY, fDiam, fExpected;
  int iSp1Group1, iSp2Group1,
  iSp1Group2, iSp2Group2,
  iSp1Group3, iSp2Group3,
  iSp1SnagsGroup1, iSp2SnagsGroup1,
  iSp1SnagsGroup2, iSp2SnagsGroup2,
  iNoStormSnags,
  iSp, iStmDmgValue,
  iIsDead;

  //Get all trees
  p_oAllTrees = p_oPop->Find( "all" );

  //>>>>>>>>>>>>Separate out and only do cell 0,0<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0.  Group 2: storm damage = 1001.  Group 3:
  //storm damage = 2001.
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  iSp1SnagsGroup1 = 0; iSp2SnagsGroup1 = 0;
  iSp1SnagsGroup2 = 0; iSp2SnagsGroup2 = 0;
  iNoStormSnags = 0;

  p_oTree = p_oAllTrees->NextTree();
  while ( p_oTree )
  {

    iSp = p_oTree->GetSpecies();

    //Get X and Y
    p_oTree->GetValue( p_oPop->GetXCode( iSp, p_oTree->GetType() ), & fX );
    p_oTree->GetValue( p_oPop->GetYCode( iSp, p_oTree->GetType() ), & fY );

    //Get storm damage counter
    p_oTree->GetValue( p_oPop->GetIntDataCode( "stm_dmg", iSp, p_oTree->GetType() ), & iStmDmgValue );

    if ( fX < 8 && fY < 8 )
    {

      //Get DBH
      p_oTree->GetValue( p_oPop->GetDbhCode( iSp, p_oTree->GetType() ), & fDiam );

      //Test "deadness"
      p_oTree->GetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), &iIsDead);
      EXPECT_EQ(notdead, iIsDead);

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if (notdead == iIsDead) {
        if ( fDiam < 6 ) {
          EXPECT_EQ( 0, iStmDmgValue );
        }
        else if ( 0 == iSp && 0 == iStmDmgValue ) {
          if (clTreePopulation::snag == p_oTree->GetType()) iNoStormSnags++;
          else iSp1Group1++;
        }
        else if ( 1 == iSp && 0 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iNoStormSnags++;
          else iSp2Group1++;
        }
        else if ( 0 == iSp && 1001 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp1SnagsGroup1++;
          else iSp1Group2++;
        }
        else if ( 1 == iSp && 1001 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp2SnagsGroup1++;
          else iSp2Group2++;
        }
        else if ( 0 == iSp && 2001 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp1SnagsGroup2++;
          else iSp1Group3++;
        }
        else if ( 1 == iSp && 2001 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp2SnagsGroup2++;
          else iSp2Group3++;
        }
        else
        {
          //Error
          sMessage << "TestNormalProcessingRun1, timestep 2, found an unexpected " << "tree storm damage value.  X: " << fX
              << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
          FAIL() << sMessage.str();
        }
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  //Validate the counts
  EXPECT_EQ( 1000, iSp1Group1 );
  EXPECT_EQ( 1000, iSp2Group1 );
  EXPECT_EQ( 0, iSp1Group2 );
  EXPECT_EQ( 0, iSp2Group2 );
  EXPECT_EQ( 0, iSp1Group3 );
  EXPECT_EQ( 0, iSp2Group3 );
  EXPECT_EQ( 0, iSp1SnagsGroup1 );
  EXPECT_EQ( 0, iSp2SnagsGroup1 );
  EXPECT_EQ( 0, iSp1SnagsGroup2 );
  EXPECT_EQ( 0, iSp2SnagsGroup2 );
  EXPECT_EQ( 100, iNoStormSnags );


  //>>>>>>>>>>>>Separate out and only do cell 0, 1<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0.  Group 2: storm damage = 1001.  Group 3:
  //storm damage = 2001.
  p_oAllTrees->StartOver();
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  iSp1SnagsGroup1 = 0; iSp2SnagsGroup1 = 0;
  iSp1SnagsGroup2 = 0; iSp2SnagsGroup2 = 0;
  iNoStormSnags = 0;

  p_oTree = p_oAllTrees->NextTree();
  while ( p_oTree )
  {

    iSp = p_oTree->GetSpecies();

    //Get X and Y
    p_oTree->GetValue( p_oPop->GetXCode( iSp, p_oTree->GetType() ), & fX );
    p_oTree->GetValue( p_oPop->GetYCode( iSp, p_oTree->GetType() ), & fY );

    //Get storm damage counter
    p_oTree->GetValue( p_oPop->GetIntDataCode( "stm_dmg", iSp, p_oTree->GetType() ), & iStmDmgValue );

    if ( fX < 8 && fY > 8 && fY < 16 )
    {
      //Get DBH
      p_oTree->GetValue( p_oPop->GetDbhCode( iSp, p_oTree->GetType() ), & fDiam );

      //Test "deadness"
      p_oTree->GetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), &iIsDead);
      EXPECT_EQ(notdead, iIsDead);

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if (notdead == iIsDead) {
        if ( fDiam < 6 ) {
          EXPECT_EQ( 0, iStmDmgValue );
        }
        else if ( 0 == iSp && 0 == iStmDmgValue ) {
          if (clTreePopulation::snag == p_oTree->GetType()) iNoStormSnags++;
          else iSp1Group1++;
        }
        else if ( 1 == iSp && 0 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iNoStormSnags++;
          else iSp2Group1++;
        }
        else if ( 0 == iSp && 1001 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp1SnagsGroup1++;
          else iSp1Group2++;
        }
        else if ( 1 == iSp && 1001 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp2SnagsGroup1++;
          else iSp2Group2++;
        }
        else if ( 0 == iSp && 2001 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp1SnagsGroup2++;
          else iSp1Group3++;
        }
        else if ( 1 == iSp && 2001 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp2SnagsGroup2++;
          else iSp2Group3++;
        }
        else
        {
          //Error
          sMessage << "TestNormalProcessingRun1, timestep 2, found an unexpected " << "tree storm damage value.  X: " << fX
              << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
          FAIL() << sMessage.str();
        }
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  //Validate the counts
  EXPECT_EQ( 0, iSp1Group1);
  EXPECT_EQ( 0, iSp2Group1);
  fExpected = 574.4;
  EXPECT_LT( fabs( fExpected - iSp1Group2 ) / fExpected, 0.1 );
  fExpected = 850.6;
  EXPECT_LT( fabs( fExpected - iSp2Group2 ) / fExpected, 0.1 );
  EXPECT_EQ( 0, iSp1Group3);
  EXPECT_EQ( 0, iSp2Group3);
  fExpected = 425.5;
  EXPECT_LT( fabs( fExpected - iSp1SnagsGroup1 ) / fExpected, 0.1 );
  fExpected = 149.3;
  EXPECT_LT( fabs( fExpected - iSp2SnagsGroup1 ) / fExpected, 0.10 );
  EXPECT_EQ( 0, iSp1SnagsGroup2);
  EXPECT_EQ( 0, iSp2SnagsGroup2);
  EXPECT_EQ( 100, iNoStormSnags );




  //>>>>>>>>>>>>Separate out and only do cell 0, 2<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0.  Group 2: storm damage = 1001.  Group 3:
  //storm damage = 2001.
  p_oAllTrees->StartOver();
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  iSp1SnagsGroup1 = 0; iSp2SnagsGroup1 = 0;
  iSp1SnagsGroup2 = 0; iSp2SnagsGroup2 = 0;
  iNoStormSnags = 0;

  p_oTree = p_oAllTrees->NextTree();
  while ( p_oTree )
  {

    iSp = p_oTree->GetSpecies();

    //Get X and Y
    p_oTree->GetValue( p_oPop->GetXCode( iSp, p_oTree->GetType() ), & fX );
    p_oTree->GetValue( p_oPop->GetYCode( iSp, p_oTree->GetType() ), & fY );

    //Get storm damage counter
    p_oTree->GetValue( p_oPop->GetIntDataCode( "stm_dmg", iSp, p_oTree->GetType() ), & iStmDmgValue );

    if ( fX < 8 && fY > 16 && fY < 24 )
    {
      //Get DBH
      p_oTree->GetValue( p_oPop->GetDbhCode( iSp, p_oTree->GetType() ), & fDiam );

      //Test "deadness"
      p_oTree->GetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), &iIsDead);
      EXPECT_EQ(notdead, iIsDead);

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if (notdead == iIsDead) {
        if ( fDiam < 6 ) {
          EXPECT_EQ( 0, iStmDmgValue );
        }
        else if ( 0 == iSp && 0 == iStmDmgValue ) {
          if (clTreePopulation::snag == p_oTree->GetType()) iNoStormSnags++;
          else iSp1Group1++;
        }
        else if ( 1 == iSp && 0 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iNoStormSnags++;
          else iSp2Group1++;
        }
        else if ( 0 == iSp && 1001 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp1SnagsGroup1++;
          else iSp1Group2++;
        }
        else if ( 1 == iSp && 1001 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp2SnagsGroup1++;
          else iSp2Group2++;
        }
        else if ( 0 == iSp && 2001 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp1SnagsGroup2++;
          else iSp1Group3++;
        }
        else if ( 1 == iSp && 2001 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp2SnagsGroup2++;
          else iSp2Group3++;
        }
        else
        {
          //Error
          sMessage << "TestNormalProcessingRun1, timestep 2, found an unexpected " << "tree storm damage value.  X: " << fX
              << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
          FAIL() << sMessage.str();
        }
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  //Validate the counts
  EXPECT_EQ( 0, iSp1Group1 );
  EXPECT_EQ( 0, iSp2Group1 );
  EXPECT_EQ( 0, iSp1Group2 );
  EXPECT_EQ( 0, iSp2Group2 );
  fExpected = 809.9;
  EXPECT_LT( fabs( fExpected - iSp1Group3 ) / fExpected, 0.1 );
  fExpected = 472.5;
  EXPECT_LT( fabs( fExpected - iSp2Group3 ) / fExpected, 0.1 );
  EXPECT_EQ( 0, iSp1SnagsGroup1 );
  EXPECT_EQ( 0, iSp2SnagsGroup1 );
  fExpected = 133.0;
  EXPECT_LT( fabs( fExpected - iSp1SnagsGroup2 ) / fExpected, 0.2 );
  fExpected = 105.4;
  EXPECT_LT( fabs( fExpected - iSp2SnagsGroup2 ) / fExpected, 0.2 );
  EXPECT_EQ( 100, iNoStormSnags );





  //>>>>>>>>>>>>Separate out and only do cell 1, 0<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0.  Group 2: storm damage = 1001.  Group 3:
  //storm damage = 2001.
  p_oAllTrees->StartOver();
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  iSp1SnagsGroup1 = 0; iSp2SnagsGroup1 = 0;
  iSp1SnagsGroup2 = 0; iSp2SnagsGroup2 = 0;
  iNoStormSnags = 0;

  p_oTree = p_oAllTrees->NextTree();
  while ( p_oTree )
  {

    iSp = p_oTree->GetSpecies();

    //Get X and Y
    p_oTree->GetValue( p_oPop->GetXCode( iSp, p_oTree->GetType() ), & fX );
    p_oTree->GetValue( p_oPop->GetYCode( iSp, p_oTree->GetType() ), & fY );

    //Get storm damage counter
    p_oTree->GetValue( p_oPop->GetIntDataCode( "stm_dmg", iSp, p_oTree->GetType() ), & iStmDmgValue );

    if ( fX > 8 && fX < 16 && fY < 8 )
    {
      //Get DBH
      p_oTree->GetValue( p_oPop->GetDbhCode( iSp, p_oTree->GetType() ), & fDiam );

      //Test "deadness"
      p_oTree->GetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), &iIsDead);
      EXPECT_EQ(notdead, iIsDead);

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if (notdead == iIsDead) {
        if ( fDiam < 6 ) {
          EXPECT_EQ( 0, iStmDmgValue );
        }
        else if ( 0 == iSp && 0 == iStmDmgValue ) {
          if (clTreePopulation::snag == p_oTree->GetType()) iNoStormSnags++;
          else iSp1Group1++;
        }
        else if ( 1 == iSp && 0 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iNoStormSnags++;
          else iSp2Group1++;
        }
        else if ( 0 == iSp && 1001 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp1SnagsGroup1++;
          else iSp1Group2++;
        }
        else if ( 1 == iSp && 1001 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp2SnagsGroup1++;
          else iSp2Group2++;
        }
        else if ( 0 == iSp && 2001 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp1SnagsGroup2++;
          else iSp1Group3++;
        }
        else if ( 1 == iSp && 2001 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp2SnagsGroup2++;
          else iSp2Group3++;
        }
        else
        {
          //Error
          sMessage << "TestNormalProcessingRun1, timestep 2, found an unexpected " << "tree storm damage value.  X: " << fX
              << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
          FAIL() << sMessage.str();
        }
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  //Validate the counts
  EXPECT_EQ( 1000, iSp1Group1 );
  EXPECT_EQ( 1000, iSp2Group1 );
  EXPECT_EQ( 0, iSp1Group2 );
  EXPECT_EQ( 0, iSp2Group2 );
  EXPECT_EQ( 0, iSp1Group3 );
  EXPECT_EQ( 0, iSp2Group3 );
  EXPECT_EQ( 0, iSp1SnagsGroup1 );
  EXPECT_EQ( 0, iSp2SnagsGroup1 );
  EXPECT_EQ( 0, iSp1SnagsGroup2 );
  EXPECT_EQ( 0, iSp2SnagsGroup2 );
  EXPECT_EQ( 100, iNoStormSnags );




  //>>>>>>>>>>>>Separate out and only do cell 1, 1<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0.  Group 2: storm damage = 1001.  Group 3:
  //storm damage = 2001.
  p_oAllTrees->StartOver();
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  iSp1SnagsGroup1 = 0; iSp2SnagsGroup1 = 0;
  iSp1SnagsGroup2 = 0; iSp2SnagsGroup2 = 0;
  iNoStormSnags = 0;

  p_oTree = p_oAllTrees->NextTree();
  while ( p_oTree )
  {

    iSp = p_oTree->GetSpecies();

    //Get X and Y
    p_oTree->GetValue( p_oPop->GetXCode( iSp, p_oTree->GetType() ), & fX );
    p_oTree->GetValue( p_oPop->GetYCode( iSp, p_oTree->GetType() ), & fY );

    //Get storm damage counter
    p_oTree->GetValue( p_oPop->GetIntDataCode( "stm_dmg", iSp, p_oTree->GetType() ), & iStmDmgValue );

    if ( fX > 8 && fX < 16 && fY > 8 && fY < 16 )
    {
      //Get DBH
      p_oTree->GetValue( p_oPop->GetDbhCode( iSp, p_oTree->GetType() ), & fDiam );

      //Test "deadness"
      p_oTree->GetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), &iIsDead);
      EXPECT_EQ(notdead, iIsDead);

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if (notdead == iIsDead) {
        if ( fDiam < 6 ) {
          EXPECT_EQ( 0, iStmDmgValue );
        }
        else if ( 0 == iSp && 0 == iStmDmgValue ) {
          if (clTreePopulation::snag == p_oTree->GetType()) iNoStormSnags++;
          else iSp1Group1++;
        }
        else if ( 1 == iSp && 0 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iNoStormSnags++;
          else iSp2Group1++;
        }
        else if ( 0 == iSp && 1001 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp1SnagsGroup1++;
          else iSp1Group2++;
        }
        else if ( 1 == iSp && 1001 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp2SnagsGroup1++;
          else iSp2Group2++;
        }
        else if ( 0 == iSp && 2001 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp1SnagsGroup2++;
          else iSp1Group3++;
        }
        else if ( 1 == iSp && 2001 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp2SnagsGroup2++;
          else iSp2Group3++;
        }
        else
        {
          //Error
          sMessage << "TestNormalProcessingRun1, timestep 2, found an unexpected " << "tree storm damage value.  X: " << fX
              << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
          FAIL() << sMessage.str();
        }
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  //Validate the counts
  EXPECT_EQ( 0, iSp1Group1);
  EXPECT_EQ( 0, iSp2Group1);
  fExpected = 627.1;
  EXPECT_LT( fabs( fExpected - iSp1Group2 ) / fExpected, 0.1 );
  fExpected = 898.4;
  EXPECT_LT( fabs( fExpected - iSp2Group2 ) / fExpected, 0.1 );
  EXPECT_EQ( 0, iSp1Group3);
  EXPECT_EQ( 0, iSp2Group3);
  EXPECT_EQ( 0, iSp1SnagsGroup1);
  EXPECT_EQ( 0, iSp1SnagsGroup2);
  EXPECT_EQ( 0, iSp2SnagsGroup1);
  EXPECT_EQ( 0, iSp2SnagsGroup2);
  EXPECT_EQ( 100, iNoStormSnags );






  //>>>>>>>>>>>>Separate out and only do cell 1, 2<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0.  Group 2: storm damage = 1001.  Group 3:
  //storm damage = 2001.
  p_oAllTrees->StartOver();
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  iSp1SnagsGroup1 = 0; iSp2SnagsGroup1 = 0;
  iSp1SnagsGroup2 = 0; iSp2SnagsGroup2 = 0;
  iNoStormSnags = 0;

  p_oTree = p_oAllTrees->NextTree();
  while ( p_oTree )
  {

    iSp = p_oTree->GetSpecies();

    //Get X and Y
    p_oTree->GetValue( p_oPop->GetXCode( iSp, p_oTree->GetType() ), & fX );
    p_oTree->GetValue( p_oPop->GetYCode( iSp, p_oTree->GetType() ), & fY );

    //Get storm damage counter
    p_oTree->GetValue( p_oPop->GetIntDataCode( "stm_dmg", iSp, p_oTree->GetType() ), & iStmDmgValue );

    if ( fX > 8 && fX < 16 && fY > 16 && fY < 24 )
    {
      //Get DBH
      p_oTree->GetValue( p_oPop->GetDbhCode( iSp, p_oTree->GetType() ), & fDiam );

      //Test "deadness"
      p_oTree->GetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), &iIsDead);
      EXPECT_EQ(notdead, iIsDead);

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if (notdead == iIsDead) {
        if ( fDiam < 6 ) {
          EXPECT_EQ( 0, iStmDmgValue );
        }
        else if ( 0 == iSp && 0 == iStmDmgValue ) {
          if (clTreePopulation::snag == p_oTree->GetType()) iNoStormSnags++;
          else iSp1Group1++;
        }
        else if ( 1 == iSp && 0 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iNoStormSnags++;
          else iSp2Group1++;
        }
        else if ( 0 == iSp && 1001 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp1SnagsGroup1++;
          else iSp1Group2++;
        }
        else if ( 1 == iSp && 1001 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp2SnagsGroup1++;
          else iSp2Group2++;
        }
        else if ( 0 == iSp && 2001 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp1SnagsGroup2++;
          else iSp1Group3++;
        }
        else if ( 1 == iSp && 2001 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp2SnagsGroup2++;
          else iSp2Group3++;
        }
        else
        {
          //Error
          sMessage << "TestNormalProcessingRun1, timestep 2, found an unexpected " << "tree storm damage value.  X: " << fX
              << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
          FAIL() << sMessage.str();
        }
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  //Validate the counts
  EXPECT_EQ( 0, iSp1Group1 );
  EXPECT_EQ( 0, iSp2Group1 );
  EXPECT_EQ( 0, iSp1Group2 );
  EXPECT_EQ( 0, iSp2Group2 );
  fExpected = 960.3;
  EXPECT_LT( fabs( fExpected - iSp1Group3 ) / fExpected, 0.1 );
  fExpected = 729.0;
  EXPECT_LT( fabs( fExpected - iSp2Group3 ) / fExpected, 0.1 );
  EXPECT_EQ( 0, iSp1SnagsGroup1 );
  EXPECT_EQ( 0, iSp2SnagsGroup1 );
  EXPECT_EQ( 0, iSp1SnagsGroup2 );
  EXPECT_EQ( 0, iSp2SnagsGroup2 );
  EXPECT_EQ( 100, iNoStormSnags );
}

/////////////////////////////////////////////////////////////////////////////
// TestStormKillerRun1Timestep3()
/////////////////////////////////////////////////////////////////////////////
void TestStormKillerRun1Timestep3( clTreePopulation * p_oPop )
{
  using namespace std;
  clTreeSearch * p_oAllTrees;
  clTree * p_oTree;
  stringstream sMessage;
  float fX, fY, fDiam, fExpected;
  int iSp1Group1, iSp2Group1,
  iSp1Group2, iSp2Group2,
  iSp1Group3, iSp2Group3,
  iSp1SnagsGroup1, iSp2SnagsGroup1,
  iSp1SnagsGroup2, iSp2SnagsGroup2,
  iNoStormSnags,
  iSp, iStmDmgValue,
  iIsDead;

  //Get all trees
  p_oAllTrees = p_oPop->Find( "all" );

  //>>>>>>>>>>>>Separate out and only do cell 0,0<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0.  Group 2: storm damage = 1002.  Group 3:
  //storm damage = 2002.
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  iSp1SnagsGroup1 = 0; iSp2SnagsGroup1 = 0;
  iSp1SnagsGroup2 = 0; iSp2SnagsGroup2 = 0;
  iNoStormSnags = 0;

  p_oTree = p_oAllTrees->NextTree();
  while ( p_oTree )
  {

    iSp = p_oTree->GetSpecies();

    //Get X and Y
    p_oTree->GetValue( p_oPop->GetXCode( iSp, p_oTree->GetType() ), & fX );
    p_oTree->GetValue( p_oPop->GetYCode( iSp, p_oTree->GetType() ), & fY );

    //Get storm damage counter
    p_oTree->GetValue( p_oPop->GetIntDataCode( "stm_dmg", iSp, p_oTree->GetType() ), & iStmDmgValue );

    if ( fX < 8 && fY < 8 )
    {

      //Get DBH
      p_oTree->GetValue( p_oPop->GetDbhCode( iSp, p_oTree->GetType() ), & fDiam );

      //Test "deadness"
      p_oTree->GetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), &iIsDead);
      EXPECT_EQ(notdead, iIsDead);

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if (notdead == iIsDead) {
        if ( fDiam < 6 ) {
          EXPECT_EQ( 0, iStmDmgValue );
        }
        else if ( 0 == iSp && 0 == iStmDmgValue ) {
          if (clTreePopulation::snag == p_oTree->GetType()) iNoStormSnags++;
          else iSp1Group1++;
        }
        else if ( 1 == iSp && 0 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iNoStormSnags++;
          else iSp2Group1++;
        }
        else if ( 0 == iSp && 1002 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp1SnagsGroup1++;
          else iSp1Group2++;
        }
        else if ( 1 == iSp && 1002 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp2SnagsGroup1++;
          else iSp2Group2++;
        }
        else if ( 0 == iSp && 2002 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp1SnagsGroup2++;
          else iSp1Group3++;
        }
        else if ( 1 == iSp && 2002 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp2SnagsGroup2++;
          else iSp2Group3++;
        }
        else
        {
          //Error
          sMessage << "TestNormalProcessingRun1, timestep 3, found an unexpected " << "tree storm damage value.  X: " << fX
              << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
          FAIL() << sMessage.str();
        }
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  //Validate the counts
  EXPECT_EQ( 1000, iSp1Group1 );
  EXPECT_EQ( 1000, iSp2Group1 );
  EXPECT_EQ( 0, iSp1Group2 );
  EXPECT_EQ( 0, iSp2Group2 );
  EXPECT_EQ( 0, iSp1Group3 );
  EXPECT_EQ( 0, iSp2Group3 );
  EXPECT_EQ( 0, iSp1SnagsGroup1 );
  EXPECT_EQ( 0, iSp2SnagsGroup1 );
  EXPECT_EQ( 0, iSp1SnagsGroup2 );
  EXPECT_EQ( 0, iSp2SnagsGroup2 );
  EXPECT_EQ( 100, iNoStormSnags );


  //>>>>>>>>>>>>Separate out and only do cell 0, 1<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0.  Group 2: storm damage = 1002.  Group 3:
  //storm damage = 2002.
  p_oAllTrees->StartOver();
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  iSp1SnagsGroup1 = 0; iSp2SnagsGroup1 = 0;
  iSp1SnagsGroup2 = 0; iSp2SnagsGroup2 = 0;
  iNoStormSnags = 0;

  p_oTree = p_oAllTrees->NextTree();
  while ( p_oTree )
  {

    iSp = p_oTree->GetSpecies();

    //Get X and Y
    p_oTree->GetValue( p_oPop->GetXCode( iSp, p_oTree->GetType() ), & fX );
    p_oTree->GetValue( p_oPop->GetYCode( iSp, p_oTree->GetType() ), & fY );

    //Get storm damage counter
    p_oTree->GetValue( p_oPop->GetIntDataCode( "stm_dmg", iSp, p_oTree->GetType() ), & iStmDmgValue );

    if ( fX < 8 && fY > 8 && fY < 16 )
    {
      //Get DBH
      p_oTree->GetValue( p_oPop->GetDbhCode( iSp, p_oTree->GetType() ), & fDiam );

      //Test "deadness"
      p_oTree->GetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), &iIsDead);
      EXPECT_EQ(notdead, iIsDead);

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if (notdead == iIsDead) {
        if ( fDiam < 6 ) {
          EXPECT_EQ( 0, iStmDmgValue );
        }
        else if ( 0 == iSp && 0 == iStmDmgValue ) {
          if (clTreePopulation::snag == p_oTree->GetType()) iNoStormSnags++;
          else iSp1Group1++;
        }
        else if ( 1 == iSp && 0 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iNoStormSnags++;
          else iSp2Group1++;
        }
        else if ( 0 == iSp && 1002 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp1SnagsGroup1++;
          else iSp1Group2++;
        }
        else if ( 1 == iSp && 1002 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp2SnagsGroup1++;
          else iSp2Group2++;
        }
        else if ( 0 == iSp && 2002 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp1SnagsGroup2++;
          else iSp1Group3++;
        }
        else if ( 1 == iSp && 2002 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp2SnagsGroup2++;
          else iSp2Group3++;
        }
        else
        {
          //Error
          sMessage << "TestNormalProcessingRun1, timestep 3, found an unexpected " << "tree storm damage value.  X: " << fX
              << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
          FAIL() << sMessage.str();
        }
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  //Validate the counts
  EXPECT_EQ( 0, iSp1Group1);
  EXPECT_EQ( 0, iSp2Group1);
  fExpected = 574.4;
  EXPECT_LT( fabs( fExpected - iSp1Group2 ) / fExpected, 0.1 );
  fExpected = 850.6;
  EXPECT_LT( fabs( fExpected - iSp2Group2 ) / fExpected, 0.1 );
  EXPECT_EQ( 0, iSp1Group3);
  EXPECT_EQ( 0, iSp2Group3);
  fExpected = 425.5;
  EXPECT_LT( fabs( fExpected - iSp1SnagsGroup1 ) / fExpected, 0.1 );
  fExpected = 149.3;
  EXPECT_LT( fabs( fExpected - iSp2SnagsGroup1 ) / fExpected, 0.10 );
  EXPECT_EQ( 0, iSp1SnagsGroup2);
  EXPECT_EQ( 0, iSp2SnagsGroup2);
  EXPECT_EQ( 100, iNoStormSnags );




  //>>>>>>>>>>>>Separate out and only do cell 0, 2<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0.  Group 2: storm damage = 1002.  Group 3:
  //storm damage = 2002.
  p_oAllTrees->StartOver();
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  iSp1SnagsGroup1 = 0; iSp2SnagsGroup1 = 0;
  iSp1SnagsGroup2 = 0; iSp2SnagsGroup2 = 0;
  iNoStormSnags = 0;

  p_oTree = p_oAllTrees->NextTree();
  while ( p_oTree )
  {

    iSp = p_oTree->GetSpecies();

    //Get X and Y
    p_oTree->GetValue( p_oPop->GetXCode( iSp, p_oTree->GetType() ), & fX );
    p_oTree->GetValue( p_oPop->GetYCode( iSp, p_oTree->GetType() ), & fY );

    //Get storm damage counter
    p_oTree->GetValue( p_oPop->GetIntDataCode( "stm_dmg", iSp, p_oTree->GetType() ), & iStmDmgValue );

    if ( fX < 8 && fY > 16 && fY < 24 )
    {
      //Get DBH
      p_oTree->GetValue( p_oPop->GetDbhCode( iSp, p_oTree->GetType() ), & fDiam );

      //Test "deadness"
      p_oTree->GetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), &iIsDead);
      EXPECT_EQ(notdead, iIsDead);

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if (notdead == iIsDead) {
        if ( fDiam < 6 ) {
          EXPECT_EQ( 0, iStmDmgValue );
        }
        else if ( 0 == iSp && 0 == iStmDmgValue ) {
          if (clTreePopulation::snag == p_oTree->GetType()) iNoStormSnags++;
          else iSp1Group1++;
        }
        else if ( 1 == iSp && 0 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iNoStormSnags++;
          else iSp2Group1++;
        }
        else if ( 0 == iSp && 1002 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp1SnagsGroup1++;
          else iSp1Group2++;
        }
        else if ( 1 == iSp && 1002 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp2SnagsGroup1++;
          else iSp2Group2++;
        }
        else if ( 0 == iSp && 2002 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp1SnagsGroup2++;
          else iSp1Group3++;
        }
        else if ( 1 == iSp && 2002 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp2SnagsGroup2++;
          else iSp2Group3++;
        }
        else
        {
          //Error
          sMessage << "TestNormalProcessingRun1, timestep 3, found an unexpected " << "tree storm damage value.  X: " << fX
              << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
          FAIL() << sMessage.str();
        }
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  //Validate the counts
  EXPECT_EQ( 0, iSp1Group1 );
  EXPECT_EQ( 0, iSp2Group1 );
  EXPECT_EQ( 0, iSp1Group2 );
  EXPECT_EQ( 0, iSp2Group2 );
  fExpected = 809.9;
  EXPECT_LT( fabs( fExpected - iSp1Group3 ) / fExpected, 0.1 );
  fExpected = 472.5;
  EXPECT_LT( fabs( fExpected - iSp2Group3 ) / fExpected, 0.1 );
  EXPECT_EQ( 0, iSp1SnagsGroup1 );
  EXPECT_EQ( 0, iSp2SnagsGroup1 );
  fExpected = 133.0;
  EXPECT_LT( fabs( fExpected - iSp1SnagsGroup2 ) / fExpected, 0.2 );
  fExpected = 105.4;
  EXPECT_LT( fabs( fExpected - iSp2SnagsGroup2 ) / fExpected, 0.2 );
  EXPECT_EQ( 100, iNoStormSnags );





  //>>>>>>>>>>>>Separate out and only do cell 1, 0<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0.  Group 2: storm damage = 1002.  Group 3:
  //storm damage = 2002.
  p_oAllTrees->StartOver();
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  iSp1SnagsGroup1 = 0; iSp2SnagsGroup1 = 0;
  iSp1SnagsGroup2 = 0; iSp2SnagsGroup2 = 0;
  iNoStormSnags = 0;

  p_oTree = p_oAllTrees->NextTree();
  while ( p_oTree )
  {

    iSp = p_oTree->GetSpecies();

    //Get X and Y
    p_oTree->GetValue( p_oPop->GetXCode( iSp, p_oTree->GetType() ), & fX );
    p_oTree->GetValue( p_oPop->GetYCode( iSp, p_oTree->GetType() ), & fY );

    //Get storm damage counter
    p_oTree->GetValue( p_oPop->GetIntDataCode( "stm_dmg", iSp, p_oTree->GetType() ), & iStmDmgValue );

    if ( fX > 8 && fX < 16 && fY < 8 )
    {
      //Get DBH
      p_oTree->GetValue( p_oPop->GetDbhCode( iSp, p_oTree->GetType() ), & fDiam );

      //Test "deadness"
      p_oTree->GetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), &iIsDead);
      EXPECT_EQ(notdead, iIsDead);

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if (notdead == iIsDead) {
        if ( fDiam < 6 ) {
          EXPECT_EQ( 0, iStmDmgValue );
        }
        else if ( 0 == iSp && 0 == iStmDmgValue ) {
          if (clTreePopulation::snag == p_oTree->GetType()) iNoStormSnags++;
          else iSp1Group1++;
        }
        else if ( 1 == iSp && 0 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iNoStormSnags++;
          else iSp2Group1++;
        }
        else if ( 0 == iSp && 1002 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp1SnagsGroup1++;
          else iSp1Group2++;
        }
        else if ( 1 == iSp && 1002 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp2SnagsGroup1++;
          else iSp2Group2++;
        }
        else if ( 0 == iSp && 2002 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp1SnagsGroup2++;
          else iSp1Group3++;
        }
        else if ( 1 == iSp && 2002 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp2SnagsGroup2++;
          else iSp2Group3++;
        }
        else
        {
          //Error
          sMessage << "TestNormalProcessingRun1, timestep 3, found an unexpected " << "tree storm damage value.  X: " << fX
              << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
          FAIL() << sMessage.str();
        }
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  //Validate the counts
  EXPECT_EQ( 1000, iSp1Group1 );
  EXPECT_EQ( 1000, iSp2Group1 );
  EXPECT_EQ( 0, iSp1Group2 );
  EXPECT_EQ( 0, iSp2Group2 );
  EXPECT_EQ( 0, iSp1Group3 );
  EXPECT_EQ( 0, iSp2Group3 );
  EXPECT_EQ( 0, iSp1SnagsGroup1 );
  EXPECT_EQ( 0, iSp2SnagsGroup1 );
  EXPECT_EQ( 0, iSp1SnagsGroup2 );
  EXPECT_EQ( 0, iSp2SnagsGroup2 );
  EXPECT_EQ( 100, iNoStormSnags );




  //>>>>>>>>>>>>Separate out and only do cell 1, 1<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0.  Group 2: storm damage = 1002.  Group 3:
  //storm damage = 2002.
  p_oAllTrees->StartOver();
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  iSp1SnagsGroup1 = 0; iSp2SnagsGroup1 = 0;
  iSp1SnagsGroup2 = 0; iSp2SnagsGroup2 = 0;
  iNoStormSnags = 0;

  p_oTree = p_oAllTrees->NextTree();
  while ( p_oTree )
  {

    iSp = p_oTree->GetSpecies();

    //Get X and Y
    p_oTree->GetValue( p_oPop->GetXCode( iSp, p_oTree->GetType() ), & fX );
    p_oTree->GetValue( p_oPop->GetYCode( iSp, p_oTree->GetType() ), & fY );

    //Get storm damage counter
    p_oTree->GetValue( p_oPop->GetIntDataCode( "stm_dmg", iSp, p_oTree->GetType() ), & iStmDmgValue );

    if ( fX > 8 && fX < 16 && fY > 8 && fY < 16 )
    {
      //Get DBH
      p_oTree->GetValue( p_oPop->GetDbhCode( iSp, p_oTree->GetType() ), & fDiam );

      //Test "deadness"
      p_oTree->GetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), &iIsDead);
      EXPECT_EQ(notdead, iIsDead);

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if (notdead == iIsDead) {
        if ( fDiam < 6 ) {
          EXPECT_EQ( 0, iStmDmgValue );
        }
        else if ( 0 == iSp && 0 == iStmDmgValue ) {
          if (clTreePopulation::snag == p_oTree->GetType()) iNoStormSnags++;
          else iSp1Group1++;
        }
        else if ( 1 == iSp && 0 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iNoStormSnags++;
          else iSp2Group1++;
        }
        else if ( 0 == iSp && 1002 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp1SnagsGroup1++;
          else iSp1Group2++;
        }
        else if ( 1 == iSp && 1002 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp2SnagsGroup1++;
          else iSp2Group2++;
        }
        else if ( 0 == iSp && 2002 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp1SnagsGroup2++;
          else iSp1Group3++;
        }
        else if ( 1 == iSp && 2002 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp2SnagsGroup2++;
          else iSp2Group3++;
        }
        else
        {
          //Error
          sMessage << "TestNormalProcessingRun1, timestep 3, found an unexpected " << "tree storm damage value.  X: " << fX
              << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
          FAIL() << sMessage.str();
        }
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  //Validate the counts
  EXPECT_EQ( 0, iSp1Group1);
  EXPECT_EQ( 0, iSp2Group1);
  fExpected = 627.1;
  EXPECT_LT( fabs( fExpected - iSp1Group2 ) / fExpected, 0.1 );
  fExpected = 898.4;
  EXPECT_LT( fabs( fExpected - iSp2Group2 ) / fExpected, 0.1 );
  EXPECT_EQ( 0, iSp1Group3);
  EXPECT_EQ( 0, iSp2Group3);
  EXPECT_EQ( 0, iSp1SnagsGroup1);
  EXPECT_EQ( 0, iSp1SnagsGroup2);
  EXPECT_EQ( 0, iSp2SnagsGroup1);
  EXPECT_EQ( 0, iSp2SnagsGroup2);
  EXPECT_EQ( 100, iNoStormSnags );






  //>>>>>>>>>>>>Separate out and only do cell 1, 2<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0.  Group 2: storm damage = 1002.  Group 3:
  //storm damage = 2002.
  p_oAllTrees->StartOver();
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  iSp1SnagsGroup1 = 0; iSp2SnagsGroup1 = 0;
  iSp1SnagsGroup2 = 0; iSp2SnagsGroup2 = 0;
  iNoStormSnags = 0;

  p_oTree = p_oAllTrees->NextTree();
  while ( p_oTree )
  {

    iSp = p_oTree->GetSpecies();

    //Get X and Y
    p_oTree->GetValue( p_oPop->GetXCode( iSp, p_oTree->GetType() ), & fX );
    p_oTree->GetValue( p_oPop->GetYCode( iSp, p_oTree->GetType() ), & fY );

    //Get storm damage counter
    p_oTree->GetValue( p_oPop->GetIntDataCode( "stm_dmg", iSp, p_oTree->GetType() ), & iStmDmgValue );

    if ( fX > 8 && fX < 16 && fY > 16 && fY < 24 )
    {
      //Get DBH
      p_oTree->GetValue( p_oPop->GetDbhCode( iSp, p_oTree->GetType() ), & fDiam );

      //Test "deadness"
      p_oTree->GetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), &iIsDead);
      EXPECT_EQ(notdead, iIsDead);

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if (notdead == iIsDead) {
        if ( fDiam < 6 ) {
          EXPECT_EQ( 0, iStmDmgValue );
        }
        else if ( 0 == iSp && 0 == iStmDmgValue ) {
          if (clTreePopulation::snag == p_oTree->GetType()) iNoStormSnags++;
          else iSp1Group1++;
        }
        else if ( 1 == iSp && 0 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iNoStormSnags++;
          else iSp2Group1++;
        }
        else if ( 0 == iSp && 1002 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp1SnagsGroup1++;
          else iSp1Group2++;
        }
        else if ( 1 == iSp && 1002 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp2SnagsGroup1++;
          else iSp2Group2++;
        }
        else if ( 0 == iSp && 2002 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp1SnagsGroup2++;
          else iSp1Group3++;
        }
        else if ( 1 == iSp && 2002 == iStmDmgValue )
        {
          if (clTreePopulation::snag == p_oTree->GetType()) iSp2SnagsGroup2++;
          else iSp2Group3++;
        }
        else
        {
          //Error
          sMessage << "TestNormalProcessingRun1, timestep 3, found an unexpected " << "tree storm damage value.  X: " << fX
              << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
          FAIL() << sMessage.str();
        }
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  //Validate the counts
  EXPECT_EQ( 0, iSp1Group1 );
  EXPECT_EQ( 0, iSp2Group1 );
  EXPECT_EQ( 0, iSp1Group2 );
  EXPECT_EQ( 0, iSp2Group2 );
  fExpected = 960.3;
  EXPECT_LT( fabs( fExpected - iSp1Group3 ) / fExpected, 0.1 );
  fExpected = 729.0;
  EXPECT_LT( fabs( fExpected - iSp2Group3 ) / fExpected, 0.1 );
  EXPECT_EQ( 0, iSp1SnagsGroup1 );
  EXPECT_EQ( 0, iSp2SnagsGroup1 );
  EXPECT_EQ( 0, iSp1SnagsGroup2 );
  EXPECT_EQ( 0, iSp2SnagsGroup2 );
  EXPECT_EQ( 100, iNoStormSnags );
}

/////////////////////////////////////////////////////////////////////////////
// TestStormKillerRun1Timestep4()
/////////////////////////////////////////////////////////////////////////////
void TestStormKillerRun1Timestep4( clTreePopulation * p_oPop )
{
  using namespace std;
  clTreeSearch * p_oAllTrees;
  clTree * p_oTree;
  stringstream sMessage;
  float fX, fY, fDiam, fExpected;
  int iSp1Group1, iSp2Group1,
  iSp1Group2, iSp2Group2,
  iSp1Group3, iSp2Group3,
  iNoStormSnags,
  iSp, iStmDmgValue,
  iIsDead;

  //Get all trees
  p_oAllTrees = p_oPop->Find( "all" );

  //>>>>>>>>>>>>Separate out and only do cell 0,0<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0.  Group 2: storm damage = 1003.  Group 3:
  //storm damage = 2003.
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  iNoStormSnags = 0;

  int iTest = 0;

  p_oTree = p_oAllTrees->NextTree();
  while ( p_oTree )
  {

    if (p_oTree->GetType() != clTreePopulation::snag)
      iTest++;

    iSp = p_oTree->GetSpecies();

    //Get X and Y
    p_oTree->GetValue( p_oPop->GetXCode( iSp, p_oTree->GetType() ), & fX );
    p_oTree->GetValue( p_oPop->GetYCode( iSp, p_oTree->GetType() ), & fY );

    //Get storm damage counter
    p_oTree->GetValue( p_oPop->GetIntDataCode( "stm_dmg", iSp, p_oTree->GetType() ), & iStmDmgValue );

    if ( fX < 8 && fY < 8 )
    {

      //Get DBH
      p_oTree->GetValue( p_oPop->GetDbhCode( iSp, p_oTree->GetType() ), & fDiam );

      //Test "deadness"
      p_oTree->GetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), &iIsDead);
      EXPECT_EQ(notdead, iIsDead);

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if ( fDiam < 6 ) {
        EXPECT_EQ( 0, iStmDmgValue );
      }
      else if ( 0 == iSp && 0 == iStmDmgValue ) {
        if (clTreePopulation::snag == p_oTree->GetType()) iNoStormSnags++;
        else iSp1Group1++;
      }
      else if ( 1 == iSp && 0 == iStmDmgValue )
      {
        if (clTreePopulation::snag == p_oTree->GetType()) iNoStormSnags++;
        else iSp2Group1++;
      }
      else if ( 0 == iSp && 1003 == iStmDmgValue )
      {
        EXPECT_NE( clTreePopulation::snag, p_oTree->GetType());
        iSp1Group2++;
      }
      else if ( 1 == iSp && 1003 == iStmDmgValue )
      {
        EXPECT_NE(clTreePopulation::snag, p_oTree->GetType());
        iSp2Group2++;
      }
      else if ( 0 == iSp && 2003 == iStmDmgValue )
      {
        EXPECT_NE(clTreePopulation::snag, p_oTree->GetType());
        iSp1Group3++;
      }
      else if ( 1 == iSp && 2003 == iStmDmgValue )
      {
        EXPECT_NE(clTreePopulation::snag, p_oTree->GetType());
        iSp2Group3++;
      }
      else
      {
        //Error
        sMessage << "TestNormalProcessingRun1, timestep 4, found an unexpected " << "tree storm damage value.  X: " << fX
            << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
        FAIL() << sMessage.str();
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  //Validate the counts
  EXPECT_EQ( 1000, iSp1Group1 );
  EXPECT_EQ( 1000, iSp2Group1 );
  EXPECT_EQ( 0, iSp1Group2 );
  EXPECT_EQ( 0, iSp2Group2 );
  EXPECT_EQ( 0, iSp1Group3 );
  EXPECT_EQ( 0, iSp2Group3 );
  EXPECT_EQ( 100, iNoStormSnags );


  //>>>>>>>>>>>>Separate out and only do cell 0, 1<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0.  Group 2: storm damage = 1003.  Group 3:
  //storm damage = 2003.
  p_oAllTrees->StartOver();
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  iNoStormSnags = 0;

  p_oTree = p_oAllTrees->NextTree();
  while ( p_oTree )
  {

    iSp = p_oTree->GetSpecies();

    //Get X and Y
    p_oTree->GetValue( p_oPop->GetXCode( iSp, p_oTree->GetType() ), & fX );
    p_oTree->GetValue( p_oPop->GetYCode( iSp, p_oTree->GetType() ), & fY );

    //Get storm damage counter
    p_oTree->GetValue( p_oPop->GetIntDataCode( "stm_dmg", iSp, p_oTree->GetType() ), & iStmDmgValue );

    if ( fX < 8 && fY > 8 && fY < 16 )
    {
      //Get DBH
      p_oTree->GetValue( p_oPop->GetDbhCode( iSp, p_oTree->GetType() ), & fDiam );

      //Test "deadness"
      p_oTree->GetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), &iIsDead);
      EXPECT_EQ(notdead, iIsDead);

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if ( fDiam < 6 ) {
        EXPECT_EQ( 0, iStmDmgValue );
      }
      else if ( 0 == iSp && 0 == iStmDmgValue ) {
        if (clTreePopulation::snag == p_oTree->GetType()) iNoStormSnags++;
        else iSp1Group1++;
      }
      else if ( 1 == iSp && 0 == iStmDmgValue )
      {
        if (clTreePopulation::snag == p_oTree->GetType()) iNoStormSnags++;
        else iSp2Group1++;
      }
      else if ( 0 == iSp && 1003 == iStmDmgValue )
      {
        EXPECT_NE(clTreePopulation::snag, p_oTree->GetType());
        iSp1Group2++;
      }
      else if ( 1 == iSp && 1003 == iStmDmgValue )
      {
        EXPECT_NE(clTreePopulation::snag, p_oTree->GetType());
        iSp2Group2++;
      }
      else if ( 0 == iSp && 2003 == iStmDmgValue )
      {
        EXPECT_NE(clTreePopulation::snag, p_oTree->GetType());
        iSp1Group3++;
      }
      else if ( 1 == iSp && 2003 == iStmDmgValue )
      {
        EXPECT_NE(clTreePopulation::snag, p_oTree->GetType());
        iSp2Group3++;
      }
      else
      {
        //Error
        sMessage << "TestNormalProcessingRun1, timestep 4, found an unexpected " << "tree storm damage value.  X: " << fX
            << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
        FAIL() << sMessage.str();
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  //Validate the counts
  EXPECT_EQ( 0, iSp1Group1);
  EXPECT_EQ( 0, iSp2Group1);
  fExpected = 574.4;
  EXPECT_LT( fabs( fExpected - iSp1Group2 ) / fExpected, 0.1 );
  fExpected = 850.6;
  EXPECT_LT( fabs( fExpected - iSp2Group2 ) / fExpected, 0.1 );
  EXPECT_EQ( 0, iSp1Group3);
  EXPECT_EQ( 0, iSp2Group3);
  EXPECT_EQ( 100, iNoStormSnags );




  //>>>>>>>>>>>>Separate out and only do cell 0, 2<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0.  Group 2: storm damage = 1003.  Group 3:
  //storm damage = 2003.
  p_oAllTrees->StartOver();
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  iNoStormSnags = 0;

  p_oTree = p_oAllTrees->NextTree();
  while ( p_oTree )
  {

    iSp = p_oTree->GetSpecies();

    //Get X and Y
    p_oTree->GetValue( p_oPop->GetXCode( iSp, p_oTree->GetType() ), & fX );
    p_oTree->GetValue( p_oPop->GetYCode( iSp, p_oTree->GetType() ), & fY );

    //Get storm damage counter
    p_oTree->GetValue( p_oPop->GetIntDataCode( "stm_dmg", iSp, p_oTree->GetType() ), & iStmDmgValue );

    if ( fX < 8 && fY > 16 && fY < 24 )
    {
      //Get DBH
      p_oTree->GetValue( p_oPop->GetDbhCode( iSp, p_oTree->GetType() ), & fDiam );

      //Test "deadness"
      p_oTree->GetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), &iIsDead);
      EXPECT_EQ(notdead, iIsDead);

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if ( fDiam < 6 ) {
        EXPECT_EQ( 0, iStmDmgValue );
      }
      else if ( 0 == iSp && 0 == iStmDmgValue ) {
        if (clTreePopulation::snag == p_oTree->GetType()) iNoStormSnags++;
        else iSp1Group1++;
      }
      else if ( 1 == iSp && 0 == iStmDmgValue )
      {
        if (clTreePopulation::snag == p_oTree->GetType()) iNoStormSnags++;
        else iSp2Group1++;
      }
      else if ( 0 == iSp && 1003 == iStmDmgValue )
      {
        EXPECT_NE(clTreePopulation::snag, p_oTree->GetType());
        iSp1Group2++;
      }
      else if ( 1 == iSp && 1003 == iStmDmgValue )
      {
        EXPECT_NE(clTreePopulation::snag, p_oTree->GetType());
        iSp2Group2++;
      }
      else if ( 0 == iSp && 2003 == iStmDmgValue )
      {
        EXPECT_NE(clTreePopulation::snag, p_oTree->GetType());
        iSp1Group3++;
      }
      else if ( 1 == iSp && 2003 == iStmDmgValue )
      {
        EXPECT_NE(clTreePopulation::snag, p_oTree->GetType());
        iSp2Group3++;
      }
      else
      {
        //Error
        sMessage << "TestNormalProcessingRun1, timestep 4, found an unexpected " << "tree storm damage value.  X: " << fX
            << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
        FAIL() << sMessage.str();
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  //Validate the counts
  EXPECT_EQ( 0, iSp1Group1 );
  EXPECT_EQ( 0, iSp2Group1 );
  EXPECT_EQ( 0, iSp1Group2 );
  EXPECT_EQ( 0, iSp2Group2 );
  fExpected = 809.9;
  EXPECT_LT( fabs( fExpected - iSp1Group3 ) / fExpected, 0.1 );
  fExpected = 472.5;
  EXPECT_LT( fabs( fExpected - iSp2Group3 ) / fExpected, 0.1 );
  EXPECT_EQ( 100, iNoStormSnags );





  //>>>>>>>>>>>>Separate out and only do cell 1, 0<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0.  Group 2: storm damage = 1003.  Group 3:
  //storm damage = 2003.
  p_oAllTrees->StartOver();
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  iNoStormSnags = 0;

  p_oTree = p_oAllTrees->NextTree();
  while ( p_oTree )
  {

    iSp = p_oTree->GetSpecies();

    //Get X and Y
    p_oTree->GetValue( p_oPop->GetXCode( iSp, p_oTree->GetType() ), & fX );
    p_oTree->GetValue( p_oPop->GetYCode( iSp, p_oTree->GetType() ), & fY );

    //Get storm damage counter
    p_oTree->GetValue( p_oPop->GetIntDataCode( "stm_dmg", iSp, p_oTree->GetType() ), & iStmDmgValue );

    if ( fX > 8 && fX < 16 && fY < 8 )
    {
      //Get DBH
      p_oTree->GetValue( p_oPop->GetDbhCode( iSp, p_oTree->GetType() ), & fDiam );

      //Test "deadness"
      p_oTree->GetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), &iIsDead);
      EXPECT_EQ(notdead, iIsDead);

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if ( fDiam < 6 ) {
        EXPECT_EQ( 0, iStmDmgValue );
      }
      else if ( 0 == iSp && 0 == iStmDmgValue ) {
        if (clTreePopulation::snag == p_oTree->GetType()) iNoStormSnags++;
        else iSp1Group1++;
      }
      else if ( 1 == iSp && 0 == iStmDmgValue )
      {
        if (clTreePopulation::snag == p_oTree->GetType()) iNoStormSnags++;
        else iSp2Group1++;
      }
      else if ( 0 == iSp && 1003 == iStmDmgValue )
      {
        EXPECT_NE(clTreePopulation::snag, p_oTree->GetType());
        iSp1Group2++;
      }
      else if ( 1 == iSp && 1003 == iStmDmgValue )
      {
        EXPECT_NE(clTreePopulation::snag, p_oTree->GetType());
        iSp2Group2++;
      }
      else if ( 0 == iSp && 2003 == iStmDmgValue )
      {
        EXPECT_NE(clTreePopulation::snag, p_oTree->GetType());
        iSp1Group3++;
      }
      else if ( 1 == iSp && 2003 == iStmDmgValue )
      {
        EXPECT_NE(clTreePopulation::snag, p_oTree->GetType());
        iSp2Group3++;
      }
      else
      {
        //Error
        sMessage << "TestNormalProcessingRun1, timestep 4, found an unexpected " << "tree storm damage value.  X: " << fX
            << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
        FAIL() << sMessage.str();
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  //Validate the counts
  EXPECT_EQ( 1000, iSp1Group1 );
  EXPECT_EQ( 1000, iSp2Group1 );
  EXPECT_EQ( 0, iSp1Group2 );
  EXPECT_EQ( 0, iSp2Group2 );
  EXPECT_EQ( 0, iSp1Group3 );
  EXPECT_EQ( 0, iSp2Group3 );
  EXPECT_EQ( 100, iNoStormSnags );




  //>>>>>>>>>>>>Separate out and only do cell 1, 1<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0.  Group 2: storm damage = 1003.  Group 3:
  //storm damage = 2003.
  p_oAllTrees->StartOver();
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  iNoStormSnags = 0;

  p_oTree = p_oAllTrees->NextTree();
  while ( p_oTree )
  {

    iSp = p_oTree->GetSpecies();

    //Get X and Y
    p_oTree->GetValue( p_oPop->GetXCode( iSp, p_oTree->GetType() ), & fX );
    p_oTree->GetValue( p_oPop->GetYCode( iSp, p_oTree->GetType() ), & fY );

    //Get storm damage counter
    p_oTree->GetValue( p_oPop->GetIntDataCode( "stm_dmg", iSp, p_oTree->GetType() ), & iStmDmgValue );

    if ( fX > 8 && fX < 16 && fY > 8 && fY < 16 )
    {
      //Get DBH
      p_oTree->GetValue( p_oPop->GetDbhCode( iSp, p_oTree->GetType() ), & fDiam );

      //Test "deadness"
      p_oTree->GetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), &iIsDead);
      EXPECT_EQ(notdead, iIsDead);

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if ( fDiam < 6 ) {
        EXPECT_EQ( 0, iStmDmgValue );
      }
      else if ( 0 == iSp && 0 == iStmDmgValue ) {
        if (clTreePopulation::snag == p_oTree->GetType()) iNoStormSnags++;
        else iSp1Group1++;
      }
      else if ( 1 == iSp && 0 == iStmDmgValue )
      {
        if (clTreePopulation::snag == p_oTree->GetType()) iNoStormSnags++;
        else iSp2Group1++;
      }
      else if ( 0 == iSp && 1003 == iStmDmgValue )
      {
        EXPECT_NE(clTreePopulation::snag, p_oTree->GetType());
        iSp1Group2++;
      }
      else if ( 1 == iSp && 1003 == iStmDmgValue )
      {
        EXPECT_NE(clTreePopulation::snag, p_oTree->GetType());
        iSp2Group2++;
      }
      else if ( 0 == iSp && 2003 == iStmDmgValue )
      {
        EXPECT_NE(clTreePopulation::snag, p_oTree->GetType());
        iSp1Group3++;
      }
      else if ( 1 == iSp && 2003 == iStmDmgValue )
      {
        EXPECT_NE(clTreePopulation::snag, p_oTree->GetType());
        iSp2Group3++;
      }
      else
      {
        //Error
        sMessage << "TestNormalProcessingRun1, timestep 4, found an unexpected " << "tree storm damage value.  X: " << fX
            << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
        FAIL() << sMessage.str();
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  //Validate the counts
  EXPECT_EQ( 0, iSp1Group1);
  EXPECT_EQ( 0, iSp2Group1);
  fExpected = 627.1;
  EXPECT_LT( fabs( fExpected - iSp1Group2 ) / fExpected, 0.1 );
  fExpected = 898.4;
  EXPECT_LT( fabs( fExpected - iSp2Group2 ) / fExpected, 0.1 );
  EXPECT_EQ( 0, iSp1Group3);
  EXPECT_EQ( 0, iSp2Group3);
  EXPECT_EQ( 100, iNoStormSnags );






  //>>>>>>>>>>>>Separate out and only do cell 1, 2<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0.  Group 2: storm damage = 1003.  Group 3:
  //storm damage = 2003.
  p_oAllTrees->StartOver();
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  iNoStormSnags = 0;

  p_oTree = p_oAllTrees->NextTree();
  while ( p_oTree )
  {

    iSp = p_oTree->GetSpecies();

    //Get X and Y
    p_oTree->GetValue( p_oPop->GetXCode( iSp, p_oTree->GetType() ), & fX );
    p_oTree->GetValue( p_oPop->GetYCode( iSp, p_oTree->GetType() ), & fY );

    //Get storm damage counter
    p_oTree->GetValue( p_oPop->GetIntDataCode( "stm_dmg", iSp, p_oTree->GetType() ), & iStmDmgValue );

    if ( fX > 8 && fX < 16 && fY > 16 && fY < 24 )
    {
      //Get DBH
      p_oTree->GetValue( p_oPop->GetDbhCode( iSp, p_oTree->GetType() ), & fDiam );

      //Test "deadness"
      p_oTree->GetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), &iIsDead);
      EXPECT_EQ(notdead, iIsDead);

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if ( fDiam < 6 ) {
        EXPECT_EQ( 0, iStmDmgValue );
      }
      else if ( 0 == iSp && 0 == iStmDmgValue ) {
        if (clTreePopulation::snag == p_oTree->GetType()) iNoStormSnags++;
        else iSp1Group1++;
      }
      else if ( 1 == iSp && 0 == iStmDmgValue )
      {
        if (clTreePopulation::snag == p_oTree->GetType()) iNoStormSnags++;
        else iSp2Group1++;
      }
      else if ( 0 == iSp && 1003 == iStmDmgValue )
      {
        EXPECT_NE(clTreePopulation::snag, p_oTree->GetType());
        iSp1Group2++;
      }
      else if ( 1 == iSp && 1003 == iStmDmgValue )
      {
        EXPECT_NE(clTreePopulation::snag, p_oTree->GetType());
        iSp2Group2++;
      }
      else if ( 0 == iSp && 2003 == iStmDmgValue )
      {
        EXPECT_NE(clTreePopulation::snag, p_oTree->GetType());
        iSp1Group3++;
      }
      else if ( 1 == iSp && 2003 == iStmDmgValue )
      {
        EXPECT_NE(clTreePopulation::snag, p_oTree->GetType());
        iSp2Group3++;
      }
      else
      {
        //Error
        sMessage << "TestNormalProcessingRun1, timestep 4, found an unexpected " << "tree storm damage value.  X: " << fX
            << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
        FAIL() << sMessage.str();
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  //Validate the counts
  EXPECT_EQ( 0, iSp1Group1 );
  EXPECT_EQ( 0, iSp2Group1 );
  fExpected = 960.3;
  EXPECT_LT( fabs( fExpected - iSp1Group3 ) / fExpected, 0.1 );
  fExpected = 729.0;
  EXPECT_LT( fabs( fExpected - iSp2Group3 ) / fExpected, 0.1 );
  EXPECT_EQ( 100, iNoStormSnags );
}

/////////////////////////////////////////////////////////////////////////////
// TestStormKillerRun1Timestep5()
/////////////////////////////////////////////////////////////////////////////
void TestStormKillerRun1Timestep5( clTreePopulation * p_oPop )
{
  clTreeSearch * p_oAllTrees;
  clTree * p_oTree;
  int iStmDmgValue;
  int iNumSnags = 0;

  //Get all trees
  p_oAllTrees = p_oPop->Find( "all" );

  //All should have a damage of 0.
  p_oTree = p_oAllTrees->NextTree();
  while ( p_oTree )
  {
    //Make sure we only have our original snags.
    if (clTreePopulation::snag == p_oTree->GetType()) iNumSnags++;
    p_oTree->GetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), & iStmDmgValue );
    EXPECT_EQ( 0, iStmDmgValue );
    p_oTree = p_oAllTrees->NextTree();
  }

  EXPECT_EQ(600, iNumSnags);
}

/////////////////////////////////////////////////////////////////////////////
// TestStormKillerRun3Timestep1()
/////////////////////////////////////////////////////////////////////////////
void TestStormKillerRun3Timestep1( clTreePopulation * p_oPop )
{
  using namespace std;
  clTreeSearch * p_oAllTrees;
  clTree * p_oTree;
  stringstream sMessage;
  float fX, fY, fDiam, fExpected;
  int iSp1Group1, iSp2Group1, iSp1Group2, iSp2Group2, iSp1Group3, iSp2Group3, iSp, iStmDmgValue;

  //Get all trees
  p_oAllTrees = p_oPop->Find( "all" );

  //>>>>>>>>>>>>Separate out and only do cell 0,0<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0.  Group 2: storm damage = 1000.  Group 3:
  //storm damage = 2000.
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  p_oTree = p_oAllTrees->NextTree();
  while ( p_oTree )
  {

    //Make sure this ain't no snag
    EXPECT_NE(clTreePopulation::snag, p_oTree->GetType());

    iSp = p_oTree->GetSpecies();

    //Get X and Y
    p_oTree->GetValue( p_oPop->GetXCode( iSp, p_oTree->GetType() ), & fX );
    p_oTree->GetValue( p_oPop->GetYCode( iSp, p_oTree->GetType() ), & fY );

    //Get storm damage counter
    p_oTree->GetValue( p_oPop->GetIntDataCode( "stm_dmg", iSp, p_oTree->GetType() ), & iStmDmgValue );

    if ( fX < 8 && fY < 8 )
    {
      //Get DBH
      p_oTree->GetValue( p_oPop->GetDbhCode( iSp, p_oTree->GetType() ), & fDiam );

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if ( fDiam < 6 )  EXPECT_EQ( 0, iStmDmgValue );
      else if ( 0 == iSp && 0 == iStmDmgValue ) iSp1Group1++;
      else if ( 1 == iSp && 0 == iStmDmgValue ) iSp2Group1++;
      else if ( 0 == iSp && 1000 == iStmDmgValue ) iSp1Group2++;
      else if ( 1 == iSp && 1000 == iStmDmgValue ) iSp2Group2++;
      else if ( 0 == iSp && 2000 == iStmDmgValue ) iSp1Group3++;
      else if ( 1 == iSp && 2000 == iStmDmgValue ) iSp2Group3++;
      else
      {
        //Error
        sMessage << "TestNormalProcessingRun3, timestep 1, found an unexpected " << "tree storm damage value.  X: " << fX
            << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
        FAIL() << sMessage.str();
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  //Validate the counts
  EXPECT_EQ( 1000, iSp1Group1 );
  EXPECT_EQ( 1000, iSp2Group1 );
  EXPECT_EQ( 0, iSp1Group2 );
  EXPECT_EQ( 0, iSp2Group2 );
  EXPECT_EQ( 0, iSp1Group3 );
  EXPECT_EQ( 0, iSp2Group3 );

  //>>>>>>>>>>>>Separate out and only do cell 0, 1<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0.  Group 2: storm damage = 1000.  Group 3:
  //storm damage = 2000.
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  p_oAllTrees->StartOver();
  p_oTree = p_oAllTrees->NextTree();
  while ( p_oTree )
  {
    //Make sure this ain't no snag
    EXPECT_NE(clTreePopulation::snag, p_oTree->GetType());

    iSp = p_oTree->GetSpecies();

    //Get X and Y
    p_oTree->GetValue( p_oPop->GetXCode( iSp, p_oTree->GetType() ), & fX );
    p_oTree->GetValue( p_oPop->GetYCode( iSp, p_oTree->GetType() ), & fY );

    //Get storm damage counter
    p_oTree->GetValue( p_oPop->GetIntDataCode( "stm_dmg", iSp, p_oTree->GetType() ), & iStmDmgValue );

    if ( fX < 8 && fY > 8 && fY < 16 )
    {

      //Get DBH
      p_oTree->GetValue( p_oPop->GetDbhCode( iSp, p_oTree->GetType() ), & fDiam );

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if ( fDiam < 6 )  EXPECT_EQ( 0, iStmDmgValue );
      else if ( 0 == iSp && 0 == iStmDmgValue ) iSp1Group1++;
      else if ( 1 == iSp && 0 == iStmDmgValue ) iSp2Group1++;
      else if ( 0 == iSp && 1000 == iStmDmgValue ) iSp1Group2++;
      else if ( 1 == iSp && 1000 == iStmDmgValue ) iSp2Group2++;
      else if ( 0 == iSp && 2000 == iStmDmgValue ) iSp1Group3++;
      else if ( 1 == iSp && 2000 == iStmDmgValue ) iSp2Group3++;
      else
      {
        //Error
        sMessage << "TestNormalProcessingRun3, timestep 1, found an unexpected " << "tree storm damage value.  X: " << fX
            << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
        FAIL() << sMessage.str();
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  //Validate the counts
  EXPECT_EQ( 0, iSp1Group1 );
  EXPECT_EQ( 0, iSp2Group1 );
  fExpected = 574.4;
  EXPECT_LT( fabs( fExpected - iSp1Group2 ) / fExpected, 0.1 );
  fExpected = 850.6;
  EXPECT_LT( fabs( fExpected - iSp2Group2 ) / fExpected, 0.1 );
  EXPECT_EQ( 0, iSp1Group3 );
  EXPECT_EQ( 0, iSp2Group3 );




  //>>>>>>>>>>>>Separate out and only do cell 0, 2<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0.  Group 2: storm damage = 1000.  Group 3:
  //storm damage = 2000.
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  p_oAllTrees->StartOver();
  p_oTree = p_oAllTrees->NextTree();
  while ( p_oTree )
  {
    //Make sure this ain't no snag
    EXPECT_NE(clTreePopulation::snag, p_oTree->GetType());

    iSp = p_oTree->GetSpecies();

    //Get X and Y
    p_oTree->GetValue( p_oPop->GetXCode( iSp, p_oTree->GetType() ), & fX );
    p_oTree->GetValue( p_oPop->GetYCode( iSp, p_oTree->GetType() ), & fY );

    //Get storm damage counter
    p_oTree->GetValue( p_oPop->GetIntDataCode( "stm_dmg", iSp, p_oTree->GetType() ), & iStmDmgValue );

    if ( fX < 8 && fY > 16 && fY < 24 )
    {

      //Get DBH
      p_oTree->GetValue( p_oPop->GetDbhCode( iSp, p_oTree->GetType() ), & fDiam );

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if ( fDiam < 6 )  EXPECT_EQ( 0, iStmDmgValue );
      else if ( 0 == iSp && 0 == iStmDmgValue ) iSp1Group1++;
      else if ( 1 == iSp && 0 == iStmDmgValue ) iSp2Group1++;
      else if ( 0 == iSp && 1000 == iStmDmgValue ) iSp1Group2++;
      else if ( 1 == iSp && 1000 == iStmDmgValue ) iSp2Group2++;
      else if ( 0 == iSp && 2000 == iStmDmgValue ) iSp1Group3++;
      else if ( 1 == iSp && 2000 == iStmDmgValue ) iSp2Group3++;
      else
      {
        //Error
        sMessage << "TestNormalProcessingRun3, timestep 1, found an unexpected " << "tree storm damage value.  X: " << fX
            << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
        FAIL() << sMessage.str();
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  //Validate the counts
  EXPECT_EQ( 0, iSp1Group1 );
  EXPECT_EQ( 0, iSp2Group1 );
  EXPECT_EQ( 0, iSp1Group2 );
  EXPECT_EQ( 0, iSp2Group2 );
  fExpected = 809.9;
  EXPECT_LT( fabs( fExpected - iSp1Group3 ) / fExpected, 0.1 );
  fExpected = 472.5;
  EXPECT_LT( fabs( fExpected - iSp2Group3 ) / fExpected, 0.1 );




  //>>>>>>>>>>>>Separate out and only do cell 1, 0<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0.  Group 2: storm damage = 1000.  Group 3:
  //storm damage = 2000.
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  p_oAllTrees->StartOver();
  p_oTree = p_oAllTrees->NextTree();
  while ( p_oTree )
  {
    //Make sure this ain't no snag
    EXPECT_NE(clTreePopulation::snag, p_oTree->GetType());

    iSp = p_oTree->GetSpecies();

    //Get X and Y
    p_oTree->GetValue( p_oPop->GetXCode( iSp, p_oTree->GetType() ), & fX );
    p_oTree->GetValue( p_oPop->GetYCode( iSp, p_oTree->GetType() ), & fY );

    //Get storm damage counter
    p_oTree->GetValue( p_oPop->GetIntDataCode( "stm_dmg", iSp, p_oTree->GetType() ), & iStmDmgValue );

    if ( fX > 8 && fX < 16 && fY < 8 )
    {

      //Get DBH
      p_oTree->GetValue( p_oPop->GetDbhCode( iSp, p_oTree->GetType() ), & fDiam );

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if ( fDiam < 6 )  EXPECT_EQ( 0, iStmDmgValue );
      else if ( 0 == iSp && 0 == iStmDmgValue ) iSp1Group1++;
      else if ( 1 == iSp && 0 == iStmDmgValue ) iSp2Group1++;
      else if ( 0 == iSp && 1000 == iStmDmgValue ) iSp1Group2++;
      else if ( 1 == iSp && 1000 == iStmDmgValue ) iSp2Group2++;
      else if ( 0 == iSp && 2000 == iStmDmgValue ) iSp1Group3++;
      else if ( 1 == iSp && 2000 == iStmDmgValue ) iSp2Group3++;
      else
      {
        //Error
        sMessage << "TestNormalProcessingRun3, timestep 1, found an unexpected " << "tree storm damage value.  X: " << fX
            << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
        FAIL() << sMessage.str();
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  EXPECT_EQ( 1000, iSp1Group1 );
  EXPECT_EQ( 1000, iSp2Group1 );
  EXPECT_EQ( 0, iSp1Group2 );
  EXPECT_EQ( 0, iSp2Group2 );
  EXPECT_EQ( 0, iSp1Group3 );
  EXPECT_EQ( 0, iSp2Group3 );




  //>>>>>>>>>>>>Separate out and only do cell 1, 1<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0.  Group 2: storm damage = 1000.  Group 3:
  //storm damage = 2000.
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  p_oAllTrees->StartOver();
  p_oTree = p_oAllTrees->NextTree();
  while ( p_oTree )
  {
    //Make sure this ain't no snag
    EXPECT_NE(clTreePopulation::snag, p_oTree->GetType());

    iSp = p_oTree->GetSpecies();

    //Get X and Y
    p_oTree->GetValue( p_oPop->GetXCode( iSp, p_oTree->GetType() ), & fX );
    p_oTree->GetValue( p_oPop->GetYCode( iSp, p_oTree->GetType() ), & fY );

    //Get storm damage counter
    p_oTree->GetValue( p_oPop->GetIntDataCode( "stm_dmg", iSp, p_oTree->GetType() ), & iStmDmgValue );

    if ( fX > 8 && fX < 16 && fY > 8 && fY < 16 )
    {

      //Get DBH
      p_oTree->GetValue( p_oPop->GetDbhCode( iSp, p_oTree->GetType() ), & fDiam );

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if ( fDiam < 6 )  EXPECT_EQ( 0, iStmDmgValue );
      else if ( 0 == iSp && 0 == iStmDmgValue ) iSp1Group1++;
      else if ( 1 == iSp && 0 == iStmDmgValue ) iSp2Group1++;
      else if ( 0 == iSp && 1000 == iStmDmgValue ) iSp1Group2++;
      else if ( 1 == iSp && 1000 == iStmDmgValue ) iSp2Group2++;
      else if ( 0 == iSp && 2000 == iStmDmgValue ) iSp1Group3++;
      else if ( 1 == iSp && 2000 == iStmDmgValue ) iSp2Group3++;
      else
      {
        //Error
        sMessage << "TestNormalProcessingRun3, timestep 1, found an unexpected " << "tree storm damage value.  X: " << fX
            << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
        FAIL() << sMessage.str();
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  //Validate the counts
  EXPECT_EQ( 0, iSp1Group1 );
  EXPECT_EQ( 0, iSp2Group1 );
  fExpected = 627.1;
  EXPECT_LT( fabs( fExpected - iSp1Group2 ) / fExpected, 0.1 );
  fExpected = 898.4;
  EXPECT_LT( fabs( fExpected - iSp2Group2 ) / fExpected, 0.1 );
  EXPECT_EQ( 0, iSp1Group3 );
  EXPECT_EQ( 0, iSp2Group3 );





  //>>>>>>>>>>>>Separate out and only do cell 1, 2<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0.  Group 2: storm damage = 1000.  Group 3:
  //storm damage = 2000.
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  p_oAllTrees->StartOver();
  p_oTree = p_oAllTrees->NextTree();
  while ( p_oTree )
  {
    //Make sure this ain't no snag
    EXPECT_NE(clTreePopulation::snag, p_oTree->GetType());

    iSp = p_oTree->GetSpecies();

    //Get X and Y
    p_oTree->GetValue( p_oPop->GetXCode( iSp, p_oTree->GetType() ), & fX );
    p_oTree->GetValue( p_oPop->GetYCode( iSp, p_oTree->GetType() ), & fY );

    //Get storm damage counter
    p_oTree->GetValue( p_oPop->GetIntDataCode( "stm_dmg", iSp, p_oTree->GetType() ), & iStmDmgValue );

    if ( fX > 8 && fX < 16 && fY > 16 && fY < 24 )
    {

      //Get DBH
      p_oTree->GetValue( p_oPop->GetDbhCode( iSp, p_oTree->GetType() ), & fDiam );

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if ( fDiam < 6 )  EXPECT_EQ( 0, iStmDmgValue );
      else if ( 0 == iSp && 0 == iStmDmgValue ) iSp1Group1++;
      else if ( 1 == iSp && 0 == iStmDmgValue ) iSp2Group1++;
      else if ( 0 == iSp && 1000 == iStmDmgValue ) iSp1Group2++;
      else if ( 1 == iSp && 1000 == iStmDmgValue ) iSp2Group2++;
      else if ( 0 == iSp && 2000 == iStmDmgValue ) iSp1Group3++;
      else if ( 1 == iSp && 2000 == iStmDmgValue ) iSp2Group3++;
      else
      {
        //Error
        sMessage << "TestNormalProcessingRun3, timestep 1, found an unexpected " << "tree storm damage value.  X: " << fX
            << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
        FAIL() << sMessage.str();
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  //Validate the counts
  EXPECT_EQ( 0, iSp1Group1 );
  EXPECT_EQ( 0, iSp2Group1 );
  EXPECT_EQ( 0, iSp1Group2 );
  EXPECT_EQ( 0, iSp2Group2 );
  fExpected = 960.3;
  EXPECT_LT( fabs( fExpected - iSp1Group3 ) / fExpected, 0.1 );
  fExpected = 729.0;
  EXPECT_LT( fabs( fExpected - iSp2Group3 ) / fExpected, 0.1 );
}

/////////////////////////////////////////////////////////////////////////////
// TestStormKillerRun3Timestep2()
/////////////////////////////////////////////////////////////////////////////
void TestStormKillerRun3Timestep2( clTreePopulation * p_oPop )
{
  using namespace std;
  clTreeSearch * p_oAllTrees;
  clTree * p_oTree;
  stringstream sMessage;
  float fX, fY, fDiam, fExpected;
  int iSp1Group1, iSp2Group1, iSp1Group2, iSp2Group2, iSp1Group3, iSp2Group3, iSp, iStmDmgValue;

  //Get all trees
  p_oAllTrees = p_oPop->Find( "all" );

  //>>>>>>>>>>>>Separate out and only do cell 0,0<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0.  Group 2: storm damage = 1001.  Group 3:
  //storm damage = 2001.
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  p_oTree = p_oAllTrees->NextTree();
  while ( p_oTree )
  {

    //Make sure this ain't no snag
    EXPECT_NE(clTreePopulation::snag, p_oTree->GetType());

    iSp = p_oTree->GetSpecies();

    //Get X and Y
    p_oTree->GetValue( p_oPop->GetXCode( iSp, p_oTree->GetType() ), & fX );
    p_oTree->GetValue( p_oPop->GetYCode( iSp, p_oTree->GetType() ), & fY );

    //Get storm damage counter
    p_oTree->GetValue( p_oPop->GetIntDataCode( "stm_dmg", iSp, p_oTree->GetType() ), & iStmDmgValue );

    if ( fX < 8 && fY < 8 )
    {
      //Get DBH
      p_oTree->GetValue( p_oPop->GetDbhCode( iSp, p_oTree->GetType() ), & fDiam );

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if ( fDiam < 6 )  EXPECT_EQ( 0, iStmDmgValue );
      else if ( 0 == iSp && 0 == iStmDmgValue ) iSp1Group1++;
      else if ( 1 == iSp && 0 == iStmDmgValue ) iSp2Group1++;
      else if ( 0 == iSp && 1001 == iStmDmgValue ) iSp1Group2++;
      else if ( 1 == iSp && 1001 == iStmDmgValue ) iSp2Group2++;
      else if ( 0 == iSp && 2001 == iStmDmgValue ) iSp1Group3++;
      else if ( 1 == iSp && 2001 == iStmDmgValue ) iSp2Group3++;
      else
      {
        //Error
        sMessage << "TestNormalProcessingRun3, timestep 2, found an unexpected " << "tree storm damage value.  X: " << fX
            << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
        FAIL() << sMessage.str();
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  //Validate the counts
  EXPECT_EQ( 1000, iSp1Group1 );
  EXPECT_EQ( 1000, iSp2Group1 );
  EXPECT_EQ( 0, iSp1Group2 );
  EXPECT_EQ( 0, iSp2Group2 );
  EXPECT_EQ( 0, iSp1Group3 );
  EXPECT_EQ( 0, iSp2Group3 );

  //>>>>>>>>>>>>Separate out and only do cell 0, 1<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0.  Group 2: storm damage = 1000.  Group 3:
  //storm damage = 2000.
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  p_oAllTrees->StartOver();
  p_oTree = p_oAllTrees->NextTree();
  while ( p_oTree )
  {
    //Make sure this ain't no snag
    EXPECT_NE(clTreePopulation::snag, p_oTree->GetType());

    iSp = p_oTree->GetSpecies();

    //Get X and Y
    p_oTree->GetValue( p_oPop->GetXCode( iSp, p_oTree->GetType() ), & fX );
    p_oTree->GetValue( p_oPop->GetYCode( iSp, p_oTree->GetType() ), & fY );

    //Get storm damage counter
    p_oTree->GetValue( p_oPop->GetIntDataCode( "stm_dmg", iSp, p_oTree->GetType() ), & iStmDmgValue );

    if ( fX < 8 && fY > 8 && fY < 16 )
    {

      //Get DBH
      p_oTree->GetValue( p_oPop->GetDbhCode( iSp, p_oTree->GetType() ), & fDiam );

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if ( fDiam < 6 )  EXPECT_EQ( 0, iStmDmgValue );
      else if ( 0 == iSp && 0 == iStmDmgValue ) iSp1Group1++;
      else if ( 1 == iSp && 0 == iStmDmgValue ) iSp2Group1++;
      else if ( 0 == iSp && 1001 == iStmDmgValue ) iSp1Group2++;
      else if ( 1 == iSp && 1001 == iStmDmgValue ) iSp2Group2++;
      else if ( 0 == iSp && 2001 == iStmDmgValue ) iSp1Group3++;
      else if ( 1 == iSp && 2001 == iStmDmgValue ) iSp2Group3++;
      else
      {
        //Error
        sMessage << "TestNormalProcessingRun3, timestep 2, found an unexpected " << "tree storm damage value.  X: " << fX
            << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
        FAIL() << sMessage.str();
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  //Validate the counts
  EXPECT_EQ( 0, iSp1Group1 );
  EXPECT_EQ( 0, iSp2Group1 );
  fExpected = 574.4;
  EXPECT_LT( fabs( fExpected - iSp1Group2 ) / fExpected, 0.1 );
  fExpected = 850.6;
  EXPECT_LT( fabs( fExpected - iSp2Group2 ) / fExpected, 0.1 );
  EXPECT_EQ( 0, iSp1Group3 );
  EXPECT_EQ( 0, iSp2Group3 );





  //>>>>>>>>>>>>Separate out and only do cell 0, 2<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0.  Group 2: storm damage = 1000.  Group 3:
  //storm damage = 2000.
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  p_oAllTrees->StartOver();
  p_oTree = p_oAllTrees->NextTree();
  while ( p_oTree )
  {
    //Make sure this ain't no snag
    EXPECT_NE(clTreePopulation::snag, p_oTree->GetType());

    iSp = p_oTree->GetSpecies();

    //Get X and Y
    p_oTree->GetValue( p_oPop->GetXCode( iSp, p_oTree->GetType() ), & fX );
    p_oTree->GetValue( p_oPop->GetYCode( iSp, p_oTree->GetType() ), & fY );

    //Get storm damage counter
    p_oTree->GetValue( p_oPop->GetIntDataCode( "stm_dmg", iSp, p_oTree->GetType() ), & iStmDmgValue );

    if ( fX < 8 && fY > 16 && fY < 24 )
    {

      //Get DBH
      p_oTree->GetValue( p_oPop->GetDbhCode( iSp, p_oTree->GetType() ), & fDiam );

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if ( fDiam < 6 )  EXPECT_EQ( 0, iStmDmgValue );
      else if ( 0 == iSp && 0 == iStmDmgValue ) iSp1Group1++;
      else if ( 1 == iSp && 0 == iStmDmgValue ) iSp2Group1++;
      else if ( 0 == iSp && 1001 == iStmDmgValue ) iSp1Group2++;
      else if ( 1 == iSp && 1001 == iStmDmgValue ) iSp2Group2++;
      else if ( 0 == iSp && 2001 == iStmDmgValue ) iSp1Group3++;
      else if ( 1 == iSp && 2001 == iStmDmgValue ) iSp2Group3++;
      else
      {
        //Error
        sMessage << "TestNormalProcessingRun3, timestep 2, found an unexpected " << "tree storm damage value.  X: " << fX
            << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
        FAIL() << sMessage.str();
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  //Validate the counts
  EXPECT_EQ( 0, iSp1Group1 );
  EXPECT_EQ( 0, iSp2Group1 );
  EXPECT_EQ( 0, iSp1Group2 );
  EXPECT_EQ( 0, iSp2Group2 );
  fExpected = 809.9;
  EXPECT_LT( fabs( fExpected - iSp1Group3 ) / fExpected, 0.1 );
  fExpected = 472.5;
  EXPECT_LT( fabs( fExpected - iSp2Group3 ) / fExpected, 0.1 );




  //>>>>>>>>>>>>Separate out and only do cell 1, 0<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0.  Group 2: storm damage = 1000.  Group 3:
  //storm damage = 2000.
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  p_oAllTrees->StartOver();
  p_oTree = p_oAllTrees->NextTree();
  while ( p_oTree )
  {
    //Make sure this ain't no snag
    EXPECT_NE(clTreePopulation::snag, p_oTree->GetType());

    iSp = p_oTree->GetSpecies();

    //Get X and Y
    p_oTree->GetValue( p_oPop->GetXCode( iSp, p_oTree->GetType() ), & fX );
    p_oTree->GetValue( p_oPop->GetYCode( iSp, p_oTree->GetType() ), & fY );

    //Get storm damage counter
    p_oTree->GetValue( p_oPop->GetIntDataCode( "stm_dmg", iSp, p_oTree->GetType() ), & iStmDmgValue );

    if ( fX > 8 && fX < 16 && fY < 8 )
    {

      //Get DBH
      p_oTree->GetValue( p_oPop->GetDbhCode( iSp, p_oTree->GetType() ), & fDiam );

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if ( fDiam < 6 )  EXPECT_EQ( 0, iStmDmgValue );
      else if ( 0 == iSp && 0 == iStmDmgValue ) iSp1Group1++;
      else if ( 1 == iSp && 0 == iStmDmgValue ) iSp2Group1++;
      else if ( 0 == iSp && 1001 == iStmDmgValue ) iSp1Group2++;
      else if ( 1 == iSp && 1001 == iStmDmgValue ) iSp2Group2++;
      else if ( 0 == iSp && 2001 == iStmDmgValue ) iSp1Group3++;
      else if ( 1 == iSp && 2001 == iStmDmgValue ) iSp2Group3++;
      else
      {
        //Error
        sMessage << "TestNormalProcessingRun3, timestep 2, found an unexpected " << "tree storm damage value.  X: " << fX
            << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
        FAIL() << sMessage.str();
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  EXPECT_EQ( 1000, iSp1Group1 );
  EXPECT_EQ( 1000, iSp2Group1 );
  EXPECT_EQ( 0, iSp1Group2 );
  EXPECT_EQ( 0, iSp2Group2 );
  EXPECT_EQ( 0, iSp1Group3 );
  EXPECT_EQ( 0, iSp2Group3 );




  //>>>>>>>>>>>>Separate out and only do cell 1, 1<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0.  Group 2: storm damage = 1000.  Group 3:
  //storm damage = 2000.
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  p_oAllTrees->StartOver();
  p_oTree = p_oAllTrees->NextTree();
  while ( p_oTree )
  {
    //Make sure this ain't no snag
    EXPECT_NE(clTreePopulation::snag, p_oTree->GetType());

    iSp = p_oTree->GetSpecies();

    //Get X and Y
    p_oTree->GetValue( p_oPop->GetXCode( iSp, p_oTree->GetType() ), & fX );
    p_oTree->GetValue( p_oPop->GetYCode( iSp, p_oTree->GetType() ), & fY );

    //Get storm damage counter
    p_oTree->GetValue( p_oPop->GetIntDataCode( "stm_dmg", iSp, p_oTree->GetType() ), & iStmDmgValue );

    if ( fX > 8 && fX < 16 && fY > 8 && fY < 16 )
    {

      //Get DBH
      p_oTree->GetValue( p_oPop->GetDbhCode( iSp, p_oTree->GetType() ), & fDiam );

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if ( fDiam < 6 )  EXPECT_EQ( 0, iStmDmgValue );
      else if ( 0 == iSp && 0 == iStmDmgValue ) iSp1Group1++;
      else if ( 1 == iSp && 0 == iStmDmgValue ) iSp2Group1++;
      else if ( 0 == iSp && 1001 == iStmDmgValue ) iSp1Group2++;
      else if ( 1 == iSp && 1001 == iStmDmgValue ) iSp2Group2++;
      else if ( 0 == iSp && 2001 == iStmDmgValue ) iSp1Group3++;
      else if ( 1 == iSp && 2001 == iStmDmgValue ) iSp2Group3++;
      else
      {
        //Error
        sMessage << "TestNormalProcessingRun3, timestep 2, found an unexpected " << "tree storm damage value.  X: " << fX
            << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
        FAIL() << sMessage.str();
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  //Validate the counts
  EXPECT_EQ( 0, iSp1Group1 );
  EXPECT_EQ( 0, iSp2Group1 );
  fExpected = 627.1;
  EXPECT_LT( fabs( fExpected - iSp1Group2 ) / fExpected, 0.1 );
  fExpected = 898.4;
  EXPECT_LT( fabs( fExpected - iSp2Group2 ) / fExpected, 0.1 );
  EXPECT_EQ( 0, iSp1Group3 );
  EXPECT_EQ( 0, iSp2Group3 );





  //>>>>>>>>>>>>Separate out and only do cell 1, 2<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0.  Group 2: storm damage = 1000.  Group 3:
  //storm damage = 2000.
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  p_oAllTrees->StartOver();
  p_oTree = p_oAllTrees->NextTree();
  while ( p_oTree )
  {
    //Make sure this ain't no snag
    EXPECT_NE(clTreePopulation::snag, p_oTree->GetType());

    iSp = p_oTree->GetSpecies();

    //Get X and Y
    p_oTree->GetValue( p_oPop->GetXCode( iSp, p_oTree->GetType() ), & fX );
    p_oTree->GetValue( p_oPop->GetYCode( iSp, p_oTree->GetType() ), & fY );

    //Get storm damage counter
    p_oTree->GetValue( p_oPop->GetIntDataCode( "stm_dmg", iSp, p_oTree->GetType() ), & iStmDmgValue );

    if ( fX > 8 && fX < 16 && fY > 16 && fY < 24 )
    {

      //Get DBH
      p_oTree->GetValue( p_oPop->GetDbhCode( iSp, p_oTree->GetType() ), & fDiam );

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if ( fDiam < 6 )  EXPECT_EQ( 0, iStmDmgValue );
      else if ( 0 == iSp && 0 == iStmDmgValue ) iSp1Group1++;
      else if ( 1 == iSp && 0 == iStmDmgValue ) iSp2Group1++;
      else if ( 0 == iSp && 1001 == iStmDmgValue ) iSp1Group2++;
      else if ( 1 == iSp && 1001 == iStmDmgValue ) iSp2Group2++;
      else if ( 0 == iSp && 2001 == iStmDmgValue ) iSp1Group3++;
      else if ( 1 == iSp && 2001 == iStmDmgValue ) iSp2Group3++;
      else
      {
        //Error
        sMessage << "TestNormalProcessingRun3, timestep 2, found an unexpected " << "tree storm damage value.  X: " << fX
            << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
        FAIL() << sMessage.str();
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  //Validate the counts
  EXPECT_EQ( 0, iSp1Group1 );
  EXPECT_EQ( 0, iSp2Group1 );
  EXPECT_EQ( 0, iSp1Group2 );
  EXPECT_EQ( 0, iSp2Group2 );
  fExpected = 960.3;
  EXPECT_LT( fabs( fExpected - iSp1Group3 ) / fExpected, 0.1 );
  fExpected = 729.0;
  EXPECT_LT( fabs( fExpected - iSp2Group3 ) / fExpected, 0.1 );
}

/////////////////////////////////////////////////////////////////////////////
// TestStormKillerRun3Timestep3()
/////////////////////////////////////////////////////////////////////////////
void TestStormKillerRun3Timestep3( clTreePopulation * p_oPop )
{
  using namespace std;
  clTreeSearch * p_oAllTrees;
  clTree * p_oTree;
  stringstream sMessage;
  float fX, fY, fDiam, fExpected;
  int iSp1Group1, iSp2Group1, iSp1Group2, iSp2Group2, iSp1Group3, iSp2Group3, iSp, iStmDmgValue;

  //Get all trees
  p_oAllTrees = p_oPop->Find( "all" );

  //>>>>>>>>>>>>Separate out and only do cell 0,0<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0.  Group 2: storm damage = 1000.  Group 3:
  //storm damage = 2000.
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  p_oTree = p_oAllTrees->NextTree();
  while ( p_oTree )
  {

    //Make sure this ain't no snag
    EXPECT_NE(clTreePopulation::snag, p_oTree->GetType());

    iSp = p_oTree->GetSpecies();

    //Get X and Y
    p_oTree->GetValue( p_oPop->GetXCode( iSp, p_oTree->GetType() ), & fX );
    p_oTree->GetValue( p_oPop->GetYCode( iSp, p_oTree->GetType() ), & fY );

    //Get storm damage counter
    p_oTree->GetValue( p_oPop->GetIntDataCode( "stm_dmg", iSp, p_oTree->GetType() ), & iStmDmgValue );

    if ( fX < 8 && fY < 8 )
    {
      //Get DBH
      p_oTree->GetValue( p_oPop->GetDbhCode( iSp, p_oTree->GetType() ), & fDiam );

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if ( fDiam < 6 )  EXPECT_EQ( 0, iStmDmgValue );
      else if ( 0 == iSp && 0 == iStmDmgValue ) iSp1Group1++;
      else if ( 1 == iSp && 0 == iStmDmgValue ) iSp2Group1++;
      else if ( 0 == iSp && 1002 == iStmDmgValue ) iSp1Group2++;
      else if ( 1 == iSp && 1002 == iStmDmgValue ) iSp2Group2++;
      else if ( 0 == iSp && 2002 == iStmDmgValue ) iSp1Group3++;
      else if ( 1 == iSp && 2002 == iStmDmgValue ) iSp2Group3++;
      else
      {
        //Error
        sMessage << "TestNormalProcessingRun3, timestep 1, found an unexpected " << "tree storm damage value.  X: " << fX
            << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
        FAIL() << sMessage.str();
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  //Validate the counts
  EXPECT_EQ( 1000, iSp1Group1 );
  EXPECT_EQ( 1000, iSp2Group1 );
  EXPECT_EQ( 0, iSp1Group2 );
  EXPECT_EQ( 0, iSp2Group2 );
  EXPECT_EQ( 0, iSp1Group3 );
  EXPECT_EQ( 0, iSp2Group3 );

  //>>>>>>>>>>>>Separate out and only do cell 0, 1<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0.  Group 2: storm damage = 1000.  Group 3:
  //storm damage = 2000.
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  p_oAllTrees->StartOver();
  p_oTree = p_oAllTrees->NextTree();
  while ( p_oTree )
  {
    //Make sure this ain't no snag
    EXPECT_NE(clTreePopulation::snag, p_oTree->GetType());

    iSp = p_oTree->GetSpecies();

    //Get X and Y
    p_oTree->GetValue( p_oPop->GetXCode( iSp, p_oTree->GetType() ), & fX );
    p_oTree->GetValue( p_oPop->GetYCode( iSp, p_oTree->GetType() ), & fY );

    //Get storm damage counter
    p_oTree->GetValue( p_oPop->GetIntDataCode( "stm_dmg", iSp, p_oTree->GetType() ), & iStmDmgValue );

    if ( fX < 8 && fY > 8 && fY < 16 )
    {

      //Get DBH
      p_oTree->GetValue( p_oPop->GetDbhCode( iSp, p_oTree->GetType() ), & fDiam );

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if ( fDiam < 6 )  EXPECT_EQ( 0, iStmDmgValue );
      else if ( 0 == iSp && 0 == iStmDmgValue ) iSp1Group1++;
      else if ( 1 == iSp && 0 == iStmDmgValue ) iSp2Group1++;
      else if ( 0 == iSp && 1002 == iStmDmgValue ) iSp1Group2++;
      else if ( 1 == iSp && 1002 == iStmDmgValue ) iSp2Group2++;
      else if ( 0 == iSp && 2002 == iStmDmgValue ) iSp1Group3++;
      else if ( 1 == iSp && 2002 == iStmDmgValue ) iSp2Group3++;
      else
      {
        //Error
        sMessage << "TestNormalProcessingRun3, timestep 1, found an unexpected " << "tree storm damage value.  X: " << fX
            << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
        FAIL() << sMessage.str();
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  //Validate the counts
  EXPECT_EQ( 0, iSp1Group1 );
  EXPECT_EQ( 0, iSp2Group1 );
  fExpected = 574.4;
  EXPECT_LT( fabs( fExpected - iSp1Group2 ) / fExpected, 0.1 );
  fExpected = 850.6;
  EXPECT_LT( fabs( fExpected - iSp2Group2 ) / fExpected, 0.1 );
  EXPECT_EQ( 0, iSp1Group3 );
  EXPECT_EQ( 0, iSp2Group3 );





  //>>>>>>>>>>>>Separate out and only do cell 0, 2<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0.  Group 2: storm damage = 1000.  Group 3:
  //storm damage = 2000.
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  p_oAllTrees->StartOver();
  p_oTree = p_oAllTrees->NextTree();
  while ( p_oTree )
  {
    //Make sure this ain't no snag
    EXPECT_NE(clTreePopulation::snag, p_oTree->GetType());

    iSp = p_oTree->GetSpecies();

    //Get X and Y
    p_oTree->GetValue( p_oPop->GetXCode( iSp, p_oTree->GetType() ), & fX );
    p_oTree->GetValue( p_oPop->GetYCode( iSp, p_oTree->GetType() ), & fY );

    //Get storm damage counter
    p_oTree->GetValue( p_oPop->GetIntDataCode( "stm_dmg", iSp, p_oTree->GetType() ), & iStmDmgValue );

    if ( fX < 8 && fY > 16 && fY < 24 )
    {

      //Get DBH
      p_oTree->GetValue( p_oPop->GetDbhCode( iSp, p_oTree->GetType() ), & fDiam );

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if ( fDiam < 6 )  EXPECT_EQ( 0, iStmDmgValue );
      else if ( 0 == iSp && 0 == iStmDmgValue ) iSp1Group1++;
      else if ( 1 == iSp && 0 == iStmDmgValue ) iSp2Group1++;
      else if ( 0 == iSp && 1002 == iStmDmgValue ) iSp1Group2++;
      else if ( 1 == iSp && 1002 == iStmDmgValue ) iSp2Group2++;
      else if ( 0 == iSp && 2002 == iStmDmgValue ) iSp1Group3++;
      else if ( 1 == iSp && 2002 == iStmDmgValue ) iSp2Group3++;
      else
      {
        //Error
        sMessage << "TestNormalProcessingRun3, timestep 1, found an unexpected " << "tree storm damage value.  X: " << fX
            << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
        FAIL() << sMessage.str();
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  //Validate the counts
  EXPECT_EQ( 0, iSp1Group1 );
  EXPECT_EQ( 0, iSp2Group1 );
  EXPECT_EQ( 0, iSp1Group2 );
  EXPECT_EQ( 0, iSp2Group2 );
  fExpected = 809.9;
  EXPECT_LT( fabs( fExpected - iSp1Group3 ) / fExpected, 0.1 );
  fExpected = 472.5;
  EXPECT_LT( fabs( fExpected - iSp2Group3 ) / fExpected, 0.1 );




  //>>>>>>>>>>>>Separate out and only do cell 1, 0<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0.  Group 2: storm damage = 1000.  Group 3:
  //storm damage = 2000.
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  p_oAllTrees->StartOver();
  p_oTree = p_oAllTrees->NextTree();
  while ( p_oTree )
  {
    //Make sure this ain't no snag
    EXPECT_NE(clTreePopulation::snag, p_oTree->GetType());

    iSp = p_oTree->GetSpecies();

    //Get X and Y
    p_oTree->GetValue( p_oPop->GetXCode( iSp, p_oTree->GetType() ), & fX );
    p_oTree->GetValue( p_oPop->GetYCode( iSp, p_oTree->GetType() ), & fY );

    //Get storm damage counter
    p_oTree->GetValue( p_oPop->GetIntDataCode( "stm_dmg", iSp, p_oTree->GetType() ), & iStmDmgValue );

    if ( fX > 8 && fX < 16 && fY < 8 )
    {

      //Get DBH
      p_oTree->GetValue( p_oPop->GetDbhCode( iSp, p_oTree->GetType() ), & fDiam );

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if ( fDiam < 6 )  EXPECT_EQ( 0, iStmDmgValue );
      else if ( 0 == iSp && 0 == iStmDmgValue ) iSp1Group1++;
      else if ( 1 == iSp && 0 == iStmDmgValue ) iSp2Group1++;
      else if ( 0 == iSp && 1002 == iStmDmgValue ) iSp1Group2++;
      else if ( 1 == iSp && 1002 == iStmDmgValue ) iSp2Group2++;
      else if ( 0 == iSp && 2002 == iStmDmgValue ) iSp1Group3++;
      else if ( 1 == iSp && 2002 == iStmDmgValue ) iSp2Group3++;
      else
      {
        //Error
        sMessage << "TestNormalProcessingRun3, timestep 1, found an unexpected " << "tree storm damage value.  X: " << fX
            << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
        FAIL() << sMessage.str();
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  EXPECT_EQ( 1000, iSp1Group1 );
  EXPECT_EQ( 1000, iSp2Group1 );
  EXPECT_EQ( 0, iSp1Group2 );
  EXPECT_EQ( 0, iSp2Group2 );
  EXPECT_EQ( 0, iSp1Group3 );
  EXPECT_EQ( 0, iSp2Group3 );




  //>>>>>>>>>>>>Separate out and only do cell 1, 1<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0.  Group 2: storm damage = 1000.  Group 3:
  //storm damage = 2000.
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  p_oAllTrees->StartOver();
  p_oTree = p_oAllTrees->NextTree();
  while ( p_oTree )
  {
    //Make sure this ain't no snag
    EXPECT_NE(clTreePopulation::snag, p_oTree->GetType());

    iSp = p_oTree->GetSpecies();

    //Get X and Y
    p_oTree->GetValue( p_oPop->GetXCode( iSp, p_oTree->GetType() ), & fX );
    p_oTree->GetValue( p_oPop->GetYCode( iSp, p_oTree->GetType() ), & fY );

    //Get storm damage counter
    p_oTree->GetValue( p_oPop->GetIntDataCode( "stm_dmg", iSp, p_oTree->GetType() ), & iStmDmgValue );

    if ( fX > 8 && fX < 16 && fY > 8 && fY < 16 )
    {

      //Get DBH
      p_oTree->GetValue( p_oPop->GetDbhCode( iSp, p_oTree->GetType() ), & fDiam );

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if ( fDiam < 6 )  EXPECT_EQ( 0, iStmDmgValue );
      else if ( 0 == iSp && 0 == iStmDmgValue ) iSp1Group1++;
      else if ( 1 == iSp && 0 == iStmDmgValue ) iSp2Group1++;
      else if ( 0 == iSp && 1002 == iStmDmgValue ) iSp1Group2++;
      else if ( 1 == iSp && 1002 == iStmDmgValue ) iSp2Group2++;
      else if ( 0 == iSp && 2002 == iStmDmgValue ) iSp1Group3++;
      else if ( 1 == iSp && 2002 == iStmDmgValue ) iSp2Group3++;
      else
      {
        //Error
        sMessage << "TestNormalProcessingRun3, timestep 1, found an unexpected " << "tree storm damage value.  X: " << fX
            << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
        FAIL() << sMessage.str();
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  //Validate the counts
  EXPECT_EQ( 0, iSp1Group1 );
  EXPECT_EQ( 0, iSp2Group1 );
  fExpected = 627.1;
  EXPECT_LT( fabs( fExpected - iSp1Group2 ) / fExpected, 0.1 );
  fExpected = 898.4;
  EXPECT_LT( fabs( fExpected - iSp2Group2 ) / fExpected, 0.1 );
  EXPECT_EQ( 0, iSp1Group3 );
  EXPECT_EQ( 0, iSp2Group3 );





  //>>>>>>>>>>>>Separate out and only do cell 1, 2<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0.  Group 2: storm damage = 1000.  Group 3:
  //storm damage = 2000.
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  p_oAllTrees->StartOver();
  p_oTree = p_oAllTrees->NextTree();
  while ( p_oTree )
  {
    //Make sure this ain't no snag
    EXPECT_NE(clTreePopulation::snag, p_oTree->GetType());

    iSp = p_oTree->GetSpecies();

    //Get X and Y
    p_oTree->GetValue( p_oPop->GetXCode( iSp, p_oTree->GetType() ), & fX );
    p_oTree->GetValue( p_oPop->GetYCode( iSp, p_oTree->GetType() ), & fY );

    //Get storm damage counter
    p_oTree->GetValue( p_oPop->GetIntDataCode( "stm_dmg", iSp, p_oTree->GetType() ), & iStmDmgValue );

    if ( fX > 8 && fX < 16 && fY > 16 && fY < 24 )
    {

      //Get DBH
      p_oTree->GetValue( p_oPop->GetDbhCode( iSp, p_oTree->GetType() ), & fDiam );

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if ( fDiam < 6 )  EXPECT_EQ( 0, iStmDmgValue );
      else if ( 0 == iSp && 0 == iStmDmgValue ) iSp1Group1++;
      else if ( 1 == iSp && 0 == iStmDmgValue ) iSp2Group1++;
      else if ( 0 == iSp && 1002 == iStmDmgValue ) iSp1Group2++;
      else if ( 1 == iSp && 1002 == iStmDmgValue ) iSp2Group2++;
      else if ( 0 == iSp && 2002 == iStmDmgValue ) iSp1Group3++;
      else if ( 1 == iSp && 2002 == iStmDmgValue ) iSp2Group3++;
      else
      {
        //Error
        sMessage << "TestNormalProcessingRun3, timestep 1, found an unexpected " << "tree storm damage value.  X: " << fX
            << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
        FAIL() << sMessage.str();
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  //Validate the counts
  EXPECT_EQ( 0, iSp1Group1 );
  EXPECT_EQ( 0, iSp2Group1 );
  EXPECT_EQ( 0, iSp1Group2 );
  EXPECT_EQ( 0, iSp2Group2 );
  fExpected = 960.3;
  EXPECT_LT( fabs( fExpected - iSp1Group3 ) / fExpected, 0.1 );
  fExpected = 729.0;
  EXPECT_LT( fabs( fExpected - iSp2Group3 ) / fExpected, 0.1 );
}

/////////////////////////////////////////////////////////////////////////////
// TestStormKillerRun3Timestep4()
/////////////////////////////////////////////////////////////////////////////
void TestStormKillerRun3Timestep4( clTreePopulation * p_oPop )
{
  using namespace std;
  clTreeSearch * p_oAllTrees;
  clTree * p_oTree;
  stringstream sMessage;
  float fX, fY, fDiam, fExpected;
  int iSp1Group1, iSp2Group1, iSp1Group2, iSp2Group2, iSp1Group3, iSp2Group3, iSp, iStmDmgValue;

  //Get all trees
  p_oAllTrees = p_oPop->Find( "all" );

  //>>>>>>>>>>>>Separate out and only do cell 0,0<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0.  Group 2: storm damage = 1000.  Group 3:
  //storm damage = 2000.
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  p_oTree = p_oAllTrees->NextTree();
  while ( p_oTree )
  {

    //Make sure this ain't no snag
    EXPECT_NE(clTreePopulation::snag, p_oTree->GetType());

    iSp = p_oTree->GetSpecies();

    //Get X and Y
    p_oTree->GetValue( p_oPop->GetXCode( iSp, p_oTree->GetType() ), & fX );
    p_oTree->GetValue( p_oPop->GetYCode( iSp, p_oTree->GetType() ), & fY );

    //Get storm damage counter
    p_oTree->GetValue( p_oPop->GetIntDataCode( "stm_dmg", iSp, p_oTree->GetType() ), & iStmDmgValue );

    if ( fX < 8 && fY < 8 )
    {
      //Get DBH
      p_oTree->GetValue( p_oPop->GetDbhCode( iSp, p_oTree->GetType() ), & fDiam );

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if ( fDiam < 6 )  EXPECT_EQ( 0, iStmDmgValue );
      else if ( 0 == iSp && 0 == iStmDmgValue ) iSp1Group1++;
      else if ( 1 == iSp && 0 == iStmDmgValue ) iSp2Group1++;
      else if ( 0 == iSp && 1003 == iStmDmgValue ) iSp1Group2++;
      else if ( 1 == iSp && 1003 == iStmDmgValue ) iSp2Group2++;
      else if ( 0 == iSp && 2003 == iStmDmgValue ) iSp1Group3++;
      else if ( 1 == iSp && 2003 == iStmDmgValue ) iSp2Group3++;
      else
      {
        //Error
        sMessage << "TestNormalProcessingRun3, timestep 1, found an unexpected " << "tree storm damage value.  X: " << fX
            << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
        FAIL() << sMessage.str();
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  //Validate the counts
  EXPECT_EQ( 1000, iSp1Group1 );
  EXPECT_EQ( 1000, iSp2Group1 );
  EXPECT_EQ( 0, iSp1Group2 );
  EXPECT_EQ( 0, iSp2Group2 );
  EXPECT_EQ( 0, iSp1Group3 );
  EXPECT_EQ( 0, iSp2Group3 );

  //>>>>>>>>>>>>Separate out and only do cell 0, 1<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0.  Group 2: storm damage = 1000.  Group 3:
  //storm damage = 2000.
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  p_oAllTrees->StartOver();
  p_oTree = p_oAllTrees->NextTree();
  while ( p_oTree )
  {
    //Make sure this ain't no snag
    EXPECT_NE(clTreePopulation::snag, p_oTree->GetType());

    iSp = p_oTree->GetSpecies();

    //Get X and Y
    p_oTree->GetValue( p_oPop->GetXCode( iSp, p_oTree->GetType() ), & fX );
    p_oTree->GetValue( p_oPop->GetYCode( iSp, p_oTree->GetType() ), & fY );

    //Get storm damage counter
    p_oTree->GetValue( p_oPop->GetIntDataCode( "stm_dmg", iSp, p_oTree->GetType() ), & iStmDmgValue );

    if ( fX < 8 && fY > 8 && fY < 16 )
    {

      //Get DBH
      p_oTree->GetValue( p_oPop->GetDbhCode( iSp, p_oTree->GetType() ), & fDiam );

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if ( fDiam < 6 )  EXPECT_EQ( 0, iStmDmgValue );
      else if ( 0 == iSp && 0 == iStmDmgValue ) iSp1Group1++;
      else if ( 1 == iSp && 0 == iStmDmgValue ) iSp2Group1++;
      else if ( 0 == iSp && 1003 == iStmDmgValue ) iSp1Group2++;
      else if ( 1 == iSp && 1003 == iStmDmgValue ) iSp2Group2++;
      else if ( 0 == iSp && 2003 == iStmDmgValue ) iSp1Group3++;
      else if ( 1 == iSp && 2003 == iStmDmgValue ) iSp2Group3++;
      else
      {
        //Error
        sMessage << "TestNormalProcessingRun3, timestep 1, found an unexpected " << "tree storm damage value.  X: " << fX
            << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
        FAIL() << sMessage.str();
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  //Validate the counts
  EXPECT_EQ( 0, iSp1Group1 );
  EXPECT_EQ( 0, iSp2Group1 );
  fExpected = 574.4;
  EXPECT_LT( fabs( fExpected - iSp1Group2 ) / fExpected, 0.1 );
  fExpected = 850.6;
  EXPECT_LT( fabs( fExpected - iSp2Group2 ) / fExpected, 0.1 );
  EXPECT_EQ( 0, iSp1Group3 );
  EXPECT_EQ( 0, iSp2Group3 );





  //>>>>>>>>>>>>Separate out and only do cell 0, 2<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0.  Group 2: storm damage = 1000.  Group 3:
  //storm damage = 2000.
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  p_oAllTrees->StartOver();
  p_oTree = p_oAllTrees->NextTree();
  while ( p_oTree )
  {
    //Make sure this ain't no snag
    EXPECT_NE(clTreePopulation::snag, p_oTree->GetType());

    iSp = p_oTree->GetSpecies();

    //Get X and Y
    p_oTree->GetValue( p_oPop->GetXCode( iSp, p_oTree->GetType() ), & fX );
    p_oTree->GetValue( p_oPop->GetYCode( iSp, p_oTree->GetType() ), & fY );

    //Get storm damage counter
    p_oTree->GetValue( p_oPop->GetIntDataCode( "stm_dmg", iSp, p_oTree->GetType() ), & iStmDmgValue );

    if ( fX < 8 && fY > 16 && fY < 24 )
    {

      //Get DBH
      p_oTree->GetValue( p_oPop->GetDbhCode( iSp, p_oTree->GetType() ), & fDiam );

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if ( fDiam < 6 )  EXPECT_EQ( 0, iStmDmgValue );
      else if ( 0 == iSp && 0 == iStmDmgValue ) iSp1Group1++;
      else if ( 1 == iSp && 0 == iStmDmgValue ) iSp2Group1++;
      else if ( 0 == iSp && 1003 == iStmDmgValue ) iSp1Group2++;
      else if ( 1 == iSp && 1003 == iStmDmgValue ) iSp2Group2++;
      else if ( 0 == iSp && 2003 == iStmDmgValue ) iSp1Group3++;
      else if ( 1 == iSp && 2003 == iStmDmgValue ) iSp2Group3++;
      else
      {
        //Error
        sMessage << "TestNormalProcessingRun3, timestep 1, found an unexpected " << "tree storm damage value.  X: " << fX
            << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
        FAIL() << sMessage.str();
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  //Validate the counts
  EXPECT_EQ( 0, iSp1Group1 );
  EXPECT_EQ( 0, iSp2Group1 );
  EXPECT_EQ( 0, iSp1Group2 );
  EXPECT_EQ( 0, iSp2Group2 );
  fExpected = 809.9;
  EXPECT_LT( fabs( fExpected - iSp1Group3 ) / fExpected, 0.1 );
  fExpected = 472.5;
  EXPECT_LT( fabs( fExpected - iSp2Group3 ) / fExpected, 0.1 );




  //>>>>>>>>>>>>Separate out and only do cell 1, 0<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0.  Group 2: storm damage = 1000.  Group 3:
  //storm damage = 2000.
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  p_oAllTrees->StartOver();
  p_oTree = p_oAllTrees->NextTree();
  while ( p_oTree )
  {
    //Make sure this ain't no snag
    EXPECT_NE(clTreePopulation::snag, p_oTree->GetType());

    iSp = p_oTree->GetSpecies();

    //Get X and Y
    p_oTree->GetValue( p_oPop->GetXCode( iSp, p_oTree->GetType() ), & fX );
    p_oTree->GetValue( p_oPop->GetYCode( iSp, p_oTree->GetType() ), & fY );

    //Get storm damage counter
    p_oTree->GetValue( p_oPop->GetIntDataCode( "stm_dmg", iSp, p_oTree->GetType() ), & iStmDmgValue );

    if ( fX > 8 && fX < 16 && fY < 8 )
    {

      //Get DBH
      p_oTree->GetValue( p_oPop->GetDbhCode( iSp, p_oTree->GetType() ), & fDiam );

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if ( fDiam < 6 )  EXPECT_EQ( 0, iStmDmgValue );
      else if ( 0 == iSp && 0 == iStmDmgValue ) iSp1Group1++;
      else if ( 1 == iSp && 0 == iStmDmgValue ) iSp2Group1++;
      else if ( 0 == iSp && 1003 == iStmDmgValue ) iSp1Group2++;
      else if ( 1 == iSp && 1003 == iStmDmgValue ) iSp2Group2++;
      else if ( 0 == iSp && 2003 == iStmDmgValue ) iSp1Group3++;
      else if ( 1 == iSp && 2003 == iStmDmgValue ) iSp2Group3++;
      else
      {
        //Error
        sMessage << "TestNormalProcessingRun3, timestep 1, found an unexpected " << "tree storm damage value.  X: " << fX
            << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
        FAIL() << sMessage.str();
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  EXPECT_EQ( 1000, iSp1Group1 );
  EXPECT_EQ( 1000, iSp2Group1 );
  EXPECT_EQ( 0, iSp1Group2 );
  EXPECT_EQ( 0, iSp2Group2 );
  EXPECT_EQ( 0, iSp1Group3 );
  EXPECT_EQ( 0, iSp2Group3 );




  //>>>>>>>>>>>>Separate out and only do cell 1, 1<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0.  Group 2: storm damage = 1000.  Group 3:
  //storm damage = 2000.
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  p_oAllTrees->StartOver();
  p_oTree = p_oAllTrees->NextTree();
  while ( p_oTree )
  {
    //Make sure this ain't no snag
    EXPECT_NE(clTreePopulation::snag, p_oTree->GetType());

    iSp = p_oTree->GetSpecies();

    //Get X and Y
    p_oTree->GetValue( p_oPop->GetXCode( iSp, p_oTree->GetType() ), & fX );
    p_oTree->GetValue( p_oPop->GetYCode( iSp, p_oTree->GetType() ), & fY );

    //Get storm damage counter
    p_oTree->GetValue( p_oPop->GetIntDataCode( "stm_dmg", iSp, p_oTree->GetType() ), & iStmDmgValue );

    if ( fX > 8 && fX < 16 && fY > 8 && fY < 16 )
    {

      //Get DBH
      p_oTree->GetValue( p_oPop->GetDbhCode( iSp, p_oTree->GetType() ), & fDiam );

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if ( fDiam < 6 )  EXPECT_EQ( 0, iStmDmgValue );
      else if ( 0 == iSp && 0 == iStmDmgValue ) iSp1Group1++;
      else if ( 1 == iSp && 0 == iStmDmgValue ) iSp2Group1++;
      else if ( 0 == iSp && 1003 == iStmDmgValue ) iSp1Group2++;
      else if ( 1 == iSp && 1003 == iStmDmgValue ) iSp2Group2++;
      else if ( 0 == iSp && 2003 == iStmDmgValue ) iSp1Group3++;
      else if ( 1 == iSp && 2003 == iStmDmgValue ) iSp2Group3++;
      else
      {
        //Error
        sMessage << "TestNormalProcessingRun3, timestep 1, found an unexpected " << "tree storm damage value.  X: " << fX
            << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
        FAIL() << sMessage.str();
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  //Validate the counts
  EXPECT_EQ( 0, iSp1Group1 );
  EXPECT_EQ( 0, iSp2Group1 );
  fExpected = 627.1;
  EXPECT_LT( fabs( fExpected - iSp1Group2 ) / fExpected, 0.1 );
  fExpected = 898.4;
  EXPECT_LT( fabs( fExpected - iSp2Group2 ) / fExpected, 0.1 );
  EXPECT_EQ( 0, iSp1Group3 );
  EXPECT_EQ( 0, iSp2Group3 );





  //>>>>>>>>>>>>Separate out and only do cell 1, 2<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0.  Group 2: storm damage = 1000.  Group 3:
  //storm damage = 2000.
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  p_oAllTrees->StartOver();
  p_oTree = p_oAllTrees->NextTree();
  while ( p_oTree )
  {
    //Make sure this ain't no snag
    EXPECT_NE(clTreePopulation::snag, p_oTree->GetType());

    iSp = p_oTree->GetSpecies();

    //Get X and Y
    p_oTree->GetValue( p_oPop->GetXCode( iSp, p_oTree->GetType() ), & fX );
    p_oTree->GetValue( p_oPop->GetYCode( iSp, p_oTree->GetType() ), & fY );

    //Get storm damage counter
    p_oTree->GetValue( p_oPop->GetIntDataCode( "stm_dmg", iSp, p_oTree->GetType() ), & iStmDmgValue );

    if ( fX > 8 && fX < 16 && fY > 16 && fY < 24 )
    {

      //Get DBH
      p_oTree->GetValue( p_oPop->GetDbhCode( iSp, p_oTree->GetType() ), & fDiam );

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if ( fDiam < 6 )  EXPECT_EQ( 0, iStmDmgValue );
      else if ( 0 == iSp && 0 == iStmDmgValue ) iSp1Group1++;
      else if ( 1 == iSp && 0 == iStmDmgValue ) iSp2Group1++;
      else if ( 0 == iSp && 1003 == iStmDmgValue ) iSp1Group2++;
      else if ( 1 == iSp && 1003 == iStmDmgValue ) iSp2Group2++;
      else if ( 0 == iSp && 2003 == iStmDmgValue ) iSp1Group3++;
      else if ( 1 == iSp && 2003 == iStmDmgValue ) iSp2Group3++;
      else
      {
        //Error
        sMessage << "TestNormalProcessingRun3, timestep 1, found an unexpected " << "tree storm damage value.  X: " << fX
            << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
        FAIL() << sMessage.str();
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  //Validate the counts
  EXPECT_EQ( 0, iSp1Group1 );
  EXPECT_EQ( 0, iSp2Group1 );
  EXPECT_EQ( 0, iSp1Group2 );
  EXPECT_EQ( 0, iSp2Group2 );
  fExpected = 960.3;
  EXPECT_LT( fabs( fExpected - iSp1Group3 ) / fExpected, 0.1 );
  fExpected = 729.0;
  EXPECT_LT( fabs( fExpected - iSp2Group3 ) / fExpected, 0.1 );
}

/////////////////////////////////////////////////////////////////////////////
// TestStormKillerRun3Timestep5()
/////////////////////////////////////////////////////////////////////////////
void TestStormKillerRun3Timestep5( clTreePopulation * p_oPop )
{
  clTreeSearch * p_oAllTrees;
  clTree * p_oTree;
  int iStmDmgValue;

  //Get all trees
  p_oAllTrees = p_oPop->Find( "all" );

  //All should have a damage of 0.
  p_oTree = p_oAllTrees->NextTree();
  while ( p_oTree )
  {
    //Make sure we have no snags
    EXPECT_NE(clTreePopulation::snag, p_oTree->GetType());
    p_oTree->GetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), & iStmDmgValue );
    EXPECT_EQ( 0, iStmDmgValue );
    p_oTree = p_oAllTrees->NextTree();
  }
}

/////////////////////////////////////////////////////////////////////////////
// WriteStormKillerXMLFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteStormKillerXMLFile1()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">"
      << "<plot>"
      << "<timesteps>5</timesteps>"
      << "<yearsPerTimestep>1</yearsPerTimestep>";

  WriteStormKillerCommonStuff(oOut);
  WriteStormKillerSnagBehaviorList(oOut);
  WriteStormKillerStormParameters(oOut);

  oOut.close();

  return cFileString;

}

/////////////////////////////////////////////////////////////////////////////
// WriteStormKillerXMLFile2()
/////////////////////////////////////////////////////////////////////////////
const char* WriteStormKillerXMLFile2()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">"
      << "<plot>"
      << "<timesteps>5</timesteps>"
      << "<yearsPerTimestep>3</yearsPerTimestep>";

  WriteStormKillerCommonStuff(oOut);
  WriteStormKillerSnagBehaviorList(oOut);
  WriteStormKillerStormParameters(oOut);

  oOut.close();

  return cFileString;

}

/////////////////////////////////////////////////////////////////////////////
// WriteStormKillerXMLFile3()
/////////////////////////////////////////////////////////////////////////////
const char* WriteStormKillerXMLFile3()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">"
      << "<plot>"
      << "<timesteps>5</timesteps>"
      << "<yearsPerTimestep>1</yearsPerTimestep>";

  WriteStormKillerCommonStuff(oOut);
  WriteStormKillerNoSnagBehaviorList(oOut);
  WriteStormKillerStormParameters(oOut);

  oOut.close();

  return cFileString;

}

/////////////////////////////////////////////////////////////////////////////
// WriteStormKillerXMLErrorFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteStormKillerXMLErrorFile1()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">"
      << "<plot>"
      << "<timesteps>5</timesteps>"
      << "<yearsPerTimestep>1</yearsPerTimestep>";

  WriteStormKillerCommonStuff(oOut);

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>StormKiller</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>StochasticMortality</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>RemoveDead</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>3</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "</behaviorList>"
      << "<StochasticMortality2>"
      << "<mo_stochasticMortRate>"
      << "<mo_smrVal species=\"Species_1\">0.0</mo_smrVal>"
      << "<mo_smrVal species=\"Species_2\">0.0</mo_smrVal>"
      << "</mo_stochasticMortRate>"
      << "</StochasticMortality2>";

  oOut << "<StormKiller1>"
      << "<st_minDBH>"
      << "<st_mdVal species=\"Species_1\">5</st_mdVal>"
      << "<st_mdVal species=\"Species_2\">6</st_mdVal>"
      << "</st_minDBH>"
      << "<st_stmMedDmgSurvProbA>"
      << "<st_smdspaVal species=\"Species_1\">0.6</st_smdspaVal>"
      << "<st_smdspaVal species=\"Species_2\">2.34</st_smdspaVal>"
      << "</st_stmMedDmgSurvProbA>"
      << "<st_stmMedDmgSurvProbB>"
      << "<st_smdspbVal species=\"Species_1\">-0.01</st_smdspbVal>"
      << "<st_smdspbVal species=\"Species_2\">-0.02</st_smdspbVal>"
      << "</st_stmMedDmgSurvProbB>"
      << "<st_stmFullDmgSurvProbA>"
      << "<st_sfdspaVal species=\"Species_1\">3.82</st_sfdspaVal>"
      << "<st_sfdspaVal species=\"Species_2\">1.39</st_sfdspaVal>"
      << "</st_stmFullDmgSurvProbA>"
      << "<st_stmFullDmgSurvProbB>"
      << "<st_sfdspbVal species=\"Species_1\">-0.079</st_sfdspbVal>"
      << "<st_sfdspbVal species=\"Species_2\">-0.05</st_sfdspbVal>"
      << "</st_stmFullDmgSurvProbB>"
      << "<st_stmPropTipUpFullDmg>"
      << "<st_sptufdVal species=\"Species_1\">0.3</st_sptufdVal>"
      << "<st_sptufdVal species=\"Species_2\">0.8</st_sptufdVal>"
      << "</st_stmPropTipUpFullDmg>"
      << "<st_numYearsStormSnags>3</st_numYearsStormSnags>"
      << "</StormKiller1>"
      << "</paramFile>";

  oOut.close();
  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteStormKillerXMLErrorFile2()
/////////////////////////////////////////////////////////////////////////////
const char* WriteStormKillerXMLErrorFile2()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">"
      << "<plot>"
      << "<timesteps>5</timesteps>"
      << "<yearsPerTimestep>1</yearsPerTimestep>";

  WriteStormKillerCommonStuff(oOut);

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>Storm</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>StormDamageApplier</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>StormKiller</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>3</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>StochasticMortality</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>4</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>RemoveDead</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>5</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "</behaviorList>"
      << "<StochasticMortality4>"
      << "<mo_stochasticMortRate>"
      << "<mo_smrVal species=\"Species_1\">0.0</mo_smrVal>"
      << "<mo_smrVal species=\"Species_2\">0.0</mo_smrVal>"
      << "</mo_stochasticMortRate>"
      << "</StochasticMortality4>";

  WriteStormKillerStormParameters(oOut);
  oOut.close();
  return cFileString;
}


/////////////////////////////////////////////////////////////////////////////
// WriteStormKillerXMLErrorFile3()
/////////////////////////////////////////////////////////////////////////////
const char* WriteStormKillerXMLErrorFile3()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">"
      << "<plot>"
      << "<timesteps>5</timesteps>"
      << "<yearsPerTimestep>1</yearsPerTimestep>";

  WriteStormKillerCommonStuff(oOut);

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>Storm</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>StormKiller</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>StochasticMortality</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>3</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>RemoveDead</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>4</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "</behaviorList>"
      << "<StochasticMortality3>"
      << "<mo_stochasticMortRate>"
      << "<mo_smrVal species=\"Species_1\">0.0</mo_smrVal>"
      << "<mo_smrVal species=\"Species_2\">0.0</mo_smrVal>"
      << "</mo_stochasticMortRate>"
      << "</StochasticMortality3>";

  oOut << "<Storm1>"
      << "<st_s1ReturnInterval>0</st_s1ReturnInterval>"
      << "<st_s2ReturnInterval>0</st_s2ReturnInterval>"
      << "<st_s3ReturnInterval>0</st_s3ReturnInterval>"
      << "<st_s4ReturnInterval>0</st_s4ReturnInterval>"
      << "<st_s5ReturnInterval>0</st_s5ReturnInterval>"
      << "<st_s6ReturnInterval>0</st_s6ReturnInterval>"
      << "<st_s7ReturnInterval>0</st_s7ReturnInterval>"
      << "<st_s8ReturnInterval>0</st_s8ReturnInterval>"
      << "<st_s9ReturnInterval>0</st_s9ReturnInterval>"
      << "<st_s10ReturnInterval>0</st_s10ReturnInterval>"
      << "<st_susceptibility>1</st_susceptibility>"
      << "<st_stochasticity>0</st_stochasticity>"
      << "<st_stmSSTPeriod>1</st_stmSSTPeriod>"
      << "<st_stmSineD>0</st_stmSineD>"
      << "<st_stmSineF>1</st_stmSineF>"
      << "<st_stmSineG>1</st_stmSineG>"
      << "<st_stmTrendSlopeM>0</st_stmTrendSlopeM>"
      << "<st_stmTrendInterceptI>1</st_stmTrendInterceptI>"
      << "</Storm1>"
      << "<StormKiller2>"
      << "<st_minDBH>"
      << "<st_mdVal species=\"Species_1\">5</st_mdVal>"
      << "<st_mdVal species=\"Species_2\">6</st_mdVal>"
      << "</st_minDBH>"
      << "<st_stmMedDmgSurvProbA>"
      << "<st_smdspaVal species=\"Species_1\">0.6</st_smdspaVal>"
      << "<st_smdspaVal species=\"Species_2\">2.34</st_smdspaVal>"
      << "</st_stmMedDmgSurvProbA>"
      << "<st_stmMedDmgSurvProbB>"
      << "<st_smdspbVal species=\"Species_1\">-0.01</st_smdspbVal>"
      << "<st_smdspbVal species=\"Species_2\">-0.02</st_smdspbVal>"
      << "</st_stmMedDmgSurvProbB>"
      << "<st_stmFullDmgSurvProbA>"
      << "<st_sfdspaVal species=\"Species_1\">3.82</st_sfdspaVal>"
      << "<st_sfdspaVal species=\"Species_2\">1.39</st_sfdspaVal>"
      << "</st_stmFullDmgSurvProbA>"
      << "<st_stmFullDmgSurvProbB>"
      << "<st_sfdspbVal species=\"Species_1\">-0.079</st_sfdspbVal>"
      << "<st_sfdspbVal species=\"Species_2\">-0.05</st_sfdspbVal>"
      << "</st_stmFullDmgSurvProbB>"
      << "<st_stmPropTipUpFullDmg>"
      << "<st_sptufdVal species=\"Species_1\">0.3</st_sptufdVal>"
      << "<st_sptufdVal species=\"Species_2\">0.8</st_sptufdVal>"
      << "</st_stmPropTipUpFullDmg>"
      << "<st_numYearsStormSnags>3</st_numYearsStormSnags>"
      << "</StormKiller2>"
      << "</paramFile>";

  oOut.close();
  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteStormKillerXMLErrorFile4()
/////////////////////////////////////////////////////////////////////////////
const char* WriteStormKillerXMLErrorFile4()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">"
      << "<plot>"
      << "<timesteps>5</timesteps>"
      << "<yearsPerTimestep>1</yearsPerTimestep>";

  WriteStormKillerCommonStuff(oOut);
  WriteStormKillerNoSnagBehaviorList(oOut);

  oOut << "<Storm1>"
      << "<st_s1ReturnInterval>0</st_s1ReturnInterval>"
      << "<st_s2ReturnInterval>0</st_s2ReturnInterval>"
      << "<st_s3ReturnInterval>0</st_s3ReturnInterval>"
      << "<st_s4ReturnInterval>0</st_s4ReturnInterval>"
      << "<st_s5ReturnInterval>0</st_s5ReturnInterval>"
      << "<st_s6ReturnInterval>0</st_s6ReturnInterval>"
      << "<st_s7ReturnInterval>0</st_s7ReturnInterval>"
      << "<st_s8ReturnInterval>0</st_s8ReturnInterval>"
      << "<st_s9ReturnInterval>0</st_s9ReturnInterval>"
      << "<st_s10ReturnInterval>0</st_s10ReturnInterval>"
      << "<st_susceptibility>1</st_susceptibility>"
      << "<st_stochasticity>0</st_stochasticity>"
      << "<st_stmSSTPeriod>1</st_stmSSTPeriod>"
      << "<st_stmSineD>0</st_stmSineD>"
      << "<st_stmSineF>1</st_stmSineF>"
      << "<st_stmSineG>1</st_stmSineG>"
      << "<st_stmTrendSlopeM>0</st_stmTrendSlopeM>"
      << "<st_stmTrendInterceptI>1</st_stmTrendInterceptI>"
      << "</Storm1>"
      << "<StormDamageApplier2>"
      << "<st_minDBH>"
      << "<st_mdVal species=\"Species_1\">5</st_mdVal>"
      << "<st_mdVal species=\"Species_2\">6</st_mdVal>"
      << "</st_minDBH>"
      << "<st_stmDmgInterceptMed>"
      << "<st_sdimVal species=\"Species_1\">2.1789601</st_sdimVal>"
      << "<st_sdimVal species=\"Species_2\">2.475987</st_sdimVal>"
      << "</st_stmDmgInterceptMed>"
      << "<st_stmDmgInterceptFull>"
      << "<st_sdifVal species=\"Species_1\">3.6334169</st_sdifVal>"
      << "<st_sdifVal species=\"Species_2\">3.6331242</st_sdifVal>"
      << "</st_stmDmgInterceptFull>"
      << "<st_stmIntensityCoeff>"
      << "<st_sicVal species=\"Species_1\">-0.3545352</st_sicVal>"
      << "<st_sicVal species=\"Species_2\">-1.2289105</st_sicVal>"
      << "</st_stmIntensityCoeff>"
      << "<st_stmDBHCoeff>"
      << "<st_sdcVal species=\"Species_1\">0.8280319</st_sdcVal>"
      << "<st_sdcVal species=\"Species_2\">0.3282479</st_sdcVal>"
      << "</st_stmDBHCoeff>"
      << "<st_numYearsToHeal>4</st_numYearsToHeal>"
      << "</StormDamageApplier2>"
      << "<StormKiller3>"
      << "<st_minDBH>"
      << "<st_mdVal species=\"Species_1\">5</st_mdVal>"
      << "<st_mdVal species=\"Species_2\">6</st_mdVal>"
      << "</st_minDBH>"
      << "<st_stmMedDmgSurvProbA>"
      << "<st_smdspaVal species=\"Species_1\">6.05</st_smdspaVal>"
      << "<st_smdspaVal species=\"Species_2\">2.34</st_smdspaVal>"
      << "</st_stmMedDmgSurvProbA>"
      << "<st_stmMedDmgSurvProbB>"
      << "<st_smdspbVal species=\"Species_1\">-0.01</st_smdspbVal>"
      << "<st_smdspbVal species=\"Species_2\">-0.02</st_smdspbVal>"
      << "</st_stmMedDmgSurvProbB>"
      << "<st_stmFullDmgSurvProbA>"
      << "<st_sfdspaVal species=\"Species_1\">3.82</st_sfdspaVal>"
      << "<st_sfdspaVal species=\"Species_2\">1.39</st_sfdspaVal>"
      << "</st_stmFullDmgSurvProbA>"
      << "<st_stmFullDmgSurvProbB>"
      << "<st_sfdspbVal species=\"Species_1\">-0.079</st_sfdspbVal>"
      << "<st_sfdspbVal species=\"Species_2\">-0.05</st_sfdspbVal>"
      << "</st_stmFullDmgSurvProbB>"
      << "<st_stmPropTipUpFullDmg>"
      << "<st_sptufdVal species=\"Species_1\">-0.3</st_sptufdVal>"
      << "<st_sptufdVal species=\"Species_2\">0.8</st_sptufdVal>"
      << "</st_stmPropTipUpFullDmg>"
      << "<st_numYearsStormSnags>3</st_numYearsStormSnags>"
      << "</StormKiller3>"
      << "</paramFile>";

  oOut.close();
  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteStormKillerXMLErrorFile5()
/////////////////////////////////////////////////////////////////////////////
const char* WriteStormKillerXMLErrorFile5()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">"
      << "<plot>"
      << "<timesteps>5</timesteps>"
      << "<yearsPerTimestep>1</yearsPerTimestep>";

  WriteStormKillerCommonStuff(oOut);
  WriteStormKillerNoSnagBehaviorList(oOut);

  oOut << "<Storm1>"
      << "<st_s1ReturnInterval>0</st_s1ReturnInterval>"
      << "<st_s2ReturnInterval>0</st_s2ReturnInterval>"
      << "<st_s3ReturnInterval>0</st_s3ReturnInterval>"
      << "<st_s4ReturnInterval>0</st_s4ReturnInterval>"
      << "<st_s5ReturnInterval>0</st_s5ReturnInterval>"
      << "<st_s6ReturnInterval>0</st_s6ReturnInterval>"
      << "<st_s7ReturnInterval>0</st_s7ReturnInterval>"
      << "<st_s8ReturnInterval>0</st_s8ReturnInterval>"
      << "<st_s9ReturnInterval>0</st_s9ReturnInterval>"
      << "<st_s10ReturnInterval>0</st_s10ReturnInterval>"
      << "<st_susceptibility>1</st_susceptibility>"
      << "<st_stochasticity>0</st_stochasticity>"
      << "<st_stmSSTPeriod>1</st_stmSSTPeriod>"
      << "<st_stmSineD>0</st_stmSineD>"
      << "<st_stmSineF>1</st_stmSineF>"
      << "<st_stmSineG>1</st_stmSineG>"
      << "<st_stmTrendSlopeM>0</st_stmTrendSlopeM>"
      << "<st_stmTrendInterceptI>1</st_stmTrendInterceptI>"
      << "</Storm1>"
      << "<StormDamageApplier2>"
      << "<st_minDBH>"
      << "<st_mdVal species=\"Species_1\">5</st_mdVal>"
      << "<st_mdVal species=\"Species_2\">6</st_mdVal>"
      << "</st_minDBH>"
      << "<st_stmDmgInterceptMed>"
      << "<st_sdimVal species=\"Species_1\">2.1789601</st_sdimVal>"
      << "<st_sdimVal species=\"Species_2\">2.475987</st_sdimVal>"
      << "</st_stmDmgInterceptMed>"
      << "<st_stmDmgInterceptFull>"
      << "<st_sdifVal species=\"Species_1\">3.6334169</st_sdifVal>"
      << "<st_sdifVal species=\"Species_2\">3.6331242</st_sdifVal>"
      << "</st_stmDmgInterceptFull>"
      << "<st_stmIntensityCoeff>"
      << "<st_sicVal species=\"Species_1\">-0.3545352</st_sicVal>"
      << "<st_sicVal species=\"Species_2\">-1.2289105</st_sicVal>"
      << "</st_stmIntensityCoeff>"
      << "<st_stmDBHCoeff>"
      << "<st_sdcVal species=\"Species_1\">0.8280319</st_sdcVal>"
      << "<st_sdcVal species=\"Species_2\">0.3282479</st_sdcVal>"
      << "</st_stmDBHCoeff>"
      << "<st_numYearsToHeal>4</st_numYearsToHeal>"
      << "</StormDamageApplier2>"
      << "<StormKiller3>"
      << "<st_minDBH>"
      << "<st_mdVal species=\"Species_1\">5</st_mdVal>"
      << "<st_mdVal species=\"Species_2\">6</st_mdVal>"
      << "</st_minDBH>"
      << "<st_stmMedDmgSurvProbA>"
      << "<st_smdspaVal species=\"Species_1\">6.05</st_smdspaVal>"
      << "<st_smdspaVal species=\"Species_2\">2.34</st_smdspaVal>"
      << "</st_stmMedDmgSurvProbA>"
      << "<st_stmMedDmgSurvProbB>"
      << "<st_smdspbVal species=\"Species_1\">-0.01</st_smdspbVal>"
      << "<st_smdspbVal species=\"Species_2\">-0.02</st_smdspbVal>"
      << "</st_stmMedDmgSurvProbB>"
      << "<st_stmFullDmgSurvProbA>"
      << "<st_sfdspaVal species=\"Species_1\">3.82</st_sfdspaVal>"
      << "<st_sfdspaVal species=\"Species_2\">1.39</st_sfdspaVal>"
      << "</st_stmFullDmgSurvProbA>"
      << "<st_stmFullDmgSurvProbB>"
      << "<st_sfdspbVal species=\"Species_1\">-0.079</st_sfdspbVal>"
      << "<st_sfdspbVal species=\"Species_2\">-0.05</st_sfdspbVal>"
      << "</st_stmFullDmgSurvProbB>"
      << "<st_stmPropTipUpFullDmg>"
      << "<st_sptufdVal species=\"Species_1\">0.3</st_sptufdVal>"
      << "<st_sptufdVal species=\"Species_2\">0.8</st_sptufdVal>"
      << "</st_stmPropTipUpFullDmg>"
      << "<st_numYearsStormSnags>-3</st_numYearsStormSnags>"
      << "</StormKiller3>"
      << "</paramFile>";

  oOut.close();
  return cFileString;

}

/////////////////////////////////////////////////////////////////////////////
// WriteStormKillerXMLErrorFile6()
/////////////////////////////////////////////////////////////////////////////
const char* WriteStormKillerXMLErrorFile6()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">"
      << "<plot>"
      << "<timesteps>5</timesteps>"
      << "<yearsPerTimestep>1</yearsPerTimestep>";

  WriteStormKillerCommonStuff(oOut);

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>Storm</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>StormDamageApplier</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>StormKiller</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>3</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "</behaviorList>";

  WriteStormKillerStormParameters(oOut);
  oOut.close();
  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteStormKillerCommonStuff()
/////////////////////////////////////////////////////////////////////////////
void WriteStormKillerCommonStuff(std::fstream &oOut)
{
  using namespace std;
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
      << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
      << "<tr_madVal species=\"Species_2\">10.0</tr_madVal>"
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
      << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_2\">0.8008</tr_cdtdVal>"
      << "</tr_conversionDiam10ToDBH>"
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
}

/////////////////////////////////////////////////////////////////////////////
// WriteStormKillerSnagBehaviorList()
/////////////////////////////////////////////////////////////////////////////
void WriteStormKillerSnagBehaviorList(std::fstream &oOut)
{
  using namespace std;
  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>Storm</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>StormDamageApplier</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Snag\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Snag\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>StormKiller</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>3</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Snag\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Snag\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>StochasticMortality</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>4</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Snag\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Snag\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>RemoveDead</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>5</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Snag\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Snag\"/>"
      << "</behavior>"
      << "</behaviorList>"
      << "<StochasticMortality4>"
      << "<mo_stochasticMortRate>"
      << "<mo_smrVal species=\"Species_1\">0.0</mo_smrVal>"
      << "<mo_smrVal species=\"Species_2\">0.0</mo_smrVal>"
      << "</mo_stochasticMortRate>"
      << "</StochasticMortality4>";
}

/////////////////////////////////////////////////////////////////////////////
// WriteStormKillerNoSnagBehaviorList()
/////////////////////////////////////////////////////////////////////////////
void WriteStormKillerNoSnagBehaviorList(std::fstream &oOut)
{
  using namespace std;
  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>Storm</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>StormDamageApplier</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>StormKiller</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>3</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>StochasticMortality</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>4</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>RemoveDead</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>5</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "</behaviorList>"
      << "<StochasticMortality4>"
      << "<mo_stochasticMortRate>"
      << "<mo_smrVal species=\"Species_1\">0.0</mo_smrVal>"
      << "<mo_smrVal species=\"Species_2\">0.0</mo_smrVal>"
      << "</mo_stochasticMortRate>"
      << "</StochasticMortality4>";
}

/////////////////////////////////////////////////////////////////////////////
// WriteStormKillerStormParameters()
/////////////////////////////////////////////////////////////////////////////
void WriteStormKillerStormParameters(std::fstream &oOut)
{
  using namespace std;
  oOut << "<Storm1>"
      << "<st_s1ReturnInterval>0</st_s1ReturnInterval>"
      << "<st_s2ReturnInterval>0</st_s2ReturnInterval>"
      << "<st_s3ReturnInterval>0</st_s3ReturnInterval>"
      << "<st_s4ReturnInterval>0</st_s4ReturnInterval>"
      << "<st_s5ReturnInterval>0</st_s5ReturnInterval>"
      << "<st_s6ReturnInterval>0</st_s6ReturnInterval>"
      << "<st_s7ReturnInterval>0</st_s7ReturnInterval>"
      << "<st_s8ReturnInterval>0</st_s8ReturnInterval>"
      << "<st_s9ReturnInterval>0</st_s9ReturnInterval>"
      << "<st_s10ReturnInterval>0</st_s10ReturnInterval>"
      << "<st_susceptibility>1</st_susceptibility>"
      << "<st_stochasticity>0</st_stochasticity>"
      << "<st_stmSSTPeriod>1</st_stmSSTPeriod>"
      << "<st_stmSineD>0</st_stmSineD>"
      << "<st_stmSineF>1</st_stmSineF>"
      << "<st_stmSineG>1</st_stmSineG>"
      << "<st_stmTrendSlopeM>0</st_stmTrendSlopeM>"
      << "<st_stmTrendInterceptI>1</st_stmTrendInterceptI>"
      << "</Storm1>"
      << "<StormDamageApplier2>"
      << "<st_minDBH>"
      << "<st_mdVal species=\"Species_1\">5</st_mdVal>"
      << "<st_mdVal species=\"Species_2\">6</st_mdVal>"
      << "</st_minDBH>"
      << "<st_stmDmgInterceptMed>"
      << "<st_sdimVal species=\"Species_1\">2.1789601</st_sdimVal>"
      << "<st_sdimVal species=\"Species_2\">2.475987</st_sdimVal>"
      << "</st_stmDmgInterceptMed>"
      << "<st_stmDmgInterceptFull>"
      << "<st_sdifVal species=\"Species_1\">3.6334169</st_sdifVal>"
      << "<st_sdifVal species=\"Species_2\">3.6331242</st_sdifVal>"
      << "</st_stmDmgInterceptFull>"
      << "<st_stmIntensityCoeff>"
      << "<st_sicVal species=\"Species_1\">-0.3545352</st_sicVal>"
      << "<st_sicVal species=\"Species_2\">-1.2289105</st_sicVal>"
      << "</st_stmIntensityCoeff>"
      << "<st_stmDBHCoeff>"
      << "<st_sdcVal species=\"Species_1\">0.8280319</st_sdcVal>"
      << "<st_sdcVal species=\"Species_2\">0.3282479</st_sdcVal>"
      << "</st_stmDBHCoeff>"
      << "<st_numYearsToHeal>4</st_numYearsToHeal>"
      << "</StormDamageApplier2>"
      << "<StormKiller3>"
      << "<st_minDBH>"
      << "<st_mdVal species=\"Species_1\">5</st_mdVal>"
      << "<st_mdVal species=\"Species_2\">6</st_mdVal>"
      << "</st_minDBH>"
      << "<st_stmMedDmgSurvProbA>"
      << "<st_smdspaVal species=\"Species_1\">0.6</st_smdspaVal>"
      << "<st_smdspaVal species=\"Species_2\">2.34</st_smdspaVal>"
      << "</st_stmMedDmgSurvProbA>"
      << "<st_stmMedDmgSurvProbB>"
      << "<st_smdspbVal species=\"Species_1\">-0.01</st_smdspbVal>"
      << "<st_smdspbVal species=\"Species_2\">-0.02</st_smdspbVal>"
      << "</st_stmMedDmgSurvProbB>"
      << "<st_stmFullDmgSurvProbA>"
      << "<st_sfdspaVal species=\"Species_1\">3.82</st_sfdspaVal>"
      << "<st_sfdspaVal species=\"Species_2\">1.39</st_sfdspaVal>"
      << "</st_stmFullDmgSurvProbA>"
      << "<st_stmFullDmgSurvProbB>"
      << "<st_sfdspbVal species=\"Species_1\">-0.079</st_sfdspbVal>"
      << "<st_sfdspbVal species=\"Species_2\">-0.05</st_sfdspbVal>"
      << "</st_stmFullDmgSurvProbB>"
      << "<st_stmPropTipUpFullDmg>"
      << "<st_sptufdVal species=\"Species_1\">0.3</st_sptufdVal>"
      << "<st_sptufdVal species=\"Species_2\">0.8</st_sptufdVal>"
      << "</st_stmPropTipUpFullDmg>"
      << "<st_numYearsStormSnags>3</st_numYearsStormSnags>"
      << "</StormKiller3>"
      << "</paramFile>";
}
