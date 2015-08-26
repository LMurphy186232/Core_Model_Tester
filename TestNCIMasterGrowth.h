//---------------------------------------------------------------------------
// TestNciGrowth
//---------------------------------------------------------------------------
#if !defined(TestNciGrowth_H)
#define TestNciGrowth_H

#include <fstream>

/**
 * Writes a parameter file to direct testing. This contains two species,
 * identical in all ways except Species 1 is assigned NCI growth
 * as a diameter-auto, and Species 2 is assigned NCI growth as diameter-only.
 *
 * @return Filename written.
 */
const char* WriteNCIGrowthXMLFile1();

/**
 * Writes a 1-year timestep file. This contains 3 species. NCI growth
 * (auto-height) is assigned to adults of Species 1.
 *
 * @return Filename written.
 */
const char* WriteNCIGrowthXMLFile2();

/**
 * Writes a 3-year timestep file. This contains 3 species. NCI growth
 * (auto-height) is assigned to adults of Species 1.
 *
 * @return Filename written.
 */
const char* WriteNCIGrowthXMLFile3();

/**
 * Writes a 1-year timestep file. This contains 4 species, one unused
 * (species 3; this helps catch array-index problems). NCI growth
 * (auto-height) is assigned to all saplings and adults.
 *
 * @return Filename written.
 */
const char* WriteNCIGrowthXMLFile4();

/**
 * Writes a 3-year timestep file. This contains 4 species, one unused
 * (species 3; this helps catch array-index problems). NCI growth
 * (auto-height) is assigned to all saplings and adults.
 *
 * @return Filename written.
 */
const char* WriteNCIGrowthXMLFile5();

/**
 * Writes a 1-timestep file for Run 3.
 * @return Filename written.
 */
const char* WriteNCIGrowthXMLFile6();

/**
 * Writes a 3-timestep file for Run 3.
 * @return Filename written.
 */
const char* WriteNCIGrowthXMLFile7();

/**
 * Writes a 1-timestep file for Run 4.
 * @return Filename written.
 */
const char* WriteNCIGrowthXMLFile8();

/**
 * Writes a 3-timestep file for Run 4.
 * @return Filename written.
 */
const char* WriteNCIGrowthXMLFile9();

/**
 * Writes a 1-timestep file for Run 5.
 * @return Filename written.
 */
const char* WriteNCIGrowthXMLFile10();

/**
 * Writes a 3-timestep file for Run 5.
 * @return Filename written.
 */
const char* WriteNCIGrowthXMLFile11();

/**
 * Writes a 1-timestep file for Run 6.
 * @return Filename written.
 */
const char* WriteNCIGrowthXMLFile12();

/**
 * Writes a 3-timestep file for Run 6.
 * @return Filename written.
 */
const char* WriteNCIGrowthXMLFile13();

/**
 * Writes an error condition where max radius of neighbor effects is < 0,
 * with default NCI or NCI with neighbor damage.
 *
 * @param bDefault if true, write default NCI; if false, write with neighbor damage.
 * @return Filename written.
 */
const char* WriteNCIGrowthXMLErrorFile1(bool bDefault);

/**
 * Writes an error condition where max growth for a species is < 0.
 *
 * @return Filename written.
 */
const char* WriteNCIGrowthXMLErrorFile2();

/**
 * Writes an error condition where Xb for a species = 0.
 *
 * @return Filename written.
 */
const char* WriteNCIGrowthXMLErrorFile3();

/**
 * Writes an error condition where X0 for a species = 0.
 *
 * @return Filename written.
 */
const char* WriteNCIGrowthXMLErrorFile4();

/**
 * Writes an error condition where med. damage eta for a species < 0.
 *
 * @return Filename written.
 */
const char* WriteNCIGrowthXMLErrorFile5();

/**
 * Writes an error condition where med. damage eta for a species > 1.
 *
 * @return Filename written.
 */
const char* WriteNCIGrowthXMLErrorFile6();

/**
 * Writes an error condition where full damage eta for a species < 0.
 *
 * @return Filename written.
 */
const char* WriteNCIGrowthXMLErrorFile7();

/**
 * Writes an error condition where full damage eta for a species > 1.
 *
 * @return Filename written.
 */
const char* WriteNCIGrowthXMLErrorFile8();

/**
 * Writes an error condition where med. damage storm effect for a species < 0.
 *
 * @return Filename written.
 */
const char* WriteNCIGrowthXMLErrorFile9();

/**
 * Writes an error condition where med. damage storm effect for a species > 1.
 *
 * @return Filename written.
 */
const char* WriteNCIGrowthXMLErrorFile10();

/**
 * Writes an error condition where full damage storm effect for a species < 0.
 *
 * @return Filename written.
 */
const char* WriteNCIGrowthXMLErrorFile11();

/**
 * Writes an error condition where full damage storm effect for a species > 1.
 *
 * @return Filename written.
 */
const char* WriteNCIGrowthXMLErrorFile12();

/**
 * Writes an error condition where shading is used but there is no light
 * behavior.
 *
 * @return Filename written.
 */
const char* WriteNCIGrowthXMLErrorFile13();

/**
 * Writes an error condition where a neighbor DBH is less than 0,
 * with default NCI or NCI with neighbor damage.
 *
 * @param bDefault if true, write default NCI; if false, write with neighbor damage.
 * @return Filename written.
 */
const char* WriteNCIGrowthXMLErrorFile14(bool bDefault);


/**
 * Writes common portions of the test parameter files (tree pop, plot, etc).
 * Picks up right after the number of years per timestep and ends at the
 * closing tree tag.
 * @param oOut File stream to write to.
 */
void WriteNCIGrowthCommonStuff(std::fstream &oOut);

/**
 * Writes common portions of the test parameter files for Run 1.
 * Picks up at the behavior list through the end of the file.
 * @param oOut File stream to write to.
 */
void WriteNCIGrowthRun1CommonStuff(std::fstream &oOut);

/**
 * Writes common portions of the test parameter files for Run 2.
 * Picks up at the behavior list through the end of the file.
 * @param oOut File stream to write to.
 */
void WriteNCIGrowthRun2CommonStuff(std::fstream &oOut);

/**
 * Writes common portions of the test parameter files for Run 3.
 * Picks up at the behavior list through the end of the file.
 * @param oOut File stream to write to.
 */
void WriteNCIGrowthRun3CommonStuff(std::fstream &oOut);

/**
 * Writes common portions of the test parameter files for Run 4.
 * Picks up at the behavior list through the end of the file.
 * @param oOut File stream to write to.
 */
void WriteNCIGrowthRun4CommonStuff(std::fstream &oOut);

/**
 * Writes common portions of the test parameter files for Run 5.
 * Picks up at the behavior list through the end of the file.
 * @param oOut File stream to write to.
 */
void WriteNCIGrowthRun5CommonStuff(std::fstream &oOut);

/**
 * Writes common portions of the test parameter files for Run 6.
 * Picks up at the behavior list through the end of the file.
 * @param oOut File stream to write to.
 */
void WriteNCIGrowthRun6CommonStuff(std::fstream &oOut);

/**
 * Writes common portions of the test error parameter files (tree pop, plot,
 * etc). Starts at the beginning of the file and ends at the closing tree tag.
 * @param oOut File stream to write to.
 */
void WriteNCIGrowthErrorFileCommonStuff(std::fstream &oOut);

/**
 * Writes common portions of the test error parameter files that deal with storms.
 * @param oOut File stream to write to.
 */
void WriteNCIGrowthStormErrorFileCommonStuff(std::fstream &oOut);
//---------------------------------------------------------------------------
#endif // TestNciGrowth_H
