//---------------------------------------------------------------------------
// TestQualityVigorClassifier
//---------------------------------------------------------------------------
#if !defined(TestQualityVigorClassifier_H)
#define TestQualityVigorClassifier_H


/**
 * Tests the class clQualityVigorClassifier.
 */

/**
 * Writes the parameter file for normal processing.
 * @param bAddTreeMap Whether to add the tag for the text tree map.
 * @return Filename written.
 */
const char* WriteQualityVigorClassifierXMLFile1(bool bAddTreeMap);

/**
 * Writes the parameter file for normal processing of initial conditions.
 * @return Filename written.
 */
const char* WriteQualityVigorClassifierXMLFile2();

/**
 * Writes the parameter file for normal processing of initial conditions.
 * @return Filename written.
 */
const char* WriteQualityVigorClassifierXMLFile3();

/**
 * Writes an error file where the behavior is applied to not-adults.
 * @return Filename written.
 */
const char* WriteQualityVigorClassifierXMLErrorFile1();

/**
 * Writes a text treemap of trees.
 * @return Filename written.
 */
const char* WriteQualityVigorClassifierTextTreeMap1();

/**
 * Writes a text treemap of trees.
 * @return Filename written.
 */
const char* WriteQualityVigorClassifierTextTreeMap2();
//---------------------------------------------------------------------------
#endif // TestBiomassCalculator_H
