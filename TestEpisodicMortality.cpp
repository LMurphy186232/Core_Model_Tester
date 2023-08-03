//---------------------------------------------------------------------------
// TestEpisodicMortality.cpp
//---------------------------------------------------------------------------
#include "TestEpisodicMortality.h"
#include <gtest/gtest.h>
#include "TreePopulation.h"
#include "SimManager.h"
#include "ModelMath.h"
#include "Grid.h"
#include <fstream>
#include <math.h>
#include <sstream>

/////////////////////////////////////////////////////////////////////////////
// DoMortEpisodeRun1()
// Performs the first run.  This run has the following characteristics:
//
// Mort ep # |TS  |Cut Ranges |Species |Cut Type |Cut Amt (abs) |Grids
//-----------|----|-----------|--------|---------|--------------|--------------
// 1         |1   |0 - 300    |2, 4    |% BA     |35            |Whole plot
// 2         |3   |0 - 30,    |5       |Abs BA   |0.2, 0.2      |Whole plot
//           |    |40 - 80    |        |         |              |
// 3         |3   |Min 0      |2, 8    |Clear    |100%          |Whole plot
//
// The mortality episode will be performed.  Then the remaining trees are
// checked to make sure the proper ones were left alone.
//
// This run includes snags, and the event is aware of them, but is told
// not to include them
/////////////////////////////////////////////////////////////////////////////
TEST(EpisodicMortality, DoMortEpisodeRun1) {
  clTreePopulation * p_oPop;
  clTreeSearch *p_oAllTrees;
  clTree *p_oTree;
  clGrid *p_oResults;
  std::stringstream sLabel;
  float fTemp, fSp2LiveBA, fSp4LiveBA, fSp2DeadBA, fSp4DeadBA;
  int *p_iC = new int[4];
  int i, iNumXCells, iNumYCells, iX, iY, iNumSpecies, j, k;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {

    p_oSimManager->ReadFile( WriteEpisodicMortalityXMLFile1() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
    p_oResults = p_oSimManager->GetGridObject("Mortality Episode Results");

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
    fSp2LiveBA = 0; fSp4LiveBA = 0;
    fSp2DeadBA = 0; fSp4DeadBA = 0;
    p_iC = new int[iNumSpecies];
    for (i = 0; i < iNumSpecies; i++) p_iC[i] = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (p_oTree->GetType() == clTreePopulation::sapling ||
          p_oTree->GetType() == clTreePopulation::adult) {

        if (p_oTree->GetSpecies() == 2) {
          p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
          fSp2LiveBA += clModelMath::CalculateBasalArea(fTemp);

        } else if (p_oTree->GetSpecies() == 4) {
          p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
          fSp4LiveBA += clModelMath::CalculateBasalArea(fTemp);

        }
      } else if (p_oTree->GetType() == clTreePopulation::snag) {

        if (p_oTree->GetSpecies() == 2) {
          p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
          fSp2DeadBA += clModelMath::CalculateBasalArea(fTemp);

        } else if (p_oTree->GetSpecies() == 4) {
          p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
          fSp4DeadBA += clModelMath::CalculateBasalArea(fTemp);

        }
      } else if (p_oTree->GetType() == clTreePopulation::seedling) {
        p_iC[p_oTree->GetSpecies()]++;
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    EXPECT_LT(fabs(fSp2LiveBA - 34.3837)/34.3837, 0.01);
    EXPECT_LT(fabs(fSp4LiveBA - 33.61)/33.61, 0.01);
    // EXPECT_LT(fabs(fSp2DeadBA - 18.5143)/18.5143, 0.01);
    // EXPECT_LT(fabs(fSp4DeadBA - 18.102)/18.102, 0.01);
    EXPECT_LT(fabs(fSp2DeadBA - 38.1493)/38.1493, 0.01);
    EXPECT_LT(fabs(fSp4DeadBA - 37.7370)/37.7370, 0.01);
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
    float fSp5LiveRange0_30 = 0, fSp5LiveRange40_80 = 0, fSp5DeadRange0_30 = 0, fSp5DeadRange40_80 = 0;
    for (i = 0; i < iNumSpecies; i++) p_iC[i] = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      //Make sure there are no trees of species 2 or 8
      if (p_oTree->GetSpecies() == 2 || p_oTree->GetSpecies() == 8) {
        ASSERT_TRUE(p_oTree->GetType() == clTreePopulation::snag ||
            p_oTree->GetType() == clTreePopulation::seedling);
      }

      //Total up the basal area for species five between DBH of 0-30 and 40-80
      if (p_oTree->GetType() == clTreePopulation::sapling ||
          p_oTree->GetType() == clTreePopulation::adult) {
        if (p_oTree->GetSpecies() == 5) {

          p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);

          if (fTemp <= 30)
            fSp5LiveRange0_30 += clModelMath::CalculateBasalArea(fTemp);
          else if (fTemp >= 40 && fTemp <= 80)
            fSp5LiveRange40_80 += clModelMath::CalculateBasalArea(fTemp);

        }
      } else if (p_oTree->GetType() == clTreePopulation::snag) {

        if (p_oTree->GetSpecies() == 5) {

          p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);

          if (fTemp <= 30)
            fSp5DeadRange0_30 += clModelMath::CalculateBasalArea(fTemp);
          else if (fTemp >= 40 && fTemp <= 80)
            fSp5DeadRange40_80 += clModelMath::CalculateBasalArea(fTemp);

        }
      } else if (p_oTree->GetType() == clTreePopulation::seedling) {
        p_iC[p_oTree->GetSpecies()]++;
      }

      p_oTree = p_oAllTrees->NextTree();
    }

    //Make sure the leftover basal area for species 5 is OK
    EXPECT_LT(fabs(fSp5LiveRange0_30 - 0.64226)/0.64226, 0.01);
    EXPECT_LT(fabs(fSp5LiveRange40_80 - 23.055)/23.055, 0.01);
    EXPECT_LT(fabs(fSp5DeadRange0_30 - 0.8)/0.8, 0.01);
    // EXPECT_LT(fabs(fSp5DeadRange40_80 - 0.8)/0.8, 0.01);
    EXPECT_LT(fabs(fSp5DeadRange40_80 - 20.435)/20.435, 0.01);
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
// DoMortEpisodeRun2()
// Performs the second mortality episode run. This run has the following
// characteristics:
// Mort ep # |TS  |Cut Ranges |Species |Cut Type |Cut Amt (abs) |Grids
//-----------|----|-----------|--------|---------|--------------|--------------
// 1         |1   |15-45,     |0, 1    |%Dens    |50, 40, 30, 20|Whole plot
//           |    |50-80,     |        |         |              |
//           |    |80 - 85,   |        |         |              |
//           |    |90 - 99    |        |         |              |
//
// The mortality episode will be performed.  Then the remaining trees are
// checked to make sure the proper ones were left alone.
/////////////////////////////////////////////////////////////////////////////
TEST(EpisodicMortality, DoMortEpisodeRun2) {

  clTreePopulation * p_oPop;
  clTreeSearch *p_oAllTrees;
  clTree *p_oTree;
  clGrid *p_oResults;
  int *p_iC = new int[4];
  std::stringstream sLabel;
  float fTemp;
  int iNumXCells, iNumYCells, iNumSpecies, iX, iY, i, j, k,
  iSp0Live_90_99 = 0, iSp0Live_80_85 = 0, iSp0Live_50_80 = 0, iSp0Live_15_45 = 0,
  iSp1Live_90_99 = 0, iSp1Live_80_85 = 0, iSp1Live_50_80 = 0, iSp1Live_15_45 = 0,
  iSp0Dead_90_99 = 0, iSp0Dead_80_85 = 0, iSp0Dead_50_80 = 0, iSp0Dead_15_45 = 0,
  iSp1Dead_90_99 = 0, iSp1Dead_80_85 = 0, iSp1Dead_50_80 = 0, iSp1Dead_15_45 = 0;


  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    p_oSimManager->ReadFile( WriteEpisodicMortalityXMLFile2() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
    p_oResults = p_oSimManager->GetGridObject("Mortality Episode Results");

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
            iSp1Live_90_99++;
          else if (fTemp >= 80 && fTemp <= 85)
            iSp1Live_80_85++;
          else if (fTemp >= 50 && fTemp <= 80)
            iSp1Live_50_80++;
          else if (fTemp >= 15 && fTemp <= 45)
            iSp1Live_15_45++;

        } else if (p_oTree->GetSpecies() == 0) {

          p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);

          if (fTemp >= 90 && fTemp <= 99)
            iSp0Live_90_99++;
          else if (fTemp >= 80 && fTemp <= 85)
            iSp0Live_80_85++;
          else if (fTemp >= 50 && fTemp <= 80)
            iSp0Live_50_80++;
          else if (fTemp >= 15 && fTemp <= 45)
            iSp0Live_15_45++;
        }
      } else if (p_oTree->GetType() == clTreePopulation::snag) {

        if (p_oTree->GetSpecies() == 1) {

          p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);

          if (fTemp >= 90 && fTemp <= 99)
            iSp1Dead_90_99++;
          else if (fTemp >= 80 && fTemp <= 85)
            iSp1Dead_80_85++;
          else if (fTemp >= 50 && fTemp <= 80)
            iSp1Dead_50_80++;
          else if (fTemp >= 15 && fTemp <= 45)
            iSp1Dead_15_45++;

        } else if (p_oTree->GetSpecies() == 0) {

          p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);

          if (fTemp >= 90 && fTemp <= 99)
            iSp0Dead_90_99++;
          else if (fTemp >= 80 && fTemp <= 85)
            iSp0Dead_80_85++;
          else if (fTemp >= 50 && fTemp <= 80)
            iSp0Dead_50_80++;
          else if (fTemp >= 15 && fTemp <= 45)
            iSp0Dead_15_45++;
        }
      } else if (p_oTree->GetType() == clTreePopulation::seedling) {
        p_iC[p_oTree->GetSpecies()]++;
      }

      p_oTree = p_oAllTrees->NextTree();
    }

    ASSERT_TRUE(iSp1Live_90_99 >= 9 && iSp1Live_90_99 <= 14);
    ASSERT_TRUE(iSp1Live_80_85 >= 6 && iSp1Live_80_85 <= 12);
    ASSERT_TRUE(iSp1Live_50_80 >= 34 && iSp1Live_50_80 <= 46);
    ASSERT_TRUE(iSp1Live_15_45 >= 25 && iSp1Live_15_45 <= 35);
    ASSERT_TRUE(iSp0Live_90_99 >= 8 && iSp0Live_90_99 <= 14);
    ASSERT_TRUE(iSp0Live_80_85 >= 5 && iSp0Live_80_85 <= 10);
    ASSERT_TRUE(iSp0Live_50_80 >= 31 && iSp0Live_50_80 <= 41);
    ASSERT_TRUE(iSp0Live_15_45 >= 23 && iSp0Live_50_80 <= 40);

    ASSERT_TRUE(iSp1Dead_90_99 >= 1 && iSp1Dead_90_99 <= 8);
    ASSERT_TRUE(iSp1Dead_80_85 >= 1 && iSp1Dead_80_85 <= 7);
    ASSERT_TRUE(iSp1Dead_50_80 >= 115 && iSp0Dead_50_80 <= 128);
    ASSERT_TRUE(iSp1Dead_15_45 >= 25 && iSp1Dead_15_45 <= 37);
    ASSERT_TRUE(iSp0Dead_90_99 >= 1 && iSp0Dead_90_99 <= 8);
    ASSERT_TRUE(iSp0Dead_80_85 >= 1 && iSp0Dead_80_85 <= 7);
    ASSERT_TRUE(iSp0Dead_50_80 >= 120 && iSp0Dead_50_80 <= 128);
    ASSERT_TRUE(iSp0Dead_15_45 >= 25 && iSp0Dead_15_45 <= 37);

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
// DoMortEpisodeRun3()
// Performs the first mortality episode run. This run has the following
// characteristics:
// Mort ep # |TS  |Cut Ranges |Species |Cut Type |Cut Amt (abs) |Grids
//-----------|----|-----------|--------|---------|--------------|--------------
// 1         |1   |15-45,     |6, 7    |Abs Den  |1             |Whole plot
//           |    |50-80,     |        |         |              |
//           |    |80 - 85,   |        |         |              |
//           |    |90 - 100   |        |         |              |
//
// The mortality episode will be performed.  Then the remaining trees are
// checked to make sure the proper ones were left alone.
/////////////////////////////////////////////////////////////////////////////
TEST(EpisodicMortality, DoMortEpisodeRun3) {

  clTreePopulation * p_oPop;
  clTreeSearch *p_oAllTrees;
  clTree *p_oTree;
  clGrid *p_oResults;
  std::stringstream sLabel;
  int *p_iC = new int[4];
  float fTemp;
  int iNumXCells, iNumYCells, iNumSpecies, iX, iY, i, j, k,
  iSp6Live_90_99 = 0, iSp6Live_80_85 = 0, iSp6Live_50_80 = 0, iSp6Live_15_45 = 0,
  iSp7Live_90_99 = 0, iSp7Live_80_85 = 0, iSp7Live_50_80 = 0, iSp7Live_15_45 = 0,
  iSp6Dead_90_99 = 0, iSp6Dead_80_85 = 0, iSp6Dead_50_80 = 0, iSp6Dead_15_45 = 0,
  iSp7Dead_90_99 = 0, iSp7Dead_80_85 = 0, iSp7Dead_50_80 = 0, iSp7Dead_15_45 = 0;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {

    p_oSimManager->ReadFile( WriteEpisodicMortalityXMLFile3() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
    p_oResults = p_oSimManager->GetGridObject("Mortality Episode Results");

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
            iSp7Live_90_99++;
          else if (fTemp >= 80 && fTemp <= 85)
            iSp7Live_80_85++;
          else if (fTemp >= 50 && fTemp <= 80)
            iSp7Live_50_80++;
          else if (fTemp >= 15 && fTemp <= 45)
            iSp7Live_15_45++;

        } else if (p_oTree->GetSpecies() == 6) {

          p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);

          if (fTemp >= 90 && fTemp <= 100)
            iSp6Live_90_99++;
          else if (fTemp >= 80 && fTemp <= 85)
            iSp6Live_80_85++;
          else if (fTemp >= 50 && fTemp <= 80)
            iSp6Live_50_80++;
          else if (fTemp >= 15 && fTemp <= 45)
            iSp6Live_15_45++;
        }
      } else if (p_oTree->GetType() == clTreePopulation::snag) {
        if (p_oTree->GetSpecies() == 7) {

          p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);

          if (fTemp >= 90 && fTemp <= 100)
            iSp7Dead_90_99++;
          else if (fTemp >= 80 && fTemp <= 85)
            iSp7Dead_80_85++;
          else if (fTemp >= 50 && fTemp <= 80)
            iSp7Dead_50_80++;
          else if (fTemp >= 15 && fTemp <= 45)
            iSp7Dead_15_45++;

        } else if (p_oTree->GetSpecies() == 6) {

          p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);

          if (fTemp >= 90 && fTemp <= 100)
            iSp6Dead_90_99++;
          else if (fTemp >= 80 && fTemp <= 85)
            iSp6Dead_80_85++;
          else if (fTemp >= 50 && fTemp <= 80)
            iSp6Dead_50_80++;
          else if (fTemp >= 15 && fTemp <= 45)
            iSp6Dead_15_45++;
        }
      } else if (p_oTree->GetType() == clTreePopulation::seedling) {
        p_iC[p_oTree->GetSpecies()]++;
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    EXPECT_EQ(iSp7Live_90_99, 16);
    EXPECT_EQ(iSp7Live_80_85, 3);
    EXPECT_EQ(iSp7Live_50_80, 56);
    EXPECT_EQ(iSp7Live_15_45, 55);
    EXPECT_EQ(iSp6Live_90_99, 16);
    EXPECT_EQ(iSp6Live_80_85, 8);
    EXPECT_EQ(iSp6Live_50_80, 56);
    EXPECT_EQ(iSp6Live_15_45, 56);

    EXPECT_EQ(iSp7Dead_90_99, 4);
    EXPECT_EQ(iSp7Dead_80_85, 4);
    EXPECT_EQ(iSp7Dead_50_80, 4);
    EXPECT_EQ(iSp7Dead_15_45, 4);
    EXPECT_EQ(iSp6Dead_90_99, 4);
    EXPECT_EQ(iSp6Dead_80_85, 4);
    EXPECT_EQ(iSp6Dead_50_80, 4);
    EXPECT_EQ(iSp6Dead_15_45, 4);

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
// DoMortEpisodeRun4()
// Performs the fourth mortality episode run. This run has the following
// characteristics:
// Mort ep # |TS |Cut Ranges  |Species |Cut Type |Cut Amt (abs) |Grids
//-----------|---|------------|--------|---------|--------------|--------------
// 1         |2  |Min 0       |0, 1, 2 |Gap      |100%          |Whole plot
// 2         |2  |15-45,      |4, 5    |% BA     |50, 100, 30, 0|(0,0) - (5,9)
//           |   |50-80,      |        |         |              |
//           |   |80-85,      |        |         |              |
//           |   |90-100      |        |         |              |
// 3         |3  |200-300,    |4       |Abs BA   |50, 100, 30, 0|(6,6) - (6-24),
//           |   |50-80,      |        |         |              |(8,6) - (8-24)
//           |   |80-85,      |        |         |              |
//           |   |90-100      |        |         |              |
// 4         |3  |0-10, 10-20,|7       |% Dens   |50, 100, 30, 0|(0,0) - (5,9)
//           |   |20-30, 30-40|        |         |              |
// The mortality episode will be performed. Then the remaining trees are
// checked to make sure the proper ones were left alone.
/////////////////////////////////////////////////////////////////////////////
TEST(EpisodicMortality, DoMortEpisodeRun4) {

  clTreePopulation * p_oPop;
  clTreeSearch *p_oAllTrees;
  clTree *p_oTree;
  clGrid *p_oResults;
  std::stringstream sLabel;
  float fTemp;
  int iNumXCells, iNumYCells, iNumSpecies, iX, iY, j, k,
  iNumTrees = 1980, iCounter = 0, i;
  //Fake tree structure
  treestruct *p_oFakeTrees = new treestruct[iNumTrees];
  int *p_iC = new int[4];
  int *p_iSeedlsOutside = NULL;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    p_oSimManager->ReadFile( WriteEpisodicMortalityXMLFile4() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
    p_oResults = p_oSimManager->GetGridObject("Mortality Episode Results");

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

    //Verify that there was no disturbance
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

      ASSERT_TRUE(p_oTree->GetType() != clTreePopulation::snag);
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
      if (0 == p_oFakeTrees[i].iSpecies ||
          1 == p_oFakeTrees[i].iSpecies ||
          2 == p_oFakeTrees[i].iSpecies) {
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
    CheckEpisodicMortalityResults(p_oPop, iNumTrees, p_oFakeTrees);
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
    int iSp7LiveOutsideCut = 0, iSp7Live_0_10 = 0, iSp7Live_10_20 = 0, iSp7Live_20_30 = 0, iSp7Live_30_40 = 0;

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
      if (p_oTree->GetType() > clTreePopulation::seedling) {

        //Make sure the correct species 4 trees have been cut - they shouldn't show up
        if ((fabs(fX - 67.5964) < 0.001 && fabs(fY - 94.4275) < 0.001) ||
            (fabs(fX - 67.5964) < 0.001 && fabs(fY - 94.4275) < 0.001) ||
            (fabs(fX - 51.9287) < 0.001 && fabs(fY - 131.873) < 0.001) ||
            (fabs(fX - 54.5044) < 0.001 && fabs(fY - 85.0464) < 0.001)) {
          EXPECT_EQ(p_oTree->GetType(), clTreePopulation::snag);
        }

        //Count the species 7 trees both within the cut area and outside it
        if (p_oTree->GetType() != clTreePopulation::snag) {
          if (7 == p_oTree->GetSpecies()) {
            if (fX >= 48 || fY >= 80) {
              //This tree is outside the cut area
              ASSERT_TRUE(p_oTree->GetType() != clTreePopulation::snag);
              iSp7LiveOutsideCut++;
            } else {

              //Get the DBH
              p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);

              if (fTemp >= 0 && fTemp <= 10)
                iSp7Live_0_10++;
              else if (fTemp >= 10 && fTemp <= 20)
                iSp7Live_10_20++;
              else if (fTemp >= 20 && fTemp <= 30)
                iSp7Live_20_30++;
              else if (fTemp >= 30 && fTemp <= 40)
                iSp7Live_30_40++;
            }
          }
        }
      } else {
        if (fX >= 48 || fY >= 80) {
          p_iSeedlsOutside[p_oTree->GetSpecies()]++;
        } else {
          p_iC[p_oTree->GetSpecies()]++;
        }
      }

      p_oTree = p_oAllTrees->NextTree();
    }

    //Make sure there were no trees cut outside the cut area
    EXPECT_EQ(197, iSp7LiveOutsideCut);
    for (i = 6; i < iNumSpecies; i++) {
      EXPECT_EQ(p_iSeedlsOutside[i], 9040);
    }

    //Make sure the right number of trees within the cut were cut
    ASSERT_TRUE(1 <= iSp7Live_0_10 || 4 >= iSp7Live_0_10);
    EXPECT_EQ(0, iSp7Live_10_20);
    EXPECT_EQ(0, iSp7Live_20_30);
    EXPECT_EQ(4, iSp7Live_30_40);
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
// DoMortEpisodeRun5()
// Performs the fifth mortality episode run. This run has the following
// characteristics:
// Mort ep # |TS |Cut Ranges  |Species |Cut Type |Cut Amt (abs) |Grids
//-----------|---|------------|--------|---------|--------------|--------------
// 1         |1  |0-10, 10-20,|0-8     |Abs Den  |5, 100, 3, 0  |(6,6) - (6-24);
//           |   |20-30, 30-40|        |         |              |(8,0) - (24-12)
//
// The mortality episode will be performed. Then the remaining trees are
// checked to make sure the proper ones were left alone.
/////////////////////////////////////////////////////////////////////////////
TEST(EpisodicMortality, DoMortEpisodeRun5) {
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

    p_oSimManager->ReadFile( WriteEpisodicMortalityXMLFile5() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
    p_oResults = p_oSimManager->GetGridObject("Mortality Episode Results");

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
    CheckEpisodicMortalityResults(p_oPop, iNumTrees, p_oFakeTrees);
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
// DoMortEpisodeRun6()
// Performs the sixth mortality episode run. This run has the following
// characteristics:
//
// Mort ep # |TS |Cut Ranges  |Species |Cut Type |Cut Amt (abs) |Grids
//-----------|---|------------|--------|---------|--------------|--------------
// 1         |1  |Min 0       |3       |Clear    |100%          |(6,6) - (6-24),
//           |   |            |        |         |              |(8,6) - (8-24)
// 2         |2  |Min 0       |0       |Gap      |100%          |(0,0) - (5,9)
// 3         |3  |0 - 300     |1       |% BA     |50            |(0,10)
// 4         |3  |0 - 300     |2       |Abs BA   |4.5           |(5,5)
// 5         |3  |0 - 300     |4       |% Dens   |50            |(10,23)
// 6         |3  |0 - 300     |5       |Abs Den  |2             |(1,1)
// 7         |3  |Min 0       |6       |Clear    |100%          |(20,0)
// 8         |3  |Min 0       |7       |Gap      |100%          |(1,7)
//
// The mortality episode will be performed.  Then the remaining trees are
// checked to make sure the proper ones were left alone.
/////////////////////////////////////////////////////////////////////////////
TEST(EpisodicMortality, DoMortEpisodeRun6) {
  clTreePopulation * p_oPop;
  clTreeSearch *p_oAllTrees;
  clTree *p_oTree;
  float fTemp;
  int iNumTrees = 1980, iCounter = 0, i;
  //Fake tree structure
  treestruct *p_oFakeTrees = new treestruct[iNumTrees];

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    p_oSimManager->ReadFile( WriteEpisodicMortalityXMLFile6() );
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
    CheckEpisodicMortalityResults(p_oPop, iNumTrees, p_oFakeTrees);

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
    CheckEpisodicMortalityResults(p_oPop, iNumTrees, p_oFakeTrees);

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
    CheckEpisodicMortalityResults(p_oPop, iNumTrees, p_oFakeTrees);


    delete[] p_oFakeTrees;
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete[] p_oFakeTrees;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

//Run seven skipped...

/////////////////////////////////////////////////////////////////////////////
// DoMortEpisodeRun8()
// Performs the eighth mortality episode run. This run has the following
// characteristics:
//
// Mort ep # |TS |Cut Ranges  |Species |Cut Type |Cut Amt (abs) |Grids
//-----------|---|------------|--------|---------|--------------|--------------
// 1         |1  |Min 0       |All     |Clear    |100%          |(0,0) - (23,39)
//
// The mortality episode will be performed.  Then the remaining trees are
// checked to make sure the proper ones were left alone.
/////////////////////////////////////////////////////////////////////////////
TEST(EpisodicMortality, DoMortEpisodeRun8) {
  clTreePopulation * p_oPop;
  clTreeSearch *p_oAllTrees;
  clTree *p_oTree;
  clGrid *p_oResults;
  int *p_iC = new int[4];
  std::stringstream sLabel;
  float fTemp, fX, fY, fDbh;
  int iNumXCells, iNumYCells, iNumSpecies, iX, iY, j, k,
  iNumTrees = 1980, iCounter = 0, i, iTemp;
  //Fake tree structure
  treestruct *p_oFakeTrees = new treestruct[iNumTrees];

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {

    p_oSimManager->ReadFile( WriteEpisodicMortalityXMLFile8() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
    p_oResults = p_oSimManager->GetGridObject("Mortality Episode Results");

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

    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (p_oTree->GetType() > clTreePopulation::seedling) {

        p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
        p_oFakeTrees[iCounter].fX = fTemp;
        p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
        p_oFakeTrees[iCounter].fY = fTemp;
        p_oFakeTrees[iCounter].iSpecies = p_oTree->GetSpecies();

        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDbh);

        //Expected results; make black cottonwoods not die if they're big
        // because they'll be avoided snags
        p_oFakeTrees[iCounter].bFound = false;
        if (p_oFakeTrees[iCounter].fX < 44 && p_oFakeTrees[iCounter].fY < 74) {
          if (fDbh > 20) {
            if (p_oFakeTrees[iCounter].iSpecies != 8) {
              p_oFakeTrees[iCounter].bDead = true;
            } else {
              p_oFakeTrees[iCounter].bDead = false;
            }
          } else {
            p_oFakeTrees[iCounter].bDead = true;
          }
        } else {
          p_oFakeTrees[iCounter].bDead = false;
        }

        iCounter++;
        if (iCounter == iNumTrees) break;
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    // Turn some trees to cut into snags
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (p_oTree->GetType() != clTreePopulation::seedling) {
        p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
        p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDbh);
        if (fX <= 44 && fY <= 74 && fDbh > 20) {
          //p_oPop->KillTree(p_oTree, natural);
          fX = fY;
        }
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    // Assign some decay classes - all black cottonwoods get a high decay class
    iTemp = 2;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (p_oTree->GetType() == clTreePopulation::snag) {
        if (p_oTree->GetSpecies() == 8) {
          p_oTree->SetValue(p_oPop->GetIntDataCode("SnagDecayClass",
              p_oTree->GetSpecies(), p_oTree->GetType()), iTemp);
        }
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    //Run the sim and check the results
    p_oSimManager->RunSim(1);
    CheckEpisodicMortalityResults(p_oPop, iNumTrees, p_oFakeTrees);

    p_iC = new int[iNumSpecies];
    for (i = 0; i < iNumSpecies; i++) p_iC[i] = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
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
// CheckEpisodicMortalityResults
/////////////////////////////////////////////////////////////////////////////
void CheckEpisodicMortalityResults(clTreePopulation *p_oPop, int iNumTrees, treestruct *p_FakeTrees) {
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
        if (p_FakeTrees[i].bDead && p_oTree->GetType() != clTreePopulation::snag) {
          //We found this tree, but it was supposed to be dead
          FAIL() << "Disturbance run failed - tree was supposed to be killed and wasn't.";
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
// WriteEpisodicMortalityXMLFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteEpisodicMortalityXMLFile1()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">" << "<plot>"
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

  oOut.close();

  WriteEpisodicMortalityTreeMap(cFileString);

  oOut.open(cFileString, ios::out | ios::app);
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
      << "<tr_stdMaxCrownRad>"
      << "<tr_smcrVal species=\"Western_Hemlock\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Western_Redcedar\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Amabilis_Fir\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Subalpine_Fir\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Hybrid_Spruce\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Lodgepole_Pine\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Trembling_Aspen\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Black_Cottonwood\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Paper_Birch\">10</tr_smcrVal>"
      << "</tr_stdMaxCrownRad>"
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
      << "</allometry>"
      << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>EpisodicMortality</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>ConstantGLI</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Western_Hemlock\" type=\"Snag\" />"
      << "<applyTo species=\"Western_Redcedar\" type=\"Snag\" />"
      << "<applyTo species=\"Amabilis_Fir\" type=\"Snag\" />"
      << "<applyTo species=\"Subalpine_Fir\" type=\"Snag\" />"
      << "<applyTo species=\"Hybrid_Spruce\" type=\"Snag\" />"
      << "<applyTo species=\"Lodgepole_Pine\" type=\"Snag\" />"
      << "<applyTo species=\"Trembling_Aspen\" type=\"Snag\" />"
      << "<applyTo species=\"Black_Cottonwood\" type=\"Snag\" />"
      << "<applyTo species=\"Paper_Birch\" type=\"Snag\" />"
      << "</behavior>"
      << "</behaviorList>"
      << "<ConstantGLI2>"
      << "<li_constGLI>100</li_constGLI>"
      << "</ConstantGLI2>"
      << "<EpisodicMortality1>"
      << "<ds_deathEvent>"
      << "<ds_applyToSpecies species=\"Amabilis_Fir\" />"
      << "<ds_applyToSpecies species=\"Paper_Birch\" />"
      << "<ds_timestep>3</ds_timestep>"
      << "<ds_cutAmountType>percent of density</ds_cutAmountType>"
      << "<ds_dbhRange>"
      << "<ds_low>0.0</ds_low>"
      << "<ds_high>3000.0</ds_high>"
      << "<ds_amountToCut>100.0</ds_amountToCut>"
      << "</ds_dbhRange>";
  for (int i = 0; i < 25; i++) {
    for (int j = 0; j < 25; j++) {
      oOut << "<ds_applyToCell x=\"" << i << "\" y=\"" << j << "\" /> ";
    }
  }
  oOut << "</ds_deathEvent>"
      << "<ds_deathEvent>"
      << "<ds_applyToSpecies species=\"Lodgepole_Pine\" />"
      << "<ds_maxSnagDecayClass>-1</ds_maxSnagDecayClass>"
      << "<ds_timestep>3</ds_timestep>"
      << "<ds_cutAmountType>absolute basal area</ds_cutAmountType>"
      << "<ds_maxSnagDecayClass>-1</ds_maxSnagDecayClass>"
      << "<ds_dbhRange>"
      << "<ds_low>0.0</ds_low>"
      << "<ds_high>30.0</ds_high>"
      << "<ds_amountToCut>0.2</ds_amountToCut>"
      << "</ds_dbhRange>"
      << "<ds_dbhRange>"
      << "<ds_low>40.0</ds_low>"
      << "<ds_high>80.0</ds_high>"
      << "<ds_amountToCut>0.2</ds_amountToCut>"
      << "</ds_dbhRange>";
  for (int i = 0; i < 25; i++) {
    for (int j = 0; j < 25; j++) {
      oOut << "<ds_applyToCell x=\"" << i << "\" y=\"" << j << "\" /> ";
    }
  }
  oOut << "</ds_deathEvent>"
      << "<ds_deathEvent>"
      << "<ds_applyToSpecies species=\"Amabilis_Fir\" />"
      << "<ds_applyToSpecies species=\"Hybrid_Spruce\" />"
      << "<ds_maxSnagDecayClass>-1</ds_maxSnagDecayClass>"
      << "<ds_timestep>1</ds_timestep>"
      << "<ds_cutAmountType>percent of basal area</ds_cutAmountType>"
      << "<ds_dbhRange>"
      << "<ds_low>0.0</ds_low>"
      << "<ds_high>300.0</ds_high>"
      << "<ds_amountToCut>35</ds_amountToCut>"
      << "</ds_dbhRange>"
      << "<ds_percentSeedlingsDie>"
      << "<ds_psdVal species=\"Amabilis_Fir\">100</ds_psdVal>"
      << "<ds_psdVal species=\"Hybrid_Spruce\">100</ds_psdVal>"
      << "<ds_psdVal species=\"Western_Hemlock\">0</ds_psdVal>"
      << "<ds_psdVal species=\"Western_Redcedar\">0</ds_psdVal>"
      << "<ds_psdVal species=\"Subalpine_Fir\">0</ds_psdVal>"
      << "<ds_psdVal species=\"Lodgepole_Pine\">0</ds_psdVal>"
      << "<ds_psdVal species=\"Trembling_Aspen\">0</ds_psdVal>"
      << "<ds_psdVal species=\"Black_Cottonwood\">0</ds_psdVal>"
      << "<ds_psdVal species=\"Paper_Birch\">0</ds_psdVal>"
      << "</ds_percentSeedlingsDie>";
  for (int i = 0; i < 25; i++) {
    for (int j = 0; j < 25; j++) {
      oOut << "<ds_applyToCell x=\"" << i << "\" y=\"" << j << "\" /> ";
    }
  }
  oOut << "</ds_deathEvent>"
      << "</EpisodicMortality1>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteEpisodicMortalityXMLFile2()
/////////////////////////////////////////////////////////////////////////////
const char* WriteEpisodicMortalityXMLFile2()
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
      << "<randomSeed>2</randomSeed>"
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

  oOut.close();

  WriteEpisodicMortalityTreeMap(cFileString);

  oOut.open(cFileString, ios::out | ios::app);
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
      << "<tr_stdMaxCrownRad>"
      << "<tr_smcrVal species=\"Western_Hemlock\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Western_Redcedar\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Amabilis_Fir\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Subalpine_Fir\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Hybrid_Spruce\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Lodgepole_Pine\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Trembling_Aspen\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Black_Cottonwood\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Paper_Birch\">10</tr_smcrVal>"
      << "</tr_stdMaxCrownRad>"
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
      << "</allometry>"
      << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>EpisodicMortality</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>ConstantGLI</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Western_Hemlock\" type=\"Snag\" />"
      << "<applyTo species=\"Western_Redcedar\" type=\"Snag\" />"
      << "<applyTo species=\"Amabilis_Fir\" type=\"Snag\" />"
      << "<applyTo species=\"Subalpine_Fir\" type=\"Snag\" />"
      << "<applyTo species=\"Hybrid_Spruce\" type=\"Snag\" />"
      << "<applyTo species=\"Lodgepole_Pine\" type=\"Snag\" />"
      << "<applyTo species=\"Trembling_Aspen\" type=\"Snag\" />"
      << "<applyTo species=\"Black_Cottonwood\" type=\"Snag\" />"
      << "<applyTo species=\"Paper_Birch\" type=\"Snag\" />"
      << "</behavior>"
      << "</behaviorList>"
      << "<ConstantGLI2>"
      << "<li_constGLI>100</li_constGLI>"
      << "</ConstantGLI2>"
      << "<EpisodicMortality1>"
      << "<ds_deathEvent>"
      << "<ds_applyToSpecies species=\"Western_Redcedar\" />"
      << "<ds_applyToSpecies species=\"Western_Hemlock\" />"
      << "<ds_timestep>1</ds_timestep>"
      << "<ds_cutAmountType>percent of density</ds_cutAmountType>"
      << "<ds_dbhRange>"
      << "<ds_low>15.0</ds_low>"
      << "<ds_high>45.0</ds_high>"
      << "<ds_amountToCut>50.0</ds_amountToCut>"
      << "</ds_dbhRange>"
      << "<ds_dbhRange>"
      << "<ds_low>50.0</ds_low>"
      << "<ds_high>80.0</ds_high>"
      << "<ds_amountToCut>40.0</ds_amountToCut>"
      << "</ds_dbhRange>"
      << "<ds_dbhRange>"
      << "<ds_low>80.0</ds_low>"
      << "<ds_high>85.0</ds_high>"
      << "<ds_amountToCut>30.0</ds_amountToCut>"
      << "</ds_dbhRange>"
      << "<ds_dbhRange>"
      << "<ds_low>90.0</ds_low>"
      << "<ds_high>99.0</ds_high>"
      << "<ds_amountToCut>20.0</ds_amountToCut>"
      << "</ds_dbhRange>";
  for (int i = 0; i < 25; i++) {
    for (int j = 0; j < 25; j++) {
      oOut << "<ds_applyToCell x=\"" << i << "\" y=\"" << j << "\" /> ";
    }
  }
  oOut << "</ds_deathEvent>"
      << "</EpisodicMortality1>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteEpisodicMortalityXMLFile3()
/////////////////////////////////////////////////////////////////////////////
const char* WriteEpisodicMortalityXMLFile3()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">" << "<plot>"
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

  oOut.close();

  WriteEpisodicMortalityTreeMap(cFileString);

  oOut.open(cFileString, ios::out | ios::app);
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
      << "<tr_stdMaxCrownRad>"
      << "<tr_smcrVal species=\"Western_Hemlock\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Western_Redcedar\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Amabilis_Fir\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Subalpine_Fir\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Hybrid_Spruce\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Lodgepole_Pine\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Trembling_Aspen\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Black_Cottonwood\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Paper_Birch\">10</tr_smcrVal>"
      << "</tr_stdMaxCrownRad>"
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
      << "</allometry>"
      << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>EpisodicMortality</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>ConstantGLI</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Western_Hemlock\" type=\"Snag\" />"
      << "<applyTo species=\"Western_Redcedar\" type=\"Snag\" />"
      << "<applyTo species=\"Amabilis_Fir\" type=\"Snag\" />"
      << "<applyTo species=\"Subalpine_Fir\" type=\"Snag\" />"
      << "<applyTo species=\"Hybrid_Spruce\" type=\"Snag\" />"
      << "<applyTo species=\"Lodgepole_Pine\" type=\"Snag\" />"
      << "<applyTo species=\"Trembling_Aspen\" type=\"Snag\" />"
      << "<applyTo species=\"Black_Cottonwood\" type=\"Snag\" />"
      << "<applyTo species=\"Paper_Birch\" type=\"Snag\" />"
      << "</behavior>"
      << "</behaviorList>"
      << "<ConstantGLI2>"
      << "<li_constGLI>100</li_constGLI>"
      << "</ConstantGLI2>"
      << "<EpisodicMortality1>"
      << "<ds_deathEvent>"
      << "<ds_applyToSpecies species=\"Trembling_Aspen\" />"
      << "<ds_applyToSpecies species=\"Black_Cottonwood\" />"
      << "<ds_timestep>1</ds_timestep>"
      << "<ds_cutAmountType>absolute density</ds_cutAmountType>"
      << "<ds_dbhRange>"
      << "<ds_low>15.0</ds_low>"
      << "<ds_high>45.0</ds_high>"
      << "<ds_amountToCut>1</ds_amountToCut>"
      << "</ds_dbhRange>"
      << "<ds_dbhRange>"
      << "<ds_low>50.0</ds_low>"
      << "<ds_high>80.0</ds_high>"
      << "<ds_amountToCut>1</ds_amountToCut>"
      << "</ds_dbhRange>"
      << "<ds_dbhRange>"
      << "<ds_low>80.0</ds_low>"
      << "<ds_high>85.0</ds_high>"
      << "<ds_amountToCut>1</ds_amountToCut>"
      << "</ds_dbhRange>"
      << "<ds_dbhRange>"
      << "<ds_low>90.0</ds_low>"
      << "<ds_high>99.0</ds_high>"
      << "<ds_amountToCut>1</ds_amountToCut>"
      << "</ds_dbhRange>";
  for (int i = 0; i < 25; i++) {
    for (int j = 0; j < 25; j++) {
      oOut << "<ds_applyToCell x=\"" << i << "\" y=\"" << j << "\" /> ";
    }
  }
  oOut << "</ds_deathEvent>"
      << "</EpisodicMortality1>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteEpisodicMortalityXMLFile4()
/////////////////////////////////////////////////////////////////////////////
const char* WriteEpisodicMortalityXMLFile4()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";
  int i;

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">" << "<plot>"
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

  oOut.close();

  WriteEpisodicMortalityTreeMap(cFileString);

  oOut.open(cFileString, ios::out | ios::app);
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
      << "<tr_stdMaxCrownRad>"
      << "<tr_smcrVal species=\"Western_Hemlock\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Western_Redcedar\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Amabilis_Fir\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Subalpine_Fir\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Hybrid_Spruce\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Lodgepole_Pine\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Trembling_Aspen\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Black_Cottonwood\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Paper_Birch\">10</tr_smcrVal>"
      << "</tr_stdMaxCrownRad>"
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
      << "</allometry>"
      << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>EpisodicMortality</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>ConstantGLI</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Western_Hemlock\" type=\"Snag\" />"
      << "<applyTo species=\"Western_Redcedar\" type=\"Snag\" />"
      << "<applyTo species=\"Amabilis_Fir\" type=\"Snag\" />"
      << "<applyTo species=\"Subalpine_Fir\" type=\"Snag\" />"
      << "<applyTo species=\"Hybrid_Spruce\" type=\"Snag\" />"
      << "<applyTo species=\"Lodgepole_Pine\" type=\"Snag\" />"
      << "<applyTo species=\"Trembling_Aspen\" type=\"Snag\" />"
      << "<applyTo species=\"Black_Cottonwood\" type=\"Snag\" />"
      << "<applyTo species=\"Paper_Birch\" type=\"Snag\" />"
      << "</behavior>"
      << "</behaviorList>"
      << "<ConstantGLI2>"
      << "<li_constGLI>100</li_constGLI>"
      << "</ConstantGLI2>"
      << "<EpisodicMortality1>"
      << "<ds_deathEvent>"
      << "<ds_applyToSpecies species=\"Western_Redcedar\" />"
      << "<ds_applyToSpecies species=\"Amabilis_Fir\" />"
      << "<ds_applyToSpecies species=\"Western_Hemlock\" />"
      << "<ds_timestep>2</ds_timestep>"
      << "<ds_cutAmountType>percent of density</ds_cutAmountType>"
      << "<ds_dbhRange>"
      << "<ds_low>0.0</ds_low>"
      << "<ds_high>3000.0</ds_high>"
      << "<ds_amountToCut>100.0</ds_amountToCut>"
      << "</ds_dbhRange>"
      << "<ds_percentSeedlingsDie>"
      << "<ds_psdVal species=\"Western_Hemlock\">50</ds_psdVal>"
      << "<ds_psdVal species=\"Western_Redcedar\">50</ds_psdVal>"
      << "<ds_psdVal species=\"Amabilis_Fir\">50</ds_psdVal>"
      << "<ds_psdVal species=\"Subalpine_Fir\">50</ds_psdVal>"
      << "<ds_psdVal species=\"Hybrid_Spruce\">50</ds_psdVal>"
      << "<ds_psdVal species=\"Lodgepole_Pine\">50</ds_psdVal>"
      << "<ds_psdVal species=\"Lodgepole_Pine\">0</ds_psdVal>"
      << "<ds_psdVal species=\"Trembling_Aspen\">0</ds_psdVal>"
      << "<ds_psdVal species=\"Black_Cottonwood\">0</ds_psdVal>"
      << "<ds_psdVal species=\"Paper_Birch\">0</ds_psdVal>"
      << "</ds_percentSeedlingsDie>";
  for (int i = 0; i < 25; i++) {
    for (int j = 0; j < 25; j++) {
      oOut << "<ds_applyToCell x=\"" << i << "\" y=\"" << j << "\" /> ";
    }
  }
  oOut << "</ds_deathEvent>"
      << "<ds_deathEvent>"
      << "<ds_applyToSpecies species=\"Lodgepole_Pine\" />"
      << "<ds_applyToSpecies species=\"Hybrid_Spruce\" />"
      << "<ds_timestep>2</ds_timestep>"
      << "<ds_cutAmountType>percent of basal area</ds_cutAmountType>"
      << "<ds_dbhRange>"
      << "<ds_low>15.0</ds_low>"
      << "<ds_high>45.0</ds_high>"
      << "<ds_amountToCut>50</ds_amountToCut>"
      << "</ds_dbhRange>"
      << "<ds_dbhRange>"
      << "<ds_low>50.0</ds_low>"
      << "<ds_high>80.0</ds_high>"
      << "<ds_amountToCut>100</ds_amountToCut>"
      << "</ds_dbhRange>"
      << "<ds_dbhRange>"
      << "<ds_low>80.0</ds_low>"
      << "<ds_high>85.0</ds_high>"
      << "<ds_amountToCut>30</ds_amountToCut>"
      << "</ds_dbhRange>"
      << "<ds_dbhRange>"
      << "<ds_low>90.0</ds_low>"
      << "<ds_high>100.0</ds_high>"
      << "<ds_amountToCut>0</ds_amountToCut>"
      << "</ds_dbhRange>"
      << "<ds_percentSeedlingsDie>"
      << "<ds_psdVal species=\"Western_Hemlock\">0</ds_psdVal>"
      << "<ds_psdVal species=\"Western_Redcedar\">0</ds_psdVal>"
      << "<ds_psdVal species=\"Amabilis_Fir\">0</ds_psdVal>"
      << "<ds_psdVal species=\"Subalpine_Fir\">0</ds_psdVal>"
      << "<ds_psdVal species=\"Hybrid_Spruce\">0</ds_psdVal>"
      << "<ds_psdVal species=\"Lodgepole_Pine\">0</ds_psdVal>"
      << "<ds_psdVal species=\"Trembling_Aspen\">0</ds_psdVal>"
      << "<ds_psdVal species=\"Black_Cottonwood\">0</ds_psdVal>"
      << "<ds_psdVal species=\"Paper_Birch\">0</ds_psdVal>"
      << "</ds_percentSeedlingsDie>";
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 10; j++) {
      oOut << "<ds_applyToCell x=\"" << i << "\" y=\"" << j << "\" /> ";
    }
  }
  oOut << "</ds_deathEvent>"
      << "<ds_deathEvent>"
      << "<ds_applyToSpecies species=\"Black_Cottonwood\" />"
      << "<ds_timestep>3</ds_timestep>"
      << "<ds_cutAmountType>percent of density</ds_cutAmountType>"
      << "<ds_dbhRange>"
      << "<ds_low>0.0</ds_low>"
      << "<ds_high>10.0</ds_high>"
      << "<ds_amountToCut>50</ds_amountToCut>"
      << "</ds_dbhRange>"
      << "<ds_dbhRange>"
      << "<ds_low>10.0</ds_low>"
      << "<ds_high>20.0</ds_high>"
      << "<ds_amountToCut>100</ds_amountToCut>"
      << "</ds_dbhRange>"
      << "<ds_dbhRange>"
      << "<ds_low>20.0</ds_low>"
      << "<ds_high>30.0</ds_high>"
      << "<ds_amountToCut>30</ds_amountToCut>"
      << "</ds_dbhRange>"
      << "<ds_dbhRange>"
      << "<ds_low>30.0</ds_low>"
      << "<ds_high>40.0</ds_high>"
      << "<ds_amountToCut>0</ds_amountToCut>"
      << "</ds_dbhRange>"
      << "<ds_percentSeedlingsDie>"
      << "<ds_psdVal species=\"Amabilis_Fir\">0</ds_psdVal>"
      << "<ds_psdVal species=\"Hybrid_Spruce\">0</ds_psdVal>"
      << "<ds_psdVal species=\"Western_Hemlock\">0</ds_psdVal>"
      << "<ds_psdVal species=\"Western_Redcedar\">0</ds_psdVal>"
      << "<ds_psdVal species=\"Subalpine_Fir\">0</ds_psdVal>"
      << "<ds_psdVal species=\"Lodgepole_Pine\">0</ds_psdVal>"
      << "<ds_psdVal species=\"Black_Cottonwood\">0</ds_psdVal>"
      << "<ds_psdVal species=\"Paper_Birch\">0</ds_psdVal>"
      << "<ds_psdVal species=\"Trembling_Aspen\">25</ds_psdVal>"
      << "</ds_percentSeedlingsDie>";
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 10; j++) {
      oOut << "<ds_applyToCell x=\"" << i << "\" y=\"" << j << "\" /> ";
    }
  }
  oOut << "</ds_deathEvent>"
      << "<ds_deathEvent>"
      << "<ds_applyToSpecies species=\"Hybrid_Spruce\" />"
      << "<ds_timestep>3</ds_timestep>"
      << "<ds_cutAmountType>absolute basal area</ds_cutAmountType>"
      << "<ds_dbhRange>"
      << "<ds_low>200.0</ds_low>"
      << "<ds_high>300.0</ds_high>"
      << "<ds_amountToCut>50</ds_amountToCut>"
      << "</ds_dbhRange>"
      << "<ds_dbhRange>"
      << "<ds_low>50.0</ds_low>"
      << "<ds_high>80.0</ds_high>"
      << "<ds_amountToCut>100</ds_amountToCut>"
      << "</ds_dbhRange>"
      << "<ds_dbhRange>"
      << "<ds_low>80.0</ds_low>"
      << "<ds_high>85.0</ds_high>"
      << "<ds_amountToCut>30</ds_amountToCut>"
      << "</ds_dbhRange>"
      << "<ds_dbhRange>"
      << "<ds_low>90.0</ds_low>"
      << "<ds_high>100.0</ds_high>"
      << "<ds_amountToCut>0</ds_amountToCut>"
      << "</ds_dbhRange>";
  i = 6;
  for (int j = 6; j < 25; j++) {
    oOut << "<ds_applyToCell x=\"" << i << "\" y=\"" << j << "\" /> ";
  }
  i = 8;
  for (int j = 6; j < 25; j++) {
    oOut << "<ds_applyToCell x=\"" << i << "\" y=\"" << j << "\" /> ";
  }
  oOut << "</ds_deathEvent>"
      << "</EpisodicMortality1>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteEpisodicMortalityXMLFile5()
/////////////////////////////////////////////////////////////////////////////
const char* WriteEpisodicMortalityXMLFile5()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";
  int i, j;

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">" << "<plot>"
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

  oOut.close();

  WriteEpisodicMortalityTreeMap(cFileString);

  oOut.open(cFileString, ios::out | ios::app);
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
      << "<tr_stdMaxCrownRad>"
      << "<tr_smcrVal species=\"Western_Hemlock\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Western_Redcedar\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Amabilis_Fir\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Subalpine_Fir\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Hybrid_Spruce\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Lodgepole_Pine\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Trembling_Aspen\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Black_Cottonwood\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Paper_Birch\">10</tr_smcrVal>"
      << "</tr_stdMaxCrownRad>"
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
      << "</allometry>"
      << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>EpisodicMortality</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>ConstantGLI</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Western_Hemlock\" type=\"Snag\" />"
      << "<applyTo species=\"Western_Redcedar\" type=\"Snag\" />"
      << "<applyTo species=\"Amabilis_Fir\" type=\"Snag\" />"
      << "<applyTo species=\"Subalpine_Fir\" type=\"Snag\" />"
      << "<applyTo species=\"Hybrid_Spruce\" type=\"Snag\" />"
      << "<applyTo species=\"Lodgepole_Pine\" type=\"Snag\" />"
      << "<applyTo species=\"Trembling_Aspen\" type=\"Snag\" />"
      << "<applyTo species=\"Black_Cottonwood\" type=\"Snag\" />"
      << "<applyTo species=\"Paper_Birch\" type=\"Snag\" />"
      << "</behavior>"
      << "</behaviorList>"
      << "<ConstantGLI2>"
      << "<li_constGLI>100</li_constGLI>"
      << "</ConstantGLI2>"
      << "<EpisodicMortality1>"
      << "<ds_deathEvent>"
      << "<ds_applyToSpecies species=\"Western_Hemlock\" />"
      << "<ds_applyToSpecies species=\"Western_Redcedar\" />"
      << "<ds_applyToSpecies species=\"Amabilis_Fir\" />"
      << "<ds_applyToSpecies species=\"Black_Cottonwood\" />"
      << "<ds_applyToSpecies species=\"Subalpine_Fir\" />"
      << "<ds_applyToSpecies species=\"Lodgepole_Pine\" />"
      << "<ds_applyToSpecies species=\"Hybrid_Spruce\" />"
      << "<ds_applyToSpecies species=\"Trembling_Aspen\" />"
      << "<ds_applyToSpecies species=\"Paper_Birch\" />"
      << "<ds_timestep>1</ds_timestep>"
      << "<ds_cutAmountType>absolute density</ds_cutAmountType>"
      << "<ds_dbhRange>"
      << "<ds_low>0.0</ds_low>"
      << "<ds_high>10.0</ds_high>"
      << "<ds_amountToCut>5.0</ds_amountToCut>"
      << "</ds_dbhRange>"
      << "<ds_dbhRange>"
      << "<ds_low>10.0</ds_low>"
      << "<ds_high>20.0</ds_high>"
      << "<ds_amountToCut>100.0</ds_amountToCut>"
      << "</ds_dbhRange>"
      << "<ds_dbhRange>"
      << "<ds_low>20.0</ds_low>"
      << "<ds_high>30.0</ds_high>"
      << "<ds_amountToCut>3.0</ds_amountToCut>"
      << "</ds_dbhRange>"
      << "<ds_dbhRange>"
      << "<ds_low>30.0</ds_low>"
      << "<ds_high>40.0</ds_high>"
      << "<ds_amountToCut>0</ds_amountToCut>"
      << "</ds_dbhRange>"
      << "<ds_percentSeedlingsDie>"
      << "<ds_psdVal species=\"Western_Hemlock\">100</ds_psdVal>"
      << "<ds_psdVal species=\"Western_Redcedar\">100</ds_psdVal>"
      << "<ds_psdVal species=\"Amabilis_Fir\">100</ds_psdVal>"
      << "<ds_psdVal species=\"Subalpine_Fir\">100</ds_psdVal>"
      << "<ds_psdVal species=\"Hybrid_Spruce\">100</ds_psdVal>"
      << "<ds_psdVal species=\"Lodgepole_Pine\">100</ds_psdVal>"
      << "<ds_psdVal species=\"Trembling_Aspen\">100</ds_psdVal>"
      << "<ds_psdVal species=\"Black_Cottonwood\">100</ds_psdVal>"
      << "<ds_psdVal species=\"Paper_Birch\">100</ds_psdVal>"
      << "</ds_percentSeedlingsDie>";
  i = 6;
  for (int j = 6; j < 25; j++) {
    oOut << "<ds_applyToCell x=\"" << i << "\" y=\"" << j << "\" /> ";
  }
  for (i = 8; i < 25; i++) {
    for (j = 0; j < 13; j++) {
      oOut << "<ds_applyToCell x=\"" << i << "\" y=\"" << j << "\" /> ";
    }
  }
  oOut << "</ds_deathEvent>"
      << "</EpisodicMortality1>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteEpisodicMortalityXMLFile6()
/////////////////////////////////////////////////////////////////////////////
const char* WriteEpisodicMortalityXMLFile6()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";
  int i;

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">" << "<plot>"
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

  oOut.close();

  WriteEpisodicMortalityTreeMap(cFileString);

  oOut.open(cFileString, ios::out | ios::app);
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
      << "<tr_stdMaxCrownRad>"
      << "<tr_smcrVal species=\"Western_Hemlock\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Western_Redcedar\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Amabilis_Fir\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Subalpine_Fir\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Hybrid_Spruce\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Lodgepole_Pine\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Trembling_Aspen\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Black_Cottonwood\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Paper_Birch\">10</tr_smcrVal>"
      << "</tr_stdMaxCrownRad>"
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
      << "</allometry>"
      << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>EpisodicMortality</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>ConstantGLI</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Western_Hemlock\" type=\"Snag\" />"
      << "<applyTo species=\"Western_Redcedar\" type=\"Snag\" />"
      << "<applyTo species=\"Amabilis_Fir\" type=\"Snag\" />"
      << "<applyTo species=\"Subalpine_Fir\" type=\"Snag\" />"
      << "<applyTo species=\"Hybrid_Spruce\" type=\"Snag\" />"
      << "<applyTo species=\"Lodgepole_Pine\" type=\"Snag\" />"
      << "<applyTo species=\"Trembling_Aspen\" type=\"Snag\" />"
      << "<applyTo species=\"Black_Cottonwood\" type=\"Snag\" />"
      << "<applyTo species=\"Paper_Birch\" type=\"Snag\" />"
      << "</behavior>"
      << "</behaviorList>"
      << "<ConstantGLI2>"
      << "<li_constGLI>100</li_constGLI>"
      << "</ConstantGLI2>"
      << "<EpisodicMortality1>"
      << "<ds_deathEvent>"
      << "<ds_applyToSpecies species=\"Subalpine_Fir\" />"
      << "<ds_timestep>1</ds_timestep>"
      << "<ds_cutAmountType>percent of density</ds_cutAmountType>"
      << "<ds_dbhRange>"
      << "<ds_low>0.0</ds_low>"
      << "<ds_high>3000.0</ds_high>"
      << "<ds_amountToCut>100.0</ds_amountToCut>"
      << "</ds_dbhRange>";
  i = 6;
  for (int j = 6; j < 25; j++) {
    oOut << "<ds_applyToCell x=\"" << i << "\" y=\"" << j << "\" /> ";
  }
  i = 8;
  for (int j = 6; j < 25; j++) {
    oOut << "<ds_applyToCell x=\"" << i << "\" y=\"" << j << "\" /> ";
  }
  oOut << "</ds_deathEvent>"
      << "<ds_deathEvent>"
      << "<ds_applyToSpecies species=\"Western_Hemlock\" />"
      << "<ds_timestep>2</ds_timestep>"
      << "<ds_cutAmountType>percent of density</ds_cutAmountType>"
      << "<ds_dbhRange>"
      << "<ds_low>0.0</ds_low>"
      << "<ds_high>30.0</ds_high>"
      << "<ds_amountToCut>100</ds_amountToCut>"
      << "</ds_dbhRange>";
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 10; j++) {
      oOut << "<ds_applyToCell x=\"" << i << "\" y=\"" << j << "\" /> ";
    }
  }
  oOut << "</ds_deathEvent>"
      << "<ds_deathEvent>"
      << "<ds_applyToSpecies species=\"Western_Hemlock\" />"
      << "<ds_timestep>2</ds_timestep>"
      << "<ds_cutAmountType>percent of density</ds_cutAmountType>"
      << "<ds_dbhRange>"
      << "<ds_low>0.0</ds_low>"
      << "<ds_high>3000.0</ds_high>"
      << "<ds_amountToCut>100</ds_amountToCut>"
      << "</ds_dbhRange>";
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 10; j++) {
      oOut << "<ds_applyToCell x=\"" << i << "\" y=\"" << j << "\" /> ";
    }
  }
  oOut << "</ds_deathEvent>"
      << "<ds_deathEvent>"
      << "<ds_applyToSpecies species=\"Western_Redcedar\" />"
      << "<ds_timestep>3</ds_timestep>"
      << "<ds_cutAmountType>percent of basal area</ds_cutAmountType>"
      << "<ds_dbhRange>"
      << "<ds_low>0.0</ds_low>"
      << "<ds_high>300.0</ds_high>"
      << "<ds_amountToCut>50</ds_amountToCut>"
      << "</ds_dbhRange>";
  oOut << "<ds_applyToCell x=\"" << 0 << "\" y=\"" << 10 << "\" /> ";
  oOut << "</ds_deathEvent>"
      << "<ds_deathEvent>"
      << "<ds_applyToSpecies species=\"Amabilis_Fir\" />"
      << "<ds_timestep>3</ds_timestep>"
      << "<ds_cutAmountType>absolute basal area</ds_cutAmountType>"
      << "<ds_dbhRange>"
      << "<ds_low>0.0</ds_low>"
      << "<ds_high>300.0</ds_high>"
      << "<ds_amountToCut>4.5</ds_amountToCut>"
      << "</ds_dbhRange>";
  oOut << "<ds_applyToCell x=\"" << 5 << "\" y=\"" << 5 << "\" /> ";
  /*  oOut << "</ds_deathEvent>"
       << "<ds_deathEvent>"
       << "<ds_applyToSpecies species=\"Hybrid_Spruce\" />"
       << "<ds_timestep>3</ds_timestep>"
       << "<ds_cutAmountType>percent of density</ds_cutAmountType>"
       << "<ds_dbhRange>"
       << "<ds_low>0.0</ds_low>"
       << "<ds_high>300.0</ds_high>"
       << "<ds_amountToCut>50</ds_amountToCut>"
       << "</ds_dbhRange>"; */
  oOut << "<ds_applyToCell x=\"" << 10 << "\" y=\"" << 23 << "\" /> ";
  oOut << "</ds_deathEvent>"
      << "<ds_deathEvent>"
      << "<ds_applyToSpecies species=\"Lodgepole_Pine\" />"
      << "<ds_timestep>3</ds_timestep>"
      << "<ds_cutAmountType>absolute density</ds_cutAmountType>"
      << "<ds_dbhRange>"
      << "<ds_low>0.0</ds_low>"
      << "<ds_high>300.0</ds_high>"
      << "<ds_amountToCut>312.5</ds_amountToCut>"
      << "</ds_dbhRange>";
  oOut << "<ds_applyToCell x=\"" << 1 << "\" y=\"" << 1 << "\" /> ";
  oOut << "</ds_deathEvent>"
      << "<ds_deathEvent>"
      << "<ds_applyToSpecies species=\"Trembling_Aspen\" />"
      << "<ds_timestep>3</ds_timestep>"
      << "<ds_cutAmountType>percent of density</ds_cutAmountType>"
      << "<ds_dbhRange>"
      << "<ds_low>0.0</ds_low>"
      << "<ds_high>3000.0</ds_high>"
      << "<ds_amountToCut>100</ds_amountToCut>"
      << "</ds_dbhRange>";
  oOut << "<ds_applyToCell x=\"" << 20 << "\" y=\"" << 0 << "\" /> ";
  oOut << "</ds_deathEvent>"
      << "<ds_deathEvent>"
      << "<ds_applyToSpecies species=\"Black_Cottonwood\" />"
      << "<ds_timestep>3</ds_timestep>"
      << "<ds_cutAmountType>percent of density</ds_cutAmountType>"
      << "<ds_dbhRange>"
      << "<ds_low>0.0</ds_low>"
      << "<ds_high>3000.0</ds_high>"
      << "<ds_amountToCut>100</ds_amountToCut>"
      << "</ds_dbhRange>";
  oOut << "<ds_applyToCell x=\"" << 1 << "\" y=\"" << 7 << "\" /> ";
  oOut << "</ds_deathEvent>"
      << "</EpisodicMortality1>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}


/////////////////////////////////////////////////////////////////////////////
// WriteEpisodicMortalityXMLFile8()
/////////////////////////////////////////////////////////////////////////////
const char* WriteEpisodicMortalityXMLFile8()
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

  oOut.close();

  WriteEpisodicMortalityTreeMap(cFileString);

  oOut.open(cFileString, ios::out | ios::app);
  oOut << "</trees>"
      << "<grid gridName=\"mortepisodemastercuts\">"
      << "<ma_lengthXCells>2</ma_lengthXCells>"
      << "<ma_lengthYCells>2</ma_lengthYCells>"
      << "</grid>"
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
      << "<tr_stdMaxCrownRad>"
      << "<tr_smcrVal species=\"Western_Hemlock\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Western_Redcedar\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Amabilis_Fir\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Subalpine_Fir\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Hybrid_Spruce\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Lodgepole_Pine\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Trembling_Aspen\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Black_Cottonwood\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Paper_Birch\">10</tr_smcrVal>"
      << "</tr_stdMaxCrownRad>"
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
      << "</allometry>"
      << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>EpisodicMortality</behaviorName>"
      << "<version>2</version>"
      << "<listPosition>1</listPosition>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>ConstantGLI</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Western_Hemlock\" type=\"Snag\" />"
      << "<applyTo species=\"Western_Redcedar\" type=\"Snag\" />"
      << "<applyTo species=\"Amabilis_Fir\" type=\"Snag\" />"
      << "<applyTo species=\"Subalpine_Fir\" type=\"Snag\" />"
      << "<applyTo species=\"Hybrid_Spruce\" type=\"Snag\" />"
      << "<applyTo species=\"Lodgepole_Pine\" type=\"Snag\" />"
      << "<applyTo species=\"Trembling_Aspen\" type=\"Snag\" />"
      << "<applyTo species=\"Black_Cottonwood\" type=\"Snag\" />"
      << "<applyTo species=\"Paper_Birch\" type=\"Snag\" />"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>StochasticMortality</behaviorName>"
      << "<version>1</version>"
      << "<applyTo species=\"Amabilis_Fir\" type=\"Adult\" />"
      << "<applyTo species=\"Amabilis_Fir\" type=\"Snag\" />"
      << "<applyTo species=\"Paper_Birch\" type=\"Adult\" />"
      << "<applyTo species=\"Paper_Birch\" type=\"Snag\" />"
      << "<applyTo species=\"Western_Hemlock\" type=\"Adult\" />"
      << "<applyTo species=\"Western_Hemlock\" type=\"Snag\" />"
      << "<listPosition>3</listPosition>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>SnagDecayClassDynamics</behaviorName>"
      << "<version>2.0</version>"
      << "<listPosition>4</listPosition>"
      << "<applyTo species=\"Amabilis_Fir\" type=\"Adult\" />"
      << "<applyTo species=\"Amabilis_Fir\" type=\"Snag\" />"
      << "<applyTo species=\"Paper_Birch\" type=\"Adult\" />"
      << "<applyTo species=\"Paper_Birch\" type=\"Snag\" />"
      << "<applyTo species=\"Western_Hemlock\" type=\"Adult\" />"
      << "<applyTo species=\"Western_Hemlock\" type=\"Snag\" />"
      << "</behavior>"
      << "</behaviorList>"
      << "<ConstantGLI2>"
      << "<li_constGLI>100</li_constGLI>"
      << "</ConstantGLI2>"
      << "<EpisodicMortality1>"
      << "<ds_deathEvent>"
      << "<ds_applyToSpecies species=\"Amabilis_Fir\" />"
      << "<ds_applyToSpecies species=\"Paper_Birch\" />"
      << "<ds_applyToSpecies species=\"Western_Hemlock\" />"
      << "<ds_applyToSpecies species=\"Western_Redcedar\" />"
      << "<ds_applyToSpecies species=\"Subalpine_Fir\" />"
      << "<ds_applyToSpecies species=\"Hybrid_Spruce\" />"
      << "<ds_applyToSpecies species=\"Lodgepole_Pine\" />"
      << "<ds_applyToSpecies species=\"Trembling_Aspen\" />"
      << "<ds_applyToSpecies species=\"Black_Cottonwood\" />"
      << "<ds_timestep>1</ds_timestep>"
      << "<ds_cutAmountType>percent of density</ds_cutAmountType>"
      << "<ha_maxSnagDecayClass>1</ha_maxSnagDecayClass>"
      << "<ds_dbhRange>"
      << "<ds_low>0.0</ds_low>"
      << "<ds_high>3000.0</ds_high>"
      << "<ds_amountToCut>100.0</ds_amountToCut>"
      << "</ds_dbhRange>"
      << "<ds_percentSeedlingsDie>"
      << "<ds_psdVal species=\"Western_Hemlock\">100</ds_psdVal>"
      << "<ds_psdVal species=\"Western_Redcedar\">100</ds_psdVal>"
      << "<ds_psdVal species=\"Amabilis_Fir\">100</ds_psdVal>"
      << "<ds_psdVal species=\"Subalpine_Fir\">100</ds_psdVal>"
      << "<ds_psdVal species=\"Hybrid_Spruce\">100</ds_psdVal>"
      << "<ds_psdVal species=\"Lodgepole_Pine\">100</ds_psdVal>"
      << "<ds_psdVal species=\"Trembling_Aspen\">100</ds_psdVal>"
      << "<ds_psdVal species=\"Black_Cottonwood\">100</ds_psdVal>"
      << "<ds_psdVal species=\"Paper_Birch\">100</ds_psdVal>"
      << "</ds_percentSeedlingsDie>";
  for (int i = 0; i < 22; i++) {
    for (int j = 0; j < 37; j++) {
      oOut << "<ds_applyToCell x=\"" << i << "\" y=\"" << j << "\" /> ";
    }
  }
  oOut << "</ds_deathEvent>"
      << "</EpisodicMortality1>"
      << "<StochasticMortality3>"
      << "<mo_stochasticMortRate>"
      << "<mo_smrVal species=\"Amabilis_Fir\">0.0</mo_smrVal>"
      << "<mo_smrVal species=\"Paper_Birch\">0.0</mo_smrVal>"
      << "<mo_smrVal species=\"Western_Hemlock\">0.0</mo_smrVal>"
      << "</mo_stochasticMortRate>"
      << "</StochasticMortality3>"
      << "<SnagDecayClassDynamics4>"
      << "<sd_snagDecompTreefallAlpha>-0.805</sd_snagDecompTreefallAlpha>"
      << "<sd_snagDecompTreefallBeta>"
      << "<sd_sdtbVal species=\"Amabilis_Fir\">0.000</sd_sdtbVal>"
      << "<sd_sdtbVal species=\"Paper_Birch\">0.000</sd_sdtbVal>"
      << "<sd_sdtbVal species=\"Western_Hemlock\">0.000</sd_sdtbVal>"
      << "</sd_snagDecompTreefallBeta>"
      << "<sd_snagDecompTreefallDelta>-0.016</sd_snagDecompTreefallDelta>"
      << "<sd_snagDecompTreefallTheta>-0.026</sd_snagDecompTreefallTheta>"
      << "<sd_snagDecompTreefallIota>3.389</sd_snagDecompTreefallIota>"
      << "<sd_snagDecompTreefallLambda>-0.084</sd_snagDecompTreefallLambda>"
      << "<sd_snagDecompSnagfallAlpha>5.691</sd_snagDecompSnagfallAlpha>"
      << "<sd_snagDecompSnagfallBeta>"
      << "<sd_sdsbVal species=\"Amabilis_Fir\">0.000</sd_sdsbVal>"
      << "<sd_sdsbVal species=\"Paper_Birch\">0.000</sd_sdsbVal>"
      << "<sd_sdsbVal species=\"Western_Hemlock\">0.000</sd_sdsbVal>"
      << "</sd_snagDecompSnagfallBeta>"
      << "<sd_snagDecompSnagfallGamma2>0.177</sd_snagDecompSnagfallGamma2>"
      << "<sd_snagDecompSnagfallGamma3>0.542</sd_snagDecompSnagfallGamma3>"
      << "<sd_snagDecompSnagfallGamma4>0.702</sd_snagDecompSnagfallGamma4>"
      << "<sd_snagDecompSnagfallGamma5>0.528</sd_snagDecompSnagfallGamma5>"
      << "<sd_snagDecompSnagfallZeta>-3.777</sd_snagDecompSnagfallZeta>"
      << "<sd_snagDecompSnagfallEta>0.531</sd_snagDecompSnagfallEta>"
      << "<sd_snagDecompSnagfallKappa>0.157</sd_snagDecompSnagfallKappa>"
      << "<sd_snagDecompLiveTo1Prob>0.290</sd_snagDecompLiveTo1Prob>"
      << "<sd_snagDecompLiveTo2Prob>0.229</sd_snagDecompLiveTo2Prob>"
      << "<sd_snagDecompLiveTo3Prob>0.196</sd_snagDecompLiveTo3Prob>"
      << "<sd_snagDecompLiveTo4Prob>0.124</sd_snagDecompLiveTo4Prob>"
      << "<sd_snagDecompLiveTo5Prob>0.161</sd_snagDecompLiveTo5Prob>"
      << "<sd_snagDecomp1To1Prob>0.045</sd_snagDecomp1To1Prob>"
      << "<sd_snagDecomp1To2Prob>0.186</sd_snagDecomp1To2Prob>"
      << "<sd_snagDecomp1To3Prob>0.329</sd_snagDecomp1To3Prob>"
      << "<sd_snagDecomp1To4Prob>0.166</sd_snagDecomp1To4Prob>"
      << "<sd_snagDecomp1To5Prob>0.274</sd_snagDecomp1To5Prob>"
      << "<sd_snagDecomp2To2Prob>0.165</sd_snagDecomp2To2Prob>"
      << "<sd_snagDecomp2To3Prob>0.379</sd_snagDecomp2To3Prob>"
      << "<sd_snagDecomp2To4Prob>0.204</sd_snagDecomp2To4Prob>"
      << "<sd_snagDecomp2To5Prob>0.252</sd_snagDecomp2To5Prob>"
      << "<sd_snagDecomp3To3Prob>0.351</sd_snagDecomp3To3Prob>"
      << "<sd_snagDecomp3To4Prob>0.346</sd_snagDecomp3To4Prob>"
      << "<sd_snagDecomp3To5Prob>0.303</sd_snagDecomp3To5Prob>"
      << "<sd_snagDecomp4To4Prob>0.527</sd_snagDecomp4To4Prob>"
      << "<sd_snagDecomp4To5Prob>0.473</sd_snagDecomp4To5Prob>"
      << "<sd_snagDecomp5To5Prob>1.000</sd_snagDecomp5To5Prob>"
      << "<sd_minSnagBreakHeight>6</sd_minSnagBreakHeight>"
      << "<sd_maxSnagBreakHeight>6</sd_maxSnagBreakHeight>"
      << "</SnagDecayClassDynamics4>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}
