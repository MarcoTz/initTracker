#include "trackform.h"
#include "ui_trackform.h"
#include <QDebug>

trackForm::trackForm(QWidget *parent, QList<QString> names, QList<int> inits, QList<int> hps) :
    QDialog(parent),
    ui(new Ui::trackForm)
{
    ui->setupUi(this);
    activeStyle = QString::fromStdString("QLabel { background-color : yellow }");
    charDeadStyle = QString::fromStdString("QLineEdit { color: red }");

    ui->gridLayout->removeWidget(ui->nextButton);
    ui->gridLayout->removeWidget(ui->doneButton);

    for(int i=0;i<names.length();i++){
        int maxInd = getHighestIndex(inits);

        chars << new QLabel(names.at(maxInd));
        charHPs << new QLineEdit(QString::number(hps.at(maxInd)));
        if(hps.at(maxInd)==0){charHPs.last()->setStyleSheet(charDeadStyle);}
        connect(charHPs.last(),SIGNAL(editingFinished()),this,SLOT(HPedited()));

        ui->gridLayout->addWidget(chars.last());
        ui->gridLayout->addWidget(charHPs.last());

        inits[maxInd] = -1;
    }

    ui->gridLayout->addWidget(ui->nextButton);
    ui->gridLayout->addWidget(ui->doneButton);

    chars.first()->setStyleSheet(activeStyle);
    if(charHPs.first()->text().toInt()==0){
        nextActive();
    }

}

trackForm::~trackForm()
{
    delete ui;
}

int trackForm::getHighestIndex(QList<int> lst)
{
    int highest = 0;

    for(int i=0; i<lst.length();i++){
        if(lst.at(i)>lst.at(highest)){
            highest = i;
        }
    }

    return highest;
}

void trackForm::on_doneButton_clicked()
{
    done(0);
}

void trackForm::on_nextButton_clicked(){
    nextActive();
}

void trackForm::nextActive()
{
    int next = 0;
    for(int i=0;i<chars.length();i++){

        if(chars.at(i)->styleSheet()==activeStyle){
            chars.at(i)->setStyleSheet("");
            next = (i+1)%chars.length();

            int whileCount = 0;
            while(charHPs.at(next)->text().toInt()==0){
                next = (next+1)%chars.length();
                if(whileCount>chars.length()){
                    next=-1;
                    break;
                }
                whileCount++;
            }

            if(next!=-1){
                chars.at(next)->setStyleSheet(activeStyle);
            }
            break;
        }
    }
}

void trackForm::HPedited()
{
    QLineEdit *current = qobject_cast<QLineEdit *>(QObject::sender());
    if(current->text().toInt()<=0){
        current->setText("0");
        current->setStyleSheet(charDeadStyle);
    }else{
        current->setStyleSheet("");
    }
}
