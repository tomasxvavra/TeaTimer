#include "mainwindow.h"
#include "ui_mainwindow.h"

static constexpr auto UPDATE_PERIOD_MS = 1000;

MainWindow::MainWindow(QWidget *parent) :
	QWidget(parent)
{
	mElapsedTimer.start();
	mUpdateTimer.start(UPDATE_PERIOD_MS);
	ui.setupUi(this);
	adjustSize();

	connect(&mUpdateTimer,			SIGNAL(timeout()),
			this,					SLOT(updateView()));
	connect(ui.pushButton_restart,	SIGNAL(pressed()),
			this,					SLOT(onBtnRestart()));
	connect(ui.timeEditDelay,		SIGNAL(timeChanged(QTime)),
			this,					SLOT(onTimeEditChanged(QTime)));

	setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);

	onTimeEditChanged(ui.timeEditDelay->time());
}

MainWindow::~MainWindow()
{

}

void MainWindow::updateView(){
	// Construct elapsed QTime
	qint64 elapsedTotal_ms = mElapsedTimer.elapsed();
	qint64 elapsed_ms = elapsedTotal_ms;
	qint64 elapsed_s = elapsed_ms/1000;
	elapsed_ms = elapsed_ms - elapsed_s*1000;
	qint64 elapsed_min = elapsed_s / 60;
	elapsed_s = elapsed_s - elapsed_min*60;
	QTime elapsed(0, elapsed_min, elapsed_s, elapsed_ms);
	if (!elapsed.isValid()){
		return;
	}

	if (elapsedTotal_ms < mDelay_ms){
		// Not expired
		if (mExpired){
			mExpired = false;
			this->setStyleSheet("");
			ui.progressBarRemins->setStyleSheet("color: rgb(0, 0, 0);");
		}
		ui.progressBarRemins->setValue(elapsedTotal_ms);
	}
	else{
		// Expired
		if (!mExpired){
			mExpired = true;
			this->setStyleSheet("background-color: rgb(255, 194, 194);");
			ui.progressBarRemins->setStyleSheet("color: rgb(255, 0, 0);");
			ui.progressBarRemins->setValue(mDelay_ms);
			QApplication::alert(this, 0);
		}
	}

	ui.progressBarRemins->setFormat(elapsed.toString("mm:ss"));
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
	ui.progressBarRemins->setMaximum(mDelay_ms);
	if (mExpired){
		ui.progressBarRemins->setValue(mDelay_ms);
	}

	updateView();
}
