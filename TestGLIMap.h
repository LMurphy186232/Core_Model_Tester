//---------------------------------------------------------------------------
// TestGLIMap
//---------------------------------------------------------------------------
#if !defined(TestGLIMap_H)
#define TestGLIMap_H


#include <fstream>

/**
 * Tests the class clGLIMap.
 *
 * <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 * TO DO:  Prepare a couple of GLI points for an 8 by 8 grid to test GLI when
 * the GLI Map behavior is the only one in the run.  Then add them to
 * TestNormalProcessing.
 * <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 */

/**
 * Writes a parameter file to direct testing.
 * <ul>
 * <li>One tree species</li>
 * <li>One behavior - GLI Map</li>
 * </ul>
 * @return Filename written.
 */
const char* WriteGLIMapXMLFile1();

/**
 * Writes a parameter file to direct testing.
 * <ul>
 * <li>One tree species</li>
 * <li>Grid information for "GLI Map" setting it to 10m by 10m with full map
 * information</li>
 * <li>Quadrat GLI grid is also set to 10m by 10m<li>
 * <li>First behavior - Quadrat GLI Light</li>
 * <li>Second behavior - GLI Map</li>
 * <li>Same sky grid information for Quadrat GLI Light and GLI Map - 12 alt
 * and 18 azi grids</li>
 * <li>Both behaviors have their light heights set to 2 m</li>
 * </ul>
 * @return Filename written.
 */
const char* WriteGLIMapXMLFile2();

/**
 * Writes a parameter file to direct testing.
 * <ul>
 * <li>One tree species</li>
 * <li>Tree densities - to provide canopy cover to calculate GLI against</li>
 * <li>First behavior - GLI Map</li>
 * <li>Second behavior - Quadrat GLI Light</li>
 * <li>Same sky grid information for Quadrat GLI Light and GLI Map - 12 alt
 * and 18 azi grids</li>
 * <li>Both behaviors have their light heights set to 0 m</li>
 * <li>Quadrat GLI grid set to 8 X 8 cells so it will match GLI Map</li>
 * </ul>
 * @return Filename written.
 */
const char* WriteGLIMapXMLFile3();

/**
 * Writes a parameter file to direct testing.
 * <ul>
 * <li>One tree species</li>
 * <li>First behavior - GLI Light</li>
 * <li>Second behavior - GLI Map</li>
 * <li>Same sky grid information for GLI Light and GLI Map</li>
 * </ul>
 * @return Filename written.
 */
const char* WriteGLIMapXMLFile4();

/**
 * Writes a parameter file to direct testing.
 * <ul>
 * <li>One tree species</li>
 * <li>First behavior - GLI Map</li>
 * <li>Second behavior - GLI Light</li>
 * <li>Same sky grid information for GLI Light and GLI Map</li>
 * </ul>
 * @return Filename written.
 */
const char* WriteGLIMapXMLFile5();

/**
 * Writes a parameter file to direct testing.
 * <ul>
 * <li>One tree species</li>
 * <li>First behavior - GLI Light</li>
 * <li>Second behavior - GLI Map</li>
 * <li>Different sky grid information for GLI Light and GLI Map</li>
 * </ul>
 * @return Filename written.
 */
const char* WriteGLIMapXMLFile6();

/**
 * Writes a parameter file to direct testing.
 * <ul>
 * <li>One tree species</li>
 * <li>Two GLI Map behaviors with different setups</li>
 * </ul>
 * @return Filename written.
 */
const char* WriteGLIMapXMLFile7();

/**
 * Writes a parameter file to direct error testing.  The number of azimuth
 * grids for GLI Map is less than or equal to 0.
 * @return Filename written.
 */
const char* WriteGLIMapXMLErrorFile1();

/**
 * Writes a parameter file to direct error testing.  The number of altitude
 * grids for GLI Map is less than or equal to 0.
 * @return Filename written.
 */
const char* WriteGLIMapXMLErrorFile2();

/**
 * Writes a parameter file to direct error testing.  The height of the GLI
 * photo is less than 0.
 * @return Filename written.
 */
const char* WriteGLIMapXMLErrorFile3();

/**
 * Writes common portions of the test parameter files (tree pop, plot, etc).
 * @param oOut File stream to write to.
 */
void WriteGLIMapCommonStuff(std::fstream &oOut);
//---------------------------------------------------------------------------
#endif // TestGLIMap_H
