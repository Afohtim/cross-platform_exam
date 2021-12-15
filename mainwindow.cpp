#include "mainwindow.h"
#include "ui_mainwindow.h"

const float EPS = 0.0001;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->solve_button, SIGNAL(clicked()), this, SLOT(solve()));
}

float f(float x)
{
    return 2.0f * x * x - 4.0f * x - 20.0f;
}


float MainWindow::solve(float a, float b)
{
    if(f(a) * f(b) > 0)
        return NULL;
    float m = (a + b) / 2;
    while(abs(f(m)) > EPS)
    {
        m = (a + b) / 2;
        if(f(m) * f(a) < 0)
        {
            b = m;
        }
        else
        {
            a = m;
        }
    }
    return m;
}

void MainWindow::solve()
{
    QString a_str = ui->text_input_a->toPlainText();
    QString b_str = ui->text_input_b->toPlainText();
    bool ok;
    float a = a_str.toFloat(&ok);
    if(!ok)
    {
        ui->text_output->setText("A is NaN");
        return;
    }

    float b = b_str.toFloat(&ok);
    if(!ok)
    {
        ui->text_output->setText("B is NaN");
        return;
    }

    float ans = solve(a,b);
    if(ans == NULL)
    {
        ui->text_output->setText("A and B have same sign");
        return;
    }
     ui->text_output->setText(QString::number(ans));
}

MainWindow::~MainWindow()
{
    delete ui;
}

