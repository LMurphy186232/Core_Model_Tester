//---------------------------------------------------------------------------
// TestSnagDecomp.cpp
//---------------------------------------------------------------------------
#include "TestSnagDecomp.h"
#include <gtest/gtest.h>
#include "SimManager.h"
#include "TreePopulation.h"
#include "BehaviorBase.h"
#include <fstream>
#include <math.h>

/////////////////////////////////////////////////////////////////////////////
// TestSnagDecomp()
// Tests the Snag Decay Class Dynamics class.
// WriteSnagDecompXMLFile1() and WriteSnagDecompXMLFile2() create separate
// parameter file. The files have the following common characteristics:
//
// -- Timestep length of 5 years.
// -- 1 species used: ACSA
//
// WriteSnagDecompXMLFile1() tests the snag fall function under harvesting, as follows:
// -- 22500 live trees and 5600 decay class 1 snags are created.
// -- The model is run for 1 timestep.
// -- 5 m2/ha is cut roughly evenly across grid cells. The dead tree remover
// behavior is not invoked so they do not become snags.
// -- The number of snags in each decay class is counted and compared to expected
// results. Individual decay classes are +/- 10%, and total snags are +/- 2%.
//
// WriteSnagDecompXMLFile2() tests the tree fall function, as follows:
// -- 11200 live trees are created.
// -- The model is run for 1 timestep.
// -- 100% mortality kills all these trees.
// -- The number of snags in each decay class is counted and compared to expected
// results. Individual decay classes are +/- 10%, and total snags are +/- 2%.
//
// Error condition 1: WriteSnagDecompXMLErrorFile1() creates the paramter file. The
// behavior finds a negative parameter value and correctly throws an error.
//
// Error condition 2: WriteSnagDecompXMLErrorFile2() creates the parameter file. The
// behaviour finds that the sum of transition probabilities does not add up to
// 1 and correctly throws an error.
/////////////////////////////////////////////////////////////////////////////
TEST(SnagDecomp, TestSnagDecomp) {
  clTreePopulation * p_oPop;
  clTreeSearch *p_oAllTrees;
  clTree *p_oTree;
  int p_iTreeCount[6]; //snag count indexed by decay class
  int i, j, DecayClass;

  //--------------------------------------------------------------------------/
  // Run 1
  //--------------------------------------------------------------------------/

  //Create the sim manager and load our file
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  p_oSimManager->ReadFile(WriteSnagDecompXMLFile1() );
  p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject("treepopulation");

  //Zero out our tree count array
  for (i = 0; i < 6; i++) {
    p_iTreeCount[i] = 0;
  }

  //Create 5600 live trees and 22500 dc1 snags
  for (i = 0; i < 5600; i++)
    p_oTree = p_oPop->CreateTree(8+16*20.0*((i/14)/20)/20.0, 8+16*20.0*((i/14)
        %20)/20.0, 0, clTreePopulation::adult, 25.0-(i%14)/14.0/1000.0);

  for (i=0; i<22500; i++) {
    p_oTree = p_oPop->CreateTree(1+298.0*(i/150)/150.0, 1+298.0*(i%150)/150.0,
        0, clTreePopulation::snag, 25);
    //Assign decay class
    p_oTree->SetValue(p_oPop->GetIntDataCode("SnagDecayClass",
        p_oTree->GetSpecies(), p_oTree->GetType()), 1);
  }

  //Initial conditions count
  p_oAllTrees = p_oPop->Find("all");
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {
    if (p_oTree->GetType()==clTreePopulation::adult)
      DecayClass=0;
    else if (p_oTree->GetType()==clTreePopulation::snag)
      p_oTree->GetValue(p_oPop->GetIntDataCode("SnagDecayClass",
          p_oTree->GetSpecies(), p_oTree->GetType()), &DecayClass);

    p_iTreeCount[DecayClass]++;
    p_oTree = p_oAllTrees->NextTree();
  }

  EXPECT_EQ(p_iTreeCount[0], 5600);
  EXPECT_EQ(p_iTreeCount[1], 22500);
  for (i = 2; i <= 5; i++)
    EXPECT_EQ(p_iTreeCount[i], 0);

  //Run for one timestep
  p_oSimManager->RunSim(1);

  //Count the remaining trees
  for (j = 0; j < 6; j++)
    p_iTreeCount[j] = 0;

  p_oAllTrees = p_oPop->Find("all");
  p_oTree = p_oAllTrees->NextTree();

  while (p_oTree) {
    if (p_oTree->GetType()==clTreePopulation::adult)
      DecayClass=0;
    else if (p_oTree->GetType()==clTreePopulation::snag)
      p_oTree->GetValue(p_oPop->GetIntDataCode("SnagDecayClass",
          p_oTree->GetSpecies(), p_oTree->GetType()), &DecayClass);

    p_iTreeCount[DecayClass]++;
    p_oTree = p_oAllTrees->NextTree();
  }

  //Make sure they are as expected

  //All decay classes
  EXPECT_LT(fabs( (p_iTreeCount[1] + p_iTreeCount[2] + p_iTreeCount[3]
                                                                    + p_iTreeCount[4] + p_iTreeCount[5]) - 11598)/11598, 0.02);

  //Decay Class 1
  EXPECT_LT(fabs(p_iTreeCount[1] - 522)/522, 0.1);
  //Decay Class 2
  EXPECT_LT(fabs(p_iTreeCount[2] - 2157)/2157, 0.1);
  //Decay Class 3
  EXPECT_LT(fabs(p_iTreeCount[3] - 3816)/3816, 0.1);
  //Decay Class 4
  EXPECT_LT(fabs(p_iTreeCount[4] - 1925)/1925, 0.1);
  //Decay Class 5
  EXPECT_LT(fabs(p_iTreeCount[5] - 3178)/3178, 0.1);

  //--------------------------------------------------------------------------/
  // Run 2
  //--------------------------------------------------------------------------/

  p_oSimManager->ReadFile(WriteSnagDecompXMLFile2() );
  p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject("treepopulation");

  //Zero out our tree count array
  for (j = 0; j < 6; j++) {
    p_iTreeCount[j] = 0;
  }

  //Create 11200 live trees
  for (i = 0; i < 11200; i++) {
    p_oTree = p_oPop->CreateTree(8+16*20.0*((i/28)/20)/20.0, 8+16*20.0*((i/28)
        %20)/20.0, 0, clTreePopulation::adult, 10.0);

  }

  //Initial conditions count
  p_oAllTrees = p_oPop->Find("all");
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {
    if (p_oTree->GetType()==clTreePopulation::adult) {
      p_iTreeCount[0]++;
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  EXPECT_EQ(p_iTreeCount[0], 11200);

  p_oSimManager->RunSim(1);

  //Count the remaining trees
  for (j = 0; j < 6; j++)
    p_iTreeCount[j] = 0;

  p_oAllTrees = p_oPop->Find("all");
  p_oTree = p_oAllTrees->NextTree();

  while (p_oTree) {
    if (p_oTree->GetType()==clTreePopulation::adult)
      DecayClass=0;
    else if (p_oTree->GetType()==clTreePopulation::snag)
      p_oTree->GetValue(p_oPop->GetIntDataCode("SnagDecayClass",
          p_oTree->GetSpecies(), p_oTree->GetType()), &DecayClass);

    p_iTreeCount[DecayClass]++;
    p_oTree = p_oAllTrees->NextTree();
  }

  //Make sure they are as expected

  //Live trees
  EXPECT_EQ(p_iTreeCount[0], 0);

  //All decay classes
  EXPECT_LT(fabs( (p_iTreeCount[1] + p_iTreeCount[2] + p_iTreeCount[3]
                                                                    + p_iTreeCount[4] + p_iTreeCount[5]) - 8645)/8645, 0.02);

  //Decay Class 1
  EXPECT_LT(fabs(p_iTreeCount[1] - 2507)/2507, 0.1);
  //Decay Class 2
  EXPECT_LT(fabs(p_iTreeCount[2] - 1980)/1980, 0.1);
  //Decay Class 3
  EXPECT_LT(fabs(p_iTreeCount[3] - 1694)/1694, 0.1);
  //Decay Class 4
  EXPECT_LT(fabs(p_iTreeCount[4] - 1072)/1072, 0.1);
  //Decay Class 5
  EXPECT_LT(fabs(p_iTreeCount[5] - 1392)/1392, 0.1);

  delete p_oSimManager;
}

/**
 * There are snags but no initial conditions parameters. All snags should be
 * decay class 1.
 */
TEST(SnagDecomp, TestSnagInitialConditions1) {
  clSimManager *p_oSimManager;
  int **p_iSnagCounts = new int*[3];
  try {
    clTreePopulation * p_oPop;
    clTreeSearch *p_oAllTrees;
    clTree *p_oTree;
    float fDbh;
    int **p_iSnagCounts = new int*[3], i, j, iDecayClass;

    //Counts:  first index size class, second species
    for (i = 0; i < 3; i++) {
      p_iSnagCounts[i] = new int[3];
    }

    //Create the sim manager and load our file
    p_oSimManager = new clSimManager( 7, 5, "" );
    p_oSimManager->ReadFile(WriteSnagsInitFile1() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject("treepopulation");

    // Zero out the counting array
    for (i = 0; i < 3; i++) {
      for (j = 0; j < 3; j++) {
        p_iSnagCounts[i][j] = 0;
      }
    }

    //Find all trees
    p_oAllTrees = p_oPop->Find( "all" );
    p_oTree = p_oAllTrees->NextTree();
    while ( p_oTree )
    {

      if (p_oTree->GetType() == clTreePopulation::snag) {

        //----------------------------------------------------------------------/
        // Verify decay class is always 1
        //----------------------------------------------------------------------/
        p_oTree->GetValue(p_oPop->GetIntDataCode("SnagDecayClass",
            p_oTree->GetSpecies(), p_oTree->GetType()), &iDecayClass);


        EXPECT_EQ(iDecayClass, 1);

        //Get the DBH
        p_oTree->GetValue( p_oPop->GetDbhCode(
            p_oTree->GetSpecies(), p_oTree->GetType() ), & fDbh );

        if (fDbh < 10) FAIL() << "Snags can't be tiny!";
        if (fDbh <= 10) { //just in case it's exactly 10
          p_iSnagCounts[0][p_oTree->GetSpecies()]++;
        }
        else if (fDbh > 10 && fDbh <= 15) {
          p_iSnagCounts[1][p_oTree->GetSpecies()]++;
        }
        else if (fDbh > 15 && fDbh <= 35) {
          p_iSnagCounts[2][p_oTree->GetSpecies()]++;
        }
        else {
          FAIL() << "Unexpected DBH for TestSnagInitialConditions1!";
        }
      }
      p_oTree = p_oAllTrees->NextTree();
    }


    //Species 1
    EXPECT_EQ( p_iSnagCounts[0][0], 0 );
    EXPECT_EQ( p_iSnagCounts[1][0], 100 );
    EXPECT_EQ( p_iSnagCounts[2][0], 160 );
    //Species 2
    EXPECT_EQ( p_iSnagCounts[0][1], 0 );
    EXPECT_EQ( p_iSnagCounts[1][1], 120 );
    EXPECT_EQ( p_iSnagCounts[2][1], 0 );
    //Species 3
    EXPECT_EQ( p_iSnagCounts[0][2], 0 );
    EXPECT_EQ( p_iSnagCounts[1][2], 140 );
    EXPECT_EQ( p_iSnagCounts[2][2], 200 );

    for (i = 0; i < 3; i++) {
      delete[] p_iSnagCounts[i];
    }
    delete[] p_iSnagCounts;
    delete p_oSimManager;
  } catch (modelErr &e) {
    for (int i = 0; i < 3; i++) {
      delete[] p_iSnagCounts[i];
    }
    delete[] p_iSnagCounts;
    delete p_oSimManager;
  }
}

/**
 * There are snags and, for a given species/size class combo:
 * All snags are decay class 1.
 * All snags are decay class 2.
 * All snags are decay class 3.
 * All snags are decay class 4.
 * All snags are decay class 5.
 * There are a mix of class values.
 */
TEST(SnagDecomp, TestSnagInitialConditions2) {
  clSimManager *p_oSimManager;
  int **p_iSnagCounts = new int*[3];
  try {
    clTreePopulation * p_oPop;
    clTreeSearch *p_oAllTrees;
    clTree *p_oTree;
    float fDbh;
    int *p_iSnagCounts = NULL, i, iDecayClass, iSp, iTp, iNum;


    //Create the sim manager and load our file
    p_oSimManager = new clSimManager( 7, 5, "" );
    p_oSimManager->ReadFile(WriteSnagsInitFile2() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject("treepopulation");

    //------------------------------------------------------------------------/
    // First blush validation: make sure that all our snags are the right size
    //------------------------------------------------------------------------/
    p_oAllTrees = p_oPop->Find( "all" );
    p_oTree = p_oAllTrees->NextTree();
    while ( p_oTree ) {

      if (p_oTree->GetType() == clTreePopulation::snag) {

        iSp = p_oTree->GetSpecies();
        iTp = p_oTree->GetType();

        //Get the DBH
        p_oTree->GetValue( p_oPop->GetDbhCode(iSp, iTp), & fDbh );

        if (fDbh <= 10 || fDbh > 35) {
          FAIL() << "Unexpected DBH for TestSnagInitialConditions2!";
        }

      }
      p_oTree = p_oAllTrees->NextTree();
    }

    //------------------------------------------------------------------------/
    // Be incredibly lazy and validate one species / size class at a time.
    // Species= 1, size class = 15.0: all are decay class 1.
    //------------------------------------------------------------------------/
    iNum = 0;
    p_oAllTrees = p_oPop->Find( "all" );
    p_oTree = p_oAllTrees->NextTree();
    while ( p_oTree ) {

      if (p_oTree->GetType() == clTreePopulation::snag) {

        iSp = p_oTree->GetSpecies();
        iTp = p_oTree->GetType();

        //Get the DBH
        p_oTree->GetValue( p_oPop->GetDbhCode(iSp, iTp), & fDbh );

        if (iSp == 0 && fDbh <= 15) {
          p_oTree->GetValue(p_oPop->GetIntDataCode("SnagDecayClass", iSp, iTp),
              &iDecayClass);

          EXPECT_EQ(iDecayClass, 1);
          iNum++;
        }

      }
      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(iNum, 1000);
    //------------------------------------------------------------------------/



    //------------------------------------------------------------------------/
    // Species= 1, size class = 35.0: all are decay class 2.
    //------------------------------------------------------------------------/
    iNum = 0;
    p_oAllTrees = p_oPop->Find( "all" );
    p_oTree = p_oAllTrees->NextTree();
    while ( p_oTree ) {

      if (p_oTree->GetType() == clTreePopulation::snag) {

        iSp = p_oTree->GetSpecies();
        iTp = p_oTree->GetType();

        //Get the DBH
        p_oTree->GetValue( p_oPop->GetDbhCode(iSp, iTp), & fDbh );

        if (iSp == 0 && fDbh > 15 && fDbh <= 35) {
          p_oTree->GetValue(p_oPop->GetIntDataCode("SnagDecayClass", iSp, iTp),
              &iDecayClass);

          EXPECT_EQ(iDecayClass, 2);
          iNum++;
        }

      }
      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(iNum, 1000);
    //------------------------------------------------------------------------/



    //------------------------------------------------------------------------/
    // Species= 2, size class = 15.0: all are decay class 2.
    //------------------------------------------------------------------------/
    iNum = 0;
    p_oAllTrees = p_oPop->Find( "all" );
    p_oTree = p_oAllTrees->NextTree();
    while ( p_oTree ) {

      if (p_oTree->GetType() == clTreePopulation::snag) {

        iSp = p_oTree->GetSpecies();
        iTp = p_oTree->GetType();

        //Get the DBH
        p_oTree->GetValue( p_oPop->GetDbhCode(iSp, iTp), & fDbh );

        if (iSp == 1 && fDbh <= 15) {
          p_oTree->GetValue(p_oPop->GetIntDataCode("SnagDecayClass", iSp, iTp),
              &iDecayClass);

          EXPECT_EQ(iDecayClass, 3);
          iNum++;
        }

      }
      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(iNum, 1000);
    //------------------------------------------------------------------------/


    //------------------------------------------------------------------------/
    // Species= 2, size class = 35.0: all are decay class 4.
    //------------------------------------------------------------------------/
    iNum = 0;
    p_oAllTrees = p_oPop->Find( "all" );
    p_oTree = p_oAllTrees->NextTree();
    while ( p_oTree ) {

      if (p_oTree->GetType() == clTreePopulation::snag) {

        iSp = p_oTree->GetSpecies();
        iTp = p_oTree->GetType();

        //Get the DBH
        p_oTree->GetValue( p_oPop->GetDbhCode(iSp, iTp), & fDbh );

        if (iSp == 1 && fDbh > 15 && fDbh <= 35) {
          p_oTree->GetValue(p_oPop->GetIntDataCode("SnagDecayClass", iSp, iTp),
              &iDecayClass);

          EXPECT_EQ(iDecayClass, 4);
          iNum++;
        }

      }
      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(iNum, 1000);
    //------------------------------------------------------------------------/


    //------------------------------------------------------------------------/
    // Species= 3, size class = 15.0: all are decay class 5.
    //------------------------------------------------------------------------/
    iNum = 0;
    p_oAllTrees = p_oPop->Find( "all" );
    p_oTree = p_oAllTrees->NextTree();
    while ( p_oTree ) {

      if (p_oTree->GetType() == clTreePopulation::snag) {

        iSp = p_oTree->GetSpecies();
        iTp = p_oTree->GetType();

        //Get the DBH
        p_oTree->GetValue( p_oPop->GetDbhCode(iSp, iTp), & fDbh );

        if (iSp == 2 && fDbh <= 15) {
          p_oTree->GetValue(p_oPop->GetIntDataCode("SnagDecayClass", iSp, iTp),
              &iDecayClass);

          EXPECT_EQ(iDecayClass, 5);
          iNum++;
        }

      }
      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(iNum, 1000);
    //------------------------------------------------------------------------/



    //------------------------------------------------------------------------/
    // Species= 3, size class = 35.0: decay class mix.
    // Decay class 1: 0.25
    // Decay class 2: 0.31
    // Decay class 3: 0.18
    // Decay class 4: 0.22
    // Decay class 5: 0.04
    //------------------------------------------------------------------------/
    p_iSnagCounts = new int[5];
    for (i = 0; i < 5; i++) p_iSnagCounts[i] = 0;
    p_oAllTrees = p_oPop->Find( "all" );
    p_oTree = p_oAllTrees->NextTree();
    while ( p_oTree ) {

      if (p_oTree->GetType() == clTreePopulation::snag) {

        iSp = p_oTree->GetSpecies();
        iTp = p_oTree->GetType();

        //Get the DBH
        p_oTree->GetValue( p_oPop->GetDbhCode(iSp, iTp), & fDbh );

        if (iSp == 2 && fDbh > 15 && fDbh <= 35) {
          p_oTree->GetValue(p_oPop->GetIntDataCode("SnagDecayClass", iSp, iTp),
              &iDecayClass);

          p_iSnagCounts[(iDecayClass-1)]++;
        }

      }
      p_oTree = p_oAllTrees->NextTree();
    }

    EXPECT_NEAR(p_iSnagCounts[0], 250, 10);
    EXPECT_NEAR(p_iSnagCounts[1], 310, 10);
    EXPECT_NEAR(p_iSnagCounts[2], 180, 10);
    EXPECT_NEAR(p_iSnagCounts[3], 220, 10);
    EXPECT_NEAR(p_iSnagCounts[4], 40 , 10);

    delete[] p_iSnagCounts;
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete[] p_iSnagCounts;
    delete p_oSimManager;
  }
}



////////////////////////////////////////////////////////////////////////////
// TestErrorProcessing()
////////////////////////////////////////////////////////////////////////////
TEST(SnagDecomp, TestErrorProcessing) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try
  {
    //Identify negative parameter value.
    p_oSimManager->ReadFile(WriteSnagDecompXMLErrorFile1());
    FAIL() << "TestSnagDecomp error processing didn't catch error for WriteSnagDecompXMLErrorFile1.";
  }
  catch (modelErr& err)
  {
    if (err.sMoreInfo.compare("Values for transition probabilites cannot be less than 0.") != 0)
    {
      FAIL() << "TestSnagDecomp error processing caught wrong error for WriteSnagDecompXMLErrorFile1.";
    }
    ;
  }

  try
  {
    //Identify that transition probabilities don't sum up to 1.
    p_oSimManager->ReadFile(WriteSnagDecompXMLErrorFile2());
    FAIL() << "TestSnagDecomp error processing didn't catch error for WriteSnagDecompXMLErrorFile2.";
  }
  catch (modelErr& err)
  {
    if (err.sMoreInfo.compare("Sum of transition probabilities must add up to 1 within each column.") != 0)
    {
      FAIL() << "TestSnagDecomp error processing caught wrong error for WriteSnagDecompXMLErrorFile2.";
    }
    ;
  }
  delete p_oSimManager;
}

/////////////////////////////////////////////////////////////////////////////
// WriteSnagDecompXMLFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteSnagDecompXMLFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06050101\">"
      << "<plot>"
      << "<timesteps>1</timesteps>"
      << "<rt_timestep>0</rt_timestep><randomSeed>0</randomSeed>"
      << "<yearsPerTimestep>5.0</yearsPerTimestep>"
      << "<plot_lenX>320.0</plot_lenX>"
      << "<plot_lenY>320.0</plot_lenY>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88171785</plot_temp_C>"
      << "<plot_latitude>41.92</plot_latitude>"
      << "<plot_title>Default parameter file-use for testing only</plot_title>"
      << "</plot>"
      << "<trees>"
      << "<tr_speciesList>"
      << "<tr_species speciesName=\"ACSA\"/>"
      << "</tr_speciesList>"
      << "<tr_seedDiam10Cm>0.2</tr_seedDiam10Cm>"
      << "<tr_minAdultDBH>"
      << "<tr_madVal species=\"ACSA\">10.0</tr_madVal>"
      << "</tr_minAdultDBH>"
      << "<tr_maxSeedlingHeight>"
      << "<tr_mshVal species=\"ACSA\">1.35</tr_mshVal>"
      << "</tr_maxSeedlingHeight>"
      << "</trees>"
      << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>Harvest</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>1</listPosition>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>StochasticMortality</behaviorName>"
      << "<version>1</version>"
      << "<applyTo species=\"ACSA\" type=\"Adult\" />"
      << "<listPosition>2</listPosition>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>SnagDecayClassDynamics</behaviorName>"
      << "<version>2.0</version>"
      << "<listPosition>3</listPosition>"
      << "<applyTo species=\"ACSA\" type=\"Adult\" />"
      << "<applyTo species=\"ACSA\" type=\"Snag\" />"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>RemoveDead</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>4</listPosition>"
      << "<applyTo species=\"ACSA\" type=\"Snag\" />"
      << "</behavior>"
      << "</behaviorList>"
      << "<Harvest1>"
      << "<ha_cutEvent>"
      << "<ha_applyToSpecies species=\"ACSA\" />"
      << "<ha_timestep>1</ha_timestep>"
      << "<ha_cutType>partial</ha_cutType>"
      << "<ha_cutAmountType>absolute density</ha_cutAmountType>"
      << "<ha_dbhRange>"
      << "<ha_low>1.0</ha_low>"
      << "<ha_high>100.0</ha_high>"
      << "<ha_amountToCut>117.1875</ha_amountToCut>"
      << "</ha_dbhRange>";

  for (int iX = 0; iX < 40; iX++)
    for (int iY = 0; iY < 40; iY++)
      oOut << "<ha_applyToCell x=\"" << iX << "\" y=\"" << iY << "\" />";

  oOut << "</ha_cutEvent>"
      << "</Harvest1>"
      << "<allometry>"
      << "<tr_whatAdultHeightDiam>"
      << "<tr_wahdVal species=\"ACSA\">0</tr_wahdVal>"
      << "</tr_whatAdultHeightDiam>"
      << "<tr_whatSaplingHeightDiam>"
      << "<tr_wsahdVal species=\"ACSA\">0</tr_wsahdVal>"
      << "</tr_whatSaplingHeightDiam>"
      << "<tr_whatSeedlingHeightDiam>"
      << "<tr_wsehdVal species=\"ACSA\">0</tr_wsehdVal>"
      << "</tr_whatSeedlingHeightDiam>"
      << "<tr_whatAdultCrownRadDiam>"
      << "<tr_wacrdVal species=\"ACSA\">0</tr_wacrdVal>"
      << "</tr_whatAdultCrownRadDiam>"
      << "<tr_whatSaplingCrownRadDiam>"
      << "<tr_wscrdVal species=\"ACSA\">0</tr_wscrdVal>"
      << "</tr_whatSaplingCrownRadDiam>"
      << "<tr_whatAdultCrownHeightHeight>"
      << "<tr_wachhVal species=\"ACSA\">0</tr_wachhVal>"
      << "</tr_whatAdultCrownHeightHeight>"
      << "<tr_whatSaplingCrownHeightHeight>"
      << "<tr_wschhVal species=\"ACSA\">0</tr_wschhVal>"
      << "</tr_whatSaplingCrownHeightHeight>"
      << "<tr_canopyHeight>"
      << "<tr_chVal species=\"ACSA\">24.8</tr_chVal>"
      << "</tr_canopyHeight>"
      << "<tr_stdAsympCrownRad>"
      << "<tr_sacrVal species=\"ACSA\">0.107</tr_sacrVal>"
      << "</tr_stdAsympCrownRad>"
      << "<tr_stdCrownRadExp>"
      << "<tr_screVal species=\"ACSA\">1.0</tr_screVal>"
      << "</tr_stdCrownRadExp>"
      << "<tr_stdMaxCrownRad>"
      << "<tr_smcrVal species=\"ACSA\">10</tr_smcrVal>"
      << "</tr_stdMaxCrownRad>"
      << "<tr_stdAsympCrownHt>"
      << "<tr_sachVal species=\"ACSA\">0.58</tr_sachVal>"
      << "</tr_stdAsympCrownHt>"
      << "<tr_stdCrownHtExp>"
      << "<tr_scheVal species=\"ACSA\">1.0</tr_scheVal>"
      << "</tr_stdCrownHtExp>"
      << "<tr_conversionDiam10ToDBH>"
      << "<tr_cdtdVal species=\"ACSA\">0.75</tr_cdtdVal>"
      << "</tr_conversionDiam10ToDBH>"
      << "<tr_interceptDiam10ToDBH>"
      << "<tr_idtdVal species=\"ACSA\">0.0</tr_idtdVal>"
      << "</tr_interceptDiam10ToDBH>"
      << "<tr_slopeOfAsymHeight>"
      << "<tr_soahVal species=\"ACSA\">0.062333334</tr_soahVal>"
      << "</tr_slopeOfAsymHeight>"
      << "<tr_slopeOfHeight-Diam10>"
      << "<tr_sohdVal species=\"ACSA\">0.03</tr_sohdVal>"
      << "</tr_slopeOfHeight-Diam10>"
      << "</allometry>"
      << "<StochasticMortality2>"
      << "<mo_stochasticMortRate>"
      << "<mo_smrVal species=\"ACSA\">0.0</mo_smrVal>"
      << "</mo_stochasticMortRate>"
      << "</StochasticMortality2>"
      << "<SnagDecayClassDynamics3>"
      << "<sd_snagDecompTreefallAlpha>-0.805</sd_snagDecompTreefallAlpha>"
      << "<sd_snagDecompTreefallBeta>"
      << "<sd_sdtbVal species=\"ACSA\">0.000</sd_sdtbVal>"
      << "</sd_snagDecompTreefallBeta>"
      << "<sd_snagDecompTreefallDelta>-0.016</sd_snagDecompTreefallDelta>"
      << "<sd_snagDecompTreefallTheta>-0.026</sd_snagDecompTreefallTheta>"
      << "<sd_snagDecompTreefallIota>3.389</sd_snagDecompTreefallIota>"
      << "<sd_snagDecompTreefallLambda>-0.084</sd_snagDecompTreefallLambda>"
      << "<sd_snagDecompSnagfallAlpha>5.691</sd_snagDecompSnagfallAlpha>"
      << "<sd_snagDecompSnagfallBeta>"
      << "<sd_sdsbVal species=\"ACSA\">0.000</sd_sdsbVal>"
      << "</sd_snagDecompSnagfallBeta>"
      << "<sd_snagDecompSnagfallGamma2>0.177</sd_snagDecompSnagfallGamma2>"
      << "<sd_snagDecompSnagfallGamma3>0.542</sd_snagDecompSnagfallGamma3>"
      << "<sd_snagDecompSnagfallGamma4>0.702</sd_snagDecompSnagfallGamma4>"
      << "<sd_snagDecompSnagfallGamma5>0.528</sd_snagDecompSnagfallGamma5>"
      << "<sd_snagDecompSnagfallZeta>-3.777</sd_snagDecompSnagfallZeta>"
      << "<sd_snagDecompSnagfallEta>0.531</sd_snagDecompSnagfallEta>"
      << "<sd_snagDecompSnagfallKappa>0.157</sd_snagDecompSnagfallKappa>"
      << "<sd_snagDecompLiveTo1Prob>0.290</sd_snagDecompLiveTo1Prob>"
      << "<sd_snagDecompLiveTo2Prob>0.229</sd_snagDecompLiveTo2Prob>"
      << "<sd_snagDecompLiveTo3Prob>0.196</sd_snagDecompLiveTo3Prob>"
      << "<sd_snagDecompLiveTo4Prob>0.124</sd_snagDecompLiveTo4Prob>"
      << "<sd_snagDecompLiveTo5Prob>0.161</sd_snagDecompLiveTo5Prob>"
      << "<sd_snagDecomp1To1Prob>0.045</sd_snagDecomp1To1Prob>"
      << "<sd_snagDecomp1To2Prob>0.186</sd_snagDecomp1To2Prob>"
      << "<sd_snagDecomp1To3Prob>0.329</sd_snagDecomp1To3Prob>"
      << "<sd_snagDecomp1To4Prob>0.166</sd_snagDecomp1To4Prob>"
      << "<sd_snagDecomp1To5Prob>0.274</sd_snagDecomp1To5Prob>"
      << "<sd_snagDecomp2To2Prob>0.165</sd_snagDecomp2To2Prob>"
      << "<sd_snagDecomp2To3Prob>0.379</sd_snagDecomp2To3Prob>"
      << "<sd_snagDecomp2To4Prob>0.204</sd_snagDecomp2To4Prob>"
      << "<sd_snagDecomp2To5Prob>0.252</sd_snagDecomp2To5Prob>"
      << "<sd_snagDecomp3To3Prob>0.351</sd_snagDecomp3To3Prob>"
      << "<sd_snagDecomp3To4Prob>0.346</sd_snagDecomp3To4Prob>"
      << "<sd_snagDecomp3To5Prob>0.303</sd_snagDecomp3To5Prob>"
      << "<sd_snagDecomp4To4Prob>0.527</sd_snagDecomp4To4Prob>"
      << "<sd_snagDecomp4To5Prob>0.473</sd_snagDecomp4To5Prob>"
      << "<sd_snagDecomp5To5Prob>1.000</sd_snagDecomp5To5Prob>"
      << "<sd_minSnagBreakHeight>6</sd_minSnagBreakHeight>"
      << "<sd_maxSnagBreakHeight>6</sd_maxSnagBreakHeight>"
      << "</SnagDecayClassDynamics3>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteSnagDecompXMLFile2()
/////////////////////////////////////////////////////////////////////////////
const char* WriteSnagDecompXMLFile2() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?><paramFile fileCode=\"06050101\">"
      << "<plot>"
      << "<timesteps>1</timesteps>"
      << "<randomSeed>0</randomSeed>"
      << "<yearsPerTimestep>5.0</yearsPerTimestep>"
      << "<plot_lenX>320.0</plot_lenX>"
      << "<plot_lenY>320.0</plot_lenY>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88171785</plot_temp_C>"
      << "<plot_latitude>41.92</plot_latitude>"
      << "<plot_title>Default parameter file-use for testing only</plot_title>"
      << "</plot>"
      << "<trees>"
      << "<tr_speciesList>"
      << "<tr_species speciesName=\"ACSA\"/>"
      << "</tr_speciesList>"
      << "<tr_seedDiam10Cm>0.2</tr_seedDiam10Cm>"
      << "<tr_minAdultDBH>"
      << "<tr_madVal species=\"ACSA\">10.0</tr_madVal>"
      << "</tr_minAdultDBH>"
      << "<tr_maxSeedlingHeight>"
      << "<tr_mshVal species=\"ACSA\">1.35</tr_mshVal>"
      << "</tr_maxSeedlingHeight>"
      << "</trees>"
      << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>StochasticMortality</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"ACSA\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>SnagDecayClassDynamics</behaviorName>"
      << "<version>2.0</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"ACSA\" type=\"Adult\" />"
      << "<applyTo species=\"ACSA\" type=\"Snag\" />"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>RemoveDead</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>3</listPosition>"
      << "<applyTo species=\"ACSA\" type=\"Adult\" />"
      << "<applyTo species=\"ACSA\" type=\"Snag\" />"
      << "</behavior>"
      << "</behaviorList>"
      << "<allometry>"
      << "<tr_whatAdultHeightDiam>"
      << "<tr_wahdVal species=\"ACSA\">0</tr_wahdVal>"
      << "</tr_whatAdultHeightDiam>"
      << "<tr_whatSaplingHeightDiam>"
      << "<tr_wsahdVal species=\"ACSA\">0</tr_wsahdVal>"
      << "</tr_whatSaplingHeightDiam>"
      << "<tr_whatSeedlingHeightDiam>"
      << "<tr_wsehdVal species=\"ACSA\">0</tr_wsehdVal>"
      << "</tr_whatSeedlingHeightDiam>"
      << "<tr_whatAdultCrownRadDiam>"
      << "<tr_wacrdVal species=\"ACSA\">0</tr_wacrdVal>"
      << "</tr_whatAdultCrownRadDiam>"
      << "<tr_whatSaplingCrownRadDiam>"
      << "<tr_wscrdVal species=\"ACSA\">0</tr_wscrdVal>"
      << "</tr_whatSaplingCrownRadDiam>"
      << "<tr_whatAdultCrownHeightHeight>"
      << "<tr_wachhVal species=\"ACSA\">0</tr_wachhVal>"
      << "</tr_whatAdultCrownHeightHeight>"
      << "<tr_whatSaplingCrownHeightHeight>"
      << "<tr_wschhVal species=\"ACSA\">0</tr_wschhVal>"
      << "</tr_whatSaplingCrownHeightHeight>"
      << "<tr_canopyHeight>"
      << "<tr_chVal species=\"ACSA\">24.8</tr_chVal>"
      << "</tr_canopyHeight>"
      << "<tr_stdAsympCrownRad>"
      << "<tr_sacrVal species=\"ACSA\">0.107</tr_sacrVal>"
      << "</tr_stdAsympCrownRad>"
      << "<tr_stdCrownRadExp>"
      << "<tr_screVal species=\"ACSA\">1.0</tr_screVal>"
      << "</tr_stdCrownRadExp>"
      << "<tr_stdMaxCrownRad>"
      << "<tr_smcrVal species=\"ACSA\">10</tr_smcrVal>"
      << "</tr_stdMaxCrownRad>"
      << "<tr_stdAsympCrownHt>"
      << "<tr_sachVal species=\"ACSA\">0.58</tr_sachVal>"
      << "</tr_stdAsympCrownHt>"
      << "<tr_stdCrownHtExp>"
      << "<tr_scheVal species=\"ACSA\">1.0</tr_scheVal>"
      << "</tr_stdCrownHtExp>"
      << "<tr_conversionDiam10ToDBH>"
      << "<tr_cdtdVal species=\"ACSA\">0.75</tr_cdtdVal>"
      << "</tr_conversionDiam10ToDBH>"
      << "<tr_interceptDiam10ToDBH>"
      << "<tr_idtdVal species=\"ACSA\">0.0</tr_idtdVal>"
      << "</tr_interceptDiam10ToDBH>"
      << "<tr_slopeOfAsymHeight>"
      << "<tr_soahVal species=\"ACSA\">0.062333334</tr_soahVal>"
      << "</tr_slopeOfAsymHeight><tr_slopeOfHeight-Diam10>"
      << "<tr_sohdVal species=\"ACSA\">0.03</tr_sohdVal>"
      << "</tr_slopeOfHeight-Diam10>"
      << "</allometry>"
      << "<StochasticMortality1>"
      << "<mo_stochasticMortRate>"
      << "<mo_smrVal species=\"ACSA\">1.0</mo_smrVal>"
      << "</mo_stochasticMortRate>"
      << "</StochasticMortality1>"
      << "<SnagDecayClassDynamics2>"
      << "<sd_snagDecompTreefallAlpha>-0.805</sd_snagDecompTreefallAlpha>"
      << "<sd_snagDecompTreefallBeta>"
      << "<sd_sdtbVal species=\"ACSA\">0.000</sd_sdtbVal>"
      << "</sd_snagDecompTreefallBeta>"
      << "<sd_snagDecompTreefallDelta>-0.016</sd_snagDecompTreefallDelta>"
      << "<sd_snagDecompTreefallTheta>-0.026</sd_snagDecompTreefallTheta>"
      << "<sd_snagDecompTreefallIota>3.389</sd_snagDecompTreefallIota>"
      << "<sd_snagDecompTreefallLambda>-0.084</sd_snagDecompTreefallLambda>"
      << "<sd_snagDecompSnagfallAlpha>5.691</sd_snagDecompSnagfallAlpha>"
      << "<sd_snagDecompSnagfallBeta>"
      << "<sd_sdsbVal species=\"ACSA\">0.000</sd_sdsbVal>"
      << "</sd_snagDecompSnagfallBeta>"
      << "<sd_snagDecompSnagfallGamma2>0.177</sd_snagDecompSnagfallGamma2>"
      << "<sd_snagDecompSnagfallGamma3>0.542</sd_snagDecompSnagfallGamma3>"
      << "<sd_snagDecompSnagfallGamma4>0.702</sd_snagDecompSnagfallGamma4>"
      << "<sd_snagDecompSnagfallGamma5>0.528</sd_snagDecompSnagfallGamma5>"
      << "<sd_snagDecompSnagfallZeta>-3.777</sd_snagDecompSnagfallZeta>"
      << "<sd_snagDecompSnagfallEta>0.531</sd_snagDecompSnagfallEta>"
      << "<sd_snagDecompSnagfallKappa>0.157</sd_snagDecompSnagfallKappa>"
      << "<sd_snagDecompLiveTo1Prob>0.290</sd_snagDecompLiveTo1Prob>"
      << "<sd_snagDecompLiveTo2Prob>0.229</sd_snagDecompLiveTo2Prob>"
      << "<sd_snagDecompLiveTo3Prob>0.196</sd_snagDecompLiveTo3Prob>"
      << "<sd_snagDecompLiveTo4Prob>0.124</sd_snagDecompLiveTo4Prob>"
      << "<sd_snagDecompLiveTo5Prob>0.161</sd_snagDecompLiveTo5Prob>"
      << "<sd_snagDecomp1To1Prob>0.045</sd_snagDecomp1To1Prob>"
      << "<sd_snagDecomp1To2Prob>0.186</sd_snagDecomp1To2Prob>"
      << "<sd_snagDecomp1To3Prob>0.329</sd_snagDecomp1To3Prob>"
      << "<sd_snagDecomp1To4Prob>0.166</sd_snagDecomp1To4Prob>"
      << "<sd_snagDecomp1To5Prob>0.274</sd_snagDecomp1To5Prob>"
      << "<sd_snagDecomp2To2Prob>0.165</sd_snagDecomp2To2Prob>"
      << "<sd_snagDecomp2To3Prob>0.379</sd_snagDecomp2To3Prob>"
      << "<sd_snagDecomp2To4Prob>0.204</sd_snagDecomp2To4Prob>"
      << "<sd_snagDecomp2To5Prob>0.252</sd_snagDecomp2To5Prob>"
      << "<sd_snagDecomp3To3Prob>0.351</sd_snagDecomp3To3Prob>"
      << "<sd_snagDecomp3To4Prob>0.346</sd_snagDecomp3To4Prob>"
      << "<sd_snagDecomp3To5Prob>0.303</sd_snagDecomp3To5Prob>"
      << "<sd_snagDecomp4To4Prob>0.527</sd_snagDecomp4To4Prob>"
      << "<sd_snagDecomp4To5Prob>0.473</sd_snagDecomp4To5Prob>"
      << "<sd_snagDecomp5To5Prob>1.000</sd_snagDecomp5To5Prob>"
      << "<sd_minSnagBreakHeight>6</sd_minSnagBreakHeight>"
      << "<sd_maxSnagBreakHeight>6</sd_maxSnagBreakHeight>"
      << "</SnagDecayClassDynamics2>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteSnagDecompXMLErrorFile()
/////////////////////////////////////////////////////////////////////////////
const char* WriteSnagDecompXMLErrorFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut
  << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?><paramFile fileCode=\"06050101\">"
  << "<plot>"
  << "<timesteps>1</timesteps>"
  << "<randomSeed>0</randomSeed>"
  << "<yearsPerTimestep>5.0</yearsPerTimestep>"
  << "<plot_lenX>320.0</plot_lenX>"
  << "<plot_lenY>320.0</plot_lenY>"
  << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
  << "<plot_temp_C>12.88171785</plot_temp_C>"
  << "<plot_latitude>41.92</plot_latitude>"
  << "<plot_title>Default parameter file-use for testing only</plot_title>"
  << "</plot>"
  << "<trees>"
  << "<tr_speciesList>"
  << "<tr_species speciesName=\"ACSA\"/>"
  << "</tr_speciesList>"
  << "<tr_seedDiam10Cm>0.2</tr_seedDiam10Cm><tr_minAdultDBH><tr_madVal species=\"ACRU\">10.0</tr_madVal><tr_madVal species=\"ACSA\">10.0</tr_madVal><tr_madVal species=\"BEAL\">10.0</tr_madVal><tr_madVal species=\"FAGR\">10.0</tr_madVal><tr_madVal species=\"TSCA\">10.0</tr_madVal><tr_madVal species=\"FRAM\">10.0</tr_madVal><tr_madVal species=\"PIST\">10.0</tr_madVal><tr_madVal species=\"PRSE\">10.0</tr_madVal><tr_madVal species=\"QURU\">10.0</tr_madVal></tr_minAdultDBH><tr_maxSeedlingHeight><tr_mshVal species=\"ACRU\">1.35</tr_mshVal><tr_mshVal species=\"ACSA\">1.35</tr_mshVal><tr_mshVal species=\"BEAL\">1.35</tr_mshVal><tr_mshVal species=\"FAGR\">1.35</tr_mshVal><tr_mshVal species=\"TSCA\">1.35</tr_mshVal><tr_mshVal species=\"FRAM\">1.35</tr_mshVal><tr_mshVal species=\"PIST\">1.35</tr_mshVal><tr_mshVal species=\"PRSE\">1.35</tr_mshVal><tr_mshVal species=\"QURU\">1.35</tr_mshVal></tr_maxSeedlingHeight>"
  << "</trees>"
  << "<behaviorList>"
  << "<behavior>"
  << "<behaviorName>StochasticMortality</behaviorName>"
  << "<version>1.0</version>"
  << "<listPosition>1</listPosition>"
  << "<applyTo species=\"ACSA\" type=\"Adult\"/>"
  << "</behavior>"
  << "<behavior>"
  << "<behaviorName>SnagDecayClassDynamics</behaviorName>"
  << "<version>2.0</version>"
  << "<listPosition>2</listPosition>"
  << "<applyTo species=\"ACSA\" type=\"Snag\" />"
  << "</behavior>"
  << "<behavior>"
  << "<behaviorName>RemoveDead</behaviorName>"
  << "<version>1</version>"
  << "<listPosition>3</listPosition>"
  << "<applyTo species=\"ACSA\" type=\"Adult\"/>"
  << "</behavior>"
  << "</behaviorList>"
  << "<allometry>"
  << "<tr_whatAdultHeightDiam>"
  << "<tr_wahdVal species=\"ACSA\">0</tr_wahdVal>"
  << "</tr_whatAdultHeightDiam>"
  << "<tr_whatSaplingHeightDiam>"
  << "<tr_wsahdVal species=\"ACSA\">0</tr_wsahdVal>"
  << "</tr_whatSaplingHeightDiam>"
  << "<tr_whatSeedlingHeightDiam>"
  << "<tr_wsehdVal species=\"ACSA\">0</tr_wsehdVal>"
  << "</tr_whatSeedlingHeightDiam>"
  << "<tr_whatAdultCrownRadDiam>"
  << "<tr_wacrdVal species=\"ACSA\">0</tr_wacrdVal>"
  << "</tr_whatAdultCrownRadDiam>"
  << "<tr_whatSaplingCrownRadDiam>"
  << "<tr_wscrdVal species=\"ACSA\">0</tr_wscrdVal>"
  << "</tr_whatSaplingCrownRadDiam>"
  << "<tr_whatAdultCrownHeightHeight>"
  << "<tr_wachhVal species=\"ACSA\">0</tr_wachhVal>"
  << "</tr_whatAdultCrownHeightHeight>"
  << "<tr_whatSaplingCrownHeightHeight>"
  << "<tr_wschhVal species=\"ACSA\">0</tr_wschhVal>"
  << "</tr_whatSaplingCrownHeightHeight>"
  << "<tr_canopyHeight>"
  << "<tr_chVal species=\"ACSA\">24.8</tr_chVal>"
  << "</tr_canopyHeight>"
  << "<tr_stdAsympCrownRad>"
  << "<tr_sacrVal species=\"ACSA\">0.107</tr_sacrVal>"
  << "</tr_stdAsympCrownRad>"
  << "<tr_stdCrownRadExp>"
  << "<tr_screVal species=\"ACSA\">1.0</tr_screVal>"
  << "</tr_stdCrownRadExp>"
  << "<tr_stdMaxCrownRad>"
  << "<tr_smcrVal species=\"ACSA\">10</tr_smcrVal>"
  << "</tr_stdMaxCrownRad>"
  << "<tr_stdAsympCrownHt>"
  << "<tr_sachVal species=\"ACSA\">0.58</tr_sachVal>"
  << "</tr_stdAsympCrownHt>"
  << "<tr_stdCrownHtExp>"
  << "<tr_scheVal species=\"ACSA\">1.0</tr_scheVal>"
  << "</tr_stdCrownHtExp>"
  << "<tr_conversionDiam10ToDBH>"
  << "<tr_cdtdVal species=\"ACSA\">0.75</tr_cdtdVal>"
  << "</tr_conversionDiam10ToDBH>"
  << "<tr_interceptDiam10ToDBH>"
  << "<tr_idtdVal species=\"ACSA\">0.0</tr_idtdVal>"
  << "</tr_interceptDiam10ToDBH>"
  << "<tr_slopeOfAsymHeight>"
  << "<tr_soahVal species=\"ACSA\">0.062333334</tr_soahVal>"
  << "</tr_slopeOfAsymHeight>"
  << "<tr_slopeOfHeight-Diam10>"
  << "<tr_sohdVal species=\"ACSA\">0.03</tr_sohdVal>"
  << "</tr_slopeOfHeight-Diam10>"
  << "</allometry>"
  << "<StochasticMortality1>"
  << "<mo_stochasticMortRate>"
  << "<mo_smrVal species=\"ACSA\">1.0</mo_smrVal></mo_stochasticMortRate>"
  << "</StochasticMortality1>"
  << "<SnagDecayClassDynamics2>"
  << "<sd_snagDecompTreefallAlpha>-0.805</sd_snagDecompTreefallAlpha>"
  << "<sd_snagDecompTreefallBeta>"
  << "<sd_sdtbVal species=\"ACSA\">0.000</sd_sdtbVal>"
  << "</sd_snagDecompTreefallBeta>"
  << "<sd_snagDecompTreefallDelta>-0.016</sd_snagDecompTreefallDelta>"
  << "<sd_snagDecompTreefallTheta>-0.026</sd_snagDecompTreefallTheta>"
  << "<sd_snagDecompTreefallIota>3.389</sd_snagDecompTreefallIota>"
  << "<sd_snagDecompTreefallLambda>-0.084</sd_snagDecompTreefallLambda>"
  << "<sd_snagDecompSnagfallAlpha>5.691</sd_snagDecompSnagfallAlpha>"
  << "<sd_snagDecompSnagfallBeta>"
  << "<sd_sdsbVal species=\"ACSA\">0.000</sd_sdsbVal>"
  << "</sd_snagDecompSnagfallBeta>"
  << "<sd_snagDecompSnagfallGamma2>0.177</sd_snagDecompSnagfallGamma2>"
  << "<sd_snagDecompSnagfallGamma3>0.542</sd_snagDecompSnagfallGamma3>"
  << "<sd_snagDecompSnagfallGamma4>0.702</sd_snagDecompSnagfallGamma4>"
  << "<sd_snagDecompSnagfallGamma5>0.528</sd_snagDecompSnagfallGamma5>"
  << "<sd_snagDecompSnagfallZeta>-3.777</sd_snagDecompSnagfallZeta>"
  << "<sd_snagDecompSnagfallEta>0.531</sd_snagDecompSnagfallEta>"
  << "<sd_snagDecompSnagfallKappa>0.157</sd_snagDecompSnagfallKappa>"
  << "<sd_snagDecompLiveTo1Prob>0.290</sd_snagDecompLiveTo1Prob>"
  << "<sd_snagDecompLiveTo2Prob>0.229</sd_snagDecompLiveTo2Prob>"
  << "<sd_snagDecompLiveTo3Prob>0.196</sd_snagDecompLiveTo3Prob>"
  << "<sd_snagDecompLiveTo4Prob>0.124</sd_snagDecompLiveTo4Prob>"
  << "<sd_snagDecompLiveTo5Prob>0.161</sd_snagDecompLiveTo5Prob>"
  << "<sd_snagDecomp1To1Prob>-0.045</sd_snagDecomp1To1Prob>"
  << "<sd_snagDecomp1To2Prob>0.186</sd_snagDecomp1To2Prob>"
  << "<sd_snagDecomp1To3Prob>0.329</sd_snagDecomp1To3Prob>"
  << "<sd_snagDecomp1To4Prob>0.166</sd_snagDecomp1To4Prob>"
  << "<sd_snagDecomp1To5Prob>0.274</sd_snagDecomp1To5Prob>"
  << "<sd_snagDecomp2To2Prob>0.165</sd_snagDecomp2To2Prob>"
  << "<sd_snagDecomp2To3Prob>0.379</sd_snagDecomp2To3Prob>"
  << "<sd_snagDecomp2To4Prob>0.204</sd_snagDecomp2To4Prob>"
  << "<sd_snagDecomp2To5Prob>0.252</sd_snagDecomp2To5Prob>"
  << "<sd_snagDecomp3To3Prob>0.351</sd_snagDecomp3To3Prob>"
  << "<sd_snagDecomp3To4Prob>0.346</sd_snagDecomp3To4Prob>"
  << "<sd_snagDecomp3To5Prob>0.303</sd_snagDecomp3To5Prob>"
  << "<sd_snagDecomp4To4Prob>0.527</sd_snagDecomp4To4Prob>"
  << "<sd_snagDecomp4To5Prob>0.473</sd_snagDecomp4To5Prob>"
  << "<sd_snagDecomp5To5Prob>1.000</sd_snagDecomp5To5Prob>"
  << "<sd_minSnagBreakHeight>6</sd_minSnagBreakHeight>"
  << "<sd_maxSnagBreakHeight>6</sd_maxSnagBreakHeight>"
  << "</SnagDecayClassDynamics2>"
  << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteSnagDecompXMLErrorFile2()
// Snag decay class probabilities don't add up to 1.
/////////////////////////////////////////////////////////////////////////////
const char* WriteSnagDecompXMLErrorFile2() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut
  << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?><paramFile fileCode=\"06050101\">"
  << "<plot>"
  << "<timesteps>1</timesteps>"
  << "<randomSeed>0</randomSeed>"
  << "<yearsPerTimestep>5.0</yearsPerTimestep>"
  << "<plot_lenX>320.0</plot_lenX>"
  << "<plot_lenY>320.0</plot_lenY>"
  << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
  << "<plot_temp_C>12.88171785</plot_temp_C>"
  << "<plot_latitude>41.92</plot_latitude><plot_title>Default parameter file-use for testing only</plot_title>"
  << "</plot>"
  << "<trees>"
  << "<tr_speciesList>"
  << "<tr_species speciesName=\"ACSA\"/>"
  << "</tr_speciesList>"
  << "<tr_seedDiam10Cm>0.2</tr_seedDiam10Cm>"
  << "<tr_minAdultDBH>"
  << "<tr_madVal species=\"ACSA\">10.0</tr_madVal>"
  << "</tr_minAdultDBH>"
  << "<tr_maxSeedlingHeight>"
  << "<tr_mshVal species=\"ACSA\">1.35</tr_mshVal>"
  << "</tr_maxSeedlingHeight>"
  << "</trees>"
  << "<behaviorList>"
  << "<behavior>"
  << "<behaviorName>StochasticMortality</behaviorName>"
  << "<version>1.0</version>"
  << "<listPosition>1</listPosition>"
  << "<applyTo species=\"ACSA\" type=\"Adult\" />"
  << "</behavior>"
  << "<behavior>"
  << "<behaviorName>SnagDecayClassDynamics</behaviorName>"
  << "<version>2.0</version>"
  << "<listPosition>2</listPosition>"
  << "<applyTo species=\"ACSA\" type=\"Adult\" />"
  << "<applyTo species=\"ACSA\" type=\"Snag\" />"
  << "</behavior>"
  << "<behavior>"
  << "<behaviorName>RemoveDead</behaviorName>"
  << "<version>1</version>"
  << "<listPosition>3</listPosition>"
  << "<applyTo species=\"ACSA\" type=\"Adult\" />"
  << "<applyTo species=\"ACSA\" type=\"Snag\" />"
  << "</behavior>"
  << "</behaviorList>"
  << "<allometry>"
  << "<tr_whatAdultHeightDiam>"
  << "<tr_wahdVal species=\"ACSA\">0</tr_wahdVal>"
  << "</tr_whatAdultHeightDiam>"
  << "<tr_whatSaplingHeightDiam>"
  << "<tr_wsahdVal species=\"ACSA\">0</tr_wsahdVal>"
  << "</tr_whatSaplingHeightDiam>"
  << "<tr_whatSeedlingHeightDiam>"
  << "<tr_wsehdVal species=\"ACSA\">0</tr_wsehdVal>"
  << "</tr_whatSeedlingHeightDiam>"
  << "<tr_whatAdultCrownRadDiam>"
  << "<tr_wacrdVal species=\"ACSA\">0</tr_wacrdVal>"
  << "</tr_whatAdultCrownRadDiam>"
  << "<tr_whatSaplingCrownRadDiam>"
  << "<tr_wscrdVal species=\"ACSA\">0</tr_wscrdVal>"
  << "</tr_whatSaplingCrownRadDiam>"
  << "<tr_whatAdultCrownHeightHeight>"
  << "<tr_wachhVal species=\"ACSA\">0</tr_wachhVal>"
  << "</tr_whatAdultCrownHeightHeight>"
  << "<tr_whatSaplingCrownHeightHeight>"
  << "<tr_wschhVal species=\"ACSA\">0</tr_wschhVal>"
  << "</tr_whatSaplingCrownHeightHeight>"
  << "<tr_canopyHeight>"
  << "<tr_chVal species=\"ACSA\">24.8</tr_chVal>"
  << "</tr_canopyHeight>"
  << "<tr_stdAsympCrownRad>"
  << "<tr_sacrVal species=\"ACSA\">0.107</tr_sacrVal>"
  << "</tr_stdAsympCrownRad>"
  << "<tr_stdCrownRadExp>"
  << "<tr_screVal species=\"ACSA\">1.0</tr_screVal>"
  << "</tr_stdCrownRadExp>"
  << "<tr_stdMaxCrownRad>"
  << "<tr_smcrVal species=\"ACSA\">10</tr_smcrVal>"
  << "</tr_stdMaxCrownRad>"
  << "<tr_stdAsympCrownHt>"
  << "<tr_sachVal species=\"ACSA\">0.58</tr_sachVal>"
  << "</tr_stdAsympCrownHt>"
  << "<tr_stdCrownHtExp>"
  << "<tr_scheVal species=\"ACSA\">1.0</tr_scheVal>"
  << "</tr_stdCrownHtExp>"
  << "<tr_conversionDiam10ToDBH>"
  << "<tr_cdtdVal species=\"ACSA\">0.75</tr_cdtdVal>"
  << "</tr_conversionDiam10ToDBH>"
  << "<tr_interceptDiam10ToDBH>"
  << "<tr_idtdVal species=\"ACSA\">0.0</tr_idtdVal>"
  << "</tr_interceptDiam10ToDBH>"
  << "<tr_slopeOfAsymHeight>"
  << "<tr_soahVal species=\"ACSA\">0.062333334</tr_soahVal>"
  << "</tr_slopeOfAsymHeight>"
  << "<tr_slopeOfHeight-Diam10>"
  << "<tr_sohdVal species=\"ACSA\">0.03</tr_sohdVal>"
  << "</tr_slopeOfHeight-Diam10>"
  << "</allometry>"
  << "<StochasticMortality1>"
  << "<mo_stochasticMortRate>"
  << "<mo_smrVal species=\"ACSA\">1.0</mo_smrVal>"
  << "</mo_stochasticMortRate>"
  << "</StochasticMortality1>"
  << "<SnagDecayClassDynamics2>"
  << "<sd_snagDecompTreefallAlpha>-0.805</sd_snagDecompTreefallAlpha>"
  << "<sd_snagDecompTreefallBeta>"
  << "<sd_sdtbVal species=\"ACSA\">0.000</sd_sdtbVal>"
  << "</sd_snagDecompTreefallBeta>"
  << "<sd_snagDecompTreefallDelta>-0.016</sd_snagDecompTreefallDelta>"
  << "<sd_snagDecompTreefallTheta>-0.026</sd_snagDecompTreefallTheta>"
  << "<sd_snagDecompTreefallIota>3.389</sd_snagDecompTreefallIota>"
  << "<sd_snagDecompTreefallLambda>-0.084</sd_snagDecompTreefallLambda>"
  << "<sd_snagDecompSnagfallAlpha>5.691</sd_snagDecompSnagfallAlpha>"
  << "<sd_snagDecompSnagfallBeta>"
  << "<sd_sdsbVal species=\"ACSA\">0.000</sd_sdsbVal>"
  << "</sd_snagDecompSnagfallBeta>"
  << "<sd_snagDecompSnagfallGamma2>0.177</sd_snagDecompSnagfallGamma2>"
  << "<sd_snagDecompSnagfallGamma3>0.542</sd_snagDecompSnagfallGamma3>"
  << "<sd_snagDecompSnagfallGamma4>0.702</sd_snagDecompSnagfallGamma4>"
  << "<sd_snagDecompSnagfallGamma5>0.528</sd_snagDecompSnagfallGamma5>"
  << "<sd_snagDecompSnagfallZeta>-3.777</sd_snagDecompSnagfallZeta>"
  << "<sd_snagDecompSnagfallEta>0.531</sd_snagDecompSnagfallEta>"
  << "<sd_snagDecompSnagfallKappa>0.157</sd_snagDecompSnagfallKappa>"
  << "<sd_snagDecompLiveTo1Prob>0.290</sd_snagDecompLiveTo1Prob>"
  << "<sd_snagDecompLiveTo2Prob>0.229</sd_snagDecompLiveTo2Prob>"
  << "<sd_snagDecompLiveTo3Prob>0.196</sd_snagDecompLiveTo3Prob>"
  << "<sd_snagDecompLiveTo4Prob>0.124</sd_snagDecompLiveTo4Prob>"
  << "<sd_snagDecompLiveTo5Prob>0.161</sd_snagDecompLiveTo5Prob>"
  << "<sd_snagDecomp1To1Prob>0.045</sd_snagDecomp1To1Prob>"
  << "<sd_snagDecomp1To2Prob>0.186</sd_snagDecomp1To2Prob>"
  << "<sd_snagDecomp1To3Prob>0.329</sd_snagDecomp1To3Prob>"
  << "<sd_snagDecomp1To4Prob>0.166</sd_snagDecomp1To4Prob>"
  << "<sd_snagDecomp1To5Prob>0.274</sd_snagDecomp1To5Prob>"
  << "<sd_snagDecomp2To2Prob>0.165</sd_snagDecomp2To2Prob>"
  << "<sd_snagDecomp2To3Prob>0.279</sd_snagDecomp2To3Prob>"
  << "<sd_snagDecomp2To4Prob>0.204</sd_snagDecomp2To4Prob>"
  << "<sd_snagDecomp2To5Prob>0.252</sd_snagDecomp2To5Prob>"
  << "<sd_snagDecomp3To3Prob>0.351</sd_snagDecomp3To3Prob>"
  << "<sd_snagDecomp3To4Prob>0.346</sd_snagDecomp3To4Prob>"
  << "<sd_snagDecomp3To5Prob>0.303</sd_snagDecomp3To5Prob>"
  << "<sd_snagDecomp4To4Prob>0.527</sd_snagDecomp4To4Prob>"
  << "<sd_snagDecomp4To5Prob>0.473</sd_snagDecomp4To5Prob>"
  << "<sd_snagDecomp5To5Prob>1.000</sd_snagDecomp5To5Prob>"
  << "<sd_minSnagBreakHeight>6</sd_minSnagBreakHeight>"
  << "<sd_maxSnagBreakHeight>6</sd_maxSnagBreakHeight>"
  << "</SnagDecayClassDynamics2>"
  << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteSnagsInitFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteSnagsInitFile1()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

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
      << "</plot>";

  oOut << "<trees>"
      << "<tr_speciesList>"
      << "<tr_species speciesName=\"Species_1\"/>"
      << "<tr_species speciesName=\"Species_2\"/>"
      << "<tr_species speciesName=\"Species_3\"/>"
      << "</tr_speciesList>"
      << "<tr_sizeClasses>"
      << "<tr_sizeClass sizeKey=\"s10.0\" />"
      << "<tr_sizeClass sizeKey=\"s15.0\" />"
      << "<tr_sizeClass sizeKey=\"s20.0\" />"
      << "<tr_sizeClass sizeKey=\"s35.0\" />"
      << "</tr_sizeClasses>"
      << "<tr_initialDensities>"
      << "<tr_idVals whatSpecies=\"Species_1\">"
      << "<tr_initialDensity sizeClass=\"s10.0\">0.0</tr_initialDensity>"
      << "<tr_initialDensity sizeClass=\"s15.0\">15.0</tr_initialDensity>"
      << "<tr_initialDensity sizeClass=\"s35.0\">30.0</tr_initialDensity>"
      << "</tr_idVals>"
      << "<tr_idVals whatSpecies=\"Species_2\">"
      << "<tr_initialDensity sizeClass=\"s10.0\">5.0</tr_initialDensity>"
      << "<tr_initialDensity sizeClass=\"s15.0\">20.0</tr_initialDensity>"
      << "<tr_initialDensity sizeClass=\"s35.0\">35.0</tr_initialDensity>"
      << "</tr_idVals>"
      << "<tr_idVals whatSpecies=\"Species_3\">"
      << "<tr_initialDensity sizeClass=\"s10.0\">10.0</tr_initialDensity>"
      << "<tr_initialDensity sizeClass=\"s15.0\">25.0</tr_initialDensity>"
      << "<tr_initialDensity sizeClass=\"s35.0\">40.0</tr_initialDensity>"
      << "</tr_idVals>"
      << "</tr_initialDensities>"
      << "<tr_snagInitialDensities>"
      << "<tr_sidVals whatSpecies=\"Species_1\">"
      << "<tr_snagInitialDensity sizeClass=\"s10.0\">0.0</tr_snagInitialDensity>"
      << "<tr_snagInitialDensity sizeClass=\"s15.0\">25.0</tr_snagInitialDensity>"
      << "<tr_snagInitialDensity sizeClass=\"s35.0\">40.0</tr_snagInitialDensity>"
      << "</tr_sidVals>"
      << "<tr_sidVals whatSpecies=\"Species_2\">"
      << "<tr_snagInitialDensity sizeClass=\"s10.0\">15.0</tr_snagInitialDensity>"
      << "<tr_snagInitialDensity sizeClass=\"s15.0\">30.0</tr_snagInitialDensity>"
      << "<tr_snagInitialDensity sizeClass=\"s35.0\">0.0</tr_snagInitialDensity>"
      << "</tr_sidVals>"
      << "<tr_sidVals whatSpecies=\"Species_3\">"
      << "<tr_snagInitialDensity sizeClass=\"s10.0\">20.0</tr_snagInitialDensity>"
      << "<tr_snagInitialDensity sizeClass=\"s15.0\">35.0</tr_snagInitialDensity>"
      << "<tr_snagInitialDensity sizeClass=\"s35.0\">50.0</tr_snagInitialDensity>"
      << "</tr_sidVals>"
      << "</tr_snagInitialDensities>";

  WriteTreePopulationCommonStuff(oOut);

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>StochasticMortality</behaviorName>"
      << "<version>1</version>"
      << "<applyTo species=\"Species_1\" type=\"Adult\" />"
      << "<applyTo species=\"Species_1\" type=\"Snag\" />"
      << "<applyTo species=\"Species_2\" type=\"Adult\" />"
      << "<applyTo species=\"Species_2\" type=\"Snag\" />"
      << "<applyTo species=\"Species_3\" type=\"Adult\" />"
      << "<applyTo species=\"Species_3\" type=\"Snag\" />"
      << "<listPosition>1</listPosition>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>SnagDecayClassDynamics</behaviorName>"
      << "<version>2.0</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\" />"
      << "<applyTo species=\"Species_1\" type=\"Snag\" />"
      << "<applyTo species=\"Species_2\" type=\"Adult\" />"
      << "<applyTo species=\"Species_2\" type=\"Snag\" />"
      << "<applyTo species=\"Species_3\" type=\"Adult\" />"
      << "<applyTo species=\"Species_3\" type=\"Snag\" />"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>RemoveDead</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>3</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\" />"
      << "<applyTo species=\"Species_1\" type=\"Snag\" />"
      << "<applyTo species=\"Species_2\" type=\"Adult\" />"
      << "<applyTo species=\"Species_2\" type=\"Snag\" />"
      << "<applyTo species=\"Species_3\" type=\"Adult\" />"
      << "<applyTo species=\"Species_3\" type=\"Snag\" />"
      << "</behavior>"
      << "</behaviorList>"
      << "<StochasticMortality1>"
      << "<mo_stochasticMortRate>"
      << "<mo_smrVal species=\"Species_1\">0.0</mo_smrVal>"
      << "<mo_smrVal species=\"Species_2\">0.0</mo_smrVal>"
      << "<mo_smrVal species=\"Species_3\">0.0</mo_smrVal>"
      << "</mo_stochasticMortRate>"
      << "</StochasticMortality1>";

  WriteSnagParsCommonStuff(oOut);
  oOut << "</SnagDecayClassDynamics2>"
      << "</paramFile>";


  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteSnagsInitFile2()
/////////////////////////////////////////////////////////////////////////////
const char* WriteSnagsInitFile2()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">"
      << "<plot>"
      << "<timesteps>1</timesteps>"
      << "<yearsPerTimestep>1</yearsPerTimestep>"
      << "<randomSeed>1</randomSeed>"
      << "<plot_lenX>100.0</plot_lenX>"
      << "<plot_lenY>100.0</plot_lenY>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88171785</plot_temp_C>"
      << "<plot_latitude>55.37</plot_latitude>"
      << "</plot>";

  oOut << "<trees>"
      << "<tr_speciesList>"
      << "<tr_species speciesName=\"Species_1\"/>"
      << "<tr_species speciesName=\"Species_2\"/>"
      << "<tr_species speciesName=\"Species_3\"/>"
      << "</tr_speciesList>"
      << "<tr_sizeClasses>"
      << "<tr_sizeClass sizeKey=\"s10.0\" />"
      << "<tr_sizeClass sizeKey=\"s15.0\" />"
      << "<tr_sizeClass sizeKey=\"s20.0\" />"
      << "<tr_sizeClass sizeKey=\"s35.0\" />"
      << "</tr_sizeClasses>"
      << "<tr_initialDensities>"
      << "<tr_idVals whatSpecies=\"Species_1\">"
      << "<tr_initialDensity sizeClass=\"s10.0\">0.0</tr_initialDensity>"
      << "<tr_initialDensity sizeClass=\"s15.0\">15.0</tr_initialDensity>"
      << "<tr_initialDensity sizeClass=\"s35.0\">30.0</tr_initialDensity>"
      << "</tr_idVals>"
      << "<tr_idVals whatSpecies=\"Species_2\">"
      << "<tr_initialDensity sizeClass=\"s10.0\">5.0</tr_initialDensity>"
      << "<tr_initialDensity sizeClass=\"s15.0\">20.0</tr_initialDensity>"
      << "<tr_initialDensity sizeClass=\"s35.0\">35.0</tr_initialDensity>"
      << "</tr_idVals>"
      << "<tr_idVals whatSpecies=\"Species_3\">"
      << "<tr_initialDensity sizeClass=\"s10.0\">10.0</tr_initialDensity>"
      << "<tr_initialDensity sizeClass=\"s15.0\">25.0</tr_initialDensity>"
      << "<tr_initialDensity sizeClass=\"s35.0\">40.0</tr_initialDensity>"
      << "</tr_idVals>"
      << "</tr_initialDensities>"
      << "<tr_snagInitialDensities>"
      << "<tr_sidVals whatSpecies=\"Species_1\">"
      << "<tr_snagInitialDensity sizeClass=\"s15.0\">1000.0</tr_snagInitialDensity>"
      << "<tr_snagInitialDensity sizeClass=\"s35.0\">1000.0</tr_snagInitialDensity>"
      << "</tr_sidVals>"
      << "<tr_sidVals whatSpecies=\"Species_2\">"
      << "<tr_snagInitialDensity sizeClass=\"s15.0\">1000.0</tr_snagInitialDensity>"
      << "<tr_snagInitialDensity sizeClass=\"s35.0\">1000.0</tr_snagInitialDensity>"
      << "</tr_sidVals>"
      << "<tr_sidVals whatSpecies=\"Species_3\">"
      << "<tr_snagInitialDensity sizeClass=\"s15.0\">1000.0</tr_snagInitialDensity>"
      << "<tr_snagInitialDensity sizeClass=\"s35.0\">1000.0</tr_snagInitialDensity>"
      << "</tr_sidVals>"
      << "</tr_snagInitialDensities>";

  WriteTreePopulationCommonStuff(oOut);

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>StochasticMortality</behaviorName>"
      << "<version>1</version>"
      << "<applyTo species=\"Species_1\" type=\"Adult\" />"
      << "<applyTo species=\"Species_1\" type=\"Snag\" />"
      << "<applyTo species=\"Species_2\" type=\"Adult\" />"
      << "<applyTo species=\"Species_2\" type=\"Snag\" />"
      << "<applyTo species=\"Species_3\" type=\"Adult\" />"
      << "<applyTo species=\"Species_3\" type=\"Snag\" />"
      << "<listPosition>1</listPosition>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>SnagDecayClassDynamics</behaviorName>"
      << "<version>2.0</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\" />"
      << "<applyTo species=\"Species_1\" type=\"Snag\" />"
      << "<applyTo species=\"Species_2\" type=\"Adult\" />"
      << "<applyTo species=\"Species_2\" type=\"Snag\" />"
      << "<applyTo species=\"Species_3\" type=\"Adult\" />"
      << "<applyTo species=\"Species_3\" type=\"Snag\" />"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>RemoveDead</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>3</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\" />"
      << "<applyTo species=\"Species_1\" type=\"Snag\" />"
      << "<applyTo species=\"Species_2\" type=\"Adult\" />"
      << "<applyTo species=\"Species_2\" type=\"Snag\" />"
      << "<applyTo species=\"Species_3\" type=\"Adult\" />"
      << "<applyTo species=\"Species_3\" type=\"Snag\" />"
      << "</behavior>"
      << "</behaviorList>"
      << "<StochasticMortality1>"
      << "<mo_stochasticMortRate>"
      << "<mo_smrVal species=\"Species_1\">0.0</mo_smrVal>"
      << "<mo_smrVal species=\"Species_2\">0.0</mo_smrVal>"
      << "<mo_smrVal species=\"Species_3\">0.0</mo_smrVal>"
      << "</mo_stochasticMortRate>"
      << "</StochasticMortality1>";

  WriteSnagParsCommonStuff(oOut);

  oOut << "<sd_snagDecompInitialClasses>"
       << "<sd_idVals whatSpecies=\"Species_1\" whatSizeClass=\"s15.0\">"
       << "<sd_id decayClass=\"1\">1.0</sd_id>"
       << "<sd_id decayClass=\"2\">0.0</sd_id>"
       << "<sd_id decayClass=\"3\">0.0</sd_id>"
       << "<sd_id decayClass=\"4\">0.0</sd_id>"
       << "<sd_id decayClass=\"5\">0.0</sd_id>"
       << "</sd_idVals>"
       << "<sd_idVals whatSpecies=\"Species_1\" whatSizeClass=\"s35.0\">"
       << "<sd_id decayClass=\"1\">0.0</sd_id>"
       << "<sd_id decayClass=\"2\">1.0</sd_id>"
       << "<sd_id decayClass=\"3\">0.0</sd_id>"
       << "<sd_id decayClass=\"4\">0.0</sd_id>"
       << "<sd_id decayClass=\"5\">0.0</sd_id>"
       << "</sd_idVals>"
       << "<sd_idVals whatSpecies=\"Species_2\" whatSizeClass=\"s15.0\">"
       << "<sd_id decayClass=\"1\">0.0</sd_id>"
       << "<sd_id decayClass=\"2\">0.0</sd_id>"
       << "<sd_id decayClass=\"3\">1.0</sd_id>"
       << "<sd_id decayClass=\"4\">0.0</sd_id>"
       << "<sd_id decayClass=\"5\">0.0</sd_id>"
       << "</sd_idVals>"
       << "<sd_idVals whatSpecies=\"Species_2\" whatSizeClass=\"s35.0\">"
       << "<sd_id decayClass=\"1\">0.0</sd_id>"
       << "<sd_id decayClass=\"2\">0.0</sd_id>"
       << "<sd_id decayClass=\"3\">0.0</sd_id>"
       << "<sd_id decayClass=\"4\">1.0</sd_id>"
       << "<sd_id decayClass=\"5\">0.0</sd_id>"
       << "</sd_idVals>"
       << "<sd_idVals whatSpecies=\"Species_3\" whatSizeClass=\"s15.0\">"
       << "<sd_id decayClass=\"1\">0.0</sd_id>"
       << "<sd_id decayClass=\"2\">0.0</sd_id>"
       << "<sd_id decayClass=\"3\">0.0</sd_id>"
       << "<sd_id decayClass=\"4\">0.0</sd_id>"
       << "<sd_id decayClass=\"5\">1.0</sd_id>"
       << "</sd_idVals>"
       << "<sd_idVals whatSpecies=\"Species_3\" whatSizeClass=\"s35.0\">"
       << "<sd_id decayClass=\"1\">0.25</sd_id>"
       << "<sd_id decayClass=\"2\">0.31</sd_id>"
       << "<sd_id decayClass=\"3\">0.18</sd_id>"
       << "<sd_id decayClass=\"4\">0.22</sd_id>"
       << "<sd_id decayClass=\"5\">0.04</sd_id>"
       << "</sd_idVals>"
       << "</sd_snagDecompInitialClasses>";
  oOut << "</SnagDecayClassDynamics2>"
       << "</paramFile>";


  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteTreePopulationCommonStuff()
/////////////////////////////////////////////////////////////////////////////
void WriteTreePopulationCommonStuff( std::fstream &oOut )
{
  using namespace std;
  oOut << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
      << "<tr_minAdultDBH>"
      << "<tr_madVal species=\"Species_1\">10</tr_madVal>"
      << "<tr_madVal species=\"Species_2\">10</tr_madVal>"
      << "<tr_madVal species=\"Species_3\">10</tr_madVal>"
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
      << "<tr_screVal species=\"Species_1\">0.9</tr_screVal>"
      << "<tr_screVal species=\"Species_2\">0.9</tr_screVal>"
      << "<tr_screVal species=\"Species_3\">0.9</tr_screVal>"
      << "</tr_stdCrownRadExp>"
      << "<tr_stdMaxCrownRad>"
      << "<tr_smcrVal species=\"Species_1\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Species_2\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Species_3\">10</tr_smcrVal>"
      << "</tr_stdMaxCrownRad>"
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
      << "<tr_scheVal species=\"Species_1\">1</tr_scheVal>"
      << "<tr_scheVal species=\"Species_2\">1</tr_scheVal>"
      << "<tr_scheVal species=\"Species_3\">1</tr_scheVal>"
      << "</tr_stdCrownHtExp>"
      << "<tr_slopeOfHeight-Diam10>"
      << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_2\">0.03418</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_3\">0.03418</tr_sohdVal>"
      << "</tr_slopeOfHeight-Diam10>"
      << "<tr_slopeOfAsymHeight>"
      << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
      << "<tr_soahVal species=\"Species_2\">0.0299</tr_soahVal>"
      << "<tr_soahVal species=\"Species_3\">0.0299</tr_soahVal>"
      << "</tr_slopeOfAsymHeight>"
      << "<tr_maxSeedlingHeight>"
      << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Species_2\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Species_3\">1.35</tr_mshVal>"
      << "</tr_maxSeedlingHeight>"
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
}


/////////////////////////////////////////////////////////////////////////////
// WriteSnagParsCommonStuff()
/////////////////////////////////////////////////////////////////////////////
void WriteSnagParsCommonStuff( std::fstream &oOut )
{
  using namespace std;
  oOut << "<SnagDecayClassDynamics2>"
      << "<sd_snagDecompTreefallAlpha>-0.805</sd_snagDecompTreefallAlpha>"
      << "<sd_snagDecompTreefallBeta>"
      << "<sd_sdtbVal species=\"Species_1\">0.000</sd_sdtbVal>"
      << "<sd_sdtbVal species=\"Species_2\">0.000</sd_sdtbVal>"
      << "<sd_sdtbVal species=\"Species_3\">0.000</sd_sdtbVal>"
      << "</sd_snagDecompTreefallBeta>"
      << "<sd_snagDecompTreefallDelta>-0.016</sd_snagDecompTreefallDelta>"
      << "<sd_snagDecompTreefallTheta>-0.026</sd_snagDecompTreefallTheta>"
      << "<sd_snagDecompTreefallIota>3.389</sd_snagDecompTreefallIota>"
      << "<sd_snagDecompTreefallLambda>-0.084</sd_snagDecompTreefallLambda>"
      << "<sd_snagDecompSnagfallAlpha>5.691</sd_snagDecompSnagfallAlpha>"
      << "<sd_snagDecompSnagfallBeta>"
      << "<sd_sdsbVal species=\"Species_1\">0.000</sd_sdsbVal>"
      << "<sd_sdsbVal species=\"Species_2\">0.000</sd_sdsbVal>"
      << "<sd_sdsbVal species=\"Species_3\">0.000</sd_sdsbVal>"
      << "</sd_snagDecompSnagfallBeta>"
      << "<sd_snagDecompSnagfallGamma2>0.177</sd_snagDecompSnagfallGamma2>"
      << "<sd_snagDecompSnagfallGamma3>0.542</sd_snagDecompSnagfallGamma3>"
      << "<sd_snagDecompSnagfallGamma4>0.702</sd_snagDecompSnagfallGamma4>"
      << "<sd_snagDecompSnagfallGamma5>0.528</sd_snagDecompSnagfallGamma5>"
      << "<sd_snagDecompSnagfallZeta>-3.777</sd_snagDecompSnagfallZeta>"
      << "<sd_snagDecompSnagfallEta>0.531</sd_snagDecompSnagfallEta>"
      << "<sd_snagDecompSnagfallKappa>0.157</sd_snagDecompSnagfallKappa>"
      << "<sd_snagDecompLiveTo1Prob>0.290</sd_snagDecompLiveTo1Prob>"
      << "<sd_snagDecompLiveTo2Prob>0.229</sd_snagDecompLiveTo2Prob>"
      << "<sd_snagDecompLiveTo3Prob>0.196</sd_snagDecompLiveTo3Prob>"
      << "<sd_snagDecompLiveTo4Prob>0.124</sd_snagDecompLiveTo4Prob>"
      << "<sd_snagDecompLiveTo5Prob>0.161</sd_snagDecompLiveTo5Prob>"
      << "<sd_snagDecomp1To1Prob>0.045</sd_snagDecomp1To1Prob>"
      << "<sd_snagDecomp1To2Prob>0.186</sd_snagDecomp1To2Prob>"
      << "<sd_snagDecomp1To3Prob>0.329</sd_snagDecomp1To3Prob>"
      << "<sd_snagDecomp1To4Prob>0.166</sd_snagDecomp1To4Prob>"
      << "<sd_snagDecomp1To5Prob>0.274</sd_snagDecomp1To5Prob>"
      << "<sd_snagDecomp2To2Prob>0.165</sd_snagDecomp2To2Prob>"
      << "<sd_snagDecomp2To3Prob>0.379</sd_snagDecomp2To3Prob>"
      << "<sd_snagDecomp2To4Prob>0.204</sd_snagDecomp2To4Prob>"
      << "<sd_snagDecomp2To5Prob>0.252</sd_snagDecomp2To5Prob>"
      << "<sd_snagDecomp3To3Prob>0.351</sd_snagDecomp3To3Prob>"
      << "<sd_snagDecomp3To4Prob>0.346</sd_snagDecomp3To4Prob>"
      << "<sd_snagDecomp3To5Prob>0.303</sd_snagDecomp3To5Prob>"
      << "<sd_snagDecomp4To4Prob>0.527</sd_snagDecomp4To4Prob>"
      << "<sd_snagDecomp4To5Prob>0.473</sd_snagDecomp4To5Prob>"
      << "<sd_snagDecomp5To5Prob>1.000</sd_snagDecomp5To5Prob>"
      << "<sd_minSnagBreakHeight>6</sd_minSnagBreakHeight>"
      << "<sd_maxSnagBreakHeight>6</sd_maxSnagBreakHeight>";
}
