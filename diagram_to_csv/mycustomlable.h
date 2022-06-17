#ifndef MYCUSTOMLABLE_H
#define MYCUSTOMLABLE_H

#include <QLabel>

class MyCustomLable : public QLabel{
    Q_OBJECT
public:
    MyCustomLable(QWidget* parent);

signals:
    void myLabelClicked(bool t,int x,int y);       // Signal to emit

protected:
    bool event(QEvent *myEvent); // This method will give all kind of events on Label Widget
};


#endif // MYCUSTOMLABLE_H
