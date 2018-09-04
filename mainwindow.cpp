#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTableView>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    model = new QStandardItemModel(0,0,this);
    modelB = new QStandardItemModel(0,0,this);
    modelR = new QStandardItemModel(0,0,this);
    ui->matrixA->setModel(model);
    ui->matrixB->setModel(modelB);
    ui->resultMatrix->setModel(modelR);
}

MainWindow::~MainWindow()
{
    delete ui;
}
bool MainWindow::isNumber(QString a)
{
    bool success;
    a.toDouble(&success);
    return success;
}
void MainWindow::add()
{
    ui->resultMatrix->model()->insertRows(0, ui->matrixA->model()->rowCount());
    ui->resultMatrix->model()->insertColumns(0, ui->matrixA->model()->columnCount());
    for (int r = 0; r < ui->resultMatrix->model()->rowCount(); r++)
    {
        for (int c = 0; c < ui->resultMatrix->model()->columnCount(); c++)
        {
            QModelIndex aIndex = model->index(r,c);
            QModelIndex rIndex = modelR->index(r,c);
            QModelIndex bIndex = modelB->index(r,c);
            if((!isNumber(model->data(aIndex).toString()) || (!isNumber(modelB->data(bIndex).toString()))))
            {
                 ui->label_3->setText("One or more of the given elements is invalid, so the operation could not be completed.");
                 modelR->clear();
                 return; //Exiting function and leaving result matrix blank if matrix A or B contains invalid input
            }
            double num = model->data(aIndex).toDouble() + modelB->data(bIndex).toDouble();
            modelR->setData(rIndex,num);
        }
    }
    ui->label->setText(QString::number(model->rowCount()) + "\t X \t" + QString::number(model->columnCount()));
}
void MainWindow::multiply()
{
    ui->resultMatrix->model()->insertRows(0,ui->matrixA->model()->rowCount());
    ui->resultMatrix->model()->insertColumns(0, ui->matrixB->model()->columnCount());
    //setting all values in result matrix to 0
    for (int r = 0; r < ui->resultMatrix->model()->rowCount(); r++)
    {
        for (int c = 0; c < ui->resultMatrix->model()->columnCount(); c++)
        {
            QModelIndex index = modelR->index(r,c);
            modelR->setData(index,0);
        }
    }
    int c2 = modelB->columnCount();
    int r1 = model->rowCount();
    int r2 = modelB->rowCount();
    //multiplying j vectors (columns of B) with n elements in each by h rows of a
    for (int j = 0; j < c2; j++)
    {
        for (int h = 0; h < r1; h++)
        {
            for (int n = 0; n < r2; n++)
            {
                QModelIndex aIndex = model->index(h,n);
                QModelIndex rIndex = modelR->index(h,j);
                QModelIndex bIndex = modelB->index(n,j);
                if((!isNumber(model->data(aIndex).toString()) || (!isNumber(modelB->data(bIndex).toString()))))
                {
                     ui->label_3->setText("One or more of the given elements is invalid, so the operation could not be completed.");
                     modelR->clear();
                     return; //Exiting function and leaving result matrix blank if matrix A or B contains invalid input
                }
                double element = modelR->data(rIndex).toDouble();
                element += (modelB->data(bIndex).toDouble()) * (model->data(aIndex).toDouble());
                modelR->setData(rIndex,element);
            }
        }
    }
    ui->label->setText(QString::number(r1) + "\t X \t" + QString::number(c2));
}
void MainWindow::on_rB_2_textChanged(const QString &arg1)
{
    int addrow;
    int newrow = ui->rB_2->text().toInt();
    if (newrow > model->rowCount())
    {
        addrow = newrow - model->rowCount();
        for (int r = 0; r < addrow; r++)
        {
            int index = model->rowCount();
            ui->matrixA->model()->insertRow(index);
        }
    }
    else if (newrow < model->rowCount())
    {
        int delrow = model->rowCount()-newrow;
        for (int r = 0; r < delrow; r++)
        {
            int index = model->rowCount();
            ui->matrixA->model()->removeRow(index-1);
        }
    }
    if (ui->comboBox->currentText() == "Addition")
    {
        ui->rB->setText(ui->rB_2->text());
    }
}

void MainWindow::on_cA_textChanged(const QString &arg1)
{
    int addcol;
    int newcol = ui->cA->text().toInt();
    addcol = newcol - model->columnCount();
    if (addcol >= 0)
    {
        for (int c = 0; c < addcol; c++)
        {
            int index = model->columnCount();
            ui->matrixA->model()->insertColumn(index);
        }
    }
    else
    {
        int delcol = -1 * addcol;
        for (int c = 0; c < delcol; c++)
        {
            int index = model->columnCount();
            ui->matrixA->model()->removeColumn(index-1);
        }
    }
    if (ui->comboBox->currentText() == "Addition")
    {
        ui->cB->setText(ui->cA->text());
    }
    if (ui->comboBox->currentText() == "Multiplication")
    {
        ui->rB->setText(ui->cA->text());
    }
}

void MainWindow::on_rB_textChanged(const QString &arg1)
{
    // row b
    int addrow;
    int newrow = ui->rB->text().toInt();
    if (newrow > modelB->rowCount())
    {
        addrow = newrow - modelB->rowCount();
        for (int r = 0; r < addrow; r++)
        {
            int index = modelB->rowCount();
            ui->matrixB->model()->insertRow(index);
        }
    }
    else if (newrow < modelB->rowCount())
    {
        int delrow = modelB->rowCount()-newrow;
        for (int r = 0; r < delrow; r++)
        {
            int index = modelB->rowCount();
            ui->matrixB->model()->removeRow(index-1);
        }
    }
    if (ui->comboBox->currentText() == "Addition")
    {
        ui->rB_2->setText(ui->rB->text());
    }
    if (ui->comboBox->currentText() == "Multiplication")
    {
        ui->cA->setText(ui->rB->text());
    }
}

void MainWindow::on_cB_textChanged(const QString &arg1)
{
    //col b
    int addcol;
    int newcol = ui->cB->text().toInt();
    addcol = newcol - modelB->columnCount();
    if (addcol >= 0)
    {
        for (int c = 0; c < addcol; c++)
        {
            int index = modelB->columnCount();
            ui->matrixB->model()->insertColumn(index);
        }
    }
    else
    {
        int delcol = -1 * addcol;
        for (int c = 0; c < delcol; c++)
        {
            int index = modelB->columnCount();
            ui->matrixB->model()->removeColumn(index-1);
        }
    }
    if (ui->comboBox->currentText() == "Addition")
    {
        ui->cA->setText(ui->cB->text());
    }
}

void MainWindow::on_pushButton_clicked()
{
    modelR->clear();
    if(ui->comboBox->currentText() == "Addition")
    {
        add();
    }
    if(ui->comboBox->currentText() == "Multiplication")
    {
        multiply();
    }

}
void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    //Resetting error message and result matrix
    modelR->clear();
    ui->label_3->clear();
    ui->label->clear();
    if(ui->comboBox->currentText() == "Multiplication")
    {
        //Displaying operation symbol
        ui->oLabel->setText("x");
        //Ensuring valid dimensions for multiplication
        ui->rB->setText(ui->cA->text());
    }
    if(ui->comboBox->currentText() == "Addition")
    {
        //Displaying operation symbol
        ui->oLabel->setText("+");
        //Ensuring valid dimensions for multiplication
        ui->rB->setText(ui->rB_2->text());
        ui->cB->setText(ui->cA->text());
    }
}
