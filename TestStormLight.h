//---------------------------------------------------------------------------
// TestStormLight
//---------------------------------------------------------------------------
#if !defined(TestStormLight_H)
#define TestStormLight_H

/**
 * Tests the clStormLight class.
 */

/**
 * Writes a parameter file for normal proceessing run 1.  This has the storm
 * and storm damage appliers, a mortality behavior to satisfy storm
 * requirements, and the storm light behavior. The timestep length is 1 year.
 * @return Filename written.
 */
const char* WriteStormLightXMLFile1();

/**
 * Writes a parameter file for normal proceessing run 1.  This has the storm
 * and storm damage appliers, a mortality behavior to satisfy storm
 * requirements, and the storm light behavior. The timestep length is 1 year.
 * @return Filename written.
 */
const char* WriteStormLightXMLFile2();

/**
 * Writes an error file where the minimum number of trees for a full canopy
 * is less than 0.
 * @return File name of the freshly written parameter file.
 */
const char* WriteStormLightXMLErrorFile1();
//---------------------------------------------------------------------------
#endif // TestStormLights_H
