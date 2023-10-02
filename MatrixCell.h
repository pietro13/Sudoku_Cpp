#pragma once
#include <QLabel>
#include <QLayout>
#include <QWidget>
#include <Qt>


class MatrixCell : public QLabel
{
    Q_OBJECT

private:
    int ID = -1;
    int* activeID = nullptr;
    bool isChangeable;
    QString default = "";

public:
    MatrixCell(int setID,int* setActiveID, bool setChangeable, QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    ~MatrixCell();

    void activate();
    void deactivate();
    void setWrong();
    void setNewCell(int num);


signals:
    void clicked();

private slots:
    void mousePressEvent(QMouseEvent* event);
};


