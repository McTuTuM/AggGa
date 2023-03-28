#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QResizeEvent>
#include <tuple>
#include <QMap>
#include "cgraphicssecene.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QMap <int, int> posZone;


private slots:
    void on_pushButton_Draw_clicked();
    void on_pushButton_Clear_clicked();
    void clearField();
    void resizeEvent(QResizeEvent * event) override;
    void clickedOnField(QPointF pos);
    void checkClickOnField(int x, int y);

private:
    Ui::MainWindow *ui;
    CGraphicsSecene *m_scene;
    void checkZone(int target, int grid);
    void FieldXorO();
    void drowZero(int target);
    void drowX(int target);
    void reDrowFigur(int target);
    void whoWin(int grid);
    std::tuple<int, int, int> calculateCellSize();
    int whoseMove = 0;
};
#endif // MAINWINDOW_H
