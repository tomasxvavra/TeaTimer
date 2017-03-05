#include "timeedit.h"

static constexpr auto MIN_SECS = 5;
static constexpr auto STEP_SEC = 5;

TimeEdit::TimeEdit(QWidget *parent) :
	QTimeEdit(parent)
{
	QFont font;
	font.setPointSize(12);
	setFont(font);
	setWrapping(true);
	setDateTime(QDateTime(QDate(2000, 1, 1), QTime(0, 1, 30)));
	setMinimumTime(QTime(0, 0, MIN_SECS));
	setCurrentSection(QDateTimeEdit::MinuteSection);
	setTime(QTime(0, 1, 30));
	setDisplayFormat("mm:ss");
}

void TimeEdit::stepBy(int steps){
	auto t = time();
	auto section = currentSection();

	// Ignore multiple steps at once for simplicity
	if (steps > 1){
		steps = 1;
	}
	else if (steps < -1){
		steps = -1;
	}

	// Handle overflow cases or continue to default action
	if (section == QTimeEdit::SecondSection){
		steps *= STEP_SEC;
		// Provide underflow and overflow of seconds to minutes
		if (steps > 0){
			// ### Incrementing
			if ((t.second() + steps) > 59){
				// Overflow
				auto rem = (t.second() + steps) % 60;
				setTime(QTime(0,t.minute()+1,rem));
				return;
			}
		}
		else if (steps < 0){
			// ### Decrementing
			auto under = t.second() + steps;
			if (t.minute() > 0){
				// Enable underflow
				if (under < 0){
					// Underflow
					if (t.minute() > 0){
						setTime(QTime(0,t.minute()-1,60+under));
					}
					return;	// Do not wrap the seconds
				}
			}
			else{
				// Disable seconds underflow when minutes are 0
				if (under < MIN_SECS){
					// Clamp on lower limit
					if (t.second() != MIN_SECS){
						setTime(QTime(0,0,MIN_SECS));
					}
					return;
				}
			}
		}
	}
	else if (section == QTimeEdit::MinuteSection){
		// Provide underflow of 1 minute to 60-STEP_SEC seconds
		if (steps == -1){
			// Modify only decrementing
			if (t.minute() == 1){
				setTime(QTime(0,0,60-STEP_SEC));
				setCurrentSection(QTimeEdit::SecondSection);
				return;
			}
			else if (t.minute() == 0){
				return;	// Do not wrap to 59
			}
		}
	}

	// Default
	QTimeEdit::stepBy(steps);
}
