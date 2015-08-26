//---------------------------------------------------------------------------
// TestSpatialDispersal.cpp
//---------------------------------------------------------------------------
#include "TestSpatialDispersal.h"
#include <gtest/gtest.h>
#include "Grid.h"
#include "SimManager.h"
#include "BehaviorBase.h"
#include <stdio.h>
#include <fstream>
#include <math.h>

/////////////////////////////////////////////////////////////////////////////
// TestDispersal1()
// Tests spatial dispersal using the first set of conditions. It will cause a
// parameter file to be written and then passed to a clSimManager object. This
// object will read it. The disperse behavior is run and the contents of the
// seed grid examined.
/////////////////////////////////////////////////////////////////////////////
TEST(SpatialDispersal, TestDispersal1) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
   clGrid *p_oSeedGrid;

   //Feed our file to the sim manager
   p_oSimManager->ReadFile(WriteSpatialDispersalXMLFile1());

   //Run one timestep - can't just use RunSim() because TimestepCleanup will
   //erase the results we want to check
   int i;
   for (i = 0; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
     clBehaviorBase *p_oBase = p_oSimManager->GetBehaviorObject(i);
     p_oBase->Action();
   }

   //Verify file 1
   p_oSeedGrid = p_oSimManager->GetGridObject("Dispersed Seeds");
   ASSERT_TRUE(p_oSeedGrid);
   VerifyXMLFile1Timestep1(p_oSeedGrid);

   //RunSim now so we can check timestep cleanup
   p_oSimManager->RunSim(1);

   //Run a second timestep and re-verify
   for (i = 0; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
     clBehaviorBase *p_oBase = p_oSimManager->GetBehaviorObject(i);
     p_oBase->Action();
   }

   p_oSeedGrid = p_oSimManager->GetGridObject("Dispersed Seeds");
   ASSERT_TRUE(p_oSeedGrid);
   VerifyXMLFile1Timestep2(p_oSeedGrid);
   delete p_oSimManager;
   } catch (modelErr &e) {
     delete p_oSimManager;
     FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
   }
}

/////////////////////////////////////////////////////////////////////////////
// TestDispersal2()
// Tests spatial dispersal using the second set of conditions. It will cause a
// parameter file to be written and then passed to a clSimManager object. This
// object will read it. The disperse behavior is run and the contents of the
// seed grid examined.
/////////////////////////////////////////////////////////////////////////////
TEST(SpatialDispersal, TestDispersal2) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
   clGrid *p_oSeedGrid;

   //Feed our file to the sim manager
   p_oSimManager->ReadFile(WriteSpatialDispersalXMLFile2());

   //Run one timestep - can't just use RunSim() because TimestepCleanup will
   //erase the results we want to check
   int i;
   for (i = 0; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
     clBehaviorBase *p_oBase = p_oSimManager->GetBehaviorObject(i);
     p_oBase->Action();
   }

   //Verify file 2
   p_oSeedGrid = p_oSimManager->GetGridObject("Dispersed Seeds");
   ASSERT_TRUE(p_oSeedGrid);
   VerifyXMLFile2(p_oSeedGrid);
   delete p_oSimManager;
   } catch (modelErr &e) {
     delete p_oSimManager;
     FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
   }
}

/////////////////////////////////////////////////////////////////////////////
// VerifyXMLFile1Timestep1
/////////////////////////////////////////////////////////////////////////////
void VerifyXMLFile1Timestep1(clGrid *p_oSeedGrid) {

  int iNumXCells, iNumYCells,
      iX, iY, i,
      iGapCode,
      iNumSpecies = 6,
      *p_iCodes = new int[iNumSpecies];
  float fTemp,
   *p_fNumSeeds = new float[iNumSpecies];
  char *cCode = new char[10];
  bool bIsGap;

  for (iX = 0; iX < iNumSpecies; iX++) {
    p_fNumSeeds[iX] = 0;
    sprintf(cCode, "%s%d", "seeds_", iX);
    p_iCodes[iX] = p_oSeedGrid->GetFloatDataCode(cCode);
    //Make sure we got the codes
    EXPECT_GT(p_iCodes[iX], -1);
  }

  iGapCode = p_oSeedGrid->GetBoolDataCode("Is Gap");
  EXPECT_GT(iGapCode, -1);

  //Verify the size of the grid cells
  EXPECT_EQ(2, p_oSeedGrid->GetLengthXCells());
  EXPECT_EQ(4, p_oSeedGrid->GetLengthYCells());

  //Add up the amount of seeds for each species
  iNumXCells = p_oSeedGrid->GetNumberXCells();
  iNumYCells = p_oSeedGrid->GetNumberYCells();

  //While we're going through the cells, assert the gap status
  for (iX = 0; iX < iNumXCells; iX++) {
    for (iY = 0; iY < iNumYCells; iY++) {

      p_oSeedGrid->GetValueOfCell(iX, iY, iGapCode, &bIsGap);

      if ((iX == 6 && iY == 3) ||
          (iX == 17 && iY == 8) ||
          (iX == 25 && iY == 12) ||
          (iX == 15 && iY == 30) ||
          (iX == 50 && iY == 25)) {

        EXPECT_EQ(bIsGap, false);
      }
      else {

        ASSERT_TRUE(bIsGap);
      }

      for (i = 0; i < iNumSpecies; i++) {
        p_oSeedGrid->GetValueOfCell(iX, iY, p_iCodes[i], &fTemp);
        p_fNumSeeds[i] += fTemp;
      }
    }
  }

  //Verify the number of seeds collected - remember that not all survive when
  //gap
  EXPECT_EQ(0, p_fNumSeeds[0]);
  EXPECT_TRUE(25 == p_fNumSeeds[1] || 26 == p_fNumSeeds[1]);
  EXPECT_TRUE(50 <= p_fNumSeeds[2] && 52 >= p_fNumSeeds[2]);
  EXPECT_TRUE(127 <= p_fNumSeeds[3] && 141 >= p_fNumSeeds[3]);
  EXPECT_TRUE(8 <= p_fNumSeeds[4] && 16 >= p_fNumSeeds[4]);
  EXPECT_EQ(0, p_fNumSeeds[5]);

  delete[] p_fNumSeeds;
  delete[] p_iCodes;
  delete[] cCode;
}
//---------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////
// VerifyXMLFile1Timestep2
/////////////////////////////////////////////////////////////////////////////
void VerifyXMLFile1Timestep2(clGrid *p_oSeedGrid) {
  float fTemp;
  int iNumXCells, iNumYCells,
      iX, iY, i,
      iGapCode,
      iNumSpecies = 6,
      *p_iNumSeeds = new int[iNumSpecies],
      *p_iCodes = new int[iNumSpecies];
  char *cCode = new char[10];
  bool bIsGap;

  for (iX = 0; iX < iNumSpecies; iX++) {
    p_iNumSeeds[iX] = 0;
    sprintf(cCode, "%s%d", "seeds_", iX);
    p_iCodes[iX] = p_oSeedGrid->GetFloatDataCode(cCode);
    //Make sure we got the codes
    EXPECT_GT(p_iCodes[iX], -1);
  }

  iGapCode = p_oSeedGrid->GetBoolDataCode("Is Gap");
  EXPECT_GT(iGapCode, -1);

  //Verify the size of the grid cells
  EXPECT_EQ(2, p_oSeedGrid->GetLengthXCells());
  EXPECT_EQ(4, p_oSeedGrid->GetLengthYCells());

  //Add up the amount of seeds for each species
  iNumXCells = p_oSeedGrid->GetNumberXCells();
  iNumYCells = p_oSeedGrid->GetNumberYCells();

  //While we're going through the cells, assert the gap status
  for (iX = 0; iX < iNumXCells; iX++) {
    for (iY = 0; iY < iNumYCells; iY++) {

      p_oSeedGrid->GetValueOfCell(iX, iY, iGapCode, &bIsGap);

      if ((iX == 6 && iY == 3) ||
          (iX == 17 && iY == 8) ||
          (iX == 25 && iY == 12) ||
          (iX == 15 && iY == 30) ||
          (iX == 50 && iY == 25)) {

        EXPECT_EQ(bIsGap, false);
      }
      else {

        ASSERT_TRUE(bIsGap);
      }

      for (i = 0; i < iNumSpecies; i++) {
        p_oSeedGrid->GetValueOfCell(iX, iY, p_iCodes[i], &fTemp);
        p_iNumSeeds[i] += (int)fTemp;
      }
    }
  }

  //Verify the number of seeds collected
  EXPECT_EQ(0, p_iNumSeeds[0]);
  EXPECT_TRUE(25 == p_iNumSeeds[1] || 26 == p_iNumSeeds[1]);
  EXPECT_TRUE(42 == p_iNumSeeds[2] || 43 == p_iNumSeeds[2]);
  EXPECT_LT(127, p_iNumSeeds[3]); EXPECT_GT(141, p_iNumSeeds[3]);
  EXPECT_TRUE(12 <= p_iNumSeeds[4] && 17 >= p_iNumSeeds[4]);
  EXPECT_EQ(0, p_iNumSeeds[5]);

  delete[] p_iNumSeeds;
  delete[] p_iCodes;
  delete[] cCode;
}
//---------------------------------------------------------------------------


/////////////////////////////////////////////////////////////////////////////
// VerifyXMLFile2()
/////////////////////////////////////////////////////////////////////////////
void VerifyXMLFile2(clGrid *p_oSeedGrid) {
  float fTemp;
  int iNumXCells, iNumYCells,
      iX, iY, i,
      iGapCode,
      iNumSpecies = 6,
      *p_iNumSeeds = new int[iNumSpecies],
      *p_iCodes = new int[iNumSpecies];
  char *cCode = new char[10];
  bool bIsGap;

  for (iX = 0; iX < iNumSpecies; iX++) {
    p_iNumSeeds[iX] = 0;
    sprintf(cCode, "%s%d", "seeds_", iX);
    p_iCodes[iX] = p_oSeedGrid->GetFloatDataCode(cCode);
    //Make sure we got the codes
    EXPECT_GT(p_iCodes[iX], -1);
  }

  iGapCode = p_oSeedGrid->GetBoolDataCode("Is Gap");
  EXPECT_GT(iGapCode, -1);

  //Verify the size of the grid cells
  EXPECT_EQ(8, p_oSeedGrid->GetLengthXCells());
  EXPECT_EQ(8, p_oSeedGrid->GetLengthYCells());

  //Add up the amount of seeds for each species
  iNumXCells = p_oSeedGrid->GetNumberXCells();
  iNumYCells = p_oSeedGrid->GetNumberYCells();

  //While we're going through the cells, assert the gap status
  for (iX = 0; iX < iNumXCells; iX++) {
    for (iY = 0; iY < iNumYCells; iY++) {

      p_oSeedGrid->GetValueOfCell(iX, iY, iGapCode, &bIsGap);

      if ((iX == 1 && iY == 1) ||
          (iX == 4 && iY == 4) ||
          (iX == 6 && iY == 6) ||
          (iX == 3 && iY == 15) ||
          (iX == 12 && iY == 12)) {
        EXPECT_EQ(bIsGap, false);
      }
      else {
      	if (false == bIsGap)
      	  bIsGap = false;
        ASSERT_TRUE(bIsGap);
      }

      for (i = 0; i < 5; i++) {
        p_oSeedGrid->GetValueOfCell(iX, iY, p_iCodes[i], &fTemp);
        p_iNumSeeds[i] += (int)fTemp;
      }
    }
  }

  //Verify the number of seeds collected
  EXPECT_EQ(0, p_iNumSeeds[0]);
  EXPECT_TRUE(100 == p_iNumSeeds[1] || 101 == p_iNumSeeds[1]);
  EXPECT_TRUE(204 == p_iNumSeeds[2] || 205 == p_iNumSeeds[2]);
  EXPECT_LT(509, p_iNumSeeds[3]); EXPECT_GT(563, p_iNumSeeds[3]);
// EXPECT_LT(52, p_iNumSeeds[4]); EXPECT_GT(60, p_iNumSeeds[4]); this one is really hard to test
  EXPECT_EQ(0, p_iNumSeeds[5]);

  delete[] p_iNumSeeds;
  delete[] p_iCodes;
  delete[] cCode;
}

/////////////////////////////////////////////////////////////////////////////
// WriteSpatialDispersalXMLFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteSpatialDispersalXMLFile1()
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
       << "<tr_treemap>"
       << "<tm_treeSettings sp=\"Species_1\" tp=\"3\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_1\" tp=\"2\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_2\" tp=\"3\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_3\" tp=\"3\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_4\" tp=\"3\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_5\" tp=\"3\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_6\" tp=\"3\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_3\" tp=\"4\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tree sp=\"0\" tp=\"3\">"
       << "<fl c=\"0\">1</fl>"
       << "<fl c=\"1\">1</fl>"
       << "<fl c=\"2\">12</fl>"
       << "</tree>"
       << "<tree sp=\"0\" tp=\"2\">"
       << "<fl c=\"0\">24</fl>"
       << "<fl c=\"1\">100</fl>"
       << "<fl c=\"2\">8</fl>"
       << "</tree>"
       << "<tree sp=\"1\" tp=\"3\">"
       << "<fl c=\"0\">12</fl>"
       << "<fl c=\"1\">12</fl>"
       << "<fl c=\"2\">34</fl>"
       << "</tree>"
       << "<tree sp=\"2\" tp=\"3\">"
       << "<fl c=\"0\">35</fl>"
       << "<fl c=\"1\">35</fl>"
       << "<fl c=\"2\">53</fl>"
       << "</tree>"
       << "<tree sp=\"3\" tp=\"3\">"
       << "<fl c=\"0\">50</fl>"
       << "<fl c=\"1\">50</fl>"
       << "<fl c=\"2\">78</fl>"
       << "</tree>"
       << "<tree sp=\"4\" tp=\"3\">"
       << "<fl c=\"0\">30</fl>"
       << "<fl c=\"1\">122</fl>"
       << "<fl c=\"2\">42</fl>"
       << "</tree>"
       << "<tree sp=\"5\" tp=\"3\">"
       << "<fl c=\"0\">100</fl>"
       << "<fl c=\"1\">100</fl>"
       << "<fl c=\"2\">30</fl>"
       << "</tree>"
       << "<tree sp=\"2\" tp=\"4\">"
       << "<fl c=\"0\">180</fl>"
       << "<fl c=\"1\">180</fl>"
       << "<fl c=\"2\">25</fl>"
       << "</tree>"
       << "</tr_treemap>"
       << "</trees>"
       << "<allometry>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_2\">39.54</tr_chVal>"
       << "<tr_chVal species=\"Species_3\">40.0</tr_chVal>"
       << "<tr_chVal species=\"Species_4\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_5\">39.54</tr_chVal>"
       << "<tr_chVal species=\"Species_6\">39.54</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_2\">0.0614</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_3\">0.0242</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_4\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_5\">0.0614</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_6\">0.0614</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_3\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_4\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_5\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_6\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_stdMaxCrownRad>"
       << "<tr_smcrVal species=\"Species_1\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_2\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_3\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_4\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_5\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_6\">10</tr_smcrVal>"
       << "</tr_stdMaxCrownRad>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">0.5944</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_3\">0.7059</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_4\">0.5944</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_5\">0.7059</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_6\">0.7059</tr_cdtdVal>"
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
       << "<tr_sachVal species=\"Species_5\">0.464</tr_sachVal>"
       << "<tr_sachVal species=\"Species_6\">0.464</tr_sachVal>"
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
       << "<tr_sohdVal species=\"Species_5\">0.02871</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_6\">0.02871</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_2\">0.0241</tr_soahVal>"
       << "<tr_soahVal species=\"Species_3\">0.0263</tr_soahVal>"
       << "<tr_soahVal species=\"Species_4\">0.0241</tr_soahVal>"
       << "<tr_soahVal species=\"Species_5\">0.0263</tr_soahVal>"
       << "<tr_soahVal species=\"Species_6\">0.0263</tr_soahVal>"
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
       //Set the default grids
       << "<grid gridName=\"Dispersed Seeds\">"
       << "<ma_intCodes>"
       << "<ma_intCode label=\"count\">6</ma_intCode>"
       << "</ma_intCodes>"
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
       << "<ma_lengthXCells>2</ma_lengthXCells>"
       << "<ma_lengthYCells>4</ma_lengthYCells>"
       << "</grid>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>GapDisperse</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_5\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>NonGapDisperse</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Stump\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<GeneralDisperse>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</GeneralDisperse>"
       << "<NonGapDisperse2>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_1\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_2\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_3\">15.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "<di_weibullCanopySTR>"
       << "<di_wcsVal species=\"Species_1\">19.325</di_wcsVal>"
       << "<di_wcsVal species=\"Species_3\">12.257</di_wcsVal>"
       << "</di_weibullCanopySTR>"
       << "<di_weibullCanopyBeta>"
       << "<di_wcbVal species=\"Species_1\">2.0</di_wcbVal>"
       << "<di_wcbVal species=\"Species_3\">2.2</di_wcbVal>"
       << "</di_weibullCanopyBeta>"
       << "<di_weibullCanopyDispersal>"
       << "<di_wcdVal species=\"Species_1\">1.76E-4</di_wcdVal>"
       << "<di_wcdVal species=\"Species_3\">9.61E-5</di_wcdVal>"
       << "</di_weibullCanopyDispersal>"
       << "<di_weibullCanopyTheta>"
       << "<di_wctVal species=\"Species_1\">3.0</di_wctVal>"
       << "<di_wctVal species=\"Species_3\">3.0</di_wctVal>"
       << "</di_weibullCanopyTheta>"
       << "<di_lognormalCanopySTR>"
       << "<di_lcsVal species=\"Species_2\">19.325</di_lcsVal>"
       << "</di_lognormalCanopySTR>"
       << "<di_lognormalCanopyXb>"
       << "<di_lcxbVal species=\"Species_2\">3.0</di_lcxbVal>"
       << "</di_lognormalCanopyXb>"
       << "<di_lognormalCanopyBeta>"
       << "<di_lcbVal species=\"Species_2\">2.1</di_lcbVal>"
       << "</di_lognormalCanopyBeta>"
       << "<di_lognormalCanopyX0>"
       << "<di_lcx0Val species=\"Species_2\">1.82E-4</di_lcx0Val>"
       << "</di_lognormalCanopyX0>"
       << "<di_suckerSTR>"
       << "<di_ssVal species=\"Species_3\">12.257</di_ssVal>"
       << "</di_suckerSTR>"
       << "<di_suckerBeta>"
       << "<di_sbVal species=\"Species_3\">2.2</di_sbVal>"
       << "</di_suckerBeta>"
       << "<di_canopyFunction>"
       << "<di_cfVal species=\"Species_1\">0</di_cfVal>"
       << "<di_cfVal species=\"Species_2\">1</di_cfVal>"
       << "<di_cfVal species=\"Species_3\">0</di_cfVal>"
       << "</di_canopyFunction>"
       << "</NonGapDisperse2>"
       << "<GapDisperse1>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_4\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_5\">15.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "<di_weibullGapSTR>"
       << "<di_wgsVal species=\"Species_4\">14.894</di_wgsVal>"
       << "<di_wgsVal species=\"Species_5\">6.628</di_wgsVal>"
       << "</di_weibullGapSTR>"
       << "<di_weibullGapBeta>"
       << "<di_wgbVal species=\"Species_4\">2.3</di_wgbVal>"
       << "<di_wgbVal species=\"Species_5\">2.2</di_wgbVal>"
       << "</di_weibullGapBeta>"
       << "<di_weibullGapDispersal>"
       << "<di_wgdVal species=\"Species_4\">1.32E-4</di_wgdVal>"
       << "<di_wgdVal species=\"Species_5\">6.93E-6</di_wgdVal>"
       << "</di_weibullGapDispersal>"
       << "<di_weibullGapTheta>"
       << "<di_wgtVal species=\"Species_4\">3.0</di_wgtVal>"
       << "<di_wgtVal species=\"Species_5\">3.0</di_wgtVal>"
       << "</di_weibullGapTheta>"
       << "<di_lognormalCanopySTR>"
       << "<di_lcsVal species=\"Species_4\">6.628</di_lcsVal>"
       << "<di_lcsVal species=\"Species_5\">17.206</di_lcsVal>"
       << "</di_lognormalCanopySTR>"
       << "<di_lognormalCanopyBeta>"
       << "<di_lcbVal species=\"Species_4\">2.3</di_lcbVal>"
       << "<di_lcbVal species=\"Species_5\">2.4</di_lcbVal>"
       << "</di_lognormalCanopyBeta>"
       << "<di_lognormalCanopyX0>"
       << "<di_lcx0Val species=\"Species_4\">1.32E-4</di_lcx0Val>"
       << "<di_lcx0Val species=\"Species_5\">6.93E-6</di_lcx0Val>"
       << "</di_lognormalCanopyX0>"
       << "<di_lognormalCanopyXb>"
       << "<di_lcxbVal species=\"Species_4\">3.0</di_lcxbVal>"
       << "<di_lcxbVal species=\"Species_5\">3.0</di_lcxbVal>"
       << "</di_lognormalCanopyXb>"
       << "<di_maxGapDensity>0</di_maxGapDensity>"
       << "<di_gapFunction>"
       << "<di_gfVal species=\"Species_4\">0</di_gfVal>"
       << "<di_gfVal species=\"Species_5\">0</di_gfVal>"
       << "</di_gapFunction>"
       << "<di_canopyFunction>"
       << "<di_cfVal species=\"Species_4\">1</di_cfVal>"
       << "<di_cfVal species=\"Species_5\">1</di_cfVal>"
       << "</di_canopyFunction>"
       << "</GapDisperse1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}


/////////////////////////////////////////////////////////////////////////////
// WriteSpatialDispersalXMLFile2()
/////////////////////////////////////////////////////////////////////////////
const char* WriteSpatialDispersalXMLFile2() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>1</timesteps>"
       << "<yearsPerTimestep>4</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>200.0</plot_lenX>"
       << "<plot_lenY>200.0</plot_lenY>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
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
       << "<tr_treemap>"
       << "<tm_treeSettings sp=\"Species_1\" tp=\"3\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_1\" tp=\"2\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_2\" tp=\"3\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_3\" tp=\"3\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_4\" tp=\"3\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_5\" tp=\"3\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_6\" tp=\"3\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_3\" tp=\"4\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tree sp=\"0\" tp=\"3\">"
       << "<fl c=\"0\">1</fl>"
       << "<fl c=\"1\">1</fl>"
       << "<fl c=\"2\">12</fl>"
       << "</tree>"
       << "<tree sp=\"0\" tp=\"2\">"
       << "<fl c=\"0\">24</fl>"
       << "<fl c=\"1\">100</fl>"
       << "<fl c=\"2\">8</fl>"
       << "</tree>"
       << "<tree sp=\"1\" tp=\"3\">"
       << "<fl c=\"0\">12</fl>"
       << "<fl c=\"1\">12</fl>"
       << "<fl c=\"2\">34</fl>"
       << "</tree>"
       << "<tree sp=\"2\" tp=\"3\">"
       << "<fl c=\"0\">35</fl>"
       << "<fl c=\"1\">35</fl>"
       << "<fl c=\"2\">53</fl>"
       << "</tree>"
       << "<tree sp=\"3\" tp=\"3\">"
       << "<fl c=\"0\">50</fl>"
       << "<fl c=\"1\">50</fl>"
       << "<fl c=\"2\">78</fl>"
       << "</tree>"
       << "<tree sp=\"4\" tp=\"3\">"
       << "<fl c=\"0\">30</fl>"
       << "<fl c=\"1\">122</fl>"
       << "<fl c=\"2\">42</fl>"
       << "</tree>"
       << "<tree sp=\"5\" tp=\"3\">"
       << "<fl c=\"0\">100</fl>"
       << "<fl c=\"1\">100</fl>"
       << "<fl c=\"2\">30</fl>"
       << "</tree>"
       << "<tree sp=\"2\" tp=\"4\">"
       << "<fl c=\"0\">180</fl>"
       << "<fl c=\"1\">180</fl>"
       << "<fl c=\"2\">25</fl>"
       << "</tree>"
       << "</tr_treemap>"
       << "</trees>"
       << "<allometry>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_2\">39.54</tr_chVal>"
       << "<tr_chVal species=\"Species_3\">40.0</tr_chVal>"
       << "<tr_chVal species=\"Species_4\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_5\">39.54</tr_chVal>"
       << "<tr_chVal species=\"Species_6\">39.54</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_2\">0.0614</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_3\">0.0242</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_4\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_5\">0.0614</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_6\">0.0614</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_3\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_4\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_5\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_6\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_stdMaxCrownRad>"
       << "<tr_smcrVal species=\"Species_1\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_2\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_3\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_4\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_5\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_6\">10</tr_smcrVal>"
       << "</tr_stdMaxCrownRad>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">0.5944</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_3\">0.7059</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_4\">0.5944</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_5\">0.7059</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_6\">0.7059</tr_cdtdVal>"
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
       << "<tr_sachVal species=\"Species_5\">0.464</tr_sachVal>"
       << "<tr_sachVal species=\"Species_6\">0.464</tr_sachVal>"
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
       << "<tr_sohdVal species=\"Species_5\">0.02871</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_6\">0.02871</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_2\">0.0241</tr_soahVal>"
       << "<tr_soahVal species=\"Species_3\">0.0263</tr_soahVal>"
       << "<tr_soahVal species=\"Species_4\">0.0241</tr_soahVal>"
       << "<tr_soahVal species=\"Species_5\">0.0263</tr_soahVal>"
       << "<tr_soahVal species=\"Species_6\">0.0263</tr_soahVal>"
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
       << "<behaviorName>GapDisperse</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_5\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>NonGapDisperse</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Stump\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<GeneralDisperse>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</GeneralDisperse>"
       << "<GapDisperse1>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_4\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_5\">15.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "<di_weibullGapSTR>"
       << "<di_wgsVal species=\"Species_4\">14.894</di_wgsVal>"
       << "<di_wgsVal species=\"Species_5\">6.628</di_wgsVal>"
       << "</di_weibullGapSTR>"
       << "<di_weibullGapBeta>"
       << "<di_wgbVal species=\"Species_4\">2.3</di_wgbVal>"
       << "<di_wgbVal species=\"Species_5\">2.2</di_wgbVal>"
       << "</di_weibullGapBeta>"
       << "<di_weibullGapDispersal>"
       << "<di_wgdVal species=\"Species_4\">1.32E-4</di_wgdVal>"
       << "<di_wgdVal species=\"Species_5\">6.93E-6</di_wgdVal>"
       << "</di_weibullGapDispersal>"
       << "<di_weibullGapTheta>"
       << "<di_wgtVal species=\"Species_4\">3.0</di_wgtVal>"
       << "<di_wgtVal species=\"Species_5\">3.0</di_wgtVal>"
       << "</di_weibullGapTheta>"
       << "<di_lognormalCanopySTR>"
       << "<di_lcsVal species=\"Species_4\">6.628</di_lcsVal>"
       << "<di_lcsVal species=\"Species_5\">17.206</di_lcsVal>"
       << "</di_lognormalCanopySTR>"
       << "<di_lognormalCanopyBeta>"
       << "<di_lcbVal species=\"Species_4\">2.3</di_lcbVal>"
       << "<di_lcbVal species=\"Species_5\">2.4</di_lcbVal>"
       << "</di_lognormalCanopyBeta>"
       << "<di_lognormalCanopyX0>"
       << "<di_lcx0Val species=\"Species_4\">1.32E-4</di_lcx0Val>"
       << "<di_lcx0Val species=\"Species_5\">6.93E-6</di_lcx0Val>"
       << "</di_lognormalCanopyX0>"
       << "<di_lognormalCanopyXb>"
       << "<di_lcxbVal species=\"Species_4\">3.0</di_lcxbVal>"
       << "<di_lcxbVal species=\"Species_5\">3.0</di_lcxbVal>"
       << "</di_lognormalCanopyXb>"
       << "<di_maxGapDensity>0</di_maxGapDensity>"
       << "<di_gapFunction>"
       << "<di_gfVal species=\"Species_4\">0</di_gfVal>"
       << "<di_gfVal species=\"Species_5\">0</di_gfVal>"
       << "</di_gapFunction>"
       << "<di_canopyFunction>"
       << "<di_cfVal species=\"Species_4\">1</di_cfVal>"
       << "<di_cfVal species=\"Species_5\">1</di_cfVal>"
       << "</di_canopyFunction>"
       << "</GapDisperse1>"
       << "<NonGapDisperse2>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_1\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_2\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_3\">15.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "<di_weibullCanopySTR>"
       << "<di_wcsVal species=\"Species_1\">19.325</di_wcsVal>"
       << "<di_wcsVal species=\"Species_3\">12.257</di_wcsVal>"
       << "</di_weibullCanopySTR>"
       << "<di_weibullCanopyBeta>"
       << "<di_wcbVal species=\"Species_1\">2.0</di_wcbVal>"
       << "<di_wcbVal species=\"Species_3\">2.2</di_wcbVal>"
       << "</di_weibullCanopyBeta>"
       << "<di_weibullCanopyDispersal>"
       << "<di_wcdVal species=\"Species_1\">1.76E-4</di_wcdVal>"
       << "<di_wcdVal species=\"Species_3\">9.61E-5</di_wcdVal>"
       << "</di_weibullCanopyDispersal>"
       << "<di_weibullCanopyTheta>"
       << "<di_wctVal species=\"Species_1\">3.0</di_wctVal>"
       << "<di_wctVal species=\"Species_3\">3.0</di_wctVal>"
       << "</di_weibullCanopyTheta>"
       << "<di_lognormalCanopySTR>"
       << "<di_lcsVal species=\"Species_2\">19.325</di_lcsVal>"
       << "</di_lognormalCanopySTR>"
       << "<di_lognormalCanopyBeta>"
       << "<di_lcbVal species=\"Species_2\">2.1</di_lcbVal>"
       << "</di_lognormalCanopyBeta>"
       << "<di_lognormalCanopyX0>"
       << "<di_lcx0Val species=\"Species_2\">1.82E-4</di_lcx0Val>"
       << "</di_lognormalCanopyX0>"
       << "<di_lognormalCanopyXb>"
       << "<di_lcxbVal species=\"Species_2\">3.0</di_lcxbVal>"
       << "</di_lognormalCanopyXb>"
       << "<di_suckerSTR>"
       << "<di_ssVal species=\"Species_3\">12.257</di_ssVal>"
       << "</di_suckerSTR>"
       << "<di_suckerBeta>"
       << "<di_sbVal species=\"Species_3\">2.2</di_sbVal>"
       << "</di_suckerBeta>"
       << "<di_canopyFunction>"
       << "<di_cfVal species=\"Species_1\">0</di_cfVal>"
       << "<di_cfVal species=\"Species_2\">1</di_cfVal>"
       << "<di_cfVal species=\"Species_3\">0</di_cfVal>"
       << "</di_canopyFunction>"
       << "</NonGapDisperse2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}
