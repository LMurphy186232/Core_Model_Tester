//---------------------------------------------------------------------------
// TestStormKilledPartitionedBiomass.cpp
//---------------------------------------------------------------------------
#include "TestStormKilledPartitionedBiomass.h"
#include <gtest/gtest.h>
#include <fstream>
#include <math.h>
#include "TreePopulation.h"
#include "SimManager.h"
#include "Grid.h"
#include "BehaviorBase.h"

////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun1()
////////////////////////////////////////////////////////////////////////////
TEST(StormKilledPartitionedBiomass, TestNormalProcessingRun1) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
  clTreePopulation * p_oPop;
  clGrid *p_oGrid;
  float fValue, fExpectedValue;
  int iNumXCells, iNumYCells, iX, iY, i;

  //Load our test file and get our tree population pointers
  p_oSimManager->ReadFile( WriteStormKilledPartitionedBiomassXMLFile1() );
  p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

  CreateStormKilledPartitionedBiomassTrees(p_oPop);

  //Now do the run, but skip the storm behaviors
  for (i = 3; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
    clBehaviorBase *p_oTemp = p_oSimManager->GetBehaviorObject(i);
    p_oTemp->Action();
  }

  p_oGrid = p_oSimManager->GetGridObject("Storm Killed Partitioned Biomass");
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

  //Run another timestep
  p_oSimManager->RunSim(1);

  //Make sure the grid totals are zero
  iNumXCells = p_oGrid->GetNumberXCells();
  iNumYCells = p_oGrid->GetNumberYCells();
  for (iX = 0; iX < iNumXCells; iX++) {
    for (iY = 0; iY < iNumYCells; iY++) {
      fExpectedValue = 0;
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("leaf_0"), &fValue);
      EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("leaf_1"), &fValue);
      EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("leaf_2"), &fValue);
      EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("leaf_3"), &fValue);
      EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("leaf_4"), &fValue);
      EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("bole_0"), &fValue);
      EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("bole_1"), &fValue);
      EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("bole_2"), &fValue);
      EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("bole_3"), &fValue);
      EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("bole_4"), &fValue);
      EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("branch_0"), &fValue);
      EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("branch_1"), &fValue);
      EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("branch_2"), &fValue);
      EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("branch_3"), &fValue);
      EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("branch_4"), &fValue);
      EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("hleaf_0"), &fValue);
      EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("hleaf_1"), &fValue);
      EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("hleaf_2"), &fValue);
      EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("hleaf_3"), &fValue);
      EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("hleaf_4"), &fValue);
      EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("hbole_0"), &fValue);
      EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("hbole_1"), &fValue);
      EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("hbole_2"), &fValue);
      EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("hbole_3"), &fValue);
      EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("hbole_4"), &fValue);
      EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
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
TEST(StormKilledPartitionedBiomass, TestNormalProcessingRun2) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
  clTreePopulation * p_oPop;
  clGrid *p_oGrid;
  float fValue, fExpectedValue;
  int i;

  //Load our test file and get our tree population pointers
  p_oSimManager->ReadFile( WriteStormKilledPartitionedBiomassXMLFile2() );
  p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

  CreateStormKilledPartitionedBiomassTrees(p_oPop);

  //Now do the run, but skip the storm behaviors
  for (i = 3; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
    clBehaviorBase *p_oTemp = p_oSimManager->GetBehaviorObject(i);
    p_oTemp->Action();
  }
  p_oGrid = p_oSimManager->GetGridObject("Storm Killed Partitioned Biomass");
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
TEST(StormKilledPartitionedBiomass, TestNormalProcessingRun3) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
  clTreePopulation * p_oPop;
  clGrid *p_oGrid;
  float fValue, fExpectedValue;
  int iNumXCells, iNumYCells, iX, iY, i;

  //Load our test file and get our tree population pointers
  p_oSimManager->ReadFile( WriteStormKilledPartitionedBiomassXMLFile3() );
  p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

  CreateStormKilledPartitionedBiomassTrees(p_oPop);

  //Now do the run, but skip the storm behaviors
  for (i = 2; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
    clBehaviorBase *p_oTemp = p_oSimManager->GetBehaviorObject(i);
    p_oTemp->Action();
  }
  p_oGrid = p_oSimManager->GetGridObject("Storm Killed Partitioned Biomass");
  ASSERT_TRUE(NULL != p_oGrid);

  //Make sure the height grid totals are zero
  iNumXCells = p_oGrid->GetNumberXCells();
  iNumYCells = p_oGrid->GetNumberYCells();
  for (iX = 0; iX < iNumXCells; iX++) {
    for (iY = 0; iY < iNumYCells; iY++) {
      fExpectedValue = 0;
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("hleaf_0"), &fValue);
      EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("hleaf_1"), &fValue);
      EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("hleaf_2"), &fValue);
      EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("hleaf_3"), &fValue);
      EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("hleaf_4"), &fValue);
      EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("hbole_0"), &fValue);
      EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("hbole_1"), &fValue);
      EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("hbole_2"), &fValue);
      EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("hbole_3"), &fValue);
      EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("hbole_4"), &fValue);
      EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
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
TEST(StormKilledPartitionedBiomass, TestNormalProcessingRun4) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
  clTreePopulation * p_oPop;
  clGrid *p_oGrid;
  float fValue, fExpectedValue;
  int iNumXCells, iNumYCells, iX, iY, i;

  //Load our test file and get our tree population pointers
  p_oSimManager->ReadFile( WriteStormKilledPartitionedBiomassXMLFile4() );
  p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

  CreateStormKilledPartitionedBiomassTrees(p_oPop);

  //Now do the run, but skip the storm behaviors
  for (i = 2; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
    clBehaviorBase *p_oTemp = p_oSimManager->GetBehaviorObject(i);
    p_oTemp->Action();
  }
  p_oGrid = p_oSimManager->GetGridObject("Storm Killed Partitioned Biomass");
  ASSERT_TRUE(NULL != p_oGrid);

  //Make sure the dbh grid totals are zero
  iNumXCells = p_oGrid->GetNumberXCells();
  iNumYCells = p_oGrid->GetNumberYCells();
  for (iX = 0; iX < iNumXCells; iX++) {
    for (iY = 0; iY < iNumYCells; iY++) {
      fExpectedValue = 0;
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("leaf_0"), &fValue);
      EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("leaf_1"), &fValue);
      EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("leaf_2"), &fValue);
      EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("leaf_3"), &fValue);
      EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("leaf_4"), &fValue);
      EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("bole_0"), &fValue);
      EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("bole_1"), &fValue);
      EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("bole_2"), &fValue);
      EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("bole_3"), &fValue);
      EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("bole_4"), &fValue);
      EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("branch_0"), &fValue);
      EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("branch_1"), &fValue);
      EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("branch_2"), &fValue);
      EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("branch_3"), &fValue);
      EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
      p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode("branch_4"), &fValue);
      EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
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
TEST(StormKilledPartitionedBiomass, TestErrorProcessing) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try
  {
    p_oSimManager->ReadFile(WriteStormKilledPartitionedBiomassXMLErrorFile1());
    FAIL() << "TestStormKilledPartitionedBiomass error processing didn't catch error for WriteStormKilledPartitionedBiomassXMLErrorFile1.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clStormKilledPartitionedBiomass::GetData") != 0)
    {
      FAIL() << "TestStormKilledPartitionedBiomass error processing caught wrong error for WriteStormKilledPartitionedBiomassXMLErrorFile1.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteStormKilledPartitionedBiomassXMLErrorFile2());
    FAIL() << "TestStormKilledPartitionedBiomass error processing didn't catch error for WriteStormKilledPartitionedBiomassXMLErrorFile2.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clStormKilledPartitionedBiomass::GetData") != 0)
    {
      FAIL() << "TestStormKilledPartitionedBiomass error processing caught wrong error for WriteStormKilledPartitionedBiomassXMLErrorFile2.";
    }
    ;
  }
  delete p_oSimManager;
}

////////////////////////////////////////////////////////////////////////////
// CreateStormKilledPartitionedBiomassTrees()
////////////////////////////////////////////////////////////////////////////
void CreateStormKilledPartitionedBiomassTrees(clTreePopulation *p_oPop) {

  clTree *p_oTree;
  float fX, fY, fDbh;
  int iSpecies, iType = clTreePopulation::snag,
      iCounter;

  iSpecies = 0;
  fX = 4;
  fY = 4;
  fDbh = 2;
  p_oPop->CreateTree(fX, fY, iSpecies, iType, fDbh);

  iSpecies = 0;
  fX = 4;
  fY = 4;
  fDbh = 2;
  p_oPop->CreateTree(fX, fY, iSpecies, iType, fDbh);

  iSpecies = 1;
  fX = 12;
  fY = 12;
  fDbh = 3;
  iCounter = 1000;
  p_oTree = p_oPop->CreateTree(fX, fY, iSpecies, iType, fDbh);
  p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg", iSpecies, iType), iCounter);

  iSpecies = 2;
  fX = 4;
  fY = 12;
  fDbh = 4;
  iCounter = 1000;
  p_oTree = p_oPop->CreateTree(fX, fY, iSpecies, iType, fDbh);
  p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg", iSpecies, iType), iCounter);

  iSpecies = 3;
  fX = 12;
  fY = 4;
  fDbh = 5;
  iCounter = 1001;
  p_oTree = p_oPop->CreateTree(fX, fY, iSpecies, iType, fDbh);
  p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg", iSpecies, iType), iCounter);

  iSpecies = 0;
  fX = 22;
  fY = 4;
  fDbh = 11;
  iCounter = 1000;
  p_oTree = p_oPop->CreateTree(fX, fY, iSpecies, iType, fDbh);

  iSpecies = 1;
  fX = 4;
  fY = 22;
  fDbh = 20;
  iCounter = 1000;
  p_oTree = p_oPop->CreateTree(fX, fY, iSpecies, iType, fDbh);
  p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg", iSpecies, iType), iCounter);

  iSpecies = 2;
  fX = 22;
  fY = 12;
  fDbh = 30;
  iCounter = 1000;
  p_oTree = p_oPop->CreateTree(fX, fY, iSpecies, iType, fDbh);
  p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg", iSpecies, iType), iCounter);

  iSpecies = 3;
  fX = 12;
  fY = 22;
  fDbh = 40;
  iCounter = 1000;
  p_oTree = p_oPop->CreateTree(fX, fY, iSpecies, iType, fDbh);
  p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg", iSpecies, iType), iCounter);

  iSpecies = 2;
  fX = 22;
  fY = 22;
  fDbh = 0.5;
  iCounter = 1000;
  p_oTree = p_oPop->CreateTree(fX, fY, iSpecies, iType, fDbh);
  p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg", iSpecies, iType), iCounter);

  iSpecies = 4;
  fX = 30;
  fY = 4;
  fDbh = 0.5;
  iCounter = 1000;
  p_oTree = p_oPop->CreateTree(fX, fY, iSpecies, iType, fDbh);
  p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg", iSpecies, iType), iCounter);

  iSpecies = 1;
  fX = 30;
  fY = 4;
  fDbh = 1;
  iCounter = 1000;
  p_oTree = p_oPop->CreateTree(fX, fY, iSpecies, iType, fDbh);
  p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg", iSpecies, iType), iCounter);

  iSpecies = 1;
  fX = 4;
  fY = 4;
  fDbh = 12;
  iCounter = 0;
  p_oTree = p_oPop->CreateTree(fX, fY, iSpecies, iType, fDbh);
  p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg", iSpecies, iType), iCounter);

  iSpecies = 1;
  fX = 4;
  fY = 4;
  fDbh = 12;
  iCounter = 1000;
  p_oTree = p_oPop->CreateTree(fX, fY, iSpecies, iType, fDbh);
  p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg", iSpecies, iType), iCounter);

  iSpecies = 2;
  fX = 4;
  fY = 4;
  fDbh = 30;
  iCounter = 1000;
  p_oTree = p_oPop->CreateTree(fX, fY, iSpecies, iType, fDbh);
  p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg", iSpecies, iType), iCounter);

  iSpecies = 2;
  fX = 4;
  fY = 4;
  fDbh = 30;
  iCounter = 1001;
  p_oTree = p_oPop->CreateTree(fX, fY, iSpecies, iType, fDbh);
  p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg", iSpecies, iType), iCounter);

  iSpecies = 3;
  fX = 4;
  fY = 4;
  fDbh = 50;
  iCounter = 2000;
  p_oTree = p_oPop->CreateTree(fX, fY, iSpecies, iType, fDbh);
  p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg", iSpecies, iType), iCounter);

  iSpecies = 3;
  fX = 4;
  fY = 4;
  fDbh = 50;
  iCounter = 2006;
  p_oTree = p_oPop->CreateTree(fX, fY, iSpecies, iType, fDbh);
  p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg", iSpecies, iType), iCounter);

  iSpecies = 4;
  fX = 4;
  fY = 4;
  fDbh = 30;
  iCounter = 2000;
  p_oTree = p_oPop->CreateTree(fX, fY, iSpecies, iType, fDbh);
  p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg", iSpecies, iType), iCounter);

  iSpecies = 4;
  fX = 4;
  fY = 4;
  fDbh = 30;
  iCounter = 0;
  p_oTree = p_oPop->CreateTree(fX, fY, iSpecies, iType, fDbh);
  p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg", iSpecies, iType), iCounter);

  iSpecies = 1;
  fX = 4;
  fY = 4;
  fDbh = 3;
  iCounter = 1000;
  p_oTree = p_oPop->CreateTree(fX, fY, iSpecies, iType, fDbh);
  p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg", iSpecies, iType), iCounter);

  iSpecies = 1;
  fX = 4;
  fY = 4;
  fDbh = 3;
  iCounter = 0;
  p_oTree = p_oPop->CreateTree(fX, fY, iSpecies, iType, fDbh);
  p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg", iSpecies, iType), iCounter);

  iSpecies = 3;
  fX = 4;
  fY = 4;
  fDbh = 40;
  iCounter = 2000;
  p_oTree = p_oPop->CreateTree(fX, fY, iSpecies, iType, fDbh);
  p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg", iSpecies, iType), iCounter);

  iSpecies = 3;
  fX = 4;
  fY = 4;
  fDbh = 40;
  iCounter = 2001;
  p_oTree = p_oPop->CreateTree(fX, fY, iSpecies, iType, fDbh);
  p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg", iSpecies, iType), iCounter);

  iSpecies = 0;
  fX = 4;
  fY = 4;
  fDbh = 11;
  p_oTree = p_oPop->CreateTree(fX, fY, iSpecies, iType, fDbh);

  iSpecies = 0;
  fX = 4;
  fY = 4;
  fDbh = 11;
  p_oTree = p_oPop->CreateTree(fX, fY, iSpecies, iType, fDbh);

  iSpecies = 2;
  fX = 4;
  fY = 4;
  fDbh = 30;
  iCounter = 1000;
  p_oTree = p_oPop->CreateTree(fX, fY, iSpecies, iType, fDbh);
  p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg", iSpecies, iType), iCounter);

  iSpecies = 2;
  fX = 4;
  fY = 4;
  fDbh = 30;
  iCounter = 0;
  p_oTree = p_oPop->CreateTree(fX, fY, iSpecies, iType, fDbh);
  p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg", iSpecies, iType), iCounter);

  iSpecies = 2;
  fX = 4;
  fY = 4;
  fDbh = 0.5;
  iCounter = 2000;
  p_oTree = p_oPop->CreateTree(fX, fY, iSpecies, iType, fDbh);
  p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg", iSpecies, iType), iCounter);

  iSpecies = 2;
  fX = 4;
  fY = 4;
  fDbh = 0.5;
  iCounter = 1001;
  p_oTree = p_oPop->CreateTree(fX, fY, iSpecies, iType, fDbh);
  p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg", iSpecies, iType), iCounter);

  iSpecies = 4;
  fX = 4;
  fY = 4;
  fDbh = 0.5;
  iCounter = 1000;
  p_oTree = p_oPop->CreateTree(fX, fY, iSpecies, iType, fDbh);
  p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg", iSpecies, iType), iCounter);

  iSpecies = 4;
  fX = 4;
  fY = 4;
  fDbh = 0.5;
  iCounter = 2001;
  p_oTree = p_oPop->CreateTree(fX, fY, iSpecies, iType, fDbh);
  p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg", iSpecies, iType), iCounter);

  iSpecies = 1;
  fX = 4;
  fY = 4;
  fDbh = 1;
  iCounter = 1000;
  p_oTree = p_oPop->CreateTree(fX, fY, iSpecies, iType, fDbh);
  p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg", iSpecies, iType), iCounter);

  iSpecies = 1;
  fX = 4;
  fY = 4;
  fDbh = 1;
  iCounter = 0;
  p_oTree = p_oPop->CreateTree(fX, fY, iSpecies, iType, fDbh);
  p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg", iSpecies, iType), iCounter);

  iSpecies = 3;
  fX = 12;
  fY = 4;
  fDbh = 10;
  iCounter = 1000;
  p_oTree = p_oPop->CreateTree(fX, fY, iSpecies, iType, fDbh);
  p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg", iSpecies, iType), iCounter);

  fX = 4;
  fY = 4;
  fDbh = 30;
  iType = clTreePopulation::adult;

  iSpecies = 0;
  p_oTree = p_oPop->CreateTree(fX, fY, iSpecies, iType, fDbh);

  iSpecies = 1;
  iCounter = 1000;
  p_oTree = p_oPop->CreateTree(fX, fY, iSpecies, iType, fDbh);
  p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg", iSpecies, iType), iCounter);

  iSpecies = 2;
  iCounter = 1005;
  p_oTree = p_oPop->CreateTree(fX, fY, iSpecies, iType, fDbh);
  p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg", iSpecies, iType), iCounter);

  iSpecies = 3;
  iCounter = 2000;
  p_oTree = p_oPop->CreateTree(fX, fY, iSpecies, iType, fDbh);
  p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg", iSpecies, iType), iCounter);

  iSpecies = 4;
  iCounter = 2002;
  p_oTree = p_oPop->CreateTree(fX, fY, iSpecies, iType, fDbh);
  p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg", iSpecies, iType), iCounter);
}

////////////////////////////////////////////////////////////////////////////
// WriteStormKilledPartitionedBiomassXMLFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteStormKilledPartitionedBiomassXMLFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteStormKilledPartitionedBiomassCommonFileBegin(oOut);
  WriteStormKilledPartitionedBiomassCommonFileEnd(oOut);

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteStormKilledPartitionedBiomassXMLFile2()
////////////////////////////////////////////////////////////////////////////
const char* WriteStormKilledPartitionedBiomassXMLFile2() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteStormKilledPartitionedBiomassCommonFileBegin(oOut);

  oOut << "<grid gridName=\"Storm Killed Partitioned Biomass\">"
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

  WriteStormKilledPartitionedBiomassCommonFileEnd(oOut);

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteStormKilledPartitionedBiomassXMLFile3()
////////////////////////////////////////////////////////////////////////////
const char* WriteStormKilledPartitionedBiomassXMLFile3() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteStormKilledPartitionedBiomassCommonFileBegin(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>Storm</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StormDamageApplier</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Snag\"/>"
       << "<applyTo species=\"Species_3\" type=\"Snag\"/>"
       << "<applyTo species=\"Species_4\" type=\"Snag\"/>"
       << "<applyTo species=\"Species_5\" type=\"Snag\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_5\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StormKilledPartitionedDBHBiomass</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Snag\"/>"
       << "<applyTo species=\"Species_4\" type=\"Snag\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<Storm1>"
       << "<st_s1ReturnInterval>0</st_s1ReturnInterval>"
       << "<st_s2ReturnInterval>0</st_s2ReturnInterval>"
       << "<st_s3ReturnInterval>0</st_s3ReturnInterval>"
       << "<st_s4ReturnInterval>0</st_s4ReturnInterval>"
       << "<st_s5ReturnInterval>0</st_s5ReturnInterval>"
       << "<st_s6ReturnInterval>0</st_s6ReturnInterval>"
       << "<st_s7ReturnInterval>0</st_s7ReturnInterval>"
       << "<st_s8ReturnInterval>0</st_s8ReturnInterval>"
       << "<st_s9ReturnInterval>0</st_s9ReturnInterval>"
       << "<st_s10ReturnInterval>0</st_s10ReturnInterval>"
       << "<st_susceptibility>1</st_susceptibility>"
       << "<st_stochasticity>0</st_stochasticity>"
       << "<st_stmSSTPeriod>1</st_stmSSTPeriod>"
       << "<st_stmSineD>0</st_stmSineD>"
       << "<st_stmSineF>1</st_stmSineF>"
       << "<st_stmSineG>1</st_stmSineG>"
       << "<st_stmTrendSlopeM>0</st_stmTrendSlopeM>"
       << "<st_stmTrendInterceptI>1</st_stmTrendInterceptI>"
       << "</Storm1>"
       << "<StormDamageApplier2>"
       << "<st_minDBH>"
       << "<st_mdVal species=\"Species_2\">0.001</st_mdVal>"
       << "<st_mdVal species=\"Species_3\">0.001</st_mdVal>"
       << "<st_mdVal species=\"Species_4\">0.001</st_mdVal>"
       << "<st_mdVal species=\"Species_5\">0.001</st_mdVal>"
       << "</st_minDBH>"
       << "<st_stmDmgInterceptMed>"
       << "<st_sdimVal species=\"Species_2\">2.1789601</st_sdimVal>"
       << "<st_sdimVal species=\"Species_3\">2.475987</st_sdimVal>"
       << "<st_sdimVal species=\"Species_4\">2.475987</st_sdimVal>"
       << "<st_sdimVal species=\"Species_5\">2.475987</st_sdimVal>"
       << "</st_stmDmgInterceptMed>"
       << "<st_stmDmgInterceptFull>"
       << "<st_sdifVal species=\"Species_2\">3.6334169</st_sdifVal>"
       << "<st_sdifVal species=\"Species_3\">3.6331242</st_sdifVal>"
       << "<st_sdifVal species=\"Species_4\">3.6331242</st_sdifVal>"
       << "<st_sdifVal species=\"Species_5\">3.6331242</st_sdifVal>"
       << "</st_stmDmgInterceptFull>"
       << "<st_stmIntensityCoeff>"
       << "<st_sicVal species=\"Species_2\">-0.3545352</st_sicVal>"
       << "<st_sicVal species=\"Species_3\">-1.2289105</st_sicVal>"
       << "<st_sicVal species=\"Species_4\">-1.2289105</st_sicVal>"
       << "<st_sicVal species=\"Species_5\">-1.2289105</st_sicVal>"
       << "</st_stmIntensityCoeff>"
       << "<st_stmDBHCoeff>"
       << "<st_sdcVal species=\"Species_2\">0.8280319</st_sdcVal>"
       << "<st_sdcVal species=\"Species_3\">0.3282479</st_sdcVal>"
       << "<st_sdcVal species=\"Species_4\">0.3282479</st_sdcVal>"
       << "<st_sdcVal species=\"Species_5\">0.3282479</st_sdcVal>"
       << "</st_stmDBHCoeff>"
       << "<st_numYearsToHeal>4</st_numYearsToHeal>"
       << "</StormDamageApplier2>"
       << "<StormKilledPartitionedBiomass3>"
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
       << "</StormKilledPartitionedBiomass3>"
       << "</paramFile>";

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteStormKilledPartitionedBiomassXMLFile4()
////////////////////////////////////////////////////////////////////////////
const char* WriteStormKilledPartitionedBiomassXMLFile4() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteStormKilledPartitionedBiomassCommonFileBegin(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>Storm</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StormDamageApplier</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Snag\"/>"
       << "<applyTo species=\"Species_3\" type=\"Snag\"/>"
       << "<applyTo species=\"Species_4\" type=\"Snag\"/>"
       << "<applyTo species=\"Species_5\" type=\"Snag\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_5\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StormKilledPartitionedHeightBiomass</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Snag\"/>"
       << "<applyTo species=\"Species_5\" type=\"Snag\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<Storm1>"
       << "<st_s1ReturnInterval>0</st_s1ReturnInterval>"
       << "<st_s2ReturnInterval>0</st_s2ReturnInterval>"
       << "<st_s3ReturnInterval>0</st_s3ReturnInterval>"
       << "<st_s4ReturnInterval>0</st_s4ReturnInterval>"
       << "<st_s5ReturnInterval>0</st_s5ReturnInterval>"
       << "<st_s6ReturnInterval>0</st_s6ReturnInterval>"
       << "<st_s7ReturnInterval>0</st_s7ReturnInterval>"
       << "<st_s8ReturnInterval>0</st_s8ReturnInterval>"
       << "<st_s9ReturnInterval>0</st_s9ReturnInterval>"
       << "<st_s10ReturnInterval>0</st_s10ReturnInterval>"
       << "<st_susceptibility>1</st_susceptibility>"
       << "<st_stochasticity>0</st_stochasticity>"
       << "<st_stmSSTPeriod>1</st_stmSSTPeriod>"
       << "<st_stmSineD>0</st_stmSineD>"
       << "<st_stmSineF>1</st_stmSineF>"
       << "<st_stmSineG>1</st_stmSineG>"
       << "<st_stmTrendSlopeM>0</st_stmTrendSlopeM>"
       << "<st_stmTrendInterceptI>1</st_stmTrendInterceptI>"
       << "</Storm1>"
       << "<StormDamageApplier2>"
       << "<st_minDBH>"
       << "<st_mdVal species=\"Species_2\">0.001</st_mdVal>"
       << "<st_mdVal species=\"Species_3\">0.001</st_mdVal>"
       << "<st_mdVal species=\"Species_4\">0.001</st_mdVal>"
       << "<st_mdVal species=\"Species_5\">0.001</st_mdVal>"
       << "</st_minDBH>"
       << "<st_stmDmgInterceptMed>"
       << "<st_sdimVal species=\"Species_2\">2.1789601</st_sdimVal>"
       << "<st_sdimVal species=\"Species_3\">2.475987</st_sdimVal>"
       << "<st_sdimVal species=\"Species_4\">2.475987</st_sdimVal>"
       << "<st_sdimVal species=\"Species_5\">2.475987</st_sdimVal>"
       << "</st_stmDmgInterceptMed>"
       << "<st_stmDmgInterceptFull>"
       << "<st_sdifVal species=\"Species_2\">3.6334169</st_sdifVal>"
       << "<st_sdifVal species=\"Species_3\">3.6331242</st_sdifVal>"
       << "<st_sdifVal species=\"Species_4\">3.6331242</st_sdifVal>"
       << "<st_sdifVal species=\"Species_5\">3.6331242</st_sdifVal>"
       << "</st_stmDmgInterceptFull>"
       << "<st_stmIntensityCoeff>"
       << "<st_sicVal species=\"Species_2\">-0.3545352</st_sicVal>"
       << "<st_sicVal species=\"Species_3\">-1.2289105</st_sicVal>"
       << "<st_sicVal species=\"Species_4\">-1.2289105</st_sicVal>"
       << "<st_sicVal species=\"Species_5\">-1.2289105</st_sicVal>"
       << "</st_stmIntensityCoeff>"
       << "<st_stmDBHCoeff>"
       << "<st_sdcVal species=\"Species_2\">0.8280319</st_sdcVal>"
       << "<st_sdcVal species=\"Species_3\">0.3282479</st_sdcVal>"
       << "<st_sdcVal species=\"Species_4\">0.3282479</st_sdcVal>"
       << "<st_sdcVal species=\"Species_5\">0.3282479</st_sdcVal>"
       << "</st_stmDBHCoeff>"
       << "<st_numYearsToHeal>4</st_numYearsToHeal>"
       << "</StormDamageApplier2>"
       << "<StormKilledPartitionedBiomass3>"
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
       << "</StormKilledPartitionedBiomass3>"
       << "</paramFile>";

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteStormKilledPartitionedBiomassXMLErrorFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteStormKilledPartitionedBiomassXMLErrorFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteStormKilledPartitionedBiomassCommonFileBegin(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>Storm</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StormDamageApplier</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Snag\"/>"
       << "<applyTo species=\"Species_3\" type=\"Snag\"/>"
       << "<applyTo species=\"Species_4\" type=\"Snag\"/>"
       << "<applyTo species=\"Species_5\" type=\"Snag\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StormKilledPartitionedDBHBiomass</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<Storm1>"
       << "<st_s1ReturnInterval>0</st_s1ReturnInterval>"
       << "<st_s2ReturnInterval>0</st_s2ReturnInterval>"
       << "<st_s3ReturnInterval>0</st_s3ReturnInterval>"
       << "<st_s4ReturnInterval>0</st_s4ReturnInterval>"
       << "<st_s5ReturnInterval>0</st_s5ReturnInterval>"
       << "<st_s6ReturnInterval>0</st_s6ReturnInterval>"
       << "<st_s7ReturnInterval>0</st_s7ReturnInterval>"
       << "<st_s8ReturnInterval>0</st_s8ReturnInterval>"
       << "<st_s9ReturnInterval>0</st_s9ReturnInterval>"
       << "<st_s10ReturnInterval>0</st_s10ReturnInterval>"
       << "<st_susceptibility>1</st_susceptibility>"
       << "<st_stochasticity>0</st_stochasticity>"
       << "<st_stmSSTPeriod>1</st_stmSSTPeriod>"
       << "<st_stmSineD>0</st_stmSineD>"
       << "<st_stmSineF>1</st_stmSineF>"
       << "<st_stmSineG>1</st_stmSineG>"
       << "<st_stmTrendSlopeM>0</st_stmTrendSlopeM>"
       << "<st_stmTrendInterceptI>1</st_stmTrendInterceptI>"
       << "</Storm1>"
       << "<StormDamageApplier2>"
       << "<st_minDBH>"
       << "<st_mdVal species=\"Species_2\">5</st_mdVal>"
       << "<st_mdVal species=\"Species_3\">6</st_mdVal>"
       << "<st_mdVal species=\"Species_4\">6</st_mdVal>"
       << "<st_mdVal species=\"Species_5\">6</st_mdVal>"
       << "</st_minDBH>"
       << "<st_stmDmgInterceptMed>"
       << "<st_sdimVal species=\"Species_2\">2.1789601</st_sdimVal>"
       << "<st_sdimVal species=\"Species_3\">2.475987</st_sdimVal>"
       << "<st_sdimVal species=\"Species_4\">2.475987</st_sdimVal>"
       << "<st_sdimVal species=\"Species_5\">2.475987</st_sdimVal>"
       << "</st_stmDmgInterceptMed>"
       << "<st_stmDmgInterceptFull>"
       << "<st_sdifVal species=\"Species_2\">3.6334169</st_sdifVal>"
       << "<st_sdifVal species=\"Species_3\">3.6331242</st_sdifVal>"
       << "<st_sdifVal species=\"Species_4\">3.6331242</st_sdifVal>"
       << "<st_sdifVal species=\"Species_5\">3.6331242</st_sdifVal>"
       << "</st_stmDmgInterceptFull>"
       << "<st_stmIntensityCoeff>"
       << "<st_sicVal species=\"Species_2\">-0.3545352</st_sicVal>"
       << "<st_sicVal species=\"Species_3\">-1.2289105</st_sicVal>"
       << "<st_sicVal species=\"Species_4\">-1.2289105</st_sicVal>"
       << "<st_sicVal species=\"Species_5\">-1.2289105</st_sicVal>"
       << "</st_stmIntensityCoeff>"
       << "<st_stmDBHCoeff>"
       << "<st_sdcVal species=\"Species_2\">0.8280319</st_sdcVal>"
       << "<st_sdcVal species=\"Species_3\">0.3282479</st_sdcVal>"
       << "<st_sdcVal species=\"Species_4\">0.3282479</st_sdcVal>"
       << "<st_sdcVal species=\"Species_5\">0.3282479</st_sdcVal>"
       << "</st_stmDBHCoeff>"
       << "<st_numYearsToHeal>4</st_numYearsToHeal>"
       << "</StormDamageApplier2>"
       << "<StormKilledPartitionedBiomass3>"
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
       << "</StormKilledPartitionedBiomass3>"
       << "</paramFile>";

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteStormKilledPartitionedBiomassXMLErrorFile2()
////////////////////////////////////////////////////////////////////////////
const char* WriteStormKilledPartitionedBiomassXMLErrorFile2() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteStormKilledPartitionedBiomassCommonFileBegin(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>Storm</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StormDamageApplier</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Snag\"/>"
       << "<applyTo species=\"Species_3\" type=\"Snag\"/>"
       << "<applyTo species=\"Species_4\" type=\"Snag\"/>"
       << "<applyTo species=\"Species_5\" type=\"Snag\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StormKilledPartitionedHeightBiomass</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_5\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_5\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<Storm1>"
       << "<st_s1ReturnInterval>0</st_s1ReturnInterval>"
       << "<st_s2ReturnInterval>0</st_s2ReturnInterval>"
       << "<st_s3ReturnInterval>0</st_s3ReturnInterval>"
       << "<st_s4ReturnInterval>0</st_s4ReturnInterval>"
       << "<st_s5ReturnInterval>0</st_s5ReturnInterval>"
       << "<st_s6ReturnInterval>0</st_s6ReturnInterval>"
       << "<st_s7ReturnInterval>0</st_s7ReturnInterval>"
       << "<st_s8ReturnInterval>0</st_s8ReturnInterval>"
       << "<st_s9ReturnInterval>0</st_s9ReturnInterval>"
       << "<st_s10ReturnInterval>0</st_s10ReturnInterval>"
       << "<st_susceptibility>1</st_susceptibility>"
       << "<st_stochasticity>0</st_stochasticity>"
       << "<st_stmSSTPeriod>1</st_stmSSTPeriod>"
       << "<st_stmSineD>0</st_stmSineD>"
       << "<st_stmSineF>1</st_stmSineF>"
       << "<st_stmSineG>1</st_stmSineG>"
       << "<st_stmTrendSlopeM>0</st_stmTrendSlopeM>"
       << "<st_stmTrendInterceptI>1</st_stmTrendInterceptI>"
       << "</Storm1>"
       << "<StormDamageApplier2>"
       << "<st_minDBH>"
       << "<st_mdVal species=\"Species_2\">5</st_mdVal>"
       << "<st_mdVal species=\"Species_3\">6</st_mdVal>"
       << "<st_mdVal species=\"Species_4\">6</st_mdVal>"
       << "<st_mdVal species=\"Species_5\">6</st_mdVal>"
       << "</st_minDBH>"
       << "<st_stmDmgInterceptMed>"
       << "<st_sdimVal species=\"Species_2\">2.1789601</st_sdimVal>"
       << "<st_sdimVal species=\"Species_3\">2.475987</st_sdimVal>"
       << "<st_sdimVal species=\"Species_4\">2.475987</st_sdimVal>"
       << "<st_sdimVal species=\"Species_5\">2.475987</st_sdimVal>"
       << "</st_stmDmgInterceptMed>"
       << "<st_stmDmgInterceptFull>"
       << "<st_sdifVal species=\"Species_2\">3.6334169</st_sdifVal>"
       << "<st_sdifVal species=\"Species_3\">3.6331242</st_sdifVal>"
       << "<st_sdifVal species=\"Species_4\">3.6331242</st_sdifVal>"
       << "<st_sdifVal species=\"Species_5\">3.6331242</st_sdifVal>"
       << "</st_stmDmgInterceptFull>"
       << "<st_stmIntensityCoeff>"
       << "<st_sicVal species=\"Species_2\">-0.3545352</st_sicVal>"
       << "<st_sicVal species=\"Species_3\">-1.2289105</st_sicVal>"
       << "<st_sicVal species=\"Species_4\">-1.2289105</st_sicVal>"
       << "<st_sicVal species=\"Species_5\">-1.2289105</st_sicVal>"
       << "</st_stmIntensityCoeff>"
       << "<st_stmDBHCoeff>"
       << "<st_sdcVal species=\"Species_2\">0.8280319</st_sdcVal>"
       << "<st_sdcVal species=\"Species_3\">0.3282479</st_sdcVal>"
       << "<st_sdcVal species=\"Species_4\">0.3282479</st_sdcVal>"
       << "<st_sdcVal species=\"Species_5\">0.3282479</st_sdcVal>"
       << "</st_stmDBHCoeff>"
       << "<st_numYearsToHeal>4</st_numYearsToHeal>"
       << "</StormDamageApplier2>"
       << "<StormKilledPartitionedBiomass3>"
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
       << "</StormKilledPartitionedBiomass3>"
       << "</paramFile>";

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteStormKilledPartitionedBiomassCommonFileBegin()
/////////////////////////////////////////////////////////////////////////////
void WriteStormKilledPartitionedBiomassCommonFileBegin( std::fstream &oOut ) {
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
       << "<tr_madVal species=\"Species_1\">0.001</tr_madVal>"
       << "<tr_madVal species=\"Species_2\">0.001</tr_madVal>"
       << "<tr_madVal species=\"Species_3\">0.001</tr_madVal>"
       << "<tr_madVal species=\"Species_4\">0.001</tr_madVal>"
       << "<tr_madVal species=\"Species_5\">0.001</tr_madVal>"
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
// WriteStormKilledPartitionedBiomassCommonFileEnd()
/////////////////////////////////////////////////////////////////////////////
void WriteStormKilledPartitionedBiomassCommonFileEnd( std::fstream &oOut ) {
  using namespace std;

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>Storm</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StormDamageApplier</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Snag\"/>"
       << "<applyTo species=\"Species_3\" type=\"Snag\"/>"
       << "<applyTo species=\"Species_4\" type=\"Snag\"/>"
       << "<applyTo species=\"Species_5\" type=\"Snag\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_5\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StormKiller</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Snag\"/>"
       << "<applyTo species=\"Species_3\" type=\"Snag\"/>"
       << "<applyTo species=\"Species_4\" type=\"Snag\"/>"
       << "<applyTo species=\"Species_5\" type=\"Snag\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_5\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StormKilledPartitionedDBHBiomass</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>4</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Snag\"/>"
       << "<applyTo species=\"Species_4\" type=\"Snag\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StormKilledPartitionedHeightBiomass</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>5</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Snag\"/>"
       << "<applyTo species=\"Species_5\" type=\"Snag\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StochasticMortality</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>6</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Snag\"/>"
       << "<applyTo species=\"Species_3\" type=\"Snag\"/>"
       << "<applyTo species=\"Species_4\" type=\"Snag\"/>"
       << "<applyTo species=\"Species_5\" type=\"Snag\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_5\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<Storm1>"
       << "<st_s1ReturnInterval>0</st_s1ReturnInterval>"
       << "<st_s2ReturnInterval>0</st_s2ReturnInterval>"
       << "<st_s3ReturnInterval>0</st_s3ReturnInterval>"
       << "<st_s4ReturnInterval>0</st_s4ReturnInterval>"
       << "<st_s5ReturnInterval>0</st_s5ReturnInterval>"
       << "<st_s6ReturnInterval>0</st_s6ReturnInterval>"
       << "<st_s7ReturnInterval>0</st_s7ReturnInterval>"
       << "<st_s8ReturnInterval>0</st_s8ReturnInterval>"
       << "<st_s9ReturnInterval>0</st_s9ReturnInterval>"
       << "<st_s10ReturnInterval>0</st_s10ReturnInterval>"
       << "<st_susceptibility>1</st_susceptibility>"
       << "<st_stochasticity>0</st_stochasticity>"
       << "<st_stmSSTPeriod>1</st_stmSSTPeriod>"
       << "<st_stmSineD>0</st_stmSineD>"
       << "<st_stmSineF>1</st_stmSineF>"
       << "<st_stmSineG>1</st_stmSineG>"
       << "<st_stmTrendSlopeM>0</st_stmTrendSlopeM>"
       << "<st_stmTrendInterceptI>1</st_stmTrendInterceptI>"
       << "</Storm1>"
       << "<StormDamageApplier2>"
       << "<st_minDBH>"
       << "<st_mdVal species=\"Species_2\">0.001</st_mdVal>"
       << "<st_mdVal species=\"Species_3\">0.001</st_mdVal>"
       << "<st_mdVal species=\"Species_4\">0.001</st_mdVal>"
       << "<st_mdVal species=\"Species_5\">0.001</st_mdVal>"
       << "</st_minDBH>"
       << "<st_stmDmgInterceptMed>"
       << "<st_sdimVal species=\"Species_2\">2.1789601</st_sdimVal>"
       << "<st_sdimVal species=\"Species_3\">2.475987</st_sdimVal>"
       << "<st_sdimVal species=\"Species_4\">2.475987</st_sdimVal>"
       << "<st_sdimVal species=\"Species_5\">2.475987</st_sdimVal>"
       << "</st_stmDmgInterceptMed>"
       << "<st_stmDmgInterceptFull>"
       << "<st_sdifVal species=\"Species_2\">3.6334169</st_sdifVal>"
       << "<st_sdifVal species=\"Species_3\">3.6331242</st_sdifVal>"
       << "<st_sdifVal species=\"Species_4\">3.6331242</st_sdifVal>"
       << "<st_sdifVal species=\"Species_5\">3.6331242</st_sdifVal>"
       << "</st_stmDmgInterceptFull>"
       << "<st_stmIntensityCoeff>"
       << "<st_sicVal species=\"Species_2\">-0.3545352</st_sicVal>"
       << "<st_sicVal species=\"Species_3\">-1.2289105</st_sicVal>"
       << "<st_sicVal species=\"Species_4\">-1.2289105</st_sicVal>"
       << "<st_sicVal species=\"Species_5\">-1.2289105</st_sicVal>"
       << "</st_stmIntensityCoeff>"
       << "<st_stmDBHCoeff>"
       << "<st_sdcVal species=\"Species_2\">0.8280319</st_sdcVal>"
       << "<st_sdcVal species=\"Species_3\">0.3282479</st_sdcVal>"
       << "<st_sdcVal species=\"Species_4\">0.3282479</st_sdcVal>"
       << "<st_sdcVal species=\"Species_5\">0.3282479</st_sdcVal>"
       << "</st_stmDBHCoeff>"
       << "<st_numYearsToHeal>4</st_numYearsToHeal>"
       << "</StormDamageApplier2>"
       << "<StormKiller3>"
       << "<st_minDBH>"
       << "<st_mdVal species=\"Species_2\">0.001</st_mdVal>"
       << "<st_mdVal species=\"Species_3\">0.001</st_mdVal>"
       << "<st_mdVal species=\"Species_4\">0.001</st_mdVal>"
       << "<st_mdVal species=\"Species_5\">0.001</st_mdVal>"
       << "</st_minDBH>"
       << "<st_stmMedDmgSurvProbA>"
       << "<st_smdspaVal species=\"Species_2\">0.6</st_smdspaVal>"
       << "<st_smdspaVal species=\"Species_3\">2.34</st_smdspaVal>"
       << "<st_smdspaVal species=\"Species_4\">2.34</st_smdspaVal>"
       << "<st_smdspaVal species=\"Species_5\">2.34</st_smdspaVal>"
       << "</st_stmMedDmgSurvProbA>"
       << "<st_stmMedDmgSurvProbB>"
       << "<st_smdspbVal species=\"Species_2\">-0.01</st_smdspbVal>"
       << "<st_smdspbVal species=\"Species_3\">-0.02</st_smdspbVal>"
       << "<st_smdspbVal species=\"Species_4\">-0.02</st_smdspbVal>"
       << "<st_smdspbVal species=\"Species_5\">-0.02</st_smdspbVal>"
       << "</st_stmMedDmgSurvProbB>"
       << "<st_stmFullDmgSurvProbA>"
       << "<st_sfdspaVal species=\"Species_2\">3.82</st_sfdspaVal>"
       << "<st_sfdspaVal species=\"Species_3\">1.39</st_sfdspaVal>"
       << "<st_sfdspaVal species=\"Species_4\">1.39</st_sfdspaVal>"
       << "<st_sfdspaVal species=\"Species_5\">1.39</st_sfdspaVal>"
       << "</st_stmFullDmgSurvProbA>"
       << "<st_stmFullDmgSurvProbB>"
       << "<st_sfdspbVal species=\"Species_2\">-0.079</st_sfdspbVal>"
       << "<st_sfdspbVal species=\"Species_3\">-0.05</st_sfdspbVal>"
       << "<st_sfdspbVal species=\"Species_4\">-0.05</st_sfdspbVal>"
       << "<st_sfdspbVal species=\"Species_5\">-0.05</st_sfdspbVal>"
       << "</st_stmFullDmgSurvProbB>"
       << "<st_stmPropTipUpFullDmg>"
       << "<st_sptufdVal species=\"Species_2\">0.3</st_sptufdVal>"
       << "<st_sptufdVal species=\"Species_3\">0.8</st_sptufdVal>"
       << "<st_sptufdVal species=\"Species_4\">0.8</st_sptufdVal>"
       << "<st_sptufdVal species=\"Species_5\">0.8</st_sptufdVal>"
       << "</st_stmPropTipUpFullDmg>"
       << "<st_numYearsStormSnags>3</st_numYearsStormSnags>"
       << "</StormKiller3>"
       << "<StochasticMortality6>"
       << "<mo_stochasticMortRate>"
       << "<mo_smrVal species=\"Species_2\">0.0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_3\">0.0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_4\">0.0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_5\">0.0</mo_smrVal>"
       << "</mo_stochasticMortRate>"
       << "</StochasticMortality6>"
       << "<StormKilledPartitionedBiomass4>"
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
       << "</StormKilledPartitionedBiomass4>"
       << "<StormKilledPartitionedBiomass5>"
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
       << "</StormKilledPartitionedBiomass5>"
       << "</paramFile>";
}
