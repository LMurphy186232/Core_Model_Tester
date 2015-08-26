//---------------------------------------------------------------------------
// TestQualityVigorClassifier.cpp
//---------------------------------------------------------------------------
#include "TestQualityVigorClassifier.h"
#include <gtest/gtest.h>
#include <fstream>
#include <math.h>
#include "TreePopulation.h"
#include "SimManager.h"
#include "BehaviorBase.h"
#include "QualityVigorClassifier.h"


////////////////////////////////////////////////////////////////////////////
// TestInitialConditions()
// Tests class assignment. WriteQualityVigorClassifierXMLFile2() and WriteQualityVigorClassifierXMLFile3() does setup.
////////////////////////////////////////////////////////////////////////////
TEST(QualityVigorClassifier, TestInitialConditions) {

  clTreePopulation * p_oPop;
  clTreeSearch *p_oTreeSearch;
  clTree *p_oTree;
  int *p_iNumTrees;
  float fDBH;
  int iClass, iNumSpecies = 5, i, iSp, iTp;
  bool bVal;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {

    p_iNumTrees = new int[iNumSpecies];

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteQualityVigorClassifierXMLFile2() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Count vigorous trees, 10-20
    for (i = 0; i < iNumSpecies; i++) p_iNumTrees[i] = 0;
    p_oTreeSearch = p_oPop->Find("all");
    p_oTree = p_oTreeSearch->NextTree();
    while (p_oTree) {
      iSp = p_oTree->GetSpecies();
      iTp = p_oTree->GetType();

      p_oTree->GetValue(p_oPop->GetDbhCode(iSp, iTp), &fDBH);
      if (fDBH > 10 && fDBH <= 20 && iSp > 0) {
        p_oTree->GetValue(p_oPop->GetBoolDataCode("vigorous", iSp, iTp), &bVal);
        if (bVal) p_iNumTrees[iSp]++;
      }
      p_oTree = p_oTreeSearch->NextTree();
    }

    EXPECT_LT(fabs(780 - p_iNumTrees[1]) / 780, 0.1);
    EXPECT_LT(fabs(880 - p_iNumTrees[2]) / 880, 0.1);
    EXPECT_EQ(p_iNumTrees[3], 0);
    EXPECT_LT(fabs(610 - p_iNumTrees[4]) / 610, 0.1);

    //Count vigorous trees, 20-30
    for (i = 0; i < iNumSpecies; i++) p_iNumTrees[i] = 0;
    p_oTreeSearch = p_oPop->Find("all");
    p_oTree = p_oTreeSearch->NextTree();
    while (p_oTree) {
      iSp = p_oTree->GetSpecies();
      iTp = p_oTree->GetType();

      p_oTree->GetValue(p_oPop->GetDbhCode(iSp, iTp), &fDBH);
      if (fDBH > 20 && fDBH <= 30 && iSp > 0) {
        p_oTree->GetValue(p_oPop->GetBoolDataCode("vigorous", iSp, iTp), &bVal);
        if (bVal) p_iNumTrees[iSp]++;
      }
      p_oTree = p_oTreeSearch->NextTree();
    }

    EXPECT_LT(fabs(330 - p_iNumTrees[1]) / 330, 0.1);
    EXPECT_LT(fabs(810 - p_iNumTrees[2]) / 810, 0.1);
    EXPECT_LT(fabs(640 - p_iNumTrees[3]) / 640, 0.1);
    EXPECT_LT(fabs(320 - p_iNumTrees[4]) / 320, 0.25);

    //Count vigorous trees, 30-40
    for (i = 0; i < iNumSpecies; i++) p_iNumTrees[i] = 0;
    p_oTreeSearch = p_oPop->Find("all");
    p_oTree = p_oTreeSearch->NextTree();
    while (p_oTree) {
      iSp = p_oTree->GetSpecies();
      iTp = p_oTree->GetType();

      p_oTree->GetValue(p_oPop->GetDbhCode(iSp, iTp), &fDBH);
      if (fDBH > 30 && fDBH <= 40 && iSp > 0) {
        p_oTree->GetValue(p_oPop->GetBoolDataCode("vigorous", iSp, iTp), &bVal);
        if (bVal) p_iNumTrees[iSp]++;
      }
      p_oTree = p_oTreeSearch->NextTree();
    }

    EXPECT_LT(fabs(340 - p_iNumTrees[1]) / 340, 0.1);
    EXPECT_LT(fabs(570 - p_iNumTrees[2]) / 570, 0.1);
    EXPECT_LT(fabs(260 - p_iNumTrees[3]) / 260, 0.1);
    EXPECT_LT(fabs(460 - p_iNumTrees[4]) / 460, 0.1);

    //Count vigorous trees, 40-50
    for (i = 0; i < iNumSpecies; i++) p_iNumTrees[i] = 0;
    p_oTreeSearch = p_oPop->Find("all");
    p_oTree = p_oTreeSearch->NextTree();
    while (p_oTree) {
      iSp = p_oTree->GetSpecies();
      iTp = p_oTree->GetType();

      p_oTree->GetValue(p_oPop->GetDbhCode(iSp, iTp), &fDBH);
      if (fDBH > 40 && fDBH <= 50 && iSp > 0) {
        p_oTree->GetValue(p_oPop->GetBoolDataCode("vigorous", iSp, iTp), &bVal);
        if (bVal) p_iNumTrees[iSp]++;
      }
      p_oTree = p_oTreeSearch->NextTree();
    }

    EXPECT_LT(fabs(100 - p_iNumTrees[1]) / 100, 0.1);
    EXPECT_LT(fabs(250 - p_iNumTrees[2]) / 250, 0.1);
    EXPECT_LT(fabs(500 - p_iNumTrees[3]) / 500, 0.1);
    EXPECT_LT(fabs(740 - p_iNumTrees[4]) / 740, 0.1);

    //Count sawlog trees, 10-20
    for (i = 0; i < iNumSpecies; i++) p_iNumTrees[i] = 0;
    p_oTreeSearch = p_oPop->Find("all");
    p_oTree = p_oTreeSearch->NextTree();
    while (p_oTree) {
      iSp = p_oTree->GetSpecies();
      iTp = p_oTree->GetType();

      p_oTree->GetValue(p_oPop->GetDbhCode(iSp, iTp), &fDBH);
      if (fDBH > 10 && fDBH <= 20 && (iSp == 1 || iSp == 3)) {
        p_oTree->GetValue(p_oPop->GetBoolDataCode("sawlog", iSp, iTp), &bVal);
        if (bVal) p_iNumTrees[iSp]++;
      }
      p_oTree = p_oTreeSearch->NextTree();
    }

    EXPECT_LT(fabs(330 - p_iNumTrees[1]) / 330, 0.1);
    EXPECT_EQ(p_iNumTrees[3], 1000);

    //Count sawlog trees, 20-30
    for (i = 0; i < iNumSpecies; i++) p_iNumTrees[i] = 0;
    p_oTreeSearch = p_oPop->Find("all");
    p_oTree = p_oTreeSearch->NextTree();
    while (p_oTree) {
      iSp = p_oTree->GetSpecies();
      iTp = p_oTree->GetType();

      p_oTree->GetValue(p_oPop->GetDbhCode(iSp, iTp), &fDBH);
      if (fDBH > 20 && fDBH <= 30 && (iSp == 1 || iSp == 3)) {
        p_oTree->GetValue(p_oPop->GetBoolDataCode("sawlog", iSp, iTp), &bVal);
        if (bVal) p_iNumTrees[iSp]++;
      }
      p_oTree = p_oTreeSearch->NextTree();
    }

    EXPECT_LT(fabs(320 - p_iNumTrees[1]) / 320, 0.1);
    EXPECT_LT(fabs(330 - p_iNumTrees[3]) / 330, 0.1);

    //Count sawlog trees, 30-40
    for (i = 0; i < iNumSpecies; i++) p_iNumTrees[i] = 0;
    p_oTreeSearch = p_oPop->Find("all");
    p_oTree = p_oTreeSearch->NextTree();
    while (p_oTree) {
      iSp = p_oTree->GetSpecies();
      iTp = p_oTree->GetType();

      p_oTree->GetValue(p_oPop->GetDbhCode(iSp, iTp), &fDBH);
      if (fDBH > 30 && fDBH <= 40 && (iSp == 1 || iSp == 3)) {
        p_oTree->GetValue(p_oPop->GetBoolDataCode("sawlog", iSp, iTp), &bVal);
        if (bVal) p_iNumTrees[iSp]++;
      }
      p_oTree = p_oTreeSearch->NextTree();
    }

    EXPECT_LT(fabs(130 - p_iNumTrees[1]) / 130, 0.1);
    EXPECT_LT(fabs(660 - p_iNumTrees[3]) / 660, 0.1);

    //Count sawlog trees, 40-50
    for (i = 0; i < iNumSpecies; i++) p_iNumTrees[i] = 0;
    p_oTreeSearch = p_oPop->Find("all");
    p_oTree = p_oTreeSearch->NextTree();
    while (p_oTree) {
      iSp = p_oTree->GetSpecies();
      iTp = p_oTree->GetType();

      p_oTree->GetValue(p_oPop->GetDbhCode(iSp, iTp), &fDBH);
      if (fDBH > 40 && fDBH <= 50 && (iSp == 1 || iSp == 3)) {
        p_oTree->GetValue(p_oPop->GetBoolDataCode("sawlog", iSp, iTp), &bVal);
        if (bVal) p_iNumTrees[iSp]++;
      }
      p_oTree = p_oTreeSearch->NextTree();
    }

    EXPECT_LT(fabs(900 - p_iNumTrees[1]) / 900, 0.1);
    EXPECT_LT(fabs(300 - p_iNumTrees[3]) / 300, 0.1);


    //***************************
    // Run 2
    p_oSimManager->ReadFile( WriteQualityVigorClassifierXMLFile3() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Count class 1 and 5 trees, 10-20; should be 10 from map
    for (i = 0; i < iNumSpecies; i++) p_iNumTrees[i] = 0;
    p_oTreeSearch = p_oPop->Find("all");
    p_oTree = p_oTreeSearch->NextTree();
    while (p_oTree) {
      iSp = p_oTree->GetSpecies();
      iTp = p_oTree->GetType();

      p_oTree->GetValue(p_oPop->GetDbhCode(iSp, iTp), &fDBH);
      if (fDBH > 10 && fDBH <= 20 && iSp > 0) {
        p_oTree->GetValue(p_oPop->GetIntDataCode("treeclass", iSp, iTp), &iClass);
        if (iClass == 1 || iClass == 5) p_iNumTrees[iSp]++;
      }
      p_oTree = p_oTreeSearch->NextTree();
    }

    EXPECT_EQ(p_iNumTrees[1], 10);
    EXPECT_EQ(p_iNumTrees[2], 10);
    EXPECT_EQ(p_iNumTrees[3], 10);
    EXPECT_EQ(p_iNumTrees[4], 10);

    //Count other trees, 10-20; should be 1000 from initial conditions
    for (i = 0; i < iNumSpecies; i++) p_iNumTrees[i] = 0;
    p_oTreeSearch = p_oPop->Find("all");
    p_oTree = p_oTreeSearch->NextTree();
    while (p_oTree) {
      iSp = p_oTree->GetSpecies();
      iTp = p_oTree->GetType();

      p_oTree->GetValue(p_oPop->GetDbhCode(iSp, iTp), &fDBH);
      if (fDBH > 10 && fDBH <= 20 && iSp > 0) {
        p_oTree->GetValue(p_oPop->GetIntDataCode("treeclass", iSp, iTp), &iClass);
        if (iClass != 1 && iClass != 5) p_iNumTrees[iSp]++;
      }
      p_oTree = p_oTreeSearch->NextTree();
    }

    EXPECT_EQ(p_iNumTrees[1], 1000);
    EXPECT_EQ(p_iNumTrees[2], 1000);
    EXPECT_EQ(p_iNumTrees[3], 1000);
    EXPECT_EQ(p_iNumTrees[4], 1000);

    //Count class 1 and 5 trees, 20-30; should be 10 from map
    for (i = 0; i < iNumSpecies; i++) p_iNumTrees[i] = 0;
    p_oTreeSearch = p_oPop->Find("all");
    p_oTree = p_oTreeSearch->NextTree();
    while (p_oTree) {
      iSp = p_oTree->GetSpecies();
      iTp = p_oTree->GetType();

      p_oTree->GetValue(p_oPop->GetDbhCode(iSp, iTp), &fDBH);
      if (fDBH > 20 && fDBH <= 30 && iSp > 0) {
        p_oTree->GetValue(p_oPop->GetIntDataCode("treeclass", iSp, iTp), &iClass);
        if (iClass == 1 || iClass == 5) p_iNumTrees[iSp]++;
      }
      p_oTree = p_oTreeSearch->NextTree();
    }

    EXPECT_EQ(p_iNumTrees[1], 10);
    EXPECT_EQ(p_iNumTrees[2], 10);
    EXPECT_EQ(p_iNumTrees[3], 10);
    EXPECT_EQ(p_iNumTrees[4], 10);

    //Count other trees, 20-30; should be 1000 from initial conditions
    for (i = 0; i < iNumSpecies; i++) p_iNumTrees[i] = 0;
    p_oTreeSearch = p_oPop->Find("all");
    p_oTree = p_oTreeSearch->NextTree();
    while (p_oTree) {
      iSp = p_oTree->GetSpecies();
      iTp = p_oTree->GetType();

      p_oTree->GetValue(p_oPop->GetDbhCode(iSp, iTp), &fDBH);
      if (fDBH > 20 && fDBH <= 30 && iSp > 0) {
        p_oTree->GetValue(p_oPop->GetIntDataCode("treeclass", iSp, iTp), &iClass);
        if (iClass != 1 && iClass != 5) p_iNumTrees[iSp]++;
      }
      p_oTree = p_oTreeSearch->NextTree();
    }

    EXPECT_EQ(p_iNumTrees[1], 1000);
    EXPECT_EQ(p_iNumTrees[2], 1000);
    EXPECT_EQ(p_iNumTrees[3], 1000);
    EXPECT_EQ(p_iNumTrees[4], 1000);

    //Count class 1 and 5 trees, 30-40; should be 10 from map
    for (i = 0; i < iNumSpecies; i++) p_iNumTrees[i] = 0;
    p_oTreeSearch = p_oPop->Find("all");
    p_oTree = p_oTreeSearch->NextTree();
    while (p_oTree) {
      iSp = p_oTree->GetSpecies();
      iTp = p_oTree->GetType();

      p_oTree->GetValue(p_oPop->GetDbhCode(iSp, iTp), &fDBH);
      if (fDBH > 30 && fDBH <= 40 && iSp > 0) {
        p_oTree->GetValue(p_oPop->GetIntDataCode("treeclass", iSp, iTp), &iClass);
        if (iClass == 1 || iClass == 5) p_iNumTrees[iSp]++;
      }
      p_oTree = p_oTreeSearch->NextTree();
    }

    EXPECT_EQ(p_iNumTrees[1], 10);
    EXPECT_EQ(p_iNumTrees[2], 10);
    EXPECT_EQ(p_iNumTrees[3], 10);
    EXPECT_EQ(p_iNumTrees[4], 10);

    //Count other trees, 30-40; should be 1000 from initial conditions
    for (i = 0; i < iNumSpecies; i++) p_iNumTrees[i] = 0;
    p_oTreeSearch = p_oPop->Find("all");
    p_oTree = p_oTreeSearch->NextTree();
    while (p_oTree) {
      iSp = p_oTree->GetSpecies();
      iTp = p_oTree->GetType();

      p_oTree->GetValue(p_oPop->GetDbhCode(iSp, iTp), &fDBH);
      if (fDBH > 30 && fDBH <= 40 && iSp > 0) {
        p_oTree->GetValue(p_oPop->GetIntDataCode("treeclass", iSp, iTp), &iClass);
        if (iClass != 1 && iClass != 5) p_iNumTrees[iSp]++;
      }
      p_oTree = p_oTreeSearch->NextTree();
    }

    EXPECT_EQ(p_iNumTrees[1], 1000);
    EXPECT_EQ(p_iNumTrees[2], 1000);
    EXPECT_EQ(p_iNumTrees[3], 1000);
    EXPECT_EQ(p_iNumTrees[4], 1000);

    //Count class 1 and 5 trees, 40-50; should be 10 from map
    for (i = 0; i < iNumSpecies; i++) p_iNumTrees[i] = 0;
    p_oTreeSearch = p_oPop->Find("all");
    p_oTree = p_oTreeSearch->NextTree();
    while (p_oTree) {
      iSp = p_oTree->GetSpecies();
      iTp = p_oTree->GetType();

      p_oTree->GetValue(p_oPop->GetDbhCode(iSp, iTp), &fDBH);
      if (fDBH > 40 && fDBH <= 50 && iSp > 0) {
        p_oTree->GetValue(p_oPop->GetIntDataCode("treeclass", iSp, iTp), &iClass);
        if (iClass == 1 || iClass == 5) p_iNumTrees[iSp]++;
      }
      p_oTree = p_oTreeSearch->NextTree();
    }

    EXPECT_EQ(p_iNumTrees[1], 10);
    EXPECT_EQ(p_iNumTrees[2], 10);
    EXPECT_EQ(p_iNumTrees[3], 10);
    EXPECT_EQ(p_iNumTrees[4], 10);

    //Count other trees, 40-50; should be 1000 from initial conditions
    for (i = 0; i < iNumSpecies; i++) p_iNumTrees[i] = 0;
    p_oTreeSearch = p_oPop->Find("all");
    p_oTree = p_oTreeSearch->NextTree();
    while (p_oTree) {
      iSp = p_oTree->GetSpecies();
      iTp = p_oTree->GetType();

      p_oTree->GetValue(p_oPop->GetDbhCode(iSp, iTp), &fDBH);
      if (fDBH > 40 && fDBH <= 50 && iSp > 0) {
        p_oTree->GetValue(p_oPop->GetIntDataCode("treeclass", iSp, iTp), &iClass);
        if (iClass != 1 && iClass != 5) p_iNumTrees[iSp]++;
      }
      p_oTree = p_oTreeSearch->NextTree();
    }

    EXPECT_EQ(p_iNumTrees[1], 1000);
    EXPECT_EQ(p_iNumTrees[2], 1000);
    EXPECT_EQ(p_iNumTrees[3], 1000);
    EXPECT_EQ(p_iNumTrees[4], 1000);

    delete[] p_iNumTrees;
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete[] p_iNumTrees;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestClassAssignment()
// Tests class assignment. XMLFile1() does setup.
////////////////////////////////////////////////////////////////////////////
TEST(QualityVigorClassifier, TestClassAssignment) {
  clTreePopulation * p_oPop;
  clTreeSearch *p_oTreeSearch;
  clTree *p_oTree;
  clTree **p_oTrees; //array to hold our target trees
  float fX;
  int iClass, iExpectedClass, iNumTrees = 13, i, iSp, iTp;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteQualityVigorClassifierXMLFile1(true) );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Retrieve trees
    p_oTrees = new clTree*[iNumTrees];
    p_oTreeSearch = p_oPop->Find("all");
    p_oTree = p_oTreeSearch->NextTree();
    while (p_oTree) {
      iSp = p_oTree->GetSpecies();
      iTp = p_oTree->GetType();
      p_oTree->GetValue(p_oPop->GetXCode(iSp, iTp), &fX);
      p_oTrees[((int)fX-1)] = p_oTree;
      p_oTree = p_oTreeSearch->NextTree();
    }

    clBehaviorBase *p_oBase = p_oSimManager->GetBehaviorObject(0);
    clQualityVigorClassifier *p_oBeh = dynamic_cast<clQualityVigorClassifier*>(p_oBase);

    for (i = 0; i < iNumTrees; i++) p_oBeh->AssignClass(p_oPop, p_oTrees[i]);

    iExpectedClass = 1;
    p_oTrees[0]->GetValue(p_oPop->GetIntDataCode("treeclass", iSp, iTp), &iClass);
    EXPECT_EQ(iExpectedClass, iClass);

    iExpectedClass = 2;
    p_oTrees[1]->GetValue(p_oPop->GetIntDataCode("treeclass", iSp, iTp), &iClass);
    EXPECT_EQ(iExpectedClass, iClass);

    iExpectedClass = 3;
    p_oTrees[2]->GetValue(p_oPop->GetIntDataCode("treeclass", iSp, iTp), &iClass);
    EXPECT_EQ(iExpectedClass, iClass);

    iExpectedClass = 4;
    p_oTrees[3]->GetValue(p_oPop->GetIntDataCode("treeclass", iSp, iTp), &iClass);
    EXPECT_EQ(iExpectedClass, iClass);

    iExpectedClass = 4;
    p_oTrees[4]->GetValue(p_oPop->GetIntDataCode("treeclass", iSp, iTp), &iClass);
    EXPECT_EQ(iExpectedClass, iClass);

    iExpectedClass = 5;
    p_oTrees[5]->GetValue(p_oPop->GetIntDataCode("treeclass", iSp, iTp), &iClass);
    EXPECT_EQ(iExpectedClass, iClass);

    iExpectedClass = 6;
    p_oTrees[6]->GetValue(p_oPop->GetIntDataCode("treeclass", iSp, iTp), &iClass);
    EXPECT_EQ(iExpectedClass, iClass);

    iExpectedClass = 1;
    p_oTrees[7]->GetValue(p_oPop->GetIntDataCode("treeclass", iSp, iTp), &iClass);
    EXPECT_EQ(iExpectedClass, iClass);

    iExpectedClass = 2;
    p_oTrees[8]->GetValue(p_oPop->GetIntDataCode("treeclass", iSp, iTp), &iClass);
    EXPECT_EQ(iExpectedClass, iClass);

    iExpectedClass = 4;
    p_oTrees[9]->GetValue(p_oPop->GetIntDataCode("treeclass", iSp, iTp), &iClass);
    EXPECT_EQ(iExpectedClass, iClass);

    iExpectedClass = 4;
    p_oTrees[10]->GetValue(p_oPop->GetIntDataCode("treeclass", iSp, iTp), &iClass);
    EXPECT_EQ(iExpectedClass, iClass);

    iExpectedClass = 5;
    p_oTrees[11]->GetValue(p_oPop->GetIntDataCode("treeclass", iSp, iTp), &iClass);
    EXPECT_EQ(iExpectedClass, iClass);

    iExpectedClass = 6;
    p_oTrees[12]->GetValue(p_oPop->GetIntDataCode("treeclass", iSp, iTp), &iClass);
    EXPECT_EQ(iExpectedClass, iClass);

    delete[] p_oTrees;
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete[] p_oTrees;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestEvolveClass()
// Tests normal processing. XMLFile1() does setup. This directly tests
// the output from the clQualityVigorClassifier::EvolveVigorQuality function,
// and also creates adult trees by 1000s to test it indirectly.
////////////////////////////////////////////////////////////////////////////
TEST(QualityVigorClassifier, TestEvolveClass) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTreeSearch *p_oTrees;
    clTree *p_oTree;
    float fDiam, fX;
    int i, iSp, iTp, iNumVigorous, iNumSawlog, iNumTotal, iClass;
    bool bVigorous, bSawlog;

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteQualityVigorClassifierXMLFile1(false) );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    fDiam = 10;

    //Create our adult trees
    iTp = clTreePopulation::adult;

    //Tree 1 - initial class 1
    fDiam = 10;
    iSp = 1;
    iClass = 1;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(1, 1, iSp, iTp, fDiam);
      p_oTree->SetValue(p_oPop->GetIntDataCode("treeclass", iSp,  iTp), iClass);
    }

    //Tree 2 - initial class 2
    fDiam = 20;
    iSp = 1;
    iClass = 2;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(2, 2, iSp, iTp, fDiam);
      p_oTree->SetValue(p_oPop->GetIntDataCode("treeclass", iSp,  iTp), iClass);
    }

    //Tree 3 - initial class 3
    fDiam = 30;
    iSp = 1;
    iClass = 3;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(3, 3, iSp, iTp, fDiam);
      p_oTree->SetValue(p_oPop->GetIntDataCode("treeclass", iSp,  iTp), iClass);
    }

    //Tree 4 - initial class 4
    fDiam = 40;
    iSp = 1;
    iClass = 4;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(4, 4, iSp, iTp, fDiam);
      p_oTree->SetValue(p_oPop->GetIntDataCode("treeclass", iSp,  iTp), iClass);
    }

    //Tree 5 - initial class 5
    fDiam = 10;
    iSp = 2;
    iClass = 5;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(5, 5, iSp, iTp, fDiam);
      p_oTree->SetValue(p_oPop->GetIntDataCode("treeclass", iSp,  iTp), iClass);
    }

    //Tree 6 - initial class 6
    fDiam = 20;
    iSp = 2;
    iClass = 6;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(6, 6, iSp, iTp, fDiam);
      p_oTree->SetValue(p_oPop->GetIntDataCode("treeclass", iSp,  iTp), iClass);
    }

    //Tree 7 - initial class 1
    fDiam = 30;
    iSp = 3;
    iClass = 1;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(7, 7, iSp, iTp, fDiam);
      p_oTree->SetValue(p_oPop->GetIntDataCode("treeclass", iSp,  iTp), iClass);
    }

    //Tree 8 - initial class 2
    fDiam = 40;
    iSp = 3;
    iClass = 2;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(8, 8, iSp, iTp, fDiam);
      p_oTree->SetValue(p_oPop->GetIntDataCode("treeclass", iSp,  iTp), iClass);
    }

    //Tree 9 - initial class 3
    fDiam = 10;
    iSp = 3;
    iClass = 3;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(9, 9, iSp, iTp, fDiam);
      p_oTree->SetValue(p_oPop->GetIntDataCode("treeclass", iSp,  iTp), iClass);
    }

    //Tree 10 - initial class 4
    fDiam = 20;
    iSp = 3;
    iClass = 4;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(10, 10, iSp, iTp, fDiam);
      p_oTree->SetValue(p_oPop->GetIntDataCode("treeclass", iSp,  iTp), iClass);
    }

    //Tree 11 - initial class 5
    fDiam = 30;
    iSp = 4;
    iClass = 5;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(11, 11, iSp, iTp, fDiam);
      p_oTree->SetValue(p_oPop->GetIntDataCode("treeclass", iSp,  iTp), iClass);
    }

    //Tree 12 - initial class 6
    fDiam = 40;
    iSp = 4;
    iClass = 6;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(12, 12, iSp, iTp, fDiam);
      p_oTree->SetValue(p_oPop->GetIntDataCode("treeclass", iSp,  iTp), iClass);
    }

    //Now do the run
    p_oSimManager->RunSim(1);

    p_oTrees = p_oPop->Find("all");

    //Count the vigorous and sawlog of tree 1
    p_oTree = p_oTrees->NextTree();
    iNumVigorous = 0;
    iNumSawlog = 0;
    iNumTotal = 0;
    while (p_oTree) {
      iSp = p_oTree->GetSpecies();
      iTp = p_oTree->GetType();
      p_oTree->GetValue(p_oPop->GetXCode(iSp, iTp), &fX);

      if (fabs(fX - 1) < 0.1) {
        iNumTotal++;

        p_oTree->GetValue(p_oPop->GetBoolDataCode("vigorous", iSp, iTp), &bVigorous);
        if (bVigorous) iNumVigorous++;

        p_oTree->GetValue(p_oPop->GetBoolDataCode("sawlog", iSp, iTp), &bSawlog);
        if (bSawlog) iNumSawlog++;
      }
      p_oTree = p_oTrees->NextTree();
    }
    p_oTrees->StartOver();
    EXPECT_EQ(iNumTotal, 1000);
    EXPECT_LT(fabs(599 - iNumVigorous) / 599, 0.1);
    EXPECT_LT(fabs(713 - iNumSawlog) / 713, 0.1);

    //Count the vigorous and sawlog of tree 2
    p_oTree = p_oTrees->NextTree();
    iNumVigorous = 0;
    iNumSawlog = 0;
    iNumTotal = 0;
    while (p_oTree) {
      iSp = p_oTree->GetSpecies();
      iTp = p_oTree->GetType();
      p_oTree->GetValue(p_oPop->GetXCode(iSp, iTp), &fX);

      if (fabs(fX - 2) < 0.1) {
        iNumTotal++;

        p_oTree->GetValue(p_oPop->GetBoolDataCode("vigorous", iSp, iTp), &bVigorous);
        if (bVigorous) iNumVigorous++;

        p_oTree->GetValue(p_oPop->GetBoolDataCode("sawlog", iSp, iTp), &bSawlog);
        if (bSawlog) iNumSawlog++;
      }
      p_oTree = p_oTrees->NextTree();
    }
    p_oTrees->StartOver();
    EXPECT_EQ(iNumTotal, 1000);
    EXPECT_LT(fabs(119 - iNumVigorous) / 119, 0.1);
    EXPECT_LT(fabs(324 - iNumSawlog) / 324, 0.1);

    //Count the vigorous and sawlog of tree 3
    p_oTree = p_oTrees->NextTree();
    iNumVigorous = 0;
    iNumSawlog = 0;
    iNumTotal = 0;
    while (p_oTree) {
      iSp = p_oTree->GetSpecies();
      iTp = p_oTree->GetType();
      p_oTree->GetValue(p_oPop->GetXCode(iSp, iTp), &fX);

      if (fabs(fX - 3) < 0.1) {
        iNumTotal++;

        p_oTree->GetValue(p_oPop->GetBoolDataCode("vigorous", iSp, iTp), &bVigorous);
        if (bVigorous) iNumVigorous++;

        p_oTree->GetValue(p_oPop->GetBoolDataCode("sawlog", iSp, iTp), &bSawlog);
        if (bSawlog) iNumSawlog++;
      }
      p_oTree = p_oTrees->NextTree();
    }
    p_oTrees->StartOver();
    EXPECT_EQ(iNumTotal, 1000);
    EXPECT_LT(fabs(630 - iNumVigorous) / 630, 0.1);
    EXPECT_LT(fabs(104 - iNumSawlog) / 104, 0.1);

    //Count the vigorous and sawlog of tree 4
    p_oTree = p_oTrees->NextTree();
    iNumVigorous = 0;
    iNumSawlog = 0;
    iNumTotal = 0;
    while (p_oTree) {
      iSp = p_oTree->GetSpecies();
      iTp = p_oTree->GetType();
      p_oTree->GetValue(p_oPop->GetXCode(iSp, iTp), &fX);

      if (fabs(fX - 4) < 0.1) {
        iNumTotal++;

        p_oTree->GetValue(p_oPop->GetBoolDataCode("vigorous", iSp, iTp), &bVigorous);
        if (bVigorous) iNumVigorous++;

        p_oTree->GetValue(p_oPop->GetBoolDataCode("sawlog", iSp, iTp), &bSawlog);
        if (bSawlog) iNumSawlog++;
      }
      p_oTree = p_oTrees->NextTree();
    }
    p_oTrees->StartOver();
    EXPECT_EQ(iNumTotal, 1000);
    EXPECT_LT(fabs(802 - iNumVigorous) / 802, 0.1);
    EXPECT_LT(iNumSawlog, 50);

    //Count the vigorous and sawlog of tree 5
    p_oTree = p_oTrees->NextTree();
    iNumVigorous = 0;
    iNumSawlog = 0;
    iNumTotal = 0;
    while (p_oTree) {
      iSp = p_oTree->GetSpecies();
      iTp = p_oTree->GetType();
      p_oTree->GetValue(p_oPop->GetXCode(iSp, iTp), &fX);

      if (fabs(fX - 5) < 0.1) {
        iNumTotal++;

        p_oTree->GetValue(p_oPop->GetBoolDataCode("vigorous", iSp, iTp), &bVigorous);
        if (bVigorous) iNumVigorous++;

        p_oTree->GetValue(p_oPop->GetBoolDataCode("sawlog", iSp, iTp), &bSawlog);
        if (bSawlog) iNumSawlog++;
      }
      p_oTree = p_oTrees->NextTree();
    }
    p_oTrees->StartOver();
    EXPECT_EQ(iNumTotal, 1000);
    EXPECT_LT(fabs(713 - iNumVigorous) / 713, 0.1);
    EXPECT_EQ(iNumSawlog, 0);

    //Count the vigorous and sawlog of tree 6
    p_oTree = p_oTrees->NextTree();
    iNumVigorous = 0;
    iNumSawlog = 0;
    iNumTotal = 0;
    while (p_oTree) {
      iSp = p_oTree->GetSpecies();
      iTp = p_oTree->GetType();
      p_oTree->GetValue(p_oPop->GetXCode(iSp, iTp), &fX);

      if (fabs(fX - 6) < 0.1) {
        iNumTotal++;

        p_oTree->GetValue(p_oPop->GetBoolDataCode("vigorous", iSp, iTp), &bVigorous);
        if (bVigorous) iNumVigorous++;

        p_oTree->GetValue(p_oPop->GetBoolDataCode("sawlog", iSp, iTp), &bSawlog);
        if (bSawlog) iNumSawlog++;
      }
      p_oTree = p_oTrees->NextTree();
    }
    p_oTrees->StartOver();
    EXPECT_EQ(iNumTotal, 1000);
    EXPECT_LT(fabs(795 - iNumVigorous) / 795, 0.1);
    EXPECT_EQ(iNumSawlog, 0);

    //Count the vigorous and sawlog of tree 7
    p_oTree = p_oTrees->NextTree();
    iNumVigorous = 0;
    iNumSawlog = 0;
    iNumTotal = 0;
    while (p_oTree) {
      iSp = p_oTree->GetSpecies();
      iTp = p_oTree->GetType();
      p_oTree->GetValue(p_oPop->GetXCode(iSp, iTp), &fX);

      if (fabs(fX - 7) < 0.1) {
        iNumTotal++;

        p_oTree->GetValue(p_oPop->GetBoolDataCode("vigorous", iSp, iTp), &bVigorous);
        if (bVigorous) iNumVigorous++;

        p_oTree->GetValue(p_oPop->GetBoolDataCode("sawlog", iSp, iTp), &bSawlog);
        if (bSawlog) iNumSawlog++;
      }
      p_oTree = p_oTrees->NextTree();
    }
    p_oTrees->StartOver();
    EXPECT_EQ(iNumTotal, 1000);
    EXPECT_LT(fabs(932 - iNumVigorous) / 932, 0.1);
    EXPECT_LT(fabs(677 - iNumSawlog) / 677, 0.1);

    //Count the vigorous and sawlog of tree 8
    p_oTree = p_oTrees->NextTree();
    iNumVigorous = 0;
    iNumSawlog = 0;
    iNumTotal = 0;
    while (p_oTree) {
      iSp = p_oTree->GetSpecies();
      iTp = p_oTree->GetType();
      p_oTree->GetValue(p_oPop->GetXCode(iSp, iTp), &fX);

      if (fabs(fX - 8) < 0.1) {
        iNumTotal++;

        p_oTree->GetValue(p_oPop->GetBoolDataCode("vigorous", iSp, iTp), &bVigorous);
        if (bVigorous) iNumVigorous++;

        p_oTree->GetValue(p_oPop->GetBoolDataCode("sawlog", iSp, iTp), &bSawlog);
        if (bSawlog) iNumSawlog++;
      }
      p_oTree = p_oTrees->NextTree();
    }
    p_oTrees->StartOver();
    EXPECT_EQ(iNumTotal, 1000);
    EXPECT_LT(fabs(965 - iNumVigorous) / 965, 0.1);
    EXPECT_LT(fabs(661 - iNumSawlog) / 661, 0.1);

    //Count the vigorous and sawlog of tree 9
    p_oTree = p_oTrees->NextTree();
    iNumVigorous = 0;
    iNumSawlog = 0;
    iNumTotal = 0;
    while (p_oTree) {
      iSp = p_oTree->GetSpecies();
      iTp = p_oTree->GetType();
      p_oTree->GetValue(p_oPop->GetXCode(iSp, iTp), &fX);

      if (fabs(fX - 9) < 0.1) {
        iNumTotal++;

        p_oTree->GetValue(p_oPop->GetBoolDataCode("vigorous", iSp, iTp), &bVigorous);
        if (bVigorous) iNumVigorous++;

        p_oTree->GetValue(p_oPop->GetBoolDataCode("sawlog", iSp, iTp), &bSawlog);
        if (bSawlog) iNumSawlog++;
      }
      p_oTree = p_oTrees->NextTree();
    }
    p_oTrees->StartOver();
    EXPECT_EQ(iNumTotal, 1000);
    EXPECT_LT(fabs(766 - iNumVigorous) / 766, 0.1);
    EXPECT_LT(fabs(482 - iNumSawlog) / 482, 0.1);

    //Count the vigorous and sawlog of tree 10
    p_oTree = p_oTrees->NextTree();
    iNumVigorous = 0;
    iNumSawlog = 0;
    iNumTotal = 0;
    while (p_oTree) {
      iSp = p_oTree->GetSpecies();
      iTp = p_oTree->GetType();
      p_oTree->GetValue(p_oPop->GetXCode(iSp, iTp), &fX);

      if (fabs(fX - 10) < 0.1) {
        iNumTotal++;

        p_oTree->GetValue(p_oPop->GetBoolDataCode("vigorous", iSp, iTp), &bVigorous);
        if (bVigorous) iNumVigorous++;

        p_oTree->GetValue(p_oPop->GetBoolDataCode("sawlog", iSp, iTp), &bSawlog);
        if (bSawlog) iNumSawlog++;
      }
      p_oTree = p_oTrees->NextTree();
    }
    p_oTrees->StartOver();
    EXPECT_EQ(iNumTotal, 1000);
    EXPECT_LT(fabs(730 - iNumVigorous) / 730, 0.1);
    EXPECT_LT(fabs(474 - iNumSawlog) / 474, 0.1);

    //Count the vigorous and sawlog of tree 11
    p_oTree = p_oTrees->NextTree();
    iNumVigorous = 0;
    iNumSawlog = 0;
    iNumTotal = 0;
    while (p_oTree) {
      iSp = p_oTree->GetSpecies();
      iTp = p_oTree->GetType();
      p_oTree->GetValue(p_oPop->GetXCode(iSp, iTp), &fX);

      if (fabs(fX - 11) < 0.1) {
        iNumTotal++;

        p_oTree->GetValue(p_oPop->GetBoolDataCode("vigorous", iSp, iTp), &bVigorous);
        if (bVigorous) iNumVigorous++;

        p_oTree->GetValue(p_oPop->GetBoolDataCode("sawlog", iSp, iTp), &bSawlog);
        if (bSawlog) iNumSawlog++;
      }
      p_oTree = p_oTrees->NextTree();
    }
    p_oTrees->StartOver();
    EXPECT_EQ(iNumTotal, 1000);
    EXPECT_LT(fabs(986 - iNumVigorous) / 986, 0.1);
    EXPECT_EQ(iNumSawlog, 0);

    //Count the vigorous and sawlog of tree 12
    p_oTree = p_oTrees->NextTree();
    iNumVigorous = 0;
    iNumSawlog = 0;
    iNumTotal = 0;
    while (p_oTree) {
      iSp = p_oTree->GetSpecies();
      iTp = p_oTree->GetType();
      p_oTree->GetValue(p_oPop->GetXCode(iSp, iTp), &fX);

      if (fabs(fX - 12) < 0.1) {
        iNumTotal++;

        p_oTree->GetValue(p_oPop->GetBoolDataCode("vigorous", iSp, iTp), &bVigorous);
        if (bVigorous) iNumVigorous++;

        p_oTree->GetValue(p_oPop->GetBoolDataCode("sawlog", iSp, iTp), &bSawlog);
        if (bSawlog) iNumSawlog++;
      }
      p_oTree = p_oTrees->NextTree();
    }
    p_oTrees->StartOver();
    EXPECT_EQ(iNumTotal, 1000);
    EXPECT_LT(fabs(986 - iNumVigorous) / 986, 0.1);
    EXPECT_EQ(iNumSawlog, 0);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestNewAdultAssignment()
// Tests normal processing. WriteQualityVigorClassifierXMLFile1() does setup. This creates new adult
// trees by 1000s to test it indirectly.
////////////////////////////////////////////////////////////////////////////
TEST(QualityVigorClassifier, TestNewAdultAssignment) {

  clTreePopulation * p_oPop;
  clTreeSearch *p_oTrees;
  clTree *p_oTree;
  float fExpectedValue, fDiam, fX;
  int iNumSpecies = 5, i, iSp, iTp;
  bool bVigorous, bSawlog;

  int *p_iNumVigorous = new int[iNumSpecies],
      *p_iNumTotal = new int[iNumSpecies],
      *p_iNumSawlog = new int[iNumSpecies];

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {

    for (i = 0; i < iNumSpecies; i++) {
      p_iNumVigorous[i] = 0;
      p_iNumTotal[i] = 0;
      p_iNumSawlog[i] = 0;
    }

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteQualityVigorClassifierXMLFile1(false) );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create our new adult trees
    for (i = 0; i < 1000; i++) {
      fDiam = 11;

      fX = 2;
      p_oPop->CreateTree(fX, 10, 1, clTreePopulation::adult, fDiam);

      fX = 3;
      p_oPop->CreateTree(fX, 10, 2, clTreePopulation::adult, fDiam);

      fX = 4;
      p_oPop->CreateTree(fX, 10, 3, clTreePopulation::adult, fDiam);

      fX = 5;
      p_oPop->CreateTree(fX, 10, 4, clTreePopulation::adult, fDiam);
    }

    //Now do the run
    p_oSimManager->RunSim(1);

    //Count the vigorous and sawlog of each species
    p_oTrees = p_oPop->Find("all");
    p_oTree = p_oTrees->NextTree();

    while (p_oTree) {
      iSp = p_oTree->GetSpecies();
      iTp = p_oTree->GetType();

      p_oTree->GetValue(p_oPop->GetBoolDataCode("vigorous", iSp, iTp), &bVigorous);
      if (bVigorous) p_iNumVigorous[iSp]++;
      p_iNumTotal[iSp]++;

      p_oTree->GetValue(p_oPop->GetBoolDataCode("sawlog", iSp, iTp), &bSawlog);
      if (bSawlog) p_iNumSawlog[iSp]++;

      p_oTree = p_oTrees->NextTree();
    }

    //Test number of vigorous trees
    fExpectedValue = 100;
    EXPECT_LT(fabs(fExpectedValue - p_iNumVigorous[1])/fExpectedValue, 0.15);

    fExpectedValue = 250;
    EXPECT_LT(fabs(fExpectedValue - p_iNumVigorous[2])/fExpectedValue, 0.1);

    fExpectedValue = 500;
    EXPECT_LT(fabs(fExpectedValue - p_iNumVigorous[3])/fExpectedValue, 0.1);

    fExpectedValue = 740;
    EXPECT_LT(fabs(fExpectedValue - p_iNumVigorous[4])/fExpectedValue, 0.1);

    //Test number of sawlog trees
    fExpectedValue = 900;
    EXPECT_LT(fabs(fExpectedValue - p_iNumSawlog[1])/fExpectedValue, 0.1);

    fExpectedValue = 0;
    EXPECT_LT(fabs(fExpectedValue - p_iNumSawlog[2]), 0.00001);

    fExpectedValue = 300;
    EXPECT_LT(fabs(fExpectedValue - p_iNumSawlog[3])/fExpectedValue, 0.1);

    fExpectedValue = 0;
    EXPECT_LT(fabs(fExpectedValue - p_iNumSawlog[4]), 0.00001);

    //Verify total numbers
    fExpectedValue = 1000;
    EXPECT_LT(fabs(fExpectedValue - p_iNumTotal[1]), 0.00001);
    EXPECT_LT(fabs(fExpectedValue - p_iNumTotal[2]), 0.00001);
    EXPECT_LT(fabs(fExpectedValue - p_iNumTotal[3]), 0.00001);
    EXPECT_LT(fabs(fExpectedValue - p_iNumTotal[4]), 0.00001);

    //Delete our arrays
    delete[] p_iNumSawlog;
    delete[] p_iNumTotal;
    delete[] p_iNumVigorous;
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete[] p_iNumSawlog;
    delete[] p_iNumTotal;
    delete[] p_iNumVigorous;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestErrorProcessing()
////////////////////////////////////////////////////////////////////////////
TEST(QualityVigorClassifier, TestErrorProcessing) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try
  {
    p_oSimManager->ReadFile(WriteQualityVigorClassifierXMLErrorFile1());
    FAIL() << "TestQualityVigorClassifier error processing didn't catch error for WriteQualityVigorClassifierXMLErrorFile1.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clQualityVigorClassifier::RegisterTreeDataMembers") != 0)
    {
      FAIL() << "TestQualityVigorClassifier error processing caught wrong error for WriteQualityVigorClassifierXMLErrorFile1.";
    }
    ;
  }
  delete p_oSimManager;
}

////////////////////////////////////////////////////////////////////////////
// WriteQualityVigorClassifierXMLFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteQualityVigorClassifierXMLFile1(bool bAddTreeMap) {
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
       << "</tr_maxSeedlingHeight>";
  if (bAddTreeMap) {
    oOut << "<tr_treemapFile>" << WriteQualityVigorClassifierTextTreeMap1() << "</tr_treemapFile>";
  }
  oOut << "</trees>"
       << "<allometry>"
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
       << "<tr_stdMaxCrownRad>"
       << "<tr_smcrVal species=\"Species_1\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_2\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_3\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_4\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_5\">10</tr_smcrVal>"
       << "</tr_stdMaxCrownRad>"
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
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_2\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_3\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_4\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_5\">0.389</tr_sachVal>"
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
       << "<tr_sohdVal species=\"Species_2\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_3\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_4\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_5\">0.03418</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_2\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_3\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_4\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_5\">0.0299</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
       << "<tr_whatSeedlingHeightDiam>"
       << "<tr_wsehdVal species=\"Species_1\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_2\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_3\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_4\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_5\">0</tr_wsehdVal>"
       << "</tr_whatSeedlingHeightDiam>"
       << "<tr_whatSaplingHeightDiam>"
       << "<tr_wsahdVal species=\"Species_1\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_2\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_3\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_4\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_5\">0</tr_wsahdVal>"
       << "</tr_whatSaplingHeightDiam>"
       << "<tr_whatAdultHeightDiam>"
       << "<tr_wahdVal species=\"Species_1\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_2\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_3\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_4\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_5\">0</tr_wahdVal>"
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
       << "<behaviorName>QualityVigorClassifier</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_5\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>";

  oOut << "<QualityVigorClassifier1>"
       << "<ma_classifierVigBeta0>"
       << "<ma_cvb0Val species=\"Species_2\">0.1</ma_cvb0Val>"
       << "<ma_cvb0Val species=\"Species_3\">0</ma_cvb0Val>"
       << "<ma_cvb0Val species=\"Species_4\">0.3</ma_cvb0Val>"
       << "<ma_cvb0Val species=\"Species_5\">0.4</ma_cvb0Val>"
       << "</ma_classifierVigBeta0>"
       << "<ma_classifierVigBeta11>"
       << "<ma_cvb11Val species=\"Species_2\">0.2</ma_cvb11Val>"
       << "<ma_cvb11Val species=\"Species_3\">2.35</ma_cvb11Val>"
       << "<ma_cvb11Val species=\"Species_4\">0.1</ma_cvb11Val>"
       << "<ma_cvb11Val species=\"Species_5\">2.43</ma_cvb11Val>"
       << "</ma_classifierVigBeta11>"
       << "<ma_classifierVigBeta12>"
       << "<ma_cvb12Val species=\"Species_2\">-2.3</ma_cvb12Val>"
       << "<ma_cvb12Val species=\"Species_3\">1.12</ma_cvb12Val>"
       << "<ma_cvb12Val species=\"Species_4\">0.32</ma_cvb12Val>"
       << "<ma_cvb12Val species=\"Species_5\">1.3</ma_cvb12Val>"
       << "</ma_classifierVigBeta12>"
       << "<ma_classifierVigBeta13>"
       << "<ma_cvb13Val species=\"Species_2\">0.13</ma_cvb13Val>"
       << "<ma_cvb13Val species=\"Species_3\">1</ma_cvb13Val>"
       << "<ma_cvb13Val species=\"Species_4\">-0.2</ma_cvb13Val>"
       << "<ma_cvb13Val species=\"Species_5\">1</ma_cvb13Val>"
       << "</ma_classifierVigBeta13>"
       << "<ma_classifierVigBeta14>"
       << "<ma_cvb14Val species=\"Species_2\">0.9</ma_cvb14Val>"
       << "<ma_cvb14Val species=\"Species_3\">0</ma_cvb14Val>"
       << "<ma_cvb14Val species=\"Species_4\">-1</ma_cvb14Val>"
       << "<ma_cvb14Val species=\"Species_5\">0</ma_cvb14Val>"
       << "</ma_classifierVigBeta14>"
       << "<ma_classifierVigBeta15>"
       << "<ma_cvb15Val species=\"Species_2\">1</ma_cvb15Val>"
       << "<ma_cvb15Val species=\"Species_3\">0.25</ma_cvb15Val>"
       << "<ma_cvb15Val species=\"Species_4\">1</ma_cvb15Val>"
       << "<ma_cvb15Val species=\"Species_5\">-0.45</ma_cvb15Val>"
       << "</ma_classifierVigBeta15>"
       << "<ma_classifierVigBeta16>"
       << "<ma_cvb16Val species=\"Species_2\">1</ma_cvb16Val>"
       << "<ma_cvb16Val species=\"Species_3\">0.36</ma_cvb16Val>"
       << "<ma_cvb16Val species=\"Species_4\">0</ma_cvb16Val>"
       << "<ma_cvb16Val species=\"Species_5\">0.46</ma_cvb16Val>"
       << "</ma_classifierVigBeta16>"
       << "<ma_classifierVigBeta2>"
       << "<ma_cvb2Val species=\"Species_2\">0.01</ma_cvb2Val>"
       << "<ma_cvb2Val species=\"Species_3\">0.02</ma_cvb2Val>"
       << "<ma_cvb2Val species=\"Species_4\">0.04</ma_cvb2Val>"
       << "<ma_cvb2Val species=\"Species_5\">0.1</ma_cvb2Val>"
       << "</ma_classifierVigBeta2>"
       << "<ma_classifierVigBeta3>"
       << "<ma_cvb3Val species=\"Species_2\">0.001</ma_cvb3Val>"
       << "<ma_cvb3Val species=\"Species_3\">0.2</ma_cvb3Val>"
       << "<ma_cvb3Val species=\"Species_4\">0.3</ma_cvb3Val>"
       << "<ma_cvb3Val species=\"Species_5\">0.4</ma_cvb3Val>"
       << "</ma_classifierVigBeta3>"
       << "<ma_classifierQualBeta0>"
       << "<ma_cqb0Val species=\"Species_2\">0.25</ma_cqb0Val>"
       << "<ma_cqb0Val species=\"Species_3\">1.13</ma_cqb0Val>"
       << "<ma_cqb0Val species=\"Species_4\">0</ma_cqb0Val>"
       << "<ma_cqb0Val species=\"Species_5\">1.15</ma_cqb0Val>"
       << "</ma_classifierQualBeta0>"
       << "<ma_classifierQualBeta11>"
       << "<ma_cqb11Val species=\"Species_2\">0.36</ma_cqb11Val>"
       << "<ma_cqb11Val species=\"Species_3\">0</ma_cqb11Val>"
       << "<ma_cqb11Val species=\"Species_4\">0.4</ma_cqb11Val>"
       << "<ma_cqb11Val species=\"Species_5\">0</ma_cqb11Val>"
       << "</ma_classifierQualBeta11>"
       << "<ma_classifierQualBeta12>"
       << "<ma_cqb12Val species=\"Species_2\">0.02</ma_cqb12Val>"
       << "<ma_cqb12Val species=\"Species_3\">10</ma_cqb12Val>"
       << "<ma_cqb12Val species=\"Species_4\">0.3</ma_cqb12Val>"
       << "<ma_cqb12Val species=\"Species_5\">30</ma_cqb12Val>"
       << "</ma_classifierQualBeta12>"
       << "<ma_classifierQualBeta13>"
       << "<ma_cqb13Val species=\"Species_2\">0.2</ma_cqb13Val>"
       << "<ma_cqb13Val species=\"Species_3\">10</ma_cqb13Val>"
       << "<ma_cqb13Val species=\"Species_4\">-0.3</ma_cqb13Val>"
       << "<ma_cqb13Val species=\"Species_5\">30</ma_cqb13Val>"
       << "</ma_classifierQualBeta13>"
       << "<ma_classifierQualBeta14>"
       << "<ma_cqb14Val species=\"Species_2\">-0.2</ma_cqb14Val>"
       << "<ma_cqb14Val species=\"Species_3\">10</ma_cqb14Val>"
       << "<ma_cqb14Val species=\"Species_4\">-0.4</ma_cqb14Val>"
       << "<ma_cqb14Val species=\"Species_5\">30</ma_cqb14Val>"
       << "</ma_classifierQualBeta14>"
       << "<ma_classifierQualBeta2>"
       << "<ma_cqb2Val species=\"Species_2\">-0.2</ma_cqb2Val>"
       << "<ma_cqb2Val species=\"Species_3\">10</ma_cqb2Val>"
       << "<ma_cqb2Val species=\"Species_4\">0</ma_cqb2Val>"
       << "<ma_cqb2Val species=\"Species_5\">30</ma_cqb2Val>"
       << "</ma_classifierQualBeta2>"
       << "<ma_classifierQualBeta3>"
       << "<ma_cqb3Val species=\"Species_2\">1</ma_cqb3Val>"
       << "<ma_cqb3Val species=\"Species_3\">10</ma_cqb3Val>"
       << "<ma_cqb3Val species=\"Species_4\">0.1</ma_cqb3Val>"
       << "<ma_cqb3Val species=\"Species_5\">30</ma_cqb3Val>"
       << "</ma_classifierQualBeta3>"
       << "<ma_classifierNewAdultProbVigorous>"
       << "<ma_cnapvVal species=\"Species_2\">0.1</ma_cnapvVal>"
       << "<ma_cnapvVal species=\"Species_3\">0.25</ma_cnapvVal>"
       << "<ma_cnapvVal species=\"Species_4\">0.5</ma_cnapvVal>"
       << "<ma_cnapvVal species=\"Species_5\">0.74</ma_cnapvVal>"
       << "</ma_classifierNewAdultProbVigorous>"
       << "<ma_classifierNewAdultProbSawlog>"
       << "<ma_cnapsVal species=\"Species_2\">0.9</ma_cnapsVal>"
       << "<ma_cnapsVal species=\"Species_3\">0.25</ma_cnapsVal>"
       << "<ma_cnapsVal species=\"Species_4\">0.3</ma_cnapsVal>"
       << "<ma_cnapsVal species=\"Species_5\">0.74</ma_cnapsVal>"
       << "</ma_classifierNewAdultProbSawlog>"
       << "<ma_classifierDeciduous>"
       << "<ma_cdVal species=\"Species_2\">1</ma_cdVal>"
       << "<ma_cdVal species=\"Species_3\">0</ma_cdVal>"
       << "<ma_cdVal species=\"Species_4\">1</ma_cdVal>"
       << "<ma_cdVal species=\"Species_5\">0</ma_cdVal>"
       << "</ma_classifierDeciduous>"
       << "</QualityVigorClassifier1>"
       << "</paramFile>";

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteQualityVigorClassifierXMLFile2()
////////////////////////////////////////////////////////////////////////////
const char* WriteQualityVigorClassifierXMLFile2() {
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
       << "<tr_sizeClasses>"
       << "<tr_sizeClass sizeKey=\"s1.0\"/>"
       << "<tr_sizeClass sizeKey=\"s10.0\"/>"
       << "<tr_sizeClass sizeKey=\"s20.0\"/>"
       << "<tr_sizeClass sizeKey=\"s30.0\"/>"
       << "<tr_sizeClass sizeKey=\"s40.0\"/>"
       << "<tr_sizeClass sizeKey=\"s50.0\"/>"
       << "</tr_sizeClasses>"
       << "<tr_initialDensities>"
       << "<tr_idVals whatSpecies=\"Species_1\">"
       << "<tr_initialDensity sizeClass=\"s20.0\">250</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s30.0\">250</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s40.0\">250</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s50.0\">250</tr_initialDensity>"
       << "</tr_idVals>"
       << "<tr_idVals whatSpecies=\"Species_1\">"
       << "<tr_initialDensity sizeClass=\"s20.0\">250</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s30.0\">250</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s40.0\">250</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s50.0\">250</tr_initialDensity>"
       << "</tr_idVals>"
       << "<tr_idVals whatSpecies=\"Species_2\">"
       << "<tr_initialDensity sizeClass=\"s20.0\">250</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s30.0\">250</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s40.0\">250</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s50.0\">250</tr_initialDensity>"
       << "</tr_idVals>"
       << "<tr_idVals whatSpecies=\"Species_3\">"
       << "<tr_initialDensity sizeClass=\"s20.0\">250</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s30.0\">250</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s40.0\">250</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s50.0\">250</tr_initialDensity>"
       << "</tr_idVals>"
       << "<tr_idVals whatSpecies=\"Species_4\">"
       << "<tr_initialDensity sizeClass=\"s20.0\">250</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s30.0\">250</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s40.0\">250</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s50.0\">250</tr_initialDensity>"
       << "</tr_idVals>"
       << "<tr_idVals whatSpecies=\"Species_5\">"
       << "<tr_initialDensity sizeClass=\"s20.0\">250</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s30.0\">250</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s40.0\">250</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s50.0\">250</tr_initialDensity>"
       << "</tr_idVals>"
       << "</tr_initialDensities>";

  oOut << "</trees>"
       << "<allometry>"
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
       << "<tr_stdMaxCrownRad>"
       << "<tr_smcrVal species=\"Species_1\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_2\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_3\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_4\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_5\">10</tr_smcrVal>"
       << "</tr_stdMaxCrownRad>"
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
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_2\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_3\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_4\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_5\">0.389</tr_sachVal>"
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
       << "<tr_sohdVal species=\"Species_2\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_3\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_4\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_5\">0.03418</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_2\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_3\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_4\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_5\">0.0299</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
       << "<tr_whatSeedlingHeightDiam>"
       << "<tr_wsehdVal species=\"Species_1\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_2\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_3\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_4\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_5\">0</tr_wsehdVal>"
       << "</tr_whatSeedlingHeightDiam>"
       << "<tr_whatSaplingHeightDiam>"
       << "<tr_wsahdVal species=\"Species_1\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_2\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_3\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_4\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_5\">0</tr_wsahdVal>"
       << "</tr_whatSaplingHeightDiam>"
       << "<tr_whatAdultHeightDiam>"
       << "<tr_wahdVal species=\"Species_1\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_2\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_3\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_4\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_5\">0</tr_wahdVal>"
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
       << "<behaviorName>QualityVigorClassifier</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_5\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>";

  oOut << "<QualityVigorClassifier1>"
       << "<ma_classifierInitialConditions>"
       << "<ma_classifierSizeClass>"
       << "<ma_classifierBeginDBH>10</ma_classifierBeginDBH>"
       << "<ma_classifierEndDBH>20</ma_classifierEndDBH>"
       << "<ma_classifierProbVigorous>"
       << "<ma_cpvVal species=\"Species_2\">0.78</ma_cpvVal>"
       << "<ma_cpvVal species=\"Species_3\">0.88</ma_cpvVal>"
       << "<ma_cpvVal species=\"Species_4\">0</ma_cpvVal>"
       << "<ma_cpvVal species=\"Species_5\">0.61</ma_cpvVal>"
       << "</ma_classifierProbVigorous>"
       << "<ma_classifierProbSawlog>"
       << "<ma_cpsVal species=\"Species_2\">0.33</ma_cpsVal>"
       << "<ma_cpsVal species=\"Species_3\">0.64</ma_cpsVal>"
       << "<ma_cpsVal species=\"Species_4\">1</ma_cpsVal>"
       << "<ma_cpsVal species=\"Species_5\">0.55</ma_cpsVal>"
       << "</ma_classifierProbSawlog>"
       << "</ma_classifierSizeClass>"
       << "<ma_classifierSizeClass>"
       << "<ma_classifierBeginDBH>20</ma_classifierBeginDBH>"
       << "<ma_classifierEndDBH>30</ma_classifierEndDBH>"
       << "<ma_classifierProbVigorous>"
       << "<ma_cpvVal species=\"Species_2\">0.33</ma_cpvVal>"
       << "<ma_cpvVal species=\"Species_3\">0.81</ma_cpvVal>"
       << "<ma_cpvVal species=\"Species_4\">0.64</ma_cpvVal>"
       << "<ma_cpvVal species=\"Species_5\">0.32</ma_cpvVal>"
       << "</ma_classifierProbVigorous>"
       << "<ma_classifierProbSawlog>"
       << "<ma_cpsVal species=\"Species_2\">0.32</ma_cpsVal>"
       << "<ma_cpsVal species=\"Species_3\">0.69</ma_cpsVal>"
       << "<ma_cpsVal species=\"Species_4\">0.33</ma_cpsVal>"
       << "<ma_cpsVal species=\"Species_5\">0.58</ma_cpsVal>"
       << "</ma_classifierProbSawlog>"
       << "</ma_classifierSizeClass>"
       << "<ma_classifierSizeClass>"
       << "<ma_classifierBeginDBH>30</ma_classifierBeginDBH>"
       << "<ma_classifierEndDBH>40</ma_classifierEndDBH>"
       << "<ma_classifierProbVigorous>"
       << "<ma_cpvVal species=\"Species_2\">0.34</ma_cpvVal>"
       << "<ma_cpvVal species=\"Species_3\">0.57</ma_cpvVal>"
       << "<ma_cpvVal species=\"Species_4\">0.26</ma_cpvVal>"
       << "<ma_cpvVal species=\"Species_5\">0.46</ma_cpvVal>"
       << "</ma_classifierProbVigorous>"
       << "<ma_classifierProbSawlog>"
       << "<ma_cpsVal species=\"Species_2\">0.13</ma_cpsVal>"
       << "<ma_cpsVal species=\"Species_3\">0.36</ma_cpsVal>"
       << "<ma_cpsVal species=\"Species_4\">0.66</ma_cpsVal>"
       << "<ma_cpsVal species=\"Species_5\">0.45</ma_cpsVal>"
       << "</ma_classifierProbSawlog>"
       << "</ma_classifierSizeClass>"
       << "</ma_classifierInitialConditions>"
       << "<ma_classifierVigBeta0>"
       << "<ma_cvb0Val species=\"Species_2\">0.1</ma_cvb0Val>"
       << "<ma_cvb0Val species=\"Species_3\">0</ma_cvb0Val>"
       << "<ma_cvb0Val species=\"Species_4\">0.3</ma_cvb0Val>"
       << "<ma_cvb0Val species=\"Species_5\">0.4</ma_cvb0Val>"
       << "</ma_classifierVigBeta0>"
       << "<ma_classifierVigBeta11>"
       << "<ma_cvb11Val species=\"Species_2\">0.2</ma_cvb11Val>"
       << "<ma_cvb11Val species=\"Species_3\">2.35</ma_cvb11Val>"
       << "<ma_cvb11Val species=\"Species_4\">0.1</ma_cvb11Val>"
       << "<ma_cvb11Val species=\"Species_5\">2.43</ma_cvb11Val>"
       << "</ma_classifierVigBeta11>"
       << "<ma_classifierVigBeta12>"
       << "<ma_cvb12Val species=\"Species_2\">-2.3</ma_cvb12Val>"
       << "<ma_cvb12Val species=\"Species_3\">1.12</ma_cvb12Val>"
       << "<ma_cvb12Val species=\"Species_4\">0.32</ma_cvb12Val>"
       << "<ma_cvb12Val species=\"Species_5\">1.3</ma_cvb12Val>"
       << "</ma_classifierVigBeta12>"
       << "<ma_classifierVigBeta13>"
       << "<ma_cvb13Val species=\"Species_2\">0.13</ma_cvb13Val>"
       << "<ma_cvb13Val species=\"Species_3\">1</ma_cvb13Val>"
       << "<ma_cvb13Val species=\"Species_4\">-0.2</ma_cvb13Val>"
       << "<ma_cvb13Val species=\"Species_5\">1</ma_cvb13Val>"
       << "</ma_classifierVigBeta13>"
       << "<ma_classifierVigBeta14>"
       << "<ma_cvb14Val species=\"Species_2\">0.9</ma_cvb14Val>"
       << "<ma_cvb14Val species=\"Species_3\">0</ma_cvb14Val>"
       << "<ma_cvb14Val species=\"Species_4\">-1</ma_cvb14Val>"
       << "<ma_cvb14Val species=\"Species_5\">0</ma_cvb14Val>"
       << "</ma_classifierVigBeta14>"
       << "<ma_classifierVigBeta15>"
       << "<ma_cvb15Val species=\"Species_2\">1</ma_cvb15Val>"
       << "<ma_cvb15Val species=\"Species_3\">0.25</ma_cvb15Val>"
       << "<ma_cvb15Val species=\"Species_4\">1</ma_cvb15Val>"
       << "<ma_cvb15Val species=\"Species_5\">-0.45</ma_cvb15Val>"
       << "</ma_classifierVigBeta15>"
       << "<ma_classifierVigBeta16>"
       << "<ma_cvb16Val species=\"Species_2\">1</ma_cvb16Val>"
       << "<ma_cvb16Val species=\"Species_3\">0.36</ma_cvb16Val>"
       << "<ma_cvb16Val species=\"Species_4\">0</ma_cvb16Val>"
       << "<ma_cvb16Val species=\"Species_5\">0.46</ma_cvb16Val>"
       << "</ma_classifierVigBeta16>"
       << "<ma_classifierVigBeta2>"
       << "<ma_cvb2Val species=\"Species_2\">0.01</ma_cvb2Val>"
       << "<ma_cvb2Val species=\"Species_3\">0.02</ma_cvb2Val>"
       << "<ma_cvb2Val species=\"Species_4\">0.04</ma_cvb2Val>"
       << "<ma_cvb2Val species=\"Species_5\">0.1</ma_cvb2Val>"
       << "</ma_classifierVigBeta2>"
       << "<ma_classifierVigBeta3>"
       << "<ma_cvb3Val species=\"Species_2\">0.001</ma_cvb3Val>"
       << "<ma_cvb3Val species=\"Species_3\">0.2</ma_cvb3Val>"
       << "<ma_cvb3Val species=\"Species_4\">0.3</ma_cvb3Val>"
       << "<ma_cvb3Val species=\"Species_5\">0.4</ma_cvb3Val>"
       << "</ma_classifierVigBeta3>"
       << "<ma_classifierQualBeta0>"
       << "<ma_cqb0Val species=\"Species_2\">0.25</ma_cqb0Val>"
       << "<ma_cqb0Val species=\"Species_3\">1.13</ma_cqb0Val>"
       << "<ma_cqb0Val species=\"Species_4\">0</ma_cqb0Val>"
       << "<ma_cqb0Val species=\"Species_5\">1.15</ma_cqb0Val>"
       << "</ma_classifierQualBeta0>"
       << "<ma_classifierQualBeta11>"
       << "<ma_cqb11Val species=\"Species_2\">0.36</ma_cqb11Val>"
       << "<ma_cqb11Val species=\"Species_3\">0</ma_cqb11Val>"
       << "<ma_cqb11Val species=\"Species_4\">0.4</ma_cqb11Val>"
       << "<ma_cqb11Val species=\"Species_5\">0</ma_cqb11Val>"
       << "</ma_classifierQualBeta11>"
       << "<ma_classifierQualBeta12>"
       << "<ma_cqb12Val species=\"Species_2\">0.02</ma_cqb12Val>"
       << "<ma_cqb12Val species=\"Species_3\">10</ma_cqb12Val>"
       << "<ma_cqb12Val species=\"Species_4\">0.3</ma_cqb12Val>"
       << "<ma_cqb12Val species=\"Species_5\">30</ma_cqb12Val>"
       << "</ma_classifierQualBeta12>"
       << "<ma_classifierQualBeta13>"
       << "<ma_cqb13Val species=\"Species_2\">0.2</ma_cqb13Val>"
       << "<ma_cqb13Val species=\"Species_3\">10</ma_cqb13Val>"
       << "<ma_cqb13Val species=\"Species_4\">-0.3</ma_cqb13Val>"
       << "<ma_cqb13Val species=\"Species_5\">30</ma_cqb13Val>"
       << "</ma_classifierQualBeta13>"
       << "<ma_classifierQualBeta14>"
       << "<ma_cqb14Val species=\"Species_2\">-0.2</ma_cqb14Val>"
       << "<ma_cqb14Val species=\"Species_3\">10</ma_cqb14Val>"
       << "<ma_cqb14Val species=\"Species_4\">-0.4</ma_cqb14Val>"
       << "<ma_cqb14Val species=\"Species_5\">30</ma_cqb14Val>"
       << "</ma_classifierQualBeta14>"
       << "<ma_classifierQualBeta2>"
       << "<ma_cqb2Val species=\"Species_2\">-0.2</ma_cqb2Val>"
       << "<ma_cqb2Val species=\"Species_3\">10</ma_cqb2Val>"
       << "<ma_cqb2Val species=\"Species_4\">0</ma_cqb2Val>"
       << "<ma_cqb2Val species=\"Species_5\">30</ma_cqb2Val>"
       << "</ma_classifierQualBeta2>"
       << "<ma_classifierQualBeta3>"
       << "<ma_cqb3Val species=\"Species_2\">1</ma_cqb3Val>"
       << "<ma_cqb3Val species=\"Species_3\">10</ma_cqb3Val>"
       << "<ma_cqb3Val species=\"Species_4\">0.1</ma_cqb3Val>"
       << "<ma_cqb3Val species=\"Species_5\">30</ma_cqb3Val>"
       << "</ma_classifierQualBeta3>"
       << "<ma_classifierNewAdultProbVigorous>"
       << "<ma_cnapvVal species=\"Species_2\">0.1</ma_cnapvVal>"
       << "<ma_cnapvVal species=\"Species_3\">0.25</ma_cnapvVal>"
       << "<ma_cnapvVal species=\"Species_4\">0.5</ma_cnapvVal>"
       << "<ma_cnapvVal species=\"Species_5\">0.74</ma_cnapvVal>"
       << "</ma_classifierNewAdultProbVigorous>"
       << "<ma_classifierNewAdultProbSawlog>"
       << "<ma_cnapsVal species=\"Species_2\">0.9</ma_cnapsVal>"
       << "<ma_cnapsVal species=\"Species_3\">0.25</ma_cnapsVal>"
       << "<ma_cnapsVal species=\"Species_4\">0.3</ma_cnapsVal>"
       << "<ma_cnapsVal species=\"Species_5\">0.74</ma_cnapsVal>"
       << "</ma_classifierNewAdultProbSawlog>"
       << "<ma_classifierDeciduous>"
       << "<ma_cdVal species=\"Species_2\">1</ma_cdVal>"
       << "<ma_cdVal species=\"Species_3\">0</ma_cdVal>"
       << "<ma_cdVal species=\"Species_4\">1</ma_cdVal>"
       << "<ma_cdVal species=\"Species_5\">0</ma_cdVal>"
       << "</ma_classifierDeciduous>"
       << "</QualityVigorClassifier1>"
       << "</paramFile>";

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteQualityVigorClassifierXMLFile3()
////////////////////////////////////////////////////////////////////////////
const char* WriteQualityVigorClassifierXMLFile3() {
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
       << "<tr_sizeClasses>"
       << "<tr_sizeClass sizeKey=\"s1.0\"/>"
       << "<tr_sizeClass sizeKey=\"s10.0\"/>"
       << "<tr_sizeClass sizeKey=\"s20.0\"/>"
       << "<tr_sizeClass sizeKey=\"s30.0\"/>"
       << "<tr_sizeClass sizeKey=\"s40.0\"/>"
       << "<tr_sizeClass sizeKey=\"s50.0\"/>"
       << "</tr_sizeClasses>"
       << "<tr_initialDensities>"
       << "<tr_idVals whatSpecies=\"Species_1\">"
       << "<tr_initialDensity sizeClass=\"s20.0\">250</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s30.0\">250</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s40.0\">250</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s50.0\">250</tr_initialDensity>"
       << "</tr_idVals>"
       << "<tr_idVals whatSpecies=\"Species_1\">"
       << "<tr_initialDensity sizeClass=\"s20.0\">250</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s30.0\">250</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s40.0\">250</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s50.0\">250</tr_initialDensity>"
       << "</tr_idVals>"
       << "<tr_idVals whatSpecies=\"Species_2\">"
       << "<tr_initialDensity sizeClass=\"s20.0\">250</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s30.0\">250</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s40.0\">250</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s50.0\">250</tr_initialDensity>"
       << "</tr_idVals>"
       << "<tr_idVals whatSpecies=\"Species_3\">"
       << "<tr_initialDensity sizeClass=\"s20.0\">250</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s30.0\">250</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s40.0\">250</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s50.0\">250</tr_initialDensity>"
       << "</tr_idVals>"
       << "<tr_idVals whatSpecies=\"Species_4\">"
       << "<tr_initialDensity sizeClass=\"s20.0\">250</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s30.0\">250</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s40.0\">250</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s50.0\">250</tr_initialDensity>"
       << "</tr_idVals>"
       << "<tr_idVals whatSpecies=\"Species_5\">"
       << "<tr_initialDensity sizeClass=\"s20.0\">250</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s30.0\">250</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s40.0\">250</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s50.0\">250</tr_initialDensity>"
       << "</tr_idVals>"
       << "</tr_initialDensities>";
  oOut << "<tr_treemapFile>" << WriteQualityVigorClassifierTextTreeMap2() << "</tr_treemapFile>";

  oOut << "</trees>"
       << "<allometry>"
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
       << "<tr_stdMaxCrownRad>"
       << "<tr_smcrVal species=\"Species_1\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_2\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_3\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_4\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_5\">10</tr_smcrVal>"
       << "</tr_stdMaxCrownRad>"
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
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_2\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_3\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_4\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_5\">0.389</tr_sachVal>"
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
       << "<tr_sohdVal species=\"Species_2\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_3\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_4\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_5\">0.03418</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_2\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_3\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_4\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_5\">0.0299</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
       << "<tr_whatSeedlingHeightDiam>"
       << "<tr_wsehdVal species=\"Species_1\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_2\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_3\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_4\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_5\">0</tr_wsehdVal>"
       << "</tr_whatSeedlingHeightDiam>"
       << "<tr_whatSaplingHeightDiam>"
       << "<tr_wsahdVal species=\"Species_1\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_2\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_3\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_4\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_5\">0</tr_wsahdVal>"
       << "</tr_whatSaplingHeightDiam>"
       << "<tr_whatAdultHeightDiam>"
       << "<tr_wahdVal species=\"Species_1\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_2\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_3\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_4\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_5\">0</tr_wahdVal>"
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
       << "<behaviorName>QualityVigorClassifier</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_5\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>";

  oOut << "<QualityVigorClassifier1>"
       << "<ma_classifierInitialConditions>"
       << "<ma_classifierSizeClass>"
       << "<ma_classifierBeginDBH>10</ma_classifierBeginDBH>"
       << "<ma_classifierEndDBH>20</ma_classifierEndDBH>"
       << "<ma_classifierProbVigorous>"
       << "<ma_cpvVal species=\"Species_2\">0</ma_cpvVal>"
       << "<ma_cpvVal species=\"Species_3\">0</ma_cpvVal>"
       << "<ma_cpvVal species=\"Species_4\">0</ma_cpvVal>"
       << "<ma_cpvVal species=\"Species_5\">0</ma_cpvVal>"
       << "</ma_classifierProbVigorous>"
       << "<ma_classifierProbSawlog>"
       << "<ma_cpsVal species=\"Species_2\">0</ma_cpsVal>"
       << "<ma_cpsVal species=\"Species_3\">0</ma_cpsVal>"
       << "<ma_cpsVal species=\"Species_4\">0</ma_cpsVal>"
       << "<ma_cpsVal species=\"Species_5\">0</ma_cpsVal>"
       << "</ma_classifierProbSawlog>"
       << "</ma_classifierSizeClass>"
       << "<ma_classifierSizeClass>"
       << "<ma_classifierBeginDBH>20</ma_classifierBeginDBH>"
       << "<ma_classifierEndDBH>30</ma_classifierEndDBH>"
       << "<ma_classifierProbVigorous>"
       << "<ma_cpvVal species=\"Species_2\">0</ma_cpvVal>"
       << "<ma_cpvVal species=\"Species_3\">0</ma_cpvVal>"
       << "<ma_cpvVal species=\"Species_4\">0</ma_cpvVal>"
       << "<ma_cpvVal species=\"Species_5\">0</ma_cpvVal>"
       << "</ma_classifierProbVigorous>"
       << "<ma_classifierProbSawlog>"
       << "<ma_cpsVal species=\"Species_2\">0</ma_cpsVal>"
       << "<ma_cpsVal species=\"Species_3\">0</ma_cpsVal>"
       << "<ma_cpsVal species=\"Species_4\">0</ma_cpsVal>"
       << "<ma_cpsVal species=\"Species_5\">0</ma_cpsVal>"
       << "</ma_classifierProbSawlog>"
       << "</ma_classifierSizeClass>"
       << "<ma_classifierSizeClass>"
       << "<ma_classifierBeginDBH>30</ma_classifierBeginDBH>"
       << "<ma_classifierEndDBH>40</ma_classifierEndDBH>"
       << "<ma_classifierProbVigorous>"
       << "<ma_cpvVal species=\"Species_2\">0</ma_cpvVal>"
       << "<ma_cpvVal species=\"Species_3\">0</ma_cpvVal>"
       << "<ma_cpvVal species=\"Species_4\">0</ma_cpvVal>"
       << "<ma_cpvVal species=\"Species_5\">0</ma_cpvVal>"
       << "</ma_classifierProbVigorous>"
       << "<ma_classifierProbSawlog>"
       << "<ma_cpsVal species=\"Species_2\">0</ma_cpsVal>"
       << "<ma_cpsVal species=\"Species_3\">0</ma_cpsVal>"
       << "<ma_cpsVal species=\"Species_4\">0</ma_cpsVal>"
       << "<ma_cpsVal species=\"Species_5\">0</ma_cpsVal>"
       << "</ma_classifierProbSawlog>"
       << "</ma_classifierSizeClass>"
       << "</ma_classifierInitialConditions>"
       << "<ma_classifierVigBeta0>"
       << "<ma_cvb0Val species=\"Species_2\">0.1</ma_cvb0Val>"
       << "<ma_cvb0Val species=\"Species_3\">0</ma_cvb0Val>"
       << "<ma_cvb0Val species=\"Species_4\">0.3</ma_cvb0Val>"
       << "<ma_cvb0Val species=\"Species_5\">0.4</ma_cvb0Val>"
       << "</ma_classifierVigBeta0>"
       << "<ma_classifierVigBeta11>"
       << "<ma_cvb11Val species=\"Species_2\">0.2</ma_cvb11Val>"
       << "<ma_cvb11Val species=\"Species_3\">2.35</ma_cvb11Val>"
       << "<ma_cvb11Val species=\"Species_4\">0.1</ma_cvb11Val>"
       << "<ma_cvb11Val species=\"Species_5\">2.43</ma_cvb11Val>"
       << "</ma_classifierVigBeta11>"
       << "<ma_classifierVigBeta12>"
       << "<ma_cvb12Val species=\"Species_2\">-2.3</ma_cvb12Val>"
       << "<ma_cvb12Val species=\"Species_3\">1.12</ma_cvb12Val>"
       << "<ma_cvb12Val species=\"Species_4\">0.32</ma_cvb12Val>"
       << "<ma_cvb12Val species=\"Species_5\">1.3</ma_cvb12Val>"
       << "</ma_classifierVigBeta12>"
       << "<ma_classifierVigBeta13>"
       << "<ma_cvb13Val species=\"Species_2\">0.13</ma_cvb13Val>"
       << "<ma_cvb13Val species=\"Species_3\">1</ma_cvb13Val>"
       << "<ma_cvb13Val species=\"Species_4\">-0.2</ma_cvb13Val>"
       << "<ma_cvb13Val species=\"Species_5\">1</ma_cvb13Val>"
       << "</ma_classifierVigBeta13>"
       << "<ma_classifierVigBeta14>"
       << "<ma_cvb14Val species=\"Species_2\">0.9</ma_cvb14Val>"
       << "<ma_cvb14Val species=\"Species_3\">0</ma_cvb14Val>"
       << "<ma_cvb14Val species=\"Species_4\">-1</ma_cvb14Val>"
       << "<ma_cvb14Val species=\"Species_5\">0</ma_cvb14Val>"
       << "</ma_classifierVigBeta14>"
       << "<ma_classifierVigBeta15>"
       << "<ma_cvb15Val species=\"Species_2\">1</ma_cvb15Val>"
       << "<ma_cvb15Val species=\"Species_3\">0.25</ma_cvb15Val>"
       << "<ma_cvb15Val species=\"Species_4\">1</ma_cvb15Val>"
       << "<ma_cvb15Val species=\"Species_5\">-0.45</ma_cvb15Val>"
       << "</ma_classifierVigBeta15>"
       << "<ma_classifierVigBeta16>"
       << "<ma_cvb16Val species=\"Species_2\">1</ma_cvb16Val>"
       << "<ma_cvb16Val species=\"Species_3\">0.36</ma_cvb16Val>"
       << "<ma_cvb16Val species=\"Species_4\">0</ma_cvb16Val>"
       << "<ma_cvb16Val species=\"Species_5\">0.46</ma_cvb16Val>"
       << "</ma_classifierVigBeta16>"
       << "<ma_classifierVigBeta2>"
       << "<ma_cvb2Val species=\"Species_2\">0.01</ma_cvb2Val>"
       << "<ma_cvb2Val species=\"Species_3\">0.02</ma_cvb2Val>"
       << "<ma_cvb2Val species=\"Species_4\">0.04</ma_cvb2Val>"
       << "<ma_cvb2Val species=\"Species_5\">0.1</ma_cvb2Val>"
       << "</ma_classifierVigBeta2>"
       << "<ma_classifierVigBeta3>"
       << "<ma_cvb3Val species=\"Species_2\">0.001</ma_cvb3Val>"
       << "<ma_cvb3Val species=\"Species_3\">0.2</ma_cvb3Val>"
       << "<ma_cvb3Val species=\"Species_4\">0.3</ma_cvb3Val>"
       << "<ma_cvb3Val species=\"Species_5\">0.4</ma_cvb3Val>"
       << "</ma_classifierVigBeta3>"
       << "<ma_classifierQualBeta0>"
       << "<ma_cqb0Val species=\"Species_2\">0.25</ma_cqb0Val>"
       << "<ma_cqb0Val species=\"Species_3\">1.13</ma_cqb0Val>"
       << "<ma_cqb0Val species=\"Species_4\">0</ma_cqb0Val>"
       << "<ma_cqb0Val species=\"Species_5\">1.15</ma_cqb0Val>"
       << "</ma_classifierQualBeta0>"
       << "<ma_classifierQualBeta11>"
       << "<ma_cqb11Val species=\"Species_2\">0.36</ma_cqb11Val>"
       << "<ma_cqb11Val species=\"Species_3\">0</ma_cqb11Val>"
       << "<ma_cqb11Val species=\"Species_4\">0.4</ma_cqb11Val>"
       << "<ma_cqb11Val species=\"Species_5\">0</ma_cqb11Val>"
       << "</ma_classifierQualBeta11>"
       << "<ma_classifierQualBeta12>"
       << "<ma_cqb12Val species=\"Species_2\">0.02</ma_cqb12Val>"
       << "<ma_cqb12Val species=\"Species_3\">10</ma_cqb12Val>"
       << "<ma_cqb12Val species=\"Species_4\">0.3</ma_cqb12Val>"
       << "<ma_cqb12Val species=\"Species_5\">30</ma_cqb12Val>"
       << "</ma_classifierQualBeta12>"
       << "<ma_classifierQualBeta13>"
       << "<ma_cqb13Val species=\"Species_2\">0.2</ma_cqb13Val>"
       << "<ma_cqb13Val species=\"Species_3\">10</ma_cqb13Val>"
       << "<ma_cqb13Val species=\"Species_4\">-0.3</ma_cqb13Val>"
       << "<ma_cqb13Val species=\"Species_5\">30</ma_cqb13Val>"
       << "</ma_classifierQualBeta13>"
       << "<ma_classifierQualBeta14>"
       << "<ma_cqb14Val species=\"Species_2\">-0.2</ma_cqb14Val>"
       << "<ma_cqb14Val species=\"Species_3\">10</ma_cqb14Val>"
       << "<ma_cqb14Val species=\"Species_4\">-0.4</ma_cqb14Val>"
       << "<ma_cqb14Val species=\"Species_5\">30</ma_cqb14Val>"
       << "</ma_classifierQualBeta14>"
       << "<ma_classifierQualBeta2>"
       << "<ma_cqb2Val species=\"Species_2\">-0.2</ma_cqb2Val>"
       << "<ma_cqb2Val species=\"Species_3\">10</ma_cqb2Val>"
       << "<ma_cqb2Val species=\"Species_4\">0</ma_cqb2Val>"
       << "<ma_cqb2Val species=\"Species_5\">30</ma_cqb2Val>"
       << "</ma_classifierQualBeta2>"
       << "<ma_classifierQualBeta3>"
       << "<ma_cqb3Val species=\"Species_2\">1</ma_cqb3Val>"
       << "<ma_cqb3Val species=\"Species_3\">10</ma_cqb3Val>"
       << "<ma_cqb3Val species=\"Species_4\">0.1</ma_cqb3Val>"
       << "<ma_cqb3Val species=\"Species_5\">30</ma_cqb3Val>"
       << "</ma_classifierQualBeta3>"
       << "<ma_classifierNewAdultProbVigorous>"
       << "<ma_cnapvVal species=\"Species_2\">0</ma_cnapvVal>"
       << "<ma_cnapvVal species=\"Species_3\">0</ma_cnapvVal>"
       << "<ma_cnapvVal species=\"Species_4\">0</ma_cnapvVal>"
       << "<ma_cnapvVal species=\"Species_5\">0</ma_cnapvVal>"
       << "</ma_classifierNewAdultProbVigorous>"
       << "<ma_classifierNewAdultProbSawlog>"
       << "<ma_cnapsVal species=\"Species_2\">0</ma_cnapsVal>"
       << "<ma_cnapsVal species=\"Species_3\">0</ma_cnapsVal>"
       << "<ma_cnapsVal species=\"Species_4\">0</ma_cnapsVal>"
       << "<ma_cnapsVal species=\"Species_5\">0</ma_cnapsVal>"
       << "</ma_classifierNewAdultProbSawlog>"
       << "<ma_classifierDeciduous>"
       << "<ma_cdVal species=\"Species_2\">1</ma_cdVal>"
       << "<ma_cdVal species=\"Species_3\">0</ma_cdVal>"
       << "<ma_cdVal species=\"Species_4\">1</ma_cdVal>"
       << "<ma_cdVal species=\"Species_5\">0</ma_cdVal>"
       << "</ma_classifierDeciduous>"
       << "</QualityVigorClassifier1>"
       << "</paramFile>";

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteQualityVigorClassifierTextTreeMap1()
////////////////////////////////////////////////////////////////////////////
const char* WriteQualityVigorClassifierTextTreeMap1() {
  using namespace std;
  const char *cFileString = "TreeMap.txt";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "X\tY\tSpecies\tType\tDiam\tHeight\tvigorous\tsawlog\ttreeclass\n";
  oOut << "1\t1\tSpecies_2\tAdult\t10\t0\t1\t1\t10\n";
  oOut << "2\t2\tSpecies_2\tAdult\t20\t1\t1\t0\t10\n";
  oOut << "3\t3\tSpecies_2\tAdult\t30\t2\t0\t1\t10\n";
  oOut << "4\t4\tSpecies_2\tAdult\t20\t3\t0\t1\t10\n";
  oOut << "5\t5\tSpecies_2\tAdult\t40\t4\t0\t0\t10\n";
  oOut << "6\t6\tSpecies_3\tAdult\t10\t5\t1\t0\t10\n";
  oOut << "7\t7\tSpecies_3\tAdult\t20\t6\t0\t0\t10\n";
  oOut << "8\t8\tSpecies_4\tAdult\t30\t7\t1\t1\t10\n";
  oOut << "9\t9\tSpecies_4\tAdult\t40\t8\t1\t0\t10\n";
  oOut << "10\t10\tSpecies_4\tAdult\t10\t9\t0\t1\t10\n";
  oOut << "11\t11\tSpecies_4\tAdult\t20\t10\t0\t0\t10\n";
  oOut << "12\t12\tSpecies_5\tAdult\t30\t11\t1\t0\t10\n";
  oOut << "13\t13\tSpecies_5\tAdult\t40\t12\t0\t0\t10\n";

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteQualityVigorClassifierTextTreeMap2()
////////////////////////////////////////////////////////////////////////////
const char* WriteQualityVigorClassifierTextTreeMap2() {
  using namespace std;
  const char *cFileString = "TreeMap.txt";
  int i;

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "X\tY\tSpecies\tType\tDiam\tHeight\ttreeclass\n";
  for (i = 0; i < 10; i++) {
    oOut << "1\t1\tSpecies_2\tAdult\t12\t0\t1\n";
    oOut << "1\t1\tSpecies_2\tAdult\t22\t0\t1\n";
    oOut << "1\t1\tSpecies_2\tAdult\t32\t0\t1\n";
    oOut << "1\t1\tSpecies_2\tAdult\t42\t0\t1\n";
  }
  for (i = 0; i < 10; i++) {
    oOut << "6\t6\tSpecies_3\tAdult\t13\t0\t5\n";
    oOut << "6\t6\tSpecies_3\tAdult\t24\t0\t5\n";
    oOut << "6\t6\tSpecies_3\tAdult\t35\t0\t5\n";
    oOut << "6\t6\tSpecies_3\tAdult\t46\t0\t5\n";
  }
  for (i = 0; i < 10; i++) {
    oOut << "8\t8\tSpecies_4\tAdult\t13\t0\t1\n";
    oOut << "8\t8\tSpecies_4\tAdult\t23\t0\t1\n";
    oOut << "8\t8\tSpecies_4\tAdult\t33\t0\t1\n";
    oOut << "8\t8\tSpecies_4\tAdult\t43\t0\t1\n";
  }
  for (i = 0; i < 10; i++) {
    oOut << "12\t12\tSpecies_5\tAdult\t17\t0\t5\n";
    oOut << "12\t12\tSpecies_5\tAdult\t27\t0\t5\n";
    oOut << "12\t12\tSpecies_5\tAdult\t37\t0\t5\n";
    oOut << "12\t12\tSpecies_5\tAdult\t47\t0\t5\n";
  }


  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteQualityVigorClassifierXMLErrorFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteQualityVigorClassifierXMLErrorFile1() {
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
       << "<tr_chVal species=\"Species_2\">39.48</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_2\">0.0549</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_stdMaxCrownRad>"
       << "<tr_smcrVal species=\"Species_1\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_2\">10</tr_smcrVal>"
       << "</tr_stdMaxCrownRad>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">0.8008</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_2\">0.389</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_2\">0.03418</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_2\">0.0299</tr_soahVal>"
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
       << "<behaviorName>QualityVigorClassifier</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "</behavior>"
       << "</behaviorList>";

  oOut << "<QualityVigorClassifier1>"
       << "<ma_classifierVigBeta0>"
       << "<ma_cvb0Val species=\"Species_2\">0.1</ma_cvb0Val>"
       << "<ma_cvb0Val species=\"Species_1\">0</ma_cvb0Val>"
       << "</ma_classifierVigBeta0>"
       << "<ma_classifierVigBeta11>"
       << "<ma_cvb11Val species=\"Species_2\">0.2</ma_cvb11Val>"
       << "<ma_cvb11Val species=\"Species_1\">2.35</ma_cvb11Val>"
       << "</ma_classifierVigBeta11>"
       << "<ma_classifierVigBeta12>"
       << "<ma_cvb12Val species=\"Species_2\">-2.3</ma_cvb12Val>"
       << "<ma_cvb12Val species=\"Species_1\">1.12</ma_cvb12Val>"
       << "</ma_classifierVigBeta12>"
       << "<ma_classifierVigBeta13>"
       << "<ma_cvb13Val species=\"Species_2\">0.13</ma_cvb13Val>"
       << "<ma_cvb13Val species=\"Species_1\">1</ma_cvb13Val>"
       << "</ma_classifierVigBeta13>"
       << "<ma_classifierVigBeta14>"
       << "<ma_cvb14Val species=\"Species_2\">0.9</ma_cvb14Val>"
       << "<ma_cvb14Val species=\"Species_1\">0</ma_cvb14Val>"
       << "</ma_classifierVigBeta14>"
       << "<ma_classifierVigBeta15>"
       << "<ma_cvb15Val species=\"Species_2\">1</ma_cvb15Val>"
       << "<ma_cvb15Val species=\"Species_1\">0.25</ma_cvb15Val>"
       << "</ma_classifierVigBeta15>"
       << "<ma_classifierVigBeta16>"
       << "<ma_cvb16Val species=\"Species_2\">1</ma_cvb16Val>"
       << "<ma_cvb16Val species=\"Species_1\">0.36</ma_cvb16Val>"
       << "</ma_classifierVigBeta16>"
       << "<ma_classifierVigBeta2>"
       << "<ma_cvb2Val species=\"Species_2\">0.01</ma_cvb2Val>"
       << "<ma_cvb2Val species=\"Species_1\">0.02</ma_cvb2Val>"
       << "</ma_classifierVigBeta2>"
       << "<ma_classifierVigBeta3>"
       << "<ma_cvb3Val species=\"Species_2\">0.001</ma_cvb3Val>"
       << "<ma_cvb3Val species=\"Species_1\">0.2</ma_cvb3Val>"
       << "</ma_classifierVigBeta3>"
       << "<ma_classifierQualBeta0>"
       << "<ma_cqb0Val species=\"Species_2\">0.25</ma_cqb0Val>"
       << "<ma_cqb0Val species=\"Species_1\">1.13</ma_cqb0Val>"
       << "</ma_classifierQualBeta0>"
       << "<ma_classifierQualBeta11>"
       << "<ma_cqb11Val species=\"Species_2\">0.36</ma_cqb11Val>"
       << "<ma_cqb11Val species=\"Species_1\">0</ma_cqb11Val>"
       << "</ma_classifierQualBeta11>"
       << "<ma_classifierQualBeta12>"
       << "<ma_cqb12Val species=\"Species_2\">0.02</ma_cqb12Val>"
       << "<ma_cqb12Val species=\"Species_1\">10</ma_cqb12Val>"
       << "</ma_classifierQualBeta12>"
       << "<ma_classifierQualBeta13>"
       << "<ma_cqb13Val species=\"Species_2\">0.2</ma_cqb13Val>"
       << "<ma_cqb13Val species=\"Species_1\">10</ma_cqb13Val>"
       << "</ma_classifierQualBeta13>"
       << "<ma_classifierQualBeta14>"
       << "<ma_cqb14Val species=\"Species_2\">-0.2</ma_cqb14Val>"
       << "<ma_cqb14Val species=\"Species_1\">10</ma_cqb14Val>"
       << "</ma_classifierQualBeta14>"
       << "<ma_classifierQualBeta2>"
       << "<ma_cqb2Val species=\"Species_2\">-0.2</ma_cqb2Val>"
       << "<ma_cqb2Val species=\"Species_1\">10</ma_cqb2Val>"
       << "</ma_classifierQualBeta2>"
       << "<ma_classifierQualBeta3>"
       << "<ma_cqb3Val species=\"Species_2\">1</ma_cqb3Val>"
       << "<ma_cqb3Val species=\"Species_1\">10</ma_cqb3Val>"
       << "</ma_classifierQualBeta3>"
       << "<ma_classifierNewAdultProbVigorous>"
       << "<ma_cnapvVal species=\"Species_2\">0.1</ma_cnapvVal>"
       << "<ma_cnapvVal species=\"Species_1\">0.25</ma_cnapvVal>"
       << "</ma_classifierNewAdultProbVigorous>"
       << "<ma_classifierNewAdultProbSawlog>"
       << "<ma_cnapsVal species=\"Species_2\">0.9</ma_cnapsVal>"
       << "<ma_cnapsVal species=\"Species_1\">0.25</ma_cnapsVal>"
       << "</ma_classifierNewAdultProbSawlog>"
       << "<ma_classifierDeciduous>"
       << "<ma_cdVal species=\"Species_2\">1</ma_cdVal>"
       << "<ma_cdVal species=\"Species_1\">0</ma_cdVal>"
       << "</ma_classifierDeciduous>"
       << "</QualityVigorClassifier1>"
       << "</paramFile>";

  return cFileString;

}
