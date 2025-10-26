#ifndef EMULATOR_MAINWINDOW_H
#define EMULATOR_MAINWINDOW_H

#include <QWidget>

#include "Emulator.h"


QT_BEGIN_NAMESPACE

namespace Ui {
    class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : public QWidget {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
    Emulator emulator;

    void initButtons();

    void updateLayout() const;

    void initEmulator();

private slots:
    void nextStep();

    void loadData();

    void loadCommands();
};


#endif //EMULATOR_MAINWINDOW_H
