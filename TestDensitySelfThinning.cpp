//---------------------------------------------------------------------------
// TestDensitySelfThinning.cpp
//---------------------------------------------------------------------------
#include "TestDensitySelfThinning.h"
#include <gtest/gtest.h>
#include "SimManager.h"
#include "TreePopulation.h"
#include "BehaviorBase.h"
#include <fstream>
#include <math.h>

/////////////////////////////////////////////////////////////////////////////
// TestNormalProcessing()
/////////////////////////////////////////////////////////////////////////////
TEST(DensitySelfThinning, TestNormalProcessing) {
  clPopulationBase * p_oTemp;
  clTreePopulation * p_oPop;
  clTreeSearch *p_oAllTrees;
  clTree *p_oTree;

  float fDiam;
  int **p_iTreeCount;
  int i, j, iNumSpecies, iNumTypes;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    // Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteDensitySelfThinningXMLFile1() );
    p_oTemp = p_oSimManager->GetPopulationObject( "treepopulation" );
    p_oPop = ( clTreePopulation * ) p_oTemp;
    iNumSpecies = p_oPop->GetNumberOfSpecies();
    iNumTypes = p_oPop->GetNumberOfTypes();

    // Set up our tree count array
    p_iTreeCount = new int*[iNumSpecies];
    for (i = 0; i < iNumSpecies; i++) {
      p_iTreeCount[i] = new int[iNumTypes];
      for (j = 0; j < iNumTypes; j++) {
        p_iTreeCount[i][j] = 0;
      }
    }
    // Create 100 of each kind of tree affected by mortality
    // Seedlings of Species 1
    fDiam = 0.01;
    for (i = 0; i < 100; i++)
      p_oTree = p_oPop->CreateTree(1, 1, 0, clTreePopulation::seedling, fDiam);

    // Saplings of Species 1
    fDiam = 2.2;
    for (i = 0; i < 100; i++)
      p_oTree = p_oPop->CreateTree(1, 1, 0, clTreePopulation::sapling, fDiam);

    // Initial conditions count
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_iTreeCount[p_oTree->GetSpecies()][p_oTree->GetType()]++;
      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(p_iTreeCount[0][clTreePopulation::seedling], 100);
    EXPECT_EQ(p_iTreeCount[0][clTreePopulation::sapling], 100);

    // Run for one timestep
    p_oSimManager->RunSim(1);


    // Count the remaining trees
    for (i = 0; i < iNumSpecies; i++) {
      for (j = 0; j < iNumTypes; j++) {
        p_iTreeCount[i][j] = 0;
      }
    }
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_iTreeCount[p_oTree->GetSpecies()][p_oTree->GetType()]++;
      p_oTree = p_oAllTrees->NextTree();
    }

    // Make sure they are as expected
    // Seedlings of Species 1
    ASSERT_TRUE((p_iTreeCount[0][clTreePopulation::seedling] >= 89) && (p_iTreeCount[0][clTreePopulation::seedling] <= 100)  );
    // Saplings of Species 1
    ASSERT_TRUE((p_iTreeCount[0][clTreePopulation::sapling] >= 89) && (p_iTreeCount[0][clTreePopulation::sapling] <= 100));

    for (i = 0; i < iNumSpecies; i++) delete[] p_iTreeCount[i];
    delete[] p_iTreeCount;
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete[] p_iTreeCount;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestErrorProcessing()
/////////////////////////////////////////////////////////////////////////////
TEST(DensitySelfThinning, TestErrorProcessing) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try
  {
    p_oSimManager->ReadFile (WriteDensitySelfThinningXMLErrorFile1());
    FAIL() << "TestDensitySelfThinning error processing didn't catch error for WriteDensitySelfThinningXMLErrorFile1.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clDensitySelfThinning::DoShellSetup" ) != 0)
    {
      FAIL() << "TestDensitySelfThinning error processing caught the wrong error for WriteDensitySelfThinningXMLErrorFile1.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile (WriteDensitySelfThinningXMLErrorFile2());
    FAIL() << "TestDensitySelfThinning error processing didn't catch error for WriteDensitySelfThinningXMLErrorFile2.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clDensitySelfThinning::DoShellSetup" ) != 0)
    {
      FAIL() << "TestDensitySelfThinning error processing caught the wrong error for WriteDensitySelfThinningXMLErrorFile2.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile (WriteDensitySelfThinningXMLErrorFile3());
    FAIL() << "TestDensitySelfThinning error processing didn't catch error for WriteDensitySelfThinningXMLErrorFile3.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clDensitySelfThinning::DoShellSetup" ) != 0)
    {
      FAIL() << "TestDensitySelfThinning error processing caught the wrong error for WriteDensitySelfThinningXMLErrorFile3.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile (WriteDensitySelfThinningXMLErrorFile4());
    FAIL() << "TestDensitySelfThinning error processing didn't catch error for WriteDensitySelfThinningXMLErrorFile4.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clDensitySelfThinning::DoShellSetup" ) != 0)
    {
      FAIL() << "TestDensitySelfThinning error processing caught the wrong error for WriteDensitySelfThinningXMLErrorFile4.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile (WriteDensitySelfThinningXMLErrorFile5());
    FAIL() << "TestDensitySelfThinning error processing didn't catch error for WriteDensitySelfThinningXMLErrorFile5.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clDensitySelfThinning::DoShellSetup" ) != 0)
    {
      FAIL() << "TestDensitySelfThinning error processing caught the wrong error for WriteDensitySelfThinningXMLErrorFile5.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile (WriteDensitySelfThinningXMLErrorFile6());
    FAIL() << "TestDensitySelfThinning error processing didn't catch error for WriteDensitySelfThinningXMLErrorFile6.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clDensitySelfThinning::DoShellSetup" ) != 0)
    {
      FAIL() << "TestDensitySelfThinning error processing caught the wrong error for WriteDensitySelfThinningXMLErrorFile6.";
    }
    ;
  }
  delete p_oSimManager;
}

/////////////////////////////////////////////////////////////////////////////
// WriteDensitySelfThinningXMLFile1()
// Good parameter file
/////////////////////////////////////////////////////////////////////////////
const char* WriteDensitySelfThinningXMLFile1()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">"
      << "<plot>"
      << "<timesteps>2</timesteps>"
      << "<rt_timestep>0</rt_timestep>"
      << "<randomSeed>1</randomSeed>"
      << "<yearsPerTimestep>1.0</yearsPerTimestep>"
      << "<plot_lenX>100.0</plot_lenX>"
      << "<plot_lenY>100.0</plot_lenY>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88171785</plot_temp_C>"
      << "<plot_latitude>0.0</plot_latitude>"
      << "</plot>"
      << "<trees>"
      << "<tr_speciesList>"
      << "<tr_species speciesName=\"Species_1\" />"
      << "</tr_speciesList>"
      << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
      << "<tr_minAdultDBH>"
      << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
      << "</tr_minAdultDBH>"
      << "<tr_maxSeedlingHeight>"
      << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
      << "</tr_maxSeedlingHeight>"
      << "</trees>"
      << "<allometry>"
      << "<tr_canopyHeight>"
      << "<tr_chVal species=\"Species_1\">40.0</tr_chVal>"
      << "</tr_canopyHeight>"
      << "<tr_stdAsympCrownRad>"
      << "<tr_sacrVal species=\"Species_1\">0.7</tr_sacrVal>"
      << "</tr_stdAsympCrownRad>"
      << "<tr_stdCrownRadExp>"
      << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
      << "</tr_stdCrownRadExp>"
      << "<tr_conversionDiam10ToDBH>"
      << "<tr_cdtdVal species=\"Species_1\">0.7</tr_cdtdVal>"
      << "</tr_conversionDiam10ToDBH>"
      << "<tr_interceptDiam10ToDBH>"
      << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
      << "</tr_interceptDiam10ToDBH>"
      << "<tr_stdAsympCrownHt>"
      << "<tr_sachVal species=\"Species_1\">0.7</tr_sachVal>"
      << "</tr_stdAsympCrownHt>"
      << "<tr_stdCrownHtExp>"
      << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
      << "</tr_stdCrownHtExp>"
      << "<tr_slopeOfHeight-Diam10>"
      << "<tr_sohdVal species=\"Species_1\">0.03</tr_sohdVal>"
      << "</tr_slopeOfHeight-Diam10>"
      << "<tr_slopeOfAsymHeight>"
      << "<tr_soahVal species=\"Species_1\">0.7</tr_soahVal>"
      << "</tr_slopeOfAsymHeight>"
      << "<tr_whatSeedlingHeightDiam>"
      << "<tr_wsehdVal species=\"Species_1\">0</tr_wsehdVal>"
      << "</tr_whatSeedlingHeightDiam>"
      << "<tr_whatSaplingHeightDiam>"
      << "<tr_wsahdVal species=\"Species_1\">0</tr_wsahdVal>"
      << "</tr_whatSaplingHeightDiam>"
      << "<tr_whatAdultHeightDiam>"
      << "<tr_wahdVal species=\"Species_1\">0</tr_wahdVal>"
      << "</tr_whatAdultHeightDiam>"
      << "<tr_whatAdultCrownRadDiam>"
      << "<tr_wacrdVal species=\"Species_1\">0</tr_wacrdVal>"
      << "</tr_whatAdultCrownRadDiam>"
      << "<tr_whatAdultCrownHeightHeight>"
      << "<tr_wachhVal species=\"Species_1\">0</tr_wachhVal>"
      << "</tr_whatAdultCrownHeightHeight>"
      << "<tr_whatSaplingCrownRadDiam>"
      << "<tr_wscrdVal species=\"Species_1\">0</tr_wscrdVal>"
      << "</tr_whatSaplingCrownRadDiam>"
      << "<tr_whatSaplingCrownHeightHeight>"
      << "<tr_wschhVal species=\"Species_1\">0</tr_wschhVal>"
      << "</tr_whatSaplingCrownHeightHeight>"
      << "</allometry>"
      << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>DensitySelfThinning</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\" />"
      << "<applyTo species=\"Species_1\" type=\"Sapling\" />"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>RemoveDead</behaviorName>"
      << "<version>2.0</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\" />"
      << "<applyTo species=\"Species_1\" type=\"Sapling\" />"
      << "</behavior>"
      << "</behaviorList>"
      << "<DensitySelfThinning1>"
      << "<mo_selfThinRadius>"
      << "<mo_strVal species=\"Species_1\">9</mo_strVal>"
      << "</mo_selfThinRadius>"
      << "<mo_minDensityForMort>"
      << "<mo_mdfmVal species=\"Species_1\">0</mo_mdfmVal>"
      << "</mo_minDensityForMort>"
      << "<mo_selfThinAsymptote>"
      << "<mo_staVal species=\"Species_1\">0.1019</mo_staVal>"
      << "</mo_selfThinAsymptote>"
      << "<mo_selfThinDiamEffect>"
      << "<mo_stdieVal species=\"Species_1\">0.5391</mo_stdieVal>"
      << "</mo_selfThinDiamEffect>"
      << "<mo_selfThinDensityEffect>"
      << "<mo_stdeeVal species=\"Species_1\">0.00000877</mo_stdeeVal>"
      << "</mo_selfThinDensityEffect>"
      << "</DensitySelfThinning1>"
      << "</paramFile>";
  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteDensitySelfThinningXMLErrorFile1()
// Error parameter file - more than one year per timestep
/////////////////////////////////////////////////////////////////////////////
const char* WriteDensitySelfThinningXMLErrorFile1()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">"
      << "<plot>"
      << "<timesteps>2</timesteps>"
      << "<rt_timestep>0</rt_timestep>"
      << "<randomSeed>0</randomSeed>"
      << "<yearsPerTimestep>5.0</yearsPerTimestep>"
      << "<plot_lenX>100.0</plot_lenX>"
      << "<plot_lenY>100.0</plot_lenY>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88171785</plot_temp_C>"
      << "<plot_latitude>0.0</plot_latitude>"
      << "</plot>"
      << "<trees>"
      << "<tr_speciesList>"
      << "<tr_species speciesName=\"Species_1\" />"
      << "</tr_speciesList>"
      << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
      << "<tr_minAdultDBH>"
      << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
      << "</tr_minAdultDBH>"
      << "<tr_maxSeedlingHeight>"
      << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
      << "</tr_maxSeedlingHeight>"
      << "</trees>"
      << "<allometry>"
      << "<tr_canopyHeight>"
      << "<tr_chVal species=\"Species_1\">40.0</tr_chVal>"
      << "</tr_canopyHeight>"
      << "<tr_stdAsympCrownRad>"
      << "<tr_sacrVal species=\"Species_1\">0.7</tr_sacrVal>"
      << "</tr_stdAsympCrownRad>"
      << "<tr_stdCrownRadExp>"
      << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
      << "</tr_stdCrownRadExp>"
      << "<tr_conversionDiam10ToDBH>"
      << "<tr_cdtdVal species=\"Species_1\">0.7</tr_cdtdVal>"
      << "</tr_conversionDiam10ToDBH>"
      << "<tr_interceptDiam10ToDBH>"
      << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
      << "</tr_interceptDiam10ToDBH>"
      << "<tr_stdAsympCrownHt>"
      << "<tr_sachVal species=\"Species_1\">0.7</tr_sachVal>"
      << "</tr_stdAsympCrownHt>"
      << "<tr_stdCrownHtExp>"
      << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
      << "</tr_stdCrownHtExp>"
      << "<tr_slopeOfHeight-Diam10>"
      << "<tr_sohdVal species=\"Species_1\">0.03</tr_sohdVal>"
      << "</tr_slopeOfHeight-Diam10>"
      << "<tr_slopeOfAsymHeight>"
      << "<tr_soahVal species=\"Species_1\">0.7</tr_soahVal>"
      << "</tr_slopeOfAsymHeight>"
      << "<tr_whatSeedlingHeightDiam>"
      << "<tr_wsehdVal species=\"Species_1\">0</tr_wsehdVal>"
      << "</tr_whatSeedlingHeightDiam>"
      << "<tr_whatSaplingHeightDiam>"
      << "<tr_wsahdVal species=\"Species_1\">0</tr_wsahdVal>"
      << "</tr_whatSaplingHeightDiam>"
      << "<tr_whatAdultHeightDiam>"
      << "<tr_wahdVal species=\"Species_1\">0</tr_wahdVal>"
      << "</tr_whatAdultHeightDiam>"
      << "<tr_whatAdultCrownRadDiam>"
      << "<tr_wacrdVal species=\"Species_1\">0</tr_wacrdVal>"
      << "</tr_whatAdultCrownRadDiam>"
      << "<tr_whatAdultCrownHeightHeight>"
      << "<tr_wachhVal species=\"Species_1\">0</tr_wachhVal>"
      << "</tr_whatAdultCrownHeightHeight>"
      << "<tr_whatSaplingCrownRadDiam>"
      << "<tr_wscrdVal species=\"Species_1\">0</tr_wscrdVal>"
      << "</tr_whatSaplingCrownRadDiam>"
      << "<tr_whatSaplingCrownHeightHeight>"
      << "<tr_wschhVal species=\"Species_1\">0</tr_wschhVal>"
      << "</tr_whatSaplingCrownHeightHeight>"
      << "</allometry>"
      << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>DensitySelfThinning</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\" />"
      << "<applyTo species=\"Species_1\" type=\"Sapling\" />"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>RemoveDead</behaviorName>"
      << "<version>2.0</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\" />"
      << "<applyTo species=\"Species_1\" type=\"Sapling\" />"
      << "</behavior>"
      << "</behaviorList>"
      << "<DensitySelfThinning1>"
      << "<mo_selfThinRadius>"
      << "<mo_strVal species=\"Species_1\">0.5</mo_strVal>"
      << "</mo_selfThinRadius>"
      << "<mo_minDensityForMort>"
      << "<mo_mdfmVal species=\"Species_1\">0.55</mo_mdfmVal>"
      << "</mo_minDensityForMort>"
      << "<mo_selfThinAsymptote>"
      << "<mo_staVal species=\"Species_1\">0.55</mo_staVal>"
      << "</mo_selfThinAsymptote>"
      << "<mo_selfThinDiamEffect>"
      << "<mo_stdieVal species=\"Species_1\">0.55</mo_stdieVal>"
      << "</mo_selfThinDiamEffect>"
      << "<mo_selfThinDensityEffect>"
      << "<mo_stdeeVal species=\"Species_1\">0.55</mo_stdeeVal>"
      << "</mo_selfThinDensityEffect>"
      << "</DensitySelfThinning1>"
      << "</paramFile>";
  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteDensitySelfThinningXMLErrorFile2()
/////////////////////////////////////////////////////////////////////////////

//Error parameter file - passes adults to this behavior
const char* WriteDensitySelfThinningXMLErrorFile2()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">"
      << "<plot>"
      << "<timesteps>2</timesteps>"
      << "<rt_timestep>0</rt_timestep>"
      << "<randomSeed>0</randomSeed>"
      << "<yearsPerTimestep>1.0</yearsPerTimestep>"
      << "<plot_lenX>100.0</plot_lenX>"
      << "<plot_lenY>100.0</plot_lenY>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88171785</plot_temp_C>"
      << "<plot_latitude>0.0</plot_latitude>"
      << "</plot>"
      << "<trees>"
      << "<tr_speciesList>"
      << "<tr_species speciesName=\"Species_1\" />"
      << "</tr_speciesList>"
      << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
      << "<tr_minAdultDBH>"
      << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
      << "</tr_minAdultDBH>"
      << "<tr_maxSeedlingHeight>"
      << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
      << "</tr_maxSeedlingHeight>"
      << "</trees>"
      << "<allometry>"
      << "<tr_canopyHeight>"
      << "<tr_chVal species=\"Species_1\">40.0</tr_chVal>"
      << "</tr_canopyHeight>"
      << "<tr_stdAsympCrownRad>"
      << "<tr_sacrVal species=\"Species_1\">0.7</tr_sacrVal>"
      << "</tr_stdAsympCrownRad>"
      << "<tr_stdCrownRadExp>"
      << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
      << "</tr_stdCrownRadExp>"
      << "<tr_conversionDiam10ToDBH>"
      << "<tr_cdtdVal species=\"Species_1\">0.7</tr_cdtdVal>"
      << "</tr_conversionDiam10ToDBH>"
      << "<tr_interceptDiam10ToDBH>"
      << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
      << "</tr_interceptDiam10ToDBH>"
      << "<tr_stdAsympCrownHt>"
      << "<tr_sachVal species=\"Species_1\">0.7</tr_sachVal>"
      << "</tr_stdAsympCrownHt>"
      << "<tr_stdCrownHtExp>"
      << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
      << "</tr_stdCrownHtExp>"
      << "<tr_slopeOfHeight-Diam10>"
      << "<tr_sohdVal species=\"Species_1\">0.03</tr_sohdVal>"
      << "</tr_slopeOfHeight-Diam10>"
      << "<tr_slopeOfAsymHeight>"
      << "<tr_soahVal species=\"Species_1\">0.7</tr_soahVal>"
      << "</tr_slopeOfAsymHeight>"
      << "<tr_whatSeedlingHeightDiam>"
      << "<tr_wsehdVal species=\"Species_1\">0</tr_wsehdVal>"
      << "</tr_whatSeedlingHeightDiam>"
      << "<tr_whatSaplingHeightDiam>"
      << "<tr_wsahdVal species=\"Species_1\">0</tr_wsahdVal>"
      << "</tr_whatSaplingHeightDiam>"
      << "<tr_whatAdultHeightDiam>"
      << "<tr_wahdVal species=\"Species_1\">0</tr_wahdVal>"
      << "</tr_whatAdultHeightDiam>"
      << "<tr_whatAdultCrownRadDiam>"
      << "<tr_wacrdVal species=\"Species_1\">0</tr_wacrdVal>"
      << "</tr_whatAdultCrownRadDiam>"
      << "<tr_whatAdultCrownHeightHeight>"
      << "<tr_wachhVal species=\"Species_1\">0</tr_wachhVal>"
      << "</tr_whatAdultCrownHeightHeight>"
      << "<tr_whatSaplingCrownRadDiam>"
      << "<tr_wscrdVal species=\"Species_1\">0</tr_wscrdVal>"
      << "</tr_whatSaplingCrownRadDiam>"
      << "<tr_whatSaplingCrownHeightHeight>"
      << "<tr_wschhVal species=\"Species_1\">0</tr_wschhVal>"
      << "</tr_whatSaplingCrownHeightHeight>"
      << "</allometry>"
      << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>DensitySelfThinning</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\" />"
      << "<applyTo species=\"Species_1\" type=\"Adult\" />"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>RemoveDead</behaviorName>"
      << "<version>2.0</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\" />"
      << "<applyTo species=\"Species_1\" type=\"Adult\" />"
      << "</behavior>"
      << "</behaviorList>"
      << "<DensitySelfThinning1>"
      << "<mo_selfThinRadius>"
      << "<mo_strVal species=\"Species_1\">0.5</mo_strVal>"
      << "</mo_selfThinRadius>"
      << "<mo_minDensityForMort>"
      << "<mo_mdfmVal species=\"Species_1\">0.55</mo_mdfmVal>"
      << "</mo_minDensityForMort>"
      << "<mo_selfThinAsymptote>"
      << "<mo_staVal species=\"Species_1\">0.55</mo_staVal>"
      << "</mo_selfThinAsymptote>"
      << "<mo_selfThinDiamEffect>"
      << "<mo_stdieVal species=\"Species_1\">0.55</mo_stdieVal>"
      << "</mo_selfThinDiamEffect>"
      << "<mo_selfThinDensityEffect>"
      << "<mo_stdeeVal species=\"Species_1\">0.55</mo_stdeeVal>"
      << "</mo_selfThinDensityEffect>"
      << "</DensitySelfThinning1>"
      << "</paramFile>";
  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteDensitySelfThinningXMLErrorFile3()
/////////////////////////////////////////////////////////////////////////////

//Error parameter file - bad parameter
const char* WriteDensitySelfThinningXMLErrorFile3()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">"
      << "<plot>"
      << "<timesteps>2</timesteps>"
      << "<rt_timestep>0</rt_timestep>"
      << "<randomSeed>0</randomSeed>"
      << "<yearsPerTimestep>1.0</yearsPerTimestep>"
      << "<plot_lenX>100.0</plot_lenX>"
      << "<plot_lenY>100.0</plot_lenY>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88171785</plot_temp_C>"
      << "<plot_latitude>0.0</plot_latitude>"
      << "</plot>"
      << "<trees>"
      << "<tr_speciesList>"
      << "<tr_species speciesName=\"Species_1\" />"
      << "</tr_speciesList>"
      << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
      << "<tr_minAdultDBH>"
      << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
      << "</tr_minAdultDBH>"
      << "<tr_maxSeedlingHeight>"
      << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
      << "</tr_maxSeedlingHeight>"
      << "</trees>"
      << "<allometry>"
      << "<tr_canopyHeight>"
      << "<tr_chVal species=\"Species_1\">40.0</tr_chVal>"
      << "</tr_canopyHeight>"
      << "<tr_stdAsympCrownRad>"
      << "<tr_sacrVal species=\"Species_1\">0.7</tr_sacrVal>"
      << "</tr_stdAsympCrownRad>"
      << "<tr_stdCrownRadExp>"
      << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
      << "</tr_stdCrownRadExp>"
      << "<tr_conversionDiam10ToDBH>"
      << "<tr_cdtdVal species=\"Species_1\">0.7</tr_cdtdVal>"
      << "</tr_conversionDiam10ToDBH>"
      << "<tr_interceptDiam10ToDBH>"
      << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
      << "</tr_interceptDiam10ToDBH>"
      << "<tr_stdAsympCrownHt>"
      << "<tr_sachVal species=\"Species_1\">0.7</tr_sachVal>"
      << "</tr_stdAsympCrownHt>"
      << "<tr_stdCrownHtExp>"
      << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
      << "</tr_stdCrownHtExp>"
      << "<tr_slopeOfHeight-Diam10>"
      << "<tr_sohdVal species=\"Species_1\">0.03</tr_sohdVal>"
      << "</tr_slopeOfHeight-Diam10>"
      << "<tr_slopeOfAsymHeight>"
      << "<tr_soahVal species=\"Species_1\">0.7</tr_soahVal>"
      << "</tr_slopeOfAsymHeight>"
      << "<tr_whatSeedlingHeightDiam>"
      << "<tr_wsehdVal species=\"Species_1\">0</tr_wsehdVal>"
      << "</tr_whatSeedlingHeightDiam>"
      << "<tr_whatSaplingHeightDiam>"
      << "<tr_wsahdVal species=\"Species_1\">0</tr_wsahdVal>"
      << "</tr_whatSaplingHeightDiam>"
      << "<tr_whatAdultHeightDiam>"
      << "<tr_wahdVal species=\"Species_1\">0</tr_wahdVal>"
      << "</tr_whatAdultHeightDiam>"
      << "<tr_whatAdultCrownRadDiam>"
      << "<tr_wacrdVal species=\"Species_1\">0</tr_wacrdVal>"
      << "</tr_whatAdultCrownRadDiam>"
      << "<tr_whatAdultCrownHeightHeight>"
      << "<tr_wachhVal species=\"Species_1\">0</tr_wachhVal>"
      << "</tr_whatAdultCrownHeightHeight>"
      << "<tr_whatSaplingCrownRadDiam>"
      << "<tr_wscrdVal species=\"Species_1\">0</tr_wscrdVal>"
      << "</tr_whatSaplingCrownRadDiam>"
      << "<tr_whatSaplingCrownHeightHeight>"
      << "<tr_wschhVal species=\"Species_1\">0</tr_wschhVal>"
      << "</tr_whatSaplingCrownHeightHeight>"
      << "</allometry>"
      << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>DensitySelfThinning</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\" />"
      << "<applyTo species=\"Species_1\" type=\"Sapling\" />"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>RemoveDead</behaviorName>"
      << "<version>2.0</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\" />"
      << "<applyTo species=\"Species_1\" type=\"Sapling\" />"
      << "</behavior>"
      << "</behaviorList>"
      << "<DensitySelfThinning1>"
      << "<mo_selfThinRadius>"
      << "<mo_strVal species=\"Species_1\">-0.5</mo_strVal>"
      << "</mo_selfThinRadius>"
      << "<mo_minDensityForMort>"
      << "<mo_mdfmVal species=\"Species_1\">0.55</mo_mdfmVal>"
      << "</mo_minDensityForMort>"
      << "<mo_selfThinAsymptote>"
      << "<mo_staVal species=\"Species_1\">0.55</mo_staVal>"
      << "</mo_selfThinAsymptote>"
      << "<mo_selfThinDiamEffect>"
      << "<mo_stdieVal species=\"Species_1\">0.55</mo_stdieVal>"
      << "</mo_selfThinDiamEffect>"
      << "<mo_selfThinDensityEffect>"
      << "<mo_stdeeVal species=\"Species_1\">0.55</mo_stdeeVal>"
      << "</mo_selfThinDensityEffect>"
      << "</DensitySelfThinning1>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteDensitySelfThinningXMLErrorFile4()
/////////////////////////////////////////////////////////////////////////////

//Error parameter file - bad parameter
const char* WriteDensitySelfThinningXMLErrorFile4()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">"
      << "<plot>"
      << "<timesteps>2</timesteps>"
      << "<rt_timestep>0</rt_timestep>"
      << "<randomSeed>0</randomSeed>"
      << "<yearsPerTimestep>1.0</yearsPerTimestep>"
      << "<plot_lenX>100.0</plot_lenX>"
      << "<plot_lenY>100.0</plot_lenY>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88171785</plot_temp_C>"
      << "<plot_latitude>0.0</plot_latitude>"
      << "</plot>"
      << "<trees>"
      << "<tr_speciesList>"
      << "<tr_species speciesName=\"Species_1\" />"
      << "</tr_speciesList>"
      << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
      << "<tr_minAdultDBH>"
      << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
      << "</tr_minAdultDBH>"
      << "<tr_maxSeedlingHeight>"
      << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
      << "</tr_maxSeedlingHeight>"
      << "</trees>"
      << "<allometry>"
      << "<tr_canopyHeight>"
      << "<tr_chVal species=\"Species_1\">40.0</tr_chVal>"
      << "</tr_canopyHeight>"
      << "<tr_stdAsympCrownRad>"
      << "<tr_sacrVal species=\"Species_1\">0.7</tr_sacrVal>"
      << "</tr_stdAsympCrownRad>"
      << "<tr_stdCrownRadExp>"
      << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
      << "</tr_stdCrownRadExp>"
      << "<tr_conversionDiam10ToDBH>"
      << "<tr_cdtdVal species=\"Species_1\">0.7</tr_cdtdVal>"
      << "</tr_conversionDiam10ToDBH>"
      << "<tr_interceptDiam10ToDBH>"
      << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
      << "</tr_interceptDiam10ToDBH>"
      << "<tr_stdAsympCrownHt>"
      << "<tr_sachVal species=\"Species_1\">0.7</tr_sachVal>"
      << "</tr_stdAsympCrownHt>"
      << "<tr_stdCrownHtExp>"
      << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
      << "</tr_stdCrownHtExp>"
      << "<tr_slopeOfHeight-Diam10>"
      << "<tr_sohdVal species=\"Species_1\">0.03</tr_sohdVal>"
      << "</tr_slopeOfHeight-Diam10>"
      << "<tr_slopeOfAsymHeight>"
      << "<tr_soahVal species=\"Species_1\">0.7</tr_soahVal>"
      << "</tr_slopeOfAsymHeight>"
      << "<tr_whatSeedlingHeightDiam>"
      << "<tr_wsehdVal species=\"Species_1\">0</tr_wsehdVal>"
      << "</tr_whatSeedlingHeightDiam>"
      << "<tr_whatSaplingHeightDiam>"
      << "<tr_wsahdVal species=\"Species_1\">0</tr_wsahdVal>"
      << "</tr_whatSaplingHeightDiam>"
      << "<tr_whatAdultHeightDiam>"
      << "<tr_wahdVal species=\"Species_1\">0</tr_wahdVal>"
      << "</tr_whatAdultHeightDiam>"
      << "<tr_whatAdultCrownRadDiam>"
      << "<tr_wacrdVal species=\"Species_1\">0</tr_wacrdVal>"
      << "</tr_whatAdultCrownRadDiam>"
      << "<tr_whatAdultCrownHeightHeight>"
      << "<tr_wachhVal species=\"Species_1\">0</tr_wachhVal>"
      << "</tr_whatAdultCrownHeightHeight>"
      << "<tr_whatSaplingCrownRadDiam>"
      << "<tr_wscrdVal species=\"Species_1\">0</tr_wscrdVal>"
      << "</tr_whatSaplingCrownRadDiam>"
      << "<tr_whatSaplingCrownHeightHeight>"
      << "<tr_wschhVal species=\"Species_1\">0</tr_wschhVal>"
      << "</tr_whatSaplingCrownHeightHeight>"
      << "</allometry>"
      << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>DensitySelfThinning</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\" />"
      << "<applyTo species=\"Species_1\" type=\"Sapling\" />"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>RemoveDead</behaviorName>"
      << "<version>2.0</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\" />"
      << "<applyTo species=\"Species_1\" type=\"Sapling\" />"
      << "</behavior>"
      << "</behaviorList>"
      << "<DensitySelfThinning1>"
      << "<mo_selfThinRadius>"
      << "<mo_strVal species=\"Species_1\">0.5</mo_strVal>"
      << "</mo_selfThinRadius>"
      << "<mo_minDensityForMort>"
      << "<mo_mdfmVal species=\"Species_1\">-0.55</mo_mdfmVal>"
      << "</mo_minDensityForMort>"
      << "<mo_selfThinAsymptote>"
      << "<mo_staVal species=\"Species_1\">0.55</mo_staVal>"
      << "</mo_selfThinAsymptote>"
      << "<mo_selfThinDiamEffect>"
      << "<mo_stdieVal species=\"Species_1\">0.55</mo_stdieVal>"
      << "</mo_selfThinDiamEffect>"
      << "<mo_selfThinDensityEffect>"
      << "<mo_stdeeVal species=\"Species_1\">0.55</mo_stdeeVal>"
      << "</mo_selfThinDensityEffect>"
      << "</DensitySelfThinning1>"
      << "</paramFile>";
  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteDensitySelfThinningXMLErrorFile5()
/////////////////////////////////////////////////////////////////////////////

//Error parameter file - bad parameter
const char* WriteDensitySelfThinningXMLErrorFile5()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">"
      << "<plot>"
      << "<timesteps>2</timesteps>"
      << "<rt_timestep>0</rt_timestep>"
      << "<randomSeed>0</randomSeed>"
      << "<yearsPerTimestep>1.0</yearsPerTimestep>"
      << "<plot_lenX>100.0</plot_lenX>"
      << "<plot_lenY>100.0</plot_lenY>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88171785</plot_temp_C>"
      << "<plot_latitude>0.0</plot_latitude>"
      << "</plot>"
      << "<trees>"
      << "<tr_speciesList>"
      << "<tr_species speciesName=\"Species_1\" />"
      << "</tr_speciesList>"
      << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
      << "<tr_minAdultDBH>"
      << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
      << "</tr_minAdultDBH>"
      << "<tr_maxSeedlingHeight>"
      << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
      << "</tr_maxSeedlingHeight>"
      << "</trees>"
      << "<allometry>"
      << "<tr_canopyHeight>"
      << "<tr_chVal species=\"Species_1\">40.0</tr_chVal>"
      << "</tr_canopyHeight>"
      << "<tr_stdAsympCrownRad>"
      << "<tr_sacrVal species=\"Species_1\">0.7</tr_sacrVal>"
      << "</tr_stdAsympCrownRad>"
      << "<tr_stdCrownRadExp>"
      << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
      << "</tr_stdCrownRadExp>"
      << "<tr_conversionDiam10ToDBH>"
      << "<tr_cdtdVal species=\"Species_1\">0.7</tr_cdtdVal>"
      << "</tr_conversionDiam10ToDBH>"
      << "<tr_interceptDiam10ToDBH>"
      << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
      << "</tr_interceptDiam10ToDBH>"
      << "<tr_stdAsympCrownHt>"
      << "<tr_sachVal species=\"Species_1\">0.7</tr_sachVal>"
      << "</tr_stdAsympCrownHt>"
      << "<tr_stdCrownHtExp>"
      << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
      << "</tr_stdCrownHtExp>"
      << "<tr_slopeOfHeight-Diam10>"
      << "<tr_sohdVal species=\"Species_1\">0.03</tr_sohdVal>"
      << "</tr_slopeOfHeight-Diam10>"
      << "<tr_slopeOfAsymHeight>"
      << "<tr_soahVal species=\"Species_1\">0.7</tr_soahVal>"
      << "</tr_slopeOfAsymHeight>"
      << "<tr_whatSeedlingHeightDiam>"
      << "<tr_wsehdVal species=\"Species_1\">0</tr_wsehdVal>"
      << "</tr_whatSeedlingHeightDiam>"
      << "<tr_whatSaplingHeightDiam>"
      << "<tr_wsahdVal species=\"Species_1\">0</tr_wsahdVal>"
      << "</tr_whatSaplingHeightDiam>"
      << "<tr_whatAdultHeightDiam>"
      << "<tr_wahdVal species=\"Species_1\">0</tr_wahdVal>"
      << "</tr_whatAdultHeightDiam>"
      << "<tr_whatAdultCrownRadDiam>"
      << "<tr_wacrdVal species=\"Species_1\">0</tr_wacrdVal>"
      << "</tr_whatAdultCrownRadDiam>"
      << "<tr_whatAdultCrownHeightHeight>"
      << "<tr_wachhVal species=\"Species_1\">0</tr_wachhVal>"
      << "</tr_whatAdultCrownHeightHeight>"
      << "<tr_whatSaplingCrownRadDiam>"
      << "<tr_wscrdVal species=\"Species_1\">0</tr_wscrdVal>"
      << "</tr_whatSaplingCrownRadDiam>"
      << "<tr_whatSaplingCrownHeightHeight>"
      << "<tr_wschhVal species=\"Species_1\">0</tr_wschhVal>"
      << "</tr_whatSaplingCrownHeightHeight>"
      << "</allometry>"
      << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>DensitySelfThinning</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\" />"
      << "<applyTo species=\"Species_1\" type=\"Sapling\" />"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>RemoveDead</behaviorName>"
      << "<version>2.0</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\" />"
      << "<applyTo species=\"Species_1\" type=\"Sapling\" />"
      << "</behavior>"
      << "</behaviorList>"
      << "<DensitySelfThinning1>"
      << "<mo_selfThinRadius>"
      << "<mo_strVal species=\"Species_1\">0.5</mo_strVal>"
      << "</mo_selfThinRadius>"
      << "<mo_minDensityForMort>"
      << "<mo_mdfmVal species=\"Species_1\">0.55</mo_mdfmVal>"
      << "</mo_minDensityForMort>"
      << "<mo_selfThinAsymptote>"
      << "<mo_staVal species=\"Species_1\">-0.55</mo_staVal>"
      << "</mo_selfThinAsymptote>"
      << "<mo_selfThinDiamEffect>"
      << "<mo_stdieVal species=\"Species_1\">0.55</mo_stdieVal>"
      << "</mo_selfThinDiamEffect>"
      << "<mo_selfThinDensityEffect>"
      << "<mo_stdeeVal species=\"Species_1\">0.55</mo_stdeeVal>"
      << "</mo_selfThinDensityEffect>"
      << "</DensitySelfThinning1>"
      << "</paramFile>";
  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteDensitySelfThinningXMLErrorFile6()
// Error parameter file - bad parameter
/////////////////////////////////////////////////////////////////////////////
const char* WriteDensitySelfThinningXMLErrorFile6() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">"
      << "<plot>"
      << "<timesteps>2</timesteps>"
      << "<rt_timestep>0</rt_timestep>"
      << "<randomSeed>0</randomSeed>"
      << "<yearsPerTimestep>1.0</yearsPerTimestep>"
      << "<plot_lenX>100.0</plot_lenX>"
      << "<plot_lenY>100.0</plot_lenY>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88171785</plot_temp_C>"
      << "<plot_latitude>0.0</plot_latitude>"
      << "</plot>"
      << "<trees>"
      << "<tr_speciesList>"
      << "<tr_species speciesName=\"Species_1\" />"
      << "</tr_speciesList>"
      << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
      << "<tr_minAdultDBH>"
      << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
      << "</tr_minAdultDBH>"
      << "<tr_maxSeedlingHeight>"
      << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
      << "</tr_maxSeedlingHeight>"
      << "</trees>"
      << "<allometry>"
      << "<tr_canopyHeight>"
      << "<tr_chVal species=\"Species_1\">40.0</tr_chVal>"
      << "</tr_canopyHeight>"
      << "<tr_stdAsympCrownRad>"
      << "<tr_sacrVal species=\"Species_1\">0.7</tr_sacrVal>"
      << "</tr_stdAsympCrownRad>"
      << "<tr_stdCrownRadExp>"
      << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
      << "</tr_stdCrownRadExp>"
      << "<tr_conversionDiam10ToDBH>"
      << "<tr_cdtdVal species=\"Species_1\">0.7</tr_cdtdVal>"
      << "</tr_conversionDiam10ToDBH>"
      << "<tr_interceptDiam10ToDBH>"
      << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
      << "</tr_interceptDiam10ToDBH>"
      << "<tr_stdAsympCrownHt>"
      << "<tr_sachVal species=\"Species_1\">0.7</tr_sachVal>"
      << "</tr_stdAsympCrownHt>"
      << "<tr_stdCrownHtExp>"
      << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
      << "</tr_stdCrownHtExp>"
      << "<tr_slopeOfHeight-Diam10>"
      << "<tr_sohdVal species=\"Species_1\">0.03</tr_sohdVal>"
      << "</tr_slopeOfHeight-Diam10>"
      << "<tr_slopeOfAsymHeight>"
      << "<tr_soahVal species=\"Species_1\">0.7</tr_soahVal>"
      << "</tr_slopeOfAsymHeight>"
      << "<tr_whatSeedlingHeightDiam>"
      << "<tr_wsehdVal species=\"Species_1\">0</tr_wsehdVal>"
      << "</tr_whatSeedlingHeightDiam>"
      << "<tr_whatSaplingHeightDiam>"
      << "<tr_wsahdVal species=\"Species_1\">0</tr_wsahdVal>"
      << "</tr_whatSaplingHeightDiam>"
      << "<tr_whatAdultHeightDiam>"
      << "<tr_wahdVal species=\"Species_1\">0</tr_wahdVal>"
      << "</tr_whatAdultHeightDiam>"
      << "<tr_whatAdultCrownRadDiam>"
      << "<tr_wacrdVal species=\"Species_1\">0</tr_wacrdVal>"
      << "</tr_whatAdultCrownRadDiam>"
      << "<tr_whatAdultCrownHeightHeight>"
      << "<tr_wachhVal species=\"Species_1\">0</tr_wachhVal>"
      << "</tr_whatAdultCrownHeightHeight>"
      << "<tr_whatSaplingCrownRadDiam>"
      << "<tr_wscrdVal species=\"Species_1\">0</tr_wscrdVal>"
      << "</tr_whatSaplingCrownRadDiam>"
      << "<tr_whatSaplingCrownHeightHeight>"
      << "<tr_wschhVal species=\"Species_1\">0</tr_wschhVal>"
      << "</tr_whatSaplingCrownHeightHeight>"
      << "</allometry>"
      << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>DensitySelfThinning</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\" />"
      << "<applyTo species=\"Species_1\" type=\"Sapling\" />"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>RemoveDead</behaviorName>"
      << "<version>2.0</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\" />"
      << "<applyTo species=\"Species_1\" type=\"Sapling\" />"
      << "</behavior>"
      << "</behaviorList>"
      << "<DensitySelfThinning1>"
      << "<mo_selfThinRadius>"
      << "<mo_strVal species=\"Species_1\">0.5</mo_strVal>"
      << "</mo_selfThinRadius>"
      << "<mo_minDensityForMort>"
      << "<mo_mdfmVal species=\"Species_1\">0.55</mo_mdfmVal>"
      << "</mo_minDensityForMort>"
      << "<mo_selfThinAsymptote>"
      << "<mo_staVal species=\"Species_1\">0.55</mo_staVal>"
      << "</mo_selfThinAsymptote>"
      << "<mo_selfThinDiamEffect>"
      << "<mo_stdieVal species=\"Species_1\">0.55</mo_stdieVal>"
      << "</mo_selfThinDiamEffect>"
      << "<mo_selfThinDensityEffect>"
      << "<mo_stdeeVal species=\"Species_1\">-0.55</mo_stdeeVal>"
      << "</mo_selfThinDensityEffect>"
      << "</DensitySelfThinning1>"
      << "</paramFile>";
  oOut.close();

  return cFileString;
}
