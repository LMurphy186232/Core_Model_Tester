//---------------------------------------------------------------------------
// TestNCIMort
//---------------------------------------------------------------------------
#if !defined(TestNCIMasterMortality_H)
#define TestNCIMasterMortality_H

#include <fstream>

/**
 * Writes a 1-year timestep file. This contains 4 species, one unused
 * (species 3; this helps catch array-index problems). NCI mortality
 * is assigned to all saplings and adults.
 *
 * @return Filename written.
 */
const char* WriteNCIMortXMLFile1();

/**
 * Writes a 3-year timestep file. This contains 4 species, one unused
 * (species 3; this helps catch array-index problems). NCI mortality
 * is assigned to all saplings and adults.
 *
 * @return Filename written.
 */
const char* WriteNCIMortXMLFile2();

/**
 * Writes a 1-year timestep file. NCI mortality is assigned to species 1
 * adults.
 *
 * @return Filename written.
 */
const char* WriteNCIMortXMLFile3();

/**
 * Writes a 3-year timestep file. NCI mortality is assigned to species 1
 * adults.
 *
 * @return Filename written.
 */
const char* WriteNCIMortXMLFile4();

/**
 * Writes a 1-year timestep file for Run 3.
 *
 * @return Filename written.
 */
const char* WriteNCIMortXMLFile5();

/**
 * Writes a 3-year timestep file for Run 3.
 *
 * @return Filename written.
 */
const char* WriteNCIMortXMLFile6();

/**
 * Writes a 1-year timestep file for Run 4.
 *
 * @return Filename written.
 */
const char* WriteNCIMortXMLFile7();

/**
 * Writes a 3-year timestep file for Run 4.
 *
 * @return Filename written.
 */
const char* WriteNCIMortXMLFile8();

/**
 * Writes a 1-year timestep file for Run 5.
 *
 * @return Filename written.
 */
const char* WriteNCIMortXMLFile9();

/**
 * Writes a 3-year timestep file for Run 5.
 *
 * @return Filename written.
 */
const char* WriteNCIMortXMLFile10();

/**
 * Writes a 1-year timestep file for Run 6.
 *
 * @return Filename written.
 */
const char* WriteNCIMortXMLFile11();

/**
 * Writes a 3-year timestep file for Run 6.
 *
 * @return Filename written.
 */
const char* WriteNCIMortXMLFile12();

/**
 * Writes an error condition where max radius of neighbor effects is < 0.
 *
 * @return Filename written.
 */
const char* WriteNCIMortXMLErrorFile1();

/**
 * Writes an error condition where max probability for survival for a species
 * is not between 0 and 1.
 *
 * @return Filename written.
 */
const char* WriteNCIMortXMLErrorFile2();

/**
 * Writes an error condition where Xb for a species = 0.
 *
 * @return Filename written.
 */
const char* WriteNCIMortXMLErrorFile3();

/**
 * Writes an error condition where X0 for a species = 0.
 *
 * @return Filename written.
 */
const char* WriteNCIMortXMLErrorFile4();

/**
 * Writes an error condition where med. damage eta for a species < 0.
 *
 * @return Filename written.
 */
const char* WriteNCIMortXMLErrorFile5();

/**
 * Writes an error condition where med. damage eta for a species > 1.
 *
 * @return Filename written.
 */
const char* WriteNCIMortXMLErrorFile6();

/**
 * Writes an error condition where full damage eta for a species < 0.
 *
 * @return Filename written.
 */
const char* WriteNCIMortXMLErrorFile7();

/**
 * Writes an error condition where full damage eta for a species > 1.
 *
 * @return Filename written.
 */
const char* WriteNCIMortXMLErrorFile8();

/**
 * Writes an error condition where med. damage storm effect for a species < 0.
 *
 * @return Filename written.
 */
const char* WriteNCIMortXMLErrorFile9();

/**
 * Writes an error condition where med. damage storm effect for a species > 1.
 *
 * @return Filename written.
 */
const char* WriteNCIMortXMLErrorFile10();

/**
 * Writes an error condition where full damage storm effect for a species < 0.
 *
 * @return Filename written.
 */
const char* WriteNCIMortXMLErrorFile11();

/**
 * Writes an error condition where full damage storm effect for a species > 1.
 *
 * @return Filename written.
 */
const char* WriteNCIMortXMLErrorFile12();

/**
 * Writes an error condition where shading is used but there is no light
 * behavior.
 *
 * @return Filename written.
 */
const char* WriteNCIMortXMLErrorFile13();

/**
 * Writes common portions of the test parameter files. Ends with
 * "</allometry>".
 * @param oOut File stream to write to.
 */
void WriteNCIMortPlotAndTrees(std::fstream &oOut);

/**
 * Writes storm parameters. Everything from "<storm>" to "</storm>".
 */
void WriteNCIMortStormParameters(std::fstream &oOut);

/**
 * Writes common portions of the test error parameter files (tree pop, plot,
 * etc).
 * @param oOut File stream to write to.
 */
void WriteNCIMortCommonErrorStuff(std::fstream &oOut);

/**
 * Writes common portions of the test parameter files for Run 1.
 * Picks up at the behavior list through the end of the file.
 * @param oOut File stream to write to.
 */
void WriteNCIMortRun1CommonStuff(std::fstream &oOut);

/**
 * Writes common portions of the test parameter files for Run 2.
 * Picks up at the behavior list through the end of the file.
 * @param oOut File stream to write to.
 */
void WriteNCIMortRun2CommonStuff(std::fstream &oOut);

/**
 * Writes common portions of the test parameter files for Run 3.
 * Picks up at the behavior list through the end of the file.
 * @param oOut File stream to write to.
 */
void WriteNCIMortRun3CommonStuff(std::fstream &oOut);

/**
 * Writes common portions of the test parameter files for Run 4.
 * Picks up at the behavior list through the end of the file.
 * @param oOut File stream to write to.
 */
void WriteNCIMortRun4CommonStuff(std::fstream &oOut);

/**
 * Writes common portions of the test parameter files for Run 5.
 * Picks up at the behavior list through the end of the file.
 * @param oOut File stream to write to.
 */
void WriteNCIMortRun5CommonStuff(std::fstream &oOut);

/**
 * Writes common portions of the test parameter files for Run 6.
 * Picks up at the behavior list through the end of the file.
 * @param oOut File stream to write to.
 */
void WriteNCIMortRun6CommonStuff(std::fstream &oOut);
//---------------------------------------------------------------------------
#endif // TestPuertoRicoNCIMort_H
