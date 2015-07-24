//---------------------------------------------------------------------------
// TestDimensionAnalysis.cpp
//---------------------------------------------------------------------------
#include "TestDimensionAnalysis.h"
#include <gtest/gtest.h>
#include <fstream>
#include <math.h>
#include "TreePopulation.h"
#include "SimManager.h"
#include "BehaviorBase.h"

////////////////////////////////////////////////////////////////////////////
// TestRun1()
// Performs test run 1. Tests equation 1, all possible units conversions.
// WriteDimensionAnalysisXMLFile1() does setup. This function creates three trees for each
// species, of varying sizes. The run goes for a timestep and then the
// function checks the biomass values.
////////////////////////////////////////////////////////////////////////////
TEST(DimensionAnalysis, TestRun1) {
  clTreePopulation * p_oPop;
  clTree **p_oTrees; //array to hold our target trees
  float fBiomass, fExpectedBiomass;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
  //Load our test file and get our tree population pointers
  p_oSimManager->ReadFile( WriteDimensionAnalysisXMLFile1() );
  p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
  int iCount = 0;

  //Create our trees
  p_oTrees = CreateDimensionAnalysisTrees(p_oPop);

  //Now do the run
  p_oSimManager->RunSim(1);

  //Check the biomass for each tree
  p_oTrees[0]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.262593268;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[1]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 25.07746237;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[2]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 98.92885413;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[3]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.005293412;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[4]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 1.360616499;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[5]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 7.231327365;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[6]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.000547159;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[7]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.234484182;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[8]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 1.453531672;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[9]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 9.03827E-05;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[10]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.000139857;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[11]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.0001595;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[12]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.008429464;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[13]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 12.15625879;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[14]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 108.580964;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[15]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.000234289;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[16]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.081424017;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[17]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.473881486;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[18]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.010435325;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[19]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 6.523880448;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[20]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 45.30914446;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[21]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 1.16112E-05;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[22]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.006993246;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[23]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.048026618;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[24]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 1.32636E-06;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[25]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.001488205;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[26]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.012325488;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[27]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.236570511;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[28]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 22.59230844;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[29]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 89.12509381;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[30]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.004726261;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[31]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 1.21483616;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[32]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 6.45654229;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[33]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.000483244;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[34]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.207093615;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[35]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 1.283741727;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[36]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 7.92831E-05;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[37]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.000122682;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[38]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.000139912;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[39]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.007329968;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[40]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 10.57065981;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[41]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 94.41822959;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[42]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.000201974;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[43]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.070193118;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[44]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.408518523;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[45]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.008919081;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[46]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 5.575966195;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[47]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 38.72576449;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[48]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 9.84004E-06;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[49]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.00592648;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[50]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.040700524;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[51]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 1.11459E-06;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[52]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.001250592;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[53]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.010357553;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);

  delete[] p_oTrees;
  delete p_oSimManager;
  } catch (modelErr &e) {
    delete[] p_oTrees;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestRun2()
// Performs test run 2. Tests equation 2, all possible units conversions.
// WriteDimensionAnalysisXMLFile2() does setup. This function creates three trees for each
// species, of varying sizes. The run goes for a timestep and then the
// function checks the biomass values.
////////////////////////////////////////////////////////////////////////////
TEST(DimensionAnalysis, TestRun2) {
  clTreePopulation * p_oPop;
  clTree **p_oTrees; //array to hold our target trees
  float fBiomass, fExpectedBiomass;
  int iCount = 0;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
  //Load our test file and get our tree population pointers
  p_oSimManager->ReadFile( WriteDimensionAnalysisXMLFile2() );
  p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

  //Create our trees
  p_oTrees = CreateDimensionAnalysisTrees(p_oPop);

  //Now do the run
  p_oSimManager->RunSim(1);

  //Check the biomass for each tree
  p_oTrees[0]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.000116236;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[1]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.043204535;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[2]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 20.37173309;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[3]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.002102813;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[4]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 1.229703912;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[5]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 8.370483652;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[6]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.008464555;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[7]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 1.450791369;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[8]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 9.096187004;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[9]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 1.38681E-05;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[10]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 5.72817E-05;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[11]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.000262058;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[12]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 3.71119E-05;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[13]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.006483925;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[14]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 1.174916652;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[15]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.008956691;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[16]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 2.750094286;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[17]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 15.41946796;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[18]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.000792491;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[19]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.283135579;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[20]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 1.661590596;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[21]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 2.1054E-06;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[22]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.000201275;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[23]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.000765836;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[24]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 2.66288E-05;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[25]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.013638237;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[26]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.032663775;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[27]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.000108631;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[28]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.04037807;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[29]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 19.03900289;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[30]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.001947049;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[31]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 1.138614733;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[32]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 7.750447826;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[33]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.007753153;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[34]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 1.328502106;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[35]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 8.326964584;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[36]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 1.26074E-05;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[37]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 5.20743E-05;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[38]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.000238235;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[39]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 3.09266E-05;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[40]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.005403271;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[41]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.97909721;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[42]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.004714048;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[43]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 1.447418045;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[44]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 8.115509455;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[45]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.000440273;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[46]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.157297544;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[47]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.923105887;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[48]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 1.23847E-06;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[49]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.000118397;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[50]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.000450492;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[51]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 1.6643E-05;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[52]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.008523898;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[53]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.020414859;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  delete[] p_oTrees;
  delete p_oSimManager;
  } catch (modelErr &e) {
    delete[] p_oTrees;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestRun3()
// Performs test run 3. Tests equation 3, all possible units conversions.
// WriteDimensionAnalysisXMLFile3() does setup. This function creates three trees for each
// species, of varying sizes. The run goes for a timestep and then the
// function checks the biomass values.
////////////////////////////////////////////////////////////////////////////
TEST(DimensionAnalysis, TestRun3) {
  clTreePopulation * p_oPop;
  clTree **p_oTrees; //array to hold our target trees
  float fBiomass, fExpectedBiomass;
  int iCount = 0;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
  //Load our test file and get our tree population pointers
  p_oSimManager->ReadFile( WriteDimensionAnalysisXMLFile3() );
  p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

  //Create our trees
  p_oTrees = CreateDimensionAnalysisTrees(p_oPop);

  //Now do the run
  p_oSimManager->RunSim(1);

  //Check the biomass for each tree
  p_oTrees[0]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.049347628;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[1]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 1.104755786;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[2]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 2.816156455;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[3]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.023429843;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[4]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 8.230180988;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[5]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 48.0533184;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[6]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.093809817;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[7]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 38.92676287;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[8]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 238.9707894;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[9]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.009392153;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[10]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.08866764;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[11]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.174288766;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[12]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.018839525;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[13]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 9.017163812;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[14]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 57.78702649;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[15]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.039163994;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[16]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.387049919;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[17]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.771357493;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[18]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 8.54293E-05;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[19]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.001830657;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[20]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.004605511;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[21]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 4.04538E-06;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[22]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 5.84736E-05;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[23]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.000130664;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[24]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.000379314;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[25]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.056234029;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[26]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.25324176;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[27]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.046119279;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[28]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 1.032482043;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[29]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 2.631921921;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[30]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.021694299;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[31]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 7.620537952;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[32]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 44.49381333;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[33]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.086064052;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[34]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 35.64166737;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[35]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 218.8036394;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[36]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.008538321;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[37]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.080606945;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[38]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.158444332;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[39]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.015699605;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[40]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 7.514303177;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[41]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 48.15585541;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[42]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.020612629;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[43]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.203710484;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[44]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.405977628;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[45]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 4.74607E-05;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[46]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.001017032;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[47]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.002558617;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[48]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 2.37964E-06;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[49]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 3.43962E-05;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[50]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 7.68609E-05;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[51]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.000237071;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[52]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.035146268;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[53]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.1582761;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  delete[] p_oTrees;
  delete p_oSimManager;
  } catch (modelErr &e) {
    delete[] p_oTrees;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestRun4()
// Performs test run 4. Tests equations 4 and 5, all possible units
// conversions. WriteDimensionAnalysisXMLFile4() does setup. This function creates three trees
// for each species, of varying sizes. The run goes for a timestep and then
// the function checks the biomass values.
////////////////////////////////////////////////////////////////////////////
TEST(DimensionAnalysis, TestRun4) {
  clTreePopulation * p_oPop;
  clTree **p_oTrees; //array to hold our target trees
  float fBiomass, fExpectedBiomass;
  int iCount = 0;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
  //Load our test file and get our tree population pointers
  p_oSimManager->ReadFile( WriteDimensionAnalysisXMLFile4() );
  p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

  //Create our trees
  p_oTrees = CreateDimensionAnalysisTrees(p_oPop);

  //Now do the run
  p_oSimManager->RunSim(1);

  //Check the biomass for each tree
  p_oTrees[0]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.0030516;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[1]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.9138966;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[2]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 3.8781966;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[3]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.005568986;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[4]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.014609336;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[5]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.024625594;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[6]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.004904483;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[7]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.008860406;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[8]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.013218323;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[9]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.00444215;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[10]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.999416059;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[11]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 4.413157655;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[12]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.002546344;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[13]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.008269498;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[14]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.014626656;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[15]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.00213353;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[16]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.004551647;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[17]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.007236249;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[18]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 3.87345E-05;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[19]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.006845448;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[20]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.031672574;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[21]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 7.58771E-05;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[22]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.008885146;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[23]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.038058037;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[24]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 1.72038E-05;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[25]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.019387919;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[26]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.178108663;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[27]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.1183;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[28]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 113.1448;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[29]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 902.6848;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[30]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.1899359;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[31]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 132.0991334;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[32]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 1028.414883;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[33]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.007027093;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[34]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 7.594950237;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[35]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 58.46478623;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[36]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.0307585;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[37]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 53.419456;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[38]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 427.050106;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[39]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.0807212;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[40]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 57.3214952;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[41]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 447.2008052;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[42]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.003718217;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[43]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 3.684205251;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[44]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 28.34456399;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[45]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.1393941;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[46]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 137.6877441;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[47]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 1100.750494;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[48]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.0002322;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[49]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.1697742;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[50]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 1.3290542;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[51]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 1.21879E-05;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[52]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.010240541;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[53]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.079091545;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);

  delete[] p_oTrees;
  delete p_oSimManager;
  } catch (modelErr &e) {
    delete[] p_oTrees;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestRun5()
// Performs test run 5.  Tests equations 6 and 7, all possible units
// conversions. WriteDimensionAnalysisXMLFile5() does setup.  This function creates three trees
// for each species, of varying sizes.  The run goes for a timestep and then
// the function checks the biomass values.
////////////////////////////////////////////////////////////////////////////
TEST(DimensionAnalysis, TestRun5) {
  clTreePopulation * p_oPop;
  clTree **p_oTrees; //array to hold our target trees
  float fBiomass, fExpectedBiomass;
  int iCount = 0;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
  //Load our test file and get our tree population pointers
  p_oSimManager->ReadFile( WriteDimensionAnalysisXMLFile5() );
  p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

  //Create our trees
  p_oTrees = CreateDimensionAnalysisTrees(p_oPop);

  //Now do the run
  p_oSimManager->RunSim(1);

  //Check the biomass for each tree
  p_oTrees[0]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.023218013;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[1]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.029851078;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[2]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.015530325;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[3]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.002061419;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[4]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.022309581;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[5]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 1.74991208;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[6]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.016855478;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[7]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 12.07122587;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[8]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 3166.719494;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[9]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 7.309737871;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[10]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.000169079;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[11]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 7.49317E-10;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[12]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.013057889;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[13]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.327618001;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[14]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 1.998871641;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[15]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.005609392;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[16]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 1.690156398;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[17]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 455.3561866;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[18]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.000165829;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[19]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.004164969;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[20]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.024509522;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[21]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.000163652;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[22]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.118404482;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[23]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 4.43169759;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[24]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 1.12577E-05;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[25]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.000193939;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[26]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.000723197;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[27]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.001779949;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[28]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.002797013;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[29]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.003249092;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[30]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.003669494;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[31]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 1.43716913;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[32]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 6.115769916;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[33]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.000749552;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[34]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.000810932;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[35]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.000841389;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[36]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 2.65663498;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[37]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 6.507032962;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[38]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 6.512344084;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[39]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.000450766;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[40]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.000721167;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[41]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.000979842;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[42]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.000215318;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[43]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.000226049;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[44]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.000229904;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[45]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 7.07191E-05;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[46]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.002970481;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[47]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.007077495;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[48]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 4.5507E-07;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[49]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 7.71019E-07;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[50]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 9.27791E-07;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[51]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 3.56336E-08;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[52]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 1.00429E-07;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[53]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 1.3719E-07;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  delete[] p_oTrees;
  delete p_oSimManager;
  } catch (modelErr &e) {
    delete[] p_oTrees;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestRun6()
// Performs test run 6. Tests equation 8, all possible units conversions.
// WriteDimensionAnalysisXMLFile6() does setup. This function creates three trees for each
// species, of varying sizes. The run goes for a timestep and then the
// function checks the biomass values.
////////////////////////////////////////////////////////////////////////////
TEST(DimensionAnalysis, TestRun6) {
  clTreePopulation * p_oPop;
  clTree **p_oTrees; //array to hold our target trees
  float fBiomass, fExpectedBiomass;
  int iCount = 0;
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
  //Load our test file and get our tree population pointers
  p_oSimManager->ReadFile( WriteDimensionAnalysisXMLFile6() );
  p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

  //Create our trees
  p_oTrees = CreateDimensionAnalysisTrees(p_oPop);

  //Now do the run
  p_oSimManager->RunSim(1);

  //Check the biomass for each tree
  p_oTrees[0]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.051033761;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[1]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.017695286;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[2]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.012864229;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[3]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.001985721;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[4]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.000657534;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[5]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.000471437;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[6]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.00489997;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[7]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.001549506;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[8]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.001095667;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[9]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.000653107;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[10]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.000197235;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[11]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.000137546;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[12]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.003620706;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[13]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.001044223;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[14]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.000718186;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[15]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.014822053;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[16]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.004082332;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[17]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.002769055;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[18]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.467595047;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[19]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.122990029;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[20]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.082275874;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[21]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 4.08382E-05;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[22]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 1.02581E-05;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[23]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 6.76782E-06;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[24]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.000105137;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[25]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 2.52206E-05;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[26]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 1.64103E-05;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[27]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.047695104;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[28]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.01653765;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[29]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.012022644;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[30]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.00183863;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[31]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.000608828;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[32]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.000436516;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[33]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.004497093;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[34]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.001422106;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[35]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.001005581;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[36]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.000593733;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[37]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.000179305;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[38]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.000125042;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[39]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.003017255;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[40]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.000870186;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[41]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.000598489;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[42]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.007801081;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[43]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.002148596;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[44]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.001457397;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[45]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.259775026;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[46]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.068327794;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[47]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.045708819;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[48]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 2.40225E-05;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[49]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 6.03418E-06;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[50]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 3.98107E-06;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[51]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 6.57106E-05;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[52]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 1.57629E-05;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[53]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 1.02564E-05;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);

  delete[] p_oTrees;
  delete p_oSimManager;
  } catch (modelErr &e) {
    delete[] p_oTrees;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestRun7()
// Performs test run 7. Tests equation 9, all possible units conversions.
// WriteDimensionAnalysisXMLFile7() does setup. This function creates three trees for each
// species, of varying sizes. The run goes for a timestep and then the
// function checks the biomass values.
////////////////////////////////////////////////////////////////////////////
TEST(DimensionAnalysis, TestRun7) {
  clTreePopulation * p_oPop;
  clTree **p_oTrees; //array to hold our target trees
  float fBiomass, fExpectedBiomass;
  int iCount = 0;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
  //Load our test file and get our tree population pointers
  p_oSimManager->ReadFile( WriteDimensionAnalysisXMLFile7() );
  p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

  //Create our trees
  p_oTrees = CreateDimensionAnalysisTrees(p_oPop);

  //Now do the run
  p_oSimManager->RunSim(1);

  //Check the biomass for each tree
  p_oTrees[0]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.024746649;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[1]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.139160632;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[2]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.234039353;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[3]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.001066063;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[4]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.005858451;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[5]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.009784644;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[6]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.000724997;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[7]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.004076957;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[8]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.006856597;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[9]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.004882427;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[10]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.028095434;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[11]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.047579354;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[12]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.001128743;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[13]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.006646534;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[14]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.011334134;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[15]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.001024687;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[16]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.006174349;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[17]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.010602165;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[18]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.000126651;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[19]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.000780924;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[20]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.001350276;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[21]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 5.54456E-06;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[22]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 3.49838E-05;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[23]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 6.09104E-05;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[24]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 2.7693E-06;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[25]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 1.78801E-05;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[26]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 3.13476E-05;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[27]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.021387165;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[28]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.114855875;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[29]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.190504444;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[30]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.000987095;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[31]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.005424492;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[32]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.009059855;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[33]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.000664756;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[34]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.003738197;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[35]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.006286873;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[36]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.00443857;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[37]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.025541304;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[38]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.043253958;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[39]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.00094062;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[40]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.005538779;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[41]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.009445112;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[42]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.000539309;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[43]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.003249657;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[44]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.005580087;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[45]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 7.03617E-05;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[46]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.000433847;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[47]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.000750153;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[48]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 3.26151E-06;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[49]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 2.05787E-05;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[50]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 3.58296E-05;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[51]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 1.73081E-06;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[52]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 1.11751E-05;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[53]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 1.95923E-05;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  delete[] p_oTrees;
  delete p_oSimManager;
  } catch (modelErr &e) {
    delete[] p_oTrees;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestRun8()
// Performs test run 8. Tests "dia" = DBH^2. WriteDimensionAnalysisXMLFile8() does setup. This
// function creates three trees for each species, of varying sizes. The run
// goes for a timestep and then the function checks the biomass values.
////////////////////////////////////////////////////////////////////////////
TEST(DimensionAnalysis, TestRun8) {
  clTreePopulation * p_oPop;
  clTree **p_oTrees; //array to hold our target trees
  float fBiomass, fExpectedBiomass;
  int iCount = 0;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
  //Load our test file and get our tree population pointers
  p_oSimManager->ReadFile( WriteDimensionAnalysisXMLFile8() );
  p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

  //Create our trees
  p_oTrees = CreateDimensionAnalysisTrees(p_oPop);

  //Now do the run
  p_oSimManager->RunSim(1);

  //Check the biomass for each tree
  p_oTrees[0]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.368633583;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[1]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 5.842448568;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[2]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 13.42242212;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[3]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.009595183;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[4]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.504739088;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[5]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 2.004815479;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[6]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.005338012;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[7]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.090046108;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[8]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.346295817;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[9]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.29705447;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[10]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 29.51195447;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[11]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 118.0419545;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[12]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.005090511;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[13]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.319723272;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[14]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 1.273129457;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[15]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.006808356;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[16]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 1.081838033;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[17]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 4.974682746;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[18]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.01052901;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[19]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 1.052504012;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[20]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 4.210004012;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[21]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.002078194;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[22]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 32.80126682;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[23]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 602.8543482;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[24]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 0.000112571;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[25]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 269.5950899;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  p_oTrees[26]->GetValue(p_oPop->GetFloatDataCode("Biomass", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fBiomass);
  fExpectedBiomass = 22766.89788;
  EXPECT_LT(fabs(fExpectedBiomass - fBiomass)/fExpectedBiomass, 0.1);
  iCount++;

  delete[] p_oTrees;
  delete p_oSimManager;
  } catch (modelErr &e) {
    delete[] p_oTrees;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// CreateDimensionAnalysisTrees()
////////////////////////////////////////////////////////////////////////////
clTree** CreateDimensionAnalysisTrees(clTreePopulation *p_oPop) {
  clTree **p_oTrees; //array to hold our target trees
  float fDiam;
  int iSpecies, iNumTrees = 54, iCount;

  //Create the array of target trees
  p_oTrees = new clTree*[iNumTrees];

  //Create our trees
  iCount = 0;

  //Species 1
  iSpecies = 0;
  fDiam = 5;
  p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::sapling, fDiam);
  iCount++;

  fDiam = 50;
  p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
  iCount++;

  fDiam = 100;
  p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
  iCount++;

  //Species 2
  iSpecies = 1;
  fDiam = 5;
  p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::sapling, fDiam);
  iCount++;

  fDiam = 50;
  p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
  iCount++;

  fDiam = 100;
  p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
  iCount++;

  //Species 3
  iSpecies = 2;
  fDiam = 5;
  p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::sapling, fDiam);
  iCount++;

  fDiam = 50;
  p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
  iCount++;

  fDiam = 100;
  p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
  iCount++;

  //Species 4
  iSpecies = 3;
  fDiam = 5;
  p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::sapling, fDiam);
  iCount++;

  fDiam = 50;
  p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
  iCount++;

  fDiam = 100;
  p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
  iCount++;

  //Species 5
  iSpecies = 4;
  fDiam = 5;
  p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::sapling, fDiam);
  iCount++;

  fDiam = 50;
  p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
  iCount++;

  fDiam = 100;
  p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
  iCount++;

  //Species 6
  iSpecies = 5;
  fDiam = 5;
  p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::sapling, fDiam);
  iCount++;

  fDiam = 50;
  p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
  iCount++;

  fDiam = 100;
  p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
  iCount++;

  //Species 7
  iSpecies = 6;
  fDiam = 5;
  p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::sapling, fDiam);
  iCount++;

  fDiam = 50;
  p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
  iCount++;

  fDiam = 100;
  p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
  iCount++;

  //Species 8
  iSpecies = 7;
  fDiam = 5;
  p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::sapling, fDiam);
  iCount++;

  fDiam = 50;
  p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
  iCount++;

  fDiam = 100;
  p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
  iCount++;

  //Species 9
  iSpecies = 8;
  fDiam = 5;
  p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::sapling, fDiam);
  iCount++;

  fDiam = 50;
  p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
  iCount++;

  fDiam = 100;
  p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
  iCount++;

  //Species 10
  iSpecies = 9;
  fDiam = 5;
  p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::sapling, fDiam);
  iCount++;

  fDiam = 50;
  p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
  iCount++;

  fDiam = 100;
  p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
  iCount++;

  //Species 11
  iSpecies = 10;
  fDiam = 5;
  p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::sapling, fDiam);
  iCount++;

  fDiam = 50;
  p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
  iCount++;

  fDiam = 100;
  p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
  iCount++;

  //Species 12
  iSpecies = 11;
  fDiam = 5;
  p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::sapling, fDiam);
  iCount++;

  fDiam = 50;
  p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
  iCount++;

  fDiam = 100;
  p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
  iCount++;

  //No species 13

  //Species 14
  iSpecies = 13;
  fDiam = 5;
  p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::sapling, fDiam);
  iCount++;

  fDiam = 50;
  p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
  iCount++;

  fDiam = 100;
  p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
  iCount++;

  //Species 15
  iSpecies = 14;
  fDiam = 5;
  p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::sapling, fDiam);
  iCount++;

  fDiam = 50;
  p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
  iCount++;

  fDiam = 100;
  p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
  iCount++;

  //Species 16
  iSpecies = 15;
  fDiam = 5;
  p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::sapling, fDiam);
  iCount++;

  fDiam = 50;
  p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
  iCount++;

  fDiam = 100;
  p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
  iCount++;

  //Species 17
  iSpecies = 16;
  fDiam = 5;
  p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::sapling, fDiam);
  iCount++;

  fDiam = 50;
  p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
  iCount++;

  fDiam = 100;
  p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
  iCount++;

  //Species 18
  iSpecies = 17;
  fDiam = 5;
  p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::sapling, fDiam);
  iCount++;

  fDiam = 50;
  p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
  iCount++;

  fDiam = 100;
  p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
  iCount++;

  //Species 19
  iSpecies = 18;
  fDiam = 5;
  p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::sapling, fDiam);
  iCount++;

  fDiam = 50;
  p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
  iCount++;

  fDiam = 100;
  p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
  iCount++;

  return p_oTrees;
}

////////////////////////////////////////////////////////////////////////////
// TestErrorProcessing()
////////////////////////////////////////////////////////////////////////////
TEST(DimensionAnalysis, TestErrorProcessing) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try
  {
    p_oSimManager->ReadFile(WriteDimensionAnalysisXMLErrorFile1());
    FAIL() << "TestDimensionAnalysis error processing didn't catch error for WriteDimensionAnalysisXMLErrorFile1.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clDimensionAnalysis::GetData") != 0)
    {
      FAIL() << "TestDimensionAnalysis error processing caught wrong error for WriteDimensionAnalysisXMLErrorFile1.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteDimensionAnalysisXMLErrorFile2());
    FAIL() << "TestDimensionAnalysis error processing didn't catch error for WriteDimensionAnalysisXMLErrorFile2.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clDimensionAnalysis::GetData") != 0)
    {
      FAIL() << "TestDimensionAnalysis error processing caught wrong error for WriteDimensionAnalysisXMLErrorFile2.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteDimensionAnalysisXMLErrorFile3());
    FAIL() << "TestDimensionAnalysis error processing didn't catch error for WriteDimensionAnalysisXMLErrorFile3.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clDimensionAnalysis::RegisterTreeDataMembers") != 0)
    {
      FAIL() << "TestDimensionAnalysis error processing caught wrong error for WriteDimensionAnalysisXMLErrorFile3.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteDimensionAnalysisXMLErrorFile4());
    FAIL() << "TestDimensionAnalysis error processing didn't catch error for WriteDimensionAnalysisXMLErrorFile4.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clDimensionAnalysis::GetData") != 0)
    {
      FAIL() << "TestDimensionAnalysis error processing caught wrong error for WriteDimensionAnalysisXMLErrorFile4.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteDimensionAnalysisXMLErrorFile5());
    FAIL() << "TestDimensionAnalysis error processing didn't catch error for WriteDimensionAnalysisXMLErrorFile5.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("FillSpeciesSpecificValue(bool)") != 0)
    {
      FAIL() << "TestDimensionAnalysis error processing caught wrong error for WriteDimensionAnalysisXMLErrorFile5.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteDimensionAnalysisXMLErrorFile6());
    FAIL() << "TestDimensionAnalysis error processing didn't catch error for WriteDimensionAnalysisXMLErrorFile6.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clDimensionAnalysis::GetData") != 0)
    {
      FAIL() << "TestDimensionAnalysis error processing caught wrong error for WriteDimensionAnalysisXMLErrorFile6.";
    }
    ;
  }
  delete p_oSimManager;
}

////////////////////////////////////////////////////////////////////////////
// WriteDimensionAnalysisXMLFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteDimensionAnalysisXMLFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteDimensionAnalysisCommonStuff(oOut);

  oOut << "<DimensionAnalysis1>"
       << "<bi_a>"
       << "<bi_aVal species=\"Species_1\">-0.99</bi_aVal>"
       << "<bi_aVal species=\"Species_2\">-1.01</bi_aVal>"
       << "<bi_aVal species=\"Species_3\">-1.09</bi_aVal>"
       << "<bi_aVal species=\"Species_4\">-1.08</bi_aVal>"
       << "<bi_aVal species=\"Species_5\">-1</bi_aVal>"
       << "<bi_aVal species=\"Species_6\">-1.1</bi_aVal>"
       << "<bi_aVal species=\"Species_7\">-0.8</bi_aVal>"
       << "<bi_aVal species=\"Species_8\">-0.95</bi_aVal>"
       << "<bi_aVal species=\"Species_9\">-0.85</bi_aVal>"
       << "<bi_aVal species=\"Species_10\">-0.99</bi_aVal>"
       << "<bi_aVal species=\"Species_11\">-1.01</bi_aVal>"
       << "<bi_aVal species=\"Species_12\">-1.09</bi_aVal>"
       << "<bi_aVal species=\"Species_14\">-1.08</bi_aVal>"
       << "<bi_aVal species=\"Species_15\">-1</bi_aVal>"
       << "<bi_aVal species=\"Species_16\">-1.1</bi_aVal>"
       << "<bi_aVal species=\"Species_17\">-0.8</bi_aVal>"
       << "<bi_aVal species=\"Species_18\">-0.95</bi_aVal>"
       << "<bi_aVal species=\"Species_19\">-0.85</bi_aVal>"
       << "</bi_a>"
       << "<bi_b>"
       << "<bi_bVal species=\"Species_1\">2.2</bi_bVal>"
       << "<bi_bVal species=\"Species_2\">2.41</bi_bVal>"
       << "<bi_bVal species=\"Species_3\">2.35</bi_bVal>"
       << "<bi_bVal species=\"Species_4\">2.37</bi_bVal>"
       << "<bi_bVal species=\"Species_5\">2.43</bi_bVal>"
       << "<bi_bVal species=\"Species_6\">2.31</bi_bVal>"
       << "<bi_bVal species=\"Species_7\">2.33</bi_bVal>"
       << "<bi_bVal species=\"Species_8\">2.46</bi_bVal>"
       << "<bi_bVal species=\"Species_9\">2.44</bi_bVal>"
       << "<bi_bVal species=\"Species_10\">2.2</bi_bVal>"
       << "<bi_bVal species=\"Species_11\">2.41</bi_bVal>"
       << "<bi_bVal species=\"Species_12\">2.35</bi_bVal>"
       << "<bi_bVal species=\"Species_14\">2.37</bi_bVal>"
       << "<bi_bVal species=\"Species_15\">2.43</bi_bVal>"
       << "<bi_bVal species=\"Species_16\">2.31</bi_bVal>"
       << "<bi_bVal species=\"Species_17\">2.33</bi_bVal>"
       << "<bi_bVal species=\"Species_18\">2.46</bi_bVal>"
       << "<bi_bVal species=\"Species_19\">2.44</bi_bVal>"
       << "</bi_b>"
       << "<bi_c>"
       << "<bi_cVal species=\"Species_1\">0.9</bi_cVal>"
       << "<bi_cVal species=\"Species_2\">1</bi_cVal>"
       << "<bi_cVal species=\"Species_3\">1.12</bi_cVal>"
       << "<bi_cVal species=\"Species_4\">0.08</bi_cVal>"
       << "<bi_cVal species=\"Species_5\">1.3</bi_cVal>"
       << "<bi_cVal species=\"Species_6\">1.1</bi_cVal>"
       << "<bi_cVal species=\"Species_7\">1.2</bi_cVal>"
       << "<bi_cVal species=\"Species_8\">1.13</bi_cVal>"
       << "<bi_cVal species=\"Species_9\">1.25</bi_cVal>"
       << "<bi_cVal species=\"Species_10\">0.9</bi_cVal>"
       << "<bi_cVal species=\"Species_11\">1</bi_cVal>"
       << "<bi_cVal species=\"Species_12\">1.12</bi_cVal>"
       << "<bi_cVal species=\"Species_14\">0.08</bi_cVal>"
       << "<bi_cVal species=\"Species_15\">1.3</bi_cVal>"
       << "<bi_cVal species=\"Species_16\">1.1</bi_cVal>"
       << "<bi_cVal species=\"Species_17\">1.2</bi_cVal>"
       << "<bi_cVal species=\"Species_18\">1.13</bi_cVal>"
       << "<bi_cVal species=\"Species_19\">1.25</bi_cVal>"
       << "</bi_c>"
       << "<bi_d>"
       << "<bi_dVal species=\"Species_1\">1</bi_dVal>"
       << "<bi_dVal species=\"Species_2\">1</bi_dVal>"
       << "<bi_dVal species=\"Species_3\">1</bi_dVal>"
       << "<bi_dVal species=\"Species_4\">1</bi_dVal>"
       << "<bi_dVal species=\"Species_5\">1</bi_dVal>"
       << "<bi_dVal species=\"Species_6\">1</bi_dVal>"
       << "<bi_dVal species=\"Species_7\">1</bi_dVal>"
       << "<bi_dVal species=\"Species_8\">1</bi_dVal>"
       << "<bi_dVal species=\"Species_9\">1</bi_dVal>"
       << "<bi_dVal species=\"Species_10\">1</bi_dVal>"
       << "<bi_dVal species=\"Species_11\">1</bi_dVal>"
       << "<bi_dVal species=\"Species_12\">1</bi_dVal>"
       << "<bi_dVal species=\"Species_14\">1</bi_dVal>"
       << "<bi_dVal species=\"Species_15\">1</bi_dVal>"
       << "<bi_dVal species=\"Species_16\">1</bi_dVal>"
       << "<bi_dVal species=\"Species_17\">1</bi_dVal>"
       << "<bi_dVal species=\"Species_18\">1</bi_dVal>"
       << "<bi_dVal species=\"Species_19\">1</bi_dVal>"
       << "</bi_d>"
       << "<bi_e>"
       << "<bi_eVal species=\"Species_1\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_2\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_3\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_4\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_5\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_6\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_7\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_8\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_9\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_10\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_11\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_12\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_14\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_15\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_16\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_17\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_18\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_19\">0</bi_eVal>"
       << "</bi_e>"
       << "<bi_eqID>"
       << "<bi_eiVal species=\"Species_1\">1</bi_eiVal>"
       << "<bi_eiVal species=\"Species_2\">1</bi_eiVal>"
       << "<bi_eiVal species=\"Species_3\">1</bi_eiVal>"
       << "<bi_eiVal species=\"Species_4\">1</bi_eiVal>"
       << "<bi_eiVal species=\"Species_5\">1</bi_eiVal>"
       << "<bi_eiVal species=\"Species_6\">1</bi_eiVal>"
       << "<bi_eiVal species=\"Species_7\">1</bi_eiVal>"
       << "<bi_eiVal species=\"Species_8\">1</bi_eiVal>"
       << "<bi_eiVal species=\"Species_9\">1</bi_eiVal>"
       << "<bi_eiVal species=\"Species_10\">1</bi_eiVal>"
       << "<bi_eiVal species=\"Species_11\">1</bi_eiVal>"
       << "<bi_eiVal species=\"Species_12\">1</bi_eiVal>"
       << "<bi_eiVal species=\"Species_14\">1</bi_eiVal>"
       << "<bi_eiVal species=\"Species_15\">1</bi_eiVal>"
       << "<bi_eiVal species=\"Species_16\">1</bi_eiVal>"
       << "<bi_eiVal species=\"Species_17\">1</bi_eiVal>"
       << "<bi_eiVal species=\"Species_18\">1</bi_eiVal>"
       << "<bi_eiVal species=\"Species_19\">1</bi_eiVal>"
       << "</bi_eqID>"
       << "<bi_dbhUnits>"
       << "<bi_duVal species=\"Species_1\">0</bi_duVal>"
       << "<bi_duVal species=\"Species_2\">1</bi_duVal>"
       << "<bi_duVal species=\"Species_3\">2</bi_duVal>"
       << "<bi_duVal species=\"Species_4\">0</bi_duVal>"
       << "<bi_duVal species=\"Species_5\">1</bi_duVal>"
       << "<bi_duVal species=\"Species_6\">2</bi_duVal>"
       << "<bi_duVal species=\"Species_7\">0</bi_duVal>"
       << "<bi_duVal species=\"Species_8\">1</bi_duVal>"
       << "<bi_duVal species=\"Species_9\">2</bi_duVal>"
       << "<bi_duVal species=\"Species_10\">0</bi_duVal>"
       << "<bi_duVal species=\"Species_11\">1</bi_duVal>"
       << "<bi_duVal species=\"Species_12\">2</bi_duVal>"
       << "<bi_duVal species=\"Species_14\">0</bi_duVal>"
       << "<bi_duVal species=\"Species_15\">1</bi_duVal>"
       << "<bi_duVal species=\"Species_16\">2</bi_duVal>"
       << "<bi_duVal species=\"Species_17\">0</bi_duVal>"
       << "<bi_duVal species=\"Species_18\">1</bi_duVal>"
       << "<bi_duVal species=\"Species_19\">2</bi_duVal>"
       << "</bi_dbhUnits>"
       << "<bi_biomassUnits>"
       << "<bi_buVal species=\"Species_1\">1</bi_buVal>"
       << "<bi_buVal species=\"Species_2\">1</bi_buVal>"
       << "<bi_buVal species=\"Species_3\">1</bi_buVal>"
       << "<bi_buVal species=\"Species_4\">2</bi_buVal>"
       << "<bi_buVal species=\"Species_5\">2</bi_buVal>"
       << "<bi_buVal species=\"Species_6\">2</bi_buVal>"
       << "<bi_buVal species=\"Species_7\">0</bi_buVal>"
       << "<bi_buVal species=\"Species_8\">0</bi_buVal>"
       << "<bi_buVal species=\"Species_9\">0</bi_buVal>"
       << "<bi_buVal species=\"Species_10\">1</bi_buVal>"
       << "<bi_buVal species=\"Species_11\">1</bi_buVal>"
       << "<bi_buVal species=\"Species_12\">1</bi_buVal>"
       << "<bi_buVal species=\"Species_14\">2</bi_buVal>"
       << "<bi_buVal species=\"Species_15\">2</bi_buVal>"
       << "<bi_buVal species=\"Species_16\">2</bi_buVal>"
       << "<bi_buVal species=\"Species_17\">0</bi_buVal>"
       << "<bi_buVal species=\"Species_18\">0</bi_buVal>"
       << "<bi_buVal species=\"Species_19\">0</bi_buVal>"
       << "</bi_biomassUnits>"
       << "<bi_useCorrectionFactor>"
       << "<bi_ucfVal species=\"Species_1\">1</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_2\">1</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_3\">1</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_4\">1</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_5\">1</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_6\">1</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_7\">1</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_8\">1</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_9\">1</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_10\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_11\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_12\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_14\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_15\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_16\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_17\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_18\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_19\">0</bi_ucfVal>"
       << "</bi_useCorrectionFactor>"
       << "<bi_correctionFactorValue>"
       << "<bi_cfvVal species=\"Species_1\">1.11</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_2\">1.12</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_3\">1.13</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_4\">1.14</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_5\">1.15</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_6\">1.16</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_7\">1.17</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_8\">1.18</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_9\">1.19</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_10\">1</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_11\">1</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_12\">1</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_14\">1</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_15\">1</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_16\">1</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_17\">1</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_18\">1</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_19\">1</bi_cfvVal>"
       << "</bi_correctionFactorValue>"
       << "<bi_whatDia>"
       << "<bi_wdVal species=\"Species_1\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_2\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_3\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_4\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_5\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_6\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_7\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_8\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_9\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_10\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_11\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_12\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_14\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_15\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_16\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_17\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_18\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_19\">0</bi_wdVal>"
       << "</bi_whatDia>"
       << "</DimensionAnalysis1>"
       << "</paramFile>";

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteDimensionAnalysisXMLFile2()
////////////////////////////////////////////////////////////////////////////
const char* WriteDimensionAnalysisXMLFile2() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteDimensionAnalysisCommonStuff(oOut);

  oOut << "<DimensionAnalysis1>"
       << "<bi_a>"
       << "<bi_aVal species=\"Species_1\">-3.7</bi_aVal>"
       << "<bi_aVal species=\"Species_2\">-3.787</bi_aVal>"
       << "<bi_aVal species=\"Species_3\">0.6</bi_aVal>"
       << "<bi_aVal species=\"Species_4\">-3.85</bi_aVal>"
       << "<bi_aVal species=\"Species_5\">-3.65</bi_aVal>"
       << "<bi_aVal species=\"Species_6\">0.6538</bi_aVal>"
       << "<bi_aVal species=\"Species_7\">-3.9</bi_aVal>"
       << "<bi_aVal species=\"Species_8\">-3</bi_aVal>"
       << "<bi_aVal species=\"Species_9\">0.75</bi_aVal>"
       << "<bi_aVal species=\"Species_10\">-3.7</bi_aVal>"
       << "<bi_aVal species=\"Species_11\">-3.787</bi_aVal>"
       << "<bi_aVal species=\"Species_12\">0.6</bi_aVal>"
       << "<bi_aVal species=\"Species_14\">-3.85</bi_aVal>"
       << "<bi_aVal species=\"Species_15\">-3.65</bi_aVal>"
       << "<bi_aVal species=\"Species_16\">0.6538</bi_aVal>"
       << "<bi_aVal species=\"Species_17\">-3.9</bi_aVal>"
       << "<bi_aVal species=\"Species_18\">-3</bi_aVal>"
       << "<bi_aVal species=\"Species_19\">0.75</bi_aVal>"
       << "</bi_a>"
       << "<bi_b>"
       << "<bi_bVal species=\"Species_1\">0.012</bi_bVal>"
       << "<bi_bVal species=\"Species_2\">0</bi_bVal>"
       << "<bi_bVal species=\"Species_3\">0.02</bi_bVal>"
       << "<bi_bVal species=\"Species_4\">0.003</bi_bVal>"
       << "<bi_bVal species=\"Species_5\">0.1</bi_bVal>"
       << "<bi_bVal species=\"Species_6\">0</bi_bVal>"
       << "<bi_bVal species=\"Species_7\">0</bi_bVal>"
       << "<bi_bVal species=\"Species_8\">-0.001</bi_bVal>"
       << "<bi_bVal species=\"Species_9\">-0.07</bi_bVal>"
       << "<bi_bVal species=\"Species_10\">0.012</bi_bVal>"
       << "<bi_bVal species=\"Species_11\">0</bi_bVal>"
       << "<bi_bVal species=\"Species_12\">0.02</bi_bVal>"
       << "<bi_bVal species=\"Species_14\">0.003</bi_bVal>"
       << "<bi_bVal species=\"Species_15\">0.1</bi_bVal>"
       << "<bi_bVal species=\"Species_16\">0</bi_bVal>"
       << "<bi_bVal species=\"Species_17\">0</bi_bVal>"
       << "<bi_bVal species=\"Species_18\">-0.001</bi_bVal>"
       << "<bi_bVal species=\"Species_19\">-0.07</bi_bVal>"
       << "</bi_b>"
       << "<bi_c>"
       << "<bi_cVal species=\"Species_1\">2.5</bi_cVal>"
       << "<bi_cVal species=\"Species_2\">2.767</bi_cVal>"
       << "<bi_cVal species=\"Species_3\">2.6</bi_cVal>"
       << "<bi_cVal species=\"Species_4\">2.7</bi_cVal>"
       << "<bi_cVal species=\"Species_5\">2.4</bi_cVal>"
       << "<bi_cVal species=\"Species_6\">2.4872</bi_cVal>"
       << "<bi_cVal species=\"Species_7\">2.3</bi_cVal>"
       << "<bi_cVal species=\"Species_8\">2</bi_cVal>"
       << "<bi_cVal species=\"Species_9\">2.9</bi_cVal>"
       << "<bi_cVal species=\"Species_10\">2.5</bi_cVal>"
       << "<bi_cVal species=\"Species_11\">2.767</bi_cVal>"
       << "<bi_cVal species=\"Species_12\">2.6</bi_cVal>"
       << "<bi_cVal species=\"Species_14\">2.7</bi_cVal>"
       << "<bi_cVal species=\"Species_15\">2.4</bi_cVal>"
       << "<bi_cVal species=\"Species_16\">2.4872</bi_cVal>"
       << "<bi_cVal species=\"Species_17\">2.3</bi_cVal>"
       << "<bi_cVal species=\"Species_18\">2</bi_cVal>"
       << "<bi_cVal species=\"Species_19\">2.9</bi_cVal>"
       << "</bi_c>"
       << "<bi_d>"
       << "<bi_dVal species=\"Species_1\">0.09</bi_dVal>"
       << "<bi_dVal species=\"Species_2\">1</bi_dVal>"
       << "<bi_dVal species=\"Species_3\">0.8</bi_dVal>"
       << "<bi_dVal species=\"Species_4\">0.011</bi_dVal>"
       << "<bi_dVal species=\"Species_5\">0.12</bi_dVal>"
       << "<bi_dVal species=\"Species_6\">1</bi_dVal>"
       << "<bi_dVal species=\"Species_7\">1.11</bi_dVal>"
       << "<bi_dVal species=\"Species_8\">1</bi_dVal>"
       << "<bi_dVal species=\"Species_9\">1.12</bi_dVal>"
       << "<bi_dVal species=\"Species_10\">0.09</bi_dVal>"
       << "<bi_dVal species=\"Species_11\">1</bi_dVal>"
       << "<bi_dVal species=\"Species_12\">0.8</bi_dVal>"
       << "<bi_dVal species=\"Species_14\">0.011</bi_dVal>"
       << "<bi_dVal species=\"Species_15\">0.12</bi_dVal>"
       << "<bi_dVal species=\"Species_16\">1</bi_dVal>"
       << "<bi_dVal species=\"Species_17\">1.11</bi_dVal>"
       << "<bi_dVal species=\"Species_18\">1</bi_dVal>"
       << "<bi_dVal species=\"Species_19\">1.12</bi_dVal>"
       << "</bi_d>"
       << "<bi_e>"
       << "<bi_eVal species=\"Species_1\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_2\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_3\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_4\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_5\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_6\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_7\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_8\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_9\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_10\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_11\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_12\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_14\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_15\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_16\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_17\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_18\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_19\">0</bi_eVal>"
       << "</bi_e>"
       << "<bi_eqID>"
       << "<bi_eiVal species=\"Species_1\">2</bi_eiVal>"
       << "<bi_eiVal species=\"Species_2\">2</bi_eiVal>"
       << "<bi_eiVal species=\"Species_3\">2</bi_eiVal>"
       << "<bi_eiVal species=\"Species_4\">2</bi_eiVal>"
       << "<bi_eiVal species=\"Species_5\">2</bi_eiVal>"
       << "<bi_eiVal species=\"Species_6\">2</bi_eiVal>"
       << "<bi_eiVal species=\"Species_7\">2</bi_eiVal>"
       << "<bi_eiVal species=\"Species_8\">2</bi_eiVal>"
       << "<bi_eiVal species=\"Species_9\">2</bi_eiVal>"
       << "<bi_eiVal species=\"Species_10\">2</bi_eiVal>"
       << "<bi_eiVal species=\"Species_11\">2</bi_eiVal>"
       << "<bi_eiVal species=\"Species_12\">2</bi_eiVal>"
       << "<bi_eiVal species=\"Species_14\">2</bi_eiVal>"
       << "<bi_eiVal species=\"Species_15\">2</bi_eiVal>"
       << "<bi_eiVal species=\"Species_16\">2</bi_eiVal>"
       << "<bi_eiVal species=\"Species_17\">2</bi_eiVal>"
       << "<bi_eiVal species=\"Species_18\">2</bi_eiVal>"
       << "<bi_eiVal species=\"Species_19\">2</bi_eiVal>"
       << "</bi_eqID>"
       << "<bi_dbhUnits>"
       << "<bi_duVal species=\"Species_1\">0</bi_duVal>"
       << "<bi_duVal species=\"Species_2\">1</bi_duVal>"
       << "<bi_duVal species=\"Species_3\">2</bi_duVal>"
       << "<bi_duVal species=\"Species_4\">0</bi_duVal>"
       << "<bi_duVal species=\"Species_5\">1</bi_duVal>"
       << "<bi_duVal species=\"Species_6\">2</bi_duVal>"
       << "<bi_duVal species=\"Species_7\">0</bi_duVal>"
       << "<bi_duVal species=\"Species_8\">1</bi_duVal>"
       << "<bi_duVal species=\"Species_9\">2</bi_duVal>"
       << "<bi_duVal species=\"Species_10\">0</bi_duVal>"
       << "<bi_duVal species=\"Species_11\">1</bi_duVal>"
       << "<bi_duVal species=\"Species_12\">2</bi_duVal>"
       << "<bi_duVal species=\"Species_14\">0</bi_duVal>"
       << "<bi_duVal species=\"Species_15\">1</bi_duVal>"
       << "<bi_duVal species=\"Species_16\">2</bi_duVal>"
       << "<bi_duVal species=\"Species_17\">0</bi_duVal>"
       << "<bi_duVal species=\"Species_18\">1</bi_duVal>"
       << "<bi_duVal species=\"Species_19\">2</bi_duVal>"
       << "</bi_dbhUnits>"
       << "<bi_biomassUnits>"
       << "<bi_buVal species=\"Species_1\">1</bi_buVal>"
       << "<bi_buVal species=\"Species_2\">1</bi_buVal>"
       << "<bi_buVal species=\"Species_3\">1</bi_buVal>"
       << "<bi_buVal species=\"Species_4\">2</bi_buVal>"
       << "<bi_buVal species=\"Species_5\">2</bi_buVal>"
       << "<bi_buVal species=\"Species_6\">2</bi_buVal>"
       << "<bi_buVal species=\"Species_7\">0</bi_buVal>"
       << "<bi_buVal species=\"Species_8\">0</bi_buVal>"
       << "<bi_buVal species=\"Species_9\">0</bi_buVal>"
       << "<bi_buVal species=\"Species_10\">1</bi_buVal>"
       << "<bi_buVal species=\"Species_11\">1</bi_buVal>"
       << "<bi_buVal species=\"Species_12\">1</bi_buVal>"
       << "<bi_buVal species=\"Species_14\">2</bi_buVal>"
       << "<bi_buVal species=\"Species_15\">2</bi_buVal>"
       << "<bi_buVal species=\"Species_16\">2</bi_buVal>"
       << "<bi_buVal species=\"Species_17\">0</bi_buVal>"
       << "<bi_buVal species=\"Species_18\">0</bi_buVal>"
       << "<bi_buVal species=\"Species_19\">0</bi_buVal>"
       << "</bi_biomassUnits>"
       << "<bi_useCorrectionFactor>"
       << "<bi_ucfVal species=\"Species_1\">1</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_2\">1</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_3\">1</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_4\">1</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_5\">1</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_6\">1</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_7\">1</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_8\">1</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_9\">1</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_10\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_11\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_12\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_14\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_15\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_16\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_17\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_18\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_19\">0</bi_ucfVal>"
       << "</bi_useCorrectionFactor>"
       << "<bi_correctionFactorValue>"
       << "<bi_cfvVal species=\"Species_1\">1.07</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_2\">1.08</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_3\">1.09</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_4\">1.1</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_5\">1.2</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_6\">1.9</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_7\">1.8</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_8\">1.7</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_9\">1.6</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_10\">1</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_11\">1</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_12\">1</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_14\">1</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_15\">1</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_16\">0</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_17\">0</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_18\">0</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_19\">0</bi_cfvVal>"
       << "</bi_correctionFactorValue>"
       << "<bi_whatDia>"
       << "<bi_wdVal species=\"Species_1\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_2\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_3\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_4\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_5\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_6\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_7\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_8\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_9\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_10\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_11\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_12\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_14\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_15\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_16\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_17\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_18\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_19\">0</bi_wdVal>"
       << "</bi_whatDia>"
       << "</DimensionAnalysis1>"
       << "</paramFile>";

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteDimensionAnalysisXMLFile3()
////////////////////////////////////////////////////////////////////////////
const char* WriteDimensionAnalysisXMLFile3() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteDimensionAnalysisCommonStuff(oOut);

  oOut << "<DimensionAnalysis1>"
       << "<bi_a>"
       << "<bi_aVal species=\"Species_1\">-3.7</bi_aVal>"
       << "<bi_aVal species=\"Species_2\">-3.787</bi_aVal>"
       << "<bi_aVal species=\"Species_3\">0.6</bi_aVal>"
       << "<bi_aVal species=\"Species_4\">-3.85</bi_aVal>"
       << "<bi_aVal species=\"Species_5\">-3.65</bi_aVal>"
       << "<bi_aVal species=\"Species_6\">0.6538</bi_aVal>"
       << "<bi_aVal species=\"Species_7\">-3.9</bi_aVal>"
       << "<bi_aVal species=\"Species_8\">-3</bi_aVal>"
       << "<bi_aVal species=\"Species_9\">0.75</bi_aVal>"
       << "<bi_aVal species=\"Species_10\">-3.7</bi_aVal>"
       << "<bi_aVal species=\"Species_11\">-3.787</bi_aVal>"
       << "<bi_aVal species=\"Species_12\">0.6</bi_aVal>"
       << "<bi_aVal species=\"Species_14\">-3.85</bi_aVal>"
       << "<bi_aVal species=\"Species_15\">-3.65</bi_aVal>"
       << "<bi_aVal species=\"Species_16\">0.6538</bi_aVal>"
       << "<bi_aVal species=\"Species_17\">-3.9</bi_aVal>"
       << "<bi_aVal species=\"Species_18\">-3</bi_aVal>"
       << "<bi_aVal species=\"Species_19\">0.75</bi_aVal>"
       << "</bi_a>"
       << "<bi_b>"
       << "<bi_bVal species=\"Species_1\">0.1</bi_bVal>"
       << "<bi_bVal species=\"Species_2\">0</bi_bVal>"
       << "<bi_bVal species=\"Species_3\">0.2</bi_bVal>"
       << "<bi_bVal species=\"Species_4\">0.3</bi_bVal>"
       << "<bi_bVal species=\"Species_5\">0.4</bi_bVal>"
       << "<bi_bVal species=\"Species_6\">0</bi_bVal>"
       << "<bi_bVal species=\"Species_7\">-0.9</bi_bVal>"
       << "<bi_bVal species=\"Species_8\">-0.8</bi_bVal>"
       << "<bi_bVal species=\"Species_9\">-0.7</bi_bVal>"
       << "<bi_bVal species=\"Species_10\">0.1</bi_bVal>"
       << "<bi_bVal species=\"Species_11\">0</bi_bVal>"
       << "<bi_bVal species=\"Species_12\">0.2</bi_bVal>"
       << "<bi_bVal species=\"Species_14\">0.3</bi_bVal>"
       << "<bi_bVal species=\"Species_15\">0.4</bi_bVal>"
       << "<bi_bVal species=\"Species_16\">0</bi_bVal>"
       << "<bi_bVal species=\"Species_17\">-0.9</bi_bVal>"
       << "<bi_bVal species=\"Species_18\">-0.8</bi_bVal>"
       << "<bi_bVal species=\"Species_19\">-0.7</bi_bVal>"
       << "</bi_b>"
       << "<bi_c>"
       << "<bi_cVal species=\"Species_1\">2.5</bi_cVal>"
       << "<bi_cVal species=\"Species_2\">2.767</bi_cVal>"
       << "<bi_cVal species=\"Species_3\">2.6</bi_cVal>"
       << "<bi_cVal species=\"Species_4\">2.7</bi_cVal>"
       << "<bi_cVal species=\"Species_5\">2.4</bi_cVal>"
       << "<bi_cVal species=\"Species_6\">2.4872</bi_cVal>"
       << "<bi_cVal species=\"Species_7\">2.3</bi_cVal>"
       << "<bi_cVal species=\"Species_8\">2</bi_cVal>"
       << "<bi_cVal species=\"Species_9\">2.9</bi_cVal>"
       << "<bi_cVal species=\"Species_10\">2.5</bi_cVal>"
       << "<bi_cVal species=\"Species_11\">2.767</bi_cVal>"
       << "<bi_cVal species=\"Species_12\">2.6</bi_cVal>"
       << "<bi_cVal species=\"Species_14\">2.7</bi_cVal>"
       << "<bi_cVal species=\"Species_15\">2.4</bi_cVal>"
       << "<bi_cVal species=\"Species_16\">2.4872</bi_cVal>"
       << "<bi_cVal species=\"Species_17\">2.3</bi_cVal>"
       << "<bi_cVal species=\"Species_18\">2</bi_cVal>"
       << "<bi_cVal species=\"Species_19\">2.9</bi_cVal>"
       << "</bi_c>"
       << "<bi_d>"
       << "<bi_dVal species=\"Species_1\">0.9</bi_dVal>"
       << "<bi_dVal species=\"Species_2\">1</bi_dVal>"
       << "<bi_dVal species=\"Species_3\">0.8</bi_dVal>"
       << "<bi_dVal species=\"Species_4\">1.1</bi_dVal>"
       << "<bi_dVal species=\"Species_5\">1.2</bi_dVal>"
       << "<bi_dVal species=\"Species_6\">1</bi_dVal>"
       << "<bi_dVal species=\"Species_7\">1.11</bi_dVal>"
       << "<bi_dVal species=\"Species_8\">1</bi_dVal>"
       << "<bi_dVal species=\"Species_9\">1.12</bi_dVal>"
       << "<bi_dVal species=\"Species_10\">0.9</bi_dVal>"
       << "<bi_dVal species=\"Species_11\">1</bi_dVal>"
       << "<bi_dVal species=\"Species_12\">0.8</bi_dVal>"
       << "<bi_dVal species=\"Species_14\">1.1</bi_dVal>"
       << "<bi_dVal species=\"Species_15\">1.2</bi_dVal>"
       << "<bi_dVal species=\"Species_16\">1</bi_dVal>"
       << "<bi_dVal species=\"Species_17\">1.11</bi_dVal>"
       << "<bi_dVal species=\"Species_18\">1</bi_dVal>"
       << "<bi_dVal species=\"Species_19\">1.12</bi_dVal>"
       << "</bi_d>"
       << "<bi_e>"
       << "<bi_eVal species=\"Species_1\">0.5</bi_eVal>"
       << "<bi_eVal species=\"Species_2\">0.92</bi_eVal>"
       << "<bi_eVal species=\"Species_3\">0.93</bi_eVal>"
       << "<bi_eVal species=\"Species_4\">0.25</bi_eVal>"
       << "<bi_eVal species=\"Species_5\">0.95</bi_eVal>"
       << "<bi_eVal species=\"Species_6\">0.4</bi_eVal>"
       << "<bi_eVal species=\"Species_7\">0.97</bi_eVal>"
       << "<bi_eVal species=\"Species_8\">0.98</bi_eVal>"
       << "<bi_eVal species=\"Species_9\">0.99</bi_eVal>"
       << "<bi_eVal species=\"Species_10\">0.5</bi_eVal>"
       << "<bi_eVal species=\"Species_11\">0.92</bi_eVal>"
       << "<bi_eVal species=\"Species_12\">0.93</bi_eVal>"
       << "<bi_eVal species=\"Species_14\">0.25</bi_eVal>"
       << "<bi_eVal species=\"Species_15\">0.95</bi_eVal>"
       << "<bi_eVal species=\"Species_16\">0.4</bi_eVal>"
       << "<bi_eVal species=\"Species_17\">0.97</bi_eVal>"
       << "<bi_eVal species=\"Species_18\">0.98</bi_eVal>"
       << "<bi_eVal species=\"Species_19\">0.99</bi_eVal>"
       << "</bi_e>"
       << "<bi_eqID>"
       << "<bi_eiVal species=\"Species_1\">3</bi_eiVal>"
       << "<bi_eiVal species=\"Species_2\">3</bi_eiVal>"
       << "<bi_eiVal species=\"Species_3\">3</bi_eiVal>"
       << "<bi_eiVal species=\"Species_4\">3</bi_eiVal>"
       << "<bi_eiVal species=\"Species_5\">3</bi_eiVal>"
       << "<bi_eiVal species=\"Species_6\">3</bi_eiVal>"
       << "<bi_eiVal species=\"Species_7\">3</bi_eiVal>"
       << "<bi_eiVal species=\"Species_8\">3</bi_eiVal>"
       << "<bi_eiVal species=\"Species_9\">3</bi_eiVal>"
       << "<bi_eiVal species=\"Species_10\">3</bi_eiVal>"
       << "<bi_eiVal species=\"Species_11\">3</bi_eiVal>"
       << "<bi_eiVal species=\"Species_12\">3</bi_eiVal>"
       << "<bi_eiVal species=\"Species_14\">3</bi_eiVal>"
       << "<bi_eiVal species=\"Species_15\">3</bi_eiVal>"
       << "<bi_eiVal species=\"Species_16\">3</bi_eiVal>"
       << "<bi_eiVal species=\"Species_17\">3</bi_eiVal>"
       << "<bi_eiVal species=\"Species_18\">3</bi_eiVal>"
       << "<bi_eiVal species=\"Species_19\">3</bi_eiVal>"
       << "</bi_eqID>"
       << "<bi_dbhUnits>"
       << "<bi_duVal species=\"Species_1\">0</bi_duVal>"
       << "<bi_duVal species=\"Species_2\">1</bi_duVal>"
       << "<bi_duVal species=\"Species_3\">2</bi_duVal>"
       << "<bi_duVal species=\"Species_4\">0</bi_duVal>"
       << "<bi_duVal species=\"Species_5\">1</bi_duVal>"
       << "<bi_duVal species=\"Species_6\">2</bi_duVal>"
       << "<bi_duVal species=\"Species_7\">0</bi_duVal>"
       << "<bi_duVal species=\"Species_8\">1</bi_duVal>"
       << "<bi_duVal species=\"Species_9\">2</bi_duVal>"
       << "<bi_duVal species=\"Species_10\">0</bi_duVal>"
       << "<bi_duVal species=\"Species_11\">1</bi_duVal>"
       << "<bi_duVal species=\"Species_12\">2</bi_duVal>"
       << "<bi_duVal species=\"Species_14\">0</bi_duVal>"
       << "<bi_duVal species=\"Species_15\">1</bi_duVal>"
       << "<bi_duVal species=\"Species_16\">2</bi_duVal>"
       << "<bi_duVal species=\"Species_17\">0</bi_duVal>"
       << "<bi_duVal species=\"Species_18\">1</bi_duVal>"
       << "<bi_duVal species=\"Species_19\">2</bi_duVal>"
       << "</bi_dbhUnits>"
       << "<bi_biomassUnits>"
       << "<bi_buVal species=\"Species_1\">1</bi_buVal>"
       << "<bi_buVal species=\"Species_2\">1</bi_buVal>"
       << "<bi_buVal species=\"Species_3\">1</bi_buVal>"
       << "<bi_buVal species=\"Species_4\">2</bi_buVal>"
       << "<bi_buVal species=\"Species_5\">2</bi_buVal>"
       << "<bi_buVal species=\"Species_6\">2</bi_buVal>"
       << "<bi_buVal species=\"Species_7\">0</bi_buVal>"
       << "<bi_buVal species=\"Species_8\">0</bi_buVal>"
       << "<bi_buVal species=\"Species_9\">0</bi_buVal>"
       << "<bi_buVal species=\"Species_10\">1</bi_buVal>"
       << "<bi_buVal species=\"Species_11\">1</bi_buVal>"
       << "<bi_buVal species=\"Species_12\">1</bi_buVal>"
       << "<bi_buVal species=\"Species_14\">2</bi_buVal>"
       << "<bi_buVal species=\"Species_15\">2</bi_buVal>"
       << "<bi_buVal species=\"Species_16\">2</bi_buVal>"
       << "<bi_buVal species=\"Species_17\">0</bi_buVal>"
       << "<bi_buVal species=\"Species_18\">0</bi_buVal>"
       << "<bi_buVal species=\"Species_19\">0</bi_buVal>"
       << "</bi_biomassUnits>"
       << "<bi_useCorrectionFactor>"
       << "<bi_ucfVal species=\"Species_1\">1</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_2\">1</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_3\">1</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_4\">1</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_5\">1</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_6\">1</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_7\">1</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_8\">1</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_9\">1</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_10\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_11\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_12\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_14\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_15\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_16\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_17\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_18\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_19\">0</bi_ucfVal>"
       << "</bi_useCorrectionFactor>"
       << "<bi_correctionFactorValue>"
       << "<bi_cfvVal species=\"Species_1\">1.07</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_2\">1.08</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_3\">1.09</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_4\">1.1</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_5\">1.2</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_6\">1.9</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_7\">1.8</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_8\">1.7</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_9\">1.6</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_10\">1</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_11\">1</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_12\">1</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_14\">1</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_15\">1</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_16\">1</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_17\">1</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_18\">1</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_19\">1</bi_cfvVal>"
       << "</bi_correctionFactorValue>"
       << "<bi_whatDia>"
       << "<bi_wdVal species=\"Species_1\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_2\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_3\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_4\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_5\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_6\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_7\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_8\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_9\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_10\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_11\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_12\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_14\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_15\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_16\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_17\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_18\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_19\">0</bi_wdVal>"
       << "</bi_whatDia>"
       << "</DimensionAnalysis1>"
       << "</paramFile>";

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteDimensionAnalysisXMLFile4()
////////////////////////////////////////////////////////////////////////////
const char* WriteDimensionAnalysisXMLFile4() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteDimensionAnalysisCommonStuff(oOut);

  oOut << "<DimensionAnalysis1>"
       << "<bi_a>"
       << "<bi_aVal species=\"Species_1\">4.5966</bi_aVal>"
       << "<bi_aVal species=\"Species_2\">4.5</bi_aVal>"
       << "<bi_aVal species=\"Species_3\">4.4</bi_aVal>"
       << "<bi_aVal species=\"Species_4\">4.3</bi_aVal>"
       << "<bi_aVal species=\"Species_5\">4.2</bi_aVal>"
       << "<bi_aVal species=\"Species_6\">4.1</bi_aVal>"
       << "<bi_aVal species=\"Species_7\">4</bi_aVal>"
       << "<bi_aVal species=\"Species_8\">4.6</bi_aVal>"
       << "<bi_aVal species=\"Species_9\">4.7</bi_aVal>"
       << "<bi_aVal species=\"Species_10\">4.8</bi_aVal>"
       << "<bi_aVal species=\"Species_11\">-6.1166</bi_aVal>"
       << "<bi_aVal species=\"Species_12\">-6</bi_aVal>"
       << "<bi_aVal species=\"Species_14\">-61</bi_aVal>"
       << "<bi_aVal species=\"Species_15\">-6.2</bi_aVal>"
       << "<bi_aVal species=\"Species_16\">-6.3</bi_aVal>"
       << "<bi_aVal species=\"Species_17\">-5.9</bi_aVal>"
       << "<bi_aVal species=\"Species_18\">-5.8</bi_aVal>"
       << "<bi_aVal species=\"Species_19\">-5.7</bi_aVal>"
       << "</bi_a>"
       << "<bi_b>"
       << "<bi_bVal species=\"Species_1\">-0.2364</bi_bVal>"
       << "<bi_bVal species=\"Species_2\">0.2</bi_bVal>"
       << "<bi_bVal species=\"Species_3\">0.22</bi_bVal>"
       << "<bi_bVal species=\"Species_4\">-0.26</bi_bVal>"
       << "<bi_bVal species=\"Species_5\">0.28</bi_bVal>"
       << "<bi_bVal species=\"Species_6\">0.3</bi_bVal>"
       << "<bi_bVal species=\"Species_7\">-0.18</bi_bVal>"
       << "<bi_bVal species=\"Species_8\">0.16</bi_bVal>"
       << "<bi_bVal species=\"Species_9\">0.14</bi_bVal>"
       << "<bi_bVal species=\"Species_10\">-0.12</bi_bVal>"
       << "<bi_bVal species=\"Species_11\">0</bi_bVal>"
       << "<bi_bVal species=\"Species_12\">0.1</bi_bVal>"
       << "<bi_bVal species=\"Species_14\">0.2</bi_bVal>"
       << "<bi_bVal species=\"Species_15\">0.3</bi_bVal>"
       << "<bi_bVal species=\"Species_16\">0.4</bi_bVal>"
       << "<bi_bVal species=\"Species_17\">0.5</bi_bVal>"
       << "<bi_bVal species=\"Species_18\">0.6</bi_bVal>"
       << "<bi_bVal species=\"Species_19\">0.7</bi_bVal>"
       << "</bi_b>"
       << "<bi_c>"
       << "<bi_cVal species=\"Species_1\">0.00411</bi_cVal>"
       << "<bi_cVal species=\"Species_2\">0.05</bi_cVal>"
       << "<bi_cVal species=\"Species_3\">0.06</bi_cVal>"
       << "<bi_cVal species=\"Species_4\">0.005</bi_cVal>"
       << "<bi_cVal species=\"Species_5\">0.006</bi_cVal>"
       << "<bi_cVal species=\"Species_6\">0.007</bi_cVal>"
       << "<bi_cVal species=\"Species_7\">0.008</bi_cVal>"
       << "<bi_cVal species=\"Species_8\">2.4</bi_cVal>"
       << "<bi_cVal species=\"Species_9\">1.4</bi_cVal>"
       << "<bi_cVal species=\"Species_10\">0.0028</bi_cVal>"
       << "<bi_cVal species=\"Species_11\">2.8421</bi_cVal>"
       << "<bi_cVal species=\"Species_12\">1.5</bi_cVal>"
       << "<bi_cVal species=\"Species_14\">0.0005</bi_cVal>"
       << "<bi_cVal species=\"Species_15\">2.5</bi_cVal>"
       << "<bi_cVal species=\"Species_16\">1.6</bi_cVal>"
       << "<bi_cVal species=\"Species_17\">0.75</bi_cVal>"
       << "<bi_cVal species=\"Species_18\">2.9</bi_cVal>"
       << "<bi_cVal species=\"Species_19\">1.8</bi_cVal>"
       << "</bi_c>"
       << "<bi_d>"
       << "<bi_dVal species=\"Species_1\">2</bi_dVal>"
       << "<bi_dVal species=\"Species_2\">0.2</bi_dVal>"
       << "<bi_dVal species=\"Species_3\">0.25</bi_dVal>"
       << "<bi_dVal species=\"Species_4\">2.1</bi_dVal>"
       << "<bi_dVal species=\"Species_5\">0.23</bi_dVal>"
       << "<bi_dVal species=\"Species_6\">0.27</bi_dVal>"
       << "<bi_dVal species=\"Species_7\">2.2</bi_dVal>"
       << "<bi_dVal species=\"Species_8\">2.1</bi_dVal>"
       << "<bi_dVal species=\"Species_9\">3.2</bi_dVal>"
       << "<bi_dVal species=\"Species_10\">0.0009</bi_dVal>"
       << "<bi_dVal species=\"Species_11\">1</bi_dVal>"
       << "<bi_dVal species=\"Species_12\">0.92</bi_dVal>"
       << "<bi_dVal species=\"Species_14\">0.00094</bi_dVal>"
       << "<bi_dVal species=\"Species_15\">0.96</bi_dVal>"
       << "<bi_dVal species=\"Species_16\">0.98</bi_dVal>"
       << "<bi_dVal species=\"Species_17\">1.1</bi_dVal>"
       << "<bi_dVal species=\"Species_18\">1.3</bi_dVal>"
       << "<bi_dVal species=\"Species_19\">1.25</bi_dVal>"
       << "</bi_d>"
       << "<bi_e>"
       << "<bi_eVal species=\"Species_1\">1</bi_eVal>"
       << "<bi_eVal species=\"Species_2\">1</bi_eVal>"
       << "<bi_eVal species=\"Species_3\">1</bi_eVal>"
       << "<bi_eVal species=\"Species_4\">1</bi_eVal>"
       << "<bi_eVal species=\"Species_5\">1</bi_eVal>"
       << "<bi_eVal species=\"Species_6\">1</bi_eVal>"
       << "<bi_eVal species=\"Species_7\">1</bi_eVal>"
       << "<bi_eVal species=\"Species_8\">1</bi_eVal>"
       << "<bi_eVal species=\"Species_9\">1</bi_eVal>"
       << "<bi_eVal species=\"Species_10\">1</bi_eVal>"
       << "<bi_eVal species=\"Species_11\">1</bi_eVal>"
       << "<bi_eVal species=\"Species_12\">1</bi_eVal>"
       << "<bi_eVal species=\"Species_14\">1</bi_eVal>"
       << "<bi_eVal species=\"Species_15\">1</bi_eVal>"
       << "<bi_eVal species=\"Species_16\">1</bi_eVal>"
       << "<bi_eVal species=\"Species_17\">1</bi_eVal>"
       << "<bi_eVal species=\"Species_18\">1</bi_eVal>"
       << "<bi_eVal species=\"Species_19\">1</bi_eVal>"
       << "</bi_e>"
       << "<bi_eqID>"
       << "<bi_eiVal species=\"Species_1\">4</bi_eiVal>"
       << "<bi_eiVal species=\"Species_2\">4</bi_eiVal>"
       << "<bi_eiVal species=\"Species_3\">4</bi_eiVal>"
       << "<bi_eiVal species=\"Species_4\">4</bi_eiVal>"
       << "<bi_eiVal species=\"Species_5\">4</bi_eiVal>"
       << "<bi_eiVal species=\"Species_6\">4</bi_eiVal>"
       << "<bi_eiVal species=\"Species_7\">4</bi_eiVal>"
       << "<bi_eiVal species=\"Species_8\">4</bi_eiVal>"
       << "<bi_eiVal species=\"Species_9\">4</bi_eiVal>"
       << "<bi_eiVal species=\"Species_10\">5</bi_eiVal>"
       << "<bi_eiVal species=\"Species_11\">5</bi_eiVal>"
       << "<bi_eiVal species=\"Species_12\">5</bi_eiVal>"
       << "<bi_eiVal species=\"Species_14\">5</bi_eiVal>"
       << "<bi_eiVal species=\"Species_15\">5</bi_eiVal>"
       << "<bi_eiVal species=\"Species_16\">5</bi_eiVal>"
       << "<bi_eiVal species=\"Species_17\">5</bi_eiVal>"
       << "<bi_eiVal species=\"Species_18\">5</bi_eiVal>"
       << "<bi_eiVal species=\"Species_19\">5</bi_eiVal>"
       << "</bi_eqID>"
       << "<bi_dbhUnits>"
       << "<bi_duVal species=\"Species_1\">0</bi_duVal>"
       << "<bi_duVal species=\"Species_2\">1</bi_duVal>"
       << "<bi_duVal species=\"Species_3\">2</bi_duVal>"
       << "<bi_duVal species=\"Species_4\">0</bi_duVal>"
       << "<bi_duVal species=\"Species_5\">1</bi_duVal>"
       << "<bi_duVal species=\"Species_6\">2</bi_duVal>"
       << "<bi_duVal species=\"Species_7\">0</bi_duVal>"
       << "<bi_duVal species=\"Species_8\">1</bi_duVal>"
       << "<bi_duVal species=\"Species_9\">2</bi_duVal>"
       << "<bi_duVal species=\"Species_10\">0</bi_duVal>"
       << "<bi_duVal species=\"Species_11\">1</bi_duVal>"
       << "<bi_duVal species=\"Species_12\">2</bi_duVal>"
       << "<bi_duVal species=\"Species_14\">0</bi_duVal>"
       << "<bi_duVal species=\"Species_15\">1</bi_duVal>"
       << "<bi_duVal species=\"Species_16\">2</bi_duVal>"
       << "<bi_duVal species=\"Species_17\">0</bi_duVal>"
       << "<bi_duVal species=\"Species_18\">1</bi_duVal>"
       << "<bi_duVal species=\"Species_19\">2</bi_duVal>"
       << "</bi_dbhUnits>"
       << "<bi_biomassUnits>"
       << "<bi_buVal species=\"Species_1\">1</bi_buVal>"
       << "<bi_buVal species=\"Species_2\">1</bi_buVal>"
       << "<bi_buVal species=\"Species_3\">1</bi_buVal>"
       << "<bi_buVal species=\"Species_4\">2</bi_buVal>"
       << "<bi_buVal species=\"Species_5\">2</bi_buVal>"
       << "<bi_buVal species=\"Species_6\">2</bi_buVal>"
       << "<bi_buVal species=\"Species_7\">0</bi_buVal>"
       << "<bi_buVal species=\"Species_8\">0</bi_buVal>"
       << "<bi_buVal species=\"Species_9\">0</bi_buVal>"
       << "<bi_buVal species=\"Species_10\">1</bi_buVal>"
       << "<bi_buVal species=\"Species_11\">1</bi_buVal>"
       << "<bi_buVal species=\"Species_12\">1</bi_buVal>"
       << "<bi_buVal species=\"Species_14\">2</bi_buVal>"
       << "<bi_buVal species=\"Species_15\">2</bi_buVal>"
       << "<bi_buVal species=\"Species_16\">2</bi_buVal>"
       << "<bi_buVal species=\"Species_17\">0</bi_buVal>"
       << "<bi_buVal species=\"Species_18\">0</bi_buVal>"
       << "<bi_buVal species=\"Species_19\">0</bi_buVal>"
       << "</bi_biomassUnits>"
       << "<bi_useCorrectionFactor>"
       << "<bi_ucfVal species=\"Species_1\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_2\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_3\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_4\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_5\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_6\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_7\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_8\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_9\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_10\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_11\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_12\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_14\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_15\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_16\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_17\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_18\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_19\">0</bi_ucfVal>"
       << "</bi_useCorrectionFactor>"
       << "<bi_correctionFactorValue>"
       << "<bi_cfvVal species=\"Species_1\">0</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_2\">0</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_3\">0</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_4\">0</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_5\">0</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_6\">0</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_7\">0</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_8\">0</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_9\">0</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_10\">0</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_11\">0</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_12\">0</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_14\">0</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_15\">0</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_16\">0</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_17\">0</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_18\">0</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_19\">0</bi_cfvVal>"
       << "</bi_correctionFactorValue>"
       << "<bi_whatDia>"
       << "<bi_wdVal species=\"Species_1\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_2\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_3\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_4\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_5\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_6\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_7\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_8\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_9\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_10\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_11\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_12\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_14\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_15\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_16\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_17\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_18\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_19\">0</bi_wdVal>"
       << "</bi_whatDia>"
       << "</DimensionAnalysis1>"
       << "</paramFile>";

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteDimensionAnalysisXMLFile5()
////////////////////////////////////////////////////////////////////////////
const char* WriteDimensionAnalysisXMLFile5() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteDimensionAnalysisCommonStuff(oOut);

  oOut << "<DimensionAnalysis1>"
       << "<bi_a>"
       << "<bi_aVal species=\"Species_1\">4.5966</bi_aVal>"
       << "<bi_aVal species=\"Species_2\">4.5</bi_aVal>"
       << "<bi_aVal species=\"Species_3\">4.4</bi_aVal>"
       << "<bi_aVal species=\"Species_4\">4.3</bi_aVal>"
       << "<bi_aVal species=\"Species_5\">4.2</bi_aVal>"
       << "<bi_aVal species=\"Species_6\">4.1</bi_aVal>"
       << "<bi_aVal species=\"Species_7\">4</bi_aVal>"
       << "<bi_aVal species=\"Species_8\">4.6</bi_aVal>"
       << "<bi_aVal species=\"Species_9\">4.7</bi_aVal>"
       << "<bi_aVal species=\"Species_10\">0.6</bi_aVal>"
       << "<bi_aVal species=\"Species_11\">0.5</bi_aVal>"
       << "<bi_aVal species=\"Species_12\">0.7</bi_aVal>"
       << "<bi_aVal species=\"Species_14\">0.8</bi_aVal>"
       << "<bi_aVal species=\"Species_15\">0.9</bi_aVal>"
       << "<bi_aVal species=\"Species_16\">0.4</bi_aVal>"
       << "<bi_aVal species=\"Species_17\">0.3</bi_aVal>"
       << "<bi_aVal species=\"Species_18\">0.2</bi_aVal>"
       << "<bi_aVal species=\"Species_19\">0</bi_aVal>"
       << "</bi_a>"
       << "<bi_b>"
       << "<bi_bVal species=\"Species_1\">-0.2364</bi_bVal>"
       << "<bi_bVal species=\"Species_2\">0.2</bi_bVal>"
       << "<bi_bVal species=\"Species_3\">0.22</bi_bVal>"
       << "<bi_bVal species=\"Species_4\">8.5</bi_bVal>"
       << "<bi_bVal species=\"Species_5\">0.28</bi_bVal>"
       << "<bi_bVal species=\"Species_6\">0.3</bi_bVal>"
       << "<bi_bVal species=\"Species_7\">-0.18</bi_bVal>"
       << "<bi_bVal species=\"Species_8\">0.16</bi_bVal>"
       << "<bi_bVal species=\"Species_9\">0.14</bi_bVal>"
       << "<bi_bVal species=\"Species_10\">14363</bi_bVal>"
       << "<bi_bVal species=\"Species_11\">15000</bi_bVal>"
       << "<bi_bVal species=\"Species_12\">15467</bi_bVal>"
       << "<bi_bVal species=\"Species_14\">14345</bi_bVal>"
       << "<bi_bVal species=\"Species_15\">12989</bi_bVal>"
       << "<bi_bVal species=\"Species_16\">17457</bi_bVal>"
       << "<bi_bVal species=\"Species_17\">18374</bi_bVal>"
       << "<bi_bVal species=\"Species_18\">15346</bi_bVal>"
       << "<bi_bVal species=\"Species_19\">17732</bi_bVal>"
       << "</bi_b>"
       << "<bi_c>"
       << "<bi_cVal species=\"Species_1\">0.5</bi_cVal>"
       << "<bi_cVal species=\"Species_2\">-0.92</bi_cVal>"
       << "<bi_cVal species=\"Species_3\">0.93</bi_cVal>"
       << "<bi_cVal species=\"Species_4\">0.25</bi_cVal>"
       << "<bi_cVal species=\"Species_5\">0.95</bi_cVal>"
       << "<bi_cVal species=\"Species_6\">0.4</bi_cVal>"
       << "<bi_cVal species=\"Species_7\">0.97</bi_cVal>"
       << "<bi_cVal species=\"Species_8\">1.98</bi_cVal>"
       << "<bi_cVal species=\"Species_9\">0.99</bi_cVal>"
       << "<bi_cVal species=\"Species_10\">0.27</bi_cVal>"
       << "<bi_cVal species=\"Species_11\">2.7</bi_cVal>"
       << "<bi_cVal species=\"Species_12\">0.35</bi_cVal>"
       << "<bi_cVal species=\"Species_14\">3.2</bi_cVal>"
       << "<bi_cVal species=\"Species_15\">0.87</bi_cVal>"
       << "<bi_cVal species=\"Species_16\">0.12</bi_cVal>"
       << "<bi_cVal species=\"Species_17\">1.7</bi_cVal>"
       << "<bi_cVal species=\"Species_18\">0.35</bi_cVal>"
       << "<bi_cVal species=\"Species_19\">0.45</bi_cVal>"
       << "</bi_c>"
       << "<bi_d>"
       << "<bi_dVal species=\"Species_1\">-0.002</bi_dVal>"
       << "<bi_dVal species=\"Species_2\">0.1</bi_dVal>"
       << "<bi_dVal species=\"Species_3\">0.25</bi_dVal>"
       << "<bi_dVal species=\"Species_4\">-0.025</bi_dVal>"
       << "<bi_dVal species=\"Species_5\">0.023</bi_dVal>"
       << "<bi_dVal species=\"Species_6\">0.27</bi_dVal>"
       << "<bi_dVal species=\"Species_7\">0.0022</bi_dVal>"
       << "<bi_dVal species=\"Species_8\">0.045</bi_dVal>"
       << "<bi_dVal species=\"Species_9\">0.032</bi_dVal>"
       << "<bi_dVal species=\"Species_10\">35000</bi_dVal>"
       << "<bi_dVal species=\"Species_11\">364946</bi_dVal>"
       << "<bi_dVal species=\"Species_12\">395634</bi_dVal>"
       << "<bi_dVal species=\"Species_14\">396834</bi_dVal>"
       << "<bi_dVal species=\"Species_15\">567243</bi_dVal>"
       << "<bi_dVal species=\"Species_16\">254976</bi_dVal>"
       << "<bi_dVal species=\"Species_17\">200953</bi_dVal>"
       << "<bi_dVal species=\"Species_18\">105674</bi_dVal>"
       << "<bi_dVal species=\"Species_19\">674929</bi_dVal>"
       << "</bi_d>"
       << "<bi_e>"
       << "<bi_eVal species=\"Species_1\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_2\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_3\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_4\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_5\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_6\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_7\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_8\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_9\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_10\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_11\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_12\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_14\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_15\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_16\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_17\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_18\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_19\">0</bi_eVal>"
       << "</bi_e>"
       << "<bi_eqID>"
       << "<bi_eiVal species=\"Species_1\">6</bi_eiVal>"
       << "<bi_eiVal species=\"Species_2\">6</bi_eiVal>"
       << "<bi_eiVal species=\"Species_3\">6</bi_eiVal>"
       << "<bi_eiVal species=\"Species_4\">6</bi_eiVal>"
       << "<bi_eiVal species=\"Species_5\">6</bi_eiVal>"
       << "<bi_eiVal species=\"Species_6\">6</bi_eiVal>"
       << "<bi_eiVal species=\"Species_7\">6</bi_eiVal>"
       << "<bi_eiVal species=\"Species_8\">6</bi_eiVal>"
       << "<bi_eiVal species=\"Species_9\">6</bi_eiVal>"
       << "<bi_eiVal species=\"Species_10\">7</bi_eiVal>"
       << "<bi_eiVal species=\"Species_11\">7</bi_eiVal>"
       << "<bi_eiVal species=\"Species_12\">7</bi_eiVal>"
       << "<bi_eiVal species=\"Species_14\">7</bi_eiVal>"
       << "<bi_eiVal species=\"Species_15\">7</bi_eiVal>"
       << "<bi_eiVal species=\"Species_16\">7</bi_eiVal>"
       << "<bi_eiVal species=\"Species_17\">7</bi_eiVal>"
       << "<bi_eiVal species=\"Species_18\">7</bi_eiVal>"
       << "<bi_eiVal species=\"Species_19\">7</bi_eiVal>"
       << "</bi_eqID>"
       << "<bi_dbhUnits>"
       << "<bi_duVal species=\"Species_1\">0</bi_duVal>"
       << "<bi_duVal species=\"Species_2\">1</bi_duVal>"
       << "<bi_duVal species=\"Species_3\">2</bi_duVal>"
       << "<bi_duVal species=\"Species_4\">0</bi_duVal>"
       << "<bi_duVal species=\"Species_5\">1</bi_duVal>"
       << "<bi_duVal species=\"Species_6\">2</bi_duVal>"
       << "<bi_duVal species=\"Species_7\">0</bi_duVal>"
       << "<bi_duVal species=\"Species_8\">1</bi_duVal>"
       << "<bi_duVal species=\"Species_9\">2</bi_duVal>"
       << "<bi_duVal species=\"Species_10\">0</bi_duVal>"
       << "<bi_duVal species=\"Species_11\">1</bi_duVal>"
       << "<bi_duVal species=\"Species_12\">2</bi_duVal>"
       << "<bi_duVal species=\"Species_14\">0</bi_duVal>"
       << "<bi_duVal species=\"Species_15\">1</bi_duVal>"
       << "<bi_duVal species=\"Species_16\">2</bi_duVal>"
       << "<bi_duVal species=\"Species_17\">0</bi_duVal>"
       << "<bi_duVal species=\"Species_18\">1</bi_duVal>"
       << "<bi_duVal species=\"Species_19\">2</bi_duVal>"
       << "</bi_dbhUnits>"
       << "<bi_biomassUnits>"
       << "<bi_buVal species=\"Species_1\">1</bi_buVal>"
       << "<bi_buVal species=\"Species_2\">1</bi_buVal>"
       << "<bi_buVal species=\"Species_3\">1</bi_buVal>"
       << "<bi_buVal species=\"Species_4\">2</bi_buVal>"
       << "<bi_buVal species=\"Species_5\">2</bi_buVal>"
       << "<bi_buVal species=\"Species_6\">2</bi_buVal>"
       << "<bi_buVal species=\"Species_7\">0</bi_buVal>"
       << "<bi_buVal species=\"Species_8\">0</bi_buVal>"
       << "<bi_buVal species=\"Species_9\">0</bi_buVal>"
       << "<bi_buVal species=\"Species_10\">1</bi_buVal>"
       << "<bi_buVal species=\"Species_11\">1</bi_buVal>"
       << "<bi_buVal species=\"Species_12\">1</bi_buVal>"
       << "<bi_buVal species=\"Species_14\">2</bi_buVal>"
       << "<bi_buVal species=\"Species_15\">2</bi_buVal>"
       << "<bi_buVal species=\"Species_16\">2</bi_buVal>"
       << "<bi_buVal species=\"Species_17\">0</bi_buVal>"
       << "<bi_buVal species=\"Species_18\">0</bi_buVal>"
       << "<bi_buVal species=\"Species_19\">0</bi_buVal>"
       << "</bi_biomassUnits>"
       << "<bi_useCorrectionFactor>"
       << "<bi_ucfVal species=\"Species_1\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_2\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_3\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_4\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_5\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_6\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_7\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_8\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_9\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_10\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_11\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_12\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_14\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_15\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_16\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_17\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_18\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_19\">0</bi_ucfVal>"
       << "</bi_useCorrectionFactor>"
       << "<bi_correctionFactorValue>"
       << "<bi_cfvVal species=\"Species_1\">1</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_2\">1</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_3\">1</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_4\">1</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_5\">1</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_6\">1</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_7\">1</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_8\">1</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_9\">1</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_10\">1</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_11\">1</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_12\">1</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_14\">1</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_15\">1</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_16\">1</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_17\">1</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_18\">1</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_19\">1</bi_cfvVal>"
       << "</bi_correctionFactorValue>"
       << "<bi_whatDia>"
       << "<bi_wdVal species=\"Species_1\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_2\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_3\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_4\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_5\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_6\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_7\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_8\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_9\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_10\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_11\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_12\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_14\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_15\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_16\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_17\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_18\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_19\">0</bi_wdVal>"
       << "</bi_whatDia>"
       << "</DimensionAnalysis1>"
       << "</paramFile>";

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteDimensionAnalysisXMLFile6()
////////////////////////////////////////////////////////////////////////////
const char* WriteDimensionAnalysisXMLFile6() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteDimensionAnalysisCommonStuff(oOut);

  oOut << "<DimensionAnalysis1>"
       << "<bi_a>"
       << "<bi_aVal species=\"Species_1\">1.23</bi_aVal>"
       << "<bi_aVal species=\"Species_2\">0.3</bi_aVal>"
       << "<bi_aVal species=\"Species_3\">0.4</bi_aVal>"
       << "<bi_aVal species=\"Species_4\">0.5</bi_aVal>"
       << "<bi_aVal species=\"Species_5\">0.6</bi_aVal>"
       << "<bi_aVal species=\"Species_6\">0.7</bi_aVal>"
       << "<bi_aVal species=\"Species_7\">3.2</bi_aVal>"
       << "<bi_aVal species=\"Species_8\">0.9</bi_aVal>"
       << "<bi_aVal species=\"Species_9\">1</bi_aVal>"
       << "<bi_aVal species=\"Species_10\">1.23</bi_aVal>"
       << "<bi_aVal species=\"Species_11\">0.3</bi_aVal>"
       << "<bi_aVal species=\"Species_12\">0.4</bi_aVal>"
       << "<bi_aVal species=\"Species_14\">0.5</bi_aVal>"
       << "<bi_aVal species=\"Species_15\">0.6</bi_aVal>"
       << "<bi_aVal species=\"Species_16\">0.7</bi_aVal>"
       << "<bi_aVal species=\"Species_17\">3.2</bi_aVal>"
       << "<bi_aVal species=\"Species_18\">0.9</bi_aVal>"
       << "<bi_aVal species=\"Species_19\">1</bi_aVal>"
       << "</bi_a>"
       << "<bi_b>"
       << "<bi_bVal species=\"Species_1\">-0.23</bi_bVal>"
       << "<bi_bVal species=\"Species_2\">-0.24</bi_bVal>"
       << "<bi_bVal species=\"Species_3\">-0.25</bi_bVal>"
       << "<bi_bVal species=\"Species_4\">-0.26</bi_bVal>"
       << "<bi_bVal species=\"Species_5\">-0.27</bi_bVal>"
       << "<bi_bVal species=\"Species_6\">-0.28</bi_bVal>"
       << "<bi_bVal species=\"Species_7\">-0.29</bi_bVal>"
       << "<bi_bVal species=\"Species_8\">-0.3</bi_bVal>"
       << "<bi_bVal species=\"Species_9\">-0.31</bi_bVal>"
       << "<bi_bVal species=\"Species_10\">-0.23</bi_bVal>"
       << "<bi_bVal species=\"Species_11\">-0.24</bi_bVal>"
       << "<bi_bVal species=\"Species_12\">-0.25</bi_bVal>"
       << "<bi_bVal species=\"Species_14\">-0.26</bi_bVal>"
       << "<bi_bVal species=\"Species_15\">-0.27</bi_bVal>"
       << "<bi_bVal species=\"Species_16\">-0.28</bi_bVal>"
       << "<bi_bVal species=\"Species_17\">-0.29</bi_bVal>"
       << "<bi_bVal species=\"Species_18\">-0.3</bi_bVal>"
       << "<bi_bVal species=\"Species_19\">-0.31</bi_bVal>"
       << "</bi_b>"
       << "<bi_c>"
       << "<bi_cVal species=\"Species_1\">0</bi_cVal>"
       << "<bi_cVal species=\"Species_2\">0</bi_cVal>"
       << "<bi_cVal species=\"Species_3\">0</bi_cVal>"
       << "<bi_cVal species=\"Species_4\">0</bi_cVal>"
       << "<bi_cVal species=\"Species_5\">0</bi_cVal>"
       << "<bi_cVal species=\"Species_6\">0</bi_cVal>"
       << "<bi_cVal species=\"Species_7\">0</bi_cVal>"
       << "<bi_cVal species=\"Species_8\">0</bi_cVal>"
       << "<bi_cVal species=\"Species_9\">0</bi_cVal>"
       << "<bi_cVal species=\"Species_10\">0</bi_cVal>"
       << "<bi_cVal species=\"Species_11\">0</bi_cVal>"
       << "<bi_cVal species=\"Species_12\">0</bi_cVal>"
       << "<bi_cVal species=\"Species_14\">0</bi_cVal>"
       << "<bi_cVal species=\"Species_15\">0</bi_cVal>"
       << "<bi_cVal species=\"Species_16\">0</bi_cVal>"
       << "<bi_cVal species=\"Species_17\">0</bi_cVal>"
       << "<bi_cVal species=\"Species_18\">0</bi_cVal>"
       << "<bi_cVal species=\"Species_19\">0</bi_cVal>"
       << "</bi_c>"
       << "<bi_d>"
       << "<bi_dVal species=\"Species_1\">0</bi_dVal>"
       << "<bi_dVal species=\"Species_2\">0</bi_dVal>"
       << "<bi_dVal species=\"Species_3\">0</bi_dVal>"
       << "<bi_dVal species=\"Species_4\">0</bi_dVal>"
       << "<bi_dVal species=\"Species_5\">0</bi_dVal>"
       << "<bi_dVal species=\"Species_6\">0</bi_dVal>"
       << "<bi_dVal species=\"Species_7\">0</bi_dVal>"
       << "<bi_dVal species=\"Species_8\">0</bi_dVal>"
       << "<bi_dVal species=\"Species_9\">0</bi_dVal>"
       << "<bi_dVal species=\"Species_10\">0</bi_dVal>"
       << "<bi_dVal species=\"Species_11\">0</bi_dVal>"
       << "<bi_dVal species=\"Species_12\">0</bi_dVal>"
       << "<bi_dVal species=\"Species_14\">0</bi_dVal>"
       << "<bi_dVal species=\"Species_15\">0</bi_dVal>"
       << "<bi_dVal species=\"Species_16\">0</bi_dVal>"
       << "<bi_dVal species=\"Species_17\">0</bi_dVal>"
       << "<bi_dVal species=\"Species_18\">0</bi_dVal>"
       << "<bi_dVal species=\"Species_19\">0</bi_dVal>"
       << "</bi_d>"
       << "<bi_e>"
       << "<bi_eVal species=\"Species_1\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_2\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_3\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_4\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_5\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_6\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_7\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_8\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_9\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_10\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_11\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_12\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_14\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_15\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_16\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_17\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_18\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_19\">0</bi_eVal>"
       << "</bi_e>"
       << "<bi_eqID>"
       << "<bi_eiVal species=\"Species_1\">8</bi_eiVal>"
       << "<bi_eiVal species=\"Species_2\">8</bi_eiVal>"
       << "<bi_eiVal species=\"Species_3\">8</bi_eiVal>"
       << "<bi_eiVal species=\"Species_4\">8</bi_eiVal>"
       << "<bi_eiVal species=\"Species_5\">8</bi_eiVal>"
       << "<bi_eiVal species=\"Species_6\">8</bi_eiVal>"
       << "<bi_eiVal species=\"Species_7\">8</bi_eiVal>"
       << "<bi_eiVal species=\"Species_8\">8</bi_eiVal>"
       << "<bi_eiVal species=\"Species_9\">8</bi_eiVal>"
       << "<bi_eiVal species=\"Species_10\">8</bi_eiVal>"
       << "<bi_eiVal species=\"Species_11\">8</bi_eiVal>"
       << "<bi_eiVal species=\"Species_12\">8</bi_eiVal>"
       << "<bi_eiVal species=\"Species_14\">8</bi_eiVal>"
       << "<bi_eiVal species=\"Species_15\">8</bi_eiVal>"
       << "<bi_eiVal species=\"Species_16\">8</bi_eiVal>"
       << "<bi_eiVal species=\"Species_17\">8</bi_eiVal>"
       << "<bi_eiVal species=\"Species_18\">8</bi_eiVal>"
       << "<bi_eiVal species=\"Species_19\">8</bi_eiVal>"
       << "</bi_eqID>"
       << "<bi_dbhUnits>"
       << "<bi_duVal species=\"Species_1\">0</bi_duVal>"
       << "<bi_duVal species=\"Species_2\">1</bi_duVal>"
       << "<bi_duVal species=\"Species_3\">2</bi_duVal>"
       << "<bi_duVal species=\"Species_4\">0</bi_duVal>"
       << "<bi_duVal species=\"Species_5\">1</bi_duVal>"
       << "<bi_duVal species=\"Species_6\">2</bi_duVal>"
       << "<bi_duVal species=\"Species_7\">0</bi_duVal>"
       << "<bi_duVal species=\"Species_8\">1</bi_duVal>"
       << "<bi_duVal species=\"Species_9\">2</bi_duVal>"
       << "<bi_duVal species=\"Species_10\">0</bi_duVal>"
       << "<bi_duVal species=\"Species_11\">1</bi_duVal>"
       << "<bi_duVal species=\"Species_12\">2</bi_duVal>"
       << "<bi_duVal species=\"Species_14\">0</bi_duVal>"
       << "<bi_duVal species=\"Species_15\">1</bi_duVal>"
       << "<bi_duVal species=\"Species_16\">2</bi_duVal>"
       << "<bi_duVal species=\"Species_17\">0</bi_duVal>"
       << "<bi_duVal species=\"Species_18\">1</bi_duVal>"
       << "<bi_duVal species=\"Species_19\">2</bi_duVal>"
       << "</bi_dbhUnits>"
       << "<bi_biomassUnits>"
       << "<bi_buVal species=\"Species_1\">1</bi_buVal>"
       << "<bi_buVal species=\"Species_2\">1</bi_buVal>"
       << "<bi_buVal species=\"Species_3\">1</bi_buVal>"
       << "<bi_buVal species=\"Species_4\">2</bi_buVal>"
       << "<bi_buVal species=\"Species_5\">2</bi_buVal>"
       << "<bi_buVal species=\"Species_6\">2</bi_buVal>"
       << "<bi_buVal species=\"Species_7\">0</bi_buVal>"
       << "<bi_buVal species=\"Species_8\">0</bi_buVal>"
       << "<bi_buVal species=\"Species_9\">0</bi_buVal>"
       << "<bi_buVal species=\"Species_10\">1</bi_buVal>"
       << "<bi_buVal species=\"Species_11\">1</bi_buVal>"
       << "<bi_buVal species=\"Species_12\">1</bi_buVal>"
       << "<bi_buVal species=\"Species_14\">2</bi_buVal>"
       << "<bi_buVal species=\"Species_15\">2</bi_buVal>"
       << "<bi_buVal species=\"Species_16\">2</bi_buVal>"
       << "<bi_buVal species=\"Species_17\">0</bi_buVal>"
       << "<bi_buVal species=\"Species_18\">0</bi_buVal>"
       << "<bi_buVal species=\"Species_19\">0</bi_buVal>"
       << "</bi_biomassUnits>"
       << "<bi_useCorrectionFactor>"
       << "<bi_ucfVal species=\"Species_1\">1</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_2\">1</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_3\">1</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_4\">1</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_5\">1</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_6\">1</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_7\">1</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_8\">1</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_9\">1</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_10\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_11\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_12\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_14\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_15\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_16\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_17\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_18\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_19\">0</bi_ucfVal>"
       << "</bi_useCorrectionFactor>"
       << "<bi_correctionFactorValue>"
       << "<bi_cfvVal species=\"Species_1\">1.07</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_2\">1.08</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_3\">1.09</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_4\">1.1</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_5\">1.2</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_6\">1.9</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_7\">1.8</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_8\">1.7</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_9\">1.6</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_10\">1</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_11\">1</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_12\">1</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_14\">1</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_15\">1</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_16\">1</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_17\">1</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_18\">1</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_19\">1</bi_cfvVal>"
       << "</bi_correctionFactorValue>"
       << "<bi_whatDia>"
       << "<bi_wdVal species=\"Species_1\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_2\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_3\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_4\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_5\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_6\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_7\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_8\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_9\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_10\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_11\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_12\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_14\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_15\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_16\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_17\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_18\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_19\">0</bi_wdVal>"
       << "</bi_whatDia>"
       << "</DimensionAnalysis1>"
       << "</paramFile>";

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteDimensionAnalysisXMLFile7()
////////////////////////////////////////////////////////////////////////////
const char* WriteDimensionAnalysisXMLFile7() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteDimensionAnalysisCommonStuff(oOut);

  oOut << "<DimensionAnalysis1>"
       << "<bi_a>"
       << "<bi_aVal species=\"Species_1\">1.23</bi_aVal>"
       << "<bi_aVal species=\"Species_2\">0.3</bi_aVal>"
       << "<bi_aVal species=\"Species_3\">0.4</bi_aVal>"
       << "<bi_aVal species=\"Species_4\">0.5</bi_aVal>"
       << "<bi_aVal species=\"Species_5\">0.6</bi_aVal>"
       << "<bi_aVal species=\"Species_6\">0.7</bi_aVal>"
       << "<bi_aVal species=\"Species_7\">3.2</bi_aVal>"
       << "<bi_aVal species=\"Species_8\">0.9</bi_aVal>"
       << "<bi_aVal species=\"Species_9\">1</bi_aVal>"
       << "<bi_aVal species=\"Species_10\">1.23</bi_aVal>"
       << "<bi_aVal species=\"Species_11\">0.3</bi_aVal>"
       << "<bi_aVal species=\"Species_12\">0.4</bi_aVal>"
       << "<bi_aVal species=\"Species_14\">0.5</bi_aVal>"
       << "<bi_aVal species=\"Species_15\">0.6</bi_aVal>"
       << "<bi_aVal species=\"Species_16\">0.7</bi_aVal>"
       << "<bi_aVal species=\"Species_17\">3.2</bi_aVal>"
       << "<bi_aVal species=\"Species_18\">0.9</bi_aVal>"
       << "<bi_aVal species=\"Species_19\">1</bi_aVal>"
       << "</bi_a>"
       << "<bi_b>"
       << "<bi_bVal species=\"Species_1\">0.75</bi_bVal>"
       << "<bi_bVal species=\"Species_2\">0.74</bi_bVal>"
       << "<bi_bVal species=\"Species_3\">0.75</bi_bVal>"
       << "<bi_bVal species=\"Species_4\">0.76</bi_bVal>"
       << "<bi_bVal species=\"Species_5\">0.77</bi_bVal>"
       << "<bi_bVal species=\"Species_6\">0.78</bi_bVal>"
       << "<bi_bVal species=\"Species_7\">0.79</bi_bVal>"
       << "<bi_bVal species=\"Species_8\">0.8</bi_bVal>"
       << "<bi_bVal species=\"Species_9\">0.81</bi_bVal>"
       << "<bi_bVal species=\"Species_10\">0.73</bi_bVal>"
       << "<bi_bVal species=\"Species_11\">0.74</bi_bVal>"
       << "<bi_bVal species=\"Species_12\">0.75</bi_bVal>"
       << "<bi_bVal species=\"Species_14\">0.76</bi_bVal>"
       << "<bi_bVal species=\"Species_15\">0.77</bi_bVal>"
       << "<bi_bVal species=\"Species_16\">0.78</bi_bVal>"
       << "<bi_bVal species=\"Species_17\">0.79</bi_bVal>"
       << "<bi_bVal species=\"Species_18\">0.8</bi_bVal>"
       << "<bi_bVal species=\"Species_19\">0.81</bi_bVal>"
       << "</bi_b>"
       << "<bi_c>"
       << "<bi_cVal species=\"Species_1\">1</bi_cVal>"
       << "<bi_cVal species=\"Species_2\">1</bi_cVal>"
       << "<bi_cVal species=\"Species_3\">1</bi_cVal>"
       << "<bi_cVal species=\"Species_4\">1</bi_cVal>"
       << "<bi_cVal species=\"Species_5\">1</bi_cVal>"
       << "<bi_cVal species=\"Species_6\">1</bi_cVal>"
       << "<bi_cVal species=\"Species_7\">1</bi_cVal>"
       << "<bi_cVal species=\"Species_8\">1</bi_cVal>"
       << "<bi_cVal species=\"Species_9\">1</bi_cVal>"
       << "<bi_cVal species=\"Species_10\">1</bi_cVal>"
       << "<bi_cVal species=\"Species_11\">1</bi_cVal>"
       << "<bi_cVal species=\"Species_12\">1</bi_cVal>"
       << "<bi_cVal species=\"Species_14\">1</bi_cVal>"
       << "<bi_cVal species=\"Species_15\">1</bi_cVal>"
       << "<bi_cVal species=\"Species_16\">1</bi_cVal>"
       << "<bi_cVal species=\"Species_17\">1</bi_cVal>"
       << "<bi_cVal species=\"Species_18\">1</bi_cVal>"
       << "<bi_cVal species=\"Species_19\">1</bi_cVal>"
       << "</bi_c>"
       << "<bi_d>"
       << "<bi_dVal species=\"Species_1\">1</bi_dVal>"
       << "<bi_dVal species=\"Species_2\">1</bi_dVal>"
       << "<bi_dVal species=\"Species_3\">1</bi_dVal>"
       << "<bi_dVal species=\"Species_4\">1</bi_dVal>"
       << "<bi_dVal species=\"Species_5\">1</bi_dVal>"
       << "<bi_dVal species=\"Species_6\">1</bi_dVal>"
       << "<bi_dVal species=\"Species_7\">1</bi_dVal>"
       << "<bi_dVal species=\"Species_8\">1</bi_dVal>"
       << "<bi_dVal species=\"Species_9\">1</bi_dVal>"
       << "<bi_dVal species=\"Species_10\">1</bi_dVal>"
       << "<bi_dVal species=\"Species_11\">1</bi_dVal>"
       << "<bi_dVal species=\"Species_12\">1</bi_dVal>"
       << "<bi_dVal species=\"Species_14\">1</bi_dVal>"
       << "<bi_dVal species=\"Species_15\">1</bi_dVal>"
       << "<bi_dVal species=\"Species_16\">1</bi_dVal>"
       << "<bi_dVal species=\"Species_17\">1</bi_dVal>"
       << "<bi_dVal species=\"Species_18\">1</bi_dVal>"
       << "<bi_dVal species=\"Species_19\">1</bi_dVal>"
       << "</bi_d>"
       << "<bi_e>"
       << "<bi_eVal species=\"Species_1\">1</bi_eVal>"
       << "<bi_eVal species=\"Species_2\">1</bi_eVal>"
       << "<bi_eVal species=\"Species_3\">1</bi_eVal>"
       << "<bi_eVal species=\"Species_4\">1</bi_eVal>"
       << "<bi_eVal species=\"Species_5\">1</bi_eVal>"
       << "<bi_eVal species=\"Species_6\">1</bi_eVal>"
       << "<bi_eVal species=\"Species_7\">1</bi_eVal>"
       << "<bi_eVal species=\"Species_8\">1</bi_eVal>"
       << "<bi_eVal species=\"Species_9\">1</bi_eVal>"
       << "<bi_eVal species=\"Species_10\">1</bi_eVal>"
       << "<bi_eVal species=\"Species_11\">1</bi_eVal>"
       << "<bi_eVal species=\"Species_12\">1</bi_eVal>"
       << "<bi_eVal species=\"Species_14\">1</bi_eVal>"
       << "<bi_eVal species=\"Species_15\">1</bi_eVal>"
       << "<bi_eVal species=\"Species_16\">1</bi_eVal>"
       << "<bi_eVal species=\"Species_17\">1</bi_eVal>"
       << "<bi_eVal species=\"Species_18\">1</bi_eVal>"
       << "<bi_eVal species=\"Species_19\">1</bi_eVal>"
       << "</bi_e>"
       << "<bi_eqID>"
       << "<bi_eiVal species=\"Species_1\">9</bi_eiVal>"
       << "<bi_eiVal species=\"Species_2\">9</bi_eiVal>"
       << "<bi_eiVal species=\"Species_3\">9</bi_eiVal>"
       << "<bi_eiVal species=\"Species_4\">9</bi_eiVal>"
       << "<bi_eiVal species=\"Species_5\">9</bi_eiVal>"
       << "<bi_eiVal species=\"Species_6\">9</bi_eiVal>"
       << "<bi_eiVal species=\"Species_7\">9</bi_eiVal>"
       << "<bi_eiVal species=\"Species_8\">9</bi_eiVal>"
       << "<bi_eiVal species=\"Species_9\">9</bi_eiVal>"
       << "<bi_eiVal species=\"Species_10\">9</bi_eiVal>"
       << "<bi_eiVal species=\"Species_11\">9</bi_eiVal>"
       << "<bi_eiVal species=\"Species_12\">9</bi_eiVal>"
       << "<bi_eiVal species=\"Species_14\">9</bi_eiVal>"
       << "<bi_eiVal species=\"Species_15\">9</bi_eiVal>"
       << "<bi_eiVal species=\"Species_16\">9</bi_eiVal>"
       << "<bi_eiVal species=\"Species_17\">9</bi_eiVal>"
       << "<bi_eiVal species=\"Species_18\">9</bi_eiVal>"
       << "<bi_eiVal species=\"Species_19\">9</bi_eiVal>"
       << "</bi_eqID>"
       << "<bi_dbhUnits>"
       << "<bi_duVal species=\"Species_1\">0</bi_duVal>"
       << "<bi_duVal species=\"Species_2\">1</bi_duVal>"
       << "<bi_duVal species=\"Species_3\">2</bi_duVal>"
       << "<bi_duVal species=\"Species_4\">0</bi_duVal>"
       << "<bi_duVal species=\"Species_5\">1</bi_duVal>"
       << "<bi_duVal species=\"Species_6\">2</bi_duVal>"
       << "<bi_duVal species=\"Species_7\">0</bi_duVal>"
       << "<bi_duVal species=\"Species_8\">1</bi_duVal>"
       << "<bi_duVal species=\"Species_9\">2</bi_duVal>"
       << "<bi_duVal species=\"Species_10\">0</bi_duVal>"
       << "<bi_duVal species=\"Species_11\">1</bi_duVal>"
       << "<bi_duVal species=\"Species_12\">2</bi_duVal>"
       << "<bi_duVal species=\"Species_14\">0</bi_duVal>"
       << "<bi_duVal species=\"Species_15\">1</bi_duVal>"
       << "<bi_duVal species=\"Species_16\">2</bi_duVal>"
       << "<bi_duVal species=\"Species_17\">0</bi_duVal>"
       << "<bi_duVal species=\"Species_18\">1</bi_duVal>"
       << "<bi_duVal species=\"Species_19\">2</bi_duVal>"
       << "</bi_dbhUnits>"
       << "<bi_biomassUnits>"
       << "<bi_buVal species=\"Species_1\">1</bi_buVal>"
       << "<bi_buVal species=\"Species_2\">1</bi_buVal>"
       << "<bi_buVal species=\"Species_3\">1</bi_buVal>"
       << "<bi_buVal species=\"Species_4\">2</bi_buVal>"
       << "<bi_buVal species=\"Species_5\">2</bi_buVal>"
       << "<bi_buVal species=\"Species_6\">2</bi_buVal>"
       << "<bi_buVal species=\"Species_7\">0</bi_buVal>"
       << "<bi_buVal species=\"Species_8\">0</bi_buVal>"
       << "<bi_buVal species=\"Species_9\">0</bi_buVal>"
       << "<bi_buVal species=\"Species_10\">1</bi_buVal>"
       << "<bi_buVal species=\"Species_11\">1</bi_buVal>"
       << "<bi_buVal species=\"Species_12\">1</bi_buVal>"
       << "<bi_buVal species=\"Species_14\">2</bi_buVal>"
       << "<bi_buVal species=\"Species_15\">2</bi_buVal>"
       << "<bi_buVal species=\"Species_16\">2</bi_buVal>"
       << "<bi_buVal species=\"Species_17\">0</bi_buVal>"
       << "<bi_buVal species=\"Species_18\">0</bi_buVal>"
       << "<bi_buVal species=\"Species_19\">0</bi_buVal>"
       << "</bi_biomassUnits>"
       << "<bi_useCorrectionFactor>"
       << "<bi_ucfVal species=\"Species_1\">1</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_2\">1</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_3\">1</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_4\">1</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_5\">1</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_6\">1</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_7\">1</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_8\">1</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_9\">1</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_10\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_11\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_12\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_14\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_15\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_16\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_17\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_18\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_19\">0</bi_ucfVal>"
       << "</bi_useCorrectionFactor>"
       << "<bi_correctionFactorValue>"
       << "<bi_cfvVal species=\"Species_1\">1.07</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_2\">1.08</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_3\">1.09</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_4\">1.1</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_5\">1.2</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_6\">1.9</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_7\">1.8</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_8\">1.7</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_9\">1.6</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_10\">0</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_11\">0</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_12\">0</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_14\">0</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_15\">0</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_16\">0</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_17\">0</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_18\">0</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_19\">0</bi_cfvVal>"
       << "</bi_correctionFactorValue>"
       << "<bi_whatDia>"
       << "<bi_wdVal species=\"Species_1\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_2\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_3\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_4\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_5\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_6\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_7\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_8\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_9\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_10\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_11\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_12\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_14\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_15\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_16\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_17\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_18\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_19\">0</bi_wdVal>"
       << "</bi_whatDia>"
       << "</DimensionAnalysis1>"
       << "</paramFile>";

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteDimensionAnalysisXMLFile8()
////////////////////////////////////////////////////////////////////////////
const char* WriteDimensionAnalysisXMLFile8() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteDimensionAnalysisCommonStuff(oOut);

  oOut << "<DimensionAnalysis1>"
       << "<bi_a>"
       << "<bi_aVal species=\"Species_1\">0</bi_aVal>"
       << "<bi_aVal species=\"Species_2\">4.5</bi_aVal>"
       << "<bi_aVal species=\"Species_3\">4.4</bi_aVal>"
       << "<bi_aVal species=\"Species_4\">4.3</bi_aVal>"
       << "<bi_aVal species=\"Species_5\">4.2</bi_aVal>"
       << "<bi_aVal species=\"Species_6\">0</bi_aVal>"
       << "<bi_aVal species=\"Species_7\">4</bi_aVal>"
       << "<bi_aVal species=\"Species_8\">4.6</bi_aVal>"
       << "<bi_aVal species=\"Species_9\">4.7</bi_aVal>"
       << "<bi_aVal species=\"Species_10\">1.23</bi_aVal>"
       << "<bi_aVal species=\"Species_11\">0.3</bi_aVal>"
       << "<bi_aVal species=\"Species_12\">0.4</bi_aVal>"
       << "<bi_aVal species=\"Species_14\">0.5</bi_aVal>"
       << "<bi_aVal species=\"Species_15\">0.6</bi_aVal>"
       << "<bi_aVal species=\"Species_16\">0.7</bi_aVal>"
       << "<bi_aVal species=\"Species_17\">3.2</bi_aVal>"
       << "<bi_aVal species=\"Species_18\">0.9</bi_aVal>"
       << "<bi_aVal species=\"Species_19\">1</bi_aVal>"
       << "</bi_a>"
       << "<bi_b>"
       << "<bi_bVal species=\"Species_1\">0</bi_bVal>"
       << "<bi_bVal species=\"Species_2\">0.2</bi_bVal>"
       << "<bi_bVal species=\"Species_3\">0.22</bi_bVal>"
       << "<bi_bVal species=\"Species_4\">0.26</bi_bVal>"
       << "<bi_bVal species=\"Species_5\">0.28</bi_bVal>"
       << "<bi_bVal species=\"Species_6\">0</bi_bVal>"
       << "<bi_bVal species=\"Species_7\">4.21</bi_bVal>"
       << "<bi_bVal species=\"Species_8\">0.16</bi_bVal>"
       << "<bi_bVal species=\"Species_9\">0.14</bi_bVal>"
       << "<bi_bVal species=\"Species_10\">0.73</bi_bVal>"
       << "<bi_bVal species=\"Species_11\">0.74</bi_bVal>"
       << "<bi_bVal species=\"Species_12\">0.75</bi_bVal>"
       << "<bi_bVal species=\"Species_14\">0.76</bi_bVal>"
       << "<bi_bVal species=\"Species_15\">0.77</bi_bVal>"
       << "<bi_bVal species=\"Species_16\">0.78</bi_bVal>"
       << "<bi_bVal species=\"Species_17\">0.79</bi_bVal>"
       << "<bi_bVal species=\"Species_18\">0.8</bi_bVal>"
       << "<bi_bVal species=\"Species_19\">0.81</bi_bVal>"
       << "</bi_b>"
       << "<bi_c>"
       << "<bi_cVal species=\"Species_1\">3.3716</bi_cVal>"
       << "<bi_cVal species=\"Species_2\">0.05</bi_cVal>"
       << "<bi_cVal species=\"Species_3\">0.06</bi_cVal>"
       << "<bi_cVal species=\"Species_4\">0.005</bi_cVal>"
       << "<bi_cVal species=\"Species_5\">0.006</bi_cVal>"
       << "<bi_cVal species=\"Species_6\">3.3716</bi_cVal>"
       << "<bi_cVal species=\"Species_7\">0.008</bi_cVal>"
       << "<bi_cVal species=\"Species_8\">2.4</bi_cVal>"
       << "<bi_cVal species=\"Species_9\">1.4</bi_cVal>"
       << "<bi_cVal species=\"Species_10\">1</bi_cVal>"
       << "<bi_cVal species=\"Species_11\">1</bi_cVal>"
       << "<bi_cVal species=\"Species_12\">1</bi_cVal>"
       << "<bi_cVal species=\"Species_14\">1</bi_cVal>"
       << "<bi_cVal species=\"Species_15\">1</bi_cVal>"
       << "<bi_cVal species=\"Species_16\">1</bi_cVal>"
       << "<bi_cVal species=\"Species_17\">1</bi_cVal>"
       << "<bi_cVal species=\"Species_18\">1</bi_cVal>"
       << "<bi_cVal species=\"Species_19\">1</bi_cVal>"
       << "</bi_c>"
       << "<bi_d>"
       << "<bi_dVal species=\"Species_1\">0.6</bi_dVal>"
       << "<bi_dVal species=\"Species_2\">0.2</bi_dVal>"
       << "<bi_dVal species=\"Species_3\">0.25</bi_dVal>"
       << "<bi_dVal species=\"Species_4\">0</bi_dVal>"
       << "<bi_dVal species=\"Species_5\">0.23</bi_dVal>"
       << "<bi_dVal species=\"Species_6\">1.101</bi_dVal>"
       << "<bi_dVal species=\"Species_7\">0.03</bi_dVal>"
       << "<bi_dVal species=\"Species_8\">2.1</bi_dVal>"
       << "<bi_dVal species=\"Species_9\">3.2</bi_dVal>"
       << "<bi_dVal species=\"Species_10\">1</bi_dVal>"
       << "<bi_dVal species=\"Species_11\">1</bi_dVal>"
       << "<bi_dVal species=\"Species_12\">1</bi_dVal>"
       << "<bi_dVal species=\"Species_14\">1</bi_dVal>"
       << "<bi_dVal species=\"Species_15\">1</bi_dVal>"
       << "<bi_dVal species=\"Species_16\">1</bi_dVal>"
       << "<bi_dVal species=\"Species_17\">1</bi_dVal>"
       << "<bi_dVal species=\"Species_18\">1</bi_dVal>"
       << "<bi_dVal species=\"Species_19\">1</bi_dVal>"
       << "</bi_d>"
       << "<bi_e>"
       << "<bi_eVal species=\"Species_1\">1</bi_eVal>"
       << "<bi_eVal species=\"Species_2\">1</bi_eVal>"
       << "<bi_eVal species=\"Species_3\">1</bi_eVal>"
       << "<bi_eVal species=\"Species_4\">1</bi_eVal>"
       << "<bi_eVal species=\"Species_5\">1</bi_eVal>"
       << "<bi_eVal species=\"Species_6\">1</bi_eVal>"
       << "<bi_eVal species=\"Species_7\">1</bi_eVal>"
       << "<bi_eVal species=\"Species_8\">1</bi_eVal>"
       << "<bi_eVal species=\"Species_9\">1</bi_eVal>"
       << "<bi_eVal species=\"Species_10\">1</bi_eVal>"
       << "<bi_eVal species=\"Species_11\">1</bi_eVal>"
       << "<bi_eVal species=\"Species_12\">1</bi_eVal>"
       << "<bi_eVal species=\"Species_14\">1</bi_eVal>"
       << "<bi_eVal species=\"Species_15\">1</bi_eVal>"
       << "<bi_eVal species=\"Species_16\">1</bi_eVal>"
       << "<bi_eVal species=\"Species_17\">1</bi_eVal>"
       << "<bi_eVal species=\"Species_18\">1</bi_eVal>"
       << "<bi_eVal species=\"Species_19\">1</bi_eVal>"
       << "</bi_e>"
       << "<bi_eqID>"
       << "<bi_eiVal species=\"Species_1\">4</bi_eiVal>"
       << "<bi_eiVal species=\"Species_2\">4</bi_eiVal>"
       << "<bi_eiVal species=\"Species_3\">4</bi_eiVal>"
       << "<bi_eiVal species=\"Species_4\">4</bi_eiVal>"
       << "<bi_eiVal species=\"Species_5\">4</bi_eiVal>"
       << "<bi_eiVal species=\"Species_6\">4</bi_eiVal>"
       << "<bi_eiVal species=\"Species_7\">4</bi_eiVal>"
       << "<bi_eiVal species=\"Species_8\">4</bi_eiVal>"
       << "<bi_eiVal species=\"Species_9\">4</bi_eiVal>"
       << "<bi_eiVal species=\"Species_10\">9</bi_eiVal>"
       << "<bi_eiVal species=\"Species_11\">9</bi_eiVal>"
       << "<bi_eiVal species=\"Species_12\">9</bi_eiVal>"
       << "<bi_eiVal species=\"Species_14\">9</bi_eiVal>"
       << "<bi_eiVal species=\"Species_15\">9</bi_eiVal>"
       << "<bi_eiVal species=\"Species_16\">9</bi_eiVal>"
       << "<bi_eiVal species=\"Species_17\">9</bi_eiVal>"
       << "<bi_eiVal species=\"Species_18\">9</bi_eiVal>"
       << "<bi_eiVal species=\"Species_19\">9</bi_eiVal>"
       << "</bi_eqID>"
       << "<bi_dbhUnits>"
       << "<bi_duVal species=\"Species_1\">0</bi_duVal>"
       << "<bi_duVal species=\"Species_2\">1</bi_duVal>"
       << "<bi_duVal species=\"Species_3\">2</bi_duVal>"
       << "<bi_duVal species=\"Species_4\">0</bi_duVal>"
       << "<bi_duVal species=\"Species_5\">1</bi_duVal>"
       << "<bi_duVal species=\"Species_6\">2</bi_duVal>"
       << "<bi_duVal species=\"Species_7\">0</bi_duVal>"
       << "<bi_duVal species=\"Species_8\">1</bi_duVal>"
       << "<bi_duVal species=\"Species_9\">2</bi_duVal>"
       << "<bi_duVal species=\"Species_10\">0</bi_duVal>"
       << "<bi_duVal species=\"Species_11\">1</bi_duVal>"
       << "<bi_duVal species=\"Species_12\">2</bi_duVal>"
       << "<bi_duVal species=\"Species_14\">0</bi_duVal>"
       << "<bi_duVal species=\"Species_15\">1</bi_duVal>"
       << "<bi_duVal species=\"Species_16\">2</bi_duVal>"
       << "<bi_duVal species=\"Species_17\">0</bi_duVal>"
       << "<bi_duVal species=\"Species_18\">1</bi_duVal>"
       << "<bi_duVal species=\"Species_19\">2</bi_duVal>"
       << "</bi_dbhUnits>"
       << "<bi_biomassUnits>"
       << "<bi_buVal species=\"Species_1\">1</bi_buVal>"
       << "<bi_buVal species=\"Species_2\">1</bi_buVal>"
       << "<bi_buVal species=\"Species_3\">1</bi_buVal>"
       << "<bi_buVal species=\"Species_4\">2</bi_buVal>"
       << "<bi_buVal species=\"Species_5\">2</bi_buVal>"
       << "<bi_buVal species=\"Species_6\">2</bi_buVal>"
       << "<bi_buVal species=\"Species_7\">0</bi_buVal>"
       << "<bi_buVal species=\"Species_8\">0</bi_buVal>"
       << "<bi_buVal species=\"Species_9\">0</bi_buVal>"
       << "<bi_buVal species=\"Species_10\">1</bi_buVal>"
       << "<bi_buVal species=\"Species_11\">1</bi_buVal>"
       << "<bi_buVal species=\"Species_12\">1</bi_buVal>"
       << "<bi_buVal species=\"Species_14\">2</bi_buVal>"
       << "<bi_buVal species=\"Species_15\">2</bi_buVal>"
       << "<bi_buVal species=\"Species_16\">2</bi_buVal>"
       << "<bi_buVal species=\"Species_17\">0</bi_buVal>"
       << "<bi_buVal species=\"Species_18\">0</bi_buVal>"
       << "<bi_buVal species=\"Species_19\">0</bi_buVal>"
       << "</bi_biomassUnits>"
       << "<bi_useCorrectionFactor>"
       << "<bi_ucfVal species=\"Species_1\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_2\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_3\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_4\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_5\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_6\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_7\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_8\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_9\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_10\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_11\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_12\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_14\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_15\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_16\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_17\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_18\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_19\">0</bi_ucfVal>"
       << "</bi_useCorrectionFactor>"
       << "<bi_correctionFactorValue>"
       << "<bi_cfvVal species=\"Species_1\">1.07</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_2\">1.08</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_3\">1.09</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_4\">1.1</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_5\">1.2</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_6\">1.9</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_7\">1.8</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_8\">1.7</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_9\">1.6</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_10\">0</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_11\">0</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_12\">0</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_14\">0</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_15\">0</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_16\">0</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_17\">0</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_18\">0</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_19\">0</bi_cfvVal>"
       << "</bi_correctionFactorValue>"
       << "<bi_whatDia>"
       << "<bi_wdVal species=\"Species_1\">1</bi_wdVal>"
       << "<bi_wdVal species=\"Species_2\">1</bi_wdVal>"
       << "<bi_wdVal species=\"Species_3\">1</bi_wdVal>"
       << "<bi_wdVal species=\"Species_4\">1</bi_wdVal>"
       << "<bi_wdVal species=\"Species_5\">1</bi_wdVal>"
       << "<bi_wdVal species=\"Species_6\">1</bi_wdVal>"
       << "<bi_wdVal species=\"Species_7\">1</bi_wdVal>"
       << "<bi_wdVal species=\"Species_8\">1</bi_wdVal>"
       << "<bi_wdVal species=\"Species_9\">1</bi_wdVal>"
       << "<bi_wdVal species=\"Species_10\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_11\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_12\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_14\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_15\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_16\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_17\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_18\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_19\">0</bi_wdVal>"
       << "</bi_whatDia>"
       << "</DimensionAnalysis1>"
       << "</paramFile>";

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteDimensionAnalysisXMLErrorFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteDimensionAnalysisXMLErrorFile1() {
  using namespace std;

  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteDimensionAnalysisCommonErrorStuff(oOut);

  oOut << "<DimensionAnalysis1>"
       << "<bi_a>"
       << "<bi_aVal species=\"Species_1\">-0.99</bi_aVal>"
       << "<bi_aVal species=\"Species_2\">-1.01</bi_aVal>"
       << "</bi_a>"
       << "<bi_b>"
       << "<bi_bVal species=\"Species_1\">2.2</bi_bVal>"
       << "<bi_bVal species=\"Species_2\">2.41</bi_bVal>"
       << "</bi_b>"
       << "<bi_c>"
       << "<bi_cVal species=\"Species_1\">0.9</bi_cVal>"
       << "<bi_cVal species=\"Species_2\">1</bi_cVal>"
       << "</bi_c>"
       << "<bi_d>"
       << "<bi_dVal species=\"Species_1\">1</bi_dVal>"
       << "<bi_dVal species=\"Species_2\">1</bi_dVal>"
       << "</bi_d>"
       << "<bi_e>"
       << "<bi_eVal species=\"Species_1\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_2\">0</bi_eVal>"
       << "</bi_e>"
       << "<bi_eqID>"
       << "<bi_eiVal species=\"Species_1\">0</bi_eiVal>"
       << "<bi_eiVal species=\"Species_2\">1</bi_eiVal>"
       << "</bi_eqID>"
       << "<bi_dbhUnits>"
       << "<bi_duVal species=\"Species_1\">0</bi_duVal>"
       << "<bi_duVal species=\"Species_2\">1</bi_duVal>"
       << "</bi_dbhUnits>"
       << "<bi_biomassUnits>"
       << "<bi_buVal species=\"Species_1\">1</bi_buVal>"
       << "<bi_buVal species=\"Species_2\">1</bi_buVal>"
       << "</bi_biomassUnits>"
       << "<bi_useCorrectionFactor>"
       << "<bi_ucfVal species=\"Species_1\">1</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_2\">1</bi_ucfVal>"
       << "</bi_useCorrectionFactor>"
       << "<bi_correctionFactorValue>"
       << "<bi_cfvVal species=\"Species_1\">1.11</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_2\">1.12</bi_cfvVal>"
       << "</bi_correctionFactorValue>"
       << "<bi_whatDia>"
       << "<bi_wdVal species=\"Species_1\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_2\">0</bi_wdVal>"
       << "</bi_whatDia>"
       << "</DimensionAnalysis1>"
       << "</paramFile>";

  return cFileString;

}

////////////////////////////////////////////////////////////////////////////
// WriteDimensionAnalysisXMLErrorFile2()
////////////////////////////////////////////////////////////////////////////
const char* WriteDimensionAnalysisXMLErrorFile2() {
  using namespace std;

  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteDimensionAnalysisCommonErrorStuff(oOut);

  oOut << "<DimensionAnalysis1>"
       << "<bi_a>"
       << "<bi_aVal species=\"Species_1\">-0.99</bi_aVal>"
       << "<bi_aVal species=\"Species_2\">-1.01</bi_aVal>"
       << "</bi_a>"
       << "<bi_b>"
       << "<bi_bVal species=\"Species_1\">2.2</bi_bVal>"
       << "<bi_bVal species=\"Species_2\">2.41</bi_bVal>"
       << "</bi_b>"
       << "<bi_c>"
       << "<bi_cVal species=\"Species_1\">0.9</bi_cVal>"
       << "<bi_cVal species=\"Species_2\">1</bi_cVal>"
       << "</bi_c>"
       << "<bi_d>"
       << "<bi_dVal species=\"Species_1\">1</bi_dVal>"
       << "<bi_dVal species=\"Species_2\">1</bi_dVal>"
       << "</bi_d>"
       << "<bi_e>"
       << "<bi_eVal species=\"Species_1\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_2\">0</bi_eVal>"
       << "</bi_e>"
       << "<bi_eqID>"
       << "<bi_eiVal species=\"Species_1\">1</bi_eiVal>"
       << "<bi_eiVal species=\"Species_2\">1</bi_eiVal>"
       << "</bi_eqID>"
       << "<bi_dbhUnits>"
       << "<bi_duVal species=\"Species_1\">0</bi_duVal>"
       << "<bi_duVal species=\"Species_2\">3</bi_duVal>"
       << "</bi_dbhUnits>"
       << "<bi_biomassUnits>"
       << "<bi_buVal species=\"Species_1\">1</bi_buVal>"
       << "<bi_buVal species=\"Species_2\">1</bi_buVal>"
       << "</bi_biomassUnits>"
       << "<bi_useCorrectionFactor>"
       << "<bi_ucfVal species=\"Species_1\">1</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_2\">1</bi_ucfVal>"
       << "</bi_useCorrectionFactor>"
       << "<bi_correctionFactorValue>"
       << "<bi_cfvVal species=\"Species_1\">1.11</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_2\">1.12</bi_cfvVal>"
       << "</bi_correctionFactorValue>"
       << "<bi_whatDia>"
       << "<bi_wdVal species=\"Species_1\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_2\">0</bi_wdVal>"
       << "</bi_whatDia>"
       << "</DimensionAnalysis1>"
       << "</paramFile>";

  return cFileString;

}

////////////////////////////////////////////////////////////////////////////
// WriteDimensionAnalysisXMLErrorFile3()
////////////////////////////////////////////////////////////////////////////
const char* WriteDimensionAnalysisXMLErrorFile3() {
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
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
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
       << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_2\">39.48</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_2\">0.0549</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">0.8008</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_2\">0.389</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_2\">0.03418</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_2\">0.0299</tr_soahVal>"
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
       << "<behaviorName>DimensionAnalysis</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
       << "</behavior>"
       << "</behaviorList>";

       oOut << "<DimensionAnalysis1>"
       << "<bi_a>"
       << "<bi_aVal species=\"Species_1\">-0.99</bi_aVal>"
       << "<bi_aVal species=\"Species_2\">-1.01</bi_aVal>"
       << "</bi_a>"
       << "<bi_b>"
       << "<bi_bVal species=\"Species_1\">2.2</bi_bVal>"
       << "<bi_bVal species=\"Species_2\">2.41</bi_bVal>"
       << "</bi_b>"
       << "<bi_c>"
       << "<bi_cVal species=\"Species_1\">0.9</bi_cVal>"
       << "<bi_cVal species=\"Species_2\">1</bi_cVal>"
       << "</bi_c>"
       << "<bi_d>"
       << "<bi_dVal species=\"Species_1\">1</bi_dVal>"
       << "<bi_dVal species=\"Species_2\">1</bi_dVal>"
       << "</bi_d>"
       << "<bi_e>"
       << "<bi_eVal species=\"Species_1\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_2\">0</bi_eVal>"
       << "</bi_e>"
       << "<bi_eqID>"
       << "<bi_eiVal species=\"Species_1\">1</bi_eiVal>"
       << "<bi_eiVal species=\"Species_2\">1</bi_eiVal>"
       << "</bi_eqID>"
       << "<bi_dbhUnits>"
       << "<bi_duVal species=\"Species_1\">0</bi_duVal>"
       << "<bi_duVal species=\"Species_2\">1</bi_duVal>"
       << "</bi_dbhUnits>"
       << "<bi_biomassUnits>"
       << "<bi_buVal species=\"Species_1\">1</bi_buVal>"
       << "<bi_buVal species=\"Species_2\">1</bi_buVal>"
       << "</bi_biomassUnits>"
       << "<bi_useCorrectionFactor>"
       << "<bi_ucfVal species=\"Species_1\">1</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_2\">1</bi_ucfVal>"
       << "</bi_useCorrectionFactor>"
       << "<bi_correctionFactorValue>"
       << "<bi_cfvVal species=\"Species_1\">1.11</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_2\">1.12</bi_cfvVal>"
       << "</bi_correctionFactorValue>"
       << "<bi_whatDia>"
       << "<bi_wdVal species=\"Species_1\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_2\">0</bi_wdVal>"
       << "</bi_whatDia>"
       << "</DimensionAnalysis1>"
       << "</paramFile>";

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteDimensionAnalysisXMLErrorFile4()
////////////////////////////////////////////////////////////////////////////
const char* WriteDimensionAnalysisXMLErrorFile4() {
  using namespace std;

  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteDimensionAnalysisCommonErrorStuff(oOut);

  oOut << "<DimensionAnalysis1>"
       << "<bi_a>"
       << "<bi_aVal species=\"Species_1\">-0.99</bi_aVal>"
       << "<bi_aVal species=\"Species_2\">-1.01</bi_aVal>"
       << "</bi_a>"
       << "<bi_b>"
       << "<bi_bVal species=\"Species_1\">2.2</bi_bVal>"
       << "<bi_bVal species=\"Species_2\">2.41</bi_bVal>"
       << "</bi_b>"
       << "<bi_c>"
       << "<bi_cVal species=\"Species_1\">0.9</bi_cVal>"
       << "<bi_cVal species=\"Species_2\">1</bi_cVal>"
       << "</bi_c>"
       << "<bi_d>"
       << "<bi_dVal species=\"Species_1\">1</bi_dVal>"
       << "<bi_dVal species=\"Species_2\">1</bi_dVal>"
       << "</bi_d>"
       << "<bi_e>"
       << "<bi_eVal species=\"Species_1\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_2\">0</bi_eVal>"
       << "</bi_e>"
       << "<bi_eqID>"
       << "<bi_eiVal species=\"Species_1\">1</bi_eiVal>"
       << "<bi_eiVal species=\"Species_2\">1</bi_eiVal>"
       << "</bi_eqID>"
       << "<bi_dbhUnits>"
       << "<bi_duVal species=\"Species_1\">0</bi_duVal>"
       << "<bi_duVal species=\"Species_2\">1</bi_duVal>"
       << "</bi_dbhUnits>"
       << "<bi_biomassUnits>"
       << "<bi_buVal species=\"Species_1\">1</bi_buVal>"
       << "<bi_buVal species=\"Species_2\">4</bi_buVal>"
       << "</bi_biomassUnits>"
       << "<bi_useCorrectionFactor>"
       << "<bi_ucfVal species=\"Species_1\">1</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_2\">1</bi_ucfVal>"
       << "</bi_useCorrectionFactor>"
       << "<bi_correctionFactorValue>"
       << "<bi_cfvVal species=\"Species_1\">1.11</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_2\">1.12</bi_cfvVal>"
       << "</bi_correctionFactorValue>"
       << "<bi_whatDia>"
       << "<bi_wdVal species=\"Species_1\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_2\">0</bi_wdVal>"
       << "</bi_whatDia>"
       << "</DimensionAnalysis1>"
       << "</paramFile>";

  return cFileString;

}

////////////////////////////////////////////////////////////////////////////
// WriteDimensionAnalysisXMLErrorFile5()
////////////////////////////////////////////////////////////////////////////
const char* WriteDimensionAnalysisXMLErrorFile5() {
  using namespace std;

  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteDimensionAnalysisCommonErrorStuff(oOut);

  oOut << "<DimensionAnalysis1>"
       << "<bi_a>"
       << "<bi_aVal species=\"Species_1\">-0.99</bi_aVal>"
       << "<bi_aVal species=\"Species_2\">-1.01</bi_aVal>"
       << "</bi_a>"
       << "<bi_b>"
       << "<bi_bVal species=\"Species_1\">2.2</bi_bVal>"
       << "<bi_bVal species=\"Species_2\">2.41</bi_bVal>"
       << "</bi_b>"
       << "<bi_c>"
       << "<bi_cVal species=\"Species_1\">0.9</bi_cVal>"
       << "<bi_cVal species=\"Species_2\">1</bi_cVal>"
       << "</bi_c>"
       << "<bi_d>"
       << "<bi_dVal species=\"Species_1\">1</bi_dVal>"
       << "<bi_dVal species=\"Species_2\">1</bi_dVal>"
       << "</bi_d>"
       << "<bi_e>"
       << "<bi_eVal species=\"Species_1\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_2\">0</bi_eVal>"
       << "</bi_e>"
       << "<bi_eqID>"
       << "<bi_eiVal species=\"Species_1\">1</bi_eiVal>"
       << "<bi_eiVal species=\"Species_2\">1</bi_eiVal>"
       << "</bi_eqID>"
       << "<bi_dbhUnits>"
       << "<bi_duVal species=\"Species_1\">0</bi_duVal>"
       << "<bi_duVal species=\"Species_2\">1</bi_duVal>"
       << "</bi_dbhUnits>"
       << "<bi_biomassUnits>"
       << "<bi_buVal species=\"Species_1\">1</bi_buVal>"
       << "<bi_buVal species=\"Species_2\">1</bi_buVal>"
       << "</bi_biomassUnits>"
       << "<bi_useCorrectionFactor>"
       << "<bi_ucfVal species=\"Species_1\">1</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_2\">2</bi_ucfVal>"
       << "</bi_useCorrectionFactor>"
       << "<bi_correctionFactorValue>"
       << "<bi_cfvVal species=\"Species_1\">1.11</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_2\">1.12</bi_cfvVal>"
       << "</bi_correctionFactorValue>"
       << "<bi_whatDia>"
       << "<bi_wdVal species=\"Species_1\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_2\">0</bi_wdVal>"
       << "</bi_whatDia>"
       << "</DimensionAnalysis1>"
       << "</paramFile>";

  return cFileString;

}

////////////////////////////////////////////////////////////////////////////
// WriteDimensionAnalysisXMLErrorFile6()
////////////////////////////////////////////////////////////////////////////
const char* WriteDimensionAnalysisXMLErrorFile6() {
  using namespace std;

  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteDimensionAnalysisCommonErrorStuff(oOut);

  oOut << "<DimensionAnalysis1>"
       << "<bi_a>"
       << "<bi_aVal species=\"Species_1\">-0.99</bi_aVal>"
       << "<bi_aVal species=\"Species_2\">-1.01</bi_aVal>"
       << "</bi_a>"
       << "<bi_b>"
       << "<bi_bVal species=\"Species_1\">2.2</bi_bVal>"
       << "<bi_bVal species=\"Species_2\">2.41</bi_bVal>"
       << "</bi_b>"
       << "<bi_c>"
       << "<bi_cVal species=\"Species_1\">0.9</bi_cVal>"
       << "<bi_cVal species=\"Species_2\">1</bi_cVal>"
       << "</bi_c>"
       << "<bi_d>"
       << "<bi_dVal species=\"Species_1\">1</bi_dVal>"
       << "<bi_dVal species=\"Species_2\">1</bi_dVal>"
       << "</bi_d>"
       << "<bi_e>"
       << "<bi_eVal species=\"Species_1\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_2\">0</bi_eVal>"
       << "</bi_e>"
       << "<bi_eqID>"
       << "<bi_eiVal species=\"Species_1\">1</bi_eiVal>"
       << "<bi_eiVal species=\"Species_2\">1</bi_eiVal>"
       << "</bi_eqID>"
       << "<bi_dbhUnits>"
       << "<bi_duVal species=\"Species_1\">0</bi_duVal>"
       << "<bi_duVal species=\"Species_2\">1</bi_duVal>"
       << "</bi_dbhUnits>"
       << "<bi_biomassUnits>"
       << "<bi_buVal species=\"Species_1\">1</bi_buVal>"
       << "<bi_buVal species=\"Species_2\">1</bi_buVal>"
       << "</bi_biomassUnits>"
       << "<bi_useCorrectionFactor>"
       << "<bi_ucfVal species=\"Species_1\">1</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_2\">1</bi_ucfVal>"
       << "</bi_useCorrectionFactor>"
       << "<bi_correctionFactorValue>"
       << "<bi_cfvVal species=\"Species_1\">1.11</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_2\">1.12</bi_cfvVal>"
       << "</bi_correctionFactorValue>"
       << "<bi_whatDia>"
       << "<bi_wdVal species=\"Species_1\">4</bi_wdVal>"
       << "<bi_wdVal species=\"Species_2\">0</bi_wdVal>"
       << "</bi_whatDia>"
       << "</DimensionAnalysis1>"
       << "</paramFile>";

  return cFileString;

}

/////////////////////////////////////////////////////////////////////////////
// WriteDimensionAnalysisCommonStuff()
/////////////////////////////////////////////////////////////////////////////
void WriteDimensionAnalysisCommonStuff( std::fstream &oOut )
{
  using namespace std;
  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>2</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>200.0</plot_lenX>"
       << "<plot_lenY>200.0</plot_lenY>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "</plot>"
       << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\" />"
       << "<tr_species speciesName=\"Species_2\" />"
       << "<tr_species speciesName=\"Species_3\" />"
       << "<tr_species speciesName=\"Species_4\" />"
       << "<tr_species speciesName=\"Species_5\" />"
       << "<tr_species speciesName=\"Species_6\" />"
       << "<tr_species speciesName=\"Species_7\" />"
       << "<tr_species speciesName=\"Species_8\" />"
       << "<tr_species speciesName=\"Species_9\" />"
       << "<tr_species speciesName=\"Species_10\" />"
       << "<tr_species speciesName=\"Species_11\" />"
       << "<tr_species speciesName=\"Species_12\" />"
       << "<tr_species speciesName=\"Species_13\" />"
       << "<tr_species speciesName=\"Species_14\" />"
       << "<tr_species speciesName=\"Species_15\" />"
       << "<tr_species speciesName=\"Species_16\" />"
       << "<tr_species speciesName=\"Species_17\" />"
       << "<tr_species speciesName=\"Species_18\" />"
       << "<tr_species speciesName=\"Species_19\" />"
       << "</tr_speciesList>"
       << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
       << "<tr_minAdultDBH>"
       << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_2\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_3\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_4\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_5\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_6\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_7\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_8\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_9\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_10\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_11\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_12\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_13\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_14\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_15\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_16\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_17\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_18\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_19\">10.0</tr_madVal>"
       << "</tr_minAdultDBH>"
       << "<tr_maxSeedlingHeight>"
       << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_2\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_3\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_4\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_5\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_6\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_7\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_8\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_9\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_10\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_11\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_12\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_13\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_14\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_15\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_16\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_17\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_18\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_19\">1.35</tr_mshVal>"
       << "</tr_maxSeedlingHeight>"
       << "</trees>"
       << "<allometry>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_2\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_3\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_4\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_5\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_6\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_7\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_8\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_9\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_10\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_11\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_12\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_13\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_14\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_15\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_16\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_17\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_18\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_19\">39.48</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_2\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_3\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_4\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_5\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_6\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_7\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_8\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_9\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_10\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_11\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_12\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_13\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_14\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_15\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_16\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_17\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_18\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_19\">0.0549</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_3\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_4\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_5\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_6\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_7\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_8\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_9\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_10\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_11\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_12\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_13\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_14\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_15\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_16\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_17\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_18\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_19\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_3\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_4\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_5\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_6\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_7\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_8\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_9\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_10\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_11\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_12\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_13\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_14\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_15\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_16\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_17\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_18\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_19\">0.8008</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_3\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_4\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_5\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_6\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_7\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_8\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_9\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_10\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_11\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_12\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_13\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_14\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_15\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_16\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_17\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_18\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_19\">0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_2\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_3\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_4\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_5\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_6\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_7\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_8\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_9\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_10\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_12\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_13\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_14\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_15\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_16\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_17\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_18\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_11\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_19\">0.389</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_3\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_4\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_5\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_6\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_7\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_8\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_9\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_10\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_11\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_12\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_13\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_14\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_15\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_16\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_17\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_18\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_19\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_2\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_3\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_4\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_5\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_6\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_7\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_8\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_9\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_10\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_11\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_12\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_13\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_14\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_15\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_16\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_17\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_18\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_19\">0.03418</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_2\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_3\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_4\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_5\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_6\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_7\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_8\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_9\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_10\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_11\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_12\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_13\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_14\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_15\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_16\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_17\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_18\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_19\">0.0299</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
       << "<tr_whatSeedlingHeightDiam>"
       << "<tr_wsehdVal species=\"Species_1\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_2\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_3\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_4\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_5\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_6\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_7\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_8\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_9\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_10\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_11\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_12\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_13\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_14\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_15\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_16\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_17\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_18\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_19\">0</tr_wsehdVal>"
       << "</tr_whatSeedlingHeightDiam>"
       << "<tr_whatSaplingHeightDiam>"
       << "<tr_wsahdVal species=\"Species_1\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_2\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_3\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_4\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_5\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_6\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_7\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_8\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_9\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_10\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_11\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_12\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_13\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_14\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_15\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_16\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_17\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_18\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_19\">0</tr_wsahdVal>"
       << "</tr_whatSaplingHeightDiam>"
       << "<tr_whatAdultHeightDiam>"
       << "<tr_wahdVal species=\"Species_1\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_2\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_3\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_4\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_5\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_6\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_7\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_8\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_9\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_10\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_11\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_12\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_13\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_14\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_15\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_16\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_17\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_18\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_19\">0</tr_wahdVal>"
       << "</tr_whatAdultHeightDiam>"
       << "<tr_whatAdultCrownRadDiam>"
       << "<tr_wacrdVal species=\"Species_1\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_2\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_3\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_4\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_5\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_6\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_7\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_8\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_9\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_10\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_11\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_12\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_13\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_14\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_15\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_16\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_17\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_18\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_19\">0</tr_wacrdVal>"
       << "</tr_whatAdultCrownRadDiam>"
       << "<tr_whatAdultCrownHeightHeight>"
       << "<tr_wachhVal species=\"Species_1\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_2\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_3\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_4\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_5\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_6\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_7\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_8\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_9\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_10\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_11\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_12\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_13\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_14\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_15\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_16\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_17\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_18\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_19\">0</tr_wachhVal>"
       << "</tr_whatAdultCrownHeightHeight>"
       << "<tr_whatSaplingCrownRadDiam>"
       << "<tr_wscrdVal species=\"Species_1\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_2\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_3\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_4\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_5\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_6\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_7\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_8\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_9\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_10\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_11\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_12\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_13\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_14\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_15\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_16\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_17\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_18\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_19\">0</tr_wscrdVal>"
       << "</tr_whatSaplingCrownRadDiam>"
       << "<tr_whatSaplingCrownHeightHeight>"
       << "<tr_wschhVal species=\"Species_1\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_2\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_3\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_4\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_5\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_6\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_7\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_8\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_9\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_10\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_11\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_12\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_13\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_14\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_15\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_16\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_17\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_18\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_19\">0</tr_wschhVal>"
       << "</tr_whatSaplingCrownHeightHeight>"
       << "</allometry>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>DimensionAnalysis</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_5\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_6\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_7\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_8\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_9\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_10\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_11\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_12\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_14\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_15\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_16\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_17\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_18\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_19\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_5\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_6\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_7\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_8\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_9\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_10\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_11\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_12\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_14\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_15\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_16\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_17\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_18\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_19\" type=\"Sapling\"/>"
       << "</behavior>"
       << "</behaviorList>";
}

/////////////////////////////////////////////////////////////////////////////
// WriteDimensionAnalysisCommonErrorStuff()
/////////////////////////////////////////////////////////////////////////////
void WriteDimensionAnalysisCommonErrorStuff( std::fstream &oOut )
{
  using namespace std;
  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>2</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>200.0</plot_lenX>"
       << "<plot_lenY>200.0</plot_lenY>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
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
       << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_2\">39.48</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_2\">0.0549</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">0.8008</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
        << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_2\">0.389</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_2\">0.03418</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_2\">0.0299</tr_soahVal>"
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
       << "<tr_wacrdVal species=\"Species_3\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_4\">0</tr_wacrdVal>"
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
       << "<behaviorName>DimensionAnalysis</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>";
}

