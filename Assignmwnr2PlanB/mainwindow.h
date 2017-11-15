#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPoint>
#include <QLabel>
#include <QAction>
#include <QMenu>
#include <QGraphicsRectItem>
#include <QPainter>
#include <QPixmap>
#include <QStaticText>
#include <QTableWidgetItem>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QFont>
#include <iostream>
#include <cstdlib>
#include "QStandardItemModel"
#include "QBrush"
#include "math.h"
#include "cell.h"
#include "data.h"

//QTableWidgetItem *cellSelected;

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:

    QMap<QString, Cell> cells;

    enum GameSelect {g0x0,g3x3,g9x9,g13x13};

    GameSelect gs;

    int cellWidth;
    int cellHeight;
    int fontSize;
    int gameSize;
    int moveNumber;
    QMap<QString, Cell> allMoves;

    QJsonObject currentGame;
    QString sId;
    QJsonArray aPuzzle;
    QJsonArray aGame;
    QJsonArray aMoves;


    Ui::MainWindow *ui;

public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void createNonClue(QPoint pos);
    void createClue(double dClue, double rClue);
    void createClue(QPoint pos,double dRight,double dDown);
    void createGameBoard();
    void setUpTesting();
    void setButtonAble();
    void setCurrentAnswer(double num);
    void setCurrentAnswer(double num, int row, int col);
    Cell getCell(int row, int col);
    void addCellToMovesMap();
    QVector<QString> splitString(const QString& str, const QChar& ch);

    QMap<QString,Cell> gamefileToQMap(const QJsonObject& gameFile);
    QJsonObject qmapToGamefile(const QMap<QString,Cell>& cells);

public slots:
    void menuRequest(const QPoint &pos);

private slots:

    void on_tableWidget_cellClicked(int row, int column);

    void on_pushButton_10_clicked();

    void on_pushButton_1_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_Game1_clicked();
    void on_pushButton_Game2_clicked();
    void on_pushButton_Game3_clicked();
    void on_pushButton_delete_clicked();
    void on_pushButton_LoadGame_clicked();
    void on_pushButton_check_clicked();
    void on_pushButton_save_clicked();
    void on_pushButton_newGame_clicked();
    void on_pushButton_undo_clicked();
    void on_pushButton_redo_clicked();
};

#endif // MAINWINDOW_H
