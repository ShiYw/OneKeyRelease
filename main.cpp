#include <QCoreApplication>
#include <QProcess>
#include <iostream>
#include <QStringList>
#include <QString>
#include <QDebug>
QString runcmd(const QString& cmd){

    QProcess p(0);
    p.start(cmd.toLatin1().constData());
    p.waitForStarted();
    p.waitForFinished();
    QString result=QString::fromLocal8Bit(p.readAllStandardOutput());
#ifdef DEBUG
    std::cout<< result;
#endif
    return result ;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    if(argc<3 || argv[1] == "-h" || argv[1] == "--help"){
        std::cout<<"Give me a path of an excu and a dir,i will copy the libs it need to the dir/n";
        return 0;
    }
    QString cmd("ldd ");
    cmd.append(argv[1]);
    QString result = runcmd(cmd);
    QStringList list = result.split('\n',QString::SkipEmptyParts);
    for(int i = 1; i< list.length();i++){
        int left = list[i].indexOf('>');
        int right = list[i].indexOf('(');
        QString path = list[i].mid(left+1,right - left - 2);
        std::cout<<"cp " <<path.toStdString() <<"  " <<*argv[2]<<std::endl;
        runcmd("cp " + path +"  " + QString(argv[2]));
    }
    std::cout<<"Done. copyed "<<list.size() - 1<<" in all.\n";
    return 0;
}

