//---------------------------------------------------------------------------
// TestGapLight
//---------------------------------------------------------------------------
#if !defined(TestGapLight_H)
  #define TestGapLight_H

/**
* Tests the GapLight class.
*/

/**
 * Writes a parameter file.  This contains no grid information so that the
 * grid will default to 8 X 8 cells.
 *
 * @return Filename written.
 */
const char* WriteGapLightXMLFile1();

/**
 * Writes a parameter file.  This contains grid information so that the
 * grid will have 2 X 4 cells.
 *
 * @return Filename written.
 */
const char* WriteGapLightXMLFile2();
//---------------------------------------------------------------------------
#endif // TestGapLight_H
