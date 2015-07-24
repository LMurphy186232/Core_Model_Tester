//---------------------------------------------------------------------------
// TestMortality.cpp
//---------------------------------------------------------------------------
#include "TestCompetitionMortality.h"
#include <gtest/gtest.h>
#include "SimManager.h"
#include "TreePopulation.h"
#include "BehaviorBase.h"
#include <fstream>
#include <math.h>
#include "NCIEffectsList.h"

/////////////////////////////////////////////////////////////////////////////
// TestMortality()
/////////////////////////////////////////////////////////////////////////////
TEST(CompetitionMortality, TestMortality) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  clTreePopulation * p_oPop;
  clTreeSearch *p_oAllTrees;
  clTree *p_oTree;
  float fVal;
  int **p_iTreeCount;
  int i, j, iNumSpecies, iNumTypes;

  try {

    //Change to WriteCompetitionMortalityXMLFile2 to test one of the errors - timestep>1
    p_oSimManager->ReadFile( WriteCompetitionMortalityXMLFile1() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
    iNumSpecies = p_oPop->GetNumberOfSpecies();
    iNumTypes = p_oPop->GetNumberOfTypes();

    //Set up our tree count array
    p_iTreeCount = new int*[iNumSpecies];
    for (i = 0; i < iNumSpecies; i++) {
      p_iTreeCount[i] = new int[iNumTypes];
      for (j = 0; j < iNumTypes; j++) {
        p_iTreeCount[i][j] = 0;
      }
    }

    //Adults of Species 1
    fVal = 0.5;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(1, 1, 0, clTreePopulation::adult, 20);
      //Put a value of 0.5 in the "lgm" data member
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), fVal);
    }

    //Initial conditions count
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_iTreeCount[p_oTree->GetSpecies()][p_oTree->GetType()]++;
      p_oTree = p_oAllTrees->NextTree();
    }

    EXPECT_EQ(p_iTreeCount[0][clTreePopulation::adult], 1000);

    //Run for one timestep - everything except the light and growth behavior
    for (i = 2; i < p_oSimManager->GetNumberOfBehaviors(); i++)
      p_oSimManager->GetBehaviorObject(i)->Action();

    ASSERT_TRUE((p_iTreeCount[0][clTreePopulation::adult] >= 517) && (p_iTreeCount[0][clTreePopulation::adult] >= 563));

    //Cleanup
    for (i = 0; i < iNumSpecies; i++) delete[] p_iTreeCount[i];
    delete[] p_iTreeCount;

    delete p_oSimManager;

  } catch (modelErr &e) {
    for (i = 0; i < iNumSpecies; i++) delete[] p_iTreeCount[i];
    delete[] p_iTreeCount;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}



/////////////////////////////////////////////////////////////////////////////
// WriteCompetitionMortalityXMLFile1()
/////////////////////////////////////////////////////////////////////////////
//Rasmus parameter file
const char* WriteCompetitionMortalityXMLFile1()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">"
      << "<plot>"
      << "<timesteps>15</timesteps>"
      << "<rt_timestep>0</rt_timestep>"
      << "<randomSeed>937465</randomSeed>"
      << "<yearsPerTimestep>1.0</yearsPerTimestep>"
      //<< "<yearsPerTimestep>5.0</yearsPerTimestep>"
      << "<plot_lenX>100.0</plot_lenX>"
      << "<plot_lenY>100.0</plot_lenY>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88171785</plot_temp_C>"
      << "<plot_latitude>0.0</plot_latitude>"
      << "</plot>"
      << "<trees>"
      << "<tr_speciesList>"
      << "<tr_species speciesName=\"Species_1\" />"
      //<< "<tr_species speciesName=\"Species_2\" />"
      << "</tr_speciesList>"
      << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
      << "<tr_minAdultDBH>"
      << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
      //<< "<tr_madVal species=\"Species_2\">10.0</tr_madVal>"
      << "</tr_minAdultDBH>"
      << "<tr_maxSeedlingHeight>"
      << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
      << "</tr_maxSeedlingHeight>"
      << "</trees>"
      << "<allometry>"
      << "<tr_canopyHeight>"
      << "<tr_chVal species=\"Species_1\">40.0</tr_chVal>"
      // << "<tr_chVal species=\"Species_2\">40.0</tr_chVal>"
      << "</tr_canopyHeight>"
      << "<tr_stdAsympCrownRad>"
      << "<tr_sacrVal species=\"Species_1\">0.7</tr_sacrVal>"
      //<< "<tr_sacrVal species=\"Species_2\">0.7</tr_sacrVal>"
      << "</tr_stdAsympCrownRad>"
      << "<tr_stdCrownRadExp>"
      << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
      //<< "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
      << "</tr_stdCrownRadExp>"
      << "<tr_conversionDiam10ToDBH>"
      << "<tr_cdtdVal species=\"Species_1\">0.7</tr_cdtdVal>"
      //<< "<tr_cdtdVal species=\"Species_2\">0.7</tr_cdtdVal>"
      << "</tr_conversionDiam10ToDBH>"
      << "<tr_interceptDiam10ToDBH>"
      << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
      << "</tr_interceptDiam10ToDBH>"
      << "<tr_stdAsympCrownHt>"
      << "<tr_sachVal species=\"Species_1\">0.7</tr_sachVal>"
      //<< "<tr_sachVal species=\"Species_2\">0.7</tr_sachVal>"
      << "</tr_stdAsympCrownHt>"
      << "<tr_stdCrownHtExp>"
      << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
      //<< "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
      << "</tr_stdCrownHtExp>"
      << "<tr_slopeOfHeight-Diam10>"
      << "<tr_sohdVal species=\"Species_1\">0.03</tr_sohdVal>"
      //<< "<tr_sohdVal species=\"Species_2\">0.03</tr_sohdVal>"
      << "</tr_slopeOfHeight-Diam10>"
      << "<tr_slopeOfAsymHeight>"
      << "<tr_soahVal species=\"Species_1\">0.7</tr_soahVal>"
      // << "<tr_soahVal species=\"Species_2\">0.7</tr_soahVal>"
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
      << "<behaviorName>ConstantGLI</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>1</listPosition>"
      //<< "<applyTo species=\"Species_1\" type=\"Seedling\" />"
      //<< "<applyTo species=\"Species_1\" type=\"Sapling\" />"
      // << "<applyTo species=\"Species_2\" type=\"Sapling\" />"
      << "<applyTo species=\"Species_1\" type=\"Adult\" />"
      //<< "<applyTo species=\"Species_2\" type=\"Adult\" />"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>NCIMasterGrowth</behaviorName>"
      << "<version>3.0</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\" />"
      //<< "<applyTo species=\"Species_1\" type=\"Sapling\" />"
      //<< "<applyTo species=\"Species_2\" type=\"Adult\" />"
      //<< "<applyTo species=\"Species_2\" type=\"Sapling\" />"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>CompetitionMortality</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>3</listPosition>"
      //<< "<applyTo species=\"Species_1\" type=\"Seedling\" />"
      //<< "<applyTo species=\"Species_1\" type=\"Sapling\" />"
      << "<applyTo species=\"Species_1\" type=\"Adult\" />"
      //<< "<applyTo species=\"Species_2\" type=\"Sapling\" />"
      // << "<applyTo species=\"Species_2\" type=\"Adult\" />"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>RemoveDead</behaviorName>"
      << "<version>2.0</version>"
      << "<listPosition>4</listPosition>"
      //<< "<applyTo species=\"Species_1\" type=\"Seedling\" />"
      //<< "<applyTo species=\"Species_1\" type=\"Sapling\" />"
      << "<applyTo species=\"Species_1\" type=\"Adult\" />"
      //<< "<applyTo species=\"Species_2\" type=\"Sapling\" />"
      //<< "<applyTo species=\"Species_2\" type=\"Adult\" />"
      << "</behavior>"
      << "</behaviorList>"
      << "<ConstantGLI1>"
      << "<li_constGLI>100</li_constGLI>"
      << "</ConstantGLI1>"
      << "<NCIMasterGrowth2>"
      << "<nciWhichShadingEffect>" << no_shading << "</nciWhichShadingEffect>"
      << "<nciWhichCrowdingEffect>" << no_crowding_effect << "</nciWhichCrowdingEffect>"
      << "<nciWhichNCITerm>" << no_nci_term << "</nciWhichNCITerm>"
      << "<nciWhichSizeEffect>1</nciWhichSizeEffect>"
      << "<nciWhichDamageEffect>" << no_damage_effect << "</nciWhichDamageEffect>"
      << "<nciWhichPrecipitationEffect>" << no_precip_effect << "</nciWhichPrecipitationEffect>"
      << "<nciWhichTemperatureEffect>" << no_temp_effect << "</nciWhichTemperatureEffect>"
      << "<nciWhichNitrogenEffect>" << no_nitrogen_effect << "</nciWhichNitrogenEffect>"
      << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
      << "<gr_stochGrowthMethod>" << deterministic_pdf << "</gr_stochGrowthMethod>"

      << "<gr_nciMaxPotentialGrowth>"
      << "<gr_nmpgVal species=\"Species_1\">0.2</gr_nmpgVal>"
      << "</gr_nciMaxPotentialGrowth>"

      << "<gr_nciMaxCrowdingRadius>"
      << "<gr_nmcrVal species=\"Species_1\">10</gr_nmcrVal>"
      << "</gr_nciMaxCrowdingRadius>"

      << "<nciSizeEffectX0>"
      << "<nsex0Val species=\"Species_1\">25</nsex0Val>"
      << "</nciSizeEffectX0>"

      << "<nciSizeEffectXb>"
      << "<nsexbVal species=\"Species_1\">1</nsexbVal>"
      << "</nciSizeEffectXb>"

      << "</NCIMasterGrowth2>"


      << "<CompetitionMortality3>"
      << "<mo_CompMort>"
      << "<mo_cmVal species=\"Species_1\">0.05</mo_cmVal>"
      //<< "<mo_cmVal species=\"Species_2\">1</mo_cmVal>"
      << "</mo_CompMort>"
      << "<mo_CompMortMax>"
      << "<mo_cmmVal species=\"Species_1\">1</mo_cmmVal>"
      //<< "<mo_cmmVal species=\"Species_2\">0.45</mo_cmmVal>"
      << "</mo_CompMortMax>"
      << "</CompetitionMortality3>"
      << "</paramFile>";
  oOut.close();
  return cFileString;
}


/////////////////////////////////////////////////////////////////////////////
// WriteCompetitionMortalityXMLFile2()
/////////////////////////////////////////////////////////////////////////////

//Rasmus parameter file
const char* WriteCompetitionMortalityXMLFile2()
{
  using namespace std;
  const char *cFileString = "TestFile2.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">"
      << "<plot>"
      << "<timesteps>15</timesteps>"
      << "<rt_timestep>0</rt_timestep>"
      << "<randomSeed>937465</randomSeed>"
      << "<yearsPerTimestep>5.0</yearsPerTimestep>"
      //<< "<yearsPerTimestep>5.0</yearsPerTimestep>"
      << "<plot_lenX>100.0</plot_lenX>"
      << "<plot_lenY>100.0</plot_lenY>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88171785</plot_temp_C>"
      << "<plot_latitude>0.0</plot_latitude>"
      << "</plot>"
      << "<trees>"
      << "<tr_speciesList>"
      << "<tr_species speciesName=\"Species_1\" />"
      //<< "<tr_species speciesName=\"Species_2\" />"
      << "</tr_speciesList>"
      << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
      << "<tr_minAdultDBH>"
      << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
      //<< "<tr_madVal species=\"Species_2\">10.0</tr_madVal>"
      << "</tr_minAdultDBH>"
      << "<tr_maxSeedlingHeight>"
      << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
      << "</tr_maxSeedlingHeight>"
      << "</trees>"
      << "<allometry>"
      << "<tr_canopyHeight>"
      << "<tr_chVal species=\"Species_1\">40.0</tr_chVal>"
      // << "<tr_chVal species=\"Species_2\">40.0</tr_chVal>"
      << "</tr_canopyHeight>"
      << "<tr_stdAsympCrownRad>"
      << "<tr_sacrVal species=\"Species_1\">0.7</tr_sacrVal>"
      //<< "<tr_sacrVal species=\"Species_2\">0.7</tr_sacrVal>"
      << "</tr_stdAsympCrownRad>"
      << "<tr_stdCrownRadExp>"
      << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
      //<< "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
      << "</tr_stdCrownRadExp>"
      << "<tr_conversionDiam10ToDBH>"
      << "<tr_cdtdVal species=\"Species_1\">0.7</tr_cdtdVal>"
      //<< "<tr_cdtdVal species=\"Species_2\">0.7</tr_cdtdVal>"
      << "</tr_conversionDiam10ToDBH>"
      << "<tr_interceptDiam10ToDBH>"
      << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
      << "</tr_interceptDiam10ToDBH>"
      << "<tr_stdAsympCrownHt>"
      << "<tr_sachVal species=\"Species_1\">0.7</tr_sachVal>"
      //<< "<tr_sachVal species=\"Species_2\">0.7</tr_sachVal>"
      << "</tr_stdAsympCrownHt>"
      << "<tr_stdCrownHtExp>"
      << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
      //<< "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
      << "</tr_stdCrownHtExp>"
      << "<tr_slopeOfHeight-Diam10>"
      << "<tr_sohdVal species=\"Species_1\">0.03</tr_sohdVal>"
      //<< "<tr_sohdVal species=\"Species_2\">0.03</tr_sohdVal>"
      << "</tr_slopeOfHeight-Diam10>"
      << "<tr_slopeOfAsymHeight>"
      << "<tr_soahVal species=\"Species_1\">0.7</tr_soahVal>"
      // << "<tr_soahVal species=\"Species_2\">0.7</tr_soahVal>"
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
      << "<behaviorName>ConstantGLI</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>1</listPosition>"
      //<< "<applyTo species=\"Species_1\" type=\"Seedling\" />"
      //<< "<applyTo species=\"Species_1\" type=\"Sapling\" />"
      // << "<applyTo species=\"Species_2\" type=\"Sapling\" />"
      << "<applyTo species=\"Species_1\" type=\"Adult\" />"
      //<< "<applyTo species=\"Species_2\" type=\"Adult\" />"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>NCIMasterGrowth</behaviorName>"
      << "<version>3.0</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\" />"
      //<< "<applyTo species=\"Species_1\" type=\"Sapling\" />"
      //<< "<applyTo species=\"Species_2\" type=\"Adult\" />"
      //<< "<applyTo species=\"Species_2\" type=\"Sapling\" />"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>CompetitionMortality</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>3</listPosition>"
      //<< "<applyTo species=\"Species_1\" type=\"Seedling\" />"
      //<< "<applyTo species=\"Species_1\" type=\"Sapling\" />"
      << "<applyTo species=\"Species_1\" type=\"Adult\" />"
      //<< "<applyTo species=\"Species_2\" type=\"Sapling\" />"
      // << "<applyTo species=\"Species_2\" type=\"Adult\" />"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>RemoveDead</behaviorName>"
      << "<version>2.0</version>"
      << "<listPosition>4</listPosition>"
      //<< "<applyTo species=\"Species_1\" type=\"Seedling\" />"
      //<< "<applyTo species=\"Species_1\" type=\"Sapling\" />"
      << "<applyTo species=\"Species_1\" type=\"Adult\" />"
      //<< "<applyTo species=\"Species_2\" type=\"Sapling\" />"
      //<< "<applyTo species=\"Species_2\" type=\"Adult\" />"
      << "</behavior>"
      << "</behaviorList>"
      << "<ConstantGLI1>"
      << "<li_constGLI>100</li_constGLI>"
      << "</ConstantGLI1>"
      << "<NCIMasterGrowth2>"

      << "<nciWhichShadingEffect>" << no_shading << "</nciWhichShadingEffect>"
      << "<nciWhichCrowdingEffect>" << no_crowding_effect << "</nciWhichCrowdingEffect>"
      << "<nciWhichNCITerm>" << no_nci_term << "</nciWhichNCITerm>"
      << "<nciWhichSizeEffect>1</nciWhichSizeEffect>"
      << "<nciWhichDamageEffect>" << no_damage_effect << "</nciWhichDamageEffect>"
      << "<nciWhichPrecipitationEffect>" << no_precip_effect << "</nciWhichPrecipitationEffect>"
      << "<nciWhichTemperatureEffect>" << no_temp_effect << "</nciWhichTemperatureEffect>"
      << "<nciWhichNitrogenEffect>" << no_nitrogen_effect << "</nciWhichNitrogenEffect>"
      << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
      << "<gr_stochGrowthMethod>" << deterministic_pdf << "</gr_stochGrowthMethod>"

      << "<gr_nciMaxPotentialGrowth>"
      << "<gr_nmpgVal species=\"Species_1\">0.2</gr_nmpgVal>"
      << "</gr_nciMaxPotentialGrowth>"

      << "<nciSizeEffectX0>"
      << "<nsex0Val species=\"Species_1\">25</nsex0Val>"
      << "</nciSizeEffectX0>"

      << "<nciSizeEffectXb>"
      << "<nsexbVal species=\"Species_1\">1</nsexbVal>"
      << "</nciSizeEffectXb>"

      << "</NCIMasterGrowth2>"


      << "<CompetitionMortality3>"
      << "<mo_CompMort>"
      << "<mo_cmVal species=\"Species_1\">0.05</mo_cmVal>"
      //<< "<mo_cmVal species=\"Species_2\">1</mo_cmVal>"
      << "</mo_CompMort>"
      << "<mo_CompMortMax>"
      << "<mo_cmmVal species=\"Species_1\">1</mo_cmmVal>"
      //<< "<mo_cmmVal species=\"Species_2\">0.45</mo_cmmVal>"
      << "</mo_CompMortMax>"
      << "</CompetitionMortality3>"
      << "</paramFile>";

  oOut.close();
  return cFileString;
}

