#ifndef TIMEEDIT_H
#define TIMEEDIT_H

#include<QTimeEdit>

class TimeEdit : public QTimeEdit
{
	Q_OBJECT
public:
	TimeEdit(QWidget *parent=nullptr);

	virtual void stepBy(int steps) override;
};

#endif // TIMEEDIT_H
