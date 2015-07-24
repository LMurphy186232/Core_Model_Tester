//---------------------------------------------------------------------------
// TestGrids
//---------------------------------------------------------------------------
#if !defined(TestGrids_H)
  #define TestGrids_H

class clSimManager;
class clGrid;

/**
 * Creates a grid and initializes it with values.  The two data members are
 * called "int" and "float".  The grid cell size is 4X6.
 * @param p_oSimManager Sim manager.
 * @return Created, initialized grid.
 */
clGrid* CreateGrid(clSimManager *p_oSimManager);

/**
 * Writes an XML file that will create the sim manager so we can create a
 * grid through the proper channels.  The plot size is 200X200 m.
 * @return Filename just written.
 */
const char* WriteGridXMLFile1();
//---------------------------------------------------------------------------
#endif // TestGrids_H
