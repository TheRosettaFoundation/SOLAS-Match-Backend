
#include "Smtp.h"

#include <QDebug>

#include "../Common/ConfigParser.h"

Smtp::Smtp( const QString &from, const QString &to, const QString
&subject, const QString &body )
{
    this->init(from, to, subject, body);
}

Smtp::Smtp(Email *email)
{
    this->init(email->getSender(), email->getRecipient(),
               email->getSubject(), email->getBody());
}

Smtp::~Smtp()
{
    delete t;
    delete socket;
}

void Smtp::init(const QString &from, const QString &to, const QString
                &subject, const QString &body )
{
    socket = new QTcpSocket( this );
    connect( socket, SIGNAL( readyRead() ), this, SLOT( readyRead() ) );
    connect( socket, SIGNAL( connected() ), this, SLOT( connected() ) );
    connect( socket, SIGNAL( error( QAbstractSocket::SocketError) ),
             this, SLOT( errorReceived( QAbstractSocket::SocketError ) ) );
    connect( socket, SIGNAL( stateChanged( QAbstractSocket::SocketState)),
             this, SLOT( stateChanged( QAbstractSocket::SocketState ) ) );
    connect( socket, SIGNAL( disconnected()), this,
             SLOT(disconnected() ) );
    message = QString::fromLatin1( "From: " ) +
            from+QString::fromLatin1( "\nTo: " ) +to +QString::fromLatin1( "\nSubject: "
            ) +subject +QString::fromLatin1( "\n\n" ) +body +"\n";
    message.replace( QString::fromLatin1( "\n" ), QString::fromLatin1("\r\n" ) );
    message.replace( QString::fromLatin1( "\r\n.\r\n" ),
                     QString::fromLatin1( "\r\n..\r\n" ) );
    this->from = from;
    rcpt = to;
    state = Init;

    ConfigParser mParser;
    QString hostName = mParser.get("mail.server");
    int port = mParser.get("mail.port").toInt();
    socket->connectToHost( hostName, port );

    if( socket->waitForConnected( 30000 ) )
        qDebug() << ("connected");

    t = new QTextStream( socket );
}

void Smtp::stateChanged( QAbstractSocket::SocketState socketState)
{
    qDebug() <<"stateChanged " << socketState;
}

void Smtp::errorReceived( QAbstractSocket::SocketError socketError)
{
    qDebug() << "error " <<socketError;
}

void Smtp::disconnected()
{
    qDebug() <<"disconneted";
    qDebug() << "error "  << socket->errorString();
}

void Smtp::connected()
{
    qDebug() << "Connected ";
}

void Smtp::readyRead()
{
    qDebug() << "Ready Read";
    if( !socket->canReadLine() )
        return;

    QString responseLine;

    do {
        responseLine = socket->readLine();
        response += responseLine;
    } while( socket->canReadLine() && responseLine[3] != ' ' );

    responseLine.truncate( 3 );

    if ( state == Init && responseLine[0] == '2' )
    {
        // banner was okay, let's go on
        *t << "HELO there\r\n";
        t->flush();
        state = Mail;
        qDebug() << "Sent hello";
    }
    else if ( state == Mail && responseLine[0] == '2' )
    {
        // HELLO response was okay (well, it has to be)
        *t << "MAIL FROM: <" << from << ">\r\n";
        t->flush();
        state = Rcpt;
        qDebug() << "Sent MAIL FROM";
    }
    else if ( state == Rcpt && responseLine[0] == '2' )
    {

        *t << "RCPT TO: <" << rcpt << ">\r\n";
        t->flush();
        state = Data;
        qDebug() << "Sent recipient";
    }
    else if ( state == Data && responseLine[0] == '2' )
    {
        *t << "DATA\r\n";
        t->flush();
        state = Body;
        qDebug() << "Sent body";
    }
    else if ( state == Body && responseLine[0] == '3' )
    {
        *t << message << ".\r\n";
        t->flush();
        state = Quit;
        qDebug() << "Sent message";
    }
    else if ( state == Quit && responseLine[0] == '2' )
    {
        *t << "QUIT\r\n";
        // here, we just close.
        state = Close;
        //t->flush();
        qDebug() << "Sent QUIT";
        emit status( tr( "Message sent" ) );
    }
    else if ( state == Close )
    {
        deleteLater();
        qDebug() << "Closing";
        return;
    }
    else
    {
        // something broke.
        qDebug() << tr( "Qt Mail Example" ) << tr( "Unexpected reply from SMTP server:\n\n" )
                 << response;
        state = Close;
    }
    response = "";
}
