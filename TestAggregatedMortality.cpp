//---------------------------------------------------------------------------
// TestAggregatedMortality.cpp
//---------------------------------------------------------------------------
#include "TestAggregatedMortality.h"
#include <gtest/gtest.h>
#include "SimManager.h"
#include "TreePopulation.h"
#include "AggregatedMortality.h"
#include <fstream>
#include <sstream>
#include <math.h>


////////////////////////////////////////////////////////////////////////////
// TestErrorProcessing()
////////////////////////////////////////////////////////////////////////////
TEST(AggregatedMortality, TestErrorProcessing)
{
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try
  {
    p_oSimManager->ReadFile( WriteAggregatedMortalityXMLErrorFile1() );
    FAIL() << "TestAggregatedMortality error processing didn't catch error for WriteAggregatedMortalityXMLErrorFile1.";
  }
  catch ( modelErr& err )
  {
    if ( err.sFunction.compare("clAggregatedMortality::ReadParFile" ) != 0 )
    {
      delete p_oSimManager;
      FAIL() << "TestAggregatedMortality error processing caught wrong error for WriteAggregatedMortalityXMLErrorFile1. Function: " << err.sFunction << " Message: " << err.sMoreInfo;
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile( WriteAggregatedMortalityXMLErrorFile2() );
    FAIL() << "TestAggregatedMortality error processing didn't catch error for WriteAggregatedMortalityXMLErrorFile2.";
  }
  catch ( modelErr& err )
  {
    if ( err.sFunction.compare("clAggregatedMortality::ReadParFile" ) != 0 )
    {
      delete p_oSimManager;
      FAIL() << "TestAggregatedMortality error processing caught wrong error for WriteAggregatedMortalityXMLErrorFile2. Function: " << err.sFunction << " Message: " << err.sMoreInfo;
    }
    ;
  }
  delete p_oSimManager;
}

/////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun1()
/////////////////////////////////////////////////////////////////////////////
TEST(AggregatedMortality, TestNormalProcessingRun1)
{
  using namespace std;
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  int **p_iNumCellTrees = NULL;
  int *p_iNumTrees = NULL;

  clTreePopulation * p_oPop;
  clTreeSearch * p_oAllTrees;
  clBehaviorBase * p_oTemp;
  clAggregatedMortality * p_oAggMort;
  clTree * p_oTree;
  float fX, fY, fDiam, fCellLength, fTemp;

  int iSp, iNumXCells, iNumYCells, iX, iY, iNumSpecies = 3, iTemp, iExpected;
  try {
    p_iNumTrees = new int[iNumSpecies];

    //Feed our file to the sim manager
    p_oSimManager->ReadFile( WriteAggregatedMortalityXMLFile1() );

    //Get the tree population
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Put three trees of each species in the center of each grid cell
    fCellLength = p_oPop->GetGridCellSize();
    iNumXCells = p_oPop->GetNumXCells();
    iNumYCells = p_oPop->GetNumYCells();
    fDiam = 20;
    for (iX = 0; iX < iNumXCells; iX++) {
      fX = (iX * fCellLength) + (fCellLength / 2);
      for (iY = 0; iY < iNumYCells; iY++) {
        fY = (iY * fCellLength) + (fCellLength / 2);
        for (iSp = 0; iSp < iNumSpecies; iSp++) {
          p_oPop->CreateTree( fX, fY, iSp, clTreePopulation::adult, fDiam );
          p_oPop->CreateTree( fX, fY, iSp, clTreePopulation::adult, fDiam );
          p_oPop->CreateTree( fX, fY, iSp, clTreePopulation::adult, fDiam );
        }
      }
    }

    //Verify proportion of mortality and probability of mortality
    p_oTemp = p_oSimManager->GetBehaviorObject( "aggregatedmortshell" );
    p_oAggMort = dynamic_cast<clAggregatedMortality*>(p_oTemp);
    fTemp = p_oAggMort->GetMortalityEpisodeProbability();
    EXPECT_LT(fabs(fTemp - 1), 0.001);
    fTemp = p_oAggMort->GetTreeMortalityProb();
    EXPECT_LT(fabs(fTemp - 0.015425), 0.001);

    //Set up the array for counting trees in each cell
    p_iNumCellTrees = new int*[iNumXCells];
    for (iX = 0; iX < iNumXCells; iX++) {
      p_iNumCellTrees[iX] = new int[iNumYCells];
      for (iY = 0; iY < iNumYCells; iY++)
        p_iNumCellTrees[iX][iY] = 0;
    }

    p_oSimManager->RunSim( 1 );

    for (iSp = 0; iSp < iNumSpecies; iSp++)
      p_iNumTrees[iSp] = 0;

    //Get all trees and count them into their cells
    p_oAllTrees = p_oPop->Find( "all" );
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
      p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
      iX = (int)(fX / fCellLength);
      iY = (int)(fY / fCellLength);
      p_iNumCellTrees[iX][iY]++;
      p_iNumTrees[p_oTree->GetSpecies()]++;
      p_oTree = p_oAllTrees->NextTree();
    }

    //Verify that all cells hold either 9, 5, or 1 trees; count the ones that
    //hold 5, count twice the ones that hold 1
    iTemp = 0;
    for (iX = 0; iX < iNumXCells; iX++) {
      for (iY = 0; iY < iNumYCells; iY++) {
        EXPECT_TRUE(9 == p_iNumCellTrees[iX][iY] ||
            5 == p_iNumCellTrees[iX][iY] ||
            1 == p_iNumCellTrees[iX][iY]);
        if (5 == p_iNumCellTrees[iX][iY])
          iTemp++;
        else if (1 == p_iNumCellTrees[iX][iY])
          iTemp+=2;
      }
    }

    EXPECT_TRUE(iTemp >= 17 && iTemp <= 25);

    //Make sure there are the right number of trees, and that they didn't
    //all come from one species
    iTemp = 0;
    for (iSp = 0; iSp < iNumSpecies; iSp++) iTemp += p_iNumTrees[iSp];
    iExpected = 1216;
    EXPECT_LT(fabs(iExpected - iTemp)/iExpected, 0.1);
    EXPECT_EQ(iTemp % 4, 0);
    EXPECT_LT(432 > p_iNumTrees[0] && 0, p_iNumTrees[0]);
    EXPECT_LT(432 > p_iNumTrees[1] && 0, p_iNumTrees[1]);
    EXPECT_LT(432 > p_iNumTrees[2] && 0, p_iNumTrees[2]);

    //Run another timestep, and make sure it happens correctly again
    p_oSimManager->RunSim( 1 );

    for (iSp = 0; iSp < iNumSpecies; iSp++)
      p_iNumTrees[iSp] = 0;

    //Get all trees and count them into their cells
    // for (iX = 0; iX < iNumXCells; iX++)
    //    for (iY = 0; iY < iNumYCells; iY++)
    //      p_iNumCellTrees[iX][iY] = 0;

    p_oAllTrees = p_oPop->Find( "all" );
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      //    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
      //    p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
      //    iX = (int)(fX / fCellLength);
      //    iY = (int)(fY / fCellLength);
      //    p_iNumCellTrees[iX][iY]++;
      p_iNumTrees[p_oTree->GetSpecies()]++;
      p_oTree = p_oAllTrees->NextTree();
    }

    //Verify that all cells hold either 9, 5, or 1 trees
    /*  for (iX = 0; iX < iNumXCells; iX++) {
    for (iY = 0; iY < iNumYCells; iY++) {
      CPPUNIT_ASSERT(9 == p_iNumCellTrees[iX][iY] ||
                     5 == p_iNumCellTrees[iX][iY] ||
                     1 == p_iNumCellTrees[iX][iY]);
    }
  }*/

    //Make sure there are the right number of trees, and that they didn't
    //all come from one species
    iTemp = 0;
    for (iSp = 0; iSp < iNumSpecies; iSp++) iTemp += p_iNumTrees[iSp];
    iExpected = 1141;
    EXPECT_EQ((1296 - iTemp) % 4, 0);
    EXPECT_LT(fabs(iExpected - iTemp)/iExpected, 0.1);
    EXPECT_LT(432 > p_iNumTrees[0] && 0, p_iNumTrees[0]);
    EXPECT_LT(432 > p_iNumTrees[1] && 0, p_iNumTrees[1]);
    EXPECT_LT(432 > p_iNumTrees[2] && 0, p_iNumTrees[2]);

    delete[] p_iNumTrees;
    for (iX = 0; iX < iNumXCells; iX++)
      delete[] p_iNumCellTrees[iX];

    delete[] p_iNumCellTrees;
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete[] p_iNumTrees;
    for (int iX = 0; iX < iNumXCells; iX++)
      delete[] p_iNumCellTrees[iX];

    delete[] p_iNumCellTrees;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun2()
/////////////////////////////////////////////////////////////////////////////
TEST(AggregatedMortality, TestNormalProcessingRun2)
{
  using namespace std;
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );

  clTreePopulation * p_oPop;
  clTreeSearch * p_oAllTrees;
  clTree * p_oTree;
  float fX, fY, fDiam, fCellLength;
  int **p_iNumCellTrees;
  int *p_iNumTrees;
  int iSp, iNumXCells, iNumYCells, iX, iY, iNumSpecies = 3, iTemp,
      iXMinus, iXPlus, iYMinus, iYPlus, iExpected;
  try {
    p_iNumTrees = new int[iNumSpecies];

    //Feed our file to the sim manager
    p_oSimManager->ReadFile( WriteAggregatedMortalityXMLFile2() );

    //Get the tree population
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Put two trees in the center of each grid cell
    fCellLength = p_oPop->GetGridCellSize();
    iNumXCells = p_oPop->GetNumXCells();
    iNumYCells = p_oPop->GetNumYCells();
    fDiam = 20;
    for (iX = 0; iX < iNumXCells; iX++) {
      fX = (iX * fCellLength) + (fCellLength / 2);
      for (iY = 0; iY < iNumYCells; iY++) {
        fY = (iY * fCellLength) + (fCellLength / 2);
        p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, fDiam );
        p_oPop->CreateTree( fX, fY, 1, clTreePopulation::adult, fDiam );
      }
    }

    //Set up the array for counting trees in each cell
    p_iNumCellTrees = new int*[iNumXCells];
    for (iX = 0; iX < iNumXCells; iX++) {
      p_iNumCellTrees[iX] = new int[iNumYCells];
      for (iY = 0; iY < iNumYCells; iY++)
        p_iNumCellTrees[iX][iY] = 0;
    }

    p_oSimManager->RunSim( 1 );

    for (iSp = 0; iSp < iNumSpecies; iSp++)
      p_iNumTrees[iSp] = 0;

    //Get all trees and count them into their cells
    p_oAllTrees = p_oPop->Find( "all" );
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
      p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
      iX = (int)(fX / fCellLength);
      iY = (int)(fY / fCellLength);
      p_iNumCellTrees[iX][iY]++;
      p_iNumTrees[p_oTree->GetSpecies()]++;
      p_oTree = p_oAllTrees->NextTree();
    }

    //Verify that all cells hold either 2 or 0 trees; count the ones that
    //hold 0
    iTemp = 0;
    for (iX = 0; iX < iNumXCells; iX++) {
      for (iY = 0; iY < iNumYCells; iY++) {
        EXPECT_TRUE(2 == p_iNumCellTrees[iX][iY] ||
            0 == p_iNumCellTrees[iX][iY]);
        if (0 == p_iNumCellTrees[iX][iY])
          iTemp++;
      }
    }

    EXPECT_EQ(iTemp % 3, 0);

    //Find a 0 cell, and make sure that one other touches it (all three should
    //touch but this will work because we probably won't find the center cell
    //first)
    iTemp = 0;
    for (iX = 0; iX < iNumXCells; iX++) {
      for (iY = 0; iY < iNumYCells; iY++) {
        if (0 == p_iNumCellTrees[iX][iY]) {
          iTemp = 1;
          break;
        }
      }
      if (1 == iTemp)
        break;
    }

    if (0 == iX) {
      iXMinus = iNumXCells - 1;
      iXPlus = iX + 1;
    }
    else if (iNumXCells - 1 == iX) {
      iXMinus = iX - 1;
      iXPlus = 0;
    }
    else {
      iXMinus = iX - 1;
      iXPlus = iX + 1;
    }

    if (0 == iY) {
      iYMinus = iNumYCells - 1;
      iYPlus = iY + 1;
    }
    else if (iNumYCells - 1 == iY) {
      iYMinus = iY - 1;
      iYPlus = 0;
    }
    else {
      iYMinus = iY - 1;
      iYPlus = iY + 1;
    }

    EXPECT_TRUE(0 == p_iNumCellTrees[iXMinus][iYMinus] ||
        0 == p_iNumCellTrees[iX][iYMinus] ||
        0 == p_iNumCellTrees[iXPlus][iYMinus] ||
        0 == p_iNumCellTrees[iXMinus][iY] ||
        0 == p_iNumCellTrees[iXPlus][iY] ||
        0 == p_iNumCellTrees[iXMinus][iYPlus] ||
        0 == p_iNumCellTrees[iX][iYPlus] ||
        0 == p_iNumCellTrees[iXPlus][iYPlus]);


    //Make sure there are the right number of trees
    iTemp = 0;
    for (iSp = 0; iSp < iNumSpecies; iSp++) iTemp += p_iNumTrees[iSp];
    iExpected = 282;
    EXPECT_LT(fabs(iExpected - iTemp) / iExpected, 0.1);

    delete[] p_iNumTrees;
    for (iX = 0; iX < iNumXCells; iX++)
      delete[] p_iNumCellTrees[iX];

    delete[] p_iNumCellTrees;
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete[] p_iNumTrees;
    for (iX = 0; iX < iNumXCells; iX++)
      delete[] p_iNumCellTrees[iX];

    delete[] p_iNumCellTrees;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}


/////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun3()
/////////////////////////////////////////////////////////////////////////////
TEST(AggregatedMortality, TestNormalProcessingRun3)
{
  using namespace std;
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  clTreePopulation * p_oPop;
  clTreeSearch * p_oAllTrees;
  clTree * p_oTree;
  float fX, fY, fDiam, fCellLength;
  int *p_iNumAdults, *p_iNumSaplings;
  int iSp, iNumXCells, iNumYCells, iX, iY, iNumSpecies = 3, iExpected, iTemp,
      iIsDead;

  try {
    p_iNumAdults = new int[iNumSpecies];
    p_iNumSaplings = new int[iNumSpecies];

    //Feed our file to the sim manager
    p_oSimManager->ReadFile( WriteAggregatedMortalityXMLFile3() );

    //Get the tree population
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Put the following trees in the center of each grid cell:
    //Three adult trees of each species
    //One sapling of each species
    //One dead adult of each species
    fCellLength = p_oPop->GetGridCellSize();
    iNumXCells = p_oPop->GetNumXCells();
    iNumYCells = p_oPop->GetNumYCells();
    iIsDead = natural;
    for (iX = 0; iX < iNumXCells; iX++) {
      fX = (iX * fCellLength) + (fCellLength / 2);
      for (iY = 0; iY < iNumYCells; iY++) {
        fY = (iY * fCellLength) + (fCellLength / 2);
        for (iSp = 0; iSp < iNumSpecies; iSp++) {
          fDiam = 20;
          p_oPop->CreateTree( fX, fY, iSp, clTreePopulation::adult, fDiam );
          p_oPop->CreateTree( fX, fY, iSp, clTreePopulation::adult, fDiam );
          p_oPop->CreateTree( fX, fY, iSp, clTreePopulation::adult, fDiam );

          p_oTree = p_oPop->CreateTree( fX, fY, iSp, clTreePopulation::adult, fDiam );
          p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iIsDead);

          fDiam = 4.0;
          p_oPop->CreateTree( fX, fY, iSp, clTreePopulation::sapling, fDiam );
        }
      }
    }

    p_oSimManager->RunSim( 1 );

    for (iSp = 0; iSp < iNumSpecies; iSp++) {
      p_iNumAdults[iSp] = 0;
      p_iNumSaplings[iSp] = 0;
    }

    //Get all trees and count them by species and type
    p_oAllTrees = p_oPop->Find( "all" );
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      if (p_oTree->GetType() == clTreePopulation::adult)
        p_iNumAdults[p_oTree->GetSpecies()]++;
      else if (p_oTree->GetType() == clTreePopulation::sapling)
        p_iNumSaplings[p_oTree->GetSpecies()]++;
      else
        FAIL() << "Found unexpected tree type in run 3.";

      p_oTree = p_oAllTrees->NextTree();
    }

    //Make sure that no trees of species 2 were killed
    EXPECT_EQ(p_iNumAdults[1], 432);
    EXPECT_EQ(p_iNumSaplings[1], 144);

    //Make sure we still have all of our species 3 saplings
    EXPECT_EQ(p_iNumSaplings[2], 144);

    //Make sure that there are about 756 trees left in the pool
    iTemp = p_iNumAdults[0] + p_iNumAdults[2] + p_iNumSaplings[0];
    iExpected = 756;
    EXPECT_EQ((1008 - iTemp) % 8, 0);
    EXPECT_LT(fabs(iExpected - iTemp)/iExpected, 0.15);

    //Now kill all the pool trees - to make sure the behavior can handle it
    p_oAllTrees->StartOver();
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      if (0 == p_oTree->GetSpecies() ||
          (2 == p_oTree->GetSpecies() && clTreePopulation::adult == p_oTree->GetType()))
        p_oPop->KillTree(p_oTree, natural);

      p_oTree = p_oAllTrees->NextTree();
    }

    //Run another timestep
    p_oSimManager->RunSim( 1 );

    for (iSp = 0; iSp < iNumSpecies; iSp++) {
      p_iNumAdults[iSp] = 0;
      p_iNumSaplings[iSp] = 0;
    }

    //Get all trees and count them by species and type
    p_oAllTrees = p_oPop->Find( "all" );
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      if (p_oTree->GetType() == clTreePopulation::adult)
        p_iNumAdults[p_oTree->GetSpecies()]++;
      else if (p_oTree->GetType() == clTreePopulation::sapling)
        p_iNumSaplings[p_oTree->GetSpecies()]++;
      else
        FAIL() << "Found unexpected tree type in run 3.";

      p_oTree = p_oAllTrees->NextTree();
    }

    //Make sure that no trees of species 2 were killed
    EXPECT_EQ(p_iNumAdults[1], 432);
    EXPECT_EQ(p_iNumSaplings[1], 144);

    EXPECT_EQ(p_iNumAdults[0], 0);
    EXPECT_EQ(p_iNumAdults[2], 0);
    EXPECT_EQ(p_iNumSaplings[0], 0);
    EXPECT_EQ(p_iNumSaplings[2], 144);

    delete[] p_iNumAdults;
    delete[] p_iNumSaplings;
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete[] p_iNumAdults;
    delete[] p_iNumSaplings;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun4()
/////////////////////////////////////////////////////////////////////////////
TEST(AggregatedMortality, TestNormalProcessingRun4)
{
  using namespace std;
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTreeSearch * p_oAllTrees;
    clTree * p_oTree;
    float fX, fY, fDiam, fCellLength;
    int iNumTrees, iSp, iNumXCells, iNumYCells, iX, iY;

    //Feed our file to the sim manager
    p_oSimManager->ReadFile( WriteAggregatedMortalityXMLFile4() );

    //Get the tree population
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Put one tree in the center of every other grid cell
    fCellLength = p_oPop->GetGridCellSize();
    iNumXCells = p_oPop->GetNumXCells();
    iNumYCells = p_oPop->GetNumYCells();
    fDiam = 20;
    for (iX = 0; iX < iNumXCells; iX+=2) {
      fX = (iX * fCellLength) + (fCellLength / 2);
      for (iY = 0; iY < iNumYCells; iY++) {
        fY = (iY * fCellLength) + (fCellLength / 2);

        iSp = (iY % 2) + 1;
        p_oPop->CreateTree( fX, fY, iSp, clTreePopulation::adult, fDiam );
      }
    }

    p_oSimManager->RunSim( 1 );

    //Get all trees and count them
    iNumTrees = 0;
    p_oAllTrees = p_oPop->Find( "all" );
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      iNumTrees++;
      p_oTree = p_oAllTrees->NextTree();
    }

    //Verify that 18 trees are missing
    EXPECT_EQ((72 - iNumTrees) % 6, 0);
    EXPECT_LT(fabs(54 - iNumTrees)/54, 0.2);
    delete p_oSimManager;

  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun5()
/////////////////////////////////////////////////////////////////////////////
TEST(AggregatedMortality, TestNormalProcessingRun5)
{
  using namespace std;
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTreeSearch * p_oAllTrees;
    clTree * p_oTree;
    float fX, fY, fDiam, fCellLength;
    int iNumTrees, iSp, iNumXCells, iNumYCells, iX, iY, iNumSpecies = 3,
        iExpected;

    //Feed our file to the sim manager
    p_oSimManager->ReadFile( WriteAggregatedMortalityXMLFile5() );

    //Get the tree population
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Put three trees of each species in the center of each grid cell
    fCellLength = p_oPop->GetGridCellSize();
    iNumXCells = p_oPop->GetNumXCells();
    iNumYCells = p_oPop->GetNumYCells();
    fDiam = 20;
    for (iX = 0; iX < iNumXCells; iX++) {
      fX = (iX * fCellLength) + (fCellLength / 2);
      for (iY = 0; iY < iNumYCells; iY++) {
        fY = (iY * fCellLength) + (fCellLength / 2);
        for (iSp = 0; iSp < iNumSpecies; iSp++) {
          p_oPop->CreateTree( fX, fY, iSp, clTreePopulation::adult, fDiam );
          p_oPop->CreateTree( fX, fY, iSp, clTreePopulation::adult, fDiam );
          p_oPop->CreateTree( fX, fY, iSp, clTreePopulation::adult, fDiam );
        }
      }
    }

    p_oSimManager->RunSim( 1 );

    //Count the trees
    iNumTrees = 0;
    p_oAllTrees = p_oPop->Find( "all" );
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      iNumTrees++;
      p_oTree = p_oAllTrees->NextTree();
    }

    //Verify that there are the correct number left
    iExpected = 868;
    EXPECT_LT(fabs(iExpected - iNumTrees)/iExpected, 0.1);

    //Run another timestep, and make sure it happens correctly again
    p_oSimManager->RunSim( 1 );

    iNumTrees = 0;

    p_oAllTrees = p_oPop->Find( "all" );
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      iNumTrees++;
      p_oTree = p_oAllTrees->NextTree();
    }

    //Verify that there are the correct number left
    iExpected = 582;
    EXPECT_LT(fabs(iExpected - iNumTrees)/iExpected, 0.1);
    delete p_oSimManager;

  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun6()
/////////////////////////////////////////////////////////////////////////////
TEST(AggregatedMortality, TestNormalProcessingRun6)
{

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clBehaviorBase * p_oTemp;
    clAggregatedMortality * p_oAggMort;
    float fTemp;

    //Feed our file to the sim manager
    p_oSimManager->ReadFile( WriteAggregatedMortalityXMLFile6() );

    //Get the aggregated mortality object so we can check its probability
    //of a mortality episode
    p_oTemp = p_oSimManager->GetBehaviorObject( "aggregatedmortshell" );
    p_oAggMort = dynamic_cast<clAggregatedMortality*>(p_oTemp);

    fTemp = p_oAggMort->GetMortalityEpisodeProbability();

    EXPECT_LT(fabs(fTemp - 0.6667), 0.001);

    fTemp = p_oAggMort->GetTreeMortalityProb();

    EXPECT_LT(fabs(fTemp - 0.5511), 0.001);
    delete p_oSimManager;

  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// WriteAggregatedMortalityXMLFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteAggregatedMortalityXMLFile1()
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

  WriteAggregatedMortalityCommonStuff(oOut);

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>AggregatedMortality</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>RemoveDead</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "</behavior>"
      << "</behaviorList>"
      << "<AggregatedMortality1>"
      << "<mo_aggReturnInterval>1</mo_aggReturnInterval>"
      << "<mo_aggPropTreesToKill>0.0617</mo_aggPropTreesToKill>"
      << "<mo_aggNumTreesToClump>4</mo_aggNumTreesToClump>"
      << "<mo_aggClumpSizeDeterministic>1</mo_aggClumpSizeDeterministic>"
      << "</AggregatedMortality1>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteAggregatedMortalityXMLFile2()
/////////////////////////////////////////////////////////////////////////////
const char* WriteAggregatedMortalityXMLFile2()
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

  WriteAggregatedMortalityCommonStuff(oOut);

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>AggregatedMortality</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>RemoveDead</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "</behavior>"
      << "</behaviorList>"
      << "<AggregatedMortality1>"
      << "<mo_aggReturnInterval>1</mo_aggReturnInterval>"
      << "<mo_aggPropTreesToKill>0.02083</mo_aggPropTreesToKill>"
      << "<mo_aggNumTreesToClump>6</mo_aggNumTreesToClump>"
      << "<mo_aggClumpSizeDeterministic>1</mo_aggClumpSizeDeterministic>"
      << "</AggregatedMortality1>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteAggregatedMortalityXMLFile3()
/////////////////////////////////////////////////////////////////////////////
const char* WriteAggregatedMortalityXMLFile3()
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

  WriteAggregatedMortalityCommonStuff(oOut);

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>StochasticMortality</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>AggregatedMortality</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>RemoveDead</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>3</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "</behavior>"
      << "</behaviorList>"
      << "<StochasticMortality1>"
      << "<mo_stochasticMortRate>"
      << "<mo_smrVal species=\"Species_3\">0.0</mo_smrVal>"
      << "<mo_smrVal species=\"Species_2\">0.0</mo_smrVal>"
      << "</mo_stochasticMortRate>"
      << "</StochasticMortality1>"
      << "<AggregatedMortality2>"
      << "<mo_aggReturnInterval>1</mo_aggReturnInterval>"
      << "<mo_aggPropTreesToKill>0.25</mo_aggPropTreesToKill>"
      << "<mo_aggNumTreesToClump>8</mo_aggNumTreesToClump>"
      << "<mo_aggClumpSizeDeterministic>1</mo_aggClumpSizeDeterministic>"
      << "</AggregatedMortality2>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteAggregatedMortalityXMLFile4()
/////////////////////////////////////////////////////////////////////////////
const char* WriteAggregatedMortalityXMLFile4()
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

  WriteAggregatedMortalityCommonStuff(oOut);

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>AggregatedMortality</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>RemoveDead</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "</behavior>"
      << "</behaviorList>"
      << "<AggregatedMortality1>"
      << "<mo_aggReturnInterval>1</mo_aggReturnInterval>"
      << "<mo_aggPropTreesToKill>0.25</mo_aggPropTreesToKill>"
      << "<mo_aggNumTreesToClump>6</mo_aggNumTreesToClump>"
      << "<mo_aggClumpSizeDeterministic>1</mo_aggClumpSizeDeterministic>"
      << "</AggregatedMortality1>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteAggregatedMortalityXMLFile5()
/////////////////////////////////////////////////////////////////////////////
const char* WriteAggregatedMortalityXMLFile5()
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

  WriteAggregatedMortalityCommonStuff(oOut);

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>AggregatedMortality</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>RemoveDead</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "</behavior>"
      << "</behaviorList>"
      << "<AggregatedMortality1>"
      << "<mo_aggReturnInterval>1</mo_aggReturnInterval>"
      << "<mo_aggPropTreesToKill>0.33</mo_aggPropTreesToKill>"
      << "<mo_aggNumTreesToClump>1</mo_aggNumTreesToClump>"
      << "<mo_aggClumpSizeDeterministic>1</mo_aggClumpSizeDeterministic>"
      << "</AggregatedMortality1>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteAggregatedMortalityXMLFile6()
/////////////////////////////////////////////////////////////////////////////
const char* WriteAggregatedMortalityXMLFile6()
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
      << "<yearsPerTimestep>2</yearsPerTimestep>";

  WriteAggregatedMortalityCommonStuff(oOut);

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>AggregatedMortality</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>RemoveDead</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "</behavior>"
      << "</behaviorList>"
      << "<AggregatedMortality1>"
      << "<mo_aggReturnInterval>3</mo_aggReturnInterval>"
      << "<mo_aggPropTreesToKill>0.33</mo_aggPropTreesToKill>"
      << "<mo_aggNumTreesToClump>1</mo_aggNumTreesToClump>"
      << "<mo_aggClumpSizeDeterministic>1</mo_aggClumpSizeDeterministic>"
      << "</AggregatedMortality1>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteAggregatedMortalityXMLErrorFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteAggregatedMortalityXMLErrorFile1()
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

  WriteAggregatedMortalityCommonStuff(oOut);

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>AggregatedMortality</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>RemoveDead</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "</behaviorList>"
      << "<AggregatedMortality1>"
      << "<mo_aggReturnInterval>1</mo_aggReturnInterval>"
      << "<mo_aggPropTreesToKill>6.7</mo_aggPropTreesToKill>"
      << "<mo_aggNumTreesToClump>4</mo_aggNumTreesToClump>"
      << "<mo_aggClumpSizeDeterministic>0</mo_aggClumpSizeDeterministic>"
      << "</AggregatedMortality1>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteAggregatedMortalityXMLErrorFile2()
/////////////////////////////////////////////////////////////////////////////
const char* WriteAggregatedMortalityXMLErrorFile2()
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

  WriteAggregatedMortalityCommonStuff(oOut);

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>AggregatedMortality</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>RemoveDead</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "</behaviorList>"
      << "<AggregatedMortality1>"
      << "<mo_aggReturnInterval>-1</mo_aggReturnInterval>"
      << "<mo_aggPropTreesToKill>0.0617</mo_aggPropTreesToKill>"
      << "<mo_aggNumTreesToClump>4</mo_aggNumTreesToClump>"
      << "<mo_aggClumpSizeDeterministic>0</mo_aggClumpSizeDeterministic>"
      << "</AggregatedMortality1>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteAggregatedMortalityCommonStuff()
/////////////////////////////////////////////////////////////////////////////
void WriteAggregatedMortalityCommonStuff(std::fstream &oOut)
{
  using namespace std;
  oOut << "<randomSeed>10</randomSeed>"
      << "<plot_lenX>96</plot_lenX>"
      << "<plot_lenY>96</plot_lenY>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88171785</plot_temp_C>"
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
      << "<tr_madVal species=\"Species_1\">5</tr_madVal>"
      << "<tr_madVal species=\"Species_2\">5</tr_madVal>"
      << "<tr_madVal species=\"Species_3\">5</tr_madVal>"
      << "</tr_minAdultDBH>"
      << "<tr_maxSeedlingHeight>"
      << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Species_2\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Species_3\">1.35</tr_mshVal>"
      << "</tr_maxSeedlingHeight>"
      << "</trees>"
      << "<allometry>"
      << "<tr_slopeOfAsymHeight>"
      << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
      << "<tr_soahVal species=\"Species_2\">0.0299</tr_soahVal>"
      << "<tr_soahVal species=\"Species_3\">0.0299</tr_soahVal>"
      << "</tr_slopeOfAsymHeight>"
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
      << "</allometry>";
}
