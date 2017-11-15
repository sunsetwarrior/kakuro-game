#include "puzzle.h"

Puzzle::Puzzle()
{
    vPuzzle = {};
    vRow = {};
    puzzle = {};
    row = {};
    dCell = 0;
}

void Puzzle::read(const QJsonObject& json) {
    puzzle = json["puzzle"].toArray();
    for(int i = 0; i < puzzle.size(); i++)
    {
        row = puzzle[i].toArray();
        for(int j = 0; j < row.size(); j++)
        {
            vRow.append(row[j].toDouble());
        }
        vPuzzle.append(vRow);
    }
};

void Puzzle::write(QJsonObject& json) const {
    for(int i = 0; i < vPuzzle.size(); i++)
    {
        QVector<double> tempRow = vPuzzle.at(i);
        for(int j = 0; j < tempRow.size(); j++)
        {
            row[j] = tempRow[j];
        }
        puzzle[i] = row;
    }
    json["puzzle"] = puzzle;
};

double Puzzle::getCell()
{
    return dCell;
};

void Puzzle::setCell(double cell)
{
    dCell = cell;
};

