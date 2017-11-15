#ifndef CELL_H
#define CELL_H

#include <QString>
#include <QJsonObject>
#include <iostream>
#include <cstdlib>

class Cell
{
private:
    //The id should be of the format 'x_y'
    QString id;

    //Used for the type of cell it is. a for answer cell, b for blank, and c for clue cell.
    QString type;

    //If clue, this is the Right clue, else if it is Answer it is the answer. Else = 0
    double dRightOrAnswer;
//    double num1;

    //If clue, this is the down clue. Else = 0
    double dDownOrSolution;
//    double num2;

    QJsonObject cell;
    QJsonObject clue;
    QJsonObject answer;

public:
    Cell();

    explicit Cell(QString id, QString type, double n1, double n2);
//    explicit Cell(QString id, QString type, double n1);

    Cell(QString iId, QString tType, double dr, double dd, QString created);

    // id should only be set on creation.
    QString getID() const;
    //void setID(QString id);

    //Type shouldn't be changed after created.
    QString getType() const;
    //void setType(QString type);

    double getRightOrAnswer() const;
    void setRightOrAnswer(const double &right);

    double getDownOrSolution() const;
    //void setDown(double down);

    double getAnswer() const;
    void setAnswer(double answer);

    void read(const QJsonObject& json);
    void write(QJsonObject& json) const;

};


class Clue
{
public:
    Clue();

private:
    QJsonObject clue;
    double right;
    double down;
};

class Answer
{
public:
    Answer();

private:
    QJsonObject answer;
    double ans;
    double sol;
};

#endif // CELL_H
