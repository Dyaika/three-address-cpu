#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QRegularExpression>
#include <QMessageBox>
#include "Commands.h"


MainWindow::MainWindow(QWidget *parent) : QWidget(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    initEmulator();
    initButtons();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::initButtons() {
    connect(ui->CommandsButton, &QPushButton::clicked, this, &MainWindow::loadCommands);
    connect(ui->DataButton, &QPushButton::clicked, this, &MainWindow::loadData);
    connect(ui->NextButton, &QPushButton::clicked, this, &MainWindow::nextStep);
    connect(ui->RunButton, &QPushButton::clicked, this, &MainWindow::runProgram);
}


void MainWindow::updateLayout() const {
    // PC
    const auto pc = emulator.getPC();
    ui->RBin_PC->setText(QString("%1").arg(pc, 16, 2, QLatin1Char('0')));
    ui->RHex_PC->setText(QString("%1").arg(pc, 4, 16, QLatin1Char('0')).toUpper());
    ui->RDec_PC->setText(QString::number(pc));

    // CMD
    const auto cmd = emulator.getCMD();
    ui->RBin_CMD->setText(QString("%1").arg(cmd, 32, 2, QLatin1Char('0')));
    ui->RHex_CMD->setText(QString("%1").arg(cmd, 8, 16, QLatin1Char('0')).toUpper());
    ui->RDec_CMD->setText(QString::number(cmd));

    // REGISTERS (R0...R7)
    for (int i = 0; i < Emulator::REG_SIZE; ++i) {
        const auto reg = emulator.getRegister(i);
        QLabel *binLabel = findChild<QLabel *>(QString("RBin_%1").arg(i));
        QLabel *hexLabel = findChild<QLabel *>(QString("RHex_%1").arg(i));
        QLabel *decLabel = findChild<QLabel *>(QString("RDec_%1").arg(i));
        if (binLabel) binLabel->setText(QString("%1").arg(reg, 16, 2, QLatin1Char('0')));
        if (hexLabel) hexLabel->setText(QString("%1").arg(reg, 4, 16, QLatin1Char('0')).toUpper());
        if (decLabel) decLabel->setText(QString::number(reg));
    }
}

void MainWindow::showResults() {
    unsigned int firstTaskResult = emulator.getRegister(3);
    unsigned int secondTaskResult = 0;
    secondTaskResult += emulator.getRegister(4);
    secondTaskResult = secondTaskResult << 16;
    secondTaskResult += emulator.getRegister(3);

    QMessageBox::information(
        this,
        tr("Execution completed."),
        tr("<b>Results of emulation:</b><br><br>"
            "First task: %1<br>"
            "Second task: %2")
        .arg(firstTaskResult)
        .arg(secondTaskResult),
        QMessageBox::Ok
    );
}

void MainWindow::nextStep() {
    emulator.step();
    updateLayout();
    if (emulator.getCMD() >> 28 == Commands::END) {
        showResults();
    }
}

void MainWindow::loadData() {
    if (emulator.getPC() != 0) {
        initEmulator();
    }
    const QString text = ui->DataTextEdit->toPlainText();
    static const QRegularExpression lineBreaks("[\r\n]+");
    QStringList lines = text.split(lineBreaks, Qt::SkipEmptyParts);

    const auto n = lines.count();
    const int count = (n > INT_MAX) ? INT_MAX : static_cast<int>(n);

    auto *data = new unsigned short[n];
    for (int i = 0; i < count; i++) {
        bool ok = false;
        const unsigned short value = lines[i].trimmed().toUShort(&ok, 0);
        if (ok)
            data[i] = value;
    }
    emulator.loadData(data, count);
}

void MainWindow::loadCommands() {
    if (emulator.getPC() != 0) {
        initEmulator();
    }

    const QString text = ui->CommandsTextEdit->toPlainText();
    static const QRegularExpression lineBreaks("[\r\n]+");
    QStringList lines = text.split(lineBreaks, Qt::SkipEmptyParts);

    const auto n = lines.count();
    const int count = (n > INT_MAX) ? INT_MAX : static_cast<int>(n);

    auto *commands = new std::string[n];
    for (int i = 0; i < count; i++) {
        const std::string value = lines[i].toStdString();
        commands[i] = value;
    }
    try
    {
        emulator.loadProgram(commands, count);
    }
    catch (...)
    {
        initEmulator();
        QMessageBox::information(
        this,
        tr("Failed."),
        tr("Error while parsing program."),
        QMessageBox::Ok
    );
    }
}

void MainWindow::initEmulator() {
    emulator = Emulator();
    updateLayout();
}

void MainWindow::runProgram() {
    emulator.run();
    updateLayout();
    showResults();
}
