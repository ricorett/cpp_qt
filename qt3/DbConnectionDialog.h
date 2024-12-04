#pragma once
#include <QDialog>
#include <QString>

namespace Ui {
    class DbConnectionDialog;
}

class DbConnectionDialog : public QDialog {
Q_OBJECT

public:
    explicit DbConnectionDialog(QWidget *parent = nullptr);
    ~DbConnectionDialog();

    QString getHostName() const;
    QString getDatabaseName() const;
    QString getUsername() const;
    QString getPassword() const;
    uint getPort() const;

private slots:
    void onOkButtonClicked();
    void onCancelButtonClicked();

private:
    Ui::DbConnectionDialog *ui;
    QString hostName;
    QString databaseName;
    QString username;
    QString password;
    uint port;
};

