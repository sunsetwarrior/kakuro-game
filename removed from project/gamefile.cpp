#include "gamefile.h"

Gamefile::Gamefile()
{
    sId = "";
    oId = {};
    oGamefile = {};
    oGame = {};
    oPuzzle = {};
    oMoves = {};
    aGamefile = {};
    aPuzzle = {};
    aGame = {};
    aMoves = {};
}

//Gamefile::operator=(const Gamefile& other)
//{
//    setOGamefile(other.getOGamefile());
//    setOId(other.getOId());
//    setOPuzzle(other.getOPuzzle());
//    setOGame(other.getOGame());
//    setOMoves(other.getOMoves());
//    aGamefile = oGamefile.find("gamefile").value().toArray();
//    sId = oGamefile.find("gamefile").value().toArray().at(0).toObject().find("id").value().toString();
//    aPuzzle = oGamefile.find("gamefile").value().toArray().at(1).toObject().find("puzzle").value().toArray();
//    aGame = oGamefile.find("gamefile").value().toArray().at(2).toObject().find("game").value().toArray();
//    aMoves = oGamefile.find("gamefile").value().toArray().at(3).toObject().find("moves").value().toArray();
//};

QMap<QString,Cell> Gamefile::gamefileToQMap(const Gamefile& gameFile)
{
    oGamefile = gameFile.getOGamefile();
    QMap<QString,Cell> cells = {};
    sId = oGamefile.find("gamefile").value().toArray().at(0).toObject().find("id").value().toString();
    aPuzzle = oGamefile.find("gamefile").value().toArray().at(1).toObject().find("puzzle").value().toArray();
    aGame = oGamefile.find("gamefile").value().toArray().at(2).toObject().find("game").value().toArray();
    aMoves = oGamefile.find("gamefile").value().toArray().at(3).toObject().find("moves").value().toArray();
    QJsonArray::ConstIterator gameIt = {};
    QJsonArray::ConstIterator gRowIt = {};
    QJsonArray::ConstIterator puzzleIt = {};
    QJsonArray::ConstIterator pRowIt = {};
    puzzleIt = aPuzzle.begin();
    for(gameIt = aGame.begin();gameIt != aGame.end(); gameIt++, puzzleIt++)
    {
        for(gRowIt = aGame.at(gameIt.i).toObject().find("row").value().toArray().begin();gRowIt != aGame.at(gameIt.i).toObject().find("row").value().toArray().end();gRowIt++, pRowIt++)
        {
            QString tempId = gRowIt.a->at(gRowIt.i).toObject().find("id").value().toString();
            QString tempType = gRowIt.a->at(gRowIt.i).toObject().find("type").value().toString();
            double tempRorA = 0;
            double tempDorS = 0;
            if(tempType.contains("a"))
            {
                tempRorA = gRowIt.a->at(gRowIt.i).toObject().find("answer").value().toDouble();
//                tempDorS = rowIt.a->at(rowIt.i).toObject().find("solution").value().toDouble();
                tempDorS = pRowIt.a->at(pRowIt.i).toDouble();
            }
            else
            {
                tempRorA = gRowIt.a->at(gRowIt.i).toObject().find("right").value().toDouble();
                tempDorS = gRowIt.a->at(gRowIt.i).toObject().find("down").value().toDouble();
            }
            cells.insert(tempId,Cell(tempId,tempType,tempRorA,tempDorS));
        }
    }

    return cells;
}

Gamefile Gamefile::qmapToGamefile(const QMap<QString,Cell>& cells)
{
    QMap<QString,Cell>::const_iterator it = {};
    it = cells.cbegin();

    if(it != cells.cend())
    {

    }

    return *this;
//    double gameSize = sqrt(cells.size());
//    int currentRow = 0;
//    int mapIndex = 1;
//    oGame = {};
//    aGame = {};
//    for(Cell mCell: cells)
//    {
//        aRow = {};
//        oRow = {};
//        oCell = {};
//        int tempRow = mCell.getID().split("_").first().toInt();
//        int tempCol = mCell.getID().split("_").last().toInt();
//        oCell.insert("id",mCell.getID());
//        oCell.insert("type",mCell.getType());
//        if(mCell.getType()=="a")
//        {
//            oCell.insert("answer",mCell.getRightOrAnswer());
//            oCell.insert("solution",mCell.getDownOrSolution());
//        } else {
//            oCell.insert("right",mCell.getRightOrAnswer());
//            oCell.insert("down",mCell.getDownOrSolution());
//        }
//        aRow.insert(tempCol,QJsonObject(oCell));
//        if(mapIndex == int(gameSize))
//        {
//            oRow.insert("row",QJsonValue(aRow));
//            aGame.insert(tempRow,QJsonObject(oRow));
//            mapIndex = 1;
//            currentRow++;
//        } else {
//            mapIndex++;
//        }
//    }
//    oGame.insert("game",QJsonValue(aGame));
}


/*
 * reads a file from the directory where the application is running from
 */
bool Gamefile::loadGamefile(Gamefile::FileFormat ff) {
    QFile inFile(ff == Json
                 ? QString(sId + ".json")
        : QString(sId + ".dat"));

    if(!inFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open the gamefile.");
        return false;
    }

    QByteArray data = inFile.readAll();

    QJsonDocument loadDoc(ff == Json
                          ? QJsonDocument::fromJson(data)
                          : QJsonDocument::fromBinaryData(data));
    Gamefile::read(loadDoc.object());
    return true;
};

/*
 * writes a file to the directory where the application is running from
 */
bool Gamefile::saveGamefile(Gamefile::FileFormat ff) const {
    QFile outFile(ff == Json
                  ? QString(sId + ".json")
        : QString(sId + ".dat"));

    if(!outFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open the gamefile.");
        return false;
    }

    QJsonObject game;
    Gamefile::write(game);
    QJsonDocument saveDoc(game);
    outFile.write(ff == Json ? saveDoc.toJson() : saveDoc.toBinaryData());
    return true;
};

QJsonObject Gamefile::read(const QJsonObject& json) {
    setOGamefile(json);
//    aGamefile = oGamefile["gamefile"].toArray();
//    oId = json["id"].toObject();
//    sId = oId.value("id").toString();
//    oGame = json["game"].toObject();
//    aGame = oGame["game"].toArray();
//    oPuzzle = json["puzzle"].toObject();
//    aPuzzle = oPuzzle["puzzle"].toArray();
//    oMoves = json["moves"].toObject();
//    aMoves = oMoves["moves"].toArray();
    return oGamefile;
};

void Gamefile::write(QJsonObject& json) const {
    QJsonArray tempGamefile = {};
    oId["id"] = QJsonValue(sId);
    tempGamefile.append(oId["id"]);
    oGame["game"] = QJsonValue(aGame);
    tempGamefile.append(oGame["game"]);
    oPuzzle["puzzle"] = QJsonValue(aPuzzle);
    tempGamefile.append(oPuzzle["puzzle"]);
    oMoves["moves"] = QJsonValue(aMoves);
    tempGamefile.append(oMoves["moves"]);
    json["gamefile"] = tempGamefile;
}

QJsonObject Gamefile::getOId() const
{
    return oId;
}

void Gamefile::setOId(const QJsonObject &value)
{
    oId = value;
}

QJsonObject Gamefile::getOGamefile() const
{
    return oGamefile;
}

void Gamefile::setOGamefile(const QJsonObject &value)
{
    oGamefile = value;
}

QJsonObject Gamefile::getOGame() const
{
    return oGame;
}

void Gamefile::setOGame(const QJsonObject &value)
{
    oGame = value;
}

QJsonObject Gamefile::getOPuzzle() const
{
    return oPuzzle;
}

void Gamefile::setOPuzzle(const QJsonObject &value)
{
    oPuzzle = value;
}

QJsonObject Gamefile::getOMoves() const
{
    return oMoves;
}

void Gamefile::setOMoves(const QJsonObject &value)
{
    oMoves = value;
}

QString Gamefile::getSId() const
{
    return sId;
}

void Gamefile::setSId(const QString &value)
{
    sId = value;
}

QJsonArray Gamefile::getAPuzzle() const
{
    return aPuzzle;
}

void Gamefile::setAPuzzle(const QJsonArray &value)
{
    aPuzzle = value;
}

QJsonArray Gamefile::getAGame() const
{
    return aGame;
}

void Gamefile::setAGame(const QJsonArray &value)
{
    aGame = value;
}

QJsonArray Gamefile::getAMoves() const
{
    return aMoves;
}

void Gamefile::setAMoves(const QJsonArray &value)
{
    aMoves = value;
}
