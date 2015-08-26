//---------------------------------------------------------------------------
// TestBrowsedRelativeGrowth.cpp
//---------------------------------------------------------------------------
#include "TestBrowsedRelativeGrowth.h"
#include <gtest/gtest.h>
#include <fstream>
#include <math.h>
#include "TreePopulation.h"
#include "SimManager.h"
#include "BehaviorBase.h"

////////////////////////////////////////////////////////////////////////////
// TestNormalRun1()
// Tests the growth when the timestep length is one year.
// WriteBrowsedRelativeGrowthXMLFile1() is used to set up the run.
////////////////////////////////////////////////////////////////////////////
TEST(BrowsedRelativeGrowth, TestNormalRun1) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTree *p_oTree1, *p_oTree2, *p_oTree3, *p_oTree4, *p_oTree5, *p_oTree6,
    *p_oTree7, *p_oTree8, *p_oTree9, *p_oTree10, *p_oTree11, *p_oTree12,
    *p_oTree13, *p_oTree14, *p_oTree15, *p_oTree16, *p_oTree17, *p_oTree18,
    *p_oTree19, *p_oTree20, *p_oTree;
    float fDiam, fHeight, fExpectedDiam, fExpectedHeight, fLight, fGrowth,
    fExpectedGrowth;
    int iSp;
    bool bBrowsed;

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteBrowsedRelativeGrowthXMLFile1() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create our ten trees and set diameter, height, and GLI for each
    iSp=0;  fLight=60;  fDiam=1.0;  bBrowsed=false;
    p_oTree = p_oPop->CreateTree(1, 1, iSp, clTreePopulation::seedling, fDiam);
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType()), fLight, false, false);
    p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", p_oTree->GetSpecies(), p_oTree->GetType()), bBrowsed);
    p_oTree1 = p_oTree;

    iSp=1;  fLight=80;  fDiam=2.0;  bBrowsed=false;
    p_oTree = p_oPop->CreateTree(1, 1, iSp, clTreePopulation::seedling, fDiam);
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType()), fLight, false, false);
    p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", p_oTree->GetSpecies(), p_oTree->GetType()), bBrowsed);
    p_oTree2 = p_oTree;

    iSp=1;  fLight=10;  fDiam=3.0;  bBrowsed=false;
    p_oTree = p_oPop->CreateTree(1, 1, iSp, clTreePopulation::seedling, fDiam);
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType()), fLight, false, false);
    p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", p_oTree->GetSpecies(), p_oTree->GetType()), bBrowsed);
    p_oTree3 = p_oTree;

    iSp=0;  fLight=2; fDiam=4.0;  bBrowsed=false;
    p_oTree = p_oPop->CreateTree(1, 1, iSp, clTreePopulation::seedling, fDiam);
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType()), fLight, false, false);
    p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", p_oTree->GetSpecies(), p_oTree->GetType()), bBrowsed);
    p_oTree4 = p_oTree;

    iSp=0;  fLight=90;  fDiam=5.0;  bBrowsed=false;
    p_oTree = p_oPop->CreateTree(1, 1, iSp, clTreePopulation::seedling, fDiam);
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType()), fLight, false, false);
    p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", p_oTree->GetSpecies(), p_oTree->GetType()), bBrowsed);
    p_oTree5 = p_oTree;

    iSp=2;  fLight=60;  fDiam=1.0;  bBrowsed=false;
    p_oTree = p_oPop->CreateTree(1, 1, iSp, clTreePopulation::seedling, fDiam);
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType()), fLight, false, false);
    p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", p_oTree->GetSpecies(), p_oTree->GetType()), bBrowsed);
    p_oTree6 = p_oTree;

    iSp=3;  fLight=70;  fDiam=2.0;  bBrowsed=false;
    p_oTree = p_oPop->CreateTree(1, 1, iSp, clTreePopulation::seedling, fDiam);
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType()), fLight, false, false);
    p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", p_oTree->GetSpecies(), p_oTree->GetType()), bBrowsed);
    p_oTree7 = p_oTree;

    iSp=3;  fLight=10;  fDiam=3.0;  bBrowsed=false;
    p_oTree = p_oPop->CreateTree(1, 1, iSp, clTreePopulation::seedling, fDiam);
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType()), fLight, false, false);
    p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", p_oTree->GetSpecies(), p_oTree->GetType()), bBrowsed);
    p_oTree8 = p_oTree;

    iSp=2;  fLight=2; fDiam=4.0;  bBrowsed=false;
    p_oTree = p_oPop->CreateTree(1, 1, iSp, clTreePopulation::seedling, fDiam);
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType()), fLight, false, false);
    p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", p_oTree->GetSpecies(), p_oTree->GetType()), bBrowsed);
    p_oTree9 = p_oTree;

    iSp=2;  fLight=90;  fDiam=5.0;  bBrowsed=false;
    p_oTree = p_oPop->CreateTree(1, 1, iSp, clTreePopulation::seedling, fDiam);
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType()), fLight, false, false);
    p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", p_oTree->GetSpecies(), p_oTree->GetType()), bBrowsed);
    p_oTree10 = p_oTree;

    iSp=0;  fLight=60;  fDiam=1.0;  bBrowsed=true;
    p_oTree = p_oPop->CreateTree(1, 1, iSp, clTreePopulation::seedling, fDiam);
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType()), fLight, false, false);
    p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", p_oTree->GetSpecies(), p_oTree->GetType()), bBrowsed);
    p_oTree11 = p_oTree;

    iSp=1;  fLight=80;  fDiam=2.0;  bBrowsed=true;
    p_oTree = p_oPop->CreateTree(1, 1, iSp, clTreePopulation::seedling, fDiam);
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType()), fLight, false, false);
    p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", p_oTree->GetSpecies(), p_oTree->GetType()), bBrowsed);
    p_oTree12 = p_oTree;

    iSp=1;  fLight=10;  fDiam=3.0;  bBrowsed=true;
    p_oTree = p_oPop->CreateTree(1, 1, iSp, clTreePopulation::seedling, fDiam);
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType()), fLight, false, false);
    p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", p_oTree->GetSpecies(), p_oTree->GetType()), bBrowsed);
    p_oTree13 = p_oTree;

    iSp=0;  fLight=2; fDiam=4.0;  bBrowsed=true;
    p_oTree = p_oPop->CreateTree(1, 1, iSp, clTreePopulation::seedling, fDiam);
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType()), fLight, false, false);
    p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", p_oTree->GetSpecies(), p_oTree->GetType()), bBrowsed);
    p_oTree14 = p_oTree;

    iSp=0;  fLight=90;  fDiam=5.0;  bBrowsed=true;
    p_oTree = p_oPop->CreateTree(1, 1, iSp, clTreePopulation::seedling, fDiam);
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType()), fLight, false, false);
    p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", p_oTree->GetSpecies(), p_oTree->GetType()), bBrowsed);
    p_oTree15 = p_oTree;

    iSp=2;  fLight=60;  fDiam=1.0;  bBrowsed=true;
    p_oTree = p_oPop->CreateTree(1, 1, iSp, clTreePopulation::seedling, fDiam);
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType()), fLight, false, false);
    p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", p_oTree->GetSpecies(), p_oTree->GetType()), bBrowsed);
    p_oTree16 = p_oTree;

    iSp=3;  fLight=70;  fDiam=2.0;  bBrowsed=true;
    p_oTree = p_oPop->CreateTree(1, 1, iSp, clTreePopulation::seedling, fDiam);
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType()), fLight, false, false);
    p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", p_oTree->GetSpecies(), p_oTree->GetType()), bBrowsed);
    p_oTree17 = p_oTree;

    iSp=3;  fLight=10;  fDiam=2.0;  bBrowsed=true;
    p_oTree = p_oPop->CreateTree(1, 1, iSp, clTreePopulation::seedling, fDiam);
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType()), fLight, false, false);
    p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", p_oTree->GetSpecies(), p_oTree->GetType()), bBrowsed);
    p_oTree18 = p_oTree;

    iSp=2;  fLight=2; fDiam=4.0;  bBrowsed=true;
    p_oTree = p_oPop->CreateTree(1, 1, iSp, clTreePopulation::seedling, fDiam);
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType()), fLight, false, false);
    p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", p_oTree->GetSpecies(), p_oTree->GetType()), bBrowsed);
    p_oTree19 = p_oTree;

    iSp=2;  fLight=90;  fDiam=4.0;  bBrowsed=true;
    p_oTree = p_oPop->CreateTree(1, 1, iSp, clTreePopulation::seedling, fDiam);
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType()), fLight, false, false);
    p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", p_oTree->GetSpecies(), p_oTree->GetType()), bBrowsed);
    p_oTree20 = p_oTree;

    //Now run growth, but skip light and browse
    clBehaviorBase *p_oBase = p_oSimManager->GetBehaviorObject(2);
    p_oBase->Action();

    //Confirm all trees
    p_oTree = p_oTree1;
    fExpectedDiam = 1.017194259;
    fExpectedHeight = 0.213610794;
    fExpectedGrowth = 0.085971296;
    p_oTree->GetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
    p_oTree->GetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fHeight);
    p_oTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    p_oTree = p_oTree2;
    fExpectedDiam = 2.074287108;
    fExpectedHeight = 0.456343164;
    fExpectedGrowth = 0.371435542;
    p_oTree->GetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
    p_oTree->GetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fHeight);
    p_oTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    p_oTree = p_oTree3;
    fExpectedDiam = 3.102193882;
    fExpectedHeight = 0.682482654;
    fExpectedGrowth = 0.510969408;
    p_oTree->GetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
    p_oTree->GetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fHeight);
    p_oTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    p_oTree = p_oTree4;
    fExpectedDiam = 4.078246704;
    fExpectedHeight = 0.856431808;
    fExpectedGrowth = 0.39123352;
    p_oTree->GetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
    p_oTree->GetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fHeight);
    p_oTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    p_oTree = p_oTree5;
    fExpectedDiam = 5.100994749;
    fExpectedHeight = 1.071208897;
    fExpectedGrowth = 0.504973746;
    p_oTree->GetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
    p_oTree->GetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fHeight);
    p_oTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    p_oTree = p_oTree6;
    fExpectedDiam = 1.01970683;
    fExpectedHeight = 0.234532571;
    fExpectedGrowth = 0.098534151;
    p_oTree->GetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
    p_oTree->GetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fHeight);
    p_oTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    p_oTree = p_oTree7;
    fExpectedDiam = 2.043261981;
    fExpectedHeight = 0.490382876;
    fExpectedGrowth = 0.216309907;
    p_oTree->GetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
    p_oTree->GetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fHeight);
    p_oTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    p_oTree = p_oTree8;
    fExpectedDiam = 3.059037414;
    fExpectedHeight = 0.734168979;
    fExpectedGrowth = 0.295187069;
    p_oTree->GetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
    p_oTree->GetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fHeight);
    p_oTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    p_oTree = p_oTree9;
    fExpectedDiam = 4.105133296;
    fExpectedHeight = 0.944180658;
    fExpectedGrowth = 0.52566648;
    p_oTree->GetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
    p_oTree->GetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fHeight);
    p_oTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    p_oTree = p_oTree10;
    fExpectedDiam = 5.159940891;
    fExpectedHeight = 1.186786405;
    fExpectedGrowth = 0.799704457;
    p_oTree->GetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
    p_oTree->GetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fHeight);
    p_oTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    p_oTree = p_oTree11;
    fExpectedDiam = 1.022905755;
    fExpectedHeight = 0.214810209;
    fExpectedGrowth = 0.114528776;
    p_oTree->GetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
    p_oTree->GetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fHeight);
    p_oTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    p_oTree = p_oTree12;
    fExpectedDiam = 2.055273757;
    fExpectedHeight = 0.452160227;
    fExpectedGrowth = 0.276368786;
    p_oTree->GetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
    p_oTree->GetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fHeight);
    p_oTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    p_oTree = p_oTree13;
    fExpectedDiam = 3.072742545;
    fExpectedHeight = 0.67600336;
    fExpectedGrowth = 0.363712724;
    p_oTree->GetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
    p_oTree->GetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fHeight);
    p_oTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    p_oTree = p_oTree14;
    fExpectedDiam = 4.055824147;
    fExpectedHeight = 0.851723071;
    fExpectedGrowth = 0.279120736;
    p_oTree->GetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
    p_oTree->GetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fHeight);
    p_oTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    p_oTree = p_oTree15;
    fExpectedDiam = 5.08324145;
    fExpectedHeight = 1.067480704;
    fExpectedGrowth = 0.416207249;
    p_oTree->GetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
    p_oTree->GetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fHeight);
    p_oTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    p_oTree = p_oTree16;
    fExpectedDiam = 1.042655664;
    fExpectedHeight = 0.239810803;
    fExpectedGrowth = 0.213278322;
    p_oTree->GetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
    p_oTree->GetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fHeight);
    p_oTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    p_oTree = p_oTree17;
    fExpectedDiam = 2.612080591;
    fExpectedHeight = 0.626899342;
    fExpectedGrowth = 3.060402957;
    p_oTree->GetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
    p_oTree->GetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fHeight);
    p_oTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    p_oTree = p_oTree18;
    fExpectedDiam = 2.579904766;
    fExpectedHeight = 0.619177144;
    fExpectedGrowth = 2.89952383;
    p_oTree->GetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
    p_oTree->GetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fHeight);
    p_oTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    p_oTree = p_oTree19;
    fExpectedDiam = 4.218557007;
    fExpectedHeight = 0.970268112;
    fExpectedGrowth = 1.092785036;
    p_oTree->GetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
    p_oTree->GetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fHeight);
    p_oTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    p_oTree = p_oTree20;
    fExpectedDiam = 4.225215894;
    fExpectedHeight = 0.971799656;
    fExpectedGrowth = 1.126079469;
    p_oTree->GetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
    p_oTree->GetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fHeight);
    p_oTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), &fGrowth);
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
// TestNormalRun2()
// Tests the growth when the timestep length is three years.
// WriteBrowsedRelativeGrowthXMLFile2() is used to set up the run.
////////////////////////////////////////////////////////////////////////////
TEST(BrowsedRelativeGrowth, TestNormalRun2) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTree *p_oTree1, *p_oTree2, *p_oTree3, *p_oTree4, *p_oTree5, *p_oTree6,
    *p_oTree7, *p_oTree8, *p_oTree9, *p_oTree10, *p_oTree11, *p_oTree12,
    *p_oTree13, *p_oTree14, *p_oTree15, *p_oTree16, *p_oTree17, *p_oTree18,
    *p_oTree19, *p_oTree20, *p_oTree;
    float fDiam, fHeight, fExpectedDiam, fExpectedHeight, fLight, fGrowth,
    fExpectedGrowth;
    int iSp;
    bool bBrowsed;

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteBrowsedRelativeGrowthXMLFile2() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create our ten trees and set diameter, height, and GLI for each
    iSp=0;  fLight=60;  fDiam=1.0;  bBrowsed=false;
    p_oTree = p_oPop->CreateTree(1, 1, iSp, clTreePopulation::seedling, fDiam);
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType()), fLight, false, false);
    p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", p_oTree->GetSpecies(), p_oTree->GetType()), bBrowsed);
    p_oTree1 = p_oTree;

    iSp=1;  fLight=80;  fDiam=2.0;  bBrowsed=false;
    p_oTree = p_oPop->CreateTree(1, 1, iSp, clTreePopulation::seedling, fDiam);
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType()), fLight, false, false);
    p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", p_oTree->GetSpecies(), p_oTree->GetType()), bBrowsed);
    p_oTree2 = p_oTree;

    iSp=1;  fLight=10;  fDiam=3.0;  bBrowsed=false;
    p_oTree = p_oPop->CreateTree(1, 1, iSp, clTreePopulation::seedling, fDiam);
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType()), fLight, false, false);
    p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", p_oTree->GetSpecies(), p_oTree->GetType()), bBrowsed);
    p_oTree3 = p_oTree;

    iSp=0;  fLight=2; fDiam=4.0;  bBrowsed=false;
    p_oTree = p_oPop->CreateTree(1, 1, iSp, clTreePopulation::seedling, fDiam);
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType()), fLight, false, false);
    p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", p_oTree->GetSpecies(), p_oTree->GetType()), bBrowsed);
    p_oTree4 = p_oTree;

    iSp=0;  fLight=90;  fDiam=5.0;  bBrowsed=false;
    p_oTree = p_oPop->CreateTree(1, 1, iSp, clTreePopulation::seedling, fDiam);
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType()), fLight, false, false);
    p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", p_oTree->GetSpecies(), p_oTree->GetType()), bBrowsed);
    p_oTree5 = p_oTree;

    iSp=2;  fLight=60;  fDiam=1.0;  bBrowsed=false;
    p_oTree = p_oPop->CreateTree(1, 1, iSp, clTreePopulation::seedling, fDiam);
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType()), fLight, false, false);
    p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", p_oTree->GetSpecies(), p_oTree->GetType()), bBrowsed);
    p_oTree6 = p_oTree;

    iSp=3;  fLight=70;  fDiam=2.0;  bBrowsed=false;
    p_oTree = p_oPop->CreateTree(1, 1, iSp, clTreePopulation::seedling, fDiam);
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType()), fLight, false, false);
    p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", p_oTree->GetSpecies(), p_oTree->GetType()), bBrowsed);
    p_oTree7 = p_oTree;

    iSp=3;  fLight=10;  fDiam=3.0;  bBrowsed=false;
    p_oTree = p_oPop->CreateTree(1, 1, iSp, clTreePopulation::seedling, fDiam);
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType()), fLight, false, false);
    p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", p_oTree->GetSpecies(), p_oTree->GetType()), bBrowsed);
    p_oTree8 = p_oTree;

    iSp=2;  fLight=2; fDiam=4.0;  bBrowsed=false;
    p_oTree = p_oPop->CreateTree(1, 1, iSp, clTreePopulation::seedling, fDiam);
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType()), fLight, false, false);
    p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", p_oTree->GetSpecies(), p_oTree->GetType()), bBrowsed);
    p_oTree9 = p_oTree;

    iSp=2;  fLight=90;  fDiam=5.0;  bBrowsed=false;
    p_oTree = p_oPop->CreateTree(1, 1, iSp, clTreePopulation::seedling, fDiam);
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType()), fLight, false, false);
    p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", p_oTree->GetSpecies(), p_oTree->GetType()), bBrowsed);
    p_oTree10 = p_oTree;

    iSp=0;  fLight=60;  fDiam=1.0;  bBrowsed=true;
    p_oTree = p_oPop->CreateTree(1, 1, iSp, clTreePopulation::seedling, fDiam);
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType()), fLight, false, false);
    p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", p_oTree->GetSpecies(), p_oTree->GetType()), bBrowsed);
    p_oTree11 = p_oTree;

    iSp=1;  fLight=80;  fDiam=2.0;  bBrowsed=true;
    p_oTree = p_oPop->CreateTree(1, 1, iSp, clTreePopulation::seedling, fDiam);
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType()), fLight, false, false);
    p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", p_oTree->GetSpecies(), p_oTree->GetType()), bBrowsed);
    p_oTree12 = p_oTree;

    iSp=1;  fLight=10;  fDiam=3.0;  bBrowsed=true;
    p_oTree = p_oPop->CreateTree(1, 1, iSp, clTreePopulation::seedling, fDiam);
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType()), fLight, false, false);
    p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", p_oTree->GetSpecies(), p_oTree->GetType()), bBrowsed);
    p_oTree13 = p_oTree;

    iSp=0;  fLight=2; fDiam=4.0;  bBrowsed=true;
    p_oTree = p_oPop->CreateTree(1, 1, iSp, clTreePopulation::seedling, fDiam);
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType()), fLight, false, false);
    p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", p_oTree->GetSpecies(), p_oTree->GetType()), bBrowsed);
    p_oTree14 = p_oTree;

    iSp=0;  fLight=90;  fDiam=5.0;  bBrowsed=true;
    p_oTree = p_oPop->CreateTree(1, 1, iSp, clTreePopulation::seedling, fDiam);
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType()), fLight, false, false);
    p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", p_oTree->GetSpecies(), p_oTree->GetType()), bBrowsed);
    p_oTree15 = p_oTree;

    iSp=2;  fLight=60;  fDiam=1.0;  bBrowsed=true;
    p_oTree = p_oPop->CreateTree(1, 1, iSp, clTreePopulation::seedling, fDiam);
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType()), fLight, false, false);
    p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", p_oTree->GetSpecies(), p_oTree->GetType()), bBrowsed);
    p_oTree16 = p_oTree;

    iSp=3;  fLight=70;  fDiam=2.0;  bBrowsed=true;
    p_oTree = p_oPop->CreateTree(1, 1, iSp, clTreePopulation::seedling, fDiam);
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType()), fLight, false, false);
    p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", p_oTree->GetSpecies(), p_oTree->GetType()), bBrowsed);
    p_oTree17 = p_oTree;

    iSp=3;  fLight=10;  fDiam=2.0;  bBrowsed=true;
    p_oTree = p_oPop->CreateTree(1, 1, iSp, clTreePopulation::seedling, fDiam);
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType()), fLight, false, false);
    p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", p_oTree->GetSpecies(), p_oTree->GetType()), bBrowsed);
    p_oTree18 = p_oTree;

    iSp=2;  fLight=2; fDiam=4.0;  bBrowsed=true;
    p_oTree = p_oPop->CreateTree(1, 1, iSp, clTreePopulation::seedling, fDiam);
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType()), fLight, false, false);
    p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", p_oTree->GetSpecies(), p_oTree->GetType()), bBrowsed);
    p_oTree19 = p_oTree;

    iSp=2;  fLight=90;  fDiam=4.0;  bBrowsed=true;
    p_oTree = p_oPop->CreateTree(1, 1, iSp, clTreePopulation::seedling, fDiam);
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType()), fLight, false, false);
    p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", p_oTree->GetSpecies(), p_oTree->GetType()), bBrowsed);
    p_oTree20 = p_oTree;

    //Now run growth, but skip light and browse
    clBehaviorBase *p_oBase = p_oSimManager->GetBehaviorObject(2);
    p_oBase->Action();

    //Confirm all trees
    p_oTree = p_oTree1;
    fExpectedDiam = 1.052474789;
    fExpectedHeight = 0.221019706;
    fExpectedGrowth = 0.087457981;
    p_oTree->GetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
    p_oTree->GetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fHeight);
    p_oTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    p_oTree = p_oTree2;
    fExpectedDiam = 2.232505327;
    fExpectedHeight = 0.491151172;
    fExpectedGrowth = 0.387508879;
    p_oTree->GetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
    p_oTree->GetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fHeight);
    p_oTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    p_oTree = p_oTree3;
    fExpectedDiam = 3.319775574;
    fExpectedHeight = 0.730350626;
    fExpectedGrowth = 0.53295929;
    p_oTree->GetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
    p_oTree->GetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fHeight);
    p_oTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    p_oTree = p_oTree4;
    fExpectedDiam = 4.238760293;
    fExpectedHeight = 0.890139662;
    fExpectedGrowth = 0.397933822;
    p_oTree->GetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
    p_oTree->GetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fHeight);
    p_oTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    p_oTree = p_oTree5;
    fExpectedDiam = 5.308224282;
    fExpectedHeight = 1.114727099;
    fExpectedGrowth = 0.513707137;
    p_oTree->GetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
    p_oTree->GetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fHeight);
    p_oTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    p_oTree = p_oTree6;
    fExpectedDiam = 1.060293221;
    fExpectedHeight = 0.243867441;
    fExpectedGrowth = 0.100488702;
    p_oTree->GetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
    p_oTree->GetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fHeight);
    p_oTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    p_oTree = p_oTree7;
    fExpectedDiam = 2.132818092;
    fExpectedHeight = 0.511876342;
    fExpectedGrowth = 0.221363486;
    p_oTree->GetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
    p_oTree->GetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fHeight);
    p_oTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    p_oTree = p_oTree8;
    fExpectedDiam = 3.181030877;
    fExpectedHeight = 0.76344741;
    fExpectedGrowth = 0.301718128;
    p_oTree->GetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
    p_oTree->GetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fHeight);
    p_oTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    p_oTree = p_oTree9;
    fExpectedDiam = 4.320900701;
    fExpectedHeight = 0.993807161;
    fExpectedGrowth = 0.534834502;
    p_oTree->GetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
    p_oTree->GetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fHeight);
    p_oTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    p_oTree = p_oTree10;
    fExpectedDiam = 5.489355623;
    fExpectedHeight = 1.262551793;
    fExpectedGrowth = 0.815592705;
    p_oTree->GetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
    p_oTree->GetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fHeight);
    p_oTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    p_oTree = p_oTree11;
    fExpectedDiam = 1.070303304;
    fExpectedHeight = 0.224763694;
    fExpectedGrowth = 0.117172174;
    p_oTree->GetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
    p_oTree->GetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fHeight);
    p_oTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    p_oTree = p_oTree12;
    fExpectedDiam = 2.170446272;
    fExpectedHeight = 0.4774981;
    fExpectedGrowth = 0.28407712;
    p_oTree->GetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
    p_oTree->GetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fHeight);
    p_oTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    p_oTree = p_oTree13;
    fExpectedDiam = 3.22356188;
    fExpectedHeight = 0.709183614;
    fExpectedGrowth = 0.372603134;
    p_oTree->GetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
    p_oTree->GetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fHeight);
    p_oTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    p_oTree = p_oTree14;
    fExpectedDiam = 4.170575394;
    fExpectedHeight = 0.875820833;
    fExpectedGrowth = 0.284292324;
    p_oTree->GetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
    p_oTree->GetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fHeight);
    p_oTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    p_oTree = p_oTree15;
    fExpectedDiam = 5.255504473;
    fExpectedHeight = 1.103655939;
    fExpectedGrowth = 0.425840788;
    p_oTree->GetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
    p_oTree->GetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fHeight);
    p_oTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    p_oTree = p_oTree16;
    fExpectedDiam = 1.133503122;
    fExpectedHeight = 0.260705718;
    fExpectedGrowth = 0.222505204;
    p_oTree->GetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
    p_oTree->GetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fHeight);
    p_oTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    p_oTree = p_oTree17;
    fExpectedDiam = 4.295057045;
    fExpectedHeight = 1.030813691;
    fExpectedGrowth = 3.825095075;
    p_oTree->GetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
    p_oTree->GetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fHeight);
    p_oTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    p_oTree = p_oTree18;
    fExpectedDiam = 4.150005822;
    fExpectedHeight = 0.996001397;
    fExpectedGrowth = 3.583343037;
    p_oTree->GetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
    p_oTree->GetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fHeight);
    p_oTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    p_oTree = p_oTree19;
    fExpectedDiam = 4.683196336;
    fExpectedHeight = 1.077135157;
    fExpectedGrowth = 1.138660559;
    p_oTree->GetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
    p_oTree->GetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fHeight);
    p_oTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    p_oTree = p_oTree20;
    fExpectedDiam = 4.704887926;
    fExpectedHeight = 1.082124223;
    fExpectedGrowth = 1.17481321;
    p_oTree->GetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
    p_oTree->GetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fHeight);
    p_oTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), &fGrowth);
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
// TestNormalRun3()
// Tests when growth is diam only.
////////////////////////////////////////////////////////////////////////////
TEST(BrowsedRelativeGrowth, TestNormalRun3) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTree *p_oTree1, *p_oTree2, *p_oTree3, *p_oTree4, *p_oTree5, *p_oTree6,
    *p_oTree7, *p_oTree8, *p_oTree9, *p_oTree10, *p_oTree11, *p_oTree12,
    *p_oTree13, *p_oTree14, *p_oTree15, *p_oTree16, *p_oTree17, *p_oTree18,
    *p_oTree19, *p_oTree20, *p_oTree;
    float fDiam, fHeight, fExpectedDiam, fExpectedHeight, fLight, fGrowth,
    fExpectedGrowth;
    int iSp;
    bool bBrowsed;

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteBrowsedRelativeGrowthXMLFile3() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create our ten trees and set diameter, height, and GLI for each
    iSp=0;  fLight=60;  fDiam=1.0;  bBrowsed=false; fHeight=0.8;
    p_oTree = p_oPop->CreateTree(9, 9, iSp, clTreePopulation::seedling, fDiam);
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType()), fLight, false, false);
    p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", p_oTree->GetSpecies(), p_oTree->GetType()), bBrowsed);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), fHeight, false, false);
    p_oTree1 = p_oTree;

    iSp=1;  fLight=80;  fDiam=2.0;  bBrowsed=false; fHeight=0.8;
    p_oTree = p_oPop->CreateTree(9, 9, iSp, clTreePopulation::seedling, fDiam);
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType()), fLight, false, false);
    p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", p_oTree->GetSpecies(), p_oTree->GetType()), bBrowsed);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), fHeight, false, false);
    p_oTree2 = p_oTree;

    iSp=1;  fLight=10;  fDiam=3.0;  bBrowsed=false; fHeight=0.8;
    p_oTree = p_oPop->CreateTree(9, 9, iSp, clTreePopulation::seedling, fDiam);
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType()), fLight, false, false);
    p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", p_oTree->GetSpecies(), p_oTree->GetType()), bBrowsed);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), fHeight, false, false);
    p_oTree3 = p_oTree;

    iSp=0;  fLight=2; fDiam=4.0;  bBrowsed=false; fHeight=0.8;
    p_oTree = p_oPop->CreateTree(1, 1, iSp, clTreePopulation::seedling, fDiam);
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType()), fLight, false, false);
    p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", p_oTree->GetSpecies(), p_oTree->GetType()), bBrowsed);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), fHeight, false, false);
    p_oTree4 = p_oTree;

    iSp=0;  fLight=90;  fDiam=5.0;  bBrowsed=false; fHeight=0.8;
    p_oTree = p_oPop->CreateTree(9, 9, iSp, clTreePopulation::seedling, fDiam);
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType()), fLight, false, false);
    p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", p_oTree->GetSpecies(), p_oTree->GetType()), bBrowsed);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), fHeight, false, false);
    p_oTree5 = p_oTree;

    iSp=2;  fLight=60;  fDiam=1.0;  bBrowsed=false; fHeight=0.8;
    p_oTree = p_oPop->CreateTree(9, 9, iSp, clTreePopulation::seedling, fDiam);
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType()), fLight, false, false);
    p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", p_oTree->GetSpecies(), p_oTree->GetType()), bBrowsed);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), fHeight, false, false);
    p_oTree6 = p_oTree;

    iSp=3;  fLight=70;  fDiam=2.0;  bBrowsed=false; fHeight=0.8;
    p_oTree = p_oPop->CreateTree(9, 9, iSp, clTreePopulation::seedling, fDiam);
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType()), fLight, false, false);
    p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", p_oTree->GetSpecies(), p_oTree->GetType()), bBrowsed);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), fHeight, false, false);
    p_oTree7 = p_oTree;

    iSp=3;  fLight=10;  fDiam=3.0;  bBrowsed=false; fHeight=0.8;
    p_oTree = p_oPop->CreateTree(9, 9, iSp, clTreePopulation::seedling, fDiam);
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType()), fLight, false, false);
    p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", p_oTree->GetSpecies(), p_oTree->GetType()), bBrowsed);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), fHeight, false, false);
    p_oTree8 = p_oTree;

    iSp=2;  fLight=2; fDiam=4.0;  bBrowsed=false; fHeight=0.8;
    p_oTree = p_oPop->CreateTree(9, 9, iSp, clTreePopulation::seedling, fDiam);
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType()), fLight, false, false);
    p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", p_oTree->GetSpecies(), p_oTree->GetType()), bBrowsed);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), fHeight, false, false);
    p_oTree9 = p_oTree;

    iSp=2;  fLight=90;  fDiam=5.0;  bBrowsed=false; fHeight=0.8;
    p_oTree = p_oPop->CreateTree(9, 9, iSp, clTreePopulation::seedling, fDiam);
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType()), fLight, false, false);
    p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", p_oTree->GetSpecies(), p_oTree->GetType()), bBrowsed);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), fHeight, false, false);
    p_oTree10 = p_oTree;

    iSp=0;  fLight=60;  fDiam=1.0;  bBrowsed=true; fHeight=0.8;
    p_oTree = p_oPop->CreateTree(9, 9, iSp, clTreePopulation::seedling, fDiam);
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType()), fLight, false, false);
    p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", p_oTree->GetSpecies(), p_oTree->GetType()), bBrowsed);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), fHeight, false, false);
    p_oTree11 = p_oTree;

    iSp=1;  fLight=80;  fDiam=2.0;  bBrowsed=true; fHeight=0.8;
    p_oTree = p_oPop->CreateTree(9, 9, iSp, clTreePopulation::seedling, fDiam);
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType()), fLight, false, false);
    p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", p_oTree->GetSpecies(), p_oTree->GetType()), bBrowsed);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), fHeight, false, false);
    p_oTree12 = p_oTree;

    iSp=1;  fLight=10;  fDiam=3.0;  bBrowsed=true; fHeight=0.8;
    p_oTree = p_oPop->CreateTree(9, 9, iSp, clTreePopulation::seedling, fDiam);
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType()), fLight, false, false);
    p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", p_oTree->GetSpecies(), p_oTree->GetType()), bBrowsed);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), fHeight, false, false);
    p_oTree13 = p_oTree;

    iSp=0;  fLight=2; fDiam=4.0;  bBrowsed=true; fHeight=0.8;
    p_oTree = p_oPop->CreateTree(9, 9, iSp, clTreePopulation::seedling, fDiam);
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType()), fLight, false, false);
    p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", p_oTree->GetSpecies(), p_oTree->GetType()), bBrowsed);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), fHeight, false, false);
    p_oTree14 = p_oTree;

    iSp=0;  fLight=90;  fDiam=5.0;  bBrowsed=true; fHeight=0.8;
    p_oTree = p_oPop->CreateTree(9, 9, iSp, clTreePopulation::seedling, fDiam);
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType()), fLight, false, false);
    p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", p_oTree->GetSpecies(), p_oTree->GetType()), bBrowsed);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), fHeight, false, false);
    p_oTree15 = p_oTree;

    iSp=2;  fLight=60;  fDiam=1.0;  bBrowsed=true; fHeight=0.8;
    p_oTree = p_oPop->CreateTree(9, 9, iSp, clTreePopulation::seedling, fDiam);
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType()), fLight, false, false);
    p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", p_oTree->GetSpecies(), p_oTree->GetType()), bBrowsed);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), fHeight, false, false);
    p_oTree16 = p_oTree;

    iSp=3;  fLight=70;  fDiam=2.0;  bBrowsed=true; fHeight=0.8;
    p_oTree = p_oPop->CreateTree(9, 9, iSp, clTreePopulation::seedling, fDiam);
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType()), fLight, false, false);
    p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", p_oTree->GetSpecies(), p_oTree->GetType()), bBrowsed);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), fHeight, false, false);
    p_oTree17 = p_oTree;

    iSp=3;  fLight=10;  fDiam=3.0;  bBrowsed=true; fHeight=0.8;
    p_oTree = p_oPop->CreateTree(9, 9, iSp, clTreePopulation::seedling, fDiam);
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType()), fLight, false, false);
    p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", p_oTree->GetSpecies(), p_oTree->GetType()), bBrowsed);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), fHeight, false, false);
    p_oTree18 = p_oTree;

    iSp=2;  fLight=2; fDiam=4.0;  bBrowsed=true; fHeight=0.8;
    p_oTree = p_oPop->CreateTree(9, 9, iSp, clTreePopulation::seedling, fDiam);
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType()), fLight, false, false);
    p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", p_oTree->GetSpecies(), p_oTree->GetType()), bBrowsed);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), fHeight, false, false);
    p_oTree19 = p_oTree;

    iSp=2;  fLight=90;  fDiam=5.0;  bBrowsed=true; fHeight=0.8;
    p_oTree = p_oPop->CreateTree(9, 9, iSp, clTreePopulation::seedling, fDiam);
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType()), fLight, false, false);
    p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", p_oTree->GetSpecies(), p_oTree->GetType()), bBrowsed);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), fHeight, false, false);
    p_oTree20 = p_oTree;

    //Now run growth, but skip light and browse
    clBehaviorBase *p_oBase = p_oSimManager->GetBehaviorObject(2);
    p_oBase->Action();
    p_oBase = p_oSimManager->GetBehaviorObject(3);
    p_oBase->Action();

    //Confirm all trees
    p_oTree = p_oTree1;
    fExpectedDiam = 1.01719425;
    fExpectedHeight = 0.803610794;
    fExpectedGrowth = 0.085971296;
    p_oTree->GetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
    p_oTree->GetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fHeight);
    p_oTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    p_oTree = p_oTree2;
    fExpectedDiam = 2.074287108;
    fExpectedHeight = 0.816343164;
    fExpectedGrowth = 0.371435542;
    p_oTree->GetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
    p_oTree->GetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fHeight);
    p_oTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    p_oTree = p_oTree3;
    fExpectedDiam = 3.102193882;
    fExpectedHeight = 0.822482654;
    fExpectedGrowth = 0.510969408;
    p_oTree->GetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
    p_oTree->GetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fHeight);
    p_oTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    p_oTree = p_oTree4;
    fExpectedDiam = 4.078246704;
    fExpectedHeight = 0.816431808;
    fExpectedGrowth = 0.39123352;
    p_oTree->GetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
    p_oTree->GetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fHeight);
    p_oTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    p_oTree = p_oTree5;
    fExpectedDiam = 5.100994749;
    fExpectedHeight = 0.821208897;
    fExpectedGrowth = 0.50497374;
    p_oTree->GetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
    p_oTree->GetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fHeight);
    p_oTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    p_oTree = p_oTree6;
    fExpectedDiam = 1.01970683;
    fExpectedHeight = 0.804532571;
    fExpectedGrowth = 0.098534151;
    p_oTree->GetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
    p_oTree->GetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fHeight);
    p_oTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    p_oTree = p_oTree7;
    fExpectedDiam = 2.043261981;
    fExpectedHeight = 0.810382876;
    fExpectedGrowth = 0.216309907;
    p_oTree->GetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
    p_oTree->GetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fHeight);
    p_oTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    p_oTree = p_oTree8;
    fExpectedDiam = 3.059037414;
    fExpectedHeight = 0.814168979;
    fExpectedGrowth = 0.295187069;
    p_oTree->GetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
    p_oTree->GetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fHeight);
    p_oTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    p_oTree = p_oTree9;
    fExpectedDiam = 4.105133296;
    fExpectedHeight = 0.824180658;
    fExpectedGrowth = 0.52566648;
    p_oTree->GetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
    p_oTree->GetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fHeight);
    p_oTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    p_oTree = p_oTree10;
    fExpectedDiam = 5.159940891;
    fExpectedHeight = 0.836786405;
    fExpectedGrowth = 0.799704457;
    p_oTree->GetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
    p_oTree->GetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fHeight);
    p_oTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    p_oTree = p_oTree11;
    fExpectedDiam = 1.022905755;
    fExpectedHeight = 0.804810209;
    fExpectedGrowth = 0.114528776;
    p_oTree->GetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
    p_oTree->GetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fHeight);
    p_oTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    p_oTree = p_oTree12;
    fExpectedDiam = 2.055273757;
    fExpectedHeight = 0.812160227;
    fExpectedGrowth = 0.276368786;
    p_oTree->GetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
    p_oTree->GetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fHeight);
    p_oTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    p_oTree = p_oTree13;
    fExpectedDiam = 3.072742545;
    fExpectedHeight = 0.81600336;
    fExpectedGrowth = 0.363712724;
    p_oTree->GetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
    p_oTree->GetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fHeight);
    p_oTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    p_oTree = p_oTree14;
    fExpectedDiam = 4.055824147;
    fExpectedHeight = 0.811723071;
    fExpectedGrowth = 0.279120736;
    p_oTree->GetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
    p_oTree->GetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fHeight);
    p_oTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    p_oTree = p_oTree15;
    fExpectedDiam = 5.08324145;
    fExpectedHeight = 0.817480704;
    fExpectedGrowth = 0.416207249;
    p_oTree->GetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
    p_oTree->GetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fHeight);
    p_oTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    p_oTree = p_oTree16;
    fExpectedDiam = 1.042655664;
    fExpectedHeight = 0.809810803;
    fExpectedGrowth = 0.213278322;
    p_oTree->GetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
    p_oTree->GetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fHeight);
    p_oTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    p_oTree = p_oTree17;
    fExpectedDiam = 2.612080591;
    fExpectedHeight = 0.946899342;
    fExpectedGrowth = 3.060402957;
    p_oTree->GetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
    p_oTree->GetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fHeight);
    p_oTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    p_oTree = p_oTree18;
    fExpectedDiam = 4.023020746;
    fExpectedHeight = 1.045524979;
    fExpectedGrowth = 5.115103728;
    p_oTree->GetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
    p_oTree->GetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fHeight);
    p_oTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    p_oTree = p_oTree19;
    fExpectedDiam = 4.218557007;
    fExpectedHeight = 0.850268112;
    fExpectedGrowth = 1.092785036;
    p_oTree->GetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
    p_oTree->GetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fHeight);
    p_oTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    p_oTree = p_oTree20;
    fExpectedDiam = 5.294368308;
    fExpectedHeight = 0.867704711;
    fExpectedGrowth = 1.471841541;
    p_oTree->GetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
    p_oTree->GetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fHeight);
    p_oTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), &fGrowth);
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
TEST(BrowsedRelativeGrowth, TestErrorProcessing) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try
  {
    p_oSimManager->ReadFile(WriteBrowsedRelativeGrowthXMLErrorFile1());
    FAIL() << "TestBrowsedRelativeGrowth error processing didn't catch error for WriteBrowsedRelativeGrowthXMLErrorFile1.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clBrowsedRelativeGrowth::DoShellSetup") != 0)
    {
      FAIL() << "TestBrowsedRelativeGrowth error processing caught wrong error for WriteBrowsedRelativeGrowthXMLErrorFile1.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteBrowsedRelativeGrowthXMLErrorFile2());
    FAIL() << "TestBrowsedRelativeGrowth error processing didn't catch error for WriteBrowsedRelativeGrowthXMLErrorFile2.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clBrowsedRelativeGrowth::DoShellSetup") != 0)
    {
      FAIL() << "TestBrowsedRelativeGrowth error processing caught wrong error for WriteBrowsedRelativeGrowthXMLErrorFile2.";
    }
    ;
  }
  delete p_oSimManager;
}

////////////////////////////////////////////////////////////////////////////
// WriteBrowsedRelativeGrowthXMLFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteBrowsedRelativeGrowthXMLFile1() {
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

  WriteBrowsedRelativeGrowthPlotAndTrees(oOut);

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>RandomBrowse</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_4\" type=\"Seedling\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>ConstantGLI</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_4\" type=\"Seedling\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>BrowsedRelativeGrowth</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>3</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_4\" type=\"Seedling\"/>"
      << "</behavior>"
      << "</behaviorList>";

  WriteBrowsedRelativeGrowthCommonParameters(oOut);

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteBrowsedRelativeGrowthXMLFile2()
////////////////////////////////////////////////////////////////////////////
const char* WriteBrowsedRelativeGrowthXMLFile2() {
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

  WriteBrowsedRelativeGrowthPlotAndTrees(oOut);

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>RandomBrowse</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_4\" type=\"Seedling\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>ConstantGLI</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_4\" type=\"Seedling\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>BrowsedRelativeGrowth</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>3</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_4\" type=\"Seedling\"/>"
      << "</behavior>"
      << "</behaviorList>";

  WriteBrowsedRelativeGrowthCommonParameters(oOut);

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteBrowsedRelativeGrowthXMLFile3()
////////////////////////////////////////////////////////////////////////////
const char* WriteBrowsedRelativeGrowthXMLFile3() {
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

  WriteBrowsedRelativeGrowthPlotAndTrees(oOut);

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>RandomBrowse</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_4\" type=\"Seedling\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>ConstantGLI</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_4\" type=\"Seedling\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>BrowsedRelativeGrowth diam only</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>3</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_4\" type=\"Seedling\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>HeightIncrementer</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>4</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_4\" type=\"Seedling\"/>"
      << "</behavior>"
      << "</behaviorList>";

  WriteBrowsedRelativeGrowthCommonParameters(oOut);

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteBrowsedRelativeGrowthXMLErrorFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteBrowsedRelativeGrowthXMLErrorFile1() {
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

  WriteBrowsedRelativeGrowthPlotAndTrees(oOut);

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>RandomBrowse</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_4\" type=\"Seedling\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>ConstantGLI</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_4\" type=\"Seedling\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>BrowsedRelativeGrowth</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>3</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_4\" type=\"Seedling\"/>"
      << "</behavior>"
      << "</behaviorList>";

  WriteBrowsedRelativeGrowthCommonParameters(oOut);

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteBrowsedRelativeGrowthXMLErrorFile2()
////////////////////////////////////////////////////////////////////////////
const char* WriteBrowsedRelativeGrowthXMLErrorFile2() {
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

  WriteBrowsedRelativeGrowthPlotAndTrees(oOut);

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>RandomBrowse</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>ConstantGLI</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_4\" type=\"Seedling\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>BrowsedRelativeGrowth</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>3</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_4\" type=\"Seedling\"/>"
      << "</behavior>"
      << "</behaviorList>";

  WriteBrowsedRelativeGrowthCommonParameters(oOut);

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteBrowsedRelativeGrowthPlotAndTrees()
/////////////////////////////////////////////////////////////////////////////
void WriteBrowsedRelativeGrowthPlotAndTrees( std::fstream &oOut )
{
  using namespace std;
  oOut << "<plot_lenX>500.0</plot_lenX>"
      << "<plot_lenY>500.0</plot_lenY>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88171785</plot_temp_C>"
      << "<randomSeed>1</randomSeed>"
      << "<plot_latitude>41.92</plot_latitude>"
      << "<plot_title>Test</plot_title>"
      << "</plot>"
      << "<trees>"
      << "<tr_speciesList>"
      << "<tr_species speciesName=\"Species_1\"/>"
      << "<tr_species speciesName=\"Species_2\"/>"
      << "<tr_species speciesName=\"Species_3\"/>"
      << "<tr_species speciesName=\"Species_4\"/>"
      << "</tr_speciesList>"
      << "<tr_seedDiam10Cm>0.2</tr_seedDiam10Cm>"
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
      << "</trees>";
}

/////////////////////////////////////////////////////////////////////////////
// WriteBrowsedRelativeGrowthCommonParameters()
/////////////////////////////////////////////////////////////////////////////
void WriteBrowsedRelativeGrowthCommonParameters( std::fstream &oOut )
{
  using namespace std;

  oOut << "<allometry>"
      << "<tr_whatAdultHeightDiam>"
      << "<tr_wahdVal species=\"Species_1\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_2\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_3\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_4\">0</tr_wahdVal>"
      << "</tr_whatAdultHeightDiam>"
      << "<tr_whatSaplingHeightDiam>"
      << "<tr_wsahdVal species=\"Species_1\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_2\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_3\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_4\">0</tr_wsahdVal>"
      << "</tr_whatSaplingHeightDiam>"
      << "<tr_whatSeedlingHeightDiam>"
      << "<tr_wsehdVal species=\"Species_1\">1</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_2\">1</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_3\">1</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_4\">1</tr_wsehdVal>"
      << "</tr_whatSeedlingHeightDiam>"
      << "<tr_whatAdultCrownRadDiam>"
      << "<tr_wacrdVal species=\"Species_1\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Species_2\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Species_3\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Species_4\">0</tr_wacrdVal>"
      << "</tr_whatAdultCrownRadDiam>"
      << "<tr_whatSaplingCrownRadDiam>"
      << "<tr_wscrdVal species=\"Species_1\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Species_2\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Species_3\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Species_4\">0</tr_wscrdVal>"
      << "</tr_whatSaplingCrownRadDiam>"
      << "<tr_whatAdultCrownHeightHeight>"
      << "<tr_wachhVal species=\"Species_1\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Species_2\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Species_3\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Species_4\">0</tr_wachhVal>"
      << "</tr_whatAdultCrownHeightHeight>"
      << "<tr_whatSaplingCrownHeightHeight>"
      << "<tr_wschhVal species=\"Species_1\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Species_2\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Species_3\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Species_4\">0</tr_wschhVal>"
      << "</tr_whatSaplingCrownHeightHeight>"
      << "<tr_canopyHeight>"
      << "<tr_chVal species=\"Species_1\">30.0</tr_chVal>"
      << "<tr_chVal species=\"Species_2\">30.0</tr_chVal>"
      << "<tr_chVal species=\"Species_3\">30.0</tr_chVal>"
      << "<tr_chVal species=\"Species_4\">30.0</tr_chVal>"
      << "</tr_canopyHeight>"
      << "<tr_stdAsympCrownRad>"
      << "<tr_sacrVal species=\"Species_1\">0.108</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_2\">0.107</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_3\">0.109</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_4\">0.152</tr_sacrVal>"
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
      << "<tr_stdAsympCrownHt>"
      << "<tr_sachVal species=\"Species_1\">0.49</tr_sachVal>"
      << "<tr_sachVal species=\"Species_2\">0.58</tr_sachVal>"
      << "<tr_sachVal species=\"Species_3\">0.54</tr_sachVal>"
      << "<tr_sachVal species=\"Species_4\">0.66</tr_sachVal>"
      << "</tr_stdAsympCrownHt>"
      << "<tr_stdCrownHtExp>"
      << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_3\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_4\">1.0</tr_scheVal>"
      << "</tr_stdCrownHtExp>"
      << "<tr_conversionDiam10ToDBH>"
      << "<tr_cdtdVal species=\"Species_1\">0.75</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_2\">0.75</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_3\">0.75</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_4\">0.75</tr_cdtdVal>"
      << "</tr_conversionDiam10ToDBH>"
      << "<tr_interceptDiam10ToDBH>"
      << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_3\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_4\">0</tr_idtdVal>"
      << "</tr_interceptDiam10ToDBH>"
      << "<tr_seedlingLinearSlope>"
      << "<tr_selsVal species=\"Species_1\">0.21</tr_selsVal>"
      << "<tr_selsVal species=\"Species_2\">0.22</tr_selsVal>"
      << "<tr_selsVal species=\"Species_3\">0.23</tr_selsVal>"
      << "<tr_selsVal species=\"Species_4\">0.24</tr_selsVal>"
      << "</tr_seedlingLinearSlope>"
      << "<tr_seedlingLinearIntercept>"
      << "<tr_seliVal species=\"Species_1\">0.0</tr_seliVal>"
      << "<tr_seliVal species=\"Species_2\">0.0</tr_seliVal>"
      << "<tr_seliVal species=\"Species_3\">0.0</tr_seliVal>"
      << "<tr_seliVal species=\"Species_4\">0.0</tr_seliVal>"
      << "</tr_seedlingLinearIntercept>"
      << "<tr_slopeOfAsymHeight>"
      << "<tr_soahVal species=\"Species_1\">0.063</tr_soahVal>"
      << "<tr_soahVal species=\"Species_2\">0.062</tr_soahVal>"
      << "<tr_soahVal species=\"Species_3\">0.063</tr_soahVal>"
      << "<tr_soahVal species=\"Species_4\">0.035</tr_soahVal>"
      << "</tr_slopeOfAsymHeight>"
      << "</allometry>"
      << "<RandomBrowse1>"
      << "<di_randBrowsePDF>0</di_randBrowsePDF>"
      << "<di_randBrowseProb>"
      << "<di_rbpVal species=\"Species_1\">0.33</di_rbpVal>"
      << "<di_rbpVal species=\"Species_2\">1</di_rbpVal>"
      << "<di_rbpVal species=\"Species_3\">0.0</di_rbpVal>"
      << "<di_rbpVal species=\"Species_4\">0.66</di_rbpVal>"
      << "</di_randBrowseProb>"
      << "</RandomBrowse1>"
      << "<ConstantGLI2>"
      << "<li_constGLI>100</li_constGLI>"
      << "</ConstantGLI2>"
      << "<BrowsedRelativeGrowth3>"
      << "<gr_asympDiameterGrowth>"
      << "<gr_adgVal species=\"Species_1\">0.0172</gr_adgVal>"
      << "<gr_adgVal species=\"Species_2\">0.0427</gr_adgVal>"
      << "<gr_adgVal species=\"Species_3\">0.0198</gr_adgVal>"
      << "<gr_adgVal species=\"Species_4\">0.0234</gr_adgVal>"
      << "</gr_asympDiameterGrowth>"
      << "<gr_slopeGrowthResponse>"
      << "<gr_sgrVal species=\"Species_1\">0.8586</gr_sgrVal>"
      << "<gr_sgrVal species=\"Species_2\">0.6847</gr_sgrVal>"
      << "<gr_sgrVal species=\"Species_3\">0.0698</gr_sgrVal>"
      << "<gr_sgrVal species=\"Species_4\">0.0358</gr_sgrVal>"
      << "</gr_slopeGrowthResponse>"
      << "<gr_relGrowthDiamExp>"
      << "<gr_rgdeVal species=\"Species_1\">1.1</gr_rgdeVal>"
      << "<gr_rgdeVal species=\"Species_2\">0.8</gr_rgdeVal>"
      << "<gr_rgdeVal species=\"Species_3\">1.3</gr_rgdeVal>"
      << "<gr_rgdeVal species=\"Species_4\">0.9</gr_rgdeVal>"
      << "</gr_relGrowthDiamExp>"
      << "<gr_browsedAsympDiameterGrowth>"
      << "<gr_badgVal species=\"Species_1\">0.0231</gr_badgVal>"
      << "<gr_badgVal species=\"Species_2\">0.0282</gr_badgVal>"
      << "<gr_badgVal species=\"Species_3\">0.0427</gr_badgVal>"
      << "<gr_badgVal species=\"Species_4\">0.2341</gr_badgVal>"
      << "</gr_browsedAsympDiameterGrowth>"
      << "<gr_browsedSlopeGrowthResponse>"
      << "<gr_bsgrVal species=\"Species_1\">0.0454</gr_bsgrVal>"
      << "<gr_bsgrVal species=\"Species_2\">0.0173</gr_bsgrVal>"
      << "<gr_bsgrVal species=\"Species_3\">0.6847</gr_bsgrVal>"
      << "<gr_bsgrVal species=\"Species_4\">0.3583</gr_bsgrVal>"
      << "</gr_browsedSlopeGrowthResponse>"
      << "<gr_browsedRelGrowthDiamExp>"
      << "<gr_brgdeVal species=\"Species_1\">0.8</gr_brgdeVal>"
      << "<gr_brgdeVal species=\"Species_2\">1</gr_brgdeVal>"
      << "<gr_brgdeVal species=\"Species_3\">1.2</gr_brgdeVal>"
      << "<gr_brgdeVal species=\"Species_4\">1.4</gr_brgdeVal>"
      << "</gr_browsedRelGrowthDiamExp>"
      << "</BrowsedRelativeGrowth3>"
      << "</paramFile>";
}
