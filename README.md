Readme

ReadGlobales.c (compiled for x64 readglobales)
Input file: ficheroPCB.kicad_pcb
Output file:  ficheroPCB-RelativasGlobales.csv

Reads the references and their relative positions of all the modules of a layout filePCB.kicad_pcb
and save them in  filePCB-RelativasGlobales.csv

The first line of the output file shows the number of footprints

----------------------------------------------------------------------------------------------------

The program RestoreGlobales.c restores the references saved wiht ReadGlobales.c.

RestoreGlobales.c (compiled restoreglobales)
Input file 1: filePCB.kicad_pcb
Input file 2: filePCB-RelativasGlobales.cs

Output file 1: filePCB.kicad_pcbOld (original)
Output file 2: filePCB.kicad_pcb 

----------------------------------------------------------------------------------------------------

Main use:
After having positioned the reference of a module, if this module is updated its reference is reset to the default in library.

If all footprints of the board are updated, all the reference's positions are updated to default.
With ReadGlobales the relative reference positions can be saved BEFORE updating the modules.
With RestoreGlobales former reference positions are restored.

-----------------------------------------------------------------------------------------------------------------------------
