#include <QDebug>
#include <QListWidgetItem>
#include <QLineEdit>

#include "client.h"
#include "d2h.h"
#include "ui_d2h.h"
#include "worker.h"

d2h::d2h(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::d2h)
{
    ui->setupUi(this);

    client = new Client();
    generateEdits();

    Worker *w = new Worker( guiobj );
    w->start();
}

d2h::~d2h()
{
    if( client ) {
        delete client;
    }

    delete ui;
}

void d2h::generateEdits() {
    QLabel *ql;
    int h, i, x, y, a, b, ptr;
    struct guiobj_s *idx;
    char *allocptr;

    a = 20;
    b = 30;
    x = 100;
    y = 30;

#define DR(s)\
    ql = new QLabel(s, ui->tabWidget->widget(0));\
    ql->setGeometry(QRect(a, b, 70, 20));\
    b+=20;
    DR("Playername");
    DR("Hero Model");
    DR("Hero ID");
    DR("X");
    DR("Y");
    DR("Side");
    DR("Max HP");
    DR("HP");
    DR("Kills");
    DR("Assists");
    DR("Deaths");
    DR("Level");
    DR("Last hits");
    DR("Denies");
    DR("Total gold");
    DR("Total exp");
    DR("Gold0");
    DR("Gold1");

    guiobj = (struct guiobj_s ***)malloc( sizeof( struct guiobj_s ) * 4 ) ;
    allocptr = (char *)malloc( sizeof( struct guiobj_s ) * 256  * 4);
    memset( allocptr, 0, sizeof( struct guiobj_s ) * 256 * 4 );
    for( i = 0; i < 4; i++ ) {
        guiobj[i] = (struct guiobj_s **)allocptr+256*i;
    }

    ptr = 0;
#define GI(s)\
    idx = (struct guiobj_s *)malloc( sizeof( struct guiobj_s ));\
    idx->qe = s;\
    guiobj[0][ptr] = idx;\
    ptr++;

    GI(ui->leRadiant);
    GI(ui->leDire);
    GI(ui->leGametime);
    GI(ui->leRoshan);

    for( h = 0; h < 10; h++ ) {
        for( i = 0; i < 18; i++ ) {
            QLineEdit *qe = new QLineEdit(ui->tabWidget->widget(0));
            qe->setGeometry(QRect(x, y, 60, 20));
            qe->setEnabled(false);
            idx = (struct guiobj_s *)malloc( sizeof( struct guiobj_s ));
            idx->qe = qe;
            guiobj[0][ptr++] = idx;
            y += 20;
        }
        y = 30;
        if( h == 4 ) {
            x += 100;
        } else {
            x += 60;
        }
    }

    a = 20;
    b = 30;
    x = 100;
    y = 30;

    ptr = 0;
#define DR(s)\
    ql = new QLabel(s, ui->tabWidget->widget(1));\
    ql->setGeometry(QRect(a, b, 70, 20));\
    b+=20;
    DR("Tier1 Top");
    DR("Tier1 Mid");
    DR("Tier1 Bot");
    DR("Tier2 Top");
    DR("Tier2 Mid");
    DR("Tier2 Bot");
    DR("Tier3 Top");
    DR("Tier3 Mid");
    DR("Tier3 Bot");
    DR("Tier4 Top");
    DR("Tier4 Mid");

    for( h = 0; h < 2; h++ ) {
        for( i = 0; i < 11; i++ ) {
            QLineEdit *qe = new QLineEdit(ui->tabWidget->widget(1));
            qe->setGeometry(QRect(x, y, 60, 20));
            qe->setEnabled(false);
            idx = (struct guiobj_s *)malloc( sizeof( struct guiobj_s ));
            idx->qe = qe;
            guiobj[1][ptr++] = idx;
            y += 20;
        }

        y = 30;
        x += 60;
    }
}

void d2h::systemMsg( const char *msg ) {
    if( ui->listWidget->count() > 10 ) {
        ui->listWidget->clear();
    }

    QListWidgetItem *listitem = new QListWidgetItem;
    listitem->setText( msg );
    ui->listWidget->addItem( listitem );
}

void d2h::on_pbConnect_clicked() {
    if( client->connected ) {
        client->closeClient();
        systemMsg( "Disconnected.");
        ui->pbConnect->setText("Connect");
        ui->pbStream->setEnabled(false);
        return;
    }

    if( client->initClient( ui->editIP->text().toLocal8Bit().data(), ui->editPass->text().toInt() ) != 0 ) {
        systemMsg( "Connection failed.");
        return;
    }

    systemMsg( "Connected.");
    ui->pbConnect->setText("Disconnect");
    ui->pbStream->setEnabled(true);

    qDebug() << "clicked";
}
