#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QTimer>
#include <QElapsedTimer>
#include "ui_mainwindow.h"

class MainWindow : public QWidget
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private:
	Ui::MainWindow ui;
	QElapsedTimer mElapsedTimer;
	QTimer mUpdateTimer;
	bool mExpired;
	qint64 mDelay_ms;

private slots:
	void updateView();
	void onBtnRestart();
	void onBtnOptions();
	void onTimeEditChanged(QTime);

};

#endif // MAINWINDOW_H
