#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    ui->tableWidget-> setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tableWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(menuRequest(QPoint)));

    currentGame = {};
    //possible values frame
    ui->tableWidget->hide();
    ui->gridFrame->hide();
    ui->WinFrame->hide();
    ui->Game_Menu_Frame->hide();
    ui->Undo_redo_Frame->hide();

    moveNumber = 0;
    allMoves = {};
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createGameBoard()
{
    ui->tableWidget->show();
    ui->Game_Menu_Frame->show();
    ui->Undo_redo_Frame->show();
    setUpTesting(); // <----- Remove when load, and save is done.
    gameSize = sqrt(cells.size());
    ui->tableWidget->setRowCount(gameSize);
    ui->tableWidget->setColumnCount(gameSize);

    //Cells Setup
    fontSize = 10;
    cellHeight = 5* fontSize;
    cellWidth = 7* fontSize;
    Cell emptyCell("","",0,0);
    QTableWidgetItem	*value;
    QFont	f("Consolas");
    f.setPointSize(14);
    QString cId = "";
    QMap<QString, Cell>::iterator it{};
    Cell& pCell = emptyCell;

    //Sets up cells
    for(int	row	=	0;	row	<	gameSize;	row++)
    {
        for(int	col	=	0;	col	<	gameSize;	col++)
        {
            value = new	QTableWidgetItem(QString(" "));
            value->setFont(f);
            value->setTextAlignment(Qt::AlignCenter);
            value->setFlags(value->flags()^Qt::ItemIsEditable);
            ui->tableWidget->setRowHeight(row,cellHeight);
            ui->tableWidget->setColumnWidth(col,cellWidth);
            ui->tableWidget->setItem(row,col,value);

            cId = QString::number(row) + "_" + QString::number(col);

            if(cells.find(cId) != cells.end())
            {
                it = cells.find(cId);

                pCell = it.value();

                if	(pCell.getType().contains("b"))
                {
                    createNonClue(*new QPoint(row, col));
                }
                else if(pCell.getType().contains("c"))
                {
                    createClue(*new QPoint(row, col), pCell.getRightOrAnswer(),pCell.getDownOrSolution());
                }
                /*else if(pCell.getType().contains("a"))
                {

                }*/

            }
        }
    }
}

void MainWindow::setUpTesting()
{
    cells = {}; // <--- TODO: Re-Assigned to Alistairs passed QMap

    //USED FOR TESTING PURPOSE (3x3). Remove when above TODO is done.

    if(gs==g0x0)
    {
        // placeholder to build an empty grid to allow for selection of a gamefile using filepicker
        cells = {};
        //        cells.insert("0_0", Cell("0_0","a",0,0));
    }
    else if(gs==g3x3)
    {
        cells = {};
        cells.insert( "0_0",Cell( "0_0", "b",0,0));
        cells.insert( "0_1",Cell( "0_1", "c",0,12));
        cells.insert( "0_2",Cell( "0_2", "c",0,7));
        cells.insert( "1_0",Cell( "1_0", "c",15,0));
        cells.insert( "1_1",Cell( "1_1", "a",0,9));
        cells.insert( "1_2",Cell( "1_2", "a",0,6));
        cells.insert( "2_0",Cell( "2_0", "c",4,0));
        cells.insert( "2_1",Cell( "2_1", "a",0,3));
        cells.insert( "2_2",Cell( "2_2", "a",0,1));
    }
    else if(gs==g9x9)
    {
        cells = {};
        cells.insert( "0_0",Cell( "0_0", "b",0,0));
        cells.insert( "0_1",Cell( "0_1", "b",0,0));
        cells.insert( "0_2",Cell( "0_2", "b",0,0));
        cells.insert( "0_3",Cell( "0_3", "c",0,13));
        cells.insert( "0_4",Cell( "0_4", "c",0,39));
        cells.insert( "0_5",Cell( "0_5", "b",0,0));
        cells.insert( "0_6",Cell( "0_6", "b",0,0));
        cells.insert( "0_7",Cell( "0_7", "b",0,0));
        cells.insert( "0_8",Cell( "0_8", "b",0,0));
        cells.insert( "1_0",Cell( "1_0", "b",0,0));
        cells.insert( "1_1",Cell( "1_1", "b",0,0));
        cells.insert( "1_2",Cell( "1_2", "c",17,0));
        cells.insert( "1_3",Cell( "1_3", "a",0,9));
        cells.insert( "1_4",Cell( "1_4", "a",0,8));
        cells.insert( "1_5",Cell( "1_5", "b",0,0));
        cells.insert( "1_6",Cell( "1_6", "b",0,0));
        cells.insert( "1_7",Cell( "1_7", "b",0,0));
        cells.insert( "1_8",Cell( "1_8", "b",0,0));
        cells.insert( "2_0",Cell( "2_0", "b",0,0));
        cells.insert( "2_1",Cell( "2_1", "c",0,4));
        cells.insert( "2_2",Cell( "2_2", "c",5,17));
        cells.insert( "2_3",Cell( "2_3", "a",0,4));
        cells.insert( "2_4",Cell( "2_4", "a",0,1));
        cells.insert( "2_5",Cell( "2_5", "c",0,13));
        cells.insert( "2_6",Cell( "2_6", "c",0,12));
        cells.insert( "2_7",Cell( "2_7", "b",0,0));
        cells.insert( "2_8",Cell( "2_8", "b",0,0));
        cells.insert( "3_0",Cell( "3_0", "c",6,0));
        cells.insert( "3_1",Cell( "3_1", "a",0,1));
        cells.insert( "3_2",Cell( "3_2", "a",0,5));
        cells.insert( "3_3",Cell( "3_3", "c",7,0));
        cells.insert( "3_4",Cell( "3_4", "a",0,2));
        cells.insert( "3_5",Cell( "3_5", "a",0,4));
        cells.insert( "3_6",Cell( "3_6", "a",0,1));
        cells.insert( "3_7",Cell( "3_7", "b",0,0));
        cells.insert( "3_8",Cell( "3_8", "b",0,0));
        cells.insert( "4_0",Cell( "4_0", "c",5,0));
        cells.insert( "4_1",Cell( "4_1", "a",0,3));
        cells.insert( "4_2",Cell( "4_2", "a",0,2));
        cells.insert( "4_3",Cell( "4_3", "c",17,14));
        cells.insert( "4_4",Cell( "4_4", "a",0,3));
        cells.insert( "4_5",Cell( "4_5", "a",0,9));
        cells.insert( "4_6",Cell( "4_6", "a",0,5));
        cells.insert( "4_7",Cell( "4_7", "c",0,6));
        cells.insert( "4_8",Cell( "4_8", "b",0,0));
        cells.insert( "5_0",Cell( "5_0", "b",0,0));
        cells.insert( "5_1",Cell( "5_1", "c",15,0));
        cells.insert( "5_2",Cell( "5_2", "a",0,4));
        cells.insert( "5_3",Cell( "5_3", "a",0,6));
        cells.insert( "5_4",Cell( "5_4", "a",0,5));
        cells.insert( "5_5",Cell( "5_5", "c",7,0));
        cells.insert( "5_6",Cell( "5_6", "a",0,2));
        cells.insert( "5_7",Cell( "5_7", "a",0,5));
        cells.insert( "5_8",Cell( "5_8", "b",0,0));
        cells.insert( "6_0",Cell( "6_0", "b",0,0));
        cells.insert( "6_1",Cell( "6_1", "c",23,0));
        cells.insert( "6_2",Cell( "6_2", "a",0,6));
        cells.insert( "6_3",Cell( "6_3", "a",0,8));
        cells.insert( "6_4",Cell( "6_4", "a",0,9));
        cells.insert( "6_5",Cell( "6_5", "c",5,8));
        cells.insert( "6_6",Cell( "6_6", "a",0,4));
        cells.insert( "6_7",Cell( "6_7", "a",0,1));
        cells.insert( "6_8",Cell( "6_8", "b",0,0));
        cells.insert( "7_0",Cell( "7_0", "b",0,0));
        cells.insert( "7_1",Cell( "7_1", "b",0,0));
        cells.insert( "7_2",Cell( "7_2", "b",0,0));
        cells.insert( "7_3",Cell( "7_3", "c",7,0));
        cells.insert( "7_4",Cell( "7_4", "a",0,4));
        cells.insert( "7_5",Cell( "7_5", "a",0,3));
        cells.insert( "7_6",Cell( "7_6", "b",0,0));
        cells.insert( "7_7",Cell( "7_7", "b",0,0));
        cells.insert( "7_8",Cell( "7_8", "b",0,0));
        cells.insert( "8_0",Cell( "8_0", "b",0,0));
        cells.insert( "8_1",Cell( "8_1", "b",0,0));
        cells.insert( "8_2",Cell( "8_2", "b",0,0));
        cells.insert( "8_3",Cell( "8_3", "c",12,0));
        cells.insert( "8_4",Cell( "8_4", "a",0,7));
        cells.insert( "8_5",Cell( "8_5", "a",0,5));
        cells.insert( "8_6",Cell( "8_6", "b",0,0));
        cells.insert( "8_7",Cell( "8_7", "b",0,0));
        cells.insert( "8_8",Cell( "8_8", "b",0,0));
    }
    else if(gs==g13x13)
    {
        cells = {};
        cells.insert( "0_0",Cell( "0_0", "b",0,0));
        cells.insert( "0_1",Cell( "0_1", "b",0,0));
        cells.insert( "0_2",Cell( "0_2", "b",0,0));
        cells.insert( "0_3",Cell( "0_3", "b",0,0));
        cells.insert( "0_4",Cell( "0_4", "c",0,17));
        cells.insert( "0_5",Cell( "0_5", "c",0,24));
        cells.insert( "0_6",Cell( "0_6", "b",0,0));
        cells.insert( "0_7",Cell( "0_7", "b",0,0));
        cells.insert( "0_8",Cell( "0_8", "c",0,3));
        cells.insert( "0_9",Cell( "0_9", "c",0,29));
        cells.insert( "0_10",Cell( "0_10", "b",0,0));
        cells.insert( "0_11",Cell( "0_11", "b",0,0));
        cells.insert( "0_12",Cell( "0_12", "b",0,0));//valid
        cells.insert( "1_0",Cell( "1_0", "b",0,0));
        cells.insert( "1_1",Cell( "1_1", "b",0,0));
        cells.insert( "1_2",Cell( "1_2", "c",0,3));
        cells.insert( "1_3",Cell( "1_3", "c",15,6));
        cells.insert( "1_4",Cell( "1_4", "a",0,8));
        cells.insert( "1_5",Cell( "1_5", "a",0,7));
        cells.insert( "1_6",Cell( "1_6", "b",0,0));
        cells.insert( "1_7",Cell( "1_7", "c",7,0));
        cells.insert( "1_8",Cell( "1_8", "a",0,2));
        cells.insert( "1_9",Cell( "1_9", "a",0,5));
        cells.insert( "1_10",Cell( "1_10", "b",0,0));
        cells.insert( "1_11",Cell( "1_11", "c",0,16));
        cells.insert( "1_12",Cell( "1_12", "c",0,4));//valid
        cells.insert( "2_0",Cell( "2_0", "b",0,0));
        cells.insert( "2_1",Cell( "2_1", "c",22,0));
        cells.insert( "2_2",Cell( "2_2", "a",0,2));
        cells.insert( "2_3",Cell( "2_3", "a",0,3));
        cells.insert( "2_4",Cell( "2_4", "a",0,9));
        cells.insert( "2_5",Cell( "2_5", "a",0,8));
        cells.insert( "2_6",Cell( "2_6", "c",0,17));
        cells.insert( "2_7",Cell( "2_7", "c",10,0));
        cells.insert( "2_8",Cell( "2_8", "a",0,1));
        cells.insert( "2_9",Cell( "2_9", "a",0,9));
        cells.insert( "2_10",Cell( "2_10", "c",10,34));
        cells.insert( "2_11",Cell( "2_11", "a",0,7));
        cells.insert( "2_12",Cell( "2_12", "a",0,3));//valid
        cells.insert( "3_0",Cell( "3_0", "b",0,0));
        cells.insert( "3_1",Cell( "3_1", "c",3,0));
        cells.insert( "3_2",Cell( "3_2", "a",0,1));
        cells.insert( "3_3",Cell( "3_3", "a",0,2));
        cells.insert( "3_4",Cell( "3_4", "c",17,10));
        cells.insert( "3_5",Cell( "3_5", "a",0,9));
        cells.insert( "3_6",Cell( "3_6", "a",0,8));
        cells.insert( "3_7",Cell( "3_7", "c",0,4));
        cells.insert( "3_8",Cell( "3_8", "c",25,0));
        cells.insert( "3_9",Cell( "3_9", "a",0,8));
        cells.insert( "3_10",Cell( "3_10", "a",0,7));
        cells.insert( "3_11",Cell( "3_11", "a",0,9));
        cells.insert( "3_12",Cell( "3_12", "a",0,1));//valid
        cells.insert( "4_0",Cell( "4_0", "b",0,0));
        cells.insert( "4_1",Cell( "4_1", "b",0,0));
        cells.insert( "4_2",Cell( "4_2", "c",3,0));
        cells.insert( "4_3",Cell( "4_3", "a",0,1));
        cells.insert( "4_4",Cell( "4_4", "a",0,2));
        cells.insert( "4_5",Cell( "4_5", "c",12,11));
        cells.insert( "4_6",Cell( "4_6", "a",0,9));
        cells.insert( "4_7",Cell( "4_7", "a",0,3));
        cells.insert( "4_8",Cell( "4_8", "c",11,11));
        cells.insert( "4_9",Cell( "4_9", "a",0,7));
        cells.insert( "4_10",Cell( "4_10", "a",0,4));
        cells.insert( "4_11",Cell( "4_11", "c",0,4));
        cells.insert( "4_12",Cell( "4_12", "b",0,0));
        cells.insert( "5_0",Cell( "5_0", "b",0,0));
        cells.insert( "5_1",Cell( "5_1", "b",0,0));
        cells.insert( "5_2",Cell( "5_2", "b",0,0));
        cells.insert( "5_3",Cell( "5_3", "c",9,34));
        cells.insert( "5_4",Cell( "5_4", "a",0,4));
        cells.insert( "5_5",Cell( "5_5", "a",0,5));
        cells.insert( "5_6",Cell( "5_6", "c",6,0));
        cells.insert( "5_7",Cell( "5_7", "a",0,1));
        cells.insert( "5_8",Cell( "5_8", "a",0,5));
        cells.insert( "5_9",Cell( "5_9", "c",12,11));
        cells.insert( "5_10",Cell( "5_10", "a",0,9));
        cells.insert( "5_11",Cell( "5_11", "a",0,3));
        cells.insert( "5_12",Cell( "5_12", "b",0,0));
        cells.insert( "6_0",Cell( "6_0", "b",0,0));
        cells.insert( "6_1",Cell( "6_1", "b",0,0));
        cells.insert( "6_2",Cell( "6_2", "c",9,3));
        cells.insert( "6_3",Cell( "6_3", "a",0,4));
        cells.insert( "6_4",Cell( "6_4", "a",0,3));
        cells.insert( "6_5",Cell( "6_5", "a",0,2));
        cells.insert( "6_6",Cell( "6_6", "b",0,0));
        cells.insert( "6_7",Cell( "6_7", "c",15,0));
        cells.insert( "6_8",Cell( "6_8", "a",0,3));
        cells.insert( "6_9",Cell( "6_9", "a",0,5));
        cells.insert( "6_10",Cell( "6_10", "a",0,6));
        cells.insert( "6_11",Cell( "6_11", "a",0,1));
        cells.insert( "6_12",Cell( "6_12", "b",0,0));
        cells.insert( "7_0",Cell( "7_0", "b",0,0));
        cells.insert( "7_1",Cell( "7_1", "c",14,0));
        cells.insert( "7_2",Cell( "7_2", "a",0,2));
        cells.insert( "7_3",Cell( "7_3", "a",0,8));
        cells.insert( "7_4",Cell( "7_4", "a",0,1));
        cells.insert( "7_5",Cell( "7_5", "a",0,3));
        cells.insert( "7_6",Cell( "7_6", "c",0,4));
        cells.insert( "7_7",Cell( "7_7", "c",11,0));
        cells.insert( "7_8",Cell( "7_8", "a",0,1));
        cells.insert( "7_9",Cell( "7_9", "a",0,3));
        cells.insert( "7_10",Cell( "7_10", "a",0,8));
        cells.insert( "7_11",Cell( "7_11", "b",0,0));
        cells.insert( "7_12",Cell( "7_12", "b",0,0));
        cells.insert( "8_0",Cell( "8_0", "b",0,0));
        cells.insert( "8_1",Cell( "8_1", "c",10,0));
        cells.insert( "8_2",Cell( "8_2", "a",0,1));
        cells.insert( "8_3",Cell( "8_3", "a",0,9));
        cells.insert( "8_4",Cell( "8_4", "c",4,11));
        cells.insert( "8_5",Cell( "8_5", "a",0,1));
        cells.insert( "8_6",Cell( "8_6", "a",0,3));
        cells.insert( "8_7",Cell( "8_7", "c",5,4));
        cells.insert( "8_8",Cell( "8_8", "a",0,2));
        cells.insert( "8_9",Cell( "8_9", "a",0,1));
        cells.insert( "8_10",Cell( "8_10", "c",0,6));
        cells.insert( "8_11",Cell( "8_11", "b",0,0));
        cells.insert( "8_12",Cell( "8_12", "b",0,0));
        cells.insert( "9_0",Cell( "9_0", "b",0,0));
        cells.insert( "9_1",Cell( "9_1", "c",0,16));
        cells.insert( "9_2",Cell( "9_2", "c",9,17));
        cells.insert( "9_3",Cell( "9_3", "a",0,6));
        cells.insert( "9_4",Cell( "9_4", "a",0,3));
        cells.insert( "9_5",Cell( "9_5", "c",4,0));
        cells.insert( "9_6",Cell( "9_6", "a",0,1));
        cells.insert( "9_7",Cell( "9_7", "a",0,3));
        cells.insert( "9_8",Cell( "9_8", "c",3,24));
        cells.insert( "9_9",Cell( "9_9", "a",0,2));
        cells.insert( "9_10",Cell( "9_10", "a",0,2));
        cells.insert( "9_11",Cell( "9_11", "c",0,3));
        cells.insert( "9_12",Cell( "9_12", "b",0,0));
        cells.insert( "10_0",Cell( "10_0", "c",25,0));
        cells.insert( "10_1",Cell( "10_1", "a",0,9));
        cells.insert( "10_2",Cell( "10_2", "a",0,8));
        cells.insert( "10_3",Cell( "10_3", "a",0,7));
        cells.insert( "10_4",Cell( "10_4", "a",0,1));
        cells.insert( "10_5",Cell( "10_5", "c",0,17));
        cells.insert( "10_6",Cell( "10_6", "c",9,0));
        cells.insert( "10_7",Cell( "10_7", "a",0,1));
        cells.insert( "10_8",Cell( "10_8", "a",0,8));
        cells.insert( "10_9",Cell( "10_9", "c",4,17));
        cells.insert( "10_10",Cell( "10_10", "a",0,3));
        cells.insert( "10_11",Cell( "10_11", "a",0,1));
        cells.insert( "10_12",Cell( "10_12", "b",0,0));
        cells.insert( "11_0",Cell( "11_0", "c",16,0));
        cells.insert( "11_1",Cell( "11_1", "a",0,7));
        cells.insert( "11_2",Cell( "11_2", "a",0,9));
        cells.insert( "11_3",Cell( "11_3", "c",14,0));
        cells.insert( "11_4",Cell( "11_4", "a",0,5));
        cells.insert( "11_5",Cell( "11_5", "a",0,9));
        cells.insert( "11_6",Cell( "11_6", "b",0,0));
        cells.insert( "11_7",Cell( "11_7", "c",20,0));
        cells.insert( "11_8",Cell( "11_8", "a",0,9));
        cells.insert( "11_9",Cell( "11_9", "a",0,8));
        cells.insert( "11_10",Cell( "11_10", "a",0,1));
        cells.insert( "11_11",Cell( "11_11", "a",0,2));
        cells.insert( "11_12",Cell( "11_12", "b",0,0));
        cells.insert( "12_0",Cell( "12_0", "b",0,0));
        cells.insert( "12_1",Cell( "12_1", "b",0,0));
        cells.insert( "12_2",Cell( "12_2", "b",0,0));
        cells.insert( "12_3",Cell( "12_3", "c",10,0));
        cells.insert( "12_4",Cell( "12_4", "a",0,2));
        cells.insert( "12_5",Cell( "12_5", "a",0,8));
        cells.insert( "12_6",Cell( "12_6", "b",0,0));
        cells.insert( "12_7",Cell( "12_7", "c",16,0));
        cells.insert( "12_8",Cell( "12_8", "a",0,7));
        cells.insert( "12_9",Cell( "12_9", "a",0,9));
        cells.insert( "12_10",Cell( "12_10", "b",0,0));
        cells.insert( "12_11",Cell( "12_11", "b",0,0));
        cells.insert( "12_12",Cell( "12_12", "b",0,0));
    }
}

void MainWindow::createNonClue(QPoint pos)
{

    QTableWidgetItem *cell = ui->tableWidget->item(pos.x(),pos.y());
    cell->setBackgroundColor(Qt::black);
    cell->setFlags(cell->flags()^Qt::ItemIsEditable);
}

void MainWindow::createClue(QPoint pos, double dRClue, double dDClue)
{
    QString rClue = " ";
    QString dClue = " ";
    QString imagePath = ":/res/slash.png";
    QImage *img = new QImage();

    bool loaded = img -> load(imagePath);

    if(loaded)
    {
        //std::cout << "IMAGE has been loaded!" << std::endl;
    }

    if(dRClue > 0)
    {
        rClue = QString::number(dRClue);
    }
    if(dDClue > 0)
    {
        dClue = QString::number(dDClue);
    }

    QString space= "  ";
    QString tab= "     ";
    QTableWidgetItem *cell =new QTableWidgetItem(space + tab + tab + rClue + "\n" + tab + space  + "\n" + "\n" + dClue + tab + tab);
    /*(space+"/"+tab+tab+space+rClue+" \n"+tab+space+"/ \n"+dClue+tab+space+space+space+"/"+space+space);*/
    cell->setFlags(cell->flags()^Qt::ItemIsEditable);

    QFont font;
    font.setPointSize(fontSize);
    font.setFamily("Arial");
    cell->setFont(font);
    cell->setBackground(QPixmap::fromImage(*img).scaled(cellWidth, cellHeight));
    cell->setTextColor(Qt::white);
    ui->tableWidget->setItem(pos.x(),pos.y(),cell);

}

void MainWindow::menuRequest(const QPoint &pos)
{
    QModelIndex	index	=	ui->tableWidget->indexAt(pos);

    std::cout	<<	"MainWindow::menuRequest	-	at"
                 <<	"	QModelIndex	row	=	"	<<	index.row()
                 <<	",	column	=	"	<<	index.column()
                 <<	std::endl;
    QMenu	menu(this);
    QAction	*clearValue;
    QAction	*setValue1;
    QAction	*showValueSet;
    QAction	*hideValueSet;
    clearValue	=	menu.addAction("Clear	set	value");
    showValueSet	=	menu.addAction("Set	possible	values");
    setValue1=	menu.addAction("Set	value	to	1");
    QAction	*action	=	menu.exec(ui->tableWidget->viewport()->mapToGlobal(pos));
}

void MainWindow::on_tableWidget_cellClicked(int row, int column)
{
    Cell emptyCell("","",0,0);
    QMap<QString, Cell>::iterator it{};
    QString cId = QString::number(row) + "_" + QString::number(column);
    Cell& pCell = emptyCell;

    if(cells.find(cId) != cells.end())
    {
        it = cells.find(cId);

        pCell = it.value();

        if(pCell.getType().contains("a"))
        {
            Data::selectedrow = row;
            Data::selectedcolumn = column;
            QPoint p = ui->tableWidget->mapFromGlobal(QCursor::pos());

            ui->gridFrame->move(p);

            //find possible values
            //QTableWidgetItem *cellSelected = ui->tableWidget->item(row, column);

            double max = 0;
            double topAnswer = 0;
            double bottomAnswer = 0;
            double leftAnswer = 0;
            double rightAnswer = 0;

            //get top cell
            bool getTopcell = true;
            int topRow = row;
            while(getTopcell)
            {
                topRow--;
                QString topId = QString::number(topRow) + "_" + QString::number(column);
                QTableWidgetItem *topAnswerCell = ui->tableWidget->item(topRow, column);

                if(cells.find(topId) != cells.end())
                {
                    it = cells.find(topId);
                    Cell topCell = it.value();
                    if(topCell.getType() == "c")
                    {
                        getTopcell = false; //found top cell
                        max = topCell.getDownOrSolution();
                        break;
                    }

                    if(topCell.getType() == "a")
                    {
                        topAnswer += topAnswerCell->text().toDouble();
                    }
                }
                else
                {
                    break;
                }
            }

            //get bottom cell
            bool getBottomCell = true;
            int bottomRow = row;
            while(getBottomCell)
            {
                bottomRow++;
                QString bottomId = QString::number(bottomRow) + "_" + QString::number(column);
                QTableWidgetItem *bottomAnswerCell = ui->tableWidget->item(bottomRow, column);

                if(bottomRow > 12)
                {
                    getBottomCell = false;
                    break;
                }
                if(cells.find(bottomId) != cells.end())
                {
                    it = cells.find(bottomId);
                    Cell bottomCell = it.value();
                    if(bottomCell.getType() == "c" || bottomCell.getType() == "b")
                    {
                        getBottomCell = false; //found bottom cell
                        break;
                    }

                    if(bottomCell.getType() == "a"){
                        bottomAnswer += bottomAnswerCell->text().toDouble();
                    }
                }
                else
                {
                    break;
                }
            }

            double maxColumn = 0;
            //get left cell
            bool getLeftCell = true;
            int leftColumn = column;
            while(getLeftCell)
            {
                leftColumn--;
                QString leftId = QString::number(row) + "_" + QString::number(leftColumn);
                QTableWidgetItem *leftAnswerCell = ui->tableWidget->item(row, leftColumn);

                if(cells.find(leftId) != cells.end())
                {
                    it = cells.find(leftId);
                    Cell leftCell = it.value();
                    if(leftCell.getType() == "c")
                    {
                        getLeftCell = false; //found left cell
                        maxColumn = leftCell.getRightOrAnswer();
                        break;
                    }

                    if(leftCell.getType() == "a"){
                        leftAnswer += leftAnswerCell->text().toDouble();
                    }
                }
                else
                {
                    break;
                }
            }

            //get right cell
            bool getRightCell = true;
            int rightColumn = column;
            while(getRightCell)
            {
                rightColumn++;
                QString rightId = QString::number(row) + "_" + QString::number(rightColumn);
                QTableWidgetItem *rightAnswerCell = ui->tableWidget->item(row, rightColumn);

                if(rightColumn > 13)
                {
                    getRightCell = false;
                    break;
                }
                if(cells.find(rightId) != cells.end())
                {
                    it = cells.find(rightId);
                    Cell rightCell = it.value();
                    if(rightCell.getType() == "c" || rightCell.getType() == "b"){
                        getRightCell = false; //found right cell
                        break;
                    }

                    if(rightCell.getType() == "a")
                    {
                        rightAnswer += rightAnswerCell->text().toDouble();
                    }
                }
                else
                {
                    break;
                }
            }

            max = max - topAnswer - bottomAnswer;
            maxColumn = maxColumn - leftAnswer - rightAnswer;
            if(maxColumn < max)
            {
                max = maxColumn;
            }

            this->setButtonAble();
            //manage value display
            if(max >= 9)
            {

            }
            else if(max ==8)
            {
                ui->pushButton_9->setDisabled(true);
                ui->pushButton_9->setStyleSheet("background-color:red");

            }
            else if(max ==7)
            {
                ui->pushButton_9->setDisabled(true);
                ui->pushButton_8->setDisabled(true);
                ui->pushButton_9->setStyleSheet("background-color:red");
                ui->pushButton_8->setStyleSheet("background-color:red");

            }
            else if(max ==6)
            {
                ui->pushButton_9->setDisabled(true);
                ui->pushButton_8->setDisabled(true);
                ui->pushButton_7->setDisabled(true);
                ui->pushButton_9->setStyleSheet("background-color:red");
                ui->pushButton_8->setStyleSheet("background-color:red");
                ui->pushButton_7->setStyleSheet("background-color:red");

            }
            else if(max ==5)
            {
                ui->pushButton_9->setDisabled(true);
                ui->pushButton_8->setDisabled(true);
                ui->pushButton_7->setDisabled(true);
                ui->pushButton_6->setDisabled(true);
                ui->pushButton_9->setStyleSheet("background-color:red");
                ui->pushButton_8->setStyleSheet("background-color:red");
                ui->pushButton_7->setStyleSheet("background-color:red");
                ui->pushButton_6->setStyleSheet("background-color:red");

            }
            else if(max ==4)
            {
                ui->pushButton_9->setDisabled(true);
                ui->pushButton_8->setDisabled(true);
                ui->pushButton_7->setDisabled(true);
                ui->pushButton_6->setDisabled(true);
                ui->pushButton_5->setDisabled(true);
                ui->pushButton_9->setStyleSheet("background-color:red");
                ui->pushButton_8->setStyleSheet("background-color:red");
                ui->pushButton_7->setStyleSheet("background-color:red");
                ui->pushButton_6->setStyleSheet("background-color:red");
                ui->pushButton_5->setStyleSheet("background-color:red");


            }
            else if(max ==3)
            {
                ui->pushButton_9->setDisabled(true);
                ui->pushButton_8->setDisabled(true);
                ui->pushButton_7->setDisabled(true);
                ui->pushButton_6->setDisabled(true);
                ui->pushButton_5->setDisabled(true);
                ui->pushButton_4->setDisabled(true);
                ui->pushButton_9->setStyleSheet("background-color:red");
                ui->pushButton_8->setStyleSheet("background-color:red");
                ui->pushButton_7->setStyleSheet("background-color:red");
                ui->pushButton_6->setStyleSheet("background-color:red");
                ui->pushButton_5->setStyleSheet("background-color:red");
                ui->pushButton_4->setStyleSheet("background-color:red");


            }
            else if(max ==2)
            {
                ui->pushButton_9->setDisabled(true);
                ui->pushButton_8->setDisabled(true);
                ui->pushButton_7->setDisabled(true);
                ui->pushButton_6->setDisabled(true);
                ui->pushButton_5->setDisabled(true);
                ui->pushButton_4->setDisabled(true);
                ui->pushButton_3->setDisabled(true);
                ui->pushButton_9->setStyleSheet("background-color:red");
                ui->pushButton_8->setStyleSheet("background-color:red");
                ui->pushButton_7->setStyleSheet("background-color:red");
                ui->pushButton_6->setStyleSheet("background-color:red");
                ui->pushButton_5->setStyleSheet("background-color:red");
                ui->pushButton_4->setStyleSheet("background-color:red");
                ui->pushButton_3->setStyleSheet("background-color:red");


            }
            else if(max ==1)
            {
                ui->pushButton_9->setDisabled(true);
                ui->pushButton_8->setDisabled(true);
                ui->pushButton_7->setDisabled(true);
                ui->pushButton_6->setDisabled(true);
                ui->pushButton_5->setDisabled(true);
                ui->pushButton_4->setDisabled(true);
                ui->pushButton_3->setDisabled(true);
                ui->pushButton_2->setDisabled(true);
                ui->pushButton_9->setStyleSheet("background-color:red");
                ui->pushButton_8->setStyleSheet("background-color:red");
                ui->pushButton_7->setStyleSheet("background-color:red");
                ui->pushButton_6->setStyleSheet("background-color:red");
                ui->pushButton_5->setStyleSheet("background-color:red");
                ui->pushButton_4->setStyleSheet("background-color:red");
                ui->pushButton_3->setStyleSheet("background-color:red");
                ui->pushButton_2->setStyleSheet("background-color:red");
            }
            else if(max <1)
            {
                ui->pushButton_9->setDisabled(true);
                ui->pushButton_8->setDisabled(true);
                ui->pushButton_7->setDisabled(true);
                ui->pushButton_6->setDisabled(true);
                ui->pushButton_5->setDisabled(true);
                ui->pushButton_4->setDisabled(true);
                ui->pushButton_3->setDisabled(true);
                ui->pushButton_2->setDisabled(true);
                ui->pushButton_1->setDisabled(true);
                ui->pushButton_9->setStyleSheet("background-color:red");
                ui->pushButton_8->setStyleSheet("background-color:red");
                ui->pushButton_7->setStyleSheet("background-color:red");
                ui->pushButton_6->setStyleSheet("background-color:red");
                ui->pushButton_5->setStyleSheet("background-color:red");
                ui->pushButton_4->setStyleSheet("background-color:red");
                ui->pushButton_3->setStyleSheet("background-color:red");
                ui->pushButton_2->setStyleSheet("background-color:red");
                ui->pushButton_1->setStyleSheet("background-color:red");
            }

            ui->tableWidget->setDisabled(true);
            ui->gridFrame->show();
        }
    }
}


void MainWindow::setButtonAble()
{
    ui->pushButton_1->setDisabled(false);
    ui->pushButton_2->setDisabled(false);
    ui->pushButton_3->setDisabled(false);
    ui->pushButton_4->setDisabled(false);
    ui->pushButton_5->setDisabled(false);
    ui->pushButton_6->setDisabled(false);
    ui->pushButton_7->setDisabled(false);
    ui->pushButton_8->setDisabled(false);
    ui->pushButton_9->setDisabled(false);

    ui->pushButton_1->setStyleSheet("");
    ui->pushButton_2->setStyleSheet("");
    ui->pushButton_3->setStyleSheet("");
    ui->pushButton_4->setStyleSheet("");
    ui->pushButton_5->setStyleSheet("");
    ui->pushButton_6->setStyleSheet("");
    ui->pushButton_7->setStyleSheet("");
    ui->pushButton_8->setStyleSheet("");
    ui->pushButton_9->setStyleSheet("");
}


void MainWindow::on_pushButton_10_clicked()
{
    ui->tableWidget->setDisabled(false);
    ui->gridFrame->hide();
}

void MainWindow::on_pushButton_1_clicked()
{

    QTableWidgetItem *cellSelected = ui->tableWidget->item(Data::selectedrow, Data::selectedcolumn);

    cellSelected->setText("1");
    cellSelected->setBackgroundColor(Qt::white);
    setCurrentAnswer(1);

    addCellToMovesMap();

    ui->tableWidget->setDisabled(false);
    ui->gridFrame->hide();
    this->setButtonAble();
}

void MainWindow::on_pushButton_2_clicked()
{
    QTableWidgetItem *cellSelected = ui->tableWidget->item(Data::selectedrow, Data::selectedcolumn);

    cellSelected->setText("2");
    cellSelected->setBackgroundColor(Qt::white);
    setCurrentAnswer(2);

    addCellToMovesMap();

    ui->tableWidget->setDisabled(false);
    ui->gridFrame->hide();
    this->setButtonAble();
}

void MainWindow::on_pushButton_3_clicked()
{
    QTableWidgetItem *cellSelected = ui->tableWidget->item(Data::selectedrow, Data::selectedcolumn);

    cellSelected->setText("3");
    cellSelected->setBackgroundColor(Qt::white);
    setCurrentAnswer(3);

    addCellToMovesMap();

    ui->tableWidget->setDisabled(false);
    ui->gridFrame->hide();
    this->setButtonAble();
}

void MainWindow::on_pushButton_4_clicked()
{
    QTableWidgetItem *cellSelected = ui->tableWidget->item(Data::selectedrow, Data::selectedcolumn);

    cellSelected->setText("4");
    cellSelected->setBackgroundColor(Qt::white);
    setCurrentAnswer(4);

    addCellToMovesMap();

    ui->tableWidget->setDisabled(false);
    ui->gridFrame->hide();
    this->setButtonAble();
}

void MainWindow::on_pushButton_5_clicked()
{
    QTableWidgetItem *cellSelected = ui->tableWidget->item(Data::selectedrow, Data::selectedcolumn);

    cellSelected->setText("5");
    cellSelected->setBackgroundColor(Qt::white);
    setCurrentAnswer(5);

    addCellToMovesMap();

    ui->tableWidget->setDisabled(false);
    ui->gridFrame->hide();
    this->setButtonAble();
}

void MainWindow::on_pushButton_6_clicked()
{
    QTableWidgetItem *cellSelected = ui->tableWidget->item(Data::selectedrow, Data::selectedcolumn);

    cellSelected->setText("6");
    setCurrentAnswer(6);

    addCellToMovesMap();

    cellSelected->setBackgroundColor(Qt::white);
    ui->tableWidget->setDisabled(false);
    ui->gridFrame->hide();
    this->setButtonAble();
}

void MainWindow::on_pushButton_7_clicked()
{
    QTableWidgetItem *cellSelected = ui->tableWidget->item(Data::selectedrow, Data::selectedcolumn);

    cellSelected->setText("7");
    cellSelected->setBackgroundColor(Qt::white);
    setCurrentAnswer(7);

    addCellToMovesMap();

    ui->tableWidget->setDisabled(false);
    ui->gridFrame->hide();
    this->setButtonAble();
}

void MainWindow::on_pushButton_8_clicked()
{
    QTableWidgetItem *cellSelected = ui->tableWidget->item(Data::selectedrow, Data::selectedcolumn);

    cellSelected->setText("8");
    cellSelected->setBackgroundColor(Qt::white);
    setCurrentAnswer(8);

    addCellToMovesMap();

    ui->tableWidget->setDisabled(false);
    ui->gridFrame->hide();
    this->setButtonAble();
}

void MainWindow::on_pushButton_9_clicked()
{
    QTableWidgetItem *cellSelected = ui->tableWidget->item(Data::selectedrow, Data::selectedcolumn);

    cellSelected->setText("9");
    cellSelected->setBackgroundColor(Qt::white);
    setCurrentAnswer(9);

    addCellToMovesMap();

    ui->tableWidget->setDisabled(false);
    ui->gridFrame->hide();
    this->setButtonAble();
}

void MainWindow::on_pushButton_delete_clicked()
{
    QTableWidgetItem *cellSelected = ui->tableWidget->item(Data::selectedrow, Data::selectedcolumn);

    cellSelected->setText("");
    cellSelected->setBackgroundColor(Qt::white);
    setCurrentAnswer(0);

    addCellToMovesMap();

    ui->tableWidget->setDisabled(false);
    ui->gridFrame->hide();
}

void MainWindow::setCurrentAnswer(double num)
{
    QString cId = "";
    QMap<QString, Cell>::iterator it{};
    Cell *pCell = {};

    cId = QString::number(Data::selectedrow) + "_" + QString::number(Data::selectedcolumn);

    if(cells.find(cId) != cells.end())
    {
        it = cells.find(cId);

        pCell = &it.value();

        if(pCell->getType() == "a")
        {
            pCell->setRightOrAnswer(num);
        }
    }
}

void MainWindow::setCurrentAnswer(double num, int row, int col)
{
    QString cId = "";
    QMap<QString, Cell>::iterator it{};
    Cell *pCell = {};

    cId = QString::number(row) + "_" + QString::number(col);

    QTableWidgetItem *cellSelected = ui->tableWidget->item(row, col);

    if(num > 0)
    {

        cellSelected->setText(QString::number(num));
    }
    else
    {
        cellSelected->setText("");
    }

    if(cells.find(cId) != cells.end())
    {
        it = cells.find(cId);

        pCell = &it.value();

        if(pCell->getType() == "a")
        {
            pCell->setRightOrAnswer(num);
        }
    }
}

void MainWindow::on_pushButton_Game1_clicked()
{
    gs = g3x3;
    ui->verticalFrame_2->hide();

    createGameBoard();
}

void MainWindow::on_pushButton_Game2_clicked()
{
    gs = g9x9;
    ui->verticalFrame_2->hide();

    createGameBoard();
}

void MainWindow::on_pushButton_Game3_clicked()
{
    gs = g13x13;
    ui->verticalFrame_2->hide();

    createGameBoard();
}

void MainWindow::on_pushButton_LoadGame_clicked()
{
    cells = {};
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QString(),
                                                    tr("Text Game Files (*.json);;Binary Game Files (*.dat)"));

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
            return;
        }
        QString ff = fileName.split(".").last();

        QByteArray data = file.readAll();

        QJsonDocument loadDoc(ff.contains("json")
                              ? QJsonDocument::fromJson(data)
                              : QJsonDocument::fromBinaryData(data));
        currentGame = loadDoc.object();
        file.close();
    }
    std::string cgId = currentGame["gamefile"].toArray().at(0).toObject().find("id").value().toString().toStdString();
    std::cout << "file " + cgId + " has been loaded" << std::endl;

    // load cells from currentGame

    if(cgId.substr(0,1) == "3")
    {
        // cells = {};
        // gameSize = 3;
        // cells = gamefileToQMap(currentGame);
        gs = g3x3;
    }
    else if(cgId.substr(0,1) == "9")
    {
        // cells = {};
        // gameSize = 9;
        // cells = gamefileToQMap(currentGame);
        gs = g9x9;
    }
    // else if(cgId.substr(0,1) == "D")
    // {
    //     cells = {};
    //     gameSize = 13;
    //     cells = gamefileToQMap(currentGame);
    // }
//    else
//    {
//        gs = g0x0;
//    }
    ui->verticalFrame_2->hide();

    createGameBoard();
}

void MainWindow::on_pushButton_check_clicked()
{
    QString cId = "";
    Cell emptyCell("","",0,0);
    QMap<QString, Cell>::iterator it{};
    Cell& pCell = emptyCell;

    int totalAnswerCells = 0;
    int totalCorrectCells = 0;

    for(int i = 1; i < gameSize; i++)
    {
        for(int j = 1; j < gameSize; j++)
        {
            cId = QString::number(i) + "_" + QString::number(j);

            if(cells.find(cId) != cells.end())
            {
                it = cells.find(cId);

                pCell = it.value();

                if(pCell.getType() == "a")
                {
                    totalAnswerCells++;
                    std::cout << "Cell ID: " << pCell.getID().toStdString() << "Answer: " << pCell.getRightOrAnswer() << ", Solution: " << pCell.getDownOrSolution() << std::endl;
                    if(pCell.getRightOrAnswer() == pCell.getDownOrSolution())
                    {
                        totalCorrectCells++;
                        ui->tableWidget->item(i, j)->setBackgroundColor(Qt::green);
                    }
                    else
                    {
                        if(pCell.getRightOrAnswer() != 0)
                        {
                            ui->tableWidget->item(i, j)->setBackgroundColor(Qt::yellow);
                        }
                    }
                }
            }
        }
    }

    std::cout << "Answer Cells: " << totalAnswerCells << ", Right Answers: " << totalCorrectCells << std::endl;
    if(totalCorrectCells == totalAnswerCells)
    {
        ui->tableWidget->setDisabled(true);
        ui->Undo_redo_Frame->setDisabled(true);
        ui->WinFrame->show();
    }
}

void MainWindow::on_pushButton_newGame_clicked()
{
    ui->tableWidget->hide();
    ui->tableWidget->setEnabled(true);
    ui->Undo_redo_Frame->setEnabled(true);
    ui->gridFrame->hide();
    ui->WinFrame->hide();
    ui->Game_Menu_Frame->hide();
    ui->Undo_redo_Frame->hide();

    ui->tableWidget->clearContents();

    allMoves.clear();

    moveNumber = 0;

    cells.clear();

    ui->verticalFrame_2->show();
}

void MainWindow::on_pushButton_save_clicked()
{
    QString ff = "json";//fileName.split(".").last();

    //save game
    QFile outFile(ff == "json"
                  ? QString(sId + ".save.json")
        : QString(sId + ".save.dat"));

    QJsonObject outGamefile = MainWindow::qmapToGamefile(cells);
    QJsonDocument saveDoc(outGamefile);
    std::string cgId = "";

    if(!outFile.open(QIODevice::WriteOnly))
    {
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), QString(),
                                                        tr("Text Game Files (*.json);;Binary Game Files (*.dat)"));
        if (!fileName.isEmpty())
        {
            cgId = fileName.toStdString();
            QFile file(fileName);
            if (!file.open(QIODevice::WriteOnly))
            {
                QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
                return;
            }
            file.write(ff == "json" ? saveDoc.toJson() : saveDoc.toBinaryData());
            file.close();
        }
    }

    cgId = outFile.objectName().toStdString();
    outFile.write(ff == "json" ? saveDoc.toJson() : saveDoc.toBinaryData());
    outFile.close();

//    std::string cgId = currentGame["gamefile"].toArray().at(0).toObject().find("id").value().toString().toStdString();
    std::cout << "file " + cgId + " has been loaded" << std::endl;

}

QMap<QString,Cell> MainWindow::gamefileToQMap(const QJsonObject& inGameFile)
{
    QMap<QString,Cell> cells = {};
    sId = inGameFile.find("gamefile").value().toArray().at(0).toObject().find("id").value().toString();
    aPuzzle = inGameFile.find("gamefile").value().toArray().at(1).toObject().find("puzzle").value().toArray();
    aGame = inGameFile.find("gamefile").value().toArray().at(2).toObject().find("game").value().toArray();
    aMoves = inGameFile.find("gamefile").value().toArray().at(3).toObject().find("moves").value().toArray();
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

QJsonObject MainWindow::qmapToGamefile(const QMap<QString,Cell>& cells)
{
    QJsonObject outGamefile = {};
    double gameSize = sqrt(cells.size());
    int currentRow = 0;
    int mapIndex = 1;
//    outGamefile = {};
//    QJsonArray aGamefile = {};
    for(Cell mCell: cells)
    {
        QJsonArray aRowG = {};
        QJsonObject oRowG = {};
        QJsonObject oCellG = {};
        QJsonArray aRowP = {};
        QJsonObject oRowP = {};
        QJsonArray aCellP = {};
//        int tempRow = mCell.getID().split("_").first().toInt();
//        int tempCol = mCell.getID().split("_").last().toInt();
        oCellG.insert("id",mCell.getID());
        oCellG.insert("type",mCell.getType());
        if(mCell.getType()=="a")
        {
            oCellG.insert("answer",mCell.getRightOrAnswer());
            aCellP.push_back(mCell.getDownOrSolution());
        } else {
            oCellG.insert("right",mCell.getRightOrAnswer());
            oCellG.insert("down",mCell.getDownOrSolution());
        }
        aRowG.push_back(oCellG);
        aRowP.push_back(aCellP);
        if(mapIndex == int(gameSize))
        {
            oRowG.insert("row",QJsonValue(aRowG));
            aGame.push_back(QJsonValue(oRowG));
            oRowP = QJsonValue(aRowP).toObject();
            aPuzzle.push_back(QJsonValue(oRowP));
            mapIndex = 1;
            currentRow++;
        } else {
            mapIndex++;
        }
    }
    outGamefile.find("gamefile").value().toArray().at(2).toObject().find("game").value().toArray() = aGame;
//    outGamefile.insert("game",QJsonValue(aGamefile));

    return outGamefile;
}

Cell MainWindow::getCell(int row, int col)
{
    Cell emptyCell("","",0,0);
    QString cId = "";
    QMap<QString, Cell>::iterator it{};
    Cell& pCell = emptyCell;
    cId = QString::number(row) + "_" + QString::number(col);

    if(cells.find(cId) != cells.end())
    {
        it = cells.find(cId);

        pCell = it.value();

        return pCell;
    }
    return emptyCell;
}

void MainWindow::addCellToMovesMap()
{
    if(moveNumber < allMoves.size())
    {
        // i is set to moveNumber, as the next move hasn't been added yet.
        for(int i = moveNumber+1; i <= allMoves.size(); i++)
        {
            allMoves.remove(QString::number(i));
        }

        std::cout << "After Delete: moveNumber: " << moveNumber << ", allMoves.size(): "<< allMoves.size() <<std::endl;

        for(auto k: allMoves.keys())
        {
            std::cout << "Key: " << k.toStdString() << ", Answer: " << allMoves.value(k).getRightOrAnswer() << std::endl;
        }
    }
    Cell cell1 = getCell(Data::selectedrow, Data::selectedcolumn);

    if(cell1.getID() != "")
    {
        std::cout << "Cell1 =  " << "Id: " << cell1.getID().toStdString() << ", Answer: " << cell1.getRightOrAnswer() << std::endl;
        QString mNum = QString::number((moveNumber+1));
        allMoves.insert(mNum, Cell(cell1.getID(), cell1.getType(), cell1.getRightOrAnswer(), cell1.getDownOrSolution(), "Yes"));
        moveNumber++;

        //TESTING
        //std::cout << "Postd add:-  moveNumber: " << moveNumber << ", allMoves.size(): "<< allMoves.size() <<std::endl;
        /*for(auto k: allMoves.keys())
        {
            std::cout << "Key: " << k.toStdString() << ", Answer: " << allMoves.value(k).getRightOrAnswer() << std::endl;
        }*/
    }
}

void MainWindow::on_pushButton_undo_clicked()
{
    std::cout << "Undo Clicked! Number of Moves =  " << moveNumber << std::endl;
    if(moveNumber > 0)
    {
        Cell emptyCell("","",0,0);
        QString cId = QString::number(moveNumber);
        QMap<QString, Cell>::iterator it{};
        QMap<QString, Cell>::iterator it2{};
        Cell pCell = emptyCell;
        Cell tempCell = emptyCell;
        bool foundAnother = false;
        int countTotal = 0;

        if(allMoves.find(cId) != allMoves.end())
        {
            it = allMoves.find(cId);

            pCell = it.value();

            std::cout << "Looking for:  " << pCell.getID().toStdString() << std::endl;

            for(int i = moveNumber; i > 0; i--)
            {
                cId = QString::number(i);

                if(allMoves.find(cId) != allMoves.end())
                {
                    it2 = allMoves.find(cId);

                    tempCell = it2.value();

                    std::cout << tempCell.getID().toStdString() << std::endl;

                    if(pCell.getID() == tempCell.getID())
                    {
                        countTotal++;

                        std::cout << "Count: " << countTotal << std::endl;

                        if(countTotal > 1)
                        {
                            foundAnother = true;
                            std::cout << "FOUND: " << countTotal << std::endl;

                            QVector<QString> idSplit = splitString(pCell.getID(), '_');

                            setCurrentAnswer(tempCell.getRightOrAnswer(), idSplit[0].toInt(), idSplit[1].toInt());

                            moveNumber--;

                            break;

                        }
                    }
                }
            }

            if(!foundAnother)
            {
                std::cout << "Didn't find another for : " << pCell.getID().toStdString() << std::endl;
                QVector<QString> idSplit = splitString(pCell.getID(), '_');
                setCurrentAnswer(0, idSplit[0].toInt(), idSplit[1].toInt());
                moveNumber--;
            }
        }
    }
}

void MainWindow::on_pushButton_redo_clicked()
{
    if(moveNumber < allMoves.size())
    {
        std::cout << "Postd add:-  moveNumber: " << moveNumber << ", allMoves.size(): "<< allMoves.size() <<std::endl;

        Cell emptyCell("","",0,0);
        QString cId = QString::number(moveNumber+1);
        QMap<QString, Cell>::iterator it{};
        Cell& pCell = emptyCell;

        if(allMoves.find(cId) != allMoves.end())
        {
            it = allMoves.find(cId);
            pCell = it.value();

            QVector<QString> idSplit = splitString(pCell.getID(), '_');

            setCurrentAnswer(pCell.getRightOrAnswer(), idSplit[0].toInt(), idSplit[1].toInt());

            moveNumber++;
        }

        std::cout << "Postd add:-  moveNumber: " << moveNumber << ", allMoves.size(): "<< allMoves.size() <<std::endl;
    }
}

QVector<QString> MainWindow::splitString(const QString& str, const QChar& ch)
{
    QString next;
    QVector<QString> result;

    for (QString::const_iterator it = str.begin(); it != str.end(); it++)
    {
        if (*it == ch)
        {
            if (!next.isEmpty())
            {
                result.push_back(next);
                next.clear();
            }
        }
        else
        {
            next += *it;
        }
    }
    if (!next.isEmpty())
    {
        result.push_back(next);
    }
    return result;
}
