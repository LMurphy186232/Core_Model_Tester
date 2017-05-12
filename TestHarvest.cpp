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
    p_oSimManager->ReadFile( WriteHarvestXMLFile1(true) );
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

    EXPECT_LT(fabs(fSp2BA - 34.3837), 0.01);
    EXPECT_LT(fabs(fSp4BA - 33.61), 0.01);
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
    EXPECT_LT(fabs(fSp5Range0_30 - 0.64226), 0.01);
    EXPECT_LT(fabs(fSp5Range40_80 - 23.055), 0.01);
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
// DoHarvestRun1a()
// The setup is identical to HarvestRun1 except we are cutting smallest to
// largest.
/////////////////////////////////////////////////////////////////////////////
TEST(Harvest, DoHarvestRun1a) {
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
    p_oSimManager->ReadFile( WriteHarvestXMLFile1(false) );
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

    //Total up the basal area for species 2 and 4 - we're expecting 34.64876 sq
    //m of species 2 and 33.84402 sq m of species 4
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

    EXPECT_LT(fabs(fSp2BA - 34.25842189), 0.01);
    EXPECT_LT(fabs(fSp4BA - 33.45900391), 0.01);
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
    EXPECT_LT(fabs(fSp5Range0_30 - 0.634407585), 0.01);
    EXPECT_LT(fabs(fSp5Range40_80 - 23.03753927), 0.01);
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
    p_oSimManager->ReadFile( WriteHarvestXMLFile3(true) );
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

          if (fTemp >= 90 && fTemp <= 100) {
            iSp7_90_99++;

            // Verify that this is not any of the trees that should have been cut
            EXPECT_GT(fabs(fTemp - 99.9619), 0.001);
            EXPECT_GT(fabs(fTemp - 99.7043), 0.001);
            EXPECT_GT(fabs(fTemp - 99.6863), 0.001);
            EXPECT_GT(fabs(fTemp - 98.5852), 0.001);

          } else if (fTemp >= 80 && fTemp <= 85) {
            iSp7_80_85++;

            // Verify that this is not any of the trees that should have been cut
            EXPECT_GT(fabs(fTemp - 84.9774), 0.001);
            EXPECT_GT(fabs(fTemp - 84.9411), 0.001);
            EXPECT_GT(fabs(fTemp - 84.9057), 0.001);
            EXPECT_GT(fabs(fTemp - 83.2541), 0.001);

          } else if (fTemp >= 50 && fTemp <= 80) {
            iSp7_50_80++;

            // Verify that this is not any of the trees that should have been cut
            EXPECT_GT(fabs(fTemp - 79.9518), 0.001);
            EXPECT_GT(fabs(fTemp - 79.6609), 0.001);
            EXPECT_GT(fabs(fTemp - 79.5135), 0.001);
            EXPECT_GT(fabs(fTemp - 79.4186), 0.001);

          } else if (fTemp >= 15 && fTemp <= 45) {
            iSp7_15_45++;

            // Verify that this is not any of the trees that should have been cut
            EXPECT_GT(fabs(fTemp - 43.8516), 0.001);
            EXPECT_GT(fabs(fTemp - 41.2891), 0.001);
            EXPECT_GT(fabs(fTemp - 40.9753), 0.001);
            EXPECT_GT(fabs(fTemp - 40.5386), 0.001);
          }
        } else if (p_oTree->GetSpecies() == 6) {

          p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);

          if (fTemp >= 90 && fTemp <= 100) {
            iSp6_90_99++;

            // Verify that this is not any of the trees that should have been cut
            EXPECT_GT(fabs(fTemp - 99.7946), 0.001);
            EXPECT_GT(fabs(fTemp - 99.4312), 0.001);
            EXPECT_GT(fabs(fTemp - 99.1422), 0.001);
            EXPECT_GT(fabs(fTemp - 97.9132), 0.001);

          } else if (fTemp >= 80 && fTemp <= 85) {
            iSp6_80_85++;

            // Verify that this is not any of the trees that should have been cut
            EXPECT_GT(fabs(fTemp - 84.3524), 0.001);
            EXPECT_GT(fabs(fTemp - 84.0259), 0.001);
            EXPECT_GT(fabs(fTemp - 83.7686), 0.001);
            EXPECT_GT(fabs(fTemp - 81.9788), 0.001);

          } else if (fTemp >= 50 && fTemp <= 80) {
            iSp6_50_80++;

            // Verify that this is not any of the trees that should have been cut
            EXPECT_GT(fabs(fTemp - 79.91), 0.001);
            EXPECT_GT(fabs(fTemp - 78.8437), 0.001);
            EXPECT_GT(fabs(fTemp - 78.479), 0.001);
            EXPECT_GT(fabs(fTemp - 78.2904), 0.001);

          } else if (fTemp >= 15 && fTemp <= 45) {
            iSp6_15_45++;

            // Verify that this is not any of the trees that should have been cut
            EXPECT_GT(fabs(fTemp - 44.5139), 0.001);
            EXPECT_GT(fabs(fTemp - 44.0927), 0.001);
            EXPECT_GT(fabs(fTemp - 43.5123), 0.001);
            EXPECT_GT(fabs(fTemp - 43.0118), 0.001);
          }
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
// DoHarvestRun3a()
//
// This is identical to DoHarvestRun3 except the cut flag is set to smallest
// first.
/////////////////////////////////////////////////////////////////////////////
TEST(Harvest, DoHarvestRun3a) {

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
    p_oSimManager->ReadFile( WriteHarvestXMLFile3(false) );
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

          if (fTemp >= 90 && fTemp <= 100) {
            iSp7_90_99++;

            // Verify that this is not any of the trees that should have been cut
            EXPECT_GT(fabs(fTemp - 91.1108), 0.001);
            EXPECT_GT(fabs(fTemp - 91.3141), 0.001);
            EXPECT_GT(fabs(fTemp - 91.5756), 0.001);
            EXPECT_GT(fabs(fTemp - 91.6418), 0.001);

          } else if (fTemp >= 80 && fTemp <= 85) {
            iSp7_80_85++;

            // Verify that this is not any of the trees that should have been cut
            EXPECT_GT(fabs(fTemp - 80.9933), 0.001);
            EXPECT_GT(fabs(fTemp - 81.4853), 0.001);
            EXPECT_GT(fabs(fTemp - 82.8751), 0.001);
            EXPECT_GT(fabs(fTemp - 83.2541), 0.001);

          } else if (fTemp >= 50 && fTemp <= 80) {
            iSp7_50_80++;

            // Verify that this is not any of the trees that should have been cut
            EXPECT_GT(fabs(fTemp - 50.6357), 0.001);
            EXPECT_GT(fabs(fTemp - 50.6992), 0.001);
            EXPECT_GT(fabs(fTemp - 50.7578), 0.001);
            EXPECT_GT(fabs(fTemp - 50.9372), 0.001);

          } else if (fTemp >= 15 && fTemp <= 45) {
            iSp7_15_45++;

            // Verify that this is not any of the trees that should have been cut
            EXPECT_GT(fabs(fTemp - 15.0159), 0.001);
            EXPECT_GT(fabs(fTemp - 15.5627), 0.001);
            EXPECT_GT(fabs(fTemp - 15.8936), 0.001);
            EXPECT_GT(fabs(fTemp - 16.5344), 0.001);
          }
        } else if (p_oTree->GetSpecies() == 6) {

          p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);

          if (fTemp >= 90 && fTemp <= 100) {
            iSp6_90_99++;

            // Verify that this is not any of the trees that should have been cut
            EXPECT_GT(fabs(fTemp - 90.2371), 0.001);
            EXPECT_GT(fabs(fTemp - 90.4434), 0.001);
            EXPECT_GT(fabs(fTemp - 90.9143), 0.001);
            EXPECT_GT(fabs(fTemp - 91.0968), 0.001);

          } else if (fTemp >= 80 && fTemp <= 85) {
            iSp6_80_85++;

            // Verify that this is not any of the trees that should have been cut
            EXPECT_GT(fabs(fTemp - 80.5399), 0.001);
            EXPECT_GT(fabs(fTemp - 80.5624), 0.001);
            EXPECT_GT(fabs(fTemp - 80.6061), 0.001);
            EXPECT_GT(fabs(fTemp - 80.8011), 0.001);

          } else if (fTemp >= 50 && fTemp <= 80) {
            iSp6_50_80++;

            // Verify that this is not any of the trees that should have been cut
            EXPECT_GT(fabs(fTemp - 50.9534), 0.001);
            EXPECT_GT(fabs(fTemp - 51.1322), 0.001);
            EXPECT_GT(fabs(fTemp - 52.5479), 0.001);
            EXPECT_GT(fabs(fTemp - 52.8021), 0.001);

          } else if (fTemp >= 15 && fTemp <= 45) {
            iSp6_15_45++;

            // Verify that this is not any of the trees that should have been cut
            EXPECT_GT(fabs(fTemp - 16.3382), 0.001);
            EXPECT_GT(fabs(fTemp - 17.1033), 0.001);
            EXPECT_GT(fabs(fTemp - 17.1301), 0.001);
            EXPECT_GT(fabs(fTemp - 17.9541), 0.001);
          }
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
    p_oSimManager->ReadFile( WriteHarvestXMLFile4(true) );
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
// DoHarvestRun4a()
// Just like DoHarvestRun4, but cutting smallest to largest.
/////////////////////////////////////////////////////////////////////////////
TEST(Harvest, DoHarvestRun4a) {
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
    p_oSimManager->ReadFile( WriteHarvestXMLFile4(false) );
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
      else if (fabs(p_oFakeTrees[i].fX - 28.3142) < 0.001 && fabs(p_oFakeTrees[i].fY - 53.8513) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 13.7268) < 0.001 && fabs(p_oFakeTrees[i].fY - 27.3499) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 19.3359) < 0.001 && fabs(p_oFakeTrees[i].fY - 27.6611) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 39.9719) < 0.001 && fabs(p_oFakeTrees[i].fY - 77.1362) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 20.5322) < 0.001 && fabs(p_oFakeTrees[i].fY - 41.9495) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 30.957) < 0.001 && fabs(p_oFakeTrees[i].fY - 52.1729) < 0.001) p_oFakeTrees[i].bDead = true;

      else if (fabs(p_oFakeTrees[i].fX - 34.4727) < 0.001 && fabs(p_oFakeTrees[i].fY - 9.57642) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 14.5996) < 0.001 && fabs(p_oFakeTrees[i].fY - 24.8596) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 25.1953) < 0.001 && fabs(p_oFakeTrees[i].fY - 8.25806) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 0.787354) < 0.001 && fabs(p_oFakeTrees[i].fY - 67.4988) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 34.1431) < 0.001 && fabs(p_oFakeTrees[i].fY - 24.7314) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 19.9097) < 0.001 && fabs(p_oFakeTrees[i].fY - 3.38745) < 0.001) p_oFakeTrees[i].bDead = true;

      else if (fabs(p_oFakeTrees[i].fX - 30.6702) < 0.001 && fabs(p_oFakeTrees[i].fY - 74.1028) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 40.8142) < 0.001 && fabs(p_oFakeTrees[i].fY - 30.3772) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 47.229) < 0.001 && fabs(p_oFakeTrees[i].fY - 1.01318) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 15.1917) < 0.001 && fabs(p_oFakeTrees[i].fY - 47.8943) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 33.5754) < 0.001 && fabs(p_oFakeTrees[i].fY - 2.94189) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 39.2273) < 0.001 && fabs(p_oFakeTrees[i].fY - 1.5686) < 0.001) p_oFakeTrees[i].bDead = true;
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

    p_oSimManager->ReadFile( WriteHarvestXMLFile5(true) );
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
// DoHarvestRun5a()
// Same as DoHarvestRun5, but cut flag is smallest to largest.
/////////////////////////////////////////////////////////////////////////////
TEST(Harvest, DoHarvestRun5a) {
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

    p_oSimManager->ReadFile( WriteHarvestXMLFile5(false) );
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

      //Species 0
      if (fabs(p_oFakeTrees[i].fX - 162.177) < 0.001 && fabs(p_oFakeTrees[i].fY - 90.2039) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 191.901) < 0.001 && fabs(p_oFakeTrees[i].fY - 43.8843) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 189.978) < 0.001 && fabs(p_oFakeTrees[i].fY - 54.9561) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 144) < 0.001 && fabs(p_oFakeTrees[i].fY - 22.7905) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 173.743) < 0.001 && fabs(p_oFakeTrees[i].fY - 52.8809) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 92.2119) < 0.001 && fabs(p_oFakeTrees[i].fY - 77.3071) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 107.391) < 0.001 && fabs(p_oFakeTrees[i].fY - 39.1541) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 71.0205) < 0.001 && fabs(p_oFakeTrees[i].fY - 80.9814) < 0.001) p_oFakeTrees[i].bDead = true;

      else if (fabs(p_oFakeTrees[i].fX - 147.51 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 101.953) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 122.552) < 0.001 && fabs(p_oFakeTrees[i].fY - 16.3757) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 90.4602) < 0.001 && fabs(p_oFakeTrees[i].fY - 47.4609) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 197.339) < 0.001 && fabs(p_oFakeTrees[i].fY - 91.4429) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 98.4802) < 0.001 && fabs(p_oFakeTrees[i].fY - 35.0342) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 139.703) < 0.001 && fabs(p_oFakeTrees[i].fY - 44.696) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 130.17 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 25.415) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 196.722) < 0.001 && fabs(p_oFakeTrees[i].fY - 2.92969) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 179.663) < 0.001 && fabs(p_oFakeTrees[i].fY - 14.4348) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 143.604) < 0.001 && fabs(p_oFakeTrees[i].fY - 57.1594) < 0.001) p_oFakeTrees[i].bDead = true;

      else if (fabs(p_oFakeTrees[i].fX - 184.186) < 0.001 && fabs(p_oFakeTrees[i].fY - 48.9075) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 181.006) < 0.001 && fabs(p_oFakeTrees[i].fY - 53.0579) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 189.886) < 0.001 && fabs(p_oFakeTrees[i].fY - 53.9001) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 182.709) < 0.001 && fabs(p_oFakeTrees[i].fY - 83.905) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 177.155) < 0.001 && fabs(p_oFakeTrees[i].fY - 29.1626) < 0.001) p_oFakeTrees[i].bDead = true;

      //Species 1
      else if (fabs(p_oFakeTrees[i].fX - 165.167) < 0.001 && fabs(p_oFakeTrees[i].fY - 64.2334) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 164.111) < 0.001 && fabs(p_oFakeTrees[i].fY - 28.6133) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 77.9907) < 0.001 && fabs(p_oFakeTrees[i].fY - 31.0547) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 72.8882) < 0.001 && fabs(p_oFakeTrees[i].fY - 57.0251) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 163.068) < 0.001 && fabs(p_oFakeTrees[i].fY - 101.776) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 189.374) < 0.001 && fabs(p_oFakeTrees[i].fY - 80.542) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 193.097) < 0.001 && fabs(p_oFakeTrees[i].fY - 43.7378) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 97.6379) < 0.001 && fabs(p_oFakeTrees[i].fY - 15.033) < 0.001) p_oFakeTrees[i].bDead = true;

      else if (fabs(p_oFakeTrees[i].fX - 51.1841) < 0.001 && fabs(p_oFakeTrees[i].fY - 48.3032) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 157.025) < 0.001 && fabs(p_oFakeTrees[i].fY - 61.7126) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 105.298) < 0.001 && fabs(p_oFakeTrees[i].fY - 63.4949) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 98.0896) < 0.001 && fabs(p_oFakeTrees[i].fY - 102.673) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 98.8159) < 0.001 && fabs(p_oFakeTrees[i].fY - 7.02515) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 179.48 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 100.677) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 173.615) < 0.001 && fabs(p_oFakeTrees[i].fY - 71.2341) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 121.405) < 0.001 && fabs(p_oFakeTrees[i].fY - 59.0332) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 48.0469) < 0.001 && fabs(p_oFakeTrees[i].fY - 89.1907) < 0.001) p_oFakeTrees[i].bDead = true;

      else if (fabs(p_oFakeTrees[i].fX - 167.847) < 0.001 && fabs(p_oFakeTrees[i].fY - 76.6663) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 198.431) < 0.001 && fabs(p_oFakeTrees[i].fY - 16.3879) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 140.552) < 0.001 && fabs(p_oFakeTrees[i].fY - 58.1909) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 123.09 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 65.5579) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 184.857) < 0.001 && fabs(p_oFakeTrees[i].fY - 91.0767) < 0.001) p_oFakeTrees[i].bDead = true;

      //Species 2
      else if (fabs(p_oFakeTrees[i].fX - 121.844) < 0.001 && fabs(p_oFakeTrees[i].fY - 77.3865) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 183.545) < 0.001 && fabs(p_oFakeTrees[i].fY - 71.4294) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 119.995) < 0.001 && fabs(p_oFakeTrees[i].fY - 29.6753) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 146.924) < 0.001 && fabs(p_oFakeTrees[i].fY - 32.7332) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 143.329) < 0.001 && fabs(p_oFakeTrees[i].fY - 44.7388) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 182.166) < 0.001 && fabs(p_oFakeTrees[i].fY - 95.3491) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 125.916) < 0.001 && fabs(p_oFakeTrees[i].fY - 33.9905) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 191.888) < 0.001 && fabs(p_oFakeTrees[i].fY - 9.43604) < 0.001) p_oFakeTrees[i].bDead = true;

      else if (fabs(p_oFakeTrees[i].fX - 156.732) < 0.001 && fabs(p_oFakeTrees[i].fY - 37.8967) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 133.496) < 0.001 && fabs(p_oFakeTrees[i].fY - 46.814) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 123.419) < 0.001 && fabs(p_oFakeTrees[i].fY - 23.3643) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 176.904) < 0.001 && fabs(p_oFakeTrees[i].fY - 15.1733) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 198.608) < 0.001 && fabs(p_oFakeTrees[i].fY - 44.8059) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 157.66 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 81.9031) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 163.367) < 0.001 && fabs(p_oFakeTrees[i].fY - 33.5144) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 48.3582) < 0.001 && fabs(p_oFakeTrees[i].fY - 180.725) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 189.703) < 0.001 && fabs(p_oFakeTrees[i].fY - 65.1428) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 93.335 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 99.4446) < 0.001) p_oFakeTrees[i].bDead = true;

      else if (fabs(p_oFakeTrees[i].fX - 130.414) < 0.001 && fabs(p_oFakeTrees[i].fY - 56.0669) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 153.149) < 0.001 && fabs(p_oFakeTrees[i].fY - 64.3188) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 118.036) < 0.001 && fabs(p_oFakeTrees[i].fY - 57.0435) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 103.693) < 0.001 && fabs(p_oFakeTrees[i].fY - 29.8462) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 105.121) < 0.001 && fabs(p_oFakeTrees[i].fY - 96.4417) < 0.001) p_oFakeTrees[i].bDead = true;

      //Species 3
      else if (fabs(p_oFakeTrees[i].fX - 166.87 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 97.76) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 145.88 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 86.7188) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 170.764) < 0.001 && fabs(p_oFakeTrees[i].fY - 12.9761) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 99.1211) < 0.001 && fabs(p_oFakeTrees[i].fY - 10.5957) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 143.28 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 29.9011) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 79.5593) < 0.001 && fabs(p_oFakeTrees[i].fY - 89.9902) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 88.678 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 77.5269) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 173.914) < 0.001 && fabs(p_oFakeTrees[i].fY - 81.2988) < 0.001) p_oFakeTrees[i].bDead = true;

      else if (fabs(p_oFakeTrees[i].fX - 137.219) < 0.001 && fabs(p_oFakeTrees[i].fY - 70.6909) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 169.672) < 0.001 && fabs(p_oFakeTrees[i].fY - 46.7957) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 54.0466) < 0.001 && fabs(p_oFakeTrees[i].fY - 167.749) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 55.7434) < 0.001 && fabs(p_oFakeTrees[i].fY - 180.17) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 189.929) < 0.001 && fabs(p_oFakeTrees[i].fY - 35.6934) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 89.1785) < 0.001 && fabs(p_oFakeTrees[i].fY - 100.226) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 86.2854) < 0.001 && fabs(p_oFakeTrees[i].fY - 59.3201) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 91.1743) < 0.001 && fabs(p_oFakeTrees[i].fY - 12.4817) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 101.331) < 0.001 && fabs(p_oFakeTrees[i].fY - 97.9858) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 148.279) < 0.001 && fabs(p_oFakeTrees[i].fY - 52.0447) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 136.108) < 0.001 && fabs(p_oFakeTrees[i].fY - 62.5061) < 0.001) p_oFakeTrees[i].bDead = true;

      else if (fabs(p_oFakeTrees[i].fX - 104.803) < 0.001 && fabs(p_oFakeTrees[i].fY - 46.875) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 143.878) < 0.001 && fabs(p_oFakeTrees[i].fY - 37.5916) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 151.3) < 0.001 && fabs(p_oFakeTrees[i].fY - 100.049) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 50.6348) < 0.001 && fabs(p_oFakeTrees[i].fY - 66.4795) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 185.931) < 0.001 && fabs(p_oFakeTrees[i].fY - 79.3701) < 0.001) p_oFakeTrees[i].bDead = true;

      //Species 4
      else if (fabs(p_oFakeTrees[i].fX - 136.23 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 47.229) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 139.874) < 0.001 && fabs(p_oFakeTrees[i].fY - 83.4656) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 153.68 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 63.7573) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 98.8098) < 0.001 && fabs(p_oFakeTrees[i].fY - 2.76489) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 173.633) < 0.001 && fabs(p_oFakeTrees[i].fY - 23.4863) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 146.277) < 0.001 && fabs(p_oFakeTrees[i].fY - 30.3589) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 66.5344) < 0.001 && fabs(p_oFakeTrees[i].fY - 16.9006) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 173.56 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 24.4141) < 0.001) p_oFakeTrees[i].bDead = true;

      else if (fabs(p_oFakeTrees[i].fX - 132.764) < 0.001 && fabs(p_oFakeTrees[i].fY - 44.5862) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 66.0767) < 0.001 && fabs(p_oFakeTrees[i].fY - 57.2632) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 186.731) < 0.001 && fabs(p_oFakeTrees[i].fY - 26.825) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 197.919) < 0.001 && fabs(p_oFakeTrees[i].fY - 47.9004) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 51.6235) < 0.001 && fabs(p_oFakeTrees[i].fY - 172.089) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 127.332) < 0.001 && fabs(p_oFakeTrees[i].fY - 33.3374) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 55.3345) < 0.001 && fabs(p_oFakeTrees[i].fY - 151.379) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 169.58 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 59.4971) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 199.5) < 0.001 && fabs(p_oFakeTrees[i].fY - 7.44629) < 0.001) p_oFakeTrees[i].bDead = true;

      else if (fabs(p_oFakeTrees[i].fX - 103.998) < 0.001 && fabs(p_oFakeTrees[i].fY - 36.5784) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 53.3447) < 0.001 && fabs(p_oFakeTrees[i].fY - 129.956) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 98.4619) < 0.001 && fabs(p_oFakeTrees[i].fY - 67.1326) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 49.5972) < 0.001 && fabs(p_oFakeTrees[i].fY - 123.993) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 175.818) < 0.001 && fabs(p_oFakeTrees[i].fY - 90.9851) < 0.001) p_oFakeTrees[i].bDead = true;

      //Species 5
      else if (fabs(p_oFakeTrees[i].fX - 162.903) < 0.001 && fabs(p_oFakeTrees[i].fY - 96.2952) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 123.56 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 78.5156) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 48.645 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 185.901) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 173.566) < 0.001 && fabs(p_oFakeTrees[i].fY - 38.9893) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 190.442) < 0.001 && fabs(p_oFakeTrees[i].fY - 10.1807) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 124.615) < 0.001 && fabs(p_oFakeTrees[i].fY - 22.2351) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 101.794) < 0.001 && fabs(p_oFakeTrees[i].fY - 89.1479) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 156.348) < 0.001 && fabs(p_oFakeTrees[i].fY - 80.0415) < 0.001) p_oFakeTrees[i].bDead = true;

      else if (fabs(p_oFakeTrees[i].fX - 105.475) < 0.001 && fabs(p_oFakeTrees[i].fY - 52.0325) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 174.414) < 0.001 && fabs(p_oFakeTrees[i].fY - 28.6072) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 130.383) < 0.001 && fabs(p_oFakeTrees[i].fY - 8.25806) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 145.813) < 0.001 && fabs(p_oFakeTrees[i].fY - 10.6445) < 0.001) p_oFakeTrees[i].bDead = true;

      else if (fabs(p_oFakeTrees[i].fX - 53.4119) < 0.001 && fabs(p_oFakeTrees[i].fY - 133.685) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 143.707) < 0.001 && fabs(p_oFakeTrees[i].fY - 1.84326) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 90.1978) < 0.001 && fabs(p_oFakeTrees[i].fY - 17.0593) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 101.215) < 0.001 && fabs(p_oFakeTrees[i].fY - 69.3787) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 169.568) < 0.001 && fabs(p_oFakeTrees[i].fY - 60.3699) < 0.001) p_oFakeTrees[i].bDead = true;

      //Species 6
      else if (fabs(p_oFakeTrees[i].fX - 117.725) < 0.001 && fabs(p_oFakeTrees[i].fY - 13.2385) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 169.855) < 0.001 && fabs(p_oFakeTrees[i].fY - 85.144) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 125.305) < 0.001 && fabs(p_oFakeTrees[i].fY - 70.2698) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 141.315) < 0.001 && fabs(p_oFakeTrees[i].fY - 83.2825) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 130.408) < 0.001 && fabs(p_oFakeTrees[i].fY - 50.3113) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 167.108) < 0.001 && fabs(p_oFakeTrees[i].fY - 63.3179) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 195.807) < 0.001 && fabs(p_oFakeTrees[i].fY - 31.6833) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 187.701) < 0.001 && fabs(p_oFakeTrees[i].fY - 35.4858) < 0.001) p_oFakeTrees[i].bDead = true;

      else if (fabs(p_oFakeTrees[i].fX - 48.0225) < 0.001 && fabs(p_oFakeTrees[i].fY - 85.2478) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 106.128) < 0.001 && fabs(p_oFakeTrees[i].fY - 53.6987) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 152.411) < 0.001 && fabs(p_oFakeTrees[i].fY - 103.461) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 140.826) < 0.001 && fabs(p_oFakeTrees[i].fY - 79.1626) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 135.791) < 0.001 && fabs(p_oFakeTrees[i].fY - 101.55) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 113.94 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 63.6169) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 175.232) < 0.001 && fabs(p_oFakeTrees[i].fY - 20.4346) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 195.447) < 0.001 && fabs(p_oFakeTrees[i].fY - 85.9009) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 141.846) < 0.001 && fabs(p_oFakeTrees[i].fY - 25.4822) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 83.8867) < 0.001 && fabs(p_oFakeTrees[i].fY - 17.7673) < 0.001) p_oFakeTrees[i].bDead = true;

      else if (fabs(p_oFakeTrees[i].fX - 74.2981) < 0.001 && fabs(p_oFakeTrees[i].fY - 91.0339) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 180.969) < 0.001 && fabs(p_oFakeTrees[i].fY - 34.4299) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 158.649) < 0.001 && fabs(p_oFakeTrees[i].fY - 88.8489) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 119.757) < 0.001 && fabs(p_oFakeTrees[i].fY - 93.158) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 148.657) < 0.001 && fabs(p_oFakeTrees[i].fY - 34.4299) < 0.001) p_oFakeTrees[i].bDead = true;

      //Species 7
      else if (fabs(p_oFakeTrees[i].fX - 113.08 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 77.5452) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 55.5359) < 0.001 && fabs(p_oFakeTrees[i].fY - 73.0652) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 65.9119) < 0.001 && fabs(p_oFakeTrees[i].fY - 42.3889) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 92.9688) < 0.001 && fabs(p_oFakeTrees[i].fY - 6.97021) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 118.353) < 0.001 && fabs(p_oFakeTrees[i].fY - 33.5266) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 151.587) < 0.001 && fabs(p_oFakeTrees[i].fY - 50.9766) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 112.384) < 0.001 && fabs(p_oFakeTrees[i].fY - 73.7244) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 83.075 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 84.6436) < 0.001) p_oFakeTrees[i].bDead = true;

      else if (fabs(p_oFakeTrees[i].fX - 159.839) < 0.001 && fabs(p_oFakeTrees[i].fY - 6.12793) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 67.9443) < 0.001 && fabs(p_oFakeTrees[i].fY - 85.4553) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 194.482) < 0.001 && fabs(p_oFakeTrees[i].fY - 28.7781) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 156.36 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 5.97534) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 99.823 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 86.7126) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 141.724) < 0.001 && fabs(p_oFakeTrees[i].fY - 10.6445) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 51.3794) < 0.001 && fabs(p_oFakeTrees[i].fY - 174.731) < 0.001) p_oFakeTrees[i].bDead = true;

      else if (fabs(p_oFakeTrees[i].fX - 106.213) < 0.001 && fabs(p_oFakeTrees[i].fY - 31.1951) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 189.771) < 0.001 && fabs(p_oFakeTrees[i].fY - 39.679) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 79.0283) < 0.001 && fabs(p_oFakeTrees[i].fY - 81.2012) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 129.7) < 0.001 && fabs(p_oFakeTrees[i].fY - 83.1299) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 141.107) < 0.001 && fabs(p_oFakeTrees[i].fY - 87.3779) < 0.001) p_oFakeTrees[i].bDead = true;

      //Species 8
      else if (fabs(p_oFakeTrees[i].fX - 125.366) < 0.001 && fabs(p_oFakeTrees[i].fY - 39.9475) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 156.311) < 0.001 && fabs(p_oFakeTrees[i].fY - 64.3677) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 164.062) < 0.001 && fabs(p_oFakeTrees[i].fY - 90.7227) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 104.987) < 0.001 && fabs(p_oFakeTrees[i].fY - 3.17993) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 191.876) < 0.001 && fabs(p_oFakeTrees[i].fY - 14.5325) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 101.288) < 0.001 && fabs(p_oFakeTrees[i].fY - 38.9648) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 83.0872) < 0.001 && fabs(p_oFakeTrees[i].fY - 74.7437) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 199.994) < 0.001 && fabs(p_oFakeTrees[i].fY - 71.4294) < 0.001) p_oFakeTrees[i].bDead = true;

      else if (fabs(p_oFakeTrees[i].fX - 176.855) < 0.001 && fabs(p_oFakeTrees[i].fY - 47.522) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 106.378) < 0.001 && fabs(p_oFakeTrees[i].fY - 90.6311) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 94.635 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 61.8286) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 51.5808) < 0.001 && fabs(p_oFakeTrees[i].fY - 51.0254) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 82.428 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 74.7192) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 141.443) < 0.001 && fabs(p_oFakeTrees[i].fY - 2.7771) < 0.001) p_oFakeTrees[i].bDead = true;

      else if (fabs(p_oFakeTrees[i].fX - 154.639) < 0.001 && fabs(p_oFakeTrees[i].fY - 82.428) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 113.947) < 0.001 && fabs(p_oFakeTrees[i].fY - 97.052) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 98.5168) < 0.001 && fabs(p_oFakeTrees[i].fY - 43.5486) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 55.0781) < 0.001 && fabs(p_oFakeTrees[i].fY - 127.094) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 76.8799) < 0.001 && fabs(p_oFakeTrees[i].fY - 85.5164) < 0.001) p_oFakeTrees[i].bDead = true;
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
    p_oSimManager->ReadFile( WriteHarvestXMLFile6(true) );
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

/////////////////////////////////////////////////////////////////////////////
// DoHarvestRun6a()
// This is the same as DoHarvestRun6, with the flag for smallest to 
// largest cut set to true.
/////////////////////////////////////////////////////////////////////////////
TEST(Harvest, DoHarvestRun6a) {
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
    p_oSimManager->ReadFile( WriteHarvestXMLFile6(false) );
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

      //Sp 1
      if (fabs(p_oFakeTrees[i].fX - 7.2937) < 0.001 && fabs(p_oFakeTrees[i].fY - 82.8491) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 1.30005) < 0.001 && fabs(p_oFakeTrees[i].fY - 85.4675) < 0.001) p_oFakeTrees[i].bDead = true;
      
      //Sp 2
      else if (fabs(p_oFakeTrees[i].fX - 47.76) < 0.001 && fabs(p_oFakeTrees[i].fY - 42.3767) < 0.001) p_oFakeTrees[i].bDead = true;
     
      //Sp 5
      else if (fabs(p_oFakeTrees[i].fX - 15.5945) < 0.001 && fabs(p_oFakeTrees[i].fY - 8.71582) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 13.9404) < 0.001 && fabs(p_oFakeTrees[i].fY - 10.8521) < 0.001) p_oFakeTrees[i].bDead = true;
      
      //Sp 6
      else if (fabs(p_oFakeTrees[i].fX - 165.112) < 0.001 && fabs(p_oFakeTrees[i].fY - 6.23779) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 164.618) < 0.001 && fabs(p_oFakeTrees[i].fY - 6.66504) < 0.001) p_oFakeTrees[i].bDead = true;
      
      //Sp 8
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
  int iNumInPriority, iNumTotal, iTemp, iNumTrees = 1980, iCounter = 0, i;
  bool bTemp;
  treestruct *p_oFakeTrees = new treestruct[iNumTrees];

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {

    p_oSimManager->ReadFile( WriteHarvestXMLFile9(true) );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

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

    //Run harvest only
    p_oSimManager->SetCurrentTimestep(1);
    clBehaviorBase *p_oBase = p_oSimManager->GetBehaviorObject(0);
    clDisturbance *p_oHarv = dynamic_cast<clDisturbance*>(p_oBase);
    p_oHarv->Action();


    //Expected results
    for (i = 0; i < iNumTrees; i++) {

      //*********************************************
      // Western Redcedar
      //*********************************************
      if (fabs(p_oFakeTrees[i].fX - 10.8154) < 0.001 && fabs(p_oFakeTrees[i].fY - 120.825) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 54.5044) < 0.001 && fabs(p_oFakeTrees[i].fY - 17.5354) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 18.457 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 66.2415) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 86.8164) < 0.001 && fabs(p_oFakeTrees[i].fY - 41.6809) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 61.0596) < 0.001 && fabs(p_oFakeTrees[i].fY - 34.2102) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 3.39966) < 0.001 && fabs(p_oFakeTrees[i].fY - 162.634) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 24.3408) < 0.001 && fabs(p_oFakeTrees[i].fY - 36.7615) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 57.5378) < 0.001 && fabs(p_oFakeTrees[i].fY - 115.991) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 72.406 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 131.665) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 78.2227) < 0.001 && fabs(p_oFakeTrees[i].fY - 190.918) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 7.2937 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 82.8491) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 9.5459 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 114.655) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 2.47803) < 0.001 && fabs(p_oFakeTrees[i].fY - 178.595) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 21.1731) < 0.001 && fabs(p_oFakeTrees[i].fY - 163.885) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 8.1665 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 28.2959) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 3.96118) < 0.001 && fabs(p_oFakeTrees[i].fY - 153.894) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 85.1135) < 0.001 && fabs(p_oFakeTrees[i].fY - 74.1882) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 70.2759) < 0.001 && fabs(p_oFakeTrees[i].fY - 21.759) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 53.772 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 131.628) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 30.9814) < 0.001 && fabs(p_oFakeTrees[i].fY - 170.563) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 83.8806) < 0.001 && fabs(p_oFakeTrees[i].fY - 133.972) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 5.71899) < 0.001 && fabs(p_oFakeTrees[i].fY - 144.849) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 12.7869) < 0.001 && fabs(p_oFakeTrees[i].fY - 8.81348) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 15.1489) < 0.001 && fabs(p_oFakeTrees[i].fY - 191.254) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 83.8196) < 0.001 && fabs(p_oFakeTrees[i].fY - 168.127) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 70.7764) < 0.001 && fabs(p_oFakeTrees[i].fY - 85.3638) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 40.5762) < 0.001 && fabs(p_oFakeTrees[i].fY - 125.592) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 50.6165) < 0.001 && fabs(p_oFakeTrees[i].fY - 77.0691) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 30.6274) < 0.001 && fabs(p_oFakeTrees[i].fY - 68.0908) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 74.3042) < 0.001 && fabs(p_oFakeTrees[i].fY - 80.9998) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 2.62451) < 0.001 && fabs(p_oFakeTrees[i].fY - 96.6858) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 47.699 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 36.5723) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 67.0715) < 0.001 && fabs(p_oFakeTrees[i].fY - 168.024) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 21.6064) < 0.001 && fabs(p_oFakeTrees[i].fY - 138.373) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 56.4148) < 0.001 && fabs(p_oFakeTrees[i].fY - 190.533) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 61.0229) < 0.001 && fabs(p_oFakeTrees[i].fY - 127.991) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 60.7971) < 0.001 && fabs(p_oFakeTrees[i].fY - 49.3469) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 55.7251) < 0.001 && fabs(p_oFakeTrees[i].fY - 37.4695) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 21.814 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 114.398) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 32.0557) < 0.001 && fabs(p_oFakeTrees[i].fY - 51.9958) < 0.001) p_oFakeTrees[i].bDead = true;


      //*********************************************
      // Amabilis Fir
      //*********************************************
      if (fabs(p_oFakeTrees[i].fX - 59.6069) < 0.001 && fabs(p_oFakeTrees[i].fY - 123.224) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 30.603 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 65.4236) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 130.353) < 0.001 && fabs(p_oFakeTrees[i].fY - 1.96533) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 165.485) < 0.001 && fabs(p_oFakeTrees[i].fY - 143.365) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 91.8335) < 0.001 && fabs(p_oFakeTrees[i].fY - 81.6162) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 35.6262) < 0.001 && fabs(p_oFakeTrees[i].fY - 192.2) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 145.172) < 0.001 && fabs(p_oFakeTrees[i].fY - 57.5256) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 97.1497) < 0.001 && fabs(p_oFakeTrees[i].fY - 34.0454) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 90.7959) < 0.001 && fabs(p_oFakeTrees[i].fY - 59.845) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 18.5486) < 0.001 && fabs(p_oFakeTrees[i].fY - 183.551) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 51.2756) < 0.001 && fabs(p_oFakeTrees[i].fY - 146.735) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 83.96) < 0.001 && fabs(p_oFakeTrees[i].fY - 65.4663) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 45.7214) < 0.001 && fabs(p_oFakeTrees[i].fY - 199.78) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 97.9004) < 0.001 && fabs(p_oFakeTrees[i].fY - 69.3909) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 92.6208) < 0.001 && fabs(p_oFakeTrees[i].fY - 43.3044) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 123.285) < 0.001 && fabs(p_oFakeTrees[i].fY - 187.439) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 88.9954) < 0.001 && fabs(p_oFakeTrees[i].fY - 187.689) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 157.452) < 0.001 && fabs(p_oFakeTrees[i].fY - 134.991) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 179.108) < 0.001 && fabs(p_oFakeTrees[i].fY - 173.303) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 194.452) < 0.001 && fabs(p_oFakeTrees[i].fY - 178.802) < 0.001) p_oFakeTrees[i].bDead = true;


      //*********************************************
      // Subalpine Fir
      //*********************************************
      else if (fabs(p_oFakeTrees[i].fX - 40.3015) < 0.001 && fabs(p_oFakeTrees[i].fY - 171.814) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 151.813) < 0.001 && fabs(p_oFakeTrees[i].fY - 70.7886) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 14.4775) < 0.001 && fabs(p_oFakeTrees[i].fY - 130.17) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 32.0435) < 0.001 && fabs(p_oFakeTrees[i].fY - 39.6667) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 153.461) < 0.001 && fabs(p_oFakeTrees[i].fY - 69.1162) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 5.98145) < 0.001 && fabs(p_oFakeTrees[i].fY - 22.345) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 189.374) < 0.001 && fabs(p_oFakeTrees[i].fY - 71.1121) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 145.654) < 0.001 && fabs(p_oFakeTrees[i].fY - 62.1033) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 132.428) < 0.001 && fabs(p_oFakeTrees[i].fY - 100.903) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 179.944) < 0.001 && fabs(p_oFakeTrees[i].fY - 155.145) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 94.2322) < 0.001 && fabs(p_oFakeTrees[i].fY - 181.531) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 113.135) < 0.001 && fabs(p_oFakeTrees[i].fY - 133.386) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 4.84619) < 0.001 && fabs(p_oFakeTrees[i].fY - 80.7007) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 133.801) < 0.001 && fabs(p_oFakeTrees[i].fY - 129.919) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 13.9648) < 0.001 && fabs(p_oFakeTrees[i].fY - 20.0195) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 37.8235) < 0.001 && fabs(p_oFakeTrees[i].fY - 98.4375) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 190.466) < 0.001 && fabs(p_oFakeTrees[i].fY - 12.6465) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 173.346) < 0.001 && fabs(p_oFakeTrees[i].fY - 118.073) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 95.1111) < 0.001 && fabs(p_oFakeTrees[i].fY - 145.312) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 68.4326) < 0.001 && fabs(p_oFakeTrees[i].fY - 168.573) < 0.001) p_oFakeTrees[i].bDead = true;

      //*********************************************
      // Hybrid Spruce
      //*********************************************
      else if (fabs(p_oFakeTrees[i].fX - 156.14 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 99.6399) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 147.949) < 0.001 && fabs(p_oFakeTrees[i].fY - 70.7886) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 62.207 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 123.401) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 137.292) < 0.001 && fabs(p_oFakeTrees[i].fY - 127.087) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 188.361) < 0.001 && fabs(p_oFakeTrees[i].fY - 39.8315) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 150.958) < 0.001 && fabs(p_oFakeTrees[i].fY - 80.1636) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 84.1309) < 0.001 && fabs(p_oFakeTrees[i].fY - 90.4968) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 19.5801) < 0.001 && fabs(p_oFakeTrees[i].fY - 106.049) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 55.9998) < 0.001 && fabs(p_oFakeTrees[i].fY - 99.9207) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 45.343 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 68.3472) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 184.998) < 0.001 && fabs(p_oFakeTrees[i].fY - 180.701) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 33.7524) < 0.001 && fabs(p_oFakeTrees[i].fY - 49.9756) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 59.6191) < 0.001 && fabs(p_oFakeTrees[i].fY - 31.8787) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 49.1455) < 0.001 && fabs(p_oFakeTrees[i].fY - 97.522) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 13.8489) < 0.001 && fabs(p_oFakeTrees[i].fY - 137.787) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 154.895) < 0.001 && fabs(p_oFakeTrees[i].fY - 113.556) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 109.076) < 0.001 && fabs(p_oFakeTrees[i].fY - 174.786) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 177.356) < 0.001 && fabs(p_oFakeTrees[i].fY - 76.5503) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 124.768) < 0.001 && fabs(p_oFakeTrees[i].fY - 153.552) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 152.893) < 0.001 && fabs(p_oFakeTrees[i].fY - 26.2878) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 151.031) < 0.001 && fabs(p_oFakeTrees[i].fY - 123.383) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 41.095 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 153.882) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 166.052) < 0.001 && fabs(p_oFakeTrees[i].fY - 114.868) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 0.616455 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 32.3242) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 136.914) < 0.001 && fabs(p_oFakeTrees[i].fY - 123.224) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 132.843) < 0.001 && fabs(p_oFakeTrees[i].fY - 56.5002) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 38.9587) < 0.001 && fabs(p_oFakeTrees[i].fY - 101.501) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 169.391) < 0.001 && fabs(p_oFakeTrees[i].fY - 0.634766) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 164.771) < 0.001 && fabs(p_oFakeTrees[i].fY - 17.7979) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 190.045) < 0.001 && fabs(p_oFakeTrees[i].fY - 119.031) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 60.73) < 0.001 && fabs(p_oFakeTrees[i].fY - 120.459) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 170.929) < 0.001 && fabs(p_oFakeTrees[i].fY - 73.2056) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 193.604) < 0.001 && fabs(p_oFakeTrees[i].fY - 184.564) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 142.053) < 0.001 && fabs(p_oFakeTrees[i].fY - 105.682) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 83.8501) < 0.001 && fabs(p_oFakeTrees[i].fY - 91.803) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 41.0889) < 0.001 && fabs(p_oFakeTrees[i].fY - 84.6741) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 86.2854) < 0.001 && fabs(p_oFakeTrees[i].fY - 39.7644) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 55.2185) < 0.001 && fabs(p_oFakeTrees[i].fY - 19.574) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 81.8848) < 0.001 && fabs(p_oFakeTrees[i].fY - 121.558) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 196.49 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 168.988) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 60.8643) < 0.001 && fabs(p_oFakeTrees[i].fY - 45.8557) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 62.7808) < 0.001 && fabs(p_oFakeTrees[i].fY - 193.109) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 189.392) < 0.001 && fabs(p_oFakeTrees[i].fY - 28.1311) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 37.2925) < 0.001 && fabs(p_oFakeTrees[i].fY - 99.0234) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 105.481) < 0.001 && fabs(p_oFakeTrees[i].fY - 85.907) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 94.8059) < 0.001 && fabs(p_oFakeTrees[i].fY - 127.271) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 86.6516) < 0.001 && fabs(p_oFakeTrees[i].fY - 113.049) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 132.397) < 0.001 && fabs(p_oFakeTrees[i].fY - 84.8999) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 129.297) < 0.001 && fabs(p_oFakeTrees[i].fY - 188.177) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 78.9795) < 0.001 && fabs(p_oFakeTrees[i].fY - 66.7542) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 20.5322) < 0.001 && fabs(p_oFakeTrees[i].fY - 41.9495) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 181.128) < 0.001 && fabs(p_oFakeTrees[i].fY - 185.382) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 142.358) < 0.001 && fabs(p_oFakeTrees[i].fY - 10.8704) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 111.493) < 0.001 && fabs(p_oFakeTrees[i].fY - 28.5828) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 11.3342) < 0.001 && fabs(p_oFakeTrees[i].fY - 101.404) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 39.9719) < 0.001 && fabs(p_oFakeTrees[i].fY - 77.1362) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 77.9297) < 0.001 && fabs(p_oFakeTrees[i].fY - 85.907) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 178.888) < 0.001 && fabs(p_oFakeTrees[i].fY - 180.273) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 75.2197) < 0.001 && fabs(p_oFakeTrees[i].fY - 128.607) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 129.028) < 0.001 && fabs(p_oFakeTrees[i].fY - 15.5518) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 175.83 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 149.908) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 67.5964) < 0.001 && fabs(p_oFakeTrees[i].fY - 94.4275) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 35.8826) < 0.001 && fabs(p_oFakeTrees[i].fY - 173.944) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 157.532) < 0.001 && fabs(p_oFakeTrees[i].fY - 192.352) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 41.0278) < 0.001 && fabs(p_oFakeTrees[i].fY - 128.68) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 160.852) < 0.001 && fabs(p_oFakeTrees[i].fY - 67.6025) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 51.9287) < 0.001 && fabs(p_oFakeTrees[i].fY - 131.873) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 136.017) < 0.001 && fabs(p_oFakeTrees[i].fY - 164.508) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 33.3496) < 0.001 && fabs(p_oFakeTrees[i].fY - 99.0295) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 34.3628) < 0.001 && fabs(p_oFakeTrees[i].fY - 194.751) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 170.801) < 0.001 && fabs(p_oFakeTrees[i].fY - 153.412) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 36.5784) < 0.001 && fabs(p_oFakeTrees[i].fY - 103.125) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 94.5679) < 0.001 && fabs(p_oFakeTrees[i].fY - 43.811) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 19.3359) < 0.001 && fabs(p_oFakeTrees[i].fY - 27.6611) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 56.8909) < 0.001 && fabs(p_oFakeTrees[i].fY - 153.015) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 181.342) < 0.001 && fabs(p_oFakeTrees[i].fY - 42.0959) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 35.5408) < 0.001 && fabs(p_oFakeTrees[i].fY - 108.008) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 192.285) < 0.001 && fabs(p_oFakeTrees[i].fY - 177.661) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 120.184) < 0.001 && fabs(p_oFakeTrees[i].fY - 138.959) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 107.581) < 0.001 && fabs(p_oFakeTrees[i].fY - 115.912) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 38.7085) < 0.001 && fabs(p_oFakeTrees[i].fY - 109.65) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 86.6577) < 0.001 && fabs(p_oFakeTrees[i].fY - 181.042) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 191.797) < 0.001 && fabs(p_oFakeTrees[i].fY - 61.3586) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 13.7268) < 0.001 && fabs(p_oFakeTrees[i].fY - 27.3499) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 62.2925) < 0.001 && fabs(p_oFakeTrees[i].fY - 19.6533) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 54.5044) < 0.001 && fabs(p_oFakeTrees[i].fY - 85.0464) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 56.0608) < 0.001 && fabs(p_oFakeTrees[i].fY - 67.9138) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 32.3914) < 0.001 && fabs(p_oFakeTrees[i].fY - 38.4583) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 159.607) < 0.001 && fabs(p_oFakeTrees[i].fY - 6.84814) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 90.4358) < 0.001 && fabs(p_oFakeTrees[i].fY - 0.146484) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 75.415 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 142.963) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 129.84 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 16.8518) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 124.762) < 0.001 && fabs(p_oFakeTrees[i].fY - 37.3596) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 12.4146) < 0.001 && fabs(p_oFakeTrees[i].fY - 95.8923) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 32.5439) < 0.001 && fabs(p_oFakeTrees[i].fY - 121.399) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 129.327) < 0.001 && fabs(p_oFakeTrees[i].fY - 105.841) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 68.1885) < 0.001 && fabs(p_oFakeTrees[i].fY - 43.4875) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 167.676) < 0.001 && fabs(p_oFakeTrees[i].fY - 11.3281) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 48.114 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 156.976) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 131.586) < 0.001 && fabs(p_oFakeTrees[i].fY - 122.089) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 13.562 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 166.565) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 152.734) < 0.001 && fabs(p_oFakeTrees[i].fY - 98.5962) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 146.521) < 0.001 && fabs(p_oFakeTrees[i].fY - 53.0884) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 27.5635) < 0.001 && fabs(p_oFakeTrees[i].fY - 7.47681) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 192.706) < 0.001 && fabs(p_oFakeTrees[i].fY - 59.0942) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 152.82 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 70.8069) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 28.3142) < 0.001 && fabs(p_oFakeTrees[i].fY - 53.8513) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 21.4905) < 0.001 && fabs(p_oFakeTrees[i].fY - 195.148) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 138.66 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 49.8169) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 86.3342) < 0.001 && fabs(p_oFakeTrees[i].fY - 184.369) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 119.135) < 0.001 && fabs(p_oFakeTrees[i].fY - 65.9912) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 164.667) < 0.001 && fabs(p_oFakeTrees[i].fY - 195.239) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 111.023) < 0.001 && fabs(p_oFakeTrees[i].fY - 134.1) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 82.5439) < 0.001 && fabs(p_oFakeTrees[i].fY - 186.157) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 113.257) < 0.001 && fabs(p_oFakeTrees[i].fY - 52.887) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 111.572) < 0.001 && fabs(p_oFakeTrees[i].fY - 118.756) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 86.9263) < 0.001 && fabs(p_oFakeTrees[i].fY - 149.762) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 108.398) < 0.001 && fabs(p_oFakeTrees[i].fY - 138.153) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 120.306) < 0.001 && fabs(p_oFakeTrees[i].fY - 67.0227) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 158.167) < 0.001 && fabs(p_oFakeTrees[i].fY - 76.5991) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 18.3655) < 0.001 && fabs(p_oFakeTrees[i].fY - 106.775) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 168.292) < 0.001 && fabs(p_oFakeTrees[i].fY - 118.292) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 69.574 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 151.202) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 181.494) < 0.001 && fabs(p_oFakeTrees[i].fY - 95.4712) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 192.81 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 173.029) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 175.818) < 0.001 && fabs(p_oFakeTrees[i].fY - 90.9851) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 65.3809) < 0.001 && fabs(p_oFakeTrees[i].fY - 110.986) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 49.5972) < 0.001 && fabs(p_oFakeTrees[i].fY - 123.993) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 98.4619) < 0.001 && fabs(p_oFakeTrees[i].fY - 67.1326) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 53.3447) < 0.001 && fabs(p_oFakeTrees[i].fY - 129.956) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 103.998) < 0.001 && fabs(p_oFakeTrees[i].fY - 36.5784) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 104.248) < 0.001 && fabs(p_oFakeTrees[i].fY - 193.347) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 187) < 0.001 && fabs(p_oFakeTrees[i].fY - 155.127) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 168.207) < 0.001 && fabs(p_oFakeTrees[i].fY - 144.788) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 52.4353) < 0.001 && fabs(p_oFakeTrees[i].fY - 36.8652) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 66.4734) < 0.001 && fabs(p_oFakeTrees[i].fY - 177.948) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 80.426 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 130.377) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 47.1436) < 0.001 && fabs(p_oFakeTrees[i].fY - 183.905) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 45.2087) < 0.001 && fabs(p_oFakeTrees[i].fY - 138.226) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 111.749) < 0.001 && fabs(p_oFakeTrees[i].fY - 160.437) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 180.072) < 0.001 && fabs(p_oFakeTrees[i].fY - 124.53) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 131.75 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 156.403) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 199.5) < 0.001 && fabs(p_oFakeTrees[i].fY - 7.44629) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 26.0254) < 0.001 && fabs(p_oFakeTrees[i].fY - 196.973) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 169.58 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 59.4971) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 55.3345) < 0.001 && fabs(p_oFakeTrees[i].fY - 151.379) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 127.332) < 0.001 && fabs(p_oFakeTrees[i].fY - 33.3374) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 51.6235) < 0.001 && fabs(p_oFakeTrees[i].fY - 172.089) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 197.919) < 0.001 && fabs(p_oFakeTrees[i].fY - 47.9004) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 21.106 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 151.831) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 66.0767) < 0.001 && fabs(p_oFakeTrees[i].fY - 57.2632) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 47.0215) < 0.001 && fabs(p_oFakeTrees[i].fY - 151.764) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 46.1121) < 0.001 && fabs(p_oFakeTrees[i].fY - 174.646) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 120.709) < 0.001 && fabs(p_oFakeTrees[i].fY - 69.2139) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 106.915) < 0.001 && fabs(p_oFakeTrees[i].fY - 10.26) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 168.121) < 0.001 && fabs(p_oFakeTrees[i].fY - 136.176) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 5.07812) < 0.001 && fabs(p_oFakeTrees[i].fY - 35.9253) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 154.718) < 0.001 && fabs(p_oFakeTrees[i].fY - 161.206) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 99.115 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 25.6531) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 90.1855) < 0.001 && fabs(p_oFakeTrees[i].fY - 89.4592) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 15.3992) < 0.001 && fabs(p_oFakeTrees[i].fY - 184.686) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 28.5889) < 0.001 && fabs(p_oFakeTrees[i].fY - 119.635) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 140.363) < 0.001 && fabs(p_oFakeTrees[i].fY - 85.2173) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 82.2205) < 0.001 && fabs(p_oFakeTrees[i].fY - 159.558) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 156.238) < 0.001 && fabs(p_oFakeTrees[i].fY - 94.2017) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 115.497) < 0.001 && fabs(p_oFakeTrees[i].fY - 107.568) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 157.587) < 0.001 && fabs(p_oFakeTrees[i].fY - 163.226) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 137.091) < 0.001 && fabs(p_oFakeTrees[i].fY - 99.7742) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 121.1) < 0.001 && fabs(p_oFakeTrees[i].fY - 56.2927) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 173.56 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 24.4141) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 66.5344) < 0.001 && fabs(p_oFakeTrees[i].fY - 16.9006) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 106.824) < 0.001 && fabs(p_oFakeTrees[i].fY - 153.51) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 146.277) < 0.001 && fabs(p_oFakeTrees[i].fY - 30.3589) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 46.4966) < 0.001 && fabs(p_oFakeTrees[i].fY - 178.687) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 30.9509) < 0.001 && fabs(p_oFakeTrees[i].fY - 15.1672) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 127.551) < 0.001 && fabs(p_oFakeTrees[i].fY - 189.984) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 196.13 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 107.007) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 14.7034) < 0.001 && fabs(p_oFakeTrees[i].fY - 116.223) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 173.633) < 0.001 && fabs(p_oFakeTrees[i].fY - 23.4863) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 90.7227) < 0.001 && fabs(p_oFakeTrees[i].fY - 121.198) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 98.8098) < 0.001 && fabs(p_oFakeTrees[i].fY - 2.76489) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 153.906) < 0.001 && fabs(p_oFakeTrees[i].fY - 135.333) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 139.886) < 0.001 && fabs(p_oFakeTrees[i].fY - 110.84) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 2.44751) < 0.001 && fabs(p_oFakeTrees[i].fY - 74.7803) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 153.68 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 63.7573) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 19.7205) < 0.001 && fabs(p_oFakeTrees[i].fY - 37.6526) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 139.874) < 0.001 && fabs(p_oFakeTrees[i].fY - 83.4656) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 71.7957) < 0.001 && fabs(p_oFakeTrees[i].fY - 163.202) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 86.1755) < 0.001 && fabs(p_oFakeTrees[i].fY - 106.824) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 136.23 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 47.229) < 0.001) p_oFakeTrees[i].bDead = true;


      //*********************************************
      // Trembling Aspen
      //*********************************************
      else if (fabs(p_oFakeTrees[i].fX - 182.666) < 0.001 && fabs(p_oFakeTrees[i].fY - 31.0364) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 135.48 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 100.342) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 50.0061) < 0.001 && fabs(p_oFakeTrees[i].fY - 25.592) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 111.713) < 0.001 && fabs(p_oFakeTrees[i].fY - 53.0701) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 108.85 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 45.9473) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 3.61938) < 0.001 && fabs(p_oFakeTrees[i].fY - 94.5862) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 106.25 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 119.873) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 9.97925) < 0.001 && fabs(p_oFakeTrees[i].fY - 90.448) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 115.051) < 0.001 && fabs(p_oFakeTrees[i].fY - 38.6902) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 92.688 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 182.611) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 94.9951) < 0.001 && fabs(p_oFakeTrees[i].fY - 79.1016) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 110.663) < 0.001 && fabs(p_oFakeTrees[i].fY - 104.822) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 111.42 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 152.234) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 111.823) < 0.001 && fabs(p_oFakeTrees[i].fY - 119.897) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 196.808) < 0.001 && fabs(p_oFakeTrees[i].fY - 11.8042) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 30.8594) < 0.001 && fabs(p_oFakeTrees[i].fY - 182.654) < 0.001) p_oFakeTrees[i].bDead = true;

      //*********************************************
      // Black Cottonwood
      //*********************************************
      else if (fabs(p_oFakeTrees[i].fX - 110.889) < 0.001 && fabs(p_oFakeTrees[i].fY - 110.76) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 139.819) < 0.001 && fabs(p_oFakeTrees[i].fY - 14.624) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 112.366) < 0.001 && fabs(p_oFakeTrees[i].fY - 47.6074) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 123.578) < 0.001 && fabs(p_oFakeTrees[i].fY - 48.6084) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 24.2249) < 0.001 && fabs(p_oFakeTrees[i].fY - 180.219) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 197.632) < 0.001 && fabs(p_oFakeTrees[i].fY - 157.861) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 111.249) < 0.001 && fabs(p_oFakeTrees[i].fY - 9.65576) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 101.013) < 0.001 && fabs(p_oFakeTrees[i].fY - 165.723) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 39.3066) < 0.001 && fabs(p_oFakeTrees[i].fY - 143.207) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 45.6909) < 0.001 && fabs(p_oFakeTrees[i].fY - 28.064) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 120.911) < 0.001 && fabs(p_oFakeTrees[i].fY - 14.6179) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 198.151) < 0.001 && fabs(p_oFakeTrees[i].fY - 157.324) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 185.217) < 0.001 && fabs(p_oFakeTrees[i].fY - 81.8359) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 1.37939) < 0.001 && fabs(p_oFakeTrees[i].fY - 39.3188) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 108.154) < 0.001 && fabs(p_oFakeTrees[i].fY - 129.559) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 101.019) < 0.001 && fabs(p_oFakeTrees[i].fY - 137.213) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 143.634) < 0.001 && fabs(p_oFakeTrees[i].fY - 182.379) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 96.2036) < 0.001 && fabs(p_oFakeTrees[i].fY - 1.5686) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 178.082) < 0.001 && fabs(p_oFakeTrees[i].fY - 38.6414) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 0.0244141) < 0.001 && fabs(p_oFakeTrees[i].fY - 18.6401) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 113.177) < 0.001 && fabs(p_oFakeTrees[i].fY - 102.356) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 179.376) < 0.001 && fabs(p_oFakeTrees[i].fY - 100.708) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 104.541) < 0.001 && fabs(p_oFakeTrees[i].fY - 128.662) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 123.816) < 0.001 && fabs(p_oFakeTrees[i].fY - 147.052) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 26.8005) < 0.001 && fabs(p_oFakeTrees[i].fY - 78.6072) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 99.7314) < 0.001 && fabs(p_oFakeTrees[i].fY - 21.3623) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 93.3777) < 0.001 && fabs(p_oFakeTrees[i].fY - 34.7412) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 138.806) < 0.001 && fabs(p_oFakeTrees[i].fY - 145.758) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 33.9539) < 0.001 && fabs(p_oFakeTrees[i].fY - 17.0532) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 177.277) < 0.001 && fabs(p_oFakeTrees[i].fY - 155.872) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 8.42285) < 0.001 && fabs(p_oFakeTrees[i].fY - 22.8088) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 111.066) < 0.001 && fabs(p_oFakeTrees[i].fY - 157.922) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 95.7336) < 0.001 && fabs(p_oFakeTrees[i].fY - 161.938) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 136.646) < 0.001 && fabs(p_oFakeTrees[i].fY - 125.232) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 3.4729 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 9.44214) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 180.469) < 0.001 && fabs(p_oFakeTrees[i].fY - 156.335) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 13.1836) < 0.001 && fabs(p_oFakeTrees[i].fY - 92.5842) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 10.5713) < 0.001 && fabs(p_oFakeTrees[i].fY - 79.6814) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 92.926 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 88.324) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 140.521) < 0.001 && fabs(p_oFakeTrees[i].fY - 43.5669) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 113.336) < 0.001 && fabs(p_oFakeTrees[i].fY - 77.9236) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 194.592) < 0.001 && fabs(p_oFakeTrees[i].fY - 102.588) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 25.1648) < 0.001 && fabs(p_oFakeTrees[i].fY - 51.825) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 7.06177) < 0.001 && fabs(p_oFakeTrees[i].fY - 28.0029) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 66.8579) < 0.001 && fabs(p_oFakeTrees[i].fY - 165.387) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 182.733) < 0.001 && fabs(p_oFakeTrees[i].fY - 180.237) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 120.801) < 0.001 && fabs(p_oFakeTrees[i].fY - 169.794) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 25.6531) < 0.001 && fabs(p_oFakeTrees[i].fY - 98.3643) < 0.001) p_oFakeTrees[i].bDead = true;

      //*********************************************
      // Species 8
      //*********************************************
      else if (fabs(p_oFakeTrees[i].fX - 97.8333) < 0.001 && fabs(p_oFakeTrees[i].fY - 126.642) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 87.5305) < 0.001 && fabs(p_oFakeTrees[i].fY - 47.4609) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 51.4587) < 0.001 && fabs(p_oFakeTrees[i].fY - 190.485) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 108.575) < 0.001 && fabs(p_oFakeTrees[i].fY - 172.308) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 101.007) < 0.001 && fabs(p_oFakeTrees[i].fY - 120.526) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 187.897) < 0.001 && fabs(p_oFakeTrees[i].fY - 129.346) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 0.396729 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 176.636) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 123.407) < 0.001 && fabs(p_oFakeTrees[i].fY - 152.02) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 8.77686) < 0.001 && fabs(p_oFakeTrees[i].fY - 3.38745) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 8.70972) < 0.001 && fabs(p_oFakeTrees[i].fY - 47.7356) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 186.31 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 157.55) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 195.477) < 0.001 && fabs(p_oFakeTrees[i].fY - 108.527) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 118.506) < 0.001 && fabs(p_oFakeTrees[i].fY - 150.482) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 100.006) < 0.001 && fabs(p_oFakeTrees[i].fY - 173.853) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 173.602) < 0.001 && fabs(p_oFakeTrees[i].fY - 50.946) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 141.351) < 0.001 && fabs(p_oFakeTrees[i].fY - 122.467) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 112.299) < 0.001 && fabs(p_oFakeTrees[i].fY - 46.7957) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 110.925) < 0.001 && fabs(p_oFakeTrees[i].fY - 172.809) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 14.8376) < 0.001 && fabs(p_oFakeTrees[i].fY - 51.593) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 18.4998) < 0.001 && fabs(p_oFakeTrees[i].fY - 23.1384) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 108.649) < 0.001 && fabs(p_oFakeTrees[i].fY - 2.20947) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 195.166) < 0.001 && fabs(p_oFakeTrees[i].fY - 109.32) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 175.061) < 0.001 && fabs(p_oFakeTrees[i].fY - 21.2585) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 25.1343) < 0.001 && fabs(p_oFakeTrees[i].fY - 62.7686) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 124.036) < 0.001 && fabs(p_oFakeTrees[i].fY - 17.4194) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 135.364) < 0.001 && fabs(p_oFakeTrees[i].fY - 119.525) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 175.073) < 0.001 && fabs(p_oFakeTrees[i].fY - 88.2996) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 33.9294) < 0.001 && fabs(p_oFakeTrees[i].fY - 151.782) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 34.3689) < 0.001 && fabs(p_oFakeTrees[i].fY - 56.2073) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 125.177) < 0.001 && fabs(p_oFakeTrees[i].fY - 127.399) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 101.447) < 0.001 && fabs(p_oFakeTrees[i].fY - 77.1729) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 101.831) < 0.001 && fabs(p_oFakeTrees[i].fY - 167.291) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 18.0481) < 0.001 && fabs(p_oFakeTrees[i].fY - 108.502) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 187.006) < 0.001 && fabs(p_oFakeTrees[i].fY - 173.682) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 181.885) < 0.001 && fabs(p_oFakeTrees[i].fY - 165.039) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 19.2322) < 0.001 && fabs(p_oFakeTrees[i].fY - 109.54) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 19.7205) < 0.001 && fabs(p_oFakeTrees[i].fY - 118.402) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 199.982) < 0.001 && fabs(p_oFakeTrees[i].fY - 155.444) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 107.495) < 0.001 && fabs(p_oFakeTrees[i].fY - 42.4377) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 174.298) < 0.001 && fabs(p_oFakeTrees[i].fY - 121.887) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 173.944) < 0.001 && fabs(p_oFakeTrees[i].fY - 4.42505) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 19.6045) < 0.001 && fabs(p_oFakeTrees[i].fY - 38.8428) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 122.247) < 0.001 && fabs(p_oFakeTrees[i].fY - 4.82178) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 140.668) < 0.001 && fabs(p_oFakeTrees[i].fY - 136.847) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 195.209) < 0.001 && fabs(p_oFakeTrees[i].fY - 70.3125) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 174.097) < 0.001 && fabs(p_oFakeTrees[i].fY - 111.536) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 126.721) < 0.001 && fabs(p_oFakeTrees[i].fY - 27.9663) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 16.4246) < 0.001 && fabs(p_oFakeTrees[i].fY - 177.063) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 13.9648) < 0.001 && fabs(p_oFakeTrees[i].fY - 90.4175) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 94.8364) < 0.001 && fabs(p_oFakeTrees[i].fY - 156.635) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 183.734) < 0.001 && fabs(p_oFakeTrees[i].fY - 86.7798) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 103.9) < 0.001 && fabs(p_oFakeTrees[i].fY - 132.855) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 81.4087) < 0.001 && fabs(p_oFakeTrees[i].fY - 135.193) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 31.0974) < 0.001 && fabs(p_oFakeTrees[i].fY - 74.9023) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 193.225) < 0.001 && fabs(p_oFakeTrees[i].fY - 162.28) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 175.385) < 0.001 && fabs(p_oFakeTrees[i].fY - 5.40161) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 56.4697) < 0.001 && fabs(p_oFakeTrees[i].fY - 167.139) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 182.782) < 0.001 && fabs(p_oFakeTrees[i].fY - 143.738) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 142.322) < 0.001 && fabs(p_oFakeTrees[i].fY - 80.3406) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 19.1711) < 0.001 && fabs(p_oFakeTrees[i].fY - 61.3708) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 120.453) < 0.001 && fabs(p_oFakeTrees[i].fY - 124.731) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 197.443) < 0.001 && fabs(p_oFakeTrees[i].fY - 120.703) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 136.334) < 0.001 && fabs(p_oFakeTrees[i].fY - 37.5732) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 94.8486) < 0.001 && fabs(p_oFakeTrees[i].fY - 1.94092) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 137.891) < 0.001 && fabs(p_oFakeTrees[i].fY - 155.591) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 14.4653) < 0.001 && fabs(p_oFakeTrees[i].fY - 47.7112) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 112.189) < 0.001 && fabs(p_oFakeTrees[i].fY - 20.3796) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 186.017) < 0.001 && fabs(p_oFakeTrees[i].fY - 69.22) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 124.036) < 0.001 && fabs(p_oFakeTrees[i].fY - 145.728) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 136.09 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 125.092) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 111.89 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 25.5493) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 187.75 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 88.2446) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 91.6077) < 0.001 && fabs(p_oFakeTrees[i].fY - 164.447) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 194.415) < 0.001 && fabs(p_oFakeTrees[i].fY - 180.652) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 103.943) < 0.001 && fabs(p_oFakeTrees[i].fY - 93.4204) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 55.0781) < 0.001 && fabs(p_oFakeTrees[i].fY - 127.094) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 98.5168) < 0.001 && fabs(p_oFakeTrees[i].fY - 43.5486) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 113.947) < 0.001 && fabs(p_oFakeTrees[i].fY - 97.052) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 8.47778) < 0.001 && fabs(p_oFakeTrees[i].fY - 67.9626) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 20.5688) < 0.001 && fabs(p_oFakeTrees[i].fY - 15.2893) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 27.3438) < 0.001 && fabs(p_oFakeTrees[i].fY - 54.4434) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 15.8386) < 0.001 && fabs(p_oFakeTrees[i].fY - 171.686) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 131.403) < 0.001 && fabs(p_oFakeTrees[i].fY - 184.003) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 116.18 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 177.57) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 141.443) < 0.001 && fabs(p_oFakeTrees[i].fY - 2.7771) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 26.2146) < 0.001 && fabs(p_oFakeTrees[i].fY - 187.976) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 82.428 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 74.7192) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 109.131) < 0.001 && fabs(p_oFakeTrees[i].fY - 136.359) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 94.635 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 61.8286) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 112.61 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 139.526) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 172.986) < 0.001 && fabs(p_oFakeTrees[i].fY - 154.852) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 46.9604) < 0.001 && fabs(p_oFakeTrees[i].fY - 64.7156) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 106.378) < 0.001 && fabs(p_oFakeTrees[i].fY - 90.6311) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 176.855) < 0.001 && fabs(p_oFakeTrees[i].fY - 47.522) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 116.486) < 0.001 && fabs(p_oFakeTrees[i].fY - 193.408) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 167.578) < 0.001 && fabs(p_oFakeTrees[i].fY - 195.734) < 0.001) p_oFakeTrees[i].bDead = true;


      //*********************************************
      // Species 5
      //*********************************************
      else if (fabs(p_oFakeTrees[i].fX - 118.561) < 0.001 && fabs(p_oFakeTrees[i].fY - 174.622) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 40.5151) < 0.001 && fabs(p_oFakeTrees[i].fY - 1.25732) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 103.717) < 0.001 && fabs(p_oFakeTrees[i].fY - 79.126) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 20.3247) < 0.001 && fabs(p_oFakeTrees[i].fY - 62.5305) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 11.438 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 125.458) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 134.583) < 0.001 && fabs(p_oFakeTrees[i].fY - 189.154) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 65.6555) < 0.001 && fabs(p_oFakeTrees[i].fY - 58.7036) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 103.162) < 0.001 && fabs(p_oFakeTrees[i].fY - 195.148) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 131.708) < 0.001 && fabs(p_oFakeTrees[i].fY - 131.744) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 19.8853) < 0.001 && fabs(p_oFakeTrees[i].fY - 77.2583) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 178.192) < 0.001 && fabs(p_oFakeTrees[i].fY - 8.5022) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 104.382) < 0.001 && fabs(p_oFakeTrees[i].fY - 122.729) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 110.028) < 0.001 && fabs(p_oFakeTrees[i].fY - 45.0562) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 110.51 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 14.1785) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 169.94 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 123.12) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 100.494) < 0.001 && fabs(p_oFakeTrees[i].fY - 189.032) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 125.69 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 69.9341) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 153.912) < 0.001 && fabs(p_oFakeTrees[i].fY - 70.2759) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 190.338) < 0.001 && fabs(p_oFakeTrees[i].fY - 98.6755) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 130.975) < 0.001 && fabs(p_oFakeTrees[i].fY - 119.8) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 13.9832) < 0.001 && fabs(p_oFakeTrees[i].fY - 81.7261) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 154.205) < 0.001 && fabs(p_oFakeTrees[i].fY - 41.3818) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 177.948) < 0.001 && fabs(p_oFakeTrees[i].fY - 28.5034) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 163.562) < 0.001 && fabs(p_oFakeTrees[i].fY - 17.1753) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 14.74) < 0.001 && fabs(p_oFakeTrees[i].fY - 69.5496) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 45.8984) < 0.001 && fabs(p_oFakeTrees[i].fY - 118.671) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 75.7385) < 0.001 && fabs(p_oFakeTrees[i].fY - 42.2424) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 76.5259) < 0.001 && fabs(p_oFakeTrees[i].fY - 24.2798) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 107.245) < 0.001 && fabs(p_oFakeTrees[i].fY - 60.5713) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 142.212) < 0.001 && fabs(p_oFakeTrees[i].fY - 46.0266) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 33.4961) < 0.001 && fabs(p_oFakeTrees[i].fY - 91.2659) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 71.3989) < 0.001 && fabs(p_oFakeTrees[i].fY - 1.0376) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 83.5144) < 0.001 && fabs(p_oFakeTrees[i].fY - 38.0371) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 192.169) < 0.001 && fabs(p_oFakeTrees[i].fY - 17.4316) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 16.4734) < 0.001 && fabs(p_oFakeTrees[i].fY - 92.1997) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 61.5967) < 0.001 && fabs(p_oFakeTrees[i].fY - 179.272) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 146.838) < 0.001 && fabs(p_oFakeTrees[i].fY - 54.0588) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 50.0549) < 0.001 && fabs(p_oFakeTrees[i].fY - 151.318) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 2.56348) < 0.001 && fabs(p_oFakeTrees[i].fY - 3.32031) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 118.622) < 0.001 && fabs(p_oFakeTrees[i].fY - 58.7952) < 0.001) p_oFakeTrees[i].bDead = true;

    }

    CheckHarvestResults(p_oPop, iNumTrees, p_oFakeTrees);

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


    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}


/////////////////////////////////////////////////////////////////////////////
// DoHarvestRun9()
// Performs the ninth harvest run. This tests priorities.
/////////////////////////////////////////////////////////////////////////////
TEST(Harvest, DoHarvestRun9a) {

  clTreePopulation * p_oPop;
  clTreeSearch *p_oAllTrees;
  clTree *p_oTree;
  float fTemp;
  int iNumTrees = 1980, iCounter = 0, i;
  treestruct *p_oFakeTrees = new treestruct[iNumTrees];

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {

    p_oSimManager->ReadFile( WriteHarvestXMLFile9(false) );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

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

    //Run harvest only
    p_oSimManager->SetCurrentTimestep(1);
    clBehaviorBase *p_oBase = p_oSimManager->GetBehaviorObject(0);
    clDisturbance *p_oHarv = dynamic_cast<clDisturbance*>(p_oBase);
    p_oHarv->Action();


    //Expected results
    for (i = 0; i < iNumTrees; i++) {

      //*********************************************
      // Western Redcedar
      //*********************************************
      if (fabs(p_oFakeTrees[i].fX - 77.9907) < 0.001 && fabs(p_oFakeTrees[i].fY - 31.0547) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 24.115 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 63.385) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 72.8882) < 0.001 && fabs(p_oFakeTrees[i].fY - 57.0251) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 13.7878) < 0.001 && fabs(p_oFakeTrees[i].fY - 4.45557) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 4.88281) < 0.001 && fabs(p_oFakeTrees[i].fY - 122.552) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 38.6169) < 0.001 && fabs(p_oFakeTrees[i].fY - 30.7434) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 23.9258) < 0.001 && fabs(p_oFakeTrees[i].fY - 142.303) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 23.0591) < 0.001 && fabs(p_oFakeTrees[i].fY - 106.61) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 26.1353) < 0.001 && fabs(p_oFakeTrees[i].fY - 12.0361) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 34.8328) < 0.001 && fabs(p_oFakeTrees[i].fY - 78.3508) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 48.4192) < 0.001 && fabs(p_oFakeTrees[i].fY - 126.709) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 10.4248) < 0.001 && fabs(p_oFakeTrees[i].fY - 64.4287) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 67.4255) < 0.001 && fabs(p_oFakeTrees[i].fY - 15.8325) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 67.3645) < 0.001 && fabs(p_oFakeTrees[i].fY - 97.4365) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 71.5698) < 0.001 && fabs(p_oFakeTrees[i].fY - 29.4067) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 51.1841) < 0.001 && fabs(p_oFakeTrees[i].fY - 48.3032) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 16.2048) < 0.001 && fabs(p_oFakeTrees[i].fY - 109.18) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 21.1365) < 0.001 && fabs(p_oFakeTrees[i].fY - 185.858) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 63.4644) < 0.001 && fabs(p_oFakeTrees[i].fY - 38.6047) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 48.0469) < 0.001 && fabs(p_oFakeTrees[i].fY - 89.1907) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 38.2812) < 0.001 && fabs(p_oFakeTrees[i].fY - 52.655) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 44.6594) < 0.001 && fabs(p_oFakeTrees[i].fY - 73.0042) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 10.199 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 141.699) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 44.9829) < 0.001 && fabs(p_oFakeTrees[i].fY - 33.9539) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 15.0879) < 0.001 && fabs(p_oFakeTrees[i].fY - 16.2659) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 56.2561) < 0.001 && fabs(p_oFakeTrees[i].fY - 193.231) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 77.9175) < 0.001 && fabs(p_oFakeTrees[i].fY - 94.0369) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 11.1511) < 0.001 && fabs(p_oFakeTrees[i].fY - 53.1677) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 32.1533) < 0.001 && fabs(p_oFakeTrees[i].fY - 123.181) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 9.33838) < 0.001 && fabs(p_oFakeTrees[i].fY - 86.4929) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 39.2395) < 0.001 && fabs(p_oFakeTrees[i].fY - 87.8357) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 46.5942) < 0.001 && fabs(p_oFakeTrees[i].fY - 29.9683) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 64.9048) < 0.001 && fabs(p_oFakeTrees[i].fY - 123.749) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 24.3286) < 0.001 && fabs(p_oFakeTrees[i].fY - 157.99) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 50.885 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 166.345) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 1.30005) < 0.001 && fabs(p_oFakeTrees[i].fY - 85.4675) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 66.7664) < 0.001 && fabs(p_oFakeTrees[i].fY - 136.639) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 38.0066) < 0.001 && fabs(p_oFakeTrees[i].fY - 83.2336) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 54.5044) < 0.001 && fabs(p_oFakeTrees[i].fY - 17.5354) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 10.8154) < 0.001 && fabs(p_oFakeTrees[i].fY - 120.825) < 0.001) p_oFakeTrees[i].bDead = true;


      //*********************************************
      // Amabilis Fir
      //*********************************************
      else if (fabs(p_oFakeTrees[i].fX - 165.485) < 0.001 && fabs(p_oFakeTrees[i].fY - 143.365) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 157.452) < 0.001 && fabs(p_oFakeTrees[i].fY - 134.991) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 179.108) < 0.001 && fabs(p_oFakeTrees[i].fY - 173.303) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 48.3582) < 0.001 && fabs(p_oFakeTrees[i].fY - 180.725) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 163.367) < 0.001 && fabs(p_oFakeTrees[i].fY - 33.5144) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 157.66 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 81.9031) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 198.608) < 0.001 && fabs(p_oFakeTrees[i].fY - 44.8059) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 47.76) < 0.001 && fabs(p_oFakeTrees[i].fY - 42.3767) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 176.904) < 0.001 && fabs(p_oFakeTrees[i].fY - 15.1733) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 123.419) < 0.001 && fabs(p_oFakeTrees[i].fY - 23.3643) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 133.496) < 0.001 && fabs(p_oFakeTrees[i].fY - 46.814) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 108.997) < 0.001 && fabs(p_oFakeTrees[i].fY - 165.833) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 10.3027) < 0.001 && fabs(p_oFakeTrees[i].fY - 175.47) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 194.452) < 0.001 && fabs(p_oFakeTrees[i].fY - 178.802) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 156.732) < 0.001 && fabs(p_oFakeTrees[i].fY - 37.8967) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 85.8704) < 0.001 && fabs(p_oFakeTrees[i].fY - 112.659) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 28.8818) < 0.001 && fabs(p_oFakeTrees[i].fY - 117.932) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 66.0461) < 0.001 && fabs(p_oFakeTrees[i].fY - 133.484) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 116.528) < 0.001 && fabs(p_oFakeTrees[i].fY - 112.451) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 35.8765) < 0.001 && fabs(p_oFakeTrees[i].fY - 168.518) < 0.001) p_oFakeTrees[i].bDead = true;


      //*********************************************
      // Subalpine Fir
      //*********************************************
      else if (fabs(p_oFakeTrees[i].fX - 137.219) < 0.001 && fabs(p_oFakeTrees[i].fY - 70.6909) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 169.672) < 0.001 && fabs(p_oFakeTrees[i].fY - 46.7957) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 134.082) < 0.001 && fabs(p_oFakeTrees[i].fY - 185.791) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 164.972) < 0.001 && fabs(p_oFakeTrees[i].fY - 183.441) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 87.3169) < 0.001 && fabs(p_oFakeTrees[i].fY - 198.584) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 133.502) < 0.001 && fabs(p_oFakeTrees[i].fY - 126.794) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 54.0466) < 0.001 && fabs(p_oFakeTrees[i].fY - 167.749) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 55.7434) < 0.001 && fabs(p_oFakeTrees[i].fY - 180.17) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 189.929) < 0.001 && fabs(p_oFakeTrees[i].fY - 35.6934) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 131.775) < 0.001 && fabs(p_oFakeTrees[i].fY - 156.055) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 36.6211) < 0.001 && fabs(p_oFakeTrees[i].fY - 156.097) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 42.6636) < 0.001 && fabs(p_oFakeTrees[i].fY - 114.465) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 89.1785) < 0.001 && fabs(p_oFakeTrees[i].fY - 100.226) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 86.2854) < 0.001 && fabs(p_oFakeTrees[i].fY - 59.3201) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 91.1743) < 0.001 && fabs(p_oFakeTrees[i].fY - 12.4817) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 40.3015) < 0.001 && fabs(p_oFakeTrees[i].fY - 171.814) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 151.813) < 0.001 && fabs(p_oFakeTrees[i].fY - 70.7886) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 14.4775) < 0.001 && fabs(p_oFakeTrees[i].fY - 130.17) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 32.0435) < 0.001 && fabs(p_oFakeTrees[i].fY - 39.6667) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 5.98145) < 0.001 && fabs(p_oFakeTrees[i].fY - 22.345) < 0.001) p_oFakeTrees[i].bDead = true;

      //*********************************************
      // Hybrid Spruce
      //*********************************************
      else if (fabs(p_oFakeTrees[i].fX - 156.14 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 99.6399) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 147.949) < 0.001 && fabs(p_oFakeTrees[i].fY - 70.7886) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 62.207 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 123.401) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 188.361) < 0.001 && fabs(p_oFakeTrees[i].fY - 39.8315) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 150.958) < 0.001 && fabs(p_oFakeTrees[i].fY - 80.1636) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 84.1309) < 0.001 && fabs(p_oFakeTrees[i].fY - 90.4968) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 19.5801) < 0.001 && fabs(p_oFakeTrees[i].fY - 106.049) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 55.9998) < 0.001 && fabs(p_oFakeTrees[i].fY - 99.9207) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 45.343 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 68.3472) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 184.998) < 0.001 && fabs(p_oFakeTrees[i].fY - 180.701) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 33.7524) < 0.001 && fabs(p_oFakeTrees[i].fY - 49.9756) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 59.6191) < 0.001 && fabs(p_oFakeTrees[i].fY - 31.8787) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 49.1455) < 0.001 && fabs(p_oFakeTrees[i].fY - 97.522) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 13.8489) < 0.001 && fabs(p_oFakeTrees[i].fY - 137.787) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 154.895) < 0.001 && fabs(p_oFakeTrees[i].fY - 113.556) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 109.076) < 0.001 && fabs(p_oFakeTrees[i].fY - 174.786) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 177.356) < 0.001 && fabs(p_oFakeTrees[i].fY - 76.5503) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 124.768) < 0.001 && fabs(p_oFakeTrees[i].fY - 153.552) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 152.893) < 0.001 && fabs(p_oFakeTrees[i].fY - 26.2878) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 151.031) < 0.001 && fabs(p_oFakeTrees[i].fY - 123.383) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 41.095 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 153.882) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 166.052) < 0.001 && fabs(p_oFakeTrees[i].fY - 114.868) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 0.616455 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 32.3242) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 136.914) < 0.001 && fabs(p_oFakeTrees[i].fY - 123.224) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 132.843) < 0.001 && fabs(p_oFakeTrees[i].fY - 56.5002) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 38.9587) < 0.001 && fabs(p_oFakeTrees[i].fY - 101.501) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 169.391) < 0.001 && fabs(p_oFakeTrees[i].fY - 0.634766) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 164.771) < 0.001 && fabs(p_oFakeTrees[i].fY - 17.7979) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 190.045) < 0.001 && fabs(p_oFakeTrees[i].fY - 119.031) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 60.73) < 0.001 && fabs(p_oFakeTrees[i].fY - 120.459) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 170.929) < 0.001 && fabs(p_oFakeTrees[i].fY - 73.2056) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 193.604) < 0.001 && fabs(p_oFakeTrees[i].fY - 184.564) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 142.053) < 0.001 && fabs(p_oFakeTrees[i].fY - 105.682) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 83.8501) < 0.001 && fabs(p_oFakeTrees[i].fY - 91.803) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 41.0889) < 0.001 && fabs(p_oFakeTrees[i].fY - 84.6741) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 86.2854) < 0.001 && fabs(p_oFakeTrees[i].fY - 39.7644) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 55.2185) < 0.001 && fabs(p_oFakeTrees[i].fY - 19.574) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 81.8848) < 0.001 && fabs(p_oFakeTrees[i].fY - 121.558) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 196.49 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 168.988) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 60.8643) < 0.001 && fabs(p_oFakeTrees[i].fY - 45.8557) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 62.7808) < 0.001 && fabs(p_oFakeTrees[i].fY - 193.109) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 37.2925) < 0.001 && fabs(p_oFakeTrees[i].fY - 99.0234) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 105.481) < 0.001 && fabs(p_oFakeTrees[i].fY - 85.907) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 94.8059) < 0.001 && fabs(p_oFakeTrees[i].fY - 127.271) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 86.6516) < 0.001 && fabs(p_oFakeTrees[i].fY - 113.049) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 132.397) < 0.001 && fabs(p_oFakeTrees[i].fY - 84.8999) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 129.297) < 0.001 && fabs(p_oFakeTrees[i].fY - 188.177) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 78.9795) < 0.001 && fabs(p_oFakeTrees[i].fY - 66.7542) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 20.5322) < 0.001 && fabs(p_oFakeTrees[i].fY - 41.9495) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 181.128) < 0.001 && fabs(p_oFakeTrees[i].fY - 185.382) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 142.358) < 0.001 && fabs(p_oFakeTrees[i].fY - 10.8704) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 111.493) < 0.001 && fabs(p_oFakeTrees[i].fY - 28.5828) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 11.3342) < 0.001 && fabs(p_oFakeTrees[i].fY - 101.404) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 39.9719) < 0.001 && fabs(p_oFakeTrees[i].fY - 77.1362) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 77.9297) < 0.001 && fabs(p_oFakeTrees[i].fY - 85.907) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 178.888) < 0.001 && fabs(p_oFakeTrees[i].fY - 180.273) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 75.2197) < 0.001 && fabs(p_oFakeTrees[i].fY - 128.607) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 129.028) < 0.001 && fabs(p_oFakeTrees[i].fY - 15.5518) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 175.83 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 149.908) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 67.5964) < 0.001 && fabs(p_oFakeTrees[i].fY - 94.4275) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 35.8826) < 0.001 && fabs(p_oFakeTrees[i].fY - 173.944) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 157.532) < 0.001 && fabs(p_oFakeTrees[i].fY - 192.352) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 41.0278) < 0.001 && fabs(p_oFakeTrees[i].fY - 128.68) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 160.852) < 0.001 && fabs(p_oFakeTrees[i].fY - 67.6025) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 51.9287) < 0.001 && fabs(p_oFakeTrees[i].fY - 131.873) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 136.017) < 0.001 && fabs(p_oFakeTrees[i].fY - 164.508) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 33.3496) < 0.001 && fabs(p_oFakeTrees[i].fY - 99.0295) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 34.3628) < 0.001 && fabs(p_oFakeTrees[i].fY - 194.751) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 170.801) < 0.001 && fabs(p_oFakeTrees[i].fY - 153.412) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 36.5784) < 0.001 && fabs(p_oFakeTrees[i].fY - 103.125) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 94.5679) < 0.001 && fabs(p_oFakeTrees[i].fY - 43.811) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 19.3359) < 0.001 && fabs(p_oFakeTrees[i].fY - 27.6611) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 56.8909) < 0.001 && fabs(p_oFakeTrees[i].fY - 153.015) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 181.342) < 0.001 && fabs(p_oFakeTrees[i].fY - 42.0959) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 35.5408) < 0.001 && fabs(p_oFakeTrees[i].fY - 108.008) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 192.285) < 0.001 && fabs(p_oFakeTrees[i].fY - 177.661) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 120.184) < 0.001 && fabs(p_oFakeTrees[i].fY - 138.959) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 107.581) < 0.001 && fabs(p_oFakeTrees[i].fY - 115.912) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 38.7085) < 0.001 && fabs(p_oFakeTrees[i].fY - 109.65) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 86.6577) < 0.001 && fabs(p_oFakeTrees[i].fY - 181.042) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 191.797) < 0.001 && fabs(p_oFakeTrees[i].fY - 61.3586) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 13.7268) < 0.001 && fabs(p_oFakeTrees[i].fY - 27.3499) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 62.2925) < 0.001 && fabs(p_oFakeTrees[i].fY - 19.6533) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 54.5044) < 0.001 && fabs(p_oFakeTrees[i].fY - 85.0464) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 8.88062) < 0.001 && fabs(p_oFakeTrees[i].fY - 193.494) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 99.5239) < 0.001 && fabs(p_oFakeTrees[i].fY - 27.5391) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 56.0608) < 0.001 && fabs(p_oFakeTrees[i].fY - 67.9138) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 32.3914) < 0.001 && fabs(p_oFakeTrees[i].fY - 38.4583) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 159.607) < 0.001 && fabs(p_oFakeTrees[i].fY - 6.84814) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 90.4358) < 0.001 && fabs(p_oFakeTrees[i].fY - 0.146484) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 18.6279) < 0.001 && fabs(p_oFakeTrees[i].fY - 22.4121) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 75.415 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 142.963) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 129.84 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 16.8518) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 124.762) < 0.001 && fabs(p_oFakeTrees[i].fY - 37.3596) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 12.4146) < 0.001 && fabs(p_oFakeTrees[i].fY - 95.8923) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 32.5439) < 0.001 && fabs(p_oFakeTrees[i].fY - 121.399) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 111.658) < 0.001 && fabs(p_oFakeTrees[i].fY - 11.4563) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 129.327) < 0.001 && fabs(p_oFakeTrees[i].fY - 105.841) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 27.0752) < 0.001 && fabs(p_oFakeTrees[i].fY - 166.302) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 68.1885) < 0.001 && fabs(p_oFakeTrees[i].fY - 43.4875) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 167.676) < 0.001 && fabs(p_oFakeTrees[i].fY - 11.3281) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 48.114 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 156.976) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 131.586) < 0.001 && fabs(p_oFakeTrees[i].fY - 122.089) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 177.417) < 0.001 && fabs(p_oFakeTrees[i].fY - 32.0923) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 13.562 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 166.565) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 152.734) < 0.001 && fabs(p_oFakeTrees[i].fY - 98.5962) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 146.521) < 0.001 && fabs(p_oFakeTrees[i].fY - 53.0884) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 27.5635) < 0.001 && fabs(p_oFakeTrees[i].fY - 7.47681) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 192.706) < 0.001 && fabs(p_oFakeTrees[i].fY - 59.0942) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 152.82 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 70.8069) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 28.3142) < 0.001 && fabs(p_oFakeTrees[i].fY - 53.8513) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 21.4905) < 0.001 && fabs(p_oFakeTrees[i].fY - 195.148) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 138.66 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 49.8169) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 86.3342) < 0.001 && fabs(p_oFakeTrees[i].fY - 184.369) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 119.135) < 0.001 && fabs(p_oFakeTrees[i].fY - 65.9912) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 164.667) < 0.001 && fabs(p_oFakeTrees[i].fY - 195.239) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 111.023) < 0.001 && fabs(p_oFakeTrees[i].fY - 134.1) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 82.5439) < 0.001 && fabs(p_oFakeTrees[i].fY - 186.157) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 93.75) < 0.001 && fabs(p_oFakeTrees[i].fY - 156.512) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 113.257) < 0.001 && fabs(p_oFakeTrees[i].fY - 52.887) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 111.572) < 0.001 && fabs(p_oFakeTrees[i].fY - 118.756) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 86.9263) < 0.001 && fabs(p_oFakeTrees[i].fY - 149.762) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 108.398) < 0.001 && fabs(p_oFakeTrees[i].fY - 138.153) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 120.306) < 0.001 && fabs(p_oFakeTrees[i].fY - 67.0227) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 158.167) < 0.001 && fabs(p_oFakeTrees[i].fY - 76.5991) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 18.3655) < 0.001 && fabs(p_oFakeTrees[i].fY - 106.775) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 168.292) < 0.001 && fabs(p_oFakeTrees[i].fY - 118.292) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 69.574 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 151.202) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 181.494) < 0.001 && fabs(p_oFakeTrees[i].fY - 95.4712) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 192.81 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 173.029) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 175.818) < 0.001 && fabs(p_oFakeTrees[i].fY - 90.9851) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 65.3809) < 0.001 && fabs(p_oFakeTrees[i].fY - 110.986) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 49.5972) < 0.001 && fabs(p_oFakeTrees[i].fY - 123.993) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 98.4619) < 0.001 && fabs(p_oFakeTrees[i].fY - 67.1326) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 189.996) < 0.001 && fabs(p_oFakeTrees[i].fY - 126.154) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 53.3447) < 0.001 && fabs(p_oFakeTrees[i].fY - 129.956) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 103.998) < 0.001 && fabs(p_oFakeTrees[i].fY - 36.5784) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 104.248) < 0.001 && fabs(p_oFakeTrees[i].fY - 193.347) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 187) < 0.001 && fabs(p_oFakeTrees[i].fY - 155.127) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 168.207) < 0.001 && fabs(p_oFakeTrees[i].fY - 144.788) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 52.4353) < 0.001 && fabs(p_oFakeTrees[i].fY - 36.8652) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 66.4734) < 0.001 && fabs(p_oFakeTrees[i].fY - 177.948) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 80.426 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 130.377) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 47.1436) < 0.001 && fabs(p_oFakeTrees[i].fY - 183.905) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 180.914) < 0.001 && fabs(p_oFakeTrees[i].fY - 157.446) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 45.2087) < 0.001 && fabs(p_oFakeTrees[i].fY - 138.226) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 111.749) < 0.001 && fabs(p_oFakeTrees[i].fY - 160.437) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 180.072) < 0.001 && fabs(p_oFakeTrees[i].fY - 124.53) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 131.75 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 156.403) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 189.758) < 0.001 && fabs(p_oFakeTrees[i].fY - 123.718) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 199.5) < 0.001 && fabs(p_oFakeTrees[i].fY - 7.44629) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 26.0254) < 0.001 && fabs(p_oFakeTrees[i].fY - 196.973) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 169.58 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 59.4971) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 13.4766) < 0.001 && fabs(p_oFakeTrees[i].fY - 107.52) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 55.3345) < 0.001 && fabs(p_oFakeTrees[i].fY - 151.379) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 127.332) < 0.001 && fabs(p_oFakeTrees[i].fY - 33.3374) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 51.6235) < 0.001 && fabs(p_oFakeTrees[i].fY - 172.089) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 197.919) < 0.001 && fabs(p_oFakeTrees[i].fY - 47.9004) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 21.106 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 151.831) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 186.731) < 0.001 && fabs(p_oFakeTrees[i].fY - 26.825) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 66.0767) < 0.001 && fabs(p_oFakeTrees[i].fY - 57.2632) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 47.0215) < 0.001 && fabs(p_oFakeTrees[i].fY - 151.764) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 132.764) < 0.001 && fabs(p_oFakeTrees[i].fY - 44.5862) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 46.1121) < 0.001 && fabs(p_oFakeTrees[i].fY - 174.646) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 120.709) < 0.001 && fabs(p_oFakeTrees[i].fY - 69.2139) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 26.7334) < 0.001 && fabs(p_oFakeTrees[i].fY - 116.461) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 106.915) < 0.001 && fabs(p_oFakeTrees[i].fY - 10.26) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 168.121) < 0.001 && fabs(p_oFakeTrees[i].fY - 136.176) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 84.5459) < 0.001 && fabs(p_oFakeTrees[i].fY - 21.6858) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 5.07812) < 0.001 && fabs(p_oFakeTrees[i].fY - 35.9253) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 154.718) < 0.001 && fabs(p_oFakeTrees[i].fY - 161.206) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 99.115 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 25.6531) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 15.9302) < 0.001 && fabs(p_oFakeTrees[i].fY - 116.821) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 90.1855) < 0.001 && fabs(p_oFakeTrees[i].fY - 89.4592) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 15.3992) < 0.001 && fabs(p_oFakeTrees[i].fY - 184.686) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 28.5889) < 0.001 && fabs(p_oFakeTrees[i].fY - 119.635) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 140.363) < 0.001 && fabs(p_oFakeTrees[i].fY - 85.2173) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 82.2205) < 0.001 && fabs(p_oFakeTrees[i].fY - 159.558) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 156.238) < 0.001 && fabs(p_oFakeTrees[i].fY - 94.2017) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 115.497) < 0.001 && fabs(p_oFakeTrees[i].fY - 107.568) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 157.587) < 0.001 && fabs(p_oFakeTrees[i].fY - 163.226) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 137.091) < 0.001 && fabs(p_oFakeTrees[i].fY - 99.7742) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 121.1) < 0.001 && fabs(p_oFakeTrees[i].fY - 56.2927) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 173.56 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 24.4141) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 66.5344) < 0.001 && fabs(p_oFakeTrees[i].fY - 16.9006) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 106.824) < 0.001 && fabs(p_oFakeTrees[i].fY - 153.51) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 146.277) < 0.001 && fabs(p_oFakeTrees[i].fY - 30.3589) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 46.4966) < 0.001 && fabs(p_oFakeTrees[i].fY - 178.687) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 30.9509) < 0.001 && fabs(p_oFakeTrees[i].fY - 15.1672) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 127.551) < 0.001 && fabs(p_oFakeTrees[i].fY - 189.984) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 196.13 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 107.007) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 14.7034) < 0.001 && fabs(p_oFakeTrees[i].fY - 116.223) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 173.633) < 0.001 && fabs(p_oFakeTrees[i].fY - 23.4863) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 90.7227) < 0.001 && fabs(p_oFakeTrees[i].fY - 121.198) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 98.8098) < 0.001 && fabs(p_oFakeTrees[i].fY - 2.76489) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 153.906) < 0.001 && fabs(p_oFakeTrees[i].fY - 135.333) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 139.886) < 0.001 && fabs(p_oFakeTrees[i].fY - 110.84) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 2.44751) < 0.001 && fabs(p_oFakeTrees[i].fY - 74.7803) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 153.68 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 63.7573) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 19.7205) < 0.001 && fabs(p_oFakeTrees[i].fY - 37.6526) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 139.874) < 0.001 && fabs(p_oFakeTrees[i].fY - 83.4656) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 71.7957) < 0.001 && fabs(p_oFakeTrees[i].fY - 163.202) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 86.1755) < 0.001 && fabs(p_oFakeTrees[i].fY - 106.824) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 136.23) < 0.001 && fabs(p_oFakeTrees[i].fY - 47.229) < 0.001) p_oFakeTrees[i].bDead = true;


      //*********************************************
      // Trembling Aspen
      //*********************************************
      else if (fabs(p_oFakeTrees[i].fX - 115.051) < 0.001 && fabs(p_oFakeTrees[i].fY - 38.6902) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 92.688 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 182.611) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 94.9951) < 0.001 && fabs(p_oFakeTrees[i].fY - 79.1016) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 110.663) < 0.001 && fabs(p_oFakeTrees[i].fY - 104.822) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 111.42 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 152.234) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 111.823) < 0.001 && fabs(p_oFakeTrees[i].fY - 119.897) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 196.808) < 0.001 && fabs(p_oFakeTrees[i].fY - 11.8042) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 30.8594) < 0.001 && fabs(p_oFakeTrees[i].fY - 182.654) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 13.8733) < 0.001 && fabs(p_oFakeTrees[i].fY - 50.293) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 17.5354) < 0.001 && fabs(p_oFakeTrees[i].fY - 188.818) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 107.605) < 0.001 && fabs(p_oFakeTrees[i].fY - 138.708) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 3.48511) < 0.001 && fabs(p_oFakeTrees[i].fY - 188.428) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 115.765) < 0.001 && fabs(p_oFakeTrees[i].fY - 158.661) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 106.72 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 161.517) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 97.2717) < 0.001 && fabs(p_oFakeTrees[i].fY - 107.532) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 103.735) < 0.001 && fabs(p_oFakeTrees[i].fY - 49.6948) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 144.971) < 0.001 && fabs(p_oFakeTrees[i].fY - 132.629) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 187.305) < 0.001 && fabs(p_oFakeTrees[i].fY - 1.47095) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 24.9451) < 0.001 && fabs(p_oFakeTrees[i].fY - 121.228) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 172.223) < 0.001 && fabs(p_oFakeTrees[i].fY - 99.8901) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 114.99 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 25.5005) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 193.86 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 21.5759) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 2.83203) < 0.001 && fabs(p_oFakeTrees[i].fY - 138.33) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 95.0439) < 0.001 && fabs(p_oFakeTrees[i].fY - 90.0208) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 21.3257) < 0.001 && fabs(p_oFakeTrees[i].fY - 92.1265) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 24.1516) < 0.001 && fabs(p_oFakeTrees[i].fY - 85.7239) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 173.145) < 0.001 && fabs(p_oFakeTrees[i].fY - 197.058) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 95.4529) < 0.001 && fabs(p_oFakeTrees[i].fY - 34.8083) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 197.638) < 0.001 && fabs(p_oFakeTrees[i].fY - 82.7454) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 101.117) < 0.001 && fabs(p_oFakeTrees[i].fY - 12.6465) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 93.1641) < 0.001 && fabs(p_oFakeTrees[i].fY - 133.429) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 5.07812) < 0.001 && fabs(p_oFakeTrees[i].fY - 137.927) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 109.65 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 184.723) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 191.016) < 0.001 && fabs(p_oFakeTrees[i].fY - 152.826) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 187.891) < 0.001 && fabs(p_oFakeTrees[i].fY - 122.107) < 0.001) p_oFakeTrees[i].bDead = true;

      //*********************************************
      // Black Cottonwood
      //*********************************************
      else if (fabs(p_oFakeTrees[i].fX - 112.366) < 0.001 && fabs(p_oFakeTrees[i].fY - 47.6074) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 24.2249) < 0.001 && fabs(p_oFakeTrees[i].fY - 180.219) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 197.632) < 0.001 && fabs(p_oFakeTrees[i].fY - 157.861) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 111.249) < 0.001 && fabs(p_oFakeTrees[i].fY - 9.65576) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 101.013) < 0.001 && fabs(p_oFakeTrees[i].fY - 165.723) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 39.3066) < 0.001 && fabs(p_oFakeTrees[i].fY - 143.207) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 45.6909) < 0.001 && fabs(p_oFakeTrees[i].fY - 28.064) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 198.151) < 0.001 && fabs(p_oFakeTrees[i].fY - 157.324) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 185.217) < 0.001 && fabs(p_oFakeTrees[i].fY - 81.8359) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 1.37939) < 0.001 && fabs(p_oFakeTrees[i].fY - 39.3188) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 108.154) < 0.001 && fabs(p_oFakeTrees[i].fY - 129.559) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 101.019) < 0.001 && fabs(p_oFakeTrees[i].fY - 137.213) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 143.634) < 0.001 && fabs(p_oFakeTrees[i].fY - 182.379) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 96.2036) < 0.001 && fabs(p_oFakeTrees[i].fY - 1.5686) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 178.082) < 0.001 && fabs(p_oFakeTrees[i].fY - 38.6414) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 0.0244141) < 0.001 && fabs(p_oFakeTrees[i].fY - 18.6401) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 113.177) < 0.001 && fabs(p_oFakeTrees[i].fY - 102.356) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 179.376) < 0.001 && fabs(p_oFakeTrees[i].fY - 100.708) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 104.541) < 0.001 && fabs(p_oFakeTrees[i].fY - 128.662) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 123.816) < 0.001 && fabs(p_oFakeTrees[i].fY - 147.052) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 134.32 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 9.79614) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 26.8005) < 0.001 && fabs(p_oFakeTrees[i].fY - 78.6072) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 142.871) < 0.001 && fabs(p_oFakeTrees[i].fY - 31.7261) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 99.7314) < 0.001 && fabs(p_oFakeTrees[i].fY - 21.3623) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 93.3777) < 0.001 && fabs(p_oFakeTrees[i].fY - 34.7412) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 192.493) < 0.001 && fabs(p_oFakeTrees[i].fY - 177.795) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 138.806) < 0.001 && fabs(p_oFakeTrees[i].fY - 145.758) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 33.9539) < 0.001 && fabs(p_oFakeTrees[i].fY - 17.0532) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 177.277) < 0.001 && fabs(p_oFakeTrees[i].fY - 155.872) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 8.42285) < 0.001 && fabs(p_oFakeTrees[i].fY - 22.8088) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 111.066) < 0.001 && fabs(p_oFakeTrees[i].fY - 157.922) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 118.536) < 0.001 && fabs(p_oFakeTrees[i].fY - 175.97) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 8.69751) < 0.001 && fabs(p_oFakeTrees[i].fY - 61.4624) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 139.801) < 0.001 && fabs(p_oFakeTrees[i].fY - 37.793) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 196.094) < 0.001 && fabs(p_oFakeTrees[i].fY - 109.802) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 95.7336) < 0.001 && fabs(p_oFakeTrees[i].fY - 161.938) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 136.646) < 0.001 && fabs(p_oFakeTrees[i].fY - 125.232) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 3.4729 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 9.44214) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 143.28 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 176.154) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 180.469) < 0.001 && fabs(p_oFakeTrees[i].fY - 156.335) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 13.1836) < 0.001 && fabs(p_oFakeTrees[i].fY - 92.5842) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 121.851) < 0.001 && fabs(p_oFakeTrees[i].fY - 187.134) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 52.771 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 61.1816) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 10.5713) < 0.001 && fabs(p_oFakeTrees[i].fY - 79.6814) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 92.926 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 88.324) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 140.521) < 0.001 && fabs(p_oFakeTrees[i].fY - 43.5669) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 113.336) < 0.001 && fabs(p_oFakeTrees[i].fY - 77.9236) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 122.235) < 0.001 && fabs(p_oFakeTrees[i].fY - 113.013) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 194.592) < 0.001 && fabs(p_oFakeTrees[i].fY - 102.588) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 116.687) < 0.001 && fabs(p_oFakeTrees[i].fY - 132.648) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 132.05 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 58.5876) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 25.1648) < 0.001 && fabs(p_oFakeTrees[i].fY - 51.825) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 16.5222) < 0.001 && fabs(p_oFakeTrees[i].fY - 107.257) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 7.06177) < 0.001 && fabs(p_oFakeTrees[i].fY - 28.0029) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 141.107) < 0.001 && fabs(p_oFakeTrees[i].fY - 87.3779) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 129.7) < 0.001 && fabs(p_oFakeTrees[i].fY - 83.1299) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 66.8579) < 0.001 && fabs(p_oFakeTrees[i].fY - 165.387) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 182.733) < 0.001 && fabs(p_oFakeTrees[i].fY - 180.237) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 120.801) < 0.001 && fabs(p_oFakeTrees[i].fY - 169.794) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 189.771) < 0.001 && fabs(p_oFakeTrees[i].fY - 39.679) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 106.213) < 0.001 && fabs(p_oFakeTrees[i].fY - 31.1951) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 188.257) < 0.001 && fabs(p_oFakeTrees[i].fY - 195.312) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 118.268) < 0.001 && fabs(p_oFakeTrees[i].fY - 145.471) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 96.3684) < 0.001 && fabs(p_oFakeTrees[i].fY - 139.05) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 143.713) < 0.001 && fabs(p_oFakeTrees[i].fY - 127.374) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 31.9702) < 0.001 && fabs(p_oFakeTrees[i].fY - 174.127) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 100.366) < 0.001 && fabs(p_oFakeTrees[i].fY - 197.04) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 141.724) < 0.001 && fabs(p_oFakeTrees[i].fY - 10.6445) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 99.823 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 86.7126) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 134.979) < 0.001 && fabs(p_oFakeTrees[i].fY - 186.09) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 118.372) < 0.001 && fabs(p_oFakeTrees[i].fY - 140.179) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 25.6531) < 0.001 && fabs(p_oFakeTrees[i].fY - 98.3643) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 194.482) < 0.001 && fabs(p_oFakeTrees[i].fY - 28.7781) < 0.001) p_oFakeTrees[i].bDead = true;

      //*********************************************
      // Species 8
      //*********************************************
      else if (fabs(p_oFakeTrees[i].fX - 97.8333) < 0.001 && fabs(p_oFakeTrees[i].fY - 126.642) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 108.575) < 0.001 && fabs(p_oFakeTrees[i].fY - 172.308) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 101.007) < 0.001 && fabs(p_oFakeTrees[i].fY - 120.526) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 187.897) < 0.001 && fabs(p_oFakeTrees[i].fY - 129.346) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 0.396729 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 176.636) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 123.407) < 0.001 && fabs(p_oFakeTrees[i].fY - 152.02) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 8.77686) < 0.001 && fabs(p_oFakeTrees[i].fY - 3.38745) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 8.70972) < 0.001 && fabs(p_oFakeTrees[i].fY - 47.7356) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 186.31 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 157.55) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 195.477) < 0.001 && fabs(p_oFakeTrees[i].fY - 108.527) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 118.506) < 0.001 && fabs(p_oFakeTrees[i].fY - 150.482) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 100.006) < 0.001 && fabs(p_oFakeTrees[i].fY - 173.853) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 173.602) < 0.001 && fabs(p_oFakeTrees[i].fY - 50.946) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 141.351) < 0.001 && fabs(p_oFakeTrees[i].fY - 122.467) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 112.299) < 0.001 && fabs(p_oFakeTrees[i].fY - 46.7957) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 110.925) < 0.001 && fabs(p_oFakeTrees[i].fY - 172.809) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 14.8376) < 0.001 && fabs(p_oFakeTrees[i].fY - 51.593) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 18.4998) < 0.001 && fabs(p_oFakeTrees[i].fY - 23.1384) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 108.649) < 0.001 && fabs(p_oFakeTrees[i].fY - 2.20947) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 195.166) < 0.001 && fabs(p_oFakeTrees[i].fY - 109.32) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 175.061) < 0.001 && fabs(p_oFakeTrees[i].fY - 21.2585) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 25.1343) < 0.001 && fabs(p_oFakeTrees[i].fY - 62.7686) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 124.036) < 0.001 && fabs(p_oFakeTrees[i].fY - 17.4194) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 135.364) < 0.001 && fabs(p_oFakeTrees[i].fY - 119.525) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 175.073) < 0.001 && fabs(p_oFakeTrees[i].fY - 88.2996) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 33.9294) < 0.001 && fabs(p_oFakeTrees[i].fY - 151.782) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 34.3689) < 0.001 && fabs(p_oFakeTrees[i].fY - 56.2073) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 125.177) < 0.001 && fabs(p_oFakeTrees[i].fY - 127.399) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 101.447) < 0.001 && fabs(p_oFakeTrees[i].fY - 77.1729) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 101.831) < 0.001 && fabs(p_oFakeTrees[i].fY - 167.291) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 18.0481) < 0.001 && fabs(p_oFakeTrees[i].fY - 108.502) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 187.006) < 0.001 && fabs(p_oFakeTrees[i].fY - 173.682) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 181.885) < 0.001 && fabs(p_oFakeTrees[i].fY - 165.039) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 19.2322) < 0.001 && fabs(p_oFakeTrees[i].fY - 109.54) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 19.7205) < 0.001 && fabs(p_oFakeTrees[i].fY - 118.402) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 199.982) < 0.001 && fabs(p_oFakeTrees[i].fY - 155.444) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 107.495) < 0.001 && fabs(p_oFakeTrees[i].fY - 42.4377) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 174.298) < 0.001 && fabs(p_oFakeTrees[i].fY - 121.887) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 173.944) < 0.001 && fabs(p_oFakeTrees[i].fY - 4.42505) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 19.6045) < 0.001 && fabs(p_oFakeTrees[i].fY - 38.8428) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 122.247) < 0.001 && fabs(p_oFakeTrees[i].fY - 4.82178) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 140.668) < 0.001 && fabs(p_oFakeTrees[i].fY - 136.847) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 195.209) < 0.001 && fabs(p_oFakeTrees[i].fY - 70.3125) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 174.097) < 0.001 && fabs(p_oFakeTrees[i].fY - 111.536) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 126.721) < 0.001 && fabs(p_oFakeTrees[i].fY - 27.9663) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 16.4246) < 0.001 && fabs(p_oFakeTrees[i].fY - 177.063) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 13.9648) < 0.001 && fabs(p_oFakeTrees[i].fY - 90.4175) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 94.8364) < 0.001 && fabs(p_oFakeTrees[i].fY - 156.635) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 183.734) < 0.001 && fabs(p_oFakeTrees[i].fY - 86.7798) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 103.9) < 0.001 && fabs(p_oFakeTrees[i].fY - 132.855) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 81.4087) < 0.001 && fabs(p_oFakeTrees[i].fY - 135.193) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 31.0974) < 0.001 && fabs(p_oFakeTrees[i].fY - 74.9023) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 193.225) < 0.001 && fabs(p_oFakeTrees[i].fY - 162.28) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 175.385) < 0.001 && fabs(p_oFakeTrees[i].fY - 5.40161) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 56.4697) < 0.001 && fabs(p_oFakeTrees[i].fY - 167.139) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 182.782) < 0.001 && fabs(p_oFakeTrees[i].fY - 143.738) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 165.436) < 0.001 && fabs(p_oFakeTrees[i].fY - 150.183) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 168.384) < 0.001 && fabs(p_oFakeTrees[i].fY - 155.005) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 0.921631 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 188.062) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 83.6548) < 0.001 && fabs(p_oFakeTrees[i].fY - 104.919) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 142.322) < 0.001 && fabs(p_oFakeTrees[i].fY - 80.3406) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 77.7161) < 0.001 && fabs(p_oFakeTrees[i].fY - 66.2415) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 19.1711) < 0.001 && fabs(p_oFakeTrees[i].fY - 61.3708) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 159.357) < 0.001 && fabs(p_oFakeTrees[i].fY - 93.3228) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 120.453) < 0.001 && fabs(p_oFakeTrees[i].fY - 124.731) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 197.443) < 0.001 && fabs(p_oFakeTrees[i].fY - 120.703) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 136.334) < 0.001 && fabs(p_oFakeTrees[i].fY - 37.5732) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 32.2937) < 0.001 && fabs(p_oFakeTrees[i].fY - 65.5823) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 94.8486) < 0.001 && fabs(p_oFakeTrees[i].fY - 1.94092) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 159.076) < 0.001 && fabs(p_oFakeTrees[i].fY - 7.49512) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 137.891) < 0.001 && fabs(p_oFakeTrees[i].fY - 155.591) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 160.974) < 0.001 && fabs(p_oFakeTrees[i].fY - 186.908) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 157.281) < 0.001 && fabs(p_oFakeTrees[i].fY - 12.9456) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 14.4653) < 0.001 && fabs(p_oFakeTrees[i].fY - 47.7112) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 112.189) < 0.001 && fabs(p_oFakeTrees[i].fY - 20.3796) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 186.017) < 0.001 && fabs(p_oFakeTrees[i].fY - 69.22) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 57.7698) < 0.001 && fabs(p_oFakeTrees[i].fY - 193.115) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 87.9333) < 0.001 && fabs(p_oFakeTrees[i].fY - 72.1924) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 76.7944) < 0.001 && fabs(p_oFakeTrees[i].fY - 114.923) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 124.036) < 0.001 && fabs(p_oFakeTrees[i].fY - 145.728) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 136.09 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 125.092) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 46.2952) < 0.001 && fabs(p_oFakeTrees[i].fY - 44.9585) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 36.0291) < 0.001 && fabs(p_oFakeTrees[i].fY - 1.00708) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 111.89 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 25.5493) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 148.053) < 0.001 && fabs(p_oFakeTrees[i].fY - 133.557) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 165.729) < 0.001 && fabs(p_oFakeTrees[i].fY - 133.893) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 170.825) < 0.001 && fabs(p_oFakeTrees[i].fY - 20.7703) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 187.75 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 88.2446) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 91.6077) < 0.001 && fabs(p_oFakeTrees[i].fY - 164.447) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 38.1958) < 0.001 && fabs(p_oFakeTrees[i].fY - 199.561) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 194.415) < 0.001 && fabs(p_oFakeTrees[i].fY - 180.652) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 103.943) < 0.001 && fabs(p_oFakeTrees[i].fY - 93.4204) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 76.8799) < 0.001 && fabs(p_oFakeTrees[i].fY - 85.5164) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 55.0781) < 0.001 && fabs(p_oFakeTrees[i].fY - 127.094) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 98.5168) < 0.001 && fabs(p_oFakeTrees[i].fY - 43.5486) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 18.5852) < 0.001 && fabs(p_oFakeTrees[i].fY - 20.9045) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 113.947) < 0.001 && fabs(p_oFakeTrees[i].fY - 97.052) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 154.639) < 0.001 && fabs(p_oFakeTrees[i].fY - 82.428) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 8.47778) < 0.001 && fabs(p_oFakeTrees[i].fY - 67.9626) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 20.5688) < 0.001 && fabs(p_oFakeTrees[i].fY - 15.2893) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 27.3438) < 0.001 && fabs(p_oFakeTrees[i].fY - 54.4434) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 15.8386) < 0.001 && fabs(p_oFakeTrees[i].fY - 171.686) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 131.403) < 0.001 && fabs(p_oFakeTrees[i].fY - 184.003) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 116.18 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 177.57) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 141.443) < 0.001 && fabs(p_oFakeTrees[i].fY - 2.7771) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 26.2146) < 0.001 && fabs(p_oFakeTrees[i].fY - 187.976) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 82.428 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 74.7192) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 109.131) < 0.001 && fabs(p_oFakeTrees[i].fY - 136.359) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 36.3525) < 0.001 && fabs(p_oFakeTrees[i].fY - 48.4375) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 51.5808) < 0.001 && fabs(p_oFakeTrees[i].fY - 51.0254) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 94.635 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 61.8286) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 112.61 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 139.526) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 154.163) < 0.001 && fabs(p_oFakeTrees[i].fY - 144.855) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 52.6917) < 0.001 && fabs(p_oFakeTrees[i].fY - 36.6943) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 145.709) < 0.001 && fabs(p_oFakeTrees[i].fY - 113.123) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 172.986) < 0.001 && fabs(p_oFakeTrees[i].fY - 154.852) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 46.9604) < 0.001 && fabs(p_oFakeTrees[i].fY - 64.7156) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 49.7803) < 0.001 && fabs(p_oFakeTrees[i].fY - 2.96021) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 106.378) < 0.001 && fabs(p_oFakeTrees[i].fY - 90.6311) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 176.855) < 0.001 && fabs(p_oFakeTrees[i].fY - 47.522) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 32.8979) < 0.001 && fabs(p_oFakeTrees[i].fY - 186.365) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 116.486) < 0.001 && fabs(p_oFakeTrees[i].fY - 193.408) < 0.001) p_oFakeTrees[i].bDead = true;


      //*********************************************
      // Lodgepole Pine
      //*********************************************
      else if (fabs(p_oFakeTrees[i].fX - 16.2354) < 0.001 && fabs(p_oFakeTrees[i].fY - 85.6934) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 84.3872) < 0.001 && fabs(p_oFakeTrees[i].fY - 111.719) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 178.711) < 0.001 && fabs(p_oFakeTrees[i].fY - 82.0801) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 23.5413) < 0.001 && fabs(p_oFakeTrees[i].fY - 71.1609) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 63.0615) < 0.001 && fabs(p_oFakeTrees[i].fY - 5.57251) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 91.6382) < 0.001 && fabs(p_oFakeTrees[i].fY - 69.7205) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 128.455) < 0.001 && fabs(p_oFakeTrees[i].fY - 81.2683) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 53.9185) < 0.001 && fabs(p_oFakeTrees[i].fY - 142.413) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 49.6765) < 0.001 && fabs(p_oFakeTrees[i].fY - 185.339) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 151.013) < 0.001 && fabs(p_oFakeTrees[i].fY - 115.509) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 34.9731) < 0.001 && fabs(p_oFakeTrees[i].fY - 135.425) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 116.187) < 0.001 && fabs(p_oFakeTrees[i].fY - 45.4407) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 187.518) < 0.001 && fabs(p_oFakeTrees[i].fY - 38.5193) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 75.6226) < 0.001 && fabs(p_oFakeTrees[i].fY - 176.874) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 90.0757) < 0.001 && fabs(p_oFakeTrees[i].fY - 102.545) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 27.4841) < 0.001 && fabs(p_oFakeTrees[i].fY - 157.66) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 170.673) < 0.001 && fabs(p_oFakeTrees[i].fY - 140.796) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 183.929) < 0.001 && fabs(p_oFakeTrees[i].fY - 64.801) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 128.455) < 0.001 && fabs(p_oFakeTrees[i].fY - 168.915) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 116.29 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 108.911) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 65.5029) < 0.001 && fabs(p_oFakeTrees[i].fY - 78.3325) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 33.6365) < 0.001 && fabs(p_oFakeTrees[i].fY - 136.755) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 156.348) < 0.001 && fabs(p_oFakeTrees[i].fY - 80.0415) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 136.157) < 0.001 && fabs(p_oFakeTrees[i].fY - 189.856) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 63.9221) < 0.001 && fabs(p_oFakeTrees[i].fY - 156.024) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 61.7615) < 0.001 && fabs(p_oFakeTrees[i].fY - 186.346) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 61.3159) < 0.001 && fabs(p_oFakeTrees[i].fY - 79.4617) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 74.3042) < 0.001 && fabs(p_oFakeTrees[i].fY - 134.143) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 101.794) < 0.001 && fabs(p_oFakeTrees[i].fY - 89.1479) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 131.604) < 0.001 && fabs(p_oFakeTrees[i].fY - 131.256) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 181.238) < 0.001 && fabs(p_oFakeTrees[i].fY - 143.158) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 158.02 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 156.549) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 124.615) < 0.001 && fabs(p_oFakeTrees[i].fY - 22.2351) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 190.442) < 0.001 && fabs(p_oFakeTrees[i].fY - 10.1807) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 173.566) < 0.001 && fabs(p_oFakeTrees[i].fY - 38.9893) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 48.645 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 185.901) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 196.216) < 0.001 && fabs(p_oFakeTrees[i].fY - 170.532) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 123.56 ) < 0.001 && fabs(p_oFakeTrees[i].fY - 78.5156) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 162.903) < 0.001 && fabs(p_oFakeTrees[i].fY - 96.2952) < 0.001) p_oFakeTrees[i].bDead = true;
      else if (fabs(p_oFakeTrees[i].fX - 118.652) < 0.001 && fabs(p_oFakeTrees[i].fY - 119.257) < 0.001) p_oFakeTrees[i].bDead = true;


    }

    CheckHarvestResults(p_oPop, iNumTrees, p_oFakeTrees);



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
