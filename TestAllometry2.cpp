//---------------------------------------------------------------------------
// TestAllometry.cpp
//---------------------------------------------------------------------------
#include "TestAllometry.h"
#include "TestAllometry2.h"
#include <gtest/gtest.h>
#include "TreePopulation.h"
#include "SimManager.h"
#include "Allometry.h"
#include <fstream>
#include <iostream>
#include <math.h>

/////////////////////////////////////////////////////////////////////////////
// TestDensityDependentCrownAllometry
// Verifies that non-spatial density dependent crown allometry functions
// calculate correctly.  This run uses WriteAllometryXMLFile7 for setup. This file
// contains 4 species, three of which use those functions.
/////////////////////////////////////////////////////////////////////////////
TEST(Allometry, DensityDependentCrownAllometry)
{
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation *p_oPop;
    clTree *p_oTree;
    clAllometry *p_oAllom;
    float fX, fY, fDBH, fHeight, fExpCrownDepth, fExpCrownRad,
    fActual;
    int iSpecies, i;

    p_oSimManager->ReadFile(WriteAllometryXMLFile7());
    p_oPop = (clTreePopulation*) p_oSimManager->GetPopulationObject("treepopulation");
    p_oAllom = p_oPop->GetAllometryObject();

    EXPECT_EQ(1000, p_oAllom->GetMaxCrownRadius());

    //Create the trees
    fX = 1; fY = 1; iSpecies = 0; fDBH = 20.9245;
    p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDBH );

    fX = 2; fY = 2; iSpecies = 3; fDBH = 54.7187;
    p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDBH );

    fX = 3; fY = 3; iSpecies = 1; fDBH = 39.1188;
    p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDBH );

    fX = 4; fY = 4; iSpecies = 3; fDBH = 71.1313;
    p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDBH );

    fX = 5; fY = 5; iSpecies = 3; fDBH = 45.3493;
    p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDBH );

    fX = 6; fY = 6; iSpecies = 0; fDBH = 25.13;
    p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDBH );

    fX = 7; fY = 7; iSpecies = 2; fDBH = 48.4916;
    p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDBH );

    fX = 8; fY = 8; iSpecies = 0; fDBH = 26.3038;
    p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDBH );

    fX = 9; fY = 9; iSpecies = 3; fDBH = 67.8397;
    p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDBH );

    fX = 10; fY = 10; iSpecies = 1; fDBH = 43.5958;
    p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDBH );

    fX = 11; fY = 11; iSpecies = 3; fDBH = 59.6401;
    p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDBH );

    fX = 12; fY = 12; iSpecies = 0; fDBH = 33.0471;
    p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDBH );

    fX = 13; fY = 13; iSpecies = 3; fDBH = 93.7086;
    p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDBH );

    fX = 14; fY = 14; iSpecies = 3; fDBH = 48.8456;
    p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDBH );

    fX = 15; fY = 15; iSpecies = 3; fDBH = 50.7243;
    p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDBH );

    fX = 16; fY = 16; iSpecies = 3; fDBH = 50.9807;
    p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDBH );

    fX = 17; fY = 17; iSpecies = 3; fDBH = 84.8799;
    p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDBH );

    fX = 18; fY = 18; iSpecies = 3; fDBH = 67.1728;
    p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDBH );

    fX = 19; fY = 19; iSpecies = 2; fDBH = 32.443;
    p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDBH );

    fX = 20; fY = 20; iSpecies = 1; fDBH = 35.3926;
    p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDBH );

    fX = 21; fY = 21; iSpecies = 1; fDBH = 38.5777;
    p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDBH );

    fX = 22; fY = 22; iSpecies = 1; fDBH = 44.5903;
    p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDBH );

    fX = 23; fY = 23; iSpecies = 2; fDBH = 42.7597;
    p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDBH );

    fX = 24; fY = 24; iSpecies = 3; fDBH = 38.1041;
    p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDBH );

    fX = 25; fY = 25; iSpecies = 3; fDBH = 62.0297;
    p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDBH );

    fX = 26; fY = 26; iSpecies = 2; fDBH = 44.2927;
    p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDBH );

    fX = 27; fY = 27; iSpecies = 0; fDBH = 19.9621;
    p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDBH );

    fX = 28; fY = 28; iSpecies = 3; fDBH = 15.6386;
    p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDBH );

    fX = 29; fY = 29; iSpecies = 2; fDBH = 23.0316;
    p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDBH );

    fX = 30; fY = 30; iSpecies = 3; fDBH = 51.6542;
    p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDBH );

    fX = 31; fY = 31; iSpecies = 0; fDBH = 38.8274;
    p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDBH );

    fX = 32; fY = 32; iSpecies = 0; fDBH = 9.9621;
    p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::sapling, fDBH );

    fX = 33; fY = 33; iSpecies = 3; fDBH = 5.6386;
    p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::sapling, fDBH );

    fX = 34; fY = 34; iSpecies = 2; fDBH = 3.0316;
    p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::sapling, fDBH );

    fX = 35; fY = 35; iSpecies = 3; fDBH = 1.6542;
    p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::sapling, fDBH );

    //Save one tree - we'll calculate its relationships first, so that we
    //will have triggered the plot density calculations before we have to create
    //test trees
    fX = 36; fY = 36; iSpecies = 0; fDBH = 8.8274;
    p_oTree = p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::sapling, fDBH );

    fX = 37; fY = 37; iSpecies = 3; fDBH = 0.1;
    p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::seedling, fDBH );

    fX = 38; fY = 38; iSpecies = 1; fDBH = 0.1;
    p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::seedling, fDBH );

    fX = 39; fY = 39; iSpecies = 0; fDBH = 0.1;
    p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::seedling, fDBH );

    fX = 40; fY = 40; iSpecies = 3; fDBH = 0.1;
    p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::seedling, fDBH );

    fX = 40; fY = 40; iSpecies = 2; fDBH = 0.1;
    p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::seedling, fDBH );

    fX = 41; fY = 41; iSpecies = 3; fDBH = 0.1;
    p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::seedling, fDBH );

    fX = 42; fY = 42; iSpecies = 1; fDBH = 0.1;
    p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::seedling, fDBH );

    //Calculate the crown radius of our saved tree to trigger the plot
    //calculations
    fActual = p_oAllom->CalcAdultCrownDepth(p_oTree);

    //Test the crown radius and crown height for each tree
    iSpecies = 0; fDBH = 20.9245; fHeight = 11.3698;
    p_oTree = p_oPop->CreateTree(1,1,iSpecies,clTreePopulation::adult,fDBH);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()),fHeight, false);
    fExpCrownRad = 2.605371776; fExpCrownDepth = 7.513287765;
    fActual = p_oAllom->CalcAdultCrownDepth(p_oTree);
    EXPECT_LT(fabs(fExpCrownDepth - fActual)/fExpCrownDepth, 0.01);
    fActual = p_oAllom->CalcAdultCrownRadius(p_oTree);
    EXPECT_LT(fabs(fExpCrownRad - fActual)/fExpCrownRad, 0.01);
    p_oPop->KillTree(p_oTree,remove_tree);

    iSpecies = 3; fDBH = 54.7187; fHeight = 44.30309;
    p_oTree = p_oPop->CreateTree(1,1,iSpecies,clTreePopulation::adult,fDBH);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()),fHeight, false);
    fExpCrownRad = 5.841479418; fExpCrownDepth = 0.194576868;
    fActual = p_oAllom->CalcAdultCrownDepth(p_oTree);
    EXPECT_LT(fabs(fExpCrownDepth - fActual)/fExpCrownDepth, 0.01);
    fActual = p_oAllom->CalcAdultCrownRadius(p_oTree);
    EXPECT_LT(fabs(fExpCrownRad - fActual)/fExpCrownRad, 0.01);
    p_oPop->KillTree(p_oTree,remove_tree);

    iSpecies = 1; fDBH = 39.1188; fHeight = 23.5594;
    p_oTree = p_oPop->CreateTree(1,1,iSpecies,clTreePopulation::adult,fDBH);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()),fHeight, false);
    fExpCrownRad = 4.471934894; fExpCrownDepth = 0.043796564;
    fActual = p_oAllom->CalcAdultCrownDepth(p_oTree);
    EXPECT_LT(fabs(fExpCrownDepth - fActual)/fExpCrownDepth, 0.01);
    fActual = p_oAllom->CalcAdultCrownRadius(p_oTree);
    EXPECT_LT(fabs(fExpCrownRad - fActual)/fExpCrownRad, 0.01);
    p_oPop->KillTree(p_oTree,remove_tree);

    iSpecies = 3; fDBH = 71.1313; fHeight = 55.79192;
    p_oTree = p_oPop->CreateTree(1,1,iSpecies,clTreePopulation::adult,fDBH);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()),fHeight, false);
    fExpCrownRad = 7.453981042; fExpCrownDepth = 0.590977705;
    fActual = p_oAllom->CalcAdultCrownDepth(p_oTree);
    EXPECT_LT(fabs(fExpCrownDepth - fActual)/fExpCrownDepth, 0.01);
    fActual = p_oAllom->CalcAdultCrownRadius(p_oTree);
    EXPECT_LT(fabs(fExpCrownRad - fActual)/fExpCrownRad, 0.01);
    p_oPop->KillTree(p_oTree,remove_tree);

    iSpecies = 3; fDBH = 45.3493; fHeight = 37.74451;
    p_oTree = p_oPop->CreateTree(1,1,iSpecies,clTreePopulation::adult,fDBH);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()),fHeight, false);
    fExpCrownRad = 4.888505716; fExpCrownDepth = 0.107917135;
    fActual = p_oAllom->CalcAdultCrownDepth(p_oTree);
    EXPECT_LT(fabs(fExpCrownDepth - fActual)/fExpCrownDepth, 0.01);
    fActual = p_oAllom->CalcAdultCrownRadius(p_oTree);
    EXPECT_LT(fabs(fExpCrownRad - fActual)/fExpCrownRad, 0.01);
    p_oPop->KillTree(p_oTree,remove_tree);

    iSpecies = 0; fDBH = 25.13; fHeight = 13.052;
    p_oTree = p_oPop->CreateTree(1,1,iSpecies,clTreePopulation::adult,fDBH);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()),fHeight, false);
    fExpCrownRad = 3.069477879; fExpCrownDepth = 8.453676313;
    fActual = p_oAllom->CalcAdultCrownDepth(p_oTree);
    EXPECT_LT(fabs(fExpCrownDepth - fActual)/fExpCrownDepth, 0.01);
    fActual = p_oAllom->CalcAdultCrownRadius(p_oTree);
    EXPECT_LT(fabs(fExpCrownRad - fActual)/fExpCrownRad, 0.01);
    p_oPop->KillTree(p_oTree,remove_tree);

    iSpecies = 2; fDBH = 48.4916; fHeight = 34.09496;
    p_oTree = p_oPop->CreateTree(1,1,iSpecies,clTreePopulation::adult,fDBH);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()),fHeight, false);
    fExpCrownRad = 2.66218884; fExpCrownDepth =  13.26293944;
    fActual = p_oAllom->CalcAdultCrownDepth(p_oTree);
    EXPECT_LT(fabs(fExpCrownDepth - fActual)/fExpCrownDepth, 0.01);
    fActual = p_oAllom->CalcAdultCrownRadius(p_oTree);
    EXPECT_LT(fabs(fExpCrownRad - fActual)/fExpCrownRad, 0.01);
    p_oPop->KillTree(p_oTree,remove_tree);

    iSpecies = 0; fDBH = 26.3038; fHeight = 13.52152;
    p_oTree = p_oPop->CreateTree(1,1,iSpecies,clTreePopulation::adult,fDBH);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()),fHeight, false);
    fExpCrownRad = 3.1977713; fExpCrownDepth = 8.715875165;
    fActual = p_oAllom->CalcAdultCrownDepth(p_oTree);
    EXPECT_LT(fabs(fExpCrownDepth - fActual)/fExpCrownDepth, 0.01);
    fActual = p_oAllom->CalcAdultCrownRadius(p_oTree);
    EXPECT_LT(fabs(fExpCrownRad - fActual)/fExpCrownRad, 0.01);
    p_oPop->KillTree(p_oTree,remove_tree);

    iSpecies = 3; fDBH = 67.8397; fHeight = 53.48779;
    p_oTree = p_oPop->CreateTree(1,1,iSpecies,clTreePopulation::adult,fDBH);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()),fHeight, false);
    fExpCrownRad = 7.162120751; fExpCrownDepth = 0.459672566;
    fActual = p_oAllom->CalcAdultCrownDepth(p_oTree);
    EXPECT_LT(fabs(fExpCrownDepth - fActual)/fExpCrownDepth, 0.01);
    fActual = p_oAllom->CalcAdultCrownRadius(p_oTree);
    EXPECT_LT(fabs(fExpCrownRad - fActual)/fExpCrownRad, 0.01);
    p_oPop->KillTree(p_oTree,remove_tree);

    iSpecies = 1; fDBH = 43.5958; fHeight = 25.7979;
    p_oTree = p_oPop->CreateTree(1,1,iSpecies,clTreePopulation::adult,fDBH);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()),fHeight, false);
    fExpCrownRad = 4.923236797; fExpCrownDepth = 0.004826027;
    fActual = p_oAllom->CalcAdultCrownDepth(p_oTree);
    EXPECT_LT(fabs(fExpCrownDepth - fActual)/fExpCrownDepth, 0.01);
    fActual = p_oAllom->CalcAdultCrownRadius(p_oTree);
    EXPECT_LT(fabs(fExpCrownRad - fActual)/fExpCrownRad, 0.01);
    p_oPop->KillTree(p_oTree,remove_tree);

    iSpecies = 3; fDBH = 59.6401; fHeight = 47.74807;
    p_oTree = p_oPop->CreateTree(1,1,iSpecies,clTreePopulation::adult,fDBH);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()),fHeight, false);
    fExpCrownRad = 6.365326251; fExpCrownDepth = 0.250622973;
    fActual = p_oAllom->CalcAdultCrownDepth(p_oTree);
    EXPECT_LT(fabs(fExpCrownDepth - fActual)/fExpCrownDepth, 0.01);
    fActual = p_oAllom->CalcAdultCrownRadius(p_oTree);
    EXPECT_LT(fabs(fExpCrownRad - fActual)/fExpCrownRad, 0.01);
    p_oPop->KillTree(p_oTree,remove_tree);

    iSpecies = 0; fDBH = 33.0471; fHeight = 16.21884;
    p_oTree = p_oPop->CreateTree(1,1,iSpecies,clTreePopulation::adult,fDBH);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()),fHeight, false);
    fExpCrownRad = 3.925227284; fExpCrownDepth = 10.15157913;
    fActual = p_oAllom->CalcAdultCrownDepth(p_oTree);
    EXPECT_LT(fabs(fExpCrownDepth - fActual)/fExpCrownDepth, 0.01);
    fActual = p_oAllom->CalcAdultCrownRadius(p_oTree);
    EXPECT_LT(fabs(fExpCrownRad - fActual)/fExpCrownRad, 0.01);
    p_oPop->KillTree(p_oTree,remove_tree);

    iSpecies = 3; fDBH = 93.7086; fHeight = 71.59602;
    p_oTree = p_oPop->CreateTree(1,1,iSpecies,clTreePopulation::adult,fDBH);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()),fHeight, false);
    fExpCrownRad = 0; fExpCrownDepth = 2.6211426;
    fActual = p_oAllom->CalcAdultCrownDepth(p_oTree);
    EXPECT_LT(fabs(fExpCrownDepth - fActual)/fExpCrownDepth, 0.01);
    fActual = p_oAllom->CalcAdultCrownRadius(p_oTree);
    EXPECT_LT(fExpCrownRad, 0.01);
    p_oPop->KillTree(p_oTree,remove_tree);

    iSpecies = 3; fDBH = 48.8456; fHeight = 40.19192;
    p_oTree = p_oPop->CreateTree(1,1,iSpecies,clTreePopulation::adult,fDBH);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()),fHeight, false);
    fExpCrownRad = 5.252754948; fExpCrownDepth = 0.126510359;
    fActual = p_oAllom->CalcAdultCrownDepth(p_oTree);
    EXPECT_LT(fabs(fExpCrownDepth - fActual)/fExpCrownDepth, 0.01);
    fActual = p_oAllom->CalcAdultCrownRadius(p_oTree);
    EXPECT_LT(fabs(fExpCrownRad - fActual)/fExpCrownRad, 0.01);
    p_oPop->KillTree(p_oTree,remove_tree);

    iSpecies = 3; fDBH = 50.7243; fHeight = 41.50701;
    p_oTree = p_oPop->CreateTree(1,1,iSpecies,clTreePopulation::adult,fDBH);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()),fHeight, false);
    fExpCrownRad = 5.445621569; fExpCrownDepth = 0.142099683;
    fActual = p_oAllom->CalcAdultCrownDepth(p_oTree);
    EXPECT_LT(fabs(fExpCrownDepth - fActual)/fExpCrownDepth, 0.01);
    fActual = p_oAllom->CalcAdultCrownRadius(p_oTree);
    EXPECT_LT(fabs(fExpCrownRad - fActual)/fExpCrownRad, 0.01);
    p_oPop->KillTree(p_oTree,remove_tree);

    iSpecies = 3; fDBH = 50.9807; fHeight = 41.68649;
    p_oTree = p_oPop->CreateTree(1,1,iSpecies,clTreePopulation::adult,fDBH);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()),fHeight, false);
    fExpCrownRad = 5.461885049; fExpCrownDepth = 0.15171623;
    fActual = p_oAllom->CalcAdultCrownDepth(p_oTree);
    EXPECT_LT(fabs(fExpCrownDepth - fActual)/fExpCrownDepth, 0.01);
    fActual = p_oAllom->CalcAdultCrownRadius(p_oTree);
    EXPECT_LT(fabs(fExpCrownRad - fActual)/fExpCrownRad, 0.01);
    p_oPop->KillTree(p_oTree,remove_tree);

    iSpecies = 3; fDBH = 84.8799; fHeight = 65.41593;
    p_oTree = p_oPop->CreateTree(1,1,iSpecies,clTreePopulation::adult,fDBH);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()),fHeight, false);
    fExpCrownRad = 8.8094839; fExpCrownDepth = 1.336880694;
    fActual = p_oAllom->CalcAdultCrownDepth(p_oTree);
    EXPECT_LT(fabs(fExpCrownDepth - fActual)/fExpCrownDepth, 0.01);
    fActual = p_oAllom->CalcAdultCrownRadius(p_oTree);
    EXPECT_LT(fabs(fExpCrownRad - fActual)/fExpCrownRad, 0.01);
    p_oPop->KillTree(p_oTree,remove_tree);

    iSpecies = 3; fDBH = 67.1728; fHeight = 53.02096;
    p_oTree = p_oPop->CreateTree(1,1,iSpecies,clTreePopulation::adult,fDBH);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()),fHeight, false);
    fExpCrownRad = 7.141739241; fExpCrownDepth = 0.404222841;
    fActual = p_oAllom->CalcAdultCrownDepth(p_oTree);
    EXPECT_LT(fabs(fExpCrownDepth - fActual)/fExpCrownDepth, 0.01);
    fActual = p_oAllom->CalcAdultCrownRadius(p_oTree);
    EXPECT_LT(fabs(fExpCrownRad - fActual)/fExpCrownRad, 0.01);
    p_oPop->KillTree(p_oTree,remove_tree);

    iSpecies = 2; fDBH = 32.44; fHeight = 24.4658;
    p_oTree = p_oPop->CreateTree(1,1,iSpecies,clTreePopulation::adult,fDBH);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()),fHeight, false);
    fExpCrownRad = 1.7811207; fExpCrownDepth = 9.5171962;
    fActual = p_oAllom->CalcAdultCrownDepth(p_oTree);
    EXPECT_LT(fabs(fExpCrownDepth - fActual)/fExpCrownDepth, 0.01);
    fActual = p_oAllom->CalcAdultCrownRadius(p_oTree);
    EXPECT_LT(fabs(fExpCrownRad - fActual)/fExpCrownRad, 0.01);
    p_oPop->KillTree(p_oTree,remove_tree);

    iSpecies = 1; fDBH = 35.3926; fHeight = 21.6963;
    p_oTree = p_oPop->CreateTree(1,1,iSpecies,clTreePopulation::adult,fDBH);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()),fHeight, false);
    fExpCrownRad = 4.116558407; fExpCrownDepth = 0.269431351;
    fActual = p_oAllom->CalcAdultCrownDepth(p_oTree);
    EXPECT_LT(fabs(fExpCrownDepth - fActual)/fExpCrownDepth, 0.01);
    fActual = p_oAllom->CalcAdultCrownRadius(p_oTree);
    EXPECT_LT(fabs(fExpCrownRad - fActual)/fExpCrownRad, 0.01);
    p_oPop->KillTree(p_oTree,remove_tree);

    iSpecies = 1; fDBH = 38.5777; fHeight = 23.28885;
    p_oTree = p_oPop->CreateTree(1,1,iSpecies,clTreePopulation::adult,fDBH);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()),fHeight, false);
    fExpCrownRad = 4.42106662; fExpCrownDepth = 0.056221518;
    fActual = p_oAllom->CalcAdultCrownDepth(p_oTree);
    EXPECT_LT(fabs(fExpCrownDepth - fActual)/fExpCrownDepth, 0.01);
    fActual = p_oAllom->CalcAdultCrownRadius(p_oTree);
    EXPECT_LT(fabs(fExpCrownRad - fActual)/fExpCrownRad, 0.01);
    p_oPop->KillTree(p_oTree,remove_tree);

    iSpecies = 1; fDBH = 44.5903; fHeight = 26.29515;
    p_oTree = p_oPop->CreateTree(1,1,iSpecies,clTreePopulation::adult,fDBH);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()),fHeight, false);
    fExpCrownRad = 5.022830205; fExpCrownDepth = 0.003010477;
    fActual = p_oAllom->CalcAdultCrownDepth(p_oTree);
    EXPECT_LT(fabs(fExpCrownDepth - fActual)/fExpCrownDepth, 0.01);
    fActual = p_oAllom->CalcAdultCrownRadius(p_oTree);
    EXPECT_LT(fabs(fExpCrownRad - fActual)/fExpCrownRad, 0.01);
    p_oPop->KillTree(p_oTree,remove_tree);

    iSpecies = 2; fDBH = 42.7597; fHeight = 30.65582;
    p_oTree = p_oPop->CreateTree(1,1,iSpecies,clTreePopulation::adult,fDBH);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()),fHeight, false);
    fExpCrownRad = 2.34750753; fExpCrownDepth = 11.92511398;
    fActual = p_oAllom->CalcAdultCrownDepth(p_oTree);
    EXPECT_LT(fabs(fExpCrownDepth - fActual)/fExpCrownDepth, 0.01);
    fActual = p_oAllom->CalcAdultCrownRadius(p_oTree);
    EXPECT_LT(fabs(fExpCrownRad - fActual)/fExpCrownRad, 0.01);
    p_oPop->KillTree(p_oTree,remove_tree);

    iSpecies = 3; fDBH = 38.1041; fHeight = 32.67287;
    p_oTree = p_oPop->CreateTree(1,1,iSpecies,clTreePopulation::adult,fDBH);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()),fHeight, false);
    fExpCrownRad = 4.158229765; fExpCrownDepth = 0.07981587;
    fActual = p_oAllom->CalcAdultCrownDepth(p_oTree);
    EXPECT_LT(fabs(fExpCrownDepth - fActual)/fExpCrownDepth, 0.01);
    fActual = p_oAllom->CalcAdultCrownRadius(p_oTree);
    EXPECT_LT(fabs(fExpCrownRad - fActual)/fExpCrownRad, 0.01);
    p_oPop->KillTree(p_oTree,remove_tree);

    iSpecies = 3; fDBH = 62.0297; fHeight = 49.42079;
    p_oTree = p_oPop->CreateTree(1,1,iSpecies,clTreePopulation::adult,fDBH);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()),fHeight, false);
    fExpCrownRad = 6.603738348; fExpCrownDepth = 0.298362839;
    fActual = p_oAllom->CalcAdultCrownDepth(p_oTree);
    EXPECT_LT(fabs(fExpCrownDepth - fActual)/fExpCrownDepth, 0.01);
    fActual = p_oAllom->CalcAdultCrownRadius(p_oTree);
    EXPECT_LT(fabs(fExpCrownRad - fActual)/fExpCrownRad, 0.01);
    p_oPop->KillTree(p_oTree,remove_tree);

    iSpecies = 2; fDBH = 44.2927; fHeight = 31.57562;
    p_oTree = p_oPop->CreateTree(1,1,iSpecies,clTreePopulation::adult,fDBH);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()),fHeight, false);
    fExpCrownRad = 2.43166923; fExpCrownDepth = 12.28291618;
    fActual = p_oAllom->CalcAdultCrownDepth(p_oTree);
    EXPECT_LT(fabs(fExpCrownDepth - fActual)/fExpCrownDepth, 0.01);
    fActual = p_oAllom->CalcAdultCrownRadius(p_oTree);
    EXPECT_LT(fabs(fExpCrownRad - fActual)/fExpCrownRad, 0.01);
    p_oPop->KillTree(p_oTree,remove_tree);

    iSpecies = 0; fDBH = 19.9621; fHeight = 10.98484;
    p_oTree = p_oPop->CreateTree(1,1,iSpecies,clTreePopulation::adult,fDBH);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()),fHeight, false);
    fExpCrownRad = 2.498153542; fExpCrownDepth = 7.289799392;
    fActual = p_oAllom->CalcAdultCrownDepth(p_oTree);
    EXPECT_LT(fabs(fExpCrownDepth - fActual)/fExpCrownDepth, 0.01);
    fActual = p_oAllom->CalcAdultCrownRadius(p_oTree);
    EXPECT_LT(fabs(fExpCrownRad - fActual)/fExpCrownRad, 0.01);
    p_oPop->KillTree(p_oTree,remove_tree);

    iSpecies = 3; fDBH = 15.6386; fHeight = 16.94702;
    p_oTree = p_oPop->CreateTree(1,1,iSpecies,clTreePopulation::adult,fDBH);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()),fHeight, false);
    fExpCrownRad = 2.175172074; fExpCrownDepth = 0.030392796;
    fActual = p_oAllom->CalcAdultCrownDepth(p_oTree);
    EXPECT_LT(fabs(fExpCrownDepth - fActual)/fExpCrownDepth, 0.01);
    fActual = p_oAllom->CalcAdultCrownRadius(p_oTree);
    EXPECT_LT(fabs(fExpCrownRad - fActual)/fExpCrownRad, 0.01);
    p_oPop->KillTree(p_oTree,remove_tree);

    iSpecies = 2; fDBH = 23.0316; fHeight = 18.81896;
    p_oTree = p_oPop->CreateTree(1,1,iSpecies,clTreePopulation::adult,fDBH);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()),fHeight, false);
    fExpCrownRad = 1.26443484; fExpCrownDepth = 7.32057544;
    fActual = p_oAllom->CalcAdultCrownDepth(p_oTree);
    EXPECT_LT(fabs(fExpCrownDepth - fActual)/fExpCrownDepth, 0.01);
    fActual = p_oAllom->CalcAdultCrownRadius(p_oTree);
    EXPECT_LT(fabs(fExpCrownRad - fActual)/fExpCrownRad, 0.01);
    p_oPop->KillTree(p_oTree,remove_tree);

    iSpecies = 3; fDBH = 51.6542; fHeight = 42.15794;
    p_oTree = p_oPop->CreateTree(1,1,iSpecies,clTreePopulation::adult,fDBH);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()),fHeight, false);
    fExpCrownRad = 5.522244664; fExpCrownDepth = 0.164447922;
    fActual = p_oAllom->CalcAdultCrownDepth(p_oTree);
    EXPECT_LT(fabs(fExpCrownDepth - fActual)/fExpCrownDepth, 0.01);
    fActual = p_oAllom->CalcAdultCrownRadius(p_oTree);
    EXPECT_LT(fabs(fExpCrownRad - fActual)/fExpCrownRad, 0.01);
    p_oPop->KillTree(p_oTree,remove_tree);

    iSpecies = 0; fDBH = 38.8274; fHeight = 18.53096;
    p_oTree = p_oPop->CreateTree(1,1,iSpecies,clTreePopulation::adult,fDBH);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()),fHeight, false);
    fExpCrownRad = 4.536530449; fExpCrownDepth = 11.36480419;
    fActual = p_oAllom->CalcAdultCrownDepth(p_oTree);
    EXPECT_LT(fabs(fExpCrownDepth - fActual)/fExpCrownDepth, 0.01);
    fActual = p_oAllom->CalcAdultCrownRadius(p_oTree);
    EXPECT_LT(fabs(fExpCrownRad - fActual)/fExpCrownRad, 0.01);
    p_oPop->KillTree(p_oTree,remove_tree);

    iSpecies = 0; fDBH = 9.9621; fHeight = 6.98484;
    p_oTree = p_oPop->CreateTree(1,1,iSpecies,clTreePopulation::adult,fDBH);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()),fHeight, false);
    fExpCrownRad = 0.54691929; fExpCrownDepth = 2.71710276;
    fActual = p_oAllom->CalcSaplingCrownDepth(p_oTree);
    EXPECT_LT(fabs(fExpCrownDepth - fActual)/fExpCrownDepth, 0.01);
    fActual = p_oAllom->CalcSaplingCrownRadius(p_oTree);
    EXPECT_LT(fabs(fExpCrownRad - fActual)/fExpCrownRad, 0.01);
    p_oPop->KillTree(p_oTree,remove_tree);

    iSpecies = 3; fDBH = 5.6386; fHeight = 9.94702;
    p_oTree = p_oPop->CreateTree(1,1,iSpecies,clTreePopulation::adult,fDBH);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()),fHeight, false);
    fExpCrownRad = 0.30955914; fExpCrownDepth = 3.86939078;
    fActual = p_oAllom->CalcSaplingCrownDepth(p_oTree);
    EXPECT_LT(fabs(fExpCrownDepth - fActual)/fExpCrownDepth, 0.01);
    fActual = p_oAllom->CalcSaplingCrownRadius(p_oTree);
    EXPECT_LT(fabs(fExpCrownRad - fActual)/fExpCrownRad, 0.01);
    p_oPop->KillTree(p_oTree,remove_tree);

    iSpecies = 2; fDBH = 3.0316; fHeight = 6.81896;
    p_oTree = p_oPop->CreateTree(1,1,iSpecies,clTreePopulation::adult,fDBH);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()),fHeight, false);
    fExpCrownRad = 0.16643484; fExpCrownDepth = 2.65257544;
    fActual = p_oAllom->CalcSaplingCrownDepth(p_oTree);
    EXPECT_LT(fabs(fExpCrownDepth - fActual)/fExpCrownDepth, 0.01);
    fActual = p_oAllom->CalcSaplingCrownRadius(p_oTree);
    EXPECT_LT(fabs(fExpCrownRad - fActual)/fExpCrownRad, 0.01);
    p_oPop->KillTree(p_oTree,remove_tree);

    iSpecies = 3; fDBH = 1.6542; fHeight = 7.15794;
    p_oTree = p_oPop->CreateTree(1,1,iSpecies,clTreePopulation::adult,fDBH);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()),fHeight, false);
    fExpCrownRad = 0.09081558; fExpCrownDepth = 2.78443866;
    fActual = p_oAllom->CalcSaplingCrownDepth(p_oTree);
    EXPECT_LT(fabs(fExpCrownDepth - fActual)/fExpCrownDepth, 0.01);
    fActual = p_oAllom->CalcSaplingCrownRadius(p_oTree);
    EXPECT_LT(fabs(fExpCrownRad - fActual)/fExpCrownRad, 0.01);
    p_oPop->KillTree(p_oTree,remove_tree);

    iSpecies = 0; fDBH = 8.8274; fHeight = 6.53096;
    p_oTree = p_oPop->CreateTree(1,1,iSpecies,clTreePopulation::adult,fDBH);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()),fHeight, false);
    fExpCrownRad = 0.48462426; fExpCrownDepth = 2.54054344;
    fActual = p_oAllom->CalcSaplingCrownDepth(p_oTree);
    EXPECT_LT(fabs(fExpCrownDepth - fActual)/fExpCrownDepth, 0.01);
    fActual = p_oAllom->CalcSaplingCrownRadius(p_oTree);
    EXPECT_LT(fabs(fExpCrownRad - fActual)/fExpCrownRad, 0.01);
    p_oPop->KillTree(p_oTree,remove_tree);

    //To make sure that plot basal areas are correctly calculated - run a
    //timestep, add some trees, and make sure the values change
    p_oSimManager->RunSim(1);
    fX = 28; fY = 28; iSpecies = 3; fDBH = 15.6386;
    for (i = 0; i < 100; i++)
      p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDBH );

    iSpecies = 0; fDBH = 20.9245; fHeight = 11.3698;
    fExpCrownRad = 2.3922;
    p_oTree = p_oPop->CreateTree(1,1,iSpecies,clTreePopulation::adult,fDBH);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()),fHeight, false);
    fActual = p_oAllom->CalcAdultCrownRadius(p_oTree);
    EXPECT_LT(fabs(fExpCrownRad - fActual)/fExpCrownRad, 0.01);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun3()
// Verifies that NCI crown allometry functions calculate correctly. This run
// uses WriteAllometryXMLFile8 for setup. This file contains 4 species, three of which
// use those functions.
/////////////////////////////////////////////////////////////////////////////
TEST(Allometry, NCICrownAllometry)
{

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clAllometry *p_oAllom;
    clTree *p_oTargetTree1,
    *p_oTargetTree2,
    *p_oTargetTree3,
    *p_oTargetTree4,
    *p_oTargetTree5,
    *p_oTargetTree;
    float fDiam, fExpectedCrownRadius, fActualCrownRadius, fExpectedCrownDepth,
    fActualCrownDepth;
    int iSpecies;

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteAllometryXMLFile8() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
    p_oAllom = p_oPop->GetAllometryObject();

    EXPECT_LT(fabs(12.77 - p_oAllom->GetMaxCrownRadius()), 0.01);

    //Create our trees
    fDiam = 15;
    iSpecies = 1;
    p_oTargetTree1 = p_oPop->CreateTree(53, 52, iSpecies, clTreePopulation::adult, fDiam);


    fDiam = 25;
    iSpecies = 3;
    p_oTargetTree2 = p_oPop->CreateTree(59, 50, iSpecies, clTreePopulation::adult, fDiam);

    fDiam = 30;
    iSpecies = 0;
    p_oTargetTree3 = p_oPop->CreateTree(50, 59, iSpecies, clTreePopulation::adult, fDiam);

    fDiam = 45;
    iSpecies = 1;
    p_oTargetTree4 = p_oPop->CreateTree(55, 55, iSpecies, clTreePopulation::adult, fDiam);

    fDiam = 10.5;
    iSpecies = 0;
    p_oTargetTree5 = p_oPop->CreateTree(50, 50, iSpecies, clTreePopulation::adult, fDiam);

    //Now create all the neighbors that are too small or dead to compete
    p_oPop->CreateTree(52, 52, 0, clTreePopulation::sapling, 9);
    p_oPop->CreateTree(53, 53, 1, clTreePopulation::adult, 11);
    p_oPop->CreateTree(54, 54, 3, clTreePopulation::adult, 13);
    p_oPop->CreateTree(56, 56, 2, clTreePopulation::adult, 15);
    p_oPop->CreateTree(56, 56, 0, clTreePopulation::snag, 30);
    p_oTargetTree = p_oPop->CreateTree(58, 58, 1, clTreePopulation::adult, 20);
    p_oTargetTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), storm);

    //Verify that the values get stashed in the data member - should be -1 now
    p_oTargetTree = p_oTargetTree1;
    p_oTargetTree->GetValue(p_oPop->GetCrownRadiusCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fActualCrownRadius);
    p_oTargetTree->GetValue(p_oPop->GetCrownDepthCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fActualCrownDepth);
    EXPECT_LT(fActualCrownRadius, 0);
    EXPECT_LT(fActualCrownDepth, 0);

    //Check the crown dimensions of the target trees
    fExpectedCrownRadius = 3.857705242;
    fExpectedCrownDepth = 2.112031622;
    p_oTargetTree = p_oTargetTree1;
    fActualCrownRadius = p_oAllom->CalcAdultCrownRadius(p_oTargetTree);
    fActualCrownDepth = p_oAllom->CalcAdultCrownDepth(p_oTargetTree);
    EXPECT_LT(fabs(fActualCrownRadius - fExpectedCrownRadius), 0.01);
    EXPECT_LT(fabs(fActualCrownDepth - fExpectedCrownDepth), 0.01);
    p_oTargetTree->GetValue(p_oPop->GetCrownRadiusCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fActualCrownRadius);
    p_oTargetTree->GetValue(p_oPop->GetCrownDepthCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fActualCrownDepth);
    EXPECT_LT(fabs(fActualCrownRadius - fExpectedCrownRadius), 0.01);
    EXPECT_LT(fabs(fActualCrownDepth - fExpectedCrownDepth), 0.01);

    fExpectedCrownRadius = 4.267931616;
    fExpectedCrownDepth = 7.170488634;
    p_oTargetTree = p_oTargetTree2;
    fActualCrownRadius = p_oAllom->CalcAdultCrownRadius(p_oTargetTree);
    fActualCrownDepth = p_oAllom->CalcAdultCrownDepth(p_oTargetTree);
    EXPECT_LT(fabs(fActualCrownRadius - fExpectedCrownRadius), 0.01);
    EXPECT_LT(fabs(fActualCrownDepth - fExpectedCrownDepth), 0.01);

    fExpectedCrownRadius = 2.891967468;
    fExpectedCrownDepth = 23.93092154;
    p_oTargetTree = p_oTargetTree3;
    fActualCrownRadius = p_oAllom->CalcAdultCrownRadius(p_oTargetTree);
    fActualCrownDepth = p_oAllom->CalcAdultCrownDepth(p_oTargetTree);
    EXPECT_LT(fabs(fActualCrownRadius - fExpectedCrownRadius), 0.01);
    EXPECT_LT(fabs(fActualCrownDepth - fExpectedCrownDepth), 0.01);

    fExpectedCrownRadius = 5.172862891;
    fExpectedCrownDepth = 5.644058751;
    p_oTargetTree = p_oTargetTree4;
    fActualCrownRadius = p_oAllom->CalcAdultCrownRadius(p_oTargetTree);
    fActualCrownDepth = p_oAllom->CalcAdultCrownDepth(p_oTargetTree);
    EXPECT_LT(fabs(fActualCrownRadius - fExpectedCrownRadius), 0.01);
    EXPECT_LT(fabs(fActualCrownDepth - fExpectedCrownDepth), 0.01);

    fExpectedCrownRadius = 1.457681339;
    fExpectedCrownDepth = 11.62391669;
    p_oTargetTree = p_oTargetTree5;
    fActualCrownRadius = p_oAllom->CalcAdultCrownRadius(p_oTargetTree);
    fActualCrownDepth = p_oAllom->CalcAdultCrownDepth(p_oTargetTree);
    EXPECT_LT(fabs(fActualCrownRadius - fExpectedCrownRadius), 0.01);
    EXPECT_LT(fabs(fActualCrownDepth - fExpectedCrownDepth), 0.01);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// WriteAllometryXMLFile7()
/////////////////////////////////////////////////////////////////////////////
const char* WriteAllometryXMLFile7()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06090101\">" << "<plot>"
      << "<timesteps>3</timesteps>"
      << "<yearsPerTimestep>1</yearsPerTimestep>"
      << "<randomSeed>1</randomSeed>"
      << "<plot_lenX>50.0</plot_lenX>"
      << "<plot_lenY>70.0</plot_lenY>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88171785</plot_temp_C>"
      << "<plot_latitude>55.37</plot_latitude>"
      << "</plot>"
      << "<trees>"
      << "<tr_speciesList>"
      << "<tr_species speciesName=\"Species_1\"/>"
      << "<tr_species speciesName=\"Species_2\"/>"
      << "<tr_species speciesName=\"Species_3\"/>"
      << "<tr_species speciesName=\"Species_4\"/>"
      << "</tr_speciesList>"
      << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
      << "<tr_minAdultDBH>"
      << "<tr_madVal species=\"Species_1\">10</tr_madVal>"
      << "<tr_madVal species=\"Species_2\">10</tr_madVal>"
      << "<tr_madVal species=\"Species_3\">10</tr_madVal>"
      << "<tr_madVal species=\"Species_4\">10</tr_madVal>"
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
      << "<tr_chVal species=\"Species_1\">100</tr_chVal>"
      << "<tr_chVal species=\"Species_2\">100</tr_chVal>"
      << "<tr_chVal species=\"Species_3\">100</tr_chVal>"
      << "<tr_chVal species=\"Species_4\">100</tr_chVal>"
      << "</tr_canopyHeight>"
      << "<tr_stdAsympCrownRad>"
      << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_2\">0.0549</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_3\">0.0549</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_4\">0.0549</tr_sacrVal>"
      << "</tr_stdAsympCrownRad>"
      << "<tr_stdCrownRadExp>"
      << "<tr_screVal species=\"Species_1\">1</tr_screVal>"
      << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_3\">1</tr_screVal>"
      << "<tr_screVal species=\"Species_4\">1</tr_screVal>"
      << "</tr_stdCrownRadExp>"
      << "<tr_stdMaxCrownRad>"
      << "<tr_smcrVal species=\"Species_1\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Species_2\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Species_3\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Species_4\">10</tr_smcrVal>"
      << "</tr_stdMaxCrownRad>"
      << "<tr_conversionDiam10ToDBH>"
      << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_2\">0.5944</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_3\">0.7059</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_4\">0.8008</tr_cdtdVal>"
      << "</tr_conversionDiam10ToDBH>"
      << "<tr_interceptDiam10ToDBH>"
      << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_2\">1</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_3\">-0.2</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_4\">0.3</tr_idtdVal>"
      << "</tr_interceptDiam10ToDBH>"
      << "<tr_stdAsympCrownHt>"
      << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
      << "<tr_sachVal species=\"Species_2\">0.389</tr_sachVal>"
      << "<tr_sachVal species=\"Species_3\">0.389</tr_sachVal>"
      << "<tr_sachVal species=\"Species_4\">0.389</tr_sachVal>"
      << "</tr_stdAsympCrownHt>"
      << "<tr_stdCrownHtExp>"
      << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_2\">1</tr_scheVal>"
      << "<tr_scheVal species=\"Species_3\">1</tr_scheVal>"
      << "<tr_scheVal species=\"Species_4\">1.0</tr_scheVal>"
      << "</tr_stdCrownHtExp>"
      << "<tr_slopeOfHeight-Diam10>"
      << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_2\">0.03418</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_3\">0.2871</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_4\">0.03418</tr_sohdVal>"
      << "</tr_slopeOfHeight-Diam10>"
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
      << "<tr_wacrdVal species=\"Species_1\">2</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Species_2\">2</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Species_3\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Species_4\">2</tr_wacrdVal>"
      << "</tr_whatAdultCrownRadDiam>"
      << "<tr_whatAdultCrownHeightHeight>"
      << "<tr_wachhVal species=\"Species_1\">2</tr_wachhVal>"
      << "<tr_wachhVal species=\"Species_2\">2</tr_wachhVal>"
      << "<tr_wachhVal species=\"Species_3\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Species_4\">2</tr_wachhVal>"
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
      << "<tr_adultLinearSlope>"
      << "<tr_alsVal species=\"Species_1\">0.4</tr_alsVal>"
      << "<tr_alsVal species=\"Species_2\">0.5</tr_alsVal>"
      << "<tr_alsVal species=\"Species_3\">0.6</tr_alsVal>"
      << "<tr_alsVal species=\"Species_4\">0.7</tr_alsVal>"
      << "</tr_adultLinearSlope>"
      << "<tr_adultLinearIntercept>"
      << "<tr_aliVal species=\"Species_1\">3</tr_aliVal>"
      << "<tr_aliVal species=\"Species_2\">4</tr_aliVal>"
      << "<tr_aliVal species=\"Species_3\">5</tr_aliVal>"
      << "<tr_aliVal species=\"Species_4\">6</tr_aliVal>"
      << "</tr_adultLinearIntercept>"
      << "<tr_saplingLinearSlope>"
      << "<tr_salsVal species=\"Species_1\">0.4</tr_salsVal>"
      << "<tr_salsVal species=\"Species_2\">0.5</tr_salsVal>"
      << "<tr_salsVal species=\"Species_3\">0.6</tr_salsVal>"
      << "<tr_salsVal species=\"Species_4\">0.7</tr_salsVal>"
      << "</tr_saplingLinearSlope>"
      << "<tr_saplingLinearIntercept>"
      << "<tr_saliVal species=\"Species_1\">3</tr_saliVal>"
      << "<tr_saliVal species=\"Species_2\">4</tr_saliVal>"
      << "<tr_saliVal species=\"Species_3\">5</tr_saliVal>"
      << "<tr_saliVal species=\"Species_4\">6</tr_saliVal>"
      << "</tr_saplingLinearIntercept>"
      << "<tr_seedlingLinearSlope>"
      << "<tr_selsVal species=\"Species_1\">0.9629</tr_selsVal>"
      << "<tr_selsVal species=\"Species_2\">0.9629</tr_selsVal>"
      << "<tr_selsVal species=\"Species_3\">1.228</tr_selsVal>"
      << "<tr_selsVal species=\"Species_4\">0.9629</tr_selsVal>"
      << "</tr_seedlingLinearSlope>"
      << "<tr_seedlingLinearIntercept>"
      << "<tr_seliVal species=\"Species_1\">0</tr_seliVal>"
      << "<tr_seliVal species=\"Species_2\">0</tr_seliVal>"
      << "<tr_seliVal species=\"Species_3\">-0.9</tr_seliVal>"
      << "<tr_seliVal species=\"Species_4\">0</tr_seliVal>"
      << "</tr_seedlingLinearIntercept>"
      << "<tr_nonSpatDensDepInstCHA>"
      << "<tr_nsddichaVal species=\"Species_1\">4.35</tr_nsddichaVal>"
      << "<tr_nsddichaVal species=\"Species_2\">18.977</tr_nsddichaVal>"
      << "<tr_nsddichaVal species=\"Species_4\">2.193</tr_nsddichaVal>"
      << "</tr_nonSpatDensDepInstCHA>"
      << "<tr_nonSpatDensDepInstCHB>"
      << "<tr_nsddichbVal species=\"Species_1\">0.044</tr_nsddichbVal>"
      << "<tr_nsddichbVal species=\"Species_2\">-2.173</tr_nsddichbVal>"
      << "<tr_nsddichbVal species=\"Species_4\">0.041</tr_nsddichbVal>"
      << "</tr_nonSpatDensDepInstCHB>"
      << "<tr_nonSpatDensDepInstCHC>"
      << "<tr_nsddichcVal species=\"Species_1\">0.131</tr_nsddichcVal>"
      << "<tr_nsddichcVal species=\"Species_2\">3.797</tr_nsddichcVal>"
      << "<tr_nsddichcVal species=\"Species_4\">-0.153</tr_nsddichcVal>"
      << "</tr_nonSpatDensDepInstCHC>"
      << "<tr_nonSpatDensDepInstCHD>"
      << "<tr_nsddichdVal species=\"Species_1\">0.047</tr_nsddichdVal>"
      << "<tr_nsddichdVal species=\"Species_2\">0.035</tr_nsddichdVal>"
      << "<tr_nsddichdVal species=\"Species_4\">0.00096</tr_nsddichdVal>"
      << "</tr_nonSpatDensDepInstCHD>"
      << "<tr_nonSpatDensDepInstCHE>"
      << "<tr_nsddicheVal species=\"Species_1\">-0.011</tr_nsddicheVal>"
      << "<tr_nsddicheVal species=\"Species_2\">-0.073</tr_nsddicheVal>"
      << "<tr_nsddicheVal species=\"Species_4\">0.0018</tr_nsddicheVal>"
      << "</tr_nonSpatDensDepInstCHE>"
      << "<tr_nonSpatDensDepInstCHF>"
      << "<tr_nsddichfVal species=\"Species_1\">-12.31</tr_nsddichfVal>"
      << "<tr_nsddichfVal species=\"Species_2\">0.383</tr_nsddichfVal>"
      << "<tr_nsddichfVal species=\"Species_4\">-10.55</tr_nsddichfVal>"
      << "</tr_nonSpatDensDepInstCHF>"
      << "<tr_nonSpatDensDepInstCHG>"
      << "<tr_nsddichgVal species=\"Species_1\">-0.0014</tr_nsddichgVal>"
      << "<tr_nsddichgVal species=\"Species_2\">-0.0012</tr_nsddichgVal>"
      << "<tr_nsddichgVal species=\"Species_4\">-0.00019</tr_nsddichgVal>"
      << "</tr_nonSpatDensDepInstCHG>"
      << "<tr_nonSpatDensDepInstCHH>"
      << "<tr_nsddichhVal species=\"Species_1\">0.035</tr_nsddichhVal>"
      << "<tr_nsddichhVal species=\"Species_2\">0.074</tr_nsddichhVal>"
      << "<tr_nsddichhVal species=\"Species_4\">0.0041</tr_nsddichhVal>"
      << "</tr_nonSpatDensDepInstCHH>"
      << "<tr_nonSpatDensDepInstCHI>"
      << "<tr_nsddichiVal species=\"Species_1\">-0.034</tr_nsddichiVal>"
      << "<tr_nsddichiVal species=\"Species_2\">-0.108</tr_nsddichiVal>"
      << "<tr_nsddichiVal species=\"Species_4\">-0.0037</tr_nsddichiVal>"
      << "</tr_nonSpatDensDepInstCHI>"
      << "<tr_nonSpatDensDepInstCHJ>"
      << "<tr_nsddichjVal species=\"Species_1\">1.523</tr_nsddichjVal>"
      << "<tr_nsddichjVal species=\"Species_2\">-22.108</tr_nsddichjVal>"
      << "<tr_nsddichjVal species=\"Species_4\">0.772</tr_nsddichjVal>"
      << "</tr_nonSpatDensDepInstCHJ>"
      << "<tr_nonSpatExpDensDepCRD1>"
      << "<tr_nseddcrd1Val species=\"Species_1\">0.357</tr_nseddcrd1Val>"
      << "<tr_nseddcrd1Val species=\"Species_2\">0.638</tr_nseddcrd1Val>"
      << "<tr_nseddcrd1Val species=\"Species_4\">0.45</tr_nseddcrd1Val>"
      << "</tr_nonSpatExpDensDepCRD1>"
      << "<tr_nonSpatExpDensDepCRA>"
      << "<tr_nseddcraVal species=\"Species_1\">0.895</tr_nseddcraVal>"
      << "<tr_nseddcraVal species=\"Species_2\">0.968</tr_nseddcraVal>"
      << "<tr_nseddcraVal species=\"Species_4\">0.9</tr_nseddcraVal>"
      << "</tr_nonSpatExpDensDepCRA>"
      << "<tr_nonSpatExpDensDepCRB>"
      << "<tr_nseddcrbVal species=\"Species_1\">-0.45</tr_nseddcrbVal>"
      << "<tr_nseddcrbVal species=\"Species_2\">-0.938</tr_nseddcrbVal>"
      << "<tr_nseddcrbVal species=\"Species_4\">-0.66</tr_nseddcrbVal>"
      << "</tr_nonSpatExpDensDepCRB>"
      << "<tr_nonSpatExpDensDepCRC>"
      << "<tr_nseddcrcVal species=\"Species_1\">0.207</tr_nseddcrcVal>"
      << "<tr_nseddcrcVal species=\"Species_2\">0.492</tr_nseddcrcVal>"
      << "<tr_nseddcrcVal species=\"Species_4\">0.38</tr_nseddcrcVal>"
      << "</tr_nonSpatExpDensDepCRC>"
      << "<tr_nonSpatExpDensDepCRD>"
      << "<tr_nseddcrdVal species=\"Species_1\">-0.057</tr_nseddcrdVal>"
      << "<tr_nseddcrdVal species=\"Species_2\">-0.172</tr_nseddcrdVal>"
      << "<tr_nseddcrdVal species=\"Species_4\">-0.104</tr_nseddcrdVal>"
      << "</tr_nonSpatExpDensDepCRD>"
      << "<tr_nonSpatExpDensDepCRE>"
      << "<tr_nseddcreVal species=\"Species_1\">-0.025</tr_nseddcreVal>"
      << "<tr_nseddcreVal species=\"Species_2\">0.153</tr_nseddcreVal>"
      << "<tr_nseddcreVal species=\"Species_4\">0.45</tr_nseddcreVal>"
      << "</tr_nonSpatExpDensDepCRE>"
      << "<tr_nonSpatExpDensDepCRF>"
      << "<tr_nseddcrfVal species=\"Species_1\">0.004</tr_nseddcrfVal>"
      << "<tr_nseddcrfVal species=\"Species_2\">0.061</tr_nseddcrfVal>"
      << "<tr_nseddcrfVal species=\"Species_4\">0.04</tr_nseddcrfVal>"
      << "</tr_nonSpatExpDensDepCRF>"
      << "<tr_nonSpatDensDepInstCRA>"
      << "<tr_nsddicraVal species=\"Species_1\">2.193</tr_nsddicraVal>"
      << "<tr_nsddicraVal species=\"Species_2\">1.359</tr_nsddicraVal>"
      << "<tr_nsddicraVal species=\"Species_4\">1.45</tr_nsddicraVal>"
      << "</tr_nonSpatDensDepInstCRA>"
      << "<tr_nonSpatDensDepInstCRB>"
      << "<tr_nsddicrbVal species=\"Species_1\">0.041</tr_nsddicrbVal>"
      << "<tr_nsddicrbVal species=\"Species_2\">-0.007</tr_nsddicrbVal>"
      << "<tr_nsddicrbVal species=\"Species_4\">0.02</tr_nsddicrbVal>"
      << "</tr_nonSpatDensDepInstCRB>"
      << "<tr_nonSpatDensDepInstCRC>"
      << "<tr_nsddicrcVal species=\"Species_1\">-0.153</tr_nsddicrcVal>"
      << "<tr_nsddicrcVal species=\"Species_2\">0.185</tr_nsddicrcVal>"
      << "<tr_nsddicrcVal species=\"Species_4\">-0.078</tr_nsddicrcVal>"
      << "</tr_nonSpatDensDepInstCRC>"
      << "<tr_nonSpatDensDepInstCRD>"
      << "<tr_nsddicrdVal species=\"Species_1\">0.00096</tr_nsddicrdVal>"
      << "<tr_nsddicrdVal species=\"Species_2\">0.001</tr_nsddicrdVal>"
      << "<tr_nsddicrdVal species=\"Species_4\">0.001</tr_nsddicrdVal>"
      << "</tr_nonSpatDensDepInstCRD>"
      << "<tr_nonSpatDensDepInstCRE>"
      << "<tr_nsddicreVal species=\"Species_1\">0.0018</tr_nsddicreVal>"
      << "<tr_nsddicreVal species=\"Species_2\">-0.005</tr_nsddicreVal>"
      << "<tr_nsddicreVal species=\"Species_4\">0.0007</tr_nsddicreVal>"
      << "</tr_nonSpatDensDepInstCRE>"
      << "<tr_nonSpatDensDepInstCRF>"
      << "<tr_nsddicrfVal species=\"Species_1\">-10.55</tr_nsddicrfVal>"
      << "<tr_nsddicrfVal species=\"Species_2\">2.663</tr_nsddicrfVal>"
      << "<tr_nsddicrfVal species=\"Species_4\">-5.56</tr_nsddicrfVal>"
      << "</tr_nonSpatDensDepInstCRF>"
      << "<tr_nonSpatDensDepInstCRG>"
      << "<tr_nsddicrgVal species=\"Species_1\">-0.00019</tr_nsddicrgVal>"
      << "<tr_nsddicrgVal species=\"Species_2\">-0.0002</tr_nsddicrgVal>"
      << "<tr_nsddicrgVal species=\"Species_4\">-0.00199</tr_nsddicrgVal>"
      << "</tr_nonSpatDensDepInstCRG>"
      << "<tr_nonSpatDensDepInstCRH>"
      << "<tr_nsddicrhVal species=\"Species_1\">0.0041</tr_nsddicrhVal>"
      << "<tr_nsddicrhVal species=\"Species_2\">0.011</tr_nsddicrhVal>"
      << "<tr_nsddicrhVal species=\"Species_4\">0.008</tr_nsddicrhVal>"
      << "</tr_nonSpatDensDepInstCRH>"
      << "<tr_nonSpatDensDepInstCRI>"
      << "<tr_nsddicriVal species=\"Species_1\">-0.0037</tr_nsddicriVal>"
      << "<tr_nsddicriVal species=\"Species_2\">0.002</tr_nsddicriVal>"
      << "<tr_nsddicriVal species=\"Species_4\">0.0018</tr_nsddicriVal>"
      << "</tr_nonSpatDensDepInstCRI>"
      << "<tr_nonSpatDensDepInstCRJ>"
      << "<tr_nsddicrjVal species=\"Species_1\">0.772</tr_nsddicrjVal>"
      << "<tr_nsddicrjVal species=\"Species_2\">-1.885</tr_nsddicrjVal>"
      << "<tr_nsddicrjVal species=\"Species_4\">0.355</tr_nsddicrjVal>"
      << "</tr_nonSpatDensDepInstCRJ>"
      << "<tr_nonSpatLogDensDepCHA>"
      << "<tr_nslddchaVal species=\"Species_1\">-1.327</tr_nslddchaVal>"
      << "<tr_nslddchaVal species=\"Species_2\">0.638</tr_nslddchaVal>"
      << "<tr_nslddchaVal species=\"Species_4\">-0.8</tr_nslddchaVal>"
      << "</tr_nonSpatLogDensDepCHA>"
      << "<tr_nonSpatLogDensDepCHB>"
      << "<tr_nslddchbVal species=\"Species_1\">-0.037</tr_nslddchbVal>"
      << "<tr_nslddchbVal species=\"Species_2\">0.968</tr_nslddchbVal>"
      << "<tr_nslddchbVal species=\"Species_4\">-0.02</tr_nslddchbVal>"
      << "</tr_nonSpatLogDensDepCHB>"
      << "<tr_nonSpatLogDensDepCHC>"
      << "<tr_nslddchcVal species=\"Species_1\">0.153</tr_nslddchcVal>"
      << "<tr_nslddchcVal species=\"Species_2\">-0.938</tr_nslddchcVal>"
      << "<tr_nslddchcVal species=\"Species_4\">0.053</tr_nslddchcVal>"
      << "</tr_nonSpatLogDensDepCHC>"
      << "<tr_nonSpatLogDensDepCHD>"
      << "<tr_nslddchdVal species=\"Species_1\">-0.172</tr_nslddchdVal>"
      << "<tr_nslddchdVal species=\"Species_2\">0.492</tr_nslddchdVal>"
      << "<tr_nslddchdVal species=\"Species_4\">-0.298</tr_nslddchdVal>"
      << "</tr_nonSpatLogDensDepCHD>"
      << "<tr_nonSpatLogDensDepCHE>"
      << "<tr_nslddcheVal species=\"Species_1\">0.0006</tr_nslddcheVal>"
      << "<tr_nslddcheVal species=\"Species_2\">-0.172</tr_nslddcheVal>"
      << "<tr_nslddcheVal species=\"Species_4\">-0.084</tr_nslddcheVal>"
      << "</tr_nonSpatLogDensDepCHE>"
      << "<tr_nonSpatLogDensDepCHF>"
      << "<tr_nslddchfVal species=\"Species_1\">-0.018</tr_nslddchfVal>"
      << "<tr_nslddchfVal species=\"Species_2\">0.153</tr_nslddchfVal>"
      << "<tr_nslddchfVal species=\"Species_4\">0.75</tr_nslddchfVal>"
      << "</tr_nonSpatLogDensDepCHF>"
      << "<tr_nonSpatLogDensDepCHG>"
      << "<tr_nslddchgVal species=\"Species_1\">0.016</tr_nslddchgVal>"
      << "<tr_nslddchgVal species=\"Species_2\">0.061</tr_nslddchgVal>"
      << "<tr_nslddchgVal species=\"Species_4\">0.099</tr_nslddchgVal>"
      << "</tr_nonSpatLogDensDepCHG>"
      << "</allometry>"
      << "<behaviorList>"
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

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteAllometryXMLFile8()
/////////////////////////////////////////////////////////////////////////////
const char* WriteAllometryXMLFile8()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06090101\">" << "<plot>"
      << "<timesteps>3</timesteps>"
      << "<yearsPerTimestep>1</yearsPerTimestep>"
      << "<randomSeed>1</randomSeed>"
      << "<plot_lenX>100.0</plot_lenX>"
      << "<plot_lenY>100.0</plot_lenY>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88171785</plot_temp_C>"
      << "<plot_latitude>55.37</plot_latitude>"
      << "</plot>"
      << "<trees>"
      << "<tr_speciesList>"
      << "<tr_species speciesName=\"Species_1\"/>"
      << "<tr_species speciesName=\"Species_2\"/>"
      << "<tr_species speciesName=\"Species_3\"/>"
      << "<tr_species speciesName=\"Species_4\"/>"
      << "</tr_speciesList>"
      << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
      << "<tr_minAdultDBH>"
      << "<tr_madVal species=\"Species_1\">10</tr_madVal>"
      << "<tr_madVal species=\"Species_2\">10</tr_madVal>"
      << "<tr_madVal species=\"Species_3\">10</tr_madVal>"
      << "<tr_madVal species=\"Species_4\">10</tr_madVal>"
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
      << "<tr_chVal species=\"Species_2\">39.48</tr_chVal>"
      << "<tr_chVal species=\"Species_3\">39.48</tr_chVal>"
      << "<tr_chVal species=\"Species_4\">39.48</tr_chVal>"
      << "</tr_canopyHeight>"
      << "<tr_stdAsympCrownRad>"
      << "<tr_sacrVal species=\"Species_3\">0.0549</tr_sacrVal>"
      << "</tr_stdAsympCrownRad>"
      << "<tr_stdCrownRadExp>"
      << "<tr_screVal species=\"Species_3\">1</tr_screVal>"
      << "</tr_stdCrownRadExp>"
      << "<tr_stdMaxCrownRad>"
      << "<tr_smcrVal species=\"Species_3\">10</tr_smcrVal>"
      << "</tr_stdMaxCrownRad>"
      << "<tr_stdAsympCrownHt>"
      << "<tr_sachVal species=\"Species_3\">0.389</tr_sachVal>"
      << "</tr_stdAsympCrownHt>"
      << "<tr_stdCrownHtExp>"
      << "<tr_scheVal species=\"Species_3\">1</tr_scheVal>"
      << "</tr_stdCrownHtExp>"
      << "<tr_slopeOfAsymHeight>"
      << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
      << "<tr_soahVal species=\"Species_2\">0.0299</tr_soahVal>"
      << "<tr_soahVal species=\"Species_3\">0.0299</tr_soahVal>"
      << "<tr_soahVal species=\"Species_4\">0.0299</tr_soahVal>"
      << "</tr_slopeOfAsymHeight>"
      << "<tr_conversionDiam10ToDBH>"
      << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_2\">0.8008</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_3\">0.8008</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_4\">0.8008</tr_cdtdVal>"
      << "</tr_conversionDiam10ToDBH>"
      << "<tr_interceptDiam10ToDBH>"
      << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_3\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_4\">0</tr_idtdVal>"
      << "</tr_interceptDiam10ToDBH>"
      << "<tr_slopeOfHeight-Diam10>"
      << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_2\">0.03418</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_3\">0.03418</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_4\">0.03418</tr_sohdVal>"
      << "</tr_slopeOfHeight-Diam10>"
      << "<tr_whatSeedlingHeightDiam>"
      << "<tr_wsehdVal species=\"Species_1\">1</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_2\">1</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_3\">1</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_4\">1</tr_wsehdVal>"
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
      << "<tr_wacrdVal species=\"Species_1\">3</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Species_2\">3</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Species_3\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Species_4\">3</tr_wacrdVal>"
      << "</tr_whatAdultCrownRadDiam>"
      << "<tr_whatAdultCrownHeightHeight>"
      << "<tr_wachhVal species=\"Species_1\">3</tr_wachhVal>"
      << "<tr_wachhVal species=\"Species_2\">3</tr_wachhVal>"
      << "<tr_wachhVal species=\"Species_3\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Species_4\">3</tr_wachhVal>"
      << "</tr_whatAdultCrownHeightHeight>"
      << "<tr_whatSaplingCrownRadDiam>"
      << "<tr_wscrdVal species=\"Species_1\">3</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Species_2\">3</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Species_3\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Species_4\">3</tr_wscrdVal>"
      << "</tr_whatSaplingCrownRadDiam>"
      << "<tr_whatSaplingCrownHeightHeight>"
      << "<tr_wschhVal species=\"Species_1\">3</tr_wschhVal>"
      << "<tr_wschhVal species=\"Species_2\">3</tr_wschhVal>"
      << "<tr_wschhVal species=\"Species_3\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Species_4\">3</tr_wschhVal>"
      << "</tr_whatSaplingCrownHeightHeight>"
      << "<tr_seedlingLinearSlope>"
      << "<tr_selsVal species=\"Species_1\">0.9629</tr_selsVal>"
      << "<tr_selsVal species=\"Species_2\">0.9629</tr_selsVal>"
      << "<tr_selsVal species=\"Species_3\">1.228</tr_selsVal>"
      << "<tr_selsVal species=\"Species_4\">0.9629</tr_selsVal>"
      << "</tr_seedlingLinearSlope>"
      << "<tr_seedlingLinearIntercept>"
      << "<tr_seliVal species=\"Species_1\">0</tr_seliVal>"
      << "<tr_seliVal species=\"Species_2\">0</tr_seliVal>"
      << "<tr_seliVal species=\"Species_3\">-0.9</tr_seliVal>"
      << "<tr_seliVal species=\"Species_4\">0</tr_seliVal>"
      << "</tr_seedlingLinearIntercept>"
      << "<tr_nciCRSpecies_1NeighborLambda>"
      << "<tr_ncrlVal species=\"Species_1\">0.66401082</tr_ncrlVal>"
      << "<tr_ncrlVal species=\"Species_2\">0.71</tr_ncrlVal>"
      << "<tr_ncrlVal species=\"Species_4\">0.08</tr_ncrlVal>"
      << "</tr_nciCRSpecies_1NeighborLambda>"
      << "<tr_nciCRSpecies_2NeighborLambda>"
      << "<tr_ncrlVal species=\"Species_1\">0.00442797</tr_ncrlVal>"
      << "<tr_ncrlVal species=\"Species_2\">0.12</tr_ncrlVal>"
      << "<tr_ncrlVal species=\"Species_4\">0.03</tr_ncrlVal>"
      << "</tr_nciCRSpecies_2NeighborLambda>"
      << "<tr_nciCRSpecies_3NeighborLambda>"
      << "<tr_ncrlVal species=\"Species_1\">0.41812471</tr_ncrlVal>"
      << "<tr_ncrlVal species=\"Species_2\">0.24</tr_ncrlVal>"
      << "<tr_ncrlVal species=\"Species_4\">0.05</tr_ncrlVal>"
      << "</tr_nciCRSpecies_3NeighborLambda>"
      << "<tr_nciCRSpecies_4NeighborLambda>"
      << "<tr_ncrlVal species=\"Species_1\">0.41812471</tr_ncrlVal>"
      << "<tr_ncrlVal species=\"Species_2\">0.24</tr_ncrlVal>"
      << "<tr_ncrlVal species=\"Species_4\">0.05</tr_ncrlVal>"
      << "</tr_nciCRSpecies_4NeighborLambda>"
      << "<tr_nciCRMaxCrownRadius>"
      << "<tr_ncrmcrVal species=\"Species_1\">3.052587488</tr_ncrmcrVal>"
      << "<tr_ncrmcrVal species=\"Species_2\">5.2</tr_ncrmcrVal>"
      << "<tr_ncrmcrVal species=\"Species_4\">12.77</tr_ncrmcrVal>"
      << "</tr_nciCRMaxCrownRadius>"
      << "<tr_nciCRMaxCrowdingRadius>"
      << "<tr_ncrmcrVal species=\"Species_1\">10</tr_ncrmcrVal>"
      << "<tr_ncrmcrVal species=\"Species_2\">15</tr_ncrmcrVal>"
      << "<tr_ncrmcrVal species=\"Species_4\">10</tr_ncrmcrVal>"
      << "</tr_nciCRMaxCrowdingRadius>"
      << "<tr_nciCRAlpha>"
      << "<tr_ncraVal species=\"Species_1\">2.17031683</tr_ncraVal>"
      << "<tr_ncraVal species=\"Species_2\">2.81</tr_ncraVal>"
      << "<tr_ncraVal species=\"Species_4\">1.33</tr_ncraVal>"
      << "</tr_nciCRAlpha>"
      << "<tr_nciCRBeta>"
      << "<tr_ncrbVal species=\"Species_1\">0.69994199</tr_ncrbVal>"
      << "<tr_ncrbVal species=\"Species_2\">0.5</tr_ncrbVal>"
      << "<tr_ncrbVal species=\"Species_4\">0.09</tr_ncrbVal>"
      << "</tr_nciCRBeta>"
      << "<tr_nciCRGamma>"
      << "<tr_ncrgVal species=\"Species_1\">0</tr_ncrgVal>"
      << "<tr_ncrgVal species=\"Species_2\">-0.13</tr_ncrgVal>"
      << "<tr_ncrgVal species=\"Species_4\">-0.23</tr_ncrgVal>"
      << "</tr_nciCRGamma>"
      << "<tr_nciCRCrowdingN>"
      << "<tr_nccrnVal species=\"Species_1\">0.00163</tr_nccrnVal>"
      << "<tr_nccrnVal species=\"Species_2\">0.000126</tr_nccrnVal>"
      << "<tr_nccrnVal species=\"Species_4\">0.069</tr_nccrnVal>"
      << "</tr_nciCRCrowdingN>"
      << "<tr_nciCRMinNeighborDBH>"
      << "<tr_ncrmndVal species=\"Species_1\">10</tr_ncrmndVal>"
      << "<tr_ncrmndVal species=\"Species_2\">12</tr_ncrmndVal>"
      << "<tr_ncrmndVal species=\"Species_3\">16</tr_ncrmndVal>"
      << "<tr_ncrmndVal species=\"Species_4\">14</tr_ncrmndVal>"
      << "</tr_nciCRMinNeighborDBH>"
      << "<tr_nciCRSizeEffectD>"
      << "<tr_ncrsedVal species=\"Species_1\">0.163</tr_ncrsedVal>"
      << "<tr_ncrsedVal species=\"Species_2\">0.126</tr_ncrsedVal>"
      << "<tr_ncrsedVal species=\"Species_4\">0.0163</tr_ncrsedVal>"
      << "</tr_nciCRSizeEffectD>"
      << "<tr_nciCDSpecies_1NeighborLambda>"
      << "<tr_ncdlVal species=\"Species_1\">0.83</tr_ncdlVal>"
      << "<tr_ncdlVal species=\"Species_2\">0.33</tr_ncdlVal>"
      << "<tr_ncdlVal species=\"Species_4\">0.76</tr_ncdlVal>"
      << "</tr_nciCDSpecies_1NeighborLambda>"
      << "<tr_nciCDSpecies_2NeighborLambda>"
      << "<tr_ncdlVal species=\"Species_1\">0.54</tr_ncdlVal>"
      << "<tr_ncdlVal species=\"Species_2\">0.27</tr_ncdlVal>"
      << "<tr_ncdlVal species=\"Species_4\">0.7</tr_ncdlVal>"
      << "</tr_nciCDSpecies_2NeighborLambda>"
      << "<tr_nciCDSpecies_3NeighborLambda>"
      << "<tr_ncdlVal species=\"Species_1\">0.89</tr_ncdlVal>"
      << "<tr_ncdlVal species=\"Species_2\">0.9</tr_ncdlVal>"
      << "<tr_ncdlVal species=\"Species_4\">0.78</tr_ncdlVal>"
      << "</tr_nciCDSpecies_3NeighborLambda>"
      << "<tr_nciCDSpecies_4NeighborLambda>"
      << "<tr_ncdlVal species=\"Species_1\">0.89</tr_ncdlVal>"
      << "<tr_ncdlVal species=\"Species_2\">0.9</tr_ncdlVal>"
      << "<tr_ncdlVal species=\"Species_4\">0.78</tr_ncdlVal>"
      << "</tr_nciCDSpecies_4NeighborLambda>"
      << "<tr_nciCDMaxCrownDepth>"
      << "<tr_ncdmcrVal species=\"Species_1\">65.67</tr_ncdmcrVal>"
      << "<tr_ncdmcrVal species=\"Species_2\">9.52</tr_ncdmcrVal>"
      << "<tr_ncdmcrVal species=\"Species_4\">12.52</tr_ncdmcrVal>"
      << "</tr_nciCDMaxCrownDepth>"
      << "<tr_nciCDMaxCrowdingRadius>"
      << "<tr_ncdmcrVal species=\"Species_1\">10</tr_ncdmcrVal>"
      << "<tr_ncdmcrVal species=\"Species_2\">15</tr_ncdmcrVal>"
      << "<tr_ncdmcrVal species=\"Species_4\">10</tr_ncdmcrVal>"
      << "</tr_nciCDMaxCrowdingRadius>"
      << "<tr_nciCDAlpha>"
      << "<tr_ncdaVal species=\"Species_1\">1.052587488</tr_ncdaVal>"
      << "<tr_ncdaVal species=\"Species_2\">1.531</tr_ncdaVal>"
      << "<tr_ncdaVal species=\"Species_4\">0.994</tr_ncdaVal>"
      << "</tr_nciCDAlpha>"
      << "<tr_nciCDBeta>"
      << "<tr_ncdbVal species=\"Species_1\">0.698</tr_ncdbVal>"
      << "<tr_ncdbVal species=\"Species_2\">0.457</tr_ncdbVal>"
      << "<tr_ncdbVal species=\"Species_4\">0.469</tr_ncdbVal>"
      << "</tr_nciCDBeta>"
      << "<tr_nciCDGamma>"
      << "<tr_ncdgVal species=\"Species_1\">-0.0163</tr_ncdgVal>"
      << "<tr_ncdgVal species=\"Species_2\">-0.0126</tr_ncdgVal>"
      << "<tr_ncdgVal species=\"Species_4\">-0.000163</tr_ncdgVal>"
      << "</tr_nciCDGamma>"
      << "<tr_nciCDCrowdingN>"
      << "<tr_nccdnVal species=\"Species_1\">0.0034</tr_nccdnVal>"
      << "<tr_nccdnVal species=\"Species_2\">0.00526</tr_nccdnVal>"
      << "<tr_nccdnVal species=\"Species_4\">0.0163</tr_nccdnVal>"
      << "</tr_nciCDCrowdingN>"
      << "<tr_nciCDMinNeighborDBH>"
      << "<tr_ncdmndVal species=\"Species_1\">10</tr_ncdmndVal>"
      << "<tr_ncdmndVal species=\"Species_2\">12</tr_ncdmndVal>"
      << "<tr_ncdmndVal species=\"Species_3\">16</tr_ncdmndVal>"
      << "<tr_ncdmndVal species=\"Species_4\">14</tr_ncdmndVal>"
      << "</tr_nciCDMinNeighborDBH>"
      << "<tr_nciCDSizeEffectD>"
      << "<tr_ncdsedVal species=\"Species_1\">0.042</tr_ncdsedVal>"
      << "<tr_ncdsedVal species=\"Species_2\">0.034</tr_ncdsedVal>"
      << "<tr_ncdsedVal species=\"Species_4\">0.063</tr_ncdsedVal>"
      << "</tr_nciCDSizeEffectD>"
      << "</allometry>"
      << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>ConstantGLI</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\" />"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>StochasticMortality</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
      << "</behavior>"
      << "</behaviorList>"
      << "<ConstantGLI1>"
      << "<li_constGLI>100</li_constGLI>"
      << "</ConstantGLI1>"
      << "<StochasticMortality2>"
      << "<mo_stochasticMortRate>"
      << "<mo_smrVal species=\"Species_3\">0</mo_smrVal>"
      << "<mo_smrVal species=\"Species_1\">0</mo_smrVal>"
      << "<mo_smrVal species=\"Species_2\">0</mo_smrVal>"
      << "<mo_smrVal species=\"Species_4\">0</mo_smrVal>"
      << "</mo_stochasticMortRate>"
      << "</StochasticMortality2>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}
