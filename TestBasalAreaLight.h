//---------------------------------------------------------------------------
// TestBasalAreaLight
//---------------------------------------------------------------------------
#if !defined(TestBasalAreaLight_H)
#define TestBasalAreaLight_H

#include <fstream>

/**
 * Writes a parameter file for normal proceessing run 1.
 * @return Filename written.
 */
const char* WriteBasalAreaLightXMLFile1();

/**
 * Writes a parameter file for normal proceessing run 2.
 * @return Filename written.
 */
const char* WriteBasalAreaLightXMLFile2();

/**
 * Writes a parameter file for normal proceessing run 3.
 * @return Filename written.
 */
const char* WriteBasalAreaLightXMLFile3();

/**
 * Writes a parameter file for normal proceessing run 4.
 * @return Filename written.
 */
const char* WriteBasalAreaLightXMLFile4();

/**
 * Writes a parameter file for normal proceessing run 5.
 * @return Filename written.
 */
const char* WriteBasalAreaLightXMLFile5();

/**
 * Writes an error file where the conifer "c" parameter = 0.
 * @return File name of the freshly written parameter file.
 */
const char* WriteBasalAreaLightXMLErrorFile1();

/**
 * Writes an error file where the angiosperm "c" parameter = 0.
 * @return File name of the freshly written parameter file.
 */
const char* WriteBasalAreaLightXMLErrorFile2();

/**
 * Writes an error file where the change threshold < 0.
 * @return File name of the freshly written parameter file.
 */
const char* WriteBasalAreaLightXMLErrorFile3();

/**
 * Writes an error file where the minimum DBH < 0.
 * @return File name of the freshly written parameter file.
 */
const char* WriteBasalAreaLightXMLErrorFile4();

/**
 * Writes an error file where the radius is negative.
 * @return File name of the freshly written parameter file.
 */
const char* WriteBasalAreaLightXMLErrorFile5();

/**
 * Writes common portions of the test parameter files (allometry and tree
 * pop).
 * @param oOut File stream to write to.
 */
void WriteBasalAreaLightCommonStuff(std::fstream &oOut);

//---------------------------------------------------------------------------
#endif // TestBasalAreaLight_H
