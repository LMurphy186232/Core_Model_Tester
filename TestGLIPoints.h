//---------------------------------------------------------------------------

#ifndef TestGLIPointsH
#define TestGLIPointsH

/**
 * Writes a parameter file to direct testing.  There is one species and one
 * behavior:  GLI points.
 *
 * @return Filename written.
 */
const char* WriteGLIPointsXMLFile1();

/**
 * Writes a parameter file with no points in the points list.
 * @return Filename written.
 */
const char* WriteGLIPointsXMLErrorFile1();

/**
 * Writes a parameter file where the number of azimuth angles is less than 0.
 * @return Filename written.
 */
const char* WriteGLIPointsXMLErrorFile2();

/**
 * Writes a parameter file where the number of altitude angles is less than 0.
 * @return Filename written.
 */
const char* WriteGLIPointsXMLErrorFile3();

/**
 * Writes a parameter file where a point's X or Y coordinate is outside the
 * plot.
 * @return Filename written.
 */
const char* WriteGLIPointsXMLErrorFile4();

/**
 * Writes a parameter file where a point's height is negative.
 * @return Filename written.
 */
const char* WriteGLIPointsXMLErrorFile5();
//---------------------------------------------------------------------------
#endif
