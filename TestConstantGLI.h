//---------------------------------------------------------------------------
// TestConstantGLI
//---------------------------------------------------------------------------
#if !defined(TestConstantGLI_H)
#define TestConstantGLI_H

#include <fstream>

/**
 * Writes a parameter file for normal proceessing.  There are three species,
 * and the constant GLI behavior is applied to species 2 and 3.
 * @return Filename written.
 */
const char* WriteConstantGLIXMLFile1();

/**
 * Writes an error file where the constant GLI is less than 0.
 * @return File name of the freshly written parameter file.
 */
const char* WriteConstantGLIXMLErrorFile1();

/**
 * Writes an error file where the constant GLI is greater than 100.
 * @return File name of the freshly written parameter file.
 */
const char* WriteConstantGLIXMLErrorFile2();

/**
 * Writes common portions of the test parameter files (allometry and tree
 * pop).
 * @param oOut File stream to write to.
 */
void WriteConstantGLICommonStuff(std::fstream &oOut);

//---------------------------------------------------------------------------
#endif // TestDensityLight_H
