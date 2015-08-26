//---------------------------------------------------------------------------
// TestMichMenPhotoinhibition.cpp
//---------------------------------------------------------------------------
#include "TestMichMenPhotoinhibition.h"
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
// WriteMichMenPhotoinhibitionXMLFile1() is used to set up the run. 10 trees are
// created of four species. GLIs are assigned to them, and then growth is run.
// Their diameters, heights, and "Growth" values are checked to make sure they
// are correct.
////////////////////////////////////////////////////////////////////////////
TEST(MichMenPhotoinhibition, Test1Run1YearPerTimestep) {

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTree *p_oTree1, *p_oTree2, *p_oTree3, *p_oTree4, *p_oTree5, *p_oTree6,
    *p_oTree7, *p_oTree8, *p_oTree9, *p_oTree10;
    float fDiam, fHeight, fExpectedDiam, fExpectedHeight, fLight, fGrowth, fExpectedGrowth;

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteMichMenPhotoinhibitionXMLFile1() );
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
    fExpectedDiam = 5.156989381;
    fExpectedHeight = 7.150709805;
    fExpectedGrowth = 0.784946903;
    p_oTree1->GetValue(p_oPop->GetDiam10Code(p_oTree1->GetSpecies(), p_oTree1->GetType()), &fDiam);
    p_oTree1->GetValue(p_oPop->GetHeightCode(p_oTree1->GetSpecies(), p_oTree1->GetType()), &fHeight);
    p_oTree1->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree1->GetSpecies(), p_oTree1->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Tree 2: Sapling, Species 2
    fExpectedDiam = 5.019891122;
    fExpectedHeight = 8.017703099;
    fExpectedGrowth = 0.099455612;
    p_oTree2->GetValue(p_oPop->GetDiam10Code(p_oTree2->GetSpecies(), p_oTree2->GetType()), &fDiam);
    p_oTree2->GetValue(p_oPop->GetHeightCode(p_oTree2->GetSpecies(), p_oTree2->GetType()), &fHeight);
    p_oTree2->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree2->GetSpecies(), p_oTree2->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Tree 3: Seedling, Species 2
    fExpectedDiam = 1.002469378;
    fExpectedHeight = 0.752197747;
    fExpectedGrowth = 0.012346892;
    p_oTree3->GetValue(p_oPop->GetDiam10Code(p_oTree3->GetSpecies(), p_oTree3->GetType()), &fDiam);
    p_oTree3->GetValue(p_oPop->GetHeightCode(p_oTree3->GetSpecies(), p_oTree3->GetType()), &fHeight);
    p_oTree3->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree3->GetSpecies(), p_oTree3->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Tree 4: Adult, Species 1
    fExpectedDiam = 23.98585272;
    fExpectedHeight = 18.82641861;
    fExpectedGrowth = 19.92926358;
    p_oTree4->GetValue(p_oPop->GetDbhCode(p_oTree4->GetSpecies(), p_oTree4->GetType()), &fDiam);
    p_oTree4->GetValue(p_oPop->GetHeightCode(p_oTree4->GetSpecies(), p_oTree4->GetType()), &fHeight);
    p_oTree4->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree4->GetSpecies(), p_oTree4->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Tree 5: Seedling, Species 1
    fExpectedDiam = 1.06948252;
    fExpectedHeight = 0.874703219;
    fExpectedGrowth = -0.652587402;
    p_oTree5->GetValue(p_oPop->GetDiam10Code(p_oTree5->GetSpecies(), p_oTree5->GetType()), &fDiam);
    p_oTree5->GetValue(p_oPop->GetHeightCode(p_oTree5->GetSpecies(), p_oTree5->GetType()), &fHeight);
    p_oTree5->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree5->GetSpecies(), p_oTree5->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Tree 6: Sapling, Species 4
    fExpectedDiam = 5.070029624;
    fExpectedHeight = 7.073110928;
    fExpectedGrowth = 0.350148122;
    p_oTree6->GetValue(p_oPop->GetDiam10Code(p_oTree6->GetSpecies(), p_oTree6->GetType()), &fDiam);
    p_oTree6->GetValue(p_oPop->GetHeightCode(p_oTree6->GetSpecies(), p_oTree6->GetType()), &fHeight);
    p_oTree6->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree6->GetSpecies(), p_oTree6->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Tree 7: Sapling, Species 4
    fExpectedDiam = 5.076398879;
    fExpectedHeight = 8.079760429;
    fExpectedGrowth = 0.381994393;
    p_oTree7->GetValue(p_oPop->GetDiam10Code(p_oTree7->GetSpecies(), p_oTree7->GetType()), &fDiam);
    p_oTree7->GetValue(p_oPop->GetHeightCode(p_oTree7->GetSpecies(), p_oTree7->GetType()), &fHeight);
    p_oTree7->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree7->GetSpecies(), p_oTree7->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Tree 8: Sapling, Species 4
    fExpectedDiam = 7.022677906;
    fExpectedHeight = 6.023675734;
    fExpectedGrowth = 0.11338953;
    p_oTree8->GetValue(p_oPop->GetDiam10Code(p_oTree8->GetSpecies(), p_oTree8->GetType()), &fDiam);
    p_oTree8->GetValue(p_oPop->GetHeightCode(p_oTree8->GetSpecies(), p_oTree8->GetType()), &fHeight);
    p_oTree8->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree8->GetSpecies(), p_oTree8->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Tree 9: Adult, Species 4
    fExpectedDiam = 20.00825866;
    fExpectedHeight = 15.00862204;
    fExpectedGrowth = 0.041293294;
    p_oTree9->GetValue(p_oPop->GetDbhCode(p_oTree9->GetSpecies(), p_oTree9->GetType()), &fDiam);
    p_oTree9->GetValue(p_oPop->GetHeightCode(p_oTree9->GetSpecies(), p_oTree9->GetType()), &fHeight);
    p_oTree9->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree9->GetSpecies(), p_oTree9->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Tree 10: Adult, Species 4
    fExpectedDiam = 20.10659839;
    fExpectedHeight = 16.11128872;
    fExpectedGrowth = 0.532991963;
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
// Test1Run3YearsPerTimestep()
// Tests height growth when the timestep length is three years.
// WriteMichMenPhotoinhibitionXMLFile2() is used to set up the run. 10 trees are
// created of four species. GLIs are assigned to them, and then growth is run.
// Their diameters, heights, and "Growth" values are checked to make sure they
// are correct.
////////////////////////////////////////////////////////////////////////////
TEST(MichMenPhotoinhibition, Test1Run3YearsPerTimestep) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTree *p_oTree1, *p_oTree2, *p_oTree3, *p_oTree4, *p_oTree5, *p_oTree6,
    *p_oTree7, *p_oTree8, *p_oTree9, *p_oTree10;
    float fDiam, fHeight, fExpectedDiam, fExpectedHeight, fLight, fGrowth, fExpectedGrowth;

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteMichMenPhotoinhibitionXMLFile2() );
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
    fExpectedDiam = 5.479667098;
    fExpectedHeight = 7.460480414;
    fExpectedGrowth = 0.799445163;
    p_oTree1->GetValue(p_oPop->GetDiam10Code(p_oTree1->GetSpecies(), p_oTree1->GetType()), &fDiam);
    p_oTree1->GetValue(p_oPop->GetHeightCode(p_oTree1->GetSpecies(), p_oTree1->GetType()), &fHeight);
    p_oTree1->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree1->GetSpecies(), p_oTree1->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Tree 2: Sapling, Species 2
    fExpectedDiam = 5.059683914;
    fExpectedHeight = 8.053118683;
    fExpectedGrowth = 0.09947319;
    p_oTree2->GetValue(p_oPop->GetDiam10Code(p_oTree2->GetSpecies(), p_oTree2->GetType()), &fDiam);
    p_oTree2->GetValue(p_oPop->GetHeightCode(p_oTree2->GetSpecies(), p_oTree2->GetType()), &fHeight);
    p_oTree2->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree2->GetSpecies(), p_oTree2->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Tree 3: Seedling, Species 2
    fExpectedDiam = 1.007409868;
    fExpectedHeight = 0.756594782;
    fExpectedGrowth = 0.01234978;
    p_oTree3->GetValue(p_oPop->GetDiam10Code(p_oTree3->GetSpecies(), p_oTree3->GetType()), &fDiam);
    p_oTree3->GetValue(p_oPop->GetHeightCode(p_oTree3->GetSpecies(), p_oTree3->GetType()), &fHeight);
    p_oTree3->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree3->GetSpecies(), p_oTree3->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Tree 4: Adult, Species 1
    fExpectedDiam = 34.67113499;
    fExpectedHeight = 29.08428959;
    fExpectedGrowth = 24.45189166;
    p_oTree4->GetValue(p_oPop->GetDbhCode(p_oTree4->GetSpecies(), p_oTree4->GetType()), &fDiam);
    p_oTree4->GetValue(p_oPop->GetHeightCode(p_oTree4->GetSpecies(), p_oTree4->GetType()), &fHeight);
    p_oTree4->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree4->GetSpecies(), p_oTree4->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Tree 5: Seedling, Species 1
    fExpectedDiam = 0.849512277;
    fExpectedHeight = 0.663531786;
    fExpectedGrowth = -0.584146205;
    p_oTree5->GetValue(p_oPop->GetDiam10Code(p_oTree5->GetSpecies(), p_oTree5->GetType()), &fDiam);
    p_oTree5->GetValue(p_oPop->GetHeightCode(p_oTree5->GetSpecies(), p_oTree5->GetType()), &fHeight);
    p_oTree5->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree5->GetSpecies(), p_oTree5->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Tree 6: Sapling, Species 4
    fExpectedDiam = 5.211183156;
    fExpectedHeight = 7.220475215;
    fExpectedGrowth = 0.351971927;
    p_oTree6->GetValue(p_oPop->GetDiam10Code(p_oTree6->GetSpecies(), p_oTree6->GetType()), &fDiam);
    p_oTree6->GetValue(p_oPop->GetHeightCode(p_oTree6->GetSpecies(), p_oTree6->GetType()), &fHeight);
    p_oTree6->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree6->GetSpecies(), p_oTree6->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Tree 7: Sapling, Species 4
    fExpectedDiam = 5.230336358;
    fExpectedHeight = 8.240471158;
    fExpectedGrowth = 0.38389393;
    p_oTree7->GetValue(p_oPop->GetDiam10Code(p_oTree7->GetSpecies(), p_oTree7->GetType()), &fDiam);
    p_oTree7->GetValue(p_oPop->GetHeightCode(p_oTree7->GetSpecies(), p_oTree7->GetType()), &fHeight);
    p_oTree7->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree7->GetSpecies(), p_oTree7->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Tree 8: Sapling, Species 4
    fExpectedDiam = 7.068167815;
    fExpectedHeight = 6.071167199;
    fExpectedGrowth = 0.113613025;
    p_oTree8->GetValue(p_oPop->GetDiam10Code(p_oTree8->GetSpecies(), p_oTree8->GetType()), &fDiam);
    p_oTree8->GetValue(p_oPop->GetHeightCode(p_oTree8->GetSpecies(), p_oTree8->GetType()), &fHeight);
    p_oTree8->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree8->GetSpecies(), p_oTree8->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Tree 9: Adult, Species 4
    fExpectedDiam = 20.0247831;
    fExpectedHeight = 15.02587355;
    fExpectedGrowth = 0.04130516;
    p_oTree9->GetValue(p_oPop->GetDbhCode(p_oTree9->GetSpecies(), p_oTree9->GetType()), &fDiam);
    p_oTree9->GetValue(p_oPop->GetHeightCode(p_oTree9->GetSpecies(), p_oTree9->GetType()), &fHeight);
    p_oTree9->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree9->GetSpecies(), p_oTree9->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Tree 10: Adult, Species 4
    fExpectedDiam = 20.32090543;
    fExpectedHeight = 16.33502527;
    fExpectedGrowth = 0.534842379;
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
// TestErrorProcessing()
////////////////////////////////////////////////////////////////////////////
TEST(MichMenPhotoinhibition, TestErrorProcessing)
{
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try
  {
    p_oSimManager->ReadFile( WriteMichMenPhotoinhibitionXMLErrorFile1() );
    FAIL() << "TestMichMenPhotoinhibition error processing didn't catch error for WriteMichMenPhotoinhibitionXMLErrorFile1.";
  }
  catch ( modelErr& err )
  {
    if ( err.sFunction.compare("clMichMenPhotoinhibition::DoShellSetup" ) != 0 )
    {
      FAIL() << "TestMichMenPhotoinhibition error processing caught wrong error for WriteMichMenPhotoinhibitionXMLErrorFile1.";
    }
    ;
  }
  delete p_oSimManager;
}


////////////////////////////////////////////////////////////////////////////
// WriteMichMenPhotoinhibitionXMLFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteMichMenPhotoinhibitionXMLFile1() {
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

  WriteMichMenPhotoinhibitionCommonStuff(oOut);

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteMichMenPhotoinhibitionXMLFile2()
////////////////////////////////////////////////////////////////////////////
const char* WriteMichMenPhotoinhibitionXMLFile2() {
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

  WriteMichMenPhotoinhibitionCommonStuff(oOut);

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteMichMenPhotoinhibitionCommonStuff()
/////////////////////////////////////////////////////////////////////////////
void WriteMichMenPhotoinhibitionCommonStuff(std::fstream &oOut)
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
       << "<behaviorName>MichaelisMentenPhotoinhibitionGrowth height only</behaviorName>"
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
       << "<MichaelisMentenPhotoinhibitionGrowth2>"
       << "<gr_mmPhotGrowthAlpha>"
       << "<gr_mmpgaVal species=\"Species_1\">0.650909</gr_mmpgaVal>"
       << "<gr_mmpgaVal species=\"Species_2\">7.99</gr_mmpgaVal>"
       << "<gr_mmpgaVal species=\"Species_4\">1.044</gr_mmpgaVal>"
       << "</gr_mmPhotGrowthAlpha>"
       << "<gr_mmPhotGrowthBeta>"
       << "<gr_mmpgbVal species=\"Species_1\">-2.31861</gr_mmpgbVal>"
       << "<gr_mmpgbVal species=\"Species_2\">0.019</gr_mmpgbVal>"
       << "<gr_mmpgbVal species=\"Species_4\">0.015</gr_mmpgbVal>"
       << "</gr_mmPhotGrowthBeta>"
       << "<gr_mmPhotGrowthD>"
       << "<gr_mmpgdVal species=\"Species_1\">0.009971</gr_mmpgdVal>"
       << "<gr_mmpgdVal species=\"Species_2\">0.003</gr_mmpgdVal>"
       << "<gr_mmpgdVal species=\"Species_4\">0.00345</gr_mmpgdVal>"
       << "</gr_mmPhotGrowthD>"
       << "<gr_mmPhotGrowthPhi>"
       << "<gr_mmpgpVal species=\"Species_1\">0.85488</gr_mmpgpVal>"
       << "<gr_mmpgpVal species=\"Species_2\">0.08</gr_mmpgpVal>"
       << "<gr_mmpgpVal species=\"Species_4\">0.5</gr_mmpgpVal>"
       << "</gr_mmPhotGrowthPhi>"
       << "</MichaelisMentenPhotoinhibitionGrowth2>"
       << "</paramFile>";
}

////////////////////////////////////////////////////////////////////////////
// WriteMichMenPhotoinhibitionXMLErrorFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteMichMenPhotoinhibitionXMLErrorFile1() {
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
       << "<behaviorName>MichaelisMentenPhotoinhibitionGrowth height only</behaviorName>"
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
       << "<MichaelisMentenPhotoinhibitionGrowth2>"
       << "<gr_mmPhotGrowthAlpha>"
       << "<gr_mmpgaVal species=\"Species_1\">26.98894</gr_mmpgaVal>"
       << "<gr_mmpgaVal species=\"Species_2\">7.99</gr_mmpgaVal>"
       << "<gr_mmpgaVal species=\"Species_4\">1.044</gr_mmpgaVal>"
       << "</gr_mmPhotGrowthAlpha>"
       << "<gr_mmPhotGrowthBeta>"
       << "<gr_mmpgbVal species=\"Species_1\">498.31</gr_mmpgbVal>"
       << "<gr_mmpgbVal species=\"Species_2\">0.019</gr_mmpgbVal>"
       << "<gr_mmpgbVal species=\"Species_4\">0</gr_mmpgbVal>"
       << "</gr_mmPhotGrowthBeta>"
       << "<gr_mmPhotGrowthD>"
       << "<gr_mmpgdVal species=\"Species_1\">17.18377</gr_mmpgdVal>"
       << "<gr_mmpgdVal species=\"Species_2\">34</gr_mmpgdVal>"
       << "<gr_mmpgdVal species=\"Species_4\">16</gr_mmpgdVal>"
       << "</gr_mmPhotGrowthD>"
       << "<gr_mmPhotGrowthPhi>"
       << "<gr_mmpgpVal species=\"Species_1\">-0.15811</gr_mmpgpVal>"
       << "<gr_mmpgpVal species=\"Species_2\">0.08</gr_mmpgpVal>"
       << "<gr_mmpgpVal species=\"Species_4\">0.5</gr_mmpgpVal>"
       << "</gr_mmPhotGrowthPhi>"
       << "</MichaelisMentenPhotoinhibitionGrowth2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}
