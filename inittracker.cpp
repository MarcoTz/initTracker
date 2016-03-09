#include "inittracker.h"
#include "ui_inittracker.h"
#include <QDebug>

initTracker::initTracker(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::initTracker)
{
    ui->setupUi(this);
    addChar();
}

initTracker::~initTracker()
{
    delete ui;
}

void initTracker::addChar()
{
    ui->centralWidget->layout()->removeWidget(ui->okButton);

    for(int i=0;i<3;i++){
        characters[i] << new QLineEdit("unnamed");
        ui->centralWidget->layout()->addWidget(characters[i].last());
        if(i!=0){
            connect(characters[i].last(),SIGNAL(editingFinished()),this,SLOT(sanitizeInput()));
            characters[i].last()->setText("1");
        }
    }

    removeButtons << new QPushButton(QApplication::style()->standardIcon(QStyle::SP_TrashIcon),"");
    ui->centralWidget->layout()->addWidget(removeButtons.last());
    connect(removeButtons.last(),SIGNAL(clicked()),this,SLOT(removeChar()));


    ui->centralWidget->layout()->addWidget(ui->okButton);
}

void initTracker::on_addButton_clicked()
{
    addChar();
}

void initTracker::removeChar(){
    int row = removeButtons.indexOf(qobject_cast<QPushButton *>(QObject::sender()));
    delete removeButtons.at(row);
    removeButtons.removeAt(row);

    for(int i=0;i<3;i++){
        delete characters[i].at(row);
        characters[i].removeAt(row);
    }
}

void initTracker::on_actionClear_triggered()
{
    for(int i=0;i<removeButtons.size();i++){
        delete removeButtons.at(i);
        for(int j=0;j<3;j++){
            delete characters[j].at(i);
        }
    }

    removeButtons.clear();
    for(int i=0;i<3;i++){
        characters[i].clear();
    }

    resize(0,0);
}

void initTracker::on_actionExit_triggered()
{
    qApp->quit();
}

void initTracker::on_okButton_clicked()
{
    if(removeButtons.isEmpty()){
        return;
    }

    QList<QString> names;
    QList<int> inits;
    QList<int> hps;

    ui->okButton->setEnabled(false);
    ui->addButton->setEnabled(false);

    for(int i=0;i<removeButtons.length();i++){

        removeButtons.at(i)->setEnabled(false);

        names << characters[0].at(i)->text();
        inits << characters[1].at(i)->text().toInt();
        hps << characters[2].at(i)->text().toInt();

        for(int j=0;j<3;j++){
            characters[j].at(i)->setEnabled(false);
        }
    }


    tracker = new trackForm(this,names,hps,inits);
    connect(tracker,SIGNAL(finished(int)),this,SLOT(doneTracking()));
    tracker->show();
}

void initTracker::doneTracking()
{
    ui->okButton->setEnabled(true);
    ui->addButton->setEnabled(true);

    for(int i=0;i<removeButtons.length();i++){
        removeButtons.at(i)->setEnabled(true);
        for(int j=0;j<3;j++){
            characters[j].at(i)->setEnabled(true);
        }
    }

    delete tracker;
}

void initTracker::sanitizeInput()
{
    QLineEdit *current = qobject_cast<QLineEdit *>(QObject::sender());
    if(current->text().toInt()<=0){
        current->setText("0");
    }
}
