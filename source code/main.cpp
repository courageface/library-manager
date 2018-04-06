#include <QTextCodec>
#include "login.h"
#include <QApplication>
#include "form.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    Form f;
    f.show();



    return a.exec();
}
