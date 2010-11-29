#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "optionwindow.h"
#include "qmylabel.h"

#include <math.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    m_launched = false;
    ui->setupUi(this);
    setWindowTitle("Shark and Fishes !");
    fileMenu = menuBar()->addMenu("File");
    startAnimation = new QAction("Start simulation", this);
    fileMenu->addAction(startAnimation);

    optionMenu = menuBar()->addMenu("Option");
    preferences = new QAction("Preferences", this);
    optionMenu->addAction(preferences);

    m_fishPix = new QPixmap(":/images/fish.png");
    m_sharkPix= new QPixmap(":/images/shark.png");
    m_fishBabyPix= new QPixmap(":/images/fish.png");
    m_sharkBabyPix= new QPixmap(":/images/shark.png");

    m_fishPix_original = new QPixmap(":/images/fish.png");
    m_sharkPix_original = new QPixmap(":/images/shark.png");
    m_fishBabyPix_original = new QPixmap(":/images/fish.png");
    m_sharkBabyPix_original = new QPixmap(":/images/shark.png");

    /*Connect the startAction menu to our custom slot.*/
    connect(startAnimation,SIGNAL(triggered()),this,SLOT(startAnim()));
    connect(preferences,SIGNAL(triggered()),this,SLOT(showOptions()));

    show();
    setGeometry((QApplication::desktop()->screenGeometry().width()/2 - width()/2), (QApplication::desktop()->screenGeometry().height()/2 -                       height()/2), width(), height());

    m_gridWidth = 10;
    m_gridHeight = 10;
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

    m_sceneG = new QGraphicsScene(this);
    m_viewG = new QGraphicsView();
    m_viewG->setScene(m_sceneG);
    m_gridLayoutG = new QGraphicsGridLayout();
    setCentralWidget(m_viewG);

    m_rowSize = geometry().width() / m_gridWidth;
    m_columnSize = geometry().height() / m_gridHeight;

    *m_fishPix = m_fishPix_original->scaled(m_rowSize,m_columnSize, Qt::KeepAspectRatio);
    *m_sharkPix = m_sharkPix_original->scaled(m_rowSize,m_columnSize, Qt::KeepAspectRatio);
    *m_fishBabyPix = m_fishBabyPix_original->scaled(m_rowSize,m_columnSize, Qt::KeepAspectRatio);
    *m_sharkBabyPix = m_sharkBabyPix_original->scaled(m_rowSize,m_columnSize, Qt::KeepAspectRatio);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *)
{

    m_rowSize = geometry().width() / m_gridWidth;
    m_columnSize = geometry().height() / m_gridHeight;

    *m_fishPix = m_fishPix_original->scaled(m_rowSize,m_columnSize, Qt::KeepAspectRatio);
    *m_sharkPix = m_sharkPix_original->scaled(m_rowSize,m_columnSize, Qt::KeepAspectRatio);
    *m_fishBabyPix = m_fishBabyPix_original->scaled(m_rowSize,m_columnSize, Qt::KeepAspectRatio);
    *m_sharkBabyPix = m_sharkBabyPix_original->scaled(m_rowSize,m_columnSize, Qt::KeepAspectRatio);

    if(m_launched == true)
    {
        for(int iPos = 0; iPos < m_gridWidth; iPos++)
        {
            for(int iPos2 = 0; iPos2 < m_gridHeight; iPos2++)
            {
                listImage[iPos][iPos2]->setFixedWidth(m_rowSize);
                listImage[iPos][iPos2]->setFixedHeight(m_columnSize);
                if(listImage[iPos][iPos2]->GetType() == Fish)
                {
                    setFishPos(iPos,iPos2);
                }
                else if(listImage[iPos][iPos2]->GetType() == Shark)
                {
                    setSharkPos(iPos,iPos2);
                }

            }
        }
    }
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
    listImage = QVector<QVector<QMyLabel *> >(m_gridWidth);
    for(int iPos = 0; iPos < m_gridWidth; iPos++)
    {
        listImage[iPos] = QVector<QMyLabel *>(m_gridHeight);
        for(int iPos2 = 0; iPos2 < m_gridHeight; iPos2++)
        {
            listImage[iPos][iPos2] = new QMyLabel();
            listImage[iPos][iPos2]->setFixedWidth(m_rowSize);
            listImage[iPos][iPos2]->setFixedHeight(m_columnSize);
            QGraphicsWidget *localGWidget = m_sceneG->addWidget(listImage[iPos][iPos2]);
            m_gridLayoutG->addItem(localGWidget, iPos, iPos2);
            if(rand() % 100 < 15)
            {
                setFishPos(iPos,iPos2);
                listImage[iPos][iPos2]->SetType(Fish);
            }
            else if(rand() % 100 < 15)
            {
                setSharkPos(iPos, iPos2);
                listImage[iPos][iPos2]->SetType(Shark);
            }
            else
            {
                listImage[iPos][iPos2]->SetType(Nothing);
            }
        }
    }
    QGraphicsWidget *form = new QGraphicsWidget;
    form->setLayout(m_gridLayoutG);
    m_sceneG->addItem(form);
    m_launched = true;
}

void MainWindow::setFishPos(int x, int y)
{
    listImage[x][y]->setPixmap(*m_fishPix);
}

void MainWindow::setSharkPos(int x, int y)
{
    listImage[x][y]->setPixmap(*m_sharkPix);
}
