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
            (fabs(fX - 54.5044) < 0.001 && fabs(fY - 85.0464) < 0.001))
          EXPECT_EQ(p_oTree->GetType(), clTreePopulation::snag);

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
  float fTemp, fX, fY;
  int iNumXCells, iNumYCells, iNumSpecies, iX, iY, j, k,
  iNumTrees = 1980, iCounter = 0, i;
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
    CheckEpisodicMortalityResults(p_oPop, iNumTrees, p_oFakeTrees);

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
      << "<ds_timestep>3</ds_timestep>"
      << "<ds_cutAmountType>absolute basal area</ds_cutAmountType>"
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
      << "</paramFile>";

  oOut.close();

  return cFileString;
}


void WriteEpisodicMortalityTreeMap(const char *cFileName) {
  using namespace std;
  std::fstream oOut;
  oOut.open(cFileName, ios::out | ios::app);
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

  oOut.close();
}
