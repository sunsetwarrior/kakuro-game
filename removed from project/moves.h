#ifndef MOVES_H
#define MOVES_H

#include <QJsonArray>
#include <QJsonObject>
#include <QVector>
#include "moves.h"

class Moves
{
public:
    Moves();

    void read(const QJsonObject& json);
    void write(QJsonObject& json) const;

private:
    /*
     * moves is an array of QString
     * format is "<grid_right>_<grid_down>_<answer>"
     * eg. "2_2_1" for 33000012
     */
    QVector<QString> vMoves;
    QJsonArray moves;
};

#endif // MOVES_H
