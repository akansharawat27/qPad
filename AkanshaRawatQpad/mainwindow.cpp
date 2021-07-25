#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_actionNew_triggered()
{
    mFilename="";
    ui->textEdit->setPlainText("");
}


void MainWindow::on_actionOpen_triggered()
{
    QString file= QFileDialog::getOpenFileName(this,"Open a file");
    if(!file.isEmpty()){
        QFile sFile(file);
        if(sFile.open(QFile::ReadOnly | QFile::Text)){
            mFilename = file;
            QTextStream in(&sFile);
            QString text = in.readAll();
            sFile.close();

            ui->textEdit->setPlainText(text);
        }
    }
}


void MainWindow::on_actionSave_triggered()
{
    if(mFilename.isEmpty()){
        on_actionSave_As_triggered();
    }
    else{
        QFile sFile(mFilename);
        if(sFile.open(QFile::WriteOnly | QFile::Text)){
            QTextStream out(&sFile);

            out<<ui->textEdit->toPlainText();

            sFile.flush();
            sFile.close();
        }
    }
}


void MainWindow::on_actionSave_As_triggered()
{
    QString file= QFileDialog::getSaveFileName(this,"Open a file");
    if(!file.isEmpty()){
        mFilename = file;
        on_actionSave_triggered();
    }
}


void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}


void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}


void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}


void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}


void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}


void MainWindow::on_actionAbout_Me_triggered()
{
    QDesktopServices::openUrl(QUrl("/home/asr16/qPad/CV_Akansha_Rawat.pdf", QUrl::TolerantMode));
}


void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}


void MainWindow::on_actionBold_triggered(bool checked)
{
    checked? ui->textEdit->setFontWeight(QFont::Bold):
             ui->textEdit->setFontWeight(QFont::Normal);
}


void MainWindow::on_actionSuperscript_triggered(bool checked)
{
    QString text = ui->textEdit->toPlainText();
    QString selectedText = ui->textEdit->textCursor().selectedText();
    qint32 x = ui->textEdit->textCursor().selectionStart();
    ui->textEdit->textCursor().removeSelectedText();
    QString superscript = ui->textEdit->toPlainText();
    superscript.insert(x,"<sup>"+ selectedText +"</sup>");
    checked? ui->textEdit->setText(superscript):
             ui->textEdit->setText(text);
}


void MainWindow::on_actionSubscript_triggered(bool checked)
{
    QString text = ui->textEdit->toPlainText();
    QString selectedText = ui->textEdit->textCursor().selectedText();
    qint32 x = ui->textEdit->textCursor().selectionStart();
    ui->textEdit->textCursor().removeSelectedText();
    QString subscript = ui->textEdit->toPlainText();
    subscript.insert(x,"<sub>"+ selectedText +"</sub>");
    checked? ui->textEdit->setText(subscript):
             ui->textEdit->setText(text);
}



