#include "InsertSudokuWindow.h"


InsertSudokuWindow::InsertSudokuWindow( QMainWindow* parent) : QMainWindow(nullptr)
{
    mainW = parent; 

    

    setMinimumSize(500, 300);
    ui.setupUi(this);
    for (int j = 1; j < DISPLAY_GRID_SIZE; j += 2)
    {
        QFrame* lineH = new QFrame;
        lineH->setFrameShape(QFrame::HLine);
        lineH->setLineWidth(3);
        ui.gridLayout->addWidget(lineH, 0, j);
    }
    int IDcounter = 0;
    for (int i = 1; i < DISPLAY_GRID_SIZE; i++)
    {
        if (i % 2)
        {
            QFrame* lineL = new QFrame;
            lineL->setFrameShape(QFrame::VLine);
            ui.gridLayout->addWidget(lineL, i, 0);
            lineL->setLineWidth(3);
            for (int j = 1; j < DISPLAY_GRID_SIZE; j += 2)
            {
                int currentVal = 0;

                MatrixCell* label = new MatrixCell(IDcounter++, &activeCellID, !bool(currentVal));
                label->setAlignment(Qt::AlignCenter);
                if (currentVal) {
                    label->setText(QString::number(currentVal));
                }
                ui.gridLayout->addWidget(label, i, j);

                DisplayMatrix[i / 2][j / 2] = label;
                connect(label, SIGNAL(clicked()), this, SLOT(deactive_cell()));

                QFrame* lineR = new QFrame;
                lineR->setFrameShape(QFrame::VLine);
                if (!((j + 1) % 6))
                {
                    lineR->setLineWidth(3);
                }
                ui.gridLayout->addWidget(lineR, i, j + 1);
            }
        }
        else
        {
            for (int j = 1; j < DISPLAY_GRID_SIZE; j += 2)
            {
                QFrame* lineH = new QFrame;
                lineH->setFrameShape(QFrame::HLine);
                if (!(i % 6))
                {
                    lineH->setLineWidth(3);
                }
                ui.gridLayout->addWidget(lineH, i, j);
            }
        }
    }
}

void InsertSudokuWindow::deactive_cell()
{
    if (activeCellID != -1)
    {
        DisplayMatrix[activeCellID / GRID_SIZE][activeCellID % GRID_SIZE]->deactivate();
    }
    

}

void InsertSudokuWindow::keyPressEvent(QKeyEvent* e)
{
    if (activeCellID != -1)
    {
        
        if (e->key() > Qt::Key_0 && e->key() <= Qt::Key_9)
        {
            DisplayMatrix[activeCellID / GRID_SIZE][activeCellID % GRID_SIZE]->setText(e->text());
            matrix[activeCellID / GRID_SIZE][activeCellID % GRID_SIZE] = e->text().toInt();
        }
        else if (e->key() == Qt::Key_Backspace || e->key() == Qt::Key_Delete) {
            DisplayMatrix[activeCellID / GRID_SIZE][activeCellID % GRID_SIZE]->setText("");
            matrix[activeCellID / GRID_SIZE][activeCellID % GRID_SIZE] = 0;
        }

    }
}

void InsertSudokuWindow::on_setButton_clicked()
{
    
    emit setNewSudoku(matrix);
    mainW->show();
    this->close();
}

void InsertSudokuWindow::on_backButton_clicked()
{
    mainW->show();
    this->close();
}


void InsertSudokuWindow::resizeEvent(QResizeEvent* event)
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


InsertSudokuWindow::~InsertSudokuWindow() {
	
}