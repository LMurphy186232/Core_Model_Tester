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

//---------------------------------------------------------------------------
#endif
