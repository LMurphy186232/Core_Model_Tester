//---------------------------------------------------------------------------
// TestAllometry.cpp
//---------------------------------------------------------------------------
#include "TestAllometry.h"
#include <gtest/gtest.h>
#include "TreePopulation.h"
#include "SimManager.h"
#include "Allometry.h"
#include <fstream>
#include <iostream>
#include <math.h>


/////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun1()
// Verifies that allometry functions calculate correctly.  This run uses
// WriteXMLFile1 for setup.  This file contains 6 species, with a mix of
// allometric functions throughout the life history stages.  This tests each
// allometric function for each life history stage for each species.  (No
// actual trees are used; we just call the functions directly.)
/////////////////////////////////////////////////////////////////////////////

///////////////////////////////
// Test CalcAdultHeight
///////////////////////////////
TEST(Allometry, CalcAdultHeight)
{
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clAllometry *p_oAllom;
    float fDBH, fHeight, fExpected;
    int iSp;

    //Set up our run and get the tree popluation pointer
    p_oSimManager->ReadFile( WriteAllometryXMLFile1() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
    p_oAllom = p_oPop->GetAllometryObject();

    fDBH = 32.4;
    iSp = 0;  fExpected = 25.00762914;
    fHeight = p_oAllom->CalcAdultHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 1;  fExpected = 22.04817374;
    fHeight = p_oAllom->CalcAdultHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 2;  fExpected = 26.38284845;
    fHeight = p_oAllom->CalcAdultHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 3;  fExpected = 31.104;
    fHeight = p_oAllom->CalcAdultHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 4;  fExpected = 15.41705714;
    fHeight = p_oAllom->CalcAdultHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 5;  fExpected = 41.22;
    fHeight = p_oAllom->CalcAdultHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);


    fDBH = 0;
    iSp = 0;  fExpected = 1.35;
    fHeight = p_oAllom->CalcAdultHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 1;  fExpected = 1.35;
    fHeight = p_oAllom->CalcAdultHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 2;  fExpected = 1.35;
    fHeight = p_oAllom->CalcAdultHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 3;  fExpected = 0.001;
    fHeight = p_oAllom->CalcAdultHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected), 0.01);

    iSp = 4;  fExpected = 0.001;
    fHeight = p_oAllom->CalcAdultHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 5;  fExpected = 0.001;
    fHeight = p_oAllom->CalcAdultHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);


    fDBH = -12;
    iSp = 0;  fExpected = 0.001;
    fHeight = p_oAllom->CalcAdultHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 1;  fExpected = 0.001;
    fHeight = p_oAllom->CalcAdultHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 2;  fExpected = 0.001;
    fHeight = p_oAllom->CalcAdultHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 3;  fExpected = 0.001;
    fHeight = p_oAllom->CalcAdultHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 4;  fExpected = 0.001;
    fHeight = p_oAllom->CalcAdultHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 5;  fExpected = 0.001;
    fHeight = p_oAllom->CalcAdultHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);


    fDBH = 3.45E+12;
    iSp = 0;  fExpected = 39.48;
    fHeight = p_oAllom->CalcAdultHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 1;  fExpected = 39.54;
    fHeight = p_oAllom->CalcAdultHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 2;  fExpected = 45;
    fHeight = p_oAllom->CalcAdultHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 3;  fExpected = 39.48;
    fHeight = p_oAllom->CalcAdultHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 4;  fExpected = 39.54;
    fHeight = p_oAllom->CalcAdultHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 5;  fExpected = 45;
    fHeight = p_oAllom->CalcAdultHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);


    fDBH = 4.30E-28;
    iSp = 0;  fExpected = 1.35;
    fHeight = p_oAllom->CalcAdultHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 1;  fExpected = 1.35;
    fHeight = p_oAllom->CalcAdultHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 2;  fExpected = 1.35;
    fHeight = p_oAllom->CalcAdultHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 3;  fExpected = 0.001;
    fHeight = p_oAllom->CalcAdultHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 4;  fExpected = 0.001;
    fHeight = p_oAllom->CalcAdultHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 5;  fExpected = 0.001;
    fHeight = p_oAllom->CalcAdultHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

///////////////////////////////
// Test CalcAdultDbh
///////////////////////////////
TEST(Allometry, CalcAdultDbh) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clAllometry *p_oAllom;
    float fDBH, fHeight, fExpected;
    int iSp;

    //Set up our run and get the tree popluation pointer
    p_oSimManager->ReadFile( WriteAllometryXMLFile1() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
    p_oAllom = p_oPop->GetAllometryObject();

    fHeight = 14.789;
    iSp = 0;  fExpected = 14.53386519;
    fDBH = p_oAllom->CalcAdultDbh(fHeight, iSp);
    EXPECT_LT(fabs(fExpected - fDBH)/fExpected, 0.01);

    iSp = 1;  fExpected = 17.99617465;
    fDBH = p_oAllom->CalcAdultDbh(fHeight, iSp);
    EXPECT_LT(fabs(fExpected - fDBH)/fExpected, 0.01);

    iSp = 2;  fExpected = 13.99228843;
    fDBH = p_oAllom->CalcAdultDbh(fHeight, iSp);
    EXPECT_LT(fabs(fExpected - fDBH)/fExpected, 0.01);

    iSp = 3;  fExpected = 15.40520833;
    fDBH = p_oAllom->CalcAdultDbh(fHeight, iSp);
    EXPECT_LT(fabs(fExpected - fDBH)/fExpected, 0.01);

    iSp = 4;  fExpected = 31.08108;
    fDBH = p_oAllom->CalcAdultDbh(fHeight, iSp);
    EXPECT_LT(fabs(fExpected - fDBH)/fExpected, 0.01);

    iSp = 5;  fExpected = 12.06846154;
    fDBH = p_oAllom->CalcAdultDbh(fHeight, iSp);
    EXPECT_LT(fabs(fExpected - fDBH)/fExpected, 0.01);


    fHeight = 0;
    iSp = 0;  fExpected = MINDIAM; // fExpected = -1.163640157;
    fDBH = p_oAllom->CalcAdultDbh(fHeight, iSp);
    EXPECT_LT(fabs(fExpected - fDBH)/fExpected, 0.01);

    iSp = 1;  fExpected = MINDIAM; // fExpected = -1.441457116;
    fDBH = p_oAllom->CalcAdultDbh(fHeight, iSp);
    EXPECT_LT(fabs(fExpected - fDBH)/fExpected, 0.01);

    iSp = 2;  fExpected = MINDIAM; // fExpected = -1.158144771;
    fDBH = p_oAllom->CalcAdultDbh(fHeight, iSp);
    EXPECT_LT(fabs(fExpected - fDBH)/fExpected, 0.01);

    iSp = 3;  fExpected = MINDIAM; // fExpected = 0;
    fDBH = p_oAllom->CalcAdultDbh(fHeight, iSp);
    EXPECT_EQ(fExpected, fDBH);

    iSp = 4;  fExpected = 0.02418;
    fDBH = p_oAllom->CalcAdultDbh(fHeight, iSp);
    EXPECT_LT(fabs(fExpected - fDBH)/fExpected, 0.01);

    iSp = 5;  fExpected = 0.692307692;
    fDBH = p_oAllom->CalcAdultDbh(fHeight, iSp);
    EXPECT_LT(fabs(fExpected - fDBH)/fExpected, 0.01);


    fHeight = -35.778;
    iSp = 0;  fExpected = MINDIAM; // fExpected = -22.7398273;
    fDBH = p_oAllom->CalcAdultDbh(fHeight, iSp);
    EXPECT_LT(fabs(fExpected - fDBH)/fExpected, 0.01);

    iSp = 1;  fExpected = MINDIAM; // fExpected = -28.18030908;
    fDBH = p_oAllom->CalcAdultDbh(fHeight, iSp);
    EXPECT_LT(fabs(fExpected - fDBH)/fExpected, 0.01);

    iSp = 2;  fExpected = MINDIAM; // fExpected = -23.40309388;
    fDBH = p_oAllom->CalcAdultDbh(fHeight, iSp);
    EXPECT_LT(fabs(fExpected - fDBH)/fExpected, 0.01);

    iSp = 3;  fExpected = MINDIAM; // fExpected = -37.26875;
    fDBH = p_oAllom->CalcAdultDbh(fHeight, iSp);
    EXPECT_LT(fabs(fExpected - fDBH)/fExpected, 0.01);

    iSp = 4;  fExpected = MINDIAM; // fExpected = -75.10962;
    fDBH = p_oAllom->CalcAdultDbh(fHeight, iSp);
    EXPECT_LT(fabs(fExpected - fDBH)/fExpected, 0.01);

    iSp = 5;  fExpected = MINDIAM; // fExpected = -26.82923077;
    fDBH = p_oAllom->CalcAdultDbh(fHeight, iSp);
    EXPECT_LT(fabs(fExpected - fDBH)/fExpected, 0.01);


    fHeight = 4.30E-28;
    iSp = 0;  fExpected = MINDIAM; // fExpected = -1.163640157;
    fDBH = p_oAllom->CalcAdultDbh(fHeight, iSp);
    EXPECT_LT(fabs(fExpected - fDBH)/fExpected, 0.01);

    iSp = 1;  fExpected = MINDIAM; // fExpected = -1.441457116;
    fDBH = p_oAllom->CalcAdultDbh(fHeight, iSp);
    EXPECT_LT(fabs(fExpected - fDBH)/fExpected, 0.01);

    iSp = 2;  fExpected = MINDIAM; // fExpected = -1.158144771;
    fDBH = p_oAllom->CalcAdultDbh(fHeight, iSp);
    EXPECT_LT(fabs(fExpected - fDBH)/fExpected, 0.01);

    iSp = 3;  fExpected = MINDIAM; // fExpected = 4.47917E-28;
    fDBH = p_oAllom->CalcAdultDbh(fHeight, iSp);
    EXPECT_LT(fabs(fExpected - fDBH)/fExpected, 0.01);

    iSp = 4;  fExpected = 0.02418;
    fDBH = p_oAllom->CalcAdultDbh(fHeight, iSp);
    EXPECT_LT(fabs(fExpected - fDBH)/fExpected, 0.01);

    iSp = 5;  fExpected = 0.692307692;
    fDBH = p_oAllom->CalcAdultDbh(fHeight, iSp);
    EXPECT_LT(fabs(fExpected - fDBH)/fExpected, 0.01);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

///////////////////////////////
// Test CalcAdultCrownRadius
///////////////////////////////
TEST(Allometry, CalcAdultCrownRadius) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clAllometry *p_oAllom;
    clTree *p_oTree;
    float fDBH, fCrownRad, fExpected;
    int iSp;

    //Set up our run and get the tree popluation pointer
    p_oSimManager->ReadFile( WriteAllometryXMLFile1() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
    p_oAllom = p_oPop->GetAllometryObject();

    EXPECT_EQ(50, p_oAllom->GetMaxCrownRadius());

    fDBH = 45.633;
    iSp = 0;

    // Make sure crown radius data member is properly initialized
    p_oTree = p_oPop->CreateTree(1,1,iSp,clTreePopulation::adult,fDBH);
    p_oTree->GetValue(p_oPop->GetCrownRadiusCode(p_oTree->GetSpecies(), p_oTree->GetType()),&fCrownRad);
    EXPECT_LT(fCrownRad, 0);
    fExpected = 4.640207347;
    fCrownRad = p_oAllom->CalcAdultCrownRadius(p_oTree);
    EXPECT_LT(fabs(fExpected - fCrownRad)/fExpected, 0.01);

    iSp = 1;  fExpected = 8.103324011;
    p_oTree = p_oPop->CreateTree(1,1,iSp,clTreePopulation::adult,fDBH);
    fCrownRad = p_oAllom->CalcAdultCrownRadius(p_oTree);
    EXPECT_LT(fabs(fExpected - fCrownRad)/fExpected, 0.01);

    iSp = 2;  fExpected = 16.16825759;
    p_oTree = p_oPop->CreateTree(1,1,iSp,clTreePopulation::adult,fDBH);
    fCrownRad = p_oAllom->CalcAdultCrownRadius(p_oTree);
    EXPECT_LT(fabs(fExpected - fCrownRad)/fExpected, 0.01);

    iSp = 3;  fExpected = 10.31610291;
    p_oTree = p_oPop->CreateTree(1,1,iSp,clTreePopulation::adult,fDBH);
    fCrownRad = p_oAllom->CalcAdultCrownRadius(p_oTree);
    EXPECT_LT(fabs(fExpected - fCrownRad)/fExpected, 0.01);

    iSp = 4;  fExpected = 2.8018662;
    p_oTree = p_oPop->CreateTree(1,1,iSp,clTreePopulation::adult,fDBH);
    fCrownRad = p_oAllom->CalcAdultCrownRadius(p_oTree);
    EXPECT_LT(fabs(fExpected - fCrownRad)/fExpected, 0.01);

    iSp = 5;  fExpected = 9.898099411;
    p_oTree = p_oPop->CreateTree(1,1,iSp,clTreePopulation::adult,fDBH);
    fCrownRad = p_oAllom->CalcAdultCrownRadius(p_oTree);
    EXPECT_LT(fabs(fExpected - fCrownRad)/fExpected, 0.01);




    fDBH = 200;
    iSp = 0;  fExpected = 10;
    p_oTree = p_oPop->CreateTree(1,1,iSp,clTreePopulation::adult,fDBH);
    fCrownRad = p_oAllom->CalcAdultCrownRadius(p_oTree);
    EXPECT_LT(fabs(fExpected - fCrownRad)/fExpected, 0.01);

    iSp = 1;  fExpected = 8.3;
    p_oTree = p_oPop->CreateTree(1,1,iSp,clTreePopulation::adult,fDBH);
    fCrownRad = p_oAllom->CalcAdultCrownRadius(p_oTree);
    EXPECT_LT(fabs(fExpected - fCrownRad)/fExpected, 0.01);

    iSp = 2;  fExpected = 30;
    p_oTree = p_oPop->CreateTree(1,1,iSp,clTreePopulation::adult,fDBH);
    fCrownRad = p_oAllom->CalcAdultCrownRadius(p_oTree);
    EXPECT_LT(fabs(fExpected - fCrownRad)/fExpected, 0.01);

    iSp = 3;  fExpected = 10.5;
    p_oTree = p_oPop->CreateTree(1,1,iSp,clTreePopulation::adult,fDBH);
    fCrownRad = p_oAllom->CalcAdultCrownRadius(p_oTree);
    EXPECT_LT(fabs(fExpected - fCrownRad)/fExpected, 0.01);

    iSp = 4;  fExpected = 12.28;
    p_oTree = p_oPop->CreateTree(1,1,iSp,clTreePopulation::adult,fDBH);
    fCrownRad = p_oAllom->CalcAdultCrownRadius(p_oTree);
    EXPECT_LT(fabs(fExpected - fCrownRad)/fExpected, 0.01);

    iSp = 5;  fExpected = 9.9;
    p_oTree = p_oPop->CreateTree(1,1,iSp,clTreePopulation::adult,fDBH);
    fCrownRad = p_oAllom->CalcAdultCrownRadius(p_oTree);
    EXPECT_LT(fabs(fExpected - fCrownRad)/fExpected, 0.01);



  /*
   * Can't do this - it wouldn't be an adult
   * fDBH = 4.30E-28;
  iSp = 0;  fExpected = 1.28734E-26;
  fCrownRad = p_oAllom->CalcAdultCrownRadius(fHeight, fDBH, iSp);
  EXPECT_LT(fabs(fExpected - fCrownRad)/fExpected, 0.01);

  iSp = 1;  fExpected = 0.3;
  fCrownRad = p_oAllom->CalcAdultCrownRadius(fHeight, fDBH, iSp);
  EXPECT_LT(fabs(fExpected - fCrownRad)/fExpected, 0.01);

  iSp = 2;  fExpected = 1.90665E-32;
  fCrownRad = p_oAllom->CalcAdultCrownRadius(fHeight, fDBH, iSp);
  EXPECT_LT(fabs(fExpected - fCrownRad)/fExpected, 0.01);

  iSp = 3;  fExpected = 0.5;
  fCrownRad = p_oAllom->CalcAdultCrownRadius(fHeight, fDBH, iSp);
  EXPECT_LT(fabs(fExpected - fCrownRad)/fExpected, 0.01);

  iSp = 4;  fExpected = 2.6402E-29;
  fCrownRad = p_oAllom->CalcAdultCrownRadius(fHeight, fDBH, iSp);
  EXPECT_LT(fabs(fExpected - fCrownRad)/fExpected, 0.01);

  iSp = 5;  fExpected = 0.7;
  fCrownRad = p_oAllom->CalcAdultCrownRadius(fHeight, fDBH, iSp);
  EXPECT_LT(fabs(fExpected - fCrownRad)/fExpected, 0.01);*/

    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

///////////////////////////////
// Test CalcAdultCrownDepth
///////////////////////////////
TEST(Allometry, CalcAdultCrownDepth) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clAllometry *p_oAllom;
    clTreeSearch *p_oAllTrees;
    clTree *p_oTree;
    float fDBH, fHeight, fCrownDepth, fCrownRad, fExpected;
    int iSp;

    //Set up our run and get the tree popluation pointer
    p_oSimManager->ReadFile( WriteAllometryXMLFile1() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
    p_oAllom = p_oPop->GetAllometryObject();

    fHeight = 25.633; fDBH = 20;
    iSp = 0;  fExpected = 9.971237;
    p_oTree = p_oPop->CreateTree(1,1,iSp,clTreePopulation::adult,fDBH);
    // Make sure crown radius data member is properly initialized
    p_oTree->GetValue(p_oPop->GetCrownDepthCode(p_oTree->GetSpecies(), p_oTree->GetType()),&fCrownDepth);
    EXPECT_LT(fCrownDepth, 0);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()),fHeight,false);
    fCrownDepth = p_oAllom->CalcAdultCrownDepth(p_oTree);
    EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

    iSp = 1;  fExpected = 25.633;
    p_oTree = p_oPop->CreateTree(1,1,iSp,clTreePopulation::adult,fDBH);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()),fHeight,false);
    fCrownDepth = p_oAllom->CalcAdultCrownDepth(p_oTree);
    EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

    iSp = 2;  fExpected = 6.300839409;
    p_oTree = p_oPop->CreateTree(1,1,iSp,clTreePopulation::adult,fDBH);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()),fHeight,false);
    fCrownDepth = p_oAllom->CalcAdultCrownDepth(p_oTree);
    EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

    iSp = 3;  fExpected = 11.73552899;
    p_oTree = p_oPop->CreateTree(1,1,iSp,clTreePopulation::adult,fDBH);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()),fHeight,false);
    fCrownDepth = p_oAllom->CalcAdultCrownDepth(p_oTree);
    EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

    iSp = 4;  fExpected = 13.50561862;
    p_oTree = p_oPop->CreateTree(1,1,iSp,clTreePopulation::adult,fDBH);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()),fHeight,false);
    fCrownDepth = p_oAllom->CalcAdultCrownDepth(p_oTree);
    EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

    iSp = 5;  fExpected = 6.300839409;
    p_oTree = p_oPop->CreateTree(1,1,iSp,clTreePopulation::adult,fDBH);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()),fHeight,false);
    fCrownDepth = p_oAllom->CalcAdultCrownDepth(p_oTree);
    EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

    // Make sure that crown radius and depth parameters are reset each timestep
    p_oSimManager->RunSim(1);
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    EXPECT_TRUE(p_oTree != NULL);
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetCrownDepthCode(p_oTree->GetSpecies(),p_oTree->GetType()), &fCrownDepth);
      p_oTree->GetValue(p_oPop->GetCrownRadiusCode(p_oTree->GetSpecies(),p_oTree->GetType()), &fCrownRad);
      EXPECT_LT(fCrownDepth, 0);
      EXPECT_LT(fCrownRad, 0);
      p_oTree = p_oAllTrees->NextTree();
    }

    /*fHeight = 0;
  iSp = 0;  fExpected = 0;
  fCrownDepth = p_oAllom->CalcAdultCrownDepth(fHeight, fDBH, iSp);
  EXPECT_EQ(fExpected, fCrownDepth);

  iSp = 1;  fExpected = 0;
  fCrownDepth = p_oAllom->CalcAdultCrownDepth(fHeight, fDBH, iSp);
  EXPECT_EQ(fExpected, fCrownDepth);

  iSp = 2;  fExpected = 0;
  fCrownDepth = p_oAllom->CalcAdultCrownDepth(fHeight, fDBH, iSp);
  EXPECT_EQ(fExpected, fCrownDepth);

  iSp = 3;  fExpected = 0;
  fCrownDepth = p_oAllom->CalcAdultCrownDepth(fHeight, fDBH, iSp);
  EXPECT_EQ(fExpected, fCrownDepth);

  iSp = 4;  fExpected = 0;
  fCrownDepth = p_oAllom->CalcAdultCrownDepth(fHeight, fDBH, iSp);
  EXPECT_EQ(fExpected, fCrownDepth);

  iSp = 5;  fExpected = 0;
  fCrownDepth = p_oAllom->CalcAdultCrownDepth(fHeight, fDBH, iSp);
  EXPECT_EQ(fExpected, fCrownDepth);



  fHeight = 3.45E+12;
  iSp = 0;  fExpected = 1.34205E+12;
  fCrownDepth = p_oAllom->CalcAdultCrownDepth(fHeight, fDBH, iSp);
  EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

  iSp = 1;  fExpected = 60.6;
  fCrownDepth = p_oAllom->CalcAdultCrownDepth(fHeight, fDBH, iSp);
  EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

  iSp = 2;  fExpected = 65390717488.0;
  fCrownDepth = p_oAllom->CalcAdultCrownDepth(fHeight, fDBH, iSp);
  EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

  iSp = 3;  fExpected = 13.4;
  fCrownDepth = p_oAllom->CalcAdultCrownDepth(fHeight, fDBH, iSp);
  EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

  iSp = 4;  fExpected = 14.3;
  fCrownDepth = p_oAllom->CalcAdultCrownDepth(fHeight, fDBH, iSp);
  EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

  iSp = 5;  fExpected = 65390717488.0;
  fCrownDepth = p_oAllom->CalcAdultCrownDepth(fHeight, fDBH, iSp);
  EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);



  fHeight = 4.30E-28;
  iSp = 0;  fExpected = 1.6727E-28;
  fCrownDepth = p_oAllom->CalcAdultCrownDepth(fHeight, fDBH, iSp);
  EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

  iSp = 1;  fExpected = 4.3E-28;
  fCrownDepth = p_oAllom->CalcAdultCrownDepth(fHeight, fDBH, iSp);
  EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

  iSp = 2;  fExpected = 4.3E-28;
  fCrownDepth = p_oAllom->CalcAdultCrownDepth(fHeight, fDBH, iSp);
  EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

  iSp = 3;  fExpected = 4.3E-28;
  fCrownDepth = p_oAllom->CalcAdultCrownDepth(fHeight, fDBH, iSp);
  EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

  iSp = 4;  fExpected = 4.3E-28;
  fCrownDepth = p_oAllom->CalcAdultCrownDepth(fHeight, fDBH, iSp);
  EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

  iSp = 5;  fExpected = 4.3E-28;
  fCrownDepth = p_oAllom->CalcAdultCrownDepth(fHeight, fDBH, iSp);
  EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);
     */
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

///////////////////////////////
// Test CalcSaplingHeight
///////////////////////////////
TEST(Allometry, CalcSaplingHeight) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clAllometry *p_oAllom;
    float fDBH, fHeight, fExpected;
    int iSp;

    //Set up our run and get the tree popluation pointer
    p_oSimManager->ReadFile( WriteAllometryXMLFile1() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
    p_oAllom = p_oPop->GetAllometryObject();

    fDBH = 5.7332;
    iSp = 0;  fExpected = 7.35679411;
    fHeight = p_oAllom->CalcSaplingHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 1;  fExpected = 4.0207344;
    fHeight = p_oAllom->CalcSaplingHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 2;  fExpected = 5.982;
    fHeight = p_oAllom->CalcSaplingHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 3;  fExpected = 7.15455718;
    fHeight = p_oAllom->CalcSaplingHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 4;  fExpected = 3.3148;
    fHeight = p_oAllom->CalcSaplingHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 5;  fExpected = 7.459508556;
    fHeight = p_oAllom->CalcSaplingHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);


    fDBH = 0;
    iSp = 0;  fExpected = 1.35;
    fHeight = p_oAllom->CalcSaplingHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 1;  fExpected = 1.2;
    fHeight = p_oAllom->CalcSaplingHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 2;  fExpected = 0.77;
    fHeight = p_oAllom->CalcSaplingHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 3;  fExpected = 0.001;
    fHeight = p_oAllom->CalcSaplingHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected), 0.01);

    iSp = 4;  fExpected = 0.001;
    fHeight = p_oAllom->CalcSaplingHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 5;  fExpected = 1.35;
    fHeight = p_oAllom->CalcSaplingHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);



    fDBH = -8.907;
    iSp = 0;  fExpected = 0.001;
    fHeight = p_oAllom->CalcSaplingHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 1;  fExpected = 0.001;
    fHeight = p_oAllom->CalcSaplingHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 2;  fExpected = 0.001;
    fHeight = p_oAllom->CalcSaplingHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 3;  fExpected = 0.001;
    fHeight = p_oAllom->CalcSaplingHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 4;  fExpected = 0.001;
    fHeight = p_oAllom->CalcSaplingHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 5;  fExpected = 0.001;
    fHeight = p_oAllom->CalcSaplingHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);


    fDBH = 3.45E+12;
    iSp = 0;  fExpected = 39.48;
    fHeight = p_oAllom->CalcSaplingHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 1;  fExpected = 39.54;
    fHeight = p_oAllom->CalcSaplingHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 2;  fExpected = 45;
    fHeight = p_oAllom->CalcSaplingHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 3;  fExpected = 39.48;
    fHeight = p_oAllom->CalcSaplingHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 4;  fExpected = 39.54;
    fHeight = p_oAllom->CalcSaplingHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 5;  fExpected = 45;
    fHeight = p_oAllom->CalcSaplingHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);


    fDBH = 4.30E-28;
    iSp = 0;  fExpected = 1.35;
    fHeight = p_oAllom->CalcSaplingHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 1;  fExpected = 1.2;
    fHeight = p_oAllom->CalcSaplingHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 2;  fExpected = 0.77;
    fHeight = p_oAllom->CalcSaplingHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 3;  fExpected = 0.001;
    fHeight = p_oAllom->CalcSaplingHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 4;  fExpected = -0.507333333;
    fHeight = p_oAllom->CalcSaplingHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 5;  fExpected = 1.35;
    fHeight = p_oAllom->CalcSaplingHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

///////////////////////////////
// Test CalcSaplingDbh
///////////////////////////////
TEST(Allometry, CalcSaplingDbh) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clAllometry *p_oAllom;
    float fDBH, fHeight, fExpected;
    int iSp;

    //Set up our run and get the tree popluation pointer
    p_oSimManager->ReadFile( WriteAllometryXMLFile1() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
    p_oAllom = p_oPop->GetAllometryObject();

    fHeight = 4.56223;
    iSp = 0;  fExpected = 2.943327933;
    fDBH = p_oAllom->CalcSaplingDbh(fHeight, iSp);
    EXPECT_LT(fabs(fExpected - fDBH)/fExpected, 0.01);

    iSp = 1;  fExpected = 6.833800813;
    fDBH = p_oAllom->CalcSaplingDbh(fHeight, iSp);
    EXPECT_LT(fabs(fExpected - fDBH)/fExpected, 0.01);

    iSp = 2;  fExpected = 4.171453;
    fDBH = p_oAllom->CalcSaplingDbh(fHeight, iSp);
    EXPECT_LT(fabs(fExpected - fDBH)/fExpected, 0.01);

    iSp = 3;  fExpected = 3.282049957;
    fDBH = p_oAllom->CalcSaplingDbh(fHeight, iSp);
    EXPECT_LT(fabs(fExpected - fDBH)/fExpected, 0.01);

    iSp = 4;  fExpected = 7.604345;
    fDBH = p_oAllom->CalcSaplingDbh(fHeight, iSp);
    EXPECT_LT(fabs(fExpected - fDBH)/fExpected, 0.01);

    iSp = 5;  fExpected = 2.906427113;
    fDBH = p_oAllom->CalcSaplingDbh(fHeight, iSp);
    EXPECT_LT(fabs(fExpected - fDBH)/fExpected, 0.01);


    fHeight = 0;
    iSp = 0; fExpected = MINDIAM; // fExpected = -1.163640157;
    fDBH = p_oAllom->CalcSaplingDbh(fHeight, iSp);
    EXPECT_LT(fabs(fExpected - fDBH)/fExpected, 0.01);

    iSp = 1;  fExpected = MINDIAM; // fExpected = -2.43902439;
    fDBH = p_oAllom->CalcSaplingDbh(fHeight, iSp);
    EXPECT_LT(fabs(fExpected - fDBH)/fExpected, 0.01);

    iSp = 2;  fExpected = MINDIAM; // fExpected = -0.847;
    fDBH = p_oAllom->CalcSaplingDbh(fHeight, iSp);
    EXPECT_LT(fabs(fExpected - fDBH)/fExpected, 0.01);

    iSp = 3;  fExpected = 0.001;
    fDBH = p_oAllom->CalcSaplingDbh(fHeight, iSp);
    EXPECT_LT(fabs(fExpected), 0.01);

    iSp = 4;  fExpected = 0.761;
    fDBH = p_oAllom->CalcSaplingDbh(fHeight, iSp);
    EXPECT_LT(fabs(fExpected - fDBH)/fExpected, 0.01);

    iSp = 5;  fExpected = MINDIAM; // fExpected = -1.158144771;
    fDBH = p_oAllom->CalcSaplingDbh(fHeight, iSp);
    EXPECT_LT(fabs(fExpected - fDBH)/fExpected, 0.01);


    fHeight = -2.4123;
    iSp = 0;  fExpected = MINDIAM; // fExpected = -3.147179441;
    fDBH = p_oAllom->CalcSaplingDbh(fHeight, iSp);
    EXPECT_LT(fabs(fExpected - fDBH)/fExpected, 0.01);

    iSp = 1;  fExpected = MINDIAM; // fExpected = -7.342073171;
    fDBH = p_oAllom->CalcSaplingDbh(fHeight, iSp);
    EXPECT_LT(fabs(fExpected - fDBH)/fExpected, 0.01);

    iSp = 2;  fExpected = MINDIAM; // fExpected = -3.50053;
    fDBH = p_oAllom->CalcSaplingDbh(fHeight, iSp);
    EXPECT_LT(fabs(fExpected - fDBH)/fExpected, 0.01);

    iSp = 3;  fExpected = MINDIAM; // fExpected = -43.93989071;
    fDBH = p_oAllom->CalcSaplingDbh(fHeight, iSp);
    EXPECT_LT(fabs(fExpected - fDBH)/fExpected, 0.01);

    iSp = 4;  fExpected = MINDIAM; // fExpected = -2.85745;
    fDBH = p_oAllom->CalcSaplingDbh(fHeight, iSp);
    EXPECT_LT(fabs(fExpected - fDBH)/fExpected, 0.01);

    iSp = 5;  fExpected = MINDIAM; // fExpected = -3.143665643;
    fDBH = p_oAllom->CalcSaplingDbh(fHeight, iSp);
    EXPECT_LT(fabs(fExpected - fDBH)/fExpected, 0.01);


    fHeight = 4.30E-28;
    iSp = 0;  fExpected = MINDIAM; // -1.163640157;
    fDBH = p_oAllom->CalcSaplingDbh(fHeight, iSp);
    EXPECT_LT(fabs(fExpected - fDBH)/fExpected, 0.01);

    iSp = 1;  fExpected = MINDIAM; // fExpected = -2.43902439;
    fDBH = p_oAllom->CalcSaplingDbh(fHeight, iSp);
    EXPECT_LT(fabs(fExpected - fDBH)/fExpected, 0.01);

    iSp = 2;  fExpected = MINDIAM; // fExpected = -0.847;
    fDBH = p_oAllom->CalcSaplingDbh(fHeight, iSp);
    EXPECT_LT(fabs(fExpected - fDBH)/fExpected, 0.01);

    iSp = 3;  fExpected = 0.001;
    fDBH = p_oAllom->CalcSaplingDbh(fHeight, iSp);
    EXPECT_LT(fabs(fExpected - fDBH)/fExpected, 0.01);

    iSp = 4;  fExpected = 0.761;
    fDBH = p_oAllom->CalcSaplingDbh(fHeight, iSp);
    EXPECT_LT(fabs(fExpected - fDBH)/fExpected, 0.01);

    iSp = 5;  fExpected = MINDIAM; // fExpected = -1.158144771;
    fDBH = p_oAllom->CalcSaplingDbh(fHeight, iSp);
    EXPECT_LT(fabs(fExpected - fDBH)/fExpected, 0.01);

    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

///////////////////////////////
// Test CalcSaplingCrownRadius
///////////////////////////////
TEST(Allometry, CalcSaplingCrownRadius) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clAllometry *p_oAllom;
    clTree *p_oTree;
    float fDBH, fCrownRad, fExpected;
    int iSp;

    //Set up our run and get the tree popluation pointer
    p_oSimManager->ReadFile( WriteAllometryXMLFile1() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
    p_oAllom = p_oPop->GetAllometryObject();

    fDBH = 7.0375;
    iSp = 0;  fExpected = 0.862706034;
    // Make sure crown radius data member is properly initialized
    p_oTree = p_oPop->CreateTree(1,1,iSp,clTreePopulation::sapling,fDBH);
    p_oTree->GetValue(p_oPop->GetCrownRadiusCode(p_oTree->GetSpecies(), p_oTree->GetType()),&fCrownRad);
    EXPECT_LT(fCrownRad, 0);
    fCrownRad = p_oAllom->CalcSaplingCrownRadius(p_oTree);
    EXPECT_LT(fabs(fExpected - fCrownRad)/fExpected, 0.01);

    iSp = 1;  fExpected = 0.4321025;
    p_oTree = p_oPop->CreateTree(1,1,iSp,clTreePopulation::sapling,fDBH);
    fCrownRad = p_oAllom->CalcSaplingCrownRadius(p_oTree);
    EXPECT_LT(fabs(fExpected - fCrownRad)/fExpected, 0.01);

    iSp = 2;  fExpected = 1.760070726;
    p_oTree = p_oPop->CreateTree(1,1,iSp,clTreePopulation::sapling,fDBH);
    fCrownRad = p_oAllom->CalcSaplingCrownRadius(p_oTree);
    EXPECT_LT(fabs(fExpected - fCrownRad)/fExpected, 0.01);

    iSp = 3;  fExpected = 2.270952665;
    p_oTree = p_oPop->CreateTree(1,1,iSp,clTreePopulation::sapling,fDBH);
    fCrownRad = p_oAllom->CalcSaplingCrownRadius(p_oTree);
    EXPECT_LT(fabs(fExpected - fCrownRad)/fExpected, 0.01);

    iSp = 4;  fExpected = 0.4321025;
    p_oTree = p_oPop->CreateTree(1,1,iSp,clTreePopulation::sapling,fDBH);
    fCrownRad = p_oAllom->CalcSaplingCrownRadius(p_oTree);
    EXPECT_LT(fabs(fExpected - fCrownRad)/fExpected, 0.01);

    iSp = 5;  fExpected = 6.09703717;
    p_oTree = p_oPop->CreateTree(1,1,iSp,clTreePopulation::sapling,fDBH);
    fCrownRad = p_oAllom->CalcSaplingCrownRadius(p_oTree);
    EXPECT_LT(fabs(fExpected - fCrownRad)/fExpected, 0.01);


    /*  fDBH = 0;
  iSp = 0;  fExpected = 0;
  fCrownRad = p_oAllom->CalcSaplingCrownRadius(fHeight, fDBH, iSp);
  EXPECT_LT(fabs(fExpected), 0.01);

  iSp = 1;  fExpected = 0;
  fCrownRad = p_oAllom->CalcSaplingCrownRadius(fHeight, fDBH, iSp);
  EXPECT_LT(fabs(fExpected), 0.01);

  iSp = 2;  fExpected = 0.4;
  fCrownRad = p_oAllom->CalcSaplingCrownRadius(fHeight, fDBH, iSp);
  EXPECT_LT(fabs(fExpected - fCrownRad)/fExpected, 0.01);

  iSp = 3;  fExpected = 0.5;
  fCrownRad = p_oAllom->CalcSaplingCrownRadius(fHeight, fDBH, iSp);
  EXPECT_LT(fabs(fExpected - fCrownRad)/fExpected, 0.01);

  iSp = 4;  fExpected = 0;
  fCrownRad = p_oAllom->CalcSaplingCrownRadius(fHeight, fDBH, iSp);
  EXPECT_LT(fabs(fExpected), 0.01);

  iSp = 5;  fExpected = 0.7;
  fCrownRad = p_oAllom->CalcSaplingCrownRadius(fHeight, fDBH, iSp);
  EXPECT_LT(fabs(fExpected - fCrownRad)/fExpected, 0.01);



  fDBH = 3.45E+12;
  iSp = 0;  fExpected = 10;
  fCrownRad = p_oAllom->CalcSaplingCrownRadius(fHeight, fDBH, iSp);
  EXPECT_LT(fabs(fExpected - fCrownRad)/fExpected, 0.01);

  iSp = 1;  fExpected = 10;
  fCrownRad = p_oAllom->CalcSaplingCrownRadius(fHeight, fDBH, iSp);
  EXPECT_LT(fabs(fExpected - fCrownRad)/fExpected, 0.01);

  iSp = 2;  fExpected = 7.4;
  fCrownRad = p_oAllom->CalcSaplingCrownRadius(fHeight, fDBH, iSp);
  EXPECT_LT(fabs(fExpected - fCrownRad)/fExpected, 0.01);

  iSp = 3;  fExpected = 10.5;
  fCrownRad = p_oAllom->CalcSaplingCrownRadius(fHeight, fDBH, iSp);
  EXPECT_LT(fabs(fExpected - fCrownRad)/fExpected, 0.01);

  iSp = 4;  fExpected = 10;
  fCrownRad = p_oAllom->CalcSaplingCrownRadius(fHeight, fDBH, iSp);
  EXPECT_LT(fabs(fExpected - fCrownRad)/fExpected, 0.01);

  iSp = 5;  fExpected = 9.9;
  fCrownRad = p_oAllom->CalcSaplingCrownRadius(fHeight, fDBH, iSp);
  EXPECT_LT(fabs(fExpected - fCrownRad)/fExpected, 0.01);



  fDBH = 4.30E-28;
  iSp = 0;  fExpected = 1.28734E-26;
  fCrownRad = p_oAllom->CalcSaplingCrownRadius(fHeight, fDBH, iSp);
  EXPECT_LT(fabs(fExpected - fCrownRad)/fExpected, 0.01);

  iSp = 1;  fExpected = 2.6402E-29;
  fCrownRad = p_oAllom->CalcSaplingCrownRadius(fHeight, fDBH, iSp);
  EXPECT_LT(fabs(fExpected - fCrownRad)/fExpected, 0.01);

  iSp = 2;  fExpected = 0.4;
  fCrownRad = p_oAllom->CalcSaplingCrownRadius(fHeight, fDBH, iSp);
  EXPECT_LT(fabs(fExpected - fCrownRad)/fExpected, 0.01);

  iSp = 3;  fExpected = 0.5;
  fCrownRad = p_oAllom->CalcSaplingCrownRadius(fHeight, fDBH, iSp);
  EXPECT_LT(fabs(fExpected - fCrownRad)/fExpected, 0.01);

  iSp = 4;  fExpected = 2.6402E-29;
  fCrownRad = p_oAllom->CalcSaplingCrownRadius(fHeight, fDBH, iSp);
  EXPECT_LT(fabs(fExpected - fCrownRad)/fExpected, 0.01);

  iSp = 5;  fExpected = 0.7;
  fCrownRad = p_oAllom->CalcSaplingCrownRadius(fHeight, fDBH, iSp);
  EXPECT_LT(fabs(fExpected - fCrownRad)/fExpected, 0.01);
     */
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

///////////////////////////////
// Test CalcSaplingCrownDepth
///////////////////////////////
TEST(Allometry, CalcSaplingCrownDepth) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clAllometry *p_oAllom;
    clTree *p_oTree;
    float fDBH, fHeight, fCrownDepth, fExpected;
    int iSp;

    //Set up our run and get the tree popluation pointer
    p_oSimManager->ReadFile( WriteAllometryXMLFile1() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
    p_oAllom = p_oPop->GetAllometryObject();

    fHeight = 7.0375; fDBH = 5;
    iSp = 0;  fExpected = 2.7375875;
    p_oTree = p_oPop->CreateTree(1,1,iSp,clTreePopulation::sapling,fDBH);
    p_oTree->GetValue(p_oPop->GetCrownDepthCode(p_oTree->GetSpecies(), p_oTree->GetType()),&fCrownDepth);
    EXPECT_LT(fCrownDepth, 0);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()),fHeight,false);
    fCrownDepth = p_oAllom->CalcSaplingCrownDepth(p_oTree);
    EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

    iSp = 1;  fExpected = 0.976240954;
    p_oTree = p_oPop->CreateTree(1,1,iSp,clTreePopulation::sapling,fDBH);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()),fHeight,false);
    fCrownDepth = p_oAllom->CalcSaplingCrownDepth(p_oTree);
    EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

    iSp = 2;  fExpected = 1.230532674;
    p_oTree = p_oPop->CreateTree(1,1,iSp,clTreePopulation::sapling,fDBH);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()),fHeight,false);
    fCrownDepth = p_oAllom->CalcSaplingCrownDepth(p_oTree);
    EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

    iSp = 3;  fExpected = 2.949668354;
    p_oTree = p_oPop->CreateTree(1,1,iSp,clTreePopulation::sapling,fDBH);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()),fHeight,false);
    fCrownDepth = p_oAllom->CalcSaplingCrownDepth(p_oTree);
    EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

    iSp = 4;  fExpected = 3.849799421;
    p_oTree = p_oPop->CreateTree(1,1,iSp,clTreePopulation::sapling,fDBH);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()),fHeight,false);
    fCrownDepth = p_oAllom->CalcSaplingCrownDepth(p_oTree);
    EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

    iSp = 5;  fExpected = 1.968590949;
    p_oTree = p_oPop->CreateTree(1,1,iSp,clTreePopulation::sapling,fDBH);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()),fHeight,false);
    fCrownDepth = p_oAllom->CalcSaplingCrownDepth(p_oTree);
    EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);



    /* fHeight = 0;
  iSp = 0;  fExpected = 0;
  fCrownDepth = p_oAllom->CalcSaplingCrownDepth(fHeight, fDBH, iSp);
  EXPECT_LT(fabs(fExpected), 0.01);

  iSp = 1;  fExpected = 0;
  fCrownDepth = p_oAllom->CalcSaplingCrownDepth(fHeight, fDBH, iSp);
  EXPECT_LT(fabs(fExpected), 0.01);

  iSp = 2;  fExpected = 0;
  fCrownDepth = p_oAllom->CalcSaplingCrownDepth(fHeight, fDBH, iSp);
  EXPECT_LT(fabs(fExpected), 0.01);

  iSp = 3;  fExpected = 0;
  fCrownDepth = p_oAllom->CalcSaplingCrownDepth(fHeight, fDBH, iSp);
  EXPECT_LT(fabs(fExpected), 0.01);

  iSp = 4;  fExpected = 0;
  fCrownDepth = p_oAllom->CalcSaplingCrownDepth(fHeight, fDBH, iSp);
  EXPECT_LT(fabs(fExpected), 0.01);

  iSp = 5;  fExpected = 0;
  fCrownDepth = p_oAllom->CalcSaplingCrownDepth(fHeight, fDBH, iSp);
  EXPECT_LT(fabs(fExpected), 0.01);



  fHeight = 3.45E+12;
  iSp = 0;  fExpected = 1.34205E+12;
  fCrownDepth = p_oAllom->CalcSaplingCrownDepth(fHeight, fDBH, iSp);
  EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

  iSp = 1;  fExpected = 683529.6629;
  fCrownDepth = p_oAllom->CalcSaplingCrownDepth(fHeight, fDBH, iSp);
  EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

  iSp = 2;  fExpected = 12.5;
  fCrownDepth = p_oAllom->CalcSaplingCrownDepth(fHeight, fDBH, iSp);
  EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

  iSp = 3;  fExpected = 13.4;
  fCrownDepth = p_oAllom->CalcSaplingCrownDepth(fHeight, fDBH, iSp);
  EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

  iSp = 4;  fExpected = 14.3;
  fCrownDepth = p_oAllom->CalcSaplingCrownDepth(fHeight, fDBH, iSp);
  EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

  iSp = 5;  fExpected = 65390717488.0;
  fCrownDepth = p_oAllom->CalcSaplingCrownDepth(fHeight, fDBH, iSp);
  EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);



  fHeight = 4.30E-28;
  iSp = 0;  fExpected = 1.6727E-28;
  fCrownDepth = p_oAllom->CalcSaplingCrownDepth(fHeight, fDBH, iSp);
  EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

  iSp = 1;  fExpected = 4.3E-28;
  fCrownDepth = p_oAllom->CalcSaplingCrownDepth(fHeight, fDBH, iSp);
  EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

  iSp = 2;  fExpected = 4.3E-28;
  fCrownDepth = p_oAllom->CalcSaplingCrownDepth(fHeight, fDBH, iSp);
  EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

  iSp = 3;  fExpected = 4.3E-28;
  fCrownDepth = p_oAllom->CalcSaplingCrownDepth(fHeight, fDBH, iSp);
  EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

  iSp = 4;  fExpected = 4.3E-28;
  fCrownDepth = p_oAllom->CalcSaplingCrownDepth(fHeight, fDBH, iSp);
  EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

  iSp = 5;  fExpected = 4.3E-28;
  fCrownDepth = p_oAllom->CalcSaplingCrownDepth(fHeight, fDBH, iSp);
  EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);
     */
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

///////////////////////////////
// Test CalcSeedlingHeight
///////////////////////////////
TEST(Allometry, CalcSeedlingHeight) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clAllometry *p_oAllom;
    float fDBH, fHeight, fExpected;
    int iSp;

    //Set up our run and get the tree popluation pointer
    p_oSimManager->ReadFile( WriteAllometryXMLFile1() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
    p_oAllom = p_oPop->GetAllometryObject();

    fDBH = 0.89485;
    iSp = 0;  fExpected = 1.003688643;
    fHeight = p_oAllom->CalcSeedlingHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 1;  fExpected = 0.089233333;
    fHeight = p_oAllom->CalcSeedlingHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 2;  fExpected = 6.896898695;
    fHeight = p_oAllom->CalcSeedlingHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 3;  fExpected = 0.861651065;
    fHeight = p_oAllom->CalcSeedlingHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 4;  fExpected = 6.8425;
    fHeight = p_oAllom->CalcSeedlingHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 5;  fExpected = 0.1988758;
    fHeight = p_oAllom->CalcSeedlingHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);



    fDBH = 0;
    iSp = 0;  fExpected = 0.1;
    fHeight = p_oAllom->CalcSeedlingHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 1;  fExpected = 0.001;
    fHeight = p_oAllom->CalcSeedlingHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 2;  fExpected = 0.1;
    fHeight = p_oAllom->CalcSeedlingHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 3;  fExpected = 0.001;
    fHeight = p_oAllom->CalcSeedlingHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected), 0.01);

    iSp = 4;  fExpected = 0.001;
    fHeight = p_oAllom->CalcSeedlingHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 5;  fExpected = 0.001;
    fHeight = p_oAllom->CalcSeedlingHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);


    fDBH = -2.94893;
    iSp = 0;  fExpected = 0.001;
    fHeight = p_oAllom->CalcSeedlingHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 1;  fExpected = 0.001;
    fHeight = p_oAllom->CalcSeedlingHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 2;  fExpected = 0.001;
    fHeight = p_oAllom->CalcSeedlingHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 3;  fExpected = 0.001;
    fHeight = p_oAllom->CalcSeedlingHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 4;  fExpected = 0.001;
    fHeight = p_oAllom->CalcSeedlingHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 5;  fExpected = 0.001;
    fHeight = p_oAllom->CalcSeedlingHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);


    fDBH = 3.45E+12;
    iSp = 0;  fExpected = 30.1;
    fHeight = p_oAllom->CalcSeedlingHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 1;  fExpected = 39.54;
    fHeight = p_oAllom->CalcSeedlingHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 2;  fExpected = 30.1;
    fHeight = p_oAllom->CalcSeedlingHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 3;  fExpected = 39.48;
    fHeight = p_oAllom->CalcSeedlingHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 4;  fExpected = 39.54;
    fHeight = p_oAllom->CalcSeedlingHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 5;  fExpected = 45;
    fHeight = p_oAllom->CalcSeedlingHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);


    fDBH = 4.30E-28;
    iSp = 0;  fExpected = 0.1;
    fHeight = p_oAllom->CalcSeedlingHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 1;  fExpected = 0.001;
    fHeight = p_oAllom->CalcSeedlingHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 2;  fExpected = 0.1;
    fHeight = p_oAllom->CalcSeedlingHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 3;  fExpected = 0.001;
    fHeight = p_oAllom->CalcSeedlingHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 4;  fExpected = 0.001;
    fHeight = p_oAllom->CalcSeedlingHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    iSp = 5;  fExpected = 0.001;
    fHeight = p_oAllom->CalcSeedlingHeight(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fHeight)/fExpected, 0.01);

    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

///////////////////////////////
// Test CalcSeedlingDiam10
///////////////////////////////
TEST(Allometry, CalcSeedlingDiam10) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clAllometry *p_oAllom;
    float fDBH, fHeight, fExpected;
    int iSp;

    //Set up our run and get the tree popluation pointer
    p_oSimManager->ReadFile( WriteAllometryXMLFile1() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
    p_oAllom = p_oPop->GetAllometryObject();

    fHeight = 0.8747;
    iSp = 0;  fExpected = 0.765436196;
    fDBH = p_oAllom->CalcSeedlingDiam10(fHeight, iSp);
    EXPECT_LT(fabs(fExpected - fDBH)/fExpected, 0.01);

    iSp = 1;  fExpected = 2.07305;
    fDBH = p_oAllom->CalcSeedlingDiam10(fHeight, iSp);
    EXPECT_LT(fabs(fExpected - fDBH)/fExpected, 0.01);

    iSp = 2;  fExpected = 0.091127165;
    fDBH = p_oAllom->CalcSeedlingDiam10(fHeight, iSp);
    EXPECT_LT(fabs(fExpected - fDBH)/fExpected, 0.01);

    iSp = 3;  fExpected = 0.908401703;
    fDBH = p_oAllom->CalcSeedlingDiam10(fHeight, iSp);
    EXPECT_LT(fabs(fExpected - fDBH)/fExpected, 0.01);

    iSp = 4;  fExpected = 0.775494;
    fDBH = p_oAllom->CalcSeedlingDiam10(fHeight, iSp);
    EXPECT_LT(fabs(fExpected - fDBH)/fExpected, 0.01);

    iSp = 5;  fExpected = 1.44519544;
    fDBH = p_oAllom->CalcSeedlingDiam10(fHeight, iSp);
    EXPECT_LT(fabs(fExpected - fDBH)/fExpected, 0.01);


    fHeight = 0;
    iSp = 0;  fExpected = MINDIAM; //fExpected = -0.09736074;
    fDBH = p_oAllom->CalcSeedlingDiam10(fHeight, iSp);
    EXPECT_LT(fabs(fExpected - fDBH)/fExpected, 0.01);

    iSp = 1;  fExpected = 0.761;
    fDBH = p_oAllom->CalcSeedlingDiam10(fHeight, iSp);
    EXPECT_LT(fabs(fExpected - fDBH)/fExpected, 0.01);

    iSp = 2;  fExpected = MINDIAM; //fExpected = -0.011591049;
    fDBH = p_oAllom->CalcSeedlingDiam10(fHeight, iSp);
    EXPECT_LT(fabs(fExpected - fDBH)/fExpected, 0.01);

    iSp = 3;  fExpected = MINDIAM; //fExpected = 0;
    fDBH = p_oAllom->CalcSeedlingDiam10(fHeight, iSp);
    EXPECT_LT(fabs(fExpected), 0.01);

    iSp = 4;  fExpected = 0.758;
    fDBH = p_oAllom->CalcSeedlingDiam10(fHeight, iSp);
    EXPECT_LT(fabs(fExpected - fDBH)/fExpected, 0.01);

    iSp = 5;  fExpected = 0.732899023;
    fDBH = p_oAllom->CalcSeedlingDiam10(fHeight, iSp);
    EXPECT_LT(fabs(fExpected - fDBH)/fExpected, 0.01);


    fHeight = -0.35234;
    iSp = 0;  fExpected = MINDIAM; //fExpected = -0.437842505;
    fDBH = p_oAllom->CalcSeedlingDiam10(fHeight, iSp);
    EXPECT_LT(fabs(fExpected - fDBH)/fExpected, 0.01);

    iSp = 1;  fExpected = 0.23249;
    fDBH = p_oAllom->CalcSeedlingDiam10(fHeight, iSp);
    EXPECT_LT(fabs(fExpected - fDBH)/fExpected, 0.01);

    iSp = 2;  fExpected = MINDIAM; //fExpected = -0.052126286;
    fDBH = p_oAllom->CalcSeedlingDiam10(fHeight, iSp);
    EXPECT_LT(fabs(fExpected - fDBH)/fExpected, 0.01);

    iSp = 3;  fExpected = MINDIAM; //fExpected = -0.003659155;
    fDBH = p_oAllom->CalcSeedlingDiam10(fHeight, iSp);
    EXPECT_LT(fabs(fExpected - fDBH)/fExpected, 0.01);

    iSp = 4;  fExpected = 0.7509532;
    fDBH = p_oAllom->CalcSeedlingDiam10(fHeight, iSp);
    EXPECT_LT(fabs(fExpected - fDBH)/fExpected, 0.01);

    iSp = 5;  fExpected = 0.445977199;
    fDBH = p_oAllom->CalcSeedlingDiam10(fHeight, iSp);
    EXPECT_LT(fabs(fExpected - fDBH)/fExpected, 0.01);


    fHeight = 4.30E-28;
    iSp = 0;  fExpected = MINDIAM; //fExpected = -0.09736074;
    fDBH = p_oAllom->CalcSeedlingDiam10(fHeight, iSp);
    EXPECT_LT(fabs(fExpected - fDBH)/fExpected, 0.01);

    iSp = 1;  fExpected = 0.761;
    fDBH = p_oAllom->CalcSeedlingDiam10(fHeight, iSp);
    EXPECT_LT(fabs(fExpected - fDBH)/fExpected, 0.01);

    iSp = 2;  fExpected = MINDIAM; //fExpected = -0.011591049;
    fDBH = p_oAllom->CalcSeedlingDiam10(fHeight, iSp);
    EXPECT_LT(fabs(fExpected - fDBH)/fExpected, 0.01);

    iSp = 3;  fExpected = MINDIAM; //fExpected = 4.46568E-28;
    fDBH = p_oAllom->CalcSeedlingDiam10(fHeight, iSp);
    EXPECT_LT(fabs(fExpected - fDBH)/fExpected, 0.01);

    iSp = 4;  fExpected = 0.758;
    fDBH = p_oAllom->CalcSeedlingDiam10(fHeight, iSp);
    EXPECT_LT(fabs(fExpected - fDBH)/fExpected, 0.01);

    iSp = 5;  fExpected = 0.732899023;
    fDBH = p_oAllom->CalcSeedlingDiam10(fHeight, iSp);
    EXPECT_LT(fabs(fExpected - fDBH)/fExpected, 0.01);

    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

///////////////////////////////
// Test ConvertDiam10ToDbh
///////////////////////////////
TEST(Allometry, ConvertDiam10ToDbh) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clAllometry *p_oAllom;
    float fDBH, fCrownDepth, fExpected;
    int iSp;

    //Set up our run and get the tree popluation pointer
    p_oSimManager->ReadFile( WriteAllometryXMLFile1() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
    p_oAllom = p_oPop->GetAllometryObject();

    fDBH = 2.5938;
    iSp = 0;  fExpected = 2.07711504;
    fCrownDepth = p_oAllom->ConvertDiam10ToDbh(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

    iSp = 1;  fExpected = 2.54175472;
    fCrownDepth = p_oAllom->ConvertDiam10ToDbh(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

    iSp = 2;  fExpected = 1.63096342;
    fCrownDepth = p_oAllom->ConvertDiam10ToDbh(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

    iSp = 3;  fExpected = 2.37711504;
    fCrownDepth = p_oAllom->ConvertDiam10ToDbh(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

    iSp = 4;  fExpected = 1.54175472;
    fCrownDepth = p_oAllom->ConvertDiam10ToDbh(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

    iSp = 5;  fExpected = MINDIAM; //fExpected = -1.16903658;
    fCrownDepth = p_oAllom->ConvertDiam10ToDbh(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);



    fDBH = 0;
    iSp = 0;  fExpected = MINDIAM; //fExpected = 0;
    fCrownDepth = p_oAllom->ConvertDiam10ToDbh(fDBH, iSp);
    EXPECT_LT(fabs(fExpected), 0.01);

    iSp = 1;  fExpected = 1;
    fCrownDepth = p_oAllom->ConvertDiam10ToDbh(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

    iSp = 2;  fExpected = MINDIAM; //fExpected = -0.2;
    fCrownDepth = p_oAllom->ConvertDiam10ToDbh(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

    iSp = 3;  fExpected = 0.3;
    fCrownDepth = p_oAllom->ConvertDiam10ToDbh(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

    iSp = 4;  fExpected = 0;
    fCrownDepth = p_oAllom->ConvertDiam10ToDbh(fDBH, iSp);
    EXPECT_LT(fabs(fExpected), 0.01);

    iSp = 5;  fExpected = MINDIAM; //fExpected = -3;
    fCrownDepth = p_oAllom->ConvertDiam10ToDbh(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);



    fDBH = -9.94983;
    iSp = 0;  fExpected = MINDIAM; //fExpected = -7.967823864;
    fCrownDepth = p_oAllom->ConvertDiam10ToDbh(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

    iSp = 1;  fExpected = MINDIAM; //fExpected = -4.914178952;
    fCrownDepth = p_oAllom->ConvertDiam10ToDbh(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

    iSp = 2;  fExpected = MINDIAM; //fExpected = -7.223584997;
    fCrownDepth = p_oAllom->ConvertDiam10ToDbh(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

    iSp = 3;  fExpected = MINDIAM; //fExpected = -7.667823864;
    fCrownDepth = p_oAllom->ConvertDiam10ToDbh(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

    iSp = 4;  fExpected = MINDIAM; //fExpected = -5.914178952;
    fCrownDepth = p_oAllom->ConvertDiam10ToDbh(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

    iSp = 5;  fExpected = MINDIAM; //fExpected = -10.023585;
    fCrownDepth = p_oAllom->ConvertDiam10ToDbh(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);



    fDBH = 3.45E+12;
    iSp = 0;  fExpected = 2.76276E+12;
    fCrownDepth = p_oAllom->ConvertDiam10ToDbh(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

    iSp = 1;  fExpected = 2.05068E+12;
    fCrownDepth = p_oAllom->ConvertDiam10ToDbh(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

    iSp = 2;  fExpected = 2.43535E+12;
    fCrownDepth = p_oAllom->ConvertDiam10ToDbh(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

    iSp = 3;  fExpected = 2.76276E+12;
    fCrownDepth = p_oAllom->ConvertDiam10ToDbh(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

    iSp = 4;  fExpected = 2.05068E+12;
    fCrownDepth = p_oAllom->ConvertDiam10ToDbh(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

    iSp = 5;  fExpected = 2.43535E+12;
    fCrownDepth = p_oAllom->ConvertDiam10ToDbh(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);




    fDBH = 4.30E-28;
    iSp = 0;  fExpected = MINDIAM; //fExpected = 3.44E-28;
    fCrownDepth = p_oAllom->ConvertDiam10ToDbh(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

    iSp = 1;  fExpected = 1;
    fCrownDepth = p_oAllom->ConvertDiam10ToDbh(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

    iSp = 2;  fExpected = MINDIAM; //fExpected = -0.2;
    fCrownDepth = p_oAllom->ConvertDiam10ToDbh(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

    iSp = 3;  fExpected = 0.3;
    fCrownDepth = p_oAllom->ConvertDiam10ToDbh(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

    iSp = 4;  fExpected = MINDIAM; //fExpected = 2.55592E-28;
    fCrownDepth = p_oAllom->ConvertDiam10ToDbh(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

    iSp = 5;  fExpected = MINDIAM; //fExpected = -3;
    fCrownDepth = p_oAllom->ConvertDiam10ToDbh(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

///////////////////////////////
// Test ConvertDbhToDiam10
///////////////////////////////
TEST(Allometry, ConvertDbhToDiam10) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clAllometry *p_oAllom;
    float fDBH, fCrownDepth, fExpected;
    int iSp;

    //Set up our run and get the tree popluation pointer
    p_oSimManager->ReadFile( WriteAllometryXMLFile1() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
    p_oAllom = p_oPop->GetAllometryObject();

    fDBH = 10.2342;
    iSp = 0;  fExpected = 12.77997003;
    fCrownDepth = p_oAllom->ConvertDbhToDiam10(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

    iSp = 1;  fExpected = 15.53532974;
    fCrownDepth = p_oAllom->ConvertDbhToDiam10(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

    iSp = 2;  fExpected = 14.7814138;
    fCrownDepth = p_oAllom->ConvertDbhToDiam10(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

    iSp = 3;  fExpected = 12.40534466;
    fCrownDepth = p_oAllom->ConvertDbhToDiam10(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

    iSp = 4;  fExpected = 17.21769852;
    fCrownDepth = p_oAllom->ConvertDbhToDiam10(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

    iSp = 5;  fExpected = 18.7479813;
    fCrownDepth = p_oAllom->ConvertDbhToDiam10(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);



    fDBH = 0;
    iSp = 0;  fExpected = 0;
    fCrownDepth = p_oAllom->ConvertDbhToDiam10(fDBH, iSp);
    EXPECT_LT(fabs(fExpected), 0.01);

    iSp = 1;  fExpected = MINDIAM; //fExpected = -1.682368775;
    fCrownDepth = p_oAllom->ConvertDbhToDiam10(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

    iSp = 2;  fExpected = 0.28332625;
    fCrownDepth = p_oAllom->ConvertDbhToDiam10(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

    iSp = 3;  fExpected = MINDIAM; //fExpected = -0.374625375;
    fCrownDepth = p_oAllom->ConvertDbhToDiam10(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

    iSp = 4;  fExpected = 0;
    fCrownDepth = p_oAllom->ConvertDbhToDiam10(fDBH, iSp);
    EXPECT_LT(fabs(fExpected), 0.01);

    iSp = 5;  fExpected = 4.249893753;
    fCrownDepth = p_oAllom->ConvertDbhToDiam10(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);



    fDBH = -33.98034;
    iSp = 0;  fExpected = MINDIAM; //fExpected = -42.43299201;
    fCrownDepth = p_oAllom->ConvertDbhToDiam10(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

    iSp = 1;  fExpected = MINDIAM; //fExpected = -58.84983176;
    fCrownDepth = p_oAllom->ConvertDbhToDiam10(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

    iSp = 2;  fExpected = MINDIAM; //fExpected = -47.85428531;
    fCrownDepth = p_oAllom->ConvertDbhToDiam10(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

    iSp = 3;  fExpected = MINDIAM; //fExpected = -42.80761738;
    fCrownDepth = p_oAllom->ConvertDbhToDiam10(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

    iSp = 4;  fExpected = MINDIAM; //fExpected = -57.16746299;
    fCrownDepth = p_oAllom->ConvertDbhToDiam10(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

    iSp = 5;  fExpected = MINDIAM; //fExpected = -43.88771781;
    fCrownDepth = p_oAllom->ConvertDbhToDiam10(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);



    fDBH = 3.45E+12;
    iSp = 0;  fExpected = 4.30819E+12;
    fCrownDepth = p_oAllom->ConvertDbhToDiam10(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

    iSp = 1;  fExpected = 5.80417E+12;
    fCrownDepth = p_oAllom->ConvertDbhToDiam10(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

    iSp = 2;  fExpected = 4.88738E+12;
    fCrownDepth = p_oAllom->ConvertDbhToDiam10(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

    iSp = 3;  fExpected = 4.30819E+12;
    fCrownDepth = p_oAllom->ConvertDbhToDiam10(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

    iSp = 4;  fExpected = 5.80417E+12;
    fCrownDepth = p_oAllom->ConvertDbhToDiam10(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

    iSp = 5;  fExpected = 4.88738E+12;
    fCrownDepth = p_oAllom->ConvertDbhToDiam10(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);



    fDBH = 4.30E-28;
    iSp = 0;  fExpected = MINDIAM; //fExpected = 5.36963E-28;
    fCrownDepth = p_oAllom->ConvertDbhToDiam10(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

    iSp = 1;  fExpected = MINDIAM; //fExpected = -1.682368775;
    fCrownDepth = p_oAllom->ConvertDbhToDiam10(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

    iSp = 2;  fExpected = 0.28332625;
    fCrownDepth = p_oAllom->ConvertDbhToDiam10(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

    iSp = 3;  fExpected = MINDIAM; //fExpected = -0.374625375;
    fCrownDepth = p_oAllom->ConvertDbhToDiam10(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

    iSp = 4;  fExpected = MINDIAM; //fExpected = 7.23419E-28;
    fCrownDepth = p_oAllom->ConvertDbhToDiam10(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);

    iSp = 5;  fExpected = 4.249893753;
    fCrownDepth = p_oAllom->ConvertDbhToDiam10(fDBH, iSp);
    EXPECT_LT(fabs(fExpected - fCrownDepth)/fExpected, 0.01);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

///////////////////////////////
// Test parameter file reading
///////////////////////////////
TEST(Allometry, ParameterFileReading) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clAllometry *p_oAllom;

    //These files should simply load without problems.
    p_oSimManager->ReadFile( WriteAllometryXMLFile2() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
    p_oAllom = p_oPop->GetAllometryObject();
    EXPECT_EQ(10, p_oAllom->GetMaxCrownRadius());

    p_oSimManager->ReadFile( WriteAllometryXMLFile3() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
    p_oAllom = p_oPop->GetAllometryObject();
    EXPECT_EQ(9.5, p_oAllom->GetMaxCrownRadius());

    p_oSimManager->ReadFile( WriteAllometryXMLFile4() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
    p_oAllom = p_oPop->GetAllometryObject();
    EXPECT_EQ(10, p_oAllom->GetMaxCrownRadius());

    p_oSimManager->ReadFile( WriteAllometryXMLFile5() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    p_oSimManager->ReadFile( WriteAllometryXMLFile6() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestErrorProcessing()
// Tests error processing. In the first part, invalid requests are made of
// the clAllometry functions. In the second part, parameter files with bad
// data are read in.
/////////////////////////////////////////////////////////////////////////////
TEST(Allometry, TestErrorProcessing) {
  clTreePopulation * p_oPop;
  clAllometry *p_oAllom;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );

  //////////////////////////////
  // Part 1:  Bad arguments to the allometry functions
  //////////////////////////////
  //Set up our run and get the tree popluation pointer
  p_oSimManager->ReadFile( WriteAllometryXMLFile1() );
  p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
  p_oAllom = p_oPop->GetAllometryObject();

  //Invalid species to CalcAdultHeight
  ASSERT_THROW(p_oAllom->CalcAdultHeight(10.0, -1), modelErr) << "Didn't catch invalid species for CalcAdultHeight.";

  //Invalid species to CalcAdultDbh
  ASSERT_THROW(p_oAllom->CalcAdultDbh(10.0, 10), modelErr) << "Didn't catch invalid species for CalcAdultDbh.";
  //Invalid species to CalcSaplingHeight
  ASSERT_THROW(p_oAllom->CalcSaplingHeight(10.0, -10), modelErr) << "Didn't catch invalid species for CalcSaplingHeight.";

  //Invalid species to CalcSaplingDbh
  ASSERT_THROW(p_oAllom->CalcSaplingDbh(10.0, 9), modelErr) << "Didn't catch invalid species for CalcSaplingDbh.";

  //Invalid species to CalcSeedlingHeight
  ASSERT_THROW(p_oAllom->CalcSeedlingHeight(10.0, -10), modelErr) << "Didn't catch invalid species for CalcSeedlingHeight.";

  //Invalid species to CalcSeedlingDiam10
  ASSERT_THROW(p_oAllom->CalcSeedlingDiam10(10.0, 9), modelErr) << "Didn't catch invalid species for CalcSeedlingDiam10.";

  /*catch (modelErr&err) {;}
  try {
    //Invalid species to CalcAdultCrownRadius
    p_oAllom->CalcAdultCrownRadius(10.0, 10.0, 9);
    FAIL() << "Didn't catch invalid species for CalcAdultCrownRadius.";
  }
  catch (modelErr&err) {;}
  try {
    //Invalid species to CalcSaplingCrownRadius
    p_oAllom->CalcSaplingCrownRadius(10.0, 10.0, 9);
    FAIL() << "Didn't catch invalid species for CalcSaplingCrownRadius.";
  }
  catch (modelErr&err) {;}
  try {
    //Invalid species to CalcAdultCrownDepth
    p_oAllom->CalcAdultCrownDepth(10.0, 10.0, -9);
    FAIL() << "Didn't catch invalid species for CalcAdultCrownDepth.";
  }
  catch (modelErr&err) {;}
  try {
    //Invalid species to CalcSaplingCrownDepth
    p_oAllom->CalcSaplingCrownDepth(10.0, 10.0, 9);
    FAIL() << "Didn't catch invalid species for CalcSaplingCrownDepth.";
  }*/

  //Invalid species to ConvertDiam10ToDbh
  ASSERT_THROW(p_oAllom->ConvertDiam10ToDbh(10.0, 1985), modelErr) << "Didn't catch invalid species for ConvertDiam10ToDbh.";

  //Invalid species to ConvertDbhToDiam10
  ASSERT_THROW(p_oAllom->ConvertDbhToDiam10(10.0, 1985), modelErr) << "Didn't catch invalid species for ConvertDbhToDiam10.";

  //Height too large to CalcAdultDbh
  ASSERT_THROW(p_oAllom->CalcAdultDbh(100.0, 1), modelErr) << "Didn't catch invalid height for CalcAdultDbh.";

  //Height too large to CalcSaplingDbh
  ASSERT_THROW(p_oAllom->CalcSaplingDbh(100.0, 0), modelErr) << "Didn't catch invalid height for CalcSaplingDbh.";

  //////////////////////////////
  // Part 2:  Bad data in parameter files
  //////////////////////////////
  try
  {
    p_oSimManager->ReadFile(WriteAllometryXMLErrorFile1());
    FAIL() << "TestAllometry error processing didn't catch error for WriteAllometryXMLErrorFile1.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clAllometry::GetData") != 0)
    {
      FAIL() << "TestAllometry error processing caught wrong error for WriteAllometryXMLErrorFile1.";
    }
    ;
  }
  try
  {
    p_oSimManager->ReadFile(WriteAllometryXMLErrorFile2());
    FAIL() << "TestAllometry error processing didn't catch error for WriteAllometryXMLErrorFile2.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clAllometry::GetData") != 0)
    {
      FAIL() << "TestAllometry error processing caught wrong error for WriteAllometryXMLErrorFile2.";
    }
    ;
  }
  try
  {
    p_oSimManager->ReadFile(WriteAllometryXMLErrorFile3());
    FAIL() << "TestAllometry error processing didn't catch error for WriteAllometryXMLErrorFile3.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clAllometry::GetData") != 0)
    {
      FAIL() << "TestAllometry error processing caught wrong error for WriteAllometryXMLErrorFile3.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteAllometryXMLErrorFile4());
    FAIL() << "TestAllometry error processing didn't catch error for WriteAllometryXMLErrorFile4.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clAllometry::GetData") != 0)
    {
      FAIL() << "TestAllometry error processing caught wrong error for WriteAllometryXMLErrorFile4.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteAllometryXMLErrorFile5());
    FAIL() << "TestAllometry error processing didn't catch error for WriteAllometryXMLErrorFile5.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clAllometry::GetData") != 0)
    {
      FAIL() << "TestAllometry error processing caught wrong error for WriteAllometryXMLErrorFile5.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteAllometryXMLErrorFile6());
    FAIL() << "TestAllometry error processing didn't catch error for WriteAllometryXMLErrorFile6.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clAllometry::GetData") != 0)
    {
      FAIL() << "TestAllometry error processing caught wrong error for WriteAllometryXMLErrorFile6.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteAllometryXMLErrorFile7());
    FAIL() << "TestAllometry error processing didn't catch error for WriteAllometryXMLErrorFile7.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clAllometry::GetData") != 0)
    {
      FAIL() << "TestAllometry error processing caught wrong error for WriteAllometryXMLErrorFile7.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteAllometryXMLErrorFile8());
    FAIL() << "TestAllometry error processing didn't catch error for WriteAllometryXMLErrorFile8.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clAllometry::GetData") != 0)
    {
      FAIL() << "TestAllometry error processing caught wrong error for WriteAllometryXMLErrorFile8.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteAllometryXMLErrorFile9());
    FAIL() << "TestAllometry error processing didn't catch error for WriteAllometryXMLErrorFile9.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clAllometry::GetData") != 0)
    {
      FAIL() << "TestAllometry error processing caught wrong error for WriteAllometryXMLErrorFile9.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteAllometryXMLErrorFile10());
    FAIL() << "TestAllometry error processing didn't catch error for WriteAllometryXMLErrorFile10.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clAllometry::GetData") != 0)
    {
      FAIL() << "TestAllometry error processing caught wrong error for WriteAllometryXMLErrorFile10.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteAllometryXMLErrorFile11());
    FAIL() << "TestAllometry error processing didn't catch error for WriteAllometryXMLErrorFile11.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clAllometry::GetData") != 0)
    {
      FAIL() << "TestAllometry error processing caught wrong error for WriteAllometryXMLErrorFile11.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteAllometryXMLErrorFile12());
    FAIL() << "TestAllometry error processing didn't catch error for WriteAllometryXMLErrorFile12.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clAllometry::GetData") != 0)
    {
      FAIL() << "TestAllometry error processing caught wrong error for WriteAllometryXMLErrorFile12.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteAllometryXMLErrorFile13());
    FAIL() << "TestAllometry error processing didn't catch error for WriteAllometryXMLErrorFile13.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clAllometry::GetData") != 0)
    {
      FAIL() << "TestAllometry error processing caught wrong error for WriteAllometryXMLErrorFile13.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteAllometryXMLErrorFile14());
    FAIL() << "TestAllometry error processing didn't catch error for WriteAllometryXMLErrorFile14.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clAllometry::GetData") != 0)
    {
      FAIL() << "TestAllometry error processing caught wrong error for WriteAllometryXMLErrorFile14.";
    }
    ;
  }
  delete p_oSimManager;
}

/////////////////////////////////////////////////////////////////////////////
// WriteAllometryCommonPlot()
/////////////////////////////////////////////////////////////////////////////
void WriteAllometryCommonPlot(std::fstream &oOut)
{

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06040101\">" << "<plot>"
       << "<timesteps>3</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>200.0</plot_lenX>"
       << "<plot_lenY>200.0</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>";
}

/////////////////////////////////////////////////////////////////////////////
// WriteAllometryCommonTrees()
/////////////////////////////////////////////////////////////////////////////
void WriteAllometryCommonTrees(std::fstream &oOut, const int &iNumSpp)
{

  int i;
  oOut << "<trees>"
      << "<tr_speciesList>";
  for (i = 0; i < iNumSpp; i++) {
    oOut << "<tr_species speciesName=\"Species_" << (i+1) << "\"/>";
  }
  oOut << "</tr_speciesList>"
      << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
      << "<tr_minAdultDBH>";
  for (i = 0; i < iNumSpp; i++) {
    oOut << "<tr_madVal species=\"Species_" << (i+1) << "\">10</tr_madVal>";
  }
  oOut << "</tr_minAdultDBH>"
      << "<tr_maxSeedlingHeight>";
  for (i = 0; i < iNumSpp; i++) {
      oOut << "<tr_mshVal species=\"Species_" << (i+1) << "\">1.35</tr_mshVal>";
    }
  oOut << "</tr_maxSeedlingHeight>"
      << "</trees>";
}

/////////////////////////////////////////////////////////////////////////////
// WriteAllometryCommonBehaviorList()
/////////////////////////////////////////////////////////////////////////////
void WriteAllometryCommonBehaviorList(std::fstream &oOut)
{

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>ConstantGLI</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\" />"
      << "</behavior>"
      << "</behaviorList>"
      << "<ConstantGLI1>"
      << "<li_constGLI>100</li_constGLI>"
      << "</ConstantGLI1>"
      << "</paramFile>";
}

/////////////////////////////////////////////////////////////////////////////
// WriteAllometryCommonErrorBlock1()
/////////////////////////////////////////////////////////////////////////////
void WriteAllometryCommonErrorBlock1(std::fstream &oOut)
{

  WriteAllometryCommonPlot(oOut);
  WriteAllometryCommonTrees(oOut, 2);

  oOut << "<allometry>"
      << "<tr_canopyHeight>"
      << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
      << "<tr_chVal species=\"Species_2\">39.54</tr_chVal>"
      << "</tr_canopyHeight>"
      << "<tr_stdAsympCrownRad>"
      << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_2\">0.0614</tr_sacrVal>"
      << "</tr_stdAsympCrownRad>"
      << "<tr_stdCrownRadExp>"
      << "<tr_screVal species=\"Species_1\">0.9</tr_screVal>"
      << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
      << "</tr_stdCrownRadExp>"
      << "<tr_stdMaxCrownRad>"
      << "<tr_smcrVal species=\"Species_1\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Species_2\">10</tr_smcrVal>"
      << "</tr_stdMaxCrownRad>"
      << "<tr_conversionDiam10ToDBH>"
      << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_2\">0.5944</tr_cdtdVal>"
      << "</tr_conversionDiam10ToDBH>"
      << "<tr_interceptDiam10ToDBH>"
      << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_2\">1</tr_idtdVal>"
      << "</tr_interceptDiam10ToDBH>"
      << "<tr_stdAsympCrownHt>"
      << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
      << "<tr_sachVal species=\"Species_2\">0.368</tr_sachVal>"
      << "</tr_stdAsympCrownHt>"
      << "<tr_stdCrownHtExp>"
      << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_2\">0.5</tr_scheVal>"
      << "</tr_stdCrownHtExp>"
      << "<tr_slopeOfHeight-Diam10>"
      << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_2\">0.03418</tr_sohdVal>"
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
      << "</tr_whatAdultHeightDiam>";
}

/////////////////////////////////////////////////////////////////////////////
// WriteAllometryCommonErrorBlock2()
/////////////////////////////////////////////////////////////////////////////
void WriteAllometryCommonErrorBlock2(std::fstream &oOut)
{
  WriteAllometryCommonPlot(oOut);
  WriteAllometryCommonTrees(oOut, 3);

  oOut << "<allometry>"
      << "<tr_canopyHeight>"
      << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
      << "<tr_chVal species=\"Species_2\">39.54</tr_chVal>"
      << "<tr_chVal species=\"Species_3\">45</tr_chVal>"
      << "</tr_canopyHeight>"
      << "<tr_stdAsympCrownRad>"
      << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_2\">0.0614</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_3\">0.02418</tr_sacrVal>"
      << "</tr_stdAsympCrownRad>"
      << "<tr_stdCrownRadExp>"
      << "<tr_screVal species=\"Species_1\">0.9</tr_screVal>"
      << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_3\">1.1</tr_screVal>"
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
      << "<tr_idtdVal species=\"Species_2\">1</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_3\">-0.2</tr_idtdVal>"
      << "</tr_interceptDiam10ToDBH>"
      << "<tr_stdAsympCrownHt>"
      << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
      << "<tr_sachVal species=\"Species_2\">0.368</tr_sachVal>"
      << "<tr_sachVal species=\"Species_3\">0.34</tr_sachVal>"
      << "</tr_stdAsympCrownHt>"
      << "<tr_stdCrownHtExp>"
      << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_2\">0.5</tr_scheVal>"
      << "<tr_scheVal species=\"Species_3\">0.9</tr_scheVal>"
      << "</tr_stdCrownHtExp>"
      << "<tr_slopeOfHeight-Diam10>"
      << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_2\">0.03418</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_3\">0.2871</tr_sohdVal>"
      << "</tr_slopeOfHeight-Diam10>"
      << "<tr_slopeOfAsymHeight>"
      << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
      << "<tr_soahVal species=\"Species_2\">0.0241</tr_soahVal>"
      << "<tr_soahVal species=\"Species_3\">0.0263</tr_soahVal>"
      << "</tr_slopeOfAsymHeight>"
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
      << "</tr_whatSaplingCrownHeightHeight>";
}

/////////////////////////////////////////////////////////////////////////////
// WriteAllometryCommonErrorBlock3()
/////////////////////////////////////////////////////////////////////////////
void WriteAllometryCommonErrorBlock3(std::fstream &oOut)
{
  WriteAllometryCommonPlot(oOut);
  WriteAllometryCommonTrees(oOut, 3);

  oOut << "<allometry>"
      << "<tr_canopyHeight>"
      << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
      << "<tr_chVal species=\"Species_2\">39.54</tr_chVal>"
      << "<tr_chVal species=\"Species_3\">45</tr_chVal>"
      << "</tr_canopyHeight>"
      << "<tr_stdAsympCrownRad>"
      << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_2\">0.0614</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_3\">0.02418</tr_sacrVal>"
      << "</tr_stdAsympCrownRad>"
      << "<tr_stdCrownRadExp>"
      << "<tr_screVal species=\"Species_1\">0.9</tr_screVal>"
      << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_3\">1.1</tr_screVal>"
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
      << "<tr_idtdVal species=\"Species_2\">1</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_3\">-0.2</tr_idtdVal>"
      << "</tr_interceptDiam10ToDBH>"
      << "<tr_stdAsympCrownHt>"
      << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
      << "<tr_sachVal species=\"Species_2\">0.368</tr_sachVal>"
      << "<tr_sachVal species=\"Species_3\">0.34</tr_sachVal>"
      << "</tr_stdAsympCrownHt>"
      << "<tr_stdCrownHtExp>"
      << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_2\">0.5</tr_scheVal>"
      << "<tr_scheVal species=\"Species_3\">0.9</tr_scheVal>"
      << "</tr_stdCrownHtExp>"
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
      << "</tr_whatSaplingCrownHeightHeight>";
}
/////////////////////////////////////////////////////////////////////////////
// WriteAllometryXMLFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteAllometryXMLFile1()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteAllometryCommonPlot(oOut);
  WriteAllometryCommonTrees(oOut, 6);

  oOut << "<allometry>"
      << "<tr_canopyHeight>"
      << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
      << "<tr_chVal species=\"Species_2\">39.54</tr_chVal>"
      << "<tr_chVal species=\"Species_3\">45</tr_chVal>"
      << "<tr_chVal species=\"Species_4\">39.48</tr_chVal>"
      << "<tr_chVal species=\"Species_5\">39.54</tr_chVal>"
      << "<tr_chVal species=\"Species_6\">45</tr_chVal>"
      << "</tr_canopyHeight>"
      << "<tr_stdAsympCrownRad>"
      << "<tr_sacrVal species=\"Species_1\">0.149</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_2\">0.0614</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_3\">0.2418</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_4\">0.0549</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_5\">0.0614</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_6\">0.02418</tr_sacrVal>"
      << "</tr_stdAsympCrownRad>"
      << "<tr_stdCrownRadExp>"
      << "<tr_screVal species=\"Species_1\">0.9</tr_screVal>"
      << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_3\">1.1</tr_screVal>"
      << "<tr_screVal species=\"Species_4\">0.9</tr_screVal>"
      << "<tr_screVal species=\"Species_5\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_6\">1.1</tr_screVal>"
      << "</tr_stdCrownRadExp>"
      << "<tr_stdMaxCrownRad>"
      << "<tr_smcrVal species=\"Species_1\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Species_2\">20</tr_smcrVal>"
      << "<tr_smcrVal species=\"Species_3\">30</tr_smcrVal>"
      << "<tr_smcrVal species=\"Species_5\">50</tr_smcrVal>"
      << "</tr_stdMaxCrownRad>"
      << "<tr_conversionDiam10ToDBH>"
      << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_2\">0.5944</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_3\">0.7059</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_4\">0.8008</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_5\">0.5944</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_6\">0.7059</tr_cdtdVal>"
      << "</tr_conversionDiam10ToDBH>"
      << "<tr_interceptDiam10ToDBH>"
      << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_2\">1</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_3\">-0.2</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_4\">0.3</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_5\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_6\">-3</tr_idtdVal>"
      << "</tr_interceptDiam10ToDBH>"
      << "<tr_stdAsympCrownHt>"
      << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
      << "<tr_sachVal species=\"Species_2\">0.368</tr_sachVal>"
      << "<tr_sachVal species=\"Species_3\">0.34</tr_sachVal>"
      << "<tr_sachVal species=\"Species_4\">0.389</tr_sachVal>"
      << "<tr_sachVal species=\"Species_5\">0.368</tr_sachVal>"
      << "<tr_sachVal species=\"Species_6\">0.34</tr_sachVal>"
      << "</tr_stdAsympCrownHt>"
      << "<tr_stdCrownHtExp>"
      << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_2\">0.5</tr_scheVal>"
      << "<tr_scheVal species=\"Species_3\">0.9</tr_scheVal>"
      << "<tr_scheVal species=\"Species_4\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_5\">0.5</tr_scheVal>"
      << "<tr_scheVal species=\"Species_6\">0.9</tr_scheVal>"
      << "</tr_stdCrownHtExp>"
      << "<tr_slopeOfHeight-Diam10>"
      << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_3\">0.2871</tr_sohdVal>"
      << "</tr_slopeOfHeight-Diam10>"
      << "<tr_slopeOfAsymHeight>"
      << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
      << "<tr_soahVal species=\"Species_2\">0.0241</tr_soahVal>"
      << "<tr_soahVal species=\"Species_3\">0.0263</tr_soahVal>"
      << "<tr_soahVal species=\"Species_6\">0.0263</tr_soahVal>"
      << "</tr_slopeOfAsymHeight>"
      << "<tr_whatSeedlingHeightDiam>"
      << "<tr_wsehdVal species=\"Species_1\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_2\">2</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_3\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_4\">1</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_5\">2</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_6\">1</tr_wsehdVal>"
      << "</tr_whatSeedlingHeightDiam>"
      << "<tr_whatSaplingHeightDiam>"
      << "<tr_wsahdVal species=\"Species_1\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_2\">1</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_3\">2</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_4\">3</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_5\">2</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_6\">0</tr_wsahdVal>"
      << "</tr_whatSaplingHeightDiam>"
      << "<tr_whatAdultHeightDiam>"
      << "<tr_wahdVal species=\"Species_1\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_2\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_3\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_4\">1</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_5\">2</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_6\">1</tr_wahdVal>"
      << "</tr_whatAdultHeightDiam>"
      << "<tr_whatAdultCrownRadDiam>"
      << "<tr_wacrdVal species=\"Species_1\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Species_2\">1</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Species_3\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Species_4\">1</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Species_5\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Species_6\">1</tr_wacrdVal>"
      << "</tr_whatAdultCrownRadDiam>"
      << "<tr_whatAdultCrownHeightHeight>"
      << "<tr_wachhVal species=\"Species_1\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Species_2\">1</tr_wachhVal>"
      << "<tr_wachhVal species=\"Species_3\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Species_4\">1</tr_wachhVal>"
      << "<tr_wachhVal species=\"Species_5\">1</tr_wachhVal>"
      << "<tr_wachhVal species=\"Species_6\">0</tr_wachhVal>"
      << "</tr_whatAdultCrownHeightHeight>"
      << "<tr_whatSaplingCrownRadDiam>"
      << "<tr_wscrdVal species=\"Species_1\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Species_2\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Species_3\">1</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Species_4\">1</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Species_5\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Species_6\">1</tr_wscrdVal>"
      << "</tr_whatSaplingCrownRadDiam>"
      << "<tr_whatSaplingCrownHeightHeight>"
      << "<tr_wschhVal species=\"Species_1\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Species_2\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Species_3\">1</tr_wschhVal>"
      << "<tr_wschhVal species=\"Species_4\">1</tr_wschhVal>"
      << "<tr_wschhVal species=\"Species_5\">1</tr_wschhVal>"
      << "<tr_wschhVal species=\"Species_6\">0</tr_wschhVal>"
      << "</tr_whatSaplingCrownHeightHeight>"
      << "<tr_adultLinearSlope>"
      << "<tr_alsVal species=\"Species_4\">0.96</tr_alsVal>"
      << "<tr_alsVal species=\"Species_6\">1.3</tr_alsVal>"
      << "</tr_adultLinearSlope>"
      << "<tr_adultLinearIntercept>"
      << "<tr_aliVal species=\"Species_4\">0</tr_aliVal>"
      << "<tr_aliVal species=\"Species_6\">-0.9</tr_aliVal>"
      << "</tr_adultLinearIntercept>"
      << "<tr_saplingLinearSlope>"
      << "<tr_salsVal species=\"Species_2\">0.492</tr_salsVal>"
      << "<tr_salsVal species=\"Species_4\">0.0549</tr_salsVal>"
      << "</tr_saplingLinearSlope>"
      << "<tr_saplingLinearIntercept>"
      << "<tr_saliVal species=\"Species_2\">1.2</tr_saliVal>"
      << "<tr_saliVal species=\"Species_4\">0</tr_saliVal>"
      << "</tr_saplingLinearIntercept>"
      << "<tr_seedlingLinearSlope>"
      << "<tr_selsVal species=\"Species_4\">0.9629</tr_selsVal>"
      << "<tr_selsVal species=\"Species_6\">1.228</tr_selsVal>"
      << "</tr_seedlingLinearSlope>"
      << "<tr_seedlingLinearIntercept>"
      << "<tr_seliVal species=\"Species_4\">0</tr_seliVal>"
      << "<tr_seliVal species=\"Species_6\">-0.9</tr_seliVal>"
      << "</tr_seedlingLinearIntercept>"
      << "<tr_adultReverseLinearSlope>"
      << "<tr_arlsVal species=\"Species_5\">2.1</tr_arlsVal>"
      << "</tr_adultReverseLinearSlope>"
      << "<tr_adultReverseLinearIntercept>"
      << "<tr_arliVal species=\"Species_5\">0.02418</tr_arliVal>"
      << "</tr_adultReverseLinearIntercept>"
      << "<tr_saplingReverseLinearSlope>"
      << "<tr_sarlsVal species=\"Species_5\">1.5</tr_sarlsVal>"
      << "<tr_sarlsVal species=\"Species_3\">1.1</tr_sarlsVal>"
      << "</tr_saplingReverseLinearSlope>"
      << "<tr_saplingReverseLinearIntercept>"
      << "<tr_sarliVal species=\"Species_5\">0.761</tr_sarliVal>"
      << "<tr_sarliVal species=\"Species_3\">-0.847</tr_sarliVal>"
      << "</tr_saplingReverseLinearIntercept>"
      << "<tr_seedlingReverseLinearSlope>"
      << "<tr_serlsVal species=\"Species_2\">1.5</tr_serlsVal>"
      << "<tr_serlsVal species=\"Species_5\">0.02</tr_serlsVal>"
      << "</tr_seedlingReverseLinearSlope>"
      << "<tr_seedlingReverseLinearIntercept>"
      << "<tr_serliVal species=\"Species_2\">0.761</tr_serliVal>"
      << "<tr_serliVal species=\"Species_5\">0.758</tr_serliVal>"
      << "</tr_seedlingReverseLinearIntercept>"
      << "<tr_chRichCrownRadIntercept>"
      << "<tr_crcriVal species=\"Species_2\">0.3</tr_crcriVal>"
      << "<tr_crcriVal species=\"Species_3\">0.4</tr_crcriVal>"
      << "<tr_crcriVal species=\"Species_4\">0.5</tr_crcriVal>"
      << "<tr_crcriVal species=\"Species_6\">0.7</tr_crcriVal>"
      << "</tr_chRichCrownRadIntercept>"
      << "<tr_chRichCrownRadAsymp>"
      << "<tr_crcraVal species=\"Species_2\">8</tr_crcraVal>"
      << "<tr_crcraVal species=\"Species_3\">7</tr_crcraVal>"
      << "<tr_crcraVal species=\"Species_4\">10</tr_crcraVal>"
      << "<tr_crcraVal species=\"Species_6\">9.2</tr_crcraVal>"
      << "</tr_chRichCrownRadAsymp>"
      << "<tr_chRichCrownRadShape1b>"
      << "<tr_crcrs1bVal species=\"Species_2\">0.09</tr_crcrs1bVal>"
      << "<tr_crcrs1bVal species=\"Species_3\">0.1</tr_crcrs1bVal>"
      << "<tr_crcrs1bVal species=\"Species_4\">0.11</tr_crcrs1bVal>"
      << "<tr_crcrs1bVal species=\"Species_6\">0.2</tr_crcrs1bVal>"
      << "</tr_chRichCrownRadShape1b>"
      << "<tr_chRichCrownRadShape2c>"
      << "<tr_crcrs2cVal species=\"Species_2\">1.5</tr_crcrs2cVal>"
      << "<tr_crcrs2cVal species=\"Species_3\">2.4</tr_crcrs2cVal>"
      << "<tr_crcrs2cVal species=\"Species_4\">2.8</tr_crcrs2cVal>"
      << "<tr_crcrs2cVal species=\"Species_6\">1.9</tr_crcrs2cVal>"
      << "</tr_chRichCrownRadShape2c>"
      << "<tr_chRichCrownHtIntercept>"
      << "<tr_crchiVal species=\"Species_2\">0.6</tr_crchiVal>"
      << "<tr_crchiVal species=\"Species_3\">0.5</tr_crchiVal>"
      << "<tr_crchiVal species=\"Species_4\">0.4</tr_crchiVal>"
      << "<tr_crchiVal species=\"Species_5\">0.3</tr_crchiVal>"
      << "</tr_chRichCrownHtIntercept>"
      << "<tr_chRichCrownHtAsymp>"
      << "<tr_crchaVal species=\"Species_2\">60</tr_crchaVal>"
      << "<tr_crchaVal species=\"Species_3\">12</tr_crchaVal>"
      << "<tr_crchaVal species=\"Species_4\">13</tr_crchaVal>"
      << "<tr_crchaVal species=\"Species_5\">14</tr_crchaVal>"
      << "</tr_chRichCrownHtAsymp>"
      << "<tr_chRichCrownHtShape1b>"
      << "<tr_crchs1bVal species=\"Species_2\">0.3</tr_crchs1bVal>"
      << "<tr_crchs1bVal species=\"Species_3\">0.1</tr_crchs1bVal>"
      << "<tr_crchs1bVal species=\"Species_4\">0.12</tr_crchs1bVal>"
      << "<tr_crchs1bVal species=\"Species_5\">0.16</tr_crchs1bVal>"
      << "</tr_chRichCrownHtShape1b>"
      << "<tr_chRichCrownHtShape2c>"
      << "<tr_crchs2cVal species=\"Species_2\">3.2</tr_crchs2cVal>"
      << "<tr_crchs2cVal species=\"Species_3\">4.1</tr_crchs2cVal>"
      << "<tr_crchs2cVal species=\"Species_4\">2.9</tr_crchs2cVal>"
      << "<tr_crchs2cVal species=\"Species_5\">3.5</tr_crchs2cVal>"
      << "</tr_chRichCrownHtShape2c>"
      << "<tr_saplingPowerA>"
      << "<tr_sapaVal species=\"Species_4\">1.7019</tr_sapaVal>"
      << "</tr_saplingPowerA>"
      << "<tr_saplingPowerB>"
      << "<tr_sapbVal species=\"Species_4\">0.75</tr_sapbVal>"
      << "</tr_saplingPowerB>"
      << "</allometry>";

  WriteAllometryCommonBehaviorList(oOut);

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteAllometryXMLFile2()
/////////////////////////////////////////////////////////////////////////////
const char* WriteAllometryXMLFile2()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteAllometryCommonPlot(oOut);
  WriteAllometryCommonTrees(oOut, 3);

  oOut << "<allometry>"
      << "<tr_canopyHeight>"
      << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
      << "<tr_chVal species=\"Species_2\">39.54</tr_chVal>"
      << "<tr_chVal species=\"Species_3\">45</tr_chVal>"
      << "</tr_canopyHeight>"
      << "<tr_stdAsympCrownRad>"
      << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_2\">0.0614</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_3\">0.02418</tr_sacrVal>"
      << "</tr_stdAsympCrownRad>"
      << "<tr_stdCrownRadExp>"
      << "<tr_screVal species=\"Species_1\">0.9</tr_screVal>"
      << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_3\">1.1</tr_screVal>"
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
      << "<tr_idtdVal species=\"Species_2\">1</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_3\">-0.2</tr_idtdVal>"
      << "</tr_interceptDiam10ToDBH>"
      << "<tr_stdAsympCrownHt>"
      << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
      << "<tr_sachVal species=\"Species_2\">0.368</tr_sachVal>"
      << "<tr_sachVal species=\"Species_3\">0.34</tr_sachVal>"
      << "</tr_stdAsympCrownHt>"
      << "<tr_stdCrownHtExp>"
      << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_2\">0.5</tr_scheVal>"
      << "<tr_scheVal species=\"Species_3\">0.9</tr_scheVal>"
      << "</tr_stdCrownHtExp>"
      << "<tr_slopeOfHeight-Diam10>"
      << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_2\">0.03418</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_3\">0.2871</tr_sohdVal>"
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

  WriteAllometryCommonBehaviorList(oOut);

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteAllometryXMLFile3()
/////////////////////////////////////////////////////////////////////////////
const char* WriteAllometryXMLFile3()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteAllometryCommonPlot(oOut);
  WriteAllometryCommonTrees(oOut, 3);

  oOut << "<allometry>"
      << "<tr_canopyHeight>"
      << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
      << "<tr_chVal species=\"Species_2\">39.54</tr_chVal>"
      << "<tr_chVal species=\"Species_3\">45</tr_chVal>"
      << "</tr_canopyHeight>"
      << "<tr_stdAsympCrownRad>"
      << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_2\">0.0614</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_3\">0.02418</tr_sacrVal>"
      << "</tr_stdAsympCrownRad>"
      << "<tr_stdCrownRadExp>"
      << "<tr_screVal species=\"Species_1\">0.9</tr_screVal>"
      << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_3\">1.1</tr_screVal>"
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
      << "<tr_idtdVal species=\"Species_2\">1</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_3\">-0.2</tr_idtdVal>"
      << "</tr_interceptDiam10ToDBH>"
      << "<tr_stdAsympCrownHt>"
      << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
      << "<tr_sachVal species=\"Species_2\">0.368</tr_sachVal>"
      << "<tr_sachVal species=\"Species_3\">0.34</tr_sachVal>"
      << "</tr_stdAsympCrownHt>"
      << "<tr_stdCrownHtExp>"
      << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_2\">0.5</tr_scheVal>"
      << "<tr_scheVal species=\"Species_3\">0.9</tr_scheVal>"
      << "</tr_stdCrownHtExp>"
      << "<tr_whatSeedlingHeightDiam>"
      << "<tr_wsehdVal species=\"Species_1\">1</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_2\">1</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_3\">1</tr_wsehdVal>"
      << "</tr_whatSeedlingHeightDiam>"
      << "<tr_whatSaplingHeightDiam>"
      << "<tr_wsahdVal species=\"Species_1\">1</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_2\">1</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_3\">1</tr_wsahdVal>"
      << "</tr_whatSaplingHeightDiam>"
      << "<tr_whatAdultHeightDiam>"
      << "<tr_wahdVal species=\"Species_1\">1</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_2\">1</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_3\">1</tr_wahdVal>"
      << "</tr_whatAdultHeightDiam>"
      << "<tr_whatAdultCrownRadDiam>"
      << "<tr_wacrdVal species=\"Species_1\">1</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Species_2\">1</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Species_3\">1</tr_wacrdVal>"
      << "</tr_whatAdultCrownRadDiam>"
      << "<tr_whatAdultCrownHeightHeight>"
      << "<tr_wachhVal species=\"Species_1\">1</tr_wachhVal>"
      << "<tr_wachhVal species=\"Species_2\">1</tr_wachhVal>"
      << "<tr_wachhVal species=\"Species_3\">1</tr_wachhVal>"
      << "</tr_whatAdultCrownHeightHeight>"
      << "<tr_whatSaplingCrownRadDiam>"
      << "<tr_wscrdVal species=\"Species_1\">1</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Species_2\">1</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Species_3\">1</tr_wscrdVal>"
      << "</tr_whatSaplingCrownRadDiam>"
      << "<tr_whatSaplingCrownHeightHeight>"
      << "<tr_wschhVal species=\"Species_1\">1</tr_wschhVal>"
      << "<tr_wschhVal species=\"Species_2\">1</tr_wschhVal>"
      << "<tr_wschhVal species=\"Species_3\">1</tr_wschhVal>"
      << "</tr_whatSaplingCrownHeightHeight>"
      << "<tr_adultLinearSlope>"
      << "<tr_alsVal species=\"Species_1\">0.96</tr_alsVal>"
      << "<tr_alsVal species=\"Species_2\">0.96</tr_alsVal>"
      << "<tr_alsVal species=\"Species_3\">1.3</tr_alsVal>"
      << "</tr_adultLinearSlope>"
      << "<tr_adultLinearIntercept>"
      << "<tr_aliVal species=\"Species_1\">0</tr_aliVal>"
      << "<tr_aliVal species=\"Species_2\">0</tr_aliVal>"
      << "<tr_aliVal species=\"Species_3\">0.9</tr_aliVal>"
      << "</tr_adultLinearIntercept>"
      << "<tr_saplingLinearSlope>"
      << "<tr_salsVal species=\"Species_2\">49.82</tr_salsVal>"
      << "<tr_salsVal species=\"Species_1\">0.0549</tr_salsVal>"
      << "<tr_salsVal species=\"Species_3\">0.0549</tr_salsVal>"
      << "</tr_saplingLinearSlope>"
      << "<tr_saplingLinearIntercept>"
      << "<tr_saliVal species=\"Species_1\">1.2</tr_saliVal>"
      << "<tr_saliVal species=\"Species_2\">1.2</tr_saliVal>"
      << "<tr_saliVal species=\"Species_3\">0</tr_saliVal>"
      << "</tr_saplingLinearIntercept>"
      << "<tr_seedlingLinearSlope>"
      << "<tr_selsVal species=\"Species_1\">96.29</tr_selsVal>"
      << "<tr_selsVal species=\"Species_2\">96.29</tr_selsVal>"
      << "<tr_selsVal species=\"Species_3\">122.86</tr_selsVal>"
      << "</tr_seedlingLinearSlope>"
      << "<tr_seedlingLinearIntercept>"
      << "<tr_seliVal species=\"Species_1\">0</tr_seliVal>"
      << "<tr_seliVal species=\"Species_2\">0</tr_seliVal>"
      << "<tr_seliVal species=\"Species_3\">-0.9</tr_seliVal>"
      << "</tr_seedlingLinearIntercept>"
      << "<tr_chRichCrownRadIntercept>"
      << "<tr_crcriVal species=\"Species_2\">0.3</tr_crcriVal>"
      << "<tr_crcriVal species=\"Species_3\">0.4</tr_crcriVal>"
      << "<tr_crcriVal species=\"Species_1\">0.5</tr_crcriVal>"
      << "</tr_chRichCrownRadIntercept>"
      << "<tr_chRichCrownRadAsymp>"
      << "<tr_crcraVal species=\"Species_2\">8</tr_crcraVal>"
      << "<tr_crcraVal species=\"Species_3\">7</tr_crcraVal>"
      << "<tr_crcraVal species=\"Species_1\">9</tr_crcraVal>"
      << "</tr_chRichCrownRadAsymp>"
      << "<tr_chRichCrownRadShape1b>"
      << "<tr_crcrs1bVal species=\"Species_2\">0.09</tr_crcrs1bVal>"
      << "<tr_crcrs1bVal species=\"Species_3\">0.1</tr_crcrs1bVal>"
      << "<tr_crcrs1bVal species=\"Species_1\">0.11</tr_crcrs1bVal>"
      << "</tr_chRichCrownRadShape1b>"
      << "<tr_chRichCrownRadShape2c>"
      << "<tr_crcrs2cVal species=\"Species_2\">1.5</tr_crcrs2cVal>"
      << "<tr_crcrs2cVal species=\"Species_3\">2.4</tr_crcrs2cVal>"
      << "<tr_crcrs2cVal species=\"Species_1\">2.8</tr_crcrs2cVal>"
      << "</tr_chRichCrownRadShape2c>"
      << "<tr_chRichCrownHtIntercept>"
      << "<tr_crchiVal species=\"Species_2\">0.6</tr_crchiVal>"
      << "<tr_crchiVal species=\"Species_3\">0.5</tr_crchiVal>"
      << "<tr_crchiVal species=\"Species_1\">0.4</tr_crchiVal>"
      << "</tr_chRichCrownHtIntercept>"
      << "<tr_chRichCrownHtAsymp>"
      << "<tr_crchaVal species=\"Species_2\">60</tr_crchaVal>"
      << "<tr_crchaVal species=\"Species_3\">12</tr_crchaVal>"
      << "<tr_crchaVal species=\"Species_1\">13</tr_crchaVal>"
      << "</tr_chRichCrownHtAsymp>"
      << "<tr_chRichCrownHtShape1b>"
      << "<tr_crchs1bVal species=\"Species_2\">0.3</tr_crchs1bVal>"
      << "<tr_crchs1bVal species=\"Species_3\">0.1</tr_crchs1bVal>"
      << "<tr_crchs1bVal species=\"Species_1\">0.12</tr_crchs1bVal>"
      << "</tr_chRichCrownHtShape1b>"
      << "<tr_chRichCrownHtShape2c>"
      << "<tr_crchs2cVal species=\"Species_2\">3.2</tr_crchs2cVal>"
      << "<tr_crchs2cVal species=\"Species_3\">4.1</tr_crchs2cVal>"
      << "<tr_crchs2cVal species=\"Species_1\">2.9</tr_crchs2cVal>"
      << "</tr_chRichCrownHtShape2c>"
      << "</allometry>";

  WriteAllometryCommonBehaviorList(oOut);

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteAllometryXMLFile4()
/////////////////////////////////////////////////////////////////////////////
const char* WriteAllometryXMLFile4()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteAllometryCommonPlot(oOut);
  WriteAllometryCommonTrees(oOut, 3);

  oOut << "<allometry>"
      << "<tr_canopyHeight>"
      << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
      << "<tr_chVal species=\"Species_2\">39.54</tr_chVal>"
      << "<tr_chVal species=\"Species_3\">45</tr_chVal>"
      << "</tr_canopyHeight>"
      << "<tr_stdAsympCrownRad>"
      << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_2\">0.0614</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_3\">0.02418</tr_sacrVal>"
      << "</tr_stdAsympCrownRad>"
      << "<tr_stdCrownRadExp>"
      << "<tr_screVal species=\"Species_1\">0.9</tr_screVal>"
      << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_3\">1.1</tr_screVal>"
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
      << "<tr_idtdVal species=\"Species_2\">1</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_3\">-0.2</tr_idtdVal>"
      << "</tr_interceptDiam10ToDBH>"
      << "<tr_stdAsympCrownHt>"
      << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
      << "<tr_sachVal species=\"Species_2\">0.368</tr_sachVal>"
      << "<tr_sachVal species=\"Species_3\">0.34</tr_sachVal>"
      << "</tr_stdAsympCrownHt>"
      << "<tr_stdCrownHtExp>"
      << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_2\">0.5</tr_scheVal>"
      << "<tr_scheVal species=\"Species_3\">0.9</tr_scheVal>"
      << "</tr_stdCrownHtExp>"
      << "<tr_slopeOfHeight-Diam10>"
      << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_2\">0.03418</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_3\">0.2871</tr_sohdVal>"
      << "</tr_slopeOfHeight-Diam10>"
      << "<tr_whatSeedlingHeightDiam>"
      << "<tr_wsehdVal species=\"Species_1\">2</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_2\">2</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_3\">2</tr_wsehdVal>"
      << "</tr_whatSeedlingHeightDiam>"
      << "<tr_whatSaplingHeightDiam>"
      << "<tr_wsahdVal species=\"Species_1\">2</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_2\">2</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_3\">2</tr_wsahdVal>"
      << "</tr_whatSaplingHeightDiam>"
      << "<tr_whatAdultHeightDiam>"
      << "<tr_wahdVal species=\"Species_1\">2</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_2\">2</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_3\">2</tr_wahdVal>"
      << "</tr_whatAdultHeightDiam>"
      << "<tr_adultReverseLinearSlope>"
      << "<tr_arlsVal species=\"Species_1\">2.1</tr_arlsVal>"
      << "<tr_arlsVal species=\"Species_2\">2.1</tr_arlsVal>"
      << "<tr_arlsVal species=\"Species_3\">2.1</tr_arlsVal>"
      << "</tr_adultReverseLinearSlope>"
      << "<tr_adultReverseLinearIntercept>"
      << "<tr_arliVal species=\"Species_1\">0.02418</tr_arliVal>"
      << "<tr_arliVal species=\"Species_2\">0.02418</tr_arliVal>"
      << "<tr_arliVal species=\"Species_3\">0.02418</tr_arliVal>"
      << "</tr_adultReverseLinearIntercept>"
      << "<tr_saplingReverseLinearSlope>"
      << "<tr_sarlsVal species=\"Species_1\">1.5</tr_sarlsVal>"
      << "<tr_sarlsVal species=\"Species_2\">1.5</tr_sarlsVal>"
      << "<tr_sarlsVal species=\"Species_3\">1.1</tr_sarlsVal>"
      << "</tr_saplingReverseLinearSlope>"
      << "<tr_saplingReverseLinearIntercept>"
      << "<tr_sarliVal species=\"Species_1\">0.761</tr_sarliVal>"
      << "<tr_sarliVal species=\"Species_2\">0.761</tr_sarliVal>"
      << "<tr_sarliVal species=\"Species_3\">-0.847</tr_sarliVal>"
      << "</tr_saplingReverseLinearIntercept>"
      << "<tr_seedlingReverseLinearSlope>"
      << "<tr_serlsVal species=\"Species_2\">1.5</tr_serlsVal>"
      << "<tr_serlsVal species=\"Species_1\">0.761</tr_serlsVal>"
      << "<tr_serlsVal species=\"Species_3\">0.761</tr_serlsVal>"
      << "</tr_seedlingReverseLinearSlope>"
      << "<tr_seedlingReverseLinearIntercept>"
      << "<tr_serliVal species=\"Species_2\">0.02</tr_serliVal>"
      << "<tr_serliVal species=\"Species_1\">0.758</tr_serliVal>"
      << "<tr_serliVal species=\"Species_3\">0.758</tr_serliVal>"
      << "</tr_seedlingReverseLinearIntercept>"
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

  WriteAllometryCommonBehaviorList(oOut);

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteAllometryXMLErrorFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteAllometryXMLErrorFile1()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteAllometryCommonErrorBlock2(oOut);

  oOut << "<tr_whatSeedlingHeightDiam>"
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
      << "<tr_wahdVal species=\"Species_2\">4</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_3\">0</tr_wahdVal>"
      << "</tr_whatAdultHeightDiam>"
      << "</allometry>";

  WriteAllometryCommonBehaviorList(oOut);

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteAllometryXMLErrorFile2()
/////////////////////////////////////////////////////////////////////////////
const char* WriteAllometryXMLErrorFile2()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteAllometryCommonErrorBlock2(oOut);

  oOut << "<tr_whatSeedlingHeightDiam>"
      << "<tr_wsehdVal species=\"Species_1\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_2\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_3\">0</tr_wsehdVal>"
      << "</tr_whatSeedlingHeightDiam>"
      << "<tr_whatSaplingHeightDiam>"
      << "<tr_wsahdVal species=\"Species_1\">-1</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_2\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_3\">0</tr_wsahdVal>"
      << "</tr_whatSaplingHeightDiam>"
      << "<tr_whatAdultHeightDiam>"
      << "<tr_wahdVal species=\"Species_1\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_2\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_3\">0</tr_wahdVal>"
      << "</tr_whatAdultHeightDiam>"
      << "</allometry>";

  WriteAllometryCommonBehaviorList(oOut);

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteAllometryXMLErrorFile3()
/////////////////////////////////////////////////////////////////////////////
const char* WriteAllometryXMLErrorFile3()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteAllometryCommonErrorBlock2(oOut);

  oOut << "<tr_whatSeedlingHeightDiam>"
      << "<tr_wsehdVal species=\"Species_1\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_2\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_3\">4</tr_wsehdVal>"
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
      << "</allometry>";

  WriteAllometryCommonBehaviorList(oOut);

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteAllometryXMLErrorFile4()
/////////////////////////////////////////////////////////////////////////////
const char* WriteAllometryXMLErrorFile4()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteAllometryCommonErrorBlock3(oOut);

  oOut << "<tr_whatSeedlingHeightDiam>"
      << "<tr_wsehdVal species=\"Species_1\">1</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_2\">1</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_3\">1</tr_wsehdVal>"
      << "</tr_whatSeedlingHeightDiam>"
      << "<tr_whatSaplingHeightDiam>"
      << "<tr_wsahdVal species=\"Species_1\">1</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_2\">1</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_3\">1</tr_wsahdVal>"
      << "</tr_whatSaplingHeightDiam>"
      << "<tr_whatAdultHeightDiam>"
      << "<tr_wahdVal species=\"Species_1\">1</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_2\">1</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_3\">1</tr_wahdVal>"
      << "</tr_whatAdultHeightDiam>"
      << "<tr_adultLinearSlope>"
      << "<tr_alsVal species=\"Species_1\">0.96</tr_alsVal>"
      << "<tr_alsVal species=\"Species_2\">0</tr_alsVal>"
      << "<tr_alsVal species=\"Species_3\">1.3</tr_alsVal>"
      << "</tr_adultLinearSlope>"
      << "<tr_adultLinearIntercept>"
      << "<tr_aliVal species=\"Species_1\">0</tr_aliVal>"
      << "<tr_aliVal species=\"Species_2\">0</tr_aliVal>"
      << "<tr_aliVal species=\"Species_3\">0.9</tr_aliVal>"
      << "</tr_adultLinearIntercept>"
      << "<tr_saplingLinearSlope>"
      << "<tr_salsVal species=\"Species_2\">49.82</tr_salsVal>"
      << "<tr_salsVal species=\"Species_1\">0.0549</tr_salsVal>"
      << "<tr_salsVal species=\"Species_3\">0.0549</tr_salsVal>"
      << "</tr_saplingLinearSlope>"
      << "<tr_saplingLinearIntercept>"
      << "<tr_saliVal species=\"Species_1\">1.2</tr_saliVal>"
      << "<tr_saliVal species=\"Species_2\">1.2</tr_saliVal>"
      << "<tr_saliVal species=\"Species_3\">0</tr_saliVal>"
      << "</tr_saplingLinearIntercept>"
      << "<tr_seedlingLinearSlope>"
      << "<tr_selsVal species=\"Species_1\">96.29</tr_selsVal>"
      << "<tr_selsVal species=\"Species_2\">96.29</tr_selsVal>"
      << "<tr_selsVal species=\"Species_3\">122.86</tr_selsVal>"
      << "</tr_seedlingLinearSlope>"
      << "<tr_seedlingLinearIntercept>"
      << "<tr_seliVal species=\"Species_1\">0</tr_seliVal>"
      << "<tr_seliVal species=\"Species_2\">0</tr_seliVal>"
      << "<tr_seliVal species=\"Species_3\">-0.9</tr_seliVal>"
      << "</tr_seedlingLinearIntercept>"
      << "</allometry>";

  WriteAllometryCommonBehaviorList(oOut);

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteAllometryXMLErrorFile5()
/////////////////////////////////////////////////////////////////////////////
const char* WriteAllometryXMLErrorFile5()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteAllometryCommonErrorBlock3(oOut);

  oOut << "<tr_whatSeedlingHeightDiam>"
      << "<tr_wsehdVal species=\"Species_1\">2</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_2\">2</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_3\">2</tr_wsehdVal>"
      << "</tr_whatSeedlingHeightDiam>"
      << "<tr_whatSaplingHeightDiam>"
      << "<tr_wsahdVal species=\"Species_1\">2</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_2\">2</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_3\">2</tr_wsahdVal>"
      << "</tr_whatSaplingHeightDiam>"
      << "<tr_whatAdultHeightDiam>"
      << "<tr_wahdVal species=\"Species_1\">2</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_2\">2</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_3\">2</tr_wahdVal>"
      << "</tr_whatAdultHeightDiam>"
      << "<tr_adultReverseLinearSlope>"
      << "<tr_arlsVal species=\"Species_1\">2.1</tr_arlsVal>"
      << "<tr_arlsVal species=\"Species_2\">2.1</tr_arlsVal>"
      << "<tr_arlsVal species=\"Species_3\">2.1</tr_arlsVal>"
      << "</tr_adultReverseLinearSlope>"
      << "<tr_adultReverseLinearIntercept>"
      << "<tr_arliVal species=\"Species_1\">0.02418</tr_arliVal>"
      << "<tr_arliVal species=\"Species_2\">0.02418</tr_arliVal>"
      << "<tr_arliVal species=\"Species_3\">0.02418</tr_arliVal>"
      << "</tr_adultReverseLinearIntercept>"
      << "<tr_saplingReverseLinearSlope>"
      << "<tr_sarlsVal species=\"Species_1\">0</tr_sarlsVal>"
      << "<tr_sarlsVal species=\"Species_2\">1.5</tr_sarlsVal>"
      << "<tr_sarlsVal species=\"Species_3\">1.1</tr_sarlsVal>"
      << "</tr_saplingReverseLinearSlope>"
      << "<tr_saplingReverseLinearIntercept>"
      << "<tr_sarliVal species=\"Species_1\">0.761</tr_sarliVal>"
      << "<tr_sarliVal species=\"Species_2\">0.761</tr_sarliVal>"
      << "<tr_sarliVal species=\"Species_3\">-0.847</tr_sarliVal>"
      << "</tr_saplingReverseLinearIntercept>"
      << "<tr_seedlingReverseLinearSlope>"
      << "<tr_serlsVal species=\"Species_2\">1.5</tr_serlsVal>"
      << "<tr_serlsVal species=\"Species_1\">0.761</tr_serlsVal>"
      << "<tr_serlsVal species=\"Species_3\">0.761</tr_serlsVal>"
      << "</tr_seedlingReverseLinearSlope>"
      << "<tr_seedlingReverseLinearIntercept>"
      << "<tr_serliVal species=\"Species_2\">0.02</tr_serliVal>"
      << "<tr_serliVal species=\"Species_1\">0.758</tr_serliVal>"
      << "<tr_serliVal species=\"Species_3\">0.758</tr_serliVal>"
      << "</tr_seedlingReverseLinearIntercept>"
      << "</allometry>";

  WriteAllometryCommonBehaviorList(oOut);

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteAllometryXMLErrorFile6()
/////////////////////////////////////////////////////////////////////////////
const char* WriteAllometryXMLErrorFile6()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteAllometryCommonErrorBlock3(oOut);

  oOut << "<tr_whatSeedlingHeightDiam>"
      << "<tr_wsehdVal species=\"Species_1\">1</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_2\">1</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_3\">1</tr_wsehdVal>"
      << "</tr_whatSeedlingHeightDiam>"
      << "<tr_whatSaplingHeightDiam>"
      << "<tr_wsahdVal species=\"Species_1\">1</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_2\">1</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_3\">1</tr_wsahdVal>"
      << "</tr_whatSaplingHeightDiam>"
      << "<tr_whatAdultHeightDiam>"
      << "<tr_wahdVal species=\"Species_1\">1</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_2\">1</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_3\">1</tr_wahdVal>"
      << "</tr_whatAdultHeightDiam>"
      << "<tr_adultLinearSlope>"
      << "<tr_alsVal species=\"Species_1\">0.96</tr_alsVal>"
      << "<tr_alsVal species=\"Species_2\">0.96</tr_alsVal>"
      << "<tr_alsVal species=\"Species_3\">1.3</tr_alsVal>"
      << "</tr_adultLinearSlope>"
      << "<tr_adultLinearIntercept>"
      << "<tr_aliVal species=\"Species_1\">0</tr_aliVal>"
      << "<tr_aliVal species=\"Species_2\">0</tr_aliVal>"
      << "<tr_aliVal species=\"Species_3\">0.9</tr_aliVal>"
      << "</tr_adultLinearIntercept>"
      << "<tr_saplingLinearSlope>"
      << "<tr_salsVal species=\"Species_2\">0</tr_salsVal>"
      << "<tr_salsVal species=\"Species_1\">0.0549</tr_salsVal>"
      << "<tr_salsVal species=\"Species_3\">0.0549</tr_salsVal>"
      << "</tr_saplingLinearSlope>"
      << "<tr_saplingLinearIntercept>"
      << "<tr_saliVal species=\"Species_1\">1.2</tr_saliVal>"
      << "<tr_saliVal species=\"Species_2\">1.2</tr_saliVal>"
      << "<tr_saliVal species=\"Species_3\">0</tr_saliVal>"
      << "</tr_saplingLinearIntercept>"
      << "<tr_seedlingLinearSlope>"
      << "<tr_selsVal species=\"Species_1\">96.29</tr_selsVal>"
      << "<tr_selsVal species=\"Species_2\">96.29</tr_selsVal>"
      << "<tr_selsVal species=\"Species_3\">122.86</tr_selsVal>"
      << "</tr_seedlingLinearSlope>"
      << "<tr_seedlingLinearIntercept>"
      << "<tr_seliVal species=\"Species_1\">0</tr_seliVal>"
      << "<tr_seliVal species=\"Species_2\">0</tr_seliVal>"
      << "<tr_seliVal species=\"Species_3\">-0.9</tr_seliVal>"
      << "</tr_seedlingLinearIntercept>"
      << "</allometry>";

  WriteAllometryCommonBehaviorList(oOut);

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteAllometryXMLErrorFile7()
/////////////////////////////////////////////////////////////////////////////
const char* WriteAllometryXMLErrorFile7()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteAllometryCommonErrorBlock3(oOut);

  oOut << "<tr_whatSeedlingHeightDiam>"
      << "<tr_wsehdVal species=\"Species_1\">2</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_2\">2</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_3\">2</tr_wsehdVal>"
      << "</tr_whatSeedlingHeightDiam>"
      << "<tr_whatSaplingHeightDiam>"
      << "<tr_wsahdVal species=\"Species_1\">2</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_2\">2</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_3\">2</tr_wsahdVal>"
      << "</tr_whatSaplingHeightDiam>"
      << "<tr_whatAdultHeightDiam>"
      << "<tr_wahdVal species=\"Species_1\">2</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_2\">2</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_3\">2</tr_wahdVal>"
      << "</tr_whatAdultHeightDiam>"
      << "<tr_adultReverseLinearSlope>"
      << "<tr_arlsVal species=\"Species_1\">2.1</tr_arlsVal>"
      << "<tr_arlsVal species=\"Species_2\">2.1</tr_arlsVal>"
      << "<tr_arlsVal species=\"Species_3\">2.1</tr_arlsVal>"
      << "</tr_adultReverseLinearSlope>"
      << "<tr_adultReverseLinearIntercept>"
      << "<tr_arliVal species=\"Species_1\">0.02418</tr_arliVal>"
      << "<tr_arliVal species=\"Species_2\">0.02418</tr_arliVal>"
      << "<tr_arliVal species=\"Species_3\">0.02418</tr_arliVal>"
      << "</tr_adultReverseLinearIntercept>"
      << "<tr_saplingReverseLinearSlope>"
      << "<tr_sarlsVal species=\"Species_1\">1.5</tr_sarlsVal>"
      << "<tr_sarlsVal species=\"Species_2\">1.5</tr_sarlsVal>"
      << "<tr_sarlsVal species=\"Species_3\">0</tr_sarlsVal>"
      << "</tr_saplingReverseLinearSlope>"
      << "<tr_saplingReverseLinearIntercept>"
      << "<tr_sarliVal species=\"Species_1\">0.761</tr_sarliVal>"
      << "<tr_sarliVal species=\"Species_2\">0.761</tr_sarliVal>"
      << "<tr_sarliVal species=\"Species_3\">-0.847</tr_sarliVal>"
      << "</tr_saplingReverseLinearIntercept>"
      << "<tr_seedlingReverseLinearSlope>"
      << "<tr_serlsVal species=\"Species_2\">1.5</tr_serlsVal>"
      << "<tr_serlsVal species=\"Species_1\">0.761</tr_serlsVal>"
      << "<tr_serlsVal species=\"Species_3\">0.761</tr_serlsVal>"
      << "</tr_seedlingReverseLinearSlope>"
      << "<tr_seedlingReverseLinearIntercept>"
      << "<tr_serliVal species=\"Species_2\">0.02</tr_serliVal>"
      << "<tr_serliVal species=\"Species_1\">0.758</tr_serliVal>"
      << "<tr_serliVal species=\"Species_3\">0.758</tr_serliVal>"
      << "</tr_seedlingReverseLinearIntercept>"
      << "</allometry>";

  WriteAllometryCommonBehaviorList(oOut);

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteAllometryXMLErrorFile8()
/////////////////////////////////////////////////////////////////////////////
const char* WriteAllometryXMLErrorFile8()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteAllometryCommonErrorBlock3(oOut);

  oOut << "<tr_whatSeedlingHeightDiam>"
      << "<tr_wsehdVal species=\"Species_1\">1</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_2\">1</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_3\">1</tr_wsehdVal>"
      << "</tr_whatSeedlingHeightDiam>"
      << "<tr_whatSaplingHeightDiam>"
      << "<tr_wsahdVal species=\"Species_1\">1</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_2\">1</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_3\">1</tr_wsahdVal>"
      << "</tr_whatSaplingHeightDiam>"
      << "<tr_whatAdultHeightDiam>"
      << "<tr_wahdVal species=\"Species_1\">1</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_2\">1</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_3\">1</tr_wahdVal>"
      << "</tr_whatAdultHeightDiam>"
      << "<tr_adultLinearSlope>"
      << "<tr_alsVal species=\"Species_1\">0.96</tr_alsVal>"
      << "<tr_alsVal species=\"Species_2\">0.96</tr_alsVal>"
      << "<tr_alsVal species=\"Species_3\">1.3</tr_alsVal>"
      << "</tr_adultLinearSlope>"
      << "<tr_adultLinearIntercept>"
      << "<tr_aliVal species=\"Species_1\">0</tr_aliVal>"
      << "<tr_aliVal species=\"Species_2\">0</tr_aliVal>"
      << "<tr_aliVal species=\"Species_3\">0.9</tr_aliVal>"
      << "</tr_adultLinearIntercept>"
      << "<tr_saplingLinearSlope>"
      << "<tr_salsVal species=\"Species_2\">49.82</tr_salsVal>"
      << "<tr_salsVal species=\"Species_1\">0.0549</tr_salsVal>"
      << "<tr_salsVal species=\"Species_3\">0.0549</tr_salsVal>"
      << "</tr_saplingLinearSlope>"
      << "<tr_saplingLinearIntercept>"
      << "<tr_saliVal species=\"Species_1\">1.2</tr_saliVal>"
      << "<tr_saliVal species=\"Species_2\">1.2</tr_saliVal>"
      << "<tr_saliVal species=\"Species_3\">0</tr_saliVal>"
      << "</tr_saplingLinearIntercept>"
      << "<tr_seedlingLinearSlope>"
      << "<tr_selsVal species=\"Species_1\">96.29</tr_selsVal>"
      << "<tr_selsVal species=\"Species_2\">96.29</tr_selsVal>"
      << "<tr_selsVal species=\"Species_3\">0</tr_selsVal>"
      << "</tr_seedlingLinearSlope>"
      << "<tr_seedlingLinearIntercept>"
      << "<tr_seliVal species=\"Species_1\">0</tr_seliVal>"
      << "<tr_seliVal species=\"Species_2\">0</tr_seliVal>"
      << "<tr_seliVal species=\"Species_3\">-0.9</tr_seliVal>"
      << "</tr_seedlingLinearIntercept>"
      << "</allometry>";

  WriteAllometryCommonBehaviorList(oOut);

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteAllometryXMLErrorFile9()
/////////////////////////////////////////////////////////////////////////////
const char* WriteAllometryXMLErrorFile9()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteAllometryCommonErrorBlock3(oOut);

  oOut << "<tr_whatSeedlingHeightDiam>"
      << "<tr_wsehdVal species=\"Species_1\">2</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_2\">2</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_3\">2</tr_wsehdVal>"
      << "</tr_whatSeedlingHeightDiam>"
      << "<tr_whatSaplingHeightDiam>"
      << "<tr_wsahdVal species=\"Species_1\">2</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_2\">2</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_3\">2</tr_wsahdVal>"
      << "</tr_whatSaplingHeightDiam>"
      << "<tr_whatAdultHeightDiam>"
      << "<tr_wahdVal species=\"Species_1\">2</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_2\">2</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_3\">2</tr_wahdVal>"
      << "</tr_whatAdultHeightDiam>"
      << "<tr_adultReverseLinearSlope>"
      << "<tr_arlsVal species=\"Species_1\">2.1</tr_arlsVal>"
      << "<tr_arlsVal species=\"Species_2\">2.1</tr_arlsVal>"
      << "<tr_arlsVal species=\"Species_3\">2.1</tr_arlsVal>"
      << "</tr_adultReverseLinearSlope>"
      << "<tr_adultReverseLinearIntercept>"
      << "<tr_arliVal species=\"Species_1\">0.02418</tr_arliVal>"
      << "<tr_arliVal species=\"Species_2\">0.02418</tr_arliVal>"
      << "<tr_arliVal species=\"Species_3\">0.02418</tr_arliVal>"
      << "</tr_adultReverseLinearIntercept>"
      << "<tr_saplingReverseLinearSlope>"
      << "<tr_sarlsVal species=\"Species_1\">1.5</tr_sarlsVal>"
      << "<tr_sarlsVal species=\"Species_2\">1.5</tr_sarlsVal>"
      << "<tr_sarlsVal species=\"Species_3\">1.1</tr_sarlsVal>"
      << "</tr_saplingReverseLinearSlope>"
      << "<tr_saplingReverseLinearIntercept>"
      << "<tr_sarliVal species=\"Species_1\">0.761</tr_sarliVal>"
      << "<tr_sarliVal species=\"Species_2\">0.761</tr_sarliVal>"
      << "<tr_sarliVal species=\"Species_3\">-0.847</tr_sarliVal>"
      << "</tr_saplingReverseLinearIntercept>"
      << "<tr_seedlingReverseLinearSlope>"
      << "<tr_serlsVal species=\"Species_2\">0</tr_serlsVal>"
      << "<tr_serlsVal species=\"Species_1\">0.761</tr_serlsVal>"
      << "<tr_serlsVal species=\"Species_3\">0.761</tr_serlsVal>"
      << "</tr_seedlingReverseLinearSlope>"
      << "<tr_seedlingReverseLinearIntercept>"
      << "<tr_serliVal species=\"Species_2\">0.02</tr_serliVal>"
      << "<tr_serliVal species=\"Species_1\">0.758</tr_serliVal>"
      << "<tr_serliVal species=\"Species_3\">0.758</tr_serliVal>"
      << "</tr_seedlingReverseLinearIntercept>"
      << "</allometry>";

  WriteAllometryCommonBehaviorList(oOut);

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteAllometryXMLErrorFile10()
/////////////////////////////////////////////////////////////////////////////
const char* WriteAllometryXMLErrorFile10()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteAllometryCommonPlot(oOut);
  WriteAllometryCommonTrees(oOut, 3);

  oOut << "<allometry>"
      << "<tr_canopyHeight>"
      << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
      << "<tr_chVal species=\"Species_2\">39.54</tr_chVal>"
      << "<tr_chVal species=\"Species_3\">45</tr_chVal>"
      << "</tr_canopyHeight>"
      << "<tr_stdAsympCrownRad>"
      << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_2\">0.0614</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_3\">0.02418</tr_sacrVal>"
      << "</tr_stdAsympCrownRad>"
      << "<tr_stdCrownRadExp>"
      << "<tr_screVal species=\"Species_1\">0.9</tr_screVal>"
      << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_3\">1.1</tr_screVal>"
      << "</tr_stdCrownRadExp>"
      << "<tr_conversionDiam10ToDBH>"
      << "<tr_cdtdVal species=\"Species_1\">0</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_2\">0.5944</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_3\">0.7059</tr_cdtdVal>"
      << "</tr_conversionDiam10ToDBH>"
      << "<tr_interceptDiam10ToDBH>"
      << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_2\">1</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_3\">-0.2</tr_idtdVal>"
      << "</tr_interceptDiam10ToDBH>"
      << "<tr_stdAsympCrownHt>"
      << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
      << "<tr_sachVal species=\"Species_2\">0.368</tr_sachVal>"
      << "<tr_sachVal species=\"Species_3\">0.34</tr_sachVal>"
      << "</tr_stdAsympCrownHt>"
      << "<tr_stdCrownHtExp>"
      << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_2\">0.5</tr_scheVal>"
      << "<tr_scheVal species=\"Species_3\">0.9</tr_scheVal>"
      << "</tr_stdCrownHtExp>"
      << "<tr_slopeOfHeight-Diam10>"
      << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_2\">0.03418</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_3\">0.2871</tr_sohdVal>"
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

  WriteAllometryCommonBehaviorList(oOut);

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteAllometryXMLErrorFile11()
/////////////////////////////////////////////////////////////////////////////
const char* WriteAllometryXMLErrorFile11()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteAllometryCommonErrorBlock1(oOut);

  oOut << "<tr_whatAdultCrownRadDiam>"
      << "<tr_wacrdVal species=\"Species_1\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Species_2\">13</tr_wacrdVal>"
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
      << "</allometry>";

  WriteAllometryCommonBehaviorList(oOut);

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteAllometryXMLErrorFile12()
/////////////////////////////////////////////////////////////////////////////
const char* WriteAllometryXMLErrorFile12()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteAllometryCommonErrorBlock1(oOut);

  oOut << "<tr_whatAdultCrownRadDiam>"
      << "<tr_wacrdVal species=\"Species_1\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Species_2\">0</tr_wacrdVal>"
      << "</tr_whatAdultCrownRadDiam>"
      << "<tr_whatAdultCrownHeightHeight>"
      << "<tr_wachhVal species=\"Species_1\">4</tr_wachhVal>"
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
      << "</allometry>";

  WriteAllometryCommonBehaviorList(oOut);

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteAllometryXMLErrorFile13()
/////////////////////////////////////////////////////////////////////////////
const char* WriteAllometryXMLErrorFile13()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteAllometryCommonErrorBlock1(oOut);

  oOut << "<tr_whatAdultCrownRadDiam>"
      << "<tr_wacrdVal species=\"Species_1\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Species_2\">0</tr_wacrdVal>"
      << "</tr_whatAdultCrownRadDiam>"
      << "<tr_whatAdultCrownHeightHeight>"
      << "<tr_wachhVal species=\"Species_1\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Species_2\">0</tr_wachhVal>"
      << "</tr_whatAdultCrownHeightHeight>"
      << "<tr_whatSaplingCrownRadDiam>"
      << "<tr_wscrdVal species=\"Species_1\">2</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Species_2\">0</tr_wscrdVal>"
      << "</tr_whatSaplingCrownRadDiam>"
      << "<tr_whatSaplingCrownHeightHeight>"
      << "<tr_wschhVal species=\"Species_1\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Species_2\">0</tr_wschhVal>"
      << "</tr_whatSaplingCrownHeightHeight>"
      << "</allometry>";

  WriteAllometryCommonBehaviorList(oOut);

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteAllometryXMLErrorFile14()
/////////////////////////////////////////////////////////////////////////////
const char* WriteAllometryXMLErrorFile14()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteAllometryCommonErrorBlock1(oOut);

   oOut << "<tr_whatAdultCrownRadDiam>"
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
      << "<tr_wschhVal species=\"Species_2\">2</tr_wschhVal>"
      << "</tr_whatSaplingCrownHeightHeight>"
      << "</allometry>";

  WriteAllometryCommonBehaviorList(oOut);

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteAllometryXMLFile5()
/////////////////////////////////////////////////////////////////////////////
const char* WriteAllometryXMLFile5()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteAllometryCommonPlot(oOut);
  WriteAllometryCommonTrees(oOut, 3);

  oOut << "<allometry>"
      << "<tr_canopyHeight>"
      << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
      << "<tr_chVal species=\"Species_2\">39.54</tr_chVal>"
      << "<tr_chVal species=\"Species_3\">45</tr_chVal>"
      << "</tr_canopyHeight>"
      << "<tr_stdAsympCrownRad>"
      << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_2\">0.0614</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_3\">0.02418</tr_sacrVal>"
      << "</tr_stdAsympCrownRad>"
      << "<tr_stdCrownRadExp>"
      << "<tr_screVal species=\"Species_1\">0.9</tr_screVal>"
      << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_3\">1.1</tr_screVal>"
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
      << "<tr_idtdVal species=\"Species_2\">1</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_3\">-0.2</tr_idtdVal>"
      << "</tr_interceptDiam10ToDBH>"
      << "<tr_stdAsympCrownHt>"
      << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
      << "<tr_sachVal species=\"Species_2\">0.368</tr_sachVal>"
      << "<tr_sachVal species=\"Species_3\">0.34</tr_sachVal>"
      << "</tr_stdAsympCrownHt>"
      << "<tr_stdCrownHtExp>"
      << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_2\">0.5</tr_scheVal>"
      << "<tr_scheVal species=\"Species_3\">0.9</tr_scheVal>"
      << "</tr_stdCrownHtExp>"
      << "<tr_slopeOfHeight-Diam10>"
      << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_2\">0.03418</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_3\">0.2871</tr_sohdVal>"
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
      << "<tr_wahdVal species=\"Species_1\">1</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_2\">1</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_3\">1</tr_wahdVal>"
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
      << "<tr_wscrdVal species=\"Species_1\">1</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Species_2\">1</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Species_3\">1</tr_wscrdVal>"
      << "</tr_whatSaplingCrownRadDiam>"
      << "<tr_whatSaplingCrownHeightHeight>"
      << "<tr_wschhVal species=\"Species_1\">1</tr_wschhVal>"
      << "<tr_wschhVal species=\"Species_2\">1</tr_wschhVal>"
      << "<tr_wschhVal species=\"Species_3\">1</tr_wschhVal>"
      << "</tr_whatSaplingCrownHeightHeight>"
      << "<tr_adultLinearSlope>"
      << "<tr_alsVal species=\"Species_1\">0.96</tr_alsVal>"
      << "<tr_alsVal species=\"Species_2\">1.3</tr_alsVal>"
      << "<tr_alsVal species=\"Species_3\">1.3</tr_alsVal>"
      << "</tr_adultLinearSlope>"
      << "<tr_adultLinearIntercept>"
      << "<tr_aliVal species=\"Species_1\">0</tr_aliVal>"
      << "<tr_aliVal species=\"Species_2\">-0.9</tr_aliVal>"
      << "<tr_aliVal species=\"Species_3\">-0.9</tr_aliVal>"
      << "</tr_adultLinearIntercept>"
      << "<tr_chRichCrownRadIntercept>"
      << "<tr_crcriVal species=\"Species_2\">0.3</tr_crcriVal>"
      << "<tr_crcriVal species=\"Species_3\">0.4</tr_crcriVal>"
      << "<tr_crcriVal species=\"Species_1\">0.5</tr_crcriVal>"
      << "</tr_chRichCrownRadIntercept>"
      << "<tr_chRichCrownRadAsymp>"
      << "<tr_crcraVal species=\"Species_2\">8</tr_crcraVal>"
      << "<tr_crcraVal species=\"Species_3\">7</tr_crcraVal>"
      << "<tr_crcraVal species=\"Species_1\">10</tr_crcraVal>"
      << "</tr_chRichCrownRadAsymp>"
      << "<tr_chRichCrownRadShape1b>"
      << "<tr_crcrs1bVal species=\"Species_2\">0.09</tr_crcrs1bVal>"
      << "<tr_crcrs1bVal species=\"Species_3\">0.1</tr_crcrs1bVal>"
      << "<tr_crcrs1bVal species=\"Species_1\">0.11</tr_crcrs1bVal>"
      << "</tr_chRichCrownRadShape1b>"
      << "<tr_chRichCrownRadShape2c>"
      << "<tr_crcrs2cVal species=\"Species_2\">1.5</tr_crcrs2cVal>"
      << "<tr_crcrs2cVal species=\"Species_3\">2.4</tr_crcrs2cVal>"
      << "<tr_crcrs2cVal species=\"Species_1\">2.8</tr_crcrs2cVal>"
      << "</tr_chRichCrownRadShape2c>"
      << "<tr_chRichCrownHtIntercept>"
      << "<tr_crchiVal species=\"Species_2\">0.6</tr_crchiVal>"
      << "<tr_crchiVal species=\"Species_3\">0.5</tr_crchiVal>"
      << "<tr_crchiVal species=\"Species_1\">0.4</tr_crchiVal>"
      << "</tr_chRichCrownHtIntercept>"
      << "<tr_chRichCrownHtAsymp>"
      << "<tr_crchaVal species=\"Species_2\">60</tr_crchaVal>"
      << "<tr_crchaVal species=\"Species_3\">12</tr_crchaVal>"
      << "<tr_crchaVal species=\"Species_1\">13</tr_crchaVal>"
      << "</tr_chRichCrownHtAsymp>"
      << "<tr_chRichCrownHtShape1b>"
      << "<tr_crchs1bVal species=\"Species_2\">0.3</tr_crchs1bVal>"
      << "<tr_crchs1bVal species=\"Species_3\">0.1</tr_crchs1bVal>"
      << "<tr_crchs1bVal species=\"Species_1\">0.12</tr_crchs1bVal>"
      << "</tr_chRichCrownHtShape1b>"
      << "<tr_chRichCrownHtShape2c>"
      << "<tr_crchs2cVal species=\"Species_2\">3.2</tr_crchs2cVal>"
      << "<tr_crchs2cVal species=\"Species_3\">4.1</tr_crchs2cVal>"
      << "<tr_crchs2cVal species=\"Species_1\">2.9</tr_crchs2cVal>"
      << "</tr_chRichCrownHtShape2c>"
      << "</allometry>";

      WriteAllometryCommonBehaviorList(oOut);

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteAllometryXMLFile6()
/////////////////////////////////////////////////////////////////////////////
const char* WriteAllometryXMLFile6()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteAllometryCommonPlot(oOut);
  WriteAllometryCommonTrees(oOut, 3);

  oOut << "<allometry>"
      << "<tr_canopyHeight>"
      << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
      << "<tr_chVal species=\"Species_2\">39.54</tr_chVal>"
      << "<tr_chVal species=\"Species_3\">45</tr_chVal>"
      << "</tr_canopyHeight>"
      << "<tr_stdAsympCrownRad>"
      << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_2\">0.0614</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_3\">0.02418</tr_sacrVal>"
      << "</tr_stdAsympCrownRad>"
      << "<tr_stdCrownRadExp>"
      << "<tr_screVal species=\"Species_1\">0.9</tr_screVal>"
      << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_3\">1.1</tr_screVal>"
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
      << "<tr_idtdVal species=\"Species_2\">1</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_3\">-0.2</tr_idtdVal>"
      << "</tr_interceptDiam10ToDBH>"
      << "<tr_stdAsympCrownHt>"
      << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
      << "<tr_sachVal species=\"Species_2\">0.368</tr_sachVal>"
      << "<tr_sachVal species=\"Species_3\">0.34</tr_sachVal>"
      << "</tr_stdAsympCrownHt>"
      << "<tr_stdCrownHtExp>"
      << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_2\">0.5</tr_scheVal>"
      << "<tr_scheVal species=\"Species_3\">0.9</tr_scheVal>"
      << "</tr_stdCrownHtExp>"
      << "<tr_slopeOfHeight-Diam10>"
      << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_2\">0.03418</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_3\">0.2871</tr_sohdVal>"
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
      << "<tr_wahdVal species=\"Species_1\">1</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_2\">1</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_3\">1</tr_wahdVal>"
      << "</tr_whatAdultHeightDiam>"
      << "<tr_whatAdultCrownRadDiam>"
      << "<tr_wacrdVal species=\"Species_1\">1</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Species_2\">1</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Species_3\">1</tr_wacrdVal>"
      << "</tr_whatAdultCrownRadDiam>"
      << "<tr_whatAdultCrownHeightHeight>"
      << "<tr_wachhVal species=\"Species_1\">1</tr_wachhVal>"
      << "<tr_wachhVal species=\"Species_2\">1</tr_wachhVal>"
      << "<tr_wachhVal species=\"Species_3\">1</tr_wachhVal>"
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
      << "<tr_adultLinearSlope>"
      << "<tr_alsVal species=\"Species_1\">0.96</tr_alsVal>"
      << "<tr_alsVal species=\"Species_2\">1.3</tr_alsVal>"
      << "<tr_alsVal species=\"Species_3\">1.3</tr_alsVal>"
      << "</tr_adultLinearSlope>"
      << "<tr_adultLinearIntercept>"
      << "<tr_aliVal species=\"Species_1\">0</tr_aliVal>"
      << "<tr_aliVal species=\"Species_2\">-0.9</tr_aliVal>"
      << "<tr_aliVal species=\"Species_3\">-0.9</tr_aliVal>"
      << "</tr_adultLinearIntercept>"
      << "<tr_chRichCrownRadIntercept>"
      << "<tr_crcriVal species=\"Species_2\">0.3</tr_crcriVal>"
      << "<tr_crcriVal species=\"Species_3\">0.4</tr_crcriVal>"
      << "<tr_crcriVal species=\"Species_1\">0.5</tr_crcriVal>"
      << "</tr_chRichCrownRadIntercept>"
      << "<tr_chRichCrownRadAsymp>"
      << "<tr_crcraVal species=\"Species_2\">8</tr_crcraVal>"
      << "<tr_crcraVal species=\"Species_3\">7</tr_crcraVal>"
      << "<tr_crcraVal species=\"Species_1\">10</tr_crcraVal>"
      << "</tr_chRichCrownRadAsymp>"
      << "<tr_chRichCrownRadShape1b>"
      << "<tr_crcrs1bVal species=\"Species_2\">0.09</tr_crcrs1bVal>"
      << "<tr_crcrs1bVal species=\"Species_3\">0.1</tr_crcrs1bVal>"
      << "<tr_crcrs1bVal species=\"Species_1\">0.11</tr_crcrs1bVal>"
      << "</tr_chRichCrownRadShape1b>"
      << "<tr_chRichCrownRadShape2c>"
      << "<tr_crcrs2cVal species=\"Species_2\">1.5</tr_crcrs2cVal>"
      << "<tr_crcrs2cVal species=\"Species_3\">2.4</tr_crcrs2cVal>"
      << "<tr_crcrs2cVal species=\"Species_1\">2.8</tr_crcrs2cVal>"
      << "</tr_chRichCrownRadShape2c>"
      << "<tr_chRichCrownHtIntercept>"
      << "<tr_crchiVal species=\"Species_2\">0.6</tr_crchiVal>"
      << "<tr_crchiVal species=\"Species_3\">0.5</tr_crchiVal>"
      << "<tr_crchiVal species=\"Species_1\">0.4</tr_crchiVal>"
      << "</tr_chRichCrownHtIntercept>"
      << "<tr_chRichCrownHtAsymp>"
      << "<tr_crchaVal species=\"Species_2\">60</tr_crchaVal>"
      << "<tr_crchaVal species=\"Species_3\">12</tr_crchaVal>"
      << "<tr_crchaVal species=\"Species_1\">13</tr_crchaVal>"
      << "</tr_chRichCrownHtAsymp>"
      << "<tr_chRichCrownHtShape1b>"
      << "<tr_crchs1bVal species=\"Species_2\">0.3</tr_crchs1bVal>"
      << "<tr_crchs1bVal species=\"Species_3\">0.1</tr_crchs1bVal>"
      << "<tr_crchs1bVal species=\"Species_1\">0.12</tr_crchs1bVal>"
      << "</tr_chRichCrownHtShape1b>"
      << "<tr_chRichCrownHtShape2c>"
      << "<tr_crchs2cVal species=\"Species_2\">3.2</tr_crchs2cVal>"
      << "<tr_crchs2cVal species=\"Species_3\">4.1</tr_crchs2cVal>"
      << "<tr_crchs2cVal species=\"Species_1\">2.9</tr_crchs2cVal>"
      << "</tr_chRichCrownHtShape2c>"
      << "</allometry>";

  WriteAllometryCommonBehaviorList(oOut);

  oOut.close();

  return cFileString;
}
