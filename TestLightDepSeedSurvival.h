//---------------------------------------------------------------------------
// TestLightDepSeedSurvival
//---------------------------------------------------------------------------
#if !defined(TestLightDepSeedSurvival_H)
#define TestLightDepSeedSurvival_H

#include <fstream>

/**
 * Writes the setup file for DoNormalGLIRun1().  This contains 5 species, one
 * unused (species 1; this helps catch array-index problems).  Non-spatial
 * disperse is applied to adults of all species, with values such that no
 * seeds will be dispersed from any trees.  Species 2-4 get light-dependent
 * seed survival. Species 2-4 get storm damage.
 *
 * @return Filename written.
 */
const char* WriteLightDepSeedSurvivalXMLFile1();

/**
 * Writes the setup file for DoNormalGLIRun2().  This contains 5 species, one
 * unused (species 1; this helps catch array-index problems).  Non-spatial
 * disperse is applied to adults of all species, with values such that no
 * seeds will be dispersed from any trees.  Species 2-4 get light-dependent
 * seed survival. Species 2-4 get Weibull snag mortality.
 *
 * @return Filename written.
 */
const char* WriteLightDepSeedSurvivalXMLFile2();

/**
 * Writes the setup file for DoNormalStormLightProcessing().  This contains 5
 * species, one unused (species 1; this helps catch array-index problems).
 * Non-spatial disperse is applied to adults of all species, with values such
 * that no seeds will be dispersed from any trees.  Species 2-4 get
 * storm-light-dependent seed survival.
 *
 * @return Filename written.
 */
const char* WriteLightDepSeedSurvivalXMLFile3();

/**
 * Writes a file where a light extinction coefficient is not between 0 and 1.
 * @return Filename written.
 */
const char* WriteLightDepSeedSurvivalXMLErrorFile1();

/**
 * Writes a file where the value for m_fLightHeight is not zero or greater.
 * @return Filename written.
 */
const char* WriteLightDepSeedSurvivalXMLErrorFile2();

/**
 * Writes a file where the value for mp_fOptimumGLI is not between 0 and 100.
 * @return Filename written.
 */
const char* WriteLightDepSeedSurvivalXMLErrorFile3();

/**
 * Writes a file where there is no disperse behavior.
 * @return Filename written.
 */
const char* WriteLightDepSeedSurvivalXMLErrorFile4();

/**
 * Writes a file where the number of altitude angles is less than 1.
 * @return Filename written.
 */
const char* WriteLightDepSeedSurvivalXMLErrorFile5();

/**
 * Writes a file where the number of azimuth angles is less than 1.
 * @return Filename written.
 */
const char* WriteLightDepSeedSurvivalXMLErrorFile6();

/**
 * Writes a file that has Storm Light Dependent Seed Survival but does not
 * have storm light.
 * @return Filename written.
 */
const char* WriteLightDepSeedSurvivalXMLErrorFile7();


/**
 * Writes common portions of the test parameter files (tree pop, plot, etc).
 * Ends with &lt;/trees&gt.
 * @param oOut File stream to write to.
 */
void WriteLightDepSeedSurvivalCommonStuff(std::fstream &oOut);
//---------------------------------------------------------------------------
#endif // TestPuertoRicoEstablishment_H
