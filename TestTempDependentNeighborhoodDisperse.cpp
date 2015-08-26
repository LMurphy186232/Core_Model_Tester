//---------------------------------------------------------------------------
// TestTempDependentNeighborhoodDisperse.cpp
//---------------------------------------------------------------------------
#include "TestTempDependentNeighborhoodDisperse.h"
#include <gtest/gtest.h>
#include "SimManager.h"
#include "TreePopulation.h"
#include "Grid.h"
#include "BehaviorBase.h"
#include "Plot.h"
#include <math.h>
#include <fstream>

/////////////////////////////////////////////////////////////////////////////
// TestTempDependentNeighborhoodDisperse1()
// Tests dispersal, run 1. It will cause a parameter file to be written and then
// passed to a clSimManager object. That object will read it. Then the dispersal
// behavior is run. The number of seedlings per grid cell is compared with
// expected values.
/////////////////////////////////////////////////////////////////////////////
TEST(TempDependentNeighborhoodDisperse, TestTempDependentNeighborhoodDisperse1) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {

    //Feed our file to the sim manager
    p_oSimManager->ReadFile(WriteTempDependentNeighborhoodDisperseXMLFile(1));

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
    fExpectedSeeds2 = 192;
    fExpectedSeeds3 = 128;
    fExpectedSeeds4 = 345.6;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds2), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds3), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 5; iCellY = 6;
    fExpectedSeeds2 = 510.7872318;
    fExpectedSeeds3 = 2761.041514;
    fExpectedSeeds4 = 345.6;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds2), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds3), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 6; iCellY = 5;
    fExpectedSeeds2 = 226.7896979;
    fExpectedSeeds3 = 226.722603;
    fExpectedSeeds4 = 756.7096952;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds2), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds3), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 5; iCellY = 5;
    fExpectedSeeds2 = 226.7896979;
    fExpectedSeeds3 = 128;
    fExpectedSeeds4 = 345.6;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds2), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds3), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 6; iCellY = 6;
    fExpectedSeeds2 = 510.7872318;
    fExpectedSeeds3 = 1411.832606;
    fExpectedSeeds4 = 756.7096952;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds2), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds3), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 7; iCellY = 6;
    fExpectedSeeds2 = 192;
    fExpectedSeeds3 = 1411.832606;
    fExpectedSeeds4 = 904.7091855;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds2), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds3), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 6; iCellY = 7;
    fExpectedSeeds2 = 475.9975339;
    fExpectedSeeds3 = 3946.151517;
    fExpectedSeeds4 = 493.5994903;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds2), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds3), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 12; iCellY = 12;
    fExpectedSeeds2 = 48;
    fExpectedSeeds3 = 32;
    fExpectedSeeds4 = 86.4;
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
    fExpectedSeeds2 = 192;
    fExpectedSeeds3 = 128;
    fExpectedSeeds4 = 345.6;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds2), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds3), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 5; iCellY = 6;
    fExpectedSeeds2 = 249.0549525;
    fExpectedSeeds3 = 2759.655538;
    fExpectedSeeds4 = 345.6;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds2), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds3), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 6; iCellY = 5;
    fExpectedSeeds2 = 198.226487;
    fExpectedSeeds3 = 226.6706376;
    fExpectedSeeds4 = 587.6631747;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds2), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds3), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 5; iCellY = 5;
    fExpectedSeeds2 = 198.226487;
    fExpectedSeeds3 = 128;
    fExpectedSeeds4 = 345.6;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds2), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds3), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 6; iCellY = 6;
    fExpectedSeeds2 = 249.0549525;
    fExpectedSeeds3 = 1411.156824;
    fExpectedSeeds4 = 587.6631747;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds2), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds3), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 7; iCellY = 6;
    fExpectedSeeds2 = 192;
    fExpectedSeeds3 = 1411.156824;
    fExpectedSeeds4 = 674.8059176;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds2), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds3), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 6; iCellY = 7;
    fExpectedSeeds2 = 242.8284655;
    fExpectedSeeds3 = 3944.141724;
    fExpectedSeeds4 = 432.7427429;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds2), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds3), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 12; iCellY = 12;
    fExpectedSeeds2 = 48;
    fExpectedSeeds3 = 32;
    fExpectedSeeds4 = 86.4;
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
// TestTempDependentNeighborhoodDisperse2()
/////////////////////////////////////////////////////////////////////////////
TEST(TempDependentNeighborhoodDisperse, TestTempDependentNeighborhoodDisperse2)
{
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    //Feed our file to the sim manager
    p_oSimManager->ReadFile(WriteTempDependentNeighborhoodDisperseXMLFile(3));

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
    fExpectedSeeds2 = 576;
    fExpectedSeeds3 = 384;
    fExpectedSeeds4 = 1036.8;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds2), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds3), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 5; iCellY = 6;
    fExpectedSeeds2 = 1532.361695;
    fExpectedSeeds3 = 8283.124542;
    fExpectedSeeds4 = 1036.8;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds2), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds3), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 6; iCellY = 5;
    fExpectedSeeds2 = 680.3690937;
    fExpectedSeeds3 = 680.167809;
    fExpectedSeeds4 = 2270.129086;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds2), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds3), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 5; iCellY = 5;
    fExpectedSeeds2 = 680.3690937;
    fExpectedSeeds3 = 384;
    fExpectedSeeds4 = 1036.8;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds2), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds3), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 6; iCellY = 6;
    fExpectedSeeds2 = 1532.361695;
    fExpectedSeeds3 = 4235.497819;
    fExpectedSeeds4 = 2270.129086;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds2), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds3), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 7; iCellY = 6;
    fExpectedSeeds2 = 576;
    fExpectedSeeds3 = 4235.497819;
    fExpectedSeeds4 = 2714.127557;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds2), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds3), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 6; iCellY = 7;
    fExpectedSeeds2 = 1427.992602;
    fExpectedSeeds3 = 11838.45455;
    fExpectedSeeds4 = 1480.798471;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds2), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds3), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 12; iCellY = 12;
    fExpectedSeeds2 = 144;
    fExpectedSeeds3 = 96;
    fExpectedSeeds4 = 259.2;
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
// TestTempDependentNeighborhoodDisperse3()
/////////////////////////////////////////////////////////////////////////////
TEST(TempDependentNeighborhoodDisperse, TestTempDependentNeighborhoodDisperse3) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    //Feed our file to the sim manager
    p_oSimManager->ReadFile(WriteTempDependentNeighborhoodDisperseXMLFile3());

    clTreePopulation *p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject("treepopulation");
    clGrid *p_oSeedGrid;
    float fDiam, fExpectedSeeds1, fExpectedSeeds2, fExpectedSeeds3,
    fExpectedSeeds4, fSeeds;
    int iSpecies, i, iCellX, iCellY;

    //Create all neighbors
    fDiam = 10.5;
    iSpecies = 3;
    p_oPop->CreateTree(50, 50, iSpecies, clTreePopulation::adult, fDiam);

    fDiam = 15;
    p_oPop->CreateTree(53, 52, iSpecies, clTreePopulation::adult, fDiam);

    fDiam = 26;
    p_oPop->CreateTree(55, 60, iSpecies, clTreePopulation::adult, fDiam);

    fDiam = 25;
    p_oPop->CreateTree(59, 50, iSpecies, clTreePopulation::adult, fDiam);

    fDiam = 30;
    p_oPop->CreateTree(50, 59, iSpecies, clTreePopulation::adult, fDiam);

    fDiam = 45;
    p_oPop->CreateTree(55, 55, iSpecies, clTreePopulation::adult, fDiam);

    fDiam = 15;
    p_oPop->CreateTree(60, 61, iSpecies, clTreePopulation::adult, fDiam);

    fDiam = 76;
    p_oPop->CreateTree(44, 60, iSpecies, clTreePopulation::adult, fDiam);


    //Now create all the neighbors that are too small or dead to compete
    fDiam = 4;
    p_oPop->CreateTree(52, 52, iSpecies, clTreePopulation::sapling, fDiam);
    fDiam = 4;
    p_oPop->CreateTree(53, 53, iSpecies, clTreePopulation::sapling, fDiam);
    p_oPop->CreateTree(56, 56, iSpecies, clTreePopulation::snag, 30);
    p_oPop->CreateTree(56, 56, iSpecies, clTreePopulation::seedling, 0.2);

    //Run one timestep - can't just use RunSim() because TimestepCleanup will
    //erase the results we want to check
    for (i = 0; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
      clBehaviorBase *p_oBase = p_oSimManager->GetBehaviorObject(i);
      p_oBase->Action();
    }

    p_oSeedGrid = p_oSimManager->GetGridObject("Dispersed Seeds");

    //Check the seed counts
    iCellX = 2; iCellY = 2;
    fExpectedSeeds1 = 0;
    fExpectedSeeds2 = 192;
    fExpectedSeeds3 = 0;
    fExpectedSeeds4 = 345.6;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_0"), &fSeeds);
    EXPECT_EQ(fSeeds, fExpectedSeeds1);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_EQ(fSeeds, fExpectedSeeds2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_EQ(fSeeds, fExpectedSeeds3);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 5; iCellY = 6;
    fExpectedSeeds1 = 0;
    fExpectedSeeds2 = 192;
    fExpectedSeeds3 = 0;
    fExpectedSeeds4 = 4957.42;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_0"), &fSeeds);
    EXPECT_EQ(fSeeds, fExpectedSeeds1);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_EQ(fSeeds, fExpectedSeeds2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_EQ(fSeeds, fExpectedSeeds3);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 6; iCellY = 5;
    fExpectedSeeds1 = 0;
    fExpectedSeeds2 = 192;
    fExpectedSeeds3 = 0;
    fExpectedSeeds4 = 977.22;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_0"), &fSeeds);
    EXPECT_EQ(fSeeds, fExpectedSeeds1);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_EQ(fSeeds, fExpectedSeeds2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_EQ(fSeeds, fExpectedSeeds3);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 5; iCellY = 5;
    fExpectedSeeds1 = 0;
    fExpectedSeeds2 = 192;
    fExpectedSeeds3 = 0;
    fExpectedSeeds4 = 418.11;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_0"), &fSeeds);
    EXPECT_EQ(fSeeds, fExpectedSeeds1);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_EQ(fSeeds, fExpectedSeeds2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_EQ(fSeeds, fExpectedSeeds3);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 6; iCellY = 6;
    fExpectedSeeds1 = 0;
    fExpectedSeeds2 = 192;
    fExpectedSeeds3 = 0;
    fExpectedSeeds4 = 3345.87;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_0"), &fSeeds);
    EXPECT_EQ(fSeeds, fExpectedSeeds1);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_EQ(fSeeds, fExpectedSeeds2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_EQ(fSeeds, fExpectedSeeds3);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 7; iCellY = 6;
    fExpectedSeeds1 = 0;
    fExpectedSeeds2 = 192;
    fExpectedSeeds3 = 0;
    fExpectedSeeds4 = 2829.36;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_0"), &fSeeds);
    EXPECT_EQ(fSeeds, fExpectedSeeds1);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_EQ(fSeeds, fExpectedSeeds2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_EQ(fSeeds, fExpectedSeeds3);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 6; iCellY = 7;
    fExpectedSeeds1 = 0;
    fExpectedSeeds2 = 192;
    fExpectedSeeds3 = 0;
    fExpectedSeeds4 = 6809.55;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_0"), &fSeeds);
    EXPECT_EQ(fSeeds, fExpectedSeeds1);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_EQ(fSeeds, fExpectedSeeds2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_EQ(fSeeds, fExpectedSeeds3);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 12; iCellY = 12;
    fExpectedSeeds1 = 0;
    fExpectedSeeds2 = 48;
    fExpectedSeeds3 = 0;
    fExpectedSeeds4 = 86.4;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_0"), &fSeeds);
    EXPECT_EQ(fSeeds, fExpectedSeeds1);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_EQ(fSeeds, fExpectedSeeds2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_EQ(fSeeds, fExpectedSeeds3);
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
    fExpectedSeeds1 = 0;
    fExpectedSeeds2 = 0;
    fExpectedSeeds3 = 128;
    fExpectedSeeds4 = 345.6;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_EQ(fSeeds, fExpectedSeeds2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_EQ(fSeeds, fExpectedSeeds3);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 5; iCellY = 6;
    fExpectedSeeds1 = 0;
    fExpectedSeeds2 = 0;
    fExpectedSeeds3 = 128;
    fExpectedSeeds4 = 3061.06;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_EQ(fSeeds, fExpectedSeeds2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_EQ(fSeeds, fExpectedSeeds3);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 6; iCellY = 5;
    fExpectedSeeds1 = 0;
    fExpectedSeeds2 = 0;
    fExpectedSeeds3 = 128;
    fExpectedSeeds4 = 717.50;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_EQ(fSeeds, fExpectedSeeds2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_EQ(fSeeds, fExpectedSeeds3);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 5; iCellY = 5;
    fExpectedSeeds1 = 0;
    fExpectedSeeds2 = 0;
    fExpectedSeeds3 = 128;
    fExpectedSeeds4 = 388.29;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_EQ(fSeeds, fExpectedSeeds2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_EQ(fSeeds, fExpectedSeeds3);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 6; iCellY = 6;
    fExpectedSeeds1 = 0;
    fExpectedSeeds2 = 0;
    fExpectedSeeds3 = 128;
    fExpectedSeeds4 = 2112.17;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_EQ(fSeeds, fExpectedSeeds2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_EQ(fSeeds, fExpectedSeeds3);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 7; iCellY = 6;
    fExpectedSeeds1 = 0;
    fExpectedSeeds2 = 0;
    fExpectedSeeds3 = 128;
    fExpectedSeeds4 = 1808.04;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_EQ(fSeeds, fExpectedSeeds2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_EQ(fSeeds, fExpectedSeeds3);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 6; iCellY = 7;
    fExpectedSeeds1 = 0;
    fExpectedSeeds2 = 0;
    fExpectedSeeds3 = 128;
    fExpectedSeeds4 = 4151.60;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_EQ(fSeeds, fExpectedSeeds2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_EQ(fSeeds, fExpectedSeeds3);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 12; iCellY = 12;
    fExpectedSeeds1 = 0;
    fExpectedSeeds2 = 0;
    fExpectedSeeds3 = 32;
    fExpectedSeeds4 = 86.4;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_EQ(fSeeds, fExpectedSeeds2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_EQ(fSeeds, fExpectedSeeds3);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestTempDependentNeighborhoodDisperse4()
/////////////////////////////////////////////////////////////////////////////
TEST(TempDependentNeighborhoodDisperse, TestTempDependentNeighborhoodDisperse4) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    //Feed our file to the sim manager
    p_oSimManager->ReadFile(WriteTempDependentNeighborhoodDisperseXMLFile4());

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
    fExpectedSeeds2 = 192;
    fExpectedSeeds3 = 128;
    fExpectedSeeds4 = 345.6;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds2), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds3), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 5; iCellY = 6;
    fExpectedSeeds2 = 510.7872318;
    fExpectedSeeds3 = 2761.041514;
    fExpectedSeeds4 = 345.6;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds2), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds3), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 6; iCellY = 5;
    fExpectedSeeds2 = 226.7896979;
    fExpectedSeeds3 = 226.722603;
    fExpectedSeeds4 = 756.7096952;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds2), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds3), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 5; iCellY = 5;
    fExpectedSeeds2 = 226.7896979;
    fExpectedSeeds3 = 128;
    fExpectedSeeds4 = 345.6;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds2), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds3), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 6; iCellY = 6;
    fExpectedSeeds2 = 510.7872318;
    fExpectedSeeds3 = 1411.832606;
    fExpectedSeeds4 = 756.7096952;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds2), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds3), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 7; iCellY = 6;
    fExpectedSeeds2 = 192;
    fExpectedSeeds3 = 1411.832606;
    fExpectedSeeds4 = 904.7091855;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds2), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds3), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 6; iCellY = 7;
    fExpectedSeeds2 = 475.9975339;
    fExpectedSeeds3 = 3946.151517;
    fExpectedSeeds4 = 493.5994903;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds2), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds3), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 12; iCellY = 12;
    fExpectedSeeds2 = 48;
    fExpectedSeeds3 = 32;
    fExpectedSeeds4 = 86.4;
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
    fExpectedSeeds2 = 192;
    fExpectedSeeds3 = 128;
    fExpectedSeeds4 = 345.6;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds2), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds3), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 5; iCellY = 6;
    fExpectedSeeds2 = 249.0549525;
    fExpectedSeeds3 = 2759.655538;
    fExpectedSeeds4 = 345.6;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds2), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds3), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 6; iCellY = 5;
    fExpectedSeeds2 = 198.226487;
    fExpectedSeeds3 = 226.6706376;
    fExpectedSeeds4 = 587.6631747;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds2), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds3), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 5; iCellY = 5;
    fExpectedSeeds2 = 198.226487;
    fExpectedSeeds3 = 128;
    fExpectedSeeds4 = 345.6;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds2), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds3), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 6; iCellY = 6;
    fExpectedSeeds2 = 249.0549525;
    fExpectedSeeds3 = 1411.156824;
    fExpectedSeeds4 = 587.6631747;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds2), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds3), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 7; iCellY = 6;
    fExpectedSeeds2 = 192;
    fExpectedSeeds3 = 1411.156824;
    fExpectedSeeds4 = 674.8059176;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds2), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds3), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 6; iCellY = 7;
    fExpectedSeeds2 = 242.8284655;
    fExpectedSeeds3 = 3944.141724;
    fExpectedSeeds4 = 432.7427429;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds2), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds3), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 12; iCellY = 12;
    fExpectedSeeds2 = 48;
    fExpectedSeeds3 = 32;
    fExpectedSeeds4 = 86.4;
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
// WriteTempDependentNeighborhoodDisperseXMLFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteTempDependentNeighborhoodDisperseXMLFile(int iYearsPerTimestep )
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
       << "<tr_stdMaxCrownRad>"
       << "<tr_smcrVal species=\"Species_1\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_2\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_3\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_4\">10</tr_smcrVal>"
       << "</tr_stdMaxCrownRad>"
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
       << "<behaviorName>TemperatureDependentNeighborhoodDisperse</behaviorName>"
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
       << "<TemperatureDependentNeighborhoodDisperse1>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_1\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_2\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_3\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_4\">15.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "<di_tempDepNeighFecM>"
       << "<di_tdnfmVal species=\"Species_2\">5</di_tdnfmVal>"
       << "<di_tdnfmVal species=\"Species_3\">15</di_tdnfmVal>"
       << "<di_tdnfmVal species=\"Species_4\">9</di_tdnfmVal>"
       << "</di_tempDepNeighFecM>"
       << "<di_tempDepNeighFecN>"
       << "<di_tdnfnVal species=\"Species_2\">6.88</di_tdnfnVal>"
       << "<di_tdnfnVal species=\"Species_3\">139.57</di_tdnfnVal>"
       << "<di_tdnfnVal species=\"Species_4\">10</di_tdnfnVal>"
       << "</di_tempDepNeighFecN>"
       << "<di_tempDepNeighA>"
       << "<di_tdnaVal species=\"Species_2\">3</di_tdnaVal>"
       << "<di_tdnaVal species=\"Species_3\">2</di_tdnaVal>"
       << "<di_tdnaVal species=\"Species_4\">5.4</di_tdnaVal>"
       << "</di_tempDepNeighA>"
       << "<di_tempDepNeighB>"
       << "<di_tdnbVal species=\"Species_2\">121</di_tdnbVal>"
       << "<di_tdnbVal species=\"Species_3\">87.3</di_tdnbVal>"
       << "<di_tdnbVal species=\"Species_4\">141.1</di_tdnbVal>"
       << "</di_tempDepNeighB>"
       << "<di_tempDepNeighPresM>"
       << "<di_tdnpmVal species=\"Species_2\">14.88</di_tdnpmVal>"
       << "<di_tdnpmVal species=\"Species_3\">18.87</di_tdnpmVal>"
       << "<di_tdnpmVal species=\"Species_4\">-5.27</di_tdnpmVal>"
       << "</di_tempDepNeighPresM>"
       << "<di_tempDepNeighPresB>"
       << "<di_tdnpbVal species=\"Species_2\">12.15</di_tdnpbVal>"
       << "<di_tdnpbVal species=\"Species_3\">4.85</di_tdnpbVal>"
       << "<di_tdnpbVal species=\"Species_4\">4.09</di_tdnpbVal>"
       << "</di_tempDepNeighPresB>"
       << "<di_tempDepNeighPresThreshold>"
       << "<di_tdnptVal species=\"Species_2\">0.8</di_tdnptVal>"
       << "<di_tdnptVal species=\"Species_3\">0.3</di_tdnptVal>"
       << "<di_tdnptVal species=\"Species_4\">0</di_tdnptVal>"
       << "</di_tempDepNeighPresThreshold>"
       << "<di_tempDepNeighRadius>10</di_tempDepNeighRadius>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</TemperatureDependentNeighborhoodDisperse1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteTempDependentNeighborhoodDisperseXMLFile3()
/////////////////////////////////////////////////////////////////////////////
const char* WriteTempDependentNeighborhoodDisperseXMLFile3()
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
       << "<tr_stdMaxCrownRad>"
       << "<tr_smcrVal species=\"Species_1\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_2\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_3\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_4\">10</tr_smcrVal>"
       << "</tr_stdMaxCrownRad>"
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
       << "<behaviorName>TemperatureDependentNeighborhoodDisperse</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>Establishment</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_3\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<TemperatureDependentNeighborhoodDisperse1>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_1\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_2\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_3\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_4\">15.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "<di_tempDepNeighFecM>"
       << "<di_tdnfmVal species=\"Species_1\">5</di_tdnfmVal>"
       << "<di_tdnfmVal species=\"Species_2\">5</di_tdnfmVal>"
       << "<di_tdnfmVal species=\"Species_3\">15</di_tdnfmVal>"
       << "<di_tdnfmVal species=\"Species_4\">9</di_tdnfmVal>"
       << "</di_tempDepNeighFecM>"
       << "<di_tempDepNeighFecN>"
       << "<di_tdnfnVal species=\"Species_1\">6.88</di_tdnfnVal>"
       << "<di_tdnfnVal species=\"Species_2\">6.88</di_tdnfnVal>"
       << "<di_tdnfnVal species=\"Species_3\">139.57</di_tdnfnVal>"
       << "<di_tdnfnVal species=\"Species_4\">10</di_tdnfnVal>"
       << "</di_tempDepNeighFecN>"
       << "<di_tempDepNeighA>"
       << "<di_tdnaVal species=\"Species_1\">3</di_tdnaVal>"
       << "<di_tdnaVal species=\"Species_2\">3</di_tdnaVal>"
       << "<di_tdnaVal species=\"Species_3\">2</di_tdnaVal>"
       << "<di_tdnaVal species=\"Species_4\">5.4</di_tdnaVal>"
       << "</di_tempDepNeighA>"
       << "<di_tempDepNeighB>"
       << "<di_tdnbVal species=\"Species_1\">121</di_tdnbVal>"
       << "<di_tdnbVal species=\"Species_2\">121</di_tdnbVal>"
       << "<di_tdnbVal species=\"Species_3\">87.3</di_tdnbVal>"
       << "<di_tdnbVal species=\"Species_4\">141.1</di_tdnbVal>"
       << "</di_tempDepNeighB>"
       << "<di_tempDepNeighPresM>"
       << "<di_tdnpmVal species=\"Species_1\">16</di_tdnpmVal>"
       << "<di_tdnpmVal species=\"Species_2\">14.88</di_tdnpmVal>"
       << "<di_tdnpmVal species=\"Species_3\">18.87</di_tdnpmVal>"
       << "<di_tdnpmVal species=\"Species_4\">15.27</di_tdnpmVal>"
       << "</di_tempDepNeighPresM>"
       << "<di_tempDepNeighPresB>"
       << "<di_tdnpbVal species=\"Species_1\">8</di_tdnpbVal>"
       << "<di_tdnpbVal species=\"Species_2\">12.15</di_tdnpbVal>"
       << "<di_tdnpbVal species=\"Species_3\">4.85</di_tdnpbVal>"
       << "<di_tdnpbVal species=\"Species_4\">4.09</di_tdnpbVal>"
       << "</di_tempDepNeighPresB>"
       << "<di_tempDepNeighPresThreshold>"
       << "<di_tdnptVal species=\"Species_1\">1</di_tdnptVal>"
       << "<di_tdnptVal species=\"Species_2\">0.975</di_tdnptVal>"
       << "<di_tdnptVal species=\"Species_3\">0.5</di_tdnptVal>"
       << "<di_tdnptVal species=\"Species_4\">0.9</di_tdnptVal>"
       << "</di_tempDepNeighPresThreshold>"
       << "<di_tempDepNeighRadius>10</di_tempDepNeighRadius>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</TemperatureDependentNeighborhoodDisperse1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteTempDependentNeighborhoodDisperseXMLFile4()
/////////////////////////////////////////////////////////////////////////////
const char* WriteTempDependentNeighborhoodDisperseXMLFile4() {
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
       << "<tr_stdMaxCrownRad>"
       << "<tr_smcrVal species=\"Species_1\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_2\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_3\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_4\">10</tr_smcrVal>"
       << "</tr_stdMaxCrownRad>"
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
       << "<behaviorName>TemperatureDependentNeighborhoodDisperse</behaviorName>"
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
       << "<TemperatureDependentNeighborhoodDisperse1>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_1\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_2\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_3\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_4\">15.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "<di_tempDepNeighFecM>"
       << "<di_tdnfmVal species=\"Species_2\">5</di_tdnfmVal>"
       << "<di_tdnfmVal species=\"Species_3\">15</di_tdnfmVal>"
       << "<di_tdnfmVal species=\"Species_4\">9</di_tdnfmVal>"
       << "</di_tempDepNeighFecM>"
       << "<di_tempDepNeighFecN>"
       << "<di_tdnfnVal species=\"Species_2\">6.88</di_tdnfnVal>"
       << "<di_tdnfnVal species=\"Species_3\">139.57</di_tdnfnVal>"
       << "<di_tdnfnVal species=\"Species_4\">10</di_tdnfnVal>"
       << "</di_tempDepNeighFecN>"
       << "<di_tempDepNeighA>"
       << "<di_tdnaVal species=\"Species_2\">3</di_tdnaVal>"
       << "<di_tdnaVal species=\"Species_3\">2</di_tdnaVal>"
       << "<di_tdnaVal species=\"Species_4\">5.4</di_tdnaVal>"
       << "</di_tempDepNeighA>"
       << "<di_tempDepNeighB>"
       << "<di_tdnbVal species=\"Species_2\">121</di_tdnbVal>"
       << "<di_tdnbVal species=\"Species_3\">87.3</di_tdnbVal>"
       << "<di_tdnbVal species=\"Species_4\">141.1</di_tdnbVal>"
       << "</di_tempDepNeighB>"
       << "<di_tempDepNeighPresM>"
       << "<di_tdnpmVal species=\"Species_2\">14.88</di_tdnpmVal>"
       << "<di_tdnpmVal species=\"Species_3\">18.87</di_tdnpmVal>"
       << "<di_tdnpmVal species=\"Species_4\">-5.27</di_tdnpmVal>"
       << "</di_tempDepNeighPresM>"
       << "<di_tempDepNeighPresB>"
       << "<di_tdnpbVal species=\"Species_2\">12.15</di_tdnpbVal>"
       << "<di_tdnpbVal species=\"Species_3\">4.85</di_tdnpbVal>"
       << "<di_tdnpbVal species=\"Species_4\">4.09</di_tdnpbVal>"
       << "</di_tempDepNeighPresB>"
       << "<di_tempDepNeighPresThreshold>"
       << "<di_tdnptVal species=\"Species_2\">0</di_tdnptVal>"
       << "<di_tdnptVal species=\"Species_3\">0</di_tdnptVal>"
       << "<di_tdnptVal species=\"Species_4\">0</di_tdnptVal>"
       << "</di_tempDepNeighPresThreshold>"
       << "<di_tempDepNeighRadius>10</di_tempDepNeighRadius>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</TemperatureDependentNeighborhoodDisperse1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}
