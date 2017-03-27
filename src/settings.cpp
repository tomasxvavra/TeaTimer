#include "settings.h"
#include <QSettings>
#include <exception>

static constexpr auto KEY_LAST_DURATION = "last-duration";

Settings * Settings::mInstance {nullptr};

Settings & Settings::get(){
	if (!mInstance){
		throw std::runtime_error("Settings instance not valid.");
	}
	return *mInstance;
}

Settings::Settings()
{
	mInstance = this;

	QSettings s;
	bool ok {false};
	mlastDuration = s.value(KEY_LAST_DURATION, 90).toInt(&ok);
	if (!ok){
		s.setValue(KEY_LAST_DURATION, 90);
	}
}

Settings::~Settings(){
	mInstance = nullptr;
}

void Settings::lastDuration(int aDuration_s){
	mlastDuration = aDuration_s;
	QSettings s;
	s.setValue(KEY_LAST_DURATION, aDuration_s);
}

int Settings::lastDuration() const{
	return mlastDuration;
}
