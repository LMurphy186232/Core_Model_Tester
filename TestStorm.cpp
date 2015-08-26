//---------------------------------------------------------------------------
// TestStorm.cpp
//---------------------------------------------------------------------------
#include "TestStorm.h"
#include <gtest/gtest.h>
#include "SimManager.h"
#include "Grid.h"
#include "Storm.h"
#include <fstream>
#include <math.h>

/////////////////////////////////////////////////////////////////////////////
// TestNormalDeterministic()
// Tests normal processing for a deterministic damage pattern.
// WriteStormXMLFile1() does setup. Here's how it goes:
//
// -- "Storm Damage" Grid:  10 X 10 cells.
// -- Storm return intervals:
//
//   -- 1 - 0
//   -- 2 - 1
//   -- 3 - 20
//   -- 4 - 1.00E+28
//   -- 5 - 13.2
//   -- 6 - 45
//   -- 7 - 50
//   -- 8 - 55
//   -- 9 - 60
//   -- 10 - 65
//
// -- Pre-run:  Make sure probabilities are calculated correctly.
// Time since last storm = 0.
// -- Timestep 1:  No storms. All cell values = 0. Time since
// last storm = 1.
// -- Timestep 2:  1 storm of severity 0.4-0.5. All cell values between 0.4
// and 0.5. Time since last storm = 0.
// -- Timestep 3:  2 storms of severity 0.2-0.3 and 0.5-0.6. All cell values
// between 0.7 and 0.9. Time since last storm = 0.
// -- Timestep 4:  No storms. All cell values = 0. Time since last
// storm = 1.
// -- Timestep 5:  2 storms of of severity 0.6-0.7 and 0.8-0.9. All cell
// values = 1. Time since last storm = 0.
// -- Timesteps 6, 7, 8 No storms. All cell values 0. Time since last
// storm = 1, 2, 3.
/////////////////////////////////////////////////////////////////////////////
TEST(Storm, TestNormalDeterministic)
{
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clGrid * p_oStormDamage; //storm damage grid
    clPackage *p_oPackage;
    clBehaviorBase * p_oTemp;
    clStorm * p_oStormBehavior;
    float fVal, fRefVal1, fRefVal2, fAvg;
    int i, iX, iY, iNumXCells, iNumYCells, iIndexCode, iAvgIndexCode,
    iStormTimeCode;

    //Load our parameter file
    p_oSimManager->ReadFile( WriteStormXMLFile1() );

    //Get the grid object and make sure it's set up correctly
    p_oStormDamage = p_oSimManager->GetGridObject( "Storm Damage" );
    ASSERT_TRUE( p_oStormDamage != NULL );
    iNumXCells = p_oStormDamage->GetNumberXCells();
    iNumYCells = p_oStormDamage->GetNumberYCells();
    EXPECT_EQ( 13, iNumXCells );
    EXPECT_EQ( 17, iNumYCells );
    iIndexCode = p_oStormDamage->GetPackageFloatDataCode( "1dmg_index" );
    iAvgIndexCode = p_oStormDamage->GetFloatDataCode("dmg_index");
    iStormTimeCode = p_oStormDamage->GetFloatDataCode( "stormtime" );
    ASSERT_TRUE( iIndexCode != -1 );
    ASSERT_TRUE( iAvgIndexCode != -1);
    ASSERT_TRUE( iStormTimeCode != -1 );

    //Make sure the storm probabilities were calculated correctly
    p_oTemp = p_oSimManager->GetBehaviorObject( "Storm" );
    ASSERT_TRUE( NULL != p_oTemp );
    p_oStormBehavior = dynamic_cast<clStorm *>(p_oTemp);
    EXPECT_LT( fabs(0.5 - p_oStormBehavior->GetStormProbability(0) ), 0.00001);
    EXPECT_LT( fabs(1 - p_oStormBehavior->GetStormProbability(1) ), 0.00001);
    EXPECT_LT( fabs(0.05 - p_oStormBehavior->GetStormProbability(2) ), 0.00001);
    EXPECT_LT( fabs(0 - p_oStormBehavior->GetStormProbability(3) ), 0.00001);
    EXPECT_LT( fabs(0.075757576 - p_oStormBehavior->GetStormProbability(4) ), 0.00001);
    EXPECT_LT( fabs(0.022222222 - p_oStormBehavior->GetStormProbability(5) ), 0.00001);
    EXPECT_LT( fabs(0.02 - p_oStormBehavior->GetStormProbability(6) ), 0.00001);
    EXPECT_LT( fabs(0.018181818 - p_oStormBehavior->GetStormProbability(7) ), 0.00001);
    EXPECT_LT( fabs(0.016666667 - p_oStormBehavior->GetStormProbability(8) ), 0.00001);
    EXPECT_LT( fabs(0.015384615 - p_oStormBehavior->GetStormProbability(9) ), 0.00001);

    // ****************************
    // Timestep 1
    // ****************************
    //Make sure no storms will occur
    for ( i = 0; i < 10; i++ )
    {
      p_oStormBehavior->SetStormProbability(i, 0);
    }

    p_oSimManager->RunSim( 1 );
    //Check timestep 1 results - all cells should be 1 for time, no packages
    for ( iX = 0; iX < iNumXCells; iX++ )
      for ( iY = 0; iY < iNumYCells; iY++ )
      {
        EXPECT_EQ( NULL, p_oStormDamage->GetFirstPackageOfCell(iX, iY) );
        p_oStormDamage->GetValueOfCell( iX, iY, iStormTimeCode, & fVal );
        EXPECT_EQ( 1, fVal );
        p_oStormDamage->GetValueOfCell( iX, iY, iAvgIndexCode, &fVal);
        EXPECT_EQ( 0, fVal );
      }


    // ****************************
    // Timestep 2
    // ****************************
    p_oSimManager->RunSim( 1 );

    //Check timestep 2 results - all cells should be between 0.4 and 0.5,
    //and they should all be equal
    p_oPackage = p_oStormDamage->GetFirstPackageOfCell(0, 0);
    ASSERT_TRUE(NULL != p_oPackage);
    p_oPackage->GetValue(iIndexCode, &fRefVal1);
    EXPECT_TRUE( fRefVal1 >= 0.4 && fRefVal1 <= 0.5);
    for ( iX = 0; iX < iNumXCells; iX++ )
      for ( iY = 0; iY < iNumYCells; iY++ )
      {
        p_oPackage = p_oStormDamage->GetFirstPackageOfCell(iX, iY);
        ASSERT_TRUE(NULL != p_oPackage);
        EXPECT_EQ(NULL, p_oPackage->GetNextPackage());
        p_oPackage->GetValue(iIndexCode, &fVal);
        EXPECT_LT(fabs(fVal - fRefVal1), 0.0001);
        p_oStormDamage->GetValueOfCell( iX, iY, iStormTimeCode, & fVal );
        EXPECT_EQ( 0, fVal );
        p_oStormDamage->GetValueOfCell( iX, iY, iAvgIndexCode, &fVal);
        EXPECT_LT(fabs(fVal - fRefVal1), 0.0001);
      }

    // ****************************
    // Timestep 3
    // ****************************
    p_oSimManager->RunSim( 1 );

    //Check timestep 3 results - two packages per cell
    p_oPackage = p_oStormDamage->GetFirstPackageOfCell(0, 0);
    ASSERT_TRUE(NULL != p_oPackage);
    p_oPackage->GetValue(iIndexCode, &fRefVal1);
    EXPECT_TRUE( fRefVal1 >= 0.5 && fRefVal1 <= 0.6);
    p_oPackage = p_oPackage->GetNextPackage();
    ASSERT_TRUE(NULL != p_oPackage);
    p_oPackage->GetValue(iIndexCode, &fRefVal2);
    EXPECT_TRUE( fRefVal2 >= 0.2 && fRefVal2 <= 0.3);
    fAvg = (fRefVal1 + fRefVal2) / 2;
    for ( iX = 0; iX < iNumXCells; iX++ )
      for ( iY = 0; iY < iNumYCells; iY++ )
      {
        p_oPackage = p_oStormDamage->GetFirstPackageOfCell(iX, iY);
        ASSERT_TRUE(NULL != p_oPackage);
        p_oPackage->GetValue(iIndexCode, &fVal);
        EXPECT_LT(fabs(fVal - fRefVal1), 0.0001);
        p_oPackage = p_oPackage->GetNextPackage();
        ASSERT_TRUE(NULL != p_oPackage);
        EXPECT_EQ(NULL, p_oPackage->GetNextPackage());
        p_oPackage->GetValue(iIndexCode, &fVal);
        EXPECT_LT(fabs(fVal - fRefVal2), 0.0001);

        p_oStormDamage->GetValueOfCell( iX, iY, iAvgIndexCode, &fVal);
        EXPECT_LT(fabs(fVal - fAvg), 0.0001);

        p_oStormDamage->GetValueOfCell( iX, iY, iStormTimeCode, & fVal );
        EXPECT_EQ( 0, fVal );
      }

    // ****************************
    // Timestep 4
    // ****************************
    p_oSimManager->RunSim( 1 );

    //Check timestep 4 results - all cells should be 0
    for ( iX = 0; iX < iNumXCells; iX++ )
      for ( iY = 0; iY < iNumYCells; iY++ )
      {
        EXPECT_EQ( NULL, p_oStormDamage->GetFirstPackageOfCell(iX, iY) );
        p_oStormDamage->GetValueOfCell( iX, iY, iStormTimeCode, & fVal );
        EXPECT_EQ( 1, fVal );
        p_oStormDamage->GetValueOfCell( iX, iY, iAvgIndexCode, &fVal);
        EXPECT_EQ( 0, fVal );
      }

    // ****************************
    // Timestep 5
    // ****************************
    p_oSimManager->RunSim( 1 );

    //Check timestep 5 results
    p_oPackage = p_oStormDamage->GetFirstPackageOfCell(0, 0);
    ASSERT_TRUE(NULL != p_oPackage);
    p_oPackage->GetValue(iIndexCode, &fRefVal1);
    EXPECT_TRUE( fRefVal1 >= 0.8 && fRefVal1 <= 0.9);
    p_oPackage = p_oPackage->GetNextPackage();
    ASSERT_TRUE(NULL != p_oPackage);
    EXPECT_EQ(NULL, p_oPackage->GetNextPackage());
    p_oPackage->GetValue(iIndexCode, &fRefVal2);
    EXPECT_TRUE( fRefVal2 >= 0.6 && fRefVal2 <= 0.7);
    fAvg = (fRefVal1 + fRefVal2) / 2;
    for ( iX = 0; iX < iNumXCells; iX++ )
      for ( iY = 0; iY < iNumYCells; iY++ )
      {
        p_oPackage = p_oStormDamage->GetFirstPackageOfCell(iX, iY);
        ASSERT_TRUE(NULL != p_oPackage);
        p_oPackage->GetValue(iIndexCode, &fVal);
        EXPECT_LT(fabs(fVal - fRefVal1), 0.0001);
        p_oPackage = p_oPackage->GetNextPackage();
        ASSERT_TRUE(NULL != p_oPackage);
        p_oPackage->GetValue(iIndexCode, &fVal);
        EXPECT_LT(fabs(fVal - fRefVal2), 0.0001);
        p_oStormDamage->GetValueOfCell( iX, iY, iAvgIndexCode, &fVal);
        EXPECT_LT(fabs(fVal - fAvg), 0.0001);
        p_oStormDamage->GetValueOfCell( iX, iY, iStormTimeCode, & fVal );
        EXPECT_EQ( 0, fVal );
      }

    // ****************************
    // Timestep 6
    // ****************************
    p_oSimManager->RunSim( 1 );

    //Check timestep 6 results - no packages
    for ( iX = 0; iX < iNumXCells; iX++ )
      for ( iY = 0; iY < iNumYCells; iY++ )
      {
        EXPECT_EQ( NULL, p_oStormDamage->GetFirstPackageOfCell(iX, iY) );
        p_oStormDamage->GetValueOfCell( iX, iY, iStormTimeCode, & fVal );
        EXPECT_EQ( 1, fVal );
        p_oStormDamage->GetValueOfCell( iX, iY, iAvgIndexCode, &fVal);
        EXPECT_EQ( 0, fVal );
      }

    // ****************************
    // Timestep 7
    // ****************************
    p_oSimManager->RunSim( 1 );

    //Check timestep 7 results - no packages
    for ( iX = 0; iX < iNumXCells; iX++ )
      for ( iY = 0; iY < iNumYCells; iY++ )
      {
        EXPECT_EQ( NULL, p_oStormDamage->GetFirstPackageOfCell(iX, iY) );
        p_oStormDamage->GetValueOfCell( iX, iY, iStormTimeCode, & fVal );
        EXPECT_EQ( 2, fVal );
        p_oStormDamage->GetValueOfCell( iX, iY, iAvgIndexCode, &fVal);
        EXPECT_EQ( 0, fVal );
      }

    // ****************************
    // Timestep 8
    // ****************************
    p_oSimManager->RunSim( 1 );

    //Check timestep 8 results - no packages
    for ( iX = 0; iX < iNumXCells; iX++ )
      for ( iY = 0; iY < iNumYCells; iY++ )
      {
        EXPECT_EQ( NULL, p_oStormDamage->GetFirstPackageOfCell(iX, iY) );
        p_oStormDamage->GetValueOfCell( iX, iY, iStormTimeCode, & fVal );
        EXPECT_EQ( 3, fVal );
        p_oStormDamage->GetValueOfCell( iX, iY, iAvgIndexCode, &fVal);
        EXPECT_EQ( 0, fVal );
      }

    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestNormalMappedDeterministic()
// Tests normal processing for a deterministic mapped damage pattern.
// WriteStormXMLFile2() does setup. Here's how it goes:
//
// -- "Storm Damage" Grid:   5 X 3 cells. Susceptibility map values are
// X/10 + Y/100.
// -- Timestep 1:  1 storm of severity 0.1-0.2. Cell values between
// (x/10 + y/100) * 0.1 and (x/10 + y/100) * 0.2.
// -- Timestep 2:  3 storms of 0-0.1, 0.1-0.2, and 0.2-0.3. Cell values
// between (x/10 + y/100) * 0.3 and (x/10 + y/100) * 0.6.
// -- Timestep 3:  No storms. All cell values = 0.
// -- Timestep 4:  2 storms of severity 0.6-0.7 and 0.9 - 1. All cell
// values between x/10 + y/100 * 1.5 and 1.
/////////////////////////////////////////////////////////////////////////////
TEST(Storm, TestNormalMappedDeterministic)
{
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clGrid * p_oStormDamage, //storm damage grid
    * p_oSusceptibility;
    clBehaviorBase * p_oTemp;
    clStorm * p_oStormBehavior;
    clPackage *p_oPackage;
    float fVal, fAvg, fExpectedValMin, fExpectedValMax;
    int i, iX, iY, iNumXCells, iNumYCells, iIndexCode, iAvgIndexCode;

    //Load our parameter file
    p_oSimManager->ReadFile( WriteStormXMLFile2() );

    //Get the grid object and make sure it's set up correctly
    p_oStormDamage = p_oSimManager->GetGridObject( "Storm Damage" );
    ASSERT_TRUE( p_oStormDamage != NULL );
    iNumXCells = p_oStormDamage->GetNumberXCells();
    iNumYCells = p_oStormDamage->GetNumberYCells();
    EXPECT_EQ( 20, iNumXCells );
    EXPECT_EQ( 44, iNumYCells );
    iIndexCode = p_oStormDamage->GetPackageFloatDataCode( "1dmg_index" );
    ASSERT_TRUE( iIndexCode != -1 );
    iAvgIndexCode = p_oStormDamage->GetFloatDataCode( "dmg_index" );
    ASSERT_TRUE( iAvgIndexCode != 1 );

    p_oSusceptibility = p_oSimManager->GetGridObject( "Storm Susceptibility" );
    ASSERT_TRUE( p_oSusceptibility != NULL );
    iNumXCells = p_oSusceptibility->GetNumberXCells();
    iNumYCells = p_oSusceptibility->GetNumberYCells();
    EXPECT_EQ( 20, iNumXCells );
    EXPECT_EQ( 44, iNumYCells );

    //Make sure the storm probabilities were calculated correctly
    p_oTemp = p_oSimManager->GetBehaviorObject( "Storm" );
    ASSERT_TRUE( NULL != p_oTemp );
    p_oStormBehavior = dynamic_cast<clStorm *>(p_oTemp);

    // ****************************
    // Timestep 1
    // ****************************
    for ( i = 0; i < 10; i++ )
    {
      p_oStormBehavior->SetStormProbability(i, 0);
    }

    p_oSimManager->RunSim(1);

    //Check timestep 1 results - all cells should be between (x/10 + y/10) * 0.1
    //and (x/10 + y/100) * 0.2
    for ( iX = 0; iX < iNumXCells; iX++ )
      for ( iY = 0; iY < iNumYCells; iY++ )
      {
        fExpectedValMin = ( ( float )iX / 10 + ( float )iY / 10 ) * 0.1;
        if (fExpectedValMin > 1) fExpectedValMin = 1;
        fExpectedValMax =  ( ( float )iX / 10 + ( float )iY / 10 ) * 0.2;
        if (fExpectedValMax > 1) fExpectedValMax = 1;
        p_oPackage = p_oStormDamage->GetFirstPackageOfCell(iX, iY);
        ASSERT_TRUE(NULL != p_oPackage);
        p_oPackage->GetValue(iIndexCode, &fVal);
        EXPECT_TRUE( fVal >= fExpectedValMin && fVal <= fExpectedValMax);
        p_oStormDamage->GetValueOfCell( iX, iY, iAvgIndexCode, &fAvg);
        EXPECT_EQ( fAvg, fVal );
      }

    // ****************************
    // Timestep 2
    // ****************************
    p_oSimManager->RunSim(1);

    //Check timestep 2 results - cell package values of 0 - (x/10 + y/10) * 0.1,
    //(x/10 + y/10) * 0.1 and (x/10 + y/10) * 0.2, and
    //(x/10 + y/10) * 0.2 * (x/10 + y/10) * 0.3.
    for ( iX = 0; iX < iNumXCells; iX++ )
      for ( iY = 0; iY < iNumYCells; iY++ )
      {
        fAvg = 0;

        //Package 1
        fExpectedValMin = ( ( float )iX / 10 + ( float )iY / 10 ) * 0.2;
        if (fExpectedValMin > 1) fExpectedValMin = 1;
        fExpectedValMax =  ( ( float )iX / 10 + ( float )iY / 10 ) * 0.3;
        if (fExpectedValMax > 1) fExpectedValMax = 1;
        p_oPackage = p_oStormDamage->GetFirstPackageOfCell(iX, iY);
        ASSERT_TRUE(NULL != p_oPackage);
        p_oPackage->GetValue(iIndexCode, &fVal);
        EXPECT_TRUE( fVal >= fExpectedValMin && fVal <= fExpectedValMax);
        fAvg += fVal;

        //Package 2
        fExpectedValMin = ( ( float )iX / 10 + ( float )iY / 10 ) * 0.1;
        if (fExpectedValMin > 1) fExpectedValMin = 1;
        fExpectedValMax =  ( ( float )iX / 10 + ( float )iY / 10 ) * 0.2;
        if (fExpectedValMax > 1) fExpectedValMax = 1;
        p_oPackage = p_oPackage->GetNextPackage();
        ASSERT_TRUE(NULL != p_oPackage);
        p_oPackage->GetValue(iIndexCode, &fVal);
        EXPECT_TRUE( fVal >= fExpectedValMin && fVal <= fExpectedValMax);
        fAvg += fVal;

        //Package 3
        fExpectedValMin = 0;
        fExpectedValMax =  ( ( float )iX / 10 + ( float )iY / 10 ) * 0.1;
        if (fExpectedValMax > 1) fExpectedValMax = 1;
        p_oPackage = p_oPackage->GetNextPackage();
        ASSERT_TRUE(NULL != p_oPackage);
        p_oPackage->GetValue(iIndexCode, &fVal);
        EXPECT_TRUE( fVal >= fExpectedValMin && fVal <= fExpectedValMax);
        EXPECT_EQ(NULL, p_oPackage->GetNextPackage());
        fAvg += fVal;

        fAvg /= 3;
        p_oStormDamage->GetValueOfCell( iX, iY, iAvgIndexCode, &fVal);
        EXPECT_LT( fabs(fAvg - fVal), 0.0001 );
      }

    // ****************************
    // Timestep 3
    // ****************************
    p_oSimManager->RunSim(1);

    //Check timestep 3 results - all cells should be 0.
    for ( iX = 0; iX < iNumXCells; iX++ )
      for ( iY = 0; iY < iNumYCells; iY++ )
      {
        EXPECT_EQ( NULL, p_oStormDamage->GetFirstPackageOfCell(iX, iY) );
        p_oStormDamage->GetValueOfCell( iX, iY, iAvgIndexCode, &fAvg);
        EXPECT_EQ( 0, fAvg );
      }

    // ****************************
    // Timestep 4
    // ****************************
    p_oSimManager->RunSim(1);

    //Check timestep 4 results - cell package values between (x/10 + y/10) * 0.6
    // and (x/10 + y/10) * 0.7, and (x/10 + y/10) * 0.9 and 1.
    for ( iX = 0; iX < iNumXCells; iX++ )
      for ( iY = 0; iY < iNumYCells; iY++ )
      {
        fAvg = 0;

        //Package 1
        fExpectedValMin = ( ( float )iX / 10 + ( float )iY / 10 ) * 0.9;
        if (fExpectedValMin > 1) fExpectedValMin = 1;
        fExpectedValMax =  ( ( float )iX / 10 + ( float )iY / 10 );
        if (fExpectedValMax > 1) fExpectedValMax = 1;
        p_oPackage = p_oStormDamage->GetFirstPackageOfCell(iX, iY);
        ASSERT_TRUE(NULL != p_oPackage);
        p_oPackage->GetValue(iIndexCode, &fVal);
        EXPECT_TRUE( fVal >= fExpectedValMin && fVal <= fExpectedValMax);
        fAvg += fVal;

        //Package 2
        fExpectedValMin = ( ( float )iX / 10 + ( float )iY / 10 ) * 0.6;
        if (fExpectedValMin > 1) fExpectedValMin = 1;
        fExpectedValMax =  ( ( float )iX / 10 + ( float )iY / 10 ) * 0.7;
        if (fExpectedValMax > 1) fExpectedValMax = 1;
        p_oPackage = p_oPackage->GetNextPackage();
        ASSERT_TRUE(NULL != p_oPackage);
        p_oPackage->GetValue(iIndexCode, &fVal);
        EXPECT_TRUE( fVal >= fExpectedValMin && fVal <= fExpectedValMax);
        EXPECT_EQ(NULL, p_oPackage->GetNextPackage());
        fAvg += fVal;

        fAvg /= 2;
        p_oStormDamage->GetValueOfCell( iX, iY, iAvgIndexCode, &fVal);
        EXPECT_LT( fabs(fAvg - fVal), 0.0001 );
      }

    // ****************************
    // Timestep 5
    // ****************************
    p_oSimManager->RunSim(1);

    //Check timestep 5 results - no packages
    for ( iX = 0; iX < iNumXCells; iX++ )
      for ( iY = 0; iY < iNumYCells; iY++ )
        EXPECT_EQ( NULL, p_oStormDamage->GetFirstPackageOfCell(iX, iY) );

    // ****************************
    // Timestep 6
    // ****************************
    p_oSimManager->RunSim(1);

    //Check timestep 6 results - no packages
    for ( iX = 0; iX < iNumXCells; iX++ )
      for ( iY = 0; iY < iNumYCells; iY++ )
        EXPECT_EQ( NULL, p_oStormDamage->GetFirstPackageOfCell(iX, iY) );

    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestNormalStochastic()
// Tests normal processing for a stochastic damage pattern. WriteStormXMLFile3()
// does setup. Here's how it goes:
//
// -- Grid resolution is 10X10.
// -- Normal-distribute the results with a standard deviation of 0.1.
// -- Storm damage indexes are the same as for
// TestNormalDeterministic().
// -- Timestep 1:  No storms. All cell values = 0.
// -- Timestep 2:  2 storms of severity 0.6-0.7 and 0.8-0.9. Cell values
// have a mean of 1 and a max of 1.
// -- Timestep 3:  1 storm of severity 0.4 - 0.5. Cell values have a mean of
// between 0.4 and 0.5.
/////////////////////////////////////////////////////////////////////////////
TEST(Storm, TestNormalStochastic)
{
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clGrid * p_oStormDamage; //storm damage grid
    clBehaviorBase * p_oTemp;
    clStorm * p_oStormBehavior;
    clPackage *p_oPackage;
    float fVal, fAvg, fStdDev;
    int i, iX, iY, iNumXCells, iNumYCells, iIndexCode;

    //Load our parameter file
    p_oSimManager->ReadFile( WriteStormXMLFile3() );

    p_oTemp = p_oSimManager->GetBehaviorObject( "Storm" );
    ASSERT_TRUE( NULL != p_oTemp );
    p_oStormBehavior = dynamic_cast<clStorm *>(p_oTemp);

    //Get the grid object and make sure it's set up correctly
    p_oStormDamage = p_oSimManager->GetGridObject( "Storm Damage" );
    ASSERT_TRUE( p_oStormDamage != NULL );
    iNumXCells = p_oStormDamage->GetNumberXCells();
    iNumYCells = p_oStormDamage->GetNumberYCells();
    EXPECT_EQ( 10, iNumXCells );
    EXPECT_EQ( 13, iNumYCells );
    iIndexCode = p_oStormDamage->GetPackageFloatDataCode( "1dmg_index" );
    ASSERT_TRUE( iIndexCode != -1 );

    // ****************************
    // Timestep 1
    // ****************************
    //Make sure no storms will occur
    for ( i = 0; i < 10; i++ )
    {
      p_oStormBehavior->SetStormProbability(i, 0);
    }
    //Don't let cleanup occur yet!
    for ( i = 0; i < p_oSimManager->GetNumberOfBehaviors(); i++ )
    {
      p_oSimManager->GetBehaviorObject( i )->Action();
    }

    //Check timestep 1 results - no packages
    for ( iX = 0; iX < iNumXCells; iX++ )
      for ( iY = 0; iY < iNumYCells; iY++ )
        EXPECT_EQ( NULL, p_oStormDamage->GetFirstPackageOfCell(iX, iY) );

    //Now cleanup
    for ( i = 0; i < p_oSimManager->GetNumberOfBehaviors(); i++ )
    {
      p_oSimManager->GetBehaviorObject( i )->TimestepCleanup();
    }

    // ****************************
    // Timestep 2
    // ****************************
    //Rig so 2 storms of severity 0.6-0.7 and 0.8-0.9 occurs
    for ( i = 0; i < 10; i++ )
    {
      p_oStormBehavior->SetStormProbability(i, 0);
    }
    p_oStormBehavior->SetStormProbability(6, 1);
    p_oStormBehavior->SetStormProbability(8, 1);

    //Don't let cleanup occur yet!
    for ( i = 0; i < p_oSimManager->GetNumberOfBehaviors(); i++ )
    {
      p_oSimManager->GetBehaviorObject( i )->Action();
    }

    //Check timestep 2 results - two packages
    //Mean of package 1
    fAvg = 0;
    for ( iX = 0; iX < iNumXCells; iX++ )
      for ( iY = 0; iY < iNumYCells; iY++ )
      {
        p_oPackage = p_oStormDamage->GetFirstPackageOfCell(iX, iY);
        ASSERT_TRUE(NULL != p_oPackage);
        p_oPackage->GetValue(iIndexCode, &fVal);
        EXPECT_TRUE( fVal >= 0.4 && fVal <= 1);
        fAvg += fVal;
      }
    fAvg /= (iNumXCells * iNumYCells);
    EXPECT_TRUE(fAvg >= 0.8 && fAvg <= 0.9);

    //Standard deviation of package 1
    fStdDev = 0;
    for ( iX = 0; iX < iNumXCells; iX++ )
      for ( iY = 0; iY < iNumYCells; iY++ )
      {
        p_oPackage = p_oStormDamage->GetFirstPackageOfCell(iX, iY);
        p_oPackage->GetValue(iIndexCode, &fVal);
        fStdDev += pow((fVal - fAvg), 2);
      }
    fStdDev /= (iNumXCells * iNumYCells);
    fStdDev = sqrt(fStdDev);
    EXPECT_LT(fStdDev, 0.15);

    //Mean of package 2
    fAvg = 0;
    for ( iX = 0; iX < iNumXCells; iX++ )
      for ( iY = 0; iY < iNumYCells; iY++ )
      {
        p_oPackage = p_oStormDamage->GetFirstPackageOfCell(iX, iY);
        p_oPackage = p_oPackage->GetNextPackage();
        ASSERT_TRUE(NULL != p_oPackage);
        EXPECT_EQ(NULL, p_oPackage->GetNextPackage());
        p_oPackage->GetValue(iIndexCode, &fVal);
        EXPECT_TRUE( fVal >= 0.3 && fVal <= 1);
        fAvg += fVal;
      }
    fAvg /= (iNumXCells * iNumYCells);
    EXPECT_TRUE(fAvg >= 0.6 && fAvg <= 0.7);

    //Standard deviation of package 2
    fStdDev = 0;
    for ( iX = 0; iX < iNumXCells; iX++ )
      for ( iY = 0; iY < iNumYCells; iY++ )
      {
        p_oPackage = p_oStormDamage->GetFirstPackageOfCell(iX, iY);
        p_oPackage = p_oPackage->GetNextPackage();
        p_oPackage->GetValue(iIndexCode, &fVal);
        fStdDev += pow((fVal - fAvg), 2);
      }
    fStdDev /= (iNumXCells * iNumYCells);
    fStdDev = sqrt(fStdDev);
    EXPECT_LT(fStdDev, 0.15);

    //Now cleanup
    for ( i = 0; i < p_oSimManager->GetNumberOfBehaviors(); i++ )
    {
      p_oSimManager->GetBehaviorObject( i )->TimestepCleanup();
    }

    // ****************************
    // Timestep 3
    // ****************************
    //Rig so 1 storm of severity 0.4 - 0.5 occurs
    for ( i = 0; i < 10; i++ )
    {
      p_oStormBehavior->SetStormProbability(i, 0);
    }
    p_oStormBehavior->SetStormProbability(4, 1);

    //Don't let cleanup occur yet!
    for ( i = 0; i < p_oSimManager->GetNumberOfBehaviors(); i++ )
    {
      p_oSimManager->GetBehaviorObject( i )->Action();
    }

    //Check timestep 3 results - all cells should be a mean of between 0.4 and 0.5
    //Mean of package 1
    fAvg = 0;
    for ( iX = 0; iX < iNumXCells; iX++ )
      for ( iY = 0; iY < iNumYCells; iY++ )
      {
        p_oPackage = p_oStormDamage->GetFirstPackageOfCell(iX, iY);
        ASSERT_TRUE(NULL != p_oPackage);
        p_oPackage->GetValue(iIndexCode, &fVal);
        EXPECT_TRUE( fVal >= 0.1 && fVal <= 0.8);
        fAvg += fVal;
      }
    fAvg /= (iNumXCells * iNumYCells);
    EXPECT_TRUE(fAvg >= 0.4 && fAvg <= 0.5);

    //Standard deviation of package 1
    fStdDev = 0;
    for ( iX = 0; iX < iNumXCells; iX++ )
      for ( iY = 0; iY < iNumYCells; iY++ )
      {
        p_oPackage = p_oStormDamage->GetFirstPackageOfCell(iX, iY);
        p_oPackage->GetValue(iIndexCode, &fVal);
        fStdDev += pow((fVal - fAvg), 2);
      }
    fStdDev /= (iNumXCells * iNumYCells);
    fStdDev = sqrt(fStdDev);
    EXPECT_LT(fStdDev, 0.15);

    //Now cleanup
    for ( i = 0; i < p_oSimManager->GetNumberOfBehaviors(); i++ ) {
      p_oSimManager->GetBehaviorObject( i )->TimestepCleanup();
    }
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestNormalMappedStochastic()
// Tests normal processing for a stochastic mapped damage pattern.
// WriteStormXMLFile4() does setup. Here's how it goes:
//
// -- "Storm Damage" Grid:   5 X 3 cells. Susceptibility map values are
// X/10 + Y/100.
// -- Timestep 1:  2 storms of severity 0.7-0.8 and 0.8-0.9. Cell values
// between (x/10+y/100)//1.5 and 1.
// -- Timestep 2:  1 storm of severity 0.3-0.4. Cell values between
// (x/10+y/100)//0.3 and (x/10+y/100)//0.4.
// -- Timestep 3:  No storms. All cell values = 0.
/////////////////////////////////////////////////////////////////////////////
TEST(Storm, TestNormalMappedStochastic) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clGrid * p_oStormDamage, //storm damage grid
    * p_oSusceptibility;
    clBehaviorBase * p_oTemp;
    clStorm * p_oStormBehavior;
    clPackage *p_oPackage;
    float fVal;
    int i, iX, iY, iNumXCells, iNumYCells, iIndexCode;

    //Load our parameter file
    p_oSimManager->ReadFile( WriteStormXMLFile4() );

    //Get the grid object and make sure it's set up correctly
    p_oStormDamage = p_oSimManager->GetGridObject( "Storm Damage" );
    ASSERT_TRUE( p_oStormDamage != NULL );
    iNumXCells = p_oStormDamage->GetNumberXCells();
    iNumYCells = p_oStormDamage->GetNumberYCells();
    EXPECT_EQ( 20, iNumXCells );
    EXPECT_EQ( 44, iNumYCells );
    iIndexCode = p_oStormDamage->GetPackageFloatDataCode( "1dmg_index" );
    ASSERT_TRUE( iIndexCode != -1 );

    p_oSusceptibility = p_oSimManager->GetGridObject( "Storm Susceptibility" );
    ASSERT_TRUE( p_oSusceptibility != NULL );
    iNumXCells = p_oSusceptibility->GetNumberXCells();
    iNumYCells = p_oSusceptibility->GetNumberYCells();
    EXPECT_EQ( 20, iNumXCells );
    EXPECT_EQ( 44, iNumYCells );

    //Make sure the storm probabilities were calculated correctly
    p_oTemp = p_oSimManager->GetBehaviorObject( "Storm" );
    ASSERT_TRUE( NULL != p_oTemp );
    p_oStormBehavior = dynamic_cast<clStorm *>(p_oTemp);

    // ****************************
    // Timestep 1
    // ****************************
    for ( i = 0; i < 10; i++ )
    {
      p_oStormBehavior->SetStormProbability(i, 0);
    }

    p_oSimManager->RunSim(1);

    //Check timestep 2 results - all cells should have means are between
    //(x/10+y/10)*1.5 and 1.
    for ( iX = 0; iX < iNumXCells; iX++ )
      for ( iY = 0; iY < iNumYCells; iY++ )
      {
        p_oPackage = p_oStormDamage->GetFirstPackageOfCell(iX, iY);
        ASSERT_TRUE(NULL != p_oPackage);
        p_oPackage->GetValue(iIndexCode, &fVal);
        EXPECT_TRUE( fVal >= 0 && fVal <= 1 );
        p_oPackage = p_oPackage->GetNextPackage();
        ASSERT_TRUE(NULL != p_oPackage);
        p_oPackage->GetValue(iIndexCode, &fVal);
        EXPECT_TRUE( fVal >= 0 && fVal <= 1 );
      }

    // ****************************
    // Timestep 2
    // ****************************
    p_oSimManager->RunSim(1);

    //Check timestep 2 results - all cell means between (x/10+y/10)*0.3
    //and (x/10+y/10)*0.4
    for ( iX = 0; iX < iNumXCells; iX++ )
      for ( iY = 0; iY < iNumYCells; iY++ )
      {
        p_oPackage = p_oStormDamage->GetFirstPackageOfCell(iX, iY);
        ASSERT_TRUE(NULL != p_oPackage);
        p_oPackage->GetValue(iIndexCode, &fVal);
        EXPECT_TRUE( fVal >= 0 && fVal <= 1 );
      }

    // ****************************
    // Timestep 3
    // ****************************
    p_oSimManager->RunSim(1);

    //Check timestep 3 results - all cells should be 0.
    for ( iX = 0; iX < iNumXCells; iX++ )
      for ( iY = 0; iY < iNumYCells; iY++ )
      {
        EXPECT_EQ(NULL, p_oStormDamage->GetFirstPackageOfCell(iX, iY));
      }

    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestMultiYearTimesteps()
// Tests multi-year timestep testing. WriteStormXMLFile5() does setup. Here's how
// it goes:
//
// -- Timestep length is 2 years.
// -- Default grid cell lengths.
// -- Timestep 1:  2 storm of severity 0.2-0.3. All cell values between
// 0.4 and 0.6. Time since last storm = 0.
// -- Timestep 2:  No storms. All cell values = 0. Time since last
// storm = 2.
// -- Timestep 3:  1 storm. Time since last storm = 0.
// -- Timestep 4:  No storms. All cell values = 0. Time since last
// hurricane = 2.
// -- Timestep 5:  No storms. All cell values = 0. Time since last
// hurricane = 4.
/////////////////////////////////////////////////////////////////////////////
TEST(Storm, TestMultiYearTimesteps)
{
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clGrid * p_oStormDamage; //storm damage grid
    clBehaviorBase * p_oTemp;
    clPackage *p_oPackage;
    clStorm * p_oStormBehavior;
    float fVal, fRefVal1, fRefVal2;
    int i, iX, iY, iNumXCells, iNumYCells, iIndexCode, iStormTimeCode;

    //Load our parameter file
    p_oSimManager->ReadFile( WriteStormXMLFile5() );

    //Get the grid object and make sure it's set up correctly
    p_oStormDamage = p_oSimManager->GetGridObject( "Storm Damage" );
    ASSERT_TRUE( p_oStormDamage != NULL );
    iNumXCells = p_oStormDamage->GetNumberXCells();
    iNumYCells = p_oStormDamage->GetNumberYCells();
    EXPECT_EQ( 13, iNumXCells );
    EXPECT_EQ( 17, iNumYCells );
    iIndexCode = p_oStormDamage->GetPackageFloatDataCode( "1dmg_index" );
    iStormTimeCode = p_oStormDamage->GetFloatDataCode( "stormtime");
    ASSERT_TRUE( iIndexCode != -1 );
    ASSERT_TRUE( iStormTimeCode != -1);

    //Make sure the storm probabilities were calculated correctly
    p_oTemp = p_oSimManager->GetBehaviorObject( "Storm" );
    ASSERT_TRUE( NULL != p_oTemp );
    p_oStormBehavior = dynamic_cast<clStorm *>(p_oTemp);
    EXPECT_LT( fabs(0.5 - p_oStormBehavior->GetStormProbability(0) ), 0.00001);
    EXPECT_LT( fabs(1 - p_oStormBehavior->GetStormProbability(1) ), 0.00001);
    EXPECT_LT( fabs(0.05 - p_oStormBehavior->GetStormProbability(2) ), 0.00001);
    EXPECT_LT( fabs(0.033333333 - p_oStormBehavior->GetStormProbability(3) ), 0.00001);
    EXPECT_LT( fabs(0.075757576 - p_oStormBehavior->GetStormProbability(4) ), 0.00001);
    EXPECT_LT( fabs(0.022222222 - p_oStormBehavior->GetStormProbability(5) ), 0.00001);
    EXPECT_LT( fabs(0.02 - p_oStormBehavior->GetStormProbability(6) ), 0.00001);
    EXPECT_LT( fabs(0.018181818 - p_oStormBehavior->GetStormProbability(7) ), 0.00001);
    EXPECT_LT( fabs(0.016666667 - p_oStormBehavior->GetStormProbability(8) ), 0.00001);
    EXPECT_LT( fabs(0.015384615 - p_oStormBehavior->GetStormProbability(9) ), 0.00001);

    // ****************************
    // Timestep 1
    // ****************************
    //Rig so 2 storms of severity 0.2-0.3. occurs
    for ( i = 0; i < 10; i++ )
    {
      p_oStormBehavior->SetStormProbability(i, 0);
    }
    p_oStormBehavior->SetStormProbability(2, 1);

    p_oSimManager->RunSim(1);

    //Check timestep 1 results - two packages
    p_oPackage = p_oStormDamage->GetFirstPackageOfCell(0, 0);
    ASSERT_TRUE(NULL != p_oPackage);
    p_oPackage->GetValue(iIndexCode, &fRefVal1);
    EXPECT_TRUE( fRefVal1 >= 0.2 && fRefVal1 <= 0.3);
    p_oPackage = p_oPackage->GetNextPackage();
    ASSERT_TRUE(NULL != p_oPackage);
    p_oPackage->GetValue(iIndexCode, &fRefVal2);
    EXPECT_TRUE( fRefVal2 >= 0.2 && fRefVal2 <= 0.3);
    for ( iX = 0; iX < iNumXCells; iX++ )
      for ( iY = 0; iY < iNumYCells; iY++ )
      {
        p_oPackage = p_oStormDamage->GetFirstPackageOfCell(iX, iY);
        ASSERT_TRUE(NULL != p_oPackage);
        p_oPackage->GetValue(iIndexCode, &fVal);
        EXPECT_LT(fabs(fVal - fRefVal1), 0.0001);
        p_oPackage = p_oPackage->GetNextPackage();
        ASSERT_TRUE(NULL != p_oPackage);
        EXPECT_EQ(NULL, p_oPackage->GetNextPackage());
        p_oPackage->GetValue(iIndexCode, &fVal);
        EXPECT_LT(fabs(fVal - fRefVal2), 0.0001);

        p_oStormDamage->GetValueOfCell( iX, iY, iStormTimeCode, & fVal );
        EXPECT_EQ( 0, fVal );
      }

    // ****************************
    // Timestep 2
    // ****************************
    //Rig so no storms occur
    for ( i = 0; i < 10; i++ )
    {
      p_oStormBehavior->SetStormProbability(i, 0);
    }

    p_oSimManager->RunSim( 1 );

    //Check timestep 2 results - all cells should be 0
    for ( iX = 0; iX < iNumXCells; iX++ )
      for ( iY = 0; iY < iNumYCells; iY++ )
      {
        EXPECT_EQ(NULL, p_oStormDamage->GetFirstPackageOfCell(iX, iY));
        p_oStormDamage->GetValueOfCell( iX, iY, iStormTimeCode, & fVal );
        EXPECT_EQ( 2, fVal );
      }

    // ****************************
    // Timestep 3
    // ****************************
    //2 storms of severity 0.2-0.3. occurs
    p_oSimManager->RunSim( 1 );

    //Check timestep 3 results - all cells should be between 0.4 and 0.6
    p_oPackage = p_oStormDamage->GetFirstPackageOfCell(0, 0);
    ASSERT_TRUE(NULL != p_oPackage);
    p_oPackage->GetValue(iIndexCode, &fRefVal1);
    EXPECT_TRUE( fRefVal1 >= 0.2 && fRefVal1 <= 0.3);
    p_oPackage = p_oPackage->GetNextPackage();
    ASSERT_TRUE(NULL != p_oPackage);
    p_oPackage->GetValue(iIndexCode, &fRefVal2);
    EXPECT_TRUE( fRefVal2 >= 0.2 && fRefVal2 <= 0.3);
    for ( iX = 0; iX < iNumXCells; iX++ )
      for ( iY = 0; iY < iNumYCells; iY++ )
      {
        p_oPackage = p_oStormDamage->GetFirstPackageOfCell(iX, iY);
        ASSERT_TRUE(NULL != p_oPackage);
        p_oPackage->GetValue(iIndexCode, &fVal);
        EXPECT_LT(fabs(fVal - fRefVal1), 0.0001);
        p_oPackage = p_oPackage->GetNextPackage();
        ASSERT_TRUE(NULL != p_oPackage);
        EXPECT_EQ(NULL, p_oPackage->GetNextPackage());
        p_oPackage->GetValue(iIndexCode, &fVal);
        EXPECT_LT(fabs(fVal - fRefVal2), 0.0001);

        p_oStormDamage->GetValueOfCell( iX, iY, iStormTimeCode, & fVal );
        EXPECT_EQ( 0, fVal );
      }

    // ****************************
    // Timestep 4
    // ****************************
    //No storms occur
    p_oSimManager->RunSim( 1 );

    //Check timestep 4 results - all cells should be 0
    for ( iX = 0; iX < iNumXCells; iX++ )
      for ( iY = 0; iY < iNumYCells; iY++ )
      {
        EXPECT_EQ(NULL, p_oStormDamage->GetFirstPackageOfCell(iX, iY));
        p_oStormDamage->GetValueOfCell( iX, iY, iStormTimeCode, & fVal );
        EXPECT_EQ( 2, fVal );
      }

    // ****************************
    // Timestep 5
    // ****************************
    //No storms occur
    p_oSimManager->RunSim( 1 );

    //Check timestep 5 results - all cells should be 0
    for ( iX = 0; iX < iNumXCells; iX++ )
      for ( iY = 0; iY < iNumYCells; iY++ )
      {
        EXPECT_EQ(NULL, p_oStormDamage->GetFirstPackageOfCell(iX, iY));
        p_oStormDamage->GetValueOfCell( iX, iY, iStormTimeCode, & fVal );
        EXPECT_EQ( 4, fVal );
      }

    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestErrorProcessing()
// Tests error processing. Tests:
//
// -- There are grid maps for both "Storm Damage" and "Storm Susceptibility"
// and the grid cell resolutions don't match.
// -- The damage pattern is set to "mapped" but there is no "Storm
// Susceptibility" grid map in the parameter file.
// -- The damage pattern is set to "mapped", there is a grid map for "Storm
// Susceptibility" in the parameter file, but not all values are between 0
// and 1.
// -- Not all storm interval return values are between 0 and 1.
// -- The value for storm damage pattern in the parameter file is not
// recognized.
// -- The damage pattern is "stochastic" and there is no value for
// probability distribution function.
// -- The damage pattern is "stochastic" and the value for probability
// distribution function is not recognized.
// -- The damage pattern is "stochastic", the probability distribution
// function is "normal" or "lognormal", and there is no value for standard
// deviation.
// -- The damage pattern is "stochastic", the probability distribution
// function is "negative_binomial", and there is no value for the clumping
// parameter.
////////////////////////////////////////////////////////////////////////////
TEST(Storm, TestErrorProcessing) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try
  {
    p_oSimManager->ReadFile(WriteStormXMLErrorFile1());
    FAIL() << "TestStorm error processing didn't catch error for WriteStormXMLErrorFile1.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clStorm::DoGridSetup") != 0)
    {
      FAIL() << "TestStorm error processing caught wrong error for WriteStormXMLErrorFile1.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteStormXMLErrorFile2());
    FAIL() << "TestStorm error processing didn't catch error for WriteStormXMLErrorFile2.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clStorm::DoGridSetup") != 0)
    {
      FAIL() << "TestStorm error processing caught wrong error for WriteStormXMLErrorFile2.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteStormXMLErrorFile3());
    FAIL() << "TestStorm error processing didn't catch error for WriteStormXMLErrorFile3.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clStorm::ReadParFile") != 0)
    {
      FAIL() << "TestStorm error processing caught wrong error for WriteStormXMLErrorFile3.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteStormXMLErrorFile4());
    FAIL() << "TestStorm error processing didn't catch error for WriteStormXMLErrorFile4.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clStorm::ReadParFile") != 0)
    {
      FAIL() << "TestStorm error processing caught wrong error for WriteStormXMLErrorFile4.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteStormXMLErrorFile5());
    FAIL() << "TestStorm error processing didn't catch error for WriteStormXMLErrorFile5.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.find("FillSingleValue") == std::string::npos)
    {
      FAIL() << "TestStorm error processing caught wrong error for WriteStormXMLErrorFile5.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteStormXMLErrorFile6());
    FAIL() << "TestStorm error processing didn't catch error for WriteStormXMLErrorFile6.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clStorm::ReadParFile") != 0)
    {
      FAIL() << "TestStorm error processing caught wrong error for WriteStormXMLErrorFile6.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteStormXMLErrorFile7());
    FAIL() << "TestStorm error processing didn't catch error for WriteStormXMLErrorFile7.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.find("FillSingleValue") == std::string::npos)
    {
      FAIL() << "TestStorm error processing caught wrong error for WriteStormXMLErrorFile7.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteStormXMLErrorFile8());
    FAIL() << "TestStorm error processing didn't catch error for WriteStormXMLErrorFile8.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clStorm::ReadParFile") != 0)
    {
      FAIL() << "TestStorm error processing caught wrong error for WriteStormXMLErrorFile8.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteStormXMLErrorFile9());
    FAIL() << "TestStorm error processing didn't catch error for WriteStormXMLErrorFile9.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clStorm::ReadParFile") != 0)
    {
      FAIL() << "TestStorm error processing caught wrong error for WriteStormXMLErrorFile9.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteStormXMLErrorFile10());
    FAIL() << "TestStorm error processing didn't catch error for WriteStormXMLErrorFile10.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clStorm::ReadParFile") != 0)
    {
      FAIL() << "TestStorm error processing caught wrong error for WriteStormXMLErrorFile10.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteStormXMLErrorFile11());
    FAIL() << "TestStorm error processing didn't catch error for WriteStormXMLErrorFile11.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clStorm::ReadParFile") != 0)
    {
      FAIL() << "TestStorm error processing caught wrong error for WriteStormXMLErrorFile11.";
    }
    ;
  }
  delete p_oSimManager;
}

/////////////////////////////////////////////////////////////////////////////
// WriteStormXMLFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteStormXMLFile1()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>15</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>";

  WriteStormCommonStuff( oOut );

  oOut << "<Storm1>"
       << "<st_s1ReturnInterval>2</st_s1ReturnInterval>"
       << "<st_s2ReturnInterval>1</st_s2ReturnInterval>"
       << "<st_s3ReturnInterval>20</st_s3ReturnInterval>"
       << "<st_s4ReturnInterval>1.00E+28</st_s4ReturnInterval>"
       << "<st_s5ReturnInterval>13.2</st_s5ReturnInterval>"
       << "<st_s6ReturnInterval>45</st_s6ReturnInterval>"
       << "<st_s7ReturnInterval>50</st_s7ReturnInterval>"
       << "<st_s8ReturnInterval>55</st_s8ReturnInterval>"
       << "<st_s9ReturnInterval>60</st_s9ReturnInterval>"
       << "<st_s10ReturnInterval>65</st_s10ReturnInterval>"
       << "<st_susceptibility>1</st_susceptibility>"
       << "<st_stochasticity>0</st_stochasticity>"
       << "<st_stmSSTPeriod>1</st_stmSSTPeriod>"
       << "<st_stmSineD>0</st_stmSineD>"
       << "<st_stmSineF>1</st_stmSineF>"
       << "<st_stmSineG>1</st_stmSineG>"
       << "<st_stmTrendSlopeM>0</st_stmTrendSlopeM>"
       << "<st_stmTrendInterceptI>1</st_stmTrendInterceptI>"
       << "<st_stmScheduledStorms>"
       << "<st_stmEvent min=\"0.6\" max=\"0.7\" yr=\"5\"/>"
       << "<st_stmEvent min=\"0.8\" max=\"0.9\" yr=\"5\"/>"
       << "<st_stmEvent min=\"0.4\" max=\"0.5\" yr=\"2\"/>"
       << "<st_stmEvent min=\"0.2\" max=\"0.3\" yr=\"3\"/>"
       << "<st_stmEvent min=\"0.5\" max=\"0.6\" yr=\"3\"/>"
       << "</st_stmScheduledStorms>"
       << "</Storm1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}



/////////////////////////////////////////////////////////////////////////////
// WriteStormXMLFile2()
/////////////////////////////////////////////////////////////////////////////
const char* WriteStormXMLFile2()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>10</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>";

  WriteStormCommonStuff( oOut );

  //Generate the storm susceptibility map
  oOut << "<grid gridName=\"Storm Susceptibility\">"
       << "<ma_floatCodes>"
       << "<ma_floatCode label=\"index\">0</ma_floatCode>"
       << "</ma_floatCodes>"
       << "<ma_lengthXCells>5</ma_lengthXCells>"
       << "<ma_lengthYCells>3</ma_lengthYCells>";

  //Auto-generate grid values
  int iNumX = 20, iNumY = 44, iX, iY;
  float fValue;
  for ( iX = 0; iX < iNumX; iX++ )
  {
    for ( iY = 0; iY < iNumY; iY++ )
    {
      fValue = ( ( float )iX / 10 ) + ( ( float )iY / 10 );
      oOut << "<ma_v x=\"" << iX << "\" y=\"" << iY << "\">"
           << "<fl c=\"0\">" << fValue << "</fl>" << "</ma_v>";
    }
  }
  oOut << "</grid>"
       << "<Storm1>"
       << "<st_s1ReturnInterval>0.1</st_s1ReturnInterval>"
       << "<st_s2ReturnInterval>0.2</st_s2ReturnInterval>"
       << "<st_s3ReturnInterval>0.3</st_s3ReturnInterval>"
       << "<st_s4ReturnInterval>0.4</st_s4ReturnInterval>"
       << "<st_s5ReturnInterval>0.5</st_s5ReturnInterval>"
       << "<st_s6ReturnInterval>0.6</st_s6ReturnInterval>"
       << "<st_s7ReturnInterval>0.7</st_s7ReturnInterval>"
       << "<st_s8ReturnInterval>0.8</st_s8ReturnInterval>"
       << "<st_s9ReturnInterval>0.9</st_s9ReturnInterval>"
       << "<st_s10ReturnInterval>1</st_s10ReturnInterval>"
       << "<st_susceptibility>0</st_susceptibility>"
       << "<st_stochasticity>0</st_stochasticity>"
       << "<st_stmSSTPeriod>1</st_stmSSTPeriod>"
       << "<st_stmSineD>0</st_stmSineD>"
       << "<st_stmSineF>1</st_stmSineF>"
       << "<st_stmSineG>1</st_stmSineG>"
       << "<st_stmTrendSlopeM>0</st_stmTrendSlopeM>"
       << "<st_stmTrendInterceptI>1</st_stmTrendInterceptI>"
       << "<st_stmScheduledStorms>"
       << "<st_stmEvent min=\"0.1\" max=\"0.2\" yr=\"1\"/>"
       << "<st_stmEvent min=\"0.0\" max=\"0.1\" yr=\"2\"/>"
       << "<st_stmEvent min=\"0.1\" max=\"0.2\" yr=\"2\"/>"
       << "<st_stmEvent min=\"0.2\" max=\"0.3\" yr=\"2\"/>"
       << "<st_stmEvent min=\"0.6\" max=\"0.7\" yr=\"4\"/>"
       << "<st_stmEvent min=\"0.9\" max=\"1.0\" yr=\"4\"/>"
       << "</st_stmScheduledStorms>"
       << "</Storm1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteStormXMLFile3()
/////////////////////////////////////////////////////////////////////////////
const char* WriteStormXMLFile3()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>3</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>3</randomSeed>";

  WriteStormCommonStuff( oOut );

  //Generate the storm susceptibility map
  oOut << "<grid gridName=\"Storm Damage\">"
       << "<ma_floatCodes>"
       << "<ma_floatCode label=\"1dmg_index\">0</ma_floatCode>"
       << "<ma_floatCode label=\"stormtime\">1</ma_floatCode>"
       << "<ma_floatCode label=\"dmg_index\">2</ma_floatCode>"
       << "</ma_floatCodes>"
       << "<ma_lengthXCells>10</ma_lengthXCells>"
       << "<ma_lengthYCells>10</ma_lengthYCells>"
       << "</grid>"
       << "<Storm1>"
       << "<st_s1ReturnInterval>0.1</st_s1ReturnInterval>"
       << "<st_s2ReturnInterval>0.2</st_s2ReturnInterval>"
       << "<st_s3ReturnInterval>0.3</st_s3ReturnInterval>"
       << "<st_s4ReturnInterval>0.4</st_s4ReturnInterval>"
       << "<st_s5ReturnInterval>0.5</st_s5ReturnInterval>"
       << "<st_s6ReturnInterval>0.6</st_s6ReturnInterval>"
       << "<st_s7ReturnInterval>0.7</st_s7ReturnInterval>"
       << "<st_s8ReturnInterval>0.8</st_s8ReturnInterval>"
       << "<st_s9ReturnInterval>0.9</st_s9ReturnInterval>"
       << "<st_s10ReturnInterval>1</st_s10ReturnInterval>"
       << "<st_susceptibility>1</st_susceptibility>"
       << "<st_stochasticity>1</st_stochasticity>"
       << "<st_probFunction>1</st_probFunction>"
       << "<st_standardDeviation>0.1</st_standardDeviation>"
       << "<st_stmSSTPeriod>1</st_stmSSTPeriod>"
       << "<st_stmSineD>0</st_stmSineD>"
       << "<st_stmSineF>1</st_stmSineF>"
       << "<st_stmSineG>1</st_stmSineG>"
       << "<st_stmTrendSlopeM>0</st_stmTrendSlopeM>"
       << "<st_stmTrendInterceptI>1</st_stmTrendInterceptI>"
       << "<st_stmScheduledStorms>"
       << "<st_stmEvent min=\"0.6\" max=\"0.7\" yr=\"2\"/>"
       << "<st_stmEvent min=\"0.8\" max=\"0.9\" yr=\"2\"/>"
       << "<st_stmEvent min=\"0.4\" max=\"0.5\" yr=\"3\"/>"
       << "</st_stmScheduledStorms>"
       << "</Storm1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteStormXMLFile4()
/////////////////////////////////////////////////////////////////////////////
const char* WriteStormXMLFile4()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>4</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>";

  WriteStormCommonStuff( oOut );

  //Generate the storm susceptibility map
  oOut << "<grid gridName=\"Storm Susceptibility\">"
       << "<ma_floatCodes>"
       << "<ma_floatCode label=\"index\">0</ma_floatCode>"
       << "</ma_floatCodes>"
       << "<ma_lengthXCells>5</ma_lengthXCells>"
       << "<ma_lengthYCells>3</ma_lengthYCells>";

  //Auto-generate grid values
  int iNumX = 20, iNumY = 44, iX, iY;
  float fValue;
  for ( iX = 0; iX < iNumX; iX++ )
  {
    for ( iY = 0; iY < iNumY; iY++ )
    {
      fValue = ( ( float )iX / 10 ) + ( ( float )iY / 10 );
      if (fValue > 1) fValue = 1;
      oOut << "<ma_v x=\"" << iX << "\" y=\"" << iY << "\">"
      << "<fl c=\"0\">" << fValue << "</fl>" << "</ma_v>";
    }
  }
  oOut << "</grid>"
       << "<Storm1>"
       << "<st_s1ReturnInterval>0.1</st_s1ReturnInterval>"
       << "<st_s2ReturnInterval>0.2</st_s2ReturnInterval>"
       << "<st_s3ReturnInterval>0.3</st_s3ReturnInterval>"
       << "<st_s4ReturnInterval>0.4</st_s4ReturnInterval>"
       << "<st_s5ReturnInterval>0.5</st_s5ReturnInterval>"
       << "<st_s6ReturnInterval>0.6</st_s6ReturnInterval>"
       << "<st_s7ReturnInterval>0.7</st_s7ReturnInterval>"
       << "<st_s8ReturnInterval>0.8</st_s8ReturnInterval>"
       << "<st_s9ReturnInterval>0.9</st_s9ReturnInterval>"
       << "<st_s10ReturnInterval>1</st_s10ReturnInterval>"
       << "<st_susceptibility>0</st_susceptibility>"
       << "<st_stochasticity>1</st_stochasticity>"
       << "<st_probFunction>1</st_probFunction>"
       << "<st_standardDeviation>0.1</st_standardDeviation>"
       << "<st_stmSSTPeriod>1</st_stmSSTPeriod>"
       << "<st_stmSineD>0</st_stmSineD>"
       << "<st_stmSineF>1</st_stmSineF>"
       << "<st_stmSineG>1</st_stmSineG>"
       << "<st_stmTrendSlopeM>0</st_stmTrendSlopeM>"
       << "<st_stmTrendInterceptI>1</st_stmTrendInterceptI>"
       << "<st_stmScheduledStorms>"
       << "<st_stmEvent min=\"0.7\" max=\"0.8\" yr=\"1\"/>"
       << "<st_stmEvent min=\"0.8\" max=\"0.9\" yr=\"1\"/>"
       << "<st_stmEvent min=\"0.3\" max=\"0.4\" yr=\"2\"/>"
       << "</st_stmScheduledStorms>"
       << "</Storm1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteStormXMLFile5()
/////////////////////////////////////////////////////////////////////////////
const char* WriteStormXMLFile5()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>9</timesteps>"
       << "<yearsPerTimestep>2</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>";

  WriteStormCommonStuff( oOut );

  oOut << "<Storm1>"
       << "<st_s1ReturnInterval>2</st_s1ReturnInterval>"
       << "<st_s2ReturnInterval>1</st_s2ReturnInterval>"
       << "<st_s3ReturnInterval>20</st_s3ReturnInterval>"
       << "<st_s4ReturnInterval>30</st_s4ReturnInterval>"
       << "<st_s5ReturnInterval>13.2</st_s5ReturnInterval>"
       << "<st_s6ReturnInterval>45</st_s6ReturnInterval>"
       << "<st_s7ReturnInterval>50</st_s7ReturnInterval>"
       << "<st_s8ReturnInterval>55</st_s8ReturnInterval>"
       << "<st_s9ReturnInterval>60</st_s9ReturnInterval>"
       << "<st_s10ReturnInterval>65</st_s10ReturnInterval>"
       << "<st_susceptibility>1</st_susceptibility>"
       << "<st_stochasticity>0</st_stochasticity>"
       << "<st_stmSSTPeriod>1</st_stmSSTPeriod>"
       << "<st_stmSineD>0</st_stmSineD>"
       << "<st_stmSineF>1</st_stmSineF>"
       << "<st_stmSineG>1</st_stmSineG>"
       << "<st_stmTrendSlopeM>0</st_stmTrendSlopeM>"
       << "<st_stmTrendInterceptI>1</st_stmTrendInterceptI>"
       << "<st_stmScheduledStorms>"
       << "<st_stmEvent min=\"0.2\" max=\"0.3\" yr=\"6\"/>"
       << "<st_stmEvent min=\"0.2\" max=\"0.3\" yr=\"5\"/>"
       << "</st_stmScheduledStorms>"
       << "</Storm1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteStormCommonStuff()
/////////////////////////////////////////////////////////////////////////////
void WriteStormCommonStuff( std::fstream &oOut )
{
  using namespace std;
  oOut << "<plot_lenX>100</plot_lenX>"
       << "<plot_lenY>130</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>"
       << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\"/>"
       << "</tr_speciesList>"
       << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
       << "<tr_minAdultDBH>"
       << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
       << "</tr_minAdultDBH>"
       << "<tr_maxSeedlingHeight>"
       << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
       << "</tr_maxSeedlingHeight>"
       << "</trees>"
       << "<allometry>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_stdMaxCrownRad>"
       << "<tr_smcrVal species=\"Species_1\">10</tr_smcrVal>"
       << "</tr_stdMaxCrownRad>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
       << "<tr_whatSeedlingHeightDiam>"
       << "<tr_wsehdVal species=\"Species_1\">0</tr_wsehdVal>"
       << "</tr_whatSeedlingHeightDiam>"
       << "<tr_whatSaplingHeightDiam>"
       << "<tr_wsahdVal species=\"Species_1\">0</tr_wsahdVal>"
       << "</tr_whatSaplingHeightDiam>"
       << "<tr_whatAdultHeightDiam>"
       << "<tr_wahdVal species=\"Species_1\">0</tr_wahdVal>"
       << "</tr_whatAdultHeightDiam>"
       << "<tr_whatAdultCrownRadDiam>"
       << "<tr_wacrdVal species=\"Species_1\">0</tr_wacrdVal>"
       << "</tr_whatAdultCrownRadDiam>"
       << "<tr_whatAdultCrownHeightHeight>"
       << "<tr_wachhVal species=\"Species_1\">0</tr_wachhVal>"
       << "</tr_whatAdultCrownHeightHeight>"
       << "<tr_whatSaplingCrownRadDiam>"
       << "<tr_wscrdVal species=\"Species_1\">0</tr_wscrdVal>"
       << "</tr_whatSaplingCrownRadDiam>"
       << "<tr_whatSaplingCrownHeightHeight>"
       << "<tr_wschhVal species=\"Species_1\">0</tr_wschhVal>"
       << "</tr_whatSaplingCrownHeightHeight>"
       << "</allometry>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>Storm</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "</behaviorList>";
}

/////////////////////////////////////////////////////////////////////////////
// WriteStormXMLErrorFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteStormXMLErrorFile1()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>4</timesteps>"
       << "<yearsPerTimestep>7</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>";

  WriteStormCommonStuff( oOut );

  //Generate the storm susceptibility map
  oOut << "<grid gridName=\"Storm Susceptibility\">"
       << "<ma_floatCodes>"
       << "<ma_floatCode label=\"index\">0</ma_floatCode>"
       << "</ma_floatCodes>"
       << "<ma_lengthXCells>5</ma_lengthXCells>"
       << "<ma_lengthYCells>3</ma_lengthYCells>";

  //Auto-generate grid values
  int iNumX = 20, iNumY = 44, iX, iY;
  float fValue;
  for ( iX = 0; iX < iNumX; iX++ )
  {
    for ( iY = 0; iY < iNumY; iY++ )
    {
      fValue = 0.5;
      oOut << "<ma_v x=\"" << iX << "\" y=\"" << iY << "\">"
      << "<fl c=\"0\">" << fValue << "</fl>" << "</ma_v>";
    }
  }
  oOut << "</grid>"
       << "<grid gridName=\"Storm Damage\">"
       << "<ma_floatCodes>"
       << "<ma_floatCode label=\"1dmg_index\">0</ma_floatCode>"
       << "<ma_floatCode label=\"stormtime\">1</ma_floatCode>"
       << "<ma_floatCode label=\"dmg_index\">2</ma_floatCode>"
       << "</ma_floatCodes>"
       << "<ma_lengthXCells>10</ma_lengthXCells>"
       << "<ma_lengthYCells>10</ma_lengthYCells>"
       << "</grid>"
       << "<Storm1>"
       << "<st_s1ReturnInterval>0.1</st_s1ReturnInterval>"
       << "<st_s2ReturnInterval>0.2</st_s2ReturnInterval>"
       << "<st_s3ReturnInterval>0.3</st_s3ReturnInterval>"
       << "<st_s4ReturnInterval>0.4</st_s4ReturnInterval>"
       << "<st_s5ReturnInterval>0.5</st_s5ReturnInterval>"
       << "<st_s6ReturnInterval>0.6</st_s6ReturnInterval>"
       << "<st_s7ReturnInterval>0.7</st_s7ReturnInterval>"
       << "<st_s8ReturnInterval>0.8</st_s8ReturnInterval>"
       << "<st_s9ReturnInterval>0.9</st_s9ReturnInterval>"
       << "<st_s10ReturnInterval>1</st_s10ReturnInterval>"
       << "<st_susceptibility>0</st_susceptibility>"
       << "<st_stochasticity>0</st_stochasticity>"
       << "<st_stmSSTPeriod>1</st_stmSSTPeriod>"
       << "<st_stmSineD>0</st_stmSineD>"
       << "<st_stmSineF>1</st_stmSineF>"
       << "<st_stmSineG>1</st_stmSineG>"
       << "<st_stmTrendSlopeM>0</st_stmTrendSlopeM>"
       << "<st_stmTrendInterceptI>1</st_stmTrendInterceptI>"
       << "</Storm1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteStormXMLErrorFile2()
/////////////////////////////////////////////////////////////////////////////
const char* WriteStormXMLErrorFile2()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>5</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>";

  WriteStormCommonStuff( oOut );

  oOut << "<Storm1>"
       << "<st_s1ReturnInterval>0.1</st_s1ReturnInterval>"
       << "<st_s2ReturnInterval>0.2</st_s2ReturnInterval>"
       << "<st_s3ReturnInterval>0.3</st_s3ReturnInterval>"
       << "<st_s4ReturnInterval>0.4</st_s4ReturnInterval>"
       << "<st_s5ReturnInterval>0.5</st_s5ReturnInterval>"
       << "<st_s6ReturnInterval>0.6</st_s6ReturnInterval>"
       << "<st_s7ReturnInterval>0.7</st_s7ReturnInterval>"
       << "<st_s8ReturnInterval>0.8</st_s8ReturnInterval>"
       << "<st_s9ReturnInterval>0.9</st_s9ReturnInterval>"
       << "<st_s10ReturnInterval>1</st_s10ReturnInterval>"
       << "<st_susceptibility>0</st_susceptibility>"
       << "<st_stochasticity>0</st_stochasticity>"
       << "<st_stmSSTPeriod>1</st_stmSSTPeriod>"
       << "<st_stmSineD>0</st_stmSineD>"
       << "<st_stmSineF>1</st_stmSineF>"
       << "<st_stmSineG>1</st_stmSineG>"
       << "<st_stmTrendSlopeM>0</st_stmTrendSlopeM>"
       << "<st_stmTrendInterceptI>1</st_stmTrendInterceptI>"
       << "</Storm1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteStormXMLErrorFile3()
/////////////////////////////////////////////////////////////////////////////
const char* WriteStormXMLErrorFile3()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>5</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>";

  WriteStormCommonStuff( oOut );

  oOut << "<Storm1>"
       << "<st_s1ReturnInterval>0.1</st_s1ReturnInterval>"
       << "<st_s2ReturnInterval>0.2</st_s2ReturnInterval>"
       << "<st_s3ReturnInterval>0.3</st_s3ReturnInterval>"
       << "<st_s4ReturnInterval>0.4</st_s4ReturnInterval>"
       << "<st_s5ReturnInterval>-0.5</st_s5ReturnInterval>"
       << "<st_s6ReturnInterval>0.6</st_s6ReturnInterval>"
       << "<st_s7ReturnInterval>0.7</st_s7ReturnInterval>"
       << "<st_s8ReturnInterval>0.8</st_s8ReturnInterval>"
       << "<st_s9ReturnInterval>0.9</st_s9ReturnInterval>"
       << "<st_s10ReturnInterval>1</st_s10ReturnInterval>"
       << "<st_susceptibility>1</st_susceptibility>"
       << "<st_stochasticity>0</st_stochasticity>"
       << "<st_stmSSTPeriod>1</st_stmSSTPeriod>"
       << "<st_stmSineD>0</st_stmSineD>"
       << "<st_stmSineF>1</st_stmSineF>"
       << "<st_stmSineG>1</st_stmSineG>"
       << "<st_stmTrendSlopeM>0</st_stmTrendSlopeM>"
       << "<st_stmTrendInterceptI>1</st_stmTrendInterceptI>"
       << "</Storm1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteStormXMLErrorFile4()
/////////////////////////////////////////////////////////////////////////////
const char* WriteStormXMLErrorFile4()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>5</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>";

  WriteStormCommonStuff( oOut );

  oOut << "<Storm1>"
       << "<st_s1ReturnInterval>0.1</st_s1ReturnInterval>"
       << "<st_s2ReturnInterval>0.2</st_s2ReturnInterval>"
       << "<st_s3ReturnInterval>0.3</st_s3ReturnInterval>"
       << "<st_s4ReturnInterval>0.4</st_s4ReturnInterval>"
       << "<st_s5ReturnInterval>0.5</st_s5ReturnInterval>"
       << "<st_s6ReturnInterval>0.6</st_s6ReturnInterval>"
       << "<st_s7ReturnInterval>0.7</st_s7ReturnInterval>"
       << "<st_s8ReturnInterval>0.8</st_s8ReturnInterval>"
       << "<st_s9ReturnInterval>0.9</st_s9ReturnInterval>"
       << "<st_s10ReturnInterval>1</st_s10ReturnInterval>"
       << "<st_susceptibility>3</st_susceptibility>"
       << "<st_stochasticity>0</st_stochasticity>"
       << "<st_stmSSTPeriod>1</st_stmSSTPeriod>"
       << "<st_stmSineD>0</st_stmSineD>"
       << "<st_stmSineF>1</st_stmSineF>"
       << "<st_stmSineG>1</st_stmSineG>"
       << "<st_stmTrendSlopeM>0</st_stmTrendSlopeM>"
       << "<st_stmTrendInterceptI>1</st_stmTrendInterceptI>"
       << "</Storm1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}


/////////////////////////////////////////////////////////////////////////////
// WriteStormXMLErrorFile5()
/////////////////////////////////////////////////////////////////////////////
const char* WriteStormXMLErrorFile5()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>5</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>";

  WriteStormCommonStuff( oOut );

  oOut << "<Storm1>"
       << "<st_s1ReturnInterval>0.1</st_s1ReturnInterval>"
       << "<st_s2ReturnInterval>0.2</st_s2ReturnInterval>"
       << "<st_s3ReturnInterval>0.3</st_s3ReturnInterval>"
       << "<st_s4ReturnInterval>0.4</st_s4ReturnInterval>"
       << "<st_s5ReturnInterval>0.5</st_s5ReturnInterval>"
       << "<st_s6ReturnInterval>0.6</st_s6ReturnInterval>"
       << "<st_s7ReturnInterval>0.7</st_s7ReturnInterval>"
       << "<st_s8ReturnInterval>0.8</st_s8ReturnInterval>"
       << "<st_s9ReturnInterval>0.9</st_s9ReturnInterval>"
       << "<st_s10ReturnInterval>1</st_s10ReturnInterval>"
       << "<st_susceptibility>1</st_susceptibility>"
       << "<st_stochasticity>1</st_stochasticity>"
       << "</Storm1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteStormXMLErrorFile6()
/////////////////////////////////////////////////////////////////////////////
const char* WriteStormXMLErrorFile6()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>3</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>";

  WriteStormCommonStuff( oOut );

  oOut << "<grid gridName=\"Storm Damage\">"
       << "<ma_floatCodes>"
       << "<ma_floatCode label=\"1dmg_index\">0</ma_floatCode>"
       << "<ma_floatCode label=\"stormtime\">1</ma_floatCode>"
       << "<ma_floatCode label=\"dmg_index\">2</ma_floatCode>"
       << "</ma_floatCodes>"
       << "<ma_lengthXCells>10</ma_lengthXCells>"
       << "<ma_lengthYCells>10</ma_lengthYCells>"
       << "</grid>"
       << "<Storm1>"
       << "<st_s1ReturnInterval>0.1</st_s1ReturnInterval>"
       << "<st_s2ReturnInterval>0.2</st_s2ReturnInterval>"
       << "<st_s3ReturnInterval>0.3</st_s3ReturnInterval>"
       << "<st_s4ReturnInterval>0.4</st_s4ReturnInterval>"
       << "<st_s5ReturnInterval>0.5</st_s5ReturnInterval>"
       << "<st_s6ReturnInterval>0.6</st_s6ReturnInterval>"
       << "<st_s7ReturnInterval>0.7</st_s7ReturnInterval>"
       << "<st_s8ReturnInterval>0.8</st_s8ReturnInterval>"
       << "<st_s9ReturnInterval>0.9</st_s9ReturnInterval>"
       << "<st_s10ReturnInterval>1</st_s10ReturnInterval>"
       << "<st_susceptibility>1</st_susceptibility>"
       << "<st_stochasticity>1</st_stochasticity>"
       << "<st_probFunction>9</st_probFunction>"
       << "<st_stmSSTPeriod>1</st_stmSSTPeriod>"
       << "<st_stmSineD>0</st_stmSineD>"
       << "<st_stmSineF>1</st_stmSineF>"
       << "<st_stmSineG>1</st_stmSineG>"
       << "<st_stmTrendSlopeM>0</st_stmTrendSlopeM>"
       << "<st_stmTrendInterceptI>1</st_stmTrendInterceptI>"
       << "</Storm1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteStormXMLErrorFile7()
/////////////////////////////////////////////////////////////////////////////
const char* WriteStormXMLErrorFile7()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>3</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>";

  WriteStormCommonStuff( oOut );

  oOut << "<grid gridName=\"Storm Damage\">"
       << "<ma_floatCodes>"
       << "<ma_floatCode label=\"1dmg_index\">0</ma_floatCode>"
       << "<ma_floatCode label=\"stormtime\">1</ma_floatCode>"
       << "<ma_floatCode label=\"dmg_index\">2</ma_floatCode>"
       << "</ma_floatCodes>"
       << "<ma_lengthXCells>10</ma_lengthXCells>"
       << "<ma_lengthYCells>10</ma_lengthYCells>"
       << "</grid>"
       << "<Storm1>"
       << "<st_s1ReturnInterval>0.1</st_s1ReturnInterval>"
       << "<st_s2ReturnInterval>0.2</st_s2ReturnInterval>"
       << "<st_s3ReturnInterval>0.3</st_s3ReturnInterval>"
       << "<st_s4ReturnInterval>0.4</st_s4ReturnInterval>"
       << "<st_s5ReturnInterval>0.5</st_s5ReturnInterval>"
       << "<st_s6ReturnInterval>0.6</st_s6ReturnInterval>"
       << "<st_s7ReturnInterval>0.7</st_s7ReturnInterval>"
       << "<st_s8ReturnInterval>0.8</st_s8ReturnInterval>"
       << "<st_s9ReturnInterval>0.9</st_s9ReturnInterval>"
       << "<st_s10ReturnInterval>1</st_s10ReturnInterval>"
       << "<st_susceptibility>1</st_susceptibility>"
       << "<st_stochasticity>1</st_stochasticity>"
       << "<st_stmSSTPeriod>1</st_stmSSTPeriod>"
       << "<st_stmSineD>0</st_stmSineD>"
       << "<st_stmSineF>1</st_stmSineF>"
       << "<st_stmSineG>1</st_stmSineG>"
       << "<st_stmTrendSlopeM>0</st_stmTrendSlopeM>"
       << "<st_stmTrendInterceptI>1</st_stmTrendInterceptI>"
       << "<st_probFunction>1</st_probFunction>"
       << "</Storm1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteStormXMLErrorFile8()
/////////////////////////////////////////////////////////////////////////////
const char* WriteStormXMLErrorFile8()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>3</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>";

  WriteStormCommonStuff( oOut );

  oOut << "<grid gridName=\"Storm Damage\">"
       << "<ma_floatCodes>"
       << "<ma_floatCode label=\"1dmg_index\">0</ma_floatCode>"
       << "<ma_floatCode label=\"stormtime\">1</ma_floatCode>"
       << "<ma_floatCode label=\"dmg_index\">2</ma_floatCode>"
       << "</ma_floatCodes>"
       << "<ma_lengthXCells>10</ma_lengthXCells>"
       << "<ma_lengthYCells>10</ma_lengthYCells>"
       << "</grid>"
       << "<Storm1>"
       << "<st_s1ReturnInterval>0.1</st_s1ReturnInterval>"
       << "<st_s2ReturnInterval>0.2</st_s2ReturnInterval>"
       << "<st_s3ReturnInterval>0.3</st_s3ReturnInterval>"
       << "<st_s4ReturnInterval>0.4</st_s4ReturnInterval>"
       << "<st_s5ReturnInterval>0.5</st_s5ReturnInterval>"
       << "<st_s6ReturnInterval>0.6</st_s6ReturnInterval>"
       << "<st_s7ReturnInterval>0.7</st_s7ReturnInterval>"
       << "<st_s8ReturnInterval>0.8</st_s8ReturnInterval>"
       << "<st_s9ReturnInterval>0.9</st_s9ReturnInterval>"
       << "<st_s10ReturnInterval>1</st_s10ReturnInterval>"
       << "<st_susceptibility>1</st_susceptibility>"
       << "<st_stochasticity>3</st_stochasticity>"
       << "<st_stmSSTPeriod>1</st_stmSSTPeriod>"
       << "<st_stmSineD>0</st_stmSineD>"
       << "<st_stmSineF>1</st_stmSineF>"
       << "<st_stmSineG>1</st_stmSineG>"
       << "<st_stmTrendSlopeM>0</st_stmTrendSlopeM>"
       << "<st_stmTrendInterceptI>1</st_stmTrendInterceptI>"
       << "<st_probFunction>2</st_probFunction>"
       << "</Storm1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteStormXMLErrorFile9()
/////////////////////////////////////////////////////////////////////////////
const char* WriteStormXMLErrorFile9()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>5</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>";

  WriteStormCommonStuff( oOut );

  oOut << "<Storm1>"
       << "<st_s1ReturnInterval>0.1</st_s1ReturnInterval>"
       << "<st_s2ReturnInterval>0.2</st_s2ReturnInterval>"
       << "<st_s3ReturnInterval>0.3</st_s3ReturnInterval>"
       << "<st_s4ReturnInterval>0.4</st_s4ReturnInterval>"
       << "<st_s5ReturnInterval>0.5</st_s5ReturnInterval>"
       << "<st_s6ReturnInterval>0.6</st_s6ReturnInterval>"
       << "<st_s7ReturnInterval>0.7</st_s7ReturnInterval>"
       << "<st_s8ReturnInterval>0.8</st_s8ReturnInterval>"
       << "<st_s9ReturnInterval>0.9</st_s9ReturnInterval>"
       << "<st_s10ReturnInterval>1</st_s10ReturnInterval>"
       << "<st_susceptibility>1</st_susceptibility>"
       << "<st_stochasticity>0</st_stochasticity>"
       << "<st_stmSSTPeriod>1</st_stmSSTPeriod>"
       << "<st_stmSineD>0</st_stmSineD>"
       << "<st_stmSineF>1</st_stmSineF>"
       << "<st_stmSineG>1</st_stmSineG>"
       << "<st_stmTrendSlopeM>0</st_stmTrendSlopeM>"
       << "<st_stmTrendInterceptI>1</st_stmTrendInterceptI>"
       << "<st_stmScheduledStorms>"
       << "<st_stmEvent min=\"0.6\" max=\"0.4\" yr=\"5\"/>"
       << "<st_stmEvent min=\"0.8\" max=\"0.9\" yr=\"5\"/>"
       << "<st_stmEvent min=\"0.4\" max=\"0.5\" yr=\"2\"/>"
       << "<st_stmEvent min=\"0.2\" max=\"0.3\" yr=\"3\"/>"
       << "<st_stmEvent min=\"0.5\" max=\"0.6\" yr=\"3\"/>"
       << "</st_stmScheduledStorms>"
       << "</Storm1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteStormXMLErrorFile10()
/////////////////////////////////////////////////////////////////////////////
const char* WriteStormXMLErrorFile10()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>5</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>";

  WriteStormCommonStuff( oOut );

  oOut << "<Storm1>"
       << "<st_s1ReturnInterval>0.1</st_s1ReturnInterval>"
       << "<st_s2ReturnInterval>0.2</st_s2ReturnInterval>"
       << "<st_s3ReturnInterval>0.3</st_s3ReturnInterval>"
       << "<st_s4ReturnInterval>0.4</st_s4ReturnInterval>"
       << "<st_s5ReturnInterval>0.5</st_s5ReturnInterval>"
       << "<st_s6ReturnInterval>0.6</st_s6ReturnInterval>"
       << "<st_s7ReturnInterval>0.7</st_s7ReturnInterval>"
       << "<st_s8ReturnInterval>0.8</st_s8ReturnInterval>"
       << "<st_s9ReturnInterval>0.9</st_s9ReturnInterval>"
       << "<st_s10ReturnInterval>1</st_s10ReturnInterval>"
       << "<st_susceptibility>1</st_susceptibility>"
       << "<st_stochasticity>0</st_stochasticity>"
       << "<st_stmSSTPeriod>1</st_stmSSTPeriod>"
       << "<st_stmSineD>0</st_stmSineD>"
       << "<st_stmSineF>1</st_stmSineF>"
       << "<st_stmSineG>1</st_stmSineG>"
       << "<st_stmTrendSlopeM>0</st_stmTrendSlopeM>"
       << "<st_stmTrendInterceptI>1</st_stmTrendInterceptI>"
       << "<st_stmScheduledStorms>"
       << "<st_stmEvent min=\"-0.8\" max=\"0.9\" yr=\"5\"/>"
       << "<st_stmEvent min=\"0.4\" max=\"0.5\" yr=\"2\"/>"
       << "<st_stmEvent min=\"0.2\" max=\"0.3\" yr=\"3\"/>"
       << "<st_stmEvent min=\"0.5\" max=\"0.6\" yr=\"3\"/>"
       << "</st_stmScheduledStorms>"
       << "</Storm1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteStormXMLErrorFile11()
/////////////////////////////////////////////////////////////////////////////
const char* WriteStormXMLErrorFile11()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>5</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>";

  WriteStormCommonStuff( oOut );

  oOut << "<Storm1>"
       << "<st_s1ReturnInterval>0.1</st_s1ReturnInterval>"
       << "<st_s2ReturnInterval>0.2</st_s2ReturnInterval>"
       << "<st_s3ReturnInterval>0.3</st_s3ReturnInterval>"
       << "<st_s4ReturnInterval>0.4</st_s4ReturnInterval>"
       << "<st_s5ReturnInterval>0.5</st_s5ReturnInterval>"
       << "<st_s6ReturnInterval>0.6</st_s6ReturnInterval>"
       << "<st_s7ReturnInterval>0.7</st_s7ReturnInterval>"
       << "<st_s8ReturnInterval>0.8</st_s8ReturnInterval>"
       << "<st_s9ReturnInterval>0.9</st_s9ReturnInterval>"
       << "<st_s10ReturnInterval>1</st_s10ReturnInterval>"
       << "<st_susceptibility>1</st_susceptibility>"
       << "<st_stochasticity>0</st_stochasticity>"
       << "<st_stmSSTPeriod>1</st_stmSSTPeriod>"
       << "<st_stmSineD>0</st_stmSineD>"
       << "<st_stmSineF>1</st_stmSineF>"
       << "<st_stmSineG>1</st_stmSineG>"
       << "<st_stmTrendSlopeM>0</st_stmTrendSlopeM>"
       << "<st_stmTrendInterceptI>1</st_stmTrendInterceptI>"
       << "<st_stmScheduledStorms>"
       << "<st_stmEvent min=\"0.8\" max=\"1.9\" yr=\"5\"/>"
       << "<st_stmEvent min=\"0.4\" max=\"0.5\" yr=\"2\"/>"
       << "<st_stmEvent min=\"0.2\" max=\"0.3\" yr=\"3\"/>"
       << "<st_stmEvent min=\"0.5\" max=\"0.6\" yr=\"3\"/>"
       << "</st_stmScheduledStorms>"
       << "</Storm1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}
