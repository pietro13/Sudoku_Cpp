#include "SolvingMethods.h"
#include <QDebug>
#include <windows.h>






/* 
Solving Method BackTracking
params: Matrix, DisplayMatrix, startMatrix
*/

void BackTrackingMethod(int matrix[GRID_SIZE_SOLVE][GRID_SIZE_SOLVE], MatrixCell* displayMatrix[GRID_SIZE_SOLVE][GRID_SIZE_SOLVE],
	int startMatrix[GRID_SIZE_SOLVE][GRID_SIZE_SOLVE])
{
	// Memory of acceptable numbers for cell in matrix
	std::vector<int>* mem[GRID_SIZE_SOLVE][GRID_SIZE_SOLVE]{ nullptr };


	for (int i = 0; i < GRID_SIZE_SOLVE; i++)
	{
		for (int j = 0; j < GRID_SIZE_SOLVE; j++)
		{
			if (!startMatrix[i][j])
			{// Set in memory of cell numbers from 1 to GRID_SIZE_SOLVE (should be 9)
				mem[i][j] = new std::vector<int>(GRID_SIZE_SOLVE);
				std::iota((*mem[i][j]).begin(), (*mem[i][j]).end(), 1);
			}
		}
	}


	for (int i = 0; i < GRID_SIZE_SOLVE; i++)
	{
		for (int j = 0; j < GRID_SIZE_SOLVE; j++)
		{
			if (!startMatrix[i][j])
			{
				std::vector<int>* CellMem = mem[i][j];
				//activate cell on display
				displayMatrix[i][j]->activate();
				displayMatrix[i][j]->repaint();
				displayMatrix[i][j]->deactivate();
				if (CellMem->size() == 9)
				{// Eresa numbers from memory of cell by sudoku rules
					for (int k = 0; k < GRID_SIZE_SOLVE; k++)
					{
						//horizontal line rule
						CellMem->erase(std::remove(CellMem->begin(), CellMem->end(), matrix[i][k]), CellMem->end());
						//vertcal line rule
						CellMem->erase(std::remove(CellMem->begin(), CellMem->end(), matrix[k][j]), CellMem->end());
						//grid rule
						CellMem->erase(
							std::remove(
								CellMem->begin(),
								CellMem->end(),
								matrix[(i / 3) * 3 + (k / 3)][(j / 3) * 3 + (k % 3)]
							),
							CellMem->end()
						);
					}
				}
				if (CellMem->size())
				{
					//Set first number in memory of cell as solution
					matrix[i][j] = (*CellMem)[0];
					displayMatrix[i][j]->setText(QString::number((*CellMem)[0]));
					CellMem->erase(CellMem->begin());
				}
				else
				{
					//Clear wrong solution of cell and go back on previous cell
					matrix[i][j] = 0;
					displayMatrix[i][j]->setText("");
					CellMem->resize(GRID_SIZE_SOLVE);
					std::iota(CellMem->begin(), CellMem->end(), 1);
					if (j){
						j--;
					}
					else
					{
						i--;
						j = GRID_SIZE_SOLVE - 1;
					}
					while (startMatrix[i][j])
					{
						if (j) {
							j--;
						}
						else
						{
							i--;
							j = GRID_SIZE_SOLVE - 1;
						}
					}
					//because of cycle FOR inc of J
					j--;
					
				}
			}
		}
	}
}