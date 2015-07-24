//---------------------------------------------------------------------------
// TestRandomBrowse.cpp
//---------------------------------------------------------------------------
#include "TestRandomBrowse.h"
#include <gtest/gtest.h>
#include "SimManager.h"
#include "TreePopulation.h"
#include <fstream>
#include <math.h>

/////////////////////////////////////////////////////////////////////////////
// TestNormalRun1()
// Tests normal processing run 1.
// First run: WriteRandomBrowseXMLFile1() creates the parameter file. The file
// has the following characteristics:
//
// -- Timestep length of 1 year.
// -- 5 species: Species 1, Species 2, Species 3, Species 4, Species 5.
// -- Random browse behavior applied to seedlings and saplings of Species
//    1, 4 and 5, and seedlings of species 3.
//
// The function does the following:
// -- 1000 trees are created of each tree species/type combination for
//    seedlings, saplings, and adults.
// -- The model is run for 1 timestep.
// -- The number browsed are counted.
// -- The counts are compared to expected results, give or take 5%.
// -- The model is run for another timestep.
// -- The number browsed is expected to be roughly the same, but not exactly
//    the same (i.e. a new set of browsed individuals has been chosen).
/////////////////////////////////////////////////////////////////////////////
TEST(RandomBrowse, TestNormalRun1) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTreeSearch *p_oAllTrees;
    clTree *p_oTree;
    int iSp, iTp, iCode, iNumBrowsed, iNumUnbrowsed, iNumExpectedBrowsed,
    iNumExpectedUnbrowsed, i;
    bool bVal;

    //******************************************
    // Timestep 1
    //******************************************
    //Create the sim manager and load our file
    p_oSimManager->ReadFile( WriteRandomBrowseXMLFile1() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create 1000 of each kind of tree
    for (i = 0; i < 1000; i++) {

      //Seedlings of Species 1
      p_oTree = p_oPop->CreateTree(1, 1, 0, clTreePopulation::seedling, 0);

      //Saplings of Species 1
      p_oTree = p_oPop->CreateTree(1, 1, 0, clTreePopulation::sapling, 7);

      //Adults of Species 1
      p_oTree = p_oPop->CreateTree(1, 1, 0, clTreePopulation::adult, 17);

      //Seedlings of Species 2
      p_oTree = p_oPop->CreateTree(1, 1, 1, clTreePopulation::seedling, 0);

      //Saplings of Species 2
      p_oTree = p_oPop->CreateTree(1, 1, 1, clTreePopulation::sapling, 7);

      //Adults of Species 2
      p_oTree = p_oPop->CreateTree(1, 1, 1, clTreePopulation::adult, 17);

      //Seedlings of Species 3
      p_oTree = p_oPop->CreateTree(1, 1, 2, clTreePopulation::seedling, 0);

      //Saplings of Species 3
      p_oTree = p_oPop->CreateTree(1, 1, 2, clTreePopulation::sapling, 7);

      //Adults of Species 3
      p_oTree = p_oPop->CreateTree(1, 1, 2, clTreePopulation::adult, 17);

      //Seedlings of Species 4
      p_oTree = p_oPop->CreateTree(1, 1, 3, clTreePopulation::seedling, 0);

      //Saplings of Species 4
      p_oTree = p_oPop->CreateTree(1, 1, 3, clTreePopulation::sapling, 7);

      //Adults of Species 4
      p_oTree = p_oPop->CreateTree(1, 1, 3, clTreePopulation::adult, 17);

      //Seedlings of Species 5
      p_oTree = p_oPop->CreateTree(1, 1, 4, clTreePopulation::seedling, 0);

      //Saplings of Species 5
      p_oTree = p_oPop->CreateTree(1, 1, 4, clTreePopulation::sapling, 7);

      //Adults of Species 5
      p_oTree = p_oPop->CreateTree(1, 1, 4, clTreePopulation::adult, 17);
    }

    //Run for one timestep
    p_oSimManager->RunSim(1);
    p_oAllTrees = p_oPop->Find("all");

    //Seedlings of Species 1
    iSp = 0; iTp = clTreePopulation::seedling;
    iNumExpectedBrowsed = 330;
    iNumExpectedUnbrowsed = 670;
    iCode = p_oPop->GetBoolDataCode("Browsed", iSp, iTp);
    iNumBrowsed = 0;
    iNumUnbrowsed = 0;
    p_oTree = p_oAllTrees->NextTree();

    while (p_oTree) {

      if (p_oTree->GetSpecies() == iSp &&
          p_oTree->GetType() == iTp) {

        p_oTree->GetValue(iCode, &bVal);

        if (bVal) iNumBrowsed++;
        else iNumUnbrowsed++;
      }

      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_LT(fabs(iNumBrowsed - iNumExpectedBrowsed)/iNumBrowsed, 0.05);
    EXPECT_LT(fabs(iNumUnbrowsed - iNumExpectedUnbrowsed)/iNumUnbrowsed, 0.05);

    //Saplings of Species 1
    p_oAllTrees->StartOver();
    iSp = 0; iTp = clTreePopulation::sapling;
    iNumExpectedBrowsed = 330;
    iNumExpectedUnbrowsed = 670;
    iCode = p_oPop->GetBoolDataCode("Browsed", iSp, iTp);
    iNumBrowsed = 0;
    iNumUnbrowsed = 0;
    p_oTree = p_oAllTrees->NextTree();

    while (p_oTree) {

      if (p_oTree->GetSpecies() == iSp &&
          p_oTree->GetType() == iTp) {

        p_oTree->GetValue(iCode, &bVal);

        if (bVal) iNumBrowsed++;
        else iNumUnbrowsed++;
      }

      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_LT(fabs(iNumBrowsed - iNumExpectedBrowsed)/iNumBrowsed, 0.05);
    EXPECT_LT(fabs(iNumUnbrowsed - iNumExpectedUnbrowsed)/iNumUnbrowsed, 0.05);

    //Adults of Species 1
    p_oAllTrees->StartOver();
    iSp = 0; iTp = clTreePopulation::adult;
    iNumExpectedBrowsed = 0;
    iNumExpectedUnbrowsed = 1000;
    iCode = p_oPop->GetBoolDataCode("Browsed", iSp, iTp);
    EXPECT_EQ(-1, iCode);
    iNumBrowsed = 0;
    iNumUnbrowsed = 0;
    p_oTree = p_oAllTrees->NextTree();

    while (p_oTree) {

      if (p_oTree->GetSpecies() == iSp &&
          p_oTree->GetType() == iTp) {

        iNumUnbrowsed++;

      }

      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(iNumBrowsed, iNumExpectedBrowsed);
    EXPECT_EQ(iNumUnbrowsed, iNumExpectedUnbrowsed);

    //Seedlings of Species 2
    p_oAllTrees->StartOver();
    iSp = 1; iTp = clTreePopulation::seedling;
    iNumExpectedBrowsed = 0;
    iNumExpectedUnbrowsed = 1000;
    iCode = p_oPop->GetBoolDataCode("Browsed", iSp, iTp);
    EXPECT_EQ(-1, iCode);
    iNumBrowsed = 0;
    iNumUnbrowsed = 0;
    p_oTree = p_oAllTrees->NextTree();

    while (p_oTree) {

      if (p_oTree->GetSpecies() == iSp &&
          p_oTree->GetType() == iTp) {

        iNumUnbrowsed++;

      }

      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(iNumBrowsed, iNumExpectedBrowsed);
    EXPECT_EQ(iNumUnbrowsed, iNumExpectedUnbrowsed);

    //Saplings of Species 2
    p_oAllTrees->StartOver();
    iSp = 1; iTp = clTreePopulation::sapling;
    iNumExpectedBrowsed = 0;
    iNumExpectedUnbrowsed = 1000;
    iCode = p_oPop->GetBoolDataCode("Browsed", iSp, iTp);
    EXPECT_EQ(-1, iCode);
    iNumBrowsed = 0;
    iNumUnbrowsed = 0;
    p_oTree = p_oAllTrees->NextTree();

    while (p_oTree) {

      if (p_oTree->GetSpecies() == iSp &&
          p_oTree->GetType() == iTp) {

        iNumUnbrowsed++;

      }

      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(iNumBrowsed, iNumExpectedBrowsed);
    EXPECT_EQ(iNumUnbrowsed, iNumExpectedUnbrowsed);

    //Adults of Species 2
    p_oAllTrees->StartOver();
    iSp = 1; iTp = clTreePopulation::adult;
    iNumExpectedBrowsed = 0;
    iNumExpectedUnbrowsed = 1000;
    iCode = p_oPop->GetBoolDataCode("Browsed", iSp, iTp);
    EXPECT_EQ(-1, iCode);
    iNumBrowsed = 0;
    iNumUnbrowsed = 0;
    p_oTree = p_oAllTrees->NextTree();

    while (p_oTree) {

      if (p_oTree->GetSpecies() == iSp &&
          p_oTree->GetType() == iTp) {

        iNumUnbrowsed++;

      }

      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(iNumBrowsed, iNumExpectedBrowsed);
    EXPECT_EQ(iNumUnbrowsed, iNumExpectedUnbrowsed);

    //Seedlings of Species 3
    p_oAllTrees->StartOver();
    iSp = 2; iTp = clTreePopulation::seedling;
    iNumExpectedBrowsed = 1000;
    iNumExpectedUnbrowsed = 0;
    iCode = p_oPop->GetBoolDataCode("Browsed", iSp, iTp);
    iNumBrowsed = 0;
    iNumUnbrowsed = 0;
    p_oTree = p_oAllTrees->NextTree();

    while (p_oTree) {

      if (p_oTree->GetSpecies() == iSp &&
          p_oTree->GetType() == iTp) {

        p_oTree->GetValue(iCode, &bVal);

        if (bVal) iNumBrowsed++;
        else iNumUnbrowsed++;
      }

      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(iNumBrowsed, iNumExpectedBrowsed);
    EXPECT_EQ(iNumUnbrowsed, iNumExpectedUnbrowsed);

    //Saplings of Species 3
    p_oAllTrees->StartOver();
    iSp = 2; iTp = clTreePopulation::sapling;
    iNumExpectedBrowsed = 0;
    iNumExpectedUnbrowsed = 1000;
    iCode = p_oPop->GetBoolDataCode("Browsed", iSp, iTp);
    EXPECT_EQ(-1, iCode);
    iNumBrowsed = 0;
    iNumUnbrowsed = 0;
    p_oTree = p_oAllTrees->NextTree();

    while (p_oTree) {

      if (p_oTree->GetSpecies() == iSp &&
          p_oTree->GetType() == iTp) {

        iNumUnbrowsed++;

      }

      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(iNumBrowsed, iNumExpectedBrowsed);
    EXPECT_EQ(iNumUnbrowsed, iNumExpectedUnbrowsed);

    //Adults of Species 3
    p_oAllTrees->StartOver();
    iSp = 2; iTp = clTreePopulation::adult;
    iNumExpectedBrowsed = 0;
    iNumExpectedUnbrowsed = 1000;
    iCode = p_oPop->GetBoolDataCode("Browsed", iSp, iTp);
    EXPECT_EQ(-1, iCode);
    iNumBrowsed = 0;
    iNumUnbrowsed = 0;
    p_oTree = p_oAllTrees->NextTree();

    while (p_oTree) {

      if (p_oTree->GetSpecies() == iSp &&
          p_oTree->GetType() == iTp) {

        iNumUnbrowsed++;

      }

      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(iNumBrowsed, iNumExpectedBrowsed);
    EXPECT_EQ(iNumUnbrowsed, iNumExpectedUnbrowsed);

    //Seedlings of Species 4
    p_oAllTrees->StartOver();
    iSp = 3; iTp = clTreePopulation::seedling;
    iNumExpectedBrowsed = 0;
    iNumExpectedUnbrowsed = 1000;
    iCode = p_oPop->GetBoolDataCode("Browsed", iSp, iTp);
    iNumBrowsed = 0;
    iNumUnbrowsed = 0;
    p_oTree = p_oAllTrees->NextTree();

    while (p_oTree) {

      if (p_oTree->GetSpecies() == iSp &&
          p_oTree->GetType() == iTp) {

        p_oTree->GetValue(iCode, &bVal);

        if (bVal) iNumBrowsed++;
        else iNumUnbrowsed++;
      }

      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(iNumBrowsed, iNumExpectedBrowsed);
    EXPECT_EQ(iNumUnbrowsed, iNumExpectedUnbrowsed);

    //Saplings of Species 4
    p_oAllTrees->StartOver();
    iSp = 3; iTp = clTreePopulation::sapling;
    iNumExpectedBrowsed = 0;
    iNumExpectedUnbrowsed = 1000;
    iCode = p_oPop->GetBoolDataCode("Browsed", iSp, iTp);
    iNumBrowsed = 0;
    iNumUnbrowsed = 0;
    p_oTree = p_oAllTrees->NextTree();

    while (p_oTree) {

      if (p_oTree->GetSpecies() == iSp &&
          p_oTree->GetType() == iTp) {

        p_oTree->GetValue(iCode, &bVal);

        if (bVal) iNumBrowsed++;
        else iNumUnbrowsed++;
      }

      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(iNumBrowsed, iNumExpectedBrowsed);
    EXPECT_EQ(iNumUnbrowsed, iNumExpectedUnbrowsed);

    //Adults of Species 4
    p_oAllTrees->StartOver();
    iSp = 3; iTp = clTreePopulation::adult;
    iNumExpectedBrowsed = 0;
    iNumExpectedUnbrowsed = 1000;
    iCode = p_oPop->GetBoolDataCode("Browsed", iSp, iTp);
    EXPECT_EQ(-1, iCode);
    iNumBrowsed = 0;
    iNumUnbrowsed = 0;
    p_oTree = p_oAllTrees->NextTree();

    while (p_oTree) {

      if (p_oTree->GetSpecies() == iSp &&
          p_oTree->GetType() == iTp) {

        iNumUnbrowsed++;

      }

      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(iNumBrowsed, iNumExpectedBrowsed);
    EXPECT_EQ(iNumUnbrowsed, iNumExpectedUnbrowsed);

    //Seedlings of Species 5
    p_oAllTrees->StartOver();
    iSp = 4; iTp = clTreePopulation::seedling;
    iNumExpectedBrowsed = 660;
    iNumExpectedUnbrowsed = 340;
    iCode = p_oPop->GetBoolDataCode("Browsed", iSp, iTp);
    iNumBrowsed = 0;
    iNumUnbrowsed = 0;
    p_oTree = p_oAllTrees->NextTree();

    while (p_oTree) {

      if (p_oTree->GetSpecies() == iSp &&
          p_oTree->GetType() == iTp) {

        p_oTree->GetValue(iCode, &bVal);

        if (bVal) iNumBrowsed++;
        else iNumUnbrowsed++;
      }

      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_LT(fabs(iNumBrowsed - iNumExpectedBrowsed)/iNumBrowsed, 0.05);
    EXPECT_LT(fabs(iNumUnbrowsed - iNumExpectedUnbrowsed)/iNumUnbrowsed, 0.05);

    //Saplings of Species 5
    p_oAllTrees->StartOver();
    iSp = 4; iTp = clTreePopulation::sapling;
    iNumExpectedBrowsed = 660;
    iNumExpectedUnbrowsed = 340;
    iCode = p_oPop->GetBoolDataCode("Browsed", iSp, iTp);
    iNumBrowsed = 0;
    iNumUnbrowsed = 0;
    p_oTree = p_oAllTrees->NextTree();

    while (p_oTree) {

      if (p_oTree->GetSpecies() == iSp &&
          p_oTree->GetType() == iTp) {

        p_oTree->GetValue(iCode, &bVal);

        if (bVal) iNumBrowsed++;
        else iNumUnbrowsed++;
      }

      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_LT(fabs(iNumBrowsed - iNumExpectedBrowsed)/iNumBrowsed, 0.07);
    EXPECT_LT(fabs(iNumUnbrowsed - iNumExpectedUnbrowsed)/iNumUnbrowsed, 0.15);

    //Adults of Species 4
    p_oAllTrees->StartOver();
    iSp = 4; iTp = clTreePopulation::adult;
    iNumExpectedBrowsed = 0;
    iNumExpectedUnbrowsed = 1000;
    iCode = p_oPop->GetBoolDataCode("Browsed", iSp, iTp);
    EXPECT_EQ(-1, iCode);
    iNumBrowsed = 0;
    iNumUnbrowsed = 0;
    p_oTree = p_oAllTrees->NextTree();

    while (p_oTree) {

      if (p_oTree->GetSpecies() == iSp &&
          p_oTree->GetType() == iTp) {

        iNumUnbrowsed++;

      }

      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(iNumBrowsed, iNumExpectedBrowsed);
    EXPECT_EQ(iNumUnbrowsed, iNumExpectedUnbrowsed);


    //******************************************
    // Timestep 2
    //******************************************
    p_oSimManager->RunSim(1);
    p_oAllTrees = p_oPop->Find("all");

    //Seedlings of Species 1
    iSp = 0; iTp = clTreePopulation::seedling;
    iNumExpectedBrowsed = 330;
    iNumExpectedUnbrowsed = 670;
    iCode = p_oPop->GetBoolDataCode("Browsed", iSp, iTp);
    iNumBrowsed = 0;
    iNumUnbrowsed = 0;
    p_oTree = p_oAllTrees->NextTree();

    while (p_oTree) {

      if (p_oTree->GetSpecies() == iSp &&
          p_oTree->GetType() == iTp) {

        p_oTree->GetValue(iCode, &bVal);

        if (bVal) iNumBrowsed++;
        else iNumUnbrowsed++;
      }

      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_LT(fabs(iNumBrowsed - iNumExpectedBrowsed)/iNumBrowsed, 0.05);
    EXPECT_LT(fabs(iNumUnbrowsed - iNumExpectedUnbrowsed)/iNumUnbrowsed, 0.05);

    //Saplings of Species 1
    p_oAllTrees->StartOver();
    iSp = 0; iTp = clTreePopulation::sapling;
    iNumExpectedBrowsed = 330;
    iNumExpectedUnbrowsed = 670;
    iCode = p_oPop->GetBoolDataCode("Browsed", iSp, iTp);
    iNumBrowsed = 0;
    iNumUnbrowsed = 0;
    p_oTree = p_oAllTrees->NextTree();

    while (p_oTree) {

      if (p_oTree->GetSpecies() == iSp &&
          p_oTree->GetType() == iTp) {

        p_oTree->GetValue(iCode, &bVal);

        if (bVal) iNumBrowsed++;
        else iNumUnbrowsed++;
      }

      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_LT(fabs(iNumBrowsed - iNumExpectedBrowsed)/iNumBrowsed, 0.05);
    EXPECT_LT(fabs(iNumUnbrowsed - iNumExpectedUnbrowsed)/iNumUnbrowsed, 0.05);

    //Adults of Species 1
    p_oAllTrees->StartOver();
    iSp = 0; iTp = clTreePopulation::adult;
    iNumExpectedBrowsed = 0;
    iNumExpectedUnbrowsed = 1000;
    iCode = p_oPop->GetBoolDataCode("Browsed", iSp, iTp);
    EXPECT_EQ(-1, iCode);
    iNumBrowsed = 0;
    iNumUnbrowsed = 0;
    p_oTree = p_oAllTrees->NextTree();

    while (p_oTree) {

      if (p_oTree->GetSpecies() == iSp &&
          p_oTree->GetType() == iTp) {

        iNumUnbrowsed++;

      }

      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(iNumBrowsed, iNumExpectedBrowsed);
    EXPECT_EQ(iNumUnbrowsed, iNumExpectedUnbrowsed);

    //Seedlings of Species 2
    p_oAllTrees->StartOver();
    iSp = 1; iTp = clTreePopulation::seedling;
    iNumExpectedBrowsed = 0;
    iNumExpectedUnbrowsed = 1000;
    iCode = p_oPop->GetBoolDataCode("Browsed", iSp, iTp);
    EXPECT_EQ(-1, iCode);
    iNumBrowsed = 0;
    iNumUnbrowsed = 0;
    p_oTree = p_oAllTrees->NextTree();

    while (p_oTree) {

      if (p_oTree->GetSpecies() == iSp &&
          p_oTree->GetType() == iTp) {

        iNumUnbrowsed++;

      }

      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(iNumBrowsed, iNumExpectedBrowsed);
    EXPECT_EQ(iNumUnbrowsed, iNumExpectedUnbrowsed);

    //Saplings of Species 2
    p_oAllTrees->StartOver();
    iSp = 1; iTp = clTreePopulation::sapling;
    iNumExpectedBrowsed = 0;
    iNumExpectedUnbrowsed = 1000;
    iCode = p_oPop->GetBoolDataCode("Browsed", iSp, iTp);
    EXPECT_EQ(-1, iCode);
    iNumBrowsed = 0;
    iNumUnbrowsed = 0;
    p_oTree = p_oAllTrees->NextTree();

    while (p_oTree) {

      if (p_oTree->GetSpecies() == iSp &&
          p_oTree->GetType() == iTp) {

        iNumUnbrowsed++;

      }

      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(iNumBrowsed, iNumExpectedBrowsed);
    EXPECT_EQ(iNumUnbrowsed, iNumExpectedUnbrowsed);

    //Adults of Species 2
    p_oAllTrees->StartOver();
    iSp = 1; iTp = clTreePopulation::adult;
    iNumExpectedBrowsed = 0;
    iNumExpectedUnbrowsed = 1000;
    iCode = p_oPop->GetBoolDataCode("Browsed", iSp, iTp);
    EXPECT_EQ(-1, iCode);
    iNumBrowsed = 0;
    iNumUnbrowsed = 0;
    p_oTree = p_oAllTrees->NextTree();

    while (p_oTree) {

      if (p_oTree->GetSpecies() == iSp &&
          p_oTree->GetType() == iTp) {

        iNumUnbrowsed++;

      }

      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(iNumBrowsed, iNumExpectedBrowsed);
    EXPECT_EQ(iNumUnbrowsed, iNumExpectedUnbrowsed);

    //Seedlings of Species 3
    p_oAllTrees->StartOver();
    iSp = 2; iTp = clTreePopulation::seedling;
    iNumExpectedBrowsed = 1000;
    iNumExpectedUnbrowsed = 0;
    iCode = p_oPop->GetBoolDataCode("Browsed", iSp, iTp);
    iNumBrowsed = 0;
    iNumUnbrowsed = 0;
    p_oTree = p_oAllTrees->NextTree();

    while (p_oTree) {

      if (p_oTree->GetSpecies() == iSp &&
          p_oTree->GetType() == iTp) {

        p_oTree->GetValue(iCode, &bVal);

        if (bVal) iNumBrowsed++;
        else iNumUnbrowsed++;
      }

      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(iNumBrowsed, iNumExpectedBrowsed);
    EXPECT_EQ(iNumUnbrowsed, iNumExpectedUnbrowsed);

    //Saplings of Species 3
    p_oAllTrees->StartOver();
    iSp = 2; iTp = clTreePopulation::sapling;
    iNumExpectedBrowsed = 0;
    iNumExpectedUnbrowsed = 1000;
    iCode = p_oPop->GetBoolDataCode("Browsed", iSp, iTp);
    EXPECT_EQ(-1, iCode);
    iNumBrowsed = 0;
    iNumUnbrowsed = 0;
    p_oTree = p_oAllTrees->NextTree();

    while (p_oTree) {

      if (p_oTree->GetSpecies() == iSp &&
          p_oTree->GetType() == iTp) {

        iNumUnbrowsed++;

      }

      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(iNumBrowsed, iNumExpectedBrowsed);
    EXPECT_EQ(iNumUnbrowsed, iNumExpectedUnbrowsed);

    //Adults of Species 3
    p_oAllTrees->StartOver();
    iSp = 2; iTp = clTreePopulation::adult;
    iNumExpectedBrowsed = 0;
    iNumExpectedUnbrowsed = 1000;
    iCode = p_oPop->GetBoolDataCode("Browsed", iSp, iTp);
    EXPECT_EQ(-1, iCode);
    iNumBrowsed = 0;
    iNumUnbrowsed = 0;
    p_oTree = p_oAllTrees->NextTree();

    while (p_oTree) {

      if (p_oTree->GetSpecies() == iSp &&
          p_oTree->GetType() == iTp) {

        iNumUnbrowsed++;

      }

      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(iNumBrowsed, iNumExpectedBrowsed);
    EXPECT_EQ(iNumUnbrowsed, iNumExpectedUnbrowsed);

    //Seedlings of Species 4
    p_oAllTrees->StartOver();
    iSp = 3; iTp = clTreePopulation::seedling;
    iNumExpectedBrowsed = 0;
    iNumExpectedUnbrowsed = 1000;
    iCode = p_oPop->GetBoolDataCode("Browsed", iSp, iTp);
    iNumBrowsed = 0;
    iNumUnbrowsed = 0;
    p_oTree = p_oAllTrees->NextTree();

    while (p_oTree) {

      if (p_oTree->GetSpecies() == iSp &&
          p_oTree->GetType() == iTp) {

        p_oTree->GetValue(iCode, &bVal);

        if (bVal) iNumBrowsed++;
        else iNumUnbrowsed++;
      }

      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(iNumBrowsed, iNumExpectedBrowsed);
    EXPECT_EQ(iNumUnbrowsed, iNumExpectedUnbrowsed);

    //Saplings of Species 4
    p_oAllTrees->StartOver();
    iSp = 3; iTp = clTreePopulation::sapling;
    iNumExpectedBrowsed = 0;
    iNumExpectedUnbrowsed = 1000;
    iCode = p_oPop->GetBoolDataCode("Browsed", iSp, iTp);
    iNumBrowsed = 0;
    iNumUnbrowsed = 0;
    p_oTree = p_oAllTrees->NextTree();

    while (p_oTree) {

      if (p_oTree->GetSpecies() == iSp &&
          p_oTree->GetType() == iTp) {

        p_oTree->GetValue(iCode, &bVal);

        if (bVal) iNumBrowsed++;
        else iNumUnbrowsed++;
      }

      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(iNumBrowsed, iNumExpectedBrowsed);
    EXPECT_EQ(iNumUnbrowsed, iNumExpectedUnbrowsed);

    //Adults of Species 4
    p_oAllTrees->StartOver();
    iSp = 3; iTp = clTreePopulation::adult;
    iNumExpectedBrowsed = 0;
    iNumExpectedUnbrowsed = 1000;
    iCode = p_oPop->GetBoolDataCode("Browsed", iSp, iTp);
    EXPECT_EQ(-1, iCode);
    iNumBrowsed = 0;
    iNumUnbrowsed = 0;
    p_oTree = p_oAllTrees->NextTree();

    while (p_oTree) {

      if (p_oTree->GetSpecies() == iSp &&
          p_oTree->GetType() == iTp) {

        iNumUnbrowsed++;

      }

      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(iNumBrowsed, iNumExpectedBrowsed);
    EXPECT_EQ(iNumUnbrowsed, iNumExpectedUnbrowsed);

    //Seedlings of Species 5
    p_oAllTrees->StartOver();
    iSp = 4; iTp = clTreePopulation::seedling;
    iNumExpectedBrowsed = 660;
    iNumExpectedUnbrowsed = 340;
    iCode = p_oPop->GetBoolDataCode("Browsed", iSp, iTp);
    iNumBrowsed = 0;
    iNumUnbrowsed = 0;
    p_oTree = p_oAllTrees->NextTree();

    while (p_oTree) {

      if (p_oTree->GetSpecies() == iSp &&
          p_oTree->GetType() == iTp) {

        p_oTree->GetValue(iCode, &bVal);

        if (bVal) iNumBrowsed++;
        else iNumUnbrowsed++;
      }

      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_LT(fabs(iNumBrowsed - iNumExpectedBrowsed)/iNumBrowsed, 0.05);
    EXPECT_LT(fabs(iNumUnbrowsed - iNumExpectedUnbrowsed)/iNumUnbrowsed, 0.05);

    //Saplings of Species 5
    p_oAllTrees->StartOver();
    iSp = 4; iTp = clTreePopulation::sapling;
    iNumExpectedBrowsed = 660;
    iNumExpectedUnbrowsed = 340;
    iCode = p_oPop->GetBoolDataCode("Browsed", iSp, iTp);
    iNumBrowsed = 0;
    iNumUnbrowsed = 0;
    p_oTree = p_oAllTrees->NextTree();

    while (p_oTree) {

      if (p_oTree->GetSpecies() == iSp &&
          p_oTree->GetType() == iTp) {

        p_oTree->GetValue(iCode, &bVal);

        if (bVal) iNumBrowsed++;
        else iNumUnbrowsed++;
      }

      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_LT(fabs(iNumBrowsed - iNumExpectedBrowsed)/iNumBrowsed, 0.05);
    EXPECT_LT(fabs(iNumUnbrowsed - iNumExpectedUnbrowsed)/iNumUnbrowsed, 0.05);

    //Adults of Species 4
    p_oAllTrees->StartOver();
    iSp = 4; iTp = clTreePopulation::adult;
    iNumExpectedBrowsed = 0;
    iNumExpectedUnbrowsed = 1000;
    iCode = p_oPop->GetBoolDataCode("Browsed", iSp, iTp);
    EXPECT_EQ(-1, iCode);
    iNumBrowsed = 0;
    iNumUnbrowsed = 0;
    p_oTree = p_oAllTrees->NextTree();

    while (p_oTree) {

      if (p_oTree->GetSpecies() == iSp &&
          p_oTree->GetType() == iTp) {

        iNumUnbrowsed++;

      }

      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(iNumBrowsed, iNumExpectedBrowsed);
    EXPECT_EQ(iNumUnbrowsed, iNumExpectedUnbrowsed);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestNormalRun2()
// Tests normal processing run 2.
// WriteRandomBrowseXMLFile2() creates the parameter file. The run is exactly
// the same as run 1 except the timestep length is three years, so the browse
// probabilities are compounded appropriately.
/////////////////////////////////////////////////////////////////////////////
TEST(RandomBrowse, TestNormalRun2) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTreeSearch *p_oAllTrees;
    clTree *p_oTree;
    int iSp, iTp, iCode, iNumBrowsed, iNumUnbrowsed, iNumExpectedBrowsed,
    iNumExpectedUnbrowsed, i;
    bool bVal;

    //Create the sim manager and load our file
    p_oSimManager->ReadFile( WriteRandomBrowseXMLFile2() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create 1000 of each kind of tree
    for (i = 0; i < 1000; i++) {

      //Seedlings of Species 1
      p_oTree = p_oPop->CreateTree(1, 1, 0, clTreePopulation::seedling, 0);

      //Saplings of Species 1
      p_oTree = p_oPop->CreateTree(1, 1, 0, clTreePopulation::sapling, 7);

      //Adults of Species 1
      p_oTree = p_oPop->CreateTree(1, 1, 0, clTreePopulation::adult, 17);

      //Seedlings of Species 2
      p_oTree = p_oPop->CreateTree(1, 1, 1, clTreePopulation::seedling, 0);

      //Saplings of Species 2
      p_oTree = p_oPop->CreateTree(1, 1, 1, clTreePopulation::sapling, 7);

      //Adults of Species 2
      p_oTree = p_oPop->CreateTree(1, 1, 1, clTreePopulation::adult, 17);

      //Seedlings of Species 3
      p_oTree = p_oPop->CreateTree(1, 1, 2, clTreePopulation::seedling, 0);

      //Saplings of Species 3
      p_oTree = p_oPop->CreateTree(1, 1, 2, clTreePopulation::sapling, 7);

      //Adults of Species 3
      p_oTree = p_oPop->CreateTree(1, 1, 2, clTreePopulation::adult, 17);

      //Seedlings of Species 4
      p_oTree = p_oPop->CreateTree(1, 1, 3, clTreePopulation::seedling, 0);

      //Saplings of Species 4
      p_oTree = p_oPop->CreateTree(1, 1, 3, clTreePopulation::sapling, 7);

      //Adults of Species 4
      p_oTree = p_oPop->CreateTree(1, 1, 3, clTreePopulation::adult, 17);

      //Seedlings of Species 5
      p_oTree = p_oPop->CreateTree(1, 1, 4, clTreePopulation::seedling, 0);

      //Saplings of Species 5
      p_oTree = p_oPop->CreateTree(1, 1, 4, clTreePopulation::sapling, 7);

      //Adults of Species 5
      p_oTree = p_oPop->CreateTree(1, 1, 4, clTreePopulation::adult, 17);
    }

    //Run for one timestep
    p_oSimManager->RunSim(1);
    p_oAllTrees = p_oPop->Find("all");

    //Seedlings of Species 1
    iSp = 0; iTp = clTreePopulation::seedling;
    iNumExpectedBrowsed = 699;
    iNumExpectedUnbrowsed = 301;
    iCode = p_oPop->GetBoolDataCode("Browsed", iSp, iTp);
    iNumBrowsed = 0;
    iNumUnbrowsed = 0;
    p_oTree = p_oAllTrees->NextTree();

    while (p_oTree) {

      if (p_oTree->GetSpecies() == iSp &&
          p_oTree->GetType() == iTp) {

        p_oTree->GetValue(iCode, &bVal);

        if (bVal) iNumBrowsed++;
        else iNumUnbrowsed++;
      }

      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_LT(fabs(iNumBrowsed - iNumExpectedBrowsed)/iNumBrowsed, 0.05);
    EXPECT_LT(fabs(iNumUnbrowsed - iNumExpectedUnbrowsed)/iNumUnbrowsed, 0.05);

    //Saplings of Species 1
    p_oAllTrees->StartOver();
    iSp = 0; iTp = clTreePopulation::sapling;
    iNumExpectedBrowsed = 699;
    iNumExpectedUnbrowsed = 301;
    iCode = p_oPop->GetBoolDataCode("Browsed", iSp, iTp);
    iNumBrowsed = 0;
    iNumUnbrowsed = 0;
    p_oTree = p_oAllTrees->NextTree();

    while (p_oTree) {

      if (p_oTree->GetSpecies() == iSp &&
          p_oTree->GetType() == iTp) {

        p_oTree->GetValue(iCode, &bVal);

        if (bVal) iNumBrowsed++;
        else iNumUnbrowsed++;
      }

      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_LT(fabs(iNumBrowsed - iNumExpectedBrowsed)/iNumBrowsed, 0.05);
    EXPECT_LT(fabs(iNumUnbrowsed - iNumExpectedUnbrowsed)/iNumUnbrowsed, 0.10);

    //Adults of Species 1
    p_oAllTrees->StartOver();
    iSp = 0; iTp = clTreePopulation::adult;
    iNumExpectedBrowsed = 0;
    iNumExpectedUnbrowsed = 1000;
    iCode = p_oPop->GetBoolDataCode("Browsed", iSp, iTp);
    EXPECT_EQ(-1, iCode);
    iNumBrowsed = 0;
    iNumUnbrowsed = 0;
    p_oTree = p_oAllTrees->NextTree();

    while (p_oTree) {

      if (p_oTree->GetSpecies() == iSp &&
          p_oTree->GetType() == iTp) {

        iNumUnbrowsed++;

      }

      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(iNumBrowsed, iNumExpectedBrowsed);
    EXPECT_EQ(iNumUnbrowsed, iNumExpectedUnbrowsed);

    //Seedlings of Species 2
    p_oAllTrees->StartOver();
    iSp = 1; iTp = clTreePopulation::seedling;
    iNumExpectedBrowsed = 0;
    iNumExpectedUnbrowsed = 1000;
    iCode = p_oPop->GetBoolDataCode("Browsed", iSp, iTp);
    EXPECT_EQ(-1, iCode);
    iNumBrowsed = 0;
    iNumUnbrowsed = 0;
    p_oTree = p_oAllTrees->NextTree();

    while (p_oTree) {

      if (p_oTree->GetSpecies() == iSp &&
          p_oTree->GetType() == iTp) {

        iNumUnbrowsed++;

      }

      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(iNumBrowsed, iNumExpectedBrowsed);
    EXPECT_EQ(iNumUnbrowsed, iNumExpectedUnbrowsed);

    //Saplings of Species 2
    p_oAllTrees->StartOver();
    iSp = 1; iTp = clTreePopulation::sapling;
    iNumExpectedBrowsed = 0;
    iNumExpectedUnbrowsed = 1000;
    iCode = p_oPop->GetBoolDataCode("Browsed", iSp, iTp);
    EXPECT_EQ(-1, iCode);
    iNumBrowsed = 0;
    iNumUnbrowsed = 0;
    p_oTree = p_oAllTrees->NextTree();

    while (p_oTree) {

      if (p_oTree->GetSpecies() == iSp &&
          p_oTree->GetType() == iTp) {

        iNumUnbrowsed++;

      }

      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(iNumBrowsed, iNumExpectedBrowsed);
    EXPECT_EQ(iNumUnbrowsed, iNumExpectedUnbrowsed);

    //Adults of Species 2
    p_oAllTrees->StartOver();
    iSp = 1; iTp = clTreePopulation::adult;
    iNumExpectedBrowsed = 0;
    iNumExpectedUnbrowsed = 1000;
    iCode = p_oPop->GetBoolDataCode("Browsed", iSp, iTp);
    EXPECT_EQ(-1, iCode);
    iNumBrowsed = 0;
    iNumUnbrowsed = 0;
    p_oTree = p_oAllTrees->NextTree();

    while (p_oTree) {

      if (p_oTree->GetSpecies() == iSp &&
          p_oTree->GetType() == iTp) {

        iNumUnbrowsed++;

      }

      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(iNumBrowsed, iNumExpectedBrowsed);
    EXPECT_EQ(iNumUnbrowsed, iNumExpectedUnbrowsed);

    //Seedlings of Species 3
    p_oAllTrees->StartOver();
    iSp = 2; iTp = clTreePopulation::seedling;
    iNumExpectedBrowsed = 1000;
    iNumExpectedUnbrowsed = 0;
    iCode = p_oPop->GetBoolDataCode("Browsed", iSp, iTp);
    iNumBrowsed = 0;
    iNumUnbrowsed = 0;
    p_oTree = p_oAllTrees->NextTree();

    while (p_oTree) {

      if (p_oTree->GetSpecies() == iSp &&
          p_oTree->GetType() == iTp) {

        p_oTree->GetValue(iCode, &bVal);

        if (bVal) iNumBrowsed++;
        else iNumUnbrowsed++;
      }

      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(iNumBrowsed, iNumExpectedBrowsed);
    EXPECT_EQ(iNumUnbrowsed, iNumExpectedUnbrowsed);

    //Saplings of Species 3
    p_oAllTrees->StartOver();
    iSp = 2; iTp = clTreePopulation::sapling;
    iNumExpectedBrowsed = 0;
    iNumExpectedUnbrowsed = 1000;
    iCode = p_oPop->GetBoolDataCode("Browsed", iSp, iTp);
    EXPECT_EQ(-1, iCode);
    iNumBrowsed = 0;
    iNumUnbrowsed = 0;
    p_oTree = p_oAllTrees->NextTree();

    while (p_oTree) {

      if (p_oTree->GetSpecies() == iSp &&
          p_oTree->GetType() == iTp) {

        iNumUnbrowsed++;

      }

      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(iNumBrowsed, iNumExpectedBrowsed);
    EXPECT_EQ(iNumUnbrowsed, iNumExpectedUnbrowsed);

    //Adults of Species 3
    p_oAllTrees->StartOver();
    iSp = 2; iTp = clTreePopulation::adult;
    iNumExpectedBrowsed = 0;
    iNumExpectedUnbrowsed = 1000;
    iCode = p_oPop->GetBoolDataCode("Browsed", iSp, iTp);
    EXPECT_EQ(-1, iCode);
    iNumBrowsed = 0;
    iNumUnbrowsed = 0;
    p_oTree = p_oAllTrees->NextTree();

    while (p_oTree) {

      if (p_oTree->GetSpecies() == iSp &&
          p_oTree->GetType() == iTp) {

        iNumUnbrowsed++;

      }

      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(iNumBrowsed, iNumExpectedBrowsed);
    EXPECT_EQ(iNumUnbrowsed, iNumExpectedUnbrowsed);

    //Seedlings of Species 4
    p_oAllTrees->StartOver();
    iSp = 3; iTp = clTreePopulation::seedling;
    iNumExpectedBrowsed = 0;
    iNumExpectedUnbrowsed = 1000;
    iCode = p_oPop->GetBoolDataCode("Browsed", iSp, iTp);
    iNumBrowsed = 0;
    iNumUnbrowsed = 0;
    p_oTree = p_oAllTrees->NextTree();

    while (p_oTree) {

      if (p_oTree->GetSpecies() == iSp &&
          p_oTree->GetType() == iTp) {

        p_oTree->GetValue(iCode, &bVal);

        if (bVal) iNumBrowsed++;
        else iNumUnbrowsed++;
      }

      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(iNumBrowsed, iNumExpectedBrowsed);
    EXPECT_EQ(iNumUnbrowsed, iNumExpectedUnbrowsed);

    //Saplings of Species 4
    p_oAllTrees->StartOver();
    iSp = 3; iTp = clTreePopulation::sapling;
    iNumExpectedBrowsed = 0;
    iNumExpectedUnbrowsed = 1000;
    iCode = p_oPop->GetBoolDataCode("Browsed", iSp, iTp);
    iNumBrowsed = 0;
    iNumUnbrowsed = 0;
    p_oTree = p_oAllTrees->NextTree();

    while (p_oTree) {

      if (p_oTree->GetSpecies() == iSp &&
          p_oTree->GetType() == iTp) {

        p_oTree->GetValue(iCode, &bVal);

        if (bVal) iNumBrowsed++;
        else iNumUnbrowsed++;
      }

      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(iNumBrowsed, iNumExpectedBrowsed);
    EXPECT_EQ(iNumUnbrowsed, iNumExpectedUnbrowsed);

    //Adults of Species 4
    p_oAllTrees->StartOver();
    iSp = 3; iTp = clTreePopulation::adult;
    iNumExpectedBrowsed = 0;
    iNumExpectedUnbrowsed = 1000;
    iCode = p_oPop->GetBoolDataCode("Browsed", iSp, iTp);
    EXPECT_EQ(-1, iCode);
    iNumBrowsed = 0;
    iNumUnbrowsed = 0;
    p_oTree = p_oAllTrees->NextTree();

    while (p_oTree) {

      if (p_oTree->GetSpecies() == iSp &&
          p_oTree->GetType() == iTp) {

        iNumUnbrowsed++;

      }

      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(iNumBrowsed, iNumExpectedBrowsed);
    EXPECT_EQ(iNumUnbrowsed, iNumExpectedUnbrowsed);

    //Seedlings of Species 5
    p_oAllTrees->StartOver();
    iSp = 4; iTp = clTreePopulation::seedling;
    iNumExpectedBrowsed = 960;
    iNumExpectedUnbrowsed = 40;
    iCode = p_oPop->GetBoolDataCode("Browsed", iSp, iTp);
    iNumBrowsed = 0;
    iNumUnbrowsed = 0;
    p_oTree = p_oAllTrees->NextTree();

    while (p_oTree) {

      if (p_oTree->GetSpecies() == iSp &&
          p_oTree->GetType() == iTp) {

        p_oTree->GetValue(iCode, &bVal);

        if (bVal) iNumBrowsed++;
        else iNumUnbrowsed++;
      }

      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_LT(fabs(iNumBrowsed - iNumExpectedBrowsed)/iNumBrowsed, 0.05);
    EXPECT_LT(fabs(iNumUnbrowsed - iNumExpectedUnbrowsed)/iNumUnbrowsed, 0.15);

    //Saplings of Species 5
    p_oAllTrees->StartOver();
    iSp = 4; iTp = clTreePopulation::sapling;
    iNumExpectedBrowsed = 960;
    iNumExpectedUnbrowsed = 40;
    iCode = p_oPop->GetBoolDataCode("Browsed", iSp, iTp);
    iNumBrowsed = 0;
    iNumUnbrowsed = 0;
    p_oTree = p_oAllTrees->NextTree();

    while (p_oTree) {

      if (p_oTree->GetSpecies() == iSp &&
          p_oTree->GetType() == iTp) {

        p_oTree->GetValue(iCode, &bVal);

        if (bVal) iNumBrowsed++;
        else iNumUnbrowsed++;
      }

      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_LT(fabs(iNumBrowsed - iNumExpectedBrowsed)/iNumBrowsed, 0.05);
    EXPECT_LT(fabs(iNumUnbrowsed - iNumExpectedUnbrowsed)/iNumUnbrowsed, 0.15);

    //Adults of Species 4
    p_oAllTrees->StartOver();
    iSp = 4; iTp = clTreePopulation::adult;
    iNumExpectedBrowsed = 0;
    iNumExpectedUnbrowsed = 1000;
    iCode = p_oPop->GetBoolDataCode("Browsed", iSp, iTp);
    EXPECT_EQ(-1, iCode);
    iNumBrowsed = 0;
    iNumUnbrowsed = 0;
    p_oTree = p_oAllTrees->NextTree();

    while (p_oTree) {

      if (p_oTree->GetSpecies() == iSp &&
          p_oTree->GetType() == iTp) {

        iNumUnbrowsed++;

      }

      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(iNumBrowsed, iNumExpectedBrowsed);
    EXPECT_EQ(iNumUnbrowsed, iNumExpectedUnbrowsed);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestNormalRun3()
// Tests normal processing run 3.
// WriteRandomBrowseXMLFile3() creates the parameter file. The probabilities are done on
// a normal random draw. This creates a large number of probabilities to
// test the draw.
/////////////////////////////////////////////////////////////////////////////
TEST(RandomBrowse, TestNormalRun3) {
  clTreePopulation * p_oPop;
  clTreeSearch *p_oAllTrees;
  clTree *p_oTree;
  int *p_iNumBrowsed;
  float fMean, fStdDev;
  int iSp, iTp, iCode, i, iRun, iNumRuns = 1000;
  bool bVal;
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {

    p_iNumBrowsed = new int[iNumRuns];
    for (i = 0; i < iNumRuns; i++) {
      p_iNumBrowsed[i] = 0;
    }

    //Do a whole set of repetitions and count the number browsed for each
    for (iRun = 0; iRun < iNumRuns; iRun++) {

      p_oSimManager->ReadFile( WriteRandomBrowseXMLFile3() );
      p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

      //Create 1000 trees
      for (i = 0; i < 1000; i++) {
        p_oTree = p_oPop->CreateTree(1, 1, 0, clTreePopulation::seedling, 0);
      }

      //Run for one timestep
      p_oSimManager->RunSim(1);
      p_oAllTrees = p_oPop->Find("all");

      iSp = 0; iTp = clTreePopulation::seedling;
      iCode = p_oPop->GetBoolDataCode("Browsed", iSp, iTp);
      p_oTree = p_oAllTrees->NextTree();

      while (p_oTree) {
        p_oTree->GetValue(iCode, &bVal);
        if (bVal) p_iNumBrowsed[iRun]++;
        p_oTree = p_oAllTrees->NextTree();
      }
    }
    //Calculate the mean browse rate
    fMean = 0;
    for (i = 0; i < iNumRuns; i++) {
      fMean += ((float)p_iNumBrowsed[i]/1000.0);
    }
    fMean /= iNumRuns;

    //Calculate the standard deviation
    fStdDev = 0;
    for (i = 0; i < iNumRuns; i++) {
      fStdDev += pow(((float)p_iNumBrowsed[i]/1000.0) - fMean, 2);
    }
    fStdDev /= iNumRuns;
    fStdDev = sqrt(fStdDev);

    EXPECT_LT(fabs(0.33 - fMean), 0.1);
    EXPECT_LT(fabs(0.1 - fStdDev), 0.1);

    delete[] p_iNumBrowsed;
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete[] p_iNumBrowsed;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestErrorProcessing()
////////////////////////////////////////////////////////////////////////////
TEST(RandomBrowse, TestErrorProcessing)
{
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try
  {
    p_oSimManager->ReadFile( WriteRandomBrowseXMLErrorFile1() );
    FAIL() << "TestRandomBrowse error processing didn't catch error for WriteRandomBrowseXMLErrorFile1.";
  }
  catch ( modelErr& err )
  {
    if ( err.sFunction.compare("clRandomBrowse::GetData" ) != 0 )
    {
      FAIL() << "TestRandomBrowse error processing caught wrong error for WriteRandomBrowseXMLErrorFile1.";
    }
    ;
  }
  delete p_oSimManager;
}

/////////////////////////////////////////////////////////////////////////////
// WriteRandomBrowseXMLFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteRandomBrowseXMLFile1()
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
      << "<randomSeed>-1</randomSeed>"
      << "<yearsPerTimestep>1.0</yearsPerTimestep>"
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
      << "<tr_species speciesName=\"Species_5\" />"
      << "</tr_speciesList>"
      << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
      << "<tr_minAdultDBH>"
      << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
      << "<tr_madVal species=\"Species_2\">10.0</tr_madVal>"
      << "<tr_madVal species=\"Species_3\">10.0</tr_madVal>"
      << "<tr_madVal species=\"Species_4\">10.0</tr_madVal>"
      << "<tr_madVal species=\"Species_5\">10.0</tr_madVal>"
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
      << "<tr_canopyHeight>"
      << "<tr_chVal species=\"Species_1\">40.0</tr_chVal>"
      << "<tr_chVal species=\"Species_2\">40.0</tr_chVal>"
      << "<tr_chVal species=\"Species_3\">40.0</tr_chVal>"
      << "<tr_chVal species=\"Species_4\">40.0</tr_chVal>"
      << "<tr_chVal species=\"Species_5\">40.0</tr_chVal>"
      << "</tr_canopyHeight>"
      << "<tr_stdAsympCrownRad>"
      << "<tr_sacrVal species=\"Species_1\">0.7</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_2\">0.7</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_3\">0.7</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_4\">0.7</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_5\">0.7</tr_sacrVal>"
      << "</tr_stdAsympCrownRad>"
      << "<tr_stdCrownRadExp>"
      << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_3\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_4\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_5\">1.0</tr_screVal>"
      << "</tr_stdCrownRadExp>"
      << "<tr_conversionDiam10ToDBH>"
      << "<tr_cdtdVal species=\"Species_1\">0.7</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_2\">0.7</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_3\">0.7</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_4\">0.7</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_5\">0.7</tr_cdtdVal>"
      << "</tr_conversionDiam10ToDBH>"
      << "<tr_interceptDiam10ToDBH>"
      << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_3\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_4\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_5\">0</tr_idtdVal>"
      << "</tr_interceptDiam10ToDBH>"
      << "<tr_stdAsympCrownHt>"
      << "<tr_sachVal species=\"Species_1\">0.7</tr_sachVal>"
      << "<tr_sachVal species=\"Species_2\">0.7</tr_sachVal>"
      << "<tr_sachVal species=\"Species_3\">0.7</tr_sachVal>"
      << "<tr_sachVal species=\"Species_4\">0.7</tr_sachVal>"
      << "<tr_sachVal species=\"Species_5\">0.7</tr_sachVal>"
      << "</tr_stdAsympCrownHt>"
      << "<tr_stdCrownHtExp>"
      << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_3\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_4\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_5\">1.0</tr_scheVal>"
      << "</tr_stdCrownHtExp>"
      << "<tr_slopeOfHeight-Diam10>"
      << "<tr_sohdVal species=\"Species_1\">0.03</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_2\">0.03</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_3\">0.03</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_4\">0.03</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_5\">0.03</tr_sohdVal>"
      << "</tr_slopeOfHeight-Diam10>"
      << "<tr_slopeOfAsymHeight>"
      << "<tr_soahVal species=\"Species_1\">0.7</tr_soahVal>"
      << "<tr_soahVal species=\"Species_2\">0.7</tr_soahVal>"
      << "<tr_soahVal species=\"Species_3\">0.7</tr_soahVal>"
      << "<tr_soahVal species=\"Species_4\">0.7</tr_soahVal>"
      << "<tr_soahVal species=\"Species_5\">0.7</tr_soahVal>"
      << "</tr_slopeOfAsymHeight>"
      << "<tr_whatSeedlingHeightDiam>"
      << "<tr_wsehdVal species=\"Species_1\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_2\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_3\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_4\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_5\">0</tr_wsehdVal>"
      << "</tr_whatSeedlingHeightDiam>"
      << "<tr_whatSaplingHeightDiam>"
      << "<tr_wsahdVal species=\"Species_1\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_2\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_3\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_4\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_5\">0</tr_wsahdVal>"
      << "</tr_whatSaplingHeightDiam>"
      << "<tr_whatAdultHeightDiam>"
      << "<tr_wahdVal species=\"Species_1\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_2\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_3\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_4\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_5\">0</tr_wahdVal>"
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
      << "</allometry>"
      << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>RandomBrowse</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\" />"
      << "<applyTo species=\"Species_3\" type=\"Seedling\" />"
      << "<applyTo species=\"Species_4\" type=\"Seedling\" />"
      << "<applyTo species=\"Species_5\" type=\"Seedling\" />"
      << "<applyTo species=\"Species_1\" type=\"Sapling\" />"
      << "<applyTo species=\"Species_4\" type=\"Sapling\" />"
      << "<applyTo species=\"Species_5\" type=\"Sapling\" />"
      << "</behavior>"
      << "</behaviorList>"
      << "<RandomBrowse1>"
      << "<di_randBrowsePDF>0</di_randBrowsePDF>"
      << "<di_randBrowseProb>"
      << "<di_rbpVal species=\"Species_1\">0.33</di_rbpVal>"
      << "<di_rbpVal species=\"Species_3\">1</di_rbpVal>"
      << "<di_rbpVal species=\"Species_4\">0.0</di_rbpVal>"
      << "<di_rbpVal species=\"Species_5\">0.66</di_rbpVal>"
      << "</di_randBrowseProb>"
      << "</RandomBrowse1>"
      << "</paramFile>";

  oOut.close();
  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteRandomBrowseXMLFile2()
/////////////////////////////////////////////////////////////////////////////
const char* WriteRandomBrowseXMLFile2()
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
      << "<randomSeed>-1</randomSeed>"
      << "<yearsPerTimestep>3.0</yearsPerTimestep>"
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
      << "<tr_species speciesName=\"Species_5\" />"
      << "</tr_speciesList>"
      << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
      << "<tr_minAdultDBH>"
      << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
      << "<tr_madVal species=\"Species_2\">10.0</tr_madVal>"
      << "<tr_madVal species=\"Species_3\">10.0</tr_madVal>"
      << "<tr_madVal species=\"Species_4\">10.0</tr_madVal>"
      << "<tr_madVal species=\"Species_5\">10.0</tr_madVal>"
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
      << "<tr_canopyHeight>"
      << "<tr_chVal species=\"Species_1\">40.0</tr_chVal>"
      << "<tr_chVal species=\"Species_2\">40.0</tr_chVal>"
      << "<tr_chVal species=\"Species_3\">40.0</tr_chVal>"
      << "<tr_chVal species=\"Species_4\">40.0</tr_chVal>"
      << "<tr_chVal species=\"Species_5\">40.0</tr_chVal>"
      << "</tr_canopyHeight>"
      << "<tr_stdAsympCrownRad>"
      << "<tr_sacrVal species=\"Species_1\">0.7</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_2\">0.7</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_3\">0.7</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_4\">0.7</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_5\">0.7</tr_sacrVal>"
      << "</tr_stdAsympCrownRad>"
      << "<tr_stdCrownRadExp>"
      << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_3\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_4\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_5\">1.0</tr_screVal>"
      << "</tr_stdCrownRadExp>"
      << "<tr_conversionDiam10ToDBH>"
      << "<tr_cdtdVal species=\"Species_1\">0.7</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_2\">0.7</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_3\">0.7</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_4\">0.7</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_5\">0.7</tr_cdtdVal>"
      << "</tr_conversionDiam10ToDBH>"
      << "<tr_interceptDiam10ToDBH>"
      << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_3\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_4\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_5\">0</tr_idtdVal>"
      << "</tr_interceptDiam10ToDBH>"
      << "<tr_stdAsympCrownHt>"
      << "<tr_sachVal species=\"Species_1\">0.7</tr_sachVal>"
      << "<tr_sachVal species=\"Species_2\">0.7</tr_sachVal>"
      << "<tr_sachVal species=\"Species_3\">0.7</tr_sachVal>"
      << "<tr_sachVal species=\"Species_4\">0.7</tr_sachVal>"
      << "<tr_sachVal species=\"Species_5\">0.7</tr_sachVal>"
      << "</tr_stdAsympCrownHt>"
      << "<tr_stdCrownHtExp>"
      << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_3\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_4\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_5\">1.0</tr_scheVal>"
      << "</tr_stdCrownHtExp>"
      << "<tr_slopeOfHeight-Diam10>"
      << "<tr_sohdVal species=\"Species_1\">0.03</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_2\">0.03</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_3\">0.03</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_4\">0.03</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_5\">0.03</tr_sohdVal>"
      << "</tr_slopeOfHeight-Diam10>"
      << "<tr_slopeOfAsymHeight>"
      << "<tr_soahVal species=\"Species_1\">0.7</tr_soahVal>"
      << "<tr_soahVal species=\"Species_2\">0.7</tr_soahVal>"
      << "<tr_soahVal species=\"Species_3\">0.7</tr_soahVal>"
      << "<tr_soahVal species=\"Species_4\">0.7</tr_soahVal>"
      << "<tr_soahVal species=\"Species_5\">0.7</tr_soahVal>"
      << "</tr_slopeOfAsymHeight>"
      << "<tr_whatSeedlingHeightDiam>"
      << "<tr_wsehdVal species=\"Species_1\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_2\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_3\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_4\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_5\">0</tr_wsehdVal>"
      << "</tr_whatSeedlingHeightDiam>"
      << "<tr_whatSaplingHeightDiam>"
      << "<tr_wsahdVal species=\"Species_1\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_2\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_3\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_4\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_5\">0</tr_wsahdVal>"
      << "</tr_whatSaplingHeightDiam>"
      << "<tr_whatAdultHeightDiam>"
      << "<tr_wahdVal species=\"Species_1\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_2\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_3\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_4\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_5\">0</tr_wahdVal>"
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
      << "</allometry>"
      << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>RandomBrowse</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\" />"
      << "<applyTo species=\"Species_3\" type=\"Seedling\" />"
      << "<applyTo species=\"Species_4\" type=\"Seedling\" />"
      << "<applyTo species=\"Species_5\" type=\"Seedling\" />"
      << "<applyTo species=\"Species_1\" type=\"Sapling\" />"
      << "<applyTo species=\"Species_4\" type=\"Sapling\" />"
      << "<applyTo species=\"Species_5\" type=\"Sapling\" />"
      << "</behavior>"
      << "</behaviorList>"
      << "<RandomBrowse1>"
      << "<di_randBrowsePDF>0</di_randBrowsePDF>"
      << "<di_randBrowseProb>"
      << "<di_rbpVal species=\"Species_1\">0.33</di_rbpVal>"
      << "<di_rbpVal species=\"Species_3\">1</di_rbpVal>"
      << "<di_rbpVal species=\"Species_4\">0.0</di_rbpVal>"
      << "<di_rbpVal species=\"Species_5\">0.66</di_rbpVal>"
      << "</di_randBrowseProb>"
      << "</RandomBrowse1>"
      << "</paramFile>";

  oOut.close();
  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteRandomBrowseXMLErrorFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteRandomBrowseXMLErrorFile1()
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
      << "<randomSeed>-1</randomSeed>"
      << "<yearsPerTimestep>1.0</yearsPerTimestep>"
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
      << "<tr_species speciesName=\"Species_5\" />"
      << "</tr_speciesList>"
      << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
      << "<tr_minAdultDBH>"
      << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
      << "<tr_madVal species=\"Species_2\">10.0</tr_madVal>"
      << "<tr_madVal species=\"Species_3\">10.0</tr_madVal>"
      << "<tr_madVal species=\"Species_4\">10.0</tr_madVal>"
      << "<tr_madVal species=\"Species_5\">10.0</tr_madVal>"
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
      << "<tr_canopyHeight>"
      << "<tr_chVal species=\"Species_1\">40.0</tr_chVal>"
      << "<tr_chVal species=\"Species_2\">40.0</tr_chVal>"
      << "<tr_chVal species=\"Species_3\">40.0</tr_chVal>"
      << "<tr_chVal species=\"Species_4\">40.0</tr_chVal>"
      << "<tr_chVal species=\"Species_5\">40.0</tr_chVal>"
      << "</tr_canopyHeight>"
      << "<tr_stdAsympCrownRad>"
      << "<tr_sacrVal species=\"Species_1\">0.7</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_2\">0.7</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_3\">0.7</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_4\">0.7</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_5\">0.7</tr_sacrVal>"
      << "</tr_stdAsympCrownRad>"
      << "<tr_stdCrownRadExp>"
      << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_3\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_4\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_5\">1.0</tr_screVal>"
      << "</tr_stdCrownRadExp>"
      << "<tr_conversionDiam10ToDBH>"
      << "<tr_cdtdVal species=\"Species_1\">0.7</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_2\">0.7</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_3\">0.7</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_4\">0.7</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_5\">0.7</tr_cdtdVal>"
      << "</tr_conversionDiam10ToDBH>"
      << "<tr_interceptDiam10ToDBH>"
      << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_3\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_4\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_5\">0</tr_idtdVal>"
      << "</tr_interceptDiam10ToDBH>"
      << "<tr_stdAsympCrownHt>"
      << "<tr_sachVal species=\"Species_1\">0.7</tr_sachVal>"
      << "<tr_sachVal species=\"Species_2\">0.7</tr_sachVal>"
      << "<tr_sachVal species=\"Species_3\">0.7</tr_sachVal>"
      << "<tr_sachVal species=\"Species_4\">0.7</tr_sachVal>"
      << "<tr_sachVal species=\"Species_5\">0.7</tr_sachVal>"
      << "</tr_stdAsympCrownHt>"
      << "<tr_stdCrownHtExp>"
      << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_3\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_4\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_5\">1.0</tr_scheVal>"
      << "</tr_stdCrownHtExp>"
      << "<tr_slopeOfHeight-Diam10>"
      << "<tr_sohdVal species=\"Species_1\">0.03</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_2\">0.03</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_3\">0.03</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_4\">0.03</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_5\">0.03</tr_sohdVal>"
      << "</tr_slopeOfHeight-Diam10>"
      << "<tr_slopeOfAsymHeight>"
      << "<tr_soahVal species=\"Species_1\">0.7</tr_soahVal>"
      << "<tr_soahVal species=\"Species_2\">0.7</tr_soahVal>"
      << "<tr_soahVal species=\"Species_3\">0.7</tr_soahVal>"
      << "<tr_soahVal species=\"Species_4\">0.7</tr_soahVal>"
      << "<tr_soahVal species=\"Species_5\">0.7</tr_soahVal>"
      << "</tr_slopeOfAsymHeight>"
      << "<tr_whatSeedlingHeightDiam>"
      << "<tr_wsehdVal species=\"Species_1\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_2\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_3\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_4\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_5\">0</tr_wsehdVal>"
      << "</tr_whatSeedlingHeightDiam>"
      << "<tr_whatSaplingHeightDiam>"
      << "<tr_wsahdVal species=\"Species_1\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_2\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_3\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_4\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_5\">0</tr_wsahdVal>"
      << "</tr_whatSaplingHeightDiam>"
      << "<tr_whatAdultHeightDiam>"
      << "<tr_wahdVal species=\"Species_1\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_2\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_3\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_4\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_5\">0</tr_wahdVal>"
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
      << "</allometry>"
      << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>RandomBrowse</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\" />"
      << "<applyTo species=\"Species_3\" type=\"Seedling\" />"
      << "<applyTo species=\"Species_4\" type=\"Seedling\" />"
      << "<applyTo species=\"Species_5\" type=\"Seedling\" />"
      << "<applyTo species=\"Species_1\" type=\"Sapling\" />"
      << "<applyTo species=\"Species_4\" type=\"Sapling\" />"
      << "<applyTo species=\"Species_5\" type=\"Sapling\" />"
      << "</behavior>"
      << "</behaviorList>"
      << "<RandomBrowse1>"
      << "<di_randBrowsePDF>0</di_randBrowsePDF>"
      << "<di_randBrowseProb>"
      << "<di_rbpVal species=\"Species_1\">1.33</di_rbpVal>"
      << "<di_rbpVal species=\"Species_3\">1</di_rbpVal>"
      << "<di_rbpVal species=\"Species_4\">0.0</di_rbpVal>"
      << "<di_rbpVal species=\"Species_5\">0.66</di_rbpVal>"
      << "</di_randBrowseProb>"
      << "</RandomBrowse1>"
      << "</paramFile>";

  oOut.close();
  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteRandomBrowseXMLFile3()
/////////////////////////////////////////////////////////////////////////////
const char* WriteRandomBrowseXMLFile3() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">"
      << "<plot>"
      << "<timesteps>2</timesteps>"
      << "<randomSeed>1</randomSeed>"
      << "<yearsPerTimestep>1.0</yearsPerTimestep>"
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
      << "<tr_canopyHeight>"
      << "<tr_chVal species=\"Species_1\">40.0</tr_chVal>"
      << "<tr_chVal species=\"Species_2\">40.0</tr_chVal>"
      << "</tr_canopyHeight>"
      << "<tr_stdAsympCrownRad>"
      << "<tr_sacrVal species=\"Species_1\">0.7</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_2\">0.7</tr_sacrVal>"
      << "</tr_stdAsympCrownRad>"
      << "<tr_stdCrownRadExp>"
      << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
      << "</tr_stdCrownRadExp>"
      << "<tr_conversionDiam10ToDBH>"
      << "<tr_cdtdVal species=\"Species_1\">0.7</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_2\">0.7</tr_cdtdVal>"
      << "</tr_conversionDiam10ToDBH>"
      << "<tr_interceptDiam10ToDBH>"
      << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
      << "</tr_interceptDiam10ToDBH>"
      << "<tr_stdAsympCrownHt>"
      << "<tr_sachVal species=\"Species_1\">0.7</tr_sachVal>"
      << "<tr_sachVal species=\"Species_2\">0.7</tr_sachVal>"
      << "</tr_stdAsympCrownHt>"
      << "<tr_stdCrownHtExp>"
      << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
      << "</tr_stdCrownHtExp>"
      << "<tr_slopeOfHeight-Diam10>"
      << "<tr_sohdVal species=\"Species_1\">0.03</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_2\">0.03</tr_sohdVal>"
      << "</tr_slopeOfHeight-Diam10>"
      << "<tr_slopeOfAsymHeight>"
      << "<tr_soahVal species=\"Species_1\">0.7</tr_soahVal>"
      << "<tr_soahVal species=\"Species_2\">0.7</tr_soahVal>"
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
      << "<behaviorName>RandomBrowse</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\" />"
      << "</behavior>"
      << "</behaviorList>"
      << "<RandomBrowse1>"
      << "<di_randBrowsePDF>3</di_randBrowsePDF>"
      << "<di_randBrowseProb>"
      << "<di_rbpVal species=\"Species_1\">0.33</di_rbpVal>"
      << "</di_randBrowseProb>"
      << "<di_randBrowseStdDev>"
      << "<di_rbsdVal species=\"Species_1\">0.1</di_rbsdVal>"
      << "</di_randBrowseStdDev>"
      << "</RandomBrowse1>"
      << "</paramFile>";

  oOut.close();
  return cFileString;
}
