//---------------------------------------------------------------------------
// TestRelativeGrowth
//---------------------------------------------------------------------------
#if !defined(TestRelativeGrowth_H)
#define TestRelativeGrowth_H
#include <fstream>

/**
 * Tests the clRelativeGrowth class.  This tests all six types of relative
 * growth - non-limited relative growth, relative growth limited to constant
 * radial increment, relative growth limited to constant basal area increment,
 * non-limited relative growth - diameter update only, relative growth limited to
 * constant radial increment - diameter update only, and relative growth limited
 * to constant basal area increment - diameter update only.
 */

/**
 * Writes a parameter file to direct testing.  Timestep length is 1 year.
 * This contains three species.
 * Behaviors:
 * <ul>
 * <li>Non-limited relative growth is applied to Species 1 saplings.</li>
 * <li>Relative growth limited to constant radial increment is applied to
 * Species 2 saplings.</li>
 * <li>Relative growth limited to basal area increment is applied to Species
 * 1 adults.</li>
 * <li>Non-limited relative growth - diameter only is applied to Species 3
 * saplings.</li>
 * <li>Relative growth limited to constant radial increment - diameter only is
 * applied to Species 4 saplings.</li>
 * <li>Relative growth limited to basal area increment - diameter only is
 * applied to Species 3 adults.</li>
 * <li>Height incrementer applied to all with diameter only behaviors.</li>
 * <li>Diameter exponents are 1.</li>
 * </ul>
 *
 * @return Filename written.
 */
const char* WriteRelativeGrowthXMLFile1();

/**
 * Writes a parameter file to direct testing.  Timestep length is 3 years.
 * This contains three species.
 * Behaviors:
 * <ul>
 * <li>Non-limited relative growth is applied to Species 1 saplings.</li>
 * <li>Relative growth limited to constant radial increment is applied to
 * Species 2 saplings.</li>
 * <li>Relative growth limited to basal area increment is applied to Species
 * 1 adults.</li>
 * <li>Non-limited relative growth - diameter only is applied to Species 3
 * saplings.</li>
 * <li>Relative growth limited to constant radial increment - diameter only is
 * applied to Species 4 saplings.</li>
 * <li>Relative growth limited to basal area increment - diameter only is
 * applied to Species 3 adults.</li>
 * <li>Height incrementer applied to all with diameter only behaviors.</li>
 * <li>Diameter exponents are 1.</li>
 * </ul>
 *
 * @return Filename written.
 */
const char* WriteRelativeGrowthXMLFile2();

/**
 * Writes a parameter file to direct testing.  Timestep length is 1 year.
 * This contains three species.
 * Behaviors:
 * <ul>
 * <li>Non-limited relative growth is applied to Species 1 saplings.</li>
 * <li>Relative growth limited to constant radial increment is applied to
 * Species 2 saplings.</li>
 * <li>Relative growth limited to basal area increment is applied to Species
 * 1 adults.</li>
 * <li>Non-limited relative growth - diameter only is applied to Species 3
 * saplings.</li>
 * <li>Relative growth limited to constant radial increment - diameter only is
 * applied to Species 4 saplings.</li>
 * <li>Relative growth limited to basal area increment - diameter only is
 * applied to Species 3 adults.</li>
 * <li>Height incrementer applied to all with diameter only behaviors.</li>
 * <li>Diameter exponents are non-1.</li>
 * </ul>
 *
 * @return Filename written.
 */
const char* WriteRelativeGrowthXMLFile3();

/**
 * Writes a parameter file to direct testing.  Timestep length is 3 years.
 * This contains three species.
 * Behaviors:
 * <ul>
 * <li>Non-limited relative growth is applied to Species 1 saplings.</li>
 * <li>Relative growth limited to constant radial increment is applied to
 * Species 2 saplings.</li>
 * <li>Relative growth limited to basal area increment is applied to Species
 * 1 adults.</li>
 * <li>Non-limited relative growth - diameter only is applied to Species 3
 * saplings.</li>
 * <li>Relative growth limited to constant radial increment - diameter only is
 * applied to Species 4 saplings.</li>
 * <li>Relative growth limited to basal area increment - diameter only is
 * applied to Species 3 adults.</li>
 * <li>Height incrementer applied to all with diameter only behaviors.</li>
 * <li>Diameter exponents are non-1.</li>
 * </ul>
 *
 * @return Filename written.
 */
const char* WriteRelativeGrowthXMLFile4();

/**
 * Writes a parameter file to direct testing for run 3. Timestep length is 1
 * year. This contains four species. Relative height growth is applied to all
 * species. Diameter incrementer applied to all as well.
 *
 * @return Filename written.
 */
const char* WriteRelativeGrowthXMLFile5();

/**
 * Writes a parameter file to direct testing for run 3. Timestep length is 3
 * years. This contains four species. Relative height growth is applied to all
 * species. Diameter incrementer applied to all as well.
 *
 * @return Filename written.
 */
const char* WriteRelativeGrowthXMLFile6();

/**
 * Writes common portions of the run 3 test parameter files.
 * @param oOut File stream to write to.
 */
void WriteRelativeGrowthRun3CommonStuff(std::fstream &oOut);
//---------------------------------------------------------------------------
#endif // TestRelativeGrowth_H
