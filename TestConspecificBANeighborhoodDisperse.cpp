//---------------------------------------------------------------------------
// TestConspecificBANeighborhoodDisperse.cpp
//---------------------------------------------------------------------------
#include "TestConspecificBANeighborhoodDisperse.h"
#include <gtest/gtest.h>
#include "SimManager.h"
#include "TreePopulation.h"
#include "Grid.h"
#include "BehaviorBase.h"
#include "Plot.h"
#include <math.h>
#include <fstream>

/////////////////////////////////////////////////////////////////////////////
// TestConspecificBANeighborhoodDisperse1()
// Tests dispersal, run 1. It will cause a parameter file to be written and then
// passed to a clSimManager object. That object will read it. Then the dispersal
// behavior is run. The number of seedlings per grid cell is compared with
// expected values.
/////////////////////////////////////////////////////////////////////////////
TEST(ConspecificBANeighborhoodDisperse, TestConspecificBANeighborhoodDisperse1) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {

    //Feed our file to the sim manager
    p_oSimManager->ReadFile(WriteConspecificBANeighborhoodDisperseXMLFile(1));

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
    fExpectedSeeds2 = 806.4465142;
    fExpectedSeeds3 = 2761.041514;
    fExpectedSeeds4 = 345.6;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds2), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds3), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 6; iCellY = 5;
    fExpectedSeeds2 = 259.0554102;
    fExpectedSeeds3 = 226.7339739;
    fExpectedSeeds4 = 788.8787234;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds2), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds3), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 5; iCellY = 5;
    fExpectedSeeds2 = 259.0554102;
    fExpectedSeeds3 = 128;
    fExpectedSeeds4 = 345.6;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds2), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds3), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 6; iCellY = 6;
    fExpectedSeeds2 = 806.4465142;
    fExpectedSeeds3 = 1411.832606;
    fExpectedSeeds4 = 788.8787234;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds2), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds3), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 7; iCellY = 6;
    fExpectedSeeds2 = 192;
    fExpectedSeeds3 = 1411.832606;
    fExpectedSeeds4 = 948.4590639;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds2), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds3), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 6; iCellY = 7;
    fExpectedSeeds2 = 739.391104;
    fExpectedSeeds3 = 3946.151517;
    fExpectedSeeds4 = 505.1803404;
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
// TestConspecificBANeighborhoodDisperse2()
/////////////////////////////////////////////////////////////////////////////
TEST(ConspecificBANeighborhoodDisperse, TestConspecificBANeighborhoodDisperse2)
{
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    //Feed our file to the sim manager
    p_oSimManager->ReadFile(WriteConspecificBANeighborhoodDisperseXMLFile(3));

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
    fExpectedSeeds2 = 2419.339543;
    fExpectedSeeds3 = 8284.034366;
    fExpectedSeeds4 = 1036.8;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds2), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds3), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 6; iCellY = 5;
    fExpectedSeeds2 = 777.1662307;
    fExpectedSeeds3 = 680.167809;
    fExpectedSeeds4 = 2366.63617;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds2), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds3), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 5; iCellY = 5;
    fExpectedSeeds2 = 777.1662307;
    fExpectedSeeds3 = 384;
    fExpectedSeeds4 = 1036.8;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds2), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds3), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 6; iCellY = 6;
    fExpectedSeeds2 = 2419.339543;
    fExpectedSeeds3 = 4235.497819;
    fExpectedSeeds4 = 2366.63617;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds2), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds3), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 7; iCellY = 6;
    fExpectedSeeds2 = 576;
    fExpectedSeeds3 = 4235.497819;
    fExpectedSeeds4 = 2845.377192;
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_1"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds2), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_2"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds3), 2);
    p_oSeedGrid->GetValueOfCell(iCellX, iCellY, p_oSeedGrid->GetFloatDataCode("seeds_3"), &fSeeds);
    EXPECT_LT(fabs(fSeeds - fExpectedSeeds4), 2);

    iCellX = 6; iCellY = 7;
    fExpectedSeeds2 = 2218.173312;
    fExpectedSeeds3 = 11839.77388;
    fExpectedSeeds4 = 1515.541021;
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
// WriteConspecificBANeighborhoodDisperseXMLFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteConspecificBANeighborhoodDisperseXMLFile(int iYearsPerTimestep )
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
       << "<behaviorName>ConspecificBANeighborhoodDisperse</behaviorName>"
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
       << "<ConspecificBANeighborhoodDisperse1>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_1\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_2\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_3\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_4\">15.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "<di_conspBANeighA>"
       << "<di_cbnaVal species=\"Species_2\">3</di_cbnaVal>"
       << "<di_cbnaVal species=\"Species_3\">2</di_cbnaVal>"
       << "<di_cbnaVal species=\"Species_4\">5.4</di_cbnaVal>"
       << "</di_conspBANeighA>"
       << "<di_conspBANeighB>"
       << "<di_cbnbVal species=\"Species_2\">121</di_cbnbVal>"
       << "<di_cbnbVal species=\"Species_3\">87.3</di_cbnbVal>"
       << "<di_cbnbVal species=\"Species_4\">141.1</di_cbnbVal>"
       << "</di_conspBANeighB>"
       << "<di_tempDepNeighRadius>10</di_tempDepNeighRadius>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</ConspecificBANeighborhoodDisperse1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}
