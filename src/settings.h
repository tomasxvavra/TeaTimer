#ifndef SETTINGS_H
#define SETTINGS_H

class Settings
{
public:
	static Settings & get();

	Settings();
	~Settings();


	void lastDuration(int aDuration_s);
	int lastDuration() const;

private:
	int mlastDuration;
	static Settings * mInstance;
};

#endif // SETTINGS_H
