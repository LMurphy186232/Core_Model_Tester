//---------------------------------------------------------------------------
// TestSimpleLinearGrowth.cpp
//---------------------------------------------------------------------------
#include "TestSimpleLinearGrowth.h"
#include <gtest/gtest.h>
#include <fstream>
#include <math.h>
#include "TreePopulation.h"
#include "SimManager.h"
#include "BehaviorBase.h"

////////////////////////////////////////////////////////////////////////////
// Test1YearPerTimestep()
// Tests the growth when the timestep length is one year. WriteSimpleLinearGrowthXMLFile1()
// is used to set up the run. 8 trees are created of 2 species,
// assigned to all three growth types and with high and low GLIs. GLIs are
// assigned to them, and then growth is run. Their diameters, heights, and
// growth values are checked to make sure they are correct.
////////////////////////////////////////////////////////////////////////////
TEST(SimpleLinearGrowth, Test1YearPerTimestep) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTree *p_oTree1, *p_oTree2, *p_oTree3, *p_oTree4, *p_oTree5, *p_oTree6,
    *p_oTree7, *p_oTree8;
    float fDiam, fHeight, fExpectedDiam, fExpectedHeight, fLight, fGrowth, fExpectedGrowth;

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteSimpleLinearGrowthXMLFile1() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create our eight trees and set diameter, height, and GLI for each
    //Seedling, Species 1
    fDiam = 0.7;
    fHeight = 0.8;
    fLight = 10;
    p_oTree1 = p_oPop->CreateTree(1, 1, 0, clTreePopulation::seedling, fDiam);
    p_oTree1->SetValue(p_oPop->GetHeightCode(p_oTree1->GetSpecies(), p_oTree1->GetType()), fHeight, false, false);
    p_oTree1->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree1->GetSpecies(), p_oTree1->GetType()), fLight, false, false);

    //Seedling, Species 1
    fDiam = 0.1;
    fHeight = 0.2;
    fLight = 90;
    p_oTree2 = p_oPop->CreateTree(2, 2, 0, clTreePopulation::seedling, fDiam);
    p_oTree2->SetValue(p_oPop->GetHeightCode(p_oTree2->GetSpecies(), p_oTree2->GetType()), fHeight, false, false);
    p_oTree2->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree2->GetSpecies(), p_oTree2->GetType()), fLight, false, false);

    //Sapling, Species 1
    fDiam = 3.2032;
    fHeight = 5;
    fLight = 12;
    p_oTree3 = p_oPop->CreateTree(3, 3, 0, clTreePopulation::sapling, fDiam);
    p_oTree3->SetValue(p_oPop->GetHeightCode(p_oTree3->GetSpecies(), p_oTree3->GetType()), fHeight, false, false);
    p_oTree3->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree3->GetSpecies(), p_oTree3->GetType()), fLight, false, false);

    //Sapling, Species 1
    fDiam = 6.4064;
    fHeight = 3;
    fLight = 100;
    p_oTree4 = p_oPop->CreateTree(4, 4, 0, clTreePopulation::sapling, fDiam);
    p_oTree4->SetValue(p_oPop->GetHeightCode(p_oTree4->GetSpecies(), p_oTree4->GetType()), fHeight, false, false);
    p_oTree4->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree4->GetSpecies(), p_oTree4->GetType()), fLight, false, false);

    //Seedling, Species 2
    fDiam = 0.2;
    fHeight = 0.8;
    fLight = 0;
    p_oTree5 = p_oPop->CreateTree(5, 5, 1, clTreePopulation::seedling, fDiam);
    p_oTree5->SetValue(p_oPop->GetHeightCode(p_oTree5->GetSpecies(), p_oTree5->GetType()), fHeight, false, false);
    p_oTree5->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree5->GetSpecies(), p_oTree5->GetType()), fLight, false, false);

    //Seedling, Species 2
    fDiam = 1.4;
    fHeight = 0.65;
    fLight = 95;
    p_oTree6 = p_oPop->CreateTree(6, 6, 1, clTreePopulation::seedling, fDiam);
    p_oTree6->SetValue(p_oPop->GetHeightCode(p_oTree6->GetSpecies(), p_oTree6->GetType()), fHeight, false, false);
    p_oTree6->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree6->GetSpecies(), p_oTree6->GetType()), fLight, false, false);

    //Sapling, Species 2
    fDiam = 1.7832;
    fHeight = 4;
    fLight = 7;
    p_oTree7 = p_oPop->CreateTree(7, 7, 1, clTreePopulation::sapling, fDiam);
    p_oTree7->SetValue(p_oPop->GetHeightCode(p_oTree7->GetSpecies(), p_oTree7->GetType()), fHeight, false, false);
    p_oTree7->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree7->GetSpecies(), p_oTree7->GetType()), fLight, false, false);

    //Sapling, Species 2
    fDiam = 4.1608;
    fHeight = 6.3;
    fLight = 100;
    p_oTree8 = p_oPop->CreateTree(8, 8, 1, clTreePopulation::sapling, fDiam);
    p_oTree8->SetValue(p_oPop->GetHeightCode(p_oTree8->GetSpecies(), p_oTree8->GetType()), fHeight, false, false);
    p_oTree8->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree8->GetSpecies(), p_oTree8->GetType()), fLight, false, false);

    //Now run growth, but skip light
    int i;
    for (i = 1; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
      clBehaviorBase *p_oBase = p_oSimManager->GetBehaviorObject(i);
      p_oBase->Action();
    }

    //Confirm all trees
    //Seedling, Species 1
    fExpectedDiam = 0.9052;
    fExpectedHeight = 1.004718748;
    fExpectedGrowth = 1.026;
    p_oTree1->GetValue(p_oPop->GetDiam10Code(p_oTree1->GetSpecies(), p_oTree1->GetType()), &fDiam);
    p_oTree1->GetValue(p_oPop->GetHeightCode(p_oTree1->GetSpecies(), p_oTree1->GetType()), &fHeight);
    p_oTree1->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree1->GetSpecies(), p_oTree1->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Seedling, Species 1
    fExpectedDiam = 0.5388;
    fExpectedHeight = 0.64506431;
    fExpectedGrowth = 2.194;
    p_oTree2->GetValue(p_oPop->GetDiam10Code(p_oTree2->GetSpecies(), p_oTree2->GetType()), &fDiam);
    p_oTree2->GetValue(p_oPop->GetHeightCode(p_oTree2->GetSpecies(), p_oTree2->GetType()), &fHeight);
    p_oTree2->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree2->GetSpecies(), p_oTree2->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Sapling, Species 1
    fExpectedDiam = 4.26;
    fExpectedHeight = 8.5024;
    fExpectedGrowth = 1.3;
    p_oTree3->GetValue(p_oPop->GetDiam10Code(p_oTree3->GetSpecies(), p_oTree3->GetType()), &fDiam);
    p_oTree3->GetValue(p_oPop->GetHeightCode(p_oTree3->GetSpecies(), p_oTree3->GetType()), &fHeight);
    p_oTree3->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree3->GetSpecies(), p_oTree3->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Sapling, Species 1
    fExpectedDiam = 8.26;
    fExpectedHeight = 8.588;
    fExpectedGrowth =  1.3;
    p_oTree4->GetValue(p_oPop->GetDiam10Code(p_oTree4->GetSpecies(), p_oTree4->GetType()), &fDiam);
    p_oTree4->GetValue(p_oPop->GetHeightCode(p_oTree4->GetSpecies(), p_oTree4->GetType()), &fHeight);
    p_oTree4->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree4->GetSpecies(), p_oTree4->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Seedling, Species 2
    fExpectedDiam = 0.333;
    fExpectedHeight = 1.0408;
    fExpectedGrowth = 0.665;
    p_oTree5->GetValue(p_oPop->GetDiam10Code(p_oTree5->GetSpecies(), p_oTree5->GetType()), &fDiam);
    p_oTree5->GetValue(p_oPop->GetHeightCode(p_oTree5->GetSpecies(), p_oTree5->GetType()), &fHeight);
    p_oTree5->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree5->GetSpecies(), p_oTree5->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Seedling, Species 2 (now sapling)
    fExpectedDiam = 1.8237;
    fExpectedHeight = 2.6673;
    fExpectedGrowth = 2.1185;
    p_oTree6->GetValue(p_oPop->GetDiam10Code(p_oTree6->GetSpecies(), p_oTree6->GetType()), &fDiam);
    p_oTree6->GetValue(p_oPop->GetHeightCode(p_oTree6->GetSpecies(), p_oTree6->GetType()), &fHeight);
    p_oTree6->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree6->GetSpecies(), p_oTree6->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Sapling, Species 2
    fExpectedDiam = 3.1004;
    fExpectedHeight = 3.009;
    fExpectedGrowth = 0.502;
    p_oTree7->GetValue(p_oPop->GetDiam10Code(p_oTree7->GetSpecies(), p_oTree7->GetType()), &fDiam);
    p_oTree7->GetValue(p_oPop->GetHeightCode(p_oTree7->GetSpecies(), p_oTree7->GetType()), &fHeight);
    p_oTree7->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree7->GetSpecies(), p_oTree7->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Sapling, Species 2
    fExpectedDiam = 7.77;
    fExpectedHeight = 5.3727;
    fExpectedGrowth = 3.85;
    p_oTree8->GetValue(p_oPop->GetDiam10Code(p_oTree8->GetSpecies(), p_oTree8->GetType()), &fDiam);
    p_oTree8->GetValue(p_oPop->GetHeightCode(p_oTree8->GetSpecies(), p_oTree8->GetType()), &fHeight);
    p_oTree8->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree8->GetSpecies(), p_oTree8->GetType()), &fGrowth);
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
// Tests the growth when the timestep length is three years. WriteSimpleLinearGrowthXMLFile1()
// is used to set up the run. 8 trees are created of 2 species,
// assigned to all three growth types and with high and low GLIs. GLIs are
// assigned to them, and then growth is run. Their diameters, heights, and
// growth values are checked to make sure they are correct.
////////////////////////////////////////////////////////////////////////////
TEST(SimpleLinearGrowth, Test3YearsPerTimestep) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTree *p_oTree1, *p_oTree2, *p_oTree3, *p_oTree4, *p_oTree5, *p_oTree6,
    *p_oTree7, *p_oTree8;
    float fDiam, fHeight, fExpectedDiam, fExpectedHeight, fLight, fGrowth, fExpectedGrowth;

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteSimpleLinearGrowthXMLFile2() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create our eight trees and set diameter, height, and GLI for each
    //Seedling, Species 1
    fDiam = 0.7;
    fHeight = 0.8;
    fLight = 10;
    p_oTree1 = p_oPop->CreateTree(1, 1, 0, clTreePopulation::seedling, fDiam);
    p_oTree1->SetValue(p_oPop->GetHeightCode(p_oTree1->GetSpecies(), p_oTree1->GetType()), fHeight, false, false);
    p_oTree1->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree1->GetSpecies(), p_oTree1->GetType()), fLight, false, false);

    //Seedling, Species 1
    fDiam = 0.1;
    fHeight = 0.2;
    fLight = 90;
    p_oTree2 = p_oPop->CreateTree(2, 2, 0, clTreePopulation::seedling, fDiam);
    p_oTree2->SetValue(p_oPop->GetHeightCode(p_oTree2->GetSpecies(), p_oTree2->GetType()), fHeight, false, false);
    p_oTree2->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree2->GetSpecies(), p_oTree2->GetType()), fLight, false, false);

    //Sapling, Species 1
    fDiam = 3.2032;
    fHeight = 5;
    fLight = 12;
    p_oTree3 = p_oPop->CreateTree(3, 3, 0, clTreePopulation::sapling, fDiam);
    p_oTree3->SetValue(p_oPop->GetHeightCode(p_oTree3->GetSpecies(), p_oTree3->GetType()), fHeight, false, false);
    p_oTree3->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree3->GetSpecies(), p_oTree3->GetType()), fLight, false, false);

    //Sapling, Species 1
    fDiam = 6.4064;
    fHeight = 3;
    fLight = 100;
    p_oTree4 = p_oPop->CreateTree(4, 4, 0, clTreePopulation::sapling, fDiam);
    p_oTree4->SetValue(p_oPop->GetHeightCode(p_oTree4->GetSpecies(), p_oTree4->GetType()), fHeight, false, false);
    p_oTree4->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree4->GetSpecies(), p_oTree4->GetType()), fLight, false, false);

    //Seedling, Species 2
    fDiam = 0.2;
    fHeight = 0.8;
    fLight = 0;
    p_oTree5 = p_oPop->CreateTree(5, 5, 1, clTreePopulation::seedling, fDiam);
    p_oTree5->SetValue(p_oPop->GetHeightCode(p_oTree5->GetSpecies(), p_oTree5->GetType()), fHeight, false, false);
    p_oTree5->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree5->GetSpecies(), p_oTree5->GetType()), fLight, false, false);

    //Seedling, Species 2
    fDiam = 1.4;
    fHeight = 0.65;
    fLight = 95;
    p_oTree6 = p_oPop->CreateTree(6, 6, 1, clTreePopulation::seedling, fDiam);
    p_oTree6->SetValue(p_oPop->GetHeightCode(p_oTree6->GetSpecies(), p_oTree6->GetType()), fHeight, false, false);
    p_oTree6->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree6->GetSpecies(), p_oTree6->GetType()), fLight, false, false);

    //Sapling, Species 2
    fDiam = 1.7832;
    fHeight = 4;
    fLight = 7;
    p_oTree7 = p_oPop->CreateTree(7, 7, 1, clTreePopulation::sapling, fDiam);
    p_oTree7->SetValue(p_oPop->GetHeightCode(p_oTree7->GetSpecies(), p_oTree7->GetType()), fHeight, false, false);
    p_oTree7->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree7->GetSpecies(), p_oTree7->GetType()), fLight, false, false);

    //Sapling, Species 2
    fDiam = 4.1608;
    fHeight = 6.3;
    fLight = 100;
    p_oTree8 = p_oPop->CreateTree(8, 8, 1, clTreePopulation::sapling, fDiam);
    p_oTree8->SetValue(p_oPop->GetHeightCode(p_oTree8->GetSpecies(), p_oTree8->GetType()), fHeight, false, false);
    p_oTree8->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree8->GetSpecies(), p_oTree8->GetType()), fLight, false, false);

    //Now run growth, but skip light
    int i;
    for (i = 1; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
      clBehaviorBase *p_oBase = p_oSimManager->GetBehaviorObject(i);
      p_oBase->Action();
    }

    //Confirm all trees
    //Seedling, Species 1 (now sapling)
    fExpectedDiam = 1.3156;
    fExpectedHeight = 1.409873785;
    fExpectedGrowth = 1.026;
    p_oTree1->GetValue(p_oPop->GetDiam10Code(p_oTree1->GetSpecies(), p_oTree1->GetType()), &fDiam);
    p_oTree1->GetValue(p_oPop->GetHeightCode(p_oTree1->GetSpecies(), p_oTree1->GetType()), &fHeight);
    p_oTree1->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree1->GetSpecies(), p_oTree1->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Seedling, Species 1 (now sapling)
    fExpectedDiam = 1.4164;
    fExpectedHeight = 1.515415514;
    fExpectedGrowth = 2.194;
    p_oTree2->GetValue(p_oPop->GetDiam10Code(p_oTree2->GetSpecies(), p_oTree2->GetType()), &fDiam);
    p_oTree2->GetValue(p_oPop->GetHeightCode(p_oTree2->GetSpecies(), p_oTree2->GetType()), &fHeight);
    p_oTree2->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree2->GetSpecies(), p_oTree2->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Sapling, Species 1
    fExpectedDiam = 4.78;
    fExpectedHeight = 15.5072;
    fExpectedGrowth = 1.3;
    p_oTree3->GetValue(p_oPop->GetDiam10Code(p_oTree3->GetSpecies(), p_oTree3->GetType()), &fDiam);
    p_oTree3->GetValue(p_oPop->GetHeightCode(p_oTree3->GetSpecies(), p_oTree3->GetType()), &fHeight);
    p_oTree3->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree3->GetSpecies(), p_oTree3->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Sapling, Species 1
    fExpectedDiam = 8.78;
    fExpectedHeight = 19.764;
    fExpectedGrowth = 1.3;
    p_oTree4->GetValue(p_oPop->GetDiam10Code(p_oTree4->GetSpecies(), p_oTree4->GetType()), &fDiam);
    p_oTree4->GetValue(p_oPop->GetHeightCode(p_oTree4->GetSpecies(), p_oTree4->GetType()), &fHeight);
    p_oTree4->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree4->GetSpecies(), p_oTree4->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Seedling, Species 2
    fExpectedDiam = 0.599;
    fExpectedHeight = 1.5224;
    fExpectedGrowth = 0.665;
    p_oTree5->GetValue(p_oPop->GetDiam10Code(p_oTree5->GetSpecies(), p_oTree5->GetType()), &fDiam);
    p_oTree5->GetValue(p_oPop->GetHeightCode(p_oTree5->GetSpecies(), p_oTree5->GetType()), &fHeight);
    p_oTree5->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree5->GetSpecies(), p_oTree5->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Seedling, Species 2
    fExpectedDiam = 2.6711;
    fExpectedHeight = 6.7019;
    fExpectedGrowth = 2.1185;
    p_oTree6->GetValue(p_oPop->GetDiam10Code(p_oTree6->GetSpecies(), p_oTree6->GetType()), &fDiam);
    p_oTree6->GetValue(p_oPop->GetHeightCode(p_oTree6->GetSpecies(), p_oTree6->GetType()), &fHeight);
    p_oTree6->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree6->GetSpecies(), p_oTree6->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Sapling, Species 2
    fExpectedDiam = 3.3012;
    fExpectedHeight = 3.11396;
    fExpectedGrowth = 0.502;
    p_oTree7->GetValue(p_oPop->GetDiam10Code(p_oTree7->GetSpecies(), p_oTree7->GetType()), &fDiam);
    p_oTree7->GetValue(p_oPop->GetHeightCode(p_oTree7->GetSpecies(), p_oTree7->GetType()), &fHeight);
    p_oTree7->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree7->GetSpecies(), p_oTree7->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Sapling, Species 2
    fExpectedDiam = 9.31;
    fExpectedHeight = 6.118;
    fExpectedGrowth = 3.85;
    p_oTree8->GetValue(p_oPop->GetDiam10Code(p_oTree8->GetSpecies(), p_oTree8->GetType()), &fDiam);
    p_oTree8->GetValue(p_oPop->GetHeightCode(p_oTree8->GetSpecies(), p_oTree8->GetType()), &fHeight);
    p_oTree8->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree8->GetSpecies(), p_oTree8->GetType()), &fGrowth);
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
// WriteSimpleLinearGrowthXMLFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteSimpleLinearGrowthXMLFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //Write file
  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">"
      << "<plot>"
      << "<timesteps>1</timesteps>"
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
      //Leave in one light so that "Light" will be registerd
      << "<behaviorName>ConstantGLI</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>SimpleLinearGrowth diam only</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>SimpleLinearGrowth height only</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>3</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>ConstRadialGrowth diam only</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>4</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>HeightIncrementer</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>5</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>SimpleLinearGrowth</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>6</listPosition>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "</behavior>"
      << "</behaviorList>"
      << "<ConstantGLI1>"
      << "<li_constGLI>100</li_constGLI>"
      << "</ConstantGLI1>"
      << "<ConstRadialGrowth4>"
      << "<gr_adultConstRadialInc>"
      << "<gr_acriVal species=\"Species_1\">1.3</gr_acriVal>"
      << "<gr_acriVal species=\"Species_2\">5.92</gr_acriVal>"
      << "</gr_adultConstRadialInc>"
      << "</ConstRadialGrowth4>"
      << "<SimpleLinearGrowth2>"
      << "<gr_diamSimpleLinearIntercept>"
      << "<gr_dsliVal species=\"Species_1\">0.88</gr_dsliVal>"
      << "<gr_dsliVal species=\"Species_2\">0.665</gr_dsliVal>"
      << "</gr_diamSimpleLinearIntercept>"
      << "<gr_diamSimpleLinearSlope>"
      << "<gr_dslsVal species=\"Species_1\">0.0146</gr_dslsVal>"
      << "<gr_dslsVal species=\"Species_2\">0.0153</gr_dslsVal>"
      << "</gr_diamSimpleLinearSlope>"
      << "</SimpleLinearGrowth2>"
      << "<SimpleLinearGrowth3>"
      << "<gr_heightSimpleLinearIntercept>"
      << "<gr_hsliVal species=\"Species_1\">321.8</gr_hsliVal>"
      << "<gr_hsliVal species=\"Species_2\">24.08</gr_hsliVal>"
      << "</gr_heightSimpleLinearIntercept>"
      << "<gr_heightSimpleLinearSlope>"
      << "<gr_hslsVal species=\"Species_1\">2.37</gr_hslsVal>"
      << "<gr_hslsVal species=\"Species_2\">1.87</gr_hslsVal>"
      << "</gr_heightSimpleLinearSlope>"
      << "</SimpleLinearGrowth3>"
      << "<SimpleLinearGrowth6>"
      << "<gr_diamSimpleLinearIntercept>"
      << "<gr_dsliVal species=\"Species_2\">0.25</gr_dsliVal>"
      << "</gr_diamSimpleLinearIntercept>"
      << "<gr_diamSimpleLinearSlope>"
      << "<gr_dslsVal species=\"Species_2\">0.036</gr_dslsVal>"
      << "</gr_diamSimpleLinearSlope>"
      << "</SimpleLinearGrowth6>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteSimpleLinearGrowthXMLFile2()
////////////////////////////////////////////////////////////////////////////
const char* WriteSimpleLinearGrowthXMLFile2() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //Write file
  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">"
      << "<plot>"
      << "<timesteps>1</timesteps>"
      << "<yearsPerTimestep>3</yearsPerTimestep>"
      << "<randomSeed>1</randomSeed>"
      << "<plot_lenX>200.0</plot_lenX>"
      << "<plot_lenY>200.0</plot_lenY>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88171785</plot_temp_C>"
      << "<plot_latitude>55.37</plot_latitude>"
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
      //Leave in one light so that "Light" will be registerd
      << "<behaviorName>ConstantGLI</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>SimpleLinearGrowth diam only</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>SimpleLinearGrowth height only</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>3</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>ConstRadialGrowth diam only</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>4</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>HeightIncrementer</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>5</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>SimpleLinearGrowth</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>6</listPosition>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "</behavior>"
      << "</behaviorList>"
      << "<ConstantGLI1>"
      << "<li_constGLI>100</li_constGLI>"
      << "</ConstantGLI1>"
      << "<ConstRadialGrowth4>"
      << "<gr_adultConstRadialInc>"
      << "<gr_acriVal species=\"Species_1\">1.3</gr_acriVal>"
      << "<gr_acriVal species=\"Species_2\">5.92</gr_acriVal>"
      << "</gr_adultConstRadialInc>"
      << "</ConstRadialGrowth4>"
      << "<SimpleLinearGrowth2>"
      << "<gr_diamSimpleLinearIntercept>"
      << "<gr_dsliVal species=\"Species_1\">0.88</gr_dsliVal>"
      << "<gr_dsliVal species=\"Species_2\">0.665</gr_dsliVal>"
      << "</gr_diamSimpleLinearIntercept>"
      << "<gr_diamSimpleLinearSlope>"
      << "<gr_dslsVal species=\"Species_1\">0.0146</gr_dslsVal>"
      << "<gr_dslsVal species=\"Species_2\">0.0153</gr_dslsVal>"
      << "</gr_diamSimpleLinearSlope>"
      << "</SimpleLinearGrowth2>"
      << "<SimpleLinearGrowth3>"
      << "<gr_heightSimpleLinearIntercept>"
      << "<gr_hsliVal species=\"Species_1\">321.8</gr_hsliVal>"
      << "<gr_hsliVal species=\"Species_2\">24.08</gr_hsliVal>"
      << "</gr_heightSimpleLinearIntercept>"
      << "<gr_heightSimpleLinearSlope>"
      << "<gr_hslsVal species=\"Species_1\">2.37</gr_hslsVal>"
      << "<gr_hslsVal species=\"Species_2\">1.87</gr_hslsVal>"
      << "</gr_heightSimpleLinearSlope>"
      << "</SimpleLinearGrowth3>"
      << "<SimpleLinearGrowth6>"
      << "<gr_diamSimpleLinearIntercept>"
      << "<gr_dsliVal species=\"Species_2\">0.25</gr_dsliVal>"
      << "</gr_diamSimpleLinearIntercept>"
      << "<gr_diamSimpleLinearSlope>"
      << "<gr_dslsVal species=\"Species_2\">0.036</gr_dslsVal>"
      << "</gr_diamSimpleLinearSlope>"
      << "</SimpleLinearGrowth6>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}
