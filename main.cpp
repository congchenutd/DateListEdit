#include "DateListLineEdit.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DateListLineEdit edit("MM/dd/yyyy", '_', ',');
    edit.show();
    return a.exec();
}
