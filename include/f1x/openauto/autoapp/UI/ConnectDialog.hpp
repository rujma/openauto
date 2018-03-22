#pragma once

#include <QDialog>
#include <f1x/aasdk/TCP/ITCPEndpoint.hpp>
#include <f1x/aasdk/TCP/ITCPWrapper.hpp>

namespace Ui {
class ConnectDialog;
}

namespace f1x
{
namespace openauto
{
namespace autoapp
{
namespace ui
{

class ConnectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectDialog(boost::asio::io_service& ioService,  aasdk::tcp::ITCPWrapper& tcpWrapper, QWidget *parent = nullptr);
    ~ConnectDialog() override;

signals:
    void connectToDevice(const QString& ipAddress);
    void connectionSucceed(aasdk::tcp::ITCPEndpoint::SocketPointer socket);
    void connectionFailed();

private slots:
    void onConnectButtonClicked();
    void onConnectionFailed();
    void onConnectionSucceed();
    void setControlsEnabledStatus(bool status);

private:
    boost::asio::io_service& ioService_;
    aasdk::tcp::ITCPWrapper& tcpWrapper_;
    Ui::ConnectDialog *ui_;
};

}
}
}
}
