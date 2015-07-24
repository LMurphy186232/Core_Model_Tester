//---------------------------------------------------------------------------
// TestHarvest.cpp
//---------------------------------------------------------------------------
#include "TestHarvest.h"
#include <gtest/gtest.h>
#include "TreePopulation.h"
#include "SimManager.h"
#include "ModelMath.h"
#include "Grid.h"
#include "BehaviorBase.h"
#include "Disturbance.h"
#include <fstream>
#include <math.h>
#include <sstream>

/////////////////////////////////////////////////////////////////////////////
// DoHarvestRun1()
// Performs the first harvest run.  This run has the following characteristics:
//
// Harvest # |TS |Cut Ranges |Species |Cut Type |Cut Amt (abs) |Grids
//-----------|---|-----------|--------|---------|--------------|---------------
// 1         |1  |0 - 300    |2, 4    |% BA     |35            |Whole plot
// 2         |3  |0-30, 40-80|5       |Abs BA   |0.2, 0.2      |Whole plot
// 3         |3  |Min 0      |2, 8    |Clear    |100%          |Whole plot
//
// The harvest will be performed.  Then the remaining trees are checked to make
// sure the proper ones were left alone.
/////////////////////////////////////////////////////////////////////////////
TEST(Harvest, DoHarvestRun1) {
  clTreePopulation * p_oPop;
  clTreeSearch *p_oAllTrees;
  clTree *p_oTree;
  clGrid *p_oResults;
  int *p_iC = new int[4];
  std::stringstream sLabel;
  float fTemp, fSp2BA, fSp4BA;
  int i, iNumXCells, iNumYCells, iX, iY, iNumSpecies, j, k;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    p_oSimManager->ReadFile( WriteHarvestXMLFile1() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
    p_oResults = p_oSimManager->GetGridObject("Harvest Results");

    //Add many snags to make sure they don't get counted
    for (i = 0; i < 100; i++) {
      p_oPop->CreateTree(10, 10, 0, clTreePopulation::snag, 50);
    }
    for (i = 0; i < 100; i++) {
      p_oPop->CreateTree(10, 10, 1, clTreePopulation::snag, 50);
    }
    for (i = 0; i < 100; i++) {
      p_oPop->CreateTree(10, 10, 2, clTreePopulation::snag, 50);
    }
    for (i = 0; i < 100; i++) {
      p_oPop->CreateTree(10, 10, 3, clTreePopulation::snag, 50);
    }
    for (i = 0; i < 100; i++) {
      p_oPop->CreateTree(10, 10, 4, clTreePopulation::snag, 50);
    }
    for (i = 0; i < 100; i++) {
      p_oPop->CreateTree(10, 10, 5, clTreePopulation::snag, 50);
    }
    for (i = 0; i < 100; i++) {
      p_oPop->CreateTree(10, 10, 6, clTreePopulation::snag, 50);
    }
    for (i = 0; i < 100; i++) {
      p_oPop->CreateTree(10, 10, 7, clTreePopulation::snag, 50);
    }
    for (i = 0; i < 100; i++) {
      p_oPop->CreateTree(10, 10, 8, clTreePopulation::snag, 50);
    }

    //Add a bunch of seedlings to check seedling destruction
    iNumXCells = p_oPop->GetNumXCells();
    iNumYCells = p_oPop->GetNumYCells();
    iNumSpecies = p_oPop->GetNumberOfSpecies();
    fTemp = p_oPop->GetGridCellSize();
    p_iC[0] = 1; p_iC[1] = 3; p_iC[2] = 5; p_iC[3] = 7;
    for (iX = 0; iX < iNumXCells; iX++) {
      for (iY = 0; iY < iNumYCells; iY++) {
        for (i = 0; i < iNumSpecies; i++) {
          for (j = 0; j < 4; j++) {
            for (k = 0; k < 4; k++) {
              p_oPop->CreateTree((iX * fTemp) + p_iC[j],
                  (iY * fTemp) + p_iC[k], i, clTreePopulation::seedling, 0);
            }
          }
        }
      }
    }
    delete[] p_iC;

    //*********************************************
    // Timestep 1
    //*********************************************
    //Run the first timestep
    p_oSimManager->RunSim(1);

    //Total up the basal area for species 2 and 4 - we're expecting 34.3837 sq
    //m of species 2 and 33.619 sq m of species 4
    fSp2BA = 0; fSp4BA = 0;
    p_iC = new int[iNumSpecies];
    for (i = 0; i < iNumSpecies; i++) p_iC[i] = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (p_oTree->GetType() == clTreePopulation::sapling ||
          p_oTree->GetType() == clTreePopulation::adult) {

        if (p_oTree->GetSpecies() == 2) {
          p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
          fSp2BA += clModelMath::CalculateBasalArea(fTemp);

        } else if (p_oTree->GetSpecies() == 4) {
          p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
          fSp4BA += clModelMath::CalculateBasalArea(fTemp);
        }
      } else if (p_oTree->GetType() == clTreePopulation::seedling) {
        p_iC[p_oTree->GetSpecies()]++;
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    EXPECT_LT(fabs(fSp2BA - 34.3837)/34.3837, 0.01);
    EXPECT_LT(fabs(fSp4BA - 33.61)/33.61, 0.01);
    for (i = 0; i < iNumSpecies; i++) {
      if (i == 2 || i == 4) EXPECT_EQ(p_iC[i], 0);
      else EXPECT_EQ(p_iC[i], 10000);
    }

    //Check the results grid
    iNumXCells = p_oResults->GetNumberXCells();
    iNumYCells = p_oResults->GetNumberYCells();
    for (iX = 0; iX < iNumXCells; iX++) {
      for (iY = 0; iY < iNumYCells; iY++) {
        for (i = 0; i < iNumSpecies; i++) {
          sLabel << "Cut Seedlings_" << i;
          p_oResults->GetValueOfCell(iX, iY, p_oResults->GetIntDataCode(sLabel.str()), &j);
          if (i == 2 || i == 4) EXPECT_EQ(16, j);
          else EXPECT_EQ(0, j);
          sLabel.str("");
        }
      }
    }

    //*********************************************
    // Timestep 3
    //*********************************************
    p_oSimManager->RunSim(2);
    float fSp5Range0_30 = 0, fSp5Range40_80 = 0;
    for (i = 0; i < iNumSpecies; i++) p_iC[i] = 0;

    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (p_oTree->GetType() == clTreePopulation::sapling ||
          p_oTree->GetType() == clTreePopulation::adult) {

        //Make sure there are no trees of species 2 or 8
        ASSERT_TRUE(p_oTree->GetSpecies() != 2 && p_oTree->GetSpecies() != 8);

        //Total up the basal area for species five between DBH of 0-30 and 40-80
        if (p_oTree->GetSpecies() == 5) {

          p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);

          if (fTemp <= 30)
            fSp5Range0_30 += clModelMath::CalculateBasalArea(fTemp);
          else if (fTemp >= 40 && fTemp <= 80)
            fSp5Range40_80 += clModelMath::CalculateBasalArea(fTemp);
        }
      } else if (p_oTree->GetType() == clTreePopulation::seedling) {
        p_iC[p_oTree->GetSpecies()]++;
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    //Make sure the leftover basal area for species 5 is OK
    EXPECT_LT(fabs(fSp5Range0_30 - 0.64226)/0.64226, 0.01);
    EXPECT_LT(fabs(fSp5Range40_80 - 23.055)/23.055, 0.01);
    for (i = 0; i < iNumSpecies; i++) {
      if (i == 2 || i == 4) EXPECT_EQ(p_iC[i], 0);
      else EXPECT_EQ(p_iC[i], 10000);
    }

    //Check the results grid
    iNumXCells = p_oResults->GetNumberXCells();
    iNumYCells = p_oResults->GetNumberYCells();
    for (iX = 0; iX < iNumXCells; iX++) {
      for (iY = 0; iY < iNumYCells; iY++) {
        for (i = 0; i < iNumSpecies; i++) {
          sLabel << "Cut Seedlings_" << i;
          p_oResults->GetValueOfCell(iX, iY, p_oResults->GetIntDataCode(sLabel.str()), &j);
          EXPECT_EQ(0, j);
          sLabel.str("");
        }
      }
    }

    delete[] p_iC;
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete[] p_iC;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// DoHarvestRun2()
// Performs the second harvest run.  This run has the following
// characteristics:
//
// Harvest # |TS |Cut Ranges |Species |Cut Type |Cut Amt (abs) |Grids
//-----------|---|-----------|--------|---------|--------------|---------------
// 1         |1  |15-45,     |0, 1    |%Dens    |50, 40,       |Whole plot
//           |   |50-80,     |        |         |30, 20        |
//           |   |80-85,     |        |         |              |
//           |   |90-99      |        |         |              |
//
// The harvest will be performed.  Then the remaining trees are checked to make
// sure the proper ones were left alone.
/////////////////////////////////////////////////////////////////////////////
TEST(Harvest, DoHarvestRun2) {

  clTreePopulation * p_oPop;
  clTreeSearch *p_oAllTrees;
  clTree *p_oTree;
  clGrid *p_oResults;
  std::stringstream sLabel;
  int *p_iC = new int[4];
  float fTemp;
  int iNumXCells, iNumYCells, iNumSpecies, iX, iY, j, k,
  iSp0_90_99 = 0, iSp0_80_85 = 0, iSp0_50_80 = 0, iSp0_15_45 = 0,
  iSp1_90_99 = 0, iSp1_80_85 = 0, iSp1_50_80 = 0, iSp1_15_45 = 0, i;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    p_oSimManager->ReadFile( WriteHarvestXMLFile2() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
    p_oResults = p_oSimManager->GetGridObject("Harvest Results");

    //Add many snags to make sure they don't get counted
    for (i = 0; i < 100; i++) {
      p_oPop->CreateTree(10, 10, 0, clTreePopulation::snag, 50);
    }
    for (i = 0; i < 100; i++) {
      p_oPop->CreateTree(10, 10, 1, clTreePopulation::snag, 50);
    }
    for (i = 0; i < 100; i++) {
      p_oPop->CreateTree(10, 10, 2, clTreePopulation::snag, 50);
    }
    for (i = 0; i < 100; i++) {
      p_oPop->CreateTree(10, 10, 3, clTreePopulation::snag, 50);
    }
    for (i = 0; i < 100; i++) {
      p_oPop->CreateTree(10, 10, 4, clTreePopulation::snag, 50);
    }
    for (i = 0; i < 100; i++) {
      p_oPop->CreateTree(10, 10, 5, clTreePopulation::snag, 50);
    }
    for (i = 0; i < 100; i++) {
      p_oPop->CreateTree(10, 10, 6, clTreePopulation::snag, 50);
    }
    for (i = 0; i < 100; i++) {
      p_oPop->CreateTree(10, 10, 7, clTreePopulation::snag, 50);
    }
    for (i = 0; i < 100; i++) {
      p_oPop->CreateTree(10, 10, 8, clTreePopulation::snag, 50);
    }

    //Add a bunch of seedlings to check seedling destruction
    iNumXCells = p_oPop->GetNumXCells();
    iNumYCells = p_oPop->GetNumYCells();
    iNumSpecies = p_oPop->GetNumberOfSpecies();
    fTemp = p_oPop->GetGridCellSize();
    p_iC[0] = 1; p_iC[1] = 3; p_iC[2] = 5; p_iC[3] = 7;
    for (iX = 0; iX < iNumXCells; iX++) {
      for (iY = 0; iY < iNumYCells; iY++) {
        for (i = 0; i < iNumSpecies; i++) {
          for (j = 0; j < 4; j++) {
            for (k = 0; k < 4; k++) {
              p_oPop->CreateTree((iX * fTemp) + p_iC[j],
                  (iY * fTemp) + p_iC[k], i, clTreePopulation::seedling, 0);
            }
          }
        }
      }
    }
    delete[] p_iC;

    //*********************************************
    // Timestep 1
    //*********************************************
    //Run the first timestep
    p_oSimManager->RunSim(1);

    //Count up the trees in our size classes
    p_iC = new int[iNumSpecies];
    for (i = 0; i < iNumSpecies; i++) p_iC[i] = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (p_oTree->GetType() == clTreePopulation::sapling ||
          p_oTree->GetType() == clTreePopulation::adult) {

        if (p_oTree->GetSpecies() == 1) {

          p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);

          if (fTemp >= 90 && fTemp <= 99)
            iSp1_90_99++;
          else if (fTemp >= 80 && fTemp <= 85)
            iSp1_80_85++;
          else if (fTemp >= 50 && fTemp <= 80)
            iSp1_50_80++;
          else if (fTemp >= 15 && fTemp <= 45)
            iSp1_15_45++;

        } else if (p_oTree->GetSpecies() == 0) {

          p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);

          if (fTemp >= 90 && fTemp <= 99)
            iSp0_90_99++;
          else if (fTemp >= 80 && fTemp <= 85)
            iSp0_80_85++;
          else if (fTemp >= 50 && fTemp <= 80)
            iSp0_50_80++;
          else if (fTemp >= 15 && fTemp <= 45)
            iSp0_15_45++;
        }
      } else if (p_oTree->GetType() == clTreePopulation::seedling) {
        p_iC[p_oTree->GetSpecies()]++;
      }

      p_oTree = p_oAllTrees->NextTree();
    }

    ASSERT_TRUE(iSp1_90_99 >= 10 && iSp1_90_99 <= 14);
    ASSERT_TRUE(iSp1_80_85 >= 6 && iSp1_80_85 <= 12);
    ASSERT_TRUE(iSp1_50_80 >= 34 && iSp1_50_80 <= 46);
    ASSERT_TRUE(iSp1_15_45 >= 25 && iSp1_15_45 <= 35);
    ASSERT_TRUE(iSp0_90_99 >= 8 && iSp0_90_99 <= 14);
    ASSERT_TRUE(iSp0_80_85 >= 5 && iSp0_80_85 <= 10);
    ASSERT_TRUE(iSp0_50_80 >= 31 && iSp0_50_80 <= 41);
    ASSERT_TRUE(iSp0_15_45 >= 23 && iSp0_15_45 <= 37);

    for (i = 0; i < iNumSpecies; i++) {
      EXPECT_EQ(p_iC[i], 10000);
    }

    //Check the results grid
    iNumXCells = p_oResults->GetNumberXCells();
    iNumYCells = p_oResults->GetNumberYCells();
    for (iX = 0; iX < iNumXCells; iX++) {
      for (iY = 0; iY < iNumYCells; iY++) {
        for (i = 0; i < iNumSpecies; i++) {
          sLabel << "Cut Seedlings_" << i;
          p_oResults->GetValueOfCell(iX, iY, p_oResults->GetIntDataCode(sLabel.str()), &j);
          EXPECT_EQ(0, j);
          sLabel.str("");
        }
      }
    }
    delete[] p_iC;
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete[] p_iC;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// DoHarvestRun3()
// Performs the third harvest run.  This run has the following characteristics:
//
// Harvest # |TS |Cut Ranges |Species |Cut Type |Cut Amt (abs) |Grids
//-----------|---|-----------|--------|---------|--------------|---------------
// 1         |1  |15-45,     |6, 7    |Abs Den  |1             |Whole plot
//           |   |50-80,     |        |         |              |
//           |   |80-85,     |        |         |              |
//           |   |90-100     |        |         |              |
//
// The harvest will be performed.  Then the remaining trees are checked to make
// sure the proper ones were left alone.
/////////////////////////////////////////////////////////////////////////////
TEST(Harvest, DoHarvestRun3) {

  clTreePopulation * p_oPop;
  clTreeSearch *p_oAllTrees;
  clTree *p_oTree;
  clGrid *p_oResults;
  std::stringstream sLabel;
  int *p_iC = new int[4];
  float fTemp;
  int iNumXCells, iNumYCells, iNumSpecies, iX, iY, i, j, k,
  iSp6_90_99 = 0, iSp6_80_85 = 0, iSp6_50_80 = 0, iSp6_15_45 = 0,
  iSp7_90_99 = 0, iSp7_80_85 = 0, iSp7_50_80 = 0, iSp7_15_45 = 0;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    p_oSimManager->ReadFile( WriteHarvestXMLFile3() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
    p_oResults = p_oSimManager->GetGridObject("Harvest Results");

    //Add a bunch of seedlings to check seedling destruction
    iNumXCells = p_oPop->GetNumXCells();
    iNumYCells = p_oPop->GetNumYCells();
    iNumSpecies = p_oPop->GetNumberOfSpecies();
    fTemp = p_oPop->GetGridCellSize();
    p_iC[0] = 1; p_iC[1] = 3; p_iC[2] = 5; p_iC[3] = 7;
    for (iX = 0; iX < iNumXCells; iX++) {
      for (iY = 0; iY < iNumYCells; iY++) {
        for (i = 0; i < iNumSpecies; i++) {
          for (j = 0; j < 4; j++) {
            for (k = 0; k < 4; k++) {
              p_oPop->CreateTree((iX * fTemp) + p_iC[j],
                  (iY * fTemp) + p_iC[k], i, clTreePopulation::seedling, 0);
            }
          }
        }
      }
    }
    delete[] p_iC;

    //*********************************************
    // Timestep 1
    //*********************************************
    //Run the first timestep
    p_oSimManager->RunSim(1);

    //Count up the trees in our size classes
    p_iC = new int[iNumSpecies];
    for (i = 0; i < iNumSpecies; i++) p_iC[i] = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      if (p_oTree->GetType() == clTreePopulation::sapling ||
          p_oTree->GetType() == clTreePopulation::adult) {
        if (p_oTree->GetSpecies() == 7) {

          p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);

          if (fTemp >= 90 && fTemp <= 100)
            iSp7_90_99++;
          else if (fTemp >= 80 && fTemp <= 85)
            iSp7_80_85++;
          else if (fTemp >= 50 && fTemp <= 80)
            iSp7_50_80++;
          else if (fTemp >= 15 && fTemp <= 45)
            iSp7_15_45++;

        } else if (p_oTree->GetSpecies() == 6) {

          p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);

          if (fTemp >= 90 && fTemp <= 100)
            iSp6_90_99++;
          else if (fTemp >= 80 && fTemp <= 85)
            iSp6_80_85++;
          else if (fTemp >= 50 && fTemp <= 80)
            iSp6_50_80++;
          else if (fTemp >= 15 && fTemp <= 45)
            iSp6_15_45++;
        }
      } else if (p_oTree->GetType() == clTreePopulation::seedling) {
        p_iC[p_oTree->GetSpecies()]++;
      }

      p_oTree = p_oAllTrees->NextTree();
    }

    EXPECT_EQ(iSp7_90_99, 16);
    EXPECT_EQ(iSp7_80_85, 3);
    EXPECT_EQ(iSp7_50_80, 56);
    EXPECT_EQ(iSp7_15_45, 55);
    EXPECT_EQ(iSp6_90_99, 16);
    EXPECT_EQ(iSp6_80_85, 8);
    EXPECT_EQ(iSp6_50_80, 56);
    EXPECT_EQ(iSp6_15_45, 56);

    for (i = 0; i < iNumSpecies; i++) {
      EXPECT_EQ(p_iC[i], 10000);
    }

    //Check the results grid
    iNumXCells = p_oResults->GetNumberXCells();
    iNumYCells = p_oResults->GetNumberYCells();
    for (iX = 0; iX < iNumXCells; iX++) {
      for (iY = 0; iY < iNumYCells; iY++) {
        for (i = 0; i < iNumSpecies; i++) {
          sLabel << "Cut Seedlings_" << i;
          p_oResults->GetValueOfCell(iX, iY, p_oResults->GetIntDataCode(sLabel.str()), &j);
          EXPECT_EQ(0, j);
          sLabel.str("");
        }
      }
    }
    delete[] p_iC;
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete[] p_iC;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// DoHarvestRun4()
// Performs the fourth harvest run. This run has the following characteristics:
//
// Harvest # |TS |Cut Ranges |Species |Cut Type |Cut Amt (abs) |Grids
//-----------|---|-----------|--------|---------|--------------|---------------
// 1         |2  |Min 0      |0, 1, 2 |Gap      |100%          |Whole plot
// 2         |2  |15-45,     |4, 5    |% BA     |50, 100, 30, 0|(0,0) - (5,9)
//           |   |50-80,     |        |         |              |
//           |   |80-85,     |        |         |              |
//           |   |90-100     |        |         |              |
// 3         |3  |200-300,   |4       |Abs BA   |50, 100, 30, 0|(6,6) - (6-24);
//           |   |50-80,     |        |         |              |(8,6) - (8-24)
//           |   |80-85,     |        |         |              |
//           |   |90-100     |        |         |              |
// 4         |3  |0-10,      |7       |% Dens   |50, 100, 30, 0|(0,0) - (5,9)
//           |   |10-20,     |        |         |              |
//           |   |20-30,     |        |         |              |
//           |   |30-40      |        |         |              |
//
// The harvest will be performed.  Then the remaining trees are checked to make
// sure the proper ones were left alone.
/////////////////////////////////////////////////////////////////////////////
TEST(Harvest, DoHarvestRun4) {
  clTreePopulation * p_oPop;
  clTreeSearch *p_oAllTrees;
  clTree *p_oTree;
  clGrid *p_oResults;
  std::stringstream sLabel;
  int *p_iC = new int[4], *p_iSeedlsOutside = NULL;
  float fTemp;
  int iNumXCells, iNumYCells, iNumSpecies, iX, iY, j, k,
  iNumTrees = 1980, iCounter = 0, i;
  //Fake tree structure
  treestruct *p_oFakeTrees = new treestruct[iNumTrees];

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    p_oSimManager->ReadFile( WriteHarvestXMLFile4() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
    p_oResults = p_oSimManager->GetGridObject("Harvest Results");

    //Add a bunch of seedlings to check seedling destruction
    iNumXCells = p_oPop->GetNumXCells();
    iNumYCells = p_oPop->GetNumYCells();
    iNumSpecies = p_oPop->GetNumberOfSpecies();
    fTemp = p_oPop->GetGridCellSize();
    p_iC[0] = 1; p_iC[1] = 3; p_iC[2] = 5; p_iC[3] = 7;
    for (iX = 0; iX < iNumXCells; iX++) {
      for (iY = 0; iY < iNumYCells; iY++) {
        for (i = 0; i < iNumSpecies; i++) {
          for (j = 0; j < 4; j++) {
            for (k = 0; k < 4; k++) {
              p_oPop->CreateTree((iX * fTemp) + p_iC[j],
                  (iY * fTemp) + p_iC[k], i, clTreePopulation::seedling, 0);
            }
          }
        }
      }
    }
    delete[] p_iC;

    //*********************************************
    // Timestep 1
    //*********************************************
    //Run the first timestep
    p_oSimManager->RunSim(1);

    //Verify that there was no harvest
    iNumSpecies = p_oPop->GetNumberOfSpecies();
    int *p_iSpCount = new int[iNumSpecies];
    p_iC = new int[iNumSpecies];
    for (i = 0; i < iNumSpecies; i++) {
      p_iSpCount[i] = 0;
      p_iC[i] = 0;
    }

    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (p_oTree->GetType() == clTreePopulation::sapling ||
          p_oTree->GetType() == clTreePopulation::adult) {
        p_iSpCount[p_oTree->GetSpecies()]++;
      } else if (p_oTree->GetType() == clTreePopulation::seedling) {
        p_iC[p_oTree->GetSpecies()]++;
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    for (i = 0; i < iNumSpecies; i++) {
      EXPECT_EQ(p_iSpCount[i], 220);
      EXPECT_EQ(p_iC[i], 10000);
    }

    delete[] p_iSpCount;

    //*********************************************
    // Timestep 2
    //*********************************************
    //Populate the fake tree struct with X and Y coords
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (p_oTree->GetType() > clTreePopulation::seedling) {

        p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
        p_oFakeTrees[iCounter].fX = fTemp;
        p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
        p_oFakeTrees[iCounter].fY = fTemp;
        p_oFakeTrees[iCounter].iSpecies = p_oTree->GetSpecies();
        p_oFakeTrees[iCounter].bDead = false;
        p_oFakeTrees[iCounter].bFound = false;

        iCounter++;
        if (iCounter == iNumTrees) break;
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    //Expected results
    //There should be nothing for species 0, 1, 2; for 4 and 5, do the specific trees
    for (i = 0; i < iNumTrees; i++) {
      if (0 == p_oFakeTrees[i].iSpecies || 1 == p_oFakeTrees[i].iSpecies || 2 == p_oFakeTrees[i].iSpecies) {
        p_oFakeTrees[i].bDead = true;
      }
      else if (fabs(p_oFakeTrees[i].fX - 30.957) < 0.001 && fabs(p_oFakeTrees[i].fY - 52.1729) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 20.5322) < 0.001 && fabs(p_oFakeTrees[i].fY - 41.9495) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 39.9719) < 0.001 && fabs(p_oFakeTrees[i].fY - 77.1362) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 19.3359) < 0.001 && fabs(p_oFakeTrees[i].fY - 27.6611) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 13.7268) < 0.001 && fabs(p_oFakeTrees[i].fY - 27.3499) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 28.3142) < 0.001 && fabs(p_oFakeTrees[i].fY - 53.8513) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 39.2273) < 0.001 && fabs(p_oFakeTrees[i].fY - 1.5686) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 33.5754) < 0.001 && fabs(p_oFakeTrees[i].fY - 2.94189) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 15.1917) < 0.001 && fabs(p_oFakeTrees[i].fY - 47.8943) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 47.229) < 0.001 && fabs(p_oFakeTrees[i].fY - 1.01318) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 40.8142) < 0.001 && fabs(p_oFakeTrees[i].fY - 30.3772) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 30.6702) < 0.001 && fabs(p_oFakeTrees[i].fY - 74.1028) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 39.3311) < 0.001 && fabs(p_oFakeTrees[i].fY - 55.3711) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 0.219727) < 0.001 && fabs(p_oFakeTrees[i].fY - 45.8801) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 15.5945) < 0.001 && fabs(p_oFakeTrees[i].fY - 8.71582) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 25.1953) < 0.001 && fabs(p_oFakeTrees[i].fY - 8.25806) < 0.001) p_oFakeTrees[i].bDead = true;
    }

    //Run the sim and check the results
    p_oSimManager->RunSim(1);
    CheckHarvestResults(p_oPop, iNumTrees, p_oFakeTrees);
    for (i = 0; i < iNumSpecies; i++) p_iC[i] = 0;
    p_oAllTrees = p_oPop->Find("type=1");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_iC[p_oTree->GetSpecies()]++;
      p_oTree = p_oAllTrees->NextTree();
    }
    for (i = 0; i < iNumSpecies; i++) {
      if (i < 6) EXPECT_LT(p_iC[i] > 4500 && p_iC[i], 5500);
      else EXPECT_EQ(p_iC[i], 10000);
    }

    //Check the results grid
    iNumXCells = p_oResults->GetNumberXCells();
    iNumYCells = p_oResults->GetNumberYCells();
    for (iX = 0; iX < iNumXCells; iX++) {
      for (iY = 0; iY < iNumYCells; iY++) {
        for (i = 0; i < iNumSpecies; i++) {
          sLabel << "Cut Seedlings_" << i;
          p_oResults->GetValueOfCell(iX, iY, p_oResults->GetIntDataCode(sLabel.str()), &j);
          if (i < 6) EXPECT_LT(j > 1 && j, 15);
          else EXPECT_EQ(0, j);
          sLabel.str("");
        }
      }
    }

    //*********************************************
    // Timestep 3
    //*********************************************
    float fX, fY;
    int iSp7OutsideCut = 0, iSp7_0_10 = 0, iSp7_10_20 = 0, iSp7_20_30 = 0, iSp7_30_40 = 0;

    //Run the sim
    p_oSimManager->RunSim(1);
    p_iSeedlsOutside = new int[iNumSpecies];
    for (i = 0; i < iNumSpecies; i++) {
      p_iC[i] = 0;
      p_iSeedlsOutside[i] = 0;
    }
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
      p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
      if (p_oTree->GetType() == clTreePopulation::sapling ||
          p_oTree->GetType() == clTreePopulation::adult) {

        //Make sure the correct species 4 trees have been cut - they shouldn't show up
        EXPECT_TRUE((fabs(fX - 67.5964) < 0.001 || fabs(fY - 94.4275) > 0.001) &&
            (fabs(fX - 51.9287) > 0.001 || fabs(fY - 131.873) > 0.001) &&
            (fabs(fX - 54.5044) > 0.001 || fabs(fY - 85.0464) > 0.001));

        //Count the species 7 trees both within the cut area and outside it
        if (7 == p_oTree->GetSpecies()) {
          if (fX >= 48 || fY >= 80) {
            //This tree is outside the cut area
            iSp7OutsideCut++;
          } else {

            //Get the DBH
            p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);

            if (fTemp >= 0 && fTemp <= 10)
              iSp7_0_10++;
            else if (fTemp >= 10 && fTemp <= 20)
              iSp7_10_20++;
            else if (fTemp >= 20 && fTemp <= 30)
              iSp7_20_30++;
            else if (fTemp >= 30 && fTemp <= 40)
              iSp7_30_40++;
          }
        }
      } else if (p_oTree->GetType() == clTreePopulation::seedling) {
        if (fX >= 48 || fY >= 80) {
          p_iSeedlsOutside[p_oTree->GetSpecies()]++;
        } else {
          p_iC[p_oTree->GetSpecies()]++;
        }
      }

      p_oTree = p_oAllTrees->NextTree();
    }

    //Make sure there were no trees cut outside the cut area
    EXPECT_EQ(197, iSp7OutsideCut);
    for (i = 6; i < iNumSpecies; i++) {
      EXPECT_EQ(p_iSeedlsOutside[i], 9040);
    }

    //Make sure the right number of trees within the cut were cut
    ASSERT_TRUE(1 <= iSp7_0_10 || 4 >= iSp7_0_10);
    EXPECT_EQ(0, iSp7_10_20);
    EXPECT_EQ(0, iSp7_20_30);
    EXPECT_EQ(4, iSp7_30_40);
    EXPECT_LT(p_iC[6] > 650 && p_iC[6], 800);
    EXPECT_EQ(p_iC[7], 960);
    EXPECT_EQ(p_iC[8], 960);

    //Check the results grid
    iNumXCells = p_oResults->GetNumberXCells();
    iNumYCells = p_oResults->GetNumberYCells();
    for (iX = 0; iX < iNumXCells; iX++) {
      for (iY = 0; iY < iNumYCells; iY++) {
        if (iX > 5 || iY > 9) {
          for (i = 0; i < iNumSpecies; i++) {
            sLabel << "Cut Seedlings_" << i;
            p_oResults->GetValueOfCell(iX, iY, p_oResults->GetIntDataCode(sLabel.str()), &j);
            EXPECT_EQ(0, j);
            sLabel.str("");
          }
        } else {
          for (i = 0; i < iNumSpecies; i++) {
            sLabel << "Cut Seedlings_" << i;
            p_oResults->GetValueOfCell(iX, iY, p_oResults->GetIntDataCode(sLabel.str()), &j);
            if (i == 6)
              EXPECT_LT(j > 0 && j, 10);
            else EXPECT_EQ(0, j);
            sLabel.str("");
          }
        }
      }
    }


    delete[] p_oFakeTrees;
    delete[] p_iC;
    delete[] p_iSeedlsOutside;

    delete p_oSimManager;
  } catch (modelErr &e) {
    delete[] p_oFakeTrees;
    delete[] p_iC;
    delete[] p_iSeedlsOutside;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// DoHarvestRun5()
// Performs the fifth harvest run. This run has the following characteristics:
//
// Harvest # |TS |Cut Ranges |Species |Cut Type |Cut Amt (abs) |Grids
//-----------|---|-----------|--------|---------|--------------|---------------
// 1         |1  |0-10,      |0-8     |Abs Den  |5, 100, 3, 0  |(6,6) - (6-24);
//           |   |10-20,     |        |         |              |(8,0) - (24-12)
//           |   |20-30,     |        |         |              |
//           |   |30-40      |        |         |              |
//
// The harvest will be performed.  Then the remaining trees are checked to make
// sure the proper ones were left alone.
/////////////////////////////////////////////////////////////////////////////
TEST(Harvest, DoHarvestRun5) {
  clTreePopulation * p_oPop;
  clTreeSearch *p_oAllTrees;
  clTree *p_oTree;
  clGrid *p_oResults;
  int *p_iC = new int[4];
  std::stringstream sLabel;
  float fTemp, fX, fY;
  int iNumXCells, iNumYCells, iNumSpecies, iX, iY, j, k,
  iNumTrees = 1980, iCounter = 0, i;
  //Fake tree structure
  treestruct *p_oFakeTrees = new treestruct[iNumTrees];

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {

    p_oSimManager->ReadFile( WriteHarvestXMLFile5() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
    p_oResults = p_oSimManager->GetGridObject("Harvest Results");

    //Add a bunch of seedlings to check seedling destruction
    iNumXCells = p_oPop->GetNumXCells();
    iNumYCells = p_oPop->GetNumYCells();
    iNumSpecies = p_oPop->GetNumberOfSpecies();
    fTemp = p_oPop->GetGridCellSize();
    p_iC[0] = 1; p_iC[1] = 3; p_iC[2] = 5; p_iC[3] = 7;
    for (iX = 0; iX < iNumXCells; iX++) {
      for (iY = 0; iY < iNumYCells; iY++) {
        for (i = 0; i < iNumSpecies; i++) {
          for (j = 0; j < 4; j++) {
            for (k = 0; k < 4; k++) {
              p_oPop->CreateTree((iX * fTemp) + p_iC[j],
                  (iY * fTemp) + p_iC[k], i, clTreePopulation::seedling, 0);
            }
          }
        }
      }
    }
    delete[] p_iC;

    //*********************************************
    // Timestep 1
    //*********************************************
    //Populate the fake tree struct with X and Y coords
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (p_oTree->GetType() > clTreePopulation::seedling) {

        p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
        p_oFakeTrees[iCounter].fX = fTemp;
        p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
        p_oFakeTrees[iCounter].fY = fTemp;
        p_oFakeTrees[iCounter].iSpecies = p_oTree->GetSpecies();
        p_oFakeTrees[iCounter].bDead = false;
        p_oFakeTrees[iCounter].bFound = false;

        iCounter++;
        if (iCounter == iNumTrees) break;
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    //Expected results
    for (i = 0; i < iNumTrees; i++) {
      if (fabs(p_oFakeTrees[i].fX - 136.267) < 0.001 && fabs(p_oFakeTrees[i].fY - 67.7246) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 195.917) < 0.001 && fabs(p_oFakeTrees[i].fY - 49.1394) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 75.8118) < 0.001 && fabs(p_oFakeTrees[i].fY - 50.47) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 64.4714) < 0.001 && fabs(p_oFakeTrees[i].fY - 30.3589) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 177.155) < 0.001 && fabs(p_oFakeTrees[i].fY - 29.1626) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 143.604) < 0.001 && fabs(p_oFakeTrees[i].fY - 57.1594) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 179.663) < 0.001 && fabs(p_oFakeTrees[i].fY - 14.4348) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 196.722) < 0.001 && fabs(p_oFakeTrees[i].fY - 2.92969) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 130.17) < 0.001 && fabs(p_oFakeTrees[i].fY - 25.415) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 139.703) < 0.001 && fabs(p_oFakeTrees[i].fY - 44.696) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 98.4802) < 0.001 && fabs(p_oFakeTrees[i].fY - 35.0342) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 197.339) < 0.001 && fabs(p_oFakeTrees[i].fY - 91.4429) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 90.4602) < 0.001 && fabs(p_oFakeTrees[i].fY - 47.4609) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 122.552) < 0.001 && fabs(p_oFakeTrees[i].fY - 16.3757) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 147.51) < 0.001 && fabs(p_oFakeTrees[i].fY - 101.953) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 189.734) < 0.001 && fabs(p_oFakeTrees[i].fY - 42.5415) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 110.699) < 0.001 && fabs(p_oFakeTrees[i].fY - 102.142) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 81.7261) < 0.001 && fabs(p_oFakeTrees[i].fY - 48.0835) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 154.218) < 0.001 && fabs(p_oFakeTrees[i].fY - 50.7324) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 147.186) < 0.001 && fabs(p_oFakeTrees[i].fY - 92.2607) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 71.0205) < 0.001 && fabs(p_oFakeTrees[i].fY - 80.9814) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 107.391) < 0.001 && fabs(p_oFakeTrees[i].fY - 39.1541) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 92.2119) < 0.001 && fabs(p_oFakeTrees[i].fY - 77.3071) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 110.84) < 0.001 && fabs(p_oFakeTrees[i].fY - 29.3152) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 77.9175) < 0.001 && fabs(p_oFakeTrees[i].fY - 94.0369) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 184.857) < 0.001 && fabs(p_oFakeTrees[i].fY - 91.0767) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 123.09) < 0.001 && fabs(p_oFakeTrees[i].fY - 65.5579) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 140.552) < 0.001 && fabs(p_oFakeTrees[i].fY - 58.1909) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 48.0469) < 0.001 && fabs(p_oFakeTrees[i].fY - 89.1907) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 121.405) < 0.001 && fabs(p_oFakeTrees[i].fY - 59.0332) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 173.615) < 0.001 && fabs(p_oFakeTrees[i].fY - 71.2341) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 179.48) < 0.001 && fabs(p_oFakeTrees[i].fY - 100.677) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 98.8159) < 0.001 && fabs(p_oFakeTrees[i].fY - 7.02515) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 98.0896) < 0.001 && fabs(p_oFakeTrees[i].fY - 102.673) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 105.298) < 0.001 && fabs(p_oFakeTrees[i].fY - 63.4949) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 157.025) < 0.001 && fabs(p_oFakeTrees[i].fY - 61.7126) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 51.1841) < 0.001 && fabs(p_oFakeTrees[i].fY - 48.3032) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 71.5698) < 0.001 && fabs(p_oFakeTrees[i].fY - 29.4067) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 67.3645) < 0.001 && fabs(p_oFakeTrees[i].fY - 97.4365) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 67.4255) < 0.001 && fabs(p_oFakeTrees[i].fY - 15.8325) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 179.309) < 0.001 && fabs(p_oFakeTrees[i].fY - 42.7917) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 129.095) < 0.001 && fabs(p_oFakeTrees[i].fY - 10.0342) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 48.4192) < 0.001 && fabs(p_oFakeTrees[i].fY - 126.709) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 172.485) < 0.001 && fabs(p_oFakeTrees[i].fY - 27.6489) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 92.0227) < 0.001 && fabs(p_oFakeTrees[i].fY - 33.3191) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 174.994) < 0.001 && fabs(p_oFakeTrees[i].fY - 72.1741) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 102.997) < 0.001 && fabs(p_oFakeTrees[i].fY - 7.56836) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 128.888) < 0.001 && fabs(p_oFakeTrees[i].fY - 63.7573) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 93.9453) < 0.001 && fabs(p_oFakeTrees[i].fY - 67.4561) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 105.121) < 0.001 && fabs(p_oFakeTrees[i].fY - 96.4417) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 93.335) < 0.001 && fabs(p_oFakeTrees[i].fY - 99.4446) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 189.703) < 0.001 && fabs(p_oFakeTrees[i].fY - 65.1428) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 48.3582) < 0.001 && fabs(p_oFakeTrees[i].fY - 180.725) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 163.367) < 0.001 && fabs(p_oFakeTrees[i].fY - 33.5144) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 157.66) < 0.001 && fabs(p_oFakeTrees[i].fY - 81.9031) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 198.608) < 0.001 && fabs(p_oFakeTrees[i].fY - 44.8059) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 176.904) < 0.001 && fabs(p_oFakeTrees[i].fY - 15.1733) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 123.419) < 0.001 && fabs(p_oFakeTrees[i].fY - 23.3643) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 133.496) < 0.001 && fabs(p_oFakeTrees[i].fY - 46.814) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 156.732) < 0.001 && fabs(p_oFakeTrees[i].fY - 37.8967) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 164.307) < 0.001 && fabs(p_oFakeTrees[i].fY - 34.2468) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 114.716) < 0.001 && fabs(p_oFakeTrees[i].fY - 93.7927) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 173.889) < 0.001 && fabs(p_oFakeTrees[i].fY - 25.5005) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 184.509) < 0.001 && fabs(p_oFakeTrees[i].fY - 15.5151) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 156.14) < 0.001 && fabs(p_oFakeTrees[i].fY - 49.0234) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 84.7778) < 0.001 && fabs(p_oFakeTrees[i].fY - 71.5393) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 51.3123) < 0.001 && fabs(p_oFakeTrees[i].fY - 173.602) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 188.025) < 0.001 && fabs(p_oFakeTrees[i].fY - 81.7993) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 151.245) < 0.001 && fabs(p_oFakeTrees[i].fY - 5.10254) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 151.813) < 0.001 && fabs(p_oFakeTrees[i].fY - 70.7886) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 185.931) < 0.001 && fabs(p_oFakeTrees[i].fY - 79.3701) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 50.6348) < 0.001 && fabs(p_oFakeTrees[i].fY - 66.4795) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 151.3) < 0.001 && fabs(p_oFakeTrees[i].fY - 100.049) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 136.108) < 0.001 && fabs(p_oFakeTrees[i].fY - 62.5061) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 148.279) < 0.001 && fabs(p_oFakeTrees[i].fY - 52.0447) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 101.331) < 0.001 && fabs(p_oFakeTrees[i].fY - 97.9858) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 91.1743) < 0.001 && fabs(p_oFakeTrees[i].fY - 12.4817) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 86.2854) < 0.001 && fabs(p_oFakeTrees[i].fY - 59.3201) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 89.1785) < 0.001 && fabs(p_oFakeTrees[i].fY - 100.226) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 189.929) < 0.001 && fabs(p_oFakeTrees[i].fY - 35.6934) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 55.7434) < 0.001 && fabs(p_oFakeTrees[i].fY - 180.17) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 54.0466) < 0.001 && fabs(p_oFakeTrees[i].fY - 167.749) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 169.672) < 0.001 && fabs(p_oFakeTrees[i].fY - 46.7957) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 137.219) < 0.001 && fabs(p_oFakeTrees[i].fY - 70.6909) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 54.8035) < 0.001 && fabs(p_oFakeTrees[i].fY - 99.3835) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 80.8533) < 0.001 && fabs(p_oFakeTrees[i].fY - 11.792) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 139.685) < 0.001 && fabs(p_oFakeTrees[i].fY - 47.9431) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 78.2898) < 0.001 && fabs(p_oFakeTrees[i].fY - 58.9966) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 184.003) < 0.001 && fabs(p_oFakeTrees[i].fY - 99.0662) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 105.353) < 0.001 && fabs(p_oFakeTrees[i].fY - 62.1765) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 173.914) < 0.001 && fabs(p_oFakeTrees[i].fY - 81.2988) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 88.678) < 0.001 && fabs(p_oFakeTrees[i].fY - 77.5269) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 158.167) < 0.001 && fabs(p_oFakeTrees[i].fY - 76.5991) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 181.494) < 0.001 && fabs(p_oFakeTrees[i].fY - 95.4712) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 175.818) < 0.001 && fabs(p_oFakeTrees[i].fY - 90.9851) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 49.5972) < 0.001 && fabs(p_oFakeTrees[i].fY - 123.993) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 98.4619) < 0.001 && fabs(p_oFakeTrees[i].fY - 67.1326) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 199.5) < 0.001 && fabs(p_oFakeTrees[i].fY - 7.44629) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 169.58) < 0.001 && fabs(p_oFakeTrees[i].fY - 59.4971) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 55.3345) < 0.001 && fabs(p_oFakeTrees[i].fY - 151.379) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 127.332) < 0.001 && fabs(p_oFakeTrees[i].fY - 33.3374) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 51.6235) < 0.001 && fabs(p_oFakeTrees[i].fY - 172.089) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 197.919) < 0.001 && fabs(p_oFakeTrees[i].fY - 47.9004) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 186.731) < 0.001 && fabs(p_oFakeTrees[i].fY - 26.825) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 66.0767) < 0.001 && fabs(p_oFakeTrees[i].fY - 57.2632) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 132.764) < 0.001 && fabs(p_oFakeTrees[i].fY - 44.5862) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 120.709) < 0.001 && fabs(p_oFakeTrees[i].fY - 69.2139) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 106.915) < 0.001 && fabs(p_oFakeTrees[i].fY - 10.26) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 84.5459) < 0.001 && fabs(p_oFakeTrees[i].fY - 21.6858) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 99.115) < 0.001 && fabs(p_oFakeTrees[i].fY - 25.6531) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 90.1855) < 0.001 && fabs(p_oFakeTrees[i].fY - 89.4592) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 140.363) < 0.001 && fabs(p_oFakeTrees[i].fY - 85.2173) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 156.238) < 0.001 && fabs(p_oFakeTrees[i].fY - 94.2017) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 137.091) < 0.001 && fabs(p_oFakeTrees[i].fY - 99.7742) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 169.568) < 0.001 && fabs(p_oFakeTrees[i].fY - 60.3699) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 101.215) < 0.001 && fabs(p_oFakeTrees[i].fY - 69.3787) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 90.1978) < 0.001 && fabs(p_oFakeTrees[i].fY - 17.0593) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 143.707) < 0.001 && fabs(p_oFakeTrees[i].fY - 1.84326) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 53.4119) < 0.001 && fabs(p_oFakeTrees[i].fY - 133.685) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 145.813) < 0.001 && fabs(p_oFakeTrees[i].fY - 10.6445) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 130.383) < 0.001 && fabs(p_oFakeTrees[i].fY - 8.25806) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 174.414) < 0.001 && fabs(p_oFakeTrees[i].fY - 28.6072) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 105.475) < 0.001 && fabs(p_oFakeTrees[i].fY - 52.0325) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 178.711) < 0.001 && fabs(p_oFakeTrees[i].fY - 82.0801) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 91.6382) < 0.001 && fabs(p_oFakeTrees[i].fY - 69.7205) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 128.455) < 0.001 && fabs(p_oFakeTrees[i].fY - 81.2683) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 53.9185) < 0.001 && fabs(p_oFakeTrees[i].fY - 142.413) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 49.6765) < 0.001 && fabs(p_oFakeTrees[i].fY - 185.339) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 116.187) < 0.001 && fabs(p_oFakeTrees[i].fY - 45.4407) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 187.518) < 0.001 && fabs(p_oFakeTrees[i].fY - 38.5193) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 90.0757) < 0.001 && fabs(p_oFakeTrees[i].fY - 102.545) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 158.862) < 0.001 && fabs(p_oFakeTrees[i].fY - 27.1667) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 168.28) < 0.001 && fabs(p_oFakeTrees[i].fY - 64.1663) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 130.402) < 0.001 && fabs(p_oFakeTrees[i].fY - 102.631) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 148.657) < 0.001 && fabs(p_oFakeTrees[i].fY - 34.4299) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 119.757) < 0.001 && fabs(p_oFakeTrees[i].fY - 93.158) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 83.8867) < 0.001 && fabs(p_oFakeTrees[i].fY - 17.7673) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 141.846) < 0.001 && fabs(p_oFakeTrees[i].fY - 25.4822) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 195.447) < 0.001 && fabs(p_oFakeTrees[i].fY - 85.9009) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 175.232) < 0.001 && fabs(p_oFakeTrees[i].fY - 20.4346) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 113.94) < 0.001 && fabs(p_oFakeTrees[i].fY - 63.6169) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 135.791) < 0.001 && fabs(p_oFakeTrees[i].fY - 101.55) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 140.826) < 0.001 && fabs(p_oFakeTrees[i].fY - 79.1626) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 152.411) < 0.001 && fabs(p_oFakeTrees[i].fY - 103.461) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 106.128) < 0.001 && fabs(p_oFakeTrees[i].fY - 53.6987) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 48.0225) < 0.001 && fabs(p_oFakeTrees[i].fY - 85.2478) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 172.07) < 0.001 && fabs(p_oFakeTrees[i].fY - 42.9016) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 113.251) < 0.001 && fabs(p_oFakeTrees[i].fY - 74.4202) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 121.002) < 0.001 && fabs(p_oFakeTrees[i].fY - 91.2903) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 125.256) < 0.001 && fabs(p_oFakeTrees[i].fY - 11.2305) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 173.645) < 0.001 && fabs(p_oFakeTrees[i].fY - 45.1538) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 187.701) < 0.001 && fabs(p_oFakeTrees[i].fY - 35.4858) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 195.807) < 0.001 && fabs(p_oFakeTrees[i].fY - 31.6833) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 167.108) < 0.001 && fabs(p_oFakeTrees[i].fY - 63.3179) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 141.107) < 0.001 && fabs(p_oFakeTrees[i].fY - 87.3779) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 129.7) < 0.001 && fabs(p_oFakeTrees[i].fY - 83.1299) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 79.0283) < 0.001 && fabs(p_oFakeTrees[i].fY - 81.2012) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 189.771) < 0.001 && fabs(p_oFakeTrees[i].fY - 39.679) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 106.213) < 0.001 && fabs(p_oFakeTrees[i].fY - 31.1951) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 51.3794) < 0.001 && fabs(p_oFakeTrees[i].fY - 174.731) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 141.724) < 0.001 && fabs(p_oFakeTrees[i].fY - 10.6445) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 99.823) < 0.001 && fabs(p_oFakeTrees[i].fY - 86.7126) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 156.36) < 0.001 && fabs(p_oFakeTrees[i].fY - 5.97534) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 194.482) < 0.001 && fabs(p_oFakeTrees[i].fY - 28.7781) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 67.9443) < 0.001 && fabs(p_oFakeTrees[i].fY - 85.4553) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 159.839) < 0.001 && fabs(p_oFakeTrees[i].fY - 6.12793) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 128.308) < 0.001 && fabs(p_oFakeTrees[i].fY - 80.2185) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 157.77) < 0.001 && fabs(p_oFakeTrees[i].fY - 1.48315) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 83.5083) < 0.001 && fabs(p_oFakeTrees[i].fY - 33.606) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 100.848) < 0.001 && fabs(p_oFakeTrees[i].fY - 33.0505) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 49.0234) < 0.001 && fabs(p_oFakeTrees[i].fY - 150.153) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 167.572) < 0.001 && fabs(p_oFakeTrees[i].fY - 90.1428) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 138.226) < 0.001 && fabs(p_oFakeTrees[i].fY - 100.714) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 192.053) < 0.001 && fabs(p_oFakeTrees[i].fY - 32.5745) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 111.89) < 0.001 && fabs(p_oFakeTrees[i].fY - 25.5493) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 170.825) < 0.001 && fabs(p_oFakeTrees[i].fY - 20.7703) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 187.75) < 0.001 && fabs(p_oFakeTrees[i].fY - 88.2446) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 103.943) < 0.001 && fabs(p_oFakeTrees[i].fY - 93.4204) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 76.8799) < 0.001 && fabs(p_oFakeTrees[i].fY - 85.5164) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 141.443) < 0.001 && fabs(p_oFakeTrees[i].fY - 2.7771) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 82.428) < 0.001 && fabs(p_oFakeTrees[i].fY - 74.7192) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 51.5808) < 0.001 && fabs(p_oFakeTrees[i].fY - 51.0254) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 94.635) < 0.001 && fabs(p_oFakeTrees[i].fY - 61.8286) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 106.378) < 0.001 && fabs(p_oFakeTrees[i].fY - 90.6311) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 176.855) < 0.001 && fabs(p_oFakeTrees[i].fY - 47.522) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 170.459) < 0.001 && fabs(p_oFakeTrees[i].fY - 50.4333) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 110.254) < 0.001 && fabs(p_oFakeTrees[i].fY - 31.5369) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 157.703) < 0.001 && fabs(p_oFakeTrees[i].fY - 2.66724) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 195.99) < 0.001 && fabs(p_oFakeTrees[i].fY - 73.5718) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 179.285) < 0.001 && fabs(p_oFakeTrees[i].fY - 36.8896) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 151.453) < 0.001 && fabs(p_oFakeTrees[i].fY - 60.4126) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 174.658) < 0.001 && fabs(p_oFakeTrees[i].fY - 66.0217) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 110.284) < 0.001 && fabs(p_oFakeTrees[i].fY - 29.1565) < 0.001) p_oFakeTrees[i].bDead = true;
    }

    //Run the sim and check the results
    p_oSimManager->RunSim(1);
    CheckHarvestResults(p_oPop, iNumTrees, p_oFakeTrees);
    p_iC = new int[iNumSpecies];
    for (i = 0; i < iNumSpecies; i++) p_iC[i] = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
      p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
      if ((fX >= 48 && fX < 56 && fY >= 48) ||
          (fX >= 64 && fY < 96))
        ASSERT_TRUE(p_oTree->GetType() != clTreePopulation::seedling);
      else if (p_oTree->GetType() == clTreePopulation::seedling) {
        p_iC[p_oTree->GetSpecies()]++;
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    //240 cells in the cut area = 385 outside
    for (i = 0; i < iNumSpecies; i++) {
      EXPECT_EQ(p_iC[i], 6160);
    }

    //Check the results grid
    iNumXCells = p_oResults->GetNumberXCells();
    iNumYCells = p_oResults->GetNumberYCells();
    for (iX = 0; iX < iNumXCells; iX++) {
      for (iY = 0; iY < iNumYCells; iY++) {
        if ((iX == 6 && iY >= 6) || (iX >= 8 && iY <= 12)) {
          for (i = 0; i < iNumSpecies; i++) {
            sLabel << "Cut Seedlings_" << i;
            p_oResults->GetValueOfCell(iX, iY, p_oResults->GetIntDataCode(sLabel.str()), &j);
            EXPECT_EQ(16, j);
            sLabel.str("");
          }
        } else {
          for (i = 0; i < iNumSpecies; i++) {
            sLabel << "Cut Seedlings_" << i;
            p_oResults->GetValueOfCell(iX, iY, p_oResults->GetIntDataCode(sLabel.str()), &j);
            EXPECT_EQ(0, j);
            sLabel.str("");
          }
        }
      }
    }

    delete[] p_oFakeTrees;
    delete[] p_iC;

    delete p_oSimManager;
  } catch (modelErr &e) {
    delete[] p_oFakeTrees;
    delete[] p_iC;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// DoHarvestRun6()
// Performs the sixth harvest run.  This run has the following characteristics:
// Harvest # |TS |Cut Ranges |Species |Cut Type |Cut Amt (abs) |Grids
//-----------|---|-----------|--------|---------|--------------|---------------
// 1         |1  |Min 0      |3       |Clear    |100%          |(6,6) - (6-24); (8,6) - (8-24)
// 2         |2  |Min 0      |0       |Gap      |100%          |(0,0) - (5,9)
// 3         |3  |0 - 300    |1       |% BA     |50            |(0,10)
// 4         |3  |0 - 300    |2       |Abs BA   |4.5           |(5,5)
// 5         |3  |0 - 300    |4       |%Dens    |50            |(10,23)
// 6         |3  |0 - 300    |5       |Abs Den  |2             |(1,1)
// 7         |3  |Min 0      |6       |Clear    |100%          |(20,0)
// 8         |3  |Min 0      |7       |Gap      |100%          |(1,7)
// The harvest will be performed.  Then the remaining trees are checked to make
// sure the proper ones were left alone.
/////////////////////////////////////////////////////////////////////////////
TEST(Harvest, DoHarvestRun6) {
  clTreePopulation * p_oPop;
  clTreeSearch *p_oAllTrees;
  clTree *p_oTree;
  //clGrid *p_oResults;
  float fTemp;
  int iNumTrees = 1980, iCounter = 0, i;
  //Fake tree structure
  treestruct *p_oFakeTrees = new treestruct[iNumTrees];

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    p_oSimManager->ReadFile( WriteHarvestXMLFile6() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //*********************************************
    // Timestep 1
    //*********************************************
    //Populate the fake tree struct with X and Y coords
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
      p_oFakeTrees[iCounter].fX = fTemp;
      p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
      p_oFakeTrees[iCounter].fY = fTemp;
      p_oFakeTrees[iCounter].iSpecies = p_oTree->GetSpecies();
      p_oFakeTrees[iCounter].bDead = false;
      p_oFakeTrees[iCounter].bFound = false;

      iCounter++;
      if (iCounter == iNumTrees) break;
      p_oTree = p_oAllTrees->NextTree();
    }

    EXPECT_TRUE(p_oAllTrees->NextTree() == NULL);

    //Expected results
    for (i = 0; i < iNumTrees; i++) {

      if (fabs(p_oFakeTrees[i].fX - 50.6348) < 0.001 && fabs(p_oFakeTrees[i].fY - 66.4795) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 54.8035) < 0.001 && fabs(p_oFakeTrees[i].fY - 99.3835) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 54.8645) < 0.001 && fabs(p_oFakeTrees[i].fY - 114.319) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 54.0466) < 0.001 && fabs(p_oFakeTrees[i].fY - 167.749) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 55.7434) < 0.001 && fabs(p_oFakeTrees[i].fY - 180.17) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 69.635) < 0.001 && fabs(p_oFakeTrees[i].fY - 138.104) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 70.6238) < 0.001 && fabs(p_oFakeTrees[i].fY - 155.92) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 68.4326) < 0.001 && fabs(p_oFakeTrees[i].fY - 168.573) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 70.9534) < 0.001 && fabs(p_oFakeTrees[i].fY - 177.576) < 0.001) p_oFakeTrees[i].bDead = true;

    }

    //Run the sim and check the results
    p_oSimManager->RunSim(1);
    CheckHarvestResults(p_oPop, iNumTrees, p_oFakeTrees);

    //*********************************************
    // Timestep 2
    //*********************************************
    //Expected results
    for (i = 0; i < iNumTrees; i++) {
      if (fabs(p_oFakeTrees[i].fX - 7.05566) < 0.001 && fabs(p_oFakeTrees[i].fY - 26.1169) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 6.06079) < 0.001 && fabs(p_oFakeTrees[i].fY - 43.5608) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 1.97754) < 0.001 && fabs(p_oFakeTrees[i].fY - 56.6833) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 6.65283) < 0.001 && fabs(p_oFakeTrees[i].fY - 71.1426) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 8.30078) < 0.001 && fabs(p_oFakeTrees[i].fY - 33.0322) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 15.8264) < 0.001 && fabs(p_oFakeTrees[i].fY - 54.3884) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 14.7827) < 0.001 && fabs(p_oFakeTrees[i].fY - 50.8606) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 11.6516) < 0.001 && fabs(p_oFakeTrees[i].fY - 65.9912) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 11.908) < 0.001 && fabs(p_oFakeTrees[i].fY - 76.7944) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 18.2556) < 0.001 && fabs(p_oFakeTrees[i].fY - 32.5623) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 17.0593) < 0.001 && fabs(p_oFakeTrees[i].fY - 35.7788) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 16.449) < 0.001 && fabs(p_oFakeTrees[i].fY - 49.4385) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 39.7461) < 0.001 && fabs(p_oFakeTrees[i].fY - 5.43823) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 34.0149) < 0.001 && fabs(p_oFakeTrees[i].fY - 27.0752) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 39.4165) < 0.001 && fabs(p_oFakeTrees[i].fY - 42.334) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 34.4666) < 0.001 && fabs(p_oFakeTrees[i].fY - 48.0591) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 37.8418) < 0.001 && fabs(p_oFakeTrees[i].fY - 48.4497) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 39.1602) < 0.001 && fabs(p_oFakeTrees[i].fY - 53.2349) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 35.4431) < 0.001 && fabs(p_oFakeTrees[i].fY - 65.979) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 47.8149) < 0.001 && fabs(p_oFakeTrees[i].fY - 42.8345) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 47.1985) < 0.001 && fabs(p_oFakeTrees[i].fY - 67.0959) < 0.001) p_oFakeTrees[i].bDead = true;
    }

    //Run the sim and check the results
    p_oSimManager->RunSim(1);
    CheckHarvestResults(p_oPop, iNumTrees, p_oFakeTrees);

    //*********************************************
    // Timestep 3
    //*********************************************
    //Expected results
    for (i = 0; i < iNumTrees; i++) {

      if (fabs(p_oFakeTrees[i].fX - 7.2937) < 0.001 && fabs(p_oFakeTrees[i].fY - 82.8491) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 1.30005) < 0.001 && fabs(p_oFakeTrees[i].fY - 85.4675) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 47.76) < 0.001 && fabs(p_oFakeTrees[i].fY - 42.3767) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 15.5945) < 0.001 && fabs(p_oFakeTrees[i].fY - 8.71582) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 13.9404) < 0.001 && fabs(p_oFakeTrees[i].fY - 10.8521) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 165.112) < 0.001 && fabs(p_oFakeTrees[i].fY - 6.23779) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 164.618) < 0.001 && fabs(p_oFakeTrees[i].fY - 6.66504) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 8.69751) < 0.001 && fabs(p_oFakeTrees[i].fY - 61.4624) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 14.5203) < 0.001 && fabs(p_oFakeTrees[i].fY - 60.9131) < 0.001) p_oFakeTrees[i].bDead = true;
    }

    //Run the sim and check the results
    p_oSimManager->RunSim(1);
    CheckHarvestResults(p_oPop, iNumTrees, p_oFakeTrees);


    delete[] p_oFakeTrees;
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete[] p_oFakeTrees;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

//Harvest run seven deliberately skipped...

/////////////////////////////////////////////////////////////////////////////
// DoHarvestRun8()
// Performs the eighth harvest run. This run has the following characteristics:
//
// Harvest # |TS |Cut Ranges |Species |Cut Type |Cut Amt (abs) |Grids
//-----------|---|-----------|--------|---------|--------------|---------------
// 1         |1  |Min 0      |All     |Clear    |100%          |(0,0) - (23,39)
//
// The harvest will be performed.  Then the remaining trees are checked to make
// sure the proper ones were left alone.
/////////////////////////////////////////////////////////////////////////////
TEST(Harvest, DoHarvestRun8) {
  clTreePopulation * p_oPop;
  clTreeSearch *p_oAllTrees;
  clTree *p_oTree;
  clGrid *p_oResults;
  std::stringstream sLabel;
  int *p_iC = new int[4];
  float fTemp, fX, fY;
  int iNumXCells, iNumYCells, iNumSpecies, iX, iY, j, k,
  iNumTrees = 1980, iCounter = 0, i;
  //Fake tree structure
  treestruct *p_oFakeTrees = new treestruct[iNumTrees];

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {

    p_oSimManager->ReadFile( WriteHarvestXMLFile8() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
    p_oResults = p_oSimManager->GetGridObject("Harvest Results");

    //Add a bunch of seedlings to check seedling destruction
    iNumXCells = p_oPop->GetNumXCells();
    iNumYCells = p_oPop->GetNumYCells();
    iNumSpecies = p_oPop->GetNumberOfSpecies();
    fTemp = p_oPop->GetGridCellSize();
    p_iC[0] = 1; p_iC[1] = 3; p_iC[2] = 5; p_iC[3] = 7;
    for (iX = 0; iX < iNumXCells; iX++) {
      for (iY = 0; iY < iNumYCells; iY++) {
        for (i = 0; i < iNumSpecies; i++) {
          for (j = 0; j < 4; j++) {
            for (k = 0; k < 4; k++) {
              p_oPop->CreateTree((iX * fTemp) + p_iC[j],
                  (iY * fTemp) + p_iC[k], i, clTreePopulation::seedling, 0);
            }
          }
        }
      }
    }
    delete[] p_iC;

    //*********************************************
    // Timestep 1
    //*********************************************

    //Populate the fake tree struct with X and Y coords
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (p_oTree->GetType() > clTreePopulation::seedling) {

        p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
        p_oFakeTrees[iCounter].fX = fTemp;
        p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
        p_oFakeTrees[iCounter].fY = fTemp;
        p_oFakeTrees[iCounter].iSpecies = p_oTree->GetSpecies();
        p_oFakeTrees[iCounter].bDead = false;
        p_oFakeTrees[iCounter].bFound = false;

        iCounter++;
        if (iCounter == iNumTrees) break;
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    //Expected results
    for (i = 0; i < iNumTrees; i++) {
      if (p_oFakeTrees[i].fX < 44 && p_oFakeTrees[i].fY < 74) {
        p_oFakeTrees[i].bDead = true;
      } else {
        p_oFakeTrees[i].bDead = false;
      }
    }

    //Run the sim and check the results
    p_oSimManager->RunSim(1);
    CheckHarvestResults(p_oPop, iNumTrees, p_oFakeTrees);

    p_iC = new int[iNumSpecies];
    for (i = 0; i < iNumSpecies; i++) p_iC[i] = 0;
    p_oAllTrees = p_oPop->Find("all");
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
      p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
      if (fX <= 44 && fY <= 74)
        ASSERT_TRUE(p_oTree->GetType() != clTreePopulation::seedling);
      else if (p_oTree->GetType() == clTreePopulation::seedling) {
        p_iC[p_oTree->GetSpecies()]++;
      }
      p_oTree = p_oAllTrees->NextTree();
    }
    for (i = 0; i < iNumSpecies; i++) {
      EXPECT_EQ(p_iC[i], 9186);
    }

    //Check the results grid
    iNumXCells = p_oResults->GetNumberXCells();
    iNumYCells = p_oResults->GetNumberYCells();
    for (iX = 0; iX < iNumXCells; iX++) {
      for (iY = 0; iY < iNumYCells; iY++) {
        if (iX <= 21 && iY <= 36) {
          for (i = 0; i < iNumSpecies; i++) {
            sLabel << "Cut Seedlings_" << i;
            p_oResults->GetValueOfCell(iX, iY, p_oResults->GetIntDataCode(sLabel.str()), &j);
            EXPECT_EQ(1, j);
            sLabel.str("");
          }
        } else {
          for (i = 0; i < iNumSpecies; i++) {
            sLabel << "Cut Seedlings_" << i;
            p_oResults->GetValueOfCell(iX, iY, p_oResults->GetIntDataCode(sLabel.str()), &j);
            EXPECT_EQ(0, j);
            sLabel.str("");
          }
        }
      }
    }

    delete[] p_oFakeTrees;
    delete[] p_iC;
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete[] p_oFakeTrees;
    delete[] p_iC;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// DoHarvestRun9()
// Performs the ninth harvest run. This tests priorities.
/////////////////////////////////////////////////////////////////////////////
TEST(Harvest, DoHarvestRun9) {

  clTreePopulation * p_oPop;
  clTreeSearch *p_oAllTrees;
  clTree *p_oTree;
  float fTemp, fDbh, fBA;
  int iNumInPriority, iNumInPriority2, iNumTotal, iTemp;
  bool bTemp;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {

    p_oSimManager->ReadFile( WriteHarvestXMLFile9() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Run harvest only
    p_oSimManager->SetCurrentTimestep(1);
    clBehaviorBase *p_oBase = p_oSimManager->GetBehaviorObject(0);
    clDisturbance *p_oHarv = dynamic_cast<clDisturbance*>(p_oBase);
    p_oHarv->Action();

    //*********************************************
    // Species 1
    //*********************************************
    //Count up the trees both in our priority and not
    iNumInPriority = 0;
    iNumTotal = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      if (p_oTree->GetSpecies() == 1) {

        p_oTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDbh);

        if (fDbh < 87 && fTemp >= 5 && fTemp <= 10)
          iNumInPriority++;
        iNumTotal++;
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    EXPECT_EQ(iNumInPriority, 38);
    EXPECT_EQ(iNumTotal, 180);

    //*********************************************
    // Species 2
    //*********************************************
    //Count up the trees both in our priority and not
    iNumInPriority = 0;
    iNumTotal = 0;
    p_oAllTrees->StartOver();
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      if (p_oTree->GetSpecies() == 2) {

        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDbh);

        if (fDbh >= 10 && fDbh <= 50)
          iNumInPriority++;
        iNumTotal++;
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    EXPECT_EQ(iNumInPriority, 60);
    EXPECT_EQ(iNumTotal, 200);

    //*********************************************
    // Species 3
    //*********************************************
    //Count up the trees both in our priority and not
    iNumInPriority = 0;
    iNumTotal = 0;
    p_oAllTrees->StartOver();
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      if (p_oTree->GetSpecies() == 3) {
        if (p_oTree->GetType() == clTreePopulation::sapling) {
          bTemp = false;
        } else {
          p_oTree->GetValue(p_oPop->GetBoolDataCode("vigorous", p_oTree->GetSpecies(), p_oTree->GetType()), &bTemp);
        }
        p_oTree->GetValue(p_oPop->GetIntDataCode("YearsInfested", p_oTree->GetSpecies(), p_oTree->GetType()), &iTemp);
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDbh);

        if (iTemp > 0 && bTemp && fDbh >= 10 && fDbh <= 50)
          iNumInPriority++;
        iNumTotal++;
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    EXPECT_EQ(iNumInPriority, 0);
    EXPECT_EQ(iNumTotal, 200);

    //*********************************************
    // Species 4
    //*********************************************
    //Count up the trees both in our priority and not
    iNumInPriority = 0;
    iNumTotal = 0;
    fBA = 0;
    p_oAllTrees->StartOver();
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      if (p_oTree->GetSpecies() == 4) {
        if (p_oTree->GetType() == clTreePopulation::sapling) {
          bTemp = false;
        } else {
          p_oTree->GetValue(p_oPop->GetBoolDataCode("vigorous", p_oTree->GetSpecies(), p_oTree->GetType()), &bTemp);
        }
        p_oTree->GetValue(p_oPop->GetIntDataCode("YearsInfested", p_oTree->GetSpecies(), p_oTree->GetType()), &iTemp);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDbh);

        fBA += clModelMath::CalculateBasalArea(fDbh);

        if (iTemp > 2 && bTemp && fTemp >= 5 && fTemp <= 10)
          iNumInPriority++;
        iNumTotal++;
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    EXPECT_EQ(iNumInPriority, 0);
    EXPECT_EQ(iNumTotal, 30);
    EXPECT_LT(fabs(7.758 - fBA), 0.001);

    //*********************************************
    // Species 6
    //*********************************************
    //Count up the trees both in our priority and not
    iNumInPriority = 0;
    iNumInPriority2 = 0;
    iNumTotal = 0;
    p_oAllTrees->StartOver();
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      if (p_oTree->GetSpecies() == 6) {
        if (p_oTree->GetType() == clTreePopulation::adult) {
          p_oTree->GetValue(p_oPop->GetIntDataCode("treeclass", p_oTree->GetSpecies(), p_oTree->GetType()), &iTemp);
        } else iTemp = -1;
        if (iTemp == 3)
          iNumInPriority++;
        else if (iTemp == 4)
          iNumInPriority2++;
        iNumTotal++;
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    EXPECT_EQ(iNumInPriority, 27);
    EXPECT_EQ(iNumInPriority2, 45);
    EXPECT_EQ(iNumTotal, 200);

    //*********************************************
    // Species 7
    //*********************************************
    //Count up the trees both in our priority and not
    iNumInPriority = 0;
    iNumInPriority2 = 0;
    iNumTotal = 0;
    fBA = 0;
    p_oAllTrees->StartOver();
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      if (p_oTree->GetSpecies() == 7) {
        if (p_oTree->GetType() == clTreePopulation::adult) {
          p_oTree->GetValue(p_oPop->GetIntDataCode("treeclass", p_oTree->GetSpecies(), p_oTree->GetType()), &iTemp);
        } else iTemp = -1;
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDbh);

        fBA += clModelMath::CalculateBasalArea(fDbh);
        if (iTemp == 3)
          iNumInPriority++;
        else if (iTemp == 4)
          iNumInPriority2++;

        iNumTotal++;
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    EXPECT_EQ(iNumInPriority, 0);
    EXPECT_EQ(iNumInPriority2, 46);
    EXPECT_EQ(iNumTotal, 170);
    EXPECT_LT(fabs(37.511 - fBA), 0.001);

    //*********************************************
    // Species 5
    //*********************************************
    //Count up the trees
    iNumInPriority = 0;
    iNumInPriority2 = 0;
    iNumTotal = 0;
    fTemp = 0;
    p_oAllTrees->StartOver();
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      if (p_oTree->GetSpecies() == 5) iNumTotal++;

      p_oTree = p_oAllTrees->NextTree();
    }

    EXPECT_EQ(iNumTotal, 180);

    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// CheckHarvestResults
/////////////////////////////////////////////////////////////////////////////
void CheckHarvestResults(clTreePopulation *p_oPop, int iNumTrees, treestruct *p_FakeTrees) {
  clTreeSearch *p_oAllTrees;
  clTree *p_oTree;
  float fX, fY;
  int i;

  //Set all the found tags to false
  for (i = 0; i < iNumTrees; i++) {
    p_FakeTrees[i].bFound = false;
  }

  //Go through all the trees and set to true those we find
  p_oAllTrees = p_oPop->Find("all");
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {

    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
    p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);

    for (i = 0; i < iNumTrees; i++) {
      if (fabs(p_FakeTrees[i].fX - fX) < 0.001 && fabs(p_FakeTrees[i].fY - fY) < 0.001) {
        if (p_FakeTrees[i].bDead) {
          //We found this tree, but it was supposed to be dead
          FAIL() << "Disturbance run failed - tree was supposed to be cut and wasn't.";
        }
        //Mark this tree as found
        p_FakeTrees[i].bFound = true;
      }
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  //Make sure that all live trees were found
  for (i = 0; i < iNumTrees; i++) {
    if (!p_FakeTrees[i].bDead && !p_FakeTrees[i].bFound) {
      //This tree was supposed to be there but wasn't
      FAIL() << "Disturbance run failed - tree was supposed to be alive but got cut.";
    }
  }
}


/////////////////////////////////////////////////////////////////////////////
// WriteHarvestXMLFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteHarvestXMLFile1()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteHarvestFileBeginning(oOut, 1);

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>Harvest</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "</behavior>"
      << "</behaviorList>"
      << "<Harvest1>"
      << "<ha_cutEvent>"
      << "<ha_applyToSpecies species=\"Amabilis_Fir\" />"
      << "<ha_applyToSpecies species=\"Paper_Birch\" />"
      << "<ha_timestep>3</ha_timestep>"
      << "<ha_cutType>clear</ha_cutType>"
      << "<ha_cutAmountType>percent of density</ha_cutAmountType>"
      << "<ha_dbhRange>"
      << "<ha_low>0.0</ha_low>"
      << "<ha_high>3000.0</ha_high>"
      << "<ha_amountToCut>100.0</ha_amountToCut>"
      << "</ha_dbhRange>";
  for (int i = 0; i < 25; i++) {
    for (int j = 0; j < 25; j++) {
      oOut << "<ha_applyToCell x=\"" << i << "\" y=\"" << j << "\" /> ";
    }
  }
  oOut << "</ha_cutEvent>"
      << "<ha_cutEvent>"
      << "<ha_applyToSpecies species=\"Lodgepole_Pine\" />"
      << "<ha_timestep>3</ha_timestep>"
      << "<ha_cutType>partial</ha_cutType>"
      << "<ha_cutAmountType>absolute basal area</ha_cutAmountType>"
      << "<ha_dbhRange>"
      << "<ha_low>0.0</ha_low>"
      << "<ha_high>30.0</ha_high>"
      << "<ha_amountToCut>0.2</ha_amountToCut>"
      << "</ha_dbhRange>"
      << "<ha_dbhRange>"
      << "<ha_low>40.0</ha_low>"
      << "<ha_high>80.0</ha_high>"
      << "<ha_amountToCut>0.2</ha_amountToCut>"
      << "</ha_dbhRange>";
  for (int i = 0; i < 25; i++) {
    for (int j = 0; j < 25; j++) {
      oOut << "<ha_applyToCell x=\"" << i << "\" y=\"" << j << "\" /> ";
    }
  }
  oOut << "</ha_cutEvent>"
      << "<ha_cutEvent>"
      << "<ha_applyToSpecies species=\"Amabilis_Fir\" />"
      << "<ha_applyToSpecies species=\"Hybrid_Spruce\" />"
      << "<ha_timestep>1</ha_timestep>"
      << "<ha_cutType>partial</ha_cutType>"
      << "<ha_cutAmountType>percent of basal area</ha_cutAmountType>"
      << "<ha_dbhRange>"
      << "<ha_low>0.0</ha_low>"
      << "<ha_high>300.0</ha_high>"
      << "<ha_amountToCut>35</ha_amountToCut>"
      << "</ha_dbhRange>"
      << "<ha_percentSeedlingsDie>"
      << "<ha_psdVal species=\"Amabilis_Fir\">100</ha_psdVal>"
      << "<ha_psdVal species=\"Hybrid_Spruce\">100</ha_psdVal>"
      << "<ha_psdVal species=\"Western_Hemlock\">0</ha_psdVal>"
      << "<ha_psdVal species=\"Western_Redcedar\">0</ha_psdVal>"
      << "<ha_psdVal species=\"Subalpine_Fir\">0</ha_psdVal>"
      << "<ha_psdVal species=\"Lodgepole_Pine\">0</ha_psdVal>"
      << "<ha_psdVal species=\"Trembling_Aspen\">0</ha_psdVal>"
      << "<ha_psdVal species=\"Black_Cottonwood\">0</ha_psdVal>"
      << "<ha_psdVal species=\"Paper_Birch\">0</ha_psdVal>"
      << "</ha_percentSeedlingsDie>";
  for (int i = 0; i < 25; i++) {
    for (int j = 0; j < 25; j++) {
      oOut << "<ha_applyToCell x=\"" << i << "\" y=\"" << j << "\" /> ";
    }
  }
  oOut << "</ha_cutEvent>"
      << "</Harvest1>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteHarvestXMLFile2()
/////////////////////////////////////////////////////////////////////////////
const char* WriteHarvestXMLFile2()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteHarvestFileBeginning(oOut, 2);

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>Harvest</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "</behavior>"
      << "</behaviorList>"
      << "<Harvest1>"
      << "<ha_cutEvent>"
      << "<ha_applyToSpecies species=\"Western_Redcedar\" />"
      << "<ha_applyToSpecies species=\"Western_Hemlock\" />"
      << "<ha_timestep>1</ha_timestep>"
      << "<ha_cutType>partial</ha_cutType>"
      << "<ha_cutAmountType>percent of density</ha_cutAmountType>"
      << "<ha_dbhRange>"
      << "<ha_low>15.0</ha_low>"
      << "<ha_high>45.0</ha_high>"
      << "<ha_amountToCut>50.0</ha_amountToCut>"
      << "</ha_dbhRange>"
      << "<ha_dbhRange>"
      << "<ha_low>50.0</ha_low>"
      << "<ha_high>80.0</ha_high>"
      << "<ha_amountToCut>40.0</ha_amountToCut>"
      << "</ha_dbhRange>"
      << "<ha_dbhRange>"
      << "<ha_low>80.0</ha_low>"
      << "<ha_high>85.0</ha_high>"
      << "<ha_amountToCut>30.0</ha_amountToCut>"
      << "</ha_dbhRange>"
      << "<ha_dbhRange>"
      << "<ha_low>90.0</ha_low>"
      << "<ha_high>99.0</ha_high>"
      << "<ha_amountToCut>20.0</ha_amountToCut>"
      << "</ha_dbhRange>";
  for (int i = 0; i < 25; i++) {
    for (int j = 0; j < 25; j++) {
      oOut << "<ha_applyToCell x=\"" << i << "\" y=\"" << j << "\" /> ";
    }
  }
  oOut << "</ha_cutEvent>"
      << "</Harvest1>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteHarvestXMLFile3()
/////////////////////////////////////////////////////////////////////////////
const char* WriteHarvestXMLFile3()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteHarvestFileBeginning(oOut, 1);

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>Harvest</behaviorName>"
      << "<listPosition>1</listPosition>"
      << "<version>1</version>"
      << "</behavior>"
      << "</behaviorList>"
      << "<Harvest1>"
      << "<ha_cutEvent>"
      << "<ha_applyToSpecies species=\"Trembling_Aspen\" />"
      << "<ha_applyToSpecies species=\"Black_Cottonwood\" />"
      << "<ha_timestep>1</ha_timestep>"
      << "<ha_cutType>partial</ha_cutType>"
      << "<ha_cutAmountType>absolute density</ha_cutAmountType>"
      << "<ha_dbhRange>"
      << "<ha_low>15.0</ha_low>"
      << "<ha_high>45.0</ha_high>"
      << "<ha_amountToCut>1</ha_amountToCut>"
      << "</ha_dbhRange>"
      << "<ha_dbhRange>"
      << "<ha_low>50.0</ha_low>"
      << "<ha_high>80.0</ha_high>"
      << "<ha_amountToCut>1</ha_amountToCut>"
      << "</ha_dbhRange>"
      << "<ha_dbhRange>"
      << "<ha_low>80.0</ha_low>"
      << "<ha_high>85.0</ha_high>"
      << "<ha_amountToCut>1</ha_amountToCut>"
      << "</ha_dbhRange>"
      << "<ha_dbhRange>"
      << "<ha_low>90.0</ha_low>"
      << "<ha_high>99.0</ha_high>"
      << "<ha_amountToCut>1</ha_amountToCut>"
      << "</ha_dbhRange>";
  for (int i = 0; i < 25; i++) {
    for (int j = 0; j < 25; j++) {
      oOut << "<ha_applyToCell x=\"" << i << "\" y=\"" << j << "\" /> ";
    }
  }
  oOut << "</ha_cutEvent>"
      << "</Harvest1>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteHarvestXMLFile4()
/////////////////////////////////////////////////////////////////////////////
const char* WriteHarvestXMLFile4()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";
  int i;

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteHarvestFileBeginning(oOut, 1);

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>Harvest</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "</behavior>"
      << "</behaviorList>"
      << "<Harvest1>"
      << "<ha_cutEvent>"
      << "<ha_applyToSpecies species=\"Western_Redcedar\" />"
      << "<ha_applyToSpecies species=\"Amabilis_Fir\" />"
      << "<ha_applyToSpecies species=\"Western_Hemlock\" />"
      << "<ha_timestep>2</ha_timestep>"
      << "<ha_cutType>gap</ha_cutType>"
      << "<ha_cutAmountType>percent of density</ha_cutAmountType>"
      << "<ha_dbhRange>"
      << "<ha_low>0.0</ha_low>"
      << "<ha_high>3000.0</ha_high>"
      << "<ha_amountToCut>100.0</ha_amountToCut>"
      << "</ha_dbhRange>"
      << "<ha_percentSeedlingsDie>"
      << "<ha_psdVal species=\"Western_Hemlock\">50</ha_psdVal>"
      << "<ha_psdVal species=\"Western_Redcedar\">50</ha_psdVal>"
      << "<ha_psdVal species=\"Amabilis_Fir\">50</ha_psdVal>"
      << "<ha_psdVal species=\"Subalpine_Fir\">50</ha_psdVal>"
      << "<ha_psdVal species=\"Hybrid_Spruce\">50</ha_psdVal>"
      << "<ha_psdVal species=\"Lodgepole_Pine\">50</ha_psdVal>"
      << "<ha_psdVal species=\"Lodgepole_Pine\">0</ha_psdVal>"
      << "<ha_psdVal species=\"Trembling_Aspen\">0</ha_psdVal>"
      << "<ha_psdVal species=\"Black_Cottonwood\">0</ha_psdVal>"
      << "<ha_psdVal species=\"Paper_Birch\">0</ha_psdVal>"
      << "</ha_percentSeedlingsDie>";
  for (int i = 0; i < 25; i++) {
    for (int j = 0; j < 25; j++) {
      oOut << "<ha_applyToCell x=\"" << i << "\" y=\"" << j << "\" /> ";
    }
  }
  oOut << "</ha_cutEvent>"
      << "<ha_cutEvent>"
      << "<ha_applyToSpecies species=\"Lodgepole_Pine\" />"
      << "<ha_applyToSpecies species=\"Hybrid_Spruce\" />"
      << "<ha_timestep>2</ha_timestep>"
      << "<ha_cutType>partial</ha_cutType>"
      << "<ha_cutAmountType>percent of basal area</ha_cutAmountType>"
      << "<ha_dbhRange>"
      << "<ha_low>15.0</ha_low>"
      << "<ha_high>45.0</ha_high>"
      << "<ha_amountToCut>50</ha_amountToCut>"
      << "</ha_dbhRange>"
      << "<ha_dbhRange>"
      << "<ha_low>50.0</ha_low>"
      << "<ha_high>80.0</ha_high>"
      << "<ha_amountToCut>100</ha_amountToCut>"
      << "</ha_dbhRange>"
      << "<ha_dbhRange>"
      << "<ha_low>80.0</ha_low>"
      << "<ha_high>85.0</ha_high>"
      << "<ha_amountToCut>30</ha_amountToCut>"
      << "</ha_dbhRange>"
      << "<ha_dbhRange>"
      << "<ha_low>90.0</ha_low>"
      << "<ha_high>100.0</ha_high>"
      << "<ha_amountToCut>0</ha_amountToCut>"
      << "</ha_dbhRange>"
      << "<ha_percentSeedlingsDie>"
      << "<ha_psdVal species=\"Western_Hemlock\">0</ha_psdVal>"
      << "<ha_psdVal species=\"Western_Redcedar\">0</ha_psdVal>"
      << "<ha_psdVal species=\"Amabilis_Fir\">0</ha_psdVal>"
      << "<ha_psdVal species=\"Subalpine_Fir\">0</ha_psdVal>"
      << "<ha_psdVal species=\"Hybrid_Spruce\">0</ha_psdVal>"
      << "<ha_psdVal species=\"Lodgepole_Pine\">0</ha_psdVal>"
      << "<ha_psdVal species=\"Trembling_Aspen\">0</ha_psdVal>"
      << "<ha_psdVal species=\"Black_Cottonwood\">0</ha_psdVal>"
      << "<ha_psdVal species=\"Paper_Birch\">0</ha_psdVal>"
      << "</ha_percentSeedlingsDie>";
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 10; j++) {
      oOut << "<ha_applyToCell x=\"" << i << "\" y=\"" << j << "\" /> ";
    }
  }
  oOut << "</ha_cutEvent>"
      << "<ha_cutEvent>"
      << "<ha_applyToSpecies species=\"Black_Cottonwood\" />"
      << "<ha_timestep>3</ha_timestep>"
      << "<ha_cutType>partial</ha_cutType>"
      << "<ha_cutAmountType>percent of density</ha_cutAmountType>"
      << "<ha_dbhRange>"
      << "<ha_low>0.0</ha_low>"
      << "<ha_high>10.0</ha_high>"
      << "<ha_amountToCut>50</ha_amountToCut>"
      << "</ha_dbhRange>"
      << "<ha_dbhRange>"
      << "<ha_low>10.0</ha_low>"
      << "<ha_high>20.0</ha_high>"
      << "<ha_amountToCut>100</ha_amountToCut>"
      << "</ha_dbhRange>"
      << "<ha_dbhRange>"
      << "<ha_low>20.0</ha_low>"
      << "<ha_high>30.0</ha_high>"
      << "<ha_amountToCut>30</ha_amountToCut>"
      << "</ha_dbhRange>"
      << "<ha_dbhRange>"
      << "<ha_low>30.0</ha_low>"
      << "<ha_high>40.0</ha_high>"
      << "<ha_amountToCut>0</ha_amountToCut>"
      << "</ha_dbhRange>"
      << "<ha_percentSeedlingsDie>"
      << "<ha_psdVal species=\"Amabilis_Fir\">0</ha_psdVal>"
      << "<ha_psdVal species=\"Hybrid_Spruce\">0</ha_psdVal>"
      << "<ha_psdVal species=\"Western_Hemlock\">0</ha_psdVal>"
      << "<ha_psdVal species=\"Western_Redcedar\">0</ha_psdVal>"
      << "<ha_psdVal species=\"Subalpine_Fir\">0</ha_psdVal>"
      << "<ha_psdVal species=\"Lodgepole_Pine\">0</ha_psdVal>"
      << "<ha_psdVal species=\"Black_Cottonwood\">0</ha_psdVal>"
      << "<ha_psdVal species=\"Paper_Birch\">0</ha_psdVal>"
      << "<ha_psdVal species=\"Trembling_Aspen\">25</ha_psdVal>"
      << "</ha_percentSeedlingsDie>";
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 10; j++) {
      oOut << "<ha_applyToCell x=\"" << i << "\" y=\"" << j << "\" /> ";
    }
  }
  oOut << "</ha_cutEvent>"
      << "<ha_cutEvent>"
      << "<ha_applyToSpecies species=\"Hybrid_Spruce\" />"
      << "<ha_timestep>3</ha_timestep>"
      << "<ha_cutType>partial</ha_cutType>"
      << "<ha_cutAmountType>absolute basal area</ha_cutAmountType>"
      << "<ha_dbhRange>"
      << "<ha_low>200.0</ha_low>"
      << "<ha_high>300.0</ha_high>"
      << "<ha_amountToCut>50</ha_amountToCut>"
      << "</ha_dbhRange>"
      << "<ha_dbhRange>"
      << "<ha_low>50.0</ha_low>"
      << "<ha_high>80.0</ha_high>"
      << "<ha_amountToCut>100</ha_amountToCut>"
      << "</ha_dbhRange>"
      << "<ha_dbhRange>"
      << "<ha_low>80.0</ha_low>"
      << "<ha_high>85.0</ha_high>"
      << "<ha_amountToCut>30</ha_amountToCut>"
      << "</ha_dbhRange>"
      << "<ha_dbhRange>"
      << "<ha_low>90.0</ha_low>"
      << "<ha_high>100.0</ha_high>"
      << "<ha_amountToCut>0</ha_amountToCut>"
      << "</ha_dbhRange>";
  i = 6;
  for (int j = 6; j < 25; j++) {
    oOut << "<ha_applyToCell x=\"" << i << "\" y=\"" << j << "\" /> ";
  }
  i = 8;
  for (int j = 6; j < 25; j++) {
    oOut << "<ha_applyToCell x=\"" << i << "\" y=\"" << j << "\" /> ";
  }
  oOut << "</ha_cutEvent>"
      << "</Harvest1>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteHarvestXMLFile5()
/////////////////////////////////////////////////////////////////////////////
const char* WriteHarvestXMLFile5()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";
  int i, j;

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteHarvestFileBeginning(oOut, 1);

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>Harvest</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "</behavior>"
      << "</behaviorList>"
      << "<Harvest1>"
      << "<ha_cutEvent>"
      << "<ha_applyToSpecies species=\"Western_Hemlock\" />"
      << "<ha_applyToSpecies species=\"Western_Redcedar\" />"
      << "<ha_applyToSpecies species=\"Amabilis_Fir\" />"
      << "<ha_applyToSpecies species=\"Black_Cottonwood\" />"
      << "<ha_applyToSpecies species=\"Subalpine_Fir\" />"
      << "<ha_applyToSpecies species=\"Lodgepole_Pine\" />"
      << "<ha_applyToSpecies species=\"Hybrid_Spruce\" />"
      << "<ha_applyToSpecies species=\"Trembling_Aspen\" />"
      << "<ha_applyToSpecies species=\"Paper_Birch\" />"
      << "<ha_timestep>1</ha_timestep>"
      << "<ha_cutType>partial</ha_cutType>"
      << "<ha_cutAmountType>absolute density</ha_cutAmountType>"
      << "<ha_dbhRange>"
      << "<ha_low>0.0</ha_low>"
      << "<ha_high>10.0</ha_high>"
      << "<ha_amountToCut>5.0</ha_amountToCut>"
      << "</ha_dbhRange>"
      << "<ha_dbhRange>"
      << "<ha_low>10.0</ha_low>"
      << "<ha_high>20.0</ha_high>"
      << "<ha_amountToCut>100.0</ha_amountToCut>"
      << "</ha_dbhRange>"
      << "<ha_dbhRange>"
      << "<ha_low>20.0</ha_low>"
      << "<ha_high>30.0</ha_high>"
      << "<ha_amountToCut>3.0</ha_amountToCut>"
      << "</ha_dbhRange>"
      << "<ha_dbhRange>"
      << "<ha_low>30.0</ha_low>"
      << "<ha_high>40.0</ha_high>"
      << "<ha_amountToCut>0</ha_amountToCut>"
      << "</ha_dbhRange>"
      << "<ha_percentSeedlingsDie>"
      << "<ha_psdVal species=\"Western_Hemlock\">100</ha_psdVal>"
      << "<ha_psdVal species=\"Western_Redcedar\">100</ha_psdVal>"
      << "<ha_psdVal species=\"Amabilis_Fir\">100</ha_psdVal>"
      << "<ha_psdVal species=\"Subalpine_Fir\">100</ha_psdVal>"
      << "<ha_psdVal species=\"Hybrid_Spruce\">100</ha_psdVal>"
      << "<ha_psdVal species=\"Lodgepole_Pine\">100</ha_psdVal>"
      << "<ha_psdVal species=\"Trembling_Aspen\">100</ha_psdVal>"
      << "<ha_psdVal species=\"Black_Cottonwood\">100</ha_psdVal>"
      << "<ha_psdVal species=\"Paper_Birch\">100</ha_psdVal>"
      << "</ha_percentSeedlingsDie>";
  i = 6;
  for (int j = 6; j < 25; j++) {
    oOut << "<ha_applyToCell x=\"" << i << "\" y=\"" << j << "\" /> ";
  }
  for (i = 8; i < 25; i++) {
    for (j = 0; j < 13; j++) {
      oOut << "<ha_applyToCell x=\"" << i << "\" y=\"" << j << "\" /> ";
    }
  }
  oOut << "</ha_cutEvent>"
      << "</Harvest1>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteHarvestXMLFile6()
/////////////////////////////////////////////////////////////////////////////
const char* WriteHarvestXMLFile6()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";
  int i;

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteHarvestFileBeginning(oOut, 1);

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>Harvest</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "</behavior>"
      << "</behaviorList>"
      << "<Harvest1>"
      << "<ha_cutEvent>"
      << "<ha_applyToSpecies species=\"Subalpine_Fir\" />"
      << "<ha_timestep>1</ha_timestep>"
      << "<ha_cutType>clear</ha_cutType>"
      << "<ha_cutAmountType>percent of density</ha_cutAmountType>"
      << "<ha_dbhRange>"
      << "<ha_low>0.0</ha_low>"
      << "<ha_high>3000.0</ha_high>"
      << "<ha_amountToCut>100.0</ha_amountToCut>"
      << "</ha_dbhRange>";
  i = 6;
  for (int j = 6; j < 25; j++) {
    oOut << "<ha_applyToCell x=\"" << i << "\" y=\"" << j << "\" /> ";
  }
  i = 8;
  for (int j = 6; j < 25; j++) {
    oOut << "<ha_applyToCell x=\"" << i << "\" y=\"" << j << "\" /> ";
  }
  oOut << "</ha_cutEvent>"
      << "<ha_cutEvent>"
      << "<ha_applyToSpecies species=\"Western_Hemlock\" />"
      << "<ha_timestep>2</ha_timestep>"
      << "<ha_cutType>gap</ha_cutType>"
      << "<ha_cutAmountType>percent of density</ha_cutAmountType>"
      << "<ha_dbhRange>"
      << "<ha_low>0.0</ha_low>"
      << "<ha_high>30.0</ha_high>"
      << "<ha_amountToCut>100</ha_amountToCut>"
      << "</ha_dbhRange>";
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 10; j++) {
      oOut << "<ha_applyToCell x=\"" << i << "\" y=\"" << j << "\" /> ";
    }
  }
  oOut << "</ha_cutEvent>"
      << "<ha_cutEvent>"
      << "<ha_applyToSpecies species=\"Western_Hemlock\" />"
      << "<ha_timestep>2</ha_timestep>"
      << "<ha_cutType>gap</ha_cutType>"
      << "<ha_cutAmountType>percent of density</ha_cutAmountType>"
      << "<ha_dbhRange>"
      << "<ha_low>0.0</ha_low>"
      << "<ha_high>3000.0</ha_high>"
      << "<ha_amountToCut>100</ha_amountToCut>"
      << "</ha_dbhRange>";
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 10; j++) {
      oOut << "<ha_applyToCell x=\"" << i << "\" y=\"" << j << "\" /> ";
    }
  }
  oOut << "</ha_cutEvent>"
      << "<ha_cutEvent>"
      << "<ha_applyToSpecies species=\"Western_Redcedar\" />"
      << "<ha_timestep>3</ha_timestep>"
      << "<ha_cutType>partial</ha_cutType>"
      << "<ha_cutAmountType>percent of basal area</ha_cutAmountType>"
      << "<ha_dbhRange>"
      << "<ha_low>0.0</ha_low>"
      << "<ha_high>300.0</ha_high>"
      << "<ha_amountToCut>50</ha_amountToCut>"
      << "</ha_dbhRange>";
  oOut << "<ha_applyToCell x=\"" << 0 << "\" y=\"" << 10 << "\" /> ";
  oOut << "</ha_cutEvent>"
      << "<ha_cutEvent>"
      << "<ha_applyToSpecies species=\"Amabilis_Fir\" />"
      << "<ha_timestep>3</ha_timestep>"
      << "<ha_cutType>partial</ha_cutType>"
      << "<ha_cutAmountType>absolute basal area</ha_cutAmountType>"
      << "<ha_dbhRange>"
      << "<ha_low>0.0</ha_low>"
      << "<ha_high>300.0</ha_high>"
      << "<ha_amountToCut>4.5</ha_amountToCut>"
      << "</ha_dbhRange>";
  oOut << "<ha_applyToCell x=\"" << 5 << "\" y=\"" << 5 << "\" /> ";
  /*  oOut << "</ha_cutEvent>"
       << "<ha_cutEvent>"
       << "<ha_applyToSpecies species=\"Hybrid_Spruce\" />"
       << "<ha_timestep>3</ha_timestep>"
       << "<ha_cutType>partial</ha_cutType>"
       << "<ha_cutAmountType>percent of density</ha_cutAmountType>"
       << "<ha_dbhRange>"
       << "<ha_low>0.0</ha_low>"
       << "<ha_high>300.0</ha_high>"
       << "<ha_amountToCut>50</ha_amountToCut>"
       << "</ha_dbhRange>"; */
  oOut << "<ha_applyToCell x=\"" << 10 << "\" y=\"" << 23 << "\" /> ";
  oOut << "</ha_cutEvent>"
      << "<ha_cutEvent>"
      << "<ha_applyToSpecies species=\"Lodgepole_Pine\" />"
      << "<ha_timestep>3</ha_timestep>"
      << "<ha_cutType>partial</ha_cutType>"
      << "<ha_cutAmountType>absolute density</ha_cutAmountType>"
      << "<ha_dbhRange>"
      << "<ha_low>0.0</ha_low>"
      << "<ha_high>300.0</ha_high>"
      << "<ha_amountToCut>312.5</ha_amountToCut>"
      << "</ha_dbhRange>";
  oOut << "<ha_applyToCell x=\"" << 1 << "\" y=\"" << 1 << "\" /> ";
  oOut << "</ha_cutEvent>"
      << "<ha_cutEvent>"
      << "<ha_applyToSpecies species=\"Trembling_Aspen\" />"
      << "<ha_timestep>3</ha_timestep>"
      << "<ha_cutType>clear</ha_cutType>"
      << "<ha_cutAmountType>percent of density</ha_cutAmountType>"
      << "<ha_dbhRange>"
      << "<ha_low>0.0</ha_low>"
      << "<ha_high>3000.0</ha_high>"
      << "<ha_amountToCut>100</ha_amountToCut>"
      << "</ha_dbhRange>";
  oOut << "<ha_applyToCell x=\"" << 20 << "\" y=\"" << 0 << "\" /> ";
  oOut << "</ha_cutEvent>"
      << "<ha_cutEvent>"
      << "<ha_applyToSpecies species=\"Black_Cottonwood\" />"
      << "<ha_timestep>3</ha_timestep>"
      << "<ha_cutType>gap</ha_cutType>"
      << "<ha_cutAmountType>percent of density</ha_cutAmountType>"
      << "<ha_dbhRange>"
      << "<ha_low>0.0</ha_low>"
      << "<ha_high>3000.0</ha_high>"
      << "<ha_amountToCut>100</ha_amountToCut>"
      << "</ha_dbhRange>";
  oOut << "<ha_applyToCell x=\"" << 1 << "\" y=\"" << 7 << "\" /> ";
  oOut << "</ha_cutEvent>"
      << "</Harvest1>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}


/////////////////////////////////////////////////////////////////////////////
// WriteHarvestXMLFile8()
/////////////////////////////////////////////////////////////////////////////
const char* WriteHarvestXMLFile8()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteHarvestFileBeginning(oOut, 1);

  oOut << "<grid gridName=\"harvestmastercuts\">"
      << "<ma_lengthXCells>2</ma_lengthXCells>"
      << "<ma_lengthYCells>2</ma_lengthYCells>"
      << "</grid>"
      << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>Harvest</behaviorName>"
      << "<version>2</version>"
      << "<listPosition>1</listPosition>"
      << "</behavior>"
      << "</behaviorList>"
      << "<Harvest1>"
      << "<ha_cutEvent>"
      << "<ha_applyToSpecies species=\"Amabilis_Fir\" />"
      << "<ha_applyToSpecies species=\"Paper_Birch\" />"
      << "<ha_applyToSpecies species=\"Western_Hemlock\" />"
      << "<ha_applyToSpecies species=\"Western_Redcedar\" />"
      << "<ha_applyToSpecies species=\"Subalpine_Fir\" />"
      << "<ha_applyToSpecies species=\"Hybrid_Spruce\" />"
      << "<ha_applyToSpecies species=\"Lodgepole_Pine\" />"
      << "<ha_applyToSpecies species=\"Trembling_Aspen\" />"
      << "<ha_applyToSpecies species=\"Black_Cottonwood\" />"
      << "<ha_timestep>1</ha_timestep>"
      << "<ha_cutType>clear</ha_cutType>"
      << "<ha_cutAmountType>percent of density</ha_cutAmountType>"
      << "<ha_dbhRange>"
      << "<ha_low>0.0</ha_low>"
      << "<ha_high>3000.0</ha_high>"
      << "<ha_amountToCut>100.0</ha_amountToCut>"
      << "</ha_dbhRange>"
      << "<ha_percentSeedlingsDie>"
      << "<ha_psdVal species=\"Western_Hemlock\">100</ha_psdVal>"
      << "<ha_psdVal species=\"Western_Redcedar\">100</ha_psdVal>"
      << "<ha_psdVal species=\"Amabilis_Fir\">100</ha_psdVal>"
      << "<ha_psdVal species=\"Subalpine_Fir\">100</ha_psdVal>"
      << "<ha_psdVal species=\"Hybrid_Spruce\">100</ha_psdVal>"
      << "<ha_psdVal species=\"Lodgepole_Pine\">100</ha_psdVal>"
      << "<ha_psdVal species=\"Trembling_Aspen\">100</ha_psdVal>"
      << "<ha_psdVal species=\"Black_Cottonwood\">100</ha_psdVal>"
      << "<ha_psdVal species=\"Paper_Birch\">100</ha_psdVal>"
      << "</ha_percentSeedlingsDie>";
  for (int i = 0; i < 22; i++) {
    for (int j = 0; j < 37; j++) {
      oOut << "<ha_applyToCell x=\"" << i << "\" y=\"" << j << "\" /> ";
    }
  }
  oOut << "</ha_cutEvent>"
      << "</Harvest1>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteHarvestXMLFile9()
/////////////////////////////////////////////////////////////////////////////
const char* WriteHarvestXMLFile9()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">"
      << "<plot>"
      << "<timesteps>3</timesteps>"
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
      << "<tr_species speciesName=\"Western_Hemlock\"/>"
      << "<tr_species speciesName=\"Western_Redcedar\"/>"
      << "<tr_species speciesName=\"Amabilis_Fir\"/>"
      << "<tr_species speciesName=\"Subalpine_Fir\"/>"
      << "<tr_species speciesName=\"Hybrid_Spruce\"/>"
      << "<tr_species speciesName=\"Lodgepole_Pine\"/>"
      << "<tr_species speciesName=\"Trembling_Aspen\"/>"
      << "<tr_species speciesName=\"Black_Cottonwood\"/>"
      << "<tr_species speciesName=\"Paper_Birch\"/>"
      << "</tr_speciesList>"
      << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
      << "<tr_minAdultDBH>"
      << "<tr_madVal species=\"Western_Hemlock\">10</tr_madVal>"
      << "<tr_madVal species=\"Western_Redcedar\">10</tr_madVal>"
      << "<tr_madVal species=\"Amabilis_Fir\">10</tr_madVal>"
      << "<tr_madVal species=\"Subalpine_Fir\">10</tr_madVal>"
      << "<tr_madVal species=\"Hybrid_Spruce\">10</tr_madVal>"
      << "<tr_madVal species=\"Lodgepole_Pine\">10</tr_madVal>"
      << "<tr_madVal species=\"Trembling_Aspen\">10</tr_madVal>"
      << "<tr_madVal species=\"Black_Cottonwood\">10</tr_madVal>"
      << "<tr_madVal species=\"Paper_Birch\">10</tr_madVal>"
      << "</tr_minAdultDBH>"
      << "<tr_maxSeedlingHeight>"
      << "<tr_mshVal species=\"Western_Hemlock\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Western_Redcedar\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Amabilis_Fir\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Subalpine_Fir\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Hybrid_Spruce\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Lodgepole_Pine\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Trembling_Aspen\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Black_Cottonwood\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Paper_Birch\">1.35</tr_mshVal>"
      << "</tr_maxSeedlingHeight>";

  oOut << "<tr_treemapFile>" << WriteHarvestRun9TreeMap() << "</tr_treemapFile>";

  oOut << "</trees>"
      << "<allometry>"
      << "<tr_canopyHeight>"
      << "<tr_chVal species=\"Western_Hemlock\">39.48</tr_chVal>"
      << "<tr_chVal species=\"Western_Redcedar\">39.54</tr_chVal>"
      << "<tr_chVal species=\"Amabilis_Fir\">40</tr_chVal>"
      << "<tr_chVal species=\"Subalpine_Fir\">40</tr_chVal>"
      << "<tr_chVal species=\"Hybrid_Spruce\">45</tr_chVal>"
      << "<tr_chVal species=\"Lodgepole_Pine\">40</tr_chVal>"
      << "<tr_chVal species=\"Trembling_Aspen\">39.14</tr_chVal>"
      << "<tr_chVal species=\"Black_Cottonwood\">39.47</tr_chVal>"
      << "<tr_chVal species=\"Paper_Birch\">33.18</tr_chVal>"
      << "</tr_canopyHeight>"
      << "<tr_stdAsympCrownRad>"
      << "<tr_sacrVal species=\"Western_Hemlock\">0.0549</tr_sacrVal>"
      << "<tr_sacrVal species=\"Western_Redcedar\">0.0614</tr_sacrVal>"
      << "<tr_sacrVal species=\"Amabilis_Fir\">0.0242</tr_sacrVal>"
      << "<tr_sacrVal species=\"Subalpine_Fir\">0.0251</tr_sacrVal>"
      << "<tr_sacrVal species=\"Hybrid_Spruce\">0.0239</tr_sacrVal>"
      << "<tr_sacrVal species=\"Lodgepole_Pine\">0.0303</tr_sacrVal>"
      << "<tr_sacrVal species=\"Trembling_Aspen\">0.0328</tr_sacrVal>"
      << "<tr_sacrVal species=\"Black_Cottonwood\">0.0247</tr_sacrVal>"
      << "<tr_sacrVal species=\"Paper_Birch\">0.0484</tr_sacrVal>"
      << "</tr_stdAsympCrownRad>"
      << "<tr_stdCrownRadExp>"
      << "<tr_screVal species=\"Western_Hemlock\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Western_Redcedar\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Amabilis_Fir\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Subalpine_Fir\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Hybrid_Spruce\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Lodgepole_Pine\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Trembling_Aspen\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Black_Cottonwood\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Paper_Birch\">1.0</tr_screVal>"
      << "</tr_stdCrownRadExp>"
      << "<tr_conversionDiam10ToDBH>"
      << "<tr_cdtdVal species=\"Western_Hemlock\">0.8008</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Western_Redcedar\">0.5944</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Amabilis_Fir\">0.7059</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Subalpine_Fir\">0.7776</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Hybrid_Spruce\">0.6933</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Lodgepole_Pine\">0.8014</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Trembling_Aspen\">0.7992</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Black_Cottonwood\">0.7926</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Paper_Birch\">0.7803</tr_cdtdVal>"
      << "</tr_conversionDiam10ToDBH>"
      << "<tr_interceptDiam10ToDBH>"
      << "<tr_idtdVal species=\"Western_Hemlock\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Western_Redcedar\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Amabilis_Fir\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Subalpine_Fir\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Hybrid_Spruce\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Lodgepole_Pine\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Trembling_Aspen\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Black_Cottonwood\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Paper_Birch\">0</tr_idtdVal>"
      << "</tr_interceptDiam10ToDBH>"
      << "<tr_stdAsympCrownHt>"
      << "<tr_sachVal species=\"Western_Hemlock\">0.389</tr_sachVal>"
      << "<tr_sachVal species=\"Western_Redcedar\">0.368</tr_sachVal>"
      << "<tr_sachVal species=\"Amabilis_Fir\">0.464</tr_sachVal>"
      << "<tr_sachVal species=\"Subalpine_Fir\">0.454</tr_sachVal>"
      << "<tr_sachVal species=\"Hybrid_Spruce\">0.405</tr_sachVal>"
      << "<tr_sachVal species=\"Lodgepole_Pine\">0.201</tr_sachVal>"
      << "<tr_sachVal species=\"Trembling_Aspen\">0.301</tr_sachVal>"
      << "<tr_sachVal species=\"Black_Cottonwood\">0.42</tr_sachVal>"
      << "<tr_sachVal species=\"Paper_Birch\">0.315</tr_sachVal>"
      << "</tr_stdAsympCrownHt>"
      << "<tr_stdCrownHtExp>"
      << "<tr_scheVal species=\"Western_Hemlock\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Western_Redcedar\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Amabilis_Fir\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Subalpine_Fir\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Hybrid_Spruce\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Lodgepole_Pine\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Trembling_Aspen\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Black_Cottonwood\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Paper_Birch\">1.0</tr_scheVal>"
      << "</tr_stdCrownHtExp>"
      << "<tr_slopeOfHeight-Diam10>"
      << "<tr_sohdVal species=\"Western_Hemlock\">0.03418</tr_sohdVal>"
      << "<tr_sohdVal species=\"Western_Redcedar\">0.0269</tr_sohdVal>"
      << "<tr_sohdVal species=\"Amabilis_Fir\">0.02871</tr_sohdVal>"
      << "<tr_sohdVal species=\"Subalpine_Fir\">0.02815</tr_sohdVal>"
      << "<tr_sohdVal species=\"Hybrid_Spruce\">0.02871</tr_sohdVal>"
      << "<tr_sohdVal species=\"Lodgepole_Pine\">0.03224</tr_sohdVal>"
      << "<tr_sohdVal species=\"Trembling_Aspen\">0.04796</tr_sohdVal>"
      << "<tr_sohdVal species=\"Black_Cottonwood\">0.04681</tr_sohdVal>"
      << "<tr_sohdVal species=\"Paper_Birch\">0.04101</tr_sohdVal>"
      << "</tr_slopeOfHeight-Diam10>"
      << "<tr_slopeOfAsymHeight>"
      << "<tr_soahVal species=\"Western_Hemlock\">0.0299</tr_soahVal>"
      << "<tr_soahVal species=\"Western_Redcedar\">0.0241</tr_soahVal>"
      << "<tr_soahVal species=\"Amabilis_Fir\">0.0263</tr_soahVal>"
      << "<tr_soahVal species=\"Subalpine_Fir\">0.0264</tr_soahVal>"
      << "<tr_soahVal species=\"Hybrid_Spruce\">0.0264</tr_soahVal>"
      << "<tr_soahVal species=\"Lodgepole_Pine\">0.0333</tr_soahVal>"
      << "<tr_soahVal species=\"Trembling_Aspen\">0.0352</tr_soahVal>"
      << "<tr_soahVal species=\"Black_Cottonwood\">0.0347</tr_soahVal>"
      << "<tr_soahVal species=\"Paper_Birch\">0.0454</tr_soahVal>"
      << "</tr_slopeOfAsymHeight>"
      << "<tr_whatSeedlingHeightDiam>"
      << "<tr_wsehdVal species=\"Western_Hemlock\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Western_Redcedar\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Amabilis_Fir\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Subalpine_Fir\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Hybrid_Spruce\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Lodgepole_Pine\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Trembling_Aspen\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Black_Cottonwood\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Paper_Birch\">0</tr_wsehdVal>"
      << "</tr_whatSeedlingHeightDiam>"
      << "<tr_whatSaplingHeightDiam>"
      << "<tr_wsahdVal species=\"Western_Hemlock\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Western_Redcedar\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Amabilis_Fir\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Subalpine_Fir\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Hybrid_Spruce\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Lodgepole_Pine\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Trembling_Aspen\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Black_Cottonwood\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Paper_Birch\">0</tr_wsahdVal>"
      << "</tr_whatSaplingHeightDiam>"
      << "<tr_whatAdultHeightDiam>"
      << "<tr_wahdVal species=\"Western_Hemlock\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Western_Redcedar\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Amabilis_Fir\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Subalpine_Fir\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Hybrid_Spruce\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Lodgepole_Pine\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Trembling_Aspen\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Black_Cottonwood\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Paper_Birch\">0</tr_wahdVal>"
      << "</tr_whatAdultHeightDiam>"
      << "<tr_whatAdultCrownRadDiam>"
      << "<tr_wacrdVal species=\"Western_Hemlock\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Western_Redcedar\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Amabilis_Fir\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Subalpine_Fir\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Hybrid_Spruce\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Lodgepole_Pine\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Trembling_Aspen\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Black_Cottonwood\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Paper_Birch\">0</tr_wacrdVal>"
      << "</tr_whatAdultCrownRadDiam>"
      << "<tr_whatAdultCrownHeightHeight>"
      << "<tr_wachhVal species=\"Western_Hemlock\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Western_Redcedar\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Amabilis_Fir\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Subalpine_Fir\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Hybrid_Spruce\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Lodgepole_Pine\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Trembling_Aspen\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Black_Cottonwood\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Paper_Birch\">0</tr_wachhVal>"
      << "</tr_whatAdultCrownHeightHeight>"
      << "<tr_whatSaplingCrownRadDiam>"
      << "<tr_wscrdVal species=\"Western_Hemlock\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Western_Redcedar\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Amabilis_Fir\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Subalpine_Fir\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Hybrid_Spruce\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Lodgepole_Pine\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Trembling_Aspen\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Black_Cottonwood\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Paper_Birch\">0</tr_wscrdVal>"
      << "</tr_whatSaplingCrownRadDiam>"
      << "<tr_whatSaplingCrownHeightHeight>"
      << "<tr_wschhVal species=\"Western_Hemlock\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Western_Redcedar\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Amabilis_Fir\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Subalpine_Fir\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Hybrid_Spruce\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Lodgepole_Pine\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Trembling_Aspen\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Black_Cottonwood\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Paper_Birch\">0</tr_wschhVal>"
      << "</tr_whatSaplingCrownHeightHeight>"
      << "</allometry>";

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>Harvest</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>QualityVigorClassifier</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Western_Hemlock\" type=\"Adult\"/>"
      << "<applyTo species=\"Western_Redcedar\" type=\"Adult\"/>"
      << "<applyTo species=\"Amabilis_Fir\" type=\"Adult\"/>"
      << "<applyTo species=\"Subalpine_Fir\" type=\"Adult\"/>"
      << "<applyTo species=\"Hybrid_Spruce\" type=\"Adult\"/>"
      << "<applyTo species=\"Lodgepole_Pine\" type=\"Adult\"/>"
      << "<applyTo species=\"Trembling_Aspen\" type=\"Adult\"/>"
      << "<applyTo species=\"Black_Cottonwood\" type=\"Adult\"/>"
      << "<applyTo species=\"Paper_Birch\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>ConstRadialGrowth</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>3</listPosition>"
      << "<applyTo species=\"Western_Hemlock\" type=\"Adult\"/>"
      << "<applyTo species=\"Western_Redcedar\" type=\"Adult\"/>"
      << "<applyTo species=\"Amabilis_Fir\" type=\"Adult\"/>"
      << "<applyTo species=\"Subalpine_Fir\" type=\"Adult\"/>"
      << "<applyTo species=\"Hybrid_Spruce\" type=\"Adult\"/>"
      << "<applyTo species=\"Lodgepole_Pine\" type=\"Adult\"/>"
      << "<applyTo species=\"Trembling_Aspen\" type=\"Adult\"/>"
      << "<applyTo species=\"Black_Cottonwood\" type=\"Adult\"/>"
      << "<applyTo species=\"Paper_Birch\" type=\"Adult\"/>"
      << "<applyTo species=\"Western_Hemlock\" type=\"Sapling\"/>"
      << "<applyTo species=\"Western_Redcedar\" type=\"Sapling\"/>"
      << "<applyTo species=\"Amabilis_Fir\" type=\"Sapling\"/>"
      << "<applyTo species=\"Subalpine_Fir\" type=\"Sapling\"/>"
      << "<applyTo species=\"Hybrid_Spruce\" type=\"Sapling\"/>"
      << "<applyTo species=\"Lodgepole_Pine\" type=\"Sapling\"/>"
      << "<applyTo species=\"Trembling_Aspen\" type=\"Sapling\"/>"
      << "<applyTo species=\"Black_Cottonwood\" type=\"Sapling\"/>"
      << "<applyTo species=\"Paper_Birch\" type=\"Sapling\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>InsectInfestation</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>4</listPosition>"
      << "<applyTo species=\"Subalpine_Fir\" type=\"Adult\"/>"
      << "<applyTo species=\"Hybrid_Spruce\" type=\"Adult\"/>"
      << "<applyTo species=\"Lodgepole_Pine\" type=\"Adult\"/>"
      << "<applyTo species=\"Trembling_Aspen\" type=\"Adult\"/>"
      << "<applyTo species=\"Black_Cottonwood\" type=\"Adult\"/>"
      << "<applyTo species=\"Paper_Birch\" type=\"Adult\"/>"
      << "<applyTo species=\"Subalpine_Fir\" type=\"Sapling\"/>"
      << "<applyTo species=\"Hybrid_Spruce\" type=\"Sapling\"/>"
      << "<applyTo species=\"Lodgepole_Pine\" type=\"Sapling\"/>"
      << "<applyTo species=\"Trembling_Aspen\" type=\"Sapling\"/>"
      << "<applyTo species=\"Black_Cottonwood\" type=\"Sapling\"/>"
      << "<applyTo species=\"Paper_Birch\" type=\"Sapling\"/>"
      << "</behavior>"
      << "</behaviorList>";
  oOut << "<QualityVigorClassifier2>"
      << "<ma_classifierVigBeta0>"
      << "<ma_cvb0Val species=\"Western_Hemlock\">0.1</ma_cvb0Val>"
      << "<ma_cvb0Val species=\"Western_Redcedar\">0.1</ma_cvb0Val>"
      << "<ma_cvb0Val species=\"Amabilis_Fir\">0.1</ma_cvb0Val>"
      << "<ma_cvb0Val species=\"Subalpine_Fir\">0</ma_cvb0Val>"
      << "<ma_cvb0Val species=\"Hybrid_Spruce\">0.3</ma_cvb0Val>"
      << "<ma_cvb0Val species=\"Lodgepole_Pine\">0.4</ma_cvb0Val>"
      << "<ma_cvb0Val species=\"Black_Cottonwood\">0.1</ma_cvb0Val>"
      << "<ma_cvb0Val species=\"Paper_Birch\">0.1</ma_cvb0Val>"
      << "<ma_cvb0Val species=\"Trembling_Aspen\">0.1</ma_cvb0Val>"
      << "</ma_classifierVigBeta0>"
      << "<ma_classifierVigBeta11>"
      << "<ma_cvb11Val species=\"Western_Hemlock\">0.2</ma_cvb11Val>"
      << "<ma_cvb11Val species=\"Western_Redcedar\">0.2</ma_cvb11Val>"
      << "<ma_cvb11Val species=\"Amabilis_Fir\">0.2</ma_cvb11Val>"
      << "<ma_cvb11Val species=\"Subalpine_Fir\">2.35</ma_cvb11Val>"
      << "<ma_cvb11Val species=\"Hybrid_Spruce\">0.1</ma_cvb11Val>"
      << "<ma_cvb11Val species=\"Lodgepole_Pine\">2.43</ma_cvb11Val>"
      << "<ma_cvb11Val species=\"Black_Cottonwood\">0.2</ma_cvb11Val>"
      << "<ma_cvb11Val species=\"Paper_Birch\">0.2</ma_cvb11Val>"
      << "<ma_cvb11Val species=\"Trembling_Aspen\">0.2</ma_cvb11Val>"
      << "</ma_classifierVigBeta11>"
      << "<ma_classifierVigBeta12>"
      << "<ma_cvb12Val species=\"Western_Hemlock\">-2.3</ma_cvb12Val>"
      << "<ma_cvb12Val species=\"Western_Redcedar\">-2.3</ma_cvb12Val>"
      << "<ma_cvb12Val species=\"Amabilis_Fir\">-2.3</ma_cvb12Val>"
      << "<ma_cvb12Val species=\"Subalpine_Fir\">1.12</ma_cvb12Val>"
      << "<ma_cvb12Val species=\"Hybrid_Spruce\">0.32</ma_cvb12Val>"
      << "<ma_cvb12Val species=\"Lodgepole_Pine\">1.3</ma_cvb12Val>"
      << "<ma_cvb12Val species=\"Black_Cottonwood\">-2.3</ma_cvb12Val>"
      << "<ma_cvb12Val species=\"Paper_Birch\">-2.3</ma_cvb12Val>"
      << "<ma_cvb12Val species=\"Trembling_Aspen\">-2.3</ma_cvb12Val>"
      << "</ma_classifierVigBeta12>"
      << "<ma_classifierVigBeta13>"
      << "<ma_cvb13Val species=\"Western_Hemlock\">0.13</ma_cvb13Val>"
      << "<ma_cvb13Val species=\"Western_Redcedar\">0.13</ma_cvb13Val>"
      << "<ma_cvb13Val species=\"Amabilis_Fir\">0.13</ma_cvb13Val>"
      << "<ma_cvb13Val species=\"Subalpine_Fir\">1</ma_cvb13Val>"
      << "<ma_cvb13Val species=\"Hybrid_Spruce\">-0.2</ma_cvb13Val>"
      << "<ma_cvb13Val species=\"Lodgepole_Pine\">1</ma_cvb13Val>"
      << "<ma_cvb13Val species=\"Black_Cottonwood\">0.13</ma_cvb13Val>"
      << "<ma_cvb13Val species=\"Paper_Birch\">0.13</ma_cvb13Val>"
      << "<ma_cvb13Val species=\"Trembling_Aspen\">0.13</ma_cvb13Val>"
      << "</ma_classifierVigBeta13>"
      << "<ma_classifierVigBeta14>"
      << "<ma_cvb14Val species=\"Western_Hemlock\">0.9</ma_cvb14Val>"
      << "<ma_cvb14Val species=\"Western_Redcedar\">0.9</ma_cvb14Val>"
      << "<ma_cvb14Val species=\"Amabilis_Fir\">0.9</ma_cvb14Val>"
      << "<ma_cvb14Val species=\"Subalpine_Fir\">0</ma_cvb14Val>"
      << "<ma_cvb14Val species=\"Hybrid_Spruce\">-1</ma_cvb14Val>"
      << "<ma_cvb14Val species=\"Lodgepole_Pine\">0</ma_cvb14Val>"
      << "<ma_cvb14Val species=\"Black_Cottonwood\">0.9</ma_cvb14Val>"
      << "<ma_cvb14Val species=\"Paper_Birch\">0.9</ma_cvb14Val>"
      << "<ma_cvb14Val species=\"Trembling_Aspen\">0.9</ma_cvb14Val>"
      << "</ma_classifierVigBeta14>"
      << "<ma_classifierVigBeta15>"
      << "<ma_cvb15Val species=\"Western_Hemlock\">1</ma_cvb15Val>"
      << "<ma_cvb15Val species=\"Western_Redcedar\">1</ma_cvb15Val>"
      << "<ma_cvb15Val species=\"Amabilis_Fir\">1</ma_cvb15Val>"
      << "<ma_cvb15Val species=\"Subalpine_Fir\">0.25</ma_cvb15Val>"
      << "<ma_cvb15Val species=\"Hybrid_Spruce\">1</ma_cvb15Val>"
      << "<ma_cvb15Val species=\"Lodgepole_Pine\">-0.45</ma_cvb15Val>"
      << "<ma_cvb15Val species=\"Black_Cottonwood\">1</ma_cvb15Val>"
      << "<ma_cvb15Val species=\"Paper_Birch\">1</ma_cvb15Val>"
      << "<ma_cvb15Val species=\"Trembling_Aspen\">1</ma_cvb15Val>"
      << "</ma_classifierVigBeta15>"
      << "<ma_classifierVigBeta16>"
      << "<ma_cvb16Val species=\"Western_Hemlock\">1</ma_cvb16Val>"
      << "<ma_cvb16Val species=\"Western_Redcedar\">1</ma_cvb16Val>"
      << "<ma_cvb16Val species=\"Amabilis_Fir\">1</ma_cvb16Val>"
      << "<ma_cvb16Val species=\"Subalpine_Fir\">0.36</ma_cvb16Val>"
      << "<ma_cvb16Val species=\"Hybrid_Spruce\">0</ma_cvb16Val>"
      << "<ma_cvb16Val species=\"Lodgepole_Pine\">0.46</ma_cvb16Val>"
      << "<ma_cvb16Val species=\"Black_Cottonwood\">1</ma_cvb16Val>"
      << "<ma_cvb16Val species=\"Paper_Birch\">1</ma_cvb16Val>"
      << "<ma_cvb16Val species=\"Trembling_Aspen\">1</ma_cvb16Val>"
      << "</ma_classifierVigBeta16>"
      << "<ma_classifierVigBeta2>"
      << "<ma_cvb2Val species=\"Western_Hemlock\">0.01</ma_cvb2Val>"
      << "<ma_cvb2Val species=\"Western_Redcedar\">0.01</ma_cvb2Val>"
      << "<ma_cvb2Val species=\"Amabilis_Fir\">0.01</ma_cvb2Val>"
      << "<ma_cvb2Val species=\"Subalpine_Fir\">0.02</ma_cvb2Val>"
      << "<ma_cvb2Val species=\"Hybrid_Spruce\">0.04</ma_cvb2Val>"
      << "<ma_cvb2Val species=\"Lodgepole_Pine\">0.1</ma_cvb2Val>"
      << "<ma_cvb2Val species=\"Black_Cottonwood\">0.01</ma_cvb2Val>"
      << "<ma_cvb2Val species=\"Paper_Birch\">0.01</ma_cvb2Val>"
      << "<ma_cvb2Val species=\"Trembling_Aspen\">0.01</ma_cvb2Val>"
      << "</ma_classifierVigBeta2>"
      << "<ma_classifierVigBeta3>"
      << "<ma_cvb3Val species=\"Western_Hemlock\">0.001</ma_cvb3Val>"
      << "<ma_cvb3Val species=\"Western_Redcedar\">0.001</ma_cvb3Val>"
      << "<ma_cvb3Val species=\"Amabilis_Fir\">0.001</ma_cvb3Val>"
      << "<ma_cvb3Val species=\"Subalpine_Fir\">0.2</ma_cvb3Val>"
      << "<ma_cvb3Val species=\"Hybrid_Spruce\">0.3</ma_cvb3Val>"
      << "<ma_cvb3Val species=\"Lodgepole_Pine\">0.4</ma_cvb3Val>"
      << "<ma_cvb3Val species=\"Black_Cottonwood\">0.001</ma_cvb3Val>"
      << "<ma_cvb3Val species=\"Paper_Birch\">0.001</ma_cvb3Val>"
      << "<ma_cvb3Val species=\"Trembling_Aspen\">0.001</ma_cvb3Val>"
      << "</ma_classifierVigBeta3>"
      << "<ma_classifierQualBeta0>"
      << "<ma_cqb0Val species=\"Western_Hemlock\">0.25</ma_cqb0Val>"
      << "<ma_cqb0Val species=\"Western_Redcedar\">0.25</ma_cqb0Val>"
      << "<ma_cqb0Val species=\"Amabilis_Fir\">0.25</ma_cqb0Val>"
      << "<ma_cqb0Val species=\"Subalpine_Fir\">1.13</ma_cqb0Val>"
      << "<ma_cqb0Val species=\"Hybrid_Spruce\">0</ma_cqb0Val>"
      << "<ma_cqb0Val species=\"Lodgepole_Pine\">1.15</ma_cqb0Val>"
      << "<ma_cqb0Val species=\"Black_Cottonwood\">0.25</ma_cqb0Val>"
      << "<ma_cqb0Val species=\"Paper_Birch\">0.25</ma_cqb0Val>"
      << "<ma_cqb0Val species=\"Trembling_Aspen\">0.25</ma_cqb0Val>"
      << "</ma_classifierQualBeta0>"
      << "<ma_classifierQualBeta11>"
      << "<ma_cqb11Val species=\"Western_Hemlock\">0.36</ma_cqb11Val>"
      << "<ma_cqb11Val species=\"Western_Redcedar\">0.36</ma_cqb11Val>"
      << "<ma_cqb11Val species=\"Amabilis_Fir\">0.36</ma_cqb11Val>"
      << "<ma_cqb11Val species=\"Subalpine_Fir\">0</ma_cqb11Val>"
      << "<ma_cqb11Val species=\"Hybrid_Spruce\">0.4</ma_cqb11Val>"
      << "<ma_cqb11Val species=\"Lodgepole_Pine\">0</ma_cqb11Val>"
      << "<ma_cqb11Val species=\"Black_Cottonwood\">0.36</ma_cqb11Val>"
      << "<ma_cqb11Val species=\"Paper_Birch\">0.36</ma_cqb11Val>"
      << "<ma_cqb11Val species=\"Trembling_Aspen\">0.36</ma_cqb11Val>"
      << "</ma_classifierQualBeta11>"
      << "<ma_classifierQualBeta12>"
      << "<ma_cqb12Val species=\"Western_Hemlock\">0.02</ma_cqb12Val>"
      << "<ma_cqb12Val species=\"Western_Redcedar\">0.02</ma_cqb12Val>"
      << "<ma_cqb12Val species=\"Amabilis_Fir\">0.02</ma_cqb12Val>"
      << "<ma_cqb12Val species=\"Subalpine_Fir\">10</ma_cqb12Val>"
      << "<ma_cqb12Val species=\"Hybrid_Spruce\">0.3</ma_cqb12Val>"
      << "<ma_cqb12Val species=\"Lodgepole_Pine\">30</ma_cqb12Val>"
      << "<ma_cqb12Val species=\"Black_Cottonwood\">30</ma_cqb12Val>"
      << "<ma_cqb12Val species=\"Paper_Birch\">30</ma_cqb12Val>"
      << "<ma_cqb12Val species=\"Trembling_Aspen\">30</ma_cqb12Val>"
      << "</ma_classifierQualBeta12>"
      << "<ma_classifierQualBeta13>"
      << "<ma_cqb13Val species=\"Western_Hemlock\">0.2</ma_cqb13Val>"
      << "<ma_cqb13Val species=\"Western_Redcedar\">0.2</ma_cqb13Val>"
      << "<ma_cqb13Val species=\"Amabilis_Fir\">0.2</ma_cqb13Val>"
      << "<ma_cqb13Val species=\"Subalpine_Fir\">10</ma_cqb13Val>"
      << "<ma_cqb13Val species=\"Hybrid_Spruce\">-0.3</ma_cqb13Val>"
      << "<ma_cqb13Val species=\"Lodgepole_Pine\">30</ma_cqb13Val>"
      << "<ma_cqb13Val species=\"Black_Cottonwood\">0.2</ma_cqb13Val>"
      << "<ma_cqb13Val species=\"Paper_Birch\">0.2</ma_cqb13Val>"
      << "<ma_cqb13Val species=\"Trembling_Aspen\">0.2</ma_cqb13Val>"
      << "</ma_classifierQualBeta13>"
      << "<ma_classifierQualBeta14>"
      << "<ma_cqb14Val species=\"Western_Hemlock\">-0.2</ma_cqb14Val>"
      << "<ma_cqb14Val species=\"Western_Redcedar\">-0.2</ma_cqb14Val>"
      << "<ma_cqb14Val species=\"Amabilis_Fir\">-0.2</ma_cqb14Val>"
      << "<ma_cqb14Val species=\"Subalpine_Fir\">10</ma_cqb14Val>"
      << "<ma_cqb14Val species=\"Hybrid_Spruce\">-0.4</ma_cqb14Val>"
      << "<ma_cqb14Val species=\"Lodgepole_Pine\">30</ma_cqb14Val>"
      << "<ma_cqb14Val species=\"Black_Cottonwood\">-0.2</ma_cqb14Val>"
      << "<ma_cqb14Val species=\"Paper_Birch\">-0.2</ma_cqb14Val>"
      << "<ma_cqb14Val species=\"Trembling_Aspen\">-0.2</ma_cqb14Val>"
      << "</ma_classifierQualBeta14>"
      << "<ma_classifierQualBeta2>"
      << "<ma_cqb2Val species=\"Western_Hemlock\">-0.2</ma_cqb2Val>"
      << "<ma_cqb2Val species=\"Western_Redcedar\">-0.2</ma_cqb2Val>"
      << "<ma_cqb2Val species=\"Amabilis_Fir\">-0.2</ma_cqb2Val>"
      << "<ma_cqb2Val species=\"Subalpine_Fir\">10</ma_cqb2Val>"
      << "<ma_cqb2Val species=\"Hybrid_Spruce\">0</ma_cqb2Val>"
      << "<ma_cqb2Val species=\"Lodgepole_Pine\">30</ma_cqb2Val>"
      << "<ma_cqb2Val species=\"Black_Cottonwood\">30</ma_cqb2Val>"
      << "<ma_cqb2Val species=\"Paper_Birch\">30</ma_cqb2Val>"
      << "<ma_cqb2Val species=\"Trembling_Aspen\">30</ma_cqb2Val>"
      << "</ma_classifierQualBeta2>"
      << "<ma_classifierQualBeta3>"
      << "<ma_cqb3Val species=\"Western_Hemlock\">1</ma_cqb3Val>"
      << "<ma_cqb3Val species=\"Western_Redcedar\">1</ma_cqb3Val>"
      << "<ma_cqb3Val species=\"Amabilis_Fir\">1</ma_cqb3Val>"
      << "<ma_cqb3Val species=\"Subalpine_Fir\">10</ma_cqb3Val>"
      << "<ma_cqb3Val species=\"Hybrid_Spruce\">0.1</ma_cqb3Val>"
      << "<ma_cqb3Val species=\"Lodgepole_Pine\">30</ma_cqb3Val>"
      << "<ma_cqb3Val species=\"Black_Cottonwood\">30</ma_cqb3Val>"
      << "<ma_cqb3Val species=\"Paper_Birch\">30</ma_cqb3Val>"
      << "<ma_cqb3Val species=\"Trembling_Aspen\">30</ma_cqb3Val>"
      << "</ma_classifierQualBeta3>"
      << "<ma_classifierNewAdultProbVigorous>"
      << "<ma_cnapvVal species=\"Western_Hemlock\">0.1</ma_cnapvVal>"
      << "<ma_cnapvVal species=\"Western_Redcedar\">0.1</ma_cnapvVal>"
      << "<ma_cnapvVal species=\"Amabilis_Fir\">0.1</ma_cnapvVal>"
      << "<ma_cnapvVal species=\"Subalpine_Fir\">0.25</ma_cnapvVal>"
      << "<ma_cnapvVal species=\"Hybrid_Spruce\">0.5</ma_cnapvVal>"
      << "<ma_cnapvVal species=\"Lodgepole_Pine\">0.74</ma_cnapvVal>"
      << "<ma_cnapvVal species=\"Black_Cottonwood\">0.1</ma_cnapvVal>"
      << "<ma_cnapvVal species=\"Paper_Birch\">0.1</ma_cnapvVal>"
      << "<ma_cnapvVal species=\"Trembling_Aspen\">0.1</ma_cnapvVal>"
      << "</ma_classifierNewAdultProbVigorous>"
      << "<ma_classifierNewAdultProbSawlog>"
      << "<ma_cnapsVal species=\"Western_Hemlock\">0.9</ma_cnapsVal>"
      << "<ma_cnapsVal species=\"Western_Redcedar\">0.9</ma_cnapsVal>"
      << "<ma_cnapsVal species=\"Amabilis_Fir\">0.9</ma_cnapsVal>"
      << "<ma_cnapsVal species=\"Subalpine_Fir\">0.25</ma_cnapsVal>"
      << "<ma_cnapsVal species=\"Hybrid_Spruce\">0.3</ma_cnapsVal>"
      << "<ma_cnapsVal species=\"Lodgepole_Pine\">0.74</ma_cnapsVal>"
      << "<ma_cnapsVal species=\"Black_Cottonwood\">0.9</ma_cnapsVal>"
      << "<ma_cnapsVal species=\"Paper_Birch\">0.9</ma_cnapsVal>"
      << "<ma_cnapsVal species=\"Trembling_Aspen\">0.9</ma_cnapsVal>"
      << "</ma_classifierNewAdultProbSawlog>"
      << "<ma_classifierDeciduous>"
      << "<ma_cdVal species=\"Western_Hemlock\">0</ma_cdVal>"
      << "<ma_cdVal species=\"Western_Redcedar\">0</ma_cdVal>"
      << "<ma_cdVal species=\"Amabilis_Fir\">0</ma_cdVal>"
      << "<ma_cdVal species=\"Subalpine_Fir\">0</ma_cdVal>"
      << "<ma_cdVal species=\"Hybrid_Spruce\">0</ma_cdVal>"
      << "<ma_cdVal species=\"Lodgepole_Pine\">0</ma_cdVal>"
      << "<ma_cdVal species=\"Black_Cottonwood\">1</ma_cdVal>"
      << "<ma_cdVal species=\"Paper_Birch\">1</ma_cdVal>"
      << "<ma_cdVal species=\"Trembling_Aspen\">1</ma_cdVal>"
      << "</ma_classifierDeciduous>"
      << "</QualityVigorClassifier2>"
      << "<Harvest1>"
      << "<ha_cutEvent>"
      << "<ha_applyToSpecies species=\"Western_Redcedar\" />"
      << "<ha_timestep>1</ha_timestep>"
      << "<ha_cutType>partial</ha_cutType>"
      << "<ha_cutAmountType>absolute density</ha_cutAmountType>"
      << "<ha_dbhRange>"
      << "<ha_low>0.0</ha_low>"
      << "<ha_high>87.0</ha_high>"
      << "<ha_amountToCut>10.0</ha_amountToCut>"
      << "</ha_dbhRange>"
      << "<ha_priority>"
      << "<ha_name>Growth</ha_name>"
      << "<ha_type>float</ha_type>"
      << "<ha_min>5</ha_min>"
      << "<ha_max>10</ha_max>"
      << "</ha_priority>";
  for (int i = 0; i < 25; i++) {
    for (int j = 0; j < 25; j++) {
      oOut << "<ha_applyToCell x=\"" << i << "\" y=\"" << j << "\" /> ";
    }
  }
  oOut << "</ha_cutEvent>"
      << "<ha_cutEvent>"
      << "<ha_applyToSpecies species=\"Amabilis_Fir\" />"
      << "<ha_applyToSpecies species=\"Subalpine_Fir\" />"
      << "<ha_timestep>1</ha_timestep>"
      << "<ha_cutType>partial</ha_cutType>"
      << "<ha_cutAmountType>absolute density</ha_cutAmountType>"
      << "<ha_dbhRange>"
      << "<ha_low>10.0</ha_low>"
      << "<ha_high>50.0</ha_high>"
      << "<ha_amountToCut>5.0</ha_amountToCut>"
      << "</ha_dbhRange>"
      << "<ha_priority>"
      << "<ha_name>YearsInfested</ha_name>"
      << "<ha_type>int</ha_type>"
      << "<ha_min>0</ha_min>"
      << "<ha_max>100</ha_max>"
      << "</ha_priority>"
      << "<ha_priority>"
      << "<ha_name>vigorous</ha_name>"
      << "<ha_type>bool</ha_type>"
      << "<ha_min>1</ha_min>"
      << "</ha_priority>";
  for (int i = 0; i < 25; i++) {
    for (int j = 0; j < 25; j++) {
      oOut << "<ha_applyToCell x=\"" << i << "\" y=\"" << j << "\" /> ";
    }
  }
  oOut << "</ha_cutEvent>"
      << "<ha_cutEvent>"
      << "<ha_applyToSpecies species=\"Hybrid_Spruce\" />"
      << "<ha_timestep>1</ha_timestep>"
      << "<ha_cutType>partial</ha_cutType>"
      << "<ha_cutAmountType>percent of basal area</ha_cutAmountType>"
      << "<ha_dbhRange>"
      << "<ha_low>0.0</ha_low>"
      << "<ha_high>3000.0</ha_high>"
      << "<ha_amountToCut>85.0</ha_amountToCut>"
      << "</ha_dbhRange>"
      << "<ha_priority>"
      << "<ha_name>YearsInfested</ha_name>"
      << "<ha_type>int</ha_type>"
      << "<ha_min>3</ha_min>"
      << "<ha_max>100</ha_max>"
      << "</ha_priority>"
      << "<ha_priority>"
      << "<ha_name>vigorous</ha_name>"
      << "<ha_type>bool</ha_type>"
      << "<ha_min>1</ha_min>"
      << "</ha_priority>"
      << "<ha_priority>"
      << "<ha_name>Growth</ha_name>"
      << "<ha_type>float</ha_type>"
      << "<ha_min>5</ha_min>"
      << "<ha_max>10</ha_max>"
      << "</ha_priority>";
  for (int i = 0; i < 25; i++) {
    for (int j = 0; j < 25; j++) {
      oOut << "<ha_applyToCell x=\"" << i << "\" y=\"" << j << "\" /> ";
    }
  }
  oOut << "</ha_cutEvent>"
      << "<ha_cutEvent>"
      << "<ha_applyToSpecies species=\"Trembling_Aspen\" />"
      << "<ha_timestep>1</ha_timestep>"
      << "<ha_cutType>partial</ha_cutType>"
      << "<ha_cutAmountType>absolute basal area</ha_cutAmountType>"
      << "<ha_dbhRange>"
      << "<ha_low>0.0</ha_low>"
      << "<ha_high>3000.0</ha_high>"
      << "<ha_amountToCut>2.0</ha_amountToCut>"
      << "</ha_dbhRange>"
      << "<ha_priority>"
      << "<ha_name>treeclass</ha_name>"
      << "<ha_type>int</ha_type>"
      << "<ha_min>3</ha_min>"
      << "<ha_max>3</ha_max>"
      << "</ha_priority>"
      << "<ha_priority>"
      << "<ha_name>treeclass</ha_name>"
      << "<ha_type>int</ha_type>"
      << "<ha_min>4</ha_min>"
      << "<ha_max>4</ha_max>"
      << "</ha_priority>";
  for (int i = 0; i < 25; i++) {
    for (int j = 0; j < 25; j++) {
      oOut << "<ha_applyToCell x=\"" << i << "\" y=\"" << j << "\" /> ";
    }
  }
  oOut << "</ha_cutEvent>"
      << "<ha_cutEvent>"
      << "<ha_applyToSpecies species=\"Black_Cottonwood\" />"
      << "<ha_timestep>1</ha_timestep>"
      << "<ha_cutType>partial</ha_cutType>"
      << "<ha_cutAmountType>absolute basal area</ha_cutAmountType>"
      << "<ha_dbhRange>"
      << "<ha_low>0.0</ha_low>"
      << "<ha_high>3000.0</ha_high>"
      << "<ha_amountToCut>4.0</ha_amountToCut>"
      << "</ha_dbhRange>"
      << "<ha_priority>"
      << "<ha_name>treeclass</ha_name>"
      << "<ha_type>int</ha_type>"
      << "<ha_min>3</ha_min>"
      << "<ha_max>3</ha_max>"
      << "</ha_priority>"
      << "<ha_priority>"
      << "<ha_name>treeclass</ha_name>"
      << "<ha_type>int</ha_type>"
      << "<ha_min>4</ha_min>"
      << "<ha_max>4</ha_max>"
      << "</ha_priority>";
  for (int i = 0; i < 25; i++) {
    for (int j = 0; j < 25; j++) {
      oOut << "<ha_applyToCell x=\"" << i << "\" y=\"" << j << "\" /> ";
    }
  }
  oOut << "</ha_cutEvent>"
      << "<ha_cutEvent>"
      << "<ha_applyToSpecies species=\"Paper_Birch\" />"
      << "<ha_timestep>1</ha_timestep>"
      << "<ha_cutType>partial</ha_cutType>"
      << "<ha_cutAmountType>absolute basal area</ha_cutAmountType>"
      << "<ha_dbhRange>"
      << "<ha_low>0.0</ha_low>"
      << "<ha_high>3000.0</ha_high>"
      << "<ha_amountToCut>7.0</ha_amountToCut>"
      << "</ha_dbhRange>"
      << "<ha_priority>"
      << "<ha_name>treeclass</ha_name>"
      << "<ha_type>int</ha_type>"
      << "<ha_min>3</ha_min>"
      << "<ha_max>3</ha_max>"
      << "</ha_priority>"
      << "<ha_priority>"
      << "<ha_name>treeclass</ha_name>"
      << "<ha_type>int</ha_type>"
      << "<ha_min>4</ha_min>"
      << "<ha_max>4</ha_max>"
      << "</ha_priority>";
  for (int i = 0; i < 25; i++) {
    for (int j = 0; j < 25; j++) {
      oOut << "<ha_applyToCell x=\"" << i << "\" y=\"" << j << "\" /> ";
    }
  }
  oOut << "</ha_cutEvent>"
      << "<ha_cutEvent>"
      << "<ha_applyToSpecies species=\"Lodgepole_Pine\" />"
      << "<ha_timestep>1</ha_timestep>"
      << "<ha_cutType>partial</ha_cutType>"
      << "<ha_cutAmountType>absolute density</ha_cutAmountType>"
      << "<ha_dbhRange>"
      << "<ha_low>0.0</ha_low>"
      << "<ha_high>3000.0</ha_high>"
      << "<ha_amountToCut>10.0</ha_amountToCut>"
      << "</ha_dbhRange>";
  for (int i = 0; i < 25; i++) {
    for (int j = 0; j < 25; j++) {
      oOut << "<ha_applyToCell x=\"" << i << "\" y=\"" << j << "\" /> ";
    }
  }
  oOut << "</ha_cutEvent>"
      << "</Harvest1>";
  oOut << "<InsectInfestation4>"
      << "<di_insectIntercept>"
      << "<di_iiVal species=\"Subalpine_Fir\">0</di_iiVal>"
      << "<di_iiVal species=\"Hybrid_Spruce\">0.01</di_iiVal>"
      << "<di_iiVal species=\"Lodgepole_Pine\">0.01</di_iiVal>"
      << "<di_iiVal species=\"Trembling_Aspen\">0.01</di_iiVal>"
      << "<di_iiVal species=\"Black_Cottonwood\">0.01</di_iiVal>"
      << "<di_iiVal species=\"Paper_Birch\">0.01</di_iiVal>"
      << "</di_insectIntercept>"
      << "<di_insectMaxInfestation>"
      << "<di_imiVal species=\"Subalpine_Fir\">1</di_imiVal>"
      << "<di_imiVal species=\"Hybrid_Spruce\">0.6</di_imiVal>"
      << "<di_imiVal species=\"Lodgepole_Pine\">1</di_imiVal>"
      << "<di_imiVal species=\"Trembling_Aspen\">1</di_imiVal>"
      << "<di_imiVal species=\"Black_Cottonwood\">1</di_imiVal>"
      << "<di_imiVal species=\"Paper_Birch\">1</di_imiVal>"
      << "</di_insectMaxInfestation>"
      << "<di_insectX0>"
      << "<di_ix0Val species=\"Subalpine_Fir\">11</di_ix0Val>"
      << "<di_ix0Val species=\"Hybrid_Spruce\">8</di_ix0Val>"
      << "<di_ix0Val species=\"Lodgepole_Pine\">5</di_ix0Val>"
      << "<di_ix0Val species=\"Trembling_Aspen\">9</di_ix0Val>"
      << "<di_ix0Val species=\"Black_Cottonwood\">5</di_ix0Val>"
      << "<di_ix0Val species=\"Paper_Birch\">9</di_ix0Val>"
      << "</di_insectX0>"
      << "<di_insectXb>"
      << "<di_ixbVal species=\"Subalpine_Fir\">-8</di_ixbVal>"
      << "<di_ixbVal species=\"Hybrid_Spruce\">-10</di_ixbVal>"
      << "<di_ixbVal species=\"Lodgepole_Pine\">-4</di_ixbVal>"
      << "<di_ixbVal species=\"Trembling_Aspen\">-6</di_ixbVal>"
      << "<di_ixbVal species=\"Black_Cottonwood\">-4</di_ixbVal>"
      << "<di_ixbVal species=\"Paper_Birch\">-6</di_ixbVal>"
      << "</di_insectXb>"
      << "<di_insectMinDBH>"
      << "<di_imdVal species=\"Subalpine_Fir\">2.2</di_imdVal>"
      << "<di_imdVal species=\"Hybrid_Spruce\">2.2</di_imdVal>"
      << "<di_imdVal species=\"Lodgepole_Pine\">2.2</di_imdVal>"
      << "<di_imdVal species=\"Trembling_Aspen\">2.2</di_imdVal>"
      << "<di_imdVal species=\"Black_Cottonwood\">2.2</di_imdVal>"
      << "<di_imdVal species=\"Paper_Birch\">2.2</di_imdVal>"
      << "</di_insectMinDBH>"
      << "<di_insectStartTimestep>10</di_insectStartTimestep>"
      << "</InsectInfestation4>"
      << "<ConstRadialGrowth3>"
      << "<gr_adultConstRadialInc>"
      << "<gr_acriVal species=\"Western_Hemlock\">0</gr_acriVal>"
      << "<gr_acriVal species=\"Western_Redcedar\">0</gr_acriVal>"
      << "<gr_acriVal species=\"Amabilis_Fir\">0</gr_acriVal>"
      << "<gr_acriVal species=\"Subalpine_Fir\">0</gr_acriVal>"
      << "<gr_acriVal species=\"Hybrid_Spruce\">0</gr_acriVal>"
      << "<gr_acriVal species=\"Lodgepole_Pine\">0</gr_acriVal>"
      << "<gr_acriVal species=\"Trembling_Aspen\">0</gr_acriVal>"
      << "<gr_acriVal species=\"Black_Cottonwood\">0</gr_acriVal>"
      << "<gr_acriVal species=\"Paper_Birch\">0</gr_acriVal>"
      << "</gr_adultConstRadialInc>"
      << "</ConstRadialGrowth3>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteHarvestFileBeginning()
/////////////////////////////////////////////////////////////////////////////
void WriteHarvestFileBeginning(std::fstream &oOut, int iRandomSeed) {

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">"
      << "<plot>"
      << "<timesteps>3</timesteps>"
      << "<yearsPerTimestep>1</yearsPerTimestep>"
      << "<randomSeed>" << iRandomSeed << "</randomSeed>"
      << "<plot_lenX>200.0</plot_lenX>"
      << "<plot_lenY>200.0</plot_lenY>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88171785</plot_temp_C>"
      << "<plot_latitude>55.37</plot_latitude>"
      << "</plot>"
      << "<trees>"
      << "<tr_speciesList>"
      << "<tr_species speciesName=\"Western_Hemlock\"/>"
      << "<tr_species speciesName=\"Western_Redcedar\"/>"
      << "<tr_species speciesName=\"Amabilis_Fir\"/>"
      << "<tr_species speciesName=\"Subalpine_Fir\"/>"
      << "<tr_species speciesName=\"Hybrid_Spruce\"/>"
      << "<tr_species speciesName=\"Lodgepole_Pine\"/>"
      << "<tr_species speciesName=\"Trembling_Aspen\"/>"
      << "<tr_species speciesName=\"Black_Cottonwood\"/>"
      << "<tr_species speciesName=\"Paper_Birch\"/>"
      << "</tr_speciesList>"
      << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
      << "<tr_minAdultDBH>"
      << "<tr_madVal species=\"Western_Hemlock\">10</tr_madVal>"
      << "<tr_madVal species=\"Western_Redcedar\">10</tr_madVal>"
      << "<tr_madVal species=\"Amabilis_Fir\">10</tr_madVal>"
      << "<tr_madVal species=\"Subalpine_Fir\">10</tr_madVal>"
      << "<tr_madVal species=\"Hybrid_Spruce\">10</tr_madVal>"
      << "<tr_madVal species=\"Lodgepole_Pine\">10</tr_madVal>"
      << "<tr_madVal species=\"Trembling_Aspen\">10</tr_madVal>"
      << "<tr_madVal species=\"Black_Cottonwood\">10</tr_madVal>"
      << "<tr_madVal species=\"Paper_Birch\">10</tr_madVal>"
      << "</tr_minAdultDBH>"
      << "<tr_maxSeedlingHeight>"
      << "<tr_mshVal species=\"Western_Hemlock\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Western_Redcedar\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Amabilis_Fir\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Subalpine_Fir\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Hybrid_Spruce\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Lodgepole_Pine\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Trembling_Aspen\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Black_Cottonwood\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Paper_Birch\">1.35</tr_mshVal>"
      << "</tr_maxSeedlingHeight>";

  WriteHarvestTreeMap(oOut);

  oOut << "</trees>"
      << "<allometry>"
      << "<tr_canopyHeight>"
      << "<tr_chVal species=\"Western_Hemlock\">39.48</tr_chVal>"
      << "<tr_chVal species=\"Western_Redcedar\">39.54</tr_chVal>"
      << "<tr_chVal species=\"Amabilis_Fir\">40</tr_chVal>"
      << "<tr_chVal species=\"Subalpine_Fir\">40</tr_chVal>"
      << "<tr_chVal species=\"Hybrid_Spruce\">45</tr_chVal>"
      << "<tr_chVal species=\"Lodgepole_Pine\">40</tr_chVal>"
      << "<tr_chVal species=\"Trembling_Aspen\">39.14</tr_chVal>"
      << "<tr_chVal species=\"Black_Cottonwood\">39.47</tr_chVal>"
      << "<tr_chVal species=\"Paper_Birch\">33.18</tr_chVal>"
      << "</tr_canopyHeight>"
      << "<tr_stdAsympCrownRad>"
      << "<tr_sacrVal species=\"Western_Hemlock\">0.0549</tr_sacrVal>"
      << "<tr_sacrVal species=\"Western_Redcedar\">0.0614</tr_sacrVal>"
      << "<tr_sacrVal species=\"Amabilis_Fir\">0.0242</tr_sacrVal>"
      << "<tr_sacrVal species=\"Subalpine_Fir\">0.0251</tr_sacrVal>"
      << "<tr_sacrVal species=\"Hybrid_Spruce\">0.0239</tr_sacrVal>"
      << "<tr_sacrVal species=\"Lodgepole_Pine\">0.0303</tr_sacrVal>"
      << "<tr_sacrVal species=\"Trembling_Aspen\">0.0328</tr_sacrVal>"
      << "<tr_sacrVal species=\"Black_Cottonwood\">0.0247</tr_sacrVal>"
      << "<tr_sacrVal species=\"Paper_Birch\">0.0484</tr_sacrVal>"
      << "</tr_stdAsympCrownRad>"
      << "<tr_stdCrownRadExp>"
      << "<tr_screVal species=\"Western_Hemlock\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Western_Redcedar\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Amabilis_Fir\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Subalpine_Fir\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Hybrid_Spruce\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Lodgepole_Pine\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Trembling_Aspen\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Black_Cottonwood\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Paper_Birch\">1.0</tr_screVal>"
      << "</tr_stdCrownRadExp>"
      << "<tr_conversionDiam10ToDBH>"
      << "<tr_cdtdVal species=\"Western_Hemlock\">0.8008</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Western_Redcedar\">0.5944</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Amabilis_Fir\">0.7059</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Subalpine_Fir\">0.7776</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Hybrid_Spruce\">0.6933</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Lodgepole_Pine\">0.8014</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Trembling_Aspen\">0.7992</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Black_Cottonwood\">0.7926</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Paper_Birch\">0.7803</tr_cdtdVal>"
      << "</tr_conversionDiam10ToDBH>"
      << "<tr_interceptDiam10ToDBH>"
      << "<tr_idtdVal species=\"Western_Hemlock\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Western_Redcedar\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Amabilis_Fir\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Subalpine_Fir\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Hybrid_Spruce\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Lodgepole_Pine\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Trembling_Aspen\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Black_Cottonwood\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Paper_Birch\">0</tr_idtdVal>"
      << "</tr_interceptDiam10ToDBH>"
      << "<tr_stdAsympCrownHt>"
      << "<tr_sachVal species=\"Western_Hemlock\">0.389</tr_sachVal>"
      << "<tr_sachVal species=\"Western_Redcedar\">0.368</tr_sachVal>"
      << "<tr_sachVal species=\"Amabilis_Fir\">0.464</tr_sachVal>"
      << "<tr_sachVal species=\"Subalpine_Fir\">0.454</tr_sachVal>"
      << "<tr_sachVal species=\"Hybrid_Spruce\">0.405</tr_sachVal>"
      << "<tr_sachVal species=\"Lodgepole_Pine\">0.201</tr_sachVal>"
      << "<tr_sachVal species=\"Trembling_Aspen\">0.301</tr_sachVal>"
      << "<tr_sachVal species=\"Black_Cottonwood\">0.42</tr_sachVal>"
      << "<tr_sachVal species=\"Paper_Birch\">0.315</tr_sachVal>"
      << "</tr_stdAsympCrownHt>"
      << "<tr_stdCrownHtExp>"
      << "<tr_scheVal species=\"Western_Hemlock\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Western_Redcedar\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Amabilis_Fir\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Subalpine_Fir\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Hybrid_Spruce\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Lodgepole_Pine\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Trembling_Aspen\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Black_Cottonwood\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Paper_Birch\">1.0</tr_scheVal>"
      << "</tr_stdCrownHtExp>"
      << "<tr_slopeOfHeight-Diam10>"
      << "<tr_sohdVal species=\"Western_Hemlock\">0.03418</tr_sohdVal>"
      << "<tr_sohdVal species=\"Western_Redcedar\">0.0269</tr_sohdVal>"
      << "<tr_sohdVal species=\"Amabilis_Fir\">0.02871</tr_sohdVal>"
      << "<tr_sohdVal species=\"Subalpine_Fir\">0.02815</tr_sohdVal>"
      << "<tr_sohdVal species=\"Hybrid_Spruce\">0.02871</tr_sohdVal>"
      << "<tr_sohdVal species=\"Lodgepole_Pine\">0.03224</tr_sohdVal>"
      << "<tr_sohdVal species=\"Trembling_Aspen\">0.04796</tr_sohdVal>"
      << "<tr_sohdVal species=\"Black_Cottonwood\">0.04681</tr_sohdVal>"
      << "<tr_sohdVal species=\"Paper_Birch\">0.04101</tr_sohdVal>"
      << "</tr_slopeOfHeight-Diam10>"
      << "<tr_slopeOfAsymHeight>"
      << "<tr_soahVal species=\"Western_Hemlock\">0.0299</tr_soahVal>"
      << "<tr_soahVal species=\"Western_Redcedar\">0.0241</tr_soahVal>"
      << "<tr_soahVal species=\"Amabilis_Fir\">0.0263</tr_soahVal>"
      << "<tr_soahVal species=\"Subalpine_Fir\">0.0264</tr_soahVal>"
      << "<tr_soahVal species=\"Hybrid_Spruce\">0.0264</tr_soahVal>"
      << "<tr_soahVal species=\"Lodgepole_Pine\">0.0333</tr_soahVal>"
      << "<tr_soahVal species=\"Trembling_Aspen\">0.0352</tr_soahVal>"
      << "<tr_soahVal species=\"Black_Cottonwood\">0.0347</tr_soahVal>"
      << "<tr_soahVal species=\"Paper_Birch\">0.0454</tr_soahVal>"
      << "</tr_slopeOfAsymHeight>"
      << "<tr_whatSeedlingHeightDiam>"
      << "<tr_wsehdVal species=\"Western_Hemlock\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Western_Redcedar\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Amabilis_Fir\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Subalpine_Fir\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Hybrid_Spruce\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Lodgepole_Pine\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Trembling_Aspen\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Black_Cottonwood\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Paper_Birch\">0</tr_wsehdVal>"
      << "</tr_whatSeedlingHeightDiam>"
      << "<tr_whatSaplingHeightDiam>"
      << "<tr_wsahdVal species=\"Western_Hemlock\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Western_Redcedar\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Amabilis_Fir\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Subalpine_Fir\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Hybrid_Spruce\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Lodgepole_Pine\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Trembling_Aspen\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Black_Cottonwood\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Paper_Birch\">0</tr_wsahdVal>"
      << "</tr_whatSaplingHeightDiam>"
      << "<tr_whatAdultHeightDiam>"
      << "<tr_wahdVal species=\"Western_Hemlock\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Western_Redcedar\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Amabilis_Fir\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Subalpine_Fir\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Hybrid_Spruce\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Lodgepole_Pine\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Trembling_Aspen\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Black_Cottonwood\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Paper_Birch\">0</tr_wahdVal>"
      << "</tr_whatAdultHeightDiam>"
      << "<tr_whatAdultCrownRadDiam>"
      << "<tr_wacrdVal species=\"Western_Hemlock\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Western_Redcedar\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Amabilis_Fir\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Subalpine_Fir\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Hybrid_Spruce\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Lodgepole_Pine\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Trembling_Aspen\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Black_Cottonwood\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Paper_Birch\">0</tr_wacrdVal>"
      << "</tr_whatAdultCrownRadDiam>"
      << "<tr_whatAdultCrownHeightHeight>"
      << "<tr_wachhVal species=\"Western_Hemlock\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Western_Redcedar\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Amabilis_Fir\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Subalpine_Fir\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Hybrid_Spruce\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Lodgepole_Pine\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Trembling_Aspen\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Black_Cottonwood\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Paper_Birch\">0</tr_wachhVal>"
      << "</tr_whatAdultCrownHeightHeight>"
      << "<tr_whatSaplingCrownRadDiam>"
      << "<tr_wscrdVal species=\"Western_Hemlock\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Western_Redcedar\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Amabilis_Fir\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Subalpine_Fir\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Hybrid_Spruce\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Lodgepole_Pine\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Trembling_Aspen\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Black_Cottonwood\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Paper_Birch\">0</tr_wscrdVal>"
      << "</tr_whatSaplingCrownRadDiam>"
      << "<tr_whatSaplingCrownHeightHeight>"
      << "<tr_wschhVal species=\"Western_Hemlock\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Western_Redcedar\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Amabilis_Fir\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Subalpine_Fir\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Hybrid_Spruce\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Lodgepole_Pine\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Trembling_Aspen\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Black_Cottonwood\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Paper_Birch\">0</tr_wschhVal>"
      << "</tr_whatSaplingCrownHeightHeight>"
      << "</allometry>";
}

/////////////////////////////////////////////////////////////////////////////
// WriteHarvestTreeMap()
/////////////////////////////////////////////////////////////////////////////
void WriteHarvestTreeMap(std::fstream &oOut) {

  oOut << "<tr_treemap>";
  oOut << "<tm_treeSettings sp=\"Western_Hemlock\" tp=\"2\">";
  oOut << "<tm_floatCodes>";
  oOut << "<tm_floatCode label=\"X\">0</tm_floatCode>";
  oOut << "<tm_floatCode label=\"Y\">1</tm_floatCode>";
  oOut << "<tm_floatCode label=\"DBH\">4</tm_floatCode>";
  oOut << "<tm_floatCode label=\"Height\">2</tm_floatCode>";
  oOut << "</tm_floatCodes>";
  oOut << "</tm_treeSettings>";
  oOut << "<tm_treeSettings sp=\"Western_Redcedar\" tp=\"2\">";
  oOut << "<tm_floatCodes>";
  oOut << "<tm_floatCode label=\"X\">0</tm_floatCode>";
  oOut << "<tm_floatCode label=\"Y\">1</tm_floatCode>";
  oOut << "<tm_floatCode label=\"DBH\">4</tm_floatCode>";
  oOut << "<tm_floatCode label=\"Height\">2</tm_floatCode>";
  oOut << "</tm_floatCodes>";
  oOut << "</tm_treeSettings>";
  oOut << "<tm_treeSettings sp=\"Amabilis_Fir\" tp=\"2\">";
  oOut << "<tm_floatCodes>";
  oOut << "<tm_floatCode label=\"X\">0</tm_floatCode>";
  oOut << "<tm_floatCode label=\"Y\">1</tm_floatCode>";
  oOut << "<tm_floatCode label=\"DBH\">4</tm_floatCode>";
  oOut << "<tm_floatCode label=\"Height\">2</tm_floatCode>";
  oOut << "</tm_floatCodes>";
  oOut << "</tm_treeSettings>";
  oOut << "<tm_treeSettings sp=\"Hybrid_Spruce\" tp=\"2\">";
  oOut << "<tm_floatCodes>";
  oOut << "<tm_floatCode label=\"X\">0</tm_floatCode>";
  oOut << "<tm_floatCode label=\"Y\">1</tm_floatCode>";
  oOut << "<tm_floatCode label=\"DBH\">4</tm_floatCode>";
  oOut << "<tm_floatCode label=\"Height\">2</tm_floatCode>";
  oOut << "</tm_floatCodes>";
  oOut << "</tm_treeSettings>";
  oOut << "<tm_treeSettings sp=\"Lodgepole_Pine\" tp=\"2\">";
  oOut << "<tm_floatCodes>";
  oOut << "<tm_floatCode label=\"X\">0</tm_floatCode>";
  oOut << "<tm_floatCode label=\"Y\">1</tm_floatCode>";
  oOut << "<tm_floatCode label=\"DBH\">4</tm_floatCode>";
  oOut << "<tm_floatCode label=\"Height\">2</tm_floatCode>";
  oOut << "</tm_floatCodes>";
  oOut << "</tm_treeSettings>";
  oOut << "<tm_treeSettings sp=\"Subalpine_Fir\" tp=\"2\">";
  oOut << "<tm_floatCodes>";
  oOut << "<tm_floatCode label=\"X\">0</tm_floatCode>";
  oOut << "<tm_floatCode label=\"Y\">1</tm_floatCode>";
  oOut << "<tm_floatCode label=\"DBH\">4</tm_floatCode>";
  oOut << "<tm_floatCode label=\"Height\">2</tm_floatCode>";
  oOut << "</tm_floatCodes>";
  oOut << "</tm_treeSettings>";
  oOut << "<tm_treeSettings sp=\"Black_Cottonwood\" tp=\"2\">";
  oOut << "<tm_floatCodes>";
  oOut << "<tm_floatCode label=\"X\">0</tm_floatCode>";
  oOut << "<tm_floatCode label=\"Y\">1</tm_floatCode>";
  oOut << "<tm_floatCode label=\"DBH\">4</tm_floatCode>";
  oOut << "<tm_floatCode label=\"Height\">2</tm_floatCode>";
  oOut << "</tm_floatCodes>";
  oOut << "</tm_treeSettings>";
  oOut << "<tm_treeSettings sp=\"Trembling_Aspen\" tp=\"2\">";
  oOut << "<tm_floatCodes>";
  oOut << "<tm_floatCode label=\"X\">0</tm_floatCode>";
  oOut << "<tm_floatCode label=\"Y\">1</tm_floatCode>";
  oOut << "<tm_floatCode label=\"DBH\">4</tm_floatCode>";
  oOut << "<tm_floatCode label=\"Height\">2</tm_floatCode>";
  oOut << "</tm_floatCodes>";
  oOut << "</tm_treeSettings>";
  oOut << "<tm_treeSettings sp=\"Paper_Birch\" tp=\"2\">";
  oOut << "<tm_floatCodes>";
  oOut << "<tm_floatCode label=\"X\">0</tm_floatCode>";
  oOut << "<tm_floatCode label=\"Y\">1</tm_floatCode>";
  oOut << "<tm_floatCode label=\"DBH\">4</tm_floatCode>";
  oOut << "<tm_floatCode label=\"Height\">2</tm_floatCode>";
  oOut << "</tm_floatCodes>";
  oOut << "</tm_treeSettings>";
  oOut << "<tm_treeSettings sp=\"Western_Hemlock\" tp=\"3\">";
  oOut << "<tm_floatCodes>";
  oOut << "<tm_floatCode label=\"X\">0</tm_floatCode>";
  oOut << "<tm_floatCode label=\"Y\">1</tm_floatCode>";
  oOut << "<tm_floatCode label=\"DBH\">3</tm_floatCode>";
  oOut << "<tm_floatCode label=\"Height\">2</tm_floatCode>";
  oOut << "</tm_floatCodes>";
  oOut << "</tm_treeSettings>";
  oOut << "<tm_treeSettings sp=\"Western_Redcedar\" tp=\"3\">";
  oOut << "<tm_floatCodes>";
  oOut << "<tm_floatCode label=\"X\">0</tm_floatCode>";
  oOut << "<tm_floatCode label=\"Y\">1</tm_floatCode>";
  oOut << "<tm_floatCode label=\"DBH\">3</tm_floatCode>";
  oOut << "<tm_floatCode label=\"Height\">2</tm_floatCode>";
  oOut << "</tm_floatCodes>";
  oOut << "</tm_treeSettings>";
  oOut << "<tm_treeSettings sp=\"Amabilis_Fir\" tp=\"3\">";
  oOut << "<tm_floatCodes>";
  oOut << "<tm_floatCode label=\"X\">0</tm_floatCode>";
  oOut << "<tm_floatCode label=\"Y\">1</tm_floatCode>";
  oOut << "<tm_floatCode label=\"DBH\">3</tm_floatCode>";
  oOut << "<tm_floatCode label=\"Height\">2</tm_floatCode>";
  oOut << "</tm_floatCodes>";
  oOut << "</tm_treeSettings>";
  oOut << "<tm_treeSettings sp=\"Hybrid_Spruce\" tp=\"3\">";
  oOut << "<tm_floatCodes>";
  oOut << "<tm_floatCode label=\"X\">0</tm_floatCode>";
  oOut << "<tm_floatCode label=\"Y\">1</tm_floatCode>";
  oOut << "<tm_floatCode label=\"DBH\">3</tm_floatCode>";
  oOut << "<tm_floatCode label=\"Height\">2</tm_floatCode>";
  oOut << "</tm_floatCodes>";
  oOut << "</tm_treeSettings>";
  oOut << "<tm_treeSettings sp=\"Lodgepole_Pine\" tp=\"3\">";
  oOut << "<tm_floatCodes>";
  oOut << "<tm_floatCode label=\"X\">0</tm_floatCode>";
  oOut << "<tm_floatCode label=\"Y\">1</tm_floatCode>";
  oOut << "<tm_floatCode label=\"DBH\">3</tm_floatCode>";
  oOut << "<tm_floatCode label=\"Height\">2</tm_floatCode>";
  oOut << "</tm_floatCodes>";
  oOut << "</tm_treeSettings>";
  oOut << "<tm_treeSettings sp=\"Subalpine_Fir\" tp=\"3\">";
  oOut << "<tm_floatCodes>";
  oOut << "<tm_floatCode label=\"X\">0</tm_floatCode>";
  oOut << "<tm_floatCode label=\"Y\">1</tm_floatCode>";
  oOut << "<tm_floatCode label=\"DBH\">3</tm_floatCode>";
  oOut << "<tm_floatCode label=\"Height\">2</tm_floatCode>";
  oOut << "</tm_floatCodes>";
  oOut << "</tm_treeSettings>";
  oOut << "<tm_treeSettings sp=\"Black_Cottonwood\" tp=\"3\">";
  oOut << "<tm_floatCodes>";
  oOut << "<tm_floatCode label=\"X\">0</tm_floatCode>";
  oOut << "<tm_floatCode label=\"Y\">1</tm_floatCode>";
  oOut << "<tm_floatCode label=\"DBH\">3</tm_floatCode>";
  oOut << "<tm_floatCode label=\"Height\">2</tm_floatCode>";
  oOut << "</tm_floatCodes>";
  oOut << "</tm_treeSettings>";
  oOut << "<tm_treeSettings sp=\"Trembling_Aspen\" tp=\"3\">";
  oOut << "<tm_floatCodes>";
  oOut << "<tm_floatCode label=\"X\">0</tm_floatCode>";
  oOut << "<tm_floatCode label=\"Y\">1</tm_floatCode>";
  oOut << "<tm_floatCode label=\"DBH\">3</tm_floatCode>";
  oOut << "<tm_floatCode label=\"Height\">2</tm_floatCode>";
  oOut << "</tm_floatCodes>";
  oOut << "</tm_treeSettings>";
  oOut << "<tm_treeSettings sp=\"Paper_Birch\" tp=\"3\">";
  oOut << "<tm_floatCodes>";
  oOut << "<tm_floatCode label=\"X\">0</tm_floatCode>";
  oOut << "<tm_floatCode label=\"Y\">1</tm_floatCode>";
  oOut << "<tm_floatCode label=\"DBH\">3</tm_floatCode>";
  oOut << "<tm_floatCode label=\"Height\">2</tm_floatCode>";
  oOut << "</tm_floatCodes>";
  oOut << "</tm_treeSettings>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">3.42407</fl>";
  oOut << "<fl c=\"1\">9.06982</fl>";
  oOut << "<fl c=\"3\">87.6663</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">2.67334</fl>";
  oOut << "<fl c=\"1\">43.0298</fl>";
  oOut << "<fl c=\"3\">81.6309</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">0.396729</fl>";
  oOut << "<fl c=\"1\">176.636</fl>";
  oOut << "<fl c=\"3\">92.9282</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">0.921631</fl>";
  oOut << "<fl c=\"1\">188.062</fl>";
  oOut << "<fl c=\"3\">42.6837</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">8.77686</fl>";
  oOut << "<fl c=\"1\">3.38745</fl>";
  oOut << "<fl c=\"3\">92.3648</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">10.0098</fl>";
  oOut << "<fl c=\"1\">0.476074</fl>";
  oOut << "<fl c=\"3\">62.9767</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">13.1226</fl>";
  oOut << "<fl c=\"1\">14.2883</fl>";
  oOut << "<fl c=\"3\">43.4238</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">10.4248</fl>";
  oOut << "<fl c=\"1\">23.0713</fl>";
  oOut << "<fl c=\"3\">72.4622</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">8.70972</fl>";
  oOut << "<fl c=\"1\">47.7356</fl>";
  oOut << "<fl c=\"3\">91.8393</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">14.4653</fl>";
  oOut << "<fl c=\"1\">47.7112</fl>";
  oOut << "<fl c=\"3\">33.2953</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">14.8376</fl>";
  oOut << "<fl c=\"1\">51.593</fl>";
  oOut << "<fl c=\"3\">83.3383</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">8.47778</fl>";
  oOut << "<fl c=\"1\">67.9626</fl>";
  oOut << "<fl c=\"3\">21.4218</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">13.3606</fl>";
  oOut << "<fl c=\"1\">77.1606</fl>";
  oOut << "<fl c=\"3\">63.4766</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">15.3503</fl>";
  oOut << "<fl c=\"1\">88.5803</fl>";
  oOut << "<fl c=\"3\">70.5411</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">13.9648</fl>";
  oOut << "<fl c=\"1\">90.4175</fl>";
  oOut << "<fl c=\"3\">53.9594</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">15.8386</fl>";
  oOut << "<fl c=\"1\">171.686</fl>";
  oOut << "<fl c=\"3\">20.455</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">18.8599</fl>";
  oOut << "<fl c=\"1\">15.4663</fl>";
  oOut << "<fl c=\"3\">44.364</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">20.5688</fl>";
  oOut << "<fl c=\"1\">15.2893</fl>";
  oOut << "<fl c=\"3\">21.0339</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"2\">";
  oOut << "<fl c=\"0\">20.8923</fl>";
  oOut << "<fl c=\"1\">10.6079</fl>";
  oOut << "<fl c=\"4\">5.31927</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">18.4998</fl>";
  oOut << "<fl c=\"1\">23.1384</fl>";
  oOut << "<fl c=\"3\">80.9995</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">18.5852</fl>";
  oOut << "<fl c=\"1\">20.9045</fl>";
  oOut << "<fl c=\"3\">22.1954</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">19.6045</fl>";
  oOut << "<fl c=\"1\">38.8428</fl>";
  oOut << "<fl c=\"3\">60.3818</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">19.1711</fl>";
  oOut << "<fl c=\"1\">61.3708</fl>";
  oOut << "<fl c=\"3\">39.2023</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">21.4417</fl>";
  oOut << "<fl c=\"1\">64.2395</fl>";
  oOut << "<fl c=\"3\">73.2111</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">18.0481</fl>";
  oOut << "<fl c=\"1\">108.502</fl>";
  oOut << "<fl c=\"3\">69.8529</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">19.2322</fl>";
  oOut << "<fl c=\"1\">109.54</fl>";
  oOut << "<fl c=\"3\">67.3825</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">19.7205</fl>";
  oOut << "<fl c=\"1\">118.402</fl>";
  oOut << "<fl c=\"3\">65.2399</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">16.4246</fl>";
  oOut << "<fl c=\"1\">177.063</fl>";
  oOut << "<fl c=\"3\">54.6234</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">27.3438</fl>";
  oOut << "<fl c=\"1\">54.4434</fl>";
  oOut << "<fl c=\"3\">20.8783</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">25.1343</fl>";
  oOut << "<fl c=\"1\">62.7686</fl>";
  oOut << "<fl c=\"3\">78.0664</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">31.0974</fl>";
  oOut << "<fl c=\"1\">74.9023</fl>";
  oOut << "<fl c=\"3\">50.864</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">27.5696</fl>";
  oOut << "<fl c=\"1\">84.9854</fl>";
  oOut << "<fl c=\"3\">88.9453</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">30.4688</fl>";
  oOut << "<fl c=\"1\">124.86</fl>";
  oOut << "<fl c=\"3\">61.4648</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">26.9531</fl>";
  oOut << "<fl c=\"1\">155.902</fl>";
  oOut << "<fl c=\"3\">61.7078</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">26.2146</fl>";
  oOut << "<fl c=\"1\">187.976</fl>";
  oOut << "<fl c=\"3\">18.653</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">36.0291</fl>";
  oOut << "<fl c=\"1\">1.00708</fl>";
  oOut << "<fl c=\"3\">29.4086</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"2\">";
  oOut << "<fl c=\"0\">39.5935</fl>";
  oOut << "<fl c=\"1\">14.3677</fl>";
  oOut << "<fl c=\"4\">5.76971</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">38.5132</fl>";
  oOut << "<fl c=\"1\">32.2754</fl>";
  oOut << "<fl c=\"3\">44.0454</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">36.3525</fl>";
  oOut << "<fl c=\"1\">48.4375</fl>";
  oOut << "<fl c=\"3\">17.3901</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">35.8521</fl>";
  oOut << "<fl c=\"1\">56.4209</fl>";
  oOut << "<fl c=\"3\">96.5445</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">34.3689</fl>";
  oOut << "<fl c=\"1\">56.2073</fl>";
  oOut << "<fl c=\"3\">73.2251</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">32.2937</fl>";
  oOut << "<fl c=\"1\">65.5823</fl>";
  oOut << "<fl c=\"3\">37.6617</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"2\">";
  oOut << "<fl c=\"0\">34.6008</fl>";
  oOut << "<fl c=\"1\">75.4761</fl>";
  oOut << "<fl c=\"4\">7.81317</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">35.0037</fl>";
  oOut << "<fl c=\"1\">137.585</fl>";
  oOut << "<fl c=\"3\">97.9401</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">33.9294</fl>";
  oOut << "<fl c=\"1\">151.782</fl>";
  oOut << "<fl c=\"3\">73.736</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">32.8979</fl>";
  oOut << "<fl c=\"1\">186.365</fl>";
  oOut << "<fl c=\"3\">12.1338</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">38.1958</fl>";
  oOut << "<fl c=\"1\">199.561</fl>";
  oOut << "<fl c=\"3\">25.9036</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"2\">";
  oOut << "<fl c=\"0\">45.2698</fl>";
  oOut << "<fl c=\"1\">12.9211</fl>";
  oOut << "<fl c=\"4\">0.679077</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">47.1863</fl>";
  oOut << "<fl c=\"1\">38.6719</fl>";
  oOut << "<fl c=\"3\">61.9406</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">46.2952</fl>";
  oOut << "<fl c=\"1\">44.9585</fl>";
  oOut << "<fl c=\"3\">30.1947</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">46.9604</fl>";
  oOut << "<fl c=\"1\">64.7156</fl>";
  oOut << "<fl c=\"3\">14.628</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"2\">";
  oOut << "<fl c=\"0\">43.2678</fl>";
  oOut << "<fl c=\"1\">101.447</fl>";
  oOut << "<fl c=\"4\">0.510437</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">44.7998</fl>";
  oOut << "<fl c=\"1\">111.505</fl>";
  oOut << "<fl c=\"3\">71.7853</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"2\">";
  oOut << "<fl c=\"0\">45.0439</fl>";
  oOut << "<fl c=\"1\">166.736</fl>";
  oOut << "<fl c=\"4\">7.69644</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">43.4265</fl>";
  oOut << "<fl c=\"1\">198.108</fl>";
  oOut << "<fl c=\"3\">65.1242</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">49.7803</fl>";
  oOut << "<fl c=\"1\">2.96021</fl>";
  oOut << "<fl c=\"3\">12.8821</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">52.6917</fl>";
  oOut << "<fl c=\"1\">36.6943</fl>";
  oOut << "<fl c=\"3\">15.704</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">51.5808</fl>";
  oOut << "<fl c=\"1\">51.0254</fl>";
  oOut << "<fl c=\"3\">17.1558</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">52.6001</fl>";
  oOut << "<fl c=\"1\">66.571</fl>";
  oOut << "<fl c=\"3\">95.2139</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">49.9573</fl>";
  oOut << "<fl c=\"1\">108.954</fl>";
  oOut << "<fl c=\"3\">82.2717</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">53.9246</fl>";
  oOut << "<fl c=\"1\">105.048</fl>";
  oOut << "<fl c=\"3\">63.9975</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">55.0781</fl>";
  oOut << "<fl c=\"1\">127.094</fl>";
  oOut << "<fl c=\"3\">23.291</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"2\">";
  oOut << "<fl c=\"0\">55.2551</fl>";
  oOut << "<fl c=\"1\">152.972</fl>";
  oOut << "<fl c=\"4\">0.990845</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">51.4587</fl>";
  oOut << "<fl c=\"1\">190.485</fl>";
  oOut << "<fl c=\"3\">99.0073</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"2\">";
  oOut << "<fl c=\"0\">58.9783</fl>";
  oOut << "<fl c=\"1\">10.2295</fl>";
  oOut << "<fl c=\"4\">0.538544</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"2\">";
  oOut << "<fl c=\"0\">61.7432</fl>";
  oOut << "<fl c=\"1\">78.9673</fl>";
  oOut << "<fl c=\"4\">0.158295</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"2\">";
  oOut << "<fl c=\"0\">58.252</fl>";
  oOut << "<fl c=\"1\">145.276</fl>";
  oOut << "<fl c=\"4\">2.91025</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"2\">";
  oOut << "<fl c=\"0\">63.2019</fl>";
  oOut << "<fl c=\"1\">153.76</fl>";
  oOut << "<fl c=\"4\">6.18527</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">56.4697</fl>";
  oOut << "<fl c=\"1\">167.139</fl>";
  oOut << "<fl c=\"3\">46.4163</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">57.7698</fl>";
  oOut << "<fl c=\"1\">193.115</fl>";
  oOut << "<fl c=\"3\">32.3907</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">69.2688</fl>";
  oOut << "<fl c=\"1\">27.8687</fl>";
  oOut << "<fl c=\"3\">61.0422</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">64.801</fl>";
  oOut << "<fl c=\"1\">51.4954</fl>";
  oOut << "<fl c=\"3\">78.6328</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">67.3279</fl>";
  oOut << "<fl c=\"1\">71.0266</fl>";
  oOut << "<fl c=\"3\">98.9053</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"2\">";
  oOut << "<fl c=\"0\">71.8506</fl>";
  oOut << "<fl c=\"1\">99.0906</fl>";
  oOut << "<fl c=\"4\">0.863373</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"2\">";
  oOut << "<fl c=\"0\">68.7256</fl>";
  oOut << "<fl c=\"1\">115.643</fl>";
  oOut << "<fl c=\"4\">0.467133</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">64.2212</fl>";
  oOut << "<fl c=\"1\">136.005</fl>";
  oOut << "<fl c=\"3\">80.2924</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">65.3931</fl>";
  oOut << "<fl c=\"1\">161.188</fl>";
  oOut << "<fl c=\"3\">78.5556</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">65.5701</fl>";
  oOut << "<fl c=\"1\">179.73</fl>";
  oOut << "<fl c=\"3\">72.6215</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">67.9504</fl>";
  oOut << "<fl c=\"1\">186.249</fl>";
  oOut << "<fl c=\"3\">58.2043</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">78.0334</fl>";
  oOut << "<fl c=\"1\">19.0735</fl>";
  oOut << "<fl c=\"3\">95.1352</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">72.5342</fl>";
  oOut << "<fl c=\"1\">30.4565</fl>";
  oOut << "<fl c=\"3\">44.3671</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">77.7161</fl>";
  oOut << "<fl c=\"1\">66.2415</fl>";
  oOut << "<fl c=\"3\">40.2771</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">73.6694</fl>";
  oOut << "<fl c=\"1\">82.605</fl>";
  oOut << "<fl c=\"3\">49.3393</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">76.8799</fl>";
  oOut << "<fl c=\"1\">85.5164</fl>";
  oOut << "<fl c=\"3\">23.7366</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">77.6489</fl>";
  oOut << "<fl c=\"1\">114.331</fl>";
  oOut << "<fl c=\"3\">95.8426</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">76.7944</fl>";
  oOut << "<fl c=\"1\">114.923</fl>";
  oOut << "<fl c=\"3\">31.1172</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"2\">";
  oOut << "<fl c=\"0\">74.4629</fl>";
  oOut << "<fl c=\"1\">169.391</fl>";
  oOut << "<fl c=\"4\">0.472229</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">86.322</fl>";
  oOut << "<fl c=\"1\">11.4441</fl>";
  oOut << "<fl c=\"3\">57.9987</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">87.5305</fl>";
  oOut << "<fl c=\"1\">47.4609</fl>";
  oOut << "<fl c=\"3\">99.6683</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">81.543</fl>";
  oOut << "<fl c=\"1\">50.0549</fl>";
  oOut << "<fl c=\"3\">95.5505</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">85.6384</fl>";
  oOut << "<fl c=\"1\">78.4729</fl>";
  oOut << "<fl c=\"3\">86.7651</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">87.9333</fl>";
  oOut << "<fl c=\"1\">72.1924</fl>";
  oOut << "<fl c=\"3\">31.9543</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">82.428</fl>";
  oOut << "<fl c=\"1\">74.7192</fl>";
  oOut << "<fl c=\"3\">18.3057</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"2\">";
  oOut << "<fl c=\"0\">83.0872</fl>";
  oOut << "<fl c=\"1\">74.7437</fl>";
  oOut << "<fl c=\"4\">0.657288</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">83.6548</fl>";
  oOut << "<fl c=\"1\">104.919</fl>";
  oOut << "<fl c=\"3\">40.8444</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">81.4087</fl>";
  oOut << "<fl c=\"1\">135.193</fl>";
  oOut << "<fl c=\"3\">51.5662</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"2\">";
  oOut << "<fl c=\"0\">87.3291</fl>";
  oOut << "<fl c=\"1\">169.293</fl>";
  oOut << "<fl c=\"4\">0.264435</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">91.449</fl>";
  oOut << "<fl c=\"1\">6.62231</fl>";
  oOut << "<fl c=\"3\">56.5002</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">94.8486</fl>";
  oOut << "<fl c=\"1\">1.94092</fl>";
  oOut << "<fl c=\"3\">37.352</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">88.5864</fl>";
  oOut << "<fl c=\"1\">46.0693</fl>";
  oOut << "<fl c=\"3\">79.855</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">94.635</fl>";
  oOut << "<fl c=\"1\">61.8286</fl>";
  oOut << "<fl c=\"3\">17.0517</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">89.9597</fl>";
  oOut << "<fl c=\"1\">78.363</fl>";
  oOut << "<fl c=\"3\">81.8759</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">89.4897</fl>";
  oOut << "<fl c=\"1\">75.9338</fl>";
  oOut << "<fl c=\"3\">70.7556</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">94.8364</fl>";
  oOut << "<fl c=\"1\">156.635</fl>";
  oOut << "<fl c=\"3\">53.7976</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">91.6077</fl>";
  oOut << "<fl c=\"1\">164.447</fl>";
  oOut << "<fl c=\"3\">26.1591</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">88.2751</fl>";
  oOut << "<fl c=\"1\">176.111</fl>";
  oOut << "<fl c=\"3\">95.7474</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"2\">";
  oOut << "<fl c=\"0\">101.288</fl>";
  oOut << "<fl c=\"1\">38.9648</fl>";
  oOut << "<fl c=\"4\">0.53653</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">98.5168</fl>";
  oOut << "<fl c=\"1\">43.5486</fl>";
  oOut << "<fl c=\"3\">22.9327</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">101.447</fl>";
  oOut << "<fl c=\"1\">77.1729</fl>";
  oOut << "<fl c=\"3\">70.8121</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">103.943</fl>";
  oOut << "<fl c=\"1\">93.4204</fl>";
  oOut << "<fl c=\"3\">24.368</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">102.051</fl>";
  oOut << "<fl c=\"1\">109.497</fl>";
  oOut << "<fl c=\"3\">52.4631</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">97.8333</fl>";
  oOut << "<fl c=\"1\">126.642</fl>";
  oOut << "<fl c=\"3\">99.7113</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">101.007</fl>";
  oOut << "<fl c=\"1\">120.526</fl>";
  oOut << "<fl c=\"3\">98.7943</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">103.9</fl>";
  oOut << "<fl c=\"1\">132.855</fl>";
  oOut << "<fl c=\"3\">52.3502</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">101.831</fl>";
  oOut << "<fl c=\"1\">167.291</fl>";
  oOut << "<fl c=\"3\">70.1239</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">100.006</fl>";
  oOut << "<fl c=\"1\">173.853</fl>";
  oOut << "<fl c=\"3\">88.8937</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"2\">";
  oOut << "<fl c=\"0\">96.9482</fl>";
  oOut << "<fl c=\"1\">194.91</fl>";
  oOut << "<fl c=\"4\">8.67285</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">108.649</fl>";
  oOut << "<fl c=\"1\">2.20947</fl>";
  oOut << "<fl c=\"3\">80.6494</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"2\">";
  oOut << "<fl c=\"0\">104.987</fl>";
  oOut << "<fl c=\"1\">3.17993</fl>";
  oOut << "<fl c=\"4\">0.350769</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">111.89</fl>";
  oOut << "<fl c=\"1\">25.5493</fl>";
  oOut << "<fl c=\"3\">29.2926</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"2\">";
  oOut << "<fl c=\"0\">110.254</fl>";
  oOut << "<fl c=\"1\">31.5369</fl>";
  oOut << "<fl c=\"4\">7.39542</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"2\">";
  oOut << "<fl c=\"0\">110.284</fl>";
  oOut << "<fl c=\"1\">29.1565</fl>";
  oOut << "<fl c=\"4\">4.13989</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">107.495</fl>";
  oOut << "<fl c=\"1\">42.4377</fl>";
  oOut << "<fl c=\"3\">64.0396</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">106.378</fl>";
  oOut << "<fl c=\"1\">90.6311</fl>";
  oOut << "<fl c=\"3\">12.612</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">109.131</fl>";
  oOut << "<fl c=\"1\">136.359</fl>";
  oOut << "<fl c=\"3\">18.0768</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">108.575</fl>";
  oOut << "<fl c=\"1\">172.308</fl>";
  oOut << "<fl c=\"3\">99.0091</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">110.925</fl>";
  oOut << "<fl c=\"1\">172.809</fl>";
  oOut << "<fl c=\"3\">83.9792</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">112.189</fl>";
  oOut << "<fl c=\"1\">20.3796</fl>";
  oOut << "<fl c=\"3\">33.1494</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">112.299</fl>";
  oOut << "<fl c=\"1\">46.7957</fl>";
  oOut << "<fl c=\"3\">84.6988</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">116.492</fl>";
  oOut << "<fl c=\"1\">99.6582</fl>";
  oOut << "<fl c=\"3\">54.7275</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">113.947</fl>";
  oOut << "<fl c=\"1\">97.052</fl>";
  oOut << "<fl c=\"3\">21.94</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"2\">";
  oOut << "<fl c=\"0\">117.633</fl>";
  oOut << "<fl c=\"1\">111.108</fl>";
  oOut << "<fl c=\"4\">7.25671</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">112.61</fl>";
  oOut << "<fl c=\"1\">139.526</fl>";
  oOut << "<fl c=\"3\">16.2943</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">118.506</fl>";
  oOut << "<fl c=\"1\">150.482</fl>";
  oOut << "<fl c=\"3\">89.884</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">116.18</fl>";
  oOut << "<fl c=\"1\">177.57</fl>";
  oOut << "<fl c=\"3\">19.8331</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">116.486</fl>";
  oOut << "<fl c=\"1\">193.408</fl>";
  oOut << "<fl c=\"3\">10.9738</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">122.247</fl>";
  oOut << "<fl c=\"1\">4.82178</fl>";
  oOut << "<fl c=\"3\">59.527</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">124.036</fl>";
  oOut << "<fl c=\"1\">17.4194</fl>";
  oOut << "<fl c=\"3\">77.4832</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">126.721</fl>";
  oOut << "<fl c=\"1\">27.9663</fl>";
  oOut << "<fl c=\"3\">55.1169</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"2\">";
  oOut << "<fl c=\"0\">125.366</fl>";
  oOut << "<fl c=\"1\">39.9475</fl>";
  oOut << "<fl c=\"4\">0.0650024</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">127.393</fl>";
  oOut << "<fl c=\"1\">71.2341</fl>";
  oOut << "<fl c=\"3\">85.275</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">125.177</fl>";
  oOut << "<fl c=\"1\">127.399</fl>";
  oOut << "<fl c=\"3\">71.4639</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">120.453</fl>";
  oOut << "<fl c=\"1\">124.731</fl>";
  oOut << "<fl c=\"3\">39.0875</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"2\">";
  oOut << "<fl c=\"0\">127.295</fl>";
  oOut << "<fl c=\"1\">123.126</fl>";
  oOut << "<fl c=\"4\">8.56546</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">124.036</fl>";
  oOut << "<fl c=\"1\">145.728</fl>";
  oOut << "<fl c=\"3\">30.5359</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">123.407</fl>";
  oOut << "<fl c=\"1\">152.02</fl>";
  oOut << "<fl c=\"3\">92.7948</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">135.364</fl>";
  oOut << "<fl c=\"1\">119.525</fl>";
  oOut << "<fl c=\"3\">76.3019</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">131.403</fl>";
  oOut << "<fl c=\"1\">184.003</fl>";
  oOut << "<fl c=\"3\">19.9683</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"2\">";
  oOut << "<fl c=\"0\">135.852</fl>";
  oOut << "<fl c=\"1\">186.719</fl>";
  oOut << "<fl c=\"4\">4.71365</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">141.443</fl>";
  oOut << "<fl c=\"1\">2.7771</fl>";
  oOut << "<fl c=\"3\">19.3518</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">136.334</fl>";
  oOut << "<fl c=\"1\">37.5732</fl>";
  oOut << "<fl c=\"3\">38.1079</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">142.322</fl>";
  oOut << "<fl c=\"1\">80.3406</fl>";
  oOut << "<fl c=\"3\">40.6247</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">141.351</fl>";
  oOut << "<fl c=\"1\">122.467</fl>";
  oOut << "<fl c=\"3\">86.1481</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">136.09</fl>";
  oOut << "<fl c=\"1\">125.092</fl>";
  oOut << "<fl c=\"3\">30.4562</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">140.668</fl>";
  oOut << "<fl c=\"1\">136.847</fl>";
  oOut << "<fl c=\"3\">57.818</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">137.891</fl>";
  oOut << "<fl c=\"1\">155.591</fl>";
  oOut << "<fl c=\"3\">36.7157</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">150.024</fl>";
  oOut << "<fl c=\"1\">12.9395</fl>";
  oOut << "<fl c=\"3\">49.5807</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">151.324</fl>";
  oOut << "<fl c=\"1\">62.3413</fl>";
  oOut << "<fl c=\"3\">43.9578</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"2\">";
  oOut << "<fl c=\"0\">151.453</fl>";
  oOut << "<fl c=\"1\">60.4126</fl>";
  oOut << "<fl c=\"4\">4.65955</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">150.787</fl>";
  oOut << "<fl c=\"1\">71.405</fl>";
  oOut << "<fl c=\"3\">98.0505</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">145.709</fl>";
  oOut << "<fl c=\"1\">113.123</fl>";
  oOut << "<fl c=\"3\">15.058</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"2\">";
  oOut << "<fl c=\"0\">147.491</fl>";
  oOut << "<fl c=\"1\">126.959</fl>";
  oOut << "<fl c=\"4\">0.817596</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">148.053</fl>";
  oOut << "<fl c=\"1\">133.557</fl>";
  oOut << "<fl c=\"3\">29.0634</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">145.99</fl>";
  oOut << "<fl c=\"1\">193.219</fl>";
  oOut << "<fl c=\"3\">48.9117</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">159.076</fl>";
  oOut << "<fl c=\"1\">7.49512</fl>";
  oOut << "<fl c=\"3\">37.03</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"2\">";
  oOut << "<fl c=\"0\">157.703</fl>";
  oOut << "<fl c=\"1\">2.66724</fl>";
  oOut << "<fl c=\"4\">6.38824</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">157.281</fl>";
  oOut << "<fl c=\"1\">12.9456</fl>";
  oOut << "<fl c=\"3\">34.2416</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"2\">";
  oOut << "<fl c=\"0\">156.311</fl>";
  oOut << "<fl c=\"1\">64.3677</fl>";
  oOut << "<fl c=\"4\">0.163361</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">154.639</fl>";
  oOut << "<fl c=\"1\">82.428</fl>";
  oOut << "<fl c=\"3\">21.6125</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">159.906</fl>";
  oOut << "<fl c=\"1\">94.1833</fl>";
  oOut << "<fl c=\"3\">83.3768</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">159.357</fl>";
  oOut << "<fl c=\"1\">93.3228</fl>";
  oOut << "<fl c=\"3\">39.1547</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"2\">";
  oOut << "<fl c=\"0\">152.875</fl>";
  oOut << "<fl c=\"1\">118.848</fl>";
  oOut << "<fl c=\"4\">0.0100708</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">158.795</fl>";
  oOut << "<fl c=\"1\">120.374</fl>";
  oOut << "<fl c=\"3\">46.8307</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">154.163</fl>";
  oOut << "<fl c=\"1\">144.855</fl>";
  oOut << "<fl c=\"3\">15.8466</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">166.919</fl>";
  oOut << "<fl c=\"1\">13.9343</fl>";
  oOut << "<fl c=\"3\">58.4793</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">165.137</fl>";
  oOut << "<fl c=\"1\">80.3711</fl>";
  oOut << "<fl c=\"3\">63.1146</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"2\">";
  oOut << "<fl c=\"0\">164.062</fl>";
  oOut << "<fl c=\"1\">90.7227</fl>";
  oOut << "<fl c=\"4\">0.16925</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">162.347</fl>";
  oOut << "<fl c=\"1\">98.1262</fl>";
  oOut << "<fl c=\"3\">45.5057</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">165.729</fl>";
  oOut << "<fl c=\"1\">133.893</fl>";
  oOut << "<fl c=\"3\">29.0118</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">165.436</fl>";
  oOut << "<fl c=\"1\">150.183</fl>";
  oOut << "<fl c=\"3\">43.2315</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">160.974</fl>";
  oOut << "<fl c=\"1\">186.908</fl>";
  oOut << "<fl c=\"3\">36.0547</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">167.578</fl>";
  oOut << "<fl c=\"1\">195.734</fl>";
  oOut << "<fl c=\"3\">80.3046</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">166.553</fl>";
  oOut << "<fl c=\"1\">193.732</fl>";
  oOut << "<fl c=\"3\">50.2228</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">173.944</fl>";
  oOut << "<fl c=\"1\">4.42505</fl>";
  oOut << "<fl c=\"3\">61.8021</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">175.385</fl>";
  oOut << "<fl c=\"1\">5.40161</fl>";
  oOut << "<fl c=\"3\">47.6099</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">175.061</fl>";
  oOut << "<fl c=\"1\">21.2585</fl>";
  oOut << "<fl c=\"3\">78.5895</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">170.825</fl>";
  oOut << "<fl c=\"1\">20.7703</fl>";
  oOut << "<fl c=\"3\">29.0045</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">173.602</fl>";
  oOut << "<fl c=\"1\">50.946</fl>";
  oOut << "<fl c=\"3\">87.3563</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"2\">";
  oOut << "<fl c=\"0\">170.459</fl>";
  oOut << "<fl c=\"1\">50.4333</fl>";
  oOut << "<fl c=\"4\">9.54105</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"2\">";
  oOut << "<fl c=\"0\">174.658</fl>";
  oOut << "<fl c=\"1\">66.0217</fl>";
  oOut << "<fl c=\"4\">4.15335</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">175.073</fl>";
  oOut << "<fl c=\"1\">88.2996</fl>";
  oOut << "<fl c=\"3\">75.5145</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">174.097</fl>";
  oOut << "<fl c=\"1\">111.536</fl>";
  oOut << "<fl c=\"3\">57.1103</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">169.788</fl>";
  oOut << "<fl c=\"1\">113.586</fl>";
  oOut << "<fl c=\"3\">59.0573</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">174.298</fl>";
  oOut << "<fl c=\"1\">121.887</fl>";
  oOut << "<fl c=\"3\">61.9659</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">168.384</fl>";
  oOut << "<fl c=\"1\">155.005</fl>";
  oOut << "<fl c=\"3\">42.8427</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">172.986</fl>";
  oOut << "<fl c=\"1\">154.852</fl>";
  oOut << "<fl c=\"3\">14.9524</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">168.658</fl>";
  oOut << "<fl c=\"1\">197.418</fl>";
  oOut << "<fl c=\"3\">65.2808</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"2\">";
  oOut << "<fl c=\"0\">179.285</fl>";
  oOut << "<fl c=\"1\">36.8896</fl>";
  oOut << "<fl c=\"4\">5.61646</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">176.855</fl>";
  oOut << "<fl c=\"1\">47.522</fl>";
  oOut << "<fl c=\"3\">12.2195</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">183.734</fl>";
  oOut << "<fl c=\"1\">86.7798</fl>";
  oOut << "<fl c=\"3\">53.5681</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">182.782</fl>";
  oOut << "<fl c=\"1\">143.738</fl>";
  oOut << "<fl c=\"3\">46.3022</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"2\">";
  oOut << "<fl c=\"0\">177.435</fl>";
  oOut << "<fl c=\"1\">154.828</fl>";
  oOut << "<fl c=\"4\">4.55161</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">181.885</fl>";
  oOut << "<fl c=\"1\">165.039</fl>";
  oOut << "<fl c=\"3\">68.125</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"2\">";
  oOut << "<fl c=\"0\">178.912</fl>";
  oOut << "<fl c=\"1\">192.242</fl>";
  oOut << "<fl c=\"4\">9.4397</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"2\">";
  oOut << "<fl c=\"0\">191.876</fl>";
  oOut << "<fl c=\"1\">14.5325</fl>";
  oOut << "<fl c=\"4\">0.350891</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">186.017</fl>";
  oOut << "<fl c=\"1\">69.22</fl>";
  oOut << "<fl c=\"3\">32.8851</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">187.75</fl>";
  oOut << "<fl c=\"1\">88.2446</fl>";
  oOut << "<fl c=\"3\">28.0832</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">187.897</fl>";
  oOut << "<fl c=\"1\">129.346</fl>";
  oOut << "<fl c=\"3\">97.7689</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">186.31</fl>";
  oOut << "<fl c=\"1\">157.55</fl>";
  oOut << "<fl c=\"3\">90.0214</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">187.006</fl>";
  oOut << "<fl c=\"1\">173.682</fl>";
  oOut << "<fl c=\"3\">68.1628</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">195.209</fl>";
  oOut << "<fl c=\"1\">70.3125</fl>";
  oOut << "<fl c=\"3\">57.2473</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"2\">";
  oOut << "<fl c=\"0\">199.994</fl>";
  oOut << "<fl c=\"1\">71.4294</fl>";
  oOut << "<fl c=\"4\">0.686798</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"2\">";
  oOut << "<fl c=\"0\">195.99</fl>";
  oOut << "<fl c=\"1\">73.5718</fl>";
  oOut << "<fl c=\"4\">6.09573</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">195.477</fl>";
  oOut << "<fl c=\"1\">108.527</fl>";
  oOut << "<fl c=\"3\">89.9194</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">195.166</fl>";
  oOut << "<fl c=\"1\">109.32</fl>";
  oOut << "<fl c=\"3\">79.4427</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">197.443</fl>";
  oOut << "<fl c=\"1\">120.703</fl>";
  oOut << "<fl c=\"3\">38.8083</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"2\">";
  oOut << "<fl c=\"0\">192.102</fl>";
  oOut << "<fl c=\"1\">137.518</fl>";
  oOut << "<fl c=\"4\">0.251312</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">199.982</fl>";
  oOut << "<fl c=\"1\">155.444</fl>";
  oOut << "<fl c=\"3\">65.1321</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">193.225</fl>";
  oOut << "<fl c=\"1\">162.28</fl>";
  oOut << "<fl c=\"3\">47.923</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"8\" tp=\"3\">";
  oOut << "<fl c=\"0\">194.415</fl>";
  oOut << "<fl c=\"1\">180.652</fl>";
  oOut << "<fl c=\"3\">25.5243</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">3.4729</fl>";
  oOut << "<fl c=\"1\">9.44214</fl>";
  oOut << "<fl c=\"3\">43.8516</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">0.0244141</fl>";
  oOut << "<fl c=\"1\">18.6401</fl>";
  oOut << "<fl c=\"3\">68.8135</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">7.06177</fl>";
  oOut << "<fl c=\"1\">28.0029</fl>";
  oOut << "<fl c=\"3\">30.098</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">1.37939</fl>";
  oOut << "<fl c=\"1\">39.3188</fl>";
  oOut << "<fl c=\"3\">78.4293</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"2\">";
  oOut << "<fl c=\"0\">4.90112</fl>";
  oOut << "<fl c=\"1\">105.084</fl>";
  oOut << "<fl c=\"4\">0.608093</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"2\">";
  oOut << "<fl c=\"0\">6.5979</fl>";
  oOut << "<fl c=\"1\">115.466</fl>";
  oOut << "<fl c=\"4\">5.32532</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">1.83716</fl>";
  oOut << "<fl c=\"1\">124.689</fl>";
  oOut << "<fl c=\"3\">91.1108</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"2\">";
  oOut << "<fl c=\"0\">4.24194</fl>";
  oOut << "<fl c=\"1\">129.846</fl>";
  oOut << "<fl c=\"4\">8.0274</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">6.90308</fl>";
  oOut << "<fl c=\"1\">164.758</fl>";
  oOut << "<fl c=\"3\">50.6992</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">5.3772</fl>";
  oOut << "<fl c=\"1\">173.944</fl>";
  oOut << "<fl c=\"3\">59.5526</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">8.42285</fl>";
  oOut << "<fl c=\"1\">22.8088</fl>";
  oOut << "<fl c=\"3\">50.7578</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">11.2488</fl>";
  oOut << "<fl c=\"1\">29.4983</fl>";
  oOut << "<fl c=\"3\">89.8361</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">8.69751</fl>";
  oOut << "<fl c=\"1\">61.4624</fl>";
  oOut << "<fl c=\"3\">47.056</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"2\">";
  oOut << "<fl c=\"0\">14.5203</fl>";
  oOut << "<fl c=\"1\">60.9131</fl>";
  oOut << "<fl c=\"4\">0.545288</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">10.5713</fl>";
  oOut << "<fl c=\"1\">79.6814</fl>";
  oOut << "<fl c=\"3\">36.2888</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">13.1836</fl>";
  oOut << "<fl c=\"1\">92.5842</fl>";
  oOut << "<fl c=\"3\">40.4242</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">13.7634</fl>";
  oOut << "<fl c=\"1\">119.843</fl>";
  oOut << "<fl c=\"3\">18.8617</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">15.5212</fl>";
  oOut << "<fl c=\"1\">134.308</fl>";
  oOut << "<fl c=\"3\">86.662</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">8.11157</fl>";
  oOut << "<fl c=\"1\">194.94</fl>";
  oOut << "<fl c=\"3\">49.8187</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"2\">";
  oOut << "<fl c=\"0\">20.5322</fl>";
  oOut << "<fl c=\"1\">7.1228</fl>";
  oOut << "<fl c=\"4\">1.69516</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">21.3806</fl>";
  oOut << "<fl c=\"1\">44.5496</fl>";
  oOut << "<fl c=\"3\">86.9843</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">22.7234</fl>";
  oOut << "<fl c=\"1\">54.9805</fl>";
  oOut << "<fl c=\"3\">91.752</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">16.5222</fl>";
  oOut << "<fl c=\"1\">107.257</fl>";
  oOut << "<fl c=\"3\">30.6522</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"2\">";
  oOut << "<fl c=\"0\">27.9236</fl>";
  oOut << "<fl c=\"1\">1.36719</fl>";
  oOut << "<fl c=\"4\">1.17688</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">26.8921</fl>";
  oOut << "<fl c=\"1\">29.7913</fl>";
  oOut << "<fl c=\"3\">74.8138</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"2\">";
  oOut << "<fl c=\"0\">25.6775</fl>";
  oOut << "<fl c=\"1\">39.8132</fl>";
  oOut << "<fl c=\"4\">0.0961609</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">25.1648</fl>";
  oOut << "<fl c=\"1\">51.825</fl>";
  oOut << "<fl c=\"3\">31.4819</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">29.2725</fl>";
  oOut << "<fl c=\"1\">69.6411</fl>";
  oOut << "<fl c=\"3\">81.4853</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">26.8005</fl>";
  oOut << "<fl c=\"1\">78.6072</fl>";
  oOut << "<fl c=\"3\">58.0719</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">25.6531</fl>";
  oOut << "<fl c=\"1\">98.3643</fl>";
  oOut << "<fl c=\"3\">13.9066</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">24.8413</fl>";
  oOut << "<fl c=\"1\">160.016</fl>";
  oOut << "<fl c=\"3\">23.8184</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">31.9702</fl>";
  oOut << "<fl c=\"1\">174.127</fl>";
  oOut << "<fl c=\"3\">18.79</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">24.2249</fl>";
  oOut << "<fl c=\"1\">180.219</fl>";
  oOut << "<fl c=\"3\">96.264</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">30.3223</fl>";
  oOut << "<fl c=\"1\">190.948</fl>";
  oOut << "<fl c=\"3\">79.5135</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">31.2378</fl>";
  oOut << "<fl c=\"1\">185.699</fl>";
  oOut << "<fl c=\"3\">55.3168</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">38.6963</fl>";
  oOut << "<fl c=\"1\">14.856</fl>";
  oOut << "<fl c=\"3\">30.4977</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">33.9539</fl>";
  oOut << "<fl c=\"1\">17.0532</fl>";
  oOut << "<fl c=\"3\">54.491</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">35.0342</fl>";
  oOut << "<fl c=\"1\">84.4238</fl>";
  oOut << "<fl c=\"3\">72.3129</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">37.9211</fl>";
  oOut << "<fl c=\"1\">108.337</fl>";
  oOut << "<fl c=\"3\">88.2846</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">39.3066</fl>";
  oOut << "<fl c=\"1\">143.207</fl>";
  oOut << "<fl c=\"3\">83.2541</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">33.9661</fl>";
  oOut << "<fl c=\"1\">156.934</fl>";
  oOut << "<fl c=\"3\">24.2712</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"2\">";
  oOut << "<fl c=\"0\">33.9478</fl>";
  oOut << "<fl c=\"1\">156.75</fl>";
  oOut << "<fl c=\"4\">0.460266</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">43.6218</fl>";
  oOut << "<fl c=\"1\">2.59399</fl>";
  oOut << "<fl c=\"3\">40.5328</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">45.6909</fl>";
  oOut << "<fl c=\"1\">28.064</fl>";
  oOut << "<fl c=\"3\">82.8751</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">47.5769</fl>";
  oOut << "<fl c=\"1\">36.0168</fl>";
  oOut << "<fl c=\"3\">10.9082</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">40.4724</fl>";
  oOut << "<fl c=\"1\">115.601</fl>";
  oOut << "<fl c=\"3\">69.4885</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">44.3481</fl>";
  oOut << "<fl c=\"1\">146.716</fl>";
  oOut << "<fl c=\"3\">25.7391</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">42.5964</fl>";
  oOut << "<fl c=\"1\">190.039</fl>";
  oOut << "<fl c=\"3\">35.3036</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"2\">";
  oOut << "<fl c=\"0\">44.5557</fl>";
  oOut << "<fl c=\"1\">191.833</fl>";
  oOut << "<fl c=\"4\">9.14581</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">52.8687</fl>";
  oOut << "<fl c=\"1\">18.2678</fl>";
  oOut << "<fl c=\"3\">58.0887</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">52.0325</fl>";
  oOut << "<fl c=\"1\">50.9949</fl>";
  oOut << "<fl c=\"3\">33.0844</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">52.771</fl>";
  oOut << "<fl c=\"1\">61.1816</fl>";
  oOut << "<fl c=\"3\">36.8259</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"2\">";
  oOut << "<fl c=\"0\">55.5359</fl>";
  oOut << "<fl c=\"1\">73.0652</fl>";
  oOut << "<fl c=\"4\">0.0194702</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">55.3894</fl>";
  oOut << "<fl c=\"1\">98.1201</fl>";
  oOut << "<fl c=\"3\">87.6941</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">55.2368</fl>";
  oOut << "<fl c=\"1\">113.629</fl>";
  oOut << "<fl c=\"3\">62.5677</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">50.8118</fl>";
  oOut << "<fl c=\"1\">121.942</fl>";
  oOut << "<fl c=\"3\">89.3826</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">53.6804</fl>";
  oOut << "<fl c=\"1\">147.443</fl>";
  oOut << "<fl c=\"3\">47.1579</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"2\">";
  oOut << "<fl c=\"0\">49.0234</fl>";
  oOut << "<fl c=\"1\">150.153</fl>";
  oOut << "<fl c=\"4\">5.52142</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">51.3794</fl>";
  oOut << "<fl c=\"1\">174.731</fl>";
  oOut << "<fl c=\"3\">19.9167</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">57.7148</fl>";
  oOut << "<fl c=\"1\">2.64893</fl>";
  oOut << "<fl c=\"3\">68.8913</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">59.8633</fl>";
  oOut << "<fl c=\"1\">30.4321</fl>";
  oOut << "<fl c=\"3\">96.6269</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">59.4421</fl>";
  oOut << "<fl c=\"1\">52.5879</fl>";
  oOut << "<fl c=\"3\">23.4549</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">60.6018</fl>";
  oOut << "<fl c=\"1\">56.8909</fl>";
  oOut << "<fl c=\"3\">88.7622</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">58.5144</fl>";
  oOut << "<fl c=\"1\">85.9375</fl>";
  oOut << "<fl c=\"3\">31.4279</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">56.8665</fl>";
  oOut << "<fl c=\"1\">95.1294</fl>";
  oOut << "<fl c=\"3\">99.6863</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">60.2722</fl>";
  oOut << "<fl c=\"1\">183.759</fl>";
  oOut << "<fl c=\"3\">20.611</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">65.3259</fl>";
  oOut << "<fl c=\"1\">42.749</fl>";
  oOut << "<fl c=\"3\">49.8642</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"2\">";
  oOut << "<fl c=\"0\">65.9119</fl>";
  oOut << "<fl c=\"1\">42.3889</fl>";
  oOut << "<fl c=\"4\">0.073761</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">67.6147</fl>";
  oOut << "<fl c=\"1\">70.4224</fl>";
  oOut << "<fl c=\"3\">60.7648</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">67.9443</fl>";
  oOut << "<fl c=\"1\">85.4553</fl>";
  oOut << "<fl c=\"3\">12.1933</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">69.3848</fl>";
  oOut << "<fl c=\"1\">106.921</fl>";
  oOut << "<fl c=\"3\">84.9411</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">68.5852</fl>";
  oOut << "<fl c=\"1\">105.817</fl>";
  oOut << "<fl c=\"3\">15.0159</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">71.8811</fl>";
  oOut << "<fl c=\"1\">117.328</fl>";
  oOut << "<fl c=\"3\">57.8305</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">66.4551</fl>";
  oOut << "<fl c=\"1\">127.557</fl>";
  oOut << "<fl c=\"3\">69.3808</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">67.9443</fl>";
  oOut << "<fl c=\"1\">122.455</fl>";
  oOut << "<fl c=\"3\">61.4359</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">64.1296</fl>";
  oOut << "<fl c=\"1\">165.198</fl>";
  oOut << "<fl c=\"3\">74.4772</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">66.8579</fl>";
  oOut << "<fl c=\"1\">165.387</fl>";
  oOut << "<fl c=\"3\">27.8409</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">67.6025</fl>";
  oOut << "<fl c=\"1\">175.391</fl>";
  oOut << "<fl c=\"3\">28.0981</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">64.4958</fl>";
  oOut << "<fl c=\"1\">181.256</fl>";
  oOut << "<fl c=\"3\">11.1826</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">65.2161</fl>";
  oOut << "<fl c=\"1\">184.155</fl>";
  oOut << "<fl c=\"3\">10.6464</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">69.7815</fl>";
  oOut << "<fl c=\"1\">193.97</fl>";
  oOut << "<fl c=\"3\">53.4381</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">79.6631</fl>";
  oOut << "<fl c=\"1\">17.5537</fl>";
  oOut << "<fl c=\"3\">37.2897</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">77.8503</fl>";
  oOut << "<fl c=\"1\">25.7507</fl>";
  oOut << "<fl c=\"3\">80.9933</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">72.1252</fl>";
  oOut << "<fl c=\"1\">38.3667</fl>";
  oOut << "<fl c=\"3\">50.9372</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"2\">";
  oOut << "<fl c=\"0\">74.3774</fl>";
  oOut << "<fl c=\"1\">74.4324</fl>";
  oOut << "<fl c=\"4\">0.927856</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">79.0283</fl>";
  oOut << "<fl c=\"1\">81.2012</fl>";
  oOut << "<fl c=\"3\">28.3112</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">78.6987</fl>";
  oOut << "<fl c=\"1\">96.2219</fl>";
  oOut << "<fl c=\"3\">36.4972</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">74.054</fl>";
  oOut << "<fl c=\"1\">124.42</fl>";
  oOut << "<fl c=\"3\">29.7311</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">79.1382</fl>";
  oOut << "<fl c=\"1\">159.265</fl>";
  oOut << "<fl c=\"3\">88.1915</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">72.0215</fl>";
  oOut << "<fl c=\"1\">170.593</fl>";
  oOut << "<fl c=\"3\">36.944</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">76.9714</fl>";
  oOut << "<fl c=\"1\">168.878</fl>";
  oOut << "<fl c=\"3\">25.4962</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">82.7576</fl>";
  oOut << "<fl c=\"1\">34.0454</fl>";
  oOut << "<fl c=\"3\">40.3256</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"2\">";
  oOut << "<fl c=\"0\">83.5083</fl>";
  oOut << "<fl c=\"1\">33.606</fl>";
  oOut << "<fl c=\"4\">6.9068</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"2\">";
  oOut << "<fl c=\"0\">83.075</fl>";
  oOut << "<fl c=\"1\">84.6436</fl>";
  oOut << "<fl c=\"4\">0.865417</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">84.3933</fl>";
  oOut << "<fl c=\"1\">88.1226</fl>";
  oOut << "<fl c=\"3\">60.0977</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"2\">";
  oOut << "<fl c=\"0\">81.9031</fl>";
  oOut << "<fl c=\"1\">109.406</fl>";
  oOut << "<fl c=\"4\">3.42908</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"2\">";
  oOut << "<fl c=\"0\">84.6741</fl>";
  oOut << "<fl c=\"1\">130.225</fl>";
  oOut << "<fl c=\"4\">3.86002</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"2\">";
  oOut << "<fl c=\"0\">83.8135</fl>";
  oOut << "<fl c=\"1\">146.863</fl>";
  oOut << "<fl c=\"4\">3.14371</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">85.7422</fl>";
  oOut << "<fl c=\"1\">161.554</fl>";
  oOut << "<fl c=\"3\">96.7279</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">94.3542</fl>";
  oOut << "<fl c=\"1\">1.74561</fl>";
  oOut << "<fl c=\"3\">96.7407</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"2\">";
  oOut << "<fl c=\"0\">92.9688</fl>";
  oOut << "<fl c=\"1\">6.97021</fl>";
  oOut << "<fl c=\"4\">0.121399</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">93.3777</fl>";
  oOut << "<fl c=\"1\">34.7412</fl>";
  oOut << "<fl c=\"3\">57.3093</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">92.926</fl>";
  oOut << "<fl c=\"1\">88.324</fl>";
  oOut << "<fl c=\"3\">36.1157</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">95.4224</fl>";
  oOut << "<fl c=\"1\">125.244</fl>";
  oOut << "<fl c=\"3\">89.1541</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">95.7336</fl>";
  oOut << "<fl c=\"1\">161.938</fl>";
  oOut << "<fl c=\"3\">46.3538</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">96.2036</fl>";
  oOut << "<fl c=\"1\">1.5686</fl>";
  oOut << "<fl c=\"3\">73.3417</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">99.7314</fl>";
  oOut << "<fl c=\"1\">21.3623</fl>";
  oOut << "<fl c=\"3\">57.3572</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"2\">";
  oOut << "<fl c=\"0\">100.848</fl>";
  oOut << "<fl c=\"1\">33.0505</fl>";
  oOut << "<fl c=\"4\">5.58624</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">99.823</fl>";
  oOut << "<fl c=\"1\">86.7126</fl>";
  oOut << "<fl c=\"3\">16.5344</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"2\">";
  oOut << "<fl c=\"0\">100.427</fl>";
  oOut << "<fl c=\"1\">85.7544</fl>";
  oOut << "<fl c=\"4\">0.874084</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">101.019</fl>";
  oOut << "<fl c=\"1\">137.213</fl>";
  oOut << "<fl c=\"3\">75.7404</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">96.3684</fl>";
  oOut << "<fl c=\"1\">139.05</fl>";
  oOut << "<fl c=\"3\">19.7726</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">101.013</fl>";
  oOut << "<fl c=\"1\">165.723</fl>";
  oOut << "<fl c=\"3\">84.9774</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">100.366</fl>";
  oOut << "<fl c=\"1\">197.04</fl>";
  oOut << "<fl c=\"3\">17.7695</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">111.249</fl>";
  oOut << "<fl c=\"1\">9.65576</fl>";
  oOut << "<fl c=\"3\">87.7063</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">106.213</fl>";
  oOut << "<fl c=\"1\">31.1951</fl>";
  oOut << "<fl c=\"3\">22.2653</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">109.741</fl>";
  oOut << "<fl c=\"1\">95.3918</fl>";
  oOut << "<fl c=\"3\">91.3141</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">110.889</fl>";
  oOut << "<fl c=\"1\">110.76</fl>";
  oOut << "<fl c=\"3\">99.9619</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">108.154</fl>";
  oOut << "<fl c=\"1\">129.559</fl>";
  oOut << "<fl c=\"3\">77.2925</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">104.541</fl>";
  oOut << "<fl c=\"1\">128.662</fl>";
  oOut << "<fl c=\"3\">63.3987</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"2\">";
  oOut << "<fl c=\"0\">110.876</fl>";
  oOut << "<fl c=\"1\">145.605</fl>";
  oOut << "<fl c=\"4\">7.06693</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">111.066</fl>";
  oOut << "<fl c=\"1\">157.922</fl>";
  oOut << "<fl c=\"3\">50.6357</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">105.829</fl>";
  oOut << "<fl c=\"1\">157.025</fl>";
  oOut << "<fl c=\"3\">27.6285</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"2\">";
  oOut << "<fl c=\"0\">108.478</fl>";
  oOut << "<fl c=\"1\">153.021</fl>";
  oOut << "<fl c=\"4\">9.06946</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"2\">";
  oOut << "<fl c=\"0\">118.353</fl>";
  oOut << "<fl c=\"1\">33.5266</fl>";
  oOut << "<fl c=\"4\">0.231476</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">112.366</fl>";
  oOut << "<fl c=\"1\">47.6074</fl>";
  oOut << "<fl c=\"3\">98.544</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">118.787</fl>";
  oOut << "<fl c=\"1\">43.1885</fl>";
  oOut << "<fl c=\"3\">93.6996</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">113.336</fl>";
  oOut << "<fl c=\"1\">77.9236</fl>";
  oOut << "<fl c=\"3\">35.4398</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"2\">";
  oOut << "<fl c=\"0\">112.384</fl>";
  oOut << "<fl c=\"1\">73.7244</fl>";
  oOut << "<fl c=\"4\">0.759308</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"2\">";
  oOut << "<fl c=\"0\">113.08</fl>";
  oOut << "<fl c=\"1\">77.5452</fl>";
  oOut << "<fl c=\"4\">0.0106201</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">113.177</fl>";
  oOut << "<fl c=\"1\">102.356</fl>";
  oOut << "<fl c=\"3\">68.0389</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">116.687</fl>";
  oOut << "<fl c=\"1\">132.648</fl>";
  oOut << "<fl c=\"3\">33.4067</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">118.372</fl>";
  oOut << "<fl c=\"1\">140.179</fl>";
  oOut << "<fl c=\"3\">15.5627</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">118.268</fl>";
  oOut << "<fl c=\"1\">145.471</fl>";
  oOut << "<fl c=\"3\">20.1572</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">118.536</fl>";
  oOut << "<fl c=\"1\">175.97</fl>";
  oOut << "<fl c=\"3\">49.8904</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"2\">";
  oOut << "<fl c=\"0\">113.666</fl>";
  oOut << "<fl c=\"1\">175.903</fl>";
  oOut << "<fl c=\"4\">9.13098</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">120.911</fl>";
  oOut << "<fl c=\"1\">14.6179</fl>";
  oOut << "<fl c=\"3\">79.9518</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">124.872</fl>";
  oOut << "<fl c=\"1\">24.2737</fl>";
  oOut << "<fl c=\"3\">71.2488</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">123.578</fl>";
  oOut << "<fl c=\"1\">48.6084</fl>";
  oOut << "<fl c=\"3\">97.6428</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">122.235</fl>";
  oOut << "<fl c=\"1\">113.013</fl>";
  oOut << "<fl c=\"3\">35.4224</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">123.816</fl>";
  oOut << "<fl c=\"1\">147.052</fl>";
  oOut << "<fl c=\"3\">62.9898</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">122.949</fl>";
  oOut << "<fl c=\"1\">170.654</fl>";
  oOut << "<fl c=\"3\">79.6609</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">120.801</fl>";
  oOut << "<fl c=\"1\">169.794</fl>";
  oOut << "<fl c=\"3\">23.1741</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">121.851</fl>";
  oOut << "<fl c=\"1\">187.134</fl>";
  oOut << "<fl c=\"3\">38.2736</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">134.058</fl>";
  oOut << "<fl c=\"1\">9.44214</fl>";
  oOut << "<fl c=\"3\">89.4391</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">134.32</fl>";
  oOut << "<fl c=\"1\">9.79614</fl>";
  oOut << "<fl c=\"3\">60.9674</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">132.05</fl>";
  oOut << "<fl c=\"1\">58.5876</fl>";
  oOut << "<fl c=\"3\">33.1284</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">129.7</fl>";
  oOut << "<fl c=\"1\">83.1299</fl>";
  oOut << "<fl c=\"3\">28.3542</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"2\">";
  oOut << "<fl c=\"0\">128.308</fl>";
  oOut << "<fl c=\"1\">80.2185</fl>";
  oOut << "<fl c=\"4\">8.0719</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">135.468</fl>";
  oOut << "<fl c=\"1\">157.434</fl>";
  oOut << "<fl c=\"3\">96.9788</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">134.167</fl>";
  oOut << "<fl c=\"1\">155.219</fl>";
  oOut << "<fl c=\"3\">79.4186</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">131.5</fl>";
  oOut << "<fl c=\"1\">158.453</fl>";
  oOut << "<fl c=\"3\">61.6782</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">134.979</fl>";
  oOut << "<fl c=\"1\">186.09</fl>";
  oOut << "<fl c=\"3\">15.8936</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">139.819</fl>";
  oOut << "<fl c=\"1\">14.624</fl>";
  oOut << "<fl c=\"3\">99.7043</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">141.724</fl>";
  oOut << "<fl c=\"1\">10.6445</fl>";
  oOut << "<fl c=\"3\">17.1341</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">142.871</fl>";
  oOut << "<fl c=\"1\">31.7261</fl>";
  oOut << "<fl c=\"3\">57.7597</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">139.801</fl>";
  oOut << "<fl c=\"1\">37.793</fl>";
  oOut << "<fl c=\"3\">46.7459</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">140.521</fl>";
  oOut << "<fl c=\"1\">43.5669</fl>";
  oOut << "<fl c=\"3\">35.9793</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">141.107</fl>";
  oOut << "<fl c=\"1\">87.3779</fl>";
  oOut << "<fl c=\"3\">29.9094</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"2\">";
  oOut << "<fl c=\"0\">138.226</fl>";
  oOut << "<fl c=\"1\">100.714</fl>";
  oOut << "<fl c=\"4\">1.70724</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">136.646</fl>";
  oOut << "<fl c=\"1\">125.232</fl>";
  oOut << "<fl c=\"3\">46.1038</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">143.713</fl>";
  oOut << "<fl c=\"1\">127.374</fl>";
  oOut << "<fl c=\"3\">19.0558</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">138.806</fl>";
  oOut << "<fl c=\"1\">145.758</fl>";
  oOut << "<fl c=\"3\">54.8535</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"2\">";
  oOut << "<fl c=\"0\">138.654</fl>";
  oOut << "<fl c=\"1\">144.189</fl>";
  oOut << "<fl c=\"4\">5.89359</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"2\">";
  oOut << "<fl c=\"0\">140.277</fl>";
  oOut << "<fl c=\"1\">161.493</fl>";
  oOut << "<fl c=\"4\">0.424652</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">143.634</fl>";
  oOut << "<fl c=\"1\">182.379</fl>";
  oOut << "<fl c=\"3\">73.5956</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">143.28</fl>";
  oOut << "<fl c=\"1\">176.154</fl>";
  oOut << "<fl c=\"3\">40.9753</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">137.079</fl>";
  oOut << "<fl c=\"1\">199.689</fl>";
  oOut << "<fl c=\"3\">84.9057</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">146.021</fl>";
  oOut << "<fl c=\"1\">33.9355</fl>";
  oOut << "<fl c=\"3\">59.4388</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"2\">";
  oOut << "<fl c=\"0\">151.587</fl>";
  oOut << "<fl c=\"1\">50.9766</fl>";
  oOut << "<fl c=\"4\">0.565063</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">145.74</fl>";
  oOut << "<fl c=\"1\">72.1069</fl>";
  oOut << "<fl c=\"3\">58.8098</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">147.827</fl>";
  oOut << "<fl c=\"1\">90.271</fl>";
  oOut << "<fl c=\"3\">68.3124</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">148.401</fl>";
  oOut << "<fl c=\"1\">137.726</fl>";
  oOut << "<fl c=\"3\">41.2891</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">156.36</fl>";
  oOut << "<fl c=\"1\">5.97534</fl>";
  oOut << "<fl c=\"3\">14.552</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">159.839</fl>";
  oOut << "<fl c=\"1\">6.12793</fl>";
  oOut << "<fl c=\"3\">12.1011</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"2\">";
  oOut << "<fl c=\"0\">157.77</fl>";
  oOut << "<fl c=\"1\">1.48315</fl>";
  oOut << "<fl c=\"4\">7.88678</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">152.338</fl>";
  oOut << "<fl c=\"1\">65.1672</fl>";
  oOut << "<fl c=\"3\">59.3811</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">158.124</fl>";
  oOut << "<fl c=\"1\">72.4365</fl>";
  oOut << "<fl c=\"3\">67.265</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">159.418</fl>";
  oOut << "<fl c=\"1\">98.0652</fl>";
  oOut << "<fl c=\"3\">40.4138</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">159.143</fl>";
  oOut << "<fl c=\"1\">115.289</fl>";
  oOut << "<fl c=\"3\">13.53</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"2\">";
  oOut << "<fl c=\"0\">153.43</fl>";
  oOut << "<fl c=\"1\">125.781</fl>";
  oOut << "<fl c=\"4\">0.320953</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">155.103</fl>";
  oOut << "<fl c=\"1\">147.821</fl>";
  oOut << "<fl c=\"3\">24.2194</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">152.24</fl>";
  oOut << "<fl c=\"1\">153.9</fl>";
  oOut << "<fl c=\"3\">96.1096</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">158.722</fl>";
  oOut << "<fl c=\"1\">180.762</fl>";
  oOut << "<fl c=\"3\">73.6639</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">165.582</fl>";
  oOut << "<fl c=\"1\">63.6658</fl>";
  oOut << "<fl c=\"3\">46.4575</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"2\">";
  oOut << "<fl c=\"0\">167.572</fl>";
  oOut << "<fl c=\"1\">90.1428</fl>";
  oOut << "<fl c=\"4\">2.10028</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">166.547</fl>";
  oOut << "<fl c=\"1\">117.065</fl>";
  oOut << "<fl c=\"3\">96.4426</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"2\">";
  oOut << "<fl c=\"0\">161.499</fl>";
  oOut << "<fl c=\"1\">115.997</fl>";
  oOut << "<fl c=\"4\">0.0427551</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">160.547</fl>";
  oOut << "<fl c=\"1\">169.476</fl>";
  oOut << "<fl c=\"3\">48.8187</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">162.592</fl>";
  oOut << "<fl c=\"1\">192.279</fl>";
  oOut << "<fl c=\"3\">45.5884</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">169.183</fl>";
  oOut << "<fl c=\"1\">57.1533</fl>";
  oOut << "<fl c=\"3\">67.7124</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">169.226</fl>";
  oOut << "<fl c=\"1\">99.9023</fl>";
  oOut << "<fl c=\"3\">98.5852</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">171.051</fl>";
  oOut << "<fl c=\"1\">117.261</fl>";
  oOut << "<fl c=\"3\">69.455</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">174.701</fl>";
  oOut << "<fl c=\"1\">125.238</fl>";
  oOut << "<fl c=\"3\">78.1271</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">168.738</fl>";
  oOut << "<fl c=\"1\">139.368</fl>";
  oOut << "<fl c=\"3\">69.697</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">169.916</fl>";
  oOut << "<fl c=\"1\">139.343</fl>";
  oOut << "<fl c=\"3\">67.7588</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">178.082</fl>";
  oOut << "<fl c=\"1\">38.6414</fl>";
  oOut << "<fl c=\"3\">72.2574</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">180.267</fl>";
  oOut << "<fl c=\"1\">45.2698</fl>";
  oOut << "<fl c=\"3\">88.8773</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">179.376</fl>";
  oOut << "<fl c=\"1\">100.708</fl>";
  oOut << "<fl c=\"3\">67.0215</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"2\">";
  oOut << "<fl c=\"0\">180.066</fl>";
  oOut << "<fl c=\"1\">139.948</fl>";
  oOut << "<fl c=\"4\">0.58136</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">177.277</fl>";
  oOut << "<fl c=\"1\">155.872</fl>";
  oOut << "<fl c=\"3\">51.0059</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">180.469</fl>";
  oOut << "<fl c=\"1\">156.335</fl>";
  oOut << "<fl c=\"3\">40.5386</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"2\">";
  oOut << "<fl c=\"0\">180.609</fl>";
  oOut << "<fl c=\"1\">168.848</fl>";
  oOut << "<fl c=\"4\">0.742126</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">177.209</fl>";
  oOut << "<fl c=\"1\">176.434</fl>";
  oOut << "<fl c=\"3\">76.7151</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">182.733</fl>";
  oOut << "<fl c=\"1\">180.237</fl>";
  oOut << "<fl c=\"3\">25.032</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">189.771</fl>";
  oOut << "<fl c=\"1\">39.679</fl>";
  oOut << "<fl c=\"3\">22.9523</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">185.217</fl>";
  oOut << "<fl c=\"1\">81.8359</fl>";
  oOut << "<fl c=\"3\">79.0582</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">189.844</fl>";
  oOut << "<fl c=\"1\">136.011</fl>";
  oOut << "<fl c=\"3\">91.6418</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">190.149</fl>";
  oOut << "<fl c=\"1\">142.554</fl>";
  oOut << "<fl c=\"3\">86.8805</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">188.257</fl>";
  oOut << "<fl c=\"1\">195.312</fl>";
  oOut << "<fl c=\"3\">21.1044</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">197.137</fl>";
  oOut << "<fl c=\"1\">14.624</fl>";
  oOut << "<fl c=\"3\">73.0475</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">194.482</fl>";
  oOut << "<fl c=\"1\">28.7781</fl>";
  oOut << "<fl c=\"3\">13.6069</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"2\">";
  oOut << "<fl c=\"0\">192.053</fl>";
  oOut << "<fl c=\"1\">32.5745</fl>";
  oOut << "<fl c=\"4\">1.33481</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">194.592</fl>";
  oOut << "<fl c=\"1\">102.588</fl>";
  oOut << "<fl c=\"3\">34.5648</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">196.094</fl>";
  oOut << "<fl c=\"1\">109.802</fl>";
  oOut << "<fl c=\"3\">46.6089</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"2\">";
  oOut << "<fl c=\"0\">192.279</fl>";
  oOut << "<fl c=\"1\">126.819</fl>";
  oOut << "<fl c=\"4\">0.661713</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">197.632</fl>";
  oOut << "<fl c=\"1\">157.861</fl>";
  oOut << "<fl c=\"3\">91.5756</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">198.151</fl>";
  oOut << "<fl c=\"1\">157.324</fl>";
  oOut << "<fl c=\"3\">79.1922</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">195.99</fl>";
  oOut << "<fl c=\"1\">177.252</fl>";
  oOut << "<fl c=\"3\">93.9792</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"7\" tp=\"3\">";
  oOut << "<fl c=\"0\">192.493</fl>";
  oOut << "<fl c=\"1\">177.795</fl>";
  oOut << "<fl c=\"3\">57.1655</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">7.85522</fl>";
  oOut << "<fl c=\"1\">15.8752</fl>";
  oOut << "<fl c=\"3\">53.6151</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">3.61938</fl>";
  oOut << "<fl c=\"1\">94.5862</fl>";
  oOut << "<fl c=\"3\">86.0223</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">2.83203</fl>";
  oOut << "<fl c=\"1\">138.33</fl>";
  oOut << "<fl c=\"3\">44.0927</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">5.07812</fl>";
  oOut << "<fl c=\"1\">137.927</fl>";
  oOut << "<fl c=\"3\">34.1992</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">1.24512</fl>";
  oOut << "<fl c=\"1\">159.784</fl>";
  oOut << "<fl c=\"3\">35.2258</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">2.948</fl>";
  oOut << "<fl c=\"1\">156.512</fl>";
  oOut << "<fl c=\"3\">33.9059</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">0.738525</fl>";
  oOut << "<fl c=\"1\">185.51</fl>";
  oOut << "<fl c=\"3\">92.1225</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">3.48511</fl>";
  oOut << "<fl c=\"1\">188.428</fl>";
  oOut << "<fl c=\"3\">63.6935</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">1.74561</fl>";
  oOut << "<fl c=\"1\">186.206</fl>";
  oOut << "<fl c=\"3\">30.4333</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"2\">";
  oOut << "<fl c=\"0\">8.94775</fl>";
  oOut << "<fl c=\"1\">16.8579</fl>";
  oOut << "<fl c=\"4\">0.0343323</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">8.75244</fl>";
  oOut << "<fl c=\"1\">37.7075</fl>";
  oOut << "<fl c=\"3\">24.7662</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">14.2334</fl>";
  oOut << "<fl c=\"1\">42.0044</fl>";
  oOut << "<fl c=\"3\">38.7991</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">13.8733</fl>";
  oOut << "<fl c=\"1\">50.293</fl>";
  oOut << "<fl c=\"3\">65.0327</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">11.9873</fl>";
  oOut << "<fl c=\"1\">83.0261</fl>";
  oOut << "<fl c=\"3\">78.479</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">9.97925</fl>";
  oOut << "<fl c=\"1\">90.448</fl>";
  oOut << "<fl c=\"3\">80.6061</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">12.0911</fl>";
  oOut << "<fl c=\"1\">138.55</fl>";
  oOut << "<fl c=\"3\">43.5123</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">11.7126</fl>";
  oOut << "<fl c=\"1\">146.68</fl>";
  oOut << "<fl c=\"3\">95.4285</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">10.1807</fl>";
  oOut << "<fl c=\"1\">173.822</fl>";
  oOut << "<fl c=\"3\">17.1033</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">8.38013</fl>";
  oOut << "<fl c=\"1\">193.188</fl>";
  oOut << "<fl c=\"3\">51.1322</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">10.9863</fl>";
  oOut << "<fl c=\"1\">198.413</fl>";
  oOut << "<fl c=\"3\">34.9146</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"2\">";
  oOut << "<fl c=\"0\">14.9109</fl>";
  oOut << "<fl c=\"1\">199.915</fl>";
  oOut << "<fl c=\"4\">9.48557</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">22.998</fl>";
  oOut << "<fl c=\"1\">47.113</fl>";
  oOut << "<fl c=\"3\">62.475</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">20.3186</fl>";
  oOut << "<fl c=\"1\">53.186</fl>";
  oOut << "<fl c=\"3\">86.0608</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">21.3257</fl>";
  oOut << "<fl c=\"1\">92.1265</fl>";
  oOut << "<fl c=\"3\">41.8686</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">17.334</fl>";
  oOut << "<fl c=\"1\">107.489</fl>";
  oOut << "<fl c=\"3\">78.2904</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">19.0918</fl>";
  oOut << "<fl c=\"1\">120.197</fl>";
  oOut << "<fl c=\"3\">85.6091</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">17.5354</fl>";
  oOut << "<fl c=\"1\">188.818</fl>";
  oOut << "<fl c=\"3\">64.9969</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">17.0288</fl>";
  oOut << "<fl c=\"1\">190.979</fl>";
  oOut << "<fl c=\"3\">13.5339</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"2\">";
  oOut << "<fl c=\"0\">27.1057</fl>";
  oOut << "<fl c=\"1\">79.6814</fl>";
  oOut << "<fl c=\"4\">0.208954</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">24.1516</fl>";
  oOut << "<fl c=\"1\">85.7239</fl>";
  oOut << "<fl c=\"3\">41.0172</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">26.1353</fl>";
  oOut << "<fl c=\"1\">99.1272</fl>";
  oOut << "<fl c=\"3\">73.4134</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">27.9297</fl>";
  oOut << "<fl c=\"1\">111.902</fl>";
  oOut << "<fl c=\"3\">94.1898</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">24.9451</fl>";
  oOut << "<fl c=\"1\">121.228</fl>";
  oOut << "<fl c=\"3\">49.3976</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">30.0842</fl>";
  oOut << "<fl c=\"1\">139.465</fl>";
  oOut << "<fl c=\"3\">81.8219</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">30.8594</fl>";
  oOut << "<fl c=\"1\">182.654</fl>";
  oOut << "<fl c=\"3\">34.9753</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"2\">";
  oOut << "<fl c=\"0\">31.4209</fl>";
  oOut << "<fl c=\"1\">186.853</fl>";
  oOut << "<fl c=\"4\">0.418823</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"2\">";
  oOut << "<fl c=\"0\">38.6597</fl>";
  oOut << "<fl c=\"1\">11.0229</fl>";
  oOut << "<fl c=\"4\">8.27734</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">36.7615</fl>";
  oOut << "<fl c=\"1\">81.1768</fl>";
  oOut << "<fl c=\"3\">55.0162</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">35.6018</fl>";
  oOut << "<fl c=\"1\">89.2212</fl>";
  oOut << "<fl c=\"3\">66.377</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">38.855</fl>";
  oOut << "<fl c=\"1\">92.4927</fl>";
  oOut << "<fl c=\"3\">41.9351</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">32.373</fl>";
  oOut << "<fl c=\"1\">102.222</fl>";
  oOut << "<fl c=\"3\">99.4312</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">34.4421</fl>";
  oOut << "<fl c=\"1\">105.292</fl>";
  oOut << "<fl c=\"3\">70.9167</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">38.0981</fl>";
  oOut << "<fl c=\"1\">105.444</fl>";
  oOut << "<fl c=\"3\">28.6154</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">38.385</fl>";
  oOut << "<fl c=\"1\">119.684</fl>";
  oOut << "<fl c=\"3\">17.1301</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">38.1836</fl>";
  oOut << "<fl c=\"1\">126.416</fl>";
  oOut << "<fl c=\"3\">52.8085</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">33.4106</fl>";
  oOut << "<fl c=\"1\">131.671</fl>";
  oOut << "<fl c=\"3\">17.9541</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">36.2</fl>";
  oOut << "<fl c=\"1\">180.64</fl>";
  oOut << "<fl c=\"3\">14.7354</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">33.5327</fl>";
  oOut << "<fl c=\"1\">196.79</fl>";
  oOut << "<fl c=\"3\">59.407</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"2\">";
  oOut << "<fl c=\"0\">33.0139</fl>";
  oOut << "<fl c=\"1\">196.179</fl>";
  oOut << "<fl c=\"4\">9.6748</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">46.6614</fl>";
  oOut << "<fl c=\"1\">61.1267</fl>";
  oOut << "<fl c=\"3\">90.2371</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">44.5984</fl>";
  oOut << "<fl c=\"1\">91.2048</fl>";
  oOut << "<fl c=\"3\">78.8437</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">44.3298</fl>";
  oOut << "<fl c=\"1\">94.6899</fl>";
  oOut << "<fl c=\"3\">22.3828</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">43.1335</fl>";
  oOut << "<fl c=\"1\">97.9797</fl>";
  oOut << "<fl c=\"3\">39.8886</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">46.1548</fl>";
  oOut << "<fl c=\"1\">115.314</fl>";
  oOut << "<fl c=\"3\">19.7021</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"2\">";
  oOut << "<fl c=\"0\">40.7837</fl>";
  oOut << "<fl c=\"1\">113.672</fl>";
  oOut << "<fl c=\"4\">0.283813</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">42.5293</fl>";
  oOut << "<fl c=\"1\">146.057</fl>";
  oOut << "<fl c=\"3\">32.8064</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"2\">";
  oOut << "<fl c=\"0\">47.3572</fl>";
  oOut << "<fl c=\"1\">166.418</fl>";
  oOut << "<fl c=\"4\">7.51407</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"2\">";
  oOut << "<fl c=\"0\">46.5515</fl>";
  oOut << "<fl c=\"1\">176.959</fl>";
  oOut << "<fl c=\"4\">0.794281</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">44.2932</fl>";
  oOut << "<fl c=\"1\">198.828</fl>";
  oOut << "<fl c=\"3\">81.3428</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">44.5496</fl>";
  oOut << "<fl c=\"1\">194.128</fl>";
  oOut << "<fl c=\"3\">73.0765</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">53.0701</fl>";
  oOut << "<fl c=\"1\">9.729</fl>";
  oOut << "<fl c=\"3\">80.5624</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">50.0061</fl>";
  oOut << "<fl c=\"1\">25.592</fl>";
  oOut << "<fl c=\"3\">90.4434</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">52.356</fl>";
  oOut << "<fl c=\"1\">58.5144</fl>";
  oOut << "<fl c=\"3\">95.1074</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">54.2542</fl>";
  oOut << "<fl c=\"1\">64.5691</fl>";
  oOut << "<fl c=\"3\">91.0968</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">52.4414</fl>";
  oOut << "<fl c=\"1\">84.2346</fl>";
  oOut << "<fl c=\"3\">97.9132</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">48.0225</fl>";
  oOut << "<fl c=\"1\">85.2478</fl>";
  oOut << "<fl c=\"3\">10.0641</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">55.4504</fl>";
  oOut << "<fl c=\"1\">126.959</fl>";
  oOut << "<fl c=\"3\">66.1102</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">48.6267</fl>";
  oOut << "<fl c=\"1\">140.436</fl>";
  oOut << "<fl c=\"3\">72.4905</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">63.0066</fl>";
  oOut << "<fl c=\"1\">15.6006</fl>";
  oOut << "<fl c=\"3\">22.8455</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"2\">";
  oOut << "<fl c=\"0\">57.1167</fl>";
  oOut << "<fl c=\"1\">43.6707</fl>";
  oOut << "<fl c=\"4\">6.72058</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">58.5938</fl>";
  oOut << "<fl c=\"1\">54.8279</fl>";
  oOut << "<fl c=\"3\">22.4445</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">57.074</fl>";
  oOut << "<fl c=\"1\">60.1135</fl>";
  oOut << "<fl c=\"3\">12.9913</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">57.0374</fl>";
  oOut << "<fl c=\"1\">65.7104</fl>";
  oOut << "<fl c=\"3\">73.624</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">63.3484</fl>";
  oOut << "<fl c=\"1\">76.7883</fl>";
  oOut << "<fl c=\"3\">69.1251</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">59.5764</fl>";
  oOut << "<fl c=\"1\">96.0999</fl>";
  oOut << "<fl c=\"3\">28.0154</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"2\">";
  oOut << "<fl c=\"0\">61.499</fl>";
  oOut << "<fl c=\"1\">105.438</fl>";
  oOut << "<fl c=\"4\">0.917542</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"2\">";
  oOut << "<fl c=\"0\">63.3423</fl>";
  oOut << "<fl c=\"1\">143.262</fl>";
  oOut << "<fl c=\"4\">5.25363</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">70.4346</fl>";
  oOut << "<fl c=\"1\">49.1577</fl>";
  oOut << "<fl c=\"3\">92.9312</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">70.343</fl>";
  oOut << "<fl c=\"1\">75.3845</fl>";
  oOut << "<fl c=\"3\">56.546</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">71.5942</fl>";
  oOut << "<fl c=\"1\">127.454</fl>";
  oOut << "<fl c=\"3\">44.5139</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">64.5386</fl>";
  oOut << "<fl c=\"1\">174.213</fl>";
  oOut << "<fl c=\"3\">27.8207</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">72.467</fl>";
  oOut << "<fl c=\"1\">28.1982</fl>";
  oOut << "<fl c=\"3\">94.9786</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">76.8066</fl>";
  oOut << "<fl c=\"1\">51.9287</fl>";
  oOut << "<fl c=\"3\">49.8593</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">73.3887</fl>";
  oOut << "<fl c=\"1\">91.3879</fl>";
  oOut << "<fl c=\"3\">52.5479</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">74.2981</fl>";
  oOut << "<fl c=\"1\">91.0339</fl>";
  oOut << "<fl c=\"3\">20.072</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">79.4861</fl>";
  oOut << "<fl c=\"1\">112.067</fl>";
  oOut << "<fl c=\"3\">21.673</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">78.2837</fl>";
  oOut << "<fl c=\"1\">114.899</fl>";
  oOut << "<fl c=\"3\">20.528</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"2\">";
  oOut << "<fl c=\"0\">79.2786</fl>";
  oOut << "<fl c=\"1\">119.672</fl>";
  oOut << "<fl c=\"4\">4.0553</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">76.8433</fl>";
  oOut << "<fl c=\"1\">147.992</fl>";
  oOut << "<fl c=\"3\">83.7686</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">78.064</fl>";
  oOut << "<fl c=\"1\">158.014</fl>";
  oOut << "<fl c=\"3\">40.271</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">77.2278</fl>";
  oOut << "<fl c=\"1\">163.239</fl>";
  oOut << "<fl c=\"3\">35.4596</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">72.7112</fl>";
  oOut << "<fl c=\"1\">169.318</fl>";
  oOut << "<fl c=\"3\">81.7749</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">79.4739</fl>";
  oOut << "<fl c=\"1\">179.755</fl>";
  oOut << "<fl c=\"3\">31.1191</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">72.876</fl>";
  oOut << "<fl c=\"1\">196.698</fl>";
  oOut << "<fl c=\"3\">65.3021</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">83.8867</fl>";
  oOut << "<fl c=\"1\">17.7673</fl>";
  oOut << "<fl c=\"3\">19.2203</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">87.7441</fl>";
  oOut << "<fl c=\"1\">36.7249</fl>";
  oOut << "<fl c=\"3\">94.2191</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">83.1299</fl>";
  oOut << "<fl c=\"1\">73.6389</fl>";
  oOut << "<fl c=\"3\">40.3174</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">85.8215</fl>";
  oOut << "<fl c=\"1\">79.5044</fl>";
  oOut << "<fl c=\"3\">37.2751</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">82.1899</fl>";
  oOut << "<fl c=\"1\">100.22</fl>";
  oOut << "<fl c=\"3\">85.2982</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"2\">";
  oOut << "<fl c=\"0\">80.9875</fl>";
  oOut << "<fl c=\"1\">125.586</fl>";
  oOut << "<fl c=\"4\">6.56732</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"2\">";
  oOut << "<fl c=\"0\">80.3467</fl>";
  oOut << "<fl c=\"1\">145.477</fl>";
  oOut << "<fl c=\"4\">0.154327</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">89.9353</fl>";
  oOut << "<fl c=\"1\">1.63574</fl>";
  oOut << "<fl c=\"3\">86.7889</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">95.4529</fl>";
  oOut << "<fl c=\"1\">34.8083</fl>";
  oOut << "<fl c=\"3\">39.3954</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">89.5264</fl>";
  oOut << "<fl c=\"1\">65.1001</fl>";
  oOut << "<fl c=\"3\">57.7863</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">94.9951</fl>";
  oOut << "<fl c=\"1\">79.1016</fl>";
  oOut << "<fl c=\"3\">76.0556</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">95.0439</fl>";
  oOut << "<fl c=\"1\">90.0208</fl>";
  oOut << "<fl c=\"3\">42.0859</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">93.1641</fl>";
  oOut << "<fl c=\"1\">133.429</fl>";
  oOut << "<fl c=\"3\">36.8311</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">92.688</fl>";
  oOut << "<fl c=\"1\">182.611</fl>";
  oOut << "<fl c=\"3\">79.91</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">101.117</fl>";
  oOut << "<fl c=\"1\">12.6465</fl>";
  oOut << "<fl c=\"3\">38.2138</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">103.735</fl>";
  oOut << "<fl c=\"1\">49.6948</fl>";
  oOut << "<fl c=\"3\">56.1749</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">97.2717</fl>";
  oOut << "<fl c=\"1\">107.532</fl>";
  oOut << "<fl c=\"3\">60.6042</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">108.85</fl>";
  oOut << "<fl c=\"1\">45.9473</fl>";
  oOut << "<fl c=\"3\">86.077</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">111.713</fl>";
  oOut << "<fl c=\"1\">53.0701</fl>";
  oOut << "<fl c=\"3\">86.1853</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">106.128</fl>";
  oOut << "<fl c=\"1\">53.6987</fl>";
  oOut << "<fl c=\"3\">10.116</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">110.663</fl>";
  oOut << "<fl c=\"1\">104.822</fl>";
  oOut << "<fl c=\"3\">71.2793</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">106.25</fl>";
  oOut << "<fl c=\"1\">119.873</fl>";
  oOut << "<fl c=\"3\">81.9788</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">111.823</fl>";
  oOut << "<fl c=\"1\">119.897</fl>";
  oOut << "<fl c=\"3\">67.1396</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"2\">";
  oOut << "<fl c=\"0\">104.419</fl>";
  oOut << "<fl c=\"1\">117.303</fl>";
  oOut << "<fl c=\"4\">0.330597</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">107.605</fl>";
  oOut << "<fl c=\"1\">138.708</fl>";
  oOut << "<fl c=\"3\">64.0689</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">111.42</fl>";
  oOut << "<fl c=\"1\">152.234</fl>";
  oOut << "<fl c=\"3\">69.6097</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">106.72</fl>";
  oOut << "<fl c=\"1\">161.517</fl>";
  oOut << "<fl c=\"3\">61.196</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">109.65</fl>";
  oOut << "<fl c=\"1\">184.723</fl>";
  oOut << "<fl c=\"3\">31.348</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">105.42</fl>";
  oOut << "<fl c=\"1\">190.289</fl>";
  oOut << "<fl c=\"3\">12.8107</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"2\">";
  oOut << "<fl c=\"0\">117.725</fl>";
  oOut << "<fl c=\"1\">13.2385</fl>";
  oOut << "<fl c=\"4\">0.399994</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">114.99</fl>";
  oOut << "<fl c=\"1\">25.5005</fl>";
  oOut << "<fl c=\"3\">47.1631</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">115.051</fl>";
  oOut << "<fl c=\"1\">38.6902</fl>";
  oOut << "<fl c=\"3\">80.5399</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">119.104</fl>";
  oOut << "<fl c=\"1\">62.5793</fl>";
  oOut << "<fl c=\"3\">65.2374</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">118.658</fl>";
  oOut << "<fl c=\"1\">60.8093</fl>";
  oOut << "<fl c=\"3\">64.9731</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">117.029</fl>";
  oOut << "<fl c=\"1\">63.4033</fl>";
  oOut << "<fl c=\"3\">49.5215</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">113.94</fl>";
  oOut << "<fl c=\"1\">63.6169</fl>";
  oOut << "<fl c=\"3\">13.4805</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">112.994</fl>";
  oOut << "<fl c=\"1\">69.043</fl>";
  oOut << "<fl c=\"3\">56.5231</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"2\">";
  oOut << "<fl c=\"0\">113.251</fl>";
  oOut << "<fl c=\"1\">74.4202</fl>";
  oOut << "<fl c=\"4\">8.61462</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">119.757</fl>";
  oOut << "<fl c=\"1\">93.158</fl>";
  oOut << "<fl c=\"3\">22.5317</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">119.775</fl>";
  oOut << "<fl c=\"1\">139.795</fl>";
  oOut << "<fl c=\"3\">59.8383</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">115.765</fl>";
  oOut << "<fl c=\"1\">158.661</fl>";
  oOut << "<fl c=\"3\">62.5845</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">119.891</fl>";
  oOut << "<fl c=\"1\">173.175</fl>";
  oOut << "<fl c=\"3\">96.6446</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"2\">";
  oOut << "<fl c=\"0\">116.553</fl>";
  oOut << "<fl c=\"1\">183.429</fl>";
  oOut << "<fl c=\"4\">0.703156</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"2\">";
  oOut << "<fl c=\"0\">125.256</fl>";
  oOut << "<fl c=\"1\">11.2305</fl>";
  oOut << "<fl c=\"4\">6.41489</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">125.885</fl>";
  oOut << "<fl c=\"1\">69.3298</fl>";
  oOut << "<fl c=\"3\">96.983</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"2\">";
  oOut << "<fl c=\"0\">125.305</fl>";
  oOut << "<fl c=\"1\">70.2698</fl>";
  oOut << "<fl c=\"4\">0.466827</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">127.771</fl>";
  oOut << "<fl c=\"1\">88.501</fl>";
  oOut << "<fl c=\"3\">75.1611</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"2\">";
  oOut << "<fl c=\"0\">121.002</fl>";
  oOut << "<fl c=\"1\">91.2903</fl>";
  oOut << "<fl c=\"4\">6.6868</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">123.541</fl>";
  oOut << "<fl c=\"1\">104.132</fl>";
  oOut << "<fl c=\"3\">38.0469</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">123.389</fl>";
  oOut << "<fl c=\"1\">122.272</fl>";
  oOut << "<fl c=\"3\">73.4796</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">120.142</fl>";
  oOut << "<fl c=\"1\">136.237</fl>";
  oOut << "<fl c=\"3\">41.2268</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">120.264</fl>";
  oOut << "<fl c=\"1\">151.111</fl>";
  oOut << "<fl c=\"3\">99.7946</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">124.255</fl>";
  oOut << "<fl c=\"1\">174.072</fl>";
  oOut << "<fl c=\"3\">76.0413</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">135.675</fl>";
  oOut << "<fl c=\"1\">5.80444</fl>";
  oOut << "<fl c=\"3\">81.7157</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">133.362</fl>";
  oOut << "<fl c=\"1\">50.9338</fl>";
  oOut << "<fl c=\"3\">72.4124</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"2\">";
  oOut << "<fl c=\"0\">130.408</fl>";
  oOut << "<fl c=\"1\">50.3113</fl>";
  oOut << "<fl c=\"4\">0.726501</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">135.48</fl>";
  oOut << "<fl c=\"1\">100.342</fl>";
  oOut << "<fl c=\"3\">97.7536</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">130.402</fl>";
  oOut << "<fl c=\"1\">102.631</fl>";
  oOut << "<fl c=\"3\">26.5604</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">135.791</fl>";
  oOut << "<fl c=\"1\">101.55</fl>";
  oOut << "<fl c=\"3\">12.9474</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">135.498</fl>";
  oOut << "<fl c=\"1\">123.511</fl>";
  oOut << "<fl c=\"3\">62.8033</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">130.487</fl>";
  oOut << "<fl c=\"1\">129.401</fl>";
  oOut << "<fl c=\"3\">14.4733</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"2\">";
  oOut << "<fl c=\"0\">131.83</fl>";
  oOut << "<fl c=\"1\">142.584</fl>";
  oOut << "<fl c=\"4\">0.816162</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">132.574</fl>";
  oOut << "<fl c=\"1\">150.507</fl>";
  oOut << "<fl c=\"3\">74.4968</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"2\">";
  oOut << "<fl c=\"0\">135.26</fl>";
  oOut << "<fl c=\"1\">144.403</fl>";
  oOut << "<fl c=\"4\">9.63443</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">134.778</fl>";
  oOut << "<fl c=\"1\">166.858</fl>";
  oOut << "<fl c=\"3\">84.3524</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"2\">";
  oOut << "<fl c=\"0\">129.15</fl>";
  oOut << "<fl c=\"1\">175.562</fl>";
  oOut << "<fl c=\"4\">0.730804</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">131.83</fl>";
  oOut << "<fl c=\"1\">181.116</fl>";
  oOut << "<fl c=\"3\">84.0259</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">139.844</fl>";
  oOut << "<fl c=\"1\">10.9436</fl>";
  oOut << "<fl c=\"3\">91.1642</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">139.044</fl>";
  oOut << "<fl c=\"1\">19.6411</fl>";
  oOut << "<fl c=\"3\">90.9143</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">141.846</fl>";
  oOut << "<fl c=\"1\">25.4822</fl>";
  oOut << "<fl c=\"3\">19.082</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">138.043</fl>";
  oOut << "<fl c=\"1\">41.8396</fl>";
  oOut << "<fl c=\"3\">46.2427</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">140.826</fl>";
  oOut << "<fl c=\"1\">79.1626</fl>";
  oOut << "<fl c=\"3\">12.3938</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"2\">";
  oOut << "<fl c=\"0\">141.315</fl>";
  oOut << "<fl c=\"1\">83.2825</fl>";
  oOut << "<fl c=\"4\">0.539429</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">144.196</fl>";
  oOut << "<fl c=\"1\">1.5686</fl>";
  oOut << "<fl c=\"3\">40.9665</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">148.657</fl>";
  oOut << "<fl c=\"1\">34.4299</fl>";
  oOut << "<fl c=\"3\">25.8176</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">145.532</fl>";
  oOut << "<fl c=\"1\">59.8267</fl>";
  oOut << "<fl c=\"3\">74.4089</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"2\">";
  oOut << "<fl c=\"0\">150.781</fl>";
  oOut << "<fl c=\"1\">106.335</fl>";
  oOut << "<fl c=\"4\">0.811798</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">144.971</fl>";
  oOut << "<fl c=\"1\">132.629</fl>";
  oOut << "<fl c=\"3\">54.6268</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">145.435</fl>";
  oOut << "<fl c=\"1\">139.465</fl>";
  oOut << "<fl c=\"3\">52.8021</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">158.093</fl>";
  oOut << "<fl c=\"1\">19.2749</fl>";
  oOut << "<fl c=\"3\">31.4795</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">159.979</fl>";
  oOut << "<fl c=\"1\">30.7556</fl>";
  oOut << "<fl c=\"3\">43.0118</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">158.862</fl>";
  oOut << "<fl c=\"1\">27.1667</fl>";
  oOut << "<fl c=\"3\">27.3795</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">153.381</fl>";
  oOut << "<fl c=\"1\">46.9849</fl>";
  oOut << "<fl c=\"3\">56.7966</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">152.826</fl>";
  oOut << "<fl c=\"1\">79.187</fl>";
  oOut << "<fl c=\"3\">72.8574</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">159.344</fl>";
  oOut << "<fl c=\"1\">94.5984</fl>";
  oOut << "<fl c=\"3\">87.8442</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">158.649</fl>";
  oOut << "<fl c=\"1\">88.8489</fl>";
  oOut << "<fl c=\"3\">21.088</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">152.411</fl>";
  oOut << "<fl c=\"1\">103.461</fl>";
  oOut << "<fl c=\"3\">10.2267</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">156.653</fl>";
  oOut << "<fl c=\"1\">138.177</fl>";
  oOut << "<fl c=\"3\">69.1437</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">157.068</fl>";
  oOut << "<fl c=\"1\">167.993</fl>";
  oOut << "<fl c=\"3\">55.6335</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">165.112</fl>";
  oOut << "<fl c=\"1\">6.23779</fl>";
  oOut << "<fl c=\"3\">77.269</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">164.618</fl>";
  oOut << "<fl c=\"1\">6.66504</fl>";
  oOut << "<fl c=\"3\">50.9534</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"2\">";
  oOut << "<fl c=\"0\">167.108</fl>";
  oOut << "<fl c=\"1\">63.3179</fl>";
  oOut << "<fl c=\"4\">0.861176</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">163.428</fl>";
  oOut << "<fl c=\"1\">69.2322</fl>";
  oOut << "<fl c=\"3\">80.8011</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">162.646</fl>";
  oOut << "<fl c=\"1\">91.8396</fl>";
  oOut << "<fl c=\"3\">48.5281</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">163.263</fl>";
  oOut << "<fl c=\"1\">96.637</fl>";
  oOut << "<fl c=\"3\">53.6926</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"2\">";
  oOut << "<fl c=\"0\">166.931</fl>";
  oOut << "<fl c=\"1\">109.326</fl>";
  oOut << "<fl c=\"4\">9.09665</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"2\">";
  oOut << "<fl c=\"0\">163.336</fl>";
  oOut << "<fl c=\"1\">118.28</fl>";
  oOut << "<fl c=\"4\">4.1929</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"2\">";
  oOut << "<fl c=\"0\">166.156</fl>";
  oOut << "<fl c=\"1\">132.892</fl>";
  oOut << "<fl c=\"4\">0.0366211</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">162.836</fl>";
  oOut << "<fl c=\"1\">182.41</fl>";
  oOut << "<fl c=\"3\">21.3763</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"2\">";
  oOut << "<fl c=\"0\">163.055</fl>";
  oOut << "<fl c=\"1\">177.161</fl>";
  oOut << "<fl c=\"4\">8.86896</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">175.232</fl>";
  oOut << "<fl c=\"1\">20.4346</fl>";
  oOut << "<fl c=\"3\">13.7842</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"2\">";
  oOut << "<fl c=\"0\">172.07</fl>";
  oOut << "<fl c=\"1\">42.9016</fl>";
  oOut << "<fl c=\"4\">9.2337</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"2\">";
  oOut << "<fl c=\"0\">173.645</fl>";
  oOut << "<fl c=\"1\">45.1538</fl>";
  oOut << "<fl c=\"4\">3.62161</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">168.28</fl>";
  oOut << "<fl c=\"1\">64.1663</fl>";
  oOut << "<fl c=\"3\">26.7511</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"2\">";
  oOut << "<fl c=\"0\">169.855</fl>";
  oOut << "<fl c=\"1\">85.144</fl>";
  oOut << "<fl c=\"4\">0.415985</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">169.067</fl>";
  oOut << "<fl c=\"1\">93.3716</fl>";
  oOut << "<fl c=\"3\">53.6044</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">172.223</fl>";
  oOut << "<fl c=\"1\">99.8901</fl>";
  oOut << "<fl c=\"3\">48.6642</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">168.439</fl>";
  oOut << "<fl c=\"1\">151.617</fl>";
  oOut << "<fl c=\"3\">62.8882</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">173.145</fl>";
  oOut << "<fl c=\"1\">197.058</fl>";
  oOut << "<fl c=\"3\">39.7839</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">182.666</fl>";
  oOut << "<fl c=\"1\">31.0364</fl>";
  oOut << "<fl c=\"3\">99.1422</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">180.969</fl>";
  oOut << "<fl c=\"1\">34.4299</fl>";
  oOut << "<fl c=\"3\">20.3699</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">178.149</fl>";
  oOut << "<fl c=\"1\">90.387</fl>";
  oOut << "<fl c=\"3\">93.0936</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">180.182</fl>";
  oOut << "<fl c=\"1\">137.433</fl>";
  oOut << "<fl c=\"3\">77.641</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">187.305</fl>";
  oOut << "<fl c=\"1\">1.47095</fl>";
  oOut << "<fl c=\"3\">53.0481</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"2\">";
  oOut << "<fl c=\"0\">187.701</fl>";
  oOut << "<fl c=\"1\">35.4858</fl>";
  oOut << "<fl c=\"4\">2.66635</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">189.679</fl>";
  oOut << "<fl c=\"1\">53.5522</fl>";
  oOut << "<fl c=\"3\">57.0847</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">187.891</fl>";
  oOut << "<fl c=\"1\">122.107</fl>";
  oOut << "<fl c=\"3\">24.4714</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">191.016</fl>";
  oOut << "<fl c=\"1\">152.826</fl>";
  oOut << "<fl c=\"3\">26.9931</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"2\">";
  oOut << "<fl c=\"0\">186.493</fl>";
  oOut << "<fl c=\"1\">180.328</fl>";
  oOut << "<fl c=\"4\">1.42545</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">196.808</fl>";
  oOut << "<fl c=\"1\">11.8042</fl>";
  oOut << "<fl c=\"3\">66.4471</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">193.86</fl>";
  oOut << "<fl c=\"1\">21.5759</fl>";
  oOut << "<fl c=\"3\">45.4996</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"2\">";
  oOut << "<fl c=\"0\">195.807</fl>";
  oOut << "<fl c=\"1\">31.6833</fl>";
  oOut << "<fl c=\"4\">1.76712</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">197.638</fl>";
  oOut << "<fl c=\"1\">82.7454</fl>";
  oOut << "<fl c=\"3\">38.5001</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">195.447</fl>";
  oOut << "<fl c=\"1\">85.9009</fl>";
  oOut << "<fl c=\"3\">18.4143</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"3\">";
  oOut << "<fl c=\"0\">194.012</fl>";
  oOut << "<fl c=\"1\">124.323</fl>";
  oOut << "<fl c=\"3\">16.3382</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"6\" tp=\"2\">";
  oOut << "<fl c=\"0\">199.139</fl>";
  oOut << "<fl c=\"1\">177.905</fl>";
  oOut << "<fl c=\"4\">0.428986</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">2.56348</fl>";
  oOut << "<fl c=\"1\">3.32031</fl>";
  oOut << "<fl c=\"3\">81.0385</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">0.219727</fl>";
  oOut << "<fl c=\"1\">45.8801</fl>";
  oOut << "<fl c=\"3\">35.4169</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">1.64795</fl>";
  oOut << "<fl c=\"1\">40.0024</fl>";
  oOut << "<fl c=\"3\">14.0027</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">4.99268</fl>";
  oOut << "<fl c=\"1\">55.3345</fl>";
  oOut << "<fl c=\"3\">45.7504</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">0.787354</fl>";
  oOut << "<fl c=\"1\">67.4988</fl>";
  oOut << "<fl c=\"3\">27.9898</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">3.16772</fl>";
  oOut << "<fl c=\"1\">93.3289</fl>";
  oOut << "<fl c=\"3\">41.7413</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">5.82275</fl>";
  oOut << "<fl c=\"1\">133.191</fl>";
  oOut << "<fl c=\"3\">48.324</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">15.5945</fl>";
  oOut << "<fl c=\"1\">8.71582</fl>";
  oOut << "<fl c=\"3\">35.4047</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">13.9404</fl>";
  oOut << "<fl c=\"1\">10.8521</fl>";
  oOut << "<fl c=\"3\">32.908</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">14.5996</fl>";
  oOut << "<fl c=\"1\">24.8596</fl>";
  oOut << "<fl c=\"3\">22.7774</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">15.1917</fl>";
  oOut << "<fl c=\"1\">47.8943</fl>";
  oOut << "<fl c=\"3\">74.4922</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">12.5977</fl>";
  oOut << "<fl c=\"1\">57.0618</fl>";
  oOut << "<fl c=\"3\">13.3527</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">14.74</fl>";
  oOut << "<fl c=\"1\">69.5496</fl>";
  oOut << "<fl c=\"3\">88.5971</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">13.9832</fl>";
  oOut << "<fl c=\"1\">81.7261</fl>";
  oOut << "<fl c=\"3\">89.7568</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">11.438</fl>";
  oOut << "<fl c=\"1\">125.458</fl>";
  oOut << "<fl c=\"3\">98.4561</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">12.2986</fl>";
  oOut << "<fl c=\"1\">141.968</fl>";
  oOut << "<fl c=\"3\">62.8226</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">12.5366</fl>";
  oOut << "<fl c=\"1\">137.823</fl>";
  oOut << "<fl c=\"3\">36.8817</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">19.9097</fl>";
  oOut << "<fl c=\"1\">3.38745</fl>";
  oOut << "<fl c=\"3\">31.9836</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">23.761</fl>";
  oOut << "<fl c=\"1\">15.1794</fl>";
  oOut << "<fl c=\"3\">11.3443</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">20.3247</fl>";
  oOut << "<fl c=\"1\">62.5305</fl>";
  oOut << "<fl c=\"3\">98.9093</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"2\">";
  oOut << "<fl c=\"0\">23.5413</fl>";
  oOut << "<fl c=\"1\">71.1609</fl>";
  oOut << "<fl c=\"4\">8.28915</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">19.8853</fl>";
  oOut << "<fl c=\"1\">77.2583</fl>";
  oOut << "<fl c=\"3\">95.2591</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"2\">";
  oOut << "<fl c=\"0\">16.2354</fl>";
  oOut << "<fl c=\"1\">85.6934</fl>";
  oOut << "<fl c=\"4\">9.67151</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">16.4734</fl>";
  oOut << "<fl c=\"1\">92.1997</fl>";
  oOut << "<fl c=\"3\">82.793</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">16.5405</fl>";
  oOut << "<fl c=\"1\">90.6494</fl>";
  oOut << "<fl c=\"3\">56.8857</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">23.9258</fl>";
  oOut << "<fl c=\"1\">92.3828</fl>";
  oOut << "<fl c=\"3\">41.0281</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">17.4561</fl>";
  oOut << "<fl c=\"1\">91.6382</fl>";
  oOut << "<fl c=\"3\">20.9769</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">21.3989</fl>";
  oOut << "<fl c=\"1\">145.013</fl>";
  oOut << "<fl c=\"3\">68.8904</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">19.0491</fl>";
  oOut << "<fl c=\"1\">175.604</fl>";
  oOut << "<fl c=\"3\">76.1057</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">25.1953</fl>";
  oOut << "<fl c=\"1\">8.25806</fl>";
  oOut << "<fl c=\"3\">23.8806</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">30.6702</fl>";
  oOut << "<fl c=\"1\">74.1028</fl>";
  oOut << "<fl c=\"3\">53.6279</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">28.0701</fl>";
  oOut << "<fl c=\"1\">92.3279</fl>";
  oOut << "<fl c=\"3\">12.6581</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">30.8899</fl>";
  oOut << "<fl c=\"1\">158.6</fl>";
  oOut << "<fl c=\"3\">60.6219</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"2\">";
  oOut << "<fl c=\"0\">27.4841</fl>";
  oOut << "<fl c=\"1\">157.66</fl>";
  oOut << "<fl c=\"4\">2.82016</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">29.9255</fl>";
  oOut << "<fl c=\"1\">171.478</fl>";
  oOut << "<fl c=\"3\">40.2176</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">39.2273</fl>";
  oOut << "<fl c=\"1\">1.5686</fl>";
  oOut << "<fl c=\"3\">77.5317</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">33.5754</fl>";
  oOut << "<fl c=\"1\">2.94189</fl>";
  oOut << "<fl c=\"3\">75.2295</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">34.4727</fl>";
  oOut << "<fl c=\"1\">9.57642</fl>";
  oOut << "<fl c=\"3\">16.236</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">34.1431</fl>";
  oOut << "<fl c=\"1\">24.7314</fl>";
  oOut << "<fl c=\"3\">29.3539</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">39.3311</fl>";
  oOut << "<fl c=\"1\">55.3711</fl>";
  oOut << "<fl c=\"3\">36.2152</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">33.4961</fl>";
  oOut << "<fl c=\"1\">91.2659</fl>";
  oOut << "<fl c=\"3\">83.3459</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">34.1492</fl>";
  oOut << "<fl c=\"1\">101.831</fl>";
  oOut << "<fl c=\"3\">62.3999</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"2\">";
  oOut << "<fl c=\"0\">34.9731</fl>";
  oOut << "<fl c=\"1\">135.425</fl>";
  oOut << "<fl c=\"4\">3.9935</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">35.321</fl>";
  oOut << "<fl c=\"1\">140.399</fl>";
  oOut << "<fl c=\"3\">51.4484</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"2\">";
  oOut << "<fl c=\"0\">33.6365</fl>";
  oOut << "<fl c=\"1\">136.755</fl>";
  oOut << "<fl c=\"4\">0.909607</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">40.5151</fl>";
  oOut << "<fl c=\"1\">1.25732</fl>";
  oOut << "<fl c=\"3\">99.7537</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">47.229</fl>";
  oOut << "<fl c=\"1\">1.01318</fl>";
  oOut << "<fl c=\"3\">74.4885</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">42.7368</fl>";
  oOut << "<fl c=\"1\">6.03027</fl>";
  oOut << "<fl c=\"3\">11.554</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">40.8142</fl>";
  oOut << "<fl c=\"1\">30.3772</fl>";
  oOut << "<fl c=\"3\">65.5768</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">44.6777</fl>";
  oOut << "<fl c=\"1\">98.0713</fl>";
  oOut << "<fl c=\"3\">72.7951</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">45.8984</fl>";
  oOut << "<fl c=\"1\">118.671</fl>";
  oOut << "<fl c=\"3\">86.7035</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">45.7031</fl>";
  oOut << "<fl c=\"1\">148.761</fl>";
  oOut << "<fl c=\"3\">18.15</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">55.0842</fl>";
  oOut << "<fl c=\"1\">19.7021</fl>";
  oOut << "<fl c=\"3\">44.234</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">55.6091</fl>";
  oOut << "<fl c=\"1\">58.1726</fl>";
  oOut << "<fl c=\"3\">31.3901</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">48.1873</fl>";
  oOut << "<fl c=\"1\">91.0522</fl>";
  oOut << "<fl c=\"3\">61.1679</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">53.4119</fl>";
  oOut << "<fl c=\"1\">133.685</fl>";
  oOut << "<fl c=\"3\">21.7035</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"2\">";
  oOut << "<fl c=\"0\">53.9185</fl>";
  oOut << "<fl c=\"1\">142.413</fl>";
  oOut << "<fl c=\"4\">5.11191</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">50.0549</fl>";
  oOut << "<fl c=\"1\">151.318</fl>";
  oOut << "<fl c=\"3\">81.6479</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"2\">";
  oOut << "<fl c=\"0\">49.6765</fl>";
  oOut << "<fl c=\"1\">185.339</fl>";
  oOut << "<fl c=\"4\">4.40961</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"2\">";
  oOut << "<fl c=\"0\">48.645</fl>";
  oOut << "<fl c=\"1\">185.901</fl>";
  oOut << "<fl c=\"4\">0.229431</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"2\">";
  oOut << "<fl c=\"0\">63.0615</fl>";
  oOut << "<fl c=\"1\">5.57251</fl>";
  oOut << "<fl c=\"4\">6.9892</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">59.9121</fl>";
  oOut << "<fl c=\"1\">43.5486</fl>";
  oOut << "<fl c=\"3\">55.2185</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"2\">";
  oOut << "<fl c=\"0\">61.3159</fl>";
  oOut << "<fl c=\"1\">79.4617</fl>";
  oOut << "<fl c=\"4\">0.645508</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">58.3008</fl>";
  oOut << "<fl c=\"1\">110.004</fl>";
  oOut << "<fl c=\"3\">27.5644</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">63.6658</fl>";
  oOut << "<fl c=\"1\">117.535</fl>";
  oOut << "<fl c=\"3\">27.6804</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">62.9272</fl>";
  oOut << "<fl c=\"1\">129.254</fl>";
  oOut << "<fl c=\"3\">67.3154</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">57.6721</fl>";
  oOut << "<fl c=\"1\">156.47</fl>";
  oOut << "<fl c=\"3\">63.7732</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"2\">";
  oOut << "<fl c=\"0\">63.9221</fl>";
  oOut << "<fl c=\"1\">156.024</fl>";
  oOut << "<fl c=\"4\">0.684662</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">59.2651</fl>";
  oOut << "<fl c=\"1\">163.947</fl>";
  oOut << "<fl c=\"3\">67.9419</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">61.5967</fl>";
  oOut << "<fl c=\"1\">179.272</fl>";
  oOut << "<fl c=\"3\">82.3923</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">58.2031</fl>";
  oOut << "<fl c=\"1\">179.614</fl>";
  oOut << "<fl c=\"3\">58.6664</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"2\">";
  oOut << "<fl c=\"0\">61.7615</fl>";
  oOut << "<fl c=\"1\">186.346</fl>";
  oOut << "<fl c=\"4\">0.64975</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">71.3989</fl>";
  oOut << "<fl c=\"1\">1.0376</fl>";
  oOut << "<fl c=\"3\">83.0286</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">65.6555</fl>";
  oOut << "<fl c=\"1\">58.7036</fl>";
  oOut << "<fl c=\"3\">98.0389</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"2\">";
  oOut << "<fl c=\"0\">65.5029</fl>";
  oOut << "<fl c=\"1\">78.3325</fl>";
  oOut << "<fl c=\"4\">0.939056</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">66.5771</fl>";
  oOut << "<fl c=\"1\">138.971</fl>";
  oOut << "<fl c=\"3\">32.3862</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">71.0815</fl>";
  oOut << "<fl c=\"1\">154.559</fl>";
  oOut << "<fl c=\"3\">76.2024</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">64.032</fl>";
  oOut << "<fl c=\"1\">191.76</fl>";
  oOut << "<fl c=\"3\">54.3472</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">76.5259</fl>";
  oOut << "<fl c=\"1\">24.2798</fl>";
  oOut << "<fl c=\"3\">84.267</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">74.4019</fl>";
  oOut << "<fl c=\"1\">28.4668</fl>";
  oOut << "<fl c=\"3\">36.2466</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">75.7385</fl>";
  oOut << "<fl c=\"1\">42.2424</fl>";
  oOut << "<fl c=\"3\">86.3916</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">79.6753</fl>";
  oOut << "<fl c=\"1\">55.2795</fl>";
  oOut << "<fl c=\"3\">55.0473</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">72.3022</fl>";
  oOut << "<fl c=\"1\">81.4941</fl>";
  oOut << "<fl c=\"3\">35.6067</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">72.0642</fl>";
  oOut << "<fl c=\"1\">117.883</fl>";
  oOut << "<fl c=\"3\">26.2115</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">79.6997</fl>";
  oOut << "<fl c=\"1\">125.714</fl>";
  oOut << "<fl c=\"3\">28.9337</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"2\">";
  oOut << "<fl c=\"0\">74.3042</fl>";
  oOut << "<fl c=\"1\">134.143</fl>";
  oOut << "<fl c=\"4\">0.608917</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">74.4446</fl>";
  oOut << "<fl c=\"1\">156.177</fl>";
  oOut << "<fl c=\"3\">79.3045</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">79.364</fl>";
  oOut << "<fl c=\"1\">155.511</fl>";
  oOut << "<fl c=\"3\">44.292</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">79.0039</fl>";
  oOut << "<fl c=\"1\">171.674</fl>";
  oOut << "<fl c=\"3\">58.4454</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"2\">";
  oOut << "<fl c=\"0\">75.6226</fl>";
  oOut << "<fl c=\"1\">176.874</fl>";
  oOut << "<fl c=\"4\">3.02423</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">73.6084</fl>";
  oOut << "<fl c=\"1\">195.618</fl>";
  oOut << "<fl c=\"3\">33.4982</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">83.5144</fl>";
  oOut << "<fl c=\"1\">38.0371</fl>";
  oOut << "<fl c=\"3\">83.0032</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">87.6953</fl>";
  oOut << "<fl c=\"1\">81.134</fl>";
  oOut << "<fl c=\"3\">49.6982</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"2\">";
  oOut << "<fl c=\"0\">84.3872</fl>";
  oOut << "<fl c=\"1\">111.719</fl>";
  oOut << "<fl c=\"4\">8.40561</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">86.2732</fl>";
  oOut << "<fl c=\"1\">125.58</fl>";
  oOut << "<fl c=\"3\">15.8063</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">86.499</fl>";
  oOut << "<fl c=\"1\">142.761</fl>";
  oOut << "<fl c=\"3\">74.6835</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">81.0852</fl>";
  oOut << "<fl c=\"1\">148.718</fl>";
  oOut << "<fl c=\"3\">20.3546</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">82.9712</fl>";
  oOut << "<fl c=\"1\">168.25</fl>";
  oOut << "<fl c=\"3\">78.5931</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">90.1978</fl>";
  oOut << "<fl c=\"1\">17.0593</fl>";
  oOut << "<fl c=\"3\">25.4025</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">88.6719</fl>";
  oOut << "<fl c=\"1\">44.9219</fl>";
  oOut << "<fl c=\"3\">32.778</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"2\">";
  oOut << "<fl c=\"0\">91.6382</fl>";
  oOut << "<fl c=\"1\">69.7205</fl>";
  oOut << "<fl c=\"4\">6.5448</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">88.3423</fl>";
  oOut << "<fl c=\"1\">94.2505</fl>";
  oOut << "<fl c=\"3\">70.7693</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"2\">";
  oOut << "<fl c=\"0\">90.0757</fl>";
  oOut << "<fl c=\"1\">102.545</fl>";
  oOut << "<fl c=\"4\">2.8306</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">92.2241</fl>";
  oOut << "<fl c=\"1\">138.77</fl>";
  oOut << "<fl c=\"3\">27.1899</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">91.4368</fl>";
  oOut << "<fl c=\"1\">166.034</fl>";
  oOut << "<fl c=\"3\">48.9731</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">88.7085</fl>";
  oOut << "<fl c=\"1\">198.462</fl>";
  oOut << "<fl c=\"3\">69.1141</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">101.215</fl>";
  oOut << "<fl c=\"1\">69.3787</fl>";
  oOut << "<fl c=\"3\">27.0917</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">103.717</fl>";
  oOut << "<fl c=\"1\">79.126</fl>";
  oOut << "<fl c=\"3\">99.3433</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">100.623</fl>";
  oOut << "<fl c=\"1\">84.0332</fl>";
  oOut << "<fl c=\"3\">43.4229</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"2\">";
  oOut << "<fl c=\"0\">101.794</fl>";
  oOut << "<fl c=\"1\">89.1479</fl>";
  oOut << "<fl c=\"4\">0.550873</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">103.967</fl>";
  oOut << "<fl c=\"1\">105.011</fl>";
  oOut << "<fl c=\"3\">69.2117</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">96.167</fl>";
  oOut << "<fl c=\"1\">141.113</fl>";
  oOut << "<fl c=\"3\">73.5562</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">102.179</fl>";
  oOut << "<fl c=\"1\">175.494</fl>";
  oOut << "<fl c=\"3\">64.5978</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">101.44</fl>";
  oOut << "<fl c=\"1\">168.256</fl>";
  oOut << "<fl c=\"3\">11.0999</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">100.494</fl>";
  oOut << "<fl c=\"1\">189.032</fl>";
  oOut << "<fl c=\"3\">93.3023</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">103.162</fl>";
  oOut << "<fl c=\"1\">195.148</fl>";
  oOut << "<fl c=\"3\">97.3697</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">110.51</fl>";
  oOut << "<fl c=\"1\">14.1785</fl>";
  oOut << "<fl c=\"3\">93.4778</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">110.028</fl>";
  oOut << "<fl c=\"1\">45.0562</fl>";
  oOut << "<fl c=\"3\">94.0613</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">105.475</fl>";
  oOut << "<fl c=\"1\">52.0325</fl>";
  oOut << "<fl c=\"3\">14.0408</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">107.245</fl>";
  oOut << "<fl c=\"1\">60.5713</fl>";
  oOut << "<fl c=\"3\">83.793</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">107.703</fl>";
  oOut << "<fl c=\"1\">69.2688</fl>";
  oOut << "<fl c=\"3\">50.4846</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">104.352</fl>";
  oOut << "<fl c=\"1\">93.1213</fl>";
  oOut << "<fl c=\"3\">56.4578</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">110.443</fl>";
  oOut << "<fl c=\"1\">100.873</fl>";
  oOut << "<fl c=\"3\">32.5668</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">108.905</fl>";
  oOut << "<fl c=\"1\">108.27</fl>";
  oOut << "<fl c=\"3\">15.2609</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">104.382</fl>";
  oOut << "<fl c=\"1\">122.729</fl>";
  oOut << "<fl c=\"3\">94.2108</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">116.351</fl>";
  oOut << "<fl c=\"1\">5.57861</fl>";
  oOut << "<fl c=\"3\">52.0169</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"2\">";
  oOut << "<fl c=\"0\">116.187</fl>";
  oOut << "<fl c=\"1\">45.4407</fl>";
  oOut << "<fl c=\"4\">3.4332</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">114.081</fl>";
  oOut << "<fl c=\"1\">48.2788</fl>";
  oOut << "<fl c=\"3\">36.7883</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">118.622</fl>";
  oOut << "<fl c=\"1\">58.7952</fl>";
  oOut << "<fl c=\"3\">80.9796</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">114.056</fl>";
  oOut << "<fl c=\"1\">73.7549</fl>";
  oOut << "<fl c=\"3\">55.3677</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">117.383</fl>";
  oOut << "<fl c=\"1\">74.0356</fl>";
  oOut << "<fl c=\"3\">54.4992</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">112.17</fl>";
  oOut << "<fl c=\"1\">91.272</fl>";
  oOut << "<fl c=\"3\">48.3426</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"2\">";
  oOut << "<fl c=\"0\">116.29</fl>";
  oOut << "<fl c=\"1\">108.911</fl>";
  oOut << "<fl c=\"4\">1.14777</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"2\">";
  oOut << "<fl c=\"0\">118.652</fl>";
  oOut << "<fl c=\"1\">119.257</fl>";
  oOut << "<fl c=\"4\">0.0487366</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">116.309</fl>";
  oOut << "<fl c=\"1\">128.229</fl>";
  oOut << "<fl c=\"3\">20.4834</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">118.561</fl>";
  oOut << "<fl c=\"1\">174.622</fl>";
  oOut << "<fl c=\"3\">99.7858</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">113.153</fl>";
  oOut << "<fl c=\"1\">185.101</fl>";
  oOut << "<fl c=\"3\">42.6974</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">123.12</fl>";
  oOut << "<fl c=\"1\">8.89893</fl>";
  oOut << "<fl c=\"3\">30.7855</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"2\">";
  oOut << "<fl c=\"0\">124.615</fl>";
  oOut << "<fl c=\"1\">22.2351</fl>";
  oOut << "<fl c=\"4\">0.34201</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">125.494</fl>";
  oOut << "<fl c=\"1\">28.9612</fl>";
  oOut << "<fl c=\"3\">66.8323</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">125.69</fl>";
  oOut << "<fl c=\"1\">69.9341</fl>";
  oOut << "<fl c=\"3\">93.0127</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"2\">";
  oOut << "<fl c=\"0\">123.56</fl>";
  oOut << "<fl c=\"1\">78.5156</fl>";
  oOut << "<fl c=\"4\">0.172089</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">124.591</fl>";
  oOut << "<fl c=\"1\">81.5063</fl>";
  oOut << "<fl c=\"3\">68.0316</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">123.523</fl>";
  oOut << "<fl c=\"1\">127.551</fl>";
  oOut << "<fl c=\"3\">48.0554</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">130.383</fl>";
  oOut << "<fl c=\"1\">8.25806</fl>";
  oOut << "<fl c=\"3\">14.5316</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">129.364</fl>";
  oOut << "<fl c=\"1\">27.5696</fl>";
  oOut << "<fl c=\"3\">65.1251</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"2\">";
  oOut << "<fl c=\"0\">128.455</fl>";
  oOut << "<fl c=\"1\">81.2683</fl>";
  oOut << "<fl c=\"4\">6.38962</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">130.975</fl>";
  oOut << "<fl c=\"1\">119.8</fl>";
  oOut << "<fl c=\"3\">90.4337</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">129.846</fl>";
  oOut << "<fl c=\"1\">120.319</fl>";
  oOut << "<fl c=\"3\">56.9186</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">131.708</fl>";
  oOut << "<fl c=\"1\">131.744</fl>";
  oOut << "<fl c=\"3\">96.8665</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"2\">";
  oOut << "<fl c=\"0\">131.604</fl>";
  oOut << "<fl c=\"1\">131.256</fl>";
  oOut << "<fl c=\"4\">0.497559</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"2\">";
  oOut << "<fl c=\"0\">128.455</fl>";
  oOut << "<fl c=\"1\">168.915</fl>";
  oOut << "<fl c=\"4\">2.23047</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">134.583</fl>";
  oOut << "<fl c=\"1\">189.154</fl>";
  oOut << "<fl c=\"3\">98.3527</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">143.707</fl>";
  oOut << "<fl c=\"1\">1.84326</fl>";
  oOut << "<fl c=\"3\">22.4844</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">141.565</fl>";
  oOut << "<fl c=\"1\">19.6045</fl>";
  oOut << "<fl c=\"3\">75.9677</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">138.562</fl>";
  oOut << "<fl c=\"1\">31.9702</fl>";
  oOut << "<fl c=\"3\">75.3711</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">139.978</fl>";
  oOut << "<fl c=\"1\">34.3323</fl>";
  oOut << "<fl c=\"3\">55.0888</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">142.212</fl>";
  oOut << "<fl c=\"1\">46.0266</fl>";
  oOut << "<fl c=\"3\">83.5941</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">141.913</fl>";
  oOut << "<fl c=\"1\">69.3848</fl>";
  oOut << "<fl c=\"3\">75.8035</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">137.433</fl>";
  oOut << "<fl c=\"1\">96.6553</fl>";
  oOut << "<fl c=\"3\">48.407</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">142.145</fl>";
  oOut << "<fl c=\"1\">156.396</fl>";
  oOut << "<fl c=\"3\">36.8674</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"2\">";
  oOut << "<fl c=\"0\">136.157</fl>";
  oOut << "<fl c=\"1\">189.856</fl>";
  oOut << "<fl c=\"4\">0.82608</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">145.813</fl>";
  oOut << "<fl c=\"1\">10.6445</fl>";
  oOut << "<fl c=\"3\">15.2737</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">146.838</fl>";
  oOut << "<fl c=\"1\">54.0588</fl>";
  oOut << "<fl c=\"3\">82.258</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">146.173</fl>";
  oOut << "<fl c=\"1\">54.4128</fl>";
  oOut << "<fl c=\"3\">36.5878</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">151.428</fl>";
  oOut << "<fl c=\"1\">74.8291</fl>";
  oOut << "<fl c=\"3\">42.7835</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">151.477</fl>";
  oOut << "<fl c=\"1\">111.267</fl>";
  oOut << "<fl c=\"3\">57.7094</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"2\">";
  oOut << "<fl c=\"0\">151.013</fl>";
  oOut << "<fl c=\"1\">115.509</fl>";
  oOut << "<fl c=\"4\">4.13083</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">146.021</fl>";
  oOut << "<fl c=\"1\">128.168</fl>";
  oOut << "<fl c=\"3\">44.3851</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">151.788</fl>";
  oOut << "<fl c=\"1\">147.571</fl>";
  oOut << "<fl c=\"3\">19.4974</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">149.902</fl>";
  oOut << "<fl c=\"1\">158.234</fl>";
  oOut << "<fl c=\"3\">57.074</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">151.636</fl>";
  oOut << "<fl c=\"1\">159.241</fl>";
  oOut << "<fl c=\"3\">28.6996</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">145.392</fl>";
  oOut << "<fl c=\"1\">159.485</fl>";
  oOut << "<fl c=\"3\">28.0591</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">148.651</fl>";
  oOut << "<fl c=\"1\">165.039</fl>";
  oOut << "<fl c=\"3\">16.6522</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">147.797</fl>";
  oOut << "<fl c=\"1\">173.785</fl>";
  oOut << "<fl c=\"3\">56.9458</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">154.205</fl>";
  oOut << "<fl c=\"1\">41.3818</fl>";
  oOut << "<fl c=\"3\">89.675</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">153.912</fl>";
  oOut << "<fl c=\"1\">70.2759</fl>";
  oOut << "<fl c=\"3\">91.6467</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"2\">";
  oOut << "<fl c=\"0\">156.348</fl>";
  oOut << "<fl c=\"1\">80.0415</fl>";
  oOut << "<fl c=\"4\">0.848633</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">159.363</fl>";
  oOut << "<fl c=\"1\">117.859</fl>";
  oOut << "<fl c=\"3\">68.392</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">157.898</fl>";
  oOut << "<fl c=\"1\">150.208</fl>";
  oOut << "<fl c=\"3\">66.5469</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"2\">";
  oOut << "<fl c=\"0\">158.02</fl>";
  oOut << "<fl c=\"1\">156.549</fl>";
  oOut << "<fl c=\"4\">0.346497</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">153.674</fl>";
  oOut << "<fl c=\"1\">165.802</fl>";
  oOut << "<fl c=\"3\">56.8472</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">152.374</fl>";
  oOut << "<fl c=\"1\">171.399</fl>";
  oOut << "<fl c=\"3\">16.7822</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">163.562</fl>";
  oOut << "<fl c=\"1\">17.1753</fl>";
  oOut << "<fl c=\"3\">89.151</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"2\">";
  oOut << "<fl c=\"0\">162.903</fl>";
  oOut << "<fl c=\"1\">96.2952</fl>";
  oOut << "<fl c=\"4\">0.15097</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">166.107</fl>";
  oOut << "<fl c=\"1\">129.706</fl>";
  oOut << "<fl c=\"3\">73.5678</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">163.116</fl>";
  oOut << "<fl c=\"1\">129.626</fl>";
  oOut << "<fl c=\"3\">63.2928</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">165.448</fl>";
  oOut << "<fl c=\"1\">131.079</fl>";
  oOut << "<fl c=\"3\">33.2339</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">167.023</fl>";
  oOut << "<fl c=\"1\">164.008</fl>";
  oOut << "<fl c=\"3\">63.7231</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">174.414</fl>";
  oOut << "<fl c=\"1\">28.6072</fl>";
  oOut << "<fl c=\"3\">14.1321</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"2\">";
  oOut << "<fl c=\"0\">173.566</fl>";
  oOut << "<fl c=\"1\">38.9893</fl>";
  oOut << "<fl c=\"4\">0.278931</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">169.568</fl>";
  oOut << "<fl c=\"1\">60.3699</fl>";
  oOut << "<fl c=\"3\">29.6054</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">172.253</fl>";
  oOut << "<fl c=\"1\">64.6484</fl>";
  oOut << "<fl c=\"3\">74.5413</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">170.679</fl>";
  oOut << "<fl c=\"1\">80.4016</fl>";
  oOut << "<fl c=\"3\">49.603</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">174.286</fl>";
  oOut << "<fl c=\"1\">90.509</fl>";
  oOut << "<fl c=\"3\">69.5895</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">169.94</fl>";
  oOut << "<fl c=\"1\">123.12</fl>";
  oOut << "<fl c=\"3\">93.4375</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"2\">";
  oOut << "<fl c=\"0\">170.673</fl>";
  oOut << "<fl c=\"1\">140.796</fl>";
  oOut << "<fl c=\"4\">2.70782</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">172.394</fl>";
  oOut << "<fl c=\"1\">189.41</fl>";
  oOut << "<fl c=\"3\">15.2454</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">178.192</fl>";
  oOut << "<fl c=\"1\">8.5022</fl>";
  oOut << "<fl c=\"3\">94.3698</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">177.948</fl>";
  oOut << "<fl c=\"1\">28.5034</fl>";
  oOut << "<fl c=\"3\">89.4879</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">179.376</fl>";
  oOut << "<fl c=\"1\">68.2251</fl>";
  oOut << "<fl c=\"3\">76.9028</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"2\">";
  oOut << "<fl c=\"0\">183.929</fl>";
  oOut << "<fl c=\"1\">64.801</fl>";
  oOut << "<fl c=\"4\">2.5661</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"2\">";
  oOut << "<fl c=\"0\">178.711</fl>";
  oOut << "<fl c=\"1\">82.0801</fl>";
  oOut << "<fl c=\"4\">8.35233</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">181.915</fl>";
  oOut << "<fl c=\"1\">108.014</fl>";
  oOut << "<fl c=\"3\">13.0212</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"2\">";
  oOut << "<fl c=\"0\">181.238</fl>";
  oOut << "<fl c=\"1\">143.158</fl>";
  oOut << "<fl c=\"4\">0.497375</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">178.015</fl>";
  oOut << "<fl c=\"1\">145.557</fl>";
  oOut << "<fl c=\"3\">29.0265</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"2\">";
  oOut << "<fl c=\"0\">190.442</fl>";
  oOut << "<fl c=\"1\">10.1807</fl>";
  oOut << "<fl c=\"4\">0.321686</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"2\">";
  oOut << "<fl c=\"0\">187.518</fl>";
  oOut << "<fl c=\"1\">38.5193</fl>";
  oOut << "<fl c=\"4\">3.17722</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">190.71</fl>";
  oOut << "<fl c=\"1\">41.2842</fl>";
  oOut << "<fl c=\"3\">43.7674</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">186.792</fl>";
  oOut << "<fl c=\"1\">65.094</fl>";
  oOut << "<fl c=\"3\">79.3137</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">190.338</fl>";
  oOut << "<fl c=\"1\">98.6755</fl>";
  oOut << "<fl c=\"3\">90.4568</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">186.261</fl>";
  oOut << "<fl c=\"1\">138.251</fl>";
  oOut << "<fl c=\"3\">59.8105</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">189.398</fl>";
  oOut << "<fl c=\"1\">176.599</fl>";
  oOut << "<fl c=\"3\">30.3769</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">192.169</fl>";
  oOut << "<fl c=\"1\">17.4316</fl>";
  oOut << "<fl c=\"3\">82.8525</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">198.553</fl>";
  oOut << "<fl c=\"1\">24.9939</fl>";
  oOut << "<fl c=\"3\">45.6174</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">193.536</fl>";
  oOut << "<fl c=\"1\">58.7708</fl>";
  oOut << "<fl c=\"3\">30.9601</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">197.449</fl>";
  oOut << "<fl c=\"1\">105.103</fl>";
  oOut << "<fl c=\"3\">10.715</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">192.914</fl>";
  oOut << "<fl c=\"1\">129.59</fl>";
  oOut << "<fl c=\"3\">41.3763</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"2\">";
  oOut << "<fl c=\"0\">196.216</fl>";
  oOut << "<fl c=\"1\">170.532</fl>";
  oOut << "<fl c=\"4\">0.199738</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"5\" tp=\"3\">";
  oOut << "<fl c=\"0\">193.878</fl>";
  oOut << "<fl c=\"1\">178.723</fl>";
  oOut << "<fl c=\"3\">75.2042</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">0.616455</fl>";
  oOut << "<fl c=\"1\">32.3242</fl>";
  oOut << "<fl c=\"3\">83.2599</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"2\">";
  oOut << "<fl c=\"0\">5.07812</fl>";
  oOut << "<fl c=\"1\">35.9253</fl>";
  oOut << "<fl c=\"4\">8.2897</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"2\">";
  oOut << "<fl c=\"0\">2.44751</fl>";
  oOut << "<fl c=\"1\">74.7803</fl>";
  oOut << "<fl c=\"4\">0.254028</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">13.7268</fl>";
  oOut << "<fl c=\"1\">27.3499</fl>";
  oOut << "<fl c=\"3\">52.3059</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">12.4146</fl>";
  oOut << "<fl c=\"1\">95.8923</fl>";
  oOut << "<fl c=\"3\">44.3427</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">11.3342</fl>";
  oOut << "<fl c=\"1\">101.404</fl>";
  oOut << "<fl c=\"3\">67.2638</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">13.4766</fl>";
  oOut << "<fl c=\"1\">107.52</fl>";
  oOut << "<fl c=\"3\">13.0441</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"2\">";
  oOut << "<fl c=\"0\">15.9302</fl>";
  oOut << "<fl c=\"1\">116.821</fl>";
  oOut << "<fl c=\"4\">6.53436</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"2\">";
  oOut << "<fl c=\"0\">14.7034</fl>";
  oOut << "<fl c=\"1\">116.223</fl>";
  oOut << "<fl c=\"4\">0.612091</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">13.8489</fl>";
  oOut << "<fl c=\"1\">137.787</fl>";
  oOut << "<fl c=\"3\">92.0599</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">11.5845</fl>";
  oOut << "<fl c=\"1\">143.164</fl>";
  oOut << "<fl c=\"3\">52.6022</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">14.6912</fl>";
  oOut << "<fl c=\"1\">161.993</fl>";
  oOut << "<fl c=\"3\">74.678</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">13.562</fl>";
  oOut << "<fl c=\"1\">166.565</fl>";
  oOut << "<fl c=\"3\">39.4263</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">8.37402</fl>";
  oOut << "<fl c=\"1\">170.959</fl>";
  oOut << "<fl c=\"3\">72.4911</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"2\">";
  oOut << "<fl c=\"0\">15.3992</fl>";
  oOut << "<fl c=\"1\">184.686</fl>";
  oOut << "<fl c=\"4\">4.49612</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">8.88062</fl>";
  oOut << "<fl c=\"1\">193.494</fl>";
  oOut << "<fl c=\"3\">48.1726</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">18.6279</fl>";
  oOut << "<fl c=\"1\">22.4121</fl>";
  oOut << "<fl c=\"3\">45.2301</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">19.3359</fl>";
  oOut << "<fl c=\"1\">27.6611</fl>";
  oOut << "<fl c=\"3\">56.33</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"2\">";
  oOut << "<fl c=\"0\">19.7205</fl>";
  oOut << "<fl c=\"1\">37.6526</fl>";
  oOut << "<fl c=\"4\">0.187897</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">20.5322</fl>";
  oOut << "<fl c=\"1\">41.9495</fl>";
  oOut << "<fl c=\"3\">68.107</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">19.5801</fl>";
  oOut << "<fl c=\"1\">106.049</fl>";
  oOut << "<fl c=\"3\">95.8258</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">18.3655</fl>";
  oOut << "<fl c=\"1\">106.775</fl>";
  oOut << "<fl c=\"3\">29.8276</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">21.106</fl>";
  oOut << "<fl c=\"1\">151.831</fl>";
  oOut << "<fl c=\"3\">12.1777</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">21.4905</fl>";
  oOut << "<fl c=\"1\">195.148</fl>";
  oOut << "<fl c=\"3\">36.3278</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">27.5635</fl>";
  oOut << "<fl c=\"1\">7.47681</fl>";
  oOut << "<fl c=\"3\">37.9514</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"2\">";
  oOut << "<fl c=\"0\">30.9509</fl>";
  oOut << "<fl c=\"1\">15.1672</fl>";
  oOut << "<fl c=\"4\">0.77301</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">30.957</fl>";
  oOut << "<fl c=\"1\">52.1729</fl>";
  oOut << "<fl c=\"3\">75.0894</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">28.3142</fl>";
  oOut << "<fl c=\"1\">53.8513</fl>";
  oOut << "<fl c=\"3\">36.8625</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"2\">";
  oOut << "<fl c=\"0\">26.7334</fl>";
  oOut << "<fl c=\"1\">116.461</fl>";
  oOut << "<fl c=\"4\">9.74869</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"2\">";
  oOut << "<fl c=\"0\">28.5889</fl>";
  oOut << "<fl c=\"1\">119.635</fl>";
  oOut << "<fl c=\"4\">4.46454</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">27.0752</fl>";
  oOut << "<fl c=\"1\">166.302</fl>";
  oOut << "<fl c=\"3\">43.7372</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">26.0254</fl>";
  oOut << "<fl c=\"1\">196.973</fl>";
  oOut << "<fl c=\"3\">13.8882</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">32.3914</fl>";
  oOut << "<fl c=\"1\">38.4583</fl>";
  oOut << "<fl c=\"3\">46.4084</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">33.7524</fl>";
  oOut << "<fl c=\"1\">49.9756</fl>";
  oOut << "<fl c=\"3\">93.7857</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">39.9719</fl>";
  oOut << "<fl c=\"1\">77.1362</fl>";
  oOut << "<fl c=\"3\">66.9708</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">38.9587</fl>";
  oOut << "<fl c=\"1\">101.501</fl>";
  oOut << "<fl c=\"3\">82.6611</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">37.2925</fl>";
  oOut << "<fl c=\"1\">99.0234</fl>";
  oOut << "<fl c=\"3\">73.392</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">33.3496</fl>";
  oOut << "<fl c=\"1\">99.0295</fl>";
  oOut << "<fl c=\"3\">60.2078</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">36.5784</fl>";
  oOut << "<fl c=\"1\">103.125</fl>";
  oOut << "<fl c=\"3\">58.0145</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">35.5408</fl>";
  oOut << "<fl c=\"1\">108.008</fl>";
  oOut << "<fl c=\"3\">55.5896</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">38.7085</fl>";
  oOut << "<fl c=\"1\">109.65</fl>";
  oOut << "<fl c=\"3\">53.9532</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">32.5439</fl>";
  oOut << "<fl c=\"1\">121.399</fl>";
  oOut << "<fl c=\"3\">44.0854</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">35.8826</fl>";
  oOut << "<fl c=\"1\">173.944</fl>";
  oOut << "<fl c=\"3\">64.238</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">34.3628</fl>";
  oOut << "<fl c=\"1\">194.751</fl>";
  oOut << "<fl c=\"3\">59.9167</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">45.343</fl>";
  oOut << "<fl c=\"1\">68.3472</fl>";
  oOut << "<fl c=\"3\">94.8392</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">41.0889</fl>";
  oOut << "<fl c=\"1\">84.6741</fl>";
  oOut << "<fl c=\"3\">79.4022</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">41.0278</fl>";
  oOut << "<fl c=\"1\">128.68</fl>";
  oOut << "<fl c=\"3\">63.8409</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">45.2087</fl>";
  oOut << "<fl c=\"1\">138.226</fl>";
  oOut << "<fl c=\"3\">18.7393</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">47.0215</fl>";
  oOut << "<fl c=\"1\">151.764</fl>";
  oOut << "<fl c=\"3\">10.8939</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">41.095</fl>";
  oOut << "<fl c=\"1\">153.882</fl>";
  oOut << "<fl c=\"3\">84.4791</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">46.1121</fl>";
  oOut << "<fl c=\"1\">174.646</fl>";
  oOut << "<fl c=\"3\">10.1001</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">47.1436</fl>";
  oOut << "<fl c=\"1\">183.905</fl>";
  oOut << "<fl c=\"3\">20.0504</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"2\">";
  oOut << "<fl c=\"0\">46.4966</fl>";
  oOut << "<fl c=\"1\">178.687</fl>";
  oOut << "<fl c=\"4\">0.821655</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">55.2185</fl>";
  oOut << "<fl c=\"1\">19.574</fl>";
  oOut << "<fl c=\"3\">76.7453</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">52.4353</fl>";
  oOut << "<fl c=\"1\">36.8652</fl>";
  oOut << "<fl c=\"3\">20.7635</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">54.5044</fl>";
  oOut << "<fl c=\"1\">85.0464</fl>";
  oOut << "<fl c=\"3\">50.1688</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">55.9998</fl>";
  oOut << "<fl c=\"1\">99.9207</fl>";
  oOut << "<fl c=\"3\">95.3912</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">49.1455</fl>";
  oOut << "<fl c=\"1\">97.522</fl>";
  oOut << "<fl c=\"3\">92.3273</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">49.5972</fl>";
  oOut << "<fl c=\"1\">123.993</fl>";
  oOut << "<fl c=\"3\">24.3225</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">51.9287</fl>";
  oOut << "<fl c=\"1\">131.873</fl>";
  oOut << "<fl c=\"3\">62.8839</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">53.3447</fl>";
  oOut << "<fl c=\"1\">129.956</fl>";
  oOut << "<fl c=\"3\">22.6886</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">55.3345</fl>";
  oOut << "<fl c=\"1\">151.379</fl>";
  oOut << "<fl c=\"3\">12.9614</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">48.114</fl>";
  oOut << "<fl c=\"1\">156.976</fl>";
  oOut << "<fl c=\"3\">42.4615</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">51.6235</fl>";
  oOut << "<fl c=\"1\">172.089</fl>";
  oOut << "<fl c=\"3\">12.4313</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">62.2925</fl>";
  oOut << "<fl c=\"1\">19.6533</fl>";
  oOut << "<fl c=\"3\">51.1264</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">59.6191</fl>";
  oOut << "<fl c=\"1\">31.8787</fl>";
  oOut << "<fl c=\"3\">92.8043</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">60.8643</fl>";
  oOut << "<fl c=\"1\">45.8557</fl>";
  oOut << "<fl c=\"3\">74.4998</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">56.0608</fl>";
  oOut << "<fl c=\"1\">67.9138</fl>";
  oOut << "<fl c=\"3\">46.6187</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">62.207</fl>";
  oOut << "<fl c=\"1\">123.401</fl>";
  oOut << "<fl c=\"3\">98.5498</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">60.73</fl>";
  oOut << "<fl c=\"1\">120.459</fl>";
  oOut << "<fl c=\"3\">81.6614</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">56.8909</fl>";
  oOut << "<fl c=\"1\">153.015</fl>";
  oOut << "<fl c=\"3\">56.2457</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">62.7808</fl>";
  oOut << "<fl c=\"1\">193.109</fl>";
  oOut << "<fl c=\"3\">73.9728</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"2\">";
  oOut << "<fl c=\"0\">66.5344</fl>";
  oOut << "<fl c=\"1\">16.9006</fl>";
  oOut << "<fl c=\"4\">0.961304</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">68.1885</fl>";
  oOut << "<fl c=\"1\">43.4875</fl>";
  oOut << "<fl c=\"3\">43.2742</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">66.0767</fl>";
  oOut << "<fl c=\"1\">57.2632</fl>";
  oOut << "<fl c=\"3\">11.0693</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">67.5964</fl>";
  oOut << "<fl c=\"1\">94.4275</fl>";
  oOut << "<fl c=\"3\">65.2979</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">65.3809</fl>";
  oOut << "<fl c=\"1\">110.986</fl>";
  oOut << "<fl c=\"3\">25.1639</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">69.574</fl>";
  oOut << "<fl c=\"1\">151.202</fl>";
  oOut << "<fl c=\"3\">28.6108</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"2\">";
  oOut << "<fl c=\"0\">71.7957</fl>";
  oOut << "<fl c=\"1\">163.202</fl>";
  oOut << "<fl c=\"4\">0.117188</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">66.4734</fl>";
  oOut << "<fl c=\"1\">177.948</fl>";
  oOut << "<fl c=\"3\">20.6174</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">78.9795</fl>";
  oOut << "<fl c=\"1\">66.7542</fl>";
  oOut << "<fl c=\"3\">68.7817</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">77.9297</fl>";
  oOut << "<fl c=\"1\">85.907</fl>";
  oOut << "<fl c=\"3\">66.6638</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">75.2197</fl>";
  oOut << "<fl c=\"1\">128.607</fl>";
  oOut << "<fl c=\"3\">65.7352</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">75.415</fl>";
  oOut << "<fl c=\"1\">142.963</fl>";
  oOut << "<fl c=\"3\">45</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"2\">";
  oOut << "<fl c=\"0\">84.5459</fl>";
  oOut << "<fl c=\"1\">21.6858</fl>";
  oOut << "<fl c=\"4\">8.70361</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">86.2854</fl>";
  oOut << "<fl c=\"1\">39.7644</fl>";
  oOut << "<fl c=\"3\">76.9629</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">84.1309</fl>";
  oOut << "<fl c=\"1\">90.4968</fl>";
  oOut << "<fl c=\"3\">95.8945</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">83.8501</fl>";
  oOut << "<fl c=\"1\">91.803</fl>";
  oOut << "<fl c=\"3\">79.4092</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"2\">";
  oOut << "<fl c=\"0\">86.1755</fl>";
  oOut << "<fl c=\"1\">106.824</fl>";
  oOut << "<fl c=\"4\">0.113159</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">86.6516</fl>";
  oOut << "<fl c=\"1\">113.049</fl>";
  oOut << "<fl c=\"3\">71.8594</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">81.8848</fl>";
  oOut << "<fl c=\"1\">121.558</fl>";
  oOut << "<fl c=\"3\">76.2201</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">80.426</fl>";
  oOut << "<fl c=\"1\">130.377</fl>";
  oOut << "<fl c=\"3\">20.1474</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">86.9263</fl>";
  oOut << "<fl c=\"1\">149.762</fl>";
  oOut << "<fl c=\"3\">31.3779</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"2\">";
  oOut << "<fl c=\"0\">82.2205</fl>";
  oOut << "<fl c=\"1\">159.558</fl>";
  oOut << "<fl c=\"4\">3.43292</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">86.6577</fl>";
  oOut << "<fl c=\"1\">181.042</fl>";
  oOut << "<fl c=\"3\">53.0917</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">86.3342</fl>";
  oOut << "<fl c=\"1\">184.369</fl>";
  oOut << "<fl c=\"3\">34.5831</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">82.5439</fl>";
  oOut << "<fl c=\"1\">186.157</fl>";
  oOut << "<fl c=\"3\">32.4649</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">90.4358</fl>";
  oOut << "<fl c=\"1\">0.146484</fl>";
  oOut << "<fl c=\"3\">45.4599</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">94.5679</fl>";
  oOut << "<fl c=\"1\">43.811</fl>";
  oOut << "<fl c=\"3\">57.7402</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"2\">";
  oOut << "<fl c=\"0\">90.1855</fl>";
  oOut << "<fl c=\"1\">89.4592</fl>";
  oOut << "<fl c=\"4\">5.16849</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">94.8059</fl>";
  oOut << "<fl c=\"1\">127.271</fl>";
  oOut << "<fl c=\"3\">73.0457</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"2\">";
  oOut << "<fl c=\"0\">90.7227</fl>";
  oOut << "<fl c=\"1\">121.198</fl>";
  oOut << "<fl c=\"4\">0.535553</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">93.75</fl>";
  oOut << "<fl c=\"1\">156.512</fl>";
  oOut << "<fl c=\"3\">32.3999</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"2\">";
  oOut << "<fl c=\"0\">98.8098</fl>";
  oOut << "<fl c=\"1\">2.76489</fl>";
  oOut << "<fl c=\"4\">0.487579</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">99.5239</fl>";
  oOut << "<fl c=\"1\">27.5391</fl>";
  oOut << "<fl c=\"3\">47.3404</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"2\">";
  oOut << "<fl c=\"0\">99.115</fl>";
  oOut << "<fl c=\"1\">25.6531</fl>";
  oOut << "<fl c=\"4\">7.94199</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">103.998</fl>";
  oOut << "<fl c=\"1\">36.5784</fl>";
  oOut << "<fl c=\"3\">22.6883</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">98.4619</fl>";
  oOut << "<fl c=\"1\">67.1326</fl>";
  oOut << "<fl c=\"3\">23.6703</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">111.658</fl>";
  oOut << "<fl c=\"1\">11.4563</fl>";
  oOut << "<fl c=\"3\">44.0451</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"2\">";
  oOut << "<fl c=\"0\">106.915</fl>";
  oOut << "<fl c=\"1\">10.26</fl>";
  oOut << "<fl c=\"4\">9.52429</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">111.493</fl>";
  oOut << "<fl c=\"1\">28.5828</fl>";
  oOut << "<fl c=\"3\">67.6199</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">105.481</fl>";
  oOut << "<fl c=\"1\">85.907</fl>";
  oOut << "<fl c=\"3\">73.3121</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">107.581</fl>";
  oOut << "<fl c=\"1\">115.912</fl>";
  oOut << "<fl c=\"3\">54.104</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">111.572</fl>";
  oOut << "<fl c=\"1\">118.756</fl>";
  oOut << "<fl c=\"3\">31.5875</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">111.023</fl>";
  oOut << "<fl c=\"1\">134.1</fl>";
  oOut << "<fl c=\"3\">32.5201</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">108.398</fl>";
  oOut << "<fl c=\"1\">138.153</fl>";
  oOut << "<fl c=\"3\">31.221</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"2\">";
  oOut << "<fl c=\"0\">106.824</fl>";
  oOut << "<fl c=\"1\">153.51</fl>";
  oOut << "<fl c=\"4\">0.960297</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">111.749</fl>";
  oOut << "<fl c=\"1\">160.437</fl>";
  oOut << "<fl c=\"3\">16.9574</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">109.076</fl>";
  oOut << "<fl c=\"1\">174.786</fl>";
  oOut << "<fl c=\"3\">91.7136</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">106.873</fl>";
  oOut << "<fl c=\"1\">186.755</fl>";
  oOut << "<fl c=\"3\">87.2842</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">104.248</fl>";
  oOut << "<fl c=\"1\">193.347</fl>";
  oOut << "<fl c=\"3\">22.3141</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">113.257</fl>";
  oOut << "<fl c=\"1\">52.887</fl>";
  oOut << "<fl c=\"3\">31.7151</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">119.135</fl>";
  oOut << "<fl c=\"1\">65.9912</fl>";
  oOut << "<fl c=\"3\">34.0717</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"2\">";
  oOut << "<fl c=\"0\">115.497</fl>";
  oOut << "<fl c=\"1\">107.568</fl>";
  oOut << "<fl c=\"4\">3.31647</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">124.762</fl>";
  oOut << "<fl c=\"1\">37.3596</fl>";
  oOut << "<fl c=\"3\">44.8953</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">127.332</fl>";
  oOut << "<fl c=\"1\">33.3374</fl>";
  oOut << "<fl c=\"3\">12.6553</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"2\">";
  oOut << "<fl c=\"0\">121.1</fl>";
  oOut << "<fl c=\"1\">56.2927</fl>";
  oOut << "<fl c=\"4\">1.81134</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">120.306</fl>";
  oOut << "<fl c=\"1\">67.0227</fl>";
  oOut << "<fl c=\"3\">30.9973</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"2\">";
  oOut << "<fl c=\"0\">120.709</fl>";
  oOut << "<fl c=\"1\">69.2139</fl>";
  oOut << "<fl c=\"4\">9.98407</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">120.184</fl>";
  oOut << "<fl c=\"1\">138.959</fl>";
  oOut << "<fl c=\"3\">54.3503</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">124.768</fl>";
  oOut << "<fl c=\"1\">153.552</fl>";
  oOut << "<fl c=\"3\">89.2224</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">127.277</fl>";
  oOut << "<fl c=\"1\">180.524</fl>";
  oOut << "<fl c=\"3\">85.7211</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"2\">";
  oOut << "<fl c=\"0\">127.551</fl>";
  oOut << "<fl c=\"1\">189.984</fl>";
  oOut << "<fl c=\"4\">0.745728</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">123.328</fl>";
  oOut << "<fl c=\"1\">195.746</fl>";
  oOut << "<fl c=\"3\">78.3109</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">129.028</fl>";
  oOut << "<fl c=\"1\">15.5518</fl>";
  oOut << "<fl c=\"3\">65.6329</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">129.84</fl>";
  oOut << "<fl c=\"1\">16.8518</fl>";
  oOut << "<fl c=\"3\">44.949</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">128.552</fl>";
  oOut << "<fl c=\"1\">38.5864</fl>";
  oOut << "<fl c=\"3\">58.9499</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">132.764</fl>";
  oOut << "<fl c=\"1\">44.5862</fl>";
  oOut << "<fl c=\"3\">10.5179</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">132.843</fl>";
  oOut << "<fl c=\"1\">56.5002</fl>";
  oOut << "<fl c=\"3\">82.7173</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">132.397</fl>";
  oOut << "<fl c=\"1\">84.8999</fl>";
  oOut << "<fl c=\"3\">70.7071</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">133.624</fl>";
  oOut << "<fl c=\"1\">95.6665</fl>";
  oOut << "<fl c=\"3\">88.9252</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">129.327</fl>";
  oOut << "<fl c=\"1\">105.841</fl>";
  oOut << "<fl c=\"3\">43.9096</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">131.586</fl>";
  oOut << "<fl c=\"1\">122.089</fl>";
  oOut << "<fl c=\"3\">41.8552</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">131.75</fl>";
  oOut << "<fl c=\"1\">156.403</fl>";
  oOut << "<fl c=\"3\">16.2299</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">133.124</fl>";
  oOut << "<fl c=\"1\">184.064</fl>";
  oOut << "<fl c=\"3\">71.4288</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">129.297</fl>";
  oOut << "<fl c=\"1\">188.177</fl>";
  oOut << "<fl c=\"3\">70.0156</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">142.358</fl>";
  oOut << "<fl c=\"1\">10.8704</fl>";
  oOut << "<fl c=\"3\">68.0521</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"2\">";
  oOut << "<fl c=\"0\">136.23</fl>";
  oOut << "<fl c=\"1\">47.229</fl>";
  oOut << "<fl c=\"4\">0.0601501</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">138.66</fl>";
  oOut << "<fl c=\"1\">49.8169</fl>";
  oOut << "<fl c=\"3\">35.8368</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"2\">";
  oOut << "<fl c=\"0\">140.363</fl>";
  oOut << "<fl c=\"1\">85.2173</fl>";
  oOut << "<fl c=\"4\">4.39038</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"2\">";
  oOut << "<fl c=\"0\">139.874</fl>";
  oOut << "<fl c=\"1\">83.4656</fl>";
  oOut << "<fl c=\"4\">0.178741</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"2\">";
  oOut << "<fl c=\"0\">137.091</fl>";
  oOut << "<fl c=\"1\">99.7742</fl>";
  oOut << "<fl c=\"4\">2.01047</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">142.053</fl>";
  oOut << "<fl c=\"1\">105.682</fl>";
  oOut << "<fl c=\"3\">80.2078</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"2\">";
  oOut << "<fl c=\"0\">139.886</fl>";
  oOut << "<fl c=\"1\">110.84</fl>";
  oOut << "<fl c=\"4\">0.351074</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">137.292</fl>";
  oOut << "<fl c=\"1\">127.087</fl>";
  oOut << "<fl c=\"3\">96.9315</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">136.914</fl>";
  oOut << "<fl c=\"1\">123.224</fl>";
  oOut << "<fl c=\"3\">83.1815</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">136.017</fl>";
  oOut << "<fl c=\"1\">164.508</fl>";
  oOut << "<fl c=\"3\">61.9275</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"2\">";
  oOut << "<fl c=\"0\">146.277</fl>";
  oOut << "<fl c=\"1\">30.3589</fl>";
  oOut << "<fl c=\"4\">0.951935</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">146.521</fl>";
  oOut << "<fl c=\"1\">53.0884</fl>";
  oOut << "<fl c=\"3\">38.4854</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">147.949</fl>";
  oOut << "<fl c=\"1\">70.7886</fl>";
  oOut << "<fl c=\"3\">99.1867</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">150.958</fl>";
  oOut << "<fl c=\"1\">80.1636</fl>";
  oOut << "<fl c=\"3\">96.2463</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">151.031</fl>";
  oOut << "<fl c=\"1\">123.383</fl>";
  oOut << "<fl c=\"3\">84.491</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">159.607</fl>";
  oOut << "<fl c=\"1\">6.84814</fl>";
  oOut << "<fl c=\"3\">45.9476</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">152.893</fl>";
  oOut << "<fl c=\"1\">26.2878</fl>";
  oOut << "<fl c=\"3\">84.4986</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"2\">";
  oOut << "<fl c=\"0\">153.68</fl>";
  oOut << "<fl c=\"1\">63.7573</fl>";
  oOut << "<fl c=\"4\">0.219574</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">152.82</fl>";
  oOut << "<fl c=\"1\">70.8069</fl>";
  oOut << "<fl c=\"3\">37.1304</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">158.167</fl>";
  oOut << "<fl c=\"1\">76.5991</fl>";
  oOut << "<fl c=\"3\">29.9658</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"2\">";
  oOut << "<fl c=\"0\">156.238</fl>";
  oOut << "<fl c=\"1\">94.2017</fl>";
  oOut << "<fl c=\"4\">3.3324</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">156.14</fl>";
  oOut << "<fl c=\"1\">99.6399</fl>";
  oOut << "<fl c=\"3\">99.6304</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">152.734</fl>";
  oOut << "<fl c=\"1\">98.5962</fl>";
  oOut << "<fl c=\"3\">38.9621</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">154.895</fl>";
  oOut << "<fl c=\"1\">113.556</fl>";
  oOut << "<fl c=\"3\">91.9345</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"2\">";
  oOut << "<fl c=\"0\">153.906</fl>";
  oOut << "<fl c=\"1\">135.333</fl>";
  oOut << "<fl c=\"4\">0.456757</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"2\">";
  oOut << "<fl c=\"0\">154.718</fl>";
  oOut << "<fl c=\"1\">161.206</fl>";
  oOut << "<fl c=\"4\">8.12518</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"2\">";
  oOut << "<fl c=\"0\">157.587</fl>";
  oOut << "<fl c=\"1\">163.226</fl>";
  oOut << "<fl c=\"4\">2.95007</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">157.532</fl>";
  oOut << "<fl c=\"1\">192.352</fl>";
  oOut << "<fl c=\"3\">63.9352</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">167.676</fl>";
  oOut << "<fl c=\"1\">11.3281</fl>";
  oOut << "<fl c=\"3\">42.8085</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">164.771</fl>";
  oOut << "<fl c=\"1\">17.7979</fl>";
  oOut << "<fl c=\"3\">82.1024</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">160.852</fl>";
  oOut << "<fl c=\"1\">67.6025</fl>";
  oOut << "<fl c=\"3\">63.6978</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">166.052</fl>";
  oOut << "<fl c=\"1\">114.868</fl>";
  oOut << "<fl c=\"3\">83.3246</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">164.667</fl>";
  oOut << "<fl c=\"1\">195.239</fl>";
  oOut << "<fl c=\"3\">32.7954</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">169.391</fl>";
  oOut << "<fl c=\"1\">0.634766</fl>";
  oOut << "<fl c=\"3\">82.4969</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"2\">";
  oOut << "<fl c=\"0\">173.633</fl>";
  oOut << "<fl c=\"1\">23.4863</fl>";
  oOut << "<fl c=\"4\">0.565521</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"2\">";
  oOut << "<fl c=\"0\">173.56</fl>";
  oOut << "<fl c=\"1\">24.4141</fl>";
  oOut << "<fl c=\"4\">1.37683</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">169.58</fl>";
  oOut << "<fl c=\"1\">59.4971</fl>";
  oOut << "<fl c=\"3\">13.5617</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">170.929</fl>";
  oOut << "<fl c=\"1\">73.2056</fl>";
  oOut << "<fl c=\"3\">81.3498</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">175.818</fl>";
  oOut << "<fl c=\"1\">90.9851</fl>";
  oOut << "<fl c=\"3\">25.7568</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">168.292</fl>";
  oOut << "<fl c=\"1\">118.292</fl>";
  oOut << "<fl c=\"3\">28.7762</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"2\">";
  oOut << "<fl c=\"0\">168.121</fl>";
  oOut << "<fl c=\"1\">136.176</fl>";
  oOut << "<fl c=\"4\">9.18207</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">175.83</fl>";
  oOut << "<fl c=\"1\">149.908</fl>";
  oOut << "<fl c=\"3\">65.5508</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">168.207</fl>";
  oOut << "<fl c=\"1\">144.788</fl>";
  oOut << "<fl c=\"3\">20.9869</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">170.801</fl>";
  oOut << "<fl c=\"1\">153.412</fl>";
  oOut << "<fl c=\"3\">59.025</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">176.636</fl>";
  oOut << "<fl c=\"1\">14.502</fl>";
  oOut << "<fl c=\"3\">53.5507</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">182.794</fl>";
  oOut << "<fl c=\"1\">31.9885</fl>";
  oOut << "<fl c=\"3\">91.8341</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">177.417</fl>";
  oOut << "<fl c=\"1\">32.0923</fl>";
  oOut << "<fl c=\"3\">41.091</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">181.342</fl>";
  oOut << "<fl c=\"1\">42.0959</fl>";
  oOut << "<fl c=\"3\">55.6598</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">183.801</fl>";
  oOut << "<fl c=\"1\">71.3684</fl>";
  oOut << "<fl c=\"3\">90.6638</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">177.356</fl>";
  oOut << "<fl c=\"1\">76.5503</fl>";
  oOut << "<fl c=\"3\">90.1468</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">181.494</fl>";
  oOut << "<fl c=\"1\">95.4712</fl>";
  oOut << "<fl c=\"3\">28.3881</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">180.072</fl>";
  oOut << "<fl c=\"1\">124.53</fl>";
  oOut << "<fl c=\"3\">16.5067</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">180.914</fl>";
  oOut << "<fl c=\"1\">157.446</fl>";
  oOut << "<fl c=\"3\">19.5609</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">178.888</fl>";
  oOut << "<fl c=\"1\">180.273</fl>";
  oOut << "<fl c=\"3\">66.6342</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">181.128</fl>";
  oOut << "<fl c=\"1\">185.382</fl>";
  oOut << "<fl c=\"3\">68.0597</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">189.392</fl>";
  oOut << "<fl c=\"1\">28.1311</fl>";
  oOut << "<fl c=\"3\">73.8248</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">186.731</fl>";
  oOut << "<fl c=\"1\">26.825</fl>";
  oOut << "<fl c=\"3\">11.6092</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">188.361</fl>";
  oOut << "<fl c=\"1\">39.8315</fl>";
  oOut << "<fl c=\"3\">96.7001</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">191.797</fl>";
  oOut << "<fl c=\"1\">61.3586</fl>";
  oOut << "<fl c=\"3\">52.981</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">186.963</fl>";
  oOut << "<fl c=\"1\">97.699</fl>";
  oOut << "<fl c=\"3\">86.3974</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">190.045</fl>";
  oOut << "<fl c=\"1\">119.031</fl>";
  oOut << "<fl c=\"3\">81.9983</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">189.996</fl>";
  oOut << "<fl c=\"1\">126.154</fl>";
  oOut << "<fl c=\"3\">23.3459</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">189.758</fl>";
  oOut << "<fl c=\"1\">123.718</fl>";
  oOut << "<fl c=\"3\">15.0217</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">187</fl>";
  oOut << "<fl c=\"1\">155.127</fl>";
  oOut << "<fl c=\"3\">21.4319</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">184.998</fl>";
  oOut << "<fl c=\"1\">180.701</fl>";
  oOut << "<fl c=\"3\">94.5517</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">199.5</fl>";
  oOut << "<fl c=\"1\">7.44629</fl>";
  oOut << "<fl c=\"3\">14.7906</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">197.919</fl>";
  oOut << "<fl c=\"1\">47.9004</fl>";
  oOut << "<fl c=\"3\">12.247</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">192.706</fl>";
  oOut << "<fl c=\"1\">59.0942</fl>";
  oOut << "<fl c=\"3\">37.8571</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"2\">";
  oOut << "<fl c=\"0\">196.13</fl>";
  oOut << "<fl c=\"1\">107.007</fl>";
  oOut << "<fl c=\"4\">0.626282</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">196.49</fl>";
  oOut << "<fl c=\"1\">168.988</fl>";
  oOut << "<fl c=\"3\">75.2383</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">192.81</fl>";
  oOut << "<fl c=\"1\">173.029</fl>";
  oOut << "<fl c=\"3\">27.3651</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">192.285</fl>";
  oOut << "<fl c=\"1\">177.661</fl>";
  oOut << "<fl c=\"3\">54.3536</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"4\" tp=\"3\">";
  oOut << "<fl c=\"0\">193.604</fl>";
  oOut << "<fl c=\"1\">184.564</fl>";
  oOut << "<fl c=\"3\">80.9839</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">5.98145</fl>";
  oOut << "<fl c=\"1\">22.345</fl>";
  oOut << "<fl c=\"3\">42.03</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">7.36084</fl>";
  oOut << "<fl c=\"1\">33.0811</fl>";
  oOut << "<fl c=\"3\">81.9543</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">6.38428</fl>";
  oOut << "<fl c=\"1\">50.6042</fl>";
  oOut << "<fl c=\"3\">96.2695</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">6.38428</fl>";
  oOut << "<fl c=\"1\">65.4175</fl>";
  oOut << "<fl c=\"3\">96.3052</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">0.561523</fl>";
  oOut << "<fl c=\"1\">65.9363</fl>";
  oOut << "<fl c=\"3\">36.5909</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">2.85645</fl>";
  oOut << "<fl c=\"1\">84.259</fl>";
  oOut << "<fl c=\"3\">95.1984</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">4.84619</fl>";
  oOut << "<fl c=\"1\">80.7007</fl>";
  oOut << "<fl c=\"3\">45.7001</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">0.561523</fl>";
  oOut << "<fl c=\"1\">113.623</fl>";
  oOut << "<fl c=\"3\">82.157</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">4.82178</fl>";
  oOut << "<fl c=\"1\">120.02</fl>";
  oOut << "<fl c=\"3\">91.2274</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"2\">";
  oOut << "<fl c=\"0\">4.77905</fl>";
  oOut << "<fl c=\"1\">127.905</fl>";
  oOut << "<fl c=\"4\">0.0861511</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"2\">";
  oOut << "<fl c=\"0\">0.0671387</fl>";
  oOut << "<fl c=\"1\">155.975</fl>";
  oOut << "<fl c=\"4\">4.62604</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">7.8064</fl>";
  oOut << "<fl c=\"1\">182.214</fl>";
  oOut << "<fl c=\"3\">37.6587</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">3.71704</fl>";
  oOut << "<fl c=\"1\">190.247</fl>";
  oOut << "<fl c=\"3\">74.6301</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">2.03247</fl>";
  oOut << "<fl c=\"1\">196.851</fl>";
  oOut << "<fl c=\"3\">96.2433</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"2\">";
  oOut << "<fl c=\"0\">8.73413</fl>";
  oOut << "<fl c=\"1\">3.07617</fl>";
  oOut << "<fl c=\"4\">8.3353</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">10.4736</fl>";
  oOut << "<fl c=\"1\">21.0083</fl>";
  oOut << "<fl c=\"3\">64.3872</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">13.9648</fl>";
  oOut << "<fl c=\"1\">20.0195</fl>";
  oOut << "<fl c=\"3\">46.633</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">8.6731</fl>";
  oOut << "<fl c=\"1\">47.3328</fl>";
  oOut << "<fl c=\"3\">82.1268</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">15.2405</fl>";
  oOut << "<fl c=\"1\">55.8533</fl>";
  oOut << "<fl c=\"3\">53.7085</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">13.9221</fl>";
  oOut << "<fl c=\"1\">108.533</fl>";
  oOut << "<fl c=\"3\">39.0561</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">14.4775</fl>";
  oOut << "<fl c=\"1\">130.17</fl>";
  oOut << "<fl c=\"3\">28.8632</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"2\">";
  oOut << "<fl c=\"0\">23.1323</fl>";
  oOut << "<fl c=\"1\">5.62744</fl>";
  oOut << "<fl c=\"4\">0.47525</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">22.0459</fl>";
  oOut << "<fl c=\"1\">29.0833</fl>";
  oOut << "<fl c=\"3\">18.949</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">23.4131</fl>";
  oOut << "<fl c=\"1\">39.5142</fl>";
  oOut << "<fl c=\"3\">26.1453</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">20.0806</fl>";
  oOut << "<fl c=\"1\">81.2073</fl>";
  oOut << "<fl c=\"3\">61.5433</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">17.0166</fl>";
  oOut << "<fl c=\"1\">87.1338</fl>";
  oOut << "<fl c=\"3\">19.631</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">21.0205</fl>";
  oOut << "<fl c=\"1\">93.5608</fl>";
  oOut << "<fl c=\"3\">61.3165</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">18.7805</fl>";
  oOut << "<fl c=\"1\">97.8455</fl>";
  oOut << "<fl c=\"3\">78.8037</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"2\">";
  oOut << "<fl c=\"0\">20.1355</fl>";
  oOut << "<fl c=\"1\">112.781</fl>";
  oOut << "<fl c=\"4\">0.230927</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">23.0225</fl>";
  oOut << "<fl c=\"1\">147.473</fl>";
  oOut << "<fl c=\"3\">72.3126</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">17.5415</fl>";
  oOut << "<fl c=\"1\">176.965</fl>";
  oOut << "<fl c=\"3\">38.0191</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">28.2959</fl>";
  oOut << "<fl c=\"1\">41.8152</fl>";
  oOut << "<fl c=\"3\">20.2164</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">27.6917</fl>";
  oOut << "<fl c=\"1\">57.6782</fl>";
  oOut << "<fl c=\"3\">38.8461</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">31.5735</fl>";
  oOut << "<fl c=\"1\">67.6758</fl>";
  oOut << "<fl c=\"3\">31.3239</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">29.9133</fl>";
  oOut << "<fl c=\"1\">106.873</fl>";
  oOut << "<fl c=\"3\">66.0065</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">24.1516</fl>";
  oOut << "<fl c=\"1\">122.345</fl>";
  oOut << "<fl c=\"3\">25.1749</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">29.4006</fl>";
  oOut << "<fl c=\"1\">159.54</fl>";
  oOut << "<fl c=\"3\">52.9327</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">27.2583</fl>";
  oOut << "<fl c=\"1\">175.806</fl>";
  oOut << "<fl c=\"3\">52.9846</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">30.2979</fl>";
  oOut << "<fl c=\"1\">178.51</fl>";
  oOut << "<fl c=\"3\">53.3728</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"2\">";
  oOut << "<fl c=\"0\">34.436</fl>";
  oOut << "<fl c=\"1\">0.750732</fl>";
  oOut << "<fl c=\"4\">0.224457</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">32.0435</fl>";
  oOut << "<fl c=\"1\">39.6667</fl>";
  oOut << "<fl c=\"3\">41.1737</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">37.8235</fl>";
  oOut << "<fl c=\"1\">98.4375</fl>";
  oOut << "<fl c=\"3\">47.4323</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">35.8704</fl>";
  oOut << "<fl c=\"1\">115.137</fl>";
  oOut << "<fl c=\"3\">89.9911</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">32.3914</fl>";
  oOut << "<fl c=\"1\">155.225</fl>";
  oOut << "<fl c=\"3\">37.1436</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">36.6211</fl>";
  oOut << "<fl c=\"1\">156.097</fl>";
  oOut << "<fl c=\"3\">14.35</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"2\">";
  oOut << "<fl c=\"0\">38.6963</fl>";
  oOut << "<fl c=\"1\">153.412</fl>";
  oOut << "<fl c=\"4\">0.375977</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">39.0076</fl>";
  oOut << "<fl c=\"1\">169.196</fl>";
  oOut << "<fl c=\"3\">59.7781</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">43.75</fl>";
  oOut << "<fl c=\"1\">9.82666</fl>";
  oOut << "<fl c=\"3\">73.157</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">44.9951</fl>";
  oOut << "<fl c=\"1\">39.4775</fl>";
  oOut << "<fl c=\"3\">62.4289</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">45.343</fl>";
  oOut << "<fl c=\"1\">53.4241</fl>";
  oOut << "<fl c=\"3\">91.4664</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">45.4956</fl>";
  oOut << "<fl c=\"1\">56.7017</fl>";
  oOut << "<fl c=\"3\">33.476</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"2\">";
  oOut << "<fl c=\"0\">41.9678</fl>";
  oOut << "<fl c=\"1\">78.8269</fl>";
  oOut << "<fl c=\"4\">0.638</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">46.2769</fl>";
  oOut << "<fl c=\"1\">94.8792</fl>";
  oOut << "<fl c=\"3\">76.2695</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">42.6636</fl>";
  oOut << "<fl c=\"1\">114.465</fl>";
  oOut << "<fl c=\"3\">15.5597</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">45.5017</fl>";
  oOut << "<fl c=\"1\">128.888</fl>";
  oOut << "<fl c=\"3\">36.962</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"2\">";
  oOut << "<fl c=\"0\">44.9829</fl>";
  oOut << "<fl c=\"1\">160.004</fl>";
  oOut << "<fl c=\"4\">0.526978</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">40.3015</fl>";
  oOut << "<fl c=\"1\">171.814</fl>";
  oOut << "<fl c=\"3\">23.7405</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"2\">";
  oOut << "<fl c=\"0\">46.405</fl>";
  oOut << "<fl c=\"1\">169.824</fl>";
  oOut << "<fl c=\"4\">0.899292</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">52.5635</fl>";
  oOut << "<fl c=\"1\">20.6848</fl>";
  oOut << "<fl c=\"3\">40.0092</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">50.7507</fl>";
  oOut << "<fl c=\"1\">40.0879</fl>";
  oOut << "<fl c=\"3\">51.3217</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">50.4089</fl>";
  oOut << "<fl c=\"1\">47.0947</fl>";
  oOut << "<fl c=\"3\">23.8412</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">50.6348</fl>";
  oOut << "<fl c=\"1\">66.4795</fl>";
  oOut << "<fl c=\"3\">27.4896</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"2\">";
  oOut << "<fl c=\"0\">54.8035</fl>";
  oOut << "<fl c=\"1\">99.3835</fl>";
  oOut << "<fl c=\"4\">9.78549</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">54.8645</fl>";
  oOut << "<fl c=\"1\">114.319</fl>";
  oOut << "<fl c=\"3\">96.1075</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">54.0466</fl>";
  oOut << "<fl c=\"1\">167.749</fl>";
  oOut << "<fl c=\"3\">12.7856</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">55.7434</fl>";
  oOut << "<fl c=\"1\">180.17</fl>";
  oOut << "<fl c=\"3\">12.847</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">61.1328</fl>";
  oOut << "<fl c=\"1\">55.5969</fl>";
  oOut << "<fl c=\"3\">98.9746</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"2\">";
  oOut << "<fl c=\"0\">58.0688</fl>";
  oOut << "<fl c=\"1\">60.5835</fl>";
  oOut << "<fl c=\"4\">5.76257</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">63.6963</fl>";
  oOut << "<fl c=\"1\">67.6331</fl>";
  oOut << "<fl c=\"3\">87.2345</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"2\">";
  oOut << "<fl c=\"0\">59.0881</fl>";
  oOut << "<fl c=\"1\">97.7112</fl>";
  oOut << "<fl c=\"4\">0.952972</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">58.8379</fl>";
  oOut << "<fl c=\"1\">172.76</fl>";
  oOut << "<fl c=\"3\">25.0244</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">63.2935</fl>";
  oOut << "<fl c=\"1\">192.749</fl>";
  oOut << "<fl c=\"3\">87.561</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">66.748</fl>";
  oOut << "<fl c=\"1\">34.9243</fl>";
  oOut << "<fl c=\"3\">34.1577</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">69.635</fl>";
  oOut << "<fl c=\"1\">138.104</fl>";
  oOut << "<fl c=\"3\">71.3272</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"2\">";
  oOut << "<fl c=\"0\">70.6238</fl>";
  oOut << "<fl c=\"1\">155.92</fl>";
  oOut << "<fl c=\"4\">4.07947</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">68.4326</fl>";
  oOut << "<fl c=\"1\">168.573</fl>";
  oOut << "<fl c=\"3\">49.6194</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">70.9534</fl>";
  oOut << "<fl c=\"1\">177.576</fl>";
  oOut << "<fl c=\"3\">72.3059</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"2\">";
  oOut << "<fl c=\"0\">78.2898</fl>";
  oOut << "<fl c=\"1\">58.9966</fl>";
  oOut << "<fl c=\"4\">7.57779</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">78.6255</fl>";
  oOut << "<fl c=\"1\">71.698</fl>";
  oOut << "<fl c=\"3\">71.8481</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"2\">";
  oOut << "<fl c=\"0\">79.5593</fl>";
  oOut << "<fl c=\"1\">89.9902</fl>";
  oOut << "<fl c=\"4\">0.623962</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">78.3264</fl>";
  oOut << "<fl c=\"1\">114.844</fl>";
  oOut << "<fl c=\"3\">35.6238</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">79.4617</fl>";
  oOut << "<fl c=\"1\">146.167</fl>";
  oOut << "<fl c=\"3\">37.4005</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">74.5422</fl>";
  oOut << "<fl c=\"1\">169.733</fl>";
  oOut << "<fl c=\"3\">99.5303</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"2\">";
  oOut << "<fl c=\"0\">78.9185</fl>";
  oOut << "<fl c=\"1\">190.161</fl>";
  oOut << "<fl c=\"4\">0.935028</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">72.3999</fl>";
  oOut << "<fl c=\"1\">198.157</fl>";
  oOut << "<fl c=\"3\">98.6835</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"2\">";
  oOut << "<fl c=\"0\">80.8533</fl>";
  oOut << "<fl c=\"1\">11.792</fl>";
  oOut << "<fl c=\"4\">9.0137</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">80.8716</fl>";
  oOut << "<fl c=\"1\">47.1497</fl>";
  oOut << "<fl c=\"3\">55.6409</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">86.2854</fl>";
  oOut << "<fl c=\"1\">59.3201</fl>";
  oOut << "<fl c=\"3\">18.0988</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">83.0627</fl>";
  oOut << "<fl c=\"1\">75.7141</fl>";
  oOut << "<fl c=\"3\">52.5345</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">84.7595</fl>";
  oOut << "<fl c=\"1\">163.855</fl>";
  oOut << "<fl c=\"3\">62.7328</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">84.9426</fl>";
  oOut << "<fl c=\"1\">167.639</fl>";
  oOut << "<fl c=\"3\">54.9777</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">87.3169</fl>";
  oOut << "<fl c=\"1\">198.584</fl>";
  oOut << "<fl c=\"3\">12.4268</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">91.1743</fl>";
  oOut << "<fl c=\"1\">12.4817</fl>";
  oOut << "<fl c=\"3\">18.8504</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"2\">";
  oOut << "<fl c=\"0\">88.678</fl>";
  oOut << "<fl c=\"1\">77.5269</fl>";
  oOut << "<fl c=\"4\">3.52383</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">89.1785</fl>";
  oOut << "<fl c=\"1\">100.226</fl>";
  oOut << "<fl c=\"3\">17.887</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">95.1111</fl>";
  oOut << "<fl c=\"1\">145.312</fl>";
  oOut << "<fl c=\"3\">48.9581</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">93.927</fl>";
  oOut << "<fl c=\"1\">155.627</fl>";
  oOut << "<fl c=\"3\">67.4475</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">94.2322</fl>";
  oOut << "<fl c=\"1\">181.531</fl>";
  oOut << "<fl c=\"3\">45.3134</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">89.1541</fl>";
  oOut << "<fl c=\"1\">186.389</fl>";
  oOut << "<fl c=\"3\">60.2203</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">101.385</fl>";
  oOut << "<fl c=\"1\">15.9302</fl>";
  oOut << "<fl c=\"3\">40.5408</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"2\">";
  oOut << "<fl c=\"0\">99.1211</fl>";
  oOut << "<fl c=\"1\">10.5957</fl>";
  oOut << "<fl c=\"4\">0.250061</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">97.7234</fl>";
  oOut << "<fl c=\"1\">23.4253</fl>";
  oOut << "<fl c=\"3\">62.5418</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">99.7375</fl>";
  oOut << "<fl c=\"1\">33.2703</fl>";
  oOut << "<fl c=\"3\">82.5494</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">103.735</fl>";
  oOut << "<fl c=\"1\">42.1326</fl>";
  oOut << "<fl c=\"3\">76.9492</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">99.4507</fl>";
  oOut << "<fl c=\"1\">49.0479</fl>";
  oOut << "<fl c=\"3\">40.7861</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">101.331</fl>";
  oOut << "<fl c=\"1\">97.9858</fl>";
  oOut << "<fl c=\"3\">19.9341</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">103.302</fl>";
  oOut << "<fl c=\"1\">181.396</fl>";
  oOut << "<fl c=\"3\">25.1871</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">97.7234</fl>";
  oOut << "<fl c=\"1\">184.308</fl>";
  oOut << "<fl c=\"3\">63.699</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">109.778</fl>";
  oOut << "<fl c=\"1\">47.3267</fl>";
  oOut << "<fl c=\"3\">80.8817</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">104.803</fl>";
  oOut << "<fl c=\"1\">46.875</fl>";
  oOut << "<fl c=\"3\">20.2032</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"2\">";
  oOut << "<fl c=\"0\">105.353</fl>";
  oOut << "<fl c=\"1\">62.1765</fl>";
  oOut << "<fl c=\"4\">6.05811</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">104.901</fl>";
  oOut << "<fl c=\"1\">109.247</fl>";
  oOut << "<fl c=\"3\">85.61</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"2\">";
  oOut << "<fl c=\"0\">110.089</fl>";
  oOut << "<fl c=\"1\">113.116</fl>";
  oOut << "<fl c=\"4\">8.27817</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">107.947</fl>";
  oOut << "<fl c=\"1\">140.039</fl>";
  oOut << "<fl c=\"3\">80.0525</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">106.281</fl>";
  oOut << "<fl c=\"1\">156.714</fl>";
  oOut << "<fl c=\"3\">63.9706</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">118.396</fl>";
  oOut << "<fl c=\"1\">71.5576</fl>";
  oOut << "<fl c=\"3\">87.4387</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">113.788</fl>";
  oOut << "<fl c=\"1\">90.4968</fl>";
  oOut << "<fl c=\"3\">85.3644</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">113.135</fl>";
  oOut << "<fl c=\"1\">133.386</fl>";
  oOut << "<fl c=\"3\">45.5475</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">117.273</fl>";
  oOut << "<fl c=\"1\">140.277</fl>";
  oOut << "<fl c=\"3\">67.7469</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">114.478</fl>";
  oOut << "<fl c=\"1\">158.722</fl>";
  oOut << "<fl c=\"3\">59.8831</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"2\">";
  oOut << "<fl c=\"0\">116.138</fl>";
  oOut << "<fl c=\"1\">164.539</fl>";
  oOut << "<fl c=\"4\">3.08768</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">117.554</fl>";
  oOut << "<fl c=\"1\">199.158</fl>";
  oOut << "<fl c=\"3\">75.4816</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">123.291</fl>";
  oOut << "<fl c=\"1\">22.9675</fl>";
  oOut << "<fl c=\"3\">96.7673</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"2\">";
  oOut << "<fl c=\"0\">127.039</fl>";
  oOut << "<fl c=\"1\">121.68</fl>";
  oOut << "<fl c=\"4\">2.50513</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">126.819</fl>";
  oOut << "<fl c=\"1\">133.917</fl>";
  oOut << "<fl c=\"3\">55.5777</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"2\">";
  oOut << "<fl c=\"0\">120.093</fl>";
  oOut << "<fl c=\"1\">133.691</fl>";
  oOut << "<fl c=\"4\">0.783142</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">122.308</fl>";
  oOut << "<fl c=\"1\">159.454</fl>";
  oOut << "<fl c=\"3\">63.7747</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"2\">";
  oOut << "<fl c=\"0\">127.637</fl>";
  oOut << "<fl c=\"1\">199.677</fl>";
  oOut << "<fl c=\"4\">5.60272</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">133.795</fl>";
  oOut << "<fl c=\"1\">17.8833</fl>";
  oOut << "<fl c=\"3\">63.5184</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">131.537</fl>";
  oOut << "<fl c=\"1\">93.4326</fl>";
  oOut << "<fl c=\"3\">77.8049</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">132.428</fl>";
  oOut << "<fl c=\"1\">100.903</fl>";
  oOut << "<fl c=\"3\">44.4791</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">132.202</fl>";
  oOut << "<fl c=\"1\">119.354</fl>";
  oOut << "<fl c=\"3\">91.3208</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">135.901</fl>";
  oOut << "<fl c=\"1\">113.452</fl>";
  oOut << "<fl c=\"3\">26.5845</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"2\">";
  oOut << "<fl c=\"0\">129.12</fl>";
  oOut << "<fl c=\"1\">113.702</fl>";
  oOut << "<fl c=\"4\">9.88025</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">133.502</fl>";
  oOut << "<fl c=\"1\">126.794</fl>";
  oOut << "<fl c=\"3\">12.4371</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">133.618</fl>";
  oOut << "<fl c=\"1\">128.082</fl>";
  oOut << "<fl c=\"3\">82.0486</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">133.801</fl>";
  oOut << "<fl c=\"1\">129.919</fl>";
  oOut << "<fl c=\"3\">45.9674</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">131.775</fl>";
  oOut << "<fl c=\"1\">156.055</fl>";
  oOut << "<fl c=\"3\">13.6221</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"2\">";
  oOut << "<fl c=\"0\">129.236</fl>";
  oOut << "<fl c=\"1\">170.416</fl>";
  oOut << "<fl c=\"4\">5.98972</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">134.082</fl>";
  oOut << "<fl c=\"1\">185.791</fl>";
  oOut << "<fl c=\"3\">11.488</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">132.3</fl>";
  oOut << "<fl c=\"1\">194.159</fl>";
  oOut << "<fl c=\"3\">90.7178</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">139.502</fl>";
  oOut << "<fl c=\"1\">23.2483</fl>";
  oOut << "<fl c=\"3\">93.9572</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"2\">";
  oOut << "<fl c=\"0\">143.28</fl>";
  oOut << "<fl c=\"1\">29.9011</fl>";
  oOut << "<fl c=\"4\">0.355499</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">143.878</fl>";
  oOut << "<fl c=\"1\">37.5916</fl>";
  oOut << "<fl c=\"3\">20.4703</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"2\">";
  oOut << "<fl c=\"0\">139.685</fl>";
  oOut << "<fl c=\"1\">47.9431</fl>";
  oOut << "<fl c=\"4\">7.64508</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">136.108</fl>";
  oOut << "<fl c=\"1\">62.5061</fl>";
  oOut << "<fl c=\"3\">19.9609</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">142.78</fl>";
  oOut << "<fl c=\"1\">66.0706</fl>";
  oOut << "<fl c=\"3\">38.5056</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">137.219</fl>";
  oOut << "<fl c=\"1\">70.6909</fl>";
  oOut << "<fl c=\"3\">10.4932</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">137.793</fl>";
  oOut << "<fl c=\"1\">139.166</fl>";
  oOut << "<fl c=\"3\">54.2325</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">138.751</fl>";
  oOut << "<fl c=\"1\">157.013</fl>";
  oOut << "<fl c=\"3\">78.9722</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">151.245</fl>";
  oOut << "<fl c=\"1\">5.10254</fl>";
  oOut << "<fl c=\"3\">29.7012</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">149.048</fl>";
  oOut << "<fl c=\"1\">16.4062</fl>";
  oOut << "<fl c=\"3\">53.0884</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">144</fl>";
  oOut << "<fl c=\"1\">40.5273</fl>";
  oOut << "<fl c=\"3\">97.226</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">148.279</fl>";
  oOut << "<fl c=\"1\">52.0447</fl>";
  oOut << "<fl c=\"3\">19.9344</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">145.654</fl>";
  oOut << "<fl c=\"1\">62.1033</fl>";
  oOut << "<fl c=\"3\">42.7368</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">151.813</fl>";
  oOut << "<fl c=\"1\">70.7886</fl>";
  oOut << "<fl c=\"3\">28.8422</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">146.027</fl>";
  oOut << "<fl c=\"1\">72.4121</fl>";
  oOut << "<fl c=\"3\">31.1221</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"2\">";
  oOut << "<fl c=\"0\">145.88</fl>";
  oOut << "<fl c=\"1\">86.7188</fl>";
  oOut << "<fl c=\"4\">0.120972</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">151.3</fl>";
  oOut << "<fl c=\"1\">100.049</fl>";
  oOut << "<fl c=\"3\">27.4146</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">150.464</fl>";
  oOut << "<fl c=\"1\">149.359</fl>";
  oOut << "<fl c=\"3\">81.7081</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">152.393</fl>";
  oOut << "<fl c=\"1\">21.6614</fl>";
  oOut << "<fl c=\"3\">82.1448</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">152.051</fl>";
  oOut << "<fl c=\"1\">23.7366</fl>";
  oOut << "<fl c=\"3\">51.0214</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">157.861</fl>";
  oOut << "<fl c=\"1\">65.0818</fl>";
  oOut << "<fl c=\"3\">74.1382</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">153.461</fl>";
  oOut << "<fl c=\"1\">69.1162</fl>";
  oOut << "<fl c=\"3\">41.922</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">156.903</fl>";
  oOut << "<fl c=\"1\">66.6321</fl>";
  oOut << "<fl c=\"3\">30.8554</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">154.962</fl>";
  oOut << "<fl c=\"1\">73.4985</fl>";
  oOut << "<fl c=\"3\">85.5139</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">155.176</fl>";
  oOut << "<fl c=\"1\">91.1621</fl>";
  oOut << "<fl c=\"3\">92.2083</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">156.195</fl>";
  oOut << "<fl c=\"1\">112.866</fl>";
  oOut << "<fl c=\"3\">69.3494</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">154.974</fl>";
  oOut << "<fl c=\"1\">125.421</fl>";
  oOut << "<fl c=\"3\">81.2216</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">156.226</fl>";
  oOut << "<fl c=\"1\">121.588</fl>";
  oOut << "<fl c=\"3\">79.7256</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">155.682</fl>";
  oOut << "<fl c=\"1\">140.912</fl>";
  oOut << "<fl c=\"3\">69.0521</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">152.148</fl>";
  oOut << "<fl c=\"1\">169.208</fl>";
  oOut << "<fl c=\"3\">27.005</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">154.028</fl>";
  oOut << "<fl c=\"1\">186.121</fl>";
  oOut << "<fl c=\"3\">70.6509</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">166.888</fl>";
  oOut << "<fl c=\"1\">35.3149</fl>";
  oOut << "<fl c=\"3\">83.1177</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">166.614</fl>";
  oOut << "<fl c=\"1\">46.875</fl>";
  oOut << "<fl c=\"3\">62.1439</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">166.235</fl>";
  oOut << "<fl c=\"1\">62.6831</fl>";
  oOut << "<fl c=\"3\">56.6229</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">166.736</fl>";
  oOut << "<fl c=\"1\">90.509</fl>";
  oOut << "<fl c=\"3\">94.4617</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"2\">";
  oOut << "<fl c=\"0\">166.87</fl>";
  oOut << "<fl c=\"1\">97.76</fl>";
  oOut << "<fl c=\"4\">0.116852</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">167.511</fl>";
  oOut << "<fl c=\"1\">118.958</fl>";
  oOut << "<fl c=\"3\">64.2972</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">160.223</fl>";
  oOut << "<fl c=\"1\">114.789</fl>";
  oOut << "<fl c=\"3\">57.8174</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">165.442</fl>";
  oOut << "<fl c=\"1\">145.685</fl>";
  oOut << "<fl c=\"3\">72.8882</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">161.804</fl>";
  oOut << "<fl c=\"1\">163.324</fl>";
  oOut << "<fl c=\"3\">51.702</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">164.105</fl>";
  oOut << "<fl c=\"1\">172.565</fl>";
  oOut << "<fl c=\"3\">35.1154</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">164.972</fl>";
  oOut << "<fl c=\"1\">183.441</fl>";
  oOut << "<fl c=\"3\">12.2888</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">160.394</fl>";
  oOut << "<fl c=\"1\">192.279</fl>";
  oOut << "<fl c=\"3\">76.1462</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">172.552</fl>";
  oOut << "<fl c=\"1\">12.5732</fl>";
  oOut << "<fl c=\"3\">72.7139</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"2\">";
  oOut << "<fl c=\"0\">170.764</fl>";
  oOut << "<fl c=\"1\">12.9761</fl>";
  oOut << "<fl c=\"4\">0.139954</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">174.805</fl>";
  oOut << "<fl c=\"1\">28.3264</fl>";
  oOut << "<fl c=\"3\">91.633</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">172.131</fl>";
  oOut << "<fl c=\"1\">37.9883</fl>";
  oOut << "<fl c=\"3\">54.4449</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">169.672</fl>";
  oOut << "<fl c=\"1\">46.7957</fl>";
  oOut << "<fl c=\"3\">10.6885</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">172.424</fl>";
  oOut << "<fl c=\"1\">67.2119</fl>";
  oOut << "<fl c=\"3\">64.8248</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"2\">";
  oOut << "<fl c=\"0\">173.914</fl>";
  oOut << "<fl c=\"1\">81.2988</fl>";
  oOut << "<fl c=\"4\">4.77957</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">173.346</fl>";
  oOut << "<fl c=\"1\">118.073</fl>";
  oOut << "<fl c=\"3\">47.9849</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">168.835</fl>";
  oOut << "<fl c=\"1\">131.921</fl>";
  oOut << "<fl c=\"3\">77.9413</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"2\">";
  oOut << "<fl c=\"0\">168.451</fl>";
  oOut << "<fl c=\"1\">130.634</fl>";
  oOut << "<fl c=\"4\">4.64279</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"2\">";
  oOut << "<fl c=\"0\">168.756</fl>";
  oOut << "<fl c=\"1\">178.687</fl>";
  oOut << "<fl c=\"4\">0.698883</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"2\">";
  oOut << "<fl c=\"0\">171.936</fl>";
  oOut << "<fl c=\"1\">191.76</fl>";
  oOut << "<fl c=\"4\">0.118103</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">177.496</fl>";
  oOut << "<fl c=\"1\">115.186</fl>";
  oOut << "<fl c=\"3\">28.9523</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"2\">";
  oOut << "<fl c=\"0\">182.184</fl>";
  oOut << "<fl c=\"1\">129.919</fl>";
  oOut << "<fl c=\"4\">4.99243</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">179.944</fl>";
  oOut << "<fl c=\"1\">155.145</fl>";
  oOut << "<fl c=\"3\">44.6997</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">178.333</fl>";
  oOut << "<fl c=\"1\">173.926</fl>";
  oOut << "<fl c=\"3\">82.7478</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">184.625</fl>";
  oOut << "<fl c=\"1\">2.81372</fl>";
  oOut << "<fl c=\"3\">92.1042</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">190.466</fl>";
  oOut << "<fl c=\"1\">12.6465</fl>";
  oOut << "<fl c=\"3\">47.4664</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">189.929</fl>";
  oOut << "<fl c=\"1\">35.6934</fl>";
  oOut << "<fl c=\"3\">13.1616</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">191.26</fl>";
  oOut << "<fl c=\"1\">68.5974</fl>";
  oOut << "<fl c=\"3\">68.6554</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">189.374</fl>";
  oOut << "<fl c=\"1\">71.1121</fl>";
  oOut << "<fl c=\"3\">42.4817</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">185.931</fl>";
  oOut << "<fl c=\"1\">79.3701</fl>";
  oOut << "<fl c=\"3\">28.7653</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"2\">";
  oOut << "<fl c=\"0\">184.003</fl>";
  oOut << "<fl c=\"1\">99.0662</fl>";
  oOut << "<fl c=\"4\">6.07596</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">187.262</fl>";
  oOut << "<fl c=\"1\">125.415</fl>";
  oOut << "<fl c=\"3\">52.0773</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">190.125</fl>";
  oOut << "<fl c=\"1\">120.685</fl>";
  oOut << "<fl c=\"3\">35.2078</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">184.558</fl>";
  oOut << "<fl c=\"1\">133.105</fl>";
  oOut << "<fl c=\"3\">26.5738</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"2\">";
  oOut << "<fl c=\"0\">187.921</fl>";
  oOut << "<fl c=\"1\">151.587</fl>";
  oOut << "<fl c=\"4\">0.231628</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">185.535</fl>";
  oOut << "<fl c=\"1\">159.662</fl>";
  oOut << "<fl c=\"3\">81.3635</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">187.518</fl>";
  oOut << "<fl c=\"1\">180.139</fl>";
  oOut << "<fl c=\"3\">30.8078</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">193.744</fl>";
  oOut << "<fl c=\"1\">79.6204</fl>";
  oOut << "<fl c=\"3\">55.8405</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">192.139</fl>";
  oOut << "<fl c=\"1\">113.525</fl>";
  oOut << "<fl c=\"3\">71.6766</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">194.598</fl>";
  oOut << "<fl c=\"1\">140.778</fl>";
  oOut << "<fl c=\"3\">94.4516</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">199.371</fl>";
  oOut << "<fl c=\"1\">156.976</fl>";
  oOut << "<fl c=\"3\">29.3338</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">196.729</fl>";
  oOut << "<fl c=\"1\">171.405</fl>";
  oOut << "<fl c=\"3\">34.7818</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"3\" tp=\"3\">";
  oOut << "<fl c=\"0\">193.976</fl>";
  oOut << "<fl c=\"1\">194.458</fl>";
  oOut << "<fl c=\"3\">30.1526</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">6.89087</fl>";
  oOut << "<fl c=\"1\">39.5203</fl>";
  oOut << "<fl c=\"3\">24.7052</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">4.32739</fl>";
  oOut << "<fl c=\"1\">46.8994</fl>";
  oOut << "<fl c=\"3\">21.9852</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">5.52368</fl>";
  oOut << "<fl c=\"1\">61.0229</fl>";
  oOut << "<fl c=\"3\">82.2104</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">7.66602</fl>";
  oOut << "<fl c=\"1\">76.4465</fl>";
  oOut << "<fl c=\"3\">34.2197</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">0.744629</fl>";
  oOut << "<fl c=\"1\">126.239</fl>";
  oOut << "<fl c=\"3\">64.1409</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">5.3772</fl>";
  oOut << "<fl c=\"1\">140.125</fl>";
  oOut << "<fl c=\"3\">37.2275</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"2\">";
  oOut << "<fl c=\"0\">4.64478</fl>";
  oOut << "<fl c=\"1\">140.503</fl>";
  oOut << "<fl c=\"4\">0.144775</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"2\">";
  oOut << "<fl c=\"0\">0.506592</fl>";
  oOut << "<fl c=\"1\">181.195</fl>";
  oOut << "<fl c=\"4\">0.119904</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">4.47388</fl>";
  oOut << "<fl c=\"1\">189.648</fl>";
  oOut << "<fl c=\"3\">59.92</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">15.2222</fl>";
  oOut << "<fl c=\"1\">26.5442</fl>";
  oOut << "<fl c=\"3\">27.4152</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">10.9436</fl>";
  oOut << "<fl c=\"1\">41.5161</fl>";
  oOut << "<fl c=\"3\">61.0507</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">15.3381</fl>";
  oOut << "<fl c=\"1\">68.8416</fl>";
  oOut << "<fl c=\"3\">25.9805</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">14.6179</fl>";
  oOut << "<fl c=\"1\">73.7183</fl>";
  oOut << "<fl c=\"3\">32.6947</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">10.6812</fl>";
  oOut << "<fl c=\"1\">98.9075</fl>";
  oOut << "<fl c=\"3\">73.6969</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"2\">";
  oOut << "<fl c=\"0\">15.0208</fl>";
  oOut << "<fl c=\"1\">124.097</fl>";
  oOut << "<fl c=\"4\">0.693573</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">12.4695</fl>";
  oOut << "<fl c=\"1\">128.717</fl>";
  oOut << "<fl c=\"3\">79.3292</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">10.3027</fl>";
  oOut << "<fl c=\"1\">175.47</fl>";
  oOut << "<fl c=\"3\">14.5648</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">9.76562</fl>";
  oOut << "<fl c=\"1\">187.72</fl>";
  oOut << "<fl c=\"3\">29.6579</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">10.2905</fl>";
  oOut << "<fl c=\"1\">192.236</fl>";
  oOut << "<fl c=\"3\">78.6148</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">18.6096</fl>";
  oOut << "<fl c=\"1\">26.3794</fl>";
  oOut << "<fl c=\"3\">98.6591</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">16.8701</fl>";
  oOut << "<fl c=\"1\">86.8958</fl>";
  oOut << "<fl c=\"3\">26.4551</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">22.8149</fl>";
  oOut << "<fl c=\"1\">88.0066</fl>";
  oOut << "<fl c=\"3\">97.3383</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">21.5393</fl>";
  oOut << "<fl c=\"1\">95.8557</fl>";
  oOut << "<fl c=\"3\">93.6292</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">17.7307</fl>";
  oOut << "<fl c=\"1\">92.4377</fl>";
  oOut << "<fl c=\"3\">88.9456</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">22.5098</fl>";
  oOut << "<fl c=\"1\">170.593</fl>";
  oOut << "<fl c=\"3\">39.6411</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">20.0012</fl>";
  oOut << "<fl c=\"1\">172.687</fl>";
  oOut << "<fl c=\"3\">36.5283</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">16.0217</fl>";
  oOut << "<fl c=\"1\">181.976</fl>";
  oOut << "<fl c=\"3\">54.0039</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">18.5486</fl>";
  oOut << "<fl c=\"1\">183.551</fl>";
  oOut << "<fl c=\"3\">44.8843</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">29.5593</fl>";
  oOut << "<fl c=\"1\">63.8489</fl>";
  oOut << "<fl c=\"3\">34.198</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"2\">";
  oOut << "<fl c=\"0\">27.0691</fl>";
  oOut << "<fl c=\"1\">58.2092</fl>";
  oOut << "<fl c=\"4\">7.98428</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">30.603</fl>";
  oOut << "<fl c=\"1\">65.4236</fl>";
  oOut << "<fl c=\"3\">49.375</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">26.2939</fl>";
  oOut << "<fl c=\"1\">84.5276</fl>";
  oOut << "<fl c=\"3\">58.0508</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">28.8818</fl>";
  oOut << "<fl c=\"1\">117.932</fl>";
  oOut << "<fl c=\"3\">12.991</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">24.4568</fl>";
  oOut << "<fl c=\"1\">150.647</fl>";
  oOut << "<fl c=\"3\">61.6232</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">25.3662</fl>";
  oOut << "<fl c=\"1\">147.314</fl>";
  oOut << "<fl c=\"3\">29.7968</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"2\">";
  oOut << "<fl c=\"0\">29.3213</fl>";
  oOut << "<fl c=\"1\">171.094</fl>";
  oOut << "<fl c=\"4\">8.46329</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"2\">";
  oOut << "<fl c=\"0\">24.6094</fl>";
  oOut << "<fl c=\"1\">169.244</fl>";
  oOut << "<fl c=\"4\">0.99295</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">29.9377</fl>";
  oOut << "<fl c=\"1\">188.239</fl>";
  oOut << "<fl c=\"3\">97.6373</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">36.9751</fl>";
  oOut << "<fl c=\"1\">62.5</fl>";
  oOut << "<fl c=\"3\">40.8957</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">37.616</fl>";
  oOut << "<fl c=\"1\">79.0405</fl>";
  oOut << "<fl c=\"3\">68.0954</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">36.3586</fl>";
  oOut << "<fl c=\"1\">101.831</fl>";
  oOut << "<fl c=\"3\">86.4801</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">36.6882</fl>";
  oOut << "<fl c=\"1\">124.536</fl>";
  oOut << "<fl c=\"3\">72.9596</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">35.8765</fl>";
  oOut << "<fl c=\"1\">168.518</fl>";
  oOut << "<fl c=\"3\">10.3006</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">35.6262</fl>";
  oOut << "<fl c=\"1\">192.2</fl>";
  oOut << "<fl c=\"3\">47.0511</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">34.0393</fl>";
  oOut << "<fl c=\"1\">197.827</fl>";
  oOut << "<fl c=\"3\">35.6265</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">44.7876</fl>";
  oOut << "<fl c=\"1\">6.65283</fl>";
  oOut << "<fl c=\"3\">54.4189</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">44.4336</fl>";
  oOut << "<fl c=\"1\">23.4863</fl>";
  oOut << "<fl c=\"3\">37.3267</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">40.5151</fl>";
  oOut << "<fl c=\"1\">28.7415</fl>";
  oOut << "<fl c=\"3\">29.2343</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"2\">";
  oOut << "<fl c=\"0\">47.0642</fl>";
  oOut << "<fl c=\"1\">31.2744</fl>";
  oOut << "<fl c=\"4\">2.91272</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">47.76</fl>";
  oOut << "<fl c=\"1\">42.3767</fl>";
  oOut << "<fl c=\"3\">18.3115</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">45.5627</fl>";
  oOut << "<fl c=\"1\">79.1504</fl>";
  oOut << "<fl c=\"3\">37.6816</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">43.4753</fl>";
  oOut << "<fl c=\"1\">80.7678</fl>";
  oOut << "<fl c=\"3\">19.7455</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"2\">";
  oOut << "<fl c=\"0\">45.5078</fl>";
  oOut << "<fl c=\"1\">167.48</fl>";
  oOut << "<fl c=\"4\">9.54517</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">45.7214</fl>";
  oOut << "<fl c=\"1\">199.78</fl>";
  oOut << "<fl c=\"3\">42.7408</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"2\">";
  oOut << "<fl c=\"0\">49.8474</fl>";
  oOut << "<fl c=\"1\">13.6292</fl>";
  oOut << "<fl c=\"4\">9.38339</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">54.5288</fl>";
  oOut << "<fl c=\"1\">37.03</fl>";
  oOut << "<fl c=\"3\">78.2883</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"2\">";
  oOut << "<fl c=\"0\">48.2239</fl>";
  oOut << "<fl c=\"1\">37.677</fl>";
  oOut << "<fl c=\"4\">2.51309</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"2\">";
  oOut << "<fl c=\"0\">48.8098</fl>";
  oOut << "<fl c=\"1\">59.1309</fl>";
  oOut << "<fl c=\"4\">1.38947</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">55.835</fl>";
  oOut << "<fl c=\"1\">126.947</fl>";
  oOut << "<fl c=\"3\">61.9293</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">51.2756</fl>";
  oOut << "<fl c=\"1\">146.735</fl>";
  oOut << "<fl c=\"3\">43.1937</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">54.9866</fl>";
  oOut << "<fl c=\"1\">173.016</fl>";
  oOut << "<fl c=\"3\">90.4865</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"2\">";
  oOut << "<fl c=\"0\">51.3123</fl>";
  oOut << "<fl c=\"1\">173.602</fl>";
  oOut << "<fl c=\"4\">3.11761</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">48.3582</fl>";
  oOut << "<fl c=\"1\">180.725</fl>";
  oOut << "<fl c=\"3\">19.2517</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">51.2451</fl>";
  oOut << "<fl c=\"1\">191.772</fl>";
  oOut << "<fl c=\"3\">54.1776</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">57.4097</fl>";
  oOut << "<fl c=\"1\">20.4346</fl>";
  oOut << "<fl c=\"3\">77.2064</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">56.4148</fl>";
  oOut << "<fl c=\"1\">52.832</fl>";
  oOut << "<fl c=\"3\">32.6462</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">57.5439</fl>";
  oOut << "<fl c=\"1\">54.5471</fl>";
  oOut << "<fl c=\"3\">31.586</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">62.323</fl>";
  oOut << "<fl c=\"1\">78.0151</fl>";
  oOut << "<fl c=\"3\">55.1169</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"2\">";
  oOut << "<fl c=\"0\">62.5671</fl>";
  oOut << "<fl c=\"1\">92.4377</fl>";
  oOut << "<fl c=\"4\">0.938507</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">57.074</fl>";
  oOut << "<fl c=\"1\">105.206</fl>";
  oOut << "<fl c=\"3\">73.0719</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">59.6069</fl>";
  oOut << "<fl c=\"1\">123.224</fl>";
  oOut << "<fl c=\"3\">49.8639</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">61.0901</fl>";
  oOut << "<fl c=\"1\">136.792</fl>";
  oOut << "<fl c=\"3\">92.6511</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">60.3821</fl>";
  oOut << "<fl c=\"1\">143.17</fl>";
  oOut << "<fl c=\"3\">55.8887</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">63.7329</fl>";
  oOut << "<fl c=\"1\">145.361</fl>";
  oOut << "<fl c=\"3\">95.1208</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">60.2112</fl>";
  oOut << "<fl c=\"1\">169.91</fl>";
  oOut << "<fl c=\"3\">89.7482</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">63.7024</fl>";
  oOut << "<fl c=\"1\">168.445</fl>";
  oOut << "<fl c=\"3\">59.5383</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">61.7432</fl>";
  oOut << "<fl c=\"1\">187.048</fl>";
  oOut << "<fl c=\"3\">87.233</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">66.0461</fl>";
  oOut << "<fl c=\"1\">133.484</fl>";
  oOut << "<fl c=\"3\">12.5513</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">65.1367</fl>";
  oOut << "<fl c=\"1\">160.986</fl>";
  oOut << "<fl c=\"3\">76.9843</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">65.7288</fl>";
  oOut << "<fl c=\"1\">181.073</fl>";
  oOut << "<fl c=\"3\">34.4217</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">64.4104</fl>";
  oOut << "<fl c=\"1\">197.852</fl>";
  oOut << "<fl c=\"3\">65.7321</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">74.0723</fl>";
  oOut << "<fl c=\"1\">1.06201</fl>";
  oOut << "<fl c=\"3\">92.7985</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">73.0591</fl>";
  oOut << "<fl c=\"1\">73.4619</fl>";
  oOut << "<fl c=\"3\">93.7881</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">79.2664</fl>";
  oOut << "<fl c=\"1\">93.6707</fl>";
  oOut << "<fl c=\"3\">70.4974</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">77.832</fl>";
  oOut << "<fl c=\"1\">152.216</fl>";
  oOut << "<fl c=\"3\">30.9406</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">78.5339</fl>";
  oOut << "<fl c=\"1\">168.329</fl>";
  oOut << "<fl c=\"3\">91.8478</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">78.5034</fl>";
  oOut << "<fl c=\"1\">172.992</fl>";
  oOut << "<fl c=\"3\">86.0126</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">82.3425</fl>";
  oOut << "<fl c=\"1\">35.1135</fl>";
  oOut << "<fl c=\"3\">32.2104</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">83.96</fl>";
  oOut << "<fl c=\"1\">65.4663</fl>";
  oOut << "<fl c=\"3\">43.0615</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"2\">";
  oOut << "<fl c=\"0\">84.7778</fl>";
  oOut << "<fl c=\"1\">71.5393</fl>";
  oOut << "<fl c=\"4\">4.46838</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">85.5774</fl>";
  oOut << "<fl c=\"1\">85.022</fl>";
  oOut << "<fl c=\"3\">69.5544</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">85.7361</fl>";
  oOut << "<fl c=\"1\">90.5518</fl>";
  oOut << "<fl c=\"3\">78.584</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">85.144</fl>";
  oOut << "<fl c=\"1\">107.77</fl>";
  oOut << "<fl c=\"3\">31.293</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">85.8704</fl>";
  oOut << "<fl c=\"1\">112.659</fl>";
  oOut << "<fl c=\"3\">13.2147</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">87.4329</fl>";
  oOut << "<fl c=\"1\">127.344</fl>";
  oOut << "<fl c=\"3\">66.3309</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">84.1553</fl>";
  oOut << "<fl c=\"1\">167.932</fl>";
  oOut << "<fl c=\"3\">62.3218</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">87.7808</fl>";
  oOut << "<fl c=\"1\">189.441</fl>";
  oOut << "<fl c=\"3\">56.8195</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">89.6545</fl>";
  oOut << "<fl c=\"1\">28.6316</fl>";
  oOut << "<fl c=\"3\">87.6587</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">92.6208</fl>";
  oOut << "<fl c=\"1\">43.3044</fl>";
  oOut << "<fl c=\"3\">41.6812</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">90.7959</fl>";
  oOut << "<fl c=\"1\">59.845</fl>";
  oOut << "<fl c=\"3\">45.1566</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">93.9453</fl>";
  oOut << "<fl c=\"1\">67.4561</fl>";
  oOut << "<fl c=\"3\">27.9095</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">91.8335</fl>";
  oOut << "<fl c=\"1\">81.6162</fl>";
  oOut << "<fl c=\"3\">47.3602</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">93.335</fl>";
  oOut << "<fl c=\"1\">99.4446</fl>";
  oOut << "<fl c=\"3\">19.6741</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">94.1345</fl>";
  oOut << "<fl c=\"1\">111.743</fl>";
  oOut << "<fl c=\"3\">39.0915</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"2\">";
  oOut << "<fl c=\"0\">90.0024</fl>";
  oOut << "<fl c=\"1\">122.888</fl>";
  oOut << "<fl c=\"4\">0.858124</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">88.4949</fl>";
  oOut << "<fl c=\"1\">165.308</fl>";
  oOut << "<fl c=\"3\">28.605</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">89.032</fl>";
  oOut << "<fl c=\"1\">169.348</fl>";
  oOut << "<fl c=\"3\">95.7108</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">88.9954</fl>";
  oOut << "<fl c=\"1\">187.689</fl>";
  oOut << "<fl c=\"3\">41.5155</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">102.997</fl>";
  oOut << "<fl c=\"1\">7.56836</fl>";
  oOut << "<fl c=\"3\">28.9514</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">103.693</fl>";
  oOut << "<fl c=\"1\">29.8462</fl>";
  oOut << "<fl c=\"3\">25.849</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"2\">";
  oOut << "<fl c=\"0\">101.41</fl>";
  oOut << "<fl c=\"1\">31.8481</fl>";
  oOut << "<fl c=\"4\">1.92203</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">97.1497</fl>";
  oOut << "<fl c=\"1\">34.0454</fl>";
  oOut << "<fl c=\"3\">46.2387</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">103.748</fl>";
  oOut << "<fl c=\"1\">64.1418</fl>";
  oOut << "<fl c=\"3\">67.9742</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">97.9004</fl>";
  oOut << "<fl c=\"1\">69.3909</fl>";
  oOut << "<fl c=\"3\">41.9073</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">98.7</fl>";
  oOut << "<fl c=\"1\">113.019</fl>";
  oOut << "<fl c=\"3\">26.4774</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">97.1191</fl>";
  oOut << "<fl c=\"1\">138.763</fl>";
  oOut << "<fl c=\"3\">95.9668</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">101.062</fl>";
  oOut << "<fl c=\"1\">159.46</fl>";
  oOut << "<fl c=\"3\">56.1948</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">111.963</fl>";
  oOut << "<fl c=\"1\">0.744629</fl>";
  oOut << "<fl c=\"3\">87.4756</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">104.089</fl>";
  oOut << "<fl c=\"1\">9.50928</fl>";
  oOut << "<fl c=\"3\">66.5573</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">106.055</fl>";
  oOut << "<fl c=\"1\">72.76</fl>";
  oOut << "<fl c=\"3\">92.067</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">110.858</fl>";
  oOut << "<fl c=\"1\">93.0115</fl>";
  oOut << "<fl c=\"3\">40.733</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">108.234</fl>";
  oOut << "<fl c=\"1\">95.9106</fl>";
  oOut << "<fl c=\"3\">32.2577</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">105.121</fl>";
  oOut << "<fl c=\"1\">96.4417</fl>";
  oOut << "<fl c=\"3\">25.961</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"2\">";
  oOut << "<fl c=\"0\">107.092</fl>";
  oOut << "<fl c=\"1\">138.367</fl>";
  oOut << "<fl c=\"4\">0.261871</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">110.59</fl>";
  oOut << "<fl c=\"1\">159.302</fl>";
  oOut << "<fl c=\"3\">81.0556</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">108.612</fl>";
  oOut << "<fl c=\"1\">161.707</fl>";
  oOut << "<fl c=\"3\">68.6798</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">108.997</fl>";
  oOut << "<fl c=\"1\">165.833</fl>";
  oOut << "<fl c=\"3\">14.7821</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">113.959</fl>";
  oOut << "<fl c=\"1\">2.52075</fl>";
  oOut << "<fl c=\"3\">76.4166</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">112.128</fl>";
  oOut << "<fl c=\"1\">18.8904</fl>";
  oOut << "<fl c=\"3\">97.0715</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"2\">";
  oOut << "<fl c=\"0\">119.995</fl>";
  oOut << "<fl c=\"1\">29.6753</fl>";
  oOut << "<fl c=\"4\">0.536987</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">118.036</fl>";
  oOut << "<fl c=\"1\">57.0435</fl>";
  oOut << "<fl c=\"3\">24.8669</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">116.058</fl>";
  oOut << "<fl c=\"1\">83.8013</fl>";
  oOut << "<fl c=\"3\">56.6986</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"2\">";
  oOut << "<fl c=\"0\">114.716</fl>";
  oOut << "<fl c=\"1\">93.7927</fl>";
  oOut << "<fl c=\"4\">9.44904</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">116.528</fl>";
  oOut << "<fl c=\"1\">112.451</fl>";
  oOut << "<fl c=\"3\">10.5423</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"2\">";
  oOut << "<fl c=\"0\">115.399</fl>";
  oOut << "<fl c=\"1\">157.19</fl>";
  oOut << "<fl c=\"4\">0.548431</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">113.257</fl>";
  oOut << "<fl c=\"1\">199.048</fl>";
  oOut << "<fl c=\"3\">93.6371</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">123.419</fl>";
  oOut << "<fl c=\"1\">23.3643</fl>";
  oOut << "<fl c=\"3\">17.7982</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"2\">";
  oOut << "<fl c=\"0\">125.916</fl>";
  oOut << "<fl c=\"1\">33.9905</fl>";
  oOut << "<fl c=\"4\">0.736176</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"2\">";
  oOut << "<fl c=\"0\">121.844</fl>";
  oOut << "<fl c=\"1\">77.3865</fl>";
  oOut << "<fl c=\"4\">0.261597</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">124.365</fl>";
  oOut << "<fl c=\"1\">169.507</fl>";
  oOut << "<fl c=\"3\">53.718</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">123.285</fl>";
  oOut << "<fl c=\"1\">187.439</fl>";
  oOut << "<fl c=\"3\">41.571</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">130.353</fl>";
  oOut << "<fl c=\"1\">1.96533</fl>";
  oOut << "<fl c=\"3\">49.3567</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">135.4</fl>";
  oOut << "<fl c=\"1\">23.3521</fl>";
  oOut << "<fl c=\"3\">32.3062</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">133.496</fl>";
  oOut << "<fl c=\"1\">46.814</fl>";
  oOut << "<fl c=\"3\">16.8073</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">128.888</fl>";
  oOut << "<fl c=\"1\">63.7573</fl>";
  oOut << "<fl c=\"3\">28.797</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">130.414</fl>";
  oOut << "<fl c=\"1\">56.0669</fl>";
  oOut << "<fl c=\"3\">20.8871</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">129.028</fl>";
  oOut << "<fl c=\"1\">109.155</fl>";
  oOut << "<fl c=\"3\">83.7466</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">134.21</fl>";
  oOut << "<fl c=\"1\">129.053</fl>";
  oOut << "<fl c=\"3\">81.3721</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">129.767</fl>";
  oOut << "<fl c=\"1\">188.483</fl>";
  oOut << "<fl c=\"3\">96.8378</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">143.201</fl>";
  oOut << "<fl c=\"1\">12.5671</fl>";
  oOut << "<fl c=\"3\">77.7448</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"2\">";
  oOut << "<fl c=\"0\">143.329</fl>";
  oOut << "<fl c=\"1\">44.7388</fl>";
  oOut << "<fl c=\"4\">0.60083</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">138.153</fl>";
  oOut << "<fl c=\"1\">59.1736</fl>";
  oOut << "<fl c=\"3\">86.0272</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">138.403</fl>";
  oOut << "<fl c=\"1\">71.0632</fl>";
  oOut << "<fl c=\"3\">53.0249</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">138.745</fl>";
  oOut << "<fl c=\"1\">82.5073</fl>";
  oOut << "<fl c=\"3\">97.3776</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"2\">";
  oOut << "<fl c=\"0\">139.557</fl>";
  oOut << "<fl c=\"1\">140.192</fl>";
  oOut << "<fl c=\"4\">5.12097</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">146.332</fl>";
  oOut << "<fl c=\"1\">14.0015</fl>";
  oOut << "<fl c=\"3\">75.5084</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">145.056</fl>";
  oOut << "<fl c=\"1\">33.1055</fl>";
  oOut << "<fl c=\"3\">69.5062</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"2\">";
  oOut << "<fl c=\"0\">146.924</fl>";
  oOut << "<fl c=\"1\">32.7332</fl>";
  oOut << "<fl c=\"4\">0.538849</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">145.172</fl>";
  oOut << "<fl c=\"1\">57.5256</fl>";
  oOut << "<fl c=\"3\">46.6653</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">151.941</fl>";
  oOut << "<fl c=\"1\">73.4802</fl>";
  oOut << "<fl c=\"3\">55.4453</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">148.651</fl>";
  oOut << "<fl c=\"1\">126.868</fl>";
  oOut << "<fl c=\"3\">96.1505</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">149.463</fl>";
  oOut << "<fl c=\"1\">151.44</fl>";
  oOut << "<fl c=\"3\">51.4249</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">144.916</fl>";
  oOut << "<fl c=\"1\">160.76</fl>";
  oOut << "<fl c=\"3\">66.4102</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">146.741</fl>";
  oOut << "<fl c=\"1\">160.51</fl>";
  oOut << "<fl c=\"3\">56.68</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">148.267</fl>";
  oOut << "<fl c=\"1\">182.318</fl>";
  oOut << "<fl c=\"3\">92.9678</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">156.732</fl>";
  oOut << "<fl c=\"1\">37.8967</fl>";
  oOut << "<fl c=\"3\">13.2489</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"2\">";
  oOut << "<fl c=\"0\">156.14</fl>";
  oOut << "<fl c=\"1\">49.0234</fl>";
  oOut << "<fl c=\"4\">4.48322</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">153.192</fl>";
  oOut << "<fl c=\"1\">64.8926</fl>";
  oOut << "<fl c=\"3\">37.8247</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">153.149</fl>";
  oOut << "<fl c=\"1\">64.3188</fl>";
  oOut << "<fl c=\"3\">22.8043</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">157.629</fl>";
  oOut << "<fl c=\"1\">79.2419</fl>";
  oOut << "<fl c=\"3\">65.4382</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">157.66</fl>";
  oOut << "<fl c=\"1\">81.9031</fl>";
  oOut << "<fl c=\"3\">18.8007</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">155.17</fl>";
  oOut << "<fl c=\"1\">104.962</fl>";
  oOut << "<fl c=\"3\">83.4784</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">159.937</fl>";
  oOut << "<fl c=\"1\">134.601</fl>";
  oOut << "<fl c=\"3\">78.0243</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">157.452</fl>";
  oOut << "<fl c=\"1\">134.991</fl>";
  oOut << "<fl c=\"3\">31.3168</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">157.77</fl>";
  oOut << "<fl c=\"1\">141.376</fl>";
  oOut << "<fl c=\"3\">74.6664</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"2\">";
  oOut << "<fl c=\"0\">154.425</fl>";
  oOut << "<fl c=\"1\">169.305</fl>";
  oOut << "<fl c=\"4\">2.83994</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"2\">";
  oOut << "<fl c=\"0\">159.052</fl>";
  oOut << "<fl c=\"1\">169.208</fl>";
  oOut << "<fl c=\"4\">0.325073</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">161.926</fl>";
  oOut << "<fl c=\"1\">5.58472</fl>";
  oOut << "<fl c=\"3\">51.4377</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">167.963</fl>";
  oOut << "<fl c=\"1\">39.3738</fl>";
  oOut << "<fl c=\"3\">60.3833</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">165.527</fl>";
  oOut << "<fl c=\"1\">38.2446</fl>";
  oOut << "<fl c=\"3\">54.4476</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">163.367</fl>";
  oOut << "<fl c=\"1\">33.5144</fl>";
  oOut << "<fl c=\"3\">19.1476</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"2\">";
  oOut << "<fl c=\"0\">164.307</fl>";
  oOut << "<fl c=\"1\">34.2468</fl>";
  oOut << "<fl c=\"4\">9.897</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">165.485</fl>";
  oOut << "<fl c=\"1\">143.365</fl>";
  oOut << "<fl c=\"3\">49.0317</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">165.259</fl>";
  oOut << "<fl c=\"1\">156.799</fl>";
  oOut << "<fl c=\"3\">82.699</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">167.078</fl>";
  oOut << "<fl c=\"1\">167.23</fl>";
  oOut << "<fl c=\"3\">62.4435</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">166.107</fl>";
  oOut << "<fl c=\"1\">188.129</fl>";
  oOut << "<fl c=\"3\">86.8234</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">169.226</fl>";
  oOut << "<fl c=\"1\">10.9009</fl>";
  oOut << "<fl c=\"3\">66.9174</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">172.351</fl>";
  oOut << "<fl c=\"1\">30.7617</fl>";
  oOut << "<fl c=\"3\">86.2024</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"2\">";
  oOut << "<fl c=\"0\">173.889</fl>";
  oOut << "<fl c=\"1\">25.5005</fl>";
  oOut << "<fl c=\"4\">6.92795</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">172.04</fl>";
  oOut << "<fl c=\"1\">35.7422</fl>";
  oOut << "<fl c=\"3\">83.8965</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">169.391</fl>";
  oOut << "<fl c=\"1\">56.2439</fl>";
  oOut << "<fl c=\"3\">41.3831</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">174.994</fl>";
  oOut << "<fl c=\"1\">72.1741</fl>";
  oOut << "<fl c=\"3\">29.7928</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"2\">";
  oOut << "<fl c=\"0\">175.122</fl>";
  oOut << "<fl c=\"1\">129.51</fl>";
  oOut << "<fl c=\"4\">0.81604</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">183.728</fl>";
  oOut << "<fl c=\"1\">5.0415</fl>";
  oOut << "<fl c=\"3\">76.1884</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">176.904</fl>";
  oOut << "<fl c=\"1\">15.1733</fl>";
  oOut << "<fl c=\"3\">17.8555</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"2\">";
  oOut << "<fl c=\"0\">178.894</fl>";
  oOut << "<fl c=\"1\">66.1438</fl>";
  oOut << "<fl c=\"4\">0.927246</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"2\">";
  oOut << "<fl c=\"0\">183.545</fl>";
  oOut << "<fl c=\"1\">71.4294</fl>";
  oOut << "<fl c=\"4\">0.365417</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">178.497</fl>";
  oOut << "<fl c=\"1\">81.9519</fl>";
  oOut << "<fl c=\"3\">69.1135</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"2\">";
  oOut << "<fl c=\"0\">182.166</fl>";
  oOut << "<fl c=\"1\">95.3491</fl>";
  oOut << "<fl c=\"4\">0.730316</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">180.286</fl>";
  oOut << "<fl c=\"1\">108.893</fl>";
  oOut << "<fl c=\"3\">77.4637</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">182.727</fl>";
  oOut << "<fl c=\"1\">120.795</fl>";
  oOut << "<fl c=\"3\">90.1965</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"2\">";
  oOut << "<fl c=\"0\">178.247</fl>";
  oOut << "<fl c=\"1\">143.713</fl>";
  oOut << "<fl c=\"4\">0.932129</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">179.108</fl>";
  oOut << "<fl c=\"1\">173.303</fl>";
  oOut << "<fl c=\"3\">27.3248</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">182.825</fl>";
  oOut << "<fl c=\"1\">184.155</fl>";
  oOut << "<fl c=\"3\">80.2859</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">188.086</fl>";
  oOut << "<fl c=\"1\">2.27051</fl>";
  oOut << "<fl c=\"3\">77.1536</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"2\">";
  oOut << "<fl c=\"0\">184.509</fl>";
  oOut << "<fl c=\"1\">15.5151</fl>";
  oOut << "<fl c=\"4\">4.68564</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"2\">";
  oOut << "<fl c=\"0\">191.888</fl>";
  oOut << "<fl c=\"1\">9.43604</fl>";
  oOut << "<fl c=\"4\">0.919647</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">189.703</fl>";
  oOut << "<fl c=\"1\">65.1428</fl>";
  oOut << "<fl c=\"3\">19.4406</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">191.241</fl>";
  oOut << "<fl c=\"1\">78.6011</fl>";
  oOut << "<fl c=\"3\">52.8055</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"2\">";
  oOut << "<fl c=\"0\">188.025</fl>";
  oOut << "<fl c=\"1\">81.7993</fl>";
  oOut << "<fl c=\"4\">2.33759</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">189.185</fl>";
  oOut << "<fl c=\"1\">95.52</fl>";
  oOut << "<fl c=\"3\">77.3013</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">185.889</fl>";
  oOut << "<fl c=\"1\">107.874</fl>";
  oOut << "<fl c=\"3\">67.4573</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">191.681</fl>";
  oOut << "<fl c=\"1\">149.353</fl>";
  oOut << "<fl c=\"3\">58.3801</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">198.608</fl>";
  oOut << "<fl c=\"1\">44.8059</fl>";
  oOut << "<fl c=\"3\">18.6597</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">197.308</fl>";
  oOut << "<fl c=\"1\">82.6538</fl>";
  oOut << "<fl c=\"3\">87.0148</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">193.073</fl>";
  oOut << "<fl c=\"1\">82.8125</fl>";
  oOut << "<fl c=\"3\">74.5889</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">195.819</fl>";
  oOut << "<fl c=\"1\">132.794</fl>";
  oOut << "<fl c=\"3\">88.3716</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"2\">";
  oOut << "<fl c=\"0\">199.341</fl>";
  oOut << "<fl c=\"1\">146.558</fl>";
  oOut << "<fl c=\"4\">9.01068</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"3\">";
  oOut << "<fl c=\"0\">194.452</fl>";
  oOut << "<fl c=\"1\">178.802</fl>";
  oOut << "<fl c=\"3\">13.5193</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"2\" tp=\"2\">";
  oOut << "<fl c=\"0\">195.874</fl>";
  oOut << "<fl c=\"1\">177.679</fl>";
  oOut << "<fl c=\"4\">1.64572</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">7.03125</fl>";
  oOut << "<fl c=\"1\">82.1716</fl>";
  oOut << "<fl c=\"3\">94.4907</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">7.2937</fl>";
  oOut << "<fl c=\"1\">82.8491</fl>";
  oOut << "<fl c=\"3\">51.0059</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">1.30005</fl>";
  oOut << "<fl c=\"1\">85.4675</fl>";
  oOut << "<fl c=\"3\">37.8787</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">2.62451</fl>";
  oOut << "<fl c=\"1\">96.6858</fl>";
  oOut << "<fl c=\"3\">77.612</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">1.15967</fl>";
  oOut << "<fl c=\"1\">99.1211</fl>";
  oOut << "<fl c=\"3\">27.0508</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"2\">";
  oOut << "<fl c=\"0\">4.88281</fl>";
  oOut << "<fl c=\"1\">122.552</fl>";
  oOut << "<fl c=\"4\">0.490051</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">5.71899</fl>";
  oOut << "<fl c=\"1\">144.849</fl>";
  oOut << "<fl c=\"3\">65.8121</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">3.96118</fl>";
  oOut << "<fl c=\"1\">153.894</fl>";
  oOut << "<fl c=\"3\">59.7031</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">3.39966</fl>";
  oOut << "<fl c=\"1\">162.634</fl>";
  oOut << "<fl c=\"3\">47.6489</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">2.47803</fl>";
  oOut << "<fl c=\"1\">178.595</fl>";
  oOut << "<fl c=\"3\">51.9742</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"2\">";
  oOut << "<fl c=\"0\">13.7878</fl>";
  oOut << "<fl c=\"1\">4.45557</fl>";
  oOut << "<fl c=\"4\">0.440552</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">12.7869</fl>";
  oOut << "<fl c=\"1\">8.81348</fl>";
  oOut << "<fl c=\"3\">67.1573</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">15.0879</fl>";
  oOut << "<fl c=\"1\">16.2659</fl>";
  oOut << "<fl c=\"3\">25.9573</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">8.1665</fl>";
  oOut << "<fl c=\"1\">28.2959</fl>";
  oOut << "<fl c=\"3\">54.8712</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">13.4583</fl>";
  oOut << "<fl c=\"1\">51.9043</fl>";
  oOut << "<fl c=\"3\">99.7977</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">11.1511</fl>";
  oOut << "<fl c=\"1\">53.1677</fl>";
  oOut << "<fl c=\"3\">30.8292</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"2\">";
  oOut << "<fl c=\"0\">10.4248</fl>";
  oOut << "<fl c=\"1\">64.4287</fl>";
  oOut << "<fl c=\"4\">6.80682</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">9.48486</fl>";
  oOut << "<fl c=\"1\">87.2803</fl>";
  oOut << "<fl c=\"3\">92.8543</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">9.33838</fl>";
  oOut << "<fl c=\"1\">86.4929</fl>";
  oOut << "<fl c=\"3\">31.7734</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">12.3108</fl>";
  oOut << "<fl c=\"1\">102.35</fl>";
  oOut << "<fl c=\"3\">96.1136</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">9.5459</fl>";
  oOut << "<fl c=\"1\">114.655</fl>";
  oOut << "<fl c=\"3\">51.6443</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">10.8154</fl>";
  oOut << "<fl c=\"1\">120.825</fl>";
  oOut << "<fl c=\"3\">42.0291</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">10.199</fl>";
  oOut << "<fl c=\"1\">141.699</fl>";
  oOut << "<fl c=\"3\">23.2291</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">15.1489</fl>";
  oOut << "<fl c=\"1\">191.254</fl>";
  oOut << "<fl c=\"3\">67.5153</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">18.457</fl>";
  oOut << "<fl c=\"1\">66.2415</fl>";
  oOut << "<fl c=\"3\">42.438</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">16.2048</fl>";
  oOut << "<fl c=\"1\">109.18</fl>";
  oOut << "<fl c=\"3\">14.4882</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"2\">";
  oOut << "<fl c=\"0\">23.0591</fl>";
  oOut << "<fl c=\"1\">106.61</fl>";
  oOut << "<fl c=\"4\">0.977722</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">21.814</fl>";
  oOut << "<fl c=\"1\">114.398</fl>";
  oOut << "<fl c=\"3\">85.8621</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">21.6064</fl>";
  oOut << "<fl c=\"1\">138.373</fl>";
  oOut << "<fl c=\"3\">80.5341</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"2\">";
  oOut << "<fl c=\"0\">23.9258</fl>";
  oOut << "<fl c=\"1\">142.303</fl>";
  oOut << "<fl c=\"4\">0.798492</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">21.1731</fl>";
  oOut << "<fl c=\"1\">163.885</fl>";
  oOut << "<fl c=\"3\">53.7296</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">21.1365</fl>";
  oOut << "<fl c=\"1\">185.858</fl>";
  oOut << "<fl c=\"3\">17.3123</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"2\">";
  oOut << "<fl c=\"0\">26.1353</fl>";
  oOut << "<fl c=\"1\">12.0361</fl>";
  oOut << "<fl c=\"4\">2.71552</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">24.3408</fl>";
  oOut << "<fl c=\"1\">36.7615</fl>";
  oOut << "<fl c=\"3\">48.1793</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"2\">";
  oOut << "<fl c=\"0\">24.115</fl>";
  oOut << "<fl c=\"1\">63.385</fl>";
  oOut << "<fl c=\"4\">0.25769</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">30.6274</fl>";
  oOut << "<fl c=\"1\">68.0908</fl>";
  oOut << "<fl c=\"3\">74.9478</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">30.0232</fl>";
  oOut << "<fl c=\"1\">76.8066</fl>";
  oOut << "<fl c=\"3\">97.3242</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">24.3286</fl>";
  oOut << "<fl c=\"1\">157.99</fl>";
  oOut << "<fl c=\"3\">37.3361</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">27.7771</fl>";
  oOut << "<fl c=\"1\">165.308</fl>";
  oOut << "<fl c=\"3\">99.9786</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">30.9814</fl>";
  oOut << "<fl c=\"1\">170.563</fl>";
  oOut << "<fl c=\"3\">63.8019</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"2\">";
  oOut << "<fl c=\"0\">38.6169</fl>";
  oOut << "<fl c=\"1\">30.7434</fl>";
  oOut << "<fl c=\"4\">0.619507</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">32.0557</fl>";
  oOut << "<fl c=\"1\">51.9958</fl>";
  oOut << "<fl c=\"3\">86.1874</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">38.2812</fl>";
  oOut << "<fl c=\"1\">52.655</fl>";
  oOut << "<fl c=\"3\">21.0965</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"2\">";
  oOut << "<fl c=\"0\">34.8328</fl>";
  oOut << "<fl c=\"1\">78.3508</fl>";
  oOut << "<fl c=\"4\">3.40518</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">38.0066</fl>";
  oOut << "<fl c=\"1\">83.2336</fl>";
  oOut << "<fl c=\"3\">41.1926</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">39.2395</fl>";
  oOut << "<fl c=\"1\">87.8357</fl>";
  oOut << "<fl c=\"3\">32.1518</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">32.1533</fl>";
  oOut << "<fl c=\"1\">123.181</fl>";
  oOut << "<fl c=\"3\">31.2845</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">46.5942</fl>";
  oOut << "<fl c=\"1\">29.9683</fl>";
  oOut << "<fl c=\"3\">35.5957</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">47.699</fl>";
  oOut << "<fl c=\"1\">36.5723</fl>";
  oOut << "<fl c=\"3\">79.1306</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">44.9829</fl>";
  oOut << "<fl c=\"1\">33.9539</fl>";
  oOut << "<fl c=\"3\">23.6572</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">44.6594</fl>";
  oOut << "<fl c=\"1\">73.0042</fl>";
  oOut << "<fl c=\"3\">22.6096</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">47.998</fl>";
  oOut << "<fl c=\"1\">93.4021</fl>";
  oOut << "<fl c=\"3\">95.1425</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">40.5762</fl>";
  oOut << "<fl c=\"1\">125.592</fl>";
  oOut << "<fl c=\"3\">69.8734</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">54.5044</fl>";
  oOut << "<fl c=\"1\">17.5354</fl>";
  oOut << "<fl c=\"3\">41.3925</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">55.7251</fl>";
  oOut << "<fl c=\"1\">37.4695</fl>";
  oOut << "<fl c=\"3\">85.6052</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">51.1841</fl>";
  oOut << "<fl c=\"1\">48.3032</fl>";
  oOut << "<fl c=\"3\">11.861</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">50.6165</fl>";
  oOut << "<fl c=\"1\">77.0691</fl>";
  oOut << "<fl c=\"3\">72.1301</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">48.0469</fl>";
  oOut << "<fl c=\"1\">89.1907</fl>";
  oOut << "<fl c=\"3\">18.9645</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"2\">";
  oOut << "<fl c=\"0\">48.4192</fl>";
  oOut << "<fl c=\"1\">126.709</fl>";
  oOut << "<fl c=\"4\">5.28055</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">53.772</fl>";
  oOut << "<fl c=\"1\">131.628</fl>";
  oOut << "<fl c=\"3\">63.7579</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">55.8228</fl>";
  oOut << "<fl c=\"1\">151.874</fl>";
  oOut << "<fl c=\"3\">99.4522</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">55.2368</fl>";
  oOut << "<fl c=\"1\">144.653</fl>";
  oOut << "<fl c=\"3\">93.0603</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">54.8523</fl>";
  oOut << "<fl c=\"1\">163.965</fl>";
  oOut << "<fl c=\"3\">87.8979</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">50.885</fl>";
  oOut << "<fl c=\"1\">166.345</fl>";
  oOut << "<fl c=\"3\">37.6669</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">52.7588</fl>";
  oOut << "<fl c=\"1\">174.06</fl>";
  oOut << "<fl c=\"3\">87.153</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">61.0596</fl>";
  oOut << "<fl c=\"1\">34.2102</fl>";
  oOut << "<fl c=\"3\">44.9008</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">63.4644</fl>";
  oOut << "<fl c=\"1\">38.6047</fl>";
  oOut << "<fl c=\"3\">17.3459</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">56.8359</fl>";
  oOut << "<fl c=\"1\">42.0837</fl>";
  oOut << "<fl c=\"3\">94.7501</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">60.7971</fl>";
  oOut << "<fl c=\"1\">49.3469</fl>";
  oOut << "<fl c=\"3\">83.4311</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">61.8469</fl>";
  oOut << "<fl c=\"1\">106.94</fl>";
  oOut << "<fl c=\"3\">89.1983</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">57.5378</fl>";
  oOut << "<fl c=\"1\">115.991</fl>";
  oOut << "<fl c=\"3\">48.9877</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">61.0229</fl>";
  oOut << "<fl c=\"1\">127.991</fl>";
  oOut << "<fl c=\"3\">82.5244</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">56.4148</fl>";
  oOut << "<fl c=\"1\">190.533</fl>";
  oOut << "<fl c=\"3\">82.4014</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">56.2561</fl>";
  oOut << "<fl c=\"1\">193.231</fl>";
  oOut << "<fl c=\"3\">27.5961</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"2\">";
  oOut << "<fl c=\"0\">67.4255</fl>";
  oOut << "<fl c=\"1\">15.8325</fl>";
  oOut << "<fl c=\"4\">7.66266</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">67.3767</fl>";
  oOut << "<fl c=\"1\">21.1365</fl>";
  oOut << "<fl c=\"3\">88.1223</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">70.2759</fl>";
  oOut << "<fl c=\"1\">21.759</fl>";
  oOut << "<fl c=\"3\">63.111</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">69.3848</fl>";
  oOut << "<fl c=\"1\">29.4861</fl>";
  oOut << "<fl c=\"3\">89.3964</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"2\">";
  oOut << "<fl c=\"0\">71.5698</fl>";
  oOut << "<fl c=\"1\">29.4067</fl>";
  oOut << "<fl c=\"4\">9.12576</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">70.7764</fl>";
  oOut << "<fl c=\"1\">85.3638</fl>";
  oOut << "<fl c=\"3\">67.8934</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"2\">";
  oOut << "<fl c=\"0\">67.3645</fl>";
  oOut << "<fl c=\"1\">97.4365</fl>";
  oOut << "<fl c=\"4\">8.3309</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">64.9048</fl>";
  oOut << "<fl c=\"1\">123.749</fl>";
  oOut << "<fl c=\"3\">36.6763</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">66.7664</fl>";
  oOut << "<fl c=\"1\">136.639</fl>";
  oOut << "<fl c=\"3\">38.7384</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">67.0715</fl>";
  oOut << "<fl c=\"1\">168.024</fl>";
  oOut << "<fl c=\"3\">80.3622</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"2\">";
  oOut << "<fl c=\"0\">77.9907</fl>";
  oOut << "<fl c=\"1\">31.0547</fl>";
  oOut << "<fl c=\"4\">0.246674</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"2\">";
  oOut << "<fl c=\"0\">72.8882</fl>";
  oOut << "<fl c=\"1\">57.0251</fl>";
  oOut << "<fl c=\"4\">0.302948</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">74.3042</fl>";
  oOut << "<fl c=\"1\">80.9998</fl>";
  oOut << "<fl c=\"3\">76.8146</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">77.9175</fl>";
  oOut << "<fl c=\"1\">94.0369</fl>";
  oOut << "<fl c=\"3\">28.5416</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">72.406</fl>";
  oOut << "<fl c=\"1\">131.665</fl>";
  oOut << "<fl c=\"3\">48.9996</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">78.2227</fl>";
  oOut << "<fl c=\"1\">190.918</fl>";
  oOut << "<fl c=\"3\">49.2001</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">86.8164</fl>";
  oOut << "<fl c=\"1\">41.6809</fl>";
  oOut << "<fl c=\"3\">44.4687</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">85.1135</fl>";
  oOut << "<fl c=\"1\">74.1882</fl>";
  oOut << "<fl c=\"3\">61.9946</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">87.8052</fl>";
  oOut << "<fl c=\"1\">118.939</fl>";
  oOut << "<fl c=\"3\">49.8526</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">83.8806</fl>";
  oOut << "<fl c=\"1\">133.972</fl>";
  oOut << "<fl c=\"3\">65.4797</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">83.8196</fl>";
  oOut << "<fl c=\"1\">168.127</fl>";
  oOut << "<fl c=\"3\">67.6575</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"2\">";
  oOut << "<fl c=\"0\">92.0227</fl>";
  oOut << "<fl c=\"1\">33.3191</fl>";
  oOut << "<fl c=\"4\">2.8078</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">91.3696</fl>";
  oOut << "<fl c=\"1\">113.629</fl>";
  oOut << "<fl c=\"3\">79.7092</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">91.7236</fl>";
  oOut << "<fl c=\"1\">115.771</fl>";
  oOut << "<fl c=\"3\">30.9253</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">93.8354</fl>";
  oOut << "<fl c=\"1\">142.859</fl>";
  oOut << "<fl c=\"3\">92.1274</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">95.9534</fl>";
  oOut << "<fl c=\"1\">149.744</fl>";
  oOut << "<fl c=\"3\">48.7903</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">98.8159</fl>";
  oOut << "<fl c=\"1\">7.02515</fl>";
  oOut << "<fl c=\"3\">17.5543</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"2\">";
  oOut << "<fl c=\"0\">97.6379</fl>";
  oOut << "<fl c=\"1\">15.033</fl>";
  oOut << "<fl c=\"4\">1.67456</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">99.4263</fl>";
  oOut << "<fl c=\"1\">46.8872</fl>";
  oOut << "<fl c=\"3\">57.7182</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">103.955</fl>";
  oOut << "<fl c=\"1\">49.1394</fl>";
  oOut << "<fl c=\"3\">71.7297</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">98.0896</fl>";
  oOut << "<fl c=\"1\">102.673</fl>";
  oOut << "<fl c=\"3\">17.4081</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">103.119</fl>";
  oOut << "<fl c=\"1\">145.947</fl>";
  oOut << "<fl c=\"3\">69.0469</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"2\">";
  oOut << "<fl c=\"0\">98.2422</fl>";
  oOut << "<fl c=\"1\">157.074</fl>";
  oOut << "<fl c=\"4\">0.519501</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">101.196</fl>";
  oOut << "<fl c=\"1\">179.803</fl>";
  oOut << "<fl c=\"3\">79.0756</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">102.74</fl>";
  oOut << "<fl c=\"1\">177.063</fl>";
  oOut << "<fl c=\"3\">14.7983</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">98.0591</fl>";
  oOut << "<fl c=\"1\">191.718</fl>";
  oOut << "<fl c=\"3\">12.9895</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">97.3572</fl>";
  oOut << "<fl c=\"1\">194.775</fl>";
  oOut << "<fl c=\"3\">10.6213</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">105.005</fl>";
  oOut << "<fl c=\"1\">0.415039</fl>";
  oOut << "<fl c=\"3\">58.8989</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">110.84</fl>";
  oOut << "<fl c=\"1\">29.3152</fl>";
  oOut << "<fl c=\"3\">29.1852</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">105.298</fl>";
  oOut << "<fl c=\"1\">63.4949</fl>";
  oOut << "<fl c=\"3\">16.6772</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">106.494</fl>";
  oOut << "<fl c=\"1\">104.681</fl>";
  oOut << "<fl c=\"3\">34.9564</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"2\">";
  oOut << "<fl c=\"0\">106.183</fl>";
  oOut << "<fl c=\"1\">121.539</fl>";
  oOut << "<fl c=\"4\">5.4816</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"2\">";
  oOut << "<fl c=\"0\">104.456</fl>";
  oOut << "<fl c=\"1\">122.357</fl>";
  oOut << "<fl c=\"4\">0.707458</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">109.235</fl>";
  oOut << "<fl c=\"1\">194.061</fl>";
  oOut << "<fl c=\"3\">91.5887</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">116.29</fl>";
  oOut << "<fl c=\"1\">111.719</fl>";
  oOut << "<fl c=\"3\">99.509</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"2\">";
  oOut << "<fl c=\"0\">113.647</fl>";
  oOut << "<fl c=\"1\">128.662</fl>";
  oOut << "<fl c=\"4\">0.466644</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">114.484</fl>";
  oOut << "<fl c=\"1\">140.784</fl>";
  oOut << "<fl c=\"3\">82.0862</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">114.844</fl>";
  oOut << "<fl c=\"1\">137.396</fl>";
  oOut << "<fl c=\"3\">35.6906</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">113.3</fl>";
  oOut << "<fl c=\"1\">142.78</fl>";
  oOut << "<fl c=\"3\">20.5756</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">114.954</fl>";
  oOut << "<fl c=\"1\">145.471</fl>";
  oOut << "<fl c=\"3\">28.4024</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">125.745</fl>";
  oOut << "<fl c=\"1\">5.59082</fl>";
  oOut << "<fl c=\"3\">44.7421</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">124.408</fl>";
  oOut << "<fl c=\"1\">23.3887</fl>";
  oOut << "<fl c=\"3\">64.2627</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">121.405</fl>";
  oOut << "<fl c=\"1\">59.0332</fl>";
  oOut << "<fl c=\"3\">18.3563</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">123.09</fl>";
  oOut << "<fl c=\"1\">65.5579</fl>";
  oOut << "<fl c=\"3\">27.0486</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">126.233</fl>";
  oOut << "<fl c=\"1\">110.962</fl>";
  oOut << "<fl c=\"3\">18.3704</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"2\">";
  oOut << "<fl c=\"0\">120.996</fl>";
  oOut << "<fl c=\"1\">129.846</fl>";
  oOut << "<fl c=\"4\">1.61716</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">124.805</fl>";
  oOut << "<fl c=\"1\">149.908</fl>";
  oOut << "<fl c=\"3\">56.6379</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">120.85</fl>";
  oOut << "<fl c=\"1\">187.524</fl>";
  oOut << "<fl c=\"3\">83.2361</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"2\">";
  oOut << "<fl c=\"0\">124.969</fl>";
  oOut << "<fl c=\"1\">189.423</fl>";
  oOut << "<fl c=\"4\">7.05704</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">126.343</fl>";
  oOut << "<fl c=\"1\">198.877</fl>";
  oOut << "<fl c=\"3\">49.57</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"2\">";
  oOut << "<fl c=\"0\">129.095</fl>";
  oOut << "<fl c=\"1\">10.0342</fl>";
  oOut << "<fl c=\"4\">6.12265</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">130.725</fl>";
  oOut << "<fl c=\"1\">17.5293</fl>";
  oOut << "<fl c=\"3\">42.6157</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">134.802</fl>";
  oOut << "<fl c=\"1\">41.7236</fl>";
  oOut << "<fl c=\"3\">58.4354</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">129.279</fl>";
  oOut << "<fl c=\"1\">90.5762</fl>";
  oOut << "<fl c=\"3\">41.9128</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">129.962</fl>";
  oOut << "<fl c=\"1\">110.181</fl>";
  oOut << "<fl c=\"3\">95.0616</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">134.454</fl>";
  oOut << "<fl c=\"1\">109.259</fl>";
  oOut << "<fl c=\"3\">78.1815</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"2\">";
  oOut << "<fl c=\"0\">133.539</fl>";
  oOut << "<fl c=\"1\">122.156</fl>";
  oOut << "<fl c=\"4\">7.64206</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">132.745</fl>";
  oOut << "<fl c=\"1\">135.443</fl>";
  oOut << "<fl c=\"3\">20.0974</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"2\">";
  oOut << "<fl c=\"0\">128.699</fl>";
  oOut << "<fl c=\"1\">150.848</fl>";
  oOut << "<fl c=\"4\">0.800446</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">133.582</fl>";
  oOut << "<fl c=\"1\">170.325</fl>";
  oOut << "<fl c=\"3\">50.9219</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">128.137</fl>";
  oOut << "<fl c=\"1\">177.222</fl>";
  oOut << "<fl c=\"3\">43.4476</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">141.272</fl>";
  oOut << "<fl c=\"1\">10.0159</fl>";
  oOut << "<fl c=\"3\">67.4753</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">138.812</fl>";
  oOut << "<fl c=\"1\">30.7678</fl>";
  oOut << "<fl c=\"3\">62.439</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">140.552</fl>";
  oOut << "<fl c=\"1\">58.1909</fl>";
  oOut << "<fl c=\"3\">25.9009</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"2\">";
  oOut << "<fl c=\"0\">138.947</fl>";
  oOut << "<fl c=\"1\">123.492</fl>";
  oOut << "<fl c=\"4\">0.637238</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">137.598</fl>";
  oOut << "<fl c=\"1\">170.837</fl>";
  oOut << "<fl c=\"3\">77.0963</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">140.747</fl>";
  oOut << "<fl c=\"1\">171.735</fl>";
  oOut << "<fl c=\"3\">10.3741</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">138.159</fl>";
  oOut << "<fl c=\"1\">183.856</fl>";
  oOut << "<fl c=\"3\">76.3263</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">137.238</fl>";
  oOut << "<fl c=\"1\">197.528</fl>";
  oOut << "<fl c=\"3\">71.0455</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">145.77</fl>";
  oOut << "<fl c=\"1\">0.45166</fl>";
  oOut << "<fl c=\"3\">44.6664</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">146.545</fl>";
  oOut << "<fl c=\"1\">17.3462</fl>";
  oOut << "<fl c=\"3\">71.8576</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">149.902</fl>";
  oOut << "<fl c=\"1\">23.1445</fl>";
  oOut << "<fl c=\"3\">55.3406</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">146.844</fl>";
  oOut << "<fl c=\"1\">80.1208</fl>";
  oOut << "<fl c=\"3\">31.5463</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">149.689</fl>";
  oOut << "<fl c=\"1\">100.464</fl>";
  oOut << "<fl c=\"3\">74.3665</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">149.316</fl>";
  oOut << "<fl c=\"1\">105.365</fl>";
  oOut << "<fl c=\"3\">78.9404</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"2\">";
  oOut << "<fl c=\"0\">144.824</fl>";
  oOut << "<fl c=\"1\">119.379</fl>";
  oOut << "<fl c=\"4\">2.79517</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">151.129</fl>";
  oOut << "<fl c=\"1\">131.903</fl>";
  oOut << "<fl c=\"3\">51.4929</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">145.001</fl>";
  oOut << "<fl c=\"1\">170.355</fl>";
  oOut << "<fl c=\"3\">97.0227</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">144.879</fl>";
  oOut << "<fl c=\"1\">170.807</fl>";
  oOut << "<fl c=\"3\">27.5662</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">150.067</fl>";
  oOut << "<fl c=\"1\">179.663</fl>";
  oOut << "<fl c=\"3\">23.1686</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"2\">";
  oOut << "<fl c=\"0\">150.079</fl>";
  oOut << "<fl c=\"1\">187.64</fl>";
  oOut << "<fl c=\"4\">7.47205</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">149.835</fl>";
  oOut << "<fl c=\"1\">193.793</fl>";
  oOut << "<fl c=\"3\">37.8491</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">152.319</fl>";
  oOut << "<fl c=\"1\">19.4397</fl>";
  oOut << "<fl c=\"3\">66.2836</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">152.704</fl>";
  oOut << "<fl c=\"1\">20.4834</fl>";
  oOut << "<fl c=\"3\">50.9662</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">158.728</fl>";
  oOut << "<fl c=\"1\">32.5134</fl>";
  oOut << "<fl c=\"3\">31.8536</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">153.021</fl>";
  oOut << "<fl c=\"1\">59.3689</fl>";
  oOut << "<fl c=\"3\">33.215</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">157.025</fl>";
  oOut << "<fl c=\"1\">61.7126</fl>";
  oOut << "<fl c=\"3\">15.0421</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">159.192</fl>";
  oOut << "<fl c=\"1\">105.145</fl>";
  oOut << "<fl c=\"3\">48.6996</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">158.954</fl>";
  oOut << "<fl c=\"1\">131.744</fl>";
  oOut << "<fl c=\"3\">73.7122</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">158.563</fl>";
  oOut << "<fl c=\"1\">182.782</fl>";
  oOut << "<fl c=\"3\">96.626</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"2\">";
  oOut << "<fl c=\"0\">164.111</fl>";
  oOut << "<fl c=\"1\">28.6133</fl>";
  oOut << "<fl c=\"4\">0.232513</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">163.916</fl>";
  oOut << "<fl c=\"1\">42.395</fl>";
  oOut << "<fl c=\"3\">75.0024</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"2\">";
  oOut << "<fl c=\"0\">165.167</fl>";
  oOut << "<fl c=\"1\">64.2334</fl>";
  oOut << "<fl c=\"4\">0.20813</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">167.847</fl>";
  oOut << "<fl c=\"1\">76.6663</fl>";
  oOut << "<fl c=\"3\">24.5239</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"2\">";
  oOut << "<fl c=\"0\">163.068</fl>";
  oOut << "<fl c=\"1\">101.776</fl>";
  oOut << "<fl c=\"4\">0.513916</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">164.343</fl>";
  oOut << "<fl c=\"1\">142.999</fl>";
  oOut << "<fl c=\"3\">52.0206</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">160.626</fl>";
  oOut << "<fl c=\"1\">189.24</fl>";
  oOut << "<fl c=\"3\">81.3766</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">162.048</fl>";
  oOut << "<fl c=\"1\">192.566</fl>";
  oOut << "<fl c=\"3\">12.5766</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"2\">";
  oOut << "<fl c=\"0\">172.485</fl>";
  oOut << "<fl c=\"1\">27.6489</fl>";
  oOut << "<fl c=\"4\">4.6546</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">169.208</fl>";
  oOut << "<fl c=\"1\">32.1838</fl>";
  oOut << "<fl c=\"3\">90.0916</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">174.701</fl>";
  oOut << "<fl c=\"1\">52.1912</fl>";
  oOut << "<fl c=\"3\">64.8907</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">173.486</fl>";
  oOut << "<fl c=\"1\">63.3362</fl>";
  oOut << "<fl c=\"3\">76.8973</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">173.615</fl>";
  oOut << "<fl c=\"1\">71.2341</fl>";
  oOut << "<fl c=\"3\">18.2758</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">172.528</fl>";
  oOut << "<fl c=\"1\">121.802</fl>";
  oOut << "<fl c=\"3\">85.5997</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">174.408</fl>";
  oOut << "<fl c=\"1\">168.988</fl>";
  oOut << "<fl c=\"3\">51.7786</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">168.182</fl>";
  oOut << "<fl c=\"1\">181</fl>";
  oOut << "<fl c=\"3\">83.5001</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">172.284</fl>";
  oOut << "<fl c=\"1\">196.6</fl>";
  oOut << "<fl c=\"3\">55.9174</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">180.804</fl>";
  oOut << "<fl c=\"1\">20.5444</fl>";
  oOut << "<fl c=\"3\">90.9647</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">176.971</fl>";
  oOut << "<fl c=\"1\">38.3728</fl>";
  oOut << "<fl c=\"3\">33.7769</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"2\">";
  oOut << "<fl c=\"0\">179.309</fl>";
  oOut << "<fl c=\"1\">42.7917</fl>";
  oOut << "<fl c=\"4\">6.25092</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">176.514</fl>";
  oOut << "<fl c=\"1\">56.1462</fl>";
  oOut << "<fl c=\"3\">39.3463</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">177.942</fl>";
  oOut << "<fl c=\"1\">79.1016</fl>";
  oOut << "<fl c=\"3\">58.6774</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">179.48</fl>";
  oOut << "<fl c=\"1\">100.677</fl>";
  oOut << "<fl c=\"3\">17.627</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"2\">";
  oOut << "<fl c=\"0\">181.342</fl>";
  oOut << "<fl c=\"1\">109.18</fl>";
  oOut << "<fl c=\"4\">0.738068</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">182.916</fl>";
  oOut << "<fl c=\"1\">135.376</fl>";
  oOut << "<fl c=\"3\">82.1014</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">181.995</fl>";
  oOut << "<fl c=\"1\">131.866</fl>";
  oOut << "<fl c=\"3\">37.9742</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">176.16</fl>";
  oOut << "<fl c=\"1\">147.064</fl>";
  oOut << "<fl c=\"3\">61.8173</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">178.772</fl>";
  oOut << "<fl c=\"1\">161.377</fl>";
  oOut << "<fl c=\"3\">11.1206</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"2\">";
  oOut << "<fl c=\"0\">179.816</fl>";
  oOut << "<fl c=\"1\">199.554</fl>";
  oOut << "<fl c=\"4\">6.98535</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">190.619</fl>";
  oOut << "<fl c=\"1\">26.4771</fl>";
  oOut << "<fl c=\"3\">70.867</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"2\">";
  oOut << "<fl c=\"0\">189.374</fl>";
  oOut << "<fl c=\"1\">80.542</fl>";
  oOut << "<fl c=\"4\">0.707214</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">184.857</fl>";
  oOut << "<fl c=\"1\">91.0767</fl>";
  oOut << "<fl c=\"3\">28.3304</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">190.161</fl>";
  oOut << "<fl c=\"1\">142.224</fl>";
  oOut << "<fl c=\"3\">51.2299</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">190.265</fl>";
  oOut << "<fl c=\"1\">172.699</fl>";
  oOut << "<fl c=\"3\">24.7986</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">189.032</fl>";
  oOut << "<fl c=\"1\">180.627</fl>";
  oOut << "<fl c=\"3\">14.8737</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"2\">";
  oOut << "<fl c=\"0\">189.349</fl>";
  oOut << "<fl c=\"1\">191.113</fl>";
  oOut << "<fl c=\"4\">0.967651</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">189.648</fl>";
  oOut << "<fl c=\"1\">194.086</fl>";
  oOut << "<fl c=\"3\">99.7717</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">198.431</fl>";
  oOut << "<fl c=\"1\">16.3879</fl>";
  oOut << "<fl c=\"3\">25.7132</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"2\">";
  oOut << "<fl c=\"0\">193.097</fl>";
  oOut << "<fl c=\"1\">43.7378</fl>";
  oOut << "<fl c=\"4\">0.981842</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">193.25</fl>";
  oOut << "<fl c=\"1\">84.3079</fl>";
  oOut << "<fl c=\"3\">67.2281</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">195.294</fl>";
  oOut << "<fl c=\"1\">103.076</fl>";
  oOut << "<fl c=\"3\">76.7252</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">196.606</fl>";
  oOut << "<fl c=\"1\">99.8108</fl>";
  oOut << "<fl c=\"3\">55.8298</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">198.602</fl>";
  oOut << "<fl c=\"1\">116.766</fl>";
  oOut << "<fl c=\"3\">98.623</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">193.341</fl>";
  oOut << "<fl c=\"1\">115.686</fl>";
  oOut << "<fl c=\"3\">88.1577</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"2\">";
  oOut << "<fl c=\"0\">193.823</fl>";
  oOut << "<fl c=\"1\">140.167</fl>";
  oOut << "<fl c=\"4\">8.37155</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"1\" tp=\"3\">";
  oOut << "<fl c=\"0\">194.165</fl>";
  oOut << "<fl c=\"1\">169.69</fl>";
  oOut << "<fl c=\"3\">65.2725</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"2\">";
  oOut << "<fl c=\"0\">7.05566</fl>";
  oOut << "<fl c=\"1\">26.1169</fl>";
  oOut << "<fl c=\"4\">5.216</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">6.06079</fl>";
  oOut << "<fl c=\"1\">43.5608</fl>";
  oOut << "<fl c=\"3\">47.644</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">1.97754</fl>";
  oOut << "<fl c=\"1\">56.6833</fl>";
  oOut << "<fl c=\"3\">54.7855</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"2\">";
  oOut << "<fl c=\"0\">6.65283</fl>";
  oOut << "<fl c=\"1\">71.1426</fl>";
  oOut << "<fl c=\"4\">0.664856</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"2\">";
  oOut << "<fl c=\"0\">0.323486</fl>";
  oOut << "<fl c=\"1\">81.9641</fl>";
  oOut << "<fl c=\"4\">1.14694</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">6.88477</fl>";
  oOut << "<fl c=\"1\">100.94</fl>";
  oOut << "<fl c=\"3\">50.7898</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">5.33447</fl>";
  oOut << "<fl c=\"1\">149.139</fl>";
  oOut << "<fl c=\"3\">36.4764</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"2\">";
  oOut << "<fl c=\"0\">0.610352</fl>";
  oOut << "<fl c=\"1\">157.44</fl>";
  oOut << "<fl c=\"4\">0.376617</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">0.738525</fl>";
  oOut << "<fl c=\"1\">167.12</fl>";
  oOut << "<fl c=\"3\">15.675</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">6.56128</fl>";
  oOut << "<fl c=\"1\">179.218</fl>";
  oOut << "<fl c=\"3\">81.922</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">4.05273</fl>";
  oOut << "<fl c=\"1\">197.821</fl>";
  oOut << "<fl c=\"3\">96.4136</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">4.06494</fl>";
  oOut << "<fl c=\"1\">199.231</fl>";
  oOut << "<fl c=\"3\">24.9515</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"2\">";
  oOut << "<fl c=\"0\">8.30078</fl>";
  oOut << "<fl c=\"1\">33.0322</fl>";
  oOut << "<fl c=\"4\">0.435669</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">15.8264</fl>";
  oOut << "<fl c=\"1\">54.3884</fl>";
  oOut << "<fl c=\"3\">75.0156</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"2\">";
  oOut << "<fl c=\"0\">14.7827</fl>";
  oOut << "<fl c=\"1\">50.8606</fl>";
  oOut << "<fl c=\"4\">9.37241</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">11.6516</fl>";
  oOut << "<fl c=\"1\">65.9912</fl>";
  oOut << "<fl c=\"3\">44.5438</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">11.908</fl>";
  oOut << "<fl c=\"1\">76.7944</fl>";
  oOut << "<fl c=\"3\">30.4187</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">10.675</fl>";
  oOut << "<fl c=\"1\">85.2356</fl>";
  oOut << "<fl c=\"3\">76.7548</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">8.40454</fl>";
  oOut << "<fl c=\"1\">98.7061</fl>";
  oOut << "<fl c=\"3\">76.5887</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"2\">";
  oOut << "<fl c=\"0\">10.8582</fl>";
  oOut << "<fl c=\"1\">98.8159</fl>";
  oOut << "<fl c=\"4\">6.27426</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">13.2874</fl>";
  oOut << "<fl c=\"1\">192.291</fl>";
  oOut << "<fl c=\"3\">66.6309</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">18.2556</fl>";
  oOut << "<fl c=\"1\">32.5623</fl>";
  oOut << "<fl c=\"3\">50.9213</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">17.0593</fl>";
  oOut << "<fl c=\"1\">35.7788</fl>";
  oOut << "<fl c=\"3\">39.2218</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">16.449</fl>";
  oOut << "<fl c=\"1\">49.4385</fl>";
  oOut << "<fl c=\"3\">29.9878</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">23.5046</fl>";
  oOut << "<fl c=\"1\">84.1248</fl>";
  oOut << "<fl c=\"3\">38.1808</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">17.0776</fl>";
  oOut << "<fl c=\"1\">105.554</fl>";
  oOut << "<fl c=\"3\">27.8323</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">22.6257</fl>";
  oOut << "<fl c=\"1\">142.468</fl>";
  oOut << "<fl c=\"3\">85.5286</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">21.1365</fl>";
  oOut << "<fl c=\"1\">139.081</fl>";
  oOut << "<fl c=\"3\">52.1997</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"2\">";
  oOut << "<fl c=\"0\">22.9187</fl>";
  oOut << "<fl c=\"1\">140.265</fl>";
  oOut << "<fl c=\"4\">7.72116</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"2\">";
  oOut << "<fl c=\"0\">21.7957</fl>";
  oOut << "<fl c=\"1\">139.642</fl>";
  oOut << "<fl c=\"4\">0.555725</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">20.1904</fl>";
  oOut << "<fl c=\"1\">194.47</fl>";
  oOut << "<fl c=\"3\">53.8431</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">25.2869</fl>";
  oOut << "<fl c=\"1\">111.749</fl>";
  oOut << "<fl c=\"3\">80.0323</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">25.7629</fl>";
  oOut << "<fl c=\"1\">117.81</fl>";
  oOut << "<fl c=\"3\">40.477</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">28.9612</fl>";
  oOut << "<fl c=\"1\">126.093</fl>";
  oOut << "<fl c=\"3\">45.2948</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"2\">";
  oOut << "<fl c=\"0\">26.5686</fl>";
  oOut << "<fl c=\"1\">122.839</fl>";
  oOut << "<fl c=\"4\">4.90399</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"2\">";
  oOut << "<fl c=\"0\">24.2859</fl>";
  oOut << "<fl c=\"1\">134.247</fl>";
  oOut << "<fl c=\"4\">0.593811</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">28.0762</fl>";
  oOut << "<fl c=\"1\">190.924</fl>";
  oOut << "<fl c=\"3\">73.8974</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">39.7461</fl>";
  oOut << "<fl c=\"1\">5.43823</fl>";
  oOut << "<fl c=\"3\">79.9933</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">34.0149</fl>";
  oOut << "<fl c=\"1\">27.0752</fl>";
  oOut << "<fl c=\"3\">95.9747</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"2\">";
  oOut << "<fl c=\"0\">39.4165</fl>";
  oOut << "<fl c=\"1\">42.334</fl>";
  oOut << "<fl c=\"4\">8.22571</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">34.4666</fl>";
  oOut << "<fl c=\"1\">48.0591</fl>";
  oOut << "<fl c=\"3\">97.6416</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">37.8418</fl>";
  oOut << "<fl c=\"1\">48.4497</fl>";
  oOut << "<fl c=\"3\">93.4204</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">39.1602</fl>";
  oOut << "<fl c=\"1\">53.2349</fl>";
  oOut << "<fl c=\"3\">37.963</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">35.4431</fl>";
  oOut << "<fl c=\"1\">65.979</fl>";
  oOut << "<fl c=\"3\">66.225</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">39.2761</fl>";
  oOut << "<fl c=\"1\">141.229</fl>";
  oOut << "<fl c=\"3\">61.1823</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"2\">";
  oOut << "<fl c=\"0\">34.1125</fl>";
  oOut << "<fl c=\"1\">161.029</fl>";
  oOut << "<fl c=\"4\">0.720184</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">47.8149</fl>";
  oOut << "<fl c=\"1\">42.8345</fl>";
  oOut << "<fl c=\"3\">94.0286</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"2\">";
  oOut << "<fl c=\"0\">47.1985</fl>";
  oOut << "<fl c=\"1\">67.0959</fl>";
  oOut << "<fl c=\"4\">8.04691</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">40.9302</fl>";
  oOut << "<fl c=\"1\">83.1543</fl>";
  oOut << "<fl c=\"3\">38.5379</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">44.0186</fl>";
  oOut << "<fl c=\"1\">91.9006</fl>";
  oOut << "<fl c=\"3\">35.7718</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">45.9412</fl>";
  oOut << "<fl c=\"1\">151.935</fl>";
  oOut << "<fl c=\"3\">56.9217</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">43.9819</fl>";
  oOut << "<fl c=\"1\">162.878</fl>";
  oOut << "<fl c=\"3\">88.3466</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">43.8049</fl>";
  oOut << "<fl c=\"1\">181.787</fl>";
  oOut << "<fl c=\"3\">80.6277</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">43.9331</fl>";
  oOut << "<fl c=\"1\">181.805</fl>";
  oOut << "<fl c=\"3\">69.0619</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">51.947</fl>";
  oOut << "<fl c=\"1\">62.3535</fl>";
  oOut << "<fl c=\"3\">61.5414</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">50.7263</fl>";
  oOut << "<fl c=\"1\">127.826</fl>";
  oOut << "<fl c=\"3\">83.804</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">52.4902</fl>";
  oOut << "<fl c=\"1\">132.8</fl>";
  oOut << "<fl c=\"3\">98.1351</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">54.7913</fl>";
  oOut << "<fl c=\"1\">128.998</fl>";
  oOut << "<fl c=\"3\">70.7745</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">51.2634</fl>";
  oOut << "<fl c=\"1\">158.514</fl>";
  oOut << "<fl c=\"3\">73.1763</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">56.2927</fl>";
  oOut << "<fl c=\"1\">11.0718</fl>";
  oOut << "<fl c=\"3\">74.1467</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">58.7585</fl>";
  oOut << "<fl c=\"1\">42.2607</fl>";
  oOut << "<fl c=\"3\">81.1838</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">56.5552</fl>";
  oOut << "<fl c=\"1\">92.5232</fl>";
  oOut << "<fl c=\"3\">99.3738</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">62.1704</fl>";
  oOut << "<fl c=\"1\">117.45</fl>";
  oOut << "<fl c=\"3\">33.3865</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">59.1797</fl>";
  oOut << "<fl c=\"1\">127.026</fl>";
  oOut << "<fl c=\"3\">72.8299</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">57.1716</fl>";
  oOut << "<fl c=\"1\">136.169</fl>";
  oOut << "<fl c=\"3\">25.0626</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">59.9854</fl>";
  oOut << "<fl c=\"1\">166.01</fl>";
  oOut << "<fl c=\"3\">84.8898</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">60.4797</fl>";
  oOut << "<fl c=\"1\">160.797</fl>";
  oOut << "<fl c=\"3\">58.4607</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">59.6924</fl>";
  oOut << "<fl c=\"1\">194</fl>";
  oOut << "<fl c=\"3\">33.9206</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">69.043</fl>";
  oOut << "<fl c=\"1\">4.73022</fl>";
  oOut << "<fl c=\"3\">53.4637</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">64.4714</fl>";
  oOut << "<fl c=\"1\">30.3589</fl>";
  oOut << "<fl c=\"3\">28.5464</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">65.5396</fl>";
  oOut << "<fl c=\"1\">79.9622</fl>";
  oOut << "<fl c=\"3\">41.7285</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">70.6421</fl>";
  oOut << "<fl c=\"1\">82.4768</fl>";
  oOut << "<fl c=\"3\">54.3875</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"2\">";
  oOut << "<fl c=\"0\">71.0205</fl>";
  oOut << "<fl c=\"1\">80.9814</fl>";
  oOut << "<fl c=\"4\">1.22824</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">70.9412</fl>";
  oOut << "<fl c=\"1\">151.074</fl>";
  oOut << "<fl c=\"3\">26.9037</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">70.8496</fl>";
  oOut << "<fl c=\"1\">173.535</fl>";
  oOut << "<fl c=\"3\">67.8082</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">69.6045</fl>";
  oOut << "<fl c=\"1\">173.669</fl>";
  oOut << "<fl c=\"3\">51.3788</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"2\">";
  oOut << "<fl c=\"0\">66.4734</fl>";
  oOut << "<fl c=\"1\">173.901</fl>";
  oOut << "<fl c=\"4\">8.48828</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">67.2607</fl>";
  oOut << "<fl c=\"1\">183.795</fl>";
  oOut << "<fl c=\"3\">18.551</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">75.7263</fl>";
  oOut << "<fl c=\"1\">5.23682</fl>";
  oOut << "<fl c=\"3\">92.7884</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">76.0925</fl>";
  oOut << "<fl c=\"1\">37.7258</fl>";
  oOut << "<fl c=\"3\">38.8348</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">75.8118</fl>";
  oOut << "<fl c=\"1\">50.47</fl>";
  oOut << "<fl c=\"3\">28.8422</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">74.6582</fl>";
  oOut << "<fl c=\"1\">82.4768</fl>";
  oOut << "<fl c=\"3\">88.3347</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">74.9634</fl>";
  oOut << "<fl c=\"1\">93.0603</fl>";
  oOut << "<fl c=\"3\">60.8459</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">76.6907</fl>";
  oOut << "<fl c=\"1\">89.7705</fl>";
  oOut << "<fl c=\"3\">40.3589</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">76.6663</fl>";
  oOut << "<fl c=\"1\">102.368</fl>";
  oOut << "<fl c=\"3\">81.9266</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">79.0955</fl>";
  oOut << "<fl c=\"1\">102.002</fl>";
  oOut << "<fl c=\"3\">41.6165</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">75.9766</fl>";
  oOut << "<fl c=\"1\">147.662</fl>";
  oOut << "<fl c=\"3\">70.4739</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">73.3398</fl>";
  oOut << "<fl c=\"1\">145.984</fl>";
  oOut << "<fl c=\"3\">29.3579</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">76.7822</fl>";
  oOut << "<fl c=\"1\">154.895</fl>";
  oOut << "<fl c=\"3\">14.4083</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">78.8635</fl>";
  oOut << "<fl c=\"1\">162.329</fl>";
  oOut << "<fl c=\"3\">59.6997</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">76.3367</fl>";
  oOut << "<fl c=\"1\">190.967</fl>";
  oOut << "<fl c=\"3\">94.9612</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">79.9683</fl>";
  oOut << "<fl c=\"1\">197.375</fl>";
  oOut << "<fl c=\"3\">71.0562</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"2\">";
  oOut << "<fl c=\"0\">81.7261</fl>";
  oOut << "<fl c=\"1\">48.0835</fl>";
  oOut << "<fl c=\"4\">6.99496</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">86.9934</fl>";
  oOut << "<fl c=\"1\">79.6387</fl>";
  oOut << "<fl c=\"3\">62.5281</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">80.0781</fl>";
  oOut << "<fl c=\"1\">104.449</fl>";
  oOut << "<fl c=\"3\">76.712</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">84.2224</fl>";
  oOut << "<fl c=\"1\">112.439</fl>";
  oOut << "<fl c=\"3\">10.0235</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"2\">";
  oOut << "<fl c=\"0\">84.613</fl>";
  oOut << "<fl c=\"1\">138.953</fl>";
  oOut << "<fl c=\"4\">0.82019</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">81.1157</fl>";
  oOut << "<fl c=\"1\">158.716</fl>";
  oOut << "<fl c=\"3\">44.0588</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">86.145</fl>";
  oOut << "<fl c=\"1\">172.357</fl>";
  oOut << "<fl c=\"3\">86.568</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">85.7483</fl>";
  oOut << "<fl c=\"1\">170.77</fl>";
  oOut << "<fl c=\"3\">67.4588</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">85.4614</fl>";
  oOut << "<fl c=\"1\">185.303</fl>";
  oOut << "<fl c=\"3\">58.9871</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">92.0837</fl>";
  oOut << "<fl c=\"1\">5.18799</fl>";
  oOut << "<fl c=\"3\">90.2252</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">90.4602</fl>";
  oOut << "<fl c=\"1\">47.4609</fl>";
  oOut << "<fl c=\"3\">10.5792</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">89.0808</fl>";
  oOut << "<fl c=\"1\">50.47</fl>";
  oOut << "<fl c=\"3\">63.0469</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">90.5518</fl>";
  oOut << "<fl c=\"1\">58.6426</fl>";
  oOut << "<fl c=\"3\">59.1797</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"2\">";
  oOut << "<fl c=\"0\">92.2119</fl>";
  oOut << "<fl c=\"1\">77.3071</fl>";
  oOut << "<fl c=\"4\">0.731079</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">92.8406</fl>";
  oOut << "<fl c=\"1\">91.0522</fl>";
  oOut << "<fl c=\"3\">39.9121</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">95.5383</fl>";
  oOut << "<fl c=\"1\">127.85</fl>";
  oOut << "<fl c=\"3\">74.6786</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">99.6216</fl>";
  oOut << "<fl c=\"1\">13.5559</fl>";
  oOut << "<fl c=\"3\">61.4172</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">101.471</fl>";
  oOut << "<fl c=\"1\">25.2258</fl>";
  oOut << "<fl c=\"3\">57.4838</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">98.4802</fl>";
  oOut << "<fl c=\"1\">35.0342</fl>";
  oOut << "<fl c=\"3\">13.6017</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">97.6257</fl>";
  oOut << "<fl c=\"1\">48.3459</fl>";
  oOut << "<fl c=\"3\">63.7216</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">97.937</fl>";
  oOut << "<fl c=\"1\">80.9265</fl>";
  oOut << "<fl c=\"3\">30.6873</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"2\">";
  oOut << "<fl c=\"0\">96.7957</fl>";
  oOut << "<fl c=\"1\">119.391</fl>";
  oOut << "<fl c=\"4\">5.87793</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"2\">";
  oOut << "<fl c=\"0\">98.2178</fl>";
  oOut << "<fl c=\"1\">112.848</fl>";
  oOut << "<fl c=\"4\">0.525116</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">98.9075</fl>";
  oOut << "<fl c=\"1\">125.256</fl>";
  oOut << "<fl c=\"3\">14.5364</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">101.636</fl>";
  oOut << "<fl c=\"1\">146.387</fl>";
  oOut << "<fl c=\"3\">84.155</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">103.308</fl>";
  oOut << "<fl c=\"1\">164.563</fl>";
  oOut << "<fl c=\"3\">29.1663</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">103.07</fl>";
  oOut << "<fl c=\"1\">197.333</fl>";
  oOut << "<fl c=\"3\">50.7736</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">106.873</fl>";
  oOut << "<fl c=\"1\">26.1108</fl>";
  oOut << "<fl c=\"3\">54.0695</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"2\">";
  oOut << "<fl c=\"0\">107.391</fl>";
  oOut << "<fl c=\"1\">39.1541</fl>";
  oOut << "<fl c=\"4\">0.782806</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"2\">";
  oOut << "<fl c=\"0\">110.699</fl>";
  oOut << "<fl c=\"1\">102.142</fl>";
  oOut << "<fl c=\"4\">9.6152</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">110.846</fl>";
  oOut << "<fl c=\"1\">104.651</fl>";
  oOut << "<fl c=\"3\">68.2712</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"2\">";
  oOut << "<fl c=\"0\">110.388</fl>";
  oOut << "<fl c=\"1\">114.319</fl>";
  oOut << "<fl c=\"4\">3.40848</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"2\">";
  oOut << "<fl c=\"0\">107.66</fl>";
  oOut << "<fl c=\"1\">129.095</fl>";
  oOut << "<fl c=\"4\">0.836304</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">107.568</fl>";
  oOut << "<fl c=\"1\">171.326</fl>";
  oOut << "<fl c=\"3\">38.2971</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">117.029</fl>";
  oOut << "<fl c=\"1\">38.4766</fl>";
  oOut << "<fl c=\"3\">86.4185</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">113.843</fl>";
  oOut << "<fl c=\"1\">88.9282</fl>";
  oOut << "<fl c=\"3\">67.5839</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">114.624</fl>";
  oOut << "<fl c=\"1\">125.14</fl>";
  oOut << "<fl c=\"3\">78.2462</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"2\">";
  oOut << "<fl c=\"0\">116.223</fl>";
  oOut << "<fl c=\"1\">120.691</fl>";
  oOut << "<fl c=\"4\">0.623199</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">119.47</fl>";
  oOut << "<fl c=\"1\">151.465</fl>";
  oOut << "<fl c=\"3\">49.7733</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">116.656</fl>";
  oOut << "<fl c=\"1\">157.947</fl>";
  oOut << "<fl c=\"3\">12.9224</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">122.552</fl>";
  oOut << "<fl c=\"1\">16.3757</fl>";
  oOut << "<fl c=\"3\">10.4282</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">125.146</fl>";
  oOut << "<fl c=\"1\">59.4299</fl>";
  oOut << "<fl c=\"3\">71.6089</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">123.541</fl>";
  oOut << "<fl c=\"1\">86.4319</fl>";
  oOut << "<fl c=\"3\">76.6467</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">121.405</fl>";
  oOut << "<fl c=\"1\">127.454</fl>";
  oOut << "<fl c=\"3\">77.5854</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"2\">";
  oOut << "<fl c=\"0\">125.818</fl>";
  oOut << "<fl c=\"1\">143.011</fl>";
  oOut << "<fl c=\"4\">2.72595</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">123.901</fl>";
  oOut << "<fl c=\"1\">179.602</fl>";
  oOut << "<fl c=\"3\">89.8761</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">120.129</fl>";
  oOut << "<fl c=\"1\">189.117</fl>";
  oOut << "<fl c=\"3\">51.9055</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">130.17</fl>";
  oOut << "<fl c=\"1\">25.415</fl>";
  oOut << "<fl c=\"3\">16.1133</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">132.928</fl>";
  oOut << "<fl c=\"1\">54.0588</fl>";
  oOut << "<fl c=\"3\">82.2635</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">129.303</fl>";
  oOut << "<fl c=\"1\">69.8181</fl>";
  oOut << "<fl c=\"3\">39.0826</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">135.809</fl>";
  oOut << "<fl c=\"1\">89.2761</fl>";
  oOut << "<fl c=\"3\">88.5767</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">135.675</fl>";
  oOut << "<fl c=\"1\">99.6155</fl>";
  oOut << "<fl c=\"3\">86.1768</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">134.54</fl>";
  oOut << "<fl c=\"1\">97.0642</fl>";
  oOut << "<fl c=\"3\">68.4769</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">132.855</fl>";
  oOut << "<fl c=\"1\">111.243</fl>";
  oOut << "<fl c=\"3\">43.0722</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">133.881</fl>";
  oOut << "<fl c=\"1\">114.124</fl>";
  oOut << "<fl c=\"3\">39.8019</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">129.822</fl>";
  oOut << "<fl c=\"1\">114.63</fl>";
  oOut << "<fl c=\"3\">34.1074</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"2\">";
  oOut << "<fl c=\"0\">132.33</fl>";
  oOut << "<fl c=\"1\">119.94</fl>";
  oOut << "<fl c=\"4\">0.395264</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">128.925</fl>";
  oOut << "<fl c=\"1\">143.256</fl>";
  oOut << "<fl c=\"3\">49.7015</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">129.694</fl>";
  oOut << "<fl c=\"1\">141.864</fl>";
  oOut << "<fl c=\"3\">13.4555</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">132.275</fl>";
  oOut << "<fl c=\"1\">144.196</fl>";
  oOut << "<fl c=\"3\">13.4448</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">130.133</fl>";
  oOut << "<fl c=\"1\">181.287</fl>";
  oOut << "<fl c=\"3\">41.3898</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">134.943</fl>";
  oOut << "<fl c=\"1\">185.016</fl>";
  oOut << "<fl c=\"3\">22.7289</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">138.367</fl>";
  oOut << "<fl c=\"1\">20.7031</fl>";
  oOut << "<fl c=\"3\">41.282</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">139.703</fl>";
  oOut << "<fl c=\"1\">44.696</fl>";
  oOut << "<fl c=\"3\">14.3527</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">137.933</fl>";
  oOut << "<fl c=\"1\">51.4038</fl>";
  oOut << "<fl c=\"3\">99.2041</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">143.604</fl>";
  oOut << "<fl c=\"1\">57.1594</fl>";
  oOut << "<fl c=\"3\">17.0462</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">136.267</fl>";
  oOut << "<fl c=\"1\">67.7246</fl>";
  oOut << "<fl c=\"3\">29.0283</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">136.157</fl>";
  oOut << "<fl c=\"1\">80.6274</fl>";
  oOut << "<fl c=\"3\">59.1907</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">138.959</fl>";
  oOut << "<fl c=\"1\">127.112</fl>";
  oOut << "<fl c=\"3\">40.95</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">141.919</fl>";
  oOut << "<fl c=\"1\">133.331</fl>";
  oOut << "<fl c=\"3\">66.2845</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"2\">";
  oOut << "<fl c=\"0\">137.103</fl>";
  oOut << "<fl c=\"1\">152.875</fl>";
  oOut << "<fl c=\"4\">0.18454</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">143.164</fl>";
  oOut << "<fl c=\"1\">196.24</fl>";
  oOut << "<fl c=\"3\">52.4643</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"2\">";
  oOut << "<fl c=\"0\">144</fl>";
  oOut << "<fl c=\"1\">22.7905</fl>";
  oOut << "<fl c=\"4\">0.450836</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"2\">";
  oOut << "<fl c=\"0\">147.186</fl>";
  oOut << "<fl c=\"1\">92.2607</fl>";
  oOut << "<fl c=\"4\">1.85172</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">147.51</fl>";
  oOut << "<fl c=\"1\">101.953</fl>";
  oOut << "<fl c=\"3\">10.1794</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">147.662</fl>";
  oOut << "<fl c=\"1\">122.833</fl>";
  oOut << "<fl c=\"3\">21.5207</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">148.694</fl>";
  oOut << "<fl c=\"1\">156.207</fl>";
  oOut << "<fl c=\"3\">99.9454</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">146.49</fl>";
  oOut << "<fl c=\"1\">172.516</fl>";
  oOut << "<fl c=\"3\">78.6682</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"2\">";
  oOut << "<fl c=\"0\">151.624</fl>";
  oOut << "<fl c=\"1\">177.869</fl>";
  oOut << "<fl c=\"4\">7.75879</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">153.827</fl>";
  oOut << "<fl c=\"1\">10.4553</fl>";
  oOut << "<fl c=\"3\">96.9293</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"2\">";
  oOut << "<fl c=\"0\">154.218</fl>";
  oOut << "<fl c=\"1\">50.7324</fl>";
  oOut << "<fl c=\"4\">4.41263</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">156.47</fl>";
  oOut << "<fl c=\"1\">91.6809</fl>";
  oOut << "<fl c=\"3\">78.1659</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">157.904</fl>";
  oOut << "<fl c=\"1\">103.687</fl>";
  oOut << "<fl c=\"3\">67.2159</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">157.8</fl>";
  oOut << "<fl c=\"1\">109.943</fl>";
  oOut << "<fl c=\"3\">47.3859</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">156.384</fl>";
  oOut << "<fl c=\"1\">174.127</fl>";
  oOut << "<fl c=\"3\">32.7524</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">156.329</fl>";
  oOut << "<fl c=\"1\">182.007</fl>";
  oOut << "<fl c=\"3\">47.0844</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">162.897</fl>";
  oOut << "<fl c=\"1\">56.0791</fl>";
  oOut << "<fl c=\"3\">91.8817</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"2\">";
  oOut << "<fl c=\"0\">162.177</fl>";
  oOut << "<fl c=\"1\">90.2039</fl>";
  oOut << "<fl c=\"4\">0.0767822</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">161.627</fl>";
  oOut << "<fl c=\"1\">113.623</fl>";
  oOut << "<fl c=\"3\">46.2454</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">162.292</fl>";
  oOut << "<fl c=\"1\">155.798</fl>";
  oOut << "<fl c=\"3\">99.3744</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">163.885</fl>";
  oOut << "<fl c=\"1\">194.122</fl>";
  oOut << "<fl c=\"3\">60.2737</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">174.902</fl>";
  oOut << "<fl c=\"1\">4.00391</fl>";
  oOut << "<fl c=\"3\">38.4561</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"2\">";
  oOut << "<fl c=\"0\">173.743</fl>";
  oOut << "<fl c=\"1\">52.8809</fl>";
  oOut << "<fl c=\"4\">0.655518</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">174.75</fl>";
  oOut << "<fl c=\"1\">94.4031</fl>";
  oOut << "<fl c=\"3\">91.2775</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">169.336</fl>";
  oOut << "<fl c=\"1\">101.825</fl>";
  oOut << "<fl c=\"3\">44.0875</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">171.527</fl>";
  oOut << "<fl c=\"1\">182.184</fl>";
  oOut << "<fl c=\"3\">37.7225</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">179.663</fl>";
  oOut << "<fl c=\"1\">14.4348</fl>";
  oOut << "<fl c=\"3\">16.9019</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">177.155</fl>";
  oOut << "<fl c=\"1\">29.1626</fl>";
  oOut << "<fl c=\"3\">26.6144</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">181.006</fl>";
  oOut << "<fl c=\"1\">53.0579</fl>";
  oOut << "<fl c=\"3\">21.2219</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">182.709</fl>";
  oOut << "<fl c=\"1\">83.905</fl>";
  oOut << "<fl c=\"3\">25.8966</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">178.754</fl>";
  oOut << "<fl c=\"1\">131.055</fl>";
  oOut << "<fl c=\"3\">23.8516</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">183.337</fl>";
  oOut << "<fl c=\"1\">143.231</fl>";
  oOut << "<fl c=\"3\">93.2443</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"2\">";
  oOut << "<fl c=\"0\">177.246</fl>";
  oOut << "<fl c=\"1\">175.11</fl>";
  oOut << "<fl c=\"4\">4.15665</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">191.26</fl>";
  oOut << "<fl c=\"1\">10.7422</fl>";
  oOut << "<fl c=\"3\">41.1438</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">185.193</fl>";
  oOut << "<fl c=\"1\">17.6941</fl>";
  oOut << "<fl c=\"3\">80.1282</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"2\">";
  oOut << "<fl c=\"0\">189.734</fl>";
  oOut << "<fl c=\"1\">42.5415</fl>";
  oOut << "<fl c=\"4\">9.7204</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"2\">";
  oOut << "<fl c=\"0\">191.901</fl>";
  oOut << "<fl c=\"1\">43.8843</fl>";
  oOut << "<fl c=\"4\">0.172394</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">189.886</fl>";
  oOut << "<fl c=\"1\">53.9001</fl>";
  oOut << "<fl c=\"3\">23.7564</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">184.186</fl>";
  oOut << "<fl c=\"1\">48.9075</fl>";
  oOut << "<fl c=\"3\">20.2258</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"2\">";
  oOut << "<fl c=\"0\">189.978</fl>";
  oOut << "<fl c=\"1\">54.9561</fl>";
  oOut << "<fl c=\"4\">0.299683</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">184.186</fl>";
  oOut << "<fl c=\"1\">58.6975</fl>";
  oOut << "<fl c=\"3\">79.5746</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">187.83</fl>";
  oOut << "<fl c=\"1\">128.894</fl>";
  oOut << "<fl c=\"3\">16.4716</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">190.961</fl>";
  oOut << "<fl c=\"1\">148.383</fl>";
  oOut << "<fl c=\"3\">80.6717</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"2\">";
  oOut << "<fl c=\"0\">190.515</fl>";
  oOut << "<fl c=\"1\">167.902</fl>";
  oOut << "<fl c=\"4\">0.573212</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">185.944</fl>";
  oOut << "<fl c=\"1\">168.738</fl>";
  oOut << "<fl c=\"3\">63.5855</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">188.58</fl>";
  oOut << "<fl c=\"1\">182.727</fl>";
  oOut << "<fl c=\"3\">94.0863</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">185.211</fl>";
  oOut << "<fl c=\"1\">177.795</fl>";
  oOut << "<fl c=\"3\">69.1345</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">190.71</fl>";
  oOut << "<fl c=\"1\">198.267</fl>";
  oOut << "<fl c=\"3\">13.8528</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">196.722</fl>";
  oOut << "<fl c=\"1\">2.92969</fl>";
  oOut << "<fl c=\"3\">16.2329</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">198.12</fl>";
  oOut << "<fl c=\"1\">12.9578</fl>";
  oOut << "<fl c=\"3\">37.9092</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">197.687</fl>";
  oOut << "<fl c=\"1\">36.8408</fl>";
  oOut << "<fl c=\"3\">40.531</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">198.737</fl>";
  oOut << "<fl c=\"1\">50.6836</fl>";
  oOut << "<fl c=\"3\">94.9945</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">195.917</fl>";
  oOut << "<fl c=\"1\">49.1394</fl>";
  oOut << "<fl c=\"3\">28.9987</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">197.339</fl>";
  oOut << "<fl c=\"1\">91.4429</fl>";
  oOut << "<fl c=\"3\">12.8403</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">197.29</fl>";
  oOut << "<fl c=\"1\">105.829</fl>";
  oOut << "<fl c=\"3\">51.5683</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">194.989</fl>";
  oOut << "<fl c=\"1\">173.077</fl>";
  oOut << "<fl c=\"3\">99.1153</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">198.895</fl>";
  oOut << "<fl c=\"1\">174.249</fl>";
  oOut << "<fl c=\"3\">87.7603</fl>";
  oOut << "</tree>";
  oOut << "<tree sp=\"0\" tp=\"3\">";
  oOut << "<fl c=\"0\">194.885</fl>";
  oOut << "<fl c=\"1\">196.576</fl>";
  oOut << "<fl c=\"3\">24.5227</fl>";
  oOut << "</tree>";
  oOut << "</tr_treemap>";

}

/////////////////////////////////////////////////////////////////////////////
// WriteHarvestRun9TreeMap()
/////////////////////////////////////////////////////////////////////////////
const char* WriteHarvestRun9TreeMap()
{
  using namespace std;
  const char *cFileString = "TestTreeMap.txt";

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "X\tY\tSpecies\tType\tDbh\tHeight\tvigorous\tsawlog\tYearsInfested\tGrowth\ttreeclass\n";
  oOut << "27.7771\t165.308\tWestern_Redcedar\tAdult\t99.9786\t29.9437\t1\t0\t5\t8.7\t2\n";
  oOut << "110.889\t110.76\tBlack_Cottonwood\tAdult\t99.9619\t29.6812\t0\t0\t4\t5\t4\n";
  oOut << "148.694\t156.207\tWestern_Hemlock\tAdult\t99.9454\t29.9472\t1\t1\t5\t0.7\t1\n";
  oOut << "13.4583\t51.9043\tWestern_Redcedar\tAdult\t99.7977\t29.943\t0\t0\t2\t7.5\t4\n";
  oOut << "120.264\t151.111\tTrembling_Aspen\tAdult\t99.7946\t28.9709\t1\t1\t2\t9.2\t1\n";
  oOut << "118.561\t174.622\tLodgepole_Pine\tAdult\t99.7858\t29.8928\t0\t0\t3\t3.5\t4\n";
  oOut << "189.648\t194.086\tWestern_Redcedar\tAdult\t99.7717\t29.943\t0\t1\t1\t11.9\t3\n";
  oOut << "40.5151\t1.25732\tLodgepole_Pine\tAdult\t99.7537\t29.8926\t1\t1\t4\t9.9\t1\n";
  oOut << "97.8333\t126.642\tPaper_Birch\tAdult\t99.7113\t29.5651\t0\t1\t4\t10.3\t3\n";
  oOut << "139.819\t14.624\tBlack_Cottonwood\tAdult\t99.7043\t29.6775\t0\t0\t1\t2.5\t4\n";
  oOut << "56.8665\t95.1294\tBlack_Cottonwood\tAdult\t99.6863\t29.6772\t1\t1\t1\t3.2\t1\n";
  oOut << "87.5305\t47.4609\tPaper_Birch\tAdult\t99.6683\t29.5643\t1\t0\t4\t3.6\t2\n";
  oOut << "156.14\t99.6399\tHybrid_Spruce\tAdult\t99.6304\t27.4634\t1\t0\t1\t5.4\t2\n";
  oOut << "74.5422\t169.733\tSubalpine_Fir\tAdult\t99.5303\t29.1492\t0\t0\t0\t5.7\t4\n";
  oOut << "116.29\t111.719\tWestern_Redcedar\tAdult\t99.509\t29.942\t0\t1\t1\t23.9\t3\n";
  oOut << "55.8228\t151.874\tWestern_Redcedar\tAdult\t99.4522\t29.9418\t1\t1\t4\t7.7\t1\n";
  oOut << "32.373\t102.222\tTrembling_Aspen\tAdult\t99.4312\t28.9584\t0\t0\t5\t1.5\t4\n";
  oOut << "162.292\t155.798\tWestern_Hemlock\tAdult\t99.3744\t29.9453\t1\t1\t4\t2\t1\n";
  oOut << "56.5552\t92.5232\tWestern_Hemlock\tAdult\t99.3738\t29.9453\t1\t1\t2\t0.6\t1\n";
  oOut << "103.717\t79.126\tLodgepole_Pine\tAdult\t99.3433\t29.8901\t0\t1\t3\t2.2\t3\n";
  oOut << "137.933\t51.4038\tWestern_Hemlock\tAdult\t99.2041\t29.9447\t0\t0\t0\t6.5\t4\n";
  oOut << "147.949\t70.7886\tHybrid_Spruce\tAdult\t99.1867\t27.4359\t1\t1\t3\t7\t1\n";
  oOut << "182.666\t31.0364\tTrembling_Aspen\tAdult\t99.1422\t28.9483\t0\t1\t5\t7.1\t3\n";
  oOut << "194.989\t173.077\tWestern_Hemlock\tAdult\t99.1153\t29.9444\t0\t0\t1\t4.5\t4\n";
  oOut << "108.575\t172.308\tPaper_Birch\tAdult\t99.0091\t29.5521\t0\t1\t4\t6.8\t3\n";
  oOut << "51.4587\t190.485\tPaper_Birch\tAdult\t99.0073\t29.5521\t1\t1\t2\t10.1\t1\n";
  oOut << "61.1328\t55.5969\tSubalpine_Fir\tAdult\t98.9746\t29.1323\t0\t1\t0\t7.2\t3\n";
  oOut << "20.3247\t62.5305\tLodgepole_Pine\tAdult\t98.9093\t29.8874\t1\t1\t4\t4.8\t1\n";
  oOut << "67.3279\t71.0266\tPaper_Birch\tAdult\t98.9053\t29.5502\t1\t0\t2\t2.2\t2\n";
  oOut << "101.007\t120.526\tPaper_Birch\tAdult\t98.7943\t29.5481\t0\t1\t2\t3.2\t3\n";
  oOut << "72.3999\t198.157\tSubalpine_Fir\tAdult\t98.6835\t29.1234\t0\t0\t0\t1.6\t4\n";
  oOut << "18.6096\t26.3794\tAmabilis_Fir\tAdult\t98.6591\t29.9428\t0\t1\t0\t3.3\t3\n";
  oOut << "198.602\t116.766\tWestern_Redcedar\tAdult\t98.623\t29.9387\t0\t0\t0\t0.9\t4\n";
  oOut << "169.226\t99.9023\tBlack_Cottonwood\tAdult\t98.5852\t29.6608\t1\t0\t0\t7.2\t2\n";
  oOut << "62.207\t123.401\tHybrid_Spruce\tAdult\t98.5498\t27.3958\t1\t0\t0\t3.7\t2\n";
  oOut << "112.366\t47.6074\tBlack_Cottonwood\tAdult\t98.544\t29.6602\t0\t1\t3\t2.8\t3\n";
  oOut << "11.438\t125.458\tLodgepole_Pine\tAdult\t98.4561\t29.8845\t1\t0\t5\t4.2\t2\n";
  oOut << "134.583\t189.154\tLodgepole_Pine\tAdult\t98.3527\t29.8838\t0\t0\t4\t10.1\t4\n";
  oOut << "52.4902\t132.8\tWestern_Hemlock\tAdult\t98.1351\t29.9408\t1\t1\t1\t1.4\t1\n";
  oOut << "150.787\t71.405\tPaper_Birch\tAdult\t98.0505\t29.5337\t1\t0\t5\t3.5\t2\n";
  oOut << "65.6555\t58.7036\tLodgepole_Pine\tAdult\t98.0389\t29.8818\t1\t0\t5\t7.5\t2\n";
  oOut << "35.0037\t137.585\tPaper_Birch\tAdult\t97.9401\t29.5316\t1\t0\t5\t5.5\t2\n";
  oOut << "52.4414\t84.2346\tTrembling_Aspen\tAdult\t97.9132\t28.9043\t1\t1\t0\t6\t1\n";
  oOut << "187.897\t129.346\tPaper_Birch\tAdult\t97.7689\t29.5282\t0\t1\t0\t8.3\t3\n";
  oOut << "135.48\t100.342\tTrembling_Aspen\tAdult\t97.7536\t28.8985\t0\t1\t4\t1.9\t3\n";
  oOut << "123.578\t48.6084\tBlack_Cottonwood\tAdult\t97.6428\t29.6461\t0\t0\t2\t4.7\t4\n";
  oOut << "34.4666\t48.0591\tWestern_Hemlock\tAdult\t97.6416\t29.939\t0\t0\t4\t10.7\t4\n";
  oOut << "29.9377\t188.239\tAmabilis_Fir\tAdult\t97.6373\t29.9389\t0\t0\t0\t11.2\t4\n";
  oOut << "138.745\t82.5073\tAmabilis_Fir\tAdult\t97.3776\t29.9379\t0\t1\t0\t1.1\t3\n";
  oOut << "103.162\t195.148\tLodgepole_Pine\tAdult\t97.3697\t29.8772\t0\t1\t4\t12\t3\n";
  oOut << "22.8149\t88.0066\tAmabilis_Fir\tAdult\t97.3383\t29.9378\t0\t0\t0\t10.1\t4\n";
  oOut << "30.0232\t76.8066\tWestern_Redcedar\tAdult\t97.3242\t29.9336\t0\t0\t5\t6.8\t4\n";
  oOut << "144\t40.5273\tSubalpine_Fir\tAdult\t97.226\t29.077\t0\t1\t0\t10.7\t3\n";
  oOut << "112.128\t18.8904\tAmabilis_Fir\tAdult\t97.0715\t29.9367\t0\t1\t0\t8.7\t3\n";
  oOut << "145.001\t170.355\tWestern_Redcedar\tAdult\t97.0227\t29.9323\t0\t1\t1\t10\t3\n";
  oOut << "125.885\t69.3298\tTrembling_Aspen\tAdult\t96.983\t28.8698\t0\t0\t2\t6.6\t4\n";
  oOut << "135.468\t157.434\tBlack_Cottonwood\tAdult\t96.9788\t29.6354\t0\t0\t3\t0.1\t4\n";
  oOut << "137.292\t127.087\tHybrid_Spruce\tAdult\t96.9315\t27.2912\t0\t0\t1\t4\t4\n";
  oOut << "153.827\t10.4553\tWestern_Hemlock\tAdult\t96.9293\t29.9362\t1\t1\t2\t0.9\t1\n";
  oOut << "131.708\t131.744\tLodgepole_Pine\tAdult\t96.8665\t29.8737\t0\t0\t0\t12\t4\n";
  oOut << "129.767\t188.483\tAmabilis_Fir\tAdult\t96.8378\t29.9358\t1\t0\t0\t11.1\t2\n";
  oOut << "123.291\t22.9675\tSubalpine_Fir\tAdult\t96.7673\t29.062\t0\t0\t0\t6.9\t4\n";
  oOut << "94.3542\t1.74561\tBlack_Cottonwood\tAdult\t96.7407\t29.6315\t1\t1\t5\t1.8\t1\n";
  oOut << "85.7422\t161.554\tBlack_Cottonwood\tAdult\t96.7279\t29.6312\t1\t0\t3\t3.5\t2\n";
  oOut << "188.361\t39.8315\tHybrid_Spruce\tAdult\t96.7001\t27.276\t0\t1\t5\t5.7\t3\n";
  oOut << "119.891\t173.175\tTrembling_Aspen\tAdult\t96.6446\t28.857\t0\t0\t0\t1\t4\n";
  oOut << "59.8633\t30.4321\tBlack_Cottonwood\tAdult\t96.6269\t29.6296\t1\t1\t0\t7.4\t1\n";
  oOut << "158.563\t182.782\tWestern_Redcedar\tAdult\t96.626\t29.9306\t1\t1\t3\t20.4\t1\n";
  oOut << "35.8521\t56.4209\tPaper_Birch\tAdult\t96.5445\t29.5033\t1\t1\t0\t6.2\t1\n";
  oOut << "166.547\t117.065\tBlack_Cottonwood\tAdult\t96.4426\t29.6265\t1\t0\t2\t4.6\t2\n";
  oOut << "4.05273\t197.821\tWestern_Hemlock\tAdult\t96.4136\t29.9341\t0\t0\t2\t4.8\t4\n";
  oOut << "6.38428\t65.4175\tSubalpine_Fir\tAdult\t96.3052\t29.0465\t0\t0\t0\t11.3\t4\n";
  oOut << "6.38428\t50.6042\tSubalpine_Fir\tAdult\t96.2695\t29.0453\t0\t0\t0\t11.7\t4\n";
  oOut << "24.2249\t180.219\tBlack_Cottonwood\tAdult\t96.264\t29.6235\t0\t1\t2\t3.1\t3\n";
  oOut << "150.958\t80.1636\tHybrid_Spruce\tAdult\t96.2463\t27.2457\t1\t1\t0\t8.7\t1\n";
  oOut << "2.03247\t196.851\tSubalpine_Fir\tAdult\t96.2433\t29.0444\t0\t0\t0\t1\t4\n";
  oOut << "148.651\t126.868\tAmabilis_Fir\tAdult\t96.1505\t29.933\t0\t0\t0\t11.4\t4\n";
  oOut << "12.3108\t102.35\tWestern_Redcedar\tAdult\t96.1136\t29.9283\t1\t0\t3\t9.4\t2\n";
  oOut << "152.24\t153.9\tBlack_Cottonwood\tAdult\t96.1096\t29.6208\t1\t1\t4\t6.8\t1\n";
  oOut << "54.8645\t114.319\tSubalpine_Fir\tAdult\t96.1075\t29.0398\t0\t1\t0\t9.3\t3\n";
  oOut << "34.0149\t27.0752\tWestern_Hemlock\tAdult\t95.9747\t29.9322\t0\t1\t5\t8.4\t3\n";
  oOut << "97.1191\t138.763\tAmabilis_Fir\tAdult\t95.9668\t29.9322\t0\t0\t0\t0.8\t4\n";
  oOut << "84.1309\t90.4968\tHybrid_Spruce\tAdult\t95.8945\t27.222\t1\t0\t5\t7\t2\n";
  oOut << "77.6489\t114.331\tPaper_Birch\tAdult\t95.8426\t29.4884\t1\t0\t1\t6.7\t2\n";
  oOut << "19.5801\t106.049\tHybrid_Spruce\tAdult\t95.8258\t27.2174\t0\t0\t3\t15\t4\n";
  oOut << "88.2751\t176.111\tPaper_Birch\tAdult\t95.7474\t29.4864\t1\t0\t4\t9.2\t2\n";
  oOut << "89.032\t169.348\tAmabilis_Fir\tAdult\t95.7108\t29.9311\t0\t0\t0\t4.2\t4\n";
  oOut << "81.543\t50.0549\tPaper_Birch\tAdult\t95.5505\t29.4821\t1\t0\t5\t5.9\t2\n";
  oOut << "11.7126\t146.68\tTrembling_Aspen\tAdult\t95.4285\t28.8097\t0\t0\t2\t2.3\t4\n";
  oOut << "55.9998\t99.9207\tHybrid_Spruce\tAdult\t95.3912\t27.1878\t1\t1\t3\t7.9\t1\n";
  oOut << "19.8853\t77.2583\tLodgepole_Pine\tAdult\t95.2591\t29.8618\t0\t0\t0\t10.2\t4\n";
  oOut << "52.6001\t66.571\tPaper_Birch\tAdult\t95.2139\t29.4747\t1\t1\t2\t5\t1\n";
  oOut << "2.85645\t84.259\tSubalpine_Fir\tAdult\t95.1984\t29.0085\t0\t0\t0\t1.9\t4\n";
  oOut << "47.998\t93.4021\tWestern_Redcedar\tAdult\t95.1425\t29.9239\t1\t1\t5\t7.2\t1\n";
  oOut << "78.0334\t19.0735\tPaper_Birch\tAdult\t95.1352\t29.473\t1\t0\t3\t9.5\t2\n";
  oOut << "63.7329\t145.361\tAmabilis_Fir\tAdult\t95.1208\t29.9285\t0\t0\t0\t10.5\t4\n";
  oOut << "52.356\t58.5144\tTrembling_Aspen\tAdult\t95.1074\t28.7969\t1\t1\t0\t8.6\t1\n";
  oOut << "129.962\t110.181\tWestern_Redcedar\tAdult\t95.0616\t29.9235\t0\t0\t3\t24.6\t4\n";
  oOut << "198.737\t50.6836\tWestern_Hemlock\tAdult\t94.9945\t29.9279\t0\t1\t3\t9.6\t3\n";
  oOut << "72.467\t28.1982\tTrembling_Aspen\tAdult\t94.9786\t28.7917\t1\t0\t3\t10.9\t2\n";
  oOut << "76.3367\t190.967\tWestern_Hemlock\tAdult\t94.9612\t29.9277\t0\t0\t2\t0.8\t4\n";
  oOut << "45.343\t68.3472\tHybrid_Spruce\tAdult\t94.8392\t27.1498\t1\t1\t2\t2.2\t1\n";
  oOut << "56.8359\t42.0837\tWestern_Redcedar\tAdult\t94.7501\t29.922\t1\t1\t1\t9.2\t1\n";
  oOut << "184.998\t180.701\tHybrid_Spruce\tAdult\t94.5517\t27.1298\t0\t1\t4\t2.3\t3\n";
  oOut << "7.03125\t82.1716\tWestern_Redcedar\tAdult\t94.4907\t29.9207\t1\t0\t4\t5.6\t2\n";
  oOut << "166.736\t90.509\tSubalpine_Fir\tAdult\t94.4617\t28.9823\t0\t0\t0\t2.4\t4\n";
  oOut << "194.598\t140.778\tSubalpine_Fir\tAdult\t94.4516\t28.982\t0\t1\t0\t2.7\t3\n";
  oOut << "178.192\t8.5022\tLodgepole_Pine\tAdult\t94.3698\t29.8548\t0\t1\t2\t2.9\t3\n";
  oOut << "87.7441\t36.7249\tTrembling_Aspen\tAdult\t94.2191\t28.7607\t1\t0\t3\t9.3\t2\n";
  oOut << "104.382\t122.729\tLodgepole_Pine\tAdult\t94.2108\t29.8535\t0\t1\t5\t9.5\t3\n";
  oOut << "27.9297\t111.902\tTrembling_Aspen\tAdult\t94.1898\t28.7595\t1\t0\t0\t9.5\t2\n";
  oOut << "188.58\t182.727\tWestern_Hemlock\tAdult\t94.0863\t29.9236\t0\t0\t3\t5.3\t4\n";
  oOut << "110.028\t45.0562\tLodgepole_Pine\tAdult\t94.0613\t29.8523\t0\t1\t2\t10.8\t3\n";
  oOut << "47.8149\t42.8345\tWestern_Hemlock\tAdult\t94.0286\t29.9234\t1\t1\t2\t9.7\t1\n";
  oOut << "195.99\t177.252\tBlack_Cottonwood\tAdult\t93.9792\t29.5827\t0\t0\t1\t5.8\t4\n";
  oOut << "139.502\t23.2483\tSubalpine_Fir\tAdult\t93.9572\t28.964\t0\t0\t0\t4.3\t4\n";
  oOut << "73.0591\t73.4619\tAmabilis_Fir\tAdult\t93.7881\t29.9222\t0\t0\t0\t4.1\t4\n";
  oOut << "33.7524\t49.9756\tHybrid_Spruce\tAdult\t93.7857\t27.0758\t1\t0\t1\t1\t2\n";
  oOut << "118.787\t43.1885\tBlack_Cottonwood\tAdult\t93.6996\t29.5774\t0\t0\t5\t10.7\t4\n";
  oOut << "113.257\t199.048\tAmabilis_Fir\tAdult\t93.6371\t29.9214\t0\t1\t0\t0.1\t3\n";
  oOut << "21.5393\t95.8557\tAmabilis_Fir\tAdult\t93.6292\t29.9214\t0\t1\t0\t4.3\t3\n";
  oOut << "110.51\t14.1785\tLodgepole_Pine\tAdult\t93.4778\t29.8473\t0\t1\t2\t5.9\t3\n";
  oOut << "169.94\t123.12\tLodgepole_Pine\tAdult\t93.4375\t29.847\t1\t1\t5\t5.5\t1\n";
  oOut << "37.8418\t48.4497\tWestern_Hemlock\tAdult\t93.4204\t29.9204\t1\t1\t3\t9.2\t1\n";
  oOut << "100.494\t189.032\tLodgepole_Pine\tAdult\t93.3023\t29.8458\t1\t1\t0\t8.6\t1\n";
  oOut << "183.337\t143.231\tWestern_Hemlock\tAdult\t93.2443\t29.9195\t0\t0\t4\t2.3\t4\n";
  oOut << "178.149\t90.387\tTrembling_Aspen\tAdult\t93.0936\t28.7134\t0\t0\t5\t7.3\t4\n";
  oOut << "55.2368\t144.653\tWestern_Redcedar\tAdult\t93.0603\t29.9133\t1\t1\t4\t10\t1\n";
  oOut << "125.69\t69.9341\tLodgepole_Pine\tAdult\t93.0127\t29.8433\t0\t0\t3\t4.2\t4\n";
  oOut << "148.267\t182.318\tAmabilis_Fir\tAdult\t92.9678\t29.9181\t1\t0\t0\t4.7\t2\n";
  oOut << "70.4346\t49.1577\tTrembling_Aspen\tAdult\t92.9312\t28.7064\t1\t0\t1\t10\t2\n";
  oOut << "0.396729\t176.636\tPaper_Birch\tAdult\t92.9282\t29.4218\t0\t1\t1\t7.6\t3\n";
  oOut << "9.48486\t87.2803\tWestern_Redcedar\tAdult\t92.8543\t29.9122\t1\t0\t4\t8.3\t2\n";
  oOut << "59.6191\t31.8787\tHybrid_Spruce\tAdult\t92.8043\t27.0051\t1\t1\t2\t2.1\t1\n";
  oOut << "74.0723\t1.06201\tAmabilis_Fir\tAdult\t92.7985\t29.9172\t0\t0\t0\t4.1\t4\n";
  oOut << "123.407\t152.02\tPaper_Birch\tAdult\t92.7948\t29.4185\t0\t0\t1\t2.3\t4\n";
  oOut << "75.7263\t5.23682\tWestern_Hemlock\tAdult\t92.7884\t29.9171\t1\t0\t0\t2.5\t2\n";
  oOut << "61.0901\t136.792\tAmabilis_Fir\tAdult\t92.6511\t29.9164\t0\t1\t0\t10.4\t3\n";
  oOut << "8.77686\t3.38745\tPaper_Birch\tAdult\t92.3648\t29.408\t0\t1\t3\t4.9\t3\n";
  oOut << "49.1455\t97.522\tHybrid_Spruce\tAdult\t92.3273\t26.9701\t0\t0\t3\t9.8\t4\n";
  oOut << "155.176\t91.1621\tSubalpine_Fir\tAdult\t92.2083\t28.898\t0\t1\t0\t6.7\t3\n";
  oOut << "93.8354\t142.859\tWestern_Redcedar\tAdult\t92.1274\t29.9081\t0\t1\t5\t23.6\t3\n";
  oOut << "0.738525\t185.51\tTrembling_Aspen\tAdult\t92.1225\t28.671\t0\t0\t5\t11.8\t4\n";
  oOut << "184.625\t2.81372\tSubalpine_Fir\tAdult\t92.1042\t28.8939\t0\t0\t0\t10.3\t4\n";
  oOut << "106.055\t72.76\tAmabilis_Fir\tAdult\t92.067\t29.9133\t0\t1\t0\t8.9\t3\n";
  oOut << "13.8489\t137.787\tHybrid_Spruce\tAdult\t92.0599\t26.9503\t1\t0\t3\t3.4\t2\n";
  oOut << "154.895\t113.556\tHybrid_Spruce\tAdult\t91.9345\t26.941\t1\t1\t3\t6.7\t1\n";
  oOut << "162.897\t56.0791\tWestern_Hemlock\tAdult\t91.8817\t29.9123\t1\t0\t5\t3.2\t2\n";
  oOut << "78.5339\t168.329\tAmabilis_Fir\tAdult\t91.8478\t29.9121\t0\t0\t0\t5.6\t4\n";
  oOut << "8.70972\t47.7356\tPaper_Birch\tAdult\t91.8393\t29.3947\t0\t0\t5\t14.1\t4\n";
  oOut << "182.794\t31.9885\tHybrid_Spruce\tAdult\t91.8341\t26.9335\t0\t0\t2\t3.3\t4\n";
  oOut << "22.7234\t54.9805\tBlack_Cottonwood\tAdult\t91.752\t29.5387\t1\t0\t2\t4.6\t2\n";
  oOut << "109.076\t174.786\tHybrid_Spruce\tAdult\t91.7136\t26.9245\t0\t1\t3\t10.5\t3\n";
  oOut << "153.912\t70.2759\tLodgepole_Pine\tAdult\t91.6467\t29.8309\t1\t0\t2\t9.9\t2\n";
  oOut << "189.844\t136.011\tBlack_Cottonwood\tAdult\t91.6418\t29.5364\t0\t0\t3\t2.1\t4\n";
  oOut << "174.805\t28.3264\tSubalpine_Fir\tAdult\t91.633\t28.8754\t0\t1\t0\t1.7\t3\n";
  oOut << "109.235\t194.061\tWestern_Redcedar\tAdult\t91.5887\t29.905\t0\t1\t1\t22.9\t3\n";
  oOut << "197.632\t157.861\tBlack_Cottonwood\tAdult\t91.5756\t29.535\t0\t1\t1\t8.1\t3\n";
  oOut << "45.343\t53.4241\tSubalpine_Fir\tAdult\t91.4664\t28.8687\t0\t1\t0\t11\t3\n";
  oOut << "132.202\t119.354\tSubalpine_Fir\tAdult\t91.3208\t28.8629\t0\t0\t0\t8.9\t4\n";
  oOut << "109.741\t95.3918\tBlack_Cottonwood\tAdult\t91.3141\t29.5295\t1\t1\t1\t1.8\t1\n";
  oOut << "174.75\t94.4031\tWestern_Hemlock\tAdult\t91.2775\t29.9089\t0\t0\t5\t0.5\t4\n";
  oOut << "4.82178\t120.02\tSubalpine_Fir\tAdult\t91.2274\t28.8591\t0\t0\t0\t11.8\t4\n";
  oOut << "139.844\t10.9436\tTrembling_Aspen\tAdult\t91.1642\t28.6279\t0\t0\t4\t9.8\t4\n";
  oOut << "1.83716\t124.689\tBlack_Cottonwood\tAdult\t91.1108\t29.5252\t1\t1\t1\t14.3\t1\n";
  oOut << "54.2542\t64.5691\tTrembling_Aspen\tAdult\t91.0968\t28.6248\t1\t1\t0\t3.4\t1\n";
  oOut << "180.804\t20.5444\tWestern_Redcedar\tAdult\t90.9647\t29.9012\t0\t1\t2\t13.6\t3\n";
  oOut << "139.044\t19.6411\tTrembling_Aspen\tAdult\t90.9143\t28.6164\t0\t0\t3\t11.1\t4\n";
  oOut << "132.3\t194.159\tSubalpine_Fir\tAdult\t90.7178\t28.8384\t0\t0\t0\t3.3\t4\n";
  oOut << "183.801\t71.3684\tHybrid_Spruce\tAdult\t90.6638\t26.845\t0\t0\t0\t1.8\t4\n";
  oOut << "54.9866\t173.016\tAmabilis_Fir\tAdult\t90.4865\t29.9042\t0\t1\t0\t2.6\t3\n";
  oOut << "190.338\t98.6755\tLodgepole_Pine\tAdult\t90.4568\t29.8192\t0\t1\t0\t11.2\t3\n";
  oOut << "50.0061\t25.592\tTrembling_Aspen\tAdult\t90.4434\t28.5945\t0\t1\t2\t5.4\t3\n";
  oOut << "130.975\t119.8\tLodgepole_Pine\tAdult\t90.4337\t29.819\t0\t0\t3\t0\t4\n";
  oOut << "46.6614\t61.1267\tTrembling_Aspen\tAdult\t90.2371\t28.5848\t1\t1\t5\t0.2\t1\n";
  oOut << "92.0837\t5.18799\tWestern_Hemlock\tAdult\t90.2252\t29.9026\t0\t1\t4\t10.3\t3\n";
  oOut << "182.727\t120.795\tAmabilis_Fir\tAdult\t90.1965\t29.9024\t0\t1\t0\t2.7\t3\n";
  oOut << "177.356\t76.5503\tHybrid_Spruce\tAdult\t90.1468\t26.805\t0\t1\t4\t8.8\t3\n";
  oOut << "169.208\t32.1838\tWestern_Redcedar\tAdult\t90.0916\t29.8957\t1\t1\t2\t2.6\t1\n";
  oOut << "186.31\t157.55\tPaper_Birch\tAdult\t90.0214\t29.3467\t0\t0\t4\t9.3\t4\n";
  oOut << "35.8704\t115.137\tSubalpine_Fir\tAdult\t89.9911\t28.8082\t0\t1\t0\t4.1\t3\n";
  oOut << "195.477\t108.527\tPaper_Birch\tAdult\t89.9194\t29.3439\t0\t1\t0\t9.1\t3\n";
  oOut << "118.506\t150.482\tPaper_Birch\tAdult\t89.884\t29.3429\t0\t0\t4\t5.1\t4\n";
  oOut << "123.901\t179.602\tWestern_Hemlock\tAdult\t89.8761\t29.9004\t1\t1\t2\t1.7\t1\n";
  oOut << "11.2488\t29.4983\tBlack_Cottonwood\tAdult\t89.8361\t29.4972\t0\t0\t0\t11.4\t4\n";
  oOut << "13.9832\t81.7261\tLodgepole_Pine\tAdult\t89.7568\t29.812\t0\t1\t4\t2.5\t3\n";
  oOut << "60.2112\t169.91\tAmabilis_Fir\tAdult\t89.7482\t29.8996\t0\t1\t0\t0\t3\n";
  oOut << "154.205\t41.3818\tLodgepole_Pine\tAdult\t89.675\t29.8111\t1\t1\t0\t3.9\t1\n";
  oOut << "177.948\t28.5034\tLodgepole_Pine\tAdult\t89.4879\t29.8091\t0\t0\t5\t2.3\t4\n";
  oOut << "134.058\t9.44214\tBlack_Cottonwood\tAdult\t89.4391\t29.4881\t0\t0\t5\t10.5\t4\n";
  oOut << "69.3848\t29.4861\tWestern_Redcedar\tAdult\t89.3964\t29.8911\t1\t0\t2\t9.1\t2\n";
  oOut << "50.8118\t121.942\tBlack_Cottonwood\tAdult\t89.3826\t29.4868\t1\t1\t5\t2.9\t1\n";
  oOut << "124.768\t153.552\tHybrid_Spruce\tAdult\t89.2224\t26.7323\t1\t1\t3\t3.2\t1\n";
  oOut << "61.8469\t106.94\tWestern_Redcedar\tAdult\t89.1983\t29.8897\t1\t1\t1\t9.8\t1\n";
  oOut << "95.4224\t125.244\tBlack_Cottonwood\tAdult\t89.1541\t29.4815\t0\t0\t4\t8.2\t4\n";
  oOut << "163.562\t17.1753\tLodgepole_Pine\tAdult\t89.151\t29.8055\t1\t0\t5\t3.2\t2\n";
  oOut << "17.7307\t92.4377\tAmabilis_Fir\tAdult\t88.9456\t29.8944\t0\t1\t0\t14.8\t3\n";
  oOut << "27.5696\t84.9854\tPaper_Birch\tAdult\t88.9453\t29.3165\t1\t0\t4\t7\t2\n";
  oOut << "133.624\t95.6665\tHybrid_Spruce\tAdult\t88.9252\t26.7086\t0\t0\t2\t3.1\t4\n";
  oOut << "100.006\t173.853\tPaper_Birch\tAdult\t88.8937\t29.315\t0\t1\t3\t0.4\t3\n";
  oOut << "180.267\t45.2698\tBlack_Cottonwood\tAdult\t88.8773\t29.475\t0\t0\t2\t1.3\t4\n";
  oOut << "60.6018\t56.8909\tBlack_Cottonwood\tAdult\t88.7622\t29.4723\t1\t1\t3\t3.5\t1\n";
  oOut << "14.74\t69.5496\tLodgepole_Pine\tAdult\t88.5971\t29.7994\t1\t0\t0\t2.3\t2\n";
  oOut << "135.809\t89.2761\tWestern_Hemlock\tAdult\t88.5767\t29.892\t0\t0\t5\t9.7\t4\n";
  oOut << "195.819\t132.794\tAmabilis_Fir\tAdult\t88.3716\t29.8905\t1\t0\t0\t7.2\t2\n";
  oOut << "43.9819\t162.878\tWestern_Hemlock\tAdult\t88.3466\t29.8904\t1\t1\t4\t2.5\t1\n";
  oOut << "74.6582\t82.4768\tWestern_Hemlock\tAdult\t88.3347\t29.8903\t1\t0\t3\t4.6\t2\n";
  oOut << "37.9211\t108.337\tBlack_Cottonwood\tAdult\t88.2846\t29.4608\t1\t1\t1\t9.1\t1\n";
  oOut << "79.1382\t159.265\tBlack_Cottonwood\tAdult\t88.1915\t29.4585\t1\t0\t1\t6.6\t2\n";
  oOut << "193.341\t115.686\tWestern_Redcedar\tAdult\t88.1577\t29.8823\t0\t0\t1\t2.8\t4\n";
  oOut << "67.3767\t21.1365\tWestern_Redcedar\tAdult\t88.1223\t29.8821\t1\t0\t1\t5.7\t2\n";
  oOut << "54.8523\t163.965\tWestern_Redcedar\tAdult\t87.8979\t29.8804\t1\t1\t1\t5.4\t1\n";
  oOut << "159.344\t94.5984\tTrembling_Aspen\tAdult\t87.8442\t28.4673\t1\t1\t0\t9.3\t1\n";
  oOut << "198.895\t174.249\tWestern_Hemlock\tAdult\t87.7603\t29.8862\t0\t1\t0\t5.2\t3\n";
  oOut << "111.249\t9.65576\tBlack_Cottonwood\tAdult\t87.7063\t29.4466\t0\t1\t3\t0.5\t3\n";
  oOut << "55.3894\t98.1201\tBlack_Cottonwood\tAdult\t87.6941\t29.4463\t1\t1\t5\t2.9\t1\n";
  oOut << "3.42407\t9.06982\tPaper_Birch\tAdult\t87.6663\t29.2788\t1\t1\t5\t15\t1\n";
  oOut << "89.6545\t28.6316\tAmabilis_Fir\tAdult\t87.6587\t29.8855\t0\t0\t0\t1\t4\n";
  oOut << "63.2935\t192.749\tSubalpine_Fir\tAdult\t87.561\t28.7013\t0\t0\t0\t0\t4\n";
  oOut << "111.963\t0.744629\tAmabilis_Fir\tAdult\t87.4756\t29.8842\t0\t1\t0\t5.1\t3\n";
  oOut << "118.396\t71.5576\tSubalpine_Fir\tAdult\t87.4387\t28.6957\t0\t1\t0\t10\t3\n";
  oOut << "173.602\t50.946\tPaper_Birch\tAdult\t87.3563\t29.2693\t0\t1\t5\t11.8\t3\n";
  oOut << "106.873\t186.755\tHybrid_Spruce\tAdult\t87.2842\t26.5745\t0\t1\t1\t4.6\t3\n";
  oOut << "63.6963\t67.6331\tSubalpine_Fir\tAdult\t87.2345\t28.6863\t0\t0\t0\t4.3\t4\n";
  oOut << "61.7432\t187.048\tAmabilis_Fir\tAdult\t87.233\t29.8824\t0\t1\t0\t5.1\t3\n";
  oOut << "52.7588\t174.06\tWestern_Redcedar\tAdult\t87.153\t29.8747\t1\t0\t3\t5.4\t2\n";
  oOut << "197.308\t82.6538\tAmabilis_Fir\tAdult\t87.0148\t29.8808\t0\t1\t0\t10.8\t3\n";
  oOut << "21.3806\t44.5496\tBlack_Cottonwood\tAdult\t86.9843\t29.4283\t1\t0\t5\t2.9\t2\n";
  oOut << "190.149\t142.554\tBlack_Cottonwood\tAdult\t86.8805\t29.4256\t0\t0\t2\t3.1\t4\n";
  oOut << "166.107\t188.129\tAmabilis_Fir\tAdult\t86.8234\t29.8793\t1\t1\t0\t1.2\t1\n";
  oOut << "89.9353\t1.63574\tTrembling_Aspen\tAdult\t86.7889\t28.4125\t1\t0\t2\t5.9\t2\n";
  oOut << "85.6384\t78.4729\tPaper_Birch\tAdult\t86.7651\t29.251\t1\t0\t3\t7.8\t2\n";
  oOut << "45.8984\t118.671\tLodgepole_Pine\tAdult\t86.7035\t29.7769\t1\t0\t0\t3\t2\n";
  oOut << "15.5212\t134.308\tBlack_Cottonwood\tAdult\t86.662\t29.4199\t1\t1\t4\t2.4\t1\n";
  oOut << "86.145\t172.357\tWestern_Hemlock\tAdult\t86.568\t29.8774\t1\t0\t5\t10.8\t2\n";
  oOut << "36.3586\t101.831\tAmabilis_Fir\tAdult\t86.4801\t29.8767\t0\t1\t0\t8.5\t3\n";
  oOut << "117.029\t38.4766\tWestern_Hemlock\tAdult\t86.4185\t29.8762\t0\t0\t2\t7.8\t4\n";
  oOut << "186.963\t97.699\tHybrid_Spruce\tAdult\t86.3974\t26.4998\t0\t0\t0\t2.6\t4\n";
  oOut << "75.7385\t42.2424\tLodgepole_Pine\tAdult\t86.3916\t29.773\t1\t0\t5\t10.8\t2\n";
  oOut << "172.351\t30.7617\tAmabilis_Fir\tAdult\t86.2024\t29.8745\t0\t0\t0\t11.7\t4\n";
  oOut << "32.0557\t51.9958\tWestern_Redcedar\tAdult\t86.1874\t29.867\t1\t1\t2\t7.9\t1\n";
  oOut << "111.713\t53.0701\tTrembling_Aspen\tAdult\t86.1853\t28.3802\t0\t1\t5\t2.5\t3\n";
  oOut << "135.675\t99.6155\tWestern_Hemlock\tAdult\t86.1768\t29.8743\t1\t1\t5\t7.9\t1\n";
  oOut << "141.351\t122.467\tPaper_Birch\tAdult\t86.1481\t29.2313\t0\t1\t1\t4.9\t3\n";
  oOut << "108.85\t45.9473\tTrembling_Aspen\tAdult\t86.077\t28.3743\t0\t1\t1\t2\t3\n";
  oOut << "20.3186\t53.186\tTrembling_Aspen\tAdult\t86.0608\t28.3735\t1\t0\t3\t2.6\t2\n";
  oOut << "138.153\t59.1736\tAmabilis_Fir\tAdult\t86.0272\t29.8731\t0\t0\t0\t3.8\t4\n";
  oOut << "3.61938\t94.5862\tTrembling_Aspen\tAdult\t86.0223\t28.3714\t0\t1\t4\t10.2\t3\n";
  oOut << "78.5034\t172.992\tAmabilis_Fir\tAdult\t86.0126\t29.873\t0\t0\t0\t10.8\t4\n";
  oOut << "21.814\t114.398\tWestern_Redcedar\tAdult\t85.8621\t29.8642\t1\t0\t5\t5.7\t2\n";
  oOut << "127.277\t180.524\tHybrid_Spruce\tAdult\t85.7211\t26.4417\t0\t0\t2\t4.6\t4\n";
  oOut << "104.901\t109.247\tSubalpine_Fir\tAdult\t85.61\t28.6087\t0\t1\t0\t7.4\t3\n";
  oOut << "19.0918\t120.197\tTrembling_Aspen\tAdult\t85.6091\t28.3488\t1\t0\t2\t0.6\t2\n";
  oOut << "55.7251\t37.4695\tWestern_Redcedar\tAdult\t85.6052\t29.8621\t1\t1\t5\t7.7\t1\n";
  oOut << "172.528\t121.802\tWestern_Redcedar\tAdult\t85.5997\t29.862\t0\t0\t1\t14.2\t4\n";
  oOut << "22.6257\t142.468\tWestern_Hemlock\tAdult\t85.5286\t29.8691\t0\t1\t4\t0\t3\n";
  oOut << "154.962\t73.4985\tSubalpine_Fir\tAdult\t85.5139\t28.6039\t0\t1\t0\t9.5\t3\n";
  oOut << "113.788\t90.4968\tSubalpine_Fir\tAdult\t85.3644\t28.5965\t0\t1\t0\t5.5\t3\n";
  oOut << "82.1899\t100.22\tTrembling_Aspen\tAdult\t85.2982\t28.3316\t1\t0\t3\t11.6\t2\n";
  oOut << "127.393\t71.2341\tPaper_Birch\tAdult\t85.275\t29.2026\t1\t1\t0\t8.1\t1\n";
  oOut << "101.013\t165.723\tBlack_Cottonwood\tAdult\t84.9774\t29.3743\t0\t1\t2\t4\t3\n";
  oOut << "69.3848\t106.921\tBlack_Cottonwood\tAdult\t84.9411\t29.3732\t1\t0\t1\t9.4\t2\n";
  oOut << "137.079\t199.689\tBlack_Cottonwood\tAdult\t84.9057\t29.3722\t1\t1\t0\t11.5\t1\n";
  oOut << "59.9854\t166.01\tWestern_Hemlock\tAdult\t84.8898\t29.8637\t1\t1\t2\t5.7\t1\n";
  oOut << "112.299\t46.7957\tPaper_Birch\tAdult\t84.6988\t29.1831\t0\t1\t1\t4.7\t3\n";
  oOut << "152.893\t26.2878\tHybrid_Spruce\tAdult\t84.4986\t26.3343\t1\t0\t0\t7.9\t2\n";
  oOut << "151.031\t123.383\tHybrid_Spruce\tAdult\t84.491\t26.3336\t1\t1\t4\t0.9\t1\n";
  oOut << "41.095\t153.882\tHybrid_Spruce\tAdult\t84.4791\t26.3326\t1\t1\t0\t0.2\t1\n";
  oOut << "134.778\t166.858\tTrembling_Aspen\tAdult\t84.3524\t28.2781\t0\t0\t2\t1.4\t4\n";
  oOut << "76.5259\t24.2798\tLodgepole_Pine\tAdult\t84.267\t29.7443\t0\t0\t2\t4.2\t4\n";
  oOut << "101.636\t146.387\tWestern_Hemlock\tAdult\t84.155\t29.8572\t0\t1\t0\t6.9\t3\n";
  oOut << "131.83\t181.116\tTrembling_Aspen\tAdult\t84.0259\t28.2593\t0\t0\t3\t6.3\t4\n";
  oOut << "110.925\t172.809\tPaper_Birch\tAdult\t83.9792\t29.158\t0\t1\t3\t11.6\t3\n";
  oOut << "172.04\t35.7422\tAmabilis_Fir\tAdult\t83.8965\t29.8549\t0\t1\t0\t10.7\t3\n";
  oOut << "50.7263\t127.826\tWestern_Hemlock\tAdult\t83.804\t29.8541\t1\t1\t3\t1.9\t1\n";
  oOut << "107.245\t60.5713\tLodgepole_Pine\tAdult\t83.793\t29.7374\t0\t1\t5\t3.7\t3\n";
  oOut << "76.8433\t147.992\tTrembling_Aspen\tAdult\t83.7686\t28.2443\t1\t0\t2\t4.2\t2\n";
  oOut << "129.028\t109.155\tAmabilis_Fir\tAdult\t83.7466\t29.8535\t0\t0\t0\t11.9\t4\n";
  oOut << "142.212\t46.0266\tLodgepole_Pine\tAdult\t83.5941\t29.7345\t0\t1\t1\t4.7\t3\n";
  oOut << "168.182\t181\tWestern_Redcedar\tAdult\t83.5001\t29.8427\t1\t1\t0\t1\t1\n";
  oOut << "155.17\t104.962\tAmabilis_Fir\tAdult\t83.4784\t29.851\t0\t0\t0\t9.9\t4\n";
  oOut << "60.7971\t49.3469\tWestern_Redcedar\tAdult\t83.4311\t29.842\t1\t1\t0\t7.4\t1\n";
  oOut << "159.906\t94.1833\tPaper_Birch\tAdult\t83.3768\t29.1364\t1\t0\t3\t1.3\t2\n";
  oOut << "33.4961\t91.2659\tLodgepole_Pine\tAdult\t83.3459\t29.7308\t1\t1\t5\t1.5\t1\n";
  oOut << "14.8376\t51.593\tPaper_Birch\tAdult\t83.3383\t29.135\t0\t1\t3\t4.2\t3\n";
  oOut << "166.052\t114.868\tHybrid_Spruce\tAdult\t83.3246\t26.2281\t1\t0\t5\t8.1\t2\n";
  oOut << "0.616455\t32.3242\tHybrid_Spruce\tAdult\t83.2599\t26.2221\t0\t1\t3\t3.9\t3\n";
  oOut << "39.3066\t143.207\tBlack_Cottonwood\tAdult\t83.2541\t29.3238\t0\t1\t3\t1.9\t3\n";
  oOut << "120.85\t187.524\tWestern_Redcedar\tAdult\t83.2361\t29.8401\t0\t0\t2\t20.1\t4\n";
  oOut << "136.914\t123.224\tHybrid_Spruce\tAdult\t83.1815\t26.2149\t0\t0\t3\t5.7\t4\n";
  oOut << "166.888\t35.3149\tSubalpine_Fir\tAdult\t83.1177\t28.4806\t0\t0\t0\t10.9\t4\n";
  oOut << "71.3989\t1.0376\tLodgepole_Pine\tAdult\t83.0286\t29.726\t1\t0\t1\t0.4\t2\n";
  oOut << "83.5144\t38.0371\tLodgepole_Pine\tAdult\t83.0032\t29.7256\t1\t0\t5\t7.5\t2\n";
  oOut << "45.6909\t28.064\tBlack_Cottonwood\tAdult\t82.8751\t29.3122\t0\t1\t0\t5.7\t3\n";
  oOut << "192.169\t17.4316\tLodgepole_Pine\tAdult\t82.8525\t29.7232\t0\t1\t1\t0.7\t3\n";
  oOut << "16.4734\t92.1997\tLodgepole_Pine\tAdult\t82.793\t29.7223\t0\t1\t0\t13.9\t3\n";
  oOut << "178.333\t173.926\tSubalpine_Fir\tAdult\t82.7478\t28.4606\t0\t0\t0\t9.3\t4\n";
  oOut << "132.843\t56.5002\tHybrid_Spruce\tAdult\t82.7173\t26.1719\t0\t0\t4\t2.8\t4\n";
  oOut << "165.259\t156.799\tAmabilis_Fir\tAdult\t82.699\t29.8435\t1\t0\t0\t3.2\t2\n";
  oOut << "38.9587\t101.501\tHybrid_Spruce\tAdult\t82.6611\t26.1667\t1\t1\t4\t10.5\t1\n";
  oOut << "99.7375\t33.2703\tSubalpine_Fir\tAdult\t82.5494\t28.4498\t0\t0\t0\t6\t4\n";
  oOut << "61.0229\t127.991\tWestern_Redcedar\tAdult\t82.5244\t29.8329\t1\t1\t3\t8.5\t1\n";
  oOut << "169.391\t0.634766\tHybrid_Spruce\tAdult\t82.4969\t26.1513\t1\t1\t4\t6.9\t1\n";
  oOut << "56.4148\t190.533\tWestern_Redcedar\tAdult\t82.4014\t29.8316\t1\t1\t2\t5.6\t1\n";
  oOut << "61.5967\t179.272\tLodgepole_Pine\tAdult\t82.3923\t29.716\t1\t1\t4\t3.1\t1\n";
  oOut << "49.9573\t108.954\tPaper_Birch\tAdult\t82.2717\t29.0954\t1\t1\t2\t3.8\t1\n";
  oOut << "132.928\t54.0588\tWestern_Hemlock\tAdult\t82.2635\t29.8392\t0\t0\t3\t2.4\t4\n";
  oOut << "146.838\t54.0588\tLodgepole_Pine\tAdult\t82.258\t29.7139\t1\t0\t2\t10.2\t2\n";
  oOut << "5.52368\t61.0229\tAmabilis_Fir\tAdult\t82.2104\t29.8386\t0\t0\t0\t1.2\t4\n";
  oOut << "0.561523\t113.623\tSubalpine_Fir\tAdult\t82.157\t28.4281\t0\t0\t0\t7\t4\n";
  oOut << "152.393\t21.6614\tSubalpine_Fir\tAdult\t82.1448\t28.4274\t0\t1\t0\t3.9\t3\n";
  oOut << "8.6731\t47.3328\tSubalpine_Fir\tAdult\t82.1268\t28.4264\t0\t0\t0\t12.4\t4\n";
  oOut << "164.771\t17.7979\tHybrid_Spruce\tAdult\t82.1024\t26.1142\t1\t0\t4\t3.5\t2\n";
  oOut << "182.916\t135.376\tWestern_Redcedar\tAdult\t82.1014\t29.8284\t0\t1\t1\t11.7\t3\n";
  oOut << "114.484\t140.784\tWestern_Redcedar\tAdult\t82.0862\t29.8282\t0\t1\t0\t14.7\t3\n";
  oOut << "133.618\t128.082\tSubalpine_Fir\tAdult\t82.0486\t28.4221\t0\t0\t0\t1.5\t4\n";
  oOut << "190.045\t119.031\tHybrid_Spruce\tAdult\t81.9983\t26.1043\t0\t0\t1\t9.7\t4\n";
  oOut << "106.25\t119.873\tTrembling_Aspen\tAdult\t81.9788\t28.1364\t0\t1\t1\t12\t3\n";
  oOut << "7.36084\t33.0811\tSubalpine_Fir\tAdult\t81.9543\t28.4168\t1\t1\t5\t0.2\t1\n";
  oOut << "76.6663\t102.368\tWestern_Hemlock\tAdult\t81.9266\t29.8357\t1\t0\t1\t7.3\t2\n";
  oOut << "6.56128\t179.218\tWestern_Hemlock\tAdult\t81.922\t29.8357\t0\t0\t0\t4.4\t4\n";
  oOut << "89.9597\t78.363\tPaper_Birch\tAdult\t81.8759\t29.0802\t1\t0\t0\t11.3\t2\n";
  oOut << "30.0842\t139.465\tTrembling_Aspen\tAdult\t81.8219\t28.1266\t1\t1\t1\t8\t1\n";
  oOut << "72.7112\t169.318\tTrembling_Aspen\tAdult\t81.7749\t28.1237\t1\t0\t4\t2.3\t2\n";
  oOut << "135.675\t5.80444\tTrembling_Aspen\tAdult\t81.7157\t28.12\t0\t0\t0\t8.8\t4\n";
  oOut << "150.464\t149.359\tSubalpine_Fir\tAdult\t81.7081\t28.403\t0\t0\t0\t4.6\t4\n";
  oOut << "60.73\t120.459\tHybrid_Spruce\tAdult\t81.6614\t26.0723\t1\t1\t1\t8.5\t1\n";
  oOut << "50.0549\t151.318\tLodgepole_Pine\tAdult\t81.6479\t29.7039\t1\t1\t1\t5.8\t1\n";
  oOut << "2.67334\t43.0298\tPaper_Birch\tAdult\t81.6309\t29.0707\t1\t1\t3\t12.5\t1\n";
  oOut << "29.2725\t69.6411\tBlack_Cottonwood\tAdult\t81.4853\t29.2678\t1\t0\t2\t9.8\t2\n";
  oOut << "160.626\t189.24\tWestern_Redcedar\tAdult\t81.3766\t29.8205\t1\t1\t2\t4.4\t1\n";
  oOut << "134.21\t129.053\tAmabilis_Fir\tAdult\t81.3721\t29.8299\t1\t0\t0\t9.4\t2\n";
  oOut << "185.535\t159.662\tSubalpine_Fir\tAdult\t81.3635\t28.3834\t0\t0\t0\t8.2\t4\n";
  oOut << "170.929\t73.2056\tHybrid_Spruce\tAdult\t81.3498\t26.0424\t1\t0\t4\t5.3\t2\n";
  oOut << "44.2932\t198.828\tTrembling_Aspen\tAdult\t81.3428\t28.0964\t1\t1\t3\t9.8\t1\n";
  oOut << "154.974\t125.421\tSubalpine_Fir\tAdult\t81.2216\t28.3753\t0\t1\t0\t11.6\t3\n";
  oOut << "58.7585\t42.2607\tWestern_Hemlock\tAdult\t81.1838\t29.8279\t1\t1\t5\t8.5\t1\n";
  oOut << "110.59\t159.302\tAmabilis_Fir\tAdult\t81.0556\t29.8265\t0\t1\t0\t8.8\t3\n";
  oOut << "2.56348\t3.32031\tLodgepole_Pine\tAdult\t81.0385\t29.6936\t0\t0\t5\t12.7\t4\n";
  oOut << "18.4998\t23.1384\tPaper_Birch\tAdult\t80.9995\t29.0457\t0\t1\t1\t4.1\t3\n";
  oOut << "77.8503\t25.7507\tBlack_Cottonwood\tAdult\t80.9933\t29.2514\t1\t0\t3\t5.2\t2\n";
  oOut << "193.604\t184.564\tHybrid_Spruce\tAdult\t80.9839\t26.007\t0\t1\t5\t10.5\t3\n";
  oOut << "118.622\t58.7952\tLodgepole_Pine\tAdult\t80.9796\t29.6926\t1\t0\t2\t3.5\t2\n";
  oOut << "109.778\t47.3267\tSubalpine_Fir\tAdult\t80.8817\t28.3557\t0\t0\t0\t5\t4\n";
  oOut << "163.428\t69.2322\tTrembling_Aspen\tAdult\t80.8011\t28.0618\t1\t1\t3\t7.3\t1\n";
  oOut << "190.961\t148.383\tWestern_Hemlock\tAdult\t80.6717\t29.8222\t0\t0\t5\t4\t4\n";
  oOut << "108.649\t2.20947\tPaper_Birch\tAdult\t80.6494\t29.0316\t0\t1\t2\t0.2\t3\n";
  oOut << "43.8049\t181.787\tWestern_Hemlock\tAdult\t80.6277\t29.8217\t1\t1\t5\t1.2\t1\n";
  oOut << "9.97925\t90.448\tTrembling_Aspen\tAdult\t80.6061\t28.0491\t0\t1\t3\t2.9\t3\n";
  oOut << "53.0701\t9.729\tTrembling_Aspen\tAdult\t80.5624\t28.0463\t1\t1\t0\t10.3\t1\n";
  oOut << "115.051\t38.6902\tTrembling_Aspen\tAdult\t80.5399\t28.0448\t0\t1\t2\t10.8\t3\n";
  oOut << "21.6064\t138.373\tWestern_Redcedar\tAdult\t80.5341\t29.8108\t0\t1\t3\t6.9\t3\n";
  oOut << "67.0715\t168.024\tWestern_Redcedar\tAdult\t80.3622\t29.8087\t1\t0\t2\t6.3\t2\n";
  oOut << "167.578\t195.734\tPaper_Birch\tAdult\t80.3046\t29.0175\t1\t0\t0\t7.6\t2\n";
  oOut << "64.2212\t136.005\tPaper_Birch\tAdult\t80.2924\t29.017\t1\t1\t0\t1.6\t1\n";
  oOut << "182.825\t184.155\tAmabilis_Fir\tAdult\t80.2859\t29.8178\t1\t0\t0\t10.5\t2\n";
  oOut << "142.053\t105.682\tHybrid_Spruce\tAdult\t80.2078\t25.9309\t0\t1\t3\t8\t3\n";
  oOut << "185.193\t17.6941\tWestern_Hemlock\tAdult\t80.1282\t29.816\t0\t0\t1\t10.3\t4\n";
  oOut << "107.947\t140.039\tSubalpine_Fir\tAdult\t80.0525\t28.3068\t0\t1\t0\t8.1\t3\n";
  oOut << "25.2869\t111.749\tWestern_Hemlock\tAdult\t80.0323\t29.8149\t0\t1\t5\t3.8\t3\n";
  oOut << "39.7461\t5.43823\tWestern_Hemlock\tAdult\t79.9933\t29.8144\t1\t1\t1\t9.5\t1\n";
  oOut << "120.911\t14.6179\tBlack_Cottonwood\tAdult\t79.9518\t29.2155\t0\t0\t2\t1.1\t4\n";
  oOut << "92.688\t182.611\tTrembling_Aspen\tAdult\t79.91\t28.0033\t0\t1\t4\t10.1\t3\n";
  oOut << "88.5864\t46.0693\tPaper_Birch\tAdult\t79.855\t28.9988\t1\t0\t2\t8.2\t2\n";
  oOut << "156.226\t121.588\tSubalpine_Fir\tAdult\t79.7256\t28.2871\t0\t0\t0\t7.8\t4\n";
  oOut << "91.3696\t113.629\tWestern_Redcedar\tAdult\t79.7092\t29.8008\t0\t1\t3\t11.2\t3\n";
  oOut << "122.949\t170.654\tBlack_Cottonwood\tAdult\t79.6609\t29.2051\t0\t0\t3\t2.5\t4\n";
  oOut << "184.186\t58.6975\tWestern_Hemlock\tAdult\t79.5746\t29.8095\t0\t0\t1\t1.6\t4\n";
  oOut << "30.3223\t190.948\tBlack_Cottonwood\tAdult\t79.5135\t29.1999\t1\t0\t4\t5.7\t2\n";
  oOut << "195.166\t109.32\tPaper_Birch\tAdult\t79.4427\t28.9813\t0\t0\t0\t10.9\t4\n";
  oOut << "134.167\t155.219\tBlack_Cottonwood\tAdult\t79.4186\t29.1964\t0\t0\t5\t0.9\t4\n";
  oOut << "83.8501\t91.803\tHybrid_Spruce\tAdult\t79.4092\t25.851\t1\t0\t2\t2.7\t2\n";
  oOut << "41.0889\t84.6741\tHybrid_Spruce\tAdult\t79.4022\t25.8503\t0\t0\t4\t7.4\t4\n";
  oOut << "12.4695\t128.717\tAmabilis_Fir\tAdult\t79.3292\t29.8065\t0\t1\t0\t10.6\t3\n";
  oOut << "186.792\t65.094\tLodgepole_Pine\tAdult\t79.3137\t29.6626\t0\t0\t0\t1.4\t4\n";
  oOut << "74.4446\t156.177\tLodgepole_Pine\tAdult\t79.3045\t29.6624\t0\t0\t5\t8.1\t4\n";
  oOut << "198.151\t157.324\tBlack_Cottonwood\tAdult\t79.1922\t29.1882\t0\t1\t0\t11.2\t3\n";
  oOut << "47.699\t36.5723\tWestern_Redcedar\tAdult\t79.1306\t29.7935\t1\t1\t3\t7.1\t1\n";
  oOut << "101.196\t179.803\tWestern_Redcedar\tAdult\t79.0756\t29.7928\t0\t1\t4\t13.8\t3\n";
  oOut << "185.217\t81.8359\tBlack_Cottonwood\tAdult\t79.0582\t29.1833\t0\t1\t1\t11.2\t3\n";
  oOut << "138.751\t157.013\tSubalpine_Fir\tAdult\t78.9722\t28.2409\t0\t1\t1\t6.3\t3\n";
  oOut << "149.316\t105.365\tWestern_Redcedar\tAdult\t78.9404\t29.791\t1\t0\t0\t20.5\t2\n";
  oOut << "44.5984\t91.2048\tTrembling_Aspen\tAdult\t78.8437\t27.9311\t1\t1\t1\t3.4\t1\n";
  oOut << "18.7805\t97.8455\tSubalpine_Fir\tAdult\t78.8037\t28.2304\t0\t1\t0\t13.5\t3\n";
  oOut << "146.49\t172.516\tWestern_Hemlock\tAdult\t78.6682\t29.7983\t1\t1\t2\t3.4\t1\n";
  oOut << "64.801\t51.4954\tPaper_Birch\tAdult\t78.6328\t28.946\t1\t0\t0\t5.2\t2\n";
  oOut << "10.2905\t192.236\tAmabilis_Fir\tAdult\t78.6148\t29.7976\t0\t0\t0\t14.7\t4\n";
  oOut << "82.9712\t168.25\tLodgepole_Pine\tAdult\t78.5931\t29.6487\t1\t0\t5\t7.8\t2\n";
  oOut << "175.061\t21.2585\tPaper_Birch\tAdult\t78.5895\t28.9441\t0\t1\t4\t9.6\t3\n";
  oOut << "85.7361\t90.5518\tAmabilis_Fir\tAdult\t78.584\t29.7972\t0\t0\t0\t9.7\t4\n";
  oOut << "65.3931\t161.188\tPaper_Birch\tAdult\t78.5556\t28.9426\t1\t0\t3\t0.4\t2\n";
  oOut << "11.9873\t83.0261\tTrembling_Aspen\tAdult\t78.479\t27.9058\t1\t0\t4\t14.1\t2\n";
  oOut << "1.37939\t39.3188\tBlack_Cottonwood\tAdult\t78.4293\t29.1598\t0\t1\t5\t14.6\t3\n";
  oOut << "123.328\t195.746\tHybrid_Spruce\tAdult\t78.3109\t25.7386\t0\t0\t2\t1.4\t4\n";
  oOut << "17.334\t107.489\tTrembling_Aspen\tAdult\t78.2904\t27.8926\t0\t0\t3\t13.5\t4\n";
  oOut << "54.5288\t37.03\tAmabilis_Fir\tAdult\t78.2883\t29.7934\t0\t1\t0\t5.5\t3\n";
  oOut << "114.624\t125.14\tWestern_Hemlock\tAdult\t78.2462\t29.7929\t0\t1\t3\t2.7\t3\n";
  oOut << "134.454\t109.259\tWestern_Redcedar\tAdult\t78.1815\t29.7809\t1\t1\t1\t21.6\t1\n";
  oOut << "156.47\t91.6809\tWestern_Hemlock\tAdult\t78.1659\t29.7918\t1\t1\t1\t9.9\t1\n";
  oOut << "174.701\t125.238\tBlack_Cottonwood\tAdult\t78.1271\t29.1483\t0\t0\t0\t3\t4\n";
  oOut << "25.1343\t62.7686\tPaper_Birch\tAdult\t78.0664\t28.9206\t0\t0\t1\t4.4\t4\n";
  oOut << "159.937\t134.601\tAmabilis_Fir\tAdult\t78.0243\t29.7899\t1\t1\t0\t8.1\t1\n";
  oOut << "168.835\t131.921\tSubalpine_Fir\tAdult\t77.9413\t28.1756\t0\t1\t0\t11.1\t3\n";
  oOut << "131.537\t93.4326\tSubalpine_Fir\tAdult\t77.8049\t28.1668\t0\t0\t0\t8.8\t4\n";
  oOut << "143.201\t12.5671\tAmabilis_Fir\tAdult\t77.7448\t29.7862\t0\t0\t0\t4.1\t4\n";
  oOut << "180.182\t137.433\tTrembling_Aspen\tAdult\t77.641\t27.8464\t0\t0\t4\t3.8\t4\n";
  oOut << "2.62451\t96.6858\tWestern_Redcedar\tAdult\t77.612\t29.773\t0\t1\t3\t5\t3\n";
  oOut << "121.405\t127.454\tWestern_Hemlock\tAdult\t77.5854\t29.7841\t0\t0\t5\t8.4\t4\n";
  oOut << "39.2273\t1.5686\tLodgepole_Pine\tAdult\t77.5317\t29.6272\t1\t1\t0\t12\t1\n";
  oOut << "124.036\t17.4194\tPaper_Birch\tAdult\t77.4832\t28.8939\t0\t0\t4\t9.3\t4\n";
  oOut << "180.286\t108.893\tAmabilis_Fir\tAdult\t77.4637\t29.7824\t0\t0\t0\t1.7\t4\n";
  oOut << "189.185\t95.52\tAmabilis_Fir\tAdult\t77.3013\t29.7802\t0\t1\t0\t11.2\t3\n";
  oOut << "108.154\t129.559\tBlack_Cottonwood\tAdult\t77.2925\t29.1157\t0\t1\t2\t1.2\t3\n";
  oOut << "165.112\t6.23779\tTrembling_Aspen\tAdult\t77.269\t27.8196\t1\t0\t5\t6\t2\n";
  oOut << "57.4097\t20.4346\tAmabilis_Fir\tAdult\t77.2064\t29.7788\t0\t1\t0\t2.2\t3\n";
  oOut << "188.086\t2.27051\tAmabilis_Fir\tAdult\t77.1536\t29.7781\t0\t0\t0\t9.5\t4\n";
  oOut << "137.598\t170.837\tWestern_Redcedar\tAdult\t77.0963\t29.7656\t0\t0\t0\t10.2\t4\n";
  oOut << "65.1367\t160.986\tAmabilis_Fir\tAdult\t76.9843\t29.7757\t0\t0\t0\t4.6\t4\n";
  oOut << "86.2854\t39.7644\tHybrid_Spruce\tAdult\t76.9629\t25.5965\t1\t0\t5\t0.5\t2\n";
  oOut << "103.735\t42.1326\tSubalpine_Fir\tAdult\t76.9492\t28.1106\t0\t1\t0\t5.5\t3\n";
  oOut << "179.376\t68.2251\tLodgepole_Pine\tAdult\t76.9028\t29.6138\t0\t0\t2\t1.2\t4\n";
  oOut << "173.486\t63.3362\tWestern_Redcedar\tAdult\t76.8973\t29.7626\t0\t0\t2\t2.7\t4\n";
  oOut << "74.3042\t80.9998\tWestern_Redcedar\tAdult\t76.8146\t29.7614\t1\t0\t5\t7.3\t2\n";
  oOut << "10.675\t85.2356\tWestern_Hemlock\tAdult\t76.7548\t29.7725\t0\t1\t0\t4.7\t3\n";
  oOut << "55.2185\t19.574\tHybrid_Spruce\tAdult\t76.7453\t25.5732\t1\t1\t2\t11.9\t1\n";
  oOut << "195.294\t103.076\tWestern_Redcedar\tAdult\t76.7252\t29.7601\t0\t0\t2\t15\t4\n";
  oOut << "177.209\t176.434\tBlack_Cottonwood\tAdult\t76.7151\t29.0925\t0\t0\t1\t4.8\t4\n";
  oOut << "80.0781\t104.449\tWestern_Hemlock\tAdult\t76.712\t29.7718\t0\t1\t5\t1.4\t3\n";
  oOut << "123.541\t86.4319\tWestern_Hemlock\tAdult\t76.6467\t29.7709\t0\t0\t1\t11.8\t4\n";
  oOut << "8.40454\t98.7061\tWestern_Hemlock\tAdult\t76.5887\t29.7701\t1\t0\t5\t12\t2\n";
  oOut << "113.959\t2.52075\tAmabilis_Fir\tAdult\t76.4166\t29.7676\t0\t1\t0\t2.8\t3\n";
  oOut << "138.159\t183.856\tWestern_Redcedar\tAdult\t76.3263\t29.754\t0\t1\t5\t14.4\t3\n";
  oOut << "135.364\t119.525\tPaper_Birch\tAdult\t76.3019\t28.8376\t0\t0\t4\t4.3\t4\n";
  oOut << "46.2769\t94.8792\tSubalpine_Fir\tAdult\t76.2695\t28.0646\t0\t1\t0\t3.8\t3\n";
  oOut << "81.8848\t121.558\tHybrid_Spruce\tAdult\t76.2201\t25.5162\t1\t0\t5\t10.6\t2\n";
  oOut << "71.0815\t154.559\tLodgepole_Pine\tAdult\t76.2024\t29.5984\t1\t0\t5\t5.7\t2\n";
  oOut << "183.728\t5.0415\tAmabilis_Fir\tAdult\t76.1884\t29.7642\t0\t1\t0\t7.5\t3\n";
  oOut << "160.394\t192.279\tSubalpine_Fir\tAdult\t76.1462\t28.0562\t0\t1\t5\t2.7\t3\n";
  oOut << "19.0491\t175.604\tLodgepole_Pine\tAdult\t76.1057\t29.5962\t1\t0\t4\t1.3\t2\n";
  oOut << "94.9951\t79.1016\tTrembling_Aspen\tAdult\t76.0556\t27.7296\t0\t1\t4\t2.4\t3\n";
  oOut << "124.255\t174.072\tTrembling_Aspen\tAdult\t76.0413\t27.7285\t0\t0\t3\t8.3\t4\n";
  oOut << "141.565\t19.6045\tLodgepole_Pine\tAdult\t75.9677\t29.593\t0\t0\t4\t5.5\t4\n";
  oOut << "141.913\t69.3848\tLodgepole_Pine\tAdult\t75.8035\t29.5893\t0\t0\t1\t3.3\t4\n";
  oOut << "101.019\t137.213\tBlack_Cottonwood\tAdult\t75.7404\t29.0518\t0\t1\t3\t6.4\t3\n";
  oOut << "175.073\t88.2996\tPaper_Birch\tAdult\t75.5145\t28.7985\t0\t1\t1\t10.7\t3\n";
  oOut << "146.332\t14.0015\tAmabilis_Fir\tAdult\t75.5084\t29.7539\t0\t0\t0\t9.2\t4\n";
  oOut << "117.554\t199.158\tSubalpine_Fir\tAdult\t75.4816\t28.01\t0\t0\t0\t7.2\t4\n";
  oOut << "138.562\t31.9702\tLodgepole_Pine\tAdult\t75.3711\t29.5792\t0\t0\t5\t9.8\t4\n";
  oOut << "196.49\t168.988\tHybrid_Spruce\tAdult\t75.2383\t25.4078\t0\t0\t1\t8.1\t4\n";
  oOut << "33.5754\t2.94189\tLodgepole_Pine\tAdult\t75.2295\t29.5759\t0\t1\t1\t11.4\t3\n";
  oOut << "193.878\t178.723\tLodgepole_Pine\tAdult\t75.2042\t29.5753\t0\t0\t4\t7.2\t4\n";
  oOut << "127.771\t88.501\tTrembling_Aspen\tAdult\t75.1611\t27.6609\t0\t0\t0\t9.5\t4\n";
  oOut << "30.957\t52.1729\tHybrid_Spruce\tAdult\t75.0894\t25.3912\t0\t1\t1\t11.7\t3\n";
  oOut << "15.8264\t54.3884\tWestern_Hemlock\tAdult\t75.0156\t29.7461\t0\t0\t1\t13.7\t4\n";
  oOut << "163.916\t42.395\tWestern_Redcedar\tAdult\t75.0024\t29.7329\t1\t1\t3\t3.7\t1\n";
  oOut << "30.6274\t68.0908\tWestern_Redcedar\tAdult\t74.9478\t29.732\t1\t0\t2\t5.4\t2\n";
  oOut << "26.8921\t29.7913\tBlack_Cottonwood\tAdult\t74.8138\t29.0114\t1\t0\t5\t2.5\t2\n";
  oOut << "86.499\t142.761\tLodgepole_Pine\tAdult\t74.6835\t29.5627\t1\t0\t5\t6.9\t2\n";
  oOut << "95.5383\t127.85\tWestern_Hemlock\tAdult\t74.6786\t29.7407\t0\t1\t3\t2.2\t3\n";
  oOut << "14.6912\t161.993\tHybrid_Spruce\tAdult\t74.678\t25.3448\t0\t1\t2\t0.7\t3\n";
  oOut << "157.77\t141.376\tAmabilis_Fir\tAdult\t74.6664\t29.7405\t1\t0\t0\t0.7\t2\n";
  oOut << "3.71704\t190.247\tSubalpine_Fir\tAdult\t74.6301\t27.9492\t0\t0\t0\t3.4\t4\n";
  oOut << "193.073\t82.8125\tAmabilis_Fir\tAdult\t74.5889\t29.7392\t0\t0\t0\t5.9\t4\n";
  oOut << "172.253\t64.6484\tLodgepole_Pine\tAdult\t74.5413\t29.5592\t0\t1\t0\t4.4\t3\n";
  oOut << "60.8643\t45.8557\tHybrid_Spruce\tAdult\t74.4998\t25.3246\t1\t1\t0\t5.1\t1\n";
  oOut << "132.574\t150.507\tTrembling_Aspen\tAdult\t74.4968\t27.6085\t0\t0\t2\t7.6\t4\n";
  oOut << "15.1917\t47.8943\tLodgepole_Pine\tAdult\t74.4922\t29.558\t0\t1\t3\t3.9\t3\n";
  oOut << "47.229\t1.01318\tLodgepole_Pine\tAdult\t74.4885\t29.5579\t1\t1\t0\t4.7\t1\n";
  oOut << "64.1296\t165.198\tBlack_Cottonwood\tAdult\t74.4772\t28.9963\t1\t0\t3\t4.3\t2\n";
  oOut << "145.532\t59.8267\tTrembling_Aspen\tAdult\t74.4089\t27.6015\t1\t1\t0\t4.1\t1\n";
  oOut << "149.689\t100.464\tWestern_Redcedar\tAdult\t74.3665\t29.7221\t1\t0\t5\t14.3\t2\n";
  oOut << "56.2927\t11.0718\tWestern_Hemlock\tAdult\t74.1467\t29.7318\t1\t1\t2\t7.6\t1\n";
  oOut << "157.861\t65.0818\tSubalpine_Fir\tAdult\t74.1382\t27.9133\t0\t1\t0\t2.4\t3\n";
  oOut << "62.7808\t193.109\tHybrid_Spruce\tAdult\t73.9728\t25.2642\t1\t0\t2\t10.2\t2\n";
  oOut << "28.0762\t190.924\tWestern_Hemlock\tAdult\t73.8974\t29.7276\t0\t0\t2\t8.8\t4\n";
  oOut << "189.392\t28.1311\tHybrid_Spruce\tAdult\t73.8248\t25.2471\t0\t0\t0\t10.2\t4\n";
  oOut << "33.9294\t151.782\tPaper_Birch\tAdult\t73.736\t28.7053\t0\t1\t4\t1.9\t3\n";
  oOut << "158.954\t131.744\tWestern_Redcedar\tAdult\t73.7122\t29.7105\t1\t1\t1\t12.9\t1\n";
  oOut << "10.6812\t98.9075\tAmabilis_Fir\tAdult\t73.6969\t29.7241\t0\t0\t0\t3.2\t4\n";
  oOut << "158.722\t180.762\tBlack_Cottonwood\tAdult\t73.6639\t28.9589\t1\t1\t1\t6.3\t1\n";
  oOut << "57.0374\t65.7104\tTrembling_Aspen\tAdult\t73.624\t27.5379\t1\t1\t1\t8\t1\n";
  oOut << "143.634\t182.379\tBlack_Cottonwood\tAdult\t73.5956\t28.9557\t0\t1\t3\t0.8\t3\n";
  oOut << "166.107\t129.706\tLodgepole_Pine\tAdult\t73.5678\t29.5345\t1\t1\t0\t3\t1\n";
  oOut << "96.167\t141.113\tLodgepole_Pine\tAdult\t73.5562\t29.5342\t0\t1\t0\t5.2\t3\n";
  oOut << "123.389\t122.272\tTrembling_Aspen\tAdult\t73.4796\t27.526\t0\t0\t1\t1.2\t4\n";
  oOut << "26.1353\t99.1272\tTrembling_Aspen\tAdult\t73.4134\t27.5205\t0\t0\t3\t8.9\t4\n";
  oOut << "37.2925\t99.0234\tHybrid_Spruce\tAdult\t73.392\t25.1968\t1\t1\t2\t9.1\t1\n";
  oOut << "96.2036\t1.5686\tBlack_Cottonwood\tAdult\t73.3417\t28.9437\t0\t1\t1\t0.4\t3\n";
  oOut << "105.481\t85.907\tHybrid_Spruce\tAdult\t73.3121\t25.1875\t0\t1\t3\t1\t3\n";
  oOut << "34.3689\t56.2073\tPaper_Birch\tAdult\t73.2251\t28.6773\t0\t0\t4\t2.8\t4\n";
  oOut << "21.4417\t64.2395\tPaper_Birch\tAdult\t73.2111\t28.6765\t1\t0\t4\t3.4\t2\n";
  oOut << "51.2634\t158.514\tWestern_Hemlock\tAdult\t73.1763\t29.7149\t1\t1\t1\t2.4\t1\n";
  oOut << "43.75\t9.82666\tSubalpine_Fir\tAdult\t73.157\t27.8396\t0\t1\t0\t1.6\t3\n";
  oOut << "44.5496\t194.128\tTrembling_Aspen\tAdult\t73.0765\t27.4925\t1\t1\t5\t1\t1\n";
  oOut << "57.074\t105.206\tAmabilis_Fir\tAdult\t73.0719\t29.713\t0\t1\t0\t4.3\t3\n";
  oOut << "197.137\t14.624\tBlack_Cottonwood\tAdult\t73.0475\t28.9296\t0\t0\t4\t7.3\t4\n";
  oOut << "94.8059\t127.271\tHybrid_Spruce\tAdult\t73.0457\t25.1562\t0\t1\t1\t9.9\t3\n";
  oOut << "36.6882\t124.536\tAmabilis_Fir\tAdult\t72.9596\t29.711\t0\t1\t0\t0.6\t3\n";
  oOut << "165.442\t145.685\tSubalpine_Fir\tAdult\t72.8882\t27.819\t0\t1\t0\t2.2\t3\n";
  oOut << "152.826\t79.187\tTrembling_Aspen\tAdult\t72.8574\t27.4742\t1\t1\t2\t10.6\t1\n";
  oOut << "59.1797\t127.026\tWestern_Hemlock\tAdult\t72.8299\t29.7086\t1\t1\t3\t12\t1\n";
  oOut << "44.6777\t98.0713\tLodgepole_Pine\tAdult\t72.7951\t29.5139\t1\t1\t5\t9.4\t1\n";
  oOut << "172.552\t12.5732\tSubalpine_Fir\tAdult\t72.7139\t27.8056\t0\t0\t0\t0.2\t4\n";
  oOut << "65.5701\t179.73\tPaper_Birch\tAdult\t72.6215\t28.6433\t1\t0\t4\t1.7\t2\n";
  oOut << "8.37402\t170.959\tHybrid_Spruce\tAdult\t72.4911\t25.0904\t0\t0\t1\t2.2\t4\n";
  oOut << "48.6267\t140.436\tTrembling_Aspen\tAdult\t72.4905\t27.4431\t1\t1\t1\t0.8\t1\n";
  oOut << "10.4248\t23.0713\tPaper_Birch\tAdult\t72.4622\t28.6342\t1\t1\t5\t3\t1\n";
  oOut << "133.362\t50.9338\tTrembling_Aspen\tAdult\t72.4124\t27.4364\t0\t0\t3\t7.4\t4\n";
  oOut << "35.0342\t84.4238\tBlack_Cottonwood\tAdult\t72.3129\t28.8936\t0\t0\t0\t1.1\t4\n";
  oOut << "23.0225\t147.473\tSubalpine_Fir\tAdult\t72.3126\t27.7742\t1\t0\t0\t2.8\t2\n";
  oOut << "70.9534\t177.576\tSubalpine_Fir\tAdult\t72.3059\t27.7737\t0\t0\t0\t7.1\t4\n";
  oOut << "178.082\t38.6414\tBlack_Cottonwood\tAdult\t72.2574\t28.8909\t0\t1\t3\t2.4\t3\n";
  oOut << "50.6165\t77.0691\tWestern_Redcedar\tAdult\t72.1301\t29.6805\t1\t1\t0\t9.3\t1\n";
  oOut << "86.6516\t113.049\tHybrid_Spruce\tAdult\t71.8594\t25.0143\t1\t0\t1\t6.5\t2\n";
  oOut << "146.545\t17.3462\tWestern_Redcedar\tAdult\t71.8576\t29.675\t1\t1\t2\t12.5\t1\n";
  oOut << "78.6255\t71.698\tSubalpine_Fir\tAdult\t71.8481\t27.7374\t0\t0\t0\t3\t4\n";
  oOut << "44.7998\t111.505\tPaper_Birch\tAdult\t71.7853\t28.5948\t1\t1\t1\t2.6\t1\n";
  oOut << "103.955\t49.1394\tWestern_Redcedar\tAdult\t71.7297\t29.6724\t0\t1\t1\t12.3\t3\n";
  oOut << "192.139\t113.525\tSubalpine_Fir\tAdult\t71.6766\t27.7236\t0\t0\t0\t1.3\t4\n";
  oOut << "125.146\t59.4299\tWestern_Hemlock\tAdult\t71.6089\t29.6853\t1\t0\t1\t4.6\t2\n";
  oOut << "125.177\t127.399\tPaper_Birch\tAdult\t71.4639\t28.5757\t0\t0\t4\t8.9\t4\n";
  oOut << "133.124\t184.064\tHybrid_Spruce\tAdult\t71.4288\t24.9618\t0\t0\t1\t4.9\t4\n";
  oOut << "69.635\t138.104\tSubalpine_Fir\tAdult\t71.3272\t27.6954\t0\t0\t0\t2.7\t4\n";
  oOut << "110.663\t104.822\tTrembling_Aspen\tAdult\t71.2793\t27.3377\t0\t1\t0\t4.3\t3\n";
  oOut << "124.872\t24.2737\tBlack_Cottonwood\tAdult\t71.2488\t28.8394\t1\t0\t0\t6.2\t2\n";
  oOut << "79.9683\t197.375\tWestern_Hemlock\tAdult\t71.0562\t29.6742\t1\t0\t2\t6.9\t2\n";
  oOut << "137.238\t197.528\tWestern_Redcedar\tAdult\t71.0455\t29.6581\t1\t1\t4\t14.1\t1\n";
  oOut << "34.4421\t105.292\tTrembling_Aspen\tAdult\t70.9167\t27.3054\t1\t1\t5\t9.5\t1\n";
  oOut << "190.619\t26.4771\tWestern_Redcedar\tAdult\t70.867\t29.6543\t0\t1\t4\t10.4\t3\n";
  oOut << "101.447\t77.1729\tPaper_Birch\tAdult\t70.8121\t28.5362\t0\t1\t3\t11.4\t3\n";
  oOut << "54.7913\t128.998\tWestern_Hemlock\tAdult\t70.7745\t29.6683\t1\t0\t0\t0.1\t2\n";
  oOut << "88.3423\t94.2505\tLodgepole_Pine\tAdult\t70.7693\t29.4555\t1\t0\t5\t6.6\t2\n";
  oOut << "89.4897\t75.9338\tPaper_Birch\tAdult\t70.7556\t28.5327\t1\t0\t3\t2.5\t2\n";
  oOut << "132.397\t84.8999\tHybrid_Spruce\tAdult\t70.7071\t24.8725\t0\t0\t5\t10.9\t4\n";
  oOut << "154.028\t186.121\tSubalpine_Fir\tAdult\t70.6509\t27.6396\t0\t0\t0\t11\t4\n";
  oOut << "15.3503\t88.5803\tPaper_Birch\tAdult\t70.5411\t28.5194\t1\t1\t2\t4.7\t1\n";
  oOut << "79.2664\t93.6707\tAmabilis_Fir\tAdult\t70.4974\t29.6625\t0\t0\t0\t0.3\t4\n";
  oOut << "75.9766\t147.662\tWestern_Hemlock\tAdult\t70.4739\t29.662\t1\t0\t3\t4.7\t2\n";
  oOut << "101.831\t167.291\tPaper_Birch\tAdult\t70.1239\t28.4933\t0\t1\t0\t7.2\t3\n";
  oOut << "129.297\t188.177\tHybrid_Spruce\tAdult\t70.0156\t24.7855\t0\t0\t2\t6.2\t4\n";
  oOut << "40.5762\t125.592\tWestern_Redcedar\tAdult\t69.8734\t29.6322\t1\t1\t0\t5.9\t1\n";
  oOut << "18.0481\t108.502\tPaper_Birch\tAdult\t69.8529\t28.476\t0\t1\t2\t0.5\t3\n";
  oOut << "168.738\t139.368\tBlack_Cottonwood\tAdult\t69.697\t28.7554\t1\t1\t1\t2.8\t1\n";
  oOut << "111.42\t152.234\tTrembling_Aspen\tAdult\t69.6097\t27.1854\t0\t1\t3\t9.1\t3\n";
  oOut << "174.286\t90.509\tLodgepole_Pine\tAdult\t69.5895\t29.4183\t0\t1\t3\t3.8\t3\n";
  oOut << "85.5774\t85.022\tAmabilis_Fir\tAdult\t69.5544\t29.6418\t0\t0\t0\t5.2\t4\n";
  oOut << "145.056\t33.1055\tAmabilis_Fir\tAdult\t69.5062\t29.6408\t0\t0\t0\t5.6\t4\n";
  oOut << "40.4724\t115.601\tBlack_Cottonwood\tAdult\t69.4885\t28.7437\t1\t1\t1\t7\t1\n";
  oOut << "171.051\t117.261\tBlack_Cottonwood\tAdult\t69.455\t28.7418\t0\t0\t4\t3.9\t4\n";
  oOut << "66.4551\t127.557\tBlack_Cottonwood\tAdult\t69.3808\t28.7376\t1\t0\t1\t4.8\t2\n";
  oOut << "156.195\t112.866\tSubalpine_Fir\tAdult\t69.3494\t27.5285\t0\t1\t0\t2.7\t3\n";
  oOut << "103.967\t105.011\tLodgepole_Pine\tAdult\t69.2117\t29.4059\t0\t1\t0\t2.4\t3\n";
  oOut << "156.653\t138.177\tTrembling_Aspen\tAdult\t69.1437\t27.1413\t1\t0\t5\t1.4\t2\n";
  oOut << "185.211\t177.795\tWestern_Hemlock\tAdult\t69.1345\t29.6322\t0\t0\t5\t7.4\t4\n";
  oOut << "63.3484\t76.7883\tTrembling_Aspen\tAdult\t69.1251\t27.1395\t1\t0\t0\t5.5\t2\n";
  oOut << "88.7085\t198.462\tLodgepole_Pine\tAdult\t69.1141\t29.4026\t1\t0\t4\t11.1\t2\n";
  oOut << "178.497\t81.9519\tAmabilis_Fir\tAdult\t69.1135\t29.6318\t0\t0\t0\t2.5\t4\n";
  oOut << "43.9331\t181.805\tWestern_Hemlock\tAdult\t69.0619\t29.6306\t1\t1\t0\t7.7\t1\n";
  oOut << "155.682\t140.912\tSubalpine_Fir\tAdult\t69.0521\t27.5024\t0\t1\t0\t5.2\t3\n";
  oOut << "103.119\t145.947\tWestern_Redcedar\tAdult\t69.0469\t29.6128\t0\t1\t5\t10.8\t3\n";
  oOut << "57.7148\t2.64893\tBlack_Cottonwood\tAdult\t68.8913\t28.7095\t1\t1\t3\t10\t1\n";
  oOut << "21.3989\t145.013\tLodgepole_Pine\tAdult\t68.8904\t29.3951\t0\t1\t5\t12.3\t3\n";
  oOut << "0.0244141\t18.6401\tBlack_Cottonwood\tAdult\t68.8135\t28.705\t0\t1\t5\t9.9\t3\n";
  oOut << "78.9795\t66.7542\tHybrid_Spruce\tAdult\t68.7817\t24.6266\t1\t0\t1\t7.1\t2\n";
  oOut << "108.612\t161.707\tAmabilis_Fir\tAdult\t68.6798\t29.6216\t0\t1\t0\t8.5\t3\n";
  oOut << "191.26\t68.5974\tSubalpine_Fir\tAdult\t68.6554\t27.4672\t0\t1\t0\t8.3\t3\n";
  oOut << "134.54\t97.0642\tWestern_Hemlock\tAdult\t68.4769\t29.6167\t0\t0\t0\t1.1\t4\n";
  oOut << "159.363\t117.859\tLodgepole_Pine\tAdult\t68.392\t29.378\t1\t0\t3\t1.7\t2\n";
  oOut << "147.827\t90.271\tBlack_Cottonwood\tAdult\t68.3124\t28.6754\t1\t0\t0\t2.8\t2\n";
  oOut << "110.846\t104.651\tWestern_Hemlock\tAdult\t68.2712\t29.6117\t0\t1\t4\t6.1\t3\n";
  oOut << "187.006\t173.682\tPaper_Birch\tAdult\t68.1628\t28.3639\t0\t1\t0\t10.5\t3\n";
  oOut << "181.885\t165.039\tPaper_Birch\tAdult\t68.125\t28.3613\t0\t0\t5\t0.8\t4\n";
  oOut << "20.5322\t41.9495\tHybrid_Spruce\tAdult\t68.107\t24.5376\t1\t0\t0\t2.2\t2\n";
  oOut << "37.616\t79.0405\tAmabilis_Fir\tAdult\t68.0954\t29.6074\t0\t1\t0\t8.3\t3\n";
  oOut << "181.128\t185.382\tHybrid_Spruce\tAdult\t68.0597\t24.5313\t0\t1\t5\t6.2\t3\n";
  oOut << "142.358\t10.8704\tHybrid_Spruce\tAdult\t68.0521\t24.5303\t0\t1\t0\t7.2\t3\n";
  oOut << "113.177\t102.356\tBlack_Cottonwood\tAdult\t68.0389\t28.659\t0\t1\t0\t10.1\t3\n";
  oOut << "124.591\t81.5063\tLodgepole_Pine\tAdult\t68.0316\t29.3653\t0\t0\t3\t6\t4\n";
  oOut << "103.748\t64.1418\tAmabilis_Fir\tAdult\t67.9742\t29.6043\t0\t1\t0\t1.6\t3\n";
  oOut << "59.2651\t163.947\tLodgepole_Pine\tAdult\t67.9419\t29.3621\t1\t1\t0\t6.2\t1\n";
  oOut << "70.7764\t85.3638\tWestern_Redcedar\tAdult\t67.8934\t29.5839\t1\t0\t5\t7.9\t2\n";
  oOut << "70.8496\t173.535\tWestern_Hemlock\tAdult\t67.8082\t29.6002\t1\t0\t1\t1.6\t2\n";
  oOut << "169.916\t139.343\tBlack_Cottonwood\tAdult\t67.7588\t28.642\t1\t1\t0\t6.3\t1\n";
  oOut << "117.273\t140.277\tSubalpine_Fir\tAdult\t67.7469\t27.3846\t0\t0\t0\t8.1\t4\n";
  oOut << "169.183\t57.1533\tBlack_Cottonwood\tAdult\t67.7124\t28.6392\t1\t1\t0\t3.8\t1\n";
  oOut << "83.8196\t168.127\tWestern_Redcedar\tAdult\t67.6575\t29.5778\t1\t0\t2\t6.6\t2\n";
  oOut << "111.493\t28.5828\tHybrid_Spruce\tAdult\t67.6199\t24.4725\t0\t1\t2\t9.6\t3\n";
  oOut << "113.843\t88.9282\tWestern_Hemlock\tAdult\t67.5839\t29.5945\t0\t1\t0\t3.4\t3\n";
  oOut << "15.1489\t191.254\tWestern_Redcedar\tAdult\t67.5153\t29.574\t0\t0\t5\t7.5\t4\n";
  oOut << "141.272\t10.0159\tWestern_Redcedar\tAdult\t67.4753\t29.5729\t0\t0\t0\t24.3\t4\n";
  oOut << "85.7483\t170.77\tWestern_Hemlock\tAdult\t67.4588\t29.5913\t1\t0\t2\t5.7\t2\n";
  oOut << "185.889\t107.874\tAmabilis_Fir\tAdult\t67.4573\t29.5913\t0\t1\t0\t1.9\t3\n";
  oOut << "93.927\t155.627\tSubalpine_Fir\tAdult\t67.4475\t27.3568\t0\t1\t0\t1.3\t3\n";
  oOut << "19.2322\t109.54\tPaper_Birch\tAdult\t67.3825\t28.3094\t0\t1\t4\t14.8\t3\n";
  oOut << "62.9272\t129.254\tLodgepole_Pine\tAdult\t67.3154\t29.3393\t1\t0\t4\t0.7\t2\n";
  oOut << "158.124\t72.4365\tBlack_Cottonwood\tAdult\t67.265\t28.6115\t1\t0\t3\t1.5\t2\n";
  oOut << "11.3342\t101.404\tHybrid_Spruce\tAdult\t67.2638\t24.4244\t1\t0\t1\t13.2\t2\n";
  oOut << "193.25\t84.3079\tWestern_Redcedar\tAdult\t67.2281\t29.5663\t0\t0\t4\t0.7\t4\n";
  oOut << "157.904\t103.687\tWestern_Hemlock\tAdult\t67.2159\t29.585\t1\t1\t5\t9.9\t1\n";
  oOut << "12.7869\t8.81348\tWestern_Redcedar\tAdult\t67.1573\t29.5644\t1\t1\t5\t8.9\t1\n";
  oOut << "111.823\t119.897\tTrembling_Aspen\tAdult\t67.1396\t26.9438\t0\t1\t1\t9.1\t3\n";
  oOut << "179.376\t100.708\tBlack_Cottonwood\tAdult\t67.0215\t28.5962\t0\t1\t0\t3.7\t3\n";
  oOut << "39.9719\t77.1362\tHybrid_Spruce\tAdult\t66.9708\t24.3845\t1\t1\t4\t10.5\t1\n";
  oOut << "169.226\t10.9009\tAmabilis_Fir\tAdult\t66.9174\t29.5771\t0\t0\t0\t1.8\t4\n";
  oOut << "125.494\t28.9612\tLodgepole_Pine\tAdult\t66.8323\t29.3212\t0\t0\t1\t0\t4\n";
  oOut << "77.9297\t85.907\tHybrid_Spruce\tAdult\t66.6638\t24.3424\t1\t0\t3\t3\t2\n";
  oOut << "178.888\t180.273\tHybrid_Spruce\tAdult\t66.6342\t24.3383\t0\t0\t4\t4.6\t4\n";
  oOut << "13.2874\t192.291\tWestern_Hemlock\tAdult\t66.6309\t29.5694\t0\t1\t1\t0.9\t3\n";
  oOut << "104.089\t9.50928\tAmabilis_Fir\tAdult\t66.5573\t29.5674\t0\t1\t0\t1.5\t3\n";
  oOut << "157.898\t150.208\tLodgepole_Pine\tAdult\t66.5469\t29.3103\t1\t0\t5\t0.6\t2\n";
  oOut << "196.808\t11.8042\tTrembling_Aspen\tAdult\t66.4471\t26.8725\t0\t1\t2\t4.5\t3\n";
  oOut << "144.916\t160.76\tAmabilis_Fir\tAdult\t66.4102\t29.5634\t1\t1\t0\t2.8\t1\n";
  oOut << "35.6018\t89.2212\tTrembling_Aspen\tAdult\t66.377\t26.8651\t1\t1\t1\t2.7\t1\n";
  oOut << "87.4329\t127.344\tAmabilis_Fir\tAdult\t66.3309\t29.5612\t0\t0\t0\t11.7\t4\n";
  oOut << "141.919\t133.331\tWestern_Hemlock\tAdult\t66.2845\t29.5599\t0\t0\t2\t1.8\t4\n";
  oOut << "152.319\t19.4397\tWestern_Redcedar\tAdult\t66.2836\t29.54\t1\t1\t2\t11.7\t1\n";
  oOut << "35.4431\t65.979\tWestern_Hemlock\tAdult\t66.225\t29.5583\t1\t1\t0\t7.5\t1\n";
  oOut << "55.4504\t126.959\tTrembling_Aspen\tAdult\t66.1102\t26.8371\t1\t1\t3\t11.7\t1\n";
  oOut << "29.9133\t106.873\tSubalpine_Fir\tAdult\t66.0065\t27.2187\t0\t0\t0\t9.9\t4\n";
  oOut << "5.71899\t144.849\tWestern_Redcedar\tAdult\t65.8121\t29.5263\t0\t0\t5\t6.7\t4\n";
  oOut << "75.2197\t128.607\tHybrid_Spruce\tAdult\t65.7352\t24.2131\t1\t0\t4\t7.7\t2\n";
  oOut << "64.4104\t197.852\tAmabilis_Fir\tAdult\t65.7321\t29.5443\t0\t0\t0\t7.7\t4\n";
  oOut << "129.028\t15.5518\tHybrid_Spruce\tAdult\t65.6329\t24.1987\t1\t0\t4\t6\t2\n";
  oOut << "40.8142\t30.3772\tLodgepole_Pine\tAdult\t65.5768\t29.2718\t1\t1\t1\t1.8\t1\n";
  oOut << "175.83\t149.908\tHybrid_Spruce\tAdult\t65.5508\t24.1871\t0\t0\t4\t1.2\t4\n";
  oOut << "83.8806\t133.972\tWestern_Redcedar\tAdult\t65.4797\t29.5164\t1\t0\t4\t5.9\t2\n";
  oOut << "157.629\t79.2419\tAmabilis_Fir\tAdult\t65.4382\t29.5358\t0\t1\t0\t2.3\t3\n";
  oOut << "72.876\t196.698\tTrembling_Aspen\tAdult\t65.3021\t26.7508\t1\t0\t3\t4.5\t2\n";
  oOut << "67.5964\t94.4275\tHybrid_Spruce\tAdult\t65.2979\t24.1512\t1\t0\t2\t10.7\t2\n";
  oOut << "168.658\t197.418\tPaper_Birch\tAdult\t65.2808\t28.1534\t1\t0\t5\t9.5\t2\n";
  oOut << "194.165\t169.69\tWestern_Redcedar\tAdult\t65.2725\t29.5101\t0\t0\t4\t10.4\t4\n";
  oOut << "19.7205\t118.402\tPaper_Birch\tAdult\t65.2399\t28.1502\t0\t1\t5\t1.5\t3\n";
  oOut << "119.104\t62.5793\tTrembling_Aspen\tAdult\t65.2374\t26.7438\t0\t0\t1\t11.2\t4\n";
  oOut << "199.982\t155.444\tPaper_Birch\tAdult\t65.1321\t28.1418\t0\t0\t2\t8.2\t4\n";
  oOut << "129.364\t27.5696\tLodgepole_Pine\tAdult\t65.1251\t29.2531\t0\t0\t2\t2.6\t4\n";
  oOut << "43.4265\t198.108\tPaper_Birch\tAdult\t65.1242\t28.1412\t1\t1\t1\t7.1\t1\n";
  oOut << "13.8733\t50.293\tTrembling_Aspen\tAdult\t65.0327\t26.7215\t0\t1\t5\t4.8\t3\n";
  oOut << "17.5354\t188.818\tTrembling_Aspen\tAdult\t64.9969\t26.7176\t0\t1\t2\t3.3\t3\n";
  oOut << "118.658\t60.8093\tTrembling_Aspen\tAdult\t64.9731\t26.715\t0\t0\t1\t0.3\t4\n";
  oOut << "174.701\t52.1912\tWestern_Redcedar\tAdult\t64.8907\t29.4983\t0\t1\t5\t14.9\t3\n";
  oOut << "172.424\t67.2119\tSubalpine_Fir\tAdult\t64.8248\t27.1001\t0\t1\t0\t1.3\t3\n";
  oOut << "102.179\t175.494\tLodgepole_Pine\tAdult\t64.5978\t29.2307\t1\t0\t0\t2.4\t2\n";
  oOut << "10.4736\t21.0083\tSubalpine_Fir\tAdult\t64.3872\t27.0549\t0\t1\t0\t0.1\t3\n";
  oOut << "167.511\t118.958\tSubalpine_Fir\tAdult\t64.2972\t27.0455\t0\t1\t0\t10.1\t3\n";
  oOut << "124.408\t23.3887\tWestern_Redcedar\tAdult\t64.2627\t29.4782\t0\t0\t4\t10.3\t4\n";
  oOut << "35.8826\t173.944\tHybrid_Spruce\tAdult\t64.238\t23.9984\t1\t1\t4\t1.2\t1\n";
  oOut << "0.744629\t126.239\tAmabilis_Fir\tAdult\t64.1409\t29.4963\t0\t0\t0\t8.2\t4\n";
  oOut << "107.605\t138.708\tTrembling_Aspen\tAdult\t64.0689\t26.6144\t0\t1\t1\t11.6\t3\n";
  oOut << "107.495\t42.4377\tPaper_Birch\tAdult\t64.0396\t28.0546\t0\t1\t2\t8\t3\n";
  oOut << "53.9246\t105.048\tPaper_Birch\tAdult\t63.9975\t28.0511\t1\t1\t4\t4.7\t1\n";
  oOut << "106.281\t156.714\tSubalpine_Fir\tAdult\t63.9706\t27.0112\t0\t1\t0\t3.2\t3\n";
  oOut << "157.532\t192.352\tHybrid_Spruce\tAdult\t63.9352\t23.954\t1\t0\t2\t5.7\t2\n";
  oOut << "41.0278\t128.68\tHybrid_Spruce\tAdult\t63.8409\t23.9401\t1\t1\t2\t0.1\t1\n";
  oOut << "30.9814\t170.563\tWestern_Redcedar\tAdult\t63.8019\t29.463\t0\t1\t2\t7.2\t3\n";
  oOut << "122.308\t159.454\tSubalpine_Fir\tAdult\t63.7747\t26.9905\t0\t0\t0\t4.1\t4\n";
  oOut << "57.6721\t156.47\tLodgepole_Pine\tAdult\t63.7732\t29.1944\t1\t1\t0\t8.6\t1\n";
  oOut << "53.772\t131.628\tWestern_Redcedar\tAdult\t63.7579\t29.4616\t1\t1\t2\t8.5\t1\n";
  oOut << "167.023\t164.008\tLodgepole_Pine\tAdult\t63.7231\t29.1921\t1\t0\t3\t0.8\t2\n";
  oOut << "97.6257\t48.3459\tWestern_Hemlock\tAdult\t63.7216\t29.4828\t0\t1\t2\t4.9\t3\n";
  oOut << "97.7234\t184.308\tSubalpine_Fir\tAdult\t63.699\t26.9824\t0\t1\t0\t1.8\t3\n";
  oOut << "160.852\t67.6025\tHybrid_Spruce\tAdult\t63.6978\t23.919\t1\t1\t5\t1.5\t1\n";
  oOut << "3.48511\t188.428\tTrembling_Aspen\tAdult\t63.6935\t26.5718\t0\t1\t2\t13.6\t3\n";
  oOut << "185.944\t168.738\tWestern_Hemlock\tAdult\t63.5855\t29.4783\t0\t1\t2\t3.8\t3\n";
  oOut << "133.795\t17.8833\tSubalpine_Fir\tAdult\t63.5184\t26.9631\t0\t0\t3\t10.3\t4\n";
  oOut << "13.3606\t77.1606\tPaper_Birch\tAdult\t63.4766\t28.008\t1\t0\t4\t3.4\t2\n";
  oOut << "104.541\t128.662\tBlack_Cottonwood\tAdult\t63.3987\t28.3476\t0\t1\t1\t7.2\t3\n";
  oOut << "163.116\t129.626\tLodgepole_Pine\tAdult\t63.2928\t29.1724\t1\t1\t5\t0.5\t1\n";
  oOut << "165.137\t80.3711\tPaper_Birch\tAdult\t63.1146\t27.9775\t1\t0\t5\t7.2\t2\n";
  oOut << "70.2759\t21.759\tWestern_Redcedar\tAdult\t63.111\t29.4394\t1\t0\t0\t8.9\t2\n";
  oOut << "89.0808\t50.47\tWestern_Hemlock\tAdult\t63.0469\t29.4603\t0\t1\t2\t9.4\t3\n";
  oOut << "123.816\t147.052\tBlack_Cottonwood\tAdult\t62.9898\t28.3169\t0\t1\t3\t4.8\t3\n";
  oOut << "10.0098\t0.476074\tPaper_Birch\tAdult\t62.9767\t27.9657\t1\t1\t1\t1.9\t1\n";
  oOut << "168.439\t151.617\tTrembling_Aspen\tAdult\t62.8882\t26.4785\t1\t1\t4\t11.9\t1\n";
  oOut << "51.9287\t131.873\tHybrid_Spruce\tAdult\t62.8839\t23.7973\t1\t1\t5\t5.5\t1\n";
  oOut << "12.2986\t141.968\tLodgepole_Pine\tAdult\t62.8226\t29.1503\t0\t1\t1\t11.4\t3\n";
  oOut << "135.498\t123.511\tTrembling_Aspen\tAdult\t62.8033\t26.4685\t0\t0\t4\t5.5\t4\n";
  oOut << "84.7595\t163.855\tSubalpine_Fir\tAdult\t62.7328\t26.8776\t0\t0\t0\t10.4\t4\n";
  oOut << "115.765\t158.661\tTrembling_Aspen\tAdult\t62.5845\t26.4427\t0\t1\t1\t5.3\t3\n";
  oOut << "55.2368\t113.629\tBlack_Cottonwood\tAdult\t62.5677\t28.2847\t1\t1\t1\t4.2\t1\n";
  oOut << "97.7234\t23.4253\tSubalpine_Fir\tAdult\t62.5418\t26.8565\t0\t1\t0\t9.3\t3\n";
  oOut << "86.9934\t79.6387\tWestern_Hemlock\tAdult\t62.5281\t29.4424\t1\t0\t5\t0.3\t2\n";
  oOut << "22.998\t47.113\tTrembling_Aspen\tAdult\t62.475\t26.4297\t1\t1\t2\t6.9\t1\n";
  oOut << "167.078\t167.23\tAmabilis_Fir\tAdult\t62.4435\t29.4394\t1\t1\t0\t11.6\t1\n";
  oOut << "138.812\t30.7678\tWestern_Redcedar\tAdult\t62.439\t29.4154\t0\t1\t4\t21.5\t3\n";
  oOut << "44.9951\t39.4775\tSubalpine_Fir\tAdult\t62.4289\t26.8439\t0\t1\t0\t9.9\t3\n";
  oOut << "34.1492\t101.831\tLodgepole_Pine\tAdult\t62.3999\t29.13\t0\t1\t1\t10.7\t3\n";
  oOut << "84.1553\t167.932\tAmabilis_Fir\tAdult\t62.3218\t29.4351\t0\t1\t0\t11\t3\n";
  oOut << "166.614\t46.875\tSubalpine_Fir\tAdult\t62.1439\t26.812\t0\t0\t0\t0.4\t4\n";
  oOut << "85.1135\t74.1882\tWestern_Redcedar\tAdult\t61.9946\t29.399\t1\t0\t5\t5.2\t2\n";
  oOut << "174.298\t121.887\tPaper_Birch\tAdult\t61.9659\t27.8775\t0\t1\t5\t4\t3\n";
  oOut << "47.1863\t38.6719\tPaper_Birch\tAdult\t61.9406\t27.8753\t1\t1\t5\t3.6\t1\n";
  oOut << "55.835\t126.947\tAmabilis_Fir\tAdult\t61.9293\t29.421\t0\t1\t0\t8\t3\n";
  oOut << "136.017\t164.508\tHybrid_Spruce\tAdult\t61.9275\t23.6513\t0\t0\t4\t10.6\t4\n";
  oOut << "176.16\t147.064\tWestern_Redcedar\tAdult\t61.8173\t29.3923\t0\t1\t4\t0\t3\n";
  oOut << "173.944\t4.42505\tPaper_Birch\tAdult\t61.8021\t27.8629\t0\t1\t2\t3.1\t3\n";
  oOut << "26.9531\t155.902\tPaper_Birch\tAdult\t61.7078\t27.8544\t1\t1\t5\t8\t1\n";
  oOut << "131.5\t158.453\tBlack_Cottonwood\tAdult\t61.6782\t28.2146\t0\t0\t1\t2\t4\n";
  oOut << "24.4568\t150.647\tAmabilis_Fir\tAdult\t61.6232\t29.4097\t0\t1\t0\t9\t3\n";
  oOut << "20.0806\t81.2073\tSubalpine_Fir\tAdult\t61.5433\t26.7436\t0\t1\t0\t0.8\t3\n";
  oOut << "51.947\t62.3535\tWestern_Hemlock\tAdult\t61.5414\t29.4066\t1\t1\t0\t5.7\t1\n";
  oOut << "30.4688\t124.86\tPaper_Birch\tAdult\t61.4648\t27.8324\t1\t1\t5\t2.2\t1\n";
  oOut << "67.9443\t122.455\tBlack_Cottonwood\tAdult\t61.4359\t28.195\t1\t0\t5\t0.7\t2\n";
  oOut << "99.6216\t13.5559\tWestern_Hemlock\tAdult\t61.4172\t29.402\t0\t1\t2\t11.5\t3\n";
  oOut << "21.0205\t93.5608\tSubalpine_Fir\tAdult\t61.3165\t26.7174\t0\t0\t0\t4.9\t4\n";
  oOut << "106.72\t161.517\tTrembling_Aspen\tAdult\t61.196\t26.2742\t0\t1\t3\t2.2\t3\n";
  oOut << "39.2761\t141.229\tWestern_Hemlock\tAdult\t61.1823\t29.3931\t1\t0\t5\t7.9\t2\n";
  oOut << "48.1873\t91.0522\tLodgepole_Pine\tAdult\t61.1679\t29.0678\t1\t1\t0\t8\t1\n";
  oOut << "10.9436\t41.5161\tAmabilis_Fir\tAdult\t61.0507\t29.388\t0\t0\t0\t1.9\t4\n";
  oOut << "69.2688\t27.8687\tPaper_Birch\tAdult\t61.0422\t27.7936\t1\t0\t5\t4.9\t2\n";
  oOut << "134.32\t9.79614\tBlack_Cottonwood\tAdult\t60.9674\t28.1566\t0\t0\t2\t6.2\t4\n";
  oOut << "74.9634\t93.0603\tWestern_Hemlock\tAdult\t60.8459\t29.3801\t0\t0\t1\t5.4\t4\n";
  oOut << "67.6147\t70.4224\tBlack_Cottonwood\tAdult\t60.7648\t28.1397\t1\t0\t5\t1.4\t2\n";
  oOut << "30.8899\t158.6\tLodgepole_Pine\tAdult\t60.6219\t29.0389\t0\t0\t4\t4.9\t4\n";
  oOut << "97.2717\t107.532\tTrembling_Aspen\tAdult\t60.6042\t26.2\t0\t1\t0\t3.1\t3\n";
  oOut << "167.963\t39.3738\tAmabilis_Fir\tAdult\t60.3833\t29.3617\t0\t0\t0\t11.5\t4\n";
  oOut << "19.6045\t38.8428\tPaper_Birch\tAdult\t60.3818\t27.7315\t0\t0\t2\t0.9\t4\n";
  oOut << "163.885\t194.122\tWestern_Hemlock\tAdult\t60.2737\t29.3573\t1\t1\t2\t1.5\t1\n";
  oOut << "89.1541\t186.389\tSubalpine_Fir\tAdult\t60.2203\t26.5878\t0\t0\t3\t5.3\t4\n";
  oOut << "33.3496\t99.0295\tHybrid_Spruce\tAdult\t60.2078\t23.38\t1\t0\t5\t4.1\t2\n";
  oOut << "84.3933\t88.1226\tBlack_Cottonwood\tAdult\t60.0977\t28.083\t1\t0\t4\t2.5\t2\n";
  oOut << "4.47388\t189.648\tAmabilis_Fir\tAdult\t59.92\t29.3428\t0\t1\t0\t2.7\t3\n";
  oOut << "34.3628\t194.751\tHybrid_Spruce\tAdult\t59.9167\t23.3329\t1\t1\t2\t6.5\t1\n";
  oOut << "114.478\t158.722\tSubalpine_Fir\tAdult\t59.8831\t26.5469\t0\t1\t0\t2\t3\n";
  oOut << "119.775\t139.795\tTrembling_Aspen\tAdult\t59.8383\t26.1017\t1\t0\t4\t1.9\t2\n";
  oOut << "186.261\t138.251\tLodgepole_Pine\tAdult\t59.8105\t28.9942\t0\t1\t3\t10.3\t3\n";
  oOut << "39.0076\t169.196\tSubalpine_Fir\tAdult\t59.7781\t26.534\t0\t1\t0\t12\t3\n";
  oOut << "3.96118\t153.894\tWestern_Redcedar\tAdult\t59.7031\t29.3067\t0\t1\t5\t8.6\t3\n";
  oOut << "78.8635\t162.329\tWestern_Hemlock\tAdult\t59.6997\t29.3336\t1\t0\t0\t8.8\t2\n";
  oOut << "5.3772\t173.944\tBlack_Cottonwood\tAdult\t59.5526\t28.0354\t1\t0\t2\t0.9\t2\n";
  oOut << "63.7024\t168.445\tAmabilis_Fir\tAdult\t59.5383\t29.3268\t0\t0\t0\t9.4\t4\n";
  oOut << "122.247\t4.82178\tPaper_Birch\tAdult\t59.527\t27.6486\t0\t0\t2\t2.3\t4\n";
  oOut << "146.021\t33.9355\tBlack_Cottonwood\tAdult\t59.4388\t28.0253\t1\t0\t5\t4.9\t2\n";
  oOut << "33.5327\t196.79\tTrembling_Aspen\tAdult\t59.407\t26.0452\t0\t0\t2\t2.1\t4\n";
  oOut << "152.338\t65.1672\tBlack_Cottonwood\tAdult\t59.3811\t28.0202\t1\t1\t0\t0.9\t1\n";
  oOut << "136.157\t80.6274\tWestern_Hemlock\tAdult\t59.1907\t29.3119\t0\t1\t3\t0.2\t3\n";
  oOut << "90.5518\t58.6426\tWestern_Hemlock\tAdult\t59.1797\t29.3114\t1\t1\t1\t6.6\t1\n";
  oOut << "169.788\t113.586\tPaper_Birch\tAdult\t59.0573\t27.6017\t1\t0\t2\t10.2\t2\n";
  oOut << "170.801\t153.412\tHybrid_Spruce\tAdult\t59.025\t23.1867\t1\t1\t1\t10.6\t1\n";
  oOut << "85.4614\t185.303\tWestern_Hemlock\tAdult\t58.9871\t29.303\t1\t0\t3\t4.8\t2\n";
  oOut << "128.552\t38.5864\tHybrid_Spruce\tAdult\t58.9499\t23.1742\t0\t0\t2\t4.6\t4\n";
  oOut << "105.005\t0.415039\tWestern_Redcedar\tAdult\t58.8989\t29.2711\t0\t1\t4\t23.1\t3\n";
  oOut << "145.74\t72.1069\tBlack_Cottonwood\tAdult\t58.8098\t27.9686\t1\t1\t3\t7\t1\n";
  oOut << "177.942\t79.1016\tWestern_Redcedar\tAdult\t58.6774\t29.261\t0\t0\t1\t2.4\t4\n";
  oOut << "58.2031\t179.614\tLodgepole_Pine\tAdult\t58.6664\t28.9277\t1\t1\t1\t10.2\t1\n";
  oOut << "166.919\t13.9343\tPaper_Birch\tAdult\t58.4793\t27.5428\t1\t1\t4\t1.3\t1\n";
  oOut << "60.4797\t160.797\tWestern_Hemlock\tAdult\t58.4607\t29.2795\t1\t1\t5\t12\t1\n";
  oOut << "79.0039\t171.674\tLodgepole_Pine\tAdult\t58.4454\t28.9143\t1\t0\t4\t8.7\t2\n";
  oOut << "134.802\t41.7236\tWestern_Redcedar\tAdult\t58.4354\t29.2497\t1\t1\t1\t22.6\t1\n";
  oOut << "191.681\t149.353\tAmabilis_Fir\tAdult\t58.3801\t29.2759\t1\t0\t0\t2.7\t2\n";
  oOut << "67.9504\t186.249\tPaper_Birch\tAdult\t58.2043\t27.5143\t1\t0\t1\t7.1\t2\n";
  oOut << "52.8687\t18.2678\tBlack_Cottonwood\tAdult\t58.0887\t27.9016\t1\t1\t2\t2.4\t1\n";
  oOut << "26.8005\t78.6072\tBlack_Cottonwood\tAdult\t58.0719\t27.9\t0\t1\t4\t5\t3\n";
  oOut << "26.2939\t84.5276\tAmabilis_Fir\tAdult\t58.0508\t29.2607\t0\t0\t0\t8.7\t4\n";
  oOut << "36.5784\t103.125\tHybrid_Spruce\tAdult\t58.0145\t23.0171\t1\t1\t5\t2.7\t1\n";
  oOut << "86.322\t11.4441\tPaper_Birch\tAdult\t57.9987\t27.4927\t1\t0\t2\t4.4\t2\n";
  oOut << "71.8811\t117.328\tBlack_Cottonwood\tAdult\t57.8305\t27.8771\t1\t0\t0\t5.3\t2\n";
  oOut << "140.668\t136.847\tPaper_Birch\tAdult\t57.818\t27.4736\t0\t0\t1\t5.1\t4\n";
  oOut << "160.223\t114.789\tSubalpine_Fir\tAdult\t57.8174\t26.2854\t0\t1\t0\t7\t3\n";
  oOut << "89.5264\t65.1001\tTrembling_Aspen\tAdult\t57.7863\t25.8257\t1\t0\t4\t4\t2\n";
  oOut << "142.871\t31.7261\tBlack_Cottonwood\tAdult\t57.7597\t27.8703\t0\t0\t5\t1.4\t4\n";
  oOut << "94.5679\t43.811\tHybrid_Spruce\tAdult\t57.7402\t22.9703\t0\t1\t1\t9.8\t3\n";
  oOut << "99.4263\t46.8872\tWestern_Redcedar\tAdult\t57.7182\t29.2154\t1\t0\t2\t20.4\t2\n";
  oOut << "151.477\t111.267\tLodgepole_Pine\tAdult\t57.7094\t28.8686\t1\t1\t2\t5.8\t1\n";
  oOut << "101.471\t25.2258\tWestern_Hemlock\tAdult\t57.4838\t29.2338\t0\t1\t5\t6.7\t3\n";
  oOut << "99.7314\t21.3623\tBlack_Cottonwood\tAdult\t57.3572\t27.8314\t0\t1\t1\t11.5\t3\n";
  oOut << "93.3777\t34.7412\tBlack_Cottonwood\tAdult\t57.3093\t27.8267\t0\t1\t4\t0.5\t3\n";
  oOut << "195.209\t70.3125\tPaper_Birch\tAdult\t57.2473\t27.4123\t0\t0\t5\t3.3\t4\n";
  oOut << "192.493\t177.795\tBlack_Cottonwood\tAdult\t57.1655\t27.8126\t0\t0\t1\t1.2\t4\n";
  oOut << "174.097\t111.536\tPaper_Birch\tAdult\t57.1103\t27.3974\t0\t1\t0\t11.9\t3\n";
  oOut << "189.679\t53.5522\tTrembling_Aspen\tAdult\t57.0847\t25.7269\t0\t0\t3\t10.9\t4\n";
  oOut << "149.902\t158.234\tLodgepole_Pine\tAdult\t57.074\t28.8277\t1\t0\t3\t0.5\t2\n";
  oOut << "147.797\t173.785\tLodgepole_Pine\tAdult\t56.9458\t28.8192\t1\t1\t2\t10.1\t1\n";
  oOut << "45.9412\t151.935\tWestern_Hemlock\tAdult\t56.9217\t29.2062\t1\t1\t3\t5.3\t1\n";
  oOut << "129.846\t120.319\tLodgepole_Pine\tAdult\t56.9186\t28.8174\t0\t0\t1\t4.5\t4\n";
  oOut << "16.5405\t90.6494\tLodgepole_Pine\tAdult\t56.8857\t28.8152\t0\t0\t3\t14.1\t4\n";
  oOut << "153.674\t165.802\tLodgepole_Pine\tAdult\t56.8472\t28.8127\t1\t0\t1\t10\t2\n";
  oOut << "87.7808\t189.441\tAmabilis_Fir\tAdult\t56.8195\t29.2011\t0\t0\t0\t4.1\t4\n";
  oOut << "153.381\t46.9849\tTrembling_Aspen\tAdult\t56.7966\t25.6857\t1\t1\t3\t3\t1\n";
  oOut << "116.058\t83.8013\tAmabilis_Fir\tAdult\t56.6986\t29.195\t0\t1\t0\t8.6\t3\n";
  oOut << "146.741\t160.51\tAmabilis_Fir\tAdult\t56.68\t29.194\t1\t1\t0\t10.4\t1\n";
  oOut << "124.805\t149.908\tWestern_Redcedar\tAdult\t56.6379\t29.1608\t0\t0\t2\t14.5\t4\n";
  oOut << "166.235\t62.6831\tSubalpine_Fir\tAdult\t56.6229\t26.1253\t0\t0\t5\t0.6\t4\n";
  oOut << "70.343\t75.3845\tTrembling_Aspen\tAdult\t56.546\t25.6495\t1\t0\t0\t12\t2\n";
  oOut << "112.994\t69.043\tTrembling_Aspen\tAdult\t56.5231\t25.6462\t0\t0\t2\t9\t4\n";
  oOut << "91.449\t6.62231\tPaper_Birch\tAdult\t56.5002\t27.3298\t1\t1\t1\t11.2\t1\n";
  oOut << "104.352\t93.1213\tLodgepole_Pine\tAdult\t56.4578\t28.7865\t0\t1\t5\t6.4\t3\n";
  oOut << "19.3359\t27.6611\tHybrid_Spruce\tAdult\t56.33\t22.7249\t1\t0\t4\t11.2\t2\n";
  oOut << "56.8909\t153.015\tHybrid_Spruce\tAdult\t56.2457\t22.71\t1\t1\t2\t11.1\t1\n";
  oOut << "101.062\t159.46\tAmabilis_Fir\tAdult\t56.1948\t29.169\t0\t0\t0\t8.1\t4\n";
  oOut << "103.735\t49.6948\tTrembling_Aspen\tAdult\t56.1749\t25.5954\t0\t1\t2\t4.3\t3\n";
  oOut << "172.284\t196.6\tWestern_Redcedar\tAdult\t55.9174\t29.1222\t0\t0\t3\t14.3\t4\n";
  oOut << "60.3821\t143.17\tAmabilis_Fir\tAdult\t55.8887\t29.1528\t0\t1\t0\t5.1\t3\n";
  oOut << "193.744\t79.6204\tSubalpine_Fir\tAdult\t55.8405\t26.0166\t0\t0\t0\t0.7\t4\n";
  oOut << "196.606\t99.8108\tWestern_Redcedar\tAdult\t55.8298\t29.1174\t0\t1\t4\t2.9\t3\n";
  oOut << "181.342\t42.0959\tHybrid_Spruce\tAdult\t55.6598\t22.6053\t0\t1\t4\t4.3\t3\n";
  oOut << "80.8716\t47.1497\tSubalpine_Fir\tAdult\t55.6409\t25.9885\t0\t0\t0\t10.6\t4\n";
  oOut << "157.068\t167.993\tTrembling_Aspen\tAdult\t55.6335\t25.5152\t1\t0\t4\t7.1\t2\n";
  oOut << "35.5408\t108.008\tHybrid_Spruce\tAdult\t55.5896\t22.5926\t1\t1\t5\t1.8\t1\n";
  oOut << "126.819\t133.917\tSubalpine_Fir\tAdult\t55.5777\t25.9795\t0\t0\t0\t10.3\t4\n";
  oOut << "151.941\t73.4802\tAmabilis_Fir\tAdult\t55.4453\t29.1288\t0\t0\t0\t11.4\t4\n";
  oOut << "114.056\t73.7549\tLodgepole_Pine\tAdult\t55.3677\t28.7101\t0\t1\t4\t8.6\t3\n";
  oOut << "149.902\t23.1445\tWestern_Redcedar\tAdult\t55.3406\t29.0901\t1\t1\t2\t21.8\t1\n";
  oOut << "31.2378\t185.699\tBlack_Cottonwood\tAdult\t55.3168\t27.6229\t1\t1\t3\t12\t1\n";
  oOut << "59.9121\t43.5486\tLodgepole_Pine\tAdult\t55.2185\t28.6993\t1\t1\t0\t8.5\t1\n";
  oOut << "62.323\t78.0151\tAmabilis_Fir\tAdult\t55.1169\t29.1106\t0\t0\t0\t4.7\t4\n";
  oOut << "126.721\t27.9663\tPaper_Birch\tAdult\t55.1169\t27.1701\t0\t0\t1\t6.6\t4\n";
  oOut << "139.978\t34.3323\tLodgepole_Pine\tAdult\t55.0888\t28.6898\t0\t0\t0\t6.2\t4\n";
  oOut << "79.6753\t55.2795\tLodgepole_Pine\tAdult\t55.0473\t28.6868\t1\t0\t1\t3.9\t2\n";
  oOut << "36.7615\t81.1768\tTrembling_Aspen\tAdult\t55.0162\t25.4219\t1\t1\t2\t7.9\t1\n";
  oOut << "84.9426\t167.639\tSubalpine_Fir\tAdult\t54.9777\t25.8934\t0\t0\t0\t4.3\t4\n";
  oOut << "8.1665\t28.2959\tWestern_Redcedar\tAdult\t54.8712\t29.0631\t0\t1\t4\t8.7\t3\n";
  oOut << "138.806\t145.758\tBlack_Cottonwood\tAdult\t54.8535\t27.5728\t0\t1\t0\t3.4\t3\n";
  oOut << "1.97754\t56.6833\tWestern_Hemlock\tAdult\t54.7855\t29.0918\t1\t1\t2\t3.7\t1\n";
  oOut << "116.492\t99.6582\tPaper_Birch\tAdult\t54.7275\t27.1234\t1\t0\t1\t4.1\t2\n";
  oOut << "144.971\t132.629\tTrembling_Aspen\tAdult\t54.6268\t25.3621\t0\t1\t5\t8.5\t3\n";
  oOut << "16.4246\t177.063\tPaper_Birch\tAdult\t54.6234\t27.1108\t0\t0\t5\t11.7\t4\n";
  oOut << "117.383\t74.0356\tLodgepole_Pine\tAdult\t54.4992\t28.6458\t0\t0\t5\t0.7\t4\n";
  oOut << "33.9539\t17.0532\tBlack_Cottonwood\tAdult\t54.491\t27.5329\t0\t1\t2\t1.8\t3\n";
  oOut << "165.527\t38.2446\tAmabilis_Fir\tAdult\t54.4476\t29.0723\t0\t0\t0\t0.1\t4\n";
  oOut << "172.131\t37.9883\tSubalpine_Fir\tAdult\t54.4449\t25.8153\t0\t0\t0\t7.1\t4\n";
  oOut << "44.7876\t6.65283\tAmabilis_Fir\tAdult\t54.4189\t29.0706\t0\t1\t0\t1.6\t3\n";
  oOut << "70.6421\t82.4768\tWestern_Hemlock\tAdult\t54.3875\t29.0688\t1\t0\t1\t2.6\t2\n";
  oOut << "192.285\t177.661\tHybrid_Spruce\tAdult\t54.3536\t22.3665\t0\t0\t5\t3.9\t4\n";
  oOut << "120.184\t138.959\tHybrid_Spruce\tAdult\t54.3503\t22.3659\t0\t0\t1\t8.6\t4\n";
  oOut << "64.032\t191.76\tLodgepole_Pine\tAdult\t54.3472\t28.6342\t1\t0\t5\t4.3\t2\n";
  oOut << "137.793\t139.166\tSubalpine_Fir\tAdult\t54.2325\t25.7838\t0\t1\t0\t8.7\t3\n";
  oOut << "51.2451\t191.772\tAmabilis_Fir\tAdult\t54.1776\t29.0564\t0\t1\t0\t2.3\t3\n";
  oOut << "107.581\t115.912\tHybrid_Spruce\tAdult\t54.104\t22.32\t0\t1\t4\t2.8\t3\n";
  oOut << "106.873\t26.1108\tWestern_Hemlock\tAdult\t54.0695\t29.0499\t0\t1\t2\t0.3\t3\n";
  oOut << "16.0217\t181.976\tAmabilis_Fir\tAdult\t54.0039\t29.046\t0\t1\t0\t1.3\t3\n";
  oOut << "13.9648\t90.4175\tPaper_Birch\tAdult\t53.9594\t27.0291\t0\t1\t1\t14.5\t3\n";
  oOut << "38.7085\t109.65\tHybrid_Spruce\tAdult\t53.9532\t22.2917\t1\t1\t5\t3\t1\n";
  oOut << "20.1904\t194.47\tWestern_Hemlock\tAdult\t53.8431\t29.0363\t0\t0\t3\t14.4\t4\n";
  oOut << "94.8364\t156.635\tPaper_Birch\tAdult\t53.7976\t27.0089\t0\t0\t0\t4.4\t4\n";
  oOut << "21.1731\t163.885\tWestern_Redcedar\tAdult\t53.7296\t28.994\t1\t0\t3\t9.4\t2\n";
  oOut << "124.365\t169.507\tAmabilis_Fir\tAdult\t53.718\t29.0287\t0\t1\t0\t3.1\t3\n";
  oOut << "15.2405\t55.8533\tSubalpine_Fir\tAdult\t53.7085\t25.705\t0\t0\t0\t10.1\t4\n";
  oOut << "163.263\t96.637\tTrembling_Aspen\tAdult\t53.6926\t25.2154\t1\t0\t4\t11\t2\n";
  oOut << "30.6702\t74.1028\tLodgepole_Pine\tAdult\t53.6279\t28.5781\t0\t0\t2\t2.9\t4\n";
  oOut << "7.85522\t15.8752\tTrembling_Aspen\tAdult\t53.6151\t25.203\t1\t1\t1\t1.3\t1\n";
  oOut << "169.067\t93.3716\tTrembling_Aspen\tAdult\t53.6044\t25.2013\t1\t0\t4\t3\t2\n";
  oOut << "183.734\t86.7798\tPaper_Birch\tAdult\t53.5681\t26.9799\t0\t1\t4\t11.1\t3\n";
  oOut << "176.636\t14.502\tHybrid_Spruce\tAdult\t53.5507\t22.2159\t0\t0\t1\t10.3\t4\n";
  oOut << "69.043\t4.73022\tWestern_Hemlock\tAdult\t53.4637\t29.013\t1\t0\t1\t8.5\t2\n";
  oOut << "69.7815\t193.97\tBlack_Cottonwood\tAdult\t53.4381\t27.4132\t1\t0\t3\t5.4\t2\n";
  oOut << "30.2979\t178.51\tSubalpine_Fir\tAdult\t53.3728\t25.6537\t0\t1\t0\t0.7\t3\n";
  oOut << "86.6577\t181.042\tHybrid_Spruce\tAdult\t53.0917\t22.1285\t1\t0\t0\t3\t2\n";
  oOut << "149.048\t16.4062\tSubalpine_Fir\tAdult\t53.0884\t25.6098\t0\t1\t0\t11.3\t3\n";
  oOut << "187.305\t1.47095\tTrembling_Aspen\tAdult\t53.0481\t25.1115\t0\t1\t3\t5.6\t3\n";
  oOut << "138.403\t71.0632\tAmabilis_Fir\tAdult\t53.0249\t28.9853\t0\t1\t0\t7.1\t3\n";
  oOut << "27.2583\t175.806\tSubalpine_Fir\tAdult\t52.9846\t25.5937\t0\t1\t0\t3.1\t3\n";
  oOut << "191.797\t61.3586\tHybrid_Spruce\tAdult\t52.981\t22.1072\t0\t1\t5\t6.2\t3\n";
  oOut << "29.4006\t159.54\tSubalpine_Fir\tAdult\t52.9327\t25.5856\t0\t1\t0\t1\t3\n";
  oOut << "38.1836\t126.416\tTrembling_Aspen\tAdult\t52.8085\t25.0723\t1\t1\t1\t4.4\t1\n";
  oOut << "191.241\t78.6011\tAmabilis_Fir\tAdult\t52.8055\t28.9712\t0\t0\t0\t9.8\t4\n";
  oOut << "145.435\t139.465\tTrembling_Aspen\tAdult\t52.8021\t25.0713\t1\t0\t1\t6.1\t2\n";
  oOut << "11.5845\t143.164\tHybrid_Spruce\tAdult\t52.6022\t22.0341\t0\t1\t0\t13.3\t3\n";
  oOut << "73.3887\t91.3879\tTrembling_Aspen\tAdult\t52.5479\t25.0293\t1\t0\t4\t7.6\t2\n";
  oOut << "83.0627\t75.7141\tSubalpine_Fir\tAdult\t52.5345\t25.5231\t0\t0\t0\t3.8\t4\n";
  oOut << "143.164\t196.24\tWestern_Hemlock\tAdult\t52.4643\t28.9488\t0\t1\t5\t10.8\t3\n";
  oOut << "102.051\t109.497\tPaper_Birch\tAdult\t52.4631\t26.8364\t1\t0\t1\t10.5\t2\n";
  oOut << "103.9\t132.855\tPaper_Birch\tAdult\t52.3502\t26.8214\t0\t1\t0\t7.5\t3\n";
  oOut << "13.7268\t27.3499\tHybrid_Spruce\tAdult\t52.3059\t21.9765\t1\t0\t0\t2.1\t2\n";
  oOut << "21.1365\t139.081\tWestern_Hemlock\tAdult\t52.1997\t28.9312\t1\t0\t1\t1.4\t2\n";
  oOut << "187.262\t125.415\tSubalpine_Fir\tAdult\t52.0773\t25.4502\t0\t0\t0\t10.8\t4\n";
  oOut << "164.343\t142.999\tWestern_Redcedar\tAdult\t52.0206\t28.8809\t1\t0\t3\t0.9\t2\n";
  oOut << "116.351\t5.57861\tLodgepole_Pine\tAdult\t52.0169\t28.4439\t0\t0\t0\t9.7\t4\n";
  oOut << "2.47803\t178.595\tWestern_Redcedar\tAdult\t51.9742\t28.8776\t1\t0\t3\t9.7\t2\n";
  oOut << "120.129\t189.117\tWestern_Hemlock\tAdult\t51.9055\t28.9112\t0\t0\t0\t2.6\t4\n";
  oOut << "174.408\t168.988\tWestern_Redcedar\tAdult\t51.7786\t28.8639\t0\t0\t4\t12.2\t4\n";
  oOut << "161.804\t163.324\tSubalpine_Fir\tAdult\t51.702\t25.3894\t0\t1\t0\t8.3\t3\n";
  oOut << "9.5459\t114.655\tWestern_Redcedar\tAdult\t51.6443\t28.8543\t0\t0\t3\t6.3\t4\n";
  oOut << "197.29\t105.829\tWestern_Hemlock\tAdult\t51.5683\t28.8878\t0\t0\t0\t0.7\t4\n";
  oOut << "81.4087\t135.193\tPaper_Birch\tAdult\t51.5662\t26.715\t0\t1\t3\t6\t3\n";
  oOut << "151.129\t131.903\tWestern_Redcedar\tAdult\t51.4929\t28.8435\t1\t1\t5\t21.9\t1\n";
  oOut << "35.321\t140.399\tLodgepole_Pine\tAdult\t51.4484\t28.3935\t0\t1\t5\t10.8\t3\n";
  oOut << "161.926\t5.58472\tAmabilis_Fir\tAdult\t51.4377\t28.8786\t0\t0\t0\t0.5\t4\n";
  oOut << "149.463\t151.44\tAmabilis_Fir\tAdult\t51.4249\t28.8777\t1\t1\t0\t4.6\t1\n";
  oOut << "69.6045\t173.669\tWestern_Hemlock\tAdult\t51.3788\t28.8744\t1\t0\t4\t8.3\t2\n";
  oOut << "50.7507\t40.0879\tSubalpine_Fir\tAdult\t51.3217\t25.3271\t0\t1\t0\t9.9\t3\n";
  oOut << "190.161\t142.224\tWestern_Redcedar\tAdult\t51.2299\t28.8243\t0\t1\t1\t1.7\t3\n";
  oOut << "8.38013\t193.188\tTrembling_Aspen\tAdult\t51.1322\t24.7891\t1\t1\t0\t0.4\t1\n";
  oOut << "62.2925\t19.6533\tHybrid_Spruce\tAdult\t51.1264\t21.7429\t1\t0\t4\t11.8\t2\n";
  oOut << "152.051\t23.7366\tSubalpine_Fir\tAdult\t51.0214\t25.2772\t0\t1\t0\t4.8\t3\n";
  oOut << "7.2937\t82.8491\tWestern_Redcedar\tAdult\t51.0059\t28.8078\t1\t0\t2\t5.1\t2\n";
  oOut << "177.277\t155.872\tBlack_Cottonwood\tAdult\t51.0059\t27.1139\t0\t1\t1\t1.4\t3\n";
  oOut << "152.704\t20.4834\tWestern_Redcedar\tAdult\t50.9662\t28.8049\t1\t0\t0\t10.9\t2\n";
  oOut << "164.618\t6.66504\tTrembling_Aspen\tAdult\t50.9534\t24.758\t1\t1\t3\t5.3\t1\n";
  oOut << "72.1252\t38.3667\tBlack_Cottonwood\tAdult\t50.9372\t27.105\t1\t0\t0\t7.9\t2\n";
  oOut << "133.582\t170.325\tWestern_Redcedar\tAdult\t50.9219\t28.8016\t0\t0\t5\t22.5\t4\n";
  oOut << "18.2556\t32.5623\tWestern_Hemlock\tAdult\t50.9213\t28.8415\t1\t0\t4\t2\t2\n";
  oOut << "31.0974\t74.9023\tPaper_Birch\tAdult\t50.864\t26.6166\t0\t1\t1\t4.5\t3\n";
  oOut << "6.88477\t100.94\tWestern_Hemlock\tAdult\t50.7898\t28.8319\t1\t0\t4\t4.2\t2\n";
  oOut << "103.07\t197.333\tWestern_Hemlock\tAdult\t50.7736\t28.8307\t0\t1\t3\t8.2\t3\n";
  oOut << "8.42285\t22.8088\tBlack_Cottonwood\tAdult\t50.7578\t27.0815\t0\t1\t0\t4.8\t3\n";
  oOut << "6.90308\t164.758\tBlack_Cottonwood\tAdult\t50.6992\t27.0738\t1\t1\t1\t13.6\t1\n";
  oOut << "111.066\t157.922\tBlack_Cottonwood\tAdult\t50.6357\t27.0655\t0\t1\t5\t1.5\t3\n";
  oOut << "107.703\t69.2688\tLodgepole_Pine\tAdult\t50.4846\t28.3044\t0\t1\t3\t11.9\t3\n";
  oOut << "166.553\t193.732\tPaper_Birch\tAdult\t50.2228\t26.5243\t1\t0\t0\t0.4\t2\n";
  oOut << "54.5044\t85.0464\tHybrid_Spruce\tAdult\t50.1688\t21.5482\t1\t1\t2\t0.9\t1\n";
  oOut << "118.536\t175.97\tBlack_Cottonwood\tAdult\t49.8904\t26.9654\t0\t0\t1\t0\t4\n";
  oOut << "65.3259\t42.749\tBlack_Cottonwood\tAdult\t49.8642\t26.9618\t1\t0\t1\t3.4\t2\n";
  oOut << "59.6069\t123.224\tAmabilis_Fir\tAdult\t49.8639\t28.7617\t0\t1\t0\t7.5\t3\n";
  oOut << "76.8066\t51.9287\tTrembling_Aspen\tAdult\t49.8593\t24.5633\t1\t0\t1\t4.2\t2\n";
  oOut << "87.8052\t118.939\tWestern_Redcedar\tAdult\t49.8526\t28.719\t1\t0\t3\t10.8\t2\n";
  oOut << "8.11157\t194.94\tBlack_Cottonwood\tAdult\t49.8187\t26.9556\t1\t0\t0\t14.2\t2\n";
  oOut << "119.47\t151.465\tWestern_Hemlock\tAdult\t49.7733\t28.7546\t0\t0\t5\t1.8\t4\n";
  oOut << "128.925\t143.256\tWestern_Hemlock\tAdult\t49.7015\t28.749\t1\t0\t4\t7.1\t2\n";
  oOut << "87.6953\t81.134\tLodgepole_Pine\tAdult\t49.6982\t28.2281\t0\t1\t2\t9.1\t3\n";
  oOut << "68.4326\t168.573\tSubalpine_Fir\tAdult\t49.6194\t25.0374\t0\t1\t0\t11.7\t3\n";
  oOut << "170.679\t80.4016\tLodgepole_Pine\tAdult\t49.603\t28.2186\t1\t1\t4\t4.5\t1\n";
  oOut << "150.024\t12.9395\tPaper_Birch\tAdult\t49.5807\t26.4293\t1\t1\t2\t10.2\t1\n";
  oOut << "126.343\t198.877\tWestern_Redcedar\tAdult\t49.57\t28.6962\t0\t0\t0\t20.5\t4\n";
  oOut << "117.029\t63.4033\tTrembling_Aspen\tAdult\t49.5215\t24.5017\t0\t0\t3\t9.7\t4\n";
  oOut << "24.9451\t121.228\tTrembling_Aspen\tAdult\t49.3976\t24.479\t0\t1\t4\t10\t3\n";
  oOut << "30.603\t65.4236\tAmabilis_Fir\tAdult\t49.375\t28.723\t0\t1\t0\t6.4\t3\n";
  oOut << "130.353\t1.96533\tAmabilis_Fir\tAdult\t49.3567\t28.7215\t0\t0\t0\t9.2\t4\n";
  oOut << "73.6694\t82.605\tPaper_Birch\tAdult\t49.3393\t26.3929\t1\t0\t4\t2.1\t2\n";
  oOut << "78.2227\t190.918\tWestern_Redcedar\tAdult\t49.2001\t28.6658\t1\t0\t0\t7.2\t2\n";
  oOut << "165.485\t143.365\tAmabilis_Fir\tAdult\t49.0317\t28.6951\t1\t0\t0\t4.3\t2\n";
  oOut << "72.406\t131.665\tWestern_Redcedar\tAdult\t48.9996\t28.649\t1\t0\t3\t5.7\t2\n";
  oOut << "57.5378\t115.991\tWestern_Redcedar\tAdult\t48.9877\t28.648\t1\t1\t3\t8.7\t1\n";
  oOut << "91.4368\t166.034\tLodgepole_Pine\tAdult\t48.9731\t28.1547\t0\t1\t4\t4.7\t3\n";
  oOut << "95.1111\t145.312\tSubalpine_Fir\tAdult\t48.9581\t24.9201\t0\t1\t0\t3.5\t3\n";
  oOut << "145.99\t193.219\tPaper_Birch\tAdult\t48.9117\t26.3275\t1\t0\t5\t0.3\t2\n";
  oOut << "160.547\t169.476\tBlack_Cottonwood\tAdult\t48.8187\t26.8154\t1\t0\t4\t8.6\t2\n";
  oOut << "95.9534\t149.744\tWestern_Redcedar\tAdult\t48.7903\t28.6313\t0\t1\t2\t22.7\t3\n";
  oOut << "159.192\t105.145\tWestern_Redcedar\tAdult\t48.6996\t28.6235\t1\t1\t3\t10.9\t1\n";
  oOut << "172.223\t99.8901\tTrembling_Aspen\tAdult\t48.6642\t24.3423\t0\t1\t2\t1.3\t3\n";
  oOut << "162.646\t91.8396\tTrembling_Aspen\tAdult\t48.5281\t24.3166\t1\t1\t3\t9.7\t1\n";
  oOut << "137.433\t96.6553\tLodgepole_Pine\tAdult\t48.407\t28.0952\t1\t1\t3\t3.4\t1\n";
  oOut << "112.17\t91.272\tLodgepole_Pine\tAdult\t48.3426\t28.0883\t0\t1\t2\t4.7\t3\n";
  oOut << "5.82275\t133.191\tLodgepole_Pine\tAdult\t48.324\t28.0864\t1\t1\t5\t13.2\t1\n";
  oOut << "24.3408\t36.7615\tWestern_Redcedar\tAdult\t48.1793\t28.5781\t1\t0\t4\t6\t2\n";
  oOut << "8.88062\t193.494\tHybrid_Spruce\tAdult\t48.1726\t21.1275\t0\t0\t2\t4.4\t4\n";
  oOut << "123.523\t127.551\tLodgepole_Pine\tAdult\t48.0554\t28.0574\t0\t0\t0\t2.8\t4\n";
  oOut << "173.346\t118.073\tSubalpine_Fir\tAdult\t47.9849\t24.7423\t0\t1\t0\t0.7\t3\n";
  oOut << "193.225\t162.28\tPaper_Birch\tAdult\t47.923\t26.1718\t0\t1\t0\t6.4\t3\n";
  oOut << "3.39966\t162.634\tWestern_Redcedar\tAdult\t47.6489\t28.5303\t0\t0\t1\t9.4\t4\n";
  oOut << "6.06079\t43.5608\tWestern_Hemlock\tAdult\t47.644\t28.5758\t0\t1\t4\t13.5\t3\n";
  oOut << "175.385\t5.40161\tPaper_Birch\tAdult\t47.6099\t26.1211\t0\t1\t3\t4.4\t3\n";
  oOut << "190.466\t12.6465\tSubalpine_Fir\tAdult\t47.4664\t24.6451\t0\t0\t0\t10.7\t4\n";
  oOut << "37.8235\t98.4375\tSubalpine_Fir\tAdult\t47.4323\t24.6387\t0\t1\t0\t5.4\t3\n";
  oOut << "157.8\t109.943\tWestern_Hemlock\tAdult\t47.3859\t28.5525\t1\t1\t5\t11.8\t1\n";
  oOut << "91.8335\t81.6162\tAmabilis_Fir\tAdult\t47.3602\t28.5502\t0\t1\t0\t4.4\t3\n";
  oOut << "99.5239\t27.5391\tHybrid_Spruce\tAdult\t47.3404\t20.946\t0\t1\t2\t1\t3\n";
  oOut << "114.99\t25.5005\tTrembling_Aspen\tAdult\t47.1631\t24.052\t0\t1\t1\t4\t3\n";
  oOut << "53.6804\t147.443\tBlack_Cottonwood\tAdult\t47.1579\t26.5683\t1\t1\t2\t9.4\t1\n";
  oOut << "156.329\t182.007\tWestern_Hemlock\tAdult\t47.0844\t28.5247\t1\t0\t5\t4.4\t2\n";
  oOut << "8.69751\t61.4624\tBlack_Cottonwood\tAdult\t47.056\t26.5525\t0\t0\t1\t12.7\t4\n";
  oOut << "35.6262\t192.2\tAmabilis_Fir\tAdult\t47.0511\t28.5216\t0\t1\t0\t3.9\t3\n";
  oOut << "158.795\t120.374\tPaper_Birch\tAdult\t46.8307\t25.9921\t1\t1\t0\t8\t1\n";
  oOut << "139.801\t37.793\tBlack_Cottonwood\tAdult\t46.7459\t26.5041\t0\t0\t1\t9.2\t4\n";
  oOut << "145.172\t57.5256\tAmabilis_Fir\tAdult\t46.6653\t28.4853\t0\t1\t0\t9.7\t3\n";
  oOut << "13.9648\t20.0195\tSubalpine_Fir\tAdult\t46.633\t24.4851\t0\t1\t0\t2.1\t3\n";
  oOut << "56.0608\t67.9138\tHybrid_Spruce\tAdult\t46.6187\t20.7856\t1\t1\t2\t9.5\t1\n";
  oOut << "196.094\t109.802\tBlack_Cottonwood\tAdult\t46.6089\t26.4825\t0\t0\t0\t7.4\t4\n";
  oOut << "165.582\t63.6658\tBlack_Cottonwood\tAdult\t46.4575\t26.4584\t1\t0\t2\t2.3\t2\n";
  oOut << "56.4697\t167.139\tPaper_Birch\tAdult\t46.4163\t25.9217\t0\t0\t5\t7.2\t4\n";
  oOut << "32.3914\t38.4583\tHybrid_Spruce\tAdult\t46.4084\t20.7383\t1\t0\t0\t5.6\t2\n";
  oOut << "95.7336\t161.938\tBlack_Cottonwood\tAdult\t46.3538\t26.4419\t0\t1\t2\t6.8\t3\n";
  oOut << "182.782\t143.738\tPaper_Birch\tAdult\t46.3022\t25.9022\t0\t1\t0\t7.5\t3\n";
  oOut << "161.627\t113.623\tWestern_Hemlock\tAdult\t46.2454\t28.4447\t1\t1\t2\t8.4\t1\n";
  oOut << "138.043\t41.8396\tTrembling_Aspen\tAdult\t46.2427\t23.8667\t0\t0\t5\t1.7\t4\n";
  oOut << "97.1497\t34.0454\tAmabilis_Fir\tAdult\t46.2387\t28.444\t0\t1\t0\t9.5\t3\n";
  oOut << "136.646\t125.232\tBlack_Cottonwood\tAdult\t46.1038\t26.4016\t0\t1\t5\t7.3\t3\n";
  oOut << "133.801\t129.919\tSubalpine_Fir\tAdult\t45.9674\t24.3539\t0\t1\t0\t3.2\t3\n";
  oOut << "159.607\t6.84814\tHybrid_Spruce\tAdult\t45.9476\t20.6339\t1\t0\t2\t9.3\t2\n";
  oOut << "4.99268\t55.3345\tLodgepole_Pine\tAdult\t45.7504\t27.7897\t0\t0\t4\t10.6\t4\n";
  oOut << "4.84619\t80.7007\tSubalpine_Fir\tAdult\t45.7001\t24.3003\t0\t1\t0\t4.7\t3\n";
  oOut << "198.553\t24.9939\tLodgepole_Pine\tAdult\t45.6174\t27.7732\t0\t1\t0\t5.5\t3\n";
  oOut << "162.592\t192.279\tBlack_Cottonwood\tAdult\t45.5884\t26.3172\t1\t0\t3\t9.7\t2\n";
  oOut << "113.135\t133.386\tSubalpine_Fir\tAdult\t45.5475\t24.2695\t0\t1\t0\t2.3\t3\n";
  oOut << "162.347\t98.1262\tPaper_Birch\tAdult\t45.5057\t25.7627\t1\t1\t1\t4.8\t1\n";
  oOut << "193.86\t21.5759\tTrembling_Aspen\tAdult\t45.4996\t23.7129\t0\t1\t4\t9.7\t3\n";
  oOut << "90.4358\t0.146484\tHybrid_Spruce\tAdult\t45.4599\t20.5221\t0\t1\t1\t5.9\t3\n";
  oOut << "94.2322\t181.531\tSubalpine_Fir\tAdult\t45.3134\t24.2219\t0\t1\t0\t6.5\t3\n";
  oOut << "28.9612\t126.093\tWestern_Hemlock\tAdult\t45.2948\t28.3487\t0\t1\t2\t8.3\t3\n";
  oOut << "18.6279\t22.4121\tHybrid_Spruce\tAdult\t45.2301\t20.469\t0\t0\t2\t0.7\t4\n";
  oOut << "90.7959\t59.845\tAmabilis_Fir\tAdult\t45.1566\t28.3342\t0\t1\t0\t9.4\t3\n";
  oOut << "75.415\t142.963\tHybrid_Spruce\tAdult\t45\t20.4154\t1\t0\t1\t10.2\t2\n";
  oOut << "129.84\t16.8518\tHybrid_Spruce\tAdult\t44.949\t20.4035\t0\t0\t5\t5.5\t4\n";
  oOut << "61.0596\t34.2102\tWestern_Redcedar\tAdult\t44.9008\t28.2557\t1\t1\t5\t7.9\t1\n";
  oOut << "124.762\t37.3596\tHybrid_Spruce\tAdult\t44.8953\t20.391\t0\t0\t5\t0\t4\n";
  oOut << "18.5486\t183.551\tAmabilis_Fir\tAdult\t44.8843\t28.3054\t0\t1\t0\t1.6\t3\n";
  oOut << "125.745\t5.59082\tWestern_Redcedar\tAdult\t44.7421\t28.2384\t0\t0\t1\t24.4\t4\n";
  oOut << "179.944\t155.145\tSubalpine_Fir\tAdult\t44.6997\t24.0952\t0\t1\t0\t7.4\t3\n";
  oOut << "145.77\t0.45166\tWestern_Redcedar\tAdult\t44.6664\t28.2301\t1\t1\t3\t23.4\t1\n";
  oOut << "11.6516\t65.9912\tWestern_Hemlock\tAdult\t44.5438\t28.2687\t1\t0\t4\t11.1\t2\n";
  oOut << "71.5942\t127.454\tTrembling_Aspen\tAdult\t44.5139\t23.5029\t1\t0\t0\t8.9\t2\n";
  oOut << "132.428\t100.903\tSubalpine_Fir\tAdult\t44.4791\t24.049\t0\t0\t0\t4.5\t4\n";
  oOut << "86.8164\t41.6809\tWestern_Redcedar\tAdult\t44.4687\t28.2081\t1\t0\t0\t9.1\t2\n";
  oOut << "146.021\t128.168\tLodgepole_Pine\tAdult\t44.3851\t27.6141\t1\t1\t3\t9.3\t1\n";
  oOut << "72.5342\t30.4565\tPaper_Birch\tAdult\t44.3671\t25.5552\t1\t0\t3\t4.3\t2\n";
  oOut << "18.8599\t15.4663\tPaper_Birch\tAdult\t44.364\t25.5546\t1\t0\t1\t12.9\t2\n";
  oOut << "12.4146\t95.8923\tHybrid_Spruce\tAdult\t44.3427\t20.2609\t1\t0\t3\t13.3\t2\n";
  oOut << "79.364\t155.511\tLodgepole_Pine\tAdult\t44.292\t27.6016\t1\t0\t2\t8.3\t2\n";
  oOut << "55.0842\t19.7021\tLodgepole_Pine\tAdult\t44.234\t27.5938\t1\t1\t3\t11.2\t1\n";
  oOut << "2.83203\t138.33\tTrembling_Aspen\tAdult\t44.0927\t23.411\t0\t1\t4\t4.1\t3\n";
  oOut << "169.336\t101.825\tWestern_Hemlock\tAdult\t44.0875\t28.2182\t1\t1\t4\t2\t1\n";
  oOut << "32.5439\t121.399\tHybrid_Spruce\tAdult\t44.0854\t20.1997\t0\t1\t5\t5.8\t3\n";
  oOut << "81.1157\t158.716\tWestern_Hemlock\tAdult\t44.0588\t28.215\t1\t0\t5\t7.9\t2\n";
  oOut << "38.5132\t32.2754\tPaper_Birch\tAdult\t44.0454\t25.4947\t1\t1\t1\t9.2\t1\n";
  oOut << "111.658\t11.4563\tHybrid_Spruce\tAdult\t44.0451\t20.1901\t0\t1\t1\t2.2\t3\n";
  oOut << "151.324\t62.3413\tPaper_Birch\tAdult\t43.9578\t25.4781\t1\t0\t1\t5.7\t2\n";
  oOut << "129.327\t105.841\tHybrid_Spruce\tAdult\t43.9096\t20.1577\t0\t0\t4\t9.8\t4\n";
  oOut << "3.4729\t9.44214\tBlack_Cottonwood\tAdult\t43.8516\t26.0178\t0\t1\t1\t10.1\t3\n";
  oOut << "190.71\t41.2842\tLodgepole_Pine\tAdult\t43.7674\t27.5301\t0\t1\t4\t8\t3\n";
  oOut << "27.0752\t166.302\tHybrid_Spruce\tAdult\t43.7372\t20.1163\t0\t0\t1\t0.9\t4\n";
  oOut << "12.0911\t138.55\tTrembling_Aspen\tAdult\t43.5123\t23.2823\t1\t0\t2\t12.7\t2\n";
  oOut << "128.137\t177.222\tWestern_Redcedar\tAdult\t43.4476\t28.0903\t0\t1\t5\t12.3\t3\n";
  oOut << "13.1226\t14.2883\tPaper_Birch\tAdult\t43.4238\t25.3756\t1\t1\t1\t1.6\t1\n";
  oOut << "100.623\t84.0332\tLodgepole_Pine\tAdult\t43.4229\t27.482\t0\t1\t5\t11\t3\n";
  oOut << "68.1885\t43.4875\tHybrid_Spruce\tAdult\t43.2742\t20.0044\t1\t0\t0\t2.5\t2\n";
  oOut << "165.436\t150.183\tPaper_Birch\tAdult\t43.2315\t25.3381\t1\t1\t2\t9.5\t1\n";
  oOut << "51.2756\t146.735\tAmabilis_Fir\tAdult\t43.1937\t28.115\t0\t1\t0\t3.9\t3\n";
  oOut << "132.855\t111.243\tWestern_Hemlock\tAdult\t43.0722\t28.1005\t0\t0\t5\t6.1\t4\n";
  oOut << "83.96\t65.4663\tAmabilis_Fir\tAdult\t43.0615\t28.0992\t0\t0\t0\t1.7\t4\n";
  oOut << "159.979\t30.7556\tTrembling_Aspen\tAdult\t43.0118\t23.1693\t1\t0\t2\t3.4\t2\n";
  oOut << "168.384\t155.005\tPaper_Birch\tAdult\t42.8427\t25.2613\t1\t0\t5\t6.2\t2\n";
  oOut << "167.676\t11.3281\tHybrid_Spruce\tAdult\t42.8085\t19.8905\t1\t0\t5\t10\t2\n";
  oOut << "151.428\t74.8291\tLodgepole_Pine\tAdult\t42.7835\t27.3902\t1\t0\t5\t9.1\t2\n";
  oOut << "45.7214\t199.78\tAmabilis_Fir\tAdult\t42.7408\t28.0604\t0\t1\t0\t6.8\t3\n";
  oOut << "145.654\t62.1033\tSubalpine_Fir\tAdult\t42.7368\t23.6711\t0\t1\t0\t2.6\t3\n";
  oOut << "113.153\t185.101\tLodgepole_Pine\tAdult\t42.6974\t27.3776\t0\t1\t2\t7.2\t3\n";
  oOut << "0.921631\t188.062\tPaper_Birch\tAdult\t42.6837\t25.2296\t1\t0\t2\t2.8\t2\n";
  oOut << "130.725\t17.5293\tWestern_Redcedar\tAdult\t42.6157\t27.9887\t0\t0\t2\t20.5\t4\n";
  oOut << "189.374\t71.1121\tSubalpine_Fir\tAdult\t42.4817\t23.6138\t0\t0\t0\t3.9\t4\n";
  oOut << "48.114\t156.976\tHybrid_Spruce\tAdult\t42.4615\t19.8047\t1\t1\t3\t6.9\t1\n";
  oOut << "18.457\t66.2415\tWestern_Redcedar\tAdult\t42.438\t27.9663\t0\t0\t4\t8.7\t4\n";
  oOut << "95.0439\t90.0208\tTrembling_Aspen\tAdult\t42.0859\t22.9552\t0\t1\t1\t3.9\t3\n";
  oOut << "5.98145\t22.345\tSubalpine_Fir\tAdult\t42.03\t23.5111\t1\t1\t0\t11.1\t1\n";
  oOut << "10.8154\t120.825\tWestern_Redcedar\tAdult\t42.0291\t27.9138\t0\t0\t5\t5.6\t4\n";
  oOut << "38.855\t92.4927\tTrembling_Aspen\tAdult\t41.9351\t22.9197\t1\t1\t1\t3.6\t1\n";
  oOut << "153.461\t69.1162\tSubalpine_Fir\tAdult\t41.922\t23.4863\t0\t1\t0\t7.4\t3\n";
  oOut << "129.279\t90.5762\tWestern_Redcedar\tAdult\t41.9128\t27.8986\t0\t0\t5\t11.9\t4\n";
  oOut << "97.9004\t69.3909\tAmabilis_Fir\tAdult\t41.9073\t27.9558\t0\t1\t0\t5.7\t3\n";
  oOut << "21.3257\t92.1265\tTrembling_Aspen\tAdult\t41.8686\t22.904\t0\t1\t5\t3.9\t3\n";
  oOut << "131.586\t122.089\tHybrid_Spruce\tAdult\t41.8552\t19.6532\t0\t0\t3\t7.6\t4\n";
  oOut << "3.16772\t93.3289\tLodgepole_Pine\tAdult\t41.7413\t27.2333\t1\t1\t5\t4.9\t1\n";
  oOut << "65.5396\t79.9622\tWestern_Hemlock\tAdult\t41.7285\t27.9327\t1\t0\t0\t7.6\t2\n";
  oOut << "92.6208\t43.3044\tAmabilis_Fir\tAdult\t41.6812\t27.9265\t0\t1\t0\t7.7\t3\n";
  oOut << "79.0955\t102.002\tWestern_Hemlock\tAdult\t41.6165\t27.918\t1\t0\t0\t10.4\t2\n";
  oOut << "123.285\t187.439\tAmabilis_Fir\tAdult\t41.571\t27.9121\t0\t0\t0\t8\t4\n";
  oOut << "88.9954\t187.689\tAmabilis_Fir\tAdult\t41.5155\t27.9047\t0\t0\t0\t2.7\t4\n";
  oOut << "54.5044\t17.5354\tWestern_Redcedar\tAdult\t41.3925\t27.8294\t1\t1\t4\t5.1\t1\n";
  oOut << "130.133\t181.287\tWestern_Hemlock\tAdult\t41.3898\t27.8881\t0\t0\t2\t0.2\t4\n";
  oOut << "169.391\t56.2439\tAmabilis_Fir\tAdult\t41.3831\t27.8872\t0\t1\t0\t2.3\t3\n";
  oOut << "192.914\t129.59\tLodgepole_Pine\tAdult\t41.3763\t27.1762\t0\t0\t3\t5.6\t4\n";
  oOut << "148.401\t137.726\tBlack_Cottonwood\tAdult\t41.2891\t25.5311\t1\t1\t2\t1.1\t1\n";
  oOut << "138.367\t20.7031\tWestern_Hemlock\tAdult\t41.282\t27.8737\t0\t0\t5\t5.7\t4\n";
  oOut << "120.142\t136.237\tTrembling_Aspen\tAdult\t41.2268\t22.7505\t0\t0\t5\t11.4\t4\n";
  oOut << "38.0066\t83.2336\tWestern_Redcedar\tAdult\t41.1926\t27.8022\t1\t1\t1\t6.8\t1\n";
  oOut << "32.0435\t39.6667\tSubalpine_Fir\tAdult\t41.1737\t23.3118\t0\t1\t1\t1.5\t3\n";
  oOut << "191.26\t10.7422\tWestern_Hemlock\tAdult\t41.1438\t27.8551\t0\t1\t4\t1.1\t3\n";
  oOut << "177.417\t32.0923\tHybrid_Spruce\tAdult\t41.091\t19.459\t0\t1\t1\t10.4\t3\n";
  oOut << "23.9258\t92.3828\tLodgepole_Pine\tAdult\t41.0281\t27.1206\t0\t0\t4\t8\t4\n";
  oOut << "24.1516\t85.7239\tTrembling_Aspen\tAdult\t41.0172\t22.6997\t0\t1\t0\t11.1\t3\n";
  oOut << "143.28\t176.154\tBlack_Cottonwood\tAdult\t40.9753\t25.4675\t0\t0\t3\t5.2\t4\n";
  oOut << "144.196\t1.5686\tTrembling_Aspen\tAdult\t40.9665\t22.6874\t0\t0\t0\t11.9\t4\n";
  oOut << "138.959\t127.112\tWestern_Hemlock\tAdult\t40.95\t27.8288\t0\t0\t4\t9.4\t4\n";
  oOut << "36.9751\t62.5\tAmabilis_Fir\tAdult\t40.8957\t27.8213\t0\t1\t0\t6.9\t3\n";
  oOut << "83.6548\t104.919\tPaper_Birch\tAdult\t40.8444\t24.8464\t1\t0\t2\t2.4\t2\n";
  oOut << "99.4507\t49.0479\tSubalpine_Fir\tAdult\t40.7861\t23.2195\t0\t1\t0\t6.2\t3\n";
  oOut << "110.858\t93.0115\tAmabilis_Fir\tAdult\t40.733\t27.7989\t0\t1\t0\t7\t3\n";
  oOut << "142.322\t80.3406\tPaper_Birch\tAdult\t40.6247\t24.7987\t0\t0\t3\t6.1\t4\n";
  oOut << "101.385\t15.9302\tSubalpine_Fir\tAdult\t40.5408\t23.1605\t0\t1\t0\t11.4\t3\n";
  oOut << "180.469\t156.335\tBlack_Cottonwood\tAdult\t40.5386\t25.3776\t0\t1\t0\t3.8\t3\n";
  oOut << "43.6218\t2.59399\tBlack_Cottonwood\tAdult\t40.5328\t25.3764\t1\t1\t0\t0.5\t1\n";
  oOut << "197.687\t36.8408\tWestern_Hemlock\tAdult\t40.531\t27.7707\t0\t0\t5\t7.4\t4\n";
  oOut << "25.7629\t117.81\tWestern_Hemlock\tAdult\t40.477\t27.7631\t0\t0\t1\t6.8\t4\n";
  oOut << "13.1836\t92.5842\tBlack_Cottonwood\tAdult\t40.4242\t25.3537\t0\t1\t0\t11.6\t3\n";
  oOut << "159.418\t98.0652\tBlack_Cottonwood\tAdult\t40.4138\t25.3516\t1\t1\t3\t1.9\t1\n";
  oOut << "76.6907\t89.7705\tWestern_Hemlock\tAdult\t40.3589\t27.7464\t1\t0\t3\t5.7\t2\n";
  oOut << "82.7576\t34.0454\tBlack_Cottonwood\tAdult\t40.3256\t25.3331\t1\t0\t2\t9.9\t2\n";
  oOut << "83.1299\t73.6389\tTrembling_Aspen\tAdult\t40.3174\t22.5274\t1\t0\t2\t11.1\t2\n";
  oOut << "77.7161\t66.2415\tPaper_Birch\tAdult\t40.2771\t24.7222\t1\t0\t0\t11.2\t2\n";
  oOut << "78.064\t158.014\tTrembling_Aspen\tAdult\t40.271\t22.5159\t1\t0\t4\t8\t2\n";
  oOut << "29.9255\t171.478\tLodgepole_Pine\tAdult\t40.2176\t26.9869\t0\t0\t2\t8.8\t4\n";
  oOut << "52.5635\t20.6848\tSubalpine_Fir\tAdult\t40.0092\t23.0308\t0\t1\t0\t8.5\t3\n";
  oOut << "92.8406\t91.0522\tWestern_Hemlock\tAdult\t39.9121\t27.682\t0\t0\t4\t5.6\t4\n";
  oOut << "43.1335\t97.9797\tTrembling_Aspen\tAdult\t39.8886\t22.4198\t1\t1\t5\t10.8\t1\n";
  oOut << "133.881\t114.124\tWestern_Hemlock\tAdult\t39.8019\t27.6659\t0\t0\t2\t3\t4\n";
  oOut << "173.145\t197.058\tTrembling_Aspen\tAdult\t39.7839\t22.3934\t0\t1\t3\t11.2\t3\n";
  oOut << "22.5098\t170.593\tAmabilis_Fir\tAdult\t39.6411\t27.6421\t0\t1\t0\t9.3\t3\n";
  oOut << "13.562\t166.565\tHybrid_Spruce\tAdult\t39.4263\t19.0232\t0\t0\t5\t12.2\t4\n";
  oOut << "95.4529\t34.8083\tTrembling_Aspen\tAdult\t39.3954\t22.2942\t0\t1\t0\t9.8\t3\n";
  oOut << "176.514\t56.1462\tWestern_Redcedar\tAdult\t39.3463\t27.5341\t0\t0\t4\t12.6\t4\n";
  oOut << "17.0593\t35.7788\tWestern_Hemlock\tAdult\t39.2218\t27.579\t1\t1\t3\t3\t1\n";
  oOut << "19.1711\t61.3708\tPaper_Birch\tAdult\t39.2023\t24.4785\t0\t1\t3\t1.4\t3\n";
  oOut << "159.357\t93.3228\tPaper_Birch\tAdult\t39.1547\t24.4674\t1\t1\t3\t8.7\t1\n";
  oOut << "94.1345\t111.743\tAmabilis_Fir\tAdult\t39.0915\t27.559\t0\t1\t0\t1.8\t3\n";
  oOut << "120.453\t124.731\tPaper_Birch\tAdult\t39.0875\t24.4518\t0\t0\t3\t0.6\t4\n";
  oOut << "129.303\t69.8181\tWestern_Hemlock\tAdult\t39.0826\t27.5577\t1\t1\t3\t1.1\t1\n";
  oOut << "13.9221\t108.533\tSubalpine_Fir\tAdult\t39.0561\t22.7921\t0\t1\t0\t1.2\t3\n";
  oOut << "152.734\t98.5962\tHybrid_Spruce\tAdult\t38.9621\t18.8986\t1\t1\t4\t10.3\t1\n";
  oOut << "27.6917\t57.6782\tSubalpine_Fir\tAdult\t38.8461\t22.7385\t0\t0\t0\t2.3\t4\n";
  oOut << "76.0925\t37.7258\tWestern_Hemlock\tAdult\t38.8348\t27.5193\t1\t0\t0\t2.6\t2\n";
  oOut << "197.443\t120.703\tPaper_Birch\tAdult\t38.8083\t24.3863\t0\t1\t1\t1\t3\n";
  oOut << "14.2334\t42.0044\tTrembling_Aspen\tAdult\t38.7991\t22.1395\t1\t0\t3\t12.2\t2\n";
  oOut << "66.7664\t136.639\tWestern_Redcedar\tAdult\t38.7384\t27.4388\t1\t0\t5\t6.2\t2\n";
  oOut << "40.9302\t83.1543\tWestern_Hemlock\tAdult\t38.5379\t27.4724\t1\t1\t0\t1.6\t1\n";
  oOut << "142.78\t66.0706\tSubalpine_Fir\tAdult\t38.5056\t22.6506\t0\t0\t0\t9.7\t4\n";
  oOut << "197.638\t82.7454\tTrembling_Aspen\tAdult\t38.5001\t22.0608\t0\t1\t5\t1.6\t3\n";
  oOut << "146.521\t53.0884\tHybrid_Spruce\tAdult\t38.4854\t18.769\t1\t0\t4\t5.8\t2\n";
  oOut << "174.902\t4.00391\tWestern_Hemlock\tAdult\t38.4561\t27.4594\t0\t1\t2\t5.4\t3\n";
  oOut << "107.568\t171.326\tWestern_Hemlock\tAdult\t38.2971\t27.4338\t0\t1\t2\t10.3\t3\n";
  oOut << "121.851\t187.134\tBlack_Cottonwood\tAdult\t38.2736\t24.8816\t0\t0\t4\t7.9\t4\n";
  oOut << "101.117\t12.6465\tTrembling_Aspen\tAdult\t38.2138\t21.9846\t0\t1\t0\t10.5\t3\n";
  oOut << "23.5046\t84.1248\tWestern_Hemlock\tAdult\t38.1808\t27.4149\t0\t0\t4\t6.3\t4\n";
  oOut << "136.334\t37.5732\tPaper_Birch\tAdult\t38.1079\t24.2187\t0\t0\t4\t10.2\t4\n";
  oOut << "123.541\t104.132\tTrembling_Aspen\tAdult\t38.0469\t21.9399\t1\t0\t2\t7.9\t2\n";
  oOut << "17.5415\t176.965\tSubalpine_Fir\tAdult\t38.0191\t22.5231\t0\t1\t0\t0.1\t3\n";
  oOut << "181.995\t131.866\tWestern_Redcedar\tAdult\t37.9742\t27.3139\t0\t1\t1\t4.3\t3\n";
  oOut << "39.1602\t53.2349\tWestern_Hemlock\tAdult\t37.963\t27.3792\t0\t0\t3\t1.8\t4\n";
  oOut << "27.5635\t7.47681\tHybrid_Spruce\tAdult\t37.9514\t18.6221\t0\t1\t5\t10.3\t3\n";
  oOut << "198.12\t12.9578\tWestern_Hemlock\tAdult\t37.9092\t27.3703\t0\t1\t0\t10.8\t3\n";
  oOut << "1.30005\t85.4675\tWestern_Redcedar\tAdult\t37.8787\t27.2979\t1\t1\t2\t7.3\t1\n";
  oOut << "192.706\t59.0942\tHybrid_Spruce\tAdult\t37.8571\t18.596\t0\t0\t2\t7.6\t4\n";
  oOut << "149.835\t193.793\tWestern_Redcedar\tAdult\t37.8491\t27.2929\t1\t0\t4\t21.7\t2\n";
  oOut << "153.192\t64.8926\tAmabilis_Fir\tAdult\t37.8247\t27.3563\t0\t1\t0\t11\t3\n";
  oOut << "171.527\t182.184\tWestern_Hemlock\tAdult\t37.7225\t27.3392\t0\t1\t4\t4.2\t3\n";
  oOut << "45.5627\t79.1504\tAmabilis_Fir\tAdult\t37.6816\t27.3323\t0\t1\t0\t9.9\t3\n";
  oOut << "50.885\t166.345\tWestern_Redcedar\tAdult\t37.6669\t27.2619\t1\t1\t5\t6.2\t1\n";
  oOut << "32.2937\t65.5823\tPaper_Birch\tAdult\t37.6617\t24.1094\t1\t0\t0\t1.1\t2\n";
  oOut << "7.8064\t182.214\tSubalpine_Fir\tAdult\t37.6587\t22.4273\t0\t0\t0\t13.3\t4\n";
  oOut << "79.4617\t146.167\tSubalpine_Fir\tAdult\t37.4005\t22.3579\t0\t0\t0\t4.7\t4\n";
  oOut << "94.8486\t1.94092\tPaper_Birch\tAdult\t37.352\t24.0323\t0\t1\t0\t3.7\t3\n";
  oOut << "24.3286\t157.99\tWestern_Redcedar\tAdult\t37.3361\t27.2049\t1\t0\t5\t6.9\t2\n";
  oOut << "44.4336\t23.4863\tAmabilis_Fir\tAdult\t37.3267\t27.272\t0\t1\t0\t9.3\t3\n";
  oOut << "79.6631\t17.5537\tBlack_Cottonwood\tAdult\t37.2897\t24.6499\t1\t0\t5\t12\t2\n";
  oOut << "85.8215\t79.5044\tTrembling_Aspen\tAdult\t37.2751\t21.7299\t1\t0\t1\t10.5\t2\n";
  oOut << "5.3772\t140.125\tAmabilis_Fir\tAdult\t37.2275\t27.2549\t0\t0\t0\t14.5\t4\n";
  oOut << "32.3914\t155.225\tSubalpine_Fir\tAdult\t37.1436\t22.2882\t0\t1\t0\t2.7\t3\n";
  oOut << "152.82\t70.8069\tHybrid_Spruce\tAdult\t37.1304\t18.3926\t1\t0\t4\t4.5\t2\n";
  oOut << "159.076\t7.49512\tPaper_Birch\tAdult\t37.03\t23.951\t1\t0\t0\t11.1\t2\n";
  oOut << "45.5017\t128.888\tSubalpine_Fir\tAdult\t36.962\t22.2386\t0\t1\t0\t11.4\t3\n";
  oOut << "72.0215\t170.593\tBlack_Cottonwood\tAdult\t36.944\t24.566\t1\t0\t4\t5.1\t2\n";
  oOut << "12.5366\t137.823\tLodgepole_Pine\tAdult\t36.8817\t26.368\t1\t0\t3\t13.4\t2\n";
  oOut << "142.145\t156.396\tLodgepole_Pine\tAdult\t36.8674\t26.3651\t0\t0\t4\t8.3\t4\n";
  oOut << "28.3142\t53.8513\tHybrid_Spruce\tAdult\t36.8625\t18.3166\t0\t0\t3\t9\t4\n";
  oOut << "93.1641\t133.429\tTrembling_Aspen\tAdult\t36.8311\t21.6066\t0\t1\t1\t5\t3\n";
  oOut << "52.771\t61.1816\tBlack_Cottonwood\tAdult\t36.8259\t24.537\t0\t0\t2\t7.9\t4\n";
  oOut << "114.081\t48.2788\tLodgepole_Pine\tAdult\t36.7883\t26.349\t0\t1\t2\t4.2\t3\n";
  oOut << "137.891\t155.591\tPaper_Birch\tAdult\t36.7157\t23.8706\t0\t0\t2\t10\t4\n";
  oOut << "64.9048\t123.749\tWestern_Redcedar\tAdult\t36.6763\t27.0875\t1\t0\t4\t9.3\t2\n";
  oOut << "0.561523\t65.9363\tSubalpine_Fir\tAdult\t36.5909\t22.1362\t0\t1\t0\t4.8\t3\n";
  oOut << "146.173\t54.4128\tLodgepole_Pine\tAdult\t36.5878\t26.3078\t1\t0\t2\t8.6\t2\n";
  oOut << "20.0012\t172.687\tAmabilis_Fir\tAdult\t36.5283\t27.1313\t0\t1\t0\t1.7\t3\n";
  oOut << "78.6987\t96.2219\tBlack_Cottonwood\tAdult\t36.4972\t24.4556\t1\t0\t1\t10\t2\n";
  oOut << "5.33447\t149.139\tWestern_Hemlock\tAdult\t36.4764\t27.1219\t0\t0\t1\t14.9\t4\n";
  oOut << "21.4905\t195.148\tHybrid_Spruce\tAdult\t36.3278\t18.1636\t1\t1\t5\t2.7\t1\n";
  oOut << "10.5713\t79.6814\tBlack_Cottonwood\tAdult\t36.2888\t24.4034\t0\t1\t1\t3.3\t3\n";
  oOut << "74.4019\t28.4668\tLodgepole_Pine\tAdult\t36.2466\t26.2365\t1\t0\t4\t10.7\t2\n";
  oOut << "39.3311\t55.3711\tLodgepole_Pine\tAdult\t36.2152\t26.2299\t0\t1\t1\t2.1\t3\n";
  oOut << "92.926\t88.324\tBlack_Cottonwood\tAdult\t36.1157\t24.3597\t0\t1\t2\t4.5\t3\n";
  oOut << "160.974\t186.908\tPaper_Birch\tAdult\t36.0547\t23.6981\t1\t1\t1\t5\t1\n";
  oOut << "140.521\t43.5669\tBlack_Cottonwood\tAdult\t35.9793\t24.3249\t0\t1\t1\t10.1\t3\n";
  oOut << "138.66\t49.8169\tHybrid_Spruce\tAdult\t35.8368\t18.0214\t0\t1\t2\t6.1\t3\n";
  oOut << "44.0186\t91.9006\tWestern_Hemlock\tAdult\t35.7718\t26.9912\t1\t1\t2\t9.5\t1\n";
  oOut << "114.844\t137.396\tWestern_Redcedar\tAdult\t35.6906\t26.903\t0\t1\t1\t22.1\t3\n";
  oOut << "34.0393\t197.827\tAmabilis_Fir\tAdult\t35.6265\t26.9636\t0\t1\t0\t4.7\t3\n";
  oOut << "78.3264\t114.844\tSubalpine_Fir\tAdult\t35.6238\t21.8628\t0\t0\t0\t1.9\t4\n";
  oOut << "72.3022\t81.4941\tLodgepole_Pine\tAdult\t35.6067\t26.0992\t1\t0\t2\t6.6\t2\n";
  oOut << "46.5942\t29.9683\tWestern_Redcedar\tAdult\t35.5957\t26.8846\t1\t1\t3\t5.4\t1\n";
  oOut << "77.2278\t163.239\tTrembling_Aspen\tAdult\t35.4596\t21.2139\t1\t0\t3\t5.3\t2\n";
  oOut << "113.336\t77.9236\tBlack_Cottonwood\tAdult\t35.4398\t24.1854\t0\t1\t3\t1.9\t3\n";
  oOut << "122.235\t113.013\tBlack_Cottonwood\tAdult\t35.4224\t24.1809\t0\t0\t1\t10.3\t4\n";
  oOut << "0.219727\t45.8801\tLodgepole_Pine\tAdult\t35.4169\t26.0575\t1\t1\t5\t9.5\t1\n";
  oOut << "15.5945\t8.71582\tLodgepole_Pine\tAdult\t35.4047\t26.0548\t0\t1\t5\t12.8\t3\n";
  oOut << "42.5964\t190.039\tBlack_Cottonwood\tAdult\t35.3036\t24.1497\t1\t1\t1\t2.9\t1\n";
  oOut << "1.24512\t159.784\tTrembling_Aspen\tAdult\t35.2258\t21.1452\t1\t0\t0\t1.9\t2\n";
  oOut << "190.125\t120.685\tSubalpine_Fir\tAdult\t35.2078\t21.7423\t0\t1\t0\t10.9\t3\n";
  oOut << "164.105\t172.565\tSubalpine_Fir\tAdult\t35.1154\t21.7153\t0\t1\t0\t6.1\t3\n";
  oOut << "30.8594\t182.654\tTrembling_Aspen\tAdult\t34.9753\t21.0709\t0\t1\t2\t5.2\t3\n";
  oOut << "106.494\t104.681\tWestern_Redcedar\tAdult\t34.9564\t26.7579\t0\t1\t5\t10.9\t3\n";
  oOut << "10.9863\t198.413\tTrembling_Aspen\tAdult\t34.9146\t21.0529\t1\t0\t0\t1.1\t2\n";
  oOut << "196.729\t171.405\tSubalpine_Fir\tAdult\t34.7818\t21.6171\t0\t0\t0\t2.9\t4\n";
  oOut << "86.3342\t184.369\tHybrid_Spruce\tAdult\t34.5831\t17.6503\t1\t0\t2\t4.5\t2\n";
  oOut << "194.592\t102.588\tBlack_Cottonwood\tAdult\t34.5648\t23.9519\t0\t1\t1\t3.9\t3\n";
  oOut << "65.7288\t181.073\tAmabilis_Fir\tAdult\t34.4217\t26.7241\t0\t0\t0\t8.4\t4\n";
  oOut << "157.281\t12.9456\tPaper_Birch\tAdult\t34.2416\t23.1994\t1\t0\t3\t7.1\t2\n";
  oOut << "7.66602\t76.4465\tAmabilis_Fir\tAdult\t34.2197\t26.6822\t0\t0\t0\t3.3\t4\n";
  oOut << "5.07812\t137.927\tTrembling_Aspen\tAdult\t34.1992\t20.8369\t0\t1\t3\t13.7\t3\n";
  oOut << "29.5593\t63.8489\tAmabilis_Fir\tAdult\t34.198\t26.6776\t0\t1\t0\t3.7\t3\n";
  oOut << "66.748\t34.9243\tSubalpine_Fir\tAdult\t34.1577\t21.4302\t0\t0\t0\t10\t4\n";
  oOut << "129.822\t114.63\tWestern_Hemlock\tAdult\t34.1074\t26.6586\t0\t0\t0\t6.7\t4\n";
  oOut << "119.135\t65.9912\tHybrid_Spruce\tAdult\t34.0717\t17.4957\t0\t0\t3\t11.2\t4\n";
  oOut << "59.6924\t194\tWestern_Hemlock\tAdult\t33.9206\t26.6191\t1\t1\t1\t6.2\t1\n";
  oOut << "2.948\t156.512\tTrembling_Aspen\tAdult\t33.9059\t20.7469\t0\t0\t5\t12.6\t4\n";
  oOut << "176.971\t38.3728\tWestern_Redcedar\tAdult\t33.7769\t26.5106\t0\t1\t5\t15\t3\n";
  oOut << "73.6084\t195.618\tLodgepole_Pine\tAdult\t33.4982\t25.6103\t1\t0\t1\t1.8\t2\n";
  oOut << "45.4956\t56.7017\tSubalpine_Fir\tAdult\t33.476\t21.2212\t0\t0\t0\t9.3\t4\n";
  oOut << "116.687\t132.648\tBlack_Cottonwood\tAdult\t33.4067\t23.6284\t0\t0\t3\t4.1\t4\n";
  oOut << "62.1704\t117.45\tWestern_Hemlock\tAdult\t33.3865\t26.5034\t0\t1\t3\t1.6\t3\n";
  oOut << "14.4653\t47.7112\tPaper_Birch\tAdult\t33.2953\t22.9237\t0\t1\t4\t4\t3\n";
  oOut << "165.448\t131.079\tLodgepole_Pine\tAdult\t33.2339\t25.5449\t1\t1\t0\t10.8\t1\n";
  oOut << "153.021\t59.3689\tWestern_Redcedar\tAdult\t33.215\t26.3862\t1\t1\t1\t12.8\t1\n";
  oOut << "112.189\t20.3796\tPaper_Birch\tAdult\t33.1494\t22.8802\t0\t1\t2\t8\t3\n";
  oOut << "132.05\t58.5876\tBlack_Cottonwood\tAdult\t33.1284\t23.5481\t0\t0\t0\t6.8\t4\n";
  oOut << "52.0325\t50.9949\tBlack_Cottonwood\tAdult\t33.0844\t23.5353\t1\t1\t2\t4.1\t1\n";
  oOut << "13.9404\t10.8521\tLodgepole_Pine\tAdult\t32.908\t25.4628\t0\t1\t5\t5\t3\n";
  oOut << "186.017\t69.22\tPaper_Birch\tAdult\t32.8851\t22.8007\t0\t1\t2\t3.3\t3\n";
  oOut << "42.5293\t146.057\tTrembling_Aspen\tAdult\t32.8064\t20.4015\t1\t1\t4\t0.6\t1\n";
  oOut << "164.667\t195.239\tHybrid_Spruce\tAdult\t32.7954\t17.1012\t1\t1\t5\t5.9\t1\n";
  oOut << "88.6719\t44.9219\tLodgepole_Pine\tAdult\t32.778\t25.4297\t1\t0\t0\t0.1\t2\n";
  oOut << "156.384\t174.127\tWestern_Hemlock\tAdult\t32.7524\t26.3608\t1\t0\t1\t6.6\t2\n";
  oOut << "14.6179\t73.7183\tAmabilis_Fir\tAdult\t32.6947\t26.3476\t0\t0\t0\t10.9\t4\n";
  oOut << "56.4148\t52.832\tAmabilis_Fir\tAdult\t32.6462\t26.3364\t0\t1\t0\t9.3\t3\n";
  oOut << "110.443\t100.873\tLodgepole_Pine\tAdult\t32.5668\t25.3753\t0\t1\t1\t1.2\t3\n";
  oOut << "111.023\t134.1\tHybrid_Spruce\tAdult\t32.5201\t17.0145\t0\t1\t2\t5.5\t3\n";
  oOut << "82.5439\t186.157\tHybrid_Spruce\tAdult\t32.4649\t16.9971\t0\t0\t0\t5\t4\n";
  oOut << "93.75\t156.512\tHybrid_Spruce\tAdult\t32.3999\t16.9765\t0\t1\t2\t3.2\t3\n";
  oOut << "57.7698\t193.115\tPaper_Birch\tAdult\t32.3907\t22.6497\t1\t1\t3\t9.1\t1\n";
  oOut << "66.5771\t138.971\tLodgepole_Pine\tAdult\t32.3862\t25.3283\t1\t0\t5\t6.2\t2\n";
  oOut << "135.4\t23.3521\tAmabilis_Fir\tAdult\t32.3062\t26.2571\t0\t1\t0\t9.3\t3\n";
  oOut << "108.234\t95.9106\tAmabilis_Fir\tAdult\t32.2577\t26.2456\t0\t0\t0\t8.5\t4\n";
  oOut << "82.3425\t35.1135\tAmabilis_Fir\tAdult\t32.2104\t26.2344\t0\t0\t0\t0.5\t4\n";
  oOut << "39.2395\t87.8357\tWestern_Redcedar\tAdult\t32.1518\t26.1386\t1\t1\t3\t5.9\t1\n";
  oOut << "19.9097\t3.38745\tLodgepole_Pine\tAdult\t31.9836\t25.2218\t0\t1\t3\t11.2\t3\n";
  oOut << "87.9333\t72.1924\tPaper_Birch\tAdult\t31.9543\t22.5137\t1\t0\t0\t0.6\t2\n";
  oOut << "158.728\t32.5134\tWestern_Redcedar\tAdult\t31.8536\t26.0662\t1\t1\t5\t25\t1\n";
  oOut << "9.33838\t86.4929\tWestern_Redcedar\tAdult\t31.7734\t26.0465\t1\t1\t0\t9.7\t1\n";
  oOut << "113.257\t52.887\tHybrid_Spruce\tAdult\t31.7151\t16.7577\t0\t1\t3\t2\t3\n";
  oOut << "111.572\t118.756\tHybrid_Spruce\tAdult\t31.5875\t16.7165\t0\t1\t5\t11\t3\n";
  oOut << "57.5439\t54.5471\tAmabilis_Fir\tAdult\t31.586\t26.0834\t0\t1\t0\t5.5\t3\n";
  oOut << "146.844\t80.1208\tWestern_Redcedar\tAdult\t31.5463\t25.9901\t1\t1\t4\t11.7\t1\n";
  oOut << "25.1648\t51.825\tBlack_Cottonwood\tAdult\t31.4819\t23.0519\t0\t1\t5\t10\t3\n";
  oOut << "158.093\t19.2749\tTrembling_Aspen\tAdult\t31.4795\t19.9674\t1\t1\t1\t9.6\t1\n";
  oOut << "58.5144\t85.9375\tBlack_Cottonwood\tAdult\t31.4279\t23.035\t1\t1\t0\t4.2\t1\n";
  oOut << "55.6091\t58.1726\tLodgepole_Pine\tAdult\t31.3901\t25.0603\t1\t1\t0\t1.7\t1\n";
  oOut << "86.9263\t149.762\tHybrid_Spruce\tAdult\t31.3779\t16.6485\t1\t1\t2\t11.8\t1\n";
  oOut << "109.65\t184.723\tTrembling_Aspen\tAdult\t31.348\t19.9233\t0\t1\t5\t5.8\t3\n";
  oOut << "31.5735\t67.6758\tSubalpine_Fir\tAdult\t31.3239\t20.5276\t0\t1\t0\t1.3\t3\n";
  oOut << "157.452\t134.991\tAmabilis_Fir\tAdult\t31.3168\t26.0164\t1\t1\t0\t11.9\t1\n";
  oOut << "85.144\t107.77\tAmabilis_Fir\tAdult\t31.293\t26.0104\t0\t0\t0\t0.8\t4\n";
  oOut << "32.1533\t123.181\tWestern_Redcedar\tAdult\t31.2845\t25.9241\t0\t1\t4\t9.1\t3\n";
  oOut << "108.398\t138.153\tHybrid_Spruce\tAdult\t31.221\t16.5975\t0\t1\t5\t5.1\t3\n";
  oOut << "146.027\t72.4121\tSubalpine_Fir\tAdult\t31.1221\t20.4599\t0\t0\t0\t5.9\t4\n";
  oOut << "79.4739\t179.755\tTrembling_Aspen\tAdult\t31.1191\t19.8462\t1\t0\t1\t0.2\t2\n";
  oOut << "76.7944\t114.923\tPaper_Birch\tAdult\t31.1172\t22.2458\t1\t0\t3\t8.5\t2\n";
  oOut << "120.306\t67.0227\tHybrid_Spruce\tAdult\t30.9973\t16.5243\t0\t0\t5\t6.1\t4\n";
  oOut << "193.536\t58.7708\tLodgepole_Pine\tAdult\t30.9601\t24.9399\t0\t1\t1\t5.9\t3\n";
  oOut << "77.832\t152.216\tAmabilis_Fir\tAdult\t30.9406\t25.9208\t0\t0\t0\t1.8\t4\n";
  oOut << "91.7236\t115.771\tWestern_Redcedar\tAdult\t30.9253\t25.8318\t1\t1\t0\t23.3\t1\n";
  oOut << "156.903\t66.6321\tSubalpine_Fir\tAdult\t30.8554\t20.3696\t0\t0\t0\t2.8\t4\n";
  oOut << "11.1511\t53.1677\tWestern_Redcedar\tAdult\t30.8292\t25.8068\t0\t0\t4\t5.1\t4\n";
  oOut << "187.518\t180.139\tSubalpine_Fir\tAdult\t30.8078\t20.3533\t0\t0\t0\t9.4\t4\n";
  oOut << "123.12\t8.89893\tLodgepole_Pine\tAdult\t30.7855\t24.8902\t0\t0\t1\t7.6\t4\n";
  oOut << "97.937\t80.9265\tWestern_Hemlock\tAdult\t30.6873\t25.8552\t0\t0\t5\t2.8\t4\n";
  oOut << "16.5222\t107.257\tBlack_Cottonwood\tAdult\t30.6522\t22.7876\t0\t0\t5\t11.9\t4\n";
  oOut << "124.036\t145.728\tPaper_Birch\tAdult\t30.5359\t22.0542\t0\t0\t3\t7.9\t4\n";
  oOut << "38.6963\t14.856\tBlack_Cottonwood\tAdult\t30.4977\t22.7373\t1\t1\t5\t10\t1\n";
  oOut << "136.09\t125.092\tPaper_Birch\tAdult\t30.4562\t22.0276\t0\t0\t3\t10.4\t4\n";
  oOut << "1.74561\t186.206\tTrembling_Aspen\tAdult\t30.4333\t19.6114\t0\t0\t0\t0.3\t4\n";
  oOut << "11.908\t76.7944\tWestern_Hemlock\tAdult\t30.4187\t25.7845\t1\t0\t4\t13\t2\n";
  oOut << "189.398\t176.599\tLodgepole_Pine\tAdult\t30.3769\t24.7719\t0\t1\t0\t1.1\t3\n";
  oOut << "46.2952\t44.9585\tPaper_Birch\tAdult\t30.1947\t21.9395\t1\t1\t4\t5.2\t1\n";
  oOut << "193.976\t194.458\tSubalpine_Fir\tAdult\t30.1526\t20.1274\t0\t1\t0\t4.6\t3\n";
  oOut << "7.06177\t28.0029\tBlack_Cottonwood\tAdult\t30.098\t22.6054\t0\t1\t3\t1.1\t3\n";
  oOut << "16.449\t49.4385\tWestern_Hemlock\tAdult\t29.9878\t25.6685\t0\t1\t1\t2.2\t3\n";
  oOut << "158.167\t76.5991\tHybrid_Spruce\tAdult\t29.9658\t16.1818\t1\t1\t0\t0.6\t1\n";
  oOut << "141.107\t87.3779\tBlack_Cottonwood\tAdult\t29.9094\t22.5424\t0\t0\t0\t0.4\t4\n";
  oOut << "18.3655\t106.775\tHybrid_Spruce\tAdult\t29.8276\t16.1353\t1\t0\t2\t2.1\t2\n";
  oOut << "25.3662\t147.314\tAmabilis_Fir\tAdult\t29.7968\t25.616\t0\t1\t0\t9.9\t3\n";
  oOut << "174.994\t72.1741\tAmabilis_Fir\tAdult\t29.7928\t25.6149\t0\t1\t0\t6.6\t3\n";
  oOut << "74.054\t124.42\tBlack_Cottonwood\tAdult\t29.7311\t22.4824\t1\t0\t3\t1.6\t2\n";
  oOut << "151.245\t5.10254\tSubalpine_Fir\tAdult\t29.7012\t19.9687\t0\t0\t0\t11.1\t4\n";
  oOut << "9.76562\t187.72\tAmabilis_Fir\tAdult\t29.6579\t25.5775\t0\t1\t0\t15\t3\n";
  oOut << "169.568\t60.3699\tLodgepole_Pine\tAdult\t29.6054\t24.5411\t1\t0\t3\t2.2\t2\n";
  oOut << "36.0291\t1.00708\tPaper_Birch\tAdult\t29.4086\t21.6689\t1\t1\t3\t1.3\t1\n";
  oOut << "73.3398\t145.984\tWestern_Hemlock\tAdult\t29.3579\t25.4931\t1\t0\t1\t6.1\t2\n";
  oOut << "34.1431\t24.7314\tLodgepole_Pine\tAdult\t29.3539\t24.4637\t1\t1\t5\t3.9\t1\n";
  oOut << "199.371\t156.976\tSubalpine_Fir\tAdult\t29.3338\t19.8376\t0\t1\t0\t1.7\t3\n";
  oOut << "111.89\t25.5493\tPaper_Birch\tAdult\t29.2926\t21.6282\t0\t1\t0\t3.6\t3\n";
  oOut << "40.5151\t28.7415\tAmabilis_Fir\tAdult\t29.2343\t25.4579\t0\t1\t0\t9.2\t3\n";
  oOut << "110.84\t29.3152\tWestern_Redcedar\tAdult\t29.1852\t25.3543\t0\t1\t4\t24.7\t3\n";
  oOut << "103.308\t164.563\tWestern_Hemlock\tAdult\t29.1663\t25.4384\t0\t1\t4\t5.9\t3\n";
  oOut << "148.053\t133.557\tPaper_Birch\tAdult\t29.0634\t21.5473\t1\t0\t4\t5.6\t2\n";
  oOut << "136.267\t67.7246\tWestern_Hemlock\tAdult\t29.0283\t25.3986\t0\t0\t4\t10.6\t4\n";
  oOut << "178.015\t145.557\tLodgepole_Pine\tAdult\t29.0265\t24.3612\t0\t1\t5\t0.4\t3\n";
  oOut << "165.729\t133.893\tPaper_Birch\tAdult\t29.0118\t21.5289\t1\t0\t2\t11.1\t2\n";
  oOut << "170.825\t20.7703\tPaper_Birch\tAdult\t29.0045\t21.5263\t1\t0\t0\t3.7\t2\n";
  oOut << "195.917\t49.1394\tWestern_Hemlock\tAdult\t28.9987\t25.39\t0\t1\t0\t5\t3\n";
  oOut << "177.496\t115.186\tSubalpine_Fir\tAdult\t28.9523\t19.6997\t0\t0\t0\t3.2\t4\n";
  oOut << "102.997\t7.56836\tAmabilis_Fir\tAdult\t28.9514\t25.3762\t0\t1\t0\t8\t3\n";
  oOut << "79.6997\t125.714\tLodgepole_Pine\tAdult\t28.9337\t24.3318\t1\t0\t4\t2.4\t2\n";
  oOut << "14.4775\t130.17\tSubalpine_Fir\tAdult\t28.8632\t19.6672\t1\t1\t0\t12.8\t1\n";
  oOut << "75.8118\t50.47\tWestern_Hemlock\tAdult\t28.8422\t25.3443\t1\t1\t3\t9.5\t1\n";
  oOut << "151.813\t70.7886\tSubalpine_Fir\tAdult\t28.8422\t19.6595\t0\t1\t3\t6.7\t3\n";
  oOut << "128.888\t63.7573\tAmabilis_Fir\tAdult\t28.797\t25.331\t0\t0\t0\t11.1\t4\n";
  oOut << "168.292\t118.292\tHybrid_Spruce\tAdult\t28.7762\t15.776\t1\t1\t0\t8.8\t1\n";
  oOut << "185.931\t79.3701\tSubalpine_Fir\tAdult\t28.7653\t19.6314\t0\t1\t0\t11.9\t3\n";
  oOut << "151.636\t159.241\tLodgepole_Pine\tAdult\t28.6996\t24.257\t1\t0\t4\t8.7\t2\n";
  oOut << "38.0981\t105.444\tTrembling_Aspen\tAdult\t28.6154\t18.9624\t1\t1\t3\t0.7\t1\n";
  oOut << "69.574\t151.202\tHybrid_Spruce\tAdult\t28.6108\t15.7186\t1\t0\t5\t9.8\t2\n";
  oOut << "88.4949\t165.308\tAmabilis_Fir\tAdult\t28.605\t25.2742\t0\t0\t0\t9.9\t4\n";
  oOut << "64.4714\t30.3589\tWestern_Hemlock\tAdult\t28.5464\t25.2567\t1\t0\t5\t4.9\t2\n";
  oOut << "77.9175\t94.0369\tWestern_Redcedar\tAdult\t28.5416\t25.1641\t1\t0\t4\t6.2\t2\n";
  oOut << "114.954\t145.471\tWestern_Redcedar\tAdult\t28.4024\t25.122\t0\t1\t1\t14.7\t3\n";
  oOut << "181.494\t95.4712\tHybrid_Spruce\tAdult\t28.3881\t15.641\t0\t1\t4\t11.4\t3\n";
  oOut << "129.7\t83.1299\tBlack_Cottonwood\tAdult\t28.3542\t22.0018\t0\t0\t4\t9.5\t4\n";
  oOut << "184.857\t91.0767\tWestern_Redcedar\tAdult\t28.3304\t25.1\t0\t1\t3\t11.8\t3\n";
  oOut << "79.0283\t81.2012\tBlack_Cottonwood\tAdult\t28.3112\t21.9863\t1\t0\t3\t3.4\t2\n";
  oOut << "67.6025\t175.391\tBlack_Cottonwood\tAdult\t28.0981\t21.9091\t1\t0\t1\t7.2\t2\n";
  oOut << "187.75\t88.2446\tPaper_Birch\tAdult\t28.0832\t21.192\t0\t0\t2\t0.5\t4\n";
  oOut << "145.392\t159.485\tLodgepole_Pine\tAdult\t28.0591\t24.0473\t1\t0\t1\t10.5\t2\n";
  oOut << "59.5764\t96.0999\tTrembling_Aspen\tAdult\t28.0154\t18.7395\t1\t1\t3\t5.6\t1\n";
  oOut << "0.787354\t67.4988\tLodgepole_Pine\tAdult\t27.9898\t24.0242\t1\t0\t1\t2.2\t2\n";
  oOut << "93.9453\t67.4561\tAmabilis_Fir\tAdult\t27.9095\t25.0625\t0\t1\t0\t6.3\t3\n";
  oOut << "66.8579\t165.387\tBlack_Cottonwood\tAdult\t27.8409\t21.8149\t0\t1\t2\t9.6\t3\n";
  oOut << "17.0776\t105.554\tWestern_Hemlock\tAdult\t27.8323\t25.0385\t0\t0\t4\t14.6\t4\n";
  oOut << "64.5386\t174.213\tTrembling_Aspen\tAdult\t27.8207\t18.6661\t0\t0\t5\t0.3\t4\n";
  oOut << "63.6658\t117.535\tLodgepole_Pine\tAdult\t27.6804\t23.9197\t1\t0\t0\t6\t2\n";
  oOut << "105.829\t157.025\tBlack_Cottonwood\tAdult\t27.6285\t21.7363\t1\t0\t1\t5.7\t2\n";
  oOut << "56.2561\t193.231\tWestern_Redcedar\tAdult\t27.5961\t24.8706\t1\t1\t0\t9.3\t1\n";
  oOut << "144.879\t170.807\tWestern_Redcedar\tAdult\t27.5662\t24.861\t0\t0\t4\t22.2\t4\n";
  oOut << "58.3008\t110.004\tLodgepole_Pine\tAdult\t27.5644\t23.8801\t1\t1\t0\t5.9\t1\n";
  oOut << "50.6348\t66.4795\tSubalpine_Fir\tAdult\t27.4896\t19.1534\t0\t1\t0\t5.8\t3\n";
  oOut << "15.2222\t26.5442\tAmabilis_Fir\tAdult\t27.4152\t24.9063\t0\t1\t0\t11.2\t3\n";
  oOut << "151.3\t100.049\tSubalpine_Fir\tAdult\t27.4146\t19.1246\t0\t0\t0\t7.9\t4\n";
  oOut << "158.862\t27.1667\tTrembling_Aspen\tAdult\t27.3795\t18.4982\t1\t0\t2\t5.7\t2\n";
  oOut << "192.81\t173.029\tHybrid_Spruce\tAdult\t27.3651\t15.2791\t0\t0\t3\t5\t4\n";
  oOut << "179.108\t173.303\tAmabilis_Fir\tAdult\t27.3248\t24.8773\t1\t1\t0\t4.7\t1\n";
  oOut << "92.2241\t138.77\tLodgepole_Pine\tAdult\t27.1899\t23.7504\t1\t1\t4\t0.7\t1\n";
  oOut << "101.215\t69.3787\tLodgepole_Pine\tAdult\t27.0917\t23.7159\t0\t1\t0\t9.1\t3\n";
  oOut << "1.15967\t99.1211\tWestern_Redcedar\tAdult\t27.0508\t24.6932\t0\t1\t0\t2.4\t3\n";
  oOut << "123.09\t65.5579\tWestern_Redcedar\tAdult\t27.0486\t24.6925\t1\t0\t2\t11.3\t2\n";
  oOut << "152.148\t169.208\tSubalpine_Fir\tAdult\t27.005\t18.9661\t0\t1\t0\t5.9\t3\n";
  oOut << "191.016\t152.826\tTrembling_Aspen\tAdult\t26.9931\t18.3491\t0\t1\t4\t6.5\t3\n";
  oOut << "70.9412\t151.074\tWestern_Hemlock\tAdult\t26.9037\t24.7395\t1\t0\t0\t10.6\t2\n";
  oOut << "168.28\t64.1663\tTrembling_Aspen\tAdult\t26.7511\t18.2547\t1\t1\t4\t6\t1\n";
  oOut << "177.155\t29.1626\tWestern_Hemlock\tAdult\t26.6144\t24.6428\t0\t1\t0\t4.4\t3\n";
  oOut << "135.901\t113.452\tSubalpine_Fir\tAdult\t26.5845\t18.8009\t0\t0\t0\t5.9\t4\n";
  oOut << "184.558\t133.105\tSubalpine_Fir\tAdult\t26.5738\t18.7966\t0\t1\t0\t11.8\t3\n";
  oOut << "130.402\t102.631\tTrembling_Aspen\tAdult\t26.5604\t18.1798\t0\t0\t0\t6.7\t4\n";
  oOut << "98.7\t113.019\tAmabilis_Fir\tAdult\t26.4774\t24.5963\t0\t1\t0\t6.7\t3\n";
  oOut << "16.8701\t86.8958\tAmabilis_Fir\tAdult\t26.4551\t24.5887\t0\t0\t0\t0.1\t4\n";
  oOut << "72.0642\t117.883\tLodgepole_Pine\tAdult\t26.2115\t23.3984\t1\t0\t0\t0\t2\n";
  oOut << "91.6077\t164.447\tPaper_Birch\tAdult\t26.1591\t20.4507\t0\t1\t3\t0.7\t3\n";
  oOut << "23.4131\t39.5142\tSubalpine_Fir\tAdult\t26.1453\t18.6257\t0\t1\t0\t0.8\t3\n";
  oOut << "15.3381\t68.8416\tAmabilis_Fir\tAdult\t25.9805\t24.4245\t0\t1\t0\t1.6\t3\n";
  oOut << "105.121\t96.4417\tAmabilis_Fir\tAdult\t25.961\t24.4176\t0\t1\t0\t3.6\t3\n";
  oOut << "15.0879\t16.2659\tWestern_Redcedar\tAdult\t25.9573\t24.3189\t1\t0\t1\t8.5\t2\n";
  oOut << "38.1958\t199.561\tPaper_Birch\tAdult\t25.9036\t20.3477\t1\t1\t0\t1.1\t1\n";
  oOut << "140.552\t58.1909\tWestern_Redcedar\tAdult\t25.9009\t24.2989\t0\t1\t4\t10.9\t3\n";
  oOut << "182.709\t83.905\tWestern_Hemlock\tAdult\t25.8966\t24.395\t0\t0\t2\t7.6\t4\n";
  oOut << "103.693\t29.8462\tAmabilis_Fir\tAdult\t25.849\t24.3781\t0\t1\t0\t4.4\t3\n";
  oOut << "148.657\t34.4299\tTrembling_Aspen\tAdult\t25.8176\t17.8835\t1\t0\t2\t4.6\t2\n";
  oOut << "175.818\t90.9851\tHybrid_Spruce\tAdult\t25.7568\t14.6916\t0\t0\t3\t8.3\t4\n";
  oOut << "44.3481\t146.716\tBlack_Cottonwood\tAdult\t25.7391\t21.003\t1\t1\t3\t4.5\t1\n";
  oOut << "198.431\t16.3879\tWestern_Redcedar\tAdult\t25.7132\t24.2318\t0\t0\t2\t1.5\t4\n";
  oOut << "194.415\t180.652\tPaper_Birch\tAdult\t25.5243\t20.1926\t0\t0\t2\t4.1\t4\n";
  oOut << "76.9714\t168.878\tBlack_Cottonwood\tAdult\t25.4962\t20.9041\t1\t0\t3\t4\t2\n";
  oOut << "90.1978\t17.0593\tLodgepole_Pine\tAdult\t25.4025\t23.0925\t1\t0\t3\t6.1\t2\n";
  oOut << "103.302\t181.396\tSubalpine_Fir\tAdult\t25.1871\t18.234\t0\t1\t0\t8.2\t3\n";
  oOut << "24.1516\t122.345\tSubalpine_Fir\tAdult\t25.1749\t18.229\t0\t0\t0\t7.8\t4\n";
  oOut << "65.3809\t110.986\tHybrid_Spruce\tAdult\t25.1639\t14.4691\t1\t0\t2\t1.6\t2\n";
  oOut << "57.1716\t136.169\tWestern_Hemlock\tAdult\t25.0626\t24.0926\t1\t1\t0\t11.1\t1\n";
  oOut << "182.733\t180.237\tBlack_Cottonwood\tAdult\t25.032\t20.7121\t0\t1\t2\t4\t3\n";
  oOut << "58.8379\t172.76\tSubalpine_Fir\tAdult\t25.0244\t18.1662\t0\t1\t0\t11.3\t3\n";
  oOut << "4.06494\t199.231\tWestern_Hemlock\tAdult\t24.9515\t24.0511\t1\t1\t5\t10.2\t1\n";
  oOut << "118.036\t57.0435\tAmabilis_Fir\tAdult\t24.8669\t24.0193\t0\t1\t0\t0.8\t3\n";
  oOut << "190.265\t172.699\tWestern_Redcedar\tAdult\t24.7986\t23.8934\t0\t0\t2\t0.9\t4\n";
  oOut << "8.75244\t37.7075\tTrembling_Aspen\tAdult\t24.7662\t17.4514\t1\t0\t2\t1\t2\n";
  oOut << "6.89087\t39.5203\tAmabilis_Fir\tAdult\t24.7052\t23.9581\t0\t0\t0\t2.8\t4\n";
  oOut << "167.847\t76.6663\tWestern_Redcedar\tAdult\t24.5239\t23.7879\t1\t1\t4\t1.2\t1\n";
  oOut << "194.885\t196.576\tWestern_Hemlock\tAdult\t24.5227\t23.8882\t0\t0\t1\t10.8\t4\n";
  oOut << "187.891\t122.107\tTrembling_Aspen\tAdult\t24.4714\t17.3274\t0\t1\t0\t3.9\t3\n";
  oOut << "103.943\t93.4204\tPaper_Birch\tAdult\t24.368\t19.7046\t0\t1\t5\t5\t3\n";
  oOut << "49.5972\t123.993\tHybrid_Spruce\tAdult\t24.3225\t14.1478\t1\t1\t3\t5.7\t1\n";
  oOut << "33.9661\t156.934\tBlack_Cottonwood\tAdult\t24.2712\t20.3886\t1\t0\t5\t10.8\t2\n";
  oOut << "155.103\t147.821\tBlack_Cottonwood\tAdult\t24.2194\t20.3662\t1\t0\t5\t3.3\t2\n";
  oOut << "25.1953\t8.25806\tLodgepole_Pine\tAdult\t23.8806\t22.4779\t1\t0\t1\t4\t2\n";
  oOut << "178.754\t131.055\tWestern_Hemlock\tAdult\t23.8516\t23.6243\t0\t1\t1\t3\t3\n";
  oOut << "50.4089\t47.0947\tSubalpine_Fir\tAdult\t23.8412\t17.661\t0\t1\t0\t8.5\t3\n";
  oOut << "24.8413\t160.016\tBlack_Cottonwood\tAdult\t23.8184\t20.1907\t1\t1\t2\t10.1\t1\n";
  oOut << "189.886\t53.9001\tWestern_Hemlock\tAdult\t23.7564\t23.5859\t0\t0\t0\t0.3\t4\n";
  oOut << "40.3015\t171.814\tSubalpine_Fir\tAdult\t23.7405\t17.617\t0\t1\t5\t9.4\t3\n";
  oOut << "76.8799\t85.5164\tPaper_Birch\tAdult\t23.7366\t19.4279\t1\t0\t2\t4.4\t2\n";
  oOut << "98.4619\t67.1326\tHybrid_Spruce\tAdult\t23.6703\t13.8943\t0\t1\t3\t6.7\t3\n";
  oOut << "44.9829\t33.9539\tWestern_Redcedar\tAdult\t23.6572\t23.4431\t1\t1\t0\t5\t1\n";
  oOut << "59.4421\t52.5879\tBlack_Cottonwood\tAdult\t23.4549\t20.029\t1\t1\t0\t6.9\t1\n";
  oOut << "189.996\t126.154\tHybrid_Spruce\tAdult\t23.3459\t13.7666\t0\t1\t0\t1.3\t3\n";
  oOut << "55.0781\t127.094\tPaper_Birch\tAdult\t23.291\t19.2282\t0\t0\t3\t5.3\t4\n";
  oOut << "10.199\t141.699\tWestern_Redcedar\tAdult\t23.2291\t23.2657\t0\t0\t3\t6\t4\n";
  oOut << "120.801\t169.794\tBlack_Cottonwood\tAdult\t23.1741\t19.9022\t0\t0\t4\t2\t4\n";
  oOut << "150.067\t179.663\tWestern_Redcedar\tAdult\t23.1686\t23.2403\t1\t1\t1\t24.5\t1\n";
  oOut << "189.771\t39.679\tBlack_Cottonwood\tAdult\t22.9523\t19.8009\t0\t1\t2\t8.4\t4\n";
  oOut << "98.5168\t43.5486\tPaper_Birch\tAdult\t22.9327\t19.0649\t0\t1\t0\t11.4\t4\n";
  oOut << "63.0066\t15.6006\tTrembling_Aspen\tAdult\t22.8455\t16.6216\t0\t0\t2\t2.8\t4\n";
  oOut << "153.149\t64.3188\tAmabilis_Fir\tAdult\t22.8043\t23.1894\t0\t1\t0\t9.6\t4\n";
  oOut << "14.5996\t24.8596\tLodgepole_Pine\tAdult\t22.7774\t21.9986\t1\t0\t0\t10.8\t2\n";
  oOut << "134.943\t185.016\tWestern_Hemlock\tAdult\t22.7289\t23.1569\t0\t0\t1\t8.1\t4\n";
  oOut << "53.3447\t129.956\tHybrid_Spruce\tAdult\t22.6886\t13.5049\t1\t1\t0\t6.5\t1\n";
  oOut << "103.998\t36.5784\tHybrid_Spruce\tAdult\t22.6883\t13.5048\t0\t1\t0\t6.7\t4\n";
  oOut << "44.6594\t73.0042\tWestern_Redcedar\tAdult\t22.6096\t23.0006\t1\t1\t3\t5.4\t1\n";
  oOut << "119.757\t93.158\tTrembling_Aspen\tAdult\t22.5317\t16.481\t0\t1\t3\t7.2\t4\n";
  oOut << "143.707\t1.84326\tLodgepole_Pine\tAdult\t22.4844\t21.8662\t0\t1\t4\t2.2\t4\n";
  oOut << "58.5938\t54.8279\tTrembling_Aspen\tAdult\t22.4445\t16.4416\t1\t1\t5\t9.5\t1\n";
  oOut << "44.3298\t94.6899\tTrembling_Aspen\tAdult\t22.3828\t16.4137\t1\t0\t3\t8.2\t2\n";
  oOut << "104.248\t193.347\tHybrid_Spruce\tAdult\t22.3141\t13.3539\t1\t1\t0\t5.6\t1\n";
  oOut << "106.213\t31.1951\tBlack_Cottonwood\tAdult\t22.2653\t19.4807\t0\t0\t4\t7\t4\n";
  oOut << "18.5852\t20.9045\tPaper_Birch\tAdult\t22.1954\t18.721\t1\t1\t5\t4.8\t1\n";
  oOut << "4.32739\t46.8994\tAmabilis_Fir\tAdult\t21.9852\t22.8287\t0\t1\t0\t3.1\t4\n";
  oOut << "113.947\t97.052\tPaper_Birch\tAdult\t21.94\t18.5993\t0\t1\t0\t4.7\t4\n";
  oOut << "53.4119\t133.685\tLodgepole_Pine\tAdult\t21.7035\t21.5026\t1\t1\t2\t11.8\t1\n";
  oOut << "79.4861\t112.067\tTrembling_Aspen\tAdult\t21.673\t16.0884\t1\t0\t4\t7.4\t2\n";
  oOut << "154.639\t82.428\tPaper_Birch\tAdult\t21.6125\t18.4414\t1\t0\t5\t1\t2\n";
  oOut << "147.662\t122.833\tWestern_Hemlock\tAdult\t21.5207\t22.6157\t1\t1\t0\t5.8\t1\n";
  oOut << "187\t155.127\tHybrid_Spruce\tAdult\t21.4319\t12.9927\t0\t0\t0\t5.7\t4\n";
  oOut << "8.47778\t67.9626\tPaper_Birch\tAdult\t21.4218\t18.3485\t0\t0\t4\t14\t4\n";
  oOut << "162.836\t182.41\tTrembling_Aspen\tAdult\t21.3763\t15.9502\t1\t1\t0\t8.1\t1\n";
  oOut << "181.006\t53.0579\tWestern_Hemlock\tAdult\t21.2219\t22.4754\t0\t0\t4\t6.1\t4\n";
  oOut << "188.257\t195.312\tBlack_Cottonwood\tAdult\t21.1044\t18.9165\t0\t0\t3\t0\t4\n";
  oOut << "38.2812\t52.655\tWestern_Redcedar\tAdult\t21.0965\t22.3083\t0\t0\t1\t7.5\t4\n";
  oOut << "158.649\t88.8489\tTrembling_Aspen\tAdult\t21.088\t15.8145\t1\t0\t0\t5.3\t2\n";
  oOut << "20.5688\t15.2893\tPaper_Birch\tAdult\t21.0339\t18.1571\t0\t0\t2\t4.7\t4\n";
  oOut << "168.207\t144.788\tHybrid_Spruce\tAdult\t20.9869\t12.8075\t1\t1\t3\t10.5\t1\n";
  oOut << "17.4561\t91.6382\tLodgepole_Pine\tAdult\t20.9769\t21.1497\t0\t0\t4\t3.6\t4\n";
  oOut << "130.414\t56.0669\tAmabilis_Fir\tAdult\t20.8871\t22.3151\t0\t0\t0\t8.5\t4\n";
  oOut << "27.3438\t54.4434\tPaper_Birch\tAdult\t20.8783\t18.0794\t0\t1\t1\t6.3\t4\n";
  oOut << "52.4353\t36.8652\tHybrid_Spruce\tAdult\t20.7635\t12.7138\t0\t1\t3\t5.1\t4\n";
  oOut << "66.4734\t177.948\tHybrid_Spruce\tAdult\t20.6174\t12.6522\t1\t0\t2\t9.5\t2\n";
  oOut << "60.2722\t183.759\tBlack_Cottonwood\tAdult\t20.611\t18.6677\t1\t1\t3\t3.9\t1\n";
  oOut << "113.3\t142.78\tWestern_Redcedar\tAdult\t20.5756\t22.0545\t0\t1\t0\t23.9\t4\n";
  oOut << "78.2837\t114.899\tTrembling_Aspen\tAdult\t20.528\t15.5472\t1\t0\t4\t6.1\t2\n";
  oOut << "116.309\t128.229\tLodgepole_Pine\tAdult\t20.4834\t20.9017\t0\t0\t3\t6.6\t4\n";
  oOut << "143.878\t37.5916\tSubalpine_Fir\tAdult\t20.4703\t16.1003\t0\t0\t0\t5\t4\n";
  oOut << "15.8386\t171.686\tPaper_Birch\tAdult\t20.455\t17.8656\t0\t1\t5\t4.5\t4\n";
  oOut << "180.969\t34.4299\tTrembling_Aspen\tAdult\t20.3699\t15.4708\t0\t0\t2\t3.5\t4\n";
  oOut << "81.0852\t148.718\tLodgepole_Pine\tAdult\t20.3546\t20.8359\t1\t0\t3\t9.8\t2\n";
  oOut << "184.186\t48.9075\tWestern_Hemlock\tAdult\t20.2258\t21.9881\t0\t0\t1\t7.7\t4\n";
  oOut << "28.2959\t41.8152\tSubalpine_Fir\tAdult\t20.2164\t15.975\t0\t0\t0\t5.5\t4\n";
  oOut << "104.803\t46.875\tSubalpine_Fir\tAdult\t20.2032\t15.9685\t0\t1\t0\t10.2\t4\n";
  oOut << "118.268\t145.471\tBlack_Cottonwood\tAdult\t20.1572\t18.4339\t0\t0\t3\t0.7\t4\n";
  oOut << "80.426\t130.377\tHybrid_Spruce\tAdult\t20.1474\t12.4527\t1\t0\t3\t9.9\t2\n";
  oOut << "132.745\t135.443\tWestern_Redcedar\tAdult\t20.0974\t21.8141\t0\t0\t5\t14.8\t4\n";
  oOut << "74.2981\t91.0339\tTrembling_Aspen\tAdult\t20.072\t15.3259\t1\t0\t1\t4.4\t2\n";
  oOut << "47.1436\t183.905\tHybrid_Spruce\tAdult\t20.0504\t12.4112\t1\t1\t2\t7.1\t1\n";
  oOut << "131.403\t184.003\tPaper_Birch\tAdult\t19.9683\t17.615\t0\t0\t1\t7.7\t4\n";
  oOut << "136.108\t62.5061\tSubalpine_Fir\tAdult\t19.9609\t15.8478\t0\t1\t0\t8\t4\n";
  oOut << "148.279\t52.0447\tSubalpine_Fir\tAdult\t19.9344\t15.8346\t0\t1\t0\t4.1\t4\n";
  oOut << "101.331\t97.9858\tSubalpine_Fir\tAdult\t19.9341\t15.8344\t0\t1\t0\t6.2\t4\n";
  oOut << "51.3794\t174.731\tBlack_Cottonwood\tAdult\t19.9167\t18.308\t1\t1\t2\t5.1\t1\n";
  oOut << "116.18\t177.57\tPaper_Birch\tAdult\t19.8331\t17.5445\t0\t0\t1\t7.8\t4\n";
  oOut << "96.3684\t139.05\tBlack_Cottonwood\tAdult\t19.7726\t18.232\t0\t1\t1\t1.6\t4\n";
  oOut << "43.4753\t80.7678\tAmabilis_Fir\tAdult\t19.7455\t21.742\t0\t1\t0\t1.7\t4\n";
  oOut << "46.1548\t115.314\tTrembling_Aspen\tAdult\t19.7021\t15.1438\t1\t1\t5\t5.7\t1\n";
  oOut << "93.335\t99.4446\tAmabilis_Fir\tAdult\t19.6741\t21.7047\t0\t1\t0\t1.6\t4\n";
  oOut << "17.0166\t87.1338\tSubalpine_Fir\tAdult\t19.631\t15.6819\t0\t1\t0\t10.5\t4\n";
  oOut << "180.914\t157.446\tHybrid_Spruce\tAdult\t19.5609\t12.2005\t0\t0\t1\t11.5\t4\n";
  oOut << "151.788\t147.571\tLodgepole_Pine\tAdult\t19.4974\t20.3852\t1\t0\t1\t5.2\t2\n";
  oOut << "189.703\t65.1428\tAmabilis_Fir\tAdult\t19.4406\t21.5818\t0\t0\t0\t6.7\t4\n";
  oOut << "141.443\t2.7771\tPaper_Birch\tAdult\t19.3518\t17.2901\t0\t1\t4\t5.7\t4\n";
  oOut << "48.3582\t180.725\tAmabilis_Fir\tAdult\t19.2517\t21.481\t0\t1\t0\t7.2\t4\n";
  oOut << "83.8867\t17.7673\tTrembling_Aspen\tAdult\t19.2203\t14.9033\t1\t0\t2\t0.4\t2\n";
  oOut << "163.367\t33.5144\tAmabilis_Fir\tAdult\t19.1476\t21.425\t0\t1\t0\t10.6\t4\n";
  oOut << "141.846\t25.4822\tTrembling_Aspen\tAdult\t19.082\t14.8336\t0\t0\t0\t2.5\t4\n";
  oOut << "143.713\t127.374\tBlack_Cottonwood\tAdult\t19.0558\t17.8462\t0\t0\t0\t4.6\t4\n";
  oOut << "48.0469\t89.1907\tWestern_Redcedar\tAdult\t18.9645\t21.2151\t0\t1\t4\t9.8\t4\n";
  oOut << "22.0459\t29.0833\tSubalpine_Fir\tAdult\t18.949\t15.3327\t0\t0\t0\t12\t4\n";
  oOut << "13.7634\t119.843\tBlack_Cottonwood\tAdult\t18.8617\t17.7396\t1\t1\t1\t3.6\t1\n";
  oOut << "91.1743\t12.4817\tSubalpine_Fir\tAdult\t18.8504\t15.2815\t0\t1\t0\t5.9\t4\n";
  oOut << "157.66\t81.9031\tAmabilis_Fir\tAdult\t18.8007\t21.2355\t0\t0\t0\t1.8\t4\n";
  oOut << "31.9702\t174.127\tBlack_Cottonwood\tAdult\t18.79\t17.6999\t0\t1\t3\t2.2\t4\n";
  oOut << "45.2087\t138.226\tHybrid_Spruce\tAdult\t18.7393\t11.8411\t1\t1\t3\t10.7\t1\n";
  oOut << "198.608\t44.8059\tAmabilis_Fir\tAdult\t18.6597\t21.1573\t0\t0\t0\t9.8\t4\n";
  oOut << "26.2146\t187.976\tPaper_Birch\tAdult\t18.653\t16.9116\t0\t1\t5\t1.6\t4\n";
  oOut << "67.2607\t183.795\tWestern_Hemlock\tAdult\t18.551\t21.0965\t1\t1\t4\t5.4\t1\n";
  oOut << "195.447\t85.9009\tTrembling_Aspen\tAdult\t18.4143\t14.4922\t0\t1\t3\t0.7\t4\n";
  oOut << "126.233\t110.962\tWestern_Redcedar\tAdult\t18.3704\t20.8837\t0\t0\t1\t12.5\t4\n";
  oOut << "121.405\t59.0332\tWestern_Redcedar\tAdult\t18.3563\t20.8757\t0\t1\t0\t12.1\t4\n";
  oOut << "47.76\t42.3767\tAmabilis_Fir\tAdult\t18.3115\t20.9612\t0\t1\t0\t1.2\t4\n";
  oOut << "82.428\t74.7192\tPaper_Birch\tAdult\t18.3057\t16.7193\t0\t0\t1\t11.6\t4\n";
  oOut << "173.615\t71.2341\tWestern_Redcedar\tAdult\t18.2758\t20.8298\t0\t1\t2\t1.1\t4\n";
  oOut << "45.7031\t148.761\tLodgepole_Pine\tAdult\t18.15\t19.6317\t1\t1\t0\t9.2\t1\n";
  oOut << "86.2854\t59.3201\tSubalpine_Fir\tAdult\t18.0988\t14.8854\t0\t0\t0\t4.9\t4\n";
  oOut << "109.131\t136.359\tPaper_Birch\tAdult\t18.0768\t16.591\t0\t1\t1\t11\t4\n";
  oOut << "33.4106\t131.671\tTrembling_Aspen\tAdult\t17.9541\t14.2525\t1\t1\t3\t1.8\t1\n";
  oOut << "89.1785\t100.226\tSubalpine_Fir\tAdult\t17.887\t14.7718\t0\t0\t0\t9.1\t4\n";
  oOut << "176.904\t15.1733\tAmabilis_Fir\tAdult\t17.8555\t20.6978\t0\t1\t0\t5.9\t4\n";
  oOut << "123.419\t23.3643\tAmabilis_Fir\tAdult\t17.7982\t20.6641\t0\t0\t0\t9.7\t4\n";
  oOut << "100.366\t197.04\tBlack_Cottonwood\tAdult\t17.7695\t17.1219\t0\t1\t2\t6.4\t4\n";
  oOut << "179.48\t100.677\tWestern_Redcedar\tAdult\t17.627\t20.4513\t0\t0\t0\t2.5\t4\n";
  oOut << "98.8159\t7.02515\tWestern_Redcedar\tAdult\t17.5543\t20.408\t0\t1\t3\t20.5\t4\n";
  oOut << "98.0896\t102.673\tWestern_Redcedar\tAdult\t17.4081\t20.3202\t0\t1\t4\t13.9\t4\n";
  oOut << "36.3525\t48.4375\tPaper_Birch\tAdult\t17.3901\t16.1986\t1\t1\t1\t1.9\t1\n";
  oOut << "63.4644\t38.6047\tWestern_Redcedar\tAdult\t17.3459\t20.2825\t1\t0\t4\t10\t2\n";
  oOut << "21.1365\t185.858\tWestern_Redcedar\tAdult\t17.3123\t20.2622\t1\t0\t0\t7.2\t2\n";
  oOut << "51.5808\t51.0254\tPaper_Birch\tAdult\t17.1558\t16.0621\t1\t1\t5\t4.4\t1\n";
  oOut << "141.724\t10.6445\tBlack_Cottonwood\tAdult\t17.1341\t16.7484\t0\t0\t0\t1.6\t4\n";
  oOut << "38.385\t119.684\tTrembling_Aspen\tAdult\t17.1301\t13.814\t1\t1\t4\t2.3\t1\n";
  oOut << "10.1807\t173.822\tTrembling_Aspen\tAdult\t17.1033\t13.7995\t1\t1\t1\t1.3\t1\n";
  oOut << "94.635\t61.8286\tPaper_Birch\tAdult\t17.0517\t16.0011\t0\t1\t1\t0.3\t4\n";
  oOut << "143.604\t57.1594\tWestern_Hemlock\tAdult\t17.0462\t20.2112\t0\t0\t2\t1.7\t4\n";
  oOut << "111.749\t160.437\tHybrid_Spruce\tAdult\t16.9574\t11.0364\t0\t1\t3\t3.6\t4\n";
  oOut << "179.663\t14.4348\tWestern_Hemlock\tAdult\t16.9019\t20.1217\t0\t1\t0\t11.5\t4\n";
  oOut << "133.496\t46.814\tAmabilis_Fir\tAdult\t16.8073\t20.0627\t0\t0\t0\t1.2\t4\n";
  oOut << "152.374\t171.399\tLodgepole_Pine\tAdult\t16.7822\t18.8063\t1\t1\t5\t9.6\t1\n";
  oOut << "105.298\t63.4949\tWestern_Redcedar\tAdult\t16.6772\t19.8689\t0\t1\t5\t20.1\t4\n";
  oOut << "148.651\t165.039\tLodgepole_Pine\tAdult\t16.6522\t18.7245\t1\t0\t3\t2.9\t2\n";
  oOut << "99.823\t86.7126\tBlack_Cottonwood\tAdult\t16.5344\t16.3859\t0\t1\t4\t0\t4\n";
  oOut << "180.072\t124.53\tHybrid_Spruce\tAdult\t16.5067\t10.8272\t0\t0\t1\t7.4\t4\n";
  oOut << "187.83\t128.894\tWestern_Hemlock\tAdult\t16.4716\t19.8503\t0\t1\t1\t5.6\t4\n";
  oOut << "194.012\t124.323\tTrembling_Aspen\tAdult\t16.3382\t13.381\t0\t0\t5\t8.1\t4\n";
  oOut << "112.61\t139.526\tPaper_Birch\tAdult\t16.2943\t15.5485\t0\t1\t3\t6.8\t4\n";
  oOut << "34.4727\t9.57642\tLodgepole_Pine\tAdult\t16.236\t18.4586\t0\t1\t5\t11.7\t4\n";
  oOut << "196.722\t2.92969\tWestern_Hemlock\tAdult\t16.2329\t19.6965\t0\t0\t2\t4.8\t4\n";
  oOut << "131.75\t156.403\tHybrid_Spruce\tAdult\t16.2299\t10.6976\t0\t0\t1\t8.5\t4\n";
  oOut << "130.17\t25.415\tWestern_Hemlock\tAdult\t16.1133\t19.6186\t0\t0\t2\t11.1\t4\n";
  oOut << "134.979\t186.09\tBlack_Cottonwood\tAdult\t15.8936\t15.9876\t0\t0\t0\t3.5\t4\n";
  oOut << "154.163\t144.855\tPaper_Birch\tAdult\t15.8466\t15.2742\t1\t0\t4\t11.2\t2\n";
  oOut << "86.2732\t125.58\tLodgepole_Pine\tAdult\t15.8063\t18.1775\t1\t0\t1\t0.3\t2\n";
  oOut << "52.6917\t36.6943\tPaper_Birch\tAdult\t15.704\t15.1858\t1\t1\t1\t4.8\t1\n";
  oOut << "0.738525\t167.12\tWestern_Hemlock\tAdult\t15.675\t19.328\t1\t1\t1\t11.6\t1\n";
  oOut << "118.372\t140.179\tBlack_Cottonwood\tAdult\t15.5627\t15.7774\t0\t0\t0\t0.5\t4\n";
  oOut << "42.6636\t114.465\tSubalpine_Fir\tAdult\t15.5597\t13.4667\t0\t0\t0\t7.6\t4\n";
  oOut << "145.813\t10.6445\tLodgepole_Pine\tAdult\t15.2737\t17.8197\t1\t1\t0\t5.5\t1\n";
  oOut << "108.905\t108.27\tLodgepole_Pine\tAdult\t15.2609\t17.8109\t0\t1\t2\t6.8\t4\n";
  oOut << "172.394\t189.41\tLodgepole_Pine\tAdult\t15.2454\t17.8003\t0\t1\t4\t7.7\t4\n";
  oOut << "145.709\t113.123\tPaper_Birch\tAdult\t15.058\t14.7784\t1\t0\t4\t0.1\t2\n";
  oOut << "157.025\t61.7126\tWestern_Redcedar\tAdult\t15.0421\t18.7819\t1\t0\t0\t20.7\t2\n";
  oOut << "189.758\t123.718\tHybrid_Spruce\tAdult\t15.0217\t10.1217\t0\t1\t0\t11.2\t4\n";
  oOut << "68.5852\t105.817\tBlack_Cottonwood\tAdult\t15.0159\t15.4231\t1\t1\t5\t8.8\t1\n";
  oOut << "172.986\t154.852\tPaper_Birch\tAdult\t14.9524\t14.7107\t0\t1\t0\t11.1\t4\n";
  oOut << "189.032\t180.627\tWestern_Redcedar\tAdult\t14.8737\t18.6635\t0\t0\t5\t14.5\t4\n";
  oOut << "102.74\t177.063\tWestern_Redcedar\tAdult\t14.7983\t18.6101\t0\t1\t2\t12\t4\n";
  oOut << "199.5\t7.44629\tHybrid_Spruce\tAdult\t14.7906\t10.0097\t0\t1\t5\t0.4\t4\n";
  oOut << "108.997\t165.833\tAmabilis_Fir\tAdult\t14.7821\t18.7104\t0\t1\t0\t11.3\t4\n";
  oOut << "36.2\t180.64\tTrembling_Aspen\tAdult\t14.7354\t12.469\t1\t1\t5\t3.5\t1\n";
  oOut << "46.9604\t64.7156\tPaper_Birch\tAdult\t14.628\t14.501\t0\t0\t0\t7.1\t4\n";
  oOut << "10.3027\t175.47\tAmabilis_Fir\tAdult\t14.5648\t18.5548\t0\t1\t0\t11.1\t4\n";
  oOut << "156.36\t5.97534\tBlack_Cottonwood\tAdult\t14.552\t15.1156\t1\t0\t1\t9.7\t2\n";
  oOut << "98.9075\t125.256\tWestern_Hemlock\tAdult\t14.5364\t18.5343\t0\t1\t2\t0.5\t4\n";
  oOut << "130.383\t8.25806\tLodgepole_Pine\tAdult\t14.5316\t17.3027\t0\t0\t4\t7.9\t4\n";
  oOut << "16.2048\t109.18\tWestern_Redcedar\tAdult\t14.4882\t18.3878\t1\t0\t1\t9.5\t2\n";
  oOut << "130.487\t129.401\tTrembling_Aspen\tAdult\t14.4733\t12.3151\t0\t0\t3\t5.7\t4\n";
  oOut << "76.7822\t154.895\tWestern_Hemlock\tAdult\t14.4083\t18.4414\t1\t0\t0\t10.7\t2\n";
  oOut << "139.703\t44.696\tWestern_Hemlock\tAdult\t14.3527\t18.4008\t0\t0\t2\t2.4\t4\n";
  oOut << "36.6211\t156.097\tSubalpine_Fir\tAdult\t14.35\t12.7447\t0\t1\t0\t1.6\t4\n";
  oOut << "174.414\t28.6072\tLodgepole_Pine\tAdult\t14.1321\t17.0155\t0\t0\t1\t4.9\t4\n";
  oOut << "105.475\t52.0325\tLodgepole_Pine\tAdult\t14.0408\t16.949\t0\t1\t5\t9.1\t4\n";
  oOut << "1.64795\t40.0024\tLodgepole_Pine\tAdult\t14.0027\t16.9211\t0\t0\t2\t2.5\t4\n";
  oOut << "25.6531\t98.3643\tBlack_Cottonwood\tAdult\t13.9066\t14.6769\t0\t0\t4\t9.5\t4\n";
  oOut << "26.0254\t196.973\tHybrid_Spruce\tAdult\t13.8882\t9.56588\t0\t0\t2\t6.3\t4\n";
  oOut << "190.71\t198.267\tWestern_Hemlock\tAdult\t13.8528\t18.0298\t0\t0\t3\t11.8\t4\n";
  oOut << "175.232\t20.4346\tTrembling_Aspen\tAdult\t13.7842\t11.9042\t0\t1\t5\t7.9\t4\n";
  oOut << "131.775\t156.055\tSubalpine_Fir\tAdult\t13.6221\t12.2952\t0\t0\t0\t0.7\t4\n";
  oOut << "194.482\t28.7781\tBlack_Cottonwood\tAdult\t13.6069\t14.4689\t0\t1\t4\t8.9\t4\n";
  oOut << "98.4802\t35.0342\tWestern_Hemlock\tAdult\t13.6017\t17.8388\t0\t1\t5\t9.4\t4\n";
  oOut << "169.58\t59.4971\tHybrid_Spruce\tAdult\t13.5617\t9.40287\t1\t1\t5\t2.7\t1\n";
  oOut << "17.0288\t190.979\tTrembling_Aspen\tAdult\t13.5339\t11.7526\t1\t0\t4\t10.7\t2\n";
  oOut << "159.143\t115.289\tBlack_Cottonwood\tAdult\t13.53\t14.4151\t1\t1\t0\t7.8\t1\n";
  oOut << "194.452\t178.802\tAmabilis_Fir\tAdult\t13.5193\t17.7755\t1\t0\t0\t7.4\t2\n";
  oOut << "113.94\t63.6169\tTrembling_Aspen\tAdult\t13.4805\t11.7201\t0\t1\t5\t1.5\t4\n";
  oOut << "129.694\t141.864\tWestern_Hemlock\tAdult\t13.4555\t17.7263\t0\t0\t2\t6.6\t4\n";
  oOut << "132.275\t144.196\tWestern_Hemlock\tAdult\t13.4448\t17.7181\t0\t0\t0\t6.5\t4\n";
  oOut << "12.5977\t57.0618\tLodgepole_Pine\tAdult\t13.3527\t16.4362\t1\t0\t0\t0.6\t2\n";
  oOut << "156.732\t37.8967\tAmabilis_Fir\tAdult\t13.2489\t17.5655\t0\t1\t0\t4.4\t4\n";
  oOut << "85.8704\t112.659\tAmabilis_Fir\tAdult\t13.2147\t17.5387\t0\t0\t0\t4.6\t4\n";
  oOut << "189.929\t35.6934\tSubalpine_Fir\tAdult\t13.1616\t12.0047\t0\t0\t0\t11\t4\n";
  oOut << "13.4766\t107.52\tHybrid_Spruce\tAdult\t13.0441\t9.14182\t0\t1\t0\t1.6\t4\n";
  oOut << "181.915\t108.014\tLodgepole_Pine\tAdult\t13.0212\t16.1821\t0\t1\t5\t10.9\t4\n";
  oOut << "57.074\t60.1135\tTrembling_Aspen\tAdult\t12.9913\t11.4196\t1\t1\t0\t1.7\t1\n";
  oOut << "28.8818\t117.932\tAmabilis_Fir\tAdult\t12.991\t17.3619\t0\t0\t0\t3.5\t4\n";
  oOut << "98.0591\t191.718\tWestern_Redcedar\tAdult\t12.9895\t17.2507\t0\t1\t2\t11.4\t4\n";
  oOut << "55.3345\t151.379\tHybrid_Spruce\tAdult\t12.9614\t9.0998\t1\t1\t0\t8.9\t1\n";
  oOut << "135.791\t101.55\tTrembling_Aspen\tAdult\t12.9474\t11.3923\t0\t0\t0\t11.7\t4\n";
  oOut << "116.656\t157.947\tWestern_Hemlock\tAdult\t12.9224\t17.3071\t0\t0\t3\t11.4\t4\n";
  oOut << "49.7803\t2.96021\tPaper_Birch\tAdult\t12.8821\t13.3217\t1\t1\t0\t9.1\t1\n";
  oOut << "55.7434\t180.17\tSubalpine_Fir\tAdult\t12.847\t11.8035\t0\t1\t0\t12\t4\n";
  oOut << "197.339\t91.4429\tWestern_Hemlock\tAdult\t12.8403\t17.2413\t0\t1\t3\t12\t4\n";
  oOut << "105.42\t190.289\tTrembling_Aspen\tAdult\t12.8107\t11.3073\t0\t1\t3\t10.3\t4\n";
  oOut << "54.0466\t167.749\tSubalpine_Fir\tAdult\t12.7856\t11.7641\t0\t1\t0\t10.8\t4\n";
  oOut << "28.0701\t92.3279\tLodgepole_Pine\tAdult\t12.6581\t15.8982\t0\t1\t4\t4.7\t4\n";
  oOut << "127.332\t33.3374\tHybrid_Spruce\tAdult\t12.6553\t8.94355\t1\t1\t4\t3.8\t1\n";
  oOut << "106.378\t90.6311\tPaper_Birch\tAdult\t12.612\t13.1315\t0\t1\t2\t7.6\t4\n";
  oOut << "162.048\t192.566\tWestern_Redcedar\tAdult\t12.5766\t16.9183\t1\t1\t2\t11.5\t1\n";
  oOut << "66.0461\t133.484\tAmabilis_Fir\tAdult\t12.5513\t17.0068\t0\t0\t0\t6.6\t4\n";
  oOut << "133.502\t126.794\tSubalpine_Fir\tAdult\t12.4371\t11.5381\t0\t0\t0\t1.4\t4\n";
  oOut << "51.6235\t172.089\tHybrid_Spruce\tAdult\t12.4313\t8.82846\t1\t1\t4\t0.6\t1\n";
  oOut << "87.3169\t198.584\tSubalpine_Fir\tAdult\t12.4268\t11.5314\t0\t0\t0\t2.5\t4\n";
  oOut << "140.826\t79.1626\tTrembling_Aspen\tAdult\t12.3938\t11.0458\t0\t1\t0\t7.6\t4\n";
  oOut << "164.972\t183.441\tSubalpine_Fir\tAdult\t12.2888\t11.4411\t0\t1\t0\t11.4\t4\n";
  oOut << "197.919\t47.9004\tHybrid_Spruce\tAdult\t12.247\t8.73329\t0\t0\t3\t10.3\t4\n";
  oOut << "176.855\t47.522\tPaper_Birch\tAdult\t12.2195\t12.8511\t0\t0\t0\t0.7\t4\n";
  oOut << "67.9443\t85.4553\tBlack_Cottonwood\tAdult\t12.1933\t13.4489\t1\t0\t2\t7.1\t2\n";
  oOut << "21.106\t151.831\tHybrid_Spruce\tAdult\t12.1777\t8.69741\t0\t0\t4\t2.3\t4\n";
  oOut << "32.8979\t186.365\tPaper_Birch\tAdult\t12.1338\t12.7892\t1\t0\t2\t7.9\t2\n";
  oOut << "159.839\t6.12793\tBlack_Cottonwood\tAdult\t12.1011\t13.3801\t1\t0\t3\t4.2\t2\n";
  oOut << "51.1841\t48.3032\tWestern_Redcedar\tAdult\t11.861\t16.3216\t1\t1\t1\t5.3\t1\n";
  oOut << "186.731\t26.825\tHybrid_Spruce\tAdult\t11.6092\t8.40065\t0\t0\t0\t3.5\t4\n";
  oOut << "42.7368\t6.03027\tLodgepole_Pine\tAdult\t11.554\t14.9988\t1\t1\t3\t1.8\t1\n";
  oOut << "134.082\t185.791\tSubalpine_Fir\tAdult\t11.488\t10.9085\t0\t0\t0\t6.9\t4\n";
  oOut << "23.761\t15.1794\tLodgepole_Pine\tAdult\t11.3443\t14.8216\t0\t1\t1\t3.3\t4\n";
  oOut << "64.4958\t181.256\tBlack_Cottonwood\tAdult\t11.1826\t12.6787\t1\t0\t5\t6.2\t2\n";
  oOut << "178.772\t161.377\tWestern_Redcedar\tAdult\t11.1206\t15.6755\t0\t0\t3\t13.4\t4\n";
  oOut << "101.44\t168.256\tLodgepole_Pine\tAdult\t11.0999\t14.6124\t0\t1\t0\t2.1\t4\n";
  oOut << "66.0767\t57.2632\tHybrid_Spruce\tAdult\t11.0693\t8.11504\t1\t0\t0\t9.8\t2\n";
  oOut << "116.486\t193.408\tPaper_Birch\tAdult\t10.9738\t11.93\t0\t1\t1\t6.8\t4\n";
  oOut << "47.5769\t36.0168\tBlack_Cottonwood\tAdult\t10.9082\t12.4635\t1\t1\t5\t6.8\t1\n";
  oOut << "47.0215\t151.764\tHybrid_Spruce\tAdult\t10.8939\t8.02139\t1\t1\t5\t7\t1\n";
  oOut << "197.449\t105.103\tLodgepole_Pine\tAdult\t10.715\t14.2772\t0\t1\t3\t9.3\t4\n";
  oOut << "169.672\t46.7957\tSubalpine_Fir\tAdult\t10.6885\t10.3615\t0\t1\t0\t6.3\t4\n";
  oOut << "65.2161\t184.155\tBlack_Cottonwood\tAdult\t10.6464\t12.2557\t1\t0\t0\t8.4\t2\n";
  oOut << "97.3572\t194.775\tWestern_Redcedar\tAdult\t10.6213\t15.2227\t0\t1\t2\t14.1\t4\n";
  oOut << "90.4602\t47.4609\tWestern_Hemlock\tAdult\t10.5792\t15.288\t0\t1\t0\t8.8\t4\n";
  oOut << "116.528\t112.451\tAmabilis_Fir\tAdult\t10.5423\t15.2538\t0\t0\t0\t6.4\t4\n";
  oOut << "132.764\t44.5862\tHybrid_Spruce\tAdult\t10.5179\t7.81939\t0\t0\t0\t3.9\t4\n";
  oOut << "137.219\t70.6909\tSubalpine_Fir\tAdult\t10.4932\t10.2255\t0\t1\t0\t10\t4\n";
  oOut << "122.552\t16.3757\tWestern_Hemlock\tAdult\t10.4282\t15.1473\t0\t0\t2\t0.9\t4\n";
  oOut << "140.747\t171.735\tWestern_Redcedar\tAdult\t10.3741\t14.9933\t0\t0\t3\t11\t4\n";
  oOut << "35.8765\t168.518\tAmabilis_Fir\tAdult\t10.3006\t15.0275\t0\t1\t0\t3.5\t4\n";
  oOut << "152.411\t103.461\tTrembling_Aspen\tAdult\t10.2267\t9.62595\t1\t0\t4\t10\t2\n";
  oOut << "147.51\t101.953\tWestern_Hemlock\tAdult\t10.1794\t14.9128\t1\t1\t2\t2.6\t1\n";
  oOut << "106.128\t53.6987\tTrembling_Aspen\tAdult\t10.116\t9.55058\t0\t1\t4\t8.7\t4\n";
  oOut << "46.1121\t174.646\tHybrid_Spruce\tAdult\t10.1001\t7.59275\t1\t1\t1\t2.8\t1\n";
  oOut << "48.0225\t85.2478\tTrembling_Aspen\tAdult\t10.0641\t9.51519\t1\t1\t0\t0.4\t1\n";
  oOut << "84.2224\t112.439\tWestern_Hemlock\tAdult\t10.0235\t14.7638\t1\t0\t0\t6\t2\n";
  oOut << "120.709\t69.2139\tHybrid_Spruce\tSapling\t9.98407\t7.5294\t0\t0\t0\t9\t0\n";
  oOut << "164.307\t34.2468\tAmabilis_Fir\tSapling\t9.897\t14.6419\t0\t0\t0\t5\t0\n";
  oOut << "129.12\t113.702\tSubalpine_Fir\tSapling\t9.88025\t9.79255\t0\t0\t0\t8.2\t0\n";
  oOut << "54.8035\t99.3835\tSubalpine_Fir\tSapling\t9.78549\t9.72478\t0\t1\t0\t6.7\t0\n";
  oOut << "26.7334\t116.461\tHybrid_Spruce\tSapling\t9.74869\t7.40033\t0\t0\t1\t0.5\t0\n";
  oOut << "189.734\t42.5415\tWestern_Hemlock\tSapling\t9.7204\t14.4701\t0\t1\t0\t3.8\t0\n";
  oOut << "33.0139\t196.179\tTrembling_Aspen\tSapling\t9.6748\t9.24764\t1\t1\t5\t0\t0\n";
  oOut << "16.2354\t85.6934\tLodgepole_Pine\tSapling\t9.67151\t13.331\t0\t1\t1\t13.5\t0\n";
  oOut << "135.26\t144.403\tTrembling_Aspen\tSapling\t9.63443\t9.21969\t0\t0\t2\t8.7\t0\n";
  oOut << "110.699\t102.142\tWestern_Hemlock\tSapling\t9.6152\t14.3668\t0\t1\t4\t8.6\t0\n";
  oOut << "45.5078\t167.48\tAmabilis_Fir\tSapling\t9.54517\t14.2977\t0\t1\t0\t3.4\t0\n";
  oOut << "170.459\t50.4333\tPaper_Birch\tSapling\t9.54105\t10.8092\t1\t0\t1\t1.1\t0\n";
  oOut << "106.915\t10.26\tHybrid_Spruce\tSapling\t9.52429\t7.27659\t0\t1\t1\t5.1\t0\n";
  oOut << "14.9109\t199.915\tTrembling_Aspen\tSapling\t9.48557\t9.11632\t1\t1\t5\t11.1\t0\n";
  oOut << "114.716\t93.7927\tAmabilis_Fir\tSapling\t9.44904\t14.2023\t0\t1\t0\t11\t0\n";
  oOut << "178.912\t192.242\tPaper_Birch\tSapling\t9.4397\t10.7274\t0\t0\t3\t4.9\t0\n";
  oOut << "49.8474\t13.6292\tAmabilis_Fir\tSapling\t9.38339\t14.1368\t0\t1\t0\t0.2\t0\n";
  oOut << "14.7827\t50.8606\tWestern_Hemlock\tSapling\t9.37241\t14.1259\t0\t0\t0\t5\t0\n";
  oOut << "172.07\t42.9016\tTrembling_Aspen\tSapling\t9.2337\t8.94026\t0\t1\t2\t3.1\t0\n";
  oOut << "168.121\t136.176\tHybrid_Spruce\tSapling\t9.18207\t7.08657\t1\t1\t1\t11.7\t0\n";
  oOut << "44.5557\t191.833\tBlack_Cottonwood\tSapling\t9.14581\t11.0161\t1\t1\t3\t11.9\t0\n";
  oOut << "113.666\t175.903\tBlack_Cottonwood\tSapling\t9.13098\t11.0034\t0\t1\t3\t7.6\t0\n";
  oOut << "71.5698\t29.4067\tWestern_Redcedar\tSapling\t9.12576\t13.7789\t0\t1\t5\t5\t0\n";
  oOut << "166.931\t109.326\tTrembling_Aspen\tSapling\t9.09665\t8.84383\t1\t0\t3\t1.7\t0\n";
  oOut << "108.478\t153.021\tBlack_Cottonwood\tSapling\t9.06946\t10.9507\t0\t1\t1\t2.1\t0\n";
  oOut << "80.8533\t11.792\tSubalpine_Fir\tSapling\t9.0137\t9.16427\t0\t0\t2\t1.5\t0\n";
  oOut << "199.341\t146.558\tAmabilis_Fir\tSapling\t9.01068\t13.7599\t1\t1\t0\t10.5\t0\n";
  oOut << "163.055\t177.161\tTrembling_Aspen\tSapling\t8.86896\t8.68265\t1\t0\t4\t8.7\t0\n";
  oOut << "84.5459\t21.6858\tHybrid_Spruce\tSapling\t8.70361\t6.81825\t1\t0\t0\t3\t0\n";
  oOut << "96.9482\t194.91\tPaper_Birch\tSapling\t8.67285\t10.0965\t0\t0\t3\t9.3\t0\n";
  oOut << "113.251\t74.4202\tTrembling_Aspen\tSapling\t8.61462\t8.50115\t0\t1\t5\t3.6\t0\n";
  oOut << "127.295\t123.126\tPaper_Birch\tSapling\t8.56546\t10.0066\t0\t0\t5\t4\t0\n";
  oOut << "66.4734\t173.901\tWestern_Hemlock\tSapling\t8.48828\t13.2166\t1\t1\t2\t7.3\t0\n";
  oOut << "29.3213\t171.094\tAmabilis_Fir\tSapling\t8.46329\t13.1901\t0\t0\t0\t7.2\t0\n";
  oOut << "84.3872\t111.719\tLodgepole_Pine\tSapling\t8.40561\t12.1065\t1\t0\t2\t1.3\t0\n";
  oOut << "193.823\t140.167\tWestern_Redcedar\tSapling\t8.37155\t12.9981\t0\t1\t4\t10.7\t0\n";
  oOut << "178.711\t82.0801\tLodgepole_Pine\tSapling\t8.35233\t12.053\t0\t0\t3\t7.1\t0\n";
  oOut << "8.73413\t3.07617\tSubalpine_Fir\tSapling\t8.3353\t8.6588\t0\t0\t0\t0.9\t0\n";
  oOut << "67.3645\t97.4365\tWestern_Redcedar\tSapling\t8.3309\t12.9549\t1\t0\t2\t9.1\t0\n";
  oOut << "5.07812\t35.9253\tHybrid_Spruce\tSapling\t8.2897\t6.58358\t0\t0\t5\t0.6\t0\n";
  oOut << "23.5413\t71.1609\tLodgepole_Pine\tSapling\t8.28915\t11.9894\t1\t1\t0\t4\t0\n";
  oOut << "110.089\t113.116\tSubalpine_Fir\tSapling\t8.27817\t8.61567\t0\t1\t0\t9.3\t0\n";
  oOut << "38.6597\t11.0229\tTrembling_Aspen\tSapling\t8.27734\t8.25809\t1\t1\t2\t8.7\t0\n";
  oOut << "39.4165\t42.334\tWestern_Hemlock\tSapling\t8.22571\t12.9366\t1\t1\t3\t11.8\t0\n";
  oOut << "154.718\t161.206\tHybrid_Spruce\tSapling\t8.12518\t6.48965\t1\t1\t3\t11.3\t0\n";
  oOut << "128.308\t80.2185\tBlack_Cottonwood\tSapling\t8.0719\t10.0761\t0\t0\t1\t1.7\t0\n";
  oOut << "47.1985\t67.0959\tWestern_Hemlock\tSapling\t8.04691\t12.7433\t1\t1\t3\t3.6\t0\n";
  oOut << "4.24194\t129.846\tBlack_Cottonwood\tSapling\t8.0274\t10.0362\t1\t0\t1\t12.6\t0\n";
  oOut << "27.0691\t58.2092\tAmabilis_Fir\tSapling\t7.98428\t12.6751\t0\t1\t0\t0.6\t0\n";
  oOut << "99.115\t25.6531\tHybrid_Spruce\tSapling\t7.94199\t6.38461\t0\t1\t5\t9.6\t0\n";
  oOut << "157.77\t1.48315\tBlack_Cottonwood\tSapling\t7.88678\t9.90947\t1\t0\t4\t9\t0\n";
  oOut << "34.6008\t75.4761\tPaper_Birch\tSapling\t7.81317\t9.36476\t0\t0\t5\t6.9\t0\n";
  oOut << "151.624\t177.869\tWestern_Hemlock\tSapling\t7.75879\t12.4272\t1\t1\t4\t11.9\t0\n";
  oOut << "22.9187\t140.265\tWestern_Hemlock\tSapling\t7.72116\t12.3855\t1\t1\t4\t4.2\t0\n";
  oOut << "45.0439\t166.736\tPaper_Birch\tSapling\t7.69644\t9.26334\t1\t1\t5\t1\t0\n";
  oOut << "67.4255\t15.8325\tWestern_Redcedar\tSapling\t7.66266\t12.23\t1\t0\t2\t6.1\t0\n";
  oOut << "139.685\t47.9431\tSubalpine_Fir\tSapling\t7.64508\t8.13194\t0\t1\t0\t5.2\t0\n";
  oOut << "133.539\t122.156\tWestern_Redcedar\tSapling\t7.64206\t12.2071\t0\t0\t4\t24.9\t0\n";
  oOut << "78.2898\t58.9966\tSubalpine_Fir\tSapling\t7.57779\t8.07988\t0\t0\t0\t0\t0\n";
  oOut << "47.3572\t166.418\tTrembling_Aspen\tSapling\t7.51407\t7.69782\t1\t1\t0\t9.3\t0\n";
  oOut << "150.079\t187.64\tWestern_Redcedar\tSapling\t7.47205\t12.0176\t1\t1\t5\t13.7\t0\n";
  oOut << "110.254\t31.5369\tPaper_Birch\tSapling\t7.39542\t8.99951\t0\t1\t0\t3.7\t0\n";
  oOut << "117.633\t111.108\tPaper_Birch\tSapling\t7.25671\t8.87681\t0\t0\t4\t0.7\t0\n";
  oOut << "110.876\t145.605\tBlack_Cottonwood\tSapling\t7.06693\t9.15442\t0\t1\t4\t8.3\t0\n";
  oOut << "124.969\t189.423\tWestern_Redcedar\tSapling\t7.05704\t11.5463\t0\t0\t3\t20.1\t0\n";
  oOut << "81.7261\t48.0835\tWestern_Hemlock\tSapling\t6.99496\t11.561\t0\t1\t0\t9.6\t0\n";
  oOut << "63.0615\t5.57251\tLodgepole_Pine\tSapling\t6.9892\t10.6294\t0\t1\t4\t9.5\t0\n";
  oOut << "179.816\t199.554\tWestern_Redcedar\tSapling\t6.98535\t11.4637\t0\t0\t5\t1.7\t0\n";
  oOut << "173.889\t25.5005\tAmabilis_Fir\tSapling\t6.92795\t11.4829\t0\t1\t0\t4.2\t0\n";
  oOut << "83.5083\t33.606\tBlack_Cottonwood\tSapling\t6.9068\t9.00367\t1\t0\t3\t11.1\t0\n";
  oOut << "10.4248\t64.4287\tWestern_Redcedar\tSapling\t6.80682\t11.2562\t0\t0\t5\t7.3\t0\n";
  oOut << "57.1167\t43.6707\tTrembling_Aspen\tSapling\t6.72058\t7.10007\t1\t1\t2\t8.9\t0\n";
  oOut << "121.002\t91.2903\tTrembling_Aspen\tSapling\t6.6868\t7.07426\t0\t0\t4\t6\t0\n";
  oOut << "80.9875\t125.586\tTrembling_Aspen\tSapling\t6.56732\t6.98278\t1\t0\t2\t0.6\t0\n";
  oOut << "91.6382\t69.7205\tLodgepole_Pine\tSapling\t6.5448\t10.1413\t0\t1\t0\t11.2\t0\n";
  oOut << "15.9302\t116.821\tHybrid_Spruce\tSapling\t6.53436\t5.56172\t1\t1\t2\t10.5\t0\n";
  oOut << "125.256\t11.2305\tTrembling_Aspen\tSapling\t6.41489\t6.86553\t0\t0\t1\t11.1\t0\n";
  oOut << "128.455\t81.2683\tLodgepole_Pine\tSapling\t6.38962\t9.96792\t0\t0\t4\t9.8\t0\n";
  oOut << "157.703\t2.66724\tPaper_Birch\tSapling\t6.38824\t8.0921\t1\t0\t0\t5.3\t0\n";
  oOut << "10.8582\t98.8159\tWestern_Hemlock\tSapling\t6.27426\t10.7044\t1\t1\t2\t11.5\t0\n";
  oOut << "179.309\t42.7917\tWestern_Redcedar\tSapling\t6.25092\t10.5953\t0\t1\t4\t14\t0\n";
  oOut << "63.2019\t153.76\tPaper_Birch\tSapling\t6.18527\t7.90454\t1\t0\t5\t11.8\t0\n";
  oOut << "129.095\t10.0342\tWestern_Redcedar\tSapling\t6.12265\t10.4396\t0\t0\t3\t22.6\t0\n";
  oOut << "195.99\t73.5718\tPaper_Birch\tSapling\t6.09573\t7.82129\t0\t1\t2\t1.9\t0\n";
  oOut << "184.003\t99.0662\tSubalpine_Fir\tSapling\t6.07596\t6.88528\t0\t0\t0\t2.7\t0\n";
  oOut << "105.353\t62.1765\tSubalpine_Fir\tSapling\t6.05811\t6.8707\t0\t1\t0\t0\t0\n";
  oOut << "129.236\t170.416\tSubalpine_Fir\tSapling\t5.98972\t6.81474\t0\t0\t0\t6.1\t0\n";
  oOut << "138.654\t144.189\tBlack_Cottonwood\tSapling\t5.89359\t8.02419\t0\t1\t3\t3.6\t0\n";
  oOut << "96.7957\t119.391\tWestern_Hemlock\tSapling\t5.87793\t10.2166\t0\t1\t1\t1.9\t0\n";
  oOut << "39.5935\t14.3677\tPaper_Birch\tSapling\t5.76971\t7.51552\t1\t1\t4\t3.4\t0\n";
  oOut << "58.0688\t60.5835\tSubalpine_Fir\tSapling\t5.76257\t6.62791\t0\t1\t2\t1.1\t0\n";
  oOut << "179.285\t36.8896\tPaper_Birch\tSapling\t5.61646\t7.37032\t0\t0\t4\t4.5\t0\n";
  oOut << "127.637\t199.677\tSubalpine_Fir\tSapling\t5.60272\t6.49553\t0\t0\t0\t6.7\t0\n";
  oOut << "100.848\t33.0505\tBlack_Cottonwood\tSapling\t5.58624\t7.71815\t1\t0\t2\t12\t0\n";
  oOut << "49.0234\t150.153\tBlack_Cottonwood\tSapling\t5.52142\t7.65306\t1\t1\t1\t5.3\t0\n";
  oOut << "106.183\t121.539\tWestern_Redcedar\tSapling\t5.4816\t9.64214\t0\t1\t1\t13.6\t0\n";
  oOut << "6.5979\t115.466\tBlack_Cottonwood\tSapling\t5.32532\t7.45498\t1\t1\t4\t2.8\t0\n";
  oOut << "20.8923\t10.6079\tPaper_Birch\tSapling\t5.31927\t7.0861\t0\t0\t3\t1.4\t0\n";
  oOut << "48.4192\t126.709\tWestern_Redcedar\tSapling\t5.28055\t9.38541\t0\t1\t5\t7.6\t0\n";
  oOut << "63.3423\t143.262\tTrembling_Aspen\tSapling\t5.25363\t5.95247\t1\t0\t0\t0.1\t0\n";
  oOut << "7.05566\t26.1169\tWestern_Hemlock\tSapling\t5.216\t9.37415\t0\t1\t1\t3.4\t0\n";
  oOut << "90.1855\t89.4592\tHybrid_Spruce\tSapling\t5.16849\t4.73584\t1\t0\t5\t8.2\t0\n";
  oOut << "139.557\t140.192\tAmabilis_Fir\tSapling\t5.12097\t9.25029\t1\t1\t0\t6.2\t0\n";
  oOut << "53.9185\t142.413\tLodgepole_Pine\tSapling\t5.11191\t8.48207\t1\t1\t5\t11.7\t0\n";
  oOut << "182.184\t129.919\tSubalpine_Fir\tSapling\t4.99243\t5.98319\t0\t1\t0\t0\t0\n";
  oOut << "26.5686\t122.839\tWestern_Hemlock\tSapling\t4.90399\t8.9647\t1\t0\t5\t2.1\t0\n";
  oOut << "173.914\t81.2988\tSubalpine_Fir\tSapling\t4.77957\t5.80187\t0\t0\t0\t11.3\t0\n";
  oOut << "135.852\t186.719\tPaper_Birch\tSapling\t4.71365\t6.49578\t0\t1\t1\t4.2\t0\n";
  oOut << "184.509\t15.5151\tAmabilis_Fir\tSapling\t4.68564\t8.67333\t0\t0\t0\t10.9\t0\n";
  oOut << "151.453\t60.4126\tPaper_Birch\tSapling\t4.65955\t6.44231\t1\t0\t5\t0.1\t0\n";
  oOut << "172.485\t27.6489\tWestern_Redcedar\tSapling\t4.6546\t8.56518\t0\t1\t1\t14.7\t0\n";
  oOut << "168.451\t130.634\tSubalpine_Fir\tSapling\t4.64279\t5.68464\t0\t0\t0\t1.5\t0\n";
  oOut << "0.0671387\t155.975\tSubalpine_Fir\tSapling\t4.62604\t5.67024\t0\t0\t0\t7.6\t0\n";
  oOut << "177.435\t154.828\tPaper_Birch\tSapling\t4.55161\t6.33526\t0\t0\t2\t3.9\t0\n";
  oOut << "15.3992\t184.686\tHybrid_Spruce\tSapling\t4.49612\t4.31909\t1\t0\t4\t14.7\t0\n";
  oOut << "156.14\t49.0234\tAmabilis_Fir\tSapling\t4.48322\t8.39962\t0\t1\t0\t2.2\t0\n";
  oOut << "84.7778\t71.5393\tAmabilis_Fir\tSapling\t4.46838\t8.37943\t0\t0\t0\t3.8\t0\n";
  oOut << "28.5889\t119.635\tHybrid_Spruce\tSapling\t4.46454\t4.29935\t1\t0\t5\t6.5\t0\n";
  oOut << "154.218\t50.7324\tWestern_Hemlock\tSapling\t4.41263\t8.30335\t1\t1\t3\t3.2\t0\n";
  oOut << "49.6765\t185.339\tLodgepole_Pine\tSapling\t4.40961\t7.61893\t0\t1\t4\t6.1\t0\n";
  oOut << "140.363\t85.2173\tHybrid_Spruce\tSapling\t4.39038\t4.25293\t0\t0\t4\t5.9\t0\n";
  oOut << "163.336\t118.28\tTrembling_Aspen\tSapling\t4.1929\t5.08699\t1\t1\t4\t7.3\t0\n";
  oOut << "177.246\t175.11\tWestern_Hemlock\tSapling\t4.15665\t7.95062\t0\t1\t4\t11.9\t0\n";
  oOut << "174.658\t66.0217\tPaper_Birch\tSapling\t4.15335\t5.9361\t0\t1\t4\t8.2\t0\n";
  oOut << "110.284\t29.1565\tPaper_Birch\tSapling\t4.13989\t5.9225\t0\t1\t4\t8.4\t0\n";
  oOut << "151.013\t115.509\tLodgepole_Pine\tSapling\t4.13083\t7.26679\t1\t1\t5\t7.4\t0\n";
  oOut << "70.6238\t155.92\tSubalpine_Fir\tSapling\t4.07947\t5.19582\t0\t0\t0\t10.6\t0\n";
  oOut << "79.2786\t119.672\tTrembling_Aspen\tSapling\t4.0553\t4.97246\t1\t0\t5\t5.3\t0\n";
  oOut << "34.9731\t135.425\tLodgepole_Pine\tSapling\t3.9935\t7.09128\t0\t0\t0\t3.8\t0\n";
  oOut << "84.6741\t130.225\tBlack_Cottonwood\tSapling\t3.86002\t5.91829\t1\t0\t1\t7.7\t0\n";
  oOut << "173.645\t45.1538\tTrembling_Aspen\tSapling\t3.62161\t4.60803\t0\t0\t3\t5\t0\n";
  oOut << "88.678\t77.5269\tSubalpine_Fir\tSapling\t3.52383\t4.70404\t0\t0\t0\t3.1\t0\n";
  oOut << "116.187\t45.4407\tLodgepole_Pine\tSapling\t3.4332\t6.36108\t0\t0\t5\t10\t0\n";
  oOut << "82.2205\t159.558\tHybrid_Spruce\tSapling\t3.43292\t3.64603\t1\t0\t2\t9.3\t0\n";
  oOut << "81.9031\t109.406\tBlack_Cottonwood\tSapling\t3.42908\t5.44673\t1\t0\t1\t2.8\t0\n";
  oOut << "110.388\t114.319\tWestern_Hemlock\tSapling\t3.40848\t6.88644\t0\t1\t5\t2.7\t0\n";
  oOut << "34.8328\t78.3508\tWestern_Redcedar\tSapling\t3.40518\t6.8291\t1\t0\t4\t6.2\t0\n";
  oOut << "156.238\t94.2017\tHybrid_Spruce\tSapling\t3.3324\t3.58148\t1\t1\t5\t8.6\t0\n";
  oOut << "115.497\t107.568\tHybrid_Spruce\tSapling\t3.31647\t3.57124\t0\t1\t4\t8.8\t0\n";
  oOut << "187.518\t38.5193\tLodgepole_Pine\tSapling\t3.17722\t6.01978\t0\t0\t1\t3.1\t0\n";
  oOut << "83.8135\t146.863\tBlack_Cottonwood\tSapling\t3.14371\t5.12939\t1\t0\t1\t1.2\t0\n";
  oOut << "51.3123\t173.602\tAmabilis_Fir\tSapling\t3.11761\t6.459\t0\t1\t0\t5.2\t0\n";
  oOut << "116.138\t164.539\tSubalpine_Fir\tSapling\t3.08768\t4.31119\t0\t0\t0\t0\t0\n";
  oOut << "75.6226\t176.874\tLodgepole_Pine\tSapling\t3.02423\t5.81345\t1\t0\t1\t6.5\t0\n";
  oOut << "157.587\t163.226\tHybrid_Spruce\tSapling\t2.95007\t3.33456\t1\t1\t2\t7.7\t0\n";
  oOut << "47.0642\t31.2744\tAmabilis_Fir\tSapling\t2.91272\t6.15315\t0\t1\t0\t3.9\t0\n";
  oOut << "58.252\t145.276\tPaper_Birch\tSapling\t2.91025\t4.64634\t1\t1\t4\t4\t0\n";
  oOut << "154.425\t169.305\tAmabilis_Fir\tSapling\t2.83994\t6.04355\t1\t1\t0\t0.5\t0\n";
  oOut << "90.0757\t102.545\tLodgepole_Pine\tSapling\t2.8306\t5.54976\t1\t0\t5\t2.3\t0\n";
  oOut << "27.4841\t157.66\tLodgepole_Pine\tSapling\t2.82016\t5.53547\t1\t1\t5\t10.6\t0\n";
  oOut << "92.0227\t33.3191\tWestern_Redcedar\tSapling\t2.8078\t5.95003\t0\t1\t3\t10.4\t0\n";
  oOut << "144.824\t119.379\tWestern_Redcedar\tSapling\t2.79517\t5.93108\t0\t1\t4\t24.2\t0\n";
  oOut << "125.818\t143.011\tWestern_Hemlock\tSapling\t2.72595\t5.8709\t0\t0\t5\t1\t0\n";
  oOut << "26.1353\t12.0361\tWestern_Redcedar\tSapling\t2.71552\t5.81128\t0\t1\t1\t5.5\t0\n";
  oOut << "170.673\t140.796\tLodgepole_Pine\tSapling\t2.70782\t5.38108\t1\t1\t0\t2.9\t0\n";
  oOut << "187.701\t35.4858\tTrembling_Aspen\tSapling\t2.66635\t3.78649\t0\t1\t5\t8.5\t0\n";
  oOut << "183.929\t64.801\tLodgepole_Pine\tSapling\t2.5661\t5.18491\t0\t1\t0\t9.3\t0\n";
  oOut << "48.2239\t37.677\tAmabilis_Fir\tSapling\t2.51309\t5.54515\t0\t1\t0\t8.7\t0\n";
  oOut << "127.039\t121.68\tSubalpine_Fir\tSapling\t2.50513\t3.77695\t0\t0\t0\t0.4\t0\n";
  oOut << "188.025\t81.7993\tAmabilis_Fir\tSapling\t2.33759\t5.27325\t0\t0\t0\t3\t0\n";
  oOut << "128.455\t168.915\tLodgepole_Pine\tSapling\t2.23047\t4.71409\t0\t0\t0\t0.3\t0\n";
  oOut << "167.572\t90.1428\tBlack_Cottonwood\tSapling\t2.10028\t3.93376\t1\t1\t0\t5.4\t0\n";
  oOut << "137.091\t99.7742\tHybrid_Spruce\tSapling\t2.01047\t2.71787\t0\t0\t2\t9.5\t0\n";
  oOut << "101.41\t31.8481\tAmabilis_Fir\tSapling\t1.92203\t4.61735\t0\t1\t0\t9.4\t0\n";
  oOut << "147.186\t92.2607\tWestern_Hemlock\tSapling\t1.85172\t4.50467\t1\t0\t1\t10.8\t0\n";
  oOut << "121.1\t56.2927\tHybrid_Spruce\tSapling\t1.81134\t2.58535\t0\t0\t4\t2.9\t0\n";
  oOut << "195.807\t31.6833\tTrembling_Aspen\tSapling\t1.76712\t2.98886\t0\t1\t5\t6\t0\n";
  oOut << "138.226\t100.714\tBlack_Cottonwood\tSapling\t1.70724\t3.46864\t0\t0\t1\t5.3\t0\n";
  oOut << "20.5322\t7.1228\tBlack_Cottonwood\tSapling\t1.69516\t3.45421\t0\t0\t3\t10.6\t0\n";
  oOut << "97.6379\t15.033\tWestern_Redcedar\tSapling\t1.67456\t4.18973\t0\t1\t2\t21.7\t0\n";
  oOut << "195.874\t177.679\tAmabilis_Fir\tSapling\t1.64572\t4.17164\t1\t1\t0\t6.3\t0\n";
  oOut << "120.996\t129.846\tWestern_Redcedar\tSapling\t1.61716\t4.09721\t0\t0\t1\t10.1\t0\n";
  oOut << "186.493\t180.328\tTrembling_Aspen\tSapling\t1.42545\t2.67947\t0\t1\t5\t0\t0\n";
  oOut << "48.8098\t59.1309\tAmabilis_Fir\tSapling\t1.38947\t3.75128\t0\t1\t0\t7.3\t0\n";
  oOut << "173.56\t24.4141\tHybrid_Spruce\tSapling\t1.37683\t2.29396\t0\t0\t4\t2.1\t0\n";
  oOut << "192.053\t32.5745\tBlack_Cottonwood\tSapling\t1.33481\t3.02024\t0\t1\t5\t10.1\t0\n";
  oOut << "71.0205\t80.9814\tWestern_Hemlock\tSapling\t1.22824\t3.48331\t1\t0\t4\t5.8\t0\n";
  oOut << "27.9236\t1.36719\tBlack_Cottonwood\tSapling\t1.17688\t2.82781\t0\t0\t2\t3.5\t0\n";
  oOut << "116.29\t108.911\tLodgepole_Pine\tSapling\t1.14777\t3.13354\t1\t0\t4\t9.5\t0\n";
  oOut << "0.323486\t81.9641\tWestern_Hemlock\tSapling\t1.14694\t3.34715\t0\t1\t4\t0.9\t0\n";
  oOut << "24.6094\t169.244\tAmabilis_Fir\tSapling\t0.99295\t3.08732\t0\t1\t0\t5.5\t0\n";
  oOut << "55.2551\t152.972\tPaper_Birch\tSapling\t0.990845\t2.51782\t1\t1\t2\t6.2\t0\n";
  oOut << "193.097\t43.7378\tWestern_Redcedar\tSapling\t0.981842\t3.05084\t0\t0\t3\t12.7\t0\n";
  oOut << "23.0591\t106.61\tWestern_Redcedar\tSapling\t0.977722\t3.04392\t0\t1\t3\t5.4\t0\n";
  oOut << "189.349\t191.113\tWestern_Redcedar\tSapling\t0.967651\t3.027\t0\t1\t4\t3.7\t0\n";
  oOut << "66.5344\t16.9006\tHybrid_Spruce\tSapling\t0.961304\t2.0124\t0\t1\t3\t11.4\t0\n";
  oOut << "106.824\t153.51\tHybrid_Spruce\tSapling\t0.960297\t2.01171\t0\t1\t3\t7.2\t0\n";
  oOut << "59.0881\t97.7112\tSubalpine_Fir\tSapling\t0.952972\t2.29863\t0\t1\t0\t11.7\t0\n";
  oOut << "146.277\t30.3589\tHybrid_Spruce\tSapling\t0.951935\t2.00601\t1\t0\t4\t8.4\t0\n";
  oOut << "65.5029\t78.3325\tLodgepole_Pine\tSapling\t0.939056\t2.81769\t0\t0\t0\t7.4\t0\n";
  oOut << "62.5671\t92.4377\tAmabilis_Fir\tSapling\t0.938507\t2.99485\t0\t0\t0\t6.7\t0\n";
  oOut << "78.9185\t190.161\tSubalpine_Fir\tSapling\t0.935028\t2.28106\t0\t0\t0\t9.8\t0\n";
  oOut << "178.247\t143.713\tAmabilis_Fir\tSapling\t0.932129\t2.984\t1\t1\t0\t7.2\t0\n";
  oOut << "74.3774\t74.4324\tBlack_Cottonwood\tSapling\t0.927856\t2.52161\t1\t0\t5\t5.8\t0\n";
  oOut << "178.894\t66.1438\tAmabilis_Fir\tSapling\t0.927246\t2.97569\t0\t0\t0\t9.9\t0\n";
  oOut << "191.888\t9.43604\tAmabilis_Fir\tSapling\t0.919647\t2.96275\t0\t0\t0\t6.3\t0\n";
  oOut << "61.499\t105.438\tTrembling_Aspen\tSapling\t0.917542\t2.21299\t1\t1\t0\t2.5\t0\n";
  oOut << "33.6365\t136.755\tLodgepole_Pine\tSapling\t0.909607\t2.77283\t1\t0\t2\t0.3\t0\n";
  oOut << "46.405\t169.824\tSubalpine_Fir\tSapling\t0.899292\t2.24604\t0\t1\t0\t7.6\t0\n";
  oOut << "100.427\t85.7544\tBlack_Cottonwood\tSapling\t0.874084\t2.45504\t1\t1\t5\t2.9\t0\n";
  oOut << "83.075\t84.6436\tBlack_Cottonwood\tSapling\t0.865417\t2.44429\t1\t0\t4\t8.1\t0\n";
  oOut << "71.8506\t99.0906\tPaper_Birch\tSapling\t0.863373\t2.37029\t1\t1\t4\t6.9\t0\n";
  oOut << "167.108\t63.3179\tTrembling_Aspen\tSapling\t0.861176\t2.16073\t1\t1\t5\t0\t0\n";
  oOut << "90.0024\t122.888\tAmabilis_Fir\tSapling\t0.858124\t2.85775\t0\t0\t0\t5.4\t0\n";
  oOut << "156.348\t80.0415\tLodgepole_Pine\tSapling\t0.848633\t2.6797\t1\t0\t2\t6.6\t0\n";
  oOut << "107.66\t129.095\tWestern_Hemlock\tSapling\t0.836304\t2.82041\t0\t1\t0\t9\t0\n";
  oOut << "136.157\t189.856\tLodgepole_Pine\tSapling\t0.82608\t2.64517\t0\t0\t4\t10.7\t0\n";
  oOut << "46.4966\t178.687\tHybrid_Spruce\tSapling\t0.821655\t1.91713\t1\t1\t3\t1.2\t0\n";
  oOut << "84.613\t138.953\tWestern_Hemlock\tSapling\t0.82019\t2.79281\t1\t0\t4\t1.7\t0\n";
  oOut << "147.491\t126.959\tPaper_Birch\tSapling\t0.817596\t2.31711\t1\t1\t4\t10.2\t0\n";
  oOut << "131.83\t142.584\tTrembling_Aspen\tSapling\t0.816162\t2.11893\t0\t0\t4\t4.8\t0\n";
  oOut << "175.122\t129.51\tAmabilis_Fir\tSapling\t0.81604\t2.78569\t1\t1\t0\t8.5\t0\n";
  oOut << "150.781\t106.335\tTrembling_Aspen\tSapling\t0.811798\t2.11487\t1\t1\t4\t7.6\t0\n";
  oOut << "128.699\t150.848\tWestern_Redcedar\tSapling\t0.800446\t2.7444\t0\t0\t4\t11.2\t0\n";
  oOut << "23.9258\t142.303\tWestern_Redcedar\tSapling\t0.798492\t2.74108\t0\t0\t0\t6.8\t0\n";
  oOut << "46.5515\t176.959\tTrembling_Aspen\tSapling\t0.794281\t2.09858\t1\t1\t3\t3.7\t0\n";
  oOut << "120.093\t133.691\tSubalpine_Fir\tSapling\t0.783142\t2.13191\t0\t0\t0\t4.9\t0\n";
  oOut << "107.391\t39.1541\tWestern_Hemlock\tSapling\t0.782806\t2.72865\t0\t1\t0\t0.2\t0\n";
  oOut << "30.9509\t15.1672\tHybrid_Spruce\tSapling\t0.77301\t1.88387\t1\t0\t2\t2.4\t0\n";
  oOut << "112.384\t73.7244\tBlack_Cottonwood\tSapling\t0.759308\t2.3124\t0\t0\t1\t2.7\t0\n";
  oOut << "127.551\t189.984\tHybrid_Spruce\tSapling\t0.745728\t1.8652\t0\t0\t1\t1.6\t0\n";
  oOut << "180.609\t168.848\tBlack_Cottonwood\tSapling\t0.742126\t2.29099\t0\t1\t0\t9.3\t0\n";
  oOut << "181.342\t109.18\tWestern_Redcedar\tSapling\t0.738068\t2.63822\t0\t1\t0\t10.5\t0\n";
  oOut << "125.916\t33.9905\tAmabilis_Fir\tSapling\t0.736176\t2.64842\t0\t0\t0\t5.4\t0\n";
  oOut << "92.2119\t77.3071\tWestern_Hemlock\tSapling\t0.731079\t2.63963\t0\t1\t5\t1.9\t0\n";
  oOut << "129.15\t175.562\tTrembling_Aspen\tSapling\t0.730804\t2.03949\t0\t0\t2\t10.5\t0\n";
  oOut << "182.166\t95.3491\tAmabilis_Fir\tSapling\t0.730316\t2.63832\t0\t1\t0\t2.3\t0\n";
  oOut << "130.408\t50.3113\tTrembling_Aspen\tSapling\t0.726501\t2.03548\t0\t0\t0\t0.6\t0\n";
  oOut << "34.1125\t161.029\tWestern_Hemlock\tSapling\t0.720184\t2.62085\t1\t1\t4\t5.3\t0\n";
  oOut << "104.456\t122.357\tWestern_Redcedar\tSapling\t0.707458\t2.58596\t0\t0\t3\t22.7\t0\n";
  oOut << "189.374\t80.542\tWestern_Redcedar\tSapling\t0.707214\t2.58555\t0\t1\t0\t14.5\t0\n";
  oOut << "116.553\t183.429\tTrembling_Aspen\tSapling\t0.703156\t2.01371\t0\t0\t4\t5.7\t0\n";
  oOut << "168.756\t178.687\tSubalpine_Fir\tSapling\t0.698883\t2.04882\t0\t0\t0\t4.2\t0\n";
  oOut << "15.0208\t124.097\tAmabilis_Fir\tSapling\t0.693573\t2.57491\t0\t1\t0\t14\t0\n";
  oOut << "199.994\t71.4294\tPaper_Birch\tSapling\t0.686798\t2.16462\t0\t0\t1\t2.9\t0\n";
  oOut << "63.9221\t156.024\tLodgepole_Pine\tSapling\t0.684662\t2.42768\t1\t0\t2\t5.7\t0\n";
  oOut << "45.2698\t12.9211\tPaper_Birch\tSapling\t0.679077\t2.15559\t1\t1\t4\t3.4\t0\n";
  oOut << "6.65283\t71.1426\tWestern_Hemlock\tSapling\t0.664856\t2.52525\t1\t1\t0\t1.2\t0\n";
  oOut << "192.279\t126.819\tBlack_Cottonwood\tSapling\t0.661713\t2.19054\t0\t1\t0\t0.9\t0\n";
  oOut << "83.0872\t74.7437\tPaper_Birch\tSapling\t0.657288\t2.1301\t1\t0\t4\t9.7\t0\n";
  oOut << "173.743\t52.8809\tWestern_Hemlock\tSapling\t0.655518\t2.50908\t0\t0\t5\t0.1\t0\n";
  oOut << "61.7615\t186.346\tLodgepole_Pine\tSapling\t0.64975\t2.37372\t1\t1\t3\t3.4\t0\n";
  oOut << "61.3159\t79.4617\tLodgepole_Pine\tSapling\t0.645508\t2.36716\t1\t1\t3\t11\t0\n";
  oOut << "41.9678\t78.8269\tSubalpine_Fir\tSapling\t0.638\t1.98862\t0\t1\t0\t0.1\t0\n";
  oOut << "138.947\t123.492\tWestern_Redcedar\tSapling\t0.637238\t2.46571\t0\t1\t0\t23.3\t0\n";
  oOut << "196.13\t107.007\tHybrid_Spruce\tSapling\t0.626282\t1.7833\t0\t0\t3\t7.3\t0\n";
  oOut << "79.5593\t89.9902\tSubalpine_Fir\tSapling\t0.623962\t1.97473\t0\t0\t0\t10.3\t0\n";
  oOut << "116.223\t120.691\tWestern_Hemlock\tSapling\t0.623199\t2.45305\t0\t0\t0\t8.3\t0\n";
  oOut << "38.6169\t30.7434\tWestern_Redcedar\tSapling\t0.619507\t2.43526\t1\t1\t2\t8.8\t0\n";
  oOut << "14.7034\t116.223\tHybrid_Spruce\tSapling\t0.612091\t1.77356\t1\t1\t2\t4.4\t0\n";
  oOut << "74.3042\t134.143\tLodgepole_Pine\tSapling\t0.608917\t2.31048\t1\t0\t0\t10.9\t0\n";
  oOut << "4.90112\t105.084\tBlack_Cottonwood\tSapling\t0.608093\t2.12335\t0\t1\t1\t2.3\t0\n";
  oOut << "143.329\t44.7388\tAmabilis_Fir\tSapling\t0.60083\t2.4142\t0\t1\t0\t11.8\t0\n";
  oOut << "24.2859\t134.247\tWestern_Hemlock\tSapling\t0.593811\t2.402\t0\t1\t3\t1.9\t0\n";
  oOut << "180.066\t139.948\tBlack_Cottonwood\tSapling\t0.58136\t2.0898\t0\t1\t4\t11.1\t0\n";
  oOut << "190.515\t167.902\tWestern_Hemlock\tSapling\t0.573212\t2.36616\t0\t1\t3\t5.4\t0\n";
  oOut << "173.633\t23.4863\tHybrid_Spruce\tSapling\t0.565521\t1.74155\t0\t1\t0\t5.3\t0\n";
  oOut << "151.587\t50.9766\tBlack_Cottonwood\tSapling\t0.565063\t2.06932\t1\t1\t4\t5.5\t0\n";
  oOut << "21.7957\t139.642\tWestern_Hemlock\tSapling\t0.555725\t2.3357\t1\t0\t0\t1.4\t0\n";
  oOut << "101.794\t89.1479\tLodgepole_Pine\tSapling\t0.550873\t2.22033\t0\t1\t1\t7.8\t0\n";
  oOut << "115.399\t157.19\tAmabilis_Fir\tSapling\t0.548431\t2.32299\t0\t1\t0\t4\t0\n";
  oOut << "14.5203\t60.9131\tBlack_Cottonwood\tSapling\t0.545288\t2.04446\t0\t1\t0\t12.4\t0\n";
  oOut << "141.315\t83.2825\tTrembling_Aspen\tSapling\t0.539429\t1.86055\t0\t0\t1\t7.9\t0\n";
  oOut << "146.924\t32.7332\tAmabilis_Fir\tSapling\t0.538849\t2.30627\t0\t1\t0\t9.1\t0\n";
  oOut << "58.9783\t10.2295\tPaper_Birch\tSapling\t0.538544\t1.99076\t1\t1\t3\t3.4\t0\n";
  oOut << "119.995\t29.6753\tAmabilis_Fir\tSapling\t0.536987\t2.30302\t0\t0\t0\t11.1\t0\n";
  oOut << "101.288\t38.9648\tPaper_Birch\tSapling\t0.53653\t1.98839\t0\t1\t3\t9.7\t0\n";
  oOut << "90.7227\t121.198\tHybrid_Spruce\tSapling\t0.535553\t1.72094\t0\t1\t0\t11.1\t0\n";
  oOut << "44.9829\t160.004\tSubalpine_Fir\tSapling\t0.526978\t1.87852\t0\t1\t0\t0.5\t0\n";
  oOut << "98.2178\t112.848\tWestern_Hemlock\tSapling\t0.525116\t2.2823\t0\t1\t5\t4.5\t0\n";
  oOut << "98.2422\t157.074\tWestern_Redcedar\tSapling\t0.519501\t2.26289\t1\t1\t5\t10.2\t0\n";
  oOut << "163.068\t101.776\tWestern_Redcedar\tSapling\t0.513916\t2.25323\t1\t1\t3\t13.3\t0\n";
  oOut << "43.2678\t101.447\tPaper_Birch\tSapling\t0.510437\t1.95767\t1\t1\t1\t3.8\t0\n";
  oOut << "131.604\t131.256\tLodgepole_Pine\tSapling\t0.497559\t2.13726\t0\t0\t1\t11.6\t0\n";
  oOut << "181.238\t143.158\tLodgepole_Pine\tSapling\t0.497375\t2.13698\t0\t1\t5\t6.5\t0\n";
  oOut << "4.88281\t122.552\tWestern_Redcedar\tSapling\t0.490051\t2.21193\t1\t1\t2\t5.1\t0\n";
  oOut << "98.8098\t2.76489\tHybrid_Spruce\tSapling\t0.487579\t1.68791\t0\t1\t5\t6.2\t0\n";
  oOut << "23.1323\t5.62744\tSubalpine_Fir\tSapling\t0.47525\t1.82708\t0\t0\t0\t9.2\t0\n";
  oOut << "74.4629\t169.391\tPaper_Birch\tSapling\t0.472229\t1.91264\t1\t0\t2\t3.1\t0\n";
  oOut << "68.7256\t115.643\tPaper_Birch\tSapling\t0.467133\t1.90662\t1\t0\t1\t7.8\t0\n";
  oOut << "125.305\t70.2698\tTrembling_Aspen\tSapling\t0.466827\t1.79237\t0\t0\t0\t9.5\t0\n";
  oOut << "113.647\t128.662\tWestern_Redcedar\tSapling\t0.466644\t2.17135\t0\t1\t5\t11.9\t0\n";
  oOut << "33.9478\t156.75\tBlack_Cottonwood\tSapling\t0.460266\t1.9373\t0\t0\t3\t8.1\t0\n";
  oOut << "153.906\t135.333\tHybrid_Spruce\tSapling\t0.456757\t1.66666\t1\t1\t1\t3.2\t0\n";
  oOut << "144\t22.7905\tWestern_Hemlock\tSapling\t0.450836\t2.15229\t0\t1\t0\t11.9\t0\n";
  oOut << "13.7878\t4.45557\tWestern_Redcedar\tSapling\t0.440552\t2.12606\t1\t0\t4\t7\t0\n";
  oOut << "8.30078\t33.0322\tWestern_Hemlock\tSapling\t0.435669\t2.12567\t1\t1\t3\t14.2\t0\n";
  oOut << "199.139\t177.905\tTrembling_Aspen\tSapling\t0.428986\t1.75677\t0\t0\t1\t5.9\t0\n";
  oOut << "140.277\t161.493\tBlack_Cottonwood\tSapling\t0.424652\t1.89228\t0\t0\t3\t3.1\t0\n";
  oOut << "31.4209\t186.853\tTrembling_Aspen\tSapling\t0.418823\t1.7472\t1\t1\t1\t0.2\t0\n";
  oOut << "169.855\t85.144\tTrembling_Aspen\tSapling\t0.415985\t1.74452\t1\t1\t4\t9.2\t0\n";
  oOut << "117.725\t13.2385\tTrembling_Aspen\tSapling\t0.399994\t1.72946\t0\t0\t3\t9.9\t0\n";
  oOut << "132.33\t119.94\tWestern_Hemlock\tSapling\t0.395264\t2.05462\t0\t0\t4\t8.8\t0\n";
  oOut << "0.610352\t157.44\tWestern_Hemlock\tSapling\t0.376617\t2.02177\t0\t1\t3\t9.1\t0\n";
  oOut << "38.6963\t153.412\tSubalpine_Fir\tSapling\t0.375977\t1.72808\t0\t1\t0\t1.8\t0\n";
  oOut << "183.545\t71.4294\tAmabilis_Fir\tSapling\t0.365417\t2.00203\t0\t0\t0\t9.1\t0\n";
  oOut << "143.28\t29.9011\tSubalpine_Fir\tSapling\t0.355499\t1.70762\t0\t1\t0\t5.5\t0\n";
  oOut << "139.886\t110.84\tHybrid_Spruce\tSapling\t0.351074\t1.59371\t0\t1\t0\t3.5\t0\n";
  oOut << "191.876\t14.5325\tPaper_Birch\tSapling\t0.350891\t1.76913\t0\t0\t5\t4.5\t0\n";
  oOut << "104.987\t3.17993\tPaper_Birch\tSapling\t0.350769\t1.76899\t0\t1\t0\t9.1\t0\n";
  oOut << "158.02\t156.549\tLodgepole_Pine\tSapling\t0.346497\t1.90056\t1\t0\t5\t2.7\t0\n";
  oOut << "124.615\t22.2351\tLodgepole_Pine\tSapling\t0.34201\t1.8935\t0\t0\t3\t3.7\t0\n";
  oOut << "104.419\t117.303\tTrembling_Aspen\tSapling\t0.330597\t1.66399\t0\t1\t3\t9.1\t0\n";
  oOut << "159.052\t169.208\tAmabilis_Fir\tSapling\t0.325073\t1.93077\t1\t0\t0\t6.8\t0\n";
  oOut << "190.442\t10.1807\tLodgepole_Pine\tSapling\t0.321686\t1.86149\t0\t0\t0\t8.6\t0\n";
  oOut << "153.43\t125.781\tBlack_Cottonwood\tSapling\t0.320953\t1.76082\t1\t0\t1\t3.8\t0\n";
  oOut << "72.8882\t57.0251\tWestern_Redcedar\tSapling\t0.302948\t1.88594\t1\t0\t1\t6.5\t0\n";
  oOut << "189.978\t54.9561\tWestern_Hemlock\tSapling\t0.299683\t1.88584\t0\t0\t0\t8.9\t0\n";
  oOut << "40.7837\t113.672\tTrembling_Aspen\tSapling\t0.283813\t1.61976\t0\t0\t5\t6.4\t0\n";
  oOut << "173.566\t38.9893\tLodgepole_Pine\tSapling\t0.278931\t1.79404\t0\t0\t2\t5.4\t0\n";
  oOut << "87.3291\t169.293\tPaper_Birch\tSapling\t0.264435\t1.66643\t1\t0\t1\t7.7\t0\n";
  oOut << "107.092\t138.367\tAmabilis_Fir\tSapling\t0.261871\t1.81879\t0\t1\t0\t2.3\t0\n";
  oOut << "121.844\t77.3865\tAmabilis_Fir\tSapling\t0.261597\t1.8183\t0\t0\t0\t5.5\t0\n";
  oOut << "24.115\t63.385\tWestern_Redcedar\tSapling\t0.25769\t1.80652\t0\t0\t5\t7\t0\n";
  oOut << "2.44751\t74.7803\tHybrid_Spruce\tSapling\t0.254028\t1.52655\t0\t1\t3\t10.8\t0\n";
  oOut << "192.102\t137.518\tPaper_Birch\tSapling\t0.251312\t1.65081\t0\t0\t1\t9.8\t0\n";
  oOut << "99.1211\t10.5957\tSubalpine_Fir\tSapling\t0.250061\t1.60202\t0\t1\t0\t9.3\t0\n";
  oOut << "77.9907\t31.0547\tWestern_Redcedar\tSapling\t0.246674\t1.78715\t1\t0\t0\t8.5\t0\n";
  oOut << "164.111\t28.6133\tWestern_Redcedar\tSapling\t0.232513\t1.76224\t1\t1\t0\t1.3\t0\n";
  oOut << "187.921\t151.587\tSubalpine_Fir\tSapling\t0.231628\t1.58352\t0\t0\t0\t6\t0\n";
  oOut << "118.353\t33.5266\tBlack_Cottonwood\tSapling\t0.231476\t1.64688\t0\t0\t3\t10.8\t0\n";
  oOut << "20.1355\t112.781\tSubalpine_Fir\tSapling\t0.230927\t1.58282\t0\t0\t0\t12.7\t0\n";
  oOut << "48.645\t185.901\tLodgepole_Pine\tSapling\t0.229431\t1.71574\t1\t1\t5\t3.6\t0\n";
  oOut << "34.436\t0.750732\tSubalpine_Fir\tSapling\t0.224457\t1.57632\t0\t1\t0\t5\t0\n";
  oOut << "153.68\t63.7573\tHybrid_Spruce\tSapling\t0.219574\t1.50267\t1\t0\t5\t8.3\t0\n";
  oOut << "27.1057\t79.6814\tTrembling_Aspen\tSapling\t0.208954\t1.54886\t1\t1\t1\t10.4\t0\n";
  oOut << "165.167\t64.2334\tWestern_Redcedar\tSapling\t0.20813\t1.71929\t1\t0\t0\t3\t0\n";
  oOut << "196.216\t170.532\tLodgepole_Pine\tSapling\t0.199738\t1.66867\t0\t0\t2\t10.9\t0\n";
  oOut << "19.7205\t37.6526\tHybrid_Spruce\tSapling\t0.187897\t1.48069\t0\t1\t5\t12.4\t0\n";
  oOut << "137.103\t152.875\tWestern_Hemlock\tSapling\t0.18454\t1.68116\t0\t0\t0\t3.4\t0\n";
  oOut << "139.874\t83.4656\tHybrid_Spruce\tSapling\t0.178741\t1.47434\t0\t0\t0\t4.7\t0\n";
  oOut << "191.901\t43.8843\tWestern_Hemlock\tSapling\t0.172394\t1.65948\t0\t1\t5\t10.3\t0\n";
  oOut << "123.56\t78.5156\tLodgepole_Pine\tSapling\t0.172089\t1.62477\t0\t0\t2\t0.9\t0\n";
  oOut << "164.062\t90.7227\tPaper_Birch\tSapling\t0.16925\t1.55294\t1\t1\t2\t8.4\t0\n";
  oOut << "156.311\t64.3677\tPaper_Birch\tSapling\t0.163361\t1.5459\t1\t0\t0\t6.2\t0\n";
  oOut << "61.7432\t78.9673\tPaper_Birch\tSapling\t0.158295\t1.53984\t1\t1\t3\t3\t0\n";
  oOut << "80.3467\t145.477\tTrembling_Aspen\tSapling\t0.154327\t1.497\t1\t0\t5\t4.2\t0\n";
  oOut << "162.903\t96.2952\tLodgepole_Pine\tSapling\t0.15097\t1.5912\t1\t0\t4\t3.3\t0\n";
  oOut << "4.64478\t140.503\tAmabilis_Fir\tSapling\t0.144775\t1.61012\t0\t1\t0\t3.6\t0\n";
  oOut << "170.764\t12.9761\tSubalpine_Fir\tSapling\t0.139954\t1.49133\t0\t0\t0\t6.6\t0\n";
  oOut << "92.9688\t6.97021\tBlack_Cottonwood\tSapling\t0.121399\t1.50609\t1\t0\t0\t7.9\t0\n";
  oOut << "145.88\t86.7188\tSubalpine_Fir\tSapling\t0.120972\t1.4722\t0\t0\t0\t5.5\t0\n";
  oOut << "0.506592\t181.195\tAmabilis_Fir\tSapling\t0.119904\t1.5656\t0\t1\t0\t7\t0\n";
  oOut << "171.936\t191.76\tSubalpine_Fir\tSapling\t0.118103\t1.46931\t0\t1\t0\t6.7\t0\n";
  oOut << "71.7957\t163.202\tHybrid_Spruce\tSapling\t0.117188\t1.43158\t1\t0\t1\t7.6\t0\n";
  oOut << "166.87\t97.76\tSubalpine_Fir\tSapling\t0.116852\t1.46805\t0\t0\t0\t7.9\t0\n";
  oOut << "86.1755\t106.824\tHybrid_Spruce\tSapling\t0.113159\t1.42878\t1\t0\t0\t10.1\t0\n";
  oOut << "25.6775\t39.8132\tBlack_Cottonwood\tSapling\t0.1961609\t1.47371\t1\t1\t0\t8.9\t0\n";
  oOut << "4.77905\t127.905\tSubalpine_Fir\tSapling\t0.1861511\t1.43708\t0\t1\t0\t13.6\t0\n";
  oOut << "162.177\t90.2039\tWestern_Hemlock\tSapling\t0.1767822\t1.48825\t1\t0\t5\t10.2\t0\n";
  oOut << "65.9119\t42.3889\tBlack_Cottonwood\tSapling\t0.73761\t1.44494\t1\t0\t2\t10.1\t0\n";
  oOut << "125.366\t39.9475\tPaper_Birch\tSapling\t0.1650024\t1.42811\t0\t0\t1\t4.2\t0\n";
  oOut << "136.23\t47.229\tHybrid_Spruce\tSapling\t0.1601501\t1.3919\t0\t0\t3\t6.7\t0\n";
  oOut << "118.652\t119.257\tLodgepole_Pine\tSapling\t0.487366\t1.42809\t0\t0\t3\t9.8\t0\n";
  oOut << "161.499\t115.997\tBlack_Cottonwood\tSapling\t0.427551\t1.40507\t1\t0\t1\t2.6\t0\n";
  oOut << "166.156\t132.892\tTrembling_Aspen\tSapling\t0.366211\t1.38495\t1\t1\t2\t8.7\t0\n";
  oOut << "8.94775\t16.8579\tTrembling_Aspen\tSapling\t0.343323\t1.38277\t0\t1\t0\t11.4\t0\n";
  oOut << "55.5359\t73.0652\tBlack_Cottonwood\tSapling\t0.194702\t1.37509\t1\t1\t1\t3.2\t0\n";
  oOut << "113.08\t77.5452\tBlack_Cottonwood\tSapling\t0.106201\t1.36369\t0\t1\t0\t7.5\t0\n";
  oOut << "152.875\t118.848\tPaper_Birch\tSapling\t0.100708\t1.36212\t1\t1\t4\t6.9\t0\n";

  return cFileString;
}
