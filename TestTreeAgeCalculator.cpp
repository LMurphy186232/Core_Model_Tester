//---------------------------------------------------------------------------
// TestTreeAgeCalculator.cpp
//---------------------------------------------------------------------------
#include "TestTreeAgeCalculator.h"
#include <gtest/gtest.h>
#include <fstream>
#include <math.h>
#include "TreePopulation.h"
#include "SimManager.h"
#include "BehaviorBase.h"

////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun1()
////////////////////////////////////////////////////////////////////////////
TEST(TreeAgeCalculator, TestNormalProcessingRun1) {

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTreeSearch *p_oAllTrees;
    clTree *p_oTargetTree1, *p_oTargetTree2, *p_oTargetTree3,
    *p_oTargetTree4, *p_oTargetTree5, *p_oTargetTree6,
    *p_oTargetTree7, *p_oTargetTree8, *p_oTargetTree9,
    *p_oTargetTree10, *p_oTargetTree11, *p_oTargetTree12,
    *p_oTargetTree13, *p_oTargetTree14, *p_oTargetTree15,
    *p_oTree;
    float fX;
    int iSpecies, iAge, iExpectedAge;

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteTreeAgeCalculatorXMLFile1() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Check the initial conditions trees
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      iSpecies = p_oTree->GetSpecies();
      if (0 == iSpecies) {
        //Species 1 - age behavior not applied
        EXPECT_EQ(-1, p_oPop->GetIntDataCode("Tree Age",  iSpecies,  p_oTree->GetType()));
      }
      else if (1 == iSpecies) {
        //Species 2 - age not specified
        iExpectedAge = 10000;
        p_oTree->GetValue(p_oPop->GetIntDataCode("Tree Age",  iSpecies, p_oTree->GetType()), &iAge);
        EXPECT_EQ(iAge, iExpectedAge);
      }
      else {
        //Species 3 - age specified as 10
        iExpectedAge = 10;
        p_oTree->GetValue(p_oPop->GetIntDataCode("Tree Age",  iSpecies, p_oTree->GetType()), &iAge);
        EXPECT_EQ(iAge, iExpectedAge);
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    //Create our trees
    iSpecies = 0;
    p_oTargetTree1 = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::seedling, 0.3);
    p_oTargetTree2 = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::sapling, 5);
    p_oTargetTree3 = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, 12);

    iSpecies = 1;
    iAge = 0;
    p_oTargetTree4 = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::seedling, 0.3);
    p_oTargetTree4->SetValue(p_oPop->GetIntDataCode("Tree Age",
        p_oTargetTree4->GetSpecies(), p_oTargetTree4->GetType()), iAge);
    p_oTargetTree5 = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::sapling, 5);
    p_oTargetTree5->SetValue(p_oPop->GetIntDataCode("Tree Age",
        p_oTargetTree5->GetSpecies(), p_oTargetTree5->GetType()), iAge);
    p_oTargetTree6 = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, 12);
    p_oTargetTree6->SetValue(p_oPop->GetIntDataCode("Tree Age",
        p_oTargetTree6->GetSpecies(), p_oTargetTree6->GetType()), iAge);

    iAge = 1;
    p_oTargetTree7 = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::seedling, 0.3);
    p_oTargetTree7->SetValue(p_oPop->GetIntDataCode("Tree Age",
        p_oTargetTree7->GetSpecies(), p_oTargetTree7->GetType()), iAge);
    iAge = 2;
    p_oTargetTree8 = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::sapling, 5);
    p_oTargetTree8->SetValue(p_oPop->GetIntDataCode("Tree Age",
        p_oTargetTree8->GetSpecies(), p_oTargetTree8->GetType()), iAge);
    iAge = 4;
    p_oTargetTree9 = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, 12);
    p_oTargetTree9->SetValue(p_oPop->GetIntDataCode("Tree Age",
        p_oTargetTree9->GetSpecies(), p_oTargetTree9->GetType()), iAge);

    iSpecies = 2;
    iAge = 0;
    p_oTargetTree10 = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::seedling, 0.3);
    p_oTargetTree10->SetValue(p_oPop->GetIntDataCode("Tree Age",
        p_oTargetTree10->GetSpecies(), p_oTargetTree10->GetType()), iAge);
    p_oTargetTree11 = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::sapling, 5);
    p_oTargetTree11->SetValue(p_oPop->GetIntDataCode("Tree Age",
        p_oTargetTree11->GetSpecies(), p_oTargetTree11->GetType()), iAge);
    p_oTargetTree12 = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, 12);
    p_oTargetTree12->SetValue(p_oPop->GetIntDataCode("Tree Age",
        p_oTargetTree12->GetSpecies(), p_oTargetTree12->GetType()), iAge);

    iAge = 5;
    p_oTargetTree13 = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::seedling, 0.3);
    p_oTargetTree13->SetValue(p_oPop->GetIntDataCode("Tree Age",
        p_oTargetTree13->GetSpecies(), p_oTargetTree13->GetType()), iAge);
    iAge = 7;
    p_oTargetTree14 = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::sapling, 5);
    p_oTargetTree14->SetValue(p_oPop->GetIntDataCode("Tree Age",
        p_oTargetTree14->GetSpecies(), p_oTargetTree14->GetType()), iAge);
    iAge = 2;
    p_oTargetTree15 = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, 12);
    p_oTargetTree15->SetValue(p_oPop->GetIntDataCode("Tree Age",
        p_oTargetTree15->GetSpecies(), p_oTargetTree15->GetType()), iAge);

    //Run one timestep
    p_oSimManager->RunSim(1);

    //Check the age for each tree
    EXPECT_EQ(-1, p_oPop->GetIntDataCode("Tree Age",  p_oTargetTree1->GetSpecies(),  p_oTargetTree1->GetType()));
    EXPECT_EQ(-1, p_oPop->GetIntDataCode("Tree Age",  p_oTargetTree2->GetSpecies(),  p_oTargetTree2->GetType()));
    EXPECT_EQ(-1, p_oPop->GetIntDataCode("Tree Age",  p_oTargetTree3->GetSpecies(),  p_oTargetTree3->GetType()));

    iExpectedAge = 1;
    p_oTargetTree4->GetValue(p_oPop->GetIntDataCode("Tree Age",  p_oTargetTree4->GetSpecies(), p_oTargetTree4->GetType()), &iAge);
    EXPECT_EQ(iAge, iExpectedAge);
    p_oTargetTree5->GetValue(p_oPop->GetIntDataCode("Tree Age",  p_oTargetTree5->GetSpecies(), p_oTargetTree5->GetType()), &iAge);
    EXPECT_EQ(iAge, iExpectedAge);
    p_oTargetTree6->GetValue(p_oPop->GetIntDataCode("Tree Age",  p_oTargetTree6->GetSpecies(), p_oTargetTree6->GetType()), &iAge);
    EXPECT_EQ(iAge, iExpectedAge);

    iExpectedAge = 2;
    p_oTargetTree7->GetValue(p_oPop->GetIntDataCode("Tree Age",  p_oTargetTree7->GetSpecies(), p_oTargetTree7->GetType()), &iAge);
    EXPECT_EQ(iAge, iExpectedAge);
    iExpectedAge = 3;
    p_oTargetTree8->GetValue(p_oPop->GetIntDataCode("Tree Age",  p_oTargetTree8->GetSpecies(), p_oTargetTree8->GetType()), &iAge);
    EXPECT_EQ(iAge, iExpectedAge);
    iExpectedAge = 5;
    p_oTargetTree9->GetValue(p_oPop->GetIntDataCode("Tree Age",  p_oTargetTree9->GetSpecies(), p_oTargetTree9->GetType()), &iAge);
    EXPECT_EQ(iAge, iExpectedAge);

    iExpectedAge = 1;
    p_oTargetTree10->GetValue(p_oPop->GetIntDataCode("Tree Age",  p_oTargetTree10->GetSpecies(), p_oTargetTree10->GetType()), &iAge);
    EXPECT_EQ(iAge, iExpectedAge);
    p_oTargetTree11->GetValue(p_oPop->GetIntDataCode("Tree Age",  p_oTargetTree11->GetSpecies(), p_oTargetTree11->GetType()), &iAge);
    EXPECT_EQ(iAge, iExpectedAge);
    p_oTargetTree12->GetValue(p_oPop->GetIntDataCode("Tree Age",  p_oTargetTree12->GetSpecies(), p_oTargetTree12->GetType()), &iAge);
    EXPECT_EQ(iAge, iExpectedAge);

    iExpectedAge = 6;
    p_oTargetTree13->GetValue(p_oPop->GetIntDataCode("Tree Age",  p_oTargetTree13->GetSpecies(), p_oTargetTree13->GetType()), &iAge);
    EXPECT_EQ(iAge, iExpectedAge);
    iExpectedAge = 8;
    p_oTargetTree14->GetValue(p_oPop->GetIntDataCode("Tree Age",  p_oTargetTree14->GetSpecies(), p_oTargetTree14->GetType()), &iAge);
    EXPECT_EQ(iAge, iExpectedAge);
    iExpectedAge = 3;
    p_oTargetTree15->GetValue(p_oPop->GetIntDataCode("Tree Age",  p_oTargetTree15->GetSpecies(), p_oTargetTree15->GetType()), &iAge);
    EXPECT_EQ(iAge, iExpectedAge);

    //Check the initial conditions trees
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
      if (fX > 20) {

        iSpecies = p_oTree->GetSpecies();
        if (0 == iSpecies) {
          //Species 1 - age behavior not applied
          EXPECT_EQ(-1, p_oPop->GetIntDataCode("Tree Age",  iSpecies,  p_oTree->GetType()));
        }
        else if (1 == iSpecies) {
          //Species 2 - age not specified
          iExpectedAge = 10001;
          p_oTree->GetValue(p_oPop->GetIntDataCode("Tree Age",  iSpecies, p_oTree->GetType()), &iAge);
          EXPECT_EQ(iAge, iExpectedAge);
        }
        else {
          //Species 3 - age specified as 10
          iExpectedAge = 11;
          p_oTree->GetValue(p_oPop->GetIntDataCode("Tree Age",  iSpecies, p_oTree->GetType()), &iAge);
          EXPECT_EQ(iAge, iExpectedAge);
        }
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    //Run another timestep
    p_oSimManager->RunSim(1);

    //Check the age for each tree
    EXPECT_EQ(-1, p_oPop->GetIntDataCode("Tree Age",  p_oTargetTree1->GetSpecies(),  p_oTargetTree1->GetType()));
    EXPECT_EQ(-1, p_oPop->GetIntDataCode("Tree Age",  p_oTargetTree2->GetSpecies(),  p_oTargetTree2->GetType()));
    EXPECT_EQ(-1, p_oPop->GetIntDataCode("Tree Age",  p_oTargetTree3->GetSpecies(),  p_oTargetTree3->GetType()));

    iExpectedAge = 2;
    p_oTargetTree4->GetValue(p_oPop->GetIntDataCode("Tree Age",  p_oTargetTree4->GetSpecies(), p_oTargetTree4->GetType()), &iAge);
    EXPECT_EQ(iAge, iExpectedAge);
    p_oTargetTree5->GetValue(p_oPop->GetIntDataCode("Tree Age",  p_oTargetTree5->GetSpecies(), p_oTargetTree5->GetType()), &iAge);
    EXPECT_EQ(iAge, iExpectedAge);
    p_oTargetTree6->GetValue(p_oPop->GetIntDataCode("Tree Age",  p_oTargetTree6->GetSpecies(), p_oTargetTree6->GetType()), &iAge);
    EXPECT_EQ(iAge, iExpectedAge);

    iExpectedAge = 3;
    p_oTargetTree7->GetValue(p_oPop->GetIntDataCode("Tree Age",  p_oTargetTree7->GetSpecies(), p_oTargetTree7->GetType()), &iAge);
    EXPECT_EQ(iAge, iExpectedAge);
    iExpectedAge = 4;
    p_oTargetTree8->GetValue(p_oPop->GetIntDataCode("Tree Age",  p_oTargetTree8->GetSpecies(), p_oTargetTree8->GetType()), &iAge);
    EXPECT_EQ(iAge, iExpectedAge);
    iExpectedAge = 6;
    p_oTargetTree9->GetValue(p_oPop->GetIntDataCode("Tree Age",  p_oTargetTree9->GetSpecies(), p_oTargetTree9->GetType()), &iAge);
    EXPECT_EQ(iAge, iExpectedAge);

    iExpectedAge = 2;
    p_oTargetTree10->GetValue(p_oPop->GetIntDataCode("Tree Age",  p_oTargetTree10->GetSpecies(), p_oTargetTree10->GetType()), &iAge);
    EXPECT_EQ(iAge, iExpectedAge);
    p_oTargetTree11->GetValue(p_oPop->GetIntDataCode("Tree Age",  p_oTargetTree11->GetSpecies(), p_oTargetTree11->GetType()), &iAge);
    EXPECT_EQ(iAge, iExpectedAge);
    p_oTargetTree12->GetValue(p_oPop->GetIntDataCode("Tree Age",  p_oTargetTree12->GetSpecies(), p_oTargetTree12->GetType()), &iAge);
    EXPECT_EQ(iAge, iExpectedAge);

    iExpectedAge = 7;
    p_oTargetTree13->GetValue(p_oPop->GetIntDataCode("Tree Age",  p_oTargetTree13->GetSpecies(), p_oTargetTree13->GetType()), &iAge);
    EXPECT_EQ(iAge, iExpectedAge);
    iExpectedAge = 9;
    p_oTargetTree14->GetValue(p_oPop->GetIntDataCode("Tree Age",  p_oTargetTree14->GetSpecies(), p_oTargetTree14->GetType()), &iAge);
    EXPECT_EQ(iAge, iExpectedAge);
    iExpectedAge = 4;
    p_oTargetTree15->GetValue(p_oPop->GetIntDataCode("Tree Age",  p_oTargetTree15->GetSpecies(), p_oTargetTree15->GetType()), &iAge);
    EXPECT_EQ(iAge, iExpectedAge);

    //Check the initial conditions trees
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
      if (fX > 20) {

        iSpecies = p_oTree->GetSpecies();
        if (0 == iSpecies) {
          //Species 1 - age behavior not applied
          EXPECT_EQ(-1, p_oPop->GetIntDataCode("Tree Age",  iSpecies,  p_oTree->GetType()));
        }
        else if (1 == iSpecies) {
          //Species 2 - age not specified
          iExpectedAge = 10002;
          p_oTree->GetValue(p_oPop->GetIntDataCode("Tree Age",  iSpecies, p_oTree->GetType()), &iAge);
          EXPECT_EQ(iAge, iExpectedAge);
        }
        else {
          //Species 3 - age specified as 10
          iExpectedAge = 12;
          p_oTree->GetValue(p_oPop->GetIntDataCode("Tree Age",  iSpecies, p_oTree->GetType()), &iAge);
          EXPECT_EQ(iAge, iExpectedAge);
        }
      }
      p_oTree = p_oAllTrees->NextTree();
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
TEST(TreeAgeCalculator, TestNormalProcessingRun2) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTreeSearch *p_oAllTrees;
    clTree *p_oTargetTree1, *p_oTargetTree2, *p_oTargetTree3,
    *p_oTargetTree4, *p_oTargetTree5, *p_oTargetTree6,
    *p_oTargetTree7, *p_oTargetTree8, *p_oTargetTree9,
    *p_oTargetTree10, *p_oTargetTree11, *p_oTargetTree12,
    *p_oTargetTree13, *p_oTargetTree14, *p_oTargetTree15,
    *p_oTree;
    float fDiam;
    int iSpecies, iAge, iExpectedAge;

    //Run 1 of 2
    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteTreeAgeCalculatorXMLFile2() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Check the initial conditions trees
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    iExpectedAge = 10000;
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetIntDataCode("Tree Age",  p_oTree->GetSpecies(), p_oTree->GetType()), &iAge);
      EXPECT_EQ(iAge, iExpectedAge);
      p_oTree = p_oAllTrees->NextTree();
    }

    //Create our trees
    iSpecies = 0;
    p_oTargetTree1 = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::seedling, 0.3);
    p_oTargetTree2 = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::sapling, 5);
    p_oTargetTree3 = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, 12);

    iSpecies = 1;
    iAge = 0;
    p_oTargetTree4 = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::seedling, 0.3);
    p_oTargetTree4->SetValue(p_oPop->GetIntDataCode("Tree Age",
        p_oTargetTree4->GetSpecies(), p_oTargetTree4->GetType()), iAge);
    p_oTargetTree5 = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::sapling, 5);
    p_oTargetTree5->SetValue(p_oPop->GetIntDataCode("Tree Age",
        p_oTargetTree5->GetSpecies(), p_oTargetTree5->GetType()), iAge);
    p_oTargetTree6 = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, 12);
    p_oTargetTree6->SetValue(p_oPop->GetIntDataCode("Tree Age",
        p_oTargetTree6->GetSpecies(), p_oTargetTree6->GetType()), iAge);

    iAge = 1;
    p_oTargetTree7 = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::seedling, 0.3);
    p_oTargetTree7->SetValue(p_oPop->GetIntDataCode("Tree Age",
        p_oTargetTree7->GetSpecies(), p_oTargetTree7->GetType()), iAge);
    iAge = 2;
    p_oTargetTree8 = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::sapling, 5);
    p_oTargetTree8->SetValue(p_oPop->GetIntDataCode("Tree Age",
        p_oTargetTree8->GetSpecies(), p_oTargetTree8->GetType()), iAge);
    iAge = 4;
    p_oTargetTree9 = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, 12);
    p_oTargetTree9->SetValue(p_oPop->GetIntDataCode("Tree Age",
        p_oTargetTree9->GetSpecies(), p_oTargetTree9->GetType()), iAge);

    iSpecies = 2;
    iAge = 0;
    p_oTargetTree10 = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::seedling, 0.3);
    p_oTargetTree10->SetValue(p_oPop->GetIntDataCode("Tree Age",
        p_oTargetTree10->GetSpecies(), p_oTargetTree10->GetType()), iAge);
    p_oTargetTree11 = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::sapling, 5);
    p_oTargetTree11->SetValue(p_oPop->GetIntDataCode("Tree Age",
        p_oTargetTree11->GetSpecies(), p_oTargetTree11->GetType()), iAge);
    p_oTargetTree12 = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, 12);
    p_oTargetTree12->SetValue(p_oPop->GetIntDataCode("Tree Age",
        p_oTargetTree12->GetSpecies(), p_oTargetTree12->GetType()), iAge);

    iAge = 5;
    p_oTargetTree13 = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::seedling, 0.3);
    p_oTargetTree13->SetValue(p_oPop->GetIntDataCode("Tree Age",
        p_oTargetTree13->GetSpecies(), p_oTargetTree13->GetType()), iAge);
    iAge = 7;
    p_oTargetTree14 = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::sapling, 5);
    p_oTargetTree14->SetValue(p_oPop->GetIntDataCode("Tree Age",
        p_oTargetTree14->GetSpecies(), p_oTargetTree14->GetType()), iAge);
    iAge = 2;
    p_oTargetTree15 = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, 12);
    p_oTargetTree15->SetValue(p_oPop->GetIntDataCode("Tree Age",
        p_oTargetTree15->GetSpecies(), p_oTargetTree15->GetType()), iAge);

    //Run one timestep
    p_oSimManager->RunSim(1);

    //Check the initial conditions trees
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    iExpectedAge = 10003;
    while (p_oTree) {
      if (p_oTree->GetSpecies() == 1 && p_oTree->GetType() == clTreePopulation::adult) {
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
        if (fDiam > 49) {
          p_oTree->GetValue(p_oPop->GetIntDataCode("Tree Age",  p_oTree->GetSpecies(), p_oTree->GetType()), &iAge);
          EXPECT_EQ(iAge, iExpectedAge);
        }
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    //Check the age for each tree
    EXPECT_EQ(-1, p_oPop->GetIntDataCode("Tree Age",  p_oTargetTree1->GetSpecies(),  p_oTargetTree1->GetType()));
    EXPECT_EQ(-1, p_oPop->GetIntDataCode("Tree Age",  p_oTargetTree2->GetSpecies(),  p_oTargetTree2->GetType()));
    EXPECT_EQ(-1, p_oPop->GetIntDataCode("Tree Age",  p_oTargetTree3->GetSpecies(),  p_oTargetTree3->GetType()));

    iExpectedAge = 3;
    p_oTargetTree4->GetValue(p_oPop->GetIntDataCode("Tree Age",  p_oTargetTree4->GetSpecies(), p_oTargetTree4->GetType()), &iAge);
    EXPECT_EQ(iAge, iExpectedAge);
    p_oTargetTree5->GetValue(p_oPop->GetIntDataCode("Tree Age",  p_oTargetTree5->GetSpecies(), p_oTargetTree5->GetType()), &iAge);
    EXPECT_EQ(iAge, iExpectedAge);
    p_oTargetTree6->GetValue(p_oPop->GetIntDataCode("Tree Age",  p_oTargetTree6->GetSpecies(), p_oTargetTree6->GetType()), &iAge);
    EXPECT_EQ(iAge, iExpectedAge);

    iExpectedAge = 4;
    p_oTargetTree7->GetValue(p_oPop->GetIntDataCode("Tree Age",  p_oTargetTree7->GetSpecies(), p_oTargetTree7->GetType()), &iAge);
    EXPECT_EQ(iAge, iExpectedAge);
    iExpectedAge = 5;
    p_oTargetTree8->GetValue(p_oPop->GetIntDataCode("Tree Age",  p_oTargetTree8->GetSpecies(), p_oTargetTree8->GetType()), &iAge);
    EXPECT_EQ(iAge, iExpectedAge);
    iExpectedAge = 7;
    p_oTargetTree9->GetValue(p_oPop->GetIntDataCode("Tree Age",  p_oTargetTree9->GetSpecies(), p_oTargetTree9->GetType()), &iAge);
    EXPECT_EQ(iAge, iExpectedAge);

    iExpectedAge = 3;
    p_oTargetTree10->GetValue(p_oPop->GetIntDataCode("Tree Age",  p_oTargetTree10->GetSpecies(), p_oTargetTree10->GetType()), &iAge);
    EXPECT_EQ(iAge, iExpectedAge);
    p_oTargetTree11->GetValue(p_oPop->GetIntDataCode("Tree Age",  p_oTargetTree11->GetSpecies(), p_oTargetTree11->GetType()), &iAge);
    EXPECT_EQ(iAge, iExpectedAge);
    p_oTargetTree12->GetValue(p_oPop->GetIntDataCode("Tree Age",  p_oTargetTree12->GetSpecies(), p_oTargetTree12->GetType()), &iAge);
    EXPECT_EQ(iAge, iExpectedAge);

    iExpectedAge = 8;
    p_oTargetTree13->GetValue(p_oPop->GetIntDataCode("Tree Age",  p_oTargetTree13->GetSpecies(), p_oTargetTree13->GetType()), &iAge);
    EXPECT_EQ(iAge, iExpectedAge);
    iExpectedAge = 10;
    p_oTargetTree14->GetValue(p_oPop->GetIntDataCode("Tree Age",  p_oTargetTree14->GetSpecies(), p_oTargetTree14->GetType()), &iAge);
    EXPECT_EQ(iAge, iExpectedAge);
    iExpectedAge = 5;
    p_oTargetTree15->GetValue(p_oPop->GetIntDataCode("Tree Age",  p_oTargetTree15->GetSpecies(), p_oTargetTree15->GetType()), &iAge);
    EXPECT_EQ(iAge, iExpectedAge);

    //Run another timestep
    p_oSimManager->RunSim(1);

    //Check the age for each tree
    EXPECT_EQ(-1, p_oPop->GetIntDataCode("Tree Age",  p_oTargetTree1->GetSpecies(),  p_oTargetTree1->GetType()));
    EXPECT_EQ(-1, p_oPop->GetIntDataCode("Tree Age",  p_oTargetTree2->GetSpecies(),  p_oTargetTree2->GetType()));
    EXPECT_EQ(-1, p_oPop->GetIntDataCode("Tree Age",  p_oTargetTree3->GetSpecies(),  p_oTargetTree3->GetType()));

    iExpectedAge = 6;
    p_oTargetTree4->GetValue(p_oPop->GetIntDataCode("Tree Age",  p_oTargetTree4->GetSpecies(), p_oTargetTree4->GetType()), &iAge);
    EXPECT_EQ(iAge, iExpectedAge);
    p_oTargetTree5->GetValue(p_oPop->GetIntDataCode("Tree Age",  p_oTargetTree5->GetSpecies(), p_oTargetTree5->GetType()), &iAge);
    EXPECT_EQ(iAge, iExpectedAge);
    p_oTargetTree6->GetValue(p_oPop->GetIntDataCode("Tree Age",  p_oTargetTree6->GetSpecies(), p_oTargetTree6->GetType()), &iAge);
    EXPECT_EQ(iAge, iExpectedAge);

    iExpectedAge = 7;
    p_oTargetTree7->GetValue(p_oPop->GetIntDataCode("Tree Age",  p_oTargetTree7->GetSpecies(), p_oTargetTree7->GetType()), &iAge);
    EXPECT_EQ(iAge, iExpectedAge);
    iExpectedAge = 8;
    p_oTargetTree8->GetValue(p_oPop->GetIntDataCode("Tree Age",  p_oTargetTree8->GetSpecies(), p_oTargetTree8->GetType()), &iAge);
    EXPECT_EQ(iAge, iExpectedAge);
    iExpectedAge = 10;
    p_oTargetTree9->GetValue(p_oPop->GetIntDataCode("Tree Age",  p_oTargetTree9->GetSpecies(), p_oTargetTree9->GetType()), &iAge);
    EXPECT_EQ(iAge, iExpectedAge);

    iExpectedAge = 6;
    p_oTargetTree10->GetValue(p_oPop->GetIntDataCode("Tree Age",  p_oTargetTree10->GetSpecies(), p_oTargetTree10->GetType()), &iAge);
    EXPECT_EQ(iAge, iExpectedAge);
    p_oTargetTree11->GetValue(p_oPop->GetIntDataCode("Tree Age",  p_oTargetTree11->GetSpecies(), p_oTargetTree11->GetType()), &iAge);
    EXPECT_EQ(iAge, iExpectedAge);
    p_oTargetTree12->GetValue(p_oPop->GetIntDataCode("Tree Age",  p_oTargetTree12->GetSpecies(), p_oTargetTree12->GetType()), &iAge);
    EXPECT_EQ(iAge, iExpectedAge);

    iExpectedAge = 11;
    p_oTargetTree13->GetValue(p_oPop->GetIntDataCode("Tree Age",  p_oTargetTree13->GetSpecies(), p_oTargetTree13->GetType()), &iAge);
    EXPECT_EQ(iAge, iExpectedAge);
    iExpectedAge = 13;
    p_oTargetTree14->GetValue(p_oPop->GetIntDataCode("Tree Age",  p_oTargetTree14->GetSpecies(), p_oTargetTree14->GetType()), &iAge);
    EXPECT_EQ(iAge, iExpectedAge);
    iExpectedAge = 8;
    p_oTargetTree15->GetValue(p_oPop->GetIntDataCode("Tree Age",  p_oTargetTree15->GetSpecies(), p_oTargetTree15->GetType()), &iAge);
    EXPECT_EQ(iAge, iExpectedAge);

    //Check the initial conditions trees
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    iExpectedAge = 10006;
    while (p_oTree) {
      if (p_oTree->GetSpecies() == 1 && p_oTree->GetType() == clTreePopulation::adult) {
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
        if (fDiam > 49) {
          p_oTree->GetValue(p_oPop->GetIntDataCode("Tree Age",  p_oTree->GetSpecies(), p_oTree->GetType()), &iAge);
          EXPECT_EQ(iAge, iExpectedAge);
        }
      }
      p_oTree = p_oAllTrees->NextTree();
    }
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestErrorProcessing()
////////////////////////////////////////////////////////////////////////////
TEST(TreeAgeCalculator, TestErrorProcessing) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try
  {
    p_oSimManager->ReadFile(WriteTreeAgeCalculatorXMLErrorFile1());
    FAIL() << "TestTreeAgeCalculator error processing didn't catch error for WriteTreeAgeCalculatorXMLErrorFile1.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.find("RegisterTreeDataMembers") == std::string::npos)
    {
      FAIL() << "TestTreeAgeCalculator error processing caught wrong error for WriteTreeAgeCalculatorXMLErrorFile1.";
    }
    ;
  }
  delete p_oSimManager;
}

////////////////////////////////////////////////////////////////////////////
// WriteTreeAgeCalculatorXMLFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteTreeAgeCalculatorXMLFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>3</timesteps>"
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
       << "</tr_speciesList>"
       << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
       << "<tr_minAdultDBH>"
       << "<tr_madVal species=\"Species_1\">0.0</tr_madVal>"
       << "<tr_madVal species=\"Species_2\">0.0</tr_madVal>"
       << "<tr_madVal species=\"Species_3\">0.0</tr_madVal>"
       << "</tr_minAdultDBH>"
       << "<tr_maxSeedlingHeight>"
       << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_2\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_3\">1.35</tr_mshVal>"
       << "</tr_maxSeedlingHeight>";

  oOut << "<tr_treemap>"
       << "<tm_treeSettings sp=\"Species_1\" tp=\"3\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">3</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_2\" tp=\"3\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">3</tm_floatCode>"
       << "</tm_floatCodes>"
       << "<tm_intCodes>"
       << "<tm_intCode label=\"Tree Age\">0</tm_intCode>"
       << "</tm_intCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_3\" tp=\"3\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">3</tm_floatCode>"
       << "</tm_floatCodes>"
       << "<tm_intCodes>"
       << "<tm_intCode label=\"Tree Age\">0</tm_intCode>"
       << "</tm_intCodes>"
       << "</tm_treeSettings>"
       //10 trees - species 1, age behavior not applied
       << "<tree sp=\"0\" tp=\"3\">"
       << "<fl c=\"0\">30</fl>"
       << "<fl c=\"1\">30</fl>"
       << "<fl c=\"3\">30</fl>"
       << "</tree>"
       << "<tree sp=\"0\" tp=\"3\">"
       << "<fl c=\"0\">30</fl>"
       << "<fl c=\"1\">30</fl>"
       << "<fl c=\"3\">30</fl>"
       << "</tree>"
       << "<tree sp=\"0\" tp=\"3\">"
       << "<fl c=\"0\">30</fl>"
       << "<fl c=\"1\">30</fl>"
       << "<fl c=\"3\">30</fl>"
       << "</tree>"
       << "<tree sp=\"0\" tp=\"3\">"
       << "<fl c=\"0\">30</fl>"
       << "<fl c=\"1\">30</fl>"
       << "<fl c=\"3\">30</fl>"
       << "</tree>"
       << "<tree sp=\"0\" tp=\"3\">"
       << "<fl c=\"0\">30</fl>"
       << "<fl c=\"1\">30</fl>"
       << "<fl c=\"3\">30</fl>"
       << "</tree>"
       << "<tree sp=\"0\" tp=\"3\">"
       << "<fl c=\"0\">30</fl>"
       << "<fl c=\"1\">30</fl>"
       << "<fl c=\"3\">30</fl>"
       << "</tree>"
       << "<tree sp=\"0\" tp=\"3\">"
       << "<fl c=\"0\">30</fl>"
       << "<fl c=\"1\">30</fl>"
       << "<fl c=\"3\">30</fl>"
       << "</tree>"
       << "<tree sp=\"0\" tp=\"3\">"
       << "<fl c=\"0\">30</fl>"
       << "<fl c=\"1\">30</fl>"
       << "<fl c=\"3\">30</fl>"
       << "</tree>"
       << "<tree sp=\"0\" tp=\"3\">"
       << "<fl c=\"0\">30</fl>"
       << "<fl c=\"1\">30</fl>"
       << "<fl c=\"3\">30</fl>"
       << "</tree>"
       << "<tree sp=\"0\" tp=\"3\">"
       << "<fl c=\"0\">30</fl>"
       << "<fl c=\"1\">30</fl>"
       << "<fl c=\"3\">30</fl>"
       << "</tree>"
       //10 trees - species 2, no age specified
       << "<tree sp=\"1\" tp=\"3\">"
       << "<fl c=\"0\">40</fl>"
       << "<fl c=\"1\">40</fl>"
       << "<fl c=\"3\">30</fl>"
       << "</tree>"
       << "<tree sp=\"1\" tp=\"3\">"
       << "<fl c=\"0\">40</fl>"
       << "<fl c=\"1\">40</fl>"
       << "<fl c=\"3\">30</fl>"
       << "</tree>"
       << "<tree sp=\"1\" tp=\"3\">"
       << "<fl c=\"0\">40</fl>"
       << "<fl c=\"1\">40</fl>"
       << "<fl c=\"3\">30</fl>"
       << "</tree>"
       << "<tree sp=\"1\" tp=\"3\">"
       << "<fl c=\"0\">40</fl>"
       << "<fl c=\"1\">40</fl>"
       << "<fl c=\"3\">30</fl>"
       << "</tree>"
       << "<tree sp=\"1\" tp=\"3\">"
       << "<fl c=\"0\">40</fl>"
       << "<fl c=\"1\">40</fl>"
       << "<fl c=\"3\">30</fl>"
       << "</tree>"
       << "<tree sp=\"1\" tp=\"3\">"
       << "<fl c=\"0\">40</fl>"
       << "<fl c=\"1\">40</fl>"
       << "<fl c=\"3\">30</fl>"
       << "</tree>"
       << "<tree sp=\"1\" tp=\"3\">"
       << "<fl c=\"0\">40</fl>"
       << "<fl c=\"1\">40</fl>"
       << "<fl c=\"3\">30</fl>"
       << "</tree>"
       << "<tree sp=\"1\" tp=\"3\">"
       << "<fl c=\"0\">40</fl>"
       << "<fl c=\"1\">40</fl>"
       << "<fl c=\"3\">30</fl>"
       << "</tree>"
       << "<tree sp=\"1\" tp=\"3\">"
       << "<fl c=\"0\">40</fl>"
       << "<fl c=\"1\">40</fl>"
       << "<fl c=\"3\">30</fl>"
       << "</tree>"
       << "<tree sp=\"1\" tp=\"3\">"
       << "<fl c=\"0\">40</fl>"
       << "<fl c=\"1\">40</fl>"
       << "<fl c=\"3\">30</fl>"
       << "</tree>"
       //10 trees - species 3, age = 10
       << "<tree sp=\"2\" tp=\"3\">"
       << "<fl c=\"0\">50</fl>"
       << "<fl c=\"1\">50</fl>"
       << "<fl c=\"3\">30</fl>"
       << "<int c=\"0\">10</int>"
       << "</tree>"
       << "<tree sp=\"2\" tp=\"3\">"
       << "<fl c=\"0\">50</fl>"
       << "<fl c=\"1\">50</fl>"
       << "<fl c=\"3\">30</fl>"
       << "<int c=\"0\">10</int>"
       << "</tree>"
       << "<tree sp=\"2\" tp=\"3\">"
       << "<fl c=\"0\">50</fl>"
       << "<fl c=\"1\">50</fl>"
       << "<fl c=\"3\">30</fl>"
       << "<int c=\"0\">10</int>"
       << "</tree>"
       << "<tree sp=\"2\" tp=\"3\">"
       << "<fl c=\"0\">50</fl>"
       << "<fl c=\"1\">50</fl>"
       << "<fl c=\"3\">30</fl>"
       << "<int c=\"0\">10</int>"
       << "</tree>"
       << "<tree sp=\"2\" tp=\"3\">"
       << "<fl c=\"0\">50</fl>"
       << "<fl c=\"1\">50</fl>"
       << "<fl c=\"3\">30</fl>"
       << "<int c=\"0\">10</int>"
       << "</tree>"
       << "<tree sp=\"2\" tp=\"3\">"
       << "<fl c=\"0\">50</fl>"
       << "<fl c=\"1\">50</fl>"
       << "<fl c=\"3\">30</fl>"
       << "<int c=\"0\">10</int>"
       << "</tree>"
       << "<tree sp=\"2\" tp=\"3\">"
       << "<fl c=\"0\">50</fl>"
       << "<fl c=\"1\">50</fl>"
       << "<fl c=\"3\">30</fl>"
       << "<int c=\"0\">10</int>"
       << "</tree>"
       << "<tree sp=\"2\" tp=\"3\">"
       << "<fl c=\"0\">50</fl>"
       << "<fl c=\"1\">50</fl>"
       << "<fl c=\"3\">30</fl>"
       << "<int c=\"0\">10</int>"
       << "</tree>"
       << "<tree sp=\"2\" tp=\"3\">"
       << "<fl c=\"0\">50</fl>"
       << "<fl c=\"1\">50</fl>"
       << "<fl c=\"3\">30</fl>"
       << "<int c=\"0\">10</int>"
       << "</tree>"
       << "<tree sp=\"2\" tp=\"3\">"
       << "<fl c=\"0\">50</fl>"
       << "<fl c=\"1\">50</fl>"
       << "<fl c=\"3\">30</fl>"
       << "<int c=\"0\">10</int>"
       << "</tree>"
       << "</tr_treemap>"
       << "</trees>"
       << "<allometry>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_2\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_3\">39.48</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_2\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_3\">0.0549</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_3\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_3\">0.8008</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_3\">0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_2\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_3\">0.389</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_3\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_2\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_3\">0.03418</tr_sohdVal>"
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
       << "<behaviorName>TreeAgeCalculator</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "</paramFile>";

  oOut.close();
  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteTreeAgeCalculatorXMLFile2()
////////////////////////////////////////////////////////////////////////////
const char* WriteTreeAgeCalculatorXMLFile2() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

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
       << "</tr_speciesList>"
       << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
       << "<tr_minAdultDBH>"
       << "<tr_madVal species=\"Species_1\">0.0</tr_madVal>"
       << "<tr_madVal species=\"Species_2\">0.0</tr_madVal>"
       << "<tr_madVal species=\"Species_3\">0.0</tr_madVal>"
       << "</tr_minAdultDBH>"
       << "<tr_maxSeedlingHeight>"
       << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_2\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_3\">1.35</tr_mshVal>"
       << "</tr_maxSeedlingHeight>"
       << "<tr_sizeClasses>"
       << "<tr_sizeClass sizeKey=\"s50.0\"/>"
       << "<tr_sizeClass sizeKey=\"s60.0\"/>"
       << "</tr_sizeClasses>"
       << "<tr_initialDensities>"
       << "<tr_idVals whatSpecies=\"Species_2\">"
       << "<tr_initialDensity sizeClass=\"s60.0\">10.0</tr_initialDensity>"
       << "</tr_idVals>"
       << "</tr_initialDensities>"
       << "</trees>"
       << "<allometry>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_2\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_3\">39.48</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_2\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_3\">0.0549</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_3\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_3\">0.8008</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_3\">0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_2\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_3\">0.389</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_3\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_2\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_3\">0.03418</tr_sohdVal>"
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
       << "<behaviorName>TreeAgeCalculator</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "</paramFile>";

  oOut.close();
  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteTreeAgeCalculatorXMLErrorFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteTreeAgeCalculatorXMLErrorFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>3</timesteps>"
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
       << "</tr_speciesList>"
       << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
       << "<tr_minAdultDBH>"
       << "<tr_madVal species=\"Species_1\">0.0</tr_madVal>"
       << "<tr_madVal species=\"Species_2\">0.0</tr_madVal>"
       << "<tr_madVal species=\"Species_3\">0.0</tr_madVal>"
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
       << "<tr_chVal species=\"Species_2\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_3\">39.48</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_2\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_3\">0.0549</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_3\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_3\">0.8008</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_3\">0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_2\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_3\">0.389</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_3\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_2\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_3\">0.03418</tr_sohdVal>"
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
       << "<behaviorName>TreeAgeCalculator</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Snag\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "</paramFile>";

  oOut.close();
  return cFileString;
}
