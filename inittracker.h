#ifndef INITTRACKER_H
#define INITTRACKER_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include "trackform.h"

namespace Ui {
class initTracker;
}

class initTracker : public QMainWindow
{
    Q_OBJECT

public:
    explicit initTracker(QWidget *parent = 0);
    ~initTracker();

private slots:
    void on_addButton_clicked();

    void removeChar();

    void doneTracking();

    void sanitizeInput();

    void on_actionClear_triggered();

    void on_actionExit_triggered();

    void on_okButton_clicked();

private:
    Ui::initTracker *ui;
    QList<QLineEdit *> characters [3];
    QList<QPushButton *> removeButtons;
    QList<QLabel *> active;
    trackForm *tracker;
    void addChar();
};

#endif // INITTRACKER_H
