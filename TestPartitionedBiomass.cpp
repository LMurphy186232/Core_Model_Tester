//---------------------------------------------------------------------------
// TestPartitionedBiomass.cpp
//---------------------------------------------------------------------------
#include "TestPartitionedBiomass.h"
#include <gtest/gtest.h>
#include <fstream>
#include <math.h>
#include "TreePopulation.h"
#include "SimManager.h"
#include "Grid.h"

////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun1()
////////////////////////////////////////////////////////////////////////////
TEST(PartitionedBiomass, TestNormalProcessingRun1) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
  clTreePopulation * p_oPop;
  clTreeSearch *p_oAllTrees;
  clTree *p_oTree;
  clGrid *p_oGrid;
  float fValue, fExpectedValue;
  int iNumXCells, iNumYCells, iX, iY;

  //Load our test file and get our tree population pointers
  p_oSimManager->ReadFile( WritePartitionedBiomassXMLFile1() );
  p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

  CreatePartitionedBiomassTrees(p_oPop);

  //Now do the run
  p_oSimManager->RunSim(1);
  p_oGrid = p_oSimManager->GetGridObject("Partitioned Biomass");
  ASSERT_TRUE(NULL != p_oGrid);

  //************
  //Grid 0,0
  //************
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("leaf_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.015865;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("leaf_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("leaf_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.168796;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("leaf_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("leaf_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("bole_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.031867;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("bole_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("bole_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.235974;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("bole_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("bole_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("branch_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.019004;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("branch_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("branch_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.18576;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("branch_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("branch_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("hleaf_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("hleaf_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.09894;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("hleaf_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("hleaf_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.032788;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("hleaf_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("hbole_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("hbole_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.269026;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("hbole_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("hbole_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.125479;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("hbole_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  //************
  //Grid 0,1
  //************
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("leaf_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("leaf_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("leaf_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("leaf_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("leaf_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("bole_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("bole_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("bole_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("bole_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("bole_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("branch_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("branch_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("branch_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("branch_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("branch_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("hleaf_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("hleaf_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.011543;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("hleaf_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("hleaf_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("hleaf_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("hbole_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("hbole_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.014861;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("hbole_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("hbole_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("hbole_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  //************
  //Grid 0,2
  //************
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("leaf_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.02697;
  p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("leaf_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("leaf_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("leaf_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("leaf_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("bole_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.047721;
  p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("bole_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("bole_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("bole_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("bole_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("branch_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.035277;
  p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("branch_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("branch_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("branch_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("branch_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("hleaf_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("hleaf_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("hleaf_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("hleaf_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("hleaf_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("hbole_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("hbole_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("hbole_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("hbole_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("hbole_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  //************
  //Grid 1,0
  //************
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("leaf_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("leaf_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("leaf_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.021678;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("leaf_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("leaf_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("bole_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("bole_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("bole_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.028422;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("bole_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("bole_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("branch_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("branch_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("branch_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.02351;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("branch_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("branch_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("hleaf_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("hleaf_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("hleaf_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("hleaf_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("hleaf_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("hbole_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("hbole_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("hbole_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("hbole_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("hbole_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  //************
  //Grid 1,1
  //************
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("leaf_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.001079;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("leaf_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("leaf_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("leaf_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("leaf_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("bole_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.00449;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("bole_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("bole_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("bole_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("bole_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("branch_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.000223;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("branch_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("branch_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("branch_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("branch_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("hleaf_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("hleaf_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("hleaf_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("hleaf_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("hleaf_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("hbole_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("hbole_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("hbole_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("hbole_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("hbole_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  //************
  //Grid 1, 2
  //************
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("leaf_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("leaf_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("leaf_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.075438;
  p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("leaf_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("leaf_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("bole_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("bole_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("bole_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.105192;
  p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("bole_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("bole_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("branch_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("branch_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("branch_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.08297;
  p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("branch_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("branch_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("hleaf_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("hleaf_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("hleaf_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("hleaf_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("hleaf_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("hbole_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("hbole_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("hbole_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("hbole_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("hbole_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  //************
  //Grid 2,0
  //************
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("leaf_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("leaf_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("leaf_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("leaf_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("leaf_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("bole_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("bole_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("bole_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("bole_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("bole_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("branch_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("branch_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("branch_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("branch_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("branch_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("hleaf_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("hleaf_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("hleaf_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("hleaf_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("hleaf_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("hbole_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("hbole_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("hbole_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("hbole_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("hbole_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  //************
  //Grid 2,1
  //************
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("leaf_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("leaf_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("leaf_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("leaf_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("leaf_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("bole_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("bole_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("bole_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("bole_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("bole_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("branch_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("branch_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("branch_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("branch_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("branch_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("hleaf_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("hleaf_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.046019;
  p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("hleaf_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("hleaf_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("hleaf_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("hbole_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("hbole_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.134513;
  p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("hbole_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("hbole_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("hbole_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  //************
  //Grid 2,2
  //************
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("leaf_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("leaf_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("leaf_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("leaf_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("leaf_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("bole_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("bole_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("bole_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("bole_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("bole_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("branch_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("branch_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("branch_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("branch_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("branch_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("hleaf_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("hleaf_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.006902;
  p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("hleaf_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("hleaf_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("hleaf_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("hbole_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("hbole_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("hbole_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("hbole_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("hbole_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  //************
  //Grid 3,0
  //************
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("leaf_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("leaf_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("leaf_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("leaf_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("leaf_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("bole_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("bole_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("bole_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("bole_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("bole_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("branch_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("branch_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("branch_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("branch_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("branch_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("hleaf_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("hleaf_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("hleaf_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("hleaf_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("hleaf_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("hbole_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("hbole_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("hbole_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("hbole_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.005303;
  p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("hbole_4"), &fValue);
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
      fExpectedValue = 0;
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("leaf_0"), &fValue);
      EXPECT_LT(fabs(fValue), 0.00001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("leaf_1"), &fValue);
      EXPECT_LT(fabs(fValue), 0.00001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("leaf_2"), &fValue);
      EXPECT_LT(fabs(fValue), 0.00001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("leaf_3"), &fValue);
      EXPECT_LT(fabs(fValue), 0.00001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("leaf_4"), &fValue);
      EXPECT_LT(fabs(fValue), 0.00001);

      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("bole_0"), &fValue);
      EXPECT_LT(fabs(fValue), 0.00001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("bole_1"), &fValue);
      EXPECT_LT(fabs(fValue), 0.00001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("bole_2"), &fValue);
      EXPECT_LT(fabs(fValue), 0.00001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("bole_3"), &fValue);
      EXPECT_LT(fabs(fValue), 0.00001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("bole_4"), &fValue);
      EXPECT_LT(fabs(fValue), 0.00001);

      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("branch_0"), &fValue);
      EXPECT_LT(fabs(fValue), 0.00001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("branch_1"), &fValue);
      EXPECT_LT(fabs(fValue), 0.00001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("branch_2"), &fValue);
      EXPECT_LT(fabs(fValue), 0.00001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("branch_3"), &fValue);
      EXPECT_LT(fabs(fValue), 0.00001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("branch_4"), &fValue);
      EXPECT_LT(fabs(fValue), 0.00001);

      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("hleaf_0"), &fValue);
      EXPECT_LT(fabs(fValue), 0.00001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("hleaf_1"), &fValue);
      EXPECT_LT(fabs(fValue), 0.00001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("hleaf_2"), &fValue);
      EXPECT_LT(fabs(fValue), 0.00001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("hleaf_3"), &fValue);
      EXPECT_LT(fabs(fValue), 0.00001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("hleaf_4"), &fValue);
      EXPECT_LT(fabs(fValue), 0.00001);

      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("hbole_0"), &fValue);
      EXPECT_LT(fabs(fValue), 0.00001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("hbole_1"), &fValue);
      EXPECT_LT(fabs(fValue), 0.00001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("hbole_2"), &fValue);
      EXPECT_LT(fabs(fValue), 0.00001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("hbole_3"), &fValue);
      EXPECT_LT(fabs(fValue), 0.00001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("hbole_4"), &fValue);
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
TEST(PartitionedBiomass, TestNormalProcessingRun2) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
  clTreePopulation * p_oPop;
  clGrid *p_oGrid;
  float fValue, fExpectedValue;

  //Load our test file and get our tree population pointers
  p_oSimManager->ReadFile( WritePartitionedBiomassXMLFile2() );
  p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

  CreatePartitionedBiomassTrees(p_oPop);

  //Now do the run
  p_oSimManager->RunSim(1);
  p_oGrid = p_oSimManager->GetGridObject("Partitioned Biomass");
  ASSERT_TRUE(NULL != p_oGrid);

  //************
  //Grid 0,0
  //************
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("leaf_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.01694;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("leaf_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("leaf_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.190474;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("leaf_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("leaf_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("bole_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.036357;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("bole_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("bole_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.264396;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("bole_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("bole_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("branch_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.019227;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("branch_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("branch_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.20927;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("branch_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("branch_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("hleaf_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("hleaf_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.110483;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("hleaf_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("hleaf_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.032788;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("hleaf_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("hbole_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("hbole_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.283887;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("hbole_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("hbole_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.125479;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("hbole_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  //************
  //Grid 0,1
  //************
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("leaf_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.02697;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("leaf_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("leaf_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.075438;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("leaf_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("leaf_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("bole_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.047721;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("bole_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("bole_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.105192;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("bole_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("bole_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("branch_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.035277;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("branch_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("branch_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.08297;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("branch_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("branch_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("hleaf_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("hleaf_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("hleaf_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("hleaf_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("hleaf_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("hbole_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("hbole_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("hbole_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("hbole_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("hbole_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  //************
  //Grid 1,0
  //************
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("leaf_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("leaf_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("leaf_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("leaf_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("leaf_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("bole_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("bole_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("bole_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("bole_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("bole_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("branch_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("branch_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("branch_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("branch_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("branch_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("hleaf_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("hleaf_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.046019;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("hleaf_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("hleaf_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("hleaf_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("hbole_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("hbole_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.134513;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("hbole_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("hbole_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.005303;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("hbole_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  //************
  //Grid 1,1
  //************
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("leaf_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("leaf_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("leaf_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("leaf_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("leaf_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("bole_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("bole_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("bole_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("bole_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("bole_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("branch_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("branch_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("branch_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("branch_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("branch_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("hleaf_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("hleaf_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.006902;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("hleaf_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("hleaf_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("hleaf_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("hbole_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("hbole_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("hbole_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("hbole_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("hbole_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun3()
////////////////////////////////////////////////////////////////////////////
TEST(PartitionedBiomass, TestNormalProcessingRun3) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
  clTreePopulation * p_oPop;
  clGrid *p_oGrid;
  float fValue, fExpectedValue;
  int iNumXCells, iNumYCells, iX, iY;

  //Load our test file and get our tree population pointers
  p_oSimManager->ReadFile( WritePartitionedBiomassXMLFile3() );
  p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

  CreatePartitionedBiomassTrees(p_oPop);

  //Now do the run
  p_oSimManager->RunSim(1);
  p_oGrid = p_oSimManager->GetGridObject("Partitioned Biomass");
  ASSERT_TRUE(NULL != p_oGrid);

  //Make sure the height grid totals are zero
  iNumXCells = p_oGrid->GetNumberXCells();
  iNumYCells = p_oGrid->GetNumberYCells();
  for (iX = 0; iX < iNumXCells; iX++) {
    for (iY = 0; iY < iNumYCells; iY++) {
      fExpectedValue = 0;
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("hleaf_0"), &fValue);
      EXPECT_LT(fabs(fValue), 0.00001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("hleaf_1"), &fValue);
      EXPECT_LT(fabs(fValue), 0.00001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("hleaf_2"), &fValue);
      EXPECT_LT(fabs(fValue), 0.00001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("hleaf_3"), &fValue);
      EXPECT_LT(fabs(fValue), 0.00001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("hleaf_4"), &fValue);
      EXPECT_LT(fabs(fValue), 0.00001);

      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("hbole_0"), &fValue);
      EXPECT_LT(fabs(fValue), 0.00001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("hbole_1"), &fValue);
      EXPECT_LT(fabs(fValue), 0.00001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("hbole_2"), &fValue);
      EXPECT_LT(fabs(fValue), 0.00001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("hbole_3"), &fValue);
      EXPECT_LT(fabs(fValue), 0.00001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("hbole_4"), &fValue);
      EXPECT_LT(fabs(fValue), 0.00001);
    }
  }

  //************
  //Grid 0,0
  //************
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("leaf_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.015865;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("leaf_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("leaf_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.168796;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("leaf_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("leaf_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("bole_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.031867;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("bole_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("bole_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.235974;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("bole_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("bole_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("branch_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.019004;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("branch_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("branch_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.18576;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("branch_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("branch_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  //************
  //Grid 0,1
  //************
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("leaf_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("leaf_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("leaf_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("leaf_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("leaf_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("bole_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("bole_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("bole_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("bole_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("bole_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("branch_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("branch_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("branch_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("branch_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("branch_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  //************
  //Grid 0,2
  //************
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("leaf_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.02697;
  p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("leaf_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("leaf_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("leaf_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("leaf_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("bole_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.047721;
  p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("bole_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("bole_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("bole_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("bole_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("branch_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.035277;
  p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("branch_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("branch_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("branch_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("branch_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  //************
  //Grid 1,0
  //************
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("leaf_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("leaf_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("leaf_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.021678;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("leaf_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("leaf_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("bole_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("bole_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("bole_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.028422;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("bole_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("bole_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("branch_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("branch_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("branch_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.02351;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("branch_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("branch_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  //************
  //Grid 1,1
  //************
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("leaf_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.001079;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("leaf_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("leaf_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("leaf_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("leaf_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("bole_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.00449;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("bole_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("bole_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("bole_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("bole_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("branch_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.000223;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("branch_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("branch_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("branch_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("branch_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  //************
  //Grid 1, 2
  //************
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("leaf_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("leaf_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("leaf_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.075438;
  p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("leaf_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("leaf_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("bole_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("bole_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("bole_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.105192;
  p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("bole_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("bole_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("branch_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("branch_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("branch_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.08297;
  p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("branch_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("branch_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  //************
  //Grid 2,0
  //************
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("leaf_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("leaf_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("leaf_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("leaf_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("leaf_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("bole_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("bole_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("bole_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("bole_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("bole_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("branch_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("branch_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("branch_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("branch_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("branch_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  //************
  //Grid 2,1
  //************
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("leaf_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("leaf_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("leaf_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("leaf_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("leaf_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("bole_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("bole_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("bole_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("bole_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("bole_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("branch_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("branch_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("branch_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("branch_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("branch_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  //************
  //Grid 2,2
  //************
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("leaf_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("leaf_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("leaf_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("leaf_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("leaf_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("bole_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("bole_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("bole_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("bole_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("bole_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("branch_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("branch_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("branch_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("branch_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("branch_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  //************
  //Grid 3,0
  //************
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("leaf_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("leaf_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("leaf_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("leaf_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("leaf_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("bole_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("bole_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("bole_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("bole_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("bole_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("branch_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("branch_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("branch_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("branch_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("branch_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun4()
////////////////////////////////////////////////////////////////////////////
TEST(PartitionedBiomass, TestNormalProcessingRun4) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
  clTreePopulation * p_oPop;
  clGrid *p_oGrid;
  float fValue, fExpectedValue;
  int iNumXCells, iNumYCells, iX, iY;

  //Load our test file and get our tree population pointers
  p_oSimManager->ReadFile( WritePartitionedBiomassXMLFile4() );
  p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

  CreatePartitionedBiomassTrees(p_oPop);

  //Now do the run
  p_oSimManager->RunSim(1);
  p_oGrid = p_oSimManager->GetGridObject("Partitioned Biomass");
  ASSERT_TRUE(NULL != p_oGrid);

  //Make sure the dbh grid totals are zero
  iNumXCells = p_oGrid->GetNumberXCells();
  iNumYCells = p_oGrid->GetNumberYCells();
  for (iX = 0; iX < iNumXCells; iX++) {
    for (iY = 0; iY < iNumYCells; iY++) {
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("leaf_0"), &fValue);
      EXPECT_LT(fabs(fValue), 0.00001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("leaf_1"), &fValue);
      EXPECT_LT(fabs(fValue), 0.00001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("leaf_2"), &fValue);
      EXPECT_LT(fabs(fValue), 0.00001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("leaf_3"), &fValue);
      EXPECT_LT(fabs(fValue), 0.00001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("leaf_4"), &fValue);
      EXPECT_LT(fabs(fValue), 0.00001);

      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("bole_0"), &fValue);
      EXPECT_LT(fabs(fValue), 0.00001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("bole_1"), &fValue);
      EXPECT_LT(fabs(fValue), 0.00001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("bole_2"), &fValue);
      EXPECT_LT(fabs(fValue), 0.00001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("bole_3"), &fValue);
      EXPECT_LT(fabs(fValue), 0.00001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("bole_4"), &fValue);
      EXPECT_LT(fabs(fValue), 0.00001);

      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("branch_0"), &fValue);
      EXPECT_LT(fabs(fValue), 0.00001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("branch_1"), &fValue);
      EXPECT_LT(fabs(fValue), 0.00001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("branch_2"), &fValue);
      EXPECT_LT(fabs(fValue), 0.00001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("branch_3"), &fValue);
      EXPECT_LT(fabs(fValue), 0.00001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("branch_4"), &fValue);
      EXPECT_LT(fabs(fValue), 0.00001);
    }
  }

  //************
  //Grid 0,0
  //************
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("hleaf_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("hleaf_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.09894;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("hleaf_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("hleaf_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.032788;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("hleaf_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("hbole_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("hbole_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.269026;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("hbole_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("hbole_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.125479;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("hbole_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  //************
  //Grid 0,1
  //************
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("hleaf_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("hleaf_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.011543;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("hleaf_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("hleaf_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("hleaf_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("hbole_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("hbole_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.014861;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("hbole_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("hbole_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("hbole_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  //************
  //Grid 0,2
  //************
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("hleaf_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("hleaf_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("hleaf_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("hleaf_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("hleaf_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("hbole_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("hbole_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("hbole_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("hbole_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("hbole_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  //************
  //Grid 1,0
  //************
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("hleaf_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("hleaf_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("hleaf_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("hleaf_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("hleaf_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("hbole_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("hbole_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("hbole_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("hbole_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("hbole_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  //************
  //Grid 1,1
  //************
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("hleaf_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("hleaf_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("hleaf_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("hleaf_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("hleaf_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("hbole_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("hbole_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("hbole_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("hbole_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("hbole_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  //************
  //Grid 1, 2
  //************
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("hleaf_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("hleaf_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("hleaf_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("hleaf_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("hleaf_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("hbole_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("hbole_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("hbole_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("hbole_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("hbole_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  //************
  //Grid 2,0
  //************
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("hleaf_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("hleaf_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("hleaf_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("hleaf_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("hleaf_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("hbole_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("hbole_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("hbole_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("hbole_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("hbole_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  //************
  //Grid 2,1
  //************
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("hleaf_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("hleaf_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.046019;
  p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("hleaf_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("hleaf_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("hleaf_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("hbole_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("hbole_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.134513;
  p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("hbole_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("hbole_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("hbole_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  //************
  //Grid 2,2
  //************
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("hleaf_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("hleaf_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.006902;
  p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("hleaf_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("hleaf_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("hleaf_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("hbole_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("hbole_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("hbole_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("hbole_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("hbole_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  //************
  //Grid 3,0
  //************
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("hleaf_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("hleaf_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("hleaf_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("hleaf_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("hleaf_4"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("hbole_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("hbole_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("hbole_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("hbole_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0.005303;
  p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("hbole_4"), &fValue);
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
TEST(PartitionedBiomass, TestErrorProcessing) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try
  {
    p_oSimManager->ReadFile(WritePartitionedBiomassXMLErrorFile1());
    FAIL() << "TestPartitionedBiomass error processing didn't catch error for WritePartitionedBiomassXMLErrorFile1.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clPartitionedBiomass::GetAppliesTo") != 0)
    {
      FAIL() << "TestPartitionedBiomass error processing caught wrong error for WritePartitionedBiomassXMLErrorFile1.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WritePartitionedBiomassXMLErrorFile2());
    FAIL() << "TestPartitionedBiomass error processing didn't catch error for WritePartitionedBiomassXMLErrorFile2.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clPartitionedBiomass::GetAppliesTo") != 0)
    {
      FAIL() << "TestPartitionedBiomass error processing caught wrong error for WritePartitionedBiomassXMLErrorFile2.";
    }
    ;
  }
  delete p_oSimManager;
}

////////////////////////////////////////////////////////////////////////////
// CreatePartitionedBiomassTrees()
////////////////////////////////////////////////////////////////////////////
void CreatePartitionedBiomassTrees(clTreePopulation *p_oPop) {

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
// WritePartitionedBiomassXMLFile1()
////////////////////////////////////////////////////////////////////////////
const char* WritePartitionedBiomassXMLFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WritePartitionedBiomassCommonFileBegin(oOut);
  WritePartitionedBiomassCommonFileEnd(oOut);

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WritePartitionedBiomassXMLFile2()
////////////////////////////////////////////////////////////////////////////
const char* WritePartitionedBiomassXMLFile2() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WritePartitionedBiomassCommonFileBegin(oOut);

  oOut << "<grid gridName=\"Partitioned Biomass\">"
       << "<ma_floatCodes>"
       << "<ma_floatCode label=\"leaf_0\">0</ma_floatCode>"
       << "<ma_floatCode label=\"leaf_1\">1</ma_floatCode>"
       << "<ma_floatCode label=\"leaf_2\">2</ma_floatCode>"
       << "<ma_floatCode label=\"leaf_3\">3</ma_floatCode>"
       << "<ma_floatCode label=\"leaf_4\">4</ma_floatCode>"
       << "<ma_floatCode label=\"branch_0\">5</ma_floatCode>"
       << "<ma_floatCode label=\"branch_1\">6</ma_floatCode>"
       << "<ma_floatCode label=\"branch_2\">7</ma_floatCode>"
       << "<ma_floatCode label=\"branch_3\">8</ma_floatCode>"
       << "<ma_floatCode label=\"branch_4\">9</ma_floatCode>"
       << "<ma_floatCode label=\"bole_0\">10</ma_floatCode>"
       << "<ma_floatCode label=\"bole_1\">11</ma_floatCode>"
       << "<ma_floatCode label=\"bole_2\">12</ma_floatCode>"
       << "<ma_floatCode label=\"bole_3\">13</ma_floatCode>"
       << "<ma_floatCode label=\"bole_4\">14</ma_floatCode>"
       << "<ma_floatCode label=\"hleaf_0\">15</ma_floatCode>"
       << "<ma_floatCode label=\"hleaf_1\">16</ma_floatCode>"
       << "<ma_floatCode label=\"hleaf_2\">17</ma_floatCode>"
       << "<ma_floatCode label=\"hleaf_3\">18</ma_floatCode>"
       << "<ma_floatCode label=\"hleaf_4\">19</ma_floatCode>"
       << "<ma_floatCode label=\"hbole_0\">20</ma_floatCode>"
       << "<ma_floatCode label=\"hbole_1\">21</ma_floatCode>"
       << "<ma_floatCode label=\"hbole_2\">22</ma_floatCode>"
       << "<ma_floatCode label=\"hbole_3\">23</ma_floatCode>"
       << "<ma_floatCode label=\"hbole_4\">24</ma_floatCode>"
       << "</ma_floatCodes>"
       << "<ma_lengthXCells>20</ma_lengthXCells>"
       << "<ma_lengthYCells>20</ma_lengthYCells>"
       << "</grid>";

  WritePartitionedBiomassCommonFileEnd(oOut);

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WritePartitionedBiomassXMLFile3()
////////////////////////////////////////////////////////////////////////////
const char* WritePartitionedBiomassXMLFile3() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WritePartitionedBiomassCommonFileBegin(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>PartitionedDBHBiomass</behaviorName>"
       << "<version>2</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<PartitionedBiomass1>"
       << "<an_partBioDbhLeafA>"
       << "<an_pbdlaVal species=\"Species_2\">1.523</an_pbdlaVal>"
       << "<an_pbdlaVal species=\"Species_4\">1.792</an_pbdlaVal>"
       << "</an_partBioDbhLeafA>"
       << "<an_partBioDbhLeafB>"
       << "<an_pbdlbVal species=\"Species_2\">-3.49</an_pbdlbVal>"
       << "<an_pbdlbVal species=\"Species_4\">3.758</an_pbdlbVal>"
       << "</an_partBioDbhLeafB>"
       << "<an_partBioDbhBranchA>"
       << "<an_pbdbraVal species=\"Species_2\">2.062</an_pbdbraVal>"
       << "<an_pbdbraVal species=\"Species_4\">1.982</an_pbdbraVal>"
       << "</an_partBioDbhBranchA>"
       << "<an_partBioDbhBranchB>"
       << "<an_pbdbrbVal species=\"Species_2\">-5.963</an_pbdbrbVal>"
       << "<an_pbdbrbVal species=\"Species_4\">3.69</an_pbdbrbVal>"
       << "</an_partBioDbhBranchB>"
       << "<an_partBioDbhBoleA>"
       << "<an_pbdboaVal species=\"Species_2\">2.543</an_pbdboaVal>"
       << "<an_pbdboaVal species=\"Species_4\">2.559</an_pbdboaVal>"
       << "</an_partBioDbhBoleA>"
       << "<an_partBioDbhBoleB>"
       << "<an_pbdbobVal species=\"Species_2\">-3.139</an_pbdbobVal>"
       << "<an_pbdbobVal species=\"Species_4\">2.832</an_pbdbobVal>"
       << "</an_partBioDbhBoleB>"
       << "</PartitionedBiomass1>"
       << "</paramFile>";

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WritePartitionedBiomassXMLFile4()
////////////////////////////////////////////////////////////////////////////
const char* WritePartitionedBiomassXMLFile4() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WritePartitionedBiomassCommonFileBegin(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>PartitionedHeightBiomass</behaviorName>"
       << "<version>2</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_5\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_5\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<PartitionedBiomass1>"
       << "<an_partBioHeightLeafA>"
       << "<an_pbhlaVal species=\"Species_3\">1.7</an_pbhlaVal>"
       << "<an_pbhlaVal species=\"Species_5\">1.7</an_pbhlaVal>"
       << "</an_partBioHeightLeafA>"
       << "<an_partBioHeightLeafB>"
       << "<an_pbhlbVal species=\"Species_3\">6.8</an_pbhlbVal>"
       << "<an_pbhlbVal species=\"Species_5\">-2.3</an_pbhlbVal>"
       << "</an_partBioHeightLeafB>"
       << "<an_partBioHeightBoleA>"
       << "<an_pbhboaVal species=\"Species_3\">5.9</an_pbhboaVal>"
       << "<an_pbhboaVal species=\"Species_5\">5.9</an_pbhboaVal>"
       << "</an_partBioHeightBoleA>"
       << "<an_partBioHeightBoleB>"
       << "<an_pbhbobVal species=\"Species_3\">-1.6</an_pbhbobVal>"
       << "<an_pbhbobVal species=\"Species_5\">-1.6</an_pbhbobVal>"
       << "</an_partBioHeightBoleB>"
       << "</PartitionedBiomass1>"
       << "</paramFile>";

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WritePartitionedBiomassXMLErrorFile1()
////////////////////////////////////////////////////////////////////////////
const char* WritePartitionedBiomassXMLErrorFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WritePartitionedBiomassCommonFileBegin(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>PartitionedDBHBiomass</behaviorName>"
       << "<version>2</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<PartitionedBiomass1>"
       << "<an_partBioDbhLeafA>"
       << "<an_pbdlaVal species=\"Species_2\">1.523</an_pbdlaVal>"
       << "<an_pbdlaVal species=\"Species_4\">1.792</an_pbdlaVal>"
       << "</an_partBioDbhLeafA>"
       << "<an_partBioDbhLeafB>"
       << "<an_pbdlbVal species=\"Species_2\">-3.49</an_pbdlbVal>"
       << "<an_pbdlbVal species=\"Species_4\">3.758</an_pbdlbVal>"
       << "</an_partBioDbhLeafB>"
       << "<an_partBioDbhBranchA>"
       << "<an_pbdbraVal species=\"Species_2\">2.062</an_pbdbraVal>"
       << "<an_pbdbraVal species=\"Species_4\">1.982</an_pbdbraVal>"
       << "</an_partBioDbhBranchA>"
       << "<an_partBioDbhBranchB>"
       << "<an_pbdbrbVal species=\"Species_2\">-5.963</an_pbdbrbVal>"
       << "<an_pbdbrbVal species=\"Species_4\">3.69</an_pbdbrbVal>"
       << "</an_partBioDbhBranchB>"
       << "<an_partBioDbhBoleA>"
       << "<an_pbdboaVal species=\"Species_2\">2.543</an_pbdboaVal>"
       << "<an_pbdboaVal species=\"Species_4\">2.559</an_pbdboaVal>"
       << "</an_partBioDbhBoleA>"
       << "<an_partBioDbhBoleB>"
       << "<an_pbdbobVal species=\"Species_2\">-3.139</an_pbdbobVal>"
       << "<an_pbdbobVal species=\"Species_4\">2.832</an_pbdbobVal>"
       << "</an_partBioDbhBoleB>"
       << "</PartitionedBiomass1>"
       << "</paramFile>";

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WritePartitionedBiomassXMLErrorFile2()
////////////////////////////////////////////////////////////////////////////
const char* WritePartitionedBiomassXMLErrorFile2() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WritePartitionedBiomassCommonFileBegin(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>PartitionedHeightBiomass</behaviorName>"
       << "<version>2</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_5\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_5\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<PartitionedBiomass1>"
       << "<an_partBioHeightLeafA>"
       << "<an_pbhlaVal species=\"Species_3\">1.7</an_pbhlaVal>"
       << "<an_pbhlaVal species=\"Species_5\">1.7</an_pbhlaVal>"
       << "</an_partBioHeightLeafA>"
       << "<an_partBioHeightLeafB>"
       << "<an_pbhlbVal species=\"Species_3\">6.8</an_pbhlbVal>"
       << "<an_pbhlbVal species=\"Species_5\">-2.3</an_pbhlbVal>"
       << "</an_partBioHeightLeafB>"
       << "<an_partBioHeightBoleA>"
       << "<an_pbhboaVal species=\"Species_3\">5.9</an_pbhboaVal>"
       << "<an_pbhboaVal species=\"Species_5\">5.9</an_pbhboaVal>"
       << "</an_partBioHeightBoleA>"
       << "<an_partBioHeightBoleB>"
       << "<an_pbhbobVal species=\"Species_1\">-1.6</an_pbhbobVal>"
       << "<an_pbhbobVal species=\"Species_2\">-1.6</an_pbhbobVal>"
       << "</an_partBioHeightBoleB>"
       << "</PartitionedBiomass1>"
       << "</paramFile>";

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WritePartitionedBiomassCommonFileBegin()
/////////////////////////////////////////////////////////////////////////////
void WritePartitionedBiomassCommonFileBegin( std::fstream &oOut )
{
  using namespace std;
  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>2</timesteps>"
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
// WritePartitionedBiomassCommonFileEnd()
/////////////////////////////////////////////////////////////////////////////
void WritePartitionedBiomassCommonFileEnd( std::fstream &oOut )
{
  using namespace std;

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>PartitionedDBHBiomass</behaviorName>"
       << "<version>2</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>PartitionedHeightBiomass</behaviorName>"
       << "<version>2</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_5\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_5\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<PartitionedBiomass1>"
       << "<an_partBioDbhLeafA>"
       << "<an_pbdlaVal species=\"Species_2\">1.523</an_pbdlaVal>"
       << "<an_pbdlaVal species=\"Species_4\">1.792</an_pbdlaVal>"
       << "</an_partBioDbhLeafA>"
       << "<an_partBioDbhLeafB>"
       << "<an_pbdlbVal species=\"Species_2\">-3.49</an_pbdlbVal>"
       << "<an_pbdlbVal species=\"Species_4\">3.758</an_pbdlbVal>"
       << "</an_partBioDbhLeafB>"
       << "<an_partBioDbhBranchA>"
       << "<an_pbdbraVal species=\"Species_2\">2.062</an_pbdbraVal>"
       << "<an_pbdbraVal species=\"Species_4\">1.982</an_pbdbraVal>"
       << "</an_partBioDbhBranchA>"
       << "<an_partBioDbhBranchB>"
       << "<an_pbdbrbVal species=\"Species_2\">-5.963</an_pbdbrbVal>"
       << "<an_pbdbrbVal species=\"Species_4\">3.69</an_pbdbrbVal>"
       << "</an_partBioDbhBranchB>"
       << "<an_partBioDbhBoleA>"
       << "<an_pbdboaVal species=\"Species_2\">2.543</an_pbdboaVal>"
       << "<an_pbdboaVal species=\"Species_4\">2.559</an_pbdboaVal>"
       << "</an_partBioDbhBoleA>"
       << "<an_partBioDbhBoleB>"
       << "<an_pbdbobVal species=\"Species_2\">-3.139</an_pbdbobVal>"
       << "<an_pbdbobVal species=\"Species_4\">2.832</an_pbdbobVal>"
       << "</an_partBioDbhBoleB>"
       << "</PartitionedBiomass1>"
       << "<PartitionedBiomass2>"
       << "<an_partBioHeightLeafA>"
       << "<an_pbhlaVal species=\"Species_3\">1.7</an_pbhlaVal>"
       << "<an_pbhlaVal species=\"Species_5\">1.7</an_pbhlaVal>"
       << "</an_partBioHeightLeafA>"
       << "<an_partBioHeightLeafB>"
       << "<an_pbhlbVal species=\"Species_3\">6.8</an_pbhlbVal>"
       << "<an_pbhlbVal species=\"Species_5\">-2.3</an_pbhlbVal>"
       << "</an_partBioHeightLeafB>"
       << "<an_partBioHeightBoleA>"
       << "<an_pbhboaVal species=\"Species_3\">5.9</an_pbhboaVal>"
       << "<an_pbhboaVal species=\"Species_5\">5.9</an_pbhboaVal>"
       << "</an_partBioHeightBoleA>"
       << "<an_partBioHeightBoleB>"
       << "<an_pbhbobVal species=\"Species_3\">-1.6</an_pbhbobVal>"
       << "<an_pbhbobVal species=\"Species_5\">-1.6</an_pbhbobVal>"
       << "</an_partBioHeightBoleB>"
       << "</PartitionedBiomass2>"
       << "</paramFile>";
}
