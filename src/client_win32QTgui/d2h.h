#ifndef D2H_H
#define D2H_H

#include <QMainWindow>
#include <QLineEdit>
#include "client.h"

struct guiobj_s {
    QLineEdit *qe;
};

namespace Ui {
class d2h;
}

class d2h : public QMainWindow
{
    Q_OBJECT

public:
    explicit d2h(QWidget *parent = 0);
    ~d2h();

private:
    void systemMsg( const char *msg );
    void generateEdits();

private slots:
    void on_pbConnect_clicked();

private:
    Ui::d2h *ui;
    struct guiobj_s ***guiobj;
    Client *client;
};

#endif // D2H_H
