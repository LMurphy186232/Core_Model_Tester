//---------------------------------------------------------------------------
// TestFoliarChemistry.cpp
//---------------------------------------------------------------------------
#include "TestFoliarChemistry.h"
#include <gtest/gtest.h>
#include <fstream>
#include <math.h>
#include "TreePopulation.h"
#include "SimManager.h"
#include "Grid.h"

////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun1()
////////////////////////////////////////////////////////////////////////////
TEST(FoliarChemistry, TestNormalProcessingRun1) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTreeSearch *p_oAllTrees;
    clTree *p_oTree;
    clGrid *p_oGrid;
    float fValue, fExpectedValue;
    int iNumXCells, iNumYCells, iX, iY;

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile(WriteFoliarChemistryXMLFile1());
    p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject(
        "treepopulation");

    CreateFoliarChemistryTrees(p_oPop);

    //Now do the run
    p_oSimManager->RunSim(1);
    p_oGrid = p_oSimManager->GetGridObject("Rodent Lambda");
    ASSERT_TRUE(NULL != p_oGrid);

    //************
    //Grid 0,0
    //************
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("N_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0.48011;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("N_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("N_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 188.658904;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("N_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("N_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("P_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0.960219;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("P_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("P_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 190.313807;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("P_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("P_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("SLA_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 1.440329;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("SLA_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("SLA_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 191.968709;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("SLA_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("SLA_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("lignin_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 1.920438;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("lignin_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("lignin_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 193.623612;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("lignin_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("lignin_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("fiber_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 2.400548;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("fiber_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("fiber_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 195.278515;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("fiber_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("fiber_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("cellulose_0"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 2.880657;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("cellulose_1"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("cellulose_2"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 196.933417;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("cellulose_3"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("cellulose_4"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("tannins_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 3.360767;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("tannins_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("tannins_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 198.58832;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("tannins_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("tannins_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("phenolics_0"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 3.840876;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("phenolics_1"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("phenolics_2"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 200.243223;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("phenolics_3"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("phenolics_4"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    //************
    //Grid 0,1
    //************
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("N_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("N_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("N_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("N_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("N_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("P_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("P_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("P_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("P_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("P_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("SLA_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("SLA_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("SLA_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("SLA_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("SLA_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("lignin_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("lignin_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("lignin_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("lignin_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("lignin_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("fiber_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("fiber_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("fiber_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("fiber_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("fiber_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("cellulose_0"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("cellulose_1"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("cellulose_2"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("cellulose_3"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("cellulose_4"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("tannins_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("tannins_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("tannins_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("tannins_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("tannins_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("phenolics_0"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("phenolics_1"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("phenolics_2"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("phenolics_3"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("phenolics_4"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    //************
    //Grid 0,2
    //************
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("N_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0.231957;
    p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("N_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("N_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("N_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("N_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("P_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0.463914;
    p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("P_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("P_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("P_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("P_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("SLA_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0.695872;
    p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("SLA_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("SLA_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("SLA_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("SLA_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("lignin_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0.927829;
    p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("lignin_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("lignin_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("lignin_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("lignin_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("fiber_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 1.159786;
    p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("fiber_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("fiber_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("fiber_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("fiber_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("cellulose_0"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 1.391743;
    p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("cellulose_1"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("cellulose_2"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("cellulose_3"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("cellulose_4"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("tannins_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 1.6237;
    p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("tannins_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("tannins_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("tannins_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("tannins_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("phenolics_0"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 1.855658;
    p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("phenolics_1"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("phenolics_2"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("phenolics_3"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("phenolics_4"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    //************
    //Grid 1,0
    //************
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("N_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("N_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("N_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 17.223558;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("N_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("N_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("P_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("P_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("P_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 17.374642;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("P_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("P_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("SLA_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("SLA_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("SLA_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 17.525726;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("SLA_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("SLA_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("lignin_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("lignin_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("lignin_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 17.67681;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("lignin_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("lignin_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("fiber_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("fiber_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("fiber_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 17.827893;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("fiber_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("fiber_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("cellulose_0"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("cellulose_1"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("cellulose_2"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 17.978977;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("cellulose_3"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("cellulose_4"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("tannins_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("tannins_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("tannins_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 18.130061;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("tannins_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("tannins_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("phenolics_0"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("phenolics_1"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("phenolics_2"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 18.281145;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("phenolics_3"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("phenolics_4"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    //************
    //Grid 1,1
    //************
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("N_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0.152809;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("N_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("N_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("N_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("N_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("P_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0.305617;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("P_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("P_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("P_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("P_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("SLA_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0.458426;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("SLA_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("SLA_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("SLA_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("SLA_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("lignin_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0.611235;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("lignin_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("lignin_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("lignin_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("lignin_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("fiber_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0.764043;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("fiber_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("fiber_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("fiber_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("fiber_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("cellulose_0"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0.916852;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("cellulose_1"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("cellulose_2"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("cellulose_3"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("cellulose_4"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("tannins_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 1.069661;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("tannins_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("tannins_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("tannins_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("tannins_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("phenolics_0"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 1.222469;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("phenolics_1"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("phenolics_2"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("phenolics_3"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("phenolics_4"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    //************
    //Grid 1, 2
    //************
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("N_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("N_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("N_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 82.499376;
    p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("N_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("N_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("P_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("P_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("P_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 83.223055;
    p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("P_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("P_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("SLA_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("SLA_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("SLA_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 83.946734;
    p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("SLA_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("SLA_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("lignin_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("lignin_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("lignin_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 84.670412;
    p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("lignin_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("lignin_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("fiber_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("fiber_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("fiber_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 85.394091;
    p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("fiber_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("fiber_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("cellulose_0"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("cellulose_1"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("cellulose_2"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 86.11777;
    p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("cellulose_3"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("cellulose_4"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("tannins_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("tannins_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("tannins_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 86.841449;
    p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("tannins_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("tannins_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("phenolics_0"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("phenolics_1"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("phenolics_2"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 87.565127;
    p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("phenolics_3"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("phenolics_4"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    //************
    //Grid 2,0
    //************
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("N_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("N_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("N_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("N_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("N_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("P_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("P_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("P_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("P_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("P_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("SLA_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("SLA_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("SLA_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("SLA_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("SLA_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("lignin_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("lignin_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("lignin_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("lignin_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("lignin_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("fiber_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("fiber_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("fiber_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("fiber_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("fiber_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("cellulose_0"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("cellulose_1"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("cellulose_2"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("cellulose_3"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("cellulose_4"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("tannins_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("tannins_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("tannins_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("tannins_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("tannins_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("phenolics_0"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("phenolics_1"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("phenolics_2"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("phenolics_3"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("phenolics_4"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);


    //************
    //Grid 2,1
    //************
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("P_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("P_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("P_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("P_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("P_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("SLA_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("SLA_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("SLA_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("SLA_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("SLA_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("lignin_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("lignin_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("lignin_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("lignin_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("lignin_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("fiber_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("fiber_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("fiber_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("fiber_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("fiber_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("cellulose_0"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("cellulose_1"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("cellulose_2"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("cellulose_3"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("cellulose_4"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("tannins_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("tannins_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("tannins_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("tannins_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("tannins_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("phenolics_0"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("phenolics_1"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("phenolics_2"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("phenolics_3"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("phenolics_4"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    //************
    //Grid 2,2
    //************
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("N_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("N_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("N_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("N_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("N_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("P_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("P_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("P_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("P_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("P_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("SLA_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("SLA_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("SLA_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("SLA_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("SLA_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("lignin_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("lignin_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("lignin_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("lignin_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("lignin_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("fiber_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("fiber_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("fiber_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("fiber_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("fiber_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("cellulose_0"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("cellulose_1"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("cellulose_2"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("cellulose_3"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("cellulose_4"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("tannins_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("tannins_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("tannins_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("tannins_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("tannins_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("phenolics_0"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("phenolics_1"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("phenolics_2"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("phenolics_3"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("phenolics_4"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    //************
    //Grid 3,0
    //************
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("N_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0.12;
    p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("N_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("N_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("N_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("N_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("P_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0.24;
    p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("P_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("P_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("P_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("P_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("SLA_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0.36;
    p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("SLA_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("SLA_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("SLA_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("SLA_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("lignin_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0.48;
    p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("lignin_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("lignin_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("lignin_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("lignin_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("fiber_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0.6;
    p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("fiber_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("fiber_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("fiber_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("fiber_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("cellulose_0"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0.72;
    p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("cellulose_1"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("cellulose_2"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("cellulose_3"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("cellulose_4"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("tannins_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0.84;
    p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("tannins_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("tannins_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("tannins_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("tannins_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("phenolics_0"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0.96;
    p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("phenolics_1"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("phenolics_2"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("phenolics_3"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("phenolics_4"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);


    //Kill all the trees
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_oPop->KillTree(p_oTree, remove_tree);
      p_oTree = p_oAllTrees->NextTree();
    }

    //Run another timestep
    p_oSimManager->RunSim(1);

    //Make sure the grid totals are zero
    iNumXCells = p_oGrid->GetNumberXCells();
    iNumYCells = p_oGrid->GetNumberYCells();
    for (iX = 0; iX < iNumXCells; iX++) {
      for (iY = 0; iY < iNumYCells; iY++) {
        p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("N_0"), &fValue);
        EXPECT_LT(fabs(fValue), 0.00001);
        p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("N_1"), &fValue);
        EXPECT_LT(fabs(fValue), 0.00001);
        p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("N_2"), &fValue);
        EXPECT_LT(fabs(fValue), 0.00001);
        p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("N_3"), &fValue);
        EXPECT_LT(fabs(fValue), 0.00001);
        p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("N_4"), &fValue);
        EXPECT_LT(fabs(fValue), 0.00001);

        p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("P_0"), &fValue);
        EXPECT_LT(fabs(fValue), 0.00001);
        p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("P_1"), &fValue);
        EXPECT_LT(fabs(fValue), 0.00001);
        p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("P_2"), &fValue);
        EXPECT_LT(fabs(fValue), 0.00001);
        p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("P_3"), &fValue);
        EXPECT_LT(fabs(fValue), 0.00001);
        p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("P_4"), &fValue);
        EXPECT_LT(fabs(fValue), 0.00001);

        p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("SLA_0"),
            &fValue);
        EXPECT_LT(fabs(fValue), 0.00001);
        p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("SLA_1"),
            &fValue);
        EXPECT_LT(fabs(fValue), 0.00001);
        p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("SLA_2"),
            &fValue);
        EXPECT_LT(fabs(fValue), 0.00001);
        p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("SLA_3"),
            &fValue);
        EXPECT_LT(fabs(fValue), 0.00001);
        p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("SLA_4"),
            &fValue);
        EXPECT_LT(fabs(fValue), 0.00001);

        p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("lignin_0"),
            &fValue);
        EXPECT_LT(fabs(fValue), 0.00001);
        p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("lignin_1"),
            &fValue);
        EXPECT_LT(fabs(fValue), 0.00001);
        p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("lignin_2"),
            &fValue);
        EXPECT_LT(fabs(fValue), 0.00001);
        p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("lignin_3"),
            &fValue);
        EXPECT_LT(fabs(fValue), 0.00001);
        p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("lignin_4"),
            &fValue);
        EXPECT_LT(fabs(fValue), 0.00001);

        p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("fiber_0"),
            &fValue);
        EXPECT_LT(fabs(fValue), 0.00001);
        p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("fiber_1"),
            &fValue);
        EXPECT_LT(fabs(fValue), 0.00001);
        p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("fiber_2"),
            &fValue);
        EXPECT_LT(fabs(fValue), 0.00001);
        p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("fiber_3"),
            &fValue);
        EXPECT_LT(fabs(fValue), 0.00001);
        p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("fiber_4"),
            &fValue);
        EXPECT_LT(fabs(fValue), 0.00001);

        p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("cellulose_0"),
            &fValue);
        EXPECT_LT(fabs(fValue), 0.00001);
        p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("cellulose_1"),
            &fValue);
        EXPECT_LT(fabs(fValue), 0.00001);
        p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("cellulose_2"),
            &fValue);
        EXPECT_LT(fabs(fValue), 0.00001);
        p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("cellulose_3"),
            &fValue);
        EXPECT_LT(fabs(fValue), 0.00001);
        p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("cellulose_4"),
            &fValue);
        EXPECT_LT(fabs(fValue), 0.00001);

        p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("tannins_0"),
            &fValue);
        EXPECT_LT(fabs(fValue), 0.00001);
        p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("tannins_1"),
            &fValue);
        EXPECT_LT(fabs(fValue), 0.00001);
        p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("tannins_2"),
            &fValue);
        EXPECT_LT(fabs(fValue), 0.00001);
        p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("tannins_3"),
            &fValue);
        EXPECT_LT(fabs(fValue), 0.00001);
        p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("tannins_4"),
            &fValue);
        EXPECT_LT(fabs(fValue), 0.00001);

        p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("phenolics_0"),
            &fValue);
        EXPECT_LT(fabs(fValue), 0.00001);
        p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("phenolics_1"),
            &fValue);
        EXPECT_LT(fabs(fValue), 0.00001);
        p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("phenolics_2"),
            &fValue);
        EXPECT_LT(fabs(fValue), 0.00001);
        p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("phenolics_3"),
            &fValue);
        EXPECT_LT(fabs(fValue), 0.00001);
        p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("phenolics_4"),
            &fValue);
        EXPECT_LT(fabs(fValue), 0.00001);
      }
    }
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun2()
////////////////////////////////////////////////////////////////////////////
TEST(FoliarChemistry, TestNormalProcessingRun2) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clGrid *p_oGrid;
    float fValue, fExpectedValue;

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile(WriteFoliarChemistryXMLFile2());
    p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject(
        "treepopulation");

    CreateFoliarChemistryTrees(p_oPop);

    //Now do the run
    p_oSimManager->RunSim(1);
    p_oGrid = p_oSimManager->GetGridObject("Foliar Chemistry");
    ASSERT_TRUE(NULL != p_oGrid);

    //************
    //Grid 0,0
    //************
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("N_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0.632918;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("N_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("N_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 205.882462;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("N_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("N_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("P_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 1.265836;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("P_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("P_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 207.688449;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("P_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("P_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("SLA_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 1.898754;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("SLA_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("SLA_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 209.494435;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("SLA_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("SLA_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("lignin_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 2.531673;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("lignin_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("lignin_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 211.300422;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("lignin_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("lignin_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("fiber_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 3.164591;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("fiber_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("fiber_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 213.106408;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("fiber_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("fiber_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("cellulose_0"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 3.797509;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("cellulose_1"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("cellulose_2"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 214.912395;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("cellulose_3"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("cellulose_4"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("tannins_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 4.430427;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("tannins_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("tannins_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 216.718381;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("tannins_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("tannins_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("phenolics_0"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 5.063345;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("phenolics_1"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("phenolics_2"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 218.524368;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("phenolics_3"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("phenolics_4"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    //************
    //Grid 0,1
    //************
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("N_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0.231957;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("N_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("N_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 82.499376;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("N_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("N_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("P_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0.463914;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("P_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("P_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 83.223055;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("P_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("P_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("SLA_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0.695872;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("SLA_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("SLA_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 83.946734;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("SLA_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("SLA_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("lignin_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0.927829;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("lignin_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("lignin_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 84.670412;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("lignin_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("lignin_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("fiber_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 1.159786;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("fiber_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("fiber_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 85.394091;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("fiber_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("fiber_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("cellulose_0"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 1.391743;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("cellulose_1"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("cellulose_2"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 86.11777;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("cellulose_3"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("cellulose_4"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("tannins_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 1.6237;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("tannins_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("tannins_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 86.841449;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("tannins_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("tannins_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("phenolics_0"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 1.855658;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("phenolics_1"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("phenolics_2"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 87.565127;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("phenolics_3"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("phenolics_4"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    //************
    //Grid 1,0
    //************
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("N_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0.12;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("N_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("N_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("N_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("N_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("P_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0.24;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("P_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("P_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("P_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("P_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("SLA_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0.36;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("SLA_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("SLA_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("SLA_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("SLA_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("lignin_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0.48;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("lignin_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("lignin_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("lignin_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("lignin_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("fiber_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0.6;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("fiber_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("fiber_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("fiber_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("fiber_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("cellulose_0"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0.72;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("cellulose_1"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("cellulose_2"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("cellulose_3"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("cellulose_4"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("tannins_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0.84;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("tannins_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("tannins_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("tannins_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("tannins_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("phenolics_0"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0.96;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("phenolics_1"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("phenolics_2"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("phenolics_3"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("phenolics_4"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    //************
    //Grid 1,1
    //************
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("N_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("N_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("N_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("N_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("N_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("P_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("P_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("P_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("P_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("P_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("SLA_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("SLA_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("SLA_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("SLA_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("SLA_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("lignin_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("lignin_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("lignin_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("lignin_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("lignin_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("fiber_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("fiber_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("fiber_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("fiber_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("fiber_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("cellulose_0"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("cellulose_1"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("cellulose_2"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("cellulose_3"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("cellulose_4"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("tannins_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("tannins_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("tannins_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("tannins_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("tannins_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("phenolics_0"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("phenolics_1"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("phenolics_2"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("phenolics_3"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("phenolics_4"),
        &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestErrorProcessing()
////////////////////////////////////////////////////////////////////////////
TEST(FoliarChemistry, TestErrorProcessing) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    p_oSimManager->ReadFile(WriteFoliarChemistryXMLErrorFile1());
    FAIL() << "TestFoliarChemistry error processing didn't catch error for WriteFoliarChemistryXMLErrorFile1.";
  } catch (modelErr& err) {
    if (err.sFunction.compare("clFoliarChemistry::GetAppliesTo") != 0) {
      FAIL() << "TestFoliarChemistry error processing caught wrong error for WriteFoliarChemistryXMLErrorFile1.";
    }
  }
  delete p_oSimManager;
}

////////////////////////////////////////////////////////////////////////////
// CreateFoliarChemistryTrees()
////////////////////////////////////////////////////////////////////////////
void CreateFoliarChemistryTrees(clTreePopulation *p_oPop) {

  float fX, fY, fDbh;
  int iSpecies, iType;
  iSpecies = 0;
  fX = 4;
  fY = 4;
  fDbh = 2;
  iType = clTreePopulation::sapling;
  p_oPop->CreateTree(fX, fY, iSpecies, iType, fDbh);

  iSpecies = 1;
  fX = 12;
  fY = 12;
  fDbh = 3;
  iType = clTreePopulation::sapling;
  p_oPop->CreateTree(fX, fY, iSpecies, iType, fDbh);

  iSpecies = 2;
  fX = 4;
  fY = 12;
  fDbh = 4;
  iType = clTreePopulation::sapling;
  p_oPop->CreateTree(fX, fY, iSpecies, iType, fDbh);

  iSpecies = 3;
  fX = 12;
  fY = 4;
  fDbh = 5;
  iType = clTreePopulation::sapling;
  p_oPop->CreateTree(fX, fY, iSpecies, iType, fDbh);

  iSpecies = 0;
  fX = 22;
  fY = 4;
  fDbh = 11;
  iType = clTreePopulation::adult;
  p_oPop->CreateTree(fX, fY, iSpecies, iType, fDbh);

  iSpecies = 1;
  fX = 4;
  fY = 22;
  fDbh = 20;
  iType = clTreePopulation::adult;
  p_oPop->CreateTree(fX, fY, iSpecies, iType, fDbh);

  iSpecies = 2;
  fX = 22;
  fY = 12;
  fDbh = 30;
  iType = clTreePopulation::adult;
  p_oPop->CreateTree(fX, fY, iSpecies, iType, fDbh);

  iSpecies = 3;
  fX = 12;
  fY = 22;
  fDbh = 40;
  iType = clTreePopulation::adult;
  p_oPop->CreateTree(fX, fY, iSpecies, iType, fDbh);

  iSpecies = 2;
  fX = 22;
  fY = 22;
  fDbh = 0.5;
  iType = clTreePopulation::sapling;
  p_oPop->CreateTree(fX, fY, iSpecies, iType, fDbh);

  iSpecies = 4;
  fX = 30;
  fY = 4;
  fDbh = 0.5;
  iType = clTreePopulation::sapling;
  p_oPop->CreateTree(fX, fY, iSpecies, iType, fDbh);

  iSpecies = 1;
  fX = 30;
  fY = 4;
  fDbh = 1;
  iType = clTreePopulation::sapling;
  p_oPop->CreateTree(fX, fY, iSpecies, iType, fDbh);

  iSpecies = 1;
  fX = 4;
  fY = 4;
  fDbh = 12;
  iType = clTreePopulation::adult;
  p_oPop->CreateTree(fX, fY, iSpecies, iType, fDbh);

  iSpecies = 2;
  fX = 4;
  fY = 4;
  fDbh = 30;
  iType = clTreePopulation::adult;
  p_oPop->CreateTree(fX, fY, iSpecies, iType, fDbh);

  iSpecies = 3;
  fX = 4;
  fY = 4;
  fDbh = 50;
  iType = clTreePopulation::adult;
  p_oPop->CreateTree(fX, fY, iSpecies, iType, fDbh);

  iSpecies = 4;
  fX = 4;
  fY = 4;
  fDbh = 30;
  iType = clTreePopulation::adult;
  p_oPop->CreateTree(fX, fY, iSpecies, iType, fDbh);

  iSpecies = 1;
  fX = 4;
  fY = 4;
  fDbh = 3;
  iType = clTreePopulation::sapling;
  p_oPop->CreateTree(fX, fY, iSpecies, iType, fDbh);

  iSpecies = 3;
  fX = 4;
  fY = 4;
  fDbh = 40;
  iType = clTreePopulation::adult;
  p_oPop->CreateTree(fX, fY, iSpecies, iType, fDbh);

  iSpecies = 0;
  fX = 4;
  fY = 4;
  fDbh = 11;
  iType = clTreePopulation::adult;
  p_oPop->CreateTree(fX, fY, iSpecies, iType, fDbh);

  iSpecies = 2;
  fX = 4;
  fY = 4;
  fDbh = 30;
  iType = clTreePopulation::adult;
  p_oPop->CreateTree(fX, fY, iSpecies, iType, fDbh);

  iSpecies = 2;
  fX = 4;
  fY = 4;
  fDbh = 0.5;
  iType = clTreePopulation::sapling;
  p_oPop->CreateTree(fX, fY, iSpecies, iType, fDbh);

  iSpecies = 4;
  fX = 4;
  fY = 4;
  fDbh = 0.5;
  iType = clTreePopulation::sapling;
  p_oPop->CreateTree(fX, fY, iSpecies, iType, fDbh);

  iSpecies = 1;
  fX = 4;
  fY = 4;
  fDbh = 1;
  iType = clTreePopulation::sapling;
  p_oPop->CreateTree(fX, fY, iSpecies, iType, fDbh);

  iSpecies = 3;
  fX = 12;
  fY = 4;
  fDbh = 10;
  iType = clTreePopulation::adult;
  p_oPop->CreateTree(fX, fY, iSpecies, iType, fDbh);
}

////////////////////////////////////////////////////////////////////////////
// WriteFoliarChemistryXMLFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteFoliarChemistryXMLFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteFoliarChemistryCommonFileBegin(oOut);
  WriteFoliarChemistryCommonFileEnd(oOut);

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteFoliarChemistryXMLFile2()
////////////////////////////////////////////////////////////////////////////
const char* WriteFoliarChemistryXMLFile2() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteFoliarChemistryCommonFileBegin(oOut);

  oOut << "<grid gridName=\"Foliar Chemistry\">"
       << "<ma_floatCodes>"
       << "<ma_floatCode label=\"N_0\">25</ma_floatCode>"
       << "<ma_floatCode label=\"N_1\">26</ma_floatCode>"
       << "<ma_floatCode label=\"N_2\">27</ma_floatCode>"
       << "<ma_floatCode label=\"N_3\">28</ma_floatCode>"
       << "<ma_floatCode label=\"N_4\">29</ma_floatCode>"
       << "<ma_floatCode label=\"P_0\">30</ma_floatCode>"
       << "<ma_floatCode label=\"P_1\">31</ma_floatCode>"
       << "<ma_floatCode label=\"P_2\">32</ma_floatCode>"
       << "<ma_floatCode label=\"P_3\">33</ma_floatCode>"
       << "<ma_floatCode label=\"P_4\">34</ma_floatCode>"
       << "<ma_floatCode label=\"SLA_0\">35</ma_floatCode>"
       << "<ma_floatCode label=\"SLA_1\">36</ma_floatCode>"
       << "<ma_floatCode label=\"SLA_2\">37</ma_floatCode>"
       << "<ma_floatCode label=\"SLA_3\">38</ma_floatCode>"
       << "<ma_floatCode label=\"SLA_4\">39</ma_floatCode>"
       << "<ma_floatCode label=\"lignin_0\">40</ma_floatCode>"
       << "<ma_floatCode label=\"lignin_1\">41</ma_floatCode>"
       << "<ma_floatCode label=\"lignin_2\">42</ma_floatCode>"
       << "<ma_floatCode label=\"lignin_3\">43</ma_floatCode>"
       << "<ma_floatCode label=\"lignin_4\">44</ma_floatCode>"
       << "<ma_floatCode label=\"tannins_0\">45</ma_floatCode>"
       << "<ma_floatCode label=\"tannins_1\">46</ma_floatCode>"
       << "<ma_floatCode label=\"tannins_2\">47</ma_floatCode>"
       << "<ma_floatCode label=\"tannins_3\">48</ma_floatCode>"
       << "<ma_floatCode label=\"tannins_4\">49</ma_floatCode>"
       << "<ma_floatCode label=\"phenolics_0\">50</ma_floatCode>"
       << "<ma_floatCode label=\"phenolics_1\">51</ma_floatCode>"
       << "<ma_floatCode label=\"phenolics_2\">52</ma_floatCode>"
       << "<ma_floatCode label=\"phenolics_3\">53</ma_floatCode>"
       << "<ma_floatCode label=\"phenolics_4\">54</ma_floatCode>"
       << "<ma_floatCode label=\"fiber_0\">55</ma_floatCode>"
       << "<ma_floatCode label=\"fiber_1\">56</ma_floatCode>"
       << "<ma_floatCode label=\"fiber_2\">57</ma_floatCode>"
       << "<ma_floatCode label=\"fiber_3\">58</ma_floatCode>"
       << "<ma_floatCode label=\"fiber_4\">59</ma_floatCode>"
       << "<ma_floatCode label=\"cellulose_0\">60</ma_floatCode>"
       << "<ma_floatCode label=\"cellulose_1\">61</ma_floatCode>"
       << "<ma_floatCode label=\"cellulose_2\">62</ma_floatCode>"
       << "<ma_floatCode label=\"cellulose_3\">63</ma_floatCode>"
       << "<ma_floatCode label=\"cellulose_4\">64</ma_floatCode>"
       << "</ma_floatCodes>"
       << "<ma_lengthXCells>20</ma_lengthXCells>"
       << "<ma_lengthYCells>20</ma_lengthYCells>"
       << "</grid>";

  WriteFoliarChemistryCommonFileEnd(oOut);

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteFoliarChemistryXMLErrorFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteFoliarChemistryXMLErrorFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteFoliarChemistryCommonFileBegin(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>FoliarChemistry</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<FoliarChemistry1>"
       << "<an_foliarChemWeightA>"
       << "<an_fcwaVal species=\"Species_2\">0.12</an_fcwaVal>"
       << "<an_fcwaVal species=\"Species_4\">1.12</an_fcwaVal>"
       << "</an_foliarChemWeightA>"
       << "<an_foliarChemWeightB>"
       << "<an_fcwbVal species=\"Species_2\">0.22</an_fcwbVal>"
       << "<an_fcwbVal species=\"Species_4\">1.13</an_fcwbVal>"
       << "</an_foliarChemWeightB>"
       << "<an_foliarChemN>"
       << "<an_fcnVal species=\"Species_2\">1</an_fcnVal>"
       << "<an_fcnVal species=\"Species_4\">1.14</an_fcnVal>"
       << "</an_foliarChemN>"
       << "<an_foliarChemP>"
       << "<an_fcpVal species=\"Species_2\">2</an_fcpVal>"
       << "<an_fcpVal species=\"Species_4\">1.15</an_fcpVal>"
       << "</an_foliarChemP>"
       << "<an_foliarChemSLA>"
       << "<an_fcsVal species=\"Species_2\">3</an_fcsVal>"
       << "<an_fcsVal species=\"Species_4\">1.16</an_fcsVal>"
       << "</an_foliarChemSLA>"
       << "<an_foliarChemLignin>"
       << "<an_fclVal species=\"Species_2\">4</an_fclVal>"
       << "<an_fclVal species=\"Species_4\">1.17</an_fclVal>"
       << "</an_foliarChemLignin>"
       << "<an_foliarChemTannins>"
       << "<an_fctVal species=\"Species_2\">7</an_fctVal>"
       << "<an_fctVal species=\"Species_4\">1.2</an_fctVal>"
       << "</an_foliarChemTannins>"
       << "<an_foliarChemPhenolics>"
       << "<an_fcphVal species=\"Species_2\">8</an_fcphVal>"
       << "<an_fcphVal species=\"Species_4\">1.21</an_fcphVal>"
       << "</an_foliarChemPhenolics>"
       << "<an_foliarChemFiber>"
       << "<an_fcfVal species=\"Species_2\">5</an_fcfVal>"
       << "<an_fcfVal species=\"Species_4\">1.18</an_fcfVal>"
       << "</an_foliarChemFiber>"
       << "<an_foliarChemCellulose>"
       << "<an_fccVal species=\"Species_2\">6</an_fccVal>"
       << "<an_fccVal species=\"Species_4\">1.19</an_fccVal>"
       << "</an_foliarChemCellulose>"
       << "</FoliarChemistry1>"
       << "</paramFile>";

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteFoliarChemistryCommonFileBegin()
/////////////////////////////////////////////////////////////////////////////
void WriteFoliarChemistryCommonFileBegin(std::fstream &oOut) {
  using namespace std;
  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>2</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>100.0</plot_lenX>"
       << "<plot_lenY>100.0</plot_lenY>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12</plot_temp_C>"
       << "</plot>"
       << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\" />"
       << "<tr_species speciesName=\"Species_2\" />"
       << "<tr_species speciesName=\"Species_3\" />"
       << "<tr_species speciesName=\"Species_4\" />"
       << "<tr_species speciesName=\"Species_5\" />"
       << "</tr_speciesList>"
       << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
       << "<tr_minAdultDBH>"
       << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_2\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_3\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_4\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_5\">10.0</tr_madVal>"
       << "</tr_minAdultDBH>"
       << "<tr_maxSeedlingHeight>"
       << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_2\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_3\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_4\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_5\">1.35</tr_mshVal>"
       << "</tr_maxSeedlingHeight>"
       << "</trees>"
       << "<allometry>"
       << "<tr_whatSeedlingHeightDiam>"
       << "<tr_wsehdVal species=\"Species_1\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_2\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_3\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_4\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_5\">0</tr_wsehdVal>"
       << "</tr_whatSeedlingHeightDiam>"
       << "<tr_whatSaplingHeightDiam>"
       << "<tr_wsahdVal species=\"Species_1\">1</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_2\">1</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_3\">1</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_4\">1</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_5\">1</tr_wsahdVal>"
       << "</tr_whatSaplingHeightDiam>"
       << "<tr_whatAdultHeightDiam>"
       << "<tr_wahdVal species=\"Species_1\">1</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_2\">1</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_3\">1</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_4\">1</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_5\">1</tr_wahdVal>"
       << "</tr_whatAdultHeightDiam>"
       << "<tr_whatAdultCrownRadDiam>"
       << "<tr_wacrdVal species=\"Species_1\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_2\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_3\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_4\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_5\">0</tr_wacrdVal>"
       << "</tr_whatAdultCrownRadDiam>"
       << "<tr_whatAdultCrownHeightHeight>"
       << "<tr_wachhVal species=\"Species_1\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_2\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_3\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_4\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_5\">0</tr_wachhVal>"
       << "</tr_whatAdultCrownHeightHeight>"
       << "<tr_whatSaplingCrownRadDiam>"
       << "<tr_wscrdVal species=\"Species_1\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_2\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_3\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_4\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_5\">0</tr_wscrdVal>"
       << "</tr_whatSaplingCrownRadDiam>"
       << "<tr_whatSaplingCrownHeightHeight>"
       << "<tr_wschhVal species=\"Species_1\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_2\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_3\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_4\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_5\">0</tr_wschhVal>"
       << "</tr_whatSaplingCrownHeightHeight>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_2\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_3\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_4\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_5\">39.48</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_2\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_3\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_4\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_5\">0.0549</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_3\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_4\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_5\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_stdMaxCrownRad>"
       << "<tr_smcrVal species=\"Species_1\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_2\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_3\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_4\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_5\">10</tr_smcrVal>"
       << "</tr_stdMaxCrownRad>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.49</tr_sachVal>"
       << "<tr_sachVal species=\"Species_2\">0.49</tr_sachVal>"
       << "<tr_sachVal species=\"Species_3\">0.49</tr_sachVal>"
       << "<tr_sachVal species=\"Species_4\">0.49</tr_sachVal>"
       << "<tr_sachVal species=\"Species_5\">0.49</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_3\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_4\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_5\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_3\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_4\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_5\">0.8008</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_3\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_4\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_5\">0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_2\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_3\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_4\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_5\">0.03418</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "<tr_adultLinearSlope>"
       << "<tr_alsVal species=\"Species_1\">0.34</tr_alsVal>"
       << "<tr_alsVal species=\"Species_2\">0.76</tr_alsVal>"
       << "<tr_alsVal species=\"Species_3\">0.78</tr_alsVal>"
       << "<tr_alsVal species=\"Species_4\">0.66</tr_alsVal>"
       << "<tr_alsVal species=\"Species_5\">0.66</tr_alsVal>"
       << "</tr_adultLinearSlope>"
       << "<tr_adultLinearIntercept>"
       << "<tr_aliVal species=\"Species_1\">0.34</tr_aliVal>"
       << "<tr_aliVal species=\"Species_2\">-0.258</tr_aliVal>"
       << "<tr_aliVal species=\"Species_3\">-0.33</tr_aliVal>"
       << "<tr_aliVal species=\"Species_4\">0.84</tr_aliVal>"
       << "<tr_aliVal species=\"Species_5\">0.84</tr_aliVal>"
       << "</tr_adultLinearIntercept>"
       << "<tr_saplingLinearSlope>"
       << "<tr_salsVal species=\"Species_1\">0.34</tr_salsVal>"
       << "<tr_salsVal species=\"Species_2\">0.76</tr_salsVal>"
       << "<tr_salsVal species=\"Species_3\">0.78</tr_salsVal>"
       << "<tr_salsVal species=\"Species_4\">0.66</tr_salsVal>"
       << "<tr_salsVal species=\"Species_5\">0.66</tr_salsVal>"
       << "</tr_saplingLinearSlope>"
       << "<tr_saplingLinearIntercept>"
       << "<tr_saliVal species=\"Species_1\">0.34</tr_saliVal>"
       << "<tr_saliVal species=\"Species_2\">-0.258</tr_saliVal>"
       << "<tr_saliVal species=\"Species_3\">-0.33</tr_saliVal>"
       << "<tr_saliVal species=\"Species_4\">0.84</tr_saliVal>"
       << "<tr_saliVal species=\"Species_5\">0.84</tr_saliVal>"
       << "</tr_saplingLinearIntercept>"
       << "</allometry>";
}

/////////////////////////////////////////////////////////////////////////////
// WriteFoliarChemistryCommonFileEnd()
/////////////////////////////////////////////////////////////////////////////
void WriteFoliarChemistryCommonFileEnd(std::fstream &oOut) {
  using namespace std;

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>FoliarChemistry</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<FoliarChemistry1>"
       << "<an_foliarChemWeightA>"
       << "<an_fcwaVal species=\"Species_2\">0.12</an_fcwaVal>"
       << "<an_fcwaVal species=\"Species_4\">1.12</an_fcwaVal>"
       << "</an_foliarChemWeightA>"
       << "<an_foliarChemWeightB>"
       << "<an_fcwbVal species=\"Species_2\">0.22</an_fcwbVal>"
       << "<an_fcwbVal species=\"Species_4\">1.13</an_fcwbVal>"
       << "</an_foliarChemWeightB>"
       << "<an_foliarChemN>"
       << "<an_fcnVal species=\"Species_2\">1</an_fcnVal>"
       << "<an_fcnVal species=\"Species_4\">1.14</an_fcnVal>"
       << "</an_foliarChemN>"
       << "<an_foliarChemP>"
       << "<an_fcpVal species=\"Species_2\">2</an_fcpVal>"
       << "<an_fcpVal species=\"Species_4\">1.15</an_fcpVal>"
       << "</an_foliarChemP>"
       << "<an_foliarChemSLA>"
       << "<an_fcsVal species=\"Species_2\">3</an_fcsVal>"
       << "<an_fcsVal species=\"Species_4\">1.16</an_fcsVal>"
       << "</an_foliarChemSLA>"
       << "<an_foliarChemLignin>"
       << "<an_fclVal species=\"Species_2\">4</an_fclVal>"
       << "<an_fclVal species=\"Species_4\">1.17</an_fclVal>"
       << "</an_foliarChemLignin>"
       << "<an_foliarChemTannins>"
       << "<an_fctVal species=\"Species_2\">7</an_fctVal>"
       << "<an_fctVal species=\"Species_4\">1.2</an_fctVal>"
       << "</an_foliarChemTannins>"
       << "<an_foliarChemPhenolics>"
       << "<an_fcphVal species=\"Species_2\">8</an_fcphVal>"
       << "<an_fcphVal species=\"Species_4\">1.21</an_fcphVal>"
       << "</an_foliarChemPhenolics>"
       << "<an_foliarChemFiber>"
       << "<an_fcfVal species=\"Species_2\">5</an_fcfVal>"
       << "<an_fcfVal species=\"Species_4\">1.18</an_fcfVal>"
       << "</an_foliarChemFiber>"
       << "<an_foliarChemCellulose>"
       << "<an_fccVal species=\"Species_2\">6</an_fccVal>"
       << "<an_fccVal species=\"Species_4\">1.19</an_fccVal>"
       << "</an_foliarChemCellulose>"
       << "</FoliarChemistry1>"
       << "</paramFile>";
}
