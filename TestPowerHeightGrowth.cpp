//---------------------------------------------------------------------------
// TestPowerHeightGrowth.cpp
//---------------------------------------------------------------------------
#include "TestPowerHeightGrowth.h"
#include <gtest/gtest.h>
#include <fstream>
#include <math.h>
#include "TreePopulation.h"
#include "SimManager.h"
#include "BehaviorBase.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////
// TestRun1YearPerTimestep()
// Tests height growth when the timestep length is one year.
// WritePowerHeightGrowthXMLFile1() is used to set up the run. 10 trees are
// created of four species. Growth is run. Their diameters, heights, and
// "Growth" values are checked to make sure they are correct.
////////////////////////////////////////////////////////////////////////////
TEST(PowerHeightGrowth, TestRun1YearPerTimestep) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTree *p_oTree1, *p_oTree2, *p_oTree3, *p_oTree4, *p_oTree5, *p_oTree6,
    *p_oTree7, *p_oTree8, *p_oTree9, *p_oTree10;
    float fDiam, fHeight, fExpectedDiam, fExpectedHeight, fGrowth, fExpectedGrowth;

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WritePowerHeightGrowthXMLFile1() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create our ten trees and set diameter and height for each
    //Tree 1: Sapling, Species 1
    fDiam = 5;
    fHeight = 7;
    p_oTree1 = p_oPop->CreateTree(1, 1, 0, clTreePopulation::sapling, fDiam);
    p_oTree1->SetValue(p_oPop->GetHeightCode(p_oTree1->GetSpecies(), p_oTree1->GetType()), fHeight, false, false);

    //Tree 2: Sapling, Species 2
    fDiam = 5;
    fHeight = 8;
    p_oTree2 = p_oPop->CreateTree(2, 2, 1, clTreePopulation::sapling, fDiam);
    p_oTree2->SetValue(p_oPop->GetHeightCode(p_oTree2->GetSpecies(), p_oTree2->GetType()), fHeight, false, false);

    //Tree 3: Seedling, Species 2
    fDiam = 1;
    fHeight = 0.75;
    p_oTree3 = p_oPop->CreateTree(3, 3, 1, clTreePopulation::seedling, fDiam);
    p_oTree3->SetValue(p_oPop->GetHeightCode(p_oTree3->GetSpecies(), p_oTree3->GetType()), fHeight, false, false);

    //Tree 4: Adult, Species 1
    fDiam = 20;
    fHeight = 15;
    p_oTree4 = p_oPop->CreateTree(4, 4, 0, clTreePopulation::adult, fDiam);
    p_oTree4->SetValue(p_oPop->GetHeightCode(p_oTree4->GetSpecies(), p_oTree4->GetType()), fHeight, false, false);

    //Tree 5: Seedling, Species 1
    fDiam = 1.2;
    fHeight = 1;
    p_oTree5 = p_oPop->CreateTree(5, 5, 0, clTreePopulation::seedling, fDiam);
    p_oTree5->SetValue(p_oPop->GetHeightCode(p_oTree5->GetSpecies(), p_oTree5->GetType()), fHeight, false, false);

    //Tree 6: Sapling, Species 4
    fDiam = 5;
    fHeight = 7;
    p_oTree6 = p_oPop->CreateTree(6, 6, 3, clTreePopulation::sapling, fDiam);
    p_oTree6->SetValue(p_oPop->GetHeightCode(p_oTree6->GetSpecies(), p_oTree6->GetType()), fHeight, false, false);

    //Tree 7: Sapling, Species 4
    fDiam = 5;
    fHeight = 8;
    p_oTree7 = p_oPop->CreateTree(7, 7, 3, clTreePopulation::sapling, fDiam);
    p_oTree7->SetValue(p_oPop->GetHeightCode(p_oTree7->GetSpecies(), p_oTree7->GetType()), fHeight, false, false);

    //Tree 8: Sapling, Species 4
    fDiam = 7;
    fHeight = 6;
    p_oTree8 = p_oPop->CreateTree(8, 8, 3, clTreePopulation::sapling, fDiam);
    p_oTree8->SetValue(p_oPop->GetHeightCode(p_oTree8->GetSpecies(), p_oTree8->GetType()), fHeight, false, false);

    //Tree 9: Adult, Species 4
    fDiam = 20;
    fHeight = 15;
    p_oTree9 = p_oPop->CreateTree(9, 9, 3, clTreePopulation::adult, fDiam);
    p_oTree9->SetValue(p_oPop->GetHeightCode(p_oTree9->GetSpecies(), p_oTree9->GetType()), fHeight, false, false);

    //Tree 10: Adult, Species 4
    fDiam = 20;
    fHeight = 16;
    p_oTree10 = p_oPop->CreateTree(10, 10, 3, clTreePopulation::adult, fDiam);
    p_oTree10->SetValue(p_oPop->GetHeightCode(p_oTree10->GetSpecies(), p_oTree10->GetType()), fHeight, false, false);

    p_oSimManager->RunSim(1);

    //Confirm all trees
    //Tree 1: Sapling, Species 1
    fExpectedDiam = 5.052407389;
    fExpectedHeight = 7.050311094;
    fExpectedGrowth = 0.262036946;
    p_oTree1->GetValue(p_oPop->GetDiam10Code(p_oTree1->GetSpecies(), p_oTree1->GetType()), &fDiam);
    p_oTree1->GetValue(p_oPop->GetHeightCode(p_oTree1->GetSpecies(), p_oTree1->GetType()), &fHeight);
    p_oTree1->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree1->GetSpecies(), p_oTree1->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Tree 2: Sapling, Species 2
    fExpectedDiam = 5.319700908;
    fExpectedHeight = 8.284533808;
    fExpectedGrowth = 1.598504542;
    p_oTree2->GetValue(p_oPop->GetDiam10Code(p_oTree2->GetSpecies(), p_oTree2->GetType()), &fDiam);
    p_oTree2->GetValue(p_oPop->GetHeightCode(p_oTree2->GetSpecies(), p_oTree2->GetType()), &fHeight);
    p_oTree2->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree2->GetSpecies(), p_oTree2->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Tree 3: Seedling, Species 2
    fExpectedDiam = 1.203900557;
    fExpectedHeight = 0.931471496;
    fExpectedGrowth = 1.019502786;
    p_oTree3->GetValue(p_oPop->GetDiam10Code(p_oTree3->GetSpecies(), p_oTree3->GetType()), &fDiam);
    p_oTree3->GetValue(p_oPop->GetHeightCode(p_oTree3->GetSpecies(), p_oTree3->GetType()), &fHeight);
    p_oTree3->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree3->GetSpecies(), p_oTree3->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Tree 4: Adult, Species 1
    fExpectedDiam = 20.06438144;
    fExpectedHeight = 15.06180618;
    fExpectedGrowth = 0.321907206;
    p_oTree4->GetValue(p_oPop->GetDbhCode(p_oTree4->GetSpecies(), p_oTree4->GetType()), &fDiam);
    p_oTree4->GetValue(p_oPop->GetHeightCode(p_oTree4->GetSpecies(), p_oTree4->GetType()), &fHeight);
    p_oTree4->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree4->GetSpecies(), p_oTree4->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Tree 5: Seedling, Species 1
    fExpectedDiam = 1.230989606;
    fExpectedHeight = 1.029750022;
    fExpectedGrowth = 0.15494803;
    p_oTree5->GetValue(p_oPop->GetDiam10Code(p_oTree5->GetSpecies(), p_oTree5->GetType()), &fDiam);
    p_oTree5->GetValue(p_oPop->GetHeightCode(p_oTree5->GetSpecies(), p_oTree5->GetType()), &fHeight);
    p_oTree5->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree5->GetSpecies(), p_oTree5->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Tree 6: Sapling, Species 4
    fExpectedDiam = 5.026715586;
    fExpectedHeight = 7.027891072;
    fExpectedGrowth = 0.13357793;
    p_oTree6->GetValue(p_oPop->GetDiam10Code(p_oTree6->GetSpecies(), p_oTree6->GetType()), &fDiam);
    p_oTree6->GetValue(p_oPop->GetHeightCode(p_oTree6->GetSpecies(), p_oTree6->GetType()), &fHeight);
    p_oTree6->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree6->GetSpecies(), p_oTree6->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Tree 7: Sapling, Species 4
    fExpectedDiam = 5.027256086;
    fExpectedHeight = 8.028455354;
    fExpectedGrowth = 0.136280432;
    p_oTree7->GetValue(p_oPop->GetDiam10Code(p_oTree7->GetSpecies(), p_oTree7->GetType()), &fDiam);
    p_oTree7->GetValue(p_oPop->GetHeightCode(p_oTree7->GetSpecies(), p_oTree7->GetType()), &fHeight);
    p_oTree7->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree7->GetSpecies(), p_oTree7->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Tree 8: Sapling, Species 4
    fExpectedDiam = 7.026104939;
    fExpectedHeight = 6.027253557;
    fExpectedGrowth = 0.130524696;
    p_oTree8->GetValue(p_oPop->GetDiam10Code(p_oTree8->GetSpecies(), p_oTree8->GetType()), &fDiam);
    p_oTree8->GetValue(p_oPop->GetHeightCode(p_oTree8->GetSpecies(), p_oTree8->GetType()), &fHeight);
    p_oTree8->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree8->GetSpecies(), p_oTree8->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Tree 9: Adult, Species 4
    fExpectedDiam = 20.02995116;
    fExpectedHeight = 15.03126901;
    fExpectedGrowth = 0.149755814;
    p_oTree9->GetValue(p_oPop->GetDbhCode(p_oTree9->GetSpecies(), p_oTree9->GetType()), &fDiam);
    p_oTree9->GetValue(p_oPop->GetHeightCode(p_oTree9->GetSpecies(), p_oTree9->GetType()), &fHeight);
    p_oTree9->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree9->GetSpecies(), p_oTree9->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Tree 10: Adult, Species 4
    fExpectedDiam = 20.03024252;
    fExpectedHeight = 16.03157319;
    fExpectedGrowth = 0.151212607;
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
// TestRun3YearsPerTimestep()
// Tests height growth when the timestep length is three years.
// WritePowerHeightGrowthXMLFile2() is used to set up the run. 10 trees are
// created of four species. Growth is run. Their diameters, heights, and
// "Growth" values are checked to make sure they are correct.
////////////////////////////////////////////////////////////////////////////
TEST(PowerHeightGrowth, TestRun3YearsPerTimestep) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTree *p_oTree1, *p_oTree2, *p_oTree3, *p_oTree4, *p_oTree5, *p_oTree6,
    *p_oTree7, *p_oTree8, *p_oTree9, *p_oTree10;
    float fDiam, fHeight, fExpectedDiam, fExpectedHeight, fGrowth, fExpectedGrowth;

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WritePowerHeightGrowthXMLFile2() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create our ten trees and set diameter and height for each
    //Tree 1: Sapling, Species 1
    fDiam = 5;
    fHeight = 7;
    p_oTree1 = p_oPop->CreateTree(1, 1, 0, clTreePopulation::sapling, fDiam);
    p_oTree1->SetValue(p_oPop->GetHeightCode(p_oTree1->GetSpecies(), p_oTree1->GetType()), fHeight, false, false);

    //Tree 2: Sapling, Species 2
    fDiam = 5;
    fHeight = 8;
    p_oTree2 = p_oPop->CreateTree(2, 2, 1, clTreePopulation::sapling, fDiam);
    p_oTree2->SetValue(p_oPop->GetHeightCode(p_oTree2->GetSpecies(), p_oTree2->GetType()), fHeight, false, false);

    //Tree 3: Seedling, Species 2
    fDiam = 1;
    fHeight = 0.75;
    p_oTree3 = p_oPop->CreateTree(3, 3, 1, clTreePopulation::seedling, fDiam);
    p_oTree3->SetValue(p_oPop->GetHeightCode(p_oTree3->GetSpecies(), p_oTree3->GetType()), fHeight, false, false);

    //Tree 4: Adult, Species 1
    fDiam = 20;
    fHeight = 15;
    p_oTree4 = p_oPop->CreateTree(4, 4, 0, clTreePopulation::adult, fDiam);
    p_oTree4->SetValue(p_oPop->GetHeightCode(p_oTree4->GetSpecies(), p_oTree4->GetType()), fHeight, false, false);

    //Tree 5: Seedling, Species 1
    fDiam = 1.2;
    fHeight = 1;
    p_oTree5 = p_oPop->CreateTree(5, 5, 0, clTreePopulation::seedling, fDiam);
    p_oTree5->SetValue(p_oPop->GetHeightCode(p_oTree5->GetSpecies(), p_oTree5->GetType()), fHeight, false, false);

    //Tree 6: Sapling, Species 4
    fDiam = 5;
    fHeight = 7;
    p_oTree6 = p_oPop->CreateTree(6, 6, 3, clTreePopulation::sapling, fDiam);
    p_oTree6->SetValue(p_oPop->GetHeightCode(p_oTree6->GetSpecies(), p_oTree6->GetType()), fHeight, false, false);

    //Tree 7: Sapling, Species 4
    fDiam = 5;
    fHeight = 8;
    p_oTree7 = p_oPop->CreateTree(7, 7, 3, clTreePopulation::sapling, fDiam);
    p_oTree7->SetValue(p_oPop->GetHeightCode(p_oTree7->GetSpecies(), p_oTree7->GetType()), fHeight, false, false);

    //Tree 8: Sapling, Species 4
    fDiam = 7;
    fHeight = 6;
    p_oTree8 = p_oPop->CreateTree(8, 8, 3, clTreePopulation::sapling, fDiam);
    p_oTree8->SetValue(p_oPop->GetHeightCode(p_oTree8->GetSpecies(), p_oTree8->GetType()), fHeight, false, false);

    //Tree 9: Adult, Species 4
    fDiam = 20;
    fHeight = 15;
    p_oTree9 = p_oPop->CreateTree(9, 9, 3, clTreePopulation::adult, fDiam);
    p_oTree9->SetValue(p_oPop->GetHeightCode(p_oTree9->GetSpecies(), p_oTree9->GetType()), fHeight, false, false);

    //Tree 10: Adult, Species 4
    fDiam = 20;
    fHeight = 16;
    p_oTree10 = p_oPop->CreateTree(10, 10, 3, clTreePopulation::adult, fDiam);
    p_oTree10->SetValue(p_oPop->GetHeightCode(p_oTree10->GetSpecies(), p_oTree10->GetType()), fHeight, false, false);

    p_oSimManager->RunSim(1);

    //Confirm all trees
    //Tree 1: Sapling, Species 1
    fExpectedDiam = 5.157526139;
    fExpectedHeight = 7.151225094;
    fExpectedGrowth = 0.262543566;
    p_oTree1->GetValue(p_oPop->GetDiam10Code(p_oTree1->GetSpecies(), p_oTree1->GetType()), &fDiam);
    p_oTree1->GetValue(p_oPop->GetHeightCode(p_oTree1->GetSpecies(), p_oTree1->GetType()), &fHeight);
    p_oTree1->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree1->GetSpecies(), p_oTree1->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Tree 2: Sapling, Species 2
    fExpectedDiam = 5.965447786;
    fExpectedHeight = 8.859248529;
    fExpectedGrowth = 1.609079643;
    p_oTree2->GetValue(p_oPop->GetDiam10Code(p_oTree2->GetSpecies(), p_oTree2->GetType()), &fDiam);
    p_oTree2->GetValue(p_oPop->GetHeightCode(p_oTree2->GetSpecies(), p_oTree2->GetType()), &fHeight);
    p_oTree2->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree2->GetSpecies(), p_oTree2->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Tree 3: Seedling, Species 2
    fExpectedDiam = 1.636435841;
    fExpectedHeight = 1.316427898;
    fExpectedGrowth = 1.060726401;
    p_oTree3->GetValue(p_oPop->GetDiam10Code(p_oTree3->GetSpecies(), p_oTree3->GetType()), &fDiam);
    p_oTree3->GetValue(p_oPop->GetHeightCode(p_oTree3->GetSpecies(), p_oTree3->GetType()), &fHeight);
    p_oTree3->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree3->GetSpecies(), p_oTree3->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Tree 4: Adult, Species 1
    fExpectedDiam = 20.19335874;
    fExpectedHeight = 15.18562439;
    fExpectedGrowth = 0.32226457;
    p_oTree4->GetValue(p_oPop->GetDbhCode(p_oTree4->GetSpecies(), p_oTree4->GetType()), &fDiam);
    p_oTree4->GetValue(p_oPop->GetHeightCode(p_oTree4->GetSpecies(), p_oTree4->GetType()), &fHeight);
    p_oTree4->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree4->GetSpecies(), p_oTree4->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Tree 5: Seedling, Species 1
    fExpectedDiam = 1.293704374;
    fExpectedHeight = 1.089956199;
    fExpectedGrowth = 0.156173956;
    p_oTree5->GetValue(p_oPop->GetDiam10Code(p_oTree5->GetSpecies(), p_oTree5->GetType()), &fDiam);
    p_oTree5->GetValue(p_oPop->GetHeightCode(p_oTree5->GetSpecies(), p_oTree5->GetType()), &fHeight);
    p_oTree5->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree5->GetSpecies(), p_oTree5->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Tree 6: Sapling, Species 4
    fExpectedDiam = 5.080194534;
    fExpectedHeight = 7.083723094;
    fExpectedGrowth = 0.133657557;
    p_oTree6->GetValue(p_oPop->GetDiam10Code(p_oTree6->GetSpecies(), p_oTree6->GetType()), &fDiam);
    p_oTree6->GetValue(p_oPop->GetHeightCode(p_oTree6->GetSpecies(), p_oTree6->GetType()), &fHeight);
    p_oTree6->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree6->GetSpecies(), p_oTree6->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Tree 7: Sapling, Species 4
    fExpectedDiam = 5.081811784;
    fExpectedHeight = 8.085411503;
    fExpectedGrowth = 0.136352973;
    p_oTree7->GetValue(p_oPop->GetDiam10Code(p_oTree7->GetSpecies(), p_oTree7->GetType()), &fDiam);
    p_oTree7->GetValue(p_oPop->GetHeightCode(p_oTree7->GetSpecies(), p_oTree7->GetType()), &fHeight);
    p_oTree7->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree7->GetSpecies(), p_oTree7->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Tree 8: Sapling, Species 4
    fExpectedDiam = 7.078368018;
    fExpectedHeight = 6.081816211;
    fExpectedGrowth = 0.130613363;
    p_oTree8->GetValue(p_oPop->GetDiam10Code(p_oTree8->GetSpecies(), p_oTree8->GetType()), &fDiam);
    p_oTree8->GetValue(p_oPop->GetHeightCode(p_oTree8->GetSpecies(), p_oTree8->GetType()), &fHeight);
    p_oTree8->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree8->GetSpecies(), p_oTree8->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Tree 9: Adult, Species 4
    fExpectedDiam = 20.08988155;
    fExpectedHeight = 15.09383633;
    fExpectedGrowth = 0.149802577;
    p_oTree9->GetValue(p_oPop->GetDbhCode(p_oTree9->GetSpecies(), p_oTree9->GetType()), &fDiam);
    p_oTree9->GetValue(p_oPop->GetHeightCode(p_oTree9->GetSpecies(), p_oTree9->GetType()), &fHeight);
    p_oTree9->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree9->GetSpecies(), p_oTree9->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Tree 10: Adult, Species 4
    fExpectedDiam = 20.09075438;
    fExpectedHeight = 16.09474758;
    fExpectedGrowth = 0.151257308;
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
// WritePowerHeightGrowthXMLFile1()
////////////////////////////////////////////////////////////////////////////
const char* WritePowerHeightGrowthXMLFile1() {
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

  WritePowerHeightGrowthCommonStuff(oOut);

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WritePowerHeightGrowthXMLFile2()
////////////////////////////////////////////////////////////////////////////
const char* WritePowerHeightGrowthXMLFile2() {
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

  WritePowerHeightGrowthCommonStuff(oOut);

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WritePowerHeightGrowthCommonStuff()
/////////////////////////////////////////////////////////////////////////////
void WritePowerHeightGrowthCommonStuff(std::fstream &oOut) {
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
       << "<behaviorName>PowerGrowth height only</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
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
       << "</behaviorList>"
       << "<PowerGrowth1>"
       << "<gr_powerHeightN>"
       << "<gr_phnVal species=\"Species_1\">0.858</gr_phnVal>"
       << "<gr_phnVal species=\"Species_2\">7.99</gr_phnVal>"
       << "<gr_phnVal species=\"Species_4\">1.044</gr_phnVal>"
       << "</gr_powerHeightN>"
       << "<gr_powerHeightExp>"
       << "<gr_pheVal species=\"Species_1\">0.27</gr_pheVal>"
       << "<gr_pheVal species=\"Species_2\">0.19</gr_pheVal>"
       << "<gr_pheVal species=\"Species_4\">0.15</gr_pheVal>"
       << "</gr_powerHeightExp>"
       << "</PowerGrowth1>"
       << "</paramFile>";
}
