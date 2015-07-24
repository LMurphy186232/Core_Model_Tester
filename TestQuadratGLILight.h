//---------------------------------------------------------------------------
// TestQuadratGLILight
//---------------------------------------------------------------------------
#if !defined(TestQuadratGLILight_H)
#define TestQuadratGLILight_H


#include <fstream>

/**
 * Tests the class clQuadratGLILight.
 */

/**
 * Writes a parameter file to direct testing.
 * <ul>
 * <li>Two tree species</li>
 * <li>One behavior - Quadrat GLI</li>
 * </ul>
 * @return Filename written.
 */
const char* WriteQuadratGLILightXMLFile1();

/**
 * Writes a parameter file to direct testing.
 * <ul>
 * <li>Two tree species</li>
 * <li>Grid information for "Quadrat GLI" setting it to 10m by 10m with full
 * map information</li>
 * <li>First behavior - GLI Light</li>
 * <li>Second behavior - Quadrat GLI</li>
 * <li>Same sky grid information for Quadrat GLI Light and GLI Light - 12 alt
 * and 18 azi grids</li>
 * </ul>
 * @return Filename written.
 */
const char* WriteQuadratGLILightXMLFile2();

/**
 * Writes a parameter file to direct testing.
 * <ul>
 * <li>Two tree species</li>
 * <li>Tree densities - to provide canopy cover to calculate GLI against</li>
 * <li>First behavior - Quadrat GLI</li>
 * <li>Second behavior - Quadrat GLI Light</li>
 * <li>Same sky grid information for Quadrat GLI Light and GLI Map - 12 alt
 * and 18 azi grids</li>
 * <li>Both behaviors have their light heights set to 0 m</li>
 * <li>Quadrat GLI grid set to 8 X 8 cells so it will match GLI Map</li>
 * </ul>
 * @return Filename written.
 */
const char* WriteQuadratGLILightXMLFile3();

/**
 * Writes a parameter file to direct testing.
 * <ul>
 * <li>Two tree species</li>
 * <li>First behavior - GLI Light</li>
 * <li>Second behavior - GLI Map</li>
 * <li>Different sky grid information for GLI Light and GLI Map</li>
 * </ul>
 * @return Filename written.
 */
const char* WriteQuadratGLILightXMLFile4();

/**
 * Writes a parameter file to direct testing.
 * <ul>
 * <li>Two tree species</li>
 * <li>Tree densities - to provide canopy cover to calculate GLI against</li>
 * <li>Only behavior - Quadrat GLI</li>
 * <li>Quadrat GLI forced to calculate every cell</li>
 * </ul>
 * @return Filename written.
 */
const char* WriteQuadratGLILightXMLFile5();

/**
 * Writes a parameter file to direct error testing.  The number of azimuth
 * grids for Quadrat GLI is less than or equal to 0.
 * @return Filename written.
 */
const char* WriteQuadratGLILightXMLErrorFile1();

/**
 * Writes a parameter file to direct error testing.  The number of altitude
 * grids for Quadrat GLI is less than or equal to 0.
 * @return Filename written.
 */
const char* WriteQuadratGLILightXMLErrorFile2();

/**
 * Writes a parameter file to direct error testing.  The height of the GLI
 * photo is less than 0.
 * @return Filename written.
 */
const char* WriteQuadratGLILightXMLErrorFile3();

/**
 * Writes common portions of the test parameter files (tree pop, plot, etc).
 * @param oOut File stream to write to.
 */
void WriteQuadratGLILightCommonStuff(std::fstream &oOut);
//---------------------------------------------------------------------------
#endif // TestGLIMap_H
