#pragma once

// QT
#include <QtWidgets/QMainWindow>
#include <QKeyEvent>
#include <QFile>
#include <QTextStream>

// STD
#include <iostream>

// Headers
#include "MatrixCell.h"
#include "InsertSudokuWindow.h"
#include "SolvingMethods.h"

// Ui
#include "ui_SudokuWindow.h"





class SudokuWindow : public QMainWindow
{
    Q_OBJECT

public:
    static const int GRID_SIZE = 9;
    static const int DISPLAY_GRID_SIZE = GRID_SIZE * 2 + 1;


private:
    MatrixCell* DisplayMatrix[9][9];
    int resMatrix[9][9] = { 0 };
    int startMatrix[9][9] = { 0 };
    int activeCellID = -1;
    bool checked = false;
    QFile saveFile;


public:
    SudokuWindow(QWidget *parent = nullptr);
    ~SudokuWindow();

    

private:
    Ui::SudokuWindowClass ui;

private slots:
    void on_checkButton_clicked();
    void on_newSudokuButton_clicked();
    void on_solveButton_clicked();
    void deactive_cell();
    void keyPressEvent(QKeyEvent* e);
    void setNewSudoku(int matrix[GRID_SIZE][GRID_SIZE]);
    void resizeEvent(QResizeEvent* event);
};
