//---------------------------------------------------------------------------
// TestTreePopulation2.cpp
//---------------------------------------------------------------------------
#include "TestTreePopulation2.h"
#include <gtest/gtest.h>
#include "SimManager.h"
#include "TreePopulation.h"
#include "PlatformFuncs.h"

#include <math.h>

/////////////////////////////////////////////////////////////////////////////
// TreeMapBugFixTesting()
// This checks hash table organization bugs I've run into to make sure
// they're fixed. WriteTreePopulation2XMLFile9() does setup with a particular
// tree map.
/////////////////////////////////////////////////////////////////////////////
TEST(TreePopulation, TreeMapBugFixTesting) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTreeSearch * p_oAllTrees;
    clTree * p_oTree;
    int iTreeTotal = 0;

    //Read in the parameter file
    p_oSimManager->ReadFile( WriteTreePopulation2XMLFile9() );
    p_oPop = ( clTreePopulation * )  p_oSimManager->GetPopulationObject( "treepopulation" );

    //Count all trees - there should be 11
    p_oAllTrees = p_oPop->Find( "all" );
    p_oTree = p_oAllTrees->NextTree();
    while ( p_oTree )
    {
      iTreeTotal++;
      p_oTree = p_oAllTrees->NextTree();
    }

    //Verify that we found all the trees - this checks fix of bug 1 created in
    //cell 0, 14
    EXPECT_EQ( iTreeTotal, 11 );

    //Check cell 1, 14, height div 3 - this checks fix of bug 2
    iTreeTotal = -1;
    p_oTree = p_oPop->GetTallestInCellHeightDiv(1, 14, 2);
    while (p_oTree) {
      iTreeTotal++;
      p_oTree = p_oTree->GetTaller();
    }
    EXPECT_EQ( iTreeTotal, 6 );
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}


/////////////////////////////////////////////////////////////////////////////
// TestTreeMapReading()
// Makes sure that tree maps are read correctly. This includes trees of every
// tree type, with each type defined by either diameter or height.
// WriteTreePopulation2XMLFile1() writes the tree map parameter file.
/////////////////////////////////////////////////////////////////////////////
TEST(TreePopulation, TestTreeMapReading) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTreeSearch * p_oAllTrees;
    clTree * p_oTree;
    float fX, fDbh, fHeight, fDiam10, fExpected;
    int iTreeTotal = 0;

    //Read in the parameter file
    p_oSimManager->ReadFile( WriteTreePopulation2XMLFile1() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Find all trees
    p_oAllTrees = p_oPop->Find( "all" );
    p_oTree = p_oAllTrees->NextTree();
    while ( p_oTree )
    {

      //Get the X - that's the tree's number
      p_oTree->GetValue( p_oPop->GetXCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fX );

      if ( fabs( 1 - fX ) < 0.01 )
      {
        //Seedling - get the diam10 and height and compare
        p_oTree->GetValue( p_oPop->GetDiam10Code( p_oTree->GetSpecies(), p_oTree->GetType() ), & fDiam10 );
        p_oTree->GetValue( p_oPop->GetHeightCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fHeight );

        fExpected = 0.2;
        EXPECT_LT( fabs( fExpected - fDiam10 ), 0.01 );

        fExpected = 0.304380631;
        EXPECT_LT( fabs( fExpected - fHeight ), 0.01 );
      }
      else if ( fabs( 2 - fX ) < 0.01 )
      {
        //Seedling - get the diam10 and height and compare
        p_oTree->GetValue( p_oPop->GetDiam10Code( p_oTree->GetSpecies(), p_oTree->GetType() ), & fDiam10 );
        p_oTree->GetValue( p_oPop->GetHeightCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fHeight );

        fExpected = 0.901196874;
        EXPECT_LT( fabs( fExpected - fDiam10 ), 0.01 );

        fExpected = 1.01;
        EXPECT_LT( fabs( fExpected - fHeight ), 0.01 );

      }
      else if ( fabs( 3 - fX ) < 0.01 )
      {

        //Sapling - get the diam10, DBH, and height and compare
        p_oTree->GetValue( p_oPop->GetDiam10Code( p_oTree->GetSpecies(), p_oTree->GetType() ), & fDiam10 );
        p_oTree->GetValue( p_oPop->GetHeightCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fHeight );
        p_oTree->GetValue( p_oPop->GetDbhCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fDbh );

        fExpected = 6.5;
        EXPECT_LT( fabs( fExpected - fDiam10 ), 0.01 );

        fExpected = 5.2052;
        EXPECT_LT( fabs( fExpected - fDbh ), 0.01 );

        fExpected = 6.84563436;
        EXPECT_LT( fabs( fExpected - fHeight ), 0.01 );

      }
      else if ( fabs( 4 - fX ) < 0.01 )
      {
        //Sapling - get the diam10, DBH, and height and compare
        p_oTree->GetValue( p_oPop->GetDiam10Code( p_oTree->GetSpecies(), p_oTree->GetType() ), & fDiam10 );
        p_oTree->GetValue( p_oPop->GetHeightCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fHeight );
        p_oTree->GetValue( p_oPop->GetDbhCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fDbh );

        fExpected = 9.99000999;
        EXPECT_LT( fabs( fExpected - fDiam10 ), 0.01 );

        fExpected = 8;
        EXPECT_LT( fabs( fExpected - fDbh ), 0.01 );

        fExpected = 9.461874761;
        EXPECT_LT( fabs( fExpected - fHeight ), 0.01 );

      }
      else if ( fabs( 5 - fX ) < 0.01 )
      {
        //Sapling - get the diam10, DBH, and height and compare
        p_oTree->GetValue( p_oPop->GetDiam10Code( p_oTree->GetSpecies(), p_oTree->GetType() ), & fDiam10 );
        p_oTree->GetValue( p_oPop->GetHeightCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fHeight );
        p_oTree->GetValue( p_oPop->GetDbhCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fDbh );

        fExpected = 2.077134764;
        EXPECT_LT( fabs( fExpected - fDiam10 ), 0.01 );

        fExpected = 1.663369519;
        EXPECT_LT( fabs( fExpected - fDbh ), 0.01 );

        fExpected = 3.2;
        EXPECT_LT( fabs( fExpected - fHeight ), 0.01 );

      }
      else if ( fabs( 6 - fX ) < 0.01 )
      {
        //Adult - get the DBH and height and compare
        p_oTree->GetValue( p_oPop->GetHeightCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fHeight );
        p_oTree->GetValue( p_oPop->GetDbhCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fDbh );

        fExpected = 15;
        EXPECT_LT( fabs( fExpected - fDbh ), 0.01 );

        fExpected = 15.13074207;
        EXPECT_LT( fabs( fExpected - fHeight ), 0.01 );

      }
      else if ( fabs( 7 - fX ) < 0.01 )
      {
        //Adult - get the DBH and height and compare
        p_oTree->GetValue( p_oPop->GetHeightCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fHeight );
        p_oTree->GetValue( p_oPop->GetDbhCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fDbh );

        fExpected = 23.15587652;
        EXPECT_LT( fabs( fExpected - fDbh ), 0.01 );

        fExpected = 20.4;
        EXPECT_LT( fabs( fExpected - fHeight ), 0.01 );

      }
      else if ( fabs( 8 - fX ) < 0.01 )
      {
        //Snag - get the DBH and height and compare
        p_oTree->GetValue( p_oPop->GetHeightCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fHeight );
        p_oTree->GetValue( p_oPop->GetDbhCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fDbh );

        fExpected = 43;
        EXPECT_LT( fabs( fExpected - fDbh ), 0.01 );

        fExpected = 28.93869474;
        EXPECT_LT( fabs( fExpected - fHeight ), 0.01 );

      }
      else if ( fabs( 9 - fX ) < 0.01 )
      {
        //Snag - get the DBH and height and compare
        p_oTree->GetValue( p_oPop->GetHeightCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fHeight );
        p_oTree->GetValue( p_oPop->GetDbhCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fDbh );

        fExpected = 15.41359121;
        EXPECT_LT( fabs( fExpected - fDbh ), 0.01 );

        fExpected = 15.43;
        EXPECT_LT( fabs( fExpected - fHeight ), 0.01 );

      }
      else if ( fabs( 10 - fX ) < 0.01 )
      {
        //Seedling - get the diam10 and height and compare
        p_oTree->GetValue( p_oPop->GetDiam10Code( p_oTree->GetSpecies(), p_oTree->GetType() ), & fDiam10 );
        p_oTree->GetValue( p_oPop->GetHeightCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fHeight );

        fExpected = 0.8;
        EXPECT_LT( fabs( fExpected - fDiam10 ), 0.01 );

        fExpected = 0.909206115;
        EXPECT_LT( fabs( fExpected - fHeight ), 0.01 );

      }
      else if ( fabs( 11 - fX ) < 0.01 )
      {
        //Seedling - get the diam10 and height and compare
        p_oTree->GetValue( p_oPop->GetDiam10Code( p_oTree->GetSpecies(), p_oTree->GetType() ), & fDiam10 );
        p_oTree->GetValue( p_oPop->GetHeightCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fHeight );

        fExpected = 0.65;
        EXPECT_LT( fabs( fExpected - fDiam10 ), 0.01 );

        fExpected = 1.05;
        EXPECT_LT( fabs( fExpected - fHeight ), 0.01 );

      }
      else if ( fabs( 12 - fX ) < 0.01 )
      {
        //Sapling - get the diam10, DBH, and height and compare
        p_oTree->GetValue( p_oPop->GetDiam10Code( p_oTree->GetSpecies(), p_oTree->GetType() ), & fDiam10 );
        p_oTree->GetValue( p_oPop->GetHeightCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fHeight );
        p_oTree->GetValue( p_oPop->GetDbhCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fDbh );

        fExpected = 5.36963037;
        EXPECT_LT( fabs( fExpected - fDiam10 ), 0.01 );

        fExpected = 4.3;
        EXPECT_LT( fabs( fExpected - fDbh ), 0.01 );

        fExpected = 5.950308026;
        EXPECT_LT( fabs( fExpected - fHeight ), 0.01 );
      }
      else if ( fabs( 13 - fX ) < 0.01 )
      {
        //Sapling - get the diam10, DBH, and height and compare
        p_oTree->GetValue( p_oPop->GetDiam10Code( p_oTree->GetSpecies(), p_oTree->GetType() ), & fDiam10 );
        p_oTree->GetValue( p_oPop->GetHeightCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fHeight );
        p_oTree->GetValue( p_oPop->GetDbhCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fDbh );

        fExpected = 5.6;
        EXPECT_TRUE( fabs( fExpected - fDiam10 ) < 0.01 || fabs( fExpected - fDbh ) < 0.01 );

        fExpected = 5.6;
        EXPECT_LT( fabs( fExpected - fHeight ), 0.01 );
      }
      else if ( fabs( 14 - fX ) < 0.01 )
      {
        //Adult - get the DBH and height and compare
        p_oTree->GetValue( p_oPop->GetHeightCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fHeight );
        p_oTree->GetValue( p_oPop->GetDbhCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fDbh );

        fExpected = 18.7;
        EXPECT_LT( fabs( fExpected - fDbh ), 0.01 );

        fExpected = 17.68084137;
        EXPECT_LT( fabs( fExpected - fHeight ), 0.01 );
      }
      else if ( fabs( 15 - fX ) < 0.01 )
      {
        //Adult - get the DBH and height and compare
        p_oTree->GetValue( p_oPop->GetHeightCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fHeight );
        p_oTree->GetValue( p_oPop->GetDbhCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fDbh );

        fExpected = 21.2;
        EXPECT_LT( fabs( fExpected - fDbh ), 0.01 );

        fExpected = 18.7;
        EXPECT_LT( fabs( fExpected - fHeight ), 0.01 );
      }
      else if ( fabs( 16 - fX ) < 0.01 )
      {
        //Snag - get the DBH and height and compare
        p_oTree->GetValue( p_oPop->GetHeightCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fHeight );
        p_oTree->GetValue( p_oPop->GetDbhCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fDbh );

        fExpected = 45.9;
        EXPECT_LT( fabs( fExpected - fDbh ), 0.01 );

        fExpected = 29.81422424;
        EXPECT_LT( fabs( fExpected - fHeight ), 0.01 );
      }
      else if ( fabs( 17 - fX ) < 0.01 )
      {
        //Snag - get the DBH and height and compare
        p_oTree->GetValue( p_oPop->GetHeightCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fHeight );
        p_oTree->GetValue( p_oPop->GetDbhCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fDbh );

        fExpected = 32.5;
        EXPECT_LT( fabs( fExpected - fDbh ), 0.01 );

        fExpected = 15.8;
        EXPECT_LT( fabs( fExpected - fHeight ), 0.01 );
      }
      else
      {
        FAIL() << "Found unexpected tree.";
      }


      iTreeTotal++;
      p_oTree = p_oAllTrees->NextTree();
    }

    //Verify that we found all the trees
    EXPECT_EQ( iTreeTotal, 17 );
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestTextTreeMapReading1()
// This is a clone of TestTreeMapReading except it uses a text tree map.
/////////////////////////////////////////////////////////////////////////////
TEST(TreePopulation, TestTextTreeMapReading1) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTreeSearch * p_oAllTrees;
    clTree * p_oTree;
    float fX, fDbh, fHeight, fDiam10, fExpected;
    int iTreeTotal = 0;

    //Read in the parameter file
    p_oSimManager->ReadFile( WriteTreePopulation2XMLFile10() );
    DeleteThisFile("TestTreeFile1.txt");
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Find all trees
    p_oAllTrees = p_oPop->Find( "all" );
    p_oTree = p_oAllTrees->NextTree();
    while ( p_oTree )
    {

      //Get the X - that's the tree's number
      p_oTree->GetValue( p_oPop->GetXCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fX );

      if ( fabs( 1 - fX ) < 0.01 )
      {
        //Seedling - get the diam10 and height and compare
        p_oTree->GetValue( p_oPop->GetDiam10Code( p_oTree->GetSpecies(), p_oTree->GetType() ), & fDiam10 );
        p_oTree->GetValue( p_oPop->GetHeightCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fHeight );

        fExpected = 0.2;
        EXPECT_LT( fabs( fExpected - fDiam10 ), 0.01 );

        fExpected = 0.304380631;
        EXPECT_LT( fabs( fExpected - fHeight ), 0.01 );
      }
      else if ( fabs( 2 - fX ) < 0.01 )
      {
        //Seedling - get the diam10 and height and compare
        p_oTree->GetValue( p_oPop->GetDiam10Code( p_oTree->GetSpecies(), p_oTree->GetType() ), & fDiam10 );
        p_oTree->GetValue( p_oPop->GetHeightCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fHeight );

        fExpected = 0.901196874;
        EXPECT_LT( fabs( fExpected - fDiam10 ), 0.01 );

        fExpected = 1.01;
        EXPECT_LT( fabs( fExpected - fHeight ), 0.01 );

      }
      else if ( fabs( 3 - fX ) < 0.01 )
      {

        //Sapling - get the diam10, DBH, and height and compare
        p_oTree->GetValue( p_oPop->GetDiam10Code( p_oTree->GetSpecies(), p_oTree->GetType() ), & fDiam10 );
        p_oTree->GetValue( p_oPop->GetHeightCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fHeight );
        p_oTree->GetValue( p_oPop->GetDbhCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fDbh );

        fExpected = 6.5;
        EXPECT_LT( fabs( fExpected - fDiam10 ), 0.01 );

        fExpected = 5.2052;
        EXPECT_LT( fabs( fExpected - fDbh ), 0.01 );

        fExpected = 6.84563436;
        EXPECT_LT( fabs( fExpected - fHeight ), 0.01 );

      }
      else if ( fabs( 4 - fX ) < 0.01 )
      {
        //Sapling - get the diam10, DBH, and height and compare
        p_oTree->GetValue( p_oPop->GetDiam10Code( p_oTree->GetSpecies(), p_oTree->GetType() ), & fDiam10 );
        p_oTree->GetValue( p_oPop->GetHeightCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fHeight );
        p_oTree->GetValue( p_oPop->GetDbhCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fDbh );

        fExpected = 9.99000999;
        EXPECT_LT( fabs( fExpected - fDiam10 ), 0.01 );

        fExpected = 8;
        EXPECT_LT( fabs( fExpected - fDbh ), 0.01 );

        fExpected = 9.461874761;
        EXPECT_LT( fabs( fExpected - fHeight ), 0.01 );

      }
      else if ( fabs( 5 - fX ) < 0.01 )
      {
        //Sapling - get the diam10, DBH, and height and compare
        p_oTree->GetValue( p_oPop->GetDiam10Code( p_oTree->GetSpecies(), p_oTree->GetType() ), & fDiam10 );
        p_oTree->GetValue( p_oPop->GetHeightCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fHeight );
        p_oTree->GetValue( p_oPop->GetDbhCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fDbh );

        fExpected = 2.077134764;
        EXPECT_LT( fabs( fExpected - fDiam10 ), 0.01 );

        fExpected = 1.663369519;
        EXPECT_LT( fabs( fExpected - fDbh ), 0.01 );

        fExpected = 3.2;
        EXPECT_LT( fabs( fExpected - fHeight ), 0.01 );

      }
      else if ( fabs( 6 - fX ) < 0.01 )
      {
        //Adult - get the DBH and height and compare
        p_oTree->GetValue( p_oPop->GetHeightCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fHeight );
        p_oTree->GetValue( p_oPop->GetDbhCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fDbh );

        fExpected = 15;
        EXPECT_LT( fabs( fExpected - fDbh ), 0.01 );

        fExpected = 15.13074207;
        EXPECT_LT( fabs( fExpected - fHeight ), 0.01 );

      }
      else if ( fabs( 7 - fX ) < 0.01 )
      {
        //Adult - get the DBH and height and compare
        p_oTree->GetValue( p_oPop->GetHeightCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fHeight );
        p_oTree->GetValue( p_oPop->GetDbhCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fDbh );

        fExpected = 23.15587652;
        EXPECT_LT( fabs( fExpected - fDbh ), 0.01 );

        fExpected = 20.4;
        EXPECT_LT( fabs( fExpected - fHeight ), 0.01 );

      }
      else if ( fabs( 8 - fX ) < 0.01 )
      {
        //Snag - get the DBH and height and compare
        p_oTree->GetValue( p_oPop->GetHeightCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fHeight );
        p_oTree->GetValue( p_oPop->GetDbhCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fDbh );

        fExpected = 43;
        EXPECT_LT( fabs( fExpected - fDbh ), 0.01 );

        fExpected = 28.93869474;
        EXPECT_LT( fabs( fExpected - fHeight ), 0.01 );

      }
      else if ( fabs( 9 - fX ) < 0.01 )
      {
        //Snag - get the DBH and height and compare
        p_oTree->GetValue( p_oPop->GetHeightCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fHeight );
        p_oTree->GetValue( p_oPop->GetDbhCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fDbh );

        fExpected = 15.41359121;
        EXPECT_LT( fabs( fExpected - fDbh ), 0.01 );

        fExpected = 15.43;
        EXPECT_LT( fabs( fExpected - fHeight ), 0.01 );

      }
      else if ( fabs( 10 - fX ) < 0.01 )
      {
        //Seedling - get the diam10 and height and compare
        p_oTree->GetValue( p_oPop->GetDiam10Code( p_oTree->GetSpecies(), p_oTree->GetType() ), & fDiam10 );
        p_oTree->GetValue( p_oPop->GetHeightCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fHeight );

        fExpected = 0.8;
        EXPECT_LT( fabs( fExpected - fDiam10 ), 0.01 );

        fExpected = 0.909206115;
        EXPECT_LT( fabs( fExpected - fHeight ), 0.01 );

      }
      else if ( fabs( 11 - fX ) < 0.01 )
      {
        //Seedling - get the diam10 and height and compare
        p_oTree->GetValue( p_oPop->GetDiam10Code( p_oTree->GetSpecies(), p_oTree->GetType() ), & fDiam10 );
        p_oTree->GetValue( p_oPop->GetHeightCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fHeight );

        fExpected = 0.65;
        EXPECT_LT( fabs( fExpected - fDiam10 ), 0.01 );

        fExpected = 1.05;
        EXPECT_LT( fabs( fExpected - fHeight ), 0.01 );

      }
      else if ( fabs( 12 - fX ) < 0.01 )
      {
        //Sapling - get the diam10, DBH, and height and compare
        p_oTree->GetValue( p_oPop->GetDiam10Code( p_oTree->GetSpecies(), p_oTree->GetType() ), & fDiam10 );
        p_oTree->GetValue( p_oPop->GetHeightCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fHeight );
        p_oTree->GetValue( p_oPop->GetDbhCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fDbh );

        fExpected = 5.36963037;
        EXPECT_LT( fabs( fExpected - fDiam10 ), 0.01 );

        fExpected = 4.3;
        EXPECT_LT( fabs( fExpected - fDbh ), 0.01 );

        fExpected = 5.950308026;
        EXPECT_LT( fabs( fExpected - fHeight ), 0.01 );
      }
      else if ( fabs( 13 - fX ) < 0.01 )
      {
        //Sapling - get the diam10, DBH, and height and compare
        p_oTree->GetValue( p_oPop->GetDiam10Code( p_oTree->GetSpecies(), p_oTree->GetType() ), & fDiam10 );
        p_oTree->GetValue( p_oPop->GetHeightCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fHeight );
        p_oTree->GetValue( p_oPop->GetDbhCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fDbh );

        fExpected = 5.6;
        EXPECT_TRUE( fabs( fExpected - fDiam10 ) < 0.01 || fabs( fExpected - fDbh ) < 0.01 );

        fExpected = 5.6;
        EXPECT_LT( fabs( fExpected - fHeight ), 0.01 );
      }
      else if ( fabs( 14 - fX ) < 0.01 )
      {
        //Adult - get the DBH and height and compare
        p_oTree->GetValue( p_oPop->GetHeightCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fHeight );
        p_oTree->GetValue( p_oPop->GetDbhCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fDbh );

        fExpected = 18.7;
        EXPECT_LT( fabs( fExpected - fDbh ), 0.01 );

        fExpected = 17.68084137;
        EXPECT_LT( fabs( fExpected - fHeight ), 0.01 );
      }
      else if ( fabs( 15 - fX ) < 0.01 )
      {
        //Adult - get the DBH and height and compare
        p_oTree->GetValue( p_oPop->GetHeightCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fHeight );
        p_oTree->GetValue( p_oPop->GetDbhCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fDbh );

        fExpected = 21.2;
        EXPECT_LT( fabs( fExpected - fDbh ), 0.01 );

        fExpected = 18.7;
        EXPECT_LT( fabs( fExpected - fHeight ), 0.01 );
      }
      else if ( fabs( 16 - fX ) < 0.01 )
      {
        //Snag - get the DBH and height and compare
        p_oTree->GetValue( p_oPop->GetHeightCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fHeight );
        p_oTree->GetValue( p_oPop->GetDbhCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fDbh );

        fExpected = 45.9;
        EXPECT_LT( fabs( fExpected - fDbh ), 0.01 );

        fExpected = 29.81422424;
        EXPECT_LT( fabs( fExpected - fHeight ), 0.01 );
      }
      else if ( fabs( 17 - fX ) < 0.01 )
      {
        //Snag - get the DBH and height and compare
        p_oTree->GetValue( p_oPop->GetHeightCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fHeight );
        p_oTree->GetValue( p_oPop->GetDbhCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fDbh );

        fExpected = 32.5;
        EXPECT_LT( fabs( fExpected - fDbh ), 0.01 );

        fExpected = 15.8;
        EXPECT_LT( fabs( fExpected - fHeight ), 0.01 );
      }
      else
      {
        FAIL() << "Found unexpected tree.";
      }


      iTreeTotal++;
      p_oTree = p_oAllTrees->NextTree();
    }

    //Verify that we found all the trees
    EXPECT_EQ( iTreeTotal, 17 );
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestTextTreeMapReading2()
// Makes sure that tree maps are read correctly. This includes trees of every
// tree type, with each type defined by either diameter or height.
// WriteTreePopulation2XMLFile11() writes the tree map parameter file.
/////////////////////////////////////////////////////////////////////////////
TEST(TreePopulation, TestTextTreeMapReading2) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTreeSearch * p_oAllTrees;
    clTree * p_oTree;
    float fX, fDbh, fDiam10, fExpected, fTemp;
    int iTreeTotal = 0, iTemp, iExpected;
    bool bTemp;

    //Read in the parameter file
    p_oSimManager->ReadFile( WriteTreePopulation2XMLFile11() );
    DeleteThisFile("TestTreeFile1.txt");
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Find all trees
    p_oAllTrees = p_oPop->Find( "all" );
    p_oTree = p_oAllTrees->NextTree();
    while ( p_oTree )
    {

      //Get the X - that's the tree's number
      p_oTree->GetValue( p_oPop->GetXCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fX );

      if ( fabs( 1 - fX ) < 0.01 )
      {
        //Snag
        EXPECT_EQ(p_oTree->GetType(), clTreePopulation::snag);
        EXPECT_EQ(p_oTree->GetSpecies(), 0);
        p_oTree->GetValue( p_oPop->GetDbhCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fDbh );

        fExpected = 67.38;
        EXPECT_LT( fabs( fExpected - fDbh ), 0.0001 );

        //Light
        fExpected = 57.79;
        p_oTree->GetValue( p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType() ), & fTemp );
        EXPECT_LT( fabs( fExpected - fTemp ), 0.01 );

        //Age
        iExpected = 1;
        p_oTree->GetValue( p_oPop->GetIntDataCode("Age", p_oTree->GetSpecies(), p_oTree->GetType() ), & iTemp );
        EXPECT_LT( fabs( iExpected - iTemp ), 0.01 );
      }
      else if ( fabs( 2 - fX ) < 0.01 )
      {
        //Sapling
        EXPECT_EQ(p_oTree->GetType(), clTreePopulation::sapling);
        EXPECT_EQ(p_oTree->GetSpecies(), 0);
        p_oTree->GetValue( p_oPop->GetDbhCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fDbh );

        fExpected = 8.9;
        EXPECT_LT( fabs( fExpected - fDbh ), 0.01 );

        //Light
        fExpected = 27.81;
        p_oTree->GetValue( p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType() ), & fTemp );
        EXPECT_LT( fabs( fExpected - fTemp ), 0.01 );

        //ylr
        iExpected = 2;
        p_oTree->GetValue( p_oPop->GetIntDataCode("ylr", p_oTree->GetSpecies(), p_oTree->GetType() ), & iTemp );
        EXPECT_LT( fabs( iExpected - iTemp ), 0.01 );
      }
      else if ( fabs( 3 - fX ) < 0.01 )
      {

        EXPECT_EQ(p_oTree->GetType(), clTreePopulation::adult);
        EXPECT_EQ(p_oTree->GetSpecies(), 0);
        p_oTree->GetValue( p_oPop->GetDbhCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fDbh );

        fExpected = 73.9;
        EXPECT_LT( fabs( fExpected - fDbh ), 0.0001 );

        //Light
        fExpected = 93.63;
        p_oTree->GetValue( p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType() ), & fTemp );
        EXPECT_LT( fabs( fExpected - fTemp ), 0.01 );

        //Growth
        fExpected = 12.4;
        p_oTree->GetValue( p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType() ), & fTemp );
        EXPECT_LT( fabs( fExpected - fTemp ), 0.01 );
      }
      else if ( fabs( 4 - fX ) < 0.01 )
      {
        EXPECT_EQ(p_oTree->GetType(), clTreePopulation::adult);
        EXPECT_EQ(p_oTree->GetSpecies(), 1);
        p_oTree->GetValue( p_oPop->GetDbhCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fDbh );

        fExpected = 53.04;
        EXPECT_LT( fabs( fExpected - fDbh ), 0.0001 );

        //Light
        fExpected = 68.75;
        p_oTree->GetValue( p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType() ), & fTemp );
        EXPECT_LT( fabs( fExpected - fTemp ), 0.01 );

        //Growth
        fExpected = 5.32;
        p_oTree->GetValue( p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType() ), & fTemp );
        EXPECT_LT( fabs( fExpected - fTemp ), 0.01 );

        //Vigorous
        p_oTree->GetValue( p_oPop->GetBoolDataCode("vigorous", p_oTree->GetSpecies(), p_oTree->GetType() ), & bTemp );
        ASSERT_TRUE( bTemp );
      }
      else if ( fabs( 5 - fX ) < 0.01 )
      {
        EXPECT_EQ(p_oTree->GetType(), clTreePopulation::adult);
        EXPECT_EQ(p_oTree->GetSpecies(), 2);
        p_oTree->GetValue( p_oPop->GetDbhCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fDbh );

        fExpected = 95.17;
        EXPECT_LT( fabs( fExpected - fDbh ), 0.0001 );

        //Light
        fExpected = 58.11;
        p_oTree->GetValue( p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType() ), & fTemp );
        EXPECT_LT( fabs( fExpected - fTemp ), 0.01 );

        //Growth
        fExpected = 1.7;
        p_oTree->GetValue( p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType() ), & fTemp );
        EXPECT_LT( fabs( fExpected - fTemp ), 0.01 );
      }
      else if ( fabs( 6 - fX ) < 0.01 )
      {
        //Snag
        EXPECT_EQ(p_oTree->GetType(), clTreePopulation::snag);
        EXPECT_EQ(p_oTree->GetSpecies(), 1);
        p_oTree->GetValue( p_oPop->GetDbhCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fDbh );

        fExpected = 50.1;
        EXPECT_LT( fabs( fExpected - fDbh ), 0.0001 );

        //Light
        fExpected = 7.66;
        p_oTree->GetValue( p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType() ), & fTemp );
        EXPECT_LT( fabs( fExpected - fTemp ), 0.01 );

        //Age
        iExpected = 4;
        p_oTree->GetValue( p_oPop->GetIntDataCode("Age", p_oTree->GetSpecies(), p_oTree->GetType() ), & iTemp );
        EXPECT_LT( fabs( iExpected - iTemp ), 0.01 );
      }
      else if ( fabs( 7 - fX ) < 0.01 )
      {
        //Sapling
        EXPECT_EQ(p_oTree->GetType(), clTreePopulation::sapling);
        EXPECT_EQ(p_oTree->GetSpecies(), 0);
        p_oTree->GetValue( p_oPop->GetDbhCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fDbh );

        fExpected = 4.19;
        EXPECT_LT( fabs( fExpected - fDbh ), 0.01 );

        //Light
        fExpected = 0.04;
        p_oTree->GetValue( p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType() ), & fTemp );
        EXPECT_LT( fabs( fExpected - fTemp ), 0.01 );

        //ylr
        iExpected = 1;
        p_oTree->GetValue( p_oPop->GetIntDataCode("ylr", p_oTree->GetSpecies(), p_oTree->GetType() ), & iTemp );
        EXPECT_LT( fabs( iExpected - iTemp ), 0.01 );
      }
      else if ( fabs( 8 - fX ) < 0.01 )
      {
        EXPECT_EQ(p_oTree->GetType(), clTreePopulation::adult);
        EXPECT_EQ(p_oTree->GetSpecies(), 3);
        p_oTree->GetValue( p_oPop->GetDbhCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fDbh );

        fExpected = 25.19;
        EXPECT_LT( fabs( fExpected - fDbh ), 0.0001 );

        //Light
        fExpected = 64.47;
        p_oTree->GetValue( p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType() ), & fTemp );
        EXPECT_LT( fabs( fExpected - fTemp ), 0.01 );

        //Growth
        fExpected = 6.69;
        p_oTree->GetValue( p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType() ), & fTemp );
        EXPECT_LT( fabs( fExpected - fTemp ), 0.01 );

        //Vigorous
        p_oTree->GetValue( p_oPop->GetBoolDataCode("vigorous", p_oTree->GetSpecies(), p_oTree->GetType() ), & bTemp );
        ASSERT_TRUE( !bTemp );
      }
      else if ( fabs( 9 - fX ) < 0.01 )
      {
        //Snag
        EXPECT_EQ(p_oTree->GetType(), clTreePopulation::snag);
        EXPECT_EQ(p_oTree->GetSpecies(), 2);
        p_oTree->GetValue( p_oPop->GetDbhCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fDbh );

        fExpected = 96.8;
        EXPECT_LT( fabs( fExpected - fDbh ), 0.0001 );

        //Light
        fExpected = 31.19;
        p_oTree->GetValue( p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType() ), & fTemp );
        EXPECT_LT( fabs( fExpected - fTemp ), 0.01 );

        //Age
        iExpected = 8;
        p_oTree->GetValue( p_oPop->GetIntDataCode("Age", p_oTree->GetSpecies(), p_oTree->GetType() ), & iTemp );
        EXPECT_LT( fabs( iExpected - iTemp ), 0.01 );
      }
      else if ( fabs( 10 - fX ) < 0.01 )
      {
        //Sapling
        EXPECT_EQ(p_oTree->GetType(), clTreePopulation::sapling);
        EXPECT_EQ(p_oTree->GetSpecies(), 2);
        p_oTree->GetValue( p_oPop->GetDbhCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fDbh );

        fExpected = 4.55;
        EXPECT_LT( fabs( fExpected - fDbh ), 0.01 );

        //Light
        fExpected = 73.28;
        p_oTree->GetValue( p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType() ), & fTemp );
        EXPECT_LT( fabs( fExpected - fTemp ), 0.01 );

        //ylr
        iExpected = 0;
        p_oTree->GetValue( p_oPop->GetIntDataCode("ylr", p_oTree->GetSpecies(), p_oTree->GetType() ), & iTemp );
        EXPECT_LT( fabs( iExpected - iTemp ), 0.01 );
      }
      else if ( fabs( 11 - fX ) < 0.01 )
      {
        //Seedling
        EXPECT_EQ(p_oTree->GetType(), clTreePopulation::seedling);
        EXPECT_EQ(p_oTree->GetSpecies(), 3);
        p_oTree->GetValue( p_oPop->GetDiam10Code( p_oTree->GetSpecies(), p_oTree->GetType() ), & fDiam10 );

        fExpected = 0.61;
        EXPECT_LT( fabs( fExpected - fDiam10 ), 0.01 );

        //Light
        fExpected = 58.66;
        p_oTree->GetValue( p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType() ), & fTemp );
        EXPECT_LT( fabs( fExpected - fTemp ), 0.01 );
      }
      else if ( fabs( 12 - fX ) < 0.01 )
      {
        //Snag
        EXPECT_EQ(p_oTree->GetType(), clTreePopulation::snag);
        EXPECT_EQ(p_oTree->GetSpecies(), 3);
        p_oTree->GetValue( p_oPop->GetDbhCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fDbh );

        fExpected = 26.58;
        EXPECT_LT( fabs( fExpected - fDbh ), 0.0001 );

        //Light
        fExpected = 31.71;
        p_oTree->GetValue( p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType() ), & fTemp );
        EXPECT_LT( fabs( fExpected - fTemp ), 0.01 );

        //Age
        iExpected = 2;
        p_oTree->GetValue( p_oPop->GetIntDataCode("Age", p_oTree->GetSpecies(), p_oTree->GetType() ), & iTemp );
        EXPECT_LT( fabs( iExpected - iTemp ), 0.01 );
      }
      else
      {
        FAIL() << "Found unexpected tree.";
      }


      iTreeTotal++;
      p_oTree = p_oAllTrees->NextTree();
    }

    //Verify that we found all the trees
    EXPECT_EQ( iTreeTotal, 12 );
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestInitialDensities()
// Makes sure that initial densities are set up correctly. There are 7 runs.
// They are as follows:
//
// -- Run 1: No trees in the initial densities.  (No trees are created.)
// -- Run 2: No seedlings at all.
// -- Run 3: Seedlings in all three size classes, all species, plus DBH
//    class seedlings.
// -- Run 4: Seedlings in only the first size class, some species.
// -- Run 5: Seedlings in only the second size class, some species.
// -- Run 6: Seedlings in only the third size class, some species.
// -- Run 7: Only seedlings in the DBH size class.</li>
//
// There is a parameter file for each run, WriteTreePopulation2XMLFile2 through
// WriteTreePopulation2XMLFile8.
/////////////////////////////////////////////////////////////////////////////
TEST(TreePopulation, TestInitialDensities) {
  clTreePopulation * p_oPop;
  clTreeSearch * p_oAllTrees;
  clTree * p_oTree;
  float fDbh, fHeight;
  int **p_iAdultCounts = new int*[3],
      **p_iSeedlingCounts = new int*[3], i, j;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    //Counts:  first index size class, second species
    for (i = 0; i < 3; i++) {
      p_iAdultCounts[i] = new int[3];
      p_iSeedlingCounts[i] = new int[3];
    }

    //*****************************
    // Run 1
    //*****************************
    p_oSimManager->ReadFile( WriteTreePopulation2XMLFile2() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
    p_oAllTrees = p_oPop->Find( "all" );
    EXPECT_EQ(NULL, p_oAllTrees->NextTree());

    //*****************************
    // Run 2
    //*****************************
    p_oSimManager->ReadFile( WriteTreePopulation2XMLFile3() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    for (i = 0; i < 3; i++) {
      for (j = 0; j < 3; j++) {
        p_iAdultCounts[i][j] = 0;
      }
    }

    //Find all trees
    p_oAllTrees = p_oPop->Find( "all" );
    p_oTree = p_oAllTrees->NextTree();
    while ( p_oTree )
    {

      if (p_oTree->GetType() != clTreePopulation::seedling) {
        //Get the DBH
        p_oTree->GetValue( p_oPop->GetDbhCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fDbh );

        if (fDbh <= 10) {
          p_iAdultCounts[0][p_oTree->GetSpecies()]++;
        }
        else if (fDbh > 10 && fDbh <= 15) {
          p_iAdultCounts[1][p_oTree->GetSpecies()]++;
        }
        else if (fDbh > 20 && fDbh <= 35) {
          p_iAdultCounts[2][p_oTree->GetSpecies()]++;
        }
        else {
          FAIL() << "Unexpected DBH for run 2!";
        }
      }
      else {
        FAIL() << "Unexpected seedling for run 2!";
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    //Verify that we found all the trees
    //Species 1
    EXPECT_EQ( p_iAdultCounts[0][0], 0 );
    EXPECT_EQ( p_iAdultCounts[1][0], 60 );
    EXPECT_EQ( p_iAdultCounts[2][0], 120 );
    //Species 2
    EXPECT_EQ( p_iAdultCounts[0][1], 20 );
    EXPECT_EQ( p_iAdultCounts[1][1], 80 );
    EXPECT_EQ( p_iAdultCounts[2][1], 140 );
    //Species 3
    EXPECT_EQ( p_iAdultCounts[0][2], 40 );
    EXPECT_EQ( p_iAdultCounts[1][2], 100 );
    EXPECT_EQ( p_iAdultCounts[2][2], 160 );

    //*****************************
    // Run 3
    //*****************************
    p_oSimManager->ReadFile( WriteTreePopulation2XMLFile4() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    for (i = 0; i < 3; i++) {
      for (j = 0; j < 3; j++) {
        p_iAdultCounts[i][j] = 0;
        p_iSeedlingCounts[i][j] = 0;
      }
    }

    //Find all trees
    p_oAllTrees = p_oPop->Find( "all" );
    p_oTree = p_oAllTrees->NextTree();
    while ( p_oTree )
    {

      if (p_oTree->GetType() != clTreePopulation::seedling) {
        //Get the DBH
        p_oTree->GetValue( p_oPop->GetDbhCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fDbh );

        if (fDbh <= 10) {
          p_iAdultCounts[0][p_oTree->GetSpecies()]++;
        }
        else if (fDbh > 10 && fDbh <= 15) {
          p_iAdultCounts[1][p_oTree->GetSpecies()]++;
        }
        else if (fDbh > 20 && fDbh <= 35) {
          p_iAdultCounts[2][p_oTree->GetSpecies()]++;
        }
        else {
          FAIL() << "Unexpected DBH for run 3!";
        }
      }
      else {
        //It's a seedling - get the height
        p_oTree->GetValue( p_oPop->GetHeightCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fHeight );
        if (fHeight <= 0.5) {
          p_iSeedlingCounts[0][p_oTree->GetSpecies()]++;
        }
        else if (fHeight > 0.5 && fHeight <= 1) {
          p_iSeedlingCounts[1][p_oTree->GetSpecies()]++;
        }
        else {
          p_iSeedlingCounts[2][p_oTree->GetSpecies()]++;
        }
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    //Verify that we found all the adult trees
    //Species 1
    EXPECT_EQ( p_iAdultCounts[0][0], 0 );
    EXPECT_EQ( p_iAdultCounts[1][0], 60 );
    EXPECT_EQ( p_iAdultCounts[2][0], 120 );
    //Species 2
    EXPECT_EQ( p_iAdultCounts[0][1], 20 );
    EXPECT_EQ( p_iAdultCounts[1][1], 80 );
    EXPECT_EQ( p_iAdultCounts[2][1], 140 );
    //Species 3
    EXPECT_EQ( p_iAdultCounts[0][2], 40 );
    EXPECT_EQ( p_iAdultCounts[1][2], 100 );
    EXPECT_EQ( p_iAdultCounts[2][2], 160 );

    //Verify that we found all the seedlings
    //Species 1
    EXPECT_EQ( p_iSeedlingCounts[0][0], 72 );
    EXPECT_EQ( p_iSeedlingCounts[1][0], 72 );
    EXPECT_EQ( p_iSeedlingCounts[2][0], 96 );
    //Species 2
    EXPECT_EQ( p_iSeedlingCounts[0][1], 88 );
    EXPECT_EQ( p_iSeedlingCounts[1][1], 80 );
    EXPECT_EQ( p_iSeedlingCounts[2][1], 104 );
    //Species 3
    EXPECT_EQ( p_iSeedlingCounts[0][2], 104 );
    EXPECT_EQ( p_iSeedlingCounts[1][2], 88 );
    EXPECT_EQ( p_iSeedlingCounts[2][2], 112 );

    //*****************************
    // Run 4
    //*****************************
    p_oSimManager->ReadFile( WriteTreePopulation2XMLFile5() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    for (i = 0; i < 3; i++) {
      for (j = 0; j < 3; j++) {
        p_iAdultCounts[i][j] = 0;
        p_iSeedlingCounts[i][j] = 0;
      }
    }

    //Find all trees
    p_oAllTrees = p_oPop->Find( "all" );
    p_oTree = p_oAllTrees->NextTree();
    while ( p_oTree )
    {

      if (p_oTree->GetType() != clTreePopulation::seedling) {
        //Get the DBH
        p_oTree->GetValue( p_oPop->GetDbhCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fDbh );

        if (fDbh <= 10) {
          p_iAdultCounts[0][p_oTree->GetSpecies()]++;
        }
        else if (fDbh > 10 && fDbh <= 15) {
          p_iAdultCounts[1][p_oTree->GetSpecies()]++;
        }
        else if (fDbh > 20 && fDbh <= 35) {
          p_iAdultCounts[2][p_oTree->GetSpecies()]++;
        }
        else {
          FAIL() << "Unexpected DBH for run 4!";
        }
      }
      else {
        //It's a seedling - get the height
        p_oTree->GetValue( p_oPop->GetHeightCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fHeight );
        if (fHeight <= 0.5) {
          p_iSeedlingCounts[0][p_oTree->GetSpecies()]++;
        }
        else if (fHeight > 0.5 && fHeight <= 1) {
          p_iSeedlingCounts[1][p_oTree->GetSpecies()]++;
        }
        else {
          p_iSeedlingCounts[2][p_oTree->GetSpecies()]++;
        }
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    //Verify that we found all the adult trees
    //Species 1
    EXPECT_EQ( p_iAdultCounts[0][0], 0 );
    EXPECT_EQ( p_iAdultCounts[1][0], 0 );
    EXPECT_EQ( p_iAdultCounts[2][0], 0 );
    //Species 2
    EXPECT_EQ( p_iAdultCounts[0][1], 0 );
    EXPECT_EQ( p_iAdultCounts[1][1], 0 );
    EXPECT_EQ( p_iAdultCounts[2][1], 0 );
    //Species 3
    EXPECT_EQ( p_iAdultCounts[0][2], 0 );
    EXPECT_EQ( p_iAdultCounts[1][2], 0 );
    EXPECT_EQ( p_iAdultCounts[2][2], 0 );

    //Verify that we found all the seedlings
    //Species 1
    EXPECT_EQ( p_iSeedlingCounts[0][0], 48 );
    EXPECT_EQ( p_iSeedlingCounts[1][0], 0 );
    EXPECT_EQ( p_iSeedlingCounts[2][0], 0 );
    //Species 2
    EXPECT_EQ( p_iSeedlingCounts[0][1], 0 );
    EXPECT_EQ( p_iSeedlingCounts[1][1], 0 );
    EXPECT_EQ( p_iSeedlingCounts[2][1], 0 );
    //Species 3
    EXPECT_EQ( p_iSeedlingCounts[0][2], 64 );
    EXPECT_EQ( p_iSeedlingCounts[1][2], 0 );
    EXPECT_EQ( p_iSeedlingCounts[2][2], 0 );

    //*****************************
    // Run 5
    //*****************************
    p_oSimManager->ReadFile( WriteTreePopulation2XMLFile6() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    for (i = 0; i < 3; i++) {
      for (j = 0; j < 3; j++) {
        p_iAdultCounts[i][j] = 0;
        p_iSeedlingCounts[i][j] = 0;
      }
    }

    //Find all trees
    p_oAllTrees = p_oPop->Find( "all" );
    p_oTree = p_oAllTrees->NextTree();
    while ( p_oTree )
    {

      if (p_oTree->GetType() != clTreePopulation::seedling) {
        //Get the DBH
        p_oTree->GetValue( p_oPop->GetDbhCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fDbh );

        if (fDbh <= 10) {
          p_iAdultCounts[0][p_oTree->GetSpecies()]++;
        }
        else if (fDbh > 10 && fDbh <= 15) {
          p_iAdultCounts[1][p_oTree->GetSpecies()]++;
        }
        else if (fDbh > 20 && fDbh <= 35) {
          p_iAdultCounts[2][p_oTree->GetSpecies()]++;
        }
        else {
          FAIL() << "Unexpected DBH for run 5!";
        }
      }
      else {
        //It's a seedling - get the height
        p_oTree->GetValue( p_oPop->GetHeightCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fHeight );
        if (fHeight <= 0.5) {
          p_iSeedlingCounts[0][p_oTree->GetSpecies()]++;
        }
        else if (fHeight > 0.5 && fHeight <= 1) {
          p_iSeedlingCounts[1][p_oTree->GetSpecies()]++;
        }
        else {
          p_iSeedlingCounts[2][p_oTree->GetSpecies()]++;
        }
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    //Verify that we found all the adult trees
    //Species 1
    EXPECT_EQ( p_iAdultCounts[0][0], 0 );
    EXPECT_EQ( p_iAdultCounts[1][0], 0 );
    EXPECT_EQ( p_iAdultCounts[2][0], 0 );
    //Species 2
    EXPECT_EQ( p_iAdultCounts[0][1], 0 );
    EXPECT_EQ( p_iAdultCounts[1][1], 0 );
    EXPECT_EQ( p_iAdultCounts[2][1], 0 );
    //Species 3
    EXPECT_EQ( p_iAdultCounts[0][2], 0 );
    EXPECT_EQ( p_iAdultCounts[1][2], 0 );
    EXPECT_EQ( p_iAdultCounts[2][2], 0 );

    //Verify that we found all the seedlings
    //Species 1
    EXPECT_EQ( p_iSeedlingCounts[0][0], 0 );
    EXPECT_EQ( p_iSeedlingCounts[1][0], 0 );
    EXPECT_EQ( p_iSeedlingCounts[2][0], 0 );
    //Species 2
    EXPECT_EQ( p_iSeedlingCounts[0][1], 0 );
    EXPECT_EQ( p_iSeedlingCounts[1][1], 80 );
    EXPECT_EQ( p_iSeedlingCounts[2][1], 0 );
    //Species 3
    EXPECT_EQ( p_iSeedlingCounts[0][2], 0 );
    EXPECT_EQ( p_iSeedlingCounts[1][2], 88 );
    EXPECT_EQ( p_iSeedlingCounts[2][2], 0 );

    //*****************************
    // Run 6
    //*****************************
    p_oSimManager->ReadFile( WriteTreePopulation2XMLFile7() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    for (i = 0; i < 3; i++) {
      for (j = 0; j < 3; j++) {
        p_iAdultCounts[i][j] = 0;
        p_iSeedlingCounts[i][j] = 0;
      }
    }

    //Find all trees
    p_oAllTrees = p_oPop->Find( "all" );
    p_oTree = p_oAllTrees->NextTree();
    while ( p_oTree )
    {

      if (p_oTree->GetType() != clTreePopulation::seedling) {
        //Get the DBH
        p_oTree->GetValue( p_oPop->GetDbhCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fDbh );

        if (fDbh <= 10) {
          p_iAdultCounts[0][p_oTree->GetSpecies()]++;
        }
        else if (fDbh > 10 && fDbh <= 15) {
          p_iAdultCounts[1][p_oTree->GetSpecies()]++;
        }
        else if (fDbh > 20 && fDbh <= 35) {
          p_iAdultCounts[2][p_oTree->GetSpecies()]++;
        }
        else {
          FAIL() << "Unexpected DBH for run 6!";
        }
      }
      else {
        //It's a seedling - get the height
        p_oTree->GetValue( p_oPop->GetHeightCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fHeight );
        if (fHeight <= 0.5) {
          p_iSeedlingCounts[0][p_oTree->GetSpecies()]++;
        }
        else if (fHeight > 0.5 && fHeight <= 1) {
          p_iSeedlingCounts[1][p_oTree->GetSpecies()]++;
        }
        else {
          p_iSeedlingCounts[2][p_oTree->GetSpecies()]++;
        }
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    //Verify that we found all the adult trees
    //Species 1
    EXPECT_EQ( p_iAdultCounts[0][0], 0 );
    EXPECT_EQ( p_iAdultCounts[1][0], 0 );
    EXPECT_EQ( p_iAdultCounts[2][0], 0 );
    //Species 2
    EXPECT_EQ( p_iAdultCounts[0][1], 0 );
    EXPECT_EQ( p_iAdultCounts[1][1], 0 );
    EXPECT_EQ( p_iAdultCounts[2][1], 0 );
    //Species 3
    EXPECT_EQ( p_iAdultCounts[0][2], 0 );
    EXPECT_EQ( p_iAdultCounts[1][2], 0 );
    EXPECT_EQ( p_iAdultCounts[2][2], 0 );

    //Verify that we found all the seedlings
    //Species 1
    EXPECT_EQ( p_iSeedlingCounts[0][0], 0 );
    EXPECT_EQ( p_iSeedlingCounts[1][0], 0 );
    EXPECT_EQ( p_iSeedlingCounts[2][0], 96 );
    //Species 2
    EXPECT_EQ( p_iSeedlingCounts[0][1], 0 );
    EXPECT_EQ( p_iSeedlingCounts[1][1], 0 );
    EXPECT_EQ( p_iSeedlingCounts[2][1], 104 );
    //Species 3
    EXPECT_EQ( p_iSeedlingCounts[0][2], 0 );
    EXPECT_EQ( p_iSeedlingCounts[1][2], 0 );
    EXPECT_EQ( p_iSeedlingCounts[2][2], 0 );

    //*****************************
    // Run 7
    //*****************************
    p_oSimManager->ReadFile( WriteTreePopulation2XMLFile8() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    for (i = 0; i < 3; i++) {
      for (j = 0; j < 3; j++) {
        p_iAdultCounts[i][j] = 0;
        p_iSeedlingCounts[i][j] = 0;
      }
    }

    //Find all trees
    p_oAllTrees = p_oPop->Find( "all" );
    p_oTree = p_oAllTrees->NextTree();
    while ( p_oTree )
    {

      if (p_oTree->GetType() != clTreePopulation::seedling) {
        //Get the DBH
        p_oTree->GetValue( p_oPop->GetDbhCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fDbh );

        if (fDbh <= 10) {
          p_iAdultCounts[0][p_oTree->GetSpecies()]++;
        }
        else if (fDbh > 10 && fDbh <= 15) {
          p_iAdultCounts[1][p_oTree->GetSpecies()]++;
        }
        else if (fDbh > 20 && fDbh <= 35) {
          p_iAdultCounts[2][p_oTree->GetSpecies()]++;
        }
        else {
          FAIL() << "Unexpected DBH for run 7!";
        }
      }
      else {
        //It's a seedling - get diam10
        p_oTree->GetValue( p_oPop->GetDiam10Code( p_oTree->GetSpecies(), p_oTree->GetType() ), & fDbh );
        EXPECT_GT(fDbh, 0.08); EXPECT_LT(fDbh, 0.12);
        p_iSeedlingCounts[0][p_oTree->GetSpecies()]++;
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    //Verify that we found all the adult trees
    //Species 1
    EXPECT_EQ( p_iAdultCounts[0][0], 0 );
    EXPECT_EQ( p_iAdultCounts[1][0], 60 );
    EXPECT_EQ( p_iAdultCounts[2][0], 120 );
    //Species 2
    EXPECT_EQ( p_iAdultCounts[0][1], 20 );
    EXPECT_EQ( p_iAdultCounts[1][1], 80 );
    EXPECT_EQ( p_iAdultCounts[2][1], 140 );
    //Species 3
    EXPECT_EQ( p_iAdultCounts[0][2], 40 );
    EXPECT_EQ( p_iAdultCounts[1][2], 100 );
    EXPECT_EQ( p_iAdultCounts[2][2], 160 );

    //Verify that we found all the seedlings
    //Species 1
    EXPECT_EQ( p_iSeedlingCounts[0][0], 24 );
    EXPECT_EQ( p_iSeedlingCounts[1][0], 0 );
    EXPECT_EQ( p_iSeedlingCounts[2][0], 0 );
    //Species 2
    EXPECT_EQ( p_iSeedlingCounts[0][1], 32 );
    EXPECT_EQ( p_iSeedlingCounts[1][1], 0 );
    EXPECT_EQ( p_iSeedlingCounts[2][1], 0 );
    //Species 3
    EXPECT_EQ( p_iSeedlingCounts[0][2], 40 );
    EXPECT_EQ( p_iSeedlingCounts[1][2], 0 );
    EXPECT_EQ( p_iSeedlingCounts[2][2], 0 );

    for (i = 0; i < 3; i++) {
      delete[] p_iAdultCounts[i];
      delete[] p_iSeedlingCounts[i];
    }
    delete[] p_iAdultCounts;
    delete[] p_iSeedlingCounts;
    delete p_oSimManager;
  } catch (modelErr &e) {
    for (int i = 0; i < 3; i++) {
      delete[] p_iAdultCounts[i];
      delete[] p_iSeedlingCounts[i];
    }
    delete[] p_iAdultCounts;
    delete[] p_iSeedlingCounts;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestErrorProcessing()
////////////////////////////////////////////////////////////////////////////
TEST(TreePopulation2, TestErrorProcessing) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try
  {
    p_oSimManager->ReadFile(WriteTreePopulation2XMLErrorFile1());
    FAIL() << "TestInitialDensities error processing didn't catch error for WriteTreePopulation2XMLErrorFile1.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clTreePopulation::CreateTreesFromInitialDensities") != 0)
    {
      FAIL() << "TestInitialDensities error processing caught wrong error for WriteTreePopulation2XMLErrorFile1.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteTreePopulation2XMLErrorFile2());
    FAIL() << "TestInitialDensities error processing didn't catch error for WriteTreePopulation2XMLErrorFile2.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clTreePopulation::CreateTreesFromInitialDensities") != 0)
    {
      FAIL() << "TestInitialDensities error processing caught wrong error for WriteTreePopulation2XMLErrorFile2.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteTreePopulation2XMLErrorFile3());
    FAIL() << "TestInitialDensities error processing didn't catch error for WriteTreePopulation2XMLErrorFile3.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clTreePopulation::CreateTreesFromInitialDensities") != 0)
    {
      FAIL() << "TestInitialDensities error processing caught wrong error for WriteTreePopulation2XMLErrorFile3.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteTreePopulation2XMLErrorFile4());
    FAIL() << "TestInitialDensities error processing didn't catch error for WriteTreePopulation2XMLErrorFile4.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clTreePopulation::CreateTreesFromInitialDensities") != 0)
    {
      FAIL() << "TestInitialDensities error processing caught wrong error for WriteTreePopulation2XMLErrorFile4.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteTreePopulation2XMLErrorFile5());
    FAIL() << "TestInitialDensities error processing didn't catch error for WriteTreePopulation2XMLErrorFile5.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clTreePopulation::CreateTreesFromInitialDensities") != 0)
    {
      FAIL() << "TestInitialDensities error processing caught wrong error for WriteTreePopulation2XMLErrorFile5.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteTreePopulation2XMLErrorFile6());
    FAIL() << "TestInitialDensities error processing didn't catch error for WriteTreePopulation2XMLErrorFile6.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clTreePopulation::CreateTreesFromInitialDensities") != 0)
    {
      FAIL() << "TestInitialDensities error processing caught wrong error for WriteTreePopulation2XMLErrorFile6.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteTreePopulation2XMLErrorFile7());
    FAIL() << "TestInitialDensities error processing didn't catch error for WriteTreePopulation2XMLErrorFile7.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clTreePopulation::CreateTreesFromInitialDensities") != 0)
    {
      FAIL() << "TestInitialDensities error processing caught wrong error for WriteTreePopulation2XMLErrorFile7.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteTreePopulation2XMLErrorFile8());
    FAIL() << "TestInitialDensities error processing didn't catch error for WriteTreePopulation2XMLErrorFile8.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clTreePopulation::CreateTreesFromInitialDensities") != 0)
    {
      FAIL() << "TestInitialDensities error processing caught wrong error for WriteTreePopulation2XMLErrorFile8.";
    }
    ;
  }
  delete p_oSimManager;
}

/////////////////////////////////////////////////////////////////////////////
// WriteTreePopulation2XMLFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteTreePopulation2XMLFile1()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  WriteTreePopulation2CommonPlotStuff(oOut);

  oOut << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\"/>"
       << "</tr_speciesList>"
       << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
       << "<tr_minAdultDBH>"
       << "<tr_madVal species=\"Species_1\">10</tr_madVal>"
       << "</tr_minAdultDBH>"
       << "<tr_maxSeedlingHeight>"
       << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
       << "</tr_maxSeedlingHeight>"
       << "<tr_treemap>"
       << "<tm_treeSettings sp=\"Species_1\" tp=\"1\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"Diam10\">2</tm_floatCode>"
       << "<tm_floatCode label=\"Height\">3</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_1\" tp=\"2\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "<tm_floatCode label=\"Diam10\">3</tm_floatCode>"
       << "<tm_floatCode label=\"Height\">4</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_1\" tp=\"3\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "<tm_floatCode label=\"Height\">4</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_1\" tp=\"5\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "<tm_floatCode label=\"Height\">3</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tree sp=\"0\" tp=\"5\">" << "<fl c=\"0\">17</fl>" //X
       << "<fl c=\"1\">17</fl>" //Y
       << "<fl c=\"2\">32.5</fl>" //DBH
       << "<fl c=\"3\">15.8</fl>" //Height
       << "</tree>" << "<tree sp=\"0\" tp=\"5\">" << "<fl c=\"0\">16</fl>" //X
       << "<fl c=\"1\">16</fl>" //Y
       << "<fl c=\"2\">45.9</fl>" //DBH
       << "<fl c=\"3\">29.81422424</fl>" //Height
       << "</tree>" << "<tree sp=\"0\" tp=\"3\">" << "<fl c=\"0\">15</fl>" //X
       << "<fl c=\"1\">15</fl>" //Y
       << "<fl c=\"2\">21.2</fl>" //DBH
       << "<fl c=\"4\">18.7</fl>" //Height
       << "</tree>" << "<tree sp=\"0\" tp=\"3\">" << "<fl c=\"0\">14</fl>" //X
       << "<fl c=\"1\">14</fl>" //Y
       << "<fl c=\"2\">18.7</fl>" //DBH
       << "<fl c=\"4\">17.68084137</fl>" //Height
       << "</tree>" << "<tree sp=\"0\" tp=\"2\">" << "<fl c=\"0\">13</fl>" //X
       << "<fl c=\"1\">13</fl>" //Y
       << "<fl c=\"3\">5.6</fl>" //diam10
       << "<fl c=\"2\">5.6</fl>" //DBH
       << "<fl c=\"4\">5.6</fl>" //Height
       << "</tree>" << "<tree sp=\"0\" tp=\"2\">" << "<fl c=\"0\">12</fl>" //X
       << "<fl c=\"1\">12</fl>" //Y
       << "<fl c=\"3\">5.36963037</fl>" //diam10
       << "<fl c=\"2\">4.3</fl>" //DBH
       << "<fl c=\"4\">5.950308026</fl>" //Height
       << "</tree>" << "<tree sp=\"0\" tp=\"1\">" << "<fl c=\"0\">11</fl>" //X
       << "<fl c=\"1\">11</fl>" //Y
       << "<fl c=\"2\">0.65</fl>" //diam10
       << "<fl c=\"3\">1.05</fl>" //Height
       << "</tree>" << "<tree sp=\"0\" tp=\"1\">" << "<fl c=\"0\">10</fl>" //X
       << "<fl c=\"1\">10</fl>" //Y
       << "<fl c=\"2\">0.8</fl>" //diam10
       << "<fl c=\"3\">0.909206115</fl>" //Height
       << "</tree>" << "<tree sp=\"0\" tp=\"5\">" << "<fl c=\"0\">9</fl>" //X
       << "<fl c=\"1\">9</fl>" //Y
       << "<fl c=\"3\">15.43</fl>" //Height
       << "</tree>" << "<tree sp=\"0\" tp=\"5\">" << "<fl c=\"0\">8</fl>" //X
       << "<fl c=\"1\">8</fl>" //Y
       << "<fl c=\"2\">43</fl>" //DBH
       << "</tree>" << "<tree sp=\"0\" tp=\"3\">" << "<fl c=\"0\">7</fl>" //X
       << "<fl c=\"1\">7</fl>" //Y
       << "<fl c=\"4\">20.4</fl>" //Height
       << "</tree>" << "<tree sp=\"0\" tp=\"3\">" << "<fl c=\"0\">6</fl>" //X
       << "<fl c=\"1\">6</fl>" //Y
       << "<fl c=\"2\">15</fl>" //DBH
       << "</tree>" << "<tree sp=\"0\" tp=\"2\">" << "<fl c=\"0\">5</fl>" //X
       << "<fl c=\"1\">5</fl>" //Y
       << "<fl c=\"4\">3.2</fl>" //Height
       << "</tree>" << "<tree sp=\"0\" tp=\"2\">" << "<fl c=\"0\">4</fl>" //X
       << "<fl c=\"1\">4</fl>" //Y
       << "<fl c=\"2\">8</fl>" //DBH
       << "</tree>" << "<tree sp=\"0\" tp=\"2\">" << "<fl c=\"0\">3</fl>" //X
       << "<fl c=\"1\">3</fl>" //Y
       << "<fl c=\"3\">6.5</fl>" //diam10
       << "</tree>" << "<tree sp=\"0\" tp=\"1\">" << "<fl c=\"0\">2</fl>" //X
       << "<fl c=\"1\">2</fl>" //Y
       << "<fl c=\"3\">1.01</fl>" //height
       << "</tree>" << "<tree sp=\"0\" tp=\"1\">" << "<fl c=\"0\">1</fl>" //X
       << "<fl c=\"1\">1</fl>" //Y
       << "<fl c=\"2\">0.2</fl>" //diam10
       << "</tree>" << "</tr_treemap>" << "</trees>"
       << "<allometry>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"Species_1\">0.9</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"Species_1\">1</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
       << "<tr_whatSeedlingHeightDiam>"
       << "<tr_wsehdVal species=\"Species_1\">0</tr_wsehdVal>"
       << "</tr_whatSeedlingHeightDiam>"
       << "<tr_whatSaplingHeightDiam>"
       << "<tr_wsahdVal species=\"Species_1\">0</tr_wsahdVal>"
       << "</tr_whatSaplingHeightDiam>"
       << "<tr_whatAdultHeightDiam>"
       << "<tr_wahdVal species=\"Species_1\">0</tr_wahdVal>"
       << "</tr_whatAdultHeightDiam>"
       << "<tr_whatAdultCrownRadDiam>"
       << "<tr_wacrdVal species=\"Species_1\">0</tr_wacrdVal>"
       << "</tr_whatAdultCrownRadDiam>"
       << "<tr_whatAdultCrownHeightHeight>"
       << "<tr_wachhVal species=\"Species_1\">0</tr_wachhVal>"
       << "</tr_whatAdultCrownHeightHeight>"
       << "<tr_whatSaplingCrownRadDiam>"
       << "<tr_wscrdVal species=\"Species_1\">0</tr_wscrdVal>"
       << "</tr_whatSaplingCrownRadDiam>"
       << "<tr_whatSaplingCrownHeightHeight>"
       << "<tr_wschhVal species=\"Species_1\">0</tr_wschhVal>"
       << "</tr_whatSaplingCrownHeightHeight>"
       << "</allometry>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>ConstantGLI</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Snag\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<ConstantGLI1>"
       << "<li_constGLI>100</li_constGLI>"
       << "</ConstantGLI1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteTreePopulation2XMLFile2()
/////////////////////////////////////////////////////////////////////////////
const char* WriteTreePopulation2XMLFile2()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  WriteTreePopulation2CommonPlotStuff(oOut);

  oOut << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\"/>"
       << "<tr_species speciesName=\"Species_2\"/>"
       << "<tr_species speciesName=\"Species_3\"/>"
       << "</tr_speciesList>";

  WriteTreePopulation2CommonFileStuff(oOut);

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteTreePopulation2XMLFile3()
/////////////////////////////////////////////////////////////////////////////
const char* WriteTreePopulation2XMLFile3()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  WriteTreePopulation2CommonPlotStuff(oOut);

  oOut << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\"/>"
       << "<tr_species speciesName=\"Species_2\"/>"
       << "<tr_species speciesName=\"Species_3\"/>"
       << "</tr_speciesList>"
       << "<tr_sizeClasses>"
       << "<tr_sizeClass sizeKey=\"s10.0\" />"
       << "<tr_sizeClass sizeKey=\"s15.0\" />"
       << "<tr_sizeClass sizeKey=\"s20.0\" />"
       << "<tr_sizeClass sizeKey=\"s35.0\" />"
       << "</tr_sizeClasses>"
       << "<tr_initialDensities>"
       << "<tr_idVals whatSpecies=\"Species_1\">"
       << "<tr_initialDensity sizeClass=\"s10.0\">0.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s15.0\">15.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s35.0\">30.0</tr_initialDensity>"
       << "</tr_idVals>"
       << "<tr_idVals whatSpecies=\"Species_2\">"
       << "<tr_initialDensity sizeClass=\"s10.0\">5.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s15.0\">20.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s35.0\">35.0</tr_initialDensity>"
       << "</tr_idVals>"
       << "<tr_idVals whatSpecies=\"Species_3\">"
       << "<tr_initialDensity sizeClass=\"s10.0\">10.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s15.0\">25.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s35.0\">40.0</tr_initialDensity>"
       << "</tr_idVals>"
       << "</tr_initialDensities>";

  WriteTreePopulation2CommonFileStuff(oOut);

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteTreePopulation2XMLFile4()
/////////////////////////////////////////////////////////////////////////////
const char* WriteTreePopulation2XMLFile4()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  WriteTreePopulation2CommonPlotStuff(oOut);

  oOut << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\"/>"
       << "<tr_species speciesName=\"Species_2\"/>"
       << "<tr_species speciesName=\"Species_3\"/>"
       << "</tr_speciesList>"
       << "<tr_sizeClasses>"
       << "<tr_sizeClass sizeKey=\"Seedling\" />"
       << "<tr_sizeClass sizeKey=\"s10.0\" />"
       << "<tr_sizeClass sizeKey=\"s15.0\" />"
       << "<tr_sizeClass sizeKey=\"s20.0\" />"
       << "<tr_sizeClass sizeKey=\"s35.0\" />"
       << "</tr_sizeClasses>"
       << "<tr_initialDensities>"
       << "<tr_idVals whatSpecies=\"Species_1\">"
       << "<tr_initialDensity sizeClass=\"Seedling\">6.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s10.0\">0.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s15.0\">15.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s35.0\">30.0</tr_initialDensity>"
       << "</tr_idVals>"
       << "<tr_idVals whatSpecies=\"Species_2\">"
       << "<tr_initialDensity sizeClass=\"Seedling\">8.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s10.0\">5.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s15.0\">20.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s35.0\">35.0</tr_initialDensity>"
       << "</tr_idVals>"
       << "<tr_idVals whatSpecies=\"Species_3\">"
       << "<tr_initialDensity sizeClass=\"Seedling\">10.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s10.0\">10.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s15.0\">25.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s35.0\">40.0</tr_initialDensity>"
       << "</tr_idVals>"
       << "</tr_initialDensities>"
       << "<tr_seedlingHeightClass1>50.0</tr_seedlingHeightClass1>"
       << "<tr_seedlingHeightClass2>100.0</tr_seedlingHeightClass2>"
       << "<tr_seedlingHeight1Density>"
       << "<tr_sh1dVal species=\"Species_1\">12</tr_sh1dVal>"
       << "<tr_sh1dVal species=\"Species_2\">14</tr_sh1dVal>"
       << "<tr_sh1dVal species=\"Species_3\">16</tr_sh1dVal>"
       << "</tr_seedlingHeight1Density>"
       << "<tr_seedlingHeight2Density>"
       << "<tr_sh2dVal species=\"Species_1\">18</tr_sh2dVal>"
       << "<tr_sh2dVal species=\"Species_2\">20</tr_sh2dVal>"
       << "<tr_sh2dVal species=\"Species_3\">22</tr_sh2dVal>"
       << "</tr_seedlingHeight2Density>"
       << "<tr_seedlingHeight3Density>"
       << "<tr_sh3dVal species=\"Species_1\">24</tr_sh3dVal>"
       << "<tr_sh3dVal species=\"Species_2\">26</tr_sh3dVal>"
       << "<tr_sh3dVal species=\"Species_3\">28</tr_sh3dVal>"
       << "</tr_seedlingHeight3Density>";

  WriteTreePopulation2CommonFileStuff(oOut);

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteTreePopulation2XMLFile5()
/////////////////////////////////////////////////////////////////////////////
const char* WriteTreePopulation2XMLFile5()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  WriteTreePopulation2CommonPlotStuff(oOut);

  oOut << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\"/>"
       << "<tr_species speciesName=\"Species_2\"/>"
       << "<tr_species speciesName=\"Species_3\"/>"
       << "</tr_speciesList>"
       << "<tr_seedlingHeightClass1>50.0</tr_seedlingHeightClass1>"
       << "<tr_seedlingHeightClass2>100.0</tr_seedlingHeightClass2>"
       << "<tr_seedlingHeight1Density>"
       << "<tr_sh1dVal species=\"Species_1\">12</tr_sh1dVal>"
       << "<tr_sh1dVal species=\"Species_2\">0</tr_sh1dVal>"
       << "<tr_sh1dVal species=\"Species_3\">16</tr_sh1dVal>"
       << "</tr_seedlingHeight1Density>"
       << "<tr_seedlingHeight2Density>"
       << "<tr_sh2dVal species=\"Species_1\">0</tr_sh2dVal>"
       << "<tr_sh2dVal species=\"Species_2\">0</tr_sh2dVal>"
       << "<tr_sh2dVal species=\"Species_3\">0</tr_sh2dVal>"
       << "</tr_seedlingHeight2Density>";

  WriteTreePopulation2CommonFileStuff(oOut);

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteTreePopulation2XMLFile6()
/////////////////////////////////////////////////////////////////////////////
const char* WriteTreePopulation2XMLFile6()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  WriteTreePopulation2CommonPlotStuff(oOut);

  oOut << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\"/>"
       << "<tr_species speciesName=\"Species_2\"/>"
       << "<tr_species speciesName=\"Species_3\"/>"
       << "</tr_speciesList>"
       << "<tr_sizeClasses>"
       << "<tr_sizeClass sizeKey=\"Seedling\" />"
       << "<tr_sizeClass sizeKey=\"s10.0\" />"
       << "<tr_sizeClass sizeKey=\"s15.0\" />"
       << "<tr_sizeClass sizeKey=\"s20.0\" />"
       << "<tr_sizeClass sizeKey=\"s35.0\" />"
       << "</tr_sizeClasses>"
       << "<tr_initialDensities>"
       << "<tr_idVals whatSpecies=\"Species_1\">"
       << "<tr_initialDensity sizeClass=\"Seedling\">0.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s10.0\">0.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s15.0\">0.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s35.0\">0.0</tr_initialDensity>"
       << "</tr_idVals>"
       << "<tr_idVals whatSpecies=\"Species_2\">"
       << "<tr_initialDensity sizeClass=\"Seedling\">0.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s10.0\">0.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s15.0\">0.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s35.0\">0.0</tr_initialDensity>"
       << "</tr_idVals>"
       << "<tr_idVals whatSpecies=\"Species_3\">"
       << "<tr_initialDensity sizeClass=\"Seedling\">0.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s10.0\">0.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s15.0\">0.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s35.0\">0.0</tr_initialDensity>"
       << "</tr_idVals>"
       << "</tr_initialDensities>"
       << "<tr_seedlingHeightClass1>50.0</tr_seedlingHeightClass1>"
       << "<tr_seedlingHeightClass2>100.0</tr_seedlingHeightClass2>"
       << "<tr_seedlingHeight2Density>"
       << "<tr_sh2dVal species=\"Species_1\">0</tr_sh2dVal>"
       << "<tr_sh2dVal species=\"Species_2\">20</tr_sh2dVal>"
       << "<tr_sh2dVal species=\"Species_3\">22</tr_sh2dVal>"
       << "</tr_seedlingHeight2Density>";

  WriteTreePopulation2CommonFileStuff(oOut);

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteTreePopulation2XMLFile7()
/////////////////////////////////////////////////////////////////////////////
const char* WriteTreePopulation2XMLFile7()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  WriteTreePopulation2CommonPlotStuff(oOut);

  oOut << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\"/>"
       << "<tr_species speciesName=\"Species_2\"/>"
       << "<tr_species speciesName=\"Species_3\"/>"
       << "</tr_speciesList>"
       << "<tr_seedlingHeightClass1>50.0</tr_seedlingHeightClass1>"
       << "<tr_seedlingHeightClass2>100.0</tr_seedlingHeightClass2>"
       << "<tr_seedlingHeight3Density>"
       << "<tr_sh3dVal species=\"Species_1\">24</tr_sh3dVal>"
       << "<tr_sh3dVal species=\"Species_2\">26</tr_sh3dVal>"
       << "<tr_sh3dVal species=\"Species_3\">0</tr_sh3dVal>"
       << "</tr_seedlingHeight3Density>";

  WriteTreePopulation2CommonFileStuff(oOut);

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteTreePopulation2XMLFile8()
/////////////////////////////////////////////////////////////////////////////
const char* WriteTreePopulation2XMLFile8()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  WriteTreePopulation2CommonPlotStuff(oOut);

  oOut << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\"/>"
       << "<tr_species speciesName=\"Species_2\"/>"
       << "<tr_species speciesName=\"Species_3\"/>"
       << "</tr_speciesList>"
       << "<tr_sizeClasses>"
       << "<tr_sizeClass sizeKey=\"Seedling\" />"
       << "<tr_sizeClass sizeKey=\"s10.0\" />"
       << "<tr_sizeClass sizeKey=\"s15.0\" />"
       << "<tr_sizeClass sizeKey=\"s20.0\" />"
       << "<tr_sizeClass sizeKey=\"s35.0\" />"
       << "</tr_sizeClasses>"
       << "<tr_initialDensities>"
       << "<tr_idVals whatSpecies=\"Species_1\">"
       << "<tr_initialDensity sizeClass=\"Seedling\">6.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s10.0\">0.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s15.0\">15.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s35.0\">30.0</tr_initialDensity>"
       << "</tr_idVals>"
       << "<tr_idVals whatSpecies=\"Species_2\">"
       << "<tr_initialDensity sizeClass=\"Seedling\">8.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s10.0\">5.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s15.0\">20.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s35.0\">35.0</tr_initialDensity>"
       << "</tr_idVals>"
       << "<tr_idVals whatSpecies=\"Species_3\">"
       << "<tr_initialDensity sizeClass=\"Seedling\">10.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s10.0\">10.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s15.0\">25.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s35.0\">40.0</tr_initialDensity>"
       << "</tr_idVals>"
       << "</tr_initialDensities>";

  WriteTreePopulation2CommonFileStuff(oOut);

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteTreePopulation2XMLFile9()
/////////////////////////////////////////////////////////////////////////////
const char* WriteTreePopulation2XMLFile9()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  WriteTreePopulation2CommonPlotStuff(oOut);

  oOut << "<trees>"
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
       << "<tm_treeSettings sp=\"Species_1\" tp=\"2\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "<tm_floatCode label=\"Height\">3</tm_floatCode>"
       << "<tm_floatCode label=\"Diam10\">4</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_1\" tp=\"3\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "<tm_floatCode label=\"Height\">3</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_2\" tp=\"2\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "<tm_floatCode label=\"Height\">3</tm_floatCode>"
       << "<tm_floatCode label=\"Diam10\">4</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_2\" tp=\"3\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "<tm_floatCode label=\"Height\">3</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tree sp=\"0\" tp=\"3\">"
       << "<fl c=\"0\">7.479825586</fl>" //X
       << "<fl c=\"1\">115.7228207</fl>" //Y
       << "<fl c=\"2\">11.4</fl>" //DBH
       << "<fl c=\"3\">5.42</fl>" //Height
       << "</tree>"
       << "<tree sp=\"0\" tp=\"3\">"
       << "<fl c=\"0\">7.479825586</fl>" //X
       << "<fl c=\"1\">117.9567383</fl>" //Y
       << "<fl c=\"2\">11.4</fl>" //DBH
       << "<fl c=\"3\">5.42</fl>" //Height
       << "</tree>"
       << "<tree sp=\"0\" tp=\"3\">"
       << "<fl c=\"0\">12.03691733</fl>" //X
       << "<fl c=\"1\">114.1195824</fl>" //Y
       << "<fl c=\"2\">44</fl>" //DBH
       << "<fl c=\"3\">15.56</fl>" //Height
       << "</tree>"
       << "<tree sp=\"0\" tp=\"3\">"
       << "<fl c=\"0\">12.03691733</fl>" //X
       << "<fl c=\"1\">119.5599766</fl>" //Y
       << "<fl c=\"2\">44</fl>" //DBH
       << "<fl c=\"3\">15.56</fl>" //Height
       << "</tree>"
       << "<tree sp=\"0\" tp=\"3\">"
       << "<fl c=\"0\">9.83690691</fl>" //X
       << "<fl c=\"1\">113.2771304</fl>" //Y
       << "<fl c=\"2\">11.3</fl>" //DBH
       << "<fl c=\"3\">8.01</fl>" //Height
       << "</tree>"
       << "<tree sp=\"0\" tp=\"2\">"
       << "<fl c=\"0\">10.94454598</fl>" //X
       << "<fl c=\"1\">114.1526108</fl>" //Y
       << "<fl c=\"2\">7</fl>" //DBH
       << "<fl c=\"3\">9.9</fl>" //Height
       << "</tree>"
       << "<tree sp=\"0\" tp=\"2\">"
       << "<fl c=\"0\">13.91744238</fl>" //X
       << "<fl c=\"1\">115.090028</fl>" //Y
       << "<fl c=\"2\">8.5</fl>" //DBH
       << "<fl c=\"3\">12.86</fl>" //Height
       << "</tree>"
       << "<tree sp=\"0\" tp=\"3\">"
       << "<fl c=\"0\">10.39379609</fl>" //X
       << "<fl c=\"1\">115.6548967</fl>" //Y
       << "<fl c=\"2\">17</fl>" //DBH
       << "<fl c=\"3\">15.29</fl>" //Height
       << "</tree>"
       << "<tree sp=\"0\" tp=\"3\">"
       << "<fl c=\"0\">10.39379609</fl>" //X
       << "<fl c=\"1\">118.0246623</fl>" //Y
       << "<fl c=\"2\">17</fl>" //DBH
       << "<fl c=\"3\">15.29</fl>" //Height
       << "</tree>"
       << "<tree sp=\"1\" tp=\"2\">"
       << "<fl c=\"0\">13.91744238</fl>" //X
       << "<fl c=\"1\">118.589531</fl>" //Y
       << "<fl c=\"2\">8.5</fl>" //DBH
       << "<fl c=\"3\">12.86</fl>" //Height
       << "</tree>"
       << "<tree sp=\"1\" tp=\"2\">"
       << "<fl c=\"0\">10.94454598</fl>" //X
       << "<fl c=\"1\">119.5269482</fl>" //Y
       << "<fl c=\"2\">7</fl>" //DBH
       << "<fl c=\"3\">9.9</fl>" //Height
       << "</tree>"
       << "</tr_treemap>"
       << "</trees>"
       << "<allometry>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"Species_1\">21.27298</tr_chVal>"
       << "<tr_chVal species=\"Species_2\">26.46132</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_2\">0.0549</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"Species_1\">0.9</tr_screVal>"
       << "<tr_screVal species=\"Species_2\">0.9</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">0.75</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">0.75</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.5929285</tr_sachVal>"
       << "<tr_sachVal species=\"Species_2\">0.3759975</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"Species_1\">1</tr_scheVal>"
       << "<tr_scheVal species=\"Species_2\">1</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_2\">0.03418</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
        << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.06143158</tr_soahVal>"
       << "<tr_soahVal species=\"Species_2\">0.04575488</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
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
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>ConstantGLI</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Snag\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<ConstantGLI1>"
       << "<li_constGLI>100</li_constGLI>"
       << "</ConstantGLI1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteTreePopulation2XMLFile10()
/////////////////////////////////////////////////////////////////////////////
const char* WriteTreePopulation2XMLFile10()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  WriteTreePopulation2CommonPlotStuff(oOut);

  oOut << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\"/>"
       << "</tr_speciesList>"
       << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
       << "<tr_minAdultDBH>"
       << "<tr_madVal species=\"Species_1\">10</tr_madVal>"
       << "</tr_minAdultDBH>"
       << "<tr_maxSeedlingHeight>"
       << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
       << "</tr_maxSeedlingHeight>"
       << "<tr_treemapFile>" << WriteTreePopulation2TextTreeMap() << "</tr_treemapFile>"
       << "</trees>"
       << "<allometry>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"Species_1\">0.9</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"Species_1\">1</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
       << "<tr_whatSeedlingHeightDiam>"
       << "<tr_wsehdVal species=\"Species_1\">0</tr_wsehdVal>"
       << "</tr_whatSeedlingHeightDiam>"
       << "<tr_whatSaplingHeightDiam>"
       << "<tr_wsahdVal species=\"Species_1\">0</tr_wsahdVal>"
       << "</tr_whatSaplingHeightDiam>"
       << "<tr_whatAdultHeightDiam>"
       << "<tr_wahdVal species=\"Species_1\">0</tr_wahdVal>"
       << "</tr_whatAdultHeightDiam>"
       << "<tr_whatAdultCrownRadDiam>"
       << "<tr_wacrdVal species=\"Species_1\">0</tr_wacrdVal>"
       << "</tr_whatAdultCrownRadDiam>"
       << "<tr_whatAdultCrownHeightHeight>"
       << "<tr_wachhVal species=\"Species_1\">0</tr_wachhVal>"
       << "</tr_whatAdultCrownHeightHeight>"
       << "<tr_whatSaplingCrownRadDiam>"
       << "<tr_wscrdVal species=\"Species_1\">0</tr_wscrdVal>"
       << "</tr_whatSaplingCrownRadDiam>"
       << "<tr_whatSaplingCrownHeightHeight>"
       << "<tr_wschhVal species=\"Species_1\">0</tr_wschhVal>"
       << "</tr_whatSaplingCrownHeightHeight>"
       << "</allometry>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>ConstantGLI</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Snag\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<ConstantGLI1>"
       << "<li_constGLI>100</li_constGLI>"
       << "</ConstantGLI1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteTreePopulation2XMLFile11()
/////////////////////////////////////////////////////////////////////////////
const char* WriteTreePopulation2XMLFile11()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  WriteTreePopulation2CommonPlotStuff(oOut);

  oOut << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\"/>"
       << "<tr_species speciesName=\"Species_2\"/>"
       << "<tr_species speciesName=\"Species_3\"/>"
       << "<tr_species speciesName=\"Species_4\"/>"
       << "</tr_speciesList>"
       << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
       << "<tr_minAdultDBH>"
       << "<tr_madVal species=\"Species_1\">10</tr_madVal>"
       << "<tr_madVal species=\"Species_2\">10</tr_madVal>"
       << "<tr_madVal species=\"Species_3\">10</tr_madVal>"
       << "<tr_madVal species=\"Species_4\">10</tr_madVal>"
       << "</tr_minAdultDBH>"
       << "<tr_maxSeedlingHeight>"
       << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_2\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_3\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_4\">1.35</tr_mshVal>"
       << "</tr_maxSeedlingHeight>"
       << "<tr_treemapFile>" << WriteTreePopulation2TextTreeMap2() << "</tr_treemapFile>"
       << "</trees>"
       << "<allometry>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_2\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_3\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_4\">39.48</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_2\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_3\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_4\">0.0549</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"Species_1\">0.9</tr_screVal>"
       << "<tr_screVal species=\"Species_2\">0.9</tr_screVal>"
       << "<tr_screVal species=\"Species_3\">0.9</tr_screVal>"
       << "<tr_screVal species=\"Species_4\">0.9</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_3\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_4\">0.8008</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_3\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_4\">0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_2\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_3\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_4\">0.389</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"Species_1\">1</tr_scheVal>"
       << "<tr_scheVal species=\"Species_2\">1</tr_scheVal>"
       << "<tr_scheVal species=\"Species_3\">1</tr_scheVal>"
       << "<tr_scheVal species=\"Species_4\">1</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_2\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_3\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_4\">0.03418</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_2\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_3\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_4\">0.0299</tr_soahVal>"
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
       << "<behaviorName>ConstantGLI</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Snag\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Snag\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Snag\"/>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Snag\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seedling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>AbsUnlimGrowth</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>QualityVigorClassifier</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<ConstantGLI1>"
       << "<li_constGLI>100</li_constGLI>"
       << "</ConstantGLI1>"
       << "<AbsUnlimGrowth2>"
       << "<gr_asympDiameterGrowth>"
       << "<gr_adgVal species=\"Species_1\">0.858</gr_adgVal>"
       << "<gr_adgVal species=\"Species_2\">0.858</gr_adgVal>"
       << "<gr_adgVal species=\"Species_3\">0.911</gr_adgVal>"
       << "<gr_adgVal species=\"Species_4\">0.911</gr_adgVal>"
       << "</gr_asympDiameterGrowth>"
       << "<gr_slopeGrowthResponse>"
       << "<gr_sgrVal species=\"Species_1\">0.027</gr_sgrVal>"
       << "<gr_sgrVal species=\"Species_2\">0.027</gr_sgrVal>"
       << "<gr_sgrVal species=\"Species_3\">0.01</gr_sgrVal>"
       << "<gr_sgrVal species=\"Species_4\">0.01</gr_sgrVal>"
       << "</gr_slopeGrowthResponse>"
       << "<gr_lengthLastSuppFactor>"
       << "<gr_llsfVal species=\"Species_1\">0.0</gr_llsfVal>"
       << "<gr_llsfVal species=\"Species_2\">0.0</gr_llsfVal>"
       << "<gr_llsfVal species=\"Species_3\">0.0</gr_llsfVal>"
       << "<gr_llsfVal species=\"Species_4\">0.0</gr_llsfVal>"
       << "</gr_lengthLastSuppFactor>"
       << "<gr_lengthCurrReleaseFactor>"
       << "<gr_lcrfVal species=\"Species_1\">0.0</gr_lcrfVal>"
       << "<gr_lcrfVal species=\"Species_2\">0.0</gr_lcrfVal>"
       << "<gr_lcrfVal species=\"Species_3\">0.016</gr_lcrfVal>"
       << "<gr_lcrfVal species=\"Species_4\">0.016</gr_lcrfVal>"
       << "</gr_lengthCurrReleaseFactor>"
       << "<gr_yrsExceedThresholdBeforeSupp>6</gr_yrsExceedThresholdBeforeSupp>"
       << "<gr_mortRateAtSuppression>0.1</gr_mortRateAtSuppression>"
       << "<mo_mortAtZeroGrowth>"
       << "<mo_mazgVal species=\"Species_1\">0.01</mo_mazgVal>"
       << "<mo_mazgVal species=\"Species_2\">0.01</mo_mazgVal>"
       << "<mo_mazgVal species=\"Species_3\">0.01</mo_mazgVal>"
       << "<mo_mazgVal species=\"Species_4\">0.01</mo_mazgVal>"
       << "</mo_mortAtZeroGrowth>"
       << "<mo_lightDependentMortality>"
       << "<mo_ldmVal species=\"Species_1\">0.1</mo_ldmVal>"
       << "<mo_ldmVal species=\"Species_2\">0.1</mo_ldmVal>"
       << "<mo_ldmVal species=\"Species_3\">0.1</mo_ldmVal>"
       << "<mo_ldmVal species=\"Species_4\">0.1</mo_ldmVal>"
       << "</mo_lightDependentMortality>"
       << "</AbsUnlimGrowth2>";

  oOut << "<QualityVigorClassifier3>"
       << "<ma_classifierVigBeta0>"
       << "<ma_cvb0Val species=\"Species_2\">0.1</ma_cvb0Val>"
       << "<ma_cvb0Val species=\"Species_4\">0.3</ma_cvb0Val>"
       << "</ma_classifierVigBeta0>"
       << "<ma_classifierVigBeta11>"
       << "<ma_cvb11Val species=\"Species_2\">0.2</ma_cvb11Val>"
       << "<ma_cvb11Val species=\"Species_4\">0.1</ma_cvb11Val>"
       << "</ma_classifierVigBeta11>"
       << "<ma_classifierVigBeta12>"
       << "<ma_cvb12Val species=\"Species_2\">-2.3</ma_cvb12Val>"
       << "<ma_cvb12Val species=\"Species_4\">0.32</ma_cvb12Val>"
       << "</ma_classifierVigBeta12>"
       << "<ma_classifierVigBeta13>"
       << "<ma_cvb13Val species=\"Species_2\">0.13</ma_cvb13Val>"
       << "<ma_cvb13Val species=\"Species_4\">-0.2</ma_cvb13Val>"
       << "</ma_classifierVigBeta13>"
       << "<ma_classifierVigBeta14>"
       << "<ma_cvb14Val species=\"Species_2\">0.9</ma_cvb14Val>"
       << "<ma_cvb14Val species=\"Species_4\">-1</ma_cvb14Val>"
       << "</ma_classifierVigBeta14>"
       << "<ma_classifierVigBeta15>"
       << "<ma_cvb15Val species=\"Species_2\">1</ma_cvb15Val>"
       << "<ma_cvb15Val species=\"Species_4\">1</ma_cvb15Val>"
       << "</ma_classifierVigBeta15>"
       << "<ma_classifierVigBeta16>"
       << "<ma_cvb16Val species=\"Species_2\">1</ma_cvb16Val>"
       << "<ma_cvb16Val species=\"Species_4\">0</ma_cvb16Val>"
       << "</ma_classifierVigBeta16>"
       << "<ma_classifierVigBeta2>"
       << "<ma_cvb2Val species=\"Species_2\">0.01</ma_cvb2Val>"
       << "<ma_cvb2Val species=\"Species_4\">0.04</ma_cvb2Val>"
       << "</ma_classifierVigBeta2>"
       << "<ma_classifierVigBeta3>"
       << "<ma_cvb3Val species=\"Species_2\">0.001</ma_cvb3Val>"
       << "<ma_cvb3Val species=\"Species_4\">0.3</ma_cvb3Val>"
       << "</ma_classifierVigBeta3>"
       << "<ma_classifierQualBeta0>"
       << "<ma_cqb0Val species=\"Species_2\">0.25</ma_cqb0Val>"
       << "<ma_cqb0Val species=\"Species_4\">0</ma_cqb0Val>"
       << "</ma_classifierQualBeta0>"
       << "<ma_classifierQualBeta11>"
       << "<ma_cqb11Val species=\"Species_2\">0.36</ma_cqb11Val>"
       << "<ma_cqb11Val species=\"Species_4\">0.4</ma_cqb11Val>"
       << "</ma_classifierQualBeta11>"
       << "<ma_classifierQualBeta12>"
       << "<ma_cqb12Val species=\"Species_2\">0.02</ma_cqb12Val>"
       << "<ma_cqb12Val species=\"Species_4\">0.3</ma_cqb12Val>"
       << "</ma_classifierQualBeta12>"
       << "<ma_classifierQualBeta13>"
       << "<ma_cqb13Val species=\"Species_2\">0.2</ma_cqb13Val>"
       << "<ma_cqb13Val species=\"Species_4\">-0.3</ma_cqb13Val>"
       << "</ma_classifierQualBeta13>"
       << "<ma_classifierQualBeta14>"
       << "<ma_cqb14Val species=\"Species_2\">-0.2</ma_cqb14Val>"
       << "<ma_cqb14Val species=\"Species_4\">-0.4</ma_cqb14Val>"
       << "</ma_classifierQualBeta14>"
       << "<ma_classifierQualBeta2>"
       << "<ma_cqb2Val species=\"Species_2\">-0.2</ma_cqb2Val>"
       << "<ma_cqb2Val species=\"Species_4\">0</ma_cqb2Val>"
       << "</ma_classifierQualBeta2>"
       << "<ma_classifierQualBeta3>"
       << "<ma_cqb3Val species=\"Species_2\">1</ma_cqb3Val>"
       << "<ma_cqb3Val species=\"Species_4\">0.1</ma_cqb3Val>"
       << "</ma_classifierQualBeta3>"
       << "<ma_classifierNewAdultProbVigorous>"
       << "<ma_cnapvVal species=\"Species_2\">0.1</ma_cnapvVal>"
       << "<ma_cnapvVal species=\"Species_4\">0.5</ma_cnapvVal>"
       << "</ma_classifierNewAdultProbVigorous>"
       << "<ma_classifierNewAdultProbSawlog>"
       << "<ma_cnapsVal species=\"Species_2\">0.9</ma_cnapsVal>"
       << "<ma_cnapsVal species=\"Species_4\">0.3</ma_cnapsVal>"
       << "</ma_classifierNewAdultProbSawlog>"
       << "<ma_classifierDeciduous>"
       << "<ma_cdVal species=\"Species_2\">1</ma_cdVal>"
       << "<ma_cdVal species=\"Species_4\">1</ma_cdVal>"
       << "</ma_classifierDeciduous>"
       << "</QualityVigorClassifier3>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteTreePopulation2XMLErrorFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteTreePopulation2XMLErrorFile1()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  WriteTreePopulation2CommonPlotStuff(oOut);

  oOut << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\"/>"
       << "<tr_species speciesName=\"Species_2\"/>"
       << "<tr_species speciesName=\"Species_3\"/>"
       << "</tr_speciesList>"
       << "<tr_sizeClasses>"
       << "<tr_sizeClass sizeKey=\"s10.0\" />"
       << "<tr_sizeClass sizeKey=\"s15.0\" />"
       << "<tr_sizeClass sizeKey=\"s20.0\" />"
       << "<tr_sizeClass sizeKey=\"s35.0\" />"
       << "</tr_sizeClasses>"
       << "<tr_initialDensities>"
       << "<tr_idVals whatSpecies=\"Species_1\">"
       << "<tr_initialDensity sizeClass=\"s10.0\">0.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s15.0\">-15.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s35.0\">20.0</tr_initialDensity>"
       << "</tr_idVals>"
       << "<tr_idVals whatSpecies=\"Species_2\">"
       << "<tr_initialDensity sizeClass=\"s10.0\">5.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s15.0\">20.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s35.0\">35.0</tr_initialDensity>"
       << "</tr_idVals>"
       << "<tr_idVals whatSpecies=\"Species_3\">"
       << "<tr_initialDensity sizeClass=\"s10.0\">10.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s15.0\">25.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s35.0\">40.0</tr_initialDensity>"
       << "</tr_idVals>"
       << "</tr_initialDensities>";

  WriteTreePopulation2CommonFileStuff(oOut);

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteTreePopulation2XMLErrorFile2()
/////////////////////////////////////////////////////////////////////////////
const char* WriteTreePopulation2XMLErrorFile2()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  WriteTreePopulation2CommonPlotStuff(oOut);

  oOut << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\"/>"
       << "<tr_species speciesName=\"Species_2\"/>"
       << "<tr_species speciesName=\"Species_3\"/>"
       << "</tr_speciesList>"
       << "<tr_sizeClasses>"
       << "<tr_sizeClass sizeKey=\"s10.0\" />"
       << "<tr_sizeClass sizeKey=\"s15.0\" />"
       << "<tr_sizeClass sizeKey=\"s20.0\" />"
       << "<tr_sizeClass sizeKey=\"s35.0\" />"
       << "</tr_sizeClasses>"
       << "<tr_initialDensities>"
       << "<tr_idVals whatSpecies=\"Species_1\">"
       << "<tr_initialDensity sizeClass=\"s10.0\">0.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s15.0\">15.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s35.0\">20.0</tr_initialDensity>"
       << "</tr_idVals>"
       << "<tr_idVals whatSpecies=\"Species_2\">"
       << "<tr_initialDensity sizeClass=\"s10.0\">5.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s15.0\">20.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s35.0\">35.0</tr_initialDensity>"
       << "</tr_idVals>"
       << "<tr_idVals whatSpecies=\"Species_3\">"
       << "<tr_initialDensity sizeClass=\"s10.0\">ten</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s15.0\">25.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s35.0\">40.0</tr_initialDensity>"
       << "</tr_idVals>"
       << "</tr_initialDensities>";

  WriteTreePopulation2CommonFileStuff(oOut);

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteTreePopulation2XMLErrorFile3()
/////////////////////////////////////////////////////////////////////////////
const char* WriteTreePopulation2XMLErrorFile3()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  WriteTreePopulation2CommonPlotStuff(oOut);

  oOut << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\"/>"
       << "<tr_species speciesName=\"Species_2\"/>"
       << "<tr_species speciesName=\"Species_3\"/>"
       << "</tr_speciesList>"
       << "<tr_initialDensities>"
       << "<tr_idVals whatSpecies=\"Species_1\">"
       << "<tr_initialDensity sizeClass=\"s10.0\">0.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s15.0\">15.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s35.0\">20.0</tr_initialDensity>"
       << "</tr_idVals>"
       << "<tr_idVals whatSpecies=\"Species_2\">"
       << "<tr_initialDensity sizeClass=\"s10.0\">5.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s15.0\">20.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s35.0\">35.0</tr_initialDensity>"
       << "</tr_idVals>"
       << "<tr_idVals whatSpecies=\"Species_3\">"
       << "<tr_initialDensity sizeClass=\"s10.0\">10.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s15.0\">25.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s35.0\">40.0</tr_initialDensity>"
       << "</tr_idVals>"
       << "</tr_initialDensities>";

  WriteTreePopulation2CommonFileStuff(oOut);

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteTreePopulation2XMLErrorFile4()
/////////////////////////////////////////////////////////////////////////////
const char* WriteTreePopulation2XMLErrorFile4()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  WriteTreePopulation2CommonPlotStuff(oOut);

  oOut << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\"/>"
       << "<tr_species speciesName=\"Species_2\"/>"
       << "<tr_species speciesName=\"Species_3\"/>"
       << "</tr_speciesList>"
       << "<tr_sizeClasses>"
       << "<tr_sizeClass sizeKey=\"s10.0\" />"
       << "<tr_sizeClass sizeKey=\"s15.0\" />"
       << "<tr_sizeClass sizeKey=\"s20.0\" />"
       << "<tr_sizeClass sizeKey=\"s35.0\" />"
       << "</tr_sizeClasses>"
       << "<tr_initialDensities>"
       << "<tr_idVals whatSpecies=\"Species_4\">"
       << "<tr_initialDensity sizeClass=\"s10.0\">0.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s15.0\">15.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s35.0\">20.0</tr_initialDensity>"
       << "</tr_idVals>"
       << "<tr_idVals whatSpecies=\"Species_2\">"
       << "<tr_initialDensity sizeClass=\"s10.0\">5.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s15.0\">20.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s35.0\">35.0</tr_initialDensity>"
       << "</tr_idVals>"
       << "<tr_idVals whatSpecies=\"Species_3\">"
       << "<tr_initialDensity sizeClass=\"s10.0\">10.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s15.0\">25.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s35.0\">40.0</tr_initialDensity>"
       << "</tr_idVals>"
       << "</tr_initialDensities>";

  WriteTreePopulation2CommonFileStuff(oOut);

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteTreePopulation2XMLErrorFile5()
/////////////////////////////////////////////////////////////////////////////
const char* WriteTreePopulation2XMLErrorFile5()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  WriteTreePopulation2CommonPlotStuff(oOut);

  oOut << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\"/>"
       << "<tr_species speciesName=\"Species_2\"/>"
       << "<tr_species speciesName=\"Species_3\"/>"
       << "</tr_speciesList>"
       << "<tr_sizeClasses>"
       << "<tr_sizeClass sizeKey=\"s10.0\" />"
       << "<tr_sizeClass sizeKey=\"s15.0\" />"
       << "<tr_sizeClass sizeKey=\"s20.0\" />"
       << "<tr_sizeClass sizeKey=\"s35.0\" />"
       << "</tr_sizeClasses>"
       << "<tr_initialDensities>"
       << "<tr_idVals whatSpecies=\"Species_1\">"
       << "<tr_initialDensity sizeClass=\"s10.0\">0.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s15.0\">15.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s65.0\">20.0</tr_initialDensity>"
       << "</tr_idVals>"
       << "<tr_idVals whatSpecies=\"Species_2\">"
       << "<tr_initialDensity sizeClass=\"s10.0\">5.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s15.0\">20.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s35.0\">35.0</tr_initialDensity>"
       << "</tr_idVals>"
       << "<tr_idVals whatSpecies=\"Species_3\">"
       << "<tr_initialDensity sizeClass=\"s10.0\">10.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s15.0\">25.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s35.0\">40.0</tr_initialDensity>"
       << "</tr_idVals>"
       << "</tr_initialDensities>";

  WriteTreePopulation2CommonFileStuff(oOut);

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteTreePopulation2XMLErrorFile6()
/////////////////////////////////////////////////////////////////////////////
const char* WriteTreePopulation2XMLErrorFile6()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  WriteTreePopulation2CommonPlotStuff(oOut);

  oOut << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\"/>"
       << "<tr_species speciesName=\"Species_2\"/>"
       << "<tr_species speciesName=\"Species_3\"/>"
       << "</tr_speciesList>"
       << "<tr_sizeClasses>"
       << "<tr_sizeClass sizeKey=\"s10.0\" />"
       << "<tr_sizeClass sizeKey=\"s15.0\" />"
       << "<tr_sizeClass sizeKey=\"s20.0\" />"
       << "<tr_sizeClass sizeKey=\"s35.0\" />"
       << "</tr_sizeClasses>"
       << "<tr_initialDensities>"
       << "<tr_idVals whatSpecies=\"Species_1\">"
       << "<tr_initialDensity sizeClass=\"s10.0\">0.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s15.0\">15.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s35.0\">20.0</tr_initialDensity>"
       << "</tr_idVals>"
       << "<tr_idVals whatSpecies=\"Species_2\">"
       << "<tr_initialDensity sizeClass=\"s10.0\">5.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s15.0\">20.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s35.0\">35.0</tr_initialDensity>"
       << "</tr_idVals>"
       << "<tr_idVals whatSpecies=\"Species_3\">"
       << "<tr_initialDensity sizeClass=\"sds\">10.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s15.0\">25.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s35.0\">40.0</tr_initialDensity>"
       << "</tr_idVals>"
       << "</tr_initialDensities>";

  WriteTreePopulation2CommonFileStuff(oOut);

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteTreePopulation2XMLErrorFile7()
/////////////////////////////////////////////////////////////////////////////
const char* WriteTreePopulation2XMLErrorFile7()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  WriteTreePopulation2CommonPlotStuff(oOut);

  oOut << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\"/>"
       << "<tr_species speciesName=\"Species_2\"/>"
       << "<tr_species speciesName=\"Species_3\"/>"
       << "</tr_speciesList>"
       << "<tr_sizeClasses>"
       << "<tr_sizeClass sizeKey=\"Seedling\" />"
       << "<tr_sizeClass sizeKey=\"s10.0\" />"
       << "<tr_sizeClass sizeKey=\"s15.0\" />"
       << "<tr_sizeClass sizeKey=\"s20.0\" />"
       << "<tr_sizeClass sizeKey=\"s35.0\" />"
       << "</tr_sizeClasses>"
       << "<tr_initialDensities>"
       << "<tr_idVals whatSpecies=\"Species_1\">"
       << "<tr_initialDensity sizeClass=\"Seedling\">6.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s10.0\">0.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s15.0\">15.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s35.0\">20.0</tr_initialDensity>"
       << "</tr_idVals>"
       << "<tr_idVals whatSpecies=\"Species_2\">"
       << "<tr_initialDensity sizeClass=\"Seedling\">8.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s10.0\">5.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s15.0\">20.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s35.0\">35.0</tr_initialDensity>"
       << "</tr_idVals>"
       << "<tr_idVals whatSpecies=\"Species_3\">"
       << "<tr_initialDensity sizeClass=\"Seedling\">10.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s10.0\">10.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s15.0\">25.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s35.0\">40.0</tr_initialDensity>"
       << "</tr_idVals>"
       << "</tr_initialDensities>"
       << "<tr_seedlingHeightClass1>220.0</tr_seedlingHeightClass1>"
       << "<tr_seedlingHeightClass2>100.0</tr_seedlingHeightClass2>"
       << "<tr_seedlingHeight1Density>"
       << "<tr_sh1dVal species=\"Species_1\">12</tr_sh1dVal>"
       << "<tr_sh1dVal species=\"Species_2\">14</tr_sh1dVal>"
       << "<tr_sh1dVal species=\"Species_3\">16</tr_sh1dVal>"
       << "</tr_seedlingHeight1Density>"
       << "<tr_seedlingHeight2Density>"
       << "<tr_sh2dVal species=\"Species_1\">18</tr_sh2dVal>"
       << "<tr_sh2dVal species=\"Species_2\">20</tr_sh2dVal>"
       << "<tr_sh2dVal species=\"Species_3\">22</tr_sh2dVal>"
       << "</tr_seedlingHeight2Density>"
       << "<tr_seedlingHeight3Density>"
       << "<tr_sh3dVal species=\"Species_1\">24</tr_sh3dVal>"
       << "<tr_sh3dVal species=\"Species_2\">26</tr_sh3dVal>"
       << "<tr_sh3dVal species=\"Species_3\">28</tr_sh3dVal>"
       << "</tr_seedlingHeight3Density>";

  WriteTreePopulation2CommonFileStuff(oOut);

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteTreePopulation2XMLErrorFile8()
/////////////////////////////////////////////////////////////////////////////
const char* WriteTreePopulation2XMLErrorFile8()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  WriteTreePopulation2CommonPlotStuff(oOut);

  oOut << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\"/>"
       << "<tr_species speciesName=\"Species_2\"/>"
       << "<tr_species speciesName=\"Species_3\"/>"
       << "</tr_speciesList>"
       << "<tr_sizeClasses>"
       << "<tr_sizeClass sizeKey=\"Seedling\" />"
       << "<tr_sizeClass sizeKey=\"s10.0\" />"
       << "<tr_sizeClass sizeKey=\"s15.0\" />"
       << "<tr_sizeClass sizeKey=\"s20.0\" />"
       << "<tr_sizeClass sizeKey=\"s35.0\" />"
       << "</tr_sizeClasses>"
       << "<tr_initialDensities>"
       << "<tr_idVals whatSpecies=\"Species_1\">"
       << "<tr_initialDensity sizeClass=\"Seedling\">6.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s10.0\">0.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s15.0\">15.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s35.0\">20.0</tr_initialDensity>"
       << "</tr_idVals>"
       << "<tr_idVals whatSpecies=\"Species_2\">"
       << "<tr_initialDensity sizeClass=\"Seedling\">8.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s10.0\">5.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s15.0\">20.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s35.0\">35.0</tr_initialDensity>"
       << "</tr_idVals>"
       << "<tr_idVals whatSpecies=\"Species_3\">"
       << "<tr_initialDensity sizeClass=\"Seedling\">10.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s10.0\">10.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s15.0\">25.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s35.0\">40.0</tr_initialDensity>"
       << "</tr_idVals>"
       << "</tr_initialDensities>"
       << "<tr_seedlingHeightClass1>120.0</tr_seedlingHeightClass1>"
       << "<tr_seedlingHeightClass2>100.0</tr_seedlingHeightClass2>"
       << "<tr_seedlingHeight1Density>"
       << "<tr_sh1dVal species=\"Species_1\">12</tr_sh1dVal>"
       << "<tr_sh1dVal species=\"Species_2\">14</tr_sh1dVal>"
       << "<tr_sh1dVal species=\"Species_3\">16</tr_sh1dVal>"
       << "</tr_seedlingHeight1Density>"
       << "<tr_seedlingHeight2Density>"
       << "<tr_sh2dVal species=\"Species_1\">18</tr_sh2dVal>"
       << "<tr_sh2dVal species=\"Species_2\">20</tr_sh2dVal>"
       << "<tr_sh2dVal species=\"Species_3\">22</tr_sh2dVal>"
       << "</tr_seedlingHeight2Density>"
       << "<tr_seedlingHeight3Density>"
       << "<tr_sh3dVal species=\"Species_1\">24</tr_sh3dVal>"
       << "<tr_sh3dVal species=\"Species_2\">26</tr_sh3dVal>"
       << "<tr_sh3dVal species=\"Species_3\">28</tr_sh3dVal>"
       << "</tr_seedlingHeight3Density>";

  WriteTreePopulation2CommonFileStuff(oOut);

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteTreePopulation2CommonPlotStuff()
/////////////////////////////////////////////////////////////////////////////
void WriteTreePopulation2CommonPlotStuff( std::fstream &oOut )
{
  using namespace std;
  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
         << "<paramFile fileCode=\"06010101\">"
         << "<plot>"
         << "<timesteps>1</timesteps>"
         << "<yearsPerTimestep>1</yearsPerTimestep>"
         << "<randomSeed>1</randomSeed>"
         << "<plot_lenX>200.0</plot_lenX>"
         << "<plot_lenY>200.0</plot_lenY>"
         << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
         << "<plot_temp_C>12.88171785</plot_temp_C>"
         << "<plot_latitude>55.37</plot_latitude>"
         << "</plot>";
}

/////////////////////////////////////////////////////////////////////////////
// WriteTreePopulation2CommonFileStuff()
/////////////////////////////////////////////////////////////////////////////
void WriteTreePopulation2CommonFileStuff( std::fstream &oOut )
{
  using namespace std;
  oOut << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
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
       << "<tr_screVal species=\"Species_1\">0.9</tr_screVal>"
       << "<tr_screVal species=\"Species_2\">0.9</tr_screVal>"
       << "<tr_screVal species=\"Species_3\">0.9</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_3\">0.8008</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
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
       << "<tr_scheVal species=\"Species_1\">1</tr_scheVal>"
       << "<tr_scheVal species=\"Species_2\">1</tr_scheVal>"
       << "<tr_scheVal species=\"Species_3\">1</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_2\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_3\">0.03418</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_2\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_3\">0.0299</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
       << "<tr_maxSeedlingHeight>"
       << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_2\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_3\">1.35</tr_mshVal>"
       << "</tr_maxSeedlingHeight>"
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
       << "<behaviorName>ConstantGLI</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Snag\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<ConstantGLI1>"
       << "<li_constGLI>100</li_constGLI>"
       << "</ConstantGLI1>"
       << "</paramFile>";
}

/////////////////////////////////////////////////////////////////////////////
// WriteTreePopulation2TextTreeMap()
/////////////////////////////////////////////////////////////////////////////
const char* WriteTreePopulation2TextTreeMap()
{
  using namespace std;
  const char *cFileString = "TestTreeFile1.txt";

  //Open file to write to
  fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "X\tY\tSpecies\tType\tDiam\tHeight" << endl

       << "17\t" //X
       << "17\t" //Y
       << "Species_1\tsnag\t"
       << "32.5\t" //DBH
       << "15.8" //Height
       << endl

       << "16\t" //X
       << "16\t" //Y
       << "Species_1\tSnag\t"
       << "45.9\t" //DBH
       << "29.81422424" //Height
       << endl

       << "15\t" //X
       << "15\t" //Y
       << "Species_1\tADULT\t"
       << "21.2\t" //DBH
       << "18.7" //Height
       << endl

       << "14\t" //X
       << "14\t" //Y
       << "Species_1\tadult\t"
       << "18.7\t" //DBH
       << "17.68084137\t" //Height
       << endl

       << "13\t" //X
       << "13\t" //Y
       << "Species_1\tsapling\t"
       << "5.6\t" //DBH
       << "5.6" //Height
       << endl

       << "12\t" //X
       << "12\t" //Y
       << "Species_1\tsapling\t"
       << "4.3\t" //DBH
       << "5.950308026\t\t\t" //Height
       << endl

       << "11\t" //X
       << "11\t" //Y
       << "Species_1\tseedling\t"
       << "0.65\t" //diam10
       << "1.05" //Height
       << endl

       << "10\t" //X
       << "10\t" //Y
       << "Species_1\tseedling\t"
       << "0.8\t" //diam10
       << "0.909206115" //Height
       << endl

       << "9\t" //X
       << "9\t" //Y
       << "Species_1\tsnag\t"
       << "15.41359121\t" //DBH
       << "15.43" //Height
       << endl

       << "8\t" //X
       << "8\t" //Y
       << "Species_1\tsnag\t"
       << "43\t" //DBH
       << "0" //Height
       << endl

       << "7\t" //X
       << "7\t" //Y
       << "Species_1\tadult\t"
       << "23.15587652\t"
       << "20.4" //Height
       << endl

       << "6\t" //X
       << "6\t" //Y
       << "Species_1\tadult\t"
       << "15\t" //DBH
       << "0" //Height
       << endl

       << "5\t" //X
       << "5\t" //Y
       << "Species_1\tsapling\t"
       << "1.663369519\t"
       << "3.2" //Height
       << endl

       << "4\t" //X
       << "4\t" //Y
       << "Species_1\tsapling\t"
       << "8\t" //DBH
       << "0" //Height
       << endl

       << "3\t" //X
       << "3\t" //Y
       << "Species_1\tsapling\t"
       << "5.2052\t" //DBH
       << "0" //Height
       << endl

       << "2\t" //X
       << "2\t" //Y
       << "Species_1\tseedling\t"
       << "0.901196874\t"
       << "1.01" //height
       << endl

       << "1\t" //X
       << "1\t" //Y
       << "Species_1\tseedling\t"
       << "0.2\t" //diam10
       << "0" //Height
       << endl;


  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteTreePopulation2TextTreeMap2()
/////////////////////////////////////////////////////////////////////////////
const char* WriteTreePopulation2TextTreeMap2()
{
  using namespace std;
  const char *cFileString = "TestTreeFile1.txt";

  //Open file to write to
  fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "X\tY\tSpecies\tType\tDiam\tHeight\tylr\tAge\tGrowth\tLight\tvigorous" << endl;
  oOut << "1\t1\tSpecies_1\tSnag\t67.38\t0\t-1\t1\t-1\t57.79\t-1" << endl;
  oOut << "2\t2\tSpecies_1\tSapling\t8.9\t0\t2\t-1\t-1\t27.81\t-1" << endl;
  oOut << "3\t3\tSpecies_1\tAdult\t73.9\t0\t-1\t-1\t12.4\t93.63\t-1" << endl;
  oOut << "4\t4\tSpecies_2\tAdult\t53.04\t0\t-1\t-1\t5.32\t68.75\t1" << endl;
  oOut << "5\t5\tSpecies_3\tAdult\t95.17\t0\t-1\t-1\t1.7\t58.11\t-1" << endl;
  oOut << "6\t6\tSpecies_2\tSnag\t50.1\t0\t-1\t4\t-1\t7.66\t-1" << endl;
  oOut << "7\t7\tSpecies_1\tSapling\t4.19\t0\t1\t-1\t-1\t0.04\t-1" << endl;
  oOut << "8\t8\tSpecies_4\tAdult\t25.19\t0\t-1\t-1\t6.69\t64.47\t0" << endl;
  oOut << "9\t9\tSpecies_3\tSnag\t96.8\t0\t-1\t8\t-1\t31.19\t-1" << endl;
  oOut << "10\t10\tSpecies_3\tSapling\t4.55\t0\t0\t-1\t-1\t73.28\t-1" << endl;
  oOut << "11\t11\tSpecies_4\tSeedling\t0.61\t0\t-1\t-1\t-1\t58.66\t-1" << endl;
  oOut << "12\t12\tSpecies_4\tSnag\t26.58\t0\t-1\t2\t-1\t31.71\t-1" << endl;

  oOut.close();

  return cFileString;
}
