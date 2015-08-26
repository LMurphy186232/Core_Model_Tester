//---------------------------------------------------------------------------
// TestRipleysKCalculator.cpp
//---------------------------------------------------------------------------
#include "TestRipleysKCalculator.h"
#include <gtest/gtest.h>
#include <fstream>
#include <math.h>
#include "TreePopulation.h"
#include "SimManager.h"
#include "Grid.h"
#include "BehaviorBase.h"
#include "Plot.h"
#include "RipleysKCalculator.h"
#include <sstream>

////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun1()
////////////////////////////////////////////////////////////////////////////
TEST(RipleysKCalculator, TestNormalProcessingRun1) {

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clPlot *p_oPlot;
    clGrid *p_oGrid;
    //clBehaviorBase *p_oTemp;
    //clRipleysKCalculator *p_oBeh;
    std::stringstream sLabel;
    float fExpectedValue, fActualValue;
    int i, j, iCode;

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteRipleysKCalculatorXMLFile1() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
    p_oPlot = p_oSimManager->GetPlotObject();
    p_oGrid = p_oSimManager->GetGridObject("Ripley's K");
    ASSERT_TRUE(p_oGrid != NULL);
    EXPECT_EQ(p_oGrid->GetNumberXCells(), 1);
    EXPECT_EQ(p_oGrid->GetNumberYCells(), 1);
    fExpectedValue = 1;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("inc"), &fActualValue);
    EXPECT_LT(fabs(fActualValue - fExpectedValue), 0.001);
    fExpectedValue = 50;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("dist"), &fActualValue);
    EXPECT_LT(fabs(fActualValue - fExpectedValue), 0.001);

    //Check the distance calculator
    //p_oTemp = p_oSimManager->GetBehaviorObject("Ripley's K");
    //p_oBeh = dynamic_cast<clRipleysKCalculator*>(p_oTemp);
    //ASSERT_TRUE(p_oBeh->WorthSearching(p_oPlot, 1, 1, 3, 4, 8));
    //ASSERT_TRUE(!p_oBeh->WorthSearching(p_oPlot, 1, 1, 7, 6, 8));
    //ASSERT_TRUE(p_oBeh->WorthSearching(p_oPlot, 1, 1, 3, -2, 8));
    //ASSERT_TRUE(!p_oBeh->WorthSearching(p_oPlot, 1, 1, 6, -5, 8));
    //ASSERT_TRUE(p_oBeh->WorthSearching(p_oPlot, 1, 1, -1, -1, 8));
    //ASSERT_TRUE(!p_oBeh->WorthSearching(p_oPlot, 1, 1, -5, -5, 8));
    //ASSERT_TRUE(p_oBeh->WorthSearching(p_oPlot, 1, 1, 0, 3, 8));
    //ASSERT_TRUE(!p_oBeh->WorthSearching(p_oPlot, 1, 1, -5, 6, 8));

    //Check the initial conditions - all zeroes
    for (i = 0; i < 50; i++) {
      for (j = 0; j <= 4; j++) {
        sLabel << i << "_" << j;
        iCode = p_oGrid->GetFloatDataCode(sLabel.str());
        ASSERT_TRUE(-1 != iCode);
        p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
        EXPECT_LT(fabs(fActualValue), 0.0001);
        sLabel.str("");
      }
    }

    CreateTrees(p_oPop, p_oPlot, 0);

    //Run one timestep
    p_oSimManager->RunSim(1);

    CheckRipleysKRun1Results (p_oGrid);

    p_oSimManager->RunSim(1);

    CheckRipleysKRun1Results (p_oGrid);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun2()
////////////////////////////////////////////////////////////////////////////
TEST(RipleysKCalculator, TestNormalProcessingRun2) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clPlot *p_oPlot;
    clGrid *p_oGrid;
    std::stringstream sLabel;
    float fActualValue, fExpectedValue;
    int iCode, i, j;

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteRipleysKCalculatorXMLFile2() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
    p_oPlot = p_oSimManager->GetPlotObject();
    p_oGrid = p_oSimManager->GetGridObject("Ripley's K");
    ASSERT_TRUE(p_oGrid != NULL);
    EXPECT_EQ(p_oGrid->GetNumberXCells(), 1);
    EXPECT_EQ(p_oGrid->GetNumberYCells(), 1);
    fExpectedValue = 5;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("inc"), &fActualValue);
    EXPECT_LT(fabs(fActualValue - fExpectedValue), 0.001);
    fExpectedValue = 25;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("dist"), &fActualValue);
    EXPECT_LT(fabs(fActualValue - fExpectedValue), 0.001);

    //Check the initial conditions - all zeroes
    for (i = 0; i < 5; i++) {
      for (j = 0; j <= 4; j++) {
        sLabel << i << "_" << j;
        iCode = p_oGrid->GetFloatDataCode(sLabel.str());
        ASSERT_TRUE(-1 != iCode);
        p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
        EXPECT_LT(fabs(fActualValue), 0.0001);
        sLabel.str("");
      }
    }

    CreateTrees(p_oPop, p_oPlot, 0);

    //Run one timestep
    p_oSimManager->RunSim(1);

    //Check the values for the grid - all species
    iCode = p_oGrid->GetFloatDataCode("0_4");
    fExpectedValue = 860;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("1_4");
    fExpectedValue = 2836;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("2_4");
    fExpectedValue = 5496;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("3_4");
    fExpectedValue = 8228;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("4_4");
    fExpectedValue = 11156;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    //Species 1
    iCode = p_oGrid->GetFloatDataCode("0_0");
    fExpectedValue = 3600;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("1_0");
    fExpectedValue = 12800;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("2_0");
    fExpectedValue = 17600;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("3_0");
    fExpectedValue = 18000;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("4_0");
    fExpectedValue = 18000;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    //Species 2
    iCode = p_oGrid->GetFloatDataCode("0_1");
    fExpectedValue = 3200;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("1_1");
    fExpectedValue = 10400;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("2_1");
    fExpectedValue = 18000;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("3_1");
    fExpectedValue = 18000;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("4_1");
    fExpectedValue = 18000;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    //Species 3
    iCode = p_oGrid->GetFloatDataCode("0_2");
    fExpectedValue = 1175;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("1_2");
    fExpectedValue = 3400;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("2_2");
    fExpectedValue = 5881.25;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("3_2");
    fExpectedValue = 7812.5;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("4_2");
    fExpectedValue = 10237.5;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    //Species 4
    for (i = 0; i < 5; i++) {
      sLabel << i << "_3";
      iCode = p_oGrid->GetFloatDataCode(sLabel.str());
      ASSERT_TRUE(-1 != iCode);
      p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
      EXPECT_LT(fabs(fActualValue), 0.0001);
      sLabel.str("");
    }
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun3()
////////////////////////////////////////////////////////////////////////////
TEST(RipleysKCalculator, TestNormalProcessingRun3) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clPlot *p_oPlot;
    clGrid *p_oGrid;
    std::stringstream sLabel;
    float fActualValue, fExpectedValue;
    int i, j, iCode;

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteRipleysKCalculatorXMLFile3() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
    p_oPlot = p_oSimManager->GetPlotObject();
    p_oGrid = p_oSimManager->GetGridObject("Ripley's K");
    ASSERT_TRUE(p_oGrid != NULL);
    EXPECT_EQ(p_oGrid->GetNumberXCells(), 1);
    EXPECT_EQ(p_oGrid->GetNumberYCells(), 1);

    //Check the initial conditions - all zeroes
    for (i = 0; i < 50; i++) {
      for (j = 0; j <= 4; j++) {
        sLabel << i << "_" << j;
        iCode = p_oGrid->GetFloatDataCode(sLabel.str());
        ASSERT_TRUE(-1 != iCode);
        p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
        EXPECT_LT(fabs(fActualValue), 0.0001);
        sLabel.str("");
      }
    }

    CreateTrees(p_oPop, p_oPlot, 0);

    //Run one timestep
    p_oSimManager->RunSim(1);

    //Check the values for the grid - all species
    iCode = p_oGrid->GetFloatDataCode("0_4");
    fExpectedValue = 17.9712;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("1_4");
    fExpectedValue = 55.9104;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("2_4");
    fExpectedValue = 101.8368;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("3_4");
    fExpectedValue = 154.752;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("4_4");
    fExpectedValue = 214.656;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("5_4");
    fExpectedValue = 296.5248;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("6_4");
    fExpectedValue = 387.3792;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("7_4");
    fExpectedValue = 503.1936;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("8_4");
    fExpectedValue = 599.04;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("9_4");
    fExpectedValue = 707.8656;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("10_4");
    fExpectedValue = 818.688;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("11_4");
    fExpectedValue = 940.4928;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("12_4");
    fExpectedValue = 1068.288;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("13_4");
    fExpectedValue = 1223.04;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("14_4");
    fExpectedValue = 1371.8016;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("15_4");
    fExpectedValue = 1501.5936;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("16_4");
    fExpectedValue = 1632.384;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("17_4");
    fExpectedValue = 1765.1712;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("18_4");
    fExpectedValue = 1911.936;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("19_4");
    fExpectedValue = 2053.7088;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("20_4");
    fExpectedValue = 2183.5008;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("21_4");
    fExpectedValue = 2339.2512;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("22_4");
    fExpectedValue = 2490.0096;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("23_4");
    fExpectedValue = 2642.7648;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("24_4");
    fExpectedValue = 2784.5376;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("25_4");
    fExpectedValue = 2944.2816;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("26_4");
    fExpectedValue = 3102.0288;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("27_4");
    fExpectedValue = 3263.7696;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("28_4");
    fExpectedValue = 3420.5184;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("29_4");
    fExpectedValue = 3598.2336;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("30_4");
    fExpectedValue = 3749.9904;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("31_4");
    fExpectedValue = 3889.7664;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("32_4");
    fExpectedValue = 4003.584;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("33_4");
    fExpectedValue = 4126.3872;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("34_4");
    fExpectedValue = 4243.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("35_4");
    fExpectedValue = 4365.0048;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("36_4");
    fExpectedValue = 4466.8416;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("37_4");
    fExpectedValue = 4546.7136;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("38_4");
    fExpectedValue = 4616.6016;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("39_4");
    fExpectedValue = 4680.4992;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("40_4");
    fExpectedValue = 4739.4048;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("41_4");
    fExpectedValue = 4793.3184;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("42_4");
    fExpectedValue = 4823.2704;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("43_4");
    fExpectedValue = 4851.2256;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("44_4");
    fExpectedValue = 4870.1952;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("45_4");
    fExpectedValue = 4889.1648;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("46_4");
    fExpectedValue = 4906.1376;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("47_4");
    fExpectedValue = 4924.1088;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("48_4");
    fExpectedValue = 4931.0976;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("49_4");
    fExpectedValue = 4932.096;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    //Species 1
    iCode = p_oGrid->GetFloatDataCode("0_0");
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("1_0");
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("2_0");
    fExpectedValue = 399.36;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("3_0");
    fExpectedValue = 698.88;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("4_0");
    fExpectedValue = 898.56;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("5_0");
    fExpectedValue = 1597.44;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("6_0");
    fExpectedValue = 1896.96;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("7_0");
    fExpectedValue = 2595.84;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("8_0");
    fExpectedValue = 2695.68;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("9_0");
    fExpectedValue = 3194.88;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("10_0");
    fExpectedValue = 3494.4;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("11_0");
    fExpectedValue = 3694.08;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("12_0");
    fExpectedValue = 4093.44;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("13_0");
    fExpectedValue = 4293.12;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("14_0");
    fExpectedValue = 4392.96;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("15_0");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("16_0");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("17_0");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("18_0");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("19_0");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("20_0");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("21_0");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("22_0");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("23_0");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("24_0");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("25_0");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("26_0");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("27_0");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("28_0");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("29_0");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("30_0");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("31_0");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("32_0");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("33_0");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("34_0");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("35_0");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("36_0");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("37_0");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("38_0");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("39_0");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("40_0");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("41_0");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("42_0");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("43_0");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("44_0");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("45_0");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("46_0");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("47_0");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("48_0");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("49_0");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);


    //Species 2
    iCode = p_oGrid->GetFloatDataCode("0_1");
    fExpectedValue = 99.84;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("1_1");
    fExpectedValue = 199.68;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("2_1");
    fExpectedValue = 199.68;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("3_1");
    fExpectedValue = 599.04;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("4_1");
    fExpectedValue = 798.72;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("5_1");
    fExpectedValue = 1098.24;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("6_1");
    fExpectedValue = 1896.96;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("7_1");
    fExpectedValue = 2196.48;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("8_1");
    fExpectedValue = 2496;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("9_1");
    fExpectedValue = 2595.84;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("10_1");
    fExpectedValue = 3095.04;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("11_1");
    fExpectedValue = 3893.76;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("12_1");
    fExpectedValue = 3893.76;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("13_1");
    fExpectedValue = 4293.12;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("14_1");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("15_1");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("16_1");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("17_1");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("18_1");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("19_1");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("20_1");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("21_1");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("22_1");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("23_1");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("24_1");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("25_1");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("26_1");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("27_1");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("28_1");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("29_1");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("30_1");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("31_1");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("32_1");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("33_1");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("34_1");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("35_1");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("36_1");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("37_1");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("38_1");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("39_1");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("40_1");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("41_1");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("42_1");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("43_1");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("44_1");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("45_1");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("46_1");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("47_1");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("48_1");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("49_1");
    fExpectedValue = 4492.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    //Species 3
    iCode = p_oGrid->GetFloatDataCode("0_2");
    fExpectedValue = 26.52;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("1_2");
    fExpectedValue = 82.68;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("2_2");
    fExpectedValue = 145.08;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("3_2");
    fExpectedValue = 212.16;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("4_2");
    fExpectedValue = 293.28;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("5_2");
    fExpectedValue = 400.92;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("6_2");
    fExpectedValue = 508.56;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("7_2");
    fExpectedValue = 639.6;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("8_2");
    fExpectedValue = 742.56;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("9_2");
    fExpectedValue = 848.64;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("10_2");
    fExpectedValue = 967.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("11_2");
    fExpectedValue = 1084.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("12_2");
    fExpectedValue = 1210.56;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("13_2");
    fExpectedValue = 1350.96;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("14_2");
    fExpectedValue = 1467.96;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("15_2");
    fExpectedValue = 1555.32;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("16_2");
    fExpectedValue = 1648.92;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("17_2");
    fExpectedValue = 1750.32;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("18_2");
    fExpectedValue = 1856.4;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("19_2");
    fExpectedValue = 1950;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("20_2");
    fExpectedValue = 2040.48;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("21_2");
    fExpectedValue = 2163.72;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("22_2");
    fExpectedValue = 2283.84;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("23_2");
    fExpectedValue = 2421.12;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("24_2");
    fExpectedValue = 2555.28;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("25_2");
    fExpectedValue = 2689.44;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("26_2");
    fExpectedValue = 2840.76;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("27_2");
    fExpectedValue = 2993.64;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("28_2");
    fExpectedValue = 3165.24;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("29_2");
    fExpectedValue = 3368.04;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("30_2");
    fExpectedValue = 3545.88;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("31_2");
    fExpectedValue = 3712.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("32_2");
    fExpectedValue = 3846.96;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("33_2");
    fExpectedValue = 3990.48;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("34_2");
    fExpectedValue = 4130.88;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("35_2");
    fExpectedValue = 4288.44;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("36_2");
    fExpectedValue = 4419.48;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("37_2");
    fExpectedValue = 4506.84;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("38_2");
    fExpectedValue = 4589.52;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("39_2");
    fExpectedValue = 4672.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("40_2");
    fExpectedValue = 4731.48;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("41_2");
    fExpectedValue = 4793.88;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("42_2");
    fExpectedValue = 4817.28;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("43_2");
    fExpectedValue = 4840.68;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("44_2");
    fExpectedValue = 4857.84;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("45_2");
    fExpectedValue = 4879.68;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("46_2");
    fExpectedValue = 4887.48;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("47_2");
    fExpectedValue = 4901.52;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("48_2");
    fExpectedValue = 4912.44;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("49_2");
    fExpectedValue = 4914;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    //Species 4
    for (i = 0; i < 50; i++) {
      sLabel << i << "_3";
      iCode = p_oGrid->GetFloatDataCode(sLabel.str());
      ASSERT_TRUE(-1 != iCode);
      p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
      EXPECT_LT(fabs(fActualValue), 0.0001);
      sLabel.str("");
    }

    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun4()
////////////////////////////////////////////////////////////////////////////
TEST(RipleysKCalculator, TestNormalProcessingRun4) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clPlot *p_oPlot;
    clGrid *p_oGrid;
    std::stringstream sLabel;
    float fActualValue, fExpectedValue;
    int i, j, iCode;

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteRipleysKCalculatorXMLFile4() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
    p_oPlot = p_oSimManager->GetPlotObject();
    p_oGrid = p_oSimManager->GetGridObject("Ripley's K");
    ASSERT_TRUE(p_oGrid != NULL);
    EXPECT_EQ(p_oGrid->GetNumberXCells(), 1);
    EXPECT_EQ(p_oGrid->GetNumberYCells(), 1);

    //Check the initial conditions - all zeroes
    for (i = 0; i < 50; i++) {
      for (j = 0; j <= 4; j++) {
        sLabel << i << "_" << j;
        iCode = p_oGrid->GetFloatDataCode(sLabel.str());
        ASSERT_TRUE(-1 != iCode);
        p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
        EXPECT_LT(fabs(fActualValue), 0.0001);
        sLabel.str("");
      }
    }

    CreateTrees(p_oPop, p_oPlot, 50);

    //Run one timestep
    p_oSimManager->RunSim(1);

    //Check the values for the grid - all species
    iCode = p_oGrid->GetFloatDataCode("0_4");
    fExpectedValue = 69.1488;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("1_4");
    fExpectedValue = 215.1296;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("2_4");
    fExpectedValue = 391.8432;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("3_4");
    fExpectedValue = 595.448;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("4_4");
    fExpectedValue = 825.944;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("5_4");
    fExpectedValue = 1140.9552;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("6_4");
    fExpectedValue = 1490.5408;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("7_4");
    fExpectedValue = 1936.1664;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("8_4");
    fExpectedValue = 2304.96;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("9_4");
    fExpectedValue = 2723.6944;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("10_4");
    fExpectedValue = 3150.112;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("11_4");
    fExpectedValue = 3618.7872;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("12_4");
    fExpectedValue = 4110.512;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("13_4");
    fExpectedValue = 4705.96;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("14_4");
    fExpectedValue = 5278.3584;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("15_4");
    fExpectedValue = 5777.7664;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("16_4");
    fExpectedValue = 6281.016;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("17_4");
    fExpectedValue = 6791.9488;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("18_4");
    fExpectedValue = 7356.664;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("19_4");
    fExpectedValue = 7902.1712;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("20_4");
    fExpectedValue = 8401.5792;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("21_4");
    fExpectedValue = 9000.8688;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("22_4");
    fExpectedValue = 9580.9504;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("23_4");
    fExpectedValue = 10168.7152;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("24_4");
    fExpectedValue = 10714.2224;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("25_4");
    fExpectedValue = 11328.8784;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("26_4");
    fExpectedValue = 11935.8512;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("27_4");
    fExpectedValue = 12558.1904;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("28_4");
    fExpectedValue = 13161.3216;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("29_4");
    fExpectedValue = 13845.1264;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("30_4");
    fExpectedValue = 14429.0496;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("31_4");
    fExpectedValue = 14966.8736;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("32_4");
    fExpectedValue = 15404.816;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("33_4");
    fExpectedValue = 15877.3328;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("34_4");
    fExpectedValue = 16326.8;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("35_4");
    fExpectedValue = 16795.4752;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("36_4");
    fExpectedValue = 17187.3184;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("37_4");
    fExpectedValue = 17494.6464;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("38_4");
    fExpectedValue = 17763.5584;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("39_4");
    fExpectedValue = 18009.4208;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("40_4");
    fExpectedValue = 18236.0752;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("41_4");
    fExpectedValue = 18443.5216;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("42_4");
    fExpectedValue = 18558.7696;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("43_4");
    fExpectedValue = 18666.3344;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("44_4");
    fExpectedValue = 18739.3248;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("45_4");
    fExpectedValue = 18812.3152;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("46_4");
    fExpectedValue = 18877.6224;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("47_4");
    fExpectedValue = 18946.7712;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("48_4");
    fExpectedValue = 18973.6624;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("49_4");
    fExpectedValue = 18977.504;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    //Species 1
    iCode = p_oGrid->GetFloatDataCode("0_0");
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("1_0");
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("2_0");
    fExpectedValue = 1536.64;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("3_0");
    fExpectedValue = 2689.12;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("4_0");
    fExpectedValue = 3457.44;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("5_0");
    fExpectedValue = 6146.56;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("6_0");
    fExpectedValue = 7299.04;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("7_0");
    fExpectedValue = 9988.16;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("8_0");
    fExpectedValue = 10372.32;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("9_0");
    fExpectedValue = 12293.12;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("10_0");
    fExpectedValue = 13445.6;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("11_0");
    fExpectedValue = 14213.92;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("12_0");
    fExpectedValue = 15750.56;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("13_0");
    fExpectedValue = 16518.88;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("14_0");
    fExpectedValue = 16903.04;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("15_0");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("16_0");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("17_0");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("18_0");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("19_0");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("20_0");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("21_0");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("22_0");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("23_0");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("24_0");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("25_0");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("26_0");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("27_0");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("28_0");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("29_0");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("30_0");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("31_0");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("32_0");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("33_0");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("34_0");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("35_0");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("36_0");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("37_0");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("38_0");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("39_0");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("40_0");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("41_0");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("42_0");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("43_0");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("44_0");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("45_0");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("46_0");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("47_0");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("48_0");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("49_0");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);


    //Species 2
    iCode = p_oGrid->GetFloatDataCode("0_1");
    fExpectedValue = 384.16;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("1_1");
    fExpectedValue = 768.32;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("2_1");
    fExpectedValue = 768.32;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("3_1");
    fExpectedValue = 2304.96;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("4_1");
    fExpectedValue = 3073.28;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("5_1");
    fExpectedValue = 4225.76;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("6_1");
    fExpectedValue = 7299.04;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("7_1");
    fExpectedValue = 8451.52;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("8_1");
    fExpectedValue = 9604;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("9_1");
    fExpectedValue = 9988.16;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("10_1");
    fExpectedValue = 11908.96;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("11_1");
    fExpectedValue = 14982.24;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("12_1");
    fExpectedValue = 14982.24;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("13_1");
    fExpectedValue = 16518.88;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("14_1");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("15_1");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("16_1");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("17_1");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("18_1");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("19_1");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("20_1");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("21_1");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("22_1");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("23_1");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("24_1");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("25_1");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("26_1");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("27_1");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("28_1");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("29_1");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("30_1");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("31_1");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("32_1");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("33_1");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("34_1");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("35_1");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("36_1");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("37_1");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("38_1");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("39_1");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("40_1");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("41_1");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("42_1");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("43_1");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("44_1");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("45_1");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("46_1");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("47_1");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("48_1");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("49_1");
    fExpectedValue = 17287.2;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    //Species 3
    iCode = p_oGrid->GetFloatDataCode("0_2");
    fExpectedValue = 102.0425;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("1_2");
    fExpectedValue = 318.1325;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("2_2");
    fExpectedValue = 558.2325;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("3_2");
    fExpectedValue = 816.34;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("4_2");
    fExpectedValue = 1128.47;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("5_2");
    fExpectedValue = 1542.6425;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("6_2");
    fExpectedValue = 1956.815;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("7_2");
    fExpectedValue = 2461.025;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("8_2");
    fExpectedValue = 2857.19;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("9_2");
    fExpectedValue = 3265.36;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("10_2");
    fExpectedValue = 3721.55;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("11_2");
    fExpectedValue = 4171.7375;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("12_2");
    fExpectedValue = 4657.94;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("13_2");
    fExpectedValue = 5198.165;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("14_2");
    fExpectedValue = 5648.3525;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("15_2");
    fExpectedValue = 5984.4925;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("16_2");
    fExpectedValue = 6344.6425;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("17_2");
    fExpectedValue = 6734.805;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("18_2");
    fExpectedValue = 7142.975;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("19_2");
    fExpectedValue = 7503.125;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("20_2");
    fExpectedValue = 7851.27;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("21_2");
    fExpectedValue = 8325.4675;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("22_2");
    fExpectedValue = 8787.66;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("23_2");
    fExpectedValue = 9315.88;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("24_2");
    fExpectedValue = 9832.095;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("25_2");
    fExpectedValue = 10348.31;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("26_2");
    fExpectedValue = 10930.5525;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("27_2");
    fExpectedValue = 11518.7975;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("28_2");
    fExpectedValue = 12179.0725;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("29_2");
    fExpectedValue = 12959.3975;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("30_2");
    fExpectedValue = 13643.6825;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("31_2");
    fExpectedValue = 14285.95;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("32_2");
    fExpectedValue = 14802.165;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("33_2");
    fExpectedValue = 15354.395;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("34_2");
    fExpectedValue = 15894.62;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("35_2");
    fExpectedValue = 16500.8725;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("36_2");
    fExpectedValue = 17005.0825;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("37_2");
    fExpectedValue = 17341.2225;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("38_2");
    fExpectedValue = 17659.355;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("39_2");
    fExpectedValue = 17977.4875;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("40_2");
    fExpectedValue = 18205.5825;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("41_2");
    fExpectedValue = 18445.6825;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("42_2");
    fExpectedValue = 18535.72;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("43_2");
    fExpectedValue = 18625.7575;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("44_2");
    fExpectedValue = 18691.785;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("45_2");
    fExpectedValue = 18775.82;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("46_2");
    fExpectedValue = 18805.8325;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("47_2");
    fExpectedValue = 18859.855;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("48_2");
    fExpectedValue = 18901.8725;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("49_2");
    fExpectedValue = 18907.875;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    //Species 4
    for (i = 0; i < 50; i++) {
      sLabel << i << "_3";
      iCode = p_oGrid->GetFloatDataCode(sLabel.str());
      ASSERT_TRUE(-1 != iCode);
      p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
      EXPECT_LT(fabs(fActualValue), 0.0001);
      sLabel.str("");
    }

    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestErrorProcessing()
////////////////////////////////////////////////////////////////////////////
TEST(RipleysKCalculator, TestErrorProcessing) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try
  {
    p_oSimManager->ReadFile(WriteRipleysKCalculatorXMLErrorFile1());
    FAIL() << "TestRipleysKCalculator error processing didn't catch error for WriteRipleysKCalculatorXMLErrorFile1.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clRipleysKCalculator::GetParameterFileData") != 0 &&
        err.sMoreInfo.compare("The distance increment must be less than the max distance.") != 0)
    {
      FAIL() << "TestRipleysKCalculator error processing caught wrong error for WriteRipleysKCalculatorXMLErrorFile1.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteRipleysKCalculatorXMLErrorFile2());
    FAIL() << "TestRipleysKCalculator error processing didn't catch error for WriteRipleysKCalculatorXMLErrorFile2.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clRipleysKCalculator::GetParameterFileData") != 0 &&
        err.sMoreInfo.compare("The max distance must be greater than zero.") != 0)
    {
      FAIL() << "TestRipleysKCalculator error processing caught wrong error for WriteRipleysKCalculatorXMLErrorFile2.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteRipleysKCalculatorXMLErrorFile3());
    FAIL() << "TestRipleysKCalculator error processing didn't catch error for WriteRipleysKCalculatorXMLErrorFile3.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clRipleysKCalculator::GetParameterFileData") != 0 &&
        err.sMoreInfo.compare("The distance increment must be greater than zero.") != 0)
    {
      FAIL() << "TestRipleysKCalculator error processing caught wrong error for WriteRipleysKCalculatorXMLErrorFile3.";
    }
    ;
  }
  delete p_oSimManager;
}

////////////////////////////////////////////////////////////////////////////
// WriteRipleysKCalculatorXMLFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteRipleysKCalculatorXMLFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
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
      << "</plot>";

  WriteRipleysKCalculatorCommonStuff(oOut);

  oOut << "<RipleysK1>"
      << "<an_RipleysKMaxDistance>50</an_RipleysKMaxDistance>"
      << "<an_RipleysKDistanceInc>1</an_RipleysKDistanceInc>"
      << "</RipleysK1>"
      << "</paramFile>";

  oOut.close();
  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteRipleysKCalculatorXMLFile2()
////////////////////////////////////////////////////////////////////////////
const char* WriteRipleysKCalculatorXMLFile2() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
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
      << "</plot>";

  WriteRipleysKCalculatorCommonStuff(oOut);

  oOut << "<RipleysK1>"
      << "<an_RipleysKMaxDistance>25</an_RipleysKMaxDistance>"
      << "<an_RipleysKDistanceInc>5</an_RipleysKDistanceInc>"
      << "</RipleysK1>"
      << "</paramFile>";

  oOut.close();
  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteRipleysKCalculatorXMLFile3()
////////////////////////////////////////////////////////////////////////////
const char* WriteRipleysKCalculatorXMLFile3() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">"
      << "<plot>"
      << "<timesteps>3</timesteps>"
      << "<yearsPerTimestep>1</yearsPerTimestep>"
      << "<randomSeed>1</randomSeed>"
      << "<plot_lenX>104.0</plot_lenX>"
      << "<plot_lenY>96.0</plot_lenY>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88171785</plot_temp_C>"
      << "<plot_latitude>55.37</plot_latitude>"
      << "</plot>";

  WriteRipleysKCalculatorCommonStuff(oOut);

  oOut << "<RipleysK1>"
      << "<an_RipleysKMaxDistance>50</an_RipleysKMaxDistance>"
      << "<an_RipleysKDistanceInc>1</an_RipleysKDistanceInc>"
      << "</RipleysK1>"
      << "</paramFile>";

  oOut.close();
  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteRipleysKCalculatorXMLFile4()
////////////////////////////////////////////////////////////////////////////
const char* WriteRipleysKCalculatorXMLFile4() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">"
      << "<plot>"
      << "<timesteps>3</timesteps>"
      << "<yearsPerTimestep>1</yearsPerTimestep>"
      << "<randomSeed>1</randomSeed>"
      << "<plot_lenX>196.0</plot_lenX>"
      << "<plot_lenY>196.0</plot_lenY>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88171785</plot_temp_C>"
      << "<plot_latitude>55.37</plot_latitude>"
      << "</plot>";

  WriteRipleysKCalculatorCommonStuff(oOut);

  oOut << "<RipleysK1>"
      << "<an_RipleysKMaxDistance>50</an_RipleysKMaxDistance>"
      << "<an_RipleysKDistanceInc>1</an_RipleysKDistanceInc>"
      << "</RipleysK1>"
      << "</paramFile>";

  oOut.close();
  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteRipleysKCalculatorXMLErrorFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteRipleysKCalculatorXMLErrorFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
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
      << "</plot>";

  WriteRipleysKCalculatorCommonStuff(oOut);

  oOut << "<RipleysK1>"
      << "<an_RipleysKMaxDistance>10</an_RipleysKMaxDistance>"
      << "<an_RipleysKDistanceInc>20</an_RipleysKDistanceInc>"
      << "</RipleysK1>"
      << "</paramFile>";

  oOut.close();
  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteRipleysKCalculatorXMLErrorFile2()
////////////////////////////////////////////////////////////////////////////
const char* WriteRipleysKCalculatorXMLErrorFile2() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
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
      << "</plot>";

  WriteRipleysKCalculatorCommonStuff(oOut);

  oOut << "<RipleysK1>"
      << "<an_RipleysKMaxDistance>-50</an_RipleysKMaxDistance>"
      << "<an_RipleysKDistanceInc>1</an_RipleysKDistanceInc>"
      << "</RipleysK1>"
      << "</paramFile>";

  oOut.close();
  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteRipleysKCalculatorXMLErrorFile3()
////////////////////////////////////////////////////////////////////////////
const char* WriteRipleysKCalculatorXMLErrorFile3() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
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
      << "</plot>";

  WriteRipleysKCalculatorCommonStuff(oOut);

  oOut << "<RipleysK1>"
      << "<an_RipleysKMaxDistance>50</an_RipleysKMaxDistance>"
      << "<an_RipleysKDistanceInc>-1</an_RipleysKDistanceInc>"
      << "</RipleysK1>"
      << "</paramFile>";

  oOut.close();
  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteRipleysKCalculatorCommonStuff()
////////////////////////////////////////////////////////////////////////////
void WriteRipleysKCalculatorCommonStuff(std::fstream &oOut) {

  oOut << "<trees>"
      << "<tr_speciesList>"
      << "<tr_species speciesName=\"Species_1\" />"
      << "<tr_species speciesName=\"Species_2\" />"
      << "<tr_species speciesName=\"Species_3\" />"
      << "<tr_species speciesName=\"Species_4\" />"
      << "</tr_speciesList>"
      << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
      << "<tr_minAdultDBH>"
      << "<tr_madVal species=\"Species_1\">0.0</tr_madVal>"
      << "<tr_madVal species=\"Species_2\">0.0</tr_madVal>"
      << "<tr_madVal species=\"Species_3\">0.0</tr_madVal>"
      << "<tr_madVal species=\"Species_4\">0.0</tr_madVal>"
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
      << "<tr_smcrVal species=\"Species_5\">10</tr_smcrVal>"
      << "</tr_stdMaxCrownRad>"
      << "<tr_conversionDiam10ToDBH>"
      << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_2\">0.8008</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_3\">0.8008</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_4\">0.8008</tr_cdtdVal>"
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
      << "<tr_soahVal species=\"Species_2\">0.0241</tr_soahVal>"
      << "<tr_soahVal species=\"Species_3\">0.0263</tr_soahVal>"
      << "<tr_soahVal species=\"Species_4\">0.0263</tr_soahVal>"
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
      << "</allometry>"
      << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>RipleysK</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "</behavior>"
      << "</behaviorList>";
}

////////////////////////////////////////////////////////////////////////////
// CreateTrees()
////////////////////////////////////////////////////////////////////////////
void CreateTrees(clTreePopulation *p_oPop, clPlot *p_oPlot, float fOffset) {

  float fX, fY, fDBH;
  int iSp;

  fX = p_oPlot->CorrectX(31.7094184 - fOffset);
  fY = p_oPlot->CorrectY(69.2171281 - fOffset);
  fDBH = 6.70; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::sapling, fDBH);

  fX = p_oPlot->CorrectX(63.0650021 - fOffset);
  fY = p_oPlot->CorrectY(58.5537260 - fOffset);
  fDBH = 15.58; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(34.6777252 - fOffset);
  fY = p_oPlot->CorrectY(42.6892403 - fOffset);
  fDBH = 19.13; iSp = 0;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(60.2542323 - fOffset);
  fY = p_oPlot->CorrectY(43.3365898 - fOffset);
  fDBH = 47.91; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(57.7935430 - fOffset);
  fY = p_oPlot->CorrectY(31.8673210 - fOffset);
  fDBH = 41.56; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(58.5834899 - fOffset);
  fY = p_oPlot->CorrectY(38.0598394 - fOffset);
  fDBH = 25.92; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(61.0027385 - fOffset);
  fY = p_oPlot->CorrectY(69.1505016 - fOffset);
  fDBH = 47.12; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(58.1158336 - fOffset);
  fY = p_oPlot->CorrectY(30.6776078 - fOffset);
  fDBH = 45.25; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(36.6402414 - fOffset);
  fY = p_oPlot->CorrectY(36.9972270 - fOffset);
  fDBH = 23.00; iSp = 0;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(68.1446909 - fOffset);
  fY = p_oPlot->CorrectY(61.9238429 - fOffset);
  fDBH = 20.35; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(62.3120718 - fOffset);
  fY = p_oPlot->CorrectY(52.4005773 - fOffset);
  fDBH = 17.07; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(44.6887800 - fOffset);
  fY = p_oPlot->CorrectY(41.9360127 - fOffset);
  fDBH = 22.02; iSp = 0;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(52.5822889 - fOffset);
  fY = p_oPlot->CorrectY(31.2152253 - fOffset);
  fDBH = 7.31; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::sapling, fDBH);

  fX = p_oPlot->CorrectX(56.4709828 - fOffset);
  fY = p_oPlot->CorrectY(37.1044565 - fOffset);
  fDBH = 10.76; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(61.7827570 - fOffset);
  fY = p_oPlot->CorrectY(66.6782430 - fOffset);
  fDBH = 2.53; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::sapling, fDBH);

  fX = p_oPlot->CorrectX(40.7574851 - fOffset);
  fY = p_oPlot->CorrectY(51.9639395 - fOffset);
  fDBH = 10.81; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(60.7592505 - fOffset);
  fY = p_oPlot->CorrectY(30.0070687 - fOffset);
  fDBH = 22.23; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(38.3173005 - fOffset);
  fY = p_oPlot->CorrectY(59.1225341 - fOffset);
  fDBH = 4.73; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::sapling, fDBH);

  fX = p_oPlot->CorrectX(54.3454495 - fOffset);
  fY = p_oPlot->CorrectY(39.1810222 - fOffset);
  fDBH = 35.74; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(52.6841327 - fOffset);
  fY = p_oPlot->CorrectY(42.9954431 - fOffset);
  fDBH = 43.69; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(44.7244036 - fOffset);
  fY = p_oPlot->CorrectY(31.3294605 - fOffset);
  fDBH = 4.96; iSp = 0;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::sapling, fDBH);

  fX = p_oPlot->CorrectX(42.2820773 - fOffset);
  fY = p_oPlot->CorrectY(56.6854570 - fOffset);
  fDBH = 1.07; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::sapling, fDBH);

  fX = p_oPlot->CorrectX(37.3181167 - fOffset);
  fY = p_oPlot->CorrectY(31.1232073 - fOffset);
  fDBH = 24.51; iSp = 0;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(59.6902360 - fOffset);
  fY = p_oPlot->CorrectY(31.0386153 - fOffset);
  fDBH = 42.43; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(65.7543677 - fOffset);
  fY = p_oPlot->CorrectY(68.9714840 - fOffset);
  fDBH = 17.64; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(64.0057333 - fOffset);
  fY = p_oPlot->CorrectY(37.9274886 - fOffset);
  fDBH = 39.64; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(42.8191345 - fOffset);
  fY = p_oPlot->CorrectY(54.1697617 - fOffset);
  fDBH = 10.30; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(63.6726781 - fOffset);
  fY = p_oPlot->CorrectY(37.3445726 - fOffset);
  fDBH = 6.88; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::sapling, fDBH);

  fX = p_oPlot->CorrectX(48.0225822 - fOffset);
  fY = p_oPlot->CorrectY(67.0129890 - fOffset);
  fDBH = 24.28; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(30.0999843 - fOffset);
  fY = p_oPlot->CorrectY(48.0911072 - fOffset);
  fDBH = 13.84; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(67.0225125 - fOffset);
  fY = p_oPlot->CorrectY(46.4747131 - fOffset);
  fDBH = 14.23; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(64.2440628 - fOffset);
  fY = p_oPlot->CorrectY(37.2466892 - fOffset);
  fDBH = 49.45; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(32.5510550 - fOffset);
  fY = p_oPlot->CorrectY(53.7041606 - fOffset);
  fDBH = 35.07; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(64.3337019 - fOffset);
  fY = p_oPlot->CorrectY(55.2130771 - fOffset);
  fDBH = 1.48; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::sapling, fDBH);

  fX = p_oPlot->CorrectX(69.9937888 - fOffset);
  fY = p_oPlot->CorrectY(59.4101570 - fOffset);
  fDBH = 11.55; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(61.5409042 - fOffset);
  fY = p_oPlot->CorrectY(66.1535237 - fOffset);
  fDBH = 3.25; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::sapling, fDBH);

  fX = p_oPlot->CorrectX(55.7173425 - fOffset);
  fY = p_oPlot->CorrectY(68.4870485 - fOffset);
  fDBH = 34.48; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(59.5319442 - fOffset);
  fY = p_oPlot->CorrectY(34.7770076 - fOffset);
  fDBH = 7.40; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::sapling, fDBH);

  fX = p_oPlot->CorrectX(38.7133121 - fOffset);
  fY = p_oPlot->CorrectY(36.8053197 - fOffset);
  fDBH = 44.46; iSp = 0;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(66.3748061 - fOffset);
  fY = p_oPlot->CorrectY(67.9110779 - fOffset);
  fDBH = 37.60; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(68.4595765 - fOffset);
  fY = p_oPlot->CorrectY(34.0531134 - fOffset);
  fDBH = 19.03; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(52.5231057 - fOffset);
  fY = p_oPlot->CorrectY(45.6320188 - fOffset);
  fDBH = 10.55; iSp = 1;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(35.5425861 - fOffset);
  fY = p_oPlot->CorrectY(66.8206196 - fOffset);
  fDBH = 42.47; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(31.4508971 - fOffset);
  fY = p_oPlot->CorrectY(64.1512154 - fOffset);
  fDBH = 19.47; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(33.0824643 - fOffset);
  fY = p_oPlot->CorrectY(35.3648909 - fOffset);
  fDBH = 41.03; iSp = 0;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(66.0341443 - fOffset);
  fY = p_oPlot->CorrectY(59.9338286 - fOffset);
  fDBH = 22.97; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(55.0419430 - fOffset);
  fY = p_oPlot->CorrectY(54.2776736 - fOffset);
  fDBH = 26.11; iSp = 1;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(69.4689362 - fOffset);
  fY = p_oPlot->CorrectY(47.0136816 - fOffset);
  fDBH = 5.76; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(66.2749605 - fOffset);
  fY = p_oPlot->CorrectY(30.3135251 - fOffset);
  fDBH = 30.60; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(66.9336249 - fOffset);
  fY = p_oPlot->CorrectY(67.8912659 - fOffset);
  fDBH = 39.27; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(32.0115274 - fOffset);
  fY = p_oPlot->CorrectY(69.6498619 - fOffset);
  fDBH = 28.48; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(35.5562352 - fOffset);
  fY = p_oPlot->CorrectY(32.7346060 - fOffset);
  fDBH = 15.04; iSp = 0;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(30.4359842 - fOffset);
  fY = p_oPlot->CorrectY(50.7268044 - fOffset);
  fDBH = 24.25; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(43.0721663 - fOffset);
  fY = p_oPlot->CorrectY(55.4585224 - fOffset);
  fDBH = 8.42; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(58.0836270 - fOffset);
  fY = p_oPlot->CorrectY(37.4290565 - fOffset);
  fDBH = 38.32; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(30.9104683 - fOffset);
  fY = p_oPlot->CorrectY(52.5851442 - fOffset);
  fDBH = 13.62; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(66.6604773 - fOffset);
  fY = p_oPlot->CorrectY(46.9947606 - fOffset);
  fDBH = 4.09; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(46.9727741 - fOffset);
  fY = p_oPlot->CorrectY(48.1382869 - fOffset);
  fDBH = 29.92; iSp = 1;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(63.2410097 - fOffset);
  fY = p_oPlot->CorrectY(41.5415066 - fOffset);
  fDBH = 32.91; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(66.2716582 - fOffset);
  fY = p_oPlot->CorrectY(67.5411284 - fOffset);
  fDBH = 46.33; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(50.2501481 - fOffset);
  fY = p_oPlot->CorrectY(58.4426534 - fOffset);
  fDBH = 11.15; iSp = 1;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(64.0742451 - fOffset);
  fY = p_oPlot->CorrectY(62.0013591 - fOffset);
  fDBH = 22.10; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(55.1002950 - fOffset);
  fY = p_oPlot->CorrectY(48.0370165 - fOffset);
  fDBH = 33.19; iSp = 1;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(41.7031183 - fOffset);
  fY = p_oPlot->CorrectY(53.8484351 - fOffset);
  fDBH = 36.70; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(39.4844218 - fOffset);
  fY = p_oPlot->CorrectY(30.8515324 - fOffset);
  fDBH = 36.48; iSp = 0;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(66.0148319 - fOffset);
  fY = p_oPlot->CorrectY(32.0354012 - fOffset);
  fDBH = 44.62; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(57.9983750 - fOffset);
  fY = p_oPlot->CorrectY(50.8579588 - fOffset);
  fDBH = 11.08; iSp = 1;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(41.3090853 - fOffset);
  fY = p_oPlot->CorrectY(55.3172117 - fOffset);
  fDBH = 21.98; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(68.0889239 - fOffset);
  fY = p_oPlot->CorrectY(67.8509960 - fOffset);
  fDBH = 49.27; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(59.2650277 - fOffset);
  fY = p_oPlot->CorrectY(30.2195109 - fOffset);
  fDBH = 13.32; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(48.0081818 - fOffset);
  fY = p_oPlot->CorrectY(33.5267253 - fOffset);
  fDBH = 3.70; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(67.3063727 - fOffset);
  fY = p_oPlot->CorrectY(50.6869068 - fOffset);
  fDBH = 1.68; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(62.7331277 - fOffset);
  fY = p_oPlot->CorrectY(36.1758086 - fOffset);
  fDBH = 31.45; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(68.6612698 - fOffset);
  fY = p_oPlot->CorrectY(66.1263193 - fOffset);
  fDBH = 39.46; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(36.3649443 - fOffset);
  fY = p_oPlot->CorrectY(57.7572972 - fOffset);
  fDBH = 21.49; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(40.5483717 - fOffset);
  fY = p_oPlot->CorrectY(57.2168482 - fOffset);
  fDBH = 37.01; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(54.2735002 - fOffset);
  fY = p_oPlot->CorrectY(60.7494505 - fOffset);
  fDBH = 37.65; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(39.9040256 - fOffset);
  fY = p_oPlot->CorrectY(57.0768941 - fOffset);
  fDBH = 31.72; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(56.3782721 - fOffset);
  fY = p_oPlot->CorrectY(59.2669709 - fOffset);
  fDBH = 11.80; iSp = 1;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(50.6824674 - fOffset);
  fY = p_oPlot->CorrectY(58.6841613 - fOffset);
  fDBH = 28.86; iSp = 1;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(40.1631905 - fOffset);
  fY = p_oPlot->CorrectY(53.7083696 - fOffset);
  fDBH = 29.45; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(39.9462708 - fOffset);
  fY = p_oPlot->CorrectY(57.2334618 - fOffset);
  fDBH = 19.69; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(64.3522870 - fOffset);
  fY = p_oPlot->CorrectY(37.1541965 - fOffset);
  fDBH = 16.45; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(58.4491902 - fOffset);
  fY = p_oPlot->CorrectY(47.5277952 - fOffset);
  fDBH = 32.77; iSp = 1;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(66.0808891 - fOffset);
  fY = p_oPlot->CorrectY(48.4055297 - fOffset);
  fDBH = 10.57; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(69.1167040 - fOffset);
  fY = p_oPlot->CorrectY(38.2317015 - fOffset);
  fDBH = 8.51; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::sapling, fDBH);

  fX = p_oPlot->CorrectX(65.0434486 - fOffset);
  fY = p_oPlot->CorrectY(39.9599933 - fOffset);
  fDBH = 41.08; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(69.8230852 - fOffset);
  fY = p_oPlot->CorrectY(34.3845812 - fOffset);
  fDBH = 20.35; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(42.7282420 - fOffset);
  fY = p_oPlot->CorrectY(30.2865289 - fOffset);
  fDBH = 41.26; iSp = 0;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(57.6942266 - fOffset);
  fY = p_oPlot->CorrectY(64.8899863 - fOffset);
  fDBH = 19.07; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(31.2855571 - fOffset);
  fY = p_oPlot->CorrectY(49.1837897 - fOffset);
  fDBH = 3.94; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::sapling, fDBH);

  fX = p_oPlot->CorrectX(50.5203479 - fOffset);
  fY = p_oPlot->CorrectY(38.9092183 - fOffset);
  fDBH = 34.21; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(56.0964522 - fOffset);
  fY = p_oPlot->CorrectY(55.6961520 - fOffset);
  fDBH = 24.56; iSp = 1;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(44.1205560 - fOffset);
  fY = p_oPlot->CorrectY(63.2525782 - fOffset);
  fDBH = 49.64; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(52.1101118 - fOffset);
  fY = p_oPlot->CorrectY(66.2257349 - fOffset);
  fDBH = 4.49; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(34.8577627 - fOffset);
  fY = p_oPlot->CorrectY(55.8509844 - fOffset);
  fDBH = 7.58; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(51.5419791 - fOffset);
  fY = p_oPlot->CorrectY(42.5956021 - fOffset);
  fDBH = 27.52; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(46.1417305 - fOffset);
  fY = p_oPlot->CorrectY(30.7815262 - fOffset);
  fDBH = 47.63; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(30.1654434 - fOffset);
  fY = p_oPlot->CorrectY(65.1138069 - fOffset);
  fDBH = 11.93; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

  fX = p_oPlot->CorrectX(54.8983830 - fOffset);
  fY = p_oPlot->CorrectY(66.2619967 - fOffset);
  fDBH = 1.96; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);


  //Create some seedlings and snags to be skipped
  fX = p_oPlot->CorrectX(57.6942266 - fOffset);
  fY = p_oPlot->CorrectY(64.8899863 - fOffset);
  fDBH = 19.07; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::snag, fDBH);

  fX = p_oPlot->CorrectX(31.2855571 - fOffset);
  fY = p_oPlot->CorrectY(49.1837897 - fOffset);
  fDBH = 0.94; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::seedling, fDBH);

  fX = p_oPlot->CorrectX(50.5203479 - fOffset);
  fY = p_oPlot->CorrectY(38.9092183 - fOffset);
  fDBH = 34.21; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::snag, fDBH);

  fX = p_oPlot->CorrectX(56.0964522 - fOffset);
  fY = p_oPlot->CorrectY(55.6961520 - fOffset);
  fDBH = 24.56; iSp = 1;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::snag, fDBH);

  fX = p_oPlot->CorrectX(44.1205560 - fOffset);
  fY = p_oPlot->CorrectY(63.2525782 - fOffset);
  fDBH = 49.64; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::snag, fDBH);

  fX = p_oPlot->CorrectX(52.1101118 - fOffset);
  fY = p_oPlot->CorrectY(66.2257349 - fOffset);
  fDBH = 4.49; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::snag, fDBH);

  fX = p_oPlot->CorrectX(34.8577627 - fOffset);
  fY = p_oPlot->CorrectY(55.8509844 - fOffset);
  fDBH = 7.58; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::snag, fDBH);

  fX = p_oPlot->CorrectX(51.5419791 - fOffset);
  fY = p_oPlot->CorrectY(42.5956021 - fOffset);
  fDBH = 27.52; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::snag, fDBH);

  fX = p_oPlot->CorrectX(46.1417305 - fOffset);
  fY = p_oPlot->CorrectY(30.7815262 - fOffset);
  fDBH = 47.63; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::snag, fDBH);

  fX = p_oPlot->CorrectX(30.1654434 - fOffset);
  fY = p_oPlot->CorrectY(65.1138069 - fOffset);
  fDBH = 11.93; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::snag, fDBH);

  fX = p_oPlot->CorrectX(54.8983830 - fOffset);
  fY = p_oPlot->CorrectY(66.2619967 - fOffset);
  fDBH = 1.96; iSp = 2;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::snag, fDBH);

  fX = p_oPlot->CorrectX(51.5419791 - fOffset);
  fY = p_oPlot->CorrectY(42.5956021 - fOffset);
  fDBH = 0.94; iSp = 3;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::seedling, fDBH);

  fX = p_oPlot->CorrectX(46.1417305 - fOffset);
  fY = p_oPlot->CorrectY(30.7815262 - fOffset);
  fDBH = 0.94; iSp = 3;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::seedling, fDBH);

  fX = p_oPlot->CorrectX(30.1654434 - fOffset);
  fY = p_oPlot->CorrectY(65.1138069 - fOffset);
  fDBH = 0.94; iSp = 3;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::seedling, fDBH);

  fX = p_oPlot->CorrectX(54.8983830 - fOffset);
  fY = p_oPlot->CorrectY(66.2619967 - fOffset);
  fDBH = 0.94; iSp = 3;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::seedling, fDBH);

  //Cell with only seedlings
  fX = p_oPlot->CorrectX(86.1417305 - fOffset);
  fY = p_oPlot->CorrectY(80.7815262 - fOffset);
  fDBH = 0.94; iSp = 3;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::seedling, fDBH);

  fX = p_oPlot->CorrectX(80.1654434 - fOffset);
  fY = p_oPlot->CorrectY(85.1138069 - fOffset);
  fDBH = 0.94; iSp = 3;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::seedling, fDBH);

  fX = p_oPlot->CorrectX(84.8983830 - fOffset);
  fY = p_oPlot->CorrectY(86.2619967 - fOffset);
  fDBH = 0.94; iSp = 3;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::seedling, fDBH);
}

////////////////////////////////////////////////////////////////////////////
// CheckRipleysKRun1Results ()
////////////////////////////////////////////////////////////////////////////
void CheckRipleysKRun1Results (clGrid *p_oGrid) {

  std::stringstream sLabel;
  float fActualValue, fExpectedValue;
  int iCode, i;

  //Check the values for the grid - all species
  iCode = p_oGrid->GetFloatDataCode("0_4");
  fExpectedValue = 72;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("1_4");
  fExpectedValue = 224;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("2_4");
  fExpectedValue = 408;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("3_4");
  fExpectedValue = 620;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("4_4");
  fExpectedValue = 860;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("5_4");
  fExpectedValue = 1188;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("6_4");
  fExpectedValue = 1552;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("7_4");
  fExpectedValue = 2016;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("8_4");
  fExpectedValue = 2400;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("9_4");
  fExpectedValue = 2836;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("10_4");
  fExpectedValue = 3280;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("11_4");
  fExpectedValue = 3768;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("12_4");
  fExpectedValue = 4280;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("13_4");
  fExpectedValue = 4900;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("14_4");
  fExpectedValue = 5496;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("15_4");
  fExpectedValue = 6016;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("16_4");
  fExpectedValue = 6540;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("17_4");
  fExpectedValue = 7072;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("18_4");
  fExpectedValue = 7660;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("19_4");
  fExpectedValue = 8228;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("20_4");
  fExpectedValue = 8748;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("21_4");
  fExpectedValue = 9372;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("22_4");
  fExpectedValue = 9976;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("23_4");
  fExpectedValue = 10588;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("24_4");
  fExpectedValue = 11156;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("25_4");
  fExpectedValue = 11796;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("26_4");
  fExpectedValue = 12428;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("27_4");
  fExpectedValue = 13076;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("28_4");
  fExpectedValue = 13704;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("29_4");
  fExpectedValue = 14416;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("30_4");
  fExpectedValue = 15024;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("31_4");
  fExpectedValue = 15584;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("32_4");
  fExpectedValue = 16040;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("33_4");
  fExpectedValue = 16532;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("34_4");
  fExpectedValue = 17000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("35_4");
  fExpectedValue = 17488;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("36_4");
  fExpectedValue = 17896;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("37_4");
  fExpectedValue = 18216;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("38_4");
  fExpectedValue = 18496;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("39_4");
  fExpectedValue = 18752;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("40_4");
  fExpectedValue = 18988;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("41_4");
  fExpectedValue = 19204;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("42_4");
  fExpectedValue = 19324;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("43_4");
  fExpectedValue = 19436;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("44_4");
  fExpectedValue = 19512;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("45_4");
  fExpectedValue = 19588;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("46_4");
  fExpectedValue = 19656;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("47_4");
  fExpectedValue = 19728;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("48_4");
  fExpectedValue = 19756;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("49_4");
  fExpectedValue = 19760;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  //Species 1
  iCode = p_oGrid->GetFloatDataCode("0_0");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("1_0");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("2_0");
  fExpectedValue = 1600;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("3_0");
  fExpectedValue = 2800;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("4_0");
  fExpectedValue = 3600;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("5_0");
  fExpectedValue = 6400;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("6_0");
  fExpectedValue = 7600;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("7_0");
  fExpectedValue = 10400;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("8_0");
  fExpectedValue = 10800;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("9_0");
  fExpectedValue = 12800;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("10_0");
  fExpectedValue = 14000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("11_0");
  fExpectedValue = 14800;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("12_0");
  fExpectedValue = 16400;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("13_0");
  fExpectedValue = 17200;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("14_0");
  fExpectedValue = 17600;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("15_0");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("16_0");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("17_0");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("18_0");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("19_0");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("20_0");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("21_0");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("22_0");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("23_0");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("24_0");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("25_0");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("26_0");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("27_0");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("28_0");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("29_0");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("30_0");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("31_0");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("32_0");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("33_0");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("34_0");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("35_0");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("36_0");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("37_0");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("38_0");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("39_0");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("40_0");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("41_0");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("42_0");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("43_0");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("44_0");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("45_0");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("46_0");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("47_0");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("48_0");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("49_0");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);


  //Species 2
  iCode = p_oGrid->GetFloatDataCode("0_1");
  fExpectedValue = 400;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("1_1");
  fExpectedValue = 800;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("2_1");
  fExpectedValue = 800;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("3_1");
  fExpectedValue = 2400;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("4_1");
  fExpectedValue = 3200;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("5_1");
  fExpectedValue = 4400;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("6_1");
  fExpectedValue = 7600;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("7_1");
  fExpectedValue = 8800;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("8_1");
  fExpectedValue = 10000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("9_1");
  fExpectedValue = 10400;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("10_1");
  fExpectedValue = 12400;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("11_1");
  fExpectedValue = 15600;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("12_1");
  fExpectedValue = 15600;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("13_1");
  fExpectedValue = 17200;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("14_1");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("15_1");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("16_1");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("17_1");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("18_1");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("19_1");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("20_1");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("21_1");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("22_1");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("23_1");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("24_1");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("25_1");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("26_1");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("27_1");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("28_1");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("29_1");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("30_1");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("31_1");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("32_1");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("33_1");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("34_1");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("35_1");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("36_1");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("37_1");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("38_1");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("39_1");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("40_1");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("41_1");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("42_1");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("43_1");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("44_1");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("45_1");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("46_1");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("47_1");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("48_1");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("49_1");
  fExpectedValue = 18000;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  //Species 3
  iCode = p_oGrid->GetFloatDataCode("0_2");
  fExpectedValue = 106.25;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("1_2");
  fExpectedValue = 331.25;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("2_2");
  fExpectedValue = 581.25;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("3_2");
  fExpectedValue = 850;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("4_2");
  fExpectedValue = 1175;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("5_2");
  fExpectedValue = 1606.25;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("6_2");
  fExpectedValue = 2037.5;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("7_2");
  fExpectedValue = 2562.5;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("8_2");
  fExpectedValue = 2975;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("9_2");
  fExpectedValue = 3400;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("10_2");
  fExpectedValue = 3875;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("11_2");
  fExpectedValue = 4343.75;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("12_2");
  fExpectedValue = 4850;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("13_2");
  fExpectedValue = 5412.5;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("14_2");
  fExpectedValue = 5881.25;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("15_2");
  fExpectedValue = 6231.25;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("16_2");
  fExpectedValue = 6606.25;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("17_2");
  fExpectedValue = 7012.5;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("18_2");
  fExpectedValue = 7437.5;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("19_2");
  fExpectedValue = 7812.5;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("20_2");
  fExpectedValue = 8175;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("21_2");
  fExpectedValue = 8668.75;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("22_2");
  fExpectedValue = 9150;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("23_2");
  fExpectedValue = 9700;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("24_2");
  fExpectedValue = 10237.5;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("25_2");
  fExpectedValue = 10775;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("26_2");
  fExpectedValue = 11381.25;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("27_2");
  fExpectedValue = 11993.75;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("28_2");
  fExpectedValue = 12681.25;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("29_2");
  fExpectedValue = 13493.75;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("30_2");
  fExpectedValue = 14206.25;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("31_2");
  fExpectedValue = 14875;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("32_2");
  fExpectedValue = 15412.5;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("33_2");
  fExpectedValue = 15987.5;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("34_2");
  fExpectedValue = 16550;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("35_2");
  fExpectedValue = 17181.25;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("36_2");
  fExpectedValue = 17706.25;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("37_2");
  fExpectedValue = 18056.25;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("38_2");
  fExpectedValue = 18387.5;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("39_2");
  fExpectedValue = 18718.75;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("40_2");
  fExpectedValue = 18956.25;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("41_2");
  fExpectedValue = 19206.25;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("42_2");
  fExpectedValue = 19300;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("43_2");
  fExpectedValue = 19393.75;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("44_2");
  fExpectedValue = 19462.5;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("45_2");
  fExpectedValue = 19550;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("46_2");
  fExpectedValue = 19581.25;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("47_2");
  fExpectedValue = 19637.5;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("48_2");
  fExpectedValue = 19681.25;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("49_2");
  fExpectedValue = 19687.5;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  //Species 4
  for (i = 0; i < 50; i++) {
    sLabel << i << "_3";
    iCode = p_oGrid->GetFloatDataCode(sLabel.str());
    ASSERT_TRUE(-1 != iCode);
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fActualValue), 0.0001);
    sLabel.str("");
  }
}
