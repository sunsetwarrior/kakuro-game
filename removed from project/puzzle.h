#ifndef PUZZLE_H
#define PUZZLE_H

#include <QJsonArray>
#include <QJsonObject>
#include <QVector>
#include "puzzle.h"

class Puzzle
{
public:
    Puzzle();
    Puzzle(const QVector<double>& row);

    void read(const QJsonObject& json);
    void write(QJsonObject& json) const;
    double getCell();
    void setCell(double cell);

private:
    /*
     * puzzle is an array of row.
     * row is an array of double values.
     */
    QVector<QVector<double>> vPuzzle;
    QVector<double> vRow;
    QJsonArray puzzle;
    QJsonArray row;

    double dCell;
};

#endif // PUZZLE_H
