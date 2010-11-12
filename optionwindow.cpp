#include "optionwindow.h"


optionWindow::optionWindow(MainWindow *parent) :
    QDialog(parent),
    ui(new Ui::optionWindow)
{
    ui->setupUi(this);
    parW = parent;
    setWindowTitle("Options");
    ui->gW->setValue(parW->getGridWidth());
    ui->gH->setValue(parW->getGridHeight());
    ui->maxL_F->setValue(parW->getNbMaxLifeFishes());
    ui->maxL_S->setValue(parW->getNbMaxLifeSharks());
    ui->nbT->setValue(parW->getNbTurn());
    ui->decT_F->setValue(parW->getNbTurnBeforeDecayFishes());
    ui->decT_S->setValue(parW->getNbTurnBeforeDecaySharks());
    ui->starva_S->setValue(parW->getNbTurnBeforeStarvationSharks());
    ui->timeBProc_F->setValue(parW->getNbTurnBetweenProcFishes());
    ui->timeBProc_S->setValue(parW->getNbTurnBetweenProcSharks());
    ui->stN_F->setValue(parW->getStartFishes());
    ui->stN_S->setValue(parW->getStartSharks());


}
void optionWindow::on_buttonBox_accepted()
{
    parW->setGridWidth(ui->gW->value());
    parW->setGridHeight(ui->gH->value());
    parW->setNbMaxLifeFishes(ui->maxL_F->value());
    parW->setNbMaxLifeSharks(ui->maxL_S->value());
    parW->setNbTurn(ui->nbT->value());
    parW->setNbTurnBeforeDecayFishes(ui->decT_F->value());
    parW->setNbTurnBeforeDecaySharks(ui->decT_S->value());
    parW->setNbTurnBeforeStarvationSharks(ui->starva_S->value());
    parW->setNbTurnBetweenProcFishes(ui->timeBProc_F->value());
    parW->setNbTurnBetweenProcSharks(ui->timeBProc_S->value());
    parW->setStartFishes(ui->stN_F->value());
    parW->setStartSharks(ui->stN_S->value());
}
