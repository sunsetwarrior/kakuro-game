#ifndef GAMEFILE_H
#define GAMEFILE_H

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include "cell.h"
#include "game.h"
#include "puzzle.h"
#include "moves.h"

class Gamefile
{
public:
    Gamefile();
    enum FileFormat{Json,Bin};

    Gamefile operator=(const Gamefile& other);

    bool loadGamefile(FileFormat ff);
    bool saveGamefile(FileFormat ff) const;

    QMap<QString,Cell> gamefileToQMap(const Gamefile& gameFile);
    Gamefile qmapToGamefile(const QMap<QString,Cell>& cells);

    QJsonObject read(const QJsonObject& json);
    void write(QJsonObject& json) const;

    QJsonObject getOId() const;
    void setOId(const QJsonObject &value);

    QJsonObject getOGamefile() const;
    void setOGamefile(const QJsonObject &value);

    QJsonObject getOGame() const;
    void setOGame(const QJsonObject &value);

    QJsonObject getOPuzzle() const;
    void setOPuzzle(const QJsonObject &value);

    QJsonObject getOMoves() const;
    void setOMoves(const QJsonObject &value);

    QString getSId() const;
    void setSId(const QString &value);

    QJsonArray getAPuzzle() const;
    void setAPuzzle(const QJsonArray &value);

    QJsonArray getAGame() const;
    void setAGame(const QJsonArray &value);

    QJsonArray getAMoves() const;
    void setAMoves(const QJsonArray &value);

private:
    /*
     * gamefile contains:
     * - id; made up of "<hex_right><hex_down><unique_variant_number>"
     * - puzzle; see puzzle.h
     * - game; see game.h
     * - moves; see moves.h
     */
    QString sId;
    QJsonObject oId;
    QJsonObject oGamefile;
    QJsonObject oGame;
    QJsonObject oPuzzle;
    QJsonObject oMoves;
    QJsonArray aGamefile;
    QJsonArray aPuzzle;
    QJsonArray aGame;
    QJsonArray aMoves;

//    Game game;
//    Puzzle puzzle;
//    Moves moves;
};

#endif // GAMEFILE_H
