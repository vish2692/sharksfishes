#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "optionwindow.h"
#include "qmylabel.h"
#include "simulation.h"
#include "fish.h"
#include "shark.h"
#include "./qwt/qwt_plot_curve.h"
#include "./qwt/qwt_legend_item.h"
#include <QDebug>


#include <math.h>

#define HEIGHT_MARGIN 160
#define WIDTH_MARGIN 50

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
    startAnimation->setIcon(QIcon(":/images/run.png"));

    optionMenu = menuBar()->addMenu("Option");
    preferences = new QAction("Preferences", this);
    preferences->setIcon(QIcon(":/images/preferences.png"));
    optionMenu->addAction(preferences);

    QAction *goStat = new QAction("Open statistic", this);
    goStat->setIcon(QIcon(":/images/stat_button.png"));
    optionMenu->addAction(goStat);

    QToolBar *toolBarFichier = ui->mainToolBar;
    toolBarFichier->addAction(startAnimation);
    toolBarFichier->addAction(preferences);
    toolBarFichier->addAction(goStat);


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
    connect(goStat, SIGNAL(triggered()),this,SLOT(launchStat()));

    show();
    setGeometry((QApplication::desktop()->screenGeometry().width()/2 - width()/2), (QApplication::desktop()->screenGeometry().height()/2 -                       height()/2), width(), height());

    m_gridWidth = 10;
    m_gridHeight = 10;
    m_nbTurn = 1000;
    m_nbStartSharks = 20;
    m_nbStartFishes = 50;
    m_nbMaxLifeSharks = 100;
    m_nbMaxLifeFishes = 100;
    m_nbTurnBetweenProcSharks = 30;
    m_nbTurnBetweenProcFishes = 30;
    m_nbTurnBeforeDecaySharks = 5;
    m_nbTurnBeforeDecayFishes = 5;
    m_nbTurnBeforeStarvationSharks = 30;
    m_nbTurnBabyTimeFish = 10;
    m_nbTurnBabyTimeShark = 10;
    m_turnTime = 100;
    m_displayRefresh = 500;

    m_sceneG = new QGraphicsScene(this);
    m_viewG = new QGraphicsView();
    m_viewG->setScene(m_sceneG);
    m_gridLayoutG = new QGraphicsGridLayout();
    m_gridLayoutG->setHorizontalSpacing(0);
    m_gridLayoutG->setVerticalSpacing(0);
    m_mdi = new QMdiArea(this);
    m_mdi->setViewMode(QMdiArea::TabbedView);


    setCentralWidget(m_mdi);

    m_columnSize = (frameGeometry().width() - WIDTH_MARGIN) / m_gridWidth;
    m_rowSize = (frameGeometry().height() - HEIGHT_MARGIN) / m_gridHeight;

    qDebug() << "Width: " << m_columnSize << " Height: " << m_rowSize;

    *m_fishPix = m_fishPix_original->scaled(m_rowSize,m_columnSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    *m_sharkPix = m_sharkPix_original->scaled(m_rowSize,m_columnSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    *m_fishBabyPix = m_fishBabyPix_original->scaled(m_rowSize,m_columnSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    *m_sharkBabyPix = m_sharkBabyPix_original->scaled(m_rowSize,m_columnSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    m_alreadyStat = false;


}

void MainWindow::launchStat()
{
    if(m_simulation != NULL && m_simulation->GetSimuState() == false && m_alreadyStat == false)
    {
        QwtPlot *plot = new QwtPlot(QwtText("Population"), this);
        QwtPlotCurve *curveFish = new QwtPlotCurve("Fishes");
        QwtPlotCurve *curveShark = new QwtPlotCurve("Sharks");
        double *x = (double *)malloc(m_simulation->GetTurnAtTheEnd()*sizeof(double));
        for(int iPos=0; iPos < m_simulation->GetTurnAtTheEnd(); iPos++)
        {
            x[iPos]=(double)iPos;
        }
        QwtPointArrayData *dataF = new QwtPointArrayData(x, m_simulation->GetStat()->getFishes(),m_simulation->GetTurnAtTheEnd());
        QwtPointArrayData *dataS = new QwtPointArrayData(x, m_simulation->GetStat()->getSharks(),m_simulation->GetTurnAtTheEnd());
        curveFish->setData(dataF);
        curveFish->attach(plot);
        curveFish->setPen(QPen(QColor(255,153,0)));
        curveFish->setRenderHint(QwtPlotItem::RenderAntialiased);
        curveShark->setData(dataS);
        curveShark->setPen(QPen(QColor(126,126,126)));
        curveShark->setRenderHint(QwtPlotItem::RenderAntialiased);
        curveShark->attach(plot);
        plot->setAxisTitle(2,"Nb Turns");
        plot->setAxisTitle(0,"Number of");
        QwtLegend *legend = new QwtLegend();
        plot->insertLegend(legend,QwtPlot::BottomLegend);
        QMdiSubWindow *subStat = new QMdiSubWindow(this);
        subStat->setWidget(plot);
        subStat->setAttribute(Qt::WA_DeleteOnClose);
        m_mdi->addSubWindow(subStat);
        subStat->setWindowTitle("Statistics");
        subStat->show();
        m_alreadyStat = true;
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *)
{
    if(m_launched == true)
    {
        m_columnSize = (frameGeometry().width() - WIDTH_MARGIN) / m_gridWidth;
        m_rowSize = (frameGeometry().height() - HEIGHT_MARGIN) / m_gridHeight;
        qDebug() << "Width: " << m_columnSize << " Height: " << m_rowSize;

        *m_fishPix = m_fishPix_original->scaled(m_columnSize,m_rowSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        *m_sharkPix = m_sharkPix_original->scaled(m_columnSize,m_rowSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        *m_fishBabyPix = m_fishBabyPix_original->scaled(m_columnSize,m_rowSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        *m_sharkBabyPix = m_sharkBabyPix_original->scaled(m_columnSize,m_rowSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        for(int iPos = 0; iPos < m_gridWidth; iPos++)
        {
            for(int iPos2 = 0; iPos2 < m_gridHeight; iPos2++)
            {
                listImage[iPos][iPos2]->setFixedWidth(m_columnSize);
                listImage[iPos][iPos2]->setFixedHeight(m_rowSize);
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
    //setStyleSheet("QMainWindow{background-image: url(:/images/background.png)}");
    QMdiSubWindow *subSimu = new QMdiSubWindow(this);
    subSimu->setWindowTitle("Simulation");
    subSimu->setAttribute(Qt::WA_DeleteOnClose);
    subSimu->setWidget(m_viewG);
    m_mdi->addSubWindow(subSimu);
    subSimu->setWindowState(Qt::WindowMaximized);
    m_progressLabel = new QLabel(subSimu);
    m_movie = new QMovie(subSimu);
    m_movie->setFileName(":/images/progress.gif");
    //movie->set
    m_progressLabel->setMovie(m_movie);
    m_progressLabel->show();
    m_progressLabel->setGeometry(3,3,60,60);
    m_movie->start();

    /*Create the sea object.*/
    Fish::InitVars(m_nbMaxLifeFishes, m_nbTurnBetweenProcFishes, m_nbTurnBeforeDecayFishes, m_nbTurnBabyTimeFish);
    Shark::InitVars(m_nbMaxLifeSharks, m_nbTurnBetweenProcSharks, m_nbTurnBeforeDecaySharks, m_nbTurnBabyTimeShark, m_nbTurnBeforeStarvationSharks);

    actualSea = new Sea(m_gridWidth, m_gridHeight, m_nbTurn, m_nbStartFishes, m_nbStartSharks);

    /*initialise our grid layout, depends on the options that the user made.*/
    listImage = QVector<QVector<QMyLabel *> >(m_gridWidth);
    for(int iPos = 0; iPos < m_gridWidth; iPos++)
    {
        listImage[iPos] = QVector<QMyLabel *>(m_gridHeight);
        for(int iPos2 = 0; iPos2 < m_gridHeight; iPos2++)
        {
            listImage[iPos][iPos2] = new QMyLabel();
            listImage[iPos][iPos2]->setFixedWidth(m_columnSize);
            listImage[iPos][iPos2]->setFixedHeight(m_rowSize);
            QGraphicsWidget *localGWidget = m_sceneG->addWidget(listImage[iPos][iPos2]);
            m_gridLayoutG->addItem(localGWidget, iPos, iPos2);
            Animal *localAnimal = actualSea->Get(iPos,iPos2);
            if(localAnimal != NULL && localAnimal->GetType() == FISH)
            {
                setFishPos(iPos,iPos2);
                listImage[iPos][iPos2]->SetType(Fish);
            }
            else if(localAnimal != NULL && localAnimal->GetType() == SHARK)
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

    m_columnSize = (frameGeometry().width() - WIDTH_MARGIN) / m_gridWidth;
    m_rowSize = (frameGeometry().height() - HEIGHT_MARGIN) / m_gridHeight;
    qDebug() << "Width: " << m_columnSize << " Height: " << m_rowSize;

    *m_fishPix = m_fishPix_original->scaled(m_columnSize,m_rowSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    *m_sharkPix = m_sharkPix_original->scaled(m_columnSize,m_rowSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    *m_fishBabyPix = m_fishBabyPix_original->scaled(m_columnSize,m_rowSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    *m_sharkBabyPix = m_sharkBabyPix_original->scaled(m_columnSize,m_rowSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    for(int iPos = 0; iPos < m_gridWidth; iPos++)
    {
        for(int iPos2 = 0; iPos2 < m_gridHeight; iPos2++)
        {
            listImage[iPos][iPos2]->setFixedWidth(m_columnSize);
            listImage[iPos][iPos2]->setFixedHeight(m_rowSize);
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

    //Now run the simulation.
    m_simulation = new Simulation(actualSea, m_turnTime);
    m_timeRefresh = new QTimer(this);
    m_timeRefresh->setInterval(m_displayRefresh);
    connect(m_timeRefresh, SIGNAL(timeout()), this, SLOT(updateGrid()));
    m_simulation->start();
    m_timeRefresh->start();
}

void MainWindow::updateGrid()
{
    if(m_simulation->GetSimuState() == true)    //Simulation is running.
    {
        for(int iWidthPos = 0; iWidthPos < m_gridWidth; iWidthPos++)
        {
            for(int iHeightPos = 0; iHeightPos < m_gridHeight; iHeightPos++)
            {
                Animal *localAnimal = actualSea->Get(iWidthPos, iHeightPos);
                if(localAnimal == NULL)  //Nothing to display
                {
                    setNothingPos(iWidthPos,iHeightPos);
                }
                else if(localAnimal->GetType() == SHARK)
                {
                    setSharkPos(iWidthPos,iHeightPos);
                }
                else if(localAnimal->GetType() == FISH)
                {
                    setFishPos(iWidthPos,iHeightPos);
                }
            }
        }
    }
    else
    {
        for(int iWidthPos = 0; iWidthPos < m_gridWidth; iWidthPos++)
        {
            for(int iHeightPos = 0; iHeightPos < m_gridHeight; iHeightPos++)
            {
                Animal *localAnimal = actualSea->Get(iWidthPos, iHeightPos);
                if(localAnimal == NULL)  //Nothing to display
                {
                    setNothingPos(iWidthPos,iHeightPos);
                }
                else if(localAnimal->GetType() == SHARK)
                {
                    setSharkPos(iWidthPos,iHeightPos);
                }
                else if(localAnimal->GetType() == FISH)
                {
                    setFishPos(iWidthPos,iHeightPos);
                }
            }
        }
        m_progressLabel->clear();
    }
}

void MainWindow::setNothingPos(int x, int y)
{
     listImage[x][y]->clear();
}

void MainWindow::setFishPos(int x, int y)
{
    listImage[x][y]->setPixmap(*m_fishPix);
}

void MainWindow::setSharkPos(int x, int y)
{
    listImage[x][y]->setPixmap(*m_sharkPix);
}

