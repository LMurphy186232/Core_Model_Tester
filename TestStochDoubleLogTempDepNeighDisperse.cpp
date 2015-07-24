//---------------------------------------------------------------------------
// TestStochDoubleLogTempDepNeighDisperse.cpp
//---------------------------------------------------------------------------
#include "TestStochDoubleLogTempDepNeighDisperse.h"
#include <gtest/gtest.h>
#include <fstream>
#include "SimManager.h"
#include "TreePopulation.h"
#include "Grid.h"
#include "BehaviorBase.h"
#include "Plot.h"
#include <math.h>
#include <fstream>

/////////////////////////////////////////////////////////////////////////////
// TestStochDoubleLogTempDepNeighDisperse1()
// Tests dispersal, run 1. This is testing the colonization.
/////////////////////////////////////////////////////////////////////////////
TEST(StochDoubleLogTempDepNeighDisperse, TestRun1) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {

    //Feed our file to the sim manager
    p_oSimManager->ReadFile(WriteXMLFile1());

    clGrid *p_oSeedGrid;
    std::stringstream sLabel;
    float fSeeds;
    int i, iCellX, iCellY, iNumXCells, iNumYCells,
        iNumSpp = 1000,
        iNum0Spp = 0, iExpected0Spp;

    //Run one timestep - can't just use RunSim() because TimestepCleanup will
    //erase the results we want to check
    for (i = 0; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
      clBehaviorBase *p_oBase = p_oSimManager->GetBehaviorObject(i);
      p_oBase->Action();
    }

    p_oSeedGrid = p_oSimManager->GetGridObject("Dispersed Seeds");
    iNumXCells = p_oSeedGrid->GetNumberXCells();
    iNumYCells = p_oSeedGrid->GetNumberYCells();

    //Check how many species have 0s
    for (i = 0; i < iNumSpp; i++) {

      sLabel << "seeds_" << i;

      //Check the first cell - if it's 0, they all should be 0; if not,
      //they all should be 2
      p_oSeedGrid->GetValueOfCell(0, 0, p_oSeedGrid->GetFloatDataCode(sLabel.str()), &fSeeds);
      if (fSeeds == 0) {
        iNum0Spp++;
        for (iCellX = 0; iCellX < iNumXCells; iCellX++) {
          for (iCellY = 0; iCellY < iNumYCells; iCellY++) {
            p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode(sLabel.str()), &fSeeds);
            EXPECT_EQ(0, fSeeds);
          }
        }
      } else {
        for (iCellX = 0; iCellX < iNumXCells; iCellX++) {
          for (iCellY = 0; iCellY < iNumYCells; iCellY++) {
            p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode(sLabel.str()), &fSeeds);
            EXPECT_EQ(32, fSeeds);
          }
        }
      }

      sLabel.str("");
    }
    iExpected0Spp = 734;
    EXPECT_LT(fabs(iNum0Spp - iExpected0Spp) / iExpected0Spp, 0.1);


    p_oSimManager->RunSim(1);

    //Update temp, run again
    clPlot *p_oPlot = p_oSimManager->GetPlotObject();
    p_oPlot->SetMeanAnnualTemp(20);

    for (i = 0; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
      clBehaviorBase *p_oBase = p_oSimManager->GetBehaviorObject(i);
      p_oBase->Action();
    }

    iNum0Spp = 0;
    //Check how many species have 0s
    for (i = 0; i < iNumSpp; i++) {

      sLabel << "seeds_" << i;

      //Check the first cell - if it's 0, they all should be 0; if not,
      //they all should be 2
      p_oSeedGrid->GetValueOfCell(0, 0, p_oSeedGrid->GetFloatDataCode(sLabel.str()), &fSeeds);
      if (fSeeds == 0) {
        iNum0Spp++;
        for (iCellX = 0; iCellX < iNumXCells; iCellX++) {
          for (iCellY = 0; iCellY < iNumYCells; iCellY++) {
            p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode(sLabel.str()), &fSeeds);
            EXPECT_EQ(0, fSeeds);
          }
        }
      } else {
        for (iCellX = 0; iCellX < iNumXCells; iCellX++) {
          for (iCellY = 0; iCellY < iNumYCells; iCellY++) {
            p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode(sLabel.str()), &fSeeds);
            EXPECT_EQ(32, fSeeds);
          }
        }
      }

      sLabel.str("");
    }
    iExpected0Spp = 512;
    EXPECT_LT(fabs(iNum0Spp - iExpected0Spp) / iExpected0Spp, 0.1);


    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}


/////////////////////////////////////////////////////////////////////////////
// TestStochDoubleLogTempDepNeighDisperse2()
// Tests dispersal, run 1. This tests the final Poisson draw.
/////////////////////////////////////////////////////////////////////////////
TEST(StochDoubleLogTempDepNeighDisperse, TestRun2) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {

    //Feed our file to the sim manager
    p_oSimManager->ReadFile(WriteXMLFile2());

    clTreePopulation *p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject("treepopulation");
    clGrid *p_oSeedGrid;
    float fDiam, fExpectedSeeds, fSeeds, fMeanSeeds;
    int i, iCellX, iCellY, iNumXCells, iNumYCells;

    //Create a 15 cm neighbor of each spp every 2 m
    fDiam = 15.0;
    for (iCellX = 0; iCellX < 100; iCellX = iCellX+2) {
      for (iCellY = 0; iCellY < 100; iCellY = iCellY+2) {
        p_oPop->CreateTree((float)iCellX, (float)iCellY, 0, clTreePopulation::adult, fDiam);
        p_oPop->CreateTree((float)iCellX, (float)iCellY, 1, clTreePopulation::adult, fDiam);
        p_oPop->CreateTree((float)iCellX, (float)iCellY, 2, clTreePopulation::adult, fDiam);
        p_oPop->CreateTree((float)iCellX, (float)iCellY, 3, clTreePopulation::adult, fDiam);
      }
    }

    //Run one timestep - can't just use RunSim() because TimestepCleanup will
    //erase the results we want to check
    for (i = 0; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
      clBehaviorBase *p_oBase = p_oSimManager->GetBehaviorObject(i);
      p_oBase->Action();
    }

    p_oSeedGrid = p_oSimManager->GetGridObject("Dispersed Seeds");

    //Get mean cell values
    iNumXCells = p_oSeedGrid->GetNumberXCells();
    iNumYCells = p_oSeedGrid->GetNumberYCells();

    // Species 2
    fMeanSeeds = 0;
    for (iCellX = 0; iCellX < iNumXCells; iCellX++) {
      for (iCellY = 0; iCellY < iNumYCells; iCellY++) {
        p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
        fMeanSeeds += fSeeds;
      }
    }
    fMeanSeeds /= 2500;
    fExpectedSeeds = 104.1744303;
    EXPECT_LT(fabs(fMeanSeeds - fExpectedSeeds) / fExpectedSeeds, 0.1);

    // Species 3
    fMeanSeeds = 0;
    for (iCellX = 0; iCellX < iNumXCells; iCellX++) {
      for (iCellY = 0; iCellY < iNumYCells; iCellY++) {
        p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
        fMeanSeeds += fSeeds;
      }
    }
    fMeanSeeds /= 2500;
    fExpectedSeeds = 14.29573744;
    EXPECT_LT(fabs(fMeanSeeds - fExpectedSeeds) / fExpectedSeeds, 0.1);

    // Species 4
    fMeanSeeds = 0;
    for (iCellX = 0; iCellX < iNumXCells; iCellX++) {
      for (iCellY = 0; iCellY < iNumYCells; iCellY++) {
        p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
        fMeanSeeds += fSeeds;
      }
    }
    fMeanSeeds /= 2500;
    fExpectedSeeds = 16.08139708;
    EXPECT_LT(fabs(fMeanSeeds - fExpectedSeeds) / fExpectedSeeds, 0.1);

    p_oSimManager->RunSim(1);

    //Update temp, run again
    clPlot *p_oPlot = p_oSimManager->GetPlotObject();
    p_oPlot->SetMeanAnnualTemp(20);

    for (i = 0; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
      clBehaviorBase *p_oBase = p_oSimManager->GetBehaviorObject(i);
      p_oBase->Action();
    }

    // Species 2
    fMeanSeeds = 0;
    for (iCellX = 0; iCellX < iNumXCells; iCellX++) {
      for (iCellY = 0; iCellY < iNumYCells; iCellY++) {
        p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
        fMeanSeeds += fSeeds;
      }
    }
    fMeanSeeds /= 2500;
    fExpectedSeeds = 105.2566056;
    EXPECT_LT(fabs(fMeanSeeds - fExpectedSeeds) / fExpectedSeeds, 0.1);

    // Species 3
    fMeanSeeds = 0;
    for (iCellX = 0; iCellX < iNumXCells; iCellX++) {
      for (iCellY = 0; iCellY < iNumYCells; iCellY++) {
        p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
        fMeanSeeds += fSeeds;
      }
    }
    fMeanSeeds /= 2500;
    fExpectedSeeds = 85.69201421;
    EXPECT_LT(fabs(fMeanSeeds - fExpectedSeeds) / fExpectedSeeds, 0.1);

    // Species 4
    fMeanSeeds = 0;
    for (iCellX = 0; iCellX < iNumXCells; iCellX++) {
      for (iCellY = 0; iCellY < iNumYCells; iCellY++) {
        p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
        fMeanSeeds += fSeeds;
      }
    }
    fMeanSeeds /= 2500;
    fExpectedSeeds = 15.81798069;
    EXPECT_LT(fabs(fMeanSeeds - fExpectedSeeds) / fExpectedSeeds, 0.1);

    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}


/////////////////////////////////////////////////////////////////////////////
// TestStochDoubleLogTempDepNeighDisperse3()
// Tests dispersal, run 3.
/////////////////////////////////////////////////////////////////////////////
TEST(StochDoubleLogTempDepNeighDisperse, TestRun3) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {

    //Feed our file to the sim manager
    p_oSimManager->ReadFile(WriteXMLFile34(1));

    clTreePopulation *p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject("treepopulation");
    clGrid *p_oSeedGrid;
    float fDiam, fExpectedSeeds2, fExpectedSeeds3, fExpectedSeeds4, fSeeds;
    int iSpecies, i, iCellX, iCellY;

    //Create all neighbors
    fDiam = 10.5;
    iSpecies = 1;
    p_oPop->CreateTree(50, 50, iSpecies, clTreePopulation::adult, fDiam);

    fDiam = 15;
    iSpecies = 2;
    p_oPop->CreateTree(53, 52, iSpecies, clTreePopulation::adult, fDiam);

    fDiam = 26;
    iSpecies = 2;
    p_oPop->CreateTree(55, 60, iSpecies, clTreePopulation::adult, fDiam);

    fDiam = 25;
    iSpecies = 3;
    p_oPop->CreateTree(59, 50, iSpecies, clTreePopulation::adult, fDiam);

    fDiam = 30;
    iSpecies = 1;
    p_oPop->CreateTree(50, 59, iSpecies, clTreePopulation::adult, fDiam);

    fDiam = 45;
    iSpecies = 2;
    p_oPop->CreateTree(55, 55, iSpecies, clTreePopulation::adult, fDiam);

    fDiam = 15;
    iSpecies = 3;
    p_oPop->CreateTree(60, 61, iSpecies, clTreePopulation::adult, fDiam);

    fDiam = 76;
    iSpecies = 2;
    p_oPop->CreateTree(44, 60, iSpecies, clTreePopulation::adult, fDiam);


    //Now create all the neighbors that are too small or dead to compete
    fDiam = 4;
    iSpecies = 1;
    p_oPop->CreateTree(52, 52, iSpecies, clTreePopulation::sapling, fDiam);
    fDiam = 4;
    iSpecies = 2;
    p_oPop->CreateTree(53, 53, iSpecies, clTreePopulation::sapling, fDiam);
    p_oPop->CreateTree(56, 56, 0, clTreePopulation::snag, 30);
    p_oPop->CreateTree(56, 56, 0, clTreePopulation::seedling, 0.2);

    //Run one timestep - can't just use RunSim() because TimestepCleanup will
    //erase the results we want to check
    for (i = 0; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
      clBehaviorBase *p_oBase = p_oSimManager->GetBehaviorObject(i);
      p_oBase->Action();
    }

    p_oSeedGrid = p_oSimManager->GetGridObject("Dispersed Seeds");

    //Check the seed counts
    iCellX = 2; iCellY = 2;
    fExpectedSeeds2 = 32;
    fExpectedSeeds3 = 21.33333333;
    fExpectedSeeds4 = 57.6;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds2), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds3), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 5; iCellY = 6;
    fExpectedSeeds2 = 92.56975891;
    fExpectedSeeds3 = 45.58095398;
    fExpectedSeeds4 = 57.6;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds2), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds3), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 6; iCellY = 5;
    fExpectedSeeds2 = 38.61006278;
    fExpectedSeeds3 = 22.24246759;
    fExpectedSeeds4 = 104.1168249;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds2), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds3), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 5; iCellY = 5;
    fExpectedSeeds2 = 38.61006278;
    fExpectedSeeds3 = 21.33333333;
    fExpectedSeeds4 = 57.6;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds2), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds3), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 6; iCellY = 6;
    fExpectedSeeds2 = 92.56975891;
    fExpectedSeeds3 = 33.1561192;
    fExpectedSeeds4 = 104.1168249;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds2), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds3), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 7; iCellY = 6;
    fExpectedSeeds2 = 32;
    fExpectedSeeds3 = 33.1561192;
    fExpectedSeeds4 = 120.8628819;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds2), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds3), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 6; iCellY = 7;
    fExpectedSeeds2 = 85.95969613;
    fExpectedSeeds3 = 56.49460559;
    fExpectedSeeds4 = 74.34605697;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds2), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds3), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 12; iCellY = 12;
    fExpectedSeeds2 = 8;
    fExpectedSeeds3 = 5.333333333;
    fExpectedSeeds4 = 14.4;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds2), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds3), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    p_oSimManager->RunSim(1);

    //Update temp, run again
    clPlot *p_oPlot = p_oSimManager->GetPlotObject();
    p_oPlot->SetMeanAnnualTemp(20);

    for (i = 0; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
      clBehaviorBase *p_oBase = p_oSimManager->GetBehaviorObject(i);
      p_oBase->Action();
    }

    iCellX = 2; iCellY = 2;
    fExpectedSeeds2 = 32;
    fExpectedSeeds3 = 21.33333333;
    fExpectedSeeds4 = 57.6;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds2), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds3), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 5; iCellY = 6;
    fExpectedSeeds2 = 93.2176212;
    fExpectedSeeds3 = 448.5827335;
    fExpectedSeeds4 = 57.6;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds2), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds3), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 6; iCellY = 5;
    fExpectedSeeds2 = 38.6807649;
    fExpectedSeeds3 = 37.35251598;
    fExpectedSeeds4 = 102.9696628;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds2), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds3), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 5; iCellY = 5;
    fExpectedSeeds2 = 38.6807649;
    fExpectedSeeds3 = 21.33333333;
    fExpectedSeeds4 = 57.6;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds2), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds3), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 6; iCellY = 6;
    fExpectedSeeds2 = 93.2176212;
    fExpectedSeeds3 = 229.6539041;
    fExpectedSeeds4 = 102.9696628;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds2), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds3), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 7; iCellY = 6;
    fExpectedSeeds2 = 32;
    fExpectedSeeds3 = 229.6539041;
    fExpectedSeeds4 = 119.3027414;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds2), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds3), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 6; iCellY = 7;
    fExpectedSeeds2 = 86.5368563;
    fExpectedSeeds3 = 640.8841216;
    fExpectedSeeds4 = 73.93307862;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds2), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds3), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 12; iCellY = 12;
    fExpectedSeeds2 = 8;
    fExpectedSeeds3 = 5.333333333;
    fExpectedSeeds4 = 14.4;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds2), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds3), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}


/////////////////////////////////////////////////////////////////////////////
// TestStochDoubleLogTempDepNeighDisperse4()
/////////////////////////////////////////////////////////////////////////////
TEST(StochDoubleLogTempDepNeighDisperse, TestRun4)
{
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    //Feed our file to the sim manager
    p_oSimManager->ReadFile(WriteXMLFile34(3));

    clTreePopulation *p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject("treepopulation");
    clGrid *p_oSeedGrid;
    float fDiam, fExpectedSeeds2, fExpectedSeeds3, fExpectedSeeds4, fSeeds;
    int iSpecies, i, iCellX, iCellY;

    //Create all neighbors
    fDiam = 10.5;
    iSpecies = 1;
    p_oPop->CreateTree(50, 50, iSpecies, clTreePopulation::adult, fDiam);

    fDiam = 15;
    iSpecies = 2;
    p_oPop->CreateTree(53, 52, iSpecies, clTreePopulation::adult, fDiam);

    fDiam = 26;
    iSpecies = 2;
    p_oPop->CreateTree(55, 60, iSpecies, clTreePopulation::adult, fDiam);

    fDiam = 25;
    iSpecies = 3;
    p_oPop->CreateTree(59, 50, iSpecies, clTreePopulation::adult, fDiam);

    fDiam = 30;
    iSpecies = 1;
    p_oPop->CreateTree(50, 59, iSpecies, clTreePopulation::adult, fDiam);

    fDiam = 45;
    iSpecies = 2;
    p_oPop->CreateTree(55, 55, iSpecies, clTreePopulation::adult, fDiam);

    fDiam = 15;
    iSpecies = 3;
    p_oPop->CreateTree(60, 61, iSpecies, clTreePopulation::adult, fDiam);

    fDiam = 76;
    iSpecies = 2;
    p_oPop->CreateTree(44, 60, iSpecies, clTreePopulation::adult, fDiam);


    //Now create all the neighbors that are too small or dead to compete
    fDiam = 4;
    iSpecies = 1;
    p_oPop->CreateTree(52, 52, iSpecies, clTreePopulation::sapling, fDiam);
    fDiam = 4;
    iSpecies = 2;
    p_oPop->CreateTree(53, 53, iSpecies, clTreePopulation::sapling, fDiam);
    p_oPop->CreateTree(56, 56, 0, clTreePopulation::snag, 30);
    p_oPop->CreateTree(56, 56, 0, clTreePopulation::seedling, 0.2);

    //Run one timestep - can't just use RunSim() because TimestepCleanup will
    //erase the results we want to check
    for (i = 0; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
      clBehaviorBase *p_oBase = p_oSimManager->GetBehaviorObject(i);
      p_oBase->Action();
    }

    p_oSeedGrid = p_oSimManager->GetGridObject("Dispersed Seeds");

    //Check the seed counts
    iCellX = 2; iCellY = 2;
    fExpectedSeeds2 = 96;
    fExpectedSeeds3 = 64;
    fExpectedSeeds4 = 172.8;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds2), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds3), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 5; iCellY = 6;
    fExpectedSeeds2 = 277.7092767;
    fExpectedSeeds3 = 136.7428619;
    fExpectedSeeds4 = 172.8;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds2), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds3), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 6; iCellY = 5;
    fExpectedSeeds2 = 115.8301883;
    fExpectedSeeds3 = 66.72740276;
    fExpectedSeeds4 = 312.3504748;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds2), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds3), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 5; iCellY = 5;
    fExpectedSeeds2 = 115.8301883;
    fExpectedSeeds3 = 64;
    fExpectedSeeds4 = 172.8;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds2), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds3), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 6; iCellY = 6;
    fExpectedSeeds2 = 277.7092767;
    fExpectedSeeds3 = 99.46835761;
    fExpectedSeeds4 = 312.3504748;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds2), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds3), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 7; iCellY = 6;
    fExpectedSeeds2 = 96;
    fExpectedSeeds3 = 99.46835761;
    fExpectedSeeds4 = 362.5886457;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds2), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds3), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 6; iCellY = 7;
    fExpectedSeeds2 = 257.8790884;
    fExpectedSeeds3 = 169.4838168;
    fExpectedSeeds4 = 223.0381709;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds2), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds3), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 12; iCellY = 12;
    fExpectedSeeds2 = 24;
    fExpectedSeeds3 = 16;
    fExpectedSeeds4 = 43.2;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds2), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds3), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}


/////////////////////////////////////////////////////////////////////////////
// WriteXMLFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteXMLFile1()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";
  int iNumSpecies = 1000, i;

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>4</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>80.0</plot_lenX>"
       << "<plot_lenY>80.0</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>"
       << "<trees>"
       << "<tr_speciesList>";
  for (i = 0; i < iNumSpecies; i++)
    oOut << "<tr_species speciesName=\"Species_" << i << "\"/>";
  oOut << "</tr_speciesList>"
       << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
       << "<tr_minAdultDBH>";
  for (i = 0; i < iNumSpecies; i++)
    oOut << "<tr_madVal species=\"Species_" << i << "\">10.0</tr_madVal>";
  oOut << "</tr_minAdultDBH>"
       << "<tr_maxSeedlingHeight>";
  for (i = 0; i < iNumSpecies; i++)
    oOut << "<tr_mshVal species=\"Species_" << i << "\">1.35</tr_mshVal>";
  oOut << "</tr_maxSeedlingHeight>"
       << "</trees>"
       << "<allometry>"
       << "<tr_canopyHeight>";
  for (i = 0; i < iNumSpecies; i++)
    oOut << "<tr_chVal species=\"Species_" << i << "\">39.48</tr_chVal>";
  oOut << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>";
  for (i = 0; i < iNumSpecies; i++)
    oOut << "<tr_sacrVal species=\"Species_" << i << "\">0.0549</tr_sacrVal>";
  oOut << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>";
  for (i = 0; i < iNumSpecies; i++)
    oOut << "<tr_screVal species=\"Species_" << i << "\">1.0</tr_screVal>";
  oOut << "</tr_stdCrownRadExp>"
       << "<tr_conversionDiam10ToDBH>";
  for (i = 0; i < iNumSpecies; i++)
    oOut << "<tr_cdtdVal species=\"Species_" << i << "\">1</tr_cdtdVal>";
  oOut << "</tr_conversionDiam10ToDBH>"
      << "<tr_interceptDiam10ToDBH>";
  for (i = 0; i < iNumSpecies; i++)
    oOut << "<tr_idtdVal species=\"Species_" << i << "\">0</tr_idtdVal>";
  oOut << "</tr_interceptDiam10ToDBH>"
      << "<tr_stdAsympCrownHt>";
  for (i = 0; i < iNumSpecies; i++)
    oOut << "<tr_sachVal species=\"Species_" << i << "\">0.389</tr_sachVal>";
  oOut << "</tr_stdAsympCrownHt>"
      << "<tr_stdCrownHtExp>";
  for (i = 0; i < iNumSpecies; i++)
    oOut << "<tr_scheVal species=\"Species_" << i << "\">1.0</tr_scheVal>";
  oOut << "</tr_stdCrownHtExp>"
      << "<tr_slopeOfHeight-Diam10>";
  for (i = 0; i < iNumSpecies; i++)
    oOut << "<tr_sohdVal species=\"Species_" << i << "\">0.03418</tr_sohdVal>";
  oOut << "</tr_slopeOfHeight-Diam10>"
      << "<tr_slopeOfAsymHeight>";
  for (i = 0; i < iNumSpecies; i++)
    oOut << "<tr_soahVal species=\"Species_" << i << "\">0.0299</tr_soahVal>";
  oOut << "</tr_slopeOfAsymHeight>"
      << "<tr_whatSeedlingHeightDiam>";
  for (i = 0; i < iNumSpecies; i++)
    oOut << "<tr_wsehdVal species=\"Species_" << i << "\">0</tr_wsehdVal>";
  oOut << "</tr_whatSeedlingHeightDiam>"
      << "<tr_whatSaplingHeightDiam>";
  for (i = 0; i < iNumSpecies; i++)
    oOut << "<tr_wsahdVal species=\"Species_" << i << "\">0</tr_wsahdVal>";
  oOut << "</tr_whatSaplingHeightDiam>"
      << "<tr_whatAdultHeightDiam>";
  for (i = 0; i < iNumSpecies; i++)
    oOut << "<tr_wahdVal species=\"Species_" << i << "\">0</tr_wahdVal>";
  oOut << "</tr_whatAdultHeightDiam>"
      << "<tr_whatAdultCrownRadDiam>";
  for (i = 0; i < iNumSpecies; i++)
    oOut << "<tr_wacrdVal species=\"Species_" << i << "\">0</tr_wacrdVal>";
  oOut << "</tr_whatAdultCrownRadDiam>"
      << "<tr_whatAdultCrownHeightHeight>";
  for (i = 0; i < iNumSpecies; i++)
    oOut << "<tr_wachhVal species=\"Species_" << i << "\">0</tr_wachhVal>";
  oOut << "</tr_whatAdultCrownHeightHeight>"
      << "<tr_whatSaplingCrownRadDiam>";
  for (i = 0; i < iNumSpecies; i++)
    oOut << "<tr_wscrdVal species=\"Species_" << i << "\">0</tr_wscrdVal>";
  oOut << "</tr_whatSaplingCrownRadDiam>"
      << "<tr_whatSaplingCrownHeightHeight>";
  for (i = 0; i < iNumSpecies; i++)
    oOut << "<tr_wschhVal species=\"Species_" << i << "\">0</tr_wschhVal>";
  oOut << "</tr_whatSaplingCrownHeightHeight>"
      << "</allometry>";

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>StochDoubleLogTempDepNeighDisperse</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>";
  for (i = 0; i < iNumSpecies; i++)
    oOut << "<applyTo species=\"Species_" << i << "\" type=\"Adult\"/>";
  oOut << "</behavior>"
    << "<behavior>"
    << "<behaviorName>Establishment</behaviorName>"
    << "<version>1.0</version>"
    << "<listPosition>2</listPosition>";
  for (i = 0; i < iNumSpecies; i++)
    oOut << "<applyTo species=\"Species_" << i << "\" type=\"Seed\"/>";
  oOut << "</behavior>"
      << "</behaviorList>"
      << "<StochDoubleLogTempDepNeighDisperse1>"
      << "<di_stochDoubLogTempDepNeighPA>";
  for (i = 0; i < iNumSpecies; i++)
    oOut << "<di_sdltdnpaVal species=\"Species_" << i << "\">1</di_sdltdnpaVal>";
  oOut << "</di_stochDoubLogTempDepNeighPA>"
      << "<di_stochDoubLogTempDepNeighPB>";
  for (i = 0; i < iNumSpecies; i++)
    oOut << "<di_sdltdnpbVal species=\"Species_" << i << "\">20</di_sdltdnpbVal>";
  oOut << "</di_stochDoubLogTempDepNeighPB>"
      << "<di_stochDoubLogTempDepNeighPM>";
  for (i = 0; i < iNumSpecies; i++)
    oOut << "<di_sdltdnpmVal species=\"Species_" << i << "\">19</di_sdltdnpmVal>";
  oOut << "</di_stochDoubLogTempDepNeighPM>"
      << "<di_stochDoubLogTempDepNeighA>";
  for (i = 0; i < iNumSpecies; i++)
    oOut << "<di_sdltdnaVal species=\"Species_" << i << "\">3</di_sdltdnaVal>";
  oOut << "</di_stochDoubLogTempDepNeighA>"
      << "<di_stochDoubLogTempDepNeighB>";
  for (i = 0; i < iNumSpecies; i++)
    oOut << "<di_sdltdnbVal species=\"Species_" << i << "\">121</di_sdltdnbVal>";
  oOut << "</di_stochDoubLogTempDepNeighB>"
      << "<di_stochDoubLogTempDepNeighRadius>10</di_stochDoubLogTempDepNeighRadius>"
      << "<di_stochDoubLogTempDepNeighPlotSize>6</di_stochDoubLogTempDepNeighPlotSize>"
      << "<di_stochDoubLogTempDepNeighDeterministic>1</di_stochDoubLogTempDepNeighDeterministic>"
      << "<di_stochDoubLogTempDepNeighTempFec>0</di_stochDoubLogTempDepNeighTempFec>"
      << "<di_stochDoubLogTempDepNeighT>10</di_stochDoubLogTempDepNeighT>"
      << "</StochDoubleLogTempDepNeighDisperse1>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteXMLFile2()
/////////////////////////////////////////////////////////////////////////////
const char* WriteXMLFile2()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>4</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>100.0</plot_lenX>"
       << "<plot_lenY>100.0</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>"
       << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\"/>"
       << "<tr_species speciesName=\"Species_2\"/>"
       << "<tr_species speciesName=\"Species_3\"/>"
       << "<tr_species speciesName=\"Species_4\"/>"
       << "</tr_speciesList>"
       << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
       << "<tr_minAdultDBH>"
       << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_2\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_3\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_4\">10.0</tr_madVal>"
       << "</tr_minAdultDBH>"
       << "<tr_maxSeedlingHeight>"
       << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_2\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_3\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_4\">1.35</tr_mshVal>"
       << "</tr_maxSeedlingHeight>"
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
       << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_3\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_4\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">1</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">1</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_3\">1</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_4\">1</tr_cdtdVal>"
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
       << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_3\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_4\">1.0</tr_scheVal>"
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
       << "</allometry>";

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>StochDoubleLogTempDepNeighDisperse</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>Establishment</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_3\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<grid gridName=\"Dispersed Seeds\">"
       << "<ma_floatCodes>"
       << "<ma_floatCode label=\"seeds_0\">0</ma_floatCode>"
       << "<ma_floatCode label=\"seeds_1\">1</ma_floatCode>"
       << "<ma_floatCode label=\"seeds_2\">2</ma_floatCode>"
       << "<ma_floatCode label=\"seeds_3\">3</ma_floatCode>"
       << "</ma_floatCodes>"
       << "<ma_intCodes>"
       << "<ma_intCode label=\"count\">0</ma_intCode>"
       << "</ma_intCodes>"
       << "<ma_boolCodes>"
       << "<ma_boolCode label=\"Is Gap\">0</ma_boolCode>"
       << "</ma_boolCodes>"
       << "<ma_lengthXCells>2</ma_lengthXCells>"
       << "<ma_lengthYCells>2</ma_lengthYCells>"
       << "</grid>"
       << "<StochDoubleLogTempDepNeighDisperse1>"
       << "<di_stochDoubLogTempDepNeighPA>"
       << "<di_sdltdnpaVal species=\"Species_2\">500</di_sdltdnpaVal>"
       << "<di_sdltdnpaVal species=\"Species_3\">300</di_sdltdnpaVal>"
       << "<di_sdltdnpaVal species=\"Species_4\">3000</di_sdltdnpaVal>"
       << "</di_stochDoubLogTempDepNeighPA>"
       << "<di_stochDoubLogTempDepNeighPB>"
       << "<di_sdltdnpbVal species=\"Species_2\">12.15</di_sdltdnpbVal>"
       << "<di_sdltdnpbVal species=\"Species_3\">4.85</di_sdltdnpbVal>"
       << "<di_sdltdnpbVal species=\"Species_4\">4.09</di_sdltdnpbVal>"
       << "</di_stochDoubLogTempDepNeighPB>"
       << "<di_stochDoubLogTempDepNeighPM>"
       << "<di_sdltdnpmVal species=\"Species_2\">14.88</di_sdltdnpmVal>"
       << "<di_sdltdnpmVal species=\"Species_3\">18.87</di_sdltdnpmVal>"
       << "<di_sdltdnpmVal species=\"Species_4\">5</di_sdltdnpmVal>"
       << "</di_stochDoubLogTempDepNeighPM>"
       << "<di_stochDoubLogTempDepNeighA>"
       << "<di_sdltdnaVal species=\"Species_2\">3</di_sdltdnaVal>"
       << "<di_sdltdnaVal species=\"Species_3\">10</di_sdltdnaVal>"
       << "<di_sdltdnaVal species=\"Species_4\">5.4</di_sdltdnaVal>"
       << "</di_stochDoubLogTempDepNeighA>"
       << "<di_stochDoubLogTempDepNeighB>"
       << "<di_sdltdnbVal species=\"Species_2\">121</di_sdltdnbVal>"
       << "<di_sdltdnbVal species=\"Species_3\">55</di_sdltdnbVal>"
       << "<di_sdltdnbVal species=\"Species_4\">12</di_sdltdnbVal>"
       << "</di_stochDoubLogTempDepNeighB>"
       << "<di_stochDoubLogTempDepNeighAl>"
       << "<di_sdltdnalVal species=\"Species_2\">0.5</di_sdltdnalVal>"
       << "<di_sdltdnalVal species=\"Species_3\">0</di_sdltdnalVal>"
       << "<di_sdltdnalVal species=\"Species_4\">0.6</di_sdltdnalVal>"
       << "</di_stochDoubLogTempDepNeighAl>"
       << "<di_stochDoubLogTempDepNeighBl>"
       << "<di_sdltdnblVal species=\"Species_2\">293</di_sdltdnblVal>"
       << "<di_sdltdnblVal species=\"Species_3\">289</di_sdltdnblVal>"
       << "<di_sdltdnblVal species=\"Species_4\">300</di_sdltdnblVal>"
       << "</di_stochDoubLogTempDepNeighBl>"
       << "<di_stochDoubLogTempDepNeighCl>"
       << "<di_sdltdnclVal species=\"Species_2\">20</di_sdltdnclVal>"
       << "<di_sdltdnclVal species=\"Species_3\">275</di_sdltdnclVal>"
       << "<di_sdltdnclVal species=\"Species_4\">6.7</di_sdltdnclVal>"
       << "</di_stochDoubLogTempDepNeighCl>"
       << "<di_stochDoubLogTempDepNeighAh>"
       << "<di_sdltdnahVal species=\"Species_2\">0.4</di_sdltdnahVal>"
       << "<di_sdltdnahVal species=\"Species_3\">0</di_sdltdnahVal>"
       << "<di_sdltdnahVal species=\"Species_4\">0.1</di_sdltdnahVal>"
       << "</di_stochDoubLogTempDepNeighAh>"
       << "<di_stochDoubLogTempDepNeighBh>"
       << "<di_sdltdnbhVal species=\"Species_2\">303</di_sdltdnbhVal>"
       << "<di_sdltdnbhVal species=\"Species_3\">298</di_sdltdnbhVal>"
       << "<di_sdltdnbhVal species=\"Species_4\">330</di_sdltdnbhVal>"
       << "</di_stochDoubLogTempDepNeighBh>"
       << "<di_stochDoubLogTempDepNeighCh>"
       << "<di_sdltdnchVal species=\"Species_2\">20</di_sdltdnchVal>"
       << "<di_sdltdnchVal species=\"Species_3\">300</di_sdltdnchVal>"
       << "<di_sdltdnchVal species=\"Species_4\">9.67</di_sdltdnchVal>"
       << "</di_stochDoubLogTempDepNeighCh>"
       << "<di_stochDoubLogTempDepNeighRadius>10</di_stochDoubLogTempDepNeighRadius>"
       << "<di_stochDoubLogTempDepNeighPlotSize>4</di_stochDoubLogTempDepNeighPlotSize>"
       << "<di_stochDoubLogTempDepNeighDeterministic>0</di_stochDoubLogTempDepNeighDeterministic>"
       << "<di_stochDoubLogTempDepNeighTempFec>1</di_stochDoubLogTempDepNeighTempFec>"
       << "<di_stochDoubLogTempDepNeighT>10</di_stochDoubLogTempDepNeighT>"
       << "</StochDoubleLogTempDepNeighDisperse1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteXMLFile34()
/////////////////////////////////////////////////////////////////////////////
const char* WriteXMLFile34(int iYearsPerTimestep )
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>4</timesteps>"
       << "<yearsPerTimestep>" << iYearsPerTimestep << "</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>100.0</plot_lenX>"
       << "<plot_lenY>100.0</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>"
       << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\"/>"
       << "<tr_species speciesName=\"Species_2\"/>"
       << "<tr_species speciesName=\"Species_3\"/>"
       << "<tr_species speciesName=\"Species_4\"/>"
       << "</tr_speciesList>"
       << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
       << "<tr_minAdultDBH>"
       << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_2\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_3\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_4\">10.0</tr_madVal>"
       << "</tr_minAdultDBH>"
       << "<tr_maxSeedlingHeight>"
       << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_2\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_3\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_4\">1.35</tr_mshVal>"
       << "</tr_maxSeedlingHeight>"
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
       << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_3\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_4\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">1</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">1</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_3\">1</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_4\">1</tr_cdtdVal>"
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
       << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_3\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_4\">1.0</tr_scheVal>"
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
       << "</allometry>";

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>StochDoubleLogTempDepNeighDisperse</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>Establishment</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_3\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<StochDoubleLogTempDepNeighDisperse1>"
       << "<di_stochDoubLogTempDepNeighPA>"
       << "<di_sdltdnpaVal species=\"Species_2\">2</di_sdltdnpaVal>"
       << "<di_sdltdnpaVal species=\"Species_3\">3</di_sdltdnpaVal>"
       << "<di_sdltdnpaVal species=\"Species_4\">100000</di_sdltdnpaVal>"
       << "</di_stochDoubLogTempDepNeighPA>"
       << "<di_stochDoubLogTempDepNeighPB>"
       << "<di_sdltdnpbVal species=\"Species_2\">12.15</di_sdltdnpbVal>"
       << "<di_sdltdnpbVal species=\"Species_3\">4.85</di_sdltdnpbVal>"
       << "<di_sdltdnpbVal species=\"Species_4\">4.09</di_sdltdnpbVal>"
       << "</di_stochDoubLogTempDepNeighPB>"
       << "<di_stochDoubLogTempDepNeighPM>"
       << "<di_sdltdnpmVal species=\"Species_2\">14.88</di_sdltdnpmVal>"
       << "<di_sdltdnpmVal species=\"Species_3\">18.87</di_sdltdnpmVal>"
       << "<di_sdltdnpmVal species=\"Species_4\">5.27</di_sdltdnpmVal>"
       << "</di_stochDoubLogTempDepNeighPM>"
       << "<di_stochDoubLogTempDepNeighA>"
       << "<di_sdltdnaVal species=\"Species_2\">3</di_sdltdnaVal>"
       << "<di_sdltdnaVal species=\"Species_3\">2</di_sdltdnaVal>"
       << "<di_sdltdnaVal species=\"Species_4\">5.4</di_sdltdnaVal>"
       << "</di_stochDoubLogTempDepNeighA>"
       << "<di_stochDoubLogTempDepNeighB>"
       << "<di_sdltdnbVal species=\"Species_2\">121</di_sdltdnbVal>"
       << "<di_sdltdnbVal species=\"Species_3\">87.3</di_sdltdnbVal>"
       << "<di_sdltdnbVal species=\"Species_4\">141.1</di_sdltdnbVal>"
       << "</di_stochDoubLogTempDepNeighB>"
       << "<di_stochDoubLogTempDepNeighAl>"
       << "<di_sdltdnalVal species=\"Species_2\">0.5</di_sdltdnalVal>"
       << "<di_sdltdnalVal species=\"Species_3\">0</di_sdltdnalVal>"
       << "<di_sdltdnalVal species=\"Species_4\">0.6</di_sdltdnalVal>"
       << "</di_stochDoubLogTempDepNeighAl>"
       << "<di_stochDoubLogTempDepNeighBl>"
       << "<di_sdltdnblVal species=\"Species_2\">293</di_sdltdnblVal>"
       << "<di_sdltdnblVal species=\"Species_3\">289</di_sdltdnblVal>"
       << "<di_sdltdnblVal species=\"Species_4\">300</di_sdltdnblVal>"
       << "</di_stochDoubLogTempDepNeighBl>"
       << "<di_stochDoubLogTempDepNeighCl>"
       << "<di_sdltdnclVal species=\"Species_2\">20</di_sdltdnclVal>"
       << "<di_sdltdnclVal species=\"Species_3\">275</di_sdltdnclVal>"
       << "<di_sdltdnclVal species=\"Species_4\">6.7</di_sdltdnclVal>"
       << "</di_stochDoubLogTempDepNeighCl>"
       << "<di_stochDoubLogTempDepNeighAh>"
       << "<di_sdltdnahVal species=\"Species_2\">0.4</di_sdltdnahVal>"
       << "<di_sdltdnahVal species=\"Species_3\">0</di_sdltdnahVal>"
       << "<di_sdltdnahVal species=\"Species_4\">0.1</di_sdltdnahVal>"
       << "</di_stochDoubLogTempDepNeighAh>"
       << "<di_stochDoubLogTempDepNeighBh>"
       << "<di_sdltdnbhVal species=\"Species_2\">303</di_sdltdnbhVal>"
       << "<di_sdltdnbhVal species=\"Species_3\">298</di_sdltdnbhVal>"
       << "<di_sdltdnbhVal species=\"Species_4\">330</di_sdltdnbhVal>"
       << "</di_stochDoubLogTempDepNeighBh>"
       << "<di_stochDoubLogTempDepNeighCh>"
       << "<di_sdltdnchVal species=\"Species_2\">20</di_sdltdnchVal>"
       << "<di_sdltdnchVal species=\"Species_3\">300</di_sdltdnchVal>"
       << "<di_sdltdnchVal species=\"Species_4\">9.67</di_sdltdnchVal>"
       << "</di_stochDoubLogTempDepNeighCh>"
       << "<di_stochDoubLogTempDepNeighRadius>10</di_stochDoubLogTempDepNeighRadius>"
       << "<di_stochDoubLogTempDepNeighPlotSize>6</di_stochDoubLogTempDepNeighPlotSize>"
       << "<di_stochDoubLogTempDepNeighDeterministic>1</di_stochDoubLogTempDepNeighDeterministic>"
       << "<di_stochDoubLogTempDepNeighTempFec>1</di_stochDoubLogTempDepNeighTempFec>"
       << "<di_stochDoubLogTempDepNeighT>10</di_stochDoubLogTempDepNeighT>"
       << "</StochDoubleLogTempDepNeighDisperse1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}
