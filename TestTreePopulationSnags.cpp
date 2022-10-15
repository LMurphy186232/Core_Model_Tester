//---------------------------------------------------------------------------
// TestTreePopulationSnags.cpp
//---------------------------------------------------------------------------
#include "TestTreePopulationSnags.h"
#include <gtest/gtest.h>
#include "SimManager.h"
#include "TreePopulation.h"
#include <fstream>
#include <math.h>



/////////////////////////////////////////////////////////////////////////////
// TestCreateSnagsFromInitialDensities()
// Makes sure that initial densities are set up correctly.
/////////////////////////////////////////////////////////////////////////////
TEST(TreePopulation, TestCreateSnagsFromInitialDensities) {
  clTreePopulation * p_oPop;
  clTreeSearch * p_oAllTrees;
  clTree * p_oTree;
  float fDbh;
  int **p_iSnagCounts = new int*[3],
      **p_iAdultCounts = new int*[3], i, j;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    //Counts:  first index size class, second species
    for (i = 0; i < 3; i++) {
      p_iSnagCounts[i] = new int[3];
      p_iAdultCounts[i] = new int[3];
    }

    //------------------------------------------------------------------------/
    // Run 1: snag-aware run, initial densities, but no snag initial densities
    //------------------------------------------------------------------------/
    p_oSimManager->ReadFile( WriteSnagsInitFileRun1() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
    p_oAllTrees = p_oPop->Find( "all" );
    p_oTree = p_oAllTrees->NextTree();
    while ( p_oTree )
    {
      if (p_oTree->GetType() == clTreePopulation::snag) {
        FAIL() << "Snag found where it should not be!";
      }
      p_oTree = p_oAllTrees->NextTree();
    }


    //------------------------------------------------------------------------/
    // Run 2: both snag and live tree initial densities
    //------------------------------------------------------------------------/
    p_oSimManager->ReadFile( WriteSnagsInitFileRun2() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    for (i = 0; i < 3; i++) {
      for (j = 0; j < 3; j++) {
        p_iSnagCounts[i][j] = 0;
        p_iAdultCounts[i][j] = 0;
      }
    }

    //Find all trees
    p_oAllTrees = p_oPop->Find( "all" );
    p_oTree = p_oAllTrees->NextTree();
    while ( p_oTree )
    {

      if (p_oTree->GetType() == clTreePopulation::adult ||
          p_oTree->GetType() == clTreePopulation::sapling) {

        //Get the DBH
        p_oTree->GetValue( p_oPop->GetDbhCode(
            p_oTree->GetSpecies(), p_oTree->GetType() ), & fDbh );

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
      } else if (p_oTree->GetType() == clTreePopulation::snag) {
        //Get the DBH
        p_oTree->GetValue( p_oPop->GetDbhCode(
            p_oTree->GetSpecies(), p_oTree->GetType() ), & fDbh );

        if (fDbh < 10) FAIL() << "Snags can't be tiny!";
        if (fDbh <= 10) { //just in case it's exactly 10
          p_iSnagCounts[0][p_oTree->GetSpecies()]++;
        }
        else if (fDbh > 10 && fDbh <= 15) {
          p_iSnagCounts[1][p_oTree->GetSpecies()]++;
        }
        else if (fDbh > 20 && fDbh <= 35) {
          p_iSnagCounts[2][p_oTree->GetSpecies()]++;
        }
        else {
          FAIL() << "Unexpected DBH for run 2!";
        }
      }
      else {
        FAIL() << "Unexpected tree for run 2!";
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

    //Species 1
    EXPECT_EQ( p_iSnagCounts[0][0], 0 );
    EXPECT_EQ( p_iSnagCounts[1][0], 100 );
    EXPECT_EQ( p_iSnagCounts[2][0], 160 );
    //Species 2
    EXPECT_EQ( p_iSnagCounts[0][1], 0 );
    EXPECT_EQ( p_iSnagCounts[1][1], 120 );
    EXPECT_EQ( p_iSnagCounts[2][1], 0 );
    //Species 3
    EXPECT_EQ( p_iSnagCounts[0][2], 0 );
    EXPECT_EQ( p_iSnagCounts[1][2], 140 );
    EXPECT_EQ( p_iSnagCounts[2][2], 200 );


    //------------------------------------------------------------------------/
    // Run 3: Only snag initial densities; a size class that contains the
    // minimum adult diameter boundary; a seedling size class to be ignored
    //------------------------------------------------------------------------/
    p_oSimManager->ReadFile( WriteSnagsInitFileRun3() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    for (i = 0; i < 3; i++) {
      for (j = 0; j < 3; j++) {
        p_iSnagCounts[i][j] = 0;
      }
    }

    //Find all trees
    p_oAllTrees = p_oPop->Find( "all" );
    p_oTree = p_oAllTrees->NextTree();
    while ( p_oTree )
    {

      if (p_oTree->GetType() == clTreePopulation::snag) {
        //Get the DBH
        p_oTree->GetValue( p_oPop->GetDbhCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fDbh );

        if (fDbh < 10) {
          FAIL() << "Sapling sized snag for run 3!";
        }
        else if (fDbh >= 10 && fDbh <= 15) {
          p_iSnagCounts[1][p_oTree->GetSpecies()]++;
        }
        else if (fDbh > 20 && fDbh <= 35) {
          p_iSnagCounts[2][p_oTree->GetSpecies()]++;
        }
        else {
          FAIL() << "Unexpected DBH for run 3!";
        }
      }
      else {
        FAIL() << "Unexpected tree for run 3!";
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    //Verify that we found all the trees
    //Species 1
    EXPECT_EQ( p_iSnagCounts[0][0], 0 );
    EXPECT_EQ( p_iSnagCounts[1][0], 60 );
    EXPECT_EQ( p_iSnagCounts[2][0], 120 );
    //Species 2
    EXPECT_EQ( p_iSnagCounts[0][1], 0 );
    EXPECT_EQ( p_iSnagCounts[1][1], 80 );
    EXPECT_EQ( p_iSnagCounts[2][1], 140 );
    //Species 3
    EXPECT_EQ( p_iSnagCounts[0][2], 0 );
    EXPECT_EQ( p_iSnagCounts[1][2], 100 );
    EXPECT_EQ( p_iSnagCounts[2][2], 160 );


    //------------------------------------------------------------------------/
    // Run 4: Snag initial densities in a run that isn't snag aware
    //------------------------------------------------------------------------/
    p_oSimManager->ReadFile( WriteSnagsInitFileRun4() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    for (i = 0; i < 3; i++) {
      for (j = 0; j < 3; j++) {
        p_iSnagCounts[i][j] = 0;
        p_iAdultCounts[i][j] = 0;
      }
    }

    //Find all trees
    p_oAllTrees = p_oPop->Find( "all" );
    p_oTree = p_oAllTrees->NextTree();
    while ( p_oTree )
    {
      if (p_oTree->GetType() == clTreePopulation::snag) {
        FAIL() << "Unexpected snag for run 4!";
      }

      //Get the DBH
      p_oTree->GetValue( p_oPop->GetDbhCode(
          p_oTree->GetSpecies(), p_oTree->GetType() ), & fDbh );

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

    for (i = 0; i < 3; i++) {
      delete[] p_iSnagCounts[i];
      delete[] p_iAdultCounts[i];
    }
    delete[] p_iSnagCounts;
    delete p_oSimManager;
  } catch (modelErr &e) {
    for (int i = 0; i < 3; i++) {
      delete[] p_iSnagCounts[i];
      delete[] p_iAdultCounts[i];
    }
    delete[] p_iSnagCounts;
    delete[] p_iAdultCounts;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}



/////////////////////////////////////////////////////////////////////////////
// TestSnagAges()
// This tests the snag age updating. It uses WriteTreePopulationSnagsFile1() to
// create a run where snags are supported. Two snags are created in the file.
// Another is created by the function. It is verified that the ages of all are
// 0. Then a timestep is run, and it is verified that the ages of all snags are
// 1. The process is repeated with WriteTreePopulationSnagsFile2(), which does the
// same thing except with three years per timestep.
/////////////////////////////////////////////////////////////////////////////
TEST(TreePopulation, TestSnagAges)
{
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTreeSearch *p_oAllTrees;
    clTree *p_oTree;
    int iTreeCount = 0, iAge;

    //Read in the parameter file
    p_oSimManager->ReadFile(WriteTreePopulationSnagsFile1());
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Kill all adults
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      if (clTreePopulation::adult == p_oTree->GetType()) {
        p_oPop->KillTree(p_oTree, natural);
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    //Check the ages of each snag - should all be 0
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      if (clTreePopulation::snag == p_oTree->GetType()) {

        iTreeCount++;
        p_oTree->GetValue(p_oPop->GetAgeCode(p_oTree->GetSpecies()), &iAge);
        EXPECT_EQ(0, iAge);
      }

      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(4, iTreeCount);

    //Run a timestep and check the ages again - should all be 1
    p_oSimManager->RunSim(1);
    iTreeCount = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      if (clTreePopulation::snag == p_oTree->GetType()) {

        iTreeCount++;
        p_oTree->GetValue(p_oPop->GetAgeCode(p_oTree->GetSpecies()), &iAge);
        EXPECT_EQ(1, iAge);
      }

      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(4, iTreeCount);

    p_oSimManager->RunSim(1);
    iTreeCount = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      if (clTreePopulation::snag == p_oTree->GetType()) {

        iTreeCount++;
        p_oTree->GetValue(p_oPop->GetAgeCode(p_oTree->GetSpecies()), &iAge);
        EXPECT_EQ(2, iAge);
      }

      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(4, iTreeCount);


    //Repeat with WriteTreePopulationSnagsFile2()
    iTreeCount = 0;
    //Read in the parameter file
    p_oSimManager->ReadFile(WriteTreePopulationSnagsFile2());
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Kill all adults
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      if (clTreePopulation::adult == p_oTree->GetType()) {
        p_oPop->KillTree(p_oTree, natural);
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    //Check the ages of each snag - should all be 0
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      if (clTreePopulation::snag == p_oTree->GetType()) {

        iTreeCount++;
        p_oTree->GetValue(p_oPop->GetAgeCode(p_oTree->GetSpecies()), &iAge);
        EXPECT_EQ(0, iAge);
      }

      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(4, iTreeCount);

    //Run a timestep and check the ages again - should all be 3
    p_oSimManager->RunSim(1);
    iTreeCount = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      if (clTreePopulation::snag == p_oTree->GetType()) {

        iTreeCount++;
        p_oTree->GetValue(p_oPop->GetAgeCode(p_oTree->GetSpecies()), &iAge);
        EXPECT_EQ(3, iAge);
      }

      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(4, iTreeCount);
    p_oSimManager->RunSim(1);
    iTreeCount = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      if (clTreePopulation::snag == p_oTree->GetType()) {

        iTreeCount++;
        p_oTree->GetValue(p_oPop->GetAgeCode(p_oTree->GetSpecies()), &iAge);
        EXPECT_EQ(6, iAge);
      }

      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(4, iTreeCount);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestKillTree()
// Tests tree killing. To test to make sure snags are correctly created,
// WriteTreePopulationSnagsFile3() is used to load a file. Seedlings, saplings, adults, and
// snags with all dead reasons are fed to KillTree() to make sure that the
// right thing happens. Then, to make sure snags aren't created when they
// aren't wanted, WriteTreePopulationSnagsFile1() is used to load a file and the same thing
// done to the trees.
/////////////////////////////////////////////////////////////////////////////
TEST(TreePopulation, TestKillTree)
{
  clTreePopulation * p_oPop;
  clTreeSearch *p_oAllTrees;
  clTree *p_oTree;
  float fTemp;
  int *p_iTreeList;
  int iNumTrees = 8, i, iTemp, iTreeCount;
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    p_oSimManager->ReadFile( WriteTreePopulationSnagsFile3() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //The trees are identified by number, which corresponds to their X and Y
    //coordinates.  Tree 1 is a seedling of Species 1; tree 2 is a seedling of
    //species 2; tree 3 is a sapling of species 1; etc.  Species 1 stumps,
    //species 2 does not.  The p_iTreeList will hold the type number for each
    //tree, or -1 if the tree does not exist.  Declare that array and initialize
    //to all -1

    p_iTreeList = new int[iNumTrees];
    for (i = 0; i < iNumTrees; i++) p_iTreeList[i] = -1;

    //Just to make sure, do a search and verify that our initial conditions are
    //the way we expect them
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      //Get the tree's X coordinate, which equals the tree number
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);

      //Set the tree's type
      p_iTreeList[(int)fTemp - 1] = p_oTree->GetType();

      p_oTree = p_oAllTrees->NextTree();
    }

    //Repeat with stumps
    p_oTree = p_oPop->GetFirstStump();
    while ( p_oTree )
    {
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
      //Set the tree's type
      p_iTreeList[(int)fTemp - 1] = p_oTree->GetType();
      p_oTree = p_oTree->GetTaller();
    }

    EXPECT_EQ(p_iTreeList[0], clTreePopulation::seedling);
    EXPECT_EQ(p_iTreeList[1], clTreePopulation::seedling);
    EXPECT_EQ(p_iTreeList[2], clTreePopulation::sapling);
    EXPECT_EQ(p_iTreeList[3], clTreePopulation::sapling);
    EXPECT_EQ(p_iTreeList[4], clTreePopulation::adult);
    EXPECT_EQ(p_iTreeList[5], clTreePopulation::adult);
    EXPECT_EQ(p_iTreeList[6], clTreePopulation::snag);
    EXPECT_EQ(p_iTreeList[7], clTreePopulation::snag);

    //**************************************************
    //Kill all the trees due to natural cause - no snags
    //**************************************************
    p_oAllTrees->StartOver();
    for (i = 0; i < iNumTrees; i++) p_iTreeList[i] = -1;
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_oPop->KillTree(p_oTree, natural);
      p_oTree = p_oAllTrees->NextTree();
    }

    //Collect the flags again
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      //Get the tree's X coordinate, which equals the tree number
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);

      //Set the tree's type
      p_iTreeList[(int)fTemp - 1] = p_oTree->GetType();

      p_oTree = p_oAllTrees->NextTree();
    }

    //Repeat with stumps
    p_oTree = p_oPop->GetFirstStump();
    while ( p_oTree )
    {
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
      //Set the tree's type
      p_iTreeList[(int)fTemp - 1] = p_oTree->GetType();
      p_oTree = p_oTree->GetTaller();
    }

    //All trees should be gone
    for (i = 0; i < iNumTrees; i++) {
      EXPECT_EQ(p_iTreeList[i], -1);
    }

    //**************************************************
    //Kill all the trees due to disease - no snags
    //**************************************************
    p_oSimManager->ReadFile( WriteTreePopulationSnagsFile3() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
    for (i = 0; i < iNumTrees; i++) p_iTreeList[i] = -1;

    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_oPop->KillTree(p_oTree, disease);
      p_oTree = p_oAllTrees->NextTree();
    }

    //Collect the flags
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      //Get the tree's X coordinate, which equals the tree number
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);

      //Set the tree's type
      p_iTreeList[(int)fTemp - 1] = p_oTree->GetType();

      p_oTree = p_oAllTrees->NextTree();
    }

    //Repeat with stumps
    p_oTree = p_oPop->GetFirstStump();
    while ( p_oTree )
    {
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
      //Set the tree's type
      p_iTreeList[(int)fTemp - 1] = p_oTree->GetType();
      p_oTree = p_oTree->GetTaller();
    }

    //All trees should be gone
    for (i = 0; i < iNumTrees; i++) {
      EXPECT_EQ(p_iTreeList[i], -1);
    }

    //**************************************************
    //Kill all the trees due to insects - no snags
    //**************************************************
    p_oSimManager->ReadFile( WriteTreePopulationSnagsFile3() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
    for (i = 0; i < iNumTrees; i++) p_iTreeList[i] = -1;

    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_oPop->KillTree(p_oTree, insects);
      p_oTree = p_oAllTrees->NextTree();
    }

    //Collect the flags
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      //Get the tree's X coordinate, which equals the tree number
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);

      //Set the tree's type
      p_iTreeList[(int)fTemp - 1] = p_oTree->GetType();

      p_oTree = p_oAllTrees->NextTree();
    }

    //Repeat with stumps
    p_oTree = p_oPop->GetFirstStump();
    while ( p_oTree )
    {
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
      //Set the tree's type
      p_iTreeList[(int)fTemp - 1] = p_oTree->GetType();
      p_oTree = p_oTree->GetTaller();
    }

    //All trees should be gone
    for (i = 0; i < iNumTrees; i++) {
      EXPECT_EQ(p_iTreeList[i], -1);
    }

    //**************************************************
    //Kill all the trees due to fire - no snags
    //**************************************************
    p_oSimManager->ReadFile( WriteTreePopulationSnagsFile3() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
    for (i = 0; i < iNumTrees; i++) p_iTreeList[i] = -1;

    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_oPop->KillTree(p_oTree, fire);
      p_oTree = p_oAllTrees->NextTree();
    }

    //Collect the flags
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      //Get the tree's X coordinate, which equals the tree number
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);

      //Set the tree's type
      p_iTreeList[(int)fTemp - 1] = p_oTree->GetType();

      p_oTree = p_oAllTrees->NextTree();
    }

    //Repeat with stumps
    p_oTree = p_oPop->GetFirstStump();
    while ( p_oTree )
    {
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
      //Set the tree's type
      p_iTreeList[(int)fTemp - 1] = p_oTree->GetType();
      p_oTree = p_oTree->GetTaller();
    }

    //All trees should be gone
    for (i = 0; i < iNumTrees; i++) {
      EXPECT_EQ(p_iTreeList[i], -1);
    }

    //**************************************************
    //Kill all the trees due to harvest - no snags
    //**************************************************
    p_oSimManager->ReadFile( WriteTreePopulationSnagsFile3() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
    for (i = 0; i < iNumTrees; i++) p_iTreeList[i] = -1;

    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_oPop->KillTree(p_oTree, harvest);
      p_oTree = p_oAllTrees->NextTree();
    }

    //Collect the flags
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      //Get the tree's X coordinate, which equals the tree number
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);

      //Set the tree's type
      p_iTreeList[(int)fTemp - 1] = p_oTree->GetType();

      p_oTree = p_oAllTrees->NextTree();
    }

    //Make sure that the adults are gone before we go through the stumps - trees 5 & 6
    EXPECT_EQ(p_iTreeList[4], -1);
    EXPECT_EQ(p_iTreeList[5], -1);

    //Repeat with stumps
    p_oTree = p_oPop->GetFirstStump();
    while ( p_oTree )
    {
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
      //Set the tree's type
      p_iTreeList[(int)fTemp - 1] = p_oTree->GetType();
      p_oTree = p_oTree->GetTaller();
    }

    //All trees should be gone except the sapling (#3) and adult (# 5) of
    //species 1, which should be stumps
    for (i = 0; i < iNumTrees; i++) {
      if (i == 4 || i == 2)
        EXPECT_EQ(p_iTreeList[i], clTreePopulation::stump);
      else
        EXPECT_EQ(p_iTreeList[i], -1);
    }

    //**************************************************
    //Kill all the trees with forced removal - no snags
    //**************************************************
    p_oSimManager->ReadFile( WriteTreePopulationSnagsFile3() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
    for (i = 0; i < iNumTrees; i++) p_iTreeList[i] = -1;

    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_oPop->KillTree(p_oTree, remove_tree);
      p_oTree = p_oAllTrees->NextTree();
    }

    //Collect the flags
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      //Get the tree's X coordinate, which equals the tree number
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);

      //Set the tree's type
      p_iTreeList[(int)fTemp - 1] = p_oTree->GetType();

      p_oTree = p_oAllTrees->NextTree();
    }

    //Repeat with stumps
    p_oTree = p_oPop->GetFirstStump();
    while ( p_oTree )
    {
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
      //Set the tree's type
      p_iTreeList[(int)fTemp - 1] = p_oTree->GetType();
      p_oTree = p_oTree->GetTaller();
    }

    //All trees should be gone
    for (i = 0; i < iNumTrees; i++) {
      EXPECT_EQ(p_iTreeList[i], -1);
    }

    //**************************************************
    //Redo everything with snags this time
    //**************************************************
    //Test our initial conditions
    p_oSimManager->ReadFile( WriteTreePopulationSnagsFile1() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
    for (i = 0; i < iNumTrees; i++) p_iTreeList[i] = -1;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      //Get the tree's X coordinate, which equals the tree number
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);

      //Set the tree's type
      p_iTreeList[(int)fTemp - 1] = p_oTree->GetType();

      p_oTree = p_oAllTrees->NextTree();
    }

    //Repeat with stumps
    p_oTree = p_oPop->GetFirstStump();
    while ( p_oTree )
    {
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
      //Set the tree's type
      p_iTreeList[(int)fTemp - 1] = p_oTree->GetType();
      p_oTree = p_oTree->GetTaller();
    }
    EXPECT_EQ(p_iTreeList[0], clTreePopulation::seedling);
    EXPECT_EQ(p_iTreeList[1], clTreePopulation::seedling);
    EXPECT_EQ(p_iTreeList[2], clTreePopulation::sapling);
    EXPECT_EQ(p_iTreeList[3], clTreePopulation::sapling);
    EXPECT_EQ(p_iTreeList[4], clTreePopulation::adult);
    EXPECT_EQ(p_iTreeList[5], clTreePopulation::adult);
    EXPECT_EQ(p_iTreeList[6], clTreePopulation::snag);
    EXPECT_EQ(p_iTreeList[7], clTreePopulation::snag);

    //**************************************************
    //Kill all the trees due to natural cause - with snags
    //**************************************************
    p_oAllTrees->StartOver();
    for (i = 0; i < iNumTrees; i++) p_iTreeList[i] = -1;
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_oPop->KillTree(p_oTree, natural);
      p_oTree = p_oAllTrees->NextTree();
    }

    //Collect the flags again
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    iTreeCount = 0;
    while (p_oTree) {

      //Get the tree's X coordinate, which equals the tree number
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
      i = (int)fTemp - 1;
      //Trees 5 & 6 should be snags - all others should be gone
      EXPECT_TRUE(i == 4 || i == 5);
      EXPECT_EQ(p_oTree->GetType(), clTreePopulation::snag);
      //Make sure the reason code is right
      p_oTree->GetValue(p_oPop->GetWhyDeadCode(p_oTree->GetSpecies()), &iTemp);
      EXPECT_EQ(natural, iTemp);
      //Make sure the snags are the same size as the adults were
      p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
      EXPECT_EQ(fTemp, 33.0);

      iTreeCount++;

      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(2, iTreeCount);

    //Repeat with stumps
    p_oTree = p_oPop->GetFirstStump();
    EXPECT_EQ(NULL, p_oTree);

    //**************************************************
    //Kill all the trees due to disease - with snags
    //**************************************************
    p_oSimManager->ReadFile( WriteTreePopulationSnagsFile1() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
    for (i = 0; i < iNumTrees; i++) p_iTreeList[i] = -1;

    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_oPop->KillTree(p_oTree, disease);
      p_oTree = p_oAllTrees->NextTree();
    }

    //Collect the flags
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    iTreeCount = 0;
    while (p_oTree) {

      //Get the tree's X coordinate, which equals the tree number
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
      i = (int)fTemp - 1;
      //Trees 5 & 6 should be snags - all others should be gone
      EXPECT_TRUE(i == 4 || i == 5);
      EXPECT_EQ(p_oTree->GetType(), clTreePopulation::snag);
      //Make sure the reason code is right
      p_oTree->GetValue(p_oPop->GetWhyDeadCode(p_oTree->GetSpecies()), &iTemp);
      EXPECT_EQ(disease, iTemp);
      //Make sure the snags are the same size as the adults were
      p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
      EXPECT_EQ(fTemp, 33.0);

      iTreeCount++;

      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(2, iTreeCount);

    //Repeat with stumps
    p_oTree = p_oPop->GetFirstStump();
    EXPECT_EQ(NULL, p_oTree);

    //**************************************************
    //Kill all the trees due to insects - with snags
    //**************************************************
    p_oSimManager->ReadFile( WriteTreePopulationSnagsFile1() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
    for (i = 0; i < iNumTrees; i++) p_iTreeList[i] = -1;

    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_oPop->KillTree(p_oTree, insects);
      p_oTree = p_oAllTrees->NextTree();
    }

    //Collect the flags
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    iTreeCount = 0;
    while (p_oTree) {

      //Get the tree's X coordinate, which equals the tree number
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
      i = (int)fTemp - 1;
      //Trees 5 & 6 should be snags - all others should be gone
      EXPECT_TRUE(i == 4 || i == 5);
      EXPECT_EQ(p_oTree->GetType(), clTreePopulation::snag);
      //Make sure the reason code is right
      p_oTree->GetValue(p_oPop->GetWhyDeadCode(p_oTree->GetSpecies()), &iTemp);
      EXPECT_EQ(insects, iTemp);
      //Make sure the snags are the same size as the adults were
      p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
      EXPECT_EQ(fTemp, 33.0);

      iTreeCount++;

      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(2, iTreeCount);

    //Repeat with stumps
    p_oTree = p_oPop->GetFirstStump();
    EXPECT_EQ(NULL, p_oTree);

    //**************************************************
    //Kill all the trees due to fire - with snags
    //**************************************************
    p_oSimManager->ReadFile( WriteTreePopulationSnagsFile1() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
    for (i = 0; i < iNumTrees; i++) p_iTreeList[i] = -1;

    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_oPop->KillTree(p_oTree, fire);
      p_oTree = p_oAllTrees->NextTree();
    }

    //Collect the flags
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    iTreeCount = 0;
    while (p_oTree) {

      //Get the tree's X coordinate, which equals the tree number
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
      i = (int)fTemp - 1;
      //Trees 5 & 6 should be snags - all others should be gone
      EXPECT_TRUE(i == 4 || i == 5);
      EXPECT_EQ(p_oTree->GetType(), clTreePopulation::snag);
      //Make sure the reason code is right
      p_oTree->GetValue(p_oPop->GetWhyDeadCode(p_oTree->GetSpecies()), &iTemp);
      EXPECT_EQ(fire, iTemp);
      //Make sure the snags are the same size as the adults were
      p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
      EXPECT_EQ(fTemp, 33.0);

      iTreeCount++;

      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(2, iTreeCount);

    //Repeat with stumps
    p_oTree = p_oPop->GetFirstStump();
    EXPECT_EQ(NULL, p_oTree);


    //**************************************************
    //Kill all the trees due to harvest - with snags
    //**************************************************
    p_oSimManager->ReadFile( WriteTreePopulationSnagsFile1() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
    for (i = 0; i < iNumTrees; i++) p_iTreeList[i] = -1;

    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_oPop->KillTree(p_oTree, harvest);
      p_oTree = p_oAllTrees->NextTree();
    }

    //Collect the flags
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      //Get the tree's X coordinate, which equals the tree number
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);

      //Set the tree's type
      p_iTreeList[(int)fTemp - 1] = p_oTree->GetType();

      p_oTree = p_oAllTrees->NextTree();
    }

    //Make sure that the adults are gone before we go through the stumps - trees 5 & 6
    EXPECT_EQ(p_iTreeList[4], -1);
    EXPECT_EQ(p_iTreeList[5], -1);

    //Repeat with stumps
    p_oTree = p_oPop->GetFirstStump();
    while ( p_oTree )
    {
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
      //Set the tree's type
      p_iTreeList[(int)fTemp - 1] = p_oTree->GetType();
      p_oTree = p_oTree->GetTaller();
    }

    //All trees should be gone except the sapling (#3) and adult (# 5) of
    //species 1, which should be stumps
    for (i = 0; i < iNumTrees; i++) {
      if (i == 4 || i == 2)
        EXPECT_EQ(p_iTreeList[i], clTreePopulation::stump);
      else
        EXPECT_EQ(p_iTreeList[i], -1);
    }

    //**************************************************
    //Kill all the trees with forced removal - with snags
    //**************************************************
    p_oSimManager->ReadFile( WriteTreePopulationSnagsFile1() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
    for (i = 0; i < iNumTrees; i++) p_iTreeList[i] = -1;

    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_oPop->KillTree(p_oTree, remove_tree);
      p_oTree = p_oAllTrees->NextTree();
    }

    //Collect the flags
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      //Get the tree's X coordinate, which equals the tree number
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);

      //Set the tree's type
      p_iTreeList[(int)fTemp - 1] = p_oTree->GetType();

      p_oTree = p_oAllTrees->NextTree();
    }

    //Repeat with stumps
    p_oTree = p_oPop->GetFirstStump();
    while ( p_oTree )
    {
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
      //Set the tree's type
      p_iTreeList[(int)fTemp - 1] = p_oTree->GetType();
      p_oTree = p_oTree->GetTaller();
    }

    //All trees should be gone
    for (i = 0; i < iNumTrees; i++) {
      EXPECT_EQ(p_iTreeList[i], -1);
    }

    delete[] p_iTreeList;
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete[] p_iTreeList;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestErrorProcessing()
////////////////////////////////////////////////////////////////////////////
TEST(TreePopulation2, TestSnagInitErrorProcessing) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try
  {
    //Error file 1: a negative number
    p_oSimManager->ReadFile(WriteSnagInitErrorFile1());
    FAIL() << "TestSnagInitialDensities error processing didn't catch error for WriteSnagInitErrorFile1.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clTreePopulation::CreateSnagsFromInitialDensities") != 0)
    {
      FAIL() << "TestSnagInitialDensities error processing caught wrong error for WriteSnagInitErrorFile1.";
    }
    ;
  }

  try
  {
    // Error file 2: A non-number
    p_oSimManager->ReadFile(WriteSnagInitErrorFile2());
    FAIL() << "TestSnagInitialDensities error processing didn't catch error for WriteSnagInitErrorFile2.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clTreePopulation::CreateSnagsFromInitialDensities") != 0)
    {
      FAIL() << "TestSnagInitialDensities error processing caught wrong error for WriteSnagInitErrorFile2.";
    }
    ;
  }

  try
  {
    //Error file 3: Size classes are missing.
    p_oSimManager->ReadFile(WriteSnagInitErrorFile3());
    FAIL() << "TestSnagInitialDensities error processing didn't catch error for WriteSnagInitErrorFile3.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clTreePopulation::CreateSnagsFromInitialDensities") != 0)
    {
      FAIL() << "TestSnagInitialDensities error processing caught wrong error for WriteSnagInitErrorFile3.";
    }
    ;
  }

  try
  {
    //Error file 4: Unrecognized species.
    p_oSimManager->ReadFile(WriteSnagInitErrorFile4());
    FAIL() << "TestSnagInitialDensities error processing didn't catch error for WriteSnagInitErrorFile4.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clTreePopulation::CreateSnagsFromInitialDensities") != 0)
    {
      FAIL() << "TestSnagInitialDensities error processing caught wrong error for WriteSnagInitErrorFile4.";
    }
    ;
  }

  try
  {
    //Error file 5: Unrecognized size class.
    p_oSimManager->ReadFile(WriteSnagInitErrorFile5());
    FAIL() << "TestSnagInitialDensities error processing didn't catch error for WriteSnagInitErrorFile5.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clTreePopulation::CreateSnagsFromInitialDensities") != 0)
    {
      FAIL() << "TestSnagInitialDensities error processing caught wrong error for WriteSnagInitErrorFile5.";
    }
    ;
  }

  try
  {
    //Error file 6: Unparseable size class in size class definition.
    p_oSimManager->ReadFile(WriteSnagInitErrorFile6());
    FAIL() << "TestSnagInitialDensities error processing didn't catch error for WriteSnagInitErrorFile6.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clTreePopulation::CreateSnagsFromInitialDensities") != 0)
    {
      FAIL() << "TestSnagInitialDensities error processing caught wrong error for WriteSnagInitErrorFile6.";
    }
    ;
  }

  try
  {
    //Error file 7: Attempt to create seedling-size snags.
    p_oSimManager->ReadFile(WriteSnagInitErrorFile7());
    FAIL() << "TestSnagInitialDensities error processing didn't catch error for WriteSnagInitErrorFile7.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clTreePopulation::CreateSnagsFromInitialDensities") != 0)
    {
      FAIL() << "TestSnagInitialDensities error processing caught wrong error for WriteSnagInitErrorFile7.";
    }
    ;
  }


  delete p_oSimManager;
}




/////////////////////////////////////////////////////////////////////////////
// WriteTreePopulationSnagsFile3()
/////////////////////////////////////////////////////////////////////////////
const char* WriteTreePopulationSnagsFile3()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

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
      << "</plot>"
      << "<trees>"
      << "<tr_speciesList>"
      << "<tr_species speciesName=\"Species_1\"/>"
      << "<tr_species speciesName=\"Species_2\"/>"
      << "</tr_speciesList>"
      << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
      << "<tr_minAdultDBH>"
      << "<tr_madVal species=\"Species_1\">9.8</tr_madVal>"
      << "<tr_madVal species=\"Species_2\">10</tr_madVal>"
      << "</tr_minAdultDBH>"
      << "<tr_maxSeedlingHeight>"
      << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Species_2\">1.35</tr_mshVal>"
      << "</tr_maxSeedlingHeight>"
      << "<tr_treemap>"
      << "<tm_treeSettings sp=\"Species_1\" tp=\"1\">"
      << "<tm_floatCodes>"
      << "<tm_floatCode label=\"X\">0</tm_floatCode>"
      << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
      << "<tm_floatCode label=\"Diam10\">2</tm_floatCode>"
      << "</tm_floatCodes>"
      << "</tm_treeSettings>"
      << "<tm_treeSettings sp=\"Species_2\" tp=\"1\">"
      << "<tm_floatCodes>"
      << "<tm_floatCode label=\"X\">0</tm_floatCode>"
      << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
      << "<tm_floatCode label=\"Diam10\">2</tm_floatCode>"
      << "</tm_floatCodes>"
      << "</tm_treeSettings>"
      << "<tm_treeSettings sp=\"Species_1\" tp=\"2\">"
      << "<tm_floatCodes>"
      << "<tm_floatCode label=\"X\">0</tm_floatCode>"
      << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
      << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
      << "</tm_floatCodes>"
      << "</tm_treeSettings>"
      << "<tm_treeSettings sp=\"Species_2\" tp=\"2\">"
      << "<tm_floatCodes>"
      << "<tm_floatCode label=\"X\">0</tm_floatCode>"
      << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
      << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
      << "</tm_floatCodes>"
      << "</tm_treeSettings>"
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
      << "</tm_treeSettings>"
      << "<tm_treeSettings sp=\"Species_1\" tp=\"5\">"
      << "<tm_floatCodes>"
      << "<tm_floatCode label=\"X\">0</tm_floatCode>"
      << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
      << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
      << "</tm_floatCodes>"
      << "</tm_treeSettings>"
      << "<tm_treeSettings sp=\"Species_2\" tp=\"5\">"
      << "<tm_floatCodes>"
      << "<tm_floatCode label=\"X\">0</tm_floatCode>"
      << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
      << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
      << "</tm_floatCodes>"
      << "</tm_treeSettings>"
      << "<tree sp=\"0\" tp=\"1\">"
      << "<fl c=\"0\">1</fl>"
      << "<fl c=\"1\">1</fl>"
      << "<fl c=\"2\">0.3</fl>"
      << "</tree>"
      << "<tree sp=\"1\" tp=\"1\">"
      << "<fl c=\"0\">2</fl>"
      << "<fl c=\"1\">2</fl>"
      << "<fl c=\"2\">0.3</fl>"
      << "</tree>"
      << "<tree sp=\"0\" tp=\"2\">"
      << "<fl c=\"0\">3</fl>"
      << "<fl c=\"1\">3</fl>"
      << "<fl c=\"2\">3</fl>"
      << "</tree>"
      << "<tree sp=\"1\" tp=\"2\">"
      << "<fl c=\"0\">4</fl>"
      << "<fl c=\"1\">4</fl>"
      << "<fl c=\"2\">3</fl>"
      << "</tree>"
      << "<tree sp=\"0\" tp=\"3\">"
      << "<fl c=\"0\">5</fl>"
      << "<fl c=\"1\">5</fl>"
      << "<fl c=\"2\">33</fl>"
      << "</tree>"
      << "<tree sp=\"1\" tp=\"3\">"
      << "<fl c=\"0\">6</fl>"
      << "<fl c=\"1\">6</fl>"
      << "<fl c=\"2\">33</fl>"
      << "</tree>"
      << "<tree sp=\"0\" tp=\"5\">"
      << "<fl c=\"0\">7</fl>"
      << "<fl c=\"1\">7</fl>"
      << "<fl c=\"2\">13</fl>"
      << "</tree>"
      << "<tree sp=\"1\" tp=\"5\">"
      << "<fl c=\"0\">8</fl>"
      << "<fl c=\"1\">8</fl>"
      << "<fl c=\"2\">13</fl>"
      << "</tree>"
      << "</tr_treemap>"
      << "</trees>"
      << "<allometry>"
      << "<tr_canopyHeight>"
      << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
      << "<tr_chVal species=\"Species_2\">39.54</tr_chVal>"
      << "</tr_canopyHeight>"
      << "<tr_stdAsympCrownRad>"
      << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_2\">0.0614</tr_sacrVal>"
      << "</tr_stdAsympCrownRad>"
      << "<tr_stdCrownRadExp>"
      << "<tr_screVal species=\"Species_1\">0.9</tr_screVal>"
      << "<tr_screVal species=\"Species_2\">1</tr_screVal>"
      << "</tr_stdCrownRadExp>"
      << "<tr_stdMaxCrownRad>"
      << "<tr_smcrVal species=\"Species_1\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Species_2\">10</tr_smcrVal>"
      << "</tr_stdMaxCrownRad>"
      << "<tr_conversionDiam10ToDBH>"
      << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_2\">0.5944</tr_cdtdVal>"
      << "</tr_conversionDiam10ToDBH>"
      << "<tr_interceptDiam10ToDBH>"
      << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
      << "</tr_interceptDiam10ToDBH>"
      << "<tr_stdAsympCrownHt>"
      << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
      << "<tr_sachVal species=\"Species_2\">0.368</tr_sachVal>"
      << "</tr_stdAsympCrownHt>"
      << "<tr_stdCrownHtExp>"
      << "<tr_scheVal species=\"Species_1\">1</tr_scheVal>"
      << "<tr_scheVal species=\"Species_2\">0.5</tr_scheVal>"
      << "</tr_stdCrownHtExp>"
      << "<tr_slopeOfHeight-Diam10>"
      << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_2\">0.0269</tr_sohdVal>"
      << "</tr_slopeOfHeight-Diam10>"
      << "<tr_slopeOfAsymHeight>"
      << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
      << "<tr_soahVal species=\"Species_2\">0.0241</tr_soahVal>"
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
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>GapDisperse</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Stump\" />"
      << "<applyTo species=\"Species_2\" type=\"Adult\" />"
      << "</behavior>"
      << "</behaviorList>"
      << "<ConstantGLI1>"
      << "<li_constGLI>100</li_constGLI>"
      << "</ConstantGLI1>"
      << "<GapDisperse2>"
      << "<di_weibullCanopySTR>"
      << "<di_wcsVal species=\"Species_1\">0.0</di_wcsVal>"
      << "<di_wcsVal species=\"Species_2\">0.0</di_wcsVal>"
      << "</di_weibullCanopySTR>"
      << "<di_weibullCanopyBeta>"
      << "<di_wcbVal species=\"Species_1\">0.0</di_wcbVal>"
      << "<di_wcbVal species=\"Species_2\">0.0</di_wcbVal>"
      << "</di_weibullCanopyBeta>"
      << "<di_weibullCanopyDispersal>"
      << "<di_wcdVal species=\"Species_1\">0.0</di_wcdVal>"
      << "<di_wcdVal species=\"Species_2\">0.0</di_wcdVal>"
      << "</di_weibullCanopyDispersal>"
      << "<di_weibullCanopyTheta>"
      << "<di_wctVal species=\"Species_1\">0.0</di_wctVal>"
      << "<di_wctVal species=\"Species_2\">0.0</di_wctVal>"
      << "</di_weibullCanopyTheta>"
      << "<di_weibullGapSTR>"
      << "<di_wgsVal species=\"Species_1\">0.0</di_wgsVal>"
      << "<di_wgsVal species=\"Species_2\">0.0</di_wgsVal>"
      << "</di_weibullGapSTR>"
      << "<di_weibullGapBeta>"
      << "<di_wgbVal species=\"Species_1\">0.0</di_wgbVal>"
      << "<di_wgbVal species=\"Species_2\">0.0</di_wgbVal>"
      << "</di_weibullGapBeta>"
      << "<di_weibullGapDispersal>"
      << "<di_wgdVal species=\"Species_1\">0.0</di_wgdVal>"
      << "<di_wgdVal species=\"Species_2\">0.0</di_wgdVal>"
      << "</di_weibullGapDispersal>"
      << "<di_weibullGapTheta>"
      << "<di_wgtVal species=\"Species_1\">0.0</di_wgtVal>"
      << "<di_wgtVal species=\"Species_2\">0.0</di_wgtVal>"
      << "</di_weibullGapTheta>"
      << "<di_lognormalCanopySTR>"
      << "<di_lcsVal species=\"Species_1\">0.0</di_lcsVal>"
      << "<di_lcsVal species=\"Species_2\">0.0</di_lcsVal>"
      << "</di_lognormalCanopySTR>"
      << "<di_lognormalCanopyBeta>"
      << "<di_lcbVal species=\"Species_1\">0.0</di_lcbVal>"
      << "<di_lcbVal species=\"Species_2\">0.0</di_lcbVal>"
      << "</di_lognormalCanopyBeta>"
      << "<di_lognormalCanopyX0>"
      << "<di_lcx0Val species=\"Species_1\">0.0</di_lcx0Val>"
      << "<di_lcx0Val species=\"Species_2\">0.0</di_lcx0Val>"
      << "</di_lognormalCanopyX0>"
      << "<di_lognormalCanopyXb>"
      << "<di_lcxbVal species=\"Species_1\">0.0</di_lcxbVal>"
      << "<di_lcxbVal species=\"Species_2\">0.0</di_lcxbVal>"
      << "</di_lognormalCanopyXb>"
      << "<di_lognormalGapSTR>"
      << "<di_lgsVal species=\"Species_1\">0.0</di_lgsVal>"
      << "<di_lgsVal species=\"Species_2\">0.0</di_lgsVal>"
      << "</di_lognormalGapSTR>"
      << "<di_lognormalGapBeta>"
      << "<di_lgbVal species=\"Species_1\">0.0</di_lgbVal>"
      << "<di_lgbVal species=\"Species_2\">0.0</di_lgbVal>"
      << "</di_lognormalGapBeta>"
      << "<di_lognormalGapX0>"
      << "<di_lgx0Val species=\"Species_1\">0.0</di_lgx0Val>"
      << "<di_lgx0Val species=\"Species_2\">0.0</di_lgx0Val>"
      << "</di_lognormalGapX0>"
      << "<di_lognormalGapXb>"
      << "<di_lgxbVal species=\"Species_1\">0.0</di_lgxbVal>"
      << "<di_lgxbVal species=\"Species_2\">0.0</di_lgxbVal>"
      << "</di_lognormalGapXb>"
      << "<di_suckerSTR>"
      << "<di_ssVal species=\"Species_1\">0.0</di_ssVal>"
      << "<di_ssVal species=\"Species_2\">0.0</di_ssVal>"
      << "</di_suckerSTR>"
      << "<di_suckerBeta>"
      << "<di_sbVal species=\"Species_1\">0.0</di_sbVal>"
      << "<di_sbVal species=\"Species_2\">0.0</di_sbVal>"
      << "</di_suckerBeta>"
      << "<di_maxGapDensity>0</di_maxGapDensity>"
      << "<di_gapFunction>"
      << "<di_gfVal species=\"Species_1\">0</di_gfVal>"
      << "<di_gfVal species=\"Species_2\">0</di_gfVal>"
      << "</di_gapFunction>"
      << "<di_canopyFunction>"
      << "<di_cfVal species=\"Species_1\">0</di_cfVal>"
      << "<di_cfVal species=\"Species_2\">0</di_cfVal>"
      << "</di_canopyFunction>"
      << "<di_minDbhForReproduction>"
      << "<di_mdfrVal species=\"Species_1\">15.0</di_mdfrVal>"
      << "<di_mdfrVal species=\"Species_2\">15.0</di_mdfrVal>"
      << "</di_minDbhForReproduction>"
      << "</GapDisperse2>"
      << "<GeneralDisperse>"
      << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
      << "</GeneralDisperse>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteTreePopulationSnagsFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteTreePopulationSnagsFile1()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">"
      << "<plot>"
      << "<timesteps>6</timesteps>"
      << "<yearsPerTimestep>1</yearsPerTimestep>"
      << "<randomSeed>1</randomSeed>"
      << "<plot_lenX>200.0</plot_lenX>"
      << "<plot_lenY>200.0</plot_lenY>"
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
      << "<tr_madVal species=\"Species_1\">9.8</tr_madVal>"
      << "<tr_madVal species=\"Species_2\">10</tr_madVal>"
      << "</tr_minAdultDBH>"
      << "<tr_maxSeedlingHeight>"
      << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Species_2\">1.35</tr_mshVal>"
      << "</tr_maxSeedlingHeight>"
      << "<tr_treemap>"
      << "<tm_treeSettings sp=\"Species_1\" tp=\"1\">"
      << "<tm_floatCodes>"
      << "<tm_floatCode label=\"X\">0</tm_floatCode>"
      << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
      << "<tm_floatCode label=\"Diam10\">2</tm_floatCode>"
      << "</tm_floatCodes>"
      << "</tm_treeSettings>"
      << "<tm_treeSettings sp=\"Species_2\" tp=\"1\">"
      << "<tm_floatCodes>"
      << "<tm_floatCode label=\"X\">0</tm_floatCode>"
      << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
      << "<tm_floatCode label=\"Diam10\">2</tm_floatCode>"
      << "</tm_floatCodes>"
      << "</tm_treeSettings>"
      << "<tm_treeSettings sp=\"Species_1\" tp=\"2\">"
      << "<tm_floatCodes>"
      << "<tm_floatCode label=\"X\">0</tm_floatCode>"
      << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
      << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
      << "</tm_floatCodes>"
      << "</tm_treeSettings>"
      << "<tm_treeSettings sp=\"Species_2\" tp=\"2\">"
      << "<tm_floatCodes>"
      << "<tm_floatCode label=\"X\">0</tm_floatCode>"
      << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
      << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
      << "</tm_floatCodes>"
      << "</tm_treeSettings>"
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
      << "</tm_treeSettings>"
      << "<tm_treeSettings sp=\"Species_1\" tp=\"5\">"
      << "<tm_floatCodes>"
      << "<tm_floatCode label=\"X\">0</tm_floatCode>"
      << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
      << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
      << "</tm_floatCodes>"
      << "</tm_treeSettings>"
      << "<tm_treeSettings sp=\"Species_2\" tp=\"5\">"
      << "<tm_floatCodes>"
      << "<tm_floatCode label=\"X\">0</tm_floatCode>"
      << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
      << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
      << "</tm_floatCodes>"
      << "</tm_treeSettings>"
      << "<tree sp=\"0\" tp=\"1\">"
      << "<fl c=\"0\">1</fl>"
      << "<fl c=\"1\">1</fl>"
      << "<fl c=\"2\">0.3</fl>"
      << "</tree>"
      << "<tree sp=\"1\" tp=\"1\">"
      << "<fl c=\"0\">2</fl>"
      << "<fl c=\"1\">2</fl>"
      << "<fl c=\"2\">0.3</fl>"
      << "</tree>"
      << "<tree sp=\"0\" tp=\"2\">"
      << "<fl c=\"0\">3</fl>"
      << "<fl c=\"1\">3</fl>"
      << "<fl c=\"2\">3</fl>"
      << "</tree>"
      << "<tree sp=\"1\" tp=\"2\">"
      << "<fl c=\"0\">4</fl>"
      << "<fl c=\"1\">4</fl>"
      << "<fl c=\"2\">3</fl>"
      << "</tree>"
      << "<tree sp=\"0\" tp=\"3\">"
      << "<fl c=\"0\">5</fl>"
      << "<fl c=\"1\">5</fl>"
      << "<fl c=\"2\">33</fl>"
      << "</tree>"
      << "<tree sp=\"1\" tp=\"3\">"
      << "<fl c=\"0\">6</fl>"
      << "<fl c=\"1\">6</fl>"
      << "<fl c=\"2\">33</fl>"
      << "</tree>"
      << "<tree sp=\"0\" tp=\"5\">"
      << "<fl c=\"0\">7</fl>"
      << "<fl c=\"1\">7</fl>"
      << "<fl c=\"2\">13</fl>"
      << "</tree>"
      << "<tree sp=\"1\" tp=\"5\">"
      << "<fl c=\"0\">8</fl>"
      << "<fl c=\"1\">8</fl>"
      << "<fl c=\"2\">13</fl>"
      << "</tree>"
      << "</tr_treemap>"
      << "</trees>"
      << "<allometry>"
      << "<tr_canopyHeight>"
      << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
      << "<tr_chVal species=\"Species_2\">39.54</tr_chVal>"
      << "</tr_canopyHeight>"
      << "<tr_stdAsympCrownRad>"
      << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_2\">0.0614</tr_sacrVal>"
      << "</tr_stdAsympCrownRad>"
      << "<tr_stdCrownRadExp>"
      << "<tr_screVal species=\"Species_1\">0.9</tr_screVal>"
      << "<tr_screVal species=\"Species_2\">1</tr_screVal>"
      << "</tr_stdCrownRadExp>"
      << "<tr_stdMaxCrownRad>"
      << "<tr_smcrVal species=\"Species_1\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Species_2\">10</tr_smcrVal>"
      << "</tr_stdMaxCrownRad>"
      << "<tr_conversionDiam10ToDBH>"
      << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_2\">0.5944</tr_cdtdVal>"
      << "</tr_conversionDiam10ToDBH>"
      << "<tr_interceptDiam10ToDBH>"
      << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
      << "</tr_interceptDiam10ToDBH>"
      << "<tr_stdAsympCrownHt>"
      << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
      << "<tr_sachVal species=\"Species_2\">0.368</tr_sachVal>"
      << "</tr_stdAsympCrownHt>"
      << "<tr_stdCrownHtExp>"
      << "<tr_scheVal species=\"Species_1\">1</tr_scheVal>"
      << "<tr_scheVal species=\"Species_2\">0.5</tr_scheVal>"
      << "</tr_stdCrownHtExp>"
      << "<tr_slopeOfHeight-Diam10>"
      << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_2\">0.0269</tr_sohdVal>"
      << "</tr_slopeOfHeight-Diam10>"
      << "<tr_slopeOfAsymHeight>"
      << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
      << "<tr_soahVal species=\"Species_2\">0.0241</tr_soahVal>"
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
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Snag\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>GapDisperse</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Stump\" />"
      << "<applyTo species=\"Species_2\" type=\"Adult\" />"
      << "</behavior>"
      << "</behaviorList>"
      << "<ConstantGLI1>"
      << "<li_constGLI>100</li_constGLI>"
      << "</ConstantGLI1>"
      << "<GapDisperse2>"
      << "<di_weibullCanopySTR>"
      << "<di_wcsVal species=\"Species_1\">0.0</di_wcsVal>"
      << "<di_wcsVal species=\"Species_2\">0.0</di_wcsVal>"
      << "</di_weibullCanopySTR>"
      << "<di_weibullCanopyBeta>"
      << "<di_wcbVal species=\"Species_1\">0.0</di_wcbVal>"
      << "<di_wcbVal species=\"Species_2\">0.0</di_wcbVal>"
      << "</di_weibullCanopyBeta>"
      << "<di_weibullCanopyDispersal>"
      << "<di_wcdVal species=\"Species_1\">0.0</di_wcdVal>"
      << "<di_wcdVal species=\"Species_2\">0.0</di_wcdVal>"
      << "</di_weibullCanopyDispersal>"
      << "<di_weibullCanopyTheta>"
      << "<di_wctVal species=\"Species_1\">0.0</di_wctVal>"
      << "<di_wctVal species=\"Species_2\">0.0</di_wctVal>"
      << "</di_weibullCanopyTheta>"
      << "<di_weibullGapSTR>"
      << "<di_wgsVal species=\"Species_1\">0.0</di_wgsVal>"
      << "<di_wgsVal species=\"Species_2\">0.0</di_wgsVal>"
      << "</di_weibullGapSTR>"
      << "<di_weibullGapBeta>"
      << "<di_wgbVal species=\"Species_1\">0.0</di_wgbVal>"
      << "<di_wgbVal species=\"Species_2\">0.0</di_wgbVal>"
      << "</di_weibullGapBeta>"
      << "<di_weibullGapDispersal>"
      << "<di_wgdVal species=\"Species_1\">0.0</di_wgdVal>"
      << "<di_wgdVal species=\"Species_2\">0.0</di_wgdVal>"
      << "</di_weibullGapDispersal>"
      << "<di_weibullGapTheta>"
      << "<di_wgtVal species=\"Species_1\">0.0</di_wgtVal>"
      << "<di_wgtVal species=\"Species_2\">0.0</di_wgtVal>"
      << "</di_weibullGapTheta>"
      << "<di_lognormalCanopySTR>"
      << "<di_lcsVal species=\"Species_1\">0.0</di_lcsVal>"
      << "<di_lcsVal species=\"Species_2\">0.0</di_lcsVal>"
      << "</di_lognormalCanopySTR>"
      << "<di_lognormalCanopyBeta>"
      << "<di_lcbVal species=\"Species_1\">0.0</di_lcbVal>"
      << "<di_lcbVal species=\"Species_2\">0.0</di_lcbVal>"
      << "</di_lognormalCanopyBeta>"
      << "<di_lognormalCanopyX0>"
      << "<di_lcx0Val species=\"Species_1\">0.0</di_lcx0Val>"
      << "<di_lcx0Val species=\"Species_2\">0.0</di_lcx0Val>"
      << "</di_lognormalCanopyX0>"
      << "<di_lognormalCanopyXb>"
      << "<di_lcxbVal species=\"Species_1\">0.0</di_lcxbVal>"
      << "<di_lcxbVal species=\"Species_2\">0.0</di_lcxbVal>"
      << "</di_lognormalCanopyXb>"
      << "<di_lognormalGapSTR>"
      << "<di_lgsVal species=\"Species_1\">0.0</di_lgsVal>"
      << "<di_lgsVal species=\"Species_2\">0.0</di_lgsVal>"
      << "</di_lognormalGapSTR>"
      << "<di_lognormalGapBeta>"
      << "<di_lgbVal species=\"Species_1\">0.0</di_lgbVal>"
      << "<di_lgbVal species=\"Species_2\">0.0</di_lgbVal>"
      << "</di_lognormalGapBeta>"
      << "<di_lognormalGapX0>"
      << "<di_lgx0Val species=\"Species_1\">0.0</di_lgx0Val>"
      << "<di_lgx0Val species=\"Species_2\">0.0</di_lgx0Val>"
      << "</di_lognormalGapX0>"
      << "<di_lognormalGapXb>"
      << "<di_lgxbVal species=\"Species_1\">0.0</di_lgxbVal>"
      << "<di_lgxbVal species=\"Species_2\">0.0</di_lgxbVal>"
      << "</di_lognormalGapXb>"
      << "<di_suckerSTR>"
      << "<di_ssVal species=\"Species_1\">0.0</di_ssVal>"
      << "<di_ssVal species=\"Species_2\">0.0</di_ssVal>"
      << "</di_suckerSTR>"
      << "<di_suckerBeta>"
      << "<di_sbVal species=\"Species_1\">0.0</di_sbVal>"
      << "<di_sbVal species=\"Species_2\">0.0</di_sbVal>"
      << "</di_suckerBeta>"
      << "<di_maxGapDensity>0</di_maxGapDensity>"
      << "<di_gapFunction>"
      << "<di_gfVal species=\"Species_1\">0</di_gfVal>"
      << "<di_gfVal species=\"Species_2\">0</di_gfVal>"
      << "</di_gapFunction>"
      << "<di_canopyFunction>"
      << "<di_cfVal species=\"Species_1\">0</di_cfVal>"
      << "<di_cfVal species=\"Species_2\">0</di_cfVal>"
      << "</di_canopyFunction>"
      << "<di_minDbhForReproduction>"
      << "<di_mdfrVal species=\"Species_1\">15.0</di_mdfrVal>"
      << "<di_mdfrVal species=\"Species_2\">15.0</di_mdfrVal>"
      << "</di_minDbhForReproduction>"
      << "</GapDisperse2>"
      << "<GeneralDisperse>"
      << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
      << "</GeneralDisperse>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteTreePopulationSnagsFile2()
/////////////////////////////////////////////////////////////////////////////
const char* WriteTreePopulationSnagsFile2()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">"
      << "<plot>"
      << "<timesteps>2</timesteps>"
      << "<yearsPerTimestep>3</yearsPerTimestep>"
      << "<randomSeed>1</randomSeed>"
      << "<plot_lenX>200.0</plot_lenX>"
      << "<plot_lenY>200.0</plot_lenY>"
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
      << "<tr_madVal species=\"Species_1\">9.8</tr_madVal>"
      << "<tr_madVal species=\"Species_2\">10</tr_madVal>"
      << "</tr_minAdultDBH>"
      << "<tr_maxSeedlingHeight>"
      << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Species_2\">1.35</tr_mshVal>"
      << "</tr_maxSeedlingHeight>"
      << "<tr_treemap>"
      << "<tm_treeSettings sp=\"Species_1\" tp=\"1\">"
      << "<tm_floatCodes>"
      << "<tm_floatCode label=\"X\">0</tm_floatCode>"
      << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
      << "<tm_floatCode label=\"Diam10\">2</tm_floatCode>"
      << "</tm_floatCodes>"
      << "</tm_treeSettings>"
      << "<tm_treeSettings sp=\"Species_2\" tp=\"1\">"
      << "<tm_floatCodes>"
      << "<tm_floatCode label=\"X\">0</tm_floatCode>"
      << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
      << "<tm_floatCode label=\"Diam10\">2</tm_floatCode>"
      << "</tm_floatCodes>"
      << "</tm_treeSettings>"
      << "<tm_treeSettings sp=\"Species_1\" tp=\"2\">"
      << "<tm_floatCodes>"
      << "<tm_floatCode label=\"X\">0</tm_floatCode>"
      << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
      << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
      << "</tm_floatCodes>"
      << "</tm_treeSettings>"
      << "<tm_treeSettings sp=\"Species_2\" tp=\"2\">"
      << "<tm_floatCodes>"
      << "<tm_floatCode label=\"X\">0</tm_floatCode>"
      << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
      << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
      << "</tm_floatCodes>"
      << "</tm_treeSettings>"
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
      << "</tm_treeSettings>"
      << "<tm_treeSettings sp=\"Species_1\" tp=\"5\">"
      << "<tm_floatCodes>"
      << "<tm_floatCode label=\"X\">0</tm_floatCode>"
      << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
      << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
      << "</tm_floatCodes>"
      << "</tm_treeSettings>"
      << "<tm_treeSettings sp=\"Species_2\" tp=\"5\">"
      << "<tm_floatCodes>"
      << "<tm_floatCode label=\"X\">0</tm_floatCode>"
      << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
      << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
      << "</tm_floatCodes>"
      << "</tm_treeSettings>"
      << "<tree sp=\"0\" tp=\"1\">"
      << "<fl c=\"0\">1</fl>"
      << "<fl c=\"1\">1</fl>"
      << "<fl c=\"2\">0.3</fl>"
      << "</tree>"
      << "<tree sp=\"1\" tp=\"1\">"
      << "<fl c=\"0\">2</fl>"
      << "<fl c=\"1\">2</fl>"
      << "<fl c=\"2\">0.3</fl>"
      << "</tree>"
      << "<tree sp=\"0\" tp=\"2\">"
      << "<fl c=\"0\">3</fl>"
      << "<fl c=\"1\">3</fl>"
      << "<fl c=\"2\">3</fl>"
      << "</tree>"
      << "<tree sp=\"1\" tp=\"2\">"
      << "<fl c=\"0\">4</fl>"
      << "<fl c=\"1\">4</fl>"
      << "<fl c=\"2\">3</fl>"
      << "</tree>"
      << "<tree sp=\"0\" tp=\"3\">"
      << "<fl c=\"0\">5</fl>"
      << "<fl c=\"1\">5</fl>"
      << "<fl c=\"2\">33</fl>"
      << "</tree>"
      << "<tree sp=\"1\" tp=\"3\">"
      << "<fl c=\"0\">6</fl>"
      << "<fl c=\"1\">6</fl>"
      << "<fl c=\"2\">33</fl>"
      << "</tree>"
      << "<tree sp=\"0\" tp=\"5\">"
      << "<fl c=\"0\">7</fl>"
      << "<fl c=\"1\">7</fl>"
      << "<fl c=\"2\">13</fl>"
      << "</tree>"
      << "<tree sp=\"1\" tp=\"5\">"
      << "<fl c=\"0\">8</fl>"
      << "<fl c=\"1\">8</fl>"
      << "<fl c=\"2\">13</fl>"
      << "</tree>"
      << "</tr_treemap>"
      << "</trees>"
      << "<allometry>"
      << "<tr_canopyHeight>"
      << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
      << "<tr_chVal species=\"Species_2\">39.54</tr_chVal>"
      << "</tr_canopyHeight>"
      << "<tr_stdAsympCrownRad>"
      << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_2\">0.0614</tr_sacrVal>"
      << "</tr_stdAsympCrownRad>"
      << "<tr_stdCrownRadExp>"
      << "<tr_screVal species=\"Species_1\">0.9</tr_screVal>"
      << "<tr_screVal species=\"Species_2\">1</tr_screVal>"
      << "</tr_stdCrownRadExp>"
      << "<tr_stdMaxCrownRad>"
      << "<tr_smcrVal species=\"Species_1\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Species_2\">10</tr_smcrVal>"
      << "</tr_stdMaxCrownRad>"
      << "<tr_conversionDiam10ToDBH>"
      << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_2\">0.5944</tr_cdtdVal>"
      << "</tr_conversionDiam10ToDBH>"
      << "<tr_interceptDiam10ToDBH>"
      << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
      << "</tr_interceptDiam10ToDBH>"
      << "<tr_stdAsympCrownHt>"
      << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
      << "<tr_sachVal species=\"Species_2\">0.368</tr_sachVal>"
      << "</tr_stdAsympCrownHt>"
      << "<tr_stdCrownHtExp>"
      << "<tr_scheVal species=\"Species_1\">1</tr_scheVal>"
      << "<tr_scheVal species=\"Species_2\">0.5</tr_scheVal>"
      << "</tr_stdCrownHtExp>"
      << "<tr_slopeOfHeight-Diam10>"
      << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_2\">0.0269</tr_sohdVal>"
      << "</tr_slopeOfHeight-Diam10>"
      << "<tr_slopeOfAsymHeight>"
      << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
      << "<tr_soahVal species=\"Species_2\">0.0241</tr_soahVal>"
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
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Snag\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>GapDisperse</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Stump\" />"
      << "<applyTo species=\"Species_2\" type=\"Adult\" />"
      << "</behavior>"
      << "</behaviorList>"
      << "<ConstantGLI1>"
      << "<li_constGLI>100</li_constGLI>"
      << "</ConstantGLI1>"
      << "<GapDisperse2>"
      << "<di_weibullCanopySTR>"
      << "<di_wcsVal species=\"Species_1\">0.0</di_wcsVal>"
      << "<di_wcsVal species=\"Species_2\">0.0</di_wcsVal>"
      << "</di_weibullCanopySTR>"
      << "<di_weibullCanopyBeta>"
      << "<di_wcbVal species=\"Species_1\">0.0</di_wcbVal>"
      << "<di_wcbVal species=\"Species_2\">0.0</di_wcbVal>"
      << "</di_weibullCanopyBeta>"
      << "<di_weibullCanopyDispersal>"
      << "<di_wcdVal species=\"Species_1\">0.0</di_wcdVal>"
      << "<di_wcdVal species=\"Species_2\">0.0</di_wcdVal>"
      << "</di_weibullCanopyDispersal>"
      << "<di_weibullCanopyTheta>"
      << "<di_wctVal species=\"Species_1\">0.0</di_wctVal>"
      << "<di_wctVal species=\"Species_2\">0.0</di_wctVal>"
      << "</di_weibullCanopyTheta>"
      << "<di_weibullGapSTR>"
      << "<di_wgsVal species=\"Species_1\">0.0</di_wgsVal>"
      << "<di_wgsVal species=\"Species_2\">0.0</di_wgsVal>"
      << "</di_weibullGapSTR>"
      << "<di_weibullGapBeta>"
      << "<di_wgbVal species=\"Species_1\">0.0</di_wgbVal>"
      << "<di_wgbVal species=\"Species_2\">0.0</di_wgbVal>"
      << "</di_weibullGapBeta>"
      << "<di_weibullGapDispersal>"
      << "<di_wgdVal species=\"Species_1\">0.0</di_wgdVal>"
      << "<di_wgdVal species=\"Species_2\">0.0</di_wgdVal>"
      << "</di_weibullGapDispersal>"
      << "<di_weibullGapTheta>"
      << "<di_wgtVal species=\"Species_1\">0.0</di_wgtVal>"
      << "<di_wgtVal species=\"Species_2\">0.0</di_wgtVal>"
      << "</di_weibullGapTheta>"
      << "<di_lognormalCanopySTR>"
      << "<di_lcsVal species=\"Species_1\">0.0</di_lcsVal>"
      << "<di_lcsVal species=\"Species_2\">0.0</di_lcsVal>"
      << "</di_lognormalCanopySTR>"
      << "<di_lognormalCanopyBeta>"
      << "<di_lcbVal species=\"Species_1\">0.0</di_lcbVal>"
      << "<di_lcbVal species=\"Species_2\">0.0</di_lcbVal>"
      << "</di_lognormalCanopyBeta>"
      << "<di_lognormalCanopyX0>"
      << "<di_lcx0Val species=\"Species_1\">0.0</di_lcx0Val>"
      << "<di_lcx0Val species=\"Species_2\">0.0</di_lcx0Val>"
      << "</di_lognormalCanopyX0>"
      << "<di_lognormalCanopyXb>"
      << "<di_lcxbVal species=\"Species_1\">0.0</di_lcxbVal>"
      << "<di_lcxbVal species=\"Species_2\">0.0</di_lcxbVal>"
      << "</di_lognormalCanopyXb>"
      << "<di_lognormalGapSTR>"
      << "<di_lgsVal species=\"Species_1\">0.0</di_lgsVal>"
      << "<di_lgsVal species=\"Species_2\">0.0</di_lgsVal>"
      << "</di_lognormalGapSTR>"
      << "<di_lognormalGapBeta>"
      << "<di_lgbVal species=\"Species_1\">0.0</di_lgbVal>"
      << "<di_lgbVal species=\"Species_2\">0.0</di_lgbVal>"
      << "</di_lognormalGapBeta>"
      << "<di_lognormalGapX0>"
      << "<di_lgx0Val species=\"Species_1\">0.0</di_lgx0Val>"
      << "<di_lgx0Val species=\"Species_2\">0.0</di_lgx0Val>"
      << "</di_lognormalGapX0>"
      << "<di_lognormalGapXb>"
      << "<di_lgxbVal species=\"Species_1\">0.0</di_lgxbVal>"
      << "<di_lgxbVal species=\"Species_2\">0.0</di_lgxbVal>"
      << "</di_lognormalGapXb>"
      << "<di_suckerSTR>"
      << "<di_ssVal species=\"Species_1\">0.0</di_ssVal>"
      << "<di_ssVal species=\"Species_2\">0.0</di_ssVal>"
      << "</di_suckerSTR>"
      << "<di_suckerBeta>"
      << "<di_sbVal species=\"Species_1\">0.0</di_sbVal>"
      << "<di_sbVal species=\"Species_2\">0.0</di_sbVal>"
      << "</di_suckerBeta>"
      << "<di_maxGapDensity>0</di_maxGapDensity>"
      << "<di_gapFunction>"
      << "<di_gfVal species=\"Species_1\">0</di_gfVal>"
      << "<di_gfVal species=\"Species_2\">0</di_gfVal>"
      << "</di_gapFunction>"
      << "<di_canopyFunction>"
      << "<di_cfVal species=\"Species_1\">0</di_cfVal>"
      << "<di_cfVal species=\"Species_2\">0</di_cfVal>"
      << "</di_canopyFunction>"
      << "<di_minDbhForReproduction>"
      << "<di_mdfrVal species=\"Species_1\">15.0</di_mdfrVal>"
      << "<di_mdfrVal species=\"Species_2\">15.0</di_mdfrVal>"
      << "</di_minDbhForReproduction>"
      << "</GapDisperse2>"
      << "<GeneralDisperse>"
      << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
      << "</GeneralDisperse>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}


/////////////////////////////////////////////////////////////////////////////
// WriteSnagsInitFileRun2()
/////////////////////////////////////////////////////////////////////////////
const char* WriteSnagsInitFileRun2()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

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
       << "</tr_initialDensities>"
       << "<tr_snagInitialDensities>"
       << "<tr_sidVals whatSpecies=\"Species_1\">"
       << "<tr_snagInitialDensity sizeClass=\"s10.0\">0.0</tr_snagInitialDensity>"
       << "<tr_snagInitialDensity sizeClass=\"s15.0\">25.0</tr_snagInitialDensity>"
       << "<tr_snagInitialDensity sizeClass=\"s35.0\">40.0</tr_snagInitialDensity>"
       << "</tr_sidVals>"
       << "<tr_sidVals whatSpecies=\"Species_2\">"
       << "<tr_snagInitialDensity sizeClass=\"s10.0\">15.0</tr_snagInitialDensity>"
       << "<tr_snagInitialDensity sizeClass=\"s15.0\">30.0</tr_snagInitialDensity>"
       << "<tr_snagInitialDensity sizeClass=\"s35.0\">0.0</tr_snagInitialDensity>"
       << "</tr_sidVals>"
       << "<tr_sidVals whatSpecies=\"Species_3\">"
       << "<tr_snagInitialDensity sizeClass=\"s10.0\">20.0</tr_snagInitialDensity>"
       << "<tr_snagInitialDensity sizeClass=\"s15.0\">35.0</tr_snagInitialDensity>"
       << "<tr_snagInitialDensity sizeClass=\"s35.0\">50.0</tr_snagInitialDensity>"
       << "</tr_sidVals>"
       << "</tr_snagInitialDensities>";

  WriteTreePopulationSnagsCommonFileStuff(oOut);

  oOut.close();

  return cFileString;
}



/////////////////////////////////////////////////////////////////////////////
// WriteTreePopulationSnagsCommonFileStuff()
/////////////////////////////////////////////////////////////////////////////
void WriteTreePopulationSnagsCommonFileStuff( std::fstream &oOut )
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
       << "<tr_stdMaxCrownRad>"
       << "<tr_smcrVal species=\"Species_1\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_2\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_3\">10</tr_smcrVal>"
       << "</tr_stdMaxCrownRad>"
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
// WriteSnagsInitFileRun1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteSnagsInitFileRun1()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">"
      << "<plot>"
      << "<timesteps>6</timesteps>"
      << "<yearsPerTimestep>1</yearsPerTimestep>"
      << "<randomSeed>1</randomSeed>"
      << "<plot_lenX>200.0</plot_lenX>"
      << "<plot_lenY>200.0</plot_lenY>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88171785</plot_temp_C>"
      << "<plot_latitude>55.37</plot_latitude>"
      << "</plot>"
      << "<trees>"
      << "<tr_speciesList>"
      << "<tr_species speciesName=\"Species_1\"/>"
      << "<tr_species speciesName=\"Species_2\"/>"
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
      << "</tr_initialDensities>";

  WriteTreePopulationSnagsCommonFileStuff(oOut);

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteSnagsInitFileRun3()
/////////////////////////////////////////////////////////////////////////////
const char* WriteSnagsInitFileRun3()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

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

    oOut << "<trees>"
         << "<tr_speciesList>"
         << "<tr_species speciesName=\"Species_1\"/>"
         << "<tr_species speciesName=\"Species_2\"/>"
         << "<tr_species speciesName=\"Species_3\"/>"
         << "</tr_speciesList>"
         << "<tr_sizeClasses>"
         << "<tr_sizeClass sizeKey=\"Seedling\" />"
         << "<tr_sizeClass sizeKey=\"s5.0\" />"
         << "<tr_sizeClass sizeKey=\"s15.0\" />"
         << "<tr_sizeClass sizeKey=\"s20.0\" />"
         << "<tr_sizeClass sizeKey=\"s35.0\" />"
         << "</tr_sizeClasses>"
         << "<tr_snagInitialDensities>"
         << "<tr_sidVals whatSpecies=\"Species_1\">"
         << "<tr_snagInitialDensity sizeClass=\"s15.0\">15.0</tr_snagInitialDensity>"
         << "<tr_snagInitialDensity sizeClass=\"s35.0\">30.0</tr_snagInitialDensity>"
         << "</tr_sidVals>"
         << "<tr_sidVals whatSpecies=\"Species_2\">"
         << "<tr_snagInitialDensity sizeClass=\"s15.0\">20.0</tr_snagInitialDensity>"
         << "<tr_snagInitialDensity sizeClass=\"s35.0\">35.0</tr_snagInitialDensity>"
         << "</tr_sidVals>"
         << "<tr_sidVals whatSpecies=\"Species_3\">"
         << "<tr_snagInitialDensity sizeClass=\"s15.0\">25.0</tr_snagInitialDensity>"
         << "<tr_snagInitialDensity sizeClass=\"s35.0\">40.0</tr_snagInitialDensity>"
         << "</tr_sidVals>"
         << "</tr_snagInitialDensities>";

  WriteTreePopulationSnagsCommonFileStuff(oOut);

  oOut.close();

  return cFileString;
}


/////////////////////////////////////////////////////////////////////////////
// WriteSnagsInitFileRun4()
/////////////////////////////////////////////////////////////////////////////
const char* WriteSnagsInitFileRun4()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

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
         << "</tr_initialDensities>"
         << "<tr_snagInitialDensities>"
         << "<tr_sidVals whatSpecies=\"Species_1\">"
         << "<tr_snagInitialDensity sizeClass=\"s10.0\">0.0</tr_snagInitialDensity>"
         << "<tr_snagInitialDensity sizeClass=\"s15.0\">25.0</tr_snagInitialDensity>"
         << "<tr_snagInitialDensity sizeClass=\"s35.0\">40.0</tr_snagInitialDensity>"
         << "</tr_sidVals>"
         << "<tr_sidVals whatSpecies=\"Species_2\">"
         << "<tr_snagInitialDensity sizeClass=\"s10.0\">15.0</tr_snagInitialDensity>"
         << "<tr_snagInitialDensity sizeClass=\"s15.0\">30.0</tr_snagInitialDensity>"
         << "<tr_snagInitialDensity sizeClass=\"s35.0\">0.0</tr_snagInitialDensity>"
         << "</tr_sidVals>"
         << "<tr_sidVals whatSpecies=\"Species_3\">"
         << "<tr_snagInitialDensity sizeClass=\"s10.0\">20.0</tr_snagInitialDensity>"
         << "<tr_snagInitialDensity sizeClass=\"s15.0\">35.0</tr_snagInitialDensity>"
         << "<tr_snagInitialDensity sizeClass=\"s35.0\">50.0</tr_snagInitialDensity>"
         << "</tr_sidVals>"
         << "</tr_snagInitialDensities>";

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
           << "<tr_stdMaxCrownRad>"
           << "<tr_smcrVal species=\"Species_1\">10</tr_smcrVal>"
           << "<tr_smcrVal species=\"Species_2\">10</tr_smcrVal>"
           << "<tr_smcrVal species=\"Species_3\">10</tr_smcrVal>"
           << "</tr_stdMaxCrownRad>"
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
// WriteSnagInitErrorFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteSnagInitErrorFile1()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">"
      << "<plot>"
      << "<timesteps>6</timesteps>"
      << "<yearsPerTimestep>1</yearsPerTimestep>"
      << "<randomSeed>1</randomSeed>"
      << "<plot_lenX>200.0</plot_lenX>"
      << "<plot_lenY>200.0</plot_lenY>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88171785</plot_temp_C>"
      << "<plot_latitude>55.37</plot_latitude>"
      << "</plot>"
      << "<trees>"
      << "<tr_speciesList>"
      << "<tr_species speciesName=\"Species_1\"/>"
      << "<tr_species speciesName=\"Species_2\"/>"
      << "</tr_speciesList>"
      << "<tr_sizeClasses>"
      << "<tr_sizeClass sizeKey=\"s5.0\" />"
      << "<tr_sizeClass sizeKey=\"s15.0\" />"
      << "</tr_sizeClasses>"
      << "<tr_snagInitialDensities>"
      << "<tr_sidVals whatSpecies=\"Species_1\">"
      << "<tr_snagInitialDensity sizeClass=\"s15.0\">-15.0</tr_snagInitialDensity>"
      << "</tr_sidVals>"
      << "<tr_sidVals whatSpecies=\"Species_2\">"
      << "<tr_snagInitialDensity sizeClass=\"s15.0\">20.0</tr_snagInitialDensity>"
      << "</tr_sidVals>"
      << "<tr_sidVals whatSpecies=\"Species_3\">"
      << "<tr_snagInitialDensity sizeClass=\"s15.0\">25.0</tr_snagInitialDensity>"
      << "</tr_sidVals>"
      << "</tr_snagInitialDensities>";

  WriteTreePopulationSnagsCommonFileStuff(oOut);

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteSnagInitErrorFile2()
/////////////////////////////////////////////////////////////////////////////
const char* WriteSnagInitErrorFile2()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">"
      << "<plot>"
      << "<timesteps>6</timesteps>"
      << "<yearsPerTimestep>1</yearsPerTimestep>"
      << "<randomSeed>1</randomSeed>"
      << "<plot_lenX>200.0</plot_lenX>"
      << "<plot_lenY>200.0</plot_lenY>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88171785</plot_temp_C>"
      << "<plot_latitude>55.37</plot_latitude>"
      << "</plot>"
      << "<trees>"
      << "<tr_speciesList>"
      << "<tr_species speciesName=\"Species_1\"/>"
      << "<tr_species speciesName=\"Species_2\"/>"
      << "</tr_speciesList>"
      << "<tr_sizeClasses>"
      << "<tr_sizeClass sizeKey=\"s5.0\" />"
      << "<tr_sizeClass sizeKey=\"s15.0\" />"
      << "</tr_sizeClasses>"
      << "<tr_snagInitialDensities>"
      << "<tr_sidVals whatSpecies=\"Species_1\">"
      << "<tr_snagInitialDensity sizeClass=\"s15.0\">15.0</tr_snagInitialDensity>"
      << "</tr_sidVals>"
      << "<tr_sidVals whatSpecies=\"Species_2\">"
      << "<tr_snagInitialDensity sizeClass=\"s15.0\">twenty</tr_snagInitialDensity>"
      << "</tr_sidVals>"
      << "<tr_sidVals whatSpecies=\"Species_3\">"
      << "<tr_snagInitialDensity sizeClass=\"s15.0\">25.0</tr_snagInitialDensity>"
      << "</tr_sidVals>"
      << "</tr_snagInitialDensities>";

  WriteTreePopulationSnagsCommonFileStuff(oOut);

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteSnagInitErrorFile3()
/////////////////////////////////////////////////////////////////////////////
const char* WriteSnagInitErrorFile3()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">"
      << "<plot>"
      << "<timesteps>6</timesteps>"
      << "<yearsPerTimestep>1</yearsPerTimestep>"
      << "<randomSeed>1</randomSeed>"
      << "<plot_lenX>200.0</plot_lenX>"
      << "<plot_lenY>200.0</plot_lenY>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88171785</plot_temp_C>"
      << "<plot_latitude>55.37</plot_latitude>"
      << "</plot>"
      << "<trees>"
      << "<tr_speciesList>"
      << "<tr_species speciesName=\"Species_1\"/>"
      << "<tr_species speciesName=\"Species_2\"/>"
      << "</tr_speciesList>"
      << "<tr_snagInitialDensities>"
      << "<tr_sidVals whatSpecies=\"Species_1\">"
      << "<tr_snagInitialDensity sizeClass=\"s15.0\">15.0</tr_snagInitialDensity>"
      << "</tr_sidVals>"
      << "<tr_sidVals whatSpecies=\"Species_2\">"
      << "<tr_snagInitialDensity sizeClass=\"s15.0\">20.0</tr_snagInitialDensity>"
      << "</tr_sidVals>"
      << "<tr_sidVals whatSpecies=\"Species_3\">"
      << "<tr_snagInitialDensity sizeClass=\"s15.0\">25.0</tr_snagInitialDensity>"
      << "</tr_sidVals>"
      << "</tr_snagInitialDensities>";

  WriteTreePopulationSnagsCommonFileStuff(oOut);

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteSnagInitErrorFile4()
/////////////////////////////////////////////////////////////////////////////
const char* WriteSnagInitErrorFile4()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">"
      << "<plot>"
      << "<timesteps>6</timesteps>"
      << "<yearsPerTimestep>1</yearsPerTimestep>"
      << "<randomSeed>1</randomSeed>"
      << "<plot_lenX>200.0</plot_lenX>"
      << "<plot_lenY>200.0</plot_lenY>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88171785</plot_temp_C>"
      << "<plot_latitude>55.37</plot_latitude>"
      << "</plot>"
      << "<trees>"
      << "<tr_speciesList>"
      << "<tr_species speciesName=\"Species_1\"/>"
      << "<tr_species speciesName=\"Species_2\"/>"
      << "</tr_speciesList>"
      << "<tr_sizeClasses>"
      << "<tr_sizeClass sizeKey=\"s5.0\" />"
      << "<tr_sizeClass sizeKey=\"s15.0\" />"
      << "</tr_sizeClasses>"
      << "<tr_snagInitialDensities>"
      << "<tr_sidVals whatSpecies=\"Species_1\">"
      << "<tr_snagInitialDensity sizeClass=\"s15.0\">15.0</tr_snagInitialDensity>"
      << "</tr_sidVals>"
      << "<tr_sidVals whatSpecies=\"Species_4\">"
      << "<tr_snagInitialDensity sizeClass=\"s15.0\">20.0</tr_snagInitialDensity>"
      << "</tr_sidVals>"
      << "<tr_sidVals whatSpecies=\"Species_3\">"
      << "<tr_snagInitialDensity sizeClass=\"s15.0\">25.0</tr_snagInitialDensity>"
      << "</tr_sidVals>"
      << "</tr_snagInitialDensities>";

  WriteTreePopulationSnagsCommonFileStuff(oOut);

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteSnagInitErrorFile5()
/////////////////////////////////////////////////////////////////////////////
const char* WriteSnagInitErrorFile5()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">"
      << "<plot>"
      << "<timesteps>6</timesteps>"
      << "<yearsPerTimestep>1</yearsPerTimestep>"
      << "<randomSeed>1</randomSeed>"
      << "<plot_lenX>200.0</plot_lenX>"
      << "<plot_lenY>200.0</plot_lenY>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88171785</plot_temp_C>"
      << "<plot_latitude>55.37</plot_latitude>"
      << "</plot>"
      << "<trees>"
      << "<tr_speciesList>"
      << "<tr_species speciesName=\"Species_1\"/>"
      << "<tr_species speciesName=\"Species_2\"/>"
      << "</tr_speciesList>"
      << "<tr_sizeClasses>"
      << "<tr_sizeClass sizeKey=\"s5.0\" />"
      << "<tr_sizeClass sizeKey=\"s15.0\" />"
      << "</tr_sizeClasses>"
      << "<tr_snagInitialDensities>"
      << "<tr_sidVals whatSpecies=\"Species_1\">"
      << "<tr_snagInitialDensity sizeClass=\"s15.0\">15.0</tr_snagInitialDensity>"
      << "</tr_sidVals>"
      << "<tr_sidVals whatSpecies=\"Species_2\">"
      << "<tr_snagInitialDensity sizeClass=\"s65.0\">20.0</tr_snagInitialDensity>"
      << "</tr_sidVals>"
      << "<tr_sidVals whatSpecies=\"Species_3\">"
      << "<tr_snagInitialDensity sizeClass=\"s15.0\">25.0</tr_snagInitialDensity>"
      << "</tr_sidVals>"
      << "</tr_snagInitialDensities>";

  WriteTreePopulationSnagsCommonFileStuff(oOut);

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteSnagInitErrorFile6()
/////////////////////////////////////////////////////////////////////////////
const char* WriteSnagInitErrorFile6()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">"
      << "<plot>"
      << "<timesteps>6</timesteps>"
      << "<yearsPerTimestep>1</yearsPerTimestep>"
      << "<randomSeed>1</randomSeed>"
      << "<plot_lenX>200.0</plot_lenX>"
      << "<plot_lenY>200.0</plot_lenY>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88171785</plot_temp_C>"
      << "<plot_latitude>55.37</plot_latitude>"
      << "</plot>"
      << "<trees>"
      << "<tr_speciesList>"
      << "<tr_species speciesName=\"Species_1\"/>"
      << "<tr_species speciesName=\"Species_2\"/>"
      << "</tr_speciesList>"
      << "<tr_sizeClasses>"
      << "<tr_sizeClass sizeKey=\"sds\" />"
      << "<tr_sizeClass sizeKey=\"s15.0\" />"
      << "</tr_sizeClasses>"
      << "<tr_snagInitialDensities>"
      << "<tr_sidVals whatSpecies=\"Species_1\">"
      << "<tr_snagInitialDensity sizeClass=\"s15.0\">15.0</tr_snagInitialDensity>"
      << "</tr_sidVals>"
      << "<tr_sidVals whatSpecies=\"Species_2\">"
      << "<tr_snagInitialDensity sizeClass=\"s15.0\">20.0</tr_snagInitialDensity>"
      << "</tr_sidVals>"
      << "<tr_sidVals whatSpecies=\"Species_3\">"
      << "<tr_snagInitialDensity sizeClass=\"s15.0\">25.0</tr_snagInitialDensity>"
      << "</tr_sidVals>"
      << "</tr_snagInitialDensities>";

  WriteTreePopulationSnagsCommonFileStuff(oOut);

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteSnagInitErrorFile7()
/////////////////////////////////////////////////////////////////////////////
const char* WriteSnagInitErrorFile7()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

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

    oOut << "<trees>"
         << "<tr_speciesList>"
         << "<tr_species speciesName=\"Species_1\"/>"
         << "<tr_species speciesName=\"Species_2\"/>"
         << "<tr_species speciesName=\"Species_3\"/>"
         << "</tr_speciesList>"
         << "<tr_sizeClasses>"
         << "<tr_sizeClass sizeKey=\"Seedling\" />"
         << "<tr_sizeClass sizeKey=\"s5.0\" />"
         << "<tr_sizeClass sizeKey=\"s15.0\" />"
         << "<tr_sizeClass sizeKey=\"s20.0\" />"
         << "<tr_sizeClass sizeKey=\"s35.0\" />"
         << "</tr_sizeClasses>"
         << "<tr_snagInitialDensities>"
         << "<tr_sidVals whatSpecies=\"Species_1\">"
         << "<tr_snagInitialDensity sizeClass=\"Seedling\">10.0</tr_snagInitialDensity>"
         << "<tr_snagInitialDensity sizeClass=\"s15.0\">15.0</tr_snagInitialDensity>"
         << "<tr_snagInitialDensity sizeClass=\"s35.0\">30.0</tr_snagInitialDensity>"
         << "</tr_sidVals>"
         << "<tr_sidVals whatSpecies=\"Species_2\">"
         << "<tr_snagInitialDensity sizeClass=\"Seedling\">10.0</tr_snagInitialDensity>"
         << "<tr_snagInitialDensity sizeClass=\"s15.0\">20.0</tr_snagInitialDensity>"
         << "<tr_snagInitialDensity sizeClass=\"s35.0\">35.0</tr_snagInitialDensity>"
         << "</tr_sidVals>"
         << "<tr_sidVals whatSpecies=\"Species_3\">"
         << "<tr_snagInitialDensity sizeClass=\"Seedling\">10.0</tr_snagInitialDensity>"
         << "<tr_snagInitialDensity sizeClass=\"s15.0\">25.0</tr_snagInitialDensity>"
         << "<tr_snagInitialDensity sizeClass=\"s35.0\">40.0</tr_snagInitialDensity>"
         << "</tr_sidVals>"
         << "</tr_snagInitialDensities>";

  WriteTreePopulationSnagsCommonFileStuff(oOut);

  oOut.close();

  return cFileString;
}
