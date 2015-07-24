//---------------------------------------------------------------------------
// TestAbsoluteGrowth.cpp
//---------------------------------------------------------------------------
#include "TestAbsoluteGrowth.h"
#include <fstream>
#include <math.h>
#include "TreePopulation.h"
#include "SimManager.h"
#include "BehaviorBase.h"
#include <gtest/gtest.h>

////////////////////////////////////////////////////////////////////////////
// Test1YearPerTimestep()
////////////////////////////////////////////////////////////////////////////
TEST(AbsoluteGrowth, Test1YearPerTimestep) {

  clSimManager *p_oSimManager = new clSimManager(7, 1, "");
  try {
    clTreePopulation * p_oPop;
    clTree *p_oTree1, *p_oTree2, *p_oTree3, *p_oTree4, *p_oTree5, *p_oTree6,
    *p_oTree7, *p_oTree8, *p_oTree9, *p_oTree10;
    float fDiam, fHeight, fExpectedDiam, fExpectedHeight, fLight, fGrowth, fExpectedGrowth;

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteAbsoluteGrowthXMLFile1(1) );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create our ten trees and set diameter, height, and GLI for each
    //Sapling, Species 1
    fDiam = 6.4064;
    fHeight = 10;
    fLight = 80;
    p_oTree1 = p_oPop->CreateTree(1, 1, 0, clTreePopulation::sapling, fDiam);
    p_oTree1->SetValue(p_oPop->GetHeightCode(p_oTree1->GetSpecies(), p_oTree1->GetType()), fHeight, false, false);
    p_oTree1->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree1->GetSpecies(), p_oTree1->GetType()), fLight, false, false);

    //Adult, Species 1
    fDiam = 35;
    fHeight = 20;
    fLight = 80;
    p_oTree2 = p_oPop->CreateTree(2, 2, 0, clTreePopulation::adult, fDiam);
    p_oTree2->SetValue(p_oPop->GetHeightCode(p_oTree2->GetSpecies(), p_oTree2->GetType()), fHeight, false, false);
    p_oTree2->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree2->GetSpecies(), p_oTree2->GetType()), fLight, false, false);

    //Adult, Species 1
    fDiam = 24;
    fHeight = 20;
    fLight = 15;
    p_oTree3 = p_oPop->CreateTree(3, 3, 0, clTreePopulation::adult, fDiam);
    p_oTree3->SetValue(p_oPop->GetHeightCode(p_oTree3->GetSpecies(), p_oTree3->GetType()), fHeight, false, false);
    p_oTree3->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree3->GetSpecies(), p_oTree3->GetType()), fLight, false, false);

    //Adult, Species 2
    fDiam = 80;
    fHeight = 36;
    fLight = 95;
    p_oTree4 = p_oPop->CreateTree(4, 4, 1, clTreePopulation::adult, fDiam);
    p_oTree4->SetValue(p_oPop->GetHeightCode(p_oTree4->GetSpecies(), p_oTree4->GetType()), fHeight, false, false);
    p_oTree4->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree4->GetSpecies(), p_oTree4->GetType()), fLight, false, false);

    //Adult, Species 2
    fDiam = 11;
    fHeight = 15;
    fLight = 5;
    p_oTree5 = p_oPop->CreateTree(5, 5, 1, clTreePopulation::adult, fDiam);
    p_oTree5->SetValue(p_oPop->GetHeightCode(p_oTree5->GetSpecies(), p_oTree5->GetType()), fHeight, false, false);
    p_oTree5->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree5->GetSpecies(), p_oTree5->GetType()), fLight, false, false);

    //Sapling, Species 2
    fDiam = 4.7552;
    fHeight = 10;
    fLight = 80;
    p_oTree6 = p_oPop->CreateTree(6, 6, 1, clTreePopulation::sapling, fDiam);
    p_oTree6->SetValue(p_oPop->GetHeightCode(p_oTree6->GetSpecies(), p_oTree6->GetType()), fHeight, false, false);
    p_oTree6->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree6->GetSpecies(), p_oTree6->GetType()), fLight, false, false);

    //Sapling, Species 3
    fDiam = 6.3531;
    fHeight = 9.5;
    fLight = 80;
    p_oTree7 = p_oPop->CreateTree(7, 7, 2, clTreePopulation::sapling, fDiam);
    p_oTree7->SetValue(p_oPop->GetHeightCode(p_oTree7->GetSpecies(), p_oTree7->GetType()), fHeight, false, false);
    p_oTree7->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree7->GetSpecies(), p_oTree7->GetType()), fLight, false, false);

    //Sapling, Species 3
    fDiam = 4.9413;
    fHeight = 8;
    fLight = 30;
    p_oTree8 = p_oPop->CreateTree(8, 8, 2, clTreePopulation::sapling, fDiam);
    p_oTree8->SetValue(p_oPop->GetHeightCode(p_oTree8->GetSpecies(), p_oTree8->GetType()), fHeight, false, false);
    p_oTree8->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree8->GetSpecies(), p_oTree8->GetType()), fLight, false, false);

    //Adult, Species 3
    fDiam = 80;
    fHeight = 36;
    fLight = 95;
    p_oTree9 = p_oPop->CreateTree(9, 9, 2, clTreePopulation::adult, fDiam);
    p_oTree9->SetValue(p_oPop->GetHeightCode(p_oTree9->GetSpecies(), p_oTree9->GetType()), fHeight, false, false);
    p_oTree9->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree9->GetSpecies(), p_oTree9->GetType()), fLight, false, false);

    //Adult, Species 3
    fDiam = 11;
    fHeight = 15;
    fLight = 5;
    p_oTree10 = p_oPop->CreateTree(10, 10, 2, clTreePopulation::adult, fDiam);
    p_oTree10->SetValue(p_oPop->GetHeightCode(p_oTree10->GetSpecies(), p_oTree10->GetType()), fHeight, false, false);
    p_oTree10->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree10->GetSpecies(), p_oTree10->GetType()), fLight, false, false);

    //Now run growth, but skip light
    int i;
    for (i = 1; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
      clBehaviorBase *p_oBase = p_oSimManager->GetBehaviorObject(i);
      p_oBase->Action();
    }

    //Confirm all trees
    //Sapling, Species 1
    fExpectedDiam = 8.622442496;
    fExpectedHeight = 8.462663176;
    fExpectedGrowth = 3.11221248;
    p_oTree1->GetValue(p_oPop->GetDiam10Code(p_oTree1->GetSpecies(), p_oTree1->GetType()), &fDiam);
    p_oTree1->GetValue(p_oPop->GetHeightCode(p_oTree1->GetSpecies(), p_oTree1->GetType()), &fHeight);
    p_oTree1->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree1->GetSpecies(), p_oTree1->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Adult, Species 1
    fExpectedDiam = 35.236;
    fExpectedHeight = 26.18424284;
    fExpectedGrowth = 1.18;
    p_oTree2->GetValue(p_oPop->GetDbhCode(p_oTree2->GetSpecies(), p_oTree2->GetType()), &fDiam);
    p_oTree2->GetValue(p_oPop->GetHeightCode(p_oTree2->GetSpecies(), p_oTree2->GetType()), &fHeight);
    p_oTree2->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree2->GetSpecies(), p_oTree2->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Adult, Species 1
    fExpectedDiam = 24.17684316;
    fExpectedHeight = 20.97365283;
    fExpectedGrowth = 0.8842158;
    p_oTree3->GetValue(p_oPop->GetDbhCode(p_oTree3->GetSpecies(), p_oTree3->GetType()), &fDiam);
    p_oTree3->GetValue(p_oPop->GetHeightCode(p_oTree3->GetSpecies(), p_oTree3->GetType()), &fHeight);
    p_oTree3->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree3->GetSpecies(), p_oTree3->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Adult, Species 2
    fExpectedDiam = 80.25;
    fExpectedHeight = 34.01905688;
    fExpectedGrowth = 10;
    p_oTree4->GetValue(p_oPop->GetDbhCode(p_oTree4->GetSpecies(), p_oTree4->GetType()), &fDiam);
    p_oTree4->GetValue(p_oPop->GetHeightCode(p_oTree4->GetSpecies(), p_oTree4->GetType()), &fHeight);
    p_oTree4->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree4->GetSpecies(), p_oTree4->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Adult, Species 2
    fExpectedDiam = 11.04318396;
    fExpectedHeight = 10.27380874;
    fExpectedGrowth = 0.215919775;
    p_oTree5->GetValue(p_oPop->GetDbhCode(p_oTree5->GetSpecies(), p_oTree5->GetType()), &fDiam);
    p_oTree5->GetValue(p_oPop->GetHeightCode(p_oTree5->GetSpecies(), p_oTree5->GetType()), &fHeight);
    p_oTree5->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree5->GetSpecies(), p_oTree5->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Sapling, Species 2
    fExpectedDiam = 8.467941597;
    fExpectedHeight = 10.22751607;
    fExpectedGrowth = 2.339707986;
    p_oTree6->GetValue(p_oPop->GetDiam10Code(p_oTree6->GetSpecies(), p_oTree6->GetType()), &fDiam);
    p_oTree6->GetValue(p_oPop->GetHeightCode(p_oTree6->GetSpecies(), p_oTree6->GetType()), &fHeight);
    p_oTree6->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree6->GetSpecies(), p_oTree6->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Sapling, Species 3
    fExpectedDiam = 9.184;
    fExpectedHeight = 9.625948988;
    fExpectedGrowth = 0.92;
    p_oTree7->GetValue(p_oPop->GetDiam10Code(p_oTree7->GetSpecies(), p_oTree7->GetType()), &fDiam);
    p_oTree7->GetValue(p_oPop->GetHeightCode(p_oTree7->GetSpecies(), p_oTree7->GetType()), &fHeight);
    p_oTree7->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree7->GetSpecies(), p_oTree7->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Sapling, Species 3
    fExpectedDiam = 7.136287907;
    fExpectedHeight = 8.096861666;
    fExpectedGrowth = 0.681439537;
    p_oTree8->GetValue(p_oPop->GetDiam10Code(p_oTree8->GetSpecies(), p_oTree8->GetType()), &fDiam);
    p_oTree8->GetValue(p_oPop->GetHeightCode(p_oTree8->GetSpecies(), p_oTree8->GetType()), &fHeight);
    p_oTree8->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree8->GetSpecies(), p_oTree8->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Adult, Species 3
    fExpectedDiam = 80.375;
    fExpectedHeight = 36.05224874;
    fExpectedGrowth = 10;
    p_oTree9->GetValue(p_oPop->GetDbhCode(p_oTree9->GetSpecies(), p_oTree9->GetType()), &fDiam);
    p_oTree9->GetValue(p_oPop->GetHeightCode(p_oTree9->GetSpecies(), p_oTree9->GetType()), &fHeight);
    p_oTree9->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree9->GetSpecies(), p_oTree9->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Adult, Species 3
    fExpectedDiam = 11.02306351;
    fExpectedHeight = 15.01981949;
    fExpectedGrowth = 0.115317568;
    p_oTree10->GetValue(p_oPop->GetDbhCode(p_oTree10->GetSpecies(), p_oTree10->GetType()), &fDiam);
    p_oTree10->GetValue(p_oPop->GetHeightCode(p_oTree10->GetSpecies(), p_oTree10->GetType()), &fHeight);
    p_oTree10->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree10->GetSpecies(), p_oTree10->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// Test3YearsPerTimestep()
////////////////////////////////////////////////////////////////////////////
TEST(AbsoluteGrowth, Test3YearsPerTimestep) {

  clSimManager *p_oSimManager = new clSimManager(7, 1, "");
  try {
    clTreePopulation * p_oPop;
    clTree *p_oTree1, *p_oTree2, *p_oTree3, *p_oTree4, *p_oTree5, *p_oTree6,
    *p_oTree7, *p_oTree8, *p_oTree9, *p_oTree10;
    float fDiam, fHeight, fExpectedDiam, fExpectedHeight, fLight, fGrowth, fExpectedGrowth;

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteAbsoluteGrowthXMLFile1(3) );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create our six trees and set diameter, height, and GLI for each
    //Sapling, Species 1
    fDiam = 6.4064;
    fHeight = 10;
    fLight = 80;
    p_oTree1 = p_oPop->CreateTree(1, 1, 0, clTreePopulation::sapling, fDiam);
    p_oTree1->SetValue(p_oPop->GetHeightCode(p_oTree1->GetSpecies(), p_oTree1->GetType()), fHeight, false, false);
    p_oTree1->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree1->GetSpecies(), p_oTree1->GetType()), fLight, false, false);

    //Adult, Species 1
    fDiam = 35;
    fHeight = 20;
    fLight = 80;
    p_oTree2 = p_oPop->CreateTree(2, 2, 0, clTreePopulation::adult, fDiam);
    p_oTree2->SetValue(p_oPop->GetHeightCode(p_oTree2->GetSpecies(), p_oTree2->GetType()), fHeight, false, false);
    p_oTree2->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree2->GetSpecies(), p_oTree2->GetType()), fLight, false, false);

    //Adult, Species 1
    fDiam = 24;
    fHeight = 20;
    fLight = 15;
    p_oTree3 = p_oPop->CreateTree(3, 3, 0, clTreePopulation::adult, fDiam);
    p_oTree3->SetValue(p_oPop->GetHeightCode(p_oTree3->GetSpecies(), p_oTree3->GetType()), fHeight, false, false);
    p_oTree3->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree3->GetSpecies(), p_oTree3->GetType()), fLight, false, false);

    //Adult, Species 2
    fDiam = 80;
    fHeight = 36;
    fLight = 95;
    p_oTree4 = p_oPop->CreateTree(4, 4, 1, clTreePopulation::adult, fDiam);
    p_oTree4->SetValue(p_oPop->GetHeightCode(p_oTree4->GetSpecies(), p_oTree4->GetType()), fHeight, false, false);
    p_oTree4->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree4->GetSpecies(), p_oTree4->GetType()), fLight, false, false);

    //Adult, Species 2
    fDiam = 11;
    fHeight = 15;
    fLight = 5;
    p_oTree5 = p_oPop->CreateTree(5, 5, 1, clTreePopulation::adult, fDiam);
    p_oTree5->SetValue(p_oPop->GetHeightCode(p_oTree5->GetSpecies(), p_oTree5->GetType()), fHeight, false, false);
    p_oTree5->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree5->GetSpecies(), p_oTree5->GetType()), fLight, false, false);

    //Sapling, Species 2
    fDiam = 4.7552;
    fHeight = 10;
    fLight = 80;
    p_oTree6 = p_oPop->CreateTree(6, 6, 1, clTreePopulation::sapling, fDiam);
    p_oTree6->SetValue(p_oPop->GetHeightCode(p_oTree6->GetSpecies(), p_oTree6->GetType()), fHeight, false, false);
    p_oTree6->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree6->GetSpecies(), p_oTree6->GetType()), fLight, false, false);

    //Sapling, Species 3
    fDiam = 6.3531;
    fHeight = 9.5;
    fLight = 80;
    p_oTree7 = p_oPop->CreateTree(7, 7, 2, clTreePopulation::sapling, fDiam);
    p_oTree7->SetValue(p_oPop->GetHeightCode(p_oTree7->GetSpecies(), p_oTree7->GetType()), fHeight, false, false);
    p_oTree7->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree7->GetSpecies(), p_oTree7->GetType()), fLight, false, false);

    //Sapling, Species 3
    fDiam = 4.9413;
    fHeight = 8;
    fLight = 30;
    p_oTree8 = p_oPop->CreateTree(8, 8, 2, clTreePopulation::sapling, fDiam);
    p_oTree8->SetValue(p_oPop->GetHeightCode(p_oTree8->GetSpecies(), p_oTree8->GetType()), fHeight, false, false);
    p_oTree8->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree8->GetSpecies(), p_oTree8->GetType()), fLight, false, false);

    //Adult, Species 3
    fDiam = 80;
    fHeight = 36;
    fLight = 95;
    p_oTree9 = p_oPop->CreateTree(9, 9, 2, clTreePopulation::adult, fDiam);
    p_oTree9->SetValue(p_oPop->GetHeightCode(p_oTree9->GetSpecies(), p_oTree9->GetType()), fHeight, false, false);
    p_oTree9->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree9->GetSpecies(), p_oTree9->GetType()), fLight, false, false);

    //Adult, Species 3
    fDiam = 11;
    fHeight = 15;
    fLight = 5;
    p_oTree10 = p_oPop->CreateTree(10, 10, 2, clTreePopulation::adult, fDiam);
    p_oTree10->SetValue(p_oPop->GetHeightCode(p_oTree10->GetSpecies(), p_oTree10->GetType()), fHeight, false, false);
    p_oTree10->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree10->GetSpecies(), p_oTree10->GetType()), fLight, false, false);

    //Now run growth, but skip light
    int i;
    for (i = 1; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
      clBehaviorBase *p_oBase = p_oSimManager->GetBehaviorObject(i);
      p_oBase->Action();
    }

    //Confirm all trees
    //Sapling, Species 1
    fExpectedDiam = 9.867327488;
    fExpectedHeight = 9.373566878;
    fExpectedGrowth = 3.11221248;
    p_oTree1->GetValue(p_oPop->GetDiam10Code(p_oTree1->GetSpecies(), p_oTree1->GetType()), &fDiam);
    p_oTree1->GetValue(p_oPop->GetHeightCode(p_oTree1->GetSpecies(), p_oTree1->GetType()), &fHeight);
    p_oTree1->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree1->GetSpecies(), p_oTree1->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Adult, Species 1
    fExpectedDiam = 35.708;
    fExpectedHeight = 26.37056534;
    fExpectedGrowth = 1.18;
    p_oTree2->GetValue(p_oPop->GetDbhCode(p_oTree2->GetSpecies(), p_oTree2->GetType()), &fDiam);
    p_oTree2->GetValue(p_oPop->GetHeightCode(p_oTree2->GetSpecies(), p_oTree2->GetType()), &fHeight);
    p_oTree2->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree2->GetSpecies(), p_oTree2->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Adult, Species 1
    fExpectedDiam = 24.53052948;
    fExpectedHeight = 21.16833035;
    fExpectedGrowth = 0.8842158;
    p_oTree3->GetValue(p_oPop->GetDbhCode(p_oTree3->GetSpecies(), p_oTree3->GetType()), &fDiam);
    p_oTree3->GetValue(p_oPop->GetHeightCode(p_oTree3->GetSpecies(), p_oTree3->GetType()), &fHeight);
    p_oTree3->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree3->GetSpecies(), p_oTree3->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Adult, Species 2
    fExpectedDiam = 80.75;
    fExpectedHeight = 34.08518502;
    fExpectedGrowth = 10;
    p_oTree4->GetValue(p_oPop->GetDbhCode(p_oTree4->GetSpecies(), p_oTree4->GetType()), &fDiam);
    p_oTree4->GetValue(p_oPop->GetHeightCode(p_oTree4->GetSpecies(), p_oTree4->GetType()), &fHeight);
    p_oTree4->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree4->GetSpecies(), p_oTree4->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Adult, Species 2
    fExpectedDiam = 11.12955187;
    fExpectedHeight = 10.33466199;
    fExpectedGrowth = 0.215919775;
    p_oTree5->GetValue(p_oPop->GetDbhCode(p_oTree5->GetSpecies(), p_oTree5->GetType()), &fDiam);
    p_oTree5->GetValue(p_oPop->GetHeightCode(p_oTree5->GetSpecies(), p_oTree5->GetType()), &fHeight);
    p_oTree5->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree5->GetSpecies(), p_oTree5->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Sapling, Species 2
    fExpectedDiam = 9.403824791;
    fExpectedHeight = 10.67799836;
    fExpectedGrowth = 2.339707986;
    p_oTree6->GetValue(p_oPop->GetDiam10Code(p_oTree6->GetSpecies(), p_oTree6->GetType()), &fDiam);
    p_oTree6->GetValue(p_oPop->GetHeightCode(p_oTree6->GetSpecies(), p_oTree6->GetType()), &fHeight);
    p_oTree6->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree6->GetSpecies(), p_oTree6->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Sapling, Species 3
    fExpectedDiam = 9.552;
    fExpectedHeight = 9.876559908;
    fExpectedGrowth = 0.92;
    p_oTree7->GetValue(p_oPop->GetDiam10Code(p_oTree7->GetSpecies(), p_oTree7->GetType()), &fDiam);
    p_oTree7->GetValue(p_oPop->GetHeightCode(p_oTree7->GetSpecies(), p_oTree7->GetType()), &fHeight);
    p_oTree7->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree7->GetSpecies(), p_oTree7->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Sapling, Species 3
    fExpectedDiam = 7.408863722;
    fExpectedHeight = 8.289851305;
    fExpectedGrowth = 0.681439537;
    p_oTree8->GetValue(p_oPop->GetDiam10Code(p_oTree8->GetSpecies(), p_oTree8->GetType()), &fDiam);
    p_oTree8->GetValue(p_oPop->GetHeightCode(p_oTree8->GetSpecies(), p_oTree8->GetType()), &fHeight);
    p_oTree8->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree8->GetSpecies(), p_oTree8->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Adult, Species 3
    fExpectedDiam = 81.125;
    fExpectedHeight = 36.15521294;
    fExpectedGrowth = 10;
    p_oTree9->GetValue(p_oPop->GetDbhCode(p_oTree9->GetSpecies(), p_oTree9->GetType()), &fDiam);
    p_oTree9->GetValue(p_oPop->GetHeightCode(p_oTree9->GetSpecies(), p_oTree9->GetType()), &fHeight);
    p_oTree9->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree9->GetSpecies(), p_oTree9->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Adult, Species 3
    fExpectedDiam = 11.06919054;
    fExpectedHeight = 15.05942241;
    fExpectedGrowth = 0.115317568;
    p_oTree10->GetValue(p_oPop->GetDbhCode(p_oTree10->GetSpecies(), p_oTree10->GetType()), &fDiam);
    p_oTree10->GetValue(p_oPop->GetHeightCode(p_oTree10->GetSpecies(), p_oTree10->GetType()), &fHeight);
    p_oTree10->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree10->GetSpecies(), p_oTree10->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);
    delete p_oSimManager;
  } catch (modelErr &e) {
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// WriteXMLFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteAbsoluteGrowthXMLFile1(int iYrsPerTimestep) {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //Write file
  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"07010101\">"
      << "<plot>"
      << "<timesteps>3</timesteps>"
      << "<yearsPerTimestep>" << iYrsPerTimestep << "</yearsPerTimestep>"
      << "<randomSeed>1</randomSeed>"
      << "<plot_lenX>200.0</plot_lenX>"
      << "<plot_lenY>200.0</plot_lenY>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12</plot_temp_C>"
      << "<plot_latitude>55.37</plot_latitude>"
      << "</plot>"
      << "<trees>"
      << "<tr_speciesList>"
      << "<tr_species speciesName=\"Species_1\" />"
      << "<tr_species speciesName=\"Species_2\" />"
      << "<tr_species speciesName=\"Species_3\" />"
      << "</tr_speciesList>"
      << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
      << "<tr_minAdultDBH>"
      << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
      << "<tr_madVal species=\"Species_2\">10.0</tr_madVal>"
      << "<tr_madVal species=\"Species_3\">10.0</tr_madVal>"
      << "</tr_minAdultDBH>"
      << "<tr_maxSeedlingHeight>"
      << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Species_2\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Species_3\">1.35</tr_mshVal>"
      << "</tr_maxSeedlingHeight>"
      << "</trees>"
      << "<allometry>"
      << "<tr_canopyHeight>"
      << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
      << "<tr_chVal species=\"Species_2\">39.54</tr_chVal>"
      << "<tr_chVal species=\"Species_3\">45.0</tr_chVal>"
      << "</tr_canopyHeight>"
      << "<tr_whatAdultCrownRadDiam>"
      << "<tr_wacrdVal species=\"Species_1\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Species_2\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Species_3\">0</tr_wacrdVal>"
      << "</tr_whatAdultCrownRadDiam>"
      << "<tr_whatAdultCrownHeightHeight>"
      << "<tr_wachhVal species=\"Species_1\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Species_2\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Species_3\">0</tr_wachhVal>"
      << "</tr_whatAdultCrownHeightHeight>"
      << "<tr_whatSaplingCrownRadDiam>"
      << "<tr_wscrdVal species=\"Species_1\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Species_2\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Species_3\">0</tr_wscrdVal>"
      << "</tr_whatSaplingCrownRadDiam>"
      << "<tr_whatSaplingCrownHeightHeight>"
      << "<tr_wschhVal species=\"Species_1\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Species_2\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Species_3\">0</tr_wschhVal>"
      << "</tr_whatSaplingCrownHeightHeight>"
      << "<tr_stdAsympCrownRad>"
      << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_2\">0.0614</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_3\">0.0242</tr_sacrVal>"
      << "</tr_stdAsympCrownRad>"
      << "<tr_stdCrownRadExp>"
      << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_3\">1.0</tr_screVal>"
      << "</tr_stdCrownRadExp>"
      << "<tr_conversionDiam10ToDBH>"
      << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_2\">0.5944</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_3\">0.7059</tr_cdtdVal>"
      << "</tr_conversionDiam10ToDBH>"
      << "<tr_interceptDiam10ToDBH>"
      << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_3\">0</tr_idtdVal>"
      << "</tr_interceptDiam10ToDBH>"
      << "<tr_stdAsympCrownHt>"
      << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
      << "<tr_sachVal species=\"Species_2\">0.368</tr_sachVal>"
      << "<tr_sachVal species=\"Species_3\">0.464</tr_sachVal>"
      << "</tr_stdAsympCrownHt>"
      << "<tr_stdCrownHtExp>"
      << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_3\">1.0</tr_scheVal>"
      << "</tr_stdCrownHtExp>"
      << "<tr_slopeOfHeight-Diam10>"
      << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_2\">0.0269</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_3\">0.02871</tr_sohdVal>"
      << "</tr_slopeOfHeight-Diam10>"
      << "<tr_slopeOfAsymHeight>"
      << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
      << "<tr_soahVal species=\"Species_2\">0.0241</tr_soahVal>"
      << "<tr_soahVal species=\"Species_3\">0.0263</tr_soahVal>"
      << "</tr_slopeOfAsymHeight>"
      << "<tr_whatSeedlingHeightDiam>"
      << "<tr_wsehdVal species=\"Species_1\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_2\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_3\">0</tr_wsehdVal>"
      << "</tr_whatSeedlingHeightDiam>"
      << "<tr_whatSaplingHeightDiam>"
      << "<tr_wsahdVal species=\"Species_1\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_2\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_3\">0</tr_wsahdVal>"
      << "</tr_whatSaplingHeightDiam>"
      << "<tr_whatAdultHeightDiam>"
      << "<tr_wahdVal species=\"Species_1\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_2\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_3\">0</tr_wahdVal>"
      << "</tr_whatAdultHeightDiam>"
      << "<tr_whatAdultCrownRadDiam>"
      << "<tr_wacrdVal species=\"Species_1\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Species_2\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Species_3\">0</tr_wacrdVal>"
      << "</tr_whatAdultCrownRadDiam>"
      << "<tr_whatAdultCrownHeightHeight>"
      << "<tr_wachhVal species=\"Species_1\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Species_2\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Species_3\">0</tr_wachhVal>"
      << "</tr_whatAdultCrownHeightHeight>"
      << "<tr_whatSaplingCrownRadDiam>"
      << "<tr_wscrdVal species=\"Species_1\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Species_2\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Species_3\">0</tr_wscrdVal>"
      << "</tr_whatSaplingCrownRadDiam>"
      << "<tr_whatSaplingCrownHeightHeight>"
      << "<tr_wschhVal species=\"Species_1\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Species_2\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Species_3\">0</tr_wschhVal>"
      << "</tr_whatSaplingCrownHeightHeight>"
      << "</allometry>"
      << "<behaviorList>"
      << "<behavior>"
      //Leave in one light so that "Light" will be registerd
      << "<behaviorName>ConstantGLI</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>AbsUnlimGrowth</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>AbsRadialGrowth</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>3</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>AbsBAGrowth</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>4</listPosition>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>AbsUnlimGrowth diam only</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>5</listPosition>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>AbsRadialGrowth diam only</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>6</listPosition>"
      << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>AbsBAGrowth diam only</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>7</listPosition>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>HeightIncrementer</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>8</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
      << "</behavior>"
      << "</behaviorList>"
      << "<ConstantGLI1>"
      << "<li_constGLI>100</li_constGLI>"
      << "</ConstantGLI1>"
      << "<AbsUnlimGrowth2>"
      << "<gr_asympDiameterGrowth>"
      << "<gr_adgVal species=\"Species_1\">0.858</gr_adgVal>"
      << "</gr_asympDiameterGrowth>"
      << "<gr_slopeGrowthResponse>"
      << "<gr_sgrVal species=\"Species_1\">0.027</gr_sgrVal>"
      << "</gr_slopeGrowthResponse>"
      << "<gr_lengthLastSuppFactor>"
      << "<gr_llsfVal species=\"Species_1\">0.0</gr_llsfVal>"
      << "</gr_lengthLastSuppFactor>"
      << "<gr_lengthCurrReleaseFactor>"
      << "<gr_lcrfVal species=\"Species_1\">0.0</gr_lcrfVal>"
      << "</gr_lengthCurrReleaseFactor>"
      << "<gr_yrsExceedThresholdBeforeSupp>6</gr_yrsExceedThresholdBeforeSupp>"
      << "<gr_mortRateAtSuppression>0.1</gr_mortRateAtSuppression>"
      << "</AbsUnlimGrowth2>"
      << "<AbsRadialGrowth3>"
      << "<gr_adultConstRadialInc>"
      << "<gr_acriVal species=\"Species_1\">1.18</gr_acriVal>"
      << "</gr_adultConstRadialInc>"
      << "<gr_asympDiameterGrowth>"
      << "<gr_adgVal species=\"Species_1\">0.858</gr_adgVal>"
      << "</gr_asympDiameterGrowth>"
      << "<gr_slopeGrowthResponse>"
      << "<gr_sgrVal species=\"Species_1\">0.027</gr_sgrVal>"
      << "</gr_slopeGrowthResponse>"
      << "<gr_lengthLastSuppFactor>"
      << "<gr_llsfVal species=\"Species_1\">0.0</gr_llsfVal>"
      << "</gr_lengthLastSuppFactor>"
      << "<gr_lengthCurrReleaseFactor>"
      << "<gr_lcrfVal species=\"Species_1\">0.0</gr_lcrfVal>"
      << "</gr_lengthCurrReleaseFactor>"
      << "<gr_yrsExceedThresholdBeforeSupp>6</gr_yrsExceedThresholdBeforeSupp>"
      << "<gr_mortRateAtSuppression>0.1</gr_mortRateAtSuppression>"
      << "</AbsRadialGrowth3>"
      << "<AbsBAGrowth4>"
      << "<gr_adultConstAreaInc>"
      << "<gr_acaiVal species=\"Species_2\">0.2</gr_acaiVal>"
      << "</gr_adultConstAreaInc>"
      << "<gr_asympDiameterGrowth>"
      << "<gr_adgVal species=\"Species_2\">0.799</gr_adgVal>"
      << "</gr_asympDiameterGrowth>"
      << "<gr_slopeGrowthResponse>"
      << "<gr_sgrVal species=\"Species_2\">0.019</gr_sgrVal>"
      << "</gr_slopeGrowthResponse>"
      << "<gr_lengthLastSuppFactor>"
      << "<gr_llsfVal species=\"Species_2\">0.0</gr_llsfVal>"
      << "</gr_lengthLastSuppFactor>"
      << "<gr_lengthCurrReleaseFactor>"
      << "<gr_lcrfVal species=\"Species_2\">0.0</gr_lcrfVal>"
      << "</gr_lengthCurrReleaseFactor>"
      << "<gr_yrsExceedThresholdBeforeSupp>6</gr_yrsExceedThresholdBeforeSupp>"
      << "<gr_mortRateAtSuppression>0.1</gr_mortRateAtSuppression>"
      << "</AbsBAGrowth4>"
      << "<AbsUnlimGrowth5>"
      << "<gr_asympDiameterGrowth>"
      << "<gr_adgVal species=\"Species_2\">0.799</gr_adgVal>"
      << "</gr_asympDiameterGrowth>"
      << "<gr_slopeGrowthResponse>"
      << "<gr_sgrVal species=\"Species_2\">0.019</gr_sgrVal>"
      << "</gr_slopeGrowthResponse>"
      << "<gr_lengthLastSuppFactor>"
      << "<gr_llsfVal species=\"Species_2\">0.0</gr_llsfVal>"
      << "</gr_lengthLastSuppFactor>"
      << "<gr_lengthCurrReleaseFactor>"
      << "<gr_lcrfVal species=\"Species_2\">0.0</gr_lcrfVal>"
      << "</gr_lengthCurrReleaseFactor>"
      << "<gr_yrsExceedThresholdBeforeSupp>6</gr_yrsExceedThresholdBeforeSupp>"
      << "<gr_mortRateAtSuppression>0.1</gr_mortRateAtSuppression>"
      << "</AbsUnlimGrowth5>"
      << "<AbsRadialGrowth6>"
      << "<gr_adultConstRadialInc>"
      << "<gr_acriVal species=\"Species_3\">0.92</gr_acriVal>"
      << "</gr_adultConstRadialInc>"
      << "<gr_asympDiameterGrowth>"
      << "<gr_adgVal species=\"Species_3\">0.911</gr_adgVal>"
      << "</gr_asympDiameterGrowth>"
      << "<gr_slopeGrowthResponse>"
      << "<gr_sgrVal species=\"Species_3\">0.01</gr_sgrVal>"
      << "</gr_slopeGrowthResponse>"
      << "<gr_lengthLastSuppFactor>"
      << "<gr_llsfVal species=\"Species_3\">0.0</gr_llsfVal>"
      << "</gr_lengthLastSuppFactor>"
      << "<gr_lengthCurrReleaseFactor>"
      << "<gr_lcrfVal species=\"Species_3\">0.016</gr_lcrfVal>"
      << "</gr_lengthCurrReleaseFactor>"
      << "<gr_yrsExceedThresholdBeforeSupp>6</gr_yrsExceedThresholdBeforeSupp>"
      << "<gr_mortRateAtSuppression>0.1</gr_mortRateAtSuppression>"
      << "</AbsRadialGrowth6>"
      << "<AbsBAGrowth7>"
      << "<gr_adultConstAreaInc>"
      << "<gr_acaiVal species=\"Species_3\">0.3</gr_acaiVal>"
      << "</gr_adultConstAreaInc>"
      << "<gr_asympDiameterGrowth>"
      << "<gr_adgVal species=\"Species_3\">0.911</gr_adgVal>"
      << "</gr_asympDiameterGrowth>"
      << "<gr_slopeGrowthResponse>"
      << "<gr_sgrVal species=\"Species_3\">0.01</gr_sgrVal>"
      << "</gr_slopeGrowthResponse>"
      << "<gr_lengthLastSuppFactor>"
      << "<gr_llsfVal species=\"Species_3\">0.0</gr_llsfVal>"
      << "</gr_lengthLastSuppFactor>"
      << "<gr_lengthCurrReleaseFactor>"
      << "<gr_lcrfVal species=\"Species_3\">0.016</gr_lcrfVal>"
      << "</gr_lengthCurrReleaseFactor>"
      << "<gr_yrsExceedThresholdBeforeSupp>6</gr_yrsExceedThresholdBeforeSupp>"
      << "<gr_mortRateAtSuppression>0.1</gr_mortRateAtSuppression>"
      << "</AbsBAGrowth7>"
      << "<mortality>"
      << "<mo_mortAtZeroGrowth>"
      << "<mo_mazgVal species=\"Species_1\">0.01</mo_mazgVal>"
      << "<mo_mazgVal species=\"Species_2\">0.01</mo_mazgVal>"
      << "<mo_mazgVal species=\"Species_3\">0.01</mo_mazgVal>"
      << "</mo_mortAtZeroGrowth>"
      << "<mo_lightDependentMortality>"
      << "<mo_ldmVal species=\"Species_1\">0.1</mo_ldmVal>"
      << "<mo_ldmVal species=\"Species_2\">0.1</mo_ldmVal>"
      << "<mo_ldmVal species=\"Species_3\">0.1</mo_ldmVal>"
      << "</mo_lightDependentMortality>"
      << "</mortality>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}
