#include "SudokuWindow.h"
#include <QDebug>
#include <QFont>




SudokuWindow::SudokuWindow(QWidget *parent) : QMainWindow(parent)
{
    setMinimumSize(500,300);
    ui.setupUi(this);

    //Set horizontal lines in DISPALY_GRID 
    for (int j = 1; j < DISPLAY_GRID_SIZE; j+=2)
    {
        QFrame* lineH = new QFrame;
        lineH->setFrameShape(QFrame::HLine);
        lineH->setLineWidth(3);
        ui.gridLayout->addWidget(lineH, 0, j);   
    }

    // Counter for ID of LABEL in DISPLAY_GRID
    int IDcounter = 0;
    for (int i = 1; i < DISPLAY_GRID_SIZE; i++)
    {   
        if (i % 2)
        {   
            // Set vertical line in DISPLAY_GRID
            QFrame* lineL = new QFrame;
            lineL->setFrameShape(QFrame::VLine);
            ui.gridLayout->addWidget(lineL, i, 0);
            lineL->setLineWidth(3);
            for (int j = 1; j < DISPLAY_GRID_SIZE; j += 2)
            {
                // Set MatrixCell
                int currentVal = startMatrix[i / 2 ][j / 2];

                MatrixCell* cell = new MatrixCell(IDcounter++,&activeCellID, !bool(currentVal));
                cell->setAlignment(Qt::AlignCenter);
                if (currentVal) {
                    cell->setText(QString::number(currentVal));
                }
                ui.gridLayout->addWidget(cell, i, j);
                
                DisplayMatrix[i / 2][j / 2] = cell;
                connect(cell, SIGNAL(clicked()),this,SLOT(deactive_cell()));


                // Set vertical line in DISPLAY_GRID
                QFrame* lineR = new QFrame;
                lineR->setFrameShape(QFrame::VLine);
                if (!((j+1)%6)) 
                {
                    lineR->setLineWidth(3);
                }
                ui.gridLayout->addWidget(lineR, i, j + 1);  
            }
        }
        else
        {
            //Set horizontal lines in DISPALY_GRID 
            for (int j = 1; j < DISPLAY_GRID_SIZE; j+=2)
            {
                QFrame* lineH = new QFrame;
                lineH->setFrameShape(QFrame::HLine);
                if (!(i%6))
                {
                    lineH->setLineWidth(3);
                }
                ui.gridLayout->addWidget(lineH, i, j);
            }
        }
    }
    this->resizeEvent(nullptr);
}

void SudokuWindow::on_checkButton_clicked()
{
    checked = true;
    activeCellID = -1;
    
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            if(!resMatrix[i][j])
            {
                DisplayMatrix[i][j]->setWrong();
            }
        }
    }
    
}

void SudokuWindow::on_newSudokuButton_clicked()
{    
    InsertSudokuWindow* nw = new InsertSudokuWindow(this);
    connect(nw, &InsertSudokuWindow::setNewSudoku, this, &SudokuWindow::setNewSudoku);

    nw->show();
    this->hide();

}

void SudokuWindow::on_solveButton_clicked()
{
    BackTrackingMethod(resMatrix, DisplayMatrix,startMatrix);
}

void SudokuWindow::deactive_cell()
{
    if (activeCellID != -1) 
    {
        DisplayMatrix[activeCellID / GRID_SIZE][activeCellID % GRID_SIZE]->deactivate();
    }
    else if (checked)
    {
        checked = false;
        for (int i = 0; i < GRID_SIZE; i++)
        {
            for (int j = 0; j < GRID_SIZE; j++)
            {
                DisplayMatrix[i][j]->deactivate();
            }
        }
    }
    
}

void SudokuWindow::keyPressEvent(QKeyEvent* e)
{
    if (activeCellID != -1)
    {
        if (e->key() > Qt::Key_0 && e->key() <= Qt::Key_9)
        {
            DisplayMatrix[activeCellID / GRID_SIZE][activeCellID % GRID_SIZE]->setText(e->text());
            resMatrix[activeCellID / GRID_SIZE][activeCellID % GRID_SIZE] = e->text().toInt();
        }
        else if (e->key() == Qt::Key_Backspace || e->key() == Qt::Key_Delete) {
            DisplayMatrix[activeCellID / GRID_SIZE][activeCellID % GRID_SIZE]->setText("");
            resMatrix[activeCellID / GRID_SIZE][activeCellID % GRID_SIZE] = 0;
        }

    }
}


void SudokuWindow::setNewSudoku(int matrix[GRID_SIZE][GRID_SIZE])
{
    
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            DisplayMatrix[i][j]->setNewCell(matrix[i][j]);
            startMatrix[i][j] = matrix[i][j];
            resMatrix[i][j] = matrix[i][j];
        }
    }
}

void SudokuWindow::resizeEvent(QResizeEvent* event)
{
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
                int w = this->width();
                int h = this->height();

                auto font = this->DisplayMatrix[i][j]->font();
                font.setPointSize((w < h ? w / 33 : h / 33));
                this->DisplayMatrix[i][j]->setFont(font);
        }
    }    
}




SudokuWindow::~SudokuWindow()
{}
