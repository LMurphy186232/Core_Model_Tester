//---------------------------------------------------------------------------
// TestAverageLight
//---------------------------------------------------------------------------
#if !defined(TestAverageLight_H)
#define TestAverageLight_H

#include <fstream>

/**
 * Writes a parameter file for normal proceessing run 1.
 * @return Filename written.
 */
const char* WriteAverageLightXMLFile1();

/**
 * Writes a parameter file for normal proceessing run 2.
 * @return Filename written.
 */
const char* WriteAverageLightXMLFile2();

/**
 * Writes a parameter file for normal proceessing run 3.
 * @return Filename written.
 */
const char* WriteAverageLightXMLFile3();

/**
 * Writes a parameter file for normal proceessing run 4.
 * @return Filename written.
 */
const char* WriteAverageLightXMLFile4();

/**
 * Writes a parameter file for normal proceessing run 5.
 * @return Filename written.
 */
const char* WriteAverageLightXMLFile5();

/**
 * Writes an error file where the GLI Map behavior is not enabled.
 * @return File name of the freshly written parameter file.
 */
const char* WriteAverageLightXMLErrorFile1();

/**
 * Writes tree file.
 * @param oOut File stream to write to.
 */
void WriteAverageLightTreeFile(std::fstream &oOut);
//---------------------------------------------------------------------------
#endif // TestAverageLight_H
