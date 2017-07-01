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
	QTimer mFlashTimer;
	bool mExpired;
	qint64 mDelay_ms;
	bool mAlarmState;

	void drawAlarm(bool aActive);

private slots:
	void updateView();
	void onBtnRestart();
	void onBtnOptions();
	void onTimeEditChanged(QTime);
	void onAlarmFlash();

};

#endif // MAINWINDOW_H
