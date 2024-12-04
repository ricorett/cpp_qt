#include "DbConnectionDialog.h"
#include "ui_DbConnectionDialog.h"

DbConnectionDialog::DbConnectionDialog(QWidget *parent)
        : QDialog(parent),
          ui(new Ui::DbConnectionDialog),
          port(0) {
    ui->setupUi(this);

    // Связываем кнопки с слотами
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &DbConnectionDialog::onOkButtonClicked);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &DbConnectionDialog::onCancelButtonClicked);
}

DbConnectionDialog::~DbConnectionDialog() {
    delete ui;
}

void DbConnectionDialog::onOkButtonClicked() {
    hostName = ui->hostNameLineEdit->text();
    databaseName = ui->databaseNameLineEdit->text();
    username = ui->usernameLineEdit->text();
    password = ui->passwordLineEdit->text();
    port = ui->portSpinBox->value();
    accept(); // Закрывает окно с результатом "Accepted"
}

void DbConnectionDialog::onCancelButtonClicked() {
    reject(); // Закрывает окно с результатом "Rejected"
}

QString DbConnectionDialog::getHostName() const {
    return hostName;
}

QString DbConnectionDialog::getDatabaseName() const {
    return databaseName;
}

QString DbConnectionDialog::getUsername() const {
    return username;
}

QString DbConnectionDialog::getPassword() const {
    return password;
}

uint DbConnectionDialog::getPort() const {
    return port;
}