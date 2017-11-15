#include "moves.h"

Moves::Moves()
{
    vMoves = {};
    moves = {};
}

void Moves::read(const QJsonObject& json) {
    moves = json["moves"].toArray();
};

void Moves::write(QJsonObject& json) const {
    json["moves"] = moves;
};
