//---------------------------------------------------------------------------
// TestGhostTreePopulation.cpp
//---------------------------------------------------------------------------
#include "TestGhostTreePopulation.h"
#include <gtest/gtest.h>
#include "SimManager.h"
#include "TreePopulation.h"
#include "GhostTreePopulation.h"
#include "DataTypes.h"
#include "BehaviorBase.h"
#include <fstream>
#include <math.h>

/////////////////////////////////////////////////////////////////////////////
// TestGhostTreePopulationRun1()
// Tests normal processing. This run has no snags.
/////////////////////////////////////////////////////////////////////////////
TEST(GhostTreePopulation, TestGhostTreePopulationRun1) {
  clTreePopulation * p_oPop;
  clTreeSearch *p_oAllTrees;
  clTree *p_oTree;
  clGhostTreePopulation *p_oGhosts;
  clDeadTree *p_oDeadTree;
  bool *p_bChecker;
  int iCount, i, iVal;
  deadCode iCode;
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {

    //Feed our file to the sim manager
    p_oSimManager->ReadFile(WriteGhostTreePopulationXMLFile1());

    p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject("treepopulation");
    p_oGhosts = (clGhostTreePopulation *) p_oSimManager->GetPopulationObject("GhostTreePopulation");

    //Create our trees
    iCode = notdead;
    p_oTree = p_oPop->CreateTree((100.0*clModelMath::GetRand()), //X
        (100.0*clModelMath::GetRand()), //Y
        0, //species
        clTreePopulation::seedling, //type
        0.2); //diameter
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iCode);

    iCode = harvest;
    p_oTree = p_oPop->CreateTree((100.0*clModelMath::GetRand()), //X
        (100.0*clModelMath::GetRand()), //Y
        0, //species
        clTreePopulation::seedling, //type
        0.2); //diameter
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iCode);

    iCode = natural;
    p_oTree = p_oPop->CreateTree((100.0*clModelMath::GetRand()), //X
        (100.0*clModelMath::GetRand()), //Y
        0, //species
        clTreePopulation::seedling, //type
        0.2); //diameter
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iCode);

    iCode = disease;
    p_oTree = p_oPop->CreateTree((100.0*clModelMath::GetRand()), //X
        (100.0*clModelMath::GetRand()), //Y
        0, //species
        clTreePopulation::seedling, //type
        0.2); //diameter
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iCode);

    iCode = fire;
    p_oTree = p_oPop->CreateTree((100.0*clModelMath::GetRand()), //X
        (100.0*clModelMath::GetRand()), //Y
        0, //species
        clTreePopulation::seedling, //type
        0.2); //diameter
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iCode);

    iCode = insects;
    p_oTree = p_oPop->CreateTree((100.0*clModelMath::GetRand()), //X
        (100.0*clModelMath::GetRand()), //Y
        0, //species
        clTreePopulation::seedling, //type
        0.2); //diameter
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iCode);

    iCode = storm;
    p_oTree = p_oPop->CreateTree((100.0*clModelMath::GetRand()), //X
        (100.0*clModelMath::GetRand()), //Y
        0, //species
        clTreePopulation::seedling, //type
        0.2); //diameter
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iCode);

    iCode = remove_tree;
    p_oTree = p_oPop->CreateTree((100.0*clModelMath::GetRand()), //X
        (100.0*clModelMath::GetRand()), //Y
        0, //species
        clTreePopulation::seedling, //type
        0.2); //diameter
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iCode);

    iCode = notdead;
    p_oTree = p_oPop->CreateTree((100.0*clModelMath::GetRand()), //X
        (100.0*clModelMath::GetRand()), //Y
        0, //species
        clTreePopulation::sapling, //type
        1); //diameter
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iCode);

    iCode = harvest;
    p_oTree = p_oPop->CreateTree((100.0*clModelMath::GetRand()), //X
        (100.0*clModelMath::GetRand()), //Y
        0, //species
        clTreePopulation::sapling, //type
        1); //diameter
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iCode);

    iCode = natural;
    p_oTree = p_oPop->CreateTree((100.0*clModelMath::GetRand()), //X
        (100.0*clModelMath::GetRand()), //Y
        0, //species
        clTreePopulation::sapling, //type
        1); //diameter
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iCode);

    iCode = disease;
    p_oTree = p_oPop->CreateTree((100.0*clModelMath::GetRand()), //X
        (100.0*clModelMath::GetRand()), //Y
        0, //species
        clTreePopulation::sapling, //type
        1); //diameter
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iCode);

    iCode = fire;
    p_oTree = p_oPop->CreateTree((100.0*clModelMath::GetRand()), //X
        (100.0*clModelMath::GetRand()), //Y
        0, //species
        clTreePopulation::sapling, //type
        1); //diameter
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iCode);

    iCode = insects;
    p_oTree = p_oPop->CreateTree((100.0*clModelMath::GetRand()), //X
        (100.0*clModelMath::GetRand()), //Y
        0, //species
        clTreePopulation::sapling, //type
        1); //diameter
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iCode);

    iCode = storm;
    p_oTree = p_oPop->CreateTree((100.0*clModelMath::GetRand()), //X
        (100.0*clModelMath::GetRand()), //Y
        0, //species
        clTreePopulation::sapling, //type
        1); //diameter
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iCode);

    iCode = remove_tree;
    p_oTree = p_oPop->CreateTree((100.0*clModelMath::GetRand()), //X
        (100.0*clModelMath::GetRand()), //Y
        0, //species
        clTreePopulation::sapling, //type
        1); //diameter
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iCode);

    iCode = notdead;
    p_oTree = p_oPop->CreateTree((100.0*clModelMath::GetRand()), //X
        (100.0*clModelMath::GetRand()), //Y
        0, //species
        clTreePopulation::adult, //type
        30.0 + iCode); //diameter
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iCode);

    iCode = harvest;
    p_oTree = p_oPop->CreateTree((100.0*clModelMath::GetRand()), //X
        (100.0*clModelMath::GetRand()), //Y
        0, //species
        clTreePopulation::adult, //type
        30.0 + iCode); //diameter
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iCode);

    iCode = natural;
    p_oTree = p_oPop->CreateTree((100.0*clModelMath::GetRand()), //X
        (100.0*clModelMath::GetRand()), //Y
        0, //species
        clTreePopulation::adult, //type
        30.0 + iCode); //diameter
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iCode);

    iCode = disease;
    p_oTree = p_oPop->CreateTree((100.0*clModelMath::GetRand()), //X
        (100.0*clModelMath::GetRand()), //Y
        0, //species
        clTreePopulation::adult, //type
        30.0 + iCode); //diameter
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iCode);

    iCode = fire;
    p_oTree = p_oPop->CreateTree((100.0*clModelMath::GetRand()), //X
        (100.0*clModelMath::GetRand()), //Y
        0, //species
        clTreePopulation::adult, //type
        30.0 + iCode); //diameter
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iCode);

    iCode = insects;
    p_oTree = p_oPop->CreateTree((100.0*clModelMath::GetRand()), //X
        (100.0*clModelMath::GetRand()), //Y
        0, //species
        clTreePopulation::adult, //type
        30.0 + iCode); //diameter
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iCode);

    iCode = storm;
    p_oTree = p_oPop->CreateTree((100.0*clModelMath::GetRand()), //X
        (100.0*clModelMath::GetRand()), //Y
        0, //species
        clTreePopulation::adult, //type
        30.0 + iCode); //diameter
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iCode);

    iCode = remove_tree;
    p_oTree = p_oPop->CreateTree((100.0*clModelMath::GetRand()), //X
        (100.0*clModelMath::GetRand()), //Y
        0, //species
        clTreePopulation::adult, //type
        30.0 + iCode); //diameter
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iCode);


    //Run a timestep but don't let cleanup happen
    for (i = 0; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
      clBehaviorBase *p_oBase = p_oSimManager->GetBehaviorObject(i);
      p_oBase->Action();
    }

    //Start with a simple check - there should be three trees still alive,
    //all with a code of notdead
    p_bChecker = new bool[3];
    for (i = 0; i < 3; i++) p_bChecker[i] = false;
    iCount = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      iCount++;
      EXPECT_FALSE(p_bChecker[p_oTree->GetType() - clTreePopulation::seedling]);
      p_bChecker[p_oTree->GetType() - clTreePopulation::seedling] = true;
      p_oTree->GetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), &iVal);
      EXPECT_EQ(notdead, iVal);
      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(3, iCount);
    delete[] p_bChecker;

    //There should be 21 ghosts
    iCount = 0;
    p_oDeadTree = p_oGhosts->GetFirstTree();
    while (p_oDeadTree) {
      iCount++;
      p_oDeadTree = p_oDeadTree->GetNext();
    }
    EXPECT_EQ(21, iCount);
    p_bChecker = new bool[remove_tree+1];
    //Check the seedlings
    for (i = 0; i <= remove_tree; i++) p_bChecker[i] = false;
    iCount = 0;
    p_oDeadTree = p_oGhosts->GetFirstTree();
    while (p_oDeadTree) {
      if (clTreePopulation::seedling == p_oDeadTree->GetType()) {
        EXPECT_FALSE(p_bChecker[p_oDeadTree->GetDeadReasonCode() - notdead]);
        p_bChecker[p_oDeadTree->GetDeadReasonCode() - notdead] = true;
        iCount++;
      }
      p_oDeadTree = p_oDeadTree->GetNext();
    }
    for (i = notdead+1; i <= remove_tree; i++) EXPECT_TRUE(p_bChecker[i]);

    //Check the saplings
    for (i = 0; i <= remove_tree; i++) p_bChecker[i] = false;
    p_oDeadTree = p_oGhosts->GetFirstTree();
    while (p_oDeadTree) {
      if (clTreePopulation::sapling == p_oDeadTree->GetType()) {
        EXPECT_FALSE(p_bChecker[p_oDeadTree->GetDeadReasonCode() - notdead]);
        p_bChecker[p_oDeadTree->GetDeadReasonCode() - notdead] = true;
      }
      p_oDeadTree = p_oDeadTree->GetNext();
    }
    for (i = notdead+1; i <= remove_tree; i++) EXPECT_TRUE(p_bChecker[i]);

    //Check the adults
    for (i = 0; i <= remove_tree; i++) p_bChecker[i] = false;
    p_oDeadTree = p_oGhosts->GetFirstTree();
    while (p_oDeadTree) {
      if (clTreePopulation::adult == p_oDeadTree->GetType()) {
        EXPECT_FALSE(p_bChecker[p_oDeadTree->GetDeadReasonCode() - notdead]);
        p_bChecker[p_oDeadTree->GetDeadReasonCode() - notdead] = true;
      }
      p_oDeadTree = p_oDeadTree->GetNext();
    }
    for (i = notdead+1; i <= remove_tree; i++) EXPECT_TRUE(p_bChecker[i]);
    delete[] p_bChecker;

    //Make sure cleanup happens correctly
    p_oSimManager->RunSim(1);
    EXPECT_EQ(NULL, p_oGhosts->GetFirstTree());

    //There should be three trees still alive,
    //all with a code of notdead
    p_bChecker = new bool[3];
    for (i = 0; i < 3; i++) p_bChecker[i] = false;
    iCount = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      iCount++;
      EXPECT_FALSE(p_bChecker[p_oTree->GetType() - clTreePopulation::seedling]);
      p_bChecker[p_oTree->GetType() - clTreePopulation::seedling] = true;
      p_oTree->GetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), &iVal);
      EXPECT_EQ(notdead, iVal);
      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(3, iCount);
  delete[] p_bChecker;
  delete p_oSimManager;
  } catch (modelErr &e) {
    delete[] p_bChecker;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestGhostTreePopulationRun2()
// Tests normal processing. This run has snags.
/////////////////////////////////////////////////////////////////////////////
TEST(GhostTreePopulation, TestGhostTreePopulationRun2) {
  clTreePopulation * p_oPop;
  clTreeSearch *p_oAllTrees;
  clTree *p_oTree;
  clGhostTreePopulation *p_oGhosts;
  clDeadTree *p_oDeadTree;
  bool *p_bChecker;
  int iCount, i, iVal;
  deadCode iCode;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    //Feed our file to the sim manager
    p_oSimManager->ReadFile(WriteGhostTreePopulationXMLFile2());

    p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject("treepopulation");
    p_oGhosts = (clGhostTreePopulation *) p_oSimManager->GetPopulationObject("GhostTreePopulation");

    //Create our trees
    iCode = notdead;
    p_oTree = p_oPop->CreateTree((100.0*clModelMath::GetRand()), //X
        (100.0*clModelMath::GetRand()), //Y
        0, //species
        clTreePopulation::seedling, //type
        0.2); //diameter
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iCode);

    iCode = harvest;
    p_oTree = p_oPop->CreateTree((100.0*clModelMath::GetRand()), //X
        (100.0*clModelMath::GetRand()), //Y
        0, //species
        clTreePopulation::seedling, //type
        0.2); //diameter
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iCode);

    iCode = natural;
    p_oTree = p_oPop->CreateTree((100.0*clModelMath::GetRand()), //X
        (100.0*clModelMath::GetRand()), //Y
        0, //species
        clTreePopulation::seedling, //type
        0.2); //diameter
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iCode);

    iCode = disease;
    p_oTree = p_oPop->CreateTree((100.0*clModelMath::GetRand()), //X
        (100.0*clModelMath::GetRand()), //Y
        0, //species
        clTreePopulation::seedling, //type
        0.2); //diameter
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iCode);

    iCode = fire;
    p_oTree = p_oPop->CreateTree((100.0*clModelMath::GetRand()), //X
        (100.0*clModelMath::GetRand()), //Y
        0, //species
        clTreePopulation::seedling, //type
        0.2); //diameter
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iCode);

    iCode = insects;
    p_oTree = p_oPop->CreateTree((100.0*clModelMath::GetRand()), //X
        (100.0*clModelMath::GetRand()), //Y
        0, //species
        clTreePopulation::seedling, //type
        0.2); //diameter
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iCode);

    iCode = storm;
    p_oTree = p_oPop->CreateTree((100.0*clModelMath::GetRand()), //X
        (100.0*clModelMath::GetRand()), //Y
        0, //species
        clTreePopulation::seedling, //type
        0.2); //diameter
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iCode);

    iCode = remove_tree;
    p_oTree = p_oPop->CreateTree((100.0*clModelMath::GetRand()), //X
        (100.0*clModelMath::GetRand()), //Y
        0, //species
        clTreePopulation::seedling, //type
        0.2); //diameter
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iCode);

    iCode = notdead;
    p_oTree = p_oPop->CreateTree((100.0*clModelMath::GetRand()), //X
        (100.0*clModelMath::GetRand()), //Y
        0, //species
        clTreePopulation::sapling, //type
        1); //diameter
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iCode);

    iCode = harvest;
    p_oTree = p_oPop->CreateTree((100.0*clModelMath::GetRand()), //X
        (100.0*clModelMath::GetRand()), //Y
        0, //species
        clTreePopulation::sapling, //type
        1); //diameter
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iCode);

    iCode = natural;
    p_oTree = p_oPop->CreateTree((100.0*clModelMath::GetRand()), //X
        (100.0*clModelMath::GetRand()), //Y
        0, //species
        clTreePopulation::sapling, //type
        1); //diameter
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iCode);

    iCode = disease;
    p_oTree = p_oPop->CreateTree((100.0*clModelMath::GetRand()), //X
        (100.0*clModelMath::GetRand()), //Y
        0, //species
        clTreePopulation::sapling, //type
        1); //diameter
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iCode);

    iCode = fire;
    p_oTree = p_oPop->CreateTree((100.0*clModelMath::GetRand()), //X
        (100.0*clModelMath::GetRand()), //Y
        0, //species
        clTreePopulation::sapling, //type
        1); //diameter
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iCode);

    iCode = insects;
    p_oTree = p_oPop->CreateTree((100.0*clModelMath::GetRand()), //X
        (100.0*clModelMath::GetRand()), //Y
        0, //species
        clTreePopulation::sapling, //type
        1); //diameter
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iCode);

    iCode = storm;
    p_oTree = p_oPop->CreateTree((100.0*clModelMath::GetRand()), //X
        (100.0*clModelMath::GetRand()), //Y
        0, //species
        clTreePopulation::sapling, //type
        1); //diameter
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iCode);

    iCode = remove_tree;
    p_oTree = p_oPop->CreateTree((100.0*clModelMath::GetRand()), //X
        (100.0*clModelMath::GetRand()), //Y
        0, //species
        clTreePopulation::sapling, //type
        1); //diameter
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iCode);

    iCode = notdead;
    p_oTree = p_oPop->CreateTree((100.0*clModelMath::GetRand()), //X
        (100.0*clModelMath::GetRand()), //Y
        0, //species
        clTreePopulation::adult, //type
        30.0 + iCode); //diameter
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iCode);

    iCode = harvest;
    p_oTree = p_oPop->CreateTree((100.0*clModelMath::GetRand()), //X
        (100.0*clModelMath::GetRand()), //Y
        0, //species
        clTreePopulation::adult, //type
        30.0 + iCode); //diameter
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iCode);

    iCode = natural;
    p_oTree = p_oPop->CreateTree((100.0*clModelMath::GetRand()), //X
        (100.0*clModelMath::GetRand()), //Y
        0, //species
        clTreePopulation::adult, //type
        30.0 + iCode); //diameter
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iCode);

    iCode = disease;
    p_oTree = p_oPop->CreateTree((100.0*clModelMath::GetRand()), //X
        (100.0*clModelMath::GetRand()), //Y
        0, //species
        clTreePopulation::adult, //type
        30.0 + iCode); //diameter
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iCode);

    iCode = fire;
    p_oTree = p_oPop->CreateTree((100.0*clModelMath::GetRand()), //X
        (100.0*clModelMath::GetRand()), //Y
        0, //species
        clTreePopulation::adult, //type
        30.0 + iCode); //diameter
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iCode);

    iCode = insects;
    p_oTree = p_oPop->CreateTree((100.0*clModelMath::GetRand()), //X
        (100.0*clModelMath::GetRand()), //Y
        0, //species
        clTreePopulation::adult, //type
        30.0 + iCode); //diameter
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iCode);

    iCode = storm;
    p_oTree = p_oPop->CreateTree((100.0*clModelMath::GetRand()), //X
        (100.0*clModelMath::GetRand()), //Y
        0, //species
        clTreePopulation::adult, //type
        30.0 + iCode); //diameter
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iCode);

    iCode = remove_tree;
    p_oTree = p_oPop->CreateTree((100.0*clModelMath::GetRand()), //X
        (100.0*clModelMath::GetRand()), //Y
        0, //species
        clTreePopulation::adult, //type
        30.0 + iCode); //diameter
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iCode);

    iCode = notdead;
    p_oTree = p_oPop->CreateTree((100.0*clModelMath::GetRand()), //X
        (100.0*clModelMath::GetRand()), //Y
        0, //species
        clTreePopulation::snag, //type
        30.0 + iCode); //diameter
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iCode);

    iCode = harvest;
    p_oTree = p_oPop->CreateTree((100.0*clModelMath::GetRand()), //X
        (100.0*clModelMath::GetRand()), //Y
        0, //species
        clTreePopulation::snag, //type
        30.0 + iCode); //diameter
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iCode);

    iCode = natural;
    p_oTree = p_oPop->CreateTree((100.0*clModelMath::GetRand()), //X
        (100.0*clModelMath::GetRand()), //Y
        0, //species
        clTreePopulation::snag, //type
        30.0 + iCode); //diameter
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iCode);

    iCode = disease;
    p_oTree = p_oPop->CreateTree((100.0*clModelMath::GetRand()), //X
        (100.0*clModelMath::GetRand()), //Y
        0, //species
        clTreePopulation::snag, //type
        30.0 + iCode); //diameter
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iCode);

    iCode = fire;
    p_oTree = p_oPop->CreateTree((100.0*clModelMath::GetRand()), //X
        (100.0*clModelMath::GetRand()), //Y
        0, //species
        clTreePopulation::snag, //type
        30.0 + iCode); //diameter
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iCode);

    iCode = insects;
    p_oTree = p_oPop->CreateTree((100.0*clModelMath::GetRand()), //X
        (100.0*clModelMath::GetRand()), //Y
        0, //species
        clTreePopulation::snag, //type
        30.0 + iCode); //diameter
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iCode);

    iCode = storm;
    p_oTree = p_oPop->CreateTree((100.0*clModelMath::GetRand()), //X
        (100.0*clModelMath::GetRand()), //Y
        0, //species
        clTreePopulation::snag, //type
        30.0 + iCode); //diameter
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iCode);

    iCode = remove_tree;
    p_oTree = p_oPop->CreateTree((100.0*clModelMath::GetRand()), //X
        (100.0*clModelMath::GetRand()), //Y
        0, //species
        clTreePopulation::snag, //type
        30.0 + iCode); //diameter
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iCode);


    //Run a timestep but don't let cleanup happen
    for (i = 0; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
      clBehaviorBase *p_oBase = p_oSimManager->GetBehaviorObject(i);
      p_oBase->Action();
    }

    //Start with a simple check - there should be four trees still alive,
    //all with a code of notdead, as well as five new snags
    iCount = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      iCount++;
      p_oTree->GetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), &iVal);
      EXPECT_EQ(notdead, iVal);
      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(9, iCount);

    iCount = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (clTreePopulation::snag == p_oTree->GetType()) {
        iCount++;
      }
      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(6, iCount);

    //There should be 28 ghosts
    iCount = 0;
    p_oDeadTree = p_oGhosts->GetFirstTree();
    while (p_oDeadTree) {
      iCount++;
      p_oDeadTree = p_oDeadTree->GetNext();
    }
    EXPECT_EQ(28, iCount);
    p_bChecker = new bool[remove_tree+1];
    //Check the seedlings
    for (i = 0; i <= remove_tree; i++) p_bChecker[i] = false;
    p_oDeadTree = p_oGhosts->GetFirstTree();
    while (p_oDeadTree) {
      if (clTreePopulation::seedling == p_oDeadTree->GetType()) {
        EXPECT_FALSE(p_bChecker[p_oDeadTree->GetDeadReasonCode() - notdead]);
        p_bChecker[p_oDeadTree->GetDeadReasonCode() - notdead] = true;
      }
      p_oDeadTree = p_oDeadTree->GetNext();
    }
    for (i = notdead+1; i <= remove_tree; i++) EXPECT_TRUE(p_bChecker[i]);

    //Check the saplings
    for (i = 0; i <= remove_tree; i++) p_bChecker[i] = false;
    p_oDeadTree = p_oGhosts->GetFirstTree();
    while (p_oDeadTree) {
      if (clTreePopulation::sapling == p_oDeadTree->GetType()) {
        EXPECT_FALSE(p_bChecker[p_oDeadTree->GetDeadReasonCode() - notdead]);
        p_bChecker[p_oDeadTree->GetDeadReasonCode() - notdead] = true;
      }
      p_oDeadTree = p_oDeadTree->GetNext();
    }
    for (i = notdead+1; i <= remove_tree; i++) EXPECT_TRUE(p_bChecker[i]);

    //Check the adults
    for (i = 0; i <= remove_tree; i++) p_bChecker[i] = false;
    p_oDeadTree = p_oGhosts->GetFirstTree();
    while (p_oDeadTree) {
      if (clTreePopulation::adult == p_oDeadTree->GetType()) {
        EXPECT_FALSE(p_bChecker[p_oDeadTree->GetDeadReasonCode() - notdead]);
        p_bChecker[p_oDeadTree->GetDeadReasonCode() - notdead] = true;
      }
      p_oDeadTree = p_oDeadTree->GetNext();
    }
    for (i = notdead+1; i <= remove_tree; i++) EXPECT_TRUE(p_bChecker[i]);

    //Check the snags
    for (i = 0; i <= remove_tree; i++) p_bChecker[i] = false;
    p_oDeadTree = p_oGhosts->GetFirstTree();
    while (p_oDeadTree) {
      if (clTreePopulation::snag == p_oDeadTree->GetType()) {
        EXPECT_FALSE(p_bChecker[p_oDeadTree->GetDeadReasonCode() - notdead]);
        p_bChecker[p_oDeadTree->GetDeadReasonCode() - notdead] = true;
      }
      p_oDeadTree = p_oDeadTree->GetNext();
    }
    for (i = notdead+1; i <= remove_tree; i++) EXPECT_TRUE(p_bChecker[i]);
    delete[] p_bChecker;

    //Make sure cleanup happens correctly
    p_oSimManager->RunSim(1);
    EXPECT_EQ(NULL, p_oGhosts->GetFirstTree());

    //There should be nine trees still alive, all with a code of notdead
    iCount = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      iCount++;
      p_oTree->GetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), &iVal);
      EXPECT_EQ(notdead, iVal);
      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(9, iCount);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}


/////////////////////////////////////////////////////////////////////////////
// WriteGhostTreePopulationXMLFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteGhostTreePopulationXMLFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>1</timesteps>"
       << "<yearsPerTimestep>5</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>100.0</plot_lenX>"
       << "<plot_lenY>100.0</plot_lenY>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "</plot>"
       << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\"/>"
       << "<tr_species speciesName=\"Species_2\"/>"
       << "<tr_species speciesName=\"Species_3\"/>"
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
       << "<tr_chVal species=\"Species_3\">40.0</tr_chVal>"
       << "</tr_canopyHeight>"
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
       << "<tr_stdMaxCrownRad>"
       << "<tr_smcrVal species=\"Species_1\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_2\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_3\">10</tr_smcrVal>"
       << "</tr_stdMaxCrownRad>"
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
       << "</allometry>";


  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>StochasticMortality</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RemoveDead</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<StochasticMortality1>"
       << "<mo_stochasticMortRate>"
       << "<mo_smrVal species=\"Species_1\">0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_2\">0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_3\">0</mo_smrVal>"
       << "</mo_stochasticMortRate>"
       << "</StochasticMortality1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteGhostTreePopulationXMLFile2()
/////////////////////////////////////////////////////////////////////////////
const char* WriteGhostTreePopulationXMLFile2() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>1</timesteps>"
       << "<yearsPerTimestep>5</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>100.0</plot_lenX>"
       << "<plot_lenY>100.0</plot_lenY>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "</plot>"
       << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\"/>"
       << "<tr_species speciesName=\"Species_2\"/>"
       << "<tr_species speciesName=\"Species_3\"/>"
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
       << "<tr_chVal species=\"Species_3\">40.0</tr_chVal>"
       << "</tr_canopyHeight>"
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
       << "<tr_stdMaxCrownRad>"
       << "<tr_smcrVal species=\"Species_1\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_2\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_3\">10</tr_smcrVal>"
       << "</tr_stdMaxCrownRad>"
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
       << "</allometry>";


  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>StochasticMortality</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Snag\"/>"
       << "<applyTo species=\"Species_2\" type=\"Snag\"/>"
       << "<applyTo species=\"Species_3\" type=\"Snag\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RemoveDead</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Snag\"/>"
       << "<applyTo species=\"Species_2\" type=\"Snag\"/>"
       << "<applyTo species=\"Species_3\" type=\"Snag\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<StochasticMortality1>"
       << "<mo_stochasticMortRate>"
       << "<mo_smrVal species=\"Species_1\">0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_2\">0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_3\">0</mo_smrVal>"
       << "</mo_stochasticMortRate>"
       << "</StochasticMortality1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}
