#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtGui>
#include <QApplication>
#include "sea.h"
#include "simulation.h"
#include "./qwt/qwt_plot.h"

namespace Ui {
    class MainWindow;
}

class QMyLabel;
class optionWindow;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    /*Getter and Setter.*/
    inline int getGridWidth(){return m_gridWidth;}
    inline int getGridHeight(){return m_gridHeight;}
    inline int getNbTurn(){return m_nbTurn;}
    inline int getStartSharks(){return m_nbStartSharks;}
    inline int getStartFishes(){return m_nbStartFishes;}
    inline int getNbMaxLifeSharks(){return m_nbMaxLifeSharks;}
    inline int getNbMaxLifeFishes(){return m_nbMaxLifeFishes;}
    inline int getNbTurnBetweenProcSharks(){return m_nbTurnBetweenProcSharks;}
    inline int getNbTurnBetweenProcFishes(){return m_nbTurnBetweenProcFishes;}
    inline int getNbTurnBeforeDecaySharks(){return m_nbTurnBeforeDecaySharks;}
    inline int getNbTurnBeforeDecayFishes(){return m_nbTurnBeforeDecayFishes;}
    inline int getNbTurnBeforeStarvationSharks(){return m_nbTurnBeforeStarvationSharks;}
    inline int getNbTurnBabyTimeFish(){return m_nbTurnBabyTimeFish;}
    inline int getNbTurnBabyTimeShark(){return m_nbTurnBabyTimeShark;}
    inline int getDisplayRefresh(){return m_displayRefresh;}
    inline int getTurnTime(){return m_turnTime;}

    void setFishPos(int x, int y);
    void setSharkPos(int x, int y);
    void setNothingPos(int x, int y);
    void resizeEvent(QResizeEvent *);

public slots:
    void startAnim();
    void showOptions();
    inline void setGridWidth(int p_val){m_gridWidth = p_val;}
    inline void setGridHeight(int p_val){m_gridHeight = p_val;}
    inline void setNbTurn(int p_val){m_nbTurn = p_val;}
    inline void setStartSharks(int p_val){m_nbStartSharks = p_val;}
    inline void setStartFishes(int p_val){m_nbStartFishes = p_val;}
    inline void setNbMaxLifeSharks(int p_val){m_nbMaxLifeSharks = p_val;}
    inline void setNbMaxLifeFishes(int p_val){m_nbMaxLifeFishes = p_val;}
    inline void setNbTurnBetweenProcSharks(int p_val){m_nbTurnBetweenProcSharks = p_val;}
    inline void setNbTurnBetweenProcFishes(int p_val){m_nbTurnBetweenProcFishes = p_val;}
    inline void setNbTurnBeforeDecaySharks(int p_val){m_nbTurnBeforeDecaySharks = p_val;}
    inline void setNbTurnBeforeDecayFishes(int p_val){m_nbTurnBeforeDecayFishes = p_val;}
    inline void setNbTurnBeforeStarvationSharks(int p_val){m_nbTurnBeforeStarvationSharks = p_val;}
    inline void setNbTurnBabyTimeFish(int p_val){m_nbTurnBabyTimeFish = p_val;}
    inline void setNbTurnBabyTimeShark(int p_val){m_nbTurnBabyTimeShark = p_val;}
    inline void setDisplayRefresh(int p_val){m_displayRefresh = p_val;}
    inline void setTurnTime(int p_val){m_turnTime = p_val;}

    void updateGrid();
    void launchStat();

private:
    Ui::MainWindow *ui;
    QVector< QVector<QMyLabel *> > listImage;
    QMenu *fileMenu;
    QAction *startAnimation;
    QMenu *optionMenu;
    QAction *preferences;
    Sea *actualSea;
    Simulation *m_simulation;
    optionWindow *optionW;

    /*Options variables.*/
    int m_gridWidth;
    int m_gridHeight;
    int m_nbTurn;
    int m_nbStartSharks;
    int m_nbStartFishes;
    int m_nbMaxLifeSharks;
    int m_nbMaxLifeFishes;
    int m_nbTurnBetweenProcSharks;
    int m_nbTurnBetweenProcFishes;
    int m_nbTurnBeforeDecaySharks;
    int m_nbTurnBeforeDecayFishes;
    int m_nbTurnBeforeStarvationSharks;
    int m_nbTurnBabyTimeFish;
    int m_nbTurnBabyTimeShark;
    int m_displayRefresh;
    int m_turnTime;

    QPixmap *m_fishPix;
    QPixmap *m_sharkPix;
    QPixmap *m_fishBabyPix;
    QPixmap *m_sharkBabyPix;

    QPixmap *m_fishPix_original;
    QPixmap *m_sharkPix_original;
    QPixmap *m_fishBabyPix_original;
    QPixmap *m_sharkBabyPix_original;

    QGraphicsScene *m_sceneG;
    QGraphicsView *m_viewG;
    QGraphicsGridLayout *m_gridLayoutG;

    int m_rowSize;
    int m_columnSize;
    bool m_launched;
    QMdiArea *m_mdi;
    QTimer *m_timeRefresh;
    QMovie *m_movie;
    QLabel *m_progressLabel;
    bool m_alreadyStat;

    bool m_simulIsLaunch();

    bool m_simulAlreadyLaunched;
    QMdiSubWindow *subSimu;
    QMdiSubWindow *subStat;
    QAction *goStat;

private slots:

};

#endif // MAINWINDOW_H
