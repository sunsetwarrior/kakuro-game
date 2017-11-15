#include "cell.h"



Cell::Cell()
{
    cell = {};
    clue = {};
    id = "";
    type = "";
    dRightOrAnswer = 0;
    dDownOrSolution = 0;
}

Cell::Cell(QString iId, QString tType, double dr, double dd)
{
    this->id = iId;
    this->type = tType;
    if(type.contains("a"))
    {
        dRightOrAnswer = 0;
        dDownOrSolution = dd;
    }
    else
    {
        this->dRightOrAnswer = dr;
        this->dDownOrSolution = dd;
    }
}

Cell::Cell(QString iId, QString tType, double dr, double dd, QString created)
{
    if(created == "Yes")
    {
        this->id = iId;
        this->type = tType;
        this->dRightOrAnswer = dr;
        this->dDownOrSolution = dd;
    }
}

QString Cell::getID() const
{
    return id;
}

/*void Cell::setID(const QString& id)
{
    this->id = id;
}*/

//Type shouldn't be changed after created.
QString Cell::getType() const
{
    return type;
}

/*void Cell::setType(const QString& type)
{
    this->type = type;
}*/

double Cell::getRightOrAnswer() const
{
    return dRightOrAnswer;
}

void Cell::setRightOrAnswer(const double &right)
{
    this->dRightOrAnswer = right;
}

/*void Cell::setRightOrAnswer(const double& right)
{
    this->dRightOrAnswer = right;
}*/

double Cell::getDownOrSolution() const
{
    return dDownOrSolution;
}

/*void Cell::setDownOrSolution(const double& down)
{
    this->dDownOrSolution = down;
}*/

void Cell::read(const QJsonObject& json)
{
    cell = json["cell"].toObject();
    id = cell["id"].toString();
    type = cell["type"].toString();
    if(type.contains("a"))
    {
        answer = cell["answer"].toObject();
        dRightOrAnswer = answer["answer"].toDouble();
        dDownOrSolution = answer["solution"].toDouble();
    }
    else
    {
        clue = cell["clue"].toObject();
        dRightOrAnswer = clue["right"].toDouble();
        dDownOrSolution = clue["down"].toDouble();
    }
}

void Cell::write(QJsonObject& json) const
{
    cell["id"] = id;
    cell["type"] = type;
    if(type.contains("a"))
    {
        cell["answer"] = dRightOrAnswer;
    }
    else
    {
        clue["right"] = dRightOrAnswer;
        clue["down"] = dDownOrSolution;
        cell["clue"] = clue;
    }
    json["cell"] = cell;
}

//void Cell::readClue(const QJsonObject& json)
//{
//    clue = json["clue"].toObject();
//};

//void Cell::writeClue(QJsonObject& json) const
//{
//    json["clue"] = clue;
//};

//void Clue::read(const QJsonObject& json) {
//    clue = json["clue"].toObject();
//};

//void Clue::write(QJsonObject& json) const {
//    json["clue"] = clue;
//};
