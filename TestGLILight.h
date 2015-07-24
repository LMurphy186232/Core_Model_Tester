//---------------------------------------------------------------------------
#ifndef TestGLILightH
#define TestGLILightH

/**
 * This class tests the GLILight class.
 */

/**For testing the values in tree records*/
struct fakeRecord {
  float fX, /**<X value*/
  fY, /**<Y value*/
  fLight; /**<Expected GLI*/
  bool bRead; /**<whether or not this has been read*/
};

/**
 * Writes a parameter file to direct testing for GLI light assignments.
 * @return Filename written.
 */
const char* WriteGLILightXMLFile1();

/**
 * Writes a parameter file to direct testing for GLI light assignments.
 * @return Filename written.
 */
const char* WriteGLILightXMLFile2();

/**
 * Writes a parameter file to direct testing for GLI light assignments.
 * @return Filename written.
 */
const char* WriteGLILightXMLFile3();

/**
 * Writes a parameter file with a deliberate error.  The number of years per
 * timestep is less than 1, which should cause light to throw an error.
 * @return Filename written.
 */
const char* WriteGLILightXMLErrorFile1();
//---------------------------------------------------------------------------
#endif
