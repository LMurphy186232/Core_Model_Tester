//---------------------------------------------------------------------------
// TestStormDamageApplier.cpp
//---------------------------------------------------------------------------
#include "TestStormDamageApplier.h"
#include <gtest/gtest.h>
#include "SimManager.h"
#include "Grid.h"
#include "TreePopulation.h"
#include "Storm.h"
#include <fstream>
#include <sstream>
#include <math.h>

/////////////////////////////////////////////////////////////////////////////
// MakeGraphs()
// If you wish a visual test, this will output a spreadsheet for graph making.
// It will write a tab-delimited file called "StormTest.txt". There is one
// table for each species. It does storms at 0.02 severity intervals from 0
// to 1, a thousand trees of each species, then outputs how many were
// no damage, medium damage, and severe damage.
/////////////////////////////////////////////////////////////////////////////
/*void MakeGraphs() {
  using namespace std;
  int * * p_iCount; //species by damage category
  std::fstream oOut;
  oOut.open( "StormTest.txt", ios::out | ios::trunc );

  //Feed our file to the sim manager
  clSimManager * p_oSimManager = new clSimManager( 3, 2, "" );
  p_oSimManager->ReadFile( WriteStormDamageApplierXMLFile3() );

  //Get the tree population
  clPopulationBase * p_oTemp = p_oSimManager->GetPopulationObject( "treepopulation" );
  clTreePopulation * p_oPop = ( clTreePopulation * ) p_oTemp;
  clTreeSearch *p_oAllTrees;
  clTree * p_oTree;
  int i, j;
  p_iCount = new int * [p_oPop->GetNumberOfSpecies()];
  for ( i = 0; i < p_oPop->GetNumberOfSpecies(); i++ )
  {
    p_iCount[i] = new int[3];
  }

  //Get the "Storm Damage" grid object
  clGrid * p_oStormGrid = p_oSimManager->GetGridObject( "Storm Damage" );
  ASSERT_TRUE( p_oStormGrid != NULL );

  float fX, fY, fDiam, fStormSeverity;
  int iStmDmgCode = p_oStormGrid->GetFloatDataCode( "1dmg_index" ), iStmDmgValue;

  ASSERT_TRUE( iStmDmgCode != -1 );

  oOut << "Storm Damaged Trees, DBH 30\n";
  oOut << "Storm Severity";
  for ( i = 0; i < p_oPop->GetNumberOfSpecies(); i++ )
  {
    oOut << "\t" << p_oPop->TranslateSpeciesCodeToName( i ) << " Undamaged\t" << p_oPop->TranslateSpeciesCodeToName( i )
         << " Med dmg\t" << p_oPop->TranslateSpeciesCodeToName( i ) << " Full dmg";
  }
  oOut << "\n";

  for ( fStormSeverity = 0; fStormSeverity <= 1.0; fStormSeverity += 0.02 )
  {
    p_oStormGrid->SetValueOfCell( 0, 0, iStmDmgCode, fStormSeverity );
    fX = 1;
    fY = 1;
    fDiam = 30;
    for ( j = 0; j < p_oPop->GetNumberOfSpecies(); j++ )
    {
      for ( i = 0; i < 1000; i++ )
      {
        p_oPop->CreateTree( fX, fY, j, clTreePopulation::adult, fDiam );
      }
    }

    for ( i = 0; i < p_oPop->GetNumberOfSpecies(); i++ ) {
      for (j = 0; j < 3; j++) {
         p_iCount[i][j] = 0;
      }
    }

    p_oSimManager->RunSim(1);
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_oTree->GetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), & iStmDmgValue );
      if (iStmDmgValue > 2000) {
        iStmDmgValue = 2;
      } else if (iStmDmgValue > 1000) {
        iStmDmgValue = 1;
      }

      p_iCount[p_oTree->GetSpecies()][iStmDmgValue]++;

      p_oTree = p_oAllTrees->NextTree();
    }

    //Erase all the trees
    p_oAllTrees->StartOver();
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_oPop->KillTree(p_oTree, remove_tree);
      p_oTree = p_oAllTrees->NextTree();
    }

    //Write out the results
    oOut << fStormSeverity;
    for ( i = 0; i < p_oPop->GetNumberOfSpecies(); i++ ) {
      for (j = 0; j < 3; j++) {
         oOut << "\t" << p_iCount[i][j];
      }
    }
    oOut << "\n";
  }

  oOut.close();

  for ( i = 0; i < p_oPop->GetNumberOfSpecies(); i++ )
  {
    delete[] p_iCount[i];
  }
  delete[] p_iCount;

  delete p_oSimManager;

}*/

////////////////////////////////////////////////////////////////////////////
// TestErrorProcessing()
////////////////////////////////////////////////////////////////////////////
TEST(StormDamageApplier, TestErrorProcessing)
{
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try
  {
    p_oSimManager->ReadFile( WriteStormDamageApplierXMLErrorFile1() );
    FAIL() << "TestStormDamageApplier error processing didn't catch error for WriteStormDamageApplierXMLErrorFile1.";
  }
  catch ( modelErr& err )
  {
    if ( err.sFunction.compare("clStormDamageApplier::GetData" ) != 0 )
    {
      FAIL() << "TestStormDamageApplier error processing caught wrong error for WriteStormDamageApplierXMLErrorFile1.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile( WriteStormDamageApplierXMLErrorFile2() );
    FAIL() << "TestStormDamageApplier error processing didn't catch error for WriteStormDamageApplierXMLErrorFile2.";
  }
  catch ( modelErr& err )
  {
    if ( err.sFunction.compare("clStormDamageApplier::RegisterTreeDataMembers" ) != 0 )
    {
      FAIL() << "TestStormDamageApplier error processing caught wrong error for WriteStormDamageApplierXMLErrorFile2.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile( WriteStormDamageApplierXMLErrorFile3() );
    FAIL() << "TestStormDamageApplier error processing didn't catch error for WriteStormDamageApplierXMLErrorFile3.";
  }
  catch ( modelErr& err )
  {
    if ( err.sFunction.compare("clStormDamageApplier::GetParameterFileData" ) != 0 )
    {
      FAIL() << "TestStormDamageApplier error processing caught wrong error for WriteStormDamageApplierXMLErrorFile3.";
    }
    ;
  }
  delete p_oSimManager;
}

/////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun1()
// Tests normal processing. WriteStormDamageApplierXMLFile1() writes the parameter file.
// Aspects of the run:
//
// -- Grid resolution of "Storm Damage" is default.
// -- Run is 5 timesteps.
// -- 1 year per timestep.
// -- This behavior kills no trees.
// -- There are no snags for this behavior.
// -- The following trees will be added, with the appropriate storm triggered
//    for timestep 1:
//   -- Grid (0,0): 1000 trees of Species 1 and 2, DBH 30. Damage index is 0.
//   -- Grid (0,1): 1000 trees of Species 1 and 2, DBH 30. Damage index is 0.5.
//   -- Grid (0,2): 1000 trees of Species 1 and 2, DBH 30. Damage index is 1.
//   -- Grid (1,0): 1000 trees of Species 1 and 2, DBH 8. Damage index is 0.
//   -- Grid (1,1): 1000 trees of Species 1 and 2, DBH 8. Damage index is 0.3.
//   -- Grid (1,2): 1000 trees of Species 1 and 2, DBH 8. Damage index is 1.
//   -- Grid (2,0): 1000 trees of Species 1 and 2, DBH 45. Damage index is 0.2.
//      Initial counter is 1002.
//   -- Grid (2,1): 1000 trees of Species 1 and 2, DBH 15. Damage index is 0.7.
//      Initial counter is 2003.
//   -- All grids get 100 trees of DBH 4, Species 1, and DBH 5, Species 2.
//
// The run proceeds for 5 timesteps and the number of trees with each damage
// counter is checked through time.
/////////////////////////////////////////////////////////////////////////////
TEST(StormDamageApplier, TestNormalProcessingRun1) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    //Feed our file to the sim manager
    p_oSimManager->ReadFile( WriteStormDamageApplierXMLFile1() );

    //Get the tree population
    clTreePopulation * p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
    clTree * p_oTree;

    //Get the "Storm Damage" grid object
    clGrid * p_oStormGrid = p_oSimManager->GetGridObject( "Storm Damage" );
    clPackage *p_oPkg;
    ASSERT_TRUE( p_oStormGrid != NULL );

    float fX, fY, fDiam, fVal;
    int iStmDmgCode = p_oStormGrid->GetPackageFloatDataCode( "1dmg_index" ), iStmDmgValue, i;

    ASSERT_TRUE( iStmDmgCode != -1 );

    //Grid (0,0): 1000 trees of Species 1 and 2, DBH 30. Damage index is 0.
    //1000 trees of DBH 4, Species 1, and DBH 5, Species 2.
    //1000 snags of damage 1000 and 1000 snags of damage 2000.
    fVal = 0;
    p_oPkg = p_oStormGrid->CreatePackageOfCell(0,0);
    p_oPkg->SetValue(iStmDmgCode, fVal);
    fX = 1;
    fY = 1;
    fDiam = 30;
    for ( i = 0; i < 1000; i++ )
    {
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, fDiam );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::adult, fDiam );
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::sapling, 4.0 );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::sapling, 5.0 );
      iStmDmgValue = 1000;
      p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::snag, fDiam );
      p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iStmDmgValue );
      iStmDmgValue = 2000;
      p_oTree = p_oPop->CreateTree( fX, fY, 1, clTreePopulation::snag, fDiam );
      p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iStmDmgValue );
    }

    //Grid (0,1): 1000 trees of Species 1 and 2, DBH 30. Damage index is 0.5.
    //1000 trees of DBH 4, Species 1, and DBH 5, Species 2.
    //1000 snags of damage 1000 and 1000 snags of damage 2000.
    fVal = 0.5;
    p_oPkg = p_oStormGrid->CreatePackageOfCell(0,1);
    p_oPkg->SetValue(iStmDmgCode, fVal);
    fX = 1;
    fY = 9;
    fDiam = 30;
    for ( i = 0; i < 1000; i++ )
    {
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, fDiam );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::adult, fDiam );
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::sapling, 4.0 );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::sapling, 5.0 );
      iStmDmgValue = 1000;
      p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::snag, fDiam );
      p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iStmDmgValue );
      iStmDmgValue = 2000;
      p_oTree = p_oPop->CreateTree( fX, fY, 1, clTreePopulation::snag, fDiam );
      p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iStmDmgValue );
    }

    //Grid (0,2): 1000 trees of Species 1 and 2, DBH 30. Damage index is 1.
    //1000 trees of DBH 4, Species 1, and DBH 5, Species 2.
    //1000 snags of damage 1000 and 1000 snags of damage 2000.
    fVal = 1.0;
    p_oPkg = p_oStormGrid->CreatePackageOfCell(0,2);
    p_oPkg->SetValue(iStmDmgCode, fVal);
    fX = 1;
    fY = 17;
    fDiam = 30;
    for ( i = 0; i < 1000; i++ )
    {
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, fDiam );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::adult, fDiam );
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::sapling, 4.0 );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::sapling, 5.0 );
      iStmDmgValue = 1000;
      p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::snag, fDiam );
      p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iStmDmgValue );
      iStmDmgValue = 2000;
      p_oTree = p_oPop->CreateTree( fX, fY, 1, clTreePopulation::snag, fDiam );
      p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iStmDmgValue );
    }

    //Grid (1,0): 1000 trees of Species 1 and 2, DBH 8. Damage index is 0.
    //1000 trees of DBH 4, Species 1, and DBH 5, Species 2.
    //1000 snags of damage 1000 and 1000 snags of damage 2000.
    fVal = 0;
    p_oPkg = p_oStormGrid->CreatePackageOfCell(1,0);
    p_oPkg->SetValue(iStmDmgCode, fVal);
    fX = 9;
    fY = 1;
    fDiam = 8;
    for ( i = 0; i < 1000; i++ )
    {
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, fDiam );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::adult, fDiam );
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::sapling, 4.0 );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::sapling, 5.0 );
      iStmDmgValue = 1000;
      p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::snag, 30.0 );
      p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iStmDmgValue );
      iStmDmgValue = 2000;
      p_oTree = p_oPop->CreateTree( fX, fY, 1, clTreePopulation::snag, 30.0 );
      p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iStmDmgValue );
    }

    //Grid (1,1): 1000 trees of Species 1 and 2, DBH 8. Damage index is 0.3.
    //1000 trees of DBH 4, Species 1, and DBH 5, Species 2.
    //1000 snags of damage 1000 and 1000 snags of damage 2000.
    fVal = 0.3;
    p_oPkg = p_oStormGrid->CreatePackageOfCell(1,1);
    p_oPkg->SetValue(iStmDmgCode, fVal);
    fX = 9;
    fY = 9;
    fDiam = 8;
    for ( i = 0; i < 1000; i++ )
    {
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, fDiam );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::adult, fDiam );
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::sapling, 4.0 );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::sapling, 5.0 );
      iStmDmgValue = 1000;
      p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::snag, 30.0 );
      p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iStmDmgValue );
      iStmDmgValue = 2000;
      p_oTree = p_oPop->CreateTree( fX, fY, 1, clTreePopulation::snag, 30.0 );
      p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iStmDmgValue );
    }

    //Grid (1,2): 1000 trees of Species 1 and 2, DBH 8. Damage index is 1.
    //1000 trees of DBH 4, Species 1, and DBH 5, Species 2.
    //1000 snags of damage 1000 and 1000 snags of damage 2000.
    fVal = 1;
    p_oPkg = p_oStormGrid->CreatePackageOfCell(1, 2);
    p_oPkg->SetValue(iStmDmgCode, fVal);
    fX = 9;
    fY = 17;
    fDiam = 8;
    for ( i = 0; i < 1000; i++ )
    {
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, fDiam );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::adult, fDiam );
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::sapling, 4.0 );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::sapling, 5.0 );
      iStmDmgValue = 1000;
      p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::snag, 30.0 );
      p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iStmDmgValue );
      iStmDmgValue = 2000;
      p_oTree = p_oPop->CreateTree( fX, fY, 1, clTreePopulation::snag, 30.0 );
      p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iStmDmgValue );
    }

    //Grid (2,0): 1000 trees of Species 1 and 2, DBH 45. Damage index is 0.2.
    //Initial counter is 1002.
    //1000 trees of DBH 4, Species 1, and DBH 5, Species 2.
    fVal = 0.2;
    p_oPkg = p_oStormGrid->CreatePackageOfCell(2, 0);
    p_oPkg->SetValue(iStmDmgCode, fVal);
    fX = 17;
    fY = 1;
    fDiam = 45;
    iStmDmgValue = 1002;
    for ( i = 0; i < 1000; i++ )
    {
      p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, fDiam );
      p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iStmDmgValue );

      p_oTree = p_oPop->CreateTree( fX, fY, 1, clTreePopulation::adult, fDiam );
      p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iStmDmgValue );

      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::sapling, 4.0 );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::sapling, 5.0 );
    }

    //Grid (2,1): 1000 trees of Species 1 and 2, DBH 15. Damage index is 0.7.
    //Initial counter is 2003.
    //1000 trees of DBH 4, Species 1, and DBH 5, Species 2,
    fVal = 0.7;
    p_oPkg = p_oStormGrid->CreatePackageOfCell(2, 1);
    p_oPkg->SetValue(iStmDmgCode, fVal);
    fX = 17;
    fY = 9;
    fDiam = 15;
    iStmDmgValue = 2003;
    for ( i = 0; i < 1000; i++ )
    {
      p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, fDiam );
      p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iStmDmgValue );

      p_oTree = p_oPop->CreateTree( fX, fY, 1, clTreePopulation::adult, fDiam );
      p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iStmDmgValue );

      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::sapling, 4.0 );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::sapling, 5.0 );
    }

    //Can't run storm or it will reset the packages
    for (i = 1; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
      p_oSimManager->GetBehaviorObject(i)->Action();
    }
    TestStormDamageApplierRun1Timestep1( p_oPop );
    p_oSimManager->RunSim( 1 );
    TestStormDamageApplierRun1Timestep2( p_oPop );
    p_oSimManager->RunSim( 1 );
    TestStormDamageApplierRun1Timestep3( p_oPop );
    p_oSimManager->RunSim( 1 );
    TestStormDamageApplierRun1Timestep4( p_oPop );
    p_oSimManager->RunSim( 1 );
    TestStormDamageApplierRun1Timestep5( p_oPop );
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun2()
// Tests normal processing. WriteStormDamageApplierXMLFile2() writes the parameter file.
// Aspects of the run:
//
// -- Grid resolution of "Storm Damage" is default.
// -- Run is 3 timesteps.
// -- 3 years per timestep.
// -- This behavior kills no trees.
// -- There are no snags for this behavior.
// -- The following trees will be added, with the appropriate storm triggered
//    for timestep 1:
//   -- Grid (0,0): 1000 trees of Species 1 and 2, DBH 30. Damage index is 0.
//   -- Grid (0,1): 1000 trees of Species 1 and 2, DBH 30. Damage index is 0.5.
//   -- Grid (0,2): 1000 trees of Species 1 and 2, DBH 30. Damage index is 1.
//   -- Grid (1,0): 1000 trees of Species 1 and 2, DBH 8. Damage index is 0.
//   -- Grid (1,1): 1000 trees of Species 1 and 2, DBH 8. Damage index is 0.3.
//   -- Grid (1,2): 1000 trees of Species 1 and 2, DBH 8. Damage index is 1.
//   -- Grid (2,0): 1000 trees of Species 1 and 2, DBH 45. Damage index is 0.2.
//      Initial counter is 1002.
//   -- Grid (2,1): 1000 trees of Species 1 and 2, DBH 15. Damage index is 0.7.
//      Initial counter is 2003.
//   -- All grids get 100 trees of DBH 4, Species 1, and DBH 5, Species 2.
//
// The run proceeds for 3 timesteps and the number of trees with each damage
// counter is checked through time.
/////////////////////////////////////////////////////////////////////////////
TEST(StormDamageApplier, TestNormalProcessingRun2) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    //Feed our file to the sim manager
    p_oSimManager->ReadFile( WriteStormDamageApplierXMLFile2() );

    //Get the tree population
    clTreePopulation * p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
    clTree * p_oTree;

    //Get the "Storm Damage" grid object
    clGrid * p_oStormGrid = p_oSimManager->GetGridObject( "Storm Damage" );
    clPackage *p_oPkg;
    ASSERT_TRUE( p_oStormGrid != NULL );

    float fX, fY, fDiam, fVal;
    int iStmDmgCode = p_oStormGrid->GetPackageFloatDataCode( "1dmg_index" ), iStmDmgValue, i;

    ASSERT_TRUE( iStmDmgCode != -1 );

    //Grid (0,0): 1000 trees of Species 1 and 2, DBH 30. Damage index is 0.
    //1000 trees of DBH 4, Species 1, and DBH 5, Species 2.
    //1000 snags of damage 1000 and 1000 snags of damage 2000.
    fVal = 0;
    p_oPkg = p_oStormGrid->CreatePackageOfCell(0, 0);
    p_oPkg->SetValue(iStmDmgCode, fVal);
    fX = 1;
    fY = 1;
    fDiam = 30;
    for ( i = 0; i < 1000; i++ )
    {
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, fDiam );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::adult, fDiam );
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::sapling, 4.0 );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::sapling, 5.0 );
      iStmDmgValue = 1000;
      p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::snag, fDiam );
      p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iStmDmgValue );
      iStmDmgValue = 2000;
      p_oTree = p_oPop->CreateTree( fX, fY, 1, clTreePopulation::snag, fDiam );
      p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iStmDmgValue );
    }

    //Grid (0,1): 1000 trees of Species 1 and 2, DBH 30. Damage index is 0.5.
    //1000 trees of DBH 4, Species 1, and DBH 5, Species 2.
    //1000 snags of damage 1000 and 1000 snags of damage 2000.
    fVal = 0.5;
    p_oPkg = p_oStormGrid->CreatePackageOfCell(0, 1);
    p_oPkg->SetValue(iStmDmgCode, fVal);
    fX = 1;
    fY = 9;
    fDiam = 30;
    for ( i = 0; i < 1000; i++ )
    {
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, fDiam );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::adult, fDiam );
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::sapling, 4.0 );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::sapling, 5.0 );
      iStmDmgValue = 1000;
      p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::snag, fDiam );
      p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iStmDmgValue );
      iStmDmgValue = 2000;
      p_oTree = p_oPop->CreateTree( fX, fY, 1, clTreePopulation::snag, fDiam );
      p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iStmDmgValue );
    }

    //Grid (0,2): 1000 trees of Species 1 and 2, DBH 30. Damage index is 1.
    //1000 trees of DBH 4, Species 1, and DBH 5, Species 2.
    //1000 snags of damage 1000 and 1000 snags of damage 2000.
    fVal = 1.0;
    p_oPkg = p_oStormGrid->CreatePackageOfCell(0, 2);
    p_oPkg->SetValue(iStmDmgCode, fVal);
    fX = 1;
    fY = 17;
    fDiam = 30;
    for ( i = 0; i < 1000; i++ )
    {
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, fDiam );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::adult, fDiam );
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::sapling, 4.0 );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::sapling, 5.0 );
      iStmDmgValue = 1000;
      p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::snag, fDiam );
      p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iStmDmgValue );
      iStmDmgValue = 2000;
      p_oTree = p_oPop->CreateTree( fX, fY, 1, clTreePopulation::snag, fDiam );
      p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iStmDmgValue );
    }

    //Grid (1,0): 1000 trees of Species 1 and 2, DBH 8. Damage index is 0.
    //1000 trees of DBH 4, Species 1, and DBH 5, Species 2.
    //1000 snags of damage 1000 and 1000 snags of damage 2000.
    fVal = 0;
    p_oPkg = p_oStormGrid->CreatePackageOfCell(1, 0);
    p_oPkg->SetValue(iStmDmgCode, fVal);
    fX = 9;
    fY = 1;
    fDiam = 8;
    for ( i = 0; i < 1000; i++ )
    {
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, fDiam );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::adult, fDiam );
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::sapling, 4.0 );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::sapling, 5.0 );
      iStmDmgValue = 1000;
      p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::snag, 30.0 );
      p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iStmDmgValue );
      iStmDmgValue = 2000;
      p_oTree = p_oPop->CreateTree( fX, fY, 1, clTreePopulation::snag, 30.0 );
      p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iStmDmgValue );
    }

    //Grid (1,1): 1000 trees of Species 1 and 2, DBH 8. Damage index is 0.3.
    //1000 trees of DBH 4, Species 1, and DBH 5, Species 2.
    //1000 snags of damage 1000 and 1000 snags of damage 2000.
    fVal = 0.3;
    p_oPkg = p_oStormGrid->CreatePackageOfCell(1, 1);
    p_oPkg->SetValue(iStmDmgCode, fVal);
    fX = 9;
    fY = 9;
    fDiam = 8;
    for ( i = 0; i < 1000; i++ )
    {
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, fDiam );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::adult, fDiam );
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::sapling, 4.0 );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::sapling, 5.0 );
      iStmDmgValue = 1000;
      p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::snag, 30.0 );
      p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iStmDmgValue );
      iStmDmgValue = 2000;
      p_oTree = p_oPop->CreateTree( fX, fY, 1, clTreePopulation::snag, 30.0 );
      p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iStmDmgValue );
    }

    //Grid (1,2): 1000 trees of Species 1 and 2, DBH 8. Damage index is 1.
    //1000 trees of DBH 4, Species 1, and DBH 5, Species 2.
    //1000 snags of damage 1000 and 1000 snags of damage 2000.
    fVal = 1;
    p_oPkg = p_oStormGrid->CreatePackageOfCell(1, 2);
    p_oPkg->SetValue(iStmDmgCode, fVal);
    fX = 9;
    fY = 17;
    fDiam = 8;
    for ( i = 0; i < 1000; i++ )
    {
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, fDiam );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::adult, fDiam );
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::sapling, 4.0 );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::sapling, 5.0 );
      iStmDmgValue = 1000;
      p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::snag, 30.0 );
      p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iStmDmgValue );
      iStmDmgValue = 2000;
      p_oTree = p_oPop->CreateTree( fX, fY, 1, clTreePopulation::snag, 30.0 );
      p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iStmDmgValue );
    }

    //Grid (2,0): 1000 trees of Species 1 and 2, DBH 45. Damage index is 0.2.
    //Initial counter is 1002.
    //100 trees of DBH 4, Species 1, and DBH 5, Species 2,
    fVal = 0.2;
    p_oPkg = p_oStormGrid->CreatePackageOfCell(2, 0);
    p_oPkg->SetValue(iStmDmgCode, fVal);
    fX = 17;
    fY = 1;
    fDiam = 45;
    iStmDmgValue = 1000;
    for ( i = 0; i < 1000; i++ )
    {
      p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, fDiam );
      p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iStmDmgValue );

      p_oTree = p_oPop->CreateTree( fX, fY, 1, clTreePopulation::adult, fDiam );
      p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iStmDmgValue );

      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::sapling, 4.0 );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::sapling, 5.0 );
    }

    //Grid (2,1): 1000 trees of Species 1 and 2, DBH 15. Damage index is 0.7.
    //Initial counter is 2003.
    //100 trees of DBH 4, Species 1, and DBH 5, Species 2,
    fVal = 0.7;
    p_oPkg = p_oStormGrid->CreatePackageOfCell(2, 1);
    p_oPkg->SetValue(iStmDmgCode, fVal);
    fX = 17;
    fY = 9;
    fDiam = 15;
    iStmDmgValue = 2005;
    for ( i = 0; i < 1000; i++ )
    {
      p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, fDiam );
      p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iStmDmgValue );

      p_oTree = p_oPop->CreateTree( fX, fY, 1, clTreePopulation::adult, fDiam );
      p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iStmDmgValue );

      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::sapling, 4.0 );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::sapling, 5.0 );
    }

    for (i = 1; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
      p_oSimManager->GetBehaviorObject(i)->Action();
    }
    TestStormDamageApplierRun1Timestep1( p_oPop );
    p_oSimManager->RunSim( 1 );
    TestStormDamageApplierRun1Timestep4( p_oPop );
    p_oSimManager->RunSim( 1 );
    TestStormDamageApplierRun1Timestep5( p_oPop );
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun3()
// Tests normal processing. WriteStormDamageApplierXMLFile1() writes the parameter file. Tests
// multiple storms in one timestep.
// Aspects of the run:
//
// -- Grid resolution of "Storm Damage" is default.
// -- Run is 5 timesteps.
// -- 1 year per timestep.
// -- This behavior kills no trees.
// -- There are no snags for this behavior.
// -- The following trees will be added, with the appropriate storm triggered
// for timestep 1:
//   -- Grid (0,0): 1000 trees of Species 1 and 2, DBH 30. Damage index is 0
// and 0.
//   -- Grid (0,1): 1000 trees of Species 1 and 2, DBH 30. Damage index is 0.5
// and 0.7.
//   -- Grid (0,2): 1000 trees of Species 1 and 2, DBH 30. Damage index is 1
// and 0.
//   -- Grid (1,0): 1000 trees of Species 1 and 2, DBH 30. Damage index is 0
// and 0.2.
//   -- Grid (1,1): 1000 trees of Species 1 and 2, DBH 30. Damage index is 0.5
// and 0.3.
//   -- Grid (1,2): 1000 trees of Species 1 and 2, DBH 30. Damage index is 1
// and 0.8.
//   -- All grids get 100 trees of DBH 4, Species 1, and DBH 5, Species 2.
//
// The run proceeds for 5 timesteps and the number of trees with each damage
// counter is checked through time.
/////////////////////////////////////////////////////////////////////////////
TEST(StormDamageApplier, TestNormalProcessingRun3) {
  using namespace std;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    //Feed our file to the sim manager
    p_oSimManager->ReadFile( WriteStormDamageApplierXMLFile1() );

    //Get the tree population
    clTreePopulation * p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
    clTreeSearch * p_oAllTrees;
    clTree * p_oTree;

    //Get the "Storm Damage" grid object
    clGrid * p_oStormGrid = p_oSimManager->GetGridObject( "Storm Damage" );
    clPackage *p_oPkg;
    ASSERT_TRUE( p_oStormGrid != NULL );

    stringstream sMessage;
    float fX, fY, fDiam, fExpected, fVal;
    int iSp1Group1, iSp2Group1, iSp1Group2, iSp2Group2, iSp1Group3, iSp2Group3,
    iSnagGroup1, iSnagGroup2, iSp, iStmDmgValue,
    iStmDmgCode = p_oStormGrid->GetPackageFloatDataCode( "1dmg_index" ), i;

    ASSERT_TRUE( iStmDmgCode != -1 );

    //Grid (0,0): 1000 trees of Species 1 and 2, DBH 30. Damage index is 0 and 0.
    //1000 trees of DBH 4, Species 1, and DBH 5, Species 2.
    //1000 snags of damage 1000 and 1000 snags of damage 2000.
    fVal = 0;
    p_oPkg = p_oStormGrid->CreatePackageOfCell(0,0);
    p_oPkg->SetValue(iStmDmgCode, fVal);
    fVal = 0;
    p_oPkg = p_oStormGrid->CreatePackage(p_oPkg);
    p_oPkg->SetValue(iStmDmgCode, fVal);
    fX = 1;
    fY = 1;
    fDiam = 30;
    for ( i = 0; i < 1000; i++ )
    {
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, fDiam );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::adult, fDiam );
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::sapling, 4.0 );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::sapling, 5.0 );
      iStmDmgValue = 1000;
      p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::snag, fDiam );
      p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iStmDmgValue );
      iStmDmgValue = 2000;
      p_oTree = p_oPop->CreateTree( fX, fY, 1, clTreePopulation::snag, fDiam );
      p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iStmDmgValue );
    }

    //Grid (0,1): 1000 trees of Species 1 and 2, DBH 30. Damage index is 0.5 and
    //0.7.
    //1000 trees of DBH 4, Species 1, and DBH 5, Species 2.
    //1000 snags of damage 1000 and 1000 snags of damage 2000.
    fVal = 0.5;
    p_oPkg = p_oStormGrid->CreatePackageOfCell(0,1);
    p_oPkg->SetValue(iStmDmgCode, fVal);
    fVal = 0.7;
    p_oPkg = p_oStormGrid->CreatePackage(p_oPkg);
    p_oPkg->SetValue(iStmDmgCode, fVal);
    fX = 1;
    fY = 9;
    fDiam = 30;
    for ( i = 0; i < 1000; i++ )
    {
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, fDiam );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::adult, fDiam );
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::sapling, 4.0 );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::sapling, 5.0 );
      iStmDmgValue = 1000;
      p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::snag, fDiam );
      p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iStmDmgValue );
      iStmDmgValue = 2000;
      p_oTree = p_oPop->CreateTree( fX, fY, 1, clTreePopulation::snag, fDiam );
      p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iStmDmgValue );
    }

    //Grid (0,2): 1000 trees of Species 1 and 2, DBH 30. Damage index is 1 and 0.
    //1000 trees of DBH 4, Species 1, and DBH 5, Species 2.
    //1000 snags of damage 1000 and 1000 snags of damage 2000.
    fVal = 1.0;
    p_oPkg = p_oStormGrid->CreatePackageOfCell(0,2);
    p_oPkg->SetValue(iStmDmgCode, fVal);
    fVal = 0;
    p_oPkg = p_oStormGrid->CreatePackage(p_oPkg);
    p_oPkg->SetValue(iStmDmgCode, fVal);
    fX = 1;
    fY = 17;
    fDiam = 30;
    for ( i = 0; i < 1000; i++ )
    {
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, fDiam );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::adult, fDiam );
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::sapling, 4.0 );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::sapling, 5.0 );
      iStmDmgValue = 1000;
      p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::snag, fDiam );
      p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iStmDmgValue );
      iStmDmgValue = 2000;
      p_oTree = p_oPop->CreateTree( fX, fY, 1, clTreePopulation::snag, fDiam );
      p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iStmDmgValue );
    }

    //Grid (1,0): 1000 trees of Species 1 and 2, DBH 8. Damage index is 0 and
    // 0.2.
    //1000 trees of DBH 4, Species 1, and DBH 5, Species 2.
    //1000 snags of damage 1000 and 1000 snags of damage 2000.
    fVal = 0;
    p_oPkg = p_oStormGrid->CreatePackageOfCell(1,0);
    p_oPkg->SetValue(iStmDmgCode, fVal);
    fVal = 0.2;
    p_oPkg = p_oStormGrid->CreatePackage(p_oPkg);
    p_oPkg->SetValue(iStmDmgCode, fVal);
    fX = 9;
    fY = 1;
    fDiam = 30;
    for ( i = 0; i < 1000; i++ )
    {
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, fDiam );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::adult, fDiam );
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::sapling, 4.0 );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::sapling, 5.0 );
      iStmDmgValue = 1000;
      p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::snag, 30.0 );
      p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iStmDmgValue );
      iStmDmgValue = 2000;
      p_oTree = p_oPop->CreateTree( fX, fY, 1, clTreePopulation::snag, 30.0 );
      p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iStmDmgValue );
    }

    //Grid (1,1): 1000 trees of Species 1 and 2, DBH 8. Damage index is 0.5 and
    //0.3.
    //1000 trees of DBH 4, Species 1, and DBH 5, Species 2.
    //1000 snags of damage 1000 and 1000 snags of damage 2000.
    fVal = 0.5;
    p_oPkg = p_oStormGrid->CreatePackageOfCell(1,1);
    p_oPkg->SetValue(iStmDmgCode, fVal);
    fVal = 0.3;
    p_oPkg = p_oStormGrid->CreatePackage(p_oPkg);
    p_oPkg->SetValue(iStmDmgCode, fVal);
    fX = 9;
    fY = 9;
    fDiam = 30;
    for ( i = 0; i < 1000; i++ )
    {
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, fDiam );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::adult, fDiam );
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::sapling, 4.0 );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::sapling, 5.0 );
      iStmDmgValue = 1000;
      p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::snag, 30.0 );
      p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iStmDmgValue );
      iStmDmgValue = 2000;
      p_oTree = p_oPop->CreateTree( fX, fY, 1, clTreePopulation::snag, 30.0 );
      p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iStmDmgValue );
    }

    //Grid (1,2): 1000 trees of Species 1 and 2, DBH 8. Damage index is 1 and
    // 0.8.
    //1000 trees of DBH 4, Species 1, and DBH 5, Species 2.
    //1000 snags of damage 1000 and 1000 snags of damage 2000.
    fVal = 1;
    p_oPkg = p_oStormGrid->CreatePackageOfCell(1, 2);
    p_oPkg->SetValue(iStmDmgCode, fVal);
    fVal = 0.8;
    p_oPkg = p_oStormGrid->CreatePackage(p_oPkg);
    p_oPkg->SetValue(iStmDmgCode, fVal);
    fX = 9;
    fY = 17;
    fDiam = 30;
    for ( i = 0; i < 1000; i++ )
    {
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, fDiam );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::adult, fDiam );
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::sapling, 4.0 );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::sapling, 5.0 );
      iStmDmgValue = 1000;
      p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::snag, 30.0 );
      p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iStmDmgValue );
      iStmDmgValue = 2000;
      p_oTree = p_oPop->CreateTree( fX, fY, 1, clTreePopulation::snag, 30.0 );
      p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iStmDmgValue );
    }

    //Skip storms running
    for (i = 1; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
      p_oSimManager->GetBehaviorObject(i)->Action();
    }


    //Get all trees
    p_oAllTrees = p_oPop->Find( "all" );

    //>>>>>>>>>>>>Separate out and only do cell 0,0<<<<<<<<<<<<<<<<<<<<<<<
    //Group 1: storm damage = 0. Group 2: storm damage = 1000. Group 3:
    //storm damage = 2000.
    iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
    iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
    iSnagGroup1 = 0; iSnagGroup2 = 0;
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

        //If it's too small, it's got no damage; otherwise, count it into the
        //appropriate group
        if ( fDiam < 6 )
          EXPECT_EQ( 0, iStmDmgValue );
        else if (clTreePopulation::snag == p_oTree->GetType() && 1000 == iStmDmgValue)
          iSnagGroup1++;
        else if (clTreePopulation::snag == p_oTree->GetType() && 2000 == iStmDmgValue)
          iSnagGroup2++;
        else if ( 0 == iSp && 0 == iStmDmgValue )
          iSp1Group1++;
        else if ( 1 == iSp && 0 == iStmDmgValue )
          iSp2Group1++;
        else if ( 0 == iSp && 1000 == iStmDmgValue )
          iSp1Group2++;
        else if ( 1 == iSp && 1000 == iStmDmgValue )
          iSp2Group2++;
        else if ( 0 == iSp && 2000 == iStmDmgValue )
          iSp1Group3++;
        else if ( 1 == iSp && 2000 == iStmDmgValue )
          iSp2Group3++;
        else
        {
          //Error
          sMessage << "TestNormalProcessingRun3, timestep 1, found an unexpected " << "tree storm damage value. X: " << fX
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
    EXPECT_EQ( 1000, iSnagGroup1 );
    EXPECT_EQ( 1000, iSnagGroup2 );

    //>>>>>>>>>>>>Separate out and only do cell 0, 1<<<<<<<<<<<<<<<<<<<<<<<
    //Group 1: storm damage = 0. Group 2: storm damage = 1000. Group 3:
    //storm damage = 2000.
    iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
    iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
    iSnagGroup1 = 0; iSnagGroup2 = 0;
    p_oAllTrees->StartOver();
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

        //If it's too small, it's got no damage; otherwise, count it into the
        //appropriate group
        if ( fDiam < 6 )
          EXPECT_EQ( 0, iStmDmgValue );
        else if (clTreePopulation::snag == p_oTree->GetType() && 1000 == iStmDmgValue)
          iSnagGroup1++;
        else if (clTreePopulation::snag == p_oTree->GetType() && 2000 == iStmDmgValue)
          iSnagGroup2++;
        else if ( 0 == iSp && 0 == iStmDmgValue )
          iSp1Group1++;
        else if ( 1 == iSp && 0 == iStmDmgValue )
          iSp2Group1++;
        else if ( 0 == iSp && 1000 == iStmDmgValue )
          iSp1Group2++;
        else if ( 1 == iSp && 1000 == iStmDmgValue )
          iSp2Group2++;
        else if ( 0 == iSp && 2000 == iStmDmgValue )
          iSp1Group3++;
        else if ( 1 == iSp && 2000 == iStmDmgValue )
          iSp2Group3++;
        else
        {
          //Error
          sMessage << "TestNormalProcessingRun3, timestep 1, found an unexpected " << "tree storm damage value. X: " << fX
              << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
          FAIL() << sMessage.str();
        }
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    //Validate the counts
    EXPECT_EQ( iSp1Group1 + iSp1Group2 + iSp1Group3, 1000 );
    EXPECT_EQ( iSp2Group1 + iSp2Group2 + iSp2Group3, 1000 );
    fExpected = 38;
    EXPECT_LT( iSp1Group1 > 20 && iSp1Group1, 60 );
    fExpected = 298;
    EXPECT_LT( fabs( fExpected - iSp2Group1 ) / fExpected, 0.1 );
    fExpected = 209;
    EXPECT_LT( fabs( fExpected - iSp1Group2 ) / fExpected, 0.1 );
    fExpected = 326;
    EXPECT_LT( fabs( fExpected - iSp2Group2 ) / fExpected, 0.1 );
    fExpected = 753;
    EXPECT_LT( fabs( fExpected - iSp1Group3 ) / fExpected, 0.1 );
    fExpected = 376;
    EXPECT_LT( fabs( fExpected - iSp2Group3 ) / fExpected, 0.1 );
    EXPECT_EQ( 1000, iSnagGroup1 );
    EXPECT_EQ( 1000, iSnagGroup2 );




    //>>>>>>>>>>>>Separate out and only do cell 0, 2<<<<<<<<<<<<<<<<<<<<<<<
    //Group 1: storm damage = 0. Group 2: storm damage = 1000. Group 3:
    //storm damage = 2000.
    iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
    iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
    iSnagGroup1 = 0; iSnagGroup2 = 0;
    p_oAllTrees->StartOver();
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

        //If it's too small, it's got no damage; otherwise, count it into the
        //appropriate group
        if ( fDiam < 6 )
          EXPECT_EQ( 0, iStmDmgValue );
        else if (clTreePopulation::snag == p_oTree->GetType() && 1000 == iStmDmgValue)
          iSnagGroup1++;
        else if (clTreePopulation::snag == p_oTree->GetType() && 2000 == iStmDmgValue)
          iSnagGroup2++;
        else if ( 0 == iSp && 0 == iStmDmgValue )
          iSp1Group1++;
        else if ( 1 == iSp && 0 == iStmDmgValue )
          iSp2Group1++;
        else if ( 0 == iSp && 1000 == iStmDmgValue )
          iSp1Group2++;
        else if ( 1 == iSp && 1000 == iStmDmgValue )
          iSp2Group2++;
        else if ( 0 == iSp && 2000 == iStmDmgValue )
          iSp1Group3++;
        else if ( 1 == iSp && 2000 == iStmDmgValue )
          iSp2Group3++;
        else
        {
          //Error
          sMessage << "TestNormalProcessingRun3, timestep 1, found an unexpected " << "tree storm damage value. X: " << fX
              << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
          FAIL() << sMessage.str();
        }
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    //Validate the counts
    EXPECT_EQ( iSp1Group1 + iSp1Group2 + iSp1Group3, 1000 );
    EXPECT_EQ( iSp2Group1 + iSp2Group2 + iSp2Group3, 1000 );
    fExpected = 23;
    EXPECT_LT( iSp1Group1, 50 );
    fExpected = 218;
    EXPECT_LT( fabs( fExpected - iSp2Group1 ) / fExpected, 0.1 );
    fExpected = 69;
    EXPECT_LT( fabs( fExpected - iSp1Group2 ) / fExpected, 0.25 );
    fExpected = 257;
    EXPECT_LT( fabs( fExpected - iSp2Group2 ) / fExpected, 0.12 );
    fExpected = 908;
    EXPECT_LT( fabs( fExpected - iSp1Group3 ) / fExpected, 0.1 );
    fExpected = 530;
    EXPECT_LT( fabs( fExpected - iSp2Group3 ) / fExpected, 0.1 );
    EXPECT_EQ( 1000, iSnagGroup1 );
    EXPECT_EQ( 1000, iSnagGroup2 );




    //>>>>>>>>>>>>Separate out and only do cell 1, 0<<<<<<<<<<<<<<<<<<<<<<<
    //Group 1: storm damage = 0. Group 2: storm damage = 1000. Group 3:
    //storm damage = 2000.
    iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
    iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
    iSnagGroup1 = 0; iSnagGroup2 = 0;
    p_oAllTrees->StartOver();
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

        //If it's too small, it's got no damage; otherwise, count it into the
        //appropriate group
        if ( fDiam < 6 )
          EXPECT_EQ( 0, iStmDmgValue );
        else if (clTreePopulation::snag == p_oTree->GetType() && 1000 == iStmDmgValue)
          iSnagGroup1++;
        else if (clTreePopulation::snag == p_oTree->GetType() && 2000 == iStmDmgValue)
          iSnagGroup2++;
        else if ( 0 == iSp && 0 == iStmDmgValue )
          iSp1Group1++;
        else if ( 1 == iSp && 0 == iStmDmgValue )
          iSp2Group1++;
        else if ( 0 == iSp && 1000 == iStmDmgValue )
          iSp1Group2++;
        else if ( 1 == iSp && 1000 == iStmDmgValue )
          iSp2Group2++;
        else if ( 0 == iSp && 2000 == iStmDmgValue )
          iSp1Group3++;
        else if ( 1 == iSp && 2000 == iStmDmgValue )
          iSp2Group3++;
        else
        {
          //Error
          sMessage << "TestNormalProcessingRun3, timestep 1, found an unexpected " << "tree storm damage value. X: " << fX
              << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
          FAIL() << sMessage.str();
        }
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    EXPECT_EQ( iSp1Group1 + iSp1Group2 + iSp1Group3, 1000 );
    EXPECT_EQ( iSp2Group1 + iSp2Group2 + iSp2Group3, 1000 );
    fExpected = 730;
    EXPECT_LT( fabs( fExpected - iSp1Group1 ) / fExpected, 0.1 );
    fExpected = 849;
    EXPECT_LT( fabs( fExpected - iSp2Group1 ) / fExpected, 0.1 );
    fExpected = 191;
    EXPECT_LT( fabs( fExpected - iSp1Group2 ) / fExpected, 0.1 );
    fExpected = 98;
    EXPECT_LT( iSp2Group2 > 70 && iSp2Group2, 120 );
    fExpected = 80;
    EXPECT_LT( fabs( fExpected - iSp1Group3 ) / fExpected, 0.15 );
    fExpected = 53;
    EXPECT_LT( fabs( fExpected - iSp2Group3 ) / fExpected, 0.25 );
    EXPECT_EQ( 1000, iSnagGroup1 );
    EXPECT_EQ( 1000, iSnagGroup2 );




    //>>>>>>>>>>>>Separate out and only do cell 1, 1<<<<<<<<<<<<<<<<<<<<<<<
    //Group 1: storm damage = 0. Group 2: storm damage = 1000. Group 3:
    //storm damage = 2000.
    iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
    iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
    iSnagGroup1 = 0; iSnagGroup2 = 0;
    p_oAllTrees->StartOver();
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

        //If it's too small, it's got no damage; otherwise, count it into the
        //appropriate group
        if ( fDiam < 6 )
          EXPECT_EQ( 0, iStmDmgValue );
        else if (clTreePopulation::snag == p_oTree->GetType() && 1000 == iStmDmgValue)
          iSnagGroup1++;
        else if (clTreePopulation::snag == p_oTree->GetType() && 2000 == iStmDmgValue)
          iSnagGroup2++;
        else if ( 0 == iSp && 0 == iStmDmgValue )
          iSp1Group1++;
        else if ( 1 == iSp && 0 == iStmDmgValue )
          iSp2Group1++;
        else if ( 0 == iSp && 1000 == iStmDmgValue )
          iSp1Group2++;
        else if ( 1 == iSp && 1000 == iStmDmgValue )
          iSp2Group2++;
        else if ( 0 == iSp && 2000 == iStmDmgValue )
          iSp1Group3++;
        else if ( 1 == iSp && 2000 == iStmDmgValue )
          iSp2Group3++;
        else
        {
          //Error
          sMessage << "TestNormalProcessingRun3, timestep 1, found an unexpected " << "tree storm damage value. X: " << fX
              << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
          FAIL() << sMessage.str();
        }
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    //Validate the counts
    EXPECT_EQ( iSp1Group1 + iSp1Group2 + iSp1Group3, 1000 );
    EXPECT_EQ( iSp2Group1 + iSp2Group2 + iSp2Group3, 1000 );
    fExpected = 188;
    EXPECT_LT( fabs( fExpected - iSp1Group1 ) / fExpected, 0.1 );
    fExpected = 513;
    EXPECT_LT( fabs( fExpected - iSp2Group1 ) / fExpected, 0.1 );
    fExpected = 384;
    EXPECT_LT( fabs( fExpected - iSp1Group2 ) / fExpected, 0.1 );
    fExpected = 276;
    EXPECT_LT( fabs( fExpected - iSp2Group2 ) / fExpected, 0.1 );
    fExpected = 428;
    EXPECT_LT( fabs( fExpected - iSp1Group3 ) / fExpected, 0.1 );
    fExpected = 211;
    EXPECT_LT( fabs( fExpected - iSp2Group3 ) / fExpected, 0.1 );
    EXPECT_EQ( 1000, iSnagGroup1 );
    EXPECT_EQ( 1000, iSnagGroup2 );




    //>>>>>>>>>>>>Separate out and only do cell 1, 2<<<<<<<<<<<<<<<<<<<<<<<
    //Group 1: storm damage = 0. Group 2: storm damage = 1000. Group 3:
    //storm damage = 2000.
    iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
    iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
    iSnagGroup1 = 0; iSnagGroup2 = 0;
    p_oAllTrees->StartOver();
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

        //If it's too small, it's got no damage; otherwise, count it into the
        //appropriate group
        if ( fDiam < 6 )
          EXPECT_EQ( 0, iStmDmgValue );
        else if (clTreePopulation::snag == p_oTree->GetType() && 1000 == iStmDmgValue)
          iSnagGroup1++;
        else if (clTreePopulation::snag == p_oTree->GetType() && 2000 == iStmDmgValue)
          iSnagGroup2++;
        else if ( 0 == iSp && 0 == iStmDmgValue )
          iSp1Group1++;
        else if ( 1 == iSp && 0 == iStmDmgValue )
          iSp2Group1++;
        else if ( 0 == iSp && 1000 == iStmDmgValue )
          iSp1Group2++;
        else if ( 1 == iSp && 1000 == iStmDmgValue )
          iSp2Group2++;
        else if ( 0 == iSp && 2000 == iStmDmgValue )
          iSp1Group3++;
        else if ( 1 == iSp && 2000 == iStmDmgValue )
          iSp2Group3++;
        else
        {
          //Error
          sMessage << "TestNormalProcessingRun3, timestep 1, found an unexpected "
              << "tree storm damage value. X: " << fX  << " Y: " << fY
              << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
          FAIL() << sMessage.str();
        }
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    //Validate the counts
    EXPECT_EQ( iSp1Group1 + iSp1Group2 + iSp1Group3, 1000 );
    EXPECT_EQ( iSp2Group1 + iSp2Group2 + iSp2Group3, 1000 );
    fExpected = 2;
    EXPECT_LT( fExpected, 10 );
    fExpected = 81;
    EXPECT_LT( fabs( fExpected - iSp2Group1 ) / fExpected, 0.2 );
    fExpected = 21;
    EXPECT_LT( fabs( fExpected - iSp1Group2 ) / fExpected, 0.25 );
    fExpected = 226;
    EXPECT_LT( fabs( fExpected - iSp2Group2 ) / fExpected, 0.15 );
    fExpected = 977;
    EXPECT_LT( fabs( fExpected - iSp1Group3 ) / fExpected, 0.1 );
    fExpected = 693;
    EXPECT_LT( fabs( fExpected - iSp2Group3 ) / fExpected, 0.1 );
    EXPECT_EQ( 1000, iSnagGroup1 );
    EXPECT_EQ( 1000, iSnagGroup2 );

    p_oSimManager->RunSim( 4 );
    TestStormDamageApplierRun1Timestep5( p_oPop );
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestStormDamageApplierRun1Timestep1()
/////////////////////////////////////////////////////////////////////////////
void TestStormDamageApplierRun1Timestep1( clTreePopulation * p_oPop ) {
  using namespace std;
  clTreeSearch * p_oAllTrees;
  clTree * p_oTree;
  stringstream sMessage;
  float fX, fY, fDiam, fExpected;
  int iSp1Group1, iSp2Group1, iSp1Group2, iSp2Group2, iSp1Group3, iSp2Group3,
  iSnagGroup1, iSnagGroup2, iSp, iStmDmgValue;

  //Get all trees
  p_oAllTrees = p_oPop->Find( "all" );

  //>>>>>>>>>>>>Separate out and only do cell 0,0<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0. Group 2: storm damage = 1000. Group 3:
  //storm damage = 2000.
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  iSnagGroup1 = 0; iSnagGroup2 = 0;
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

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if ( fDiam < 6 )
      {
        EXPECT_EQ( 0, iStmDmgValue );
      }
      else if (clTreePopulation::snag == p_oTree->GetType() && 1000 == iStmDmgValue) {
        iSnagGroup1++;
      }
      else if (clTreePopulation::snag == p_oTree->GetType() && 2000 == iStmDmgValue) {
        iSnagGroup2++;
      }
      else if ( 0 == iSp && 0 == iStmDmgValue )
      {
        iSp1Group1++;
      }
      else if ( 1 == iSp && 0 == iStmDmgValue )
      {
        iSp2Group1++;
      }
      else if ( 0 == iSp && 1000 == iStmDmgValue )
      {
        iSp1Group2++;
      }
      else if ( 1 == iSp && 1000 == iStmDmgValue )
      {
        iSp2Group2++;
      }
      else if ( 0 == iSp && 2000 == iStmDmgValue )
      {
        iSp1Group3++;
      }
      else if ( 1 == iSp && 2000 == iStmDmgValue )
      {
        iSp2Group3++;
      }
      else
      {
        //Error
        sMessage << "TestNormalProcessingRun1, timestep 1, found an unexpected " << "tree storm damage value. X: " << fX
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
  EXPECT_EQ( 1000, iSnagGroup1 );
  EXPECT_EQ( 1000, iSnagGroup2 );

  //>>>>>>>>>>>>Separate out and only do cell 0, 1<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0. Group 2: storm damage = 1000. Group 3:
  //storm damage = 2000.
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  iSnagGroup1 = 0; iSnagGroup2 = 0;
  p_oAllTrees->StartOver();
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

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if ( fDiam < 6 )
      {
        EXPECT_EQ( 0, iStmDmgValue );
      }
      else if (clTreePopulation::snag == p_oTree->GetType() && 1000 == iStmDmgValue) {
        iSnagGroup1++;
      }
      else if (clTreePopulation::snag == p_oTree->GetType() && 2000 == iStmDmgValue) {
        iSnagGroup2++;
      }
      else if ( 0 == iSp && 0 == iStmDmgValue )
      {
        iSp1Group1++;
      }
      else if ( 1 == iSp && 0 == iStmDmgValue )
      {
        iSp2Group1++;
      }
      else if ( 0 == iSp && 1000 == iStmDmgValue )
      {
        iSp1Group2++;
      }
      else if ( 1 == iSp && 1000 == iStmDmgValue )
      {
        iSp2Group2++;
      }
      else if ( 0 == iSp && 2000 == iStmDmgValue )
      {
        iSp1Group3++;
      }
      else if ( 1 == iSp && 2000 == iStmDmgValue )
      {
        iSp2Group3++;
      }
      else
      {
        //Error
        sMessage << "TestNormalProcessingRun1, timestep 1, found an unexpected " << "tree storm damage value. X: " << fX
            << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
        FAIL() << sMessage.str();
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  //Validate the counts
  EXPECT_EQ( iSp1Group1 + iSp1Group2 + iSp1Group3, 1000 );
  EXPECT_EQ( iSp2Group1 + iSp2Group2 + iSp2Group3, 1000 );
  fExpected = 313;
  EXPECT_LT( fabs( fExpected - iSp1Group1 ) / fExpected, 0.1 );
  fExpected = 645;
  EXPECT_LT( fabs( fExpected - iSp2Group1 ) / fExpected, 0.1 );
  fExpected = 348;
  EXPECT_LT( fabs( fExpected - iSp1Group2 ) / fExpected, 0.1 );
  fExpected = 207;
  EXPECT_LT( fabs( fExpected - iSp2Group2 ) / fExpected, 0.11 );
  fExpected = 338;
  EXPECT_LT( fabs( fExpected - iSp1Group3 ) / fExpected, 0.1 );
  fExpected = 147;
  EXPECT_LT( fabs( fExpected - iSp2Group3 ) / fExpected, 0.15 );
  EXPECT_EQ( 1000, iSnagGroup1 );
  EXPECT_EQ( 1000, iSnagGroup2 );




  //>>>>>>>>>>>>Separate out and only do cell 0, 2<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0. Group 2: storm damage = 1000. Group 3:
  //storm damage = 2000.
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  iSnagGroup1 = 0; iSnagGroup2 = 0;
  p_oAllTrees->StartOver();
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

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if ( fDiam < 6 )
      {
        EXPECT_EQ( 0, iStmDmgValue );
      }
      else if (clTreePopulation::snag == p_oTree->GetType() && 1000 == iStmDmgValue) {
        iSnagGroup1++;
      }
      else if (clTreePopulation::snag == p_oTree->GetType() && 2000 == iStmDmgValue) {
        iSnagGroup2++;
      }
      else if ( 0 == iSp && 0 == iStmDmgValue )
      {
        iSp1Group1++;
      }
      else if ( 1 == iSp && 0 == iStmDmgValue )
      {
        iSp2Group1++;
      }
      else if ( 0 == iSp && 1000 == iStmDmgValue )
      {
        iSp1Group2++;
      }
      else if ( 1 == iSp && 1000 == iStmDmgValue )
      {
        iSp2Group2++;
      }
      else if ( 0 == iSp && 2000 == iStmDmgValue )
      {
        iSp1Group3++;
      }
      else if ( 1 == iSp && 2000 == iStmDmgValue )
      {
        iSp2Group3++;
      }
      else
      {
        //Error
        sMessage << "TestNormalProcessingRun1, timestep 1, found an unexpected " << "tree storm damage value. X: " << fX
            << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
        FAIL() << sMessage.str();
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  //Validate the counts
  EXPECT_EQ( iSp1Group1 + iSp1Group2 + iSp1Group3, 1000 );
  EXPECT_EQ( iSp2Group1 + iSp2Group2 + iSp2Group3, 1000 );
  fExpected = 23;
  EXPECT_LT( iSp1Group1 , 40 );
  fExpected = 218;
  EXPECT_LT( fabs( fExpected - iSp2Group1 ) / fExpected, 0.1 );
  fExpected = 68;
  EXPECT_LT( fabs( fExpected - iSp1Group2 ) / fExpected, 0.25 );
  fExpected = 252;
  EXPECT_LT( fabs( fExpected - iSp2Group2 ) / fExpected, 0.1 );
  fExpected = 908;
  EXPECT_LT( fabs( fExpected - iSp1Group3 ) / fExpected, 0.1 );
  fExpected = 529;
  EXPECT_LT( fabs( fExpected - iSp2Group3 ) / fExpected, 0.1 );
  EXPECT_EQ( 1000, iSnagGroup1 );
  EXPECT_EQ( 1000, iSnagGroup2 );




  //>>>>>>>>>>>>Separate out and only do cell 1, 0<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0. Group 2: storm damage = 1000. Group 3:
  //storm damage = 2000.
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  iSnagGroup1 = 0; iSnagGroup2 = 0;
  p_oAllTrees->StartOver();
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

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if ( fDiam < 6 )
      {
        EXPECT_EQ( 0, iStmDmgValue );
      }
      else if (clTreePopulation::snag == p_oTree->GetType() && 1000 == iStmDmgValue) {
        iSnagGroup1++;
      }
      else if (clTreePopulation::snag == p_oTree->GetType() && 2000 == iStmDmgValue) {
        iSnagGroup2++;
      }
      else if ( 0 == iSp && 0 == iStmDmgValue )
      {
        iSp1Group1++;
      }
      else if ( 1 == iSp && 0 == iStmDmgValue )
      {
        iSp2Group1++;
      }
      else if ( 0 == iSp && 1000 == iStmDmgValue )
      {
        iSp1Group2++;
      }
      else if ( 1 == iSp && 1000 == iStmDmgValue )
      {
        iSp2Group2++;
      }
      else if ( 0 == iSp && 2000 == iStmDmgValue )
      {
        iSp1Group3++;
      }
      else if ( 1 == iSp && 2000 == iStmDmgValue )
      {
        iSp2Group3++;
      }
      else
      {
        //Error
        sMessage << "TestNormalProcessingRun1, timestep 1, found an unexpected " << "tree storm damage value. X: " << fX
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
  EXPECT_EQ( 1000, iSnagGroup1 );
  EXPECT_EQ( 1000, iSnagGroup2 );




  //>>>>>>>>>>>>Separate out and only do cell 1, 1<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0. Group 2: storm damage = 1000. Group 3:
  //storm damage = 2000.
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  iSnagGroup1 = 0; iSnagGroup2 = 0;
  p_oAllTrees->StartOver();
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

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if ( fDiam < 6 )
      {
        EXPECT_EQ( 0, iStmDmgValue );
      }
      else if (clTreePopulation::snag == p_oTree->GetType() && 1000 == iStmDmgValue) {
        iSnagGroup1++;
      }
      else if (clTreePopulation::snag == p_oTree->GetType() && 2000 == iStmDmgValue) {
        iSnagGroup2++;
      }
      else if ( 0 == iSp && 0 == iStmDmgValue )
      {
        iSp1Group1++;
      }
      else if ( 1 == iSp && 0 == iStmDmgValue )
      {
        iSp2Group1++;
      }
      else if ( 0 == iSp && 1000 == iStmDmgValue )
      {
        iSp1Group2++;
      }
      else if ( 1 == iSp && 1000 == iStmDmgValue )
      {
        iSp2Group2++;
      }
      else if ( 0 == iSp && 2000 == iStmDmgValue )
      {
        iSp1Group3++;
      }
      else if ( 1 == iSp && 2000 == iStmDmgValue )
      {
        iSp2Group3++;
      }
      else
      {
        //Error
        sMessage << "TestNormalProcessingRun1, timestep 1, found an unexpected " << "tree storm damage value. X: " << fX
            << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
        FAIL() << sMessage.str();
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  //Validate the counts
  EXPECT_EQ( iSp1Group1 + iSp1Group2 + iSp1Group3, 1000 );
  EXPECT_EQ( iSp2Group1 + iSp2Group2 + iSp2Group3, 1000 );
  fExpected = 829;
  EXPECT_LT( fabs( fExpected - iSp1Group1 ) / fExpected, 0.1 );
  fExpected = 851;
  EXPECT_LT( fabs( fExpected - iSp2Group1 ) / fExpected, 0.1 );
  fExpected = 124;
  EXPECT_LT( fabs( fExpected - iSp1Group2 ) / fExpected, 0.1 );
  fExpected = 96;
  EXPECT_LT( fabs( fExpected - iSp2Group2 ) / fExpected, 0.25 );
  fExpected = 45;
  EXPECT_LT( fabs( fExpected - iSp1Group3 ) / fExpected, 0.25 );
  fExpected = 54;
  EXPECT_LT( fabs( fExpected - iSp2Group3 ) / fExpected, 0.3 );
  EXPECT_EQ( 1000, iSnagGroup1 );
  EXPECT_EQ( 1000, iSnagGroup2 );




  //>>>>>>>>>>>>Separate out and only do cell 1, 2<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0. Group 2: storm damage = 1000. Group 3:
  //storm damage = 2000.
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  iSnagGroup1 = 0; iSnagGroup2 = 0;
  p_oAllTrees->StartOver();
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

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if ( fDiam < 6 )
      {
        EXPECT_EQ( 0, iStmDmgValue );
      }
      else if (clTreePopulation::snag == p_oTree->GetType() && 1000 == iStmDmgValue) {
        iSnagGroup1++;
      }
      else if (clTreePopulation::snag == p_oTree->GetType() && 2000 == iStmDmgValue) {
        iSnagGroup2++;
      }
      else if ( 0 == iSp && 0 == iStmDmgValue )
      {
        iSp1Group1++;
      }
      else if ( 1 == iSp && 0 == iStmDmgValue )
      {
        iSp2Group1++;
      }
      else if ( 0 == iSp && 1000 == iStmDmgValue )
      {
        iSp1Group2++;
      }
      else if ( 1 == iSp && 1000 == iStmDmgValue )
      {
        iSp2Group2++;
      }
      else if ( 0 == iSp && 2000 == iStmDmgValue )
      {
        iSp1Group3++;
      }
      else if ( 1 == iSp && 2000 == iStmDmgValue )
      {
        iSp2Group3++;
      }
      else
      {
        //Error
        sMessage << "TestNormalProcessingRun1, timestep 1, found an unexpected " << "tree storm damage value. X: " << fX
            << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
        FAIL() << sMessage.str();
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  //Validate the counts
  EXPECT_EQ( iSp1Group1 + iSp1Group2 + iSp1Group3, 1000 );
  EXPECT_EQ( iSp2Group1 + iSp2Group2 + iSp2Group3, 1000 );
  fExpected = 548;
  EXPECT_LT( fabs( fExpected - iSp1Group1 ) / fExpected, 0.1 );
  fExpected = 511;
  EXPECT_LT( fabs( fExpected - iSp2Group1 ) / fExpected, 0.1 );
  fExpected = 290;
  EXPECT_LT( fabs( fExpected - iSp1Group2 ) / fExpected, 0.1 );
  fExpected = 257;
  EXPECT_LT( fabs( fExpected - iSp2Group2 ) / fExpected, 0.25 );
  fExpected = 161;
  EXPECT_LT( fabs( fExpected - iSp1Group3 ) / fExpected, 0.25 );
  fExpected = 231;
  EXPECT_LT( fabs( fExpected - iSp2Group3 ) / fExpected, 0.3 );
  EXPECT_EQ( 1000, iSnagGroup1 );
  EXPECT_EQ( 1000, iSnagGroup2 );




  //>>>>>>>>>>>>Separate out and only do cell 2, 0<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 1001. Group 2: storm damage = 1000. Group 3:
  //storm damage = 2000.
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  p_oAllTrees->StartOver();
  p_oTree = p_oAllTrees->NextTree();
  while ( p_oTree )
  {
    iSp = p_oTree->GetSpecies();

    //Get X and Y
    p_oTree->GetValue( p_oPop->GetXCode( iSp, p_oTree->GetType() ), & fX );
    p_oTree->GetValue( p_oPop->GetYCode( iSp, p_oTree->GetType() ), & fY );

    //Get storm damage counter
    p_oTree->GetValue( p_oPop->GetIntDataCode( "stm_dmg", iSp, p_oTree->GetType() ), & iStmDmgValue );

    if ( fY < 8 && fX > 16 && fX < 24 )
    {
      //Make sure this ain't no snag
      ASSERT_TRUE(clTreePopulation::snag != p_oTree->GetType());

      //Get DBH
      p_oTree->GetValue( p_oPop->GetDbhCode( iSp, p_oTree->GetType() ), & fDiam );

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if ( fDiam < 6 )
      {
        EXPECT_EQ( 0, iStmDmgValue );
      }
      else if ( 0 == iSp && 1003 == iStmDmgValue )
      {
        iSp1Group1++;
      }
      else if ( 1 == iSp && 1003 == iStmDmgValue )
      {
        iSp2Group1++;
      }
      else if ( 0 == iSp && 1000 == iStmDmgValue )
      {
        iSp1Group2++;
      }
      else if ( 1 == iSp && 1000 == iStmDmgValue )
      {
        iSp2Group2++;
      }
      else if ( 0 == iSp && 2000 == iStmDmgValue )
      {
        iSp1Group3++;
      }
      else if ( 1 == iSp && 2000 == iStmDmgValue )
      {
        iSp2Group3++;
      }
      else
      {
        //Error
        sMessage << "TestNormalProcessingRun1, timestep 1, found an unexpected " << "tree storm damage value. X: " << fX
            << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
        FAIL() << sMessage.str();
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  //Validate the counts - greater tolerance for low numbers
  EXPECT_EQ( iSp1Group1 + iSp1Group2 + iSp1Group3, 1000 );
  EXPECT_EQ( iSp2Group1 + iSp2Group2 + iSp2Group3, 1000 );
  fExpected = 627;
  EXPECT_LT( fabs( fExpected - iSp1Group1 ) / fExpected, 0.1 );
  fExpected = 834;
  EXPECT_LT( fabs( fExpected - iSp2Group1 ) / fExpected, 0.1 );
  fExpected = 251;
  EXPECT_LT( fabs( fExpected - iSp1Group2 ) / fExpected, 0.1 );
  fExpected = 106;
  EXPECT_LT( fabs( fExpected - iSp2Group2 ) / fExpected, 0.3 );
  fExpected = 121;
  EXPECT_LT( fabs( fExpected - iSp1Group3 ) / fExpected, 0.16 );
  fExpected = 58;
  EXPECT_LT( fabs( fExpected - iSp2Group3 ) / fExpected, 0.2 );





  //>>>>>>>>>>>>Separate out and only do cell 2, 1<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 2002. Group 2: storm damage = 2000.
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0; iSp2Group2 = 0;
  p_oAllTrees->StartOver();
  p_oTree = p_oAllTrees->NextTree();
  while ( p_oTree )
  {
    iSp = p_oTree->GetSpecies();

    //Get X and Y
    p_oTree->GetValue( p_oPop->GetXCode( iSp, p_oTree->GetType() ), & fX );
    p_oTree->GetValue( p_oPop->GetYCode( iSp, p_oTree->GetType() ), & fY );

    //Get storm damage counter
    p_oTree->GetValue( p_oPop->GetIntDataCode( "stm_dmg", iSp, p_oTree->GetType() ), & iStmDmgValue );

    if ( fY > 8 && fY < 16 && fX > 16 && fX < 24 )
    {
      //Make sure this ain't no snag
      ASSERT_TRUE(clTreePopulation::snag != p_oTree->GetType());

      //Get DBH
      p_oTree->GetValue( p_oPop->GetDbhCode( iSp, p_oTree->GetType() ), & fDiam );

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if ( fDiam < 6 )
      {
        EXPECT_EQ( 0, iStmDmgValue );
      }
      else if ( 0 == iSp && 0 == iStmDmgValue )
      {
        iSp1Group1++;
      }
      else if ( 1 == iSp && 0 == iStmDmgValue )
      {
        iSp2Group1++;
      }
      else if ( 0 == iSp && 2000 == iStmDmgValue )
      {
        iSp1Group2++;
      }
      else if ( 1 == iSp && 2000 == iStmDmgValue )
      {
        iSp2Group2++;
      }
      else
      {
        //Error
        sMessage << "TestNormalProcessingRun1, timestep 1, found an unexpected " << "tree storm damage value. X: " << fX
            << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
        FAIL() << sMessage.str();
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  //Validate the counts
  EXPECT_EQ( iSp1Group1 + iSp1Group2, 1000 );
  EXPECT_EQ( iSp2Group1 + iSp2Group2, 1000 );
  fExpected = 450;
  EXPECT_LT( fabs( fExpected - iSp1Group1 ) / fExpected, 0.1 );
  fExpected = 594;
  EXPECT_LT( fabs( fExpected - iSp2Group1 ) / fExpected, 0.1 );
  fExpected = 538;
  EXPECT_LT( fabs( fExpected - iSp1Group2 ) / fExpected, 0.1 );
  fExpected = 404;
  EXPECT_LT( fabs( fExpected - iSp2Group2 ) / fExpected, 0.1 );
}

/////////////////////////////////////////////////////////////////////////////
// TestStormDamageApplierRun1Timestep2()
/////////////////////////////////////////////////////////////////////////////
void TestStormDamageApplierRun1Timestep2( clTreePopulation * p_oPop )
{
  using namespace std;
  clTreeSearch * p_oAllTrees;
  clTree * p_oTree;
  stringstream sMessage;
  float fX, fY, fDiam, fExpected;
  int iSp1Group1, iSp2Group1, iSp1Group2, iSp2Group2, iSp1Group3, iSp2Group3,
  iSnagGroup1, iSnagGroup2, iSp, iStmDmgValue;

  //Get all trees
  p_oAllTrees = p_oPop->Find( "all" );

  //>>>>>>>>>>>>Separate out and only do cell 0,0<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0. Group 2: storm damage = 1001. Group 3:
  //storm damage = 2001.
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  iSnagGroup1 = 0; iSnagGroup2 = 0;
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

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if ( fDiam < 6 )
      {
        EXPECT_EQ( 0, iStmDmgValue );
      }
      else if (clTreePopulation::snag == p_oTree->GetType() && 1000 == iStmDmgValue) {
        iSnagGroup1++;
      }
      else if (clTreePopulation::snag == p_oTree->GetType() && 2000 == iStmDmgValue) {
        iSnagGroup2++;
      }
      else if ( 0 == iSp && 0 == iStmDmgValue )
      {
        iSp1Group1++;
      }
      else if ( 1 == iSp && 0 == iStmDmgValue )
      {
        iSp2Group1++;
      }
      else if ( 0 == iSp && 1001 == iStmDmgValue )
      {
        iSp1Group2++;
      }
      else if ( 1 == iSp && 1001 == iStmDmgValue )
      {
        iSp2Group2++;
      }
      else if ( 0 == iSp && 2001 == iStmDmgValue )
      {
        iSp1Group3++;
      }
      else if ( 1 == iSp && 2001 == iStmDmgValue )
      {
        iSp2Group3++;
      }
      else
      {
        //Error
        sMessage << "TestNormalProcessingRun1, timestep 2, found an unexpected " << "tree storm damage value. X: " << fX
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
  EXPECT_EQ( 1000, iSnagGroup1 );
  EXPECT_EQ( 1000, iSnagGroup2 );

  //>>>>>>>>>>>>Separate out and only do cell 0, 1<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0. Group 2: storm damage = 1001. Group 3:
  //storm damage = 2001.
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  iSnagGroup1 = 0; iSnagGroup2 = 0;
  p_oAllTrees->StartOver();
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

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if ( fDiam < 6 )
      {
        EXPECT_EQ( 0, iStmDmgValue );
      }
      else if (clTreePopulation::snag == p_oTree->GetType() && 1000 == iStmDmgValue) {
        iSnagGroup1++;
      }
      else if (clTreePopulation::snag == p_oTree->GetType() && 2000 == iStmDmgValue) {
        iSnagGroup2++;
      }
      else if ( 0 == iSp && 0 == iStmDmgValue )
      {
        iSp1Group1++;
      }
      else if ( 1 == iSp && 0 == iStmDmgValue )
      {
        iSp2Group1++;
      }
      else if ( 0 == iSp && 1001 == iStmDmgValue )
      {
        iSp1Group2++;
      }
      else if ( 1 == iSp && 1001 == iStmDmgValue )
      {
        iSp2Group2++;
      }
      else if ( 0 == iSp && 2001 == iStmDmgValue )
      {
        iSp1Group3++;
      }
      else if ( 1 == iSp && 2001 == iStmDmgValue )
      {
        iSp2Group3++;
      }
      else
      {
        //Error
        sMessage << "TestNormalProcessingRun1, timestep 2, found an unexpected " << "tree storm damage value. X: " << fX
            << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
        FAIL() << sMessage.str();
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  //Validate the counts
  EXPECT_EQ( iSp1Group1 + iSp1Group2 + iSp1Group3, 1000 );
  EXPECT_EQ( iSp2Group1 + iSp2Group2 + iSp2Group3, 1000 );
  fExpected = 313;
  EXPECT_LT( fabs( fExpected - iSp1Group1 ) / fExpected, 0.1 );
  fExpected = 645;
  EXPECT_LT( fabs( fExpected - iSp2Group1 ) / fExpected, 0.1 );
  fExpected = 348;
  EXPECT_LT( fabs( fExpected - iSp1Group2 ) / fExpected, 0.1 );
  fExpected = 207;
  EXPECT_LT( fabs( fExpected - iSp2Group2 ) / fExpected, 0.11 );
  fExpected = 338;
  EXPECT_LT( fabs( fExpected - iSp1Group3 ) / fExpected, 0.1 );
  fExpected = 147;
  EXPECT_LT( fabs( fExpected - iSp2Group3 ) / fExpected, 0.15 );
  EXPECT_EQ( 1000, iSnagGroup1 );
  EXPECT_EQ( 1000, iSnagGroup2 );




  //>>>>>>>>>>>>Separate out and only do cell 0, 2<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0. Group 2: storm damage = 1001. Group 3:
  //storm damage = 2001.
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  iSnagGroup1 = 0; iSnagGroup2 = 0;
  p_oAllTrees->StartOver();
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

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if ( fDiam < 6 )
      {
        EXPECT_EQ( 0, iStmDmgValue );
      }
      else if (clTreePopulation::snag == p_oTree->GetType() && 1000 == iStmDmgValue) {
        iSnagGroup1++;
      }
      else if (clTreePopulation::snag == p_oTree->GetType() && 2000 == iStmDmgValue) {
        iSnagGroup2++;
      }
      else if ( 0 == iSp && 0 == iStmDmgValue )
      {
        iSp1Group1++;
      }
      else if ( 1 == iSp && 0 == iStmDmgValue )
      {
        iSp2Group1++;
      }
      else if ( 0 == iSp && 1001 == iStmDmgValue )
      {
        iSp1Group2++;
      }
      else if ( 1 == iSp && 1001 == iStmDmgValue )
      {
        iSp2Group2++;
      }
      else if ( 0 == iSp && 2001 == iStmDmgValue )
      {
        iSp1Group3++;
      }
      else if ( 1 == iSp && 2001 == iStmDmgValue )
      {
        iSp2Group3++;
      }
      else
      {
        //Error
        sMessage << "TestNormalProcessingRun1, timestep 2, found an unexpected " << "tree storm damage value. X: " << fX
            << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
        FAIL() << sMessage.str();
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  //Validate the counts
  EXPECT_EQ( iSp1Group1 + iSp1Group2 + iSp1Group3, 1000 );
  EXPECT_EQ( iSp2Group1 + iSp2Group2 + iSp2Group3, 1000 );
  fExpected = 23;
  EXPECT_LT( iSp1Group1 , 40 );
  fExpected = 218;
  EXPECT_LT( fabs( fExpected - iSp2Group1 ) / fExpected, 0.1 );
  fExpected = 68;
  EXPECT_LT( fabs( fExpected - iSp1Group2 ) / fExpected, 0.25 );
  fExpected = 252;
  EXPECT_LT( fabs( fExpected - iSp2Group2 ) / fExpected, 0.1 );
  fExpected = 908;
  EXPECT_LT( fabs( fExpected - iSp1Group3 ) / fExpected, 0.1 );
  fExpected = 529;
  EXPECT_LT( fabs( fExpected - iSp2Group3 ) / fExpected, 0.1 );
  EXPECT_EQ( 1000, iSnagGroup1 );
  EXPECT_EQ( 1000, iSnagGroup2 );




  //>>>>>>>>>>>>Separate out and only do cell 1, 0<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0. Group 2: storm damage = 1001. Group 3:
  //storm damage = 2001.
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  iSnagGroup1 = 0; iSnagGroup2 = 0;
  p_oAllTrees->StartOver();
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

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if ( fDiam < 6 )
      {
        EXPECT_EQ( 0, iStmDmgValue );
      }
      else if (clTreePopulation::snag == p_oTree->GetType() && 1000 == iStmDmgValue) {
        iSnagGroup1++;
      }
      else if (clTreePopulation::snag == p_oTree->GetType() && 2000 == iStmDmgValue) {
        iSnagGroup2++;
      }
      else if ( 0 == iSp && 0 == iStmDmgValue )
      {
        iSp1Group1++;
      }
      else if ( 1 == iSp && 0 == iStmDmgValue )
      {
        iSp2Group1++;
      }
      else if ( 0 == iSp && 1001 == iStmDmgValue )
      {
        iSp1Group2++;
      }
      else if ( 1 == iSp && 1001 == iStmDmgValue )
      {
        iSp2Group2++;
      }
      else if ( 0 == iSp && 2001 == iStmDmgValue )
      {
        iSp1Group3++;
      }
      else if ( 1 == iSp && 2001 == iStmDmgValue )
      {
        iSp2Group3++;
      }
      else
      {
        //Error
        sMessage << "TestNormalProcessingRun1, timestep 2, found an unexpected " << "tree storm damage value. X: " << fX
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
  EXPECT_EQ( 1000, iSnagGroup1 );
  EXPECT_EQ( 1000, iSnagGroup2 );




  //>>>>>>>>>>>>Separate out and only do cell 1, 1<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0. Group 2: storm damage = 1001. Group 3:
  //storm damage = 2001.
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  iSnagGroup1 = 0; iSnagGroup2 = 0;
  p_oAllTrees->StartOver();
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

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if ( fDiam < 6 )
      {
        EXPECT_EQ( 0, iStmDmgValue );
      }
      else if (clTreePopulation::snag == p_oTree->GetType() && 1000 == iStmDmgValue) {
        iSnagGroup1++;
      }
      else if (clTreePopulation::snag == p_oTree->GetType() && 2000 == iStmDmgValue) {
        iSnagGroup2++;
      }
      else if ( 0 == iSp && 0 == iStmDmgValue )
      {
        iSp1Group1++;
      }
      else if ( 1 == iSp && 0 == iStmDmgValue )
      {
        iSp2Group1++;
      }
      else if ( 0 == iSp && 1001 == iStmDmgValue )
      {
        iSp1Group2++;
      }
      else if ( 1 == iSp && 1001 == iStmDmgValue )
      {
        iSp2Group2++;
      }
      else if ( 0 == iSp && 2001 == iStmDmgValue )
      {
        iSp1Group3++;
      }
      else if ( 1 == iSp && 2001 == iStmDmgValue )
      {
        iSp2Group3++;
      }
      else
      {
        //Error
        sMessage << "TestNormalProcessingRun1, timestep 2, found an unexpected " << "tree storm damage value. X: " << fX
            << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
        FAIL() << sMessage.str();
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  //Validate the counts
  EXPECT_EQ( iSp1Group1 + iSp1Group2 + iSp1Group3, 1000 );
  EXPECT_EQ( iSp2Group1 + iSp2Group2 + iSp2Group3, 1000 );
  fExpected = 829;
  EXPECT_LT( fabs( fExpected - iSp1Group1 ) / fExpected, 0.1 );
  fExpected = 851;
  EXPECT_LT( fabs( fExpected - iSp2Group1 ) / fExpected, 0.1 );
  fExpected = 124;
  EXPECT_LT( fabs( fExpected - iSp1Group2 ) / fExpected, 0.1 );
  fExpected = 96;
  EXPECT_LT( fabs( fExpected - iSp2Group2 ) / fExpected, 0.25 );
  fExpected = 45;
  EXPECT_LT( fabs( fExpected - iSp1Group3 ) / fExpected, 0.25 );
  fExpected = 54;
  EXPECT_LT( fabs( fExpected - iSp2Group3 ) / fExpected, 0.3 );
  EXPECT_EQ( 1000, iSnagGroup1 );
  EXPECT_EQ( 1000, iSnagGroup2 );





  //>>>>>>>>>>>>Separate out and only do cell 1, 2<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0. Group 2: storm damage = 1001. Group 3:
  //storm damage = 2001.
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  iSnagGroup1 = 0; iSnagGroup2 = 0;
  p_oAllTrees->StartOver();
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

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if ( fDiam < 6 )
      {
        EXPECT_EQ( 0, iStmDmgValue );
      }
      else if (clTreePopulation::snag == p_oTree->GetType() && 1000 == iStmDmgValue) {
        iSnagGroup1++;
      }
      else if (clTreePopulation::snag == p_oTree->GetType() && 2000 == iStmDmgValue) {
        iSnagGroup2++;
      }
      else if ( 0 == iSp && 0 == iStmDmgValue )
      {
        iSp1Group1++;
      }
      else if ( 1 == iSp && 0 == iStmDmgValue )
      {
        iSp2Group1++;
      }
      else if ( 0 == iSp && 1001 == iStmDmgValue )
      {
        iSp1Group2++;
      }
      else if ( 1 == iSp && 1001 == iStmDmgValue )
      {
        iSp2Group2++;
      }
      else if ( 0 == iSp && 2001 == iStmDmgValue )
      {
        iSp1Group3++;
      }
      else if ( 1 == iSp && 2001 == iStmDmgValue )
      {
        iSp2Group3++;
      }
      else
      {
        //Error
        sMessage << "TestNormalProcessingRun1, timestep 2, found an unexpected " << "tree storm damage value. X: " << fX
            << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
        FAIL() << sMessage.str();
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  //Validate the counts
  EXPECT_EQ( iSp1Group1 + iSp1Group2 + iSp1Group3, 1000 );
  EXPECT_EQ( iSp2Group1 + iSp2Group2 + iSp2Group3, 1000 );
  fExpected = 548;
  EXPECT_LT( fabs( fExpected - iSp1Group1 ) / fExpected, 0.1 );
  fExpected = 511;
  EXPECT_LT( fabs( fExpected - iSp2Group1 ) / fExpected, 0.1 );
  fExpected = 290;
  EXPECT_LT( fabs( fExpected - iSp1Group2 ) / fExpected, 0.1 );
  fExpected = 257;
  EXPECT_LT( fabs( fExpected - iSp2Group2 ) / fExpected, 0.1 );
  fExpected = 161;
  EXPECT_LT( fabs( fExpected - iSp1Group3 ) / fExpected, 0.1 );
  fExpected = 231;
  EXPECT_LT( fabs( fExpected - iSp2Group3 ) / fExpected, 0.25 );
  EXPECT_EQ( 1000, iSnagGroup1 );
  EXPECT_EQ( 1000, iSnagGroup2 );




  //>>>>>>>>>>>>Separate out and only do cell 2, 0<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0. Group 2: storm damage = 1001. Group 3:
  //storm damage = 2001.
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  p_oAllTrees->StartOver();
  p_oTree = p_oAllTrees->NextTree();
  while ( p_oTree )
  {
    iSp = p_oTree->GetSpecies();

    //Get X and Y
    p_oTree->GetValue( p_oPop->GetXCode( iSp, p_oTree->GetType() ), & fX );
    p_oTree->GetValue( p_oPop->GetYCode( iSp, p_oTree->GetType() ), & fY );

    //Get storm damage counter
    p_oTree->GetValue( p_oPop->GetIntDataCode( "stm_dmg", iSp, p_oTree->GetType() ), & iStmDmgValue );

    if ( fY < 8 && fX > 16 && fX < 24 )
    {
      //Make sure this ain't no snag
      ASSERT_TRUE(clTreePopulation::snag != p_oTree->GetType());

      //Get DBH
      p_oTree->GetValue( p_oPop->GetDbhCode( iSp, p_oTree->GetType() ), & fDiam );

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if ( fDiam < 6 )
      {
        EXPECT_EQ( 0, iStmDmgValue );
      }
      else if ( 0 == iSp && 0 == iStmDmgValue )
      {
        iSp1Group1++;
      }
      else if ( 1 == iSp && 0 == iStmDmgValue )
      {
        iSp2Group1++;
      }
      else if ( 0 == iSp && 1001 == iStmDmgValue )
      {
        iSp1Group2++;
      }
      else if ( 1 == iSp && 1001 == iStmDmgValue )
      {
        iSp2Group2++;
      }
      else if ( 0 == iSp && 2001 == iStmDmgValue )
      {
        iSp1Group3++;
      }
      else if ( 1 == iSp && 2001 == iStmDmgValue )
      {
        iSp2Group3++;
      }
      else
      {
        //Error
        sMessage << "TestNormalProcessingRun1, timestep 2, found an unexpected " << "tree storm damage value. X: " << fX
            << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
        FAIL() << sMessage.str();
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  EXPECT_EQ( iSp1Group1 + iSp1Group2 + iSp1Group3, 1000 );
  EXPECT_EQ( iSp2Group1 + iSp2Group2 + iSp2Group3, 1000 );
  fExpected = 627;
  EXPECT_LT( fabs( fExpected - iSp1Group1 ) / fExpected, 0.1 );
  fExpected = 834;
  EXPECT_LT( fabs( fExpected - iSp2Group1 ) / fExpected, 0.1 );
  fExpected = 251;
  EXPECT_LT( fabs( fExpected - iSp1Group2 ) / fExpected, 0.1 );
  fExpected = 106;
  EXPECT_LT( fabs( fExpected - iSp2Group2 ) / fExpected, 0.3 );
  fExpected = 121;
  EXPECT_LT( fabs( fExpected - iSp1Group3 ) / fExpected, 0.16 );
  fExpected = 58;
  EXPECT_LT( fabs( fExpected - iSp2Group3 ) / fExpected, 0.2 );





  //>>>>>>>>>>>>Separate out and only do cell 2, 1<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0. Group 2: storm damage = 2001.
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0; iSp2Group2 = 0;
  p_oAllTrees->StartOver();
  p_oTree = p_oAllTrees->NextTree();
  while ( p_oTree )
  {
    iSp = p_oTree->GetSpecies();

    //Get X and Y
    p_oTree->GetValue( p_oPop->GetXCode( iSp, p_oTree->GetType() ), & fX );
    p_oTree->GetValue( p_oPop->GetYCode( iSp, p_oTree->GetType() ), & fY );

    //Get storm damage counter
    p_oTree->GetValue( p_oPop->GetIntDataCode( "stm_dmg", iSp, p_oTree->GetType() ), & iStmDmgValue );

    if ( fY > 8 && fY < 16 && fX > 16 && fX < 24 )
    {
      //Make sure this ain't no snag
      ASSERT_TRUE(clTreePopulation::snag != p_oTree->GetType());

      //Get DBH
      p_oTree->GetValue( p_oPop->GetDbhCode( iSp, p_oTree->GetType() ), & fDiam );

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if ( fDiam < 6 )
      {
        EXPECT_EQ( 0, iStmDmgValue );
      }
      else if ( 0 == iSp && 0 == iStmDmgValue )
      {
        iSp1Group1++;
      }
      else if ( 1 == iSp && 0 == iStmDmgValue )
      {
        iSp2Group1++;
      }
      else if ( 0 == iSp && 2001 == iStmDmgValue )
      {
        iSp1Group2++;
      }
      else if ( 1 == iSp && 2001 == iStmDmgValue )
      {
        iSp2Group2++;
      }
      else
      {
        //Error
        sMessage << "TestNormalProcessingRun1, timestep 2, found an unexpected " << "tree storm damage value. X: " << fX
            << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
        FAIL() << sMessage.str();
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  //Validate the counts
  EXPECT_EQ( iSp1Group1 + iSp1Group2, 1000 );
  EXPECT_EQ( iSp2Group1 + iSp2Group2, 1000 );
  fExpected = 450;
  EXPECT_LT( fabs( fExpected - iSp1Group1 ) / fExpected, 0.1 );
  fExpected = 594;
  EXPECT_LT( fabs( fExpected - iSp2Group1 ) / fExpected, 0.1 );
  fExpected = 538;
  EXPECT_LT( fabs( fExpected - iSp1Group2 ) / fExpected, 0.1 );
  fExpected = 404;
  EXPECT_LT( fabs( fExpected - iSp2Group2 ) / fExpected, 0.1 );
}

/////////////////////////////////////////////////////////////////////////////
// TestStormDamageApplierRun1Timestep3()
/////////////////////////////////////////////////////////////////////////////
void TestStormDamageApplierRun1Timestep3( clTreePopulation * p_oPop )
{
  using namespace std;
  clTreeSearch * p_oAllTrees;
  clTree * p_oTree;
  stringstream sMessage;
  float fX, fY, fDiam, fExpected;
  int iSp1Group1, iSp2Group1, iSp1Group2, iSp2Group2, iSp1Group3, iSp2Group3,
  iSnagGroup1, iSnagGroup2, iSp, iStmDmgValue;

  //Get all trees
  p_oAllTrees = p_oPop->Find( "all" );

  //>>>>>>>>>>>>Separate out and only do cell 0,0<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0. Group 2: storm damage = 1002. Group 3:
  //storm damage = 2002.
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  iSnagGroup1 = 0; iSnagGroup2 = 0;
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

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if ( fDiam < 6 )
      {
        EXPECT_EQ( 0, iStmDmgValue );
      }
      else if (clTreePopulation::snag == p_oTree->GetType() && 1000 == iStmDmgValue) {
        iSnagGroup1++;
      }
      else if (clTreePopulation::snag == p_oTree->GetType() && 2000 == iStmDmgValue) {
        iSnagGroup2++;
      }
      else if ( 0 == iSp && 0 == iStmDmgValue )
      {
        iSp1Group1++;
      }
      else if ( 1 == iSp && 0 == iStmDmgValue )
      {
        iSp2Group1++;
      }
      else if ( 0 == iSp && 1002 == iStmDmgValue )
      {
        iSp1Group2++;
      }
      else if ( 1 == iSp && 1002 == iStmDmgValue )
      {
        iSp2Group2++;
      }
      else if ( 0 == iSp && 2002 == iStmDmgValue )
      {
        iSp1Group3++;
      }
      else if ( 1 == iSp && 2002 == iStmDmgValue )
      {
        iSp2Group3++;
      }
      else
      {
        //Error
        sMessage << "TestNormalProcessingRun1, timestep 3, found an unexpected " << "tree storm damage value. X: " << fX
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
  EXPECT_EQ( 1000, iSnagGroup1 );
  EXPECT_EQ( 1000, iSnagGroup2 );

  //>>>>>>>>>>>>Separate out and only do cell 0, 1<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0. Group 2: storm damage = 1002. Group 3:
  //storm damage = 2002.
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  iSnagGroup1 = 0; iSnagGroup2 = 0;
  p_oAllTrees->StartOver();
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

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if ( fDiam < 6 )
      {
        EXPECT_EQ( 0, iStmDmgValue );
      }
      else if (clTreePopulation::snag == p_oTree->GetType() && 1000 == iStmDmgValue) {
        iSnagGroup1++;
      }
      else if (clTreePopulation::snag == p_oTree->GetType() && 2000 == iStmDmgValue) {
        iSnagGroup2++;
      }
      else if ( 0 == iSp && 0 == iStmDmgValue )
      {
        iSp1Group1++;
      }
      else if ( 1 == iSp && 0 == iStmDmgValue )
      {
        iSp2Group1++;
      }
      else if ( 0 == iSp && 1002 == iStmDmgValue )
      {
        iSp1Group2++;
      }
      else if ( 1 == iSp && 1002 == iStmDmgValue )
      {
        iSp2Group2++;
      }
      else if ( 0 == iSp && 2002 == iStmDmgValue )
      {
        iSp1Group3++;
      }
      else if ( 1 == iSp && 2002 == iStmDmgValue )
      {
        iSp2Group3++;
      }
      else
      {
        //Error
        sMessage << "TestNormalProcessingRun1, timestep 3, found an unexpected " << "tree storm damage value. X: " << fX
            << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
        FAIL() << sMessage.str();
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  //Validate the counts
  EXPECT_EQ( iSp1Group1 + iSp1Group2 + iSp1Group3, 1000 );
  EXPECT_EQ( iSp2Group1 + iSp2Group2 + iSp2Group3, 1000 );
  fExpected = 313;
  EXPECT_LT( fabs( fExpected - iSp1Group1 ) / fExpected, 0.1 );
  fExpected = 645;
  EXPECT_LT( fabs( fExpected - iSp2Group1 ) / fExpected, 0.1 );
  fExpected = 348;
  EXPECT_LT( fabs( fExpected - iSp1Group2 ) / fExpected, 0.1 );
  fExpected = 207;
  EXPECT_LT( fabs( fExpected - iSp2Group2 ) / fExpected, 0.11 );
  fExpected = 338;
  EXPECT_LT( fabs( fExpected - iSp1Group3 ) / fExpected, 0.1 );
  fExpected = 147;
  EXPECT_LT( fabs( fExpected - iSp2Group3 ) / fExpected, 0.15 );
  EXPECT_EQ( 1000, iSnagGroup1 );
  EXPECT_EQ( 1000, iSnagGroup2 );





  //>>>>>>>>>>>>Separate out and only do cell 0, 2<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0. Group 2: storm damage = 1002. Group 3:
  //storm damage = 2002.
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  iSnagGroup1 = 0; iSnagGroup2 = 0;
  p_oAllTrees->StartOver();
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

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if ( fDiam < 6 )
      {
        EXPECT_EQ( 0, iStmDmgValue );
      }
      else if (clTreePopulation::snag == p_oTree->GetType() && 1000 == iStmDmgValue) {
        iSnagGroup1++;
      }
      else if (clTreePopulation::snag == p_oTree->GetType() && 2000 == iStmDmgValue) {
        iSnagGroup2++;
      }
      else if ( 0 == iSp && 0 == iStmDmgValue )
      {
        iSp1Group1++;
      }
      else if ( 1 == iSp && 0 == iStmDmgValue )
      {
        iSp2Group1++;
      }
      else if ( 0 == iSp && 1002 == iStmDmgValue )
      {
        iSp1Group2++;
      }
      else if ( 1 == iSp && 1002 == iStmDmgValue )
      {
        iSp2Group2++;
      }
      else if ( 0 == iSp && 2002 == iStmDmgValue )
      {
        iSp1Group3++;
      }
      else if ( 1 == iSp && 2002 == iStmDmgValue )
      {
        iSp2Group3++;
      }
      else
      {
        //Error
        sMessage << "TestNormalProcessingRun1, timestep 3, found an unexpected " << "tree storm damage value. X: " << fX
            << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
        FAIL() << sMessage.str();
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  //Validate the counts
  EXPECT_EQ( iSp1Group1 + iSp1Group2 + iSp1Group3, 1000 );
  EXPECT_EQ( iSp2Group1 + iSp2Group2 + iSp2Group3, 1000 );
  fExpected = 23;
  EXPECT_LT( iSp1Group1 , 40 );
  fExpected = 218;
  EXPECT_LT( fabs( fExpected - iSp2Group1 ) / fExpected, 0.1 );
  fExpected = 68;
  EXPECT_LT( fabs( fExpected - iSp1Group2 ) / fExpected, 0.25 );
  fExpected = 252;
  EXPECT_LT( fabs( fExpected - iSp2Group2 ) / fExpected, 0.1 );
  fExpected = 908;
  EXPECT_LT( fabs( fExpected - iSp1Group3 ) / fExpected, 0.1 );
  fExpected = 529;
  EXPECT_LT( fabs( fExpected - iSp2Group3 ) / fExpected, 0.1 );
  EXPECT_EQ( 1000, iSnagGroup1 );
  EXPECT_EQ( 1000, iSnagGroup2 );




  //>>>>>>>>>>>>Separate out and only do cell 1, 0<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0. Group 2: storm damage = 1002. Group 3:
  //storm damage = 2002.
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  iSnagGroup1 = 0; iSnagGroup2 = 0;
  p_oAllTrees->StartOver();
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

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if ( fDiam < 6 )
      {
        EXPECT_EQ( 0, iStmDmgValue );
      }
      else if (clTreePopulation::snag == p_oTree->GetType() && 1000 == iStmDmgValue) {
        iSnagGroup1++;
      }
      else if (clTreePopulation::snag == p_oTree->GetType() && 2000 == iStmDmgValue) {
        iSnagGroup2++;
      }
      else if ( 0 == iSp && 0 == iStmDmgValue )
      {
        iSp1Group1++;
      }
      else if ( 1 == iSp && 0 == iStmDmgValue )
      {
        iSp2Group1++;
      }
      else if ( 0 == iSp && 1002 == iStmDmgValue )
      {
        iSp1Group2++;
      }
      else if ( 1 == iSp && 1002 == iStmDmgValue )
      {
        iSp2Group2++;
      }
      else if ( 0 == iSp && 2002 == iStmDmgValue )
      {
        iSp1Group3++;
      }
      else if ( 1 == iSp && 2002 == iStmDmgValue )
      {
        iSp2Group3++;
      }
      else
      {
        //Error
        sMessage << "TestNormalProcessingRun1, timestep 3, found an unexpected " << "tree storm damage value. X: " << fX
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
  EXPECT_EQ( 1000, iSnagGroup1 );
  EXPECT_EQ( 1000, iSnagGroup2 );




  //>>>>>>>>>>>>Separate out and only do cell 1, 1<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0. Group 2: storm damage = 1002. Group 3:
  //storm damage = 2002.
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  iSnagGroup1 = 0; iSnagGroup2 = 0;
  p_oAllTrees->StartOver();
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

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if ( fDiam < 6 )
      {
        EXPECT_EQ( 0, iStmDmgValue );
      }
      else if (clTreePopulation::snag == p_oTree->GetType() && 1000 == iStmDmgValue) {
        iSnagGroup1++;
      }
      else if (clTreePopulation::snag == p_oTree->GetType() && 2000 == iStmDmgValue) {
        iSnagGroup2++;
      }
      else if ( 0 == iSp && 0 == iStmDmgValue )
      {
        iSp1Group1++;
      }
      else if ( 1 == iSp && 0 == iStmDmgValue )
      {
        iSp2Group1++;
      }
      else if ( 0 == iSp && 1002 == iStmDmgValue )
      {
        iSp1Group2++;
      }
      else if ( 1 == iSp && 1002 == iStmDmgValue )
      {
        iSp2Group2++;
      }
      else if ( 0 == iSp && 2002 == iStmDmgValue )
      {
        iSp1Group3++;
      }
      else if ( 1 == iSp && 2002 == iStmDmgValue )
      {
        iSp2Group3++;
      }
      else
      {
        //Error
        sMessage << "TestNormalProcessingRun1, timestep 3, found an unexpected " << "tree storm damage value. X: " << fX
            << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
        FAIL() << sMessage.str();
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  //Validate the counts
  EXPECT_EQ( iSp1Group1 + iSp1Group2 + iSp1Group3, 1000 );
  EXPECT_EQ( iSp2Group1 + iSp2Group2 + iSp2Group3, 1000 );
  fExpected = 829;
  EXPECT_LT( fabs( fExpected - iSp1Group1 ) / fExpected, 0.1 );
  fExpected = 851;
  EXPECT_LT( fabs( fExpected - iSp2Group1 ) / fExpected, 0.1 );
  fExpected = 124;
  EXPECT_LT( fabs( fExpected - iSp1Group2 ) / fExpected, 0.1 );
  fExpected = 96;
  EXPECT_LT( fabs( fExpected - iSp2Group2 ) / fExpected, 0.25 );
  fExpected = 45;
  EXPECT_LT( fabs( fExpected - iSp1Group3 ) / fExpected, 0.25 );
  fExpected = 54;
  EXPECT_LT( fabs( fExpected - iSp2Group3 ) / fExpected, 0.3 );
  EXPECT_EQ( 1000, iSnagGroup1 );
  EXPECT_EQ( 1000, iSnagGroup2 );





  //>>>>>>>>>>>>Separate out and only do cell 1, 2<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0. Group 2: storm damage = 1002. Group 3:
  //storm damage = 2002.
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  iSnagGroup1 = 0; iSnagGroup2 = 0;
  p_oAllTrees->StartOver();
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

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if ( fDiam < 6 )
      {
        EXPECT_EQ( 0, iStmDmgValue );
      }
      else if (clTreePopulation::snag == p_oTree->GetType() && 1000 == iStmDmgValue) {
        iSnagGroup1++;
      }
      else if (clTreePopulation::snag == p_oTree->GetType() && 2000 == iStmDmgValue) {
        iSnagGroup2++;
      }
      else if ( 0 == iSp && 0 == iStmDmgValue )
      {
        iSp1Group1++;
      }
      else if ( 1 == iSp && 0 == iStmDmgValue )
      {
        iSp2Group1++;
      }
      else if ( 0 == iSp && 1002 == iStmDmgValue )
      {
        iSp1Group2++;
      }
      else if ( 1 == iSp && 1002 == iStmDmgValue )
      {
        iSp2Group2++;
      }
      else if ( 0 == iSp && 2002 == iStmDmgValue )
      {
        iSp1Group3++;
      }
      else if ( 1 == iSp && 2002 == iStmDmgValue )
      {
        iSp2Group3++;
      }
      else
      {
        //Error
        sMessage << "TestNormalProcessingRun1, timestep 3, found an unexpected " << "tree storm damage value. X: " << fX
            << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
        FAIL() << sMessage.str();
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  //Validate the counts
  EXPECT_EQ( iSp1Group1 + iSp1Group2 + iSp1Group3, 1000 );
  EXPECT_EQ( iSp2Group1 + iSp2Group2 + iSp2Group3, 1000 );
  fExpected = 548;
  EXPECT_LT( fabs( fExpected - iSp1Group1 ) / fExpected, 0.1 );
  fExpected = 511;
  EXPECT_LT( fabs( fExpected - iSp2Group1 ) / fExpected, 0.1 );
  fExpected = 290;
  EXPECT_LT( fabs( fExpected - iSp1Group2 ) / fExpected, 0.1 );
  fExpected = 257;
  EXPECT_LT( fabs( fExpected - iSp2Group2 ) / fExpected, 0.1 );
  fExpected = 161;
  EXPECT_LT( fabs( fExpected - iSp1Group3 ) / fExpected, 0.1 );
  fExpected = 231;
  EXPECT_LT( fabs( fExpected - iSp2Group3 ) / fExpected, 0.2 );
  EXPECT_EQ( 1000, iSnagGroup1 );
  EXPECT_EQ( 1000, iSnagGroup2 );





  //>>>>>>>>>>>>Separate out and only do cell 2, 0<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0. Group 2: storm damage = 1002. Group 3:
  //storm damage = 2002.
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  p_oAllTrees->StartOver();
  p_oTree = p_oAllTrees->NextTree();
  while ( p_oTree )
  {
    iSp = p_oTree->GetSpecies();

    //Get X and Y
    p_oTree->GetValue( p_oPop->GetXCode( iSp, p_oTree->GetType() ), & fX );
    p_oTree->GetValue( p_oPop->GetYCode( iSp, p_oTree->GetType() ), & fY );

    //Get storm damage counter
    p_oTree->GetValue( p_oPop->GetIntDataCode( "stm_dmg", iSp, p_oTree->GetType() ), & iStmDmgValue );

    if ( fY < 8 && fX > 16 && fX < 24 )
    {
      //Make sure this ain't no snag
      ASSERT_TRUE(clTreePopulation::snag != p_oTree->GetType());

      //Get DBH
      p_oTree->GetValue( p_oPop->GetDbhCode( iSp, p_oTree->GetType() ), & fDiam );

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if ( fDiam < 6 )
      {
        EXPECT_EQ( 0, iStmDmgValue );
      }
      else if ( 0 == iSp && 0 == iStmDmgValue )
      {
        iSp1Group1++;
      }
      else if ( 1 == iSp && 0 == iStmDmgValue )
      {
        iSp2Group1++;
      }
      else if ( 0 == iSp && 1002 == iStmDmgValue )
      {
        iSp1Group2++;
      }
      else if ( 1 == iSp && 1002 == iStmDmgValue )
      {
        iSp2Group2++;
      }
      else if ( 0 == iSp && 2002 == iStmDmgValue )
      {
        iSp1Group3++;
      }
      else if ( 1 == iSp && 2002 == iStmDmgValue )
      {
        iSp2Group3++;
      }
      else
      {
        //Error
        sMessage << "TestNormalProcessingRun1, timestep 3, found an unexpected " << "tree storm damage value. X: " << fX
            << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
        FAIL() << sMessage.str();
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  EXPECT_EQ( iSp1Group1 + iSp1Group2 + iSp1Group3, 1000 );
  EXPECT_EQ( iSp2Group1 + iSp2Group2 + iSp2Group3, 1000 );
  fExpected = 627;
  EXPECT_LT( fabs( fExpected - iSp1Group1 ) / fExpected, 0.1 );
  fExpected = 834;
  EXPECT_LT( fabs( fExpected - iSp2Group1 ) / fExpected, 0.1 );
  fExpected = 251;
  EXPECT_LT( fabs( fExpected - iSp1Group2 ) / fExpected, 0.1 );
  fExpected = 106;
  EXPECT_LT( fabs( fExpected - iSp2Group2 ) / fExpected, 0.3 );
  fExpected = 121;
  EXPECT_LT( fabs( fExpected - iSp1Group3 ) / fExpected, 0.16 );
  fExpected = 58;
  EXPECT_LT( fabs( fExpected - iSp2Group3 ) / fExpected, 0.2 );






  //>>>>>>>>>>>>Separate out and only do cell 2, 1<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0. Group 2: storm damage = 2002.
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0; iSp2Group2 = 0;
  p_oAllTrees->StartOver();
  p_oTree = p_oAllTrees->NextTree();
  while ( p_oTree )
  {
    iSp = p_oTree->GetSpecies();

    //Get X and Y
    p_oTree->GetValue( p_oPop->GetXCode( iSp, p_oTree->GetType() ), & fX );
    p_oTree->GetValue( p_oPop->GetYCode( iSp, p_oTree->GetType() ), & fY );

    //Get storm damage counter
    p_oTree->GetValue( p_oPop->GetIntDataCode( "stm_dmg", iSp, p_oTree->GetType() ), & iStmDmgValue );

    if ( fY > 8 && fY < 16 && fX > 16 && fX < 24 )
    {
      //Make sure this ain't no snag
      ASSERT_TRUE(clTreePopulation::snag != p_oTree->GetType());

      //Get DBH
      p_oTree->GetValue( p_oPop->GetDbhCode( iSp, p_oTree->GetType() ), & fDiam );

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if ( fDiam < 6 )
      {
        EXPECT_EQ( 0, iStmDmgValue );
      }
      else if ( 0 == iSp && 0 == iStmDmgValue )
      {
        iSp1Group1++;
      }
      else if ( 1 == iSp && 0 == iStmDmgValue )
      {
        iSp2Group1++;
      }
      else if ( 0 == iSp && 2002 == iStmDmgValue )
      {
        iSp1Group2++;
      }
      else if ( 1 == iSp && 2002 == iStmDmgValue )
      {
        iSp2Group2++;
      }
      else
      {
        //Error
        sMessage << "TestNormalProcessingRun1, timestep 3, found an unexpected " << "tree storm damage value. X: " << fX
            << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
        FAIL() << sMessage.str();
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  //Validate the counts
  EXPECT_EQ( iSp1Group1 + iSp1Group2, 1000 );
  EXPECT_EQ( iSp2Group1 + iSp2Group2, 1000 );
  fExpected = 450;
  EXPECT_LT( fabs( fExpected - iSp1Group1 ) / fExpected, 0.1 );
  fExpected = 594;
  EXPECT_LT( fabs( fExpected - iSp2Group1 ) / fExpected, 0.1 );
  fExpected = 538;
  EXPECT_LT( fabs( fExpected - iSp1Group2 ) / fExpected, 0.1 );
  fExpected = 404;
  EXPECT_LT( fabs( fExpected - iSp2Group2 ) / fExpected, 0.1 );
}

/////////////////////////////////////////////////////////////////////////////
// TestStormDamageApplierRun1Timestep4()
/////////////////////////////////////////////////////////////////////////////
void TestStormDamageApplierRun1Timestep4( clTreePopulation * p_oPop )
{
  using namespace std;
  clTreeSearch * p_oAllTrees;
  clTree * p_oTree;
  stringstream sMessage;
  float fX, fY, fDiam, fExpected;
  int iSp1Group1, iSp2Group1, iSp1Group2, iSp2Group2, iSp1Group3, iSp2Group3,
  iSnagGroup1, iSnagGroup2, iSp, iStmDmgValue;

  //Get all trees
  p_oAllTrees = p_oPop->Find( "all" );

  //>>>>>>>>>>>>Separate out and only do cell 0,0<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0. Group 2: storm damage = 1003. Group 3:
  //storm damage = 2003.
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  iSnagGroup1 = 0; iSnagGroup2 = 0;
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

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if ( fDiam < 6 )
      {
        EXPECT_EQ( 0, iStmDmgValue );
      }
      else if (clTreePopulation::snag == p_oTree->GetType() && 1000 == iStmDmgValue) {
        iSnagGroup1++;
      }
      else if (clTreePopulation::snag == p_oTree->GetType() && 2000 == iStmDmgValue) {
        iSnagGroup2++;
      }
      else if ( 0 == iSp && 0 == iStmDmgValue )
      {
        iSp1Group1++;
      }
      else if ( 1 == iSp && 0 == iStmDmgValue )
      {
        iSp2Group1++;
      }
      else if ( 0 == iSp && 1003 == iStmDmgValue )
      {
        iSp1Group2++;
      }
      else if ( 1 == iSp && 1003 == iStmDmgValue )
      {
        iSp2Group2++;
      }
      else if ( 0 == iSp && 2003 == iStmDmgValue )
      {
        iSp1Group3++;
      }
      else if ( 1 == iSp && 2003 == iStmDmgValue )
      {
        iSp2Group3++;
      }
      else
      {
        //Error
        sMessage << "TestNormalProcessingRun1, timestep 4, found an unexpected " << "tree storm damage value. X: " << fX
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
  EXPECT_EQ( 1000, iSnagGroup1 );
  EXPECT_EQ( 1000, iSnagGroup2 );

  //>>>>>>>>>>>>Separate out and only do cell 0, 1<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0. Group 2: storm damage = 1003. Group 3:
  //storm damage = 2003.
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  iSnagGroup1 = 0; iSnagGroup2 = 0;
  p_oAllTrees->StartOver();
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

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if ( fDiam < 6 )
      {
        EXPECT_EQ( 0, iStmDmgValue );
      }
      else if (clTreePopulation::snag == p_oTree->GetType() && 1000 == iStmDmgValue) {
        iSnagGroup1++;
      }
      else if (clTreePopulation::snag == p_oTree->GetType() && 2000 == iStmDmgValue) {
        iSnagGroup2++;
      }
      else if ( 0 == iSp && 0 == iStmDmgValue )
      {
        iSp1Group1++;
      }
      else if ( 1 == iSp && 0 == iStmDmgValue )
      {
        iSp2Group1++;
      }
      else if ( 0 == iSp && 1003 == iStmDmgValue )
      {
        iSp1Group2++;
      }
      else if ( 1 == iSp && 1003 == iStmDmgValue )
      {
        iSp2Group2++;
      }
      else if ( 0 == iSp && 2003 == iStmDmgValue )
      {
        iSp1Group3++;
      }
      else if ( 1 == iSp && 2003 == iStmDmgValue )
      {
        iSp2Group3++;
      }
      else
      {
        //Error
        sMessage << "TestNormalProcessingRun1, timestep 4, found an unexpected " << "tree storm damage value. X: " << fX
            << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
        FAIL() << sMessage.str();
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  //Validate the counts
  EXPECT_EQ( iSp1Group1 + iSp1Group2 + iSp1Group3, 1000 );
  EXPECT_EQ( iSp2Group1 + iSp2Group2 + iSp2Group3, 1000 );
  fExpected = 313;
  EXPECT_LT( fabs( fExpected - iSp1Group1 ) / fExpected, 0.1 );
  fExpected = 645;
  EXPECT_LT( fabs( fExpected - iSp2Group1 ) / fExpected, 0.1 );
  fExpected = 348;
  EXPECT_LT( fabs( fExpected - iSp1Group2 ) / fExpected, 0.1 );
  fExpected = 207;
  EXPECT_LT( fabs( fExpected - iSp2Group2 ) / fExpected, 0.11 );
  fExpected = 338;
  EXPECT_LT( fabs( fExpected - iSp1Group3 ) / fExpected, 0.1 );
  fExpected = 147;
  EXPECT_LT( fabs( fExpected - iSp2Group3 ) / fExpected, 0.15 );
  EXPECT_EQ( 1000, iSnagGroup1 );
  EXPECT_EQ( 1000, iSnagGroup2 );





  //>>>>>>>>>>>>Separate out and only do cell 0, 2<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0. Group 2: storm damage = 1003. Group 3:
  //storm damage = 2003.
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  iSnagGroup1 = 0; iSnagGroup2 = 0;
  p_oAllTrees->StartOver();
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

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if ( fDiam < 6 )
      {
        EXPECT_EQ( 0, iStmDmgValue );
      }
      else if (clTreePopulation::snag == p_oTree->GetType() && 1000 == iStmDmgValue) {
        iSnagGroup1++;
      }
      else if (clTreePopulation::snag == p_oTree->GetType() && 2000 == iStmDmgValue) {
        iSnagGroup2++;
      }
      else if ( 0 == iSp && 0 == iStmDmgValue )
      {
        iSp1Group1++;
      }
      else if ( 1 == iSp && 0 == iStmDmgValue )
      {
        iSp2Group1++;
      }
      else if ( 0 == iSp && 1003 == iStmDmgValue )
      {
        iSp1Group2++;
      }
      else if ( 1 == iSp && 1003 == iStmDmgValue )
      {
        iSp2Group2++;
      }
      else if ( 0 == iSp && 2003 == iStmDmgValue )
      {
        iSp1Group3++;
      }
      else if ( 1 == iSp && 2003 == iStmDmgValue )
      {
        iSp2Group3++;
      }
      else
      {
        //Error
        sMessage << "TestNormalProcessingRun1, timestep 4, found an unexpected " << "tree storm damage value. X: " << fX
            << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
        FAIL() << sMessage.str();
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  //Validate the counts
  EXPECT_EQ( iSp1Group1 + iSp1Group2 + iSp1Group3, 1000 );
  EXPECT_EQ( iSp2Group1 + iSp2Group2 + iSp2Group3, 1000 );
  fExpected = 23;
  EXPECT_LT( iSp1Group1 , 40 );
  fExpected = 218;
  EXPECT_LT( fabs( fExpected - iSp2Group1 ) / fExpected, 0.1 );
  fExpected = 68;
  EXPECT_LT( fabs( fExpected - iSp1Group2 ) / fExpected, 0.25 );
  fExpected = 252;
  EXPECT_LT( fabs( fExpected - iSp2Group2 ) / fExpected, 0.1 );
  fExpected = 908;
  EXPECT_LT( fabs( fExpected - iSp1Group3 ) / fExpected, 0.1 );
  fExpected = 529;
  EXPECT_LT( fabs( fExpected - iSp2Group3 ) / fExpected, 0.1 );
  EXPECT_EQ( 1000, iSnagGroup1 );
  EXPECT_EQ( 1000, iSnagGroup2 );




  //>>>>>>>>>>>>Separate out and only do cell 1, 0<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0. Group 2: storm damage = 1003. Group 3:
  //storm damage = 2003.
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  iSnagGroup1 = 0; iSnagGroup2 = 0;
  p_oAllTrees->StartOver();
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

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if ( fDiam < 6 )
      {
        EXPECT_EQ( 0, iStmDmgValue );
      }
      else if (clTreePopulation::snag == p_oTree->GetType() && 1000 == iStmDmgValue) {
        iSnagGroup1++;
      }
      else if (clTreePopulation::snag == p_oTree->GetType() && 2000 == iStmDmgValue) {
        iSnagGroup2++;
      }
      else if ( 0 == iSp && 0 == iStmDmgValue )
      {
        iSp1Group1++;
      }
      else if ( 1 == iSp && 0 == iStmDmgValue )
      {
        iSp2Group1++;
      }
      else if ( 0 == iSp && 1003 == iStmDmgValue )
      {
        iSp1Group2++;
      }
      else if ( 1 == iSp && 1003 == iStmDmgValue )
      {
        iSp2Group2++;
      }
      else if ( 0 == iSp && 2003 == iStmDmgValue )
      {
        iSp1Group3++;
      }
      else if ( 1 == iSp && 2003 == iStmDmgValue )
      {
        iSp2Group3++;
      }
      else
      {
        //Error
        sMessage << "TestNormalProcessingRun1, timestep 4, found an unexpected " << "tree storm damage value. X: " << fX
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
  EXPECT_EQ( 1000, iSnagGroup1 );
  EXPECT_EQ( 1000, iSnagGroup2 );




  //>>>>>>>>>>>>Separate out and only do cell 1, 1<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0. Group 2: storm damage = 1003. Group 3:
  //storm damage = 2003.
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  iSnagGroup1 = 0; iSnagGroup2 = 0;
  p_oAllTrees->StartOver();
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

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if ( fDiam < 6 )
      {
        EXPECT_EQ( 0, iStmDmgValue );
      }
      else if (clTreePopulation::snag == p_oTree->GetType() && 1000 == iStmDmgValue) {
        iSnagGroup1++;
      }
      else if (clTreePopulation::snag == p_oTree->GetType() && 2000 == iStmDmgValue) {
        iSnagGroup2++;
      }
      else if ( 0 == iSp && 0 == iStmDmgValue )
      {
        iSp1Group1++;
      }
      else if ( 1 == iSp && 0 == iStmDmgValue )
      {
        iSp2Group1++;
      }
      else if ( 0 == iSp && 1003 == iStmDmgValue )
      {
        iSp1Group2++;
      }
      else if ( 1 == iSp && 1003 == iStmDmgValue )
      {
        iSp2Group2++;
      }
      else if ( 0 == iSp && 2003 == iStmDmgValue )
      {
        iSp1Group3++;
      }
      else if ( 1 == iSp && 2003 == iStmDmgValue )
      {
        iSp2Group3++;
      }
      else
      {
        //Error
        sMessage << "TestNormalProcessingRun1, timestep 4, found an unexpected " << "tree storm damage value. X: " << fX
            << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
        FAIL() << sMessage.str();
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  //Validate the counts
  EXPECT_EQ( iSp1Group1 + iSp1Group2 + iSp1Group3, 1000 );
  EXPECT_EQ( iSp2Group1 + iSp2Group2 + iSp2Group3, 1000 );
  fExpected = 829;
  EXPECT_LT( fabs( fExpected - iSp1Group1 ) / fExpected, 0.1 );
  fExpected = 851;
  EXPECT_LT( fabs( fExpected - iSp2Group1 ) / fExpected, 0.1 );
  fExpected = 124;
  EXPECT_LT( fabs( fExpected - iSp1Group2 ) / fExpected, 0.1 );
  fExpected = 96;
  EXPECT_LT( fabs( fExpected - iSp2Group2 ) / fExpected, 0.25 );
  fExpected = 45;
  EXPECT_LT( fabs( fExpected - iSp1Group3 ) / fExpected, 0.25 );
  fExpected = 54;
  EXPECT_LT( fabs( fExpected - iSp2Group3 ) / fExpected, 0.3 );
  EXPECT_EQ( 1000, iSnagGroup1 );
  EXPECT_EQ( 1000, iSnagGroup2 );





  //>>>>>>>>>>>>Separate out and only do cell 1, 2<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0. Group 2: storm damage = 1003. Group 3:
  //storm damage = 2003.
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  iSnagGroup1 = 0; iSnagGroup2 = 0;
  p_oAllTrees->StartOver();
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

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if ( fDiam < 6 )
      {
        EXPECT_EQ( 0, iStmDmgValue );
      }
      else if (clTreePopulation::snag == p_oTree->GetType() && 1000 == iStmDmgValue) {
        iSnagGroup1++;
      }
      else if (clTreePopulation::snag == p_oTree->GetType() && 2000 == iStmDmgValue) {
        iSnagGroup2++;
      }
      else if ( 0 == iSp && 0 == iStmDmgValue )
      {
        iSp1Group1++;
      }
      else if ( 1 == iSp && 0 == iStmDmgValue )
      {
        iSp2Group1++;
      }
      else if ( 0 == iSp && 1003 == iStmDmgValue )
      {
        iSp1Group2++;
      }
      else if ( 1 == iSp && 1003 == iStmDmgValue )
      {
        iSp2Group2++;
      }
      else if ( 0 == iSp && 2003 == iStmDmgValue )
      {
        iSp1Group3++;
      }
      else if ( 1 == iSp && 2003 == iStmDmgValue )
      {
        iSp2Group3++;
      }
      else
      {
        //Error
        sMessage << "TestNormalProcessingRun1, timestep 4, found an unexpected " << "tree storm damage value. X: " << fX
            << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
        FAIL() << sMessage.str();
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  //Validate the counts
  EXPECT_EQ( iSp1Group1 + iSp1Group2 + iSp1Group3, 1000 );
  EXPECT_EQ( iSp2Group1 + iSp2Group2 + iSp2Group3, 1000 );
  fExpected = 548;
  EXPECT_LT( fabs( fExpected - iSp1Group1 ) / fExpected, 0.1 );
  fExpected = 511;
  EXPECT_LT( fabs( fExpected - iSp2Group1 ) / fExpected, 0.1 );
  fExpected = 290;
  EXPECT_LT( fabs( fExpected - iSp1Group2 ) / fExpected, 0.1 );
  fExpected = 257;
  EXPECT_LT( fabs( fExpected - iSp2Group2 ) / fExpected, 0.1 );
  fExpected = 161;
  EXPECT_LT( fabs( fExpected - iSp1Group3 ) / fExpected, 0.1 );
  fExpected = 231;
  EXPECT_LT( fabs( fExpected - iSp2Group3 ) / fExpected, 0.2 );
  EXPECT_EQ( 1000, iSnagGroup1 );
  EXPECT_EQ( 1000, iSnagGroup2 );




  //>>>>>>>>>>>>Separate out and only do cell 2, 0<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0. Group 2: storm damage = 1003. Group 3:
  //storm damage = 2003.
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0;
  iSp2Group2 = 0; iSp1Group3 = 0; iSp2Group3 = 0;
  p_oAllTrees->StartOver();
  p_oTree = p_oAllTrees->NextTree();
  while ( p_oTree )
  {
    iSp = p_oTree->GetSpecies();

    //Get X and Y
    p_oTree->GetValue( p_oPop->GetXCode( iSp, p_oTree->GetType() ), & fX );
    p_oTree->GetValue( p_oPop->GetYCode( iSp, p_oTree->GetType() ), & fY );

    //Get storm damage counter
    p_oTree->GetValue( p_oPop->GetIntDataCode( "stm_dmg", iSp, p_oTree->GetType() ), & iStmDmgValue );

    if ( fY < 8 && fX > 16 && fX < 24 )
    {
      //Make sure this ain't no snag
      ASSERT_TRUE(clTreePopulation::snag != p_oTree->GetType());

      //Get DBH
      p_oTree->GetValue( p_oPop->GetDbhCode( iSp, p_oTree->GetType() ), & fDiam );

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if ( fDiam < 6 )
      {
        EXPECT_EQ( 0, iStmDmgValue );
      }
      else if ( 0 == iSp && 0 == iStmDmgValue )
      {
        iSp1Group1++;
      }
      else if ( 1 == iSp && 0 == iStmDmgValue )
      {
        iSp2Group1++;
      }
      else if ( 0 == iSp && 1003 == iStmDmgValue )
      {
        iSp1Group2++;
      }
      else if ( 1 == iSp && 1003 == iStmDmgValue )
      {
        iSp2Group2++;
      }
      else if ( 0 == iSp && 2003 == iStmDmgValue )
      {
        iSp1Group3++;
      }
      else if ( 1 == iSp && 2003 == iStmDmgValue )
      {
        iSp2Group3++;
      }
      else
      {
        //Error
        sMessage << "TestNormalProcessingRun1, timestep 4, found an unexpected " << "tree storm damage value. X: " << fX
            << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
        FAIL() << sMessage.str();
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  EXPECT_EQ( iSp1Group1 + iSp1Group2 + iSp1Group3, 1000 );
  EXPECT_EQ( iSp2Group1 + iSp2Group2 + iSp2Group3, 1000 );
  fExpected = 627;
  EXPECT_LT( fabs( fExpected - iSp1Group1 ) / fExpected, 0.1 );
  fExpected = 834;
  EXPECT_LT( fabs( fExpected - iSp2Group1 ) / fExpected, 0.1 );
  fExpected = 251;
  EXPECT_LT( fabs( fExpected - iSp1Group2 ) / fExpected, 0.1 );
  fExpected = 106;
  EXPECT_LT( fabs( fExpected - iSp2Group2 ) / fExpected, 0.3 );
  fExpected = 121;
  EXPECT_LT( fabs( fExpected - iSp1Group3 ) / fExpected, 0.16 );
  fExpected = 58;
  EXPECT_LT( fabs( fExpected - iSp2Group3 ) / fExpected, 0.2 );






  //>>>>>>>>>>>>Separate out and only do cell 2, 1<<<<<<<<<<<<<<<<<<<<<<<
  //Group 1: storm damage = 0. Group 2: storm damage = 2003.
  iSp1Group1 = 0; iSp2Group1 = 0; iSp1Group2 = 0; iSp2Group2 = 0;
  p_oAllTrees->StartOver();
  p_oTree = p_oAllTrees->NextTree();
  while ( p_oTree )
  {
    iSp = p_oTree->GetSpecies();

    //Get X and Y
    p_oTree->GetValue( p_oPop->GetXCode( iSp, p_oTree->GetType() ), & fX );
    p_oTree->GetValue( p_oPop->GetYCode( iSp, p_oTree->GetType() ), & fY );

    //Get storm damage counter
    p_oTree->GetValue( p_oPop->GetIntDataCode( "stm_dmg", iSp, p_oTree->GetType() ), & iStmDmgValue );

    if ( fY > 8 && fY < 16 && fX > 16 && fX < 24 )
    {
      //Make sure this ain't no snag
      ASSERT_TRUE(clTreePopulation::snag != p_oTree->GetType());

      //Get DBH
      p_oTree->GetValue( p_oPop->GetDbhCode( iSp, p_oTree->GetType() ), & fDiam );

      //If it's too small, it's got no damage; otherwise, count it into the
      //appropriate group
      if ( fDiam < 6 )
      {
        EXPECT_EQ( 0, iStmDmgValue );
      }
      else if ( 0 == iSp && 0 == iStmDmgValue )
      {
        iSp1Group1++;
      }
      else if ( 1 == iSp && 0 == iStmDmgValue )
      {
        iSp2Group1++;
      }
      else if ( 0 == iSp && 2003 == iStmDmgValue )
      {
        iSp1Group2++;
      }
      else if ( 1 == iSp && 2003 == iStmDmgValue )
      {
        iSp2Group2++;
      }
      else
      {
        //Error
        sMessage << "TestNormalProcessingRun1, timestep 4, found an unexpected " << "tree storm damage value. X: " << fX
            << " Y: " << fY << " Diam: " << fDiam << " Dmg value: " << iStmDmgValue;
        FAIL() << sMessage.str();
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  //Validate the counts
  EXPECT_EQ( iSp1Group1 + iSp1Group2, 1000 );
  EXPECT_EQ( iSp2Group1 + iSp2Group2, 1000 );
  fExpected = 450;
  EXPECT_LT( fabs( fExpected - iSp1Group1 ) / fExpected, 0.1 );
  fExpected = 594;
  EXPECT_LT( fabs( fExpected - iSp2Group1 ) / fExpected, 0.1 );
  fExpected = 538;
  EXPECT_LT( fabs( fExpected - iSp1Group2 ) / fExpected, 0.1 );
  fExpected = 404;
  EXPECT_LT( fabs( fExpected - iSp2Group2 ) / fExpected, 0.1 );

}

/////////////////////////////////////////////////////////////////////////////
// TestStormDamageApplierRun1Timestep5()
/////////////////////////////////////////////////////////////////////////////
void TestStormDamageApplierRun1Timestep5( clTreePopulation * p_oPop )
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
    p_oTree->GetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), & iStmDmgValue );
    if (clTreePopulation::snag != p_oTree->GetType())
      EXPECT_EQ( 0, iStmDmgValue );
    p_oTree = p_oAllTrees->NextTree();
  }
}


/////////////////////////////////////////////////////////////////////////////
// WriteStormDamageApplierXMLFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteStormDamageApplierXMLFile1()
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

  WriteStormDamageApplierCommonStuff(oOut);
  WriteStormDamageApplierBehaviorList(oOut);

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
      << "</paramFile>";

  oOut.close();

  return cFileString;

}

/////////////////////////////////////////////////////////////////////////////
// WriteStormDamageApplierXMLFile2()
/////////////////////////////////////////////////////////////////////////////
const char* WriteStormDamageApplierXMLFile2()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>" << "<paramFile fileCode=\"06010101\">" << "<plot>"
      << "<timesteps>5</timesteps>" << "<yearsPerTimestep>3</yearsPerTimestep>";

  WriteStormDamageApplierCommonStuff(oOut);
  WriteStormDamageApplierBehaviorList(oOut);

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
      << "<st_stmPropDieMedDmg>"
      << "<st_spdmdVal species=\"Species_1\">0</st_spdmdVal>"
      << "<st_spdmdVal species=\"Species_2\">0</st_spdmdVal>"
      << "</st_stmPropDieMedDmg>"
      << "<st_stmPropDieFullDmg>"
      << "<st_spdfdVal species=\"Species_1\">0</st_spdfdVal>"
      << "<st_spdfdVal species=\"Species_2\">0</st_spdfdVal>"
      << "</st_stmPropDieFullDmg>"
      << "<st_stmPropTipUpFullDmg>"
      << "<st_sptufdVal species=\"Species_1\">0</st_sptufdVal>"
      << "<st_sptufdVal species=\"Species_2\">0</st_sptufdVal>"
      << "</st_stmPropTipUpFullDmg>"
      << "<st_numYearsToHeal>4</st_numYearsToHeal>"
      << "<st_numYearsStormSnags>0</st_numYearsStormSnags>"
      << "</StormDamageApplier2>"
      << "</paramFile>";

  oOut.close();

  return cFileString;

}

/////////////////////////////////////////////////////////////////////////////
// WriteStormDamageApplierXMLErrorFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteStormDamageApplierXMLErrorFile1()
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

  WriteStormDamageApplierCommonStuff(oOut);

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>StormDamageApplier</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "</behaviorList>";

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
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteStormDamageApplierXMLErrorFile2()
/////////////////////////////////////////////////////////////////////////////
const char* WriteStormDamageApplierXMLErrorFile2()
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

  WriteStormDamageApplierCommonStuff(oOut);
  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>Storm</behaviorName>"
      << "<listPosition>1</listPosition>"
      << "<version>1</version>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>StormDamageApplier</behaviorName>"
      << "<listPosition>2</listPosition>"
      << "<version>1</version>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "</behaviorList>";

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
      << "</paramFile>";

  oOut.close();
  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteStormDamageApplierXMLFile3()
/////////////////////////////////////////////////////////////////////////////
const char* WriteStormDamageApplierXMLFile3()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">"
      << "<plot>"
      << "<timesteps>100</timesteps>"
      << "<yearsPerTimestep>1</yearsPerTimestep>"
      << "<randomSeed>1</randomSeed>";
  oOut << "<plot_lenX>100</plot_lenX>"
      << "<plot_lenY>100</plot_lenY>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88171785</plot_temp_C>"
      << "<plot_latitude>55.37</plot_latitude>"
      << "</plot>"
      << "<trees>"
      << "<tr_speciesList>"
      << "<tr_species speciesName=\"CASARB\"/>"
      << "<tr_species speciesName=\"GUAGUI\"/>"
      << "</tr_speciesList>"
      << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
      << "<tr_canopyHeight>"
      << "<tr_chVal species=\"CASARB\">39.48</tr_chVal>"
      << "<tr_chVal species=\"GUAGUI\">39.48</tr_chVal>"
      << "</tr_canopyHeight>"
      << "<tr_stdAsympCrownRad>"
      << "<tr_sacrVal species=\"CASARB\">0.0549</tr_sacrVal>"
      << "<tr_sacrVal species=\"GUAGUI\">0.0549</tr_sacrVal>"
      << "</tr_stdAsympCrownRad>"
      << "<tr_stdCrownRadExp>"
      << "<tr_screVal species=\"CASARB\">1.0</tr_screVal>"
      << "<tr_screVal species=\"GUAGUI\">1.0</tr_screVal>"
      << "</tr_stdCrownRadExp>"
      << "<tr_conversionDiam10ToDBH>"
      << "<tr_cdtdVal species=\"CASARB\">0.8008</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"GUAGUI\">0.8008</tr_cdtdVal>"
      << "</tr_conversionDiam10ToDBH>"
      << "<tr_stdAsympCrownHt>"
      << "<tr_sachVal species=\"CASARB\">0.389</tr_sachVal>"
      << "<tr_sachVal species=\"GUAGUI\">0.389</tr_sachVal>"
      << "</tr_stdAsympCrownHt>"
      << "<tr_stdCrownHtExp>"
      << "<tr_scheVal species=\"CASARB\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"GUAGUI\">1.0</tr_scheVal>"
      << "</tr_stdCrownHtExp>"
      << "<tr_slopeOfHeight-Diam10>"
      << "<tr_sohdVal species=\"CASARB\">0.03418</tr_sohdVal>"
      << "<tr_sohdVal species=\"GUAGUI\">0.03418</tr_sohdVal>"
      << "</tr_slopeOfHeight-Diam10>"
      << "<tr_minAdultDBH>"
      << "<tr_madVal species=\"CASARB\">10.0</tr_madVal>"
      << "<tr_madVal species=\"GUAGUI\">10.0</tr_madVal>"
      << "</tr_minAdultDBH>"
      << "<tr_slopeOfAsymHeight>"
      << "<tr_soahVal species=\"CASARB\">0.0299</tr_soahVal>"
      << "<tr_soahVal species=\"GUAGUI\">0.0299</tr_soahVal>"
      << "</tr_slopeOfAsymHeight>"
      << "</trees>"
      << "<allometry>"
      << "<tr_whatSeedlingHeightDiam>"
      << "<tr_wsehdVal species=\"CASARB\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"GUAGUI\">0</tr_wsehdVal>"
      << "</tr_whatSeedlingHeightDiam>"
      << "<tr_whatSaplingHeightDiam>"
      << "<tr_wsahdVal species=\"CASARB\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"GUAGUI\">0</tr_wsahdVal>"
      << "</tr_whatSaplingHeightDiam>"
      << "<tr_whatAdultHeightDiam>"
      << "<tr_wahdVal species=\"CASARB\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"GUAGUI\">0</tr_wahdVal>"
      << "</tr_whatAdultHeightDiam>"
      << "</allometry>"
      << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>Storm</behaviorName>"
      << "<version>1</version>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>StormDamageApplier</behaviorName>"
      << "<version>2</version>"
      << "<applyTo species=\"CASARB\" type=\"Sapling\"/>"
      << "<applyTo species=\"CASARB\" type=\"Adult\"/>"
      << "<applyTo species=\"GUAGUI\" type=\"Sapling\"/>"
      << "<applyTo species=\"GUAGUI\" type=\"Adult\"/>"
      << "</behavior>"
      << "</behaviorList>";

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
      << "<st_mdVal species=\"CASARB\">5</st_mdVal>"
      << "<st_mdVal species=\"GUAGUI\">6</st_mdVal>"
      << "</st_minDBH>"
      << "<st_stmDmgInterceptMed>"
      << "<st_sdimVal species=\"CASARB\">2.1789601</st_sdimVal>"
      << "<st_sdimVal species=\"GUAGUI\">2.772772</st_sdimVal>"
      << "</st_stmDmgInterceptMed>"
      << "<st_stmDmgInterceptFull>"
      << "<st_sdifVal species=\"CASARB\">2.6334169</st_sdifVal>"
      << "<st_sdifVal species=\"GUAGUI\">4.9189817</st_sdifVal>"
      << "</st_stmDmgInterceptFull>"
      << "<st_stmIntensityCoeff>"
      << "<st_sicVal species=\"CASARB\">-0.2545352</st_sicVal>"
      << "<st_sicVal species=\"GUAGUI\">-1.936994</st_sicVal>"
      << "</st_stmIntensityCoeff>"
      << "<st_stmDBHCoeff>"
      << "<st_sdcVal species=\"CASARB\">0.8280319</st_sdcVal>"
      << "<st_sdcVal species=\"GUAGUI\">0.2411269</st_sdcVal>"
      << "</st_stmDBHCoeff>"
      << "<st_numYearsToHeal>4</st_numYearsToHeal>"
      << "</StormDamageApplier2>"
      << "</paramFile>";

  oOut.close();

  return cFileString;

}

/////////////////////////////////////////////////////////////////////////////
// WriteStormDamageApplierXMLErrorFile3()
/////////////////////////////////////////////////////////////////////////////
const char* WriteStormDamageApplierXMLErrorFile3()
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

  WriteStormDamageApplierCommonStuff(oOut);
  WriteStormDamageApplierBehaviorList(oOut);

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
      << "<st_numYearsToHeal>-4</st_numYearsToHeal>"
      << "</StormDamageApplier2>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteStormDamageApplierCommonStuff()
/////////////////////////////////////////////////////////////////////////////
void WriteStormDamageApplierCommonStuff(std::fstream &oOut)
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
      << "<tr_conversionDiam10ToDBH>"
      << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_2\">0.8008</tr_cdtdVal>"
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
}


/////////////////////////////////////////////////////////////////////////////
// WriteStormDamageApplierBehaviorList()
/////////////////////////////////////////////////////////////////////////////
void WriteStormDamageApplierBehaviorList(std::fstream &oOut)
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
      << "</behaviorList>";
}
