#pragma once

#include "MatrixCell.h"
#include "SudokuWindow.h"
#include <vector>
#include <QString>



#define GRID_SIZE_SOLVE 9 

void BackTrackingMethod(int matrix[GRID_SIZE_SOLVE][GRID_SIZE_SOLVE], MatrixCell* DisplayMatrix[GRID_SIZE_SOLVE][GRID_SIZE_SOLVE],
	int startMatrix[GRID_SIZE_SOLVE][GRID_SIZE_SOLVE]);
