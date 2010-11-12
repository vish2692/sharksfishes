#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "optionwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Shark and Fishes !");
    fileMenu = menuBar()->addMenu("File");
    startAnimation = new QAction("Start simulation", this);
    fileMenu->addAction(startAnimation);

    optionMenu = menuBar()->addMenu("Option");
    preferences = new QAction("Preferences", this);
    optionMenu->addAction(preferences);



    /*Connect the startAction menu to our custom slot.*/
    connect(startAnimation,SIGNAL(triggered()),this,SLOT(startAnim()));
    connect(preferences,SIGNAL(triggered()),this,SLOT(showOptions()));

    show();
    setGeometry((QApplication::desktop()->screenGeometry().width()/2 - width()/2), (QApplication::desktop()->screenGeometry().height()/2 -                       height()/2), width(), height());

    m_gridWidth = 100;
    m_gridHeight = 100;
    m_nbTurn = 20;
    m_nbStartSharks = 100;
    m_nbStartFishes = 100;
    m_nbMaxLifeSharks = 40;
    m_nbMaxLifeFishes = 40;
    m_nbTurnBetweenProcSharks = 4;
    m_nbTurnBetweenProcFishes = 4;
    m_nbTurnBeforeDecaySharks = 2;
    m_nbTurnBeforeDecayFishes = 2;
    m_nbTurnBeforeStarvationSharks = 10;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showOptions()
{
    optionW = new optionWindow(this);
    optionW->show();
}

/*Launch the application.*/
void MainWindow::startAnim()
{
    /*Set a background image.*/
    setStyleSheet("QMainWindow{background-image: url(:/images/background.png)}");

    /*Create the sea object.*/
    actualSea = new Sea();

    /*initialise our grid layout, depends on the options that the user made.*/
    listImage = QVector<QVector<QLabel *> >(m_gridWidth);
    for(int iPos = 0; iPos < m_gridWidth; iPos++)
    {
        listImage[iPos] = QVector<QLabel *>(m_gridHeight);
        for(int iPos2 = 0; iPos2 < m_gridHeight; iPos2++)
        {
            listImage[iPos][iPos2] = new QLabel();
        }
    }
}

void MainWindow::setFishPos(int x, int y)
{

    //listImage[x][y]->setPicture();
}

