#ifndef GAME_H
#define GAME_H

#include <QJsonArray>
#include <QJsonObject>
#include <QVector>
#include <QString>
#include <QMap>
#include <math.h>
#include "cell.h"

class Game
{
public:
    Game();

//    void read(const QJsonObject& json);
//    void write(QJsonObject& json) const;

//    QMap<QString,Cell> gameToQMap();
//    void qmapToGame(QMap<QString,Cell>& cells);

private:
    /*
     * game is an array of row.
     * row is an array of cell.
     */
    QVector<QVector<QJsonObject>> vGame;
    QVector<QJsonObject> vRow;
    QJsonObject oCell;
    QJsonObject oGame;
    QJsonObject oRow;
    QJsonArray aGame;
    QJsonArray aRow;
    QMap<QString,Cell> mCells;
};

#endif // GAME_H
