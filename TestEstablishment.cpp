//---------------------------------------------------------------------------
// TestEstablishment.cpp
//---------------------------------------------------------------------------
#include "TestEstablishment.h"
#include <gtest/gtest.h>
#include "Grid.h"
#include "SimManager.h"
#include "TreePopulation.h"
#include <stdio.h>
#include <fstream>
#include <math.h>

/////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun1()
// Tests establishment. WriteEstablishmentXMLFile1() does setup. Non-spatial
// dispserse is included with parameters such that it creates no seeds. The
// "Dispersed Seeds" grid cells do not divide evenly into the plot lengths. The
// grid is populated with some initial values. Then one timestep of a simulation
// is run and this verifies that the number of seedlings is right, and the
// number of seeds is 0.
/////////////////////////////////////////////////////////////////////////////
TEST(Establishment, TestNormalProcessingRun1) {

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    //Feed our file to the sim manager
    p_oSimManager->ReadFile(WriteEstablishmentXMLFile1());

    //Add seeds to the Dispersed Seeds grid
    clGrid *p_oSeeds = p_oSimManager->GetGridObject("Dispersed Seeds");
    float fValue;
    int iNumXCells = p_oSeeds->GetNumberXCells(),
        iNumYCells = p_oSeeds->GetNumberYCells(),
        iX, iY;

    //Cell 2, 4
    fValue = 1;
    p_oSeeds->SetValueOfCell(2, 4, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
    fValue = 10;
    p_oSeeds->SetValueOfCell(2, 4, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
    fValue = 100;
    p_oSeeds->SetValueOfCell(2, 4, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);
    fValue = 1000;
    p_oSeeds->SetValueOfCell(2, 4, p_oSeeds->GetFloatDataCode("seeds_4"), fValue);
    fValue = 10000;
    p_oSeeds->SetValueOfCell(2, 4, p_oSeeds->GetFloatDataCode("seeds_5"), fValue);

    //Cell 3, 5
    fValue = 25;
    p_oSeeds->SetValueOfCell(3, 5, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
    fValue = 0;
    p_oSeeds->SetValueOfCell(3, 5, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
    fValue = 469;
    p_oSeeds->SetValueOfCell(3, 5, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);
    fValue = 331;
    p_oSeeds->SetValueOfCell(3, 5, p_oSeeds->GetFloatDataCode("seeds_4"), fValue);
    fValue = 0;
    p_oSeeds->SetValueOfCell(3, 5, p_oSeeds->GetFloatDataCode("seeds_5"), fValue);

    //Cell 6, 0
    fValue = 100;
    p_oSeeds->SetValueOfCell(6, 0, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
    p_oSeeds->SetValueOfCell(6, 0, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
    p_oSeeds->SetValueOfCell(6, 0, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);
    p_oSeeds->SetValueOfCell(6, 0, p_oSeeds->GetFloatDataCode("seeds_4"), fValue);
    p_oSeeds->SetValueOfCell(6, 0, p_oSeeds->GetFloatDataCode("seeds_5"), fValue);

    //Cell 0, 7
    fValue = 100;
    p_oSeeds->SetValueOfCell(0, 7, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
    p_oSeeds->SetValueOfCell(0, 7, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
    p_oSeeds->SetValueOfCell(0, 7, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);
    p_oSeeds->SetValueOfCell(0, 7, p_oSeeds->GetFloatDataCode("seeds_4"), fValue);
    p_oSeeds->SetValueOfCell(0, 7, p_oSeeds->GetFloatDataCode("seeds_5"), fValue);

    //Cell 6, 7
    fValue = 100;
    p_oSeeds->SetValueOfCell(6, 7, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
    p_oSeeds->SetValueOfCell(6, 7, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
    p_oSeeds->SetValueOfCell(6, 7, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);
    p_oSeeds->SetValueOfCell(6, 7, p_oSeeds->GetFloatDataCode("seeds_4"), fValue);
    p_oSeeds->SetValueOfCell(6, 7, p_oSeeds->GetFloatDataCode("seeds_5"), fValue);

    //Run the model one timestep
    p_oSimManager->RunSim(1);

    //Count the seedlings in each grid cell
    clTreePopulation *p_oPop = (clTreePopulation*)p_oSimManager->GetPopulationObject("treepopulation");
    clTreeSearch *p_oSeedlings = p_oPop->Find("type=1");
    clTree *p_oTree = p_oSeedlings->NextTree();
    float f2_4MinX = 2 * 8, f2_4MaxX = 3 * 8,
        f2_4MinY = 4 * 8, f2_4MaxY = 5 * 8,
        f3_5MinX = 3 * 8, f3_5MaxX = 4 * 8,
        f3_5MinY = 5 * 8, f3_5MaxY = 6 * 8,
        f6_0MinX = 6 * 8, f6_0MaxX = 7 * 8,
        f6_0MinY = 0 * 8, f6_0MaxY = 1 * 8,
        f0_7MinX = 0 * 8, f0_7MaxX = 1 * 8,
        f0_7MinY = 7 * 8, f0_7MaxY = 8 * 8,
        f6_7MinX = 6 * 8, f6_7MaxX = 7 * 8,
        f6_7MinY = 7 * 8, f6_7MaxY = 8 * 8,
        fX, fY;
    int iSp2_2_4 = 0, iSp3_2_4 = 0, iSp5_2_4 = 0, iSp6_2_4 = 0,
        iSp2_3_5 = 0, iSp3_3_5 = 0, iSp5_3_5 = 0, iSp6_3_5 = 0,
        iSp2_6_0 = 0, iSp3_6_0 = 0, iSp5_6_0 = 0, iSp6_6_0 = 0,
        iSp2_0_7 = 0, iSp3_0_7 = 0, iSp5_0_7 = 0, iSp6_0_7 = 0,
        iSp2_6_7 = 0, iSp3_6_7 = 0, iSp5_6_7 = 0, iSp6_6_7 = 0;

    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
      p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);

      if (fX >= f2_4MinX && fX < f2_4MaxX && fY >= f2_4MinY && fY < f2_4MaxY) {
        //Cell 2, 4
        if (p_oTree->GetSpecies() == 1) iSp2_2_4++;
        else if (p_oTree->GetSpecies() == 2) iSp3_2_4++;
        else if (p_oTree->GetSpecies() == 4) iSp5_2_4++;
        else if (p_oTree->GetSpecies() == 5) iSp6_2_4++;
        else FAIL() << "Found unexpected species seedling.";
      } else if (fX >= f3_5MinX && fX < f3_5MaxX && fY >= f3_5MinY && fY < f3_5MaxY) {
        //Cell 3, 5
        if (p_oTree->GetSpecies() == 1) iSp2_3_5++;
        else if (p_oTree->GetSpecies() == 2) iSp3_3_5++;
        else if (p_oTree->GetSpecies() == 4) iSp5_3_5++;
        else if (p_oTree->GetSpecies() == 5) iSp6_3_5++;
        else FAIL() << "Found unexpected species seedling.";
      } else if (fX >= f6_0MinX && fX < f6_0MaxX && fY >= f6_0MinY && fY < f6_0MaxY) {
        //Cell 6, 0
        if (p_oTree->GetSpecies() == 1) iSp2_6_0++;
        else if (p_oTree->GetSpecies() == 2) iSp3_6_0++;
        else if (p_oTree->GetSpecies() == 4) iSp5_6_0++;
        else if (p_oTree->GetSpecies() == 5) iSp6_6_0++;
        else FAIL() << "Found unexpected species seedling.";
      } else if (fX >= f0_7MinX && fX < f0_7MaxX && fY >= f0_7MinY && fY < f0_7MaxY) {
        //Cell 0, 7
        if (p_oTree->GetSpecies() == 1) iSp2_0_7++;
        else if (p_oTree->GetSpecies() == 2) iSp3_0_7++;
        else if (p_oTree->GetSpecies() == 4) iSp5_0_7++;
        else if (p_oTree->GetSpecies() == 5) iSp6_0_7++;
        else FAIL() << "Found unexpected species seedling.";
      } else if (fX >= f6_7MinX && fX < f6_7MaxX && fY >= f6_7MinY && fY < f6_7MaxY) {
        //Cell 6, 7
        if (p_oTree->GetSpecies() == 1) iSp2_6_7++;
        else if (p_oTree->GetSpecies() == 2) iSp3_6_7++;
        else if (p_oTree->GetSpecies() == 4) iSp5_6_7++;
        else if (p_oTree->GetSpecies() == 5) iSp6_6_7++;
        else FAIL() << "Found unexpected species seedling.";
      }
      else {
        //Error - found seedlings where there were no seeds
        FAIL() << "Found seedling in an unexpected place.";
      }

      p_oTree = p_oSeedlings->NextTree();
    }
    //Check the counts
    EXPECT_EQ(1, iSp2_2_4);
    EXPECT_EQ(10, iSp3_2_4);
    EXPECT_EQ(1000, iSp5_2_4);
    EXPECT_EQ(10000, iSp6_2_4);

    EXPECT_EQ(25, iSp2_3_5);
    EXPECT_EQ(0, iSp3_3_5);
    EXPECT_EQ(331, iSp5_3_5);
    EXPECT_EQ(0, iSp6_3_5);

    EXPECT_EQ(100, iSp2_6_0);
    EXPECT_EQ(100, iSp3_6_0);
    EXPECT_EQ(100, iSp5_6_0);
    EXPECT_EQ(100, iSp6_6_0);

    EXPECT_EQ(100, iSp2_0_7);
    EXPECT_EQ(100, iSp3_0_7);
    EXPECT_EQ(100, iSp5_0_7);
    EXPECT_EQ(100, iSp6_0_7);

    EXPECT_EQ(100, iSp2_6_7);
    EXPECT_EQ(100, iSp3_6_7);
    EXPECT_EQ(100, iSp5_6_7);
    EXPECT_EQ(100, iSp6_6_7);

    //Verify that all seeds have been removed
    for (iX = 0; iX < iNumXCells; iX++) {
      for (iY = 0; iY < iNumYCells; iY++) {
        p_oSeeds->GetValueOfCell(iX, iY, p_oSeeds->GetFloatDataCode("seeds_1"), &fValue);
        EXPECT_EQ(0, fValue);
        p_oSeeds->GetValueOfCell(iX, iY, p_oSeeds->GetFloatDataCode("seeds_2"), &fValue);
        EXPECT_EQ(0, fValue);
        p_oSeeds->GetValueOfCell(iX, iY, p_oSeeds->GetFloatDataCode("seeds_3"), &fValue);
        EXPECT_EQ(0, fValue);
        p_oSeeds->GetValueOfCell(iX, iY, p_oSeeds->GetFloatDataCode("seeds_4"), &fValue);
        EXPECT_EQ(0, fValue);
        p_oSeeds->GetValueOfCell(iX, iY, p_oSeeds->GetFloatDataCode("seeds_5"), &fValue);
        EXPECT_EQ(0, fValue);
      }
    }
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun2()
// Tests establishment. WriteEstablishmentXMLFile2() does setup. Non-spatial dispserse is
// included with parameters such that it creates no seeds. The "Dispersed
// Seeds" grid cells divide evenly into the plot lengths. The grid is
// populated with some initial values. Then one timestep of a simulation is
// run and this verifies that the number of seedlings is right, and the
// number of seeds is 0.
/////////////////////////////////////////////////////////////////////////////
TEST(Establishment, TestNormalProcessingRun2) {

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    //Feed our file to the sim manager
    p_oSimManager->ReadFile(WriteEstablishmentXMLFile2());

    //Add seeds to the Dispersed Seeds grid
    clGrid *p_oSeeds = p_oSimManager->GetGridObject("Dispersed Seeds");
    float fValue;

    //Cell 2, 4
    fValue = 1;
    p_oSeeds->SetValueOfCell(2, 4, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
    fValue = 10;
    p_oSeeds->SetValueOfCell(2, 4, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
    fValue = 100;
    p_oSeeds->SetValueOfCell(2, 4, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);
    fValue = 1000;
    p_oSeeds->SetValueOfCell(2, 4, p_oSeeds->GetFloatDataCode("seeds_4"), fValue);
    fValue = 10000;
    p_oSeeds->SetValueOfCell(2, 4, p_oSeeds->GetFloatDataCode("seeds_5"), fValue);

    //Cell 3, 5
    fValue = 25;
    p_oSeeds->SetValueOfCell(3, 5, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
    fValue = 0;
    p_oSeeds->SetValueOfCell(3, 5, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
    fValue = 469;
    p_oSeeds->SetValueOfCell(3, 5, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);
    fValue = 331;
    p_oSeeds->SetValueOfCell(3, 5, p_oSeeds->GetFloatDataCode("seeds_4"), fValue);
    fValue = 0;
    p_oSeeds->SetValueOfCell(3, 5, p_oSeeds->GetFloatDataCode("seeds_5"), fValue);

    //Cell 9, 0
    fValue = 100;
    p_oSeeds->SetValueOfCell(9, 0, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
    p_oSeeds->SetValueOfCell(9, 0, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
    p_oSeeds->SetValueOfCell(9, 0, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);
    p_oSeeds->SetValueOfCell(9, 0, p_oSeeds->GetFloatDataCode("seeds_4"), fValue);
    p_oSeeds->SetValueOfCell(9, 0, p_oSeeds->GetFloatDataCode("seeds_5"), fValue);

    //Cell 0, 11
    fValue = 100;
    p_oSeeds->SetValueOfCell(0, 11, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
    p_oSeeds->SetValueOfCell(0, 11, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
    p_oSeeds->SetValueOfCell(0, 11, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);
    p_oSeeds->SetValueOfCell(0, 11, p_oSeeds->GetFloatDataCode("seeds_4"), fValue);
    p_oSeeds->SetValueOfCell(0, 11, p_oSeeds->GetFloatDataCode("seeds_5"), fValue);

    //Cell 9, 11
    fValue = 100;
    p_oSeeds->SetValueOfCell(9, 11, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
    p_oSeeds->SetValueOfCell(9, 11, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
    p_oSeeds->SetValueOfCell(9, 11, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);
    p_oSeeds->SetValueOfCell(9, 11, p_oSeeds->GetFloatDataCode("seeds_4"), fValue);
    p_oSeeds->SetValueOfCell(9, 11, p_oSeeds->GetFloatDataCode("seeds_5"), fValue);

    //Run the model one timestep
    p_oSimManager->RunSim(1);

    //Count the seedlings in each grid cell
    clTreePopulation *p_oPop = (clTreePopulation*)p_oSimManager->GetPopulationObject("treepopulation");
    clTreeSearch *p_oSeedlings = p_oPop->Find("type=1");
    clTree *p_oTree = p_oSeedlings->NextTree();
    float f2_4MinX = 2 * 5, f2_4MaxX = 3 * 5,
        f2_4MinY = 4 * 5, f2_4MaxY = 5 * 5,
        f3_5MinX = 3 * 5, f3_5MaxX = 4 * 5,
        f3_5MinY = 5 * 5, f3_5MaxY = 6 * 5,
        f9_0MinX = 9 * 5, f9_0MaxX = 10 * 5,
        f9_0MinY = 0 * 5, f9_0MaxY = 1 * 5,
        f0_11MinX = 0 * 5, f0_11MaxX = 1 * 5,
        f0_11MinY = 11 * 5, f0_11MaxY = 12 * 5,
        f9_11MinX = 9 * 5, f9_11MaxX = 10 * 5,
        f9_11MinY = 11 * 5, f9_11MaxY = 12 * 5,
        fX, fY;
    int iSp2_2_4 = 0, iSp3_2_4 = 0, iSp5_2_4 = 0, iSp6_2_4 = 0,
        iSp2_3_5 = 0, iSp3_3_5 = 0, iSp5_3_5 = 0, iSp6_3_5 = 0,
        iSp2_9_0 = 0, iSp3_9_0 = 0, iSp5_9_0 = 0, iSp6_9_0 = 0,
        iSp2_0_11 = 0, iSp3_0_11 = 0, iSp5_0_11 = 0, iSp6_0_11 = 0,
        iSp2_9_11 = 0, iSp3_9_11 = 0, iSp5_9_11 = 0, iSp6_9_11 = 0;

    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
      p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);

      if (fX >= f2_4MinX && fX < f2_4MaxX && fY >= f2_4MinY && fY < f2_4MaxY) {
        //Cell 2, 4
        if (p_oTree->GetSpecies() == 1) iSp2_2_4++;
        else if (p_oTree->GetSpecies() == 2) iSp3_2_4++;
        else if (p_oTree->GetSpecies() == 4) iSp5_2_4++;
        else if (p_oTree->GetSpecies() == 5) iSp6_2_4++;
        else FAIL() << "Found unexpected species seedling.";
      } else if (fX >= f3_5MinX && fX < f3_5MaxX && fY >= f3_5MinY && fY < f3_5MaxY) {
        //Cell 3, 5
        if (p_oTree->GetSpecies() == 1) iSp2_3_5++;
        else if (p_oTree->GetSpecies() == 2) iSp3_3_5++;
        else if (p_oTree->GetSpecies() == 4) iSp5_3_5++;
        else if (p_oTree->GetSpecies() == 5) iSp6_3_5++;
        else FAIL() << "Found unexpected species seedling.";
      } else if (fX >= f9_0MinX && fX < f9_0MaxX && fY >= f9_0MinY && fY < f9_0MaxY) {
        //Cell 6, 0
        if (p_oTree->GetSpecies() == 1) iSp2_9_0++;
        else if (p_oTree->GetSpecies() == 2) iSp3_9_0++;
        else if (p_oTree->GetSpecies() == 4) iSp5_9_0++;
        else if (p_oTree->GetSpecies() == 5) iSp6_9_0++;
        else FAIL() << "Found unexpected species seedling.";
      } else if (fX >= f0_11MinX && fX < f0_11MaxX && fY >= f0_11MinY && fY < f0_11MaxY) {
        //Cell 0, 7
        if (p_oTree->GetSpecies() == 1) iSp2_0_11++;
        else if (p_oTree->GetSpecies() == 2) iSp3_0_11++;
        else if (p_oTree->GetSpecies() == 4) iSp5_0_11++;
        else if (p_oTree->GetSpecies() == 5) iSp6_0_11++;
        else FAIL() << "Found unexpected species seedling.";
      } else if (fX >= f9_11MinX && fX < f9_11MaxX && fY >= f9_11MinY && fY < f9_11MaxY) {
        //Cell 6, 7
        if (p_oTree->GetSpecies() == 1) iSp2_9_11++;
        else if (p_oTree->GetSpecies() == 2) iSp3_9_11++;
        else if (p_oTree->GetSpecies() == 4) iSp5_9_11++;
        else if (p_oTree->GetSpecies() == 5) iSp6_9_11++;
        else FAIL() << "Found unexpected species seedling.";
      }
      else {
        //Error - found seedlings where there were no seeds
        FAIL() << "Found seedling in an unexpected place.";
      }

      p_oTree = p_oSeedlings->NextTree();
    }
    //Check the counts
    EXPECT_EQ(1, iSp2_2_4);
    EXPECT_EQ(10, iSp3_2_4);
    EXPECT_EQ(1000, iSp5_2_4);
    EXPECT_EQ(10000, iSp6_2_4);

    EXPECT_EQ(25, iSp2_3_5);
    EXPECT_EQ(0, iSp3_3_5);
    EXPECT_EQ(331, iSp5_3_5);
    EXPECT_EQ(0, iSp6_3_5);

    EXPECT_EQ(100, iSp2_9_0);
    EXPECT_EQ(100, iSp3_9_0);
    EXPECT_EQ(100, iSp5_9_0);
    EXPECT_EQ(100, iSp6_9_0);

    EXPECT_EQ(100, iSp2_0_11);
    EXPECT_EQ(100, iSp3_0_11);
    EXPECT_EQ(100, iSp5_0_11);
    EXPECT_EQ(100, iSp6_0_11);

    EXPECT_EQ(100, iSp2_9_11);
    EXPECT_EQ(100, iSp3_9_11);
    EXPECT_EQ(100, iSp5_9_11);
    EXPECT_EQ(100, iSp6_9_11);

    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestErrorProcessing()
////////////////////////////////////////////////////////////////////////////
TEST(Establishment, TestErrorProcessing) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try
  {
    p_oSimManager->ReadFile(WriteEstablishmentXMLErrorFile1());
    FAIL() << "TestEstablishment error processing didn't catch error for WriteEstablishmentXMLErrorFile1.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clEstablishment::GetData") != 0)
    {
      FAIL() << "TestEstablishment error processing caught wrong error for WriteEstablishmentXMLErrorFile1.";
    }
    ;
  }
  delete p_oSimManager;
}

/////////////////////////////////////////////////////////////////////////////
// WriteEstablishmentXMLFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteEstablishmentXMLFile1()
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
      << "<yearsPerTimestep>5</yearsPerTimestep>"
      << "<randomSeed>1</randomSeed>"
      << "<plot_lenX>50.0</plot_lenX>"
      << "<plot_lenY>60.0</plot_lenY>"
      << "<plot_latitude>55.37</plot_latitude>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
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
      << "<tr_species speciesName=\"Species_5\"/>"
      << "<tr_species speciesName=\"Species_6\"/>"
      << "</tr_speciesList>"
      << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
      << "<tr_minAdultDBH>"
      << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
      << "<tr_madVal species=\"Species_2\">10.0</tr_madVal>"
      << "<tr_madVal species=\"Species_3\">10.0</tr_madVal>"
      << "<tr_madVal species=\"Species_4\">10.0</tr_madVal>"
      << "<tr_madVal species=\"Species_5\">10.0</tr_madVal>"
      << "<tr_madVal species=\"Species_6\">10.0</tr_madVal>"
      << "</tr_minAdultDBH>"
      << "<tr_maxSeedlingHeight>"
      << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Species_2\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Species_3\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Species_4\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Species_5\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Species_6\">1.35</tr_mshVal>"
      << "</tr_maxSeedlingHeight>"
      << "</trees>"
      << "<allometry>"
      << "<tr_canopyHeight>"
      << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
      << "<tr_chVal species=\"Species_2\">39.54</tr_chVal>"
      << "<tr_chVal species=\"Species_3\">40.0</tr_chVal>"
      << "<tr_chVal species=\"Species_4\">39.48</tr_chVal>"
      << "<tr_chVal species=\"Species_5\">39.48</tr_chVal>"
      << "<tr_chVal species=\"Species_6\">39.48</tr_chVal>"
      << "</tr_canopyHeight>"
      << "<tr_stdAsympCrownRad>"
      << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_2\">0.0614</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_3\">0.0242</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_4\">0.0549</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_5\">0.0549</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_6\">0.0549</tr_sacrVal>"
      << "</tr_stdAsympCrownRad>"
      << "<tr_stdCrownRadExp>"
      << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_3\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_4\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_5\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_6\">1.0</tr_screVal>"
      << "</tr_stdCrownRadExp>"
      << "<tr_conversionDiam10ToDBH>"
      << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_2\">0.5944</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_3\">0.7059</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_4\">0.5944</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_5\">0.5944</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_6\">0.5944</tr_cdtdVal>"
      << "</tr_conversionDiam10ToDBH>"
      << "<tr_interceptDiam10ToDBH>"
      << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_3\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_4\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_5\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_6\">0</tr_idtdVal>"
      << "</tr_interceptDiam10ToDBH>"
      << "<tr_stdAsympCrownHt>"
      << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
      << "<tr_sachVal species=\"Species_2\">0.368</tr_sachVal>"
      << "<tr_sachVal species=\"Species_3\">0.464</tr_sachVal>"
      << "<tr_sachVal species=\"Species_4\">0.368</tr_sachVal>"
      << "<tr_sachVal species=\"Species_5\">0.368</tr_sachVal>"
      << "<tr_sachVal species=\"Species_6\">0.368</tr_sachVal>"
      << "</tr_stdAsympCrownHt>"
      << "<tr_stdCrownHtExp>"
      << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_3\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_4\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_5\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_6\">1.0</tr_scheVal>"
      << "</tr_stdCrownHtExp>"
      << "<tr_slopeOfHeight-Diam10>"
      << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_2\">0.0269</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_3\">0.02871</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_4\">0.0269</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_5\">0.0269</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_6\">0.0269</tr_sohdVal>"
      << "</tr_slopeOfHeight-Diam10>"
      << "<tr_slopeOfAsymHeight>"
      << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
      << "<tr_soahVal species=\"Species_2\">0.0241</tr_soahVal>"
      << "<tr_soahVal species=\"Species_3\">0.0263</tr_soahVal>"
      << "<tr_soahVal species=\"Species_4\">0.0241</tr_soahVal>"
      << "<tr_soahVal species=\"Species_5\">0.0241</tr_soahVal>"
      << "<tr_soahVal species=\"Species_6\">0.0241</tr_soahVal>"
      << "</tr_slopeOfAsymHeight>"
      << "<tr_whatSeedlingHeightDiam>"
      << "<tr_wsehdVal species=\"Species_1\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_2\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_3\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_4\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_5\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_6\">0</tr_wsehdVal>"
      << "</tr_whatSeedlingHeightDiam>"
      << "<tr_whatSaplingHeightDiam>"
      << "<tr_wsahdVal species=\"Species_1\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_2\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_3\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_4\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_5\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_6\">0</tr_wsahdVal>"
      << "</tr_whatSaplingHeightDiam>"
      << "<tr_whatAdultHeightDiam>"
      << "<tr_wahdVal species=\"Species_1\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_2\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_3\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_4\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_5\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_6\">0</tr_wahdVal>"
      << "</tr_whatAdultHeightDiam>"
      << "<tr_whatAdultCrownRadDiam>"
      << "<tr_wacrdVal species=\"Species_1\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Species_2\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Species_3\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Species_4\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Species_5\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Species_6\">0</tr_wacrdVal>"
      << "</tr_whatAdultCrownRadDiam>"
      << "<tr_whatAdultCrownHeightHeight>"
      << "<tr_wachhVal species=\"Species_1\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Species_2\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Species_3\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Species_4\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Species_5\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Species_6\">0</tr_wachhVal>"
      << "</tr_whatAdultCrownHeightHeight>"
      << "<tr_whatSaplingCrownRadDiam>"
      << "<tr_wscrdVal species=\"Species_1\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Species_2\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Species_3\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Species_4\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Species_5\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Species_6\">0</tr_wscrdVal>"
      << "</tr_whatSaplingCrownRadDiam>"
      << "<tr_whatSaplingCrownHeightHeight>"
      << "<tr_wschhVal species=\"Species_1\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Species_2\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Species_3\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Species_4\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Species_5\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Species_6\">0</tr_wschhVal>"
      << "</tr_whatSaplingCrownHeightHeight>"
      << "</allometry>"
      << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>NonSpatialDisperse</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_6\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_5\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>Establishment</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_5\" type=\"Seed\"/>"
      << "<applyTo species=\"Species_3\" type=\"Seed\"/>"
      << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
      << "<applyTo species=\"Species_6\" type=\"Seed\"/>"
      << "</behavior>"
      << "</behaviorList>";

  oOut << "<GeneralDisperse>"
      << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
      << "</GeneralDisperse>"
      << "<NonSpatialDisperse1>"
      << "<di_minDbhForReproduction>"
      << "<di_mdfrVal species=\"Species_4\">15.0</di_mdfrVal>"
      << "<di_mdfrVal species=\"Species_2\">15.0</di_mdfrVal>"
      << "<di_mdfrVal species=\"Species_3\">15.0</di_mdfrVal>"
      << "<di_mdfrVal species=\"Species_5\">15.0</di_mdfrVal>"
      << "<di_mdfrVal species=\"Species_6\">15.0</di_mdfrVal>"
      << "</di_minDbhForReproduction>"
      << "<di_nonSpatialSlopeOfLambda>"
      << "<di_nssolVal species=\"Species_4\">0</di_nssolVal>"
      << "<di_nssolVal species=\"Species_2\">0</di_nssolVal>"
      << "<di_nssolVal species=\"Species_3\">0</di_nssolVal>"
      << "<di_nssolVal species=\"Species_5\">0</di_nssolVal>"
      << "<di_nssolVal species=\"Species_6\">0</di_nssolVal>"
      << "</di_nonSpatialSlopeOfLambda>"
      << "<di_nonSpatialInterceptOfLambda>"
      << "<di_nsiolVal species=\"Species_4\">0</di_nsiolVal>"
      << "<di_nsiolVal species=\"Species_2\">0</di_nsiolVal>"
      << "<di_nsiolVal species=\"Species_3\">0</di_nsiolVal>"
      << "<di_nsiolVal species=\"Species_5\">0</di_nsiolVal>"
      << "<di_nsiolVal species=\"Species_6\">0</di_nsiolVal>"
      << "</di_nonSpatialInterceptOfLambda>"
      << "</NonSpatialDisperse1>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteEstablishmentXMLFile2()
/////////////////////////////////////////////////////////////////////////////
const char* WriteEstablishmentXMLFile2()
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
      << "<yearsPerTimestep>5</yearsPerTimestep>"
      << "<randomSeed>1</randomSeed>"
      << "<plot_lenX>50.0</plot_lenX>"
      << "<plot_lenY>60.0</plot_lenY>"
      << "<plot_latitude>55.37</plot_latitude>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
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
      << "<tr_species speciesName=\"Species_5\"/>"
      << "<tr_species speciesName=\"Species_6\"/>"
      << "</tr_speciesList>"
      << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
      << "<tr_minAdultDBH>"
      << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
      << "<tr_madVal species=\"Species_2\">10.0</tr_madVal>"
      << "<tr_madVal species=\"Species_3\">10.0</tr_madVal>"
      << "<tr_madVal species=\"Species_4\">10.0</tr_madVal>"
      << "<tr_madVal species=\"Species_5\">10.0</tr_madVal>"
      << "<tr_madVal species=\"Species_6\">10.0</tr_madVal>"
      << "</tr_minAdultDBH>"
      << "<tr_maxSeedlingHeight>"
      << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Species_2\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Species_3\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Species_4\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Species_5\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Species_6\">1.35</tr_mshVal>"
      << "</tr_maxSeedlingHeight>"
      << "</trees>"
      << "<allometry>"
      << "<tr_canopyHeight>"
      << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
      << "<tr_chVal species=\"Species_2\">39.54</tr_chVal>"
      << "<tr_chVal species=\"Species_3\">40.0</tr_chVal>"
      << "<tr_chVal species=\"Species_4\">39.48</tr_chVal>"
      << "<tr_chVal species=\"Species_5\">39.48</tr_chVal>"
      << "<tr_chVal species=\"Species_6\">39.48</tr_chVal>"
      << "</tr_canopyHeight>"
      << "<tr_stdAsympCrownRad>"
      << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_2\">0.0614</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_3\">0.0242</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_4\">0.0549</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_5\">0.0549</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_6\">0.0549</tr_sacrVal>"
      << "</tr_stdAsympCrownRad>"
      << "<tr_stdCrownRadExp>"
      << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_3\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_4\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_5\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_6\">1.0</tr_screVal>"
      << "</tr_stdCrownRadExp>"
      << "<tr_conversionDiam10ToDBH>"
      << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_2\">0.5944</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_3\">0.7059</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_4\">0.5944</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_5\">0.5944</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_6\">0.5944</tr_cdtdVal>"
      << "</tr_conversionDiam10ToDBH>"
      << "<tr_interceptDiam10ToDBH>"
      << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_3\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_4\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_5\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_6\">0</tr_idtdVal>"
      << "</tr_interceptDiam10ToDBH>"
      << "<tr_stdAsympCrownHt>"
      << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
      << "<tr_sachVal species=\"Species_2\">0.368</tr_sachVal>"
      << "<tr_sachVal species=\"Species_3\">0.464</tr_sachVal>"
      << "<tr_sachVal species=\"Species_4\">0.368</tr_sachVal>"
      << "<tr_sachVal species=\"Species_5\">0.368</tr_sachVal>"
      << "<tr_sachVal species=\"Species_6\">0.368</tr_sachVal>"
      << "</tr_stdAsympCrownHt>"
      << "<tr_stdCrownHtExp>"
      << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_3\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_4\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_5\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_6\">1.0</tr_scheVal>"
      << "</tr_stdCrownHtExp>"
      << "<tr_slopeOfHeight-Diam10>"
      << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_2\">0.0269</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_3\">0.02871</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_4\">0.0269</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_5\">0.0269</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_6\">0.0269</tr_sohdVal>"
      << "</tr_slopeOfHeight-Diam10>"
      << "<tr_slopeOfAsymHeight>"
      << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
      << "<tr_soahVal species=\"Species_2\">0.0241</tr_soahVal>"
      << "<tr_soahVal species=\"Species_3\">0.0263</tr_soahVal>"
      << "<tr_soahVal species=\"Species_4\">0.0241</tr_soahVal>"
      << "<tr_soahVal species=\"Species_5\">0.0241</tr_soahVal>"
      << "<tr_soahVal species=\"Species_6\">0.0241</tr_soahVal>"
      << "</tr_slopeOfAsymHeight>"
      << "<tr_whatSeedlingHeightDiam>"
      << "<tr_wsehdVal species=\"Species_1\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_2\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_3\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_4\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_5\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_6\">0</tr_wsehdVal>"
      << "</tr_whatSeedlingHeightDiam>"
      << "<tr_whatSaplingHeightDiam>"
      << "<tr_wsahdVal species=\"Species_1\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_2\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_3\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_4\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_5\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_6\">0</tr_wsahdVal>"
      << "</tr_whatSaplingHeightDiam>"
      << "<tr_whatAdultHeightDiam>"
      << "<tr_wahdVal species=\"Species_1\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_2\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_3\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_4\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_5\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_6\">0</tr_wahdVal>"
      << "</tr_whatAdultHeightDiam>"
      << "<tr_whatAdultCrownRadDiam>"
      << "<tr_wacrdVal species=\"Species_1\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Species_2\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Species_3\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Species_4\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Species_5\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Species_6\">0</tr_wacrdVal>"
      << "</tr_whatAdultCrownRadDiam>"
      << "<tr_whatAdultCrownHeightHeight>"
      << "<tr_wachhVal species=\"Species_1\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Species_2\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Species_3\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Species_4\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Species_5\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Species_6\">0</tr_wachhVal>"
      << "</tr_whatAdultCrownHeightHeight>"
      << "<tr_whatSaplingCrownRadDiam>"
      << "<tr_wscrdVal species=\"Species_1\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Species_2\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Species_3\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Species_4\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Species_5\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Species_6\">0</tr_wscrdVal>"
      << "</tr_whatSaplingCrownRadDiam>"
      << "<tr_whatSaplingCrownHeightHeight>"
      << "<tr_wschhVal species=\"Species_1\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Species_2\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Species_3\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Species_4\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Species_5\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Species_6\">0</tr_wschhVal>"
      << "</tr_whatSaplingCrownHeightHeight>"
      << "</allometry>";
  oOut << "<grid gridName=\"Dispersed Seeds\">"
      << "<ma_floatCodes>"
      << "<ma_floatCode label=\"seeds_0\">0</ma_floatCode>"
      << "<ma_floatCode label=\"seeds_1\">1</ma_floatCode>"
      << "<ma_floatCode label=\"seeds_2\">2</ma_floatCode>"
      << "<ma_floatCode label=\"seeds_3\">3</ma_floatCode>"
      << "<ma_floatCode label=\"seeds_4\">4</ma_floatCode>"
      << "<ma_floatCode label=\"seeds_5\">5</ma_floatCode>"
      << "</ma_floatCodes>"
      << "<ma_boolCodes>"
      << "<ma_boolCode label=\"Is Gap\">0</ma_boolCode>"
      << "</ma_boolCodes>"
      << "<ma_intCodes>"
      << "<ma_intCode label=\"count\">0</ma_intCode>"
      << "</ma_intCodes>"
      << "<ma_lengthXCells>5</ma_lengthXCells>"
      << "<ma_lengthYCells>5</ma_lengthYCells>"
      << "</grid>"
      << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>NonSpatialDisperse</behaviorName>"
      << "<listPosition>1</listPosition>"
      << "<version>1</version>"
      << "<applyTo species=\"Species_6\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_5\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>Establishment</behaviorName>"
      << "<listPosition>2</listPosition>"
      << "<version>1</version>"
      << "<applyTo species=\"Species_5\" type=\"Seed\"/>"
      << "<applyTo species=\"Species_3\" type=\"Seed\"/>"
      << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
      << "<applyTo species=\"Species_6\" type=\"Seed\"/>"
      << "</behavior>"
      << "</behaviorList>";

  oOut << "<NonSpatialDisperse1>"
      << "<di_minDbhForReproduction>"
      << "<di_mdfrVal species=\"Species_4\">15.0</di_mdfrVal>"
      << "<di_mdfrVal species=\"Species_2\">15.0</di_mdfrVal>"
      << "<di_mdfrVal species=\"Species_3\">15.0</di_mdfrVal>"
      << "<di_mdfrVal species=\"Species_5\">15.0</di_mdfrVal>"
      << "<di_mdfrVal species=\"Species_6\">15.0</di_mdfrVal>"
      << "</di_minDbhForReproduction>"
      << "<di_nonSpatialSlopeOfLambda>"
      << "<di_nssolVal species=\"Species_4\">0</di_nssolVal>"
      << "<di_nssolVal species=\"Species_2\">0</di_nssolVal>"
      << "<di_nssolVal species=\"Species_3\">0</di_nssolVal>"
      << "<di_nssolVal species=\"Species_5\">0</di_nssolVal>"
      << "<di_nssolVal species=\"Species_6\">0</di_nssolVal>"
      << "</di_nonSpatialSlopeOfLambda>"
      << "<di_nonSpatialInterceptOfLambda>"
      << "<di_nsiolVal species=\"Species_4\">0</di_nsiolVal>"
      << "<di_nsiolVal species=\"Species_2\">0</di_nsiolVal>"
      << "<di_nsiolVal species=\"Species_3\">0</di_nsiolVal>"
      << "<di_nsiolVal species=\"Species_5\">0</di_nsiolVal>"
      << "<di_nsiolVal species=\"Species_6\">0</di_nsiolVal>"
      << "</di_nonSpatialInterceptOfLambda>"
      << "</NonSpatialDisperse1>"
      << "<GeneralDisperse>"
      << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
      << "</GeneralDisperse>";

  oOut << "<establishment>"
      << "<es_useSeedlingEfficiencyRoutine>0</es_useSeedlingEfficiencyRoutine>"
      << "</establishment>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteEstablishmentXMLErrorFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteEstablishmentXMLErrorFile1()
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
      << "<yearsPerTimestep>5</yearsPerTimestep>"
      << "<randomSeed>1</randomSeed>"
      << "<plot_lenX>50.0</plot_lenX>"
      << "<plot_lenY>50.0</plot_lenY>"
      << "<plot_latitude>55.37</plot_latitude>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
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
      << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
      << "<tr_chVal species=\"Species_2\">39.54</tr_chVal>"
      << "</tr_canopyHeight>"
      << "<tr_stdAsympCrownRad>"
      << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_2\">0.0614</tr_sacrVal>"
      << "</tr_stdAsympCrownRad>"
      << "<tr_stdCrownRadExp>"
      << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
      << "</tr_stdCrownRadExp>"
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
      << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
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
      << "<behaviorName>Establishment</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
      << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
      << "</behavior>"
      << "</behaviorList>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}
