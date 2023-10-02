#include "MatrixCell.h"




MatrixCell::MatrixCell(int setID,int* setActiveID,bool setChangeable, QWidget* parent, Qt::WindowFlags f)
    : QLabel(parent) 
{
    
    ID = setID;
    activeID = setActiveID;
    isChangeable = setChangeable;
    if (isChangeable)
    {
        default += "background-color: white;";
    }

    setStyleSheet(default);
}

MatrixCell::~MatrixCell() {}


void MatrixCell::mousePressEvent(QMouseEvent* event) 
{
    emit clicked();
    activate();
    
}

void MatrixCell::activate()
{
    *activeID = ID;
    setStyleSheet(default + "border: 4px solid green;");
}

void MatrixCell::deactivate() 
{
    *activeID = -1;
    setStyleSheet(default);
}

void MatrixCell::setWrong() 
{
    if (isChangeable) {
        setStyleSheet(default + "background-color: red");
    }
    else {
        setStyleSheet(default + "color: red");
    }
}

void MatrixCell::setNewCell(int num)
{
    if (num)
    {
        isChangeable = false;
        default = "";
        setText(QString::number(num));
        
    }
    else
    {
        isChangeable = true;
        default = "background-color: white;";
    }
    setStyleSheet(default);
    
    
}