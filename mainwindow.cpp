#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_scene = new CGraphicsSecene;
    ui->graphicsView->setScene(m_scene);

    connect(m_scene, SIGNAL(clickedOnField(QPointF)), this, SLOT(clickedOnField(QPointF)));
}


MainWindow::~MainWindow()
{
    delete ui;
    delete m_scene;
}


void MainWindow::resizeEvent(QResizeEvent *event)
{
    if (!ui->lineEdit->text().isEmpty())
    {
        clearField();
        FieldXorO();
        for (int indexOfPos = 0; indexOfPos < posZone.size(); indexOfPos ++)
            reDrowFigur(indexOfPos);
    }
}

void MainWindow::reDrowFigur(int target)
{
    switch (posZone[target]) {
    case 1:
        drowX(target);
        break;
    case 2:
        drowZero(target);
    default:
        break;
    }
}

void MainWindow::on_pushButton_Draw_clicked()
{
    int grid;
    grid = ui->lineEdit->text().toInt();
    for (int i = 0; i < grid * grid; ++i)
        posZone[i] = 0;
    FieldXorO();
}


void MainWindow::FieldXorO()
{
    int heightField, widthField;
    auto [heightFieldOffset, widthFieldOffset, grid] = calculateCellSize();
    heightField = ui->graphicsView->height();
    widthField = ui->graphicsView->width();
    int x = 0, y = 0, x0 = 0, y0 = 0;


    for (int i = 0; i < grid; i++)
    {
        x += widthFieldOffset;
        y += heightFieldOffset;
//        qDebug() << i;
        m_scene->addLine(x, y0, x, y0 + heightField);
        m_scene->addLine(x0, y, x0 + widthField, y);

    }
}

void MainWindow::clickedOnField(QPointF pos)
{
    checkClickOnField(pos.x(), pos.y());
//    qDebug() << pos << "Now here:)";
}

std::tuple<int, int, int> MainWindow::calculateCellSize()
{
    int heightField, widthField, heightFieldOffset, widthFieldOffset, grid;
    grid = ui->lineEdit->text().toInt();
    qDebug() << grid;

    heightField = ui->graphicsView->height();
    widthField = ui->graphicsView->width();
    heightFieldOffset = heightField / grid;
    widthFieldOffset  = widthField / grid ;
    return {heightFieldOffset, widthFieldOffset, grid};
}

void MainWindow::checkClickOnField(int x, int y)
{
    qDebug() << x;
    int heightField, widthField, clickedZone = 0;
    auto [heightFieldOffset, widthFieldOffset, grid] = calculateCellSize();
    for (int i = 0; i < grid; i ++)
    {
        if ((y < i * heightFieldOffset) or y > (i + 1) * heightFieldOffset)
            continue;

        for (int j = 0 ; j < grid; j ++)
        {
            if (x < j * widthFieldOffset or x > (j + 1) * widthFieldOffset)
                continue;

            clickedZone = i * grid + j;

            break;
        }

        break;
    }

    checkZone(clickedZone, grid);
}

void MainWindow::whoWin(int grid)
{
//    int x_match, y_match = 0;
//    for (int i = 0; i < posZone.size() / grid; i++)
//    {
//        x_match = 0;
//        for (int j = 0; j < posZone.size() / grid; j ++)
//        {
//            y_match = 0;
//            if (posZone[i * j == 1])
//                x_match ++;
//            else if (posZone[i * j == 2])
//                {
//                    y_match++;
//                }
//            if (y_match == 3 and x_match == 3)
//                qDebug() << "WIN";


//        }
//    }
}


void MainWindow::checkZone(int target, int grid)
{
    switch (posZone[target]) {
    case 0:
        if (whoseMove % 2 == 1)
        {
            posZone[target] = 2;
            drowZero(target);
        }
        else
        {
            posZone[target] = 1;
            drowX(target);
        }
        whoWin(grid);
        whoseMove ++;
        qDebug() << whoseMove;

        break;
    case 1:

        qDebug() << "Dont drow. This X";
        break;
    case 2:

        qDebug() << "This O";
        break;
    default:
        break;
    }
}


void MainWindow::drowZero(int target)
{
    int x, y, w, h;
    int i, j;
    auto [heightFieldOffset, widthFieldOffset, grid] = calculateCellSize();
    h = heightFieldOffset - heightFieldOffset * 0.1;
    w = widthFieldOffset - widthFieldOffset * 0.1;
    j = target / grid;
    i = target - j * grid;
    y = j * heightFieldOffset + 0.05 * heightFieldOffset;
    x = i * widthFieldOffset + 0.05 * widthFieldOffset;
    m_scene->addEllipse(x, y, w, h);
}

void MainWindow::drowX(int target)
{
    int x1, x1_2, x2, x2_2, y1, y1_2, y2, y2_2;
    int j, i;
    auto [heightFieldOffset, widthFieldOffset, grid] = calculateCellSize();
    j = target / grid;
    i = target - j * grid;
    x1 = i *         widthFieldOffset  + 0.05 * widthFieldOffset;
    y1 = j *         heightFieldOffset + 0.05 * heightFieldOffset;
    x2 = (i + 1) *   widthFieldOffset  - 0.05 * widthFieldOffset;
    y2 = (j + 1) *   heightFieldOffset - 0.05 * heightFieldOffset;
    x2_2 = i *       widthFieldOffset  + 0.05 * widthFieldOffset;
    y2_2 = (j + 1) * heightFieldOffset - 0.05 * heightFieldOffset;
    x1_2 = (i + 1) * widthFieldOffset  - 0.05 * widthFieldOffset;
    y1_2 = j *       heightFieldOffset + 0.05 * heightFieldOffset;
    m_scene->addLine(x1, y1, x2, y2);
    m_scene->addLine(x1_2, y1_2, x2_2, y2_2);
}

void MainWindow::clearField()
{
    m_scene->clear();
}

void MainWindow::on_pushButton_Clear_clicked()
{
   clearField();
}
