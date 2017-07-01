#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMenu>
#include "settings.h"

static constexpr auto UPDATE_PERIOD_MS = 1000;
static constexpr auto ALARM_FLASH_PERIOD_MS = 400;

MainWindow::MainWindow(QWidget *parent) :
	QWidget(parent)
{
	mElapsedTimer.start();
	mUpdateTimer.start(UPDATE_PERIOD_MS);
	ui.setupUi(this);
	adjustSize();

	auto duration = Settings::get().lastDuration();
	ui.timeEditDelay->setTime(QTime(0,0,0).addSecs(duration));

	connect(&mUpdateTimer,			SIGNAL(timeout()),
			this,					SLOT(updateView()));
	connect(ui.pushButton_restart,	SIGNAL(pressed()),
			this,					SLOT(onBtnRestart()));
	connect(ui.timeEditDelay,		SIGNAL(timeChanged(QTime)),
			this,					SLOT(onTimeEditChanged(QTime)));
	connect(&mFlashTimer,			SIGNAL(timeout()),
			this,					SLOT(onAlarmFlash()));

	QVector<QTime> mTimes = {
		QTime(0,0,30),
		QTime(0,0,45),
		QTime(0,1,0),
		QTime(0,1,15),
		QTime(0,1,30),
		QTime(0,1,45),
		QTime(0,2,0),
		QTime(0,2,15),
		QTime(0,2,30),
		QTime(0,2,45),
		QTime(0,3,0),
		QTime(0,3,30),
		QTime(0,4,0),
		QTime(0,5,0),
		QTime(0,6,0),
	};

	for (QTime & time : mTimes){
		Q_ASSERT(time.isValid());
		auto a = new QAction(time.toString("mm:ss"), this);
		connect(a,						&QAction::triggered,
				[this, time](bool){ ui.timeEditDelay->setTime(time); });
		ui.toolButton->addAction(a);
	}

	setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);

	onTimeEditChanged(ui.timeEditDelay->time());
}

MainWindow::~MainWindow()
{
	auto duration = QTime(0,0,0).secsTo(ui.timeEditDelay->time());
	Settings::get().lastDuration(duration);
}

void MainWindow::drawAlarm(bool aActive){
	if (aActive){
		this->setStyleSheet("background-color: rgb(255, 194, 194);");
		ui.progressBarRemains->setStyleSheet("color: rgb(255, 0, 0);");
	}
	else{
		// Reset style sheets
		this->setStyleSheet("");
		ui.progressBarRemains->setStyleSheet("color: rgb(0, 0, 0);");
	}
}

void MainWindow::updateView(){
	// Construct elapsed QTime
	qint64 elapsedTotal_ms = mElapsedTimer.elapsed();
	qint64 elapsed_ms = elapsedTotal_ms;
	qint64 elapsed_s = elapsed_ms/1000;
	elapsed_ms = elapsed_ms - elapsed_s*1000;

	auto elapsed = QTime(0,0,0).addMSecs(elapsed_ms).addSecs(elapsed_s);
	if (!elapsed.isValid()){
		return;
	}

	if (elapsedTotal_ms < mDelay_ms){
		// Not expired
		if (mExpired){
			mExpired = false;
			mFlashTimer.stop();
			drawAlarm(false);
		}
		ui.progressBarRemains->setValue(elapsedTotal_ms);
	}
	else{
		// Expired
		if (!mExpired){
			mExpired = true;
			mAlarmState = true;
			mFlashTimer.start(ALARM_FLASH_PERIOD_MS/2);	// Start the flashing alarm
			ui.progressBarRemains->setValue(mDelay_ms);	// Why?
			QApplication::alert(this, 0);
		}
	}

	ui.progressBarRemains->setFormat(elapsed.toString("mm:ss"));
	return;
}

void MainWindow::onBtnRestart(){
	this->setStyleSheet("");
	mElapsedTimer.start();
	mUpdateTimer.start();
	updateView();
}

void MainWindow::onBtnOptions(){

}

void MainWindow::onTimeEditChanged(QTime time){
	mDelay_ms = (time.minute()*60 + time.second()) * 1000;
	ui.progressBarRemains->setMaximum(mDelay_ms);
	if (mExpired){
		ui.progressBarRemains->setValue(mDelay_ms);
	}

	updateView();
}

void MainWindow::onAlarmFlash(){
	drawAlarm(mAlarmState);
	mAlarmState = !mAlarmState;
}
