#include "qudong.h"
#include <QProcess>
#include <QMessageBox>
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QApplication>
QuDong::QuDong()
{

}

void QuDong::startRun(QString fileName, QString outName)
{

//    QProcess *p1 = new QProcess;//./home/a913/Qt_project/20190910/prototype_v0906/Projects/test/code/radar_test.out
//    p1->start("g++", QStringList() << "/home/a913/Qt_project/20190910/prototype_v0906/Projects/test/code/radar_test.cpp"<< "-fopenmp"<< "-lfftw3"<< "-lm"<< "-o" <<"/home/a913/Qt_project/20190910/prototype_v0906/Projects/test/code/radar_test.out");
//    p1->waitForStarted();
//    p1->close();
//    p1->waitForFinished();
    QStringList args;
        args.append(fileName);
        args.append("-fopenmp");
        args.append("-lfftw3");
        args.append("-lm");
        args.append("-o");
        args.append(outName);
        QString command = args.join(" ");
        qDebug() << "command: " << command;

    QProcess *p1 = new QProcess;
    p1->start("g++", args);
    p1->waitForStarted();
    p1->waitForFinished();
    p1->close();
    p1->kill();

    QProcess *p = new QProcess;
    QString workpath = "/home/a913/Qt_project/20190910/prototype_v0906/Projects/test/code/";
    p->setWorkingDirectory(workpath);
    qDebug() << p->environment();
    p->start("./radar_test.out");
    p->waitForStarted();
    p->waitForFinished();

    QString strTemp=QString::fromLocal8Bit(p->readAllStandardOutput());
    QString strError=QString::fromLocal8Bit(p->readAllStandardError());

    p->close();
    p->kill();

    qDebug() << strTemp << ";" << strError;
    QMessageBox testMassage;
    testMassage.setText(strTemp+strError);
    testMassage.exec();
}
