#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_InsertSudokuWindow.h"
#include <QtWidgets/QMainWindow>
#include "MatrixCell.h"
#include <iostream>
#include <QKeyEvent>
#include <QFile>
#include <QTextStream>

namespace Ui {
    class InsertSudokuWindow;
};

class InsertSudokuWindow : public QMainWindow
{
    Q_OBJECT

public:
    static const int GRID_SIZE = 9;
    static const int DISPLAY_GRID_SIZE = GRID_SIZE * 2 + 1;
    

private:
    MatrixCell* DisplayMatrix[9][9];
    int matrix[9][9] = { 0 };
    int activeCellID = -1;
    QMainWindow* mainW ;

    

public:
    explicit InsertSudokuWindow( QMainWindow* parent = nullptr);
    ~InsertSudokuWindow();

signals:
    void setNewSudoku(int matrix[9][9]);
private:
    Ui::InsertSudokuWindow ui;

private slots:
    void on_setButton_clicked();
    void on_backButton_clicked();
    void deactive_cell();
    void keyPressEvent(QKeyEvent* e);
    void resizeEvent(QResizeEvent* event);


};