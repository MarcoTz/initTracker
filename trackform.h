#ifndef TRACKFORM_H
#define TRACKFORM_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>

namespace Ui {
class trackForm;
}

class trackForm : public QDialog
{
    Q_OBJECT

public:
    explicit trackForm(QWidget *parent = 0,QList<QString> = QList<QString>(), QList<int> = QList<int>(), QList<int> = QList<int>());
    ~trackForm();

private slots:

    void on_nextButton_clicked();

    void HPedited();

private:
    Ui::trackForm *ui;
    QList<QLabel *> chars;
    QList<QLineEdit *> charHPs;
    QList<QLineEdit *> charStatusses;
    int getHighestIndex(QList<int>);
    QString activeStyle;
    QString charDeadStyle;
    void nextActive();
};

#endif // TRACKFORM_H
