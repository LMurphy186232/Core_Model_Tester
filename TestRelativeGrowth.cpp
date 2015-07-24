//---------------------------------------------------------------------------
// TestRelativeGrowth.cpp
//---------------------------------------------------------------------------
#include "TestRelativeGrowth.h"
#include <gtest/gtest.h>
#include <fstream>
#include <math.h>
#include "TreePopulation.h"
#include "SimManager.h"
#include "BehaviorBase.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////
// Test1Run1YearPerTimestep()
// Tests the growth when the timestep length is one year.
// WriteRelativeGrowthXMLFile1() is used to set up the run. 10 trees are created
// of four species, assigned to all six growth types and with growth levels both
// above and below limits. GLIs are assigned to them, and then growth is run.
// Their diameters, heights, and "Growth" values are checked to make sure they
// are correct.
////////////////////////////////////////////////////////////////////////////
TEST(RelativeGrowth, Test1Run1YearPerTimestep) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTree *p_oTree1, *p_oTree2, *p_oTree3, *p_oTree4, *p_oTree5, *p_oTree6,
    *p_oTree7, *p_oTree8, *p_oTree9, *p_oTree10;
    float fDiam, fHeight, fExpectedDiam, fExpectedHeight, fLight, fGrowth, fExpectedGrowth;

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteRelativeGrowthXMLFile1() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create our ten trees and set diameter, height, and GLI for each
    //Sapling, Species 1
    fDiam = 4.004;
    fHeight = 7;
    fLight = 60;
    p_oTree1 = p_oPop->CreateTree(1, 1, 0, clTreePopulation::sapling, fDiam);
    p_oTree1->SetValue(p_oPop->GetHeightCode(p_oTree1->GetSpecies(), p_oTree1->GetType()), fHeight, false, false);
    p_oTree1->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree1->GetSpecies(), p_oTree1->GetType()), fLight, false, false);

    //Sapling, Species 2
    fDiam = 2.972;
    fHeight = 8;
    fLight = 80;
    p_oTree2 = p_oPop->CreateTree(2, 2, 1, clTreePopulation::sapling, fDiam);
    p_oTree2->SetValue(p_oPop->GetHeightCode(p_oTree2->GetSpecies(), p_oTree2->GetType()), fHeight, false, false);
    p_oTree2->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree2->GetSpecies(), p_oTree2->GetType()), fLight, false, false);

    //Sapling, Species 2
    fDiam = 4.1608;
    fHeight = 6;
    fLight = 5;
    p_oTree3 = p_oPop->CreateTree(3, 3, 1, clTreePopulation::sapling, fDiam);
    p_oTree3->SetValue(p_oPop->GetHeightCode(p_oTree3->GetSpecies(), p_oTree3->GetType()), fHeight, false, false);
    p_oTree3->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree3->GetSpecies(), p_oTree3->GetType()), fLight, false, false);

    //Adult, Species 1
    fDiam = 20;
    fHeight = 15;
    fLight = 2;
    p_oTree4 = p_oPop->CreateTree(4, 4, 0, clTreePopulation::adult, fDiam);
    p_oTree4->SetValue(p_oPop->GetHeightCode(p_oTree4->GetSpecies(), p_oTree4->GetType()), fHeight, false, false);
    p_oTree4->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree4->GetSpecies(), p_oTree4->GetType()), fLight, false, false);

    //Adult, Species 1
    fDiam = 20;
    fHeight = 16;
    fLight = 19;
    p_oTree5 = p_oPop->CreateTree(5, 5, 0, clTreePopulation::adult, fDiam);
    p_oTree5->SetValue(p_oPop->GetHeightCode(p_oTree5->GetSpecies(), p_oTree5->GetType()), fHeight, false, false);
    p_oTree5->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree5->GetSpecies(), p_oTree5->GetType()), fLight, false, false);

    //Sapling, Species 3
    fDiam = 3.5295;
    fHeight = 7;
    fLight = 60;
    p_oTree6 = p_oPop->CreateTree(6, 6, 2, clTreePopulation::sapling, fDiam);
    p_oTree6->SetValue(p_oPop->GetHeightCode(p_oTree6->GetSpecies(), p_oTree6->GetType()), fHeight, false, false);
    p_oTree6->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree6->GetSpecies(), p_oTree6->GetType()), fLight, false, false);

    //Sapling, Species 4
    fDiam = 3.5295;
    fHeight = 8;
    fLight = 70;
    p_oTree7 = p_oPop->CreateTree(7, 7, 3, clTreePopulation::sapling, fDiam);
    p_oTree7->SetValue(p_oPop->GetHeightCode(p_oTree7->GetSpecies(), p_oTree7->GetType()), fHeight, false, false);
    p_oTree7->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree7->GetSpecies(), p_oTree7->GetType()), fLight, false, false);

    //Sapling, Species 4
    fDiam = 4.9413;
    fHeight = 6;
    fLight = 10;
    p_oTree8 = p_oPop->CreateTree(8, 8, 3, clTreePopulation::sapling, fDiam);
    p_oTree8->SetValue(p_oPop->GetHeightCode(p_oTree8->GetSpecies(), p_oTree8->GetType()), fHeight, false, false);
    p_oTree8->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree8->GetSpecies(), p_oTree8->GetType()), fLight, false, false);

    //Adult, Species 3
    fDiam = 20;
    fHeight = 15;
    fLight = 2;
    p_oTree9 = p_oPop->CreateTree(9, 9, 2, clTreePopulation::adult, fDiam);
    p_oTree9->SetValue(p_oPop->GetHeightCode(p_oTree9->GetSpecies(), p_oTree9->GetType()), fHeight, false, false);
    p_oTree9->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree9->GetSpecies(), p_oTree9->GetType()), fLight, false, false);

    //Adult, Species 3
    fDiam = 20;
    fHeight = 16;
    fLight = 90;
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
    fExpectedDiam = 7.804600484;
    fExpectedHeight = 7.849284935;
    fExpectedGrowth = 14.02300242;
    p_oTree1->GetValue(p_oPop->GetDiam10Code(p_oTree1->GetSpecies(), p_oTree1->GetType()), &fDiam);
    p_oTree1->GetValue(p_oPop->GetHeightCode(p_oTree1->GetSpecies(), p_oTree1->GetType()), &fHeight);
    p_oTree1->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree1->GetSpecies(), p_oTree1->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Sapling, Species 2
    fExpectedDiam = 6.236;
    fExpectedHeight = 4.613608328;
    fExpectedGrowth = 6.18;
    p_oTree2->GetValue(p_oPop->GetDiam10Code(p_oTree2->GetSpecies(), p_oTree2->GetType()), &fDiam);
    p_oTree2->GetValue(p_oPop->GetHeightCode(p_oTree2->GetSpecies(), p_oTree2->GetType()), &fHeight);
    p_oTree2->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree2->GetSpecies(), p_oTree2->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Sapling, Species 2
    fExpectedDiam = 7.594334452;
    fExpectedHeight = 5.286643619;
    fExpectedGrowth = 2.97167226;
    p_oTree3->GetValue(p_oPop->GetDiam10Code(p_oTree3->GetSpecies(), p_oTree3->GetType()), &fDiam);
    p_oTree3->GetValue(p_oPop->GetHeightCode(p_oTree3->GetSpecies(), p_oTree3->GetType()), &fHeight);
    p_oTree3->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree3->GetSpecies(), p_oTree3->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Adult, Species 1
    fExpectedDiam = 21.01605263;
    fExpectedHeight = 19.13934892;
    fExpectedGrowth = 5.080263158;
    p_oTree4->GetValue(p_oPop->GetDbhCode(p_oTree4->GetSpecies(), p_oTree4->GetType()), &fDiam);
    p_oTree4->GetValue(p_oPop->GetHeightCode(p_oTree4->GetSpecies(), p_oTree4->GetType()), &fHeight);
    p_oTree4->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree4->GetSpecies(), p_oTree4->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Adult, Species 1
    fExpectedDiam = 22.25;
    fExpectedHeight = 19.87614219;
    fExpectedGrowth = 11.25;
    p_oTree5->GetValue(p_oPop->GetDbhCode(p_oTree5->GetSpecies(), p_oTree5->GetType()), &fDiam);
    p_oTree5->GetValue(p_oPop->GetHeightCode(p_oTree5->GetSpecies(), p_oTree5->GetType()), &fHeight);
    p_oTree5->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree5->GetSpecies(), p_oTree5->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Sapling, Species 3
    fExpectedDiam = 6.808735936;
    fExpectedHeight = 8.313630737;
    fExpectedGrowth = 9.043679682;
    p_oTree6->GetValue(p_oPop->GetDiam10Code(p_oTree6->GetSpecies(), p_oTree6->GetType()), &fDiam);
    p_oTree6->GetValue(p_oPop->GetHeightCode(p_oTree6->GetSpecies(), p_oTree6->GetType()), &fHeight);
    p_oTree6->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree6->GetSpecies(), p_oTree6->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Sapling, Species 4
    fExpectedDiam = 6.184;
    fExpectedHeight = 8.864881726;
    fExpectedGrowth = 5.92;
    p_oTree7->GetValue(p_oPop->GetDiam10Code(p_oTree7->GetSpecies(), p_oTree7->GetType()), &fDiam);
    p_oTree7->GetValue(p_oPop->GetHeightCode(p_oTree7->GetSpecies(), p_oTree7->GetType()), &fHeight);
    p_oTree7->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree7->GetSpecies(), p_oTree7->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Sapling, Species 4
    fExpectedDiam = 7.918090452;
    fExpectedHeight = 6.647788871;
    fExpectedGrowth = 4.590452261;
    p_oTree8->GetValue(p_oPop->GetDiam10Code(p_oTree8->GetSpecies(), p_oTree8->GetType()), &fDiam);
    p_oTree8->GetValue(p_oPop->GetHeightCode(p_oTree8->GetSpecies(), p_oTree8->GetType()), &fHeight);
    p_oTree8->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree8->GetSpecies(), p_oTree8->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Adult, Species 3
    fExpectedDiam = 20.39140709;
    fExpectedHeight = 15.26417784;
    fExpectedGrowth = 1.957035446;
    p_oTree9->GetValue(p_oPop->GetDbhCode(p_oTree9->GetSpecies(), p_oTree9->GetType()), &fDiam);
    p_oTree9->GetValue(p_oPop->GetHeightCode(p_oTree9->GetSpecies(), p_oTree9->GetType()), &fHeight);
    p_oTree9->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree9->GetSpecies(), p_oTree9->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Adult, Species 3
    fExpectedDiam = 21.25;
    fExpectedHeight = 16.83424181;
    fExpectedGrowth = 6.25;
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
// Tests the growth when the timestep length is three years.
// WriteRelativeGrowthXMLFile2() is used to set up the run. 10 trees are created
// of three species, assigned to all six growth types and with growth levels
// both above and below limits. GLIs are assigned to them, and then growth is
// run. Their diameters, heights, and "Growth" values are checked to make sure
// they are correct.
////////////////////////////////////////////////////////////////////////////
TEST(RelativeGrowth, Test1Run3YearsPerTimestep) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTree *p_oTree1, *p_oTree2, *p_oTree3, *p_oTree4, *p_oTree5, *p_oTree6,
    *p_oTree7, *p_oTree8, *p_oTree9, *p_oTree10;
    float fDiam, fHeight, fExpectedDiam, fExpectedHeight, fLight, fGrowth, fExpectedGrowth;

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteRelativeGrowthXMLFile2() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create our ten trees and set diameter, height, and GLI for each
    //Sapling, Species 1
    fDiam = 4.004;
    fHeight = 7;
    fLight = 60;
    p_oTree1 = p_oPop->CreateTree(1, 1, 0, clTreePopulation::sapling, fDiam);
    p_oTree1->SetValue(p_oPop->GetHeightCode(p_oTree1->GetSpecies(), p_oTree1->GetType()), fHeight, false, false);
    p_oTree1->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree1->GetSpecies(), p_oTree1->GetType()), fLight, false, false);

    //Sapling, Species 2
    fDiam = 2.972;
    fHeight = 8;
    fLight = 80;
    p_oTree2 = p_oPop->CreateTree(2, 2, 1, clTreePopulation::sapling, fDiam);
    p_oTree2->SetValue(p_oPop->GetHeightCode(p_oTree2->GetSpecies(), p_oTree2->GetType()), fHeight, false, false);
    p_oTree2->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree2->GetSpecies(), p_oTree2->GetType()), fLight, false, false);

    //Sapling, Species 2
    fDiam = 4.1608;
    fHeight = 6;
    fLight = 5;
    p_oTree3 = p_oPop->CreateTree(3, 3, 1, clTreePopulation::sapling, fDiam);
    p_oTree3->SetValue(p_oPop->GetHeightCode(p_oTree3->GetSpecies(), p_oTree3->GetType()), fHeight, false, false);
    p_oTree3->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree3->GetSpecies(), p_oTree3->GetType()), fLight, false, false);

    //Adult, Species 1
    fDiam = 20;
    fHeight = 15;
    fLight = 2;
    p_oTree4 = p_oPop->CreateTree(4, 4, 0, clTreePopulation::adult, fDiam);
    p_oTree4->SetValue(p_oPop->GetHeightCode(p_oTree4->GetSpecies(), p_oTree4->GetType()), fHeight, false, false);
    p_oTree4->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree4->GetSpecies(), p_oTree4->GetType()), fLight, false, false);

    //Adult, Species 1
    fDiam = 20;
    fHeight = 16;
    fLight = 19;
    p_oTree5 = p_oPop->CreateTree(5, 5, 0, clTreePopulation::adult, fDiam);
    p_oTree5->SetValue(p_oPop->GetHeightCode(p_oTree5->GetSpecies(), p_oTree5->GetType()), fHeight, false, false);
    p_oTree5->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree5->GetSpecies(), p_oTree5->GetType()), fLight, false, false);

    //Sapling, Species 3
    fDiam = 3.5295;
    fHeight = 7;
    fLight = 60;
    p_oTree6 = p_oPop->CreateTree(6, 6, 2, clTreePopulation::sapling, fDiam);
    p_oTree6->SetValue(p_oPop->GetHeightCode(p_oTree6->GetSpecies(), p_oTree6->GetType()), fHeight, false, false);
    p_oTree6->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree6->GetSpecies(), p_oTree6->GetType()), fLight, false, false);

    //Sapling, Species 4
    fDiam = 3.5295;
    fHeight = 8;
    fLight = 70;
    p_oTree7 = p_oPop->CreateTree(7, 7, 3, clTreePopulation::sapling, fDiam);
    p_oTree7->SetValue(p_oPop->GetHeightCode(p_oTree7->GetSpecies(), p_oTree7->GetType()), fHeight, false, false);
    p_oTree7->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree7->GetSpecies(), p_oTree7->GetType()), fLight, false, false);

    //Sapling, Species 4
    fDiam = 4.9413;
    fHeight = 6;
    fLight = 10;
    p_oTree8 = p_oPop->CreateTree(8, 8, 3, clTreePopulation::sapling, fDiam);
    p_oTree8->SetValue(p_oPop->GetHeightCode(p_oTree8->GetSpecies(), p_oTree8->GetType()), fHeight, false, false);
    p_oTree8->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree8->GetSpecies(), p_oTree8->GetType()), fLight, false, false);

    //Adult, Species 3
    fDiam = 20;
    fHeight = 15;
    fLight = 2;
    p_oTree9 = p_oPop->CreateTree(9, 9, 2, clTreePopulation::adult, fDiam);
    p_oTree9->SetValue(p_oPop->GetHeightCode(p_oTree9->GetSpecies(), p_oTree9->GetType()), fHeight, false, false);
    p_oTree9->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree9->GetSpecies(), p_oTree9->GetType()), fLight, false, false);

    //Adult, Species 3
    fDiam = 20;
    fHeight = 16;
    fLight = 90;
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
    //Sapling (now adult), Species 1
    fExpectedDiam = 15.22776217;
    fExpectedHeight = 15.29599934;
    fExpectedGrowth = 23.35947838;
    p_oTree1->GetValue(p_oPop->GetDbhCode(p_oTree1->GetSpecies(), p_oTree1->GetType()), &fDiam);
    p_oTree1->GetValue(p_oPop->GetHeightCode(p_oTree1->GetSpecies(), p_oTree1->GetType()), &fHeight);
    p_oTree1->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree1->GetSpecies(), p_oTree1->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Sapling, Species 2
    fExpectedDiam = 8.708;
    fExpectedHeight = 5.828762022;
    fExpectedGrowth = 6.18;
    p_oTree2->GetValue(p_oPop->GetDiam10Code(p_oTree2->GetSpecies(), p_oTree2->GetType()), &fDiam);
    p_oTree2->GetValue(p_oPop->GetHeightCode(p_oTree2->GetSpecies(), p_oTree2->GetType()), &fHeight);
    p_oTree2->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree2->GetSpecies(), p_oTree2->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Sapling, Species 2
    fExpectedDiam = 8.938673581;
    fExpectedHeight = 5.93997387;
    fExpectedGrowth = 3.231122636;
    p_oTree3->GetValue(p_oPop->GetDiam10Code(p_oTree3->GetSpecies(), p_oTree3->GetType()), &fDiam);
    p_oTree3->GetValue(p_oPop->GetHeightCode(p_oTree3->GetSpecies(), p_oTree3->GetType()), &fHeight);
    p_oTree3->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree3->GetSpecies(), p_oTree3->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Adult, Species 1
    fExpectedDiam = 23.20563467;
    fExpectedHeight = 20.42836553;
    fExpectedGrowth = 5.342724458;
    p_oTree4->GetValue(p_oPop->GetDbhCode(p_oTree4->GetSpecies(), p_oTree4->GetType()), &fDiam);
    p_oTree4->GetValue(p_oPop->GetHeightCode(p_oTree4->GetSpecies(), p_oTree4->GetType()), &fHeight);
    p_oTree4->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree4->GetSpecies(), p_oTree4->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Adult, Species 1
    fExpectedDiam = 26.75;
    fExpectedHeight = 22.34408808;
    fExpectedGrowth = 11.25;
    p_oTree5->GetValue(p_oPop->GetDbhCode(p_oTree5->GetSpecies(), p_oTree5->GetType()), &fDiam);
    p_oTree5->GetValue(p_oPop->GetHeightCode(p_oTree5->GetSpecies(), p_oTree5->GetType()), &fHeight);
    p_oTree5->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree5->GetSpecies(), p_oTree5->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Sapling, Species 3
    fExpectedDiam = 12.62581627;
    fExpectedHeight = 12.2514093;
    fExpectedGrowth = 12.70969378;
    p_oTree6->GetValue(p_oPop->GetDiam10Code(p_oTree6->GetSpecies(), p_oTree6->GetType()), &fDiam);
    p_oTree6->GetValue(p_oPop->GetHeightCode(p_oTree6->GetSpecies(), p_oTree6->GetType()), &fHeight);
    p_oTree6->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree6->GetSpecies(), p_oTree6->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Sapling, Species 4
    fExpectedDiam = 8.552;
    fExpectedHeight = 10.53864294;
    fExpectedGrowth = 5.92;
    p_oTree7->GetValue(p_oPop->GetDiam10Code(p_oTree7->GetSpecies(), p_oTree7->GetType()), &fDiam);
    p_oTree7->GetValue(p_oPop->GetHeightCode(p_oTree7->GetSpecies(), p_oTree7->GetType()), &fHeight);
    p_oTree7->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree7->GetSpecies(), p_oTree7->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Sapling, Species 4
    fExpectedDiam = 10.13130281;
    fExpectedHeight = 8.164744694;
    fExpectedGrowth = 5.218838009;
    p_oTree8->GetValue(p_oPop->GetDiam10Code(p_oTree8->GetSpecies(), p_oTree8->GetType()), &fDiam);
    p_oTree8->GetValue(p_oPop->GetHeightCode(p_oTree8->GetSpecies(), p_oTree8->GetType()), &fHeight);
    p_oTree8->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree8->GetSpecies(), p_oTree8->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Adult, Species 3
    fExpectedDiam = 21.1973511;
    fExpectedHeight = 15.79965475;
    fExpectedGrowth = 1.995585171;
    p_oTree9->GetValue(p_oPop->GetDbhCode(p_oTree9->GetSpecies(), p_oTree9->GetType()), &fDiam);
    p_oTree9->GetValue(p_oPop->GetHeightCode(p_oTree9->GetSpecies(), p_oTree9->GetType()), &fHeight);
    p_oTree9->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree9->GetSpecies(), p_oTree9->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Adult, Species 3
    fExpectedDiam = 23.75;
    fExpectedHeight = 18.42265861;
    fExpectedGrowth = 6.25;
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
// Tests the growth when the timestep length is one year.
// WriteRelativeGrowthXMLFile3() is used to set up the run. 10 trees are created
// of four species, assigned to all six growth types and with growth levels both
// above and below limits. There are non-1 diameter exponents. GLIs are assigned
// to them, and then growth is run. Their diameters, heights, and "Growth"
// values are checked to make sure they are correct.
////////////////////////////////////////////////////////////////////////////
TEST(RelativeGrowth, Test2Run1YearPerTimestep) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTree *p_oTree1, *p_oTree2, *p_oTree3, *p_oTree4, *p_oTree5, *p_oTree6,
    *p_oTree7, *p_oTree8, *p_oTree9, *p_oTree10;
    float fDiam, fHeight, fExpectedDiam, fExpectedHeight, fLight, fGrowth, fExpectedGrowth;

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteRelativeGrowthXMLFile3() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create our ten trees and set diameter, height, and GLI for each
    //Sapling, Species 1
    fDiam = 4.004;
    fHeight = 7;
    fLight = 60;
    p_oTree1 = p_oPop->CreateTree(1, 1, 0, clTreePopulation::sapling, fDiam);
    p_oTree1->SetValue(p_oPop->GetHeightCode(p_oTree1->GetSpecies(), p_oTree1->GetType()), fHeight, false, false);
    p_oTree1->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree1->GetSpecies(), p_oTree1->GetType()), fLight, false, false);

    //Sapling, Species 2
    fDiam = 2.972;
    fHeight = 8;
    fLight = 80;
    p_oTree2 = p_oPop->CreateTree(2, 2, 1, clTreePopulation::sapling, fDiam);
    p_oTree2->SetValue(p_oPop->GetHeightCode(p_oTree2->GetSpecies(), p_oTree2->GetType()), fHeight, false, false);
    p_oTree2->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree2->GetSpecies(), p_oTree2->GetType()), fLight, false, false);

    //Sapling, Species 2
    fDiam = 4.1608;
    fHeight = 6;
    fLight = 5;
    p_oTree3 = p_oPop->CreateTree(3, 3, 1, clTreePopulation::sapling, fDiam);
    p_oTree3->SetValue(p_oPop->GetHeightCode(p_oTree3->GetSpecies(), p_oTree3->GetType()), fHeight, false, false);
    p_oTree3->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree3->GetSpecies(), p_oTree3->GetType()), fLight, false, false);

    //Adult, Species 1
    fDiam = 20;
    fHeight = 15;
    fLight = 2;
    p_oTree4 = p_oPop->CreateTree(4, 4, 0, clTreePopulation::adult, fDiam);
    p_oTree4->SetValue(p_oPop->GetHeightCode(p_oTree4->GetSpecies(), p_oTree4->GetType()), fHeight, false, false);
    p_oTree4->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree4->GetSpecies(), p_oTree4->GetType()), fLight, false, false);

    //Adult, Species 1
    fDiam = 20;
    fHeight = 16;
    fLight = 19;
    p_oTree5 = p_oPop->CreateTree(5, 5, 0, clTreePopulation::adult, fDiam);
    p_oTree5->SetValue(p_oPop->GetHeightCode(p_oTree5->GetSpecies(), p_oTree5->GetType()), fHeight, false, false);
    p_oTree5->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree5->GetSpecies(), p_oTree5->GetType()), fLight, false, false);

    //Sapling, Species 3
    fDiam = 3.5295;
    fHeight = 7;
    fLight = 60;
    p_oTree6 = p_oPop->CreateTree(6, 6, 2, clTreePopulation::sapling, fDiam);
    p_oTree6->SetValue(p_oPop->GetHeightCode(p_oTree6->GetSpecies(), p_oTree6->GetType()), fHeight, false, false);
    p_oTree6->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree6->GetSpecies(), p_oTree6->GetType()), fLight, false, false);

    //Sapling, Species 4
    fDiam = 3.5295;
    fHeight = 8;
    fLight = 70;
    p_oTree7 = p_oPop->CreateTree(7, 7, 3, clTreePopulation::sapling, fDiam);
    p_oTree7->SetValue(p_oPop->GetHeightCode(p_oTree7->GetSpecies(), p_oTree7->GetType()), fHeight, false, false);
    p_oTree7->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree7->GetSpecies(), p_oTree7->GetType()), fLight, false, false);

    //Sapling, Species 4
    fDiam = 4.9413;
    fHeight = 6;
    fLight = 10;
    p_oTree8 = p_oPop->CreateTree(8, 8, 3, clTreePopulation::sapling, fDiam);
    p_oTree8->SetValue(p_oPop->GetHeightCode(p_oTree8->GetSpecies(), p_oTree8->GetType()), fHeight, false, false);
    p_oTree8->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree8->GetSpecies(), p_oTree8->GetType()), fLight, false, false);

    //Adult, Species 3
    fDiam = 20;
    fHeight = 15;
    fLight = 2;
    p_oTree9 = p_oPop->CreateTree(9, 9, 2, clTreePopulation::adult, fDiam);
    p_oTree9->SetValue(p_oPop->GetHeightCode(p_oTree9->GetSpecies(), p_oTree9->GetType()), fHeight, false, false);
    p_oTree9->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree9->GetSpecies(), p_oTree9->GetType()), fLight, false, false);

    //Adult, Species 3
    fDiam = 20;
    fHeight = 16;
    fLight = 90;
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
    fExpectedDiam = 8.294336857;
    fExpectedHeight = 8.218027096;
    fExpectedGrowth = 16.47168428;
    p_oTree1->GetValue(p_oPop->GetDiam10Code(p_oTree1->GetSpecies(), p_oTree1->GetType()), &fDiam);
    p_oTree1->GetValue(p_oPop->GetHeightCode(p_oTree1->GetSpecies(), p_oTree1->GetType()), &fHeight);
    p_oTree1->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree1->GetSpecies(), p_oTree1->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Sapling, Species 2
    fExpectedDiam = 6.236;
    fExpectedHeight = 4.613608328;
    fExpectedGrowth = 6.18;
    p_oTree2->GetValue(p_oPop->GetDiam10Code(p_oTree2->GetSpecies(), p_oTree2->GetType()), &fDiam);
    p_oTree2->GetValue(p_oPop->GetHeightCode(p_oTree2->GetSpecies(), p_oTree2->GetType()), &fHeight);
    p_oTree2->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree2->GetSpecies(), p_oTree2->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Sapling, Species 2
    fExpectedDiam = 7.402727511;
    fExpectedHeight = 5.192496644;
    fExpectedGrowth = 2.013637554;
    p_oTree3->GetValue(p_oPop->GetDiam10Code(p_oTree3->GetSpecies(), p_oTree3->GetType()), &fDiam);
    p_oTree3->GetValue(p_oPop->GetHeightCode(p_oTree3->GetSpecies(), p_oTree3->GetType()), &fHeight);
    p_oTree3->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree3->GetSpecies(), p_oTree3->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Adult, Species 1
    fExpectedDiam = 21.37094239;
    fExpectedHeight = 19.35404659;
    fExpectedGrowth = 6.854711941;
    p_oTree4->GetValue(p_oPop->GetDbhCode(p_oTree4->GetSpecies(), p_oTree4->GetType()), &fDiam);
    p_oTree4->GetValue(p_oPop->GetHeightCode(p_oTree4->GetSpecies(), p_oTree4->GetType()), &fHeight);
    p_oTree4->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree4->GetSpecies(), p_oTree4->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Adult, Species 1
    fExpectedDiam = 22.25;
    fExpectedHeight = 19.87614219;
    fExpectedGrowth = 11.25;
    p_oTree5->GetValue(p_oPop->GetDbhCode(p_oTree5->GetSpecies(), p_oTree5->GetType()), &fDiam);
    p_oTree5->GetValue(p_oPop->GetHeightCode(p_oTree5->GetSpecies(), p_oTree5->GetType()), &fHeight);
    p_oTree5->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree5->GetSpecies(), p_oTree5->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Sapling, Species 3
    fExpectedDiam = 7.931339827;
    fExpectedHeight = 9.107035498;
    fExpectedGrowth = 14.65669914;
    p_oTree6->GetValue(p_oPop->GetDiam10Code(p_oTree6->GetSpecies(), p_oTree6->GetType()), &fDiam);
    p_oTree6->GetValue(p_oPop->GetHeightCode(p_oTree6->GetSpecies(), p_oTree6->GetType()), &fHeight);
    p_oTree6->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree6->GetSpecies(), p_oTree6->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Sapling, Species 4
    fExpectedDiam = 6.184;
    fExpectedHeight = 8.864881726;
    fExpectedGrowth = 5.92;
    p_oTree7->GetValue(p_oPop->GetDiam10Code(p_oTree7->GetSpecies(), p_oTree7->GetType()), &fDiam);
    p_oTree7->GetValue(p_oPop->GetHeightCode(p_oTree7->GetSpecies(), p_oTree7->GetType()), &fHeight);
    p_oTree7->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree7->GetSpecies(), p_oTree7->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Sapling, Species 4
    fExpectedDiam = 7.755745669;
    fExpectedHeight = 6.534043283;
    fExpectedGrowth = 3.778728344;
    p_oTree8->GetValue(p_oPop->GetDiam10Code(p_oTree8->GetSpecies(), p_oTree8->GetType()), &fDiam);
    p_oTree8->GetValue(p_oPop->GetHeightCode(p_oTree8->GetSpecies(), p_oTree8->GetType()), &fHeight);
    p_oTree8->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree8->GetSpecies(), p_oTree8->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Adult, Species 3
    fExpectedDiam = 20.96147431;
    fExpectedHeight = 15.64410905;
    fExpectedGrowth = 4.807371565;
    p_oTree9->GetValue(p_oPop->GetDbhCode(p_oTree9->GetSpecies(), p_oTree9->GetType()), &fDiam);
    p_oTree9->GetValue(p_oPop->GetHeightCode(p_oTree9->GetSpecies(), p_oTree9->GetType()), &fHeight);
    p_oTree9->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree9->GetSpecies(), p_oTree9->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Adult, Species 3
    fExpectedDiam = 21.25;
    fExpectedHeight = 16.83424181;
    fExpectedGrowth = 6.25;
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
// Test2Run3YearsPerTimestep()
// Tests the growth when the timestep length is three years. WriteRelativeGrowthXMLFile4() is
// used to set up the run. 10 trees are created of three species, assigned to
// all six growth types and with growth levels both above and below limits.
// There are non-1 diameter exponents.  GLIs are assigned to them, and then
// growth is run.  Their diameters, heights, and "Growth" values are checked to
// make sure they are correct.
////////////////////////////////////////////////////////////////////////////
TEST(RelativeGrowth, Test2Run3YearsPerTimestep) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTree *p_oTree1, *p_oTree2, *p_oTree3, *p_oTree4, *p_oTree5, *p_oTree6,
    *p_oTree7, *p_oTree8, *p_oTree9, *p_oTree10;
    float fDiam, fHeight, fExpectedDiam, fExpectedHeight, fLight, fGrowth, fExpectedGrowth;

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteRelativeGrowthXMLFile4() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create our ten trees and set diameter, height, and GLI for each
    //Sapling, Species 1
    fDiam = 4.004;
    fHeight = 7;
    fLight = 60;
    p_oTree1 = p_oPop->CreateTree(1, 1, 0, clTreePopulation::sapling, fDiam);
    p_oTree1->SetValue(p_oPop->GetHeightCode(p_oTree1->GetSpecies(), p_oTree1->GetType()), fHeight, false, false);
    p_oTree1->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree1->GetSpecies(), p_oTree1->GetType()), fLight, false, false);

    //Sapling, Species 2
    fDiam = 2.972;
    fHeight = 8;
    fLight = 80;
    p_oTree2 = p_oPop->CreateTree(2, 2, 1, clTreePopulation::sapling, fDiam);
    p_oTree2->SetValue(p_oPop->GetHeightCode(p_oTree2->GetSpecies(), p_oTree2->GetType()), fHeight, false, false);
    p_oTree2->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree2->GetSpecies(), p_oTree2->GetType()), fLight, false, false);

    //Sapling, Species 2
    fDiam = 4.1608;
    fHeight = 6;
    fLight = 5;
    p_oTree3 = p_oPop->CreateTree(3, 3, 1, clTreePopulation::sapling, fDiam);
    p_oTree3->SetValue(p_oPop->GetHeightCode(p_oTree3->GetSpecies(), p_oTree3->GetType()), fHeight, false, false);
    p_oTree3->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree3->GetSpecies(), p_oTree3->GetType()), fLight, false, false);

    //Adult, Species 1
    fDiam = 20;
    fHeight = 15;
    fLight = 2;
    p_oTree4 = p_oPop->CreateTree(4, 4, 0, clTreePopulation::adult, fDiam);
    p_oTree4->SetValue(p_oPop->GetHeightCode(p_oTree4->GetSpecies(), p_oTree4->GetType()), fHeight, false, false);
    p_oTree4->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree4->GetSpecies(), p_oTree4->GetType()), fLight, false, false);

    //Adult, Species 1
    fDiam = 20;
    fHeight = 16;
    fLight = 19;
    p_oTree5 = p_oPop->CreateTree(5, 5, 0, clTreePopulation::adult, fDiam);
    p_oTree5->SetValue(p_oPop->GetHeightCode(p_oTree5->GetSpecies(), p_oTree5->GetType()), fHeight, false, false);
    p_oTree5->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree5->GetSpecies(), p_oTree5->GetType()), fLight, false, false);

    //Sapling, Species 3
    fDiam = 3.5295;
    fHeight = 7;
    fLight = 60;
    p_oTree6 = p_oPop->CreateTree(6, 6, 2, clTreePopulation::sapling, fDiam);
    p_oTree6->SetValue(p_oPop->GetHeightCode(p_oTree6->GetSpecies(), p_oTree6->GetType()), fHeight, false, false);
    p_oTree6->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree6->GetSpecies(), p_oTree6->GetType()), fLight, false, false);

    //Sapling, Species 4
    fDiam = 3.5295;
    fHeight = 8;
    fLight = 70;
    p_oTree7 = p_oPop->CreateTree(7, 7, 3, clTreePopulation::sapling, fDiam);
    p_oTree7->SetValue(p_oPop->GetHeightCode(p_oTree7->GetSpecies(), p_oTree7->GetType()), fHeight, false, false);
    p_oTree7->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree7->GetSpecies(), p_oTree7->GetType()), fLight, false, false);

    //Sapling, Species 4
    fDiam = 4.9413;
    fHeight = 6;
    fLight = 10;
    p_oTree8 = p_oPop->CreateTree(8, 8, 3, clTreePopulation::sapling, fDiam);
    p_oTree8->SetValue(p_oPop->GetHeightCode(p_oTree8->GetSpecies(), p_oTree8->GetType()), fHeight, false, false);
    p_oTree8->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree8->GetSpecies(), p_oTree8->GetType()), fLight, false, false);

    //Adult, Species 3
    fDiam = 20;
    fHeight = 15;
    fLight = 2;
    p_oTree9 = p_oPop->CreateTree(9, 9, 2, clTreePopulation::adult, fDiam);
    p_oTree9->SetValue(p_oPop->GetHeightCode(p_oTree9->GetSpecies(), p_oTree9->GetType()), fHeight, false, false);
    p_oTree9->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree9->GetSpecies(), p_oTree9->GetType()), fLight, false, false);

    //Adult, Species 3
    fDiam = 20;
    fHeight = 16;
    fLight = 90;
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
    //Sapling (now adult), Species 1
    fExpectedDiam = 17.18764366;
    fExpectedHeight = 16.67246809;
    fExpectedGrowth = 27.43848581;
    p_oTree1->GetValue(p_oPop->GetDbhCode(p_oTree1->GetSpecies(), p_oTree1->GetType()), &fDiam);
    p_oTree1->GetValue(p_oPop->GetHeightCode(p_oTree1->GetSpecies(), p_oTree1->GetType()), &fHeight);
    p_oTree1->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree1->GetSpecies(), p_oTree1->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Sapling, Species 2
    fExpectedDiam = 8.708;
    fExpectedHeight = 5.828762022;
    fExpectedGrowth = 6.18;
    p_oTree2->GetValue(p_oPop->GetDiam10Code(p_oTree2->GetSpecies(), p_oTree2->GetType()), &fDiam);
    p_oTree2->GetValue(p_oPop->GetHeightCode(p_oTree2->GetSpecies(), p_oTree2->GetType()), &fHeight);
    p_oTree2->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree2->GetSpecies(), p_oTree2->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Sapling, Species 2
    fExpectedDiam = 8.313666376;
    fExpectedHeight = 5.637793599;
    fExpectedGrowth = 2.18944396;
    p_oTree3->GetValue(p_oPop->GetDiam10Code(p_oTree3->GetSpecies(), p_oTree3->GetType()), &fDiam);
    p_oTree3->GetValue(p_oPop->GetHeightCode(p_oTree3->GetSpecies(), p_oTree3->GetType()), &fHeight);
    p_oTree3->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree3->GetSpecies(), p_oTree3->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Adult, Species 1
    fExpectedDiam = 24.32530788;
    fExpectedHeight = 21.0556222;
    fExpectedGrowth = 7.208846471;
    p_oTree4->GetValue(p_oPop->GetDbhCode(p_oTree4->GetSpecies(), p_oTree4->GetType()), &fDiam);
    p_oTree4->GetValue(p_oPop->GetHeightCode(p_oTree4->GetSpecies(), p_oTree4->GetType()), &fHeight);
    p_oTree4->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree4->GetSpecies(), p_oTree4->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Adult, Species 1
    fExpectedDiam = 26.75;
    fExpectedHeight = 22.34408808;
    fExpectedGrowth = 11.25;
    p_oTree5->GetValue(p_oPop->GetDbhCode(p_oTree5->GetSpecies(), p_oTree5->GetType()), &fDiam);
    p_oTree5->GetValue(p_oPop->GetHeightCode(p_oTree5->GetSpecies(), p_oTree5->GetType()), &fHeight);
    p_oTree5->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree5->GetSpecies(), p_oTree5->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Sapling, Species 3 - now sapling
    fExpectedDiam = 12.2535977;
    fExpectedHeight = 15.1559752;
    fExpectedGrowth = 20.59804906;
    p_oTree6->GetValue(p_oPop->GetDbhCode(p_oTree6->GetSpecies(), p_oTree6->GetType()), &fDiam);
    p_oTree6->GetValue(p_oPop->GetHeightCode(p_oTree6->GetSpecies(), p_oTree6->GetType()), &fHeight);
    p_oTree6->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree6->GetSpecies(), p_oTree6->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Sapling, Species 4
    fExpectedDiam = 8.552;
    fExpectedHeight = 10.53864294;
    fExpectedGrowth = 5.92;
    p_oTree7->GetValue(p_oPop->GetDiam10Code(p_oTree7->GetSpecies(), p_oTree7->GetType()), &fDiam);
    p_oTree7->GetValue(p_oPop->GetHeightCode(p_oTree7->GetSpecies(), p_oTree7->GetType()), &fHeight);
    p_oTree7->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree7->GetSpecies(), p_oTree7->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Sapling, Species 4
    fExpectedDiam = 9.577598457;
    fExpectedHeight = 7.791056787;
    fExpectedGrowth = 4.295997428;
    p_oTree8->GetValue(p_oPop->GetDiam10Code(p_oTree8->GetSpecies(), p_oTree8->GetType()), &fDiam);
    p_oTree8->GetValue(p_oPop->GetHeightCode(p_oTree8->GetSpecies(), p_oTree8->GetType()), &fHeight);
    p_oTree8->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree8->GetSpecies(), p_oTree8->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Adult, Species 3
    fExpectedDiam = 22.94124036;
    fExpectedHeight = 16.92018268;
    fExpectedGrowth = 4.90206727;
    p_oTree9->GetValue(p_oPop->GetDbhCode(p_oTree9->GetSpecies(), p_oTree9->GetType()), &fDiam);
    p_oTree9->GetValue(p_oPop->GetHeightCode(p_oTree9->GetSpecies(), p_oTree9->GetType()), &fHeight);
    p_oTree9->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree9->GetSpecies(), p_oTree9->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Adult, Species 3
    fExpectedDiam = 23.75;
    fExpectedHeight = 18.42265861;
    fExpectedGrowth = 6.25;
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
// Test3Run1YearPerTimestep()
// Tests height growth when the timestep length is one year. WriteRelativeGrowthXMLFile5() is
// used to set up the run. 10 trees are created of four species. GLIs are
// assigned to them, and then growth is run. Their diameters, heights, and
// "Growth" values are checked to make sure they are correct.
////////////////////////////////////////////////////////////////////////////
TEST(RelativeGrowth, Test3Run1YearPerTimestep) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTree *p_oTree1, *p_oTree2, *p_oTree3, *p_oTree4, *p_oTree5, *p_oTree6,
    *p_oTree7, *p_oTree8, *p_oTree9, *p_oTree10;
    float fDiam, fHeight, fExpectedDiam, fExpectedHeight, fLight, fGrowth, fExpectedGrowth;

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteRelativeGrowthXMLFile5() );
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
    fExpectedDiam = 5.012011315;
    fExpectedHeight = 7.011530862;
    fExpectedGrowth = 0.060056574;
    p_oTree1->GetValue(p_oPop->GetDiam10Code(p_oTree1->GetSpecies(), p_oTree1->GetType()), &fDiam);
    p_oTree1->GetValue(p_oPop->GetHeightCode(p_oTree1->GetSpecies(), p_oTree1->GetType()), &fHeight);
    p_oTree1->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree1->GetSpecies(), p_oTree1->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Tree 2: Sapling, Species 2
    fExpectedDiam = 5.024494413;
    fExpectedHeight = 8.021800028;
    fExpectedGrowth = 0.122472067;
    p_oTree2->GetValue(p_oPop->GetDiam10Code(p_oTree2->GetSpecies(), p_oTree2->GetType()), &fDiam);
    p_oTree2->GetValue(p_oPop->GetHeightCode(p_oTree2->GetSpecies(), p_oTree2->GetType()), &fHeight);
    p_oTree2->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree2->GetSpecies(), p_oTree2->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Tree 3: Seedling, Species 2
    fExpectedDiam = 1.00294552;
    fExpectedHeight = 0.752621513;
    fExpectedGrowth = 0.0147276;
    p_oTree3->GetValue(p_oPop->GetDiam10Code(p_oTree3->GetSpecies(), p_oTree3->GetType()), &fDiam);
    p_oTree3->GetValue(p_oPop->GetHeightCode(p_oTree3->GetSpecies(), p_oTree3->GetType()), &fHeight);
    p_oTree3->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree3->GetSpecies(), p_oTree3->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Tree 4: Adult, Species 1
    fExpectedDiam = 20.001183;
    fExpectedHeight = 15.00113568;
    fExpectedGrowth = 0.005915004;
    p_oTree4->GetValue(p_oPop->GetDbhCode(p_oTree4->GetSpecies(), p_oTree4->GetType()), &fDiam);
    p_oTree4->GetValue(p_oPop->GetHeightCode(p_oTree4->GetSpecies(), p_oTree4->GetType()), &fHeight);
    p_oTree4->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree4->GetSpecies(), p_oTree4->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Tree 5: Seedling, Species 1
    fExpectedDiam = 1.210962018;
    fExpectedHeight = 1.010523537;
    fExpectedGrowth = 0.054810091;
    p_oTree5->GetValue(p_oPop->GetDiam10Code(p_oTree5->GetSpecies(), p_oTree5->GetType()), &fDiam);
    p_oTree5->GetValue(p_oPop->GetHeightCode(p_oTree5->GetSpecies(), p_oTree5->GetType()), &fHeight);
    p_oTree5->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree5->GetSpecies(), p_oTree5->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Tree 6: Sapling, Species 4
    fExpectedDiam = 5.122488487;
    fExpectedHeight = 7.12787798;
    fExpectedGrowth = 0.612442433;
    p_oTree6->GetValue(p_oPop->GetDiam10Code(p_oTree6->GetSpecies(), p_oTree6->GetType()), &fDiam);
    p_oTree6->GetValue(p_oPop->GetHeightCode(p_oTree6->GetSpecies(), p_oTree6->GetType()), &fHeight);
    p_oTree6->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree6->GetSpecies(), p_oTree6->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Tree 7: Sapling, Species 4
    fExpectedDiam = 5.141826575;
    fExpectedHeight = 8.148066944;
    fExpectedGrowth = 0.709132875;
    p_oTree7->GetValue(p_oPop->GetDiam10Code(p_oTree7->GetSpecies(), p_oTree7->GetType()), &fDiam);
    p_oTree7->GetValue(p_oPop->GetHeightCode(p_oTree7->GetSpecies(), p_oTree7->GetType()), &fHeight);
    p_oTree7->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree7->GetSpecies(), p_oTree7->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Tree 8: Sapling, Species 4
    fExpectedDiam = 7.030772484;
    fExpectedHeight = 6.032126474;
    fExpectedGrowth = 0.153862421;
    p_oTree8->GetValue(p_oPop->GetDiam10Code(p_oTree8->GetSpecies(), p_oTree8->GetType()), &fDiam);
    p_oTree8->GetValue(p_oPop->GetHeightCode(p_oTree8->GetSpecies(), p_oTree8->GetType()), &fHeight);
    p_oTree8->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree8->GetSpecies(), p_oTree8->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Tree 9: Adult, Species 4
    fExpectedDiam = 20.01081839;
    fExpectedHeight = 15.0112944;
    fExpectedGrowth = 0.054091946;
    p_oTree9->GetValue(p_oPop->GetDbhCode(p_oTree9->GetSpecies(), p_oTree9->GetType()), &fDiam);
    p_oTree9->GetValue(p_oPop->GetHeightCode(p_oTree9->GetSpecies(), p_oTree9->GetType()), &fHeight);
    p_oTree9->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree9->GetSpecies(), p_oTree9->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Tree 10: Adult, Species 4
    fExpectedDiam = 20.22556391;
    fExpectedHeight = 16.23548872;
    fExpectedGrowth = 1.127819549;
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
// Test3Run3YearsPerTimestep()
// Tests height growth when the timestep length is three years. WriteRelativeGrowthXMLFile6()
// is used to set up the run. 10 trees are created of four species. GLIs are
// assigned to them, and then growth is run. Their diameters, heights, and
// "Growth" values are checked to make sure they are correct.
////////////////////////////////////////////////////////////////////////////
TEST(RelativeGrowth, Test3Run3YearsPerTimestep) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTree *p_oTree1, *p_oTree2, *p_oTree3, *p_oTree4, *p_oTree5, *p_oTree6,
    *p_oTree7, *p_oTree8, *p_oTree9, *p_oTree10;
    float fDiam, fHeight, fExpectedDiam, fExpectedHeight, fLight, fGrowth, fExpectedGrowth;

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteRelativeGrowthXMLFile6() );
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
    fExpectedDiam = 5.036040466;
    fExpectedHeight = 7.034598848;
    fExpectedGrowth = 0.060067444;
    p_oTree1->GetValue(p_oPop->GetDiam10Code(p_oTree1->GetSpecies(), p_oTree1->GetType()), &fDiam);
    p_oTree1->GetValue(p_oPop->GetHeightCode(p_oTree1->GetSpecies(), p_oTree1->GetType()), &fHeight);
    p_oTree1->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree1->GetSpecies(), p_oTree1->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Tree 2: Sapling, Species 2
    fExpectedDiam = 5.073499227;
    fExpectedHeight = 8.065414312;
    fExpectedGrowth = 0.122498712;
    p_oTree2->GetValue(p_oPop->GetDiam10Code(p_oTree2->GetSpecies(), p_oTree2->GetType()), &fDiam);
    p_oTree2->GetValue(p_oPop->GetHeightCode(p_oTree2->GetSpecies(), p_oTree2->GetType()), &fHeight);
    p_oTree2->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree2->GetSpecies(), p_oTree2->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Tree 3: Seedling, Species 2
    fExpectedDiam = 1.008839024;
    fExpectedHeight = 0.757866732;
    fExpectedGrowth = 0.014731707;
    p_oTree3->GetValue(p_oPop->GetDiam10Code(p_oTree3->GetSpecies(), p_oTree3->GetType()), &fDiam);
    p_oTree3->GetValue(p_oPop->GetHeightCode(p_oTree3->GetSpecies(), p_oTree3->GetType()), &fHeight);
    p_oTree3->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree3->GetSpecies(), p_oTree3->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Tree 4: Adult, Species 1
    fExpectedDiam = 20.00354903;
    fExpectedHeight = 15.00340707;
    fExpectedGrowth = 0.005915053;
    p_oTree4->GetValue(p_oPop->GetDbhCode(p_oTree4->GetSpecies(), p_oTree4->GetType()), &fDiam);
    p_oTree4->GetValue(p_oPop->GetHeightCode(p_oTree4->GetSpecies(), p_oTree4->GetType()), &fHeight);
    p_oTree4->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree4->GetSpecies(), p_oTree4->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Tree 5: Seedling, Species 1
    fExpectedDiam = 1.232923844;
    fExpectedHeight = 1.03160689;
    fExpectedGrowth = 0.054873073;
    p_oTree5->GetValue(p_oPop->GetDiam10Code(p_oTree5->GetSpecies(), p_oTree5->GetType()), &fDiam);
    p_oTree5->GetValue(p_oPop->GetHeightCode(p_oTree5->GetSpecies(), p_oTree5->GetType()), &fHeight);
    p_oTree5->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree5->GetSpecies(), p_oTree5->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Tree 6: Sapling, Species 4
    fExpectedDiam = 5.370806796;
    fExpectedHeight = 7.387122295;
    fExpectedGrowth = 0.618011326;
    p_oTree6->GetValue(p_oPop->GetDiam10Code(p_oTree6->GetSpecies(), p_oTree6->GetType()), &fDiam);
    p_oTree6->GetValue(p_oPop->GetHeightCode(p_oTree6->GetSpecies(), p_oTree6->GetType()), &fHeight);
    p_oTree6->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree6->GetSpecies(), p_oTree6->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Tree 7: Sapling, Species 4
    fExpectedDiam = 5.429399195;
    fExpectedHeight = 8.448292759;
    fExpectedGrowth = 0.715665325;
    p_oTree7->GetValue(p_oPop->GetDiam10Code(p_oTree7->GetSpecies(), p_oTree7->GetType()), &fDiam);
    p_oTree7->GetValue(p_oPop->GetHeightCode(p_oTree7->GetSpecies(), p_oTree7->GetType()), &fHeight);
    p_oTree7->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree7->GetSpecies(), p_oTree7->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Tree 8: Sapling, Species 4
    fExpectedDiam = 7.092564276;
    fExpectedHeight = 6.096637104;
    fExpectedGrowth = 0.154273793;
    p_oTree8->GetValue(p_oPop->GetDiam10Code(p_oTree8->GetSpecies(), p_oTree8->GetType()), &fDiam);
    p_oTree8->GetValue(p_oPop->GetHeightCode(p_oTree8->GetSpecies(), p_oTree8->GetType()), &fHeight);
    p_oTree8->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree8->GetSpecies(), p_oTree8->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Tree 9: Adult, Species 4
    fExpectedDiam = 20.03246738;
    fExpectedHeight = 15.03389595;
    fExpectedGrowth = 0.054112307;
    p_oTree9->GetValue(p_oPop->GetDbhCode(p_oTree9->GetSpecies(), p_oTree9->GetType()), &fDiam);
    p_oTree9->GetValue(p_oPop->GetHeightCode(p_oTree9->GetSpecies(), p_oTree9->GetType()), &fHeight);
    p_oTree9->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree9->GetSpecies(), p_oTree9->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Tree 10: Adult, Species 4
    fExpectedDiam = 20.68165337;
    fExpectedHeight = 16.71164612;
    fExpectedGrowth = 1.136088955;
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
// WriteRelativeGrowthXMLFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteRelativeGrowthXMLFile1() {
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
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">0.5944</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_3\">0.7059</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_4\">0.7059</tr_cdtdVal>"
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
       //Leave in one light so that "Light" will be registerd
       << "<behaviorName>ConstantGLI</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RelUnlimGrowth</behaviorName>"
       << "<version>1.1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RelRadialGrowth</behaviorName>"
       << "<version>1.1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RelBAGrowth</behaviorName>"
       << "<version>1.1</version>"
       << "<listPosition>4</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RelUnlimGrowth diam only</behaviorName>"
       << "<version>1.1</version>"
       << "<listPosition>5</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RelRadialGrowth diam only</behaviorName>"
       << "<version>1.1</version>"
       << "<listPosition>6</listPosition>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RelBAGrowth diam only</behaviorName>"
       << "<version>1.1</version>"
       << "<listPosition>7</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>HeightIncrementer</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>8</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<ConstantGLI1>"
       << "<li_constGLI>100</li_constGLI>"
       << "</ConstantGLI1>"
       << "<RelUnlimGrowth2>"
       << "<gr_asympDiameterGrowth>"
       << "<gr_adgVal species=\"Species_1\">0.858</gr_adgVal>"
       << "</gr_asympDiameterGrowth>"
       << "<gr_slopeGrowthResponse>"
       << "<gr_sgrVal species=\"Species_1\">0.027</gr_sgrVal>"
       << "</gr_slopeGrowthResponse>"
       << "<gr_relGrowthDiamExp>"
       << "<gr_rgdeVal species=\"Species_1\">1</gr_rgdeVal>"
       << "</gr_relGrowthDiamExp>"
       << "</RelUnlimGrowth2>"
       << "<RelRadialGrowth3>"
       << "<gr_adultConstRadialInc>"
       << "<gr_acriVal species=\"Species_2\">6.18</gr_acriVal>"
       << "</gr_adultConstRadialInc>"
       << "<gr_asympDiameterGrowth>"
       << "<gr_adgVal species=\"Species_2\">0.799</gr_adgVal>"
       << "</gr_asympDiameterGrowth>"
       << "<gr_slopeGrowthResponse>"
       << "<gr_sgrVal species=\"Species_2\">0.019</gr_sgrVal>"
       << "</gr_slopeGrowthResponse>"
       << "<gr_relGrowthDiamExp>"
       << "<gr_rgdeVal species=\"Species_2\">1</gr_rgdeVal>"
       << "</gr_relGrowthDiamExp>"
       << "</RelRadialGrowth3>"
       << "<RelBAGrowth4>"
       << "<gr_adultConstAreaInc>"
       << "<gr_acaiVal species=\"Species_1\">0.45</gr_acaiVal>"
       << "</gr_adultConstAreaInc>"
       << "<gr_asympDiameterGrowth>"
       << "<gr_adgVal species=\"Species_1\">0.858</gr_adgVal>"
       << "</gr_asympDiameterGrowth>"
       << "<gr_slopeGrowthResponse>"
       << "<gr_sgrVal species=\"Species_1\">0.027</gr_sgrVal>"
       << "</gr_slopeGrowthResponse>"
       << "<gr_relGrowthDiamExp>"
       << "<gr_rgdeVal species=\"Species_1\">1</gr_rgdeVal>"
       << "</gr_relGrowthDiamExp>"
       << "</RelBAGrowth4>"
       << "<RelUnlimGrowth5>"
       << "<gr_asympDiameterGrowth>"
       << "<gr_adgVal species=\"Species_3\">0.911</gr_adgVal>"
       << "</gr_asympDiameterGrowth>"
       << "<gr_slopeGrowthResponse>"
       << "<gr_sgrVal species=\"Species_3\">0.01</gr_sgrVal>"
       << "</gr_slopeGrowthResponse>"
       << "<gr_relGrowthDiamExp>"
       << "<gr_rgdeVal species=\"Species_3\">1</gr_rgdeVal>"
       << "</gr_relGrowthDiamExp>"
       << "</RelUnlimGrowth5>"
       << "<RelRadialGrowth6>"
       << "<gr_adultConstRadialInc>"
       << "<gr_acriVal species=\"Species_4\">5.92</gr_acriVal>"
       << "</gr_adultConstRadialInc>"
       << "<gr_asympDiameterGrowth>"
       << "<gr_adgVal species=\"Species_4\">1.044</gr_adgVal>"
       << "</gr_asympDiameterGrowth>"
       << "<gr_slopeGrowthResponse>"
       << "<gr_sgrVal species=\"Species_4\">0.015</gr_sgrVal>"
       << "</gr_slopeGrowthResponse>"
       << "<gr_relGrowthDiamExp>"
       << "<gr_rgdeVal species=\"Species_4\">1</gr_rgdeVal>"
       << "</gr_relGrowthDiamExp>"
       << "</RelRadialGrowth6>"
       << "<RelBAGrowth7>"
       << "<gr_adultConstAreaInc>"
       << "<gr_acaiVal species=\"Species_3\">0.25</gr_acaiVal>"
       << "</gr_adultConstAreaInc>"
       << "<gr_asympDiameterGrowth>"
       << "<gr_adgVal species=\"Species_3\">0.911</gr_adgVal>"
       << "</gr_asympDiameterGrowth>"
       << "<gr_slopeGrowthResponse>"
       << "<gr_sgrVal species=\"Species_3\">0.01</gr_sgrVal>"
       << "</gr_slopeGrowthResponse>"
       << "<gr_relGrowthDiamExp>"
       << "<gr_rgdeVal species=\"Species_3\">1</gr_rgdeVal>"
       << "</gr_relGrowthDiamExp>"
       << "</RelBAGrowth7>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteRelativeGrowthXMLFile2()
////////////////////////////////////////////////////////////////////////////
const char* WriteRelativeGrowthXMLFile2() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //Write file
  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>3</timesteps>"
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
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">0.5944</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_3\">0.7059</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_4\">0.7059</tr_cdtdVal>"
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
       //Leave in one light so that "Light" will be registerd
       << "<behaviorName>ConstantGLI</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RelUnlimGrowth</behaviorName>"
       << "<version>1.1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RelRadialGrowth</behaviorName>"
       << "<version>1.1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RelBAGrowth</behaviorName>"
       << "<version>1.1</version>"
       << "<listPosition>4</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RelUnlimGrowth diam only</behaviorName>"
       << "<version>1.1</version>"
       << "<listPosition>5</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RelRadialGrowth diam only</behaviorName>"
       << "<version>1.1</version>"
       << "<listPosition>6</listPosition>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RelBAGrowth diam only</behaviorName>"
       << "<version>1.1</version>"
       << "<listPosition>7</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>HeightIncrementer</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>8</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<ConstantGLI1>"
       << "<li_constGLI>100</li_constGLI>"
       << "</ConstantGLI1>"
       << "<RelUnlimGrowth2>"
       << "<gr_asympDiameterGrowth>"
       << "<gr_adgVal species=\"Species_1\">0.858</gr_adgVal>"
       << "</gr_asympDiameterGrowth>"
       << "<gr_slopeGrowthResponse>"
       << "<gr_sgrVal species=\"Species_1\">0.027</gr_sgrVal>"
       << "</gr_slopeGrowthResponse>"
       << "<gr_relGrowthDiamExp>"
       << "<gr_rgdeVal species=\"Species_1\">1</gr_rgdeVal>"
       << "</gr_relGrowthDiamExp>"
       << "</RelUnlimGrowth2>"
       << "<RelRadialGrowth3>"
       << "<gr_adultConstRadialInc>"
       << "<gr_acriVal species=\"Species_2\">6.18</gr_acriVal>"
       << "</gr_adultConstRadialInc>"
       << "<gr_asympDiameterGrowth>"
       << "<gr_adgVal species=\"Species_2\">0.799</gr_adgVal>"
       << "</gr_asympDiameterGrowth>"
       << "<gr_slopeGrowthResponse>"
       << "<gr_sgrVal species=\"Species_2\">0.019</gr_sgrVal>"
       << "</gr_slopeGrowthResponse>"
       << "<gr_relGrowthDiamExp>"
       << "<gr_rgdeVal species=\"Species_2\">1</gr_rgdeVal>"
       << "</gr_relGrowthDiamExp>"
       << "</RelRadialGrowth3>"
       << "<RelBAGrowth4>"
       << "<gr_adultConstAreaInc>"
       << "<gr_acaiVal species=\"Species_1\">0.45</gr_acaiVal>"
       << "</gr_adultConstAreaInc>"
       << "<gr_asympDiameterGrowth>"
       << "<gr_adgVal species=\"Species_1\">0.858</gr_adgVal>"
       << "</gr_asympDiameterGrowth>"
       << "<gr_slopeGrowthResponse>"
       << "<gr_sgrVal species=\"Species_1\">0.027</gr_sgrVal>"
       << "</gr_slopeGrowthResponse>"
       << "<gr_relGrowthDiamExp>"
       << "<gr_rgdeVal species=\"Species_1\">1</gr_rgdeVal>"
       << "</gr_relGrowthDiamExp>"
       << "</RelBAGrowth4>"
       << "<RelUnlimGrowth5>"
       << "<gr_asympDiameterGrowth>"
       << "<gr_adgVal species=\"Species_3\">0.911</gr_adgVal>"
       << "</gr_asympDiameterGrowth>"
       << "<gr_slopeGrowthResponse>"
       << "<gr_sgrVal species=\"Species_3\">0.01</gr_sgrVal>"
       << "</gr_slopeGrowthResponse>"
       << "<gr_relGrowthDiamExp>"
       << "<gr_rgdeVal species=\"Species_3\">1</gr_rgdeVal>"
       << "</gr_relGrowthDiamExp>"
       << "</RelUnlimGrowth5>"
       << "<RelRadialGrowth6>"
       << "<gr_adultConstRadialInc>"
       << "<gr_acriVal species=\"Species_4\">5.92</gr_acriVal>"
       << "</gr_adultConstRadialInc>"
       << "<gr_asympDiameterGrowth>"
       << "<gr_adgVal species=\"Species_4\">1.044</gr_adgVal>"
       << "</gr_asympDiameterGrowth>"
       << "<gr_slopeGrowthResponse>"
       << "<gr_sgrVal species=\"Species_4\">0.015</gr_sgrVal>"
       << "</gr_slopeGrowthResponse>"
       << "<gr_relGrowthDiamExp>"
       << "<gr_rgdeVal species=\"Species_4\">1</gr_rgdeVal>"
       << "</gr_relGrowthDiamExp>"
       << "</RelRadialGrowth6>"
       << "<RelBAGrowth7>"
       << "<gr_adultConstAreaInc>"
       << "<gr_acaiVal species=\"Species_3\">0.25</gr_acaiVal>"
       << "</gr_adultConstAreaInc>"
       << "<gr_asympDiameterGrowth>"
       << "<gr_adgVal species=\"Species_3\">0.911</gr_adgVal>"
       << "</gr_asympDiameterGrowth>"
       << "<gr_slopeGrowthResponse>"
       << "<gr_sgrVal species=\"Species_3\">0.01</gr_sgrVal>"
       << "</gr_slopeGrowthResponse>"
       << "<gr_relGrowthDiamExp>"
       << "<gr_rgdeVal species=\"Species_3\">1</gr_rgdeVal>"
       << "</gr_relGrowthDiamExp>"
       << "</RelBAGrowth7>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteRelativeGrowthXMLFile3()
////////////////////////////////////////////////////////////////////////////
const char* WriteRelativeGrowthXMLFile3() {
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
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">0.5944</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_3\">0.7059</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_4\">0.7059</tr_cdtdVal>"
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
       //Leave in one light so that "Light" will be registerd
       << "<behaviorName>ConstantGLI</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RelUnlimGrowth</behaviorName>"
       << "<listPosition>2</listPosition>"
       << "<version>1.1</version>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RelRadialGrowth</behaviorName>"
       << "<version>1.1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RelBAGrowth</behaviorName>"
       << "<version>1.1</version>"
       << "<listPosition>4</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RelUnlimGrowth diam only</behaviorName>"
       << "<version>1.1</version>"
       << "<listPosition>5</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RelRadialGrowth diam only</behaviorName>"
       << "<version>1.1</version>"
       << "<listPosition>6</listPosition>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RelBAGrowth diam only</behaviorName>"
       << "<version>1.1</version>"
       << "<listPosition>7</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>HeightIncrementer</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>8</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<ConstantGLI1>"
       << "<li_constGLI>100</li_constGLI>"
       << "</ConstantGLI1>"
       << "<RelUnlimGrowth2>"
       << "<gr_asympDiameterGrowth>"
       << "<gr_adgVal species=\"Species_1\">0.858</gr_adgVal>"
       << "</gr_asympDiameterGrowth>"
       << "<gr_slopeGrowthResponse>"
       << "<gr_sgrVal species=\"Species_1\">0.027</gr_sgrVal>"
       << "</gr_slopeGrowthResponse>"
       << "<gr_relGrowthDiamExp>"
       << "<gr_rgdeVal species=\"Species_1\">1.1</gr_rgdeVal>"
       << "</gr_relGrowthDiamExp>"
       << "</RelUnlimGrowth2>"
       << "<RelRadialGrowth3>"
       << "<gr_adultConstRadialInc>"
       << "<gr_acriVal species=\"Species_2\">6.18</gr_acriVal>"
       << "</gr_adultConstRadialInc>"
       << "<gr_asympDiameterGrowth>"
       << "<gr_adgVal species=\"Species_2\">0.799</gr_adgVal>"
       << "</gr_asympDiameterGrowth>"
       << "<gr_slopeGrowthResponse>"
       << "<gr_sgrVal species=\"Species_2\">0.019</gr_sgrVal>"
       << "</gr_slopeGrowthResponse>"
       << "<gr_relGrowthDiamExp>"
       << "<gr_rgdeVal species=\"Species_2\">0.8</gr_rgdeVal>"
       << "</gr_relGrowthDiamExp>"
       << "</RelRadialGrowth3>"
       << "<RelBAGrowth4>"
       << "<gr_adultConstAreaInc>"
       << "<gr_acaiVal species=\"Species_1\">0.45</gr_acaiVal>"
       << "</gr_adultConstAreaInc>"
       << "<gr_asympDiameterGrowth>"
       << "<gr_adgVal species=\"Species_1\">0.858</gr_adgVal>"
       << "</gr_asympDiameterGrowth>"
       << "<gr_slopeGrowthResponse>"
       << "<gr_sgrVal species=\"Species_1\">0.027</gr_sgrVal>"
       << "</gr_slopeGrowthResponse>"
       << "<gr_relGrowthDiamExp>"
       << "<gr_rgdeVal species=\"Species_1\">1.1</gr_rgdeVal>"
       << "</gr_relGrowthDiamExp>"
       << "</RelBAGrowth4>"
       << "<RelUnlimGrowth5>"
       << "<gr_asympDiameterGrowth>"
       << "<gr_adgVal species=\"Species_3\">0.911</gr_adgVal>"
       << "</gr_asympDiameterGrowth>"
       << "<gr_slopeGrowthResponse>"
       << "<gr_sgrVal species=\"Species_3\">0.01</gr_sgrVal>"
       << "</gr_slopeGrowthResponse>"
       << "<gr_relGrowthDiamExp>"
       << "<gr_rgdeVal species=\"Species_3\">1.3</gr_rgdeVal>"
       << "</gr_relGrowthDiamExp>"
       << "</RelUnlimGrowth5>"
       << "<RelRadialGrowth6>"
       << "<gr_adultConstRadialInc>"
       << "<gr_acriVal species=\"Species_4\">5.92</gr_acriVal>"
       << "</gr_adultConstRadialInc>"
       << "<gr_asympDiameterGrowth>"
       << "<gr_adgVal species=\"Species_4\">1.044</gr_adgVal>"
       << "</gr_asympDiameterGrowth>"
       << "<gr_slopeGrowthResponse>"
       << "<gr_sgrVal species=\"Species_4\">0.015</gr_sgrVal>"
       << "</gr_slopeGrowthResponse>"
       << "<gr_relGrowthDiamExp>"
       << "<gr_rgdeVal species=\"Species_4\">0.9</gr_rgdeVal>"
       << "</gr_relGrowthDiamExp>"
       << "</RelRadialGrowth6>"
       << "<RelBAGrowth7>"
       << "<gr_adultConstAreaInc>"
       << "<gr_acaiVal species=\"Species_3\">0.25</gr_acaiVal>"
       << "</gr_adultConstAreaInc>"
       << "<gr_asympDiameterGrowth>"
       << "<gr_adgVal species=\"Species_3\">0.911</gr_adgVal>"
       << "</gr_asympDiameterGrowth>"
       << "<gr_slopeGrowthResponse>"
       << "<gr_sgrVal species=\"Species_3\">0.01</gr_sgrVal>"
       << "</gr_slopeGrowthResponse>"
       << "<gr_relGrowthDiamExp>"
       << "<gr_rgdeVal species=\"Species_3\">1.3</gr_rgdeVal>"
       << "</gr_relGrowthDiamExp>"
       << "</RelBAGrowth7>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteRelativeGrowthXMLFile4()
////////////////////////////////////////////////////////////////////////////
const char* WriteRelativeGrowthXMLFile4() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //Write file
  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>3</timesteps>"
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
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">0.5944</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_3\">0.7059</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_4\">0.7059</tr_cdtdVal>"
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
       //Leave in one light so that "Light" will be registerd
       << "<behaviorName>ConstantGLI</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RelUnlimGrowth</behaviorName>"
       << "<version>1.1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RelRadialGrowth</behaviorName>"
       << "<version>1.1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RelBAGrowth</behaviorName>"
       << "<version>1.1</version>"
       << "<listPosition>4</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RelUnlimGrowth diam only</behaviorName>"
       << "<version>1.1</version>"
       << "<listPosition>5</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RelRadialGrowth diam only</behaviorName>"
       << "<version>1.1</version>"
       << "<listPosition>6</listPosition>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RelBAGrowth diam only</behaviorName>"
       << "<version>1.1</version>"
       << "<listPosition>7</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>HeightIncrementer</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>8</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<ConstantGLI1>"
       << "<li_constGLI>100</li_constGLI>"
       << "</ConstantGLI1>"
       << "<RelUnlimGrowth2>"
       << "<gr_asympDiameterGrowth>"
       << "<gr_adgVal species=\"Species_1\">0.858</gr_adgVal>"
       << "</gr_asympDiameterGrowth>"
       << "<gr_slopeGrowthResponse>"
       << "<gr_sgrVal species=\"Species_1\">0.027</gr_sgrVal>"
       << "</gr_slopeGrowthResponse>"
       << "<gr_relGrowthDiamExp>"
       << "<gr_rgdeVal species=\"Species_1\">1.1</gr_rgdeVal>"
       << "</gr_relGrowthDiamExp>"
       << "</RelUnlimGrowth2>"
       << "<RelRadialGrowth3>"
       << "<gr_adultConstRadialInc>"
       << "<gr_acriVal species=\"Species_2\">6.18</gr_acriVal>"
       << "</gr_adultConstRadialInc>"
       << "<gr_asympDiameterGrowth>"
       << "<gr_adgVal species=\"Species_2\">0.799</gr_adgVal>"
       << "</gr_asympDiameterGrowth>"
       << "<gr_slopeGrowthResponse>"
       << "<gr_sgrVal species=\"Species_2\">0.019</gr_sgrVal>"
       << "</gr_slopeGrowthResponse>"
       << "<gr_relGrowthDiamExp>"
       << "<gr_rgdeVal species=\"Species_2\">0.8</gr_rgdeVal>"
       << "</gr_relGrowthDiamExp>"
       << "</RelRadialGrowth3>"
       << "<RelBAGrowth4>"
       << "<gr_adultConstAreaInc>"
       << "<gr_acaiVal species=\"Species_1\">0.45</gr_acaiVal>"
       << "</gr_adultConstAreaInc>"
       << "<gr_asympDiameterGrowth>"
       << "<gr_adgVal species=\"Species_1\">0.858</gr_adgVal>"
       << "</gr_asympDiameterGrowth>"
       << "<gr_slopeGrowthResponse>"
       << "<gr_sgrVal species=\"Species_1\">0.027</gr_sgrVal>"
       << "</gr_slopeGrowthResponse>"
       << "<gr_relGrowthDiamExp>"
       << "<gr_rgdeVal species=\"Species_1\">1.1</gr_rgdeVal>"
       << "</gr_relGrowthDiamExp>"
       << "</RelBAGrowth4>"
       << "<RelUnlimGrowth5>"
       << "<gr_asympDiameterGrowth>"
       << "<gr_adgVal species=\"Species_3\">0.911</gr_adgVal>"
       << "</gr_asympDiameterGrowth>"
       << "<gr_slopeGrowthResponse>"
       << "<gr_sgrVal species=\"Species_3\">0.01</gr_sgrVal>"
       << "</gr_slopeGrowthResponse>"
       << "<gr_relGrowthDiamExp>"
       << "<gr_rgdeVal species=\"Species_3\">1.3</gr_rgdeVal>"
       << "</gr_relGrowthDiamExp>"
       << "</RelUnlimGrowth5>"
       << "<RelRadialGrowth6>"
       << "<gr_adultConstRadialInc>"
       << "<gr_acriVal species=\"Species_4\">5.92</gr_acriVal>"
       << "</gr_adultConstRadialInc>"
       << "<gr_asympDiameterGrowth>"
       << "<gr_adgVal species=\"Species_4\">1.044</gr_adgVal>"
       << "</gr_asympDiameterGrowth>"
       << "<gr_slopeGrowthResponse>"
       << "<gr_sgrVal species=\"Species_4\">0.015</gr_sgrVal>"
       << "</gr_slopeGrowthResponse>"
       << "<gr_relGrowthDiamExp>"
       << "<gr_rgdeVal species=\"Species_4\">0.9</gr_rgdeVal>"
       << "</gr_relGrowthDiamExp>"
       << "</RelRadialGrowth6>"
       << "<RelBAGrowth7>"
       << "<gr_adultConstAreaInc>"
       << "<gr_acaiVal species=\"Species_3\">0.25</gr_acaiVal>"
       << "</gr_adultConstAreaInc>"
       << "<gr_asympDiameterGrowth>"
       << "<gr_adgVal species=\"Species_3\">0.911</gr_adgVal>"
       << "</gr_asympDiameterGrowth>"
       << "<gr_slopeGrowthResponse>"
       << "<gr_sgrVal species=\"Species_3\">0.01</gr_sgrVal>"
       << "</gr_slopeGrowthResponse>"
       << "<gr_relGrowthDiamExp>"
       << "<gr_rgdeVal species=\"Species_3\">1.3</gr_rgdeVal>"
       << "</gr_relGrowthDiamExp>"
       << "</RelBAGrowth7>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteRelativeGrowthXMLFile5()
////////////////////////////////////////////////////////////////////////////
const char* WriteRelativeGrowthXMLFile5() {
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

  WriteRelativeGrowthRun3CommonStuff(oOut);

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteRelativeGrowthXMLFile6()
////////////////////////////////////////////////////////////////////////////
const char* WriteRelativeGrowthXMLFile6() {
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

  WriteRelativeGrowthRun3CommonStuff(oOut);

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteRelativeGrowthRun3CommonStuff()
/////////////////////////////////////////////////////////////////////////////
void WriteRelativeGrowthRun3CommonStuff(std::fstream &oOut)
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
       << "<behaviorName>RelativeHeight</behaviorName>"
       << "<version>1.2</version>"
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
       << "<RelMMHeight2>"
       << "<gr_asympHeightGrowth>"
       << "<gr_ahgVal species=\"Species_1\">0.858</gr_ahgVal>"
       << "<gr_ahgVal species=\"Species_2\">7.99</gr_ahgVal>"
       << "<gr_ahgVal species=\"Species_4\">1.044</gr_ahgVal>"
       << "</gr_asympHeightGrowth>"
       << "<gr_slopeHeightGrowthResponse>"
       << "<gr_shgrVal species=\"Species_1\">0.027</gr_shgrVal>"
       << "<gr_shgrVal species=\"Species_2\">0.019</gr_shgrVal>"
       << "<gr_shgrVal species=\"Species_4\">0.015</gr_shgrVal>"
       << "</gr_slopeHeightGrowthResponse>"
       << "<gr_relHeightGrowthHeightExp>"
       << "<gr_rhgheVal species=\"Species_1\">0.11</gr_rhgheVal>"
       << "<gr_rhgheVal species=\"Species_2\">0.08</gr_rhgheVal>"
       << "<gr_rhgheVal species=\"Species_4\">0.5</gr_rhgheVal>"
       << "</gr_relHeightGrowthHeightExp>"
       << "</RelMMHeight2>"
       << "</paramFile>";
}
