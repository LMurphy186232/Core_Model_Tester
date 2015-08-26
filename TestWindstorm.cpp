//---------------------------------------------------------------------------
// TestWindstorm.cpp
//---------------------------------------------------------------------------
#include "TestWindstorm.h"
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
TEST(Windstorm, TestErrorProcessing)
{
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try
  {
    p_oSimManager->ReadFile( WriteWindstormXMLErrorFile1() );
    FAIL() << "TestWindstorm error processing didn't catch error for WriteWindstormXMLErrorFile1.";
  }
  catch ( modelErr& err )
  {
    if ( err.sFunction.compare("clWindstorm::ReadParFile" ) != 0 )
    {
      FAIL() << "TestWindstorm error processing caught wrong error for WriteWindstormXMLErrorFile1.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile( WriteWindstormXMLErrorFile2() );
    FAIL() << "TestWindstorm error processing didn't catch error for WriteWindstormXMLErrorFile2.";
  }
  catch ( modelErr& err )
  {
    if ( err.sFunction.compare("clWindstorm::GetDeadCodes" ) != 0 )
    {
      FAIL() << "TestWindstorm error processing caught wrong error for WriteWindstormXMLErrorFile2.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile( WriteWindstormXMLErrorFile3() );
    FAIL() << "TestWindstorm error processing didn't catch error for WriteWindstormXMLErrorFile3.";
  }
  catch ( modelErr& err )
  {
    if ( err.sFunction.compare("clWindstorm::ReadParFile" ) != 0 )
    {
      FAIL() << "TestWindstorm error processing caught wrong error for WriteWindstormXMLErrorFile3.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile( WriteWindstormXMLErrorFile4() );
    FAIL() << "TestWindstorm error processing didn't catch error for WriteWindstormXMLErrorFile4.";
  }
  catch ( modelErr& err )
  {
    if ( err.sFunction.compare("clWindstorm::ReadParFile" ) != 0 )
    {
      FAIL() << "TestWindstorm error processing caught wrong error for WriteWindstormXMLErrorFile4.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile( WriteWindstormXMLErrorFile5() );
    FAIL() << "TestWindstorm error processing didn't catch error for WriteWindstormXMLErrorFile5.";
  }
  catch ( modelErr& err )
  {
    if ( err.sFunction.compare("clWindstorm::GetDeadCodes" ) != 0 )
    {
      FAIL() << "TestWindstorm error processing caught wrong error for WriteWindstormXMLErrorFile5.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile( WriteWindstormXMLErrorFile6() );
    FAIL() << "TestWindstorm error processing didn't catch error for WriteWindstormXMLErrorFile6.";
  }
  catch ( modelErr& err )
  {
    if ( err.sFunction.compare("clWindstorm::ReadParFile" ) != 0 )
    {
      FAIL() << "TestWindstorm error processing caught wrong error for WriteWindstormXMLErrorFile6.";
    }
    ;
  }
  delete p_oSimManager;
}

/////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun1()
// Tests normal processing Run 1. WriteWindstormXMLFile1() writes the parameter file.
// Aspects of the run:
//
// -- 1 year per timestep.
// -- Snag run.
// -- This run tests correct damage calculation and killing.
// -- The following trees will be added, with a storm of 0.2 triggered
// for timestep 1:
//   -- Grid (0,0): 1000 trees of Species 1 and 2, DBH 30.
//   -- Grid (1,0): 1000 trees of Species 1 and 2, DBH 8.
//   -- All grids get 1000 trees of DBH 4, Species 1, and DBH 5, Species 2.
//
// The run proceeds for 1 timestep. The "Windstorm Results" grid is checked,
// and the actual number of trees alive and dead is checked as well.
/////////////////////////////////////////////////////////////////////////////
TEST(Windstorm, TestNormalProcessingRun1) {
  using namespace std;
  clTreePopulation * p_oPop;
  clGrid * p_oResultsGrid;
  clTreeSearch * p_oAllTrees;
  clTree * p_oTree;
  clPackage *p_oStormPackage;
  stringstream sMessage;
  float fX, fY, fDiam, fVal, fExpected;
  int iSp1, iSp2, iSnagSp1, iSnagSp2, iSp, i;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {

    //Feed our file to the sim manager
    p_oSimManager->ReadFile( WriteWindstormXMLFile1() );

    //Get the tree population
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Grid (0,0): 1000 trees of Species 1 and 2, DBH 30.
    //1000 trees of DBH 4, Species 1, and DBH 5, Species 2.
    fX = 1;  fY = 1;
    fDiam = 30;
    for ( i = 0; i < 1000; i++ )
    {
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, fDiam );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::adult, fDiam );
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::sapling, 4.0 );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::sapling, 5.0 );
    }

    //Grid (1,0): 1000 trees of Species 1 and 2, DBH 8.
    //1000 trees of DBH 4, Species 1, and DBH 5, Species 2.
    fX = 9; fY = 1;
    fDiam = 8;
    for ( i = 0; i < 1000; i++ )
    {
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, fDiam );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::adult, fDiam );
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::sapling, 4.0 );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::sapling, 5.0 );
    }

    p_oSimManager->RunSim( 1 );

    //Get all trees
    p_oAllTrees = p_oPop->Find( "all" );

    //>>>>>>>>>>>>Separate out and only do cell 0,0<<<<<<<<<<<<<<<<<<<<<<<
    iSp1 = 0; iSp2 = 0; iSnagSp1 = 0; iSnagSp2 = 0;
    p_oTree = p_oAllTrees->NextTree();
    while ( p_oTree )
    {
      iSp = p_oTree->GetSpecies();

      //Get X and Y
      p_oTree->GetValue( p_oPop->GetXCode( iSp, p_oTree->GetType() ), & fX );
      p_oTree->GetValue( p_oPop->GetYCode( iSp, p_oTree->GetType() ), & fY );

      if ( fX < 8 && fY < 8 )
      {
        if (clTreePopulation::snag == p_oTree->GetType() && 0 == iSp) {
          iSnagSp1++;
        }
        else if (clTreePopulation::snag == p_oTree->GetType() && 1 == iSp) {
          iSnagSp2++;
        }
        else if ( 0 == iSp )
        {
          iSp1++;
        }
        else if ( 1 == iSp )
        {
          iSp2++;
        }
        else
        {
          //Error
          sMessage << "TestNormalProcessingRun1 is panicking. It found a "
              << "tree it can't figure out.";
          FAIL() << sMessage.str();
        }
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    //Validate the counts
    fExpected = 1784.15;
    EXPECT_LT( fabs( fExpected - iSp1 ) / fExpected, 0.1 );
    fExpected = 1828.83;
    EXPECT_LT( fabs( fExpected - iSp2 ) / fExpected, 0.1 );
    fExpected = 215.841;
    EXPECT_LT( fabs( fExpected - iSnagSp1 ) / fExpected, 0.11 );
    fExpected = 171.164;
    EXPECT_LT( fabs( fExpected - iSnagSp2 ) / fExpected, 0.1 );




    //>>>>>>>>>>>>Separate out and only do cell 1, 0<<<<<<<<<<<<<<<<<<<<<<<
    iSp1 = 0; iSp2 = 0; iSnagSp1 = 0; iSnagSp2 = 0;
    p_oAllTrees->StartOver();
    p_oTree = p_oAllTrees->NextTree();
    while ( p_oTree )
    {
      iSp = p_oTree->GetSpecies();

      //Get X and Y
      p_oTree->GetValue( p_oPop->GetXCode( iSp, p_oTree->GetType() ), & fX );
      p_oTree->GetValue( p_oPop->GetYCode( iSp, p_oTree->GetType() ), & fY );

      if ( fX > 8 && fX < 16 && fY < 8 )
      {
        if (clTreePopulation::snag == p_oTree->GetType() && 0 == iSp) {
          iSnagSp1++;
        }
        else if (clTreePopulation::snag == p_oTree->GetType() && 1 == iSp) {
          iSnagSp2++;
        }
        else if ( 0 == iSp )
        {
          iSp1++;
        }
        else if ( 1 == iSp )
        {
          iSp2++;
        }
        else
        {
          //Error
          sMessage << "TestNormalProcessingRun1 is panicking. It found a "
              << "tree it can't figure out.";
          FAIL() << sMessage.str();
        }
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    fExpected = 1846.58;
    EXPECT_LT( fabs( fExpected - iSp1 ) / fExpected, 0.1 );
    fExpected = 1858.64;
    EXPECT_LT( fabs( fExpected - iSp2 ) / fExpected, 0.1 );
    fExpected = 153.41;
    EXPECT_LT( fabs( fExpected - iSnagSp1 ) / fExpected, 0.2 );
    fExpected = 141.35;
    EXPECT_LT( fabs( fExpected - iSnagSp2 ) / fExpected, 0.2 );

    //Get the "Windstorm Results" grid object
    p_oResultsGrid = p_oSimManager->GetGridObject( "Windstorm Results" );
    ASSERT_TRUE( p_oResultsGrid != NULL );

    //Verify that there is only one grid per cell
    EXPECT_EQ(1, p_oResultsGrid->GetNumberXCells());
    EXPECT_EQ(1, p_oResultsGrid->GetNumberYCells());

    //Verify that there's one storm package for the grid
    p_oStormPackage = p_oResultsGrid->GetFirstPackageOfCell(0, 0);
    ASSERT_TRUE(NULL != p_oStormPackage);
    EXPECT_EQ(NULL, p_oStormPackage->GetNextPackage());

    //Verify the storm results
    fExpected = 0.2;
    p_oStormPackage->GetValue(p_oResultsGrid->GetPackageFloatDataCode("severity"), &fVal);
    EXPECT_LT(fabs(fExpected - fVal), 0.001);

    fExpected = 10.685;
    p_oStormPackage->GetValue(p_oResultsGrid->GetPackageFloatDataCode("ba_0"), &fVal);
    EXPECT_LT(fabs(fExpected - fVal)/fExpected, 0.1);
    fExpected = 8.539;
    p_oStormPackage->GetValue(p_oResultsGrid->GetPackageFloatDataCode("ba_1"), &fVal);
    EXPECT_LT(fabs(fExpected - fVal)/fExpected, 0.1);

    fExpected = 246.168;
    p_oStormPackage->GetValue(p_oResultsGrid->GetPackageFloatDataCode("density_0"), &fVal);
    EXPECT_LT(fabs(fExpected - fVal)/fExpected, 0.1);
    fExpected = 208.348;
    p_oStormPackage->GetValue(p_oResultsGrid->GetPackageFloatDataCode("density_1"), &fVal);
    EXPECT_LT(fabs(fExpected - fVal)/fExpected, 0.1);

    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun2()
// Tests normal processing Run 2. WriteWindstormXMLFile2() writes the parameter file.
// Aspects of the run:
//
// -- 1 year per timestep.
// -- Snag run.
// -- This run tests correct damage calculation and killing.
// -- The following trees will be added, with a storm of 0.8 triggered
// for timestep 1:
//   -- Grid (0,0): 1000 trees of Species 1 and 2, DBH 30.
//   -- Grid (1,0): 1000 trees of Species 1 and 2, DBH 8.
//   -- All grids get 1000 trees of DBH 4, Species 1, and DBH 5, Species 2.
//
// The run proceeds for 1 timestep. The "Windstorm Results" grid is checked,
// and the actual number of trees alive and dead is checked as well.
/////////////////////////////////////////////////////////////////////////////
TEST(Windstorm, TestNormalProcessingRun2) {
  using namespace std;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clGrid * p_oResultsGrid;
    clTreeSearch * p_oAllTrees;
    clTree * p_oTree;
    clPackage *p_oStormPackage;
    stringstream sMessage;
    float fX, fY, fDiam, fVal, fExpected;
    int iSp1, iSp2, iSnagSp1, iSnagSp2, iSp, i;

    //Feed our file to the sim manager
    p_oSimManager->ReadFile( WriteWindstormXMLFile2() );

    //Get the tree population
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Grid (0,0): 1000 trees of Species 1 and 2, DBH 30.
    //1000 trees of DBH 4, Species 1, and DBH 5, Species 2.
    fX = 1;  fY = 1;
    fDiam = 30;
    for ( i = 0; i < 1000; i++ )
    {
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, fDiam );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::adult, fDiam );
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::sapling, 4.0 );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::sapling, 5.0 );
    }

    //Grid (1,0): 1000 trees of Species 1 and 2, DBH 8.
    //1000 trees of DBH 4, Species 1, and DBH 5, Species 2.
    fX = 9; fY = 1;
    fDiam = 8;
    for ( i = 0; i < 1000; i++ )
    {
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, fDiam );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::adult, fDiam );
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::sapling, 4.0 );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::sapling, 5.0 );
    }

    p_oSimManager->RunSim( 1 );

    //Get all trees
    p_oAllTrees = p_oPop->Find( "all" );

    //>>>>>>>>>>>>Separate out and only do cell 0,0<<<<<<<<<<<<<<<<<<<<<<<
    iSp1 = 0; iSp2 = 0; iSnagSp1 = 0; iSnagSp2 = 0;
    p_oTree = p_oAllTrees->NextTree();
    while ( p_oTree )
    {
      iSp = p_oTree->GetSpecies();

      //Get X and Y
      p_oTree->GetValue( p_oPop->GetXCode( iSp, p_oTree->GetType() ), & fX );
      p_oTree->GetValue( p_oPop->GetYCode( iSp, p_oTree->GetType() ), & fY );

      if ( fX < 8 && fY < 8 )
      {
        if (clTreePopulation::snag == p_oTree->GetType() && 0 == iSp) {
          iSnagSp1++;
        }
        else if (clTreePopulation::snag == p_oTree->GetType() && 1 == iSp) {
          iSnagSp2++;
        }
        else if ( 0 == iSp )
        {
          iSp1++;
        }
        else if ( 1 == iSp )
        {
          iSp2++;
        }
        else
        {
          //Error
          sMessage << "TestNormalProcessingRun2 is panicking. It found a "
              << "tree it can't figure out.";
          FAIL() << sMessage.str();
        }
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    //Validate the counts
    fExpected = 1164.829;
    EXPECT_LT( fabs( fExpected - iSp1 ) / fExpected, 0.1 );
    fExpected = 1605.774;
    EXPECT_LT( fabs( fExpected - iSp2 ) / fExpected, 0.1 );
    fExpected = 835.170;
    EXPECT_LT( fabs( fExpected - iSnagSp1 ) / fExpected, 0.1 );
    fExpected = 394.225;
    EXPECT_LT( fabs( fExpected - iSnagSp2 ) / fExpected, 0.1 );




    //>>>>>>>>>>>>Separate out and only do cell 1, 0<<<<<<<<<<<<<<<<<<<<<<<
    iSp1 = 0; iSp2 = 0; iSnagSp1 = 0; iSnagSp2 = 0;
    p_oAllTrees->StartOver();
    p_oTree = p_oAllTrees->NextTree();
    while ( p_oTree )
    {
      iSp = p_oTree->GetSpecies();

      //Get X and Y
      p_oTree->GetValue( p_oPop->GetXCode( iSp, p_oTree->GetType() ), & fX );
      p_oTree->GetValue( p_oPop->GetYCode( iSp, p_oTree->GetType() ), & fY );

      if ( fX > 8 && fX < 16 && fY < 8 )
      {
        if (clTreePopulation::snag == p_oTree->GetType() && 0 == iSp) {
          iSnagSp1++;
        }
        else if (clTreePopulation::snag == p_oTree->GetType() && 1 == iSp) {
          iSnagSp2++;
        }
        else if ( 0 == iSp )
        {
          iSp1++;
        }
        else if ( 1 == iSp )
        {
          iSp2++;
        }
        else
        {
          //Error
          sMessage << "TestNormalProcessingRun1 is panicking. It found a "
              << "tree it can't figure out.";
          FAIL() << sMessage.str();
        }
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    fExpected = 1512.341;
    EXPECT_LT( fabs( fExpected - iSp1 ) / fExpected, 0.1 );
    fExpected = 1791.865;
    EXPECT_LT( fabs( fExpected - iSp2 ) / fExpected, 0.1 );
    fExpected = 487.658;
    EXPECT_LT( fabs( fExpected - iSnagSp1 ) / fExpected, 0.1 );
    fExpected = 208.134;
    EXPECT_LT( fabs( fExpected - iSnagSp2 ) / fExpected, 0.1 );

    //Get the "Windstorm Results" grid object
    p_oResultsGrid = p_oSimManager->GetGridObject( "Windstorm Results" );
    ASSERT_TRUE( p_oResultsGrid != NULL );

    //Verify that there is only one grid per cell
    EXPECT_EQ(1, p_oResultsGrid->GetNumberXCells());
    EXPECT_EQ(1, p_oResultsGrid->GetNumberYCells());

    //Verify that there's one storm package for the grid
    p_oStormPackage = p_oResultsGrid->GetFirstPackageOfCell(0, 0);
    ASSERT_TRUE(NULL != p_oStormPackage);
    EXPECT_EQ(NULL, p_oStormPackage->GetNextPackage());

    //Verify the storm results
    fExpected = 0.8;
    p_oStormPackage->GetValue(p_oResultsGrid->GetPackageFloatDataCode("severity"), &fVal);
    EXPECT_LT(fabs(fExpected - fVal), 0.001);

    fExpected = 40.990;
    p_oStormPackage->GetValue(p_oResultsGrid->GetPackageFloatDataCode("ba_0"), &fVal);
    EXPECT_LT(fabs(fExpected - fVal)/fExpected, 0.1);
    fExpected = 19.274;
    p_oStormPackage->GetValue(p_oResultsGrid->GetPackageFloatDataCode("ba_1"), &fVal);
    EXPECT_LT(fabs(fExpected - fVal)/fExpected, 0.1);

    fExpected = 881.885;
    p_oStormPackage->GetValue(p_oResultsGrid->GetPackageFloatDataCode("density_0"), &fVal);
    EXPECT_LT(fabs(fExpected - fVal)/fExpected, 0.1);
    fExpected = 401.573;
    p_oStormPackage->GetValue(p_oResultsGrid->GetPackageFloatDataCode("density_1"), &fVal);
    EXPECT_LT(fabs(fExpected - fVal)/fExpected, 0.1);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun3()
// Tests normal processing Run 3. WriteWindstormXMLFile3() writes the parameter file.
// Aspects of the run:
//
// -- 3 years per timestep.
// -- Snag run.
// -- This run tests multiple storms per timestep, and making sure dead trees
// are ignored.
// -- The following trees will be added, with 3 storms of 0.2 triggered
// for timestep 1:
//   -- Grid (0,0): 1000 trees of Species 1 and 2, DBH 30.
//   -- Grid (1,0): 1000 trees of Species 1 and 2, DBH 8.
//
// The run proceeds for 1 timestep. The "Windstorm Results" grid is checked,
// and the actual number of trees alive and dead is checked as well.
/////////////////////////////////////////////////////////////////////////////
TEST(Windstorm, TestNormalProcessingRun3)
{
  using namespace std;
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clGrid * p_oResultsGrid;
    clTreeSearch * p_oAllTrees;
    clTree * p_oTree;
    clPackage *p_oStormPackage;
    stringstream sMessage;
    float fX, fY, fDiam, fVal, fExpected;
    int iSp1, iSp2, iSnagSp1, iSnagSp2, iSp, i;

    //Feed our file to the sim manager
    p_oSimManager->ReadFile( WriteWindstormXMLFile3() );

    //Get the tree population
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Grid (0,0): 1000 trees of Species 1 and 2, DBH 30.
    fX = 1;  fY = 1;
    fDiam = 30;
    for ( i = 0; i < 1000; i++ )
    {
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, fDiam );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::adult, fDiam );
    }

    //Grid (1,0): 1000 trees of Species 1 and 2, DBH 8.
    fX = 9; fY = 1;
    fDiam = 8;
    for ( i = 0; i < 1000; i++ )
    {
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, fDiam );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::adult, fDiam );
    }

    p_oSimManager->RunSim( 1 );

    //Get all trees
    p_oAllTrees = p_oPop->Find( "all" );

    //>>>>>>>>>>>>Separate out and only do cell 0,0<<<<<<<<<<<<<<<<<<<<<<<
    iSp1 = 0; iSp2 = 0; iSnagSp1 = 0; iSnagSp2 = 0;
    p_oTree = p_oAllTrees->NextTree();
    while ( p_oTree )
    {
      iSp = p_oTree->GetSpecies();

      //Get X and Y
      p_oTree->GetValue( p_oPop->GetXCode( iSp, p_oTree->GetType() ), & fX );
      p_oTree->GetValue( p_oPop->GetYCode( iSp, p_oTree->GetType() ), & fY );

      if ( fX < 8 && fY < 8 )
      {
        if (clTreePopulation::snag == p_oTree->GetType() && 0 == iSp) {
          iSnagSp1++;
        }
        else if (clTreePopulation::snag == p_oTree->GetType() && 1 == iSp) {
          iSnagSp2++;
        }
        else if ( 0 == iSp )
        {
          iSp1++;
        }
        else if ( 1 == iSp )
        {
          iSp2++;
        }
        else
        {
          //Error
          sMessage << "TestNormalProcessingRun3 is panicking. It found a "
              << "tree it can't figure out.";
          FAIL() << sMessage.str();
        }
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    //Validate the counts
    fExpected = 482.183;
    EXPECT_LT( fabs( fExpected - iSp1 ) / fExpected, 0.1 );
    fExpected = 569.383;
    EXPECT_LT( fabs( fExpected - iSp2 ) / fExpected, 0.1 );
    fExpected = 517.816;
    EXPECT_LT( fabs( fExpected - iSnagSp1 ) / fExpected, 0.1 );
    fExpected = 430.616;
    EXPECT_LT( fabs( fExpected - iSnagSp2 ) / fExpected, 0.1 );




    //>>>>>>>>>>>>Separate out and only do cell 1, 0<<<<<<<<<<<<<<<<<<<<<<<
    iSp1 = 0; iSp2 = 0; iSnagSp1 = 0; iSnagSp2 = 0;
    p_oAllTrees->StartOver();
    p_oTree = p_oAllTrees->NextTree();
    while ( p_oTree )
    {
      iSp = p_oTree->GetSpecies();

      //Get X and Y
      p_oTree->GetValue( p_oPop->GetXCode( iSp, p_oTree->GetType() ), & fX );
      p_oTree->GetValue( p_oPop->GetYCode( iSp, p_oTree->GetType() ), & fY );

      if ( fX > 8 && fX < 16 && fY < 8 )
      {
        if (clTreePopulation::snag == p_oTree->GetType() && 0 == iSp) {
          iSnagSp1++;
        }
        else if (clTreePopulation::snag == p_oTree->GetType() && 1 == iSp) {
          iSnagSp2++;
        }
        else if ( 0 == iSp )
        {
          iSp1++;
        }
        else if ( 1 == iSp )
        {
          iSp2++;
        }
        else
        {
          //Error
          sMessage << "TestNormalProcessingRun3 is panicking. It found a "
              << "tree it can't figure out.";
          FAIL() << sMessage.str();
        }
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    fExpected = 606.761;
    EXPECT_LT( fabs( fExpected - iSp1 ) / fExpected, 0.1 );
    fExpected = 633.046;
    EXPECT_LT( fabs( fExpected - iSp2 ) / fExpected, 0.1 );
    fExpected = 393.238;
    EXPECT_LT( fabs( fExpected - iSnagSp1 ) / fExpected, 0.1 );
    fExpected = 366.953;
    EXPECT_LT( fabs( fExpected - iSnagSp2 ) / fExpected, 0.1 );

    //Get the "Windstorm Results" grid object
    p_oResultsGrid = p_oSimManager->GetGridObject( "Windstorm Results" );
    ASSERT_TRUE( p_oResultsGrid != NULL );

    //Verify that there is only one grid per cell
    EXPECT_EQ(1, p_oResultsGrid->GetNumberXCells());
    EXPECT_EQ(1, p_oResultsGrid->GetNumberYCells());

    //Verify that the first storm's results
    p_oStormPackage = p_oResultsGrid->GetFirstPackageOfCell(0, 0);
    ASSERT_TRUE(NULL != p_oStormPackage);
    fExpected = 0.2;
    p_oStormPackage->GetValue(p_oResultsGrid->GetPackageFloatDataCode("severity"), &fVal);
    EXPECT_LT(fabs(fExpected - fVal), 0.001);

    fExpected = 10.685;
    p_oStormPackage->GetValue(p_oResultsGrid->GetPackageFloatDataCode("ba_0"), &fVal);
    EXPECT_LT(fabs(fExpected - fVal)/fExpected, 0.1);
    fExpected = 8.539;
    p_oStormPackage->GetValue(p_oResultsGrid->GetPackageFloatDataCode("ba_1"), &fVal);
    EXPECT_LT(fabs(fExpected - fVal)/fExpected, 0.1);

    fExpected = 246.168;
    p_oStormPackage->GetValue(p_oResultsGrid->GetPackageFloatDataCode("density_0"), &fVal);
    EXPECT_LT(fabs(fExpected - fVal)/fExpected, 0.1);
    fExpected = 208.348;
    p_oStormPackage->GetValue(p_oResultsGrid->GetPackageFloatDataCode("density_1"), &fVal);
    EXPECT_LT(fabs(fExpected - fVal)/fExpected, 0.1);

    //Verify the second storm's results
    p_oStormPackage = p_oStormPackage->GetNextPackage();
    ASSERT_TRUE(NULL != p_oStormPackage);
    fExpected = 0.2;
    p_oStormPackage->GetValue(p_oResultsGrid->GetPackageFloatDataCode("severity"), &fVal);
    EXPECT_LT(fabs(fExpected - fVal), 0.001);

    fExpected = 8.411;
    p_oStormPackage->GetValue(p_oResultsGrid->GetPackageFloatDataCode("ba_0"), &fVal);
    EXPECT_LT(fabs(fExpected - fVal)/fExpected, 0.1);
    fExpected = 7.092;
    p_oStormPackage->GetValue(p_oResultsGrid->GetPackageFloatDataCode("ba_1"), &fVal);
    EXPECT_LT(fabs(fExpected - fVal)/fExpected, 0.1);

    fExpected = 199.419;
    p_oStormPackage->GetValue(p_oResultsGrid->GetPackageFloatDataCode("density_0"), &fVal);
    EXPECT_LT(fabs(fExpected - fVal)/fExpected, 0.1);
    fExpected = 175.495;
    p_oStormPackage->GetValue(p_oResultsGrid->GetPackageFloatDataCode("density_1"), &fVal);
    EXPECT_LT(fabs(fExpected - fVal)/fExpected, 0.1);

    //Verify the third storm's results
    p_oStormPackage = p_oStormPackage->GetNextPackage();
    ASSERT_TRUE(NULL != p_oStormPackage);
    fExpected = 0.2;
    p_oStormPackage->GetValue(p_oResultsGrid->GetPackageFloatDataCode("severity"), &fVal);
    EXPECT_LT(fabs(fExpected - fVal), 0.001);

    fExpected = 6.622;
    p_oStormPackage->GetValue(p_oResultsGrid->GetPackageFloatDataCode("ba_0"), &fVal);
    EXPECT_LT(fabs(fExpected - fVal)/fExpected, 0.1);
    fExpected = 5.890;
    p_oStormPackage->GetValue(p_oResultsGrid->GetPackageFloatDataCode("ba_1"), &fVal);
    EXPECT_LT(fabs(fExpected - fVal)/fExpected, 0.12);

    fExpected = 161.782;
    p_oStormPackage->GetValue(p_oResultsGrid->GetPackageFloatDataCode("density_0"), &fVal);
    EXPECT_LT(fabs(fExpected - fVal)/fExpected, 0.2);
    fExpected = 147.868;
    p_oStormPackage->GetValue(p_oResultsGrid->GetPackageFloatDataCode("density_1"), &fVal);
    EXPECT_LT(fabs(fExpected - fVal)/fExpected, 0.2);

    //Verify that that's the last one
    EXPECT_EQ(NULL, p_oStormPackage->GetNextPackage());
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun4()
// Tests normal processing Run 4. WriteWindstormXMLFile4() writes the parameter file.
// Aspects of the run:
//
// -- 1 year per timestep.
// -- No snags.
// -- This run tests correct handling when there are no snags.
// -- The following trees will be added, with a storm of 0.4 triggered
// for timestep 1:
//   -- Grid (0,0): 1000 trees of Species 1 and 2, DBH 30.
//   -- Grid (1,0): 1000 trees of Species 1 and 2, DBH 8.
//   -- All grids get 1000 trees of DBH 4, Species 1, and DBH 5, Species 2.
//
// The run proceeds for 1 timestep. The "Windstorm Results" grid is checked,
// and the actual number of trees alive and dead is checked as well.
/////////////////////////////////////////////////////////////////////////////
TEST(Windstorm, TestNormalProcessingRun4)
{
  using namespace std;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clGrid * p_oResultsGrid;
    clTreeSearch * p_oAllTrees;
    clTree * p_oTree;
    clPackage *p_oStormPackage;
    stringstream sMessage;
    float fX, fY, fDiam, fVal, fExpected;
    int iSp1, iSp2, iSp, i;

    //Feed our file to the sim manager
    p_oSimManager->ReadFile( WriteWindstormXMLFile4() );

    //Get the tree population
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Grid (0,0): 1000 trees of Species 1 and 2, DBH 30.
    fX = 1;  fY = 1;
    fDiam = 30;
    for ( i = 0; i < 1000; i++ )
    {
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, fDiam );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::adult, fDiam );
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::sapling, 4.0 );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::sapling, 5.0 );
    }

    //Grid (1,0): 1000 trees of Species 1 and 2, DBH 8.
    fX = 9; fY = 1;
    fDiam = 8;
    for ( i = 0; i < 1000; i++ )
    {
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, fDiam );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::adult, fDiam );
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::sapling, 4.0 );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::sapling, 5.0 );
    }

    p_oSimManager->RunSim( 1 );

    //Get all trees
    p_oAllTrees = p_oPop->Find( "all" );

    //>>>>>>>>>>>>Separate out and only do cell 0,0<<<<<<<<<<<<<<<<<<<<<<<
    iSp1 = 0; iSp2 = 0;
    p_oTree = p_oAllTrees->NextTree();
    while ( p_oTree )
    {
      iSp = p_oTree->GetSpecies();

      //Get X and Y
      p_oTree->GetValue( p_oPop->GetXCode( iSp, p_oTree->GetType() ), & fX );
      p_oTree->GetValue( p_oPop->GetYCode( iSp, p_oTree->GetType() ), & fY );

      ASSERT_TRUE(clTreePopulation::snag != p_oTree->GetType());

      if ( fX < 8 && fY < 8 )
      {
        if ( 0 == iSp )
        {
          iSp1++;
        }
        else if ( 1 == iSp )
        {
          iSp2++;
        }
        else
        {
          //Error
          sMessage << "TestNormalProcessingRun4 is panicking. It found a "
              << "tree it can't figure out.";
          FAIL() << sMessage.str();
        }
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    //Validate the counts
    fExpected = 1579.114;
    EXPECT_LT( fabs( fExpected - iSp1 ) / fExpected, 0.1 );
    fExpected = 1767.597;
    EXPECT_LT( fabs( fExpected - iSp2 ) / fExpected, 0.1 );



    //>>>>>>>>>>>>Separate out and only do cell 1, 0<<<<<<<<<<<<<<<<<<<<<<<
    iSp1 = 0; iSp2 = 0;
    p_oAllTrees->StartOver();
    p_oTree = p_oAllTrees->NextTree();
    while ( p_oTree )
    {
      iSp = p_oTree->GetSpecies();

      //Get X and Y
      p_oTree->GetValue( p_oPop->GetXCode( iSp, p_oTree->GetType() ), & fX );
      p_oTree->GetValue( p_oPop->GetYCode( iSp, p_oTree->GetType() ), & fY );

      if ( fX > 8 && fX < 16 && fY < 8 )
      {
        if ( 0 == iSp )
        {
          iSp1++;
        }
        else if ( 1 == iSp )
        {
          iSp2++;
        }
        else
        {
          //Error
          sMessage << "TestNormalProcessingRun4 is panicking. It found a "
              << "tree it can't figure out.";
          FAIL() << sMessage.str();
        }
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    fExpected = 1760.457;
    EXPECT_LT( fabs( fExpected - iSp1 ) / fExpected, 0.1 );
    fExpected = 1838.634;
    EXPECT_LT( fabs( fExpected - iSp2 ) / fExpected, 0.1 );

    //Get the "Windstorm Results" grid object
    p_oResultsGrid = p_oSimManager->GetGridObject( "Windstorm Results" );
    ASSERT_TRUE( p_oResultsGrid != NULL );

    //Verify that there is only one grid per cell
    EXPECT_EQ(1, p_oResultsGrid->GetNumberXCells());
    EXPECT_EQ(1, p_oResultsGrid->GetNumberYCells());

    //Verify that there's one storm package for the grid
    p_oStormPackage = p_oResultsGrid->GetFirstPackageOfCell(0, 0);
    ASSERT_TRUE(NULL != p_oStormPackage);
    EXPECT_EQ(NULL, p_oStormPackage->GetNextPackage());

    //Verify the storm results
    fExpected = 0.4;
    p_oStormPackage->GetValue(p_oResultsGrid->GetPackageFloatDataCode("severity"), &fVal);
    EXPECT_LT(fabs(fExpected - fVal), 0.001);

    fExpected = 20.636;
    p_oStormPackage->GetValue(p_oResultsGrid->GetPackageFloatDataCode("ba_0"), &fVal);
    EXPECT_LT(fabs(fExpected - fVal)/fExpected, 0.1);
    fExpected = 11.492;
    p_oStormPackage->GetValue(p_oResultsGrid->GetPackageFloatDataCode("ba_1"), &fVal);
    EXPECT_LT(fabs(fExpected - fVal)/fExpected, 0.1);

    fExpected = 440.285;
    p_oStormPackage->GetValue(p_oResultsGrid->GetPackageFloatDataCode("density_0"), &fVal);
    EXPECT_LT(fabs(fExpected - fVal)/fExpected, 0.1);
    fExpected = 262.512;
    p_oStormPackage->GetValue(p_oResultsGrid->GetPackageFloatDataCode("density_1"), &fVal);
    EXPECT_LT(fabs(fExpected - fVal)/fExpected, 0.1);

    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun5()
// Tests normal processing Run 5. WriteWindstormXMLFile5() writes the parameter file.
// Storm severities for all return intervals are 0, and this makes sure that
// no storms occur.
//
// The run proceeds for 1 timestep. The "Windstorm Results" grid is checked,
// and the actual number of trees alive and dead is checked as well to make
// sure nothing died.
/////////////////////////////////////////////////////////////////////////////
TEST(Windstorm, TestNormalProcessingRun5)
{
  using namespace std;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clGrid * p_oResultsGrid;
    clTreeSearch * p_oAllTrees;
    clTree * p_oTree;
    stringstream sMessage;
    float fX, fY, fDiam;
    int iSp1, iSp2, iSp, i;

    //Feed our file to the sim manager
    p_oSimManager->ReadFile( WriteWindstormXMLFile5() );

    //Get the tree population
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Grid (0,0): 1000 trees of Species 1 and 2, DBH 30.
    fX = 1;  fY = 1;
    fDiam = 30;
    for ( i = 0; i < 1000; i++ )
    {
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, fDiam );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::adult, fDiam );
    }

    //Grid (1,0): 1000 trees of Species 1 and 2, DBH 8.
    fX = 9; fY = 1;
    fDiam = 8;
    for ( i = 0; i < 1000; i++ )
    {
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, fDiam );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::adult, fDiam );
    }

    p_oSimManager->RunSim( 1 );

    //Get all trees
    p_oAllTrees = p_oPop->Find( "all" );

    //>>>>>>>>>>>>Separate out and only do cell 0,0<<<<<<<<<<<<<<<<<<<<<<<
    iSp1 = 0; iSp2 = 0;
    p_oTree = p_oAllTrees->NextTree();
    while ( p_oTree )
    {
      iSp = p_oTree->GetSpecies();

      //Get X and Y
      p_oTree->GetValue( p_oPop->GetXCode( iSp, p_oTree->GetType() ), & fX );
      p_oTree->GetValue( p_oPop->GetYCode( iSp, p_oTree->GetType() ), & fY );

      ASSERT_TRUE(clTreePopulation::snag != p_oTree->GetType());

      if ( fX < 8 && fY < 8 )
      {
        if ( 0 == iSp )
        {
          iSp1++;
        }
        else if ( 1 == iSp )
        {
          iSp2++;
        }
        else
        {
          //Error
          sMessage << "TestNormalProcessingRun5 is panicking. It found a "
              << "tree it can't figure out.";
          FAIL() << sMessage.str();
        }
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    //Validate the counts
    EXPECT_EQ( 1000, iSp1 );
    EXPECT_EQ( 1000, iSp2 );



    //>>>>>>>>>>>>Separate out and only do cell 1, 0<<<<<<<<<<<<<<<<<<<<<<<
    iSp1 = 0; iSp2 = 0;
    p_oAllTrees->StartOver();
    p_oTree = p_oAllTrees->NextTree();
    while ( p_oTree )
    {
      iSp = p_oTree->GetSpecies();

      //Get X and Y
      p_oTree->GetValue( p_oPop->GetXCode( iSp, p_oTree->GetType() ), & fX );
      p_oTree->GetValue( p_oPop->GetYCode( iSp, p_oTree->GetType() ), & fY );

      if ( fX > 8 && fX < 16 && fY < 8 )
      {
        if ( 0 == iSp )
        {
          iSp1++;
        }
        else if ( 1 == iSp )
        {
          iSp2++;
        }
        else
        {
          //Error
          sMessage << "TestNormalProcessingRun5 is panicking. It found a "
              << "tree it can't figure out.";
          FAIL() << sMessage.str();
        }
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    EXPECT_EQ( 1000, iSp1 );
    EXPECT_EQ( 1000, iSp2 );

    //Get the "Windstorm Results" grid object
    p_oResultsGrid = p_oSimManager->GetGridObject( "Windstorm Results" );
    ASSERT_TRUE( p_oResultsGrid != NULL );

    //Verify that there is only one grid per cell
    EXPECT_EQ(1, p_oResultsGrid->GetNumberXCells());
    EXPECT_EQ(1, p_oResultsGrid->GetNumberYCells());

    //Verify that there's no storm package for the grid
    EXPECT_EQ(NULL, p_oResultsGrid->GetFirstPackageOfCell(0, 0));
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun6()
// Tests normal processing Run 6. WriteWindstormXMLFile6() writes the parameter file.
// Aspects of the run:
//
// -- 1 year per timestep.
// -- No snags.
// -- This run tests when storms don't start at timestep 1.
// -- The following trees will be added, with a storm of 0.5 triggered
// for timestep 2:
//   -- Grid (0,0): 1000 trees of Species 1 and 2, DBH 30.
//   -- Grid (1,0): 1000 trees of Species 1 and 2, DBH 8.
//
// The run proceeds for 2 timesteps. The "Windstorm Results" grid is checked,
// and the actual number of trees alive and dead is checked as well. No storm
// should occur for timestep 1.
/////////////////////////////////////////////////////////////////////////////
TEST(Windstorm, TestNormalProcessingRun6) {
  using namespace std;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clGrid * p_oResultsGrid;
    clTreeSearch * p_oAllTrees;
    clTree * p_oTree;
    clPackage *p_oStormPackage;
    stringstream sMessage;
    float fX, fY, fDiam, fVal, fExpected;
    int iSp1, iSp2, iSp, i;

    //Feed our file to the sim manager
    p_oSimManager->ReadFile( WriteWindstormXMLFile6() );

    //Get the tree population
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Grid (0,0): 1000 trees of Species 1 and 2, DBH 30.
    fX = 1;  fY = 1;
    fDiam = 30;
    for ( i = 0; i < 1000; i++ )
    {
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, fDiam );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::adult, fDiam );
    }

    //Grid (1,0): 1000 trees of Species 1 and 2, DBH 8.
    fX = 9; fY = 1;
    fDiam = 8;
    for ( i = 0; i < 1000; i++ )
    {
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, fDiam );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::adult, fDiam );
    }

    p_oSimManager->RunSim( 1 );

    //Get all trees
    p_oAllTrees = p_oPop->Find( "all" );

    //>>>>>>>>>>>>Separate out and only do cell 0,0<<<<<<<<<<<<<<<<<<<<<<<
    iSp1 = 0; iSp2 = 0;
    p_oTree = p_oAllTrees->NextTree();
    while ( p_oTree )
    {
      iSp = p_oTree->GetSpecies();

      //Get X and Y
      p_oTree->GetValue( p_oPop->GetXCode( iSp, p_oTree->GetType() ), & fX );
      p_oTree->GetValue( p_oPop->GetYCode( iSp, p_oTree->GetType() ), & fY );

      ASSERT_TRUE(clTreePopulation::snag != p_oTree->GetType());

      if ( fX < 8 && fY < 8 )
      {
        if ( 0 == iSp )
        {
          iSp1++;
        }
        else if ( 1 == iSp )
        {
          iSp2++;
        }
        else
        {
          //Error
          sMessage << "TestNormalProcessingRun6 is panicking. It found a "
              << "tree it can't figure out.";
          FAIL() << sMessage.str();
        }
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    //Validate the counts
    EXPECT_EQ( 1000, iSp1 );
    EXPECT_EQ( 1000, iSp2 );



    //>>>>>>>>>>>>Separate out and only do cell 1, 0<<<<<<<<<<<<<<<<<<<<<<<
    iSp1 = 0; iSp2 = 0;
    p_oAllTrees->StartOver();
    p_oTree = p_oAllTrees->NextTree();
    while ( p_oTree )
    {
      iSp = p_oTree->GetSpecies();

      //Get X and Y
      p_oTree->GetValue( p_oPop->GetXCode( iSp, p_oTree->GetType() ), & fX );
      p_oTree->GetValue( p_oPop->GetYCode( iSp, p_oTree->GetType() ), & fY );

      if ( fX > 8 && fX < 16 && fY < 8 )
      {
        if ( 0 == iSp )
        {
          iSp1++;
        }
        else if ( 1 == iSp )
        {
          iSp2++;
        }
        else
        {
          //Error
          sMessage << "TestNormalProcessingRun6 is panicking. It found a "
              << "tree it can't figure out.";
          FAIL() << sMessage.str();
        }
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    EXPECT_EQ( 1000, iSp1 );
    EXPECT_EQ( 1000, iSp2 );

    //Get the "Windstorm Results" grid object
    p_oResultsGrid = p_oSimManager->GetGridObject( "Windstorm Results" );
    ASSERT_TRUE( p_oResultsGrid != NULL );

    //Verify that there is only one grid per cell
    EXPECT_EQ(1, p_oResultsGrid->GetNumberXCells());
    EXPECT_EQ(1, p_oResultsGrid->GetNumberYCells());

    //Verify that there's no storm package for the grid
    EXPECT_EQ(NULL, p_oResultsGrid->GetFirstPackageOfCell(0, 0));

    //>>>>>>>>>>>>Run another timestep<<<<<<<<<<<<<<<<<<<<<<<
    p_oSimManager->RunSim( 1 );

    //Get all trees
    p_oAllTrees = p_oPop->Find( "all" );

    //>>>>>>>>>>>>Separate out and only do cell 0,0<<<<<<<<<<<<<<<<<<<<<<<
    iSp1 = 0; iSp2 = 0;
    p_oTree = p_oAllTrees->NextTree();
    while ( p_oTree )
    {
      iSp = p_oTree->GetSpecies();

      //Get X and Y
      p_oTree->GetValue( p_oPop->GetXCode( iSp, p_oTree->GetType() ), & fX );
      p_oTree->GetValue( p_oPop->GetYCode( iSp, p_oTree->GetType() ), & fY );

      ASSERT_TRUE(clTreePopulation::snag != p_oTree->GetType());

      if ( fX < 8 && fY < 8 )
      {
        if ( 0 == iSp )
        {
          iSp1++;
        }
        else if ( 1 == iSp )
        {
          iSp2++;
        }
        else
        {
          //Error
          sMessage << "TestNormalProcessingRun6 is panicking. It found a "
              << "tree it can't figure out.";
          FAIL() << sMessage.str();
        }
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    //Validate the counts
    fExpected = 458.513;
    EXPECT_LT( fabs( fExpected - iSp1 ) / fExpected, 0.1 );
    fExpected = 731.744;
    EXPECT_LT( fabs( fExpected - iSp2 ) / fExpected, 0.1 );



    //>>>>>>>>>>>>Separate out and only do cell 1, 0<<<<<<<<<<<<<<<<<<<<<<<
    iSp1 = 0; iSp2 = 0;
    p_oAllTrees->StartOver();
    p_oTree = p_oAllTrees->NextTree();
    while ( p_oTree )
    {
      iSp = p_oTree->GetSpecies();

      //Get X and Y
      p_oTree->GetValue( p_oPop->GetXCode( iSp, p_oTree->GetType() ), & fX );
      p_oTree->GetValue( p_oPop->GetYCode( iSp, p_oTree->GetType() ), & fY );

      if ( fX > 8 && fX < 16 && fY < 8 )
      {
        if ( 0 == iSp )
        {
          iSp1++;
        }
        else if ( 1 == iSp )
        {
          iSp2++;
        }
        else
        {
          //Error
          sMessage << "TestNormalProcessingRun6 is panicking. It found a "
              << "tree it can't figure out.";
          FAIL() << sMessage.str();
        }
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    fExpected = 706.56;
    EXPECT_LT( fabs( fExpected - iSp1 ) / fExpected, 0.1 );
    fExpected = 827.801;
    EXPECT_LT( fabs( fExpected - iSp2 ) / fExpected, 0.1 );

    //Verify that there's one storm package for the grid
    p_oStormPackage = p_oResultsGrid->GetFirstPackageOfCell(0, 0);
    ASSERT_TRUE(NULL != p_oStormPackage);
    EXPECT_EQ(NULL, p_oStormPackage->GetNextPackage());

    //Verify the storm results
    fExpected = 0.5;
    p_oStormPackage->GetValue(p_oResultsGrid->GetPackageFloatDataCode("severity"), &fVal);
    EXPECT_LT(fabs(fExpected - fVal), 0.001);

    fExpected = 26.500;
    p_oStormPackage->GetValue(p_oResultsGrid->GetPackageFloatDataCode("ba_0"), &fVal);
    EXPECT_LT(fabs(fExpected - fVal)/fExpected, 0.1);
    fExpected = 13.218;
    p_oStormPackage->GetValue(p_oResultsGrid->GetPackageFloatDataCode("ba_1"), &fVal);
    EXPECT_LT(fabs(fExpected - fVal)/fExpected, 0.1);

    fExpected = 556.617;
    p_oStormPackage->GetValue(p_oResultsGrid->GetPackageFloatDataCode("density_0"), &fVal);
    EXPECT_LT(fabs(fExpected - fVal)/fExpected, 0.1);
    fExpected = 293.635;
    p_oStormPackage->GetValue(p_oResultsGrid->GetPackageFloatDataCode("density_1"), &fVal);
    EXPECT_LT(fabs(fExpected - fVal)/fExpected, 0.1);

    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun7()
// Tests normal processing Run 7. WriteWindstormXMLFile7() writes the parameter file.
// This run tests to make sure the "Windstorm Results" grid is refreshed for
// each timestep.
//
// The 1 year return interval is 0. This runs for 2 timesteps, and verifies
// that the results for the two in the "Windstorm Results" grid are different.
/////////////////////////////////////////////////////////////////////////////
TEST(Windstorm, TestNormalProcessingRun7)
{
  using namespace std;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clGrid * p_oResultsGrid;
    clPackage *p_oStormPackage;
    stringstream sMessage;
    float fX, fY, fDiam, fVal, fExpected,
    fTS1BA0 = 0, fTS1BA1 = 0, fTS1Dens0 = 0, fTS1Dens1 = 0;
    int i;

    //Feed our file to the sim manager
    p_oSimManager->ReadFile( WriteWindstormXMLFile7() );

    //Get the tree population
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Grid (0,0): 1000 trees of Species 1 and 2, DBH 30.
    fX = 1;  fY = 1;
    fDiam = 30;
    for ( i = 0; i < 1000; i++ )
    {
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, fDiam );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::adult, fDiam );
    }

    //Grid (1,0): 1000 trees of Species 1 and 2, DBH 8.
    fX = 9; fY = 1;
    fDiam = 8;
    for ( i = 0; i < 1000; i++ )
    {
      p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, fDiam );
      p_oPop->CreateTree( fX, fY, 1, clTreePopulation::adult, fDiam );
    }

    p_oSimManager->RunSim( 1 );

    //Get the "Windstorm Results" grid object
    p_oResultsGrid = p_oSimManager->GetGridObject( "Windstorm Results" );
    ASSERT_TRUE( p_oResultsGrid != NULL );

    //Verify that there is only one grid per cell
    EXPECT_EQ(1, p_oResultsGrid->GetNumberXCells());
    EXPECT_EQ(1, p_oResultsGrid->GetNumberYCells());

    p_oStormPackage = p_oResultsGrid->GetFirstPackageOfCell(0, 0);
    ASSERT_TRUE (NULL != p_oStormPackage);
    EXPECT_EQ(NULL, p_oStormPackage->GetNextPackage());

    //Verify the severity
    fExpected = 0.1;
    p_oStormPackage->GetValue(p_oResultsGrid->GetPackageFloatDataCode("severity"), &fVal);
    EXPECT_LT(fabs(fExpected - fVal), 0.001);

    //Collect the other values - we don't care what they are, we'll just save
    //them for comparison with timestep 2
    p_oStormPackage->GetValue(p_oResultsGrid->GetPackageFloatDataCode("ba_0"), &fTS1BA0);
    p_oStormPackage->GetValue(p_oResultsGrid->GetPackageFloatDataCode("ba_1"), &fTS1BA1);
    p_oStormPackage->GetValue(p_oResultsGrid->GetPackageFloatDataCode("density_0"), &fTS1Dens0);
    p_oStormPackage->GetValue(p_oResultsGrid->GetPackageFloatDataCode("density_1"), &fTS1Dens1);

    //Run another timestep and verify that it has results that are different
    p_oSimManager->RunSim( 1 );

    p_oStormPackage = p_oResultsGrid->GetFirstPackageOfCell(0, 0);
    ASSERT_TRUE (NULL != p_oStormPackage);
    EXPECT_EQ(NULL, p_oStormPackage->GetNextPackage());

    //Verify the severity
    fExpected = 0.1;
    p_oStormPackage->GetValue(p_oResultsGrid->GetPackageFloatDataCode("severity"), &fVal);
    EXPECT_LT(fabs(fExpected - fVal), 0.001);

    //Collect the other values and make sure they're different from timestep 1
    p_oStormPackage->GetValue(p_oResultsGrid->GetPackageFloatDataCode("ba_0"), &fVal);
    EXPECT_GT(fabs(fTS1BA0 - fVal), 0.01);
    p_oStormPackage->GetValue(p_oResultsGrid->GetPackageFloatDataCode("ba_1"), &fVal);
    EXPECT_GT(fabs(fTS1BA1 - fVal), 0.01);
    p_oStormPackage->GetValue(p_oResultsGrid->GetPackageFloatDataCode("density_0"), &fVal);
    EXPECT_GT(fabs(fTS1Dens0 - fVal), 1);
    p_oStormPackage->GetValue(p_oResultsGrid->GetPackageFloatDataCode("density_1"), &fVal);
    EXPECT_GT(fabs(fTS1Dens1 - fVal), 1);

    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// WriteWindstormXMLFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteWindstormXMLFile1()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>2</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>";

  WriteWindstormCommonStuff(oOut);
  WriteWindstormSnagBehaviorList(oOut);

  oOut << "<Windstorm2>"
       << "<ws_severityReturnInterval1>0.2</ws_severityReturnInterval1>"
       << "<ws_severityReturnInterval5>0</ws_severityReturnInterval5>"
       << "<ws_severityReturnInterval10>0</ws_severityReturnInterval10>"
       << "<ws_severityReturnInterval20>0</ws_severityReturnInterval20>"
       << "<ws_severityReturnInterval40>0</ws_severityReturnInterval40>"
       << "<ws_severityReturnInterval80>0</ws_severityReturnInterval80>"
       << "<ws_severityReturnInterval160>0</ws_severityReturnInterval160>"
       << "<ws_severityReturnInterval320>0</ws_severityReturnInterval320>"
       << "<ws_severityReturnInterval640>0</ws_severityReturnInterval640>"
       << "<ws_severityReturnInterval1280>0</ws_severityReturnInterval1280>"
       << "<ws_severityReturnInterval2560>0</ws_severityReturnInterval2560>"
       << "<ws_minDBH>"
       << "<ws_mdVal species=\"Species_1\">5</ws_mdVal>"
       << "<ws_mdVal species=\"Species_2\">6</ws_mdVal>"
       << "</ws_minDBH>"
       << "<ws_stmInterceptA>"
       << "<ws_siaVal species=\"Species_1\">-2.261</ws_siaVal>"
       << "<ws_siaVal species=\"Species_2\">-1.96</ws_siaVal>"
       << "</ws_stmInterceptA>"
       << "<ws_stmIntensCoeffC>"
       << "<ws_sicVal species=\"Species_1\">1.14</ws_sicVal>"
       << "<ws_sicVal species=\"Species_2\">0.19</ws_sicVal>"
       << "</ws_stmIntensCoeffC>"
       << "<ws_stmDBHExpB>"
       << "<ws_sdebVal species=\"Species_1\">0.426</ws_sdebVal>"
       << "<ws_sdebVal species=\"Species_2\">0.679</ws_sdebVal>"
       << "</ws_stmDBHExpB>"
       << "<ws_stmTSToStartStorms>0</ws_stmTSToStartStorms>"
       << "<ws_stmSSTPeriod>1</ws_stmSSTPeriod>"
       << "<ws_stmSineD>0</ws_stmSineD>"
       << "<ws_stmSineF>1</ws_stmSineF>"
       << "<ws_stmSineG>1</ws_stmSineG>"
       << "<ws_stmTrendSlopeM>0</ws_stmTrendSlopeM>"
       << "<ws_stmTrendInterceptI>1</ws_stmTrendInterceptI>"
       << "</Windstorm2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;

}

/////////////////////////////////////////////////////////////////////////////
// WriteWindstormXMLFile2()
/////////////////////////////////////////////////////////////////////////////
const char* WriteWindstormXMLFile2()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>2</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>";

  WriteWindstormCommonStuff(oOut);
  WriteWindstormSnagBehaviorList(oOut);

  oOut << "<Windstorm2>"
       << "<ws_severityReturnInterval1>0.8</ws_severityReturnInterval1>"
       << "<ws_severityReturnInterval5>0</ws_severityReturnInterval5>"
       << "<ws_severityReturnInterval10>0</ws_severityReturnInterval10>"
       << "<ws_severityReturnInterval20>0</ws_severityReturnInterval20>"
       << "<ws_severityReturnInterval40>0</ws_severityReturnInterval40>"
       << "<ws_severityReturnInterval80>0</ws_severityReturnInterval80>"
       << "<ws_severityReturnInterval160>0</ws_severityReturnInterval160>"
       << "<ws_severityReturnInterval320>0</ws_severityReturnInterval320>"
       << "<ws_severityReturnInterval640>0</ws_severityReturnInterval640>"
       << "<ws_severityReturnInterval1280>0</ws_severityReturnInterval1280>"
       << "<ws_severityReturnInterval2560>0</ws_severityReturnInterval2560>"
       << "<ws_minDBH>"
       << "<ws_mdVal species=\"Species_1\">5</ws_mdVal>"
       << "<ws_mdVal species=\"Species_2\">6</ws_mdVal>"
       << "</ws_minDBH>"
       << "<ws_stmInterceptA>"
       << "<ws_siaVal species=\"Species_1\">-2.261</ws_siaVal>"
       << "<ws_siaVal species=\"Species_2\">-1.96</ws_siaVal>"
       << "</ws_stmInterceptA>"
       << "<ws_stmIntensCoeffC>"
       << "<ws_sicVal species=\"Species_1\">1.14</ws_sicVal>"
       << "<ws_sicVal species=\"Species_2\">0.19</ws_sicVal>"
       << "</ws_stmIntensCoeffC>"
       << "<ws_stmDBHExpB>"
       << "<ws_sdebVal species=\"Species_1\">0.426</ws_sdebVal>"
       << "<ws_sdebVal species=\"Species_2\">0.679</ws_sdebVal>"
       << "</ws_stmDBHExpB>"
       << "<ws_stmTSToStartStorms>1</ws_stmTSToStartStorms>"
       << "<ws_stmSSTPeriod>1</ws_stmSSTPeriod>"
       << "<ws_stmSineD>0</ws_stmSineD>"
       << "<ws_stmSineF>1</ws_stmSineF>"
       << "<ws_stmSineG>1</ws_stmSineG>"
       << "<ws_stmTrendSlopeM>0</ws_stmTrendSlopeM>"
       << "<ws_stmTrendInterceptI>1</ws_stmTrendInterceptI>"
       << "</Windstorm2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;

}

/////////////////////////////////////////////////////////////////////////////
// WriteWindstormXMLFile3()
/////////////////////////////////////////////////////////////////////////////
const char* WriteWindstormXMLFile3()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>2</timesteps>"
       << "<yearsPerTimestep>3</yearsPerTimestep>";

  WriteWindstormCommonStuff(oOut);
  WriteWindstormSnagBehaviorList(oOut);

  oOut << "<Windstorm2>"
       << "<ws_severityReturnInterval1>0.2</ws_severityReturnInterval1>"
       << "<ws_severityReturnInterval5>0</ws_severityReturnInterval5>"
       << "<ws_severityReturnInterval10>0</ws_severityReturnInterval10>"
       << "<ws_severityReturnInterval20>0</ws_severityReturnInterval20>"
       << "<ws_severityReturnInterval40>0</ws_severityReturnInterval40>"
       << "<ws_severityReturnInterval80>0</ws_severityReturnInterval80>"
       << "<ws_severityReturnInterval160>0</ws_severityReturnInterval160>"
       << "<ws_severityReturnInterval320>0</ws_severityReturnInterval320>"
       << "<ws_severityReturnInterval640>0</ws_severityReturnInterval640>"
       << "<ws_severityReturnInterval1280>0</ws_severityReturnInterval1280>"
       << "<ws_severityReturnInterval2560>0</ws_severityReturnInterval2560>"
       << "<ws_minDBH>"
       << "<ws_mdVal species=\"Species_1\">5</ws_mdVal>"
       << "<ws_mdVal species=\"Species_2\">6</ws_mdVal>"
       << "</ws_minDBH>"
       << "<ws_stmInterceptA>"
       << "<ws_siaVal species=\"Species_1\">-2.261</ws_siaVal>"
       << "<ws_siaVal species=\"Species_2\">-1.96</ws_siaVal>"
       << "</ws_stmInterceptA>"
       << "<ws_stmIntensCoeffC>"
       << "<ws_sicVal species=\"Species_1\">1.14</ws_sicVal>"
       << "<ws_sicVal species=\"Species_2\">0.19</ws_sicVal>"
       << "</ws_stmIntensCoeffC>"
       << "<ws_stmDBHExpB>"
       << "<ws_sdebVal species=\"Species_1\">0.426</ws_sdebVal>"
       << "<ws_sdebVal species=\"Species_2\">0.679</ws_sdebVal>"
       << "</ws_stmDBHExpB>"
       << "<ws_stmTSToStartStorms>0</ws_stmTSToStartStorms>"
       << "<ws_stmSSTPeriod>1</ws_stmSSTPeriod>"
       << "<ws_stmSineD>0</ws_stmSineD>"
       << "<ws_stmSineF>1</ws_stmSineF>"
       << "<ws_stmSineG>1</ws_stmSineG>"
       << "<ws_stmTrendSlopeM>0</ws_stmTrendSlopeM>"
       << "<ws_stmTrendInterceptI>1</ws_stmTrendInterceptI>"
       << "</Windstorm2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;

}

/////////////////////////////////////////////////////////////////////////////
// WriteWindstormXMLFile4()
/////////////////////////////////////////////////////////////////////////////
const char* WriteWindstormXMLFile4()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>2</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>";

  WriteWindstormCommonStuff(oOut);
  WriteWindstormNoSnagBehaviorList(oOut);

  oOut << "<Windstorm2>"
       << "<ws_severityReturnInterval1>0.4</ws_severityReturnInterval1>"
       << "<ws_severityReturnInterval5>0</ws_severityReturnInterval5>"
       << "<ws_severityReturnInterval10>0</ws_severityReturnInterval10>"
       << "<ws_severityReturnInterval20>0</ws_severityReturnInterval20>"
       << "<ws_severityReturnInterval40>0</ws_severityReturnInterval40>"
       << "<ws_severityReturnInterval80>0</ws_severityReturnInterval80>"
       << "<ws_severityReturnInterval160>0</ws_severityReturnInterval160>"
       << "<ws_severityReturnInterval320>0</ws_severityReturnInterval320>"
       << "<ws_severityReturnInterval640>0</ws_severityReturnInterval640>"
       << "<ws_severityReturnInterval1280>0</ws_severityReturnInterval1280>"
       << "<ws_severityReturnInterval2560>0</ws_severityReturnInterval2560>"
       << "<ws_minDBH>"
       << "<ws_mdVal species=\"Species_1\">5</ws_mdVal>"
       << "<ws_mdVal species=\"Species_2\">6</ws_mdVal>"
       << "</ws_minDBH>"
       << "<ws_stmInterceptA>"
       << "<ws_siaVal species=\"Species_1\">-2.261</ws_siaVal>"
       << "<ws_siaVal species=\"Species_2\">-1.96</ws_siaVal>"
       << "</ws_stmInterceptA>"
       << "<ws_stmIntensCoeffC>"
       << "<ws_sicVal species=\"Species_1\">1.14</ws_sicVal>"
       << "<ws_sicVal species=\"Species_2\">0.19</ws_sicVal>"
       << "</ws_stmIntensCoeffC>"
       << "<ws_stmDBHExpB>"
       << "<ws_sdebVal species=\"Species_1\">0.426</ws_sdebVal>"
       << "<ws_sdebVal species=\"Species_2\">0.679</ws_sdebVal>"
       << "</ws_stmDBHExpB>"
       << "<ws_stmTSToStartStorms>0</ws_stmTSToStartStorms>"
       << "<ws_stmSSTPeriod>1</ws_stmSSTPeriod>"
       << "<ws_stmSineD>0</ws_stmSineD>"
       << "<ws_stmSineF>1</ws_stmSineF>"
       << "<ws_stmSineG>1</ws_stmSineG>"
       << "<ws_stmTrendSlopeM>0</ws_stmTrendSlopeM>"
       << "<ws_stmTrendInterceptI>1</ws_stmTrendInterceptI>"
       << "</Windstorm2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;

}

/////////////////////////////////////////////////////////////////////////////
// WriteWindstormXMLFile5()
/////////////////////////////////////////////////////////////////////////////
const char* WriteWindstormXMLFile5()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>2</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>";

  WriteWindstormCommonStuff(oOut);
  WriteWindstormNoSnagBehaviorList(oOut);

  oOut << "<Windstorm2>"
       << "<ws_severityReturnInterval1>0</ws_severityReturnInterval1>"
       << "<ws_severityReturnInterval5>0</ws_severityReturnInterval5>"
       << "<ws_severityReturnInterval10>0</ws_severityReturnInterval10>"
       << "<ws_severityReturnInterval20>0</ws_severityReturnInterval20>"
       << "<ws_severityReturnInterval40>0</ws_severityReturnInterval40>"
       << "<ws_severityReturnInterval80>0</ws_severityReturnInterval80>"
       << "<ws_severityReturnInterval160>0</ws_severityReturnInterval160>"
       << "<ws_severityReturnInterval320>0</ws_severityReturnInterval320>"
       << "<ws_severityReturnInterval640>0</ws_severityReturnInterval640>"
       << "<ws_severityReturnInterval1280>0</ws_severityReturnInterval1280>"
       << "<ws_severityReturnInterval2560>0</ws_severityReturnInterval2560>"
       << "<ws_minDBH>"
       << "<ws_mdVal species=\"Species_1\">5</ws_mdVal>"
       << "<ws_mdVal species=\"Species_2\">6</ws_mdVal>"
       << "</ws_minDBH>"
       << "<ws_stmInterceptA>"
       << "<ws_siaVal species=\"Species_1\">-2.261</ws_siaVal>"
       << "<ws_siaVal species=\"Species_2\">-1.96</ws_siaVal>"
       << "</ws_stmInterceptA>"
       << "<ws_stmIntensCoeffC>"
       << "<ws_sicVal species=\"Species_1\">1.14</ws_sicVal>"
       << "<ws_sicVal species=\"Species_2\">0.19</ws_sicVal>"
       << "</ws_stmIntensCoeffC>"
       << "<ws_stmDBHExpB>"
       << "<ws_sdebVal species=\"Species_1\">0.426</ws_sdebVal>"
       << "<ws_sdebVal species=\"Species_2\">0.679</ws_sdebVal>"
       << "</ws_stmDBHExpB>"
       << "<ws_stmTSToStartStorms>0</ws_stmTSToStartStorms>"
       << "<ws_stmSSTPeriod>1</ws_stmSSTPeriod>"
       << "<ws_stmSineD>0</ws_stmSineD>"
       << "<ws_stmSineF>1</ws_stmSineF>"
       << "<ws_stmSineG>1</ws_stmSineG>"
       << "<ws_stmTrendSlopeM>0</ws_stmTrendSlopeM>"
       << "<ws_stmTrendInterceptI>1</ws_stmTrendInterceptI>"
       << "</Windstorm2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;

}

/////////////////////////////////////////////////////////////////////////////
// WriteWindstormXMLFile6()
/////////////////////////////////////////////////////////////////////////////
const char* WriteWindstormXMLFile6()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>3</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>";

  WriteWindstormCommonStuff(oOut);
  WriteWindstormNoSnagBehaviorList(oOut);

  oOut << "<Windstorm2>"
       << "<ws_severityReturnInterval1>0.5</ws_severityReturnInterval1>"
       << "<ws_severityReturnInterval5>0</ws_severityReturnInterval5>"
       << "<ws_severityReturnInterval10>0</ws_severityReturnInterval10>"
       << "<ws_severityReturnInterval20>0</ws_severityReturnInterval20>"
       << "<ws_severityReturnInterval40>0</ws_severityReturnInterval40>"
       << "<ws_severityReturnInterval80>0</ws_severityReturnInterval80>"
       << "<ws_severityReturnInterval160>0</ws_severityReturnInterval160>"
       << "<ws_severityReturnInterval320>0</ws_severityReturnInterval320>"
       << "<ws_severityReturnInterval640>0</ws_severityReturnInterval640>"
       << "<ws_severityReturnInterval1280>0</ws_severityReturnInterval1280>"
       << "<ws_severityReturnInterval2560>0</ws_severityReturnInterval2560>"
       << "<ws_minDBH>"
       << "<ws_mdVal species=\"Species_1\">5</ws_mdVal>"
       << "<ws_mdVal species=\"Species_2\">6</ws_mdVal>"
       << "</ws_minDBH>"
       << "<ws_stmInterceptA>"
       << "<ws_siaVal species=\"Species_1\">-2.261</ws_siaVal>"
       << "<ws_siaVal species=\"Species_2\">-1.96</ws_siaVal>"
       << "</ws_stmInterceptA>"
       << "<ws_stmIntensCoeffC>"
       << "<ws_sicVal species=\"Species_1\">1.14</ws_sicVal>"
       << "<ws_sicVal species=\"Species_2\">0.19</ws_sicVal>"
       << "</ws_stmIntensCoeffC>"
       << "<ws_stmDBHExpB>"
       << "<ws_sdebVal species=\"Species_1\">0.426</ws_sdebVal>"
       << "<ws_sdebVal species=\"Species_2\">0.679</ws_sdebVal>"
       << "</ws_stmDBHExpB>"
       << "<ws_stmTSToStartStorms>2</ws_stmTSToStartStorms>"
       << "<ws_stmSSTPeriod>1</ws_stmSSTPeriod>"
       << "<ws_stmSineD>0</ws_stmSineD>"
       << "<ws_stmSineF>1</ws_stmSineF>"
       << "<ws_stmSineG>1</ws_stmSineG>"
       << "<ws_stmTrendSlopeM>0</ws_stmTrendSlopeM>"
       << "<ws_stmTrendInterceptI>1</ws_stmTrendInterceptI>"
       << "</Windstorm2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;

}

/////////////////////////////////////////////////////////////////////////////
// WriteWindstormXMLFile7()
/////////////////////////////////////////////////////////////////////////////
const char* WriteWindstormXMLFile7()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>3</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>";

  WriteWindstormCommonStuff(oOut);
  WriteWindstormNoSnagBehaviorList(oOut);

  oOut << "<Windstorm2>"
       << "<ws_severityReturnInterval1>0.1</ws_severityReturnInterval1>"
       << "<ws_severityReturnInterval5>0</ws_severityReturnInterval5>"
       << "<ws_severityReturnInterval10>0</ws_severityReturnInterval10>"
       << "<ws_severityReturnInterval20>0</ws_severityReturnInterval20>"
       << "<ws_severityReturnInterval40>0</ws_severityReturnInterval40>"
       << "<ws_severityReturnInterval80>0</ws_severityReturnInterval80>"
       << "<ws_severityReturnInterval160>0</ws_severityReturnInterval160>"
       << "<ws_severityReturnInterval320>0</ws_severityReturnInterval320>"
       << "<ws_severityReturnInterval640>0</ws_severityReturnInterval640>"
       << "<ws_severityReturnInterval1280>0</ws_severityReturnInterval1280>"
       << "<ws_severityReturnInterval2560>0</ws_severityReturnInterval2560>"
       << "<ws_minDBH>"
       << "<ws_mdVal species=\"Species_1\">5</ws_mdVal>"
       << "<ws_mdVal species=\"Species_2\">6</ws_mdVal>"
       << "</ws_minDBH>"
       << "<ws_stmInterceptA>"
       << "<ws_siaVal species=\"Species_1\">-2.261</ws_siaVal>"
       << "<ws_siaVal species=\"Species_2\">-1.96</ws_siaVal>"
       << "</ws_stmInterceptA>"
       << "<ws_stmIntensCoeffC>"
       << "<ws_sicVal species=\"Species_1\">1.14</ws_sicVal>"
       << "<ws_sicVal species=\"Species_2\">0.19</ws_sicVal>"
       << "</ws_stmIntensCoeffC>"
       << "<ws_stmDBHExpB>"
       << "<ws_sdebVal species=\"Species_1\">0.426</ws_sdebVal>"
       << "<ws_sdebVal species=\"Species_2\">0.679</ws_sdebVal>"
       << "</ws_stmDBHExpB>"
       << "<ws_stmTSToStartStorms>0</ws_stmTSToStartStorms>"
       << "<ws_stmSSTPeriod>1</ws_stmSSTPeriod>"
       << "<ws_stmSineD>0</ws_stmSineD>"
       << "<ws_stmSineF>1</ws_stmSineF>"
       << "<ws_stmSineG>1</ws_stmSineG>"
       << "<ws_stmTrendSlopeM>0</ws_stmTrendSlopeM>"
       << "<ws_stmTrendInterceptI>1</ws_stmTrendInterceptI>"
       << "</Windstorm2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;

}

/////////////////////////////////////////////////////////////////////////////
// WriteWindstormXMLFile8()
/////////////////////////////////////////////////////////////////////////////
const char* WriteWindstormXMLFile8()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>2</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>";

  WriteWindstormCommonStuff(oOut);
  WriteWindstormNoSnagBehaviorList(oOut);

  oOut << "<Windstorm2>"
       << "<ws_severityReturnInterval1>0.07</ws_severityReturnInterval1>"
       << "<ws_severityReturnInterval5>0</ws_severityReturnInterval5>"
       << "<ws_severityReturnInterval10>0</ws_severityReturnInterval10>"
       << "<ws_severityReturnInterval20>0</ws_severityReturnInterval20>"
       << "<ws_severityReturnInterval40>0</ws_severityReturnInterval40>"
       << "<ws_severityReturnInterval80>0</ws_severityReturnInterval80>"
       << "<ws_severityReturnInterval160>0</ws_severityReturnInterval160>"
       << "<ws_severityReturnInterval320>0</ws_severityReturnInterval320>"
       << "<ws_severityReturnInterval640>0</ws_severityReturnInterval640>"
       << "<ws_severityReturnInterval1280>0</ws_severityReturnInterval1280>"
       << "<ws_severityReturnInterval2560>0</ws_severityReturnInterval2560>"
       << "<ws_minDBH>"
       << "<ws_mdVal species=\"Species_1\">5</ws_mdVal>"
       << "<ws_mdVal species=\"Species_2\">6</ws_mdVal>"
       << "</ws_minDBH>"
       << "<ws_stmInterceptA>"
       << "<ws_siaVal species=\"Species_1\">-2.261</ws_siaVal>"
       << "<ws_siaVal species=\"Species_2\">-1.96</ws_siaVal>"
       << "</ws_stmInterceptA>"
       << "<ws_stmIntensCoeffC>"
       << "<ws_sicVal species=\"Species_1\">1.14</ws_sicVal>"
       << "<ws_sicVal species=\"Species_2\">0.19</ws_sicVal>"
       << "</ws_stmIntensCoeffC>"
       << "<ws_stmDBHExpB>"
       << "<ws_sdebVal species=\"Species_1\">0.426</ws_sdebVal>"
       << "<ws_sdebVal species=\"Species_2\">0.679</ws_sdebVal>"
       << "</ws_stmDBHExpB>"
       << "<ws_stmTSToStartStorms>0</ws_stmTSToStartStorms>"
       << "<ws_stmSSTPeriod>1</ws_stmSSTPeriod>"
       << "<ws_stmSineD>0</ws_stmSineD>"
       << "<ws_stmSineF>1</ws_stmSineF>"
       << "<ws_stmSineG>1</ws_stmSineG>"
       << "<ws_stmTrendSlopeM>0</ws_stmTrendSlopeM>"
       << "<ws_stmTrendInterceptI>1</ws_stmTrendInterceptI>"
       << "</Windstorm2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;

}

/////////////////////////////////////////////////////////////////////////////
// WriteWindstormXMLErrorFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteWindstormXMLErrorFile1()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>2</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>";

  WriteWindstormCommonStuff(oOut);
  WriteWindstormNoSnagBehaviorList(oOut);

  oOut << "<Windstorm2>"
       << "<ws_severityReturnInterval1>0.2</ws_severityReturnInterval1>"
       << "<ws_severityReturnInterval5>0</ws_severityReturnInterval5>"
       << "<ws_severityReturnInterval10>0</ws_severityReturnInterval10>"
       << "<ws_severityReturnInterval20>0</ws_severityReturnInterval20>"
       << "<ws_severityReturnInterval40>0</ws_severityReturnInterval40>"
       << "<ws_severityReturnInterval80>0</ws_severityReturnInterval80>"
       << "<ws_severityReturnInterval160>0</ws_severityReturnInterval160>"
       << "<ws_severityReturnInterval320>0</ws_severityReturnInterval320>"
       << "<ws_severityReturnInterval640>0</ws_severityReturnInterval640>"
       << "<ws_severityReturnInterval1280>0</ws_severityReturnInterval1280>"
       << "<ws_severityReturnInterval2560>0</ws_severityReturnInterval2560>"
       << "<ws_minDBH>"
       << "<ws_mdVal species=\"Species_1\">-5</ws_mdVal>"
       << "<ws_mdVal species=\"Species_2\">6</ws_mdVal>"
       << "</ws_minDBH>"
       << "<ws_stmInterceptA>"
       << "<ws_siaVal species=\"Species_1\">-2.261</ws_siaVal>"
       << "<ws_siaVal species=\"Species_2\">-1.96</ws_siaVal>"
       << "</ws_stmInterceptA>"
       << "<ws_stmIntensCoeffC>"
       << "<ws_sicVal species=\"Species_1\">1.14</ws_sicVal>"
       << "<ws_sicVal species=\"Species_2\">0.19</ws_sicVal>"
       << "</ws_stmIntensCoeffC>"
       << "<ws_stmDBHExpB>"
       << "<ws_sdebVal species=\"Species_1\">0.426</ws_sdebVal>"
       << "<ws_sdebVal species=\"Species_2\">0.679</ws_sdebVal>"
       << "</ws_stmDBHExpB>"
       << "<ws_stmTSToStartStorms>0</ws_stmTSToStartStorms>"
       << "<ws_stmSSTPeriod>1</ws_stmSSTPeriod>"
       << "<ws_stmSineD>0</ws_stmSineD>"
       << "<ws_stmSineF>1</ws_stmSineF>"
       << "<ws_stmSineG>1</ws_stmSineG>"
       << "<ws_stmTrendSlopeM>0</ws_stmTrendSlopeM>"
       << "<ws_stmTrendInterceptI>0</ws_stmTrendInterceptI>"
       << "</Windstorm2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteWindstormXMLErrorFile2()
/////////////////////////////////////////////////////////////////////////////
const char* WriteWindstormXMLErrorFile2()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>2</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>";

  WriteWindstormCommonStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>ConstantGLI</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>Windstorm</behaviorName>"
       << "<version>2</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>";

  oOut << "<Windstorm2>"
       << "<ws_severityReturnInterval1>0.2</ws_severityReturnInterval1>"
       << "<ws_severityReturnInterval5>0</ws_severityReturnInterval5>"
       << "<ws_severityReturnInterval10>0</ws_severityReturnInterval10>"
       << "<ws_severityReturnInterval20>0</ws_severityReturnInterval20>"
       << "<ws_severityReturnInterval40>0</ws_severityReturnInterval40>"
       << "<ws_severityReturnInterval80>0</ws_severityReturnInterval80>"
       << "<ws_severityReturnInterval160>0</ws_severityReturnInterval160>"
       << "<ws_severityReturnInterval320>0</ws_severityReturnInterval320>"
       << "<ws_severityReturnInterval640>0</ws_severityReturnInterval640>"
       << "<ws_severityReturnInterval1280>0</ws_severityReturnInterval1280>"
       << "<ws_severityReturnInterval2560>0</ws_severityReturnInterval2560>"
       << "<ws_minDBH>"
       << "<ws_mdVal species=\"Species_1\">5</ws_mdVal>"
       << "<ws_mdVal species=\"Species_2\">6</ws_mdVal>"
       << "</ws_minDBH>"
       << "<ws_stmInterceptA>"
       << "<ws_siaVal species=\"Species_1\">-2.261</ws_siaVal>"
       << "<ws_siaVal species=\"Species_2\">-1.96</ws_siaVal>"
       << "</ws_stmInterceptA>"
       << "<ws_stmIntensCoeffC>"
       << "<ws_sicVal species=\"Species_1\">1.14</ws_sicVal>"
       << "<ws_sicVal species=\"Species_2\">0.19</ws_sicVal>"
       << "</ws_stmIntensCoeffC>"
       << "<ws_stmDBHExpB>"
       << "<ws_sdebVal species=\"Species_1\">0.426</ws_sdebVal>"
       << "<ws_sdebVal species=\"Species_2\">0.679</ws_sdebVal>"
       << "</ws_stmDBHExpB>"
       << "<ws_stmTSToStartStorms>0</ws_stmTSToStartStorms>"
       << "<ws_stmSSTPeriod>1</ws_stmSSTPeriod>"
       << "<ws_stmSineD>0</ws_stmSineD>"
       << "<ws_stmSineF>1</ws_stmSineF>"
       << "<ws_stmSineG>1</ws_stmSineG>"
       << "<ws_stmTrendSlopeM>0</ws_stmTrendSlopeM>"
       << "<ws_stmTrendInterceptI>0</ws_stmTrendInterceptI>"
       << "</Windstorm2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteWindstormXMLErrorFile3()
/////////////////////////////////////////////////////////////////////////////
const char* WriteWindstormXMLErrorFile3()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>2</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>";

  WriteWindstormCommonStuff(oOut);
  WriteWindstormNoSnagBehaviorList(oOut);

  oOut << "<Windstorm2>"
       << "<ws_severityReturnInterval1>0.2</ws_severityReturnInterval1>"
       << "<ws_severityReturnInterval5>0</ws_severityReturnInterval5>"
       << "<ws_severityReturnInterval10>0</ws_severityReturnInterval10>"
       << "<ws_severityReturnInterval20>0</ws_severityReturnInterval20>"
       << "<ws_severityReturnInterval40>0</ws_severityReturnInterval40>"
       << "<ws_severityReturnInterval80>0</ws_severityReturnInterval80>"
       << "<ws_severityReturnInterval160>0</ws_severityReturnInterval160>"
       << "<ws_severityReturnInterval320>0</ws_severityReturnInterval320>"
       << "<ws_severityReturnInterval640>0</ws_severityReturnInterval640>"
       << "<ws_severityReturnInterval1280>0</ws_severityReturnInterval1280>"
       << "<ws_severityReturnInterval2560>0</ws_severityReturnInterval2560>"
       << "<ws_minDBH>"
       << "<ws_mdVal species=\"Species_1\">5</ws_mdVal>"
       << "<ws_mdVal species=\"Species_2\">6</ws_mdVal>"
       << "</ws_minDBH>"
       << "<ws_stmInterceptA>"
       << "<ws_siaVal species=\"Species_1\">-2.261</ws_siaVal>"
       << "<ws_siaVal species=\"Species_2\">-1.96</ws_siaVal>"
       << "</ws_stmInterceptA>"
       << "<ws_stmIntensCoeffC>"
       << "<ws_sicVal species=\"Species_1\">1.14</ws_sicVal>"
       << "<ws_sicVal species=\"Species_2\">0.19</ws_sicVal>"
       << "</ws_stmIntensCoeffC>"
       << "<ws_stmDBHExpB>"
       << "<ws_sdebVal species=\"Species_1\">0.426</ws_sdebVal>"
       << "<ws_sdebVal species=\"Species_2\">0.679</ws_sdebVal>"
       << "</ws_stmDBHExpB>"
       << "<ws_stmTSToStartStorms>-5</ws_stmTSToStartStorms>"
       << "<ws_stmSSTPeriod>1</ws_stmSSTPeriod>"
       << "<ws_stmSineD>0</ws_stmSineD>"
       << "<ws_stmSineF>1</ws_stmSineF>"
       << "<ws_stmSineG>1</ws_stmSineG>"
       << "<ws_stmTrendSlopeM>0</ws_stmTrendSlopeM>"
       << "<ws_stmTrendInterceptI>0</ws_stmTrendInterceptI>"
       << "</Windstorm2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteWindstormXMLErrorFile4()
/////////////////////////////////////////////////////////////////////////////
const char* WriteWindstormXMLErrorFile4()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>2</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>";

  WriteWindstormCommonStuff(oOut);
  WriteWindstormNoSnagBehaviorList(oOut);

  oOut << "<Windstorm2>"
       << "<ws_severityReturnInterval1>0.2</ws_severityReturnInterval1>"
       << "<ws_severityReturnInterval5>0</ws_severityReturnInterval5>"
       << "<ws_severityReturnInterval10>0</ws_severityReturnInterval10>"
       << "<ws_severityReturnInterval20>0</ws_severityReturnInterval20>"
       << "<ws_severityReturnInterval40>0</ws_severityReturnInterval40>"
       << "<ws_severityReturnInterval80>0</ws_severityReturnInterval80>"
       << "<ws_severityReturnInterval160>1.5</ws_severityReturnInterval160>"
       << "<ws_severityReturnInterval320>0</ws_severityReturnInterval320>"
       << "<ws_severityReturnInterval640>0</ws_severityReturnInterval640>"
       << "<ws_severityReturnInterval1280>0</ws_severityReturnInterval1280>"
       << "<ws_severityReturnInterval2560>0</ws_severityReturnInterval2560>"
       << "<ws_minDBH>"
       << "<ws_mdVal species=\"Species_1\">5</ws_mdVal>"
       << "<ws_mdVal species=\"Species_2\">6</ws_mdVal>"
       << "</ws_minDBH>"
       << "<ws_stmInterceptA>"
       << "<ws_siaVal species=\"Species_1\">-2.261</ws_siaVal>"
       << "<ws_siaVal species=\"Species_2\">-1.96</ws_siaVal>"
       << "</ws_stmInterceptA>"
       << "<ws_stmIntensCoeffC>"
       << "<ws_sicVal species=\"Species_1\">1.14</ws_sicVal>"
       << "<ws_sicVal species=\"Species_2\">0.19</ws_sicVal>"
       << "</ws_stmIntensCoeffC>"
       << "<ws_stmDBHExpB>"
       << "<ws_sdebVal species=\"Species_1\">0.426</ws_sdebVal>"
       << "<ws_sdebVal species=\"Species_2\">0.679</ws_sdebVal>"
       << "</ws_stmDBHExpB>"
       << "<ws_stmTSToStartStorms>0</ws_stmTSToStartStorms>"
       << "<ws_stmSSTPeriod>1</ws_stmSSTPeriod>"
       << "<ws_stmSineD>0</ws_stmSineD>"
       << "<ws_stmSineF>1</ws_stmSineF>"
       << "<ws_stmSineG>1</ws_stmSineG>"
       << "<ws_stmTrendSlopeM>0</ws_stmTrendSlopeM>"
       << "<ws_stmTrendInterceptI>0</ws_stmTrendInterceptI>"
       << "</Windstorm2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteWindstormXMLErrorFile5()
/////////////////////////////////////////////////////////////////////////////
const char* WriteWindstormXMLErrorFile5()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>2</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>";

  WriteWindstormCommonStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>ConstantGLI</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>Windstorm</behaviorName>"
       << "<version>2</version>"
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
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<StochasticMortality3>"
       << "<mo_stochasticMortRate>"
       << "<mo_smrVal species=\"Species_1\">0.0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_2\">0.0</mo_smrVal>"
       << "</mo_stochasticMortRate>"
       << "</StochasticMortality3>";

  oOut << "<Windstorm2>"
       << "<ws_severityReturnInterval1>0.2</ws_severityReturnInterval1>"
       << "<ws_severityReturnInterval5>0</ws_severityReturnInterval5>"
       << "<ws_severityReturnInterval10>0</ws_severityReturnInterval10>"
       << "<ws_severityReturnInterval20>0</ws_severityReturnInterval20>"
       << "<ws_severityReturnInterval40>0</ws_severityReturnInterval40>"
       << "<ws_severityReturnInterval80>0</ws_severityReturnInterval80>"
       << "<ws_severityReturnInterval160>0</ws_severityReturnInterval160>"
       << "<ws_severityReturnInterval320>0</ws_severityReturnInterval320>"
       << "<ws_severityReturnInterval640>0</ws_severityReturnInterval640>"
       << "<ws_severityReturnInterval1280>0</ws_severityReturnInterval1280>"
       << "<ws_severityReturnInterval2560>0</ws_severityReturnInterval2560>"
       << "<ws_minDBH>"
       << "<ws_mdVal species=\"Species_1\">5</ws_mdVal>"
       << "<ws_mdVal species=\"Species_2\">6</ws_mdVal>"
       << "</ws_minDBH>"
       << "<ws_stmInterceptA>"
       << "<ws_siaVal species=\"Species_1\">-2.261</ws_siaVal>"
       << "<ws_siaVal species=\"Species_2\">-1.96</ws_siaVal>"
       << "</ws_stmInterceptA>"
       << "<ws_stmIntensCoeffC>"
       << "<ws_sicVal species=\"Species_1\">1.14</ws_sicVal>"
       << "<ws_sicVal species=\"Species_2\">0.19</ws_sicVal>"
       << "</ws_stmIntensCoeffC>"
       << "<ws_stmDBHExpB>"
       << "<ws_sdebVal species=\"Species_1\">0.426</ws_sdebVal>"
       << "<ws_sdebVal species=\"Species_2\">0.679</ws_sdebVal>"
       << "</ws_stmDBHExpB>"
       << "<ws_stmTSToStartStorms>0</ws_stmTSToStartStorms>"
       << "<ws_stmSSTPeriod>1</ws_stmSSTPeriod>"
       << "<ws_stmSineD>0</ws_stmSineD>"
       << "<ws_stmSineF>1</ws_stmSineF>"
       << "<ws_stmSineG>1</ws_stmSineG>"
       << "<ws_stmTrendSlopeM>0</ws_stmTrendSlopeM>"
       << "<ws_stmTrendInterceptI>0</ws_stmTrendInterceptI>"
       << "</Windstorm2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteWindstormXMLErrorFile6()
/////////////////////////////////////////////////////////////////////////////
const char* WriteWindstormXMLErrorFile6()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>2</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>";

  WriteWindstormCommonStuff(oOut);
  WriteWindstormSnagBehaviorList(oOut);

  oOut << "<Windstorm2>"
       << "<ws_severityReturnInterval1>0.2</ws_severityReturnInterval1>"
       << "<ws_severityReturnInterval5>0</ws_severityReturnInterval5>"
       << "<ws_severityReturnInterval10>0</ws_severityReturnInterval10>"
       << "<ws_severityReturnInterval20>0</ws_severityReturnInterval20>"
       << "<ws_severityReturnInterval40>0</ws_severityReturnInterval40>"
       << "<ws_severityReturnInterval80>0</ws_severityReturnInterval80>"
       << "<ws_severityReturnInterval160>0</ws_severityReturnInterval160>"
       << "<ws_severityReturnInterval320>0</ws_severityReturnInterval320>"
       << "<ws_severityReturnInterval640>0</ws_severityReturnInterval640>"
       << "<ws_severityReturnInterval1280>0</ws_severityReturnInterval1280>"
       << "<ws_severityReturnInterval2560>0</ws_severityReturnInterval2560>"
       << "<ws_minDBH>"
       << "<ws_mdVal species=\"Species_1\">5</ws_mdVal>"
       << "<ws_mdVal species=\"Species_2\">6</ws_mdVal>"
       << "</ws_minDBH>"
       << "<ws_stmInterceptA>"
       << "<ws_siaVal species=\"Species_1\">-2.261</ws_siaVal>"
       << "<ws_siaVal species=\"Species_2\">-1.96</ws_siaVal>"
       << "</ws_stmInterceptA>"
       << "<ws_stmIntensCoeffC>"
       << "<ws_sicVal species=\"Species_1\">1.14</ws_sicVal>"
       << "<ws_sicVal species=\"Species_2\">0.19</ws_sicVal>"
       << "</ws_stmIntensCoeffC>"
       << "<ws_stmDBHExpB>"
       << "<ws_sdebVal species=\"Species_1\">0.426</ws_sdebVal>"
       << "<ws_sdebVal species=\"Species_2\">0.679</ws_sdebVal>"
       << "</ws_stmDBHExpB>"
       << "<ws_stmTSToStartStorms>0</ws_stmTSToStartStorms>"
       << "<ws_stmSSTPeriod>0</ws_stmSSTPeriod>"
       << "<ws_stmSineD>0</ws_stmSineD>"
       << "<ws_stmSineF>1</ws_stmSineF>"
       << "<ws_stmSineG>1</ws_stmSineG>"
       << "<ws_stmTrendSlopeM>0</ws_stmTrendSlopeM>"
       << "<ws_stmTrendInterceptI>0</ws_stmTrendInterceptI>"
       << "</Windstorm2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;

}

/////////////////////////////////////////////////////////////////////////////
// WriteWindstormCommonStuff()
/////////////////////////////////////////////////////////////////////////////
void WriteWindstormCommonStuff(std::fstream &oOut)
{
  using namespace std;
  oOut << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>150</plot_lenX>"
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
       << "<tr_madVal species=\"Species_1\">5</tr_madVal>"
       << "<tr_madVal species=\"Species_2\">5</tr_madVal>"
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
       << "</allometry>"
       << "<ConstantGLI1>"
       << "<li_constGLI>100</li_constGLI>"
       << "</ConstantGLI1>";
}


/////////////////////////////////////////////////////////////////////////////
// WriteWindstormSnagBehaviorList()
/////////////////////////////////////////////////////////////////////////////
void WriteWindstormSnagBehaviorList(std::fstream &oOut)
{
  using namespace std;
  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>ConstantGLI</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Snag\"/>"
       << "<applyTo species=\"Species_2\" type=\"Snag\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>Windstorm</behaviorName>"
       << "<version>2</version>"
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
}

/////////////////////////////////////////////////////////////////////////////
// WriteWindstormNoSnagBehaviorList()
/////////////////////////////////////////////////////////////////////////////
void WriteWindstormNoSnagBehaviorList(std::fstream &oOut) {
  using namespace std;
  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>ConstantGLI</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>Windstorm</behaviorName>"
       << "<version>2</version>"
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
}
