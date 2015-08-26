#include <iostream>
//---------------------------------------------------------------------------
// TestMichMenNegGrowth.cpp
//---------------------------------------------------------------------------
#include "TestMichMenNegGrowth.h"
#include <gtest/gtest.h>
#include <fstream>
#include <math.h>
#include "TreePopulation.h"
#include "SimManager.h"
#include "BehaviorBase.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////
// Test1Run1YearPerTimestep()
// Tests height growth when the timestep length is one year.
// WriteMichMenNegGrowthXMLFile1() is used to set up the run. 10 trees are
// created of four species. GLIs are assigned to them, and then growth is run.
// Their diameters, heights, and "Growth" values are checked to make sure they
// are correct.
////////////////////////////////////////////////////////////////////////////
TEST(MichMenNegGrowth, Test1Run1YearPerTimestep) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTree *p_oTree1, *p_oTree2, *p_oTree3, *p_oTree4, *p_oTree5, *p_oTree6,
    *p_oTree7, *p_oTree8, *p_oTree9, *p_oTree10;
    float fDiam, fHeight, fExpectedDiam, fExpectedHeight, fLight, fGrowth,
    fExpectedGrowth, fStochastic;

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteMichMenNegGrowthXMLFile1() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create our ten trees and set diameter, height, and GLI for each
    //Tree 1: Sapling, Species 1
    fDiam = 5;
    fHeight = 7;
    fLight = 60;
    p_oTree1 = p_oPop->CreateTree(1, 1, 0, clTreePopulation::sapling, fDiam);
    p_oTree1->SetValue(p_oPop->GetHeightCode(p_oTree1->GetSpecies(), p_oTree1->GetType()), fHeight, false, false);
    p_oTree1->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree1->GetSpecies(), p_oTree1->GetType()), fLight, false, false);

    //Tree 2: Sapling, Species 2
    fDiam = 5;
    fHeight = 8;
    fLight = 80;
    p_oTree2 = p_oPop->CreateTree(2, 2, 1, clTreePopulation::sapling, fDiam);
    p_oTree2->SetValue(p_oPop->GetHeightCode(p_oTree2->GetSpecies(), p_oTree2->GetType()), fHeight, false, false);
    p_oTree2->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree2->GetSpecies(), p_oTree2->GetType()), fLight, false, false);

    //Tree 3: Seedling, Species 2
    fDiam = 1;
    fHeight = 0.75;
    fLight = 10;
    p_oTree3 = p_oPop->CreateTree(3, 3, 1, clTreePopulation::seedling, fDiam);
    p_oTree3->SetValue(p_oPop->GetHeightCode(p_oTree3->GetSpecies(), p_oTree3->GetType()), fHeight, false, false);
    p_oTree3->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree3->GetSpecies(), p_oTree3->GetType()), fLight, false, false);

    //Tree 4: Adult, Species 1
    fDiam = 20;
    fHeight = 15;
    fLight = 2;
    p_oTree4 = p_oPop->CreateTree(4, 4, 0, clTreePopulation::adult, fDiam);
    p_oTree4->SetValue(p_oPop->GetHeightCode(p_oTree4->GetSpecies(), p_oTree4->GetType()), fHeight, false, false);
    p_oTree4->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree4->GetSpecies(), p_oTree4->GetType()), fLight, false, false);

    //Tree 5: Seedling, Species 1
    fDiam = 1.2;
    fHeight = 1;
    fLight = 90;
    p_oTree5 = p_oPop->CreateTree(5, 5, 0, clTreePopulation::seedling, fDiam);
    p_oTree5->SetValue(p_oPop->GetHeightCode(p_oTree5->GetSpecies(), p_oTree5->GetType()), fHeight, false, false);
    p_oTree5->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree5->GetSpecies(), p_oTree5->GetType()), fLight, false, false);

    //Tree 6: Sapling, Species 4
    fDiam = 5;
    fHeight = 7;
    fLight = 60;
    p_oTree6 = p_oPop->CreateTree(6, 6, 3, clTreePopulation::sapling, fDiam);
    p_oTree6->SetValue(p_oPop->GetHeightCode(p_oTree6->GetSpecies(), p_oTree6->GetType()), fHeight, false, false);
    p_oTree6->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree6->GetSpecies(), p_oTree6->GetType()), fLight, false, false);

    //Tree 7: Sapling, Species 4
    fDiam = 5;
    fHeight = 8;
    fLight = 70;
    p_oTree7 = p_oPop->CreateTree(7, 7, 3, clTreePopulation::sapling, fDiam);
    p_oTree7->SetValue(p_oPop->GetHeightCode(p_oTree7->GetSpecies(), p_oTree7->GetType()), fHeight, false, false);
    p_oTree7->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree7->GetSpecies(), p_oTree7->GetType()), fLight, false, false);

    //Tree 8: Sapling, Species 4
    fDiam = 7;
    fHeight = 6;
    fLight = 10;
    p_oTree8 = p_oPop->CreateTree(8, 8, 3, clTreePopulation::sapling, fDiam);
    p_oTree8->SetValue(p_oPop->GetHeightCode(p_oTree8->GetSpecies(), p_oTree8->GetType()), fHeight, false, false);
    p_oTree8->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree8->GetSpecies(), p_oTree8->GetType()), fLight, false, false);

    //Tree 9: Adult, Species 4
    fDiam = 20;
    fHeight = 15;
    fLight = 2;
    p_oTree9 = p_oPop->CreateTree(9, 9, 3, clTreePopulation::adult, fDiam);
    p_oTree9->SetValue(p_oPop->GetHeightCode(p_oTree9->GetSpecies(), p_oTree9->GetType()), fHeight, false, false);
    p_oTree9->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree9->GetSpecies(), p_oTree9->GetType()), fLight, false, false);

    //Tree 10: Adult, Species 4
    fDiam = 20;
    fHeight = 16;
    fLight = 90;
    p_oTree10 = p_oPop->CreateTree(10, 10, 3, clTreePopulation::adult, fDiam);
    p_oTree10->SetValue(p_oPop->GetHeightCode(p_oTree10->GetSpecies(), p_oTree10->GetType()), fHeight, false, false);
    p_oTree10->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree10->GetSpecies(), p_oTree10->GetType()), fLight, false, false);

    //Now run growth, but skip light
    int i;
    for (i = 1; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
      clBehaviorBase *p_oBase = p_oSimManager->GetBehaviorObject(i);
      p_oBase->Action();
    }

    //Confirm all trees
    //Tree 1: Sapling, Species 1
    fExpectedDiam = 5.02021774;
    fExpectedHeight = 7.019409031;
    fExpectedGrowth = 0.101088701;
    p_oTree1->GetValue(p_oPop->GetDiam10Code(p_oTree1->GetSpecies(), p_oTree1->GetType()), &fDiam);
    p_oTree1->GetValue(p_oPop->GetHeightCode(p_oTree1->GetSpecies(), p_oTree1->GetType()), &fHeight);
    p_oTree1->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree1->GetSpecies(), p_oTree1->GetType()), &fGrowth);
    p_oTree1->GetValue(p_oPop->GetFloatDataCode("autocorr", p_oTree1->GetSpecies(), p_oTree1->GetType()), &fStochastic);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);
    EXPECT_EQ(fStochastic, 0);

    //Tree 2: Sapling, Species 2
    fExpectedDiam = 4.644599456;
    fExpectedHeight = 7.683693516;
    fExpectedGrowth = -1.777002719;
    p_oTree2->GetValue(p_oPop->GetDiam10Code(p_oTree2->GetSpecies(), p_oTree2->GetType()), &fDiam);
    p_oTree2->GetValue(p_oPop->GetHeightCode(p_oTree2->GetSpecies(), p_oTree2->GetType()), &fHeight);
    p_oTree2->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree2->GetSpecies(), p_oTree2->GetType()), &fGrowth);
    p_oTree2->GetValue(p_oPop->GetFloatDataCode("autocorr", p_oTree2->GetSpecies(), p_oTree2->GetType()), &fStochastic);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);
    EXPECT_EQ(fStochastic, 0);

    //Tree 3: Seedling, Species 2
    fExpectedDiam = 0.620957658;
    fExpectedHeight = 0.412652316;
    fExpectedGrowth = -1.895211708;
    p_oTree3->GetValue(p_oPop->GetDiam10Code(p_oTree3->GetSpecies(), p_oTree3->GetType()), &fDiam);
    p_oTree3->GetValue(p_oPop->GetHeightCode(p_oTree3->GetSpecies(), p_oTree3->GetType()), &fHeight);
    p_oTree3->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree3->GetSpecies(), p_oTree3->GetType()), &fGrowth);
    p_oTree3->GetValue(p_oPop->GetFloatDataCode("autocorr", p_oTree3->GetSpecies(), p_oTree3->GetType()), &fStochastic);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);
    EXPECT_EQ(fStochastic, 0);

    //Tree 4: Adult, Species 1
    fExpectedDiam = 19.98883096;
    fExpectedHeight = 14.98927772;
    fExpectedGrowth = -0.055845199;
    p_oTree4->GetValue(p_oPop->GetDbhCode(p_oTree4->GetSpecies(), p_oTree4->GetType()), &fDiam);
    p_oTree4->GetValue(p_oPop->GetHeightCode(p_oTree4->GetSpecies(), p_oTree4->GetType()), &fHeight);
    p_oTree4->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree4->GetSpecies(), p_oTree4->GetType()), &fGrowth);
    p_oTree4->GetValue(p_oPop->GetFloatDataCode("autocorr", p_oTree4->GetSpecies(), p_oTree4->GetType()), &fStochastic);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);
    EXPECT_EQ(fStochastic, 0);

    //Tree 5: Seedling, Species 1
    fExpectedDiam = 1.292147769;
    fExpectedHeight = 1.088461858;
    fExpectedGrowth = 0.460738845;
    p_oTree5->GetValue(p_oPop->GetDiam10Code(p_oTree5->GetSpecies(), p_oTree5->GetType()), &fDiam);
    p_oTree5->GetValue(p_oPop->GetHeightCode(p_oTree5->GetSpecies(), p_oTree5->GetType()), &fHeight);
    p_oTree5->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree5->GetSpecies(), p_oTree5->GetType()), &fGrowth);
    p_oTree5->GetValue(p_oPop->GetFloatDataCode("autocorr", p_oTree5->GetSpecies(), p_oTree5->GetType()), &fStochastic);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);
    EXPECT_EQ(fStochastic, 0);

    //Tree 6: Sapling, Species 4
    fExpectedDiam = 5.006125904;
    fExpectedHeight = 7.006395444;
    fExpectedGrowth = 0.030629521;
    p_oTree6->GetValue(p_oPop->GetDiam10Code(p_oTree6->GetSpecies(), p_oTree6->GetType()), &fDiam);
    p_oTree6->GetValue(p_oPop->GetHeightCode(p_oTree6->GetSpecies(), p_oTree6->GetType()), &fHeight);
    p_oTree6->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree6->GetSpecies(), p_oTree6->GetType()), &fGrowth);
    p_oTree6->GetValue(p_oPop->GetFloatDataCode("autocorr", p_oTree6->GetSpecies(), p_oTree6->GetType()), &fStochastic);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);
    EXPECT_EQ(fStochastic, 0);

    //Tree 7: Sapling, Species 4
    fExpectedDiam = 5.036026181;
    fExpectedHeight = 8.037611333;
    fExpectedGrowth = 0.180130905;
    p_oTree7->GetValue(p_oPop->GetDiam10Code(p_oTree7->GetSpecies(), p_oTree7->GetType()), &fDiam);
    p_oTree7->GetValue(p_oPop->GetHeightCode(p_oTree7->GetSpecies(), p_oTree7->GetType()), &fHeight);
    p_oTree7->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree7->GetSpecies(), p_oTree7->GetType()), &fGrowth);
    p_oTree7->GetValue(p_oPop->GetFloatDataCode("autocorr", p_oTree7->GetSpecies(), p_oTree7->GetType()), &fStochastic);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);
    EXPECT_EQ(fStochastic, 0);

    //Tree 8: Sapling, Species 4
    fExpectedDiam = 6.879578278;
    fExpectedHeight = 5.874279722;
    fExpectedGrowth = -0.602108609;
    p_oTree8->GetValue(p_oPop->GetDiam10Code(p_oTree8->GetSpecies(), p_oTree8->GetType()), &fDiam);
    p_oTree8->GetValue(p_oPop->GetHeightCode(p_oTree8->GetSpecies(), p_oTree8->GetType()), &fHeight);
    p_oTree8->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree8->GetSpecies(), p_oTree8->GetType()), &fGrowth);
    p_oTree8->GetValue(p_oPop->GetFloatDataCode("autocorr", p_oTree8->GetSpecies(), p_oTree8->GetType()), &fStochastic);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);
    EXPECT_EQ(fStochastic, 0);

    //Tree 9: Adult, Species 4
    fExpectedDiam = 19.85771492;
    fExpectedHeight = 14.85145438;
    fExpectedGrowth = -0.711425404;
    p_oTree9->GetValue(p_oPop->GetDbhCode(p_oTree9->GetSpecies(), p_oTree9->GetType()), &fDiam);
    p_oTree9->GetValue(p_oPop->GetHeightCode(p_oTree9->GetSpecies(), p_oTree9->GetType()), &fHeight);
    p_oTree9->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree9->GetSpecies(), p_oTree9->GetType()), &fGrowth);
    p_oTree9->GetValue(p_oPop->GetFloatDataCode("autocorr", p_oTree9->GetSpecies(), p_oTree9->GetType()), &fStochastic);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);
    EXPECT_EQ(fStochastic, 0);

    //Tree 10: Adult, Species 4
    fExpectedDiam = 20.16087942;
    fExpectedHeight = 16.16795812;
    fExpectedGrowth = 0.804397103;
    p_oTree10->GetValue(p_oPop->GetDbhCode(p_oTree10->GetSpecies(), p_oTree10->GetType()), &fDiam);
    p_oTree10->GetValue(p_oPop->GetHeightCode(p_oTree10->GetSpecies(), p_oTree10->GetType()), &fHeight);
    p_oTree10->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree10->GetSpecies(), p_oTree10->GetType()), &fGrowth);
    p_oTree10->GetValue(p_oPop->GetFloatDataCode("autocorr", p_oTree10->GetSpecies(), p_oTree10->GetType()), &fStochastic);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);
    EXPECT_EQ(fStochastic, 0);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// Test1Run3YearsPerTimestep()
// Tests height growth when the timestep length is three years.
// WriteMichMenNegGrowthXMLFile2() is used to set up the run. 10 trees are
// created of four species. GLIs are assigned to them, and then growth is run.
// Their diameters, heights, and "Growth" values are checked to make sure they
// are correct.
////////////////////////////////////////////////////////////////////////////
TEST(MichMenNegGrowth, Test1Run3YearsPerTimestep) {
  clTreePopulation * p_oPop;
  clTree *p_oTree1, *p_oTree2, *p_oTree3, *p_oTree4, *p_oTree5, *p_oTree6,
     *p_oTree7, *p_oTree8, *p_oTree9, *p_oTree10;
  float fDiam, fHeight, fExpectedDiam, fExpectedHeight, fLight, fGrowth, fExpectedGrowth;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteMichMenNegGrowthXMLFile2() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create our ten trees and set diameter, height, and GLI for each
    //Tree 1: Sapling, Species 1
    fDiam = 5;
    fHeight = 7;
    fLight = 60;
    p_oTree1 = p_oPop->CreateTree(1, 1, 0, clTreePopulation::sapling, fDiam);
    p_oTree1->SetValue(p_oPop->GetHeightCode(p_oTree1->GetSpecies(), p_oTree1->GetType()), fHeight, false, false);
    p_oTree1->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree1->GetSpecies(), p_oTree1->GetType()), fLight, false, false);

    //Tree 2: Sapling, Species 2
    fDiam = 5;
    fHeight = 8;
    fLight = 80;
    p_oTree2 = p_oPop->CreateTree(2, 2, 1, clTreePopulation::sapling, fDiam);
    p_oTree2->SetValue(p_oPop->GetHeightCode(p_oTree2->GetSpecies(), p_oTree2->GetType()), fHeight, false, false);
    p_oTree2->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree2->GetSpecies(), p_oTree2->GetType()), fLight, false, false);

    //Tree 3: Seedling, Species 2
    fDiam = 1;
    fHeight = 0.75;
    fLight = 10;
    p_oTree3 = p_oPop->CreateTree(3, 3, 1, clTreePopulation::seedling, fDiam);
    p_oTree3->SetValue(p_oPop->GetHeightCode(p_oTree3->GetSpecies(), p_oTree3->GetType()), fHeight, false, false);
    p_oTree3->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree3->GetSpecies(), p_oTree3->GetType()), fLight, false, false);

    //Tree 4: Adult, Species 1
    fDiam = 20;
    fHeight = 15;
    fLight = 2;
    p_oTree4 = p_oPop->CreateTree(4, 4, 0, clTreePopulation::adult, fDiam);
    p_oTree4->SetValue(p_oPop->GetHeightCode(p_oTree4->GetSpecies(), p_oTree4->GetType()), fHeight, false, false);
    p_oTree4->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree4->GetSpecies(), p_oTree4->GetType()), fLight, false, false);

    //Tree 5: Seedling, Species 1
    fDiam = 1.2;
    fHeight = 1;
    fLight = 90;
    p_oTree5 = p_oPop->CreateTree(5, 5, 0, clTreePopulation::seedling, fDiam);
    p_oTree5->SetValue(p_oPop->GetHeightCode(p_oTree5->GetSpecies(), p_oTree5->GetType()), fHeight, false, false);
    p_oTree5->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree5->GetSpecies(), p_oTree5->GetType()), fLight, false, false);

    //Tree 6: Sapling, Species 4
    fDiam = 5;
    fHeight = 7;
    fLight = 60;
    p_oTree6 = p_oPop->CreateTree(6, 6, 3, clTreePopulation::sapling, fDiam);
    p_oTree6->SetValue(p_oPop->GetHeightCode(p_oTree6->GetSpecies(), p_oTree6->GetType()), fHeight, false, false);
    p_oTree6->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree6->GetSpecies(), p_oTree6->GetType()), fLight, false, false);

    //Tree 7: Sapling, Species 4
    fDiam = 5;
    fHeight = 8;
    fLight = 70;
    p_oTree7 = p_oPop->CreateTree(7, 7, 3, clTreePopulation::sapling, fDiam);
    p_oTree7->SetValue(p_oPop->GetHeightCode(p_oTree7->GetSpecies(), p_oTree7->GetType()), fHeight, false, false);
    p_oTree7->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree7->GetSpecies(), p_oTree7->GetType()), fLight, false, false);

    //Tree 8: Sapling, Species 4
    fDiam = 7;
    fHeight = 6;
    fLight = 10;
    p_oTree8 = p_oPop->CreateTree(8, 8, 3, clTreePopulation::sapling, fDiam);
    p_oTree8->SetValue(p_oPop->GetHeightCode(p_oTree8->GetSpecies(), p_oTree8->GetType()), fHeight, false, false);
    p_oTree8->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree8->GetSpecies(), p_oTree8->GetType()), fLight, false, false);

    //Tree 9: Adult, Species 4
    fDiam = 20;
    fHeight = 15;
    fLight = 2;
    p_oTree9 = p_oPop->CreateTree(9, 9, 3, clTreePopulation::adult, fDiam);
    p_oTree9->SetValue(p_oPop->GetHeightCode(p_oTree9->GetSpecies(), p_oTree9->GetType()), fHeight, false, false);
    p_oTree9->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree9->GetSpecies(), p_oTree9->GetType()), fLight, false, false);

    //Tree 10: Adult, Species 4
    fDiam = 20;
    fHeight = 16;
    fLight = 90;
    p_oTree10 = p_oPop->CreateTree(10, 10, 3, clTreePopulation::adult, fDiam);
    p_oTree10->SetValue(p_oPop->GetHeightCode(p_oTree10->GetSpecies(), p_oTree10->GetType()), fHeight, false, false);
    p_oTree10->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree10->GetSpecies(), p_oTree10->GetType()), fLight, false, false);

    //Now run growth, but skip light
    int i;
    for (i = 1; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
      clBehaviorBase *p_oBase = p_oSimManager->GetBehaviorObject(i);
      p_oBase->Action();
    }

    //Confirm all trees
    //Tree 1: Sapling, Species 1
    fExpectedDiam = 5.060392288;
    fExpectedHeight = 7.057976597;
    fExpectedGrowth = 0.100653814;
    p_oTree1->GetValue(p_oPop->GetDiam10Code(p_oTree1->GetSpecies(), p_oTree1->GetType()), &fDiam);
    p_oTree1->GetValue(p_oPop->GetHeightCode(p_oTree1->GetSpecies(), p_oTree1->GetType()), &fHeight);
    p_oTree1->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree1->GetSpecies(), p_oTree1->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Tree 2: Sapling, Species 2
    fExpectedDiam = 3.933537699;
    fExpectedHeight = 7.050848552;
    fExpectedGrowth = -1.777437168;
    p_oTree2->GetValue(p_oPop->GetDiam10Code(p_oTree2->GetSpecies(), p_oTree2->GetType()), &fDiam);
    p_oTree2->GetValue(p_oPop->GetHeightCode(p_oTree2->GetSpecies(), p_oTree2->GetType()), &fHeight);
    p_oTree2->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree2->GetSpecies(), p_oTree2->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Tree 3: Seedling, Species 2
    fExpectedDiam = 0.269662921;
    fExpectedHeight = 0.1;
    fExpectedGrowth = -1.217228464;
    p_oTree3->GetValue(p_oPop->GetDiam10Code(p_oTree3->GetSpecies(), p_oTree3->GetType()), &fDiam);
    p_oTree3->GetValue(p_oPop->GetHeightCode(p_oTree3->GetSpecies(), p_oTree3->GetType()), &fHeight);
    p_oTree3->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree3->GetSpecies(), p_oTree3->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Tree 4: Adult, Species 1
    fExpectedDiam = 19.96654979;
    fExpectedHeight = 14.9678878;
    fExpectedGrowth = -0.055750347;
    p_oTree4->GetValue(p_oPop->GetDbhCode(p_oTree4->GetSpecies(), p_oTree4->GetType()), &fDiam);
    p_oTree4->GetValue(p_oPop->GetHeightCode(p_oTree4->GetSpecies(), p_oTree4->GetType()), &fHeight);
    p_oTree4->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree4->GetSpecies(), p_oTree4->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Tree 5: Seedling, Species 1
    fExpectedDiam = 1.466062161;
    fExpectedHeight = 1.255419675;
    fExpectedGrowth = 0.443436935;
    p_oTree5->GetValue(p_oPop->GetDiam10Code(p_oTree5->GetSpecies(), p_oTree5->GetType()), &fDiam);
    p_oTree5->GetValue(p_oPop->GetHeightCode(p_oTree5->GetSpecies(), p_oTree5->GetType()), &fHeight);
    p_oTree5->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree5->GetSpecies(), p_oTree5->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Tree 6: Sapling, Species 4
    fExpectedDiam = 5.01859692;
    fExpectedHeight = 7.019415184;
    fExpectedGrowth = 0.030994867;
    p_oTree6->GetValue(p_oPop->GetDiam10Code(p_oTree6->GetSpecies(), p_oTree6->GetType()), &fDiam);
    p_oTree6->GetValue(p_oPop->GetHeightCode(p_oTree6->GetSpecies(), p_oTree6->GetType()), &fHeight);
    p_oTree6->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree6->GetSpecies(), p_oTree6->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Tree 7: Sapling, Species 4
    fExpectedDiam = 5.109416249;
    fExpectedHeight = 8.114230564;
    fExpectedGrowth = 0.182360415;
    p_oTree7->GetValue(p_oPop->GetDiam10Code(p_oTree7->GetSpecies(), p_oTree7->GetType()), &fDiam);
    p_oTree7->GetValue(p_oPop->GetHeightCode(p_oTree7->GetSpecies(), p_oTree7->GetType()), &fHeight);
    p_oTree7->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree7->GetSpecies(), p_oTree7->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Tree 8: Sapling, Species 4
    fExpectedDiam = 6.637692635;
    fExpectedHeight = 5.621751111;
    fExpectedGrowth = -0.603845608;
    p_oTree8->GetValue(p_oPop->GetDiam10Code(p_oTree8->GetSpecies(), p_oTree8->GetType()), &fDiam);
    p_oTree8->GetValue(p_oPop->GetHeightCode(p_oTree8->GetSpecies(), p_oTree8->GetType()), &fHeight);
    p_oTree8->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree8->GetSpecies(), p_oTree8->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Tree 9: Adult, Species 4
    fExpectedDiam = 19.57298108;
    fExpectedHeight = 14.55419225;
    fExpectedGrowth = -0.711698201;
    p_oTree9->GetValue(p_oPop->GetDbhCode(p_oTree9->GetSpecies(), p_oTree9->GetType()), &fDiam);
    p_oTree9->GetValue(p_oPop->GetHeightCode(p_oTree9->GetSpecies(), p_oTree9->GetType()), &fHeight);
    p_oTree9->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree9->GetSpecies(), p_oTree9->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Tree 10: Adult, Species 4
    fExpectedDiam = 20.48757992;
    fExpectedHeight = 16.50903343;
    fExpectedGrowth = 0.812633198;
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
// Test2Run1YearPerTimestep()
// Tests height growth with autocorrelation when the timestep length is one
// year. WriteMichMenNegGrowthXMLFile3() is used to set up the run.
////////////////////////////////////////////////////////////////////////////
TEST(MichMenNegGrowth, Test2Run1YearPerTimestep) {
  clTreePopulation * p_oPop;
  clTreeSearch *p_oAllTrees;
  clTree *p_oTree;
  float **p_fStoch,
  fDiam, fHeight, fExpectedDiam, fExpectedHeight, fLight, fGrowth,
  fExpectedGrowth, fExpectedDiamInc, fStochastic, fMean, fStdDev;
  int *p_iCount, iNumTrees = 1000,i,iSp,iCorrelated;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    p_fStoch = new float *[3];
    for (i = 0; i < 3; i++)
      p_fStoch[i] = new float [iNumTrees];
    p_iCount = new int[3];

    //Load our test file and get our tree population pointer
    p_oSimManager->ReadFile( WriteMichMenNegGrowthXMLFile3() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create our trees and set diameter, height, and GLI for each
    for (i = 0; i < iNumTrees; i++) {
      //Adult, Species 1
      fDiam = 20;
      fHeight = 15;
      fLight = 2;
      p_oTree = p_oPop->CreateTree(4, 4, 0, clTreePopulation::adult, fDiam);
      p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), fHeight, false, false);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType()), fLight, false, false);

      //Adult, Species 2
      fDiam = 20;
      fHeight = 15;
      fLight = 2;
      p_oTree = p_oPop->CreateTree(4, 4, 1, clTreePopulation::adult, fDiam);
      p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), fHeight, false, false);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType()), fLight, false, false);

      //Adult, Species 4
      fDiam = 20;
      fHeight = 15;
      fLight = 2;
      p_oTree = p_oPop->CreateTree(4, 4, 3, clTreePopulation::adult, fDiam);
      p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), fHeight, false, false);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType()), fLight, false, false);

      //Adult, Species 5
      fDiam = 20;
      fHeight = 15;
      fLight = 2;
      p_oTree = p_oPop->CreateTree(4, 4, 4, clTreePopulation::adult, fDiam);
      p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), fHeight, false, false);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType()), fLight, false, false);
    }


    //Now run growth, but skip light
    for (i = 1; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
      clBehaviorBase *p_oBase = p_oSimManager->GetBehaviorObject(i);
      p_oBase->Action();
    }

    //Confirm the trees
    for (i = 0; i < 3; i++) p_iCount[i] = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      iSp = p_oTree->GetSpecies();

      if (iSp == 0) {
        fExpectedHeight = 14.98927772;
        fExpectedDiam = 19.98883096;
        fExpectedGrowth = -0.055845199;
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
        p_oTree->GetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fHeight);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), &fGrowth);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("autocorr", p_oTree->GetSpecies(), p_oTree->GetType()), &fStochastic);
        fExpectedDiamInc = (fStochastic/100)/0.96;
        ASSERT_TRUE(fStochastic != 0);
        EXPECT_LT(fabs(fHeight - (fExpectedHeight + (fStochastic/100.0))), 0.001);
        EXPECT_LT(fabs(fDiam - (fExpectedDiam + fExpectedDiamInc)), 0.001);
        EXPECT_LT(fabs(fGrowth - (fExpectedGrowth + (fExpectedDiamInc * 5))), 0.001); //units conversion

        p_fStoch[iSp][p_iCount[iSp]] = fStochastic;
        p_iCount[iSp]++;

      } else if (1 == iSp) {

        //No stochasticity
        fExpectedDiam = 19.64654221;
        fExpectedHeight = 14.66068052;
        fExpectedGrowth = -1.767288971;
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
        p_oTree->GetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fHeight);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), &fGrowth);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("autocorr", p_oTree->GetSpecies(), p_oTree->GetType()), &fStochastic);
        EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
        EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
        EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);
        EXPECT_EQ(fStochastic, 0);
      } else {
        if (3 == iSp) iSp = 1;
        else iSp = 2;

        fExpectedHeight = 15.16;
        fExpectedDiam = 20.16666667;
        fExpectedGrowth = 0.833333333;
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
        p_oTree->GetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fHeight);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), &fGrowth);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("autocorr", p_oTree->GetSpecies(), p_oTree->GetType()), &fStochastic);
        fExpectedDiamInc = (fStochastic/100)/0.96;
        ASSERT_TRUE(fStochastic != 0);
        EXPECT_LT(fabs(fHeight - (fExpectedHeight + (fStochastic/100.0))), 0.001);
        EXPECT_LT(fabs(fDiam - (fExpectedDiam + fExpectedDiamInc)), 0.001);
        EXPECT_LT(fabs(fGrowth - (fExpectedGrowth + (fExpectedDiamInc * 5))), 0.001); //units conversion

        p_fStoch[iSp][p_iCount[iSp]] = fStochastic;
        p_iCount[iSp]++;
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    //Check the mean and sd on the stochasticities
    //Species 1
    fMean = 0;
    for (i = 0; i < iNumTrees; i++) fMean += p_fStoch[0][i];
    fMean /= iNumTrees;
    fStdDev = 0;
    for (i = 0; i < iNumTrees; i++) fStdDev += pow(p_fStoch[0][i] - fMean, 2);
    fStdDev /= iNumTrees;
    fStdDev = sqrt(fStdDev);
    EXPECT_LT(fabs(fMean), 0.15);
    EXPECT_LT(fabs(fStdDev - 4), 0.2);

    //Species 4
    fMean = 0;
    for (i = 0; i < iNumTrees; i++) fMean += p_fStoch[1][i];
    fMean /= iNumTrees;
    fStdDev = 0;
    for (i = 0; i < iNumTrees; i++) fStdDev += pow(p_fStoch[1][i] - fMean, 2);
    fStdDev /= iNumTrees;
    fStdDev = sqrt(fStdDev);
    EXPECT_LT(fabs(fMean), 0.15);
    EXPECT_LT(fabs(fStdDev - 6), 0.25);

    //Species 5
    fMean = 0;
    for (i = 0; i < iNumTrees; i++) fMean += p_fStoch[2][i];
    fMean /= iNumTrees;
    fStdDev = 0;
    for (i = 0; i < iNumTrees; i++) fStdDev += pow(p_fStoch[2][i] - fMean, 2);
    fStdDev /= iNumTrees;
    fStdDev = sqrt(fStdDev);
    EXPECT_LT(fabs(fMean), 0.15);
    EXPECT_LT(fabs(fStdDev - 6), 0.25);

    //****************************************************************
    //Run another timestep
    for (i = 1; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
      clBehaviorBase *p_oBase = p_oSimManager->GetBehaviorObject(i);
      p_oBase->Action();
    }

    iCorrelated = 0;
    //Confirm the trees
    for (i = 0; i < 3; i++) p_iCount[i] = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      iSp = p_oTree->GetSpecies();
      p_oTree->GetValue(p_oPop->GetFloatDataCode("autocorr", p_oTree->GetSpecies(), p_oTree->GetType()), &fStochastic);

      if (iSp == 0 || iSp == 3) {
        if (3 == iSp) iSp = 1;
        //Autocorrelation 100%
        EXPECT_EQ(fStochastic, p_fStoch[iSp][p_iCount[iSp]]);
        p_iCount[iSp]++;

      } else if (1 == iSp) {

        //No stochasticity
        EXPECT_EQ(fStochastic, 0);

      } else {
        iSp = 2;
        //Count the autocorrelations
        if (fStochastic == p_fStoch[iSp][p_iCount[iSp]]) iCorrelated++;
        p_iCount[iSp]++;
      }
      p_oTree = p_oAllTrees->NextTree();
    }
    //Make sure species 5 autocorrelated correctly
    EXPECT_LT(fabs(750 - iCorrelated), 50);

    for (i = 0; i < 3; i++)
      delete[] p_fStoch[i];
    delete[] p_fStoch;
    delete[] p_iCount;
    delete p_oSimManager;
  } catch (modelErr &e) {
    for (int i = 0; i < 3; i++)
      delete[] p_fStoch[i];
    delete[] p_fStoch;
    delete[] p_iCount;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}



////////////////////////////////////////////////////////////////////////////
// TestErrorProcessing()
////////////////////////////////////////////////////////////////////////////
TEST(MichMenNegGrowth, TestErrorProcessing)
{
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try
  {
    p_oSimManager->ReadFile( WriteMichMenNegGrowthXMLErrorFile1() );
    FAIL() << "TestMichMenNegGrowth error processing didn't catch error for WriteMichMenNegGrowthXMLErrorFile1.";
  }
  catch ( modelErr& err )
  {
    if ( err.sFunction.compare("clMichMenNegGrowth::DoShellSetup" ) != 0 )
    {
      FAIL() << "TestMichMenNegGrowth error processing caught wrong error for WriteMichMenNegGrowthXMLErrorFile1.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile( WriteMichMenNegGrowthXMLErrorFile2() );
    FAIL() << "TestMichMenNegGrowth error processing didn't catch error for WriteMichMenNegGrowthXMLErrorFile1.";
  }
  catch ( modelErr& err )
  {
    if ( err.sFunction.compare("clMichMenNegGrowth::DoShellSetup" ) != 0 )
    {
      FAIL() << "TestMichMenNegGrowth error processing caught wrong error for WriteMichMenNegGrowthXMLErrorFile1.";
    }
    ;
  }
  delete p_oSimManager;
}


////////////////////////////////////////////////////////////////////////////
// WriteMichMenNegGrowthXMLFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteMichMenNegGrowthXMLFile1() {
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
       << "<yearsPerTimestep>1</yearsPerTimestep>";

  WriteMichMenNegGrowthRun1CommonStuff(oOut);

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteMichMenNegGrowthXMLFile2()
////////////////////////////////////////////////////////////////////////////
const char* WriteMichMenNegGrowthXMLFile2() {
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
       << "<yearsPerTimestep>3</yearsPerTimestep>";

  WriteMichMenNegGrowthRun1CommonStuff(oOut);

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteMichMenNegGrowthXMLFile3()
////////////////////////////////////////////////////////////////////////////
const char* WriteMichMenNegGrowthXMLFile3() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //Write file
  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>5</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>";

  WriteMichMenNegGrowthRun2CommonStuff(oOut);

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteMichMenNegGrowthCommonStuff()
/////////////////////////////////////////////////////////////////////////////
void WriteMichMenNegGrowthRun1CommonStuff(std::fstream &oOut)
{
  oOut << "<randomSeed>1</randomSeed>"
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
       << "<tr_species speciesName=\"Species_3\" />"
       << "<tr_species speciesName=\"Species_4\" />"
       << "</tr_speciesList>"
       << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
       << "<tr_minAdultDBH>"
       << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_2\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_3\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_4\">10.0</tr_madVal>"
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
       << "<tr_chVal species=\"Species_2\">39.54</tr_chVal>"
       << "<tr_chVal species=\"Species_3\">45.0</tr_chVal>"
       << "<tr_chVal species=\"Species_4\">45.0</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_2\">0.0614</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_3\">0.0242</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_4\">0.0242</tr_sacrVal>"
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
       << "</tr_stdMaxCrownRad>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">1</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">1</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_3\">1</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_4\">1</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_3\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_4\">0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_2\">0.368</tr_sachVal>"
       << "<tr_sachVal species=\"Species_3\">0.464</tr_sachVal>"
       << "<tr_sachVal species=\"Species_4\">0.464</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_3\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_4\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_2\">0.0269</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_3\">0.02871</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_4\">0.02871</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "<tr_adultLinearSlope>"
       << "<tr_alsVal species=\"Species_1\">0.96</tr_alsVal>"
       << "<tr_alsVal species=\"Species_2\">0.89</tr_alsVal>"
       << "<tr_alsVal species=\"Species_3\">0.858</tr_alsVal>"
       << "<tr_alsVal species=\"Species_4\">1.044</tr_alsVal>"
       << "</tr_adultLinearSlope>"
       << "<tr_adultLinearIntercept>"
       << "<tr_aliVal species=\"Species_1\">-0.258</tr_aliVal>"
       << "<tr_aliVal species=\"Species_2\">-0.33</tr_aliVal>"
       << "<tr_aliVal species=\"Species_3\">0.027</tr_aliVal>"
       << "<tr_aliVal species=\"Species_4\">0.015</tr_aliVal>"
       << "</tr_adultLinearIntercept>"
       << "<tr_saplingLinearSlope>"
       << "<tr_salsVal species=\"Species_1\">0.96</tr_salsVal>"
       << "<tr_salsVal species=\"Species_2\">0.89</tr_salsVal>"
       << "<tr_salsVal species=\"Species_3\">0.858</tr_salsVal>"
       << "<tr_salsVal species=\"Species_4\">1.044</tr_salsVal>"
       << "</tr_saplingLinearSlope>"
       << "<tr_saplingLinearIntercept>"
       << "<tr_saliVal species=\"Species_1\">-0.258</tr_saliVal>"
       << "<tr_saliVal species=\"Species_2\">-0.33</tr_saliVal>"
       << "<tr_saliVal species=\"Species_3\">0.027</tr_saliVal>"
       << "<tr_saliVal species=\"Species_4\">0.015</tr_saliVal>"
       << "</tr_saplingLinearIntercept>"
       << "<tr_seedlingLinearSlope>"
       << "<tr_selsVal species=\"Species_1\">0.96</tr_selsVal>"
       << "<tr_selsVal species=\"Species_2\">0.89</tr_selsVal>"
       << "<tr_selsVal species=\"Species_3\">0.858</tr_selsVal>"
       << "<tr_selsVal species=\"Species_4\">1.044</tr_selsVal>"
       << "</tr_seedlingLinearSlope>"
       << "<tr_seedlingLinearIntercept>"
       << "<tr_seliVal species=\"Species_1\">-0.258</tr_seliVal>"
       << "<tr_seliVal species=\"Species_2\">-0.33</tr_seliVal>"
       << "<tr_seliVal species=\"Species_3\">0.027</tr_seliVal>"
       << "<tr_seliVal species=\"Species_4\">0.015</tr_seliVal>"
       << "</tr_seedlingLinearIntercept>"
       << "<tr_whatSeedlingHeightDiam>"
       << "<tr_wsehdVal species=\"Species_1\">1</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_2\">1</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_3\">1</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_4\">1</tr_wsehdVal>"
       << "</tr_whatSeedlingHeightDiam>"
       << "<tr_whatSaplingHeightDiam>"
       << "<tr_wsahdVal species=\"Species_1\">1</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_2\">1</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_3\">1</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_4\">1</tr_wsahdVal>"
       << "</tr_whatSaplingHeightDiam>"
       << "<tr_whatAdultHeightDiam>"
       << "<tr_wahdVal species=\"Species_1\">1</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_2\">1</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_3\">1</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_4\">1</tr_wahdVal>"
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
       //Leave in one light so that "Light" will be registerd
       << "<behaviorName>ConstantGLI</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>MichaelisMentenNegativeGrowth height only</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>DiameterIncrementer</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<ConstantGLI1>"
       << "<li_constGLI>100</li_constGLI>"
       << "</ConstantGLI1>"
       << "<MichaelisMentenNegativeGrowth2>"
       << "<gr_mmNegGrowthAlpha>"
       << "<gr_mmngaVal species=\"Species_1\">53.97788</gr_mmngaVal>"
       << "<gr_mmngaVal species=\"Species_2\">15.98</gr_mmngaVal>"
       << "<gr_mmngaVal species=\"Species_4\">2.088</gr_mmngaVal>"
       << "</gr_mmNegGrowthAlpha>"
       << "<gr_mmNegGrowthBeta>"
       << "<gr_mmngbVal species=\"Species_1\">498.31</gr_mmngbVal>"
       << "<gr_mmngbVal species=\"Species_2\">0.019</gr_mmngbVal>"
       << "<gr_mmngbVal species=\"Species_4\">0.015</gr_mmngbVal>"
       << "</gr_mmNegGrowthBeta>"
       << "<gr_mmNegGrowthGamma>"
       << "<gr_mmnggVal species=\"Species_1\">17.18377</gr_mmnggVal>"
       << "<gr_mmnggVal species=\"Species_2\">34</gr_mmnggVal>"
       << "<gr_mmnggVal species=\"Species_4\">16</gr_mmnggVal>"
       << "</gr_mmNegGrowthGamma>"
       << "<gr_mmNegGrowthPhi>"
       << "<gr_mmngpVal species=\"Species_1\">-0.15811</gr_mmngpVal>"
       << "<gr_mmngpVal species=\"Species_2\">0.08</gr_mmngpVal>"
       << "<gr_mmngpVal species=\"Species_4\">0.5</gr_mmngpVal>"
       << "</gr_mmNegGrowthPhi>"
       << "<gr_mmNegGrowthStdDev>"
       << "<gr_mmngsdVal species=\"Species_1\">0</gr_mmngsdVal>"
       << "<gr_mmngsdVal species=\"Species_2\">0</gr_mmngsdVal>"
       << "<gr_mmngsdVal species=\"Species_4\">0</gr_mmngsdVal>"
       << "</gr_mmNegGrowthStdDev>"
       << "<gr_mmNegGrowthAutoCorrProb>"
       << "<gr_mmngacpVal species=\"Species_1\">0</gr_mmngacpVal>"
       << "<gr_mmngacpVal species=\"Species_2\">0</gr_mmngacpVal>"
       << "<gr_mmngacpVal species=\"Species_4\">0</gr_mmngacpVal>"
       << "</gr_mmNegGrowthAutoCorrProb>"
       << "</MichaelisMentenNegativeGrowth2>"
       << "</paramFile>";
}

void WriteMichMenNegGrowthRun2CommonStuff(std::fstream &oOut)
{
  oOut << "<randomSeed>1</randomSeed>"
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
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_2\">39.54</tr_chVal>"
       << "<tr_chVal species=\"Species_3\">45.0</tr_chVal>"
       << "<tr_chVal species=\"Species_4\">45.0</tr_chVal>"
       << "<tr_chVal species=\"Species_5\">45.0</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_2\">0.0614</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_3\">0.0242</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_4\">0.0242</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_5\">0.0242</tr_sacrVal>"
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
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">1</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">1</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_3\">1</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_4\">1</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_5\">1</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_3\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_4\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_5\">0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_2\">0.368</tr_sachVal>"
       << "<tr_sachVal species=\"Species_3\">0.464</tr_sachVal>"
       << "<tr_sachVal species=\"Species_4\">0.464</tr_sachVal>"
       << "<tr_sachVal species=\"Species_5\">0.464</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_3\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_4\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_5\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_2\">0.0269</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_3\">0.02871</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_4\">0.02871</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_5\">0.02871</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "<tr_adultLinearSlope>"
       << "<tr_alsVal species=\"Species_1\">0.96</tr_alsVal>"
       << "<tr_alsVal species=\"Species_2\">0.96</tr_alsVal>"
       << "<tr_alsVal species=\"Species_3\">0.96</tr_alsVal>"
       << "<tr_alsVal species=\"Species_4\">0.96</tr_alsVal>"
       << "<tr_alsVal species=\"Species_5\">0.96</tr_alsVal>"
       << "</tr_adultLinearSlope>"
       << "<tr_adultLinearIntercept>"
       << "<tr_aliVal species=\"Species_1\">-0.258</tr_aliVal>"
       << "<tr_aliVal species=\"Species_2\">-0.258</tr_aliVal>"
       << "<tr_aliVal species=\"Species_3\">-0.258</tr_aliVal>"
       << "<tr_aliVal species=\"Species_4\">-0.258</tr_aliVal>"
       << "<tr_aliVal species=\"Species_5\">-0.258</tr_aliVal>"
       << "</tr_adultLinearIntercept>"
       << "<tr_saplingLinearSlope>"
       << "<tr_salsVal species=\"Species_1\">0.96</tr_salsVal>"
       << "<tr_salsVal species=\"Species_2\">0.89</tr_salsVal>"
       << "<tr_salsVal species=\"Species_3\">0.858</tr_salsVal>"
       << "<tr_salsVal species=\"Species_4\">1.044</tr_salsVal>"
       << "<tr_salsVal species=\"Species_5\">1.044</tr_salsVal>"
       << "</tr_saplingLinearSlope>"
       << "<tr_saplingLinearIntercept>"
       << "<tr_saliVal species=\"Species_1\">-0.258</tr_saliVal>"
       << "<tr_saliVal species=\"Species_2\">-0.33</tr_saliVal>"
       << "<tr_saliVal species=\"Species_3\">0.027</tr_saliVal>"
       << "<tr_saliVal species=\"Species_4\">0.015</tr_saliVal>"
       << "<tr_saliVal species=\"Species_5\">0.015</tr_saliVal>"
       << "</tr_saplingLinearIntercept>"
       << "<tr_seedlingLinearSlope>"
       << "<tr_selsVal species=\"Species_1\">0.96</tr_selsVal>"
       << "<tr_selsVal species=\"Species_2\">0.89</tr_selsVal>"
       << "<tr_selsVal species=\"Species_3\">0.858</tr_selsVal>"
       << "<tr_selsVal species=\"Species_4\">1.044</tr_selsVal>"
       << "<tr_selsVal species=\"Species_5\">1.044</tr_selsVal>"
       << "</tr_seedlingLinearSlope>"
       << "<tr_seedlingLinearIntercept>"
       << "<tr_seliVal species=\"Species_1\">-0.258</tr_seliVal>"
       << "<tr_seliVal species=\"Species_2\">-0.33</tr_seliVal>"
       << "<tr_seliVal species=\"Species_3\">0.027</tr_seliVal>"
       << "<tr_seliVal species=\"Species_4\">0.015</tr_seliVal>"
       << "<tr_seliVal species=\"Species_5\">0.015</tr_seliVal>"
       << "</tr_seedlingLinearIntercept>"
       << "<tr_whatSeedlingHeightDiam>"
       << "<tr_wsehdVal species=\"Species_1\">1</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_2\">1</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_3\">1</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_4\">1</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_5\">1</tr_wsehdVal>"
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
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_5\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>MichaelisMentenNegativeGrowth height only</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_5\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>DiameterIncrementer</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_5\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<ConstantGLI1>"
       << "<li_constGLI>100</li_constGLI>"
       << "</ConstantGLI1>"
       << "<MichaelisMentenNegativeGrowth2>"
       << "<gr_mmNegGrowthAlpha>"
       << "<gr_mmngaVal species=\"Species_1\">53.97788</gr_mmngaVal>"
       << "<gr_mmngaVal species=\"Species_2\">15.98</gr_mmngaVal>"
       << "<gr_mmngaVal species=\"Species_4\">0</gr_mmngaVal>"
       << "<gr_mmngaVal species=\"Species_5\">0</gr_mmngaVal>"
       << "</gr_mmNegGrowthAlpha>"
       << "<gr_mmNegGrowthBeta>"
       << "<gr_mmngbVal species=\"Species_1\">498.31</gr_mmngbVal>"
       << "<gr_mmngbVal species=\"Species_2\">0.019</gr_mmngbVal>"
       << "<gr_mmngbVal species=\"Species_4\">0.015</gr_mmngbVal>"
       << "<gr_mmngbVal species=\"Species_5\">0.015</gr_mmngbVal>"
       << "</gr_mmNegGrowthBeta>"
       << "<gr_mmNegGrowthGamma>"
       << "<gr_mmnggVal species=\"Species_1\">17.18377</gr_mmnggVal>"
       << "<gr_mmnggVal species=\"Species_2\">34</gr_mmnggVal>"
       << "<gr_mmnggVal species=\"Species_4\">-16</gr_mmnggVal>"
       << "<gr_mmnggVal species=\"Species_5\">-16</gr_mmnggVal>"
       << "</gr_mmNegGrowthGamma>"
       << "<gr_mmNegGrowthPhi>"
       << "<gr_mmngpVal species=\"Species_1\">-0.15811</gr_mmngpVal>"
       << "<gr_mmngpVal species=\"Species_2\">0.08</gr_mmngpVal>"
       << "<gr_mmngpVal species=\"Species_4\">0.5</gr_mmngpVal>"
       << "<gr_mmngpVal species=\"Species_5\">0.5</gr_mmngpVal>"
       << "</gr_mmNegGrowthPhi>"
       << "<gr_mmNegGrowthStdDev>"
       << "<gr_mmngsdVal species=\"Species_1\">4</gr_mmngsdVal>"
       << "<gr_mmngsdVal species=\"Species_2\">0</gr_mmngsdVal>"
       << "<gr_mmngsdVal species=\"Species_4\">6</gr_mmngsdVal>"
       << "<gr_mmngsdVal species=\"Species_5\">6</gr_mmngsdVal>"
       << "</gr_mmNegGrowthStdDev>"
       << "<gr_mmNegGrowthAutoCorrProb>"
       << "<gr_mmngacpVal species=\"Species_1\">1</gr_mmngacpVal>"
       << "<gr_mmngacpVal species=\"Species_2\">0</gr_mmngacpVal>"
       << "<gr_mmngacpVal species=\"Species_4\">1</gr_mmngacpVal>"
       << "<gr_mmngacpVal species=\"Species_5\">0.75</gr_mmngacpVal>"
       << "</gr_mmNegGrowthAutoCorrProb>"
       << "</MichaelisMentenNegativeGrowth2>"
       << "</paramFile>";
}


////////////////////////////////////////////////////////////////////////////
// WriteMichMenNegGrowthXMLErrorFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteMichMenNegGrowthXMLErrorFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteMichMenNegGrowthErrorCommonStuff(oOut);

  oOut << "<gr_mmNegGrowthBeta>"
       << "<gr_mmngbVal species=\"Species_1\">498.31</gr_mmngbVal>"
       << "<gr_mmngbVal species=\"Species_2\">0.019</gr_mmngbVal>"
       << "<gr_mmngbVal species=\"Species_4\">0</gr_mmngbVal>"
       << "</gr_mmNegGrowthBeta>"
       << "<gr_mmNegGrowthAutoCorrProb>"
       << "<gr_mmngacpVal species=\"Species_1\">0</gr_mmngacpVal>"
       << "<gr_mmngacpVal species=\"Species_2\">0</gr_mmngacpVal>"
       << "<gr_mmngacpVal species=\"Species_4\">0</gr_mmngacpVal>"
       << "</gr_mmNegGrowthAutoCorrProb>"
       << "</MichaelisMentenNegativeGrowth2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteMichMenNegGrowthXMLErrorFile2()
////////////////////////////////////////////////////////////////////////////
const char* WriteMichMenNegGrowthXMLErrorFile2() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteMichMenNegGrowthErrorCommonStuff(oOut);

  oOut << "<gr_mmNegGrowthBeta>"
       << "<gr_mmngbVal species=\"Species_1\">498.31</gr_mmngbVal>"
       << "<gr_mmngbVal species=\"Species_2\">0.019</gr_mmngbVal>"
       << "<gr_mmngbVal species=\"Species_4\">0.019</gr_mmngbVal>"
       << "</gr_mmNegGrowthBeta>"
       << "<gr_mmNegGrowthAutoCorrProb>"
       << "<gr_mmngacpVal species=\"Species_1\">10</gr_mmngacpVal>"
       << "<gr_mmngacpVal species=\"Species_2\">0</gr_mmngacpVal>"
       << "<gr_mmngacpVal species=\"Species_4\">0</gr_mmngacpVal>"
       << "</gr_mmNegGrowthAutoCorrProb>"
       << "</MichaelisMentenNegativeGrowth2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteMichMenNegGrowthErrorCommonStuff()
////////////////////////////////////////////////////////////////////////////
void WriteMichMenNegGrowthErrorCommonStuff(std::fstream &oOut) {
  using namespace std;


  //Write file
  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>1</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>";

  oOut << "<randomSeed>1</randomSeed>"
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
       << "<tr_species speciesName=\"Species_3\" />"
       << "<tr_species speciesName=\"Species_4\" />"
       << "</tr_speciesList>"
       << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
       << "<tr_minAdultDBH>"
       << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_2\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_3\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_4\">10.0</tr_madVal>"
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
       << "<tr_chVal species=\"Species_2\">39.54</tr_chVal>"
       << "<tr_chVal species=\"Species_3\">45.0</tr_chVal>"
       << "<tr_chVal species=\"Species_4\">45.0</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_2\">0.0614</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_3\">0.0242</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_4\">0.0242</tr_sacrVal>"
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
       << "</tr_stdMaxCrownRad>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">1</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">1</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_3\">1</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_4\">1</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_3\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_4\">0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_2\">0.368</tr_sachVal>"
       << "<tr_sachVal species=\"Species_3\">0.464</tr_sachVal>"
       << "<tr_sachVal species=\"Species_4\">0.464</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_3\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_4\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_2\">0.0269</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_3\">0.02871</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_4\">0.02871</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "<tr_adultLinearSlope>"
       << "<tr_alsVal species=\"Species_1\">0.96</tr_alsVal>"
       << "<tr_alsVal species=\"Species_2\">0.89</tr_alsVal>"
       << "<tr_alsVal species=\"Species_3\">0.858</tr_alsVal>"
       << "<tr_alsVal species=\"Species_4\">1.044</tr_alsVal>"
       << "</tr_adultLinearSlope>"
       << "<tr_adultLinearIntercept>"
       << "<tr_aliVal species=\"Species_1\">-0.258</tr_aliVal>"
       << "<tr_aliVal species=\"Species_2\">-0.33</tr_aliVal>"
       << "<tr_aliVal species=\"Species_3\">0.027</tr_aliVal>"
       << "<tr_aliVal species=\"Species_4\">0.015</tr_aliVal>"
       << "</tr_adultLinearIntercept>"
       << "<tr_saplingLinearSlope>"
       << "<tr_salsVal species=\"Species_1\">0.96</tr_salsVal>"
       << "<tr_salsVal species=\"Species_2\">0.89</tr_salsVal>"
       << "<tr_salsVal species=\"Species_3\">0.858</tr_salsVal>"
       << "<tr_salsVal species=\"Species_4\">1.044</tr_salsVal>"
       << "</tr_saplingLinearSlope>"
       << "<tr_saplingLinearIntercept>"
       << "<tr_saliVal species=\"Species_1\">-0.258</tr_saliVal>"
       << "<tr_saliVal species=\"Species_2\">-0.33</tr_saliVal>"
       << "<tr_saliVal species=\"Species_3\">0.027</tr_saliVal>"
       << "<tr_saliVal species=\"Species_4\">0.015</tr_saliVal>"
       << "</tr_saplingLinearIntercept>"
       << "<tr_seedlingLinearSlope>"
       << "<tr_selsVal species=\"Species_1\">0.96</tr_selsVal>"
       << "<tr_selsVal species=\"Species_2\">0.89</tr_selsVal>"
       << "<tr_selsVal species=\"Species_3\">0.858</tr_selsVal>"
       << "<tr_selsVal species=\"Species_4\">1.044</tr_selsVal>"
       << "</tr_seedlingLinearSlope>"
       << "<tr_seedlingLinearIntercept>"
       << "<tr_seliVal species=\"Species_1\">-0.258</tr_seliVal>"
       << "<tr_seliVal species=\"Species_2\">-0.33</tr_seliVal>"
       << "<tr_seliVal species=\"Species_3\">0.027</tr_seliVal>"
       << "<tr_seliVal species=\"Species_4\">0.015</tr_seliVal>"
       << "</tr_seedlingLinearIntercept>"
       << "<tr_whatSeedlingHeightDiam>"
       << "<tr_wsehdVal species=\"Species_1\">1</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_2\">1</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_3\">1</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_4\">1</tr_wsehdVal>"
       << "</tr_whatSeedlingHeightDiam>"
       << "<tr_whatSaplingHeightDiam>"
       << "<tr_wsahdVal species=\"Species_1\">1</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_2\">1</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_3\">1</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_4\">1</tr_wsahdVal>"
       << "</tr_whatSaplingHeightDiam>"
       << "<tr_whatAdultHeightDiam>"
       << "<tr_wahdVal species=\"Species_1\">1</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_2\">1</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_3\">1</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_4\">1</tr_wahdVal>"
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
       //Leave in one light so that "Light" will be registerd
       << "<behaviorName>ConstantGLI</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>MichaelisMentenNegativeGrowth height only</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>DiameterIncrementer</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<ConstantGLI1>"
       << "<li_constGLI>100</li_constGLI>"
       << "</ConstantGLI1>"
       << "<MichaelisMentenNegativeGrowth2>"
       << "<gr_mmNegGrowthAlpha>"
       << "<gr_mmngaVal species=\"Species_1\">26.98894</gr_mmngaVal>"
       << "<gr_mmngaVal species=\"Species_2\">7.99</gr_mmngaVal>"
       << "<gr_mmngaVal species=\"Species_4\">1.044</gr_mmngaVal>"
       << "</gr_mmNegGrowthAlpha>"
       << "<gr_mmNegGrowthGamma>"
       << "<gr_mmnggVal species=\"Species_1\">17.18377</gr_mmnggVal>"
       << "<gr_mmnggVal species=\"Species_2\">34</gr_mmnggVal>"
       << "<gr_mmnggVal species=\"Species_4\">16</gr_mmnggVal>"
       << "</gr_mmNegGrowthGamma>"
       << "<gr_mmNegGrowthPhi>"
       << "<gr_mmngpVal species=\"Species_1\">-0.15811</gr_mmngpVal>"
       << "<gr_mmngpVal species=\"Species_2\">0.08</gr_mmngpVal>"
       << "<gr_mmngpVal species=\"Species_4\">0.5</gr_mmngpVal>"
       << "</gr_mmNegGrowthPhi>"
       << "<gr_mmNegGrowthStdDev>"
       << "<gr_mmngsdVal species=\"Species_1\">0</gr_mmngsdVal>"
       << "<gr_mmngsdVal species=\"Species_2\">0</gr_mmngsdVal>"
       << "<gr_mmngsdVal species=\"Species_4\">0</gr_mmngsdVal>"
       << "</gr_mmNegGrowthStdDev>";
}
